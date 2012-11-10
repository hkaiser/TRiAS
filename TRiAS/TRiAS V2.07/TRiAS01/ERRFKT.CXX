// Memberfunktionen und 'C'-Schnittstelle fuer Fehlerbehandlung
// File: ERRFKT.CXX

#include "trias01p.hxx"

#include <containr.hxx>

#include "errfkt.hxx"
#include "syncdb.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

static ErrorTree *s_pET = NULL;

// 'C' - Schnittstelle --------------------------------------------------------
extern "C" {

extern "C" int FUNCTYPE EXPORT01 err_install (long err_code, int (*error_func)(int,int,...), 
					 int (* *old_errfunc)(int,int,...))
{
	return ExtErrInstall (err_code, error_func, old_errfunc, NULL);
}

extern "C" int FUNCTYPE EXPORT01 ExtErrInstall (long err_code, int (*error_func)(int,int,...), 
			    int (* *old_errfunc)(int,int,...), void *pData)
{
	SYNC_DBACCESS_EX (g_pDbMutex);

ErrCode RC;
int (*oldfunc)(int,int,...);

// wenn Baum nicht existiert, dann Baum anlegen
	if (s_pET == NULL) {
		s_pET = new ErrorTree ();
		if (s_pET == NULL) 
			return db_error (EC_NOMEMORY, RC_ErrInstall);
	}

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
extern "C" BOOL FUNCTYPE EXPORT01 ReleaseErrorTree (void)
{
	if (s_pET != NULL) {
		delete s_pET;
		s_pET = NULL;
		return true;
	}

return false;
}


// liefert aktuellen BehandlungsMode ------------------------------------------
extern "C" long FUNCTYPE EXPORT01 err_type (long ErrorCode) 
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
extern "C" int (* EXPORT01 err_func (long ErrorCode))(int,int,...)
{
// wenn kein Baum existiert, dann Fehlermeldung
	if (s_pET == NULL) {
		db_error (WC_NOTFOUND, RC_ErrorFunc);
		return NULL;
	}

return s_pET -> GetFunc (ErrorCode);	// ansonsten Funktion liefern
}

extern "C" void * FUNCTYPE EXPORT01 err_data (long ErrorCode) 
{
// wenn kein Baum existiert, dann Fehlermeldung
	if (s_pET == NULL) {
		db_error (WC_NOTFOUND, RC_ErrorFunc);
		return NULL;
	}

return s_pET -> GetData (ErrorCode);	// ansonsten Funktion liefern
}

}	// extern "C"

// Memberfunktionen für Fehlerbehandlung Baum ---------------------------------
ErrorHandler :: ErrorHandler (long ErrorCode, int (*NewMode)(int,int,...), void *pData)
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

// Memberfunktionen für VerwaltungsBaum ---------------------------------------
ErrorTree :: ErrorTree (void)
	   : CTree (GetErrorCode, CmpErrorCodes, CONTFLAG(CFSyncThreads|CFAutoDelete))
{
	// nothing else to do
}

ErrorTree :: ~ErrorTree (void)
{
	EveryDelete ();
}

void EXPORT01 ErrorTree :: UserDelete (void *pObj) 
{
	((ErrorHandler *)pObj) -> /*ErrorHandler ::*/ ~ErrorHandler ();
}

ErrCode ErrorTree :: InstallHandler (long ErrorCode, int (*NewFunc)(int,int,...), void *pData)
{
ErrorHandlerCreator EHCr (*this);

	if (Create (EHCr, ErrorHandler)(ErrorCode, NewFunc, pData) == NULL) 
		return (ErrCode)db_error (EC_NOMEMORY, RC_InstallHandler1);

return EC_OKAY;
}

int (*ErrorTree :: RemoveEntry (long ErrorCode))(int,int,...) 
{
CTable t(*this);
BOOL toDelete = false;
int (*oldFunc)(int,int,...) = NULL;

	if (t.Find (&ErrorCode)) {
	ErrorHandlerLock l(t);

		if (l) {
			toDelete = true;
			oldFunc = l -> ActFunc();
		}
	}
	if (toDelete) 
		t.Delete();

return oldFunc;
}
	
ErrorMode ErrorTree :: GetMode (long ErrorCode)
{
CTable t(*this);

	if (t.Find (&ErrorCode)) {
	ErrorHandlerLock l(t);

		if (l) return l -> ActMode();
	}

return EMDefault;	// nichts gefunden, also default handling
}

int (*ErrorTree :: GetFunc (long ErrorCode))(int,int,...)
{
CTable t(*this);

	if (t.Find (&ErrorCode)) {
	ErrorHandlerLock l(t);

		if (l) return l -> ActFunc();
	}

return NULL;		// nichts gefunden, NULL liefern
}

void *ErrorTree :: GetData (long ErrorCode)
{
CTable t(*this);

	if (t.Find (&ErrorCode)) {
	ErrorHandlerLock l(t);

		if (l) return l -> pData();
	}

return NULL;	// nichts gefunden, also NULL liefern
}
