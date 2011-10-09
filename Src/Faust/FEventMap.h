#ifndef FEVENTMAP_H
#define FEVENTMAP_H

#include "Utils.h"

#include "FEvent.h"

class FEventMap
{
	public:
		FEventMap();
		~FEventMap();

	public:
		FEvent*		Add();
		FEvent*		Add(uint id);
		FEvent*		Add(FEvent* pEvent);
		FEvent*		Add(PGresult* res, int iTuple, bool bFull = false);
		void		Remove(uint id);
		void		Remove(FEvent* pEvent);

		void		ChangeId(FEvent* pEvent, uint iLastId);

	private:

	private:
		typedef map<FEvent*, uint>		EventByAdMap;
		typedef pair<FEvent*, uint>		EventByAdPair;
		EventByAdMap					m_aEventByAd;

		typedef multimap<uint, FEvent*>	EventByIdMap;
		typedef pair<uint, FEvent*>		EventByIdPair;
		EventByIdMap					m_aEventById;


};

#endif