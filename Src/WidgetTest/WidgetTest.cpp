#include "Utils.h"

#include "GEngine_SDL.h"
#include "Event_SDL.h"
#include "Timer.h"
#include "EventManager.h"
#include "Widget.h"
#include "WidgetEditor.h"


extern "C" int SDL_main(int argc, char *argv[])
{
	InitLog(argc, argv);

	int w = 1280;
	int h = 720;

	GEngine_SDL ge(w, h, 32, "../../");
	Widget MainWin(ge, "main");
	MainWin.SetPrintFont(FONT_PATH, 14);
	MainWin.SetSideProp(SideEnum::Left,		WidgetSide::ParentRef(0.f, 10));
	MainWin.SetSideProp(SideEnum::Right,	WidgetSide::ParentRef(1.f, -10));
	MainWin.SetSideProp(SideEnum::Top,		WidgetSide::ParentRef(0.f, 10));
	MainWin.SetSideProp(SideEnum::Bottom,	WidgetSide::ParentRef(1.f, -10));
	//MainWin.SetMaxWidth(1000);

	Widget* pWin1 = MainWin.AddNewChild(0, "sub1");
	pWin1->SetMinWidth(50);
	pWin1->SetSideProp(SideEnum::Left,		WidgetSide::ParentRef(0.5f));
	pWin1->SetSideProp(SideEnum::Right,		WidgetSide::ChildRef(1, 0.f, 5));
	pWin1->SetSideProp(SideEnum::Top,		WidgetSide::ParentRef(0.25f));
	pWin1->SetSideProp(SideEnum::Bottom,	WidgetSide::ParentRef(0.75f));
	pWin1->SetHorizOffset(-0.5f, 0);

	Widget* pWin11 = pWin1->AddNewChild(0, "sub11");
	pWin11->SetSideProp(SideEnum::Left,		WidgetSide::ParentRef(0.f, 5));
	pWin11->SetSideProp(SideEnum::Right,	WidgetSide::SelfRef(100));
	pWin11->SetSideProp(SideEnum::Top,		WidgetSide::ParentRef(0.f, 5));
	pWin11->SetSideProp(SideEnum::Bottom,	WidgetSide::SelfRef(100));

	Widget* pWin12 = pWin1->AddNewChild(1, "sub12");
	pWin12->SetSideProp(SideEnum::Left,		WidgetSide::BrotherRef(0, 1.f, 5));
	pWin12->SetSideProp(SideEnum::Right,	WidgetSide::SelfRef(100));
	pWin12->SetSideProp(SideEnum::Top,		WidgetSide::ParentRef(0.f, 5));
	pWin12->SetSideProp(SideEnum::Bottom,	WidgetSide::SelfRef(100));

	Widget* pWin2 = MainWin.AddNewChild(1, "sub2");
	pWin2->SetSideProp(SideEnum::Left,		WidgetSide::BrotherRef(0, 1.f, 10));
	pWin2->SetSideProp(SideEnum::Right,		WidgetSide::SelfRef(100));
	pWin2->SetSideProp(SideEnum::Top,		WidgetSide::BrotherRef(0, 0.f));
	pWin2->SetSideProp(SideEnum::Bottom,	WidgetSide::SelfRef(100));

	Widget* pWin3 = MainWin.AddNewChild(1, "sub3");
	pWin3->SetSideProp(SideEnum::Left,		WidgetSide::SelfRef(100));
	pWin3->SetSideProp(SideEnum::Right,		WidgetSide::ParentRef(1.f, -10));
	pWin3->SetSideProp(SideEnum::Top,		WidgetSide::ParentRef(0.5f));
	pWin3->SetSideProp(SideEnum::Bottom,	WidgetSide::SelfRef(100));
	pWin3->SetVertiOffset(-0.5f, 0);

	WidgetEditor oWidgetEditor;

	bool bQuit = false;
	int i=0;
	double fTime = Timer::Get();

	while (!bQuit)
	{
		uint16 w = ge.GetWidth();
		uint16 h = ge.GetHeight();

		ge.UpdateEvent();

		if (w != ge.GetWidth())
			MainWin.SetDirtySide(SideEnum::Right);

		if (h != ge.GetHeight())
			MainWin.SetDirtySide(SideEnum::Bottom);

		bQuit = (ge.GetEventManager()->IsQuit() || ge.GetEventManager()->GetVirtualKey(KEY_ESC) == KeyPressed);

		ge.Clear();

		MainWin.DetermineDimension();
		MainWin.Draw();

		ge.Flip();
	}

	return 0;
}


