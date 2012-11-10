// Routinen zu ObjectPropertyExtension ----------------------------------------
// File: OPROPEXT.CXX

extern "C" {
	#include <windows.h>
	#include <stdlib.h>
	#include <string.h>

	#include <protos.h>

	#include <xtension.h>
	#include <xtensnx.h>
	#include <xtensnxx.h>

	#include <resstrg.h>
}

#include <commonvu.hxx>
#define NOWODELETE
#include <containr.hxx>

#include <errcodes.hxx>
#include <textensn.hxx>

#include <opropext.hxx>

// Konstruktor/Destruktor -----------------------------------------------------
ObjectPropertyExtension :: ObjectPropertyExtension (UINT iMenuID, UINT iORMenuID)
			 : TriasExtension (iMenuID, iORMenuID)
{
	_pOPList = new ObjPropList ();
	_iFuncIDCnt = 0;
}

ObjectPropertyExtension :: ~ObjectPropertyExtension (void)
{
	DELETE (_pOPList);
}

// Installieren einer normalen OPF --------------------------------------------
short ObjectPropertyExtension :: AddPropertyFunction (
				 const char *pFName, OBJPROPPROC pFunc)
{
	if (_pOPList == NULL) return -1;

ObjPropCreator OPCr (*_pOPList);

	Create (OPCr, ObjProp)(pFName, ++_iFuncIDCnt, pFunc);

return _iFuncIDCnt;	// ID liefern
}

// Installieren einer erweiterten OPF -----------------------------------------
short ObjectPropertyExtension :: AddPropertyFunctionEx (
					const char *pFName, 
					OBJPROPEXPROC pFunc,
					DWORD eData)
{
	if (_pOPList == NULL) return -1;

ObjPropCreator OPCr (*_pOPList);

	Create (OPCr, ObjPropEx)(pFName, ++_iFuncIDCnt, pFunc, eData);

return _iFuncIDCnt;	// ID liefern
}

// Freigeben einer installierten OPF ------------------------------------------
Bool ObjectPropertyExtension :: RemovePropertyFunction (short iFuncID)
{
	if (_pOPList == NULL) return FALSE;

CTable t(*_pOPList);

	if (t.Find (&iFuncID)) {
		t.Delete();
		return TRUE;
	}

return FALSE;
}

// Freigeben aller installiereten OPFs ----------------------------------------
Bool ObjectPropertyExtension :: RemoveAllPropertyFunctions (void)
{
	if (_pOPList == NULL) return FALSE;

CTable t(*_pOPList);

	t.First();
	while (t.Valid()) t.Delete();		// alle l”schen

return TRUE;
}

// Freigeben einer erweiterten installierten OPF ------------------------------
extern "C" {

inline void OPDelF (OBJPROPDELPROC pF, DWORD eData)
{
	((OBJPROPDELCALLBACK)pF)(eData);
}

} 	// extern "C"


Bool ObjectPropertyExtension :: RemovePropertyFunctionEx (
					short iFuncID, 
					OBJPROPDELPROC pDelF)
{
	if (_pOPList == NULL) return FALSE;

CTable t(*_pOPList);

	if (t.Find (&iFuncID)) {
		{
		ObjPropLock l(t);

			if (l -> isA() == OPropEx && pDelF)
				OPDelF (pDelF, ((ObjPropEx *)(ObjProp *)l) -> eData());
		}
		t.Delete();
		return TRUE;
	}

return FALSE;
}

// Freigeben aller installiereten OPFs ----------------------------------------
Bool ObjectPropertyExtension :: RemoveAllPropertyFunctionsEx (
					OBJPROPDELPROC pDelF)
{
	if (_pOPList == NULL) return FALSE;

CTable t(*_pOPList);

	t.First();
	while (t.Valid()) {
		{
		ObjPropLock l(t);

			if (l -> isA() == OPropEx && pDelF)
				OPDelF (pDelF, ((ObjPropEx *)(ObjProp *)l) -> eData());
		}
		t.Delete();		// alle l”schen
	}

return TRUE;
}

// lokaler EventDispatcher ----------------------------------------------------
LRESULT ObjectPropertyExtension :: Dispatch (HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam)
{
	switch (wMsg) {
	case DEX_CAPABILITIES:
		if (wParam == DEXCAP_OBJPROPFUNCS && _pOPList)
			return _pOPList -> Count();

	case DEX_ENUMEXTENSIONPROP:
		return (LRESULT)EnumObjProp ((ENUMOBJPROPDATA *)lParam);

	case DEX_INVOKEOBJPROPFUNC:
		return (LRESULT)InvokeObjPropFunc ((INVOKEOBJPROPDATA *)lParam);
		
	case DEX_OBJPROPGETHELPTEXT:
		return (LRESULT)GetHelpText ((GETHELPTEXTDATA *)lParam);
	}

// für alles was übrig ist, übergeordnete Funktion rufen
return TriasExtension :: Dispatch (hWnd, wMsg, wParam, lParam);
}

// Aufzählen aller derzeit installiereten OPFs --------------------------------
extern "C" {

inline BOOL CALLBACK pCallBack (ENUMOBJPROPPROC pF, const char *pFN,
				short iFuncID, BOOL iNotLast, void *pData)
{
	return ((ENUMOBJPROPCALLBACK)pF)(pFN, iFuncID, iNotLast, pData);
}

} 	// extern "C" 

Bool ObjectPropertyExtension :: EnumObjProp (ENUMOBJPROPDATA *pEOPD)
{
	if (_pOPList == NULL || pEOPD == NULL) return FALSE;

CTable t(*_pOPList);

	for (t.First(); t.Valid(); ) {
	ObjPropLock l(t);
	Bool iNotLast = t.Next();

		if (!l) continue;

	Bool iResult = pCallBack (pEOPD -> pFunc, l -> FName(), l -> FuncID(), 
				  iNotLast, pEOPD -> pPtr);

		if (iResult == FALSE) return FALSE;	// abgebrochen
	}

return TRUE;	// ok durchgelaufen
}

// Ausführen einer der derzeit installierten OPFs -----------------------------
char *ObjectPropertyExtension :: InvokeObjPropFunc (INVOKEOBJPROPDATA *pIOPD)
{
	if (_pOPList == NULL || pIOPD == NULL) return FALSE;

CTable t(*_pOPList);

	if (t.Find (&pIOPD -> iFuncID)) {
	ObjPropLock l(t);

		if (l) return l -> InvokeFunc (pIOPD -> lONr, pIOPD -> pBuff, 
					       pIOPD -> iBuffLen);
	}

return NULL;
}

// Abfragen des HilfeTextes für eine OPF --------------------------------------
char *ObjectPropertyExtension :: GetHelpText (GETHELPTEXTDATA *pGHTD)
{
	if (_pOPList == NULL || pGHTD == NULL) return FALSE;

CTable t(*_pOPList);

	if (t.Find (&pGHTD -> iFuncID)) {
	ObjPropLock l(t);

		if (l) return l -> GetHelpText (pGHTD -> pBuff, pGHTD -> iBuffLen);
	}

return NULL;
}

// ----------------------------------------------------------------------------
// Funktionen für ObjProp -----------------------------------------------------
void *GetFuncIDPtr (void *pObj)		// ZugriffsFunktion für Baum
{
	return & ((ObjProp *)pObj) -> _iFuncID;
}

// Einfache ObjectPropertyFunction (OPF) --------------------------------------
ObjProp :: ObjProp (const char *pFName, short iFuncID, OBJPROPPROC pFunc)
{
// Member initialisieren
	strncpy (_pFName, pFName, OBJPROPFUNCNAMELEN);
	_pFName[OBJPROPFUNCNAMELEN] = '\0';
	_iFuncID = iFuncID;
	_pFunc = pFunc;
}

ObjProp :: ~ObjProp (void)
{
	// nothing to do
}

ObjPropType ObjProp :: isA (void) { return OProp; }	// liefert Typ

extern "C" {		// HilfsFunktionen, um den Compiler ruhig zu stellen

inline char *OPCallBack (OBJPROPPROC pF, long lONr, char *pB, short iLen)
{
	return ((OBJPROPCALLBACK)pF)(lONr, pB, iLen);
}

inline char *OPExCallBack (OBJPROPEXPROC pF, long lONr, char *pB, 
			   short iLen, DWORD eData)
{
	return ((OBJPROPEXCALLBACK)pF)(lONr, pB, iLen, eData);
}

}	// extern "C"

// Abarbeiten dieser OPF ------------------------------------------------------
char *ObjProp :: InvokeFunc (long lONr, char *pBuffer, short iLen)
{
	if (F()) return OPCallBack (F(), lONr, pBuffer, iLen);

return NULL;
}


// liefern des HilfeTextes ----------------------------------------------------
char *ObjProp :: GetHelpText (char *pBuffer, short iLen)
{
	if (F()) return OPCallBack (F(), OBJPROP_GETHELPTEXT, pBuffer, iLen);

return NULL;
}


// Erweiterte OPF, erlaubt zusätzliche Daten zu übergeben ---------------------
ObjPropEx :: ObjPropEx (const char *pFName, short iFuncID, 
			OBJPROPEXPROC pFunc, DWORD extData)
	   : ObjProp (pFName, iFuncID, (OBJPROPPROC)pFunc)
{
// Member initialisieren
	_Data = extData;
}

ObjPropEx :: ~ObjPropEx (void)
{
	// nothing to do
}

ObjPropType ObjPropEx :: isA (void) { return OPropEx; }	// liefert Typ

// Abarbeiten dieser OPF ------------------------------------------------------
char *ObjPropEx :: InvokeFunc (long lONr, char *pBuffer, short iLen)
{
	if (F()) return OPExCallBack ((OBJPROPEXPROC)F(), lONr, 
				      pBuffer, iLen, _Data);

return NULL;
}

// Abfragen des HilfeTextes ---------------------------------------------------
char *ObjPropEx :: GetHelpText (char *pBuffer, short iLen)
{
	if (F()) return OPExCallBack ((OBJPROPEXPROC)F(), OBJPROP_GETHELPTEXT, 
				      pBuffer, iLen, _Data);

return NULL;
}

// ----------------------------------------------------------------------------
// Baum, der OPFs enthält -----------------------------------------------------
ObjPropList :: ObjPropList (void)
	     : CTree (GetFuncIDPtr, IntCmp)
{
	// nothing else to do
}

ObjPropList :: ~ObjPropList (void)
{
	EveryDelete();
}

void ObjPropList :: UserDelete (void *pObj)
{
	((ObjProp *)pObj) -> ObjProp :: ~ObjProp ();
}
