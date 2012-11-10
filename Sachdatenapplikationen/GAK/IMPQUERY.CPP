// ImpQuery.cpp : implementation file
//

#include "stdafx.h"		// prec. Header
#include "gak.h"		// CGakApp u. Ressourcen
#include "ImpQuery.h"	// zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImportQueryDialog dialog


CImportQueryDialog::CImportQueryDialog(CWnd* pParent, CDaoDatabase *pSource, CDaoDatabase *pDest)
	: CDialog(CImportQueryDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CImportQueryDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	ASSERT (NULL != pSource);
	ASSERT (pSource -> IsOpen ());
	ASSERT (NULL != pDest);
	ASSERT (pDest -> IsOpen ());

	m_pSourceDatabase = pSource;
	m_pDestDatabase = pDest;
}


void CImportQueryDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImportQueryDialog)
	DDX_Control(pDX, IDOK, m_btOk);
	DDX_Control(pDX, IDL_QUERIES, m_lbQueries);
	DDX_Control(pDX, IDB_SELECT, m_btSelect);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CImportQueryDialog, CDialog)
	//{{AFX_MSG_MAP(CImportQueryDialog)
	ON_BN_CLICKED(IDB_SELECT, OnSelect)
	ON_LBN_SELCHANGE(IDL_QUERIES, OnSelchangeQueries)
	ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImportQueryDialog message handlers

BOOL CImportQueryDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
//	TODO: Add extra initialization here
	m_btOk.EnableWindow (FALSE);

//	Auswahl Button setzen
	CString strInfo;
	VERIFY (strInfo.LoadString (IDS_TEXT_ALL_SELECT));
	m_btSelect.SetWindowText (strInfo);

//	Caption setzen
	ASSERT (NULL != m_pSourceDatabase);
	ASSERT (m_pSourceDatabase -> IsOpen ());
	CString strPath = m_pSourceDatabase -> GetName ();
	CString strFileName;
	char *pFileName = strFileName.GetBuffer (_MAX_FNAME);
	_splitpath (strPath, NULL, NULL, pFileName, NULL);
	AfxFormatString1 (strPath, IDS_IMP_QUERY_CAPTION, strupr (pFileName));
	SetWindowText (strPath);

//	Abfragen in ListBox ausgeben
	int iMax = m_pSourceDatabase -> GetQueryDefCount ();
	CDaoQueryDefInfo Info;
	int iMaxLen = 0;
	for (int iIndex = 0; iIndex < iMax; iIndex++)
	{
		m_pSourceDatabase -> GetQueryDefInfo (iIndex, Info);
		if (m_lbQueries.AddString (Info.m_strName) < 0)
			AfxThrowMemoryException ();
		iMaxLen = max (iMaxLen, Info.m_strName.GetLength ());
	}	
	
//	Scrollbalken setzen
	if (iMaxLen > 0)
	{
		WORD wUnits = LOWORD (:: GetDialogBaseUnits ());
		m_lbQueries.SetHorizontalExtent (iMaxLen *wUnits);
	}
	
//	wenn keine Abfragen vorhanden
	if (m_lbQueries.GetCount () <= 0)
	{
		CString strErr;
		AfxFormatString1 (strErr, IDS_NO_QUERIES, pFileName);
		((CGakApp *) AfxGetApp ()) -> OutputMessage (strErr);
		EndDialog (IDCANCEL);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//	Info für Auswahl
void CImportQueryDialog::OnSelect() 
{
	BOOL bSel = m_btSelect.GetCheck () == 1 ? TRUE : FALSE;
	CString strInfo;
	VERIFY (strInfo.LoadString (bSel ? IDS_TEXT_ALL_SELECT : IDS_TEXT_NO_SELECT));
	m_btSelect.SetWindowText (strInfo);	

//	Selektion durchführen
	int iCnt = m_lbQueries.GetCount ();
	if (iCnt <= 0)
		return;

	m_lbQueries.SelItemRange (bSel, 0, iCnt - 1);
	OnSelchangeQueries();
}

//	Import-Button setzen
void CImportQueryDialog::OnSelchangeQueries() 
{
	m_btOk.EnableWindow (m_lbQueries.GetSelCount () > 0);
}

//	Import der Abfragen durchführen
void CImportQueryDialog::OnOK() 
{
//	püfe Databasen
	ASSERT (NULL != m_pSourceDatabase);
	ASSERT (m_pSourceDatabase -> IsOpen ());
	ASSERT (NULL != m_pDestDatabase);
	ASSERT (m_pDestDatabase -> IsOpen ());

	LPINT pInt = NULL;

	try
	{
		CWaitCursor wc;
		int iCnt = m_lbQueries.GetSelCount ();
		if (iCnt <= 0)
			AfxThrowUserException ();

		pInt = new int [iCnt + 1];
		memset (pInt, -1, iCnt * sizeof (int));

	//	lese selektierte Items
		m_lbQueries.GetSelItems (iCnt, pInt);
		CString strQuery;
		CDaoQueryDefInfo Info;
		for (int iIndex = 0; iIndex < iCnt; iIndex++)
		{
		//	lese Name der Abfrage
			strQuery.Empty ();
			m_lbQueries.GetText (pInt [iIndex], strQuery);			
			ASSERT (!strQuery.IsEmpty ());

		//	lese QueryInfo
			m_pSourceDatabase -> GetQueryDefInfo (strQuery, Info, AFX_DAO_ALL_INFO);
		
		//	neue Def erzeugen
			CDaoQueryDef Query (m_pDestDatabase);
			Query.Create (Info.m_strName, Info.m_strSQL);
			Query.Append ();
			if (Query.IsOpen ())
				Query.Close ();
		}

	}
	catch (CUserException *ue)
	{
		ue -> Delete ();			// hier nur Abbruch
	}
	catch (CDaoException *e)
	{
		:: DisplayDaoException (e);
		e -> Delete ();
	}
	catch (CException *e) 
	{
		e -> ReportError ();
		e -> Delete ();
	}

//	Speicher freigeben
	DELETE_OBJ (pInt);

//	Collection auffrischen
	DAO_CHECK(m_pDestDatabase -> m_pDAOQueryDefs -> Refresh ());
	
	CDialog::OnOK();
}

BOOL CImportQueryDialog::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	// TODO: Add your message handler code here and/or call default
	
	// return CDialog::OnHelpInfo(pHelpInfo);
	ASSERT (pHelpInfo != NULL);

	if (pHelpInfo -> dwContextId)
		WinHelp (pHelpInfo -> dwContextId, HELP_CONTEXTPOPUP);

	return TRUE;
}

