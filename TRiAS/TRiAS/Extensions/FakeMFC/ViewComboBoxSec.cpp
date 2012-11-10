// ViewComboBoxSec.cpp : Implementation of the CInstViewComboBox

#include "fakemfcp.hxx"
#include "fakemfc.h"

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

BEGIN_MESSAGE_MAP(CViewComboBoxSec, CFlatComboBox)
	//{{AFX_MSG_MAP(CViewComboBoxSec)
	//}}AFX_MSG_MAP
//	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, OnToolTipText)
//	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, OnToolTipText)
END_MESSAGE_MAP()


BOOL CViewComboBoxSec::CreateWnd (CWnd* pParentWnd, DWORD dwStyle, CRect& rect, int nID)
{
	dwStyle |= WS_DISABLED;
	if (!CFlatComboBox::CreateWnd (pParentWnd, dwStyle, rect, nID))
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

		VERIFY(strDefaultFont.LoadString(IDS_DEFAULT_FONT));
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
BOOL GetRelatedDataSourceName (LPCSTR pcView, CString &rstrViewWithDS)
{
char cbBuffer[_MAX_PATH] = { '\0' };
RELATEDDATASOURCENAME RDSN;

	INITSTRUCT(RDSN, RELATEDDATASOURCENAME);
	RDSN.pcTargetName = const_cast<const char *>(pcView);
	RDSN.pDataSourceName = cbBuffer;
	RDSN.iLen = sizeof(cbBuffer);
	if (S_OK == DEX_GetRelatedDataSourceName(RDSN) && '\0' != cbBuffer[0]) {
		rstrViewWithDS.Format ("%s (%s)", pcView, cbBuffer);
		return TRUE;
	}
	return FALSE;
}

// Callbackfunktion für das Füllen der Combobox
extern "C"
BOOL WINAPI FillToViewList (char *pPtr, BOOL, void *pCBox)
{
	if (pCBox && pPtr) {
	CString strTempView;

		strTempView.LoadString (IDS_TEMPACTIVEVIEW);
		if (strcmp (pPtr, strTempView)) {
		CString strView;
		int iNewIndex = CB_ERR;

			if (GetRelatedDataSourceName (pPtr, strView))
				iNewIndex = ((CComboBox *)pCBox) -> AddString (strView);
			else
				iNewIndex = ((CComboBox *)pCBox) -> AddString (pPtr);

		// Anzahl der Zeichen der OriginalAnsicht als zusätzliche Daten ablegen
			if (CB_ERR != iNewIndex)
				((CComboBox *)pCBox) -> SetItemData (iNewIndex, strlen (pPtr));
		}
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
char cbActView[MAXVIEWNAMESIZE+1];
UINT uiStr = 0L;

	if (NULL != pcView) {
	CString strTempView;

		strTempView.LoadString (IDS_TEMPACTIVEVIEW);
		if ('\0' != *pcView && strcmp (pcView, strTempView)) {
		// normale Ansicht aktiviert
		int iIndex = FindViewName (-1, pcView);

			if (-1 != iIndex)
				SetCurSel (iIndex);
			m_fNoActView = false;
		} 
		else {
		// temporäre Ansicht aktiviert
			uiStr = IDS_TEMPACTIVEVIEW;
			m_fNoActView = true;
		}
	} 
	else if (NULL != DEX_GetActiveSight (cbActView)) {
		if ('\0' != cbActView[0]) {
		// normale Ansicht aktiviert
		int iIndex = FindViewName (-1, cbActView);

			if (-1 != iIndex)
				SetCurSel (iIndex);
			m_fNoActView = false;
		} else {
		// temporäre Ansicht aktiviert
			uiStr = IDS_TEMPACTIVEVIEW;
			m_fNoActView = true;
		}
	} 
	else {
		uiStr = IDS_NOACTIVEVIEW;
		m_fNoActView = true;
	}
	
// '<Kein Ansichtname>' && '<Keine aktive Ansicht>' aus Liste herauslöschen
	TRY {
		DeleteEntry (IDS_NOACTIVEVIEW);
		DeleteEntry (IDS_TEMPACTIVEVIEW);
	} 
	CATCH (CMemoryException, e) {
		return E_OUTOFMEMORY;
	} END_CATCH

// Eintrag evtl. entsprechend setzen
	if (m_fNoActView) {
		TRY {
			ASSERT(0L != uiStr);	// muß gesetzt sein 

		CString str;

			VERIFY(str.LoadString (uiStr));
			AddString (str);

		int iIndex = FindViewName (-1, str);

			if (-1 != iIndex) {
				SetCurSel (iIndex);
				SetItemData (iIndex, str.GetLength());
			}

		} CATCH (CMemoryException, e) {
			m_fNoActView = false;
			return E_OUTOFMEMORY;
		} END_CATCH
	}
	return NOERROR;
}

bool CViewComboBoxSec::DeleteEntry (UINT uiStr)
{
CString str;

	VERIFY(str.LoadString (uiStr));

int iIndex = FindViewName (-1, str);

	if (-1 != iIndex) {
		DeleteString (iIndex);
		return true;
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////
// Zuerst Ansicht direkt suchen, dann, wenn nicht gefunden mit evtl. angehängtem 
// DataSourceNamen
int CViewComboBoxSec::FindViewName (int iStartIndex, LPCSTR pcViewName) const
{
int iIndex = FindStringExact (iStartIndex, pcViewName);

	if (CB_ERR == iIndex) {
	// nicht wiedergefunden, mit Datenquelle nochmal versuchen
	CString strViewWithDS;

		if (GetRelatedDataSourceName (pcViewName, strViewWithDS))
			iIndex = FindStringExact (iStartIndex, strViewWithDS);
	}
	if (CB_ERR == iIndex) {
	// immer noch nichts gefunden
	int iIndexT = FindString (iStartIndex, pcViewName);

		if (CB_ERR != iIndexT) {
		// evtl. doch noch gefunden (in ComboBox ist der Name noch mit Datenquelle drin)
		CString strEntry, strT;
		int iLen = strlen(pcViewName);

			GetLBText (iIndexT, strEntry);
			strT = strEntry.Right (strEntry.GetLength() - iLen);
			if (strEntry.Left(iLen) == pcViewName &&
				strT[0] == ' ' && strT[1] == '(' && strT[strT.GetLength()-1] == ')')
			{
				iIndex = iIndexT;		// scheint eine Datenquelle zu sein
			}
		}
	}
	return iIndex;
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
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	switch (se) {
	case SERVEREVT_ServerToClose:	// das letzte vom Tage
		DisConnectFromServer();
		break;
	}
	return NOERROR;
}

STDMETHODIMP CInstViewComboBox::ProjectEvent (long hPr, PROJECTEVT pe, VARIANT)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

HRESULT hr = NOERROR;

	ASSERT(NULL != m_pBack);

	switch (pe) {
	case PROJECTEVT_ProjectOpened:
		hr = m_pBack -> FillWithViews();			// mit Ansichten füllen
		if (SUCCEEDED(hr))
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
	AFX_MANAGE_STATE(AfxGetAppModuleState())
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
		int iIndex = m_pBack -> FindViewName (-1, pView);

			if (iIndex != -1)
				m_pBack -> DeleteString (iIndex);
			if (iIndex == iCurrIndex || 0 == m_pBack -> GetCount())
				m_pBack -> ActivateActualView (NULL);
		}
		break;

	case GEOVIEWEVT_ViewCreated:
		{
		// neue Ansicht zur Liste hinzufügen und selektieren
		int iIndex = m_pBack -> FindViewName (-1, pView);

			if (CB_ERR == iIndex) {	// wirklich neue Ansicht
			CString strView;

				if (GetRelatedDataSourceName (pView, strView))
					iIndex = m_pBack -> AddString (strView);
				else
					iIndex = m_pBack -> AddString (pView);

			// Anzahl der Zeichen der OriginalAnsicht als zusätzliche Daten ablegen
				if (CB_ERR != iIndex)
					m_pBack -> SetItemData (iIndex, strlen (pView));

			} else {
			// ggf. Ansichtsnamen austauschen
				m_pBack -> DeleteString (iIndex);
				m_pBack -> InsertString (iIndex, pView);
				m_pBack -> SetItemData (iIndex, strlen (pView));
			}
			if (0 == m_pBack -> GetCount())
				m_pBack -> ActivateActualView (pView);
		}
		break;

	case GEOVIEWEVT_ReReadAll:		// alles neu einlesen
		{
		HRESULT hr = m_pBack -> FillWithViews();			// mit Ansichten füllen

			if (SUCCEEDED(hr))
				m_pBack -> ActivateActualView();	// aktuelle Ansicht voreinstellen
		}
		break;
	}
	return NOERROR;
}

STDMETHODIMP CInstViewComboBox::GeoClassEvent (long hPr, GEOCLASSEVT ce, long ulIdent)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())
	return NOERROR;
}

STDMETHODIMP CInstViewComboBox::GeoObjectEvent (long hPr, GEOOBJECTEVT oe, long lONr)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())
	return NOERROR;
}

STDMETHODIMP CInstViewComboBox::GeoFeatureEvent (long hPr, GEOFEATUREEVT fe, long ulMCode)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())
	return NOERROR;
}

STDMETHODIMP CInstViewComboBox::GeoRelationEvent (long hPr, GEORELATIONEVT re, long ulRCode)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())
	return NOERROR;
}

STDMETHODIMP CInstViewComboBox::ObjectWindowEvent (OBJWNDEVT oe, long hORWnd)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())
	return NOERROR;
}

