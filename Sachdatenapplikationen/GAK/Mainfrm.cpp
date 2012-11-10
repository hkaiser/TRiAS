// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"			// prec. Header
#include "gak.h"			// CGakApp
#include "importty.h"		// CImportParams
#include "InTablPg.h"		// CInputTablePage
#include "OutTbPg.h"		// COutputTablePage
#include "ImpParPg.h"		// CImportParamPage
#include "ImpSumPg.h"		// CImportSumPage
#include "DoImpPge.h"		// CDoImportPage	
#include "ImpResPg.h"		// CImportResultPage		
#include "ImprtDlg.h"		// CImportDlg
#include "StatDlg.h"		// CStatistikDialog
#include <odbcinst.h>
#include "getodbci.h"		// ODBC-Rufe
#include "statbare.h"		// CStatusBarExt
#include "progress.h"		// CProgress
#include "selectex.h"		// CSelectExportTables	
#include "gaksete.h"		// CRecordsetExt
#include "gakset.h"			// CGakSet
#include "abfsetex.h"		// CAbfSetExport
#include "exportre.h"		// CExportResultDlg	
//#include "direct.h"			// _getdrive ()
#include "afidlg.h"			//	CAfiDlg
#include "selset.h"			//	CSelectSet
#include "abfarset.h"		//	CAbfArtSet

#include "MainFrm.h"		// zugeh. Header

// JG Das Exportieren wird abbrechbar dazu wird diese Transactionsklasse benutzt
#include "DAOTransaction.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//	externe Variablen
extern IndexFieldInfo ErzeugerIndexField [];
extern IndexFieldInfo AbfallIndexField [];

// externe Funktionen
extern void StartErrorHelp ();

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(IDM_IMPORT, OnImport)
	ON_COMMAND(IDM_STATISTIK, OnStatistik)
	ON_COMMAND(IDM_HELP_DATABSE_ERRORS, OnHelpDatabaseErrors)
	ON_COMMAND(IDM_CONFIG_DSN, OnConfigDsn)
	ON_COMMAND(IDM_CALL_ADMIN, OnCallAdmin)
	ON_WM_DESTROY()
	ON_COMMAND(IDM_EXPORT, OnExport)
	ON_UPDATE_COMMAND_UI(IDM_AKTBILANZ, OnUpdateAktbilanz)
	ON_UPDATE_COMMAND_UI(IDM_ODBC_ACESS, OnUpdateOdbcAcess)
	ON_WM_SHOWWINDOW()
	ON_COMMAND(IDM_ODBC_ACESS, OnOdbcAcess)
	//}}AFX_MSG_MAP
	// Global help commands
	ON_COMMAND(ID_HELP_FINDER, CMDIFrameWnd::OnHelpFinder)
	ON_COMMAND(ID_HELP, CMDIFrameWnd::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CMDIFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CMDIFrameWnd::OnHelpFinder)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		| WS_THICKFRAME | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE;

	return CMDIFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

void CMainFrame::SetStatusBarText (const char *pText, BOOL bIgnore /* TRUE*/)
{
	ASSERT (NULL != pText && AfxIsValidString (pText));
	m_wndStatusBar.SetPaneText (0, pText, TRUE);
	m_wndStatusBar.m_bIgnoreSetText = bIgnore;
}

void CMainFrame::GetStatusBarText (CString &strText)
{
	m_wndStatusBar.GetPaneText (0, strText);
}

//	Daten importieren
void CMainFrame::OnImport() 
{
	CImportDlg Dlg ("", this);
	Dlg.SetWizardMode ();
	Dlg.DoModal ();
}

//	Datenbank-Statistik anzeigen
void CMainFrame::OnStatistik() 
{
	try
	{
		CMutex mt;
		CStatistikDialog Dlg (this);
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

void CMainFrame::OnHelpDatabaseErrors() 
{
	// TODO: Add your command handler code here
	StartErrorHelp ();
}

void CMainFrame::OnConfigDsn() 
{
	// TODO: Add your command handler code here
	try
	{
		CString strDSN;
		VERIFY (strDSN.LoadString (IDS_DSN_GAK));
		ChangeDataSource (this -> m_hWnd, strDSN);	
	}
	catch (CMemoryException *me)
	{
		me -> ReportError ();
		me -> Delete ();
	}			
}

void CMainFrame::OnCallAdmin() 
{
	// TODO: Add your command handler code here
	:: SQLManageDataSources (this -> m_hWnd);
}

/*
#define crColorGray ((COLORREF)RGB(255,255,255))
BOOL CMainFrame::OnEraseBkgnd(CDC* pDC) 
{
// TODO: Add your message handler code here and/or call default
	CRect rect;
 	GetClientRect(rect);
 	CBrush brush (crColorGray);
	pDC -> FillRect (&rect, &brush);

	return TRUE;
}
	
	BYTE obj[32];         
	CBitmap bild;
	VERIFY (bild.LoadBitmap (IDB_LAND));
	int r = bild.GetObject (30, obj);
	short bildX = obj[2] + obj[3]*256;
	short bildY = obj[4] + obj[5]*256;

	CDC	memdc;
	VERIFY (memdc.CreateCompatibleDC (pDC));
	CBitmap *oldBM = memdc.SelectObject( &bild );
	ASSERT (NULL != oldBM);

	short screenX = (rect.right - rect.left - bildX) / 2;
	short screenY = (rect.bottom - rect.top - bildY) / 2;
	VERIFY (pDC -> StretchBlt (screenX, screenY, bildX, bildY, &memdc, 0, 0, bildX, bildY, SRCCOPY ));
	memdc.SelectObject (oldBM);
	bild.DeleteObject();

	return TRUE;
	// return CMDIFrameWnd::OnEraseBkgnd(pDC);
}
*/
void CMainFrame::OnDestroy() 
{
/*
//	SizeOrg speichern                                
	CRect rc;
	GetWindowRect (rc);				
	CString strFormat, strSection, strEntry;
	VERIFY (strFormat.LoadString (IDS_SIZEORG_FORMAT));
	char Buffer80 [80] = "";
	wsprintf (Buffer80, strFormat, rc.left, rc.top, rc.Width (), rc.Height ());
	VERIFY (strSection.LoadString (IDS_CONFIG_SECTION));
	VERIFY (strEntry.LoadString (IDS_SIZEORG));									
	AfxGetApp () -> WriteProfileString (strSection, strEntry, Buffer80);
*/

	CMDIFrameWnd::OnDestroy();
}

//	ermittle Anzahl der Datensätze in Tabelle
//	kein try/catch
long CMainFrame :: GetAnzahl (CDaoDatabase *pDatabase, const char *pTable)
{
//	prüfe Parameter
	ASSERT (NULL != pTable && AfxIsValidString (pTable));
	ASSERT (NULL != pDatabase && pDatabase -> IsOpen ());

	CWaitCursor wc;
	CString strSQL, strFieldName;
	AfxFormatString1 (strSQL, IDS_SELECT_COUNT, pTable);
	CDaoRecordset Set (pDatabase);
	Set.Open (dbOpenSnapshot, strSQL, dbForwardOnly);
	
//	lese Anzahl der Datensätze vom Feld 'Anzahl'
	CDaoFieldInfo Info;
	Set.GetFieldInfo (0, Info);
	COleVariant var (Set.GetFieldValue (Info.m_strName));
	if (VT_NULL == var.vt)
		return 0;

	if (VT_I4 != var.vt)
		var.ChangeType (VT_I4);

	Set.Close ();

	return var.lVal;
}

//	kein try/catch
void CMainFrame::CreateTable (CDaoDatabase *pDatabase, const char *pTableName, UINT uiResId, 
							  IndexFieldInfo *pFieldInfo)
{        
//	prüfe Parameter
	ASSERT (NULL != pTableName && AfxIsValidString (pTableName));
	ASSERT (uiResId > 0);
	ASSERT (NULL != pFieldInfo);
	ASSERT (NULL != pDatabase && pDatabase -> IsOpen ());
                           
//	SQL-String zusammenbauen	                           
	CString strSQL;
	strSQL.Format(uiResId, pTableName);
	
//	Tabelle erzeugen
	pDatabase -> Execute (strSQL, dbFailOnError);
	//DAO_CHECK(pDatabase -> m_pDAOTableDefs->Refresh ());
	
//	Indizes erzeugen
	CString strFieldName, strDisAllowNull;
	strSQL.Empty ();
	VERIFY (strDisAllowNull.LoadString (IDS_DISALLOW_NULL));
	do
	{
		AfxFormatString2 (strSQL, IDS_CREATE_INDEX_DDL, pTableName, pFieldInfo->pIndexName);
		if (pFieldInfo->bDisAllowNull)
			strSQL += " " + strDisAllowNull;
			pDatabase -> Execute (strSQL, dbFailOnError);
		pFieldInfo++;
	} 
	while ((NULL != pFieldInfo) && pFieldInfo->pIndexName && *pFieldInfo->pIndexName);
}	            

//	Daten exportieren
void CMainFrame::OnExport() 
{
//	TODO: Add your command handler code here
	CGakApp *pApp = (CGakApp *) AfxGetApp ();
	ASSERT (NULL != pApp);
	
	CProgress *pProgress = NULL;
	long lAbfCntExp = 0;		//	mitgezählte Anzahl der wirklich exportierten
	long lErzCntExp = 0;

	long out_lAbfCntExp = 0;	// im Ergebnis angezeigte Datensatzanzahl 
	long out_lErzCntExp = 0;
								// bleibt bei Abbruch einfach so
	CDaoDatabase OutputDB;

	try
	{   
	//	Tabelle auswählen
		CSelectExportTables TableDlg (this);
		if (IDOK != TableDlg.DoModal ())
			AfxThrowUserException ();			

#ifdef _BRANDENBURG
	//	für LUA-Version muß zusätzlich der Afi-Bereich abgefragt werden
		CString strGKZFilter;
		BOOL bExportAfi = TRUE;
		CAfiDlg AfiDlg (this);
		if (IDOK != AfiDlg.DoModal ())	//	bei Abbruch
			AfxThrowUserException ();	//	beenden				
				       
		bExportAfi = AfiDlg.m_bType;	//	Exporttyp speichern	

// Beschreibung des Exportfeldes
const char AFIEXPORT = 1;
const char KREISEXPORT = 2;
const char IMPORTIERT = 8;
 
		char iExportFlag = AfiDlg.m_bType ? AFIEXPORT : KREISEXPORT;

	//	den Filter-String zusammenbauen:alle GKZ aufsammeln		
		CString strTemp, strOr;
		VERIFY (strOr.LoadString (IDS_OR));			
		char *pEnd = NULL;
		char *pBeg = (char *)(const char *)AfiDlg.m_strGKZ;;
		char Buffer20 [20] = "";
		ULONG ulVal = 0;
		while (pBeg && *pBeg)
		{
        	ulVal = strtoul (pBeg, &pEnd, 10);
        	ASSERT (ulVal > 0);
        	ultoa (ulVal, Buffer20, 10);
        	AfxFormatString1 (strTemp, IDS_WHERE_GKZ, Buffer20);
        	if (strGKZFilter.IsEmpty ())
        		strGKZFilter = strTemp;
			else
				strGKZFilter += strOr + strTemp;        			

        	if (pEnd && *pEnd)
                pBeg = ++pEnd;
        	else
                break;
		}             
#endif
			
	//	Meldung an Nutzer
		pApp -> OutputMessage (IDS_PREPARE_DISK);					
		
	//	Namen der Ausgabe-DB eingeben
		CString strDBName (pApp -> DatabaseName ());
		CString strOutExt (' ', _MAX_EXT);
		CString strNewFileName (' ', _MAX_FNAME);
		_splitpath (strDBName, NULL, NULL, (char*)(const char*)strNewFileName, 
										   (char*)(const char *)strOutExt);
		strcat ((char*)(const char *)strNewFileName, strOutExt);
		CString strExt, strFilter;
		VERIFY(strFilter.LoadString (IDS_MDB_FILTER)); 
		VERIFY (strExt.LoadString (IDS_DATABASE_EXTENSION));
		CFileDialog CopyToDialog (FALSE, strExt, strNewFileName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
								  strFilter, this);

	//	kann auf Laufwerk A gewechselt werden
		/*int iOldDrive = _getdrive ();
		if (0 == _chdrive (1))
			CopyToDialog.m_ofn.lpstrInitialDir = "a:\\";
		_chdrive (iOldDrive);
		*/
		CString strCaption;
		VERIFY (strCaption.LoadString (IDS_RUECK_OUT_CAPTION));
		CopyToDialog.m_ofn.lpstrTitle = strCaption;				
		
	//	Dialog aufrufen
		if (IDOK != CopyToDialog.DoModal ())
			AfxThrowUserException ();
		
	//	lese Namen der Ausgabedatenbank
		CString strOutName = CopyToDialog.GetPathName ();
		strOutName.MakeUpper ();
		
	//	Dateinamen gleich ?
		if (0 == strDBName.CompareNoCase(strOutName))
		{
			pApp -> OutputMessage (IDS_DIFF_NAMES);
			AfxThrowUserException ();			
		}		                
		
	//	Meldung an Nutzer ausgeben
		CWaitCursorExt wc (IDS_PREPARE_EXPORT);		
		
	//	Ausgabedatenbank leere DB erzeugen und öffnen: Access-Version 2.0 !
	//	wenn Datenbank existiert, diese zuvor löschen
		OFSTRUCT of;
		if (OpenFile (strOutName, &of, OF_EXIST) > 0)
			OpenFile (strOutName, &of, OF_DELETE);

#ifdef MDB_VERSION20
		OutputDB.Create (strOutName, dbLangGeneral, dbVersion20);
#else
		OutputDB.Create (strOutName, dbLangGeneral);
#endif
	//	Eingabe-DB öffnen
		CDaoDatabase InputDB;
		InputDB.Open (pApp -> DatabaseName ());
		
	//	Ausgabetabellen erzeugen: zuerst Erzeuger
		long lErzCnt = 0;
		long lAbfCnt = 0;                               

		if (TableDlg.m_bErzeuger)
		{	
			CreateTable (&OutputDB, pApp -> ErzeugerDefaultSQL (), 
						 IDS_ERZEUGER_DDL, ErzeugerIndexField);
#ifndef _BRANDENBURG				
			lErzCnt = GetAnzahl (&InputDB, pApp -> ErzeugerDefaultSQL ());
#endif
		}				
        
	//	Bilanztabelle        
		if (TableDlg.m_bAbfaelle)
		{
			CreateTable (&OutputDB, pApp -> AbfallDefaultSQL (), 
						IDS_ABFALL_DDL, AbfallIndexField);
#ifndef _BRANDENBURG				
			lAbfCnt = GetAnzahl (&InputDB, pApp -> AbfallDefaultSQL ());
#endif
		}	
		OutputDB.Close ();

#ifdef _BRANDENBURG
	//	für LUA-Version muß schrittweises Zählen erfolgen					
		CGakSetRed ErzSetRed (&InputDB);
		ASSERT (!strGKZFilter.IsEmpty ());																									
		ErzSetRed.m_strFilter = strGKZFilter;
		ErzSetRed.Open (dbOpenSnapshot, NULL, dbReadOnly);
		for (; !ErzSetRed.IsEOF (); lErzCnt++)
			ErzSetRed.MoveNext ();				
		lAbfCnt = lErzCnt;
		if (lErzCnt > 0)
			ErzSetRed.MoveFirst ();
#endif	

	//	Test, ob Datensätze vorhanden ?
		if (0 == lAbfCnt + lErzCnt)
		{
			pApp -> OutputMessage (IDS_NO_RECORDS);
			AfxThrowUserException ();					
		}			

	//	Scrollbalken erzeugen               
		pProgress = new CProgress (this);
		UINT uiCnt = 0; 
		VERIFY (strCaption.LoadString (IDS_EXPORT_TABLES));
		pProgress -> SetParams (uiCnt, (UINT)(lAbfCnt + lErzCnt), strCaption); 				
	
	//	Tabellen kopieren: Erzeuger
		OutputDB.Open (strOutName);
//		CDaoTransaction CopyTransaction(OutputDB);

		if (TableDlg.m_bErzeuger && (lErzCnt > 0))
		{                   
		//	Scrollbalken überschrift setzen
			CString strAction;
			AfxFormatString1 (strAction, IDS_EXPORT_TABLE_FORMAT, pApp -> ErzeugerDefaultSQL ());
			pProgress -> SetActionText (strAction);
		
		//	Sets init.
			CGakSet ErzInSet (&InputDB);
#ifdef _BRANDENBURG
			ErzInSet.m_strFilter = strGKZFilter;			
#endif

#ifdef	_WITHPARAEXPORTED
			ErzInSet.CDaoRecordset::Open (dbOpenDynaset, pApp -> ErzeugerDefaultSQL ());
#else	// _WITHPARAEXPORTED
			ErzInSet.CDaoRecordset::Open (dbOpenSnapshot, pApp -> ErzeugerDefaultSQL (), dbForwardOnly);
#endif	// _WITHPARAEXPORTED
			CGakSet ErzOutSet (&OutputDB);
			ErzOutSet.Open (dbOpenSnapshot, pApp -> ErzeugerDefaultSQL (), dbAppendOnly);			 					
					
			for (; !ErzInSet.IsEOF (); ErzInSet.MoveNext ())						   							   
			{                        
			//
			//	Nutzerabbruch ?				                             
			//

				if (pProgress -> Break ())
					AfxThrowUserException ();
			
			//
			//	Srcollbalken akt.				
			//

				pProgress -> SetPos (++uiCnt);

#ifdef	_WITHPARAEXPORTED
			//
			//	wenn nur neue DS exporteiert werden sollen &&wenn der Datensatz bereits exportiert wurde
			//  dann tschüß du Datensatz
			//

				if (AfiDlg.m_bOnlyNotExported && !ErzInSet.m_Exportiert.IsEmpty() && ErzInSet.m_Exportiert[0] & iExportFlag)
					continue;
#endif	_WITHPARAEXPORTED					
				                        
				ErzOutSet.AddNew ();
				ErzOutSet = ErzInSet;					
				ErzOutSet.m_Exportiert = IMPORTIERT;	// als importiert kennzeichnen, alles andere vergessen
				ErzOutSet.Update ();
				lErzCntExp++;

#ifdef	_WITHPARAEXPORTED
				//
				// als exportiert kennzeichnen
				//

				ErzInSet.Edit();
				if (ErzInSet.m_Exportiert.IsEmpty())
					ErzInSet.m_Exportiert = static_cast<char> (iExportFlag);
				else
					ErzInSet.m_Exportiert = static_cast<char> (ErzInSet.m_Exportiert[0] | iExportFlag);	// als exportiert kennzeichnen
				ErzInSet.Update();
#endif	// _WITHPARAEXPORTED

			}
		//			
		//	leere Erzeuger-Tabelle wieder löschen
		//

			if ((0 == lErzCntExp) && ErzOutSet.IsOpen ())
			{            
			//
			//	Set schließen			
			//

				ErzOutSet.Close ();        
				ASSERT (OutputDB.IsOpen ());		

			//			
			//	Tabelle löschen
			//

				CString strDel;
				AfxFormatString1 (strDel, IDS_DELETE_TABLE, pApp -> ErzeugerDefaultSQL ());			
				try
				{
					OutputDB.Execute (strDel, dbFailOnError);
				}
				catch (CDaoException * db)
				{
					// this will sometimes throw an exception, i dont know why
					db -> Delete ();
				}		

			}						
		}						   

	//		
	//	Kopiere Bilanztabelle
	//

		if (TableDlg.m_bAbfaelle && (lAbfCnt > 0))
		{                   
		//
		//	Scrollbalken überschrift setzen         
		//

			CString strAction;
			AfxFormatString1 (strAction, IDS_EXPORT_TABLE_FORMAT, pApp -> AbfallDefaultSQL ());
			pProgress -> SetActionText (strAction);

		//		
		//	Sets init.
		//

			CAbfSetExport AbfInSet (&InputDB);

#ifdef	_WITHPARAEXPORTED
			//
			// schließlich müssen wir diesen Satz als exportiert markieren
			//
			AbfInSet.CDaoRecordset::Open (dbOpenDynaset, pApp -> AbfallDefaultSQL ()/*, dbReadOnly*/);

#else	// _WITHPARAEXPORTED
			//
			// sonst können wir (problemloser) als readonly öffnen
			//
			AbfInSet.CDaoRecordset::Open (dbOpenSnapshot, pApp -> AbfallDefaultSQL (), dbReadOnly);

#endif	// _WITHPARAEXPORTED

			AbfInSet.CDaoRecordset::MoveFirst ();
			CAbfSetExport AbfOutSet (&OutputDB);
			AbfOutSet.Open (dbOpenDynaset, pApp -> AbfallDefaultSQL (), dbAppendOnly);			 	
			
#ifdef _BRANDENBURG

			ASSERT (ErzSetRed.IsOpen ());
			ErzSetRed.MoveFirst ();
			CAbfArtSet ArtenSet (&InputDB, pApp -> AbfallArtenDefaultSQL ());
			ArtenSet.Open (); 
			CString strFilter;
			for (; !ErzSetRed.IsEOF (); ErzSetRed.MoveNext ())						   							   
			{                        
			//
			//	Nutzerabbruch ?				                             
			//

				if (pProgress -> Break ())
					AfxThrowUserException ();								

			//	
			//	Srcollbalken akt.			
			//

				pProgress -> SetPos (++uiCnt);	

			//				
			//	lese Abfälle über Erzeugernummer
			//

				if (!ErzSetRed.m_Nummer.IsEmpty ())
				{
					BOOL bOutput = FALSE;                       
					char Buffer5 [5] = "";
					AfxFormatString1 (AbfInSet.m_strFilter, IDS_FIND_NUMMER, ErzSetRed.m_Nummer);
					for (AbfInSet.Requery (); !AbfInSet.IsEOF (); AbfInSet.CDaoRecordset::MoveNext ())											
					{              
						bOutput = FALSE;                                 
						Buffer5 [0] = '\0';
						
#ifdef	_WITHPARAEXPORTED
						//
						//	wenn nur neue DS exporteiert werden sollen &&wenn der Datensatz bereits exportiert wurde
						//

						if (AfiDlg.m_bOnlyNotExported && !AbfInSet.m_Exportiert.IsEmpty() && AbfInSet.m_Exportiert[0] & iExportFlag)
							continue;
#endif	// _WITHPARAEXPORTED					

					//
					//	nicht nur Sonderabfälle
					//

						if (!AfiDlg.m_bOnlySA)
						{
							AbfOutSet.AddNew ();
							AbfOutSet = AbfInSet;					
							// AbfOutSet.m_Exportiert = itoa((atoi(AbfOutSet.m_Exportiert) | EXPORTED_AFI), Buffer5, 10); 
#ifdef	_WITHPARAEXPORTED
							AbfOutSet.m_Exportiert = IMPORTIERT;	// als importiert kennzeichnen, alles andere vergessen
#endif	// _WITHPARAEXPORTED					
							AbfOutSet.Update ();		
							bOutput = TRUE;
							lAbfCntExp++;
						}
						else

						//
						//	nur Sonderabfälle
						//

						{ 
  
						//
						//	wenn eine Abfallart angegeben
						//

							bOutput = !AbfInSet.m_Abfallnummer.IsEmpty ();
							if (bOutput)
							{ 
      
							//
							//	und ein in der Liste hinterlegter Sonderabfall								
							//

								AfxFormatString1 (strFilter, IDS_FIND_NUMMER, AbfInSet.m_Abfallnummer);
								if (ArtenSet.FindFirst (strFilter) && ArtenSet.m_Sonderabfall)
									bOutput = TRUE;										
								else
									bOutput = FALSE;
							}
							
							if (bOutput)
							{
								AbfOutSet.AddNew ();
								AbfOutSet = AbfInSet;
								//AbfOutSet.m_Exportiert = itoa((atoi(AbfOutSet.m_Exportiert) | EXPORTED_KRS), Buffer5, 10);
#ifdef	_WITHPARAEXPORTED					
								AbfOutSet.m_Exportiert = IMPORTIERT;	// als importiert kennzeichnen, alles andere vergessen
#endif	// _WITHPARAEXPORTED					
								AbfOutSet.Update ();	
								lAbfCntExp++;
							}								
						}

#ifdef	_WITHPARAEXPORTED
						if (TRUE == bOutput)
						{
							//
							// als exportiert kennzeichnen
							//

							AbfInSet.Edit();

							if (AbfInSet.m_Exportiert.IsEmpty())
							{
								AbfInSet.m_Exportiert = static_cast<char> (iExportFlag);
							}
							else
							{
								AbfInSet.m_Exportiert = static_cast<char> (AbfInSet.m_Exportiert[0] | iExportFlag);	// als exportiert kennzeichnen
							}
							
							AbfInSet.Update();
						}
#endif	// _WITHPARAEXPORTED
						
					}							
				}						
			}
#else	// _BRANDENBURG
			for (; !AbfInSet.IsEOF (); AbfInSet.CDaoRecordset::MoveNext ())						   							   
			{                        
			//
			//	Nutzerabbruch ?				                             
			//

				if (pProgress -> Break ())
					AfxThrowUserException ();								

#ifdef	_WITHPARAEXPORTED
				//
				//	wenn nur neue DS exporteiert werden sollen &&wenn der Datensatz bereits exportiert wurde
				//

				if (AfiDlg.m_bOnlyNotExported && !AbfInSet.m_Exportiert.IsEmpty() && AbfInSet.m_Exportiert[0] & iExportFlag)
					continue;
#endif	_WITHPARAEXPORTED					

			//
			//	Srcollbalken akt.			
			//

				pProgress -> SetPos (++uiCnt);	
				
				AbfOutSet.AddNew ();
				AbfOutSet = AbfInSet;	
#ifdef	_WITHPARAEXPORTED					
				AbfOutSet.m_Exportiert = IMPORTIERT;	// als importiert kennzeichnen, alles andere vergessen
#endif	// _WITHPARAEXPORTED					
				AbfOutSet.Update ();
				lAbfCntExp++;

#ifdef	_WITHPARAEXPORTED
				//
				// als exportiert kennzeichnen
				//

				AbfInSet.Edit();

				if (AbfInSet.m_Exportiert.IsEmpty())
				{
					AbfInSet.m_Exportiert = static_cast<char> (iExportFlag);
				}
				else
				{
					AbfInSet.m_Exportiert = static_cast<char> (AbfInSet.m_Exportiert[0] | iExportFlag);	// als exportiert kennzeichnen
				}
				
				AbfInSet.Update();
#endif	// _WITHPARAEXPORTED

			}
#endif	// _BRANDENBURG
		
		//  Transaction erfolgreich abgeschlossen
//			CopyTransaction.Commit();

		//	ggf. leere  Abfall-Tabelle wieder löschen
			if ((0 == lAbfCntExp) && AbfOutSet.IsOpen ())
			{            
			//	Set schließen			
				AbfOutSet.Close ();       
				ASSERT (OutputDB.IsOpen ());		
			
			//	Tabelle löschen
				CString strDel;
				AfxFormatString1 (strDel, IDS_DELETE_TABLE, pApp -> AbfallDefaultSQL ());
				try 
				{
					OutputDB.Execute (strDel, dbFailOnError);
				}
				catch (CDaoException * db)
				{
					// this will sometimes throw an exception, i dont know why
					db -> Delete ();
				}		

			}			
		}	
		
	//	Datenbanken schließen
		InputDB.Close ();
		OutputDB.Close ();

		out_lAbfCntExp = lAbfCntExp;
		out_lErzCntExp = lErzCntExp;
	}			
	catch (CMemoryException *me)
	{            
		me -> ReportError ();
		me -> Delete ();
	}	    
	catch (CDaoException *db)
	{
		:: DisplayDaoException (db);
		db -> Delete ();
	}		
	catch (CUserException *ue)
	{
			//	nur auffangen
			ue -> Delete ();
		// JG 981007 Da Transaktionen nicht funktionieren müssen bei Benutzerabbruch die Tabellen wieder gelöscht werden
		// Abbrechen wurde betätigt -> bereits kopierte Daten wieder löschen

			if (OutputDB.IsOpen())
			{
			//	Tabelle löschen
				CString strDel;
				AfxFormatString1 (strDel, IDS_DELETE_TABLE, pApp -> ErzeugerDefaultSQL ());
				OutputDB.Execute (strDel, dbFailOnError);

				AfxFormatString1 (strDel, IDS_DELETE_TABLE, pApp -> AbfallDefaultSQL ());
				OutputDB.Execute (strDel, dbFailOnError);
			}
	}                               
         
	DELETE_OBJ (pProgress);
	
//	ExportErgebnis anzeigen
	CExportResultDlg DlgRes (this);
	char Buffer20 [20] = "";
	DlgRes.m_strAbfCnt = ltoa (out_lAbfCntExp , Buffer20, 10);
	DlgRes.m_strErzCnt = ltoa (out_lErzCntExp , Buffer20, 10);
	DlgRes.m_strSumCnt = ltoa (out_lAbfCntExp + out_lErzCntExp, Buffer20, 10);
	DlgRes.DoModal ();			
}


void CMainFrame::OnUpdateAktbilanz(CCmdUI* pCmdUI) 
{
	if (NULL == pCmdUI) 
		return;

	pCmdUI->Enable(false);
}

void CMainFrame::OnUpdateOdbcAcess(CCmdUI* pCmdUI) 
{
	if (NULL == pCmdUI) 
		return;

	pCmdUI->Enable(true);
}

void CMainFrame::OnOdbcAcess() 
{
	// TODO: Add your command handler code here
	try
	{
		CString strDSN;
		VERIFY (strDSN.LoadString (IDS_MDB_DSN));
		ChangeDataSource (this -> m_hWnd, strDSN);	
	}
	catch (CMemoryException *me)
	{
		me -> ReportError ();
		me -> Delete ();
	}			
	
}
