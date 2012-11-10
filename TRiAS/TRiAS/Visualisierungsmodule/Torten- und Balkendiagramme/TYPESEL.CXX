// Auswahl des konkreten Torten-/Balken-Typs ----------------------------------
// File: TYPESEL.CXX

#include "tortenp.hxx"

#include <ctype.h>
	
#include <oddlgwin.hxx>
#include <numeditx.hxx>
#include <icustom.hxx>

#include "impcustm.hxx"
#include "cpicbox.hxx"
#include "typesel.hxx"

#include "paltree.hxx"
#include "paltree.inl"
#include "cpalette.hxx"

#include <resstrg.h>
#include "torten.h"
#include "typesel.h"

// Daten, die benötigt werden, um die Bildchen zu zeichnen --------------------
const short SAMPLESECTORS = 3;
static long s_pSectors[SAMPLESECTORS+1] = { 25900L, 42300L, 31600L, 0L, };
static char *s_ppSecWerte[SAMPLESECTORS+1] = { "0.0", "25.9", "42.3", "31.6", };

const short SAMPLERECTS = 4;
static long s_pRects[SAMPLERECTS+1] = { 30000L, 25900L, 42300L, 31600L, 0L, };
static char *s_ppRectWerte[SAMPLERECTS+1] = { NULL, "0.0", "25.9", "42.3", "31.6", };

const short SAMPLERECTSROT = 5;
static long s_pRectsRot[SAMPLERECTSROT+1] = { 30000L, 600000L, 25900L, 42300L, 31600L, 0L, };
static char *s_ppRectRotWerte[SAMPLERECTSROT+1] = { NULL, NULL, "0.0", "25.9", "42.3", "31.6", };

// Datenstruktur, die alle Informationen über die Symbolisierungstypen dieses
// VisModules enthält
typedef struct tagVISTYPEDATA {
	unsigned short m_uiString;	// BeschreibungsText
	short m_iType;			// TypNummer
	unsigned short m_fOffset : 1;	// Offset möglich
	unsigned short m_fRelText : 1;	// Prozentanzeige sinnvoll
	short m_iSectors;		// Anzahl der BeispielSektoren
	long *m_pSectors;		// BeispielDaten
	char **m_ppMWerte;		// BeispielTexte
} VISTYPEDATA;


VISTYPEDATA s_rgVisTypes[] = {
	{ IDS_FULLCIRCLE, TORTEN_FULLCIRCLE, false, true, 
	  SAMPLESECTORS, s_pSectors, s_ppSecWerte, },	// VollKreis
	{ IDS_UPPERHALF, TORTEN_UPPERHALF, true, true, 
	  SAMPLESECTORS, s_pSectors, s_ppSecWerte, },	// oberer HalbKreis
	{ IDS_LOWERHALF, TORTEN_LOWERHALF, true, true, 
	  SAMPLESECTORS, s_pSectors, s_ppSecWerte, },	// unterer HalbKreis
	{ IDS_BALKENHOCHPOS, TORTEN_BALKENHOCHPOS, true, false, 
	  SAMPLERECTS, s_pRects, s_ppRectWerte,	},	// Balken hoch
	{ IDS_BALKENHOCHPOSLOG, TORTEN_BALKENHOCHPOSLOG, true, false, 
	  SAMPLERECTS, s_pRects, s_ppRectWerte,	},	// Balken hoch, log
	{ IDS_BALKENROT, TORTEN_BALKENROT, false, false, 
	  SAMPLERECTSROT, s_pRectsRot, s_ppRectRotWerte,	},	// Balken drehbar
	{ IDS_BALKENROTLOG, TORTEN_BALKENROTLOG, false, false, 
	  SAMPLERECTSROT, s_pRectsRot, s_ppRectRotWerte,	},	// Balken drehbar, log
//	{ IDS_BALKENHOCHPOSEXP, TORTEN_BALKENHOCHPOSEXP, true, false,
//	  SAMPLERECTS, s_pRects, s_ppRectWerte,	},	// Balken hoch
};
#define MAXVISTYPES	(sizeof(s_rgVisTypes)/sizeof(VISTYPEDATA))


// Merkmale aus der PBD lesen -------------------------------------------------
extern "C" {

typedef struct tagFILLMCODEDATA {
	ComboBox *m_pcbList;
	char *m_pBuff;
	HWND m_hWnd;
	uint m_uiDexCmd;
} FILLMCODEDATA;

BOOL _VMD_EXPORT PASCAL FillMCodesListBox (long lMCode, BOOL, void *pData)
{
PBDMERKMAL pbdData;
char cbKText[33];
FILLMCODEDATA *pFMD = (FILLMCODEDATA *)pData;
HWND __hWndM = pFMD -> m_hWnd;
uint __DexCmd = pFMD -> m_uiDexCmd;

	memset (&pbdData, '\0', sizeof(PBDMERKMAL));

	pbdData.dwSize = sizeof(PBDMERKMAL);
	pbdData.pbdTyp = 'm';
	pbdData.pbdCode = lMCode;
	pbdData.pbdKText = cbKText;
	pbdData.pbdKTextLen = sizeof(cbKText) -1;
	pbdData.pbdLTextLen = 0;
	pbdData.ipbdMTyp = 'u';

	DEX_GetPBDData (pbdData);

	wsprintf (pFMD -> m_pBuff, "%08ld:%s", lMCode, pbdData.pbdKText);
	pFMD -> m_pcbList -> AddString (pFMD -> m_pBuff);

return true;	// weitermachen
}

} // extern "C"


// globale Variablen ----------------------------------------------------------
static long GetMCodeFromVisString (char *pVisStr);

// Anzeigen des Dialogfensters zur Auswahl des zu verwendenden TortenTyps -----
STDMETHODIMP CTortenVisModule :: QueryParameters (
			HWND hWndM, long /*lONr*/, VisInfo *pVI, char *pVisStr, 
			char *pBuffer, short /*iLen*/, short *piOTypes)
{
	__hWndM = hWndM;

// wenn noch keine Palette gegeben ist, dann diese holen und mergen		
	if (m_hPal == 0) {
		m_hPal = DEX_GetActivePalette();	// von TRIAS Palette holen
		if (m_hPal != 0 && m_pPalT) 
			m_pPalT -> RetrievePalette (m_hPal);
	}

// hier geht's richtig los
	*pBuffer = '\0';			// sicherheitshalber
	*piOTypes = 0;

Window *pMainWnd = new Window (__hWndM);		// ParentFenster

	if (pMainWnd == NULL || m_pPalT == NULL) 
		return ResultFromScode (E_OUTOFMEMORY);

long lMCode = GetMCodeFromVisString (pVisStr);
short iType = 0;
HRESULT hr = NOERROR;

	if (lMCode != -1L && pVI != NULL) iType = pVI -> Style();

	{
	CEierUhr Wait (pMainWnd);
	CTortenSelDlg TSDlg (pMainWnd, m_pRF, this, iType, lMCode, m_hPal, m_pPalT);
	
		if (TSDlg.FInit (pVI -> VisName())) {
			Wait.Hide();
			TSDlg.Show();
			if (TSDlg.Result()) {	// Auswertung
				wsprintf (pBuffer, ResString (ResID (IDS_CUSTFORMAT, m_pRF), 30),
						   TSDlg.GetSelectedType(), 
						   TSDlg.GetSelectedPalette(),
						   TSDlg.GetSelectedMCode());
			} else	// Cancel 
				hr = ResultFromScode(VISMODULE_E_GENERALERROR);
				
			if (TSDlg.FPalTreeChanged()) SavePalettes (__hWndM);
				
			*piOTypes = (OTPunkt|OTLinie|OTFlaeche);
		} else
			hr = ResultFromScode(VISMODULE_E_GENERALERROR);
	}
        DELETE_OBJ (pMainWnd);
	
return hr;
}


// Alle Paletten wegschreiben -------------------------------------------------
BOOL CTortenVisModule :: SavePalettes (HWND hWndM)
{
	if (m_pActProject == NULL) return false;
	
LPSTORAGE pIStorage = NULL;
HRESULT hr = OpenProjectPaletteStorage (hWndM, m_pActProject, &pIStorage);
	
	if (FAILED(hr)) return false;;
		
ResString resPals (ResID (IDS_TORTENPALETTEN, m_pRF), 40);

	if (m_pPalT -> SavePalettes (pIStorage, resPals))
		pIStorage -> Commit (STGC_DEFAULT);
	pIStorage -> Release();

return true;
}


static long GetMCodeFromVisString (char *pVisStr)
{
char *pTmp = pVisStr;

	if (pTmp == NULL) return -1L;
	
	while (isspace(*pTmp)) 
		pTmp++;
	if (*pTmp == '\"') return -1L;		// direkt visualisiert
	if (*pTmp == '%') return atol (pTmp+1);	// MCode gegeben

return -1L;	// nichts von allem
}


// Memberfunktionen für dieses DialogFenster ----------------------------------
#pragma warning (disable: 4355)

CTortenSelDlg :: CTortenSelDlg (pWindow pW, ResourceFile *pRF, 
				CTortenVisModule *pVM, short iType, long lMCode,
				HPALETTE hPal, CVisPaletteTree *pVPT)
	       : DialogWindow (pW, ResID (TORTENDLG, pRF)),
	         m_rRF (*pRF),
		 __hWndM (pW -> Handle(API_CLIENT_HWND)),
		 m_rVPT (*pVPT),
		 m_cbTypes (this, IDCB_TORTENTYPEN),
		 m_chkbShowValues (this, IDCB_SHOWVALUES),
		 m_rbRelValues (this, IDR_RELVALUES),
		 m_rbAbsValues (this, IDR_ABSVALUES),
		 m_cbMCodes (this, IDCB_FEATURECODE),
		 m_bbPreview (this, IDT_TORTENPREVIEW, pVM),
		 m_chkbOffset (this, IDCB_OFFSET),
		 m_pbOK (this, IDOK),
		 m_pbHelp (this, IDB_TORTENHILFE),
		 m_pbColors (this, IDB_COLORS),
		 m_ftHelpText (this, IDT_HELPTEXT),
		 m_chkbPalettes (this, IDCB_COLORPALETTE)
{
// voreinstellungen merken
	m_lMCode = lMCode;
	m_iType = iType;
	
// Variablen initialisieren
	m_fOffset = false;
	m_pBuff = NULL;
	m_pInBuff = NULL;

	m_fRelValues = false;
	m_fAbsValues = true;
#if defined(_FORCE_LEGACY_CODE)
	m_fFontChanged = false;
	m_pFont = NULL;
#endif // _FORCE_LEGACY_CODE
	m_fPalTreeChanged = false;

	m_hPal = hPal;
	
// Controls initialisieren
	m_pbOK.Disable();
	m_pbHelp.Disable();
	
	m_rbRelValues.Disable();
	m_rbAbsValues.Disable();
}

#pragma warning (default: 4355)

CTortenSelDlg :: ~CTortenSelDlg (void)
{
	DELETE_OBJ (m_pBuff);
	DELETE_OBJ (m_pInBuff);
#if defined(_FORCE_LEGACY_CODE)
	if (m_fFontChanged) {
		m_pFont = m_ftHelpText.ChangeFont (m_pFont);
		DELETE_OBJ (m_pFont);
	}
#endif // _FORCE_LEGACY_CODE
}


BOOL CTortenSelDlg :: FInit (const char *pPName)
{
// Speicher anfordern
	m_pBuff = new char [_MAX_PATH];
	if (m_pBuff == NULL) return false;
	m_pInBuff = new char [_MAX_PATH];
	if (m_pInBuff == NULL) return false;

#if defined(_FORCE_LEGACY_CODE)
ResString rsArial (IDS_ARIAL, 20);

#if !defined(_TRIAS_OLDIMPLEMENTATION2)
	m_pFont = new CVFont (Swiss, Dimension (0, -12), rsArial);
#else
	m_pFont = new Font (Swiss, Dimension (0, -12), rsArial);
#endif //!defined(_TRIAS_OLDIMPLEMENTATION2)
	if (m_pFont) {
		m_pFont = m_ftHelpText.ChangeFont (m_pFont);
		m_fFontChanged = true;	
	}
#endif // _FORCE_LEGACY_CODE

// ComboBoxen füllen
short iIndex = -1;

	for (short i = 0; i < MAXVISTYPES; i++) {
	unsigned short uiResID = s_rgVisTypes[i].m_uiString;
	
		if (uiResID) m_cbTypes.AddString (
					ResString (ResID (uiResID, &m_rRF), 50)
			     );
		if ((m_iType & TORTEN_TYPEMASK) == s_rgVisTypes[i].m_iType)
			iIndex = i;
	}

// verfügbare Farbpaletten einlesen
	ReadDefinedPalettes (pPName);
	
// Controls voreinstellen
	m_fOffset = (m_iType & TORTEN_OFFSET) ? true : false;
	if (iIndex != -1) m_cbTypes.ChangeCurrentIndex (iIndex);
	m_chkbOffset.SetChecked (m_fOffset);
	
	if (m_iType & (TORTEN_TEXTSABS|TORTEN_TEXTSREL)) {
		m_chkbShowValues.SetChecked(true);
		m_rbRelValues.Enable();
		m_rbAbsValues.Enable();
		if (m_iType & TORTEN_TEXTSREL) {
			m_rbRelValues.SetState(true);
			m_fRelValues = true;
			m_fAbsValues = false;
		} else {
			m_rbAbsValues.SetState (true);
			m_fRelValues = false;
			m_fAbsValues = true;
		}
	}
	AdjustTypeInfos ();	// Bildchen zeichnen etc.
		
// MerkmalsKurztexte laden
ENUMLONGKEY ELK;
FILLMCODEDATA FMD;

	FMD.m_pcbList = &m_cbMCodes;
	FMD.m_pBuff = m_pBuff;
	FMD.m_hWnd = __hWndM;
	FMD.m_uiDexCmd = __DexCmd;
	
	memset (&ELK, '\0', sizeof (ENUMLONGKEY));
	ELK.eKey = 'm';
	ELK.eFcn = (ENUMLONGKEYPROC)FillMCodesListBox;
	ELK.ePtr = (void*)&FMD;
	DEX_EnumPBDData (ELK);
	
// MCode voreinstellen
	if (m_lMCode != -1L) {
	char cbMCode[20];
	short iIndex = -1;
		
		ltoa (m_lMCode, cbMCode, 10);
		iIndex = m_cbMCodes.FindString (cbMCode);
		if (iIndex != -1) 
			m_cbMCodes.ChangeCurrentIndex (iIndex);
	}		
	AdjustOKButton();
	
return true;
}


// AbfrageFunktionen für Nutzerwünsche ----------------------------------------
short CTortenSelDlg :: GetSelectedType (void)
{
short iType = m_cbTypes.GetCurrentIndex();

	if (iType != -1) {
		iType = s_rgVisTypes[iType].m_iType;
		if (m_chkbOffset.isChecked()) iType |= TORTEN_OFFSET;
		if (m_chkbShowValues.isChecked()) {
			if (m_rbRelValues.GetState())
				iType |= TORTEN_TEXTSREL;
			else 
				iType |= TORTEN_TEXTSABS;		
		}
	}
	
return iType;
}


long CTortenSelDlg :: GetSelectedMCode (void)
{
short iIndex = m_cbMCodes.GetCurrentIndex();
long lMCode = 0;

	if (iIndex != -1) {
		m_cbMCodes.GetString (m_pBuff, iIndex, _MAX_PATH);
		lMCode = atol (m_pBuff);
	}
	
return lMCode;
}


char *& CTortenSelDlg :: GetSelectedPalette (void)
{
short iIndex = m_chkbPalettes.GetCurrentIndex();

	if (iIndex != -1)
		m_chkbPalettes.GetString (m_pBuff, iIndex, _MAX_PATH);
	else
		strcpy (m_pBuff, ResString (ResID (IDS_DEFAULTPALETTE, &m_rRF), 40));
	
return m_pBuff;
}


// EventHandler ---------------------------------------------------------------
void _VMD_EXPORT CTortenSelDlg :: ButtonClick (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDOK:
		EndDlg (1);
		break;
		
	case IDCANCEL:
		EndDlg (0);
		break;
		
	case IDB_FARBENHILFE:
		break;

	case IDB_COLORS:
		ModifyVisPalette();
		break;
		
	case IDCB_OFFSET:
		{
		unsigned short uiRes = 0;
		short iIndex = m_cbTypes.GetCurrentIndex();
				
			if (iIndex == TORTEN_UPPERHALF || 
			    iIndex == TORTEN_BALKENHOCHPOS ||
			    iIndex == TORTEN_BALKENHOCHPOSLOG) 
			{
			    	uiRes = IDS_OBEN;
			}
			if (iIndex == TORTEN_LOWERHALF) uiRes = IDS_UNTEN;
			if (uiRes != 0) {
				SetHelpText (IDCB_OFFSET, 
					     ResString (ResID (uiRes, &m_rRF), 10));
			}
			m_fOffset = m_chkbOffset.isChecked() ? true : false;
			AdjustTypeInfos();
		}
		break;
		
	case IDCB_SHOWVALUES:
		if (m_chkbShowValues.isChecked()) {
		short iIndex = m_cbTypes.GetCurrentIndex();

			if (iIndex == -1) break;
			
			SetHelpText (m_fRelValues ? IDR_RELVALUES : IDR_ABSVALUES);
			if (s_rgVisTypes[iIndex].m_fRelText) {
				m_rbRelValues.Enable();
				m_rbRelValues.SetState (m_fRelValues);
			} else if (m_fRelValues) {
				m_fRelValues = false;
				m_fAbsValues = true;
			}
			m_rbAbsValues.Enable();
			m_rbAbsValues.SetState (m_fAbsValues);
		} else {
			SetHelpText (IDR_ABSVALUES);
			m_fRelValues = 	m_rbRelValues.GetState() ? true : false;
			m_rbRelValues.SetState (false);
			m_rbRelValues.Disable();
			m_fAbsValues = 	m_rbAbsValues.GetState() ? true : false;
			m_rbAbsValues.SetState (false);
			m_rbAbsValues.Disable();
		}
		AdjustTypeInfos();
		break;

	case IDR_RELVALUES:
	case IDR_ABSVALUES:
		SetHelpText ((uint)e.GetControlID());
		AdjustTypeInfos();
		break;
	}
}


void _VMD_EXPORT CTortenSelDlg :: ListBoxSel (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDCB_TORTENTYPEN:
		{
		short iType = m_cbTypes.GetCurrentIndex();
		
			if (iType == -1) break;
			iType = s_rgVisTypes[iType].m_iType;
			SetHelpText (IDCB_TORTENTYPEN, 
				     ResString (ResID (iType+IDS_FULLCIRCLE, &m_rRF), 60));
			AdjustTypeInfos();
		}
		break;
		
	case IDCB_FEATURECODE:
		{
		short iIndex = m_cbMCodes.GetCurrentIndex();
		
			if (iIndex != -1) {
				m_cbMCodes.GetString (m_pInBuff, iIndex, _MAX_PATH);
				SetHelpText (IDCB_FEATURECODE, strchr (m_pInBuff, ':')+1);
			}
		}
		break;

	case IDCB_COLORPALETTE:
		{
		short iIndex = m_chkbPalettes.GetCurrentIndex();
		
			if (iIndex != -1) {
				m_chkbPalettes.GetString (m_pInBuff, iIndex, _MAX_PATH);
				SetHelpText (IDCB_COLORPALETTE, m_pInBuff);
				AdjustTypeInfos();
			}
		}
		break;
	}

// testen, ob OKButton aktiv sein kann
	AdjustOKButton();
}


// Überprüfen, wenn ComboBoxen Focus erhalten haben ---------------------------
void _VMD_EXPORT CTortenSelDlg :: EditFocusChg (EditFocusChgEvt e)
{
	if (!((ComboFocusChgEvt &)e).gotFocus()) return;	// nur wenn Fokus erhalten
	
	switch ((uint)e.GetControlID()) {
	case IDCB_FEATURECODE:
		{
		short iIndex = m_cbMCodes.GetCurrentIndex();
				
			if (iIndex != -1) {
				m_cbMCodes.GetString (m_pInBuff, iIndex, _MAX_PATH);
				SetHelpText (IDCB_FEATURECODE, strchr (m_pInBuff, ':')+1);
			}
		}
		break;
		
	case IDCB_TORTENTYPEN:
		{
		short iType = m_cbTypes.GetCurrentIndex();
		
			if (iType == -1) break;
			iType = s_rgVisTypes[iType].m_iType;
			SetHelpText (IDCB_TORTENTYPEN, 
				     ResString (ResID (iType+IDS_FULLCIRCLE, &m_rRF), 60));
		}
		break;	

	case IDCB_COLORPALETTE:
		{
		short iIndex = m_chkbPalettes.GetCurrentIndex();
		
			if (iIndex != -1) {
				m_chkbPalettes.GetString (m_pInBuff, iIndex, _MAX_PATH);
				SetHelpText (IDCB_COLORPALETTE, m_pInBuff);
			}
		}
		break;
	}
}


void CTortenSelDlg :: AdjustTypeInfos (short iIndex)
{
	if (iIndex == -1)
		iIndex = m_cbTypes.GetCurrentIndex();

	if (iIndex == -1) return;
			
// CheckBox richten
	if (s_rgVisTypes[iIndex].m_fOffset) {
		m_chkbOffset.Enable();
		m_chkbOffset.SetChecked (m_fOffset);
	} else {
		m_fOffset = m_chkbOffset.isChecked();
		m_chkbOffset.SetChecked (false);
		m_chkbOffset.Disable();
	}
				
// Prozentanzeige richten
	if (!s_rgVisTypes[iIndex].m_fRelText) {
		if (m_chkbShowValues.isChecked() && m_rbRelValues.GetState()) {
			m_rbAbsValues.SetState (true);
			m_fAbsValues = true;
			m_rbRelValues.SetState (false);
			m_fRelValues = false;
		}
		m_rbRelValues.Disable();
	} else if (m_chkbShowValues.isChecked())
		m_rbRelValues.Enable();
	
// Bildchen anzeigen
	m_bbPreview.FInit (GetSelectedType(), GetSelectedPalette(),
			   s_rgVisTypes[iIndex].m_iSectors,
			   s_rgVisTypes[iIndex].m_pSectors, 
			   s_rgVisTypes[iIndex].m_ppMWerte
	);
}
		

// Setzt den BeschreibungsText entsprechend dem ResourceText ------------------
void CTortenSelDlg :: SetHelpText (unsigned short uiRes, const char *pStr)
{
ResString *pRes = new ResString (ResID (uiRes, &m_rRF), 255);

	if (pRes == NULL) return;

	if (pStr) {
		wsprintf (m_pBuff, pRes -> Addr(), pStr);	
		m_ftHelpText.SetText (m_pBuff);
	} else
		m_ftHelpText.SetText (pRes -> Addr());
	
	DELETE_OBJ (pRes);
}


// PalettenDialog anzeigen und auswerten --------------------------------------
BOOL CTortenSelDlg :: ModifyVisPalette (void)
{
CVisPalette *pVP = NULL;
short iIndex = m_chkbPalettes.GetCurrentIndex();
BOOL fFreePalette = false;
		
	if (iIndex != -1) {
		m_chkbPalettes.GetString (m_pInBuff, iIndex, _MAX_PATH);
		pVP = m_rVPT.FFindItem (m_pInBuff);
	}
	if (pVP == NULL) {	// Palette kennen wir nicht
	// StandardPalette benutzen
		pVP = CVisPalette :: GetDefaultVisPalette();
		if (pVP == NULL) return false;
		fFreePalette = true;
	}

// Dialog generieren und Anzeigen
CPaletteDlg *pDlg = CPaletteDlg :: CreateInstance (
				this, __hWndM, *pVP, m_hPal, 
				&m_rRF, m_rbRelValues.GetState());

	if (pDlg == NULL) {
		if (fFreePalette) DELETE_OBJ (pVP);
		DELETE_OBJ (pVP);
		return false;
	}
	pDlg -> Show();
	if (!pDlg -> Result()) {
		if (fFreePalette) DELETE_OBJ (pVP);
		DELETE_OBJ (pDlg);
		return false;	
	}
		
// NutzerEingabe abholen, wegschreiben und merken
CVisPalette *pVPNew = pDlg -> GetVisPalette();	// neue Palette

	if (pVPNew) {
		if (!strcmp (pVP -> FGetpChar(), pVPNew -> FGetpChar()))
		// alte Palette verändert: herauslöschen
			m_rVPT.FDeleteItem (pVP -> FGetpChar());

		m_rVPT.FAddItem (*pVPNew);
		m_fPalTreeChanged = true;
	}

// neue Palette in ComboBox anzeigen
	iIndex = m_chkbPalettes.FindString (pVPNew -> FGetpChar(), true);
	if (iIndex == -1)	// neue Palette
		iIndex = m_chkbPalettes.AddString (pVPNew -> FGetpChar());
	m_chkbPalettes.ChangeCurrentIndex (iIndex);
	AdjustTypeInfos();
	AdjustOKButton();
		
// aufräumen
	if (fFreePalette) DELETE_OBJ (pVP);
	DELETE_OBJ (pVPNew);
	DELETE_OBJ (pDlg);
	
return true;
}


void CTortenSelDlg :: ReadDefinedPalettes (const char *pPName)
{
CTable t(m_rVPT);
short iIndex;

// alle vordefinierten Palette eintragen
	for (t.First(); t.Valid(); t.Next()) {
	CVisPaletteLock l(t);
	
		if (!l) continue;
		iIndex = m_chkbPalettes.AddString (l -> FGetpChar());
		if (!strcmp (pPName, l -> FGetpChar()))
			m_chkbPalettes.ChangeCurrentIndex (iIndex);
	}
}


BOOL CTortenSelDlg :: AdjustOKButton (void)
{
	if (m_cbTypes.GetCurrentIndex() != -1 &&
	    m_cbMCodes.GetCurrentIndex() != -1 &&
	    m_chkbPalettes.GetCurrentIndex() != -1) 
	{
		m_pbOK.Enable();
		return true;
	} else
		m_pbOK.Disable();

return false;
}
