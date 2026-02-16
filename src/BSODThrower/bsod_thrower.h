#pragma once

#include "../MalwareTechniques/ntdll.h"

namespace maltech {

    namespace bsod {

#define STATUS_FLOAT_MULTIPLE_FAULTS     0xC0000094
#define STATUS_ASSERTION_FAILURE         0xC0000420
#define STATUS_SYSTEM_PROCESS_TERMINATED 0xC000021A  
#define STATUS_DATA_CORRUPTION_ERROR     0xC00002C4 

        class BSODThrower {
        public:
            BSODThrower(ntdll::NtDll& ntdll);

            void TriggerHardError();

        private:
            ntdll::NtDll& ntdll_;

        };

    }

}