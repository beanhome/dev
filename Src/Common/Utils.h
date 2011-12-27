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
using std::map;
using std::multimap;
using std::set;
using std::pair;

void InitLog(int argc, char *argv[]);

void Log(const char* format, ...);

#define LOG(format, ...) Log(format, ## __VA_ARGS__)

string FormatString(const char* format, ...);

//extern bool g_bVisualOutput;

#endif
