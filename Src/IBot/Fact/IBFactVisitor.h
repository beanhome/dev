#ifndef __IBFACTVISITOR_H__
#define __IBFACTVISITOR_H__

#include "Utils.h"
#include "IBFact.h"
#include "Action/IBAction.h"

class IBFact;
class IBAction;
class IBPlanner;

class IBFactVisitor
{
	public:
		friend class IBAction;

	public:
		IBFactVisitor(const IBPlanner& planner);

	private:
		struct Iterator 
		{
			const IBFact*	m_pFact;
			ActionSet::const_iterator m_itCauseAction;
			int				m_iPreCondId;

			Iterator(const IBFact* parent)
				: m_pFact(parent), m_itCauseAction(parent->GetCauseAction().begin()), m_iPreCondId(0)
			{
				while ((*m_itCauseAction)->GetPreCond().size() == 0)
				{
					++m_itCauseAction;
					ASSERT(m_itCauseAction != m_pFact->GetCauseAction().end());
				}
			}
		};

		IBFactVisitor(const IBFact* ref, const IBAction* parent, int id);

		bool NextChild();
		const IBFact* LastFact();

		void Set(const IBFactVisitor& fact);

		bool HasChildren(const IBFact* pFact) const;

	public:
		const IBFact* Begin();
		IBFact* Get();
		const IBFact* Next();

	private:
		const IBPlanner& m_oPlanner;
		vector<Iterator> m_Stack;

		FactSet::const_iterator m_itGoals;
};

#endif
