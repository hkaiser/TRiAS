// Fenster in welchem Legende gezeichnet werden kann --------------------------
// File: LEGWIND.CXX

#include "triaspre.hxx"

#include <Com/ComBool.h>
#include <dirisole.h>
#include <SidManageTabs.h>

#include "extmain3.hxx"
#include "legdinfo.hxx"
#include "prlayout.hxx"
#include "legende.hxx"
#include "legwind.hxx"
#include "legtxted.hxx"
#include "ldroptgt.hxx"
#include "ldropsrc.hxx"
#include "LegendeCallback.h"

#include "triasres.h"
#include "strings.h"

///////////////////////////////////////////////////////////////////////////////
// TabWindowSupport
DefineSmartInterface(ManageTabWindows);
DefineSmartInterface(ServiceProvider);
DefineSmartInterface(DataObject);

extern bool LegendeCFlag;
extern HPALETTE hPalette;
extern HINSTANCE hInstance;
extern ExtDirisWindow *CurrActDirisW;	// Hauptfenster

#if _TRiAS_VER < 0x0400
///////////////////////////////////////////////////////////////////////////////
// Versionsspezifika beachten
extern DWORD g_dwVer4;
#endif // _TRiAS_VER < 0x0400

#define WM_SHOWLEGENDMENU	WM_USER+2000
#define WM_ENTRYSELECTED	WM_USER+2001
#define WM_ENTRYDESELECTED	WM_USER+2002

///////////////////////////////////////////////////////////////////////////////
// LegendeFenster 
/*static*/
HRESULT CLegendeWindow::RegisterTabWindow()
{
	COM_TRY {
	WServiceProvider SP;
	WManageTabWindows Tabs;

		_ASSERTE(NULL != CurrActDirisW);
		if (SUCCEEDED(CurrActDirisW -> EL().QueryInterface(__uuidof(IServiceProvider), SP.ppv())) &&
			SUCCEEDED(SP -> QueryService(SID_ManageProjectTabs, __uuidof(IManageTabWindows), Tabs.ppv()))) 
		{
		CComObject<CLegendeCallback> *pLegendeCB = NULL;

			THROW_FAILED_HRESULT(CComObject<CLegendeCallback>::CreateInstance(&pLegendeCB));

		WUnknown Unk (pLegendeCB -> GetUnknown());		// pending AddRef
		CComBSTR bstrLegend;
		
			bstrLegend.LoadString(IDS_LEGENDECAP);
			pLegendeCB -> SetCmdTarget (CurrActDirisW);
			THROW_FAILED_HRESULT(Tabs -> AddTabWindowDelayed(bstrLegend, pLegendeCB));
		}
	} COM_CATCH;
	return S_OK;
}

/*static*/
CLegendeClientWindow *CLegendeWindow::CreateInstance (
	pWindow pParent, char *pCaption, DatenBasisObjekt &rDBO) 
{
CLegendeClientWindow *pClient = NULL;

	COM_TRY {
	// Legendenfenster erzeugen
	CEierUhr Wait (pParent);

	// entscheiden, wo die Legende angezeigt werden soll
	WServiceProvider SP;
	WManageTabWindows Tabs;

		_ASSERTE(NULL != CurrActDirisW);
		if (SUCCEEDED(CurrActDirisW -> EL().QueryInterface(__uuidof(IServiceProvider), SP.ppv())) &&
			SUCCEEDED(SP -> QueryService(SID_ManageProjectTabs, __uuidof(IManageTabWindows), Tabs.ppv()))) 
		{
		// Anzeige erfolgt im DockingTab
		INT_PTR hHandle = NULL;
		CComBSTR bstrLegend;
		
			bstrLegend.LoadString(IDS_LEGENDECAP);
			pClient = CLegendeClientWindow::CreateInstance(rDBO);

			THROW_FAILED_HRESULT(Tabs -> AddTabWindow(reinterpret_cast<INT_PTR>(pClient ->Handle()), bstrLegend, pClient -> GetIcon(), &hHandle));
			_ASSERTE(reinterpret_cast<HWND>(hHandle) == pClient -> Handle());

			THROW_FAILED_HRESULT(Tabs -> ActivateTabWindow(hHandle));

		// ggf. Tabfenster anzeigen
		CComBool fVisible;

			THROW_FAILED_HRESULT(Tabs -> get_Visible(&fVisible));
			if (!fVisible)
				THROW_FAILED_HRESULT(Tabs -> put_Visible(VARIANT_TRUE));
		}
		else {
		// 'alten' Anzeigerahmen instantiieren und Legend dort einfügen
		CLegendeWindow *pLeg = new CLegendeWindow (pParent, pCaption);

			pClient = new CLegendeClientWindow(rDBO, pLeg);
			if (pLeg == NULL || !pLeg -> FInit(pClient)) {
				DELETE_OBJ (pLeg);
				return NULL;
			}
			DEX_KickIdle();

		// das Ganze anzeigen
			pClient -> Show(ShowState(Normal|NoActivate));
			pLeg -> Show (ShowState(Normal|NoActivate));
		}

	} COM_CATCH_RETURN(NULL);
	return pClient;
}

bool CLegendeClientWindow::ReShow()
{
	COM_TRY {
	// Legendenfenster erzeugen
	CEierUhr Wait (this);

	// Legende muß im DockingFenster angezeigt sein
	WServiceProvider SP;
	WManageTabWindows Tabs;

		_ASSERTE(NULL != CurrActDirisW);
		THROW_FAILED_HRESULT(CurrActDirisW -> EL().QueryInterface(__uuidof(IServiceProvider), SP.ppv()));
		THROW_FAILED_HRESULT(SP -> QueryService(SID_ManageProjectTabs, __uuidof(IManageTabWindows), Tabs.ppv()));

	INT_PTR hHandle = NULL;
	CComBSTR bstrLegend;
	
		bstrLegend.LoadString(IDS_LEGENDECAP);
		THROW_FAILED_HRESULT(Tabs -> FindTabWindow(bstrLegend, &hHandle));
		_ASSERTE(reinterpret_cast<HWND>(hHandle) == Handle());

		THROW_FAILED_HRESULT(Tabs -> ActivateTabWindow(hHandle));

	// ggf. Tabfenster anzeigen
#if defined(_DEBUG)
	CComBool fVisible;

		THROW_FAILED_HRESULT(Tabs -> get_Visible(&fVisible));
		_ASSERTE(!fVisible);
#endif // defined(_DEBUG)
		THROW_FAILED_HRESULT(Tabs -> put_Visible(VARIANT_TRUE));

	} COM_CATCH_RETURN(false);
	return true;
}


void CLegendeWindow::DeleteInstance(CLegendeClientWindow *& pLegend)
{
	COM_TRY {
	// entscheiden, wo die Legende angezeigt wurde
	WServiceProvider SP;
	WManageTabWindows Tabs;

		_ASSERTE(NULL != CurrActDirisW);
		if (SUCCEEDED(CurrActDirisW -> EL().QueryInterface(__uuidof(IServiceProvider), SP.ppv())) &&
			SUCCEEDED(SP -> QueryService(SID_ManageProjectTabs, __uuidof(IManageTabWindows), Tabs.ppv()))) 
		{
		// Anzeige erfolgte im DockingTab
			_ASSERTE(NULL == pLegend -> GetParentWindow());
			THROW_FAILED_HRESULT(Tabs -> DeleteTabWindow(reinterpret_cast<INT_PTR>(pLegend -> Handle())));
			DELETE_OBJ(pLegend);

		// ggf. TabFenster ausblenden (wenns die letzte TabLasche war)
		int iCount = 0;

			THROW_FAILED_HRESULT(Tabs -> get_Count(&iCount));
			if (0 == iCount) {
			CComBool fVisible;

				THROW_FAILED_HRESULT(Tabs -> get_Visible(&fVisible));
				if (fVisible) 
					THROW_FAILED_HRESULT(Tabs -> put_Visible(VARIANT_FALSE));
			}
		}
		else {
		// Anzeige erfolgte im 'alten' Anzeigerahmen
			_ASSERTE(NULL != pLegend -> GetParentWindow());
			pLegend -> GetParentWindow() -> Hide();
			delete pLegend -> GetParentWindow();
			DELETE_OBJ(pLegend);
		}
	} COM_CATCH_NORETURN;
}

CLegendeWindow::CLegendeWindow (pWindow pParent, char *pCaption) :
	DialogWindow (pParent, ResID (LEGENDEDLG), false),
	m_LMenu (LEGENDEMENU), m_pLegend(NULL)
{
// Überschrift setzen
	SetCaption (pCaption);
	ChangeMenu (&m_LMenu);
	
// Menupunkte eines Fensters mit SysMenu entfernen
HMENU hSysMenu = ::GetSystemMenu (Handle(API_WINDOW_HWND), false);

	::RemoveMenu (hSysMenu, SC_MINIMIZE, MF_BYCOMMAND);
	::RemoveMenu (hSysMenu, SC_RESTORE, MF_BYCOMMAND);
	::RemoveMenu (hSysMenu, SC_MAXIMIZE, MF_BYCOMMAND);

#if _TRiAS_VER < 0x0400
// Versionsspezifika beachten
	if (0 == g_dwVer4) 
		m_LMenu.DeleteItem (IDM_ENTERHEADLINE);
#endif // _TRiAS_VER < 0x0400
}

bool CLegendeWindow::FInit (CLegendeClientWindow *pClient)
{
	_ASSERTE(NULL != pClient);
	m_pLegend = pClient;
	
// Kontextmenu im Hauptmenu passivieren
	ResetSelection();

// Größe und Lage Voreinstellen
Rectangle rcC = GetParent() -> CanvasRect();
short iWidth = ((rcC.Right()-rcC.Left())*5)/16;
Point ptOrg (rcC.Right()-iWidth, 0);

// LegendeFenster maximal so hoch machen, wie Client vom Hauptfenster
	ChangeSize (Dimension (iWidth, rcC.Top()-rcC.Bottom()));
	ChangePosition (ptOrg);

Rectangle rcL (CanvasRect());
Dimension dim;

	if (!m_pLegend -> FInit(&rcL, &dim))
		return false;

// Fenster positionieren
	ptOrg.Y() = ((rcC.Top()-rcC.Bottom()) - ptOrg.Y());
	
Rectangle rcT (ptOrg, Dimension (dim.Width(), -dim.Height()));

	AdjustWindowRectEx ((RECT *)&rcT, WS_CHILD|WS_CAPTION|WS_THICKFRAME, true, IsWin40() ? WS_EX_TOOLWINDOW : 0);

	ChangeSize (Dimension (rcT.Right()-rcT.Left(), rcT.Bottom()-rcT.Top()));
	ChangePosition (Point (rcT.Left(), 0));
	return true;
}

CLegendeWindow::~CLegendeWindow (void) 
{
}

BOOL CLegendeWindow::QueryClose (Event) 
{
// Legende speichern, wenn notwendig
CEierUhr Wait (this);

	SaveLegend();

// Legende ausblenden
	if (LegendeCFlag) 
	// wenn über Systemmenu geschlossen, dann MenuPunkt simulieren
		GetParent() -> PostEvent (WM_COMMAND, IDM_LEGENDE);	

	return TRUE;	// auf jeden Fall raus
}

LRESULT CLegendeWindow::Dispatch (Event e)
{
	switch (e.Msg()) {
	case WM_ENTRYSELECTED:
		EnableMenuItem (m_LMenu.Handle(), 1, MF_BYPOSITION | MF_ENABLED);
		DrawMenuBar (Handle(API_WINDOW_HWND));
		break;

	case WM_ENTRYDESELECTED:
		EnableMenuItem (m_LMenu.Handle(), 1, MF_BYPOSITION | MF_GRAYED);
		DrawMenuBar (Handle(API_WINDOW_HWND));
		break;
	}
	return DialogWindow::Dispatch(e);
}

///////////////////////////////////////////////////////////////////////////////
// MenuPunkte angeklickt 
void CLegendeWindow::MenuCommand (MenuCommandEvt e)
{
	m_pLegend -> MenuCommand(e);
}

///////////////////////////////////////////////////////////////////////////////
// MenuInitialisierungen 
void MenuCheck (pMenu pM, int MenuItem, bool Flag);
void MenuEnable (pMenu pM, int MenuItem, bool Flag);

void CLegendeWindow::MenuInit (MenuInitEvt e)
{
// Hauptmenu initialisieren
	MenuCheck (&m_LMenu, IDM_FITLEGENDENTRIES, m_pLegend -> GetFitFont());
	MenuCheck (&m_LMenu, IDM_SHOWALLENTRIES, m_pLegend -> GetShowAll());
	MenuCheck (&m_LMenu, IDM_LEGENDE_ANAUSSCHNITTANPASSEN, m_pLegend -> GetShowAreaOnly());
	MenuCheck (&m_LMenu, IDM_SIZESLIKESCALING, !m_pLegend -> GetScaleMode());

HMENU hMenu = GetSubMenu (m_LMenu.Handle(API_MENU_HMENU), 0);
	
// Ein Trick am Rande, der erlaubt die Legende on the fly zu speichern.
// (mit der ControlTaste das erste SubMenu der Legende öffnen :-) )

	if (GetKeyState (VK_CONTROL) < 0) {	// ControlTaste gedrückt
		ModifyMenu (hMenu, 6,	// letzter Eintrag
			    MF_BYPOSITION|MF_UNCHECKED, 
			    IDM_LEGENDSAVE, ResString (IDS_LEGENDSAVE, 64).Addr());
	} 
	else {	// Normaler Mode
		ModifyMenu (hMenu, 6,	// letzter Eintrag
			    MF_BYPOSITION|MF_UNCHECKED, 
			    IDM_LEGENDRESET, ResString (IDS_LEGENDRESET, 64).Addr());
	}
	
//	MenuEnable (&m_LMenu, IDM_LEGENDRESET, m_pLO -> isDirty());
//	MenuEnable (&m_LMenu, IDM_LEGENDSELFONT, !m_fFitFont);

WORD iActSelection = m_pLegend -> GetActSelection();

	if (USHRT_MAX == iActSelection) 
		return;
	
// KontextMenu im Hauptmenu initialisieren
bool fShown = m_pLegend -> GetIsShown(iActSelection);
bool fSpace = m_pLegend -> GetHasSpace (iActSelection);
bool fIdentEntry = (LEGENTRYTYPE_IDENT == m_pLegend -> GetIsA(iActSelection)) ? true : false;
bool fSpaceLine = (LEGENTRYTYPE_SPACELINE == m_pLegend -> GetIsA(iActSelection)) ? true : false;
bool fTextEntry = (LEGENTRYTYPE_TEXT == m_pLegend -> GetIsA(iActSelection)) ? true : false;
bool fCustText = m_pLegend -> GetCustomizedText (iActSelection);
bool fNotFirst = !m_pLegend -> GetIsFirstEntry (iActSelection);
bool fNotLast = !m_pLegend -> GetIsLastEntry (iActSelection);

	hMenu = GetSubMenu (m_LMenu.Handle(API_MENU_HMENU), 1);

// Identifikator/ObjektEintrag
	if (fIdentEntry) {	// IdentifikatorEintrag
		ModifyMenu (hMenu, 0,	// erster Eintrag
			    MF_BYPOSITION|MF_ENABLED | (fShown ? MF_CHECKED : MF_UNCHECKED), 
			    IDM_LEGENTRYSHOWENTRY, ResString (IDS_LEGENTRYSHOW, 64).Addr());
	} else {		// ObjektEintrag
		ModifyMenu (hMenu, 0,	// erster Eintrag
				MF_BYPOSITION|MF_UNCHECKED|MF_ENABLED, 
				IDM_LEGENTRYREMOVEENTRY, ResString (IDS_LEGENTRYREMOVE, 64).Addr());
	}

// Leerzeile vorhanden/nicht vorhanden
	if (fSpace) {	// Leerzeile vorhanden
		ModifyMenu (hMenu, 5,	// fünfter Eintrag
			    MF_BYPOSITION|MF_UNCHECKED|MF_ENABLED, IDM_REMOVESPACELINE, 
			    ResString (IDS_REMOVESPACELINE, 64).Addr());
	} else {		// ObjektEintrag
#if _TRiAS_VER < 0x0400
		ModifyMenu (hMenu, 5,	// fünfter Eintrag
			    MF_BYPOSITION|MF_UNCHECKED|((fNotLast || 0 != g_dwVer4) ? MF_ENABLED : MF_GRAYED), 
			    IDM_ENTERSPACELINE, ResString (IDS_ENTERSPACELINE, 64).Addr());
#else
		ModifyMenu (hMenu, 5,	// fünfter Eintrag
			    MF_BYPOSITION|MF_UNCHECKED|MF_ENABLED, 
			    IDM_ENTERSPACELINE, ResString (IDS_ENTERSPACELINE, 64).Addr());
#endif // _TRiAS_VER < 0x0400
	}

// ist eine Zwischenüberschrift
#if _TRiAS_VER < 0x0400
// Versionsspezifika beachten
	if (0 != g_dwVer4) 
#endif // _TRiAS_VER < 0x0400
	{
		EnableMenuItem (hMenu, IDM_LEGENTRYRESETTEXT, MF_BYCOMMAND|MF_UNCHECKED|((fTextEntry || fSpaceLine || fCustText) ? MF_ENABLED : MF_GRAYED));
		EnableMenuItem (hMenu, IDM_LEGENTRYEDITTEXT, MF_BYCOMMAND|MF_UNCHECKED|(fSpaceLine ? MF_GRAYED : MF_ENABLED));
	}
#if _TRiAS_VER < 0x0400
	else
		EnableMenuItem (hMenu, IDM_LEGENTRYRESETTEXT, MF_BYCOMMAND|MF_UNCHECKED|(fCustText ? MF_ENABLED : MF_GRAYED));
#endif // _TRiAS_VER < 0x0400

	MenuEnable (&m_LMenu, IDM_LEGENTRYVISPARAMS, fIdentEntry);
	MenuEnable (&m_LMenu, IDM_LEGENTRYRESETTEXT, fCustText);
	MenuEnable (&m_LMenu, IDM_LEGENTRYMOVEUP, fNotFirst);
	MenuEnable (&m_LMenu, IDM_LEGENTRYMOVEDOWN, fNotLast);

	m_pLegend -> MenuInit(e);
}

void CLegendeWindow::ReSize (ReSizeEvt evt) 
{	
	m_pLegend -> ChangePosition(Point());
	m_pLegend -> ChangeSize(evt.GetNewSize());
}

HBRUSH WINAPI CreateInvBrush (void)
{
HBITMAP hBM = LoadBitmap (hInstance, MAKEINTRESOURCE (IDB_INVPATTERN));

	if (hBM == NULL) return NULL;
	
HBRUSH hBr = CreatePatternBrush (hBM);

	DeleteObject (hBM);
	return hBr;
}
  
///////////////////////////////////////////////////////////////////////////////
// CLegendeClientWindow
/*static*/
CLegendeClientWindow *CLegendeClientWindow::CreateInstance(
	DatenBasisObjekt &rDBO, CLegendeWindow *pParent)
{
CLegendeClientWindow *pClient = NULL;

	ATLTRY(pClient = new CLegendeClientWindow(rDBO, pParent));
	if (NULL == pClient || !pClient -> FInit()) {
		DELETE_OBJ(pClient);
		return NULL;
	}
	return pClient;
}

CLegendeClientWindow::CLegendeClientWindow(DatenBasisObjekt &rDBO, CLegendeWindow *pParent) :
	ChildAppWindow ((NULL != pParent) ? pParent : (pWindow)CurrActDirisW, ID_LEGEND_CLIENT, (LPSTR)g_cbLegendClass, /*IsWin40() ? WS_EX_CLIENTEDGE : */0),
	m_rDBO(rDBO)
{
// Mode initialisieren
	m_fFitFont = true;			// Default: Font anpassen
	m_fSetScrollBars = false;	// HilfsFlag
	m_fPainting = false;		// Semaphore für Zeichnen
	m_fShowMenu = false;
	m_fSelRect = false;
	m_fPendingReSel = false;
	m_fNeedsCalculation = true;
			
	m_pVertSB = NULL;
	m_pHorzSB = NULL;
	m_pLO = NULL;
	m_pParent = pParent;
	m_hMenu = NULL;
	m_pbkBrush = NULL;
	m_pTabIcon = NULL;

	m_iActSelection = 0;		// damit ResetSelection() funktioniert
				
	m_fBrushToDelete = false;
	m_fIsDropSource = false;	
	m_pDropTgt = NULL;
	m_iDropPos = -1;
	m_iDropOrder = USHRT_MAX;
	m_iClipOrder = USHRT_MAX;
	m_uiScrollInset = g_dwScrollInset;
	m_uiScrollDelay = g_dwScrollDelay;
	m_uiHorzScrollCode = USHRT_MAX;
	m_uiVertScrollCode = USHRT_MAX;
	m_uiLastTest = UDROP_NONE;
	m_dwTimeLast = 0L;
		
	m_hWnd = Handle (API_WINDOW_HWND);

	m_hAccel = NULL;
}

bool CLegendeClientWindow::FInit (Rectangle *prcParentCanvas, Dimension *pDim)
{
// DragDrop-initialisierungen
	m_cf = RegisterClipboardFormat (ResString (IDS_LEGENDCLIPBOARDFMT, 30));

	m_hBr = CreateInvBrush();
	if (m_hBr == NULL) {
		m_hBr = (HBRUSH)GetStockObject (GRAY_BRUSH);
		m_fBrushToDelete = false;
	} else
		m_fBrushToDelete = true;

// Hintergrundfarbe setzen
	ATLTRY(m_pbkBrush = new Brush(Color((Colors)255, (Colors)255, (Colors)255)));
	if (NULL == m_pbkBrush) return false;
	ChangeBackground (m_pbkBrush);        // Hintergrund setzen

// anlegen und registrieren des DropTargets
	m_pDropTgt = new CLegWindDropTarget (this);
	if (m_pDropTgt != NULL)	{
		m_pDropTgt -> AddRef();
		CoLockObjectExternal ((LPUNKNOWN)m_pDropTgt, true, false);
		RegisterDragDrop (m_hWnd, (LPDROPTARGET)m_pDropTgt);
	}
		
	ATLTRY(m_pLO = CLegendeObjekt::CreateInstance (this, m_rDBO));
	if (NULL == m_pLO) return false;		// Fehler

// ggf. Größe selbst berechnen
	if (NULL != prcParentCanvas) {
	bool fFitWidth = true;	
	Dimension dim;

		if (m_fFitFont) 
			dim = m_pLO -> FitLegendSize (prcParentCanvas);				// Größe mit Anpassen
		else
			dim = m_pLO -> GetRealSize (prcParentCanvas, fFitWidth);	// Größe ohne Anpassen

		if (NULL != pDim)
			*pDim = dim;
		m_fNeedsCalculation = false;
	}

// Acceleratoren laden
	m_hAccel = ::LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_LEGMENUACCEL));
	_ASSERTE(NULL != m_hAccel);

	return true;
}

CLegendeClientWindow::~CLegendeClientWindow (void) 
{
CEierUhr Wait (this);

	SaveLegend();		// evtl. wegschreiben
	DELETE_OBJ(m_pLO);

	ChangeBackground(NULL);
	DELETE_OBJ(m_pbkBrush);
	DELETE_OBJ(m_pTabIcon);

	if (m_fBrushToDelete)
		DeleteObject (m_hBr);

// DropTarget abmelden, wenn's noch nicht passiert ist
	if (m_pDropTgt) {
		RevokeDragDrop (m_hWnd);
		CoLockObjectExternal ((LPUNKNOWN)m_pDropTgt, false, true);
		m_pDropTgt -> Release();
		m_pDropTgt = NULL;
	}
}

CComVariant CLegendeClientWindow::GetIcon()
{
CComVariant vIcon;

	if (NULL == m_pTabIcon) {
		ATLTRY(m_pTabIcon = new Icon(ResID(IDI_LEGEND)));
		if (NULL == m_pTabIcon) return vtMissing;
	}

// das IconHandle der Einfachheit halber direkt liefern
	V_VT(&vIcon) = VT_I4;
	V_I4(&vIcon) = reinterpret_cast<INT_PTR>(m_pTabIcon -> Handle());
	return vIcon;
}

BOOL CLegendeClientWindow::QueryClose (Event) 
{
// Legende speichern, wenn notwendig
CEierUhr Wait (this);

	SaveLegend();

// DropTarget abmelden
	if (m_pDropTgt) {
		RevokeDragDrop (m_hWnd);
		CoLockObjectExternal ((LPUNKNOWN)m_pDropTgt, false, true);
		m_pDropTgt -> Release();
		m_pDropTgt = NULL;
	}
	return TRUE;	// auf jeden Fall raus
}

///////////////////////////////////////////////////////////////////////////////
// Legende neu zeichnen (entsprechend aktueller Sicht) 
void CLegendeClientWindow::Expose (ExposeEvt e) 
{
	if (NULL == m_pLO) return;

	if (!m_fPainting) {
	CEierUhr Wait (this);
	
		m_fPainting = true;
	
	Rectangle rcL (CanvasRect());
	Rectangle rcEA (e.GetExposedArea());
	bool fFitWidth = true;
	
	// das Rechteck muß auch gekippt werden, da CLegendeClientWind::DrawEx ein WindowsRECT erwartet
	CoOrd dY = rcL.Top() - rcL.Bottom();
	
		rcEA.Top() = dY - rcEA.Top();
		rcEA.Bottom() = dY - rcEA.Bottom();

		if (m_fNeedsCalculation) {
			if (m_fFitFont) 
				m_Dim = m_pLO -> FitLegendSize (&rcL);			// Größe mit Anpassen
			else 
				m_Dim = m_pLO -> GetRealSize (&rcL, fFitWidth);	// Größe ohne Anpassen

			m_fNeedsCalculation = false;
		}
			
		if (m_fSetScrollBars) {
			SetScrollRanges();
			m_fSetScrollBars = false;
		}

	// gesamte aktuelle Legende zeichnen
		DrawEx (m_pLO, (DWORD)&rcEA);

		ShowSelection (m_iActSelection, true);	// SelRect einblenden
		DrawDropSelection (rcL);				// DropSelection neu zeichnen
		m_fPainting = false;
	}
}

BOOL CLegendeClientWindow::PreTranslateMsg (MSG *pMsg)		// Accels bearbeiten
{
	if (m_hAccel && ::TranslateAccelerator(m_hWnd, m_hAccel, pMsg))
		return true;
	return ChildAppWindow::PreTranslateMsg(pMsg);			// nicht für uns
}

void CLegendeClientWindow::ReSize (ReSizeEvt evt) 
{	
// ScrollBereich neu setzen
	if (!m_fFitFont)
		SetScrollRanges ();

	m_fNeedsCalculation = true;			// Font neu berechnen
	HideSelection (m_iActSelection);	// SelRect ausblenden
	RePaint();	// neu zeichnen
}

///////////////////////////////////////////////////////////////////////////////
// ScrollSupport
void CLegendeClientWindow::HorizScroll (ScrollEvt e) 
{
	if (m_pHorzSB == NULL) return;		// kein ScrollBalken da
	
Range HorzR;
short iPos, dn;
Rectangle rcT;

// neue vertikale Rollposition berechnen
	HorzR = m_pHorzSB -> GetRange();
	iPos = e.GetOldPos();
	rcT = CanvasRect();
	switch (e.GetScrollType()) {
	case UnitDecrement:		dn = -rcT.Right() / 16 + 1; break;
	case UnitIncrement:		dn =  rcT.Right() / 16 - 1; break;
	case BlockDecrement:	dn = -rcT.Right() / 2 + 1; break;
	case BlockIncrement:	dn =  rcT.Right() / 2 - 1; break;
	case ThumbDrag:			dn =  e.GetPos() - iPos; break;
	default:				dn =  0; break;
	}

// Rollen auf aktuellen Rollbereich begrenzen
	if ((dn = BOUND (iPos + dn, 0, HorzR.Max() - m_pHorzSB -> GetPageSize()) - iPos) != 0) {
		HideSelection (m_iActSelection);
		Scroll (Dimension (-dn, 0), rcT);
		m_pHorzSB -> SetThumbPos (iPos + dn);
		if (m_pLO) m_pLO -> m_ptOrg.X() = iPos + dn;
	}
}

void CLegendeClientWindow::VertScroll (ScrollEvt e) 
{
	if (m_pVertSB == NULL) return;		// kein ScrollBalken da

Range VertR;
short iPos, dn;
Rectangle rcT;

// neue vertikale Rollposition berechnen
	VertR = m_pVertSB -> GetRange();
	iPos = m_pVertSB -> GetThumbPos();
	rcT = CanvasRect();
	switch (e.GetScrollType()) {
	case UnitDecrement:		dn = -rcT.Top() / 16 + 1; break;
	case UnitIncrement:		dn =  rcT.Top() / 16 - 1; break;
	case BlockDecrement:	dn = -rcT.Top() / 2 + 1; break;
	case BlockIncrement:	dn =  rcT.Top() / 2 - 1; break;
	case ThumbDrag:			dn =  m_pVertSB -> GetTrackPos() - iPos; break;
	default:				dn =  0; break;
	}

// Rollen auf aktuellen Rollbereich begrenzen
	if ((dn = BOUND (iPos + dn, 0, VertR.Max() - m_pVertSB -> GetPageSize()) - iPos) != 0) {
		HideSelection (m_iActSelection);
		Scroll (Dimension (0, dn), rcT);
		m_pVertSB -> SetThumbPos (iPos + dn);
		if (m_pLO) m_pLO -> m_ptOrg.Y() = -(iPos + dn);
	}
}

///////////////////////////////////////////////////////////////////////////////
// ScrollBereiche neu setzen 
void CLegendeClientWindow::SetScrollRanges (void) 
{
Rectangle rcT;
static int iScrollSem = 0;
CoOrd iRangeH, iRangeV, i;

	if (!iScrollSem) {
		iScrollSem++;
		for (i = 0; i < 2; i++) {
			rcT = RealCanvasRect();
			iRangeV = m_Dim.Height() - (rcT.Top()-rcT.Bottom());
			iRangeH = m_Dim.Width() - rcT.Right();
			if (iRangeH < 0) iRangeH = 0;
			if (iRangeV < 0) iRangeV = 0;

		// etwas neuzeichnen ?
		int yThumbPos = m_pVertSB != NULL ? m_pVertSB -> GetThumbPos() : 0;
		int xThumbPos = m_pHorzSB != NULL ? m_pHorzSB -> GetThumbPos() : 0;

			if ((iRangeV && yThumbPos >= iRangeV) || 
			    (iRangeH && xThumbPos >= iRangeH)) 
			{
				HideSelection (m_iActSelection);	// SelRect ausblenden
				RePaint();
			}

		// ScrollBalken anzeigen bzw. löschen
			if (iRangeV > 0) {
				m_pVertSB = EnableVScroll (true);
				m_pVertSB -> SetRange (Range (0, m_Dim.Height()));
				m_pVertSB -> SetPageSize(rcT.Top()-rcT.Bottom());
			} else {
				if (m_pVertSB) m_pVertSB -> SetRange (Range (0, 0));
				m_pVertSB = EnableVScroll (false);
				if (m_pLO) m_pLO -> m_ptOrg.Y() = 0;
			}
			if (iRangeH > 0) {
				m_pHorzSB = EnableHScroll (true);
				m_pHorzSB -> SetRange (Range (0, m_Dim.Width()));
				m_pHorzSB -> SetPageSize(rcT.Right());
			} else {
				if (m_pHorzSB) m_pHorzSB -> SetRange (Range (0, 0));
				m_pHorzSB = EnableHScroll (false);
				if (m_pLO) m_pLO -> m_ptOrg.X() = 0;
			}
			SetStyle(WS_BORDER, CVOff);		// Border auf jeden Fall ausschalten

		// zweite Runde
//			rcT = CanvasRect();
		}
		iScrollSem--;
	}
}

// Berechnung der ClientFlaeche unter Berücksichtigung der Rollbalken
Rectangle CLegendeClientWindow::RealCanvasRect (void) 
{
long dwStyle = GetWindowLong (Handle (API_CLIENT_HWND), GWL_STYLE);
							// FensterStil
Rectangle rcT = CanvasRect();

	if (dwStyle & WS_HSCROLL)
		rcT.Bottom() += GetSystemMetrics (SM_CYHSCROLL);
	if (dwStyle & WS_VSCROLL)
		rcT.Right() -= GetSystemMetrics (SM_CXVSCROLL);

	return rcT;
}

///////////////////////////////////////////////////////////////////////////////
// MouseEvents auswerten 
void CLegendeClientWindow::MouseButtonDn (MouseEvt e)
{
	if (m_pLO == NULL || m_hMenu) 
		return;		// Fehler, oder Menu offen: nichts tun
	
Point pt (e.Where());
WORD iOrder = FindEntry (pt);	// passenden Einrag finden

	if (USHRT_MAX == iOrder) {
	// nichts selektiert
		if (NULL == m_pParent && e.isRightButton()) {
		// standalone: Hauptmenu anzeigen
			pt.Y() += m_pLO -> m_ptOrg.Y();		// korrigieren
			PostEvent (WM_SHOWLEGENDMENU, ULONG_MAX, MAKELONG (pt.X(), pt.Y()));
		}
	}

	if (e.isRightButton()) {
	// Rechteck zeichnen
		if (ShowSelection (iOrder)) {
		// Menu anzeigen
			pt.Y() += m_pLO -> m_ptOrg.Y();		// korrigieren
			PostEvent (WM_SHOWLEGENDMENU, iOrder, MAKELONG (pt.X(), pt.Y()));
		} else 
			ResetSelection();	// nichts aktiv
	} 
	else if (e.isLeftButton()) {
		if (iOrder == m_iActSelection) 
		// erst beim MouseButtonUp Selektion löschen
			m_fPendingReSel = true;
		else
			ShowSelection (iOrder);		// neue Selektion setzen
	}
}

void CLegendeClientWindow::MouseButtonUp (MouseEvt e)
{
Point pt = e.Where();
WORD iOrder = FindEntry (pt);	// passenden Einrag finden

	if (e.isLeftButton() && m_fPendingReSel) {
	// alte Selektion muß evtl. gelöscht werden
		if (iOrder == m_iActSelection) {
			HideSelection (iOrder);		// Selektion freigeben
			ResetSelection();
		} else
			ShowSelection (iOrder);
		m_fPendingReSel = false;
	}
}

void CLegendeClientWindow::MouseDrag (MouseEvt e)
{
	if (!e.isLeftButton()) return;		// Drag beginnt mit linker Taste
	
Point pt (e.Where());

	m_iClipOrder = FindEntry (pt);		// passenden Einrag finden
	if (m_iClipOrder == USHRT_MAX || m_iClipOrder != m_iActSelection)
		return;

// zu bewegende Daten erzeugen
LPDATAOBJECT pIDataObject = TransferObjectCreate (m_iClipOrder);
SCODE sc = E_FAIL;
DWORD dwEffect;

	if (pIDataObject != NULL) {
	// DropSource generieren
	CLegWindDropSource *pIDropSrc = NULL;
	
		TX_TRY(pIDropSrc = new CLegWindDropSource (this));
		if (pIDropSrc == NULL) {
			m_iClipOrder = USHRT_MAX;
			return;		// kein Drop möglich
		}
		pIDropSrc -> AddRef();
		m_fIsDropSource = true;
		
	HRESULT hr = DoDragDrop (pIDataObject, pIDropSrc, 
				 DROPEFFECT_MOVE|DROPEFFECT_COPY, &dwEffect);

		m_fIsDropSource = false;	
		pIDropSrc -> Release();		// DropSource freigeben
		pIDataObject -> Release();	// Daten freigeben

		sc = GetScode (hr);		// Resultat der Aktion merken
	}

	if (sc == DRAGDROP_S_DROP) {
		if (dwEffect == DROPEFFECT_MOVE) 
			FClipEntry (m_iClipOrder);	// alten Eintrag rausnehmen
		RePaint();
	}
	m_iClipOrder = USHRT_MAX;
}

void CLegendeClientWindow::MouseButtonDblClk (MouseEvt) 
{
}

void CLegendeClientWindow::KeyDown (KeyEvt e) 
{ 
#if 0 // ======================================================================
// wenn nichts selektiert ist, dann weiter
	if (m_iActSelection == USHRT_MAX) return;
	
// selektiertes Item verschieben
	if (e.ASCIIChar() == '\0') {
		switch (e.Keycode()) {
		case VK_UP:
			if (!m_pLO -> isFirstEntry (m_iActSelection))
				PostEvent (WM_COMMAND, IDM_LEGENTRYMOVEUP);
			return;

		case VK_DOWN:
			if (!m_pLO -> isLastEntry (m_iActSelection))
				PostEvent (WM_COMMAND, IDM_LEGENTRYMOVEDOWN);
			return;
		}
	}
#endif // =====================================================================
}

LRESULT CLegendeClientWindow::Dispatch (Event e)
{
	switch (e.Msg()) {
	case WM_SHOWLEGENDMENU:
		if (!m_fShowMenu) {
			m_fShowMenu = true;
			ShowMenu (e.WParam(), LOWORD(e.LParam()), HIWORD(e.LParam()));
			m_fShowMenu = false;
		}
		return true;

	default:
		break;
	}
	return ChildAppWindow::Dispatch (e);
}

///////////////////////////////////////////////////////////////////////////////
// Kontextmenu anzeigen 
void CLegendeClientWindow::ShowMenu (WORD wOrder, int X, int Y)
{
// Menu generieren und anzeigen
Menu menuLeg (LEGENDEMENU);
Point Pt (X, Y);

#if _TRiAS_VER < 0x0400
// Versionsspezifika beachten
	if (0 == g_dwVer4) 
		menuLeg.DeleteItem (IDM_ENTERHEADLINE);
#endif // _TRiAS_VER < 0x0400

	_ASSERTE(USHRT_MAX != wOrder || NULL == m_pParent);		// Hauptmenu nur wenn standalone
	m_hMenu = GetSubMenu (menuLeg.Handle(API_MENU_HMENU), (USHRT_MAX == wOrder) ? 0 : 1);	// SubMenu holen

	ClientToScreen (m_hWnd, (LPPOINT)&Pt);
	if (!TrackPopupMenu (m_hMenu, 0, Pt.X(), Pt.Y(), 0, m_hWnd, NULL)) {	
	// Fehler 
		HideSelection (m_iActSelection);
		ResetSelection();
	}
	m_hMenu = 0;
}

///////////////////////////////////////////////////////////////////////////////
// Legende neu generieren bei Sichtwechsel etc. 
bool CLegendeClientWindow::RefreshLegend (void)
{ 
CEierUhr Wait (this);

	m_fNeedsCalculation = true;
	return m_pLO -> RefreshLegend(); 
}

///////////////////////////////////////////////////////////////////////////////
// Selektion zurücksetzen
bool CLegendeClientWindow::ResetSelection (void)
{
	if (m_iActSelection == USHRT_MAX)
		return false;

WORD iOldSel = m_iActSelection;
HWND hParent = ::GetParent(m_hWnd);

	m_iActSelection = USHRT_MAX;
	PostMessage (hParent, WM_ENTRYDESELECTED, iOldSel, 0);
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// SelectionsRechteck ausblenden/anzeigen 
bool CLegendeClientWindow::HideSelection (WORD iOrder)
{
	if (m_pLO == NULL || !m_fSelRect || iOrder == USHRT_MAX) 
		return false;

Rectangle rc (CanvasRect());
CoOrd iScrPos = m_pLO -> m_ptOrg.Y();
Range r;

	if (m_pLO -> GetEntrySize (iOrder, r)) {
		rc.Top() = r.Min() + iScrPos;
		rc.Bottom() = r.Max() + iScrPos;
		PaintSelection (rc);
		m_fSelRect = false;
		return true;
	}
	return false;
}

// Selektiert einen Eintrag, wenn ein anderer Selektiert war, dann wird dieser
// vorher deselektiert, Ist der Eintrag selbst bereits selektiert, passiert
// garnichts
bool CLegendeClientWindow::ShowSelection (WORD iOrder, bool fForce)
{
	if (m_pLO == NULL || iOrder == USHRT_MAX) return false;

	if (m_fSelRect && !fForce) {
		if (m_iActSelection == iOrder) 
			return true;
		HideSelection (m_iActSelection);	// anderes deselektieren
	}
				
Rectangle rc (CanvasRect());
CoOrd iScrPos = m_pLO -> m_ptOrg.Y();
Range r;

	if (m_pLO -> GetEntrySize (iOrder, r)) {
		rc.Top() = r.Min() + iScrPos;
		rc.Bottom() = r.Max() + iScrPos;
		m_iActSelection = iOrder;
		PaintSelection (rc);

	HWND hParent = ::GetParent(m_hWnd);

		PostMessage(hParent, WM_ENTRYSELECTED, m_iActSelection, 0);
		m_fSelRect = true;
		return true;
	}
	return false;
}		

// SelektionsRechteck zeichnen 
#define DD		2		// Dicke der SelektionsLinie [Pixel]

void CLegendeClientWindow::PaintSelection (Rectangle &rRc)
{
HDC hDC = GetDC (m_hWnd);

// Rechteck zeichnen
	PatBlt (hDC, rRc.Left(), rRc.Top()-DD, rRc.Right()-rRc.Left(), DD, DSTINVERT);		// Top
	PatBlt (hDC, rRc.Left(), rRc.Bottom()-DD, rRc.Right()-rRc.Left(), DD, DSTINVERT);	// Bottom
	PatBlt (hDC, rRc.Left(), rRc.Top(), DD, rRc.Bottom()-rRc.Top()-DD, DSTINVERT);		// Left
	PatBlt (hDC, rRc.Right()-DD, rRc.Top(), DD, rRc.Bottom()-rRc.Top()-DD, DSTINVERT);	// Right

	ReleaseDC (m_hWnd, hDC);
}

///////////////////////////////////////////////////////////////////////////////
// einen Eintrag anhand einer MausKoordinate finden (kippt außerdem y-Koordinate im Punkt)
WORD CLegendeClientWindow::FindEntry (Point &pt)
{
Rectangle rc (CanvasRect());
CoOrd iScrPos = m_pLO -> m_ptOrg.Y();
	
	pt.Y() = (rc.Top()-rc.Bottom()) - pt.Y();	// Y kippen
	pt.Y() -= iScrPos;			// ScrollPos beachten
	return m_pLO -> FindEntry (short(pt.Y()));
}

// Alle LegendenEinträge(Merkmale) dieser Sicht aus der DB löschen 
bool CLegendeClientWindow::ResetLegend (void)
{
CEierUhr Wait (this);
char cbView[_MAX_PATH];
bool iRet = false;
	
	if (DEX_GetActiveSight(cbView) != NULL) {
		iRet = m_pLO -> ResetLegend (cbView);
		ResetSelection();
	}
	return iRet;
}

// Zustand der Legende an der aktuellen Sicht speichern 
bool CLegendeClientWindow::SaveLegend (void)
{
// Legende nur speichern, wenn notwendig
	if (m_pLO -> isDirty()) {
	CEierUhr Wait (this);

		return m_pLO -> SaveLegend();
	}
	return true;	// nichts zu tun
}

///////////////////////////////////////////////////////////////////////////////
// neue Ansicht wurde selektiert
bool CLegendeClientWindow::ViewSelected (LPCSTR pcView)
{
// ggf. Caption anpassen
	if (NULL != GetParentWindow())
		GetParentWindow() -> SetCaption(pcView);

// alles andere weiter unten erledigen
	return m_pLO -> ViewSelected (pcView);
}

///////////////////////////////////////////////////////////////////////////////
// Objekt zu Legende hinzufügen 
bool CLegendeClientWindow::AddObject (long lONr)
{
	return m_pLO -> AddObject (lONr);
}

///////////////////////////////////////////////////////////////////////////////
// Drag'nDrop support

// Generieren des DataTransferObjektes für eine DragDropOperation 
LPDATAOBJECT CLegendeClientWindow::TransferObjectCreate (WORD iOrder)
{
	if (iOrder == USHRT_MAX) 
		return NULL;

WDataObject DataObject;
HRESULT hr = DataObject.CreateInstance(CLSID_DataTransferObject);
	
	if (FAILED(hr)) return NULL;

// Copy from known obj into transfer obj.  Ordering is important!
char cbTmp[5*_MAX_PATH];
LEGENTRYTYPE rgLType = LEGENTRYTYPE_UNKNOWN;
VisType rgVType = VT_Default;
INT_PTR lTarget = NULL;
INT_PTR lMCode = NULL;

	if (!m_pLO -> GetEntryDesc (iOrder, cbTmp, rgLType, rgVType, lTarget, lMCode)) 
		return NULL;
	
// Generate placeable object structure
STGMEDIUM stm;

	stm.tymed = TYMED_HGLOBAL;
	stm.pUnkForRelease = NULL;
	stm.hGlobal = GlobalAlloc (GHND, sizeof(DRAGDROPLEGENTRY) + strlen (cbTmp));
	if (stm.hGlobal == NULL) 
		return NULL;

// Beschreibung des zu bewegenden LegendenEintrages generieren
LPDRAGDROPLEGENTRY pLegDesc = (LPDRAGDROPLEGENTRY)GlobalLock (stm.hGlobal);

	pLegDesc -> m_dwSize = sizeof(DRAGDROPLEGENTRY);
	pLegDesc -> m_rgLEType = rgLType;
	pLegDesc -> m_rgVType = rgVType;
	pLegDesc -> m_lTarget = lTarget;
	pLegDesc -> m_lMCode = (VT_Default == rgVType) ? lMCode : NULL;
	strcpy (pLegDesc -> m_cbLegDesc, cbTmp);		// Daten reinkopieren
	GlobalUnlock(stm.hGlobal);

FORMATETC fe;

	SETDefFormatEtc (fe, m_cf, TYMED_HGLOBAL);
	DataObject -> SetData (&fe, &stm, true);
	
// als zweites Format den blanken LegendenText mit übergeben
LPSTR pTmp = m_pLO -> GetText (iOrder);

	stm.tymed = TYMED_HGLOBAL;
	stm.pUnkForRelease = NULL;
	stm.hGlobal = GlobalAlloc (GHND, strlen(pTmp) +1);
	if (stm.hGlobal == NULL) {
		DELETE_VEC (pTmp);
		return NULL;
	}

char *pText = (char *)GlobalLock (stm.hGlobal);
	
	strcpy (pText, pTmp);		// Text reinkopieren
	DELETE_VEC (pTmp);
	GlobalUnlock(stm.hGlobal);

	SETDefFormatEtc (fe, CF_TEXT, TYMED_HGLOBAL);
	DataObject -> SetData (&fe, &stm, true);
	return DataObject.detach();    // Caller now responsible
}

// Erzeugen der Einfügemarke bei DragDrop-Operationen 
bool CLegendeClientWindow::DropSelectTargetWindow (POINTL *pptl, bool fRemove, bool fPaint)
{
Rectangle rc = CanvasRect();

// nur vorherige Einfügemarke entfernen
	if (fRemove) {
		DrawDropSelection (rc);
		m_iDropPos = -1;
		m_iDropOrder = USHRT_MAX;
		return true;
	}

// neue Einfügemarke erzeugen
Point pt (CoOrd(pptl -> x), CoOrd(pptl -> y));

	ScreenToClient (m_hWnd, (POINT *)&pt);
	pt.Y() = (rc.Top()-rc.Bottom()) - pt.Y();

WORD iOrder = FindEntry (pt);

	if (iOrder == USHRT_MAX) 
		return false;	// außerhalb des gültigen Bereiches

Range r;
CoOrd iScrPos = m_pLO -> m_ptOrg.Y();
		
	if (m_pLO -> GetEntrySize (iOrder, r)) {
	// Position der Einfügemarke bestimmen
		if (pt.Y() > (r.Max()+r.Min())/2)
			pt.Y() = r.Max() + iScrPos;
		else 
			pt.Y() = r.Min() + iScrPos;

		if (pt.Y() != m_iDropPos) {
		// vorherige Einfügemarke entfernen
			if (fPaint) DrawDropSelection (rc);
			
		// Einfügemarke zeichnen
			m_iDropOrder = iOrder;
			m_iDropPos = short(pt.Y());
			if (fPaint) DrawDropSelection (rc);
		}
	}
	return true;
}

bool CLegendeClientWindow::DrawDropSelection (Rectangle &rRc)
{
	if (m_iDropPos < 0) return false;
	
	UnrealizeObject (m_hBr);

HDC hDC = GetDC (m_hWnd);
HBRUSH hBrush = (HBRUSH)SelectObject (hDC, m_hBr);

	PatBlt (hDC, rRc.Left()+DD, m_iDropPos-DD/2, rRc.Right()-rRc.Left()-2*DD, DD, PATINVERT);

	SelectObject (hDC, hBrush);
	ReleaseDC (m_hWnd, hDC);
	return true;
}

bool CLegendeClientWindow::FQueryPasteFromData (LPDATAOBJECT pIDataObject)
{
FORMATETC fe;

	SETDefFormatEtc (fe, m_cf, TYMED_HGLOBAL);
	return (pIDataObject -> QueryGetData (&fe) == NOERROR);
}

UINT CLegendeClientWindow::UTestDroppablePoint (LPPOINTL pptl)
{
POINT pt;
RECT rcC;
UINT uRet;

	POINTFROMPOINTL (pt, *pptl);
	ScreenToClient (m_hWnd, &pt);
	GetClientRect (m_hWnd, &rcC);

// Check for at least a client area hit.
	if (!PtInRect (&rcC, pt)) return UDROP_NONE;

	uRet = UDROP_CLIENT;

	if (m_fFitFont) return uRet;	// kein Scrollen notwendig
	
// Check horizontal inset
	if (pt.x <= rcC.left + (int)m_uiScrollInset)
		uRet |= UDROP_INSETLEFT;
	else if (pt.x >= rcC.right - (int)m_uiScrollInset)
		uRet |= UDROP_INSETRIGHT;

// Check vertical inset
	if (pt.y <= rcC.top + (int)m_uiScrollInset)
		uRet |= UDROP_INSETTOP;
	else if (pt.y >= rcC.bottom - (int)m_uiScrollInset)
		uRet |= UDROP_INSETBOTTOM;

	return uRet;
}

bool CLegendeClientWindow::FPasteFromData (LPDATAOBJECT pIDataObject)
{
// wenn keine Verschiebung resultiert, dann wieder raus
	if (!FQueryDrop()) return false;

// Eintrag einfügen
FORMATETC fe;
STGMEDIUM stm;
bool fRet;

	SETDefFormatEtc (fe, m_cf, TYMED_HGLOBAL);
	fRet = SUCCEEDED(pIDataObject -> GetData (&fe, &stm));
	if (fRet && stm.hGlobal) {
	LPDRAGDROPLEGENTRY pDDLegEntry = (LPDRAGDROPLEGENTRY)GlobalLock (stm.hGlobal);
	
		if (m_iDropOrder < m_iClipOrder)
			m_iClipOrder++;
		else if (m_iDropOrder > m_iClipOrder)
			m_iDropOrder++;

		m_pLO -> FPasteEntry (pDDLegEntry, m_iDropOrder);
		GlobalUnlock (stm.hGlobal);
		ReleaseStgMedium (&stm);

		m_fNeedsCalculation = true;
		ShowSelection (m_iDropOrder);	// neue Selektion anzeigen
	}
	return fRet;
}

bool CLegendeClientWindow::FClipEntry (WORD iOrder)
{
	return m_pLO -> FClipEntry (iOrder);
}

///////////////////////////////////////////////////////////////////////////////
// Menuinitialisierung für PopupMenu
void CLegendeClientWindow::MenuInit(MenuInitEvt e)
{
	if (m_hMenu == 0) 
		return;	// kein Kontextmenu offen

	if (USHRT_MAX != GetActSelection()) {
	// KontextMenu initialisieren
	bool fShown = GetIsShown(m_iActSelection);
	bool fIdentEntry = (LEGENTRYTYPE_IDENT == GetIsA(m_iActSelection)) ? true : false;

	// Identifikator/Objekteintrag
		if (fIdentEntry) {	// IdentifikatorEintrag
			ModifyMenu (m_hMenu, 0,	// erster Eintrag
					MF_BYPOSITION|MF_ENABLED | (fShown ? MF_CHECKED : MF_UNCHECKED), 
					IDM_LEGENTRYSHOWENTRY, ResString (IDS_LEGENTRYSHOWENTRY, 64).Addr());
		} 
		else {			// ObjektEintrag o.ä.
			ModifyMenu (m_hMenu, 0,	// erster Eintrag
					MF_BYPOSITION|MF_UNCHECKED|MF_ENABLED, 
					IDM_LEGENTRYREMOVEENTRY, ResString (IDS_LEGENTRYREMOVEENTRY, 64).Addr());
		}

	// Leerzeile vorhanden/nicht vorhanden
		if (GetHasSpace (m_iActSelection)) {	// (alte) Leerzeile vorhanden
			ModifyMenu (m_hMenu, 5,	// fünfter Eintrag
					MF_BYPOSITION|MF_UNCHECKED|MF_ENABLED, IDM_REMOVESPACELINE, 
					ResString (IDS_REMOVESPACELINE, 64).Addr());
		} 
		else {
	#if _TRiAS_VER < 0x0400
			ModifyMenu (m_hMenu, 5,	// fünfter Eintrag
					MF_BYPOSITION|MF_UNCHECKED|((fNotLast || 0 != g_dwVer4) ? MF_ENABLED : MF_GRAYED), 
					IDM_ENTERSPACELINE, ResString (IDS_ENTERSPACELINE, 64).Addr());
	#else
			ModifyMenu (m_hMenu, 5,	// fünfter Eintrag
					MF_BYPOSITION|MF_UNCHECKED|MF_ENABLED, 
					IDM_ENTERSPACELINE, ResString (IDS_ENTERSPACELINE, 64).Addr());
	#endif // _TRiAS_VER < 0x0400
		}

	#if _TRiAS_VER < 0x0400
	// Versionsspezifika beachten
		if (0 != g_dwVer4) 
	#endif // _TRiAS_VER < 0x0400
		{
		bool fTextEntry = (LEGENTRYTYPE_TEXT == GetIsA(m_iActSelection)) ? true : false;
		bool fSpaceLine = (LEGENTRYTYPE_SPACELINE == GetIsA(m_iActSelection)) ? true : false;
		bool fCustText = GetCustomizedText (m_iActSelection);

			EnableMenuItem (m_hMenu, IDM_LEGENTRYRESETTEXT, MF_BYCOMMAND|MF_UNCHECKED|((fTextEntry || fSpaceLine || fCustText) ? MF_ENABLED : MF_GRAYED));
			EnableMenuItem (m_hMenu, IDM_LEGENTRYEDITTEXT, MF_BYCOMMAND|MF_UNCHECKED|(fSpaceLine ? MF_GRAYED : MF_ENABLED));
		}
	#if _TRiAS_VER < 0x0400
		else
			EnableMenuItem (m_hMenu, IDM_LEGENTRYRESETTEXT, MF_BYCOMMAND| (fCustText ? MF_ENABLED : MF_GRAYED));	
	#endif // _TRiAS_VER < 0x0400

	bool fNotFirst = !GetIsFirstEntry (m_iActSelection);
	bool fNotLast = !GetIsLastEntry (m_iActSelection);

		EnableMenuItem (m_hMenu, IDM_LEGENTRYVISPARAMS, MF_BYCOMMAND | (fIdentEntry ? MF_ENABLED : MF_GRAYED));	
		EnableMenuItem (m_hMenu, IDM_LEGENTRYMOVEUP, MF_BYCOMMAND| (fNotFirst ? MF_ENABLED : MF_GRAYED));	
		EnableMenuItem (m_hMenu, IDM_LEGENTRYMOVEDOWN, MF_BYCOMMAND| (fNotLast ? MF_ENABLED : MF_GRAYED));	
	}
	else {
	// Hauptmenu initialisieren
		_ASSERTE(NULL == m_pParent);	// nur, wenn standalone

		CheckMenuItem (m_hMenu, IDM_FITLEGENDENTRIES, GetFitFont() ? MF_CHECKED : MF_UNCHECKED); 
		CheckMenuItem (m_hMenu, IDM_SHOWALLENTRIES, GetShowAll() ? MF_CHECKED : MF_UNCHECKED);
		CheckMenuItem (m_hMenu, IDM_LEGENDE_ANAUSSCHNITTANPASSEN, GetShowAreaOnly() ? MF_CHECKED : MF_UNCHECKED);
		CheckMenuItem (m_hMenu, IDM_SIZESLIKESCALING, !GetScaleMode() ? MF_CHECKED : MF_UNCHECKED);

	// Ein Trick am Rande, der erlaubt die Legende on the fly zu speichern.
	// (mit der ControlTaste das erste SubMenu der Legende öffnen :-) )
		if (GetKeyState (VK_CONTROL) < 0) {	// ControlTaste gedrückt
			ModifyMenu (m_hMenu, 6,	// letzter Eintrag
					MF_BYPOSITION|MF_UNCHECKED, 
					IDM_LEGENDSAVE, ResString (IDS_LEGENDSAVE, 64).Addr());
		} 
		else {	// Normaler Mode
			ModifyMenu (m_hMenu, 6,	// letzter Eintrag
					MF_BYPOSITION|MF_UNCHECKED, 
					IDM_LEGENDRESET, ResString (IDS_LEGENDRESET, 64).Addr());
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
// MenuCommands kommen hier an
void CLegendeClientWindow::MenuCommand (MenuCommandEvt e)
{
	switch (e.GetItemID()) {
	case IDM_FITLEGENDENTRIES:
		FitLegendEntries();
		break;

	case IDM_SIZESLIKESCALING:
		SizesLikeScaling();
		break;

	case IDM_LEGENDSELFONT:
		break;
		
	case IDM_SHOWALLENTRIES:
		ShowAllEntries();
		break;
		
	case IDM_LEGENDRESET:				// Legende rücksetzen
		LegendReset();
		break;
		
	case IDM_LEGENDSAVE:				// Legende speichern, wenn notwendig
		SaveLegend();
		break;
	
	// PopupMenu 
	case IDM_LEGENTRYSHOWENTRY:
		HandleShowEntry();
		break;
		
	case IDM_REMOVEHEADLINE:			// Zwischenüberschrift entfernen
	case IDM_LEGENTRYREMOVEENTRY:		// nur für Objekteinträge
		HandleRemoveEntry();
		break;
		
	case IDM_LEGENTRYVISPARAMS:
		HandleVisParams();
		break;
		
	case IDM_LEGENTRYEDITTEXT:
		HandleEditText();
		break;
		
	case IDM_LEGENTRYRESETTEXT:
		HandleResetText();
		break;

	case IDM_LEGENTRYMOVEUP:		// eine Etage hoch
		HandleMoveUp();
		break;
		
	case IDM_LEGENTRYMOVEDOWN:
		HandleMoveDown();
		break;

	case IDM_ENTERSPACELINE:
		HandleInsertSpaceLine();
		break;

	case IDM_REMOVESPACELINE:
		HandleRemoveSpaceLine();
		break;

	case IDM_ENTERHEADLINE:		// Zwischenüberschrift einfügen
		HandleInsertHeadLine();
		break;

	case IDM_LEGENDE_ANAUSSCHNITTANPASSEN:
		HandleSelectAusschnitt();
		break;
	}
}

///////////////////////////////////////////////////////////////////////////////
// Menupunkte
bool CLegendeClientWindow::FitLegendEntries()
{
	m_fFitFont = !m_fFitFont;
	if (NULL != m_pHorzSB)
		m_pHorzSB -> SetThumbPos(0);
	if (NULL != m_pVertSB)
		m_pVertSB -> SetThumbPos(0);

	if (m_pLO) {
		m_pLO -> m_ptOrg.X() = 0;
		m_pLO -> m_ptOrg.Y() = 0;
	}

	if (!m_fFitFont) 
		m_fSetScrollBars = true;		// beim nächsten zeichnen Scrolls setzen
	else {
	// Scrollbalken ausblenden
		m_pHorzSB = EnableHScroll (false);
		m_pVertSB = EnableVScroll (false);
	}
	m_fNeedsCalculation = true;
	HideSelection (m_iActSelection);	// SelRect ausblenden
	RePaint();

	return true;
}

bool CLegendeClientWindow::SizesLikeScaling()
{
	m_pLO -> SetScaleMode (!m_pLO -> GetScaleMode());
	m_pLO -> SetDirty();

	m_fNeedsCalculation = true;
	HideSelection(m_iActSelection);	// SelRect ausblenden
	RePaint();
	return true;
}

bool CLegendeClientWindow::ShowAllEntries()
{
	m_pLO -> ShowAll (!m_pLO -> ShowAll());
	m_fNeedsCalculation = true;
	HideSelection (m_iActSelection);	// SelRect ausblenden
	RePaint();
	return true;
}

// Legende rücksetzen
bool CLegendeClientWindow::LegendReset()
{
CEierUhr Wait (this);
char cbView[_MAX_PATH];

	if (DEX_GetActiveSight(cbView) != NULL) {
		m_pLO -> ResetLegend (cbView);
		m_fNeedsCalculation = true;
		ResetSelection();
		RePaint();
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// PopupMenu-Befehle
bool CLegendeClientWindow::HandleShowEntry()
{
	if (m_iActSelection >= 0) {
	bool fShown = m_pLO -> isShown (m_iActSelection);
	
		m_pLO -> isShown (m_iActSelection, !fShown);
		m_fNeedsCalculation = true;
		HideSelection (m_iActSelection);
		ResetSelection();	// Paint überschreibt SelRect
		RePaint();
	}
	return true;
}

bool CLegendeClientWindow::HandleRemoveEntry()
{
	if (m_iActSelection != USHRT_MAX) {
		m_pLO -> RemoveEntry (m_iActSelection);
		m_fNeedsCalculation = true;
		HideSelection (m_iActSelection); // Selektion freigeben
		ResetSelection();		
		RePaint();			 // neu zeichnen
	}		
	return true;
}

bool CLegendeClientWindow::HandleRemoveSpaceLine()
{
	if (LEGENTRYTYPE_SPACELINE == m_pLO -> isA (m_iActSelection)) 
		HandleRemoveEntry();
	else if (m_pLO -> RemoveSpace (m_iActSelection)) {
		m_fNeedsCalculation = true;
		RePaint();
	}
	return true;
}

bool CLegendeClientWindow::HandleVisParams (void)
{
	switch (m_pLO -> isA (m_iActSelection)) {
	case LEGENTRYTYPE_IDENT:
		{
		long lIdent = m_pLO -> GetIdent (m_iActSelection);
		VisType iVTyp = m_pLO -> GetVType (m_iActSelection);
				
			if (DefineNewIdentVisInfo (lIdent, iVTyp, GetKeyState (VK_CONTROL) < 0)) {
				m_fNeedsCalculation = true;
				DEX_RePaintWait();	// Hauptfenster neu zeichnen
			}
		} 
		break;
				
	case LEGENTRYTYPE_OBJECT:
		break;

	case LEGENTRYTYPE_SPACELINE:
	case LEGENTRYTYPE_TEXT:
	case LEGENTRYTYPE_UNKNOWN:
	default:
		break;
	}			
	return true;
}

bool CLegendeClientWindow::HandleEditText (void)
{
	switch (m_pLO -> isA (m_iActSelection)) {
	case LEGENTRYTYPE_OBJECT:
	case LEGENTRYTYPE_IDENT:
	case LEGENTRYTYPE_TEXT:
		{
		char *pText = m_pLO -> GetText (m_iActSelection);
		CEditLegTextDlg *pDlg = CEditLegTextDlg::CreateInstance (this, pText);
		
			if (pDlg != NULL) {
				pDlg -> Show();
				if (pDlg -> Result()) {
					m_pLO -> SetText (m_iActSelection, pDlg -> GetNewText());
					m_fNeedsCalculation = true;
					RePaint();
				}
			}
			DELETE_OBJ (pText);
			DELETE_OBJ (pDlg);
		}
		break;
				
	case LEGENTRYTYPE_UNKNOWN:
	default:
		break;
	}			
	return true;
}

bool CLegendeClientWindow::HandleResetText()
{
	if (m_pLO -> ResetText (m_iActSelection)) {
		m_fNeedsCalculation = true;
		RePaint();
	}
	return true;
}

// Eintrag nach oben verschieben
bool CLegendeClientWindow::HandleMoveUp()
{
	if (m_pLO -> MoveUp (m_iActSelection, m_fShowAllEntries)) {
		m_fNeedsCalculation = true;
		RePaint();
	}
	return true;
}

// Eintrag nach unten verschieben
bool CLegendeClientWindow::HandleMoveDown()
{
	if (m_pLO -> MoveDown (m_iActSelection, m_fShowAllEntries)) {
		m_fNeedsCalculation = true;
		RePaint();
	}
	return true;
}

bool CLegendeClientWindow::HandleInsertSpaceLine()
{
#if _TRiAS_VER < 0x0400
bool fOk = false;

	if (0 != g_dwVer4) 
		fOk = m_pLO -> InsertHeadLine (m_iActSelection, g_cbNil);
	else
		fOk = m_pLO -> EnterSpace (m_iActSelection);

// alles ok, neu berechnen
	if (fOk) {
		m_fNeedsCalculation = true;
		RePaint();
	}
#else
	if (m_pLO -> InsertHeadLine (m_iActSelection, g_cbNil)) {
		m_fNeedsCalculation = true;
		RePaint();
	}
#endif // _TRiAS_VER < 0x0400
	return true;
}

bool CLegendeClientWindow::HandleInsertHeadLine (void)
{
CEditLegTextDlg Dlg (this, IDS_EDITHEADLINE_CAP, IDS_EDITLEGENTRYHEADLINE);

	if (!Dlg.FInit(g_cbNil))
		return false;

	Dlg.Show();
	if (Dlg.Result()) {
		m_pLO -> InsertHeadLine (m_iActSelection, Dlg.GetNewText(), true);
		m_fNeedsCalculation = true;
		RePaint();
		return true;
	}
	return false;
}

bool CLegendeClientWindow::HandleSelectAusschnitt()
{
	m_pLO -> SetAreaOnly (!m_pLO -> ShowAreaOnly());
	m_pLO -> SetDirty();

	m_fNeedsCalculation = true;
	RePaint();
	return true;
}
