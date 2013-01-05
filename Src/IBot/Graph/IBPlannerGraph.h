#ifndef __IBPLANNERGRAPH_H__
#define __IBPLANNERGRAPH_H__

#include "Utils.h"
#include "Color.h"
#include "IBPlannerDisplay.h"

//#include "Fact/IBFactLibrary.h"
//#include "Fact/IBFact.h"

//class IBFactDef;

class IBFact;
class IBAction;

class IBPlanner;
class CanvasBase;

class IBGBox;

class IBCube;

class IBGBoxBase
{
	public:
		IBGBoxBase();
		IBGBoxBase(IBGBox* pMainBox);

		sint16 GetX() const { return x; }
		sint16 GetY() const { return y; }
		sint16 GetW() const { return w; }
		sint16 GetH() const { return h; }

		void SetX(sint16 _x) { x = _x; }
		void SetY(sint16 _y) { y = _y; }
		void SetW(sint16 _w) { w = _w; }
		void SetH(sint16 _h) { h = _h; }

		IBGBox* GetMainBox() { return m_pMainBox; }

		void Draw(CanvasBase& canva, const Color& color) const;

	protected:
		IBGBox* m_pMainBox;
		
		sint16 x, y;
		sint16 w, h;
};


class IBGFactBox : public IBGBoxBase
{
public:
	IBGFactBox(IBGBox* pMainBox, IBFact* pFact);

	IBFact*				GetFact() { return m_pFact; }
	IBAction*			GetCauseAction();

	void				SetCauseBox(IBGBox* pBox) { m_pCauseBox = pBox; }
	IBGBox*				GetCauseBox() { return m_pCauseBox; }

	void				Draw(CanvasBase& canva) const;

private:
	IBFact* m_pFact;
	IBGBox* m_pCauseBox;
};

class IBGActionBox : public IBGBoxBase
{
	public:
		IBGActionBox(IBGBox* pMainBox, IBAction* pAction);

		IBAction*		GetAction() { return m_pAction; }
		void			SetAction(IBAction* pAction) { m_pAction = pAction; }
		
		IBGFactBox*		GetPostCondBox() { return m_pPostCond; }
		IBFact*			GetPostCond() { return m_pPostCond->GetFact(); }
		IBGBox*			GetPostCondMainBox() { return m_pPostCond->GetMainBox(); }

		void			Draw(CanvasBase& canva) const;

	private:
		IBAction* m_pAction;
		IBGFactBox* m_pPostCond;
};

class IBGBox : public IBGBoxBase
{
	public:
		IBGBox();
		//IBGBox(IBGActionBox* pActionBox);
		IBGBox(IBAction* pAction);
		~IBGBox();

		IBGActionBox* GetActionBox() { return m_pActionBox; }
		vector<IBGFactBox*>& GetFactBox() { return m_aFactBox; }

		//void			SetAction(IBAction* pAction);
		void			AddFactCond(IBFact* pFact);
		
		void			Draw(CanvasBase& canva) const;

	private:
		vector<IBGFactBox*>	m_aFactBox;
		IBGActionBox*		m_pActionBox;
};


class IBPlannerGraph : public IBPlannerDisplay
{
	public:
		IBPlannerGraph(const IBPlanner& oPlanner, CanvasBase& oWorldCanva, CanvasBase& oGraphCanva);
		virtual ~IBPlannerGraph();

	public:
		virtual void		DrawGraph();

		void				Init(const IBPlanner& oPlanner, CanvasBase& canva);
		//void				AddBox(const IBPlanner& oPlanner, IBAction* pAction, Box* pParentBox, uint col);
		void				DrawCube(const IBCube* pCube, CanvasBase& canva, int i, int j);
		void				Insert(IBGBox* pBox, uint col);

	private:
		vector<vector<IBGBox*>> m_aBox;
		CanvasBase&			m_oWorldCanva;
		CanvasBase&			m_oGraphCanva;

	public:
		static const uint		s_iMargin;
		static const uint		s_iFactWidth;
		static const uint		s_iFactTitleHeight;
		static const uint		s_iFactVarHeight;
		static const uint		s_iFactHeight; // to del
		static const uint		s_iFactMinSpace; // to del
		static const uint		s_iLinkWidth;
		static const uint		s_iActionWidth;
		static const uint		s_iActionMinHeight;
		static const uint		s_iActionTitleHeight;
		static const uint		s_iActionAnchorHeight;
		static const uint		s_iActionVarHeight;
		static       uint		s_iBoxWidth;
		static       uint		s_iBoxMinHeight;
		static const uint		s_iBoxSpace;

		static const Color		s_oActionColor;
		static const Color		s_oFactColor;
		static const Color		s_oFalseFactColor;
		static const Color		s_oLinkColor;
		static const Color		s_oBoxColor;

};

#endif
