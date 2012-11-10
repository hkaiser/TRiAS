// Einlesen aller MerkmalsInformationen eines vorgegebenen Objektes
// File: GETMI.CXX

#include "trias02p.hxx"
#include "merkinfo.hxx"

extern "C" ErrCode EXPORT02 GetMerkInfo (HPROJECT hPr, long lTarget, short iTyp, 
					 MerkInfo ***ppMI, short *Cnt) 
{
ErrCode RC;		// FehlerCode
long VOMNext = 0;
bool fText = false;

// sicherheitshalber Anzahl der Merkmale Nullsetzen
	*Cnt = 0;

	switch (iTyp) {
	case OBL_OLD:	// Merkmale eines Objektes
		{
		struct obl OBLSatz;
		DB_ADDR_OBL dbaOBL(hPr);

		// Objektsatz einlesen
//			dbaOBL.file_no = OBL;
			dbaOBL.rec_no = lTarget;
			__Read (dbaOBL, OBLSatz);

			if (GetDBVersion(hPr) < VERSION05000008 &&
			    OBLSatz.status & SB_TEXTOBJ)
			// alte DB und Textobjekt
				return WC_RETURN;

			if (OBLSatz.status & SB_TEXTOBJIND)
				fText = true;

			VOMNext = OBLSatz.zovom;
		}
		break;

	case IDL:	// Merkmale eines Identifikators
		{
			if (GetDBVersion(hPr) < VERSION05000007)
				return EC_OKAY;		// noch nicht implementiert

		struct idl IDLSatz;
		DB_ADDR dbaIDL(hPr);

			dbaIDL.file_no = IDL;
			dbaIDL.rec_no = lTarget;
			__Read (dbaIDL, IDLSatz);

			VOMNext = IDLSatz.zmerki;
		}
		break;

	case SICHT:
		{
			if (GetDBVersion(hPr) < VERSION05000007)
				return EC_OKAY;		// noch nicht implementiert

		struct sicht SICHTSatz;
		DB_ADDR dbaSICHT(hPr);

			dbaSICHT.file_no = SICHT;
			dbaSICHT.rec_no = lTarget;
			__Read (dbaSICHT, SICHTSatz);

			VOMNext = SICHTSatz.zmerkm;			
		}
		break;

	default:
		return WC_RETURN;	// kein Fehler aber != 0
	}

// Anzahl der Merkmale bestimmen
struct vom VOMSatz;
DB_ADDR dbaVOM(hPr);
short VOMCnt = 0;

	dbaVOM.file_no = VOM;
	VOMSatz.znmk = VOMNext;		// erster Satz
	do {
	// VOMSatz lesen
		if ((dbaVOM.rec_no = VOMSatz.znmk) == 0)
			break;	// Ende der Kette
		__Read (dbaVOM, VOMSatz);
	// Anzahl der MKodes bestimmen
		VOMCnt++;
	} while (TRUE);		// bis Ende der Kette erreicht ist

// Speicher anfordern
	*ppMI = new MerkInfo * [VOMCnt];
	if (*ppMI == NULL) 
		return (ErrCode)db_error (EC_NOMEMORY, RC_GetMerkInfo);

// Merkmale der Reihe nach einlesen
struct mkl MKLSatz;
DB_ADDR dbaMKL(hPr);

	dbaMKL.file_no = MKL;
	VOMSatz.znmk = VOMNext;	// noch mal von vorn
	for (short i = 0; i < VOMCnt; i++) {
	// VOMSatz lesen
		if ((dbaVOM.rec_no = VOMSatz.znmk) == 0)
			break;	// Ende der Kette
		__Read (dbaVOM, VOMSatz);

	// Merkmalswert(e) einlesen und MerkInfo bilden
		dbaMKL.rec_no = VOMSatz.zvommk;
		__Read (dbaMKL, MKLSatz);

		switch (MKLSatz.typ) {
		case 0:		// Textmerkmal
			{
			long iLen;

			// Textlänge bestimmen
				DBASSERT (GetTextLen (hPr, VOMSatz.zvommi, &iLen));
//				if (iLen <= 0) {	// #HK960116
				if (iLen < 0) {	// #HK960116
					(*ppMI)[i] = NULL;
					continue;	// nächstes Merkmal
				}
				iLen = ((iLen + 3) / 4) * 4;	
						// auf long Grenze aufrunden

			char *MText = new char [iLen+1];

				if (MText) {
				// Textmerkmal einlesen
					memset (MText, '\0', (short)(iLen+1));
					DBASSERT (GetText (hPr, VOMSatz.zvommi, MText, iLen, fText));
#if defined(MSWIND)
					OemToAnsi (MText, MText);
#endif
				} else	
					return (ErrCode)db_error (EC_NOMEMORY, RC_GetMerkInfo);

			// neue MerkInfo anlegen
				(*ppMI)[i] = new TextMerkInfo (MKLSatz.mk, MText);
				if ((*ppMI)[i] == NULL)
					return (ErrCode)db_error (EC_NOMEMORY, RC_GetMerkInfo);

			// Speicher wieder freigeben
				DELETE (MText);
			}
			break;

		case 1:		// LongMerkmal(e)
			{
			long iLen;

			// Feldlänge bestimmen
				DBASSERT (GetMerkLen (hPr, VOMSatz.zvommi, &iLen));

			long *MLong = new long [iLen];

				if (MLong) {
				// LongMerkmale einlesen
					DBASSERT (GetMerkLong (hPr, VOMSatz.zvommi, MLong, iLen));
				} else	
					return (ErrCode)db_error (EC_NOMEMORY, RC_GetMerkInfo);

			// neue MerkInfo anlegen
				(*ppMI)[i] = new LongMerkInfo (MKLSatz.mk, MLong, iLen);
				if ((*ppMI)[i] == NULL)
					return (ErrCode)db_error (EC_NOMEMORY, RC_GetMerkInfo);

			// Speicher wieder freigeben
				DELETE (MLong);
			}
			break;

		case 3:		// DoubleMerkmal(e)
			{
			long iLen;

			// Feldlänge bestimmen
				DBASSERT (GetMerkLen (hPr, VOMSatz.zvommi, &iLen));

			double *MDouble = new double [iLen];

				if (MDouble) {
				// LongMerkmale einlesen
					DBASSERT (GetMerkDouble (hPr, VOMSatz.zvommi, MDouble, iLen));
				} else	
					return (ErrCode)db_error (EC_NOMEMORY, RC_GetMerkInfo);

			// neue MerkInfo anlegen
				(*ppMI)[i] = new DoubleMerkInfo (MKLSatz.mk, MDouble, iLen);
				if ((*ppMI)[i] == NULL)
					return (ErrCode)db_error (EC_NOMEMORY, RC_GetMerkInfo);

			// Speicher wieder freigeben
				DELETE (MDouble);
			}
			break;

		default:
			(*ppMI)[i] = NULL;	// kein MerkmalsWert
			break;
		}
	}

// Anzahl der Mermale richtig setzen
	*Cnt = VOMCnt;

return EC_OKAY;		// Kein Fehler
}


