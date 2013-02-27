#ifndef __BLGOALMENU_H__
#define __BLGOALMENU_H__

#include "Utils.h"
#include "Canvas.h"
#include "IBGoal.h"

class CanvasBase;
class BLSquare;
class IBObject;

class BLGoalMenu
{
	public:
		BLGoalMenu(CanvasBase& oParent);
		~BLGoalMenu();

		void SetVisible(bool bVisible) { m_bVisible = bVisible; }
		bool IsVisible() const { return m_bVisible; }

		const vector<IBGoal>& GetGoals() const { return m_aGoals; }

		void ConstructFromCase(const BLSquare& pSquare, int I, int J);

		void SetPos(sint32 x, sint32 y);

		void Update();

		void Draw() const;

	private:
		Canvas m_oCanva;
		bool m_bVisible;
		vector<IBGoal> m_aGoals;
		vector<IBObject*> m_aTempObject;
};



#endif