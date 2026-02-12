#include "domain.h"

#include <string>
#include <string_view>
#include <stdexcept>

#include <Windows.h>


namespace ntdll {

    namespace domain {

        HMODULE LoadModule(std::wstring_view module_name) {
            if (module_name.empty()) {
                return 0;
            }
            HMODULE hModule = GetModuleHandleW(module_name.data());
            if (!hModule) {
                throw std::runtime_error("Can't load " + domain::WideCharToString(module_name.data())
                    + ". error code:"s + std::to_string(GetLastError()));
            }
            return hModule;
        }

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

}
