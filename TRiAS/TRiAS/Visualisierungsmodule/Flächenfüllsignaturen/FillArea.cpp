// FillArea.cpp : implementation file
//

#include "stdafx.h"

#include <vismguid.h>

#include "FillMode.h"
#include "FixupDC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern "C" HINSTANCE g_hInstance;

/////////////////////////////////////////////////////////////////////////////
// CFillArea

IMPLEMENT_DYNCREATE(CFillArea, CCmdTarget)

CFillArea::CFillArea()
{
	EnableAutomation();
	
// To keep the application running as long as an OLE automation 
//	object is active, the constructor calls AfxOleLockApp.
	AfxOleLockApp();

// Initialisierung der Member
	m_pPts = NULL;
	m_iCnt = 0;
	m_hPal = NULL;
}

CFillArea::~CFillArea()
{
	ResetPoints();

// To terminate the application when all objects created with
// 	with OLE automation, the destructor calls AfxOleUnlockApp.
	AfxOleUnlockApp();
}

void CFillArea::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}

// Sicherstellen, daß das Feld 'm_pPts' die geforderte Größe besitzt ----------
bool CFillArea::InitPoints (int iCnt)
{
	if (iCnt <= m_iCnt) {		// Feld ist ausreichend groß
		ASSERT(NULL != m_pPts);
		return true;
	}

// neues Feld anlegen
	ResetPoints();
	m_pPts = new CPoint [iCnt];
	if (NULL == m_pPts)
		return false;
	m_iCnt = iCnt;

return true;
}

// Punktfeld freigeben --------------------------------------------------------
void CFillArea::ResetPoints (void)
{
	DELETE_OBJ(m_pPts);
	m_iCnt = 0;
}

BEGIN_MESSAGE_MAP(CFillArea, CCmdTarget)
	//{{AFX_MSG_MAP(CFillArea)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CFillArea, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CFillArea)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

BEGIN_INTERFACE_MAP(CFillArea, CCmdTarget)
	INTERFACE_PART(CFillArea, IID_IVisModule, VisModule)
END_INTERFACE_MAP()

///////////////////////////////////////////////////////////////////////////////
// {07963854-3123-101C-BB62-00AA0018497C}
const char g_cbProgID[] = TEXT("TRiAS.FillSignatures.1");
const char g_cbFillMode[] = TEXT("fillmode");

IMPLEMENT_OLECREATE_EX(CFillArea, TEXT("TRiAS.FillSignatures.1"), 0x07963854, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C) 

// Registriert diesen VisModule -----------------------------------------------
bool RegisterVisModule (REFCLSID rclsid, LPCTSTR pcProgID, 
						HINSTANCE hInstance, UINT uiName, DWORD dwObjTypes);
bool UnRegisterVisModule (REFCLSID rclsid, LPCTSTR pcProgID);

BOOL CFillArea::
CFillAreaFactory::UpdateRegistry (BOOL fRegister)
{
	if (fRegister)
		return RegisterVisModule (CLSID_FillSignaturesVM, g_cbProgID, 
				g_hInstance, IDS_LONGCLASSNAME, OTFlaeche);
	else
		return UnRegisterVisModule (CLSID_FillSignaturesVM, g_cbProgID);
}

///////////////////////////////////////////////////////////////////////////////
// Member von IVisModule
STDMETHODIMP_(ULONG) CFillArea::
XVisModule::AddRef (void)
{
    METHOD_PROLOGUE(CFillArea, VisModule)
    return pThis->ExternalAddRef();
}

STDMETHODIMP_(ULONG) CFillArea::
XVisModule::Release (void)
{
    METHOD_PROLOGUE(CFillArea, VisModule)
    return pThis->ExternalRelease();
}

STDMETHODIMP CFillArea::
XVisModule::QueryInterface (REFIID iid, LPVOID *ppvObj)
{
    METHOD_PROLOGUE(CFillArea, VisModule)
    return (HRESULT)pThis->ExternalQueryInterface(&iid, ppvObj);
}

STDMETHODIMP CFillArea::
XVisModule::SymbolizeObject (HWND hWndM, long &rlONr, short &riOType, char *pBuffer, short iLen)
{
    METHOD_PROLOGUE(CFillArea, VisModule)
    return pThis->SymbolizeObject (hWndM, rlONr, riOType, pBuffer, iLen);
}

STDMETHODIMP CFillArea::
XVisModule::DrawObject (HWND hWndM, HDC hDC, HDC hTargetDC, long lONr, short &rfDrawFlags, VisInfo *pVI, char *pVisString)
{
    METHOD_PROLOGUE(CFillArea, VisModule)
	return pThis-> DrawObject(hWndM, hDC, hTargetDC, lONr, rfDrawFlags, pVI, pVisString);
}

STDMETHODIMP CFillArea::
XVisModule::QueryParameters (
		HWND hWndM, long lONr, VisInfo *pVI, char *pVisStr, 
		char *pBuffer, short iLen, short *piOTypes)
{
    METHOD_PROLOGUE(CFillArea, VisModule)
	return pThis->QueryParameters(hWndM, lONr, pVI, pVisStr, pBuffer, iLen, piOTypes);
}

// NotifikationsempfängerFunktionen -------------------------------------------
STDMETHODIMP_(void) CFillArea::
XVisModule::OnProjectChange (HWND hWndM, PROJECTCHANGE rgPC, char *pPrName)
{
    METHOD_PROLOGUE(CFillArea, VisModule)
	pThis->OnProjectChange(hWndM, rgPC, pPrName);
}

STDMETHODIMP_(void) CFillArea::
XVisModule::OnViewChange (HWND hWndM, VIEWCHANGE rgVC, char *pView)
{
    METHOD_PROLOGUE(CFillArea, VisModule)
	pThis->OnViewChange(hWndM, rgVC, pView);
}

STDMETHODIMP_(void) CFillArea::
XVisModule::OnPaletteChange (HWND hWndM, HPALETTE hPal)
{
    METHOD_PROLOGUE(CFillArea, VisModule)
	pThis->OnPaletteChange(hWndM, hPal);
}

/////////////////////////////////////////////////////////////////////////////
// CFillArea message handlers
void CFillArea::OnPaletteChange (HWND hWndM, HPALETTE hPal)
{
	m_hPal = hPal;		// Palette des Hauptfensters merken
}

void CFillArea::OnViewChange (HWND hWndM, VIEWCHANGE rgVC, char *pView)
{
	ResetPoints();
}

void CFillArea::OnProjectChange (HWND hWndM, PROJECTCHANGE rgPC, char *pPrName)
{
	__hWndM = hWndM;
	ResetPoints();
	if (rgPC == PROJECTCHANGE_CLOSED) 
		m_hPal = 0;	// alte Palette vergessen
}

HRESULT CFillArea::QueryParameters (HWND hWnd, long lONr, 
			VisInfo *pVI, char *pVisStr, char *pBuffer, short iLen, short *piOTypes)
{
CString strFmt;

	strFmt.LoadString (IDS_CUSTFORMAT);

	wsprintf (pBuffer, strFmt, g_cbFillMode);		// must save oldname
	*piOTypes = OTFlaeche;
	return NOERROR;
}

HRESULT CFillArea::SymbolizeObject (HWND hWndM, long &rlONr, 
			short &riOType, char *pBuffer, short iLen)
{
	return ResultFromScode(E_NOTIMPL);
}

// Ein Objekt soll gezeichnet werden ------------------------------------------
HRESULT CFillArea::DrawObject (HWND hWndM, HDC hDC, HDC hTargetDC, 
			long lONr, short &rfDrawFlags, VisInfo *pVI, char *pVisString)
{
// beim Blinken nicht zeichnen
	if (rfDrawFlags & (DF_Blinking|DF_Analyze))
		return ResultFromScode (VISMODULE_S_OBJECTISDRAWN);

// nur Flächen bearbeiten
	ASSERT(NULL != pVI);
	if (NULL == pVI || VT_Flaeche != pVI -> isA())
		return NOERROR;		// TRiAS soll zeichnen

// Flächen-Füllmode auswerten
	switch (static_cast<FVisInfo *>(pVI) -> Type()) {
	case FILLMODE_HORIZONTAL:
	case FILLMODE_VERTICAL:
		break;

	case FILLMODE_BDIAGONAL:
	case FILLMODE_FDIAGONAL:
	case FILLMODE_CROSS:
	case FILLMODE_DIACROSS:
	default:		// alles andere macht TRiAS
		return NOERROR;
	}

// wenn noch keine Palette gegeben ist, dann diese holen und mergen		
	if (m_hPal == 0)
		m_hPal = DEX_GetActivePalette();

// Analyse des VisStrings, extrahieren der Parameter
CFillParams fp (hTargetDC);
HRESULT hr = fp.ParseVisString (pVisString);

	if (FAILED(hr)) return hr;

// Besorgen der Objektgeometrie
CGObject GO (lONr);
CRgn Rgn;

// Bilden der Clipregion
	hr = CreateObjectRegion (GO, Rgn);
	if (FAILED(hr)) return hr;

// eigentliches Zeichnen innerhalb der ClipRegion
	hr = FillObjectRgn (hDC, Rgn, static_cast<FVisInfo *>(pVI), fp);
	if (SUCCEEDED(hr)) {
		pVI -> Style() = FILLMODE_HOLLOW;
		rfDrawFlags |= DO_StyleChanged;
	}

return hr;
}

// Zeichnen innerhalb einer Region --------------------------------------------
HRESULT CFillArea::FillObjectRgn (HDC hDC, CRgn &rRgn, FVisInfo *pFVI, CFillParams &rfp)
{
CFixupDC dc (hDC, m_hPal, rRgn, pFVI, rfp);
HRESULT hr = NOERROR;

// wir sind nur für das Füllmuster zuständig, den Rand zeichnet TRiAS drauf
	switch (pFVI -> Type()) {
	case FILLMODE_VERTICAL:
		if (pFVI -> isOpaque())
			dc.FillRect (m_rcBound);
		hr = HatchVertical (dc, rfp);
		break;

	case FILLMODE_HORIZONTAL:
		if (pFVI -> isOpaque())
			dc.FillRect (m_rcBound);
		hr = HatchHorizontal (dc, rfp);
		break;

	case FILLMODE_BDIAGONAL:
	case FILLMODE_FDIAGONAL:
	case FILLMODE_CROSS:
	case FILLMODE_DIACROSS:
	default:		// alles muß TRiAS machen
		ASSERT(false);
		return ResultFromScode(E_UNEXPECTED);
	}

return hr;
}

///////////////////////////////////////////////////////////////////////////////
// FüllRoutinen
HRESULT CFillArea::HatchHorizontal (CDC &rDC, CFillParams &rfp)
{
long lWidth2 = rfp.GetWidthOnDC_Y()/2;
long lStep = rfp.GetStepOnDC_Y() + rfp.GetWidthOnDC_Y();

	for (long lVert = m_rcBound.top + rfp.GetOffsetOnDC_Y() + lWidth2;
		 lVert < m_rcBound.bottom + lWidth2;
		 lVert += lStep)
	{
		rDC.MoveTo (m_rcBound.left, lVert);
		rDC.LineTo (m_rcBound.right, lVert);
	}

return ResultFromScode(VISMODULE_S_DRAWOBJECT);
}

HRESULT CFillArea::HatchVertical (CDC &rDC, CFillParams &rfp)
{
long lWidth2 = rfp.GetWidthOnDC_X()/2;
long lStep = rfp.GetStepOnDC_X() + rfp.GetWidthOnDC_X();

	for (long lHorz = m_rcBound.left + rfp.GetOffsetOnDC_X() + lWidth2;
		 lHorz < m_rcBound.right + lWidth2;
		 lHorz += lStep)
	{
		rDC.MoveTo (lHorz, m_rcBound.top);
		rDC.LineTo (lHorz, m_rcBound.bottom);
	}

return ResultFromScode(VISMODULE_S_DRAWOBJECT);
}

// Eine Clipregion bilden, die einem Objekt entspricht ------------------------
HRESULT CFillArea::CreateObjectRegion (CGObject &rGO, CRgn &rRgn) 
{
// wenn es keine Fläche ist, dann sofort wieder raus
	if (!rGO.FInit() || rGO.isA() != OGFlaeche)
		return ResultFromScode(E_UNEXPECTED);

// hier gehts los
long lCnt = rGO.lCnt();

	if (!InitPoints (lCnt))
		return ResultFromScode(E_OUTOFMEMORY);		// No Memory

// Punkte transformieren
	if (!OCtoDC (rGO.lX(), rGO.lY(), lCnt, m_pPts, m_rcBound))
		return ResultFromScode(E_FAIL);

// Region bilden
	if (1 == rGO.iKCnt())	// Nur ein PolygonZug (keine Löcher)
		rRgn.CreatePolygonRgn (m_pPts, lCnt, ALTERNATE);
	else						// Fläche mit Löchern
		rRgn.CreatePolyPolygonRgn (m_pPts, (int *)rGO.plCnt(), rGO.iKCnt(), ALTERNATE);

return (NULL == (HRGN)rRgn) ? ResultFromScode (E_FAIL) : NOERROR;
}

