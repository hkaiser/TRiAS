// Erzeugen eines neuen Satzes in einer Verbindungsdatei ----------------------
// File: PUTLINK.C

#include "trias02p.hxx"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// PUTLINK erzeugt einen neuen Satz am Kopf einer gegebenen VerbindungsKette.
extern "C" 
long EXPORT02 FUNCTYPE PutLink (HPROJECT hPr, long FileNo, long *Begin, long Wert) 
{
DB_ADDR dba(hPr);	// neue Datenbankadresse
long Data[4];
ErrCode RC;	// FehlerCode 

// Neuen Satz erzeugen und am Anfang der gegebenen Kette einfügen
	dba.file_no = (short)FileNo;

// Satz neu zusammensetzen
	Data[0] = Wert;		// TargetSatz eintragen
	Data[1] = *Begin;	// altes erstes Element
	Data[2] = 0;		// evtl. drittes/viertes Element ausnullen
	Data[3] = 0;

// Satz neu bilden
	*Begin = 0;		// für alle Fälle Nullsetzen
	__New (dba, Data);	// Satz neu anfordern
	*Begin = dba.rec_no;	// neues erstes Element
	return S_OKAY;
}

// Anhängen eines Satzes an das KettenEnde ------------------------------------
long FUNCTYPE PutChainEnd (HPROJECT hPr, long FileNo, long *pBegin, long Wert)
{
DB_ADDR dba(hPr);	// neue Datenbankadresse
long Data[4];
ErrCode RC;	// FehlerCode 
long lLast = 0;

// KettenEnde finden
	dba.file_no = (short)FileNo;
	dba.rec_no = *pBegin;
	while (dba.rec_no) {
		__Read (dba, Data);
		lLast = dba.rec_no;	// vorhergehendes Element der Kette
		dba.rec_no = Data[1];	// weiter in der Kette
	}
		
// Neuen Satz erzeugen und am Ende der gegebenen Kette einfügen
// Satz neu zusammensetzen
	Data[0] = Wert;		// TargetSatz eintragen
	Data[1] = 0;		// erstmal Ende der Kette
	Data[2] = 0;		// evtl. drittes/viertes Element ausnullen
	Data[3] = 0;

// Satz neu bilden
	__New (dba, Data);	// Satz neu anfordern

// in Kette einfügen
	if (lLast == 0)
		*pBegin = dba.rec_no;	// neues erstes Element
	else {
	// am Ende der Kette eintragen
	long lNew = dba.rec_no;

		dba.rec_no = lLast;	// letzten Satz lesen
		__Read (dba, Data);
		Data[1] = lNew;		// modfizieren 
		__Write (dba, Data);	// und wieder wegschreiben
	}
	return S_OKAY;
}

// PUTLINK erzeugt einen neuen Satz am Kopf einer gegebenen VerbindungsKette.
extern "C" 
long EXPORT02 FUNCTYPE PutLinkVMO (HPROJECT hPr, long *pBegin, long lWert, long lMCode) 
{
	if (VERSION0500000F <= GetDBVersion(hPr)) {
	// Rückverkettung Merkmal --> Objekt ist jetzt indiziert (MCODEBSatz)
	struct mcodeb MCODEBSatz;
	DB_ADDR dbaMCODEB (hPr);
	ErrCode RC;

		dbaMCODEB.file_no = VMO_NEW;
		MCODEBSatz.mcodebkey.zvmook = lWert;		// TargetSatz 
		MCODEBSatz.mcodebkey.mcodek = lMCode;		// MerkmalsCode
		MCODEBSatz.zvmonk = *pBegin;	// altes erstes Element
//		MCODEBSatz.zvmopk = 0L;			// vorhergehendes Element existiert nicht

		*pBegin = 0;					// für alle Fälle Nullsetzen
		__New (dbaMCODEB, MCODEBSatz);	// neues Satz generieren (incl. Index)
		*pBegin = dbaMCODEB.rec_no;		// neues erstes Element

		if (0 != MCODEBSatz.zvmonk) {
		// Rückverkettung eintragen
			dbaMCODEB.rec_no = MCODEBSatz.zvmonk;
			__Read(dbaMCODEB, MCODEBSatz);

			TX_ASSERT(0 == MCODEBSatz.zvmopk);
			MCODEBSatz.zvmopk = *pBegin;
			__Write(dbaMCODEB, MCODEBSatz);
		}
		return S_OKAY;
	}

// ansonsten alles beim Alten
	return PutLink (hPr, VMO_OLD, pBegin, lWert);
}

extern "C" 
long EXPORT02 FUNCTYPE PutLinkVIO (HPROJECT hPr, long *pBegin, long lWert, long lIdent, LINKTYPE rgLink) 
{
	if (VERSION0500000F <= GetDBVersion(hPr)) {
	// Rückverkettung Merkmal --> Objekt ist jetzt indiziert (MCODEBSatz)
	struct identb IDENTBSatz;
	DB_ADDR dbaIDENTB (hPr);
	ErrCode RC;

		dbaIDENTB.file_no = VIO_NEW;
		IDENTBSatz.identbkey.zviook = TYPETOLINK(lWert, rgLink);		// TargetSatz 
		IDENTBSatz.identbkey.identk = lIdent;		// MerkmalsCode
		IDENTBSatz.zvionk = *pBegin;	// altes erstes Element
//		IDENTBSatz.zviopk = 0L;			// vorhergehendes Element existiert nicht

		*pBegin = 0;					// für alle Fälle Nullsetzen
		__New (dbaIDENTB, IDENTBSatz);	// neues Satz generieren (incl. Index)
		*pBegin = dbaIDENTB.rec_no;		// neues erstes Element

		if (0 != IDENTBSatz.zvionk) {
		// Rückverkettung eintragen
			dbaIDENTB.rec_no = IDENTBSatz.zvionk;
			__Read(dbaIDENTB, IDENTBSatz);

			TX_ASSERT(0 == IDENTBSatz.zviopk);
			IDENTBSatz.zviopk = *pBegin;
			__Write(dbaIDENTB, IDENTBSatz);
		}
		return S_OKAY;
	}

// ansonsten alles beim Alten
	return PutLink (hPr, VIO_OLD, pBegin, lWert);
}

