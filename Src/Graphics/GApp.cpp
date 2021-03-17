#include "GApp.h"
#include "GEngine.h"
#include "Timer.h"
#include "Event.h"
//#include <complex>
#include "EventManager.h"
#include <cmath>

GAppBase::GAppBase(GEngine* pEngine, int argc, char *argv[])
	: m_pEngine(pEngine)
	, m_bNoClearScreen(false)
	, m_bPause(false)
	, m_fSlomo(1.f)
	, m_bQuit(false)
{
}

GAppBase::~GAppBase()
{
}

//static
AppMap::iterator GAppBase::RegisterApp(const char* AppName, CreateAppFct Fct)
{
	AppMap& s_Map = GAppBase::GetAppMap();
	return s_Map.insert_or_assign(AppName, Fct).first;
}

//static
GAppBase* GAppBase::InstanciateApp(const char* sAppName, GEngine* pEngine, int argc, char *argv[])
{
	GAppBase* pApp = nullptr;

	AppMap& s_Map = GAppBase::GetAppMap();
	AppMap::iterator it = s_Map.find(sAppName);
	if (it != GAppBase::GetAppMap().end())
	{
		pApp = it->second(pEngine, argc, argv);
		pEngine->SetApp(pApp);
	}

	return pApp;
}

//static
AppMap& GAppBase::GetAppMap()
{
	static AppMap s_Map; return s_Map;
}


//static
char* GAppBase::GetArg(char arg, int argc, char *argv[])
{
	for (int i = 1; i < argc; ++i)
	{
		if (argv[i][0] == '-' && argv[i][1] == arg && i + 1 < argc)
			return argv[i + 1];
	}

	return nullptr;
}

//static
float GAppBase::GetArgAsFloat(char arg, float fDefault, int argc, char *argv[])
{
	char* sValue = GetArg(arg, argc, argv);
	if (sValue == nullptr)
		return fDefault;

	return (float)atof(sValue);
}

//static
int GAppBase::GetArgAsInt(char arg, int iDefault, int argc, char *argv[])
{
	char* sValue = GetArg(arg, argc, argv);
	if (sValue == nullptr)
		return iDefault;

	return atoi(sValue);
}

//static
const char* GAppBase::GetArgAsString(char arg, const char* sDefault, int argc, char *argv[])
{
	char* sValue = GetArg(arg, argc, argv);
	if (sValue == nullptr)
		return sDefault;

	return sValue;
}


void GAppBase::CatchEvent(Event* pEvent)
{
	m_bQuit |= pEvent->IsQuit();

	if (pEvent->IsKeyboard())
	{
		m_bQuit |= (m_pEngine->GetEventManager()->GetVirtualKey(KEY_ESC) == KeyPressed);

		/*
		if (m_pEngine->GetEventManager()->GetVirtualKey(KEY_SPACE) == KeyPressed)
			m_bPause = !m_bPause;
		*/
	}

	if (pEvent->IsResize())
	{
		sint32 w, h;
		pEvent->GetResizeEvent(w, h);
		m_pEngine->Resize((uint16)w, (uint16)h);
	}
}


int GAppBase::Loop()
{
	int res;
	double fTime = Timer::Get();
	double fLastTime = fTime;

	while (!m_bQuit)
	{
		fLastTime = fTime;
		fTime = Timer::Get();
		float dt = (float)(fTime - fLastTime);
		dt = std::min<float>(dt, 0.1f);

		if (!m_bPause)
		{
			res = Update(dt * m_fSlomo);
			if (res != 0)
				return res;
		}
		else
		{
			res = UpdatePause();
			if (res != 0)
				return res;
		}

		if (!m_bNoClearScreen)
			m_pEngine->Clear();

		res = Draw();
		if (res != 0)
			return res;

		m_pEngine->ClampClear();
		m_pEngine->Print(m_pEngine->GetWidth() - 5, 5, m_pEngine->GetPrintFont(), 12, RightTop, 255, 255, 255, "%.2f ms / %.2f fps", dt * 1000.f, (dt > 0.f ? 1.f / dt : 0.f));
		m_pEngine->Print(m_pEngine->GetWidth() - 5, 20, m_pEngine->GetPrintFont(), 12, RightTop, 255, 255, 255, "%.2f", fTime);
		m_pEngine->Print(m_pEngine->GetWidth() - 5, 35, m_pEngine->GetPrintFont(), 12, RightTop, 255, 255, 255, "%d %d", m_pEngine->GetMouseX(), m_pEngine->GetMouseY());

		if (m_bPause)
		{
			m_pEngine->ClampClear();
			m_pEngine->CanvasBase::Print(m_pEngine->GetWidth()/2, 100, m_pEngine->GetPrintFont(), 50, Center, (int)(sin(fTime*4.f)*0.5f * 254.f) + 127, 0, 0, "PAUSE");
		}

		m_pEngine->Flip();

		m_pEngine->UpdateEvent(dt);
	}

	return 0;
}

