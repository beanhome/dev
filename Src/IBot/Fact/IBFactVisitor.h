#ifndef __IBFACTVISITOR_H__
#define __IBFACTVISITOR_H__

#include "Utils.h"
#include "IBFact.h"

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
			int				m_iId;

			Iterator(const IBFact* parent, int id) : m_pFact(parent), m_iId(id) {}
		};

		IBFactVisitor(const IBFact* ref, const IBAction* parent, int id);

		bool NextChild();
		const IBFact* LastFact();

		void Set(const IBFactVisitor& fact);

	public:
		const IBFact* Begin();
		//IBFact* Back();
		//IBFact* End();
		IBFact* Get();
		const IBFact* Next();
		IBFact* Prev();

	private:
		const IBPlanner& m_oPlanner;
		vector<Iterator> m_Stack;

		FactSet::const_iterator m_itGoals;
};

#endif
