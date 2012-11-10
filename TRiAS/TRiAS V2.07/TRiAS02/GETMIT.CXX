// Lesen eines ausgewaehlten TextMerkmales fuer ein Objekt
// File: GETMIT.CXX

#include "trias02p.hxx"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// RoutinenKode
#define RC_GetMiTxt  	1021

// Liest ein TextMerkmal für das vorgegebene Objekt. --------------------------
extern "C" 
long FUNCTYPE EXPORT02 GetMiText (HPROJECT hPr, long MKode, long lFirst, short iTyp, char **ppMText) 
{
struct vom VOMSatz;
struct mkl MKLSatz;
DB_ADDR dbaVOM(hPr);
DB_ADDR dbaMKL(hPr);
long iLen = 0;
long VOMPrev = 0;       // vorhergehender VOMSatz
long VOMNext;           // nächster Satz
long zvommi = 0;        // Zeiger auf MISatz
long RC;
bool fText = false;

// sicherheitshalber NULL setzen
	VOMNext = 0L;

// TextPointer ausnullen
	*ppMText = NULL;

	if (lFirst == -1L) return EC_OKAY;

	switch (iTyp) {
	case OBL_OLD:		// normales ObjektMerkmal
		{
		struct obl OBLSatz;
		DB_ADDR_OBL dbaOBL(hPr);

		// Objektsatz einlesen
//			dbaOBL.file_no = OBL;
			dbaOBL.rec_no = lFirst;
			__Read (dbaOBL, OBLSatz);

			if (GetDBVersion(hPr) < VERSION05000008 &&
			    OBLSatz.status & SB_TEXTOBJ)
			// alte DB und Textobjekt
				return WC_RETURN;
			if (OBLSatz.status & SB_TEXTOBJIND)
				fText = true;
			VOMNext = OBLSatz.zovom;        // erster Satz
		}
		break;

	case IDL:		// IdentifikatorMerkmal
		{
			if (GetDBVersion(hPr) < VERSION05000007)
				return EC_OKAY;		// noch nicht implementiert

		struct idl IDLSatz;
		DB_ADDR dbaIDL(hPr);

			dbaIDL.file_no = IDL;
			dbaIDL.rec_no = lFirst;
			__Read (dbaIDL, IDLSatz);

			VOMNext = IDLSatz.zmerki;
		}
		break;

	case SICHT:		// SichtMerkmal
		{
			if (GetDBVersion(hPr) < VERSION05000007)
				return EC_OKAY;		// noch nicht implementiert

		struct sicht SICHTSatz;
		DB_ADDR dbaSICHT(hPr);

			dbaSICHT.file_no = SICHT;
			dbaSICHT.rec_no = lFirst;
			__Read (dbaSICHT, SICHTSatz);

			VOMNext = SICHTSatz.zmerkm;			
		}
		break;

	default:
		return WC_RETURN;
	}

// Verbindungsdatei zu Merkmalen (VOM) lesen und entspr. Satz suchen
	dbaVOM.file_no = VOM;
	dbaMKL.file_no = MKL;
	dbaVOM.rec_no = 0;
	MKLSatz.mk = 0;

	do {
	// VOMSatz lesen
		VOMPrev = dbaVOM.rec_no;
		if ((dbaVOM.rec_no = VOMNext) == 0)
			break;	// Ende der Kette: MCode nicht vorhanden
		__Read (dbaVOM, VOMSatz);
	// MKLSatz lesen
		dbaMKL.rec_no = VOMSatz.zvommk;
		__Read (dbaMKL, MKLSatz);
	// nächster VOMSatz
		VOMNext = VOMSatz.znmk;
	} while (MKLSatz.mk != MKode);          // bis MKode gefunden

// wenn für dieses Objekt MCode nicht exitiert: wieder raus mit Warnung
	if (MKLSatz.mk != MKode)
		return db_error (WC_NOTFOUND, RC_GetMiTxt);

// Prüfen, ob MerkmalsTyp stimmt
	if (MKLSatz.typ != 0)	// kein TextMerkmal
		return db_error (WC_BADMKTYP, RC_GetMiTxt);

// TextInfo einlesen
	DBASSERT (GetTextLen (hPr, VOMSatz.zvommi, &iLen));
	if (iLen <= 0) {
	// entweder kein Text oder Text aus Bezugsobjekt

		if (iTyp != OBL_OLD && SICHT != iTyp && IDL != iTyp)	// kein ObjektMerkmal
			return (ErrCode)db_error (WC_BADMKTYP, RC_GetMiTxt);

		*ppMText = new char [1];
		if (*ppMText == NULL) 
			return (ErrCode)db_error (EC_NOMEMORY, RC_GetMiTxt);
		**ppMText = '\0';
		return EC_OKAY;		// leerer TextString gegeben
	}
	iLen = ((iLen + 3) / 4) * 4;	// auf long Grenze aufrunden
	*ppMText = new char [iLen+1];
	if (*ppMText == NULL) 
		return (ErrCode)db_error (EC_NOMEMORY, RC_GetMiTxt);
	if (*ppMText) {
		memset (*ppMText, '\0', (short)(iLen+1));
		DBASSERT (GetText (hPr, VOMSatz.zvommi, *ppMText, iLen, fText));
#if defined(MSWIND)
		OemToAnsi (*ppMText, *ppMText);
#endif
	} else
		return db_error (EC_NOMEMORY, RC_GetMiTxt);

return EC_OKAY;
}

long FUNCTYPE GetVOMMI (HPROJECT hPr, long *lFirst, long MCode) 
{
// Verbindungsdatei zu Merkmalen (VOM) lesen und entspr. Satz suchen
struct vom VOMSatz;
struct mkl MKLSatz;
DB_ADDR dbaVOM(hPr);
DB_ADDR dbaMKL(hPr);
long VOMNext = *lFirst;
long VOMPrev;
ErrCode RC;

	MKLSatz.mk = 0;
	dbaVOM.file_no = VOM;
	dbaMKL.file_no = MKL;
	dbaVOM.rec_no = 0;

	do {
	// VOMSatz lesen
		VOMPrev = dbaVOM.rec_no;
		if ((dbaVOM.rec_no = VOMNext) == 0)
			break;	// Ende der Kette: MCode nicht vorhanden
		__Read (dbaVOM, VOMSatz);
	// MKLSatz lesen
		dbaMKL.rec_no = VOMSatz.zvommk;
		__Read (dbaMKL, MKLSatz);
	// nächster VOMSatz
		VOMNext = VOMSatz.znmk;
	} while (MKLSatz.mk != MCode);          // bis MKode gefunden

	if (MKLSatz.mk == MCode) {
		*lFirst = VOMSatz.zvommi;
		return EC_OKAY;
	}

return db_error (WC_NOTFOUND, RC_GetVOMMI);
}


// Bestimmt den konkreten TargetPointer in Abhängigkeit von dem MerkmalsTyp
extern "C" 
long EXPORT02 FUNCTYPE GetTarget (HPROJECT hPr, void *pTarget, short iTTyp)
{
	switch (iTTyp) {
	case OBL_OLD:	// direkt ObjektNummer
		TX_ASSERT((long)pTarget > 0);
		return (long)pTarget;

	case IDL:	// Identifikator ist gegeben
		{
		long ID = (long)pTarget;
		ErrInstall EI (WC_NOTFOUND);
		DB_ADDR dbaIDL(hPr);

			TX_ASSERT(ID != 0L && ID != -1L);

			dbaIDL.file_no = IDL;
			if (z_keyfind (&dbaIDL, IDN, &ID) != EC_OKAY)
				return -1L;
			return dbaIDL.rec_no;
		}
		break;

	case SICHT:
		if (pTarget != NULL) {
		char *pSicht = new char [41];

			if (pSicht == NULL) return -1L;

			TX_ASSERT(TIsValidString ((char *)pTarget));

			memset (pSicht, '\0', 41);
			strcpy (pSicht, (char *)pTarget);

			AnsiToOem (pSicht, pSicht);	// Zeichensatz konvertieren

		ErrInstall EI (WC_NOTFOUND);
		DB_ADDR dbaSICHT(hPr);
		long result = -1;

			dbaSICHT.file_no = SICHT;
			if (z_keyfind (&dbaSICHT, SICHTNAME, pSicht) == EC_OKAY)
				result = dbaSICHT.rec_no;
			DELETE (pSicht);
			return result;
		} else
			return -1L;
		break;

	default:
		TX_ASSERT(false);
		break;
	}

return -1L;
}

// Erzeugen eines neuen OBL, IDL oder SICHT-Satzes, derzeit jedoch lediglich
// Identifikatoren unterstützt.
extern "C"
long FUNCTYPE EXPORT02 CreateTarget (
	HPROJECT hPr, short iTTyp, long lTarget, long *pulNewTarget)
{
	if (NULL == pulNewTarget)
		return S_SYSERR;		// snh

	*pulNewTarget = 0L;
	switch (iTTyp) {
	case OBL_OLD:	// direkt ObjektNummer
		TX_ASSERT(false);
		break;

	case IDL:	// Identifikator ist gegeben
		{
		DB_ADDR dbaIDL(hPr);
		struct idl IDLSatz;
		ErrCode RC;

			TX_ASSERT(lTarget != 0L && lTarget != -1L);

			dbaIDL.file_no = IDL;
			memset (&IDLSatz, '\0', sizeof (IDLSatz));
			IDLSatz.idn = lTarget;
			__New (dbaIDL, IDLSatz);
			*pulNewTarget = dbaIDL.rec_no;
			return S_OKAY;
		}
		break;

	case SICHT:
		TX_ASSERT(false);
		break;

	default:
		TX_ASSERT(false);
		break;
	}

return S_DUMMY;
}

