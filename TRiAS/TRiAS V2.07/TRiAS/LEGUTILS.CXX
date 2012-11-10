// Routinen für Verwaltung der LegendenMerkmale für LegendenStruktur ----------
// File: LEGUTILS.CXX

#include "triaspre.hxx"
#include "strings.h"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define MCODESIZE	20

bool SaveObjMCodeInPbd (LPCSTR pView, long lMCode, uint, uint);
bool SaveViewMCodeInPbd (LPCSTR pView, long lMCode, uint, uint);
bool SaveIdentMCodeInPbd (LPCSTR pView, long lMCode, uint, uint);

long GetHeaderMCode (bool fGenerate, uint resID, LPCSTR pView, 
		     uint uiResKT, uint uiResLT)
{
GEODBHDRENTRY hdrEntry;
long result = -1L;

	INITSTRUCT(hdrEntry, GEODBHDRENTRY);
	strncpy (hdrEntry.hdrKey, ResString (resID, 17), 16);
	hdrEntry.lphdrText = NULL; ATLTRY(hdrEntry.lphdrText = new char [MCODESIZE +1]);
	hdrEntry.hdrTextLen = MCODESIZE;

	if (DEX_ReadGeoDBHdrEntry (hdrEntry) == EC_OKAY) {
	// HeaderEintrag existiert
		result = atol (hdrEntry.lphdrText);
		if (result == 0L) result = -1L;
	} else if (fGenerate) {
	// bei Bedarf neu generieren
	long lMCode = DEX_GetUniqueSysMCode();	// neuen MCode besorgen
	
		if (lMCode != -1) {		// und wegschreiben
			hdrEntry.hdrTextLen = MCODESIZE;
			ltoa (lMCode, hdrEntry.lphdrText, 10);

			if (DEX_WriteGeoDBHdrEntry (hdrEntry) == EC_OKAY)
				result = lMCode;
		// in Pbd eintragen
			SaveViewMCodeInPbd (pView, lMCode, uiResKT, uiResLT);
		}
	}
	DELETE (hdrEntry.lphdrText);
	return result;
}

// Für eine bestimmte Sicht MCode für Objekte besorgen ------------------------
long GetObjMCodeView (bool fGenerate, LPCSTR pView, long lVMCode, uint uiResKT, uint uiResLT)
{
string strView;

	if (NULL == pView) {
	char cbBuffer[_MAX_PATH];
	
		if (NULL == DEX_GetActiveSight(cbBuffer))
			return -1L;
		strView = cbBuffer;
	} else
		strView = pView;

TARGETMERKMAL gm;
long result = -1L;

	INITSTRUCT(gm, TARGETMERKMAL);
	gm.lTarget = (LPARAM)strView.c_str();
	gm.lMCode = lVMCode;
	gm.imaxLen = MCODESIZE;
	gm.pMText = NULL; ATLTRY(gm.pMText = new char [MCODESIZE+1]);
	gm.iTTyp = TT_Sicht;

	if (DEX_GetTextMerkmal (gm) != NULL) {
		if (gm.pMText)
			result = atol (gm.pMText);
	} else if (fGenerate) {
	// neu generieren
	long lMCode = DEX_GetUniqueSysMCode();
	
		if (lMCode != -1 && gm.pMText) {	// und wegschreiben
			ltoa (lMCode, gm.pMText, 10);
			gm.imaxLen = MCODESIZE;

			if (DEX_ModTextMerkmal (gm) == EC_OKAY) {
				result = lMCode;

			// neuen Eintrag in PBD generieren
				SaveObjMCodeInPbd (strView.c_str(), result, uiResKT, uiResLT);
			}
		}
	}
	DELETE (gm.pMText);

return result;
}

///////////////////////////////////////////////////////////////////////////////
// Für eine bestimmte Sicht MCode für Idents besorgen 
long GetIdentMCodeView (bool fGenerate, LPCSTR pView, long lVMCode, uint uiResKT, uint uiResLT)
{
string strView;

	if (NULL == pView) {
	char cbBuffer[_MAX_PATH];
	
		if (NULL == DEX_GetActiveSight(cbBuffer))
			return -1L;
		strView = cbBuffer;
	} else
		strView = pView;

TARGETMERKMAL gm;
long result = -1L;

	INITSTRUCT(gm, TARGETMERKMAL);
	gm.lTarget = (LPARAM)strView.c_str();
	gm.lMCode = lVMCode;
	gm.imaxLen = MCODESIZE;
	gm.pMText = NULL; ATLTRY(gm.pMText = new char [MCODESIZE+1]);
	gm.iTTyp = TT_Sicht;

	if (DEX_GetTextMerkmal (gm) != NULL) {
		if (gm.pMText)
			result = atol (gm.pMText);
	} else if (fGenerate) {
	// neu generieren
	long lMCode = DEX_GetUniqueSysMCode();
	
		if (lMCode != -1 && gm.pMText) {	// und wegschreiben
			ltoa (lMCode, gm.pMText, 10);
			gm.imaxLen = MCODESIZE;

			if (DEX_ModTextMerkmal (gm) == EC_OKAY) {
				result = lMCode;

			// neuen Eintrag in PBD generieren
				SaveIdentMCodeInPbd (strView.c_str(), result, uiResKT, uiResLT);
			}
		}
	}
	DELETE (gm.pMText);

return result;
}

///////////////////////////////////////////////////////////////////////////////
// Eintrag für ObjMCode in PBD generieren 
bool SaveObjMCodeInPbd (LPCSTR pView, long lMCode, uint uiRes1, uint uiRes2)
{
	if (0 == uiRes1) uiRes1 = IDS_LEGINFOKURZTEXT;		// Notanker
	if (0 == uiRes2) uiRes2 = IDS_LEGINFOLANGTEXT;

	return SaveViewMCodeInPbd (pView, lMCode, uiRes1, uiRes2);
}

///////////////////////////////////////////////////////////////////////////////
// Eintrag für IdentMCode in PBD generieren 
bool SaveIdentMCodeInPbd (LPCSTR pView, long lMCode, uint uiRes1, uint uiRes2)
{
	return SaveViewMCodeInPbd (pView, lMCode, uiRes1, uiRes2);
}

///////////////////////////////////////////////////////////////////////////////
// Eintrag für ViewLegMCode in PBD generieren 
bool SaveViewMCodeInPbd (LPCSTR pView, long lMCode, uint uiRes1, uint uiRes2)
{
// PBDEintrag zusammenstellen
char *pKText = NULL; ATLTRY(pKText = new char [64]);
char *pLText = NULL; ATLTRY(pLText = new char [256]);

	if (pKText == NULL || pLText == NULL) {
		DELETE (pKText);
		return false;
	}

const char *pLocView = pView ? pView : g_cbNil;
ResString KFormat (uiRes1, 32);
ResString LFormat (uiRes2, 64);

	wsprintf (pKText, KFormat, pLocView);
	if (NULL != pLocView && strlen (pKText) > 31) {	// länger als max. KurzText
		pKText[31] = ')';	// SichtNamen abschneiden
		pKText[32] = '\0';
	}
	wsprintf (pLText, LFormat, pLocView);

PBDMERKMAL TM;
bool iResult = true;

	INITSTRUCT(TM, PBDMERKMAL);
	TM.pbdTyp = 'm';
	TM.pbdCode = lMCode;
	TM.pbdKText = pKText;
	TM.pbdLText = pLText;	
	TM.pbdKTextLen = strlen (pKText);
	TM.pbdLTextLen = strlen (pLText);
	TM.ipbdMTyp = 'b' | PBDMERKMAL_SYSTEMFLAG;
	TM.ipbdMLen = 256;
	{
	ErrInstall EI (WC_NOMERKMAL);

		if (DEX_ModPBDData (TM) != EC_OKAY)
			iResult = false;
		else
			DEXN_PBDMCodeChanged (lMCode);
	}
	
// Speicher freigeben
	delete pKText;
	delete pLText;
	return iResult; 
}

bool ReadTextMerkmal (short iTTyp, DWORD lTarget, long lMCode, char *pText, short iLen)
{
TARGETMERKMAL gm;

	INITSTRUCT(gm, TARGETMERKMAL);
	gm.lTarget = (LPARAM)lTarget;
	gm.lMCode = lMCode;
	gm.imaxLen = pText != NULL ? iLen : 0;
	gm.pMText = pText;
	gm.iTTyp = iTTyp;
	if (DEX_GetTextMerkmal (gm) == NULL)
		return false;

return true;
}

bool WriteTextMerkmal (short iTTyp, long lTarget, long lMCode, char *pText, short iFlags)
{
TARGETMERKMALEX gm;

	INITSTRUCT(gm, TARGETMERKMALEX);
	gm.lTarget = (LPARAM)lTarget;
	gm.lMCode = lMCode;
	gm.imaxLen = pText != NULL ? strlen (pText) : 0;
	gm.pMText = pText;
	gm.iTTyp = iTTyp;
	gm.iFlags = iFlags;
	if (DEX_ModTextMerkmal (gm) != EC_OKAY)
		return false;

return true;
}


// BehandlungsRoutinen für HANDLEVISINFO --------------------------------------
HANDLEVISINFO *ctHANDLEVISINFO (short iVTyp)
{
HANDLEVISINFO *pHVI = new HANDLEVISINFO;
VISINFO *pVI = NULL;

	if (pHVI == NULL) return NULL;
	
	switch (iVTyp) {
	case VTPunkt:
		pVI = (VISINFO *)new PVISINFO;
		if (pVI) memset (pVI, '\0', sizeof(PVISINFO));
		break;
		
	case VTLinie:
		pVI = (VISINFO *)new LVISINFO;
		if (pVI) memset (pVI, '\0', sizeof(LVISINFO));
		break;
		
	case VTFlaeche:
		pVI = (VISINFO *)new FVISINFO;
		if (pVI) memset (pVI, '\0', sizeof(FVISINFO));
		break;
		
	case VTText:
		pVI = (VISINFO *)new TVISINFO;
		if (pVI) memset (pVI, '\0', sizeof(TVISINFO));
		break;

	default:
	case VTDefault:
		pVI = (VISINFO *)new DVISINFO;
		if (pVI) memset (pVI, '\0', sizeof(DVISINFO));
		break;
	}
	if (pVI == NULL) {
		DELETE (pHVI);
		return NULL;
	}

	memset (pHVI, '\0', sizeof(HANDLEVISINFO));
	pHVI -> dwSize = sizeof (HANDLEVISINFO);
	pHVI -> m_iVTyp = iVTyp;
	pHVI -> m_pVI = pVI;

return pHVI;
}

// Destruktor für HANDLEVISINFO -----------------------------------------------
void dtHANDLEVISINFO (HANDLEVISINFO *& pHVI)
{
	if (pHVI) {
		DELETE (pHVI -> m_pVI);
		DELETE (pHVI -> m_pView);
		DELETE (pHVI -> m_pDesc);
		DELETE (pHVI);
	}
}

// VisualisierungsInfo für einen Identifikator/Typ besoregn -------------------
HANDLEVISINFO *GetIdentVisInfo (long lIdent, short iVTyp, char *pView)
{
// typgerechte VISINFO-Struktur anfordern
HANDLEVISINFO *pHVI = ctHANDLEVISINFO (iVTyp);

	if (pHVI == NULL) return NULL;

// Strukturen füllen
	pHVI -> m_pView = pView;
	pHVI -> m_lIdent = lIdent;
	
	if (!DEX_GetIdentVisInfo (*pHVI)) 	// Fehler aufgetreten
		dtHANDLEVISINFO (pHVI);
	
return pHVI;
}


// Visinfo für einen Ident neu einstellen -------------------------------------
bool DefineNewIdentVisInfo (long lIdent, short iVTyp, bool fHSB)
{
	if (!IsValidIdent(lIdent) || iVTyp == VT_Default)
		return false;	// falsche Parameter
		
// aktuelle VisInfo für Ident/Typ besorgen (StandardVisualisierung)
HANDLEVISINFO *pHVI = GetIdentVisInfo (lIdent, iVTyp, NULL);

	if (pHVI == NULL) return false;	// Fehler

	if (fHSB) pHVI -> m_fFlags |= DF_HSBModel;

// DialogFenster zur VisInfoEinstellung anfordern
short iResult = false;

// IdentKurzText besorgen
PBDDATA pbdData;
char pKText[33];

	INITSTRUCT(pbdData, PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = lIdent;
	pbdData.pbdKText = pKText;
	pbdData.pbdKTextLen = sizeof(pKText) -1;

	if (DEX_GetPBDData (pbdData) != EC_OKAY)
		ClassFromIdent (lIdent, pKText, sizeof(pKText));
		
	pKText[32] = '\0';
	pHVI -> m_pDesc = pKText;	// Überschrift der DialogBox setzen
	
	if (DEX_ModVisInfoDialog (*pHVI) == EC_OKAY && 
	    DEX_ModIdentVisInfo (*pHVI) == EC_OKAY)
		iResult = true;
		
	pHVI -> m_pDesc = NULL;		// Verhindern, daß gelöscht wird
	dtHANDLEVISINFO (pHVI);		// Speicher freigeben
		
return iResult;	// ok, error handled
}

// Besorgen des Kurz/Langtextes aus der PBD -----------------------------------
bool HasSpacesOnly (LPCSTR pcText)
{
	while (*pcText) {
		if (!isspace(*pcText))
			return false;
		pcText++;
	}
	return true;		// besteht nur aus spaces
}

char *GetPBDText (long lIdent, char *pText, int iLen)
{
	if (!IsValidIdent(lIdent)) return NULL;

PBDDATA pbdData;
char pKText[34];

	INITSTRUCT(pbdData, PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = lIdent;
	pbdData.pbdKText = pKText;
	pbdData.pbdKTextLen = sizeof(pKText) -1;
	pbdData.pbdLText = pText;
	pbdData.pbdLTextLen = pText ? iLen-1 : 0;
	
	if (DEX_GetPBDData (pbdData) != EC_OKAY) {
		return NULL;
	}
	pKText[32] = '\0';
	if (pbdData.pbdLTextLen <= 0 || HasSpacesOnly(pbdData.pbdLText))
		strcpy (pText, pKText);		// kein LangText (oder leer) --> Kurztext

return pText;
}		

