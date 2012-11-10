// ObjTypDialogFenster --------------------------------------------------------
// File: OBJTYPE.CXX

#include "triaspre.hxX"

#include "objtype.h"
#include "objtype.hxx"


// Konstruktor ----------------------------------------------------------------
#pragma warning (disable:4355)

ObjTypDlg :: ObjTypDlg (pWindow pW, char *lpIdent, VisType VT) 
	   : DialogWindow (pW, SELECTOBJTYPE),
	     PunktObjekt (this, IDR_PUNKTOBJ),
	     LinienObjekt (this, IDR_LINIENOBJ),
	     FlaechenObjekt (this, IDR_FLAECHENOBJ),
	     TextObjekt (this, IDR_TEXTOBJ),
	     OKButton (this, IDOK),
	     CancelButton (this, IDCANCEL),
	     HelpButton (this, IDB_OBJTYPHELP),
	     CommentString (this, IDT_OBJTYPSIGNON)
{
// tempor‰r auﬂer Betrieb setzen
	HelpButton.Disable();

// Initialisieren
	PunktObjekt.SetState (FALSE);
	LinienObjekt.SetState (FALSE);
	FlaechenObjekt.SetState (FALSE);
	TextObjekt.SetState (FALSE);

// Voreinstellungen vornehmen
// Text korrigieren
char lpNewText[256];
ResString OldTypText (IDS_OLDOBJTYP, 255);

	switch (VT) {
	case VT_Default:
	default:
		wsprintf (lpNewText, ResString (IDS_NOOBJTYP, 255), lpIdent);
		_OT = OT_UNKNOWN;
		break;

	case VT_Punkt:
		wsprintf (lpNewText, OldTypText, lpIdent, ResString (IDS_OBJTYPPUNKT, 8).Addr());
		_OT = OT_PUNKT;
		PunktObjekt.SetState (TRUE);
		break;

	case VT_Linie:
		wsprintf (lpNewText, OldTypText, lpIdent, ResString (IDS_OBJTYPLINIE, 8).Addr());
		_OT = OT_KANTE;
		LinienObjekt.SetState (TRUE);
		break;

	case VT_Flaeche:
		wsprintf (lpNewText, OldTypText, lpIdent, ResString (IDS_OBJTYPFLAECHE, 8).Addr());
		_OT = OT_FLAECHE;
		FlaechenObjekt.SetState (TRUE);
		break;

	case VT_Text:
		wsprintf (lpNewText, OldTypText, lpIdent, ResString (IDS_OBJTYPTEXT, 8).Addr());
		_OT = OT_TEXT;
		TextObjekt.SetState (TRUE);
		break;
	}

// Text setzen
	CommentString.SetText (lpNewText);
}

#pragma warning (default:4355)

// Memberfunktionen -----------------------------------------------------------
void ObjTypDlg :: ButtonClick (ControlEvt e) {

	switch ((uint)e.GetControlID()) {
	case IDR_PUNKTOBJ:
		PunktObjekt.SetState (TRUE);
		LinienObjekt.SetState (FALSE);
		FlaechenObjekt.SetState (FALSE);
		TextObjekt.SetState (FALSE);
		_OT = OT_PUNKT;
		break;

	case IDR_LINIENOBJ:
		PunktObjekt.SetState (FALSE);
		LinienObjekt.SetState (TRUE);
		FlaechenObjekt.SetState (FALSE);
		TextObjekt.SetState (FALSE);
		_OT = OT_KANTE;
		break;

	case IDR_FLAECHENOBJ:
		PunktObjekt.SetState (FALSE);
		LinienObjekt.SetState (FALSE);
		FlaechenObjekt.SetState (TRUE);
		TextObjekt.SetState (FALSE);
		_OT = OT_FLAECHE;
		break;

	case IDR_TEXTOBJ:
		PunktObjekt.SetState (FALSE);
		LinienObjekt.SetState (FALSE);
		FlaechenObjekt.SetState (FALSE);
		TextObjekt.SetState (TRUE);
		_OT = OT_TEXT;
		break;

	case IDOK:
		EndDlg(1);	// OK und raus
		break;

	case IDCANCEL:
		EndDlg();	// Abbruch
		break;

	case IDB_OBJTYPHELP:
		break;

	default:
		break;
	}
}

