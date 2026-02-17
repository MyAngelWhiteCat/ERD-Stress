#pragma once

#include "../MalwareTechniques/ntdll.h"

#include <Windows.h>

#include <string_view>

namespace maltech {

    namespace ransom {

        using namespace std::literals;

        class RansomwareSimulator {
        public:
            RansomwareSimulator(ntdll::NtDll& ntdll);

            void StartEncryptingSimulation();

        private:
            ntdll::NtDll& ntdll_;

            void PrintCatalogue(std::string_view path);
        };

    }

}