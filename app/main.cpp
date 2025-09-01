#include <iostream>
#include "Application.hpp"
#include "exception/YahtzeeException.hpp"


int main(int argc,const char* argv[]) {
    try {
        Application::run(argv[0]);
    } catch (const YahtzeeException& e) {
    std::cerr << "Yahtzee" << std::endl;
    }catch (...) {
        std::cerr << "An exception occurred!" << std::endl;
    }
}
