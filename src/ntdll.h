#pragma once

#include "domain.h"

#include <Windows.h>
#include <string_view>
#include <string>

namespace ntdll {

#define STATUS_FLOAT_MULTIPLE_FAULTS     0xC0000094
#define STATUS_ASSERTION_FAILURE         0xC0000420
#define STATUS_SYSTEM_PROCESS_TERMINATED 0xC000021A  
#define STATUS_DATA_CORRUPTION_ERROR     0xC00002C4 

#define SE_SHUTDOWN_PRIVILEGE            0x13
#define SE_DEBUG_PRIVILEGE               0x14
#define SE_TCB_PRIVILEGE                 0x17

#define STATUS_PRIVILEGE_NOT_HELD        0xC0000060

    using namespace std::literals;

    class NtDll {
    public:
        NtDll();
        NTSTATUS RtlAdjustPrivilege(ULONG privilege,
            BOOLEAN enable,
            BOOLEAN client,
            PBOOLEAN was_enabled);

        NTSTATUS NtRaiseHardError(NTSTATUS error_status,
            ULONG numbers_of_parameters, 
            ULONG parameter_mask,
            PULONG_PTR parameter,
            ULONG valid_response_options,
            PULONG response);

    private:
        HMODULE ntdll_{ 0 };
        domain::pRtlAdjustPrivilege RtlAdjustPrivilege_{ 0 };
        domain::pNtRaiseHardError NtRaiseHardError_{ 0 };

        void LoadRtlAdjustPrivelege();
        void LoadNtRaiseHardError();
    };

}