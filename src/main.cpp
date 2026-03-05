#include "MalwareVaccine/application.h"
#include "Logger/logger.h"

#include <Windows.h>

#include <exception>
#include <iostream>


int main() {
    logging::Logger logger;
    logger.Init();
    try {
        Sleep(5000);
        malvac::application::InstallStartupFolderPersistence();
        Sleep(10000); // For manual check. 
        // I dont wanna realize another getter of startup folder for assert here now.
        malvac::application::RemoveStartupFolderPersistence();
        while (true) {
            Sleep(1000);
        }
    }
    catch (const std::exception& e) {
        std::cout << "test error: " << e.what() << std::endl;
    }
}