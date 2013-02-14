#include "Utils.h"
#include "GEngine_SDL.h"
#include "InputEvent_SDL.h"

#include "SDL.h"
#include "SDL_video.h"
#include "SDL_Draw.h"
#include "SDL_ttf.h"
#include "SDL_rotozoom.h"
#include "FontResource_SDL.h"
#include "ImageResource_SDL.h"
#include "SDL_gfxPrimitives.h"
#include "SDL_gfxBlitFunc.h"


GEngine_SDL::GEngine_SDL(uint16 width, uint16 height, uint16 depth)
	: GEngine(width, height, depth)
	, m_pCursor(NULL)
{
	Init();

	m_pInputEvent = new InputEvent_SDL;
	m_pPreviousInputEvent = new InputEvent_SDL;
}

GEngine_SDL::~GEngine_SDL()
{
	delete m_pInputEvent;
	delete m_pPreviousInputEvent;

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

	LOG("SDL Set Video Mode.\n");
	m_pScreen = SDL_SetVideoMode(m_iWidth, m_iHeight, m_iDepth, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_ANYFORMAT);
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
	SDL_FillRect(m_pScreen, NULL, SDL_MapRGB(m_pScreen->format, 128, 128, 128));
}

void GEngine_SDL::Flip()
{
	SDL_Flip(m_pScreen);
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
	oLoc.w = (uint16)image->w;
	oLoc.h = (uint16)image->h;

	/* Blit onto the screen surface */
	if(SDL_BlitSurface(image, NULL, m_pScreen, &oLoc) < 0)
		LOG("BlitSurface error: %s\n", SDL_GetError());
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
	oLoc.w = (uint16)pOutput->w;
	oLoc.h = (uint16)pOutput->h;

    /* Blit onto the screen surface */
    if(SDL_BlitSurface(pOutput, NULL, m_pScreen, &oLoc) < 0)
        LOG("BlitSurface error: %s\n", SDL_GetError());

	SDL_FreeSurface(pOutput);
}

void GEngine_SDL::DrawImage(const ImageResource& _image, sint16 x, sint16 y, uint16 w, uint16 h, sint16 sx, sint16 sy, uint16 sw, uint16 sh) const
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
		oDestRect.x = x - (sint16)w / 2;
		oDestRect.y = y - (sint16)h / 2;
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
		oDestRect.x = x - (sint16)w / 2;
		oDestRect.y = y - (sint16)h / 2;
		oDestRect.w = w;
		oDestRect.h = h;

		SDL_Rect oSrcRect;
		oSrcRect.x = sx;
		oSrcRect.y = sy;
		oSrcRect.w = sw;
		oSrcRect.h = sh;

		/* Blit onto the screen surface */
		if(SDL_BlitSurface(image, &oSrcRect, m_pScreen, &oDestRect) < 0)
			LOG("BlitSurface error: %s\n", SDL_GetError());
	}
}

void GEngine_SDL::DrawImage(const ImageResource& _image, sint16 x, sint16 y, sint16 sx, sint16 sy, uint16 sw, uint16 sh) const
{
	DrawImage(_image, x, y, sw, sh, sx, sy, sw, sh);
}


void GEngine_SDL::SetPixel(sint16 x, sint16 y, uint8 r, uint8 g, uint8 b) const
{
	pixelRGBA(m_pScreen, x, y, r, g, b, 255);
}

void GEngine_SDL::DrawRect(sint16 x, sint16 y, sint16 width, sint16 height, uint8 r, uint8 g, uint8 b) const
{
	rectangleRGBA(m_pScreen, x, y, x+width, y+height, r, g, b, 255);
}

void GEngine_SDL::DrawFillRect(sint16 x, sint16 y, sint16 width, sint16 height, uint8 r, uint8 g, uint8 b) const
{
	boxRGBA(m_pScreen, x, y, x+width, y+height, r, g, b, 255);
}

void GEngine_SDL::DrawCircle(sint16 x, sint16 y, sint16 radius, uint8 r, uint8 g, uint8 b) const
{
	circleRGBA(m_pScreen, x, y, radius, r, g, b, 255);
}

void GEngine_SDL::DrawFillCircle(sint16 x, sint16 y, sint16 radius, uint8 r, uint8 g, uint8 b) const
{
	filledCircleRGBA(m_pScreen, x, y, radius, r, g, b, 255);
}

void GEngine_SDL::DrawLine(sint16 x1, sint16 y1, sint16 x2, sint16 y2, uint8 r, uint8 g, uint8 b) const
{
	lineRGBA(m_pScreen, x1, y1, x2, y2, r, g, b, 255);
}

void GEngine_SDL::PrintArgs(sint16 x, sint16 y, const char* sFontPath, uint size, ETextAlign eAlign, uint8 r, uint8 g, uint8 b, const char* format, va_list oArgs) const
{
	ASSERT(sFontPath != NULL);

	FontResource_SDL* pFont = GetResource<FontResource_SDL>(FontResource_SDL::Desc(sFontPath, size));

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

void GEngine_SDL::ClampClear() const
{
	SDL_SetClipRect(m_pScreen, NULL);
}


void GEngine_SDL::ClampRect(sint16 x, sint16 y, uint16 w, uint16 h) const
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	SDL_SetClipRect(m_pScreen, &rect);
}


bool GEngine_SDL::PollEvent()
{
	return (SDL_PollEvent(((InputEvent_SDL*)m_pInputEvent)->GetSDLEvent()) != 0);
}

const InputEvent& GEngine_SDL::WaitEvent()
{
	SDL_WaitEvent(((InputEvent_SDL*)m_pInputEvent)->GetSDLEvent());
	return *m_pInputEvent;
}



void GEngine_SDL::SaveEvent()
{
	*(InputEvent_SDL*)m_pPreviousInputEvent = *(InputEvent_SDL*)m_pInputEvent;
}
