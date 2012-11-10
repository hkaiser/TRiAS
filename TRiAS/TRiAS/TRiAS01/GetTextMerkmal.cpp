// @doc
// @module GetTextMerkmal.cpp | Lesen eines ausgewaehlten TextMerkmales fuer ein Objekt

#include "trias01p.hxx"

#include <ErrInst.hxx>
#include <NativeObject.h>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Liest ein TextMerkmal für das vorgegebene Objekt
HRESULT GetTextMerkmal (HPROJECT hPr, long lMCode, long lFirst, short iTyp, char **ppMText) 
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

	if (lFirst == -1L) return S_OK;

	switch (iTyp) {
	case OBL_OLD:		// normales ObjektMerkmal
		{
		struct obl OBLSatz;
		DB_ADDR_OBL dbaOBL(hPr);

		// Objektsatz einlesen
			dbaOBL.rec_no = lFirst;
			__ReadHR (dbaOBL, OBLSatz);

			if (LocGetDBVersion(hPr) < VERSION05000008 && OBLSatz.status & SB_TEXTOBJ)
			// alte DB und Textobjekt
				return S_FALSE;

			if (OBLSatz.status & SB_TEXTOBJIND)
				fText = true;
			VOMNext = OBLSatz.zovom;        // erster Satz
		}
		break;

	case IDL_OLD:		// IdentifikatorMerkmal
		{
			if (LocGetDBVersion(hPr) < VERSION05000007)
				return S_FALSE;		// noch nicht implementiert

		struct idl IDLSatz;
		DB_ADDR_IDL dbaIDL(hPr);

//			dbaIDL.file_no = IDL;
			dbaIDL.rec_no = lFirst;
			__ReadHR (dbaIDL, IDLSatz);

			VOMNext = IDLSatz.zmerki;
		}
		break;

	case SICHT:		// SichtMerkmal
		{
			if (LocGetDBVersion(hPr) < VERSION05000007)
				return S_FALSE;		// noch nicht implementiert

		struct sicht SICHTSatz;
		DB_ADDR dbaSICHT(hPr);

			dbaSICHT.file_no = SICHT;
			dbaSICHT.rec_no = lFirst;
			__ReadHR (dbaSICHT, SICHTSatz);

			VOMNext = SICHTSatz.zmerkm;			
		}
		break;

	default:
		return E_INVALIDARG;
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
		__ReadHR (dbaVOM, VOMSatz);

	// MKLSatz lesen
		dbaMKL.rec_no = VOMSatz.zvommk;
		__ReadHR (dbaMKL, MKLSatz);

	// nächster VOMSatz
		VOMNext = VOMSatz.znmk;
	} while (MKLSatz.mk != lMCode);          // bis lMCode gefunden

// wenn für dieses Objekt MCode nicht exitiert: wieder raus mit Warnung
	if (MKLSatz.mk != lMCode)
		return HRESULT_FROM_ERRCODE(WC_NOTFOUND);

// Prüfen, ob MerkmalsTyp stimmt
	if (MKLSatz.typ != 0)	// kein TextMerkmal
		return HRESULT_FROM_ERRCODE(WC_BADMKTYP);

// TextInfo einlesen
	DBASSERTHR (GetTextMerkmalLen (hPr, VOMSatz.zvommi, &iLen));
	if (iLen == 0 || iLen == -1) {
	// entweder kein Text oder Text aus Bezugsobjekt
		if (iTyp != OBL_OLD && SICHT != iTyp && IDL_OLD != iTyp)	// kein ObjektMerkmal
			return HRESULT_FROM_ERRCODE(WC_BADMKTYP);

		ATLTRY(*ppMText = new char [1]);
		if (*ppMText == NULL) 
			return E_OUTOFMEMORY;

		**ppMText = '\0';
		return S_OK;		// leerer TextString gegeben
	} else if (iLen < 0)
		iLen = -iLen;		// indirektes Textobjekt

	iLen = ((iLen + 3) / 4) * 4;	// auf long Grenze aufrunden
	ATLTRY(*ppMText = new char[iLen+1]);
	if (NULL == *ppMText) 
		return E_OUTOFMEMORY;

	memset (*ppMText, '\0', (size_t)(iLen+1));
	DBASSERTHR (GetTextFromDBT (hPr, VOMSatz.zvommi, *ppMText, iLen, fText));
	OemToAnsi (*ppMText, *ppMText);
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Bestimmt den konkreten TargetPointer in Abhängigkeit von dem MerkmalsTyp
long GetMerkmalTarget (HPROJECT hPr, void *pTarget, short iTTyp)
{
	switch (iTTyp) {
	case OBL_OLD:	// direkt ObjektNummer
		TX_ASSERT((long)pTarget > 0);
		return (long)pTarget;

	case IDL_OLD:	// Identifikator ist gegeben
		{
		long ID = (long)pTarget;
		ErrInstall EI (WC_NOTFOUND);
		DB_ADDR_IDL dbaIDL(hPr);

			TX_ASSERT(ID != 0L && ID != -1L);

//			dbaIDL.file_no = IDL;
			if (z_keyfind (&dbaIDL, IDN_OLD, &ID) != EC_OKAY)
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

//			AnsiToOem (pSicht, pSicht);	// Zeichensatz konvertieren

		ErrInstall EI (WC_NOTFOUND);
		DB_ADDR dbaSICHT(hPr);
		long result = -1;

			dbaSICHT.file_no = SICHT;
			if (z_keyfind (&dbaSICHT, SICHTNAME, pSicht) == EC_OKAY)
				result = dbaSICHT.rec_no;
			DELETE_OBJ (pSicht);
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

/////////////////////////////////////////////////////////////////////////////
// Erzeugen eines neuen OBL, IDL oder SICHT-Satzes, derzeit jedoch lediglich
// Identifikatoren unterstützt.
HRESULT CreateMerkmalTarget (HPROJECT hPr, short iTTyp, long lTarget, long *pulNewTarget)
{
	if (NULL == pulNewTarget)
		return S_SYSERR;		// snh

	*pulNewTarget = 0L;
	switch (iTTyp) {
	case OBL_OLD:	// direkt ObjektNummer
		TX_ASSERT(false);
		break;

	case IDL_OLD:	// Identifikator ist gegeben
		{
		DB_ADDR_IDL dbaIDL(hPr);
		struct idl IDLSatz;
		ErrCode RC;

			TX_ASSERT(lTarget != 0L && lTarget != -1L);

//			dbaIDL.file_no = IDL;
//			memset (&IDLSatz, '\0', sizeof (IDLSatz));
			IDLSatz.idn = lTarget;
			__NewHR (dbaIDL, IDLSatz);
			*pulNewTarget = dbaIDL.rec_no;
			return S_OK;
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

/////////////////////////////////////////////////////////////////////////////
// Länge eines Textmerkmales bestimmen
HRESULT GetTextMerkmalLen (HPROJECT hPr, long madr, long *plLen) 
{
DB_ADDR	dba(hPr);
struct kdbt dbt_satz;	// Satz der Datei '.dbt'
int RC;

// Kein Text da (Textlänge gleich 0)
	if (0 == madr) {
		*plLen = 0;
		return S_OK;
	}

	dba.file_no = FDBT;
	dba.rec_no = madr;
	*plLen = 0;

	__ReadHR (dba, dbt_satz);
	*plLen = dbt_satz.llen;
	if (*plLen != -1L)
		*plLen *= sizeof(INT);	// wirkliche Textlänge
	
	return S_OKAY;
}

