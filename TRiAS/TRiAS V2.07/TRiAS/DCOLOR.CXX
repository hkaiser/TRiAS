// Funktionen fuer das Dialofenster Farbeinstellung
// File: DCOLOR.CXX

#include "triaspre.hxx"

#include <stdio.h>

#include "owncombo.hxx"
#include "feature.hxx"
#include "dcolor.hxx"

#include "punktstr.h"

#define PALVERSION 0x0300

// Anzahl der Farben in der lokalen Palette der ColorListBox
const short NUMPALETTEENTRIES = 10;

// FarbRollBalken - Memberfunktionen ------------------------------------------
ColorScrollBar :: ColorScrollBar (pDialogWindow pW, uint SBarID, uint EdID, short iMax)
		: ColorBar (pW, SBarID),
		  ColorEdit (pW, EdID, iMax)
{
// MaximalWert abspeichern
	m_iMax = iMax;
	
// ScrollBalkenParameter setzen
	ColorBar.SetRange (Range (0, m_iMax));
	ColorBar.SetThumbPos (0);

// EditParameter setzen
	ColorEdit.SetTextLimit (3);
	ColorEdit.SetText ("0");

// Mode einstellen 
	_Mode = SB_Coarse;	// damits richtig losgeht
	SetMode (SB_Fine);
}

ColorScrollBar :: SB_Mode ColorScrollBar :: SetMode (ColorScrollBar :: SB_Mode newMode) 
{
	if (newMode != _Mode) {
	SB_Mode oldMode = _Mode;

		switch (newMode) {
		case SB_Fine:
		// Mode auf FEIN einstellen
			_Mode = SB_Fine;

		// ScrollBalkenParameter setzen
			ColorBar.SetUnit (1);
			ColorBar.SetBlock (16);
			break;

		case SB_Coarse:
			{
			// Mode auf GROB einstellen
				_Mode = SB_Coarse;

			// ThumbPos korrigieren
			short Pos = ColorBar.GetThumbPos();
			short newPos = ((Pos + 15)/32 * 32);

				if (newPos != Pos)
					ColorBar.SetThumbPos (newPos);

			// ScrollBalkenParameter setzen
				ColorBar.SetUnit (32);
				ColorBar.SetBlock (32);
			}
			break;
		}
		return oldMode;
	} else
		return _Mode;
}

// Destruktor -----------------------------------------------------------------
ColorScrollBar :: ~ColorScrollBar (void) 
{
	// nothing to do
}


void ColorScrollBar :: SetColor (short Val) 
{
// WerteKorrektur
	if (Val < 0) Val = 0;
	if (Val > m_iMax) Val = m_iMax;

// FarbWert abbilden
short oldVal, newVal = Val;

	if ((oldVal = ColorBar.GetThumbPos()) != Val) {
		if (_Mode == SB_Coarse) {
		// Wert Runden
			Val = ((Val + 15)/32) * 32;
			if (oldVal != Val)
				newVal = Val;
		// WerteKorrektur
			if (newVal < 0) newVal = 0;
			if (newVal > m_iMax) newVal = m_iMax;
		}

	// neue Werte setzen
		ColorBar.SetThumbPos (newVal);
		ColorEdit.SetValue (newVal);
	}
}

short ColorScrollBar :: GetColor (void) 
{
	return (short)ColorBar.GetThumbPos();
}

// sollte erst gerufen werden, wenn der Wert geprüft ist
short ColorScrollBar :: CopyToScrollBar (void) 
{
short retVal;

	ColorBar.SetThumbPos (retVal = ColorEdit.GetValue());

return retVal;
}

// ComboBox, die Farben mit Ihren Namen anzeigt -------------------------------
ColorListBox :: ColorListBox (pDialogWindow pW, uint ID) 
	      : OwnerDrawComboBox (pW, ID)
{
	// nothing else to do
}


bool ColorListBox :: FInit (Color C, const char *pIniFile)
{
// Parameter merken
	if (pIniFile != NULL) {
		_InitFile = new char [strlen (pIniFile)+1];
		if (_InitFile == NULL) {
			db_error (EC_NOMEMORY, RC_ctColorListBox);
			return false;	
		}
		strcpy (_InitFile, pIniFile);
	} else {
	ResString ColIni (IDS_COLORINIFILE, 80);

		_InitFile = new char [strlen (ColIni)+1];
		if (_InitFile == NULL) {
			db_error (EC_NOMEMORY, RC_ctColorListBox);
			return false;	
		}
		strcpy (_InitFile, ColIni);
	}

// Farben aus Ini-Datei einlesen und in ComboBox einfügen
ResString ColorSection (IDS_PROFCOLOR, 10);	// Colors-Sektion
// Anzahl der definierten Farben
int numColors = GetPrivateProfileInt (ResString (IDS_IRISPARS, 12),
			ResString(IDS_NUMCOLORS, 10), 0, _InitFile);

	SetSearchMode (SM_Name);		// nach Alphabet einordnen
	if (numColors > 0) {
	// wenn Farben vordefiniert sind
	char *ColorNamesStr = new char [numColors*40+1];
	char **ColorNames = new char * [numColors];

		if (ColorNamesStr == NULL || ColorNames == NULL) {
			db_error (EC_NOMEMORY, RC_ctColorListBox);
			return false;	
		}
		GetPrivateProfileString (ColorSection, NULL, "", ColorNamesStr, 
					 numColors*40+1, _InitFile);
		ColorNames[0] = ColorNamesStr;

	int len = 0;
	char ColorBuff[17];
	int iRed, iGreen, iBlue;
	ColorItem *pData;

	// alle Namen lesen
		for (int i = 1; i < numColors; i++) 
			ColorNames[i] = &ColorNamesStr[len += strlen(ColorNames[i-1])+1];

		for (int j = 0; j < numColors; j++) {
		// alle Farben einlesen und in ComboBox einhängen
			GetPrivateProfileString (ColorSection, ColorNames[j], 
									"", ColorBuff, 16, _InitFile);

			if (sscanf (ColorBuff, "%d,%d,%d", &iRed, &iGreen, &iBlue) != 3)
				continue;	// fehlerhaftes Format
			
			OemToAnsi (ColorNames[j], ColorNames[j]);
			pData = new ColorItem (Color ((ColorVal)iRed, 
								(ColorVal)iGreen, 
								(ColorVal)iBlue), 
								ColorNames[j]);
			if (pData == NULL) {
				db_error (EC_NOMEMORY, RC_ctColorListBox);
				return false;
			}
		
			if (CB_ERR == AddItem (pData))	// Item einhängen
				delete pData;
		}

	// Speicher wieder freigeben
		DELETE (ColorNames);
		DELETE (ColorNamesStr);
	}

// evtl. gegebene Farbe voreinstellen
ColorItem CI (C, "");
short iIndex;

	SetSearchMode (SM_Color);		// nach Farbe suchen
	if ((iIndex = (short)FindItem (&CI)) == CB_ERR)
		LocControl() -> ChangeCurrentIndex (0);		// erste Farbe auswählen
	else
		LocControl() -> ChangeCurrentIndex (iIndex);

// PalettenHandling vorbereiten
	_iCurrPalEntry = 0;		// lfder Eintrag in Palette
	_pPal = (LOGPALETTE *)new char[sizeof(LOGPALETTE) + 
				       NUMPALETTEENTRIES*sizeof(PALETTEENTRY)];
	if (_pPal == NULL) {
		db_error (EC_NOMEMORY, RC_ctColorListBox);
		return false;
	}

// Palette initialisieren
	_pPal -> palNumEntries = NUMPALETTEENTRIES;
	_pPal -> palVersion = PALVERSION;
	for (int i = 0; i < NUMPALETTEENTRIES; i++) {
		_pPal -> palPalEntry[i].peRed = (BYTE)0;
		_pPal -> palPalEntry[i].peGreen = (BYTE)0;
		_pPal -> palPalEntry[i].peBlue = (BYTE)0;
		_pPal -> palPalEntry[i].peFlags = (BYTE)0;
	}

// Palette generieren
	_hPal = CreatePalette (_pPal);

return true;
}


ColorListBox :: ~ColorListBox (void) 
{
#if 0 // ----------------------------------------------------------------------
// Wegschreiben aller Farben in INI-Datei
ColorItem *pData;
ResString ColorSection (IDS_PROFCOLOR, 10);	// [Colors]
char OutColor[40];
short iCnt = LocControl() -> GetCount();

	for (int i = 0; i < iCnt; i++) {
		pData = (ColorItem *)GetItem (i);
		if (!pData) continue;
		wsprintf (OutColor, "%d,%d,%d", pData -> _C.Red(),
						pData -> _C.Green(),
						pData -> _C.Blue());
		AnsiToOem (pData -> _Name, pData -> _Name);
		WritePrivateProfileString (ColorSection, pData -> _Name,
						OutColor, _InitFile);
	}
// Anzahl der Farben wegschreiben
	WritePrivateProfileString (ResString (IDS_IRISPARS, 12),
					ResString(IDS_NUMCOLORS, 10), 
					itoa (iCnt, OutColor, 10), _InitFile);
#endif // ---------------------------------------------------------------------

// alle Items in ColorListBox freigeben
	LocControl() -> Clear();

// dynamischen Speicher freigeben
	DELETE (_InitFile);
	if (_pPal) {
		delete (char *)_pPal;	
		_pPal = NULL;
	}
	if (_hPal != 0)
		DeleteObject (_hPal);
}

// Suchkriterium setzen 
ColorListBox :: ColorSearchMode ColorListBox :: SetSearchMode (ColorListBox :: ColorSearchMode newMode) 
{
ColorSearchMode oldMode = _SM;

	_SM = newMode;

return oldMode;
}

// Palette für ComboBox generieren --------------------------------------------
HPALETTE ColorListBox :: CorrectPalette (Color C) 
{
register int i = 0;

// nur bearbeiten, wenn Palette angelegt ist
	if (_pPal == NULL) 
		return _hPal;

// nachsehen, ob diese Farbe bereits in Palette enthalten ist
	if (_hPal) {
		for (i = 0; i < NUMPALETTEENTRIES; i++)
			if (!CmpColor (C, *(Color *)&_pPal -> palPalEntry[i]))
				break;
		if (i < NUMPALETTEENTRIES)
			return _hPal;		// Farbe gibt es schon
	}

// alte Palette freigeben
//	if (_hPal != 0) 
//		DeleteObject (_hPal);

// neuen PalettenEintrag setzen
	i = _iCurrPalEntry++;
	if (_iCurrPalEntry >= NUMPALETTEENTRIES) 
		_iCurrPalEntry = 0;
	_pPal -> palPalEntry[i].peRed = (BYTE)C.Red();
	_pPal -> palPalEntry[i].peGreen = (BYTE)C.Green();
	_pPal -> palPalEntry[i].peBlue = (BYTE)C.Blue();
	_pPal -> palPalEntry[i].peFlags = (BYTE)0;

// neue Palette bilden
//	_hPal = CreatePalette (_pPal);
	SetPaletteEntries (_hPal, i, 1, &_pPal -> palPalEntry[i]);

return _hPal;
}

// PalettenHandling -----------------------------------------------------------
void EXPORTTRIAS ColorListBox :: PaletteChange (PaletteChangeEvt e) 
{
HWND hWnd = Handle();
int i = 0;

	switch (e.GetPalAction()) {
	case PaletteChangeEvt :: PaletteIsChanging:
		break;		// keine Aktion

	case PaletteChangeEvt :: PaletteChanged:
		if (_hPal != NULL && hWnd != e.hPalChgWnd()) {
		HDC hDC = GetDC (hWnd);
		HPALETTE hOldPal = SelectPalette (hDC, _hPal, 0);
			
			i = RealizePalette (hDC);
			if (i) 
				UpdateColors (hDC);
			SelectPalette (hDC, hOldPal, 0);
			ReleaseDC (hWnd, hDC);
		}	
		break;

	case PaletteChangeEvt :: QueryNewPalette:
		{
			if (_hPal == NULL) return;

		HDC hDC = GetDC (hWnd);
		HPALETTE hOldPal = SelectPalette (hDC, _hPal, 0);
			
			i = RealizePalette (hDC);
			SelectPalette (hDC, hOldPal, 0);
			ReleaseDC (hWnd, hDC);
			if (i) 
				InvalidateRect (hWnd, (LPRECT)NULL, 1);
		}	
		break;

	default:
		Default ((Event &)e);
	}
}


// ComboBox für die Anzeige und Auswahl des FüllModes -------------------------
FillStyleComboBox :: FillStyleComboBox (pDialogWindow pDW, uint rsc)
		   : StyleComboBox (pDW, rsc)
{
	// nothing else to do
}

bool FillStyleComboBox :: FInit (short iStyle)
{
#if !defined(TRANSPARENT_PATTERNS)
	return StyleComboBox :: FInit (iStyle, IDS_NUMFILLSTYLES, NUMFILLSTYLES);
#else
int iNumStyles = DEX_Is16BitCompatible() ? NUMFILLSTYLES : NUMFILLSTYLES_TRANSPARARENT;

	return StyleComboBox :: FInit (iStyle, IDS_NUMFILLSTYLES, iNumStyles);
#endif // TRANSPARENT_PATTERNS
}


FillStyleComboBox :: ~FillStyleComboBox (void) 
{
	// nothing else to do
}


// ComboBox für die Anzeige und Auswahl des LineModes -------------------------
LineStyleComboBox :: LineStyleComboBox (pDialogWindow pDW, uint rsc)
		   : StyleComboBox (pDW, rsc)
{
	// nothing else to do
}

bool LineStyleComboBox :: FInit (short iStyle)
{
	return StyleComboBox :: FInit (iStyle, IDS_NUMLINESTYLES, NUMLINESTYLES);
}


LineStyleComboBox :: ~LineStyleComboBox (void) 
{
	// nothing else to do
}


// ComboBox für die Anzeige und Auswahl des LineModes -------------------------
PointStyleComboBox :: PointStyleComboBox (pDialogWindow pDW, uint rsc)
		    : StyleComboBox (pDW, rsc)
{
	// nothing else to do
}

bool PointStyleComboBox :: FInit (unsigned short iStyle, DatenBasisObjekt &rDBO)
{
	if (!rDBO.FNewPnts())
		return StyleComboBox :: FInit (short(iStyle), IDS_NUMPOINTSTYLES, NUMPOINTSTYLES);
	else {
	// DarstellungsStile in ComboBox einfügen
		SetSearchMode (SM_Style);		// nach Stil einordnen

	CTable t (rDBO.GetMap());
	int iIndex = -1;

		for (t.First(); t.Valid(); t.Next()) {
		CIndexPairLock l(t);

			if (!l) continue;

		ResString resPtName (IDS_PUNKTSYM001 + l->FIndex(), _MAX_PATH);

			if (strlen (resPtName) == 0) continue;

		Feature *pData = new Feature (l->FPunktID(), (char *)resPtName.Addr());
		
			if (pData == NULL) {
				db_error (EC_NOMEMORY, RC_ctStyleComboBox);
				return false;
			}
		
		int iNewIndex = (int)AddItem (pData);	// Item einhängen

			if (CB_ERR == iNewIndex)
				delete pData;			
			else if (l -> FPunktID() == iStyle)
				iIndex = iNewIndex;
		}

		if (iIndex == -1)
			LocControl() -> ChangeCurrentIndex (0);		// ersten Stil auswählen
		else
			LocControl() -> ChangeCurrentIndex (iIndex);

	return true;
	}
}


PointStyleComboBox :: ~PointStyleComboBox (void) 
{
	// nothing else to do
}


// ComboBox für die Anzeige und Auswahl des DarstellungsStiles ----------------
StyleComboBox :: StyleComboBox (pDialogWindow pDW, uint rsc)
	       : OwnerDrawComboBox (pDW, rsc)
{
	// nothing else to do
}

bool StyleComboBox :: FInit (short Style, uint strrsc, short numStyles)
{
// DarstellungsStile in ComboBox einfügen
ResString FSNameRes (strrsc+1, 20);
short iIndex = CB_ERR;

	SetSearchMode (SM_Style);		// nach Stil einordnen
	if (numStyles > 0) {
	static char cbFeatureName[64];

		for (int i = 0; i < numStyles; i++) {
			wsprintf (cbFeatureName, "%s%d", FSNameRes.Addr(), i+1);
		
		Feature *pData = new Feature (i, cbFeatureName);
		
			if (pData == NULL) {
				db_error (EC_NOMEMORY, RC_ctStyleComboBox);
				return false;
			}
		
		int iNewItem = (int)AddItem (pData);	// Item einhängen

			if (CB_ERR == iNewItem)
				delete pData;
			else if (i == Style)
				iIndex = iNewItem;
		}
	}

// evtl. gegebenen DarstellungsStil voreinstellen
	if (CB_ERR == iIndex)
		LocControl() -> ChangeCurrentIndex (0);		// ersten Stil auswählen
	else
		LocControl() -> ChangeCurrentIndex (iIndex);

return true;
}

StyleComboBox :: ~StyleComboBox (void) 
{
	LocControl() -> Clear ();	// alles löschen

// Speicher freigeben
//	DELETE (_InitFile);	// != NULL) delete _InitFile;
}

// Suchkriterium setzen 
StyleComboBox :: SearchMode StyleComboBox :: SetSearchMode (StyleComboBox :: SearchMode newMode) 
{
SearchMode oldMode = _SM;

	_SM = newMode;

return oldMode;
}


// EditControl für die Eingabe der Farbwerte ----------------------------------
// Konstruktor 
ColEdit :: ColEdit (pDialogWindow pW, ResID rsc, short iMax) 
	 : NumEdit (pW, rsc)
{
	m_iMax = iMax;
}

// Validierungsfunktion der FarbEingabe 
int ColEdit :: PostValidate (int Value) 
{
	if (Value < 0) return 0;
	if (Value > m_iMax) return m_iMax;
	return Value;
}

// DatenTyp, der In ColorListBox eingehängt wird ------------------------------
short CmpColor (Color C1, Color C2) 
{
long Diff = *(long *)&C1 - *(long *)&C2;

	if (Diff > 0) return 1;
	if (Diff < 0) return -1;
	return 0;
}

ColorItem :: ColorItem (Color C, char *Name) 
{
	_C = C;
	_Name = new char [strlen(Name)+3];
	if (_Name != NULL) {
		strcpy (_Name, "  ");
		strcat (_Name, Name);
	}
}

ColorItem :: ~ColorItem (void) 
{
	DELETE (_Name);
}

