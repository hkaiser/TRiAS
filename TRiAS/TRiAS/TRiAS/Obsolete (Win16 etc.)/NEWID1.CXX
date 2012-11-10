// Memberfunktionen fuer ModID
// File: NEWID.CXX

#if defined(sccs)
static char SccsId[] = "IRISWIN: %W%	%E%";
#endif

#include "newid.htp"

extern "C" {
	#include <windows.h>
}


#include <commonvu.hxx>

extern "C" {
	#include <stdlib.h>
	#include <string.h>

	#include <xtension.h>
	#include <xtensnx.h>
}

#include <ristypes.hxx>
#include <errcodes.hxx>
#include <numedit.hxx>

#include "iris.h"
#include "newid.hxx"

// globale Daten
extern HelpDisplay *IrisHD;

const short IDENTLEN = 15;	// max. 9 Stellen in ID

// Konstruktor ---------------------------------------------------------------
#pragma warning (disable: 4355)

NewIdentDlg :: NewIdentDlg (pWindow pW, long ON, long oldId, 
			    const char *lpCaption, short iBase) 
	     : DialogWindow (pW, NEWIDENT),
	       OKButton (this, IDOK),
	       CancelButton (this, IDCANCEL),
	       HelpButton (this, IDB_NEWIDHELP),
	       NewId (this, IDE_NEWIDENT, iBase),
	       OldId (this, IDE_OLDIDENT, iBase),
	       OldText (this, IDT_OLDIDENT)
{
// eingegeben Id nicht mit interener Funktion testen
	NewId.SetNumEditMode (NumEdit :: NEM_NoTest);
	OldId.SetNumEditMode (NumEdit :: NEM_NoTest);

// EditControl initialisieren
	NewId.SetTextLimit (IDENTLEN);	// Zeichen begrenzen
	OldId.SetTextLimit (IDENTLEN);

	if (lpCaption == NULL) {
	// Caption mit ObjektNummer fttern
	char oldCaption[51];
	char newCaption[70];

		GetCaption (oldCaption, 50);
		wsprintf (newCaption, oldCaption, ON);
		SetCaption (newCaption);
	} else
		SetCaption (lpCaption);

	if (oldId != -1L) {
	char OldIdText[30];

		ultoa (oldId, OldIdText, DEX_GetIdBase()); 
		OldId.GetEditControl() -> SetText (OldIdText);

	// wenn nur Objekt ge„ndert werden soll, dann OldId passivieren
		OldId.Disable();
		NewId.SetFocus();
	} else if (ON != -1L) {
	// evtl. zu modifizierenden Ident eingeben
		OldId.SetFocus();
	} else {
	// Objekt neu erfassen
		OldId.Hide();
		OldText.Hide();
		NewId.SetFocus();
	}
}

#pragma warning (default: 4355)

// Memberfunktionen -----------------------------------------------------------
void NewIdentDlg :: ButtonClick (ControlEvt e) 
{
char NewIdentText[IDENTLEN+1];
char OldIdentText[IDENTLEN+1];

	switch ((uint)e.GetControlID()) {
	case IDOK:		// OK 
		{
		short iBase = DEX_GetIdBase();

		NewId.GetEditControl() -> GetText (NewIdentText, IDENTLEN);
		OldId.GetEditControl() -> GetText (OldIdentText, IDENTLEN);
		if (strlen (NewIdentText) > 0)
			_NewIdent = strtoul (NewIdentText, NULL, iBase);
		else
			_NewIdent = -1L;
		if (strlen (OldIdentText) > 0)
			_OldIdent = strtoul (OldIdentText, NULL, iBase);
		else
			_OldIdent = -1L;
		EndDlg (1);
		}
		break;

	case IDCANCEL:
		EndDlg ();	// raus und vorbei
		break;

	case IDB_BUFFHELP:
		IrisHD -> Show (IDB_NEWIDHELP);
		break;
	}
}

