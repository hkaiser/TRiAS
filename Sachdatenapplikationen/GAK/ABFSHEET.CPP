// AbfSheet.cpp : implementation file
//

#include "stdafx.h"			// prec. Header
#include "gak.h"			// CGakApp
#include "branpage.h"		// CBranchPage
#include "TransPge.h"		// CTransPage
#include "EntPage.h"		// CEntPage
#include "numedit.h"		// CErzNrEdit
#include "abfpage.h"		// CAbfPage
#include "BetrPage.h"		// CBetreiberPage
#include "AbfSheet.h"		// zugeh. Header
#include "recview.h"		// CDaoRecordViewExt	
#include "AbfView.h"		// CAbfView

// JG add Prog settings
#include "ProgSetting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAbfSheet

IMPLEMENT_DYNAMIC(CAbfSheet, CPropertySheet)

CAbfSheet :: CAbfSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
		   : CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	AddPage (&m_pgAbfall);
	AddPage (&m_pgTransPage);
	AddPage (&m_pgBetreiber);
	
	// abhängig von den *.ini-Daten entsprechende Seite anzeigen
	if (1 == GetEntsorgerPage())
	{
		AddPage (&m_pgEntPage);
	}
	else
	{
		AddPage (&m_pgEntPage2);
	}

//	KK990714
	CGakApp * pApp = (CGakApp *) AfxGetApp();
	if (pApp)
		pApp->SetAbfWindow(this);

}

BEGIN_MESSAGE_MAP(CAbfSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CAbfSheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAbfSheet message handlers
void CAbfSheet::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	CPropertySheet::PostNcDestroy();
	delete this;
}

/*
CString CAbfSheet::GetSonderAbfall (void)
{
	return m_pgAbfall.GetSonderAbfall ();
}

CString CAbfSheet::GetMengeT (void)
{
	return m_pgAbfall.GetMengeT ();
}

CString CAbfSheet::GetMengeM (void)
{
	return m_pgAbfall.GetMengeM ();
}

CString CAbfSheet::GetAbfallName (void)
{
	return m_pgAbfall.GetName ();
}

CString CAbfSheet::GetVorbehandlung (void)
{
	return m_pgAbfall.GetVorbehandlung ();
}

CString CAbfSheet::GetTranspName (void)
{
	return m_pgTransPage.GetName ();
}

CString CAbfSheet::GetTranspStrasse (void)
{
	return m_pgTransPage.GetStrasse ();
}

CString CAbfSheet::GetTranspOrt (void)
{
	return m_pgTransPage.GetOrt ();
}

CString CAbfSheet::GetTranspPlz (void)
{
	return m_pgTransPage.GetPlz ();
}

CString CAbfSheet::GetEntsName (void)
{
	return m_pgEntPage.GetName ();
}

CString CAbfSheet::GetEntsStrasse (void)
{
	return m_pgEntPage.GetStrasse ();
}

CString CAbfSheet::GetEntsOrt (void)
{
	return m_pgEntPage.GetOrt ();
}

CString CAbfSheet::GetEntsPlz (void)
{
	return m_pgEntPage.GetPlz ();
}

CString CAbfSheet::GetEntsArt (void)
{
	return m_pgEntPage.GetArt ();
}

CString CAbfSheet::GetVerwertung (void)
{
	return m_pgEntPage.GetVerwertung ();
}
*/

void CAbfSheet::SetCaption()
{
	((CAbfView *) GetParent ()) -> SetCaption ();
}

void CAbfSheet::DeleteAbfallGruppe()
{
	((CAbfView *) GetParent ()) -> DeleteAbfallGruppe();	
}
