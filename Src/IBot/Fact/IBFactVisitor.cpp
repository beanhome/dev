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

	while (HasChildren(LastFact()))
	{
		m_Stack.push_back(IBFactVisitor::Iterator(LastFact()));
	}

	return LastFact();
}

bool IBFactVisitor::HasChildren(const IBFact* pFact) const
{
	if (pFact->GetCauseAction().size() == 0)
		return false;

	for (ActionSet::const_iterator it = pFact->GetCauseAction().begin() ; it != pFact->GetCauseAction().end() ; ++it)
	{
		if ((*it)->GetPreCond().size() > 0)
			return true;
	}

	return false;
}

IBFact* IBFactVisitor::Get()
{
	return NULL;
}

bool IBFactVisitor::NextChild()
{
	if (m_Stack.size() > 0)
	{
		Iterator& Last = m_Stack[m_Stack.size()-1];
		const IBFact* pFact = Last.m_pFact;
		int& id = Last.m_iPreCondId;
		IBAction* pAction = *(Last.m_itCauseAction);

		if (++id < (int)pAction->GetPreCond().size())
			return true;

		id = 0;
		while (++Last.m_itCauseAction != pFact->GetCauseAction().end()
			&& (*Last.m_itCauseAction)->GetPreCond().size() == 0)
		{}

		return (Last.m_itCauseAction != pFact->GetCauseAction().end());
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
		Iterator& Last = m_Stack[m_Stack.size()-1];
		int id = Last.m_iPreCondId;
		return ((*Last.m_itCauseAction)->GetPreCond()[id]);
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
		while (HasChildren(LastFact()))
		{
			m_Stack.push_back(IBFactVisitor::Iterator(LastFact()));
		}

		return LastFact();
	}
}

