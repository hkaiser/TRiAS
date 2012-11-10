// QueryDlg.cpp : implementation file
//

#include "stdafx.h"		// prec. Header
#include "gak.h"		// CGakApp u. Ressourcen
#include "numedit.h"	// CErzNrEdit
#include "NewQuery.h"	// CNewQueryDef
#include "searchse.h"	// CSearchSet
#include <listext.hpp>	// CListBoxExt
#include "SearRes.h"	// CSearchResult
#include "QueryRes.h"	// CQueryResult
#include "ErzPar.h"		// CErzeugerParam
#include "resultp.h"	// CResultParam
#include "branchep.h"	// CBrancheParam
#include "gebietp.h"	// CGebietParam
#include "AbfallP.h"	// CAbfallParam
#include "QueryPar.h"	// CEnterQueryParam
#include "ImpQuery.h"	// CImportQueryDialog
#include "QueryDlg.h"	// zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Konstanten
const short NamePos = 0;		// Positionen der Spalten in Tabelle
const short TypePos = 1;
const short RetRecPos = 2;
const short ChangePos = 3;
const short SQLStPos = 4;

/////////////////////////////////////////////////////////////////////////////
// CQueryDialog dialog
CQueryDialog::CQueryDialog(CWnd* pParent /*=NULL*/)
			 : CDialog(CQueryDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CQueryDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_bDatenBlatt = TRUE;
}

CQueryDialog::~CQueryDialog(void)
{
	if (m_Database.IsOpen ())
		m_Database.Close ();
}	

void CQueryDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CQueryDialog)
	DDX_Control(pDX, IDB_STANDARD, m_btAbfrageArt);
	DDX_Control(pDX, IDS_INFO, m_stInfo);
	DDX_Control(pDX, IDB_IMPORT, m_btImport);
	DDX_Control(pDX, IDS_SELECT_INFO, m_stSelectInfo);
	DDX_Control(pDX, IDB_DATENBLATT, m_btBlatt);
	DDX_Control(pDX, IDB_QUERY_LISTE, m_btListe);
	DDX_Control(pDX, IDC_QUERIES, m_lcQueries);
	DDX_Control(pDX, IDOK, m_btOk);
	DDX_Control(pDX, IDB_NEU, m_btNew);
	DDX_Control(pDX, IDB_DELETE, m_btDelete);
	DDX_Control(pDX, IDB_AENDERN, m_btChange);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CQueryDialog, CDialog)
	//{{AFX_MSG_MAP(CQueryDialog)
	ON_BN_CLICKED(IDB_AENDERN, OnAendern)
	ON_BN_CLICKED(IDB_DELETE, OnDelete)
	ON_BN_CLICKED(IDB_NEU, OnNeu)
	ON_NOTIFY(NM_CLICK, IDC_QUERIES, OnClickQueries)
	ON_NOTIFY(NM_DBLCLK, IDC_QUERIES, OnDblclkQueries)
	ON_BN_CLICKED(IDB_DATENBLATT, OnDatenblatt)
	ON_BN_CLICKED(IDB_QUERY_LISTE, OnQueryListe)
	ON_BN_CLICKED(IDB_IMPORT, OnImport)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDB_STANDARD, OnStandard)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQueryDialog message handlers

BOOL CQueryDialog::OnInitDialog() // kein TRY/CATCH
{
	CDialog::OnInitDialog();

//	ListControl init.
	CString strName;
	VERIFY (strName.LoadString (IDS_QUERY_NAME));
	if (m_lcQueries.InsertColumn (NamePos, strName) != NamePos)
		AfxThrowResourceException ();
	VERIFY (strName.LoadString (IDS_QUERY_TYPE));
	if (m_lcQueries.InsertColumn (TypePos, strName) != TypePos)
		AfxThrowResourceException ();
	VERIFY (strName.LoadString (IDS_QUERY_RETREC));
	if (m_lcQueries.InsertColumn (RetRecPos, strName) != RetRecPos)
		AfxThrowResourceException ();
	VERIFY (strName.LoadString (IDS_QUERY_AEND));
	if (m_lcQueries.InsertColumn (ChangePos, strName) != ChangePos)
		AfxThrowResourceException ();
	VERIFY (strName.LoadString (IDS_QUERY_SQLST));
	if (m_lcQueries.InsertColumn (SQLStPos, strName) != SQLStPos)
		AfxThrowResourceException ();

//	TODO: Add extra initialization here
	CGakApp *pApp = (CGakApp *) AfxGetApp ();
	ASSERT (NULL != pApp);
	ASSERT_VALID (pApp);
	m_Database.Open (pApp -> DatabaseName ());	

//	Spalten-Breiten setzen
	CRect rc;
	m_lcQueries.GetClientRect (rc);
	m_lcQueries.SetColumnWidth (NamePos, rc.Width () * 2 / 5 );
	m_lcQueries.SetColumnWidth (TypePos, rc.Width () / 5);
	// m_lcQueries.SetColumnWidth (ChangePos, rc.Width () / 10);
	// m_lcQueries.SetColumnWidth (RetRecPos, rc.Width () / 10);
	// m_lcQueries.SetColumnWidth (SQLStPos, rc.Width () * 2 / 5);

	m_lcQueries.SetColumnWidth (ChangePos, LVSCW_AUTOSIZE_USEHEADER);
	m_lcQueries.SetColumnWidth (RetRecPos, LVSCW_AUTOSIZE_USEHEADER);
	m_lcQueries.SetColumnWidth (SQLStPos, LVSCW_AUTOSIZE_USEHEADER);

//	Selektion "beibehalten" setzen
	long lAttr = :: GetWindowLong (m_lcQueries.m_hWnd, GWL_STYLE);
	:: SetWindowLong (m_lcQueries.m_hWnd, GWL_STYLE, lAttr | LVS_SHOWSELALWAYS);

//	Standard-Abfragen setzen
	m_btAbfrageArt.SetCheck (1);
	CString strTemp;
	VERIFY (strTemp.LoadString (IDS_STANDARD_QUEYRIES));
	m_btAbfrageArt.SetWindowText (strTemp);

	ReadQueryDefCollection ();

	SetControlState ();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CQueryDialog::ReadQueryDefCollection (void)
{
	try
	{
		CMutex mt;
		CWaitCursor wc;
	
		ASSERT (m_Database.IsOpen ());

	//	alte Liste löschen
		VERIFY (m_lcQueries.DeleteAllItems ());

	//	Queries ausgeben
		CString strJa, strNein, strType;
		VERIFY (strJa.LoadString (IDS_JA));
		VERIFY (strNein.LoadString (IDS_NEIN));
		int iCnt = m_Database.GetQueryDefCount ();
		CDaoQueryDefInfo Info;
		BOOL bBilanz = m_btAbfrageArt.GetCheck () == 0 ? TRUE : FALSE;
		const char *pBilanz = NULL;
		int iPos = 0;
		for (int iIndex = 0; iIndex < iCnt; iIndex++)
		{
		//	Info lesen
			m_Database.GetQueryDefInfo (iIndex, Info, AFX_DAO_ALL_INFO);	

		//	Standard-Abfrage/Bilanz
			pBilanz = strstr (Info.m_strName, BilanzKennung);
			if (bBilanz)
			{				
				if (!pBilanz || (pBilanz != Info.m_strName))
					continue;
			}
			else		// Standardabfrage
			{
				if (pBilanz && (pBilanz == Info.m_strName))
					continue;
			}

		//	Info ausgeben
			strType = GetQueryType (Info.m_nType);
			if ((m_lcQueries.InsertItem (iPos, Info.m_strName) != iPos) ||
				!m_lcQueries.SetItemText (iPos, TypePos, strType) ||
				!m_lcQueries.SetItemText (iPos, RetRecPos, (dbQSelect == Info.m_nType) ||
															 (dbQSetOperation == Info.m_nType) ? 
															  strJa : strNein) || 
				!m_lcQueries.SetItemText (iPos, ChangePos, Info.m_bUpdatable ? strJa : strNein) ||
				!m_lcQueries.SetItemText (iPos, SQLStPos, Info.m_strSQL))
				AfxThrowMemoryException ();

			iPos++;
		}

	//	Anzahl gefundener ausgeben
		char Buffer [30] = "";
		CString strInfo;
		itoa (m_lcQueries.GetItemCount (), Buffer, 10);
		AfxFormatString1 (strInfo, IDS_QUERY_INFO, Buffer);
		m_stInfo.SetWindowText (strInfo);
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

//	Query-Information zur akt. Selektion
BOOL CQueryDialog::GetQueryInfo (CDaoQueryDefInfo &Info)
{
	try 
	{
		ASSERT (m_Database.IsOpen ());

		int iSel = m_lcQueries.GetNextItem (-1, LVNI_SELECTED);
		if (iSel >= 0)
		{
			CString strQueryName (m_lcQueries.GetItemText (iSel, 0)); 
			m_Database.GetQueryDefInfo (strQueryName, Info, AFX_DAO_ALL_INFO);	
			return TRUE;
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

	return FALSE;
}

//	Controls setzen
void CQueryDialog::SetControlState (void)
{
//	ändern/löschen/ausführen
	try
	{
		int iSel = m_lcQueries.GetNextItem (-1, LVNI_SELECTED);
		if (iSel < 0)
		{
			m_btOk.EnableWindow (FALSE);
			m_btDelete.EnableWindow (FALSE);
			m_btChange.EnableWindow (FALSE);
			m_btListe.EnableWindow (FALSE);
			m_btBlatt.EnableWindow (FALSE);
			m_stSelectInfo.EnableWindow (FALSE);
			m_btListe.SetCheck (0);
			m_btBlatt.SetCheck (1);
			return;
		}
		m_btOk.EnableWindow (TRUE);

	//	Query änderbar ?
		CString strQueryName (m_lcQueries.GetItemText (iSel, 0)); 
		CDaoQueryDefInfo Info;
		m_Database.GetQueryDefInfo (strQueryName, Info, AFX_DAO_ALL_INFO);	

		m_btDelete.EnableWindow (Info.m_bUpdatable);
		m_btChange.EnableWindow (Info.m_bUpdatable);

		if ((dbQSelect == Info.m_nType) ||
		    (dbQSetOperation == Info.m_nType))
		{
			m_btBlatt.EnableWindow (TRUE);
			m_btListe.EnableWindow (TRUE);
			m_stSelectInfo.EnableWindow (TRUE);
		}
		else
		{
			m_btBlatt.EnableWindow (FALSE);
			m_btBlatt.SetCheck (0);
			m_btListe.EnableWindow (FALSE);
			m_stSelectInfo.EnableWindow (FALSE);
			m_btListe.SetCheck (0);
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

void CQueryDialog::OnClickQueries(NMHDR* pNMHDR, LRESULT* pResult) // ok
{
	// TODO: Add your control notification handler code here
	SetControlState ();	
	*pResult = 0;
}

//	Abfrage löschen
void CQueryDialog::OnDelete() 
{
//	TODO: Add your control notification handler code here
	try
	{
		CMutex mt;

	//	Info zur akt. Query abfragen
		CDaoQueryDefInfo Info;
		VERIFY (GetQueryInfo (Info));
		ASSERT (Info.m_bUpdatable);		// muß änderbar sein

	//	beim Nutzer nachfragen
		CString strDelText;
		AfxFormatString1 (strDelText, IDS_DELETE_QUERY, Info.m_strName);
		if (IDYES != MessageBox (strDelText, AfxGetAppName(), MB_ICONQUESTION | MB_YESNO))
			return;

	//	Abfrage löschen
		CWaitCursor wc;
		m_Database.DeleteQueryDef (Info.m_strName);

	//	Collection auffrischen
		DAO_CHECK(m_Database.m_pDAOQueryDefs->Refresh ());

		ReadQueryDefCollection ();						// Collection neu in ListBox ausgeben
		SetControlState ();
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

//	Neue Abfrage hinzufügen
void CQueryDialog::OnNeu() 
{
	try
	{
		CMutex mt;
		CNewQueryDef Dlg (this, &m_Database);
		if (IDOK == Dlg.DoModal ())
		{
			ASSERT (m_Database.IsOpen ());
			CWaitCursor wc;
			CDaoQueryDef NewDef (&m_Database);
			NewDef.Create (Dlg.m_strName, Dlg.m_strSQL);	// neue Abfrage erzeugen

			try
			{
				NewDef.Append ();								// permanent zur Collection
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

		//	Collection auffrischen
			DAO_CHECK(m_Database.m_pDAOQueryDefs->Refresh ());

			ReadQueryDefCollection ();						// Collection neu in ListBox ausgeben
			SelectItem (Dlg.m_strName);						// die neue Abfrage selektieren
			SetControlState ();								// Button akt.
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

void CQueryDialog::OnAendern() 
{
//	TODO: Add your control notification handler code here
	try
	{
		CMutex mt;

	//	Info zur akt. Query abfragen
		CDaoQueryDefInfo Info;
		VERIFY (GetQueryInfo (Info));
		ASSERT (Info.m_bUpdatable);		// muß änderbar sein

	//	Abfrage modifizieren
		CNewQueryDef Dlg (this, &m_Database);
		Dlg.m_strName = Info.m_strName;
		Dlg.m_strSQL = Info.m_strSQL;
		if (IDOK == Dlg.DoModal ())
		{
			CWaitCursor wc;

		//	alte Abfrage löschen
			m_Database.DeleteQueryDef (Info.m_strName);					

		//	neue Abfrage erstellen
			CDaoQueryDef NewDef (&m_Database);				
			NewDef.Create (Dlg.m_strName, Dlg.m_strSQL);	// neue Abfrage erzeugen

			try
			{
				NewDef.Append ();								// permanent zur Collection
			}
			catch (CException *e)
			{
				if (e -> IsKindOf (RUNTIME_CLASS (CDaoException)))
					:: DisplayDaoException ((CDaoException *) e);
				else
					e -> ReportError ();
				e -> Delete ();

			//	alte Abfrage wieder einfügen
				CDaoQueryDef OldQuery (&m_Database);
				OldQuery.Create (Info.m_strName, Info.m_strSQL);
				OldQuery.Append ();
			}
			if (NewDef.IsOpen ())
				NewDef.Close ();

		//	Collection auffrischen
			DAO_CHECK(m_Database.m_pDAOQueryDefs->Refresh ());

			ReadQueryDefCollection ();						// Collection neu in ListBox ausgeben
			SelectItem (Dlg.m_strName);						// die neue Abfrage selektieren
			SetControlState ();								// Button akt.
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

void CQueryDialog::SelectItem (const CString& strFind)
{
	LV_FINDINFO fi;						
	memset (&fi, 0, sizeof (fi));
	fi.flags = LVFI_STRING;		// exakt match
	fi.psz = strFind;

//	suche Item in ListControl		
	int	iItem = m_lcQueries.FindItem (&fi, -1);
	if (iItem >= 0)
	{
		m_lcQueries.EnsureVisible (iItem, FALSE);
		m_lcQueries.SetItemState (iItem, LVIS_SELECTED, LVIS_SELECTED);						
	}
}	

void CQueryDialog::OnOK() 
{
	// TODO: Add extra validation here
	GetQueryInfo (m_QueryInfo);
	DoRecherche (m_QueryInfo);
	// CDialog::OnOK();
}

void CQueryDialog::OnDblclkQueries(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	*pResult = 0;

	GetQueryInfo (m_QueryInfo);
	DoRecherche (m_QueryInfo);
	// EndDialog (IDOK);
}

void CQueryDialog::DoRecherche (const CDaoQueryDefInfo &Info, 
								BOOL bCallExtern /*FALSE*/)
{
	CGakApp *pApp = (CGakApp *) AfxGetApp ();
	ASSERT (NULL != pApp);
	ASSERT_VALID (pApp);
	BOOL &bResDlg = pApp -> m_bResDlg;
	CDaoQueryDef Query (&m_Database);

	try
	{
		ASSERT (m_Database.IsOpen ());

		CMutex mt;
		CString strWait;
		AfxFormatString1 (strWait, IDS_DORECHERCHE, Info.m_strName);

	//	Abfrage erzeugen
		CString strError;
		AfxFormatString1 (strError, IDS_NO_REC_FOUND_QUERY, Info.m_strName);
		Query.Open (Info.m_strName);

		if (m_bDatenBlatt || (!m_bDatenBlatt && bCallExtern))
			GetParameters (Query);
			
		switch (Info.m_nType)		
		{
			case dbQSetOperation:	// Records werden geliefert
			case dbQSelect:
			{
				if (m_bDatenBlatt)
				{
					CDaoRecordset ResSet (&m_Database);
					if (TRUE)
					{
						CWaitCursorExt wcd (strWait, IDS_BEREIT);	// Scope für WaitCursor
						ResSet.Open (&Query, dbOpenSnapshot);
					}
					if (!ResSet.IsBOF ())
					{
						CQueryResult ResDlg (NULL, &ResSet, Info.m_strName);
						ResDlg.DoModal ();
					}
					else
					//	Nutzer informieren
						pApp -> OutputMessage (strError);
						// MessageBox (strError, AfxGetAppName (), MB_OK | MB_ICONINFORMATION);
					ResSet.Close ();
				}
				else	// Listen-Ausgabe
				{
					if (!bCallExtern)
					{
						if (!CheckListenOutput (Info.m_strSQL))	// beim Nutzer nachfragen
							break;

						if (Query.IsOpen ())
							Query.Close ();
						m_bDatenBlatt = FALSE;
						EndDialog (IDOK);		// Recherche extern ausführen
						return;
					}
					CSearchSet Set (&m_Database);
					if (TRUE)
					{
						CWaitCursorExt wc (strWait, IDS_BEREIT); // Scope für WaitCursor
						Set.Open (&Query, dbOpenSnapshot, dbForwardOnly);
					}
					if (!Set.IsBOF ())		// wenn Datensätze vorhanden
					{
						CSearchResult *pResDlg = new CSearchResult (&Set);
						if (pResDlg -> Create (IDD_SEARCH_RESULT))
						{
							pResDlg -> ShowWindow (SW_SHOWNORMAL);
							bResDlg = TRUE;
						}
						else
							DELETE_OBJ (pResDlg);
					}
					else
					//	Nutzer informieren und zurück
						pApp -> OutputMessage (strError);						
						// MessageBox (strError, AfxGetAppName (), MB_OK | MB_ICONINFORMATION);
					Set.Close ();
				}
			}
			break;
			case dbQDelete:		// Datensätze löschen				
			case dbQUpdate:		//			  ändern
			case dbQAppend:		//			  anhängen
			case dbQMakeTable:	// Tabelle erzeugen	
			case dbQDDL:		// DDL-Anweisung 
			case dbQAction:		// Änderung der Daten aber keine Rekords zurück
				Query.Execute (dbFailOnError);		// Rollback bei Fehler
			break;
			case dbQSPTBulk:
			case dbQSQLPassThrough:
			case dbQCrosstab:
			default:
			{
			//	Information an Nutzer ausgeben -> unbekannter/nicht unterstützter Typ
				CString strText;
				VERIFY (strText.LoadString (IDS_UNKN_QUERY));
				MessageBox (strText, AfxGetAppName(), MB_ICONSTOP | MB_OK);
			}
			break;
		}	// end_switch		
	}
	catch (CUserException *e)
	{
		e -> Delete ();		// hier Abbruch !
	}
	catch (CDaoException *e)
	{
		::DisplayDaoException (e);
		e -> Delete ();
	}
	catch (CException *e)
	{
		e -> ReportError ();
		e -> Delete ();
		bResDlg = FALSE;		// Dialog kann wieder gerufen werden
	}		

	if (Query.IsOpen ())
		Query.Close ();
}

//	kein try/catch
void CQueryDialog::GetParameters (CDaoQueryDef &Query)
{
	ASSERT (Query.IsOpen ());

	int iCnt = Query.GetParameterCount();
	if (iCnt <= 0)
		return;

//	Caption bilden
	CQueryParams Params (&Query, this, "");
	Params.SetWizardMode ();
	if (ID_WIZFINISH != Params.DoModal ())
		AfxThrowUserException ();
	
/*
	CDaoParameterInfo Info;
	for (int iIndex = 0; iIndex < iCnt; iIndex++)
	{
		Query.GetParameterInfo (iIndex, Info, AFX_DAO_SECONDARY_INFO);
		CEnterQueryParam Dlg (this);
		Dlg.m_varParamInfo = Info;
		if (IDOK != Dlg.DoModal ())
			AfxThrowUserException ();
		
		Query.SetParamValue (Info.m_strName, Dlg.m_varParamInfo.m_varValue);
	}
*/
}

void CQueryDialog::OnDatenblatt() 
{
	// TODO: Add your control notification handler code here
	m_bDatenBlatt = TRUE;	
}

void CQueryDialog::OnQueryListe() 
{
	// TODO: Add your control notification handler code here
	m_bDatenBlatt = FALSE;	
}

//	Select-Anforderung erfüllt für Listenausgabe ?
BOOL CQueryDialog :: CheckListenOutput (const CString strSQL)
{
	BOOL bListe = FALSE;
	CString strSel;
	VERIFY (strSel.LoadString (IDS_CHECK_SELECT));
	strSel.MakeUpper ();
	if (strstr (strSQL, strSel))
		bListe = TRUE;
	else
	{
		strSel.MakeLower ();
		if (strstr (strSQL, strSel))
			bListe = TRUE;
	}

	if (bListe)
		return TRUE;

//	Beim Nutzer nachfragen
	CString strText;
	VERIFY (strText.LoadString (IDS_NUMMER_QUERY));
	return (MessageBox (strText, AfxGetAppName (), MB_YESNO | MB_ICONQUESTION) == IDYES);
}

void CQueryDialog::OnImport() 
{
	try
	{
		CMutex mt;

	//	Datei-Auswahl-Diolog öffnen
		CString strExt, strFilter, strCaption;
		VERIFY (strExt.LoadString (IDS_DATABASE_EXTENSION));
		VERIFY (strFilter.LoadString (IDS_MDB_FILTER));
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

	//	Source und Destination müssen verschieden sein
		if (0 == m_Database.GetName ().CompareNoCase (Dlg.GetPathName ()))
		{
			((CGakApp *) AfxGetApp ()) -> OutputMessage (IDS_DIFF_IN_OUT_DB); 
			AfxThrowUserException ();
		}

		CWaitCursor wc;
		CDaoDatabase SourceDatabase;
		CString strDriver;
		SourceDatabase.Open (Dlg.GetPathName (),	
							 FALSE,	/* nicht exclusiv */
							 TRUE);	/* read only */

		CImportQueryDialog Import (this, &SourceDatabase, &m_Database); 	
		if (IDOK == Import.DoModal ())
		{
			ReadQueryDefCollection ();	// Collection neu in ListBox ausgeben
			SetControlState ();			// Controlstate neu setzen					
		}

		if (SourceDatabase.IsOpen ())
			SourceDatabase.Close ();
	}
	catch (CUserException *ue)
	{
		ue -> Delete ();		// hier nur Abbruch
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

BOOL CQueryDialog::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	// TODO: Add your message handler code here and/or call default
	// return CDialog::OnHelpInfo(pHelpInfo);
	ASSERT (pHelpInfo != NULL);

	if (pHelpInfo -> dwContextId)
		WinHelp (pHelpInfo -> dwContextId, HELP_CONTEXTPOPUP);

	return TRUE;
}

void CQueryDialog::OnStandard() 
{
	CString strTemp;
	VERIFY (strTemp.LoadString (m_btAbfrageArt.GetCheck () == 1 ?
								IDS_STANDARD_QUEYRIES : IDS_BILANZ_QUERIES));
	m_btAbfrageArt.SetWindowText (strTemp);

	ReadQueryDefCollection ();
}

