#include "Utils.h"
#include "GEngine_SDL.h"
#include "InputEvent_SDL.h"

#include "SDL.h"
#include "SDL_video.h"
#include "SDL_Draw.h"
#include "SDL_ttf.h"
#include "SDL_rotozoom.h"
#include "Font_SDL.h"
#include "ImageResource_SDL.h"


GEngine_SDL::GEngine_SDL(uint16 width, uint16 height, uint16 depth)
	: GEngine(width, height, depth)
{
	Init();

	m_pInputEvent = new InputEvent_SDL;
}

GEngine_SDL::~GEngine_SDL()
{
	delete m_pInputEvent;

	Close();
}

uint GEngine_SDL::Init()
{
	LOG("Initializing SDL.\n");
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{ 
		LOG("Could not initialize SDL: %s.\n", SDL_GetError());
		return 1;
	}

	LOG("SDL Set Video Mode.\n");
	m_pScreen = SDL_SetVideoMode(m_iWidth, m_iHeight, m_iDepth, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_ANYFORMAT);
	if (m_pScreen == NULL)
	{
		LOG("Couldn't set %dx%dx%d video mode: %s\n", m_iWidth, m_iHeight, m_iDepth, SDL_GetError());
		return 1;
	}

	//SDL_EnableKeyRepeat(500, 10);

	LOG("Initializing SDL TTF.\n");
	if(TTF_Init() == -1)
	{
		LOG("Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
		return 1;
	}
	return 0;
}

uint GEngine_SDL::Close()
{
	LOG("Quiting SDL.\n");

	PurgeResource();

	TTF_Quit();

	SDL_Quit();

	return 0;
}

void GEngine_SDL::Clear()
{
	SDL_FillRect(m_pScreen, NULL, SDL_MapRGB(m_pScreen->format, 128, 128, 128));
}

void GEngine_SDL::Flip()
{
	SDL_Flip(m_pScreen);
}

Font* GEngine_SDL::CreateFontResource(const char* path, uint16 size)
{
	Font* pFont = new Font_SDL(this, path, size);
	return pFont;
}

ImageResource* GEngine_SDL::CreateImageResource(const char* path)
{
	ImageResource* pImg = new ImageResource_SDL(this, path);
	return pImg;
}

void GEngine_SDL::DrawImage(const ImageResource& _image, sint16 x, sint16 y) const
{
	SDL_Surface* image = ((const ImageResource_SDL&)_image).m_pSurface;

	if (image == NULL)
		return;

	if (image->format->palette && m_pScreen->format->palette)
		SDL_SetColors(m_pScreen, image->format->palette->colors, 0, image->format->palette->ncolors);

	SDL_Rect oLoc;
	oLoc.x = x - (sint16)image->w / 2;
	oLoc.y = y - (sint16)image->h / 2;
	oLoc.w = (sint16)image->w;
	oLoc.h = (sint16)image->h;

	/* Blit onto the screen surface */
	if(SDL_BlitSurface(image, NULL, m_pScreen, &oLoc) < 0)
	{
		LOG("BlitSurface error: %s\n", SDL_GetError());
	}
}


void GEngine_SDL::DrawImage(const ImageResource& _image, sint16 x, sint16 y, float fAngle, float fZoom) const
{
	SDL_Surface* image = ((const ImageResource_SDL&)_image).m_pSurface;

	if (image == NULL)
		return;

    if (image->format->palette && m_pScreen->format->palette)
		SDL_SetColors(m_pScreen, image->format->palette->colors, 0, image->format->palette->ncolors);

	SDL_Surface* pOutput = rotozoomSurface(image, fAngle, fZoom, 1);
	if (pOutput == NULL)
		return;

	SDL_Rect oLoc;
	oLoc.x = x - (sint16)pOutput->w / 2;
	oLoc.y = y - (sint16)pOutput->h / 2;
	oLoc.w = (sint16)pOutput->w;
	oLoc.h = (sint16)pOutput->h;

    /* Blit onto the screen surface */
    if(SDL_BlitSurface(pOutput, NULL, m_pScreen, &oLoc) < 0)
	{
        LOG("BlitSurface error: %s\n", SDL_GetError());
	}

	SDL_FreeSurface(pOutput);
}

void GEngine_SDL::SetPixel(sint16 x, sint16 y, uint8 r, uint8 g, uint8 b) const
{
	Draw_Pixel(m_pScreen, x, y, SDL_MapRGB(m_pScreen->format, r, g, b));
}

void GEngine_SDL::DrawRect(sint16 x, sint16 y, sint16 width, sint16 height, uint8 r, uint8 g, uint8 b) const
{
	Draw_Rect(m_pScreen, x, y, width, height, SDL_MapRGB(m_pScreen->format, r, g, b));
}

void GEngine_SDL::DrawFillRect(sint16 x, sint16 y, sint16 width, sint16 height, uint8 _r, uint8 _g, uint8 _b) const
{
	Draw_FillRect(m_pScreen, x, y, width, height, SDL_MapRGB(m_pScreen->format, _r, _g, _b));
}

void GEngine_SDL::DrawCircle(sint16 x, sint16 y, sint16 radius, uint8 r, uint8 g, uint8 b) const
{
	Draw_Circle(m_pScreen, x, y, radius, SDL_MapRGB(m_pScreen->format, r, g, b));
}

void GEngine_SDL::DrawFillCircle(sint16 x, sint16 y, sint16 radius, uint8 r, uint8 g, uint8 b) const
{
	Draw_FillCircle(m_pScreen, x, y, radius, SDL_MapRGB(m_pScreen->format, r, g, b));
}

void GEngine_SDL::DrawLine(sint16 x1, sint16 y1, sint16 x2, sint16 y2, uint8 r, uint8 g, uint8 b) const
{
	Draw_Line(m_pScreen, x1, y1, x2, y2, SDL_MapRGB(m_pScreen->format, r, g, b));
}

void GEngine_SDL::PrintArgs(sint16 x, sint16 y, uint size, ETextAlign eAlign, uint8 r, uint8 g, uint8 b, const char* format, va_list oArgs)
{
	Font_SDL* pFont = (Font_SDL*)GetFont(FONT_PATH, size);

	int ln = _vscprintf(format, oArgs) + 1;
	char* str = new char[ln];
	vsprintf_s(str, ln, format, oArgs);

	SDL_Surface* texte = NULL;
	SDL_Color color = { 0, 0, 0 };
	color.r = r;
	color.g = g;
	color.b = b;
	texte = TTF_RenderText_Solid(pFont->m_pFont, str, color);
	delete [] str;
	if (texte == NULL)
		return;

	uint16 iWidth = (uint16)texte->w;
	uint16 iHeight = (uint16)texte->h;

	SDL_Rect position;
	position.x = x;
	position.y = y;

	switch (eAlign)
	{
	case LeftTop:
	case LeftCenter:
	case LeftBottom:
		position.x = x;
		break;

	case CenterTop:
	case Center:
	case CenterBottom:
		position.x = x - iWidth / 2;	
		break;

	case RightTop:
	case RightCenter:
	case RightBottom:
		position.x = x - iWidth;		
		break;
	}

	switch (eAlign)
	{
	case LeftTop:
	case CenterTop:
	case RightTop:
		position.y = y;
		break;

	case LeftCenter:
	case Center:
	case RightCenter:
		position.y = y - iHeight / 2;
		break;

	case LeftBottom:
	case CenterBottom:
	case RightBottom:
		position.y = y - iHeight;
		break;
	}

	SDL_BlitSurface(texte, NULL, m_pScreen, &position); 

	SDL_FreeSurface(texte);
}



const InputEvent& GEngine_SDL::PollEvent()
{
	SDL_PollEvent(((InputEvent_SDL*)m_pInputEvent)->GetSDLEvent());

	//m_pInputEvent->GetMouseMove(m_iMouseX, m_iMouseY);

	return *m_pInputEvent;
}

const InputEvent& GEngine_SDL::WaitEvent()
{
	SDL_WaitEvent(((InputEvent_SDL*)m_pInputEvent)->GetSDLEvent());
	return *m_pInputEvent;
}
