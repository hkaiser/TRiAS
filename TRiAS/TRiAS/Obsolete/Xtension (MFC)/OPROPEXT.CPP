// Routinen zu ObjectPropertyExtension ----------------------------------------
// File: OPROPEXT.CPP

#include <afxwin.h>

extern "C" {
	#include <xtension.h>
	#include <xtensnx.h> 
	#include <xtensnxx.h>
	#include <stdlib.h>
	#include <string.h>
	#include <protos.h>             
	#include <resstrg.h>            
}

#define NOWODELETE
#include <containr.hxx>
#include <xtsnmfc.hpp>
#include <errcodes.hxx>         

#include <opropext.hpp>

// Konstruktor/Destruktor -----------------------------------------------------
CObjectPropertyExtension :: CObjectPropertyExtension (UINT iMenuID, UINT iORMenuID)
			  : CTriasExtension (iMenuID, iORMenuID)
{
	m_pOPList = new CObjPropList ();
	m_iFuncIDCnt = 0;
}

CObjectPropertyExtension :: ~CObjectPropertyExtension (void)
{
	DELETE (m_pOPList);
}

// Installieren einer normalen OPF --------------------------------------------
short CObjectPropertyExtension :: AddPropertyFunction (
				  const char *pFName, OBJPROPPROC pFunc)
{
	if (m_pOPList == NULL) return -1;

CObjPropCreator OPCr (*m_pOPList);

	Create (OPCr, CObjProp)(pFName, ++m_iFuncIDCnt, pFunc);

return m_iFuncIDCnt;	// ID liefern
}

// Installieren einer erweiterten OPF -----------------------------------------
short CObjectPropertyExtension :: AddPropertyFunctionEx (
					const char *pFName, 
					OBJPROPEXPROC pFunc,
					DWORD eData)
{
	if (m_pOPList == NULL) return -1;

CObjPropCreator OPCr (*m_pOPList);

	Create (OPCr, CObjPropEx)(pFName, ++m_iFuncIDCnt, pFunc, eData);

return m_iFuncIDCnt;	// ID liefern
}

// Freigeben einer installierten OPF ------------------------------------------
Bool CObjectPropertyExtension :: RemovePropertyFunction (short iFuncID)
{
	if (m_pOPList == NULL) return FALSE;

CTable t(*m_pOPList);

	if (t.Find (&iFuncID)) {
		t.Delete();
		return TRUE;
	}

return FALSE;
}

// Freigeben aller installiereten OPFs ----------------------------------------
Bool CObjectPropertyExtension :: RemoveAllPropertyFunctions (void)
{
	if (m_pOPList == NULL) return FALSE;

CTable t(*m_pOPList);

	t.First();
	while (t.Valid()) t.Delete();		// alle löschen

return TRUE;
}

// Freigeben einer erweiterten installierten OPF ------------------------------
extern "C" {

inline void OPDelF (OBJPROPDELPROC pF, DWORD eData)
{
	((OBJPROPDELCALLBACK)pF)(eData);
}

} 	// extern "C"


BOOL CObjectPropertyExtension :: RemovePropertyFunctionEx (
					short iFuncID, 
					OBJPROPDELPROC pDelF)
{
	if (m_pOPList == NULL) return FALSE;

CTable t(*m_pOPList);

	if (t.Find (&iFuncID)) {
		{
		CObjPropLock l(t);

			if (l -> isA() == OPropEx && pDelF)
				OPDelF (pDelF, ((CObjPropEx *)(CObjProp *)l) -> eData());
		}
		t.Delete();
		return TRUE;
	}

return FALSE;
}

// Freigeben aller installiereten OPFs ----------------------------------------
BOOL CObjectPropertyExtension :: RemoveAllPropertyFunctionsEx (
					 OBJPROPDELPROC pDelF)
{
	if (m_pOPList == NULL) return FALSE;

CTable t(*m_pOPList);

	t.First();
	while (t.Valid()) {
		{
		CObjPropLock l(t);

			if (l -> isA() == OPropEx && pDelF)
				OPDelF (pDelF, ((CObjPropEx *)(CObjProp *)l) -> eData());
		}
		t.Delete();		// alle löschen
	}

return TRUE;
}

// lokaler EventDispatcher ----------------------------------------------------
LRESULT CObjectPropertyExtension :: Dispatch (HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam)
{
	switch (wMsg) {
	case DEX_CAPABILITIES:
		if (wParam == DEXCAP_OBJPROPFUNCS && m_pOPList)
			return m_pOPList -> Count();

	case DEX_ENUMEXTENSIONPROP:
		return (LRESULT)EnumObjProp ((ENUMOBJPROPDATA *)lParam);

	case DEX_INVOKEOBJPROPFUNC:
		return (LRESULT)InvokeObjPropFunc ((INVOKEOBJPROPDATA *)lParam);
		
	case DEX_OBJPROPGETHELPTEXT:
		return (LRESULT)GetHelpText ((GETHELPTEXTDATA *)lParam);		
	}               

// für alles was übrig ist, übergeordnete Funktion rufen
return CTriasExtension :: Dispatch (hWnd, wMsg, wParam, lParam);
}

// Aufzählen aller derzeit installiereten OPFs --------------------------------
extern "C" {

inline BOOL CALLBACK pCallBack (ENUMOBJPROPPROC pF, const char *pFN,
				short iFuncID, BOOL iNotLast, void *pData)
{
	return ((ENUMOBJPROPCALLBACK)pF)(pFN, iFuncID, iNotLast, pData);
}

} 	// extern "C" 

BOOL CObjectPropertyExtension :: EnumObjProp (ENUMOBJPROPDATA *pEOPD)
{
	if (m_pOPList == NULL || pEOPD == NULL) return FALSE;

CTable t(*m_pOPList);

	for (t.First(); t.Valid(); ) {
	CObjPropLock l(t);
	Bool iNotLast = t.Next();

		if (!l) continue;

	Bool iResult = pCallBack (pEOPD -> pFunc, l -> FName(), l -> FuncID(), 
				  iNotLast, pEOPD -> pPtr);

		if (iResult == FALSE) return FALSE;	// abgebrochen
	}

return TRUE;	// ok durchgelaufen
}

// Ausführen einer der derzeit installierten OPFs -----------------------------
char *CObjectPropertyExtension :: InvokeObjPropFunc (INVOKEOBJPROPDATA *pIOPD)
{
	if (m_pOPList == NULL || pIOPD == NULL) return FALSE;

CTable t(*m_pOPList);

	if (t.Find (&pIOPD -> iFuncID)) {
	CObjPropLock l(t);

		if (l) return l -> InvokeFunc (pIOPD -> lONr, pIOPD -> pBuff, 
					       pIOPD -> iBuffLen);
	}

return NULL;
}                         

// Abfragen des HilfeTextes für eine OPF --------------------------------------
char *CObjectPropertyExtension :: GetHelpText (GETHELPTEXTDATA *pGHTD)
{
	if (m_pOPList == NULL || pGHTD == NULL) return FALSE;

CTable t(*m_pOPList);

	if (t.Find (&pGHTD -> iFuncID)) {
	CObjPropLock l(t);

		if (l) return l -> GetHelpText (pGHTD -> pBuff, pGHTD -> iBuffLen);
	}

return NULL;
}

// ----------------------------------------------------------------------------
// Funktionen für ObjProp -----------------------------------------------------
void *GetFuncIDPtr (void *pObj)		// ZugriffsFunktion für Baum
{
	return & ((CObjProp *)pObj) -> m_iFuncID;
}

// Einfache ObjectPropertyFunction (OPF) --------------------------------------
CObjProp :: CObjProp (const char *pFName, short iFuncID, OBJPROPPROC pFunc)
{
// Member initialisieren
	strncpy (m_pFName, pFName, OBJPROPFUNCNAMELEN);
	m_pFName[OBJPROPFUNCNAMELEN] = '\0';
	m_iFuncID = iFuncID;
	m_pFunc = pFunc;
}

CObjProp :: ~CObjProp (void)
{
	// nothing to do
}

ObjPropType CObjProp :: isA (void) { return OProp; }	// liefert Typ

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
char *CObjProp :: InvokeFunc (long lONr, char *pBuffer, short iLen)
{
	if (F()) return OPCallBack (F(), lONr, pBuffer, iLen);

return NULL;
}

// liefern des HilfeTextes ----------------------------------------------------
char *CObjProp :: GetHelpText (char *pBuffer, short iLen)
{
	if (F()) return OPCallBack (F(), OBJPROP_GETHELPTEXT, pBuffer, iLen);

return NULL;
}

// Erweiterte OPF, erlaubt zusätzliche Daten zu übergeben ---------------------
CObjPropEx :: CObjPropEx (const char *pFName, short iFuncID, 
			OBJPROPEXPROC pFunc, DWORD extData)
	    : CObjProp (pFName, iFuncID, (OBJPROPPROC)pFunc)
{
// Member initialisieren
	m_Data = extData;
}

CObjPropEx :: ~CObjPropEx (void)
{
	// nothing to do
}

ObjPropType CObjPropEx :: isA (void) { return OPropEx; }	// liefert Typ

// Abarbeiten dieser OPF ------------------------------------------------------
char *CObjPropEx :: InvokeFunc (long lONr, char *pBuffer, short iLen)
{
	if (F()) return OPExCallBack ((OBJPROPEXPROC)F(), lONr, 
				      pBuffer, iLen, m_Data);

return NULL;
}

// Abfragen des HilfeTextes ---------------------------------------------------
char *CObjPropEx :: GetHelpText (char *pBuffer, short iLen)
{
	if (F()) return OPExCallBack ((OBJPROPEXPROC)F(), OBJPROP_GETHELPTEXT, 
				      pBuffer, iLen, m_Data);

return NULL;
}

// ----------------------------------------------------------------------------
// Baum, der OPFs enthält -----------------------------------------------------
CObjPropList :: CObjPropList (void)
	      : CTree (GetFuncIDPtr, IntCmp)
{
	// nothing else to do
}

CObjPropList :: ~CObjPropList (void)
{
	EveryDelete();
}

void CObjPropList :: UserDelete (void *pObj)
{
	((CObjProp *)pObj) -> CObjProp :: ~CObjProp ();
}
