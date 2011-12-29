#ifndef __GENGINE_H__
#define __GENGINE_H__

#include "Utils.h"
#include "CanvasBase.h"
#include "Font.h"

typedef map<uint32, Resource*> ResourceMap;
typedef pair<uint32, Resource*> ResourcePair;

class InputEvent;

class GEngine : public CanvasBase
{
	public:
		GEngine(uint16 width, uint16 height, uint16 depth);
		~GEngine();

		GEngine*						GetGEngine() { return this; }

		uint16							GetWidth() { return m_iWidth; }
		uint16							GetHeight() { return m_iHeight; }

		virtual void					Clear() = 0;
		virtual void					Flip() = 0;

		virtual void					PurgeResource();

		virtual const InputEvent&		PollEvent() = 0;
		virtual const InputEvent&		WaitEvent() = 0;

		Font* const						GetFontResource(const char* path, uint16 size);
		ImageResource* const			GetImageResource(const char* path);

		bool							AddResource(uint32 crc, Resource* pRes);
		bool							RemResource(uint32 crc);
		bool							RemResource(Resource* pRes);

	protected:
		const Font* const				GetFont(const char* path, uint16 size);

		virtual Font*					CreateFontResource(uint32 crc, const char* path, uint16 size) = 0;
		virtual ImageResource*			CreateImageResource(uint32 crc, const char* path) = 0;

		uint32							ComputeFontCRC32(const char* path, uint16 size);
		uint32							ComputeImageCRC32(const char* path);

	protected:
		uint16							m_iDepth;
		InputEvent*						m_pInputEvent;

	private:
		ResourceMap						m_aResources;
};



#endif // __GENGINE_H__

