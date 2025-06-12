// Kamil Eren Ezen
// 040210021
#include "Neuron.h"
#include <cstdlib>
#include <cmath>

Neuron::Neuron(int num_inputs) {
    for (int i = 0; i < num_inputs; ++i) {
        weights.push_back((double)rand() / RAND_MAX - 0.5); //Random weighed between [-0.5, 0.5].
    }
    bias = (double)rand() / RAND_MAX - 0.5; //Random bias between -0.5 0.5.
}

double Neuron::forward(const std::vector<double>& inputs) {//Forward pass func. Compute neuron's output.
    double sum = bias;
    for (size_t i = 0; i < weights.size(); ++i) {
        sum += weights[i] * inputs[i]; //Calsulate weighed sum of inputs.
    }
    output = activate(sum);//Apply activation func.
    return output;
}

double Neuron::activate(double x) { //Activation func.
    return 1.0 / (1.0 + exp(-x)); //Sigmoid
}

double Neuron::activateDerivative(double x) {//Derivative of the sigmoid activation function.
    double fx = activate(x); //Recalculate activation.
    return fx * (1.0 - fx); //Derivative of sigmoid.
}

double Neuron::getOutput() const { //Getter.
    return output;
}

void Neuron::setDelta(double d) { //Setter.
    delta = d;
}

double Neuron::getDelta() const { //Getter.
    return delta;
}

std::vector<double>& Neuron::getWeights() { //Getter.
    return weights;
}

double& Neuron::getBias() { //Getter.
    return bias;
}
