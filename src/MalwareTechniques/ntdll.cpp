#include "ntdll.h"
#include "domain.h"

#include <Windows.h>

namespace ntdll {

    NtDll::NtDll()
    {
        ntdll_ = domain::LoadModule(domain::Names::NTDLL);
    }

    NTSTATUS NtDll::RtlAdjustPrivilege(ULONG privilege,
        BOOLEAN enable, BOOLEAN client, PBOOLEAN was_enabled)
    {
        LoadRtlAdjustPrivelege();
        return RtlAdjustPrivilege_(privilege, enable, client, was_enabled);
    }

    NTSTATUS NtDll::NtRaiseHardError(NTSTATUS error_status,
        ULONG numbers_of_parameters,
        ULONG parameter_mask,
        PULONG_PTR parameter,
        ULONG valid_response_options,
        PULONG response)
    {
        LoadNtRaiseHardError();
        return NtRaiseHardError_(error_status,
            numbers_of_parameters,
            parameter_mask,
            parameter,
            valid_response_options,
            response);
    }

    void NtDll::LoadRtlAdjustPrivelege() {
        if (RtlAdjustPrivilege_) return;
        RtlAdjustPrivilege_ = domain::LoadFunctionFromModule
            <domain::pRtlAdjustPrivilege>(ntdll_, domain::Names::ADJUST_PRIVILEGE);
    }

    void NtDll::LoadNtRaiseHardError() {
        if (NtRaiseHardError_) return;
        NtRaiseHardError_ = domain::LoadFunctionFromModule
            <domain::pNtRaiseHardError>(ntdll_, domain::Names::RAISE_HARD_ERROR);
    }

}