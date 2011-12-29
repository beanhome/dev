#include "Font.h"

Font::Font(GEngine* pGEngine, uint32 crc, const char* path, uint16 size)
	: Resource(pGEngine, crc)
	, m_sPath(path)
	, m_iSize(size)
{}

Font::~Font()
{}