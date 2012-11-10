// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 09/06/1998 01:33:35 PM
//
// @doc
// @module Berlin.cpp | TRiAS Berlin


#include "StdAfx.h"

#include "resource.h"		// ResourceKonstanten
#include "version.h"

#include <itoolbar.h>
#include <toolguid.h>

// BasicScript
#include <eb.h>
#include <ibscript.hxx>



//#include <Triastlb_i.c>
#include <Triastlb.h>

#include <xtsnguid.h>

#include <initguid.h>

#include <ospace/std/map>		// STL related stuff

#include <TriasHelper_i.c>
#include <TriasHelper.h>

#include <initguid.h>		// nur im einem Module notwendig
#include "blnguid.h"
#include <bscrguid.h>
#include <ScriptPropActGuid.h>

#include "ObjektNummerierenGuid.h"
#include "ObjekteNummerieren.h"

#include "BerlinExt.h"		// die Erweiterung selbst

#include "AuxUIOwner.h"




#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG


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

#define CBRS_LEFT           (CBRS_ALIGN_LEFT|CBRS_BORDER_RIGHT)
#define CBRS_TOP            (CBRS_ALIGN_TOP|CBRS_BORDER_BOTTOM)
#define CBRS_RIGHT          (CBRS_ALIGN_RIGHT|CBRS_BORDER_LEFT)
#define CBRS_BOTTOM         (CBRS_ALIGN_BOTTOM|CBRS_BORDER_TOP)

#define AFX_IDW_DOCKBAR_TOP             0xE81B
#define AFX_IDW_DOCKBAR_LEFT            0xE81C
#define AFX_IDW_DOCKBAR_RIGHT           0xE81D
#define AFX_IDW_DOCKBAR_BOTTOM          0xE81E
#define AFX_IDW_DOCKBAR_FLOAT           0xE81F


DefineSmartInterface(TRiASBar);
DefineSmartInterface(PersistStreamInit);
DefineSmartInterface(TRiASBarContainer);
DefineSmartInterface(TRiASUIOwner);

// Toolbar instatiieren -------------------------------------------------------
const int NOSTRING = 0;
const TBBUTTON buttonsBln[] =
{	
	{ 0, ID_BLNDATA_ALB, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{ 1, ID_BLNDATA_BLINK, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{ 2, ID_BLNDATA_NUMMER, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{ 3, ID_BLNDATA_IDENT, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{ 4, ID_BLNDATA_GITEST, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{ 5, ID_BLNDATA_FTEIL, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{ 6, ID_BLNDATA_INSEL, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{ 7, ID_BLNDATA_OBJNUMMER, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
};
#define NUMBUTTONS_BLN (sizeof(buttonsBln)/sizeof(buttonsBln[0]))



///////////////////////////////////////////////////////////////////////////////
// NEU: An Stelle der Funktionen NewExtension und GetExtensionCLSID muß die 
// Erweiterung jetzt in der ATL ObjectMap eingetragen werden (zusammen 
// mit allen anderen ATL-Objekten)
BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_BerlinExt, CBerlinExt)
	OBJECT_ENTRY(CLSID_ObjekteNummerieren, CObjekteNummerieren)
END_OBJECT_MAP()

// mit der folgenden Funktion wird die ObjectMap in den ClassFactory-Mechanismus
// dieser Erweiterung eingebunden
_ATL_OBJMAP_ENTRY *GetObjectMap (void)
{
	return ObjectMap;		// liefert ObjectMap
}

///////////////////////////////////////////////////////////////////////////////
// Registrierung/DeRegistrierung
BOOL UpdateRegistry (BOOL fRegister)	// RegDB aktualisieren (initialisieren/löschen)
{
	if (fRegister) {
	// RegDB initialisieren
		return ExtOleRegisterExtensionClass (g_hInstance,
				CLSID_BerlinExt, 
				TEXT("TRiAS.BerlinSchale.1"),IDS_LONGCLASSNAME,
				BERLIN_MAJORVERSION, BERLIN_MINORVERSION,
				EFVisible|EFUnLoadable|EFRegisterToolBitmap);
	} else {
	// RegDB säubern
		return ExtOleUnregisterClass (CLSID_BerlinExt, 
					      TEXT("TRiAS.BerlinSchale.1"));
	}
	return true;	// alles ok
}

///////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP_(BOOL) CBerlinExt::InitExtension (short iMode) 
{
	if (!CTriasExtension::InitExtension(iMode))
		return false;

	CreateBlnDataToolBar();

	ATLTRY(m_BasicScript = WExtendBScript (CLSID_MacroScriptExtension));
	return m_BasicScript.IsValid();
}

STDMETHODIMP_(BOOL) CBerlinExt::UnLoadExtension (void)
{
	m_BasicScript.Assign (NULL);

	RemoveBlnDataToolBar();

	return CTriasExtension::UnLoadExtension();
}

//------------------------------------------------------------------------
HRESULT CBerlinExt :: StartALB ( void)
{
	int iNum = 0;
	LPVOID pTyp = NULL;

	ebPARAM PA;
	PA.wType = 0;
	PA.szExtType[0] = '\0';

	BSPARAM BS;
	BS.pTypes = &PA;
	BS.pValues = &pTyp;
	HRESULT hr;
	WExtendBScript m_Script;
	hr = GetBasicScript (m_Script.ppi());
	if ( m_Script )
		hr = m_Script->RunCode(g_hInstance,IDR_SCRIPTALB,"ALB",iNum,&BS);

	return S_OK;
}
//------------------------------------------------------------------------
HRESULT CBerlinExt :: StartBlink ( void)
{
	int iNum = 0;
	LPVOID pTyp = NULL;

	ebPARAM PA;
	PA.wType = 0;
	PA.szExtType[0] = '\0';

	BSPARAM BS;
	BS.pTypes = &PA;
	BS.pValues = &pTyp;
	HRESULT hr;
	WExtendBScript m_Script;
	hr = GetBasicScript (m_Script.ppi());
	if ( m_Script )
		hr = m_Script->RunCode(g_hInstance,IDR_SCRIPTBLINK,"Blink",iNum,&BS);

	return S_OK;
}
//------------------------------------------------------------------------
HRESULT CBerlinExt :: StartGiTest ( void)
{
	int iNum = 0;
	LPVOID pTyp = NULL;

	ebPARAM PA;
	PA.wType = 0;
	PA.szExtType[0] = '\0';

	BSPARAM BS;
	BS.pTypes = &PA;
	BS.pValues = &pTyp;
	HRESULT hr;
	WExtendBScript m_Script;
	hr = GetBasicScript (m_Script.ppi());
	if ( m_Script )
		hr = m_Script->RunCode(g_hInstance,IDR_SCRIPTGITEST,"GiTest",iNum,&BS);
	return S_OK;
}
//------------------------------------------------------------------------
HRESULT CBerlinExt :: StartFTeil ( void)
{
	int iNum = 0;
	LPVOID pTyp = NULL;

	ebPARAM PA;
	PA.wType = 0;
	PA.szExtType[0] = '\0';

	BSPARAM BS;
	BS.pTypes = &PA;
	BS.pValues = &pTyp;
	HRESULT hr;
	WExtendBScript m_Script;
	hr = GetBasicScript (m_Script.ppi());
	if ( m_Script )
		hr = m_Script->RunCode(g_hInstance,IDR_SCRIPTFTEIL,"FTeil",iNum,&BS);
	return S_OK;
}
//------------------------------------------------------------------------
HRESULT CBerlinExt :: StartInsel ( void)
{
	int iNum = 0;
	LPVOID pTyp = NULL;

	ebPARAM PA;
	PA.wType = 0;
	PA.szExtType[0] = '\0';

	BSPARAM BS;
	BS.pTypes = &PA;
	BS.pValues = &pTyp;
	HRESULT hr;
	WExtendBScript m_Script;
	hr = GetBasicScript (m_Script.ppi());
	if ( m_Script )
		hr = m_Script->RunCode(g_hInstance,IDR_SCRIPTINSEL,"Insel",iNum,&BS);
	return S_OK;
}
///////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------
HRESULT CBerlinExt :: StartNummer ( void)
{
	int iNum = 0;
	LPVOID pTyp = NULL;

	ebPARAM PA;
	PA.wType = 0;
	PA.szExtType[0] = '\0';

	BSPARAM BS;
	BS.pTypes = &PA;
	BS.pValues = &pTyp;
	HRESULT hr;
	WExtendBScript m_Script;
	hr = GetBasicScript (m_Script.ppi());
	if ( m_Script )
		hr = m_Script->RunCode(g_hInstance,IDR_SCRIPTNUMMER,"Nummer",iNum,&BS);
	return S_OK;
}
//------------------------------------------------------------------------
HRESULT CBerlinExt :: StartIdent ( void)
{
	int iNum = 0;
	LPVOID pTyp = NULL;

	ebPARAM PA;
	PA.wType = 0;
	PA.szExtType[0] = '\0';

	BSPARAM BS;
	BS.pTypes = &PA;
	BS.pValues = &pTyp;
	HRESULT hr;
	WExtendBScript m_Script;
	hr = GetBasicScript (m_Script.ppi());
	if ( m_Script )
		hr = m_Script->RunCode(g_hInstance,IDR_SCRIPTIDENT,"Ident",iNum,&BS);
	return S_OK;
}
///////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------
HRESULT CBerlinExt :: StartObjNummer ( void)
{
	int iNum = 0;
	LPVOID pTyp = NULL;

	ebPARAM PA;
	PA.wType = 0;
	PA.szExtType[0] = '\0';

	BSPARAM BS;
	BS.pTypes = &PA;
	BS.pValues = &pTyp;
	HRESULT hr;
	WExtendBScript m_Script;
	hr = GetBasicScript (m_Script.ppi());
	if ( m_Script )
		hr = m_Script->RunCode(g_hInstance,IDR_SCRIPTOBJNUMMER,"ObjNummer",iNum,&BS);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////


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
/////////////////////////////////////////////////////////////////////////////////////////////
HRESULT CBerlinExt::CreateBlnDataToolBar (void)
{
TBBUTTON *pBtnCopy = NULL;

	try {
	WTRiASBarContainer BarCont (m_pXtnSite);
	WTRiASBar Bar;
	ResString strCap (ResID (IDS_BLNTOOLCAPTION, &RF()), 128);
	DWORD dwStyle = CBRS_ALIGN_TOP|CBRS_SIZE_DYNAMIC|CBRS_TOOLTIPS|
				CBRS_BORDER_ANY|CBRS_FLYBY|CBRS_FLOATING;


		if (IsWin40()) dwStyle |= CBRS_BORDER_3D;

	// ToolBar erzeugen
	HRESULT hr = BarCont -> AddTRiASBar (strCap, dwStyle, TRIASTOOLBAR_PREDEFINED, Bar.ppi());

		if (FAILED(hr)) throw hr;


//---------------------------------------------------


	// Bitmaps hinzufügen
	WTRiASToolBar Tools (Bar);		// throws HRESULT
	int iOffset = -1;

		hr = Tools -> AddBitmap (g_hInstance, ID_BLNDATA_ALB, NUMBUTTONS_BLN, &iOffset);
//		hr = Tools -> AddBitmap (g_hInstance, ID_BLNDATA_ALB, 8, &iOffset);
		if (FAILED(hr)) return hr;

		pBtnCopy = CopyButtons (buttonsBln, NUMBUTTONS_BLN);
		if (NULL == pBtnCopy) throw E_OUTOFMEMORY;

	TBBUTTON *pCurr = pBtnCopy;

		for (int i = 0; i < NUMBUTTONS_BLN; i++, pCurr++) {
			if (!(TBSTYLE_SEP & pCurr -> fsStyle))
				pCurr -> iBitmap += iOffset;
		}
	
	// UIOwner erzeugen
	WTRiASUIOwner UIOwner;
	
		try {
		CComObject<CAuxUIOwner> *pOwner = NULL;
		HRESULT hr = CComObject<CAuxUIOwner>::CreateInstance(&pOwner);

			if (FAILED(hr)) throw hr;
			UIOwner = (ITRiASUIOwner *)pOwner;		// AddRef !
		
			hr = pOwner -> SetExtension (this);
			if (FAILED(hr)) throw hr;
		
		} catch (HRESULT hr) {
			return hr;
		} catch (...) {
			throw E_OUTOFMEMORY;
		}			
	
	// Buttons hinzufügen
		hr = Tools -> AddButtons (pBtnCopy, NUMBUTTONS_BLN, UIOwner);
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

		DELETE_OBJ(pBtnCopy);

	} catch (HRESULT hr) {

		DELETE_OBJ(pBtnCopy);
		return hr;
	}

return NOERROR;
}

HRESULT CBerlinExt::RemoveBlnDataToolBar (void)
{
	try {
	WTRiASBarContainer BarCont (m_pXtnSite);
	ResString strCap (ResID (IDS_BLNTOOLCAPTION, &RF()), 128);

	// ToolBar beseitigen
		return BarCont -> DeleteTRiASBar (strCap);

	} catch (HRESULT hr) {
		return hr;
	}
}

///////////////////////////////////////////////////////////////////////////////
