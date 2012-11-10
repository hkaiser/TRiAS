// Allgemeine Routinen fuer Import-/ExportFilter ------------------------------
// File: COMMFIL.CXX
               
#include "stdafx.h"
#include "AcadDXFImpl.h"
               
extern "C" {
	#include <string.h>
}

#include <attribs.hxx>
#include <impexp.hxx>

#include "acaddxf.hxx"		// KurzTextLen

// Identifikatorexport --------------------------------------------------------
IdentDescription :: IdentDescription (long ID, char *lpKText, 
				      VisInfo *pVI, HPALETTE hPal) 
{
// Identifikator merken
	_Ident = ID;

// Kurztext kopieren
	if (lpKText) {
		_Text = new char [strlen(lpKText)+1];
		if (_Text) { 
			strcpy (_Text, lpKText);
			AnsiToOem (_Text, _Text);
		}
	} else
		_Text = NULL;

// VisInfo kopieren
	if (pVI) {
		_pVI = (VisInfo *)pVI -> Copy();
	// wenn VisInfo für Fläche bestimmt ist
		if (_pVI -> isA() == VT_Flaeche) {
		// FüllFarbe konvertieren
		FVisInfo *pFVI = (FVisInfo *)_pVI;

			GetPaletteEntries (hPal, pFVI -> SecColor().Red(), 1,
					   (PALETTEENTRY *)&(pFVI -> SecColor()));
			pFVI -> SecColor().Reserved() = 0;
			GetPaletteEntries (hPal, pFVI -> PrimColor().Red(), 1,
					   (PALETTEENTRY *)&(pFVI -> PrimColor()));
			pFVI -> PrimColor().Reserved() = 0;
		}
	} else
		_pVI = NULL;
}

IdentDescription :: IdentDescription (IdentDescription &ID) 
{
// Identifikator merken
	_Ident = ID._Ident;

// Kurztext kopieren
	if (ID._Text && *ID._Text) 
	{
		_Text = new char [strlen(ID._Text)+1];
		if (_Text) 
			strcpy (_Text, ID._Text);
	} 
	else
	{
		_Text = new char [KurzTextLen];
		if (!_Text)
			return;
		ultoa (ID._Ident, _Text, DEX_GetIdBase ());			
	}

// VisInfo kopieren
	if (ID._pVI)
		_pVI = (VisInfo *)ID._pVI -> Copy();
	else
		_pVI = NULL;
}

// Destruktor
IdentDescription :: ~IdentDescription (void) 
{
// Speicher wieder freigeben
	if (_Text) { delete _Text; _Text = NULL; }
	if (_pVI) { delete _pVI; _pVI = NULL; }
}

// MerkmalsDescription --------------------------------------------------------
MerkmalDescription :: MerkmalDescription (long MC, char *lpKText, 
					  short MTyp, short MLen) 
{
// MCode merken
	_MCode = MC;

// Kurztext kopieren
	if (lpKText) {
		_Text = new char [strlen(lpKText)+1];
		if (_Text) {
			strcpy (_Text, lpKText);
			AnsiToOem (_Text, _Text);
		}
	} else
		_Text = NULL;

// Typ und Länge merken
	_MTyp = MTyp;
	_MLen = MLen;
}

MerkmalDescription :: MerkmalDescription (MerkmalDescription &MD) 
{
// MerkmalsCode merken
	_MCode = MD._MCode;

// Kurztext kopieren
	if (MD._Text && *MD._Text) 
	{
		_Text = new char [strlen(MD._Text)+1];
		if (_Text) 
			strcpy (_Text, MD._Text);
	} 
	else
	{
		_Text = new char [KurzTextLen];
		if (!_Text)
			return;
		ultoa (MD._MCode, _Text, DEX_GetMkBase ());			
	}

// Typ und Länge kopieren
	_MTyp = MD._MTyp;
	_MLen = MD._MLen;
}

// Destruktor -----------------------------------------------------------------
MerkmalDescription :: ~MerkmalDescription (void) 
{
// Speicher wieder freigeben
	if (_Text) { delete _Text; _Text = NULL; }
}
//---------------------------------------------------------------------------
