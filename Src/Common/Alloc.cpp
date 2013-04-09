#define SKIP_ALLOC
#include "Utils.h"
#include "Allocator.h"

#pragma warning( disable : 4290 )

#ifdef _DEBUG

const char *del_FILE;
unsigned long del_LINE;

void *_Malloc(size_t size, const char* file_name, unsigned int line_num)
{
	return Allocator::Malloc(size, file_name, line_num);
}

void *_Realloc(void *block, size_t size, const char* file_name, unsigned int line_num)
{
	return Allocator::Realloc(block, size, file_name, line_num);
}

void *_Calloc(size_t n, size_t size, const char* file_name, unsigned int line_num)
{
	return Allocator::Calloc(n, size, file_name, line_num);
}

void _Free(void *block, const char* file_name, unsigned int line_num)
{
	Allocator::Free(block, file_name, line_num);
}


void* operator new (size_t size) throw (std::bad_alloc)
{
	void* ptr = Allocator::Malloc(size, "unknown", 0);

	if (ptr == NULL)
		throw std::bad_alloc();

	return ptr;
}

void* operator new[] (size_t size) throw (std::bad_alloc)
{
	void* ptr = Allocator::Malloc(size, "unknown", 0);

	if (ptr == NULL)
		throw std::bad_alloc();

	return ptr;
}

void* operator new (size_t size, const char* file_name, unsigned int line_num) throw (std::bad_alloc)
{
	void* ptr = Allocator::Malloc(size, file_name, line_num);

	if (ptr == NULL)
		throw std::bad_alloc();

	return ptr;
}

void* operator new[] (size_t size, const char* file_name, unsigned int line_num) throw (std::bad_alloc)
{
	void* ptr = Allocator::Malloc(size, file_name, line_num);

	if (ptr == NULL)
		throw std::bad_alloc();

	return ptr;
}

void operator delete (void* ptr, const char* file_name, unsigned int line_num) throw ()
{
	Allocator::Free(ptr, file_name, line_num);
}

void operator delete[] (void *ptr, const char* file_name, unsigned int line_num) throw ()
{
	Allocator::Free(ptr, file_name, line_num);
}

void operator delete (void* ptr) throw ()
{
	Allocator::Free(ptr, del_FILE, del_LINE);
	del_FILE = NULL;
	del_LINE = 0;
}

void operator delete[] (void *ptr) throw ()
{
	Allocator::Free(ptr, del_FILE, del_LINE);
	del_FILE = NULL;
	del_LINE = 0;
}

#endif

