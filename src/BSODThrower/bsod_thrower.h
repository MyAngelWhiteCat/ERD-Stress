#pragma once

#include "../MalwareTechniques/ntdll.h"

namespace maltech {

    namespace bsod {

#define STATUS_SYSTEM_PROCESS_TERMINATED 0xC000021A  
#define STATUS_DATA_CORRUPTION_ERROR     0xC00002C4 

        using namespace std::literals;

        class BSODThrower {
        public:
            BSODThrower(ntdll::NtDll& ntdll);

            void TriggerHardError();

        private:
            ntdll::NtDll& ntdll_;

        };

    }

}