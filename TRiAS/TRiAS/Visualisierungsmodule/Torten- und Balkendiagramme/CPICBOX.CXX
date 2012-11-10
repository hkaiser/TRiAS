// Rahmen, in dem ein Bildchen gezeichnet werden soll --------------------------
// File: CPICBOX.CXX

#include "tortenp.hxx"

#include <protos.h>

#include <drawobj.hxx>
#include <icustom.hxx>

#include "impcustm.hxx"
#include "cpicbox.hxx"

extern "C" bool WINAPI DrawRectangle (HDC hDC, int x1, int y1, int x2, int y2);

CPictureBox :: CPictureBox (pDialogWindow pDW, ResID uiID, CTortenVisModule *pVM)
	     : ControlWindow (new FixedText (pDW, uiID)),
	       m_rVM (*pVM)
{
	m_iType = 0;
	m_iNums = 0;
	m_pSectors = NULL;
	m_ppMWerte = NULL;
	m_pPalName = NULL;
}


CPictureBox :: ~CPictureBox (void)
{
	if (GetControl()) delete (FixedText *)GetControl();
	DELETE_OBJ (m_pPalName);
}


BOOL CPictureBox :: FInit (short iType, char *pPalName, short iSectors, 
			   long *pSectors, char **ppMWerte)
{
	if (GetControl() == NULL) return FALSE;
		
	if (m_pPalName == NULL) {
		m_pPalName = new char [_MAX_PATH];
		if (m_pPalName == NULL) return FALSE;
	}
	
	strcpy (m_pPalName, pPalName);	// PalettenName
	m_iType = iType;
	m_iNums = iSectors;
	m_ppMWerte = ppMWerte;		// nur Pointer kopieren
	m_pSectors = pSectors;		// nur Pointer merken
	
	RePaint();	// neu zeichnen
	
return TRUE;
}


void _VMD_EXPORT CPictureBox :: Expose (ExposeEvt)
{
// Bildchen zeichnen
Rectangle Rc = CanvasRect();
CoOrd iRcX = Rc.Right()-Rc.Left();
CoOrd iRcY = Rc.Top()-Rc.Bottom();
Dimension dimSize (7*iRcX/24, 7*iRcY/24);
Point ptPos (iRcX/2, iRcY/2);
VisInfo VI (m_iType|TORTEN_BIGFONT, 0, BLACK);

	VI.SetVisName (m_pPalName);

PAINTSTRUCT ps;
HDC hDC = :: BeginPaint (Handle(), &ps);
HBRUSH hBr = (HBRUSH)SelectObject (hDC, GetStockObject (WHITE_BRUSH));

	DrawRectangle (hDC, Rc.Left(), Rc.Top(), Rc.Right(), Rc.Bottom());
	SelectObject (hDC, hBr);
	
// wenn noch nicht mit Daten initialisiert, dann gleich wieder raus
	if (m_iNums != 0) {
		SetMapMode (hDC, MM_ISOTROPIC);		// Koordinatenursprung jetzt
		SetWindowExtEx (hDC, iRcX, iRcY, NULL);		// links unten
		SetViewportExtEx (hDC, iRcX, -iRcY, NULL);
		SetViewportOrgEx (hDC, 0, iRcY, NULL);
		
		InflateRect ((RECT *)&Rc, -1, -1);
		LPtoDP (hDC, (POINT *)&Rc, 2);		// Region muﬂ in DeviceKoords sein
		
	HRGN hRgn = CreateRectRgnIndirect ((LPRECT)&Rc);
	
		SelectClipRgn (hDC, hRgn);
		DeleteObject (hRgn);
		
	// WerteFeld umkopieren
	long *plT = new long [m_iNums+1];
	
		if (plT == NULL) return;
		for (short i = 0; i <= m_iNums; i++)
			plT[i] = m_pSectors[i];
	
		m_rVM.DrawGraphic (&VI, hDC, hDC, 
				   *(POINT *)&ptPos, *(SIZE *)&dimSize,
				   m_iNums, plT, m_ppMWerte);
		DELETE_OBJ (plT);
	}			   
	:: EndPaint (Handle(), &ps);
}

	
	
