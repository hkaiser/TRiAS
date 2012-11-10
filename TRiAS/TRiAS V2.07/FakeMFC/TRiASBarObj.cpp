// TRiASBarObj.cpp : Implementation of CTRiASToolBarObj

#include "fakemfcp.hxx"
#include "fakemfc.h"

#include <xtensnn.h>

#include <itoolbar.h>
#include <toolguid.h>
#include <dirisole.h>
#include <oleguid.h>
#include <itriasap.h>

#include "Wrapper.h"		// SmartInterfaces

#include "mainfrm.h"
#include "TRiASToolBar.h"
#include "TRiASBarObj.h"
#include "TRiASCmdUI.h"
#include "DispUIOwner.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface (PersistStreamInit);

///////////////////////////////////////////////////////////////////////////////
// customized IMPLEMENT_DYNCREATE(CTRiASToolBarObj, CObject)
CObject* PASCAL CTRiASToolBarObj::CreateObject() 
{
CComObject<CTRiASToolBarObj> *pTBObj = NULL;
HRESULT hr = CComObject<CTRiASToolBarObj>::CreateInstance (&pTBObj);

	if (FAILED(hr)) return NULL;

	{
	WPersistStreamInit Init (pTBObj);

		if (FAILED(Init -> InitNew()))
			return NULL;

		pTBObj -> AddRef();		// RefCnt ist jetzt 1 (2)
	}

	return pTBObj->GetToolBar();
}

IMPLEMENT_RUNTIMECLASS(CTRiASToolBarObj, CObject, 0xFFFF, CTRiASToolBarObj::CreateObject)

///////////////////////////////////////////////////////////////////////////////
// zusätzlich benötigte SmartInterfaces
DefineSmartInterface(EnumConnections);
DefineSmartInterface(TRiASBarInstallControl);
DefineSmartInterface(GetTRiASApplication);

DefineSmartInterface(Dispatch);

///////////////////////////////////////////////////////////////////////////////
// Basisklassen fetig initialisieren
HRESULT CTRiASToolBarObj::FinalConstruct (void)
{
	return S_OK;
}

CTRiASToolBarObj::~CTRiASToolBarObj(void)
{ 
CTRiASToolBar *pTBZombie = m_pToolBar;

	DELETE(m_pToolBar);				// jetzt Toolbar verabschieden

#if defined(_USE_SEC_CLASSES)
	((CMainFrame *)AfxGetMainWnd()) -> ResetInvalidDockbars(pTBZombie);
#endif // _USE_SEC_CLASSES
}

/////////////////////////////////////////////////////////////////////////////
// *** ITRiASBar specific functions ***
STDMETHODIMP CTRiASToolBarObj::GetBarStyle (
	LPSTR pName, ULONG ulLen, ULONG *pulWritten/*=NULL*/, 
	DWORD *pdwStyle/*=NULL*/, DWORD *pdwStyleEx/*=NULL*/)
{
	ASSERT(NULL != m_pToolBar);
	return m_pToolBar -> GetBarStyleEx (pName, ulLen, pulWritten, pdwStyle, pdwStyleEx);
}

STDMETHODIMP CTRiASToolBarObj::SetBarStyle (LPCSTR pcName, DWORD dwStyle, DWORD dwStyleEx, bool fDelay)
{
	ASSERT(NULL != m_pToolBar);
	return m_pToolBar -> SetBarStyleEx (pcName, dwStyle, dwStyleEx, fDelay);
}

STDMETHODIMP CTRiASToolBarObj::FloatBar (POINT pt, DWORD dwStyle)
{
	ASSERT(NULL != m_pToolBar);
	return m_pToolBar -> FloatBar (pt, dwStyle);
}

STDMETHODIMP CTRiASToolBarObj::DockBar (UINT uiWhere, LPCRECT pcRc/*=NULL*/)
{
	ASSERT(NULL != m_pToolBar);
	return m_pToolBar -> DockBar (uiWhere, pcRc);
}

STDMETHODIMP CTRiASToolBarObj::IsFloating (void)
{
	ASSERT(NULL != m_pToolBar);
	return m_pToolBar -> IsFloating();
}

STDMETHODIMP CTRiASToolBarObj::GetBarID (UINT *puiID)
{
	ASSERT(NULL != m_pToolBar);
	return m_pToolBar -> GetBarID (puiID);
}

STDMETHODIMP CTRiASToolBarObj::GetBarHandle (HWND *phWnd)
{
	ASSERT(NULL != m_pToolBar);
	return m_pToolBar -> GetBarHandle (phWnd);
}

STDMETHODIMP CTRiASToolBarObj::OnCmdMsg (UINT uiID, int nCode, void *pExtra1, void *pExtra2)
{
	ASSERT(NULL != m_pToolBar);
	return m_pToolBar -> OnCmdMessage (uiID, nCode, pExtra1, (AFX_CMDHANDLERINFO *)pExtra2);
}

STDMETHODIMP CTRiASToolBarObj::get_CtrlID (int *piCtrlID)
{
	ASSERT(NULL != m_pToolBar);

UINT uiID = 0;
HRESULT hr = m_pToolBar -> GetBarID (&uiID);

	if (SUCCEEDED(hr))
		*piCtrlID = (int)uiID;
	return S_OK;
}

STDMETHODIMP CTRiASToolBarObj::put_CtrlID (THIS_ int iCtrlID)
{
	ASSERT(NULL != m_pToolBar);
	return m_pToolBar -> SetBarID (iCtrlID);
}

// *** ITRiASToolBar specific functions ***
STDMETHODIMP CTRiASToolBarObj::GetButtonStyle (int iIndex, UINT *puiStyle)
{
	ASSERT(NULL != m_pToolBar);
	return m_pToolBar -> GetButtonStyle (iIndex, puiStyle);
}

STDMETHODIMP CTRiASToolBarObj::SetButtonStyle (int iIndex, UINT uiStyle)
{
	ASSERT(NULL != m_pToolBar);
	return m_pToolBar -> SetButtonStyle (iIndex, uiStyle);
}

STDMETHODIMP CTRiASToolBarObj::AddBitmap (HINSTANCE hInst, UINT uiRsc, int iNumButtons, int *piOffset/*=NULL*/)
{
	ASSERT(NULL != m_pToolBar);
	return m_pToolBar -> AddBitmap (hInst, uiRsc, iNumButtons, piOffset);
}

STDMETHODIMP CTRiASToolBarObj::AddButtons (const TBBUTTON *pBttns, int iCnt, ITRiASUIOwner *pIOwner)
{
	ASSERT(NULL != m_pToolBar);

HRESULT hr = OnRequestAddButtons (-1, pBttns, iCnt);

	if (S_OK != hr) return hr;

	hr = m_pToolBar -> AddButtons (pBttns, iCnt, pIOwner);
	OnAddedButtons (-1, pBttns, iCnt);

return hr;
}

STDMETHODIMP CTRiASToolBarObj::InsertButton (int iIndex, const TBBUTTON *pBttn, ITRiASUIOwner *pIOwner)
{
	ASSERT(NULL != m_pToolBar);

HRESULT hr = OnRequestAddButtons (iIndex, pBttn, 1);

	if (S_OK != hr) return hr;

	hr = m_pToolBar -> InsertButton (iIndex, pBttn, pIOwner);
	OnAddedButtons (iIndex, pBttn, 1);

return hr;
}

STDMETHODIMP CTRiASToolBarObj::DeleteItem (int iIndex)
{
	ASSERT(NULL != m_pToolBar);

HRESULT hr = NOERROR;
UINT uiID = 0;
UINT uiStyle = 0;

	try {
		hr = m_pToolBar -> GetButtonStyle (iIndex, &uiStyle, &uiID);
		if (FAILED(hr)) _com_issue_error(hr);

	// nachfragen, ob wirklich gelöscht werden soll
		hr = OnRequestDeleteItem (uiID, DWORD(uiStyle));
		if (S_OK != hr) _com_issue_error(hr);

	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

// nur entfernen, wenn kein Fehler und keiner was dagegen hat
	hr = m_pToolBar -> DeleteItem (iIndex);
	if (SUCCEEDED(hr)) OnDeletedItem (uiID);

return hr;
}

STDMETHODIMP CTRiASToolBarObj::CommandToIndex (UINT uiID, int *piIndex)
{
	ASSERT(NULL != m_pToolBar);
	return m_pToolBar -> CommandToIndex (uiID, piIndex);
}

STDMETHODIMP CTRiASToolBarObj::GetItemRect (int iIndex, LPRECT pRc)
{
	ASSERT(NULL != m_pToolBar);
	return m_pToolBar -> GetItemRect (iIndex, pRc);
}

STDMETHODIMP CTRiASToolBarObj::GetButton (int iIndex, TBBUTTON *pBttn, ITRiASUIOwner **ppIOwner) 
{
	ASSERT(NULL != m_pToolBar);
	return m_pToolBar -> GetButtonEx (iIndex, pBttn, ppIOwner);
}

///////////////////////////////////////////////////////////////////////////////
// *** IPersist methods
STDMETHODIMP CTRiASToolBarObj::GetClassID (CLSID *pClassID)
{
	if (NULL == pClassID) return E_POINTER;

	*pClassID = CLSID_TRiASToolBar;
	return NOERROR;
}

// *** IPersistStreamInit functions
STDMETHODIMP CTRiASToolBarObj::IsDirty (void)
{
	return E_NOTIMPL;
}

STDMETHODIMP CTRiASToolBarObj::Load (LPSTREAM pStrm)
{
	return E_NOTIMPL;
}

STDMETHODIMP CTRiASToolBarObj::Save (LPSTREAM pStrm, BOOL fClearDirty)
{
	return E_NOTIMPL;
}

STDMETHODIMP CTRiASToolBarObj::GetSizeMax (ULARGE_INTEGER * pcbSize)
{
	return E_NOTIMPL;
}

STDMETHODIMP CTRiASToolBarObj::InitNew (void)
{
	ASSERT(NULL == m_pToolBar);

	TRY { 
		m_pToolBar = new CTRiASToolBar((ITRiASToolBar *)this);
	} CATCH (CMemoryException, e) {
		return E_OUTOFMEMORY;
	} END_CATCH

	return m_pToolBar -> InitNew();
}

///////////////////////////////////////////////////////////////////////////////
// Connections bedienen
HRESULT CTRiASToolBarObj::OnRequestAddButtons (int iIndex, const TBBUTTON *pBttn, int iCnt) 
{
// Enumerator besorgen
WEnumConnections Conns;
HRESULT hr = m_cpTRiASBarNotifySink.EnumConnections (Conns.ppi());

	if (FAILED(hr)) return hr;

// alle registrierten Connections abarbeiten
	try {
	CONNECTDATA cd;

		for (Conns -> Reset(); 
			 S_OK == Conns -> Next (1, &cd, NULL); /**/) 
		{
		WTRiASBarNotifySink Sink(cd.pUnk);		// throws HRESULT

			cd.pUnk -> Release();		// Connection freigeben
			hr = Sink -> OnRequestAddButtons (this, iIndex, pBttn, iCnt);
			if (S_OK != hr)
				return hr;		// nicht zulassen
		}
	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

return NOERROR;
}

HRESULT CTRiASToolBarObj::OnAddedButtons (int iIndex, const TBBUTTON *pBttn, int iCnt) 
{
// Enumerator besorgen
WEnumConnections Conns;
HRESULT hr = m_cpTRiASBarNotifySink.EnumConnections (Conns.ppi());

	if (FAILED(hr)) return hr;

// alle registrierten Connections abarbeiten
	try {
	CONNECTDATA cd;

		for (Conns -> Reset(); 
			 S_OK == Conns -> Next (1, &cd, NULL); /**/) 
		{
		WTRiASBarNotifySink Sink(cd.pUnk);		// throws HRESULT

			cd.pUnk -> Release();		// Connection freigeben
			Sink -> OnAddedButtons (this, iIndex, pBttn, iCnt);
		// evtl. Fehler ignorieren
		}
	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

return NOERROR;
}

HRESULT CTRiASToolBarObj::OnRequestDeleteItem (UINT uiCtrlID, DWORD dwStyle) 
{
// Enumerator besorgen
WEnumConnections Conns;
HRESULT hr = m_cpTRiASBarNotifySink.EnumConnections (Conns.ppi());

	if (FAILED(hr)) return hr;

// alle registrierten Connections abarbeiten
	try {
	CONNECTDATA cd;

		for (Conns -> Reset(); 
			 S_OK == Conns -> Next (1, &cd, NULL); /**/) 
		{
		WTRiASBarNotifySink Sink(cd.pUnk);		// throws HRESULT

			cd.pUnk -> Release();		// Connection freigeben
			hr = Sink -> OnRequestDeleteItem (this, uiCtrlID, dwStyle);
			if (S_OK != hr)
				return hr;		// nicht zulassen
		}
	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

return NOERROR;
}

HRESULT CTRiASToolBarObj::OnDeletedItem (UINT uiCtrlID) 
{
// Enumerator besorgen
WEnumConnections Conns;
HRESULT hr = m_cpTRiASBarNotifySink.EnumConnections (Conns.ppi());

	if (FAILED(hr)) return hr;

// alle registrierten Connections abarbeiten
	try {
	CONNECTDATA cd;

		for (Conns -> Reset(); 
			 S_OK == Conns -> Next (1, &cd, NULL); /**/) 
		{
		WTRiASBarNotifySink Sink (cd.pUnk);		// throws HRESULT

			cd.pUnk -> Release();		// Connection freigeben
			Sink -> OnDeletedItem (this, uiCtrlID);
		// evtl. Fehler ignorieren
		}

		m_mapBttns.erase (uiCtrlID);		// evtl. aus Liste herausnehmen

	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// _ITRiASBaseClass methods
STDMETHODIMP CTRiASToolBarObj::get_Properties (DTRiASProperties **ppIProps)
{
	ATLTRACENOTIMPL("CTRiASToolBarObj::get_Properties");
}

STDMETHODIMP CTRiASToolBarObj::CreateProperty (VARIANT vName, VARIANT vType, VARIANT vValue, DTRiASProperty **ppIProp)
{
	ATLTRACENOTIMPL("CTRiASToolBarObj::CreateProperty ");
}

STDMETHODIMP CTRiASToolBarObj::get_isA (long *plRTTI)
{
	if (NULL == plRTTI) return E_POINTER;

	*plRTTI = RTTI_ToolBar;
	return NOERROR;
}

STDMETHODIMP CTRiASToolBarObj::get_Parent (IDispatch **ppIBase)
{
	if (NULL != (IUnknown *)m_Parent) 
		return m_Parent -> QueryInterface (IID_IDispatch, (LPVOID *)ppIBase); 
	return E_UNEXPECTED;
}

STDMETHODIMP CTRiASToolBarObj::put_Parent (IDispatch *pIBase)
{
	m_Parent = pIBase; 
	return NOERROR;
}

STDMETHODIMP CTRiASToolBarObj::get_Application (IDispatch **ppIApp)
{
	if (NULL != (IUnknown *)m_App) 
		return m_App -> QueryInterface (IID_IDispatch, (LPVOID *)ppIApp); 
	return E_UNEXPECTED;
}

STDMETHODIMP CTRiASToolBarObj::put_Application (IDispatch *pIApp)
{
	m_App = pIApp; 
	return NOERROR;
}

// IControlToolBar methods
STDMETHODIMP CTRiASToolBarObj::get_Name (BSTR *pbstrName)
{
	USES_CONVERSION;
	if (NULL == pbstrName) return E_POINTER;

	ASSERT(NULL != m_pToolBar);

char cbBuffer[_MAX_PATH];
HRESULT hr = m_pToolBar -> GetBarStyleEx (cbBuffer, sizeof(cbBuffer), NULL, NULL, NULL);

	if (FAILED(hr)) return hr;

	*pbstrName = SysAllocString (A2OLE(cbBuffer));
	return NULL != *pbstrName ? NOERROR : E_OUTOFMEMORY;
}

STDMETHODIMP CTRiASToolBarObj::put_Name (BSTR bstrName)
{
	USES_CONVERSION;
	ASSERT(NULL != m_pToolBar);

DWORD dwStyle = 0L;
DWORD dwStyleEx = 0L;
HRESULT hr = m_pToolBar -> GetBarStyleEx (NULL, 0, NULL, &dwStyle, &dwStyleEx);

	if (SUCCEEDED(hr)) 
		hr = m_pToolBar -> SetBarStyleEx (OLE2A(bstrName), dwStyle, dwStyleEx, false);

return hr;
}

STDMETHODIMP CTRiASToolBarObj::get_Width (long *plWidth)
{
	if (NULL == plWidth) 
		return E_POINTER;
	
	*plWidth = MoveSize (MOVESIZEACTION_GETWIDTH);
	return NOERROR;
}

STDMETHODIMP CTRiASToolBarObj::put_Width (long lWidth)
{
	MoveSize (MOVESIZEACTION_WIDTH, 0, 0, lWidth);
	return NOERROR;
}

STDMETHODIMP CTRiASToolBarObj::get_Height (long *plHeight)
{
	if (NULL == plHeight) 
		return E_POINTER;
	
	*plHeight = MoveSize (MOVESIZEACTION_GETHEIGHT);
	return NOERROR;
}

STDMETHODIMP CTRiASToolBarObj::put_Height (long lHeight)
{
	return E_NOTIMPL;
}

STDMETHODIMP CTRiASToolBarObj::get_Left (long *plLeft)
{
	if (NULL == plLeft) 
		return E_POINTER;
	
	*plLeft = MoveSize (MOVESIZEACTION_GETLEFT);
	return NOERROR;
}

STDMETHODIMP CTRiASToolBarObj::put_Left (long lLeft)
{
	MoveSize (MOVESIZEACTION_LEFT, lLeft);
	return NOERROR;
}

STDMETHODIMP CTRiASToolBarObj::get_Top (long *plTop)
{
	if (NULL == plTop) return E_POINTER;

	*plTop = MoveSize (MOVESIZEACTION_GETTOP);
	return NOERROR;
}

STDMETHODIMP CTRiASToolBarObj::put_Top (long lTop)
{
	MoveSize (MOVESIZEACTION_TOP, 0, lTop);
	return NOERROR;
}

/*
 * CTriasAppPro::MoveSize
 *
 * Purpose:
 *  Helper function for the Left, Top, Width, and Height properties
 *  that centralizes calls to GetWindowRect and SetWindowPos,
 *  reducing overall code somewhat.
 *
 * Parameters:
 *  iAction         MOVESIZEACTION enum value to indicate what
 *                  type of moving/sizing to perform
 *  x, y            long position coordinates;  x is only meaningful
 *                  with MOVESIZEACTION_LEFT, y only with _TOP
 *  cx, cy          long extents;  cx is only meaningful
 *                  with MOVESIZEACTION_WIDTH, cy only with _HEIGHT
 *
 * Return Value:
 *  long            The current x, y, cx, or cy value depending on
 *                  iAction being _GETLEFT, _GETTOP, _GETWIDTH, or
 *                  _GETHEIGHT.
 */

long CTRiASToolBarObj::MoveSize (CTRiASToolBarObj::MOVESIZEACTION iAction, long x, long y, long cx, long cy)
{
RECT rc;
long x1, y1, cx1, cy1;
UINT uFlags;
HWND hWnd = m_pToolBar -> GetSafeHwnd();

	::GetWindowRect (hWnd, &rc);

CPoint pt1(rc.left, rc.top), pt2 (rc.right, rc.bottom);

	::ScreenToClient (GetParent(hWnd), &pt1);
	::ScreenToClient (GetParent(hWnd), &pt2);

//By default we'll do nothing
	x1 = pt1.x;
	y1 = pt1.y;
	cx1 = pt2.x-pt1.x;
	cy1 = pt2.y-pt1.y;
	uFlags = 0L;

	switch (iAction) {
	/*
	 * Each individual property modifies the appropriate
	 * variable x1, y1, cx1, cy1, as well as uFlags to set
	 * up SetWindowPos call.
	 */
	case MOVESIZEACTION_LEFT:
		x1 = x;
		uFlags = SWP_NOSIZE;
		break;

	case MOVESIZEACTION_TOP:
		y1 = y;
		uFlags = SWP_NOSIZE;
		break;

	case MOVESIZEACTION_WIDTH:
		m_pToolBar -> m_nMRUWidth = cx;
		cx1 = cx;
		uFlags = SWP_NOMOVE;
		break;

	case MOVESIZEACTION_HEIGHT:
		cy1 = cy;
		uFlags = SWP_NOMOVE;
		break;

	case MOVESIZEACTION_GETLEFT:
		return x1;

	case MOVESIZEACTION_GETTOP:
		return y1;

	case MOVESIZEACTION_GETWIDTH:
		return cx1;

	case MOVESIZEACTION_GETHEIGHT:
		return cy1;

	default:
		return 0;
	}

// We only get here on propety changes
	SetWindowPos (hWnd, NULL, (int)x1, (int)y1, (int)cx1, (int)cy1,
				  SWP_NOZORDER | SWP_NOACTIVATE | uFlags);

	((CFrameWnd *)AfxGetMainWnd()) -> RecalcLayout();
	return 0;	// Irrelevant for property changes.
}

STDMETHODIMP CTRiASToolBarObj::get_DockState (DOCKSTATE *prgState)
{
	if (NULL == prgState) return E_POINTER;
	ASSERT(NULL != m_pToolBar);

DWORD dwStyle = 0L;
DWORD dwStyleEx = 0L;
HRESULT hr = m_pToolBar -> GetBarStyleEx (NULL, 0, NULL, &dwStyle, &dwStyleEx);

	if (FAILED(hr)) return hr;
	if (dwStyle & CBRS_ALIGN_TOP)
		*prgState = DOCKSTATE_DOCKEDTOP;
	else if (dwStyle & CBRS_ALIGN_BOTTOM)
		*prgState = DOCKSTATE_DOCKEDBOTTOM;
	else if (dwStyle & CBRS_ALIGN_LEFT)
		*prgState = DOCKSTATE_DOCKEDLEFT;
	else if (dwStyle & CBRS_ALIGN_RIGHT)
		*prgState = DOCKSTATE_DOCKEDRIGHT;
	else 
		*prgState = DOCKSTATE_FLOATING;

return NOERROR;
}

STDMETHODIMP CTRiASToolBarObj::put_DockState (DOCKSTATE rgState)
{
	ASSERT(NULL != m_pToolBar);

	switch (rgState) {
	case DOCKSTATE_DOCKEDTOP:
		m_pToolBar -> DockBar (AFX_IDW_DOCKBAR_TOP, NULL);
		break;

	case DOCKSTATE_DOCKEDLEFT:
		m_pToolBar -> DockBar (AFX_IDW_DOCKBAR_LEFT, NULL);
		break;

	case DOCKSTATE_DOCKEDRIGHT:
		m_pToolBar -> DockBar (AFX_IDW_DOCKBAR_RIGHT, NULL);
		break;

	case DOCKSTATE_DOCKEDBOTTOM:
		m_pToolBar -> DockBar (AFX_IDW_DOCKBAR_BOTTOM, NULL);
		break;

	case DOCKSTATE_FLOATING:
		{
		long lLeft = MoveSize (MOVESIZEACTION_GETLEFT);
		long lTop = MoveSize (MOVESIZEACTION_GETTOP);

			m_pToolBar -> FloatBar (CPoint(lLeft, lTop), CBRS_ALIGN_TOP);
		}
		break;

	default:
		return E_INVALIDARG;
	}

return NOERROR;
}

STDMETHODIMP CTRiASToolBarObj::get_Style (long *pdwStyle)
{
	ASSERT(NULL != m_pToolBar);
	return m_pToolBar -> GetBarStyleEx (NULL, 0, NULL, (DWORD *)pdwStyle, NULL);
}

STDMETHODIMP CTRiASToolBarObj::put_Style (long dwStyle)
{
	ASSERT(NULL != m_pToolBar);

char cbName[_MAX_PATH];
DWORD dwStyleEx = 0L;

	if (SUCCEEDED(m_pToolBar -> GetBarStyleEx (cbName, _MAX_PATH, NULL, NULL, &dwStyleEx)))
		return m_pToolBar -> SetBarStyleEx (cbName, dwStyle, dwStyleEx, false);

return E_FAIL;
}

STDMETHODIMP CTRiASToolBarObj::get_StyleEx (long *pdwStyleEx)
{
	ASSERT(NULL != m_pToolBar);
	return m_pToolBar -> GetBarStyleEx (NULL, 0, NULL, NULL, (DWORD *)pdwStyleEx);
}

STDMETHODIMP CTRiASToolBarObj::put_StyleEx (long dwStyleEx)
{
	ASSERT(NULL != m_pToolBar);

char cbName[_MAX_PATH];
DWORD dwStyle = 0;

	if (SUCCEEDED(m_pToolBar -> GetBarStyleEx (cbName, _MAX_PATH, NULL, &dwStyle, NULL)))
		return m_pToolBar -> SetBarStyleEx (cbName, dwStyle, dwStyleEx, false);

return E_FAIL;
}

STDMETHODIMP CTRiASToolBarObj::get_Visible (VARIANT_BOOL *pfVisible)
{
	ASSERT(NULL != m_pToolBar);
	if (NULL == pfVisible) return E_POINTER;

DWORD dwStyle = 0L;
HRESULT hr = m_pToolBar -> GetBarStyleEx (NULL, 0, NULL, &dwStyle, NULL);

	if (FAILED(hr)) return hr;

	*pfVisible = (dwStyle & WS_VISIBLE) ? (-1) : (0);
	return NOERROR;
}

STDMETHODIMP CTRiASToolBarObj::put_Visible (VARIANT_BOOL fVisible)
{
	ASSERT(NULL != m_pToolBar);

DWORD dwStyle = 0L;
DWORD dwStyleEx = 0L;
HRESULT hr = m_pToolBar -> GetBarStyleEx (NULL, 0, NULL, &dwStyle, &dwStyleEx);

	if (FAILED(hr)) return hr;

bool fNewVisible = fVisible ? true : false;
bool fOldVisible = (dwStyle & WS_VISIBLE) ? true : false;

	if (fOldVisible ^ fNewVisible) {
		if (fNewVisible)
			dwStyle |= WS_VISIBLE;
		else
			dwStyle &= ~WS_VISIBLE;
		hr = m_pToolBar -> SetBarStyleEx (NULL, dwStyle, dwStyleEx, false);
	}

return hr;
}

STDMETHODIMP CTRiASToolBarObj::ToolBarButtons (DControlToolBarButtons **pIBttns)
{
	return E_NOTIMPL;
}

STDMETHODIMP CTRiASToolBarObj::Reset (void)
{
	ASSERT(NULL != m_pToolBar);
	return m_pToolBar -> Reset ();
}

STDMETHODIMP CTRiASToolBarObj::InsertButton (
	int iIndex, DControlToolBarButton *pIBttn, DToolBarUIOwner *pIUIOwner, 
	IUnknown *pIInstCtrl)
{
HRESULT hr = NOERROR;

	try {
	WTRiASBarInstallControl Inst (pIInstCtrl);		// throws hr
//	WDControlToolBarButton Bttn (pIBttn);			// throws hr
	TBBUTTON tb;

	// Eigenschaften besorgen
	int iCmdID = 0;
	BUTTONSTATE rgState = BUTTONSTATE_ENABLED;
	BUTTONSTYLE rgStyle = BUTTONSTYLE_BUTTON;

		THROW_FAILED_HRESULT(pIBttn -> get_CmdID (&iCmdID));
		THROW_FAILED_HRESULT(pIBttn -> get_Style (&rgStyle));
		THROW_FAILED_HRESULT(pIBttn -> get_State (&rgState));

	// Bitmap besorgen
	HBITMAP hBitmap = NULL;
	int iOffset = 0;
	int iOffsetInBmp = 0;
	int iCnt = 0;

		hr = pIBttn -> GetImage ((long *)&hBitmap, &iCnt, &iOffsetInBmp);
		if (-1 == iOffsetInBmp)
			iOffsetInBmp = iIndex;

		if (SUCCEEDED(hr)) {
			THROW_FAILED_HRESULT(m_pToolBar -> AddBitmap (NULL, (UINT)hBitmap, iCnt, &iOffset));
			if (iOffsetInBmp > 0)
				iOffset += iOffsetInBmp;
		} else if (rgStyle & BUTTONSTYLE_SEPARATOR) {
		long lOffset = 0;

			pIBttn -> get_Width (&lOffset);	// Separator
			iOffset = lOffset;
		}

		memset (&tb, 0, sizeof(TBBUTTON));
		tb.iBitmap = iOffset;
		tb.idCommand = iCmdID;
		tb.fsState = (BYTE)rgState;
		tb.fsStyle = (BYTE)rgStyle;
		tb.dwData = reinterpret_cast<DWORD>((ITRiASBarInstallControl *)Inst);

	CComObject<CDispUIOwner> *pDispUIOwner = NULL;		// _ATL_11
	
		THROW_FAILED_HRESULT(CComObject<CDispUIOwner>::CreateInstance (&pDispUIOwner));
		if (NULL != pDispUIOwner) {
			pDispUIOwner -> AddRef();

//		WDToolBarUIOwner DispOwner (pIUIOwner);		// throws hr

			pDispUIOwner -> SetTargetUIOwner (pIUIOwner);
		}

/*	// neuen Parent setzen
		{
		WDispatch Parent (this);	// throws hr

			THROW_FAILED_HRESULT(pIBttn -> put_Parent (Parent));
		}
*/
	// jetzt wirklich einfügen
		hr = m_pToolBar -> InsertButton (iIndex, &tb, pDispUIOwner);
		if (NULL != pDispUIOwner)
			pDispUIOwner -> Release();
		if (FAILED(hr)) _com_issue_error(hr);

	// diesen Button zu der Liste der externen Buttons hinzufügen
		InsertButtonToList (iCmdID, pIBttn);

	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

return NOERROR;
}

HRESULT CTRiASToolBarObj::InsertButtonToList (UINT iCmdID, DControlToolBarButton *pIBttn)
{
	if (0 == iCmdID) return S_FALSE;		// Separatoren nicht behandeln

pair<CButtons::iterator, bool> p = m_mapBttns.insert (iCmdID, WDControlToolBarButton(pIBttn));

	ASSERT(p.second);		// muß erfolgreich sein
	return p.second ? S_OK : E_FAIL;
}

STDMETHODIMP CTRiASToolBarObj::DeleteButton (int iIndex)
{
	return DeleteItem (iIndex);
}

STDMETHODIMP CTRiASToolBarObj::Remove (void)
{
	m_mapBttns.clear();						// alle Buttons aus Liste herausnehmen
	return m_pToolBar -> RemoveBar();		// deletes this object
}

STDMETHODIMP CTRiASToolBarObj::GetButton (int iIndex, DControlToolBarButton **ppIBttn)
{
	if (NULL == ppIBttn) return E_POINTER;
	*ppIBttn = NULL;

	try {
	UINT uiID = 0;
	UINT uiStyle = 0;

		THROW_FAILED_HRESULT(m_pToolBar -> GetButtonStyle (iIndex, &uiStyle, &uiID));

	CButtons::iterator it = m_mapBttns.find (uiID);
	
		if (it == m_mapBttns.end()) 
			_com_issue_error(E_FAIL);

	WDControlToolBarButton Bttn ((*it).second);

		*ppIBttn = Bttn.detach();

	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}
	
	return S_OK;
}

STDMETHODIMP CTRiASToolBarObj::AddButton (int iIndex, DToolBarUIOwner *pIUIOwner, 
	VARIANT vBttnTmpl, DControlToolBarButton **ppIBttn)
{
	if (NULL == ppIBttn) return E_POINTER;
	*ppIBttn = NULL;

	try {
	CComVariant vBttn;
	HRESULT hr = vBttn.ChangeType (VT_DISPATCH, &vBttnTmpl);
	WDControlToolBarButton Bttn;

	WGetTRiASApplication GetApp (CLSID_OleAutoExtension);
	WDispatch App;

		THROW_FAILED_HRESULT(GetApp -> GetApplication (IID_IDispatch, App.ppv()));

		if (FAILED(hr)) {	// erzeugen eines neuen ToolBarButtons und dessen Initialisierung
			Bttn = WDControlToolBarButton (CLSID_TRiASToolBarButton);
			THROW_FAILED_HRESULT(Bttn -> put_Application (App));
		} else 
			Bttn = V_DISPATCH(&vBttn);		// throws hr
			
		THROW_FAILED_HRESULT(Bttn -> put_Parent (this));
		THROW_FAILED_HRESULT(InsertButton (iIndex, Bttn, pIUIOwner, NULL));

		*ppIBttn = Bttn.detach();

	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

	return S_OK;
}


