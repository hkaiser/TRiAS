// Basisklasse für ObjektKlassenEigenschaft -----------------------------------
// File CLSPROPB.CXX

#include "featurep.hxx"

#include "clspropb.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Konstruktor/Destruktor/Initialisierung -------------------------------------
CClassProperty :: CClassProperty (void)
{
	m_dwRefCnt = 0;
}

CClassProperty :: ~CClassProperty (void)
{
}

bool CClassProperty :: FInit (void) { return true; }

// *** IUnkown methods --------------------------------------------------------
STDMETHODIMP CClassProperty :: QueryInterface (REFIID riid, LPVOID *ppvObj)
{
	*ppvObj = NULL;
	if (riid == IID_IUnknown || riid == IID_IClassProperty) 
		*ppvObj = this;

	if (*ppvObj) {
		LPUNKNOWN(*ppvObj) -> AddRef();
		return NOERROR;
	}

return ResultFromScode (E_NOINTERFACE);
}

STDMETHODIMP_(ULONG) CClassProperty :: AddRef (void)
{
	return ++m_dwRefCnt;
}

STDMETHODIMP_(ULONG) CClassProperty :: Release (void)
{
	TX_ASSERT(m_dwRefCnt > 0);

	if (--m_dwRefCnt == 0) {
		delete this;
		return 0L;
	}

return m_dwRefCnt;
}

// *** IClassProperty specific functions *** ----------------------------------
STDMETHODIMP CClassProperty :: GetPropInfo (LPSTR, WORD, DWORD *)
{
	return ResultFromScode (E_NOTIMPL);
}

STDMETHODIMP CClassProperty :: Reset (void)
{
	return ResultFromScode (E_NOTIMPL);
}

STDMETHODIMP_(ULONG) CClassProperty :: Count (void)
{
	return 0L;
}

STDMETHODIMP CClassProperty :: HelpInfo (LPSTR, ULONG, LPSTR, ULONG *)
{
	return ResultFromScode (E_NOTIMPL);
}

STDMETHODIMP CClassProperty :: Eval (IEnumLONG *, LPSTR, ULONG, ULONG *) 
{
	return ResultFromScode (E_NOTIMPL);
}

STDMETHODIMP CClassProperty :: Cumulation (LPSTR, ULONG, ULONG *)
{
	return ResultFromScode (E_NOTIMPL);
}

