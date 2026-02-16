#pragma once

#include "../MalwareTechniques/ntdll.h"

namespace maltech {

    namespace bsod {

        class BSODThrower {
        public:
            void TriggerHardError();

        private:
            ntdll::NtDll ntdll_;

        };

    }

}