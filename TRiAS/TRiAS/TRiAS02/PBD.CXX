// PBD-Datensaetze -- Klassen- & Memberfunktionen
// File: PBD.CXX

#include "trias02p.hxx"

#include <ctype.h>
#include <switchkc.h>
#include <pbd.hxx>
#include <merkmal.hxx>

#include "pbdids.hxx"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define MAXTEXTMERKMALLEN       80

// Konstruktoren für PBD-Datenklasse-------------------------------------------
PBD_Data :: PBD_Data (PBD_DB *pDB, PBDTyp Typ) 
{
// Daten auf Defaultwerte initialisieren
	m_lCode = -1;
	memset (m_cbKurzText, '\0', TEXTLEN+1);
	m_pLangText = NULL;
	m_dbaSatz = -1;
	m_rgTyp = Typ;
	m_rgStatus = PBD_Invalid;
	m_pDB = pDB;
	m_fTemp = false;
}

PBD_Data :: PBD_Data (PBD_DB *pDB, PBDTyp rgTyp, long lCode, char *lpkText, BOOL iAdding) 
{
// Code setzen und Kurztext dazu lesen
ErrCode EC;

// Memberdaten initialisieren
	m_lCode = lCode;                   // vollständigen Code merken
	memset (m_cbKurzText, '\0', TEXTLEN+1);
	m_pLangText = NULL;
	m_dbaSatz = -1;
	m_rgTyp = rgTyp;
	m_rgStatus = PBD_Invalid;
	m_pDB = pDB;
	m_fTemp = false;

	if (m_pDB == NULL || m_lCode == -1 || m_lCode == 0) return;

// erstmal im entsprechenden Baum nachsehen, ob wir diesen Code bereits kennen
	if (!iAdding && lpkText == NULL && pDB -> FillFromTree (this))
		return;		// ok, haben wir

// PBD-DB aktivieren
DBTemplate *oldDB = m_pDB -> Activate();

	if (oldDB == NULL) return; 	// Fehler beim aktivieren

	if (!iAdding) {
	ErrInstall E1 (WC_NOTFOUND);

		EC = (ErrCode)mfind (PBD().DBDesc(), rgTyp, lCode, &m_dbaSatz);
	} else
		EC = EC_OKAY;
	if (EC != EC_OKAY && lpkText == NULL) {
	// Versuchen, aus TempTree zu lesen
	ErrCode Result = EC;

		if (!m_pDB -> FillFromTempTree(*this)) {
		// solange versuchen bis abgebrochen oder richtig definiert
			do {
			// PBD wieder wegschalten
				oldDB -> Activate();
				switch (m_rgTyp) {
				case PBD_IDENT:
					Result = (ErrCode)db_error (WC_NOIDENT, RC_ctPBD_Data, &lCode);
					break;

				case PBD_RELATION:
					Result = (ErrCode)db_error (WC_NORELATION, RC_ctPBD_Data, &lCode);
					break;

				case PBD_MERKMAL:
					Result = (ErrCode)db_error (WC_NOMERKMAL, RC_ctPBD_Data, &lCode);
					break;
				}

			// PBD wieder zuschalten
				oldDB = m_pDB -> Activate();

				if (Result == EC_OKAY) {
				// nochmal versuchen
				ErrInstall E1 (WC_NOTFOUND);

					EC = (ErrCode)mfind (PBD().DBDesc(), rgTyp, lCode, &m_dbaSatz);
					if (EC == EC_OKAY)
						break;
				}
			} while (Result == EC_OKAY);
		}
		if (EC != EC_OKAY) {
		// Fehler aufgetreten
			if (EC == WC_NOTFOUND)  // neuer Satz
				m_rgStatus = PBD_Unmodified;
			oldDB -> Activate();    // alte DB wieder aktivieren
			return;
		}
	} 
	if (!iAdding && (lpkText == NULL || *lpkText == '\0')) {
	// KurzText lesen
		mgetkt (PBD().DBDesc(), rgTyp, m_dbaSatz, m_cbKurzText);
#if defined(MSWIND)
		OemToAnsi (m_cbKurzText, m_cbKurzText);       // Windows Zeichensatz
#endif
		oldDB -> Activate();
		if (lpkText != NULL && *lpkText == '\0')
			m_fTemp = true;  	// nicht umklassifizieren
		m_rgStatus = PBD_Unmodified;
		
		pDB -> AddToTree (this);	// im PBDBaum merken
	} else if (lpkText != NULL) {
	// temporäres Objekt
		m_fTemp = !iAdding;
		strncpy (m_cbKurzText, lpkText, TEXTLEN);
		m_cbKurzText[TEXTLEN] = '\0';
		if (!iAdding) 
			m_pDB -> AddToTempTree (*this);
		m_rgStatus = PBD_Unmodified;
		oldDB -> Activate();
	}
}

PBD_Data :: ~PBD_Data (void) 
{
	DELETE_OBJ (m_pLangText);		// evtl. LangText freigeben
}

// Memberfunktionen -----------------------------------------------------------
char *PBD_Data :: GetLangText (void) 
{
long TextLen;
ErrCode EC;

// wenn der gesuchte Satz nicht existiert, dann gleich wieder raus
	if (m_dbaSatz == -1) return NULL;

// PDB-DB aktivieren
CActDB ActDB (*m_pDB);

// Länge des LangTextes bestimmen
	EC = (ErrCode)mgetl (PBD().DBDesc(), m_rgTyp, m_dbaSatz, &TextLen);
	if (EC != EC_OKAY) 
		return NULL;            // Fehler aufgetreten

// wenn LangText noch nicht gelesen ist, dann einlesen
	if (m_pLangText == NULL && TextLen > 0) {
	// LangText - Speicher anfordern
		m_pLangText = new char [TextLen+1];
		memset (m_pLangText, '\0', (uint)TextLen+1);
		if (m_pLangText == NULL) {
		// Kein Speicherplatz.
			db_error ((int)EC_NOMEMORY, (int)RC_GetLangText);
			return NULL;
		}

	// LangText einlesen
		EC = (ErrCode)mgettx (PBD().DBDesc(), m_rgTyp, m_dbaSatz, m_pLangText);
		if (EC != EC_OKAY) {
			DELETE_OBJ (m_pLangText);
			return NULL;
		}
#if defined(MSWIND)
		OemToAnsi (m_pLangText, m_pLangText);       // Windows Zeichensatz
#endif
	}

return m_pLangText;
}

// Konstruktoren für PBD_Merkmal ---------------------------------------------
PBD_Merkmal :: PBD_Merkmal (PBD_DB *pDB) 
	     : PBD_Data (pDB, PBD_MERKMAL) 
{
	m_fSystem = false;
	m_fReadOnly = false;
	m_iMTyp = 0;
}

PBD_Merkmal :: PBD_Merkmal (PBD_DB *pDB, long lCode, char *lpkText, BOOL iTemp)
	     : PBD_Data (pDB, PBD_MERKMAL, lCode, lpkText, iTemp) 
{
// wenn der gesuchte Satz nicht existiert, dann gleich wieder raus
	m_fSystem = false;
	m_fReadOnly = false;
	m_iMTyp = 'a';		// erstmal ObjektMerkmal annehmen

// wenn der gesuchte Satz nicht existiert, dann gleich wieder raus
	if (m_dbaSatz == -1) return;

// PBD-DB aktivieren
CActDB ActDB (*pDB);

	if (!ActDB) return; // Fehler beim aktivieren

short iMTyp = 0;

	mgetkm (PBD().DBDesc(), m_dbaSatz, &lCode, &iMTyp, NULL, NULL, NULL, NULL);
	m_iMTyp = (unsigned char)iMTyp;		// nur niederwertiges Byte

	m_fSystem = m_iMTyp & PBDMERKMAL_SYSTEMFLAG ? true : false;
	m_iMTyp &= ~PBDMERKMAL_SYSTEMFLAG;

	SetReadOnly (iMTyp & PBDMERKMAL_READONLY);

// als KleinBuchstaben übergeben
	m_iMTyp = tolower((unsigned char)m_iMTyp);
}


// liefern eines evtl. MerkmalswerteTextes für Int-Aufzählunstyp -------------
// nur für Int-Aufzählungstypen rufen !
char *PBD_Merkmal :: GetMerkmalsWert (long WCode) 
{
register char *cptr;            // temp Puffer
ErrCode EC;

	if (m_dbaSatz == -1) return NULL;    // nicht initialisiertes MObj

// MerkmalsSatz einlesen
CActDB ActDB (*m_pDB);

	if (!ActDB)	// Fehler beim aktivieren
		return NULL;

long d, von[2], bis[2], WFaktor, zNext;
short mkTyp = 0;

	EC = (ErrCode)mgetkm (PBD().DBDesc(), m_dbaSatz, &d, &mkTyp, &WFaktor, 
			      von, bis, &zNext);
// Fehlerbehandlung
	if (EC != EC_OKAY || mkTyp != PBD_IDENT || bis[1] != -1) 
		return NULL;            // kein Int-Aufzählungstyp

// MerkmalswerteSatz suchen
long WerteCode, Rec;

	do {
		Rec = zNext;
		EC = (ErrCode)mgetwm (PBD().DBDesc(), Rec, &WerteCode, &zNext);
		if (EC != EC_OKAY) break;
		if (WerteCode == WCode) {
		// Satz gefunden, Text einlesen
		long TextLen;

		// Textlänge feststellen
			mkTyp = PBD_MWERT;
			EC = (ErrCode)mgetl (PBD().DBDesc(), mkTyp, Rec, &TextLen);
			if (EC != EC_OKAY) break;
		// Speicher anfordern
			cptr = new char [TextLen +1];
			if (cptr == NULL) {
				db_error ((int)EC_NOMEMORY, (int)RC_GetMWert);
				break;
			}
		// Text selbst lesen
			EC = (ErrCode)mgettx (PBD().DBDesc(), mkTyp, Rec, cptr);
			if (EC != EC_OKAY) break;
			return cptr;            // OK, Resultat liefern
		}
	} while (zNext != 0);

return NULL;    // nichts gefunden
}

// Datenbankarbeit: DummyFunktionen -------------------------------------------
ErrCode PBD_Merkmal :: SaveInDB (long, short) { return EC_OKAY; }
ErrCode PBD_Merkmal :: DeleteInDB (long, short) { return EC_OKAY; }

// PBD_Identifikator - mit temporären Identifikatoren -------------------------
PBD_Ident :: PBD_Ident (PBD_DB *pDB) 
	   : PBD_Data (pDB, PBD_IDENT) 
{
	// nothing to do
}

PBD_Ident :: PBD_Ident (PBD_DB *pDB, long lCode, char *lpkText, BOOL iTemp) 
	   : PBD_Data (pDB, PBD_IDENT, lCode, lpkText, iTemp) 
{
	// nothing to do
}

// Destruktor
PBD_Ident :: ~PBD_Ident (void) 
{
	// nothing to do
}

// Speichern einer BeschreibungsInfo in der PBD -------------------------------
ErrCode PBD_Ident :: SaveInPBD (void) 
{
	if (m_rgStatus != PBD_Modified) return WC_RETURN;

CActDB ActDB (*m_pDB);
ErrCode RC;

	if (!ActDB)      // Fehler beim aktivieren de PBD
		return (ErrCode)db_error (EC_ACTIVATE, RC_SavePBDIdent);

	m_pDB -> SetDirty();

// wenn der gesuchte Satz nicht existiert, dann gleich wieder raus
	if (m_dbaSatz != -1) { 
		DBASSERT (DeleteInPBD ());	// alten Satz löschen
	}

// neuen Eintrag aufbauen: IdentSatz
	DBASSERT (mputki (PBD().DBDesc(), m_lCode, &m_dbaSatz));

// KurzText
	{
	string str = m_cbKurzText;

		AnsiToOem (str.c_str(), (char *)str.c_str());
		DBASSERT (mputkt (PBD().DBDesc(), m_rgTyp, m_dbaSatz, (char *)str.c_str()));
	}

// LangText
	if (m_pLangText != NULL) {
	string str = m_pLangText;

		AnsiToOem (str.c_str(), (char *)str.c_str());
		RC = (ErrCode)mputtxi (PBD().DBDesc(), m_dbaSatz, (char *)str.c_str());
	}
	m_rgStatus = PBD_Unmodified;

return RC;
}

// Speichern einer BeschreibungsInfo in der PBD -------------------------------
ErrCode PBD_Merkmal :: SaveInPBD (void) 
{
	if (m_rgStatus != PBD_Modified) return WC_RETURN;

CActDB ActDB (*m_pDB);
ErrCode RC;

	if (!ActDB)      // Fehler beim aktivieren de PBD
		return (ErrCode)db_error (EC_ACTIVATE, RC_SavePBDMerkmal);

// wenn der gesuchte Satz nicht existiert, dann gleich wieder raus
	m_pDB -> SetDirty();
	if (m_dbaSatz != -1) { 
		DBASSERT (DeleteInPBD ());	 // alten Satz löschen
	}

// neuen Eintrag aufbauen: MerkmalsSatz
long lVon[2]; 
long lBis[2]; 
short mkTyp = isA();

	if (isSystem()) mkTyp |= PBDMERKMAL_SYSTEMFLAG;
	if (isReadOnly()) mkTyp |= PBDMERKMAL_READONLY;

	lVon[0] = MAXTEXTMERKMALLEN;
	lVon[1] = lBis[0] = lBis[1] = 0L;

	DBASSERT (mputkm (PBD().DBDesc(), m_lCode, mkTyp, 1L, lVon, lBis, &m_dbaSatz));  

// KurzText
	{
	string str = m_cbKurzText;

		AnsiToOem (str.c_str(), (char *)str.c_str());
		DBASSERT (mputkt (PBD().DBDesc(), m_rgTyp, m_dbaSatz, (char *)str.c_str()));
	}

// LangText
	if (m_pLangText != NULL) {
	string str = m_pLangText;

		AnsiToOem (str.c_str(), (char *)str.c_str());
		RC = (ErrCode)mputtxm (PBD().DBDesc(), m_dbaSatz, (char *)str.c_str());
	}

	m_rgStatus = PBD_Unmodified;

return RC;
}

// Konstruktoren für PBD_Relation ---------------------------------------------
PBD_Relation :: PBD_Relation (PBD_DB *pDB) 
	      : PBD_Data (pDB, PBD_RELATION) 
{
	m_iRelTyp = 0;
}

PBD_Relation :: PBD_Relation (PBD_DB *pDB, long lCode, char *lpkText, BOOL iTemp)
	      : PBD_Data (pDB, PBD_RELATION, lCode, lpkText, iTemp) 
{
// wenn der gesuchte Satz nicht existiert, dann gleich wieder raus
	m_iRelTyp = 0;
	if (m_dbaSatz == -1) return;

// PBD-DB aktivieren
CActDB ActDB (*pDB);

	if (!ActDB) // Fehler beim aktivieren
		return;
	mgetkr (PBD().DBDesc(), m_dbaSatz, &lCode, &m_iRelTyp);    // RelTyp holen

// als KleinBuchstaben übergeben        
	m_iRelTyp = tolower ((unsigned char)m_iRelTyp);
}


// Speichern einer BeschreibungsInfo in der PBD -------------------------------
ErrCode PBD_Relation :: SaveInPBD (void) 
{
	if (m_rgStatus != PBD_Modified) return WC_RETURN;
	
CActDB ActDB (*m_pDB);
ErrCode RC;

	if (!ActDB)      // Fehler beim aktivieren de PBD
		return (ErrCode)db_error (EC_ACTIVATE, RC_SavePBDIdent);

// wenn der gesuchte Satz nicht existiert, dann gleich wieder raus
	m_pDB -> SetDirty();
	if (m_dbaSatz != -1) { 
		DBASSERT (DeleteInPBD());	// alten Satz löschen
	}

// neuen Eintrag aufbauen: RelationsSatz
	DBASSERT (mputkr (PBD().DBDesc(), m_lCode, m_iRelTyp, &m_dbaSatz));

// KurzText
	{
	string str = m_cbKurzText;

		AnsiToOem (str.c_str(), (char *)str.c_str());
		DBASSERT (mputkt (PBD().DBDesc(), m_rgTyp, m_dbaSatz, (char *)str.c_str()));
	}

// LangText
	if (m_pLangText != NULL) {
	string str = m_pLangText;

		AnsiToOem (str.c_str(), (char *)str.c_str());
		RC = (ErrCode)mputtxr (PBD().DBDesc(), m_dbaSatz, (char *)str.c_str());
	}

	m_rgStatus = PBD_Unmodified;

return RC;
}

// Löschen eine IdentEintrages aus der PBD ------------------------------------
ErrCode PBD_Ident :: DeleteInPBD (void)
{
CActDB ActDB (*m_pDB);

	if (!ActDB)      // Fehler beim aktivieren de PBD
		return (ErrCode)db_error (EC_ACTIVATE, RC_DeletePBDIdent);

// herauslöschen des alten Eintrages
ErrCode RC;
	
	m_pDB -> SetDirty();
	if (m_dbaSatz != -1) {
		DBASSERT (mdelki (PBD().DBDesc(), m_dbaSatz));
	}
	m_rgStatus = PBD_Modified;

return EC_OKAY;
}

// Löschen eines MerkmalsEintrages aus der PBD --------------------------------
ErrCode PBD_Merkmal :: DeleteInPBD (void)
{
CActDB ActDB (*m_pDB);

	if (!ActDB)      // Fehler beim aktivieren der PBD
		return (ErrCode)db_error (EC_ACTIVATE, RC_DeletePBDMerkmal);

// herauslöschen des alten Eintrages
ErrCode RC;

	m_pDB -> SetDirty();
	if (m_dbaSatz != -1) {
		DBASSERT (mdelkm (PBD().DBDesc(), m_dbaSatz));
	}
	m_rgStatus = PBD_Modified;

return EC_OKAY;
}

// Löschen eines RelationsEintrages aus der PBD -------------------------------
ErrCode PBD_Relation :: DeleteInPBD (void)
{
CActDB ActDB (*m_pDB);

	if (!ActDB)      // Fehler beim aktivieren de PBD
		return (ErrCode)db_error (EC_ACTIVATE, RC_DeletePBDMerkmal);

// herauslöschen des alten Eintrages
ErrCode RC;

	m_pDB -> SetDirty();
	if (m_dbaSatz != -1) {
		DBASSERT (mdelkr (PBD().DBDesc(), m_dbaSatz));
	}
	m_rgStatus = PBD_Modified;

return EC_OKAY;
}

ErrCode PBD_Data :: DeleteInPBD (void) { return EC_OKAY; }      // Platzhalter
ErrCode PBD_Data :: SaveInPBD (void) { return EC_OKAY; }

// KurzText und LangText austauschen ------------------------------------------
void EXPORT02 PBD_Data :: SetKurzText (char *newText) 
{
	strncpy (m_cbKurzText, newText, TEXTLEN);
	m_rgStatus = PBD_Modified;
}

char *PBD_Data :: SetLangText (char *newText)
{
char *oldText = m_pLangText;

	if (newText != NULL) {
		m_pLangText = new char [strlen(newText) +1];
		if (m_pLangText)
			strcpy (m_pLangText, newText);
	} else
		m_pLangText = NULL;
	m_rgStatus = PBD_Modified;

return oldText;
}

// PBD-VerwaltungsFunktionen für die Schnittstelle nach außen -----------------
ErrCode PBD_DB :: GetPBDData (PBDDATA *pData) 
{
PBD_Data *pPBData = NULL;

	switch ((PBDTyp)pData -> pbdTyp) {
	case PBD_IDENT:         // Identifikator
		pPBData = new PBD_Ident (this, pData -> pbdCode);
		if (pPBData) pData -> pbdTemp = pPBData  -> isTemp();
		break;

	case PBD_MERKMAL:       // Merkmal
		pPBData = new PBD_Merkmal (this, pData -> pbdCode);
		break;

	case PBD_RELATION:      // Relation
		pPBData = new PBD_Relation (this, pData -> pbdCode);
		break;

	default:
		TX_ASSERT(false);
		break;
	}

	if (pPBData) {
		if (pPBData -> Status() == PBD_Data :: PBD_Invalid ||
		    pPBData -> Addr() == -1) 
		{

			DELETE_OBJ (pPBData);
			return WC_NOTFOUND;
		}

		if (pData -> pbdKTextLen > 0 && pData -> pbdKText) {
		char *pStr = pPBData -> GetKurzText();

			if (pStr) {
			int iLen = strlen (pStr);
			
				iLen = min(iLen, pData -> pbdKTextLen-1);
				strncpy (pData -> pbdKText, pStr, iLen);
				pData -> pbdKText[iLen] = '\0';
				pData -> pbdKTextLen = iLen;
			} else {
				*pData -> pbdKText = '\0';
				pData -> pbdKTextLen = 0;
			}
		}
		if (pData -> pbdLTextLen > 0 && pData -> pbdLText) {
		char *pStr = pPBData -> GetLangText();

			if (pStr) {
			int iLen = strlen (pStr);

				iLen = min(iLen, pData -> pbdLTextLen-1);
				strncpy (pData -> pbdLText, pStr, iLen);
				pData -> pbdLText[iLen] = '\0';
				pData -> pbdLTextLen = iLen;
			} else {
				*pData -> pbdLText = '\0';
				pData -> pbdLTextLen = 0;
			}
		}

	// MerkmalsSpezifika setzen
		if ((PBDTyp)pData -> pbdTyp == PBD_MERKMAL &&
		    pData -> dwSize == sizeof(PBDMERKMAL)) 
		{
		PBD_Merkmal *pM = (PBD_Merkmal *)pPBData;
		short mkTyp = pM -> isA();

			if (pM -> isSystem()) mkTyp |= PBDMERKMAL_SYSTEMFLAG;
			if (pM -> isReadOnly()) mkTyp |= PBDMERKMAL_READONLY;

			((PBDMERKMAL *)pData) -> ipbdMTyp = mkTyp;
			((PBDMERKMAL *)pData) -> ipbdMLen = pM -> GetMLen();
		}

	// RelationsSpezifika setzen
		if ((PBDTyp)pData -> pbdTyp == PBD_RELATION && 
		    pData -> dwSize == sizeof(PBDRELATION)) 
		{
			((PBDRELATION *)pData) -> ipbdRTyp = ((PBD_Relation *)pPBData) -> FRTyp();
		}

		DELETE_OBJ (pPBData);
	}

return EC_OKAY;
}

ErrCode PBD_DB :: ModPBDData (PBDDATA *pData)
{
PBD_Data *pPBData = NULL;
CPBDData *pTree = NULL;

	if (0 == pData -> pbdCode || MAXPOSLONG == pData -> pbdCode) 
		return WC_NOTFOUND;		// eine '0' lieben wir überhaupt nicht, MAXPOSLONG ist Löschkennzeichen

	switch ((PBDTyp)pData -> pbdTyp) {
	case PBD_IDENT:         // Identifikator
		if (pData -> pbdTemp) 
			pPBData = new PBD_Ident (this, pData -> pbdCode, pData -> pbdKText);
		else 
			pPBData = new PBD_Ident (this, pData -> pbdCode);
		pTree = m_pIdents;
		break;

	case PBD_MERKMAL:       // Merkmal
		if (pData -> dwSize < sizeof(PBDMERKMAL)) {
		// kein spezifisches Merkmal 
			pPBData = new PBD_Merkmal (this, pData -> pbdCode);
		} else {
		short iMTyp = ((PBDMERKMAL *)pData) -> ipbdMTyp;
		short mkTyp = iMTyp & ~(PBDMERKMAL_SYSTEMFLAG|PBDMERKMAL_READONLY);

			switch (tolower(mkTyp)) {
			case MPIntegerFeature:
				pPBData = new IntMerkmal (this, pData -> pbdCode);
				break;

			case MPUnknownFeature:       // unknown
				mkTyp = MPObjectFeature;     
				// durchfallen
			case MPObjectFeature:
			case MPViewFeature:
			case MPIdentFeature:
				pPBData = new TextMerkmal (this, pData -> pbdCode);
				((PBD_Merkmal *)pPBData) -> SetTyp (mkTyp);
				((PBD_Merkmal *)pPBData) -> SetSystem (iMTyp & PBDMERKMAL_SYSTEMFLAG);
				((PBD_Merkmal *)pPBData) -> SetReadOnly (iMTyp & PBDMERKMAL_READONLY);
				break;

			case MPDoubleFeature:
				pPBData = new DoubleMerkmal (this, pData -> pbdCode);
				break;
			}
		}
		pTree = m_pMCodes;
		break;

	case PBD_RELATION:      // Relation
		pPBData = new PBD_Relation (this, pData -> pbdCode);
		if (pPBData != NULL && pData -> dwSize == sizeof(PBDRELATION)) 
			((PBD_Relation *)pPBData) -> SetTyp (
				tolower (((PBDRELATION *)pData) -> ipbdRTyp)
			);
		pTree = m_pRCodes;
		break;

	default:
		TX_ASSERT(false);
		break;
	}

	if (pPBData && !pData -> pbdTemp) {
		if (pPBData -> Status () == PBD_Data :: PBD_Invalid) {
			DELETE_OBJ (pPBData);
			return WC_NOTFOUND;
		}

		if (pData -> pbdKTextLen > 0 && pData -> pbdKText)
			pPBData -> SetKurzText (pData -> pbdKText);
		if (pData -> pbdLTextLen > 0 && pData -> pbdLText) {
		char *pOldText = pPBData -> SetLangText (pData -> pbdLText);

			DELETE_OBJ (pOldText);
		}

		SetAccess (Z_ALL | Z_RDWR);     // Schreibrechte erwirken
		if (EC_OKAY == pPBData -> SaveInPBD()) { 	// wegschreiben, wenn nicht temp
			if (pTree)
				pTree -> RefreshEntry (pPBData);
		}
		if (!GetCOMFlag())
			Flush();       				// erstmal alles wegschreiben
		RestoreAccess (Z_ALL);			// Zugriffrechte zurücksetzen
	}
	DELETE_OBJ (pPBData);

return EC_OKAY;
}

ErrCode PBD_DB :: DelPBDData (PBDDATA *pData)
{
PBD_Data *pPBData = NULL;
CPBDData *pTree = NULL;

	switch ((PBDTyp)pData -> pbdTyp) {
	case PBD_IDENT:         // Identifikator
		pPBData = new PBD_Ident (this, pData -> pbdCode);
		pTree = m_pIdents;
		break;

	case PBD_MERKMAL:       // Merkmal
		pPBData = new PBD_Merkmal (this, pData -> pbdCode);
		pTree = m_pMCodes;
		break;

	case PBD_RELATION:      // Relation
		pPBData = new PBD_Relation (this, pData -> pbdCode);
		pTree = m_pRCodes;
		break;

	default:
		TX_ASSERT(false);
		break;
	}

	if (pPBData) {
		if (pPBData -> Status() == PBD_Data :: PBD_Invalid ||
		    pPBData -> Addr() == -1) 
		{
			DELETE_OBJ (pPBData);
			return WC_NOTFOUND;
		}

		SetAccess (Z_ALL | Z_RDWR);	// Schreibrechte erwirken
		if (EC_OKAY == pPBData -> DeleteInPBD()) {	// löschen
			if (pTree) 
				pTree -> FDeleteItem ((ULONG &)(pPBData -> GetCode()));
		}
		if (!GetCOMFlag())
			Flush();       			// erstmal alles wegschreiben
		RestoreAccess (Z_ALL);		// Zugriffrechte zurücksetzen
	}
	DELETE_OBJ (pPBData);

return EC_OKAY;
}

// Enumeration der Sätze innerhalb der PBD ------------------------------------
// die EnumerationsFunktion muß 'PASCAL' sein
extern "C" {

inline BOOL EnumPBDDataCallback (BOOL (*pFcn)(long, BOOL, void *), 
				 long lKey, BOOL iNext, void *pData) 
{
	return ((ENUMLONGKEYCALLBACK)pFcn)(lKey, iNext, pData);
}

}

// Enumeration der Einträge einer PBD -----------------------------------------
BOOL PBD_DB :: EnumPBDData (long pbdTyp, BOOL (*pFcn)(long, BOOL, void *), 
			    void *pData) 
{
ErrCode RC;
DB_ADDR dba (DBDesc());
KEYCONTEXT KC;
ErrInstall EI (WC_NOTFOUND);
int keyIndex;
CPBDData *pPBDTree = NULL;

	switch (pbdTyp) {
	case PBD_IDENT:
	// wenn schon mal enumeriert wurde, dann nur noch Baum bearbeiten
		if (m_pIdents && m_pIdents -> fEnumerated()) 
			return m_pIdents -> FEnumAllItems (pFcn, pData);
	
	// ansonsten normale Enumeration
		if (m_pIdents == NULL)
			m_pIdents = new CPBDIdents;
		pPBDTree = m_pIdents;
		keyIndex = IDS;
		break;
		
	case PBD_MERKMAL:
	// wenn schon mal enumeriert wurde, dann nur noch Baum bearbeiten
		if (m_pMCodes && m_pMCodes -> fEnumerated()) 
			return m_pMCodes -> FEnumAllItems (pFcn, pData);
	
	// ansonsten normale Enumeration	
		if (m_pMCodes == NULL)
			m_pMCodes = new CPBDMCodes;
		pPBDTree = m_pMCodes;
		keyIndex = MKS; 
		break;
		
	case PBD_RELATION:
	// wenn schon mal enumeriert wurde, dann nur noch Baum bearbeiten
		if (m_pRCodes && m_pRCodes -> fEnumerated()) 
			return m_pRCodes -> FEnumAllItems (pFcn, pData);
	
	// ansonsten normale Enumeration	
		if (m_pRCodes == NULL)
			m_pRCodes = new CPBDRCodes;
		pPBDTree = m_pRCodes;
		keyIndex = PRIREL; 
		break;

	default:
		TX_ASSERT(false);
		break;
	}

// PBD-DB aktivieren
CActDB ActDB (*this);

	if (!ActDB) return false;

	RC = (ErrCode)z_keyfirst (&dba, keyIndex);
	if (RC != EC_OKAY) {
	// Fehler aufgetreten
		if (RC == WC_NOTFOUND) 
			RC = EC_OKAY;		// nichts gefunden: OK
		return RC == EC_OKAY;           // sonstiger Fehler
	}

bool iNext = true;

	while (iNext) {
	long lKey;

		RC = (ErrCode)z_keyread (DBDesc(), &lKey);
		if (RC != EC_OKAY) break;

	// dieses Element im Baum speichern
		if (0 != lKey && pPBDTree) 
			pPBDTree -> AddToTree (this, lKey);
		
	// nächsten Schlüssel suchen
		iNext = ((RC = (ErrCode)z_keynext (&dba, keyIndex)) == EC_OKAY);
		if (RC == WC_NOTFOUND) RC = EC_OKAY;
		if (RC != EC_OKAY)
			break;		// Fehler: abbrechen

		if (0 == lKey) continue;	// wo kommt denn die '0' her ??

		GetKeyContext (&KC);

	// DB für Nutzer wieder einstellen
		{
		CActDB UserDB (ActDB.GetOldDB());

		// Enumeration
			if (EnumPBDDataCallback (pFcn, lKey, iNext, pData) == false)
				return false;
		}	// diese DB wieder aktivieren
		SetKeyContext (&KC);
	}
	if (pPBDTree) 	// merken, daß enumeriert wurde
		pPBDTree -> fEnumerated (true);
	
return RC == EC_OKAY;
}
