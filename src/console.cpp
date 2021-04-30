#include <iostream>
#include "console.hpp"

void console::error(std::string message) {
    std::cout << "Error: " << message << std::endl;
}

void console::warning(std::string message) {
    std::cout << "Warning: " << message << std::endl;
}

void console::info(std::string message) {
    std::cout << "Info: " << message << std::endl;
}
