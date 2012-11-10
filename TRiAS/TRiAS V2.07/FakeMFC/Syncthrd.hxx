// Verwaltung von Thread-Spezifika --------------------------------------------
// File: SYNCTHRD.HXX

#if !defined(_SYNCTHRD_HXX)
#define _SYNCTHRD_HXX

// CTRiASMutex enkapsuliert ein Mutex-Handle, welches vom Betriebssystem zur Verfügung 
// gestellt wird.
class CTRiASMutex {
private:
	HANDLE m_hMtx;		// Handle des Mutex-Objektes

public:
	inline CTRiASMutex (bool fUseMtx = true);
	inline ~CTRiASMutex (void);

	inline HANDLE Handle (void) const { return m_hMtx; }
	inline operator bool (void) { return Handle() != NULL ? true : false; }

// CLockMutex sorgt dafür, daß der Thread, der Zugriff auf die Klasse erhalten
// will, die mit diesem CLockMutex verbunden ist, solange blockiert wird, bis
// kein anderer Thread mehr eine Instanz dieser Klasse (CLockMutex) aktiv hat.
	class CLockMutex {
	private:
		const CTRiASMutex &m_Mtx;

	public:
		inline CLockMutex (const CTRiASMutex &, DWORD dwTimeOut = INFINITE);
		inline ~CLockMutex (void);
	};

friend class CLockMutex;
};

inline CTRiASMutex :: CTRiASMutex (bool fUseMtx)
	       : m_hMtx (fUseMtx ? CreateMutex (NULL, false, NULL) : NULL)
{
}

inline CTRiASMutex :: ~CTRiASMutex (void)
{
	if (Handle()) {
		CloseHandle (Handle());
		m_hMtx = NULL;
	}
}

inline CTRiASMutex :: 
CLockMutex :: CLockMutex (const CTRiASMutex &mtx, DWORD dwTimeOut)
	    : m_Mtx (mtx)
{
	if (NULL != m_Mtx.Handle()) 
		WaitForSingleObject (m_Mtx.Handle(), dwTimeOut);
}

inline CTRiASMutex :: 
CLockMutex :: ~CLockMutex (void)
{
	if (NULL != m_Mtx.Handle()) 
		ReleaseMutex (m_Mtx.Handle());
}

// CSyncMonitor ist eine BasisKlasse für alle Klassen, die einen ZugriffsSchutz im 
// Sinne des Schutzes vor gleichzeitigem Zugriff aus mehreren Thread's eines
// Prozesses heraus benötigen.
// Sie ist eine WrapperKlasse, die die Erzeugung der beiden für das Verwalten 
// eines Mutex's notwendigen Klassen CTRiASMutex und CLockMutex vereinfacht.
class CSyncMonitor {
private:
	CTRiASMutex m_Mtx;

protected:
	inline CSyncMonitor (bool fUseMtx = true);	// nur als BasisKlasse verwenden

// CSyncThread ist die Klasse, die die eigentliche Synchronisation der Threads
// realisiert, wobei automatisch im Destruktor das Mutex wieder freigegeben wird,
// was insbesondere in Szenarios des ExeptionHandling wichtig ist. Sie darf nur 
// innerhalb von Memberfunktionen der zu schützenden Klasse (abgeleitet von
// CSyncMonitor) verwendet werden.
	class CSyncThread {
	private:
		CTRiASMutex :: CLockMutex m_LockMtx;

	public:
		inline CSyncThread (const CSyncMonitor *, DWORD dwTimeOut = INFINITE);
	};

friend class CSyncThread;
};

inline CSyncMonitor :: CSyncMonitor (bool fUseMtx)
		     : m_Mtx (fUseMtx)
{
}

inline CSyncMonitor :: 
CSyncThread :: CSyncThread (const CSyncMonitor *pMonitor, DWORD dwTimeOut)
	     : m_LockMtx (pMonitor -> m_Mtx, dwTimeOut)
{
}

#endif // _SYNCTHRD_HXX
