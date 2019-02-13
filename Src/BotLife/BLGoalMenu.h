#ifndef __BLGOALMENU_H__
#define __BLGOALMENU_H__

#include "Utils.h"
#include "Canvas.h"
#include "BLGoal.h"

class CanvasBase;
class BLSquare;
class IBObject;
class BLBot;

class BLGoalMenu
{
	public:
		BLGoalMenu(CanvasBase& oParent, BLBot& oBot);
		~BLGoalMenu();

		void SetVisible(bool bVisible) { m_bVisible = bVisible; }
		bool IsVisible() const { return m_bVisible; }

		const vector<BLGoal>& GetGoals() const { return m_aGoals; }

		void ConstructFromCase(const BLSquare* pSquare, const BLSquare* pSelectSquare);

		void UpdatePos();

		void Update();
		bool Click();

		void Draw() const;

	private:
		Canvas m_oCanva;
		BLBot& m_oBot;
		int m_iI;
		int m_iJ;
		bool m_bVisible;
		vector<BLGoal> m_aGoals;

	private:
		static int s_iYL;
		static int s_iTextHeight;
		static Color s_cBackGroundColor;
		static Color s_cForeGroundColor;
		static Color s_cNormalTextColor;
		static Color s_cMouseTextColor;
};



#endif
