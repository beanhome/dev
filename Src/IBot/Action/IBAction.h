#ifndef __IBACTION_H__
#define __IBACTION_H__

#include "Utils.h"
#include "Fact/IBFact.h"
//#include "Fact/IBFactVisitor.h"

class IBActionDef;
struct FactCondDef;
class IBObject;

class IBAction
{
	public:
		friend class IBPlanner;
		friend class IBFact;
		friend class IBActionLibrary;

	protected:
		IBAction(IBActionDef* pDef, IBFact* pPostCond1);
		virtual ~IBAction();

	public:
		enum State
		{
			IBA_Init,
			IBA_Unresolved,
			IBA_Start,
			IBA_Execute,
			IBA_Abort,
			IBA_End,
			IBA_Finish,
			IBA_Destroy,
			IBA_Destroyed,
		};

		typedef map<string, IBObject*> VarMap;
		typedef pair<string, IBObject*> VarPair;

	public:
		State					GetState() const { return m_eState; }
		void					SetState(State state) { m_eState = state; }

		const VarMap&			GetVariables() const { return m_aVariables; }
		IBObject*				FindVariables(const string& name) const;
		void					SetVariable(const string& name, IBObject* val);

		template <typename T>
		T*						FindVariables(const string& name) const;

		const IBActionDef*		GetDef() const { return m_pDef; }

		const vector<IBFact*>&	GetPreCond() const { return m_aPreCond; }
		const vector<IBFact*>&	GetPostCond() const { return m_aPostCond; }

		void*					GetUserData() { return m_pUserData; }
		void					SetUserData(void* pUserData) { m_pUserData = pUserData; }

		void					Start();
		void					Execute();
		void					Finish();

		void					AddPostCond(uint i, IBFact* pPostCond);
		void					RemPostCond(IBFact* pPostCond);

		void					AddPreCond(uint i, IBFact* pPreCond);
		void					AddPreCond(IBFact* pPreCond);

		const FactCondDef&		GetPostConfDefFromFact(IBFact* pPostCond) const;
		const FactCondDef&		GetPreConfDefFromFact(IBFact* pPreCond) const;

		void					ResolveVariableName(uint i, IBFact* pPreCond);
		void					AffectPreCondVariable(const string& name, IBObject* data);
		void					AffectPostCondVariable(const string& name, IBObject* data);

		void					SpreadPreCondVariable();
		void					SpreadPostCondVariable();
		void					SpreadVariable();
		void					ResolvePreCond();

		State					Resolve(IBPlanner* pPlanner);
		float					Valuate();

		void					PrepareToDelete();
		bool					IsReadyToDelete();
		bool					IsMarkToDelete() const { return m_bToDelete; }

		int						GetExecCounter() const { return m_iExecCount; }
		//friend class IBFactIterator;
		/*
		IBFactIterator			BeginFactIterator() const;
		IBFactIterator			BackFactIterator() const;
		IBFactIterator			EndFactIterator() const;
		IBFactIterator			NextFactIterator(const IBFactIterator& it) const;
		IBFactIterator			PrevFactIterator(const IBFactIterator& it) const;
		*/

	protected:
		IBActionDef*			m_pDef;

		State					m_eState;
		int						m_iExecCount;
		
		VarMap					m_aVariables;
		vector<IBFact*>			m_aPreCond;
		vector<IBFact*>			m_aPostCond;

		void*					m_pUserData;

		bool					m_bToDelete;
};

template <typename T>
T* IBAction::FindVariables(const string& name) const
{
	IBObject* pObj = FindVariables(name);
	if (pObj == NULL)
		return NULL;

	T* pTObj = dynamic_cast<T*>(pObj);
	ASSERT(pTObj != NULL);

	return pTObj;
}



#endif
