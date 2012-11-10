// Klassendefinition fuer Fehlerbehandlung ------------------------------------
// File: ERRFKT.HXX

#include <ospace/std/list>
#include <copttree.hxx>

#if defined(_USE_PERFMON_COUNTERS)
#include <Com/PerfMonInstanceMap.h>
#endif // defined(_USE_PERFMON_COUNTERS)

// mögliche FehlerbehandlungsModes
enum ErrorMode {
	EMDefault = 1,	// Fehler normal behandeln (Fehlermeldung)
	EMIgnore = 0,	// Fehler ignorieren
	EMHandler = 2,	// eigene Fehlerbehandlung
};

// Element, das im Baum hängt -------------------------------------------------
class ErrorHandler 
{
public:
private:
	long _ErrCode;		// FehlerCode
	ErrorMode _EM;		// aktueller FehlerbehandlungsMode
	int (*_ActFunc)(int,int,...);	// aktuelle BehandlungsRoutine
	void *_pData;		// zusätzliche Daten

public:
		ErrorHandler (long ErrorCode, int (*NewMode)(int,int,...) = NULL, void *pData = NULL);
		~ErrorHandler (void) {}

	long ErrorCode() { return _ErrCode; }
	int (*ActFunc (void))(int,int,...) { return _ActFunc; }
	ErrorMode ActMode (void) { return _EM; }
	void *pData (void) { return _pData; }

friend void *GetErrorCode (void *pObj);
friend int CmpErrorCodes (void *pObj1, void *pObj2);
#if !defined(_IMPLEMENT_ERRTREE_AS_TREE)
friend uint HashErrorCodes (void *pObj);
#endif // !defined(_IMPLEMENT_ERRTREE_AS_TREE)
};

#if defined(_IMPLEMENT_ERRTREE_AS_TREE)

class ErrorTree : 
	public COptTree
{
protected:
	void UserDelete (void *pObj);

public:
		ErrorTree (void);
		~ErrorTree (void);

	ErrCode InstallHandler (long ErrorCode, int (*NewFunc)(int,int,...), void *pData);
	int (*RemoveEntry (long ErrorCode))(int,int,...);

	ErrorMode GetMode (long ErrorCode);
	int (*GetFunc (long ErrorCode))(int,int,...);
	void *GetData (long ErrorCode);
};

#else

class ErrorTree : 
//	public CHashTable
	public list<ErrorHandler>
{
protected:
//	void UserDelete (void *pObj);

public:
		ErrorTree (void);
		~ErrorTree (void);

	ErrCode InstallHandler (long ErrorCode, int (*NewFunc)(int,int,...), void *pData);
	int (*RemoveEntry (long ErrorCode))(int,int,...);

	ErrorMode GetMode (long ErrorCode);
	int (*GetFunc (long ErrorCode))(int,int,...);
	void *GetData (long ErrorCode);

	void EveryDelete() { clear(); }
	size_t Count() { return size(); }

private:
#if defined(_USE_PERFMON_COUNTERS)
	__Interface<PerfMon::IPerfCounter> m_Installs;
	__Interface<PerfMon::IPerfCounter> m_Removes;
	__Interface<PerfMon::IPerfCounter> m_ActCount;
#endif // defined(_USE_PERFMON_COUNTERS)
};
#define ERRORTREE_BUCKETS	11		// Größe der Hashtabelle

#endif // defined(_IMPLEMENT_ERRTREE_AS_TREE)

//DeclareLock (ErrorTree, ErrorHandler);

