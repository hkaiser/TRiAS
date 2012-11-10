// Schreiben eines IdentifikatorSatzes in die IDL, wenn Ident noch 
// nicht vorhanden ist
// File: PUTIDENT.C

#include "trias02p.hxx"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// Generiert einen neuen IdentifikatorSatz ------------------------------------
extern "C" 
long EXPORT02 FUNCTYPE PutIdent (HPROJECT hPr, long ONr, long Ident, int iOTyp, long *pIDL) 
{
struct idl IDLSatz;
DB_ADDR dbaIDL(hPr);
ErrCode RC;                 // FehlerVariable
int (*e_notfound)(int,int,...), (*dummy)(int,int,...);

	DEX_SetDirtyGeoDB (true);

// IdentifikatorSatz suchen und ggf. neu generieren
	dbaIDL.file_no = IDL;
	DBASSERT (err_install (S_NOTFOUND, (int(*)(int,int,...))0, &e_notfound));
	if ((RC = (ErrCode)z_keyfind (&dbaIDL, IDN, &Ident)) != S_OKAY) {
	ErrCode EC = RC;

		DBASSERT (err_install (S_NOTFOUND, e_notfound, &dummy));
		if (EC == S_NOTFOUND) {
		// erstes Objekt mit diesem Ident
			memset (&IDLSatz, '\0', sizeof (IDLSatz));
			IDLSatz.idn = Ident;
			__New (dbaIDL, IDLSatz);
		} else
			return EC;
	} else {
	// nicht erstes Objekt: IDLSatz einlesen
		DBASSERT (err_install (S_NOTFOUND, e_notfound, &dummy));
		__Read (dbaIDL, IDLSatz);
	}

// Objekt in entsprechende Verbindungsliste eintragen
	if (VERSION0500000E <= GetDBVersion (hPr)) {
	// feststellen, ob dieses Objekt schon in der allgemeinen Liste hängt
	LINKTYPE rgLink = LINKTYPE_Unknown;

		if (EC_OKAY == TestLinkVIO (hPr, IDLSatz.zvio, ONr, Ident, LINKTYPE_DontCare, &rgLink)) {
//		ErrInstall EI (WC_NOTFOUND);	// wenn er hier nicht drin hängt, hängt er eben nicht hier drin

			if (LINKTYPE_Unknown == rgLink)
				DelLinkVIO (hPr, &IDLSatz.zvio,	ONr, Ident, LINKTYPE_Unknown);		// rausnehmen und vorne dran neu wegspeichern (s.u.)
		}

	// neu einhängen
		switch (iOTyp) {
		case TPPunkt:
			DBASSERT (PutLinkVIO (hPr, &IDLSatz.zpvio, ONr, Ident, LINKTYPE_Point));
			IDLSatz.lpvio++;
			break;

		case TPLinie:
			DBASSERT (PutLinkVIO (hPr, &IDLSatz.zlvio, ONr, Ident, LINKTYPE_Line));
			IDLSatz.llvio++;
			break;

		case TPFlaeche:
			DBASSERT (PutLinkVIO (hPr, &IDLSatz.zfvio, ONr, Ident, LINKTYPE_Area));
			IDLSatz.lfvio++;
			break;

		case TPText:
			DBASSERT (PutLinkVIO (hPr, &IDLSatz.ztvio, ONr, Ident, LINKTYPE_Text));
			IDLSatz.ltvio++;
			break;

		case TPKO:
			DBASSERT (PutLinkVIO (hPr, &IDLSatz.zkvio, ONr, Ident, LINKTYPE_Complex));
			IDLSatz.lkvio++;
			break;

		default:		// unbekannter Objekttyp
		case TPSO:
			DBASSERT (PutLinkVIO (hPr, &IDLSatz.zvio, ONr, Ident, LINKTYPE_Unknown));
			break;
		}
	} else {
		DBASSERT (PutLink (hPr, VIO_OLD, &IDLSatz.zvio, ONr));
	}
	__Write (dbaIDL, IDLSatz);

// Zeiger auf IDL liefern
	*pIDL = dbaIDL.rec_no;
	return S_OKAY;
}

// Objekt an der richtigen Kette im IdentifikatorSatz einhängen
extern "C"
long FUNCTYPE EXPORT02 VerifyIdent (HPROJECT hPr, long ONr, long lIdent, int iOTyp)
{
// nur bei neuen Datenbanken
	if (VERSION0500000E > GetDBVersion (hPr))
		return EC_OKAY;

// feststellen, ob dieses Objekt schon in der gewünschten Liste hängt
// neu einhängen
struct idl IDLSatz;
DB_ADDR dbaIDL(hPr);
ErrCode RC;

	dbaIDL.file_no = IDL;
	dbaIDL.rec_no = lIdent;
	__Read (dbaIDL, IDLSatz);

	switch (iOTyp) {
	case TPPunkt:
		{
			if (EC_OKAY == TestLinkVIO (hPr, IDLSatz.zpvio, ONr, lIdent, LINKTYPE_Point, NULL))
				return EC_OKAY;

			if (EC_OKAY != TestLinkVIO (hPr, IDLSatz.zvio, ONr, lIdent, LINKTYPE_Unknown, NULL))
				return db_error (EC_BADLINK, RC_VerifyIdent);

			DBASSERT(DelLinkVIO (hPr, &IDLSatz.zvio, ONr, lIdent, LINKTYPE_Unknown));		// hier rausnehmen		
			DBASSERT(PutLinkVIO (hPr, &IDLSatz.zpvio, ONr, lIdent, LINKTYPE_Point));
			IDLSatz.lpvio++;
		}
		break;

	case TPLinie:
		{
			if (EC_OKAY == TestLinkVIO (hPr, IDLSatz.zlvio, ONr, lIdent, LINKTYPE_Line, NULL))
				return EC_OKAY;

			if (EC_OKAY != TestLinkVIO (hPr, IDLSatz.zvio, ONr, lIdent, LINKTYPE_Unknown, NULL))
				return db_error (EC_BADLINK, RC_VerifyIdent);

			DBASSERT(DelLinkVIO (hPr, &IDLSatz.zvio, ONr, lIdent, LINKTYPE_Unknown));		// hier rausnehmen		
			DBASSERT(PutLinkVIO (hPr, &IDLSatz.zlvio, ONr, lIdent, LINKTYPE_Line));
			IDLSatz.llvio++;
		}
		break;
	case TPFlaeche:
		{
			if (EC_OKAY == TestLinkVIO (hPr, IDLSatz.zfvio, ONr, lIdent, LINKTYPE_Area, NULL))
				return EC_OKAY;

			if (EC_OKAY != TestLinkVIO (hPr, IDLSatz.zvio, ONr, lIdent, LINKTYPE_Unknown, NULL))
				return db_error (EC_BADLINK, RC_VerifyIdent);

			DBASSERT(DelLinkVIO (hPr, &IDLSatz.zvio, ONr, lIdent, LINKTYPE_Unknown));		// hier rausnehmen		
			DBASSERT(PutLinkVIO (hPr, &IDLSatz.zfvio, ONr, lIdent, LINKTYPE_Area));
			IDLSatz.lfvio++;
		}
		break;
	case TPText:
		{
			if (EC_OKAY == TestLinkVIO (hPr, IDLSatz.ztvio, ONr, lIdent, LINKTYPE_Text, NULL))
				return EC_OKAY;

			if (EC_OKAY != TestLinkVIO (hPr, IDLSatz.zvio, ONr, lIdent, LINKTYPE_Unknown, NULL))
				return db_error (EC_BADLINK, RC_VerifyIdent);

			DBASSERT(DelLinkVIO (hPr, &IDLSatz.zvio, ONr, lIdent, LINKTYPE_Unknown));		// hier rausnehmen		
			DBASSERT(PutLinkVIO (hPr, &IDLSatz.ztvio, ONr, lIdent, LINKTYPE_Text));
			IDLSatz.ltvio++;
		}
		break;
	case TPKO:
		{
			if (EC_OKAY == TestLinkVIO (hPr, IDLSatz.zkvio, ONr, lIdent, LINKTYPE_Complex, NULL))
				return EC_OKAY;

			if (EC_OKAY != TestLinkVIO (hPr, IDLSatz.zvio, ONr, lIdent, LINKTYPE_Unknown, NULL))
				return db_error (EC_BADLINK, RC_VerifyIdent);

			DBASSERT(DelLinkVIO (hPr, &IDLSatz.zvio, ONr, lIdent, LINKTYPE_Unknown));		// hier rausnehmen		
			DBASSERT(PutLinkVIO (hPr, &IDLSatz.zkvio, ONr, lIdent, LINKTYPE_Complex));
			IDLSatz.lkvio++;
		}
		break;

	default:		// unbekannter Objekttyp
	case TPSO:
		return (EC_BADLINK, RC_VerifyIdent);

	}

	__Write (dbaIDL, IDLSatz);
	return EC_OKAY;
}

