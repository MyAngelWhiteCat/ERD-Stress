#pragma once

#include "../MalwareTechniques/ntdll.h"
#include "../ThreadPool/thread_pool.h"

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
            ThreadPool thread_pool_;

            void PrintCatalogue(std::string_view path);
        };

    }

}