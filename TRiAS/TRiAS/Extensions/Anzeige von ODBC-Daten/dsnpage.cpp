// dsnpage.cpp : implementation file
//

#include "pheader.h"
#include "odbcext.hr"				// Resource-Konstanten

#include <hpp/getodbci.hpp>				// GetDataSources ()
#include "database.hpp"				// CDataBaseExt
#include <hpp/waitcur.hpp>				// CWaitCursor
#include <hpp/helptext.hpp>				// CHelpText
#include <tabdlgs.hpp>				// CTabbedDialogs

#include "UserDlg.h"				// CUserDlg
#include "FileDlg.h"				// CFileDsnPage

#include "importpa.hpp"				// CImportParams
#include "dsnpage.hpp"				// zugeh. Header

#include "fakename.h"

extern CImportParams *g_pCParams;
#ifndef WIN32
	extern CPropertySheetExt *g_pSheet;
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDsnPage property page

IMPLEMENT_DYNCREATE(CDsnPage, CPropertyPage)

CDsnPage::CDsnPage() : CPropertyPage(CDsnPage::IDD), m_tbDsn (3)
{
	//{{AFX_DATA_INIT(CDsnPage)
	//}}AFX_DATA_INIT
	m_tDsn = UserDataSource;
}

CDsnPage::~CDsnPage()
{
}

void CDsnPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDsnPage)
	DDX_Control(pDX, IDC_DSN_TAB, m_tbDsn);
	DDX_Control(pDX, IDB_IMP_DEL_NOTEXISTS, m_btDelNotExist);
	DDX_Control(pDX, IDB_IMP_IMP_NOTEXISTS, m_btImpNotExist);
	DDX_Control(pDX, IDL_DSN_TABLE, m_lbTable);
	DDX_Control(pDX, IDB_DSN_ON_TRIAS, m_btTrias);
	DDX_Control(pDX, IDB_DSN_ON_TABLE, m_btTable);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDsnPage, CPropertyPage)
	//{{AFX_MSG_MAP(CDsnPage)
	ON_LBN_SELCHANGE(IDL_DSN_TABLE, OnSelchangeTable)
	ON_BN_CLICKED(IDB_DSN_ON_TABLE, OnButtonOnTable)
	ON_BN_CLICKED(IDB_DSN_ON_TRIAS, OnButtonOnTrias)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDsnPage message handlers

BOOL CDsnPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

// 	TODO: Add extra initialization here
//	ODBC-Data-Sources lesen	
	CWaitCursor wc;
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

//  TRiAS-Namen austauschen
	FakeName(GetDlgItem(IDB_DSN_ON_TRIAS));
	FakeName(GetDlgItem(IDB_DSN_ON_TABLE));

#ifndef WIN32    
	if (!ReadParams ())
	{
		GetParent () -> EndDialog (IDCANCEL);
		return TRUE;
	}
	SetControlState ();
	if (!ModifyButtonsText ())
	{
		GetParent () -> EndDialog (IDCANCEL);
		return TRUE;
	} 
	UpdateWindow ();
	PostMessage (IDM_SETFOCUS, 0, 0L);
#endif
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDsnPage::OnSelchangeTable() 
{
// TODO: Add your control notification handler code here
	int iSel = m_lbTable.GetCurSel ();
	if (iSel < 0)
	{
		m_strTableName.Empty ();
		return;
	}

	TRY
	{
	//	Table-Bschreibung ausgeben
		m_lbTable.GetText (iSel, m_strTableName);
	
		ASSERT (g_pCParams != NULL);
		g_pCParams -> m_strTableName = m_strTableName;
	}
	CATCH (CMemoryException, me)
	{
		DEX_Error (RC_OdbcImport, EC_NOMEMORY);
	}
	END_CATCH

	SetControlState ();	
}

//	Controls akt.
void CDsnPage::SetControlState (void)
{
//	Anpassen-Button setzen
	ASSERT (g_pCParams != NULL);
	if (g_pCParams -> m_COdbcInfos.m_pDataBase != NULL &&
		g_pCParams -> m_COdbcInfos.m_pDataBase -> IsOpen ())
	{
		if (g_pCParams -> m_COdbcInfos.m_pDataBase -> CanUpdate ())
			m_btTable.EnableWindow (TRUE);
		else
		{//	Tabelle kann nicht geändert werden
			m_btTable.EnableWindow (FALSE);		
			m_btTrias.SetCheck (1);
			m_btTable.SetCheck (0);
		}
	}
	
//	Tabelle		
	m_lbTable.EnableWindow (m_lbTable.GetCount () > 0 ? TRUE : FALSE);

//	globales Ok-Button setzen
	if (m_lbTable.GetCurSel () >= 0)
#ifdef WIN32		
		GetParent () -> SetWizardButtons (PSWIZB_NEXT | PSWIZB_BACK);
	else
		GetParent () -> SetWizardButtons (PSWIZB_BACK);
#else 
		g_pSheet -> SetWizardButtons (PSWIZB_NEXT | PSWIZB_BACK);
	else
		g_pSheet -> SetWizardButtons (PSWIZB_BACK);
#endif		
}

void CDsnPage :: ResetOdbcInfos (void)
{
	ASSERT (g_pCParams != NULL);

// 	DataSource-Infos löschen
	m_tDsn = NoDataSource;
	m_strDataSource.Empty ();
	g_pCParams -> m_COdbcInfos.DeleteAll ();	
	g_pCParams -> m_strDataSource.Empty ();
	g_pCParams -> m_tDsn = m_tDsn;

//	TabellenInfos löschen
	m_strTableName.Empty ();
	g_pCParams -> m_strTableName.Empty ();
	m_lbTable.ResetContent ();			
}

// Nutzereingaben lesen
BOOL CDsnPage :: GetUserEntries (BOOL bGet)	
{
	ASSERT (g_pCParams != NULL);

//	Parameter löschen
	g_pCParams -> m_strDataSource.Empty ();
	g_pCParams -> m_tDsn = NoDataSource;
	g_pCParams -> m_strTableName.Empty ();
	if (!bGet)
		return TRUE;		// nur Infos löschen

	TRY
	{
	//	lese Tabellen-Namen
		g_pCParams -> m_strTableName = m_strTableName;

	//	lese DataSourceNamen
		g_pCParams -> m_strDataSource = m_strDataSource;

	//	lese DataSourcetyp
		g_pCParams -> m_tDsn = m_tDsn;
			
	//	lese AktionsFlag
		g_pCParams -> m_bAction = m_btTrias.GetCheck () == 1 ? TRUE : FALSE;

	//	lese Zustand der Button
		if (g_pCParams -> m_bAction)
			g_pCParams -> m_bDelNotExist = m_btDelNotExist.GetCheck () == 1 ? TRUE : FALSE;
		else
			g_pCParams -> m_bDelNotExist = FALSE;		// in Tabelle niemals Datensätze lö.
		g_pCParams -> m_bAddNotExist = m_btImpNotExist.GetCheck () == 1 ? TRUE : FALSE;
	}
	CATCH (CMemoryException, me)
	{
		DEX_Error (RC_OdbcImport, EC_NOMEMORY);
		return FALSE;
	}
	END_CATCH		
	
	return TRUE;	
}

void CDsnPage::OnCancel() 
{
	// TODO: Add your specialized code here and/or call the base class
	GetUserEntries (FALSE);

	CPropertyPage::OnCancel();
}

BOOL CDsnPage::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
#ifdef WIN32	
	if (!ReadParams ())
	{
		GetParent () -> EndDialog (IDCANCEL);
		return FALSE;
	}
	SetControlState ();
	if (!ModifyButtonsText ())
	{
		GetParent () -> EndDialog (IDCANCEL);
		return FALSE;
	}
	UpdateWindow ();
#endif	
	
	return CPropertyPage::OnSetActive();
}

BOOL CDsnPage::ReadParams (void)
{
	ASSERT (g_pCParams != NULL);

	BOOL bRet = FALSE;

	TRY
	{
		CWaitCursor wc;								// Sanduhr einschalten		
		BOOL bIsChanged = (m_strDataSource != g_pCParams -> m_strDataSource) || 
						  (m_tDsn != g_pCParams -> m_tDsn);

	//	hat sich DataSource geändert ?
		if (bIsChanged || (NULL == g_pCParams -> m_COdbcInfos.m_pDataBase))
		{
			m_lbTable.ResetContent ();					// Inhalt der ListBox lö.
			g_pCParams -> m_COdbcInfos.DeleteAll ();	

		//	DataSource ggf. neu lesen
			if (g_pCParams -> m_strDataSource.IsEmpty () || (NoDataSource == g_pCParams -> m_tDsn))
				g_pCParams -> m_strTableName.Empty ();		// Tabelle wird ungültig				
			else
			{				
				if (!g_pCParams -> m_COdbcInfos.CreateDataBase (g_pCParams -> m_strDataSource, g_pCParams -> m_tDsn) ||			// Datsource erzeugen
					!g_pCParams -> m_COdbcInfos.OutputTableNames (&m_lbTable))								// Tabellen ausgeben
				{
					g_pCParams -> m_COdbcInfos.DeleteAll ();	
					g_pCParams -> m_strDataSource.Empty ();
					g_pCParams -> m_tDsn = NoDataSource;
					g_pCParams -> m_strTableName.Empty ();					
				}
			}
		}                    
#ifndef WIN32
		else
			g_pCParams -> m_COdbcInfos.OutputTableNames (&m_lbTable);					
#endif		
	//	DataSourceNamen immer neu speichern
		m_strDataSource = g_pCParams -> m_strDataSource;

	//	Typ speichern
		m_tDsn = g_pCParams -> m_tDsn;

	//	Tabellennamen immer neu speichern
		m_strTableName = g_pCParams -> m_strTableName;

	//	Selektion ändern
		m_lbTable.SelectString (-1, m_strTableName);

	//	Aktions-Button einstellen
		m_btTrias.SetCheck (g_pCParams -> m_bAction);
		m_btTable.SetCheck (!g_pCParams -> m_bAction);

	//	Löschflags und Text einstellen
		m_btDelNotExist.SetCheck (g_pCParams -> m_bDelNotExist);
		m_btImpNotExist.SetCheck (g_pCParams -> m_bAddNotExist);

	//	DSN-Dialogseite akt.
		if (bIsChanged && !m_strDataSource.IsEmpty ())
		{
			switch (g_pCParams -> m_tDsn)
			{
				case UserDataSource:
				{
					VERIFY (m_tbDsn.SetActiveDialog (&m_dlgUserDsn));
					VERIFY (m_dlgUserDsn.SelectDataSource (m_strDataSource));
				}
				break;
				case FileDataSource:
				{
					VERIFY (m_tbDsn.SetActiveDialog (&m_dlgFileDsn));
					VERIFY (m_dlgFileDsn.SelectDataSource (m_strDataSource));
				}
				break;
				case SystemDataSource:
				{
					VERIFY (m_tbDsn.SetActiveDialog (&m_dlgSystemDsn));
					VERIFY (m_dlgSystemDsn.SelectDataSource (m_strDataSource));
				}
				break;
				default:
				{
					m_tbDsn.SetActiveDialog (&m_dlgUserDsn);
					m_dlgUserDsn.SelectDataSource ("");
				}
			}								
		}
		
		bRet = TRUE;
	}
	CATCH (CMemoryException, me)
	{
		DEX_Error (RC_OdbcImport, EC_NOMEMORY);		
	}
	END_CATCH
	
	return bRet;
}

BOOL CDsnPage::ModifyButtonsText (void)
{
	TRY
	{
		CString strArtDel, strArtImp, strText;
		if (m_btTrias.GetCheck () == 1 )
		{
			m_btDelNotExist.ShowWindow (SW_SHOW); 	// löschen wieder möglich
			if (!strArtDel.LoadString (IDS_IMP_TRIAS_OBJEKTE) ||
				!strArtImp.LoadString (IDS_IMP_RECORDS))
				AfxThrowUserException ();
		}
		else
		{ 
		//	Tabelle soll geändert werden
			if (!strArtDel.LoadString (IDS_IMP_RECORDS) ||
				!strArtImp.LoadString (IDS_IMP_TRIAS_OBJEKTE))
				AfxThrowUserException ();
			m_btDelNotExist.ShowWindow (SW_HIDE);
		}

	//	Texte ausgeben		
		AfxFormatString1 (strText, IDS_IMP_DEL_OBEZUG, strArtDel);
		m_btDelNotExist.SetWindowText (strText);
		AfxFormatString1 (strText, IDS_IMP_ZU_IMP, strArtImp);
		m_btImpNotExist.SetWindowText (strText);
	}
	CATCH (CMemoryException, me)
	{
		DEX_Error (RC_OdbcImport, EC_NOMEMORY);		
	}
	AND_CATCH (CUserException, ue)
	{
		DEX_Error (RC_OdbcImport, EC_SYSERROR);		
	}
	END_CATCH

	return TRUE;
}


void CDsnPage::OnButtonOnTable() 
{
	// TODO: Add your control notification handler code here
	ModifyButtonsText ();	
}

void CDsnPage::OnButtonOnTrias() 
{
	// TODO: Add your control notification handler code here
	ModifyButtonsText ();	
}

BOOL CDsnPage::OnKillActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	GetUserEntries (TRUE);
	
	return CPropertyPage::OnKillActive();
}

void CDsnPage::OnDestroy() 
{
	CPropertyPage::OnDestroy();
	
	// TODO: Add your message handler code here
#ifndef WIN32
	GetUserEntries (TRUE);
#endif	
}

#ifndef WIN32
LONG CDsnPage :: OnSetFocusToControl (UINT, LONG)
{
	GotoDlgCtrl (&m_lbDsn);
	return TRUE;		
}
#endif

BOOL CDsnPage::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	try
	{
		if (IDM_CONFIG_DSN == wParam || IDM_SELECT_DSN == wParam)
		{
		//	lese und prüfe Parameter
			DataSourceInfo *pInfo = (DataSourceInfo *)lParam;
			ASSERT (NULL != pInfo);
			ASSERT (NULL != pInfo -> pName && AfxIsValidString (pInfo -> pName));
			ASSERT ((UserDataSource == pInfo->tType) || (SystemDataSource == pInfo-> tType) ||
					 (FileDataSource == pInfo->tType));

			CWaitCursor wc;								// Sanduhr einschalten
			ASSERT (g_pCParams != NULL);
			ResetOdbcInfos ();							// alle Infos löschen

			if (!g_pCParams -> m_COdbcInfos.CreateDataBase (pInfo->pName, pInfo->tType) || 	// Datsource erzeugen
				!g_pCParams -> m_COdbcInfos.OutputTableNames (&m_lbTable))					// Tabellen ausgeben
			{
				g_pCParams -> m_COdbcInfos.DeleteAll ();	
				g_pCParams -> m_strDataSource.Empty ();
				g_pCParams -> m_tDsn = NoDataSource;	
				m_strDataSource.Empty ();
				m_tDsn = NoDataSource;
			}                         
			else
			{
			//	alles speichern
				m_strDataSource = pInfo -> pName;
				m_tDsn = pInfo -> tType;
				g_pCParams -> m_strDataSource = m_strDataSource;
				g_pCParams -> m_tDsn = m_tDsn;
			}

			SetControlState ();					

			return TRUE;
		}
	}
	catch (CMemoryException *m)
	{
		m -> Delete ();
		DEX_Error (RC_OdbcImport, EC_NOMEMORY);
	}
	return CPropertyPage::OnCommand(wParam, lParam);
}

/*
void CDsnPage::OnDsnChange() 
{
// 	TODO: Add your control notification handler code here
	int iSel = m_lbDsn.GetCurSel ();
	if (iSel < 0)
	{
		m_strDataSource.Empty ();
		m_strTableName.Empty ();			
		return;
	}

	m_lbDsn.GetText (iSel, m_strDataSource);
	if (ChangeDataSource (GetParent () -> m_hWnd, m_strDataSource, m_tDsnType))
		ResetOdbcInfos ();
		
	SetControlState ();					
}

void CDsnPage::OnSelchangeDsn() 
{
// 	TODO: Add your control notification handler code here
	int iSel = m_lbDsn.GetCurSel ();
	if (iSel < 0)
	{
		m_strDataSource.Empty ();
		m_strTableName.Empty ();
		return;
	}

	TRY
	{
		CWaitCursor wc;								// Sanduhr einschalten
		m_lbDsn.GetText (iSel, m_strDataSource);	// DSN lesen

		ASSERT (g_pCParams != NULL);

	//	zuerst Tabellen-Infos löschen
		m_strTableName.Empty ();
		g_pCParams -> m_strTableName.Empty ();		// Name
		m_lbTable.ResetContent ();					// Inhalt der ListBox

		if (!g_pCParams -> m_COdbcInfos.CreateDataBase (m_strDataSource, m_tDsnType) ||			// Datsource erzeugen
			!g_pCParams -> m_COdbcInfos.OutputTableNames (&m_lbTable))				// Tabellen ausgeben
		{
			g_pCParams -> m_COdbcInfos.DeleteAll ();	
			g_pCParams -> m_strDataSource.Empty ();
			m_strDataSource.Empty ();
		}                                                                                 
	}
	CATCH (CMemoryException, me)
	{
		DEX_Error (RC_OdbcImport, EC_NOMEMORY);
	}
	END_CATCH

	SetControlState ();							// Controls akt. 
}
*/

