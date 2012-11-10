// Loeschen des IdentifikatorSatzes fuer ein vorgegebenes Objekt
// File: DELID.C

#include "trias02p.hxx"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#if defined(_FORCE_LEGACY_CODE)
short GetObjectType (struct obl *pOBLSatz);
#endif // defined(_FORCE_LEGACY_CODE)

extern "C" 
long EXPORT02 FUNCTYPE delid (HPROJECT hPr, long ON, int *piOType) 
{
#if defined(_FORCE_LEGACY_CODE)
// 1. ObjektSatz löschen
struct obl OBLSatz;
struct idl IDLSatz;
DB_ADDR_OBL dbaOBL(hPr);
DB_ADDR dbaIDL(hPr);
long RC;		// FehlerCode

	DEX_SetDirtyGeoDB (true);

// Objektsatz einlesen
//	dbaOBL.file_no = OBL;
	dbaOBL.rec_no = ON;
	__Read (dbaOBL, OBLSatz);

// IdentifikatorSatz lesen
	dbaIDL.file_no = IDL;
	dbaIDL.rec_no = OBLSatz.zoid;
	__Read (dbaIDL, IDLSatz);

	if (VERSION0500000E <= GetDBVersion(hPr)) {
//	ErrInstall EI (WC_NOTFOUND);	// da der Reihe nach abgefragt wird

		TX_ASSERT(NULL != piOType);

	long lIdent = IDLSatz.idn;		// behandelter Identifikator
	int iOType = ::GetObjectType (&OBLSatz);

		RC = WC_NOTFOUND;
		switch (iOType) {
		case TPPunkt:
			RC = DelLinkVIO (hPr, &IDLSatz.zpvio, ON, lIdent, LINKTYPE_Point);
			if (EC_OKAY == RC) {
				*piOType = TPPunkt;
				IDLSatz.lpvio--;

				TX_ASSERT(0 <= IDLSatz.lpvio);
				TX_ASSERT(0 != IDLSatz.zpvio || 0 == IDLSatz.lpvio);
			}		
			break;

		case TPLinie:
			RC = DelLinkVIO (hPr, &IDLSatz.zlvio, ON, lIdent, LINKTYPE_Line);
			if (EC_OKAY == RC) {
				*piOType = TPLinie;
				IDLSatz.llvio--;

				TX_ASSERT(0 <= IDLSatz.llvio);
				TX_ASSERT(0 != IDLSatz.zlvio || 0 == IDLSatz.llvio);
			}
			break;

		case TPFlaeche:
			RC = DelLinkVIO (hPr, &IDLSatz.zfvio, ON, lIdent, LINKTYPE_Area);
			if (EC_OKAY == RC) {
				*piOType = TPFlaeche;
				IDLSatz.lfvio--;

				TX_ASSERT(0 <= IDLSatz.lfvio);
				TX_ASSERT(0 != IDLSatz.zfvio || 0 == IDLSatz.lfvio);
			}
			break;

		case TPText:
			RC = DelLinkVIO (hPr, &IDLSatz.ztvio, ON, lIdent, LINKTYPE_Text);
			if (EC_OKAY == RC) {
				*piOType = TPText;
				IDLSatz.ltvio--;

				TX_ASSERT(0 <= IDLSatz.ltvio);
				TX_ASSERT(0 != IDLSatz.ztvio || 0 == IDLSatz.ltvio);
			} 
			break;

		case TPKO:
			RC = DelLinkVIO (hPr, &IDLSatz.zkvio, ON, lIdent, LINKTYPE_Complex);
			if (EC_OKAY == RC) {
				*piOType = TPKO;
				IDLSatz.lkvio--;

				TX_ASSERT(0 <= IDLSatz.lkvio);
				TX_ASSERT(0 != IDLSatz.zkvio || 0 == IDLSatz.lkvio);
			} 
			break;

		case TPSO:
		default:
			RC = DelLinkVIO (hPr, &IDLSatz.zvio, ON, lIdent, LINKTYPE_Unknown);
			if (EC_OKAY == RC) 
				*piOType = TPUnknown;
			break;
		}

		if (EC_OKAY != RC)
			return RC;		// nichts gefunden oder Fehler

	} else {
	// ON aus Verbindungsdatei VIO löschen
		DBASSERT (DelLink (hPr, VIO_OLD, &IDLSatz.zvio, ON));
	}

// testen, ob keine Merkmale und keine Relationen mehr vorhanden sind
	if (IsEmptyIDL (hPr, &IDLSatz)) {
		// einziges (und letztes) Objekt --> IDL freigeben
		__Dispose (dbaIDL);
		return EC_OKAY;
	} 

// modifizierten Satz wegschreiben
	__Write (dbaIDL, IDLSatz);
	return S_OKAY;
#else
	TX_ASSERT(SUCCEEDED(E_UNEXPECTED));
	return ERRCODE_FROM_HRESULT(E_FAIL);
#endif // defined(_FORCE_LEGACY_CODE)
}
