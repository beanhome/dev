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

typedef unsigned int uint;
typedef wchar_t wchar;

using std::string;
using std::vector;
using std::map;
using std::multimap;
using std::set;
using std::pair;

void Log(const char* format, ...);

string FormatString(const char* format, ...);

extern bool g_bVisualOutput;

#endif
