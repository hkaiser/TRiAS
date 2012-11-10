// Compact.cpp : implementation file
//

#include "stdafx.h"		// prec. Header
#include "gak.h"		// Ressourcen und CGakApp
#include "Compact.h"	// zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCompactDataBase dialog
CCompactDataBase::CCompactDataBase(CWnd* pParent, const char *pOldName)
	: CDialog(CCompactDataBase::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCompactDataBase)
	//}}AFX_DATA_INIT
#ifdef MDB_VERSION20
	m_iVersion = dbVersion20;		// voreingestellte Version 2.0
#else
	m_iVersion = dbVersion30;		// voreingestellte Version 3.0
#endif
	ASSERT (pOldName != NULL && AfxIsValidString (pOldName));
	if (!*pOldName)
		AfxThrowUserException ();

	m_strOldDatabase = pOldName;
}


void CCompactDataBase::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCompactDataBase)
	DDX_Control(pDX, IDE_FILENAME, m_edFileName);
	DDX_Control(pDX, IDB_AS_NEW, m_btAsNew);
	DDX_Control(pDX, IDOK, m_btOk);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCompactDataBase, CDialog)
	//{{AFX_MSG_MAP(CCompactDataBase)
	ON_BN_CLICKED(IDB_FILE_NAME, OnFileName)
	ON_BN_CLICKED(IDB_VERSION10, OnVersion10)
	ON_BN_CLICKED(IDB_VERSION11, OnVersion11)
	ON_BN_CLICKED(IDB_VERSION20, OnVersion20)
	ON_BN_CLICKED(IDB_VERSION30, OnVersion30)
	ON_EN_CHANGE(IDE_FILENAME, OnChangeFilename)
	ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCompactDataBase message handlers

void CCompactDataBase::OnFileName() // OK
{
	// TODO: Add your control notification handler code here
	CString strExt, strFilter, strCaption;
	if (!strExt.LoadString (IDS_DATABASE_EXTENSION) || 
		!strCaption.LoadString (IDS_COMPACT_CAPTION) ||
		!strFilter.LoadString (IDS_MDB_FILTER))
		AfxThrowResourceException ();

	DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;		// voreingest.
	CFileDialog Dlg (FALSE, strExt, NULL, dwFlags, strFilter, this);
	Dlg.m_ofn.lpstrInitialDir = m_strDir;
	Dlg.m_ofn.lpstrTitle = strCaption;
	if (IDOK == Dlg.DoModal ())
	{
		CString strNewDatabase;
		strNewDatabase = Dlg.GetPathName ();
		if (0 != m_strOldDatabase.CompareNoCase (strNewDatabase))
		{
			strNewDatabase.MakeUpper ();
			m_edFileName.SetWindowText (strNewDatabase);
		}
		else
		//	Namen müssen verschieden sein --> Meldung an Nutzer
		{
			CGakApp *pApp = (CGakApp *) AfxGetApp ();
			ASSERT (pApp != NULL);
			ASSERT_VALID (pApp);
			pApp -> OutputMessage (IDS_DIFF_DATABASE);
		}
	}
}

void CCompactDataBase::OnOK() 
{
	//	TODO: Add extra validation here
	CWaitCursorExt wc (IDS_COMPACT_DATASE);
	CDaoWorkspace Space;
	try
	{
		Space.Open ();				// Open default Workspace

	//	Komprimierung durchführen
		CString strNewName;
		m_edFileName.GetWindowText (strNewName);
		Space.CompactDatabase (m_strOldDatabase, strNewName, dbLangGeneral, m_iVersion);

	// ggf. neue DB verwenden
		if (1 == m_btAsNew.GetCheck ())
		{
			CGakApp *pApp = (CGakApp *) AfxGetApp ();
			ASSERT (pApp != NULL);
			ASSERT_VALID (pApp);
			CString strDatabase;
			m_edFileName.GetWindowText (strDatabase);
			pApp -> SetNewDatabase (strDatabase);
		}


		Space.Close ();
	}
	catch (CException *e)
	{
		if (Space.IsOpen ())
			Space.Close ();
		throw e;
	}

	CDialog::OnOK();
}

void CCompactDataBase::OnVersion10() // ok
{
	// TODO: Add your control notification handler code here
	m_iVersion = dbVersion10;
}

void CCompactDataBase::OnVersion11() // ok
{
	// TODO: Add your control notification handler code here
	m_iVersion = dbVersion11;
}

void CCompactDataBase::OnVersion20() // ok
{
	// TODO: Add your control notification handler code here
	m_iVersion = dbVersion20;
}

void CCompactDataBase::OnVersion30() // ok
{
	// TODO: Add your control notification handler code here
	m_iVersion = dbVersion30;
}

BOOL CCompactDataBase::OnInitDialog() // ok
{
	CDialog::OnInitDialog();
	
//	TODO: Add extra initialization here
	CButton *pButton = NULL;
	if (dbVersion30 == m_iVersion)
		pButton = (CButton *) GetDlgItem (IDB_VERSION30);		
	else
		pButton = (CButton *) GetDlgItem (IDB_VERSION20);		
	ASSERT (NULL != pButton);
	pButton -> SetCheck (1);

	m_btAsNew.SetCheck (1);
	m_btOk.EnableWindow (FALSE);

//	Caption neu bilden
	ASSERT (!m_strOldDatabase.IsEmpty ());

	CString strFileName, strExt, strCaption, strDrive, strDir, strPath;
	char *pFileName = strFileName.GetBuffer (_MAX_FNAME);
	char *pExt = strExt.GetBuffer (_MAX_EXT);
	char *pDrive = strDrive.GetBuffer (_MAX_DRIVE);
	char *pDir = strDir.GetBuffer (_MAX_DIR);
	char *pPath = strPath.GetBuffer (_MAX_PATH);
	_splitpath (m_strOldDatabase, pDrive, pDir, pFileName, pExt);
	_makepath (pPath, pDrive, pDir, NULL, NULL);
	m_strDir = pPath;				// Verzeichnis speichern
	AfxFormatString2 (strCaption, IDS_COMPACT_DATABASE, 
					  strupr (pFileName), strupr (pExt));
	SetWindowText (strCaption);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCompactDataBase::OnChangeFilename() // ok
{
	// TODO: Add your control notification handler code here
	m_btOk.EnableWindow (m_edFileName.LineLength () > 0);	
}

BOOL CCompactDataBase::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	// TODO: Add your message handler code here and/or call default

	ASSERT (pHelpInfo != NULL);
	// pHelpInfo -> iCtrlId = ID_VIEW_TOOLBAR;
	// return CDialog::OnHelpInfo(pHelpInfo);

	if (pHelpInfo -> dwContextId)
		WinHelp (pHelpInfo -> dwContextId, HELP_CONTEXTPOPUP);

	return TRUE;
}
