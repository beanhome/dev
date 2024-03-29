#ifndef __IBPLANNERDISPLAY_H__
#define __IBPLANNERDISPLAY_H__

class IBPlannerDisplay
{
	public:
		IBPlannerDisplay(const class IBPlanner& oPlanner);
		virtual ~IBPlannerDisplay();

	public:
		virtual void RefreshTree() {}
		virtual void Update(float dt) = 0;
		virtual void OnClick() {}
		virtual void DrawGraph() = 0;

	protected:
		const class IBPlanner& m_oPlanner;
};

#endif
