// v_longvr.cpp : implementation file
//

#include "pheader.h"            // vorübersetzte Header
#include "odbcext.hr"			// Resourcen-Defines

#include <hpp/waitcur.hpp>          // CWaitCursor 
#include "v_longvr.hpp"         // zugeh. Header

BEGIN_MESSAGE_MAP(CViewLongVar, CDialog)
	//{{AFX_MSG_MAP(CViewLongVar)
	ON_WM_SIZE()
	ON_WM_ACTIVATE()
	ON_EN_MAXTEXT(IDE_LONGVAR, OnMaxtextLongvar)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//	Konstanten
const uint MaxCharCount = 65000;                                           

/////////////////////////////////////////////////////////////////////////////
// CViewLongVar dialog

CViewLongVar :: CViewLongVar (CWnd* pParent, CLongBinary* pValue, CString& Caption)
			  : CDialog (CViewLongVar :: IDD, pParent)
			  
{   
	m_sRC = EC_SYSERROR;            // erstmal alles rücksetzen
				
	//{{AFX_DATA_INIT(CViewLongVar)
	m_strCaption = Caption;
	//}}AFX_DATA_INIT
	m_pCLongBinary = pValue;
	
	m_sRC = EC_OKAY;         
}

CViewLongVar :: ~CViewLongVar (void)               
{               
	// nothing to do
}

void CViewLongVar::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CViewLongVar)
	DDX_Control(pDX, IDE_LONGVAR, m_Line);
	//}}AFX_DATA_MAP
}

void CViewLongVar :: Show (void)
{            
//  prüfe internen Zustand
	if (m_sRC != EC_OKAY)          
		return;                 

	DoModal ();
}                 

/////////////////////////////////////////////////////////////////////////////
// CViewLongVar message handlers
void CViewLongVar::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	// TODO: Add your message handler code here
	      
	if (m_Line.m_hWnd && m_Line.IsWindowVisible ())      
		m_Line.MoveWindow (0, 0, cx, cy);   
}

BOOL CViewLongVar::OnInitDialog()
{
	CDialog::OnInitDialog();

//  Speicher für Text anfordern
	uint MaxCnt = (uint) m_pCLongBinary -> m_dwDataLength;
	if (MaxCnt >= MaxCharCount)
	{
		MaxCnt = MaxCharCount;
		DEX_Error (RC_ctViewLongChar, WC_TEXTTRUNCATED);
	}                               
	     
	char *pDest = NULL;          
	TRY
	{                   
		pDest = new char [MaxCnt + 1];
	}
	CATCH (CMemoryException, cme)
	{                                            
		DEX_Error (RC_ctViewLongChar, EC_NOMEMORY);     
		return FALSE;
	}               
	END_CATCH                                 
				 
	char *pSrc = (char *) GlobalLock (m_pCLongBinary -> m_hData);
	if (! pSrc)
	{
		DEX_Error (RC_ctViewLongChar, EC_LOCKERROR);
		return FALSE;
	}        
	
//  Text umkopieren: Umlaute konvertieren nicht notwendig
	CWaitCursor wc;                                 // Hourglas einschalten         
	for (register uint nIndex = 0; nIndex < MaxCnt; nIndex++)
		pDest [nIndex] = pSrc [nIndex];
	pDest [nIndex] = '\0';                                                          

//  Text ausgeben                                                                                           
	m_Line.SetWindowText (pDest);           
	
	GlobalUnlock (m_pCLongBinary -> m_hData);
	DELETE_VEC (pDest);                                 // Text löschen
	
	SetWindowText (m_strCaption);   				// Caption ausgeben                                       
	
/*
//	Endkennung setzen
	char *pSrc = (char *) GlobalLock (m_pCLongBinary -> m_hData);
	if (! pSrc)
	{
		DEX_Error (RC_ctViewLongChar, EC_LOCKERROR);
		return FALSE;
	}        
//	pSrc [m_pCLongBinary -> m_dwDataLength - 1] = '\0';		
									
	m_Line.SetWindowText (pSrc);           			//  Text ausgeben                                                                                           
	GlobalUnlock (m_pCLongBinary -> m_hData);
	SetWindowText (m_strCaption);   				// Caption ausgeben                                       
*/	

	return TRUE;  
}

void CViewLongVar::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialog::OnActivate(nState, pWndOther, bMinimized);
	
    m_Line.SetSel (0, 0);								// Text deselektieren
}

void CViewLongVar::OnMaxtextLongvar()
{
	DEX_Error (RC_ctViewLongChar, WC_TEXTTRUNCATED); 	// Text wurde abgeschnitten
}
