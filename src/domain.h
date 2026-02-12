#pragma once
#include <string>
#include <string_view>
#include <stdexcept>

#include <Windows.h>

namespace ntdll {

    namespace domain {

        using namespace std::literals;

        // names of functions from ntdll.dll for loading
        struct Names {
            Names() = delete;
            static constexpr std::wstring_view NTDLL = L"ntdll.dll"sv;
            static constexpr std::string_view ADJUST_PRIVILEGE = "RtlAdjustPrivilege"sv;
            static constexpr std::string_view RAISE_HARD_ERROR = "NtRaiseHardError"sv;
        };

        typedef NTSTATUS
        (NTAPI* pRtlAdjustPrivilege)
            (ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);

        typedef NTSTATUS
        (NTAPI* pNtRaiseHardError)
            (NTSTATUS, ULONG, ULONG, PULONG_PTR, ULONG, PULONG);

        HMODULE LoadModule(std::wstring_view module_name);

        template<typename Fn>
        Fn LoadFunctionFromModule(HMODULE hModule, std::string_view function_name) {
            Fn func = reinterpret_cast<Fn>(GetProcAddress(hModule, function_name.data()));
            if (!func) {
                throw std::runtime_error("Incorrect load func: " + std::string(function_name));
            }
            return func;
        }

        std::string WideCharToString(const WCHAR* wstr);

    }

}