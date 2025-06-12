// Kamil Eren Ezen
// 040210021
#include "Network.h"
#include <cmath>
#include <iostream>

Network::Network(double lr) : learningRate(lr) {} //Constructor.

void Network::addLayer(int num_neurons, int num_inputs_per_neuron) { //Add layer to the network with the specified number of neurons.
    layers.emplace_back(num_neurons, num_inputs_per_neuron);
}

std::vector<double> Network::forward(const std::vector<double>& inputs) {//Forward pass func. using given input.
    std::vector<double> out = inputs;
    for (auto& layer : layers) { //Pass the input from each layer.
        out = layer.forward(out);
    }
    return out;
}

void Network::train(const std::vector<std::vector<double>>& inputs,//Trains the network (Stops training if average loss falls below a specified threshold or maxEpochs is reached.).
    const std::vector<std::vector<double>>& targets,
    double lossThreshold,
    int maxEpochs) {
    bool stoppedEarly = false; //This is for indicating if early stopping happens.

    for (int epoch = 0; epoch < maxEpochs; ++epoch) {
        double totalLoss = 0.0;

        for (size_t i = 0; i < inputs.size(); ++i) {//Loop through each training sample.
            std::vector<double> activations = inputs[i];
            for (auto& layer : layers) {
                activations = layer.forward(activations);//Forward Pass.
            }

            for (size_t j = 0; j < activations.size(); ++j) {//Calculate loss(mean squared error).
                double diff = targets[i][j] - activations[j];
                totalLoss += diff * diff;
            }

            Layer& outputLayer = layers.back();
            for (size_t j = 0; j < outputLayer.getNeurons().size(); ++j) { //Itarete the neurons in output layer.
                double o = outputLayer.getNeurons()[j].getOutput(); //Output
                double t = targets[i][j];                           //Target output    
                double delta = (t - o) * o * (1.0 - o);             //Delta using sigmoid derivative.        
                outputLayer.getNeurons()[j].setDelta(delta);
            }

            for (int l = layers.size() - 2; l >= 0; --l) {
                Layer& current = layers[l];
                Layer& next = layers[l + 1];

                for (size_t j = 0; j < current.getNeurons().size(); ++j) {
                    double o = current.getNeurons()[j].getOutput();
                    double sum = 0.0;
                    for (auto& nextNeuron : next.getNeurons()) {//Sum of delta*weight from next layer. 
                        sum += nextNeuron.getWeights()[j] * nextNeuron.getDelta();
                    }
                    double delta = o * (1.0 - o) * sum; //Delta for current neuron.
                    current.getNeurons()[j].setDelta(delta);
                }
            }
            //Update weights and biases.
            std::vector<double> prevOutputs = inputs[i]; //Start with original input.
            for (auto& layer : layers) {
                std::vector<double> newOutputs;
                for (auto& neuron : layer.getNeurons()) {
                    neuron.forward(prevOutputs);
                    for (size_t w = 0; w < neuron.getWeights().size(); ++w) { //Update weights.
                        neuron.getWeights()[w] += learningRate * neuron.getDelta() * prevOutputs[w];
                    }
                    neuron.getBias() += learningRate * neuron.getDelta(); //Update bias.
                    newOutputs.push_back(neuron.getOutput());
                }
                prevOutputs = newOutputs;
            }
        }

        double avgLoss = totalLoss / inputs.size(); //Compute average loss.
        std::cout << "Epoch " << epoch + 1 << ", Loss: " << avgLoss << std::endl;

        if (avgLoss < lossThreshold) {//Early stopping.
            stoppedEarly = true;
            break;
        }
    }

    if (stoppedEarly) {
        std::cout << "Stopped early (loss < " << lossThreshold << ")" << std::endl;
    }
}




int Network::predict(const std::vector<double>& input) {//Predicts the class for input.
    std::vector<double> out = forward(input);
    int prediction = std::distance(out.begin(), std::max_element(out.begin(), out.end()));
    return prediction; //Return the index of the highest output value.
}
