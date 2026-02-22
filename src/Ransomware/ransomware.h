#pragma once

#include "../MalwareTechniques/ntdll.h"
#include "../ThreadPool/thread_pool.h"

#include <Windows.h>

#include <string_view>
#include <memory>

namespace maltech {

    namespace ransom {

        using namespace std::literals;

        class RansomwareSimulator : public std::enable_shared_from_this<RansomwareSimulator>{
        public:
            RansomwareSimulator(ntdll::NtDll& ntdll);

            void StartEncryptingSimulation();

        private:
            ntdll::NtDll& ntdll_;
            ThreadPool thread_pool_;

            void PrintCatalogue(std::string_view path);
            void ImitateFileIncryption(std::string_view path);
        };

    }

}