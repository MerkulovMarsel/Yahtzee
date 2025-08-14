#include <iostream>
#include "Application.h"
#include "exception/YahtzeeException.h"


int main(int args, char** argv) {
    try {
        Application::run();
    } catch (const YahtzeeException& e) {
    std::cerr << "Yahtzee" << std::endl;
    }catch (...) {
        std::cerr << "An exception occurred!" << std::endl;
    }
}
