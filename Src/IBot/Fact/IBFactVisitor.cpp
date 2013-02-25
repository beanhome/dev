#include "IBFactVisitor.h"

#include "Action\IBAction.h"
#include "IBPlanner.h"

IBFactVisitor::IBFactVisitor(const IBPlanner& planner)
	: m_oPlanner(planner)
{

}

const IBFact* IBFactVisitor::Begin()
{
	m_Stack.clear();

	m_itGoals = m_oPlanner.GetGoals().begin();

	if (m_itGoals == m_oPlanner.GetGoals().end())
		return NULL;

	while (LastFact()->GetCauseAction() != NULL && LastFact()->GetCauseAction()->GetPreCond().size() > 0)
	{
		m_Stack.push_back(IBFactVisitor::Iterator(LastFact(), 0));
	}

	return LastFact();
}

/*
IBFact* IBFactVisitor::Back()
{

}

IBFact* IBFactVisitor::End()
{
	return NULL;
}
*/

IBFact* IBFactVisitor::Get()
{
	return NULL;
}

bool IBFactVisitor::NextChild()
{
	if (m_Stack.size() > 0)
	{
		int& id = m_Stack[m_Stack.size()-1].m_iId;
		const IBFact* pFact = m_Stack[m_Stack.size()-1].m_pFact;
		return (++id < (int)pFact->GetCauseAction()->GetPreCond().size());
	}
	else
	{
		return (++m_itGoals != m_oPlanner.GetGoals().end());
	}
}

const IBFact* IBFactVisitor::LastFact()
{
	if (m_Stack.size() > 0)
	{
		int id = m_Stack[m_Stack.size()-1].m_iId;
		const IBFact* pFact = m_Stack[m_Stack.size()-1].m_pFact;
		return (pFact->GetCauseAction()->GetPreCond()[id]);
	}
	else
	{
		return (*m_itGoals);
	}
}


const IBFact* IBFactVisitor::Next()
{
	// ici j'ai fait tout ce que j'avais à faire avec le dernier node

	// -> on passe à l'enfant suivant
	if (NextChild() == false)
	{
		// on a parcouru tout les enfants

		if (m_Stack.size() == 0)
			return NULL;

		// -> On pop
		m_Stack.pop_back();

		// -> on s'occupe du parent
		return LastFact();
	}
	else
	{
		// on push tout les enfants possible
		while (LastFact()->GetCauseAction() != NULL && LastFact()->GetCauseAction()->GetPreCond().size() > 0)
		{
			m_Stack.push_back(IBFactVisitor::Iterator(LastFact(), 0));
		}

		return LastFact();
	}
}

/*
IBFact* IBFactVisitor::Prev()
{
	return NULL;
}
*/
