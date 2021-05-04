#include "console.hpp"
#include <iostream>

void console::error(const std::string& message) {
    std::cout << "Error: " << message << std::endl;
}

void console::warning(const std::string& message) {
    std::cout << "Warning: " << message << std::endl;
}

void console::info(const std::string& message) {
    std::cout << "Info: " << message << std::endl;
}
