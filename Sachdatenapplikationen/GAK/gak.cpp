// gak.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"			// vor. Header

#include "gak.h"			// zug. Header
#include "numedit.h"		// CErzNrEdit
#include "statbare.h"		// CStatusBarExt
#include "MainFrm.h"		// CMainFrame
#include "ChildFrm.h"		// CChildFrame
#include "erzframe.h"		// CErzFrame
#include "abfframe.h"		// CAbfFrame
#include "gaksete.h"		// CDaoRecordsetExt
#include "gakSet.h"			// CGakSet
#include "documext.h"		// CDocumentExt
#include "gakDoc.h"			// CGakDoc
#include "abfset.h"			// CAbfSet	
#include "abfdoc.h"			// CGAbfDoc
#include "recview.h"		// CDaoRecordViewExt
#include "gakView.h"		// CGakView
#include "abfview.h"		// CAbfView
#include "userinfo.h"		// CUserNameDlg	
#include "enternr.h"		// CEnterNr
#include "searchse.h"		// CSearchSet
#include <listext.hpp>		// CListBoxExt
#include "searRes.h"		// CResultDialog
#include "about.h"			// About-Dialog
#include "compact.h"		// CCompactDatabase
#include "QueryDlg.h"		// CQueryDialog
#include "getodbci.h"		// ChangeDSN ...	

// abgleich includes
//#include "res.h"			//	Resourcen

#include "odbcinst.h"
//#include "mainfrm.h"
//#include "bgsabdoc.h"
//#include "bgsabvw.h"                    
#include "editext.h"		//	CEditExt
//#include "numedit.h"		//	CNumEdit
#include "params.h"			// 	CParameters
#include "resdlg.h"			//  CResultDiaolog
//#include "listext.h"		//	CListBoxExt
#include "doabglei.h"		// 	CDoAbgleich
#include "getodbci.hpp"		//	lese ODBC-Infos
#include "SelTable.h"		//	CSelTable
#include "recset.h"			//	CRecordsetExt
#include "erzliste.h"		// 	CErzListeSet
// #include "bgsabgl.h"		//	zugeh. Header

// Crystal-Reports-Header
#include "peplus.h"
#include "crpe.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//	Konstanten
const long lItemNotFound = 3265;
const long lFileNotFound = 3024;

//	globale Variablen
CRPEngine CrEngine (TRUE);

//	externe Variablen
extern CGakSet *g_pErzSet;
extern CAbfSet *g_pAbfSet;
//	externe Variablen
extern pFieldInfo pErzListeTable;


// globale Funktionen -----------------------------------------------------------
// Nachzeichnen des Parent-Windows
void CallMessageQueue (void)
{                         
	MSG msg;
	while (:: PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
	{
    	if (msg.message == WM_QUIT)
    		return;

		:: TranslateMessage(&msg);
		:: DispatchMessage(&msg);
	}
}	                            


////////////////////////////////////
// CAbgleichParameter

CAbgleichParameter::CAbgleichParameter(		
						const CString& strLastErzeuger,
						const CString& strLastAsn,
						const CString& strAbfallTable,
						const CString& strErzTable,
						const BOOL bOnlyThisErzeuger,
						const BOOL bLockTables)

{
	m_strLastErzeuger = strLastErzeuger;
	m_strLastAsn = strLastAsn;
	m_strAbfallTable = strAbfallTable;
	m_strErzTable = strErzTable;
	m_bOnlyThisErzeuger = bOnlyThisErzeuger;
	m_bLockTables = bLockTables;
}

void CAbgleichParameter::ModifyParameters(CParameters* params)
{
	// Input checken
	if (NULL == params)
		return;

	params->m_strLastErzeuger = m_strLastErzeuger;
	params->m_strLastAsn = m_strLastAsn;
	params->m_strAbfallTable = m_strAbfallTable;
	params->m_strErzeugerTable = m_strErzTable;
	params->m_bOnlyThisErzeuger = m_bOnlyThisErzeuger;
	params->m_bLockAbfaelleSelection = m_bLockTables;
	params->m_bLockErzeugerSelection = m_bLockTables;
}

/////////////////////////////////////////////////////////////////////////////
// CGakApp

BEGIN_MESSAGE_MAP(CGakApp, CWinApp)
	//{{AFX_MSG_MAP(CGakApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(IDM_LOOK_NR, OnLookNr)
	ON_UPDATE_COMMAND_UI(IDM_LOOK_NR, OnUpdateLookNr)
	ON_COMMAND(IDM_COMPACT_DATABASE, OnCompactDatabase)
	ON_COMMAND(IDM_REPAIR_DATABASE, OnRepairDatabase)
	ON_COMMAND(IDM_RECHERCHE, OnRecherche)
	ON_UPDATE_COMMAND_UI(IDM_RECHERCHE, OnUpdateRecherche)
	ON_COMMAND(IDM_NEW_ABGLEICH, OnAbgleich)
	ON_COMMAND(IDM_DRUCK_ERZLISTE, OnDruckErzliste)
	ON_COMMAND(IDM_LAST_ABGLEICH, OnLastAbgleich)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(IDB_ABGLEICH, OnAbgleich)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(IDM_STAMMDATEN, OnCreateStammdaten)
	ON_COMMAND(IDM_ABFALL, OnCreateAbfaelle)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGakApp construction

CGakApp::CGakApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	m_pErzTemplate = NULL;
	m_pAbfTemplate = NULL;

	// BGsAbgl member
	m_pdbMDB = NULL;
	m_pdbFoxPro = NULL;
	m_pParamDlg = NULL;
	m_pAbgleichDlg = NULL;
	m_pResDlg = NULL;
	m_bError = FALSE;
}

CGakApp::~CGakApp()
{
	// BGsAbgl member
	DeleteAllDatas();
}
/////////////////////////////////////////////////////////////////////////////
// The one and only CGakApp object

CGakApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CGakApp initialization

BOOL CGakApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	LoadStdProfileSettings(0);  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

//	NutzerNamen eingeben
	try
	{
		m_bResDlg = FALSE;		// kein Ergebnisdialog vorh.		

	//	Parse command line for standard shell commands, DDE, file open
	//	lese Gemeinde-Nummer		
		CCommandLineInfo cmdInfo;
		ParseCommandLine(cmdInfo);
		cmdInfo.m_strFileName.Empty ();

		if (cmdInfo.m_strFileName.IsEmpty ())
		{
			CUserInfoDlg Dlg;
			if (Dlg.DoModal () == IDOK)
				m_strUserName = Dlg.m_strUserName;
			else
				return FALSE;
		}
		else
			VERIFY (m_strUserName.LoadString (AFX_IDS_APP_TITLE));

	//	lese Datenbasisname
		CString strSection, strEntry;
		VERIFY (strSection.LoadString (IDS_CONFIG_SECTION));
		VERIFY (strEntry.LoadString (IDS_DATEN_ENTRY));
		m_strDatabaseName = GetProfileString (strSection, strEntry);

	//	wenn Eintrag nicht gefunden, Standard verwenden
		if (m_strDatabaseName.IsEmpty ())
			VERIFY (m_strDatabaseName.LoadString (IDS_DATABASE_NAME));

		ReadTablesFromIni ();

		if (!CheckAllTables ())
			return FALSE;

	//	Erzeuger
		m_pErzTemplate = new CMultiDocTemplate(
			IDR_GAKTYPE,
			RUNTIME_CLASS(CGakDoc),
			RUNTIME_CLASS(CErzFrame), 
			RUNTIME_CLASS(CGakView));
		AddDocTemplate(m_pErzTemplate);

	//	Abfälle
		m_pAbfTemplate = new CMultiDocTemplate(
			IDR_GAKTYPE,
			RUNTIME_CLASS(CAbfDoc),
			RUNTIME_CLASS(CAbfFrame), 
			RUNTIME_CLASS(CAbfView));
		AddDocTemplate(m_pAbfTemplate);

		// create main MDI Frame window
		CMainFrame* pMainFrame = new CMainFrame;
		if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
			return FALSE;
		m_pMainWnd = pMainFrame;

	//	Check ODBC-Anbindung
		CheckOdbcConnection (TRUE);
		
	/*
		// Dispatch commands specified on the command line
		if (!ProcessShellCommand(cmdInfo))
			return FALSE;
	*/
	//	The main window has been initialized, so show and update it.
		//	lese SizeOrg
		/*
		VERIFY (strEntry.LoadString (IDS_SIZEORG));			
		CString strSize = GetProfileString (strSection, strEntry);
		BOOL bWasSized = FALSE;
		if (!strSize.IsEmpty ())
		{
		//	Size berechnen
			int iLeft, iTop, iWidth, iHeight;
			iLeft = iTop = iWidth = iHeight = 0;
			CString strSizeFormat;
			VERIFY (strSizeFormat.LoadString (IDS_SIZEORG_FORMAT));
			if (4 == sscanf (strSize, strSizeFormat, &iLeft, &iTop, &iWidth, &iHeight))
			{
				pMainFrame->MoveWindow (iLeft, iTop, iWidth, iHeight, FALSE);
				bWasSized = TRUE;
			}				                        
		}	
		*/		    
		// pMainFrame->ShowWindow (bWasSized ? SW_NORMAL : SW_SHOWMAXIMIZED);
		pMainFrame->ShowWindow (SW_SHOWMAXIMIZED);
		pMainFrame->UpdateWindow ();	

		pMainFrame->UpdateWindow();

	//	suche Gemeindenummern
		LookGKZ (cmdInfo.m_strFileName);
		
		return TRUE;
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

//	CGakApp -------------------------------------------------------------------------
//	allg. Funktionen
//
//	Information an Nutzer ausgeben: eigentliche Ausgabe
void CGakApp::OutputMessage (const char *pText)
{
	ASSERT (pText != NULL && AfxIsValidString (pText));

	:: MessageBeep (MB_OK);
	:: MessageBox (m_pMainWnd -> m_hWnd, pText, m_pszAppName, MB_ICONINFORMATION);
}

//	Information an Nutzer ausgeben
void CGakApp::OutputMessage (int iCode)
{
	CString strText;
	if (!strText.LoadString (iCode))
		AfxThrowResourceException ();

	OutputMessage (strText);
}

/////////////////////////////////////////////////////////////////////////////
//	CGakApp commands
//	About
void CGakApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

//	hier als Notvariante zum Suchen von Erzeugern über die GKZ
void CGakApp :: LookGKZ (const CString &strGKZ)
{
	try
	{
		if (strGKZ.IsEmpty ())
			return;

		CMutex mt; 
		CWaitCursor wc;
		CString strWhere;
		AfxFormatString1 (strWhere, IDS_WHERE_GKZ, strGKZ);
		CSearchSet Set (strWhere);
		Set.Open (dbOpenSnapshot, NULL, dbForwardOnly);
		if (!Set.IsBOF ())		// wenn Datensätze vorhanden
		{
			CSearchResult *pResDlg = new CSearchResult (&Set);
			if (pResDlg -> Create (IDD_SEARCH_RESULT))
			{
				pResDlg -> ShowWindow (SW_SHOWNORMAL);
				m_bResDlg = TRUE;
			}
			else
				DELETE_OBJ (pResDlg);
		}
		else	// wenn keine Sätze vorhanden,
		//	Nutzer informieren und zurück
			OutputMessage (IDS_NO_REC_FOUND);
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

//	Datensätze suchen
void CGakApp :: OnLookNr()
{
	try
	{
		CMutex mt; 
		CWaitCursorExt wc (IDS_LOOK_ERZEUGER);

	//	keine weitere Finds
		if (m_bResDlg)			
			return; 

	//	Nummber eingeben
		CEnterNr dlg;
		if (dlg.DoModal () != IDOK)
			return;

	//	Set bilden
		wc.Restore ();
		CSearchSet Set (dlg.m_strExpression);
		Set.Open (dbOpenSnapshot, NULL, dbForwardOnly);
		if (!Set.IsBOF ())		// wenn Datensätze vorhanden
		{
			CSearchResult *pResDlg = new CSearchResult (&Set);
			if (pResDlg -> Create (IDD_SEARCH_RESULT))
			{
				pResDlg -> ShowWindow (SW_SHOWNORMAL);
				m_bResDlg = TRUE;
			}
			else
				DELETE_OBJ (pResDlg);
		}
		else	// wenn keine Sätze vorhanden,
		//	Nutzer informieren und zurück
			OutputMessage (IDS_NO_REC_FOUND);
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

void CGakApp::OnUpdateLookNr(CCmdUI* pCmdUI) 
{
// TODO: Add your command update UI handler code here
	pCmdUI -> Enable (FALSE == m_bResDlg);
}

void CGakApp :: OnCreateStammdaten () 
{
	CreateStammdaten (NULL, TRUE);
}

void CGakApp:: OnCreateAbfaelle ()
{
	CreateAbfaelle (NULL, TRUE);
}

void CGakApp::CreateStammdaten (const char *pInNummer, BOOL bSetFocus)
{
	const char *pNummer = pInNummer ? pInNummer : NULL;

	if (!pNummer)
	{
		if (g_pAbfSet && g_pAbfSet -> IsOpen () && !g_pAbfSet -> m_Nummer.IsEmpty ())
			pNummer = g_pAbfSet -> m_Nummer;
	}
	// Create SiKo of NummerString
	CString strNummer;
	if (NULL != pNummer) 
		strNummer = pNummer;
	m_pErzView = (CGakView*) CreateDaten (m_pErzTemplate, pNummer, bSetFocus);
}

void CGakApp::CreateAbfaelle (const char *pInNummer, BOOL bSetFocus)
{
	const char *pNummer = pInNummer ? pInNummer : NULL;

	if (!pNummer)
	{
		if (g_pErzSet && g_pErzSet -> IsOpen () && !g_pErzSet -> m_Nummer.IsEmpty ())
			pNummer = g_pErzSet -> m_Nummer;
	}

	m_pAbfView = (CAbfView*) CreateDaten (m_pAbfTemplate, pNummer, bSetFocus);
}

CView* CGakApp::CreateDaten (CMultiDocTemplate *pDocTemp, const char *pNummer, BOOL bSetFocus)
{
//	prüfe interne Variablen
	ASSERT (NULL != pDocTemp);
	ASSERT_VALID (pDocTemp);


//  SiKo von der eingabe machen
	CString strNummer;
	if (NULL != pNummer)
		strNummer = pNummer;

//	lokale Variablen init.
	CDocument *pDoc = NULL;
	CDaoRecordViewExt* pView = NULL;
	CMDIChildWnd *pFrame = NULL;
	BOOL bOutputTitle = FALSE;
	POSITION pos;

	CWaitCursor wc;		// Sanduhr einschalten

//	ggf. Dokument erzeugen
	pos = pDocTemp -> GetFirstDocPosition ();
	if (NULL == pos)
	{
		pDoc = pDocTemp -> OpenDocumentFile (NULL);
		bOutputTitle = TRUE;
	}
	else					// Dokument war vorhanden
		pDoc = pDocTemp -> GetNextDoc (pos);		
	ASSERT (NULL != pDoc);		//	prüfe erhaltenes Dokument
	ASSERT_VALID (pDoc);

//	ggf. Überschrift akt.
	if (bOutputTitle)
		pDoc -> SetTitle ("");

//	jetzt zugeh. View holen
	pos = pDoc -> GetFirstViewPosition();
	ASSERT (NULL != pos);
	pView = (CDaoRecordViewExt* ) pDoc -> GetNextView (pos);
	ASSERT (NULL != pView);		//	prüfe erhaltene View
	ASSERT_VALID (pView);

//	dann Frame lesen
	pFrame = (CMDIChildWnd *) pView -> GetParentFrame ();
	ASSERT (NULL != pFrame);	//	prüfe erhaltenen Frame	
	ASSERT_VALID (pFrame);

//	ggf. Erzeugernummer suchen
	if (!strNummer.IsEmpty())
//	if (pNummer && *pNummer)	// JG pNummer will by changed while processing
		pView -> SearchNummer (strNummer);

//	ggf. Fenster aktivieren
	if (bSetFocus)
		pFrame -> ActivateFrame ();

	return pView;
}

//	Datenbank komprimieren
void CGakApp::OnCompactDatabase () 
{
	// TODO: Add your command handler code here
	try
	{
		CCompactDataBase Dlg (m_pMainWnd, m_strDatabaseName);
		Dlg.DoModal ();
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

//	neuen Datenbasis-Namen setzen
void CGakApp::SetNewDatabase (const char *pName)
{
	ASSERT (pName != NULL && AfxIsValidString (pName));
	
	try
	{
	//	prüfe alten und neuen Namen
		if (0 == m_strDatabaseName.CompareNoCase (pName))
			return;

	//	schreibe Datenbasisname
		CString strSection, strEntry;
		if (!strSection.LoadString (IDS_CONFIG_SECTION) ||
			!strEntry.LoadString (IDS_DATEN_ENTRY))
			AfxThrowResourceException ();

		if (!WriteProfileString (strSection, strEntry, pName))
			AfxThrowFileException (CFileException::diskFull);

	//	ODBC-Datenquelle ändern
		if (!WriteOdbcPath (pName))
			CheckOdbcConnection (TRUE);
			
		m_strDatabaseName = pName;
	}
	catch (CException *e)
	{
		e -> ReportError ();
		e -> Delete ();
	}
}	

// akktuelle DB reparieren
void CGakApp::OnRepairDatabase() 
{
//  TODO: Add your command handler code here
	ASSERT (!m_strDatabaseName.IsEmpty ());

	CWaitCursorExt wc (IDS_REPAIR_DATABASE);
	CDaoWorkspace Space;
	try
	{
		Space.Open ();				// Open default Workspace
		
	//	Komprimierung durchführen --> keine Transaktion möglich !!!
		Space.RepairDatabase (m_strDatabaseName);
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

	if (Space.IsOpen ())
		Space.Close ();
}

void CGakApp::OnRecherche() 
{
	try
	{
		CMutex mt;		
		CQueryDialog Dlg (m_pMainWnd);
		if (IDOK == Dlg.DoModal ())
			Dlg.DoRecherche (Dlg.m_QueryInfo, TRUE);
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

void CGakApp::OnUpdateRecherche(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI -> Enable (FALSE == m_bResDlg);	
}

void CGakApp::OutputBarMessage(const char *pText)
{
	ASSERT (NULL != pText && AfxIsValidString (pText));
	ASSERT (NULL != m_pMainWnd);
	MessageBeep (MB_OK);
	((CMainFrame *) m_pMainWnd) -> SetStatusBarText (pText, FALSE);
	CallMessageQueue ();
}

//	existieren alle Tabellen
BOOL CGakApp::CheckAllTables (void)
{
	CDaoDatabase db;
	CString strTable;
	BOOL bOk = FALSE;
	try
	{
	//	prüfe zuerst Datenbank vorh. ?
		strTable = m_strDatabaseName;
		db.Open (strTable);
		
	//	prüfe alle Hintergrund- und Eingabetabellen
		CDaoTableDefInfo Info;
		strTable = m_strGemeindenTable;
		db.GetTableDefInfo (strTable, Info);
		strTable = m_strBranchenTable;
		db.GetTableDefInfo (strTable, Info);
		strTable = m_strAbfallArtenTable;
		db.GetTableDefInfo (strTable, Info);
		strTable = m_strEntsorgerTable;
		db.GetTableDefInfo (strTable, Info);
		strTable = m_strTransporteureTable;
		db.GetTableDefInfo (strTable, Info);
		strTable = m_strErzTable;
		db.GetTableDefInfo (strTable, Info);
		strTable = m_strAbfallTable;
		db.GetTableDefInfo (strTable, Info);
		strTable = m_strVerbringungsTable;
		db.GetTableDefInfo (strTable, Info);
		strTable = m_strKreisTable;
		db.GetTableDefInfo (strTable, Info);
		strTable = m_strVerfahrenTable;
		db.GetTableDefInfo (strTable, Info);
		bOk = TRUE;
	}
	catch (CDaoException *de)
	{
		if ((lItemNotFound == de -> m_pErrorInfo -> m_lErrorCode) ||
			(lFileNotFound == de -> m_pErrorInfo -> m_lErrorCode))
		{
			CString strErr;
			AfxFormatString1 (strErr, IDS_TABLE_NOT_FOUND, strTable);

			:: MessageBeep (MB_OK);
			:: MessageBox (NULL, strErr, AfxGetAppName (), MB_ICONSTOP);
		}
		else 
			de -> ReportError ();

		de -> Delete ();
	}
	catch (CException *e)
	{
		e -> ReportError ();
		e -> Delete ();
	}

	if (db.IsOpen ())
		db.Close ();

	return bOk;
}

// alle Tabellennamen aus Ini-Datei lesen
void CGakApp :: ReadTablesFromIni (void)
{
	try
	{
		CString strSection, strEntry;
		VERIFY (strSection.LoadString (IDS_CONFIG_SECTION));

	//	lese Namen der Verbringungskodetabelle
		VERIFY (strEntry.LoadString (IDS_VERBR_TABLE_ENTRY));
		m_strVerbringungsTable = GetProfileString(strSection, strEntry);
		if (m_strVerbringungsTable.IsEmpty ())
			VERIFY (m_strVerbringungsTable.LoadString (IDS_VERBR_TABLE_NAME));

	//	lese Namen der Verfahrentabelle
		VERIFY (strEntry.LoadString (IDS_VERFAHREN_TABLE_ENTRY));
		m_strVerfahrenTable = GetProfileString (strSection, strEntry);
		if (m_strVerfahrenTable.IsEmpty ())
			VERIFY (m_strVerfahrenTable.LoadString (IDS_VERFAHREN_TABLE_NAME));

	//	lese Namen der Kreistabelle
		VERIFY (strEntry.LoadString (IDS_KREISE_TABLE_ENTRY));
		m_strKreisTable = GetProfileString (strSection, strEntry);
		if (m_strKreisTable.IsEmpty ())
			VERIFY (m_strKreisTable.LoadString (IDS_KREISE_TABLE_NAME));

	//	lese Name der akt. Abfalltabelle
		VERIFY (strEntry.LoadString (IDS_ABF_TABLE_ENTRY));
		m_strAbfallTable = GetProfileString (strSection, strEntry);

	//	wenn Eintrag nicht gefunden, Standard verwenden
		if (m_strAbfallTable.IsEmpty ())
			VERIFY (m_strAbfallTable.LoadString (IDS_ABF_TABLE_NAME));

	//	lese Name der akt. Erzeugertabelle
		VERIFY (strEntry.LoadString (IDS_ERZ_TABLE_ENTRY));
		m_strErzTable = GetProfileString (strSection, strEntry);

	//	wenn Eintrag nicht gefunden, Standard verwenden
		if (m_strErzTable.IsEmpty ())
			VERIFY (m_strErzTable.LoadString (IDS_ERZ_TABLE_NAME));

	//	lese Namen der Hintergrundtabellen, wenn nicht gefunden, immer Standard verwenden
		VERIFY (strEntry.LoadString (IDS_GEM_TABLE_ENTRY));	// Gemeinden
		m_strGemeindenTable = GetProfileString (strSection, strEntry);
		if (m_strGemeindenTable.IsEmpty ())
			VERIFY (m_strGemeindenTable.LoadString (IDS_GEM_TABLE_NAME));

	//	Branchen
		VERIFY (strEntry.LoadString (IDS_BR_TABLE_ENTRY));	
		m_strBranchenTable = GetProfileString (strSection, strEntry);
		if (m_strBranchenTable.IsEmpty ())
			VERIFY (m_strBranchenTable.LoadString (IDS_BR_TABLE_NAME));	

	//	Abfallarten
		VERIFY (strEntry.LoadString (IDS_ABFART_TABLE_ENTRY));	
		m_strAbfallArtenTable = GetProfileString (strSection, strEntry);
		if (m_strAbfallArtenTable.IsEmpty ())
			VERIFY (m_strAbfallArtenTable.LoadString (IDS_ABFART_TABLE_NAME));																				

	//	Transporteure
		VERIFY (strEntry.LoadString (IDS_TRANSP_TABLE_ENTRY));	
		m_strTransporteureTable = GetProfileString (strSection, strEntry);
		if (m_strTransporteureTable.IsEmpty ())
			VERIFY (m_strTransporteureTable.LoadString (IDS_TR_TABLE_NAME));

	//	Entsorger
		VERIFY (strEntry.LoadString (IDS_ENTS_TABLE_ENTRY));	
		m_strEntsorgerTable = GetProfileString (strSection, strEntry);
		if (m_strEntsorgerTable.IsEmpty ())
			VERIFY (m_strEntsorgerTable.LoadString (IDS_ENTS_TABLE_NAME));
	}
	catch (CException *e)
	{
		e -> ReportError ();
		e -> Delete ();
	}
}

//	Nur gültige Entsorger ?
BOOL CGakApp :: OnlyValidEntsorger (void)
{
	CString strSection, strEntry;
	VERIFY (strSection.LoadString (IDS_CONFIG_SECTION));
	VERIFY (strEntry.LoadString (IDS_CONFIG_ONLY_VALID_ENTS));
	return GetProfileInt (strSection, strEntry, 1) == 1 ? TRUE : FALSE;	
}

// Nur gültige Transporteure ?
BOOL CGakApp :: OnlyValidTransporteure (void)
{
	CString strSection, strEntry;
	VERIFY (strSection.LoadString (IDS_CONFIG_SECTION));
	VERIFY (strEntry.LoadString (IDS_CONFIG_ONLY_VALID_TRANS));
	return GetProfileInt (strSection, strEntry, 1) == 1 ? TRUE : FALSE;
}

//	Hintergrund oder Eingabe-Tabelle in Verwendung
BOOL CGakApp :: TableInUse (const CString &strTableName)
{
	if (strTableName.IsEmpty ())
		return FALSE;

	if ((m_strGemeindenTable.CompareNoCase (strTableName) == 0) ||
		(m_strBranchenTable.CompareNoCase (strTableName) == 0) ||
		(m_strAbfallArtenTable.CompareNoCase (strTableName) == 0) ||
		(m_strEntsorgerTable.CompareNoCase (strTableName) == 0) ||
		(m_strTransporteureTable.CompareNoCase (strTableName) == 0) ||
		(m_strErzTable.CompareNoCase (strTableName) == 0) ||
		(m_strVerbringungsTable.CompareNoCase (strTableName) == 0) ||
		(m_strKreisTable.CompareNoCase (strTableName) == 0) ||
		(m_strAbfallTable.CompareNoCase (strTableName) == 0) ||
		(m_strVerfahrenTable.CompareNoCase (strTableName) == 0))
		return TRUE;

	return FALSE;
}

//	allgemeine Druckfunktion
CRPEJob *CGakApp :: Print (const char *pReportFile, const char *pTitle/*=NULL*/, 
						   const char *pSubst/*=NULL*/, BOOL btoWindow /*= TRUE*/ , CWnd* pWnd/* = NULL*/)
{
//	prüfe Parameter
	ASSERT ((NULL != pReportFile) && AfxIsValidString (pReportFile));

	if (CRPEngine :: engineOpen != CrEngine.GetEngineStatus())
	{
		CString strError;
		VERIFY (strError.LoadString (IDS_NO_PRINT_ENGINE));
		OutputMessage (strError);
		return NULL;
	}
	
	CRPEJob *pJob = NULL;
	
	try
	{
		CWaitCursor wc;

		CString strReportFile;
		AfxFormatString1 (strReportFile, IDS_REPORT_FFORMAT, pReportFile);
		pJob =	CrEngine.OpenJob (strReportFile);	// muß im Exe-Pfad stehen
		if (NULL == pJob)
			AfxThrowUserException ();
		
	//	ggf. Substitution durchführen
		if (pSubst && *pSubst)
		{
			CString strOldSQL, strNewSQL;

		//	alten SQL-String lesen
			if (!pJob -> GetSQLQuery (strOldSQL))
				AfxThrowUserException ();
			
			int iPos = strOldSQL.Find ('$');
			if (iPos >= 0)
				strNewSQL = strOldSQL.Left (iPos) + pSubst + 
							strOldSQL.Right (strOldSQL.GetLength () - iPos - 1);
			else
				strNewSQL = strOldSQL;

		//	neuen SQL-String setzen
			if (!pJob -> SetSQLQuery (strNewSQL))
				AfxThrowUserException ();
		}
		
	//	Drucken des Jobs
		CRect rc;
		if (pWnd)
		{
			m_pMainWnd -> GetWindowRect(&rc);
		}
		else
		{
			ASSERT (NULL != m_pMainWnd);
			m_pMainWnd -> GetWindowRect (&rc);
		}
	//	Ausgabe vorbereiten
		if (btoWindow)		//	ins Fenster
		{
			if (!pJob -> OutputToWindow (pTitle, rc.left, rc.top, rc.Width (), rc.Height (),
										 WS_POPUPWINDOW | WS_EX_TOPMOST, NULL))
				AfxThrowUserException ();
		}
		else
		{
		//	auf den Drucker
			if (pTitle && *pTitle)
			{
				if (!pJob -> SetReportTitle (pTitle))
					AfxThrowUserException ();
			}
			
		//	Voreinstellungen
			CRPEPrintOptions printOpt;
			CPrintDialog printDlg(FALSE, PD_ALLPAGES | PD_USEDEVMODECOPIES
								| PD_HIDEPRINTTOFILE | PD_NOSELECTION, 
								this->m_pMainWnd);
			printDlg.m_pd.nMaxPage = 0xFFFF;
			printDlg.m_pd.nMinPage = 1;
			printDlg.m_pd.nFromPage = 1;
			printDlg.m_pd.nToPage = 0xFFFF;
			if(printDlg.DoModal() == IDCANCEL)
			{
				if (pJob)
					pJob -> Close ();
				return NULL;
			}
	
		//	Bereich lesen
			if( printDlg.PrintRange() ) 
			{
				printOpt.m_startPageN = (unsigned short)printDlg.GetFromPage();
				printOpt.m_stopPageN = (unsigned short)printDlg.GetToPage();
			}
			printOpt.m_nReportCopies = (unsigned short)printDlg.GetCopies();
			pJob -> SetPrintOptions( &printOpt );
			if (!pJob -> OutputToPrinter( (short)printOpt.m_nReportCopies))
				AfxThrowUserException ();
		}		

	//	Ausgabe durchführen
		if (!pJob -> Start ())
			AfxThrowUserException ();
	}
	catch (CUserException *ue)
	{
		if (pJob)
			pJob -> Close ();
		pJob = NULL;

		ue -> Delete ();

	//	Meldung zusammenbauen
		CString strErr;
		char Buffer10 [10] = "";
		if (pJob)
		{
			itoa (pJob -> GetErrorCode(), Buffer10, 10);
			strErr = Buffer10;
			strErr += ": ";
			strErr += pJob -> GetErrorText ();
		}
		else
		{
			itoa (CrEngine.GetErrorCode (), Buffer10, 10);
			strErr = Buffer10;
			strErr += ": ";
			strErr += CrEngine.GetErrorText ();
		}
		OutputMessage (strErr);
	}
	catch (CException *e)
	{
		if (pJob)
			pJob -> Close ();
		pJob = NULL;

		e -> ReportError ();
		e -> Delete ();
	}

	return pJob;
}

BOOL CGakApp :: CheckOdbcConnection (BOOL bOutputUserInfo /*=TRUE*/)
{
	CString strDSN, strInfo;
	VERIFY (strDSN.LoadString (IDS_DSN_GAK));
	VERIFY (strInfo.LoadString (IDS_CONFIG_DSN));

	BOOL bRet = TRUE;

	if (!ExistDataSource (strDSN))
	{
	//	Versuche Datenquelle zu erzeugen
		if (bOutputUserInfo)
			OutputMessage (strInfo);
		bRet = ChangeDataSource (m_pMainWnd -> m_hWnd, strDSN);
	}
	else
	{
	//	prüfe Pfad-Einstellungen
		CString strDB;
		GetDataPath (strDB);
		if (0 != strDB.CompareNoCase (m_strDatabaseName))
		{
			if (bOutputUserInfo)
				OutputMessage (strInfo);
			bRet = ChangeDataSource (m_pMainWnd -> m_hWnd, strDSN);								
		}
	}

	return bRet;
}

/////////////////////////////////////////////////////////////////////////////
// CBgsabglApp commands
//	letzten Abgleich starten    
void CGakApp::OnLastAbgleich()
{
	DoAbgleich (TRUE);
}

void CGakApp::OnAbgleich()
{
	DoAbgleich (FALSE);                             
}   
                                         
//	eigentlichen Abgleich starten                                         
void CGakApp::DoAbgleich (BOOL bLast,CAbgleichParameter* pAbglParas)
{
	TRY
	{       
	//	alten Objekte alle löschen
		DeleteAllDatas ();        
	
	//	Datasource besorgen
		CString strFoxproDSN, strMDBDSN;
		VERIFY (strFoxproDSN.LoadString (IDS_DSN_GAK));		// Abgleich
		VERIFY (strMDBDSN.LoadString (IDS_MDB_DSN));		// Referenz
		m_pdbMDB = new CDatabaseExt;
		if (NULL == m_pdbMDB)
			AfxThrowMemoryException ();
		TRY
		{			
			m_pdbMDB -> Open (strMDBDSN);
		}
		CATCH_ALL (e)
		{                   
			CString strInfo;
			VERIFY (strInfo.LoadString (IDS_CREATE_ACCESSDSN));
			:: MessageBox (NULL, strInfo, AfxGetAppName (), MB_ICONINFORMATION | MB_OK);					
			if (!ChangeDataSource (m_pMainWnd -> m_hWnd, strMDBDSN))
				return;                               
		}	        
		END_CATCH_ALL                                              
		if (!m_pdbMDB -> IsOpen ())
			m_pdbMDB -> Open (strMDBDSN, FALSE, TRUE);				
		
		m_pdbFoxPro = new CDatabaseExt;
		if (NULL == m_pdbFoxPro)
			AfxThrowMemoryException ();		 
			
		TRY
		{			
			m_pdbFoxPro -> Open (strFoxproDSN);
		}
		CATCH_ALL (e)
		{                      
			CString strInfo;
			VERIFY (strInfo.LoadString (IDS_CREATE_FOXDSN));
			:: MessageBox (NULL, strInfo, AfxGetAppName (), MB_ICONINFORMATION | MB_OK);					
			if (!ChangeDataSource (m_pMainWnd -> m_hWnd, strFoxproDSN))
				return;
		}	        
		END_CATCH_ALL                                              			
		if (!m_pdbFoxPro -> IsOpen ())
			m_pdbFoxPro -> Open (strFoxproDSN);			
	
	//	Parameter eingeben	
		m_pParamDlg = new CParameters (m_pMainWnd);
		if (NULL == m_pParamDlg)
			AfxThrowMemoryException ();		 			
		m_pParamDlg -> m_pFoxProDB = m_pdbFoxPro;
		m_pParamDlg -> m_pMdbDB = m_pdbMDB;
		
	//	ggf. Parameter aus der INI-Datei lesen
		if (bLast)
			ReadParams (m_pParamDlg);						

	//  ggf. Parameter abstimmen
		if (NULL != pAbglParas)
		{
			pAbglParas->ModifyParameters(m_pParamDlg);
		}
				
		if (IDOK == m_pParamDlg -> DoModal ())
		{    
			m_pAbgleichDlg = new CDoAbgleich (m_pMainWnd, 
				0 == m_pParamDlg->m_iModus ? IDD_DOABGLEICH : IDD_DOKONTROLLE);
			m_pAbgleichDlg -> m_pFoxProDatabase = m_pdbFoxPro;
			m_pAbgleichDlg -> m_strErzeugerTable = m_pParamDlg -> m_strErzeugerTable;
			m_pAbgleichDlg -> m_strAbfallTable = m_pParamDlg -> m_strAbfallTable;
			m_pAbgleichDlg -> m_strAbfallTableVJ = m_pParamDlg -> m_strAbfallTableVJ;
			m_pAbgleichDlg -> m_pMdbDatabase = m_pdbMDB;
			m_pAbgleichDlg -> m_strBgsTable = m_pParamDlg -> m_strBGSTable;			
			m_pAbgleichDlg -> m_strOutputTable = m_pParamDlg -> m_strOutputTable;
			m_pAbgleichDlg -> m_dMinMenge = m_pParamDlg -> m_dMenge;
			m_pAbgleichDlg -> m_dMinMengeRec = m_pParamDlg -> m_dMengeRec;
			m_pAbgleichDlg -> m_bOnlySonderAbfall = m_pParamDlg -> m_bOnlySonderAbfall;
			m_pAbgleichDlg -> m_strErzListe = m_pParamDlg -> m_strErzListe;
			m_pAbgleichDlg -> m_bErzListeAppend = m_pParamDlg -> m_bErzListeAppend;
			m_pAbgleichDlg -> m_bAbfallAppend = m_pParamDlg -> m_bAbfallAppend;			
			m_pAbgleichDlg -> m_strLastErzeuger = m_pParamDlg -> m_strLastErzeuger;
			m_pAbgleichDlg -> m_strLastAsn = m_pParamDlg -> m_strLastAsn;
			m_pAbgleichDlg -> m_iModus = m_pParamDlg -> m_iModus;
			m_pAbgleichDlg -> m_iPrioritaet = m_pParamDlg -> m_iPrioritaet;
			m_pAbgleichDlg -> m_bOnlyThisErzeuger = m_pParamDlg -> m_bOnlyThisErzeuger;
			m_pAbgleichDlg -> DoModal ();

		//	Statistik immer anwerfen
		//	Erzeugerliste ggf. löschen
			CErzListeSet *pSet = m_pAbgleichDlg->GetErzListeSet();
			if (pSet && pSet -> IsOpen ())
				pSet -> Close ();
			else
				m_pAbgleichDlg -> m_strErzListe.Empty ();

			m_pResDlg = new CResultDialog (m_pMainWnd, 0 == m_pParamDlg -> m_iModus);
			
		//	Zähler setzen
			char Buffer [10] = ""; 
			m_pResDlg -> m_strAbglCnt = ltoa (m_pAbgleichDlg -> m_lMaxErzCnt, Buffer, 10);
			m_pResDlg -> m_strEscCnt = ltoa (m_pAbgleichDlg -> m_lEscCnt, Buffer, 10);
			m_pResDlg -> m_strInListeCnt = ltoa (m_pAbgleichDlg -> m_lInListeCnt, Buffer, 10);
			m_pResDlg -> m_strOutputCnt = ltoa (m_pAbgleichDlg -> m_lOutputCnt, Buffer, 10);
			
		//	Erzeugerliste und Datenbanken setzen
			m_pResDlg -> m_strErzListe = m_pAbgleichDlg -> m_strErzListe;
			m_pResDlg -> m_pDatabase = m_pdbFoxPro;			
			::MessageBeep (MB_OK);
			m_pResDlg -> DoModal ();
		}
	}		
	CATCH_ALL(e)
	{
		DeleteAllDatas ();
		
        THROW_LAST();
	}
	END_CATCH_ALL
	
	DeleteAllDatas ();
}

void CGakApp::DeleteAllDatas ()
{
	DELETE_OBJ (m_pResDlg);
	DELETE_OBJ (m_pAbgleichDlg);
	DELETE_OBJ (m_pParamDlg);
	DELETE_OBJ (m_pdbMDB);
	DELETE_OBJ (m_pdbFoxPro);
	m_bError = FALSE;
}

void CGakApp::ReadTables (CParameters *pParams)
{   
	ASSERT (NULL != pParams);

	TRY
	{       
		CWaitCursor wc;
		CString strSection, strKey;
		VERIFY (strSection.LoadString (IDS_CONFIG));
		               
	//	Name der Erzeugertabelle						               
		VERIFY (strKey.LoadString (IDS_ERZEUGER_KEY));
		pParams -> m_strErzeugerTable = GetAbgleichParameter (strSection, strKey);

	//	Name der Bilanztabelle						               
		VERIFY (strKey.LoadString (IDS_BILANZ_KEY));
		pParams -> m_strAbfallTable = GetAbgleichParameter (strSection, strKey);
	}
	CATCH (CMemoryException, me)
	{               
		OutputMemoryError ();
	}                        
	AND_CATCH (CFileException, fe)
	{
		OutputFileError (fe -> m_cause);
	}                      
	END_CATCH	

}

//	lese Einstellungen aus der INI-Datei                  
void CGakApp::ReadParams (CParameters *pParams)
{   
	ASSERT (NULL != pParams);

	TRY
	{       
		CWaitCursor wc;
		CString strSection, strKey;
		VERIFY (strSection.LoadString (IDS_CONFIG));
		               
		ReadTables(pParams);

	//	Name der Bilanztabelle Vorjahr						               
		VERIFY (strKey.LoadString (IDS_BILANZ_KEY_VJ));
		pParams -> m_strAbfallTableVJ = GetAbgleichParameter (strSection, strKey);
			
	//	Name der BGS-Tabelle						               
		VERIFY (strKey.LoadString (IDS_BGS_KEY));
		pParams -> m_strBGSTable = GetAbgleichParameter (strSection, strKey);
			
	//	Name der Ausgabe-Tabelle						               
		VERIFY (strKey.LoadString (IDS_OUTPUT_KEY));
		pParams -> m_strOutputTable = GetAbgleichParameter (strSection, strKey);
	
	//	Namen der Erzeugerliste
		VERIFY (strKey.LoadString (IDS_ERZLIST_KEY));
		pParams -> m_strErzListe = GetAbgleichParameter (strSection, strKey);
		
	//	akt. Erzeuger
		VERIFY (strKey.LoadString (IDS_ERZNAME_KEY));
		pParams -> m_strLastErzeuger = GetAbgleichParameter (strSection, strKey);

	//	akt. Asn
		VERIFY (strKey.LoadString (IDS_ASN_KEY));
		pParams -> m_strLastAsn = GetAbgleichParameter (strSection, strKey);

	//	nur diesen Ereuger/Abfall
		VERIFY (strKey.LoadString (IDS_ONLY_THIS_ERZ_KEY));					    
		pParams -> m_bOnlyThisErzeuger = GetAbgleichParameterInt (strSection, strKey, 0);

	 //	Append-Flag für Bilanz-Tabelle
		pParams -> m_bAbfallAppend = 1;
			
	//	Append-Flag für Erzeugerliste-Tabelle
		pParams -> m_bErzListeAppend = 1;
										
	//	Nur Sonderabfälle-Flag	    
		VERIFY (strKey.LoadString (IDS_ONLY_SONDER_ABFALL_KEY));					    
		pParams -> m_bOnlySonderAbfall = GetAbgleichParameterInt (strSection, strKey, 0);
			
	//	Mengenschwelle
		VERIFY (strKey.LoadString (IDS_MENGEN_SCHWELLE_KEY));					    
		pParams -> m_dMenge = max (0.0, atof (GetAbgleichParameter (strSection, strKey, "0.0")));

	//	Satzmengenschwelle
		VERIFY (strKey.LoadString (IDS_MENGEN_SCHWELLE_KEY_REC));					    
		pParams -> m_dMengeRec = max (0.0, atof (GetAbgleichParameter (strSection, strKey, "0.0")));		

	//	Modus
		VERIFY (strKey.LoadString (IDS_MODUS_KEY));					    
		pParams -> m_iModus =GetAbgleichParameterInt (strSection, strKey, 0);

	//	Priorität
		VERIFY (strKey.LoadString (IDS_PRIO_KEY));					    
		pParams -> m_iPrioritaet = GetAbgleichParameterInt (strSection, strKey, 0);

	}
	CATCH (CMemoryException, me)
	{               
		OutputMemoryError ();
	}                        
	AND_CATCH (CFileException, fe)
	{
		OutputFileError (fe -> m_cause);
	}                      
	END_CATCH	
}                                                    
//	globaler Exception-Handler                     
LRESULT CGakApp::ProcessWndProcException (CException* pe, const MSG* pMsg)
{               
//	hier nur bestimmte Ausnahmen behandeln
	if (!pe)
		return CWinApp::ProcessWndProcException (pe, pMsg);
	
	if (pe->IsKindOf(RUNTIME_CLASS(CMemoryException)))
		OutputMemoryError ();         
	else 
		if (pe->IsKindOf(RUNTIME_CLASS(CDBException)))
			OutputError (((CDBException *)(pe)) -> m_strError);
		else 
			if (pe->IsKindOf(RUNTIME_CLASS(CFileException)))
				OutputFileError (((CFileException*)(pe)) -> m_cause);
			else
			{
				CString strError;    
				VERIFY (strError.LoadString (IDS_INTERNAL_ERROR));
				OutputError (strError);
			}
			
	DeleteAllDatas ();			
	m_pMainWnd -> DestroyWindow ();
              
	return -1;						
}   

//	Erzeugerliste drucken
void CGakApp::OnDruckErzliste()
{                                
	TRY
	{
	//	Datasource-Objekt öffnen
		CString strFoxproDSN;
		VERIFY (strFoxproDSN.LoadString (IDS_DSN_GAK));	// JG merge (früher IDS_FOXPRO_DSN )
		CDatabaseExt Database;
		CString strTableName;
		TRY
		{
			Database.Open (strFoxproDSN);
			CSelTable SelDlg (m_pMainWnd);
			VERIFY (SelDlg.m_strCaption.LoadString (IDS_ERZLISTE_SEL));
			SelDlg.m_bEnterNew = FALSE;
			SelDlg.m_pDataBase = &Database;
			if (IDOK == SelDlg.DoModal ())
				strTableName = SelDlg.m_strTableName; 
		}
		CATCH_ALL (e)
		{       
			CString strInfo;
			VERIFY (strInfo.LoadString (IDS_CREATE_FOXDSN));
			:: MessageBox (NULL, strInfo, AfxGetAppName (), MB_ICONINFORMATION | MB_OK);			
			if (!ChangeDataSource (m_pMainWnd -> m_hWnd, strFoxproDSN))
				return;
		}	        
		END_CATCH_ALL
		if (!Database.IsOpen ())
			Database.Open (strFoxproDSN);			                                              						
		
		if (!strTableName.IsEmpty ())
		{
		//	Tabelle OK ?
			if (! TableOK (&Database, strTableName, pErzListeTable, IDS_ERZLISTE_TABLE_ERROR))		
				return;
		
		//	Dialog-Funktion rufen und Liste ausgeben
			CResultDialog ResDlg (m_pMainWnd, TRUE);
			ResDlg.m_strErzListe = strTableName;
			ResDlg.m_pDatabase = &Database;			
			ResDlg.OutputErzeugerListe();
		}
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
}

CString CGakApp::GetAbgleichIniFileName()
{
	return CString("Bgsabgl.INI");
}

#define BUFFERSIZE 1024
CString CGakApp::GetAbgleichParameter(const CString& strSection, const CString& strKey, const CString& strDefault)
{
	char cBuffer[BUFFERSIZE];
	GetPrivateProfileString(strSection, strKey, strDefault, cBuffer, BUFFERSIZE, GetAbgleichIniFileName());
	return CString(cBuffer);
//	return GetProfileString (strSection, strKey, strDefault);
}

int CGakApp::GetAbgleichParameterInt(const CString& strSection, const CString& strKey, const int nDefault)
{
	return GetPrivateProfileInt(strSection, strKey, nDefault, GetAbgleichIniFileName());
//	return GetProfileInt(strSection, strKey, nDefault);
}

BOOL CGakApp::SetAbgleichParameter(const CString& strSection, const CString& strKey, const CString& value)
{
	return WritePrivateProfileString(strSection, strKey, value, GetAbgleichIniFileName());
//	return WriteProfileString(strSection, strKey, value);
}

BOOL CGakApp::SetAbgleichParameter(const CString& strSection, const CString& strKey, const int& value)
{
	CString strValue;
	strValue.Format("%d", value);
	return SetAbgleichParameter(strSection, strKey, strValue);
//	return WriteProfileInt(strSection, strKey, value);
}
