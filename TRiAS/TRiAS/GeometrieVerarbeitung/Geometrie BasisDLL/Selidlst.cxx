// Eine Listbox, die alle Identifikator/Objekttypen der Datenbasis enthält ----
// File: SELIDLST.CXX
// H. Kaiser


#include "GeometrP.hxx"

#include "selidlsx.hxx"		// CSelIdentListX

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#if defined(_DEBUG)
HRESULT ClassFromIdentX (ULONG ulIdent, char *pBuffer, int iBuffLen)
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

HRESULT IdentFromClassX (LPCSTR pcClass, ULONG *pulIdent, BOOL fCreateNew)
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
#endif // _DEBUG

// Konstruktor/Destruktor/Initialisierung -------------------------------------
_GEOMETR_EXPORT CSelIdentListX :: CSelIdentListX (pDialogWindow pW, ResID uiRes)
								: MultiSelListBox (pW, uiRes)
{
	m_pBuff = NULL;
	m_ulLastIdent = 0;
	m_iLastTypes = 0;
}

_GEOMETR_EXPORT CSelIdentListX :: ~CSelIdentListX (void)
{
	DELETE_OBJ (m_pBuff);
}


extern "C" {


typedef struct tagFILLIDENTDATA {
	MultiSelListBox *m_pMSLB;
//	short m_iIdBase;	// wird nicht mehr benötigt (22.1.97)
	char *m_pOutBuff;
	bool m_bShowRO;		// schreibgeschützte Objektklassen anzeigen (true) (21.09.99)
} FILLIDENTDATA;


// bShowRO = false/true: schreibgeschützte Objektklasse nicht/anzeigen
static void AddTypeString (FILLIDENTDATA* pFI, ulong ulIdent, char cTyp, char* pcKText,
						   bool bShowRO)
{
	ClassFromIdentX (ulIdent, pFI -> m_pOutBuff);
	strcat (pFI -> m_pOutBuff, ":");
	strcat (pFI -> m_pOutBuff, &cTyp);
	strcat (pFI -> m_pOutBuff, ":");
	strcat (pFI -> m_pOutBuff, pcKText);

#if _TRiAS_VER < 0x0300
	pFI -> m_pMSLB -> AddString (pFI -> m_pOutBuff);
#else
	// schreibgeschützte Objektklasse bei bShowRO == false nicht anzeigen
	if (!bShowRO &&		// 21.09.99
		DEX_GetROModeIdent (ulIdent))
		return;

	if (DEX_GetOpenConnectionCount (QDCAllOpen|QDCCountQueryDefs) > 1)
	{
	HPROJECT hPr = DEX_GetObjectsProject (ulIdent);

		_ASSERTE (NULL != hPr);

	char cbBuffer[_MAX_PATH];

		if (NULL != DEX_GetDataSourceShortName (hPr, cbBuffer))
		{
			strcat (pFI -> m_pOutBuff, " (");
			strcat (pFI -> m_pOutBuff, cbBuffer);
			strcat (pFI -> m_pOutBuff, ")");
		}
	}

// als zusätzliche Daten für jedes LB-Item den zugehörigen Ident setzen
int iIndex = pFI -> m_pMSLB -> AddString (pFI -> m_pOutBuff);

	pFI -> m_pMSLB -> SetItemData (iIndex, ulIdent);
#endif // _TRiAS_VER < 0x0300
}


BOOL PASCAL FillIdentsMSLB (ulong ulIdent, DWORD dwTypes, void *pData)
{
PBDDATA pbdData;
char pcKText[64];
FILLIDENTDATA *pFI = (FILLIDENTDATA *)pData;

	memset (pcKText, '\0', sizeof(pcKText));
	INITSTRUCT (pbdData, PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = ulIdent;
	pbdData.pbdKText = pcKText;
	pbdData.pbdKTextLen = sizeof(pcKText) -1;
	pbdData.pbdLTextLen = 0;
	DEX_GetPBDData (pbdData);
//	pcKText[32] = '\0';
	
//	if (dwTypes & OTPunkt)	 AddTypeString (pFI, ulIdent, 'P', pbdData.pbdKText,);
	if (dwTypes & OTPunkt)	 AddTypeString (pFI, ulIdent, 'P', pbdData.pbdKText, pFI->m_bShowRO);	// 21.09.99
//	if (dwTypes & OTLinie)	 AddTypeString (pFI, ulIdent, 'L', pbdData.pbdKText);
	if (dwTypes & OTLinie)	 AddTypeString (pFI, ulIdent, 'L', pbdData.pbdKText, pFI->m_bShowRO);
//	if (dwTypes & OTFlaeche) AddTypeString (pFI, ulIdent, 'F', pbdData.pbdKText);
	if (dwTypes & OTFlaeche) AddTypeString (pFI, ulIdent, 'F', pbdData.pbdKText, pFI->m_bShowRO);
//	if (dwTypes & OTText)	 AddTypeString (pFI, ulIdent, 'T', pbdData.pbdKText);
	if (dwTypes & OTText)	 AddTypeString (pFI, ulIdent, 'T', pbdData.pbdKText, pFI->m_bShowRO);

return true;	// weitermachen
}

} 	// extern "C"


//bool CSelIdentListX :: FInit (void)
bool CSelIdentListX :: FInit (bool bShowRO)		// 21.09.99
{
// Zeichenkette anlegen
	m_pBuff = new char [_MAX_PATH];
	if (m_pBuff == NULL) return false;

FILLIDENTDATA FID;

	FID.m_pMSLB = this;
	FID.m_pOutBuff = m_pBuff;
	FID.m_bShowRO = bShowRO;	// 21.09.99

ENUMTEXTKEYEX ETK;

	ETK.eKey = NULL;			// aktuelle Sicht
	ETK.eFcn = (ENUMLONGKEYEXPROC)FillIdentsMSLB;
	ETK.ePtr = &FID;
	ETK.eData = OTPunkt|OTLinie|OTFlaeche|OTText;
	if (!DEX_EnumSightIdentsEx (ETK))	// alle Idents dieser Sicht
		return false;

return true;
}


//CSelIdentListX * _GEOMETR_EXPORT CSelIdentListX :: CreateInstance (pDialogWindow pW, ResID uiRes)
CSelIdentListX * _GEOMETR_EXPORT CSelIdentListX :: CreateInstance (pDialogWindow pW,
																   ResID uiRes, bool bShowRO)	// 21.09.99)
{
CSelIdentListX *pLst = new CSelIdentListX (pW, uiRes);

//	if (pLst == NULL || !pLst -> FInit()) {
	if (pLst == NULL || !pLst -> FInit (bShowRO)) {	// 21.09.99
		DELETE_OBJ (pLst);
		return NULL;
	}
	
return pLst;
}


// ZugriffsFunktionen auf ausgewählte Identifikatoren -------------------------
// Diese Funktionen liefern jetzt alle selektierten Objekttypen für einen Ident
// mit einem mal.
bool _GEOMETR_EXPORT CSelIdentListX :: GetFirstIdent (ulong &rulIdent, short &riOTyp)
{
// anfängliche Initialisierungen
	m_ulLastIdent = 0;
	m_iLastTypes = 0;
	
	if (!DecodeEntry (GetFirstSelected(), m_ulLastIdent, m_iLastTypes))
		return false;		// kein Eintrag verfügbar

return GetNextIdent (rulIdent, riOTyp);
}


bool _GEOMETR_EXPORT CSelIdentListX :: GetNextIdent (ulong &rulIdent, short &riOTyp)
{
// wenn wir bereits am Ende sind
	if (m_ulLastIdent == 0)
		return false;	// kein weiterer Eintrag verfügbar
		
// ersten Ident gefunden
	rulIdent = m_ulLastIdent;
	riOTyp = m_iLastTypes;
	
// jetzt solange suchen, bis neuer Ident kommt
	do {
		if (!DecodeEntry (GetNextSelected(), m_ulLastIdent, m_iLastTypes)) {
			m_ulLastIdent = 0;	// das war der letzte Eintrag
			m_iLastTypes = 0;
			return true;
		}
		if (rulIdent != m_ulLastIdent)
			break;
		riOTyp |= m_iLastTypes;		// Typ hinzufügen
	} while (true);

return true;
}


bool _GEOMETR_EXPORT CSelIdentListX :: SelectIdent (ulong ulIdent, short iOTyp, bool fSel)
{
short iCnt = GetCount();
ulong ulCurrIdent = 0;
short iCurrOTyp = 0;

	for (short iIndex = 0; iIndex < iCnt; iIndex++) {
	// Alle Einträge der Listbox abarbeiten
	
		if (DecodeEntry (iIndex, ulCurrIdent, iCurrOTyp)) {
			if (ulCurrIdent == ulIdent && iCurrOTyp == iOTyp) {
			// Eintrag gefunden
				ChangeSelected (iIndex, fSel);
				SetTop (iIndex);
				return true;
			}
		}
	}

return false;
}


// HilfsFunktionen ------------------------------------------------------------
bool CSelIdentListX :: DecodeEntry (short iIndex, ulong &rulIdent, short &riOTyp)
{
	if (iIndex == -1) return false;
	
char *pT = NULL;

	GetString (m_pBuff, iIndex, _MAX_PATH);

#if _TRiAS_VER < 0x0300
	IdentFromClassX (m_pBuff, &rulIdent);
#else
	rulIdent = GetItemData (iIndex);		// Ident ist am Item gespeichert
	_ASSERTE (0 != rulIdent);
#endif //_TRiAS_VER < 0x0300

	pT = strchr(m_pBuff, ':');
	if (pT) 
		riOTyp = GetOTyp (*(pT+1));
	else {
		riOTyp = 0;	// Unknown type
		return false;
	}
		
return true;
}

short CSelIdentListX :: GetOTyp (short ch)
{
	switch (ch) {
	case 'P':	return OTPunkt;
	case 'L':	return OTLinie;
	case 'F':	return OTFlaeche;
	case 'T':	return OTText;
	}

return 0;
}
