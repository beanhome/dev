#ifndef __IBCOST_H__
#define __IBCOST_H__

#include "Utils.h"

class IBCost
{
	public:
		IBCost();
		IBCost(const IBCost& other);
		IBCost(float fActionCost, sint32 iFactCost);

		void Reset();

		bool operator==(const IBCost& other) const;
		bool operator!=(const IBCost& other) const;
		bool operator<(const IBCost& other) const;
		bool operator<=(const IBCost& other) const;
		bool operator>(const IBCost& other) const;
		bool operator>=(const IBCost& other) const;

		IBCost operator+(const IBCost& other) const;
		IBCost& operator+=(const IBCost& other);

		float GetActionCost() const;
		sint32 GetFactCost() const;

		void SetCost(float fActionCost, sint32 iFactCost);
		void SetActionCost(float fActionCost);
		void SetFactCost(sint32 iFactCost);

		const string& GetText() const;

	private:
		void UpdateText();

		float GetUniCost() const;

	private:
		float m_fActionCost;
		sint32 m_iFactCost;

		string m_sText;

	public:
		static IBCost MaxCost;
		static float fFactCoeff;
		static float fActionCoeff;
};



#endif
