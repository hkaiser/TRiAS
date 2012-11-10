// Implementation der typspezifischen TreeKlasse ------------------------------
// Generiert aus CTTREE.CTT
// File: LEGDINFO.CXX

#include "triaspre.hxx"

#include <stdio.h>		// sscanf

#include "legdinfo.hxx"	// KlassenDeklarationen
#include "legdinfo.inl"	// Inline-Funktionen

#include "legmerkm.hxx"		// lexer/parser

#include "triasres.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// Konstruktor der typspezifischen TreeKlasse ---------------------------------
CLegendInfo :: CLegendInfo (CLegEntryParser &rP, long lVMCode)
: CTree ((CTTREEGETKEYFCN)FCTTreeGetWORD, (CTTREECMPKEYFCN)FCTTreeCmpWORD),
  m_rP(rP)
{
	m_lVMCode = lVMCode;
	m_lMCode = -1L;
	m_pBuff = NULL;
	m_iLast = FIRSTLASTIDENTORDER;
	m_pView = NULL;
	m_iMkBase = DEX_GetMkBase();

	m_fActArea = true;
}

// Destruktor, zerlegt alle Elemente des Baumes -------------------------------
CLegendInfo :: ~CLegendInfo (void)
{
	EveryDelete();
	DELETE (m_pBuff);
	DELETE (m_pView);
}


// Anlegen der Baumstruktur, die Übersicht über LegendenEinträge enthält ------
CLegendInfo *CLegendInfo :: CreateInstance (
				CLegEntryParser &rP, CIdTree &rIDs, long lMCode)
{
CLegendInfo *pLI = new CLegendInfo (rP, lMCode);

	if (pLI == NULL || !pLI -> FInit (rIDs)) {
		DELETE (pLI);
		return NULL;
	}
	
return pLI;
}

// sonstige Initialisierungen des Baumes --------------------------------------
bool CLegendInfo :: FInit (CIdTree &rIDs)
{
// Bufferbereich anlegen, wenn noch keiner da ist
	if (m_pBuff == NULL) {
		m_pBuff = new char [_MAX_PATH*5];
		if (m_pBuff == NULL) return false;
	}

// MerkmalsCode in dieser Sicht lesen
	DEX_GetActiveSight (m_pBuff);
	if (MakeMCodes (m_lVMCode, m_lMCode, m_pBuff)) {
		m_pView = StrDup (m_pBuff);
		if (NULL == m_pView) return false;
	}
			
// feststellen, ob die Legende in dieser Sicht an den aktuellen Ausschnitt angepaßt
// werden soll
	RetrieveMode (m_fActArea, m_fSizesLikeScaling);

// Baum füllen
WORD iOrder = 1;		// Reihenfolge der Einträge

	EveryDelete();		// alles bestehende im Baum löschen

// Überschriften zur Legende hinzufügen
	AddTexts (iOrder);
		
// welche Idents gehören zur aktuellen Sicht
CTable tId (rIDs.IdentTree());

	for (tId.First(); tId.Valid(); tId.Next()) {
	CIdentifikatorLock l(tId);
	
		if (!l) continue;
		if (l -> toPaint (TPPunkt)) {
			if (!AddIdent (l -> Id(), VT_Punkt, iOrder))
				return false;
		}
		if (l -> toPaint (TPLinie)) {
			if (!AddIdent (l -> Id(), VT_Linie, iOrder))
				return false;
		}
		if (l -> toPaint (TPFlaeche)) {
			if (!AddIdent (l -> Id(), VT_Flaeche, iOrder))
				return false;
		}
	}
	Optimize();
	
// welche Einzelobjekte gehören zur Legende
	AddObjects (iOrder);

return true;	// unabhängig von den Objekten ist alles glatt gelaufen
}


// AusschnittsAnpassung u.a. feststellen --------------------------------------
int CLegendInfo :: RetrieveMode (bool &rfAreaMode, bool &rfScaleMode)
{
// MerkmalsCode aus Header lesen, um LegendenMode zu bestimmen
long lMCode = GetHeaderMCode (false, IDS_LEGENDAREAMODE);

	rfAreaMode = true;
	rfScaleMode = false;

	if (lMCode != -1L) {
	// SichtMerkmal einlesen
	char cbLegMode[32];

		if (ReadTextMerkmal (TT_Sicht, (long)m_pBuff, lMCode, 
				     cbLegMode, sizeof(cbLegMode)))
		{
			return sscanf (cbLegMode, "%d,%d", &rfAreaMode, &rfScaleMode);
		}
	}

return 0;
}

void CLegendInfo :: SaveMode (LPCSTR pView)
{
// MerkmalsCode aus Header lesen, um LegendenMode zu bestimmen
long lMCode = GetHeaderMCode (true, IDS_LEGENDAREAMODE, pView,
			      IDS_AREAMODEKTEXT, IDS_AREAMODELTEXT);
TCHAR cbBuffer[10];

	wsprintf (cbBuffer, "%d,%d", ShowAreaOnly() ? 1 : 0, GetScaleMode() ? 1 : 0);
	WriteTextMerkmal (TT_Sicht, (DWORD)pView, lMCode, cbBuffer);
}

// Einen IdentifikatorEintrag im Baum ablegen ---------------------------------
bool CLegendInfo :: AddIdent (long lIdent, VisType iVTyp, WORD &riOrder)
{
// Sortierreihenfolge dieses Eintrages bestimmen
bool fShow = true;	// standardmäßig einfügen
bool fSpace = false;	// standardmäßig keine Zwischenzeile
char *pText = NULL;
bool fDirty = true;

	if (m_lMCode == -1) riOrder++;	// nichts definiert in dieser Sicht
	else 
		fDirty = GetSortOrder (riOrder, fShow, fSpace, pText, iVTyp, 
				       (DWORD)lIdent, TT_Identifikator);

bool fRet = FAddItem (LEGENTRYTYPE_IDENT, riOrder, iVTyp, lIdent, pText, fShow, fSpace);

	if (fRet && fDirty) FSetDirty (riOrder);
	
	DELETE (pText);

return fRet;
}


// TargetMerkmal lesen, ob Target zur Legende gehört --------------------------
bool CLegendInfo :: GetSortOrder (WORD &riOrder, bool &rfShow, bool &rfSpace,
				  char *& pText, VisType iVTyp, DWORD lTarget, 
				  short iTType, long lMCode)
{
	if (lMCode == 0L) lMCode = m_lMCode;
	if (!ReadTextMerkmal (iTType, lTarget, lMCode, m_pBuff, _MAX_PATH*5)) {
		riOrder = ++m_iLast;	// normal hinzufügen
		rfShow = true;	
		return true;		// DirtyFlag
	}
	
// Eingelesenes Merkmal analysieren. Das Merkmal hat die Struktur: 
// wsprintf ("%d:%d:"PText",%d:%d:"LText",%d:%d:"FText",%d:%d:"TText"", 
//	     iOrderPunkt, iOrderLinie, iOrderFlaeche, iOrderText);
CLegendInfoEntry *pLEI[4];

	memset (pLEI, '\0', sizeof(CLegendInfoEntry *)*4);

// entsprechend Typ Daten einlesen
	if (m_rP.ParseString (iTType, lTarget, m_pBuff, pLEI) < 0)
		return false;
		
bool fDirty = false;

// betreffende Info's austauschen
short iIndex = -1;

	switch (iVTyp) {
	case VT_Punkt:		iIndex = 0; break;
	case VT_Linie:		iIndex = 1; break;
	case VT_Flaeche:	iIndex = 2; break;
	case VT_Text:		iIndex = 3; break;
	case VT_Default:	iIndex = 0; break;	// Zwischentexte
	default:		iIndex = -1; break;
	}
	
	if (iIndex >= 0 && pLEI[iIndex]) {
		riOrder = pLEI[iIndex] -> FGetWORD();
		rfShow = pLEI[iIndex] -> isShown();
		rfSpace = pLEI[iIndex] -> hasSpace();
		pText = pLEI[iIndex] -> GetText (false);	// no reread
	} else {
		riOrder = ++m_iLast;	// normal hinzufügen
		rfShow = true;	
		rfSpace = false;
		fDirty = true;		// DirtyFlag
	}
		
	for (iIndex = 0; iIndex < 4; iIndex++) {
		DELETE (pLEI[iIndex]);
	}

return fDirty;		// DirtyFlag
}


// Feststellen welche Objekte zur Legende gehören -----------------------------
class ADDOBJECTDATA {
public:
	CLegendInfo *m_pLI;	// Pointer auf diesen Baum
	WORD &m_riOrder;	// Reihenfolge	
	
		ADDOBJECTDATA (WORD &riOrder, CLegendInfo *pLI) 
			: m_pLI(pLI), m_riOrder(riOrder) {}
};

extern "C" BOOL EXPORTTRIAS WINAPI HandleAddObject (long lONr, BOOL, void *pData)
{
ADDOBJECTDATA *pAOD = (ADDOBJECTDATA *)pData;

	return pAOD -> m_pLI -> AddObject (lONr, pAOD -> m_riOrder);
}
	
bool CLegendInfo :: AddObjects (WORD &riOrder)
{
	if (m_lMCode == -1) return true;	// garantiert keine Objekte
	
// Objekte enumerieren, die diesen MCode besitzen
ADDOBJECTDATA AOD (riOrder, this);
ENUMRECHTEXTMERKMAL ERTM;

	ERTM.dwSize = sizeof(ENUMRECHTEXTMERKMAL);
	ERTM.pView = NULL;	// es können nur Objekte einer Sicht sein
	ERTM.lMCode = m_lMCode;
	ERTM.pMWert = NULL;	// alle Objekte 
	ERTM.iMode = SMActViewOnly;	// Objekte müssen sowieso in dieser Sicht liegen
	ERTM.eFcn = HandleAddObject;
	ERTM.pData = &AOD;

bool fRet = DEX_EnumRechTextMerkmal (ERTM);

	Optimize();	// Baum optimieren
	
return fRet;
}


// Ein Objekt zur Legende hinzufügen ------------------------------------------
bool CLegendInfo :: AddObject (long lONr, WORD &riOrder)
{
// MerkmalsCodes absichern
	if (!MakeMCodes (m_lVMCode, m_lMCode)) return false;

// Sortierreihenfolge dieses Eintrages bestimmen
bool fShow = true;			// standardmäßig einfügen
bool fSpace = false;			// standardmäßig keine ZwischenZeile
char *pText = NULL;			// anzuzeigender Text
VisType iVTyp = OTypToVTyp ((ObjTyp)DEX_GetObjectType(lONr));
bool fDirty = GetSortOrder (riOrder, fShow, fSpace, pText, iVTyp, (DWORD)lONr, TT_Objekt);
bool fRet = FAddItem (LEGENTRYTYPE_OBJECT, riOrder, iVTyp, lONr, pText, fShow, fSpace);

	if (fRet && fDirty) FSetDirty (riOrder);
	DELETE (pText);

return true;		// immer weiter machen
}


// Zwischenüberschriften hinzufügen -------------------------------------------
bool CLegendInfo :: AddTexts (WORD &riOrder)
{
	if (!IsValidMCode(m_lMCode)) return false;

// 1. MasterMerkmal einlesen
	if (!ReadTextMerkmal (TT_Sicht, (DWORD)m_pView, m_lMCode, m_pBuff, _MAX_PATH*5)) 
		return false;	// keine Überschriften

// extrahieren der MCodes aus Mastermerkmal
ULONG *pulMCodes = NULL;
int iCnt = 0;

	if ((iCnt = ExtractMCodes (m_pBuff, &pulMCodes)) == 0) {
		DELETE (pulMCodes);
		return false;	// falsches Format
	}

// 2. alle im Mastermerkmal gegebenen Merkmale abklappern
	for (int i = 0; i < iCnt; i++) 
		AddText (riOrder, pulMCodes[i]);

	DELETE (pulMCodes);
	Optimize();	// Baum optimieren

return true;
}

int CLegendInfo :: ExtractMCodes (char *pMWert, ULONG **ppulMCodes)
{
	if (pMWert == 0) return 0;

// Anzahl der Merkmale holen
int iCnt = (int)strtoul (pMWert, &pMWert, 10);

	if (iCnt == 0) return 0;
	*ppulMCodes = new ULONG [iCnt];
	if (*ppulMCodes == NULL) return 0;

// einzelne Merkmale extrahieren
	for (int i = 0; i < iCnt; i++) {
		while (*pMWert && !isdigit(*pMWert))
			pMWert++;
		if (*pMWert == '\0')
			return i;
		(*ppulMCodes)[i] = strtoul (pMWert, &pMWert, m_iMkBase);
	}

return iCnt;
}

bool CLegendInfo :: AddText (WORD &riOrder, long lMCode)
{
// Sortierreihenfolge dieses Eintrages bestimmen
bool fShow = true;			// standardmäßig einfügen
bool fSpace = false;			// standardmäßig keine ZwischenZeile
char *pText = NULL;
bool fDirty = GetSortOrder (riOrder, fShow, fSpace, pText, VT_Default, (DWORD)m_pView, TT_Sicht, lMCode);
bool fRet = FAddItem (LEGENTRYTYPE_TEXT, riOrder, VT_Default, (DWORD)m_pView, pText, fShow, fSpace);

	if (fRet && fDirty) FSetDirty (riOrder);

return true;
}

// Funktion, die ein neues Element in den Baum einhängt -----------------------
bool CLegendInfo :: FAddItem (LEGENTRYTYPE rgType, WORD iSrt, VisType rgVType, 
			      long lTarget, char *pText, bool fShow, bool fSpace)
{
CLegendInfoEntryCreator Cr (*this);

	switch (rgType) {
	case LEGENTRYTYPE_IDENT:
		{
		CLegendInfoIdent *pLE = 
			ContCreate (Cr, CLegendInfoIdent)(iSrt, fShow, fSpace, 
						      rgVType, lTarget);
			if (pLE) {
				if (pText) pLE -> SetText (pText);
				return true;
			}
		}
		break;
		
		
	case LEGENTRYTYPE_OBJECT:
		{
		CLegendInfoObject *pLE = 
			ContCreate (Cr, CLegendInfoObject)(iSrt, fShow, fSpace, 
						       rgVType, lTarget);
			if (pLE) {
				if (pText) pLE -> SetText (pText);
				return true;
			}
		}
		break;

	case LEGENTRYTYPE_TEXT:
		{
		CLegendInfoText *pLE = ContCreate (Cr, CLegendInfoText)(iSrt, fSpace);

			if (pLE) {
				if (pText) pLE -> SetText (pText);
				return true;
			}
		}
		break;

	default:
		break;
	}
	
return false;
}

// Funktion, die ein Element aus dem Baum löscht -----------------------------
bool CLegendInfo :: FDeleteItem (WORD &rKT)
{
CTable t(*this);

	if (t.Find (&rKT)) return t.Delete();

return false;
}

// Funktion, die Pointer auf ein gesuchtes Item liefert ---------------------
CLegendInfoEntry *CLegendInfo :: FFindItem (WORD &rKT)
{
CTable t(*this);

	if (t.Find (&rKT)) {
	CLegendInfoEntryLock l(t);

		if (l) return l;
	}

return NULL;	// nicht gefunden
}

void CLegendInfo :: FSetDirty (WORD &rKT)
{
CTable t(*this);

	if (t.Find (&rKT)) {
	CLegendInfoEntryLock l(t);

		if (l) l -> SetDirty();
	}
}

// Diese Funktion zerlegt ein Element des Baumes ------------------------------
void EXPORTTRIAS CLegendInfo :: UserDelete (void *pObj)
{
	((CLegendInfoEntry *)pObj) -> ~CLegendInfoEntry();
}

// Funktion, die Pointer auf den Suchschlüssel liefert ------------------------
WORD *FCTTreeGetWORD (CLegendInfoEntry *pObj)
{
	return & ((CLegendInfoEntry *)pObj) -> FGetWORD();
}

// Funktion, die zwei SuchSchlüssel miteinander vergleicht --------------------
int FCTTreeCmpWORD (WORD *pObj1, WORD *pObj2)
{
	return FCmpWORD (*pObj1, *pObj2);
}


// Enumeration aller Items in dem Baum ----------------------------------------
bool CLegendInfo :: FEnumAllItems (CLegendInfoEntryEnumFunc pFcn, void *pEData)
{
CTable t(*this);

	for (t.First(); t.Valid(); t.Next()) {
	CLegendInfoEntryLock l(t);

		if (l && pFcn (*(CLegendInfoEntry *)l, pEData) == false)
			return false;
	}

return true;
}

// Enumeration aller Objekte mit einem bestimmten SuchSchlüssel ---------------
bool CLegendInfo  :: FEnumItems (WORD &rKey, CLegendInfoEntryEnumFunc pFcn, void *pEData)
{
CTable t(*this);

	for (t.FindFirst (&rKey); t.Valid(); t.FindNext (&rKey)) {
	CLegendInfoEntryLock l(t);

		if (l && pFcn (*(CLegendInfoEntry *)l, pEData) == false)
			return false;
	}

return true;
}

bool CLegendInfo  :: FReInsert (WORD &roldKey, WORD &rnewKey)
{
CTable t(*this);

	if (t.Find (&roldKey)) 
		return t.ReInsert (&rnewKey, sizeof (rnewKey));

return false;
}

// LegendenText typrichtig besorgen -------------------------------------------
char *CLegendInfoIdent :: GetText (bool fReadDef)
{
	if (m_pText) return StrDup (m_pText);
	if (!fReadDef) return NULL;
	
// IdentKurzText besorgen
char *pText = new char [_MAX_PATH*5];

	if (GetPBDText (GetIdent(), pText, _MAX_PATH*5) == NULL)
		SetText ("");
	else	
		SetText (pText);		// diesen Text merken
	CustomizedText (false);
	DELETE (pText);
	
return StrDup (m_pText);
}


char *CLegendInfoObject :: GetText (bool fReadDef)
{
	if (m_pText) return StrDup (m_pText);
	if (!fReadDef) return NULL;
	
// IdentKurzText besorgen
char *pText = new char [_MAX_PATH*5];

	if (GetPBDText (DEX_GetObjIdent (GetONr()), pText, _MAX_PATH*5) == NULL)
		SetText ("");
	else	
		SetText (pText);		// diesen Text merken
	CustomizedText (false);
	DELETE (pText);
	
return StrDup (m_pText);
}


char *CLegendInfoText :: GetText (bool)
{
	return StrDup (m_pText);
}


// neuen Text setzen ----------------------------------------------------------
void CLegendInfoEntry :: SetText (char *pText)
{
	DELETE (m_pText);
	m_pText = StrDup (pText);
	m_fDirty = true;
	m_fCustText = true;
}

void CLegendInfoEntry :: ResetText (void)
{
	DELETE (m_pText);
	m_fCustText = false;
	m_fDirty = true;
}
	
bool CLegendInfo :: MakeMCodes (long &rlVMCode, long &rlMCode, const char *pView)
{
string strView;

	if (NULL == pView) {
	char cbView[_MAX_PATH];

		if (!DEX_GetActiveSight (cbView)) 
			return false;

		strView = cbView;
	} else
		strView = pView;

	if (rlVMCode == -1L) {
		rlVMCode = GetHeaderMCode (true, IDS_LEGENDINFOMCODE,
						 strView.c_str(), 
						 IDS_VIEWLEGINFOKURZTEXT,
						 IDS_VIEWLEGINFOLANGTEXT);
		if (rlVMCode == -1L) return false;
	}
		
	if (rlMCode == -1L) {
		rlMCode = GetObjMCodeView (true, (char *)strView.c_str(), rlVMCode);
		if (rlMCode == -1L) return false;
	}
	return true;
}

// Gesamten Inhalt des Baumes an aktueller Sicht abspeichern, sofern notwendig 
bool CLegendInfo :: SaveLegend (void)
{
// MerkmalsCodes besorgen
	if (!DEX_GetActiveSight (m_pBuff)) 
		return false;
	if (!MakeMCodes (m_lVMCode, m_lMCode, m_pBuff)) return false;

	SaveMode (m_pBuff);		// aktuelle AreaMode speichern

// Neu durchzählen, um durchgängigen Index zu haben
WORD iOrder = 1;

// MerkmalsCode aus Header lesen, um LegendenOffset zu bestimmen
long lMCode = GetHeaderMCode (false, IDS_LEGENDOFFSET);

	if (lMCode != -1L) {
	// SichtMerkmal einlesen
	char cbLegOffset[32];

		if (ReadTextMerkmal (TT_Sicht, (long)m_pBuff, lMCode, 
				     cbLegOffset, sizeof(cbLegOffset)))
		{
			iOrder = atoi (cbLegOffset);
			if (iOrder == 0) iOrder = 1;
		}
	}

CTable t(*this);
WORD iOldOrder = USHRT_MAX;

	for (t.First(); t.Valid(); t.Next()) {
	CLegendInfoEntryLock l(t);
	
		if (!l) continue;
		iOldOrder = l -> FGetWORD();
		if (iOldOrder != iOrder) {
			l -> FGetWORD() = iOrder;
			l -> SetDirty();
		}
		iOrder++;	// weiterzählen
	}
	
// Jetzt Legende wegschreiben
	for (t.First(); t.Valid(); t.Next()) {
	CLegendInfoEntryLock l(t);
	
		if (!l || !l -> isDirty()) continue;
		l -> SaveLegendEntry (m_rP, m_lMCode);
		l -> SetDirty (false);
	}
	
return true;
}

// Testen, ob ein Eintrag der erste/letzte in der Liste ist -------------------
bool CLegendInfo :: isFirstEntry (WORD iOrder)
{
CTable t(*this);

	if (!t.Find(&iOrder)) return false;
	
bool fPrev = false;

	while ((fPrev = t.Prev()) != false) {
	CLegendInfoEntryLock l(t);
	
		if (l && l -> isShown())
			break;
	}

return !fPrev;	
}

bool CLegendInfo :: isLastEntry (WORD iOrder)
{
CTable t(*this);

	if (!t.Find(&iOrder)) return false;

bool fNext = false;

	while ((fNext = t.Next()) != false) {
	CLegendInfoEntryLock l(t);
	
		if (l && l -> isShown())
			break;
	}

return !fNext;
}


// Inhalt eines LegendenEintrages am Objekt wegschreiben ----------------------
bool CLegendInfoObject :: SaveLegendEntry (CLegEntryParser &rP, long lMCode)
{
// gesamten alten Eintrag dieses Idents einlesen
char *pBuffer = new char [5*_MAX_PATH];

	if (pBuffer == NULL) return false;
	
CLegendInfoEntry *pLEI[4];	// für jeden Objekttyp eine Struktur
short iIndex = -1;

	memset (pLEI, '\0', sizeof(CLegendInfoEntry *)*4);
	if (pLEI == NULL) return false;
	if (ReadTextMerkmal (TT_Objekt, (DWORD)GetONr(), lMCode, pBuffer, _MAX_PATH*5)) {
	// Merkmal vorhanden
		if (rP.ParseString (TT_Objekt, GetONr(), pBuffer, pLEI) < 0) {
			DELETE (pBuffer);
			for (iIndex = 0; iIndex < 4; iIndex++) {
				DELETE (pLEI[iIndex]);
			}
			return false;
		}
	}

// betreffende Info's austauschen
	switch (GetVType()) {
	case VT_Punkt:	iIndex = 0; break;
	case VT_Linie:	iIndex = 1; break;
	case VT_Flaeche:iIndex = 2; break;
	case VT_Text:	iIndex = 3; break;
	default:	iIndex = -1; break;
	}
	
bool fRet = false;

	if (iIndex >= 0 && iIndex < 4) {
		DELETE (pLEI[iIndex]);
		pLEI[iIndex] = new CLegendInfoObject (FGetWORD(), isShown(), 
						      hasSpace(), GetVType(), GetONr());
		if (GetTextRef() && pLEI[iIndex] && CustomizedText()) // eigener Text
			pLEI[iIndex] -> SetText (GetTextRef());
		
	// gesamten Eintrag am Ident wegschreiben
		if (FormatString (pBuffer, pLEI))
			WriteTextMerkmal (TT_Objekt, GetONr(), lMCode, pBuffer);
			
		fRet = true;
	}
	
	DELETE (pBuffer);
	for (iIndex = 0; iIndex < 4; iIndex++) {
		DELETE (pLEI[iIndex]);
	}
		
return fRet;
}


// Inhalt eines Identifikator/ObjekttypEintrages am Ident wegschreiben --------
bool CLegendInfoIdent :: SaveLegendEntry (CLegEntryParser &rP, long lMCode)
{
// gesamten alten Eintrag dieses Idents einlesen
char *pBuffer = new char [5*_MAX_PATH];

	if (pBuffer == NULL) return false;
	
CLegendInfoEntry *pLEI[4];	// für jeden Objekttyp eine Struktur
short iIndex = -1;

	if (pLEI == NULL) return false;
	memset (pLEI, '\0', sizeof(CLegendInfoEntry *)*4);
	if (ReadTextMerkmal (TT_Identifikator, (DWORD)GetIdent(), lMCode, pBuffer, _MAX_PATH*5)) {
	// Merkmal vorhanden
		if (rP.ParseString (TT_Identifikator, GetIdent(), pBuffer, pLEI) < 0) {
			DELETE (pBuffer);
			for (iIndex = 0; iIndex < 4; iIndex++) {
				DELETE (pLEI[iIndex]);
			}
			return false;
		}
	}

// betreffende Info's austauschen
	switch (GetVType()) {
	case VT_Punkt:	iIndex = 0; break;
	case VT_Linie:	iIndex = 1; break;
	case VT_Flaeche:iIndex = 2; break;
	case VT_Text:	iIndex = 3; break;
	default:	iIndex = -1; break;
	}
	
bool fRet = false;

	if (iIndex >= 0 && iIndex < 4) {
		DELETE (pLEI[iIndex]);
		pLEI[iIndex] = new CLegendInfoIdent (FGetWORD(), isShown(), hasSpace(), 
						     GetVType(), GetIdent());
		if (GetTextRef() && pLEI[iIndex] && CustomizedText()) // eigener Text
			pLEI[iIndex] -> SetText (GetTextRef());
		
	// gesamten Eintrag am Ident wegschreiben
		if (FormatString (pBuffer, pLEI))
			WriteTextMerkmal (TT_Identifikator, GetIdent(), lMCode, pBuffer);

		fRet = true;
	}
	
	DELETE (pBuffer);
	for (iIndex = 0; iIndex < 4; iIndex++) {
		DELETE (pLEI[iIndex]);
	}
		
return false;
}


bool CLegendInfoText :: SaveLegendEntry (CLegEntryParser &rP, long lMCode)
{
return true;
}


// Formatieren einer Zeichenkette zur LegendenEintragsBeschreibung ------------
inline char *EOS (char *pT) { return &pT[strlen(pT)]; }
const char *cbTypes = "plf t";	// Index im VisTypeEnum

bool FormatString (char *pBuffer, CLegendInfoEntry *pLEI)
{
short iMode = pLEI -> isShown() + (pLEI -> hasSpace() << 1);
		
	if (pLEI -> CustomizedText() && pLEI -> GetTextRef()) {
	int iLen = strlen (pLEI -> GetTextRef());
	LPSTR pEOF = EOS(pBuffer);

		if (iLen >= (5*_MAX_PATH - (pEOF - pBuffer))) {		// Buffer ist 5*_MAX_PATH (s.LegWind.cxx: 1031)
		char cbBuffer[5*_MAX_PATH];

			strncpy (cbBuffer, pLEI -> GetTextRef(), sizeof(cbBuffer)-1);

			iLen = min(5*_MAX_PATH - (pEOF - pBuffer), 5*_MAX_PATH);
			cbBuffer[iLen-1] = '\0';

			wsprintf (pEOF, "%c=%d:%d:\"%s\";", cbTypes[short(pLEI -> GetVType())],
				  iMode, pLEI -> FGetWORD(), 
				  cbBuffer);
		} else {
			wsprintf (pEOF, "%c=%d:%d:\"%s\";", cbTypes[short(pLEI -> GetVType())],
				  iMode, pLEI -> FGetWORD(), 
				  pLEI -> GetTextRef());
		}
	} else {
	// hier dürfte der Buffer eigentlich ausreichen
		TX_ASSERT(TIsValidAddress(pBuffer, 40, true));	// 40 Zeichen dürften reichen

		wsprintf (EOS(pBuffer), "%c=%d:%d;", cbTypes[short(pLEI -> GetVType())],
			  iMode, pLEI -> FGetWORD());
	}
	return true;
}

bool FormatString (char *pBuffer, CLegendInfoEntry *pLEI[4])
{
	if (pBuffer == NULL) return false;
	
	*pBuffer = '\0';	// von vorn anfangen
	for (short i = 0; i < 4; i++) {
		if (pLEI[i] != NULL && !FormatString (pBuffer, pLEI[i]))
			return false;
	}
	
return true;
}


// Legende rücksetzen ---------------------------------------------------------
extern "C" BOOL EXPORTTRIAS WINAPI HandleIdentOnResetLegend (
				long lIdent, BOOL, void *pData)
{
// Idents selbst behandeln (Merkmal löschen)
	WriteTextMerkmal (TT_Identifikator, lIdent, *(long *)pData, NULL);

return true;	// immer weitermachen
}

// LegInfo an Objekt löschen --------------------------------------------------
extern "C" BOOL EXPORTTRIAS WINAPI HandleObjectOnResetLegend (
				long lONr, BOOL, void *pData)
{
short Status = DEX_GetObjectStatus (lONr);

	if (Status == OSNormal || Status == OSModified) 
	// Objekt existiert und ist nicht temporär: VisInfoMerkmal löschen	
		WriteTextMerkmal (TT_Objekt, lONr, *(long *)pData, NULL);
	
return true;
}


bool CLegendInfo :: ResetLegend (char *pView)
{
// an allen Idents Merkmal löschen
	if (m_lVMCode == -1L) return true;	// nichts zu löschen

long lMCode = GetObjMCodeView (false, (LPCSTR)pView, m_lVMCode);

	if (lMCode == -1L) return true;	// in dieser Sicht nichts
	
// Alle Identifikatoren dieser Sicht enumerieren
ENUMTEXTKEY ETK;

	ETK.eKey = pView;
	ETK.eFcn = (ENUMTEXTKEYPROC)HandleIdentOnResetLegend;	
	ETK.ePtr = &lMCode;
	DEX_EnumSightIdents (ETK);

// Alle Objekte mit diesem MerkmalsCode enumerieren und Merkmal löschen
ENUMRECHTEXTMERKMAL ERTM;

	ERTM.dwSize = sizeof(ENUMRECHTEXTMERKMAL);
	ERTM.pView = NULL;	// es können nur Objekte einer Sicht sein
	ERTM.lMCode = lMCode;
	ERTM.pMWert = NULL;	// alle Objekte
	ERTM.iMode = 0;
	ERTM.eFcn = HandleObjectOnResetLegend;
	ERTM.pData = &lMCode;
	DEX_EnumRechTextMerkmal (ERTM);

// an Sicht Merkmal löschen
	WriteTextMerkmal (TT_Sicht, (DWORD)pView, m_lVMCode, NULL);
	
// in PBD Merkmal löschen
PBDDATA TM;

	memset (&TM, '\0', sizeof(PBDDATA));
	TM.dwSize = sizeof(PBDDATA);
	TM.pbdTyp = 'm';
	TM.pbdCode = lMCode;
	{
	ErrInstall EI (WC_NOMERKMAL);

		DEX_DelPBDData (TM);
		DEXN_PBDMCodeChanged (lMCode);
	}

return true;
}


// Einen LegendenEintrag oben verschieben -------------------------------------
bool CLegendInfo :: MoveUp (WORD &iActSel, bool fShowAll)
{
CTable t(*this);

	if (!t.Find(&iActSel)) return false;
	
// evtl. Leerzeile merken
bool fSpace = false;		// aktueller Eintrag hat Leerzeile
bool fPrevSpace = false; 	// vorheriger Eintrag hat Leerzeile

	{
	CLegendInfoEntryLock l(t);
	
		if (l) fSpace = l -> hasSpace();
	}
	
// vorherigen Eintrag umsetzen
CTable tPrev(t);
WORD iMoonKey = USHRT_MAX;
WORD iPrevKey = USHRT_MAX;
bool fPrev = false;

// suchen des nächsten sichtbaren Eintrages
	if (fShowAll) {		// wenn alles angezeigt ist, dann alle tauschen
		fPrev = tPrev.Prev();
	} else {
		while ((fPrev = tPrev.Prev()) != false) {
		// ansonsten nächsten sichtbaren suchen
		CLegendInfoEntryLock l(tPrev);
	
			if (l && l -> isShown())
				break;
		}
	}
	
// nur wenn es nicht bereits der erste ist
	if (fPrev) {
	CLegendInfoEntryLock l(tPrev);
	
		if (l) {
			iPrevKey = l -> FGetWORD();
			fPrevSpace = l -> hasSpace();
		}
	} else
		return false;
		
// aktuellen Eintrag auf den Mond schicken
	if (iPrevKey == USHRT_MAX || !t.ReInsert (&iMoonKey, sizeof(WORD))) 
	    	return false;

	if (tPrev.ReInsert (&iActSel, sizeof(WORD))) {
	CLegendInfoEntryLock l(tPrev);
	
		if (l) {
		// Leerzeile nur unter bestimmten Bedingungen übernehmen
			if (fSpace && !fPrevSpace)
				l -> hasSpace (fSpace);	// Leerzeile übernehmen
			l -> SetDirty();
		}
	} else
		 return false;
	
// aktuellen Eintrag zurückholen
	if (t.ReInsert (&iPrevKey, sizeof(WORD))) {
	CLegendInfoEntryLock l(t);
	
		if (l) {
		// Leerzeile nur unter bestimmten Bedingungen übernehmen
			if (fSpace && !fPrevSpace)
				l -> hasSpace (fPrevSpace);	// Leerzeile übernehmen
			l -> SetDirty();
		}
	} else
		return false;
		
// alter Eintrag bleibt aktiv
	iActSel = iPrevKey;

return true;
}


// Einen LegendenEintrag unten verschieben ------------------------------------
bool CLegendInfo :: MoveDown (WORD &iActSel, bool fShowAll)
{
CTable t(*this);

	if (!t.Find(&iActSel)) return false;

// evtl. Leerzeile merken
bool fSpace = false;		// aktueller Eintrag hat Leerzeile
bool fNextSpace = false; 	// vorheriger Eintrag hat Leerzeile

	{
	CLegendInfoEntryLock l(t);
	
		if (l) fSpace = l -> hasSpace();
	}
	
// vorherigen Eintrag umsetzen
CTable tNext(t);
WORD iMoonKey = USHRT_MAX;
WORD iNextKey = USHRT_MAX;
bool fNext = false;

// suchen des nächsten sichtbaren Eintrages
	if (fShowAll) {		// wenn alles angezeigt ist, dann alle tauschen
		fNext = tNext.Next();
	} else {
		while ((fNext = tNext.Next()) != false) {
		// ansonsten nächsten sichtbaren suchen
		CLegendInfoEntryLock l(tNext);
	
			if (l && l -> isShown())
				break;
		}
	}
	
// nur wenn es nicht bereits der letzte ist
	if (fNext) {
	CLegendInfoEntryLock l(tNext);
	
		if (l) {
			iNextKey = l -> FGetWORD();
			fNextSpace = l -> hasSpace();
		}
	} else
		return false;
		
// aktuellen Eintrag auf den Mond schicken
	if (iNextKey == USHRT_MAX || !t.ReInsert (&iMoonKey, sizeof(WORD))) 
	    	return false;

	if (tNext.ReInsert (&iActSel, sizeof(WORD))) {
	CLegendInfoEntryLock l(tNext);
	
		if (l) {
		// Leerzeile nur unter bestimmten Bedingungen übernehmen
			if (!fSpace && fNextSpace)
				l -> hasSpace (fSpace);	// Leerzeile umsetzen
			l -> SetDirty();
		}
	} else
		 return false;
	
// aktuellen Eintrag zurückholen
	if (t.ReInsert (&iNextKey, sizeof(WORD))) {
	CLegendInfoEntryLock l(t);
	
		if (l) {
		// Leerzeile nur unter bestimmten Bedingungen übernehmen
			if (!fSpace && fNextSpace)
				l -> hasSpace (fNextSpace);	// Leerzeile umsetzen
			l -> SetDirty();
		}
	} else
		return false;
		
// alter Eintrag bleibt aktiv
	iActSel = iNextKey;
	
return true;
}

// Einen Eintrag aus der Legende entfernen ------------------------------------
bool CLegendInfo :: RemoveEntry (WORD iOrder)
{
	if (m_lVMCode == -1L || m_lMCode == -1L) return true;	// nichts zu löschen

CTable t(*this);
bool fToDelete = false;

	if (t.Find(&iOrder)) {
	CLegendInfoEntryLock l(t);
	
		if (!l) return false;
		switch (l -> isA()) {
		case LEGENTRYTYPE_IDENT:	// IdentEintrag löschen
			HandleIdentOnResetLegend (
				((CLegendInfoIdent *)(CLegendInfoEntry *)l) -> GetIdent(),
				false, &m_lMCode);
			fToDelete = true;
			break;

		case LEGENTRYTYPE_OBJECT:	// ObjektEintrag löschen
			HandleObjectOnResetLegend (
				((CLegendInfoObject *)(CLegendInfoEntry *)l) -> GetONr(),
				false, &m_lMCode);
			fToDelete = true;
			break;

		default:
			return false;
		}
	}
	if (fToDelete) t.Delete();	// aus Baum löschen
	
return false;
}


// Eine Leerzeile anfügen/entfernen -------------------------------------------
bool CLegendInfo :: hasSpace (WORD iOrder, bool fSpace)
{
CTable t(*this);

	if (t.Find(&iOrder)) {
	CLegendInfoEntryLock l(t);
	
		if (!l) return false;
		if (!(fSpace ^ l -> hasSpace()))
			return false;		// nichts ändern
		l -> hasSpace (fSpace);
	}
	
return true;	// Dirty setzen
}


// Einen Eintrag an eine bestimmte Stelle einfügen ----------------------------
bool CLegendInfo :: FPasteEntry (LEGENTRYTYPE rgType, VisType rgVType, long lTarget, 
				 char *pStr, WORD iOrder)
{
// alles ab dieser Position um eine Stelle weiterrücken
CTable t(*this);

	for (t.Find (&iOrder); t.Valid(); t.Next()) {
	CLegendInfoEntryLock l(t);
	
		if (!l) continue;
		l -> FGetWORD()++;
	}

// an der freigewordenen Stelle den neuen Eintrag einfügen
CLegendInfoEntry *pLEI[4];
short iType = TT_Objekt;

	memset (pLEI, '\0', sizeof(CLegendInfoEntry *)*4);
	switch (rgType) {
	case LEGENTRYTYPE_IDENT:
		iType = TT_Identifikator;
		break;
		
	case LEGENTRYTYPE_OBJECT:
		iType = TT_Objekt;
		break;
		
	case LEGENTRYTYPE_UNKNOWN:
	default:
		return false;
	}
	
	if (m_rP.ParseString (iType, lTarget, pStr, pLEI) < 0) 
		return false;
	
// betreffende Info's austauschen
short iIndex = -1;

	switch (rgVType) {
	case VT_Punkt:	iIndex = 0; break;
	case VT_Linie:	iIndex = 1; break;
	case VT_Flaeche:iIndex = 2; break;
	case VT_Text:	iIndex = 3; break;
	default:	iIndex = -1; break;
	}

	if (pLEI[iIndex] != NULL) {	
		pLEI[iIndex] -> FGetWORD() = iOrder;	// neu einordnen
		
	CLegendInfoEntryCreator Cr (*this);
	
		return Cr.InsertPtr (pLEI[iIndex]) != NULL;
	}
	
return false;
}

