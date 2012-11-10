///////////////////////////////////////////////////////////////////////////
// @doc 
// @module SafeArray.h | Wrapperklasse für ein eindimensionales SAFEARRAY's

#if !defined(_SAFEARRAY_H__4BAB20A4_A922_11D1_8588_00600875138A__INCLUDED_)
#define _SAFEARRAY_H__4BAB20A4_A922_11D1_8588_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#if !defined(DELETE_OBJ)
#define DELETE_OBJ(x) if(NULL==(x)){}else{delete (x); (x)=NULL;}
#endif // !defined(DELETE_OBJ)

///////////////////////////////////////////////////////////////////////////////
// ZugriffsKlassen auf ein CSafeArray 
class CSafeArray;		// forward declaration

template<class T> 
class CSafeArrayLock 
{
protected:
	CSafeArray &m_rsa;		// Bezugs-SafeArray
	LONG m_lDim;			// größter möglicher Index SAFEARRAY
	T *m_pData;				// gelockte Daten
	
public:
		inline CSafeArrayLock (CSafeArray &rsa) : m_rsa(rsa)
		{
			m_lDim = m_rsa.GetUBound();
			m_pData = NULL;
			if (m_rsa.Lock())	// Daten on CSafeArray mit Lock versehen
				m_rsa.AccessData ((void **)&m_pData);
		}
		inline ~CSafeArrayLock (void)
		{
			if (m_pData && m_rsa.UnAccessData()) 
				m_rsa.UnLock();	// Lock in CSafeArray aufheben
		}

	bool operator! (void) { return NULL == m_pData ? true : false; }
	LONG Size (void) { return m_lDim +1; }
//	T &operator[] (LONG lIndex) { _ASSERTE(0 <= lIndex && lIndex <= m_lDim); return m_pData[lIndex]; }
	operator T * (void) { return m_pData; }
};

#define DeclareSafeLock(typ)	\
	typedef CSafeArrayLock<typ> CLock##typ;

///////////////////////////////////////////////////////////////////////////////
// eigentliches SafeArray
class CSafeArray 
{
private:
	VARTYPE m_iType;
	SAFEARRAY *m_psa;	// Handle des verwalteten SAFEARRAY's

	unsigned int m_fIsValid : 1;
	unsigned int m_fAutoDetach : 1;
	unsigned int m_fAttached : 1;
			
public:
	bool Lock (void)
		{ return m_fIsValid ? SUCCEEDED(SafeArrayLock (m_psa)) : false; }
	bool AccessData (void **ppvData)
		{ *ppvData = NULL; return m_fIsValid ? SUCCEEDED(SafeArrayAccessData (m_psa, ppvData)) : false; }
	bool UnLock (void)
		{ return m_fIsValid ? SUCCEEDED(SafeArrayUnlock (m_psa)) : false; }
	bool UnAccessData (void)
		{ return m_fIsValid ? SUCCEEDED(SafeArrayUnaccessData (m_psa)) : false; }
	LONG GetUBound (void)
	{
	LONG lBound = 0;

		if (m_fIsValid) 
			SafeArrayGetUBound (m_psa, 1, &lBound);
		return lBound;
	}

public:
// Konstruktor/Destruktor/Initialisierung
		CSafeArray (VARTYPE iType) : m_iType(iType)
		{
			m_psa = NULL;
			m_fIsValid = false;
			m_fAutoDetach = false;
			m_fAttached = false;
		}
		CSafeArray (VARTYPE iType, long iDim) : m_iType(iType)
		{
		SAFEARRAYBOUND rgsaBounds[] = { iDim, 0, };

			m_fIsValid = false;
			m_fAutoDetach = false;
			m_fAttached = false;

			m_psa = SafeArrayCreate (iType, 1, rgsaBounds);
			if (m_psa) m_fIsValid = true;
		}

		CSafeArray (CSafeArray &rsa) : m_iType(rsa.m_iType)
		{
		HRESULT hr = E_OUTOFMEMORY;

			m_fIsValid = false;
			m_fAutoDetach = false;
			m_fAttached = false;

			if (rsa.m_psa) hr = SafeArrayCopy (rsa.m_psa, &m_psa);
			if (m_psa && SUCCEEDED(hr)) 
				m_fIsValid = true;
		}

		CSafeArray (VARTYPE iType, SAFEARRAY *psa, bool fAutoDetach = false) 
			: m_iType(iType)
		{
			m_fIsValid = false;
			if ((m_psa = psa) != NULL) {
				m_fIsValid = true;
				m_fAutoDetach = fAutoDetach;
				m_fAttached = true;
			}
		}

		~CSafeArray (void)
		{
			if (m_fAutoDetach) Detach();

			if (m_psa && m_fIsValid) {
				SafeArrayDestroy (m_psa);
				m_psa = NULL;
			}
		}

	static CSafeArray *CreateInstance (int iType, long iDim)
	{
	CSafeArray *psa = NULL;
	
		try { psa = new CSafeArray (iType); } catch(...) {}
		if (psa == NULL || !psa -> FInit (iDim)) {
			DELETE_OBJ(psa);
			return NULL;
		}
		return psa;
	}

	bool FInit (long iDim)
	{
		if (m_psa && m_fIsValid) 
			SafeArrayDestroy (m_psa);
		
	SAFEARRAYBOUND rgsaBounds[] = { iDim, 0, };

		m_fIsValid = false;
		m_psa = SafeArrayCreate (m_iType, 1, rgsaBounds);
		if (m_psa) 
			m_fIsValid = true;
		return m_fIsValid ? true : false;
	}

	CSafeArray & operator= (CSafeArray &rsa)	// assignment operator
	{
		if (&rsa == this) return *this;	// nicht sich selbst zuweisen
		if (m_psa && m_fIsValid) 
			SafeArrayDestroy (m_psa);
		
	HRESULT hr = E_OUTOFMEMORY;

		m_fIsValid = false;
		m_fAutoDetach = false;
		m_fAttached = false;

		if (rsa.m_psa) hr = SafeArrayCopy (rsa.m_psa, &m_psa);
		if (m_psa && SUCCEEDED(hr)) 
			m_fIsValid = true;
		return *this;
	}

	operator bool (void) { return m_fIsValid ? true : false; }
	bool operator! (void) { return m_fIsValid ? false : true; }
	bool IsAttached (void) { return m_fAttached ? true : false; }
	operator SAFEARRAY * (void) { return m_psa; }

	bool Attach (SAFEARRAY *psa, bool fAutoDetach = false)
	{
		if (m_psa && m_fIsValid) 
			SafeArrayDestroy (m_psa);
		
		m_fIsValid = false;
		if ((m_psa = psa) != NULL) {
			m_fIsValid = true;
			m_fAutoDetach = fAutoDetach;
			m_fAttached = true;
		}
		return m_fIsValid ? true : false;
	}

	SAFEARRAY *Detach (void)
	{
	SAFEARRAY *psa = m_psa;

		m_psa = NULL;
		m_fIsValid = false;
		return psa;
	}
};

#endif // !defined(_SAFEARRAY_H__4BAB20A4_A922_11D1_8588_00600875138A__INCLUDED_)
