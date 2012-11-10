// InTablPg.cpp : implementation file
//

#include "stdafx.h"		// prec.Header
#include "gak.h"		// CGakApp u. Ressourcen
#include "importty.h"	// Importtypen
#include "InTablPg.h"	// zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// globale Funktion 
// richtiger Tabellentyp
BOOL CheckTable (CDaoRecordset &Set, FieldKonvert *pInfo, const CString& strTableName)
{
	try
	{
		CWaitCursor wc;
		CMutex mt;
		ASSERT (Set.IsOpen ());
		ASSERT (NULL != pInfo);

	//	Suche alle Felder
		CDaoFieldInfo FieldInfo;
		CString strError;
		while (pInfo && pInfo -> pFieldName && *pInfo -> pFieldName)
		{
			try
			{
				Set.GetFieldInfo (pInfo -> pFieldName, FieldInfo);			
			}
			catch (CMemoryException *me)
			{
				me -> ReportError ();
				me -> Delete ();
				return FALSE;
			}
			catch (CDaoException *de)
			{
				de -> Delete ();
				AfxFormatString1 (strError, IDS_FIELD_NOT_FOUND, pInfo -> pFieldName);
				throw strError;
			}
			
		//	Datentyp ok ?
			if (FieldInfo.m_nType != pInfo -> sType)
			{
				AfxFormatString1 (strError, IDS_FIELD_NO_TYPE, pInfo -> pFieldName);
				throw strError;
			}
		
		//	ggf. auch Länge vergleichen
			if ((pInfo -> sLen > 0) &&
				(pInfo -> sLen < FieldInfo.m_lSize))	// angeg. Länge muß kleiner gleich tatsächlicher sein
			{
				CString strLen;
				strLen.Format ("%ld", pInfo -> sLen);
				AfxFormatString2 (strError, IDS_FIELD_NO_LEN, pInfo -> pFieldName, strLen);
				throw strError;
			}				

			pInfo++;
		}			

		return TRUE;
	}
	catch (CString str)
	{
	//	Struktur stimmt nicht: Meldung an Nutzer
		CString strOutput;
		AfxFormatString2 (strOutput, IDS_NO_VALID_STRUCTUR, strTableName, str);
		((CGakApp *) AfxGetApp ()) -> OutputMessage (strOutput);
	}

	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CInputTablePage property page

IMPLEMENT_DYNCREATE(CInputTablePage, CPropertyPage)

CInputTablePage::CInputTablePage() : CPropertyPage(CInputTablePage::IDD)
{
	m_pParams = NULL;
	//{{AFX_DATA_INIT(CInputTablePage)
	//}}AFX_DATA_INIT
}

CInputTablePage::~CInputTablePage()
{
}

void CInputTablePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInputTablePage)
	DDX_Control(pDX, IDL_TABLES, m_lbTables);
	DDX_Control(pDX, IDE_PATH, m_edDatabase);
	DDX_Control(pDX, IDB_MDB_TABLE, m_btMdbTable);
	DDX_Control(pDX, IDB_ABFALL, m_btAbfall);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CInputTablePage, CPropertyPage)
	//{{AFX_MSG_MAP(CInputTablePage)
	ON_BN_CLICKED(IDB_MDB_TABLE, OnMdbTable)
	ON_BN_CLICKED(IDB_FOX_TABLE, OnFoxTable)
	ON_BN_CLICKED(IDB_CHANGE, OnChangeDatabase)
	ON_BN_CLICKED(IDB_ABFALL, OnAbfall)
	ON_BN_CLICKED(IDB_ERZEUGER, OnErzeuger)
	ON_BN_CLICKED(IDB_BRANCH, OnBranch)
	ON_BN_CLICKED(IDB_ABFALL_ARTEN, OnAbfallArten)
	ON_BN_CLICKED(IDB_TRANSPORTEURE, OnTransporteure)
	ON_BN_CLICKED(IDB_ENTSORGER, OnEntsorger)
	ON_BN_CLICKED(IDB_GEMEINDEN, OnGemeinden)
	ON_LBN_SELCHANGE(IDL_TABLES, OnSelchangeTables)
	ON_BN_CLICKED(IDB_OLD_VERSION, OnOldVersionMdb)
	ON_BN_CLICKED(IDB_OLD_VERSION_FOX, OnOldVersionFox)
	ON_BN_CLICKED(IDB_KREISE, OnKreise)
	ON_BN_CLICKED(IDB_VERBRINGUNG, OnVerbringung)
	ON_BN_CLICKED(IDB_VERFAHREN, OnVerfahren)
	ON_COMMAND(ID_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CInputTablePage::SetParams (CImportParams &Params)
{
	m_pParams = &Params;
}

/////////////////////////////////////////////////////////////////////////////
// CInputTablePage message handlers
BOOL CInputTablePage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
//	TODO: Add extra initialization here
	ASSERT (NULL != m_pParams);
	m_pParams -> m_tTableType = Abfall;
	m_pParams -> m_tImportType = MdbTable;
	m_bOpenTyp = TRUE;				// MDB-Database
	m_btMdbTable.SetCheck (1);
	m_btAbfall.SetCheck (1);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CInputTablePage::OnMdbTable() 
{
	// TODO: Add your control notification handler code here
	SetTableInfo (MdbTable, m_pParams -> m_tTableType);
	SetWizardButton ();
}

void CInputTablePage::OnOldVersionMdb()
{
	// TODO: Add your control notification handler code here
	SetTableInfo (MdbTableOld, m_pParams -> m_tTableType);
	SetWizardButton ();
}

void CInputTablePage::OnFoxTable() 
{
	// TODO: Add your control notification handler code here
	SetTableInfo (FoxProTable, m_pParams -> m_tTableType);
	SetWizardButton ();
}

void CInputTablePage::OnOldVersionFox() 
{
	SetTableInfo (FoxProTableOld, m_pParams -> m_tTableType);
	SetWizardButton ();
}

void CInputTablePage::OnAbfall() 
{
	// TODO: Add your control notification handler code here
	SetTableInfo (m_pParams -> m_tImportType, Abfall);
	SetWizardButton ();		
}

void CInputTablePage::OnErzeuger() 
{
	// TODO: Add your control notification handler code here
	SetTableInfo (m_pParams -> m_tImportType, Erzeuger);
	SetWizardButton ();	
}

void CInputTablePage::OnBranch() 
{
	// TODO: Add your control notification handler code here
	SetTableInfo (m_pParams -> m_tImportType, Branchen);
	SetWizardButton ();	
}

void CInputTablePage::OnVerfahren() 
{
	// TODO: Add your control notification handler code here
	SetTableInfo (m_pParams -> m_tImportType, Verfahren);
	SetWizardButton ();	
}

void CInputTablePage::OnAbfallArten() 
{
	// TODO: Add your control notification handler code here
	SetTableInfo (m_pParams -> m_tImportType, Abfallarten);
	SetWizardButton ();	
}

void CInputTablePage::OnTransporteure() 
{
	// TODO: Add your control notification handler code here
	SetTableInfo (m_pParams -> m_tImportType, Transporteure);
	SetWizardButton ();	
}

void CInputTablePage::OnEntsorger() 
{
	// TODO: Add your control notification handler code here
	SetTableInfo (m_pParams -> m_tImportType, Entsorger);
	SetWizardButton ();	
}

void CInputTablePage::OnGemeinden() 
{
	// TODO: Add your control notification handler code here
	SetTableInfo (m_pParams -> m_tImportType, Gemeinden);
	SetWizardButton ();	
}

void CInputTablePage::OnKreise() 
{
	// TODO: Add your control notification handler code here
	SetTableInfo (m_pParams -> m_tImportType, Kreise);
	SetWizardButton ();	
}

void CInputTablePage::OnVerbringung() 
{
	// TODO: Add your control notification handler code here
	SetTableInfo (m_pParams -> m_tImportType, Verbringung);
	SetWizardButton ();	
}

void CInputTablePage::OnChangeDatabase() 
{
	// TODO: Add your control notification handler code here
	try
	{
		ASSERT (NULL != m_pParams);
		if ((MdbTable == m_pParams -> m_tImportType) || 
			(MdbTableOld == m_pParams -> m_tImportType))
			m_bOpenTyp = TRUE;
		else
			m_bOpenTyp = FALSE;

	//	Datei-Auswahl-Diolog öffnen
		CString strExt, strFilter, strCaption;
		VERIFY (strExt.LoadString (m_bOpenTyp ? IDS_DATABASE_EXTENSION : IDS_FOXPRO_EXTENSION));
		VERIFY (strFilter.LoadString (m_bOpenTyp ? IDS_MDB_FILTER : IDS_FOXPRO_FILTER));
		VERIFY (strCaption.LoadString (IDS_SELECT_DB_CAPTION));

		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;		// voreingest.
		CFileDialog Dlg (TRUE, strExt, NULL, dwFlags, strFilter, this);

	//	Datenpfad ermitteln
		CString strDataPath (((CGakApp *) AfxGetApp ()) -> DatabaseName ());
		CString strDrive, strDir, strNewPath;
		char *pDrive = strDrive.GetBuffer (_MAX_DRIVE); 
		char *pDir = strDir.GetBuffer (_MAX_DIR);
		char *pNewPath = strNewPath.GetBuffer (_MAX_PATH);
		_splitpath (strDataPath, pDrive, pDir, NULL, NULL);
		_makepath (pNewPath, pDrive, pDir, NULL, NULL);

		Dlg.m_ofn.lpstrInitialDir = pNewPath;	// Pfad setzen
		Dlg.m_ofn.lpstrTitle = strCaption;
		if (IDOK != Dlg.DoModal ())
			AfxThrowUserException ();			// alles bleibt beim alten

	//	alten Set ggf. schließen
		if (m_pParams -> m_SourceSet.IsOpen ())
			m_pParams -> m_SourceSet.Close ();
		if (m_pParams -> m_SourceDatabase.IsOpen ())
			m_pParams -> m_SourceDatabase.Close ();

	//	alten Infos löschen
		m_lbTables.ResetContent ();
		m_edDatabase.SetWindowText ("");

	//	Database öffnen
		if (m_bOpenTyp)	// MDB-Datei
		{
			m_pParams -> m_SourceDatabase.Open (Dlg.GetPathName ());
												// FALSE,	/* nicht exclusiv */
												// TRUE);	/* read only */
			SetTableInfo (m_pParams -> m_tImportType, m_pParams -> m_tTableType);
		}
		else		// FOXPRO
		{
			CString strConnect;
			VERIFY (strConnect.LoadString (IDS_FOXPRO_CONNECT));
			_splitpath (Dlg.GetPathName (), pDrive, pDir, NULL, NULL);
			_makepath (pNewPath, pDrive, pDir, NULL, NULL);
			m_pParams -> m_SourceDatabase.Open (pNewPath, 
												FALSE,	/* nicht exclusiv */
												TRUE,	/* read only */
												_T(strConnect));	
			SetTableInfo (m_pParams -> m_tImportType, m_pParams -> m_tTableType);
		}

	//	Tabellen ausgeben
		int iCnt = m_pParams -> m_SourceDatabase.GetTableDefCount();
		CDaoTableDefInfo Info;
		for (short iIndex = 0; iIndex < iCnt; iIndex++)
		{
		//	primary info
			m_pParams -> m_SourceDatabase.GetTableDefInfo (iIndex, Info);	
			if (Info.m_lAttributes & dbSystemObject)	// keine
				continue;								// Systemtabellen

			if (m_lbTables.AddString (Info.m_strName) < 0)
				AfxThrowMemoryException ();
		}

	//	bei FOXPRO gleich Set öffnen
		if (!m_bOpenTyp)
		{
			m_pParams -> m_SourceSet.m_pDatabase = &m_pParams -> m_SourceDatabase;
			CString strSQL, strFileName;
			char *pFileName = strFileName.GetBuffer (_MAX_FNAME);
			_splitpath (Dlg.GetFileName (), NULL, NULL, pFileName, NULL);			
			AfxFormatString1 (strSQL, IDS_SELECT_ALL, pFileName);
			m_pParams -> m_SourceSet.Open (dbOpenSnapshot, strSQL, dbReadOnly);
			m_pParams -> m_strInputTableName = pFileName;
			m_lbTables.SelectString (-1, pFileName);
		}
		
	//	Name der Datenbank ausgeben
		m_edDatabase.SetWindowText (m_bOpenTyp ? Dlg.GetPathName () : pNewPath);
	}
	catch (CUserException *ue)
	{
		ue -> Delete ();		// hier Abbruch
	}
	catch (CException *e)
	{
		if (e -> IsKindOf (RUNTIME_CLASS (CDaoException)))
			:: DisplayDaoException ((CDaoException *) e);
		else
			e -> ReportError ();
		e -> Delete ();

		if (m_pParams -> m_SourceDatabase.IsOpen ())
			m_pParams -> m_SourceDatabase.Close ();
	}

	SetWizardButton ();	
}

BOOL CInputTablePage::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	SetWizardButton ();	
	return CPropertyPage::OnSetActive();
}

void CInputTablePage::SetWizardButton (void)
{
	ASSERT (NULL != m_pParams);
	if (CheckDatabase () &&				// Database-Einstellung OK
		m_pParams -> m_SourceSet.IsOpen () &&
		m_pParams -> m_pTableInfo &&
		CheckTable (m_pParams -> m_SourceSet, m_pParams -> m_pTableInfo -> InputTable (), 
					m_pParams -> m_pTableInfo -> TableName ()))
		GetParent () -> SetWizardButtons (PSWIZB_NEXT);
	else
		GetParent () -> SetWizardButtons (0);			

	m_lbTables.EnableWindow (m_lbTables.GetCount () > 0);
}

//	neue Tabelle ausgewählt
void CInputTablePage::OnSelchangeTables() 
{
	int iSel = m_lbTables.GetCurSel ();			
	if (iSel < 0)
		return;

	try
	{
		CMutex mt;
		CWaitCursor wc;
		ASSERT (NULL != m_pParams);
		ASSERT (m_pParams -> m_SourceDatabase.IsOpen ());

	//	Set öffnen
		if (m_pParams -> m_SourceSet.IsOpen ())
			m_pParams -> m_SourceSet.Close ();
		CString strTable, strSQL;
		m_lbTables.GetText (iSel, strTable);
		m_pParams -> m_SourceSet.m_pDatabase = &m_pParams -> m_SourceDatabase;
		AfxFormatString1 (strSQL, IDS_SELECT_ALL, strTable);
		m_pParams -> m_SourceSet.Open (dbOpenSnapshot, strSQL, dbReadOnly);

	//	hat diese Tabelle Datensätze ?
		if (m_pParams -> m_SourceSet.IsBOF ())
		{
			m_pParams -> m_SourceSet.Close ();
			m_pParams -> m_strInputTableName.Empty ();

		//	Nutzer informieren
			CString strInfo;
			AfxFormatString1 (strInfo, IDS_EMPTY_INPUT_TABLE, strTable);
			((CGakApp *) AfxGetApp ()) -> OutputMessage (strInfo);
		}
		else
			m_pParams -> m_strInputTableName = strTable;
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

BOOL CInputTablePage::CheckDatabase(void)
{
	ASSERT (NULL != m_pParams);
	if (!m_pParams -> m_SourceDatabase.IsOpen ())
		return FALSE;

	if (m_bOpenTyp)
		return ((MdbTable == m_pParams -> m_tImportType) || (MdbTableOld == m_pParams -> m_tImportType));
	else
		return ((FoxProTable == m_pParams -> m_tImportType) || (FoxProTableOld == m_pParams -> m_tImportType));
}

void CInputTablePage::SetTableInfo (ImportType iType, TableType tType)
{
	ASSERT (NULL != m_pParams);
	ASSERT ((MdbTable == iType) || (MdbTableOld == iType) || 
			(FoxProTable == iType) || (FoxProTableOld == iType));

//	ggf. garnichts machen
	if (m_pParams -> m_pTableInfo && 
	   (iType == m_pParams -> m_tImportType) &&
	   (tType == m_pParams -> m_tTableType))
		return;
	
	try 
	{
	//	alte Info löschen
		DELETE_OBJ (m_pParams -> m_pTableInfo);
		switch (tType)
		{
			case Abfall:
				m_pParams -> m_pTableInfo = new CAbfallTableInfo (iType);
			break;
			case Erzeuger:
				m_pParams -> m_pTableInfo = new CErzeugerTableInfo (iType);
			break;
			case Branchen:
				m_pParams -> m_pTableInfo = new CBranchenTableInfo (iType);
			break;
			case Gemeinden:
				m_pParams -> m_pTableInfo = new CGemeindenTableInfo (iType);
			break;
			case Abfallarten:
				m_pParams -> m_pTableInfo = new CAbfallArtenTableInfo (iType);
			break;
			case Transporteure:
				m_pParams -> m_pTableInfo = new CTransporteureTableInfo (iType);
			break;
			case Entsorger:
				m_pParams -> m_pTableInfo = new CEntsorgerTableInfo (iType);
			break;
			case Kreise:
				m_pParams -> m_pTableInfo = new CKreisTableInfo (iType);				
			break;
			case Verbringung:
				m_pParams -> m_pTableInfo = new CVerbringungTableInfo (iType);
			break;
			case Verfahren:
				m_pParams -> m_pTableInfo = new CVerfahrenTableInfo (iType);
			break;
			default:
				ASSERT (FALSE);
		}

		m_pParams -> m_tTableType = tType;
		m_pParams -> m_tImportType = iType;
	}
	catch (CException *e)
	{
		e -> ReportError ();
		e -> Delete ();
	}
}	

void CInputTablePage :: OnHelp ()
{
	AfxGetApp () -> WinHelp (IDD+HelpDialogOffset);
}
