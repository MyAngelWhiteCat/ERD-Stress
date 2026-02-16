#pragma once

#include "../MalwareTechniques/ntdll.h"

namespace maltech {

    namespace ransom {

        class Ransomware {
        public:
            Ransomware(ntdll::NtDll& ntdll);

        private:
            ntdll::NtDll& ntdll_;
        };

    }

}