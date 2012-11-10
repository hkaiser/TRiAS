// File: DOFILER.CXX

#include "pheader.h"

#include <dofiler.h>   		// zugeh. Header
#include <dllbindx.hxx>	  	// DLL anbinden

typedef BOOL (FAR PASCAL * doFileReProc)(char *pFileName, BOOL bParseOnly = FALSE);

const char* pExtName = "KOMPLEXR.EXT";			  // Name der Erweiterung
const char* pProcName = "DOFILERECHERCHE";		  // Namen der Funktion

// Puffer bilden
BOOL FAR PASCAL __export doFileRechercheCall (LPSTR pScriptName, BOOL Parse)
{
// 1. TRIAS auffordern, die Erweiterung BUFFER.EXT zu laden
LOADEXTENSIONEX LE;

		memset (&LE, '\0', sizeof(LOADEXTENSIONEX));
		LE.m_pName = pExtName;		  // Name der Erweiterung
		LE.m_iMode = LEInitOnly;		// mindestens initialisieren
		LE.m_fGlobal = FALSE;		   // nicht global laden
		
		if (!DEX_ExternalLoadExtensionEx (LE)) 
				return FALSE;		   // Fehler beim Laden der Erweiterung
				
// 2. Erweiterung direkt binden und Funktion rufen
BOOL iResult = FALSE;
CDllBindX Ext (pExtName);		 // Erweiterung binden
		doFileReProc pFcn = (doFileReProc)Ext.GetProcAddress (pProcName);

// Funktion rufen
   if (pFcn) 
				iResult = pFcn (pScriptName, Parse);
				
// Erweiterung wieder freigeben 
		DEX_ExternalUnLoadExtensionEx (LE);
				
		return iResult;		 // Funktion nicht gefunden
}


