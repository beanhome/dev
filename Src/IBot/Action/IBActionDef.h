#ifndef __IBACTIONDEF_H__
#define __IBACTIONDEF_H__

#include "Utils.h"
#include "Action/IBAction.h"

class IBPlanner;
class IBFactDef;
class IBFact;
class IBObject;

struct FactCondDef
{
	IBFactDef* m_pFactDef;
	vector<string> m_aVarName;
	FactCondDef(IBFactDef* pFactDef) : m_pFactDef(pFactDef) {}
	void AddVariable(const char* sName) { m_aVarName.push_back(sName); }
	const string& GetName() const { return m_pFactDef->GetName(); }
};

class IBActionDef
{
	public:
		IBActionDef(const string& name, IBPlanner* pPlanner);
		virtual ~IBActionDef();

	public:
		const string&					GetName() const { return m_sName; }
		virtual void					Define() = 0;

		const vector<string>&			GetVariables() const { return m_aVariable; }
		const vector<FactCondDef>&		GetPreCondDef() const { return m_aPreCondDef; }
		const vector<FactCondDef>&		GetPostCondDef() const { return m_aPostCondDef; }
		vector<FactCondDef>&			GetPostCondDef() { return m_aPostCondDef; }

		IBAction*						Instanciate(IBFact* pPostCond1);
		//void							Instanciate(IBFact* pPostCond1, IBFact* pPostCond2);
		//void							Instanciate(IBFact* pPostCond1, IBFact* pPostCond2, IBFact* pPostCond3);
		
		void							AddVariable(const char* name);
		void							AddPreCondition(const char* name, ...);
		void							AddPostCondition(const char* name, ...);

		virtual void					Print(const IBAction::VarMap& aUserData, int tab) const;

		virtual void					PreDestroy(IBAction::VarMap& aUserData) const {}

		virtual bool					Init(IBAction* pAction) { return true; };
		virtual bool					Start(IBAction* pAction) { return true; };
		virtual bool					Execute(IBAction* pAction) { return false; };
		virtual bool					Finish(IBAction* pAction) { return true; };
		virtual void					Destroy(IBAction* pAction) { };

	protected:
		string							m_sName;
		IBPlanner*						m_pPlanner;

		vector<string>					m_aVariable;

		vector<FactCondDef>				m_aPreCondDef;
		vector<FactCondDef>				m_aPostCondDef;

};

#endif
