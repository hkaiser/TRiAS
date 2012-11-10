// Definitionen: meine Toolbars in TRiAS-Fenster einhängen
// File: ToolBars.cpp
// H. Kaiser


#include "GeoEditP.h"

#include <afxres.h>			// AFX_IDW_DOCKBAR_LEFT
#include <toolguid.h>		// CLSID_TRiASUIOwner in uiowner.h
#include <itoolbar.h>		// ITRiASUIOwner in uiowner.h

#include <Esnecil.h>

#include "uiowner.h"		// CUIOwner

#include "geoedit.h"		// CGeoEditExtension



DefineSmartInterface(TRiASBar);
DefineSmartInterface(TRiASBarContainer);
DefineSmartInterface(TRiASUIOwner);

#if _TRiAS_VER < 0x0400
extern DWORD g_dwVer4;
#endif // _TRiAS_VER < 0x0400

///////////////////////////////////////////////////////////////////////////////////////////////
// Toolbar instatiieren
const TBBUTTON tbDesign[] = {{ 0, ID_TOOL_DESIGN, 0, TBSTYLE_BUTTON, 0L, 0 },
							 { 1, ID_TOOL_DESIGNSTOP, 0, TBSTYLE_BUTTON, 0L, 0 }};
#define NUMBUTTONS_DESIGN (sizeof(tbDesign)/sizeof(tbDesign[0]))



///////////////////////////////////////////////////////////////////////////////////////////////
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



///////////////////////////////////////////////////////////////////////////////////////////////
// Hinzufügen von zusätzlichen ToolButtons zur ToolBar "Werkzeuge" 
 
// Dazu wird über TRiAS der Container aller Toolbars besorgt (QueryInterface), danach die
// gewünschte ToolBar (hier: "Werkzeuge") gesucht und gefunden. Mit AddBitmap wird dieser
// ToolBar die Bitmap (Streifen) mit allen ButtonBitmaps übergeben und anschließend werden die
// Buttons selbst installiert.
HRESULT CGeoEditExtension::InstallEditToolbar (void)
{
// Finden der ToolBar "Werkzeuge"
WTRiASBarContainer ToolBars;
HRESULT hr = m_pXtnSite->QueryInterface (IID_ITRiASBarContainer, ToolBars.ppv());

	if (FAILED(hr)) return hr;

WTRiASBar Bar;
ResString resTools (ResID (IDS_WERKZEUGETOOLBAR, &RF()), 32);	// "Werkzeuge" ist der Name der Toolbar

	hr = ToolBars->FindTRiASBar (resTools, Bar.ppi());
	if (S_OK != hr) return hr;

WTRiASUIOwner UIOwner;

	try
	{
	// Hinzufügen der Buttons
	WTRiASToolBar ToolBar (Bar);	// throws HRESULT
	int iOffset = 0;

		THROW_FAILED_HRESULT (ToolBar->AddBitmap (g_hInstance, IDB_TOOLBAREDIT, BMPSIZE_EDIT,
							  &iOffset));

		THROW_FAILED_HRESULT (CUIOwner::_CreatorClass::CreateInstance (NULL, IID_ITRiASUIOwner,
							  (LPVOID*)UIOwner.ppi()));

	// für jeden zu installierenden Button diese Struktur bereitstellen
	//				       BitmapNr   CmdID		      ButtonState ButtonStyle
	TBBUTTON tbEdit[] = {{ iOffset,   ID_TOOL_PUNKTEDIT,    0,    TBSTYLE_CHECKGROUP, 0L, 0, },
						 { iOffset+1, ID_TOOL_LINIENEDIT,   0,    TBSTYLE_CHECKGROUP, 0L, 0, },
						 { iOffset+2, ID_TOOL_FLAECHENEDIT, 0,    TBSTYLE_CHECKGROUP, 0L, 0, },
						 { iOffset+3, ID_TOOL_MODIFYOBJ,    0,    TBSTYLE_CHECKGROUP, 0L, 0, },
						 { iOffset+4, ID_TOOL_MOVEOBJ,      0,    TBSTYLE_CHECKGROUP, 0L, 0  }};

	// Anzahl der in der EditToolbar zu installierenden Button
	int iBttnCnt = (sizeof(tbEdit)/sizeof(tbEdit[0]));

		THROW_FAILED_HRESULT (ToolBar->AddButtons (tbEdit, iBttnCnt, UIOwner));

	// Position des letzten von mir hinzugefügten EditToolButton merken, um die DesignTooBar
	// richtig andocken zu können
	int iIndex;		// Index meines letzten EditToolButton
	HWND hTBWnd = NULL;

		THROW_FAILED_HRESULT (ToolBar->CommandToIndex (ID_TOOL_MOVEOBJ, &iIndex));
		THROW_FAILED_HRESULT (ToolBar->GetBarHandle (&hTBWnd));
		THROW_FAILED_HRESULT (ToolBar->GetItemRect (iIndex, &m_REC));
		ClientToScreen (hTBWnd, (POINT *)&m_REC);
		ClientToScreen (hTBWnd, &((POINT *)&m_REC)[1]);
	}
	catch (_com_error& hr)
	{
		TX_TRACE1 ("Button kann nicht zur Toolbar hinzugefügt werden: %s\n", resTools.Addr());
		return _COM_ERROR(hr);
	}

	return S_OK;

} // InstallEditToolbar


//---------------------------------------------------------------------------------------------
// Entfernen der zusätzlich installierten ToolButtons aus der ToolBar "Werkzeuge"

// Im Prinzip das gleiche, wie das Installieren, nur das die Funktion DeleteItem() gerufen
// wird. CommandToIndex() liefert die aktuelle Position unseres Buttons über seinen CmdID.
HRESULT CGeoEditExtension::RemoveEditToolbar (void)
{
// Finden der ToolBar "Werkzeuge"
WTRiASBarContainer ToolBars;
HRESULT hr = m_pXtnSite->QueryInterface (IID_ITRiASBarContainer, ToolBars.ppv());

	if (FAILED(hr)) return hr;

WTRiASBar Bar;
ResString resTools (ResID (IDS_WERKZEUGETOOLBAR, &RF()), 32);	// "Werkzeuge" ist der Name der Toolbar

	hr = ToolBars->FindTRiASBar (resTools, Bar.ppi());
	if (S_OK != hr) return hr;

	try
	{
	// Entfernen der Buttons
	WTRiASToolBar ToolBar = Bar;		// throws_com_error
	int iIndex = -1;

		THROW_FAILED_HRESULT (ToolBar->CommandToIndex (ID_TOOL_PUNKTEDIT, &iIndex));
		THROW_FAILED_HRESULT (ToolBar->DeleteItem (iIndex));
		THROW_FAILED_HRESULT (ToolBar->CommandToIndex (ID_TOOL_LINIENEDIT, &iIndex));
		THROW_FAILED_HRESULT (ToolBar->DeleteItem (iIndex));
		THROW_FAILED_HRESULT (ToolBar->CommandToIndex (ID_TOOL_FLAECHENEDIT, &iIndex));
		THROW_FAILED_HRESULT (ToolBar->DeleteItem (iIndex));
		THROW_FAILED_HRESULT (ToolBar->CommandToIndex (ID_TOOL_MODIFYOBJ, &iIndex));
		THROW_FAILED_HRESULT (ToolBar->DeleteItem (iIndex));
		THROW_FAILED_HRESULT (ToolBar->CommandToIndex (ID_TOOL_MOVEOBJ, &iIndex));
		THROW_FAILED_HRESULT (ToolBar->DeleteItem (iIndex));
	}
	catch (_com_error& hr)
	{
		TX_TRACE1 ("Button kann nicht aus der Toolbar entfernt werden: %s\n", resTools.Addr());
		return _COM_ERROR(hr);
	}

	return S_OK;

} // RemoveEditToolbar


// --------------------------------------------------------------------------------------------
// Toolbar für die Bildung von Konstruktionshilfslinien in TRiAS einhängen
HRESULT CGeoEditExtension::InstallDesignToolbar (void)
{
// Lizensierung testen
#if _TRiAS_VER < 0x0400
	if (0 != g_dwVer4) 
#endif // _TRiAS_VER < 0x0400
	{
	VERIFYLICENSE VL;

		INITSTRUCT(VL, VERIFYLICENSE);
		VL.iMode = VERIFYMODE_DontShowDialog|VERIFYMODE_LessOrEqual;
		VL.lLevelOrOption = CKILEVEL_PLUS;
		if (!DEX_VerifyLicenseLevel(VL))
			return E_FAIL;
	}

TBBUTTON *pBtnCopy = NULL;

	try {
	WTRiASBarContainer BarCont (m_pXtnSite);
	WTRiASBar Bar;
	ResString strCap (ResID (IDS_DESIGNTOOLCAPTION, &RF()), 128);
	DWORD dwStyle = CBRS_ALIGN_TOP|CBRS_SIZE_DYNAMIC|CBRS_TOOLTIPS|
					CBRS_BORDER_ANY|CBRS_FLYBY|WS_VISIBLE;

		if (IsWin40()) dwStyle |= CBRS_BORDER_3D;

	// ToolBar erzeugen
	HRESULT hr = BarCont -> AddTRiASBar (strCap, dwStyle, TRIASTOOLBAR_PREDEFINED, Bar.ppi());

		if (FAILED(hr)) _com_issue_error (hr);

	// Bitmaps hinzufügen
	WTRiASToolBar ToolBar (Bar);	// throws HRESULT
	int iOffset = -1;

		hr = ToolBar -> AddBitmap (g_hInstance, IDB_TOOLBARDESIGN, BMPSIZE_DESIGN, &iOffset);
		if (FAILED(hr)) return hr;

		pBtnCopy = CopyButtons (tbDesign, NUMBUTTONS_DESIGN);
		if (NULL == pBtnCopy) _com_issue_error (E_OUTOFMEMORY);

	TBBUTTON *pCurr = pBtnCopy;

		for (int i = 0; i < NUMBUTTONS_DESIGN; i++, pCurr++) {
			if (!(TBSTYLE_SEP & pCurr -> fsStyle))
				pCurr -> iBitmap += iOffset;
		}
	
	// UIOwner erzeugen
	WTRiASUIOwner UIOwner;
	
		THROW_FAILED_HRESULT (CUIOwner::_CreatorClass::CreateInstance (NULL, IID_ITRiASUIOwner,
																	  (LPVOID*)UIOwner.ppi()));
		// Buttons hinzufügen
		hr = ToolBar -> AddButtons (pBtnCopy, NUMBUTTONS_DESIGN, UIOwner);
		if (FAILED(hr)) _com_issue_error (hr);

		hr = ToolBar -> DockBar (AFX_IDW_DOCKBAR_LEFT, &m_REC);
		if (FAILED(hr)) _com_issue_error (hr);

		DELETE_OBJ(pBtnCopy);

	} catch (_com_error &hr) {
		DELETE_OBJ(pBtnCopy);
		return _COM_ERROR(hr);
	}

return NOERROR;
}


// --------------------------------------------------------------------------------------------
// Toolbar für die Bildung von Konstruktionshilfslinien aus TRiAS entfernen
HRESULT CGeoEditExtension::RemoveDesignToolbar (void)
{
	try {
	WTRiASBarContainer BarCont (m_pXtnSite);
	ResString strCap (ResID (IDS_DESIGNTOOLCAPTION, &RF()), 128);

	// ToolBar beseitigen
		return BarCont -> DeleteTRiASBar (strCap);

	} catch (_com_error &hr) {
		return _COM_ERROR(hr);
	}
}
