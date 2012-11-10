// Implementation der Memberfunktionen für die Merkmale -----------------------
// File: MERKMAL.CXX

#include "trias02p.hxx"
	
// maximale Länge de Merkmalswerte
#define MAXINTLEN	20
#define MAXDOUBLELEN	25

#include <pbd.hxx>
#include <merkmal.hxx>
#include <attribs.hxx>

#if defined(_USE_LEGACY_CODE)

#include "merkinfo.hxx"

// Textmerkmal ---------------------------------------------------------------
// Konstruktor
TextMerkmal :: TextMerkmal (PBD_DB *pDB, long Code, char *MText)
	     : PBD_Merkmal (pDB, Code)
{
	if (MText == NULL) {
		_Text = NULL;
		return;      // kein Text gegeben
	}
	_Text = new char [strlen(MText)+1];
	if (_Text == NULL) {
		db_error ((int)EC_NOMEMORY, (int)RC_ctTextMerkmal);
		return;
	}
	strcpy (_Text, MText);
}


TextMerkmal &TextMerkmal :: operator= (TextMerkmal &TM) {

	DELETE_OBJ (_Text);		// alten Inhalt löschen
	if (TM._Text == NULL)
		return *this;           // kein Text gegeben
	_Text = new char [strlen(TM._Text)+1];
	if (_Text == NULL) {
	// Kein Speichplatz.
		db_error ((int)EC_NOMEMORY, (int)RC_opTextMerkmal);
		return *this;
	}
	strcpy (_Text, TM._Text);       // Text umkopieren

return *this;
}

// Destruktor
TextMerkmal :: ~TextMerkmal (void) {

	DELETE_OBJ (_Text);		// Pointer freigeben
}

// Kopie des MerkmalsTextes liefern
char *TextMerkmal :: GetMerkmalsText (void) {
register char *cptr;

	if (_Text == NULL) return NULL;
	cptr = new char [strlen(_Text)+1];
	if (cptr == NULL) {
		db_error ((int)EC_NOMEMORY, (int)RC_TMGetText);
		return NULL;
	}
	strcpy (cptr, _Text);

return cptr;
}

// Zeigt, ob MerkmalsText für dieses Merkmal vorhanden ist -------------------
BOOL TextMerkmal :: hasTextMerkmal (void) 
{
	return (_Text != NULL);
}


// IntegerMerkmal (IntegerWert) ----------------------------------------------
// Destruktor 
IntMerkmal :: ~IntMerkmal (void) 
{
	DELETE_OBJ (_IntText);
}

// Memberfunktionen
IntMerkmal & IntMerkmal :: operator= (IntMerkmal &IM) {

	DELETE_OBJ (_IntText);		// Text freigeben
// IntWert zuweisen
	_IntWert = IM._IntWert;
// Speicher für neuen Text anlegen
	if (IM._IntText != NULL) {
		_IntText = new char [strlen(IM._IntText) +1];
		if (_IntText == NULL) {
			db_error (EC_NOMEMORY, RC_opIntMerkmal);
			return *this;
		}
	// neuen Text kopieren
		strcpy (_IntText, IM._IntText);
	}

return *this;
}


char *IntMerkmal :: GetMerkmalsText (void) {
register char *cptr;

	if (_IntText == NULL && (cptr = GetMerkmalsWert (_IntWert)) != NULL) 
	// Int-Aufzählungstyp
		_IntText = cptr;
	if (_IntText != NULL) {
	// Kopie des Merkmalstextes anlegen
		cptr = new char [strlen(_IntText) +1];
		if (cptr == NULL) {
			db_error ((int)EC_NOMEMORY, (int)RC_TMGetText);
			return NULL;
		}
		strcpy (cptr, _IntText);
	} else {
	// normaler Int-Merkmalswert
		cptr = new char [34];
		if (cptr == NULL) {
			db_error ((int)EC_NOMEMORY, (int)RC_TMGetText);
			return NULL;
		}
		_ltoa (_IntWert, cptr, 10);
	}

return cptr;
}

// DoubleMerkmal -------------------------------------------------------------
char * EXPORT02 DoubleMerkmal :: GetMerkmalsText (void) 
{
register char *cptr;

	cptr = new char [40];
	if (cptr == NULL) {
		db_error ((int)EC_NOMEMORY, (int)RC_TMGetText);
		return NULL;
	}

return DtoA (cptr, "%10.3f", _DoubleWert);
}

// Datenbankarbeit in der GeoDB -----------------------------------------------
ErrCode TextMerkmal :: SaveInDB (long lTarget, short iTyp) 
{
// entsprechende Message abschicken 
TARGETMERKMAL TM;

	memset (&TM, '\0', sizeof(TARGETMERKMAL));
	TM.dwSize = sizeof(TARGETMERKMAL);
	TM.lTarget = lTarget;
	TM.lMCode = GetCode();
	TM.imaxLen = strlen (_Text);
	TM.pMText = _Text;
	TM.iTTyp = iTyp;

return DEX_ModTextMerkmal(TM);	
}


ErrCode TextMerkmal :: DeleteInDB (long lTarget, short iTyp) 
{
// entsprechende Message abschicken 
TARGETMERKMAL TM;

	memset (&TM, '\0', sizeof(TARGETMERKMAL));
	TM.dwSize = sizeof(TARGETMERKMAL);
	TM.lTarget = lTarget;
	TM.lMCode = GetCode();
	TM.imaxLen = 0;
	TM.pMText = NULL;
	TM.iTTyp = iTyp;

return DEX_ModTextMerkmal(TM);	
}

// Virtuelle Funktionen -------------------------------------------------------
short PBD_Merkmal :: MTyp (void) { return toupper(MPUnknownFeature); }	// Platzhalter
short TextMerkmal :: MTyp (void) { return isA(); }
short IntMerkmal :: MTyp (void) { return toupper(MPIntegerFeature); }
short DoubleMerkmal :: MTyp (void) { return toupper(MPDoubleFeature); }

// Funktionen, die die maximale MerkmalsTextLänge liefern ---------------------
short PBD_Merkmal :: GetMLen (void) 
{
CActDB ActDB (*m_pDB);
long Von[2];
ErrCode RC;

	if (!ActDB) return 0;	// Fehler beim aktivieren

// MerkmalsSatz einlesen
	if (m_dbaSatz == -1) return 0;    // nicht initialisiertes MObj

	DBASSERT (mgetkm (PBD().DBDesc(), m_dbaSatz, NULL, NULL, NULL, Von, NULL, NULL));

	switch (isA()) {
	case MPObjectFeature:	// TextMerkmal
	case MPViewFeature:
	case MPIdentFeature:
		return (short)Von[0];

	case MPIntegerFeature:	// IntegerMerkmal
		return MAXINTLEN;

	case MPDoubleFeature:	// DoubleMerkmal
		return MAXDOUBLELEN;
	}

return 0;
}

#endif // _USE_LEGACY_CODE

///////////////////////////////////////////////////////////////////////////////
// Memberfunktionen für Merkmalsliste 
MerkmalsListe :: MerkmalsListe (BOOL fSystem, BOOL fAll)
	: CTree (GetMCode, LongCmp)       // Suchbaum
{
	m_iTyp = MPObjectFeature;
	m_fSystem = fSystem ? true : false;
	m_fAllFeatures = fAll ? true : false;
}

// diverse Konstruktoren 
MerkmalsListe :: MerkmalsListe (GeoDB *pDB, PBD_DB *pPBD, long lTarget, short iTyp, BOOL fSystem, BOOL fAll)
	       : CTree (GetMCode, LongCmp)       // Suchbaum
{
CActDB ActDB (*pDB);

	if (pDB->GetDBVersion() < VERSION05000007 && iTyp == IDL)
		return;		// noch nicht implementiert

	m_fSystem = fSystem ? true : false;
	m_fAllFeatures = fAll ? true : false;

long lSatzNr = GetTarget (pDB -> DBDesc(), (void *)lTarget, iTyp);

	if (lSatzNr == -1) return;
	m_iTyp = (iTyp == OBL_OLD) ? MPObjectFeature : MPIdentFeature;	// Typ dieser MListe
	FillList (pDB, pPBD, lSatzNr, iTyp);
}


MerkmalsListe :: MerkmalsListe (GeoDB *pDB, PBD_DB *pPBD, char *pSicht, BOOL fSystem, BOOL fAll)
	       : CTree (GetMCode, LongCmp)       // Suchbaum
{
CActDB ActDB (*pDB);

	if (pDB->GetDBVersion() < VERSION05000007)
		return;		// noch nicht implementiert

	m_fSystem = fSystem ? true : false;
	m_fAllFeatures = fAll ? true : false;

long lSatzNr = GetTarget (pDB->DBDesc(), (void *)pSicht, SICHT);

	if (lSatzNr == -1) return;

	m_iTyp = MPViewFeature;		// Typ dieser MListe
	FillList (pDB, pPBD, lSatzNr, SICHT);
}


void MerkmalsListe :: FillList (GeoDB *pDB, PBD_DB *pPBD, long lTarget, short iTyp)
{
MerkInfo **ppMI = NULL;
short MICnt = 0;

// alle Merkmale dieses Objektes einlesen
	if (GetMerkInfo (pDB->DBDesc(), lTarget, iTyp, &ppMI, &MICnt) != EC_OKAY)
		return;

// Creator für zugehörige MerkmalsInfos aus der PBD
PBD_MerkmalCreator MC (*this);

	for (short i = 0; i < MICnt; i++) {
	// für alle Merkmale

		if (ppMI[i] == NULL) 	// nächstes Merkmal
			continue;

		switch (ppMI[i] -> isA()) {
		case MerkInfo :: MI_Text:
			{
			TextMerkInfo *pTMI = (TextMerkInfo *)ppMI[i];
			char *MText = pTMI -> Text();

			// Textmerkmal in MerkmalsListe einfügen
			TextMerkmal *pTM = new TextMerkmal(
						pPBD, pTMI -> MCode(), MText
					);

				if (pTM) {
//* ----------------------------------------------------------------------------
					if (!m_fSystem && pTM -> isSystem()) {
					// nicht einspeichern
						delete pTM;
					} else
// --------------------------------------------------------------------------- */
						MC.InsertPtr (pTM);
				}
				
			// Speicher wieder freigeben
				DELETE_OBJ (pTMI);
				ppMI[i] = NULL;
				DELETE_OBJ (MText);
			}
			break;

		case MerkInfo :: MI_Long:
			{
			LongMerkInfo *pLMI = (LongMerkInfo *)ppMI[i];
			long *MLong = pLMI -> LongWerte();

			// LongMerkmale in MerkmalsListe einfügen
				for (short anz = 0; anz < pLMI -> MLen(); anz++) {
				IntMerkmal *pIM = new IntMerkmal(
							pPBD, pLMI -> MCode(), MLong[anz]
						);
				// SystemMerkmale evtl. nicht speichern
					if (pIM) {
//* ----------------------------------------------------------------------------
						if (!m_fSystem && pIM -> isSystem()) {
							delete pIM;
						} else
// --------------------------------------------------------------------------- */
							MC.InsertPtr (pIM);
					}
				}
			// Speicher wieder freigeben
				DELETE_OBJ (pLMI);
				ppMI[i] = NULL;
				DELETE_OBJ (MLong);
			}
			break;

		case MerkInfo :: MI_Double:
			{
			DoubleMerkInfo *pDMI = (DoubleMerkInfo *)ppMI[i];
			double *MDouble = pDMI -> DoubleWerte();

			// LongMerkmale in MerkmalsListe einfügen
				for (short anz = 0; anz < pDMI -> MLen(); anz++) {
				DoubleMerkmal *pDM = new DoubleMerkmal (
							pPBD, pDMI -> MCode(),
							MDouble[anz]
						);
				// SystemMerkmale evtl. nicht speichern
					if (pDM) {
//* ----------------------------------------------------------------------------
						if (!m_fSystem && pDM -> isSystem()) {
							delete pDM;
						} else
// --------------------------------------------------------------------------- */
							MC.InsertPtr (pDM);
					}
				}
			// Speicher wieder freigeben
				DELETE_OBJ (pDMI);
				ppMI[i] = NULL;
				DELETE_OBJ (MDouble);
			}
			break;

		case MerkInfo :: MI_Unknown:
		default:
			DELETE_OBJ (ppMI[i]);
			break;
		}
	}
	DELETE_OBJ (ppMI);		// Feld selbst wieder freigeben
}

// Löschen eines Elementes der MerkmalsListe
void EXPORT02 MerkmalsListe :: UserDelete (void *pObj) 
{
	((PBD_Merkmal *)pObj) -> /*PBD_Merkmal ::*/ ~PBD_Merkmal ();
}

// Liefert MerkmalsText eines MerkmalsCodes -----------------------------------
char *MerkmalsListe :: GetMerkmalsText (long MCode) 
{
CTable t(*this);

	if (t.Find(&MCode)) {
	PBD_MerkmalLock l(t);

		if (l) return l -> GetMerkmalsText();
	}

return NULL;
}

// Enumeration aller Merkmale eines Objektes ----------------------------------
extern "C" {

inline BOOL EnumMerkmaleCallback (BOOL (*pFcn)(long, BOOL, void *),
				  long Key, BOOL iFlag, void *pData)
{
	return ((ENUMLONGKEYCALLBACK)pFcn)(Key, iFlag, pData);
}

inline BOOL EnumMerkmaleCallbackEx (BOOL (*pFcn)(long, DWORD, void *),
				    long lKey, DWORD dwData, void *pData)
{
	return ((ENUMLONGKEYEXCALLBACK)pFcn)(lKey, dwData, pData);
}

}

long MerkmalsListe :: EnumMerkmale (BOOL (*pFcn)(long, BOOL, void *), void *pData)
{
CTable t(*this);

	for (t.First(); t.Valid(); ) {
	long lMCode;
	BOOL iNext;

		{
		PBD_MerkmalLock l(t);

			iNext = t.Next();
			if (!l) continue;

		// ACHTUNG: Enumeriert nur Textmerkmale !
			if (l -> isA() != m_iTyp) 
				continue;
				
			lMCode = l -> GetCode();
		}
		if (EnumMerkmaleCallback (pFcn, lMCode, iNext, pData) == false)
			return false;
	}

return true;
}


long MerkmalsListe :: EnumMerkmaleEx (BOOL (*pFcn)(long, DWORD, void *), void *pData)
{
CTable t(*this);

	for (t.First(); t.Valid(); t.Next()) {
	long lMCode;
	DWORD dwData = 0L;

		{
		PBD_MerkmalLock l(t);

			if (!l) continue;

		// ACHTUNG: Enumeriert nur Textmerkmale !
			if (!m_fAllFeatures && (l -> isA() != m_iTyp)) 
				continue;
			if (!m_fSystem && l -> isSystem())
				continue;
				
			lMCode = l -> GetCode();
			
			dwData = l -> isA();
			if (l -> isSystem()) dwData |= MPSystemFeatures;
			if (l -> isReadOnly()) dwData |= MPSystemFeatures;
		}
		if (EnumMerkmaleCallbackEx (pFcn, lMCode, dwData, pData) == false)
			return false;
	}

return true;
}


