#ifndef __RESOURCE_H__
#define __RESOURCE_H__

#include "Utils.h"

class GEngine;

class Resource
{
	public:
		Resource(GEngine* pGEngine, uint32 crc);
		virtual ~Resource();

	private:
		GEngine* m_pGEngine;
};


#endif // __RESOURCE_H__

