// Wrapperklasse für ein eindimensionales SAFEARRAY ---------------------------
// File: ARRAY.HXX

#if !defined(_ARRAY_HXX)
#define _ARRAY_HXX

#if !defined(WIN32)
#error "Usable only under WIN32"
#endif // !WIN32

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

inline	bool operator! (void) { return m_pData == NULL; }
inline	LONG Size (void) { return m_lDim +1; }
inline	T &operator[] (LONG lIndex) { return m_pData[lIndex <= m_lDim ? lIndex : 0]; }
inline	operator T * (void) { return m_pData; }
};

#define DeclareSafeLock(typ)	\
	typedef CSafeArrayLock<typ> CLock##typ;

///////////////////////////////////////////////////////////////////////////////
// eigentliches SafeArray
class CSafeArray 
{
private:
	int m_iType;
	SAFEARRAY *m_psa;	// Handle des verwalteten SAFEARRAY's

	unsigned int m_fIsValid : 1;
	unsigned int m_fAutoDetach : 1;
	unsigned int m_fAttached : 1;
			
public:
	bool Lock (void);
	bool AccessData (void **);
	bool UnLock (void);
	bool UnAccessData (void);
	LONG GetUBound (void);
		
public:
// Konstruktor/Destruktor/Initialisierung
		CSafeArray (int iType);
		CSafeArray (int iType, long iDim);
		CSafeArray (CSafeArray &rsa);
				
		~CSafeArray (void);
		
static CSafeArray *CreateInstance (int iType, long iDim);

	bool FInit (long iDim);
	
	CSafeArray & operator= (CSafeArray &rsa);	// assignment operator

	operator bool (void) { return m_fIsValid ? true : false; }
	bool operator! (void) { return m_fIsValid ? false : true; }
	bool IsAttached (void) { return m_fAttached ? true : false; }

	bool Attach (SAFEARRAY *psa, bool fAutoDetach = false);
	SAFEARRAY *Detach (void);
};

#endif // _ARRAY_HXX
