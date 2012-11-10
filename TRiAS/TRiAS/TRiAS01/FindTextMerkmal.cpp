/////////////////////////////////////////////////////////////////////////////
// @doc
// @moduel FindTextMerkmal.cpp | Merkmalswerte wiederfidnen

#include "trias01p.hxx"

#include <strdup.hxx>
#include <ErrInst.hxx>
#include <ActDB.h>
#include <switchkc.h>

#include <ospace/std/memory>
#include <NativeObject.h>

#include "ConnectFilterWrappers.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// sonstige benötigte Funktionen
int IsAlike (const char *requested, const char *found);

/////////////////////////////////////////////////////////////////////////////
// Suchen aller Objekte über MWerte
HRESULT CALLBACK FillObjectInResultVector(INT_PTR lTarget, DWORD dwType, UINT_PTR dwData)
{
	TX_TRY(reinterpret_cast<vector<unsigned long> *>(dwData) -> push_back(lTarget));
	return S_OK;
}

HRESULT FindTextMerkmal (
	HPROJECT hPr, long lMCode, const char *pText, int iMode, short iTyp, 
	vector<unsigned long> &rObjs)
{
	return FindTextMerkmalF(hPr, lMCode, pText, iMode, iTyp, FillObjectInResultVector, reinterpret_cast<UINT_PTR>(&rObjs));
}

HRESULT FindTextMerkmalF (
	HPROJECT hPr, long lMCode, const char *pText, int iMode, short iTyp, 
	HRESULT (CALLBACK *pFcn)(INT_PTR, DWORD, UINT_PTR), UINT_PTR dwData)
{
// alte Variante rufen: 'alte GeoDB', nicht exakt suchen oder Existenz testen
	if (LocGetDBVersion(hPr) < VERSION0500000B || (iMode != SMExactMatch && iMode != SMSubStringStartMatch)) 
		return FindTextMerkmalPatternF (hPr, lMCode, pText, iMode, pFcn, dwData);

	TX_ASSERT(iMode == SMSubStringStartMatch || iMode == SMExactMatch);

// ACHTUNG Oem<-->Ansi mismatch ! Key ist 'Oem' und Merkmal aus GetTextMerkmal ist bereits 'Ansi'
auto_ptr<char> pOemText (StrDupF (pText));
CActDB ActDB(hPr);

// neue Variante: Text über Schlüssel suchen
ErrCode RC = EC_OKAY;
DB_ADDR dbaKDBT(hPr);
DB_ADDR dbaVOM(hPr);
DB_ADDR dbaMKL(hPr);
struct kdbt KDBTSatz;
struct vom VOMSatz;
struct mkl MKLSatz;

	dbaKDBT.file_no = KDBT;
	dbaVOM.file_no = VOM;
	dbaMKL.file_no = MKL;

char cbKey[sizeof(kdbt)];	// Feld für einzulesenden Schlüssel
int iSrchLen = 0;
HRESULT hr = S_OK;

	if (NULL != pText) {
	const char *pKey = pText;

		if (NULL != pOemText.get()) {
			AnsiToOem (pText, pOemText.get());
			pKey = pOemText.get();
		}

	// wenn Suchtext gegeben ist, dann ersten passenden suchen
		{
		ErrInstall EI (WC_NOTFOUND);

			RC = (ErrCode)z_keyfind (&dbaKDBT, INFO, (void *)pKey);
		}

	// Schlüssel stimmt nicht genau, Testen ob SubString paßt
		iSrchLen = strlen(pKey);

		if (WC_NOTFOUND == RC) {
			if (iMode == SMSubStringStartMatch) {
			// auf den vorhergehenden positioniert
				RC = (ErrCode)z_keynext (&dbaKDBT, INFO);
				if (EC_OKAY != RC)
					return HRESULT_FROM_ERRCODE(WC_NOTFOUND);
				DBASSERTHR(z_keyread (hPr, cbKey));

			// Schlüssel vergleichen
				if (strncmp (cbKey, pKey, iSrchLen) != 0)
					return HRESULT_FROM_ERRCODE(WC_NOTFOUND);	// Schlüssel stimmt wirklich nicht
			} else
				return HRESULT_FROM_ERRCODE(WC_NOTFOUND);		// nichts gefunden
		}
		else if (EC_OKAY != RC)
			return HRESULT_FROM_ERRCODE(RC);					// sonstiger Fehler
	} 
	else {
	// Kein Suchtext gegeben, alle Objekte mit diesem Merkmal liefern
		DBASSERTHR(z_keyfirst (&dbaKDBT, INFO));
	}

ErrInstall EI (WC_NOTFOUND);		// jetzt global zuschalten

	do {		// für alle gefundenen Sätze
	// wenn was gefunden wurde
	bool fSkipTestCode = false;

		__ReadHR(dbaKDBT, KDBTSatz);

	// zugehörigen Verbindungssatz lesen
		{	// wegen BUG bis jetzt (#HK000113) evtl. Korrekturcode rufen
		ErrInstall EB (EC_INVADDR);

			dbaVOM.rec_no = KDBTSatz.zmivom;
			RC = (ErrCode)z_readrec (&dbaVOM, &VOMSatz);
			if (EC_OKAY != RC) {
				if (EC_INVADDR != RC)
					return HRESULT_FROM_ERRCODE(RC);

			// hier versuchen den Fehler zu beheben (Folgesatz wurde als 1. Satz gespeichert,
			// und wurde hier irrtümlicherweise gefunden
			DB_ADDR dbaFDBT(hPr);

				dbaFDBT.file_no = FDBT;
				dbaFDBT.rec_no = dbaKDBT.rec_no;

				__DisposeHR(dbaKDBT, KDBTSatz);
				__NewHR(dbaFDBT, KDBTSatz);
				_ASSERTE(dbaFDBT.rec_no == dbaKDBT.rec_no);		// Satznummer darf sich nicht geändert haben
				fSkipTestCode = true;
			}
		}

		if (!fSkipTestCode) {
		// MerkmalsCode besorgen, dazu MKL lesen
			dbaMKL.rec_no = VOMSatz.zvommk;
			__ReadHR(dbaMKL, MKLSatz);

		// gefundenen Satz in der Liste speichern, wenn MCode stimmt
			if (MKLSatz.mk == lMCode) {
				switch (iTyp) {
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
									
										hr = GetTextMerkmal (hPr, lMCode, VOMSatz.zvomo, OBL_OLD, &pFullText);
										if (FAILED(hr)) {
											DELETE_OBJ(pFullText);
											return hr;
										}
										fMatch = !strcmp (pFullText, pText);
										DELETE_OBJ (pFullText);
									} else
										fMatch = true;		// breits gefunden
								}
							}
							if (fMatch) {
							CKeyContext keyCtx;

								hr = trias_connectfilter::EnumObjectsWrapper(
									hPr, VOMSatz.zvomo, OBL_MERKMAL, pFcn, dwData);
								if (S_OK != hr) return hr;

								ActDB.ReActivate();
							}
						}
					}
					break;
						
				case IDL_OLD:
		    		if (VOMSatz.zvomo & IDL_MERKMAL) {
					CKeyContext keyCtx;
					long lIdentSatz = VOMSatz.zvomo & ~IDL_MERKMAL;

						hr = pFcn(lIdentSatz, IDL_MERKMAL, dwData);
						if (S_OK != hr) return hr;

						ActDB.ReActivate();
					}
					break;
						
				case SICHT:
					if (VOMSatz.zvomo & SICHT_MERKMAL) {
					CKeyContext keyCtx;
					long lSichtSatz = VOMSatz.zvomo & ~SICHT_MERKMAL;
					
						hr = pFcn(lSichtSatz, SICHT_MERKMAL, dwData);
						if (S_OK != hr) return hr;

						ActDB.ReActivate();
					}
					break;
				}
			}
		}

	// nächstes Merkmal suchen
		if ((RC = (ErrCode)z_keynext (&dbaKDBT, INFO)) != EC_OKAY) {
			if (RC == WC_NOTFOUND || RC == EC_OKAY) 
				return S_OK;
			return HRESULT_FROM_ERRCODE(RC);
		}

		if (NULL != pOemText.get()) {
		// wenn Suchtext gegeben ist, dann genauer hinsehen
			DBASSERTHR(z_keyread (hPr, cbKey));	// Schlüssel lesen

		// Schlüssel vergleichen (bei !SMExactMatch reicht keylänge für match)
			if (iMode == SMExactMatch) {
				if (strcmp (cbKey, pOemText.get()) != 0)
					return S_OK;
			} else {
				if (strncmp (cbKey, pOemText.get(), iSrchLen) != 0)
					return S_OK;		// Schlüssel stimmt nicht mehr
			}
		}
	} while (TRUE);
	return S_OK;
}

HRESULT FindTextMerkmalPatternIndex (
	HPROJECT hPr, long lMCode, const char *pPattern, int iMode, 
	vector<unsigned long> &rObjs)
{
	return FindTextMerkmalPatternIndexF(hPr, lMCode, pPattern, iMode, FillObjectInResultVector, reinterpret_cast<UINT_PTR>(&rObjs));
}

HRESULT FindTextMerkmalPatternIndexF (
	HPROJECT hPr, long lMCode, const char *pPattern, int iMode, 
	HRESULT (CALLBACK *pFcn)(INT_PTR, DWORD, UINT_PTR), UINT_PTR dwData)
{
// ansonsten alles beim Alten
CActDB ActDB(hPr);
DB_ADDR dbaMKL(hPr);
struct mkl MKLSatz;
long lTarget = 0;
ErrCode RC;

// AnfangsInitialisierung
	dbaMKL.file_no = MKL;

// Finden des MCodes 
	DBASSERTHR(z_keyfind (&dbaMKL, MK, &lMCode));
	__ReadHR(dbaMKL, MKLSatz);		// MK-INF AUS MKL 
	if (MKLSatz.typ != 0) 			// kein Textmerkmal
		return HRESULT_FROM_ERRCODE(EC_BADMKTYPE);

DB_ADDR dbaVMO(hPr);
struct mcodeb::mcodebkey key;

	key.mcodebkey.mcodek = lMCode;		// alle Objekte mit diesem MCode
	key.mcodebkey.zvmook = 0L;
	dbaVMO.file_no = VMO_NEW;
	{
	ErrInstall EI (WC_NOTFOUND);

		RC = (ErrCode)z_keyfind (&dbaVMO, MCODEB, &key);
	}
	if (WC_NOTFOUND == RC) {
	// auf den vorhergehenden positioniert
		RC = (ErrCode)z_keynext (&dbaVMO, MCODEB);
		if (EC_OKAY != RC)
			return HRESULT_FROM_ERRCODE(WC_NOTFOUND);

	// ersten Treffer lesen
		DBASSERTHR(z_keyread (hPr, &key));
		if (key.mcodek != lMCode)
			return HRESULT_FROM_ERRCODE(WC_NOTFOUND);
	}

ErrInstall EI (WC_NOTFOUND);		// jetzt global zuschalten
BOOL fFound = FALSE;
int iPatternLen = 0;

	if (SMSubStringStartMatch == iMode)		// nur bei SMSubStringStartMatch benötigt
		iPatternLen = strlen(pPattern);

	do {		// für alle gefundenen Sätze
	// wenn was gefunden wurde
		if (!(key.zvmook & (IDL_MERKMAL|SICHT_MERKMAL))) {
		// eigendliche Suchroutine
			if (NULL != pPattern) {
			// Text muß existieren
				if (SMExistanceOnly == iMode)	// Existenz testen
					fFound = TRUE;
				else {
				char *pText = NULL;	// wegen DELETE_OBJ()

					RETURN_FAILED_HRESULT(GetTextMerkmal (hPr, lMCode, key.zvmook, OBL_OLD, &pText));
					switch (iMode) {
					default:
					case SMExactMatch:			// exakte Suche
						fFound = (strcmp (pPattern, pText) == 0);
						break;
			
					case SMInexactMatch:		// unexakte Suche
						fFound = IsAlike (pPattern, pText);
						break;
			
					case SMSubstringMatch:		// Teilbegriffe suchen
						fFound = (strstr (pText, pPattern) != NULL);
						break;

					case SMSubStringStartMatch:	// Teilbegriff am Zeilenanfang
						fFound = (0 == strncmp (pText, pPattern, iPatternLen)) ? TRUE : FALSE;		// #HK001105
						break;
					}
					DELETE_OBJ(pText);
				}
			} else 
				fFound = TRUE;	// nur Merkmal abfragen
		
		/* fFound == FALSE: nichts gefunden */
			if (fFound) {
			CKeyContext keyCtx;
			HRESULT hr = trias_connectfilter::EnumObjectsWrapper(hPr, key.zvmook, OBL_MERKMAL, pFcn, dwData);

				if (S_OK != hr) return hr;
				ActDB.ReActivate();
			}
		}

	// nächsten Schlüssel suchen
		if ((RC = (ErrCode)z_keynext (&dbaVMO, MCODEB)) != EC_OKAY) {
			if (RC == WC_NOTFOUND || RC == EC_OKAY) 
				return S_OK;
			return HRESULT_FROM_ERRCODE(RC);
		}

	// wenn Suchtext gegeben ist, dann genauer hinsehen
		DBASSERTHR(z_keyread (hPr, &key));	// Schlüssel lesen
		if (key.mcodek != lMCode)
			return S_OK;		// kein  Merkmal mehr
	} while (TRUE);

	return S_OK;
}

HRESULT FindTextMerkmalPatternIndexNew (
	HPROJECT hPr, long lMCode, const char *pPattern, int iMode, 
	vector<unsigned long> &rObjs)
{
	return FindTextMerkmalPatternIndexNewF(hPr, lMCode, pPattern, iMode, FillObjectInResultVector, reinterpret_cast<UINT_PTR>(&rObjs));
}

HRESULT FindTextMerkmalPatternIndexNewF (
	HPROJECT hPr, long lMCode, const char *pPattern, int iMode, 
	HRESULT (CALLBACK *pFcn)(INT_PTR, DWORD, UINT_PTR), UINT_PTR dwData)
{
	TX_ASSERT(VERSION05000011 <= LocGetDBVersion(hPr));

// nur für GeoDB's ab V017
CActDB ActDB(hPr);
DB_ADDR dbaMKL(hPr), dbaVMO(hPr); 
struct mkl MKLSatz;
struct mcodex VMOSatz;
long lTarget = 0;
ErrCode RC;
BOOL fFound = FALSE;

// AnfangsInitialisierung
	dbaMKL.file_no = MKL;
	dbaVMO.file_no = VMO_NEW;

// Finden des MCodes
	DBASSERTHR(z_keyfind (&dbaMKL, MK, &lMCode));
	__ReadHR(dbaMKL, MKLSatz);		// MK-INF AUS MKL 
	if (MKLSatz.typ != 0) 			// kein Textmerkmal
		return HRESULT_FROM_ERRCODE(EC_BADMKTYPE);

	dbaVMO.rec_no = MKLSatz.zmkvmo;			// Objektnummer in VerbindungsListe
	__ReadHR(dbaVMO, VMOSatz);				// Verweis in VerbindungsListe
	lTarget = VMOSatz.mcodexkey.zvmoox;		// erstes Objekt

int iPatternLen = 0;

	if (SMSubStringStartMatch == iMode)		// nur bei SMSubStringStartMatch benötigt
		iPatternLen = strlen(pPattern);

	do {
		if (!(lTarget & (IDL_MERKMAL|SICHT_MERKMAL))) {
		
		// eigendliche Suchroutine
			if (NULL != pPattern) {
				if (SMExistanceOnly == iMode)		// Existenz testen
					fFound = TRUE;
				else {
				// Text muß existieren
				char *pText = NULL;	// wegen DELETE_OBJ()

					RETURN_FAILED_HRESULT(GetTextMerkmal (hPr, lMCode, lTarget, OBL_OLD, &pText));
					switch (iMode) {
					default:
					case SMExactMatch:			// exakte Suche
						fFound = (strcmp (pPattern, pText) == 0);
						break;
			
					case SMInexactMatch:		// unexakte Suche
						fFound = IsAlike (pPattern, pText);
						break;

					case SMSubstringMatch:		// Teilbegriffe suchen
						fFound = (strstr (pText, pPattern) != NULL);
						break;

					case SMSubStringStartMatch:	// Teilbegriff am Zeilenanfang
						fFound = (0 == strncmp (pText, pPattern, iPatternLen)) ? TRUE : FALSE;		// #HK001105
						break;
					}
					DELETE_OBJ(pText);
				}
			} else 
				fFound = TRUE;	// nur Merkmal abfragen

		// fFound == FALSE: nichts gefunden
			if (fFound) {
			HRESULT hr = trias_connectfilter::EnumObjectsWrapper(hPr, lTarget, 
				OBL_MERKMAL, pFcn, dwData);

				if (S_OK != hr) return hr;
				ActDB.ReActivate();
			}
		}
		if ((dbaVMO.rec_no = VMOSatz.zvmonk) == 0)
			break;	// Ende der Kette

		__ReadHR(dbaVMO, VMOSatz);
	} while ((lTarget = VMOSatz.mcodexkey.zvmoox) != 0);
	return S_OK;
}

HRESULT FindTextMerkmalPattern (
	HPROJECT hPr, long lMCode, const char *pPattern, int iMode, 
	vector<unsigned long> &rObjs)
{
	return FindTextMerkmalPatternF(hPr, lMCode, pPattern, iMode, FillObjectInResultVector, reinterpret_cast<UINT_PTR>(&rObjs));
}

HRESULT FindTextMerkmalPatternF (
	HPROJECT hPr, long lMCode, const char *pPattern, int iMode, 
	HRESULT (CALLBACK *pFcn)(INT_PTR, DWORD, UINT_PTR), UINT_PTR dwData)
{
// Rückverkettung Merkmal --> Objekt jetzt indiziert 
long lVersion = LocGetDBVersion(hPr);

	if (VERSION0500000F <= lVersion) {	
		if (VERSION05000011 <= lVersion)
			return FindTextMerkmalPatternIndexNewF (hPr, lMCode, pPattern, iMode, pFcn, dwData);
		else
			return FindTextMerkmalPatternIndexF (hPr, lMCode, pPattern, iMode, pFcn, dwData);
	}

// ansonsten alles beim Alten
CActDB ActDB (hPr);
DB_ADDR dbaMKL(hPr), dbaVMO(hPr); 
struct mkl MKLSatz;
struct vmo VMOSatz;
long lTarget = 0;
ErrCode RC;
BOOL fFound = FALSE;

// AnfangsInitialisierung
	dbaMKL.file_no = MKL;
	dbaVMO.file_no = VMO_OLD;

// Finden des MCodes 
	DBASSERTHR(z_keyfind (&dbaMKL, MK, &lMCode));
	__ReadHR(dbaMKL, MKLSatz);		// MK-INF AUS MKL 
	if (MKLSatz.typ != 0) 			// kein Textmerkmal
		return HRESULT_FROM_ERRCODE(EC_BADMKTYPE);

	dbaVMO.rec_no = MKLSatz.zmkvmo;	// Objektnummer in VerbindungsListe
	__ReadHR(dbaVMO, VMOSatz);		// Verweis in VerbindungsListe
	lTarget = VMOSatz.zvmoo;		// erstes Objekt

int iPatternLen = 0;

	if (SMSubStringStartMatch == iMode)		// nur bei SMSubStringStartMatch benötigt
		iPatternLen = strlen(pPattern);

	do {
		if (!(lTarget & (IDL_MERKMAL|SICHT_MERKMAL))) {
		
		// eigendliche Suchroutine
			if (NULL != pPattern) {
				if (SMExistanceOnly == iMode)		// Existenz testen (SMExistanceOnly)
					fFound = TRUE;
				else {
				// Text muß existieren
				char *pText = NULL;	// wegen DELETE_OBJ()

					RETURN_FAILED_HRESULT(GetTextMerkmal (hPr, lMCode, lTarget, OBL_OLD, &pText));
					switch (iMode) {
					default:
					case SMExactMatch:		// exakte Suche
						fFound = (strcmp (pPattern, pText) == 0);
						break;
			
					case SMInexactMatch:	// unexakte Suche
						fFound = IsAlike (pPattern, pText);
						break;

					case SMSubstringMatch:	// Teilbegriffe suchen
						fFound = (strstr (pText, pPattern) != NULL);
						break;

					case SMSubStringStartMatch:	// Teilbegriff am Zeilenanfang
						fFound = (0 == strncmp (pText, pPattern, iPatternLen)) ? TRUE : FALSE;		// #HK001105
						break;
					}
					DELETE_OBJ(pText);
				}
			} else 
				fFound = TRUE;	// nur Merkmal abfragen

		// fFound == FALSE: nichts gefunden
			if (fFound) {
			HRESULT hr = trias_connectfilter::EnumObjectsWrapper(hPr, lTarget, 
				OBL_MERKMAL, pFcn, dwData);

				if (S_OK != hr) return hr;
				ActDB.ReActivate();
			}
		}
		if ((dbaVMO.rec_no = VMOSatz.znvmo) == 0)
			break;	// Ende der Kette

		__ReadHR(dbaVMO, VMOSatz);

	} while ((lTarget = VMOSatz.zvmoo) != 0);
	return S_OK;
}

