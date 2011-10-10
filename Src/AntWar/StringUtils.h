#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <map>
#include <set>

#include <wtypes.h>
#include <basetsd.h>
#include <winbase.h>

#include <assert.h>
#include <iostream>


#ifdef _DEBUG
#define MYDEBUG
#endif

typedef unsigned int uint;
typedef wchar_t wchar;

using std::string;
using std::vector;
using std::map;
using std::multimap;
using std::set;
using std::pair;
using std::cin;
using std::cout;


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
#define LOG(format, ...) { }
#define CHECK(test, format, ...) { }
#define CHECK_RETURN(test, format, ...) { if (!(test)) { return; } }
#define ASSERT(cond)
#endif

string FormatString(const char* format, ...);
void Tokenize(const string& s, const string& delimiters, vector<string>& tokens);
vector<string> Tokenize(const string& s, const string& delimiters = string(" "));


extern bool g_bVisualDebug;

#endif
