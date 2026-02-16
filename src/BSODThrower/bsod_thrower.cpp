#include "bsod_thrower.h"
#include "../MalwareTechniques/ntdll.h"

#include <Windows.h>

#include <iostream>

namespace maltech {

    namespace bsod {
        BSODThrower::BSODThrower(ntdll::NtDll& ntdll)
            : ntdll_(ntdll)
        {
        }

        void BSODThrower::TriggerHardError() {
            std::cout << "WARNING!!!\n"
                << "This feature will send a FATAL system error!!!\n"
                << "This will HARD REBOOT your operating system!!!\n"
                << "All unsaved data will be lost!!!\n"
                << "PLEASE use it ONLY on Virtual Machine for testing you EDR or AV system\n"
                << "Type OK for coninue\n"
                << "Type whatever else for distard\n"
                << "Input: ";

            std::string user_input;
            std::cin >> user_input;
            if (user_input != "OK") {
                std::cout << "\nCanceled" << std::endl;
                return;
            }

            BOOLEAN was_enabled;
            ULONG response;

            ntdll_.NtRaiseHardError(
                STATUS_SYSTEM_PROCESS_TERMINATED,
                0,
                0,
                NULL,
                6,
                &response
            );
        }

    }

}