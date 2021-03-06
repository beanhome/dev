#ifndef __ALLOC_H__
#define __ALLOC_H__

#ifndef SKIP_ALLOC

#if defined(_DEBUG) && defined(TRACK_MEMLEAK)

#include <exception>

#pragma warning( disable : 4290 )
void* operator new (size_t size);
void* operator new[] (size_t size);
//void* operator new (size_t size, const char* file_name, unsigned int line_num) throw (std::bad_alloc);
//void* operator new[] (size_t size, const char* file_name, unsigned int line_num) throw (std::bad_alloc);
void operator delete (void *ptr) throw ();
void operator delete[] (void *ptr) throw ();
//void operator delete (void *ptr, const char* file_name, unsigned int line_num) throw ();
//void operator delete[] (void *ptr, const char* file_name, unsigned int line_num) throw ();

extern const char *del_FILE;
extern unsigned long del_LINE;

void *_Malloc(size_t size, const char* file_name, unsigned int line_num);
void *_Realloc(void *block, size_t size, const char* file_name, unsigned int line_num);
void *_Calloc(size_t n, size_t size, const char* file_name, unsigned int line_num);
void _Free(void *block, const char* file_name, unsigned int line_num);

#define malloc(size) _Malloc(size, __FILE__, __LINE__)
#define realloc(ptr,new_size) _Realloc(ptr, new_size, __FILE__, __LINE__)
#define calloc(n,size) _Calloc(n, size, __FILE__, __LINE__)
#define free(ptr) _Free(ptr, __FILE__, __LINE__)

int SetAllocContext(const char* file, unsigned long line);

#define new SetAllocContext(__FILE__, __LINE__)?0:new
#define delete if (SetAllocContext(__FILE__,__LINE__));else delete

#endif
#endif

#endif
