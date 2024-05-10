#pragma once

#include <string>

#ifdef UNICODE
typedef std::wstring STRING;
#else
typedef std::string STRING;
#endif