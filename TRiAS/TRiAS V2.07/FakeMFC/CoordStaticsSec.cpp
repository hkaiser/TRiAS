// CoordStaticsSec.cpp : Declaration of the CZoomComboBox

#include "fakemfcp.hxx"
#include "fakemfc.h"
#include "strings.h"

#include <itoolbar.h>
#include <toolguid.h>
#include <dirisole.h>

#include <afxtempl.h>
#define __AFXCONV_H__
#include <afxpriv.h>		// CDockState et.al.

#include <secdll.h>
#include <sdocksta.h>
#include <tbarcust.h>

#include "Wrapper.h"		// SmartInterfaces
#include "fakemfc.hxx"

#include "CoordStaticsSec.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Externe Funktionen
extern "C" LPSTR PASCAL ConvertFltToStr (LPSTR lpszString, LPSTR lpszFormat, int iPrec, double dblFloat);

/////////////////////////////////////////////////////////////////////////////
// zusätzliche Wrapper
DefineSmartInterface(TRiASSysNotificationSink);

IMPLEMENT_BUTTON(CCompoundStaticSec)

/////////////////////////////////////////////////////////////////////////////
// CCompoundStaticSec

CCompoundStaticSec::CCompoundStaticSec()
{
	m_fShowToolTips = false;
	m_fDrag = false;
	m_pCP = NULL;
	m_pCTF = NULL;

	m_iHeight = -1;

	TRY {
		m_strDistance.LoadString (IDS_DISTANCE);
		
	} CATCH (CMemoryException, e) {
		ASSERT(false);
	} END_CATCH;
}

CCompoundStaticSec::~CCompoundStaticSec()
{
	ASSERT(NULL != m_pCP);
	m_pCP -> SetSitePointers (NULL, NULL);
	RELEASE(m_pCP);

	m_pCTF -> SetXtsnSite (NULL);
	RELEASE(m_pCTF);
}

BEGIN_MESSAGE_MAP(CCompoundStaticSec, CStatic)
	//{{AFX_MSG_MAP(CCompoundStaticSec)
	ON_WM_CREATE()
	ON_WM_ENABLE()
	ON_WM_NCHITTEST()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, OnToolTipText)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, OnToolTipText)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Operations

bool CCompoundStaticSec::ResetTexts (void)
{
CString str;

	TRY {
		str.LoadString (IDS_RECHTSWERT);
		m_ftCoordX.SetWindowText (str);
		str.LoadString (IDS_HOCHWERT);
		m_ftCoordY.SetWindowText (str);

	} CATCH (CMemoryException, e) {
		TRACE0("Failed to load string resource\n");
		return false;
	} END_CATCH;
	return true;
}

inline void DCtoOC (const CPoint &rPt, Punkt *pPt)
{
COORDCONVERT CT;

	CT.lpPt = (POINT *)&rPt;
	CT.lpPkt = (long *)pPt;
	DEX_DCtoOC(CT);
}

HRESULT CCompoundStaticSec::SetCoords (CPoint &rPt, bool fDrag)
{
	if (NULL == m_pCTF || !m_pCTF -> EnsureLoaded() || !IsWindowEnabled()) 
		return NOERROR;		// no open project

// Koordinaten in DB-Koordinaten umsetzen
Punkt Pkt;

	DCtoOC (rPt, &Pkt);       // Device --> Objekt

// Koordinaten transformieren (incl. rausrechnen der internen Skalierung)
double XOut, YOut;
char cbOutBuff[40];		// temporäre Zeichenkette

	if (!m_pCTF -> UnScale (Pkt.X(), Pkt.Y(), &XOut, &YOut))
		return S_OK;		// weiterreichen

	if (fDrag) {
		if (!m_fDrag) {
		// erste Koordinate merken
			m_dblBegin = DoublePair (XOut, YOut);
			m_fDrag = true; 
		}

	// Abstand berechnen und anzeigen
	DoublePair DP (XOut, YOut);
	CString strOut (m_strDistance);

		ConvertFltToStr (cbOutBuff, "%ld.%03lu", 3, m_pCTF -> CoordTransDistance (&DP, &m_dblBegin)/1000.0);
		strOut += cbOutBuff;
		DEX_SetMessageStringNoKickIdle((LPCSTR)strOut);
	}

// Koordinaten korrigieren
	m_pCTF -> Transform (&XOut, &YOut);

// Koordinaten ausgeben        
	m_pCTF -> CoordTransToStringEx (XOut, YOut, true, cbOutBuff, sizeof(cbOutBuff));
	m_ftCoordX.SetWindowText (cbOutBuff);
	m_pCTF -> CoordTransToStringEx (XOut, YOut, false, cbOutBuff, sizeof(cbOutBuff));
	m_ftCoordY.SetWindowText (cbOutBuff);
	
	return NOERROR;
}

/////////////////////////////////////////////////////////////////////////////
// SECWndBtn handlers

CWnd *CCompoundStaticSec::GetWnd (void)
{
	return this;
}

void CCompoundStaticSec::OnFontCreateAndSet()
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
		logFont.lfWeight = FW_NORMAL;
		logFont.lfPitchAndFamily = VARIABLE_PITCH | FF_SWISS;

	CString strDefaultFont;

		strDefaultFont.LoadString(IDS_DEFAULT_FONT);
		lstrcpy (logFont.lfFaceName, strDefaultFont);
		if (!m_font.CreateFontIndirect(&logFont))
			TRACE0("Could Not create font for controls.\n");
		else {
			m_ftCoordX.SetFont (&m_font, true);
			m_ftDel.SetFont (&m_font, true);
			m_ftCoordY.SetFont (&m_font, true);
		}
	} 
	
	if (NULL == (HFONT)m_font) {
		m_font.Attach (::GetStockObject(SYSTEM_FONT));
		m_ftCoordX.SetFont (&m_font, true);
		m_ftDel.SetFont (&m_font, true);
		m_ftCoordY.SetFont (&m_font, true);
	}

// Höhe des Textes mit aktuellem Font berechnen
	{
	HGDIOBJ hOldFont = NULL;
	CClientDC dc (this);

		if ((HFONT)m_font != NULL) 
			hOldFont = dc.SelectObject((HFONT)m_font);

	TEXTMETRIC tm;

		dc.GetTextMetrics (&tm);
		m_iHeight = tm.tmHeight+2;
		if (hOldFont != NULL) 
			dc.SelectObject(hOldFont);
	}
}

BOOL CCompoundStaticSec::CreateWnd (CWnd* pParentWnd, DWORD dwStyle, CRect& rect, int nID)
{
// SECWndBtn initialisieren, Fonts setzen etc.
DWORD dwStyleEx = WS_EX_STATICEDGE;

	if (!IsWin40()) {
		dwStyle |= WS_BORDER;
		dwStyleEx = 0;
	}

// CStatics generieren
	if (!CreateEx (dwStyleEx, _T("STATIC"), g_cbNil, dwStyle, 
				   rect.left, rect.top, rect.Width(), rect.Height(),
				   pParentWnd->m_hWnd, (HMENU)nID))
	{
		TRACE0("Failed to create compound static for coordinates\n");
		return E_UNEXPECTED;
	}
	this -> OnFontCreateAndSet();
	this -> AdjustSize();		// save latest and greatest size info

	EnableToolTips(true);

// jetzt Fonts einstellen

// hier sonstige Initialisierung durchführen
CComObject<CInstCoordStatics> *pCP = NULL;

	if (FAILED(CComObject<CInstCoordStatics>::CreateInstance (&pCP))) 
		return FALSE;

	m_pCP = pCP;
	pCP -> AddRef();

	if (FAILED(pCP -> SetSitePointers (g_pTE -> m_pXtnSite, this))) 
		return FALSE;

// KoordinatenTransformationsObjekt anlegen
CComObject<CConnectedCtf> *pCTF = NULL;

	if (FAILED(CComObject<CConnectedCtf>::CreateInstance (&pCTF)))
		return FALSE;

	m_pCTF = pCTF;
	pCTF -> AddRef();

	if (FAILED(m_pCTF -> SetXtsnSite (g_pTE -> m_pXtnSite)))
		return FALSE;

	return TRUE;
}

void CCompoundStaticSec::AdjustSize()
{
	SECWndBtn::AdjustSize();
	m_nHeight = m_cy;		// die Höhe ist nicht von außen voreinstellbar
}

/////////////////////////////////////////////////////////////////////////////
// CCompoundStaticSec message handlers

int CCompoundStaticSec::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CStatic::OnCreate(lpCreateStruct) == -1)
		return -1;
	
// Rechtswert 
DWORD dwStyle = WS_CHILD|WS_VISIBLE|SS_CENTER|WS_DISABLED;
CRect r;

	r.SetRectEmpty();
	if (!m_ftCoordX.Create(g_cbNil, dwStyle, r, this, ID_RECHTSWERT))
	{
		TRACE0("Failed to create fixed text (Name X)\n");
		return -1;
	}

// Delimiter
	if (!m_ftDel.Create(TEXT(":"), dwStyle, r, this, ID_DELIMITER))
	{
		TRACE0("Failed to create fixed text (delimiter)\n");
		return -1;
	}

// Hochwert
	if (!m_ftCoordY.Create(g_cbNil, dwStyle, r, this, ID_HOCHWERT))
	{
		TRACE0("Failed to create fixed text (Name Y)\n");
		return -1;
	}

// Texte initialisieren
	ResetTexts();
	return 0;
}

void CCompoundStaticSec::OnSize(UINT nType, int cx, int cy) 
{
	CStatic::OnSize(nType, cx, cy);

// childs neu in Größe und Lage verändern
CRect rect;

	GetWindowRect (&rect);

int iTop = (rect.Height() - m_iHeight)/2;
int iWidth = rect.Width()/2;

	m_ftCoordX.SetWindowPos (NULL, 2, iTop, iWidth-4, m_iHeight, SWP_NOZORDER);
	m_ftDel.SetWindowPos (NULL, iWidth-2, iTop, 4, m_iHeight, SWP_NOZORDER);
	m_ftCoordY.SetWindowPos (NULL, iWidth+2, iTop, iWidth-4, m_iHeight, SWP_NOZORDER);
}

void CCompoundStaticSec::OnEnable(BOOL bEnable) 
{
	CStatic::OnEnable(bEnable);

	m_ftCoordX.EnableWindow (bEnable);
	m_ftDel.EnableWindow (bEnable);
	m_ftCoordY.EnableWindow (bEnable);
}

// Entscheiden, für welches Childcontrol ein ToolTip angezeigt werden soll
int CCompoundStaticSec::OnToolHitTest(CPoint point, TOOLINFO* pTI) const
{
	if (NULL == pTI)
		return m_nID;

	pTI -> uFlags |= (TTF_NOTBUTTON|TTF_CENTERTIP|TTF_IDISHWND|TTF_ALWAYSTIP);
	pTI -> hwnd = m_hWnd;
	pTI -> lpszText = LPSTR_TEXTCALLBACK;

CRect rect;

	GetClientRect (rect);
	if (point.x < rect.Width()/2) {
		pTI -> uId = (UINT)::GetDlgItem(m_hWnd, ID_RECHTSWERT);
		return ID_RECHTSWERT;
	} else {
		pTI -> uId = (UINT)::GetDlgItem(m_hWnd, ID_HOCHWERT);
		return ID_HOCHWERT;
	}
}
  
// Tooltiptexte herausfischen und an ToolTipControl weitergeben ---------------
#define _countof(array) (sizeof(array)/sizeof(array[0]))

bool CCompoundStaticSec::OnToolTipText(UINT, NMHDR* pNMHDR, LRESULT* pResult)
{
	ASSERT(pNMHDR->code == TTN_NEEDTEXTA || pNMHDR->code == TTN_NEEDTEXTW);

// need to handle both ANSI and UNICODE versions of the message
TOOLTIPTEXTA* pTTTA = (TOOLTIPTEXTA*)pNMHDR;
TOOLTIPTEXTW* pTTTW = (TOOLTIPTEXTW*)pNMHDR;
CString strTipText (g_cbNil);

	if (ShowToolTips()) {
	UINT nID = pNMHDR->idFrom;

		if (pNMHDR->code == TTN_NEEDTEXTA && (pTTTA->uFlags & TTF_IDISHWND) ||
			pNMHDR->code == TTN_NEEDTEXTW && (pTTTW->uFlags & TTF_IDISHWND))
		{
			// idFrom is actually the HWND of the tool
			nID = ((UINT)(WORD)::GetDlgCtrlID((HWND)nID));
		}

		if (NULL != m_pCTF && nID != 0) {	// will be zero on a separator
		CString str;
		CString strDesc;
		LPTSTR pBuffer = NULL;

			TRY {
				pBuffer = str.GetBufferSetLength (_MAX_PATH);
				strDesc.LoadString ((ID_HOCHWERT == nID) ? IDS_HOCHWERT : IDS_RECHTSWERT);
			} CATCH (CMemoryException, e) {
				return false;
			} END_CATCH;

			if (m_pCTF -> CoordTransDescription (pBuffer, _MAX_PATH)) {
				str.ReleaseBuffer();
				strTipText = str + TEXT(": ");
			} 

			strTipText += strDesc;
		}
	}

#ifndef _UNICODE
	if (pNMHDR->code == TTN_NEEDTEXTA)
		lstrcpyn(pTTTA->szText, strTipText, _countof(pTTTA->szText));
	else
		_mbstowcsz(pTTTW->szText, strTipText, _countof(pTTTW->szText));
#else
	if (pNMHDR->code == TTN_NEEDTEXTA)
		_wcstombsz(pTTTA->szText, strTipText, _countof(pTTTA->szText));
	else
		lstrcpyn(pTTTW->szText, strTipText, _countof(pTTTW->szText));
#endif
	*pResult = 0;

// bring the tooltip window above other popup windows
	::SetWindowPos(pNMHDR->hwndFrom, HWND_TOP, 0, 0, 0, 0,
		SWP_NOACTIVATE|SWP_NOSIZE|SWP_NOMOVE);

	return true;    // message was handled
}

UINT CCompoundStaticSec::OnNcHitTest(CPoint point) 
{
UINT uiHT = CStatic::OnNcHitTest(point);

	if (HTTRANSPARENT == uiHT)
		return HTCLIENT;

	return uiHT;
}

/////////////////////////////////////////////////////////////////////////////
// CToolTipStaticSec

CToolTipStaticSec::CToolTipStaticSec()
{
}

CToolTipStaticSec::~CToolTipStaticSec()
{
}

BEGIN_MESSAGE_MAP(CToolTipStaticSec, CStatic)
	//{{AFX_MSG_MAP(CToolTipStaticSec)
	ON_WM_NCHITTEST()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolTipStaticSec message handlers

UINT CToolTipStaticSec::OnNcHitTest(CPoint point) 
{
UINT uiHT = CStatic::OnNcHitTest(point);

	if (HTTRANSPARENT == uiHT)
		return HTCLIENT;

	return uiHT;
}

/////////////////////////////////////////////////////////////////////////////
//
HRESULT CInstCoordStatics::DisConnectFromServer (void)
{
HRESULT hr = NOERROR;

	if (NULL != (IUnknown *)m_Cont) {
	// normale Notifikationen abmelden
		if (0 != m_dwCookie) {
			hr = AtlUnadvise (m_Cont, IID_ITRiASNotificationSink, m_dwCookie);
			if (SUCCEEDED(hr)) 
				m_dwCookie = 0L;
		}

	// WindowsMessages abmelden
		if (0 != m_dwCookieSys) {
			hr = AtlUnadvise (m_Cont, IID_ITRiASSysNotificationSink, m_dwCookieSys);
			if (SUCCEEDED(hr)) 
				m_dwCookieSys = 0L;
		}
		m_Cont.Assign (NULL);	// Release()
	}

return hr;
}

///////////////////////////////////////////////////////////////////////////////
// *** ITRiASNotificationSink specific functions ***
STDMETHODIMP CInstCoordStatics::ServerEvent (SERVEREVT se)
{
	switch (se) {
	case SERVEREVT_ServerToClose:	// das letzte vom Tage
		DisConnectFromServer();
		break;

	case SERVEREVT_ShowToolTips:
		m_pBack -> ShowToolTips (true);
		break;

	case SERVEREVT_ShowNoMoreToolTips:
		m_pBack -> ShowToolTips (false);
		break;
	}

return NOERROR;
}

STDMETHODIMP CInstCoordStatics::ProjectEvent (long hPr, PROJECTEVT pe, VARIANT)
{
	switch (pe) {
	case PROJECTEVT_ProjectToClose:
		m_pBack -> ResetTexts();
		break;
	
	case PROJECTEVT_ChangedCoordFormat:
		m_pBack -> SetCoords (m_ptLast);
		break;
	}

return NOERROR;
}

STDMETHODIMP CInstCoordStatics::GeoViewEvent (long hPr, GEOVIEWEVT ve, VARIANT)
{
	return NOERROR;
}

STDMETHODIMP CInstCoordStatics::GeoClassEvent (long hPr, GEOCLASSEVT ce, long ulIdent)
{
	return NOERROR;
}

STDMETHODIMP CInstCoordStatics::GeoObjectEvent (long hPr, GEOOBJECTEVT oe, long lONr)
{
	return NOERROR;
}

STDMETHODIMP CInstCoordStatics::GeoFeatureEvent (long hPr, GEOFEATUREEVT fe, long ulMCode)
{
	return NOERROR;
}

STDMETHODIMP CInstCoordStatics::GeoRelationEvent (long hPr, GEORELATIONEVT re, long ulRCode)
{
	return NOERROR;
}

STDMETHODIMP CInstCoordStatics::ObjectWindowEvent (OBJWNDEVT oe, long hORWnd)
{
	return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// *** ITRiASSysNotificationSink specific functions ***

STDMETHODIMP CInstCoordStatics::WindowsMessage (long hWnd, long uiMsg, long wParam, long lParam)
{
	if (uiMsg >= WM_MOUSEFIRST && uiMsg <= WM_MOUSELAST)
		return RouteMouseEvents ((HWND)hWnd, uiMsg, wParam, lParam);

	return NOERROR;		// nicht bearbeitet
}

///////////////////////////////////////////////////////////////////////////////
// 
HRESULT CInstCoordStatics::RouteMouseEvents (HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
	if (WM_LBUTTONDOWN == uiMsg) 
		m_fDrag = (NUMLINEAL == DEX_GetActiveTool()) ? true : false;

	ASSERT(NULL != m_pBack);

	if (m_fDrag && WM_LBUTTONUP == uiMsg) {
		m_fDrag = false;
		m_pBack -> ResetDrag();
		DEX_SetMessageStringNoKickIdle ((LPCSTR)m_strIdle);
	}

	if (WM_MOUSEMOVE == uiMsg) {
		m_ptLast = CPoint(LOWORD(lParam), HIWORD(lParam));
		return m_pBack -> SetCoords (m_ptLast, m_fDrag);
	}
	return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// StaticTexts für KoordinatenAnzeige
CInstCoordStatics::CInstCoordStatics (void)
{
	m_dwCookie = 0L;
	m_dwCookieSys = 0L;
	m_fDrag = false;
	m_pBack = NULL;

	TRY {
		m_strIdle.LoadString (AFX_IDS_IDLEMESSAGE);
	} CATCH (CMemoryException, e) {
		ASSERT(false);
	} END_CATCH;
}

///////////////////////////////////////////////////////////////////////////////
// Am TRiAS-ConnectionPoint ankoppeln
HRESULT CInstCoordStatics::SetSitePointers (
	ITriasXtensionSite *pSite, CCompoundStaticSec *pBack)
{
	try {
		if (NULL != pSite) {
			m_Cont = pSite;		// throws HRESULT
			THROW_FAILED_HRESULT(AtlAdvise (m_Cont, (ITRiASNotificationSink *)this, IID_ITRiASNotificationSink, &m_dwCookie));
				
		// Alle WindowsMessages auch hier vorbeischicken	
			THROW_FAILED_HRESULT(AtlAdvise (m_Cont, (ITRiASSysNotificationSink *)this, IID_ITRiASSysNotificationSink, &m_dwCookieSys));
		} else
			DisConnectFromServer();

		m_pBack = pBack;

	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

	return NOERROR;
}

