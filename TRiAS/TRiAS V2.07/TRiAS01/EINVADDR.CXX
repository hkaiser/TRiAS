/* Routine zur Fehlerbehandlung von S_INVADDR                   */
/* File: EINVADDR.C                                             */

#include "trias01p.hxx"

#include <stdarg.h>

extern FLAG error_flag;

int __cdecl EXPORT01 einvaddr (int errcode, int routine, ...)
{
DBASE *olddb;
char ZusatzText[128];
DB_ADDR *dba;
va_list pList;

	va_start (pList, routine);
	dba = va_arg (pList, DB_ADDR *);
	va_end (pList);
/* Metadatenbasis eroeffnen bzw. aktivieren */
        if (act_meta (&olddb) != S_OKAY) return (db_status);
/* Ausgabe einer Fehlermeldung */
        if (error_flag) {
#ifdef MSWIND
		wsprintf (ZusatzText, " (Record-/Dateinummer: %d, Satznummer: %ld)",
					(short)dba->file_no, dba->rec_no);
#else
		sprintf (ZusatzText, " (Record-/Dateinummer: %d, Satznummer: %ld)\n", 
                                        (short)dba->file_no, dba->rec_no);
#endif
		error_message (&olddb, errcode, routine, ZusatzText);
        }
/* Fehler in Liste eintragen */
        store_error (&errcode, routine);
/* aktuelle DB wieder zuschalten */
	if (olddb != NULL) {
	        activate (olddb);
		olddb = NULL;
	}
        
return (db_status = errcode);
}
