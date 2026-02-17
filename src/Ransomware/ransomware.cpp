#include "../Logger/logger.h"
#include "../MalwareTechniques/ntdll.h"
#include "ransomware.h"

#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>

#include <Windows.h>


namespace maltech {

    namespace ransom {

        RansomwareSimulator::RansomwareSimulator(ntdll::NtDll& ntdll)
            : ntdll_(ntdll)
        {
        }

        void RansomwareSimulator::StartEncryptingSimulation() {
            DWORD drivers = GetLogicalDrives();
            const int bits_in_byte = 8;
            const int dword_bits_size = sizeof(DWORD) * bits_in_byte;
            for (DWORD i = 0; i <= dword_bits_size; ++i) {
                DWORD bit_checker = 1;
                if ((bit_checker << (dword_bits_size - i)) & drivers) {
                    char disk = 'A' + (dword_bits_size - i);
                    std::string path;
                    path += disk;
                    path += ":\\*";
                    try {
                        PrintCatalogue(path);
                    }
                    catch (const std::exception& e) {
                        LOG_ERROR("Encrypting error: "s + e.what());
                    }
                }
            }
        }

        void RansomwareSimulator::PrintCatalogue(std::string_view path) {
            WIN32_FIND_DATA data{ 0 };
            HANDLE hDirEntry = FindFirstFileA(path.data(), &data);
            if (!hDirEntry || hDirEntry == INVALID_HANDLE_VALUE) {
                throw std::runtime_error("Can't open " 
                    + std::string(path)
                    + ". Error code: " 
                    + std::to_string(GetLastError()));
            }

            do {
                if (std::string(data.cFileName) == ".." 
                    || std::string(data.cFileName) == "."
                    || std::string(data.cFileName) == "Windows") {
                    continue;
                }
                LOG_INFO(std::string(path.substr(0, path.size() - 1)) + data.cFileName);
                if (data.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY) {
                    try {
                        PrintCatalogue(
                            std::string(path.substr(0, path.size() - 1))
                            + data.cFileName + "\\*");
                    }
                    catch (const std::exception& e) {
                        LOG_ERROR("Encrypting error: "s + e.what());
                    }
                }
            } while (FindNextFileA(hDirEntry, &data));
            FindClose(hDirEntry);
        }
        
    }

}