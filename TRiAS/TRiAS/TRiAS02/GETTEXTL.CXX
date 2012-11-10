/* Lesen der Laenge Textinformationen in der *.DBT		       */
/* File: GETTEXTL.C						       */

#include "trias02p.hxx"

long FUNCTYPE EXPORT02 GetTextLen (HPROJECT hPr, long madr, long *plLen) 
{
DB_ADDR	dba(hPr);
struct kdbt dbt_satz;	/* Satz	der Datei '.dbt' */
int RC;

// Kein Text da (Textlänge gleich 0)
	if (madr == 0) {
		*plLen = 0;
		return S_OKAY;
	}

	dba.file_no = FDBT;
	dba.rec_no = madr;
	*plLen = 0;

	__Read (dba, dbt_satz);
	*plLen = dbt_satz.llen;
	if (*plLen != -1L)
		*plLen *= sizeof(INT);	// wirklich Text

return S_OKAY;
}

