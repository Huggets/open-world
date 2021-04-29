#include <iostream>
#include "console.hpp"

void Console::error(std::string message) {
    std::cout << "Error: " << message << std::endl;
}

void Console::warning(std::string message) {
    std::cout << "Warning: " << message << std::endl;
}

void Console::info(std::string message) {
    std::cout << "Info: " << message << std::endl;
}
