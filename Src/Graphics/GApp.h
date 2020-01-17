#ifndef __GAPP_H__
#define __GAPP_H__

#include "Utils.h"

class GEngine;
class Event;

typedef class GAppBase* (*CreateAppFct)(GEngine* pEngine, int argc, char *argv[]);
typedef std::map<string, CreateAppFct> AppMap;

#define DEFINE_APP(App) \
AppMap::iterator App::AppMapIterator = GAppBase::RegisterApp(#App, &App::InstanciateApp);

#define DECLARE_APP(App) \
	public: \
static GAppBase* InstanciateApp(GEngine* pEngine, int argc, char *argv[]) { return new App(pEngine, argc, argv); } \
	private: \
		static AppMap::iterator AppMapIterator;


class GAppBase
{
	public:
		GAppBase(GEngine* pEngine, int argc, char *argv[]);
		virtual ~GAppBase();

		//void SetNoClearScreen(bool bNoClearScreen) { m_bNoClearScreen = bNoClearScreen; }
		//bool GetNoClearScreen() const { return m_bNoClearScreen; }

		void SetSlomo(float slomo) { m_fSlomo = slomo; }
		float GetSlomo() const { return m_fSlomo; }

		bool IsPaused() const { return m_bPause; }
		void SetPause(bool bPause) { m_bPause = bPause; }

		virtual int Update(float dt) = 0;
		virtual int UpdatePause() { return 0; };
		virtual int Draw() = 0;

		virtual void Init(int argc, char *argv[]) {}
		virtual int Loop();
		virtual void Close() {}

		virtual void CatchEvent(Event* pEvent);

		static AppMap::iterator RegisterApp(const char* AppName, CreateAppFct Fct);
		static GAppBase* InstanciateApp(const char* AppName, GEngine* pEngine, int argc, char *argv[]);
		static AppMap& GetAppMap();

		static char* GetArg(char arg, int argc, char *argv[]);
		static float GetArgAsFloat(char arg, float fDefault, int argc, char *argv[]);
		static int GetArgAsInt(char arg, int iDefault, int argc, char *argv[]);
		static const char* GetArgAsString(char arg, const char* sDefault, int argc, char *argv[]);

	protected:
		GEngine* m_pEngine;
		bool m_bNoClearScreen;
		bool m_bPause;
		float m_fSlomo;
		bool m_bQuit;
};


#endif // __GAPP_H__

