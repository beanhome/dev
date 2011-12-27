#ifndef __GENGINE_H__
#define __GENGINE_H__

#include "Utils.h"
#include "CanvasBase.h"
#include "Font.h"

typedef map<uint, Font*> FontMap;
typedef pair<uint, Font*> FontPair;

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

		virtual Font*					CreateFontResource(const char* path, uint16 size) = 0;
		virtual ImageResource*			CreateImageResource(const char* path) = 0;

		bool							AddResource(Resource* pRes);
		bool							RemResource(Resource* pRes);

	protected:
		const Font* const				GetFont(const char* path, uint16 size);

	protected:
		uint16							m_iDepth;
		InputEvent*						m_pInputEvent;

	private:
		set<Resource*>					m_aResource;
		FontMap							m_aFontMap;
};



#endif // __GENGINE_H__

