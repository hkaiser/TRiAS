// Suchen aller Objekte, die einen gegebenen MWert besitzen -------------------
// File: FNDTXTN.CXX

#include "trias02p.hxx"
#define	RoutCode	6070

#pragma warning (disable: 4284)
#include <ospace/std/memory>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern "C" 
long FUNCTYPE EXPORT02 TextFind (HPROJECT hPr, long lMCode, char *pText, short iMode, 
				 short iTarget, long *pflObj)
{
// alte Variante rufen: 'alte GeoDB', nicht exakt suchen oder Existenz testen
	if (GetDBVersion(hPr) < VERSION0500000B || (iMode != SMExactMatch && iMode != SMSubStringStartMatch)) 
		return FindPattern (hPr, lMCode, pText, iMode, pflObj);

	TX_ASSERT(iMode == SMSubStringStartMatch || iMode == SMExactMatch);

// ACHTUNG Oem<-->Ansi mismatch ! Key ist 'Oem' und Merkmal aus GetMiText ist bereits 'Ansi'
auto_ptr<char> pOemText (StrDup (pText));

// neue Variante: Text über Schlüssel suchen
ErrCode RC = EC_OKAY;
DB_ADDR dbaKDBT(hPr);
DB_ADDR dbaVOM(hPr);
DB_ADDR dbaMKL(hPr);
struct kdbt KDBTSatz;
struct vom VOMSatz;
struct mkl MKLSatz;

	if (*pflObj == 0) {
		DBASSERT (feini_ (pflObj));
	}
	dbaKDBT.file_no = KDBT;
	dbaVOM.file_no = VOM;
	dbaMKL.file_no = MKL;

char cbKey[sizeof(kdbt)];	// Feld für einzulesenden Schlüssel
int iSrchLen = 0;

	if (NULL != pText) {
	char *pKey = pText;

		if (NULL != pOemText.get()) {
			AnsiToOem (pText, pOemText.get());
			pKey = pOemText.get();
		}

	// wenn Suchtext gegeben ist, dann ersten passenden suchen
		{
		ErrInstall EI (WC_NOTFOUND);

			RC = (ErrCode)z_keyfind (&dbaKDBT, INFO, pKey);
		}

	// Schlüssel stimmt nicht genau, Testen ob SubString paßt
		iSrchLen = strlen(pKey);

		if (WC_NOTFOUND == RC) {
			if (iMode == SMSubStringStartMatch) {
			// auf den vorhergehenden positioniert
				RC = (ErrCode)z_keynext (&dbaKDBT, INFO);
				if (EC_OKAY != RC)
					return db_error (WC_NOTFOUND, RoutCode);
				DBASSERT(z_keyread (hPr, cbKey));

			// Schlüssel vergleichen
				if (strncmp (cbKey, pKey, iSrchLen) != 0)
					return db_error (WC_NOTFOUND, RoutCode);	// Schlüssel stimmt wirklich nicht
			} else
				return db_error (WC_NOTFOUND, RoutCode);	// nichts gefunden
		}
	} else {
	// Kein Suchtext gegeben, alle Objekte mit diesem Merkmal liefern
		DBASSERT(z_keyfirst (&dbaKDBT, INFO));
	}

ErrInstall EI (WC_NOTFOUND);		// jetzt global zuschalten

	do {		// für alle gefundenen Sätze
	// wenn was gefunden wurde
		__Read (dbaKDBT, KDBTSatz);

	// zugehörigen Verbindungssatz lesen
		dbaVOM.rec_no = KDBTSatz.zmivom;
		__Read (dbaVOM, VOMSatz);

	// MerkmalsCode besorgen, dazu MKL lesen
		dbaMKL.rec_no = VOMSatz.zvommk;
		__Read (dbaMKL, MKLSatz);

	// gefundenen Satz in der Liste speichern, wenn MCode stimmt
		if (MKLSatz.mk == lMCode) {
			switch (iTarget) {
			default:
			case OBL_OLD:
				{
				bool fMatch = true;		// für !SMExact haben wir's gefunden

					if (!(VOMSatz.zvomo & (IDL_MERKMAL|SICHT_MERKMAL))) {
						if (NULL == pText)
							fMatch = true;
						else {
							if (iMode == SMExactMatch) {
								if (iSrchLen > 36) {		// sizeof(kdbt::info)
								// vollständigen Text vergleichen
								char *pFullText = NULL;

									if (S_OKAY != (RC = (ErrCode)GetMiText (hPr, lMCode, VOMSatz.zvomo, OBL_OLD, &pFullText))) 
									{
										DELETE(pFullText);
										return RC;
									}
									fMatch = !strcmp (pFullText, pText);
									DELETE (pFullText);
								} else
									fMatch = true;		// breits gefunden
							}
						}

						if (fMatch) 
						{
							DBASSERTM (feput_ (pflObj, &VOMSatz.zvomo));
						}
					}
				}
				break;
					
			case IDL:
		    	if (VOMSatz.zvomo & IDL_MERKMAL) {
				long lIdentSatz = VOMSatz.zvomo & ~IDL_MERKMAL;

					DBASSERTM (feput_ (pflObj, &lIdentSatz));
				}
				break;
					
			case SICHT:
				if (VOMSatz.zvomo & SICHT_MERKMAL) {
				long lSichtSatz = VOMSatz.zvomo & ~SICHT_MERKMAL;
				
					DBASSERTM (feput_ (pflObj, &lSichtSatz));
				}
				break;
			}
		}

	// nächstes Merkmal suchen
		if ((RC = (ErrCode)z_keynext (&dbaKDBT, INFO)) != EC_OKAY) {
			if (RC == WC_NOTFOUND) RC = EC_OKAY;
			return RC;
		}

		if (NULL != pOemText.get()) {
		// wenn Suchtext gegeben ist, dann genauer hinsehen
			DBASSERT(z_keyread (hPr, cbKey));	// Schlüssel lesen

		// Schlüssel vergleichen (bei !SMExactMatch reicht keylänge für match)
			if (iMode == SMExactMatch) {
				if (strcmp (cbKey, pOemText.get()) != 0)
					return EC_OKAY;
			} else {
				if (strncmp (cbKey, pOemText.get(), iSrchLen) != 0)
					return EC_OKAY;		// Schlüssel stimmt nicht mehr
			}
		}
	} while (TRUE);

return EC_OKAY;
}
