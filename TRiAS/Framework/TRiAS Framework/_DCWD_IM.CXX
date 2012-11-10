/*
 *
 *	_ d c w d _ i m . c x x
 *
 *	Mods Log:
 *
 */
#include "tfrmpre.hxx"

CDCWind_Imp :: CDCWind_Imp (pWindow req, Rectangle &Rc)
	     : Wind_Imp (req)
{
// AusgabeFläche vorgeben
	WndSize = Dimension (Rc.Right()-Rc.Left(), Rc.Bottom()-Rc.Top());
	WndPosition = Point (Rc.Left(), Rc.Top());
}

CDCWind_Imp :: ~CDCWind_Imp (void)
{
	// nothing to do
}


// Setzt den DC auf dem gezeichnet werden soll --------------------------------
HDC CDCWind_Imp :: SetDrawDC (HDC hNewDC)
{
HDC hDC = CV_RunTime::Window_hDC (this);

	CV_RunTime::Window_hDC (this) = hNewDC;	// DC setzen
	return hDC;
}


///////////////////////////////////////////////////////////////////////////////
// DC initialisieren und liefern
HDC CDCWind_Imp::GetDC (void)		// überladene Funktion
{
HDC hDC = CV_RunTime::Window_hDC (this);

	if (NULL != hDC) {
	// ggf. Font selektieren
		if (DCFlags.FontNeeded && !DCFlags.FontInUse) {
		HFONT font = 0;
			
			if (WndFont) {
				CV_RunTime::Font_Imp(WndFont) -> Init(0, hDC);
				font = CV_RunTime::Font_hFont (WndFont);
			}
			else
				font = (HFONT)GetStockObject(13);

			CV_ASSERT_VALID(font);
			SelectObject (hDC, font);
			DCFlags.FontInUse = 1;
			DCFlags.FontNeeded = 0;
			SetTextAlign(hDC, TA_LEFT | TA_BOTTOM);
		}

	// ggf. Pen selektieren
		if (DCFlags.PenNeeded && !DCFlags.PenInUse)	{
			if	(WndPen) {
				SelectObject (hDC, CV_RunTime::Pen_hPen (WndPen));
			
			LogicalPen p(WndPen);
			
				SetTextColor(hDC, p.GetColor());
			}
			else {
				SelectObject (hDC, GetStockObject (BLACK_PEN));
				SetTextColor (hDC, GetSysColor (COLOR_WINDOWTEXT));
			}

			DCFlags.PenInUse = 1;
			DCFlags.PenNeeded = 0;
		}

	// ggf. Brush selektieren		
		if (DCFlags.BrushNeeded && !DCFlags.BrushInUse)	{
			if	(WndBrush)
				SelectObject (hDC, CV_RunTime::Brush_hBrush (WndBrush));
			else
				SelectObject (hDC, GetStockObject (BLACK_BRUSH));

			DCFlags.BrushInUse = 1;
			DCFlags.BrushNeeded = 0;
		}
	}
	return hDC;
}


// Koppelt den DC, auf dem gezeichnet wurde ab --------------------------------
HDC CDCWind_Imp :: DetachDC (void)
{
HDC hDC = CV_RunTime::Window_hDC (this);

	CV_RunTime::Window_hDC (this) = 0;	// DC abkoppeln
	return hDC;
}


// Wegblenden der ShowFunktion ------------------------------------------------
void CDCWind_Imp :: Show (ShowState)
{
	// intentionally left free
}

Rectangle CDCWind_Imp :: CanvasRect (void)
{	
Rectangle r (WndPosition.Y(), WndPosition.X(), 
	     WndPosition.Y()+WndSize.Height(), 
	     WndPosition.X()+WndSize.Width());

	return r;
}

Rectangle CDCWind_Imp :: WindowRect (void)
{
Rectangle r (WndPosition.Y(), WndPosition.X(), 
	     WndPosition.Y()+WndSize.Height(), 
	     WndPosition.X()+WndSize.Width());

	return r;
}

