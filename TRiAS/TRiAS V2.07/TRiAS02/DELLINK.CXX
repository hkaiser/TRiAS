// Auf ein neues, Anne.
// File: DELLINK.C

#include "trias02p.hxx"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern "C" 
long FUNCTYPE DelLink (HPROJECT hPr, long FileNo, long *Begin, long Wert) 
{
DB_ADDR dba(hPr);
long Data[4];
long Prev = 0;
long Next; 

long RC;	// FehlerCode

// ersten Satz einlesen
	dba.file_no = (short)FileNo;
	dba.rec_no = 0;
	Next = *Begin;
// Suche des vorgegebenen Wertes
	do {
		Prev = dba.rec_no;
		if ((dba.rec_no = Next) <= 0)
		// nichts gefunden --> raus
			return S_NOTFOUND;
	// Satz aus VerbindungsDatei einlesen
		__Read (dba, Data[0]);
	// nächster Satz
		Next = Data[1];
	} while (labs (Data[0]) != Wert);

// gefundenen Satz der VerbindungsDatei freigeben
	__Dispose (dba);
	if (Prev == 0) {
	// der gesuchte Wert ist der Erste
		*Begin = Data[1];	// nächster Satz
		return S_OKAY;
	} else {
	// VerbindungsKette umhängen (letzter oder in der Mitte)
		dba.rec_no = Prev;
		__Read (dba, Data[0]);
		Data[1] = Next;
		__Write (dba, Data[0]);
	}
	return S_OKAY;
}

extern "C" 
long FUNCTYPE DelLinkVMO (HPROJECT hPr, long *pBegin, long lWert, long lMCode) 
{
	if (VERSION0500000F <= GetDBVersion(hPr)) {
	// Rückverkettung Merkmal --> Objekt ist jetzt indiziert (MCODEBSatz)
	struct mcodeb::mcodebkey key;
	DB_ADDR dbaMCODEB (hPr);

		key.zvmook = lWert;
		key.mcodek = lMCode;
		dbaMCODEB.file_no = VMO_NEW;

	// versuchen den VerbindungsSatz wiederzufinden
	ErrCode RC;
	struct mcodeb VMOSatz;
	
		DBASSERT(z_keyfind (&dbaMCODEB, MCODEB, &key));
		__Read (dbaMCODEB, VMOSatz);

#if defined(_DEBUG)
	long lCurrent = dbaMCODEB.rec_no;
#endif // _DEBUG
	long lPrev = VMOSatz.zvmopk;
	long lNext = VMOSatz.zvmonk;

		__Dispose(dbaMCODEB);	// aktuellen Satz freigeben

	// vorhergehenden Satz lesen, korrigieren und wegschreiben
		if (0 != lPrev) {
			dbaMCODEB.rec_no = lPrev;
			__Read(dbaMCODEB, VMOSatz);
		
			TX_ASSERT(VMOSatz.zvmonk == lCurrent);
			VMOSatz.zvmonk = lNext;
			__Write(dbaMCODEB, VMOSatz);
		} else
			*pBegin = lNext;

	// nachfolgenden Satz lesen, korrigieren und wegschreiben
		if (0 != lNext) {
			dbaMCODEB.rec_no = lNext;
			__Read(dbaMCODEB, VMOSatz);
		
			TX_ASSERT(VMOSatz.zvmopk == lCurrent);
			VMOSatz.zvmopk = lPrev;
			__Write(dbaMCODEB, VMOSatz);
		}
		return S_OKAY;
	}

// ansonsten alles beim Alten
	return DelLink (hPr, VMO_OLD, pBegin, lWert);
}

extern "C" 
long FUNCTYPE DelLinkVIO (HPROJECT hPr, long *pBegin, long lWert, long lIdent, LINKTYPE rgLink) 
{
	if (VERSION0500000F <= GetDBVersion(hPr)) {
	// Rückverkettung Identifikator --> Objekt ist jetzt indiziert (IDENTBSatz)
	struct identb::identbkey key;
	DB_ADDR dbaIDENTB (hPr);
	LINKTYPE rgType = rgLink;

		if (LINKTYPE_DontCare == rgLink)
			rgType = LINKTYPE_Unknown;

		key.zviook = TYPETOLINK(lWert, rgType);
		key.identk = lIdent;
		dbaIDENTB.file_no = VIO_NEW;

	// versuchen den VerbindungsSatz wiederzufinden
	ErrCode RC = (ErrCode)z_keyfind (&dbaIDENTB, IDENTB, &key);

		if (WC_NOTFOUND == RC) {
			if (LINKTYPE_DontCare != rgLink)
				return RC;		// gesucht und nichts gefunden

		// wenn nichts gefunden wurde, dann auf nächsten positionieren
			DBASSERT(z_keynext (&dbaIDENTB, IDENTB));
			DBASSERT(z_keyread (hPr, &key));
			if (key.identk != lIdent || LINKTOLINK(key.zviook) != lWert || LINKTOTYPE(key.zviook) != rgLink)
				return WC_NOTFOUND;		// nichts gefunden
		}
		if (EC_OKAY != RC)
			return RC;		// sonstiger Fehler

	struct identb VIOSatz;

		__Read (dbaIDENTB, VIOSatz);

#if defined(_DEBUG)
	long lCurrent = dbaIDENTB.rec_no;
#endif // _DEBUG
	long lPrev = VIOSatz.zviopk;
	long lNext = VIOSatz.zvionk;

		__Dispose(dbaIDENTB);	// aktuellen Satz freigeben

	// vorhergehenden Satz lesen, korrigieren und wegschreiben
		if (0 != lPrev) {
			dbaIDENTB.rec_no = lPrev;
			__Read(dbaIDENTB, VIOSatz);
		
			TX_ASSERT(VIOSatz.zvionk == lCurrent);
			VIOSatz.zvionk = lNext;
			__Write(dbaIDENTB, VIOSatz);
		} else
			*pBegin = lNext;

	// nachfolgenden Satz lesen, korrigieren und wegschreiben
		if (0 != lNext) {
			dbaIDENTB.rec_no = lNext;
			__Read(dbaIDENTB, VIOSatz);
		
			TX_ASSERT(VIOSatz.zviopk == lCurrent);
			VIOSatz.zviopk = lPrev;
			__Write(dbaIDENTB, VIOSatz);
		}
		return S_OKAY;
	}

// ansonsten alles beim Alten
	return DelLink (hPr, VIO_OLD, pBegin, lWert);
}

///////////////////////////////////////////////////////////////////////////////
// Testen, ob ein Satz in einer Kette enthalten ist
extern "C" 
long FUNCTYPE TestLink (HPROJECT hPr, long lFileNo, long lFirst, long lValue)
{
DB_ADDR dba(hPr);
long Data[4];
long lNext = lFirst; 
long RC = EC_OKAY;	// FehlerCode

// ersten Satz einlesen
	dba.file_no = (short)lFileNo;
	dba.rec_no = 0;

// Suche des vorgegebenen Wertes
	do {
		if ((dba.rec_no = lNext) <= 0)
		// nichts gefunden --> raus
			return S_NOTFOUND;

	// Satz aus VerbindungsDatei einlesen
		__Read (dba, Data[0]);

	// nächster Satz
		lNext = Data[1];
	} while (labs (Data[0]) != lValue);

	return S_OKAY;
}

extern "C" 
long FUNCTYPE TestLinkVIO (
	HPROJECT hPr, long lFirst, long lValue, long lIdent, LINKTYPE rgLink, LINKTYPE *prgLink)
{
	if (VERSION0500000F <= GetDBVersion(hPr)) {
	ErrInstall EI (WC_NOTFOUND);
	struct identb::identbkey key;
	DB_ADDR dbaIDENTB (hPr);
	LINKTYPE rgType = rgLink;

		if (LINKTYPE_DontCare == rgType)
			rgType = LINKTYPE_Unknown;

		key.identk = lIdent;
		key.zviook = TYPETOLINK(lValue, rgType);
		dbaIDENTB.file_no = VIO_NEW;

	// versuchen den VerbindungsSatz wiederzufinden
	ErrCode RC = (ErrCode)z_keyfind (&dbaIDENTB, IDENTB, &key);

		if (WC_NOTFOUND == RC) {
			if (LINKTYPE_DontCare != rgLink)
				return RC;		// gesucht und nichts gefunden

		// wenn nichts gefunden wurde, dann auf nächsten positionieren
			DBASSERT(z_keynext (&dbaIDENTB, IDENTB));
			DBASSERT(z_keyread (hPr, &key));
			if (key.identk != lIdent || LINKTOLINK(key.zviook) != lValue)
				return WC_NOTFOUND;		// nichts gefunden

		// Key ist bereits eingelesen, also sind wir fertig
			if (NULL != prgLink) {
				*prgLink = LINKTOTYPE(key.zviook);
				return RC;
			}
		}

	// wenn der Verbindungssatz gefunden wurde und der exakte Type gewünscht ist, dann
	// diesen auch liefern
		if (EC_OKAY == RC && NULL != prgLink) {
			DBASSERT(z_keyread (hPr, &key));
			*prgLink = LINKTOTYPE(key.zviook);
		}
		return RC;
	}

// alles beim Alten
	return TestLink (hPr, VIO_OLD, lFirst, lValue);
}


