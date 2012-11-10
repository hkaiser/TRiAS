// Rahmen, in dem eine Bitmap gezeichnet werden soll --------------------------
// File: BMPBOX.CXX

#include "idntsdbp.hxx"

#include <new>
#include <drawobj.hxx>

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

static const COLORMAP colMap[] = 
{
// mapping from color in DIB to system color
	{ RGB(0x00, 0x00, 0x00), COLOR_BTNTEXT },	// black-->ButtonTextColor
	{ RGB(0xFF, 0x00, 0xFF), COLOR_BTNFACE }	// magenta-->DlgFaceColor
};
#define NUMCOLORSINMAP (sizeof(colMap)/sizeof(colMap[0]))

BOOL BitmapBox :: Init (void)
{
	if (GetControl() == NULL) 
		return FALSE;

COLORMAP *pCopyMap = NULL;

	try {
		pCopyMap = new COLORMAP[NUMCOLORSINMAP];
		for (int i = 0; i < NUMCOLORSINMAP; i++) {
			pCopyMap[i].from = colMap[i].from;
			pCopyMap[i].to = GetSysColor (colMap[i].to);
		}
		m_pBM = new Bitmap (m_uiLogo, pCopyMap, NUMCOLORSINMAP);

	} catch (...) {
		if (pCopyMap) delete pCopyMap;
		return FALSE;
	}	

	delete pCopyMap;
	RePaint();	// neu zeichnen
	
return TRUE;
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

	
