//TOOLBAR

#include "kompp.hxx"

// BasicScript
#include <eb.h>
#include <ibscript.hxx>
#include <bscrguid.h>

#include <itoolbar.h>

#include <xtsnguid.h>


#include <initguid.h>
#include <toolguid.h>
#include "mynotify.h"
//#include <toolbar_i.c>
//#include <triastlb_i.c>
#include <triastlb.h>


//#include <ospace/com/smartif.h>
//#include <smartif.h>
#include <dirisole.h>
#include <ospace/std/map>		// STL related stuff


#include <istatus.h>
#include <igeometr.hxx>


#include "cobjtree.hxx"
#include "ctopobj.hxx"
#include "kompias.h"
#include "triasdef.h"
#include "kompdef.h"
#include "gewbaum.hxx"
#include "komphead.hxx"
#include "kompdll.hxx"
#include "kompgew.hxx"


#include "kompias.hxx"

#include "AuxUIOwner.h"

///////////////////////////////////////////////////////////////////////////////
// ControlBar styles (from AFXRES.H)
#define CBRS_ALIGN_LEFT     0x1000L
#define CBRS_ALIGN_TOP      0x2000L
#define CBRS_ALIGN_RIGHT    0x4000L
#define CBRS_ALIGN_BOTTOM   0x8000L
#define CBRS_ALIGN_ANY      0xF000L

#define CBRS_BORDER_LEFT    0x0100L
#define CBRS_BORDER_TOP     0x0200L
#define CBRS_BORDER_RIGHT   0x0400L
#define CBRS_BORDER_BOTTOM  0x0800L
#define CBRS_BORDER_ANY     0x0F00L

#define CBRS_TOOLTIPS       0x0010L
#define CBRS_FLYBY          0x0020L
#define CBRS_FLOAT_MULTI    0x0040L
#define CBRS_BORDER_3D      0x0080L
#define CBRS_HIDE_INPLACE   0x0008L
#define CBRS_SIZE_DYNAMIC   0x0004L
#define CBRS_SIZE_FIXED     0x0002L
#define CBRS_FLOATING       0x0001L

#define AFX_IDW_DOCKBAR_TOP             0xE81B

DefineSmartInterface(TRiASBar);
// DefineSmartInterface(TRiASToolBar);
DefineSmartInterface(PersistStreamInit);
DefineSmartInterface(TRiASBarContainer);
DefineSmartInterface(TRiASUIOwner);

// Toolbar instatiieren -------------------------------------------------------
const int NOSTRING = 0;
const TBBUTTON buttonsKomp[] =
{	
	{ 0, ID_KOMPDATA_EREIGNIS, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{ 1, ID_KOMPDATA_WASSER, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
};
#define NUMBUTTONS_KOMP (sizeof(buttonsKomp)/sizeof(buttonsKomp[0]))

TBBUTTON *CopyButtons (const TBBUTTON *pBttns, int iCnt)
{
	try {
	TBBUTTON *pBtnCopy = new TBBUTTON [iCnt];

		for (int i = 0; i < iCnt; i++) 
			pBtnCopy[i] = pBttns[i];

		return pBtnCopy;
	} catch (...) {
		return NULL;
	} 
}

HRESULT CKompiasExtension::CreateKompDataToolBar (void)
{
TBBUTTON *pBtnCopy = NULL;

	try {
	WTRiASBarContainer BarCont (m_pXtnSite);
	WTRiASBar Bar;
	ResString strCap (ResID (IDS_KOMPTOOLCAPTION, &RF()), 128);
	DWORD dwStyle = CBRS_ALIGN_TOP|CBRS_SIZE_DYNAMIC|CBRS_TOOLTIPS|
//					CBRS_BORDER_ANY|CBRS_FLYBY;
				CBRS_BORDER_ANY|CBRS_FLYBY|CBRS_FLOATING;

		if (IsWin40()) dwStyle |= CBRS_BORDER_3D;

	// ToolBar erzeugen
	HRESULT hr = BarCont -> AddTRiASBar (strCap, dwStyle, TRIASTOOLBAR_PREDEFINED, Bar.ppi());

		if (FAILED(hr)) throw hr;


//---------------------------------------------------


	// Bitmaps hinzufügen
	WTRiASToolBar Tools (Bar);		// throws HRESULT
	int iOffset = -1;

//		hr = Tools -> AddBitmap (g_hInstance, IDB_KOMPDATA, 2, &iOffset);
		hr = Tools -> AddBitmap (g_hInstance, ID_KOMPDATA_EREIGNIS, 2, &iOffset);
		if (FAILED(hr)) return hr;

		pBtnCopy = CopyButtons (buttonsKomp, NUMBUTTONS_KOMP);
		if (NULL == pBtnCopy) throw E_OUTOFMEMORY;

	TBBUTTON *pCurr = pBtnCopy;

		for (int i = 0; i < NUMBUTTONS_KOMP; i++, pCurr++) {
			if (!(TBSTYLE_SEP & pCurr -> fsStyle))
				pCurr -> iBitmap += iOffset;
//			pBtnCopy -> idCommand += MenuOffset();
		}
	
	// UIOwner erzeugen
	WTRiASUIOwner UIOwner;
	
		try {
		CComObject<CAuxUIOwner> *pOwner = NULL;
		HRESULT hr = CComObject<CAuxUIOwner>::CreateInstance(&pOwner);

			if (FAILED(hr)) throw hr;
			UIOwner = (ITRiASUIOwner *)pOwner;		// AddRef !
			m_pUIOwner = 0;
			m_pUIOwner = (DWORD) pOwner;
		
			hr = pOwner -> SetExtension (this);
			if (FAILED(hr)) throw hr;
		
		} catch (HRESULT hr) {
			return hr;
		} catch (...) {
			throw E_OUTOFMEMORY;
		}			
	
	// Buttons hinzufügen
		hr = Tools -> AddButtons (pBtnCopy, NUMBUTTONS_KOMP, UIOwner);
		if (FAILED(hr)) throw hr;

//---------------------------------------------

	VARIANT_BOOL fVisible = true;

//---------------ToolBar sichtbar

	dwStyle = 0L;
	DWORD dwStyleEx = 0L;

	hr = Tools -> GetBarStyle (NULL, 0, NULL, &dwStyle, &dwStyleEx);

	if (FAILED(hr)) return hr;

	bool fNewVisible = fVisible ? true : false;
	bool fOldVisible = (dwStyle & WS_VISIBLE) ? true : false;

	if (fOldVisible ^ fNewVisible) {
		if (fNewVisible)
			dwStyle |= WS_VISIBLE;
		else
			dwStyle &= ~WS_VISIBLE;
		hr = Tools -> SetBarStyle (NULL, dwStyle, dwStyleEx, false);
	}


//-------------------------------------------
		
	// Toolbar jetzt floaten
		Point pt (50, 50);

		ClientToScreen (MWind() -> Handle(), (POINT *)&pt);
		hr = Tools -> FloatBar ((POINT &)pt, dwStyle);
		if (FAILED(hr)) throw hr;


//		DELETE_OBJ(pBtnCopy);
		DELETE_OBJ (pBtnCopy);

	} catch (HRESULT hr) {
//		DELETE_OBJ(pBtnCopy);
		DELETE_OBJ (pBtnCopy);
		return hr;
	}

return NOERROR;
}

HRESULT CKompiasExtension::RemoveKompDataToolBar (void)
{
	try {
	WTRiASBarContainer BarCont (m_pXtnSite);
	ResString strCap (ResID (IDS_KOMPTOOLCAPTION, &RF()), 128);

//	Notlösung ??
//	KK990803
	CComObject<CAuxUIOwner> *pOwner = NULL;

	pOwner = (CComObject<CAuxUIOwner> *) m_pUIOwner;		// AddRef !
	pOwner->DisConnectFromServer ();
#pragma message ("TOOLBAR.CPP:==> Release auslösen! - Fehlende Events von ITRiASNotificationSink ???")


	// ToolBar beseitigen
		return BarCont -> DeleteTRiASBar (strCap);

	} catch (HRESULT hr) {
		return hr;
	}
}

