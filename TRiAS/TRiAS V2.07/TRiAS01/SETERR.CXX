/* Fehlerbehandlungsroutine						 */
/* File: SETERR.C                                                       */

#include "trias01p.hxx"

#include <stdarg.h>
#include <errdb.h>
#include "syncdb.hxx"

#include "resource.h"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

int db_status = S_OKAY;

FLAG error_flag = TRUE;

static HPROJECT  errdb = (HPROJECT)0;
static FLAG tried = FALSE;

static ERROR_LIST FAR *irc_list = NULL;	/* Fehlervektor */
#ifdef MSWIND
static HANDLE hIrcList = NULL;
#endif
static int max_errors;                  /* Laenge des Fehlervektors */
static int actirc =	0;		/* naechster freier Fehlereintrag */

#ifdef MSWIND
extern "C" HINSTANCE g_hInstance;

char err_mess[_MAX_PATH +1]; // = "*** Datenbankfehler ***";
char war_mess[_MAX_PATH +1]; // = "*** Datenbankwarnung ***";
char err_head[_MAX_PATH +1]; // = "Fehlernummer (%d) in Routine %s - %s. %s";
char cbAuxError[_MAX_PATH +1]; // = "Fehlernummer (%d) in Routine %d. %s"
char cbFullList[32]; // = "Fehlerliste voll."
char cbDBError[32]; // = "db_error"
char cbRecurse[32]; // = "Rekursiver Aufruf"
char cbUnknown[32]; // = "unbekannt"
char cbOpenError[64]; // = "Fehler beim Eröffnen der Fehler-DB. "
char cbOpenErrorText[_MAX_PATH +1]; // = " Gemeldeter Fehler: %d in Routine %d."
#else
static char *err_mess = "\n*** Datenbankfehler";
static char *war_mess = "\n*** Datenbankwarnung";
static char *err_head = "%s (%d) in Routine %s:\n%s";
#endif

static char errordb_env[_MAX_PATH];		// Umgebungsvariable ERRORDB

static void FUNCTYPE open_meta (void);

extern short g_fCopyrightFlag;

/*
extern "C" 
long FUNCTYPE EXPORT01 seterr_ (long *errcode, long *routine, void *params)
{
	return ((long)db_error ((int)*errcode, (int)*routine, params));
}
*/

extern "C" 
int __cdecl EXPORT01 db_error (int errcode, int routine, ...)   
{
DBASE *olddb;
static int db_error_Flag = FALSE;	// db_error ist aktiv
va_list paramlist;

// bevor etwas losgeht, 'olddb' initialisieren
	olddb = NULL;

/* Fehlerbehandlungsart feststellen */
	switch (err_type ((INT)errcode)) {
	case E_DEFAULT:         /* keine gesonderte Fehlerbehandlung */
		break;          /* hier weitermachen */

	case E_IGNORE:          /* Fehler ignorieren */
		return (db_status = errcode);

	default:                /* eigene Fehlerbehandlungsroutine 
							   installiert */
		{
		void *params;
		int (*func)(int,int,...) = err_func ((INT)errcode);
		long Result = 0;

			if (func == NULL) 
				break;		// Fehler: Standardbehandlung

			va_start (paramlist, routine);
			params = va_arg (paramlist, void *);
			va_end (paramlist);

		// wenn Fehler behandelt wurde, an dieser Stelle wieder raus
			DEXN_ErrorMessage (Result, errcode, routine, params);
			switch (Result) {
			case 1:		// ok, try again
				db_status = errcode;
				return S_OKAY;

			case 2:		// ok, do not try again
				return (db_status = errcode);

			case 0:		// cancel
			// 950711: wenn die custom-Routine WC_RETURN liefert, dann
			// soll doch noch die Standardbearbeitung gerufen werden
				if (WC_RETURN == (*func)(errcode, routine, params, err_data (errcode))) {
					db_status = errcode;
					break;
				} 
				return (db_status = errcode);	// ok, bearbeitet
//	        return (db_status = (*func)(errcode, routine, params, err_data (errcode)));
			}
		}
	}

/* alle Fehlermeldungen umlenken, wenn db_error rekursiv gerufen wird */
	if (db_error_Flag) {
#ifdef MSWIND
		ErrorWindow (&olddb, err_mess, err_head, errcode, 
			     cbDBError,	cbRecurse, "");
#else
		fprintf (stderr, "%s (%d) in Routine db_error\n",
	                        err_mess, errcode, routine);
		fprintf (stderr, "Rekursiver Aufruf\n");
#endif
	/* Fehler in Liste eintragen */
		store_error (&errcode, routine);
		return (db_status = errcode);
	}

#if defined(MSWIND)
/* an dieser Stelle die Welt von dem Fehler in Kenntnis setzen */
	{
	void *params;
	long Result = FALSE;	// nicht behandelter Fehler

		va_start (paramlist, routine);
		params = va_arg (paramlist, void *);
		va_end (paramlist);

	// wenn Fehler behandelt wurde, an dieser Stelle wieder raus
		DEXN_ErrorMessage (Result, errcode, routine, params);
		switch (Result) {
		case 1:		// ok, try again
			db_status = errcode;
			return S_OKAY;

		case 2:		// ok, do nottry again
			return (db_status = errcode);

		case 0:	// cancel
			break;
		}
	}
#endif

// ab hier nur ein Thread, bitte
	SYNC_DBACCESS_EX (g_pDbMutex);

/* Flag setzen ,daß Fehlerbehandlung aktiv ist */
	db_error_Flag = TRUE;

/* Metadatenbasis eroeffnen bzw. aktivieren */
	if (act_meta (&olddb) != S_OKAY) return (db_status);

/* Ausgabe einer Fehlermeldung */
	if (error_flag) {
		error_message (&olddb, errcode, routine, "");
#ifndef MSWIND
		fprintf (stderr, "\n");
#endif
	}

/* Fehler in Liste eintragen */
	store_error (&errcode, routine);

/* aktuelle DB wieder zuschalten */
	if (olddb != NULL) {
		activate (olddb);
		olddb = NULL;
	}

/* Flag passivieren */
	db_error_Flag = FALSE;
        
return (db_status = errcode);
}

#ifdef DLL
int FUNCTYPE EXPORT01 set_db_status (int errcode) 
{
	return (db_status = errcode);
}

int FUNCTYPE EXPORT01 GetDBStatus (void) 
{
	return db_status;
}

void FUNCTYPE EXPORT01 SetErrorDBEnv (char *Env) 
{
	if (Env != NULL) strcpy (errordb_env, Env);
	else		 errordb_env[0] = '\0';
}
#endif

#ifdef MSWIND
extern "C" void __cdecl EXPORT01
ErrorWindow (DBASE **olddb, const char *lpszCaption, const char *lpszFormat, ...) 
{
char szText[160];

	if (olddb != NULL && *olddb != NULL) {
		activate (*olddb);	// alte DB wieder initialisieren
		*olddb = NULL;
	}

// Fenster anzeigen
	wvsprintf (szText, (LPSTR)lpszFormat, (LPSTR)(&lpszFormat+1));

#if defined(_DEBUG) && defined(WIN32)
// wenn Retry gedrückt wird, dann Assertion  auslösen (für Debugging)
UINT uiType = !strcmp (err_mess, lpszCaption) ? MB_ICONSTOP : MB_ICONEXCLAMATION;
	
	uiType |= (DEX_QueryMode() & QMSysAdmin) ? (MB_RETRYCANCEL|MB_DEFBUTTON2) : MB_OK;
	uiType |= MB_SETFOREGROUND;
	TX_ASSERT (IDRETRY != MessageBox (__hWndM, szText, lpszCaption, uiType));
#else
UINT uiType = !strcmp (err_mess, lpszCaption) ? MB_ICONSTOP : MB_ICONEXCLAMATION;

	uiType |= MB_OK | MB_SETFOREGROUND;
	MessageBox (__hWndM, szText, lpszCaption, uiType);
#endif // _DEBUG
}
#endif // MSWIND


/* Setzt das Flag, welches entscheidet, ob eine Fehlermeldung gedruckt 
   werden soll. */
BOOL FUNCTYPE EXPORT01 ShowErrorMessages (BOOL new_flag)
{
BOOL temp = error_flag;

	error_flag = (new_flag != 0) ? TRUE : FALSE;
	return (temp);
}


/* Metadatenbasis eroeffnen bzw. aktivieren */
int FUNCTYPE EXPORT01 act_meta (register DBASE **olddb)
{
	if (!tried && errdb == (HPROJECT)0) { 
	/* Fehlervektor anfordern */
#ifdef MSWIND
		if (irc_list == NULL) {
			TX_TRY(irc_list = new ERROR_LIST);
			if (irc_list == NULL) {
				errdb = (HPROJECT)NONE;   /* keine Fehler-DB */
				tried = TRUE;
				*olddb = NULL;
				return (db_error (S_NOERRVEC, SETERROR));
			}
			max_errors = MAXERRORS;
		}
	
	// StringResourcen laden
		LoadString (g_hInstance, IDS_DBERROR, err_mess, sizeof(err_mess));
		LoadString (g_hInstance, IDS_DBWARNING, war_mess, sizeof(war_mess));
		LoadString (g_hInstance, IDS_ERRORTEXT, err_head, sizeof(err_head));
		LoadString (g_hInstance, IDS_AUXERROR, cbAuxError, sizeof(cbAuxError));
		LoadString (g_hInstance, IDS_FULLLIST, cbFullList, sizeof(cbFullList));
		LoadString (g_hInstance, IDS_DBERRORNAME, cbDBError, sizeof(cbDBError));
		LoadString (g_hInstance, IDS_RECURSIVECALL, cbRecurse, sizeof(cbRecurse));
		LoadString (g_hInstance, IDS_UNKNOWNROUTINE, cbUnknown, sizeof(cbUnknown));
		LoadString (g_hInstance, IDS_OPENERROR, cbOpenError, sizeof(cbOpenError));
		LoadString (g_hInstance, IDS_OPENERRORTEXT, cbOpenErrorText, sizeof(cbOpenErrorText));
#else
		if (irc_list == NULL) {
		/* Kein Fehlervektor gegeben */
			if ((irc_list = (ERROR_LIST *)calloc (1, sizeof(ERROR_LIST))) == NULL) {
				errdb = (HPROJECT)0;   /* keine Fehler-DB */
				tried = TRUE;
				*olddb = NULL;
				return (db_error (S_NOERRVEC, SETERROR));
			}
			max_errors = MAXERRORS;
		}
#endif
	/* interne Variablen setzen */
		irc_list->error_cnt = S_OKAY;
		actirc = 0;	      /* aktueller irc */

	/* Eröffnen der Fehler-DB */
		*olddb = activate (NULL);
		open_meta ();           
		tried = TRUE;
	} else {
	// lediglich aktivieren der FehlederDB, 
		if (errdb == (HPROJECT)0) 
			*olddb = activate (NULL);
		else
			*olddb = activate (&db_table[short(errdb)-1]);
	}

return (db_status = S_OKAY);
}

// Freigeben der FehlerListe --------------------------------------------------
extern "C" void FUNCTYPE ReleaseErrorList (void)
{
	DELETE (irc_list);
}

/* Ausgabe einer Fehlermeldung */
int __cdecl EXPORT01 
error_message (DBASE **olddb, int errcode, int routine, char *pExtraText) 
{
INT key_routine, key_errcode;

	if (!error_flag) return errcode;
	if (errdb == (HPROJECT)0) {
	/* Fehlerbehandlung, wenn Meta-DB nicht eroeffnet ist */
#ifdef MSWIND
		ErrorWindow (olddb, errcode > 0 ? war_mess : err_mess,
			cbAuxError, errcode, routine, pExtraText);
#else
		fprintf (stderr, "%s (%d) in Routine %d\n",
			errcode > 0 ? war_mess : err_mess, errcode, routine);
#endif
	} else {
	/* Fehlerbehandlung im Normalfall */
	DB_ADDR dba(errdb);
	struct error error;
	struct routine ort;
	INT_FUNC *w_ntfnd, *dummy;
        
	/* Suchen des Routinennamens */
		dba.file_no = ROUTINE;
		err_install (S_NOTFOUND, E_IGNORE, &w_ntfnd);
		key_routine = (INT)routine;
		if (z_keyfind (&dba, SRCCODE, (char *)&key_routine) != S_OKAY) {
			if (db_status == S_NOTFOUND) 
				strcpy (ort.srcname, cbUnknown);
			else return (db_status);
		} else if (z_readrec (&dba, (char *)&ort) != S_OKAY)
			return (db_status);

	/* Suchen der Fehlermeldung */
		dba.file_no = ERRORNR;
		key_errcode = (INT)errcode;
		if (z_keyfind (&dba, ERRCODE, (char *)&key_errcode) != S_OKAY) {
			if (db_status == S_NOTFOUND) 
				strcpy (error.errtext, cbUnknown);
			else return (db_status);
		} else if (z_readrec (&dba, (char *)&error) != S_OKAY)
			return (db_status);

#ifdef MSWIND
		OemToAnsi (ort.srcname, ort.srcname);
		OemToAnsi (error.errtext, error.errtext);
		ErrorWindow (olddb, errcode > 0 ? war_mess : err_mess, err_head,
				errcode, ort.srcname, error.errtext,
				pExtraText);
#else
		fprintf (stderr, err_head,
			errcode > 0 ? war_mess : err_mess, 
			errcode, ort.srcname, error.errtext);
		fprintf (stderr, "\n");
#endif
		err_install (S_NOTFOUND, w_ntfnd, &dummy);
	}

return errcode;
}


/* Fehler in Fehlerliste eintragen */
static short wasMessage = FALSE;

void FUNCTYPE EXPORT01 store_error (int *errcode, int routine)
{
register ERROR_LIST FAR *el_p;

	el_p = irc_list;
	if (el_p == NULL) return;
	
	if (actirc == max_errors) {
	/* Keine Fehler-Slots mehr frei */
		if (!wasMessage) {
		// Meldung nur einmal ausgeben
#ifdef MSWIND
			ErrorWindow (NULL, err_mess, err_head, S_ERROVL,
					cbDBError, cbFullList, "");
#else
        	        fprintf (stderr, err_head, err_mess, S_ERROVL,
                                        "seterr", "Fehlerliste voll.");
#endif
		}
		wasMessage = TRUE;
                *errcode = S_ERROVL;    /* muss negativ sein */
        } else {
		el_p->irc[actirc].error_code = *errcode;
		el_p->irc[actirc].routine_code = routine;
                actirc++;
        }
        if (el_p->error_cnt >= 0) {
                el_p->error_cnt++;
                if (*errcode < 0) 
			el_p->error_cnt = - (el_p->error_cnt);
        } else {
                el_p->error_cnt--;
        }
}

static int meta_err (int errcode, int routine, ...); /* eigene Fehlerroutine */

static void FUNCTYPE open_meta (void)
{
INT_FUNC *e_maxdb, *e_nomem, *e_invdb;
INT_FUNC *e_access, *e_version, *e_noread;
INT_FUNC *e_nofile, *dummy;
short oldCopyrightFlag = g_fCopyrightFlag;

#if !defined(DLL)
char *Env = getenv (ERRORDB_ENV);

	if (Env != NULL) strcpy (errordb_env, Env);
	else errordb_env[0] = '\0';
#endif

// auch alte Versionen der Fehler-DB anerkennen
	g_fCopyrightFlag = FALSE;

/* Alle Fehlermeldungen abfangen, da sonst crash erfolgt */
	err_install (S_MAXDB, meta_err, &e_maxdb);
	err_install (S_NOMEMORY, meta_err, &e_nomem);
	err_install (S_INVDB, meta_err, &e_invdb);
	err_install (S_ACCESS, meta_err, &e_access);
	err_install (S_VERSION, meta_err, &e_version);
	err_install (S_NOREAD, meta_err, &e_noread);
	err_install (S_NOFILE, meta_err, &e_nofile);

/* erster Versuch, Meta-DB zu eroeffnen */
	if (short(errdb = z_open (strcat (errordb_env, META), META_USER, "", TRUE)) < 0)
		errdb = (HPROJECT)0;
	
/* Fehlervektoren wieder ruecksetzen */
	err_install (S_MAXDB, e_maxdb, &dummy);
	err_install (S_NOMEMORY, e_nomem, &dummy);
	err_install (S_INVDB, e_invdb, &dummy);
	err_install (S_ACCESS, e_access, &dummy);
	err_install (S_VERSION, e_version, &dummy);
	err_install (S_NOREAD, e_noread, &dummy);
	err_install (S_NOFILE, e_nofile, &dummy);

// alten Zustand wieder einstellen
	g_fCopyrightFlag = oldCopyrightFlag;
}


/* Fehlerroutine zur Behandlung von Fehlern, die
   waehrend dem Oeffnen der Errorkode-DB auftreten */
static int meta_err (int errcode, int routine, ...)
{
#ifdef MSWIND
	ErrorWindow (NULL, err_mess, cbOpenError, cbOpenErrorText, errcode, routine);
#else
	fprintf (stderr, "%s beim Eroeffnen der Fehler-DB.\n", err_mess);
	fprintf (stderr, "Gemeldeter Fehler: %d in Routine %d\n", errcode, routine);
#endif
	store_error (&errcode, routine);
        
return (errcode);
}

/* Setzen einer anderen Fehlertabelle */
extern "C" long FUNCTYPE EXPORT01 setvec_ (ERROR_LIST *errtab, long *len)   /* F77 */
{
	irc_list = errtab;
	max_errors = (int)*len; 
	irc_list->error_cnt = S_OKAY;
	actirc = 0;		/* aktueller irc */

return ((INT)(db_status = S_OKAY));
}

