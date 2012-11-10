// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 14.03.2001 19:55:16 
//
// @doc
// @module OverView.cxx | Definition of the <c COverView> and <c COverViewClient> classes

#include "triaspre.hxx"
#include "triasres.h"

#include <Com/ComBool.h>

#include <WindowPosEvent.h>
#include <SidManageTabs.h>
#include <triastlb.h>
#include <dirisole.h>

#include "overview.h"

#include "Strings.h"
#include "extmain3.hxx"
#include "shiftovw.hxx"
#include "overview.hxx"
#include "OverviewCallback.h"

#if defined(_DEBUG) && !defined(WIN16)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// #define ENUMENHMETAFILE
// #define CREATEPALETTE
#if defined(_DEBUG)
#define COPYTOCLIPBOARD
#endif //_DEBUG

extern HINSTANCE hInstance;
extern bool OverViewCFlag;
extern ExtDirisWindow *CurrActDirisW;	// Hauptfenster

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(ServiceProvider);
DefineSmartInterface(ManageTabWindows);

///////////////////////////////////////////////////////////////////////////////
// Anlegen und Anzeigen des Fensters 
/*static*/
HRESULT COverView::RegisterTabWindow()
{
	COM_TRY {
	WServiceProvider SP;
	WManageTabWindows Tabs;

		_ASSERTE(NULL != CurrActDirisW);
		if (SUCCEEDED(CurrActDirisW -> EL().QueryInterface(__uuidof(IServiceProvider), SP.ppv())) &&
			SUCCEEDED(SP -> QueryService(SID_ManageOverviewTabs, __uuidof(IManageTabWindows), Tabs.ppv()))) 
		{
		CComObject<COverviewCallback> *pOverviewCB = NULL;

			THROW_FAILED_HRESULT(CComObject<COverviewCallback>::CreateInstance(&pOverviewCB));

		WUnknown Unk (pOverviewCB -> GetUnknown());		// pending AddRef
		CComBSTR bstrOverview;
		
			bstrOverview.LoadString(IDS_OVERVIEWCAP);
			pOverviewCB -> SetCmdTarget (CurrActDirisW);
			THROW_FAILED_HRESULT(Tabs -> AddTabWindowDelayed(bstrOverview, pOverviewCB));
		}
	} COM_CATCH;
	return S_OK;
}

COverViewClientWindow *COverView::CreateOverView (
	pWindow pW, ObjContainer &ocDB, bool fInitNew, 
	Point ptAspect, double dRatio, DatenBasisObjekt &rDBO)
{
COverViewClientWindow *pClient = NULL;

	COM_TRY {
	// OverViewFenster erzeugen, dazu entscheiden, wo es angezeigt werden soll
	WServiceProvider SP;
	WManageTabWindows Tabs;

		_ASSERTE(NULL != CurrActDirisW);
		if (SUCCEEDED(CurrActDirisW -> EL().QueryInterface(__uuidof(IServiceProvider), SP.ppv())) &&
			SUCCEEDED(SP -> QueryService(SID_ManageOverviewTabs, __uuidof(IManageTabWindows), Tabs.ppv()))) 
		{
		// Anzeige erfolgt im DockingTab
		INT_PTR hHandle = NULL;
		CComBSTR bstrOverview;
		
			bstrOverview.LoadString(IDS_OVERVIEWCAP);
			pClient = COverViewClientWindow::CreateInstance(ocDB, fInitNew, ptAspect, dRatio, rDBO);

			THROW_FAILED_HRESULT(Tabs -> AddTabWindow(reinterpret_cast<INT_PTR>(pClient ->Handle()), bstrOverview, pClient -> GetIcon(), &hHandle));
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
		COverView *pOV = new COverView (pW);

			pClient = new COverViewClientWindow(ptAspect, dRatio, rDBO, pOV);
			if (NULL == pOV || !pOV -> FInit (ocDB, fInitNew, pClient)) {
				DELETE_OBJ (pOV);
				return NULL;
			}
		// das Ganze anzeigen
			pClient -> Show(ShowState(Normal|NoActivate));
			pOV -> Show (ShowState(Normal|NoActivate));
		}
		pClient -> FInitCursor();

	} COM_CATCH_RETURN(NULL);
	return pClient;
}
		
bool COverViewClientWindow::ReShow()
{
	COM_TRY {
	// Legendenfenster erzeugen
	CEierUhr Wait (this);

	// Gesamtübersicht muß im DockingFenster angezeigt sein
	WServiceProvider SP;
	WManageTabWindows Tabs;

		_ASSERTE(NULL != CurrActDirisW);
		THROW_FAILED_HRESULT(CurrActDirisW -> EL().QueryInterface(__uuidof(IServiceProvider), SP.ppv()));
		THROW_FAILED_HRESULT(SP -> QueryService(SID_ManageOverviewTabs, __uuidof(IManageTabWindows), Tabs.ppv()));

	INT_PTR hHandle = NULL;
	CComBSTR bstrOverView;
	
		bstrOverView.LoadString(IDS_OVERVIEWCAP);
		THROW_FAILED_HRESULT(Tabs -> FindTabWindow(bstrOverView, &hHandle));
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

/*static*/
void COverView::DeleteInstance(COverViewClientWindow *& pOverView)
{
	COM_TRY {
	// entscheiden, wo die Gesamtübersicht angezeigt wurde
	WServiceProvider SP;
	WManageTabWindows Tabs;

		_ASSERTE(NULL != CurrActDirisW);
		if (SUCCEEDED(CurrActDirisW -> EL().QueryInterface(__uuidof(IServiceProvider), SP.ppv())) &&
			SUCCEEDED(SP -> QueryService(SID_ManageOverviewTabs, __uuidof(IManageTabWindows), Tabs.ppv()))) 
		{
		// Anzeige erfolgte im DockingTab
			_ASSERTE(NULL == pOverView -> GetParentWindow());
			THROW_FAILED_HRESULT(Tabs -> DeleteTabWindow(reinterpret_cast<INT_PTR>(pOverView -> Handle())));
			DELETE_OBJ(pOverView);

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
			_ASSERTE(NULL != pOverView -> GetParentWindow());
			pOverView -> GetParentWindow() -> Hide();
			delete pOverView -> GetParentWindow();
			DELETE_OBJ(pOverView);
		}
	} COM_CATCH_NORETURN;
}

	
///////////////////////////////////////////////////////////////////////////////
// Konstruktor/Destruktor/Initialisierung 
COverView::COverView(pWindow pParent) :
	DialogWindow (pParent, OVERVIEWDIALOG, false)	// ModeLess
{
	m_dimWnd = Dimension (0, 0);
	m_fToDelete = false;

// Menupunkte eines Fensters mit SysMenu entfernen
HMENU hSysMenu = ::GetSystemMenu (Handle(API_WINDOW_HWND), false);

	::RemoveMenu (hSysMenu, SC_MINIMIZE, MF_BYCOMMAND);
	::RemoveMenu (hSysMenu, SC_RESTORE, MF_BYCOMMAND);
	::RemoveMenu (hSysMenu, SC_MAXIMIZE, MF_BYCOMMAND);
}

COverView::~COverView()
{
}

BOOL COverView::FInit (ObjContainer &ocGeoDB, bool fInitNew, COverViewClientWindow *pClient)
{
CEierUhr Wait (GetParent());	// SandUhr anzeigen

	_ASSERTE(NULL != pClient);
	m_pOverView = pClient;
	if (!m_pOverView -> FInit(ocGeoDB, fInitNew))
		return FALSE;

// Fenster positionieren und Größe einstellen
Rectangle rcC (GetParent() -> CanvasRect());

	m_dimWnd.Width() = (rcC.Right()-rcC.Left()) / 4;
	m_dimWnd.Height() = m_dimWnd.Width() * m_pOverView -> GetAspect();
	ChangeSize (m_dimWnd);
	
// links oben positionieren
Rectangle rcW (WindowRect());

	ChangePosition (Point (0, (rcC.Top()-rcC.Bottom()) - (rcW.Top() - rcW.Bottom())));	
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// Eigener Eventhandler und eigener Dispatcher 
long COverView::Dispatch (Event e) 
{
// wenn WM_WINDOWPOSCHANGING --> umlenken
	switch (e.Msg()) {
	case WM_WINDOWPOSCHANGING:
		WindowPosChanging ((WindowPosEvt &)e);
		break;		// auf jeden Fall weitersenden
	}

// ansonsten normaler Dispatcher
	return DialogWindow::Dispatch (e);
}

///////////////////////////////////////////////////////////////////////////////
// EventHandler für MinMaxEvent etc. 
void COverView::WindowPosChanging (WindowPosEvt e)
{
	if (!e.SizeIsChanging()) 
		return;
	
Dimension dimNew;

	e.GetWindowSize (dimNew);
	if (dimNew.Width() != m_dimWnd.Width()) {
		dimNew.Height() = int(dimNew.Width() * m_pOverView -> GetAspect());
		e.SetWindowSize (dimNew);
		return;
	}
	
	if (dimNew.Height() != m_dimWnd.Height()) {
		dimNew.Width() = int(dimNew.Height() / m_pOverView -> GetAspect());
		e.SetWindowSize (dimNew);
		return;
	}
}

void COverView::ReSize (ReSizeEvt evt)
{
	_ASSERTE(NULL != m_pOverView);
	m_pOverView -> ChangePosition(Point());
	m_pOverView -> ChangeSize(evt.GetNewSize());
	m_pOverView -> RePaint();

Rectangle rc (WindowRect());

	m_dimWnd = Dimension (rc.Right()-rc.Left(), rc.Top()-rc.Bottom());
}

///////////////////////////////////////////////////////////////////////////////
// ClientFenster
/*static*/
COverViewClientWindow *COverViewClientWindow::CreateInstance(
	ObjContainer &ocDB, bool fInitNew, Point ptAspect, double dRatio, DatenBasisObjekt &rDBO)
{
COverViewClientWindow *pClient = NULL;

	ATLTRY(pClient = new COverViewClientWindow(ptAspect, dRatio, rDBO));
	if (NULL == pClient || !pClient -> FInit(ocDB, fInitNew)) {
		DELETE_OBJ(pClient);
		return NULL;
	}
	return pClient;
}

COverViewClientWindow::COverViewClientWindow (Point ptAspect, double dRatio, DatenBasisObjekt &rDBO, COverView *pParent) :
	ChildAppWindow((NULL != pParent) ? pParent : (pWindow)CurrActDirisW, ID_OVERVIEW_CLIENT, (LPSTR)g_cbOverViewClass, 0),
	m_ptAspect(ptAspect), 
	m_dRatio(dRatio), 
	m_rDBO(rDBO),
	m_pParent(pParent)
{
// alles initialisieren
	m_hMF = 0;
	m_hPal = NULL;

	memset (&m_ocDB, '\0', sizeof(RECTL));
	m_dX = 0;
	m_dY = 0;
	m_dX0 = 0;
	m_dY0 = 0;

	m_dDBx = 0;
	m_dDBy = 0;

	m_dAspect = 1.0;
	m_ixExt = 0;
	m_iyExt = 0;

	m_fBrushChanged = false;
	m_pBr = NULL;

	m_prcActVP = NULL;
	m_prcSel = NULL;
	
	m_fLeftBttnSem = false;
	m_fPointerChanged = false;

	m_pOldPointer = NULL;
	m_pLupe = NULL;
	m_pMove = NULL;
	m_pTabIcon = NULL;

	m_fIsDirty = false;

	m_hSubMenu = NULL;
}

COverViewClientWindow::~COverViewClientWindow()
{
	if (m_hMF) {
		if (m_fIsDirty)
			SaveEnhMetaFile (g_cbDefaultPict);			// erstmal speichern
		DeleteEnhMetaFile (m_hMF);	// jetzt freigeben
		m_hMF = 0;
	}
	if (NULL != m_hPal) {
		DeleteObject (m_hPal);
		m_hPal = NULL;
	}

	if (m_fBrushChanged) {
		m_pBr = ChangeBackground (m_pBr);
		DELETE_OBJ (m_pBr);
	}
	if (m_fPointerChanged)
		ChangePointer (m_pOldPointer);

	DELETE_OBJ (m_pMove);
	DELETE_OBJ (m_pLupe);
		
	DELETE_OBJ (m_prcActVP);
	DELETE_OBJ (m_prcSel);

	DELETE_OBJ(m_pTabIcon);
}


BOOL COverViewClientWindow::FInit(ObjContainer &ocGeoDB, bool fInitNew)
{
// grauen Hintergrund einstellen
	m_pBr = new Brush(Color((ColorVal)192, (ColorVal)192, (ColorVal)192));
	if (m_pBr) {
		m_pBr = ChangeBackground (m_pBr);
		m_fBrushChanged = TRUE;
	}
	
// Pointer anlegen
	ATLTRY(m_pLupe = new Pointer (ResID(LUPECURSOR)));
	ATLTRY(m_pMove = new Pointer (ResID(MOVECURSOR)));

char cbBuffer[MAXVIEWNAMESIZE];

	cbBuffer[0];
	m_dX = m_dY = m_dX0 = m_dY0 = 0;

	if (!fInitNew) {
	// versuchen neu zu laden
	LPCSTR pcView = NULL;

		if (SUCCEEDED(LoadEnhMetaFile(g_cbDefaultPict, cbBuffer, sizeof(cbBuffer)))) 
			pcView = ('\0' != cbBuffer[0]) ? cbBuffer : NULL;

	// ggf. SichtContainer der gespeicherten Ansicht wiedereinlesen
	ObjContainer OC;

		if (EC_OKAY == m_rDBO.GetSichtCont (&OC, pcView) && OC.isValid())
			ocGeoDB = OC;
		m_strViewName = cbBuffer;
	} 
	else {
	ObjContainer OC;

		if (m_rDBO.GetActiveSightName(cbBuffer, sizeof(cbBuffer)) &&
			EC_OKAY == m_rDBO.GetSichtCont(&OC, cbBuffer))
		{
			ocGeoDB = OC;
			m_strViewName = cbBuffer;
		}

	// DatenbankContainer speichern, Aspekt berechnen
		m_ocDB.left = ocGeoDB.XMin();
		m_ocDB.right = ocGeoDB.XMax();
		m_ocDB.bottom = ocGeoDB.YMin();
		m_ocDB.top = ocGeoDB.YMax();
	}
			
long dX = (m_ocDB.right - m_ocDB.left) * m_dRatio;
long dY = m_ocDB.top - m_ocDB.bottom;

	m_dAspect = (double(dY) / double(dX)) * (double(m_ptAspect.Y()) / double(m_ptAspect.X()));
//	m_dAspect /= m_dRatio;

	// ringsherum je 5% zugeben
	dX /= 20;
	dY /= 20;
	m_ocDB.left -= dX;
	m_ocDB.right += dX;
	m_ocDB.bottom -= dY;
	m_ocDB.top += dY;
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// sonstige Member
CComVariant COverViewClientWindow::GetIcon()
{
CComVariant vIcon;

	if (NULL == m_pTabIcon) {
		ATLTRY(m_pTabIcon = new Icon(ResID(IDI_OVERVIEW)));
		if (NULL == m_pTabIcon) return vtMissing;
	}

// das IconHandle der Einfachheit halber direkt liefern
	V_VT(&vIcon) = VT_I4;
	V_I4(&vIcon) = reinterpret_cast<INT_PTR>(m_pTabIcon -> Handle());
	return vIcon;
}

bool COverViewClientWindow::SaveOverview (LPCSTR pcName)
{
	if (m_hMF) {
		if (m_fIsDirty)
			SaveEnhMetaFile (NULL != pcName ? pcName : g_cbDefaultPict);			// erstmal speichern
		DeleteEnhMetaFile (m_hMF);	// jetzt freigeben
		m_hMF = 0;
		return true;
	}
	return false;
}

void COverViewClientWindow::FInitCursor (void)		// nur Cursor wechseln
{
	if (m_pLupe) {
		m_fPointerChanged = TRUE;
		m_pOldPointer = ChangePointer (m_pLupe);
	}
}

///////////////////////////////////////////////////////////////////////////////
// MetaFile für aktuelle Ansicht besorgen
bool COverViewClientWindow::RetrieveActViewMetaFile (Rectangle *prcC)
{
Rectangle rcC ((NULL != prcC) ? *prcC : CanvasRect());

// neue FensterAbmessungen merken
	CalculateScaleKoeffs (rcC);

	if (NULL != m_hMF) {
		if (m_fIsDirty)
			SaveEnhMetaFile (g_cbDefaultPict);			// erstmal speichern
		DeleteEnhMetaFile (m_hMF);						// jetzt freigeben
		m_hMF = NULL;
	}

	m_hMF = RetrieveMetaFile (Handle(), rcC, m_ocDB, MM_HIMETRIC); //MM_ISOTROPIC);
	if (NULL == m_hMF) return false;

	m_fIsDirty = true;		// neues MetaFile

ENHMETAHEADER EMH;

	EMH.iType = EMR_HEADER;
	EMH.nSize = sizeof(ENHMETAHEADER);
	GetEnhMetaFileHeader (m_hMF, sizeof(ENHMETAHEADER), &EMH);

	m_ixExt = EMH.szlMillimeters.cx;
	m_iyExt = EMH.szlMillimeters.cy;

#if defined(CREATEPALETTE)
UINT uiPalEntries = GetEnhMetaFilePaletteEntries (m_hMF, 0, NULL);

	if (uiPalEntries) {
	LPLOGPALETTE pPal = NULL;
	
		ATLTRY(pPal = (LPLOGPALETTE) new char[sizeof(LOGPALETTE) + (sizeof (PALETTEENTRY) * uiPalEntries)]);
		if (NULL == pPal) return FALSE;
		pPal->palVersion = 0x300;
		pPal->palNumEntries = uiPalEntries;
		GetEnhMetaFilePaletteEntries (m_hMF, uiPalEntries, pPal->palPalEntry);
		m_hPal = CreatePalette (pPal);

		delete pPal;
		if (NULL == m_hPal) return FALSE;

	} else
		m_hPal = NULL;		// keine Palette
#endif // CREATEPALETTE

#if defined(COPYTOCLIPBOARD)
	OpenClipboard(Handle(API_WINDOW_HWND));
	EmptyClipboard();
	SetClipboardData (CF_ENHMETAFILE, (HANDLE)CopyEnhMetaFile (m_hMF, NULL));
	CloseClipboard();
#endif // COPYTOCLIPBOARD

char cbBuffer[MAXVIEWNAMESIZE];

	if (m_rDBO.GetActiveSightName(cbBuffer, sizeof(cbBuffer)))
		m_strViewName = cbBuffer;		// aktuellen Ansichtsnamen merken

	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Aktuellen Bildausschnitt anzeigen 
void COverViewClientWindow::EnsureScaleKoeffs()
{
	if (0 == m_dX || 0 == m_dY) {
	// Metafilebereich auf Canvas initialisieren
	Rectangle rc (CanvasRect());
		
		m_dX = rc.Right() - rc.Left();
		m_dY = rc.Top() - rc.Bottom();
		m_dX0 = m_dY0 = 0;
	}
}

double COverViewClientWindow::CalculateScaleKoeffs (Rectangle &rrc)
{
CoOrd lDeltaX = m_ocDB.right - m_ocDB.left;
CoOrd lDeltaY = m_ocDB.top - m_ocDB.bottom;

	if (NULL != GetParentWindow())
		lDeltaX *= m_dRatio;		// nicht gedockte Version

double dScaleX = double(lDeltaX)/double(rrc.Width());
double dScaleY = double(lDeltaY)/double(rrc.Height());
double dScale = 0.0;

	if(dScaleX > dScaleY) {
		m_dX = rrc.Width();
		m_dX0 = 0;
		m_dY = MulDiv(rrc.Width(), lDeltaY, lDeltaX);
		m_dY0 = (rrc.Height() - m_dY)/2;

		_ASSERTE(m_dY <= rrc.Height());
		_ASSERTE(m_dY0 >= 0);
	} 
	else {
		m_dY = rrc.Height();
		m_dY0 = 0;
		m_dX = MulDiv(rrc.Height(), lDeltaX, lDeltaY);
		m_dX0 = (rrc.Width() - m_dX)/2;

		_ASSERTE(m_dX <= rrc.Width());
		_ASSERTE(m_dX0 >= 0);
	}
	rrc = Rectangle(m_dY0+m_dY, m_dX0, m_dY0, m_dX0+m_dX);		// tlbr
	return dScale;
}

void COverViewClientWindow::SetActVP (Rectangle rcC)
{
ObjContainer OC (rcC);
ObjContainer ocAct (GetActDBRect());

	if (OC ^ ocAct && (OC.Breite() < ocAct.Breite() || OC.Hoehe() < ocAct.Hoehe())) 
		SetActVP(OC);
	else
		ResetActVP();
}

void COverViewClientWindow::SetActVP (ObjContainer &ocNewVP)
{
// Selektierten Bereich markieren
HWND hWnd = Handle (API_WINDOW_HWND);
HDC hDC = ::GetDC (hWnd);
int iOldRop = SetROP2 (hDC, R2_XORPEN);
HPEN hP = CreatePen (PS_SOLID, 0, RGB (0, 0, 0));

	hP = (HPEN)SelectObject (hDC, hP);
	if (m_prcActVP) {
	// altes Rechteck löschen
		DrawRectangle (hDC, m_prcActVP -> left, m_prcActVP -> top, m_prcActVP -> right, m_prcActVP -> bottom);
	} else 
		m_prcActVP = new RECT;

	if (m_prcActVP) {
		EnsureScaleKoeffs();

	// neues Rechteck zeichnen
	CoOrd lXMin = xDBtoCV(ocNewVP.XMin());
	CoOrd lXMax = xDBtoCV(ocNewVP.XMax());
	CoOrd lYMin = yDBtoCV(ocNewVP.YMin());
	CoOrd lYMax = yDBtoCV(ocNewVP.YMax());

		SetRect (m_prcActVP, lXMin, lYMin, lXMax, lYMax);
		DrawRectangle (hDC, m_prcActVP -> left, m_prcActVP -> top, m_prcActVP -> right, m_prcActVP -> bottom);
				
	// neue DBAusschnitts-Ausdehnungen merken
		m_dDBx = ocNewVP.XMax() - ocNewVP.XMin();
		m_dDBy = ocNewVP.YMax() - ocNewVP.YMin();
	}

	DeleteObject (SelectObject (hDC, hP));
	SetROP2 (hDC, iOldRop);
	ReleaseDC (hWnd, hDC);
}

void COverViewClientWindow::ResetActVP (BOOL fFreeSel)
{
	if (m_prcActVP) {
	// altes Rechteck löschen
	HWND hWnd = Handle (API_WINDOW_HWND);
	HDC hDC = ::GetDC (hWnd);
	int iOldRop = SetROP2 (hDC, R2_XORPEN);
	HPEN hP = CreatePen (PS_SOLID, 0, RGB (0, 0, 0));
	
		hP = (HPEN)SelectObject (hDC, hP);
		DrawRectangle (hDC, m_prcActVP -> left, m_prcActVP -> top, m_prcActVP -> right, m_prcActVP -> bottom);

		if (fFreeSel) {
			delete m_prcActVP;
			m_prcActVP = NULL;
		}
		DeleteObject (SelectObject (hDC, hP));
		SetROP2 (hDC, iOldRop);
		ReleaseDC (hWnd, hDC);
	}
}

#if defined(ENUMENHMETAFILE)
int CALLBACK DrawEnhMetaRecord (HDC hDC, HANDLETABLE *pHT, ENHMETARECORD *pMR, int cObj, LPARAM eData)
{
	PlayEnhMetaFileRecord (hDC, pHT, pMR, cObj);

/*	if (pMR -> iType == EMR_SETWINDOWEXTEX) {
	//
	// Die Funktion SetViewportExtEx soll erst nach SetWindowExtEx gerufen 
	// werden, um eine bestmögliche Platzaufteilung im Fenster zu 
	// ermöglichen. SetWindowExt wird aber erst im Metafile selbst gerufen. 
	// Folglich dieser hack gleich an der Stelle.
	//
	Rectangle *prcC = (Rectangle *)eData;

		SetViewportOrgEx (hDC, (prcC -> Right() - prcC -> Left())/2, (prcC -> Top() - prcC -> Bottom())/2, NULL);
		SetViewportExtEx (hDC, prcC -> Right() - prcC -> Left(), 
							   prcC -> Top() - prcC -> Bottom(),
						  NULL);
	} 
*/	
	App::Exec (ExecWhileEvent);			// be a good windows app
	return TRUE;	// immer weiter machen
}
#endif // ENUMENHMETAFILE

///////////////////////////////////////////////////////////////////////////////
// EventHandler 
void COverViewClientWindow::Expose (ExposeEvt e)	// neu zeichnen
{
CEierUhr Wait (GetParent());
HWND hWnd = Handle (API_WINDOW_HWND);
//HDC hDC = ::GetDC (hWnd);
HDC hDC = (HDC)Handle(API_WINDOW_HDC);

//	SendMessage (hWnd, WM_ERASEBKGND, (WPARAM)hDC, 0L);	// Hintergrund löschen
	
	SaveDC (hDC);
	SetMapMode (hDC, MM_TEXT);

HPALETTE hOldPal = NULL;

	if (NULL != m_hPal) {
		hOldPal = SelectPalette (hDC, m_hPal, FALSE);
		RealizePalette(hDC);
	}

Rectangle rcC, rcOrg;

	GetClientRect (hWnd, (RECT *)&rcC);
	rcOrg = rcC;

// ringsherum je 5% zugeben
//	InflateRect ((RECT *)&rcC, -(rcC.Right() - rcC.Left())/20, -(rcC.Bottom() - rcC.Top())/20);

// evtl. Koordinatensystem kippen
	SetMapMode (hDC, MM_ISOTROPIC);
	SetWindowExtEx (hDC, rcC.Right()-rcC.Left(), rcC.Bottom()-rcC.Top(), NULL);

#if defined(_USE_SPECIAL_METAFILE_HANDLING_WIN9X)
	if (IsWin40() && !IsWinNT()) {
	// Win95 stellt aus unbekannten Gründen das Metafile auf den Kopf
	long dX = (rcC.Right() - rcC.Left()) - (rcOrg.Right() - rcOrg.Left());
	long dY = (rcC.Bottom() - rcC.Top()) - (rcOrg.Bottom() - rcOrg.Top());

		SetViewportExtEx (hDC, rcC.Right()-rcC.Left(), -(rcC.Bottom()-rcC.Top()), NULL);
		SetViewportOrgEx (hDC, 0, (rcC.Bottom()-rcC.Top())-dY, NULL);
	} else 
#endif // defined(_USE_SPECIAL_METAFILE_HANDLING_WIN9X)
	{
		SetViewportExtEx (hDC, rcC.Right()-rcC.Left(), rcC.Bottom()-rcC.Top(), NULL);
		SetViewportOrgEx (hDC, 0, 0, NULL);
	}

	rcOrg = CanvasRect();
	CalculateScaleKoeffs(rcOrg);
	if (NULL != m_hMF || RetrieveActViewMetaFile()) {
	RECT rcMF;

		_ASSERTE(NULL != m_hMF);
		SetRect (&rcMF, xDBtoCV(m_ocDB.left), yDBtoCV(m_ocDB.top), xDBtoCV(m_ocDB.right), yDBtoCV(m_ocDB.bottom));

#if defined(ENUMENHMETAFILE)
		EnumEnhMetaFile (hDC, m_hMF, (ENHMFENUMPROC)DrawEnhMetaRecord, NULL, &rcMF);
#else
		PlayEnhMetaFile (hDC, m_hMF, &rcMF);
#endif // ENUMENHMETAFILE
	}

	if (NULL != m_hPal) 
		SelectPalette (hDC, hOldPal, FALSE);

	if (m_prcActVP) {	// aktuellen Ausschnitt Kennzeichnen (DeviceCoords)
	int iOldRop = SetROP2 (hDC, R2_XORPEN);
	
		DrawRectangle (hDC, m_prcActVP -> left, m_prcActVP -> top, m_prcActVP -> right, m_prcActVP -> bottom);
		SetROP2 (hDC, iOldRop);
	}
	RestoreDC (hDC, -1);
//	ReleaseDC (hWnd, hDC);
}

BOOL HitTest (RECT *prc, Point &pt)
{
	if (pt.X() < prc -> left || pt.X() >= prc -> right) 
		return FALSE;
	if (pt.Y() < prc -> bottom || pt.Y() >= prc -> top) 
		return FALSE;
	return TRUE;
}

void COverViewClientWindow::MouseButtonDn (MouseEvt e)
{
	if (!e.isLeftButton() || m_fLeftBttnSem) 
		return;		// nur linke Taste
	m_fLeftBttnSem = TRUE;
#if !defined(_TRIAS_OLDIMPLEMENTATION2)
	MouseTrap (CVOn);
#else
	MouseTrap (On);
#endif // !defined(_TRIAS_OLDIMPLEMENTATION2)
	
// in Abhängigkeit, ob Selektion getroffen wurde, verschiedene Wege gehen
Rectangle rcC (CanvasRect());
Point ptM (e.Where().X(), rcC.Height() - e.Where().Y());

	DELETE_OBJ (m_prcSel);	 	// für alle Fälle
	if (m_prcActVP && HitTest (m_prcActVP, ptM)) {
	// aktuelle Selektion verschieben
		m_prcSel = new SelectionRectangle (ptM, *m_prcActVP);
	} 
	else {
	// neuen Bereich aufziehen
		m_prcSel = new DragRectangle (ptM);
	}
	ResetActVP ();				// evtl. alte Selektion löschen
	if (m_prcSel) 
		Draw (m_prcSel);		// erstmalig zeichnen
}

void COverViewClientWindow::MouseButtonUp (MouseEvt e)
{
	if (e.isRightButton() && !m_fLeftBttnSem) {
		TrackOverviewMenu (e.Where());
		return;
	}

	if (!e.isLeftButton() || !m_fLeftBttnSem || m_prcSel == NULL) 
		return;		// nur linke Taste

	if (m_prcSel) 
		Draw (m_prcSel);		// letztmalig zeichnen
	
// neuen DBAusschnitt einstellen
Rectangle rcR (m_prcSel -> newRect());
ObjContainer OC;

	EnsureScaleKoeffs();
	if (m_prcSel -> isA() == SELRECT_NEWRECT) {
		OC.SetXMin(xCVtoDB(rcR.Left()));
		OC.SetXMax(xCVtoDB(rcR.Right()));
		OC.SetYMin(yCVtoDB(rcR.Top()));
		OC.SetYMax(yCVtoDB(rcR.Bottom()));
	} 
	else {
		OC.SetXMin(xCVtoDB(rcR.Left()));
		OC.SetXMax(OC.XMin() + m_dDBx);
		OC.SetYMin(yCVtoDB(rcR.Top()));
		OC.SetYMax(OC.YMin() + m_dDBy);
	}
	DELETE_OBJ (m_prcSel);	// Selektionsrechteck freigeben

long lCont[4];
KoOrd dX, dY;

	if (!m_rDBO.ScaleCTF (OC.XMin(), OC.YMin(), &dX, &dY))
		return;
	lCont[0] = dX;
	lCont[2] = dY;

	if (!m_rDBO.ScaleCTF (OC.XMax(), OC.YMax(), &dX, &dY))
		return;
	lCont[1] = dX;
	lCont[3] = dY;

	DEX_SetActiveSightContainer (lCont);
	DEX_RePaint();

#if !defined(_TRIAS_OLDIMPLEMENTATION2)
	MouseTrap (CVOff);
#else
	MouseTrap (Off);
#endif // !defined(_TRIAS_OLDIMPLEMENTATION2)
	m_fLeftBttnSem = FALSE;
}

void COverViewClientWindow::MouseDrag (MouseEvt e)
{
	if (!m_fLeftBttnSem || m_prcSel == NULL) 
		return;	// nur wenn linke Taste gedrückt ist

// DragRechteck neu dimensionieren und neu zeichen
Rectangle rcC (CanvasRect());
Point ptM (e.Where().X(), rcC.Height() - e.Where().Y());

	Draw (m_prcSel);
	m_prcSel -> Process (ptM);
	Draw (m_prcSel);
}

void COverViewClientWindow::MouseMove (MouseEvt e)
{
// nur Pointer umschalten
Rectangle rcC (CanvasRect());
Point ptM (e.Where().X(), rcC.Height() - e.Where().Y());

	if (m_prcActVP && HitTest (m_prcActVP, ptM)) {
		if (m_pMove) 
			ChangePointer (m_pMove);
	} else {
		if (m_pLupe) 
			ChangePointer (m_pLupe);
	}
}

// Skalieren des Selektionsrechteckes -----------------------------------------
inline short Rescale (CoOrd c, CoOrd dNew, CoOrd dOld)
{
	return MulDiv (c, dNew, dOld);
}

void COverViewClientWindow::ReSize (ReSizeEvt evt)
{
	if (m_prcActVP) {
	// evtl. alte Selektion löschen
	HWND hWnd = Handle (API_WINDOW_HWND);
	HDC hDC = ::GetDC (hWnd);
	int iOldRop = SetROP2 (hDC, R2_XORPEN);
	HPEN hP = CreatePen (PS_SOLID, 0, RGB (0, 0, 0));
		
		hP = (HPEN)SelectObject (hDC, hP);
		DrawRectangle (hDC, m_prcActVP -> left, m_prcActVP -> top, m_prcActVP -> right, m_prcActVP -> bottom);

	CoOrd lXMin = xCVtoDB(m_prcActVP -> left);
	CoOrd lXMax = xCVtoDB(m_prcActVP -> right);
	CoOrd lYMin = yCVtoDB(m_prcActVP -> bottom);
	CoOrd lYMax = yCVtoDB(m_prcActVP -> top);

	// neues Selektionsrechteck berechnen und anzeigen
	Rectangle rcC (CanvasRect());
	
		CalculateScaleKoeffs(rcC);

		m_prcActVP -> left = xDBtoCV(lXMin);
		m_prcActVP -> right = xDBtoCV(lXMax);
		m_prcActVP -> bottom = yDBtoCV(lYMin);
		m_prcActVP -> top = yDBtoCV(lYMax);

		DrawRectangle (hDC, m_prcActVP -> left, m_prcActVP -> top, m_prcActVP -> right, m_prcActVP -> bottom);

		DeleteObject (SelectObject (hDC, hP));
		SetROP2 (hDC, iOldRop);
		ReleaseDC (hWnd, hDC);
	}
}

Bool COverView::QueryClose (Event)
{
	OverViewCFlag = false;
	m_fToDelete = true;		// kann gelöscht werden
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// MetaFile speichern/einlesen
DefineSmartInterface(Storage);
DefineSmartInterface(Stream);

HRESULT COverViewClientWindow::LoadEnhMetaFile (LPCSTR pcName, LPSTR pBuffer, int iLen)
{
	TX_ASSERT(NULL == m_hMF);

// SubStorage öffnen bzw. anlegen, wenn es noch nicht existiert
WStorage IStg;
HRESULT hr = E_FAIL;

	USES_CONVERSION;
	{
	WStorage IRootStg;

		if (!DEX_GetProjectStorage(*IRootStg.ppv()))
			return E_FAIL;

		hr = IRootStg -> OpenStorage (A2OLE(g_cbOverviews), NULL, 
					STGM_READWRITE|STGM_SHARE_EXCLUSIVE|STGM_TRANSACTED, 
					NULL, 0L, IStg.ppi());
		
		if (FAILED(hr)) return hr;
	} // IRootStg freigeben

BYTE *pBytes = NULL;

	try {
	// Stream erzeugen
	WStream IStm;

		THROW_FAILED_HRESULT(IStg -> OpenStream (A2OLE(pcName), NULL, STGM_READ|STGM_SHARE_EXCLUSIVE, 0L, IStm.ppi()));

	// Signatur und Version stehen vorn an
	DWORD dwSignature = 0, dwVersion = 0;

		THROW_FAILED_HRESULT(IStm -> Read (&dwSignature, sizeof(DWORD), NULL));
		if (METAFILE_SIGNATURE != dwSignature) 
			return E_UNEXPECTED;
		THROW_FAILED_HRESULT(IStm -> Read (&dwVersion, sizeof(DWORD), NULL));
		if ((dwVersion & ~METAFILE_VERSION_MINOR_MASK) > METAFILE_LASTKNOWN_VERSION)
			return E_UNEXPECTED;

	// jetzt kommen die Daten, MetaFile einlesen
	UINT uiBytes = 0L;

		THROW_FAILED_HRESULT(IStm -> Read (&uiBytes, sizeof(ULONG), NULL));	
		ATLTRY(pBytes = new BYTE[uiBytes]);
		if (NULL == pBytes) _com_issue_error(E_OUTOFMEMORY);
		THROW_FAILED_HRESULT(IStm -> Read (pBytes, uiBytes, NULL));

		m_hMF = SetEnhMetaFileBits (uiBytes, pBytes);
		if (NULL == m_hMF) _com_issue_error(E_OUTOFMEMORY);

	// ab #HK010315 wird der Ansichtsname mit gespeichert
		THROW_FAILED_HRESULT(IStm -> Read (&uiBytes, sizeof(ULONG), NULL));
		_ASSERTE(uiBytes <= iLen);
		THROW_FAILED_HRESULT(IStm -> Read (pBuffer, uiBytes, NULL));

	// zugehörigen Ausschnitt einlesen und Skalierung berechnen
		THROW_FAILED_HRESULT(IStm -> Read (&m_ocDB, sizeof(RECTL), NULL));

	Rectangle rcC (CanvasRect());

		m_dX = m_dY = m_dX0 = m_dY0 = 0;
		if (0 != rcC.Width() && 0 != rcC.Height())
			CalculateScaleKoeffs(rcC);

	} catch (_com_error& hr) {
		delete pBytes;
		return _COM_ERROR(hr);
	}
	delete pBytes;
	return S_OK;
}

HRESULT COverViewClientWindow::SaveEnhMetaFile (LPCSTR pcName)
{
	if (NULL == m_hMF) return E_HANDLE;

// SubStorage öffnen bzw. anlegen, wenn es noch nicht existiert
WStorage IStg;
HRESULT hr = E_FAIL;

	USES_CONVERSION;
	{
	WStorage IRootStg;

		if (!DEX_GetProjectStorage(*IRootStg.ppv()))
			return E_FAIL;

		hr = IRootStg -> OpenStorage (A2OLE(g_cbOverviews), NULL, 
					STGM_READWRITE|STGM_SHARE_EXCLUSIVE|STGM_TRANSACTED, 
					NULL, 0L, IStg.ppi());
		
		if (FAILED(hr)) {
			hr = IRootStg -> CreateStorage (A2OLE(g_cbOverviews),  
						STGM_READWRITE|STGM_SHARE_EXCLUSIVE|STGM_TRANSACTED, 
						0L, 0L, IStg.ppi());
		}
		if (FAILED(hr)) return hr;
	} // IRootStg freigeben

BYTE *pBytes = NULL;

	try {
	// Stream erzeugen
	WStream IStm;

		THROW_FAILED_HRESULT(IStg -> CreateStream (A2OLE(pcName), STGM_READWRITE|STGM_SHARE_EXCLUSIVE|STGM_CREATE, 0L, 0L, IStm.ppi()));

	// Signatur und Version wegschreiben
		THROW_FAILED_HRESULT(IStm -> Write (&METAFILE_SIGNATURE, sizeof(DWORD), NULL));
		THROW_FAILED_HRESULT(IStm -> Write (&METAFILE_LASTKNOWN_VERSION, sizeof(DWORD), NULL));

	// MetaFile wegschreiben
	UINT uiBytes = GetEnhMetaFileBits (m_hMF, (UINT)-1, NULL);
	
		ATLTRY(pBytes = new BYTE[uiBytes]);
		if (NULL == pBytes) _com_issue_error(E_OUTOFMEMORY);
		GetEnhMetaFileBits (m_hMF, uiBytes, pBytes);

		THROW_FAILED_HRESULT(IStm -> Write (&uiBytes, sizeof(ULONG), NULL));
		THROW_FAILED_HRESULT(IStm -> Write (pBytes, uiBytes, NULL));

	// Ansichtsnamen wegschreiben
		uiBytes = m_strViewName.size()+1;
		THROW_FAILED_HRESULT(IStm -> Write (&uiBytes, sizeof(ULONG), NULL));
		THROW_FAILED_HRESULT(IStm -> Write (m_strViewName.c_str(), uiBytes, NULL));

	// zugehörigen Bildausschnitt wegschreiben
		THROW_FAILED_HRESULT(IStm -> Write (&m_ocDB, sizeof(RECTL), NULL));

	// Änderungen speichern
		THROW_FAILED_HRESULT(IStm -> Commit (STGC_DEFAULT));

	} catch (_com_error& hr) {
		delete pBytes;
		return _COM_ERROR(hr);
	}

	delete pBytes;
	hr = IStg -> Commit (STGC_DEFAULT);
	if (SUCCEEDED(hr)) {
		DEX_SetDirtyGeoDB(true);
		m_fIsDirty = false;
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// RightButtonMenu
void COverViewClientWindow::MenuCommand (MenuCommandEvt e)
{
	BEGIN_COMMANDS(e.GetItemID()) 
		ON_COMMAND_ID(ID_OVERVIEW_RESETRECT, OnResetRect);	// Ausschnitt rücksetzen
		ON_COMMAND_ID(ID_OVERVIEW_ACTVIEW, OnActView);		// Aktuelle Ansicht übernehmen
		ON_COMMAND_ID(ID_OVERVIEW_HIDE, OnHideWindow);		// Fenster ausblenden
	END_COMMANDS;
}

// MenuBefehle
bool COverViewClientWindow::OnResetRect (void) 
{
	GetParent() -> PostEvent (Event(WM_COMMAND, IDM_RESTOREVIEWCONTAINER));
	return true;
}

bool COverViewClientWindow::OnActView (void) 
{
	if (RetrieveActViewMetaFile()) {
		RePaint();
		return true;
	}
	return false;
}

bool COverViewClientWindow::OnHideWindow (void) 
{
	TX_ASSERT(OverViewCFlag);		// Fenster muß angezeigt sein
	GetParent() -> PostEvent (Event(WM_COMMAND, IDM_OVERVIEW));
	return true;
}

// Menu initialisieren
void COverViewClientWindow::MenuInit (MenuInitEvt e)
{
	if (NULL == m_hSubMenu)
		return;		// SystemMenu geöffnet

	if (NULL != m_prcActVP)
		EnableMenuItem (m_hSubMenu, ID_OVERVIEW_RESETRECT, MF_BYCOMMAND|MF_ENABLED);
	else
		EnableMenuItem (m_hSubMenu, ID_OVERVIEW_RESETRECT, MF_BYCOMMAND|MF_GRAYED);

	SetMenuDefaultItem (m_hSubMenu, ID_OVERVIEW_ACTVIEW, false);
}

// StatusZeilenText anzeigen
void COverViewClientWindow::MenuSelect (MenuSelectEvt e)
{
	if (NULL == m_hSubMenu)
		return;		// SystemMenu geöffnet

UINT uiRes = 0L;

	switch (e.GetItemID()) {
	case ID_OVERVIEW_RESETRECT: uiRes = IDS_OVERVIEW_RESETRECT; break;
	case ID_OVERVIEW_ACTVIEW: uiRes = IDS_OVERVIEW_ACTVIEW; break;
	case ID_OVERVIEW_HIDE: uiRes = IDS_OVERVIEW_HIDE; break;
	}
	if (0 == uiRes) {
	// Separator getroffen
		DEX_SetMessageString(g_cbNil);
		return;
	}

ResString resStatus (uiRes, _MAX_PATH);

	DEX_SetMessageString (resStatus.Addr());
}

bool COverViewClientWindow::TrackOverviewMenu (Point pt)
{
HMENU hMenu = LoadMenu (hInstance, MAKEINTRESOURCE (IDR_OVERVIEW_DROPDOWN));

	if (hMenu == NULL) return false;	// irgend was stimmt nicht

// Menu generieren
	m_hSubMenu = GetSubMenu (hMenu, 0);		// SubMenu holen
	if (NULL == m_hSubMenu) {
		DestroyMenu (hMenu);
		return false;
	}

Rectangle Rc (CanvasRect());
HWND hWnd = Handle (API_CLIENT_HWND);

	pt.Y() = Rc.Height() - pt.Y();		// in WindowsKoord umrechnen
	ClientToScreen (hWnd, (LPPOINT)&pt);

BOOL fResult = TrackPopupMenu (m_hSubMenu, 0, pt.X(), pt.Y(), 0, hWnd, NULL);

// wieder aufräumen
	m_hSubMenu = NULL;
	DestroyMenu (hMenu);

	return fResult ? true : false;
}

