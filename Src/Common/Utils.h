#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>

#ifdef _WIN32
#include <wtypes.h>
#include <basetsd.h>
#include <winbase.h>
#endif

#include <algorithm>
#include <string>
#include <vector>
#include <array>
#include <deque>
#include <map>
#include <set>
#include <list>

#undef min
#undef max

using std::string;
using std::array;
using std::vector;
using std::deque;
using std::map;
using std::multimap;
using std::set;
using std::multiset;
using std::pair;
using std::list;
using std::min;
using std::max;

typedef unsigned char byte;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint;
typedef unsigned long uint32;

typedef signed char sint8;
typedef signed short sint16;
typedef signed int sint;
typedef signed long sint32;

typedef wchar_t wchar;

#if defined(_DEBUG) && defined(TRACK_MEMLEAK)
#error prout
#include "Alloc.h"
#include "StlAllocator.h"
#define string std::basic_string<char, std::char_traits<char>, StlAllocator<char> >
//typedef std::basic_string<char, std::char_traits<char>, StlAllocator<char> > string;
#endif

void InitLog(int argc, char *argv[]);

void Log(const char* format, ...);

#define LOG(format, ...) Log(format, ## __VA_ARGS__)

#ifdef _DEBUG
#define CHECK(test, format, ...) { if (!(test)) { LOG(format, __VA_ARGS__); } }
#define CHECK_RETURN(test, format, ...) { if (!(test)) { LOG(format, __VA_ARGS__); return; } }
#define ASSERT(cond) assert(cond)
#define FASSERT(cond, format, ...) { if (!cond) { LOG(format, __VA_ARGS__); } assert(cond); }
#else
#define CHECK(test, format, ...) { if (!(test)) { } }
#define CHECK_RETURN(test, format, ...) { if (!(test)) { return; } }
#define ASSERT(cond)
#define FASSERT(cond, format, ...)
#endif

#ifdef _WIN32
#define strnicmp _strnicmp
#define snprintf sprintf_s
#define fread(b, s, c, f) fread_s(b, s, s, c, f)
#define fopen(p, m) myfopen(p, m)
FILE* myfopen(const char *p, const char *m);
#else
// none
#endif


string FormatString(const char* format, ...);

int Rand();
int Rand(int iMax);
int Rand(int iMin, int iMax);

template <typename T>
T Clamp(const T& x, const T& _min, const T& _max)
{
	return std::min<T>(std::max<T>(_min, x), _max);
}

float Lerp(float a, float b, float t);

#endif
