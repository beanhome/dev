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

#if 0
template <class T>
class MyAlloc
{
public:
	// type definitions
	typedef T        value_type;
	typedef T*       pointer;
	typedef const T* const_pointer;
	typedef T&       reference;
	typedef const T& const_reference;
	typedef std::size_t    size_type;
	typedef std::ptrdiff_t difference_type;

	// rebind allocator to type U
	template <class U>
	struct rebind
	{
		typedef MyAlloc<U> other;
	};

	// return address of values
	pointer address (reference value) const					{ return &value; }
	const_pointer address (const_reference value) const		{ return &value; }

	/* constructors and destructor
	* - nothing to do because the allocator has no state
	*/
	MyAlloc() throw()
	{ }

	MyAlloc(const MyAlloc&) throw()
	{ }

	template <class U>
	MyAlloc (const MyAlloc<U>&) throw()
	{ }

	~MyAlloc() throw()
	{ }

#ifdef max
#undef max
#endif

	// return maximum number of elements that can be allocated
	size_type max_size () const throw()
	{
		return std::numeric_limits<std::size_t>::max() / sizeof(T);
	}

	// allocate but don't initialize num elements of type T
	pointer allocate (size_type num, const void* = 0)
	{
		return Allocator::Malloc(num * sizeof(T), __FILE__, __LINE__);
	}

	// initialize elements of allocated storage p with value value
	void construct (pointer p, const T& value)
	{
		Allocator::Realloc(p, sizeof(T), __FILE__, __LINE__);
		*p = value;
	}

	// destroy elements of initialized storage p
	void destroy (pointer p)
	{
		// destroy objects by calling their destructor
		p->~T();
	}

	// deallocate storage p of deleted elements
	void deallocate (pointer p, size_type num)
	{
		return Allocator::Free(p, __FILE__, __LINE__);
	}
};

// return that all specializations of this allocator are interchangeable
template <class T1, class T2>
bool operator== (const MyAlloc<T1>&, const MyAlloc<T2>&) throw()
{
	return true;
}
template <class T1, class T2> 
bool operator!= (const MyAlloc<T1>&, const MyAlloc<T2>&) throw()
{
	return false;
}
#endif

#endif
