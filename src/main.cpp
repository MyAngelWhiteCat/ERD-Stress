#include "MalwareVaccine/application.h"
#include "Logger/logger.h"

#include <Windows.h>

#include <exception>
#include <iostream>


int main() {
    logging::Logger logger;
    logger.Init();
    try {
        bool res = malvac::application::EscalatePrivilegesToTCB();
        std::string ress = res ? "success" : "Error";
        LOG_INFO(ress);

        int pause_sec = 5;
        while (pause_sec--) {
            Sleep(1000);
        }
    }
    catch (const std::exception& e) {
        std::cout << "EDR stress test error: " << e.what() << std::endl;
    }
}