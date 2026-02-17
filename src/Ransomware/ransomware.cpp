#include "ransomware.h"
#include "../MalwareTechniques/ntdll.h"


namespace maltech {

    namespace ransom {

        Ransomware::Ransomware(ntdll::NtDll& ntdll)
            : ntdll_(ntdll)
        {
        }

        void Ransomware::StartEncrypting() {

        }

    }

}