/*-----------------------------------------------------------------------

File: CRCB.CXX (Implementation)

CRCB -
beihaltet globale Funktionen für die Initialisierung von CodeBase.

Erarbeitet: J. Benkenstein						 Stand am: 25. August 1993
------------------------------------------------------------------------*/

#include <d4all.h>
#ifdef WIN32
#include <bool.h>
#endif
#include <cxxtypes.hxx>

extern "C" {                       
#ifdef WIN32
	#include <objbase.h>		// LPSTORAGE 
#else
	#include <storage.h>		// LPSTORAGE 
#endif	
	#include <xtension.h>	   	// für DEX_Error ()
	#include <xtensnx.h>
}

#include <errcodes.hxx>			// Fehlerkodes
#include <dbtools.hxx>			// GetUseIndex ()
#include <crcb.hxx>				// zugeh. Header-File
#include <protos.h>				// DELETE_OBJ

// Die Funktion liefert einen Zeiger auf ein erzeugtes CodeBase-Objekt und
// setzt das Applikation-Handle.
// Bei einem Fehler ist der Zeiger gleich NULL.

static CodeBase *__pCodeBase = NULL;
static short __LockCnt = 0;

void __export ResetCodeBaseCnt (void)
{
	__LockCnt = 0;
	__pCodeBase = NULL;
}

CodeBase* __export CreateCodeBaseObj (HINSTANCE AppHandle)
{
	if (__pCodeBase != NULL) {
			__LockCnt++;
			return __pCodeBase;
	}

	CodeBase *pCodeBase = new CodeBase;

	if (pCodeBase) {
		pCodeBase -> hInst = (uint) AppHandle;
		pCodeBase -> date_format ("DD/MM/YY");
		__pCodeBase = pCodeBase;
		__LockCnt = 1;		   
				
		pCodeBase -> auto_open = GetUseIndex ();	// Production-Index autom. erzeugen
		pCodeBase -> read_lock = False;				// beim Lesen kein Locken
		return pCodeBase;
	} else {
		DEX_Error (RC_crCBobj, EC_NOMEMORY);
		return NULL;
	}
}

void __export DeleteCodeBaseObj (void)
{
	if (--__LockCnt == 0)
		DELETE_OBJ (__pCodeBase);
}

CodeBase* __export GetCodeBaseObj (void) 
{
	return __pCodeBase;
}

