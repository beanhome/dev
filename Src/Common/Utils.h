#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <deque>
#include <map>
#include <set>
#include <list>

#include <wtypes.h>
#include <basetsd.h>
#include <winbase.h>

#include <assert.h>

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint;
typedef unsigned long uint32;

typedef signed char sint8;
typedef signed short sint16;
typedef signed int sint;
typedef signed long sint32;


typedef wchar_t wchar;

using std::string;
using std::vector;
using std::deque;
using std::map;
using std::multimap;
using std::set;
using std::pair;
using std::list;

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



string FormatString(const char* format, ...);

int Rand();
int Rand(int iMax);
int Rand(int iMin, int iMax);

#endif
