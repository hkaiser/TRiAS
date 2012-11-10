// @doc 
// @module ViewPropHeader.cpp | Diverse Eigenschaften einer Ansicht lesen

#include "trias01p.hxx"

#include "Strings.h"

#include <NativeView.h>
#include <ViewPropHeader.h>
#include <ScaleHeader.h>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

using namespace trias_nativeheader;
using namespace trias_nativeview;

/////////////////////////////////////////////////////////////////////////////
// StringKonstanten
const TCHAR g_cbBMasstabMCode[] = TEXT("BMasstabMCode");
const TCHAR g_cbCaptionMCode[] = TEXT("CaptionMCode");
const TCHAR g_cbSichtContMCode[] = TEXT("SichtContMCode");

/////////////////////////////////////////////////////////////////////////////
// 
CViewPropHeader::CViewPropHeader (HPROJECT hPr)
	: m_hPr(hPr)
{
}

INT_PTR CViewPropHeader::GetMCode(LPCSTR pcEntry)
{
	TX_ASSERT(NULL != pcEntry);

CDBHeader Hdr (m_hPr, pcEntry);

	return Hdr.GetHeaderLong (0L);
}

LONG CViewPropHeader::GetBMasstab (LPCSTR pcView)
{
CNativeView View (m_hPr, pcView);
INT_PTR lMCode = GetMCode(g_cbBMasstabMCode);

	if (0 == lMCode)
		return 0L;		// überhaupt kein Bezugsmasstab vorhanden

string str (g_cbNil);

	if (FAILED(View.GetTextMerkmal (lMCode, str)))
		return 0L;		// diese Ansicht hat keinen BMasstab
	return strtol (str.c_str(), NULL, 10);
}

string CViewPropHeader::GetDescription (LPCSTR pcView)
{
CNativeView View (m_hPr, pcView);
INT_PTR lMCode = GetMCode(g_cbCaptionMCode);
string str (g_cbNil);

	if (0 == lMCode)
		return str;	// überhaupt keine AnsichtsBeschreibung vorhanden

	View.GetTextMerkmal (lMCode, str);
	return str;
}

HRESULT CViewPropHeader::GetContainer (LPCSTR pcView, double *plCont)
{
	if (NULL == plCont)
		return E_POINTER;

CNativeView View (m_hPr, pcView);
INT_PTR lMCode = GetMCode(g_cbSichtContMCode);

	if (0 == lMCode)
		return E_FAIL;		// gar kein SichtContainer definiert

string str (g_cbNil);

	if (FAILED(View.GetTextMerkmal (lMCode, str)))
		return E_FAIL;		// diese Ansicht hat keinen Conatiner

// ObjContainer neu aufbauen
char *cptr = NULL;

	strtoul (str.c_str(), &cptr, 10);		// erste Zahl überspringen
	plCont[0] = strtoul (cptr+1, &cptr, 10);
	plCont[2] = strtoul (cptr+1, &cptr, 10);
	plCont[1] = strtoul (cptr+1, &cptr, 10);
	plCont[3] = strtoul (cptr+1, NULL, 10);

// Koordinaten in RealKoordinaten umrechnen
CScaleHeader Hdr (m_hPr);

	Hdr.UnScale (plCont[0], plCont[2]);
	Hdr.UnScale (plCont[1], plCont[3]);
	return S_OK;
}
