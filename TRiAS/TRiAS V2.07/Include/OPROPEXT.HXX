// Erweitirung, die ObjPropertyFunc's unterstÅtzt -----------------------------
// File: OPROPEXT.HXX

#if !defined(_OPROPEXT_HXX)
#define _OPROPEXT_HXX

typedef char * OBJPROPFUNC (long, char *, short);
typedef char * (*OBJPROPPROC)(long, char *, short);
typedef char * OBJPROPEXFUNC (long, char *, short, DWORD);
typedef char * (*OBJPROPEXPROC)(long, char *, short, DWORD);

typedef void OBJPROPDELFUNC (DWORD eData);
typedef void (*OBJPROPDELPROC)(DWORD eData);

extern "C" {
	typedef char *(CALLBACK *OBJPROPCALLBACK)(long, char *, short);
	typedef char *(CALLBACK *OBJPROPEXCALLBACK)(long, char *, short, DWORD);
	typedef void (CALLBACK *OBJPROPDELCALLBACK)(DWORD eData);
}

const short OBJPROPFUNCNAMELEN	= 32;

#if !defined(NOOBJPROPLIST)

enum ObjPropType {
	OProp = 1,
	OPropEx = 2,
};

class ObjProp {
private:
	char _pFName[OBJPROPFUNCNAMELEN+1];
	short _iFuncID;
	OBJPROPPROC _pFunc;

protected:
	OBJPROPPROC F (void) { return _pFunc; }

public:
		ObjProp (const char *pFName, short iFuncID, OBJPROPPROC pFunc);
	virtual	~ObjProp (void);

	char *FName (void) const { return (char *)_pFName; }
	short FuncID (void) { return _iFuncID; }

virtual char *InvokeFunc (long lONr, char *pBuffer, short iLen);
virtual ObjPropType isA (void);
virtual char *GetHelpText (char *pBuffer, short iLen);

friend void *GetFuncIDPtr (void *);
};

class ObjPropEx : public ObjProp {
private:
	DWORD _Data;

public:
		ObjPropEx (const char *pFName, short iFuncID, 
			   OBJPROPEXPROC pFunc, DWORD extData = 0);
		~ObjPropEx (void);

	DWORD eData (void) const { return _Data; }
	char *InvokeFunc (long lONr, char *pBuffer, short iLen);
	ObjPropType isA (void);
	char *GetHelpText (char *pBuffer, short iLen);
};

// Baum enth‰lt alle zur Zeit installierten OPFs ------------------------------
class ObjPropList : public CTree {
protected:
	void UserDelete (void *pObj);

public:
		ObjPropList (void);
		~ObjPropList (void);
};
DeclareLock (ObjPropList, ObjProp);

#endif // NOOBJPROPLIST


// Erweiterung, die zus‰tzlich ObjPropertyFunc's unterst¸tzt ------------------
#if !defined(NOOBJPROPEXT)

class ObjPropList;

#if !defined(WIN32)
class ObjectPropertyExtension : virtual public TriasExtension {
#else
class ObjectPropertyExtension : public TriasExtension {
#endif
private:
	ObjPropList *_pOPList;		// Liste aller registrierten OPFunc's
	short _iFuncIDCnt;		// eindeutiger ID, der Funktionen

protected:
// eigener EventDispatcher, der die ObjPropMessages abf‰ngt
	LRESULT Dispatch (HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam);

	Bool EnumObjProp (ENUMOBJPROPDATA *);
	char *InvokeObjPropFunc (INVOKEOBJPROPDATA *);
	char *GetHelpText (GETHELPTEXTDATA *);
	
public:
		ObjectPropertyExtension (UINT iMenuID = 0, 	// HauptMenu
					 UINT iORMenuID = 0	// ObjRechMenu
					);
		~ObjectPropertyExtension (void);

// Memberfunktionen
	short AddPropertyFunction (const char *pFuncName, 	// Funktionsbezeichnung
				   OBJPROPPROC pFunc);		// Funktion selbst
	short AddPropertyFunctionEx (const char *pFuncName, 	// Funktionsbezeichnung
				     OBJPROPEXPROC pFunc,	// Funktion selbst
				     DWORD eData = 0);		// zus‰tzliche Daten

// Freigeben einer/aller OPFs
	Bool RemovePropertyFunction (short iFuncID);
	Bool RemoveAllPropertyFunctions (void);		

// Freigeben einer/aller OPFs, wobei pDelF mit eData gerufen wird
	Bool RemovePropertyFunctionEx (short iFuncID, OBJPROPDELPROC pDelF);
	Bool RemoveAllPropertyFunctionsEx (OBJPROPDELPROC pDelF);
};

#endif // NOOBJPROPEXT

#endif // _OPROPEXT_HXX
