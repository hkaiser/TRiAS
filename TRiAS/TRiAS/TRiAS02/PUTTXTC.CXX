/* Fuellen Textfeld(Merkmalsinformation)                                */
/* File: PUTTXTC.C							*/

#include "trias02p.hxx"

// PUTTXT schreibt einen gegebenen Text in die GeoDB als DBT-Satz (-Sätze) weg.
extern "C" long FUNCTYPE EXPORT02 PutText (HPROJECT hPr, const char *MText, short wf, long *madr) 
{
long satznr;
DB_ADDR dba (hPr);
struct fdbt dbt_satz;    /* Satz der Datei '.dbt' */
register int flag = FALSE;
int RC;
long *mi = (long *)MText;

	dba.file_no = FDBT;
	if (wf >= 0) {		// erlauben von Merkmalen mit 0 Zeichen
	// Text ist gegeben
		dba.rec_no = 0L;
		do {
		register short i;

			DBASSERT (DBPageZeroAlloc(hPr, RecordTable(hPr, FDBT) -> rt_file, &satznr));
			if (dba.rec_no != 0) {
				dbt_satz.zndbtf = satznr;
				__Write (dba, dbt_satz);
			} else 
				*madr = satznr;
			dba.rec_no = satznr;
			__Read (dba, dbt_satz);

			if (flag == FALSE) *((INT *)(&dbt_satz.infof[0])) = wf;
			else {
				*((INT *)(&dbt_satz.infof[0])) = *mi++;
				--wf;
			}
                        
			for (i = 1; i < 10; ++i) {
				if (--wf < 0) break;
				*((INT *)(&dbt_satz.infof[i*sizeof(INT)])) = *mi++;
			}
			flag = TRUE;
		} while (wf > 0);
		dbt_satz.zndbtf = 0L;
		__Write (dba, dbt_satz);
	} else {
	// kein Text gegeben, MText zeigt auf long mit MerkmalsKode
	// unter dem im Bezugsobjekt der Text abgespeichert ist

		DBASSERT (DBPageZeroAlloc(hPr, RecordTable(hPr, FDBT) -> rt_file, &satznr));
		*madr = satznr;
		dba.rec_no = satznr;
		__Read (dba, dbt_satz);
		((INT *)dbt_satz.infof)[0] = -1L;	// Kennung für MCode
		((INT *)dbt_satz.infof)[1] = *mi;	// MCode
		dbt_satz.zndbtf = 0;			// kein Folgesatz
		__Write (dba, dbt_satz);
	}
 
return S_OKAY;
}
