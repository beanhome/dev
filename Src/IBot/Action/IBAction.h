#ifndef __IBACTION_H__
#define __IBACTION_H__

#include "Utils.h"
#include "Fact/IBFact.h"
//#include "Action/IBActionDef.h"

class IBActionDef;
struct FactCondDef;

class IBAction
{
	public:
		IBAction(IBActionDef* pDef);
		~IBAction();

		typedef map<string, void*> VarMap;
		typedef pair<string, void*> VarPair;

	public:
		const VarMap&			GetVariables() const { return m_aVariables; }
		void*					FindVariables(const string& name) const;
		void					SetVariable(const string& name, void* val);

		bool					Test();

		void					Execute() {}

		void					AddPostCond(uint i, IBFact* pPostCond);
		void					AddPreCond(uint i, IBFact* pPreCond);


		void					ResolveVariableName(uint i, IBFact* pPreCond);
		void					AffectPreCondVariable(const string& name, void* data);

		void					ResolvePreCondVariable();

		bool					Resolve(IBPlanner* pPlanner);
		float					Valuate();

		void					Print(int tab) const;
		void					PrintVar(const IBAction::VarMap& aUserData, int tab) const;

private:
		IBActionDef*			m_pDef;
		
		VarMap					m_aVariables;
		vector<IBFact*>			m_aPreCond;
		vector<IBFact*>			m_aPostCond;
};

#endif
