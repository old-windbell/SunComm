#pragma once

#include <cstdint>
#include <string>

typedef signed char        int8;
typedef short              int16;
typedef int                int32;
typedef long long          int64;
typedef unsigned char      uint8;
typedef unsigned short     uint16;
typedef unsigned int       uint32;
typedef unsigned long long uint64;

#ifdef UNICODE
typedef std::wstring dstring;
#define _UC(s) Ls
#else
typedef std::string dstring;
#define _UC(s) s
#endif