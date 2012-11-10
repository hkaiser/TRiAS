// Routinen, welche an eine andere Extension gelinkt werden, um die 
// exportierten Funktionen aus der Extension VISOBJ.EXT sicher zug‰nglich
// zu machen.
// File: VISSTUB.CXX

#if defined(__cplusplus)
extern "C" {
#endif

#include <xtension.h>
#include <xtensnx.h>

#if defined(__cplusplus)
}
#endif

#include <dllbind.hxx>		// DLL anbinden

#if defined(__cplusplus)
extern "C" {
#endif

#include "bildstub.hxx"		// Funktionsprototypen


typedef bool FAR (PASCAL *CHANGEVISINFOPROC)(HANDLEVISINFO *);

const char *pExtName = "VISIBJ.EXT";		// Name der Erweiterung
const char *pChangeVisInfoName = "CHANGEVISINFO";	// Namen der Funktionen

// Vorgeben einer Objektbezogenen Visualisierung fÅr ein Objekt ---------------
bool ChangeVisInfo (HANDLEVISINFO *pHVI)
{
// 1. TRIAS auffordern, die Erweiterung VISOBJ.EXT zu laden
LOADEXTENSIONEX LE;

	memset (&LE, '\0', sizeof(LOADEXTENSION));
	LE.m_pName = pExtName;		// Name der Erweiterung
	LE.m_iMode = LEInitOnly;	// mindestens initialisieren
	LE.m_fGlobal = false;		// nicht global laden
	
	if (!DEX_LoadExtensionEx (LE)) 
		return false;		// Fehler beim laden der Erweiterung
		
// 2. Erweiterung direkt binden und Funktion rufen
bool iResult = false;
DLLBind Ext (pExtName);		// Erweiterung binden
SHOWIMAGEPROC pFcn = (CHANGEVISINFOPROC)Ext.GetProcAddress (pChangeVisInfoName);

// Funktion rufen
	if (pFcn) iResult = pFcn (pHVI);
		
// Erweiterung wieder freigeben	
	DEX_UnLoadExtensionEx (LE);
		
return iResult;		// Funktion nicht gefunden
}


#if defined(__cplusplus)
}
#endif

