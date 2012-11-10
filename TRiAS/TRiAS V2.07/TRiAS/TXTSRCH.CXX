// MemberFunktionen fuer TextSuchFenster
// File: TXTSRCH.CXX

#include "triaspre.hxx"

#include <xtensnxx.h>

#if defined(WIN32)
#include <dirisole.h>
#include "extmain3.hxx"
#endif

#include "mkrech.hxx"
#include "textsrch.hxx"

extern ExtDirisWindow *CurrActDirisW;
extern Bool TextSearchCFlag;
extern TextRechercheDlg *pTextSearch;

int TextMode = InexactMatch;           	// SuchMode TextRecherche
extern long TextCode;              	// SuchCode

bool IrisWind :: ShowTextRecherche (void) 
{
TextRechercheParams TRP (this, TextMode, TextCode);

// Dialogfenster anzeigen
	TRP.Show();
// neue Parameter abfragen
	if (TRP.Result()) {
		TextMode = TRP.GetSearchMode();
		TextCode = TRP.GetMKSearch ();
	// FensterParameter neu setzen
		if (pTextSearch) 
			pTextSearch -> AdjustRechMode (TextMode, TextCode);
		return true;
	}

return false;
}

// Konstruktor ---------------------------------------------------------------
#pragma warning (disable: 4355)

TextRechercheDlg :: TextRechercheDlg (pWindow pW, long lMCode, int Mode) 
		  : ModeLessDialog (pW, ResID (TEXTRECHERCHE)),
		    SuchButton (this, IDB_SEARCH),
		    SLE_SuchText (this, IDE_SEARCHTEXT)
{
// EditFenster initialisieren
	memset (_SuchText, '\0', MAXTEXTLEN+1);         // Suchtext löschen
	SLE_SuchText.SetTextLimit (MAXTEXTLEN);         // Zeichen begrenzen

// entsprechend Suchmode Caption setzen
	AdjustRechMode (Mode, lMCode);
	SLE_SuchText.SetFocus();
}

#pragma warning (default: 4355)

// Memberfunktionen
void TextRechercheDlg :: ButtonClick (ControlEvt e) 
{
	switch ((uint)e.GetControlID()) {
	case IDB_SEARCH:                // OK - Recherche starten
	// Recherche durchführen
		SLE_SuchText.GetText (_SuchText, MAXTEXTLEN);
		AnsiToOem (_SuchText, _SuchText);
		if (strlen (_SuchText) > 0) {
		// Focus an Hauptfenster übergeben
			GetParent() -> SetFocus();

		// Textrecherche selbst
			SuchButton.Disable();
			TextRecherche();
			SuchButton.Enable();
		}
		break;
	}
}


// abschlieáende Aktionen
Bool TextRechercheDlg :: QueryClose (Event) 
{
// Fenster wird zerlegt
	if (TextSearchCFlag) {
	// wenn über SystemMenu geschlossen, dann Menupunkt simulieren
		PostMessage (GetParent() -> Handle (API_WINDOW_HWND), WM_COMMAND, 
			     IDM_TEXTSEARCH, 0);
	}
	
return TRUE;    // auf jeden Fall schließen
}


// Überschrift entsprechend dem aktuallen Suchmode setzen
void TextRechercheDlg :: AdjustRechMode (int Mode, long lMCode) 
{
register int SMode;

	_SMode = Mode;          // SuchMode setzen
	_SearchCode = lMCode;       // SuchCode setzen
// Überschrift verändern
	switch (Mode) {
	case ExactMatch:
		SMode = IDS_EXACTMATCH;
		break;

	case InexactMatch:
		SMode = IDS_INEXACTMATCH;
		break;

	case SubStringMatch:
		SMode = IDS_SUBSTRINGMATCH;
		break;
	}
	SetCaption (ResString (SMode, 40));
}


// TextRecherche -- finden aller Objekte, die ein bestimmtes Textmerkmal besitzen
// weiterhin anzeige dieser Objekte in einem ObjektInfoFenster
ErrCode TextRechercheDlg :: TextRecherche (void) 
{
ObjFeld Objekte;                        // hier werden die Objekte gesammelt
CEierUhr Wait (CurrActDirisW);
ErrInstall EI (WC_NOON, ReportNotFoundError);

// alle Objekte finden, die dieses Kriterium erfüllen
ExtDirisWindow *pIW = CurrActDirisW;

	if (EC_OKAY != pIW -> DBO().DB().FindText (_SearchCode, _SMode, _SuchText, Objekte))
		return (ErrCode)db_error (WC_NOON, RC_TextRecherche);

// nach Identifikatoren filtern
	pIW -> DBO().DB().IdFilter (Objekte, pIW -> DBO().Idents());

// Anzeige dieser Objekte in einem ObjektInfoFenster
	if (Objekte.Count() > 0) {
	DEXXCREATEOBJEKTINFO crOI;

		crOI.dwSize = sizeof(DEXXCREATEOBJEKTINFO);
		crOI.lpCaption = StrDup (ResString (IDS_TEXTSEARCHCAPTION, 30), RC_TextRecherche);
		crOI.lcObjs = &Objekte;
		crOI.pcMColor = new Color(GREEN);
		crOI.ppntPos = new Point (0, 50);
		crOI.fcnPos = NULL;
		crOI.pData = NULL;

		DEXX_CreateObjektInfo (crOI);	// RechercheFenster generieren

		DELETE (crOI.lpCaption);
		DELETE (crOI.pcMColor);
		DELETE (crOI.ppntPos);
	} else 
		return (ErrCode)db_error (WC_NOON, RC_TextRecherche);

return EC_OKAY;
}


