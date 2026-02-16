#include "bsod_thrower.h"
#include "../MalwareTechniques/ntdll.h"
#include "../Logger/logger.h"

#include <Windows.h>

#include <iostream>

namespace maltech {

    namespace bsod {

        BSODThrower::BSODThrower(ntdll::NtDll& ntdll)
            : ntdll_(ntdll)
        {
        }

        void BSODThrower::TriggerHardError() {
            LOG_CRITICAL("WARNING!!!");
            LOG_CRITICAL("This feature will send a FATAL system error!!!");
            LOG_CRITICAL("This will HARD REBOOT your operating system!!!");
            LOG_CRITICAL("All unsaved data will be lost!!!");
            LOG_CRITICAL("PLEASE use it ONLY on Virtual Machine for testing you EDR or AV system");
            LOG_INFO("Type OK for coninue");
            LOG_INFO("Type whatever else for distard");
            LOG_INFO("Waiting for input: ");

            std::string user_input;
            std::cin >> user_input;
            LOG_DEBUG("User input: "s.append(user_input));
            if (user_input != "OK") {
                std::cout << "\nCanceled" << std::endl;
                return;
            }

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