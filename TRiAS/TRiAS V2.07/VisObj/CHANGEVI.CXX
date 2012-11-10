// Abaendern von Visualisierungsinformationen fuer einzelne Objekte -----------
// File: CHANGEVI.CXX

#include "visobjp.hxx"

#include <bmpbox.hxx>
#include <rgb_hsb.hxx>
#include <objcontx.hxx>
#include <viserror.hxx>

#include "visobj.h"	// ResourceKonstanten für dieses Beispiel
#include "defabout.h"
#include "viserrdg.h"
#include "resource.h"

#include "visobj.hxx"		// Klasse für diese Erweiterung
#include "viserrdg.hxx"

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

extern "C" {

typedef struct tagOBJCHANGEDATA {
	HANDLEVISINFO *m_pHVI;
	bool m_fFirst;
} OBJCHANGEDATA;

// VisInfo für ein Objekt neu einstellen --------------------------------------
BOOL _XTENSN_EXPORT PASCAL ObjChangeVisInfo (long lONr, BOOL, void *pData)
{
short Status = DEX_GetObjectStatus (lONr);

	if (Status != OSNormal && Status != OSModified) 
	// Objekt existiert nicht oder ist temporär
		return true;	// weitermachen

// VisInfo nur neu einstellen, wenn Objekttyp übereinstimmt
OBJCHANGEDATA *pOCD = (OBJCHANGEDATA *)pData;
HANDLEVISINFO *pHVI = pOCD -> m_pHVI;

	if (OTypToVTyp (DEX_GetObjectType(lONr)) != pHVI -> m_iVTyp)
		return true;	// weitermachen

	pHVI -> m_lONr = lONr;
	pHVI -> m_lIdent = DEX_GetObjIdent (lONr);
	
return ((CVisObjExtension *)g_pTE) -> ModObjectVisInfo (pHVI, pOCD -> m_fFirst);
}

typedef struct tagOBJHIDEDATA {
	bool m_fShow;
	bool m_fFirst;
} OBJHIDEDATA;

BOOL _XTENSN_EXPORT PASCAL ObjHideVisInfo (long lONr, BOOL, void *pData)
{
short Status = DEX_GetObjectStatus (lONr);

	if (Status != OSNormal && Status != OSModified) 
	// Objekt existiert nicht oder ist temporär
		return true;	// weitermachen

OBJHIDEDATA *pOHD = (OBJHIDEDATA *)pData;

return ((CVisObjExtension *)g_pTE) -> HandleHiddenFlag (lONr, pOHD -> m_fShow, pOHD -> m_fFirst);
}

}	// extern "C"


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
char pDesc[65];
short iCnt = 0;

	DEXOR_SelectedObjectsCount (hORWnd, &iCnt); 
	if (iCnt > 1)
		strcpy (pDesc, ResString (ResID (IDS_ALLOBJCAPTION, &RF()), 64));
	else
		wsprintf (pDesc, ResString (ResID (IDS_OBJECTCAPTION, &RF()), 20), lActObj);

	pHVI -> m_pDesc = pDesc;
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
		ObjContainer OC;
		Rectangle CRc = MWind() -> CanvasRect();

			DEX_GetObjContainer (lActObj, OC);	// Container besorgen

		Rectangle Rc = Rectangle (OC);

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

	if (Status == OSNormal || Status == OSModified) 
	{
	// Objekt existiert und ist nicht temporär: VisInfoMerkmal löschen	
		((CVisObjExtension *)g_pTE) -> ResetObjectVisInfo (lONr);
	}
	return true;
}

// VisInfo für selektiertes/aktivierte Objekt(e) rücksetzen -------------------
bool CVisObjExtension::ResetVisInfo (HWND hORWnd)
{
// MerkmalsCode für Objekt/Identifikator sicherstellen
	if (m_lObjVisMCode == -1L) return false;

// VisInfo für selektiertes/aktivierte Objekte weglöschen
short iCnt = 0;

	DEXOR_SelectedObjectsCount (hORWnd, &iCnt);
	if (iCnt > 1) {
	// alle selektierten behandeln
	ENUMLONGKEY ELK;
	
		ELK.eKey = (long)hORWnd;
		ELK.eFcn = (ENUMLONGKEYPROC)ObjResetVisInfo;
		ELK.ePtr = &m_lObjVisMCode;
		DEX_EnumSelectedObjects (ELK);
		
		DEX_RePaintWait();	// alles neu zeichnen
	} else 	{	
	// Objekt feststellen
	long lActObj = DEX_GetActiveObject (hORWnd);
        
		if (lActObj == -1) return false;
		
	short Status = DEX_GetObjectStatus (lActObj);

		if (Status != OSNormal && Status != OSModified) 
		// Objekt existiert nicht oder ist temporär
			return false;

	// lediglich aktiviertes Objekt behandeln
		ResetObjectVisInfo (lActObj);
		
	// dieses Objekt neu zeichnen lassen
	ObjContainer OC;
	Rectangle CRc = MWind() -> CanvasRect();

		DEX_GetObjContainer (lActObj, OC);	// Container besorgen

	Rectangle Rc = Rectangle (OC);

		Rc.Top() = CRc.Top() - CRc.Bottom() - Rc.Top();
		Rc.Bottom() = CRc.Top() - CRc.Bottom() - Rc.Bottom();
		DEX_RePaintRectWait (Rc);
	}

return true;
}

 
// Visualisierungsfehler für Punkt/Linie/Fläche/Text bearbeiten ---------------
// Result:	1 - ok, try again
//		2 - ok, do not try again
//		0 - cancel
short CVisObjExtension::HandleVisInfoError (CVisError *pCVE)
{
// wenn alle diesbezüglichen Fehler ignoriert werden soll dann sofort wieder raus
	if (m_fAllVisErrIgnore) return 2;

// überprüfen, ob wir diesen Ident bereits kennen
long lIdent = pCVE -> m_lIdent;
short iVTyp = pCVE -> m_iVTyp;

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

	case 3:		// im weiteren ignorieren
		m_pVIE -> FAddItem (lIdent, iVTyp, m_pActSight);
		break;

	case 4:		// im weiteren alles ignorieren
		m_fAllVisErrIgnore = true;
		break;

	case 0:			// Cancel
		break;
	}

	m_lIdentHandled = -1L;		// kein Ident mehr behandelt
	iResult = 2;			// ok, do not try again

return iResult;	
}


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
		
return iResult;	// ok, error handled
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


// Besorgen der aktuellen VisInfo eines Objektes ------------------------------
HANDLEVISINFO *GetObjectVisInfo (long lONr, char *pView, long lMCode, 
				 char **cbModuleInfo, short fFlags)
{
// typgerechte VISINFO-Struktur anfordern
short iOTyp = DEX_GetObjectType (lONr);
HANDLEVISINFO *pHVI = ctHANDLEVISINFO (OTypToVTyp (iOTyp));

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
	pHVI -> m_fFlags = 
		((CVisObjExtension *)g_pTE) -> GetNewVI (pHVI, lMCode, 
						       fFlags, cbModuleInfo);
	pHVI -> m_fFlags |= DT_CustomVisualisation;
	
return pHVI;
}


// Generieren aller Informationen für eine objektbezogene Visualisierung ------
bool CVisObjExtension::ModObjectVisInfo (HANDLEVISINFO *pHVI, bool &fFirst)
{
bool iResult = false;

// MerkmalsCodes sicherstellen und Identifikator behandeln
int iObjTypBit = VTypToOTyp(pHVI -> m_iVTyp);

	if (AdjustIdentifier (pHVI -> m_lIdent, OVModVisInfo, iObjTypBit, true, &fFirst)) {
	// alles ok, Merkmal (VisInfo) am Objekt generieren
	char *pObjM = VisInfoToString (pHVI, m_fFullVisInfo, &RF()); 	// immer RGB !
	long lMCode = GetObjMCode (false, pHVI -> m_pView);

		iResult = WriteTextMerkmal (TT_Objekt, pHVI -> m_lONr, lMCode, pObjM);
		DELETE_OBJ (pObjM);
	}
	
return iResult;
}

///////////////////////////////////////////////////////////////////////////////
// Rücksetzen einer objektbezogenen Visualisierung
bool CVisObjExtension::ResetObjectVisInfo (long lONr, LPCSTR pView)
{
long lMCode = GetObjMCode (false, (char *)pView);

	if (-1 == lMCode) {
		if (NULL != pView)
			return false;
		lMCode = m_lObjVisMCode;
		if (-1 == lMCode) 
			return false;
	}

	return WriteTextMerkmal (TT_Objekt, lONr, lMCode, NULL);
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
		iResult = WriteTextMerkmal (TT_Objekt, lONr, m_lObjVisMCode, pVStr);
	}
	
return iResult;
}


bool ReadTextMerkmal (short iTTyp, long lTarget, long lMCode, char *pText, int iLen)
{
TARGETMERKMAL gm;

	gm.dwSize = sizeof(TARGETMERKMAL);
	gm.lTarget = (LPARAM)lTarget;
	gm.lMCode = lMCode;
	gm.imaxLen = (iLen != -1) ? iLen-1 : (pText != NULL ? MWERTSIZE-2 : 0);
	gm.pMText = pText;
	gm.iTTyp = iTTyp;
	if (DEX_GetTextMerkmal (gm) == NULL)
		return false;

return true;
}

bool WriteTextMerkmal (short iTTyp, long lTarget, long lMCode, char *pText)
{
TARGETMERKMAL gm;

	gm.dwSize = sizeof(TARGETMERKMAL);
	gm.lTarget = (LPARAM)lTarget;
	gm.lMCode = lMCode;
	gm.imaxLen = pText != NULL ? strlen (pText) : 0;
	gm.pMText = pText;
	gm.iTTyp = iTTyp;
	if (DEX_ModTextMerkmal (gm) != EC_OKAY)
		return false;

return true;
}


// Generieren des Identifikatormerkmales zur Kennzeichnung, daß Objekte mit 
// diesem Identifikator objektbezogen visualisiert werden sollen
/* static */
char *CVisObjExtension::IdModeToString (long /* lIdent */, DWORD iMode)
{
char *pResult = new char [40];

	if (pResult) 
		ltoa (DT_HasNewVI | iMode, pResult, 10);
	return pResult;
}


// Interpretation des Identifikatormerkmales, welches über die objektbezogene 
// Visualisierung der Objekte mit diesem Identifikator wacht
/* static */
DWORD CVisObjExtension::StringToIdMode (char *pMText, long /* lIdent */)
{
	if (pMText) 
		return DWORD(atol (pMText));
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
	if ((fFlags & DT_WillDrawComplete) && 
	    (cbModuleInfo && cbModuleInfo[0] && cbModuleInfo[1]))
	{
		if (*cbModuleInfo[1] == '%') {	// v="%s":%s;
			wsprintf (EOS(pR), ResString (ResID (IDS_CUSTOMVISINFO1, pRF), 20),
				  cbModuleInfo[0], cbModuleInfo[1]);
		} else {			// v="%s":"%s";
			wsprintf (EOS(pR), ResString (ResID (IDS_CUSTOMVISINFO2, pRF), 20),
				  cbModuleInfo[0], cbModuleInfo[1]);
		}
	}
			   
// abschließende Klammer und Tag ausgeben
	strcat (pR, ResString (ResID (IDS_TRAILER, pRF), 13));
	if (fFlags & DO_Tagged && !(fFlags & DT_WillDrawComplete))
		strcat (pR, ResString (ResID (IDS_TAG, pRF), 13));
			
return pR;
}


// HiddenFlag hinzufügen ------------------------------------------------------
bool CVisObjExtension::HandleHiddenFlag (long lONr, bool fShow, bool &fFirst)
{
// MerkmalsCode für Objekt/Identifikator sicherstellen
long lIdent = DEX_GetObjIdent (lONr);
int iObjTypBit = OTypToBits(DEX_GetObjectType(lONr));

	if (!AdjustIdentifier (lIdent, OVModShow, iObjTypBit, !fShow, &fFirst))
		return false;

	if (ReadTextMerkmal (TT_Objekt, lONr, m_lObjVisMCode, m_pMWert)) {
	// VisualisierungsMerkmal existiert bereits
	char *pPtr = strchr (m_pMWert, '}');
	
		if (pPtr != NULL) {
			if (!fShow) 
				strcpy (pPtr +1, ResString (ResID (IDS_TAG, &RF()), 13));
			else 
				*(pPtr+1) = '\0';	// Tag wegknacken
			WriteTextMerkmal (TT_Objekt, lONr, m_lObjVisMCode, m_pMWert);
			return true;
		} else if (fShow) {
			WriteTextMerkmal (TT_Objekt, lONr, m_lObjVisMCode, NULL);
			return true;
		}			
	} 
	if (!fShow) {
		WriteTextMerkmal (TT_Objekt, lONr, m_lObjVisMCode, 
			  (char *)ResString (ResID (IDS_TAG, &RF()), 13).Addr());
	}
	
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// HiddenFlag für eine Ansicht behandlen
bool CVisObjExtension::HandleHiddenFlag (long lONr, bool fShow, bool &fFirst, LPCSTR pcView)
{
// MerkmalsCode für Objekt/Identifikator sicherstellen
long lIdent = DEX_GetObjIdent (lONr);
long lObjVisMCode = GetObjMCode(true, (LPSTR)pcView);
int iObjTypBit = OTypToBits(DEX_GetObjectType(lONr));

	if (-1 == lObjVisMCode)
		return false;
	if (!AdjustIdentifier (lIdent, OVModShow, iObjTypBit, !fShow, &fFirst))
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
	if (!fShow) {
		WriteTextMerkmal (TT_Objekt, lONr, lObjVisMCode, 
			  (char *)ResString (ResID (IDS_TAG, &RF()), 13).Addr());
	}
	return true;
}

bool CVisObjExtension::GetHiddenFlag (long lONr, bool &rfShow, LPCSTR pcView)
{
// MerkmalsCode für Objekt/Identifikator sicherstellen
long lIdent = DEX_GetObjIdent (lONr);
long lObjVisMCode = GetObjMCode(true, (LPSTR)pcView);

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
	if (m_lObjVisMCode == -1) 
		return false;	// nicht modifizieren, diese Sicht enthält nichts
		
	if (GetIDMode (pRO -> lIdent) == DT_Normal) 
		return false;	// dieser Ident enthält nichts
		
VisInfo *pVI = NULL;
char *pText = pRO -> lpText;
short iDrawStatus = GetNewVI (pRO -> lONr, pVI, true, -1L, DF_Analyze);

// Speicher freigeben
	DELETE_OBJ (pVI);

// Objekt wird über VisModule symbolisiert
	if (iDrawStatus & DT_WillDrawComplete) return false;
	if (iDrawStatus & DT_NoDrawing) {
	// Objekt ist Hidden
		if (pText) {
		int iLen = int(strlen (pText));

			iLen = min(iLen+1, pRO -> iTextLen);
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
bool CVisObjExtension::ShowObjects (HWND hORWnd, bool fHide)
{
// VisInfo für selektiertes/aktivierte Objekte weglöschen
short iCnt = 0;
OBJHIDEDATA HOD;

	HOD.m_fShow = fHide;
	HOD.m_fFirst = false;
	
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
	} else {	
	// Objekt feststellen
	long lActObj = DEX_GetActiveObject (hORWnd);
        
		if (lActObj == -1) return false;
		
	// lediglich aktiviertes Objekt behandeln
		ObjHideVisInfo (lActObj, false, &HOD);

		if (HOD.m_fFirst)
			RebuildSight();		// alles neu zeichnen, neu aufbauen
		else if (!m_fShowHidden) {		
		// dieses Objekt neu zeichnen lassen
		ObjContainer OC;
		Rectangle CRc = MWind() -> CanvasRect();

			DEX_GetObjContainer (lActObj, OC);	// Container besorgen

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
long lMCode = ((CVisObjExtension *)g_pTE) -> GetObjMCode (false, (char *)pVC -> m_pTarget);
char cbBuffer[_MAX_PATH+1];

	if (!ReadTextMerkmal (TT_Objekt, lONr, lMCode, cbBuffer))
		return true;		// Objekt hat keine Extra's

// ObjVisInfo lesen und an neuer Sicht ablegen
char *cbModuleInfo[2];

	cbModuleInfo[0] = cbModuleInfo[1] = NULL;

HANDLEVISINFO *pHVI = GetObjectVisInfo (lONr, (char *)pVC -> m_pTarget, lMCode, 
					cbModuleInfo);
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

bool HandleViewCreatedIdentEx (long lIdent, VIEWCREATED *pVC, short iVTyp, short iOTyp)
{
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
		HandleViewCreatedIdentEx (lIdent, (VIEWCREATED *)pData, VTPunkt, OTPunkt);
	if (dwData & OTLinie)
		HandleViewCreatedIdentEx (lIdent, (VIEWCREATED *)pData, VTLinie, OTLinie);
	if (dwData & OTFlaeche)
		HandleViewCreatedIdentEx (lIdent, (VIEWCREATED *)pData, VTFlaeche, OTFlaeche);
	if (dwData & OTText)
		HandleViewCreatedIdentEx (lIdent, (VIEWCREATED *)pData, VTText, OTText);

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


// Alle VisMWerte innerhalb dieser Sicht löschen ------------------------------
extern "C" {

BOOL _XTENSN_EXPORT PASCAL HandleIdentOnDeleteSight (long lIdent, BOOL, void *pData)
{
// Idents selbst behandeln (Merkmal löschen)
	WriteTextMerkmal (TT_Identifikator, lIdent, *(long *)pData, NULL);
	return true;	// immer weitermachen
}

}

bool CVisObjExtension::HandleDeleteSight (char *pView)
{
	if (m_lSichtVisMCode == -1L) {
		m_lSichtVisMCode = GetViewMCode (false);
		if (m_lSichtVisMCode == -1L) 
			return false;		// keine VisMWerte 
	}
	
// MerkmalsCode für Objekt sicherstellen
long lMCode = GetObjMCode (false, pView);

	if (lMCode == -1L) return false;	// in dieser Sicht nichts
	
// Alle Identifikatoren dieser Sicht enumerieren
ENUMTEXTKEY ETK;

	ETK.eKey = pView;
	ETK.eFcn = (ENUMTEXTKEYPROC)HandleIdentOnDeleteSight;
	ETK.ePtr = &lMCode;
	DEX_EnumSightIdents (ETK);

// Alle Objekte mit diesem MerkmalsCode enumerieren
ENUMRECHTEXTMERKMAL ERTM;

	INITSTRUCT(ERTM, ENUMRECHTEXTMERKMAL);
	ERTM.pView = NULL;	// es können nur Objekte einer Sicht sein
	ERTM.lMCode = lMCode;
	ERTM.pMWert = NULL;	// alle Objekte
	ERTM.iMode = 0;
	ERTM.eFcn = ObjResetVisInfo;
	ERTM.pData = &lMCode;
	DEX_EnumRechTextMerkmal (ERTM);
	
// an Sicht Merkmal löschen
	WriteTextMerkmal (TT_Sicht, (DWORD)pView, m_lSichtVisMCode, NULL);
	
// MCode aus PBD löschen	
PBDDATA TM;

	INITSTRUCT (TM, PBDDATA);
	TM.pbdTyp = 'm';
	TM.pbdCode = lMCode;
	{
	ErrInstall EI (WC_NOMERKMAL);

		DEX_DelPBDData (TM);
		DEXN_PBDMCodeChanged (lMCode);
	}
	
return false;		// Notification immer weiterreichen
}

///////////////////////////////////////////////////////////////////////////////
// MerkmalsCodes sicherstellen und Identifikator behandeln --------------------
bool CVisObjExtension::AdjustIdentifier (
	long lIdent, DWORD iMode, DWORD iObjTypBits, bool fSet, 
	bool *pfFirst, char *pView)
{
// MerkmalsCode für Sicht sicherstellen
	if (m_lSichtVisMCode == -1L) {
		m_lSichtVisMCode = GetViewMCode (true);
		if (m_lSichtVisMCode == -1L) 
			return false;
		if (pfFirst) *pfFirst = true;
	}
		
// MerkmalsCode für Objekt/Identifikator sicherstellen
long lObjVisMCode = m_lObjVisMCode;

	if (lObjVisMCode == -1L || pView != NULL) {
		lObjVisMCode = GetObjMCode (true, pView, lIdent);
		if (lObjVisMCode == -1L) 
			return false;
		if (pfFirst) *pfFirst = true;
	}
	if (pView == NULL) m_lObjVisMCode = lObjVisMCode;

// Merkmal an Identifikator generieren
bool iResult = true;
DWORD iOldMode = 0;

	if (fSet) {
	// Setzen einer Information
		if (ReadTextMerkmal (TT_Identifikator, lIdent, lObjVisMCode, m_pMWert)) 
			iOldMode = StringToIdMode (m_pMWert);

	DWORD iNewMode = iMode | iOldMode | GetObjectModeBits(iObjTypBits, iMode) | OVObjectTypeUsed;
	char *pIdM = IdModeToString (lIdent, iNewMode);

		if (iNewMode != iOldMode) {
			iResult = WriteTextMerkmal (TT_Identifikator, lIdent, lObjVisMCode, pIdM);
			if (pfFirst) *pfFirst = true;	// erstes Objekt mit diesem Ident
		}
		DELETE_OBJ (pIdM);
	} else {
	// Rücksetzen einer Information
		if (ReadTextMerkmal (TT_Identifikator, lIdent, lObjVisMCode, m_pMWert) &&
			(iMode & (iOldMode = StringToIdMode (m_pMWert))) )
		{
			iOldMode &= ~GetObjectModeBits(iObjTypBits, iMode);		// gewünschten Objekttyp rücksetzen

			if (!(iOldMode & OVObjectTypeUsed) || 
				iOldMode & GetObjectModeBits(OTPunkt|OTLinie|OTFlaeche|OTText, iMode) ) 
			{
			// Objekttypen nicht genutzt (alte DB) oder noch existieren Objekttypen, die Visualisiert sind
			char *pIdM = IdModeToString (lIdent, iOldMode | iMode);

				iResult = WriteTextMerkmal (TT_Identifikator, lIdent, lObjVisMCode, pIdM);
				DELETE_OBJ (pIdM);
			} else {
			// keine objektbezogen visualisierten Objekttypen mehr für diesen Ident --> löschen
				iResult = WriteTextMerkmal (TT_Identifikator, lIdent, lObjVisMCode, NULL);	// löschen
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
	
	iResult = WriteTextMerkmal (TT_Objekt, pHVI -> m_lONr, pE -> GetObjMCode(true, pHVI -> m_pView), pObjM);
	DELETE_OBJ (pObjM);
	
	return iResult;
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
		DELETE_OBJ (pHVI);
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
		DELETE_OBJ (pHVI -> m_pVI);
		DELETE_OBJ (pHVI);
	}
}


// WrapperFunktion, die die Komplexität des Prozesses versteckt --------------
bool CVisObjExtension::RebuildSight (void)
{
	m_fRebuildView = false;
	if (!DEX_RebuildSight()) {	// Fehler oder es wird gezeichnet
		if (DEXI_isDrawing()) {
			RegisterNotification (DEX_PAINTTOPLAYER);
			m_fRebuildView = true;		// nochmal versuchen
			return false;
		}
	}

return true;
}
