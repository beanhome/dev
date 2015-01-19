
#ifndef __WBUTTON_H__
#define __WBUTTON_H__

#include "Widget.h"
#include "Functor.h"

class ImageResource;
class Functor_Base;

namespace ButtonState
{
	enum Type
	{ 
		Default,
		Focus,
		Pressed,
		Num
	};

	static const char* ToString[Num] =
	{
		"Default",
		"Focus",
		"Pressed",
	};

	static const char* ToSuffix[Num] = { "D", "F", "P" };
}


class WButton : public Widget
{
public:
	struct Desc
	{
		const char* sBasePath;
		const char* sExt;
		sint32 iChildArea_Margin;

		Desc(const char* _sBasePath, const char* _sExt, sint32 m)
			: sBasePath(_sBasePath), sExt(_sExt), iChildArea_Margin(m)
		{}
	};

public:
	WButton(CanvasBase& oParent, WButton::Desc oDesc, sint32 id = -1, const string& sName = "unknow");
	WButton(Widget& oParent, WButton::Desc oDesc, sint32 id = -1, const string& sName = "unknow");
	void Init();

	~WButton();

public:
	sint32 GetAutoWidth() override;
	sint32 GetAutoHeight() override;

	void Draw() const override;

	Widget* GetChild(uint32 id) override;
	const Widget* GetChild(uint32 id) const override;

	void OnFocusEnter() override;
	void OnFocusExit() override;
	void CatchEvent(Event* pEvent) override;

	template<typename Owner>
	void SetOnClickEvent(Owner* pOwner, typename Functor<Owner>::Function pFunction) { m_pOnClickFunctor = new Functor<Owner>(pOwner, pFunction); }

protected:
	Widget* GetParentRef() override { return m_pChildArea; }
	void InsertChild(Widget* pChild) override;

	void OnClick() {	if (m_pOnClickFunctor != NULL)	(*m_pOnClickFunctor)(this);		}

private:
	Desc m_oDesc;
	ImageResource* m_pImageResource[ButtonState::Num];
	Widget* m_pChildArea;

	ButtonState::Type m_eButtonState;

	Functor_Base* m_pOnClickFunctor;
};

#endif

