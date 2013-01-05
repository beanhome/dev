#ifndef __IBPLANNERDISPLAY_H__
#define __IBPLANNERDISPLAY_H__

class IBPlanner;

class IBPlannerDisplay
{
	public:
		IBPlannerDisplay(const IBPlanner& oPlanner);
		virtual ~IBPlannerDisplay();

	public:
		virtual void DrawGraph() = 0;

	protected:
		const IBPlanner& m_oPlanner;
};

#endif
