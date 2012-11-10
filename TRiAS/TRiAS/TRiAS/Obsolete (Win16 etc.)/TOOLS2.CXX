// Routinen fÅr ToolsFenster
// File: TOOLS.CXX

#if defined(sccs)
static char SccsId[] = "IRISWIN: %W%	%E%";
#endif

#include <commonvu.hxx>
#include <drawobj.hxx>
#include "iris.h"
#include "errcodes.hxx"
#include "tools.hxx"

extern "C" {
// ZIPEDB-Prototypen
	#include "protos.h"
}

extern Window *CurrActW;

int actTool = NUMARROW;		// aktiviertes Werkzeug

// ChildFenster fÅr Werkzeugkasten --------------------------------------------
ToolWind :: ToolWind (pWindow pParent) :
	    ChildAppWindow (pParent)	// Fenster 
{
Rectangle MainCanvas = CurrActW -> CanvasRect ();

#ifdef MSWIND
// ACHTUNG: diese Stelle ist MS-Windows-spezifisch
// -------
// ToolBoxFenster in seiner Grî·e festlegen
// So ein Blîdsinn. MS-Windows und CommonView interpretieren offensichtlich
// die Y-Koordinaten eine Rechtecks (RECT bzw. Rectangle) unterschiedlich.
// Was bei dem einen Oben ist, ist bei dem anderen Unten, mit einem Minus dazu.
// Es lebe die Standardisierung.
Rectangle TBRect (Point (0, 0), Point (131, 32));
	AdjustWindowRect ((RECT *)&TBRect, WS_CHILD|WS_CAPTION, FALSE);
	ChangeSize (Dimension (TBRect.Right()-TBRect.Left(), 
			       TBRect.Bottom()-TBRect.Top()));
// ToolBoxFenster positionieren
	ChangePosition (Point (MainCanvas.Right()-2*(TBRect.Right()-TBRect.Left()), 
			       MainCanvas.Top()+TBRect.Top()-TBRect.Bottom()-1));
#endif // MSWIND

// Caption fÅr ToolBoxFenster setzen
	SetCaption (ResString (IDS_TOOLBOXCAPTION, 10));
// PushButtons generieren
	_pTools[NUMARROW] = new OwnerDrawPBWindow (this, ARROW, Point (0, 1), Dimension (32, 32), TRUE);
	_pTools[NUMLUPE] = new OwnerDrawPBWindow (this, LUPE, Point (33, 1), Dimension (32, 32), FALSE);
	_pTools[NUMSTIFT] = new OwnerDrawPBWindow (this, STIFT, Point (66, 1), Dimension (32, 32), FALSE);
	_pTools[NUMSCHERE] = new OwnerDrawPBWindow (this, SCHERE, Point (99, 1), Dimension (32, 32), FALSE);
	for (register int i = 0; i < NUMTOOLS; i++) {
		if (_pTools[i] == NULL) {
			db_error (EC_NOMEMORY, RC_ctToolWind);
			return;
		} else {
			_pTools[i] -> Show ();	// Anzeigen
		}
	}
}


// Konstruktor fÅr OwnerDrawPushButtonWindow
OwnerDrawPBWindow :: OwnerDrawPBWindow (pWindow pW, uint usrId, 
					Point p, Dimension d, Bool OnOff) 
	   : ControlWindow (new OwnerDrawPushButton (pW, usrId, p, d)),
	     _Off (usrId),	// Nummern mÅssen fortlaufend sein
	     _On (usrId+1)
{
	_OnOff = OnOff;
	_Pos = p;
}

// OwnerDrawPushButton zeichnen
void OwnerDrawPBWindow :: Expose (ExposeEvt) {

	if (_OnOff) {
	// Taste gedrÅckt
	BitmapObject BMO (_Pos, _On.GetSize(), &_On);
		Draw (&BMO);
	} else {
	// Taste nicht gedrÅckt
	BitmapObject BMO (_Pos, _Off.GetSize(), &_Off);
		Draw (&BMO);
	}
}

void OwnerDrawPBWindow :: MouseButtonDn (MouseEvt) {
return;
}


void OwnerDrawPBWindow :: MouseButtonUp (MouseEvt) {
return;
}
