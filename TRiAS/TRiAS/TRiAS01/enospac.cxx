// Routine zur Fehlerbehandlung von fehlendem Speicherplatz auf Datenträgern --
// File: ENOSPAC.CXX

#include "trias01p.hxx"

#include "resource.h"

#include <stdarg.h>
#include <containr.hxx>

extern FLAG error_flag;
extern "C" HINSTANCE g_hInstance;

extern "C" int __cdecl EXPORT01 ReportNoSpaceError (int err_code, int r_code, ...)
{
va_list paramlist;
LPCSTR pText = NULL;
DBASE *olddb = NULL;

	va_start (paramlist, r_code);
	pText = va_arg (paramlist, LPCSTR);
	va_end (paramlist);

// Metadatenbasis eröffnen bzw. aktivieren 
	if (act_meta (&olddb) != S_OKAY) return (db_status);

// Ausgabe einer Fehlermeldung 
	if (error_flag) {
	char szCaption[32];
	char szFormat[256];

		LoadString (g_hInstance, IDS_NOSPACEERRORCAP, szCaption, sizeof(szCaption));
		LoadString (g_hInstance, IDS_NOSPACEERROR, szFormat, sizeof(szFormat));
		ErrorWindow (&olddb, szCaption, szFormat, pText);
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


