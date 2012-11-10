// ViewComboBoxSec.cpp : Implementation of the CInstViewComboBox

#include "fakemfcp.hxx"
#include "fakemfc.h"

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

#include "ViewComboBoxSec.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewComboBoxSec

IMPLEMENT_BUTTON(CViewComboBoxSec)

CViewComboBoxSec::CViewComboBoxSec()
{
	m_fNoActView = false;
	m_pCP = NULL;
}

CViewComboBoxSec::~CViewComboBoxSec()
{
	ASSERT(NULL != m_pCP);
	m_pCP -> SetSitePointers (NULL, NULL);
	RELEASE(m_pCP);
}

BEGIN_MESSAGE_MAP(CViewComboBoxSec, SECComboBtn)
	//{{AFX_MSG_MAP(CViewComboBoxSec)
	//}}AFX_MSG_MAP
//	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, OnToolTipText)
//	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, OnToolTipText)
END_MESSAGE_MAP()


BOOL CViewComboBoxSec::CreateWnd (CWnd* pParentWnd, DWORD dwStyle, CRect& rect, int nID)
{
	dwStyle |= WS_DISABLED;
	if (!SECComboBtn::CreateWnd (pParentWnd, dwStyle, rect, nID))
		return FALSE;

// hier sonstige Initialisierung durchführen
CComObject<CInstViewComboBox> *pCP = NULL;
HRESULT hr = CComObject<CInstViewComboBox>::CreateInstance (&pCP);

	if (FAILED(hr)) return hr;

	m_pCP = pCP;
	pCP -> AddRef();

	hr = pCP -> SetSitePointers (g_pTE -> m_pXtnSite, this);
	if (FAILED(hr)) return hr;

// mit Ansichten füllen
	hr = FillWithViews();	
	if (S_OK == hr)
		hr = ActivateActualView();		// aktuelle Ansicht voreinstellen

	EnableWindow (FALSE);				// erstmal passivieren
//	EnableToolTips();
	return SUCCEEDED(hr);
}

void CViewComboBoxSec::OnFontCreateAndSet() 
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

		strDefaultFont.LoadString(IDS_DEFAULT_FONT);
		lstrcpy(logFont.lfFaceName, strDefaultFont);
		if (!m_font.CreateFontIndirect(&logFont))
			TRACE0("Could Not create font for combo\n");
		else
			SetFont(&m_font, true);
	} else {
		m_font.Attach (::GetStockObject(SYSTEM_FONT));
		SetFont (&m_font, true);
	}
}
/*
///////////////////////////////////////////////////////////////////////////////
// Tooltips erlauben
int CViewComboBoxSec::OnToolHitTest(CPoint point, TOOLINFO* pTI) const
{
	if(m_bWndVisible) {
	// Called when SECToolBar::OnToolHitTest has decided we are the button
	// that has been hit. We fill in the TOOLINFO structure as required.
		if(NULL != pTI) {
			pTI->cbSize = sizeof(TOOLINFO);
			pTI->uFlags      = TTF_NOTBUTTON|TTF_CENTERTIP|TTF_ALWAYSTIP;
			pTI->hwnd        = m_pToolBar->m_hWnd;
			pTI->lpszText    = LPSTR_TEXTCALLBACK; // new char[20];
//			strcpy (pTI->lpszText, "Text"); 
			pTI->rect.left   = m_x;
			pTI->rect.right  = m_x + m_cx;
			pTI->rect.top    = m_y;
			pTI->rect.bottom = m_y + m_cy;
			pTI->uId         = m_nID+1;
		}
		return m_nID+1;

	} else
		return SECWndBtn::OnToolHitTest(point, pTI);
}

bool CViewComboBoxSec::OnToolTipText(UINT, NMHDR* pNMHDR, LRESULT* pResult)
{
	*pResult = 0;
	return true;    // message was handled
}
*/
///////////////////////////////////////////////////////////////////////////////
// ComboBox mit den Namen aller Ansichten füllen

// Callbackfunktion für das Füllen der Combobox
extern "C"
bool WINAPI FillToViewList (char *pPtr, bool, void *pCBox)
{
	if (pCBox && pPtr) {
		((CComboBox *)pCBox) -> AddString (pPtr);
		return true;
	}
	return false;
}

HRESULT CViewComboBoxSec::FillWithViews (void)
{
	ResetContent();		// alles rauswerfen

ENUMNOKEY ENK;

	ENK.eFcn = (ENUMNOKEYPROC)FillToViewList;
	ENK.ePtr = (CComboBox *)this;
	if (!DEX_EnumSights (ENK))
		return S_FALSE;

	return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// aktuelle Ansicht voreinstellen

HRESULT CViewComboBoxSec::ActivateActualView (LPCSTR pcView)
{
char cbActView[64];
UINT uiStr = 0L;

	if (NULL != pcView) {
		if ('\0' != *pcView) {
		// normale Ansicht aktiviert
		int iIndex = FindStringExact (-1, pcView);

			if (-1 != iIndex)
				SetCurSel (iIndex);
			m_fNoActView = false;
		} else {
		// temporäre Ansicht aktiviert
			uiStr = IDS_TEMPACTIVEVIEW;
			m_fNoActView = true;
		}
	} else if (NULL != DEX_GetActiveSight (cbActView)) {
		if ('\0' != cbActView[0]) {
		// normale Ansicht aktiviert
		int iIndex = FindStringExact (-1, cbActView);

			if (-1 != iIndex)
				SetCurSel (iIndex);
			m_fNoActView = false;
		} else {
		// temporäre Ansicht aktiviert
			uiStr = IDS_TEMPACTIVEVIEW;
			m_fNoActView = true;
		}
	} else {
		uiStr = IDS_NOACTIVEVIEW;
		m_fNoActView = true;
	}
	
// '<Kein Ansichtname>' && '<Keine aktive Ansicht>' aus Liste herauslöschen
	TRY {
		DeleteEntry (IDS_NOACTIVEVIEW);
		DeleteEntry (IDS_TEMPACTIVEVIEW);
	} CATCH (CMemoryException, e) {
		return E_OUTOFMEMORY;
	} END_CATCH

// Eintrag evtl. entsprechend setzen
	if (m_fNoActView) {
		TRY {
			ASSERT(0L != uiStr);	// muß gesetzt sein 

		CString str;

			str.LoadString (uiStr);
			AddString (str);

		int iIndex = FindStringExact (-1, str);

			if (-1 != iIndex)
				SetCurSel (iIndex);
			m_fNoActView = true;
		} CATCH (CMemoryException, e) {
			return E_OUTOFMEMORY;
		} END_CATCH
	}

	return NOERROR;
}

bool CViewComboBoxSec::DeleteEntry (UINT uiStr)
{
CString str;

	ATLTRY(str.LoadString (uiStr));

int iIndex = FindStringExact (-1, str);

	if (-1 != iIndex) {
		DeleteString (iIndex);
		return true;
	}
	return false;
}

/////////////////////////////////////////////////////////////////////////////
// CViewComboBoxSec message handlers

///////////////////////////////////////////////////////////////////////////////
// Fertig initialisiert

HRESULT CInstViewComboBox::FinalConstruct (void)
{
	m_dwCookie = 0L;
	m_pBack = NULL;

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Am TRiAS-ConnectionPoint ankoppeln

HRESULT CInstViewComboBox::SetSitePointers (
	ITriasXtensionSite *pSite, CViewComboBoxSec *pBack)
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

HRESULT CInstViewComboBox::DisConnectFromServer (void)
{
HRESULT hr = NOERROR;

	if (NULL != (IUnknown *)m_Cont && 0 != m_dwCookie) {
		hr = AtlUnadvise (m_Cont, IID_ITRiASNotificationSink, m_dwCookie);
		if (SUCCEEDED(hr)) {
			m_dwCookie = 0L;
			m_Cont.Assign (NULL);	// Release()
			m_pBack = NULL;
		}
	}
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// *** ITRiASNotificationSink specific functions ***

STDMETHODIMP CInstViewComboBox::ServerEvent (SERVEREVT se)
{
	switch (se) {
	case SERVEREVT_ServerToClose:	// das letzte vom Tage
		DisConnectFromServer();
		break;
	}
	return NOERROR;
}

STDMETHODIMP CInstViewComboBox::ProjectEvent (long hPr, PROJECTEVT pe, VARIANT)
{
HRESULT hr = NOERROR;

	ASSERT(NULL != m_pBack);

	switch (pe) {
	case PROJECTEVT_ProjectOpened:
		hr = m_pBack -> FillWithViews();			// mit Ansichten füllen
		if (S_OK == hr)
			hr = m_pBack -> ActivateActualView();	// aktuelle Ansicht voreinstellen
		break;

//	case PROJECTEVT_ProjectToClose:
	case PROJECTEVT_ProjectClosed:
		m_pBack -> ResetContent();		// alles rauswerfen
		break;
	}
	return NOERROR;
}

STDMETHODIMP CInstViewComboBox::GeoViewEvent (long hPr, GEOVIEWEVT ve, VARIANT vData)
{
	USES_CONVERSION;

LPSTR pView = NULL;

	if (vData.vt == VT_BSTR)
		pView = OLE2A(V_BSTR(&vData));

	ASSERT(NULL != m_pBack);

	switch (ve) {
	case GEOVIEWEVT_ViewSelected:
		m_pBack -> ActivateActualView (pView);
		break;

	case GEOVIEWEVT_ViewDeleted:
		{
			ASSERT(NULL != pView);

		int iCurrIndex = m_pBack -> GetCurSel();
		int iIndex = m_pBack -> FindStringExact (-1, pView);

			if (iIndex != -1)
				m_pBack -> DeleteString (iIndex);
			if (iIndex == iCurrIndex || 0 == m_pBack -> GetCount())
				m_pBack -> ActivateActualView (NULL);
		}
		break;

	case GEOVIEWEVT_ViewCreated:
		{
		// neue Ansicht zur Liste hinzufügen und selektieren
		int iIndex = m_pBack -> FindStringExact (-1, pView);

			if (CB_ERR == iIndex)	// wirklich neue Ansicht
				m_pBack -> AddString (pView);

			if (0 == m_pBack -> GetCount())
				m_pBack -> ActivateActualView (pView);
		}
		break;
	}
	return NOERROR;
}

STDMETHODIMP CInstViewComboBox::GeoClassEvent (long hPr, GEOCLASSEVT ce, long ulIdent)
{
	return NOERROR;
}

STDMETHODIMP CInstViewComboBox::GeoObjectEvent (long hPr, GEOOBJECTEVT oe, long lONr)
{
	return NOERROR;
}

STDMETHODIMP CInstViewComboBox::GeoFeatureEvent (long hPr, GEOFEATUREEVT fe, long ulMCode)
{
	return NOERROR;
}

STDMETHODIMP CInstViewComboBox::GeoRelationEvent (long hPr, GEORELATIONEVT re, long ulRCode)
{
	return NOERROR;
}

STDMETHODIMP CInstViewComboBox::ObjectWindowEvent (OBJWNDEVT oe, long hORWnd)
{
	return NOERROR;
}

