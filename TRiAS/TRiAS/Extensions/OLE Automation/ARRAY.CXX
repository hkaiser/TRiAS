// Wrapperklasse für ein eindimensionales SAFEARRAY ---------------------------
// File: ARRAY.CXX

#include "precomp.hxx"
#include "array.hxx"

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

// Initialisierung/Konstruktor/Destruktor -------------------------------------
CSafeArray :: CSafeArray (int iType)
	    : m_iType(iType)
{
	m_psa = NULL;
	m_fIsValid = false;
	m_fAutoDetach = false;
	m_fAttached = false;
}

CSafeArray :: CSafeArray (int iType, long iDim)
	    : m_iType(iType)
{
SAFEARRAYBOUND rgsaBounds[] = { iDim, 0, };

	m_fIsValid = false;
	m_fAutoDetach = false;
	m_fAttached = false;

	m_psa = SafeArrayCreate (iType, 1, rgsaBounds);
	if (m_psa) m_fIsValid = true;
}

CSafeArray :: CSafeArray (CSafeArray &rsa)
	    : m_iType(rsa.m_iType)
{
HRESULT hr = ResultFromScode (E_OUTOFMEMORY);

	m_fIsValid = false;
	m_fAutoDetach = false;
	m_fAttached = false;

	if (rsa.m_psa) hr = SafeArrayCopy (rsa.m_psa, &m_psa);
	if (m_psa && SUCCEEDED(hr)) 
		m_fIsValid = true;
}

CSafeArray :: ~CSafeArray (void)
{
	if (m_fAutoDetach) Detach();

	if (m_psa && m_fIsValid) {
		SafeArrayDestroy (m_psa);
		m_psa = NULL;
	}
}

CSafeArray &CSafeArray :: operator= (CSafeArray &rsa)
{
	if (&rsa == this) return *this;	// nicht sich selbst zuweisen
	if (m_psa && m_fIsValid) SafeArrayDestroy (m_psa);
	
HRESULT hr = ResultFromScode (E_OUTOFMEMORY);

	m_fIsValid = false;
	m_fAutoDetach = false;
	m_fAttached = false;

	if (rsa.m_psa) hr = SafeArrayCopy (rsa.m_psa, &m_psa);
	if (m_psa && SUCCEEDED(hr)) 
		m_fIsValid = true;

return *this;
}

bool CSafeArray :: FInit (long iDim)
{
	if (m_psa && m_fIsValid) SafeArrayDestroy (m_psa);
	
SAFEARRAYBOUND rgsaBounds[] = { iDim, 0, };

	m_fIsValid = false;

	m_psa = SafeArrayCreate (m_iType, 1, rgsaBounds);
	if (m_psa) m_fIsValid = true;

return m_fIsValid ? true : false;
}

CSafeArray *CSafeArray :: CreateInstance (int iType, long iDim)
{
CSafeArray *psa = new CSafeArray (iType);

	if (psa == NULL || !psa -> FInit (iDim)) {
		DELETE_OBJ (psa);
		return NULL;
	}
	
return psa;
}

LONG CSafeArray :: GetUBound (void)
{
LONG lBound = 0;

	if (m_fIsValid) SafeArrayGetUBound (m_psa, 1, &lBound);

return lBound;
}

bool CSafeArray :: Lock (void)
{
	if (m_fIsValid) return SUCCEEDED(SafeArrayLock (m_psa));
	
return false;
}

bool CSafeArray :: AccessData (void __huge **ppvData)
{
	*ppvData = NULL;
	if (m_fIsValid) return SUCCEEDED(SafeArrayAccessData (m_psa, ppvData));
	
return false;
}

bool CSafeArray :: UnLock (void)
{
	if (m_fIsValid) return SUCCEEDED(SafeArrayUnlock (m_psa));

return false;
}

bool CSafeArray :: UnAccessData (void)
{
	if (m_fIsValid) return SUCCEEDED(SafeArrayUnaccessData (m_psa));
	
return false;
}

bool CSafeArray :: Attach (SAFEARRAY *psa, bool fAutoDetach)
{
	if (m_psa && m_fIsValid) SafeArrayDestroy (m_psa);
	
	m_fIsValid = false;

	if ((m_psa = psa) != NULL) {
		m_fIsValid = true;
		m_fAutoDetach = fAutoDetach;
		m_fAttached = true;
	}
		
return m_fIsValid ? true : false;
}

SAFEARRAY *CSafeArray :: Detach (void)
{
SAFEARRAY *psa = m_psa;

	m_psa = NULL;
	m_fIsValid = false;
	
return psa;
}

