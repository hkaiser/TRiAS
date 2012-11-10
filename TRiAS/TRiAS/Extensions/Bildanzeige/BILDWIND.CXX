// Memberfunktionen zur BildFensterklasse
// File: BILDWIND.CXX

#include "bilderp.hxx"


// Konstruktor ----------------------------------------------------------------
BildWindow :: BildWindow (pWindow pParent, char *pCaption,
			  Point Org, char *pImgName)
#if defined(WIN32)
	    : ExtChildAppWindow (pParent, IsWin40() ? WS_EX_CLIENTEDGE|
						WS_EX_WINDOWEDGE|WS_EX_TOOLWINDOW : 0),
#else
	    : ExtChildAppWindow (pParent),
#endif
	      localBrush (HollowBrush)
{
// BildObjekt generieren
	_pBO = new BildObjekt (this, pImgName, Org);
	if (_pBO == NULL || !_pBO -> OK()) return;

// ScrollBalken initialisieren
	pVertSB = EnableVScroll (FALSE);
	pHorzSB = EnableHScroll (FALSE);

// FensterTyp setzen
	EnableSysMenu ();
	EnableBorder ();
	ChangeBackground (&localBrush);

// Fenster Überschrift setzen
	if (pCaption != NULL) 
		SetCaption (pCaption);
	else {
	ResString resCaption (ResID(IDS_BILDINFO, &g_pTE -> RF()), 64);

		SetCaption (resCaption);
	}

// Fenstergröße und Lage berechnen
Rectangle Rc (Point (0, 0), _pBO -> GetSize());

#if defined(WIN32)
	AdjustWindowRectEx ((RECT *)&Rc, WS_CHILD|WS_CAPTION|WS_THICKFRAME, 
		false, IsWin40() ? WS_EX_CLIENTEDGE|WS_EX_WINDOWEDGE|WS_EX_TOOLWINDOW : 0);
#else
	AdjustWindowRect ((RECT *)&Rc, WS_CHILD|WS_CAPTION|WS_THICKFRAME, false);
#endif
	Rc.Top() -= 2*GetSystemMetrics (SM_CYFRAME);

// Neue Größe einstellen
	_maxSize = Dimension (Rc.Right()-Rc.Left(), -Rc.Bottom()-Rc.Top());
	ChangeSize (_maxSize);

// BildFenster positionieren
Point Pt (GetSystemMetrics (SM_CXFRAME), GetSystemMetrics (SM_CYFRAME));

	ChangePosition (Pt);
}

// Destruktor
BildWindow :: ~BildWindow (void)
{
	Hide();
	DELETE_OBJ (_pBO); 
}


// Eventhandler ---------------------------------------------------------------
void _XTENSN_EXPORT BildWindow :: ReSize (ReSizeEvt) 
{
// ScrollBereich neu setzen
	SetScrollRanges ();
}

void _XTENSN_EXPORT BildWindow :: Expose (ExposeEvt) 
{
	Draw (_pBO);		// Bitmap zeichnen
}

void _XTENSN_EXPORT BildWindow :: HorizScroll (ScrollEvt e) 
{
Range HorzR;
int iPos, dn;
Rectangle Rc;

// neue vertikale Rollposition berechnen
	HorzR = pHorzSB -> GetRange();
	iPos = e.GetOldPos();
	Rc = CanvasRect();
	switch (e.GetScrollType()) {
	case UnitDecrement:	dn = -Rc.Right() / 16 + 1; break;
	case UnitIncrement:	dn =  Rc.Right() / 16 + 1; break;
	case BlockDecrement:	dn = -Rc.Right() / 2 + 1; break;
	case BlockIncrement:	dn =  Rc.Right() / 2 + 1; break;
	case ThumbDrag:		dn =  e.GetPos() - iPos; break;
	default:		dn =  0; break;
	}

// Rollen auf aktuellen Rollbereich begrenzen
	if (dn = BOUND (iPos + dn, HorzR.Min(), HorzR.Max()) - iPos) {
		Scroll (Dimension (-dn, 0), Rc);
		pHorzSB -> SetThumbPos (iPos + dn);
		(_pBO -> Org()).X() = iPos + dn;
		InvalidateRect(Handle(), NULL, TRUE);
	}
}


void _XTENSN_EXPORT BildWindow :: VertScroll (ScrollEvt e) 
{
Range VertR;
int iPos, dn;
Rectangle Rc;

// neue vertikale Rollposition berechnen
	VertR = pVertSB -> GetRange();
	iPos = e.GetOldPos();
	Rc = CanvasRect();
	switch (e.GetScrollType()) {
	case UnitDecrement:	dn = -Rc.Top() / 16 + 1; break;
	case UnitIncrement:	dn =  Rc.Top() / 16 + 1; break;
	case BlockDecrement:	dn = -Rc.Top() / 2 + 1; break;
	case BlockIncrement:	dn =  Rc.Top() / 2 + 1; break;
	case ThumbDrag:		dn =  e.GetPos() - iPos; break;
	default:		dn =  0; break;
	}

// Rollen auf aktuellen Rollbereich begrenzen
	if (dn = BOUND (iPos + dn, VertR.Min(), VertR.Max()) - iPos) {
		Scroll (Dimension (0, dn), Rc);
		pVertSB -> SetThumbPos (iPos + dn);
		(_pBO -> Org()).Y() = iPos + dn;
		InvalidateRect(Handle(), NULL, TRUE);
	}
}

// ScrollBereiche neu setzen
void BildWindow :: SetScrollRanges (void) 
{
Rectangle Rc;
Dimension Size;
static int iScrollSem = 0;
register int iRangeH, iRangeV, i;

	Size = _pBO -> GetSize();
	if (!iScrollSem) {
		iScrollSem++;
		Rc = RealCanvasRect();
		for (i = 0; i < 2; i++) {
			iRangeV = Size.Height() - (Rc.Top()-Rc.Bottom());
			iRangeH = Size.Width() - Rc.Right();
			if (iRangeH < 0) iRangeH = 0;
			if (iRangeV < 0) iRangeV = 0;

		// etwas neuzeichnen ?
		int yThumbPos = pVertSB != NULL ? pVertSB -> GetThumbPos() : 0;
		int xThumbPos = pHorzSB != NULL ? pHorzSB -> GetThumbPos() : 0;

			if (yThumbPos > iRangeV || xThumbPos > iRangeH)
				RePaint();

		// ScrollBalken anzeigen bzw. l”schen
			if (iRangeV > 0) {
				pVertSB = EnableVScroll (TRUE);
				pVertSB -> SetRange (Range (0, iRangeV));
			} else {
				if (pVertSB) pVertSB -> SetRange (Range (0, 0));
				pVertSB = EnableVScroll (FALSE);
				(_pBO -> Org()).Y() = 0;
			}
			if (iRangeH > 0) {
				pHorzSB = EnableHScroll (TRUE);
				pHorzSB -> SetRange (Range (0, iRangeH));
			} else {
				if (pHorzSB) pHorzSB -> SetRange (Range (0, 0));
				pHorzSB = EnableHScroll (FALSE);
				(_pBO -> Org()).X() = 0;
			}

		// zweite Runde
			Rc = CanvasRect();
		}
		iScrollSem--;
	}
}

// Fenster soll geschlossen werden
Bool _XTENSN_EXPORT BildWindow :: QueryClose (Event) 
{
	DELETE_OBJ (_pBO);

return TRUE;	// auf jeden Fall raus
}

// Maximale Trackinggröße setzen
void _XTENSN_EXPORT BildWindow :: MinMaxQuery (MinMaxEvent e) 
{
// korrigierte Bitmapgröße als maximale Fenstergröße verwenden
	e.SetMaxTrackingSize (_maxSize);
}


// Berechnung der ClientFlaeche unter Beruecksichtigung der Rollbalken
Rectangle BildWindow :: RealCanvasRect (void) 
{
long dwStyle = GetWindowLong (Handle (API_CLIENT_HWND), GWL_STYLE);
							// FensterStil
Rectangle Rc = CanvasRect();

	if (dwStyle & WS_HSCROLL)
		Rc.Bottom() -= GetSystemMetrics (SM_CYHSCROLL);
	if (dwStyle & WS_VSCROLL)
		Rc.Right() += GetSystemMetrics (SM_CXVSCROLL);

return Rc;
}

