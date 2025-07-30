#include <iostream>
#include <istream>
#include "Application.h"


int main(int args, char** argv) {
    try {
        Application::run();
    } catch (...) {
        std::cerr << "An exception occurred!" << std::endl;
    }
}

