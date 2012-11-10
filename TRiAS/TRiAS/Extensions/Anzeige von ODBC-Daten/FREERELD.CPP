// FreeRelD.cpp : implementation file
//

#include "pheader.h"		// vorübersetzter Header
#include "odbcext.hr"		// Resource-Konstanten
#include <odbcinst.h>		// SQLCreateDataSource u.a.
#include <hpp/tableset.hpp>		// CTables
#include <hpp/columnst.hpp>		// CColumnStatus
#include <hpp/waitcur.hpp>		// CWaitCursor
#include "tablinfo.hpp"		// CTableInfoTree
#include <hpp/getodbci.hpp>		// ODBC-Infos lesen
#include "profile.hpp"		// DBaseProfile
#include <hpp/helptext.hpp>		// CHelpText
#include <hpp/tabdlgs.hpp>		// CTabbedDialogs

#include "UserDlg.h"		// CUserDlg
#include "FileDlg.h"		// CFileDsnPage

#include "FreeRelD.hpp"		// zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// externe Funktionen
void CallMessageQueue (void);	// Steuerung an Windows zum Nachzeichnen

/////////////////////////////////////////////////////////////////////////////
// CFreeRelDialog dialog
CFreeRelDialog::CFreeRelDialog(CWnd* pParent, CString &strMaster,
							   CString &strKoppelField, short sKType, HPROJECT hPr)
							   :CDialog(CFreeRelDialog::IDD, pParent),
								m_tbDsn (3)
{
	//{{AFX_DATA_INIT(CFreeRelDialog)
	//}}AFX_DATA_INIT
	m_bResult = FALSE;
	m_tType = NoDataSource;
		
	m_hProject = hPr;

//	prüfe Parameter
	if (sKType == -1
		|| strMaster.GetLength () == 0
		|| strKoppelField.GetLength () == 0)
	{
		DEX_Error (RC_ctCFreeRel, EC_ILLPARS);
		return;
	}	       
	
	try
	{        
		m_strAliasName = strMaster;
		m_strKoppelField = strKoppelField;		
		m_sKoppelType = sKType;	
		m_bInfosStored = TRUE;		// speichern jetzt nicht notwendig
		m_bResult = TRUE;
	}
	catch (CMemoryException *me)
	{          
		me -> Delete ();
		DEX_Error (RC_ctCFreeRel, EC_NOMEMORY);
	}	
}

//	akt. Relation lesen             
BOOL CFreeRelDialog :: GetRelation (CString& strAliasName, CString& strKoppelField)
{
	if (m_strAliasName.GetLength () == 0 ||
		m_strKoppelField.GetLength () == 0)		
		return False;
		
	TRY
	{   
		strAliasName = m_strAliasName;
		strKoppelField = m_strKoppelField;
	}
	CATCH (CMemoryException, me)
	{           
		DEX_Error (RC_GetRelCFreeRel, EC_NOMEMORY);
		return False;
	}
	END_CATCH
	
	return True;		
}

void CFreeRelDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFreeRelDialog)
	DDX_Control(pDX, IDOK, m_btStoreConnection);
	DDX_Control(pDX, IDC_TABLENAME, m_cbTables);
	DDX_Control(pDX, IDC_KOPPELFIELD, m_cbKoppelFields);
	DDX_Control(pDX, IDC_DSN_TAB, m_tbDsn);
	DDX_Control(pDX, IDT_DESCRIPTION, m_stDescription);
	DDX_Control(pDX, IDE_ALIASNAME, m_edAliasName);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFreeRelDialog, CDialog)
	//{{AFX_MSG_MAP(CFreeRelDialog)
	ON_CBN_SELCHANGE(IDC_KOPPELFIELD, OnSelchangeKoppelfield)
	ON_CBN_SELCHANGE(IDC_TABLENAME, OnSelchangeTablename)
	ON_EN_CHANGE(IDE_ALIASNAME, OnChangeAliasname)
	ON_EN_SETFOCUS(IDE_ALIASNAME, OnOutputAliasDescription)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFreeRelDialog message handlers
BOOL CFreeRelDialog::OnInitDialog() 
{
	try
	{
		CDialog::OnInitDialog();
	
		// TODO: Add extra initialization here
		//	prüfe Parameter
		if (m_bResult == FALSE)
		{
			EndDialog (IDCANCEL);
			return TRUE;
		}

		CString strCaption;
		VERIFY (strCaption.LoadString (IDS_USER_DSN_CAPT));
		m_dlgUserDsn.m_tType = UserDataSource;
		VERIFY (0 == m_tbDsn.AddDialog (&m_dlgUserDsn, IDD_USER_DSN_MEDIUM, strCaption));
		VERIFY (strCaption.LoadString (IDS_SYSTEM_DSN_CAPT));
		m_dlgSystemDsn.m_tType = SystemDataSource;
		VERIFY (1 == m_tbDsn.AddDialog (&m_dlgSystemDsn, IDD_USER_DSN_MEDIUM, strCaption));
		VERIFY (strCaption.LoadString (IDS_FILE_DSN_CAPT));
		m_dlgFileDsn.m_tType = FileDataSource;
		VERIFY (2 == m_tbDsn.AddDialog (&m_dlgFileDsn, IDD_FILE_DSN_MEDIUM, strCaption));
		m_tbDsn.SetActiveDialog (0);

	//	Font für Beschreibungsfeld einstellen
		m_stDescription.InitFont ();

	//	Caption setzen
		AfxFormatString2 (strCaption, IDS_CREATERELATION, m_strAliasName, m_strKoppelField);
		SetWindowText (strCaption);
		m_strAliasName = "";
		m_strKoppelField = "";
	}			       	                                
	catch (CMemoryException *me)
	{
		m_bResult = FALSE;
		DEX_Error (RC_OnInitDialogCFreeRel, EC_NOMEMORY);
		me -> Delete ();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

// Store-Button setzen/rücksetzen                                    
void CFreeRelDialog :: SetStoreButton (void)
{       
	if ((m_bInfosStored == FALSE) &&						// wenn akt. Info noch nicht gespeichert
		(m_edAliasName.GetWindowTextLength () > 0) &&		// gültiger AliasName
		(m_cbTables.GetCurSel () >= 0) &&					// Tabelle ok		
		(m_cbKoppelFields.GetCurSel () >= 0))				// Koppelfeld ok
			m_btStoreConnection.EnableWindow (TRUE);
		else 
			m_btStoreConnection.EnableWindow (FALSE);	             			   
}		

void CFreeRelDialog::OnSelchangeKoppelfield() 
{
	// TODO: Add your control notification handler code here
	if (m_cbKoppelFields.GetCurSel () < 0)
		return;

	m_bInfosStored = FALSE;		// speichern wieder möglich        
	CString strSel;                                                
	m_cbKoppelFields.GetLBText (m_cbKoppelFields.GetCurSel (), strSel); 
	m_OdbcInfos.OutputColumnInfo (strSel, m_stDescription);                                          

	SetStoreButton ();		// Store-Button	
}

void CFreeRelDialog::OnSelchangeTablename() 
{
	// TODO: Add your control notification handler code here
		if (m_cbTables.GetCurSel ()	< 0)
		return;

	m_bInfosStored = FALSE;		// speichern wieder möglich           
	CString strTableName;
	m_cbTables.GetLBText (m_cbTables.GetCurSel (), strTableName);
	if (strTableName.GetLength () &&										// Name OK
		m_OdbcInfos.OutputColumnNames (strTableName, 
									   m_cbKoppelFields, m_sKoppelType) &&  // komp. Felder ausgegeben
		m_OdbcInfos.OutputTableInfo (strTableName, m_stDescription))	// Tabellen-Kommentar
	{
		m_btStoreConnection.EnableWindow (FALSE);                	// nicht mehr möglich
		m_edAliasName.SetWindowText (strTableName);				 	// immer neu setzen 
		m_cbKoppelFields.EnableWindow ();							//	Koppelfelder aktivieren                 
	}					
}

void CFreeRelDialog::OnChangeAliasname() 
{
	// TODO: Add your control notification handler code here
	m_bInfosStored = FALSE;		// speichern wieder möglich           
	SetStoreButton ();			// Store-Button
}

BOOL CFreeRelDialog::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (IDM_CONFIG_DSN == wParam || IDM_SELECT_DSN == wParam)
	{
	//	lese und prüfe Parameter
		DataSourceInfo *pInfo = (DataSourceInfo *)lParam;
		ASSERT (NULL != pInfo);
		ASSERT (NULL != pInfo -> pName && AfxIsValidString (pInfo -> pName));
		ASSERT ((UserDataSource == pInfo->tType) || (SystemDataSource == pInfo-> tType) ||
				 (FileDataSource == pInfo->tType));
		
		m_bInfosStored = FALSE;		// speichern wieder möglich                                      		
		ResetODBCInfos ();        	// alten ODBC-Infos löschen                                    

		if ((strlen (pInfo->pName) > 0) &&							// Name ok
			m_OdbcInfos.CreateDataBase (pInfo->pName, pInfo->tType)&&// neues Data-Source-Objekt erzeugen   
			m_OdbcInfos.OutputDataBaseInfo (m_stDescription) &&		// Kommentar zum DSN ausgeben
			m_OdbcInfos.OutputTableNames (&m_cbTables))				// mögliche Tabellen ausgeben
		{           
			m_cbTables.EnableWindow (TRUE);							// Tabellen-Selektion ermöglichen                              
			m_cbKoppelFields.ResetContent ();						// alten Feldnamen löschen
			m_cbKoppelFields.EnableWindow (FALSE);					// zuvor Tabelle auswählen
			m_edAliasName.SetWindowText ("");						// Aliasnamen löschen
			m_strDsn = pInfo -> pName;
			m_tType = pInfo -> tType;
		}	
	
		SetStoreButton ();	// Store-Button setzen	
		return TRUE;
	}
	else
		return CDialog::OnCommand(wParam, lParam);
}

void CFreeRelDialog::OnOutputAliasDescription() 
{
	// TODO: Add your control notification handler code here
	m_stDescription.Output (IDS_ALIAS_DESCR);	
}

void CFreeRelDialog::OnOK() 
{
	// TODO: Add extra validation here
	StoreActConnection ();
	CDialog::OnOK();
}

//	alle über ODBC gelesenen Infos löschen 
void CFreeRelDialog :: ResetODBCInfos (void)
{                                         
//	alten Infos löschen
	m_OdbcInfos.DeleteAll ();
	
//	Tabellen-Namen löschen		
	m_cbTables.ResetContent ();
	m_cbTables.EnableWindow (FALSE);
		
//	Koppelfelder löschen		
	m_cbKoppelFields.ResetContent ();
	m_cbKoppelFields.EnableWindow (FALSE);				
		                                      
//	weitere Button rücksetzen
	m_btStoreConnection.EnableWindow (FALSE);	// speichern nicht möglich	                                      

//	Beschreibungsfeld löschen
	m_stDescription.SetWindowText (""); 	
	
//	AliasNamen löschen
	m_edAliasName.SetWindowText ("");	
}   

//	aktuellen Anbindungen speichern 
BOOL CFreeRelDialog :: StoreActConnection (void)
{   
	ErrCode EC = EC_OKAY;			// Operation-Flag
	try
	{
		Profile ProFile(m_hProject);	// Namen der Ini-Datei lesen
	
	//	Aliasname lesen                                        
		CString strAliasName, strTableName;
		m_edAliasName.GetWindowText (strAliasName);
		ASSERT (strAliasName.GetLength () > 0);
		m_cbTables.GetLBText (m_cbTables.GetCurSel (), strTableName);
		
	//	Tabellen-Name ausgeben            
		ASSERT (strTableName.GetLength () > 0);
		if (!ProFile.WriteTableName (strAliasName, strTableName))
			EC = EC_NOWRITE;			
		
	//	Data-Source-Name ausgeben
		if (EC == EC_OKAY)
		{
			ASSERT (m_strDsn.GetLength () > 0);
			ASSERT (UserDataSource == m_tType || SystemDataSource == m_tType ||
					FileDataSource == m_tType);
			if (!ProFile.WriteDataSourceName (strAliasName, m_strDsn, m_tType))
				EC = EC_NOWRITE;			
		}       

		if (EC_OKAY == EC)
		{
			m_strAliasName = strAliasName;
			m_cbKoppelFields.GetLBText (m_cbKoppelFields.GetCurSel (), m_strKoppelField);
		}
	}
	catch (CMemoryException *m)
	{        
		m -> Delete ();
		DEX_Error (RC_StoreActConnCFreeRel, EC_NOMEMORY);
		return FALSE;
	}		
	
//	ggf. Fehlermeldung ausgeben
	if (EC != EC_OKAY)
	{   
		DEX_Error (RC_StoreActConnCFreeRel, EC);
		return FALSE;
	}		 	
	else
	{
		m_bInfosStored = TRUE;						// Info gespeichert
		m_btStoreConnection.EnableWindow (FALSE);   // nicht erneut speichern
		return TRUE;
	}		
}
