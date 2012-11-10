// OutTbPg.cpp : implementation file
//

#include "stdafx.h"		// prec. Header
#include "gak.h"		// CGakApp u. Ressourcen
#include "importty.h"	// Importtypen
#include "OutTbPg.h"	// zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//	externe Funktionen
BOOL CheckTable (CDaoRecordset &Set, FieldKonvert *pInfo, const CString& strTableName);

/////////////////////////////////////////////////////////////////////////////
// COutputTablePage property page

IMPLEMENT_DYNCREATE(COutputTablePage, CPropertyPage)

COutputTablePage::COutputTablePage() : CPropertyPage(COutputTablePage::IDD)
{
	//{{AFX_DATA_INIT(COutputTablePage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pParams = NULL;
}

COutputTablePage::~COutputTablePage()
{
}

void COutputTablePage::SetParams (CImportParams &Params)
{
	m_pParams = &Params;
}

void COutputTablePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COutputTablePage)
	DDX_Control(pDX, IDB_AS_NEW, m_btAsNew);
	DDX_Control(pDX, IDS_INFO, m_stInfo);
	DDX_Control(pDX, IDB_CREATE, m_btCreate);
	DDX_Control(pDX, IDL_TABLES, m_lbTables);
	DDX_Control(pDX, IDE_TABLE_NAME, m_edTableName);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(COutputTablePage, CPropertyPage)
	//{{AFX_MSG_MAP(COutputTablePage)
	ON_EN_CHANGE(IDE_TABLE_NAME, OnChangeTableName)
	ON_LBN_SELCHANGE(IDL_TABLES, OnSelchangeTables)
	ON_BN_CLICKED(IDB_CREATE, OnCreate)
	ON_BN_CLICKED(IDB_AS_NEW, OnAsNew)
	ON_COMMAND(ID_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutputTablePage message handlers

BOOL COutputTablePage::OnInitDialog()	// kein try/catch
{
	CPropertyPage::OnInitDialog();
	
//	TODO: Add extra initialization here
	m_edTableName.LimitText (MaxTableNameLen);

	OutputTableNames ();

	SetWizardButton ();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void COutputTablePage::OnChangeTableName() 
{
	m_btCreate.EnableWindow (m_edTableName.LineLength () > 0);
}

void COutputTablePage::OnSelchangeTables() 
{
	int iSel = m_lbTables.GetCurSel ();			
	if (iSel < 0)
		return;

	try
	{
		CMutex mt;
		CWaitCursor wc;
		ASSERT (NULL != m_pParams);
		ASSERT (m_pParams -> m_DestDatabase.IsOpen ());

	//	Test ob Quelle und Ziel identisch ?
		CString strTable;
		m_lbTables.GetText (iSel, strTable);
		if ((m_pParams->m_DestDatabase.GetName().CompareNoCase(m_pParams -> m_SourceDatabase.GetName ())==0) &&
			(m_pParams->m_strInputTableName.CompareNoCase(strTable)==0))
		{
			((CGakApp *)AfxGetApp ()) -> OutputMessage (IDS_DIFF_IN_OUT_TABLE);
			AfxThrowUserException ();
		}			

	//	Set öffnen
		if (m_pParams -> m_DestSet.IsOpen ())
			m_pParams -> m_DestSet.Close ();
		CString strSQL;
		m_pParams -> m_DestSet.m_pDatabase = &m_pParams -> m_DestDatabase;
		AfxFormatString1 (strSQL, IDS_SELECT_ALL, strTable);
		m_pParams -> m_DestSet.Open (dbOpenDynaset, strSQL);
		m_pParams -> m_strOutputTableName = strTable;
	}
	catch (CUserException *e)
	{
		e -> Delete ();			// Meldung bereits ausgegeben
	}
	catch (CDaoException *e)
	{
		:: DisplayDaoException (e);
		e -> Delete ();
		m_lbTables.SetCurSel (-1);
	}
	catch (CException *e)
	{
		e -> ReportError ();
		e -> Delete ();
		m_lbTables.SetCurSel (-1);
	}		
	SetWizardButton ();	
}

BOOL COutputTablePage::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	//	Caption setzen
	CString strCaption;
	AfxFormatString1 (strCaption, IDS_OUTPUT_TABLE_INFO, m_pParams -> m_pTableInfo -> TableName ());
	m_stInfo.SetWindowText (strCaption);

	m_btAsNew.SetCheck (m_pParams -> m_bAsNewTable);

	SetWizardButton ();
	
	return CPropertyPage::OnSetActive();
}

void COutputTablePage::SetWizardButton ()
{
	ASSERT (NULL != m_pParams);
	if (m_pParams -> m_DestSet.IsOpen () &&
		m_pParams -> m_pTableInfo &&
		CheckTable (m_pParams -> m_DestSet, m_pParams -> m_pTableInfo -> OutputTable (), 
					m_pParams -> m_pTableInfo -> TableName ()))
		GetParent () -> SetWizardButtons (PSWIZB_BACK|PSWIZB_NEXT);
	else
		GetParent () -> SetWizardButtons (PSWIZB_BACK);			

	m_lbTables.EnableWindow (m_lbTables.GetCount () > 0);
	m_btCreate.EnableWindow (m_edTableName.LineLength () > 0);
}

void COutputTablePage::OutputTableNames ()
{
	try
	{
	//	Tabellen ausgeben
		CMutex mt;
		CWaitCursor wc;
		ASSERT (NULL != m_pParams);
		ASSERT (m_pParams -> m_DestDatabase.IsOpen ());
		m_lbTables.ResetContent ();
		int iCnt = m_pParams -> m_DestDatabase.GetTableDefCount();
		CDaoTableDefInfo Info;
		for (short iIndex = 0; iIndex < iCnt; iIndex++)
		{
		//	primary info
			m_pParams -> m_DestDatabase.GetTableDefInfo (iIndex, Info);	
			if (Info.m_lAttributes & dbSystemObject)	// keine
				continue;								// Systemtabellen

			if (m_lbTables.AddString (Info.m_strName) < 0)
				AfxThrowMemoryException ();
		}
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
}

//	neue Tabelle erzeugen
void COutputTablePage::OnCreate() 
{
	try
	{
		CMutex mt;
		CWaitCursor wc;
		ASSERT (NULL != m_pParams);
		ASSERT (m_pParams -> m_DestDatabase.IsOpen ());		

		m_btCreate.EnableWindow (FALSE);

	//	Tabelle erzeugen
		CString strTableName, strSQL, strFormat;
		m_edTableName.GetWindowText (strTableName);
		VERIFY (strFormat.LoadString (m_pParams -> m_pTableInfo -> DDLId ()));
		char *pSQL = strSQL.GetBuffer (strFormat.GetLength () + strTableName.GetLength () + 10);
		wsprintf (pSQL, strFormat, strTableName.operator LPCTSTR ());
		m_pParams->m_DestDatabase.Execute (pSQL, dbFailOnError);

		DAO_CHECK(m_pParams->m_DestDatabase.m_pDAOTableDefs->Refresh ());

		CString strFieldName, strDisAllowNull;
		strSQL.ReleaseBuffer ();
		VERIFY (strDisAllowNull.LoadString (IDS_DISALLOW_NULL));
		IndexFieldInfo *pFieldInfo = m_pParams -> m_pTableInfo -> GetIndexFieldInfo ();
		if (NULL != pFieldInfo)
		{
			do
			{
				AfxFormatString2 (strSQL, IDS_CREATE_INDEX_DDL, strTableName, pFieldInfo->pIndexName);
				if (pFieldInfo->bDisAllowNull)
					strSQL += " " + strDisAllowNull;
				m_pParams->m_DestDatabase.Execute (strSQL, dbFailOnError);
				pFieldInfo++;
			} 
			while ((NULL != pFieldInfo) && pFieldInfo->pIndexName && *pFieldInfo->pIndexName);
		}
		else	// Standard-Indizes erzeugen
		{
		//	non unique Index über Name erzeugen
			VERIFY (strFieldName.LoadString (IDS_NAME));
			AfxFormatString2 (strSQL, IDS_CREATE_INDEX_DDL, strTableName, strFieldName);
			strSQL += " " + strDisAllowNull;
			m_pParams->m_DestDatabase.Execute (strSQL, dbFailOnError);

		//	ggf. non unique Index über Nummer erzeugen
			if (m_pParams -> m_pTableInfo -> CreateNumberIndex ())
			{
				VERIFY (strFieldName.LoadString (IDS_NUMMER));
				AfxFormatString2 (strSQL, IDS_CREATE_INDEX_DDL, strTableName, strFieldName);
				strSQL += " " + strDisAllowNull;
				m_pParams->m_DestDatabase.Execute (strSQL, dbFailOnError);
			}
		}

	//	neuen Tabellen-Namen ausgeben
		OutputTableNames ();

	//	String selektieren
		m_lbTables.SelectString (-1, strTableName);

		OnSelchangeTables ();
	}
	catch (CDaoException *e)
	{
		:: DisplayDaoException (e);
		e -> Delete ();
		SetWizardButton ();
	}
	catch (CException *e)
	{
		e -> ReportError ();
		e -> Delete ();
		SetWizardButton ();
	}
}

void COutputTablePage::OnAsNew() 
{
	ASSERT (NULL != m_pParams);
	m_pParams -> m_bAsNewTable = m_btAsNew.GetCheck () == 1 ? TRUE : FALSE;
}

void COutputTablePage :: OnHelp ()
{
	AfxGetApp () -> WinHelp (IDD+HelpDialogOffset);
}
