// Verwaltung von Thread-Spezifika --------------------------------------------
// File: SYNCTHRDCS.HXX

#if !defined(_SYNCTHRDCS_HXX)
#define _SYNCTHRDCS_HXX

#if defined(WIN32)

#include <windows.h>		// wird nur hier benötigt

// CMutex enkapsuliert ein Mutex-Handle, welches vom Betriebssystem zur Verfügung 
// gestellt wird.
class _CTR_ENTRY32 CMutex {
public:
	class CAutoCriticalSection
	{
	public:
		void Lock() { EnterCriticalSection(&m_sec); }
		void Unlock() { LeaveCriticalSection(&m_sec); }
		CAutoCriticalSection() { InitializeCriticalSection(&m_sec); }
		~CAutoCriticalSection() { DeleteCriticalSection(&m_sec); }

	protected:
		CRITICAL_SECTION m_sec;
	};

private:
	CAutoCriticalSection *m_pCS;		// pointer auf critical section

public:
	inline CMutex (BOOL fUseMtx = true);
	inline ~CMutex (void);

	inline BOOL IsValid() const { return NULL != m_pCS ? true : false; }
	inline operator !() const { return !IsValid(); }

	inline HANDLE Handle (void) const { return reinterpret_cast<HANDLE>(m_pCS); }
	inline operator BOOL (void) { return Handle() != NULL ? true : false; }

	void Lock() { if (NULL != m_pCS) m_pCS -> Lock(); }
	void Unlock() { if (NULL != m_pCS) m_pCS -> Unlock(); }

// CLockMutex sorgt dafür, daß der Thread, der Zugriff auf die Klasse erhalten
// will, die mit diesem CLockMutex verbunden ist, solange blockiert wird, bis
// kein anderer Thread mehr eine Instanz dieser Klasse (CLockMutex) aktiv hat.
	class CLockMutex {
	private:
		const CMutex &m_Mtx;

	public:
		inline CLockMutex (const CMutex &, DWORD dwTimeOut = INFINITE);
		inline ~CLockMutex (void);

		inline void Aquire();
		inline void Release();
	};

	friend class CLockMutex;
};

inline CMutex::CMutex (BOOL fUseMtx)
	: m_pCS (NULL)
{
	if (fUseMtx && !IsWin32s()) {
		try { m_pCS = new CAutoCriticalSection; } catch(...) {}
	}
}

inline CMutex::~CMutex (void)
{
	if (NULL != m_pCS) {
		delete m_pCS;
		m_pCS = NULL;
	}
}

inline CMutex::
CLockMutex::CLockMutex (const CMutex &mtx, DWORD /*dwTimeOut*/)
    : m_Mtx (mtx)
{
	Aquire();
}

inline void CMutex::
CLockMutex::Aquire()
{
	if (m_Mtx.IsValid()) 
		const_cast<CMutex &>(m_Mtx).Lock(); 
}

inline CMutex::
CLockMutex::~CLockMutex (void)
{
	Release();
}

inline void CMutex::
CLockMutex::Release()
{
	if (m_Mtx.IsValid()) 
		const_cast<CMutex &>(m_Mtx).Unlock(); 
}

// CSyncMonitor ist eine BasisKlasse für alle Klassen, die einen ZugriffsSchutz im 
// Sinne des Schutzes vor gleichzeitigem Zugriff aus mehreren Thread's eines
// Prozesses heraus benötigen.
// Sie ist eine WrapperKlasse, die die Erzeugung der beiden für das Verwalten 
// eines Mutex's notwendigen Klassen CMutex und CLockMutex vereinfacht.
class _CTR_ENTRY32 CSyncMonitor 
{
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

#endif // _SYNCTHRDCS_HXX
