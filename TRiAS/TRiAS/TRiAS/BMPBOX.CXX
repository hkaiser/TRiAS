// Rahmen, in dem eine Bitmap gezeichnet werden soll --------------------------
// File: BMPBOX.CXX

#include "triaspre.hxx"

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


BOOL BitmapBox :: Init (void)
{
	if (GetControl() == NULL) 
		return FALSE;
		
	m_pBM = new Bitmap (m_uiLogo);
	if (m_pBM == NULL) 
		return FALSE;
	
	RePaint();	// neu zeichnen
	
return TRUE;
}

#if defined(__WATCOMC__)
#pragma warning 604 9;
#pragma warning 595 9;
#endif

void BitmapBox :: Expose (ExposeEvt e)
{
// Bitmap zeichnen
Rectangle Rc = CanvasRect();
Dimension dimSize = m_pBM -> GetSize();
Point ptPos (short((Rc.Right()-Rc.Left()-dimSize.Width())/2), 
	     short((Rc.Top()-Rc.Bottom()-dimSize.Height())/2));
BitmapObject BMO (ptPos, dimSize, m_pBM);

	Draw (&BMO);

// Rahmen auch zeichnen lassen
	ControlWindow :: Expose (e);
}

	
	
