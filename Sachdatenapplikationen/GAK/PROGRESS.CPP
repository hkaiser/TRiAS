// progress.cpp : implementation file
//

#include "stdafx.h"		//	prec. Header
#include "gak.h"		//	CGakApp    
//#include "resource.h"	//	Resourcekonstanten

#include "progress.h"	//	zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif 

// Konstanten
//static const UINT iOffsX = 0/*3*/;
//static const UINT iOffsY = 0/*2*/;
//static const int iShowCol = 255;
// static const int iDelCol = 200;
  
#ifndef WIN32           
//	CProgressCtrl -------------------------------------------------------------             
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
	//rc.left += iOffsX;
	//rc.top += iOffsY;
	//rc.right -= iOffsX;
	//rc.bottom -= iOffsY;             
	m_dFaktor = (double)(rc.right - rc.left) / (double)(iEnd - iStart);
	m_iDrawPos = 0;			// ZeichenPosition
			
	m_iStart = iStart;
	m_iEnd = iEnd;
	
	DrawPosition (0);		// Balken löschen
}

void CProgressCtrl :: SetPos (UINT iNewPos)    
{
//	prüfe Parameter
	if (iNewPos < m_iStart || iNewPos > m_iEnd || m_iStart == m_iEnd)
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
			/*
				if (iPos == 0)
					hBrush = CreateSolidBrush(RGB(iDelCol, iDelCol, iDelCol));	
				else
					hBrush = CreateSolidBrush(RGB(0, 0, iShowCol));					
			*/					
				if (0 != iPos)
				{
					hBrush = CreateSolidBrush(RGB(0, 0, iShowCol));									
					if (hBrush)
						FillRgn(pCDC -> m_hDC, hrgn, hBrush);		// Fläche füllen
				}						
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
#endif

/////////////////////////////////////////////////////////////////////////////
// CProgress dialog
CProgress::CProgress(CWnd* pParent)
		  : CDialog(/*CProgress::IDD, pParent*/)
{
	//{{AFX_DATA_INIT(CProgress)
	//}}AFX_DATA_INIT
	Create (IDD_RECHERCHESTATUS, pParent);
	
	m_bWasInterrupted = FALSE;
}

CProgress::~CProgress()
{
	if (m_hWnd && IsWindowVisible ())
		DestroyWindow ();
}

void CProgress::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProgress)
	DDX_Control(pDX, IDT_ACTIONTEXT, m_stAction);
	DDX_Control(pDX, IDT_PROGRESS, m_ctlProgress);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CProgress, CDialog)
	//{{AFX_MSG_MAP(CProgress)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CProgress message handlers

BOOL CProgress::OnInitDialog()
{
	CDialog::OnInitDialog();
	               
	CenterWindow ();	               
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CProgress::OnCancel()
{
	// TODO: Add extra cleanup here
	m_bWasInterrupted = TRUE;
	
	CDialog::OnCancel();
}
          
BOOL CProgress::Break (void)          
{
	CallMessageQueue ();
	return m_bWasInterrupted;
}   

void CProgress::SetParams (UINT uiStart, UINT uiEnd, const char *pCaption)
{ 
	ASSERT (NULL != pCaption && AfxIsValidString (pCaption));
	SetWindowText (pCaption);
	m_ctlProgress.SetRange (uiStart, uiEnd);
}

void CProgress::SetPos (UINT uiNewPos)
{
	m_ctlProgress.SetPos (uiNewPos);		          
}                                   

void CProgress::SetActionText (const char *pText)
{
	ASSERT (NULL != pText && AfxIsValidString (pText));
	m_stAction.SetWindowText (pText);
}
