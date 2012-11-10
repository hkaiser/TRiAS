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

#include "OnlyOneObjectGuid.h"
#include "OnlyOneObject.h"

#include "NoMultiObjektGuid.h"
#include "NoMultiObjekt.h"


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
#if defined ( BERLINUPDATE)
	{ 0, ID_BLNDATA_ALB_UPD, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{ 1, ID_BLNDATA_BLINK_UPD, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{ 2, ID_BLNDATA_NUMMER_UPD, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{ 3, ID_BLNDATA_IDENT_UPD, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{ 4, ID_BLNDATA_GITEST_UPD, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{ 5, ID_BLNDATA_FTEIL_UPD, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{ 6, ID_BLNDATA_INSEL_UPD, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{ 7, ID_BLNDATA_OBJNUMMER_UPD, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{ 8, ID_BLNDATA_FNUMMER, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{ 9, ID_BLNDATA_IDTEST, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
#else
	{ 0, ID_BLNDATA_ALB, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{ 1, ID_BLNDATA_BLINK, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{ 2, ID_BLNDATA_NUMMER, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{ 3, ID_BLNDATA_IDENT, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{ 4, ID_BLNDATA_GITEST, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{ 5, ID_BLNDATA_FTEIL, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{ 6, ID_BLNDATA_UGRU, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{ 7, ID_BLNDATA_INSEL, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{ 8, ID_BLNDATA_OBJNUMMER, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
#endif
};
#define NUMBUTTONS_BLN (sizeof(buttonsBln)/sizeof(buttonsBln[0]))



///////////////////////////////////////////////////////////////////////////////
// NEU: An Stelle der Funktionen NewExtension und GetExtensionCLSID muß die 
// Erweiterung jetzt in der ATL ObjectMap eingetragen werden (zusammen 
// mit allen anderen ATL-Objekten)
BEGIN_OBJECT_MAP(ObjectMap)
#if defined ( BERLINUPDATE)
	OBJECT_ENTRY(CLSID_BerlinUpdate, CBerlinExt)
#else
	OBJECT_ENTRY(CLSID_BerlinExt, CBerlinExt)
#endif

	OBJECT_ENTRY(CLSID_ObjekteNummerieren, CObjekteNummerieren)
	OBJECT_ENTRY(CLSID_OnlyOneObject, COnlyOneObject)
	OBJECT_ENTRY(CLSID_NoMultiObjekt, CNoMultiObjekt)
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
#if defined ( BERLINUPDATE)
				CLSID_BerlinUpdate,
#else
				CLSID_BerlinExt, 
#endif

#if defined ( BERLINUPDATE)
				TEXT("TRiAS.BerlinUpdate.1"),IDS_LONGCLASSNAMEUPDATE,
#else
				TEXT("TRiAS.GebuehrenSplitting.1"),IDS_LONGCLASSNAME,
#endif
				BERLIN_MAJORVERSION, BERLIN_MINORVERSION,
				EFVisible|EFUnLoadable|EFRegisterToolBitmap);
	} else {
	// RegDB säubern
#if defined ( BERLINUPDATE)
		return ExtOleUnregisterClass(CLSID_BerlinUpdate,
					      TEXT("TRiAS.BerlinUpdate.1"));
#else
		return ExtOleUnregisterClass (CLSID_BerlinExt, 
					      TEXT("TRiAS.GebuehrenSplitting.1"));
#endif

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
//---------------------------------------------------------------------
#if defined ( BERLINUPDATE)

HRESULT CBerlinExt :: StartFlurTest ( void)
{
	int iNum = 1;

	char *pQuelle = new char [_MAX_PATH];
	if (!pQuelle ) {
		return S_FALSE;
	}
	*pQuelle = '\0';

#if _MSC_VER >= 1100
	HPROJECT hPr = DEX_GetDataSourceHandle();
	if ( pQuelle)
		DEX_GetDataSourceShortName (hPr, pQuelle);

#endif

	ebPARAM PA[2];
	PA[0].wType = 0;
	PA[0].szExtType[0] = '\0';
	//DatenQuelle
	PA[1].wType = TYP_STRING;
	strcpy ( PA[1].szExtType,pQuelle);

	ebINT iHKS = false;
	LPVOID pTyp[2] = {&iHKS,pQuelle};

	BSPARAM BS;
	BS.pTypes = PA;
	BS.pValues = pTyp;
	HRESULT hr;
	WExtendBScript m_Script;
	hr = GetBasicScript (m_Script.ppi());
	if ( m_Script )

		hr = m_Script->RunCode(g_hInstance,IDR_SCRIPTFNUMMER,"FNUMMER",iNum,&BS);

	DELETE_OBJ(pQuelle);
	return S_OK;

}

//-----------------------------------------------------------------------
HRESULT CBerlinExt :: StartIDTest ( void)
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

		hr = m_Script->RunCode(g_hInstance,IDR_SCRIPTIDTEST,"IDTest",iNum,&BS);

	return S_OK;

}

#endif
//------------------------------------------------------------------------

//------------------------------------------------------------------------
HRESULT CBerlinExt :: StartALB ( void)
{
	int iNum = 1;

	char *pQuelle = new char [_MAX_PATH];
	if (!pQuelle ) {
		return S_FALSE;
	}
	*pQuelle = '\0';

#if _MSC_VER >= 1100
	HPROJECT hPr = DEX_GetDataSourceHandle();
	if ( pQuelle)
		DEX_GetDataSourceShortName (hPr, pQuelle);

#endif

	ebPARAM PA[2];
	PA[0].wType = 0;
	PA[0].szExtType[0] = '\0';
	//DatenQuelle
	PA[1].wType = TYP_STRING;
	strcpy ( PA[1].szExtType,pQuelle);

	ebINT iHKS = false;
	LPVOID pTyp[2] = {&iHKS,pQuelle};

	BSPARAM BS;
	BS.pTypes = PA;
	BS.pValues = pTyp;
	HRESULT hr;
	WExtendBScript m_Script;
	hr = GetBasicScript (m_Script.ppi());


	if ( m_Script )

#if defined ( BERLINUPDATE)
		hr = m_Script->RunCode(g_hInstance,IDR_SCRIPTALB_UPD1,"ALB_Upd1",iNum,&BS);
#else
		hr = m_Script->RunCode(g_hInstance,IDR_SCRIPTALB,"ALB",iNum,&BS);
#endif
	DELETE_OBJ(pQuelle);

	return S_OK;
}
//------------------------------------------------------------------------
HRESULT CBerlinExt :: StartBlink ( void)
{
	int iNum = 1;

	char *pQuelle = new char [_MAX_PATH];
	if (!pQuelle ) {
		return S_FALSE;
	}
	*pQuelle = '\0';

#if _MSC_VER >= 1100
	HPROJECT hPr = DEX_GetDataSourceHandle();
	if ( pQuelle)
		DEX_GetDataSourceShortName (hPr, pQuelle);

#endif

	ebPARAM PA[2];
	PA[0].wType = 0;
	PA[0].szExtType[0] = '\0';
	//DatenQuelle
	PA[1].wType = TYP_STRING;
	strcpy ( PA[1].szExtType,pQuelle);

	ebINT iHKS = false;
	LPVOID pTyp[2] = {&iHKS,pQuelle};

	BSPARAM BS;
	BS.pTypes = PA;
	BS.pValues = pTyp;
	HRESULT hr;
	WExtendBScript m_Script;
	hr = GetBasicScript (m_Script.ppi());

	if ( m_Script )
		hr = m_Script->RunCode(g_hInstance,IDR_SCRIPTBLINK,"Blink",iNum,&BS);

	DELETE_OBJ(pQuelle);

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
	int iNum = 1;

	char *pQuelle = new char [_MAX_PATH];
	if (!pQuelle ) {
		return S_FALSE;
	}
	*pQuelle = '\0';

#if _MSC_VER >= 1100
	HPROJECT hPr = DEX_GetDataSourceHandle();
	if ( pQuelle)
		DEX_GetDataSourceShortName (hPr, pQuelle);

#endif

	ebPARAM PA[2];
	PA[0].wType = 0;
	PA[0].szExtType[0] = '\0';
	//DatenQuelle
	PA[1].wType = TYP_STRING;
	strcpy ( PA[1].szExtType,pQuelle);

	ebINT iHKS = false;
	LPVOID pTyp[2] = {&iHKS,pQuelle};

	BSPARAM BS;
	BS.pTypes = PA;
	BS.pValues = pTyp;
	HRESULT hr;
	WExtendBScript m_Script;
	hr = GetBasicScript (m_Script.ppi());

	if ( m_Script )
		hr = m_Script->RunCode(g_hInstance,IDR_SCRIPTFTEIL,"FTeil",iNum,&BS);

	DELETE_OBJ(pQuelle);

	return S_OK;
}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
HRESULT CBerlinExt :: StartUnbau ( void)
{
	int iNum = 1;

	char *pQuelle = new char [_MAX_PATH];
	if (!pQuelle ) {
		return S_FALSE;
	}
	*pQuelle = '\0';

#if _MSC_VER >= 1100
	HPROJECT hPr = DEX_GetDataSourceHandle();
	if ( pQuelle)
		DEX_GetDataSourceShortName (hPr, pQuelle);

#endif

	ebPARAM PA[2];
	PA[0].wType = 0;
	PA[0].szExtType[0] = '\0';
	//DatenQuelle
	PA[1].wType = TYP_STRING;
	strcpy ( PA[1].szExtType,pQuelle);

	ebINT iHKS = false;
	LPVOID pTyp[2] = {&iHKS,pQuelle};

	BSPARAM BS;
	BS.pTypes = PA;
	BS.pValues = pTyp;
	HRESULT hr;
	WExtendBScript m_Script;
	hr = GetBasicScript (m_Script.ppi());

	if ( m_Script )
		hr = m_Script->RunCode(g_hInstance,IDR_SCRIPTUGRU,"Unbebaut",iNum,&BS);

	DELETE_OBJ(pQuelle);

	return S_OK;
}
//------------------------------------------------------------------------
HRESULT CBerlinExt :: StartInsel ( void)
{
	int iNum = 1;

	char *pQuelle = new char [_MAX_PATH];
	if (!pQuelle ) {
		return S_FALSE;
	}
	*pQuelle = '\0';

#if _MSC_VER >= 1100
	HPROJECT hPr = DEX_GetDataSourceHandle();
	if ( pQuelle)
		DEX_GetDataSourceShortName (hPr, pQuelle);

#endif

	ebPARAM PA[2];
	PA[0].wType = 0;
	PA[0].szExtType[0] = '\0';
	//DatenQuelle
	PA[1].wType = TYP_STRING;
	strcpy ( PA[1].szExtType,pQuelle);

	ebINT iHKS = false;
	LPVOID pTyp[2] = {&iHKS,pQuelle};

	BSPARAM BS;
	BS.pTypes = PA;
	BS.pValues = pTyp;
	HRESULT hr;
	WExtendBScript m_Script;
	hr = GetBasicScript (m_Script.ppi());

	if ( m_Script )
		hr = m_Script->RunCode(g_hInstance,IDR_SCRIPTINSEL,"Insel",iNum,&BS);

	DELETE_OBJ(pQuelle);

	return S_OK;
}
///////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------
HRESULT CBerlinExt :: StartNummer ( void)
{
	int iNum = 1;

	char *pQuelle = new char [_MAX_PATH];
	if (!pQuelle ) {
		return S_FALSE;
	}
	*pQuelle = '\0';

#if _MSC_VER >= 1100
	HPROJECT hPr = DEX_GetDataSourceHandle();
	if ( pQuelle)
		DEX_GetDataSourceShortName (hPr, pQuelle);

#endif

	ebPARAM PA[2];
	PA[0].wType = 0;
	PA[0].szExtType[0] = '\0';
	//DatenQuelle
	PA[1].wType = TYP_STRING;
	strcpy ( PA[1].szExtType,pQuelle);

	ebINT iHKS = false;
	LPVOID pTyp[2] = {&iHKS,pQuelle};

	BSPARAM BS;
	BS.pTypes = PA;
	BS.pValues = pTyp;
	HRESULT hr;
	WExtendBScript m_Script;
	hr = GetBasicScript (m_Script.ppi());

	if ( m_Script )
		hr = m_Script->RunCode(g_hInstance,IDR_SCRIPTNUMMER,"Nummer",iNum,&BS);

	DELETE_OBJ(pQuelle);

	return S_OK;
}
//------------------------------------------------------------------------
HRESULT CBerlinExt :: StartIdent ( void)
{
	int iNum = 1;

	char *pQuelle = new char [_MAX_PATH];
	if (!pQuelle ) {
		return S_FALSE;
	}
	*pQuelle = '\0';

#if _MSC_VER >= 1100
	HPROJECT hPr = DEX_GetDataSourceHandle();
	if ( pQuelle)
		DEX_GetDataSourceShortName (hPr, pQuelle);

#endif

	ebPARAM PA[2];
	PA[0].wType = 0;
	PA[0].szExtType[0] = '\0';
	//DatenQuelle
	PA[1].wType = TYP_STRING;
	strcpy ( PA[1].szExtType,pQuelle);

	ebINT iHKS = false;
	LPVOID pTyp[2] = {&iHKS,pQuelle};

	BSPARAM BS;
	BS.pTypes = PA;
	BS.pValues = pTyp;
	HRESULT hr;
	WExtendBScript m_Script;
	hr = GetBasicScript (m_Script.ppi());

	if ( m_Script )
#if defined ( BERLINUPDATE)
		hr = m_Script->RunCode(g_hInstance,IDR_SCRIPTIDENT_UPD1,"Ident_Upd1",iNum,&BS);
#else
		hr = m_Script->RunCode(g_hInstance,IDR_SCRIPTIDENT,"Ident",iNum,&BS);
#endif

	DELETE_OBJ(pQuelle);

	return S_OK;
}
///////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------
HRESULT CBerlinExt :: StartObjNummer ( void)
{
	int iNum = 1;

	char *pQuelle = new char [_MAX_PATH];
	if (!pQuelle ) {
		return S_FALSE;
	}
	*pQuelle = '\0';

#if _MSC_VER >= 1100
	HPROJECT hPr = DEX_GetDataSourceHandle();
	if ( pQuelle)
		DEX_GetDataSourceShortName (hPr, pQuelle);

#endif

	ebPARAM PA[2];
	PA[0].wType = 0;
	PA[0].szExtType[0] = '\0';
	//DatenQuelle
	PA[1].wType = TYP_STRING;
	strcpy ( PA[1].szExtType,pQuelle);

	ebINT iHKS = false;
	LPVOID pTyp[2] = {&iHKS,pQuelle};

	BSPARAM BS;
	BS.pTypes = PA;
	BS.pValues = pTyp;
	HRESULT hr;
	WExtendBScript m_Script;
	hr = GetBasicScript (m_Script.ppi());

	if ( m_Script )
		hr = m_Script->RunCode(g_hInstance,IDR_SCRIPTOBJNUMMER,"ObjNummer",iNum,&BS);

	DELETE_OBJ(pQuelle);

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
#if defined ( BERLINUPDATE)
	ResString strCap (ResID (IDS_BLNTOOLCAPTIONUPD, &RF()), 128);
#else
	ResString strCap (ResID (IDS_BLNTOOLCAPTION, &RF()), 128);
#endif
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

#if defined ( BERLINUPDATE)
		hr = Tools -> AddBitmap (g_hInstance, ID_BLNDATA_ALB_UPD, NUMBUTTONS_BLN, &iOffset);
#else
		hr = Tools -> AddBitmap (g_hInstance, ID_BLNDATA_ALB, NUMBUTTONS_BLN, &iOffset);
#endif
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
#if defined ( BERLINUPDATE)
	ResString strCap (ResID (IDS_BLNTOOLCAPTIONUPD, &RF()), 128);
#else
	ResString strCap (ResID (IDS_BLNTOOLCAPTION, &RF()), 128);
#endif

	// ToolBar beseitigen
		return BarCont -> DeleteTRiASBar (strCap);

	} catch (HRESULT hr) {
		return hr;
	}
}

///////////////////////////////////////////////////////////////////////////////
