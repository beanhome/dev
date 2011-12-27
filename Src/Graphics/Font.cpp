#include "Font.h"

Font::Font(GEngine* pGEngine, uint16 size)
	: Resource(pGEngine)
	, m_iSize(size)
{}

Font::~Font()
{}