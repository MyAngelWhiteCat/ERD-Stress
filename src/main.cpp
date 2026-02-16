#include "MalwareVaccine/application.h"

#include <exception>
#include <iostream>


int main() {
    try {
        malvac::Application app;
    }
    catch (const std::exception& e) {
        std::cout << "EDR stress test error: " << e.what() << std::endl;
    }
}