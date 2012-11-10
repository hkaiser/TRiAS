// importsh.cpp : implementation file
//

#include "pheader.h"
#include "odbcext.hr"				// Resource-Konstanten

#include <hpp/helptext.hpp>				// CHelpText
#include <hpp/getodbci.hpp>				// COdbcInfos   
#include <tabdlgs.hpp>				// CTabbedDialogs

#include "importpa.hpp"				// CImportParams
#include "abglpge.hpp"          	// CAbgleichPage          
#include "UserDlg.h"				// CUserDlg
#include "FileDlg.h"				// CFileDsnPage
#include "dsnpage.hpp"				// CDsnPage   
#include "filtrpge.hpp"				// CFilterPage
#include "rsltpge.hpp"				// CResultPage

#ifndef WIN32
#include <progress.hpp>				// CProgressCtrl
#endif                                               

#include "Abgleich.hpp"				// CDoAgleich
#include "ImpRslt2.hpp"				// Aktionsergebnis-Anzeige

#ifdef WIN32                                     
#include "triaspge.hpp"          	// CTriasPage
#include "feldpage.hpp"				// CFeldPage
#else
#include "trs16pge.hpp"				// CTriasPage
#include "fld16pge.hpp"				// CFeldPage
#endif

#include "importsh.hpp"         	// zugeh. Header

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// globale Variablen
CImportParams *g_pCParams = NULL;

#ifdef WIN32
BEGIN_MESSAGE_MAP(CImportSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CImportSheet)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()                           
#else		// WIN16
BEGIN_MESSAGE_MAP(CImportSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CImportSheet)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDB_IMP_NEXT, OnNext)
	ON_BN_CLICKED(IDB_IMP_BACK, OnBack)			
	ON_MESSAGE (IDM_NEXT_PAGE, OnNextPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()                           

void CImportSheet::DoDataExchange(CDataExchange* pDX)
{
	CImportSheet::DoDataExchange(pDX);
	DDX_Control(pDX, IDB_IMP_NEXT, m_btNext);
	DDX_Control(pDX, IDB_IMP_BACK, m_btBack);
}            
#endif 		// WIN16

/////////////////////////////////////////////////////////////////////////////
// CImportSheet

IMPLEMENT_DYNAMIC(CImportSheet, CPropertySheet)

CImportSheet::CImportSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
			 :CPropertySheetExt(nIDCaption, pParentWnd, iSelectPage)
{                                                  
//	interne Werte init.
	m_bResult = FALSE;
	g_pCParams = &m_Params;		// diesen Zeiger setzen
	       
	AddPage (&m_pgAbgleich);    // eine Page muß wenigstens geladen werden
	
//	einzelnen Seiten laden
#ifdef WIN32		
	AddPage (&m_pgTrias);
	AddPage (&m_pgDsn);
	AddPage (&m_pgFeld);
	AddPage (&m_pgFilter);
	AddPage (&m_pgResult);
	AddPage (&m_pgDoAgleich);
	AddPage	(&m_pgResult2);	
#endif	

	m_bResult = TRUE;
}

CImportSheet::~CImportSheet(void)
{
	g_pCParams = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// CImportSheet message handlers
int CImportSheet::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	m_bResult = FALSE;

	if (CPropertySheet::OnCreate(lpCreateStruct) == -1)
		return -1;

	TRY
	{
	// 	TODO: Add your specialized creation code here: Wizzard-Buttons simulieren 
#ifndef WIN32	       
		CRect ClientRect, WindowRect, PageWindowRect;
		GetClientRect (&ClientRect);
		GetWindowRect (&WindowRect);
		m_pgAbgleich.GetWindowRect (&PageWindowRect);
		
		int iX, iY; 			// neuen Koordinaten
		iX = iY = 0;
    	CString strText;                
    	
	//	Cancel-Button
		HWND hWnd = :: GetDlgItem (m_hWnd, IDCANCEL);					
		if (!hWnd)
			AfxThrowUserException ();

	//	Text ändern --> "&Abbrechen"
		if (!strText.LoadString (IDS_ABBRECHEN))
			AfxThrowResourceException ();
		:: SetWindowText (hWnd, strText);				
		
	//	Handel speichern
		m_hWndEsc = hWnd;		
		
	//	Button ans Ende schieben
		iX = PageWindowRect.right - WindowRect.left - m_sizeButton.cx - (WindowRect.Width () -
																	  	 ClientRect.Width ());
		CRect ButtonWindowRect;
		:: GetWindowRect (hWnd, ButtonWindowRect);
		int iPageCly = PageWindowRect.bottom - WindowRect.top - (WindowRect.Height () -
															     ClientRect.Height ());	// ClientPageY
															     
		int iYoffset = (ClientRect.Height() - iPageCly - m_sizeButton.cy) / 2;
		iY = iPageCly + iYoffset;
		:: MoveWindow (hWnd, iX, iY, m_sizeButton.cx, m_sizeButton.cy, TRUE); 				    	

	// 	OK-Button wird unsichtbar
		hWnd = :: GetDlgItem (m_hWnd, IDOK);	
		if (!hWnd)
			AfxThrowUserException ();
		:: ShowWindow (hWnd, SW_HIDE);			

	//	Weiter-Button neu erzeugen		            		
	//	Text lesen
		if (!strText.LoadString (IDS_WEITER))
			AfxThrowResourceException ();

	//	neue Position berechnen
		iX = iX - m_sizeButton.cx - 10;
		
		DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_DISABLED | WS_TABSTOP;
		CRect ButtonRect (iX, iY, m_sizeButton.cx, m_sizeButton.cy);
		if (!m_btNext.Create (strText, dwStyle | BS_DEFPUSHBUTTON, ButtonRect, this, IDB_IMP_NEXT))
			AfxThrowUserException ();							  	
		m_btNext.MoveWindow	(iX, iY, m_sizeButton.cx, m_sizeButton.cy);		
		
	//	Zeichensatz ändern		
		CFont *pFont = GetFont ();
		if (!pFont)
			AfxThrowUserException ();
		m_btNext.SetFont (pFont);			
			
	// 	Help-Button wird unsichtbar
		hWnd = :: GetDlgItem (m_hWnd, ID_HELP);	
		if (!hWnd)
			AfxThrowUserException ();
		:: ShowWindow (hWnd, SW_HIDE);			
		
	//	Apply-Button wird unsichtbar
		hWnd = :: GetDlgItem (m_hWnd, ID_APPLY_NOW);		
		if (!hWnd)
			AfxThrowUserException ();           
		:: ShowWindow (hWnd, SW_HIDE);			
	
	//	Back-Button neu erzeugen						
	//	Text ändern		
		if (!strText.LoadString (IDS_ZURUECK))
			AfxThrowResourceException ();
			
	//	neue Position berechnen
		iX -= m_sizeButton.cx;
		if (!m_btBack.Create (strText, dwStyle | BS_PUSHBUTTON, ButtonRect, this, IDB_IMP_BACK))
			AfxThrowUserException ();							  			
		m_btBack.MoveWindow (iX, iY, m_sizeButton.cx, m_sizeButton.cy);			
		m_btBack.SetFont (pFont);			
#endif		// WIN16
	}
	CATCH (CMemoryException, me)
	{
		DEX_Error (RC_OdbcImport, EC_NOMEMORY);
		return -1;
	}
	AND_CATCH (CResourceException, re);
	{
		DEX_Error (RC_OdbcImport, EC_NORESOURCE);
		return -1;
	}
	AND_CATCH (CUserException, ue);
	{
		DEX_Error (RC_OdbcImport, EC_SYSERROR);
		return -1;
	}
	END_CATCH

	m_bResult = TRUE;

	return 0;
}

#ifndef WIN32
//	Page aktualisieren	
void CImportSheet :: ActPage (int iAct)
{									                            
//	neue Page laden
	CPropertyPage *pOldPage = GetActivePage ();
	switch (iAct)
	{
		case 0:
			AddPage (&m_pgAbgleich);			
		break;
		case 1:         
			AddPage (&m_pgTrias);			
		break;          
		case 2:
			AddPage (&m_pgDsn);
		break;
		case 3:
			AddPage (&m_pgFeld);
		break;			
		case 4:
			AddPage (&m_pgFilter);
		break;			
		case 5:
			AddPage (&m_pgResult);
		break;			
		case 6:
			AddPage (&m_pgDoAgleich);
		break;			
		case 7:			
			AddPage	(&m_pgResult2);	
		break;		
		case 8:                                           
		{
			// DEX_PostRebuildSight();		// Sicht neu lesen
			EndDialog (IDOK);
			return;
		}			
		break;
		default:                                                
			return;							// gar nichts machen
		break;			
	}		
	RemovePage (pOldPage);					// alte Page entladen
}

void CImportSheet :: OnNext (void)		                                  
{   
	ActPage (++m_iActPage);
}		
		                            
void CImportSheet :: OnBack (void)		                                  
{
	ActPage (--m_iActPage);
}

LONG CImportSheet::OnNextPage (UINT, LONG)
{
	ActPage (++m_iActPage);
	return TRUE;	
}
#endif          


