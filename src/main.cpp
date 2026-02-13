#include "edr_stress.h"

#include <exception>
#include <iostream>


int main() {
    std::cout << "WARNING!!!\n"
        << "This programm will send a FATALL system error!!!\n"
        << "This will HARD REBOOT your operating system!!!\n"
        << "All unsaved data will be lost!!!\n"
        << "PLEASE use it ONLY on Virtual Machine for testing you ERD or AV system\n"
        << "Press Ctrl+c for discart\n"
        << "Type OK for coninue: ";
    std::string user_input;
    std::cin >> user_input;
    if (user_input != "OK") {
        std::cout << "\nCanceled" << std::endl;
        return 1;
    }
    try {
        attack::EDRStress edr_stress;
        edr_stress.TriggerHardError();
    }
    catch (const std::exception& e) {
        std::cout << "EDR stress test error: " << e.what() << std::endl;
    }
}