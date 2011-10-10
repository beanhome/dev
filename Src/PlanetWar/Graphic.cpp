#include "Utils.h"

#include "Graphic.h"

#include "SDL.h"
#include "SDL_video.h"
#include "SDL_Draw.h"
#include "SDL_ttf.h"
#include "SDL_rotozoom.h"

GraphicEngine::GraphicEngine(uint16 width, uint16 height, uint16 depth)
	: m_iWidth(width)
	, m_iHeight(height)
	, m_iDepth(depth)
{

}

GraphicEngine::~GraphicEngine()
{

}

uint GraphicEngine::Init()
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

uint GraphicEngine::Close()
{
	LOG("Quiting SDL.\n");

	for (FontMap::iterator it = m_aFontMap.begin() ; it != m_aFontMap.end() ; ++it)
		TTF_CloseFont(it->second);

	TTF_Quit();

	SDL_Quit();

	return 0;
}

void GraphicEngine::Clear()
{
	SDL_FillRect(m_pScreen, NULL, SDL_MapRGB(m_pScreen->format, 128, 128, 128));
}

void GraphicEngine::Flip()
{
	SDL_Flip(m_pScreen);
}

void GraphicEngine::DrawImage(GraphicImage* image, sint16 x, sint16 y, float fAngle, float fZoom) const
{
	if (image == NULL)
		return;
	/*
     * Palettized screen modes will have a default palette (a standard
     * 8*8*4 colour cube), but if the image is palettized as well we can
     * use that palette for a nicer colour matching
     */
    if (image->format->palette && m_pScreen->format->palette)
	{
		SDL_SetColors(m_pScreen, image->format->palette->colors, 0, image->format->palette->ncolors);
    }

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

void GraphicEngine::SetPixel(sint16 x, sint16 y, uint8 r, uint8 g, uint8 b) const
{
	Draw_Pixel(m_pScreen, x, y, SDL_MapRGB(m_pScreen->format, r, g, b));
}


void GraphicEngine::DrawCircle(sint16 x, sint16 y, sint16 radius, uint8 r, uint8 g, uint8 b) const
{
	Draw_Circle(m_pScreen, x, y, radius, SDL_MapRGB(m_pScreen->format, r, g, b));

}

void GraphicEngine::DrawFillCircle(sint16 x, sint16 y, sint16 radius, uint8 r, uint8 g, uint8 b) const
{
	Draw_FillCircle(m_pScreen, x, y, radius, SDL_MapRGB(m_pScreen->format, r, g, b));

}

void GraphicEngine::DrawLine(sint16 x1, sint16 y1, sint16 x2, sint16 y2, uint8 r, uint8 g, uint8 b) const
{
	Draw_Line(m_pScreen, x1, y1, x2, y2, SDL_MapRGB(m_pScreen->format, r, g, b));

}

void GraphicEngine::Print(sint16 x, sint16 y, uint size, ETextAlign eAlign, uint8 r, uint8 g, uint8 b, const char* format, va_list oArgs)
{
	GraphicFont* pFont = NULL;
	FontMap::iterator iter = m_aFontMap.find(size);
	if (iter == m_aFontMap.end())
	{
		pFont = TTF_OpenFont(FONT_PATH, size);
		m_aFontMap.insert(pair<uint, GraphicFont*>(size, pFont));
	}
	else
	{
		pFont = iter->second;
	}

	int ln = _vscprintf(format, oArgs) + 1;
	char* str = new char[ln];
	vsprintf_s(str, ln, format, oArgs);

	SDL_Surface* texte = NULL;
	SDL_Color color = { 0, 0, 0 };
	color.r = r;
	color.g = g;
	color.b = b;
	texte = TTF_RenderText_Solid(pFont, str, color);
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


void GraphicEngine::Print(sint16 x, sint16 y, uint size, ETextAlign eAlign, uint8 r, uint8 g, uint8 b, const char* format, ...)
{
	va_list oArgs;
	va_start(oArgs, format);
	Print(x, y, size, eAlign, r, g, b, format, oArgs);
	va_end(oArgs);
}


GraphicImage* GraphicEngine::LoadBMP(const char* pFileName) const
{
	SDL_Surface *image;

	/* Load the BMP file into a surface */
	image = SDL_LoadBMP(pFileName);
	if (image == NULL)
	{
		LOG("Couldn't load %s: %s\n", pFileName, SDL_GetError());
		return NULL;
	}

	SDL_SetColorKey(image, SDL_SRCCOLORKEY, SDL_MapRGB(image->format, 255, 255, 255));

	return image;
}

void GraphicEngine::FreeImage(GraphicImage* pImage) const
{
	SDL_FreeSurface(pImage);
}

GraphicImage* GraphicEngine::CopyImage(GraphicImage* pImage) const
{
	SDL_Surface* s = SDL_CreateRGBSurface(SDL_HWSURFACE, pImage->w, pImage->h, pImage->format->BitsPerPixel, pImage->format->Rmask, pImage->format->Gmask, pImage->format->Bmask, pImage->format->Amask);
	SDL_BlitSurface(pImage, NULL, s, NULL);
	return s;
}

const SDL_Event& GraphicEngine::PollEvent()
{
	SDL_PollEvent(&m_oSDLEvent);

	switch(m_oSDLEvent.type)
	{
		case SDL_MOUSEMOTION:
			{
				m_iMouseX = m_oSDLEvent.motion.x;
				m_iMouseY = m_oSDLEvent.motion.y;
				break;
			}
	}

	return m_oSDLEvent;
}

const SDL_Event& GraphicEngine::WaitEvent()
{
	SDL_WaitEvent(&m_oSDLEvent);
	return m_oSDLEvent;
}




GraphicFrame::GraphicFrame( GraphicEngine* ge, sint16 x, sint16 y, uint16 xl, uint16 yl )
	: m_pGraphicEngine(ge)
	, m_iPosX(x)
	, m_iPosY(y)
	, m_iWidth(xl)
	, m_iHeight(yl)
{

}

GraphicFrame::~GraphicFrame()
{

}

void GraphicFrame::DrawImage(GraphicImage* image, sint16 x, sint16 y, float fAngle, float fZoom) const
{
	ConvertFrameToGraphic(x, y);
	m_pGraphicEngine->DrawImage(image, x, y, fAngle, fZoom);
}

void GraphicFrame::DrawCircle(sint16 x, sint16 y, sint16 radius, uint8 r, uint8 g, uint8 b) const
{
	ConvertFrameToGraphic(x, y);
	m_pGraphicEngine->DrawCircle(x, y, radius, r, g, b);
}

void GraphicFrame::DrawFillCircle( sint16 x, sint16 y, sint16 radius, uint8 r, uint8 g, uint8 b ) const
{
	ConvertFrameToGraphic(x, y);
	m_pGraphicEngine->DrawFillCircle(x, y, radius, r, g, b);
}

void GraphicFrame::DrawLine( sint16 x1, sint16 y1, sint16 x2, sint16 y2, uint8 r, uint8 g, uint8 b ) const
{
	ConvertFrameToGraphic(x1, y1);
	ConvertFrameToGraphic(x2, y2);
	m_pGraphicEngine->DrawLine(x1, y1, x2, y2, r, g, b);
}

void GraphicFrame::Print( sint16 x, sint16 y, uint size, ETextAlign eAlign, uint8 r, uint8 g, uint8 b, const char* format, ... ) const
{
	ConvertFrameToGraphic(x, y);
	
	va_list oArgs;
	va_start(oArgs, format);
	m_pGraphicEngine->Print(x, y, size, eAlign, r, g, b, format, oArgs);
	va_end(oArgs);

}

bool GraphicFrame::IsMouseOverlapping(sint16 x, sint16 y, uint16 radius)
{
	ConvertFrameToGraphic(x, y);
	return m_pGraphicEngine->IsMouseOverlapping(x, y, radius);
}

void GraphicFrame::ConvertFrameToGraphic(sint16& x, sint16& y) const
{
	x = m_iPosX + x;
	y = m_iPosY + y;
}

void GraphicFrame::ConvertFrameToGraphic(sint16& x, sint16& y, uint16& /*xl*/, uint16& /*yl*/) const
{
	x = m_iPosX + x;
	y = m_iPosY + y;
}

void GraphicFrame::ConvertGraphicToFrame(sint16& x, sint16& y) const
{
	x = x - m_iPosX;
	y = x - m_iPosY;
}

void GraphicFrame::ConvertGraphicToFrame(sint16& x, sint16& y, uint16& /*xl*/, uint16& /*yl*/) const
{
	x = x - m_iPosX;
	y = x - m_iPosY;
}

