// Routinen fuer ASCII-Parser -------------------------------------------------
// File: ASCPARSC.CPP

#include "ascimpp.hpp"

#include <hdrentrx.hxx>
#include <xtensnn.h>
#include <dbconfig.h>
#include <errdef.h>
#include <eonrguid.h>

#include "ascimp.h"
#include "status.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern bool r_flag;					// Relationen ignorieren
extern unsigned long g_ulUniqueId;

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineEnumIIDWrapper(LONG);
DefineSmartEnumerator(LONG);

/////////////////////////////////////////////////////////////////////////////
// 
extern CStatusDlg *g_pDlg;
extern WEnumLONG g_Enum;

extern bool g_fReReadHeader;

// lokale Prototypen ----------------------------------------------------------
static int next_line (void);
void CountObjects (long lOTyp, bool fIncrement = true);
bool ImportGeometry (HPROJECT hPr, OBJGEOMETRIE *pOG, long sta[], long lIdent, double *gxi, double *gyi, int iFlags, long &rlONr, ULONG &rlIgnore);
ErrCode IdentIsDefined (long lIdent);

// Object bearbeiten ----------------------------------------------------------
int end_previous_object (void) 
{
long irc = 0L;

	lgi++;		/* Geometriezaehler korrigieren */
	if (lgi < koord_paare)
		return (db_error (EGCNT, ASCPARSER, yylineno));

// bevor irgend etwas passiert Header neu einlesen
	if (g_fReReadHeader) {
		DEXN_ReReadHeader();
		DEXN_ReScale();
		g_fReReadHeader = false;		// nur einmal
	}

// auswerten ob Komplexobjekt 
	if (lgi == 0) {
		if (RelCount() == 0)
			return db_error (EBADKO, ASCPARSER, yylineno);
		if (!r_flag)
			return EOKAY;	// keine Relationen, keine KomplexObjekte
		sta[0] = K_OBJEKT;	// Status setzen
		sta[1] = 0;		
	}

HPROJECT hPr = DEX_GetDataSourceHandle();

	_ASSERTE(NULL != hPr);
	irc = CreateObject (on, id, sta, mi, lgi, gxi, gyi);
	if (g_flag) {

	// evtl. ObjectGuid setzen
		if (irc && '\0' != guid[0]) {
		OBJECTGUID OUID;

			INITSTRUCT (OUID, OBJECTGUID);
			OUID.lONr = on;
			if (SUCCEEDED(CLSIDFromString (WideString(guid), &OUID.guid))) {
			// versuchen über GUID zu finden
				if (FAILED(DEX_FindObjectFromGuidEx (hPr, OUID))) {
				// alten Guid wieder setzen
				HRESULT hr = DEX_SetObjectGuid (OUID);

//					if (FAILED(hr) && HRESULT_FROM_ERRCODE(S_DUPLICATE) == hr) {
//						TX_ASSERT(0 != OUID.lONr);		// Objekt muß existieren
//
//					// GUID bereits in GeoDB vorhanden !!??
//						irc = S_DUPLICATE;
//
//					// neu erzeugtes Objekt löschen
//						DEX_DeleteObject (on);
//						CountObjects (sta[1], false);
//
//					// Geometrie an existierendem Objekt korrigieren
//						on = OUID.lONr;					// hier spielt die Musik
//						irc = CreateObject (on, id, sta, mi, lgi, gxi, gyi);
//					}
				}
			}
		}
	} else
		irc = UpdateFeatures (hPr, on, id, sta, mi);

// evtl. zur AusgabeObjektmenge hinzufügen
	if (irc && g_Enum.IsValid())
		g_Enum -> AddItem (on);

// Protocoll, Relationen etc.
bool fBreak = false;

	if (NULL != g_pDlg) {
		if (irc) 
			g_pDlg -> SetPos (ftell (yyin), on);
		fBreak = g_pDlg -> Break();
	}

	if (fpProt) fprintf (fpProt, "Satz %5ld, Objekt %5ld: Irc = %3ld\n", satz_nr, on, irc);

	if (irc && r_flag) {
		if (RelCount()) {
		// Relationen aufbauen
		long lONr, lRCode;
		short iRTyp;

			ResetList();
			while (RetrieveNextFromList (&lONr, &lRCode, &iRTyp)) 
				CreateRelation (on, lONr, lRCode, iRTyp);
			ClearList();
		}

	// Zuordnung Objekt <--> SatzNummer für Relationen merken
		StoreInTree (on, satz_nr);
	}

return fBreak;
}

// Objekt neu initialisieren --------------------------------------------------
void init_new_object (void) 
{
	lgi = -1;		// noch keine Geometrie gelesen
	mi[0] = MAXMI;		// Merkmalsfeldgröße
	mi[1] = 0;		// noch keine Merkmale gelesen
	curr_mi = &mi[-1];	// aktuelle Merkmalswerte
	curr_mi_text = (char *)&curr_mi[3];
	koord_paare = 0;	// Anzahl der Stützpunkte
	mi_count = 3;		// Zaehler der Merkmalswerte
	mi_werte = 0;		// Anzahl der Merkmalswerte
	satz_nr = on = 0;

	sta[0] = E_OBJEKT;	// für alle Fälle wieder auf ElementarObjekt
	guid[0] = '\0';

// RelationsDaten
	ClearList();		// interne Datenstrukturen initialisieren
}

// Objekt ueberspringen -------------------------------------------------------
int error_skip_lines (char *pattern, int error_code) 
{
// Fehlermeldung ausgeben

	db_error (error_code, ASCPARSER, yylineno);
	satz_nr = 0;			// Objekt nicht speichern
	skip_lines (pattern);		// Satz suchen

return (error_code);
}

// Schreiben von HeaderSätzen in den DB-Header --------------------------------
bool PutHdFlt (HPROJECT hPr, double Val, char *pKey, bool fForce, DWORD dwStyle) 
{
char cbOutBuff[50];

	sprintf (cbOutBuff, "%18.9lf", Val);
	return PutHdString (hPr, cbOutBuff, pKey, fForce, dwStyle);
}

bool PutHdString (HPROJECT hPr, char *pText, char *pKey, bool fForce, DWORD dwStyle) 
{
HeaderEntryX HE (pKey, hPr);

	if (HE.Status() != HE_INVALID && !fForce)
		return true;	// existiert bereits

	HE.SetEntryText (pText);
	HE.Flags() = dwStyle;

	if (EC_OKAY == HE.WriteBack()) {
		g_fReReadHeader = true;
		return true;
	}
	return false;
}

bool GetHdULONG (HPROJECT hPr, const char *pKey, unsigned long &ulVal)
{
HeaderEntryX HE (pKey, hPr);

	if (HE.Status() != HE_INVALID) {
		ulVal = (unsigned long)HE.EntryLong (0);
		return true;
	}

return false;
}

bool GetHdFloat (HPROJECT hPr, const char *pKey, double &rd)
{
HeaderEntryX HE (pKey, hPr);

	if (HE.Status() != HE_INVALID) {
		rd = HE.EntryDouble (0.0);
		return true;
	}

return false;
}

// Inverse Matrix für Koordinatentransformation berechnen ---------------------
int EvalKoeffs (double *k11, double *k12, double *k21, double *k22) 
{
double DetA = *k11 * *k22 - *k12 * *k21;

	if (DetA != 0.0) {
	double temp = *k11;

		*k11 = *k22/DetA;
		*k22 = temp/DetA;
		*k12 = -(*k12/DetA);
		*k21 = -(*k21/DetA);
		return EOKAY;
	} else {
		yyerror ("Entartete Transformationsmatrix.");
		return ESYNTX;
	}
}

// Umkonvertieren einer dezimalzahl in eine HexZahl ---------------------------
unsigned long MakeHex (unsigned long lPseudoHex)
{
char pTmp[40];

	ultoa (lPseudoHex, pTmp, 10);

return strtoul (pTmp, NULL, 16);
}

///////////////////////////////////////////////////////////////////////////////
// Zählen der importierten Objekte
void CountObjects (long lOTyp, bool fIncrement)
{
	switch (lOTyp) {
	case O_PUNKT:
		if (fIncrement)
			g_lPoints++;
		else
			g_lPoints--;
		break;

	case O_LINIE:
		if (fIncrement)
			g_lLines++;
		else
			g_lLines--;
		break;

	case O_FLAECHE:
		if (fIncrement)
			g_lAreas++;
		else
			g_lAreas--;
		break;

	case O_TEXTOBJEKT:
		if (fIncrement)
			g_lTexts++;
		else
			g_lTexts--;
		break;

	case O_TEXTOBJIND:
		if (fIncrement)
			g_lTexts++;
		else
			g_lTexts--;
		break;
	}
}

///////////////////////////////////////////////////////////////////////////////
// Geometrieobjekt erzeugen bzw. Geometrie modifizieren
short GetMOIMode (long sta[])
{
short iMode = 0;

	switch (sta[1]) {
	case O_PUNKT:
		iMode = MODIDENT_PUNKT;
		break;

	case O_LINIE:
		iMode = MODIDENT_LINIE;
		break;

	case O_FLAECHE:
		iMode = MODIDENT_FLAECHE;
		break;

	case O_TEXTOBJEKT:
	case O_TEXTOBJIND:
		iMode = MODIDENT_TEXT;
		break;
	}
	return iMode;
}

bool CreateObject (LONG &rlONr, ULONG lIdent, long sta[], 
		   long mi[], long lgi, double gxi[], double gyi[])
{
HPROJECT hPr = DEX_GetDataSourceHandle();

	_ASSERTE(NULL != hPr);

	if (sta[0] == K_OBJEKT) 
		return r_flag ? CreateKomplexObject (hPr, rlONr, lIdent, mi) : true;

// Objekt erzeugen oder wiederfinden, Geometrie schreiben
long lONr = 0L;
char *pUIdent = NULL;

	TX_ASSERT(!(g_fAbglGeom && g_fAbglAttr));	// nie gleichzeitig Attribs und Geometrie abgleichen!

	if (!m_flag || g_fAbglOks || g_fAbglGeom || g_fAbglAttr || 0 != g_ulOksToAttr) {
	// versuchen über GUID zu finden
		if ('\0' != guid[0]) {
		OBJECTGUID OUID;

			INITSTRUCT (OUID, OBJECTGUID);
			if (SUCCEEDED(CLSIDFromString (WideString(guid), &OUID.guid))) {
				if (SUCCEEDED(DEX_FindObjectFromGuid (OUID)))
					lONr = OUID.lONr;
			}
		}

	// versuchen, über Unique Ident zu finden
		if (0 == lONr && RetrieveText (g_ulUniqueId, mi, &pUIdent, false, !g_fImportObj) > 0) 
			lONr = FindObject (g_ulUniqueId, pUIdent);
	}
	DELETE_OBJ(pUIdent);

TEXTGEOMETRIEEX TG;
OBJGEOMETRIE *pOG = (OBJGEOMETRIE *)&TG;
ULONG lIgnore = 0L;
int iFlags = OGForceGeometry|OGNoMemoryObject|OGConverted;
bool fRet = true;

	if (0 == lONr) {	// nicht wiedergefunden
	// Objekt neu erzeugen
		iFlags |= OGNewObject;
		fRet = ImportGeometry (hPr, pOG, sta, lIdent, gxi, gyi, iFlags, rlONr, lIgnore);
	} else {
	// Abgleich durchführen
		if (g_fAbglGeom) {
		// Geometrie abgleichen
			iFlags |= OGModObject;
			fRet = ImportGeometry (hPr, pOG, sta, lIdent, gxi, gyi, iFlags, rlONr, lIgnore);

		} else { 
		// bisherigen Oks wegschreiben
			if (0 != g_ulOksToAttr) {
			long lOldIdent = DEX_GetObjIdent(lONr);
			char cbOKS[MAX_OKS_LENX+1];
			
				if (S_OK == ClassFromIdentX (lOldIdent, cbOKS)) 
					WriteTextMerkmal (lONr, (ULONG)g_ulOksToAttr, cbOKS, strlen(cbOKS));
			} 
			
		// Oks abgleichen
			if (g_fAbglOks) {
				if (0 == g_ulOksFromAttr) {
				// Oks vom EingabeOks nehmen
				MODOBJIDENT MOI;

					INITSTRUCT(MOI, MODOBJIDENT);
					MOI.lONr = lONr;
					MOI.lNewIdent = lIdent;
					MOI.iMode = GetMOIMode (sta);
					DEX_ModObjectIdent(MOI);
				} else {
				// Oks aus EingabeAttribut verwenden
				char *pOks = NULL;

					if (RetrieveText (g_ulOksFromAttr, mi, &pOks, false, !g_fImportObj) > 0) {
					// Ident über Oks besorgen
					long lNewIdent = 0;
					HRESULT hr = IdentFromClassX (hPr, pOks, (ULONG *)&lNewIdent);

						if (S_FALSE == hr) {
						ErrCode RC = IdentIsDefined(lNewIdent);
						
							if (RC != EC_OKAY && !DEX_isIdentUsedEx(hPr, lNewIdent)) 
							// neu erzeugen, wenn keine Objekte mit diesem Ident existieren
								hr = IdentFromClassX (hPr, pOks, (ULONG *)&lNewIdent, true);
						}

						if (0 != lNewIdent) {
						// jetzt Ident modifizieren
						MODOBJIDENT MOI;

							INITSTRUCT(MOI, MODOBJIDENT);
							MOI.lONr = lONr;
							MOI.lNewIdent = lNewIdent;
							MOI.iMode = GetMOIMode (sta);
							DEX_ModObjectIdent(MOI);

							lIdent = lNewIdent;
						}
					}
					DELETE_OBJ(pOks);
				}
			}

		// evtl. doch noch neues Objekt erzeugen
			if (g_fImportObj) {
				iFlags |= OGNewObject;
				fRet = ImportGeometry (hPr, pOG, sta, lIdent, gxi, gyi, iFlags, rlONr, lIgnore);
			} else
				rlONr = lONr;
		}
	}

	if (!fRet) {
		if (0 == pOG -> lONr) {
			g_lNotImported++;
			return false;
		} else {
			if (pOG -> iFlags & OGObjectHasGeometryErrors)
				g_lWithErrors++;	// mit Fehlern importiert
		}
	} 
	CountObjects (sta[1]);		// Objekte zählen

// Merkmale erzeugen
	if (m_flag || g_fAbglAttr)
		return CreateFeatures (rlONr, mi, lIdent, lIgnore);

	return true;
}

bool ImportGeometry (HPROJECT hPr, 
	OBJGEOMETRIE *pOG, long sta[], long lIdent, double *gxi, double *gyi, 
	int iFlags, long &rlONr, ULONG &lIgnore)
{
	INITSTRUCT (*pOG, OBJGEOMETRIE);
	pOG -> lONr = 0L;
	pOG -> lIdent = lIdent;
	pOG -> iFlags = short(iFlags);
	pOG -> pdblX = gxi;
	pOG -> pdblY = gyi;
	((TEXTGEOMETRIEEX &)pOG).fIndObjProp = FALSE;

	switch (sta[1]) {
	case O_PUNKT:
		pOG -> iObjTyp = OGPunkt;
		break;

	case O_LINIE:
		pOG -> iObjTyp = OGLinie;
		break;

	case O_FLAECHE:
		pOG -> iObjTyp = OGFlaeche;
		pOG -> iKCnt = AnalyzeAreaContures (lgi, gxi, gyi, &pOG -> plCnt);
		break;

	case O_TEXTOBJEKT:
		pOG -> iObjTyp = OGText;
		pOG -> iKCnt = RetrieveText (lTextObjMCode, mi, &((TEXTGEOMETRIE *)pOG) -> pText, true);
		lIgnore = lTextObjMCode;
		break;

	case O_TEXTOBJIND:
		pOG -> dwSize = sizeof(TEXTGEOMETRIEEX);
		pOG -> iObjTyp = OGLabel;
		pOG -> iKCnt = RetrieveText (lTextObjMCode, mi, &((TEXTGEOMETRIE *)pOG) -> pText, true);
		((TEXTGEOMETRIEEX &)pOG).fIndObjProp = TRUE;
		lIgnore = lTextObjMCode;
		break;
	}
	pOG -> lCnt = lgi;

GEOMETRIEWITHCS GCS;

	INITSTRUCT (GCS, GEOMETRIEWITHCS);
	GCS.pOG = pOG;
	GCS.pICS = ((CImpAscExtension *)g_pTE)->get_CS();

bool fRet = DEX_ModObjGeometrieEx(hPr, GCS);

	DELETE_OBJ(pOG -> plCnt);
	rlONr = pOG -> lONr;		// neue ObjektNummer
	return fRet;
}

// Anzahl der Konturen einer Fläche feststellen ------------------------------
short AnalyzeAreaContures (long &lgi, double gxi[], double gyi[], long **pplCnt)
{
short lCnt = 0;
double lX = gxi[0];
double lY = gyi[0];

// Anzahl der Konturen zählen
long lLast = 0;

	for (long lIndex = 1; lIndex < lgi; lIndex++) {
		if (lX == gxi[lIndex] && lY == gyi[lIndex]) {
			lCnt++;
			lLast = lIndex+1;
			if (++lIndex < lgi) {
				lX = gxi[lIndex];
				lY = gyi[lIndex];
			}
		}
	}

	if (lLast != lgi) // letzte Kontur nicht geschlossen
		lCnt++;		// eine mehr

// Speicher anfordern und Feld füllen
long *plCnt = NULL;

	lLast = 0;
	if (lCnt > 0) {
		plCnt = new long[lCnt];

		lCnt = 0;	// wieder von vorn
		lX = gxi[0];
		lY = gyi[0];

	long lKCnt = 1;

		for (long lIndex = 1; lIndex < lgi; lIndex++) {
			lKCnt++;	// zählt Stützpunkte dieser Kontur
			if (lX == gxi[lIndex] && lY == gyi[lIndex]) {
				plCnt[lCnt++] = lKCnt;
				lLast = lIndex+1;
				if (++lIndex < lgi) {
					lX = gxi[lIndex];
					lY = gyi[lIndex];
				}
				lKCnt = 1;
			}
		}
		if (lLast != lgi)
			plCnt[lCnt++] = lKCnt;
	}

	*pplCnt = plCnt;
	return lCnt;
}

// Geometrie nicht modifizieren, nur Merkmale/Ident korrigieren ---------------
bool UpdateFeatures (HPROJECT hPr, LONG &rlONr, ULONG lIdent, long sta[], long mi[])
{
// Objekt wiederfinden
char *pUIdent = NULL;
	
	rlONr = 0L;

	TX_ASSERT(!(g_fAbglGeom && g_fAbglAttr));	// nie gleichzeitig Attribs und Geometrie abgleichen!

// versuchen über GUID zu finden
	if ('\0' != guid[0]) {
	OBJECTGUID OUID;

		INITSTRUCT (OUID, OBJECTGUID);
		if (SUCCEEDED(CLSIDFromString (WideString(guid), &OUID.guid))) {
			if (SUCCEEDED(DEX_FindObjectFromGuidEx (hPr, OUID)))
				rlONr = OUID.lONr;
		}
	}

// versuchen, über Unique Ident zu finden
	if (0 == rlONr && RetrieveText (g_ulUniqueId, mi, &pUIdent, false, !g_fImportObj) > 0) 
		rlONr = FindObject (g_ulUniqueId, pUIdent);

	DELETE_OBJ(pUIdent);

	if (rlONr > 0) {		// Merkmale erzeugen
		if (m_flag && !CreateFeatures (rlONr, mi, lIdent)) {
			g_lWithErrors++;	// mit Fehlern importiert
			return false;
		}

	ULONG lOldId = (ULONG)DEX_GetObjIdent (rlONr);

		if (lIdent != lOldId) {
		MODOBJIDENT MOI;

			INITSTRUCT(MOI, MODOBJIDENT);
			MOI.lONr = rlONr;
			MOI.lNewIdent = lIdent;
			MOI.iMode = 0;
			if (!DEX_ModObjectIdent (MOI)) {
				g_lWithErrors++;	// mit Fehlern importiert
				return false;
			}
		}
		CountObjects (sta[1]);
		return true;
	} else
		g_lNotImported++;		// nicht wiedergefunden

    return false;
}

extern "C" 
bool PASCAL FindObjectCallback (long lONr, bool, void *pData)
{
	*(LONG *)pData = lONr;	// Objektnummer des gesuchten Objektes

return false;		// ein Objekt genügt
}

long FindObject (LONG lMCode, LPCSTR pcUIdent)
{
long lONr = 0;
ENUMRECHTEXTMERKMAL ERTM;

	INITSTRUCT(ERTM, ENUMRECHTEXTMERKMAL);
	ERTM.lMCode = lMCode;
	ERTM.pMWert = (char *)pcUIdent;
	ERTM.iMode = SMExactMatch;
	ERTM.eFcn = (RECHTEXTMERKMALCALLBACK)FindObjectCallback;
	ERTM.pData = &lONr;
	DEX_EnumRechTextMerkmal(ERTM);

return lONr;
}

// KomplexObjekt erzeugen -----------------------------------------------------
bool CreateKomplexObject (HPROJECT hPr, LONG &rlONr, ULONG lIdent, long mi[])
{
OBJCREATE OC;

	INITSTRUCT (OC, OBJCREATE);
	OC.lIdent = (long)lIdent;
	OC.iObjTyp = OGKO;
	OC.iFlags = OGNewObject;

	if (DEX_ModObjGeometrieEx (hPr, OC)) {
		g_lKomplex++;
		rlONr = OC.lONr;
		return true;
	}

	rlONr = -1L;
	return false;
}

// Kodiert diverse spezielle Zeichen um ---------------------------------------
char *CodeChars (char *lpRes, const char *lpText, int iBuffLen, int iStrLen = -1)
{
char *lpResult = lpRes;

	if (-1 == iStrLen)
		iStrLen = iBuffLen;

// jetzt umkopieren
	while (*lpText && iBuffLen > 0 && iStrLen > 0) {
		if (*lpText == '\\') {
			switch (*++lpText) {
			case 'n':	// Zeilenumbruch
				*lpResult++ = '\n';
				lpText++;
				iBuffLen--;
				iStrLen--;
				break;
				
			case 't':
				*lpResult++ = '\t';
				lpText++;
				iBuffLen--;
				iStrLen--;
				break;
				
			case '\0':	// Satzende
				*lpResult = '\0';
				return lpRes;
				
			default:	// keine Sonderbedeutung
				*lpResult++ = *lpText++;
				iBuffLen--;
				iStrLen--;
				break;
			}
		} else {
			*lpResult++ = *lpText++;
			iBuffLen--;
			iStrLen--;
		}
	}
	*lpResult = '\0';
	return lpRes;
}

// Merkmale an ein Objekt anhängen --------------------------------------------
bool CreateFeatures (LONG rlONr, long MInfo[], ULONG lIdent, ULONG lMCodeIgnore)
{
long *pMK = &MInfo[2];	// erstes Merkmal
char *pText = NULL;
bool fReturn = TRUE;
HPROJECT hPr = DEX_GetObjectsProject(lIdent);

	while (pMK < &MInfo[MInfo[1] + 2] && fReturn) {	// alle Merkmale ausgeben
		if (pMK[0] != 0 && (ULONG)pMK[0] != lMCodeIgnore) {
		// noch nicht ausgegeben
		int iLen = pMK[2]*sizeof(long);

			try { pText = new char[2*iLen+1]; } catch (...) {}
			if (NULL == pText) return false;

			memset(pText, '\0', 2*iLen);
			CodeChars (pText, (LPCSTR)&pMK[3], 2*iLen, iLen);

		// zugehörigen derzeitigen MCode wiederfinden
		MAPMCODETOHANDLE MMH;
		INT_PTR lMappedMCode = NULL;
		BOOL fCreated = FALSE;
		INT_PTR lMCode = pMK[0];

			INITSTRUCT (MMH, MAPMCODETOHANDLE);
			MMH.lIdent = lIdent;
			MMH.lMCode = lMCode;
			MMH.plHandle = &lMappedMCode;
			MMH.fCreate = FALSE;
			MMH.pfCreated = &fCreated;
			DEX_MapOrCreateMCodeToHandle (hPr, MMH);

			if (NULL != lMappedMCode && (fCreated || lMCode != lMappedMCode))
				lMCode = lMappedMCode;

		// Merkmal schreiben
			if (!WriteTextMerkmal (rlONr, (ULONG)lMCode, pText, strlen(pText)))
				fReturn = FALSE;
			DELETE_OBJ(pText);
		}
		pMK = &pMK[pMK[2] + 3];
	}
	return fReturn;
}


// Schreiben eines Merkmales --------------------------------------------------
bool WriteTextMerkmal (LONG lONr, ULONG lMCode, char cbBuffer[], int iLen)
{
TARGETMERKMALEX gm;

	INITSTRUCT (gm, TARGETMERKMALEX);
	gm.lTarget = (LPARAM)lONr;
	gm.lMCode = (long)lMCode;
	gm.imaxLen = iLen;
	gm.pMText = cbBuffer;
	gm.iTTyp = TT_Objekt;
	gm.iFlags = TMNoCaching;

	if (DEX_ModTextMerkmal (gm) != EC_OKAY)
		return false;

return true;
}


// Text eines Textobjketes aus Merkmalsfeld extrahieren ---------------------
short RetrieveText (ULONG lMCode, long mi[], char **ppText, bool fConvert, bool fMarkAsWritten)
{
short lLen = 0;
char *pText = FindMWert (lMCode, mi, &lLen, fMarkAsWritten);

	if (pText == NULL || lLen == 0)
		return 0;

char *pNewT = new char [2*lLen+1];

	if (pNewT == NULL) return 0;

	if (fConvert) 
		CodeChars (pNewT, pText, 2*lLen, lLen);
	else {
		strncpy (pNewT, pText, lLen);
		pNewT[lLen] = '\0';
	}

	*ppText = pNewT;
	return lLen;
}


// Finden eines Merkmales im MerkmalsFeld -------------------------------------
char *FindMWert (ULONG lMCode, long pMInfo[], short *plLen, bool fMarkAsWritten)
{
	TX_ASSERT (0 != lMCode);

long *pMK = &pMInfo[2];		// erstes Merkmal

	*plLen = 0;
	while (pMK < &pMInfo[pMInfo[1] + 2]) {	// alle Merkmale ausgeben
		if ((ULONG)pMK[0] == lMCode) {	// MCode gefunden
			if (fMarkAsWritten)
				pMK[0] = 0;		// MWert bereits ausgegeben
			*plLen = (pMK[2]*sizeof(long));
			return (char *)&pMK[3];
		}

		if (pMK[2] == -1L) 	// O_TEXTOBJIND
			pMK = &pMK[4];
		else
			pMK = &pMK[pMK[2] + 3];
	}

return NULL;
}

// Aufbauen einer Relation ----------------------------------------------------
bool CreateRelation (LONG lPONr, LONG lSONr, ULONG lRCode, short iRTyp)
{
MODRELATION MR;

	INITSTRUCT (MR, MODRELATION);
	MR.lPONr = lPONr;
	MR.lSONr = lSONr;
	MR.lRCode = (long)lRCode;
	MR.iRTyp = iRTyp;

return DEX_ModifyRelation (MR);
}

