#ifndef __IMAGERESOURCE_H__
#define __IMAGERESOURCE_H__

#include "Utils.h"
#include "Resource.h"

class ImageResource : public Resource
{
	public:
		struct Desc
		{
			const char* path;
			Desc(const char* _path) : path(_path) {}
		};

		static uint32 ComputeCRC32(const Desc& oDesc);

	public:
		ImageResource(GEngine* pGEngine, uint32 crc, const char* path);
		ImageResource(GEngine* pGEngine, uint32 crc, const Desc& oDesc);
		~ImageResource();

		uint16 GetWidth() const { return m_iWidth; }
		uint16 GetHeight() const { return m_iHeight; }

	protected:
		string			m_sPath;
		uint16			m_iWidth;
		uint16			m_iHeight;
};


#endif // __IMAGERESOURCE_H__

