// Tools ChildFenster/ToolBox etc. -------------------------------------------
// File: TOOLS.HXX

#if !defined(_TOOLS_HXX)
#define _TOOLS_HXX

#define NUMTOOLS 	6	// Anzahl der Standard-Werkzeuge

#define NUMARROW 	0	// Nummern der Standard-Werkzeuge
#define NUMZOOM		1
#define NUMLUPE 	2
#define NUMSCHERE 	3
#define NUMLINEAL	4
#define NUMSCHRIFT	5

#if defined(OLD_TOOLBOX)

// Größe der WerkzeugBitmaps -------------------------------------------------
#define BMPSIZEX	24
#define BMPSIZEY	24

#if !defined(NOTOOLBOX)

// Bitmap(Werkzeug) in ToolBox -----------------------------------------------
class ToolBitmap : public BitmapObject {
protected:
	Bool _isActive;
	short _iToolID;
	
public:
		ToolBitmap (Point, Dimension, pBitmap, short);
		~ToolBitmap (void);

	Bool &isActive (void) { return _isActive; }
	short &iToolID (void) { return _iToolID; }

friend void EXPORTTRIAS ResetActFlag (void *);
friend void *GetToolIDPtr (void *);
};

// Werkzeugkasten -------------------------------------------------------------
class ToolBox : public CTree {
private:
	short _iToolID;		// Zähler für Werkzeuge
	short _iActTool;	// derzeit aktiviertes Werkzeug

protected:
	void UserDelete (void *pObj);
	
public:
// Konstruktor/Destruktor
		ToolBox (void);
		~ToolBox (void);

// Memberfunktionen
	short NumX (short = 0);	// Anzahl der Werkzeuge in X-Richtung
	short NumY (short = 0);	// Anzahl der Werkzeuge in Y-Richtung

	short PosX (short);	// Anzahl der Werkzeuge in X-Richtung
	short PosY (short);	// Anzahl der Werkzeuge in Y-Richtung

	void DrawTools (pWindow);	// Werkzeuge in pWindow zeichnen
	short Select (Point);		// angeklickte Bitmap finden

	Dimension GetSize (void) { return Dimension (25*NumX(), 25*NumY()); }
	Dimension GetToolSize (short iTool);
	Point GetToolPos (short iTool);

	short AddTool (pBitmap);
	Bool RemoveTool (short iTool);

	short iActTool (void) { return _iActTool; }
	Bool ToolCFlag (short iTool) { return (iTool == _iActTool); }
	short SetTool (short iTool);
};                
DeclareLock (ToolBox, ToolBitmap);
#endif // NOTOOLBOX

#if !defined(NOTOOLITERATOR)
class ToolIterator : public CTable {
public:
		ToolIterator (CTree &T);

	short FirstTool (void);
	short NextTool (void);
};
#endif	// NOTOOLITERATOR

#if !defined(NOTOOLWIND)                          
// ChildFenster für Werkzeugkasten --------------------------------------------
class ToolWind : public ChildAppWindow {
private:
	ToolBox _Tools;		// Werkzeugkasten
	pWindow _pParent;
	Brush *m_pBGBr;
	
	unsigned short m_fBGBrush : 1;
	
public:
	ToolBox &Tools (void) const { return (ToolBox &)_Tools; }

protected:
	void MouseButtonUp (MouseEvt);
	void Expose (ExposeEvt) { Tools().DrawTools (this); }
	void HelpRequest (HelpRequestEvt);

public:
// Konstruktor
		ToolWind (pWindow);
		~ToolWind (void);

// Member
	short SetTool (short iTool);	// neues Werkzeug aktivieren
	void PositionTools (Bool = TRUE);	// ToolBox positionieren

	Bool ToolCFlag (short iTool) { return Tools().ToolCFlag (iTool); }
	short iActTool (void) { return Tools().iActTool(); }
	
	short AddTool (pBitmap pBmp);
	Bool RemoveTool (short iTool);  
};
#endif // NOTOOLWIND

#endif // OLD_TOOLBOX

#endif // TOOLS_HXX
