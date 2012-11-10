// Rahmen, in dem eine Bitmap gezeichnet werden soll --------------------------
// File: BMPBOX.CXX

#include "visobjp.hxx"

#include <drawobj.hxx>

#include "bmpbox.hxx"


BitmapBox :: BitmapBox (pDialogWindow pDW, ResID uiID, ResID uiLogo)
	   : ControlWindow (new FixedText (pDW, uiID)),
	     m_uiLogo (uiLogo)
{
	// nothing else to do
}


BitmapBox :: ~BitmapBox (void)
{
	if (GetControl()) 
		delete (FixedText *)GetControl();
	if (m_pBM) delete m_pBM;
}

// Table used to map default system colors onto the system color identifiers.
static COLORMAP sysColorMap[] = {
//	      b     g     r
	{ RGB(0x00, 0x00, 0x00), GetSysColor(COLOR_BTNTEXT) },
	{ RGB(0x80, 0x80, 0x80), GetSysColor(COLOR_BTNSHADOW) },
	{ RGB(0xc0, 0xc0, 0xc0), GetSysColor(COLOR_BTNFACE) },
	{ RGB(0xff, 0xff, 0xff), GetSysColor(COLOR_BTNHIGHLIGHT) }
};

BOOL BitmapBox :: Init (void)
{
	if (GetControl() == NULL) 
		return false;
		
	m_pBM = new Bitmap (m_uiLogo, sysColorMap, _countof(sysColorMap), 0);
	if (m_pBM == NULL) 
		return false;
	
	RePaint();	// neu zeichnen
	
return true;
}


void _XTENSN_EXPORT BitmapBox :: Expose (ExposeEvt e)
{
// Bitmap zeichnen
Rectangle Rc = CanvasRect();
Dimension dimSize = m_pBM -> GetSize();
Point ptPos ((Rc.Right()-Rc.Left()-dimSize.Width())/2, 
	     (Rc.Top()-Rc.Bottom()-dimSize.Height())/2);
BitmapObject BMO (ptPos, dimSize, m_pBM);

	Draw (&BMO);

// Rahmen auch zeichnen lassen
	ControlWindow :: Expose (e);
}

	
