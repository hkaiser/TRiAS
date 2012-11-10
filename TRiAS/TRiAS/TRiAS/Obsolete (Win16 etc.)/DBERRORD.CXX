// Fehlerfunktion darf nicht in DLL eingebunden werden, da sie '_cdecl' ist
// File: DBERROR.C

#if defined(DLL) && defined (MSWIND)
extern "C" {
	#include <windows.h>
	#include <stdarg.h>

	#include <xtension.h>
	#include <xtensnx.h>
	#include <xtensnn.h>

	#include <dbtypes.h>
	#include <errdef.h>
	#include <dioexter.h>
	#include <errdb.h>
	#include <dbproto.h>
	#include <protos.h>
}

#include <commonvu.hxx>
#include <errcodes.hxx>

extern "C" {

static char *err_mess = "*** Datenbankfehler ***";
static char *war_mess = "*** Datenbankwarnung ***";
static char *err_head = "Fehlernummer (%d) in Routine %s - %s. %s";

int _cdecl db_error (int errcode, int routine, ...)   
{
DBASE *olddb;
static int db_error_Flag = FALSE;	// db_error ist aktiv
va_list paramlist;
int EC;

	olddb = NULL;

/* Fehlerbehandlungsart feststellen */
        switch (err_type ((INT)errcode)) {
        case 1:         /* keine gesonderte Fehlerbehandlung */
                break;          /* hier weitermachen */

        case 0:          /* Fehler ignorieren */
                return (set_db_status (errcode));

        default:                /* eigene Fehlerbehandlungsroutine 
                                   installiert */
		{
		void *params;
		int (*func)(int,int,...) = err_func ((INT)errcode);
		long Result = 0;

			if (func == NULL) 
				break;		// Fehler, also Standardbehandlung

			va_start (paramlist, routine);
			params = va_arg (paramlist, void *);
			va_end (paramlist);

			DEXN_ErrorMessage (Result, errcode, routine, params);
			switch (Result) {
			case 1:		// ok, try again
				set_db_status (errcode);
				return S_OKAY;

			case 2:		// ok, do not try again
				return set_db_status (errcode);

			case 0:		// cancel
		                return set_db_status ((*func)(errcode, routine, params, err_data (errcode)));
			}
		}
        }

/* alle Fehlermeldungen umlenken, wenn db_error rekursiv gerufen wird */
	if (db_error_Flag) {
		ErrorWindow (NULL, err_mess, err_head, errcode, "db_error",
				"Rekursiver Aufruf", "");
	/* Fehler in Liste eintragen */
        	store_error (&errcode, routine);
		return (set_db_status (errcode));
	}

// die Welt von diesem Fehler in Kenntnis setzen
	{
	void *params;
	long Result = FALSE;

		va_start (paramlist, routine);
		params = va_arg (paramlist, void *);
		va_end (paramlist);

	// wenn Fehler behandelt wurde, an dieser Stelle wieder raus
		DEXN_ErrorMessage (Result, errcode, routine, params);
		switch (Result) {
		case 1:		// ok, try again
			set_db_status (errcode);
			return S_OKAY;

		case 2:		// ok, do not try again
			return set_db_status (errcode);

		case 0:		// cancel
			break;
		}
	}

/* Flag setzen ,daá Fehlerbehandlung aktiv ist */
	db_error_Flag = TRUE;
/* Metadatenbasis eroeffnen bzw. aktivieren */
        if (EC = act_meta (&olddb) != S_OKAY) return EC;
/* Ausgabe einer Fehlermeldung */
        error_message (&olddb, errcode, routine, "");
/* Fehler in Liste eintragen */
        store_error (&errcode, routine);
/* aktuelle DB wieder zuschalten */
	if (olddb) {
	        activate (olddb);
		olddb = NULL;
	}
/* Flag passivieren */
	db_error_Flag = FALSE;

/* db_status setzen */
return set_db_status (errcode);
}


void __cdecl ErrorWindow (DBASE * *olddb, const char  *lpszCaption, const char *lpszFormat, ...) {
char szText[160];

	if (olddb != NULL && *olddb != NULL) {
		activate (*olddb);
		*olddb = NULL;
	}
	wvsprintf (szText, (LPSTR)lpszFormat, (LPSTR)(&lpszFormat+1));
	MessageBox (__hWndM, szText, lpszCaption, MB_OK | MB_ICONSTOP);
}

} 	// extern "C"

#endif // DLL && MSWIND
