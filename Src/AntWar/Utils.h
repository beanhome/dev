#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#include <map>
#include <set>

#include <stdarg.h>

#include <iostream>

#ifdef _WIN32
#define MYFOPEN(p,f,o) fopen_s(&p,f,o)
#else
#define MYFOPEN(p,f,o) p = fopen(f,o)
#endif

#ifdef _DEBUG
#define MYDEBUG
#include <assert.h>
#endif

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint;
typedef unsigned long uint32;

typedef signed char sint8;
typedef signed short sint16;
typedef signed int sint;
typedef signed long sint32;


typedef wchar_t wchar;

using std::min;
using std::max;
using std::endl;
using std::string;
using std::vector;
using std::map;
using std::multimap;
using std::set;
using std::pair;
using std::cin;
using std::cout;

#ifdef _WIN32
#define USE_LOG
#endif

#ifdef MYDEBUG
#include <windows.h>
#include <winbase.h>
#include <assert.h>
extern bool  g_bVisualDebug;
extern FILE* g_MyLog;
//#define LOG(format, ...) { fprintf(g_MyLog, "[%3d] "##format, pw.GetTurnNumber(),  __VA_ARGS__); fflush(g_MyLog); }
#define LOG(format, ...) { if (!g_bVisualDebug) { fprintf(g_MyLog, format, __VA_ARGS__); fflush(g_MyLog); } else { char str[512]; sprintf_s<512>(str, format, __VA_ARGS__); OutputDebugStringA(str); } }
#define CHECK(test, format, ...) { if (!(test)) { LOG(format, __VA_ARGS__); } }
#define CHECK_RETURN(test, format, ...) { if (!(test)) { LOG(format, __VA_ARGS__); return; } }
#define ASSERT(cond) assert(cond)
#else
#ifdef USE_LOG
extern FILE* g_MyLog;
#define LOG(format, ...) { fprintf(g_MyLog, format, __VA_ARGS__); fflush(g_MyLog); }
#else
#define LOG(format, ...)
#endif
#define CHECK(test, format, ...) { }
#define CHECK_RETURN(test, format, ...) { if (!(test)) { return; } }
#define ASSERT(cond)
#endif

#endif
