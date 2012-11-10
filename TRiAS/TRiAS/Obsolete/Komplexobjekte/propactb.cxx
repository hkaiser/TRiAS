// Basisklasse für IPropertyAction --------------------------------------------
// File: PROPACTB.CXX

#include "featurep.hxx"

#include "propactb.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Konstruktor/Destruktor/Initialisierung -------------------------------------
CPropertyAction::CPropertyAction (LPUNKNOWN pIUnk)
{
#if defined(_DEBUG)
	m_dwRefCnt = 0;
#endif // WIN32
	m_pIUnk = pIUnk;	// kein AddRef !!
}

CPropertyAction::~CPropertyAction (void)
{
}

bool CPropertyAction::FInit (void) { return true; }

// ***IUnkown methods ---------------------------------------------------------
STDMETHODIMP CPropertyAction::QueryInterface (REFIID riid, LPVOID *ppvObj)
{
	return m_pIUnk -> QueryInterface (riid, ppvObj);
}

STDMETHODIMP_(ULONG) CPropertyAction::AddRef (void)
{
#if defined(_DEBUG)
	m_dwRefCnt++;		// debug purposes only
#endif // WIN32
	return m_pIUnk -> AddRef();
}

STDMETHODIMP_(ULONG) CPropertyAction::Release (void)
{
#if defined(_DEBUG)
	TX_ASSERT(m_dwRefCnt > 0);
	m_dwRefCnt--;		// debug purposes only
#endif // WIN32
	return m_pIUnk -> Release();
}

// *** IPropertyAction methods ------------------------------------------------
STDMETHODIMP CPropertyAction::AddConfigPages (
	LPFNADDPROPSHEETPAGE, LPARAM, DWORD, UINT *)
{
	return ResultFromScode (E_NOTIMPL);
}

STDMETHODIMP CPropertyAction::BeginAction (IProgressIndicator *)
{
	return ResultFromScode (E_NOTIMPL);
}

STDMETHODIMP CPropertyAction::DoAction (IDataObject *, DWORD)
{
	return ResultFromScode (E_NOTIMPL);
}

STDMETHODIMP CPropertyAction::EndAction (DWORD, IDataObject **)
{
	return ResultFromScode (E_NOTIMPL);
}

