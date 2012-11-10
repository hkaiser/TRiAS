// Basisklasse für ObjektKlassenEigenschaft -----------------------------------
// File CLSPROPB.CXX

#include "trias03p.hxx"

#include <ixtensn.hxx>
#include <xtsnguid.h>

#include "clspropb.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Konstruktor/Destruktor/Initialisierung -------------------------------------
#pragma warning (disable: 4355)

CClassProperty :: CClassProperty (REFCLSID rClsID)
				: m_Persist (this, rClsID)
{
	m_dwRefCnt = 0;
}

#pragma warning (default: 4355)

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

	if (riid == IID_IPersist)
		*ppvObj = &m_Persist;

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

///////////////////////////////////////////////////////////////////////////////
// Embedded IPersist

// Konstruktor
CClassProperty::
XPersist::XPersist (IUnknown *pIUnk, REFCLSID rClsID)
		 : m_rClsID(rClsID)
{
	m_pIUnk = pIUnk;
}

// *** IUnkown methods
STDMETHODIMP CClassProperty::
XPersist::QueryInterface (REFIID riid, LPVOID *ppvObj)
{
	return m_pIUnk -> QueryInterface (riid, ppvObj);
}

STDMETHODIMP_(ULONG) CClassProperty::
XPersist::AddRef (void)
{
#if defined(_DEBUG)
	++m_dwRefCnt;
#endif // _DEBUG
	return m_pIUnk -> AddRef();
}

STDMETHODIMP_(ULONG) CClassProperty::
XPersist::Release (void)
{
#if defined(_DEBUG)
	--m_dwRefCnt;
#endif // _DEBUG
	return m_pIUnk -> Release();
}

// *** IPersist methods
STDMETHODIMP CClassProperty::
XPersist::GetClassID (CLSID *pClsID)
{
	*pClsID = m_rClsID;
	return NOERROR;
}

