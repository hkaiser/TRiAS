// Routine zur Fehlerbehandlung von Visualisierungsfehlern
// File: EVISERR.C

#include "trias01p.hxx"

#include <stdarg.h>
#include <containr.hxx>
#include <viserror.hxx>

extern FLAG error_flag;

extern "C" int __cdecl EXPORT01 ReportVisError (int err_code, int r_code, ...)
{
char ZusatzText[128];
va_list paramlist;
CVisError *pVE;
DBASE *olddb = NULL;

	va_start (paramlist, r_code);
	pVE = va_arg (paramlist, CVisError *);
	va_end (paramlist);

// Metadatenbasis eroeffnen bzw. aktivieren 
	if (act_meta (&olddb) != S_OKAY) return (db_status);

// Ausgabe einer Fehlermeldung 
	if (error_flag) {
		if (pVE) {
#ifdef MSWIND
			wsprintf (ZusatzText, "(Identifikator: %08ld)", pVE -> m_lIdent);
#else
			sprintf (ZusatzText, "(Identifikator: %08ld)\n", pVE -> m_lIdent);
#endif
		} else
			ZusatzText[0] = '\0';
		error_message (&olddb, err_code, r_code, ZusatzText);
	}

// Fehler in Liste eintragen 
	store_error (&err_code, r_code);

#if !defined(_ERROR_MESSAGERESOURCE)
// aktuelle DB wieder zuschalten 
	if (olddb != NULL) {
	        activate (olddb);
		olddb = NULL;
	}
#endif // _ERROR_MESSAGERESOURCE

	return (db_status = err_code);
}


