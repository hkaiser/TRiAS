/* Lesen der Textinformationen in der *.DBT                             */
/* File: GETTXTC.C              last update: 05. Juni 1990              */

#include "trias02p.hxx"

// GetText liest den Text aus den DBT-Sätzen ein ------------------------------
// ACHTUNG schließt eingelesene Zeichenkette nicht unbvedingt mit '\0' ab
long FUNCTYPE EXPORT02 GetTextOld (HPROJECT hPr, long madr, char *mi, long Len) 
{
DB_ADDR dba(hPr);
struct fdbt dbt_satz;    /* Satz der Datei '.dbt' */
register short i;
long wf, j;
register int flag = FALSE;
long *lpmi = (long *)mi;

// wenn kein TextSatz da ist (Textlänge gleich 0)
	if (madr == 0) {
		if (mi) *mi = '\0';
		return S_OKAY;
	}

	dba.file_no = FDBT;
	dba.rec_no = madr;
	j = 0;
	for (;;) {
	long RC;

		__Read (dba, dbt_satz);
		if (flag == FALSE) {
		// erster Satz: überprüfen, ob Text gegeben ist
			wf = ((INT *)(dbt_satz.infof))[0];
			if (wf == -1L) {
				if (Len >= sizeof(INT)) {
				// Text ist im Bezugsobjekt
					*lpmi = ((INT *)(dbt_satz.infof))[1];
					return S_OKAY;
				} else {
					if (lpmi) *lpmi = -1L;
					return S_TEXTTOLONG;
				}
			} else if (wf < 0) {
			// Text ist Name einer Objekteigenschaft vom Bezugsobjekt
				wf = -wf;		// #HK980601
			}

			if ((size_t)(wf * sizeof(long)) > (size_t)Len) {
				if (mi) 
					*mi = '\0';
				return S_TEXTTOLONG;
			}
		} else {
			lpmi[j++] = ((INT *)(dbt_satz.infof))[0];
		}
		for (i = 1; i < 10; ++i) {
			if (j == wf) break;
			lpmi[j++] = ((INT *)(dbt_satz.infof))[i];
		}
		flag = TRUE;
		if (dbt_satz.zndbtf == 0) 
			break;
		dba.rec_no = dbt_satz.zndbtf;
	}
                        
return S_OKAY;
}

