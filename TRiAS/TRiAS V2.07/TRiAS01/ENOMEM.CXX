/* Fehlerroutine fuer S_NOMEMORY - Fehler			*/
/* File: ENOMEM.C						*/

#include "trias01p.hxx"

extern FLAG error_flag;

int __cdecl EXPORT01 enomem (int errcode, int routine, ...)
{
	if (error_flag) {
#ifdef MSWIND
		ErrorWindow (NULL, "*** Datenbankfehler ***",
			"Fehlernummer (%d) in Routine %d: Kein Speicherplatz.",
			errcode, routine);
#else
		fprintf (stderr, "\n*** Datenbankfehler (%d) in Routine %d:\n", 
			errcode, routine);
		fprintf (stderr, "Kein Speicherplatz.\n");
#endif
	}
	store_error (&errcode, routine);

return (db_status = errcode);
}
