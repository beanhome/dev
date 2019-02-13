#ifndef __IBPLANNERDISPLAY_H__
#define __IBPLANNERDISPLAY_H__

class IBPlannerDisplay
{
	public:
		IBPlannerDisplay(const class IBPlanner& oPlanner);
		virtual ~IBPlannerDisplay();

	public:
		virtual void DrawGraph() = 0;

	protected:
		const class IBPlanner& m_oPlanner;
};

#endif
