// Kamil Eren Ezen
// 040210021
#pragma once
#include <vector>
#include <string>

class DataLoader {
public:
    static void loadCSV(const std::string& filename,
        std::vector<std::vector<double>>& inputs, //Inputs vector.
        std::vector<std::vector<double>>& targets, //Targets vector with limit.
        int limit = 1000);
};
