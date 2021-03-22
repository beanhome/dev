#ifndef __IBLOGFACT_H__
#define __IBLOGFACT_H__

#include "IBLogBox.h"
#include "Utils.h"
#include "Color.h"
#include "Canvas.h"

class IBLogFact : public IBLogBox
{
	public:
		IBLogFact(const class IBFact* pFact);
		virtual ~IBLogFact();

	public:
		virtual void		Draw(Canvas& oCanvas, sint32 x, sint32 y) override;

	protected:
		virtual void		Size(Canvas& oCanvas, sint32& w, sint32& h) override;

	private:
		const class IBFact* m_pFact;
};

#endif
