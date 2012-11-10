// SelNumberDlgUsage.cpp : implementation file
//

#include "stdafx.h"
#include "gak.h"

#include "selset.h"			// CSelectSet
#include "selnum.h"			// CSelNummerDlg
#include "SelNumberDlgUsage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelNumberDlgUsage dialog


CSelNumberDlgUsage::CSelNumberDlgUsage(UINT nIDTemplate, CWnd* pParent /*=NULL*/)
	: CDialog(nIDTemplate, pParent)
{
	//{{AFX_DATA_INIT(CSelNumberDlgUsage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pNumberDlg = NULL;
}


void CSelNumberDlgUsage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelNumberDlgUsage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

CSelNumberDlgUsage::~CSelNumberDlgUsage()
{
	DELETE_OBJ(m_pNumberDlg);
}

BEGIN_MESSAGE_MAP(CSelNumberDlgUsage, CDialog)
	//{{AFX_MSG_MAP(CSelNumberDlgUsage)
	ON_MESSAGE (IDM_SEND_TEXT, OnChangeName)
	ON_MESSAGE (IDM_SEND_NUMBER, OnChangeNummer)
	ON_MESSAGE (IDM_SEND_DELETEOBJ, OnDeleteNumberDlg)
	ON_WM_CLOSE()
	// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelNumberDlgUsage message handlers

LONG CSelNumberDlgUsage::OnDeleteNumberDlg (UINT, LONG)
{
	m_pNumberDlg = NULL;	
	return TRUE;
}

LONG CSelNumberDlgUsage::OnChangeName(UINT, LONG lText)
{
	CString strName((const char*) lText);
	DoChangeName(strName);
	return TRUE;
}

LONG CSelNumberDlgUsage::OnChangeNummer(UINT, LONG lText)	
{
	CString strNummer((const char*) lText);
	DoChangeNummer(strNummer);
	return TRUE;
}

void CSelNumberDlgUsage::Change (const CString &strTableName, UINT uiCaption, CString& strAktNummer, CSelectSet* pSelectSet)
{
	try
	{	
		if (!m_pNumberDlg)
		{
			ASSERT (NULL != pSelectSet);
			ASSERT (pSelectSet -> IsOpen ());
			ASSERT (!strTableName.IsEmpty ());
			m_pNumberDlg = new CSelNumberDlg (this, pSelectSet, uiCaption,
											  strTableName);
			if (!m_pNumberDlg -> Create (IDD_SEL_NUMMER))
				AfxThrowMemoryException ();
		}		

	//	aktuelle Selektion setzen
		m_pNumberDlg -> StoreSelection (strAktNummer);

	//	Fenster aktivieren
		m_pNumberDlg -> ShowWindow (SW_SHOWNORMAL);	
		m_pNumberDlg -> SetFocus ();
	}
	catch (CDaoException *e)
	{
		:: DisplayDaoException (e);
		e -> Delete ();
		DELETE_OBJ (m_pNumberDlg);
	}
	catch (CException* e)
	{
		e -> ReportError ();
		e -> Delete ();
		DELETE_OBJ (m_pNumberDlg);
	}
}
void CSelNumberDlgUsage::OnClose() 
{
	// der muﬂ hier zerlegt werden
	DELETE_OBJ(m_pNumberDlg);
}
