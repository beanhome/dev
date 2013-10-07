#ifndef __ALLOCATOR_H__
#define __ALLOCATOR_H__

#define SKIP_ALLOC
#include "Utils.h"
#include "Alloc.h"

#define  MAGIC 0xA5A5A5A5

struct BlockNode
{
	byte* pBlock;
	BlockNode* pPrev;
	BlockNode* pNext;
};


class Header
{
	friend class Allocator;

public:
	Header();
	~Header();

	void Init(size_t size, const char* file_name, unsigned int line_num);
	bool Check() const;
	void Print() const;

	int ComputeCheckSum() const;
	bool CheckSum() const;

private:
	size_t m_iSize;
	const char* m_sFileName;
	int m_iLineNumber;

	BlockNode* m_pBlockNode;

	const void* m_pAddress;

	int m_iCkeckSum;
};

class Footer
{
	friend class Allocator;

public:
	Footer();
	~Footer();

	void Init(size_t size, const char* file_name, unsigned int line_num);
	bool Check() const;

private:
	int m_iMagicNumber;
};


class Allocator
{
	private:
		Allocator();
		~Allocator();

		void *_Malloc(size_t size, const char* file_name, unsigned int line_num);
		void *_Realloc(void *block, size_t size, const char* file_name, unsigned int line_num);
		void *_Calloc(size_t nitems, size_t size, const char* file_name, unsigned int line_num);
		void _Free(void *block, const char* file_name, unsigned int line_num);

		bool _Check() const;
		void _Print() const;

		void AddBlock(byte* pBlock);
		void RemBlock(byte* pBlock);

	public:
		static void *Malloc(size_t size, const char* file_name, unsigned int line_num) { return s_oAllocator._Malloc(size, file_name, line_num); }
		static void *Realloc(void *block, size_t size, const char* file_name, unsigned int line_num) { return s_oAllocator._Realloc(block, size, file_name, line_num); }
		static void *Calloc(size_t nitems, size_t size, const char* file_name, unsigned int line_num) { return s_oAllocator._Calloc(nitems, size, file_name, line_num); }
		static void Free(void *block, const char* file_name, unsigned int line_num) { s_oAllocator._Free(block, file_name, line_num); }
		
		static bool Check() { return s_oAllocator._Check(); }
		static bool IsEmpty() { return (s_oAllocator.m_pBlocks == NULL); }
		static void Print() { s_oAllocator._Print(); }

	private:
		BlockNode* m_pBlocks;

		static Allocator s_oAllocator;
};


#endif
