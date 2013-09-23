#include "Allocator.h"
#include "Utils.h"


Allocator Allocator::s_oAllocator;


Header::Header()
{

}

Header::~Header()
{

}

void Header::Init(size_t size, const char* file_name, unsigned int line_num)
{
	m_iSize = size;
	m_sFileName = file_name;
	m_iLineNumber = line_num;

	m_pAddress = (this+1);
	m_pBlockNode = NULL;

	m_iCkeckSum = ComputeCheckSum();
}

bool Header::Check() const
{
	return CheckSum();
}

int Header::ComputeCheckSum() const
{
	int iCkeckSum = 0;

	iCkeckSum += (int)m_sFileName;
	iCkeckSum += (int)m_iLineNumber;
	iCkeckSum += (int)m_pAddress;

	return iCkeckSum;
}

bool Header::CheckSum() const
{
	return (m_iCkeckSum == ComputeCheckSum());
}

void Header::Print() const
{
	LOG("Block 0x%p of size %d\n", m_pAddress, m_iSize);
	LOG("Allocate from %s (%d)\n", m_sFileName, m_iLineNumber);
	LOG("\n");
}


Footer::Footer()
	: m_iMagicNumber(MAGIC)
{
}

Footer::~Footer()
{
}

void Footer::Init(size_t size, const char* file_name, unsigned int line_num)
{
	m_iMagicNumber = MAGIC;
}

bool Footer::Check() const
{
	return (m_iMagicNumber == MAGIC);
}



Allocator::Allocator()
	: m_pBlocks(NULL)
{
}


Allocator::~Allocator()
{
	LOG("Check : %s\n", Check() ? "OK" : "FAIL");
	LOG("Leak Test: %s\n", IsEmpty() ? "OK" : "FAIL");

	Print();

	while (m_pBlocks != NULL)
	{
		RemBlock(m_pBlocks->pBlock);
	}
}


void* Allocator::_Malloc(size_t size, const char* file_name, unsigned int line_num)
{
	//LOG("%s:%d  malloc(%d)\n", file_name, line_num, size);

	size_t total = size + sizeof(Header) + sizeof(Footer);
	byte* pBlock = (byte*)malloc(total);
	byte* ptr = pBlock + sizeof(Header);

	Header* pHeader = reinterpret_cast<Header*>(pBlock);
	Footer* pFooter = reinterpret_cast<Footer*>(ptr+size);

	pHeader->Init(size, file_name, line_num);
	pFooter->Init(size, file_name, line_num);

	AddBlock(pBlock);

	return ptr;
}

void* Allocator::_Realloc(void* ptr, size_t size, const char* file_name, unsigned int line_num)
{
	//LOG("%s:%d  realloc(%p, %d)\n", file_name, line_num, ptr, size);

	byte* pBlock = (byte*)ptr - sizeof(Header);
	Header* pHeader = reinterpret_cast<Header*>(pBlock);
	Footer* pFooter = reinterpret_cast<Footer*>((byte*)ptr+size);

	ASSERT(pHeader->m_pBlockNode != NULL);
	BlockNode* pNode = pHeader->m_pBlockNode;

	size_t total = size + sizeof(Header) + sizeof(Footer);
	pBlock = (byte*)realloc(pBlock, total);
	ptr = pBlock + sizeof(Header);

	pHeader = reinterpret_cast<Header*>(pBlock);
	pFooter = reinterpret_cast<Footer*>((byte*)ptr+size);

	pHeader->Init(size, file_name, line_num);
	pFooter->Init(size, file_name, line_num);

	pNode->pBlock = pBlock;
	pHeader->m_pBlockNode = pNode;
	
	return ptr;
}

void* Allocator::_Calloc(size_t n, size_t size, const char* file_name, unsigned int line_num)
{
	return _Malloc(n*size, file_name, line_num);
}

void Allocator::_Free(void* ptr, const char* file_name, unsigned int line_num)
{
	//LOG("%s:%d  free(%p)\n", file_name, line_num, ptr);

	byte* pBlock = (byte*)ptr - sizeof(Header);

	Header* pHeader = reinterpret_cast<Header*>(pBlock);
	Footer* pFooter = reinterpret_cast<Footer*>((byte*)ptr+pHeader->m_iSize);

	ASSERT(pHeader->Check());
	ASSERT(pFooter->Check());

	ASSERT(pHeader->m_pBlockNode != NULL);
	RemBlock(pBlock);

	free(pBlock);
}

bool Allocator::_Check() const
{
	bool res = true;

	for (BlockNode* pNode = m_pBlocks ; pNode != NULL ; pNode = pNode->pNext)
	{
		Header* pHeader = reinterpret_cast<Header*>(pNode->pBlock);
		Footer* pFooter = reinterpret_cast<Footer*>(pNode->pBlock+sizeof(Header)+pHeader->m_iSize);

		res &= pHeader->Check();
		res &= pFooter->Check();
	}

	return true;
}

void Allocator::_Print() const
{
	int n = 0;
	for (BlockNode* pNode = m_pBlocks ; pNode != NULL ; pNode = pNode->pNext)
	{
		Header* pHeader = reinterpret_cast<Header*>(pNode->pBlock);
		pHeader->Print();
		++n;
	}

	if (n > 0)
		LOG("Counting %d Block\n", n);
}


void Allocator::AddBlock(byte* pBlock)
{
	Header* pHeader = reinterpret_cast<Header*>(pBlock);
	Footer* pFooter = reinterpret_cast<Footer*>(pBlock+sizeof(Header)+pHeader->m_iSize);

	ASSERT(pHeader->m_pBlockNode == NULL);

	if (pHeader->m_pBlockNode != NULL)
	{

	}
	else
	{
		BlockNode* pNode = (BlockNode*)malloc(sizeof(BlockNode));
		pNode->pPrev = NULL;

		if (m_pBlocks != NULL)
			m_pBlocks->pPrev = pNode;
		pNode->pNext = m_pBlocks;
		m_pBlocks = pNode;
		pNode->pBlock = pBlock;
		pHeader->m_pBlockNode = pNode;
	}
}

void Allocator::RemBlock(byte* pBlock)
{
	Header* pHeader = reinterpret_cast<Header*>(pBlock);
	Footer* pFooter = reinterpret_cast<Footer*>(pBlock+sizeof(Header)+pHeader->m_iSize);

	ASSERT(pHeader->m_pBlockNode != NULL);

	BlockNode* pNode = pHeader->m_pBlockNode;

	if (pNode->pPrev != NULL)
		pNode->pPrev->pNext = pNode->pNext;
	else
	{
		ASSERT(m_pBlocks == pNode);
		m_pBlocks = pNode->pNext;
	}

	if (pNode->pNext != NULL)
		pNode->pNext->pPrev = pNode->pPrev;

	free(pNode);
}

