// Einstellen der TextrechercheParameter
// File: MKRECH.CXX

#include "triaspre.hxx"

#if !defined(WIN16)
#include <dirisole.h>
#include "extmain3.hxx"
#endif

#include "textsrch.hxx"
#include "mkrech.hxx"

extern HelpDisplay *IrisHD;
extern ExtDirisWindow *CurrActDirisW;

// Konstruktor ----------------------------------------------------------------
#pragma warning (disable: 4355)

TextRechercheParams :: TextRechercheParams (pWindow pW, int Mode, long locMK) 
		     : DialogWindow (pW, ResID (RECHMERKMAL)),
		       RechMerkmal (this, ResID (IDL_MKRECHERCHE)),
		       OKButton (this, IDB_MKOK),
		       CancelButton (this, IDB_MKCANCEL),
#if defined(WIN16)
		       HelpButton (this, IDB_MKHELP),
#endif // WIN16
		       ExactSearch (this, IDR_EXACT),
		       InExactSearch (this, IDR_UNEXACT),
		       SubStringSearch (this, IDR_PARTRECH)
{
// EierUhr anzeigen
CEierUhr Wait (this);

	m_iMkBase = DEX_GetMkBase();

// aktuellen Mode merken
	_SMode = Mode;
	_MKSearch = locMK;
// ListBox mit allen TextMerkmalsKodes füllen
	FillMerkmale ();

// HelpButton inaktivieren
//	HelpButton.Disable();
// RadioButton setzen
	switch (_SMode) {
	case ExactMatch:
		ExactSearch.SetState (TRUE);
		break;

	case InexactMatch:
		InExactSearch.SetState (TRUE);
		break;

	case SubStringMatch:
		SubStringSearch.SetState (TRUE);
		break;
	}
// Focus auf ListBox
	RechMerkmal.SetFocus();
}

#pragma warning (default: 4355)

// Alle TextMerkmalsCodes der DB finden und in ListBox auflisten --------------
ErrCode TextRechercheParams :: FillMerkmale (void) 
{
ErrCode EC;
ExtDirisWindow *pIW = CurrActDirisW;
GeoDB &rDB = pIW -> DBO().DB();
DB_ADDR dba(rDB.DBDesc());
char OutBuff[60];
CActDB ActDB (rDB);	// DB aktivieren

	{
	// Fehler WC_NOTFOUND ignorieren
	ErrInstall EI (WC_NOTFOUND);

	// erstes Merkmal suchen
		EC = (ErrCode)z_keyfirst (&dba, MK);
		if (EC != EC_OKAY) {
		// Fehler aufgetreten
			if (EC == WC_NOTFOUND) 
				return EC_OKAY;         // nichts gefunden: OK
			return EC;                      // sonstiger Fehler
		}

	// für alle weiteren Merkmale
		do {
		long MCode;

		// Merkmal aus Schlüsseldatei lesen
			EC = (ErrCode)z_keyread (rDB.DBDesc(), &MCode);
			if (EC != EC_OKAY) 
				break;

		PBD_Merkmal PBD_MK(&pIW -> DBO().PbdDB(), MCode);
		// feststellen, ob MCode ein TextMerkmal ist
			if (PBD_MK.isA() == 'a') {
			// zu ListBox hinzufügen
				if (m_iMkBase == 10) {
					wsprintf (OutBuff, "%08ld:%-45s", 
							   MCode, PBD_MK.GetKurzText());
				} else {
					wsprintf (OutBuff, "%08lx:%-45s", 
							   MCode, PBD_MK.GetKurzText());
				}
				RechMerkmal.AddString (OutBuff);
			}
		// nächsten Schlüssel suchen
			z_keyfind (&dba, MK, &MCode);
			EC = (ErrCode)z_keynext (&dba, MK);
		} while (EC == EC_OKAY);
	} // Fehlerbearbeitung wieder einstellen
	if (EC == WC_NOTFOUND) 
		EC = EC_OKAY;           // nichts mehr gefunden: OK

// Voreinstellung vonehemen
	if (m_iMkBase == 10)
		wsprintf (OutBuff, "%08ld:", _MKSearch);
	else
		wsprintf (OutBuff, "%08lx:", _MKSearch);

int iIndex = -1;

	if ((iIndex = RechMerkmal.FindString (OutBuff)) >= 0)
	// derzeit aktives Merkmal selektieren
		RechMerkmal.ChangeCurrentIndex (iIndex);

return EC;
}


// EventHandler für TextRechercheParams ---------------------------------------
void TextRechercheParams :: ButtonClick (ControlEvt e) 
{
	switch ((uint)e.GetControlID()) {
	case IDB_MKOK:                  // OK -- Ende und raus
		EndDlg (1);
		break;

	case IDB_MKCANCEL:              // Cancel -- Abbrechen und raus
		EndDlg ();
		break;

	case IDB_MKHELP:                // Hilfe anfordern
		IrisHD -> Show (IDB_MKHELP);
		break;

	case IDR_EXACT:                 // Exakte Suche einschalten
		_SMode = ExactMatch;
		break;

	case IDR_UNEXACT:               // ÄhnlichkeitsSuche
		_SMode = InexactMatch;
		break;

	case IDR_PARTRECH:              // TeilBegriffe suchen
		_SMode = SubStringMatch;
		break;
	}
}

void TextRechercheParams :: ListBoxSel (ControlEvt) 
{
char Text[60];
// MerkmalsKode aus ListBox bestimmen
	RechMerkmal.GetCurrentString (Text);    // aktuellen Eintrag lesen
	_MKSearch = strtoul (Text, NULL, m_iMkBase);
}


void TextRechercheParams :: ListBoxClk (ControlEvt) 
{
// DoppelClick auf Listbox --> fertig und raus
	EndDlg (1);
}

