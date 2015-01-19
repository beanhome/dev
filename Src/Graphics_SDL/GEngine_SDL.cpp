#include "SDL.h"
#include "SDL_video.h"
//#include "SDL_draw.h"
#include "SDL_ttf.h"
#include "SDL_rotozoom.h"
#include "FontResource_SDL.h"
#include "ImageResource_SDL.h"
#include "SDL_gfxPrimitives.h"
#include "SDL_gfxBlitFunc.h"

#include "GEngine_SDL.h"
#include "Event_SDL.h"

GEngine_SDL::GEngine_SDL(uint16 width, uint16 height, uint16 depth, const char* rootpath)
	: GEngine(width, height, depth, rootpath)
	, m_pCursor(NULL)
{
	Init();
}

GEngine_SDL::GEngine_SDL(GAppBase* pApp, uint16 width, uint16 height, uint16 depth, const char* rootpath)
	: GEngine(pApp, width, height, depth, rootpath)
	, m_pCursor(NULL)
{
	Init();
}

GEngine_SDL::~GEngine_SDL()
{
	if (m_pCursor != NULL)
		SDL_FreeCursor(m_pCursor);

	Close();
}

#if 0
/* XPM */
static const char *arrow[] = {
	/* width height num_colors chars_per_pixel */
	"    32    32        3            1",
	/* colors */
	"X c #000000",
	". c #ffffff",
	"  c None",
	/* pixels */
	"X                               ",
	"XX                              ",
	"X.X                             ",
	"X..X                            ",
	"X...X                           ",
	"X....X                          ",
	"X.....X                         ",
	"X......X                        ",
	"X.......X                       ",
	"X........X                      ",
	"X.....XXXXX                     ",
	"X..X..X                         ",
	"X.X X..X                        ",
	"XX  X..X                        ",
	"X    X..X                       ",
	"     X..X                       ",
	"      X..X                      ",
	"      X..X                      ",
	"       XX                       ",
	"                                ",
	"                                ",
	"                                ",
	"                                ",
	"                                ",
	"                                ",
	"                                ",
	"                                ",
	"                                ",
	"                                ",
	"                                ",
	"                                ",
	"                                ",
	"0,0"
};

static SDL_Cursor *init_system_cursor(const char *image[])
{
	int i, row, col;
	Uint8 data[4*32];
	Uint8 mask[4*32];
	int hot_x, hot_y;

	i = -1;
	for ( row=0; row<32; ++row ) {
		for ( col=0; col<32; ++col ) {
			if ( col % 8 ) {
				data[i] <<= 1;
				mask[i] <<= 1;
			} else {
				++i;
				data[i] = mask[i] = 0;
			}
			switch (image[4+row][col]) {
		case 'X':
			data[i] |= 0x01;
			mask[i] |= 0x01;
			break;
		case '.':
			mask[i] |= 0x01;
			break;
		case ' ':
			break;
			}
		}
	}
	sscanf(image[4+row], "%d,%d", &hot_x, &hot_y);
	return SDL_CreateCursor(data, mask, 32, 32, hot_x, hot_y);
}
#endif

uint8 data[] = {
	0xFF,
	0x81,
	0x81,
	0x81,
	0x81,
	0x81,
	0x81,
	0xFF
};

uint8 mask[] = {
	0xFF,
	0xFF,
	0xFF,
	0xFF,
	0xFF,
	0xFF,
	0xFF,
	0xFF,
};


uint GEngine_SDL::Init()
{
	LOG("Initializing SDL.\n");
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{ 
		LOG("Could not initialize SDL: %s.\n", SDL_GetError());
		return 1;
	}

	SDL_EnableUNICODE(1);

	LOG("SDL Set Video Mode.\n");
	m_pScreen = SDL_SetVideoMode(m_iWidth, m_iHeight, m_iDepth, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_ANYFORMAT | SDL_RESIZABLE);
	if (m_pScreen == NULL)
	{
		LOG("Couldn't set %dx%dx%d video mode: %s\n", m_iWidth, m_iHeight, m_iDepth, SDL_GetError());
		return 1;
	}

	SDL_SetClipRect(m_pScreen, NULL);

	//SDL_EnableKeyRepeat(500, 10);

	LOG("Initializing SDL TTF.\n");
	if(TTF_Init() == -1)
	{
		LOG("Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
		return 1;
	}

	//m_pCursor = SDL_CreateCursor(data, mask, 8, 8, 4, 4);
	//SDL_SetCursor(m_pCursor);
	//SDL_SetCursor(init_system_cursor(arrow));

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
	SDL_SetClipRect(m_pScreen, NULL);
	SDL_FillRect(m_pScreen, NULL, SDL_MapRGB(m_pScreen->format, 128, 128, 128));
}

void GEngine_SDL::Flip()
{
	SDL_Flip(m_pScreen);
}

void GEngine_SDL::Resize(uint16 w, uint16 h)
{
	m_iWidth = w;
	m_iHeight = h;

	//LOG("SDL Resize Screen.\n");

	m_pScreen = SDL_SetVideoMode(m_iWidth, m_iHeight, m_iDepth, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_ANYFORMAT | SDL_RESIZABLE);
	
	if (m_pScreen == NULL)
		LOG("Couldn't set %dx%dx%d video mode: %s\n", m_iWidth, m_iHeight, m_iDepth, SDL_GetError());
}

void GEngine_SDL::DrawImage(const ImageResource& _image, sint32 x, sint32 y) const
{
	SDL_Surface* image = ((const ImageResource_SDL&)_image).m_pSurface;

	if (image == NULL)
		return;

	if (image->format->palette && m_pScreen->format->palette)
		SDL_SetColors(m_pScreen, image->format->palette->colors, 0, image->format->palette->ncolors);

	SDL_Rect oLoc;
	//oLoc.x = (sint16)(x - image->w / 2);
	//oLoc.y = (sint16)(y - image->h / 2);
	oLoc.x = (sint16)x;
	oLoc.y = (sint16)y;
	oLoc.w = (uint16)image->w;
	oLoc.h = (uint16)image->h;

	/* Blit onto the screen surface */
	if(SDL_BlitSurface(image, NULL, m_pScreen, &oLoc) < 0)
		LOG("BlitSurface error: %s\n", SDL_GetError());
}


void GEngine_SDL::DrawImage(const ImageResource& _image, sint32 x, sint32 y, float fAngle, float fZoom) const
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
	//oLoc.x = (sint16)(x - pOutput->w / 2);
	//oLoc.y = (sint16)(y - pOutput->h / 2);
	oLoc.x = (sint16)x;
	oLoc.y = (sint16)y;
	oLoc.w = (uint16)pOutput->w;
	oLoc.h = (uint16)pOutput->h;

    /* Blit onto the screen surface */
    if(SDL_BlitSurface(pOutput, NULL, m_pScreen, &oLoc) < 0)
        LOG("BlitSurface error: %s\n", SDL_GetError());

	SDL_FreeSurface(pOutput);
}

void GEngine_SDL::DrawImage(const ImageResource& _image, sint32 x, sint32 y, uint16 w, uint16 h, sint32 sx, sint32 sy, uint16 sw, uint16 sh) const
{
	SDL_Surface* image = ((const ImageResource_SDL&)_image).m_pSurface;

	if (image == NULL)
		return;

	if (image->format->palette && m_pScreen->format->palette)
		SDL_SetColors(m_pScreen, image->format->palette->colors, 0, image->format->palette->ncolors);

	SDL_Surface* pOutput = image;
	if (sw != w || sh != h)
	{
		double zx = (double)w/(double)sw;
		double zy = (double)h/(double)sh;
		pOutput = rotozoomSurfaceXY(image, 0.f, zx, zy, 0);
		if (pOutput == NULL)
			return;

		SDL_Rect oDestRect;
		//oDestRect.x = (sint16)(x - w / 2);
		//oDestRect.y = (sint16)(y - h / 2);
		oDestRect.x = (sint16)x;
		oDestRect.y = (sint16)y;
		oDestRect.w = w;
		oDestRect.h = h;

		SDL_Rect oSrcRect;
		oSrcRect.x = (sint16)(sx * zx);
		oSrcRect.y = (sint16)(sy * zy);
		oSrcRect.w = (sint16)(sw * zx);
		oSrcRect.h = (sint16)(sh * zy);

		/* Blit onto the screen surface */
		if(SDL_BlitSurface(pOutput, &oSrcRect, m_pScreen, &oDestRect) < 0)
			LOG("BlitSurface error: %s\n", SDL_GetError());
	
		SDL_FreeSurface(pOutput);
	}
	else
	{
		SDL_Rect oDestRect;
		//oDestRect.x = (sint16)(x - w / 2);
		//oDestRect.y = (sint16)(y - h / 2);
		oDestRect.x = (sint16)x;
		oDestRect.y = (sint16)y;
		oDestRect.w = w;
		oDestRect.h = h;

		SDL_Rect oSrcRect;
		oSrcRect.x = (sint16)sx;
		oSrcRect.y = (sint16)sy;
		oSrcRect.w = (sint16)sw;
		oSrcRect.h = (sint16)sh;

		/* Blit onto the screen surface */
		if(SDL_BlitSurface(image, &oSrcRect, m_pScreen, &oDestRect) < 0)
			LOG("BlitSurface error: %s\n", SDL_GetError());
	}
}

void GEngine_SDL::DrawImage(const ImageResource& _image, sint32 x, sint32 y, sint32 sx, sint32 sy, uint16 sw, uint16 sh) const
{
	DrawImage(_image, x, y, sw, sh, sx, sy, sw, sh);
}


void GEngine_SDL::SetPixel(sint32 x, sint32 y, uint8 r, uint8 g, uint8 b) const
{
	pixelRGBA(m_pScreen, (sint16)x, (sint16)y, r, g, b, 255);
}

void GEngine_SDL::DrawRect(sint32 x, sint32 y, sint32 width, sint32 height, uint8 r, uint8 g, uint8 b) const
{
	rectangleRGBA(m_pScreen, (sint16)x, (sint16)y, (sint16)(x+width), (sint16)(y+height), r, g, b, 255);
}

void GEngine_SDL::DrawFillRect(sint32 x, sint32 y, sint32 width, sint32 height, uint8 r, uint8 g, uint8 b) const
{
	boxRGBA(m_pScreen, (sint16)x, (sint16)y, (sint16)(x+width), (sint16)(y+height), r, g, b, 255);
}

void GEngine_SDL::DrawCircle(sint32 x, sint32 y, sint32 radius, uint8 r, uint8 g, uint8 b) const
{
	circleRGBA(m_pScreen, (sint16)x, (sint16)y, (sint16)radius, r, g, b, 255);
}

void GEngine_SDL::DrawFillCircle(sint32 x, sint32 y, sint32 radius, uint8 r, uint8 g, uint8 b) const
{
	filledCircleRGBA(m_pScreen, (sint16)x, (sint16)y, (sint16)radius, r, g, b, 255);
}

void GEngine_SDL::DrawLine(sint32 x1, sint32 y1, sint32 x2, sint32 y2, uint8 r, uint8 g, uint8 b) const
{
	lineRGBA(m_pScreen, (sint16)x1, (sint16)y1, (sint16)x2, (sint16)y2, r, g, b, 255);
}

void GEngine_SDL::TextSizeArgs(sint32& w, sint32& h, const char* sFontPath, uint16 size, const char* format, va_list oArgs) const
{
	ASSERT(sFontPath != NULL);

	FontResource_SDL* pFont = GetResource<FontResource_SDL>(FontResource_SDL::Desc(sFontPath, size));

	if (pFont->m_pFont == NULL)
	{
		w = h = 0;
		return;
	}

#ifdef _WIN32
	int ln = _vscprintf(format, oArgs) + 1;
#else
	int ln = vsnprintf(NULL, 0, format, oArgs) + 1;
#endif

	char* str = new char[ln];
#ifdef _WIN32
	vsprintf_s(str, ln, format, oArgs);
#else
	vsnprintf(str, ln, format, oArgs);
#endif

	TTF_SizeText(pFont->m_pFont, str, (int*)&w, (int*)&h);

	delete [] str;
}

void GEngine_SDL::PrintArgs(sint32 x, sint32 y, const char* sFontPath, uint16 size, ETextAlign eAlign, uint8 r, uint8 g, uint8 b, const char* format, va_list oArgs) const
{
	ASSERT(sFontPath != NULL);

	FontResource_SDL* pFont = GetResource<FontResource_SDL>(FontResource_SDL::Desc(sFontPath, size));

	if (pFont->m_pFont == NULL)
		return;

#ifdef _WIN32
	int ln = _vscprintf(format, oArgs) + 1;
#else
	int ln = vsnprintf(NULL, 0, format, oArgs) + 1;
#endif
	const int bufferln = 32;
	char buffer[bufferln];
	char* str = (ln > bufferln ? new char[ln] : buffer);
#ifdef _WIN32
	vsprintf_s(str, ln, format, oArgs);
#else
	vsnprintf(str, ln, format, oArgs);
#endif

	SDL_Surface* texte = NULL;
	SDL_Color color = { 0, 0, 0 };
	color.r = r;
	color.g = g;
	color.b = b;
	texte = TTF_RenderText_Solid(pFont->m_pFont, str, color);
	if (ln > bufferln)
		delete [] str;
	if (texte == NULL)
		return;

	uint16 w = (uint16)texte->w;
	uint16 h = (uint16)texte->h;

	SDL_Rect position;
	position.x = (sint16)x;
	position.y = (sint16)y;

	switch (eAlign)
	{
		case LeftTop:		position.x = (sint16)x;				position.y = (sint16)y;				break;
		case LeftCenter:	position.x = (sint16)x;				position.y = (sint16)(y - h / 2);	break;
		case LeftBottom:	position.x = (sint16)x;				position.y = (sint16)(y - h);		break;
		case CenterTop:		position.x = (sint16)(x - w / 2);	position.y = (sint16)y;				break;
		case Center:		position.x = (sint16)(x - w / 2);	position.y = (sint16)(y - h / 2);	break;
		case CenterBottom:	position.x = (sint16)(x - w / 2);	position.y = (sint16)(y - h);		break;
		case RightTop:		position.x = (sint16)(x - w);		position.y = (sint16)y;				break;
		case RightCenter:	position.x = (sint16)(x - w);		position.y = (sint16)(y - h / 2);	break;
		case RightBottom:	position.x = (sint16)(x - w);		position.y = (sint16)(y - h);		break;
	}

	/*
	position.w = w;
	position.h = h;
	SDL_FillRect(m_pScreen, &position, SDL_MapRGB(m_pScreen->format, 255, 0, 255));
	*/

	SDL_BlitSurface(texte, NULL, m_pScreen, &position); 

	SDL_FreeSurface(texte);
}

void GEngine_SDL::ClampClear() const
{
	SDL_SetClipRect(m_pScreen, NULL);
}


void GEngine_SDL::ClampRect(sint32 x, sint32 y, uint16 w, uint16 h) const
{
	SDL_Rect rect;
	rect.x = (sint16)x;
	rect.y = (sint16)y;
	rect.w = (sint16)w;
	rect.h = (sint16)h;
	SDL_SetClipRect(m_pScreen, &rect);
}


Event* GEngine_SDL::CreateEvent() const
{
	return new Event_SDL();
}

bool GEngine_SDL::PollEvent(Event* pEvent)
{
	return (SDL_PollEvent(((Event_SDL*)pEvent)->GetSDLEvent()) != 0);
}

const Event& GEngine_SDL::WaitEvent(Event* pEvent)
{
	SDL_WaitEvent(((Event_SDL*)pEvent)->GetSDLEvent());
	return *pEvent;
}

