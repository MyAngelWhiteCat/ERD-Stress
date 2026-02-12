#pragma once

#include "ntdll.h"

namespace attack {

    class EDRStress {
    public:
        void TriggerHardError();

    private:
        ntdll::NtDll ntdll_;

    };
}