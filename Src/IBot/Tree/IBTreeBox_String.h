#ifndef __IBTREEBOX_STRING_H__
#define __IBTREEBOX_STRING_H__

#include "IBTreeBox.h"
#include "Utils.h"
#include "Color.h"
#include "Canvas.h"

class IBTreeBox_String : public IBTreeBox
{
	public:
		IBTreeBox_String(Canvas& oCanvas, IBTreeBox* pParent);
		virtual ~IBTreeBox_String();

	public:
		void				SetString(const string& str) { m_sString = str; UpdateSize(); }
		const string&		GetString() const { return m_sString; }

		void				SetFont(FontResource* pFont) { m_pFont = pFont; UpdateSize(); }
		FontResource*		GetFont() const { return m_pFont; }

		void				SetColor(const Color& oColor) { m_oColor = oColor; }
		const Color&		GetColor() const { return m_oColor; }

		virtual void		Draw() const override;

	protected:
		virtual void		ComputeSize() override;

	protected:
		string m_sString;

		class FontResource* m_pFont;
		Color m_oColor;
};

#endif
