#include "string_converter.h"

#include <string>
#include <winnt.h>
#include <WinNls.h>
#include <Windows.h>

namespace string_converter {

    std::string WideCharToString(const WCHAR* wstr) {
        if (!wstr) {
            return "";
        }

        int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, nullptr, 0, nullptr, nullptr);
        std::string str(size_needed, 0);
        WideCharToMultiByte(CP_UTF8, 0, wstr, -1, &str[0], size_needed, nullptr, nullptr);

        if (!str.empty() && str.back() == '\0') {
            str.pop_back();
        }
        return str;
    }

}