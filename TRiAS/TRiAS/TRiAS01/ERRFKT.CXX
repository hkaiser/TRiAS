// Memberfunktionen und 'C'-Schnittstelle fuer Fehlerbehandlung
// File: ERRFKT.CXX

#include "trias01p.hxx"

#include <containr.hxx>

#include "errfkt.hxx"
#include "syncdb.hxx"

#include <Com/PerfMonContext.h>
#include <Com/PerfMonInstanceMap.h>

#include "PerfCounters.h"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

static ErrorTree *s_pET = NULL;
extern "C" HINSTANCE g_hInstance;

// 'C' - Schnittstelle --------------------------------------------------------
extern "C" 
int FUNCTYPE EXPORT01 err_install (long err_code, int (*error_func)(int,int,...), 
					 int (* *old_errfunc)(int,int,...))
{
	return ExtErrInstall (err_code, error_func, old_errfunc, NULL);
}

extern "C" 
int FUNCTYPE EXPORT01 ExtErrInstall (
	long err_code, int (*error_func)(int,int,...), int (* *old_errfunc)(int,int,...), void *pData)
{
	SYNC_DBACCESS_EX (g_pDbMutex);

ErrCode RC;
int (*oldfunc)(int,int,...);

// wenn Baum nicht existiert, dann Baum anlegen
	DBASSERT(CreateErrorTree());

// nachsehen, ob dieser Fehler bereits installiert ist
	oldfunc = E_DEFAULT;	// war default voreinstellen

// neue Fehlerbehandlung einstellen
	switch (s_pET -> GetMode (err_code)) {
	case EMDefault:		// keine Behandlung eingestellt
	// neuen Mode einstellen
		if (error_func != E_DEFAULT) {
		// nicht default einstellen
			DBASSERT (s_pET -> InstallHandler (err_code, error_func, pData));
		}
		break;

	case EMIgnore:		// Fehler wird derzeit ignoriert
		oldfunc = E_IGNORE;
		if (error_func != E_IGNORE) {
		// alten Mode weglöschen
			s_pET -> RemoveEntry (err_code);
		// ggf. neuen Mode setzen	
			if (error_func != E_DEFAULT) {
				DBASSERT (s_pET -> InstallHandler (err_code, error_func, pData));
			}
		}
		break;

	case EMHandler:		// z.Zt Handler eingestellt
	// alten Handler rauslöschen
		oldfunc = s_pET -> RemoveEntry (err_code);
	// ggf. neuen Handler installieren
		if (error_func != E_DEFAULT) {
			DBASSERT (s_pET -> InstallHandler (err_code, error_func, pData));
		}
		break;

	default:
		TX_ASSERT(false);
		break;
	}

// wenn kein Element mehr da ist, dann Baum freigeben
	if (s_pET -> Count() == 0) 
		ReleaseErrorTree();

	if (old_errfunc != NULL)
		*old_errfunc = oldfunc;

	return (int)EC_OKAY;
}

// den angelegten Baum wieder freigeben ---------------------------------------
extern "C" 
BOOL FUNCTYPE EXPORT01 ReleaseErrorTree (void)
{
	if (s_pET != NULL) {
		delete s_pET;
		s_pET = NULL;
		return true;
	}
	return false;
}

// wenn Baum nicht existiert, dann Baum anlegen
extern "C" 
int FUNCTYPE EXPORT01 CreateErrorTree()
{
#if defined(_USE_PERFMON_COUNTERS)
// Performance counter environment initialisieren
	StartPerfCounters (g_hInstance);
#endif // defined(_USE_PERFMON_COUNTERS)

	if (s_pET == NULL) {
		s_pET = new ErrorTree();
		if (s_pET == NULL) 
			return db_error (EC_NOMEMORY, RC_ErrInstall);
	}
	return S_OKAY;
}

// liefert aktuellen BehandlungsMode ------------------------------------------
extern "C" 
long FUNCTYPE EXPORT01 err_type (long ErrorCode) 
{
// wenn kein Baum existiert, dann E_DEFAULT melden
	if (s_pET == NULL) return (long)E_DEFAULT;

	switch (s_pET -> GetMode (ErrorCode)) {	// ansonsten Mode liefern
	case EMDefault:	return (long)E_DEFAULT;
	case EMIgnore:	return (long)E_IGNORE;
	case EMHandler:	return -1L;
	default:
		TX_ASSERT(false);
		return -1L;
	}
}

// liefert Handler, nur verwenden, wenn wirklich Handler installiert ist ------
extern "C" 
int (* EXPORT01 err_func (long ErrorCode))(int,int,...)
{
// wenn kein Baum existiert, dann Fehlermeldung
	if (s_pET == NULL) {
		db_error (WC_NOTFOUND, RC_ErrorFunc);
		return NULL;
	}
	return s_pET -> GetFunc (ErrorCode);	// ansonsten Funktion liefern
}

extern "C" 
void * FUNCTYPE EXPORT01 err_data (long ErrorCode) 
{
// wenn kein Baum existiert, dann Fehlermeldung
	if (s_pET == NULL) {
		db_error (WC_NOTFOUND, RC_ErrorFunc);
		return NULL;
	}
	return s_pET -> GetData (ErrorCode);	// ansonsten Funktion liefern
}

// Memberfunktionen für Fehlerbehandlung Baum ---------------------------------
ErrorHandler::ErrorHandler (long ErrorCode, int (*NewMode)(int,int,...), void *pData)
{
	_ErrCode = ErrorCode;
	_pData = pData;
	if ((_ActFunc = NewMode) != NULL)
		_EM = EMHandler;
	else
		_EM = EMIgnore;
}

// Zugriffsfunktionen für Baum ------------------------------------------------
void *GetErrorCode (void *pObj) 
{
	return & (((ErrorHandler *)pObj) -> _ErrCode);
}

int CmpErrorCodes (void *pObj1, void *pObj2) 
{
long l1 = ((ErrorHandler *)pObj1) -> _ErrCode;
long l2 = ((ErrorHandler *)pObj2) -> _ErrCode;

	if (l1 > l2) return 1;
	if (l1 < l2) return -1;
	return 0;
}

static const wchar_t g_cbErrorCounters[] = L"ErrorCounters";

RT_PERFINSTANCEDATA_ENTRY(ErrorTree, g_cbErrorCounters);

// Memberfunktionen für VerwaltungsBaum ---------------------------------------
#if defined(_IMPLEMENT_ERRTREE_AS_TREE)
ErrorTree::ErrorTree (void)
   : COptTree (GetErrorCode, CmpErrorCodes, CFAutoDelete)
{
	// nothing else to do
}
#else
ErrorTree::ErrorTree (void)
//   : CHashTable (GetErrorCode, CmpErrorCodes, HashErrorCodes, ERRORTREE_BUCKETS, CFAutoDelete)
{
#if defined(_USE_PERFMON_COUNTERS)
	PerfMon::GetPerfCounter (g_cbErrorCounters, L"ErrorTree", L"Installs", m_Installs.ppi());
	PerfMon::GetPerfCounter (g_cbErrorCounters, L"ErrorTree", L"Removes", m_Removes.ppi());
	PerfMon::GetPerfCounter (g_cbErrorCounters, L"ErrorTree", L"ActCount", m_ActCount.ppi());
#endif // defined(_USE_PERFMON_COUNTERS)
}

//uint HashErrorCodes (void *pEntry)
//{
//	return *reinterpret_cast<long *>(pEntry);
//}
#endif // defined(_IMPLEMENT_ERRTREE_AS_TREE)

ErrorTree::~ErrorTree (void)
{
	EveryDelete ();
}

//void EXPORT01 ErrorTree::UserDelete (void *pObj) 
//{
//	((ErrorHandler *)pObj) -> ~ErrorHandler ();
//}

ErrCode ErrorTree::InstallHandler (long ErrorCode, int (*NewFunc)(int,int,...), void *pData)
{
//ErrorHandlerCreator EHCr (*this);
//
//	if (ContCreate (EHCr, ErrorHandler)(ErrorCode, NewFunc, pData) == NULL) 
//		return (ErrCode)db_error (EC_NOMEMORY, RC_InstallHandler1);
	push_front(ErrorHandler(ErrorCode, NewFunc, pData));

#if defined(_USE_PERFMON_COUNTERS)
	m_Installs -> Step();
	m_ActCount -> Step();
#endif // defined(_USE_PERFMON_COUNTERS)
	return EC_OKAY;
}

int (*ErrorTree::RemoveEntry (long ErrorCode))(int,int,...) 
{
//CTable t(*this);
//BOOL toDelete = false;
int (*oldFunc)(int,int,...) = NULL;
//
//	if (t.Find (&ErrorCode)) {
//	ErrorHandlerLock l(t);
//
//		if (l) {
//			toDelete = true;
//			oldFunc = l -> ActFunc();
//		}
//	}
//	if (toDelete) 
//		t.Delete();

	for (iterator it = begin(); it != end(); ++it) {
		if (ErrorCode == (*it).ErrorCode()) {
			oldFunc = (*it).ActFunc();
			erase (it);
			break;
		}
	}

#if defined(_USE_PERFMON_COUNTERS)
	m_Removes -> Step();
	m_ActCount -> Increment(-1);
#endif // defined(_USE_PERFMON_COUNTERS)
	return oldFunc;
}
	
ErrorMode ErrorTree::GetMode (long ErrorCode)
{
//CTable t(*this);
//
//	if (t.Find (&ErrorCode)) {
//	ErrorHandlerLock l(t);
//
//		if (l) return l -> ActMode();
//	}
	for (iterator it = begin(); it != end(); ++it) {
		if (ErrorCode == (*it).ErrorCode()) {
			return (*it).ActMode();
		}
	}
	return EMDefault;	// nichts gefunden, also default handling
}

int (*ErrorTree::GetFunc (long ErrorCode))(int,int,...)
{
//CTable t(*this);
//
//	if (t.Find (&ErrorCode)) {
//	ErrorHandlerLock l(t);
//
//		if (l) return l -> ActFunc();
//	}
	for (iterator it = begin(); it != end(); ++it) {
		if (ErrorCode == (*it).ErrorCode()) {
			return (*it).ActFunc();
		}
	}
	return NULL;		// nichts gefunden, NULL liefern
}

void *ErrorTree::GetData (long ErrorCode)
{
//CTable t(*this);
//
//	if (t.Find (&ErrorCode)) {
//	ErrorHandlerLock l(t);
//
//		if (l) return l -> pData();
//	}
	for (iterator it = begin(); it != end(); ++it) {
		if (ErrorCode == (*it).ErrorCode()) {
			return (*it).pData();
		}
	}
	return NULL;	// nichts gefunden, also NULL liefern
}
