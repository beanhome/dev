#ifndef __BLPath_H__
#define __BLPath_H__

#include "Utils.h"
#include "World/BLObject.h"
#include "Path.h"

class BLPath : public BLObject, public Path
{
	public:
		BLPath(const string& name);
		BLPath(const string& name, const Vector2& start, const deque<Vector2>& oPath);
		virtual ~BLPath();
		
		BLObject* Clone() const { return new BLPath(*this); }

		virtual void FormatData() const;
		virtual void Print() const;

		void ResetStep();
		bool NextStep();
		Vector2 GetCurrentStep() const;

	private:
		uint32 m_iCurrentStep;
};

#endif
