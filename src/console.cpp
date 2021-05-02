#include "console.hpp"
#include <iostream>

void console::error(const char message[]) {
    std::cout << "Error: " << message << std::endl;
}

void console::warning(const char message[]) {
    std::cout << "Warning: " << message << std::endl;
}

void console::info(const char message[]) {
    std::cout << "Info: " << message << std::endl;
}
