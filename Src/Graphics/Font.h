#ifndef __FONT_H__
#define __FONT_H__

#include "Utils.h"
#include "Resource.h"

class Font : public Resource
{
	public:
		Font(GEngine* pGEngine, uint16 size);
		~Font();

	public:
		uint16 m_iSize;
};


#endif // __FONT_H__

