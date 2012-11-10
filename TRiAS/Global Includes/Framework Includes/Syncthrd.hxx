// Verwaltung von Thread-Spezifika --------------------------------------------
// File: SYNCTHRD.HXX

#if !defined(_SYNCTHRD_HXX)
#define _SYNCTHRD_HXX

#if defined(WIN32)

#include <windows.h>		// wird nur hier benötigt

// CMutex enkapsuliert ein Mutex-Handle, welches vom Betriebssystem zur Verfügung 
// gestellt wird.
class _CTR_ENTRY32 CMutex {
private:
	HANDLE m_hMtx;		// Handle des Mutex-Objektes

public:
	inline CMutex (BOOL fUseMtx = true);
	inline ~CMutex (void);

	inline HANDLE Handle (void) const { return m_hMtx; }
	inline operator BOOL (void) { return Handle() != NULL ? true : false; }

// CLockMutex sorgt dafür, daß der Thread, der Zugriff auf die Klasse erhalten
// will, die mit diesem CLockMutex verbunden ist, solange blockiert wird, bis
// kein anderer Thread mehr eine Instanz dieser Klasse (CLockMutex) aktiv hat.
	class CLockMutex {
	private:
		const CMutex &m_Mtx;

	public:
		inline CLockMutex (const CMutex &, DWORD dwTimeOut = INFINITE);
		inline ~CLockMutex (void);

		inline DWORD Aquire();
		inline BOOL Release();
	};

friend class CLockMutex;
};

inline CMutex::CMutex (BOOL fUseMtx)
	       : m_hMtx ((fUseMtx && !IsWin32s()) ? CreateMutex (NULL, false, NULL) : NULL)
{
}

inline CMutex::~CMutex (void)
{
	if (Handle()) {
		CloseHandle (Handle());
		m_hMtx = NULL;
	}
}

inline CMutex:: 
CLockMutex::CLockMutex (const CMutex &mtx, DWORD dwTimeOut)
	: m_Mtx (mtx)
{
	Aquire();
}

inline void CMutex::
CLockMutex::Aquire()
{
	if (NULL != m_Mtx.Handle()) 
		WaitForSingleObject (m_Mtx.Handle(), dwTimeOut);
}

inline CMutex:: 
CLockMutex::~CLockMutex (void)
{
	Release();
}

inline void CMutex::
CLockMutex::Release()
{
	if (NULL != m_Mtx.Handle()) 
		ReleaseMutex (m_Mtx.Handle());
}

// CSyncMonitor ist eine BasisKlasse für alle Klassen, die einen ZugriffsSchutz im 
// Sinne des Schutzes vor gleichzeitigem Zugriff aus mehreren Thread's eines
// Prozesses heraus benötigen.
// Sie ist eine WrapperKlasse, die die Erzeugung der beiden für das Verwalten 
// eines Mutex's notwendigen Klassen CMutex und CLockMutex vereinfacht.
class _CTR_ENTRY32 CSyncMonitor {
private:
	CMutex m_Mtx;

protected:
	inline CSyncMonitor (BOOL fUseMtx = true);	// nur als BasisKlasse verwenden

// CSyncThread ist die Klasse, die die eigentliche Synchronisation der Threads
// realisiert, wobei automatisch im Destruktor das Mutex wieder freigegeben wird,
// was insbesondere in Szenarios des ExeptionHandling wichtig ist. Sie darf nur 
// innerhalb von Memberfunktionen der zu schützenden Klasse (abgeleitet von
// CSyncMonitor) verwendet werden.
	class CSyncThread {
	private:
		CMutex::CLockMutex m_LockMtx;

	public:
		inline CSyncThread (const CSyncMonitor *, DWORD dwTimeOut = INFINITE);
	
		inline void AquireLock() { m_LockMtx.Aquire(); }
		inline void ReleaseLock() { m_LockMtx.Release(); }
	};

	friend class CSyncThread;
};

inline CSyncMonitor::CSyncMonitor (BOOL fUseMtx)
	: m_Mtx (fUseMtx)
{
}

inline CSyncMonitor::
CSyncThread::CSyncThread (const CSyncMonitor *pMonitor, DWORD dwTimeOut)
	: m_LockMtx (pMonitor -> m_Mtx, dwTimeOut)
{
}

#else	// WIN32

// In der 16-Bit-Welt gibt es (unter Windows) keine Threads -------------------
class CMutex {
public:
	inline CMutex (BOOL = true) {}
	inline ~CMutex (void) {}

	class CLockMutex {
	public: 
		CLockMutex (const CMutex &, unsigned long = -1) {}
		~CLockMutex (void) {}
	};
};


class CSyncMonitor {
protected:
	inline CSyncMonitor (BOOL = true) {}	// nur als BasisKlasse verwenden

	class CSyncThread {
	public:
		CSyncThread (const CSyncMonitor *, unsigned long = -1) {}
	};
};


#endif	// WIN32

#endif // _SYNCTHRD_HXX
