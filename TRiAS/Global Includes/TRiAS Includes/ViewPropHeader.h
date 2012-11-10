// @doc 
// @module ViewPropHeader.h | Diverse Eigenschaften einer Ansicht lesen

#if !defined(_VIEWPROPHEADER_H__E131BE67_BDBE_11D2_95B3_006008447800__INCLUDED_)
#define _VIEWPROPHEADER_H__E131BE67_BDBE_11D2_95B3_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <HeaderEntry.h>

class _TRIAS01_ENTRY CViewPropHeader
{
private:
	HPROJECT m_hPr;

public:
	CViewPropHeader (HPROJECT hPr);

	INT_PTR GetMCode(LPCSTR pcEntry);

	LONG GetBMasstab (LPCSTR pcView);
	string GetDescription (LPCSTR pcView);
	HRESULT GetContainer (LPCSTR pcView, double *plCont);
};

#endif // !defined(_VIEWPROPHEADER_H__E131BE67_BDBE_11D2_95B3_006008447800__INCLUDED_)
