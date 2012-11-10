// Einstellung einer Farbpalette ----------------------------------------------
// File: CPALETTE.CXX

#include "tortenp.hxx"

#include <oddlgwin.hxx>
#include <numeditx.hxx>
#include <protos.h> 

#include <icustom.hxx>

#include "impcustm.hxx"
#include "paltree.hxx"
#include "paltree.inl"

#include "cpalette.hxx"
#include "fixupdc.hxx"

#include "torten.h"
#include "typesel.h"		// ResourceKonstanten

#if !defined(WIN32)
#include <tchar.h>
#endif // !WIN32

// lokale FunktionsPrototypen -------------------------------------------------
HANDLEVISINFO *ctHANDLEVISINFO (short iVTyp);
void dtHANDLEVISINFO (HANDLEVISINFO *& pHVI);
OLECHAR *VMDWideString (const char *strIn);

extern "C" char FAR g_pDLLName[];	// Name dieses Modules

// Initialisieren eine Palette ------------------------------------------------
BOOL CVisPalette :: FInit (pChar pPName, LPSTORAGE pIStorage)
{
// PalettenNamen speichern
	m_pPName = new char [MAXPALETTENAMELEN+1];
	if (m_pPName == NULL) return false;
	if (pPName) 
		strcpy (m_pPName, pPName);
	else {
	ResourceFile *pRF = new ResourceFile (g_pDLLName);	// diese DLL
	
		if (pRF == NULL) return false;
		strcpy (m_pPName, ResString (ResID (IDS_DEFAULTPALETTE, pRF), 40));
		DELETE_OBJ (pRF);
	}
	
// wenn Palette nicht geladen werden soll, dann war das alles
	if (!pIStorage) return true;
	
// Palette Laden
HRESULT hr = Load (pIStorage);

	if (FAILED(hr)) return false;
	
return true;
}


// so eine Art Copy-Constructor -----------------------------------------------
BOOL CVisPalette :: FInit (CVisPalette &rVP)
{
// PalettenNamen speichern
	m_pPName = new char [MAXPALETTENAMELEN+1];
	if (m_pPName == NULL) return false;
	strcpy (m_pPName, rVP.m_pPName);
	
// kopieren aller VisInfos
	for (short i = 0; i < MAXPIECOLORS; i++) {
		m_pFVI[i] = (FVisInfo *)rVP.m_pFVI[i] -> Copy();
		if (m_pFVI[i] == NULL) return false;
	}

// Anzahl der Nachkommastellen kopieren
	m_iNumDigits = rVP.GetNumDigits();
			
return true;
}


// Palette aus Storage laden --------------------------------------------------
HRESULT CVisPalette :: Load (LPSTORAGE pIStorage)
{
DWORD dwMode = STGM_DIRECT | STGM_READ | STGM_SHARE_EXCLUSIVE;
LPSTREAM pIStream;	// Stream heißt wie Palette selbst
HRESULT hr = pIStorage -> OpenStream (VMDWideString(m_pPName), 0, dwMode, 0, &pIStream);

	if (FAILED(hr)) return hr;

// laden aller VisInfos
	for (short i = 0; i < MAXPIECOLORS; i++) {
	FVisInfo *pFVI = new FVisInfo (0, 0, BLACK, BLACK, 0);
	
		if (pFVI == NULL) return ResultFromScode (E_OUTOFMEMORY);

		pIStream -> Read (&pFVI -> Style(), sizeof(short), NULL);
		pIStream -> Read (&pFVI -> PrimColor(), sizeof(Color), NULL);
		pIStream -> Read (&pFVI -> SecColor(), sizeof(Color), NULL);
		m_pFVI[i] = pFVI;
	}

// laden der Anzahl der signifikanten Nachkommastellen
ULONG lRead = 0;	// Anzahl der gelesenen Bytes

	pIStream -> Read (&m_iNumDigits, sizeof(short), &lRead);
	if (lRead != sizeof(short))
		m_iNumDigits = 1;	// Default: 1 Nachkommastelle
	
	pIStream -> Release();		// Stream schließen

return NOERROR;
}


// Speichern einer Palette im hauseigenen Storage -----------------------------
HRESULT CVisPalette :: Save (LPSTORAGE pIStorage)
{
DWORD dwMode = STGM_DIRECT | STGM_CREATE | STGM_READWRITE | STGM_SHARE_EXCLUSIVE;
LPSTREAM pIStream;	// Stream heißt wie Palette selbst
HRESULT hr = pIStorage -> CreateStream (VMDWideString(m_pPName), dwMode, 0, 0, &pIStream);

	if (FAILED(hr)) return hr;

// alle VisInfos wegschreiben
	for (short i = 0; i < MAXPIECOLORS; i++) {
	FVisInfo *pFVI = m_pFVI[i];
	
		pIStream -> Write (&pFVI -> Style(), sizeof(short), NULL);
		pIStream -> Write (&pFVI -> PrimColor(), sizeof(Color), NULL);
		pIStream -> Write (&pFVI -> SecColor(), sizeof(Color), NULL);
	}

// Anzahl der gewünschten Nachkommastellen wegschreiben
	pIStream -> Write (&m_iNumDigits, sizeof(short), NULL);
	
	pIStream -> Release();		// Stream schließen

return NOERROR;
}


// Generieren einer StandardPalette -------------------------------------------

extern COLORREF crefPieColors[MAXPIECOLORS];	// Farben der StandardPalette

CVisPalette *CVisPalette :: GetDefaultVisPalette (void)
{
CVisPalette *pCVP = new CVisPalette;

	if (pCVP == NULL || !pCVP -> FInit()) {
		DELETE_OBJ (pCVP);		// wieder freigeben
		return NULL;
	}
	for (short i = 0; i < MAXPIECOLORS; i++) {
	FVisInfo fviT (1, DEF_PRIORITY_FLAECHE, BLACK, *(Color *)&crefPieColors[i], 0);
	
		pCVP -> SetFVisInfo (&fviT, i);
	}
	pCVP -> m_iNumDigits = 1;

return pCVP;
}


static bool ExpandPalette (HPALETTE hPal, VisInfo *pVI);
static HPALETTE CopyPalette (HPALETTE hPal);

BOOL CVisPalette :: RetrievePalette (HPALETTE &hPal)
{
bool fChanged = false;

	if (hPal == 0) {
	// leere Palette bilden
		hPal = CopyPalette ((HPALETTE)GetStockObject (DEFAULT_PALETTE));
		if (hPal == 0) return 0;
	}

// alle Farben dieser CVisPalette in der HPALETTE abbilden und unterbringen
	for (short i = 0; i < MAXPIECOLORS; i++) {
		if (ExpandPalette (hPal, m_pFVI[i]))
			fChanged = true;
	}
	
return fChanged;
}


// Erweitern einer Palette um die in einer VisInfo gegebenen Farben
inline void ConvertPaletteIndex (HPALETTE hPal, Color &C)
{
	if (hPal && C.Reserved() != 0) {
		GetPaletteEntries (hPal, C.Red(), 1, (PALETTEENTRY *)&C);
		C.Reserved() = 0;
	}
}

inline void ConvertColor (HPALETTE hPal, Color &C)
{
	if (hPal && C.Reserved() == 0) {
	PALETTEENTRY *pCRef = (PALETTEENTRY *)&C;
	long lIndex = PALETTEINDEX(GetNearestPaletteIndex (hPal, *(COLORREF *)pCRef));
	
		C = *(Color *)&lIndex;
	}
}

static bool ExpandPalette (HPALETTE hPal, VisInfo *pVI)
{
WORD iNumEntries;

// 1. Größe der Palette festellen
	if (!hPal) return 0;
	GetObject (hPal, sizeof(WORD), (LPSTR)&iNumEntries);
	if (iNumEntries == 0) return false;

PALETTEENTRY PalEntry[2];
int iNewEntries = iNumEntries;

// 2. allgemeine Farbe testen
Color C = pVI -> PrimColor();
VisType VT = pVI -> isA();

	if (VT == VT_Flaeche || VT == VT_Punkt)
		ConvertPaletteIndex (hPal, C);
	
PALETTEENTRY *pCRef = (PALETTEENTRY *)&C;
int iIndex = GetNearestPaletteIndex (hPal, *(COLORREF *)pCRef);

	GetPaletteEntries (hPal, iIndex, 1, &PalEntry[0]);
	if (*(COLORREF *)pCRef != *(COLORREF *)&PalEntry[0]) {
		iNewEntries++;
		*(COLORREF *)&PalEntry[0] = *(COLORREF *)pCRef;
	}

// 3. wenn FlächenVisInfo vorliegt, Füllfarbe testen
	if (pVI -> isA() ==  VT_Flaeche) {
		C = ((FVisInfo *)pVI) -> SecColor();
		ConvertPaletteIndex (hPal, C);

		pCRef = (PALETTEENTRY *)&C;
		iIndex = GetNearestPaletteIndex (hPal, *(COLORREF *)pCRef);

		GetPaletteEntries (hPal, iIndex, 1, &PalEntry[1]);
		if (*(COLORREF *)pCRef != *(COLORREF *)&PalEntry[1]) {
			*(COLORREF *)&PalEntry[iNewEntries-iNumEntries] = *(COLORREF *)pCRef;
			iNewEntries++;
		}
	}

	if (iNewEntries > iNumEntries) {
	// Palette vergrößern
		ResizePalette (hPal, iNewEntries);
		SetPaletteEntries (hPal, iNumEntries, 
				   iNewEntries-iNumEntries, PalEntry);
		return true;
	}

return false;	// Palette wurde nicht erweitert
}


static HPALETTE CopyPalette (HPALETTE hPal) 
{
int nNumEntries;

	if (!hPal) return 0;
	
// Anzahl der PalettenEinträge holen
	GetObject (hPal, sizeof(int), (LPSTR)&nNumEntries);
	if (nNumEntries == 0) return 0;

// temporär Speicher für Palette anlegen
LOGPALETTE *pPal = (LOGPALETTE *)new char [sizeof(LOGPALETTE) + 
					  nNumEntries*sizeof(PALETTEENTRY)];
	if (!pPal) return 0;

// Palette kopieren
	pPal->palVersion = 0x300;
	pPal->palNumEntries = nNumEntries;
	GetPaletteEntries (hPal, 0, nNumEntries, pPal->palPalEntry);

// Palette anlegen
	hPal = CreatePalette (pPal);

// Speicher wieder freigeben
	if (pPal) delete (char *)pPal;

return hPal;
}


// CColorBox: Anzeige&Interaktionsfeld im DialogFenster -----------------------
CColorBox :: CColorBox (pDialogWindow pW, short iCnt, 
			HPALETTE hPal, ResourceFile *pRF)
	   : PushButton (pW, ResID (iCnt+IDFT_COLOR1, pRF)),
	     m_rRF (*pRF),
	     m_hPal (hPal)
{
	m_pFVI = NULL;
	m_iCnt = iCnt;
	m_hWnd = pW -> Handle (API_WINDOW_HWND);
}


CColorBox :: ~CColorBox (void)
{
	DELETE_OBJ (m_pFVI);
}


BOOL CColorBox :: FInit (FVisInfo *pFVI)
{
	if (pFVI == NULL) return false;		// Initialisierungsfehler
	
	DELETE_OBJ (m_pFVI);		// für ReInitialisierung
	m_pFVI = (FVisInfo *)pFVI -> Copy();		// Kopie ablegen

// Farben über Palette abbilden
	ConvertColor (m_hPal, m_pFVI -> PrimColor());
	ConvertColor (m_hPal, m_pFVI -> SecColor());
	
return true;
}


// Herausholen der VisInfo einer CColorBox ------------------------------------
FVisInfo *CColorBox :: GetFVisInfo (BOOL fConvert)
{ 
	if (m_pFVI == NULL) return NULL;
	
FVisInfo *pFVI = (FVisInfo *)m_pFVI -> Copy();

	if (fConvert) {		// normale Farben
		ConvertPaletteIndex (m_hPal, pFVI -> PrimColor());
		ConvertPaletteIndex (m_hPal, pFVI -> SecColor());
	}

return pFVI; 
}



// Dialogfenster selber -------------------------------------------------------
CPaletteDlg *CPaletteDlg :: CreateInstance (
				pWindow pW, HWND hWndM, 
				CVisPalette &rVP, HPALETTE hPal, 
				ResourceFile *pRF, BOOL fPercents)
{
CEierUhr Wait (pW);
CPaletteDlg *pPDlg = new CPaletteDlg (pW, hWndM, rVP, hPal, pRF, fPercents);

	if (pPDlg == NULL || !pPDlg -> FInit()) {
		DELETE_OBJ (pPDlg);
		return NULL;
	}
	
return pPDlg;
}


#pragma warning (disable:4355)

CPaletteDlg :: CPaletteDlg (pWindow pW, HWND hWndM, CVisPalette &rVP, 
			    HPALETTE hPal, ResourceFile *pRF, BOOL fPercents)
	     : OwnerDrawDialogWindow (pW, ResID (COLORSELDLG, pRF)),
	       m_pbOK (this, IDOK),
	       m_pbHelp (this, IDB_FARBENHILFE),
	       m_pbSelect (this, IDB_SELECTOTHER),
	       m_pbReset (this, IDB_RESETCOLORS),
	       m_slePaletteName (this, IDE_PALETTENAME),
	       m_neDigits (this, IDE_NUMDIGITS),
	       m_ftPercents (this, IDT_PERCENTS),
	       m_ftDigits (this, IDT_NUMDIGITS),
	       m_rPalette (rVP),
	       m_rRF (*pRF),
	       m_hPal (hPal),
	       __hWndM (hWndM)
{
// Variablen initialisieren
	memset (m_pCB, '\0', sizeof(CColorBox *)*MAXPIECOLORS);
	m_iActColor = 0;
	
// Controls initialisieren
	m_slePaletteName.SetTextLimit (MAXPALETTENAMELEN);
	m_slePaletteName.SetText (rVP.FGetpChar());
	if (rVP.GetNumDigits() >= 0 && fPercents) {
		m_neDigits.SetValue (rVP.GetNumDigits());
		m_ftPercents.Enable();
		m_ftDigits.Enable();
	} else {
		m_ftPercents.Disable();
		m_ftDigits.Disable();
		m_neDigits.SetValue (1);
		m_neDigits.Disable();
	}

	m_pbOK.Disable();
	m_fIsDirty = false;
}

#pragma warning (default:4355)


CPaletteDlg :: ~CPaletteDlg (void)
{
	for (short i = 0; i < MAXPIECOLORS; i++) {
		DELETE_OBJ (m_pCB[i]);
	}
	
//	if (m_hPal) DeleteObject (m_hPal);
}


BOOL CPaletteDlg :: FInit (void)
{
// Palette bestimmen
	m_rPalette.RetrievePalette (m_hPal);
	if (m_hPal == 0) return false;
	
// einzelne FarbFelder anlegen
	for (short i = 0; i < MAXPIECOLORS; i++) {
		m_pCB[i] = new CColorBox (this, i, m_hPal, &m_rRF);
	
	FVisInfo *pFVI = m_rPalette.GetFVisInfo(i);
	
		if (m_pCB[i] == NULL || !m_pCB[i] -> FInit (pFVI)) {
			DELETE_OBJ (pFVI);
			return false;
		}
		DELETE_OBJ (pFVI);
	}
	RePaint();		// Farbeinstellung anzeigen

return true;
}


// EventHandler ---------------------------------------------------------------
void _VMD_EXPORT CPaletteDlg :: ButtonClick (ControlEvt e)
{
unsigned short uiCID = (uint)e.GetControlID();
short i = 0;

	switch (uiCID) {
	case IDOK:
		EndDlg (1);
		break;
		
	case IDCANCEL:
		EndDlg (0);
		break;
		
	case IDB_FARBENHILFE:
		break;
		
	case IDB_SELECTOTHER:
		Select (m_iActColor);
		m_fIsDirty = true;
		AdjustOK();
		RePaint();
		break;
		
	case IDB_RESETCOLORS:		// alle Farben rücksetzen
		for (i = 0; i < MAXPIECOLORS; i++) {
		FVisInfo *pFVI = m_rPalette.GetFVisInfo (i);
		
			m_pCB[i] -> FInit (pFVI);
			DELETE_OBJ (pFVI);
		}
		m_slePaletteName.SetText (m_rPalette.FGetpChar());
		m_fIsDirty = false;
		AdjustOK();
		RePaint();
		break;

	default:
		if (uiCID >= IDFT_COLOR1 && uiCID < IDFT_COLOR1+MAXPIECOLORS) {
			uiCID -= IDFT_COLOR1;
			m_pCB[uiCID] -> SetFocus();
			m_iActColor = uiCID;
		}
		break;
	}
}


void _VMD_EXPORT CPaletteDlg :: ButtonDblClk (ControlEvt e)
{
unsigned short uiCID = (uint)e.GetControlID();

	if (uiCID >= IDFT_COLOR1 && uiCID < IDFT_COLOR1+MAXPIECOLORS) {
		uiCID -= IDFT_COLOR1;
		Select (uiCID);
		SetFocus();			// Focus wieder bei uns

		m_fIsDirty = true;
		AdjustOK();
		RePaint();
	}
}


void _VMD_EXPORT CPaletteDlg :: EditChange (ControlEvt e)
{
	if ((uint)e.GetControlID() == IDE_NUMDIGITS)
		m_fIsDirty = true;
	AdjustOK();
}


// OwnerDrawEventHandler ------------------------------------------------------
BOOL _VMD_EXPORT CPaletteDlg :: MeasureItem (MeasureItemEvt e)	// Größe eines Elements bestimmen
{
	if (e.ItemType() != ODT_BUTTON) return false;
	
short iIndex = (uint)e.GetControlID() - IDFT_COLOR1;
Dimension dimC = m_pCB[iIndex] -> GetSize();

	e.SetItemHeight (dimC.Height());
	e.SetItemWidth (dimC.Width());

return true;
}


BOOL _VMD_EXPORT CPaletteDlg :: DrawEntireItem (DrawItemEvt e)	// Element vollständig malen
{
	if (e.ItemType() != ODT_BUTTON) return false;
	
// FVisInfo wiedergeben
FVisInfo *pFVI = m_pCB[(uint)e.GetControlID() - IDFT_COLOR1] -> GetFVisInfo();

	if (pFVI == NULL) return false;	// kein Speicher mehr
	
Rectangle rcC = e.ItemSize();
HDC hDC = (HDC)e.Handle (API_CONTROL_HDC);
CFixupDC dcT (hDC, m_hPal, pFVI);

	InflateRect ((RECT *)&rcC, -2, -2);
	DrawRectangle (hDC, rcC.Left(), rcC.Top(), rcC.Right(), rcC.Bottom());
	DELETE_OBJ (pFVI);		// Speicher freigeben

return true;
}


BOOL _VMD_EXPORT CPaletteDlg :: DrawItemFocus (DrawItemEvt e)	// Element mit Focus zeichnen
{
	if (e.ItemType() != ODT_BUTTON) return false;
	
// Focusrechteck zeichnen
Rectangle rcC = e.ItemSize();
HDC hDC = (HDC)e.Handle (API_CONTROL_HDC);

	if (e.hasFocus())
		FrameRect (hDC, (RECT *)&rcC, (HBRUSH)GetStockObject (BLACK_BRUSH));
	else
		FrameRect (hDC, (RECT *)&rcC, (HBRUSH)GetStockObject (WHITE_BRUSH));

return true;
}


void CPaletteDlg :: Select (short iAct)
{
// DialogBox anzeigen lassen
HANDLEVISINFO *pHVI = ctHANDLEVISINFO (VTFlaeche);

	if (pHVI == NULL) return;

FVisInfo *pFVI = m_pCB[iAct] -> GetFVisInfo (true);

	if (pFVI == NULL) return;

	pFVI -> CopyTo (*pHVI -> m_pVI);
	DELETE_OBJ (pFVI);

ResString resSelCaption (ResID (IDS_SELECTCAPTION, &m_rRF), 65);

	pHVI -> m_pDesc = (char *)resSelCaption.Addr();
	pHVI -> m_hWnd = Handle (API_WINDOW_HWND);
	if (GetKeyState (VK_CONTROL) < 0)		// Ctrl-Taste gedrückt
		pHVI -> m_fFlags |= DF_HSBModel;	// HSB-Modell
	if (DEX_ModVisInfoDialog (*pHVI)) return;

// diese Farbe neu einstellen
	pFVI = new FVisInfo (*(FVISINFO *)pHVI -> m_pVI);
	if (pFVI == NULL) return;
		
// Neue Farbe anzeigen
	ExpandPalette (m_hPal, pFVI);
	m_pCB[iAct] -> FInit (pFVI);

	DELETE_OBJ (pFVI);
	
// Speicher wieder freigeben
	dtHANDLEVISINFO (pHVI);
}



// sonstige HilfsFunktionen ---------------------------------------------------
CVisPalette *CPaletteDlg :: GetVisPalette (void)
{
char cbPName[MAXPALETTENAMELEN+1];
CVisPalette *pVPal = new CVisPalette;

	m_slePaletteName.GetText (cbPName, sizeof(cbPName));
	if (pVPal == NULL || !pVPal -> FInit (cbPName)) {
		DELETE_OBJ (pVPal);
		return NULL;
	}
	
// FVisInfo's in der Palette mit NutzerEingabe initialisieren
	for (short i = 0; i < MAXPIECOLORS; i++) {
	FVisInfo *pFVI = m_pCB[i] -> GetFVisInfo (true);
	
	// in der Resultatspalette speichern
		pVPal -> SetFVisInfo (pFVI, i);
		DELETE_OBJ (pFVI);
	}
	
// Anzahl der Digits kopieren
	pVPal -> SetNumDigits (m_neDigits.GetValue());
	
return pVPal;
}


void CPaletteDlg :: AdjustOK (void)
{
char cbPName[MAXPALETTENAMELEN+1];

	m_slePaletteName.GetText (cbPName, sizeof(cbPName));
	if (m_fIsDirty || strcmp (cbPName, m_rPalette.FGetpChar()))	
		m_pbOK.Enable();	// wenn was geändert wurde
	else    m_pbOK.Disable();
}


// BehandlungsRoutinen für HANDLEVISINFO --------------------------------------
HANDLEVISINFO *ctHANDLEVISINFO (short iVTyp)
{
VISINFO *pVI = NULL;
HANDLEVISINFO *pHVI = NULL;

	try {
		pHVI = new HANDLEVISINFO;
		if (pHVI == NULL) return NULL;
		
		switch (iVTyp) {
		case VTPunkt:
			pVI = (VISINFO *)new PVISINFO;
			if (pVI) {
				INITSTRUCT(*pVI, PVISINFO);
			}
			break;
			
		case VTLinie:
			pVI = (VISINFO *)new LVISINFO;
			if (pVI) {
				INITSTRUCT(*pVI, LVISINFO);
			}
			break;
			
		case VTFlaeche:
			pVI = (VISINFO *)new FVISINFO;
			if (pVI) {
				INITSTRUCT(*pVI, FVISINFO);
			}
			break;
			
		case VTText:
			pVI = (VISINFO *)new TVISINFO;
			if (pVI) {
				INITSTRUCT(*pVI, TVISINFO);
			}
			break;

		default:
		case VTDefault:
			pVI = (VISINFO *)new DVISINFO;
			if (pVI) {
				INITSTRUCT(*pVI, DVISINFO);
			}
			break;
		}

	} catch(...) {
		;
	}

	if (pVI == NULL) {
		DELETE_OBJ (pHVI);
		return NULL;
	}

	INITSTRUCT(*pHVI, HANDLEVISINFO);
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


