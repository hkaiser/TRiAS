// Memberdefinieionen fuer Palette einer Sicht --------------------------------
// File: PALETTE.CXX

#include "trias02p.hxx"

#include "palette.hxx"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// Vergleich der Objekte, die in SightPalette drinhängen ----------------------
int CmpColors (void *C1, void *C2) {
long CmpVal = *(long *)C1 - *(long *)C2;

	if (CmpVal < 0) return -1;
	if (CmpVal > 0) return 1;
	return 0;
}

// Funktion, die VergleichsSchlüssel liefert ----------------------------------
void *ColorValue (void *pObj) { return &((CmpColor *)pObj) -> _C; }

// SichtPalette - Baum --------------------------------------------------------
SightPalette :: SightPalette (void) 
	      : CTree (ColorValue, CmpColors)
{
	// nothing to do
}


SightPalette :: ~SightPalette (void) 
{
	EveryDelete ();
}

void EXPORT02 SightPalette :: UserDelete (void *pObj) 
{
	((CmpColor *)pObj) -> /*CmpColor ::*/ ~CmpColor ();
}

// Generiert WindowsPalette aus eingelesenen Farbwerten -----------------------
HPALETTE SightPalette :: GetPalette (void) 
{
ulong numColors = Count();
HPALETTE hPalette;

	if (numColors > 0) {
	// Speicher für Palette anfordern
	LOGPALETTE *pPal = (LOGPALETTE *)new char [sizeof(LOGPALETTE) + 
						  numColors*sizeof(PALETTEENTRY)];
		if (pPal == NULL) {
			db_error (EC_NOMEMORY, RC_GetPalette);
			return NULL;
		}
	// Palette initialisieren
		pPal -> palNumEntries = (unsigned short)numColors;
		pPal -> palVersion = PALVERSION;

	CTable t(*this);
	short i = 0;

		for (t.First(); t.Valid(); t.Next(), i++) {
		CmpColorLock l(t);

			if (l) {
				pPal->palPalEntry[i].peRed = l -> Red();
				pPal->palPalEntry[i].peGreen = l -> Green();
				pPal->palPalEntry[i].peBlue = l -> Blue();
				pPal->palPalEntry[i].peFlags = (BYTE)0;
			}
		}
	// Palette generieren
		hPalette = CreatePalette (pPal);

	// Speicher wieder freigeben
		if (pPal) {
			delete (char *)pPal;
			pPal = NULL;
		}
	}

return hPalette;	// neue Palette liefern
}

// Funktion, die Palette einer Sicht liefert, alles bisherige ist Beiwerk -----
HPALETTE Sicht :: GetPalette (void) 
{
SightPalette SP;

	{
	long *Targets;
	short *iTypes;
	short numTargets;
	CmpColorCreator CCC(SP);
	CTable t(SP);

	// Farben aller Identifikatoren holen
		GetSightIDs (&Targets, numTargets, &iTypes);
		for (short i = 0; i < numTargets; i++) {
		VisInfo *pVI = NULL;

			GetIDfromSight (Targets[i], &pVI, iTypes[i]);	// VisInfo holen
			SP.AddToSightPalette (t, CCC, pVI);
			DELETE (pVI);
		}
		if (numTargets > 0) {
			DELETE (Targets);
			DELETE (iTypes);
		}

	// Farben aller EinzelObjekte holen
		GetSightONs (&Targets, numTargets, &iTypes);
		for (i = 0; i < numTargets; i++) {
		VisInfo *pVI = NULL;

			GetONfromSight (Targets[i], &pVI, iTypes[i]);
			SP.AddToSightPalette (t, CCC, pVI);
			DELETE (pVI);
		}
		if (numTargets > 0) {
			DELETE (Targets);
			DELETE (iTypes);
		}
	}	// letzte Farbe in Baum einfügen

return SP.GetPalette();	// Palette generieren
}

void SightPalette :: AddToSightPalette (CTable &t, CmpColorCreator &CCC, VisInfo *pVI) 
{
Color C;

	if (pVI == NULL) return;
	switch (pVI -> isA()) {
	case VT_Flaeche:
		C = ((FVisInfo *)pVI) -> SecColor();
		if (!t.Find (&C))
			ContCreate (CCC, CmpColor) (C);
		// hier durchfallen, da Fläche auch PrimColor hat

	case VT_Default:
	case VT_Linie:
	case VT_Text:
		C = pVI -> PrimColor();
		if (!t.Find (&C))
			ContCreate (CCC, CmpColor) (C);
		break;

	case VT_Punkt:
		C = ((PVisInfo *)pVI) -> SecColor();
		if (!t.Find (&C))
			ContCreate (CCC, CmpColor) (C);
		C = pVI -> PrimColor();
		if (!t.Find (&C))
			ContCreate (CCC, CmpColor) (C);
		break;

	default:
	// nichts machen, da alles unbestimmt ist
		return;
	}
}

///////////////////////////////////////////////////////////////////////////////
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

_TRIAS02_ENTRY 
bool EXPORT02 ExpandPalette (HPALETTE hPal, class VisInfo *pVI)
{
WORD iNumEntries = 0;

// 1. Größe der Palette festellen
	if (!hPal) return 0;
	GetObject (hPal, sizeof(WORD), (LPSTR)&iNumEntries);
	if (iNumEntries == 0) return false;

PALETTEENTRY PalEntry;
PALETTEENTRY NewPalEntry[2];
int iNewEntries = iNumEntries;

// 2. allgemeine Farbe testen
Color C = pVI -> PrimColor();
VisType VT = pVI -> isA();

	if (VT == VT_Flaeche || VT == VT_Punkt)
		ConvertPaletteIndex (hPal, C);
	
PALETTEENTRY *pCRef = (PALETTEENTRY *)&C;
int iIndex = GetNearestPaletteIndex (hPal, *(COLORREF *)pCRef);

	GetPaletteEntries (hPal, iIndex, 1, &PalEntry);
	if (*(COLORREF *)pCRef != *(COLORREF *)&PalEntry) {
		iNewEntries++;
		*(COLORREF *)&NewPalEntry[0] = *(COLORREF *)pCRef;
	}

// 3. wenn FlächenVisInfo vorliegt, Füllfarbe testen
	if (pVI -> isA() ==  VT_Flaeche) {
		C = ((FVisInfo *)pVI) -> SecColor();
		ConvertPaletteIndex (hPal, C);

		pCRef = (PALETTEENTRY *)&C;
		iIndex = GetNearestPaletteIndex (hPal, *(COLORREF *)pCRef);

		GetPaletteEntries (hPal, iIndex, 1, &PalEntry);
		if (*(COLORREF *)pCRef != *(COLORREF *)&PalEntry) {
			*(COLORREF *)&NewPalEntry[iNewEntries-iNumEntries] = *(COLORREF *)pCRef;
			iNewEntries++;
		}
	}
	else if (pVI -> isA() ==  VT_Punkt) {
	// 4. wenn PunktVisInfo vorliegt, Füllfarbe testen
		C = ((PVisInfo *)pVI) -> SecColor();
		ConvertPaletteIndex (hPal, C);

		pCRef = (PALETTEENTRY *)&C;
		iIndex = GetNearestPaletteIndex (hPal, *(COLORREF *)pCRef);

		GetPaletteEntries (hPal, iIndex, 1, &PalEntry);
		if (*(COLORREF *)pCRef != *(COLORREF *)&PalEntry) {
			*(COLORREF *)&NewPalEntry[iNewEntries-iNumEntries] = *(COLORREF *)pCRef;
			iNewEntries++;
		}
	}

	TX_ASSERT(iNewEntries <= iNumEntries+2);	// max. 2 neue Einträge

	if (iNewEntries > iNumEntries) {
	// Palette vergrößern
		ResizePalette (hPal, iNewEntries);
		SetPaletteEntries (hPal, iNumEntries, 
				   iNewEntries-iNumEntries, NewPalEntry);
		return true;
	}

return false;	// Palette wurde nicht erweitert
}

// Hinzufügen einer Farbe zur verwendeten Palette -----------------------------
_TRIAS02_ENTRY
bool ExpandPaletteColor (HPALETTE hPal, COLORREF C)
{
WORD iNumEntries = 0;

// 1. Größe der Palette festellen
	if (!hPal) return 0;
	GetObject (hPal, sizeof(WORD), (LPSTR)&iNumEntries);
	if (iNumEntries == 0) return FALSE;

PALETTEENTRY PalEntry;
int iNewEntries = iNumEntries;

// 2. übergebene Farbe testen
PALETTEENTRY &rCRef = (PALETTEENTRY &)C;
int iIndex = GetNearestPaletteIndex (hPal, (COLORREF &)rCRef);

	GetPaletteEntries (hPal, iIndex, 1, &PalEntry);
	if ((COLORREF &)rCRef != (COLORREF &)PalEntry) {
		iNewEntries++;
		(COLORREF &)PalEntry = (COLORREF &)rCRef;
	}

	if (iNewEntries > iNumEntries) {
	// Palette vergrößern
		ResizePalette (hPal, iNewEntries);
		SetPaletteEntries (hPal, iNumEntries, 
				   iNewEntries-iNumEntries, &PalEntry);
		return true;
	}

return false;	// Palette wurde nicht erweitert
}

