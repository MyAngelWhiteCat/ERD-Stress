#pragma once

#include "ntdll.h"

namespace maltech {

    class BSODThrower {
    public:
        void TriggerHardError();

    private:
        ntdll::NtDll ntdll_;

    };
}