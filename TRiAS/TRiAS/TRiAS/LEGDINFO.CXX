// Implementation der typspezifischen TreeKlasse ------------------------------
// Generiert aus CTTREE.CTT
// File: LEGDINFO.CXX

#include "triaspre.hxx"

#include <stdio.h>		// sscanf

#include "legdinfo.hxx"	// KlassenDeklarationen
#include "legdinfo.inl"	// Inline-Funktionen

#include "ExtMain3.hxx"
#include "legmerkm.hxx"		// lexer/parser

#include "triasres.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// Konstruktor der typspezifischen TreeKlasse ---------------------------------
CLegendInfo::CLegendInfo (CLegEntryParser &rP, DatenBasisObjekt &rDBO, long lVMCode)
	: CTree ((CTTREEGETKEYFCN)FCTTreeGetWORD, (CTTREECMPKEYFCN)FCTTreeCmpWORD),
	  m_rP(rP), m_rDBO(rDBO)
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
CLegendInfo::~CLegendInfo (void)
{
	EveryDelete();
	DELETE (m_pBuff);
	DELETE (m_pView);
}


// Anlegen der Baumstruktur, die Übersicht über LegendenEinträge enthält ------
CLegendInfo *CLegendInfo::CreateInstance (
				CLegEntryParser &rP, DatenBasisObjekt &rDBO, long lMCode)
{
CLegendInfo *pLI = new CLegendInfo (rP, rDBO, lMCode);

	if (pLI == NULL || !pLI -> FInit (rDBO.Idents())) {
		DELETE (pLI);
		return NULL;
	}
	
return pLI;
}

// sonstige Initialisierungen des Baumes --------------------------------------
bool CLegendInfo::FInit (CIdTree &rIDs)
{
// Bufferbereich anlegen, wenn noch keiner da ist
	if (m_pBuff == NULL) {
		m_pBuff = new char [_MAX_PATH*5];
		if (m_pBuff == NULL) return false;
	}

// MerkmalsCode in dieser Sicht lesen
	DEX_GetActiveSight (m_pBuff);
	if (MakeMCodes (m_lVMCode, m_lMCode, m_pBuff)) {
		m_pView = StrDupF (m_pBuff);
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
int CLegendInfo::RetrieveMode (bool &rfAreaMode, bool &rfScaleMode)
{
NAMEDVIEWPROPERTY NVP;
char cbLegMode[32];
ResString resMode(IDS_LEGENDAREAMODE, 17);

	rfAreaMode = true;		// LegendenMode feststellen
	rfScaleMode = false;

	INITSTRUCT(NVP, NAMEDVIEWPROPERTY);
	NVP.pcView = m_pBuff;
	NVP.pcName = resMode;
	NVP.pBuffer = cbLegMode;
	NVP.iLen = sizeof(cbLegMode);

HRESULT hr = DEX_GetNamedViewProperty(NVP);

	if (SUCCEEDED(hr)) 
		return sscanf (cbLegMode, "%d,%d", &rfAreaMode, &rfScaleMode);

	return 0;
}

void CLegendInfo::SaveMode (LPCSTR pView)
{
// LegendenMode schreiben
TCHAR cbBuffer[10];

	wsprintf (cbBuffer, "%d,%d", ShowAreaOnly() ? 1 : 0, GetScaleMode() ? 1 : 0);

NAMEDVIEWPROPERTY NVP;
ResString resMode(IDS_LEGENDAREAMODE, 17);
ResString resKText (IDS_AREAMODEKTEXT, 33);
ResString resLText (IDS_AREAMODELTEXT, _MAX_PATH);

	INITSTRUCT(NVP, NAMEDVIEWPROPERTY);
	NVP.pcView = pView;
	NVP.pcName = resMode.Addr();
	NVP.pBuffer = cbBuffer;
	NVP.iLen = strlen(cbBuffer);
	NVP.pcShort = resKText;
	NVP.pcDesc = resLText;
	DEX_SetNamedViewProperty(NVP);
}

// Einen IdentifikatorEintrag im Baum ablegen ---------------------------------
bool CLegendInfo::AddIdent (long lIdent, VisType iVTyp, WORD &riOrder)
{
// Sortierreihenfolge dieses Eintrages bestimmen
bool fShow = true;	// standardmäßig einfügen
bool fSpace = false;	// standardmäßig keine Zwischenzeile
char *pText = NULL;
bool fDirty = true;

	if (m_lMCode == -1) riOrder++;	// nichts definiert in dieser Sicht
	else 
		fDirty = GetSortOrder (riOrder, fShow, fSpace, pText, iVTyp, 
				       (INT_PTR)lIdent, TT_Identifikator);

bool fRet = FAddItem (LEGENTRYTYPE_IDENT, riOrder, iVTyp, lIdent, pText, fShow, fSpace);

	if (fRet && fDirty) FSetDirty (riOrder);
	
	DELETE (pText);
	return fRet;
}


// TargetMerkmal lesen, ob Target zur Legende gehört --------------------------
bool CLegendInfo::GetSortOrder (WORD &riOrder, bool &rfShow, bool &rfSpace,
				  char *& pText, VisType iVTyp, INT_PTR lTarget, 
				  short iTType, long lMCode)
{
	if (lMCode == 0L) 
		lMCode = m_lMCode;

	if (!ReadTextMerkmal (iTType, lTarget, lMCode, m_pBuff, _MAX_PATH*5)) {
		riOrder = ++m_iLast;	// normal hinzufügen
		rfShow = true;	
		return true;			// DirtyFlag
	}
	
// Eingelesenes Merkmal analysieren. Das Merkmal hat die Struktur: 
// wsprintf ("%d:%d:"PText",%d:%d:"LText",%d:%d:"FText",%d:%d:"TText"", 
//	     iOrderPunkt, iOrderLinie, iOrderFlaeche, iOrderText);
CLegendInfoEntry *pLEI[LEGENTRYTYPE_CNT];

	memset (pLEI, '\0', sizeof(CLegendInfoEntry *) * LEGENTRYTYPE_CNT);

// entsprechend Typ Daten einlesen
	if (m_rP.ParseString (iTType, lTarget, lMCode, m_pBuff, pLEI) < 0)
		return false;
		
bool fDirty = false;

// betreffende Info's austauschen
short iIndex = -1;

	switch (iVTyp) {
	case VT_Punkt:		iIndex = 0; break;
	case VT_Linie:		iIndex = 1; break;
	case VT_Flaeche:	iIndex = 2; break;
	case VT_Text:		iIndex = 3; break;
	case VT_Default:	iIndex = 4; break;	// Zwischentexte
	default:		iIndex = -1; break;
	}
	
	if (iIndex >= 0 && NULL != pLEI[iIndex]) {
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
		
	for (iIndex = 0; iIndex < LEGENTRYTYPE_CNT; iIndex++) {
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
	
bool CLegendInfo::AddObjects (WORD &riOrder)
{
	if (m_lMCode == -1) return true;	// garantiert keine Objekte
	
// Objekte enumerieren, die diesen MCode besitzen
ADDOBJECTDATA AOD (riOrder, this);
ENUMRECHTEXTMERKMAL ERTM;

	ERTM.dwSize = sizeof(ENUMRECHTEXTMERKMAL);
	ERTM.pView = NULL;	// es können nur Objekte einer Sicht sein
	ERTM.lMCode = m_lMCode;
	ERTM.pMWert = NULL;	// alle Objekte 
	ERTM.iMode = SMActViewOnly|SMExistanceOnly;	// Objekte müssen sowieso in dieser Sicht liegen
	ERTM.eFcn = HandleAddObject;
	ERTM.pData = &AOD;

bool fRet = DEX_EnumRechTextMerkmal (ERTM);

	Optimize();	// Baum optimieren
	return fRet;
}


// Ein Objekt zur Legende hinzufügen ------------------------------------------
bool CLegendInfo::AddObject (long lONr, WORD &riOrder)
{
// MerkmalsCodes absichern
	if (!MakeMCodes (m_lVMCode, m_lMCode, NULL, lONr)) 
		return false;

// Sortierreihenfolge dieses Eintrages bestimmen
bool fShow = true;			// standardmäßig einfügen
bool fSpace = false;		// standardmäßig keine ZwischenZeile
char *pText = NULL;			// anzuzeigender Text
VisType iVTyp = OTypToVTyp ((ObjTyp)DEX_GetObjectType(lONr));
bool fDirty = GetSortOrder (riOrder, fShow, fSpace, pText, iVTyp, (INT_PTR)lONr, TT_Objekt);
bool fRet = FAddItem (LEGENTRYTYPE_OBJECT, riOrder, iVTyp, lONr, pText, fShow, fSpace);

	if (fRet && fDirty) 
		FSetDirty (riOrder);
	DELETE (pText);
	return true;		// immer weiter machen
}


///////////////////////////////////////////////////////////////////////////////
// Zwischenüberschriften hinzufügen 
bool CLegendInfo::AddTexts (WORD &riOrder)
{
	if (!IsValidMCode(m_lMCode)) 
		return false;

// 1. MasterMerkmal einlesen
char *pBuffer = NULL;
int iLen = 0;

	if (GetTextMerkmalLen(TT_Sicht, HGENERIC(m_pView), m_lMCode, iLen))
		pBuffer = new char [iLen+1];

	if (NULL == pBuffer || !ReadTextMerkmal (TT_Sicht, HGENERIC(m_pView), m_lMCode, pBuffer, iLen)) 
		return false;	// keine Überschriften

// extrahieren der MCodes aus Mastermerkmal
CMCodes MCodes;

	if (!ExtractMCodes (pBuffer, MCodes)) {
		DELETE(pBuffer);
		return false;	// falsches Format
	}
	DELETE(pBuffer);

// 2. alle im Mastermerkmal gegebenen Merkmale abklappern
	for (CMCodes::iterator it = MCodes.begin(); it != MCodes.end(); ++it) 
		AddText (riOrder, *it);

	Optimize();	// Baum optimieren
	return true;
}

/*static*/
int CLegendInfo::ExtractMCodes (char *pMWert, CMCodes &rMCodes)
{
	if (NULL == pMWert) 
		return 0;

// Anzahl der Merkmale holen
int iCnt = (int)strtoul (pMWert, &pMWert, 10);

	if (0 == iCnt) 
		return 0;

// einzelne Merkmale extrahieren
	for (int i = 0; i < iCnt; i++) {
		while (*pMWert && !isdigit(*pMWert))
			pMWert++;
		if (*pMWert == '\0')
			return i;
		rMCodes.insert(strtoul (pMWert, &pMWert, 10));
	}
	return rMCodes.size();
}

/*static*/
int CLegendInfo::WriteMCodes (CLegendInfo::CMCodes &rMCodes, char *pMWert, int iLen)
{
string strMCodes;
char cbBuffer[64];

	strMCodes = ultoa (rMCodes.size(), cbBuffer, 10);
	for (CMCodes::iterator it = rMCodes.begin(); it != rMCodes.end(); ++it) {
		strMCodes += ",";
		strMCodes += ultoa (*it, cbBuffer, 10);
	}

int iToCopy = min(iLen-1, (int)strMCodes.size());

	strncpy (pMWert, strMCodes.c_str(), iToCopy);
	pMWert[iToCopy] = '\0';
	return iToCopy;
}

bool CLegendInfo::AddText (WORD &riOrder, INT_PTR lMCode, LPCSTR pcText, bool fInsertBefore)
{
// Sortierreihenfolge dieses Eintrages bestimmen
bool fShow = true;				// standardmäßig einfügen
bool fSpace = false;			// standardmäßig keine ZwischenZeile
char *pDummyText = NULL;
bool fDirty = false;

	if (NULL == pcText)	{
	// wenn kein Einfügepunkt gegeben ist, ans Ende setzen
		fDirty = GetSortOrder (riOrder, fShow, fSpace, pDummyText, VT_Default, (INT_PTR)m_pView, TT_Sicht, lMCode);
		pcText = pDummyText;
	} 
	else {
	// jetzt alle Items neu einordnen
	CTable t(*this);

		if (t.Find(&riOrder)) {
		// alles Nachfolgende einfach runter schieben
			if (!fInsertBefore) {
				t.Next();
				riOrder++;
			}

			for (/**/; t.Valid(); t.Next()) {
			CLegendInfoEntryLock l(t);
			
				if (!l) continue;
				l -> FGetWORD()++;
				l -> SetDirty();
			}
		} else
			riOrder = USHRT_MAX;
	}
	_ASSERTE(NULL != pcText);

LEGENTRYTYPE rgType = ('\0' == pcText[0]) ? LEGENTRYTYPE_SPACELINE : LEGENTRYTYPE_TEXT;
bool fRet = FAddItem (rgType, riOrder, VT_Default, (INT_PTR)m_pView, pcText, fShow, fSpace, lMCode);

	if (fRet || fDirty) 
		FSetDirty (riOrder);
	DELETE (pDummyText);
	return true;
}

// Funktion, die ein neues Element in den Baum einhängt -----------------------
bool CLegendInfo::FAddItem (
	LEGENTRYTYPE rgType, WORD iSrt, VisType rgVType, INT_PTR lTarget, 
	LPCSTR pText, bool fShow, bool fSpace, INT_PTR lMCode)
{
CLegendInfoEntryCreator Cr (*this);

	switch (rgType) {
	case LEGENTRYTYPE_IDENT:
		{
		CLegendInfoIdent *pLE = ContCreate (Cr, CLegendInfoIdent)(iSrt, fShow, fSpace, rgVType, lTarget);

			if (pLE) {
				if (pText) pLE -> SetText (pText);
				return true;
			}
		}
		break;
		
		
	case LEGENTRYTYPE_OBJECT:
		{
		CLegendInfoObject *pLE = ContCreate (Cr, CLegendInfoObject)(iSrt, fShow, fSpace, rgVType, lTarget);

			if (pLE) {
				if (pText) pLE -> SetText (pText);
				return true;
			}
		}
		break;

	case LEGENTRYTYPE_SPACELINE:
		{
		CLegendInfoSpaceLine *pLE = ContCreate (Cr, CLegendInfoSpaceLine)(iSrt, (LPCSTR)lTarget, lMCode);

			if (NULL != pLE)
				return true;
		}
		break;

	case LEGENTRYTYPE_TEXT:
		{
		CLegendInfoText *pLE = ContCreate (Cr, CLegendInfoText)(iSrt, fSpace, (LPCSTR)lTarget, lMCode);

			if (pLE) {
				if (pText && LEGENTRYTYPE_TEXT == rgType) 
					pLE -> SetText (pText);
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
bool CLegendInfo::FDeleteItem (WORD &rKT)
{
CTable t(*this);

	if (t.Find (&rKT)) 
		return t.Delete();
	return false;
}

// Funktion, die Pointer auf ein gesuchtes Item liefert ---------------------
CLegendInfoEntry *CLegendInfo::FFindItem (WORD &rKT)
{
CTable t(*this);

	if (t.Find (&rKT)) {
	CLegendInfoEntryLock l(t);

		if (l) return l;
	}
	return NULL;	// nicht gefunden
}

void CLegendInfo::FSetDirty (WORD &rKT)
{
CTable t(*this);

	if (t.Find (&rKT)) {
	CLegendInfoEntryLock l(t);

		if (l) l -> SetDirty();
	}
}

// Diese Funktion zerlegt ein Element des Baumes ------------------------------
void EXPORTTRIAS CLegendInfo::UserDelete (void *pObj)
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
bool CLegendInfo::FEnumAllItems (CLegendInfoEntryEnumFunc pFcn, void *pEData)
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
bool CLegendInfo ::FEnumItems (WORD &rKey, CLegendInfoEntryEnumFunc pFcn, void *pEData)
{
CTable t(*this);

	for (t.FindFirst (&rKey); t.Valid(); t.FindNext (&rKey)) {
	CLegendInfoEntryLock l(t);

		if (l && pFcn (*(CLegendInfoEntry *)l, pEData) == false)
			return false;
	}
	return true;
}

bool CLegendInfo ::FReInsert (WORD &roldKey, WORD &rnewKey)
{
CTable t(*this);

	if (t.Find (&roldKey)) 
		return t.ReInsert (&rnewKey, sizeof (rnewKey));
	return false;
}

// LegendenText typrichtig besorgen -------------------------------------------
char *CLegendInfoIdent::GetText (bool fReadDef)
{
	if (m_pText) return StrDupF (m_pText);
	if (!fReadDef) return NULL;
	
// IdentKurzText besorgen
char *pText = new char [_MAX_PATH*5];

	if (GetPBDText (GetIdent(), pText, _MAX_PATH*5) == NULL)
		SetText ("");
	else	
		SetText (pText);		// diesen Text merken

	CustomizedText (false);
	DELETE (pText);
	return StrDupF (m_pText);
}

char *CLegendInfoObject::GetText (bool fReadDef)
{
	if (m_pText) return StrDupF (m_pText);
	if (!fReadDef) return NULL;
	
// IdentKurzText besorgen
char *pText = new char [_MAX_PATH*5];

	if (GetPBDText (DEX_GetObjIdentEx (GetONr()), pText, _MAX_PATH*5) == NULL)
		SetText ("");
	else	
		SetText (pText);		// diesen Text merken

	CustomizedText (false);
	DELETE (pText);
	return StrDupF (m_pText);
}

char *CLegendInfoText::GetText (bool)
{
	return StrDupF (m_pText);
}

char *CLegendInfoSpaceLine::GetText (bool)
{
	return StrDupF (g_cbNil);
}

bool CLegendInfoText::OnRemoveEntry (INT_PTR lMCode)
{
// 1. MasterMerkmal einlesen
char *pBuffer = NULL;
int iLen = 0;

	if (GetTextMerkmalLen(TT_Sicht, HGENERIC(GetView()), lMCode, iLen))
		pBuffer = new char [iLen+1];

	if (NULL == pBuffer || !ReadTextMerkmal (TT_Sicht, HGENERIC(GetView()), lMCode, pBuffer, iLen)) 
		return false;	// keine Überschriften

// extrahieren der MCodes aus Mastermerkmal
CLegendInfo::CMCodes MCodes;

	if (!CLegendInfo::ExtractMCodes (pBuffer, MCodes)) {
		DELETE(pBuffer);
		return false;	// falsches Format
	}

// entfernen des MCodes aus der Liste
CLegendInfo::CMCodes::iterator it = MCodes.find (GetMCode());

	if (it != MCodes.end()) {
	// Löschen des betreffenden SichtMerkmales
		WriteTextMerkmal(TT_Sicht, (INT_PTR)GetView(), GetMCode(), NULL);

	// Wegschreiben der korrigierten Liste
		MCodes.erase (it);

	int iRequiredLen = CLegendInfo::WriteMCodes (MCodes, pBuffer, iLen);

		if (iRequiredLen >= iLen) {
			DELETE(pBuffer);
			ATLTRY(pBuffer = new char [iRequiredLen+1]);
			if (NULL != pBuffer)
				CLegendInfo::WriteMCodes (MCodes, pBuffer, iRequiredLen);
		}
		if (NULL != pBuffer) 
			return WriteTextMerkmal(TT_Sicht, HGENERIC(GetView()), lMCode, MCodes.size() > 0 ? pBuffer : NULL);
	}
	return false;
}

// neuen Text setzen ----------------------------------------------------------
void CLegendInfoEntry::SetText (LPCSTR pText)
{
	DELETE (m_pText);
	m_pText = StrDupF (pText);
	m_fDirty = true;
	m_fCustText = true;
}

void CLegendInfoEntry::ResetText (void)
{
	DELETE (m_pText);
	m_fCustText = false;
	m_fDirty = true;
}
	
bool CLegendInfo::MakeMCodes (long &rlVMCode, long &rlMCode, const char *pView, INT_PTR lONr)
{
string strView;

	if (NULL == pView) {
	char cbView[MAXVIEWNAMESIZE+1];

		if (!DEX_GetActiveSight (cbView)) 
			return false;

		strView = cbView;
	} else
		strView = pView;

	if (rlVMCode == -1L) {
		rlVMCode = DBO().GetHeaderMCode (true, IDS_LEGENDINFOMCODE,
						 strView.c_str(), IDS_VIEWLEGINFOKURZTEXT, IDS_VIEWLEGINFOLANGTEXT);
		if (rlVMCode == -1L) return false;
	}
		
	if (-1L == rlMCode || 0 != lONr) {		// Objekt hinzufügen muß Pbd schreiben
		rlMCode = DBO().GetObjMCodeView (true, (char *)strView.c_str(), rlVMCode, 0, 0, lONr);
		if (rlMCode == -1L) return false;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// neue Ansicht wurde selektiert
bool CLegendInfo::ViewSelected (LPCSTR pcView)
{
	m_lMCode = -1;
	return MakeMCodes (m_lVMCode, m_lMCode, pcView);
}

// Gesamten Inhalt des Baumes an aktueller Sicht abspeichern, sofern notwendig 
bool CLegendInfo::SaveLegend (void)
{
// MerkmalsCodes besorgen
	if (!DEX_GetActiveSight (m_pBuff)) 
		return false;
	if (!MakeMCodes (m_lVMCode, m_lMCode, m_pBuff)) 
		return false;

	SaveMode (m_pBuff);		// aktuelle AreaMode speichern

// Neu durchzählen, um durchgängigen Index zu haben
WORD iOrder = 1;

// LegendenOffset bestimmen
NAMEDVIEWPROPERTY NVP;
char cbLegOffset[32];
ResString resOffset(IDS_LEGENDOFFSET, 17);

	INITSTRUCT(NVP, NAMEDVIEWPROPERTY);
	NVP.pcView = m_pBuff;
	NVP.pcName = resOffset;
	NVP.pBuffer = cbLegOffset;
	NVP.iLen = sizeof(cbLegOffset);

HRESULT hr = DEX_GetNamedViewProperty(NVP);

	if (SUCCEEDED(hr)) {
		iOrder = atoi (cbLegOffset);
		if (iOrder == 0) iOrder = 1;
	}

// jetzt alle Items neu einordnen
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
	
// jetzt Legende wegschreiben
	for (t.First(); t.Valid(); t.Next()) {
	CLegendInfoEntryLock l(t);
	
		if (!l || !l -> isDirty()) 
			continue;
		l -> SaveLegendEntry (m_rP, m_lMCode);
		l -> SetDirty (false);
	}
	return true;
}

// Testen, ob ein Eintrag der erste/letzte in der Liste ist -------------------
bool CLegendInfo::isFirstEntry (WORD iOrder)
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

bool CLegendInfo::isLastEntry (WORD iOrder)
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
bool CLegendInfoObject::SaveLegendEntry (CLegEntryParser &rP, long lMCode)
{
// gesamten alten Eintrag dieses Objektes einlesen
char *pBuffer = NULL;
CLegendInfoEntry *pLEI[LEGENTRYTYPE_CNT];	// für jeden Objekttyp eine Struktur
int iIndex = -1;
int iLen = 0;

	memset (pLEI, '\0', sizeof(CLegendInfoEntry *) * LEGENTRYTYPE_CNT);
	if (GetTextMerkmalLen(TT_Objekt, HGENERIC(GetONr()), lMCode, iLen)) 
		pBuffer = new char [iLen+1];

	if (NULL != pBuffer &&
		ReadTextMerkmal (TT_Objekt, HGENERIC(GetONr()), lMCode, pBuffer, iLen)) 
	{
	// Merkmal vorhanden
		if (rP.ParseString (TT_Objekt, GetONr(), lMCode, pBuffer, pLEI) < 0) {
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
	case VT_Default:	iIndex = -1; break;	// Zwischenüberschriften (nicht hier !)
	default:	iIndex = -1; break;
	}
	
bool fRet = false;

	if (iIndex >= 0 && iIndex < LEGENTRYTYPE_CNT) {
		DELETE (pLEI[iIndex]);
		pLEI[iIndex] = new CLegendInfoObject (FGetWORD(), isShown(), hasSpace(), GetVType(), GetONr());
		if (GetTextRef() && pLEI[iIndex] && CustomizedText()) // eigener Text
			pLEI[iIndex] -> SetText (GetTextRef());
		
	// gesamten Eintrag am Ident wegschreiben
		if (NULL == pBuffer)
			pBuffer = new char[5*_MAX_PATH];

		if (FormatString (pBuffer, pLEI))
			WriteTextMerkmal (TT_Objekt, GetONr(), lMCode, pBuffer);
			
		fRet = true;
	}
	
	DELETE (pBuffer);
	for (iIndex = 0; iIndex < LEGENTRYTYPE_CNT; iIndex++) {
		DELETE (pLEI[iIndex]);
	}
	return fRet;
}


// Inhalt eines Identifikator/ObjekttypEintrages am Ident wegschreiben --------
bool CLegendInfoIdent::SaveLegendEntry (CLegEntryParser &rP, long lMCode)
{
// gesamten alten Eintrag dieses Idents einlesen
char *pBuffer = NULL;
CLegendInfoEntry *pLEI[LEGENTRYTYPE_CNT];	// für jeden Objekttyp eine Struktur
short iIndex = -1;
int iLen = 0;

	memset (pLEI, '\0', sizeof(CLegendInfoEntry *) * LEGENTRYTYPE_CNT);
	if (GetTextMerkmalLen(TT_Identifikator, HGENERIC(GetIdent()), lMCode, iLen)) 
		pBuffer = new char [iLen+1];

	if (NULL != pBuffer && 
		ReadTextMerkmal (TT_Identifikator, HGENERIC(GetIdent()), lMCode, pBuffer, iLen)) 
	{
	// Merkmal vorhanden
		if (rP.ParseString (TT_Identifikator, GetIdent(), lMCode, pBuffer, pLEI) < 0) {
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
	case VT_Default:	iIndex = 4; break;	// Zwischenüberschriften (nicht hier !)
	default:	iIndex = -1; break;
	}
	
bool fRet = false;

	if (iIndex >= 0 && iIndex < LEGENTRYTYPE_CNT) {
		DELETE (pLEI[iIndex]);
		pLEI[iIndex] = new CLegendInfoIdent (FGetWORD(), isShown(), hasSpace(), GetVType(), GetIdent());
		if (GetTextRef() && pLEI[iIndex] && CustomizedText()) // eigener Text
			pLEI[iIndex] -> SetText (GetTextRef());
		
	// gesamten Eintrag am Ident wegschreiben
		DELETE(pBuffer)
		ATLTRY(pBuffer = new char[5*_MAX_PATH]);
		if (NULL != pBuffer) {
			if (FormatString (pBuffer, pLEI))
				WriteTextMerkmal (TT_Identifikator, GetIdent(), lMCode, pBuffer);
		}
		fRet = true;
	}
	
	DELETE (pBuffer);
	for (iIndex = 0; iIndex < LEGENTRYTYPE_CNT; iIndex++) {
		DELETE (pLEI[iIndex]);
	}
	return fRet;
}

// Zwischenüberschrift speichern
bool CLegendInfoText::SaveLegendEntry (CLegEntryParser &rP, long lMCode)
{
// gesamten alten Eintrag dieser Zwischenüberschrift einlesen
char *pBuffer = NULL;
CLegendInfoEntry *pLEI[LEGENTRYTYPE_CNT];	// für jeden Objekttyp eine Struktur
short iIndex = -1;
int iLen = 0;

	memset (pLEI, '\0', sizeof(CLegendInfoEntry *) * LEGENTRYTYPE_CNT);
	if (GetTextMerkmalLen(TT_Sicht, HGENERIC(GetView()), GetMCode(), iLen)) 
		pBuffer = new char [iLen+1];

	if (NULL != pBuffer && 
		ReadTextMerkmal (TT_Sicht, HGENERIC(GetView()), GetMCode(), pBuffer, iLen)) 
	{
	// Merkmal vorhanden
		if (rP.ParseString (TT_Sicht, (INT_PTR)GetView(), GetMCode(), pBuffer, pLEI) < 0) {
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
	case VT_Default:	iIndex = 4; break;	// Zwischenüberschriften (nicht hier !)
	default:	iIndex = -1; break;
	}
	
bool fRet = false;

	if (iIndex >= 0 && iIndex < LEGENTRYTYPE_CNT) {
		DELETE (pLEI[iIndex]);
		pLEI[iIndex] = new CLegendInfoText (FGetWORD(), hasSpace(), GetView(), GetMCode());
		if (GetTextRef() && pLEI[iIndex] && CustomizedText()) // eigener Text
			pLEI[iIndex] -> SetText (GetTextRef());
		
	// gesamten Eintrag am Ident wegschreiben
		DELETE(pBuffer)
		ATLTRY(pBuffer = new char [5*_MAX_PATH]);
		if (NULL != pBuffer) {
			if (FormatString (pBuffer, pLEI))
				WriteTextMerkmal (TT_Sicht, HGENERIC(GetView()), GetMCode(), pBuffer);
		}

	// MCode in MasterMerkmal wegschreiben
	CLegendInfo::CMCodes MCodes;

		DELETE(pBuffer);
		if (GetTextMerkmalLen(TT_Sicht, HGENERIC(GetView()), lMCode, iLen))
			pBuffer = new char [iLen+1];
		else {
			pBuffer = new char [2*_MAX_PATH];
			iLen = 5*_MAX_PATH;
		}

		if (NULL != pBuffer) {
			pBuffer[0] = '\0';
			ReadTextMerkmal (TT_Sicht, HGENERIC(GetView()), lMCode, pBuffer, iLen);
			CLegendInfo::ExtractMCodes(pBuffer, MCodes);
			MCodes.insert(GetMCode());

		int iRequiredLen = CLegendInfo::WriteMCodes (MCodes, pBuffer, iLen);

			if (iRequiredLen >= iLen) {
				DELETE(pBuffer);
				pBuffer = new char [iRequiredLen+1];
				CLegendInfo::WriteMCodes (MCodes, pBuffer, iRequiredLen);
			}
			if (NULL != pBuffer)
				WriteTextMerkmal(TT_Sicht, HGENERIC(GetView()), lMCode, pBuffer);
		}
		fRet = true;
	}
	
	DELETE (pBuffer);
	for (iIndex = 0; iIndex < LEGENTRYTYPE_CNT; iIndex++) {
		DELETE (pLEI[iIndex]);
	}
	return fRet;
}


// Formatieren einer Zeichenkette zur LegendenEintragsBeschreibung ------------
inline char *EOS (char *pT) { return &pT[strlen(pT)]; }
const char *cbTypes = "plfht";	// Index im VisTypeEnum (default entspricht Zwischenüberschrift)

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
//		TX_ASSERT(EOS(pBuffer)-pBuffer > 40);	// 40 Zeichen dürften reichen

		wsprintf (EOS(pBuffer), "%c=%d:%d;", cbTypes[short(pLEI -> GetVType())],
			  iMode, pLEI -> FGetWORD());
	}
	return true;
}

bool FormatString (char *pBuffer, CLegendInfoEntry *pLEI[LEGENTRYTYPE_CNT])
{
	if (pBuffer == NULL) return false;
	
	*pBuffer = '\0';	// von vorn anfangen
	for (short i = 0; i < LEGENTRYTYPE_CNT; i++) {
		if (pLEI[i] != NULL && !FormatString (pBuffer, pLEI[i]))
			return false;
	}
	return true;
}

bool CLegendInfo::ResetLegend (char *pView)
{
// an allen Idents Merkmal löschen
	if (-1 == m_lVMCode) 
		return true;	// nichts zu löschen

	return DBO().ResetLegend(pView, m_lVMCode);
}

// Einen LegendenEintrag oben verschieben -------------------------------------
bool CLegendInfo::MoveUp (WORD &iActSel, bool fShowAll)
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
bool CLegendInfo::MoveDown (WORD &iActSel, bool fShowAll)
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
bool CLegendInfo::RemoveEntry (WORD iOrder)
{
	if (m_lVMCode == -1L || m_lMCode == -1L) return true;	// nichts zu löschen

CTable t(*this);
bool fToDelete = false;

	if (t.Find(&iOrder)) {
	CLegendInfoEntryLock l(t);
	
		if (!l) return false;
		switch (l -> isA()) {
		case LEGENTRYTYPE_IDENT:	// IdentEintrag löschen
			HandleIdentOnResetLegend (((CLegendInfoIdent *)(CLegendInfoEntry *)l) -> GetIdent(), false, &m_lMCode);
			fToDelete = true;
			break;

		case LEGENTRYTYPE_OBJECT:	// ObjektEintrag löschen
			HandleObjectOnResetLegend (((CLegendInfoObject *)(CLegendInfoEntry *)l) -> GetONr(), false, &m_lMCode);
			fToDelete = true;
			break;

		case LEGENTRYTYPE_SPACELINE:
		case LEGENTRYTYPE_TEXT:
			((CLegendInfoText *)(CLegendInfoEntry *)l) -> OnRemoveEntry (m_lMCode);
			fToDelete = true;
			break;

		default:
			return false;
		}
	}
	if (fToDelete) 
		t.Delete();	// aus Baum löschen
	return false;
}

bool CLegendInfo::InsertHeadLine (WORD iActSel, LPCSTR pcText, bool fInsertBefore)
{
	_ASSERTE(NULL != pcText);
	return AddText (iActSel, DEX_GetUniqueSysMCode(), pcText, fInsertBefore);
}

// Eine Leerzeile anfügen/entfernen -------------------------------------------
bool CLegendInfo::hasSpace (WORD iOrder, bool fSpace)
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
bool CLegendInfo::FPasteEntry (
	LEGENTRYTYPE rgType, VisType rgVType, INT_PTR lTarget, INT_PTR lOldMCode, char *pStr, WORD iOrder)
{
// alles ab dieser Position um eine Stelle weiterrücken
CTable t(*this);

	for (t.Find (&iOrder); t.Valid(); t.Next()) {
	CLegendInfoEntryLock l(t);
	
		if (!l) continue;
		l -> FGetWORD()++;
	}

// an der freigewordenen Stelle den neuen Eintrag einfügen
CLegendInfoEntry *pLEI[LEGENTRYTYPE_CNT];
short iType = TT_Objekt;
INT_PTR lMCode = m_lMCode;

	memset (pLEI, '\0', sizeof(CLegendInfoEntry *) * LEGENTRYTYPE_CNT);
	switch (rgType) {
	case LEGENTRYTYPE_IDENT:
		iType = TT_Identifikator;
		break;
		
	case LEGENTRYTYPE_OBJECT:
		iType = TT_Objekt;
		break;

	case LEGENTRYTYPE_SPACELINE:
	case LEGENTRYTYPE_TEXT:
		iType = TT_Sicht;		// ;)
		lMCode = (NULL == lOldMCode) ? DEX_GetUniqueSysMCode() : lOldMCode;
		break;

	case LEGENTRYTYPE_UNKNOWN:
	default:
		return false;
	}
	
	if (m_rP.ParseString (iType, lTarget, lMCode, pStr, pLEI) < 0) 
		return false;
	
// betreffende Info's austauschen
short iIndex = -1;

	switch (rgVType) {
	case VT_Punkt:	iIndex = 0; break;
	case VT_Linie:	iIndex = 1; break;
	case VT_Flaeche:iIndex = 2; break;
	case VT_Text:	iIndex = 3; break;
	case VT_Default:	iIndex = 4; break;	// Zwischenüberschrift
	default:	iIndex = -1; break;
	}

	if (NULL != pLEI[iIndex]) {	
		pLEI[iIndex] -> FGetWORD() = iOrder;	// neu einordnen
		
	CLegendInfoEntryCreator Cr (*this);
	
		return (NULL != Cr.InsertPtr (pLEI[iIndex])) ? true : false;
	}
	return false;
}

