#ifndef __FONT_H__
#define __FONT_H__

#include "Utils.h"
#include "Resource.h"

class FontResource : public Resource
{
	public:
		struct Desc
		{
			const char* path;
			uint16 size;
			Desc(const char* _path, uint16 _size) : path(_path), size(_size) {}
		};
		
		static uint32 ComputeCRC32(const Desc& oDesc);

	public:
		FontResource(GEngine* pGEngine, uint32 crc/*, const char* path, uint16 size*/);
		//FontResource(GEngine* pGEngine, uint32 crc, const Desc& oDesc);
		~FontResource();

		virtual uint16 GetSize() const = 0; /* { return m_iSize; }*/
		virtual uint16 GetLineSkip() const = 0; /* { return m_iSize; }*/

	public:
		//string			m_sPath;
		//uint16			m_iSize;
};


#endif // __FONT_H__

