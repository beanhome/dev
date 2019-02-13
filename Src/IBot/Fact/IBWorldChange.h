#ifndef __IBFACTPACK_H__
#define __IBFACTPACK_H__

#include "Utils.h"
#include "IBCost.h"

typedef set<class IBFact*>		FactSet;
typedef set<class IBAction*>		ActionSet;

class IBWorldChange
{
	public:
		friend class IBPlanner;
		friend class IBAction;
		friend class IBFact;

	protected:
		IBWorldChange(class IBPlanner* pPlanner, class IBAction* pEffectAction = nullptr);
		IBWorldChange(class IBPlanner* pPlanner, const vector<class IBFact*>& WorldChange);
		virtual ~IBWorldChange();

	public:
		bool operator==(const IBWorldChange& other) const;

		void								Update();

		void								Step(const class IBPlanner* pPlanner);
		//void								Clean();

		void								Destroy();

		const FactSet&					GetFacts() const;
		uint								Size() const;
		void								AddFact(class IBFact* pFact);
		void								RemFact(class IBFact* pFact);
		
		bool								FactIsResolvableBy(const class IBFact* pFact, const class IBActionDef* pActionDef) const;

		class IBAction*					GetAction() const { return m_pAction; }

		bool								IsTrue() const;
		IBCost							GetCost() const;

		IBWorldChange*					GetBestWorldChange() const;
		bool								CheckCompatibility(const IBFact* pFact) const;
		bool								CheckInnerCompatibility() const;


	protected:
		class IBPlanner*					m_pPlanner;
		FactSet							m_aFacts;
		class IBAction*					m_pAction;
};

#endif
