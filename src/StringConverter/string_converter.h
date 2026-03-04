#pragma once

#include <string>
#include <Windows.h>


namespace string_convert {

    std::string WideCharToString(const WCHAR* wstr);

}