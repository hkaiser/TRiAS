// ErzSheet.cpp : implementation file
//

#include "stdafx.h"			// prec. Header
#include "gak.h"			// CGakApp
#include "firmpage.h"		// CFirmaPage
#include "anfpage.h"		// CAnfallStelle
#include "EntsPage.h"		// CEntsPage
#include "branPage.h"		// CBranchPage
#include "PartPage.h"		// CPartnerPage
#include "Erzsheet.h"		// zug. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CErzeugerSheet

IMPLEMENT_DYNAMIC(CErzeugerSheet, CPropertySheet)

CErzeugerSheet::CErzeugerSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	AddPage (&m_pgFirma);
	AddPage (&m_pgAnfallStelle);
	AddPage (&m_pgEntsorgung);
	AddPage (&m_pgPartner);
	AddPage (&m_pgBranche);

//	KK990714
	CGakApp * pApp = (CGakApp *) AfxGetApp();
	if (pApp)
		pApp->SetErzWindow(this);


}

BEGIN_MESSAGE_MAP(CErzeugerSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CErzeugerSheet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CErzeugerSheet::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	CPropertySheet::PostNcDestroy();
	delete this;
}

/*
CString CErzeugerSheet::GetBranchenName ()
{
	return m_pgBranche.GetName ();
}
*/


