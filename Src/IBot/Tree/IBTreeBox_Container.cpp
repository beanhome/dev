#include "IBTreeBox_Container.h"

#include "GEngine.h"
#include "Canvas.h"
#include "Utils.h"

IBTreeBox_Container::IBTreeBox_Container(Canvas& oCanvas, IBTreeBox* pParent)
	: IBTreeBox(oCanvas, pParent)
{
}

IBTreeBox_Container::~IBTreeBox_Container()
{
	for (IBTreeBox*& pTreeBox : m_aChildren)
	{
		if (pTreeBox != nullptr)
			delete pTreeBox;
		pTreeBox = nullptr;
	}
}

void IBTreeBox_Container::AddChild(class IBTreeBox* pBox)
{
	m_aChildren.push_back(pBox);

	UpdateSize();
}

void IBTreeBox_Container::SetPos(sint32 x, sint32 y)
{
	IBTreeBox::SetPos(x, y);
	UpdatePos();
}

void IBTreeBox_Container::Update(float dt, sint32 iMouseX, sint32 iMouseY)
{
	IBTreeBox::Update(dt, iMouseX, iMouseY);

	for (IBTreeBox* pTreeBox : m_aChildren)
	{
		pTreeBox->Update(dt, iMouseX, iMouseY);
	}
}

void IBTreeBox_Container::OnMouseClick(sint32 iMouseX, sint32 iMouseY)
{
	for (IBTreeBox* pTreeBox : m_aChildren)
	{
		pTreeBox->MouseClick(iMouseX, iMouseY);
	}
}

void IBTreeBox_Container::Draw() const
{
	for (IBTreeBox* pTreeBox : m_aChildren)
	{
		pTreeBox->Draw();
	}
}
