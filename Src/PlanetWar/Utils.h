#ifndef __UTILS_H__
#define __UTILS_H__

//#include <stdio.h>
#include <vector>
using namespace std;

#ifdef _DEBUG
#define MYDEBUG
#endif


typedef signed char sint8;
typedef unsigned char uint8;
typedef signed short sint16;
typedef unsigned short uint16;
typedef signed int sint32;
typedef unsigned int uint32;
typedef sint32 sint;
typedef uint32 uint;

typedef std::string String;

#define MAX_TURN 50
#define LAST_TURN MAX_TURN-1


#ifdef MYDEBUG
#include <windows.h>
#include <winbase.h>
#include <assert.h>
extern bool  g_bVisualDebug;
extern FILE* g_MyLog;
//#define LOG(format, ...) { fprintf(g_MyLog, "[%3d] "##format, pw.GetTurnNumber(),  __VA_ARGS__); fflush(g_MyLog); }
#define LOG(format, ...) { if (!g_bVisualDebug) { fprintf(g_MyLog, format, __VA_ARGS__); fflush(g_MyLog); } else { char str[512]; sprintf_s<512>(str, format, __VA_ARGS__); OutputDebugString(str); } }
#define CHECK(test, format, ...) { if (!(test)) { LOG(format, __VA_ARGS__); } }
#define CHECK_RETURN(test, format, ...) { if (!(test)) { LOG(format, __VA_ARGS__); return; } }
#define ASSERT(cond) assert(cond)
#else
#define LOG(format, ...) { }
#define CHECK(test, format, ...) { }
#define CHECK_RETURN(test, format, ...) { if (!(test)) { return; } }
#define ASSERT(cond)
#endif



#endif // __UTILS_H__
