// FarbregelungsDialog --------------------------------------------------------
// File: COLCNTRL.CXX

#include "visobjp.hxx"

#include <protos.h>
#include <rgb_hsb.hxx>

#include "obj32/visres32.h"
#include "visobj.h"
#include "colcntrl.h"

#include "visobj.hxx"		// Klasse für diese Erweiterung
#include "colcntrl.hxx"

// MenuFunktion ---------------------------------------------------------------
bool CVisObjExtension::ControlColors (void) 
{
// Fenster anlegen
	m_CCDlg = new CColorControlDlg (MVWind(), &RF());
	if (m_CCDlg == NULL) return false;
		
	if (!m_CCDlg -> Init()) {
		DELETE_OBJ
		 (m_CCDlg);
		return false;	// Fehler bei der Initialisierung
	}
	m_CCDlg -> Show();		// Dialogfenster anzeigen

bool iResult = m_CCDlg -> Result();	

	DELETE_OBJ (m_CCDlg);		// Speicher freigeben
	return iResult;
}


// Konstruktor/Destruktor -----------------------------------------------------
#pragma warning (disable: 4355)

CColorControlDlg::CColorControlDlg (pWindow pW, ResourceFile *pRF)
		  : DialogWindow (pW, ResID (COLORCONTROLDLG, pRF)),
		    m_rbSatAll (this, IDR_ALLSAT),
		    m_rbSatSmaller (this, IDR_SMALLERSAT),
		    m_rbSatBigger (this, IDR_BIGGERSAT),
		    m_sbAbsSat (this, IDSB_ABSSAT),
		    m_sleAbsSat (this, IDE_ABSSAT, Range (0, 100)),
		    m_rbBright (this, IDR_BRIGHTNESS),
		    m_rbInvBright (this, IDR_NEGBRIGHTNESS),
		    m_sbBright (this, IDSB_RELBRIGHTNESS),
		    m_sleBright (this, IDE_RELBRIGHTNESS, Range (0, 100)),
		    m_Preview (this, IDC_PREVIEW),
		    m_rRF (*pRF)
{
// links unten positionieren
Rectangle rcP = pW -> CanvasRect();
Rectangle rcMe = WindowRect();

	ChangePosition (Point (rcP.Right()-rcMe.Width(), rcP.Top()-rcMe.Height()));
		
// SättigungsControls
	m_rbSatAll.SetState (false);
	m_rbSatSmaller.SetState (false);
	m_rbSatBigger.SetState (true);
	
	m_sbAbsSat.SetRange (Range (0, 100));
	m_sbAbsSat.SetThumbPos (100);
	m_sleAbsSat.SetText ("100");
	
// HelligkeitsControls
	m_rbBright.SetState (true);
	m_rbInvBright.SetState (false);

	m_sbBright.SetRange (Range (0, 100));
	m_sbBright.SetThumbPos (100);
	m_sleBright.SetValue (100);
	
// sonstige Variablen initialisieren
	m_enPalAction = PAL_NOACTION;
	m_hPal = 0;
	m_hOldPal = 0;
	m_pBuff = NULL;
	
	m_nEntries = 0;
	m_pHSB = NULL;
	m_pPal = NULL;
}

#pragma warning (default: 4355)

bool CColorControlDlg::Init (void)
{
// lokalen SpeicherBereich reservieren
	m_pBuff = new char [_MAX_PATH];
	if (m_pBuff == NULL) 
		return false;

// neu zeichnen lassen, um Palette zu bekommen
	m_enPalAction = PAL_BEGINANIMATION;
	((CVisObjExtension *)g_pTE) -> RebuildSight();

// AnfangsSättigung setzen
	SetSat (100);
	return true;
}


CColorControlDlg::~CColorControlDlg (void)
{
// Speicher wieder freigeben
	DELETE_OBJ (m_pBuff);
	if (m_hOldPal) 
		DeleteObject (m_hOldPal);
	if (m_pPal) {
		delete (char *)m_pPal;
		m_pPal = NULL;
	}
	DELETE_OBJ (m_pHSB);

	((CVisObjExtension *)g_pTE) -> RebuildSight();	// Sicht neu enlesen und aufbauen
}


bool CColorControlDlg::SetNewPalette (HPALETTE hPal)
{
	switch (m_enPalAction) {
	case PAL_BEGINANIMATION:
		DELETE_OBJ (m_pHSB);
		if (m_hOldPal) DeleteObject (m_hOldPal);

		m_hOldPal = CopyPalette (hPal);		// alte Palette merken
		m_hPal = hPal;				// neue Palette merken

		m_enPalAction = PAL_COPYPALETTE;

		m_pPal = InitPalEntries (hPal);
		m_pHSB = InitHSBValues();
		return PaletteAnimation (hPal);		// Animation vorbereiten

	case PAL_COPYPALETTE:
		return PaletteAnimation (hPal);
		
	case PAL_NOACTION:				// ignore PaletteRequest
	default:
		break;
	}
	return true;
}


void _XTENSN_EXPORT CColorControlDlg::HorizScroll (ScrollEvt e)
{
ScrollBar *pSB = e.GetScrollBar();
short iVal = 0;

	switch ((uint)pSB -> GetID()) {
	case IDSB_RELBRIGHTNESS:
		{
			iVal = e.GetPos();
			m_sleBright.SetValue(iVal);
			m_sbBright.SetThumbPos (iVal);
			ControlBright (iVal, m_rbBright.GetState());
		}
		break;
		
	case IDSB_ABSSAT:
		{
			iVal = e.GetPos();
			m_sleAbsSat.SetValue (iVal);
			m_sbAbsSat.SetThumbPos (iVal);
			SetSat (iVal);
		}
		break;
	}
}

void _XTENSN_EXPORT CColorControlDlg::EditFocusChg (EditFocusChgEvt e)
{
// wenn Focus erhalten, dann raus
	if (e.gotFocus()) return;

short iVal = 0;

	switch ((uint)e.GetControlID ()) {
	case IDE_ABSSAT:
		{
			iVal = m_sleAbsSat.GetValue();
			m_sbAbsSat.SetThumbPos (iVal);
			SetSat (iVal);
		}
		break;

	case IDE_RELBRIGHTNESS:
		{
			iVal = m_sleBright.GetValue();
			m_sbBright.SetThumbPos (iVal);
			ControlBright (iVal, m_rbBright.GetState());
		}
		break;
	}
}

void _XTENSN_EXPORT CColorControlDlg::ButtonClick (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDOK:	// ausgewählte Farben unter aktueller Sicht speichern
		EndDlg (SaveNewColors());
		break;
		
	case IDCANCEL:
		EndDlg (0);	// Abbrechen
		
	case IDB_COLORCONTROLHELP:
		break;		// erst mal keine Hilfe
		
	case IDR_BRIGHTNESS:	// Helligkeit verkleinern
	case IDR_NEGBRIGHTNESS:	// Helligkeit vergrößern
		ControlBright (m_sbBright.GetThumbPos(), m_rbBright.GetState());
		break;

	case IDC_PREVIEW:
		DEX_RePaint();
		break;
				
/*	case IDCB_SAT:		// Sättigung auswerten/nicht auswerten
		if (m_cbSat.isChecked()) {
		short iMSat = GetInitialSat();
		
			m_sbAbsSat.Enable();
			m_sleAbsSat.Enable();
			m_sbAbsSat.SetThumbPos (iMSat);
			m_sleAbsSat.SetValue (iMSat);
			
			SetSat (iMSat);
		} else {
			m_sbAbsSat.Disable();
			m_sleAbsSat.Disable();
			
			ResetSat();
		}
		break;
*/
	case IDR_SMALLERSAT:
	case IDR_ALLSAT:
	case IDR_BIGGERSAT:
		SetSat (m_sbAbsSat.GetThumbPos());
		break;
	}	
}


// Mittlere Sättigung berechnen -----------------------------------------------
/*
short CColorControlDlg::GetInitialSat (void)
{
long iVal = 0L;

	if (m_pHSB == NULL) return 0;
	
	for (short i = 0; i < m_nEntries; i++)
		iVal += GetSValue (m_pHSB[i].lHSB);
		
return iVal / m_nEntries;
}
*/

// eigentliche Animation durchführen ------------------------------------------
void CColorControlDlg::AnimatePalette (void)
{
HWND hWnd = GetParent() -> Handle (API_WINDOW_HWND);
HDC hDC = GetDC (hWnd);
HPALETTE hOldPal = SelectPalette(hDC, m_hPal, FALSE);

//	RealizePalette(hDC);
	::AnimatePalette (m_hPal, 0, m_nEntries, m_pPal -> palPalEntry);
	SelectPalette(hDC, hOldPal, TRUE);
	ReleaseDC (hWnd, hDC);
}


// Sättigung auf einen bestimmten Wert setzen ---------------------------------
void CColorControlDlg::SetSat (short iSat)
{
	if (m_pHSB == NULL) return;

PALETTEENTRY PE;
	
	for (short i = 0; i < m_nEntries; i++) {
		if (!m_pHSB[i].fControl)
			continue;	// Sättigung nicht regeln
			
		GetPaletteEntries (m_hOldPal, i, 1, &PE);
		PE.peFlags = (BYTE)0;
		
	short iOldSat = GetSValue (RGBtoHSB (*(Color *)&PE));
	// nur regeln, wenn Regelungsbedingung erfüllt ist

		if (m_rbSatAll.GetState() ||
		    (m_rbSatBigger.GetState() && iOldSat > iSat) ||
		    (m_rbSatSmaller.GetState() && iOldSat < iSat))
		{
		ulong &rlHSB = m_pHSB[i].lHSB;
		
			rlHSB = HSB ((BYTE)iSat, GetVValue (rlHSB), GetHValue (rlHSB));
	
		Color C = HSBtoRGB (rlHSB);
	
			PE = *(PALETTEENTRY *)&C;
			PE.peFlags = (BYTE)PC_RESERVED;
	
			m_pPal -> palPalEntry[i] = PE;
		}
	}
	AnimatePalette();
}



// Sättigung auf Anfangszustand zurücksetzen ----------------------------------
/*
void CColorControlDlg::ResetSat (void)
{
	if (m_pHSB == NULL) return;

PALETTEENTRY PE;
	
	for (short i = 0; i < m_nEntries; i++) {
		GetPaletteEntries (m_hOldPal, i, 1, &PE);
		PE.peFlags = (BYTE)0;
	
	ulong lOldHSB = RGBtoHSB (*(Color *)&PE);
	ulong &rlHSB = m_pHSB[i].lHSB;
		
		rlHSB = HSB (GetSValue (lOldHSB), GetVValue (rlHSB), GetHValue (rlHSB));

	Color C = HSBtoRGB (rlHSB);

		PE = *(PALETTEENTRY *)&C;
		PE.peFlags = (BYTE)PC_RESERVED;

		m_pPal -> palPalEntry[i] = PE;
	}
	AnimatePalette ();
}
*/

// Helligkeit regeln ----------------------------------------------------------
void CColorControlDlg::ControlBright (short iRelBright, bool fDir)
{
	if (m_pHSB == NULL) return;

	ResetBright();		// auf AnfangsZustand rücksetzen
	
PALETTEENTRY PE;
	
	for (short i = 0; i < m_nEntries; i++) {
	// neue Helligkeit berechnen
	ulong &rlHSB = m_pHSB[i].lHSB;
	short iBright = GetVValue (rlHSB);	
	
		if (fDir) 	// Helligkeit kleiner werden lassen
			iBright = MulDiv (iBright, iRelBright, 100);
		else		// Helligkit vergrößern
			iBright += MulDiv (100-iBright, iRelBright, 100);
			
	// neue Helligkeit einstellen
		rlHSB = HSB (GetSValue (rlHSB), (BYTE)iBright, GetHValue (rlHSB));

	Color C = HSBtoRGB (rlHSB);

		PE = *(PALETTEENTRY *)&C;
		PE.peFlags = (BYTE)PC_RESERVED;

		m_pPal -> palPalEntry[i] = PE;
	}
	
// Palette richten
	AnimatePalette();
}

// Helligkeit auf Anfangszustand zurücksetzen ---------------------------------
void CColorControlDlg::ResetBright (void)
{
	if (m_pHSB == NULL) return;

PALETTEENTRY PE;
	
	for (short i = 0; i < m_nEntries; i++) {
		GetPaletteEntries (m_hOldPal, i, 1, &PE);
		PE.peFlags = (BYTE)0;
	
	ulong lOldHSB = RGBtoHSB (*(Color *)&PE);
	ulong &rlHSB = m_pHSB[i].lHSB;
		
		rlHSB = HSB (GetSValue (rlHSB), GetVValue (lOldHSB), GetHValue (rlHSB));

	Color C = HSBtoRGB (rlHSB);

		PE = *(PALETTEENTRY *)&C;
		PE.peFlags = (BYTE)PC_RESERVED;

		m_pPal -> palPalEntry[i] = PE;
	}
}


// LOGPALETTE anlegen ---------------------------------------------------------
LOGPALETTE *CColorControlDlg::InitPalEntries (HPALETTE hPal)
{
	if (!hPal) return NULL;
	
	if (m_nEntries == 0) {
		GetObject (hPal, sizeof(int), &m_nEntries);
		if (m_nEntries == 0) return NULL;
	}

LOGPALETTE *pPal = (LOGPALETTE *)new char[sizeof(LOGPALETTE) + 
					  m_nEntries*sizeof(PALETTEENTRY)];
	if (!pPal) return NULL;

	pPal->palVersion = 0x300;
	pPal->palNumEntries = m_nEntries;
	GetPaletteEntries (hPal, 0, m_nEntries, pPal -> palPalEntry);
	return pPal;
}

// internes Feld der HSB-Werte initialisieren ---------------------------------
HSBDATA *CColorControlDlg::InitHSBValues (void)
{
	if (m_nEntries == 0 || m_pPal == NULL) 
		return NULL;
	
// Speicher anfordern
HSBDATA *pHSB =  new HSBDATA [m_nEntries];

	if (pHSB == NULL) return NULL;

	for (short i = 0; i < m_nEntries; i++) {
	PALETTEENTRY PE = m_pPal -> palPalEntry[i];
	ulong &rlHSB = pHSB[i].lHSB;
		
		PE.peFlags = (BYTE)0;
		rlHSB = RGBtoHSB (*(Color *)&PE);
		pHSB[i].fControl = (GetSValue (rlHSB) != 0);
	}
	return pHSB;
}

bool CColorControlDlg::PaletteAnimation (HPALETTE hPal)
{
	if (!hPal || m_nEntries == 0 || m_pPal == NULL)
		return false;

// Reserve all entries in the palette otherwise AnimatePalette()
// will not modify them
	for (short i = 0; i < m_nEntries; i++)
		m_pPal -> palPalEntry[i].peFlags = (BYTE)PC_RESERVED;

	SetPaletteEntries (hPal, 0, m_nEntries, m_pPal -> palPalEntry);

return true;
}

// Neue Farben permanent in der aktuellen Sicht abspeichern -------------------
typedef struct tagREMAPDATA {
	CColorControlDlg *m_pCCDlg;
	char *m_pView;
} REMAPDATA;

extern "C" 
BOOL PASCAL _XTENSN_EXPORT RemapViewEntryColors (long lIdent, BOOL, void *pData)
{
CColorControlDlg *pCCDlg = ((REMAPDATA *)pData) -> m_pCCDlg;
char *pView = ((REMAPDATA *)pData) -> m_pView;

	pCCDlg -> RemapEntry (lIdent, VTPunkt, pView);
	pCCDlg -> RemapEntry (lIdent, VTLinie, pView);
	pCCDlg -> RemapEntry (lIdent, VTFlaeche, pView);
	pCCDlg -> RemapEntry (lIdent, VTText, pView);
	
return true;
}

bool CColorControlDlg::SaveNewColors (char *pView)
{
// aktuelle Sicht besorgen
	if (pView == NULL) {
		DEX_GetActiveSight (m_pBuff);
		if (*m_pBuff == '\0')
			return false;
	} else
		strcpy (m_pBuff, pView);
			
// alle Identifikatoren der aktuellen Sicht enumerieren und Farben ummappen
ENUMTEXTKEY ETK;
REMAPDATA RD;

	RD.m_pCCDlg = this;
	RD.m_pView = m_pBuff;
	
	ETK.eKey = m_pBuff;
	ETK.eFcn = (ENUMTEXTKEYPROC)RemapViewEntryColors;
	ETK.ePtr = &RD;

	return DEX_EnumSightIdents (ETK);
}


// Einen Eintrag der Sicht ummappen -------------------------------------------
inline void CColorControlDlg::RemapColor (COLORREF &rC)
{
WORD iIndex = GetNearestPaletteIndex (m_hOldPal, rC);

	GetPaletteEntries (m_hPal, iIndex, 1, (PALETTEENTRY *)&rC);
	rC = RGB (GetRValue(rC), GetGValue(rC), GetBValue (rC));
}


bool CColorControlDlg::RemapEntry (long lIdent, short iVTyp, char *pView)
{
// VisInfo besorgen
HANDLEVISINFO *pHVI = GetIdentVisInfo (lIdent, iVTyp, pView);

	if (pHVI != NULL) {		// VisInfo existiert, also ummappen
	// PrimärFarbe mappen
		RemapColor (pHVI -> m_pVI -> m_C);
		if (iVTyp == VTFlaeche) 	// FüllFarbe mappen
			RemapColor (((FVISINFO *)(pHVI -> m_pVI)) -> m_FC);

	// VisInfo wieder wegschreiben
		DEX_ModIdentVisInfo (*pHVI);
		dtHANDLEVISINFO (pHVI);		// Speicher freigeben
	}
	return false;
}


// Palette kopieren -----------------------------------------------------------
HPALETTE CopyPalette (HPALETTE hPal) 
{
	if (!hPal) return 0;

int nEntries = 0;

	GetObject (hPal, sizeof(int), &nEntries);
	if (nEntries == 0) return 0;

LOGPALETTE *pPal = (LOGPALETTE *)new char[sizeof(LOGPALETTE) + 
					  nEntries*sizeof(PALETTEENTRY)];
	if (!pPal) return NULL;

	pPal->palVersion = 0x300;
	pPal->palNumEntries = nEntries;
	GetPaletteEntries (hPal, 0, nEntries, pPal -> palPalEntry);

// Palette anlegen
	hPal = CreatePalette (pPal);

	DELETE_OBJ (pPal);
	return hPal;
}


