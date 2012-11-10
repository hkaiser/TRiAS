// ImprtDlg.cpp : implementation file
//

#include "stdafx.h"		// prec. Header
#include "gak.h"		// CGakApp u. Ressourcen
#include "importty.h"	// CImportParams
#include "InTablPg.h"	// CInputTablePage
#include "OutTbPg.h"	// COutputTablePage
#include "ImpParPg.h"	// CImportParamPage
#include "ImpSumPg.h"	// CImportSumPage
#include "DoImpPge.h"	// CDoImportPage
#include "ImpResPg.h"	// CImportResultPage		
#include "ImprtDlg.h"	// zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImportDlg

IMPLEMENT_DYNAMIC(CImportDlg, CPropertySheet)

CImportDlg::CImportDlg(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	m_pgInputTable.SetParams (m_ImportParams);	// Parameter speichern
	AddPage (&m_pgInputTable);
	m_pgOutputTable.SetParams (m_ImportParams);
	AddPage (&m_pgOutputTable);
	m_pgImportParam.SetParams (m_ImportParams);
	AddPage (&m_pgImportParam);
	m_pgImportSum.SetParams (m_ImportParams);
	AddPage (&m_pgImportSum);
	m_pgDoImport.SetParams (m_ImportParams);
	AddPage (&m_pgDoImport);
	m_pgImportResult.SetParams (m_ImportParams); 
	AddPage (&m_pgImportResult);
}

CImportDlg::~CImportDlg()
{
}

BEGIN_MESSAGE_MAP(CImportDlg, CPropertySheet)
	//{{AFX_MSG_MAP(CImportDlg)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImportDlg message handlers
