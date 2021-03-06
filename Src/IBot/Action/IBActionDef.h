#ifndef __IBACTIONDEF_H__
#define __IBACTIONDEF_H__

#include "Utils.h"
#include "Action/IBAction.h"
#include "Fact/IBFactDef.h"

struct IBFactCondDef
{
	struct Link
	{
		Link(const char* ActionVarName, const char* FactVarName)
		{
			ASSERT(ActionVarName != nullptr);
			ASSERT(FactVarName != nullptr);
			if (ActionVarName != nullptr)
				m_sActionVarName = ActionVarName;
			if (FactVarName != nullptr)
				m_sCondVarName = FactVarName;
		}
		string m_sActionVarName;
		string m_sCondVarName;
	};

	class IBFactDef* m_pFactDef;

	bool m_bInverted;

	vector<Link> m_aLinkNames;

	IBFactCondDef(class IBFactDef* pFactDef, bool bInverted) : m_pFactDef(pFactDef), m_bInverted(bInverted) {}
	void AddLink(const char* sActionVarName) { AddLink("Var", sActionVarName); }
	void AddLink(const char* sFactVarName, const char* sActionVarName) { m_aLinkNames.push_back(Link(sActionVarName, sFactVarName)); }
	const string& GetName() const { return m_pFactDef->GetName(); }
};

class IBActionDef
{
public:
	IBActionDef(const string& name, class IBPlanner* pPlanner);
	virtual ~IBActionDef();

public:
	const string&					GetName() const { return m_sName; }
	virtual void					Define() = 0;

	const vector<string>&			GetVarNames() const { return m_aVarNames; }
	const vector<IBFactCondDef>&	GetPreCondDef() const { return m_aPreCondDef; }
	const vector<IBFactCondDef>&	GetPostCondDef() const { return m_aPostCondDef; }
	vector<IBFactCondDef>&			GetPostCondDef() { return m_aPostCondDef; }

	IBAction*						Instanciate(class IBFact* pPostCond1);

	const IBFactCondDef*			FindPostCond(const string& sPostCondName) const;

	void							AddVariable(const char* name);
	void							AddPreCondition(const char* name, bool bTrue, ...);
	void							AddPostCondition(const char* name, bool bTrue, ...);

	virtual float					GetCost(const IBAction* pAction) const = 0;

	virtual void					CreateOwnedVariables(IBAction* pAction) const { }
	virtual void					CompleteVariables(IBAction* pAction) const { }

	virtual void					PostCreated(IBAction* pAction) const { }

	virtual void					Update(IBAction* pAction) const { }
	virtual bool					Start(IBAction* pAction) const { return true; };
	virtual void					Finish(IBAction* pAction, bool bInterrupted) const { pAction->SetState(IBA_Finish); };
	virtual void					Destroy(IBAction* pAction) const { };
	virtual void					Interrupt(IBAction* pAction) const { Finish(pAction, true); };

protected:
	string							m_sName;
	class IBPlanner*				m_pPlanner;

	vector<string>					m_aVarNames;

	vector<IBFactCondDef>			m_aPreCondDef;
	vector<IBFactCondDef>			m_aPostCondDef;
};

#endif
