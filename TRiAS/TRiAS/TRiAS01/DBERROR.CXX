// Fehlerfunktion darf nicht in DLL eingebunden werden, da sie '_cdecl' ist
// File: DBERROR.C

#include "trias01p.hxx"

static char *err_mess = "*** Datenbankfehler ***";
static char *war_mess = "*** Datenbankwarnung ***";
static char *err_head = "Fehlernummer (%d) in Routine %s - %s";

int _cdecl
db_error (errcode, routine, params)   
int errcode;    /* Fehlercode */
int routine;    /* Routinennummer */
void *params;   /* optionale Parameter, die an Handler uebergeben werden */
{
DBASE *olddb;
static int db_error_Flag = FALSE;	// db_error ist aktiv
int EC;

/* Fehlerbehandlungsart feststellen */
        switch (err_type ((INT)errcode)) {
        case E_DEFAULT:         /* keine gesonderte Fehlerbehandlung */
                break;          /* hier weitermachen */

        case E_IGNORE:          /* Fehler ignorieren */
                return (set_db_status (errcode));

        default:                /* eigene Fehlerbehandlungsroutine 
                                   installiert */
                return (set_db_status ((*( (*err_func)((INT)errcode) ))(errcode, routine, params, err_data (errcode))));
        }

/* alle Fehlermeldungen umlenken, wenn db_error rekursiv gerufen wird */
	if (db_error_Flag) {
		ErrorWindow (err_mess, err_head, errcode, "db_error",
				"Rekursiver Aufruf");
	/* Fehler in Liste eintragen */
        	store_error (&errcode, routine);
		return (set_db_status (errcode));
	}
/* Flag setzen ,daá Fehlerbehandlung aktiv ist */
	db_error_Flag = TRUE;
/* Metadatenbasis eroeffnen bzw. aktivieren */
        if (EC = act_meta (&olddb) != S_OKAY) return (EC);
/* Ausgabe einer Fehlermeldung */
        error_message (errcode, routine, "");
/* Fehler in Liste eintragen */
        store_error (&errcode, routine);
/* aktuelle DB wieder zuschalten */
        activate (olddb);
/* Flag passivieren */
	db_error_Flag = FALSE;

/* db_status setzen */
return set_db_status (errcode);
}


void _cdecl
ErrorWindow (char _far *lpszCaption, const char _far *lpszFormat, ...) {
char szText[160];

	wvsprintf (szText, (LPSTR)lpszFormat, (LPSTR)(&lpszFormat+1));
	MessageBox (NULL, szText, lpszCaption, MB_OK | MB_ICONSTOP);
}

#endif // DLL && MSWIND
