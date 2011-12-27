#ifndef __FONT_SDL_H__
#define __FONT_SDL_H__

#include "Utils.h"
#include "Font.h"

typedef struct _TTF_Font TTF_Font;

class Font_SDL : public Font
{
	public:
		Font_SDL(GEngine* pGEngine, const char* path, uint16 size);
		~Font_SDL();

	public:
		TTF_Font* m_pFont;
};


#endif // __FONT_SDL_H__

