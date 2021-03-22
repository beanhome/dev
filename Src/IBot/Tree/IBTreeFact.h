#ifndef __IBTreeFACT_H__
#define __IBTreeFACT_H__

#include "IBTreeBox.h"
#include "Utils.h"
#include "Color.h"
#include "Canvas.h"

class IBTreeFact : public IBTreeBox
{
	public:
		IBTreeFact(const class IBFact* pFact);
		virtual ~IBTreeFact();

	public:
		virtual void		Draw(Canvas& oCanvas, sint32 x, sint32 y) override;

	protected:
		virtual void		Size(Canvas& oCanvas, sint32& w, sint32& h) override;

	private:
		const class IBFact* m_pFact;
};

#endif
