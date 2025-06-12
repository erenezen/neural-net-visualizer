# Neural Net Visualizer

This is a simple C++ project with an interactive GUI for building, training, and testing a basic feedforward neural network on the MNIST dataset.

Users can add layers and neurons through the GUI, train the model using backpropagation, and test its accuracy. The GUI is built using **SFML**, and the project is written entirely in C++.

## Requirements

- C++17 compatible compiler (e.g., g++, clang++, MSVC)
- [SFML 2.5+](https://www.sfml-dev.org/download.php)
- MNIST dataset in CSV format (place in a `data/` folder)

## How to Build

You can either build the project using a terminal or open it in Visual Studio:

```bash
# Option 1: Build with terminal
g++ -std=c++17 src/*.cpp -o mnist_gui -lsfml-graphics -lsfml-window -lsfml-system

# Option 2: Open in Visual Studio (Windows)
# - Link the SFML libraries correctly in your project settings.
# - Set the include and library paths for SFML.
# - Make sure the SFML .dll files are in your executable directory.
