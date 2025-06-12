// Kamil Eren Ezen
// 040210021
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Button.h"
#include "Network.h"
#include "DataLoader.h"

//Load random MNIST from CSV file.
void loadRandomMNISTExample(const std::string& filename, std::vector<sf::RectangleShape>& pixels) {
    std::ifstream file(filename);
    std::string line;
    size_t randomLine = rand() % 1000 + 1; //Pick a random line.
    for (size_t i = 0; i < randomLine && getline(file, line); ++i) {} //Find the random line.
    if (!line.empty()) {
        std::stringstream ss(line);
        std::string value;
        getline(ss, value, ',');
        for (auto& pixel : pixels) {//Set each pixel color based on intensity.
            if (getline(ss, value, ',')) {
                int intensity = std::stoi(value);
                sf::Uint8 color = static_cast<sf::Uint8>(intensity);
                pixel.setFillColor(sf::Color(color, color, color));
            }
        }
    }
}

int main() {
    srand(static_cast<unsigned>(time(0))); //Random seed.

    sf::RenderWindow window(sf::VideoMode(1000, 600), "MNIST Trainer GUI");
    sf::Font font;

    if (!font.loadFromFile("assets/font.ttf")) { //Load a font.
        std::cerr << "Font yuklenemedi!" << std::endl;
        return 1;
    }

    //These are for the creation of the GUI.
    Button addLayerBtn(50, 550, 150, 40, font, "Add Layer");
    Button addNeuronBtn(210, 550, 150, 40, font, "Add Neuron");
    Button buildBtn(370, 550, 150, 40, font, "Build");
    Button trainBtn(530, 550, 150, 40, font, "Train");
    Button testBtn(690, 550, 150, 40, font, "Test");

    std::vector<sf::RectangleShape> layerBoxes; //Boxes representing layers.
    std::vector<std::vector<sf::CircleShape>> neuronsInLayers; //Circles in the layer.
    std::vector<sf::VertexArray> connections; //Connection lines between neurons.

    float nextLayerX = 350.0f;

    //Initialize the 28x28 MNIST digit display.
    const int pixelSize = 10;
    std::vector<sf::RectangleShape> pixelRects;
    for (int row = 0; row < 28; ++row) { //Pixels in x axis.
        for (int col = 0; col < 28; ++col) { //Pixels in y axis.
            sf::RectangleShape pixel(sf::Vector2f(pixelSize, pixelSize));
            pixel.setPosition(50 + col * pixelSize, 150 + row * pixelSize);
            pixel.setFillColor(sf::Color::White);
            pixel.setOutlineThickness(0);
            pixelRects.push_back(pixel);
        }
    }

    Network net(0.1); //Create a neural network with learning rate of 0.1.
    std::vector<std::vector<double>> train_inputs, train_targets;
    std::vector<std::vector<double>> test_inputs, test_targets;

    //Main window loop.
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            //Mouse clicks.
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                //Add new layer box.
                if (addLayerBtn.isClicked(mousePos)) {
                    float layerWidth = 80.f;
                    float layerHeight = 300.f;
                    sf::RectangleShape layer(sf::Vector2f(layerWidth, layerHeight));
                    layer.setFillColor(sf::Color(230, 230, 255)); // soft pastel
                    layer.setOutlineColor(sf::Color(100, 100, 200));
                    layer.setOutlineThickness(2);
                    layer.setPosition(nextLayerX, 300 - layerHeight / 2);
                    layerBoxes.push_back(layer);
                    neuronsInLayers.push_back({});
                    nextLayerX += 130.0f; // daha yak�n g�r�n�m
                }

                //Add neuron to last layer.
                if (addNeuronBtn.isClicked(mousePos)) {
                    if (!neuronsInLayers.empty()) {
                        int layerIndex = neuronsInLayers.size() - 1;
                        int neuronCount = static_cast<int>(neuronsInLayers[layerIndex].size());

                        float neuronRadius = 7.f;
                        sf::CircleShape neuron(neuronRadius);
                        neuron.setFillColor(sf::Color(80, 140, 255));
                        neuron.setOrigin(neuronRadius, neuronRadius);

                        float x = layerBoxes[layerIndex].getPosition().x + layerBoxes[layerIndex].getSize().x / 2;
                        float y = layerBoxes[layerIndex].getPosition().y + 30 + neuronCount * 22;
                        neuron.setPosition(x, y);

                        neuronsInLayers[layerIndex].push_back(neuron);
                    }
                }

                //Build neural network.
                if (buildBtn.isClicked(mousePos)) {
                    connections.clear();
                    net = Network(0.1);

                    //Create lines between neurons for visualization.
                    for (size_t l = 0; l + 1 < neuronsInLayers.size(); ++l) {
                        for (const auto& from : neuronsInLayers[l]) {
                            for (const auto& to : neuronsInLayers[l + 1]) {
                                sf::VertexArray line(sf::Lines, 2);
                                line[0].position = from.getPosition();
                                line[0].color = sf::Color(180, 180, 180);
                                line[1].position = to.getPosition();
                                line[1].color = sf::Color(140, 140, 140);
                                connections.push_back(line);
                            }
                        }
                    }
                    //Add layers to the network.
                    for (size_t i = 0; i < neuronsInLayers.size(); ++i) {
                        int numNeurons = static_cast<int>(neuronsInLayers[i].size());
                        int inputCount = (i == 0) ? 784 : static_cast<int>(neuronsInLayers[i - 1].size());
                        if (numNeurons > 0)
                            net.addLayer(numNeurons, inputCount);
                    }
                }
                
                //Load the data and train.
                if (trainBtn.isClicked(mousePos)) {
                    std::cout << "Training..." << std::endl;
                    train_inputs.clear();
                    train_targets.clear();
                    DataLoader::loadCSV("assets/mnist_data_train.csv", train_inputs, train_targets, 1000);
                    loadRandomMNISTExample("assets/mnist_data_train.csv", pixelRects);
                    net.train(train_inputs, train_targets, 0.03, 20);
                }

                //Load the test data and test the model.
                if (testBtn.isClicked(mousePos)) {
                    std::cout << "Testing..." << std::endl;
                    test_inputs.clear();
                    test_targets.clear();
                    DataLoader::loadCSV("assets/mnist_data_test.csv", test_inputs, test_targets, 200);
                    int correct = 0;
                    for (size_t i = 0; i < test_inputs.size(); ++i) {
                        int predicted = net.predict(test_inputs[i]);
                        int actual = std::distance(test_targets[i].begin(), std::max_element(test_targets[i].begin(), test_targets[i].end()));
                        if (predicted == actual)
                            correct++;
                    }
                    double accuracy = 100.0 * correct / test_inputs.size();
                    std::cout << "Test Accuracy: " << accuracy << "%" << std::endl;
                }
            }
        }

        window.clear(sf::Color(245, 245, 245)); //Clear the window.

        //Draw buttons.
        addLayerBtn.draw(window);
        addNeuronBtn.draw(window);
        buildBtn.draw(window);
        trainBtn.draw(window);
        testBtn.draw(window);

        //Draw the neuron connections.
        for (const auto& line : connections)
            window.draw(line);

        //Draw each layer and its neurons.
        for (size_t i = 0; i < layerBoxes.size(); ++i) {
            window.draw(layerBoxes[i]);
            for (const auto& neuron : neuronsInLayers[i]) {
                window.draw(neuron);
            }
        }

        //Draw pixels.
        for (const auto& pixel : pixelRects)
            window.draw(pixel);

        window.display();
    }

    return 0;
}