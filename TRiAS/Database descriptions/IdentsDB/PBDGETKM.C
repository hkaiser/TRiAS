// Lesen und ausgeben der TXM-Datei aus einer PBD -----------------------------
// File: PBDGETKM.C

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include "dbtypes.h"
#include "errdef.h"
#include "idtdb.h"

static char *usage = "Verwendung: %s PBD-Name TXM-Datei.\n";

main (int argc, char *argv[])
{
register int dbnum;
register FILE *fpTXM;
DB_ADDR dbaMMK, dbaMKF, dbaMMW, dbaMMF;
struct mmk MMKSatz;
struct mkf MKFSatz;
struct mmw MMWSatz;
struct mmf MMFSatz;
// alte Version der PBD
struct mmk_001 MMK001Satz;
struct mkf_001 MKF001Satz;
struct mmw_001 MMW001Satz;
struct mmf_001 MMF001Satz;
char *pExt = NULL;

        if (argc < 3) {
                fprintf (stderr, usage, argv[0]);
                exit (1);
        }
        if ((fpTXM = fopen (argv[2], "w")) == NULL) {
                fprintf (stderr, "%s: Kann Ausgabedatei %s nicht eroeffnen.\n", argv[0], argv[2]);
                exit (3);
        }
	SetCopyrightFlag (FALSE);

	if (argc == 4) pExt = argv[3];
        if ((dbnum = z_open (argv[1], argv[1], "", pExt)) != S_OKAY) {
                fprintf (stderr, "%s: Kann DB %s nicht eroeffnen.\n", argv[0], argv[1]);
                exit (2);
        }

// ersten Satz finden
	err_install (S_NOTFOUND, E_IGNORE, NULL);
        dbaMMK.file_no = MMK;
	dbaMKF.file_no = MKF;
	dbaMMW.file_no = MMW;
	dbaMMF.file_no = MMF;

        if (z_keyfirst (&dbaMMK, MKS) != S_OKAY) {
                fprintf (stderr, "%s: Kein Merkmalscode vorhanden\n.", argv[1]);
                z_close (dbnum);
                exit (0);
        }

	if (GetDBVersion() <= PBD030000001) {
	// alte Version des ganzen
		do {
			if (z_readrec (&dbaMMK, &MMK001Satz) != S_OKAY) {
		                fprintf (stderr, "%s: Lesefehler.\n", argv[1]);
        		        z_close (dbnum);
                		exit (4);
			}
			dbaMKF.rec_no = MMK001Satz.zntxtm;
			MMK001Satz.zntxtm = 0;	// Stringende sicher ausnullen

		// Kopfzeile des MKodes
			fprintf (fpTXM, "%08ld %c %ld ", MMK001Satz.mks, 
							 toupper(MMK001Satz.mtyp[0]),
							 MMK001Satz.wfakm);
			switch (MMK001Satz.mtyp[0]) {
			case 'A':
			case 'a':
			case 'I':
			case 'i':
			case 'B':
			case 'b':
			case 'C':
			case 'c':
				fprintf (fpTXM, "%ld %ld ", MMK001Satz.wvon.iwvon[0], 
							    MMK001Satz.wbis.iwbis[0]);
				break;

			case 'f':
			case 'F':
				fprintf (fpTXM, "%lf %lf ", MMK001Satz.wvon.dwvon,
							    MMK001Satz.wbis.dwbis);
				break;
			}

		// KurzText/LangText ausgeben
			fprintf (fpTXM, "/*%-.16s*/%s ", MMK001Satz.ktextm, MMK001Satz.textm);

			while (dbaMKF.rec_no != 0) {
			// Folges„tze ausgeben

				if (z_readrec (&dbaMKF, &MKF001Satz) != S_OKAY) {
					fprintf (stderr, "%s: Lesefehler.\n", argv[1]);
					z_close (dbnum);
					exit (4);
				}
				dbaMKF.rec_no = MKF001Satz.ztxtmf;
				MKF001Satz.ztxtmf = 0;	// Stringende sicher ausnullen
				fprintf (fpTXM, "\\\n%s", MKF001Satz.textmf);
			}
			fprintf (fpTXM, "\n");

		// wenn Integer-Aufz„hlungstyp, dann Folges„tze lesen und ausgeben
			if (toupper (MMK001Satz.mtyp[0]) == 'I' && 
			    MMK001Satz.wbis.iwbis[0] == -1)
			{
				if ((dbaMMW.rec_no = MMK001Satz.wbis.iwbis[1]) != 0) {
				// Folges„tze ausgeben

					do {
					// ersten Satz einlesen
						if (z_readrec (&dbaMMW, &MMW001Satz) != S_OKAY) {
							fprintf (stderr, "%s: Lesefehler.\n", argv[1]);
							z_close (dbnum);
							exit (4);
						}
					// MerkmalsKode und Z„hlnummer
						fprintf (fpTXM, "%08ld I 1 %d 0 ", 
									MMK001Satz.mks,
									MMW001Satz.wkode);
						dbaMMF.rec_no = MMW001Satz.zntxtw;
						MMW001Satz.zntxtw = 0;	// Stringende
						fprintf (fpTXM, "%s ", 	MMW001Satz.textw);
					// FolgeTexte ausgeben
						while (dbaMMF.rec_no != 0) {
							if (z_readrec (&dbaMMF, &MMF001Satz) != S_OKAY) {
								fprintf (stderr, "%s: Lesefehler.\n", argv[1]);
								z_close (dbnum);
								exit (4);
							}
							dbaMMF.rec_no = MMF001Satz.ztxtmw;
							MMF001Satz.ztxtmw = 0;	// Stringende
							fprintf (fpTXM, "\\\n%s", MMF001Satz.textmw);
						}
						fprintf (fpTXM, "\n");
					// n„chster MerkmalsSatz
						if ((dbaMMW.rec_no = MMW001Satz.znwert) == 0)
							break;	// keiner mehr
					} while (MMK001Satz.wvon.iwvon[0]-- > 0);
				}
			}

		} while (z_keynext (&dbaMMK, MKS) == S_OKAY && z_readrec (&dbaMMK, &MMK001Satz) == S_OKAY);
	} else if (GetDBVersion() >= PBD030000002) {
	// Version mit langen KurzTexten
		do {
			if (z_readrec (&dbaMMK, &MMKSatz) != S_OKAY) {
		                fprintf (stderr, "%s: Lesefehler.\n", argv[1]);
        		        z_close (dbnum);
                		exit (4);
			}
			dbaMKF.rec_no = MMKSatz.zntxtm;
			MMKSatz.zntxtm = 0;	// Stringende sicher ausnullen

		// Kopfzeile des MKodes
			fprintf (fpTXM, "%08ld %c %ld ", MMKSatz.mks, 
							 toupper(MMKSatz.mtyp[0]),
							 MMKSatz.wfakm);
			switch (MMKSatz.mtyp[0]) {
			case 'A':
			case 'a':
			case 'I':
			case 'i':
			case 'B':
			case 'b':
			case 'C':
			case 'c':
				fprintf (fpTXM, "%ld %ld ", MMKSatz.wvon.iwvon[0], 
							    MMKSatz.wbis.iwbis[0]);
				break;

			case 'f':
			case 'F':
				fprintf (fpTXM, "%lf %lf ", MMKSatz.wvon.dwvon,
							    MMKSatz.wbis.dwbis);
				break;
			}

		// KurzText/LangText ausgeben
			fprintf (fpTXM, "/*%-.32s*/%s ", MMKSatz.ktextm, MMKSatz.textm);

			while (dbaMKF.rec_no != 0) {
			// Folges„tze ausgeben

				if (z_readrec (&dbaMKF, &MKFSatz) != S_OKAY) {
					fprintf (stderr, "%s: Lesefehler.\n", argv[1]);
					z_close (dbnum);
					exit (4);
				}
				dbaMKF.rec_no = MKFSatz.ztxtmf;
				MKFSatz.ztxtmf = 0;	// Stringende sicher ausnullen
				fprintf (fpTXM, "\\\n%s", MKFSatz.textmf);
			}
			fprintf (fpTXM, "\n");

		// wenn Integer-Aufz„hlungstyp, dann Folges„tze lesen und ausgeben
			if (toupper (MMKSatz.mtyp[0]) == 'I' && 
			    MMKSatz.wbis.iwbis[0] == -1)
			{
				if ((dbaMMW.rec_no = MMKSatz.wbis.iwbis[1]) != 0) {
				// Folges„tze ausgeben

					do {
					// ersten Satz einlesen
						if (z_readrec (&dbaMMW, &MMWSatz) != S_OKAY) {
							fprintf (stderr, "%s: Lesefehler.\n", argv[1]);
							z_close (dbnum);
							exit (4);
						}
					// MerkmalsKode und Z„hlnummer
						fprintf (fpTXM, "%08ld I 1 %d 0 ", 
									MMKSatz.mks,
									MMWSatz.wkode);
						dbaMMF.rec_no = MMWSatz.zntxtw;
						MMWSatz.zntxtw = 0;	// Stringende
						fprintf (fpTXM, "%s ", 	MMWSatz.textw);
					// FolgeTexte ausgeben
						while (dbaMMF.rec_no != 0) {
							if (z_readrec (&dbaMMF, &MMFSatz) != S_OKAY) {
								fprintf (stderr, "%s: Lesefehler.\n", argv[1]);
								z_close (dbnum);
								exit (4);
							}
							dbaMMF.rec_no = MMFSatz.ztxtmw;
							MMFSatz.ztxtmw = 0;	// Stringende
							fprintf (fpTXM, "\\\n%s", MMFSatz.textmw);
						}
						fprintf (fpTXM, "\n");
					// n„chster MerkmalsSatz
						if ((dbaMMW.rec_no = MMWSatz.znwert) == 0)
							break;	// keiner mehr
					} while (MMKSatz.wvon.iwvon[0]-- > 0);
				}
			}

		} while (z_keynext (&dbaMMK, MKS) == S_OKAY && z_readrec (&dbaMMK, &MMKSatz) == S_OKAY);
	}

	err_install (S_NOTFOUND, E_DEFAULT, NULL);
        z_close (dbnum);
        fclose (fpTXM);
        
exit (0);
}

