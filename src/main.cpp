#include "MalwareVaccine/application.h"
#include "Logger/logger.h"

#include <Windows.h>

#include <exception>
#include <iostream>


int main() {
    logging::Logger logger;
    logger.Init();
    try {
        malvac::application::Application app;
        app.EscalatePrivilegesToDebug();
        
        while (true) {
            Sleep(1000);
        }
        //app.EmulateRansomware();
        //app.ThrowBSOD();

    }
    catch (const std::exception& e) {
        std::cout << "EDR stress test error: " << e.what() << std::endl;
    }
}