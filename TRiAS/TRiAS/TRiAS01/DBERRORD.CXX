// Fehlerfunktion darf nicht in DLL eingebunden werden, da sie '_cdecl' ist
// File: DBERROR.C

#if defined(DLL) && defined (MSWIND)
#include <windows.h>
#include <stdarg.h>

#include <xtension.h>
#include <xtensnx.h>
#include <xtensnn.h>

#include <dbtypes.h>
#include <errdef.h>
#include <dioexter.h>
#include <errdb.h>
#include <protos.h>

char err_mess[_MAX_PATH +1]; // = "*** Datenbankfehler ***";
char war_mess[_MAX_PATH +1]; // = "*** Datenbankwarnung ***";
char err_head[_MAX_PATH +1]; // = "Fehlernummer (%d) in Routine %s - %s, %s";
char cbDBError[32]; // = "db_error";
char cbRecurse[32]; // = "Rekursiver Aufruf";

extern "C" 
int __cdecl db_error (int errcode, int routine, ...)   
{
DBASE *olddb;
static int db_error_Flag = FALSE;	// db_error ist aktiv
va_list paramlist;
int EC;

// bevor etwas losgeht, 'olddb' initialisieren
	olddb = NULL;

/* Fehlerbehandlungsart feststellen */
        switch (err_type ((INT)errcode)) {
        case E_DEFAULT:         /* keine gesonderte Fehlerbehandlung */
                break;          /* hier weitermachen */

        case E_IGNORE:          /* Fehler ignorieren */
                return (set_db_status (errcode));

        default:                /* eigene Fehlerbehandlungsroutine 
                                   installiert */
		{
		void *params;
		int (*func)(int,int,...) = err_func ((INT)errcode);
		long lResult = FALSE;

			if (func == NULL) 
				break;		// Fehler, also Standardbehandlung

			va_start (paramlist, routine);
			params = va_arg (paramlist, void *);
			va_end (paramlist);

		// wenn Fehler behandelt wurde, an dieser Stelle wieder raus
			if (__hWndM) {
				DEXN_ErrorMessage (lResult, errcode, routine, params);
			}
			switch (lResult) {
			case 1:		// ok, try again
				set_db_status (errcode);
				return S_OKAY;

			case 2:		// ok, do not try again
				return set_db_status (errcode);

			case 0:		// cancel, eingestellte Bearbeitung
		                return set_db_status ((*func)(errcode, routine, params, err_data (errcode)));
			}
		}
        }

/* alle Fehlermeldungen umlenken, wenn db_error rekursiv gerufen wird */
	if (db_error_Flag) {
		ErrorWindow (&olddb, err_mess, err_head, errcode, 
			     cbDBError,	cbRecurse, "");
	/* Fehler in Liste eintragen */
        	store_error (&errcode, routine);
		return (set_db_status (errcode));
	}

// die Welt von diesem Fehler in Kenntnis setzen
	if (__hWndM != 0) {
	void *params;
	long lResult = FALSE;

		va_start (paramlist, routine);
		params = va_arg (paramlist, void *);
		va_end (paramlist);

	// wenn Fehler behandelt wurde, an dieser Stelle wieder raus
		DEXN_ErrorMessage (lResult, errcode, routine, params);
		switch (lResult) {
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
	if (olddb != NULL) {
	        activate (olddb);
		olddb = NULL;
	}

/* Flag passivieren */
	db_error_Flag = FALSE;

/* db_status setzen */
return set_db_status (errcode);
}

extern "C"
void __cdecl ErrorWindow (DBASE **olddb, const char *lpszCaption, const char *lpszFormat, ...) 
{
char szText[160];

	if (olddb != NULL && *olddb != NULL) {
		activate (*olddb);	// alte DB wieder initialisieren
		*olddb = NULL;
	}

// Fenster anzeigen
	wvsprintf (szText, (LPSTR)lpszFormat, (LPSTR)(&lpszFormat+1));
	MessageBox (__hWndM, szText, lpszCaption, MB_OK | MB_ICONSTOP);
}

#endif // DLL && MSWIND
