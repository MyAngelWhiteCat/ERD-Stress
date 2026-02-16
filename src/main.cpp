#include "MalwareVaccine/application.h"
#include "Logger/logger.h"

#include <exception>
#include <iostream>


int main() {
    logging::Logger logger;
    logger.Init();
    try {
        malvac::application::Application app;
        app.AsyncThrowBSOD();
    }
    catch (const std::exception& e) {
        std::cout << "EDR stress test error: " << e.what() << std::endl;
    }
}