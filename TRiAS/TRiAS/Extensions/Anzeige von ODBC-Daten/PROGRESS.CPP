/*
	DATEI: PGROGRESS.CPP
	
	Nachbildung einer Fortschrittsanzeige für Windows 3.11.
	
	Erabeitet: J.Benkenstein			Stand vom 7.2.1995
*/

#include "stdafx.h" 		//	prec. Header
#include "bgsabgl.h"        //	Ressource-Konstanten

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// Konstanten
const UINT iOffsX = 3;
const UINT iOffsY = 2;
const int iShowCol = 255;
const int iDelCol = 200;

CProgressCtrl :: CProgressCtrl (void) 
{ 
	m_iDrawPos = m_iStart = m_iEnd = m_iPos = 0; 
	m_dFaktor = 1.0;
}

void CProgressCtrl :: SetRange (UINT iStart, UINT iEnd)
{   
//	alten Parameter löschen
	m_iDrawPos = m_iStart = m_iEnd = m_iPos = 0;
	m_dFaktor = 1.0;
	
//	prüfe Parameter    
	if (iStart == iEnd || iStart > iEnd)
		return;
		
//	Rechteck nachbearbeiten		
	GetClientRect (&rc);
	rc.left += iOffsX;
	rc.top += iOffsY;
	rc.right -= iOffsX;
	rc.bottom -= iOffsY;             
	m_dFaktor = (double)(rc.right - rc.left) / (double)(iEnd - iStart);
	m_iDrawPos = 0;			// ZeichenPosition
			
	m_iStart = iStart;
	m_iEnd = iEnd;
	
	DrawPosition (0);		// Balken löschen
}

void CProgressCtrl :: SetPos (UINT iNewPos)    
{
//	prüfe Parameter
	if (iNewPos <= m_iStart || iNewPos >= m_iEnd || m_iStart == m_iEnd)
		return;

	DrawPosition (iNewPos);		
}		
	
void CProgressCtrl :: DrawPosition (UINT iPos)
{	
	HRGN hrgn = NULL;
	CDC *pCDC = NULL;
	HBRUSH hBrush = NULL;

	if (iPos == 0)		// Reset !
	{
		hrgn = CreateRectRgn(rc.left, rc.top, rc.right, rc.bottom);
		m_iDrawPos == 0;
	}		
	else                                        
	{
		UINT iX = UINT (iPos * m_dFaktor);
		if (iX == m_iDrawPos)		// keine Postionsänderung
			return;
		if (iX > m_iDrawPos && iX <= (UINT) rc.Width ())					
			m_iDrawPos = iX;
		else
		{
			if (iX > (UINT) rc.Width())
				m_iDrawPos = rc.right;		
			else
				return;			
		}	
		hrgn = CreateRectRgn(rc.left, rc.top, m_iDrawPos, rc.bottom);					
	}		
	
	if (hrgn)
	{
		pCDC = GetDC (); 	
		if (pCDC)
		{
			int iRgn = (int) SelectObject (pCDC -> m_hDC, hrgn);
			if (NULLREGION != iRgn && ERROR != iRgn)
			{
				if (iPos == 0)
					hBrush = CreateSolidBrush(RGB(iDelCol, iDelCol, iDelCol));	
				else
					hBrush = CreateSolidBrush(RGB(0, 0, iShowCol));					
				if (hBrush)
					FillRgn(pCDC -> m_hDC, hrgn, hBrush);		// Fläche füllen
			}
		}
	}
		
//	alles wieder freigeben		
	if (hrgn)		
		DeleteObject(hrgn);
	if (hBrush)
		DeleteObject (hBrush);
	if (pCDC)		
		ReleaseDC (pCDC);
		
//	Fenster nachzeichnen	
	UpdateWindow ();
}	
           
           