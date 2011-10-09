#include "FEventMap.h"

FEventMap::FEventMap()
{
}

FEventMap::~FEventMap()
{
	EventByAdMap::iterator begin = m_aEventByAd.begin();
	EventByAdMap::iterator end = m_aEventByAd.end();
	EventByAdMap::iterator it;
	
	for (it = begin ; it != end ; ++it)
	{
		delete (it->first);
	}
}

FEvent* FEventMap::Add()
{
	FEvent* pEvent = new FEvent();
	m_aEventByAd.insert(EventByAdPair(pEvent, 1));
	m_aEventById.insert(EventByIdPair(pEvent->m_uId, pEvent));

	return pEvent;
}

FEvent* FEventMap::Add(uint id)
{
	FEvent* pEvent = NULL;
	EventByIdMap::iterator itid = m_aEventById.find(id);
	if (itid != m_aEventById.end())
	{
		pEvent = itid->second;

		EventByAdMap::iterator itad = m_aEventByAd.find(pEvent);
		assert(itad != m_aEventByAd.end());
		itad->second++;
	}
	else
	{
		pEvent = new FEvent(id);
		m_aEventByAd.insert(EventByAdPair(pEvent, 1));
		m_aEventById.insert(EventByIdPair(pEvent->m_uId, pEvent));
	}

	return pEvent;
}

FEvent* FEventMap::Add(FEvent* pEvent)
{
	EventByAdMap::iterator itad = m_aEventByAd.find(pEvent);
	assert(itad != m_aEventByAd.end());
	itad->second++;

	return pEvent;
}


FEvent* FEventMap::Add(PGresult* res, int iTuple, bool bFull)
{
	FEvent* pEvent = new FEvent(res, iTuple, bFull);
	m_aEventByAd.insert(EventByAdPair(pEvent, 1));
	m_aEventById.insert(EventByIdPair(pEvent->m_uId, pEvent));

	return pEvent;
}

void FEventMap::Remove(uint id)
{
	FEvent* pEvent = NULL;
	EventByIdMap::iterator itid = m_aEventById.find(id);
	assert (itid != m_aEventById.end());
	pEvent = itid->second;

	EventByAdMap::iterator itad = m_aEventByAd.find(pEvent);
	assert(itad != m_aEventByAd.end());
	if (--(itad->second) == 0)
	{
		delete pEvent;
		m_aEventByAd.erase(itad);
		m_aEventById.erase(itid);
	}
}

void FEventMap::Remove(FEvent* pEvent)
{
	EventByAdMap::iterator itad = m_aEventByAd.find(pEvent);
	assert(itad != m_aEventByAd.end());

	EventByIdMap::iterator itid = m_aEventById.find(pEvent->m_uId);
	assert (itid != m_aEventById.end());

	if (--(itad->second) == 0)
	{
		delete pEvent;
		m_aEventByAd.erase(itad);
		m_aEventById.erase(itid);
	}
}

void FEventMap::ChangeId(FEvent* pEvent, uint iLastId)
{
	if (pEvent->GetKey() != iLastId)
	{
		EventByIdMap::iterator begin = m_aEventById.lower_bound(iLastId);
		EventByIdMap::iterator end = m_aEventById.upper_bound(iLastId);
		EventByIdMap::iterator it;

		for (it = begin ; it != end ; ++it)
		{
			if (it->second == pEvent)
			{
				m_aEventById.erase(it);
				m_aEventById.insert(EventByIdPair(pEvent->m_uId, pEvent));
				break;
			}
		}
	}
}
