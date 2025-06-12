// Kamil Eren Ezen
// 040210021
#pragma once
#include <vector>
#include "Neuron.h"

class Layer {
private:
    std::vector<Neuron> neurons; //Neurons vector.
    std::vector<double> outputs; //Outputs vector.

public:
    Layer(int num_neurons, int num_inputs_per_neuron); //Constructor.

    std::vector<double> forward(const std::vector<double>& inputs); //Forward function.

    //Getter functions.
    std::vector<Neuron>& getNeurons();
    const std::vector<double>& getOutputs() const;
};
#pragma once
