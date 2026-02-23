#include "MalwareVaccine/application.h"
#include "Logger/logger.h"

#include <Windows.h>

#include <exception>
#include <iostream>


int main() {
    logging::Logger logger;
    logger.Init();
    try {
        //bool res = malvac::application::EscalatePrivilegesToDebug();
        //std::string ress = res ? "success" : "Error";
        //LOG_INFO(ress);
        malvac::application::EmulateRansomware();
        while (true) {
            Sleep(1000);
        }
    }
    catch (const std::exception& e) {
        std::cout << "EDR stress test error: " << e.what() << std::endl;
    }
}