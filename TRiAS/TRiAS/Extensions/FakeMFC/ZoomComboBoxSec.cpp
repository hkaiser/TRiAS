// ZoomComboBoxSec.cpp : Implementation of the CInstZoomComboBoxSec

#include "fakemfcp.hxx"
#include "fakemfc.h"
#include "strings.h"

#include <itoolbar.h>
#include <toolguid.h>
#include <dirisole.h>

#include <afxtempl.h>
#define __AFXCONV_H__
#include <afxpriv.h>		// CDockState et.al.

#if !defined(_SEC_VER) || _SEC_VER < 0x0600
#include <secdll.h>
#include <sdocksta.h>
#include <tbarcust.h>
#endif // !defined(_SEC_VER) || _SEC_VER < 0x0600

#include "Wrapper.h"		// SmartInterfaces
#include "fakemfc.hxx"

#include "ZoomComboBoxSec.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Message sent when CWnd requires initialisation
const int WM_GETSETMODIFY = RegisterWindowMessage(_T("WM_GETSETMODIFY"));

/////////////////////////////////////////////////////////////////////////////
// CZoomComboBoxSec

IMPLEMENT_BUTTON(CZoomComboBoxSec)

CZoomComboBoxSec::CZoomComboBoxSec()
{
	m_fSubClassed = false;
	m_fChangedSel = false;
	m_fActiveView = false; 

char cbDummy[_MAX_PATH];

	if (DEX_GetActiveSight(cbDummy))
		m_fActiveView = true; 

	m_iCurrSel = -1;
	m_pCP = NULL;
}

CZoomComboBoxSec::~CZoomComboBoxSec()
{
	ASSERT(NULL != m_pCP);
	m_pCP -> SetSitePointers (NULL, NULL);
	RELEASE(m_pCP);

	if (m_fSubClassed && ::IsWindow(m_edit.m_hWnd)) 
		m_Hook.HookWindow (NULL);
	m_fSubClassed = false;
}

BEGIN_MESSAGE_MAP(CZoomComboBoxSec, CFlatComboBox)
	//{{AFX_MSG_MAP(CZoomComboBoxSec)
	ON_CONTROL_REFLECT(CBN_DROPDOWN, OnDropdown)
	ON_CONTROL_REFLECT(CBN_CLOSEUP, OnCloseup)
	ON_REGISTERED_MESSAGE(WM_GETSETMODIFY, OnGetSetModify)
	ON_WM_ENABLE()
	ON_WM_WINDOWPOSCHANGING()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CZoomComboBoxSec::OnFontCreateAndSet()
{
//  Create a font for the combobox
LOGFONT logFont;

	memset(&logFont, 0, sizeof(logFont));

	if (!::GetSystemMetrics(SM_DBCSENABLED)) {
	// Since design guide says toolbars are fixed height so is the font.
#ifndef _MAC
		logFont.lfHeight = -12;
#else
		logFont.lfHeight = -14;     // looks better than 12 on Mac
#endif
		logFont.lfWeight = FW_BOLD;
		logFont.lfPitchAndFamily = VARIABLE_PITCH | FF_SWISS;

	CString strDefaultFont;

		VERIFY(strDefaultFont.LoadString(IDS_DEFAULT_FONT));
		lstrcpy (logFont.lfFaceName, strDefaultFont);
		if (!m_font.CreateFontIndirect(&logFont))
			TRACE0("Could Not create font for controls.\n");
		else {
			SetFont(&m_font, true);
			m_ftZoom.SetFont(&m_font, true);
		}
	} 

	if (NULL == (HFONT)m_font) {
		m_font.Attach (::GetStockObject(SYSTEM_FONT));
		SetFont (&m_font, true);
		m_ftZoom.SetFont(&m_font, true);
	}
}

BOOL CZoomComboBoxSec::CreateWnd (CWnd* pParentWnd, DWORD dwStyle, CRect& rect, int nID)
{
// Static Text initialisieren
	if (!m_ftZoom.Create (g_cbZoomText, WS_CHILD|WS_VISIBLE|WS_DISABLED|WS_TABSTOP, rect, pParentWnd, ID_GEOVIEW_SELECTZOOM_TEXT))
	{
		TRACE0("Failed to create fixed text\n");
		return FALSE;
	}

// ComboBox initialisieren, Fonts setzen etc.
	if(!CFlatComboBox::CreateWnd (pParentWnd, dwStyle|WS_TABSTOP|WS_DISABLED|CBS_AUTOHSCROLL, rect, nID)) 
		return FALSE;

// Hook the child edit.
	if (!m_Hook.HookWindow (&m_edit))
		return FALSE;
	m_fSubClassed = true;

// hier sonstige Initialisierung durchführen
CComObject<CInstZoomComboBox> *pCP = NULL;

	if (FAILED(CComObject<CInstZoomComboBox>::CreateInstance (&pCP))) 
		return FALSE;

	m_pCP = pCP;
	pCP -> AddRef();

	if (FAILED(pCP -> SetSitePointers (g_pTE -> m_pXtnSite, this))) 
		return FALSE;

// Zooms initialisieren
	if (S_OK == FillWithZooms() && GetActiveView()) 		// Sicht ist bereits aktiv
		AdjustZoom();

	{
	CDC *pDC = m_ftZoom.GetDC();
	CFont *pOldFont = pDC -> SelectObject (&m_font);
	
		m_szText = pDC -> GetTextExtent (g_cbZoomText, strlen(g_cbZoomText));
		m_szText.cx += 6;
		pDC -> SelectObject (pOldFont);
		m_ftZoom.ReleaseDC (pDC);
	}

	EnableWindow (FALSE);				// erstmal passivieren
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// Funktionen von SecWndBttn überladen, um '1:' davor zu zaubern

void CZoomComboBoxSec::SetMode(BOOL bVertical)
{
	CFlatComboBox::SetMode (bVertical);		

	if(!bVertical) {
	// Text auch noch richten
	int y = (m_cy - m_szText.cy) / 2;

		m_ftZoom.SetWindowPos (NULL, m_x + 1, m_y + y, m_szText.cx - 1, m_szText.cy, 
							   SWP_NOZORDER|SWP_NOACTIVATE|SWP_SHOWWINDOW);
	}
}

void CZoomComboBoxSec::SetPos(int x, int y)
{
	CFlatComboBox::SetPos (x, y);

	if(m_bWndVisible) {
	// Text auch noch richten
	int y = (m_cy - m_szText.cy) / 2;

		m_ftZoom.SetWindowPos (NULL, m_x + 1, m_y + y, 0, 0, SWP_NOSIZE|SWP_NOZORDER|SWP_NOACTIVATE);
	}
}

///////////////////////////////////////////////////////////////////////////////
// CZoomComboBoxSec message handlers

void CZoomComboBoxSec::OnDropdown() 
{
	m_iCurrSel = GetCurSel();
}

void CZoomComboBoxSec::OnCloseup() 
{
int iIndex = GetCurSel();

	m_fChangedSel = (iIndex != m_iCurrSel) ? true : false;
	m_iCurrSel = iIndex;
}

LONG CZoomComboBoxSec::OnGetSetModify (UINT wParam, LONG lParam)
{
	switch (wParam) {
	case EM_GETMODIFY:
		return GetModify();

	case EM_SETMODIFY:
		SetModify (lParam ? TRUE : FALSE);
		return TRUE;

	default:
		break;
	}
	return FALSE;
}

void CZoomComboBoxSec::OnWindowPosChanging (WINDOWPOS *lpwndpos) 
{
	CFlatComboBox::OnWindowPosChanging(lpwndpos);
	
	if (!(lpwndpos -> flags & SWP_NOSIZE)) 
		lpwndpos -> cx = m_cx - m_szText.cx;

	if (!(lpwndpos -> flags & SWP_NOMOVE)) 
		lpwndpos -> x = m_x + m_szText.cx;
}

void CZoomComboBoxSec::OnEnable(BOOL bEnable) 
{
	CFlatComboBox::OnEnable(bEnable);
	m_ftZoom.EnableWindow (bEnable);
}

void CZoomComboBoxSec::PrePaint()
{
// The CWnd calls this before it paints.
	CFlatComboBox::PrePaint();

// Need to ensure that the whole control is redrawn - otherwise problems
// with XOR draw of Drag Rect.
	if (!(m_nStyle & SEC_TBBS_FOCUS)) {
	CWindowDC dc (m_pToolBar);
	CRect rect;
	
		this->GetWindowRect(&rect);

	CRect r (-m_szText.cx, 0, 0, rect.Height());

		this->ClientToScreen (&r);
		m_pToolBar -> ScreenToClient (&r);
		dc.FillSolidRect (&r, ::GetSysColor(COLOR_BTNFACE));
	}

// Text has to be drawn _before_ combobox
	m_ftZoom.Invalidate (FALSE);
	m_ftZoom.UpdateWindow();

//	GetWnd()->Invalidate (FALSE);
}

void CZoomComboBoxSec::PostPaint()
{
	// The CWnd calls this after it has painted.
	if(m_nStyle & SEC_TBBS_FOCUS) {
	// We have customize focus - add the focus rect.
	CWindowDC dc (m_pToolBar);
	
		dc.SetBkColor(RGB(255, 255, 255));
		dc.SetTextColor(RGB(0, 0, 0));

	CRect rect;
	
		this->GetWindowRect(&rect);

	CRect r (-m_szText.cx, 0, m_cx - m_szText.cx, rect.Height());

		this->ClientToScreen (&r);
		m_pToolBar->ScreenToClient (&r);

		dc.DrawDragRect(r, CSize(3, 3), NULL, CSize(3, 3));
	}
}

/////////////////////////////////////////////////////////////////////////////
//

bool CZoomComboBoxSec::GetModify (void)
{
	if (!m_fSubClassed)
		return false;

	return m_edit.GetModify() || m_fChangedSel; 
}

void CZoomComboBoxSec::SetModify (bool fModify)
{
	if (m_fSubClassed) {
		m_edit.SetModify(fModify);
		m_fChangedSel = fModify ? true : false; 
	}
}

///////////////////////////////////////////////////////////////////////////////
//
#define CNT_MASSTAB		(IDS_MASSTAB5000000-IDS_MASSTAB250+1)

HRESULT CZoomComboBoxSec::FillWithZooms (void)
{
	ResetContent();		// alles rauswerfen

	if (!DEX_TestActiveProject())
		return S_FALSE;

// MaßstabsComboBox füllen
	for (short i = 0; i < CNT_MASSTAB; i++) {
	CString str;

		TRY { 
			VERIFY(str.LoadString(IDS_MASSTAB250+i));
		} CATCH_ALL(e) {
			continue;
		} END_CATCH_ALL
		AddString (str);
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// aktuellen Maßstab voreinstellen
HRESULT CZoomComboBoxSec::ActivateActualZoom (long M)
{
	if (M == 0) {
		SetWindowText(g_cbNil);
		return S_OK;		// 1:0 nicht anzeigen
	}

CString str;

	if (M < 0) M = -M;
	if (M >= 1000000L) {
	int iMill = (int)(M / 1000000L);
	int iTaus = (int)((M % 1000000L) / 1000L);
	int iEin = (int)(M % 1000L);

		str.Format (TEXT("%d.%03d.%03d"), iMill, iTaus, iEin);
	} 
	else if (M >= 1000L) {
	int iTaus = (int)(M / 1000L);
	int iEin = (int)(M % 1000L);

		str.Format (TEXT("%d.%03d"), iTaus, iEin);
	} 
	else {
		str.Format (TEXT("%ld"), M);
	}

	SetCurSel (-1);
	SetWindowText (str);
	return NOERROR;
}

void CZoomComboBoxSec::AdjustZoom (void)
{
double dblZoom = 1.0;

	if (DEX_GetActiveZoom(dblZoom) && dblZoom != 1.0)
		ActivateActualZoom ((long)(dblZoom+0.5));
}

/////////////////////////////////////////////////////////////////////////////
// CZoomEditSec

/////////////////////////////////////////////////////////////////////////////
// CZoomEditSec message handlers

LONG CZoomEditSec::WindowProc (UINT msg, WPARAM wp, LPARAM lp)
{
	if (WM_CHAR == msg) {
		OnChar (wp, LOWORD(lp), HIWORD(lp));
		return TRUE;
	}
	
	return CMsgHook::WindowProc (msg, wp, lp);
}

void CZoomEditSec::OnChar (UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if ((nChar >= '0' && nChar <= '9') || nChar == '.' || VK_BACK == nChar)
		Default();
	else {
		::MessageBeep(MB_ICONEXCLAMATION);
//		SetFocus();
	}
}

///////////////////////////////////////////////////////////////////////////////
// Fertig initialisiert
HRESULT CInstZoomComboBox::FinalConstruct (void)
{
	m_dwCookie = 0L;
	m_pBack = NULL;

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Am TRiAS-ConnectionPoint ankoppeln
HRESULT CInstZoomComboBox::SetSitePointers (
	ITriasXtensionSite *pSite, CZoomComboBoxSec *pBack)
{
	try {
		if (NULL != pSite) {
			m_Cont = pSite;		// throws HRESULT
			THROW_FAILED_HRESULT(AtlAdvise (m_Cont, (ITRiASNotificationSink *)this, IID_ITRiASNotificationSink, &m_dwCookie));
		} else
			DisConnectFromServer();

		m_pBack = pBack;		// lediglich backpointer speichern
						
	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}
	return NOERROR;
}

HRESULT CInstZoomComboBox::DisConnectFromServer (void)
{
HRESULT hr = NOERROR;

	if (NULL != (IUnknown *)m_Cont && 0 != m_dwCookie) {
		hr = AtlUnadvise (m_Cont, IID_ITRiASNotificationSink, m_dwCookie);
		if (SUCCEEDED(hr)) {
			m_dwCookie = 0L;
			m_Cont.Assign (NULL);	// Release()
		}
	}
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// *** ITRiASNotificationSink specific functions ***
STDMETHODIMP CInstZoomComboBox::ServerEvent (SERVEREVT se)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

HRESULT hr = NOERROR;

	switch (se) {
	case SERVEREVT_ServerToClose:	// das letzte vom Tage
		DisConnectFromServer();
		break;
	}
	return hr;
}

STDMETHODIMP CInstZoomComboBox::ProjectEvent (long hPr, PROJECTEVT pe, VARIANT)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	switch (pe) {
	case PROJECTEVT_ProjectOpened:
		m_pBack -> FillWithZooms();		// mit Zooms füllen
		if (m_pBack -> GetActiveView()) 		// Sicht ist bereits aktiv
			m_pBack -> AdjustZoom();
		m_fProjectOpen = true;
		break;

	case PROJECTEVT_ProjectToClose:
		m_pBack -> SetWindowText(g_cbNil);
		m_pBack -> SetCurSel (-1);
		m_pBack -> SetActiveView (false); 
		m_fProjectOpen = false;
		break;

	case PROJECTEVT_ChangedCoordFormat:		
		if (m_pBack -> GetActiveView()) 
			m_pBack -> AdjustZoom();		// evtl. Skalierung geändert
		break;
	}
	return NOERROR;
}

STDMETHODIMP CInstZoomComboBox::GeoViewEvent (long hPr, GEOVIEWEVT ve, VARIANT vData)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	switch (ve) {
	case GEOVIEWEVT_ViewSelected:
		if (VT_BSTR == vData.vt && NULL != V_BSTR(&vData)) {	
		// neue Ansicht ausgewählt
			if (m_fProjectOpen) 
				m_pBack -> AdjustZoom();
			m_pBack -> SetActiveView (true);
		} else
			m_pBack -> SetActiveView (false);
		break;

	case GEOVIEWEVT_ZoomChanged:
		if (m_pBack -> GetActiveView() && m_fProjectOpen) {
			ASSERT(VT_I4 == vData.vt);
			m_pBack -> ActivateActualZoom ((LONG)V_I4(&vData));
		}
		break;
	}
	return NOERROR;
}

STDMETHODIMP CInstZoomComboBox::GeoClassEvent (long hPr, GEOCLASSEVT ce, long ulIdent)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())
	return NOERROR;
}

STDMETHODIMP CInstZoomComboBox::GeoObjectEvent (long hPr, GEOOBJECTEVT oe, long lONr)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())
	return NOERROR;
}

STDMETHODIMP CInstZoomComboBox::GeoFeatureEvent (long hPr, GEOFEATUREEVT fe, long ulMCode)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())
	return NOERROR;
}

STDMETHODIMP CInstZoomComboBox::GeoRelationEvent (long hPr, GEORELATIONEVT re, long ulRCode)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())
	return NOERROR;
}

STDMETHODIMP CInstZoomComboBox::ObjectWindowEvent (OBJWNDEVT oe, long hORWnd)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())
	return NOERROR;
}

#if !defined(_USE_SEC_CLASSES)
///////////////////////////////////////////////////////////////////////////////
// StaticText

// Diese Funktion wird gerufen, wenn unser Control in einer Toolbar eingehängt
// werden soll.
// Die Toolbar erkennt das daran, daß sie einen Separator mit einem uiID vor-
// findet und das zugehörige Feld 'dwData' ungleich NULL ist. 'dwData' ist in 
// diesem Fall unser this-Pointer.

STDMETHODIMP CInstZoomStatic::InstallControl (ITRiASBar *pIBar, UINT uiCtrlID, DWORD dwStyle)
{
CRect rect;
int iIndex = -1;
HRESULT hr = pIBar -> CommandToIndex (uiCtrlID, &iIndex);

	if (FAILED(hr)) return hr;

	hr = pIBar -> GetItemRect (iIndex, &rect);
	if (FAILED(hr)) return hr;

HWND hWnd = NULL;

	hr = pIBar -> GetBarHandle (&hWnd);
	if (FAILED(hr)) return hr;

// ComboBox generieren
CWnd *pWnd = CWnd::FromHandle (hWnd);

	ASSERT(NULL != pWnd);

// ComboBox initialisieren
	rect.left += 6;		// default Separator freilassen
	rect.top += 3;
	if (!m_ftZoom.Create(TEXT("1:"), WS_CHILD|WS_VISIBLE,
			rect, pWnd, uiCtrlID))
	{
		TRACE0("Failed to create fixed text\n");
		return E_UNEXPECTED;
	}
	if (InstallFont(m_font, true))			// Font für Text setzen
		m_ftZoom.SetFont (&m_font);

return hr;
}
#endif // !_USE_SEC_CLASSES

