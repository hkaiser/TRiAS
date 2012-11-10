// Wrapperklasse für ein eindimensionales SAFEARRAY ---------------------------
// File: ARRAY.HXX

#if !defined(_ARRAY_HXX)
#define _ARRAY_HXX

class CSafeArray {
private:
	int m_iType;
	SAFEARRAY *m_psa;	// Handle des verwalteten SAFEARRAY's

	unsigned int m_fIsValid : 1;
	unsigned int m_fAutoDetach : 1;
	unsigned int m_fAttached : 1;
			
protected:
	bool Lock (void);
	bool AccessData (void __huge **);
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
	
friend class CSafeArrayLock;
};

// ZugriffsKlassen auf ein CSafeArray -----------------------------------------
class CSafeArrayLock {
protected:
	CSafeArray &m_rsa;		// Bezugs-SafeArray
	LONG m_lDim;			// größter möglicher Index SAFEARRAY
	void __huge *m_pData;		// gelockte Daten
	
public:
		CSafeArrayLock (CSafeArray &rsa);
		~CSafeArrayLock (void);

inline	bool operator! (void) { return m_pData == NULL; }
inline	LONG Size (void) { return m_lDim +1; }
};

// typspezifischer Lock -------------------------------------------------------
#define DeclareSafeLock(typ)							\
class CLock##typ : public CSafeArrayLock {					\
public:										\
	inline	CLock##typ (CSafeArray &rsa) : CSafeArrayLock (rsa) {}		\
										\
inline	typ &operator[] (LONG lIndex)						\
	{ return ((typ __huge *)m_pData)[lIndex <= m_lDim ? lIndex : 0]; }	\
inline	operator typ * (void) { return (typ *)m_pData; }			\
};

#endif // _ARRAY_HXX
