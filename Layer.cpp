// Kamil Eren Ezen
// 040210021
#include "Layer.h"

Layer::Layer(int num_neurons, int num_inputs_per_neuron) {//Constructor.
    for (int i = 0; i < num_neurons; ++i) {
        neurons.emplace_back(num_inputs_per_neuron); //Create each neuron and add it to the list of neurons.
    }
}

std::vector<double> Layer::forward(const std::vector<double>& inputs) {//Forward pass function. Apply for each neuron.
    outputs.clear(); //Clear previous outputs.
    for (auto& neuron : neurons) { //For each neuron in the layer.
        outputs.push_back(neuron.forward(inputs)); //Store each neuron's output.
    }
    return outputs;
}

std::vector<Neuron>& Layer::getNeurons() {//Get neurons.
    return neurons;
}

const std::vector<double>& Layer::getOutputs() const { //Get outputs.
    return outputs;
}
