#include "DataLoader.h"
#include <fstream>
#include <sstream>

void DataLoader::loadCSV(const std::string& filename, //Function that loads a .csv file and fills inputs and targets vector.
    std::vector<std::vector<double>>& inputs,
    std::vector<std::vector<double>>& targets,
    int limit) {
    std::ifstream file(filename); //Open file.
    std::string line; //line variable for the lines from  file.
    int count = 0; //Counter initialized to 0.

    while (getline(file, line) && count < limit) { //Read the lines in the file one by one until limit is reached.
        std::stringstream ss(line);
        //Variables to store the data that read from file.
        std::string value; 
        std::vector<double> input;
        int label;

        getline(ss, value, ','); //The first value.
        label = std::stoi(value);

        while (getline(ss, value, ',')) { //Read the remaining comma separated values.
            input.push_back(std::stod(value) / 255.0);  //Normalize each pixel.
        }

        std::vector<double> target(10, 0.0); //Initialize all to 0.0
        target[label] = 1.0; //Set the target with the label to 1.0

        //Add the inputs to their correct vectors.
        inputs.push_back(input);
        targets.push_back(target);
        count++;
    }
}
