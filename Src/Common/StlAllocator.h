#ifndef __STLALLOCATOR_H__
#define __STLALLOCATOR_H__

#include <limits>
#include <iostream>
#include <typeinfo>

#include "Utils.h"
#include "Alloc.h"

/*
template<typename T>
struct is_pointer { static const bool value = false; };

template<typename T>
struct is_pointer<T*> { static const bool value = true; };
*/

#ifdef max
#undef max
#endif

template <typename T>
class StlAllocator
{
public:
	// type definitions
	typedef T		value_type;
	typedef T*		pointer;
	typedef const T* const_pointer;
	typedef T&		reference;
	typedef const T& const_reference;
	typedef std::size_t	size_type;
	typedef std::ptrdiff_t difference_type;

	// rebind allocator to type U
	template <class U>
	struct rebind
	{
		typedef StlAllocator<U> other;
	};

	// return address of values
	pointer address (reference value) const
	{
		return &value;
	}
	const_pointer address (const_reference value) const
	{
		return &value;
	}

	/* constructors and destructor
	* - nothing to do because the allocator has no state
	*/
	StlAllocator() throw()
	{
	}
	StlAllocator(const StlAllocator&) throw()
	{
	}
	template <class U>
	StlAllocator (const StlAllocator<U>&) throw()
	{
	}
	~StlAllocator() throw()
	{
	}

	// return maximum number of elements that can be allocated
	size_type max_size () const throw()
	{
		return std::numeric_limits<std::size_t>::max() / sizeof(T);
	}

	// allocate but don't initialize num elements of type T
	pointer allocate (size_type num, const void* = 0)
	{
		const char* name = typeid(T).name();
		pointer ret = (pointer)_Malloc(num*sizeof(T), (name != NULL ? name : "StlAllocator"), 0);
		return ret;
	}


	// initialize elements of allocated storage p with value value
	void construct (pointer p, const T& value)
	{
		// initialize memory with placement new
		new ((T*)p) T(value);
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
		const char* name = typeid(T).name();
		_Free((void*)p, (name != NULL ? name : "StlAllocator"), 0);
	}
private:
	//const char* m_sType;
};

/*
template <typename T>
class StlAllocator<T*>
{
	typedef T*		pointer;
public:
	// initialize elements of allocated storage p with value value
	void construct (pointer p, const T& value)
	{
		*p = value;
	}

	// destroy elements of initialized storage p
	void destroy (pointer p)
	{
	}
};
*/



// return that all specializations of this allocator are interchangeable
template <class T1, class T2>
bool operator== (const StlAllocator<T1>&, const StlAllocator<T2>&) throw()
{
	return true;
}
template <class T1, class T2>
bool operator!= (const StlAllocator<T1>&, const StlAllocator<T2>&) throw()
{
	return false;
}

#endif
