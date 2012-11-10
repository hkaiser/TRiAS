// Rahmen, in dem eine Bitmap gezeichnet werden soll --------------------------
// File: CBMPBOX.CXX

#include "tortenp.hxx"

#include <drawobj.hxx>

#include <cbmpbox.hxx>
#include <icustom.hxx>

#include "impcustm.hxx"


CBitmapBox :: CBitmapBox (pDialogWindow pDW, ResID uiID, ResID uiLogo)
	    : ControlWindow (new FixedText (pDW, uiID)),
	      m_uiLogo (uiLogo)
{
	// nothing else to do
}


CBitmapBox :: ~CBitmapBox (void)
{
	if (GetControl()) 
		delete (FixedText *)GetControl();
	if (m_pBM) delete m_pBM;
}


BOOL CBitmapBox :: FInit (ResID uiLogo)
{
	if (GetControl() == NULL) 
		return FALSE;
		
	m_uiLogo = uiLogo;
	DELETE_OBJ (m_pBM);
	m_pBM = new Bitmap (m_uiLogo);
	if (m_pBM == NULL) 
		return FALSE;
	
	RePaint();	// neu zeichnen
	
return TRUE;
}

BOOL CBitmapBox :: FInit (void)
{
	if (GetControl() == NULL) 
		return FALSE;
		
	m_pBM = new Bitmap (m_uiLogo);
	if (m_pBM == NULL) 
		return FALSE;
	
	RePaint();	// neu zeichnen
	
return TRUE;
}


void _VMD_EXPORT CBitmapBox :: Expose (ExposeEvt e)
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

	
	
