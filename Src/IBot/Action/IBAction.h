#ifndef __IBACTION_H__
#define __IBACTION_H__

#include "Utils.h"
#include "Fact/IBFact.h"
//#include "Action/IBActionDef.h"

class IBActionDef;
struct FactCondDef;
class IBPlannerGraph;

class IBAction
{
	public:
		IBAction(IBActionDef* pDef);
		~IBAction();

		typedef map<string, void*> VarMap;
		typedef pair<string, void*> VarPair;

		friend class IBPlannerGraph;

	public:
		const VarMap&			GetVariables() const { return m_aVariables; }
		void*					FindVariables(const string& name) const;
		void					SetVariable(const string& name, void* val);

		const IBActionDef*		GetDef() const { return m_pDef; }

		const vector<IBFact*>&	GetPreCond() const { return m_aPreCond; }

		bool					Test();

		void					Execute() {}

		void					AddPostCond(uint i, IBFact* pPostCond);
		void					AddPreCond(uint i, IBFact* pPreCond);

		const FactCondDef&		GetPostConfDefFromFact(IBFact* pPostCond) const;
		const FactCondDef&		GetPreConfDefFromFact(IBFact* pPreCond) const;

		void					ResolveVariableName(uint i, IBFact* pPreCond);
		void					AffectPreCondVariable(const string& name, void* data);

		void					ResolvePreCondVariable();

		bool					Resolve(IBPlanner* pPlanner);
		float					Valuate();

		void					Print(int tab) const;
		void					PrintVar(const IBAction::VarMap& aUserData, int tab) const;
		void					Draw(CanvasBase& canva, int& x, int& y, const IBFact* pFact) const;

	private:
		IBActionDef*			m_pDef;
		
		VarMap					m_aVariables;
		vector<IBFact*>			m_aPreCond;
		vector<IBFact*>			m_aPostCond;
};

#endif
