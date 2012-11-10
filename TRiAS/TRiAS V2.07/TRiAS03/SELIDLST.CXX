// Eine Listbox, die alle Identifikator/Objekttypen der Datenbasis enthält ----
// File: SELIDLST.CXX

#include "trias03p.hxx"

#include <funcs03.h>
#include <selidlst.hxx>

// Konstruktor/Destruktor/Initialisierung -------------------------------------
EXPORT03  CSelIdentList :: CSelIdentList (pDialogWindow pW, ResID uiRes)
			: MultiSelListBox (pW, uiRes)
{
	m_pBuff = NULL;
	m_lLastIdent = -1L;
	m_iLastTypes = 0;
}

EXPORT03  CSelIdentList :: ~CSelIdentList (void)
{
	DELETE_OBJ (m_pBuff);
}


extern "C" {

typedef struct tagFILLIDENTDATA {
	MultiSelListBox *m_pMSLB;
	char *m_pOutBuff;
} FILLIDENTDATA;

static 
void AddTypeString (FILLIDENTDATA *pFI, long lIdent, char cTyp, char *pKText)
{
char cbBuffer[MAX_OKS_LEN];

	ClassFromIdent (lIdent, cbBuffer);
	wsprintf (pFI -> m_pOutBuff, "%s:%c:%s", cbBuffer, cTyp, pKText);
	pFI -> m_pMSLB -> AddString (pFI -> m_pOutBuff);
}


BOOL EXPORT03  PASCAL FillIdentsMSLB (long lIdent, DWORD dwTypes, void *pData)
{
PBDDATA pbdData;
char cbKText[34];
FILLIDENTDATA *pFI = (FILLIDENTDATA *)pData;

	memset (&pbdData, '\0', sizeof(PBDDATA));
	memset (cbKText, '\0', sizeof(cbKText));

	pbdData.dwSize = sizeof(PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = lIdent;
	pbdData.pbdKText = cbKText;
	pbdData.pbdKTextLen = sizeof(cbKText) -1;
	pbdData.pbdLTextLen = 0;
	DEX_GetPBDData (pbdData);
	cbKText[32] = '\0';
	
	if (dwTypes & OTPunkt)	 AddTypeString (pFI, lIdent, 'P', pbdData.pbdKText);
	if (dwTypes & OTLinie)	 AddTypeString (pFI, lIdent, 'L', pbdData.pbdKText);
	if (dwTypes & OTFlaeche) AddTypeString (pFI, lIdent, 'F', pbdData.pbdKText);
	if (dwTypes & OTText)	 AddTypeString (pFI, lIdent, 'T', pbdData.pbdKText);
	if (dwTypes & OTKO)	 AddTypeString (pFI, lIdent, 'K', pbdData.pbdKText);

return true;	// weitermachen
}

} 	// extern "C"


bool EXPORT03  CSelIdentList :: FInit (void)
{
// ZeichenKette anlegen
	m_pBuff = new char [_MAX_PATH];
	if (m_pBuff == NULL) return false;

FILLIDENTDATA FID;

	FID.m_pMSLB = this;
	FID.m_pOutBuff = m_pBuff;

ENUMTEXTKEYEX ETK;

	ETK.eKey = NULL;			// aktuelle Sicht
	ETK.eFcn = (ENUMLONGKEYEXPROC)FillIdentsMSLB;
	ETK.ePtr = &FID;
	ETK.eData = OTPunkt|OTLinie|OTFlaeche|OTText|OTKO;
	if (!DEX_EnumSightIdentsEx (ETK))	// alle Idents dieser Sicht
		return false;

return true;
}


CSelIdentList * EXPORT03  CSelIdentList :: CreateInstance (pDialogWindow pW, ResID uiRes)
{
CSelIdentList *pLst = new CSelIdentList (pW, uiRes);

	if (pLst == NULL || !pLst -> FInit()) {
		DELETE_OBJ (pLst);
		return NULL;
	}
	
return pLst;
}


// ZugriffsFunktionen auf ausgewählte Identifikatoren -------------------------
// Diese Funktionen liefern jetzt alle selektierten Objekttypen für einen Ident
// mit einem mal.
bool EXPORT03 CSelIdentList :: GetFirstIdent (long &rlIdent, short &riOTyp)
{
// anfängliche Initialisierungen
	m_lLastIdent = -1L;
	m_iLastTypes = 0;
	
	if (!DecodeEntry (GetFirstSelected(), m_lLastIdent, m_iLastTypes))
		return false;		// kein Eintrag verfügbar

return GetNextIdent (rlIdent, riOTyp);
}

bool EXPORT03 CSelIdentList :: GetNextIdent (long &rlIdent, short &riOTyp)
{
// wenn wir bereits am Ende sind
	if (m_lLastIdent == -1L)
		return false;	// kein weiterer Eintrag verfügbar
		
// ersten Ident gefunden
	rlIdent = m_lLastIdent;
	riOTyp = m_iLastTypes;
	
// jetzt solange suchen, bis neuer Ident kommt
	do {
		if (!DecodeEntry (GetNextSelected(), m_lLastIdent, m_iLastTypes)) {
			m_lLastIdent = -1L;	// das war der letzte Eintrag
			m_iLastTypes = 0;
			return true;
		}
		if (rlIdent != m_lLastIdent)
			break;
		riOTyp |= m_iLastTypes;		// Typ hinzufügen
	} while (true);

return true;
}

bool EXPORT03 CSelIdentList::GetFirstIdentEx (long &rlIdent, short &riOTyp, int &riCnt)
{
// anfängliche Initialisierungen
	m_lLastIdent = -1L;
	m_iLastTypes = 0;
	riCnt = 0;

	if (!DecodeEntry (GetFirstSelected(), m_lLastIdent, m_iLastTypes))
		return false;		// kein Eintrag verfügbar

	return GetNextIdent (rlIdent, riOTyp);
}

bool EXPORT03 CSelIdentList::GetNextIdentEx (long &rlIdent, short &riOTyp, int &riCnt)
{
// wenn wir bereits am Ende sind
	if (m_lLastIdent == -1L)
		return false;	// kein weiterer Eintrag verfügbar
		
// ersten Ident gefunden
	rlIdent = m_lLastIdent;
	riOTyp = m_iLastTypes;
	riCnt++;

// jetzt solange suchen, bis neuer Ident kommt
	do {
		if (!DecodeEntry (GetNextSelected(), m_lLastIdent, m_iLastTypes)) {
			m_lLastIdent = -1L;	// das war der letzte Eintrag
			m_iLastTypes = 0;
			return true;
		}
		if (rlIdent != m_lLastIdent)
			break;
		riOTyp |= m_iLastTypes;		// Typ hinzufügen
		riCnt++;
	} while (true);

return true;
}

bool EXPORT03 CSelIdentList :: SelectIdent (long lIdent, short iOTyp, bool fSel)
{
long lCurrIdent = -1;
short iCurrOTyp = 0;
char cbBuffer[MAX_OKS_LEN];

	ClassFromIdent (lIdent, cbBuffer);

int iIndex = FindString (cbBuffer, false, -1);

	while (-1 != iIndex) {
		if (DecodeEntry (iIndex, lCurrIdent, iCurrOTyp)) {
			if (lCurrIdent == lIdent && iCurrOTyp == iOTyp) {
			// Eintrag gefunden
				ChangeSelected (iIndex, fSel);
				return true;
			}
		}
	
	int iNext = FindString (cbBuffer, false, iIndex);	// nächsten suchen

		if (iNext <= iIndex)
			break;
		iIndex = iNext;
	}

return false;
}


// HilfsFunktionen ------------------------------------------------------------
bool CSelIdentList :: DecodeEntry (short iIndex, long &rlIdent, short &riOTyp)
{
	if (iIndex == -1) return false;
	
char *pT = NULL;

	GetString (m_pBuff, iIndex, _MAX_PATH);
	IdentFromClass (m_pBuff, (ULONG *)&rlIdent);

	pT = strchr (m_pBuff, ':');
	if (pT && *pT == ':') 
		riOTyp = GetOTyp (*(pT+1));
	else {
		riOTyp = 0;	// Unknown type
		return false;
	}
		
return true;
}

short CSelIdentList :: GetOTyp (short ch)
{
	switch (ch) {
	case 'P':	return OTPunkt;
	case 'L':	return OTLinie;
	case 'F':	return OTFlaeche;
	case 'T':	return OTText;
	case 'K':	return OTKO;
	}

return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Globale Funktionen
#if defined(WIN32)

_TRIAS03_ENTRY 
HRESULT ClassFromIdent (ULONG ulIdent, char *pBuffer, int iBuffLen)
{
CLASSFROMIDENT CFI;

	INITSTRUCT(CFI, CLASSFROMIDENT);
	CFI.ulIdent = ulIdent;
	CFI.pClass = pBuffer;
	CFI.iBuffLen = iBuffLen;
	if (NULL != pBuffer && iBuffLen > 0)
		pBuffer[0] = '\0';
	return DEX_GetClassFromIdent(CFI);
}

_TRIAS03_ENTRY 
HRESULT IdentFromClass (LPCSTR pcClass, ULONG *pulIdent, bool fCreateNew)
{
	if (NULL == pulIdent) return E_POINTER;

IDENTFROMCLASS IFC;

	INITSTRUCT(IFC, IDENTFROMCLASS);
	IFC.pcClass = pcClass;
	IFC.fCreateNew = fCreateNew;

HRESULT hr = DEX_GetIdentFromClass(IFC);

	if (SUCCEEDED(hr)) 
		*pulIdent = IFC.ulIdent;

	return hr;
}

#endif // WIN32

