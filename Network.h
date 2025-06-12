// Kamil Eren Ezen
// 040210021
#pragma once
#include <vector>
#include "Layer.h"

class Network {
private:
    //Object's variables.
    std::vector<Layer> layers;
    double learningRate;

public:
    //Constructor and functions.
    Network(double lr = 0.1);

    void addLayer(int num_neurons, int num_inputs_per_neuron);
    std::vector<double> forward(const std::vector<double>& inputs);

    void train(const std::vector<std::vector<double>>& inputs,
        const std::vector<std::vector<double>>& targets,
        double lossThreshold,
        int maxEpochs = 50);


    int predict(const std::vector<double>& input);
};
