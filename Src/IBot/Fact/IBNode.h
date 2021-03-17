#ifndef __IBNODE_H__
#define __IBNODE_H__

#include "Types.h"
#include "IBCost.h"

class IBNode
{
	public:
		friend class IBPlanner;
		friend class IBAction;
		friend class IBFact;

	protected:
		IBNode(class IBPlanner* pPlanner, class IBAction* pEffectAction = nullptr);
		IBNode(class IBPlanner* pPlanner, const vector<class IBFact*>& Node);
		virtual ~IBNode();

	public:
		bool operator==(const IBNode& other) const;

		void							Update();
		void							Step(const class IBPlanner* pPlanner);
		void							Destroy();

		const FactSet&					GetFacts() const;
		uint							Size() const;
		void							AddFact(class IBFact* pFact);
		void							RemFact(class IBFact* pFact);

		//bool							FactIsResolvableBy(const class IBFact* pFact, const class IBActionDef* pActionDef) const;

		class IBAction*					GetAction() const { return m_pAction; }

		bool							IsTrue() const;
		bool							IsEqual(const IBNode* pOther) const;

		IBCost							GetCost() const;
		int								GetFactCost() const;
		float							GetActionCost() const;

		void							UpdateDuplicats();
		IBNode*					FindFirstDuplicat(const IBNode* pModel) const;
		IBNode*					GetBestDuplicat();

		NodeSet&					GetDuplicats() { return m_aDuplicats; }
		void							AddDuplicat(IBNode* pDuplicat);
		void							RemDuplicat(IBNode* pDuplicat);
		bool							IsDuplicat(const IBNode* pDuplicat) const;

		IBNode*					GetBestNode() const;
		bool							CheckCompatibility(const IBFact* pFact) const;
		bool							CheckInnerCompatibility() const;

	protected:
		class IBPlanner*				m_pPlanner;
		FactSet							m_aFacts;
		class IBAction*					m_pAction;
		NodeSet					m_aDuplicats;
};

#endif
