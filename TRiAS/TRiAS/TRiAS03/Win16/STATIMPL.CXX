// InterfaceImplementation IProgessIndicator ----------------------------------
// File: STATIMPL.CXX

#include "trias03p.hxx"

#include "trias03.h"

#include <time.h>

#include <statguid.h>

#include <statimpl.hxx>
#include "status.hxx"

extern char g_pDLLName[260];
extern LONG g_cObj;

#if !defined(WIN32) && !defined(InterlockedIncrement)
#define InterlockedIncrement(pl)		(++(*(pl)))
#define InterlockedDecrement(pl)		(--(*(pl)))
#endif // !WIN32 && !InterlockedIncrement

// Externe Funktion, über welche eine Instanz erzeugt werden kann -------------
_TRIAS03_ENTRY HRESULT EXPORT03 PiCreateInstance (REFIID riid, LPVOID *ppIPrInd)
{
CProgessIndicator *pPI = CProgessIndicator :: CreateInstance();

	if (NULL == pPI) return ResultFromScode (E_OUTOFMEMORY);

HRESULT hr = pPI -> QueryInterface (riid, ppIPrInd);

	pPI -> Release();

return hr;
}

// Konstruktor/Destruktor/Initialisierung -------------------------------------
bool CProgessIndicator :: FInit (void)
{
	return true;
}

CProgessIndicator :: CProgessIndicator (void)
{
	m_dwRefCnt = 0;
	m_pDlg = NULL;
	m_pParent = NULL;
}

CProgessIndicator :: ~CProgessIndicator (void)
	{
	DELETE (m_pDlg);
	DELETE (m_pParent);
	InterlockedDecrement(&g_cObj);
}

CProgessIndicator *CProgessIndicator :: CreateInstance (void)
{
CProgessIndicator *pPI = new CProgessIndicator();

	if (NULL == pPI || !pPI -> FInit()) {
		DELETE(pPI);
		return NULL;
	}
	pPI -> AddRef();
	InterlockedIncrement(&g_cObj);

return pPI;
}

// *** IUnknown methods *** ---------------------------------------------------
STDMETHODIMP CProgessIndicator :: QueryInterface (REFIID riid, LPVOID FAR* ppvObj)
{
	*ppvObj = NULL;
	if (riid == IID_IUnknown || riid == IID_IProgressIndicator)
		*ppvObj = (LPVOID)this;

	if (NULL != *ppvObj) {
		LPUNKNOWN(*ppvObj) -> AddRef();
		return NOERROR;
	}

return ResultFromScode(E_NOINTERFACE);
}

STDMETHODIMP_(ULONG) CProgessIndicator :: AddRef (void)
{
	return ++m_dwRefCnt;
}

STDMETHODIMP_(ULONG) CProgessIndicator :: Release (void)
{
	if (--m_dwRefCnt == 0) {
		delete this;
		return 0L;
	}

return m_dwRefCnt;
}


// *** IProgressIndicator methods *** -----------------------------------------
STDMETHODIMP_(HWND) CProgessIndicator :: InitNew (HWND hWnd, DWORD dwReserved)
{
	DELETE(m_pDlg);

	m_pParent = new Window (hWnd);
	if (NULL == m_pParent) return NULL;

ResourceFile RF (g_pDLLName);

	m_pDlg = new CStatusDlg (m_pParent, ResID (IDD_STATUSDLG, &RF));
	if (NULL == m_pDlg) return NULL;

return m_pDlg -> Handle (API_WINDOW_HWND);
}

STDMETHODIMP CProgessIndicator :: Restart (ULONG ulMin, ULONG ulMax, DWORD dwFlags)
{
	return m_pDlg -> FInit (ulMin, ulMax, dwFlags) ? NOERROR : ResultFromScode (E_FAIL);
}

STDMETHODIMP CProgessIndicator :: ChangeText (DWORD dwWhichText, LPCSTR pcNewText)
{
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

STDMETHODIMP CProgessIndicator :: RetrieveText (DWORD dwWichText, LPSTR cbText, ULONG uiLen)
{
	return ResultFromScode (E_NOTIMPL);
}

STDMETHODIMP_(int) CProgessIndicator :: SetPosition (ULONG uiNewPos)
{
	return m_pDlg -> SetPos (uiNewPos);
}

STDMETHODIMP_(BOOL) CProgessIndicator :: WasCanceled (void)
{
	return m_pDlg -> Break();
}

