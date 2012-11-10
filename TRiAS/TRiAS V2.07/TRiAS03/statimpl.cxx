// InterfaceImplementation IProgessIndicator ----------------------------------
// File: STATIMPL.CXX

#include "trias03p.hxx"

#include "trias03.h"

#include <time.h>

#include <statguid.h>

#include "statimpl.hxx"
#include "status.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern char g_pDLLName[_MAX_PATH];
extern LONG g_cObj;

// Externe Funktion, über welche eine Instanz erzeugt werden kann -------------
_TRIAS03_ENTRY HRESULT EXPORT03 PiCreateInstance (REFIID riid, LPVOID *ppIPrInd)
{
	try {
	CComObject<CProgressIndicator> *pPI = NULL;
	
		THROW_FAILED_HRESULT(CComObject<CProgressIndicator>::CreateInstance(&pPI));
		return ((IProgressIndicator *)pPI) -> QueryInterface (riid, ppIPrInd);

	} catch (_com_error &e) {
		return _COM_ERROR(e);
	}
}

// Konstruktor/Destruktor/Initialisierung -------------------------------------
CProgressIndicator :: CProgressIndicator (void)
{
	m_pDlg = NULL;
	m_pParent = NULL;
	m_hWnd = NULL;
	m_fInitialized = false;
}

CProgressIndicator :: ~CProgressIndicator (void)
{
	DELETE_OBJ (m_pDlg);
	DELETE_OBJ (m_pParent);
}

// *** IProgressIndicator methods *** -----------------------------------------
STDMETHODIMP_(HWND) CProgressIndicator :: InitNew (HWND hWnd, DWORD dwType)
{
	DELETE_OBJ(m_pDlg);
	DELETE_OBJ(m_pParent);

	if (!(dwType & PI_INIT_LATER)) {
		m_hWnd = NULL;

		try {
			TX_TRY(m_pParent = new Window (hWnd));
			if (NULL == m_pParent) _com_issue_error(E_OUTOFMEMORY);

		ResourceFile RF (g_pDLLName);

			TX_TRY(m_pDlg = new CStatusDlg (m_pParent, ResID (IDD_STATUSDLG, &RF)));
			if (NULL == m_pDlg) _com_issue_error(E_OUTOFMEMORY);

		HWND hWndNew = m_pDlg -> Handle (API_WINDOW_HWND);

			if (NULL != hWndNew)
				m_fInitialized = true;
			return hWndNew;

		} catch (_com_error &) {
			return NULL;
		}

	} else 
		m_hWnd = hWnd;

	return NULL;
}

STDMETHODIMP CProgressIndicator :: Restart (ULONG ulMin, ULONG ulMax, DWORD dwFlags)
{
	if (NULL == m_pDlg) {
		TX_ASSERT(NULL != m_hWnd);

		DELETE_OBJ(m_pParent);
		try {
			m_pParent = new Window (m_hWnd);
			if (NULL == m_pParent) _com_issue_error(E_OUTOFMEMORY);

		ResourceFile RF (g_pDLLName);

			m_pDlg = new CStatusDlg (m_pParent, ResID (dwFlags & PIFLAG_AVI_MASK ? IDD_STATUSDLG_AVI : IDD_STATUSDLG, &RF));
			if (NULL == m_pDlg) _com_issue_error(E_OUTOFMEMORY);

		} catch (_com_error &) {
			return E_OUTOFMEMORY;
		}
		m_fInitialized = true;
	}
	return m_pDlg -> FInit (ulMin, ulMax, dwFlags) ? NOERROR : E_FAIL;
}

STDMETHODIMP CProgressIndicator :: ChangeText (DWORD dwWhichText, LPCSTR pcNewText)
{
	if (!m_fInitialized)
		return E_UNEXPECTED;

	if (dwWhichText & PIFLAG_CAPTION) {
		m_pDlg -> SetCaption (pcNewText);
		return NOERROR;
	}
	if (dwWhichText & PIFLAG_FILE) 
		return m_pDlg -> SetFile (pcNewText);

	if (dwWhichText & PIFLAG_FILENAME) 
		return m_pDlg -> SetFileName (pcNewText);

	if (dwWhichText & PIFLAG_STATUS) 
		return m_pDlg -> SetStatus (pcNewText);

	if (dwWhichText & PIFLAG_ADJUSTPERCENT) 
		return m_pDlg -> SetStatusText (pcNewText);

	if (dwWhichText & PIFLAG_RESULT) 
		return m_pDlg -> SetResult (pcNewText);

return ResultFromScode (E_UNEXPECTED);
}

STDMETHODIMP CProgressIndicator :: RetrieveText (DWORD dwWichText, LPSTR cbText, ULONG uiLen)
{
	if (!m_fInitialized)
		return E_UNEXPECTED;

	return ResultFromScode (E_NOTIMPL);
}

STDMETHODIMP_(int) CProgressIndicator :: SetPosition (ULONG uiNewPos)
{
	if (!m_fInitialized) return 0;

	return m_pDlg -> SetPos (uiNewPos);
}

STDMETHODIMP_(BOOL) CProgressIndicator :: WasCanceled (void)
{
	if (!m_fInitialized)
		return false;

	return m_pDlg -> Break();
}

///////////////////////////////////////////////////////////////////////////////
// IProgressIndicator2 methods
//#if _MSC_VER >= 1100
STDMETHODIMP CProgressIndicator::InitNew (LONG hWndParent, DWORD dwReserved, LONG *phWnd)
//#else
//STDMETHODIMP CProgressIndicator::InitNew (HWND hWndParent, DWORD dwReserved, HWND *phWnd)
//#endif // _MSC_VER >= 1100
{
	if (NULL == phWnd) 
		return E_POINTER;

//#if _MSC_VER >= 1100
	*phWnd = (LONG)InitNew ((HWND)hWndParent, dwReserved);
//#else
//	*phWnd = InitNew ((HWND)hWndParent, dwReserved);
//#endif // _MSC_VER >= 1100
	return (NULL != *phWnd) ? S_OK : E_FAIL;
}

STDMETHODIMP CProgressIndicator::Restart (ULONG ulMinPos, ULONG ulMaxPos, PIFLAGS rgFlags)
{
	return Restart (ulMinPos, ulMaxPos, (DWORD)rgFlags);
}

STDMETHODIMP CProgressIndicator::ChangeText (PIFLAGS rgWhichText, BSTR bstrNewText)
{
	USES_CONVERSION;
	return ChangeText ((DWORD)rgWhichText, OLE2A(bstrNewText));
}

STDMETHODIMP CProgressIndicator::RetrieveText (PIFLAGS rgWhichText, BSTR *pbstrOut)
{
	if (NULL == pbstrOut) 
		return E_POINTER;

char cbBuffer[_MAX_PATH];
HRESULT hr = RetrieveText ((DWORD)rgWhichText, cbBuffer, sizeof(cbBuffer));

	if (FAILED(hr)) return hr;

	USES_CONVERSION;
	*pbstrOut = SysAllocString (A2OLE(cbBuffer));
	return (NULL != pbstrOut) ? S_OK : E_OUTOFMEMORY;
}

STDMETHODIMP CProgressIndicator::SetPosition (ULONG ulNewPos, INT *piPercent)
{
INT iActPercent = SetPosition (ulNewPos);

	if (NULL != piPercent)
		*piPercent = iActPercent;
	return S_OK;
}

STDMETHODIMP CProgressIndicator::IncrementPosition (INT *piPercent)
{
LONG lActPos = m_pDlg -> GetActPos();

	return SetPosition (lActPos+1, piPercent);
}

STDMETHODIMP CProgressIndicator::IsCanceled (void)
{
	return WasCanceled() ? S_OK : S_FALSE;
}

STDMETHODIMP CProgressIndicator::get_Flags (PIFLAGS *prgFlags)
{
	if (NULL == prgFlags) return E_POINTER;

	*prgFlags = (PIFLAGS)m_pDlg -> GetFlags();
	return S_OK;
}

STDMETHODIMP CProgressIndicator::put_Flags (PIFLAGS rgFlags)
{
PIFLAGS rgActFlags = (PIFLAGS)m_pDlg -> GetFlags();

	if (rgActFlags == rgFlags) 
		return S_OK;

ULONG ulMin = 0;
ULONG ulMax = 0;
HRESULT hr = m_pDlg -> GetRange (&ulMin, &ulMax);

	if (SUCCEEDED(hr)) 
		hr = m_pDlg -> FInit (ulMin, ulMax, (DWORD)rgFlags, true);
	return hr;
}

STDMETHODIMP CProgressIndicator::RetrieveRange (ULONG *pulMinPos, ULONG *pulMaxPos)
{
	return m_pDlg -> GetRange (pulMinPos, pulMaxPos);
}

