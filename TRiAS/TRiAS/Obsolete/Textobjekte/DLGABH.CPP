// dlgabh.cpp : implementation file
//

#include "stdafx.h"

#include "resource.h"
#include "helper.h"
#include "dlgabh.h"
#include "iterator.hpp"
#include "waitcur.hpp"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
            
/////////////////////////////////////////////////////////////////////////////
// CDlgAbh dialog

// Dlg.fenster zum Abhängen von Textobj.
//--------------------------------------------------------------------

CDlgAbh::CDlgAbh(CWnd* pParent /*=NULL*/, CHelper *pHelper)
	: CDialog(CDlgAbh::IDD, pParent)
{                    
	m_pHelper = pHelper;
    m_bLoesch = FALSE;
	//{{AFX_DATA_INIT(CDlgAbh)
	//}}AFX_DATA_INIT
}

void CDlgAbh::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAbh)
	DDX_Control(pDX, IDOK, m_OK);
	DDX_Control(pDX, IDC_LIST1, m_lbIdList);
	DDX_Control(pDX, IDC_CLOESCH, m_cLoesch);	
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgAbh, CDialog)
	//{{AFX_MSG_MAP(CDlgAbh)
	ON_LBN_SELCHANGE(IDC_LIST1, OnSelect)
	ON_BN_CLICKED(IDC_CLOESCH, OnLoesch)
	ON_BN_CLICKED(IDC_ALLID, OnAllId)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlgAbh message handlers

BOOL CDlgAbh::OnInitDialog()
{
	CDialog::OnInitDialog(); 

	CenterWindow();			// Fenster zentrieren
		
ENUMTEXTKEYEX ETKEX;
	
	ETKEX.eKey = NULL;		// Suchschlüssel
	ETKEX.eFcn = (ENUMTEXTKEYEXPROC) EnumIdentProcEx;	// zu rufende Funktion
	ETKEX.ePtr = (void *) &m_lbIdList;
	ETKEX.eData = OTPunkt | OTLinie | OTFlaeche;		// zusätzliche Parameter
	    
	if (!DEX_EnumSightIdentsEx(ETKEX)) return FALSE;	// alle Identifikatoren einer Sicht

	m_OK.EnableWindow(FALSE);
	m_cLoesch.SetCheck(0);

return TRUE;  // return TRUE  unless you set the focus to a control
}


void CDlgAbh::OnSelect()
{
	m_OK.EnableWindow(TRUE);
}

void CDlgAbh::OnOK()
{
	CDialog::OnOK();
	CWaitCursor WC;
	char cGeo ;
	CLBIterator ILB (m_lbIdList);
	HWND hWnd = 0;				                                               
		while (ILB.GetNextItem(m_lIdent, &cGeo))
		        	// Übergabe der nach "IDOK" selektierten Werte an
		        	// Enumerationsfunktionen , Obj. enum. ,Relationen enum.,
		        	// Relationen löschen
			m_pHelper -> AbhaengTextObj (hWnd, m_lIdent, m_bLoesch, &cGeo);        	  
}

void CDlgAbh::OnLoesch()
{
	if (m_cLoesch.GetCheck() == 1)
		m_bLoesch = TRUE;
	
}

void CDlgAbh::OnAllId()
{
	m_lbIdList.SetSel( -1, TRUE );
	m_OK.EnableWindow(TRUE);
}
