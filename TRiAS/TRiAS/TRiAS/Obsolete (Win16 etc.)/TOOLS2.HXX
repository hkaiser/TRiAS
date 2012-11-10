// Tools ChildFenster
// File: TOOLS.HXX

// IRISWIN: %W%	%E%


#if !defined(_TOOLS_HXX)
#define _TOOLS_HXX

extern "C" {
// Deklarationen zur Anpassung der ChildFensterGrî·e an die ToolBitmap
	typedef struct tagRECT {
		int left; int top;
		int right; int bottom;
	} RECT;
	void _far _pascal AdjustWindowRect (RECT *, long, Bool);
	#define WS_CHILD	0x40000000L
	#define WS_CAPTION	0x00C00000L
	#define BS_OWNERDRAW	0x0BL
}

const int NUMTOOLS = 4;	// Anzahl der Werkzeuge
const int NUMARROW = 0;	// Nummer der Werkzeuge
const int NUMLUPE = 1;
const int NUMSTIFT = 2;
const int NUMSCHERE = 3;

// Werkzeugkasten -------------------------------------------------------------
// Klasse fÅr OwnerDraw - PushButtons -----------------------------------------
class OwnerDrawPushButton : public PushButton {
public:
		OwnerDrawPushButton (pDialogWindow pW, ResID Id) 
			: PushButton (pW, Id) {
			SetStyle (BS_OWNERDRAW);
		}
		OwnerDrawPushButton (pWindow pW, uint i, Point p, Dimension d)
			: PushButton (pW, i, p, d) {
			SetStyle (BS_OWNERDRAW);
		}
};


// OwnerDrawPushButtonWindow definieren ---------------------------------------
class OwnerDrawPBWindow : public ControlWindow {
private:
	Bool _OnOff;			// Status des PushButtons;
	Point _Pos;			// Position im Fenster
	Bitmap _On;			// Bitmaps
	Bitmap _Off;

protected:
	void Expose (ExposeEvt);
	void MouseButtonDn (MouseEvt);
	void MouseButtonUp (MouseEvt);

public:
		OwnerDrawPBWindow (pWindow, uint, Point, Dimension, Bool);
		~OwnerDrawPBWindow (void) {
			delete (OwnerDrawPushButton *)GetControl ();
		}
};



// ChildFenster fÅr Werkzeugkasten --------------------------------------------
class ToolWind : public ChildAppWindow {
private:
	OwnerDrawPBWindow *_pTools[NUMTOOLS];

public:
// Konstruktor
		ToolWind (pWindow);
};

#endif // TOOLS_HXX
