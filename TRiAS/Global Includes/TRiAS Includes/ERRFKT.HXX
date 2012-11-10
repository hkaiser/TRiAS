// Klassendefinition fuer Fehlerbehandlung ------------------------------------
// File: ERRFKT.HXX


// mögliche FehlerbehandlungsModes
enum ErrorMode {
	EMDefault = 1,	// Fehler normal behandeln (Fehlermeldung)
	EMIgnore = 0,	// Fehler ignorieren
	EMHandler = 2,	// eigene Fehlerbehandlung
};

// Element, das im Baum hängt -------------------------------------------------
class ErrorHandler {
public:
private:
	long _ErrCode;		// FehlerCode
	ErrorMode _EM;		// aktueller FehlerbehandlungsMode
	int (*_ActFunc)(int,int,...);	// aktuelle BehandlungsRoutine
	void *_pData;		// zusätzliche Daten

public:
		ErrorHandler (long ErrorCode, int (*NewMode)(int,int,...) = NULL, void *pData = NULL);
		~ErrorHandler (void) {}

	int (*ActFunc (void))(int,int,...) { return _ActFunc; }
	ErrorMode ActMode (void) { return _EM; }
	void *pData (void) { return _pData; }

friend void *GetErrorCode (void *pObj);
friend int CmpErrorCodes (void *pObj1, void *pObj2);
};

class ErrorTree : public CTree {
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
DeclareLock (ErrorTree, ErrorHandler);

