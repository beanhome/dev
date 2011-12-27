#include "Font_SDL.h"
#include "SDL_ttf.h"

Font_SDL::Font_SDL(GEngine* pGEngine, const char* path, uint16 size)
	: Font(pGEngine, size)
	, m_pFont(NULL)
{
	m_pFont = TTF_OpenFont(path, m_iSize);
}

Font_SDL::~Font_SDL()
{
	TTF_CloseFont(m_pFont);
}
