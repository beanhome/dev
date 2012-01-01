#ifndef __FONT_H__
#define __FONT_H__

#include "Utils.h"
#include "Resource.h"

class FontResource : public Resource
{
	public:
		FontResource(GEngine* pGEngine, uint32 crc, const char* path, uint16 size);
		~FontResource();

	public:
		string			m_sPath;
		uint16			m_iSize;
};


#endif // __FONT_H__

