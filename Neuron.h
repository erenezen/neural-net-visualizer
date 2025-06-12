// Kamil Eren Ezen
// 040210021
#pragma once
#include <vector>
#include <cstdlib>
#include <cmath>

class Neuron {
private:
    //Object's variables.
    std::vector<double> weights;
    double bias;
    double output;
    double delta;

public:
    //Constructor and functions.
    Neuron(int num_inputs);
    double forward(const std::vector<double>& inputs);
    static double activate(double x);
    static double activateDerivative(double x);
    double getOutput() const;
    void setDelta(double d);
    double getDelta() const;
    std::vector<double>& getWeights();
    double& getBias();
};
#pragma once
