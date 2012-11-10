// Routinen fuer ToolsFenster -------------------------------------------------
// File: TOOLS.CXX

#include "triaspre.hxx"

#include "tools.hxx"

// Variablen für die Hilfegenerierung ----------------------------------------
extern HelpDisplay *IrisHD;
extern Bool wasHelpEvt;

// ChildFenster für Werkzeugkasten -------------------------------------------
ToolWind :: ToolWind (pWindow pParent) :
#if !defined(WIN32)
	    ChildAppWindow (pParent, (AppWindow *)NULL),   // Fenster
#else
		ChildAppWindow (pParent, NULL, WS_EX_TOOLWINDOW),
#endif // !WIN32
	    _Tools ()
{
	_pParent = pParent;	// HauptFenster merken

	Hide();			// erstmal nicht sichtbar
	SetStyle (WS_BORDER);
	EnableBorder (NonSizingBorder);
	
	m_pBGBr = new Brush;
	if (m_pBGBr) {
		m_pBGBr = ChangeBackground (m_pBGBr);        // Hintergrund setzen
		m_fBGBrush = TRUE;
	} else
		m_fBGBrush = FALSE;

	PositionTools ();	// ToolBox positionieren

// Caption für ToolBoxFenster setzen
	SetCaption (ResString (IDS_TOOLBOXCAPTION, 20));

	EnableHelp (TRUE, IrisHD);	// Hilfe einschalten
}


ToolWind :: ~ToolWind (void)
{
	if (m_fBGBrush) {
		m_pBGBr = ChangeBackground (m_pBGBr);
		DELETE (m_pBGBr);
	}
}

	
// ToolBox Rechts oben im Hauptfenster positionieren --------------------------

#if defined(__WATCOMC__)
#pragma warning 604 5;		// lookahead required
#pragma warning 595 5;		// resolved as an expression
#endif

void ToolWind :: PositionTools (Bool iFlag) 
{
// ACHTUNG: diese Stelle ist CommonVu/MS-Windows-spezifisch
// -------
// ToolBoxFenster in seiner Größe festlegen
// So ein Blödsinn. MS-Windows und CommonView interpretieren offensichtlich
// die Y-Koordinaten eines Rechtecks (RECT bzw. Rectangle) unterschiedlich.
// Was bei dem einen Oben ist, ist bei dem anderen Unten, mit einem Minus dazu.
// Es lebe die Standardisierung.
Rectangle WRc;	// FensterPosition

	if (!iFlag) WRc = WindowRect();

Rectangle MRc = _pParent -> CanvasRect ();
Rectangle TBRc (Point (0, 0),
		Point (Tools().GetSize().Width()+1, Tools().GetSize().Height()+1));

#if defined(WIN32)
	AdjustWindowRectEx ((RECT *)&TBRc, (WS_CHILD|WS_CAPTION), false, IsWin40() ? WS_EX_TOOLWINDOW : 0);
#else
	AdjustWindowRect ((RECT *)&TBRc, (WS_CHILD|WS_CAPTION), false);
#endif // WIN32
	ChangeSize (Dimension (TBRc.Right()-TBRc.Left(), TBRc.Bottom()-TBRc.Top()));

// ToolBoxFenster positionieren
	if (iFlag) {
		ChangePosition (Point (MRc.Right() - 2*(TBRc.Right()-TBRc.Left()),
				       MRc.Top()+TBRc.Top()-TBRc.Bottom()-1));
	} else {
	// Position erhalten
	Rectangle NewRc = WindowRect();
	Point UL = WRc.UpperLeft();

		ChangePosition (Point (WRc.Left(),
				       UL.Y() - (NewRc.Top()-NewRc.Bottom()) ));
	}
}


// Werkzeug wechseln (MouseClick) ---------------------------------------------
void ToolWind :: MouseButtonUp (MouseEvt e) 
{
	if (e.isLeftButton ()) {
		Tools().Select (e.Where ());	// welches Werkzeug
		RePaint ();     		// neu zeichnen
		Update();
	}
}

// neues Werkzeug von außen aktivieren ----------------------------------------
short ToolWind :: SetTool (short newTool) 
{
// jetzt also neues Werkzeug auswählen
short oldTool = Tools().SetTool (newTool);

	RePaint ();	// Auswahl anzeigen
	Update();

return oldTool;         // vorher ausgewähltes Werkzeug liefern
}


// HelpRequest-Eventhandler --------------------------------------------------
void ToolWind :: HelpRequest (HelpRequestEvt e) 
{
	if (e.RequestType() == HelpWindow && e.GetWindowArea() == WindowCanvas) 
		IrisHD -> Show (IDM_SELTOOLS);
}


short ToolWind :: AddTool (pBitmap pBmp) 
{ 
short iNewTool = Tools().AddTool (pBmp); 

	PositionTools (FALSE);
	RePaint(); 
	Update();

return iNewTool;
}


Bool ToolWind :: RemoveTool (short iTool) 
{ 
Bool iResult = Tools().RemoveTool (iTool); 

	PositionTools (FALSE);
	RePaint(); 
	Update();

return iResult;
}


// Werkzeugkasten -------------------------------------------------------------
int ShortCmp (void *pObj1, void *pObj2);

ToolBox :: ToolBox (void) 			// Konstruktor
	 : CTree (GetToolIDPtr, ShortCmp)
{
	_iActTool = -1;		// derzeit kein aktives Werkzeug
	_iToolID = -1;		// eindeutiges ID für Werkzeuge
		
// Standard-Werkzeuge installieren/initialisieren
	AddTool (new Bitmap (ResID (ARROW)));
	AddTool (new Bitmap (ResID (ZOOM)));
	AddTool (new Bitmap (ResID (LUPE)));
	AddTool (new Bitmap (ResID (SCHERE)));
	AddTool (new Bitmap (ResID (LINEAL)));
//	if (GetGeoDBVersion() >= NEWDBVERSION)
//		AddTool (new Bitmap (ResID (GRAYSCHRIFT)));
//	else
		AddTool (new Bitmap (ResID (SCHRIFT)));
		
	SetTool (NUMARROW);	// Pfeil aktiv
}

// Destruktor -----------------------------------------------------------------
ToolBox :: ~ToolBox (void) 
{
	EveryDelete();
}


// Werkzeuge neu zeichnen ----------------------------------------------------
void ToolBox :: DrawTools (pWindow pW) 
{
CTable t (*this);

// Bitmaps zeichnen
	for (t.First(); t.Valid(); t.Next()) {
	ToolBitmapLock l(t); 
	ToolBitmap *pTB = (ToolBitmap *)l;
		
		if (!l) continue;
		if (iActTool() == l -> iToolID()) {	// aktives Werkzeug invertiert zeichnen
		Brush Br (WhiteBrush);
		Pen P (SolidLine, 1, WHITE);

			{	// Hintergrund weiß malen
			RectangleObject Rc (pTB -> GetPosition(), pTB -> GetSize(), 
					    &P, &Br);

//				InflateRect ((RECT *)&Rc, 1, 1);
				pW -> Draw (&Rc);
			}
			pTB -> ChangeRop (ROP_XOR);
			pW -> Draw (pTB);
		} else {
			pTB -> ChangeRop (ROP_Overwrite);
			pW -> Draw (pTB);
		}
	}
}


// Werkzeugauswahl ------------------------------------------------------------
short ToolBox :: Select (Point Pt) 
{
CTable t (*this);

	for (t.First(); t.Valid(); t.Next()) {
	ToolBitmapLock l(t); 
		
		if (l && l -> HitTest (Pt)) {
			SetTool (l -> iToolID());
			return _iActTool;
		}
	}

return NUMARROW;
}


// Werkzeug von außen neu setzen ---------------------------------------------
void EXPORTTRIAS ResetActFlag (void *pObj)		// Rücksetzen eines ActFlags
{
	((ToolBitmap *)pObj) -> isActive() = FALSE;
}


short ToolBox :: SetTool (short iTool)
{       
// wenn altes Werkzeug wieder aktiviert werden soll, wieder raus
	if (iTool == _iActTool) return iTool;                    
	
short iOldTool = _iActTool;
CTable t(*this);

	Every (ResetActFlag);		// akivFlag bei allen zurücksetzen

	if (t.Find (&iTool))	{	
	ToolBitmapLock l(t);		// gewünschtes Werkzeug aktivieren

		if (l) {
			l -> isActive() = TRUE;
			_iActTool = l -> iToolID();
			DEXN_ActiveToolChanged (_iActTool);
		}
	}
#if !defined(WIN32)
	else if (t.First()) {
	ToolBitmapLock l(t);		// erstes Werkzeug aktivieren

		if (l) {
			l -> isActive() = TRUE;
			_iActTool = NUMARROW;
			DEXN_ActiveToolChanged (NUMARROW);
		}
	}
#else
	else {
		_iActTool = iTool;			// unbekanntes Werkzeug, wird von anderen verwaltet
		DEXN_ActiveToolChanged (_iActTool);
	}
#endif // !WIN32

return iOldTool;
}


// Position eines Werkzeuges in beiden Richtungen ----------------------------
short ToolBox :: PosX (short iTool)
{
	if (Count() <= 6) return (iTool-1);
	else		  return (iTool+3) % 4;
}


short ToolBox :: PosY (short iTool)
{
	if (Count() <= 6) return 0;
	else {
	short numX = NumX();

		return NumY() - ((iTool+numX-1) / numX);
	}
}


// Anzahl der Werkzeugreihen in beiden Richtungen ----------------------------
short ToolBox :: NumX (short i)
{       
	if (Count()+i <= 6) return (short)Count()+i;
	else		    return 4;
}

short ToolBox :: NumY (short i) 
{
	if (Count()+i <= 6) return 1;
	return ((short)Count()+i + 3) / 4;
}


// Ein neues Werkzeug in die Werkzeugkiste legen -----------------------------	        
short ToolBox :: AddTool (pBitmap pBmp)
{
// neues Werkzeug hinzufügen
	if (pBmp == NULL) return -1;
	
ToolBitmapCreator TBCr (*this);

	ContCreate (TBCr, ToolBitmap)(Point ((BMPSIZEX+1)*PosX(short(Count())+1)+1, 
					 (BMPSIZEY+1)*PosY(short(Count())+1)+1), 
				  Dimension (BMPSIZEX, BMPSIZEY), pBmp, ++_iToolID);

	TBCr.Insert();	// wirklich einfügen

// die Position aller Bitmaps neu berechnen
CTable t (*this);
short iCnt = 1;

	for (t.First(); t.Valid(); t.Next(), iCnt++) {
	ToolBitmapLock l (t);

		if (!l) continue;
		l -> ChangePosition (Point ((BMPSIZEX+1)*PosX(iCnt) +1, 
					    (BMPSIZEY+1)*PosY(iCnt) +1));
	}

return _iToolID;
}


// Ein bestimmtes Werkzeug wieder rausnehemen --------------------------------
Bool ToolBox :: RemoveTool (short iTool)
{
// gefordertes Werkzeug löschen
CTable t(*this);
Bool iResult = FALSE;

	if (t.Find (&iTool)) 
		iResult = t.Delete();

// die Position aller Bitmaps neu berechnen
short iCnt = 1;

	for (t.First(); t.Valid(); t.Next(), iCnt++) {
	ToolBitmapLock l (t);

		if (!l) continue;
		l -> ChangePosition (Point ((BMPSIZEX+1)*PosX(iCnt) +1, 
					    (BMPSIZEY+1)*PosY(iCnt) +1));
	}

// wenn das gelöschte Werkzeug das aktive war, dann NUMARROW aktivieren
	if (_iActTool == iTool) SetTool (NUMARROW);

return iResult;
}


// ZugriffsFunktion für BaumZugriff ------------------------------------------
void *GetToolIDPtr (void *pObj)
{
	return & ((ToolBitmap *)pObj) -> iToolID();
}


void EXPORTTRIAS ToolBox :: UserDelete (void *pObj)
{
	((ToolBitmap *)pObj) -> /*ToolBitmap ::*/ ~ToolBitmap();
}

	        
// ---------------------------------------------------------------------------
// Elemente der ToolBox ------------------------------------------------------
ToolBitmap :: ToolBitmap (Point Pt, Dimension Dim, pBitmap pBmp, short iTool)
	    : BitmapObject (Pt, Dim, pBmp)
{
	_isActive = FALSE;
	_iToolID = iTool;
}


ToolBitmap :: ~ToolBitmap (void)
{
	DELETE (bitmap);	// Bitmap wieder freigeben
}



// Iterator für die Werkzeuge ------------------------------------------------
ToolIterator :: ToolIterator (CTree &T)
	      : CTable (T)
{
	First();
}


short ToolIterator :: FirstTool (void)
{
	First();
	if (Valid()) {
	ToolBitmapLock l(*this);

		if (l) return l -> iToolID();
	}
	
return -1;
}


short ToolIterator :: NextTool (void)
{
	Next();
	if (Valid()) {
	ToolBitmapLock l(*this);

		if (l) return l -> iToolID();
	}
	
return -1;
}

