// SelTable.cpp : implementation file
//

#include "stdafx.h"			//	prec. Header
#include "res.h"			//	Resource-Konstanten	
#include <tableset.hpp>		//  CTables
#include "SelTable.h"		//	zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelTable dialog
CSelTable::CSelTable(CWnd* pParent /*=NULL*/)
	: CDialog(CSelTable::IDD, pParent)
{
	m_strCaption = m_strTableName = "";
	m_bTableExists = m_bEnterNew = FALSE;
	m_pDataBase = NULL;
	//{{AFX_DATA_INIT(CSelTable)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CSelTable::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelTable)
	DDX_Control(pDX, IDOK, m_btOk);
	DDX_Control(pDX, IDL_LIST_TABLES, m_lbTables);
	DDX_Control(pDX, IDE_TABLE, m_edTable);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSelTable, CDialog)
	//{{AFX_MSG_MAP(CSelTable)
	ON_EN_CHANGE(IDE_TABLE, OnChangeTable)
	ON_LBN_DBLCLK(IDL_LIST_TABLES, OnDblclkListTables)
	ON_LBN_SELCHANGE(IDL_LIST_TABLES, OnSelchangeListTables)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelTable message handlers
BOOL CSelTable::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	TRY
	{
	//	TODO: Add extra initialization here
		m_btOk.EnableWindow (FALSE);

	//	lese Tabellen
		CWaitCursor wc;
		ASSERT (NULL != m_pDataBase);
		ASSERT (m_pDataBase -> IsOpen ());
	
		CTables Tables (m_pDataBase);
		Tables.Open ();
		int iMaxLen = 0;
		while (!Tables.IsEOF ())
		{
			if (m_lbTables.AddString (Tables.m_strName) < 0)
				AfxThrowMemoryException ();
			iMaxLen = max (iMaxLen, Tables.m_strName.GetLength ());
			Tables.MoveNext ();
		}

	//  Scrollbalken setzen
		if (iMaxLen > 0)
		{
			WORD wUnits = LOWORD (:: GetDialogBaseUnits ());
			m_lbTables.SetHorizontalExtent (iMaxLen*wUnits);
		}

		if (Tables.IsOpen ())
			Tables.Close ();
	}
	CATCH (CMemoryException, me)
	{
		OutputMemoryError ();
	}
	AND_CATCH (CFileException, fe)
	{
		OutputFileError (fe -> m_cause);
	}
	AND_CATCH (CDBException, de)
	{
        OutputError (de -> m_strError);
	}
	END_CATCH

	//	ListBox akt./deaktiv.
	m_lbTables.EnableWindow (m_lbTables.GetCount () > 0);

	//	Eingabfeld akt./deakt.
	m_edTable.EnableWindow (m_bEnterNew);

	//	Caption setzen
	SetWindowText (m_strCaption);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSelTable::OnChangeTable() 
{
	// TODO: Add your control notification handler code here
	m_btOk.EnableWindow (m_edTable.GetWindowTextLength () > 0);
}

//	neue Tabelle wurde gewählt
void CSelTable::OnDblclkListTables() 
{
	// TODO: Add your control notification handler code here
	int iSel = m_lbTables.GetCurSel ();
	if (iSel >= 0)
	{
		CString strTable;
		m_lbTables.GetText (iSel, strTable);
		m_edTable.SetWindowText (strTable);
		m_btOk.EnableWindow (TRUE);
//		OnOK ();
	}
}

void CSelTable::OnOK() 
{
	// TODO: Add extra validation here
	m_edTable.GetWindowText (m_strTableName);
	m_bTableExists = m_lbTables.FindStringExact (-1, m_strTableName) >= 0;
	CDialog::OnOK();
}

void CSelTable::OnCancel() 
{
	// TODO: Add extra cleanup here
	m_strTableName.Empty ();
	m_bTableExists = FALSE;

	CDialog::OnCancel();
}

void CSelTable::OnSelchangeListTables() 
{
	// TODO: Add your control notification handler code here
	int iSel = m_lbTables.GetCurSel ();
	if (iSel >= 0)
	{
		CString strTable;
		m_lbTables.GetText (iSel, strTable);
		m_edTable.SetWindowText (strTable);
		m_btOk.EnableWindow (TRUE);
//		OnOK ();
	}
	else
	{
		CString strTable(_T(""));
		m_edTable.SetWindowText (strTable);
	}
}
