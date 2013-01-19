#ifndef __IBACTION_H__
#define __IBACTION_H__

#include "Utils.h"
#include "Fact/IBFact.h"

class IBActionDef;
struct FactCondDef;
class IBPlannerGraph;

class IBAction
{
	public:
		IBAction(IBActionDef* pDef);
		~IBAction();

		enum State
		{
			IBA_Init,
			IBA_Unresolved,
			IBA_Start,
			IBA_Execute,
			IBA_End,
			IBA_Finish,
			IBA_Destroy
		};

		typedef map<string, void*> VarMap;
		typedef pair<string, void*> VarPair;

		friend class IBPlannerGraph;

	public:
		State					GetState() const { return m_eState; }
		void					SetState(State state) { m_eState = state; }

		const VarMap&			GetVariables() const { return m_aVariables; }
		void*					FindVariables(const string& name) const;
		void					SetVariable(const string& name, void* val);

		const IBActionDef*		GetDef() const { return m_pDef; }

		const vector<IBFact*>&	GetPreCond() const { return m_aPreCond; }

		void					Start();
		void					Execute();
		void					Finish();

		void					AddPostCond(uint i, IBFact* pPostCond);
		void					AddPreCond(uint i, IBFact* pPreCond);
		void					AddPreCond(IBFact* pPreCond);

		const FactCondDef&		GetPostConfDefFromFact(IBFact* pPostCond) const;
		const FactCondDef&		GetPreConfDefFromFact(IBFact* pPreCond) const;

		void					ResolveVariableName(uint i, IBFact* pPreCond);
		void					AffectPreCondVariable(const string& name, void* data);
		void					AffectPostCondVariable(const string& name, void* data);

		void					ResolvePreCondVariable();
		void					ResolvePostCondVariable();
		void					ResolveVariable();

		State					Resolve(IBPlanner* pPlanner);
		float					Valuate();

		int						GetExecCounter() const { return m_iExecCount; }

	private:
		IBActionDef*			m_pDef;

		State					m_eState;
		int						m_iExecCount;
		
		VarMap					m_aVariables;
		vector<IBFact*>			m_aPreCond;
		vector<IBFact*>			m_aPostCond;
};

#endif
