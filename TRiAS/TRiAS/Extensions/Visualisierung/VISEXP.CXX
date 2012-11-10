// Ausgabe der Visualiserungsinformationen einer Datenbank im VISASC-Format ---
// File: VISEXP.CXX

#include "visobjp.hxx"

#include <stdio.h>
#include <stddlg.hxx>

#include <ospace/time/timedate.h>
#include <protos.h>
#include <eieruhr.hxx>
#include <hdrentrx.hxx>
#if !defined(WIN32)
#include <ctl3d.h>
#include <commdlg.h>
#endif

#include "visobj.h"
#include "visexp.h"

#include "resource.h"
#include "Strings.h"

#include "visexp.hxx"
#include "vstatus.hxx"
#include "LegendMCodes.h"

short OTypToBits (short iOTyp);
inline char *EOS (char *pBuffer) { return &pBuffer[strlen(pBuffer)]; }

// Exportieren der VisInfo ausgewählter Sichten einer GeoDB -------------------
bool CVisObjExtension::ExportVisInfo (void) 
{
// MerkmalsCodes besorgen, unter denen die ObjektVisInfo und die LegInfo 
// gespeichert sind, wenn keine aktive Sicht existiert.
long lVisMCode = m_lSichtVisMCode;
long lLegMCode = m_lSichtLegMCode;

	if (lVisMCode == -1L) lVisMCode = GetViewMCode();
	if (lLegMCode = -1L) lLegMCode = GetViewLegMCode();

// AusgabeOptionen abfragen
CExportVisInfoDlg *pEVIDlg = 
	CExportVisInfoDlg::CreateInstance (MWind(), &RF(), lVisMCode, lLegMCode);

	if (pEVIDlg == NULL) return false;	// Fehler bei der Initialisierung
	
	pEVIDlg -> Show (Centre);		// Dialogfenster anzeigen

int iResult = pEVIDlg -> Result();

	DELETE_OBJ (pEVIDlg);

return iResult;
}


static void ExportVisInfo (struct tagENUMIDENTDATA *pEID, long lIdent, short iVTyp);
static bool FindHeaderEntry (long lMCode, char *pHdrKey);
static bool OutLine (short fh, char *pOut);

// Liefert ResourceID für ObjekttypString -------------------------------------
unsigned int OTypeIDS (short iVTyp)
{
	switch (iVTyp) {
	case OGPunkt:	return IDS_PHEADER;
	case OGLinie:	return IDS_LHEADER;
	case OGFlaeche:	return IDS_FHEADER;
	case OGLabel:
	case OGText:	return IDS_THEADER;
	case OGUnknown:
	default:
		break;
	}

return IDS_GHEADER;
}


static string TagScopeChars (LPCSTR pcText)
{
string str;

	while ('\0' != *pcText) {
		if ('\"' == *pcText)
			str += '\\';
		str += *pcText;
		pcText++;
	}

return str;
}

extern "C" {

// Enumeration der Sichten der aktuellen GeoDB, eintragen in die ListBox ------
BOOL PASCAL _XTENSN_EXPORT FillViewList (char *pView, BOOL, void *pData)
{
	((MultiSelListBox *)pData) -> AddString (pView);
	return true;
}

// Exportieren der Merkmale einer Sicht ---------------------------------------
typedef struct tagEXPORTVIEWFEATUREDATA {
	short m_iFH;
	char *m_pOutBuff;
	char *m_pInBuff;
	char *m_pView;
	ResourceFile *m_pRF;
	INT_PTR m_lLegMCode;
} EXPORTVIEWFEATUREDATA;

BOOL PASCAL _XTENSN_EXPORT ExportViewFeature (char *pName, BOOL, void *pData)
{
EXPORTVIEWFEATUREDATA *pEVFD = (EXPORTVIEWFEATUREDATA *)pData;

// MerkmalsWert besorgen
NAMEDVIEWPROPERTY NVP;

	INITSTRUCT(NVP, NAMEDVIEWPROPERTY);
	NVP.pcView = pEVFD -> m_pView;
	NVP.pcName = pName;
	NVP.pBuffer = pEVFD -> m_pInBuff;
	NVP.iLen = _MAX_PATH;
	if (FAILED(DEX_GetNamedViewProperty(NVP)))
		return true;		// Fehler, trotzdem weitermachen

// evtl. vorhandene '"' durch '\"' ersetzen
os_string strOut (TagScopeChars (pEVFD -> m_pInBuff));

// versuchen, einen entsprechenden HeaderEintrag zu finden
INT_PTR lMCode = 0;

	if (1 != sscanf (pName, g_cbSysProperty, &lMCode)) {
	// ist nicht "Property MCode"
		if (strncmp (pName, ResString (IDS_OBJVISINFO, 17).Addr(), HDRKEYLENGTH) &&
		    strncmp (pName, ResString (IDS_LEGENDINFOMCODE, 17).Addr(), HDRKEYLENGTH)) 
		{
		// HeaderEintrag ohne Bedeutung für Visualisierung
			wsprintf (pEVFD -> m_pOutBuff, 
				  ResString (ResID (IDS_VIEWFEATURE1, pEVFD -> m_pRF), 40),
				  pName, strOut.c_str());
		} else {
		// Sichtmerkmal besitzt lediglich informativen Charakter
			wsprintf (pEVFD -> m_pOutBuff, 
				  ResString (ResID (IDS_VIEWFEATURECOMM, pEVFD -> m_pRF), 40),
				  pName, strOut.c_str());
		}

	// Info ausgeben
		CharToOem (pEVFD -> m_pOutBuff, pEVFD -> m_pOutBuff);
		if (!OutLine (pEVFD -> m_iFH, pEVFD -> m_pOutBuff))
			return false;
	} 
	else if (lMCode == pEVFD -> m_lLegMCode) {
	// Legenden-Info
	CLegendMCodes MCodes (lMCode, pEVFD -> m_pView);

		if (S_OK == MCodes.ExtractMCodes(strOut.c_str())) {
		// alle gefundenen MCodes durchgehen
			for (CLegendMCodes::iterator it = MCodes.begin(); it != MCodes.end(); ++it) {
				if (ReadTextMerkmal (TT_Sicht, (INT_PTR)pEVFD -> m_pView, *it, pEVFD -> m_pInBuff, _MAX_PATH)) 
				{
				// evtl. vorhandene '"' durch '\"' ersetzen
					strOut = TagScopeChars (pEVFD -> m_pInBuff);

				// LegendenÜberschrift gefunden
#if defined(_DEBUG)
				ResString resLH(ResID (IDS_VIEWLEGENDHEADLINE, pEVFD -> m_pRF), 40);
				ResString resComment(ResID (IDS_VIEWLEGENDHEADLINE_COMMENT, pEVFD -> m_pRF), 40);
				char cbBuffer[_MAX_PATH];

					strcpy (cbBuffer, resLH);
					strcat (cbBuffer, resComment);
					wsprintf (pEVFD -> m_pOutBuff, cbBuffer, strOut.c_str(), *it);
#else
					wsprintf (pEVFD -> m_pOutBuff, 
						ResString(ResID (IDS_VIEWLEGENDHEADLINE, pEVFD -> m_pRF), 40),
						strOut.c_str());
#endif // defined(_DEBUG)

				// diesen Wert ausgeben
					CharToOem (pEVFD -> m_pOutBuff, pEVFD -> m_pOutBuff);
					if (!OutLine (pEVFD -> m_iFH, pEVFD -> m_pOutBuff))
						return false;
				}
			}
		}
	} 
	else if (-1 != pEVFD -> m_lLegMCode) {
	// nichts gefunden, aber objektbezogene Visualisierung existiert für diese Ansicht
	CLegendMCodes MCodes (pEVFD -> m_lLegMCode, pEVFD -> m_pView);
	
		if (S_OK != MCodes.ExtractMCodes() || !MCodes.HasMCode(lMCode)) {
			wsprintf (pEVFD -> m_pOutBuff, 
				  ResString (ResID (IDS_VIEWFEATURECOMM2, pEVFD -> m_pRF), 40),
				  lMCode, strOut.c_str());

		// diese Info ausgeben
			CharToOem (pEVFD -> m_pOutBuff, pEVFD -> m_pOutBuff);
			if (!OutLine (pEVFD -> m_iFH, pEVFD -> m_pOutBuff))
				return false;
		}
	}
	return true;
}


// Finden eines HeaderEintrages, der ein vogegebenes String als Text enthält --
typedef struct tagENUMHDRDATA {
	char *m_chMCode;
	char *m_pHdrKey;
} ENUMHDRDATA;

BOOL PASCAL _XTENSN_EXPORT CmpHeaderEntry (char *pHdrKey, BOOL, void *pData)
{
ENUMHDRDATA *pEHD = (ENUMHDRDATA *)pData;
HeaderEntryX HE (pHdrKey);

	if (HE.Status() != HE_INVALID && !strcmp (HE.EntryText(), pEHD -> m_chMCode)) {
		memset (pEHD -> m_pHdrKey, ' ', HDRKEYLENGTH);
		memcpy (pEHD -> m_pHdrKey, HE.EntryKey(), strlen (HE.EntryKey()));
		pEHD -> m_pHdrKey[HDRKEYLENGTH+1] = '\0';
		return false;		// gefunden: Ende der Vorstellung
	}
	
return true;	// weitermachen
}

///////////////////////////////////////////////////////////////////////////////
// Übergeordnetes Objekt eines Textes suchen 

extern "C" 
BOOL PASCAL _XTENSN_EXPORT MasterObject (long lONr, long, short iRTyp, void *pData)
{
	if (iRTyp == RTBegleitU) {
		*(long *)pData = lONr;		// BezugsObjekt gefunden
		return false;		// Enumeration abbrechen
	}
	return true;	// weitermachen
}

long AssocObject (long lTONr)
{
ENUMRELATIONOBJS ERO;
long lBONr = -1L;

	INITSTRUCT (ERO, ENUMRELATIONOBJS);
	ERO.lONr = lTONr;	// TextObjekt
	ERO.lRCode = -1L;	// kein RCode
	ERO.iRTyp = RTBegleitU;	// es wird BezugsObjekt gesucht
	ERO.eFcn = (ENUMRELOBJPROC)MasterObject;
	ERO.pData = &lBONr;
	DEX_EnumRelationObjects (ERO);
	return lBONr;
}

///////////////////////////////////////////////////////////////////////////////
// Ausgabe der VisInfo für ein visualisiertes Objekt 
typedef struct tagENUMOBJECTDATA {
	short m_iFH;
	bool m_fRGB;
	ResourceFile *m_pRF;
	char *m_chStr;
	const char *m_pView;
	const char *m_chFName;
	long m_lIdent;
	long m_lUIMCode;
	long m_lVisObjMCode;
	long m_lLegMCode;
	class CStatus *m_pStatus;
} ENUMOBJECTDATA;

inline 
char *MakeUIdent (char *cbBuffer, long lONr, long lMCode, const char *pFName)
{
	if (lMCode == -1 || !ReadTextMerkmal (TT_Objekt, lONr, lMCode, cbBuffer))
	{
	// kein UIdent gegeben, selbigen generieren
		wsprintf (cbBuffer, "%s_%ld", pFName, lONr);
	}
	return cbBuffer;
}

BOOL PASCAL _XTENSN_EXPORT ExportViewObject (long lONr, BOOL, void *pData)
{
ENUMOBJECTDATA *pEOD = (ENUMOBJECTDATA *)pData;

	if (pEOD -> m_lIdent != DEX_GetObjIdent(lONr))
		return TRUE;		// not here

// wirklich exportieren
char *cbModuleInfo[2];

	cbModuleInfo[0] = cbModuleInfo[1] = NULL;

HANDLEVISINFO *pHVI = GetObjectVisInfo (lONr, (char *)pEOD -> m_pView, 
					pEOD -> m_lVisObjMCode, 
					cbModuleInfo, DF_Export|DF_Analyze);

	if (pHVI != NULL) {
		memset (pEOD -> m_chStr, '\0', _MAX_PATH);

	short iOTyp = DEX_GetObjectType (lONr);
	long lBONr = lONr;

		if (iOTyp == OGText || iOTyp == OGLabel) {	// Texte erhalten UIdent vom BeszugsObjekt
			lBONr = AssocObject (lONr);
			if (lBONr == -1L) 
				lBONr = lONr;	// kein abhängiges Objekt
			else
				*(pEOD -> m_chStr) = '$';	// UIdent modifizieren
		}
		MakeUIdent (EOS(pEOD -> m_chStr), lBONr, pEOD -> m_lUIMCode, pEOD -> m_chFName);
				
	// in Statusfenster anzeigen
		if (NULL != pEOD -> m_pStatus) {
			pEOD -> m_pStatus -> SetHandledItem (pEOD -> m_chStr, true);
			if (pEOD -> m_pStatus -> Break())
				return false;
		}

	// in AnführungsStriche einbetten
		memmove (pEOD -> m_chStr +1, pEOD -> m_chStr, strlen (pEOD -> m_chStr));
		*(pEOD -> m_chStr) = '\"';
		strcat (pEOD -> m_chStr, "\"");
		
	// Wenn gefordert, dann LegendenInfo mit exportieren.
	// An dieser Stelle wird die LegendenInfo ausgegeben, wenn ein Objekt
	// objektbezogen visualisiert ist UND in der Legende enthalten ist.
	// Ist ein Objekt nur in der Legende enthalten, aber nicht objektbezogen
	// visualisiert, dann erfolgt der Export an anderer Stelle.
	char *pLegInfo = NULL;
		
		if (pEOD -> m_lLegMCode != -1L) {
			pLegInfo = new char [5*_MAX_PATH];
			if (pLegInfo) {
				*pLegInfo = '\0';
				if (!ReadTextMerkmal (TT_Objekt, 
						      lONr, pEOD -> m_lLegMCode,
						      pLegInfo, 5*_MAX_PATH))
				{	// Merkmal existiert nicht
					DELETE_OBJ (pLegInfo);
				}
			}
		}
	
	char *pStr = VisInfoToString (pHVI, false, pEOD -> m_pRF, 
				      pEOD -> m_fRGB, pEOD -> m_chStr, true,
				      cbModuleInfo, pLegInfo);
		if (pStr) {
			OutLine (pEOD -> m_iFH, pStr);
			delete pStr;
		}
		DELETE_OBJ (pHVI -> m_pVI);
		delete pHVI;
		DELETE_OBJ (pLegInfo);
	}
	DELETE_OBJ (cbModuleInfo[0]);
	DELETE_OBJ (cbModuleInfo[1]);
		
return true;
}

///////////////////////////////////////////////////////////////////////////////
// Ausgabe der VisInfo für einen Identifikator einer Sicht 
typedef struct tagENUMIDENTDATA {
	short m_iFH;
	bool m_fRGB;
	ResourceFile *m_pRF;
	char *m_chStr;
	char *m_pView;
	short m_iIdBase;
	class CStatus *m_pStatus;
	long m_lLegMCode;
	bool m_fwasLegInfo;			// LegInfo nur beim ersten ausgeben
	bool m_fOVis;				// objektbezogene Vis exportieren
	const char *m_pcFName;		// FileBaseName für UIdent
} ENUMIDENTDATA;

BOOL PASCAL _XTENSN_EXPORT ExportViewIdent (long lIdent, BOOL, void *pData)
{
ENUMIDENTDATA *pEID = (ENUMIDENTDATA *)pData;

// Abbrechen abfragen
	if (pEID -> m_pStatus -> Break())
		return false;

// VisInfo besorgen und exportieren
	ExportVisInfo (pEID, lIdent, VTPunkt);
	ExportVisInfo (pEID, lIdent, VTLinie);
	ExportVisInfo (pEID, lIdent, VTFlaeche);
	ExportVisInfo (pEID, lIdent, VTText);
	ExportVisInfo (pEID, lIdent, VTDefault);
	
	pEID -> m_pStatus -> SetDeltaPos (1);
	pEID -> m_fwasLegInfo = false;

// jetzt noch die zu diesem Ident gehörenden Objekte (OVis) exportieren
// Objektbezogene Visualisierung schreiben
long lUIMCode = DEX_GetUniqueIdentMCodeEx (DEX_GetObjectsProject(lIdent));
long lVisObjMCode = -1L;

	if (pEID -> m_fOVis) {
		lVisObjMCode = ((CVisObjExtension *)g_pTE) -> GetObjMCode (false, pEID -> m_pView, lIdent); 

		if (lVisObjMCode != -1) {	// Objekte vorhanden
		ENUMRECHTEXTMERKMAL ERTM;
		ENUMOBJECTDATA EOD;
		char cbOutBuff[_MAX_PATH];

			EOD.m_iFH = pEID -> m_iFH;
			EOD.m_fRGB = pEID -> m_fRGB;
			EOD.m_pRF = pEID -> m_pRF;
			EOD.m_chStr = cbOutBuff;
			EOD.m_pView = pEID -> m_pView;
			EOD.m_chFName = pEID -> m_pcFName;
			EOD.m_lIdent = lIdent;
			EOD.m_lUIMCode= lUIMCode;
			EOD.m_lVisObjMCode = lVisObjMCode;
			EOD.m_lLegMCode = pEID -> m_lLegMCode;
			EOD.m_pStatus = pEID -> m_pStatus;

			INITSTRUCT(ERTM, ENUMRECHTEXTMERKMAL);
			ERTM.pView = pEID -> m_pView;
			ERTM.lMCode = lVisObjMCode;
			ERTM.eFcn = ExportViewObject;
			ERTM.pData = &EOD;
			DEX_EnumRechTextMerkmal (ERTM);
		}
	}
	return true;
}


BOOL PASCAL _XTENSN_EXPORT CountViewIdents (long, BOOL, void *pData)
{
	( *(int *)pData )++;	// nur zählen
	return true;	// immer weitermachen
}


// Funktion, welche für jedes Objekt in der Legende gerufen wird. Sie darf nur
// dann die Information schreiben, wenn das Objekt NICHT objektbezogen 
// visualisiert ist.
BOOL PASCAL _XTENSN_EXPORT ExportViewObjectLegend (long lONr, BOOL, void *pData)
{
ENUMOBJECTDATA *pEOD = (ENUMOBJECTDATA *)pData;

// Testen, ob dieses Objekt bereitsexportiert wurde
	if (pEOD -> m_lVisObjMCode != -1L &&
	    ReadTextMerkmal (TT_Objekt, lONr, pEOD -> m_lVisObjMCode, pEOD -> m_chStr))
		return true;	// ist objektbezogen visualisiert
		
// Unique Ident generieren
	memset (pEOD -> m_chStr, '\0', _MAX_PATH);
	MakeUIdent (pEOD -> m_chStr, lONr, pEOD -> m_lUIMCode, pEOD -> m_chFName);

/*	if (pEOD -> m_lUIMCode == -1 || 
	    !ReadTextMerkmal (TT_Objekt, lONr, pEOD -> m_lUIMCode, pEOD -> m_chStr))
	{
	// kein UIdent gegeben, selbigen generieren
		wsprintf (pEOD -> m_chStr, "%s_%ld", pEOD -> m_chFName, lONr);
	}
*/
// in Statusfenster anzeigen
	if (NULL != pEOD -> m_pStatus) {
		pEOD -> m_pStatus -> SetHandledItem (pEOD -> m_chStr, true);
		if (pEOD -> m_pStatus -> Break())
			return false;
	}

// in AnführungsStriche einbetten
	memmove (pEOD -> m_chStr +1, pEOD -> m_chStr, strlen (pEOD -> m_chStr));
	*(pEOD -> m_chStr) = '\"';
	strcat (pEOD -> m_chStr, "\"");

// LegendeInfo besorgen
char *pLegInfo = NULL;
		
	if (pEOD -> m_lLegMCode != -1L) {
		pLegInfo = new char [5*_MAX_PATH];
		if (pLegInfo) {
			*pLegInfo = '\0';
			if (!ReadTextMerkmal (TT_Objekt, lONr, pEOD -> m_lLegMCode, pLegInfo, 5*_MAX_PATH))
			{	// Merkmal existiert nicht
				DELETE_OBJ (pLegInfo);
			}
		}
	}

short iOTyp = DEX_GetObjectType (lONr);

	if (pLegInfo) {		// LegendenInfo gegeben
	char *pStr = new char [_MAX_PATH];
	
		if (pStr) {	// c %s {
			wsprintf (pStr, ResString (ResID (OTypeIDS (iOTyp), pEOD -> m_pRF), 13), 
					pEOD -> m_chStr);
#if defined(_DEBUG)
		ResString resLG(ResID (IDS_OBJLEGENDINFOFORMAT, pEOD -> m_pRF), 20);
		ResString resComment(ResID (IDS_VIEWLEGENDHEADLINE_COMMENT, pEOD -> m_pRF), 40);
		char cbBuffer[_MAX_PATH];

			strcpy (cbBuffer, resLG);
			strcat (cbBuffer, resComment);
			wsprintf (EOS(pStr), cbBuffer, pLegInfo, pEOD -> m_lLegMCode);		// lg=%s }
#else
			wsprintf (EOS(pStr), // lg=%s }
				  ResString (ResID (IDS_OBJLEGENDINFOFORMAT, pEOD -> m_pRF), 20), 
				  pLegInfo);
#endif // defined(_DEBUG)

			OutLine (pEOD -> m_iFH, pStr);
			delete pStr;
		}
		delete pLegInfo;
	}
	return true;
}


// HookFunktion für den SaveAsDialog ------------------------------------------
#if !defined(WIN32)
bool _XTENSN_EXPORT CALLBACK VisASCExportHookFcn (HWND hDlg, UINT wMsg, WPARAM, LPARAM)
{
	if (wMsg == WM_INITDIALOG && Ctl3dEnabled()) 
		Ctl3dSubclassDlg (hDlg, CTL3D_ALL);	// lediglich CTL3D aktivieren

return false;
}
#endif // WIN32

}	//extern "C" 


// Exportieren einer VisInfo für einen IdentGeoTyp ----------------------------	
static 
void ExportVisInfo (ENUMIDENTDATA *pEID, long lIdent, short iVTyp)
{
HANDLEVISINFO *pHVI = GetIdentVisInfo (lIdent, iVTyp, pEID -> m_pView);

	if (pHVI != NULL) {	// VisInfo existiert, also ausgeben
		if (iVTyp != VTDefault ||
		    ((DVISINFO *)pHVI -> m_pVI) -> m_iDefTypes != 0) 
		{
		char cbBuffer[MAX_OKS_LENX];

			if (S_OK == ClassFromIdentX (lIdent, cbBuffer)) {
			// ObjektKlassenSchlüssel ist vorhanden
			ResString resOKS (ResID (IDS_OKS, pEID -> m_pRF), 32);

				wsprintf (pEID -> m_chStr, resOKS, cbBuffer);
			} else {
				if (10 == DEX_GetIdBase())
					strcpy (pEID -> m_chStr, cbBuffer);		// ist Ident
				else {
					strcpy (pEID -> m_chStr, "0x");
					strcat (pEID -> m_chStr, cbBuffer);		// ist Ident
				}
			}

			if (NULL != pEID -> m_pStatus)
				pEID -> m_pStatus -> SetHandledItem (pEID -> m_chStr);

		char *pLegInfo = NULL;
		
			if (pEID -> m_lLegMCode != -1L && !pEID -> m_fwasLegInfo) {
				pLegInfo = new char [5*_MAX_PATH];
				if (pLegInfo) {
					*pLegInfo = '\0';
					if (!ReadTextMerkmal (TT_Identifikator, lIdent, pEID -> m_lLegMCode, pLegInfo, 5*_MAX_PATH, pEID -> m_pView))
					{	// Merkmal existiert nicht
						DELETE_OBJ (pLegInfo);
					} else
						pEID -> m_fwasLegInfo = true;
				}
			}
		
		IDENTSCALEDATA ISD;

			INITSTRUCT(ISD, IDENTSCALEDATA);
			ISD.pcView = pEID -> m_pView;
			ISD.lIdent = lIdent;
			ISD.iVTyp = iVTyp;
			DEX_GetIdentScaleData(ISD);

		char *pStr = VisInfoToString (pHVI, true, pEID -> m_pRF, 
					      pEID -> m_fRGB, pEID -> m_chStr, 
					      true, NULL, pLegInfo, ISD.lUpperScale, ISD.lLowerScale);

#if defined(_DEBUG)
			if (pStr) {
			char cbOutBuff[_MAX_PATH];

				wsprintf (cbOutBuff, "%s//\t %ld", pStr, pEID -> m_lLegMCode);
				OutLine (pEID -> m_iFH, cbOutBuff);
				delete pStr;
			}
#else
			if (pStr) {
				OutLine (pEID -> m_iFH, pStr);
				delete pStr;
			}
#endif // defined(_DEBUG)
			dtHANDLEVISINFO (pHVI);
			DELETE_OBJ (pLegInfo);
		}
	}
}

// Finden des HeaderEintrages, der den gegebenen MCode enthält ----------------
static bool FindHeaderEntry (long lMCode, char *pHdrKey)
{
// Enumeration der HeaderEinträge und suchen des MCodes als Text
char chMCode[20];
ENUMNOKEY ENK;
ENUMHDRDATA EHD;

	EHD.m_chMCode = chMCode;
	EHD.m_pHdrKey = pHdrKey;
	
	ltoa (lMCode, chMCode, 10);	// MCode als String vergleichen
	ENK.eFcn = (ENUMNOKEYPROC)CmpHeaderEntry;
	ENK.ePtr = (void *)&EHD;
		
	memset (pHdrKey, '\0', HDRKEYLENGTH);
#if !defined(DEX_EnumHdrEntries)
	DEX_EnumHeaderEntries(ENK);
#else
	DEX_EnumHdrEntries (ENK);
#endif // DEX_EnumHdrEntries

	return *pHdrKey != '\0';	// was gefunden oder nicht
}


// Dialogfenster zur Abfrage der ExportOptionen -------------------------------
#pragma warning (disable: 4355)
CExportVisInfoDlg *CExportVisInfoDlg::CreateInstance (
			pWindow pW, ResourceFile *pRF, long lVMCode, long lLMCode)
{
CExportVisInfoDlg *pDlg = new CExportVisInfoDlg (pW, pRF, lVMCode, lLMCode);

	if (pDlg == NULL || !pDlg -> Init()) {
		DELETE_OBJ (pDlg);
		return NULL;
	}

return pDlg;
}


CExportVisInfoDlg::CExportVisInfoDlg (pWindow pW, ResourceFile *pRF, 
					long lVMCode, long lLMCode)
		   : DialogWindow (pW, ResID (EXPORTVISINFODLG, pRF)),
		     m_pbFName (this, IDB_EXPORTFILESELECT),
		     m_mslbViews (this, IDL_EXPORTVIEWS),
		     m_sleFName (this, IDE_EXPORTFILENAME),
		     m_pbOK (this, IDOK),
		     m_pbSelectAll (this, IDB_SELECTALLVIEWS),
		     m_rbRGB (this, IDR_EXPORTRGB),
		     m_rbHSB (this, IDR_EXPORTHSB),
		     m_cbDefaultView (this, IDCB_DEFAULTVIEW),
		     m_cbObjVisInfo (this, IDCB_OBJVISINFO),
		     m_cbViewFeatures (this, IDCB_VIEWFEATURES),
		     m_cbLegendInfo (this, IDCB_LEGENDFEATURES),
		     m_rRF (*pRF),
		     m_lSichtMCode (lVMCode),
		     m_lSichtLegMCode (lLMCode)
{
	m_pbOK.Disable();
	m_pbSelectAll.Disable();

	m_rbRGB.SetState (true);
	m_rbHSB.SetState (false);
	
	m_cbDefaultView.SetChecked (true);
	m_cbObjVisInfo.SetChecked (true);
	m_cbViewFeatures.SetChecked (true);
	m_cbLegendInfo.SetChecked (true);
		
	m_pBuff = NULL;
	m_pOutBuff = NULL;
	m_pInBuff = NULL;
	
	m_cnIdents = 0;
	m_iIdBase = DEX_GetIdBase();
	
	m_pStatus = NULL;
}

#pragma warning (default: 4355)

bool CExportVisInfoDlg::Init (void)
{
// temporären Buffer anlegen
	m_pBuff = new char [_MAX_PATH];
	if (m_pBuff == NULL) 
		return false;
		
	m_pOutBuff = new char [_MAX_PATH];
	if (m_pOutBuff == NULL) 
		return false;
		
	m_pInBuff = new char [_MAX_PATH];
	if (m_pInBuff == NULL) 
		return false;

// Sichten enumerieren und in Listbox eintragen
ENUMNOKEY ENK;

	ENK.eFcn = (ENUMNOKEYPROC)FillViewList;
	ENK.ePtr = (void *)&m_mslbViews;

bool iResult = (bool)DEX_EnumSights (ENK);

	if (m_mslbViews.GetCount() > 0)
		m_pbSelectAll.Enable();
		
return iResult;
}


CExportVisInfoDlg::~CExportVisInfoDlg (void)
{
// Speicher freigeben	
	DELETE_OBJ (m_pBuff);
	DELETE_OBJ (m_pInBuff);
	DELETE_OBJ (m_pOutBuff);
}


void _XTENSN_EXPORT CExportVisInfoDlg::ButtonClick (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDOK:
		{
		CEierUhr Wait (GetParent());
		
			EndDlg (ExportSelectedViews ());
		}
		break;
		
	case IDCANCEL:
		EndDlg (false);
		break;
		
	case IDB_EXPORTFILESELECT:
		SelectExportFileName();
		break;

	case IDB_SELECTALLVIEWS:
		{
		short iCnt = m_mslbViews.GetCount();
		
			if (iCnt > 0) {
				m_mslbViews.ChangeSelected (Range (0, iCnt), true);
				m_cnIdents = CountAllIdents();
				if (m_sleFName.GetTextLen() > 0)
					m_pbOK.Enable();
			}
		}
		break;
	}
}

void _XTENSN_EXPORT CExportVisInfoDlg::EditChange (ControlEvt)
{
	if (m_sleFName.GetTextLen() > 0 && m_mslbViews.GetNoSelected() > 0)
		m_pbOK.Enable();
	else
		m_pbOK.Disable();
}


void _XTENSN_EXPORT CExportVisInfoDlg::ListBoxSel (ControlEvt)
{
// OK-Knopf richten
	if (m_sleFName.GetTextLen() > 0 && m_mslbViews.GetNoSelected() > 0)
		m_pbOK.Enable();
	else
		m_pbOK.Disable();
		
// Anzahl der zu exportierenden Identifikatoren aufsammeln
	m_cnIdents = CountAllIdents();
}


int CExportVisInfoDlg::CountAllIdents (void)
{
short iIndex = m_mslbViews.GetFirstSelected();
int iCnt = 0;

	while (iIndex != -1) {
	// SichtNamen einlesen, VisInfo ausgeben
		m_mslbViews.GetString (m_pBuff, iIndex, _MAX_PATH);
		iCnt += CountIdents (m_pBuff);
		
	// nächste Sicht besorgen
		iIndex = m_mslbViews.GetNextSelected();
	}	
	return iCnt;
}


bool CExportVisInfoDlg::ExportSelectedViews (void)
{
// AusgabeDatei erzeugen und eröffnen
	m_sleFName.GetText (m_pBuff, _MAX_PATH);

OFSTRUCT of;
short fh = OpenFile (m_pBuff, &of, OF_WRITE|OF_CREATE);

	if (fh == HFILE_ERROR) return false;
	
// Anfangskommentar ausgeben
os_string resVersion ("// ");
os_time_and_date now;

	TX_TRY(now = os_time_and_date::now());
	resVersion += g_cbTRiAS;
	resVersion += " ";
	resVersion += FakeTRiASName (IDS_SIGNONVERSION_MODAL);
	resVersion += now.to_string(ResString(ResID(IDS_EXPORTTIMEFORMAT, &m_rRF), 32));

	CharToOem (resVersion.c_str(), m_pOutBuff);
	OutLine (fh, m_pOutBuff);		// Kommentar ausgeben

// Identifikatoren in der DefaultSicht zählen, wenn diese ausgebeben werden soll
	if (m_cbDefaultView.isChecked()) 
		m_cnIdents += CountIdents (NULL);
	
	m_sleFName.GetText (m_pBuff, _MAX_PATH);

// Statusanzeige generieren
	ATLTRY(m_pStatus = new CStatus (this, m_cnIdents, &m_rRF, DEX_GetIdBase()));
	if (m_pStatus) {
		m_pStatus -> SetCaption (ResString (ResID (IDS_EXPORTCAPTION, &m_rRF), 30));
		m_pStatus -> SetComment ((char *)ResString (ResID (IDS_EXPORTCOMMENT, &m_rRF), 50).Addr());
		m_pStatus -> Show();
	}
	
// DefaultVisInfo ausgeben
bool fRGB = m_rbRGB.GetState();

	if (m_cbDefaultView.isChecked() && !ExportView (fh, NULL, fRGB)) {
		_lclose (fh);
		unlink (of.szPathName);		// Datei löschen
		DELETE_OBJ (m_pStatus);
		return false;
	}
	
// Legende speichern, wenn notwendig
bool fLegendInfo = m_cbLegendInfo.isChecked();

	if (fLegendInfo) DEX_SaveLegend();
	
// VisInfo ausgeben
short iIndex = m_mslbViews.GetFirstSelected();
bool fObjVis = m_cbObjVisInfo.isChecked();
bool fFeatures = m_cbViewFeatures.isChecked();

	while (iIndex != -1) {
	// SichtNamen einlesen, VisInfo ausgeben
		m_mslbViews.GetString (m_pBuff, iIndex, _MAX_PATH);
		if (!ExportView (fh, m_pBuff, fRGB, fFeatures, fObjVis, fLegendInfo)) {
			_lclose (fh);
			unlink (of.szPathName);		// Datei löschen
			DELETE_OBJ (m_pStatus);
			return false;
		}
		
	// nächste Sicht besorgen
		iIndex = m_mslbViews.GetNextSelected();
	}	

	DELETE_OBJ (m_pStatus);
	_lclose (fh);
	return true;
}


static bool OutLine (short fh, char *pOut)
{
	strcat (pOut, "\r\n");		// newline anhängen
	
short iLen = strlen (pOut);

	return (_lwrite (fh, pOut, iLen) == (UINT)iLen);
}

string CorrectViewName (LPCSTR pcView)
{
	if (NULL == pcView) return string("");

string str (pcView);
size_t pos = str.find ('\"');

	while (NPOS != pos) {
		str.replace (pos, 1, "\\\"");
		pos = str.find ('\"', pos+2);
	}
	return str;
}

bool CExportVisInfoDlg::ExportView (short fh, char *pView, 
				      bool fRGB, bool fFeatures, 
				      bool fOVis, bool fLegInfo)
{
// SichtHeader (SichtNamen)
	if (pView) {
	string strView = CorrectViewName(pView);

#if defined(DEX_GetDefaultView)
	char cbBuffer[_MAX_PATH];

		if (DEX_GetDefaultView(cbBuffer) && !strcmp(cbBuffer, pView))
			wsprintf (m_pOutBuff, ResString (ResID (IDS_STARTVIEWHEADER, &m_rRF), 15), strView.c_str());
		else
#endif // DEX_GetDefaultView
			wsprintf (m_pOutBuff, ResString (ResID (IDS_VIEWHEADER, &m_rRF), 15), strView.c_str());
		AnsiToOem (m_pOutBuff, m_pOutBuff);
	} else
		strcpy (m_pOutBuff, ResString (ResID (IDS_DEFVIEWHEADER, &m_rRF), 15));
	if (!OutLine (fh, m_pOutBuff)) 
		return false;

// anzuzeigende Objekteigenschaft schreiben
ResString rsDefault (ResID (IDS_DEFAULTVIEW, &m_rRF), 40);
char *pLocView = pView ? pView : (char *)rsDefault.Addr();
//SHOWOBJPROPEX SOP;
//
//	INITSTRUCT(SOP, SHOWOBJPROPEX);
//	SOP.pcView = pLocView;
//	SOP.pObjProp = m_pInBuff;
//	SOP.iLen = _MAX_PATH;
//
//	if (SUCCEEDED(DEX_GetActObjPropEx(SOP))) {
//		if ('\0' != m_pInBuff[0])
//			wsprintf (m_pOutBuff, ResString (ResID (IDS_OBJPROPTOSHOW, &m_rRF), 32), SOP.iFlags, m_pInBuff);
//		else
//			wsprintf (m_pOutBuff, ResString (ResID (IDS_OBJPROPTOSHOW2, &m_rRF), 32), SOP.iFlags);
//
//		if (!OutLine (fh, m_pOutBuff)) 
//			return false;
//	}

// Sichtmerkmale schreiben
ENUMTEXTKEY ETK;

// in StatusFenster Sichtnamen anzeigen
	if (m_pStatus) m_pStatus -> SetViewName (pLocView);
	
	if (fFeatures) {
	EXPORTVIEWFEATUREDATA EVFD;
	ErrInstall EI (WC_NOMERKMAL);
	
		EVFD.m_iFH = fh;
		EVFD.m_pOutBuff = m_pOutBuff;
		EVFD.m_pInBuff = m_pInBuff;
		EVFD.m_pRF = &m_rRF;
		EVFD.m_pView = pLocView;
		EVFD.m_lLegMCode = GetObjMCodeView (pLocView, m_lSichtLegMCode);
				
		ETK.eKey = pLocView;
		ETK.eFcn = (ENUMTEXTKEYPROC)ExportViewFeature;
		ETK.ePtr = &EVFD;
		DEX_EnumSichtMerkmale (ETK);
	}
		
// Identifikatoren schreiben
long lObjLegMCode = GetObjMCodeView (pLocView, m_lSichtLegMCode, 
			ResID (IDS_LEGINFOKTEXT, &m_rRF), 
			ResID (IDS_LEGINFOLTEXT, &m_rRF), false);
	
	m_sleFName.GetText (m_pOutBuff, _MAX_PATH);
	_splitpath (m_pOutBuff, NULL, NULL, m_pInBuff, NULL);
			
	{
	ENUMIDENTDATA EID;

		EID.m_iFH = fh;
		EID.m_fRGB = fRGB;
		EID.m_pRF = &m_rRF;
		EID.m_iIdBase = m_iIdBase;
		EID.m_chStr = m_pOutBuff;
		EID.m_pView = pLocView;
		EID.m_pStatus = m_pStatus;
		EID.m_lLegMCode = fLegInfo ? lObjLegMCode : -1L;
		EID.m_fwasLegInfo = false;
		EID.m_fOVis = fOVis;
		EID.m_pcFName = m_pInBuff;
					
		ETK.eKey = pLocView;
		ETK.eFcn = (ENUMTEXTKEYPROC)ExportViewIdent;
		ETK.ePtr = &EID;
		if (!DEX_EnumSightIdents (ETK))
			return false;
	}
				
//// Objektbezogene Visualisierung schreiben
long lUIMCode = -1L;
long lVisObjMCode = -1L;
//
//	m_sleFName.GetText (m_pOutBuff, _MAX_PATH);
//	_splitpath (m_pOutBuff, NULL, NULL, m_pInBuff, NULL);
//			
//	if (fOVis && m_lSichtMCode != -1) {
//		lVisObjMCode = GetObjMCodeView (pLocView, m_lSichtMCode, 
//				ResID (IDS_PBDKURZTEXT, &m_rRF), 
//				ResID (IDS_PBDLANGTEXT, &m_rRF), false);
//		if (lVisObjMCode != -1) {	// Objekte vorhanden
//		ENUMRECHTEXTMERKMAL ERTM;
//		ENUMOBJECTDATA EOD;
//		
//			EOD.m_iFH = fh;
//			EOD.m_fRGB = fRGB;
//			EOD.m_pRF = &m_rRF;
//			EOD.m_chStr = m_pOutBuff;
//			EOD.m_pView = pLocView;
//			EOD.m_chFName = strupr(m_pInBuff);
//			EOD.m_lUIMCode= lUIMCode;
//			EOD.m_lVisObjMCode = lVisObjMCode;
//			EOD.m_lLegMCode = fLegInfo ? lObjLegMCode : -1L;
//			EOD.m_pStatus = m_pStatus;
//
//			memset (&ERTM, '\0', sizeof(ENUMRECHTEXTMERKMAL));
//			ERTM.dwSize = sizeof(ENUMRECHTEXTMERKMAL);
//			ERTM.pView = pLocView;
//			ERTM.lMCode = lVisObjMCode;
//			ERTM.eFcn = ExportViewObject;
//			ERTM.pData = &EOD;
//			DEX_EnumRechTextMerkmal (ERTM);
//		}
//	}
//
// LegendeInfo für Objekte schreiben, die nicht objektbezogen visualisiert sind.
	if (fLegInfo && m_lSichtLegMCode != -1 && lObjLegMCode != -1L) {
	ENUMRECHTEXTMERKMAL ERTM;
	ENUMOBJECTDATA EOD;
		
		if (-1L == lVisObjMCode) {
			lVisObjMCode = GetObjMCodeView (pLocView, m_lSichtMCode, 
					ResID (IDS_PBDKURZTEXT, &m_rRF), 
					ResID (IDS_PBDLANGTEXT, &m_rRF), false);
		}
		m_sleFName.GetText (m_pOutBuff, _MAX_PATH);
		_splitpath (m_pOutBuff, NULL, NULL, m_pInBuff, NULL);
			
		EOD.m_iFH = fh;
		EOD.m_fRGB = false;		// nicht benötigt
		EOD.m_pRF = &m_rRF;
		EOD.m_chStr = m_pOutBuff;
		EOD.m_pView = pLocView;
		EOD.m_chFName = strupr(m_pInBuff);
		EOD.m_lUIMCode= lUIMCode;
		EOD.m_lVisObjMCode = lVisObjMCode;
		EOD.m_lLegMCode = lObjLegMCode;
		EOD.m_pStatus = m_pStatus;

		memset (&ERTM, '\0', sizeof(ENUMRECHTEXTMERKMAL));
		ERTM.dwSize = sizeof(ENUMRECHTEXTMERKMAL);
		ERTM.pView = pLocView;
		ERTM.lMCode = lObjLegMCode;
		ERTM.eFcn = ExportViewObjectLegend;
		ERTM.pData = &EOD;
		DEX_EnumRechTextMerkmal (ERTM);
	}
	
// Ende der Vorstellung
	wsprintf (m_pOutBuff, ResString (ResID (IDS_TRAILER, &m_rRF), 10), pView);
	return OutLine (fh, m_pOutBuff);
}


// Zählen der Identifikatoren einer Sicht -------------------------------------
int CExportVisInfoDlg::CountIdents (char *pView)
{
int iCnt = 0;
ENUMTEXTKEY ETK;
ResString rsDefault (ResID (IDS_DEFAULTVIEW, &m_rRF), 40);
char *pLocView = pView ? pView : (char *)rsDefault.Addr();

	ETK.eKey = pLocView;
	ETK.eFcn = (ENUMTEXTKEYPROC)CountViewIdents;
	ETK.ePtr = &iCnt;
	DEX_EnumSightIdents (ETK);
	return iCnt;
}

// Abfrage des AusgabeNamens für die ExportDatei ------------------------------
bool CExportVisInfoDlg::SelectExportFileName (void)
{
char *pLocDir = new char [_MAX_PATH];
char *pPath = new char [_MAX_PATH];
char *pFName = new char [_MAX_PATH];
char cDrive[_MAX_DRIVE];

	if (DEX_GetActiveProject (pLocDir) == NULL) {
		DELETE_OBJ (pLocDir);
		DELETE_OBJ (pPath);
		return false;
	}
	_splitpath (pLocDir, cDrive, pPath, pFName, NULL);
	if (pFName) {	
		strcat (pFName, ResString (ResID (IDS_VISASCEXTENSION, &m_rRF), 7));
		strlwr (pFName);
	}
	_makepath (pLocDir, cDrive, pPath, NULL, NULL);
	DELETE_OBJ (pPath);

// abschließendes '\\' entfernen
char *cptr;

	if (*(cptr = &pLocDir[strlen(pLocDir)-1]) == '\\')
		*cptr = '\0';

// AusgabeDateiNamen abfragen
CSaveAsDialog SDlg (this, (char *)(const char *)ResString (
			ResID (IDS_VISASCTEMPLATE, &m_rRF), 50)
		  );

	SDlg.SetInitialDir (pLocDir);
	SDlg.SetFileName (pFName);
	SDlg.SetCaption (ResString (ResID (IDS_SAVEVISCAP, &m_rRF), 128));
#if !defined(WIN32)
	SDlg.SetHookFcn ((HOOKFCN)VisASCExportHookFcn);
#else
	if (IsWin40()) SDlg.AddFlags (OFN_LONGNAMES);
#endif
	SDlg.AddFlags (OFN_OVERWRITEPROMPT|OFN_NOCHANGEDIR);

	if (!SDlg.Show()) {
		DELETE_OBJ (pFName);
		DELETE_OBJ (pLocDir);
		return false;
	}
	DELETE_OBJ (pLocDir);
	DELETE_OBJ (pFName);

// Eingegebenen DateiNamen lesen und im EditControl ablegen
	if (SDlg.Result()) {
		SDlg.GetFileName (m_pBuff, _MAX_PATH);
		m_sleFName.SetText (m_pBuff);
	}

return true;
}


