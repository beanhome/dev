
#ifndef __WEDITTEXT_H__
#define __WEDITTEXT_H__

#include "Utils.h"
#include "WText.h"

class ImageResource;

class WEditText : public WText
{
public:
	struct Desc : public WText::Desc
	{
		Desc(const WText::Desc& oDesc) : WText::Desc(oDesc) {}
	};

public:
	WEditText(CanvasBase& oParent, WEditText::Desc oDesc, sint32 id = -1, const string& sName = "unknow");
	WEditText(Widget& oParent, WEditText::Desc oDesc, sint32 id = -1, const string& sName = "unknow");
	void Init();

	~WEditText();

	bool IsEdit() const { return m_bEdit; }
	void SetEdit(bool val) { m_bEdit = val; }

	void OnFocusEnter() override;
	void OnFocusExit() override;
	void CatchEvent(Event* pEvent) override;

public:
	void Draw() const override;

protected:
	void OnTextChanged() override;

private:
	void SetLineIndex(sint32 iIndex);
	sint32 GetLineIndex() const;

	void ToLeft();
	void ToRight();
	void ToUp();
	void ToDown();
	void ToHome();
	void ToEnd();

private:
	bool m_bEdit;
	sint32 m_iLineIndex;
	sint32 m_iCharIndex;



};

#endif

