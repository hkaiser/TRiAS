// File: DBGETGI.CXX

#include "trias02p.hxx"

#include <switchkc.h>

#include <hdrentry.hxx>
#include "konsobj.hxx"

#if defined(_DEBUG)
extern "C" short g_iKonsFlags;
#endif // _DEBUG

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// Größe der Geometriefelder 
#define XYLEN	300L

// DatenBasis :: GetGI liest Geometrie eines DB-Objektes und übergibt einen
// Pointer auf ein GeoObjekt (GeoPunkt, GeoKante oder GeoMasche)
ErrCode GeoDB :: GetGI (long ObjNr, GeoObjekt ** ppGO, ObjContainer *pOC) 
{
KoOrd *x, *y;           // Geometriefelder
long NachLaden = 0;     // NachladeParameter
long warNachLaden = 0;  // NachLadeParameter des vorhergehenden Aufrufs
long Ident = 0;         // Objektidentifikator
long Len = XYLEN;       // Länge der Felder x und y
long UsedLen = 0;       // Anzahl der genutzten Feldelemente
long Status[2];         // Objektstatus
ErrCode RC;
long fex, fey;          // Nummern der dynamischen Felder
long Cont[4];		// ObjektContainer

// DatenBasis aktivieren 
	if (!isOpened()) return EC_NOOPEN;	// DB nicht eröffnet

CActDB ActDB (*this);
ErrInstall EI (EC_STATUSERROR);

// Geometrie anfordern
	*ppGO = NULL;           // Anfangswert
	do {
		UsedLen = 0;
		warNachLaden = NachLaden;
		fex = fey = 0L;                 // initialisieren
		RC = (ErrCode)getgi (DBDesc(), &NachLaden, &ObjNr, &Ident, Status, 
				     &Len, &UsedLen, &fex, &fey, 
				     Cont, (long *)pOC);
		if (RC != EC_OKAY && RC != WC_FORT) {
		// Fehler 
			if (fex) ferel_ (&fex); 
			if (fey) ferel_ (&fey);   // Felder freigeben
			// Ergebnis: 
			*ppGO = NULL;
			return (RC);
		}
	// GeoObjekte bilden
		FlexAdr ((short)fex, &x);       // Feldadressen holen
		FlexAdr ((short)fey, &y);

	// ElementarObjekte 
		if (Status[0] == 1) switch (Status[1]) {
		case 1:         // PunktObjekt
			*ppGO = new GeoPunkt (*this, ObjNr, Ident, 
					       Punkt (x[0], y[0]));
			break;

		case 2:         // KantenObjekt
			*ppGO = new GeoKante (*this, ObjNr, Ident, 
						      x, y, UsedLen);
			if (*ppGO)
				((GeoKante *)(*ppGO)) -> SetCont (Cont);
			break;

		case 3:         // Flächenobjekt
			{
			if (*ppGO == NULL) {
			// erste Geometrieportion       
				*ppGO = new GeoFlaeche (*this, ObjNr, Ident, 
							       x, y, UsedLen
				);
				if (*ppGO)
					((GeoFlaeche *)(*ppGO)) -> SetCont (Cont);
			} else if (warNachLaden == WC_FORT) { 
				((GeoFlaeche *)(*ppGO)) -> AddKante (
							x, y, UsedLen, -1
				);
			}
			break;
			}

		case 4:		// TextObjekt
			{
			char *pText;
			TextObjTyp ToTyp;

				DBASSERT (ReadText (ObjNr, pText, ToTyp));
				if (ToTyp == TOT_TEXT) {
					*ppGO = new GeoText (*this, ObjNr, Ident, Punkt (x[0], y[0]), pText);
				} else if (TOT_TEXTIND == ToTyp) {
					*ppGO = new GeoTextInd (*this, ObjNr, Ident, Punkt (x[0], y[0]), *(long *)pText);
				} else {
					TX_ASSERT(TOT_TEXTINDOBJPROP == ToTyp);
					*ppGO = new GeoTextIndOP (*this, ObjNr, Ident, Punkt (x[0], y[0]), pText);
				}
				DELETE (pText);
			}
			break;

		default:
			*ppGO = NULL;
			break;
		} else if (Status[0] == 2) {
		// Komplexobjekte
			*ppGO = new KomplexObjekt (*this, ObjNr, Ident);
		}

	// Felder wieder freigeben
		ferel_ (&fex);  
		ferel_ (&fey);
	// Fehler aufgetreten         
		if (*ppGO == NULL) 
			return ((ErrCode)db_error ((int)EC_NOMEMORY, (int)RC_DBOGetGI));
	} while (NachLaden);

return EC_OKAY;
}

// Finden aller Objekte mit einem Identifikator -------------------------------
typedef struct tagENUMIDENTDATA {
	long *pFlexNum;
	short *pOTyp;
	long *plObjCnts;
} ENUMIDENTDATA;

BOOL CALLBACK StoreObjNr (long lONr, short OTyp, void *pData)
{
ENUMIDENTDATA *pEID = (ENUMIDENTDATA *)pData;

	if (pEID -> pOTyp != NULL)	// ObjektTyp liefern
		*(pEID -> pOTyp) |= OTyp;

	if (NULL != pEID -> plObjCnts) {
		switch (OTyp) {
		case TPPunkt:	(pEID -> plObjCnts)[0] += 1; break;
		case TPLinie:	(pEID -> plObjCnts)[1] += 1; break;
		case TPFlaeche:	(pEID -> plObjCnts)[2] += 1; break;
		case TPText:	(pEID -> plObjCnts)[3] += 1; break;
		default:
			break;
		}
	}

	if (NULL == pEID -> pFlexNum) 
		throw true;	// mindestens ein Objekt vorhanden, Enumeration abbrechen

// Objektnummer wegschreiben
	return feput_ (pEID -> pFlexNum, &lONr) > 0;
}

ErrCode GeoDB::FindId (long lIdent, long *plFlexNum, short *pOTyp, long *plObjCnts) 
{
ErrCode RC;

// dynamisches Feld anfordern
	if (NULL != plFlexNum && 0 == *plFlexNum) 
		DBASSERT (feini_ (plFlexNum));

// Objekte reinfüllen
ENUMIDENTDATA EID;

	EID.pFlexNum = plFlexNum;
	EID.pOTyp = pOTyp;
	EID.plObjCnts = plObjCnts;

	if (!EnumIdentObjects (lIdent, (ENUMLONGKEYPROC)StoreObjNr, &EID))
	// Fehler aufgetreten
		return (ErrCode)GetDBStatus();

// evtl. ObjektZähler richten
	if (NULL != plObjCnts && NULL != pOTyp && VERSION0500000E <= GetDBVersion()) 
	{
		DBASSERT(GetIdentObjectCounts (lIdent, plObjCnts));

	// wenn der Objekttyp vertreten ist, dann muß der Zähler positiv sein
		TX_ASSERT(!(*pOTyp & TPPunkt) || 0 < plObjCnts[0]);
		TX_ASSERT(!(*pOTyp & TPLinie) || 0 < plObjCnts[1]);
		TX_ASSERT(!(*pOTyp & TPFlaeche) || 0 < plObjCnts[2]);
		TX_ASSERT(!(*pOTyp & TPText) || 0 < plObjCnts[3]);
	} 

	if (NULL != plFlexNum) {
	long iLen = 0;

		DBASSERT (felen_ (plFlexNum, &iLen));
		if (iLen == 0) 
			return WC_NOTFOUND;
	}

	return EC_OKAY;
}

ErrCode GeoDB::GetIdentObjectCounts (LONG lIdent, long *plObjCnts)
{
	TX_ASSERT(VERSION0500000E <= GetDBVersion());
	TX_ASSERT(NULL != plObjCnts);

CActDB ActDB (*this);
DB_ADDR dba (DBDesc());
struct idl IdSatz;
ErrCode RC;

	{
	// Fehler WC_NOTFOUND ignorieren
	ErrInstall EI (WC_NOTFOUND);

	// ID finden
		dba.file_no = IDL;
		RC = (ErrCode)z_keyfind (&dba, IDN, &lIdent);
		if (RC != EC_OKAY) {
		// Fehler aufgetreten

			if (RC == WC_NOTFOUND) 
				return EC_OKAY;
			return RC;
		}
	}

// IdentSatz lesen
	__Read (dba, IdSatz);

// Zähler kopieren
	plObjCnts[0] = IdSatz.lpvio;
	plObjCnts[1] = IdSatz.llvio;
	plObjCnts[2] = IdSatz.lfvio;
	plObjCnts[3] = IdSatz.ltvio;

	return EC_OKAY;
}

typedef BOOL (CALLBACK *ENUMIDENTOBJECTCALLBACK)(long, short, void *);

inline BOOL EnumIdentObjectsCallback (BOOL (*pFcn)(long, BOOL, void *), 
				      long Key, short iOTyp, void *pData)
{
	return ((ENUMIDENTOBJECTCALLBACK)pFcn)(Key, iOTyp, pData);
}

inline BOOL EnumIdentObjectsCallbackEx (BOOL (*pFcn)(long, DWORD, void *), 
					long Key, DWORD iOTyp, void *pData)
{
	return ((ENUMLONGKEYEXCALLBACK)pFcn)(Key, iOTyp, pData);
}

// Enumeration aller Objekte mit einem Identifikator ---------------------------
short GetObjectType (struct obl *pOBLSatz);

BOOL GeoDB::EnumObjectsIdl (
	long lIdent, long lNext, bool (*pFcn)(long, bool, void *), void *pData)
{
CActDB ActDB (*this);
DB_ADDR dba (DBDesc());
DB_ADDR_OBL dbaOBL (DBDesc());
struct obl OBLSatz;
bool iRC = true;
ErrCode RC;

	dba.rec_no = lNext;               // erster Satz in VIO
//	dbaOBL.file_no = OBL;

	if (VERSION0500000F <= GetDBVersion()) {
	struct identb VIOSatz;

		dba.file_no = VIO_NEW;
		while (iRC && dba.rec_no != 0) {
		// lfd. VIOSatz lesen
			if ((RC = (ErrCode)z_readrec (&dba, &VIOSatz)) != EC_OKAY) {
				iRC = false;
				break;
			}
			TX_ASSERT(lIdent == VIOSatz.identbkey.identk);

		// ObjektSatz lesen, Typ feststellen
		long lIdLink = LINKTOLINK(VIOSatz.identbkey.zviook);

			dbaOBL.rec_no = lIdLink;
			if ((RC = (ErrCode)z_readrec (&dbaOBL, &OBLSatz)) != EC_OKAY) {
				iRC = false;
				break;
			}

		short iOTyp = ::GetObjectType (&OBLSatz);

			try {
			// Objektnummer liefern
				iRC = EnumIdentObjectsCallback (pFcn, lIdLink, iOTyp, pData);
			} catch (bool fResult) {
			// abbrechen der Enumeration
				iRC = fResult;
				break;			// beí neuen GeoDB's hier aufhören
			}
			ActDB.ReActivate();	// für alle Fälle wieder aktivieren
			dba.rec_no = VIOSatz.zvionk;
		}
		return iRC;
	}

// hier ist alles beim Alten
struct vio VIOSatz;

	dba.file_no = VIO_OLD;
	while (iRC && dba.rec_no != 0) {
	// lfd. VIOSatz lesen
		if ((RC = (ErrCode)z_readrec (&dba, &VIOSatz)) != EC_OKAY) {
			iRC = false;
			break;
		}

	// ObjektSatz lesen, Typ feststellen
		dbaOBL.rec_no = VIOSatz.zvioo;
		if ((RC = (ErrCode)z_readrec (&dbaOBL, &OBLSatz)) != EC_OKAY) {
			iRC = false;
			break;
		}

	short iOTyp = ::GetObjectType (&OBLSatz);

		try {
		// Objektnummer liefern
			iRC = EnumIdentObjectsCallback (pFcn, VIOSatz.zvioo, iOTyp, pData);
		} catch (bool fResult) {
		// abbrechen der Enumeration
			iRC = fResult;
			if (VERSION0500000E <= GetDBVersion())
				break;		// beí neuen GeoDB's hier aufhören
		}
		ActDB.ReActivate();	// für alle Fälle wieder aktivieren
		dba.rec_no = VIOSatz.znvio;
	}
	return iRC;
}

BOOL GeoDB::EnumIdentObjects (
	long Ident, BOOL (*pFcn)(long, BOOL, void *), void *pData)
{
DB_ADDR dba (DBDesc());
struct idl IdSatz;
ErrCode RC;

// DatenBasis aktivieren
CActDB ActDB (*this);

// erstes Objekt suchen
	{
	// Fehler WC_NOTFOUND ignorieren
	ErrInstall EI (WC_NOTFOUND);

	// ID finden
		dba.file_no = IDL;
		RC = (ErrCode)z_keyfind (&dba, IDN, &Ident);
		if (RC != EC_OKAY) {
		// Fehler aufgetreten

			if (RC == WC_NOTFOUND) 
				return true;
			return false;
		}
	}

// über Verbindungsliste VIO alle Objekte holen
	if ((RC = (ErrCode)z_readrec (&dba, &IdSatz)) != EC_OKAY) return false;

// Hauptliste durchgehen
	if (!EnumObjectsIdl (Ident, IdSatz.zvio, pFcn, pData)) return false;

	if (VERSION0500000E <= GetDBVersion()) {
	// EinzelListen durchgehen
		if (!EnumObjectsIdl (Ident, IdSatz.zpvio, pFcn, pData)) 
			return false;
		if (!EnumObjectsIdl (Ident, IdSatz.zlvio, pFcn, pData)) 
			return false;
		if (!EnumObjectsIdl (Ident, IdSatz.zfvio, pFcn, pData)) 
			return false;
		if (!EnumObjectsIdl (Ident, IdSatz.ztvio, pFcn, pData)) 
			return false;
		if (!EnumObjectsIdl (Ident, IdSatz.zkvio, pFcn, pData)) 
			return false;
	} 

	return true;
}

BOOL GeoDB::EnumObjectsIdlEx (
	long lIdent, long lNext, BOOL fVerifyType,
	BOOL (*pFcn)(long, DWORD, void *), void *pData, DWORD dwData)
{
CActDB ActDB (*this);
DB_ADDR dba (DBDesc());
bool iRC = true;
ErrCode RC;

	dba.rec_no = lNext;               // erster Satz in VIO

	if (VERSION0500000F <= GetDBVersion()) {
	struct identb VIOSatz;

		dba.file_no = VIO_NEW;
		while (iRC && dba.rec_no != 0) {
		// lfd. VIOSatz lesen
			if ((RC = (ErrCode)z_readrec (&dba, &VIOSatz)) != EC_OKAY) 
			{
				iRC = false;
				break;
			}
			TX_ASSERT(lIdent == VIOSatz.identbkey.identk);

		// ObjektSatz nur auswerten, wenn _DEBUG, oder wenn wirklich notwendig
		long lIdLink = LINKTOLINK(VIOSatz.identbkey.zviook);
		struct obl OBLSatz;

	#if !defined(_DEBUG)
			if (fVerifyType) 
	#endif // _!DEBUG
			{
			// ObjektSatz lesen, Typ feststellen
			DB_ADDR_OBL dbaOBL (DBDesc());

	//			dbaOBL.file_no = OBL;
				dbaOBL.rec_no = lIdLink;
				if ((RC = (ErrCode)z_readrec (&dbaOBL, &OBLSatz)) != EC_OKAY) {
					iRC = false;
					break;
				}
			}

	#if defined(_DEBUG)
		// Objektnummer liefern
		short iOTyp = ::GetObjectType (&OBLSatz);
			
		// ObjektTyp muß eindeutig sein, oder alle Objekttypen behandeln
			TX_ASSERT(fVerifyType || iOTyp == dwData);
			if (dwData & iOTyp)	{	// nur wenn dieser Objekttyp gefordert ist
				try {
					iRC = EnumIdentObjectsCallbackEx (pFcn, lIdLink, iOTyp, pData);
				} catch (bool fResult) {
				// abbrechen der Enumeration
					iRC = fResult;
					break;		// beí neuen GeoDB's hier aufhören
				}
			}
	#else
		// Objektnummer liefern
			if (fVerifyType) {
			short iOTyp = ::GetObjectType (&OBLSatz);

				if (dwData & iOTyp)	{	// nur wenn dieser Objekttyp gefordert ist
					try {
						iRC = EnumIdentObjectsCallbackEx (pFcn, lIdLink, iOTyp, pData);
					} catch (bool fResult) {
					// abbrechen der Enumeration
						iRC = fResult;
						break;		// beí neuen GeoDB's hier aufhören
					}
				} 
			} else {
				try {
					iRC = EnumIdentObjectsCallbackEx (pFcn, lIdLink, dwData, pData);
				} catch (bool fResult) {
				// abbrechen der Enumeration
					iRC = fResult;
					break;		// beí neuen GeoDB's hier aufhören
				}
			}
	#endif // _DEBUG

			ActDB.ReActivate();	// für alle Fälle wieder aktivieren
			dba.rec_no = VIOSatz.zvionk;
		}
		return iRC;
	}

// hier wieder alles beim Alten
struct vio VIOSatz;

	dba.file_no = VIO_OLD;
	while (iRC && dba.rec_no != 0) {
	// lfd. VIOSatz lesen
		if ((RC = (ErrCode)z_readrec (&dba, &VIOSatz)) != EC_OKAY) 
		{
			iRC = false;
			break;
		}

	struct obl OBLSatz;

	// ObjektSatz nur auswerten, wenn _DEBUG, oder wenn wirklich notwendig
#if !defined(_DEBUG)
		if (fVerifyType) 
#endif // _!DEBUG
		{
		// ObjektSatz lesen, Typ feststellen
		DB_ADDR_OBL dbaOBL (DBDesc());

//			dbaOBL.file_no = OBL;
			dbaOBL.rec_no = VIOSatz.zvioo;
			if ((RC = (ErrCode)z_readrec (&dbaOBL, &OBLSatz)) != EC_OKAY) {
				iRC = false;
				break;
			}
		}

#if defined(_DEBUG)
	// Objektnummer liefern
	short iOTyp = ::GetObjectType (&OBLSatz);
		
	// ObjektTyp muß eindeutig sein, oder alle Objekttypen behandeln
		TX_ASSERT(fVerifyType || iOTyp == dwData);
		if (dwData & iOTyp)	{	// nur wenn dieser Objekttyp gefordert ist
			try {
				iRC = EnumIdentObjectsCallbackEx (pFcn, VIOSatz.zvioo, iOTyp, pData);
			} catch (bool fResult) {
			// abbrechen der Enumeration
				iRC = fResult;
				if (VERSION0500000E <= GetDBVersion())
					break;		// beí neuen GeoDB's hier aufhören
			}
		}
#else
	// Objektnummer liefern
		if (fVerifyType) {
		short iOTyp = ::GetObjectType (&OBLSatz);

			if (dwData & iOTyp)	{	// nur wenn dieser Objekttyp gefordert ist
				try {
					iRC = EnumIdentObjectsCallbackEx (pFcn, VIOSatz.zvioo, iOTyp, pData);
				} catch (bool fResult) {
				// abbrechen der Enumeration
					iRC = fResult;
					if (VERSION0500000E <= GetDBVersion())
						break;		// beí neuen GeoDB's hier aufhören
				}
			} 
		} else {
			try {
				iRC = EnumIdentObjectsCallbackEx (pFcn, VIOSatz.zvioo, dwData, pData);
			} catch (bool fResult) {
			// abbrechen der Enumeration
				iRC = fResult;
				if (VERSION0500000E <= GetDBVersion())
					break;		// beí neuen GeoDB's hier aufhören
			}
		}
#endif // _DEBUG

		ActDB.ReActivate();	// für alle Fälle wieder aktivieren
		dba.rec_no = VIOSatz.znvio;
	}
	return iRC;
}

// Enumerieren aller Objekte eines Idents mit ObjekttypAuswahl ----------------
BOOL GeoDB::EnumIdentObjectsEx (
	long Ident, BOOL (*pFcn)(long, DWORD, void *), void *pData, DWORD dwData)
{
DB_ADDR dba (DBDesc());
struct idl IdSatz;
ErrCode RC;

// DatenBasis aktivieren
CActDB ActDB (*this);

// erstes Objekt suchen
	{
	// Fehler WC_NOTFOUND ignorieren
	ErrInstall EI (WC_NOTFOUND);

	// ID finden
		dba.file_no = IDL;
		RC = (ErrCode)z_keyfind (&dba, IDN, &Ident);
		if (RC != EC_OKAY) {
		// Fehler aufgetreten

			if (RC == WC_NOTFOUND) return true;
			return false;
		}
	}

// über Verbindungsliste VIO alle Objekte holen
	if ((RC = (ErrCode)z_readrec (&dba, &IdSatz)) != EC_OKAY) return false;

	if (VERSION0500000E <= GetDBVersion()) {
	// EinzelListen durchgehen
		if ((dwData & TPPunkt) && !EnumObjectsIdlEx (Ident, IdSatz.zpvio, false, pFcn, pData, TPPunkt)) 
			return false;
		if ((dwData & TPLinie) && !EnumObjectsIdlEx (Ident, IdSatz.zlvio, false, pFcn, pData, TPLinie)) 
			return false;
		if ((dwData & TPFlaeche) && !EnumObjectsIdlEx (Ident, IdSatz.zfvio, false, pFcn, pData, TPFlaeche)) 
			return false;
		if ((dwData & TPText) && !EnumObjectsIdlEx (Ident, IdSatz.ztvio, false, pFcn, pData, TPText)) 
			return false;
		if ((dwData & TPKO) && !EnumObjectsIdlEx (Ident, IdSatz.zkvio, false, pFcn, pData, TPKO)) 
			return false;
	} else {
	// Hauptliste durchgehen
		if (!EnumObjectsIdlEx (Ident, IdSatz.zvio, true, pFcn, pData, dwData)) 
			return false;
	}

	return true;
}

short GetObjectType (struct obl *pOBLSatz)
{
	if (pOBLSatz == NULL) return TPUnknown;

	if (pOBLSatz -> status & (SB_TEXTOBJ|SB_TEXTOBJIND)) return TPText;
	if (pOBLSatz -> status & SB_SACHOBJ) return TPSO;
	if (pOBLSatz -> rmaske & OREL) return TPKO;

	if (pOBLSatz -> zokp) return TPPunkt;
	if (pOBLSatz -> zovol) return TPLinie;
	if (pOBLSatz -> zovoma) return TPFlaeche;

	return TPUnknown;
}


// Einlesen des Textes eines TextObjektes -------------------------------------
ErrCode GeoDB :: ReadText (long ONr, char * &pText, TextObjTyp &TOTyp) 
{
ErrCode RC;	// FehlerCode
CActDB ActDB (*this);

// Einlesen des ObjektSatzes
DB_ADDR_OBL dbaOBL (DBDesc());
struct obl OBLSatz;

//	dbaOBL.file_no = OBL;
	dbaOBL.rec_no = ONr;
	__Read (dbaOBL, OBLSatz);

	if (OBLSatz.status & SB_TEXTOBJ) {
	// gegebenes Objekt ist wirklich TextObjekt
	long TextLen;
	bool iMCodeFlag = false;	// Text am Bezugsobjekt
	bool fObjProp = false;		// Text enthält Namen deiner Objekteigenschaft des Bezugsobjektes
	long lFirstP = OBLSatz.zovom;

		TOTyp = TOT_TEXT;	// für alle Fälle
		if (GetDBVersion() >= VERSION05000008) {
		// neue TextObjekte
		ErrInstall ENF (WC_NOTFOUND);

			if (GetVOMMI (DBDesc(), &lFirstP, _lTextObjMCode) != EC_OKAY) {
			// irgend ein sinnloser Fehler
				pText = NULL;
				return EC_OKAY;
			}
		}

		DBASSERT (GetTextLen (DBDesc(), lFirstP, &TextLen));
		if (TextLen == 0) {
		// noch kein Text eingegeben
			pText = NULL;
			return EC_OKAY;
		} else if (TextLen == -1L) {
		// Text ist am BezugsObjekt
			TextLen = sizeof(long);		// MerkmalsCode
			iMCodeFlag = true;
		} else if (TextLen < 0) {
			TextLen = -TextLen; 	// Name einer Objekteigenschaft
			fObjProp = true;
		}

		pText = new char [TextLen+1];
		if (pText == NULL)
			return (ErrCode)db_error (EC_NOMEMORY, RC_ReadText);

		TX_ASSERT(!iMCodeFlag || !fObjProp);	// nur eins von beiden darf gesetzt sein
		DBASSERT (GetText (DBDesc(), lFirstP, pText, TextLen, iMCodeFlag));
		pText[TextLen] = '\0';

		if (iMCodeFlag) {
		// Text ist aus BezugsObjekt holen

			TOTyp = TOT_TEXTIND;
			return EC_OKAY;
		}

#if defined(MSWIND)
		OemToAnsi (pText, pText);
#endif
		if (fObjProp) {
		// Text ist Name einer Objekteigenschaft des Bbezugsobjektes
			TOTyp = TOT_TEXTINDOBJPROP;
			return EC_OKAY;
		}
		return EC_OKAY;
	}

return (ErrCode)db_error (WC_NOTEXTOBJ, RC_ReadText);
}


// Wegschreiben des Textes eines TextObjektes ---------------------------------
ErrCode GeoDB::WriteText (long ONr, char *pText, BOOL fIndObjProp) 
{
ErrCode RC;		// FehlerCode
CActDB ActDB (*this);	// aktivieren der GeoDB

// Einlesen des ObjektSatzes
DB_ADDR_OBL dbaOBL (DBDesc());
struct obl OBLSatz;

//	dbaOBL.file_no = OBL;
	dbaOBL.rec_no = ONr;
	__Read (dbaOBL, OBLSatz);

	if (OBLSatz.status & SB_TEXTOBJ) {
	// gegebenes Objekt ist wirklich TextObjekt
	StringDup pTmp (pText);

#if defined(MSWIND)
		AnsiToOem (pTmp, pTmp);
#endif

		if (fIndObjProp && !(OBLSatz.status & SB_TEXTOBJIND)) {
		// wenns das TO erst ein indirektes werden soll
			OBLSatz.status |= SB_TEXTOBJIND;
			__Write (dbaOBL, OBLSatz);

		} else if (!fIndObjProp && (OBLSatz.status & SB_TEXTOBJIND)) {
		// TO soll kein indirektes mehr sein
			OBLSatz.status &= ~SB_TEXTOBJIND;
			__Write (dbaOBL, OBLSatz);
		}

	// normales Textobjekt
		SetDirty();

		if (GetDBVersion() >= VERSION05000008) {
		// neues TextObjekt
			DBASSERT (delmi (DBDesc(), _lTextObjMCode, ONr, dbaOBL.file_no));
			DBASSERT (PutMiText (DBDesc(), _lTextObjMCode, ONr, dbaOBL.file_no, pTmp, TRUE)); 

		// Merkmals-Integrität testen
			TX_ASSERT(EC_OKAY == TestObjektMerkmal (*this, ONr, _lTextObjMCode, g_iKonsFlags));
		
		} else {
		long lLen = (strlen (pTmp)+3)/4;

			if (OBLSatz.status & SB_TEXTOBJIND) 
				lLen = -lLen;

			if (OBLSatz.zovom != 0) 
				DBASSERT (::DelText (DBDesc(), OBLSatz.zovom));

			DBASSERT (PutText (DBDesc(), pTmp, lLen, &OBLSatz.zovom));
			__Write (dbaOBL, OBLSatz);
		}
		return EC_OKAY;
	}
	return (ErrCode)db_error (WC_NOTEXTOBJ, RC_WriteText);
}

#if 0
// Löschen eines MerkmalsTextes aus der DBT - Datei ---------------------------
ErrCode GeoDB :: DelText (long First) 
{
DB_ADDR dbaDBT (DBDesc());
struct dbt DBTSatz;
ErrCode RC;

	SetDirty();

	dbaDBT.file_no = DBT;
	dbaDBT.rec_no = First;
	do {
	// TextSatz einlesen
		Read (dbaDBT, DBTSatz);
	// Freigeben dieses Satzes
		Dispose (dbaDBT);
		dbaDBT.rec_no = DBTSatz.zndbt;
	} while (dbaDBT.rec_no != 0);           // alle Sätze freigeben

return EC_OKAY;
}
#endif

ErrCode GeoDB :: ModGIPunkt (long ONr, Punkt &Pt) 
{
DB_ADDR_OBL dbaOBL (DBDesc());
DB_ADDR dbaPOL (DBDesc());
struct obl OBLSatz;
struct pol POLSatz;
ErrCode RC;

// ObjektSatz lesen
//	dbaOBL.file_no = OBL;
	dbaOBL.rec_no = ONr;
	__Read (dbaOBL, OBLSatz);

// alten Satz einlesen
	dbaPOL.file_no = POL;
	dbaPOL.rec_no = OBLSatz.zokp;
	__Read (dbaPOL, POLSatz);

// Geometrie korrigieren und wegschreiben
	SetDirty();

	POLSatz.kpkrd.px = Pt.X();
	POLSatz.kpkrd.py = Pt.Y();
	__Write (dbaPOL, POLSatz);

return EC_OKAY;
}


// Enumeration aller Identifikatoren einer GeoDB ------------------------------
extern "C" {

inline BOOL EnumIdentsCallback (BOOL (*pFcn)(long, BOOL, void *), 
			        long Id, BOOL iNext, void *pData) 
{
	return ((ENUMNOKEYLONGCALLBACK)pFcn)(Id, iNext, pData);
}

}


BOOL GeoDB :: EnumIdents (BOOL (*pFcn)(long, BOOL, void *), void *pData)
{
ErrCode EC;
DB_ADDR dba (DBDesc());
KEYCONTEXT KC;
ErrInstall EI (WC_NOTFOUND);	// Fehler WC_NOTFOUND ignorieren

// DatenBasis aktivieren
CActDB ActDB (*this);

// ersten ID suchen
	EC = (ErrCode)z_keyfirst (&dba, IDN);
	if (EC != EC_OKAY) {
	// Fehler aufgetreten
		if (EC == WC_NOTFOUND) 
			EC = EC_OKAY;         // nichts gefunden: OK
		return EC == EC_OKAY;         // sonstiger Fehler
	}

// für alle weiteren ID's
bool iNext = true;
bool iRC = true;

	while (iNext && iRC) {
	long Id;

	// ID aus Schlüsseldatei lesen
		EC = (ErrCode)z_keyread (DBDesc(), &Id);
		if (EC != EC_OKAY) break;

	// nächsten Schlüssel suchen
		EC = (ErrCode)z_keynext (&dba, IDN);
		if (EC != EC_OKAY)
			iNext = false;

		GetKeyContext (&KC);
		iRC = EnumIdentsCallback (pFcn, Id, iNext, pData);
		SetKeyContext (&KC);
		ActDB.ReActivate();
	}
	if (EC == WC_NOTFOUND) 
		EC = EC_OKAY;           // nichts mehr gefunden: OK

return iRC ? EC == EC_OKAY : iRC;
}


extern "C" {

inline BOOL EnumIdentsCallbackEx (BOOL (*pFcn)(long, DWORD, void *), 
			        long Id, DWORD eData, void *pData) 
{
	return ((ENUMNOKEYLONGEXCALLBACK)pFcn)(Id, eData, pData);
}

}

BOOL GeoDB :: EnumIdentsEx (BOOL (*pFcn)(long, DWORD, void *), void *pData, DWORD dwData)
{
ErrCode RC;
DB_ADDR dba (DBDesc());
KEYCONTEXT KC;
ErrInstall EI (WC_NOTFOUND);	// Fehler WC_NOTFOUND ignorieren

// DatenBasis aktivieren
CActDB ActDB (*this);

// ersten ID suchen
	RC = (ErrCode)z_keyfirst (&dba, IDN);
	if (RC != EC_OKAY) {
	// Fehler aufgetreten
		if (RC == WC_NOTFOUND) 
			RC = EC_OKAY;         // nichts gefunden: OK
		return RC == EC_OKAY;         // sonstiger Fehler
	}

// für alle weiteren ID's
bool iNext = true;
bool iRC = true;

	while (iNext && iRC) {
	long lIdent;
	short iOTypes = 0;

	// ID aus Schlüsseldatei lesen
		RC = (ErrCode)z_keyread (DBDesc(), &lIdent);
		if (RC != EC_OKAY) break;

	// nächsten Schlüssel suchen
		RC = (ErrCode)z_keynext (&dba, IDN);
		if (RC != EC_OKAY)
			iNext = false;

		GetKeyContext (&KC);

	// ObjektTypen dieses Idents feststellen
		RC = FindId (lIdent, NULL, &iOTypes);
		if (RC != EC_OKAY) break;

	// Callback aufrufen
		iRC = EnumIdentsCallbackEx (pFcn, lIdent, DWORD(iOTypes), pData);

		SetKeyContext (&KC);
		ActDB.ReActivate();
	}
	if (RC == WC_NOTFOUND) 
		RC = EC_OKAY;           // nichts mehr gefunden: OK

	return iRC ? RC == EC_OKAY : iRC;
}


// Wegspeichern eines GeoObjektes in der DB -----------------------------------
ErrCode GeoDB :: PutGI (GeoObjekt *pGO)
{
long *x = NULL, *y = NULL;
long *pK = NULL;
long lCnt = 0;

	if (!(lCnt = pGO -> RetrievePureGeometrie (&x, &y, &pK))) {
	// Speicher wieder freigeben
		DELETE (x);
		DELETE (y);
		DELETE (pK);
		return EC_NOMEMORY;
	}

CActDB ActDB (*this);
ErrCode RC = EC_OKAY;

	SetDirty();

	switch (pGO -> isA()) {
	case OT_PUNKT:
		RC = (ErrCode)PutPunktObject (DBDesc(), &pGO -> ObjNr(), pGO -> Id(), x[0], y[0]);
		break;

	case OT_KANTE:
		RC = (ErrCode)PutLineObject (DBDesc(), &pGO -> ObjNr(), pGO -> Id(), 
					     x, y, lCnt);
		break;

	case OT_FLAECHE:
		RC = (ErrCode)PutAreaObject (DBDesc(), &pGO -> ObjNr(), pGO -> Id(), 
					     x, y, pK, lCnt, 
					     ((GeoFlaeche *)pGO) -> KantenAnz());
		break;

	case OT_LABEL:
	case OT_TEXT:
		RC = (ErrCode)PutTextObject (DBDesc(), &pGO -> ObjNr(), pGO -> Id(), 
					     TOMCode(), x[0], y[0], ((BasicGeoText *)pGO) -> TextBase(),
						 (OT_LABEL == pGO -> isA()) ? TRUE : FALSE); 
		break;

	default:
		break;
	}

// Speicher wieder freigeben
	DELETE (x);
	DELETE (y);
	DELETE (pK);

return RC;
}

// Geometriebehandlung in einer GeoDB -----------------------------------------
ErrCode GeoDB :: DelGI (long lONr)
{
	if (lONr == -1L) 
		return (ErrCode)db_error (EC_NOON, RC_DelGI);

CActDB ActDB (*this);

	SetDirty();
	return (ErrCode)delgi (DBDesc(), lONr);
}

ErrCode GeoDB :: OverlayGI (long lTargetONr, GeoObjekt *pGO)
{
CActDB ActDb (*this);
ErrCode RC;

	SetDirty();

	switch (pGO -> isA()) {
	case OT_PUNKT:
		RC = (ErrCode)OvlPunktObject (DBDesc(), &pGO -> ObjNr(), pGO -> Id(), lTargetONr);
		break;

	case OT_KANTE:
		RC = (ErrCode)OvlLineObject (DBDesc(), &pGO -> ObjNr(), pGO -> Id(), lTargetONr);
		break;

	case OT_FLAECHE:
		RC = (ErrCode)OvlAreaObject (DBDesc(), &pGO -> ObjNr(), pGO -> Id(), lTargetONr);
		break;

	default:
		break;
	}

return RC;
}

// Geometrie in Feldern bereitstellen -----------------------------------------
long GeoObjekt :: RetrievePureGeometrie (long **pX, long **pY, long **pKCnt)
{
ObjTyp iTyp = isA();

	if (pX == NULL || pY == NULL) return 0L;

	switch (iTyp) {
	case OT_PUNKT:
	case OT_LABEL:
	case OT_TEXT:
		{
			*pX = new long [1];
			*pY = new long [1];
			if (*pX == NULL || *pY == NULL) {
				DELETE (*pX);
				db_error (EC_NOMEMORY, RC_QueryObjGeometrie);
				break;
			}

		// Geometrie holen
			if (iTyp == OT_PUNKT) {
				(*pX)[0] = ((GeoPunkt *)this) -> X();
				(*pY)[0] = ((GeoPunkt *)this) -> Y();
			} else {
				(*pX)[0] = ((BasicGeoText *)this) -> X();
				(*pY)[0] = ((BasicGeoText *)this) -> Y();
			}

			return 1L;
		}
		break;

	case OT_KANTE:
		{
		GeoKante *pKO = (GeoKante *)this;
		long lCnt = pKO -> ASP();

			*pX = new long [lCnt];
			*pY = new long [lCnt];
			if (*pX == NULL || *pY == NULL) {
				DELETE (*pX);
				db_error (EC_NOMEMORY, RC_QueryObjGeometrie);
				break;
			}

		// Geometrie holen
			pKO -> GetKante (*pX, *pY, lCnt);
			return lCnt;
		}
		break;

	case OT_FLAECHE:
		{
		GeoFlaeche *pFO = (GeoFlaeche *)this;
		long j = 0;
		long iKCnt = pFO -> KantenAnz();

			if (pKCnt) {
				*pKCnt = new long [iKCnt];
				if (*pKCnt == NULL) {
					db_error (EC_NOMEMORY, RC_QueryObjGeometrie);
					break;
				}
			}
			for (long i = 0; i < iKCnt; i++) {
				j += pFO -> KA((short)i).ASP();
				if (pKCnt) (*pKCnt)[i] = pFO -> KA((short)i).ASP();	
			}

		// Felder anlegen
		long lCnt = j;

			*pX = new long [lCnt];
			*pY = new long [lCnt];
			if (*pX == NULL || *pY == NULL) {
				if (pKCnt) DELETE (*pKCnt);
				DELETE (*pX);
				db_error (EC_NOMEMORY, RC_QueryObjGeometrie);
				break;
			}

		// Geometrie lesen
			for (i = 0, j = 0; i < iKCnt; i++) {
			long actSize = lCnt - j;
				
				pFO -> KA((short)i).GetKante (&(*pX)[j], &(*pY)[j], actSize);
				j += actSize;
			}
			return lCnt;
		}
		break;
	}

return 0L;
}

// Neues 'leeres' Objekt anlegen ----------------------------------------------
long GeoDB :: CreateObjTemplate (long lIdent, short)
{
long lONr = -1L;
CActDB ActDB (*this);
ErrCode RC = EC_OKAY;

	SetDirty();

	RC = (ErrCode)PutObjTemplate (DBDesc(), &lONr, lIdent);

return RC == EC_OKAY ? lONr : -1L;		// liefert neue ObjektNummer
}

// Aufzählen aller vorhandenen HeaderEinträge ---------------------------------
extern "C" {

inline BOOL EnumHeaderCallback (BOOL (*pFcn)(char *, BOOL, void *), 
			        char *pT, BOOL iNext, void *pData) 
{
	return ((ENUMNOKEYCALLBACK)pFcn)(pT, iNext, pData);
}

}


BOOL EXPORT02 GeoDB::EnumHdrData (BOOL (*pFcn)(char *, BOOL, void *), void *pData) 
{
ErrCode RC;
DB_ADDR dba(DBDesc());
KEYCONTEXT KC;
ErrInstall EI (WC_NOTFOUND);

	dba.file_no = HEAD;
	RC = (ErrCode)z_keyfirst (&dba, HDIDN);
	if (RC != EC_OKAY) {
	// Fehler aufgetreten
		if (RC == WC_NOTFOUND) 
			RC = EC_OKAY; // nichts gefunden: OK
		return RC == EC_OKAY;		// sonstiger Fehler
	}

bool iNext = true;
char pHdidn[16];		// HeaderSchlüssel

	while (iNext) {
		RC = (ErrCode)z_keyread (DBDesc(), pHdidn);
		if (RC != EC_OKAY) break;

	// nächsten Schlüssel suchen
		iNext = ((RC = (ErrCode)z_keynext (&dba, HDIDN)) == EC_OKAY);
		GetKeyContext (&KC);

	// Enumeration
		if (EnumHeaderCallback (pFcn, pHdidn, iNext, pData) == false) 
			return false;

		SetKeyContext (&KC);
	}

return RC == EC_OKAY;
}


// Überprüfen, ob GeoObjektContainer innerhalb des DBContainers liegt ---------
BOOL EXPORT02 GeoDB :: VerifyGI (GeoObjekt *pGO)
{
	if (pGO -> isA() == OT_TEXT || pGO -> isA() == OT_LABEL) 
		return TRUE;	// Texte nicht testen

ObjContainer OC;

	if (!GetObjContainer (pGO, OC)) return false;

ObjContainer DBC = DBCont();

	return DBC >= OC;	// DBCont überdeckt völlig GeoObjCont
}

///////////////////////////////////////////////////////////////////////////////
// Liefert Objettyp direkt aus der GeoDB
ErrCode EXPORT02 GeoDB::GetObjectType (LONG lONr, int *piOTyp)
{
	TX_ASSERT(NULL != piOTyp);

CActDB ActDB (*this);
DB_ADDR_OBL dbaOBL(DBDesc());
struct obl OBLSatz;
ErrCode RC;

//	dbaOBL.file_no = OBL;
	dbaOBL.rec_no = lONr;
	__Read(dbaOBL, OBLSatz);
	
	*piOTyp = ::GetObjectType (&OBLSatz);
	return EC_OKAY;
}


