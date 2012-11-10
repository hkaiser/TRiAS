// Abaendern von Visualisierungsinformationen fuer einzelne Objekte -----------
// File: CHANGEVI.CXX

#include "visobjp.hxx"

#include <stdio.h>			// sscanf
#include <bmpbox.hxx>
#include <rgb_hsb.hxx>
#include <objcontx.hxx>
#include <viserror.hxx>

#include "visobj.h"			// ResourceKonstanten für dieses Beispiel
#include "defabout.h"
#include "viserrdg.h"
#include "resource.h"

#include "visobj.hxx"		// Klasse für diese Erweiterung
#include "viserrdg.hxx"

#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// externe Dateien
short OTypToBits (short iOTyp);

///////////////////////////////////////////////////////////////////////////////
// für aktuell selektierte/aktiviertes Objekt(e) VisInfo neu einstellen 
short OTypToVTyp (short iOTyp)
{
	switch (iOTyp) {
	case OGPunkt:	return VTPunkt;
	case OGLinie:	return VTLinie;
	case OGFlaeche:
	case OGKreis:	return VTFlaeche;
	case OGLabel:
	case OGText:	return VTText;
	default:
	case OGKO:
	case OGUnknown:
		break;
	}
	return VTDefault;
}

///////////////////////////////////////////////////////////////////////////////
// für aktuell selektierte/aktiviertes Objekt(e) VisInfo neu einstellen 
short VTypToOTyp (short iVTyp)
{
	switch (iVTyp) {
	case VTPunkt:	return OTPunkt;
	case VTLinie:	return OTLinie;
	case VTFlaeche:	return OTFlaeche;
	case VTText:	return OTText;
	default:
	case VTDefault:	
		break;
	}
	return 0;
}

// VisInfo für ein Objekt neu einstellen --------------------------------------
typedef struct tagOBJCHANGEDATA {
	HANDLEVISINFO *m_pHVI;
	bool m_fFirst;
} OBJCHANGEDATA;

extern "C"
BOOL _XTENSN_EXPORT PASCAL ObjChangeVisInfo (long lONr, BOOL, void *pData)
{
short Status = DEX_GetObjectStatus (lONr);

	if (Status != OSNormal && Status != OSModified) 
	// Objekt existiert nicht oder ist temporär
		return true;	// weitermachen

LONG lIdent = DEX_GetObjIdent (lONr);

	if (DEX_GetROModeIdent (lIdent))			// Tabelle dieses Objektes ist schreibgeschützt
		return true;	// weitermachen

// VisInfo nur neu einstellen, wenn Objekttyp übereinstimmt
OBJCHANGEDATA *pOCD = (OBJCHANGEDATA *)pData;
HANDLEVISINFO *pHVI = pOCD -> m_pHVI;

	if (OTypToVTyp (DEX_GetObjectType(lONr)) != pHVI -> m_iVTyp)
		return true;	// weitermachen

	pHVI -> m_lONr = lONr;
	pHVI -> m_lIdent = lIdent;
	return ((CVisObjExtension *)g_pTE) -> ModObjectVisInfo (pHVI, pOCD -> m_fFirst);
}

///////////////////////////////////////////////////////////////////////////////
// Objekt ausblenden
typedef struct tagOBJHIDEDATA {
	bool m_fShow;
	bool m_fFirst;
	HWND m_hORWnd;
} OBJHIDEDATA;

extern "C"
BOOL _XTENSN_EXPORT PASCAL ObjHideVisInfo (long lONr, BOOL, void *pData)
{
short Status = DEX_GetObjectStatus (lONr);

	if (Status != OSNormal && Status != OSModified)		// Objekt existiert nicht oder ist temporär
		return true;	// weitermachen

	if (DEX_GetROModeIdent (DEX_GetObjIdent (lONr)))			// tabelle dieses Objektes ist schreibgeschützt
		return true;	// weitermachen

OBJHIDEDATA *pOHD = (OBJHIDEDATA *)pData;

	return ((CVisObjExtension *)g_pTE) -> HandleHiddenFlag (lONr, pOHD -> m_fShow, pOHD -> m_fFirst, pOHD -> m_hORWnd);
}

// Vorgeben einer VisInfo für ein/mehrere Objekt(e) ---------------------------
bool CVisObjExtension::ChangeVisInfo (HWND hORWnd, bool fHSB)
{
// 1. Objekt feststellen, ONr, ObjTyp, Ident
long lActObj = DEX_GetActiveObject (hORWnd);

	if (lActObj == -1) return false;
		
short Status = DEX_GetObjectStatus (lActObj);

	if (Status != OSNormal && Status != OSModified) 
	// Objekt existiert nicht oder ist temporär
		return false;

// 2. Alte VisInfo besorgen (Ident + objektbezogene VI)
HANDLEVISINFO *pHVI = GetObjectVisInfo (lActObj);

	if (pHVI == NULL) return false;
//	if (pHVI -> m_fFlags & DT_WillDrawComplete)	// dises Objekt ist symbolisiert
//		return false;
		
// 3. Dialogfenster auslösen
//char pDesc[65];
short iCnt = 0;

	DEXOR_SelectedObjectsCount (hORWnd, &iCnt); 
//	if (iCnt > 1)
//		strcpy (pDesc, ResString (ResID (IDS_ALLOBJCAPTION, &RF()), 64));
//	else
//		wsprintf (pDesc, ResString (ResID (IDS_OBJECTCAPTION, &RF()), 20), lActObj);

//	pHVI -> m_pDesc = pDesc;
ResString resCap (ResID (IDS_ALLOBJCAPTION, &RF()), 64);

	pHVI -> m_pDesc = const_cast<char *>(resCap.Addr());
	pHVI -> m_hWnd = hORWnd;	// ParentFenster
	if (fHSB) pHVI -> m_fFlags |= DF_HSBModel;
	if (DEX_ModVisInfoDialog (*pHVI) != EC_OKAY) return false;

// 4. Neue VisInfo für selektiertes/aktivierte Objekte wegschreiben
OBJCHANGEDATA OCD;

	OCD.m_pHVI = pHVI;
	OCD.m_fFirst = false;
	
	if (iCnt > 1) {
	// alle selektierten behandeln
	ENUMLONGKEY ELK;
		
		ELK.eKey = (long)hORWnd;
		ELK.eFcn = (ENUMLONGKEYPROC)ObjChangeVisInfo;
		ELK.ePtr = &OCD;
		DEX_EnumSelectedObjects (ELK);
		
		if (OCD.m_fFirst)
			RebuildSight();		// alles neu zeichnen, neu aufbauen
		else 
			DEX_RePaintWait();	// alles neu zeichnen
	} else 	{	
	// lediglich aktiviertes Objekt behandeln
		ObjChangeVisInfo (lActObj, false, &OCD);
		
		if (OCD.m_fFirst) 
			RebuildSight();		// alles neu zeichnen, neu aufbauen
		else {
		// dieses Objekt neu zeichnen lassen
		long lCont[4];

			DEX_GetObjContainer (lActObj, lCont);	// Container besorgen

		ObjContainer OC (lCont[0], lCont[1], lCont[2], lCont[3]);
		Rectangle Rc = Rectangle (OC);
		Rectangle CRc = MWind() -> CanvasRect();

			Rc.Top() = CRc.Top() - CRc.Bottom() - Rc.Top();
			Rc.Bottom() = CRc.Top() - CRc.Bottom() - Rc.Bottom();
			DEX_RePaintRectWait (Rc);
		}
	}
	
	dtHANDLEVISINFO (pHVI);		// Speicher freigeben
		
return true;
}

// VisInfo an Objekt löschen --------------------------------------------------
BOOL _XTENSN_EXPORT PASCAL ObjResetVisInfo (long lONr, BOOL, void *pData)
{
short Status = DEX_GetObjectStatus (lONr);

	if (Status == OSNormal || Status == OSModified) {
	// Objekt existiert und ist nicht temporär: VisInfoMerkmal löschen	
	char const *pcView = reinterpret_cast<char const *>(pData);

		((CVisObjExtension *)g_pTE) -> ResetObjectVisInfo (lONr, pcView);
	}
	return true;
}

// VisInfo für selektiertes/aktivierte Objekt(e) rücksetzen -------------------
//bool CVisObjExtension::ResetVisInfo (HWND hORWnd)
//{
//// VisInfo für selektiertes/aktivierte Objekte weglöschen
//short iCnt = 0;
//
//	DEXOR_SelectedObjectsCount (hORWnd, &iCnt);
//	if (iCnt > 1) {
//	// alle selektierten behandeln
//	ENUMLONGKEY ELK;
//	
//		ELK.eKey = (long)hORWnd;
//		ELK.eFcn = (ENUMLONGKEYPROC)ObjResetVisInfo;
//		ELK.ePtr = NULL;
//		DEX_EnumSelectedObjects (ELK);
//		
//		DEX_RePaintWait();	// alles neu zeichnen
//	} else 	{	
//	// Objekt feststellen
//	long lActObj = DEX_GetActiveObject (hORWnd);
//        
//		if (lActObj == -1) return false;
//		
//	short Status = DEX_GetObjectStatus (lActObj);
//
//		if (Status != OSNormal && Status != OSModified) 
//		// Objekt existiert nicht oder ist temporär
//			return false;
//
//	// lediglich aktiviertes Objekt behandeln
//		ResetObjectVisInfo (lActObj);
//		
//	// dieses Objekt neu zeichnen lassen
//	long lCont[4];
//
//		DEX_GetObjContainer (lActObj, lCont);	// Container besorgen
//
//	ObjContainer OC (lCont[0], lCont[1], lCont[2], lCont[3]);
//	Rectangle CRc = MWind() -> CanvasRect();
//	Rectangle Rc = Rectangle (OC);
//
//		Rc.Top() = CRc.Top() - CRc.Bottom() - Rc.Top();
//		Rc.Bottom() = CRc.Top() - CRc.Bottom() - Rc.Bottom();
//		DEX_RePaintRectWait (Rc);
//	}
//
//return true;
//}

 
// Visualisierungsfehler für Punkt/Linie/Fläche/Text bearbeiten ---------------
// Result:	1 - ok, try again
//		2 - ok, do not try again
//		0 - cancel
short CVisObjExtension::HandleVisInfoError (CVisError *pCVE)
{
// Farben im weiteren automatisch zuweisen 
long lIdent = pCVE -> m_lIdent;
short iVTyp = pCVE -> m_iVTyp;

	if (m_fAutoAssignColors && AutoAssignNextColor (lIdent, iVTyp))
		return 2;

// wenn alle diesbezüglichen Fehler ignoriert werden soll dann sofort wieder raus
	if (m_fAllVisErrIgnore) return 2;

// überprüfen, ob wir diesen Ident bereits kennen
	if (m_pVIE -> FFindItem (lIdent, iVTyp, m_pActSight)) 
		return 2;	// immer ignorieren

// Fenster aufbauen und abfragen, was gemacht werden soll
short iResult = 0;

	if (m_lIdentHandled == -1L) {
		m_lIdentHandled = lIdent;	// dieser Ident wird behandelt
		
	CVisErrorDlg DVIErrDlg (MWind(), RF(), ResID (UNDEFINEDVISINFO, &RF()), 
				lIdent, iVTyp);

		if (!DVIErrDlg.Init()) 
			return 0;	// InitialisierungsFehler
		
		DVIErrDlg.Show();
		iResult = DVIErrDlg.Result();
	} else if (m_lIdentHandled == lIdent) {
	// doppelte Fehlermeldung für bereits zu behandelnden Ident
		return 2;	// so tun als ob alles ok wäre
	} else {
	// neue Fehlermeldung
		return 0;	// Standardfehlermeldung
	}

	switch (iResult) {
	case 1:		// neu definieren (RGB)
		DefineNewVisInfo (lIdent, iVTyp, false);
		break;

	case 2:		// in HSB definieren
		DefineNewVisInfo (lIdent, iVTyp, true);
		break;

//	case 3:		// im weiteren ignorieren
//		m_pVIE -> FAddItem (lIdent, iVTyp, m_pActSight);
	case 3:		// im weiteren automatisch zuweisen
		m_fAutoAssignColors = true;
		AutoAssignNextColor (lIdent, iVTyp);
		break;

	case 4:		// im weiteren alles ignorieren
		m_fAllVisErrIgnore = true;
		break;

	case 0:			// Cancel
		break;
	}

	m_lIdentHandled = -1L;		// kein Ident mehr behandelt
	iResult = 2;				// ok, do not try again
	return iResult;	
}

///////////////////////////////////////////////////////////////////////////////
// blindes Zuweisen der jeweils nächsten Farbe
bool CVisObjExtension::AutoAssignNextColor (long lIdent, short iVTyp)
{
// aktuelle VisInfo für Ident/Typ besorgen (StandardVisualisierung)
HANDLEVISINFO *pHVI = GetIdentVisInfo (lIdent, iVTyp);
bool fResult = true;

	if (NULL == pHVI) 
		return false;			// Fehler

	switch (iVTyp) {
	case VTPunkt:
		pHVI -> m_pVI -> m_Style = 10008;			// Viereck (bunt gefüllt, schwarzer Rand)
		pHVI -> m_pVI -> m_C = RGB(0, 0, 0);
		reinterpret_cast<PVISINFO *>(pHVI -> m_pVI) -> m_SecC = m_Colors.GetNextColor();
		break;

	case VTLinie:
		pHVI -> m_pVI -> m_C = m_Colors.GetNextColor();
		break;

	case VTFlaeche:
		pHVI -> m_pVI -> m_Style = 1;				// voll füllen
		pHVI -> m_pVI -> m_C = RGB(0, 0, 0);		// Rand schwarz
		reinterpret_cast<FVISINFO *>(pHVI -> m_pVI) -> m_FC = m_Colors.GetNextColor();
		break;

	case VTText:	// Texte immer Arial/schwarz
		pHVI -> m_pVI -> m_Style = Swiss;				// Swiss
		pHVI -> m_pVI -> m_C = RGB(0, 0, 0);
		strcpy (pHVI -> m_pVI -> m_VisName, "Arial");	// Arial
		break;

	default:
		fResult = false;
		break;
	}
	
	if (fResult && !DEX_ModIdentVisInfo (*pHVI))
		fResult = false;

	dtHANDLEVISINFO (pHVI);		// Speicher freigeben
	return fResult;
}

///////////////////////////////////////////////////////////////////////////////
// Interaktives Neueinstellen einer VisInfo
short CVisObjExtension::DefineNewVisInfo (long lIdent, short iVTyp, bool fHSB)
{
// aktuelle VisInfo für Ident/Typ besorgen (StandardVisualisierung)
HANDLEVISINFO *pHVI = GetIdentVisInfo (lIdent, iVTyp);

	if (pHVI == NULL) return 0;	// Fehler

	if (fHSB) pHVI -> m_fFlags |= DF_HSBModel;

// DialogFenster zur VisInfoEinstellung anfordern
short iResult = 0;

// IdentKurzText besorgen
PBDDATA pbdData;
char pKText[33];

	memset (&pbdData, '\0', sizeof(PBDDATA));
	pbdData.dwSize = sizeof(PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = lIdent;
	pbdData.pbdKText = pKText;
	pbdData.pbdKTextLen = sizeof(pKText) -1;

	if (DEX_GetPBDData (pbdData) != EC_OKAY)
		ClassFromIdentX (lIdent, pKText);

	pKText[32] = '\0';
	pHVI -> m_pDesc = pKText;	// Überschrift der DialogBox setzen
	
	if (DEX_ModVisInfoDialog (*pHVI) == EC_OKAY && 
	    DEX_ModIdentVisInfo (*pHVI) == EC_OKAY)
		iResult = 2;
		
	dtHANDLEVISINFO (pHVI);		// Speicher freigeben
	return iResult;				// ok, error handled
}


// VisualisierungsInfo für einen Identifikator/Typ besoregn -------------------
HANDLEVISINFO *GetIdentVisInfo (long lIdent, short iVTyp, char *pView)
{
// typgerechte VISINFO-Struktur anfordern
HANDLEVISINFO *pHVI = ctHANDLEVISINFO (iVTyp);

	if (pHVI == NULL) return NULL;

// Strukturen füllen
	pHVI -> m_pView = pView;

	if (-1L != lIdent && 0 != lIdent) {
		pHVI -> m_lIdent = lIdent;
		
		if (!DEX_GetIdentVisInfo (*pHVI)) 	// Fehler aufgetreten
			dtHANDLEVISINFO (pHVI);
	}
	return pHVI;
}


// Besorgen der aktuellen VisInfo eines Objektes ------------------------------
HANDLEVISINFO *GetObjectVisInfo (long lONr, char *pView, long lMCode, 
				 char **cbModuleInfo, short fFlags)
{
// typgerechte VISINFO-Struktur anfordern
short iOTyp = DEX_GetObjectType (lONr);
HANDLEVISINFO *pHVI = ctHANDLEVISINFO (OTypToVTyp (iOTyp), true);

	if (pHVI == NULL) return NULL;

// Strukturen füllen, IdentVisInfo besorgen
	pHVI -> m_pView = pView;
	pHVI -> m_lONr = lONr;
	if (!DEX_GetIdentVisInfo (*pHVI)) {
	// Fehler aufgetreten
		dtHANDLEVISINFO (pHVI);
		return NULL;
	}
	
// evtl. vorhandene objektbezogene Visualiserung überlagern
// dazu Merkmal lesen und interpretieren
	if (NULL == cbModuleInfo) {
	char *cbModuleInfoT[2];

		cbModuleInfoT[0] = cbModuleInfoT[1] = NULL;
		pHVI -> m_fFlags = ((CVisObjExtension *)g_pTE) -> GetNewVI (pHVI, lMCode, 
								   fFlags, cbModuleInfoT);
		if (sizeof(HANDLEVISINFOEX) == pHVI -> dwSize) {
		HANDLEVISINFOEX *pHVIEx = (HANDLEVISINFOEX *)pHVI;

			pHVIEx -> m_pModule = cbModuleInfoT[0];
			pHVIEx -> m_pInfo = cbModuleInfoT[1];
		}
		else {
			DELETE_OBJ (cbModuleInfoT[0]);
			DELETE_OBJ (cbModuleInfoT[1]);
		}
	}
	else {
		pHVI -> m_fFlags = ((CVisObjExtension *)g_pTE) -> GetNewVI (pHVI, lMCode, 
								   fFlags, cbModuleInfo);
	}
	pHVI -> m_fFlags |= DT_CustomVisualisation;
	return pHVI;
}


// Generieren aller Informationen für eine objektbezogene Visualisierung ------
bool CVisObjExtension::ModObjectVisInfo (HANDLEVISINFO *pHVI, bool &fFirst)
{
// MerkmalsCodes sicherstellen und Identifikator behandeln
bool iResult = false;
int iObjTypBit = VTypToOTyp(pHVI -> m_iVTyp);
char *pObjM = VisInfoToString (pHVI, m_fFullVisInfo, &RF()); 	// immer RGB !

	if (AdjustIdentifier (pHVI -> m_lIdent, OVModVisInfo, iObjTypBit, true, &fFirst, pHVI -> m_pView)) {
	// alles ok, Merkmal (VisInfo) am Objekt generieren
	long lMCode = GetObjMCode (true, pHVI -> m_pView, pHVI -> m_lIdent);

		iResult = WriteTextMerkmal (TT_Objekt, pHVI -> m_lONr, lMCode, pObjM);
	}

#if defined(_USE_DEFAULTVIEW_FOR_TEXTS)
// für Textobjekte auch noch an der DefaultAnsicht wegschreiben
	if (OTText == iObjTypBit) {
	LONG lMCodeDV = GetObjMCode (false, g_cbDefaultVisInfo, pHVI -> m_lIdent);

		if (-1 == lMCodeDV || !ReadTextMerkmal (TT_Objekt, pHVI -> m_lONr, lMCodeDV, NULL)) {
			if (AdjustIdentifier (pHVI -> m_lIdent, OVModVisInfo, iObjTypBit, true, &fFirst, g_cbDefaultVisInfo)) {
			// alles ok, Merkmal (VisInfo) am Objekt generieren
				if (-1 == lMCodeDV)
					lMCodeDV = GetObjMCode (true, g_cbDefaultVisInfo, pHVI -> m_lIdent);
				iResult = WriteTextMerkmal (TT_Objekt, pHVI -> m_lONr, lMCodeDV, pObjM);
			}
		}
	}
#endif // defined(_USE_DEFAULTVIEW_FOR_TEXTS)

	DELETE_OBJ (pObjM);
	return iResult;
}

///////////////////////////////////////////////////////////////////////////////
// Rücksetzen einer objektbezogenen Visualisierung (einschließlich ausblenden!)
bool CVisObjExtension::ResetObjectVisInfo (long lONr, LPCSTR pView)
{
long lMCode = GetObjMCode (false, (char *)pView, DEX_GetObjIdent(lONr));

	if (-1 == lMCode) 
		return false;

long lIdent = DEX_GetObjIdent(lONr);
int iObjTypBit = OTypToBits(DEX_GetObjectType(lONr));

	if (WriteTextMerkmal (TT_Objekt, lONr, lMCode, NULL)) {
		if (WasLastObject (lIdent, lMCode, iObjTypBit) &&
			(!AdjustIdentifier (lIdent, OVModVisInfo, iObjTypBit, false) ||
			 !AdjustIdentifier (lIdent, OVModShow, iObjTypBit, false)) )
		{
			return false;
		}
		return true;
	}
	return false;
}


// Generieren aller Informationen für eine objektbezogene Symbolisierung ------
bool CVisObjExtension::ModObjectSymbol (long lONr, char *pVStr, bool &fFirst)
{
bool iResult = false;
long lIdent = DEX_GetObjIdent (lONr);
int iObjTypBit = OTypToBits(DEX_GetObjectType(lONr));

// MerkmalsCodes sicherstellen und Identifikator behandeln
	if (AdjustIdentifier (lIdent, OVModVisInfo, iObjTypBit, true, &fFirst)) {
	// alles ok, Merkmal (SymbolInfo) am Objekt generieren
		TX_ASSERT(NULL != m_pActSight && strlen(m_pActSight) > 0);

	long lMCode = GetObjMCode (true, (char *)m_pActSight, lIdent);

		iResult = WriteTextMerkmal (TT_Objekt, lONr, lMCode, pVStr);
	}
	return iResult;
}


bool ReadTextMerkmal (short iTTyp, long lTarget, long lMCode, char *pText, int iLen, const char *pcView)
{
TARGETMERKMALEX gm;

	gm.dwSize = sizeof(TARGETMERKMALEX);
	gm.lTarget = (LPARAM)lTarget;
	gm.lMCode = lMCode;
	gm.imaxLen = (iLen != -1) ? iLen-1 : (pText != NULL ? MWERTSIZE-2 : 0);
	gm.pMText = pText;
	gm.iTTyp = iTTyp;
	gm.pcView = (TT_Identifikator == iTTyp) ? pcView : NULL;
	if (DEX_GetTextMerkmal (gm) == NULL)
		return false;

	return true;
}

bool WriteTextMerkmal (short iTTyp, long lTarget, long lMCode, const char *pText, const char *pcView)
{
TARGETMERKMALEX gm;

	gm.dwSize = sizeof(TARGETMERKMALEX);
	gm.lTarget = (LPARAM)lTarget;
	gm.lMCode = lMCode;
	gm.imaxLen = pText != NULL ? strlen (pText) : 0;
	gm.pMText = const_cast<char *>(pText);
	gm.iTTyp = iTTyp;
	gm.pcView = (TT_Identifikator == iTTyp) ? pcView : NULL;
	if (DEX_ModTextMerkmal (gm) != EC_OKAY)
		return false;
	return true;
}


// Generieren des Identifikatormerkmales zur Kennzeichnung, daß Objekte mit 
// diesem Identifikator objektbezogen visualisiert werden sollen
/* static */
char *CVisObjExtension::IdModeToString (DWORD iMode, long lMCode)
{
char *pResult = new char [64];

	if (pResult) 
		wsprintf (pResult, "%ld,%ld", DT_HasNewVI | iMode, lMCode);
	return pResult;
}


// Interpretation des Identifikatormerkmales, welches über die objektbezogene 
// Visualisierung der Objekte mit diesem Identifikator wacht
/* static */
DWORD CVisObjExtension::StringToIdMode (char *pMText, long *plObjMCode)
{
	TX_ASSERT(NULL != pMText);

	if (pMText) {
	DWORD dwMode = 0L;
	long lMCode = -1L;

		if (2 == sscanf (pMText, "%ld,%ld", &dwMode, &lMCode)) {
			if (NULL != plObjMCode) {
				if (0 == lMCode)
					lMCode = -1L;
				*plObjMCode = lMCode;
			}
			return dwMode;
		}
	}
	return 0;
}



// Adresse des Endes einer Zeichenkette ---------------------------------------
inline char *EOS (char *pBuffer) { return &pBuffer[strlen(pBuffer)]; }

// Liefert ResourceID für ObjekttypString -------------------------------------
unsigned int TypeIDS (short iVTyp)
{
	switch (iVTyp) {
	case VTPunkt:	return IDS_PHEADER;
	case VTLinie:	return IDS_LHEADER;
	case VTFlaeche:	return IDS_FHEADER;
	case VTText:	return IDS_THEADER;
	case VTDefault:
	default:
		break;
	}

return IDS_GHEADER;
}


// Extrahiert objekttypspezifisch den Visualisierungstyp ----------------------
inline unsigned int GetStyle (HANDLEVISINFO *pHVI) 
{
unsigned short uiResult = (unsigned short)(pHVI -> m_pVI -> m_Style);

	if (pHVI -> m_iVTyp == VTFlaeche)
		uiResult = (uiResult & ~BMOpaque) % 100;

return uiResult;
}


// Wandelt eine VisInfo in einen String um, der am Objekt abgespeichert wird --
char *VisInfoToString (
	HANDLEVISINFO *pHVI, bool fFullVisInfo,	ResourceFile *pRF, bool fRGB, 
	char *pIdString, bool fExport, char **cbModuleInfo, char *pLegInfo,
	long lUpperScale, long lLowerScale)
{
short fFlags = pHVI -> m_fFlags;
VISINFO *pVI = pHVI -> m_pVI;

	if (pVI == NULL) return NULL;
	
char *pR = new char [6*_MAX_PATH];

	if (pR == NULL) return NULL;
	*pR = '\0';

	if (!fFullVisInfo && fFlags == DO_UnChanged) return pR;
	
	if (NULL == pRF) pRF = &g_pTE -> RF();

// Kopf ausgeben
	{
	ResString rsHead (ResID (TypeIDS (pHVI -> m_iVTyp), pRF), 13);
	
		wsprintf (pR, fExport ? rsHead.Addr() : rsHead.Addr()+1,
			  pIdString ? pIdString : "");
	}
	
// StandardVisInfo generieren			
	if (fFullVisInfo || fFlags & DO_NameChanged) {		// t=%d,"%s";
		if (pVI -> m_VisName[0] != '\0') {
			wsprintf (EOS(pR), 
				  ResString (ResID (IDS_NEWSTYLENAME, pRF), 13),
				  GetStyle (pHVI), pVI -> m_VisName);
		} else {
			wsprintf (EOS(pR), 
				  ResString (ResID (IDS_NEWSTYLE, pRF), 13),
				  GetStyle (pHVI));
		}
	} else if (fFlags & DO_StyleChanged)  			// t=%d;
		wsprintf (EOS(pR), 
			  ResString (ResID (IDS_NEWSTYLE, pRF), 13),
			  GetStyle (pHVI));

	if (fFullVisInfo || fFlags & DO_PriorityChanged)  	// p=%d;
		wsprintf (EOS(pR), 
			  ResString (ResID (IDS_NEWPRIORITY, pRF), 13),
			  pVI -> m_Priority);

	if (fFullVisInfo || fFlags & DO_PrimColorChanged) { 	// m=%d,%d,%d;
		if (fRGB) {	// RGB-Modell
			wsprintf (EOS(pR), 
				  ResString (ResID (IDS_NEWPRIMCOLOR, pRF), 13),
				  GetRValue (pVI -> m_C), GetGValue (pVI -> m_C),
				  GetBValue (pVI -> m_C));
		} else {	// HSB-Modell
		unsigned long hsbF = RGBtoHSB ((Color &)pVI -> m_C);
		
			wsprintf (EOS(pR), 
				  ResString (ResID (IDS_NEWPRIMCOLORHSB, pRF), 20),
				  GetSValue (hsbF), GetVValue (hsbF),
				  GetHValue (hsbF));
		}
	}
	if (fFullVisInfo || fFlags & DO_OthersChanged) {  	// us=%d; ls=%d; 
		if (0 != lUpperScale) {
			wsprintf (EOS(pR), 
				ResString (ResID (IDS_UPPERSCALE, pRF), 13),
				lUpperScale);
		}
		if (0 != lLowerScale) {
			wsprintf (EOS(pR), 
				ResString (ResID (IDS_LOWERSCALE, pRF), 13),
				lLowerScale);
		}
		if (!pVI -> m_fVisible) {
			wsprintf (EOS(pR), 
				ResString (ResID (IDS_VISIBLE, pRF), 13),
				pVI -> m_fVisible ? 1 : 0);
			fFlags |= DO_Tagged;
		}
		if (!pVI -> m_fLocatable) {
			wsprintf (EOS(pR), 
				ResString (ResID (IDS_LOCATABLE, pRF), 13),
				pVI -> m_fLocatable ? 1 : 0);
		}
		if ('\0' != pVI -> m_GeomName[0] && strcmp (g_cbGeometryFieldName, pVI -> m_GeomName)) {
			wsprintf (EOS(pR), 
				ResString (ResID (IDS_GEOMETRY, pRF), 13),
				pVI -> m_GeomName);
		}
	}

// typspezifische VisInfo generieren
	switch (pHVI -> m_iVTyp) {
	case VTPunkt:
		{
		PVISINFO *pPVI = (PVISINFO *)pVI;

		if (fFullVisInfo || fFlags & DO_SizeChanged) {	// s=%d,%d;
			wsprintf (EOS(pR), 
				  ResString (ResID (IDS_NEWSIZE, pRF), 13),
				  pPVI -> m_Size.cx, pPVI -> m_Size.cy);
		}
		if (fFullVisInfo || fFlags & DO_SecColorChanged) { 	// f=%d,%d,%d;
			if (fRGB) {	// RGB-Modell
				wsprintf (EOS(pR), 
					  ResString (ResID (IDS_NEWSECCOLOR, pRF), 13),
					  GetRValue (pPVI -> m_SecC), GetGValue (pPVI -> m_SecC),
					  GetBValue (pPVI -> m_SecC));
			} else {	// HSB-Modell
			unsigned long hsbF = RGBtoHSB ((Color &)pPVI -> m_SecC);
			
				wsprintf (EOS(pR), 
					  ResString (ResID (IDS_NEWSECCOLORHSB, pRF), 20),
					  GetSValue (hsbF), GetVValue (hsbF),
					  GetHValue (hsbF));
			}
		}
		if (fFullVisInfo || fFlags & DO_OthersChanged) 
			wsprintf (EOS(pR),  		// r=%d;
				  ResString (ResID (IDS_NEWROTATION, pRF), 13),
				  pPVI -> m_iRot);

		}
		break;
		
	case VTLinie:
		if (fFullVisInfo || fFlags & DO_SizeChanged) {	// w=%d;
			wsprintf (EOS(pR), 
				  ResString (ResID (IDS_NEWWIDTH, pRF), 13),
				  ((LVISINFO *)pVI) -> m_Width);
		}
		break;
		
	case VTFlaeche:
		{
		FVISINFO *pFVI = (FVISINFO *)pVI;
		
		if (fFullVisInfo || fFlags & DO_SecColorChanged) { 	// f=%d,%d,%d;
			if (fRGB) {	// RGB-Modell
				wsprintf (EOS(pR), 
					  ResString (ResID (IDS_NEWSECCOLOR, pRF), 13),
					  GetRValue (pFVI -> m_FC), GetGValue (pFVI -> m_FC),
					  GetBValue (pFVI -> m_FC));
			} else {	// HSB-Modell
			unsigned long hsbF = RGBtoHSB ((Color &)pFVI -> m_FC);
			
				wsprintf (EOS(pR), 
					  ResString (ResID (IDS_NEWSECCOLORHSB, pRF), 20),
					  GetSValue (hsbF), GetVValue (hsbF),
					  GetHValue (hsbF));
			}
		}
		if (fFullVisInfo || fFlags & DO_SizeChanged) {	// s=%d,%d;
			wsprintf (EOS(pR), 
				  ResString (ResID (IDS_NEWWIDTH, pRF), 13),
#if defined(OLDVISINFO)
				  (pVI -> m_Style & ~BMOpaque) / 100);
#else
				  pFVI -> m_iWidth);
#endif // OLDVISINFO
		}
		if (fFullVisInfo || fFlags & DO_StyleChanged)	// y=0x%x;
			wsprintf (EOS(pR), 
				  ResString (ResID (IDS_NEWTYPE, pRF), 13),
#if defined(OLDVISINFO)
			  	  pVI -> m_Style & BMOpaque);
#else
			  	  pFVI -> m_iAttrEx);
#endif // OLDVISINFO
		}
		break;
		
	case VTText:
		{
		TVISINFO *pTVI = (TVISINFO *)pVI;
		
		if (fFullVisInfo || fFlags & DO_SizeChanged) {	// s=%d,%d;
			wsprintf (EOS(pR), 
				  ResString (ResID (IDS_NEWSIZE, pRF), 13),
				  pTVI -> m_Size.cy, pTVI -> m_Size.cx);
		}
		if (fFullVisInfo || fFlags & DO_OthersChanged) {
			if (fExport) {
				wsprintf (EOS(pR),  		// r=%d;
					  ResString (ResID (IDS_NEWROTATION, pRF), 13),
					  pTVI -> m_Rot);
			} else {
				wsprintf (EOS(pR),  		// r=%d; o=%d;
					  ResString (ResID (IDS_NEWROTORIENT, pRF), 13),
					  pTVI -> m_Rot, pTVI -> m_Orient);
			}
			wsprintf (EOS(pR),  			// y=0x%x;
				  ResString (ResID (IDS_NEWTYPE, pRF), 13),
				  pTVI -> m_Type);
		}
		}
		break;
		
	case VTDefault:
		if (fExport) {
		DVISINFO *pDVI = (DVISINFO *)pVI;
		
			wsprintf (EOS(pR),  			// y=0x%x;
				  ResString (ResID (IDS_NEWTYPE, pRF), 13),
				  pDVI -> m_iDefTypes);
		}
		break;
		
	default:
		break;
	}

// evtl. LegendenInfo hinzufügen
	if (pLegInfo) {	// lg={"%s"};
	char cbFormat[32];

		wsprintf (cbFormat, ResString (ResID (IDS_LEGENDINFOFORMAT, pRF), 40), 5*_MAX_PATH); 
		wsprintf (EOS(pR), cbFormat, pLegInfo);
	}

// evtl. CustomInfo hinzufügen
	if (fFlags & DT_WillDrawComplete) {
	    if (cbModuleInfo && cbModuleInfo[0] && cbModuleInfo[1]) {
			if (*cbModuleInfo[1] == '%') {	// v="%s":%s;
				wsprintf (EOS(pR), ResString (ResID (IDS_CUSTOMVISINFO1, pRF), 20),
					  cbModuleInfo[0], cbModuleInfo[1]);
			} else {			// v="%s":"%s";
				wsprintf (EOS(pR), ResString (ResID (IDS_CUSTOMVISINFO2, pRF), 20),
					  cbModuleInfo[0], cbModuleInfo[1]);
			}
		}
		else if (sizeof(HANDLEVISINFOEX) == pHVI -> dwSize) {
		HANDLEVISINFOEX *pHVIEx = (HANDLEVISINFOEX *)pHVI;

			if (NULL != pHVIEx->m_pModule && NULL != pHVIEx->m_pInfo) {
				if (pHVIEx->m_pInfo[0] == '%') {	// v="%s":%s;
					wsprintf (EOS(pR), ResString (ResID (IDS_CUSTOMVISINFO1, pRF), 20),
						  pHVIEx->m_pModule, pHVIEx->m_pInfo);
				} 
				else {			// v="%s":"%s";
					wsprintf (EOS(pR), ResString (ResID (IDS_CUSTOMVISINFO2, pRF), 20),
						  pHVIEx->m_pModule, pHVIEx->m_pInfo);
				}
			}
		}
	}
				   
// abschließende Klammer und Tag ausgeben
	strcat (pR, ResString (ResID (IDS_TRAILER, pRF), 13));
	if (fFlags & DO_Tagged && !(fFlags & DT_WillDrawComplete))
		strcat (pR, ResString (ResID (IDS_TAG, pRF), 13));
			
	return pR;
}

///////////////////////////////////////////////////////////////////////////////
// Testen, ob noch Objekte des gegebenen Objekttypes ausgeblendet sind
typedef struct tagTESTOBJECTTYPE {
	long lIdent;	// gesuchter Identifikator
	DWORD dwType;	// gesuchter Objekttyp
} TESTOBJECTTYPE;

extern "C" 
BOOL CALLBACK TestObjectType (long lONr, BOOL, void *pData)
{
// abbrechen, wenn wenigstens ein betreffendes Objekt gefunden wurde
TESTOBJECTTYPE *pTOT = reinterpret_cast<TESTOBJECTTYPE *>(pData);
DWORD dwType = OTypToBits(DEX_GetObjectType(lONr));
long lIdent =  DEX_GetObjIdent (lONr);

	return (pTOT -> lIdent == lIdent && (pTOT -> dwType & dwType)) ? false : true;
}

bool CVisObjExtension::WasLastObject (long lIdent, long lMCode, DWORD dwObjTypeBit)
{
TESTOBJECTTYPE TOT;

	TOT.lIdent = lIdent;
	TOT.dwType = dwObjTypeBit;

ENUMRECHTEXTMERKMAL ERTM;

	INITSTRUCT(ERTM, ENUMRECHTEXTMERKMAL);
	ERTM.pView = NULL;		// es können nur Objekte einer Sicht sein
	ERTM.lMCode = lMCode;
	ERTM.pMWert = NULL;		// alle Objekte
	ERTM.iMode = 0;
	ERTM.eFcn = TestObjectType;
	ERTM.pData = reinterpret_cast<void *>(&TOT);
	return DEX_EnumRechTextMerkmal (ERTM);
}

///////////////////////////////////////////////////////////////////////////////
// HiddenFlag hinzufügen 
bool CVisObjExtension::HandleHiddenFlag (long lONr, bool fShow, bool &fFirst, HWND hORWnd)
{
	TX_ASSERT(NULL != m_pActSight && strlen(m_pActSight) > 0);
	return HandleHiddenFlag (lONr, fShow, fFirst, m_pActSight, hORWnd);
}

///////////////////////////////////////////////////////////////////////////////
// HiddenFlag für eine Ansicht behandlen
bool CVisObjExtension::HandleHiddenFlag (long lONr, bool fShow, bool &fFirst, LPCSTR pcView, HWND hORWnd)
{
// MerkmalsCode für Objekt/Identifikator sicherstellen
long lIdent = DEX_GetObjIdent (lONr);
long lObjVisMCode = GetObjMCode(true, (LPSTR)pcView, lIdent);
int iObjTypBit = OTypToBits(DEX_GetObjectType(lONr));

	if (-1 == lObjVisMCode)
		return false;

// beim wieder Einblenden testen, ob alle wieder da sind
	if (fShow && WasLastObject (lIdent, lObjVisMCode, iObjTypBit) &&
		!AdjustIdentifier (lIdent, OVModShow, iObjTypBit, false, &fFirst))
	{
		return false;
	}

// beim Ausblenden immer Ident richten
	if (!fShow && !AdjustIdentifier (lIdent, OVModShow, iObjTypBit, true, &fFirst))
		return false;

	if (ReadTextMerkmal (TT_Objekt, lONr, lObjVisMCode, m_pMWert)) {
	// VisualisierungsMerkmal existiert bereits
	char *pPtr = strchr (m_pMWert, '}');
	
		if (pPtr != NULL) {
			if (!fShow) 
				strcpy (pPtr +1, ResString (ResID (IDS_TAG, &RF()), 13));
			else 
				*(pPtr+1) = '\0';	// Tag wegknacken
			WriteTextMerkmal (TT_Objekt, lONr, lObjVisMCode, m_pMWert);
			return true;
		} else if (fShow) {
			WriteTextMerkmal (TT_Objekt, lONr, lObjVisMCode, NULL);
			return true;
		}			
	} 
	if (!fShow) 
		WriteTextMerkmal (TT_Objekt, lONr, lObjVisMCode, (char *)ResString (ResID (IDS_TAG, &RF()), 13).Addr());

	if (NULL != hORWnd)
		DEX_RefreshEntry(lONr);
	return true;
}

bool CVisObjExtension::GetHiddenFlag (long lONr, bool &rfShow, LPCSTR pcView)
{
// MerkmalsCode für Objekt/Identifikator sicherstellen
long lIdent = DEX_GetObjIdent (lONr);
long lObjVisMCode = GetObjMCode (false, (LPSTR)pcView, DEX_GetObjIdent(lONr));

	if (-1 == lObjVisMCode)
		return false;

	if (ReadTextMerkmal (TT_Objekt, lONr, lObjVisMCode, m_pMWert)) {
	// VisualisierungsMerkmal existiert bereits
	char *pPtr = strchr (m_pMWert, '}');
	
		if (pPtr != NULL) {
		ResString resTag (ResID (IDS_TAG, &RF()), 13);

			rfShow = strcmp (resTag, pPtr) ? true : false;
			return true;
		} 			
	} 
	rfShow = true;		// derzeit eingeblendet
	return true;
}

// String in neuem ORFenster verändern, wenn Objekt HIDDEN ist ----------------
bool CVisObjExtension::HandleQueryRechObject (RECHOBJECT *pRO)
{
long lMCode = GetObjMCode (false, (char *)m_pActSight, pRO -> lIdent);

	if (lMCode == -1) 
		return false;	// nicht modifizieren, dieses Objekt enthält nichts
		
	if (GetIDMode (pRO -> lIdent) == DT_Normal) 
		return false;	// dieser Ident enthält nichts
		
VisInfo *pVI = NULL;
char *pText = pRO -> lpText;
short iDrawStatus = GetNewVI (pRO -> lONr, pVI, true, lMCode, DF_Analyze);

// Speicher freigeben
	DELETE_OBJ (pVI);

// Objekt wird über VisModule symbolisiert
	if (iDrawStatus & DT_WillDrawComplete) return false;
	if (iDrawStatus & DT_NoDrawing) {
	// Objekt ist Hidden
		if (pText) {
		int iLen = int(strlen (pText));

			iLen = min(iLen+1, int(pRO -> iTextLen));
			memmove (pText +1, pText, iLen);
			*pText = '*';
			pText[iLen] = '\0';

			(pRO -> lpText)++;	// der nächste soll denken, hier geht's los
		}
		return !(m_fShowHidden || (pRO -> iFlags & ROShowHidden));
					// evtl. versteckte Objekte angezeigen
	}
	return false;		// alles andere recherchierbar halten
}


// Selektierte/Aktiviertes Objekt(e) HIDDEN markieren -------------------------
bool CVisObjExtension::HideObjects (HWND hORWnd)
{
// VisInfo für selektiertes/aktivierte Objekte weglöschen
short iCnt = 0;
OBJHIDEDATA HOD;

	HOD.m_fShow = false;
	HOD.m_fFirst = false;
	HOD.m_hORWnd = hORWnd;

	DEXOR_SelectedObjectsCount (hORWnd, &iCnt);
	if (iCnt > 1) {
	// alle selektierten behandeln
	ENUMLONGKEY ELK;
	
		ELK.eKey = (long)hORWnd;
		ELK.eFcn = (ENUMLONGKEYPROC)ObjHideVisInfo;
		ELK.ePtr = &HOD;
		DEX_EnumSelectedObjects (ELK);
		
		if (HOD.m_fFirst)
			RebuildSight();	// alles neu zeichnen, neu aufbauen
		else if (!m_fShowHidden) 
			DEX_RePaintWait();	// alles neu zeichnen
	} 
	else {	
	// Objekt feststellen
	long lActObj = DEX_GetActiveObject (hORWnd);
        
		if (lActObj == -1) return false;
		
	// lediglich aktiviertes Objekt behandeln
		ObjHideVisInfo (lActObj, false, &HOD);

		if (HOD.m_fFirst)
			RebuildSight();		// alles neu zeichnen, neu aufbauen
		else if (!m_fShowHidden) {		
		// dieses Objekt neu zeichnen lassen
		long lCont[4];

			DEX_GetObjContainer (lActObj, lCont);	// Container besorgen

		ObjContainer OC (lCont[0], lCont[1], lCont[2], lCont[3]);
		Rectangle CRc = MWind() -> CanvasRect();
		Rectangle Rc = Rectangle (OC);

			Rc.Top() = CRc.Top() - CRc.Bottom() - Rc.Top();
			Rc.Bottom() = CRc.Top() - CRc.Bottom() - Rc.Bottom();
			DEX_RePaintRectWait (Rc);
		}
	}
	return true;
}

// Sicht neu generiert: Ident/Objekttypen behandeln ---------------------------
extern "C" 
BOOL _XTENSN_EXPORT PASCAL HandleViewCreatedObject (long lONr, DWORD, void *pData)
{
// Testen, ob dieses Object in TargetSicht besonders behandelt wurde
VIEWCREATED *pVC = (VIEWCREATED *)pData;
long lMCode = ((CVisObjExtension *)g_pTE) -> GetObjMCode (false, (char *)pVC -> m_pTarget, DEX_GetObjIdent(lONr));
char cbBuffer[_MAX_PATH+1];

	if (!ReadTextMerkmal (TT_Objekt, lONr, lMCode, cbBuffer))
		return true;		// Objekt hat keine Extra's

// ObjVisInfo lesen und an neuer Sicht ablegen
char *cbModuleInfo[2];

	cbModuleInfo[0] = cbModuleInfo[1] = NULL;

HANDLEVISINFO *pHVI = GetObjectVisInfo (lONr, (char *)pVC -> m_pTarget, lMCode, cbModuleInfo);

	if (pHVI != NULL) {
	bool fFirst = false;	// dummy

		pHVI -> m_pView = (char *)pVC -> m_pNewName;
		ChangeVisInfo (pHVI, cbModuleInfo);
		dtHANDLEVISINFO (pHVI);		// Speicher freigeben
	}
	DELETE_OBJ (cbModuleInfo[0]);
	DELETE_OBJ (cbModuleInfo[1]);
	return true;
}

bool HandleViewCreatedIdentEx (long lIdent, VIEWCREATED *pVC, short iOTyp, short iVTyp)
{
	if (0 == iVTyp)
		iVTyp = OTypToVTyp(iOTyp);

// Testen, ob dieser Ident in TargetSicht besonders behandelt wurde
DWORD iIdMode = ((CVisObjExtension *)g_pTE) -> GetIDMode (lIdent, (char *)pVC -> m_pTarget);

	if (iIdMode == DT_Normal) return true;	// keine Extra's

// alle Objekte mit dem gegebenen Typ behandeln
ENUMLONGKEYEX ELK;

	ELK.eKey = lIdent;
	ELK.eFcn = (ENUMLONGKEYEXPROC)HandleViewCreatedObject;
	ELK.ePtr = pVC;
	ELK.eData = DWORD(iOTyp);
	DEX_EnumIdentObjectsEx(ELK);
	
	return true;
}

extern "C"
BOOL _XTENSN_EXPORT PASCAL HandleViewCreatedIdent (long lIdent, DWORD dwData, void *pData)
{
// Alle Ident/ObjektTyp-Kombinationen einzeln abarbeiten

	if (dwData & OTPunkt)
		HandleViewCreatedIdentEx (lIdent, (VIEWCREATED *)pData, OTPunkt, VTPunkt);
	if (dwData & OTLinie)
		HandleViewCreatedIdentEx (lIdent, (VIEWCREATED *)pData, OTLinie, VTLinie);
	if (dwData & OTFlaeche)
		HandleViewCreatedIdentEx (lIdent, (VIEWCREATED *)pData, OTFlaeche, VTFlaeche);
	if (dwData & OTText)
		HandleViewCreatedIdentEx (lIdent, (VIEWCREATED *)pData, OTText, VTText);

	return true;
}

// Objektbezogene Visualisierung und LegendInfo an neu erzeugte Sicht übernehmen
bool CVisObjExtension::HandleViewCreated (VIEWCREATED *pVC)
{
// testen, ob überhaupt was gemacht werden muß
	if (!(pVC -> m_iMode & VCUseTargetView) ||
	    (pVC -> m_iMode & (VCDeleteTarget|VCFeaturesMoved)))
	{
		return false;	// nichts zu tun
	}
	if (pVC -> m_pTarget == NULL || pVC -> m_pNewName == NULL)
		return true;

// für alle Idents der neuen Sicht, die entsprechende Info aus der TargetSicht
// übernehmen. Dazu Idents der neuen Sicht enumerieren
ENUMTEXTKEYEX ETK;

	ETK.eKey = (char *)pVC -> m_pNewName;
	ETK.eFcn = (ENUMLONGKEYEXPROC)HandleViewCreatedIdent;
	ETK.ePtr = pVC;
	ETK.eData = (OTPunkt|OTLinie|OTFlaeche|OTText);
	DEX_EnumSightIdentsEx(ETK);

	return false;		// Notifikation weiterreichen
}

///////////////////////////////////////////////////////////////////////////////
// Alle VisMWerte innerhalb dieser Sicht löschen 

typedef struct tagDELETEVIEWDATA {
	LPCSTR pcView;
	long lMCode;
} DELETEVIEWDATA;

extern "C" 
BOOL _XTENSN_EXPORT PASCAL HandleIdentOnDeleteSight (long lIdent, BOOL, void *pData)
{
// Alle Objekte mit diesem MerkmalsCode enumerieren
DELETEVIEWDATA *pDVD = (DELETEVIEWDATA *)pData;
long lMCode = ((CVisObjExtension *)g_pTE) -> GetObjMCode (false, pDVD -> pcView, lIdent);

	if (-1 != lMCode && 0 != lMCode) {
	ENUMRECHTEXTMERKMAL ERTM;

		INITSTRUCT(ERTM, ENUMRECHTEXTMERKMAL);
		ERTM.pView = NULL;		// es können nur Objekte einer Sicht sein
		ERTM.lMCode = lMCode;
		ERTM.pMWert = NULL;		// alle Objekte
		ERTM.iMode = 0;
		ERTM.eFcn = ObjResetVisInfo;
		ERTM.pData = const_cast<char *>(pDVD -> pcView);
		DEX_EnumRechTextMerkmal (ERTM);

	// MCode auch aus PBD löschen
	PBDMERKMALEX TM;

		INITSTRUCT (TM, PBDMERKMALEX);
		TM.pbdTyp = 'm';
		TM.pbdCode = lMCode;
		TM.lIdent = lIdent;
		{
		ErrInstall EI (WC_NOMERKMAL);

			DEX_DelPBDData (TM);
			DEXN_PBDMCodeChanged (lMCode);
		}
	}

// Idents selbst behandeln (Merkmal löschen)
	WriteTextMerkmal (TT_Identifikator, lIdent, pDVD -> lMCode, NULL);
	return true;	// immer weitermachen
}

bool CVisObjExtension::HandleDeleteSight (char *pView)
{
	if (m_lSichtVisMCode == -1L) {
		m_lSichtVisMCode = GetViewMCode (false);
		if (m_lSichtVisMCode == -1L) 
			return false;		// keine VisMWerte 
	}
	
// MerkmalsCode für Objekt sicherstellen
long lMCode = GetIdentMCode (false, pView);

	if (-1L == lMCode) 
		return false;	// in dieser Sicht nichts
	
// Alle Identifikatoren/Objekte dieser Sicht enumerieren
DELETEVIEWDATA DVD;

	DVD.pcView = (LPCSTR)pView;
	DVD.lMCode = lMCode;

ENUMTEXTKEY ETK;

	ETK.eKey = pView;
	ETK.eFcn = (ENUMTEXTKEYPROC)HandleIdentOnDeleteSight;
	ETK.ePtr = &DVD;
	DEX_EnumSightIdents (ETK);

// an Sicht Merkmal löschen
	WriteTextMerkmal (TT_Sicht, (DWORD)pView, m_lSichtVisMCode, NULL);

	return false;		// Notification immer weiterreichen
}

///////////////////////////////////////////////////////////////////////////////
// MerkmalsCodes sicherstellen und Identifikator behandeln 
bool CVisObjExtension::AdjustIdentifier (
	long lIdent, DWORD iMode, DWORD iObjTypBits, bool fSet, 
	bool *pfFirst, const char *pView)
{
// MerkmalsCode für Sicht sicherstellen
	if (m_lSichtVisMCode == -1L) {
		m_lSichtVisMCode = GetViewMCode (pView, true);
		if (m_lSichtVisMCode == -1L) 
			return false;
		if (pfFirst) *pfFirst = true;
	}
		
// MerkmalsCode für Objekt/Identifikator sicherstellen
long lVisMCode = GetIdentMCode (false, pView, lIdent);

	if (lVisMCode == -1L) {
		lVisMCode = GetIdentMCode (true, pView, lIdent);
		if (lVisMCode == -1L) 
			return false;
		if (pfFirst) *pfFirst = true;
	}

// Merkmal an Identifikator generieren
bool iResult = true;
DWORD iOldMode = 0;
long lObjVisMCode = 0L;

	if (fSet) {
	// Setzen einer Information
		if (ReadTextMerkmal (TT_Identifikator, lIdent, lVisMCode, m_pMWert, -1, pView)) 
			iOldMode = StringToIdMode (m_pMWert, &lObjVisMCode);

	DWORD iNewMode = iMode | iOldMode | GetObjectModeBits(iObjTypBits, iMode) | OVObjectTypeUsed;
	char *pIdM = IdModeToString (iNewMode, lObjVisMCode);

		if (iNewMode != iOldMode) {
			iResult = WriteTextMerkmal (TT_Identifikator, lIdent, lVisMCode, pIdM, pView);
			if (pfFirst) *pfFirst = true;	// erstes Objekt mit diesem Ident
		}
		DELETE_OBJ (pIdM);
	} 
	else {
	// Rücksetzen einer Information
		if (ReadTextMerkmal (TT_Identifikator, lIdent, lVisMCode, m_pMWert, -1, pView) &&
			(iMode & (iOldMode = StringToIdMode (m_pMWert, &lObjVisMCode))) )
		{
			iOldMode &= ~GetObjectModeBits(iObjTypBits, iMode);		// gewünschten Objekttyp rücksetzen

			if (!(iOldMode & OVObjectTypeUsed) || 
				iOldMode & GetObjectModeBits(OTPunkt|OTLinie|OTFlaeche|OTText, OVModVisInfo|OVModShow) ) 
			{
			// Objekttypen nicht genutzt (alte DB) oder noch existieren Objekttypen, die Visualisiert sind
			char *pIdM = IdModeToString (iOldMode | iMode, lObjVisMCode);

				iResult = WriteTextMerkmal (TT_Identifikator, lIdent, lVisMCode, pIdM, pView);
				DELETE_OBJ (pIdM);
			} else {
			// keine objektbezogen visualisierten Objekttypen mehr für diesen Ident --> löschen
				iResult = WriteTextMerkmal (TT_Identifikator, lIdent, lVisMCode, NULL, pView);	// löschen
			}
		}
	}
	return iResult;
}


// Funktion, die exportiert wird, um von außen diese Erweiterung zu nutzen ----
extern "C" 
bool PASCAL _XTENSN_EXPORT ChangeVisInfo (HANDLEVISINFO *pHVI, char **cbModuleInfo)
{
// Identifikator und ObjektNummer sicherstellen
	if (pHVI -> m_lIdent == 0) {
		if (pHVI -> m_lONr != 0)
			pHVI -> m_lIdent = DEX_GetObjIdent (pHVI -> m_lONr);
	} 
	if (pHVI -> m_lONr == 0)
		return false;
		
bool iResult = false;
CVisObjExtension *pE = (CVisObjExtension *)g_pTE;

	if (pE == NULL) return false;		// DLL nicht initialisiert

int iObjTypBit = VTypToOTyp(pHVI -> m_iVTyp);

	if (!pE -> AdjustIdentifier (pHVI -> m_lIdent, OVModVisInfo, iObjTypBit, true, NULL, pHVI -> m_pView))
		return false;

// alles ok, Merkmal (VisInfo) am Objekt generieren
char *pObjM = VisInfoToString (pHVI, pE -> m_fFullVisInfo, &pE -> RF(), true, NULL, false, cbModuleInfo);
	
	iResult = WriteTextMerkmal (TT_Objekt, pHVI -> m_lONr, pE -> GetObjMCode(true, pHVI -> m_pView, DEX_GetObjIdent(pHVI -> m_lONr)), pObjM);
	DELETE_OBJ (pObjM);
	
	return iResult;
}

// BehandlungsRoutinen für HANDLEVISINFO --------------------------------------
HANDLEVISINFO *ctHANDLEVISINFO (short iVTyp, bool fExtended)
{
HANDLEVISINFOEX *pHVI = NULL;
VISINFO *pVI = NULL;

	if (fExtended) {
		ATLTRY(pHVI = new HANDLEVISINFOEX);
		if (pHVI == NULL) return NULL;

		memset (pHVI, '\0', sizeof(HANDLEVISINFOEX));
		pHVI -> dwSize = sizeof (HANDLEVISINFOEX);
	}
	else {
		ATLTRY(pHVI = (HANDLEVISINFOEX *)new HANDLEVISINFO);
		if (pHVI == NULL) return NULL;

		memset (pHVI, '\0', sizeof(HANDLEVISINFO));
		pHVI -> dwSize = sizeof (HANDLEVISINFO);
	}
		
	switch (iVTyp) {
	case VTPunkt:
		ATLTRY(pVI = (VISINFO *)new PVISINFO);
		if (pVI) {
			memset (pVI, '\0', sizeof(PVISINFO));
			pVI -> dwSize = sizeof(PVISINFO);
		}
		break;
		
	case VTLinie:
		ATLTRY(pVI = (VISINFO *)new LVISINFO);
		if (pVI) {
			memset (pVI, '\0', sizeof(LVISINFO));
			pVI -> dwSize = sizeof(LVISINFO);
		}
		break;
		
	case VTFlaeche:
		ATLTRY(pVI = (VISINFO *)new FVISINFO);
		if (pVI) {
			memset (pVI, '\0', sizeof(FVISINFO));
			pVI -> dwSize = sizeof(FVISINFO);
		}
		break;
		
	case VTText:
		ATLTRY(pVI = (VISINFO *)new TVISINFO);
		if (pVI) {
			memset (pVI, '\0', sizeof(TVISINFO));
			pVI -> dwSize = sizeof(TVISINFO);
		}
		break;

	default:
	case VTDefault:
		ATLTRY(pVI = (VISINFO *)new DVISINFO);
		if (pVI) {
			memset (pVI, '\0', sizeof(DVISINFO));
			pVI -> dwSize = sizeof(DVISINFO);
		}
		break;
	}
	if (pVI == NULL) {
		DELETE_OBJ (pHVI);
		return NULL;
	}

	pVI -> m_fVisible = true;
	pVI -> m_fLocatable = true;

	pHVI -> m_iVTyp = iVTyp;
	pHVI -> m_pVI = pVI;
	return (HANDLEVISINFO *)pHVI;
}


// Destruktor für HANDLEVISINFO -----------------------------------------------
void dtHANDLEVISINFO (HANDLEVISINFO *& pHVI)
{
	if (pHVI) {
		DELETE_OBJ (pHVI -> m_pVI);
		if (pHVI -> dwSize == sizeof(HANDLEVISINFOEX)) {
		HANDLEVISINFOEX *pHVIEx = (HANDLEVISINFOEX *)pHVI;

			DELETE_OBJ(pHVIEx -> m_pModule);
			DELETE_OBJ(pHVIEx -> m_pInfo);
		}
		DELETE_OBJ (pHVI);
	}
}


// WrapperFunktion, die die Komplexität des Prozesses versteckt --------------
bool CVisObjExtension::RebuildSight (void)
{
	m_fRebuildView = false;
	if (!DEX_RebuildSight()) {	// Fehler oder es wird gezeichnet
		if (m_fIsDrawing) {
//			RegisterNotification (DEX_PAINTTOPLAYER);
			m_fRebuildView = true;		// nochmal versuchen
			return false;
		}
	}
	return true;
}
