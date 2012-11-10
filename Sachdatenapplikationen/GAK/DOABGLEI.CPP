// doabglei.cpp : implementation file
//

#include "stdafx.h" 		//	prec. Header

#include "res.h"			//	Resource-Konstanten
#include "recset.h"			//	CRecordsetExt
#include "erzeuset.h"		//	CErzeugerSet
#include "abfarsetodbc.h"		//	CAbfartSet	//angepaßt an merge
#include "abfalset.h"		//	CAbfallSet
#include "bgsset.h"			//	CBgsSet
#include "outset.h"			//	COutputSet
#include "abfarmap.h"		//	CAbfallArtenMap
#include "abfmap.h"			// 	CAbfallMap
#include "editext.h"		//	CEditExt
#include "numedit.h"		//	CNumEdit
#include "abfartpa.h"		//	CAbfartParams	
#include "selset.h"			// CSelectSet
#include "gaksete.h"		// CDaoRecordsetExt
#include "gakset.h"
#include "AbfSet.h"			// zugeh. Header
#include "erzliste.h"		// 	CErzListeSet
#include "columnst.h"		// 	CColumns
#include "ErzInfo.h"		//	CErzInfo
#include "gak.h"			//  JG merge CGakApp 

#include "doabglei.h"		// 	zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//	Konstanten
static const char * szColumnsField [iColumnsCount] = {
	"lfd. Nr.",
	"Abfallart",
	"SA",
	"EN/SN-Nr.",
	"Menge",
	"EN/SN-Menge",
	"Beförderer-Nr.",
	"Entsorger-Nr.",
	"R/D-Verfahren",
	"Priorität",
};

//	externe Variablen
extern pFieldInfo pErzListeTable;
extern pFieldInfo pAbfArtenTable;	

extern CAbfSet *g_pAbfSet;
extern CGakSet *g_pErzSet;

// JG merge (allready defined for gak-Project)
/*
void CallMessageQueue (void)
{
	MSG msg;
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
    	if (msg.message == WM_QUIT)
    		return;

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}
*/
/////////////////////////////////////////////////////////////////////////////
// CDoAbgleich dialog
CDoAbgleich::CDoAbgleich(CWnd* pParent, UINT uiResID)
	: CDialog(uiResID, pParent)
{   
//	Sets rücksetzen
	m_pBgsSet = NULL;
	m_pAbfArtenMap = NULL;
	m_pOutputSet = NULL;
	m_pErzeugerSet = NULL;       
	m_pErzeugerInfoSet = NULL;
	m_pAbfArtenSet = NULL;
	m_pAbfallSet = NULL;
	m_pAbfallSetVJ = NULL;
	m_pErzListeSet = NULL;
	m_pFoxProDatabase = NULL;
	m_pMdbDatabase = NULL;
	m_pBranchenSet = NULL;	// JG

//	Mengen rücksetzen
	m_dMinMenge = m_dMinMengeRec = 0.0;

//	Zähler rücksetzen
	m_lDirtyCnt = m_lActErzCnt = m_lMaxErzCnt = m_lOutputCnt = m_lEscCnt = m_lInListeCnt = 0;
	
//	Maps rücksetzen
	m_pAbfallMap = NULL;
	m_pAbfallMapVJ = NULL;
	m_pBgsMap = NULL;
	m_pBgsSet = NULL;

//	weitere Var. init
	m_iModus = m_iPrioritaet = 0;
	m_bInAction = m_bUserBreak = FALSE;
	m_bAbfallAppend = m_bErzListeAppend = FALSE;
	m_bNotInit = TRUE;
	m_bOnlySonderAbfall = FALSE;
	m_bOnlyThisErzeuger = m_bInputFromListe = FALSE;
	
	m_bMoveInit = TRUE;
	//{{AFX_DATA_INIT(CDoAbgleich)
	//}}AFX_DATA_INIT
}                                           

CDoAbgleich :: ~CDoAbgleich ()
{
//	Sets löschen
	DELETE_OBJ (m_pErzeugerSet);	
	DELETE_OBJ (m_pErzeugerInfoSet);
	DELETE_OBJ (m_pAbfArtenSet);
	DELETE_OBJ (m_pAbfallSet);
	DELETE_OBJ (m_pAbfallSetVJ);
	DELETE_OBJ (m_pBgsSet);
	DELETE_OBJ (m_pOutputSet);
	DELETE_OBJ (m_pErzListeSet);
	DELETE_OBJ (m_pBranchenSet);	// JG

//	Maps löschen
	DELETE_OBJ (m_pAbfallMap);
	DELETE_OBJ (m_pAbfallMapVJ);
	DELETE_OBJ (m_pBgsMap);
	DELETE_OBJ (m_pAbfArtenMap);
}

void CDoAbgleich::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDoAbgleich)
	DDX_Control(pDX, IDC_BRANCHENNUMMER, m_ctrlBranchennummer);
	DDX_Control(pDX, IDC_ANFALLSTELLE, m_ctrlAnfallstelle);
	DDX_Control(pDX, IDB_WEITER, m_btWeiter);
	DDX_Control(pDX, IDL_BGSN, m_lbBgs);
	DDX_Control(pDX, IDL_ABFALLN, m_lbAbfall);
	DDX_Control(pDX, IDL_ABFALL_VJN, m_lbAbfallVJ);
	DDX_Control(pDX, IDB_ERZ_INFO, m_btErzInfo);
	DDX_Control(pDX, ID_HELP, m_btHelp);
	DDX_Control(pDX, IDB_INLISTE, m_btInListe);
	DDX_Control(pDX, IDT_PROGRESS2, m_ctProgress);
	DDX_Control(pDX, IDT_AKTION, m_stAction);
	DDX_Control(pDX, IDOK, m_btOk);
	DDX_Control(pDX, IDB_ESCAPE, m_btEscape);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDoAbgleich, CDialog)
	//{{AFX_MSG_MAP(CDoAbgleich)
	ON_BN_CLICKED(IDB_ESCAPE, OnEscape)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDB_INLISTE, OnInListe)
	ON_BN_CLICKED(ID_HELP, OnHelp)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDB_ERZ_INFO, OnErzInfo)
	ON_NOTIFY(NM_CLICK, IDL_ABFALLN, OnClickAbfall)
	ON_NOTIFY(NM_CLICK, IDL_BGSN, OnClickBgs)
	ON_NOTIFY(LVN_DELETEITEM, IDL_ABFALL_VJN, OnDeleteitemAbfallVorjahr)
	ON_NOTIFY(LVN_DELETEITEM, IDL_ABFALLN, OnDeleteitemAbfall)
	ON_NOTIFY(LVN_DELETEITEM, IDL_BGSN, OnDeleteitemBgs)
	ON_NOTIFY(NM_CLICK, IDL_ABFALL_VJN, OnClickAbfallVorjahr)
	ON_NOTIFY(NM_RCLICK, IDL_ABFALL_VJN, OnRclickAbfallVorjahr)
	ON_NOTIFY(NM_RCLICK, IDL_ABFALLN, OnRclickAbfall)
	ON_NOTIFY(NM_RCLICK, IDL_BGSN, OnRclickBgs)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDB_WEITER, OnWeiter)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDoAbgleich message handlers

BOOL CDoAbgleich::OnInitDialog()
{       
	CDialog::OnInitDialog();
	
// 	TODO: Add extra initialization here
//	Spaltennamen der Listen setzen: zuerst Abfallliste
	for (int iItem = 0; iItem < iColumnsCount; iItem++)
	{
		ASSERT (NULL != szColumnsField [iItem]);
		if (m_lbAbfall.InsertColumn (iItem, szColumnsField [iItem]) != iItem)
			AfxThrowMemoryException ();
	}

//	Abfallliste Vorjahr
	for (iItem = 0; iItem < iColumnsCount; iItem++)
	{
		ASSERT (NULL != szColumnsField [iItem]);
		if (m_lbAbfallVJ.InsertColumn (iItem, szColumnsField [iItem]) != iItem)
			AfxThrowMemoryException ();
	}

//	Bgs
	for (iItem = 0; iItem < iColumnsCount; iItem++)
	{
		ASSERT (NULL != szColumnsField [iItem]);
		if (m_lbBgs.InsertColumn (iItem, szColumnsField [iItem]) != iItem)
			AfxThrowMemoryException ();
	}

//	Attribute der Listen setzen
//  Selektion "beibehalten" setzen
	long lAttr = :: GetWindowLong (m_lbAbfall.m_hWnd, GWL_STYLE);
	:: SetWindowLong (m_lbAbfall.m_hWnd, GWL_STYLE, lAttr | LVS_SHOWSELALWAYS);

	lAttr = :: GetWindowLong (m_lbAbfallVJ.m_hWnd, GWL_STYLE);
	:: SetWindowLong (m_lbAbfallVJ.m_hWnd, GWL_STYLE, lAttr | LVS_SHOWSELALWAYS);
	
	lAttr = :: GetWindowLong (m_lbBgs.m_hWnd, GWL_STYLE);
	:: SetWindowLong (m_lbBgs.m_hWnd, GWL_STYLE, lAttr | LVS_SHOWSELALWAYS);

//	Spaltenbreiten für alle setzen
	for (iItem = 0; iItem < iColumnsCount; iItem++)
	{
		VERIFY (m_lbAbfall.SetColumnWidth (iItem, LVSCW_AUTOSIZE_USEHEADER));
		VERIFY (m_lbAbfallVJ.SetColumnWidth (iItem, LVSCW_AUTOSIZE_USEHEADER));
		VERIFY (m_lbBgs.SetColumnWidth (iItem, LVSCW_AUTOSIZE_USEHEADER));
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}                     

void CDoAbgleich::OutputUserInfo (UINT uiID)
{                                          
	ASSERT (uiID > 0);
	CString strInfo;
	VERIFY (strInfo.LoadString (uiID));
	m_stAction.SetWindowText (strInfo);
}

//	Felder "Bearbeitet" und "Prioritaet" erzeugen
void CDoAbgleich::CreateFields (CDatabase *pDB, const CString& strTable)
{
	ASSERT (NULL != pDB && pDB -> IsOpen ());
	ASSERT (!strTable.IsEmpty ());

//	Feld "Bearbeitet" ggf. erzeugen
	CString strField, strSQL, strFieldExpr;
	VERIFY (strField.LoadString (IDS_BEARBEITET_FIELDNAME));

	CColumns Set (pDB);	
	Set.m_strTableNameParam = strTable;		
	Set.Open ();
	if (!Set.FieldExists (strField, SQL_BIT))
	{
		strFieldExpr = strField + " BIT";
		AfxFormatString2 (strSQL, IDS_ALTER_TABLE, strTable, strFieldExpr);
		pDB->ReplaceBrackets ((char *)(const char*)strSQL);
		pDB->ExecuteSQL (strSQL);
	}

//	Feld "Prioritaet" ggf. erzeugen
	VERIFY (strField.LoadString (IDS_PRIO_FIELDNAME));
	Set.MoveFirst ();
	if (!Set.FieldExists (strField, SQL_VARCHAR, 1))
	{
		strFieldExpr = strField + " varchar (1)";
		AfxFormatString2 (strSQL, IDS_ALTER_TABLE, strTable, strFieldExpr);
		pDB->ReplaceBrackets ((char *)(const char*)strSQL);
		pDB->ExecuteSQL (strSQL);
	}

//	Set schließen
	if (Set.IsOpen ())
		Set.Close ();
}

//	Filter anhängen
void AppendFilter (CString &strFilter, const CString& strExtension)
{
	// JG 990302 nichts anhängen ermöglichen
	if (strExtension.IsEmpty ())
		return; 

	if (strFilter.IsEmpty ())
		strFilter = strExtension;
	else
		strFilter += " AND " + strExtension;
}

BOOL CDoAbgleich::InitSets (void)
{       
	try
	{
		CWaitCursor wc;	
		ASSERT (NULL != m_pFoxProDatabase);
		ASSERT (m_pFoxProDatabase -> IsOpen ());

	//	Ausgabetabelle erstellen/öffnen   
		ASSERT (!m_strOutputTable.IsEmpty ());      
		OutputUserInfo (IDS_CREATE_OUTPUT_TABLE);
		if (!m_bAbfallAppend)
		{
		//	CreateString zusammenbauen		      
			char *pSQLText = OutputResourceTemplate (IDS_CREATE_TABLE);
			CString strCreateSQL;			    			
			AfxFormatString2 (strCreateSQL, IDS_CREATE_TABLE_TEXT, m_strOutputTable, pSQLText);
			DELETE_VEC (pSQLText);		 				
			m_pFoxProDatabase->ExecuteSQL (strCreateSQL);
			
		//	Indizes erzeugen                        
			AfxFormatString1 (strCreateSQL, IDS_INDEX_REGNR, m_strOutputTable);
			m_pFoxProDatabase->ExecuteSQL (strCreateSQL);
			AfxFormatString1 (strCreateSQL, IDS_INDEX_ABFART, m_strOutputTable);
			m_pFoxProDatabase->ExecuteSQL (strCreateSQL);
		}				
		else
			CreateFields (m_pFoxProDatabase, m_strOutputTable);

	//	Ausgabeset öffnen
		m_pOutputSet = new COutputSet (m_pFoxProDatabase);
		m_pOutputSet -> m_strTableName = m_strOutputTable;		
		m_pOutputSet -> Open (CRecordset::snapshot, NULL, CRecordset::appendOnly);			
		
	//	ggf. Erzeugerliste erstellen/öffnen
		if (!m_strErzListe.IsEmpty ())
		{                               
			OutputUserInfo (IDS_CREATE_ERZLISTE);
			if (!m_bErzListeAppend)	
			{                       
			//	CreateString zusammenbauen		      
				CString strCreate, strCreateSQL;
				VERIFY (strCreate.LoadString (IDS_CREATE_ERZLISTE_TABLE));
				AfxFormatString2 (strCreateSQL, IDS_CREATE_TABLE_TEXT, m_strErzListe, strCreate);
				m_pFoxProDatabase->ExecuteSQL (strCreateSQL);
			}
			
		//	zugeh. Set öffnen			
			m_pErzListeSet = new CErzListeSet (m_pFoxProDatabase);
			m_pErzListeSet -> m_strTableName = m_strErzListe;
			m_pErzListeSet -> Open (CRecordset::snapshot, NULL, CRecordset::appendOnly);										
		}
	
	//	Abfartenset erstellen
		OutputUserInfo (IDS_READ_ABFART_TABLE);
		
	//	Struktur der Tabelle ok       
		CString strTable;
		VERIFY (strTable.LoadString (IDS_ABFART_TABLE));                  
		if (!TableOK (m_pFoxProDatabase, strTable, pAbfArtenTable, IDS_ABFARTEN_TABLE_ERROR, TRUE))
			AfxThrowUserException ();
		m_pAbfArtenSet = new CAbfartSet (m_pFoxProDatabase);					
		m_pAbfArtenSet -> Open (CRecordset::forwardOnly, NULL, CRecordset::readOnly);			

	//	alle Abfallarten in Map einlesen
		m_pAbfArtenMap = new CAbfallArtenMap;
		while (!m_pAbfArtenSet -> IsEOF ())
		{
			m_pAbfArtenMap -> AddAbfallArt (m_pAbfArtenSet->m_strAbfallArt,
									        m_pAbfArtenSet->m_dDichte,m_pAbfArtenSet->m_bSonderAbfall);
			m_pAbfArtenSet -> MoveNext ();
		}
		DELETE_OBJ (m_pAbfArtenSet);		// wird nicht mehr gebraucht

	//	Abfallset öffnen
		OutputUserInfo (IDS_READ_ABFALL_TABLE);
		ASSERT (!m_strAbfallTable.IsEmpty ());			
		CreateFields (m_pFoxProDatabase, m_strAbfallTable);
		m_pAbfallSet = new CAbfallSet (m_pFoxProDatabase);
		m_pAbfallSet -> m_strTableName = m_strAbfallTable;

	//	Filter erweitern: Nicht Bearbeiteten und min. Menge ber.
		CString strTemp, strMengenFormat;
		if (0 == m_iModus)
		{
			// JG hier müsste der Filter parametrisiert werden
			VERIFY(strTemp.LoadString (IDS_NOT_BEARBEITET));
			AppendFilter (m_pAbfallSet->m_strFilter, strTemp);

		//	min. Menge
			VERIFY (strMengenFormat.LoadString (IDS_MENGEN_FILTER));
			strTemp.Format (strMengenFormat, m_dMinMengeRec);
			AppendFilter (m_pAbfallSet->m_strFilter, strTemp);
		}
		
	//	Set für akt. Arbeit öffnen			        
		m_pAbfallSet->Open (CRecordset::snapshot);								

	//	Abfallset öffnen (Vorjahr)
		OutputUserInfo (IDS_READ_ABFALL_TABLEVJ);

		if (1 == m_iModus)
			m_strAbfallTableVJ = m_strOutputTable;
		
		ASSERT (!m_strAbfallTableVJ.IsEmpty ());			
		CreateFields (m_pFoxProDatabase, m_strAbfallTableVJ);
		m_pAbfallSetVJ = new CAbfallSet (m_pFoxProDatabase);
		m_pAbfallSetVJ -> m_strTableName = m_strAbfallTableVJ;

	//	Filter erweitern: Nicht Bearbeiteten und min. Menge ber.
		if (0 == m_iModus)
		{
			// AppendFilter (m_pAbfallSetVJ->m_strFilter, strTemp); --> spielt hier keine Rolle
			VERIFY(strTemp.LoadString (IDS_NOT_BEARBEITET));
			AppendFilter (m_pAbfallSetVJ->m_strFilter, strTemp);
		}

	//	Set für akt. Arbeit öffnen			        
		m_pAbfallSetVJ->Open (CRecordset::snapshot);								
	
	//	BgsSet
		ASSERT (NULL != m_pMdbDatabase);
		ASSERT (m_pMdbDatabase -> IsOpen ());
		ASSERT (!m_strBgsTable.IsEmpty ()); 
		OutputUserInfo (IDS_READ_ABFALLBGS_TABLE);				
		CreateFields (m_pMdbDatabase, m_strBgsTable);
		m_pBgsSet = new CBgsSet (m_pMdbDatabase);
		m_pBgsSet -> m_strTableName = m_strBgsTable;			            

	//	Filter erweitern: Nicht Bearbeiteten und min. Menge ber.
		if (0 == m_iModus)
		{
			AppendFilter (m_pBgsSet->m_strFilter, strTemp);	

		//	min. Menge
			VERIFY (strMengenFormat.LoadString (IDS_MENGE_BGS_FILTER));
			strTemp.Format (strMengenFormat, m_dMinMengeRec);
			AppendFilter (m_pBgsSet->m_strFilter, strTemp);	

		//	ggf. Priorität anhängen
			strTemp.Empty ();
			if (0 == m_iPrioritaet)
				VERIFY (strTemp.LoadString (IDS_FILTER_PRIO123));
			else
				if (1 == m_iPrioritaet)
					VERIFY (strTemp.LoadString (IDS_FILTER_PRIO23));

			if (!strTemp.IsEmpty ())
				AppendFilter (m_pBgsSet->m_strFilter, strTemp);	
		}
		
	//	für akt. Arbeit öffnen			        
		m_pBgsSet -> Open (CRecordset::snapshot);					
	
	//	Art der Tabelle bestimmen (evtl. Erzeugerliste) 	            
		ASSERT (!m_strErzeugerTable.IsEmpty ());                  

		if (0 == m_iModus)
			m_bInputFromListe = TableOK (m_pFoxProDatabase, m_strErzeugerTable, pErzListeTable, 
										 IDS_ERZLISTE_TABLE_ERROR, FALSE);
		else
			m_bInputFromListe = FALSE;

	//	Erzeugerset erzeugen
		OutputUserInfo (IDS_READ_ERZ_TABLE);
		CString strBilanzTable;
		if (0 == m_iModus)
			strBilanzTable = m_bInputFromListe ? m_strErzeugerTable : m_strAbfallTable;
		else
			strBilanzTable = m_strOutputTable;
	
	//	Filter zusammenbauen
	
		CString strErzFilter, strMengenFilter;
	/*	if (0 == m_iModus)
		{
			VERIFY (strMengenFormat.LoadString (m_bInputFromListe ? IDS_MENGE_FROM_LISTE :
																	IDS_MENGE_FROM_BILANZ));
			strMengenFilter.Format (strMengenFormat, (const char *)strBilanzTable, m_dMinMengeRec);
		}
	*/				

	//	ggf. Tabelle für der Erzeuger/Abfälle aus BGS erstellen 		
		CreateBgsErzAbfTable ();
		
	//	ggf. Erzeuger-Filter zusammenbauen
	//  JG jetzt als Filterobjekt
	CAbgleichCntSetFilter filter(	m_bOnlyThisErzeuger,
									m_strLastErzeuger,
									m_strLastAsn,
									m_bOnlySonderAbfall,
									m_iModus
								);
	//	Set erzeugen
		CString strTableBgs;
		VERIFY (strTableBgs.LoadString (IDS_BGS_ERZABF_TABLE));
	//	JG angepaßter c'stor
		m_pErzeugerSet = new CAbgleichCntSet (m_pFoxProDatabase,
											  m_strErzeugerTable, strBilanzTable, 
											  strTableBgs,
											  filter);  

		if (NULL == m_pErzeugerSet)	// JG Memchecking
			return FALSE;

	//	Erzeugerset öffnen		
		m_pErzeugerSet -> Open (CRecordset::snapshot, NULL, CRecordset::readOnly);			
		
	//	Erzeuger zählen
		if (!m_pErzeugerSet -> IsEOF ())
		{
			m_lMaxErzCnt = m_pErzeugerSet -> GetRecordCount (TRUE);
			m_ctProgress.SetRange (0, (UINT) m_lMaxErzCnt);

		//	ggf. Suche Erzeuger bzw. ASN-Nr.
			if (!m_strLastErzeuger.IsEmpty ())
			{
			//	Meldung an Nutzer
				CString strT;
				AfxFormatString1 (strT, IDS_SEARCH_ERZ, m_strLastErzeuger);
				m_stAction.SetWindowText (strT);

			//	Erzeuger/ASN suchen
				for (; !m_pErzeugerSet->IsEOF (); m_pErzeugerSet->MoveNext ())
				{
					m_lActErzCnt++;

					if (m_pErzeugerSet->m_strErzNr == m_strLastErzeuger)
					{						
						if (m_strLastAsn.IsEmpty ())
							break;
						else
						{
							if (m_pErzeugerSet->m_strAsn == m_strLastAsn)
								break;
						}
					}
				}
				m_lActErzCnt--;

			//	wenn nicht gefunden, Meldung an Nutzer und zurück
				if (m_pErzeugerSet->IsEOF ())
				{
					VERIFY (strT.LoadString (IDS_NOT_FOUND));
					OutputInfo (strT);					
					return FALSE;
				}
			}
		}
		else
		{
		//	Info an Nutzer ausgeben und zurück			
			CString strInfo;
			VERIFY (strInfo.LoadString (0==m_iModus ? 
					IDS_NO_ABGL_RECORDS : IDS_NO_KONTRL_RECORDS));		
			OutputInfo (strInfo);					
			return FALSE;
		}			
		
	//	richtigen ErzeugerInfoset öffnen
		if (0 == m_iModus)
		{
			if (!m_bInputFromListe && !m_strErzListe.IsEmpty ())
				m_pErzeugerInfoSet = new CErzeugerSetErzeugerListe (m_pFoxProDatabase);
			else                            
				if (m_bInputFromListe && m_strErzListe.IsEmpty ())
					// m_pErzeugerInfoSet = new CErzeugerSetListeOhne (m_pFoxProDatabase);
					m_pErzeugerInfoSet = new CErzeugerSetListeListe (m_pFoxProDatabase);
				else
					if (m_bInputFromListe && !m_strErzListe.IsEmpty ())
						m_pErzeugerInfoSet = new CErzeugerSetListeListe (m_pFoxProDatabase);
					else
						m_pErzeugerInfoSet = new CErzeugerSetErzeugerListe (m_pFoxProDatabase);
			
			m_pErzeugerInfoSet -> m_strTableName = m_strErzeugerTable;		                                  
			if (m_bInputFromListe)
				m_pErzeugerInfoSet -> Open (CRecordset::snapshot);
			else				
				m_pErzeugerInfoSet -> Open (CRecordset::snapshot, NULL, CRecordset::readOnly);						
		}
	}
	catch (CUserException *ue)
	{
		ue -> Delete ();
	}
	catch (CException *e)
	{
		e -> ReportError ();
		throw;
	}
	
    return TRUE;		
}

void CDoAbgleich::OnCancel()
{                 
	if (m_bInAction)
		m_bUserBreak = TRUE;
	else		  
	{
	//	beim Nutzer nachfragen
		CString strQuestion;
		VERIFY (strQuestion.LoadString ((0 == m_iModus) ? IDS_SAVE_STATUS : IDS_SAVE_STATUS_C));		
		if (IDYES == MessageBox (strQuestion, AfxGetAppName (), MB_ICONQUESTION | MB_YESNO))
			SaveStatus ();

		CDialog::OnCancel();
	}		
}   

void CDoAbgleich::ResetControlValues ()
{
/*
	if (0 == m_iModus)
		m_stMenge.SetWindowText ("");
*/
	CString strCaption; 
	VERIFY (strCaption.LoadString (0 == m_iModus ? IDS_SEARCH_CAPTION : 
												   IDS_CONTROL_CAPTION));
	SetWindowText (strCaption);
}	

void CDoAbgleich::OnOK()
{
	// TODO: Add extra validation here
	// CDialog::OnOK();
	if (TRUE == m_bNotInit)
	{
		m_bNotInit = FALSE;                           
		
	//	Buttons deaktivieren		
		m_btOk.EnableWindow (FALSE);
		m_btEscape.EnableWindow (FALSE);
		m_btInListe.EnableWindow (FALSE); 
		m_btHelp.EnableWindow (FALSE); 
		m_btErzInfo.EnableWindow (FALSE); 
		m_btWeiter.EnableWindow (FALSE);
		GetDlgItem (IDCANCEL) -> EnableWindow (FALSE);		
		
		if (!InitSets ())
		{
			CDialog::EndDialog (IDCANCEL);
			return;			
		}			
		
		CString strText;
		VERIFY (strText.LoadString (IDS_UEBERNEHMEN));
		m_btOk.SetWindowText (strText);
		GetDlgItem (IDCANCEL) -> EnableWindow (TRUE);		
	}   
	else                       
	{//	Datensätze ausgeben                      
		ASSERT (NULL != m_pAbfallMap);	
		ASSERT (NULL != m_pBgsMap);
		ASSERT (NULL != m_pOutputSet);
		ASSERT (m_pOutputSet -> IsOpen ());
		ASSERT (NULL != m_pErzeugerSet);
		ASSERT (m_pErzeugerSet->IsOpen());
		
		m_btOk.EnableWindow (FALSE);
		if (m_pAbfallMap -> OutputInSet (m_pOutputSet, m_pErzeugerSet->m_strErzNr, TRUE, m_stAction, m_lOutputCnt))
			m_pBgsMap -> OutputInSet (m_pOutputSet, m_pErzeugerSet->m_strErzNr, TRUE, m_stAction, m_lOutputCnt);
		SetBearbeitet ();			
        
        ResetControlValues ();
	}
		                
//	nächsten Erzeuger lesen		                
	ReadNextErzeuger ();		
}                   

void CDoAbgleich::OnEscape()
{
	try
	{
		ResetControlValues ();

	//	die ausgelassenen hinzunehmen
		if (0 == m_iModus)
		{
			m_lEscCnt += m_lbAbfall.GetItemCount ();
			SetBearbeitet ();			
		}
		else
		{
			if (0 == m_lDirtyCnt)
				m_lEscCnt += m_lbAbfallVJ.GetItemCount ();
			else
			{
			//	lösche alle Sätze im aktuellen Set
				CWaitCursor wc;
				CString strInfo;
				VERIFY (strInfo.LoadString (IDS_DELETE_RECORDS));
				m_stAction.SetWindowText (strInfo);		
	
				ASSERT (m_pErzeugerSet && m_pErzeugerSet->IsOpen ());
				ASSERT (!m_pErzeugerSet->m_strErzNr.IsEmpty ());
				ASSERT (!m_pErzeugerSet->m_strAsn.IsEmpty ());
				ASSERT ((NULL != m_pAbfallSetVJ) && m_pAbfallSetVJ->IsOpen ());

			//	alle Datensätze löschen
				CString strWhere;
				AfxFormatString2 (strWhere, IDS_ERZNR_ASN_FILTER, m_pErzeugerSet->m_strErzNr,
																  m_pErzeugerSet->m_strAsn);					  
				m_pAbfallSetVJ->DeleteAll (strWhere);

			//	alle Datensätze in Set ausgeben
				long lDummy = 0;	
				ASSERT (m_pOutputSet && m_pOutputSet->IsOpen ());
				m_pAbfallMapVJ -> OutputInSet (m_pOutputSet, m_pErzeugerSet->m_strErzNr, 
											   FALSE,	//	alle Datensätze
											   m_stAction, lDummy, FALSE);

				m_lOutputCnt += m_lDirtyCnt;
			}				
		}
	}
	catch (CException *e)
	{
		e->ReportError ();
		e->Delete ();
	}
	
//	nächsten Erzeuger lesen		                
	ReadNextErzeuger ();		
}              

//	Ausgabe der Erzeugerabfälle in Erzeugerliste	
void CDoAbgleich::OnInListe()
{
	// TODO: Add your control notification handler code here
	m_btInListe.EnableWindow (FALSE);				
	
//	prüfe Parameter	    
	ASSERT ((NULL != m_pErzeugerSet) && m_pErzeugerSet->IsOpen ());
	ASSERT (!m_pErzeugerSet->m_strErzNr.IsEmpty ());

	if (0 == m_iModus)
	{
		ASSERT (NULL != m_pErzeugerInfoSet && m_pErzeugerInfoSet -> IsOpen ());
		ASSERT (NULL != m_pAbfallMap);
		ASSERT (NULL != m_pBgsMap);	                                                 

	//	Ausgabe der selektierten Sätze in Erzeugerliste	
		m_pErzListeSet -> Output (m_pErzeugerSet->m_strErzNr,m_pErzeugerSet->m_strAsn, m_pErzeugerInfoSet,
								 m_pAbfallMap, m_pBgsMap, m_stAction, m_lInListeCnt);
	}
	else
	{
		ASSERT (NULL != m_pOutputSet && m_pOutputSet -> IsOpen ());
		ASSERT (NULL != m_pAbfallSetVJ && m_pAbfallSetVJ -> IsOpen ());
		ASSERT (!m_pErzeugerSet->m_strErzNr.IsEmpty ());
		ASSERT (!m_pErzeugerSet->m_strAsn.IsEmpty ());

	//	lösche alle Sätze im aktuellen Set
		CWaitCursor wc;
		CString strInfo;
		VERIFY (strInfo.LoadString (IDS_DELETE_RECORDS));
		m_stAction.SetWindowText (strInfo);		
		CString strWhere;
		AfxFormatString2 (strWhere, IDS_ERZNR_ASN_FILTER, m_pErzeugerSet->m_strErzNr,
														  m_pErzeugerSet->m_strAsn);					  
		m_pAbfallSetVJ->DeleteAll (strWhere);
		
	//	Zähler setzen
		m_lInListeCnt += m_lbAbfallVJ.GetSelectedCount ();

	//	Selektion umkehren
		// m_pAbfallMapVJ -> ReverseSelection ();

	//	selektierten ausgeben
		long lDummy = 0;
		m_pAbfallMapVJ -> OutputInSet (m_pOutputSet, m_pErzeugerSet->m_strErzNr, TRUE, 
									   m_stAction, lDummy, TRUE);
	}
	
	ResetControlValues ();	
	
//	nächsten Erzeuger lesen		                
	ReadNextErzeuger ();		
}

void CDoAbgleich::SetSummenMenge()
{
	int iCnt = m_lbAbfall.GetSelectedCount()+m_lbBgs.GetSelectedCount();

	m_btOk.EnableWindow (iCnt > 0);
	m_btWeiter.EnableWindow (iCnt > 0);

	if (1 == m_iModus)
	{
	//	hier die Löschtaste
		m_btInListe.EnableWindow (m_lbAbfallVJ.GetSelectedCount() > 0);
	}
	else
	{
		m_btInListe.EnableWindow (m_pErzListeSet && (iCnt > 0));
	}
}
                    
//	nächsten Erzeuger lesen		                                  
BOOL CDoAbgleich::ReadNextErzeuger ()
{       
	BOOL bRet = TRUE;
	m_bInAction = TRUE;
	
	TRY
	{  
		CWaitCursor wc;
		                   
	//	prüfe alle Variablen
		ASSERT (NULL != m_pErzeugerSet);
		ASSERT (m_pErzeugerSet -> IsOpen ());
		ASSERT (NULL != m_pAbfArtenMap);
		ASSERT (NULL != m_pAbfallSet);
		ASSERT (m_pAbfallSet -> IsOpen ());			
		ASSERT (NULL != m_pAbfallSetVJ);
		ASSERT (m_pAbfallSetVJ -> IsOpen ());			
		ASSERT (NULL != m_pBgsSet);
		ASSERT (m_pBgsSet -> IsOpen ());			
		ASSERT (NULL != m_pOutputSet);
		ASSERT (m_pOutputSet -> IsOpen ());			
		                          
	//	Controls setzen			                          
		m_btOk.EnableWindow (FALSE);    
		m_btEscape.EnableWindow (FALSE);
		m_lbAbfall.EnableWindow (FALSE);
		m_lbBgs.EnableWindow (FALSE);
		m_btHelp.EnableWindow (FALSE);
		m_btErzInfo.EnableWindow (FALSE);
		m_btWeiter.EnableWindow (FALSE);	// JG weiterschalten
		if (m_pErzListeSet)
			m_btInListe.EnableWindow (FALSE);

	//	einen Satz weiter
		if (m_bMoveInit)
			m_bMoveInit = FALSE;
		else
		{
		//	ggf. beenden 

#pragma MSG("JG enable bOnlyThisErzeuger")
			if (m_bOnlyThisErzeuger && (m_pErzeugerSet->m_strErzNr != m_strLastErzeuger))
			{
				CDialog::OnOK();
				return TRUE;
			}
			
			if (!m_pErzeugerSet -> IsEOF ())
				m_pErzeugerSet->MoveNext ();
		}
        
	//	Abgleich durchführen									
		CString strInfo;
		for (; !m_pErzeugerSet -> IsEOF (); m_pErzeugerSet -> MoveNext())
		{
		//	Statusanzeige akt.			
			m_ctProgress.SetPos ((UINT) ++m_lActErzCnt);				
			
		//	prüfe akt. Erzeugernummer
			if (m_pErzeugerSet->m_strErzNr.IsEmpty () || m_pErzeugerSet->m_strAsn.IsEmpty ())
				continue;			        			
		
		//	Abbruch-Taste betätigt ?				
			CallMessageQueue ();
			if (m_bUserBreak)
			{               
			//	beim Nutzer nachfragen 
				CString strQuestion;
				VERIFY (strQuestion.LoadString (0 == m_iModus ? IDS_ABBRUCH : IDS_ABBRUCH_KONTROLLE));		
				if (IDYES == MessageBox (strQuestion, AfxGetAppName (), MB_ICONQUESTION | MB_YESNO))
					break;		
				else
					m_bUserBreak = FALSE;	// normal weiter machen						
			}				
			
		//	Info an Nutzer ausgeben
			AfxFormatString2 (strInfo, IDS_SEARCH_NEXT_ERZ, 
							  m_pErzeugerSet->m_strErzNr, m_pErzeugerSet->m_strAsn);				
			m_stAction.SetWindowText (strInfo);			
				
		//	alten Maps löschen
			DELETE_OBJ (m_pAbfallMapVJ);		
			DELETE_OBJ (m_pAbfallMap);		
			DELETE_OBJ (m_pBgsMap);								

		//	suche Erzeuger in Bgs-Tabelle
			m_pBgsSet->m_strErzNrParam = m_pErzeugerSet->m_strErzNr;
			m_pBgsSet->m_strAsnParam = m_pErzeugerSet->m_strAsn;

		//	zuerst Map anlegen
			m_pBgsMap = new CAbfallMap (m_pAbfArtenMap, &m_lbBgs, m_bOnlySonderAbfall, m_dMinMengeRec);			                        
		
			if (m_pBgsSet -> Requery ())
			{   
				if (!m_pBgsSet -> IsEOF () && BgsPrioOk () && GesBgsMengeOk ())
				{
				//	map füllen        			
					do
					{
						m_pBgsMap -> AddInfo (m_pBgsSet->m_strAbfallschluesselnummer, 
											  m_pBgsSet->m_strBefoerderernummer,
											  m_pBgsSet->m_strEntsorgernummer,
										  	  m_pBgsSet->m_dMenge,m_pBgsSet->m_dMenge_en,
											  m_pBgsSet->m_strNachweisnummer,
											  m_pBgsSet->m_strEntsorgungsverfahren,
											  m_pBgsSet->m_strPrioritaet,
											  CString(""),
											  CString("")
												);					
						m_pBgsSet -> MoveNext ();
					}
					while (!m_pBgsSet -> IsEOF ());
				}						
			}		

		//	Beim Abgleich müssen für Priorität 0 oder 1 immer Referenzdatensätze vorhanden sein
			if ((0 == m_iModus) && ((0 == m_iPrioritaet) || (1 == m_iPrioritaet)))
			{
				if (!m_pBgsMap || m_pBgsMap->IsEmpty ())
					continue;
			}
			
		//	suche Erzeuger in Abfall-Tabelle
			m_pAbfallSet -> m_strErzNrParam = m_pErzeugerSet -> m_strErzNr;
			m_pAbfallSet -> m_strAsnParam = m_pErzeugerSet -> m_strAsn;

		//	Map immer erzeugen
			m_pAbfallMap = new CAbfallMap (m_pAbfArtenMap, &m_lbAbfall, m_bOnlySonderAbfall, m_dMinMengeRec);			                        

			if (m_pAbfallSet -> Requery ())			 					
			{   
			//	erfüllt dieser Erzeuger die Gesamtmengeschwelle
				if (!m_pAbfallSet -> IsEOF () && GesAbfMengeOk ())
				{
				//	map füllen  
					do
					{
						m_pAbfallMap -> AddInfo (m_pAbfallSet->m_strAbfallnummer,
												 m_pAbfallSet->m_strTransporteurnummer,
												 m_pAbfallSet->m_strEntsorgernummer,
												 m_pAbfallSet->m_dMenge_t, 0,
												 m_pAbfallSet->m_strNachweisnummer,
												 m_pAbfallSet->m_strEntsorgungsverfahren,
												 m_pAbfallSet->m_strPrioritaet,
												 m_pAbfallSet->m_strEntsorgerBemerkung,
												 m_pAbfallSet->m_strTransportBemerkung
												);					
						m_pAbfallSet -> MoveNext ();					
					}
					while (!m_pAbfallSet -> IsEOF ());
				}
			}					

		//	Mengen vergleichen
			double dAbfallMenge = 0;
			double dBgsMenge = 0;
			if (0 == m_iModus)
			{
				dAbfallMenge = m_pAbfallMap ? m_pAbfallMap -> GetSumMenge () : 0;
				dBgsMenge = m_pBgsMap ? m_pBgsMap -> GetSumMenge () : 0;								
				/*
				if ((0.0 == dAbfallMenge) && (0.0 == dBgsMenge)) 
					// || ((dAbfallMenge < m_dMinMenge) && (dBgsMenge < m_dMinMenge))) 
					continue;
				*/
		
			//	sind die Inhalte der Maps bei wenigstens einer gültigen Menge identisch ?
			//	wenn ja, eine Map in Set ausgeben und weiter
				if ((dAbfallMenge > 0) || (dBgsMenge > 0))
				{
					CAbfallMap *pOutputMap = m_pAbfallMap -> IsEqual (m_pBgsMap);
					if (pOutputMap)
					{
						pOutputMap -> OutputInSet (m_pOutputSet,m_pErzeugerSet->m_strErzNr,FALSE,
												   m_stAction,m_lOutputCnt);
						SetBearbeitet ();														
						continue;
					}
				}
			}
			
		//	suche Erzeuger in Abfall-Tabelle (VJ)
			m_pAbfallSetVJ -> m_strErzNrParam = m_pErzeugerSet -> m_strErzNr;
			m_pAbfallSetVJ -> m_strAsnParam = m_pErzeugerSet -> m_strAsn;

		//	map erzeugen
			m_pAbfallMapVJ = new CAbfallMap (m_pAbfArtenMap, &m_lbAbfallVJ, m_bOnlySonderAbfall, m_dMinMengeRec);			                        

			if (m_pAbfallSetVJ -> Requery ())			 					
			{                                   
				if (!m_pAbfallSetVJ -> IsEOF ())
				{
				//	map füllen  
					do
					{
						m_pAbfallMapVJ -> AddInfo (m_pAbfallSetVJ->m_strAbfallnummer,
												   m_pAbfallSetVJ->m_strTransporteurnummer,
												   m_pAbfallSetVJ->m_strEntsorgernummer,
												   m_pAbfallSetVJ->m_dMenge_t, 0,
												   m_pAbfallSetVJ->m_strNachweisnummer,
												   m_pAbfallSetVJ->m_strEntsorgungsverfahren,
												   m_pAbfallSetVJ->m_strPrioritaet,
												   m_pAbfallSetVJ->m_strEntsorgerBemerkung,
												   m_pAbfallSetVJ->m_strTransportBemerkung
													);
						m_pAbfallSetVJ -> MoveNext ();					
					}
					while (!m_pAbfallSetVJ -> IsEOF ());
				}
			}					

		//	alle 3 Mengen in ListBox ausgeben, die mit größerem Wert immer selektieren					
			BOOL bSelect = FALSE;
			if (0 == m_iModus)
				bSelect = dAbfallMenge >= dBgsMenge;
			m_pAbfallMap -> OutputInListBox (bSelect);
			if (0 == m_iModus)
				m_pBgsMap -> OutputInListBox (bSelect ? FALSE : TRUE);
			else
				m_pBgsMap -> OutputInListBox (FALSE);
			m_pAbfallMapVJ -> OutputInListBox (FALSE);

		//	wenn Keine Einträge, weiter
			int iCnt = m_lbAbfall.GetItemCount()+m_lbAbfallVJ.GetItemCount ()+
					   m_lbBgs.GetItemCount();

			if (0 == iCnt)
				continue;
			
			break;
		}	//	end_for
		
	//	ggf. Dialog mit neuem Erzeuger akt.
		if (!m_bUserBreak && !m_pErzeugerSet -> IsEOF ())
		{
			ShowAktData();
		}						

	}
	CATCH (CMemoryException, me)
	{                    
		bRet = FALSE;		   
		OutputMemoryError ();         
	}
	AND_CATCH (CDBException, db)
	{                          
		bRet = FALSE;		   
		OutputError (db -> m_strError);      
	}                                           
	AND_CATCH (CFileException, fe)
	{                          
		bRet = FALSE;		   
		CString strFileErr;
		VERIFY (strFileErr.LoadString (IDS_FILE_ERROR));
		OutputError (strFileErr);		
	}
	END_CATCH                   	            

	m_btEscape.EnableWindow (TRUE);			//	soll immer gehen
#pragma MSG("HilfeButton ausgeschaltet")
//	m_btHelp.EnableWindow (bRet);			
	m_btErzInfo.EnableWindow (bRet);

//	Controls, die in Abhängigkeit vom Programmzustand gesetzt werden
	if (!bRet)
	{
		m_btInListe.EnableWindow (FALSE);
		m_btWeiter.EnableWindow (FALSE);	// JG weiterschalten
		m_btOk.EnableWindow (FALSE);
		m_lbAbfall.EnableWindow (FALSE);
		m_lbAbfallVJ.EnableWindow (FALSE);
		m_lbBgs.EnableWindow (FALSE);
	}

//	bereit zur Änderung von Daten
	m_lDirtyCnt = 0;

	OutputUserInfo (IDS_BEREIT);		

	m_bInAction = FALSE;
	
	if (m_bUserBreak)
		OnCancel();		
	else
	{
		if (m_pErzeugerSet -> IsEOF ())
			CDialog::OnOK();						
	}		
		
	return bRet;		
}

void CDoAbgleich::OnDestroy() 
{
	VERIFY (m_lbAbfall.DeleteAllItems ());
	VERIFY (m_lbAbfallVJ.DeleteAllItems ());
	VERIFY (m_lbBgs.DeleteAllItems ());
	
	CDialog::OnDestroy();
}
	        
//	auf Item wurde Doppelclick ausgeführt
void CDoAbgleich::ShowSelection(CListCtrl *pList, CAbfallMap *pMap,
								BOOL bStoreChanges)
{    
//	prüfe Parameter			        
	ASSERT (NULL != pList);	
	ASSERT (NULL != pMap);				
	
//	geklickten Item suchen: muß den Focus haben
	int iItem = pList -> GetNextItem (-1, LVIS_FOCUSED);
	if (iItem < 0)
		return;

//	Key des Satzes lesen		
	char *pKey = (char *) pList -> GetItemData (iItem);
	ASSERT (NULL != pKey);
	AfxIsValidString (pKey);
	
//	Key in zugeh. Map verwenden um, vollst. Info zu erhalten	                    
	CAbfallInfo *pInfo = NULL;
	ASSERT (!pMap -> IsEmpty ());
	VERIFY (pMap -> Lookup (pKey, (CObject *&) pInfo));
	ASSERT (NULL != pInfo);
                                
//	Dialog anwerfen          
	CAbfartParams Params (NULL, !bStoreChanges);			                    
	Params.m_dMinMengeRec = m_dMinMengeRec;
	Params.m_strAbfArt = pInfo -> m_strAbfArt;						
	Params.m_strEntsorger = pInfo -> m_strEntsorger;						
	Params.m_strTransp = pInfo -> m_strTransp;						
	Params.m_strNachweis = pInfo -> m_strNachweis;
	Params.m_strVerfahren = pInfo -> m_strVerfahren;
	Params.m_strPrioritaet = pInfo -> m_strPrio;
	Params.m_strMenge.Format (szMengenFormat, pInfo -> m_dMenge); 
	Params.m_strEntsorgerBemerkung = pInfo -> m_strEntsorgerBemerkungen;
	Params.m_strTransportBemerkung = pInfo -> m_strTransporteurBemerkungen;

	if (pMap == m_pAbfallMap) 
		Params.m_strCaption = "Bilanzdaten";
	else 
	if (pMap == m_pAbfallMapVJ) 
		Params.m_strCaption = "Bilanzdaten Vorjahr";
	else
	if (pMap == m_pBgsMap) 
		Params.m_strCaption = "Referenzdaten";
	else
		Params.m_strCaption = "Datensatzinfo";

//	akt. Cursorposition in Screen-Coordinaten lesen
	CPoint pt (0,0);
	::GetCursorPos (&pt);

//	Koordinaten speichern
	// ScreenToClient (&pt);
	Params.m_iPosX = pt.x;
	Params.m_iPosY = pt.y;

	if (IDOK == Params.DoModal () && bStoreChanges)
	{                             
		double dMenge = atof (Params.m_strMenge);
	
		if ((Params.m_strEntsorger != pInfo -> m_strEntsorger) ||
			(Params.m_strTransp != pInfo -> m_strTransp) ||
			(Params.m_strNachweis != pInfo -> m_strNachweis) ||
			(Params.m_strVerfahren != pInfo -> m_strVerfahren) ||
			(Params.m_strPrioritaet != pInfo -> m_strPrio) || 
			(Params.m_strEntsorgerBemerkung != pInfo -> m_strEntsorgerBemerkungen) || 
			(Params.m_strTransportBemerkung != pInfo -> m_strTransporteurBemerkungen) || 
			(dMenge != pInfo -> m_dMenge))					
		{	
		//	alte Info in Map löschen 
			VERIFY (pMap -> RemoveKey (pKey));
			pMap -> GetSumMenge () -= pInfo -> m_dMenge;
			if (pInfo -> m_bIsSelected)
				pMap -> GetSelSumMenge () -= pInfo -> m_dMenge;				

			// DELETE_VEC (pKey);				//	ItemData wird bei Ausgabe der Infos gelöscht
			// pList -> DeleteString (iSel);	--> alten Einträge werden bei Ausgabe aller zuvor gelöscht
		
		//	neue Info in Map ausgeben           
			double dMengeK = 0.0;
			pMap -> AddInfo (pInfo->m_strAbfArt, Params.m_strTransp, Params.m_strEntsorger, 
							 dMenge, pInfo -> m_dMengeEn,
							 Params.m_strNachweis, Params.m_strVerfahren, Params.m_strPrioritaet,
							 pInfo -> m_strEntsorgerBemerkungen,
							 pInfo -> m_strTransporteurBemerkungen,
							 pInfo -> m_bIsSelected);
							 
		//	alte Info jetzt löschen							 
			DELETE_OBJ (pInfo);
			
		//	alle Infos in ListBox ausgeben
			pMap -> OutputInListBox (FALSE, TRUE);

		//  ggf. Selektion in sichtbaren Bereich
			pList -> EnsureVisible (iItem, FALSE);

		// 	Mengen neu anzeigen und Controls setzen
			SetSummenMenge ();

		//	Datensatz hat sich geändert
			m_lDirtyCnt++;
		}			
	}
}   

//	Setze Flag Bearbeitet im übergebenen Set
void CDoAbgleich::SetBearbeitet (CRecordset *pSet, const CString &strWhere)
{
	if (1 == m_iModus)
		return;

//	prüfe übergebene Parameter
	ASSERT (NULL != pSet && pSet -> IsOpen ());
	ASSERT (!strWhere.IsEmpty ());

	try
	{
		CWaitCursor wc;
		CString strSQL;
		AfxFormatString2 (strSQL, IDS_UPDATE_KLAUSEL, pSet->GetTableName(), strWhere);
		pSet->m_pDatabase->ReplaceBrackets (strSQL.GetBuffer(0));
		pSet->m_pDatabase->ExecuteSQL (strSQL);
	}
	catch (CException *e)
	{
		e->ReportError ();
		e->Delete ();
	}
}

//	setze ggf. das Feld "BEARBEITET" in Erzeugerliste, Abfalltabelle, 
//	Abfalltabelle (VJ) und BilanzTabelle
void CDoAbgleich::SetBearbeitet (void)
{
	if (1 == m_iModus)
		return;

	try
	{
		ASSERT (m_pErzeugerSet && m_pErzeugerSet->IsOpen ());
		ASSERT (!m_pErzeugerSet->m_strErzNr.IsEmpty ());
		ASSERT (!m_pErzeugerSet->m_strAsn.IsEmpty ());

	//	ggf. ErzeugerListe modifizieren
		CString strWhere;
		AfxFormatString2 (strWhere, IDS_ERZNR_ASN_FILTER, m_pErzeugerSet->m_strErzNr,
														  m_pErzeugerSet->m_strAsn);					  
	
		if (m_bInputFromListe)
		{
			ASSERT (NULL != m_pErzeugerInfoSet);
			SetBearbeitet (m_pErzeugerInfoSet, strWhere);
		}

	//	BilanzTabelle
		ASSERT (NULL != m_pAbfallSet);
		SetBearbeitet (m_pAbfallSet, strWhere);
		
	//	BilanzTabelle-Vorjahr
		ASSERT (NULL != m_pAbfallSetVJ);
		SetBearbeitet (m_pAbfallSetVJ, strWhere);

	//	Bgstabelle
		ASSERT (NULL != m_pBgsSet);
		AfxFormatString2 (strWhere, IDS_ERZNR_ASNB_FILTER, m_pErzeugerSet->m_strErzNr,
														   m_pErzeugerSet->m_strAsn);					  
		SetBearbeitet (m_pBgsSet, strWhere);
	}   
	catch (...)
	{
		TRACE1 ("Fehler beim akt. der Erzeugerliste '%s'!\n", (const char *)m_pErzeugerSet->m_strErzNr);
        throw;
	}
}
                                
//	aktuellen Programmstand speichern                                
void  CDoAbgleich::SaveStatus ()     
{            
	TRY
	{       
		CWaitCursor wc;
	
		CGakApp *pApp = static_cast<CGakApp *> (AfxGetApp ());
		ASSERT (NULL != pApp);
		ASSERT_VALID (pApp);
		
		CString strSection, strKey;
		VERIFY (strSection.LoadString (IDS_CONFIG));
		               
	//	Name der Erzeugertabelle						               
		VERIFY (strKey.LoadString (IDS_ERZEUGER_KEY));
		ASSERT (! m_strErzeugerTable.IsEmpty ());
		if (! pApp -> SetAbgleichParameter(strSection, strKey, m_strErzeugerTable))
			AfxThrowFileException (CFileException::generic);

	//	Name der Bilanztabelle						               
		VERIFY (strKey.LoadString (IDS_BILANZ_KEY));
		ASSERT (! m_strAbfallTable.IsEmpty ());
		if (! pApp -> SetAbgleichParameter (strSection, strKey, m_strAbfallTable))
			AfxThrowFileException (CFileException::generic);

	//	Name der Bilanztabelle Vorjahr: bei der Datenkontrolle 
	//	wird dieser Name überschrieben						               
		if (0 == m_iModus)
		{
			VERIFY (strKey.LoadString (IDS_BILANZ_KEY_VJ));
			if (! pApp -> SetAbgleichParameter (strSection, strKey, 
				m_strAbfallTableVJ.IsEmpty () ? "" : m_strAbfallTableVJ))
				AfxThrowFileException (CFileException::generic);
		}
	
	//	Name der BGS-Tabelle						               
		VERIFY (strKey.LoadString (IDS_BGS_KEY));
		ASSERT (! m_strBgsTable.IsEmpty ());
		if (! pApp -> SetAbgleichParameter (strSection, strKey, m_strBgsTable))
			AfxThrowFileException (CFileException::generic);				
			
	//	Name der Ausgabe-Tabelle						               
		VERIFY (strKey.LoadString (IDS_OUTPUT_KEY));
		ASSERT (! m_strOutputTable.IsEmpty ());
		if (! pApp -> SetAbgleichParameter (strSection, strKey, m_strOutputTable))
			AfxThrowFileException (CFileException::generic);								
	
	//	Namen der Erzeugerliste
		VERIFY (strKey.LoadString (IDS_ERZLIST_KEY));
		if (! pApp -> SetAbgleichParameter (strSection, strKey, m_strErzListe.IsEmpty () ? 
															  "" : m_strErzListe))
			AfxThrowFileException (CFileException::generic);								
		
	//	akt. Erzeuger
		VERIFY (strKey.LoadString (IDS_ERZNAME_KEY));
		CString strErzeuger, strAsn;
		if (m_pErzeugerSet && m_pErzeugerSet -> IsOpen ())
		{
			strErzeuger = m_pErzeugerSet -> m_strErzNr;
			strAsn = m_pErzeugerSet -> m_strAsn;
		}
		else
		{
			strErzeuger = m_strLastErzeuger;
			strAsn = m_strLastAsn;
		}
		if (! pApp -> SetAbgleichParameter (strSection, strKey, strErzeuger.IsEmpty () ?
															  "" : strErzeuger))
			AfxThrowFileException (CFileException::generic);										

	//	akt. Asn
		VERIFY (strKey.LoadString (IDS_ASN_KEY));
		if (! pApp -> SetAbgleichParameter (strSection, strKey, strAsn.IsEmpty () ?
															  "" : strAsn))
			AfxThrowFileException (CFileException::generic);											

	//	zugeh. Flag
		VERIFY (strKey.LoadString (IDS_ONLY_THIS_ERZ_KEY));	
		if (! pApp -> SetAbgleichParameter (strSection, strKey, m_bOnlyThisErzeuger))
			AfxThrowFileException (CFileException::generic);															    

	 //	Nur Sonderabfälle-Flag	    
		VERIFY (strKey.LoadString (IDS_ONLY_SONDER_ABFALL_KEY));					    
		if (! pApp -> SetAbgleichParameter (strSection, strKey, m_bOnlySonderAbfall))
			AfxThrowFileException (CFileException::generic);															    
			
	//	Mengenschwelle
		VERIFY (strKey.LoadString (IDS_MENGEN_SCHWELLE_KEY));					    
		CString strTemp;
		strTemp.Format (szMengenFormat, m_dMinMenge);
		if (! pApp -> SetAbgleichParameter (strSection, strKey, strTemp))
			AfxThrowFileException (CFileException::generic);															    													

	//	Satzmengenschwelle
		VERIFY (strKey.LoadString (IDS_MENGEN_SCHWELLE_KEY_REC));					    
		strTemp.Format (szMengenFormat, m_dMinMengeRec);
		if (! pApp -> SetAbgleichParameter (strSection, strKey, strTemp))
			AfxThrowFileException (CFileException::generic);															    													

	//	Modus
		VERIFY (strKey.LoadString (IDS_MODUS_KEY));					    
		if (! pApp -> SetAbgleichParameter (strSection, strKey, m_iModus))
			AfxThrowFileException (CFileException::generic);															    

	//	Prioritaet
		VERIFY (strKey.LoadString (IDS_PRIO_KEY));					    
		if (! pApp -> SetAbgleichParameter (strSection, strKey, m_iPrioritaet))
			AfxThrowFileException (CFileException::generic);															    
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

void CDoAbgleich::OnHelp()
{
	// TODO: Add your control notification handler code here
	AfxGetApp () -> WinHelp (IDD);		
}

/*
BOOL CDoAbgleich::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	// TODO: Add your message handler code here and/or call default
	ASSERT (pHelpInfo != NULL);
	if (pHelpInfo -> dwContextId)
		AfxGetApp () -> WinHelp (pHelpInfo -> dwContextId, HELP_CONTEXTPOPUP);

	return TRUE;
}
*/

void CDoAbgleich::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	OnCancel ();
}

void CDoAbgleich::OnErzInfo() 
{
	// TODO: Add your control notification handler code here
	try
	{
/*		CWaitCursor wc;	
		ASSERT (NULL != m_pFoxProDatabase);
		ASSERT (m_pFoxProDatabase -> IsOpen ());
		ASSERT (!m_strErzeugerTable.IsEmpty ());
		ASSERT (NULL != m_pErzeugerSet);
		ASSERT (!m_pErzeugerSet->m_strErzNr.IsEmpty ());

	//	Set Öffnen
		CErzeugerSetErzeugerListe Set (m_pFoxProDatabase);
		Set.m_strTableName = m_strErzeugerTable;
		Set.Open (CRecordset::snapshot, NULL, CRecordset::readOnly);
		Set.m_strErzNrParam = m_pErzeugerSet->m_strErzNr;
		Set.Requery ();

		if (Set.IsEOF ())
		{
			CString strInfo;
			AfxFormatString1 (strInfo, IDS_ERZEUGER_NOT_FOUND, m_pErzeugerSet->m_strErzNr);
			OutputInfo (strInfo);
			Set.Close ();
			return;
		}				

		CErzInfo Dlg (this);
		Dlg.m_strErzNr = m_pErzeugerSet->m_strErzNr;
		Dlg.m_strAnfOrt = Set.m_strOrtAnfall;
		Dlg.m_strAnf = Set.m_strBezAnfall;
		Dlg.m_strFax = Set.m_strFaxAnspr;
		CString strBranche;
		m_ctrlBranchennummer.GetWindowText(strBranche);
		Dlg.m_strBranche = strBranche; // Set.m_strBranche;
		Dlg.m_strPartner =  Set.m_strAnspr;
		Dlg.m_strTel = Set.m_strTelAnspr;
		Dlg.DoModal ();
		
		if (Set.IsOpen ())
			Set.Close ();
	}
	catch (CException *e)
	{
		e -> ReportError ();
		e -> Delete ();
	}		*/

		CDaoDatabase* pDatabase = NULL;
		if (NULL != g_pErzSet)
			pDatabase = g_pErzSet->m_pDatabase;

		CGakSet set(pDatabase);
		set.Open();
		COleVariant VarNr (m_pErzeugerSet->m_strErzNr, VT_BSTRT);
		set.Seek("=", &VarNr);

		if (m_pErzeugerSet->m_strErzNr != set.m_Nummer)
		{
			CString strText;
			VERIFY(strText.LoadString(IDS_NO_REC_FOUND));
			AfxMessageBox(strText);
			return;
		}
//		set.MoveExt("=", AFX_DAO_NEXT, m_pErzeugerSet->m_strErzNr);
	
//		set.SearchNummer();

		CErzInfo Dlg (this);
		CString strBranche;
		m_ctrlBranchennummer.GetWindowText(strBranche);
		Dlg.m_strBranche = set.m_Branchennummer; //    strBranche; // Set.m_strBranche;
		Dlg.m_strErzNr = set.m_Nummer;
		Dlg.m_strAnfOrt = set.m_Ortsname;
		Dlg.m_strAnf = set.m_Anfallstelle;
		Dlg.m_strFax = set.m_Partnertelefax;
		Dlg.m_strPartner =  set.m_Ansprechpartner;
		Dlg.m_strTel = set.m_Partnertelefon;
		Dlg.m_strStrasse = set.m_Strasse;
		Dlg.m_strFirma = set.m_Firmenname;
		Dlg.DoModal ();
			
		// aufräumen	
		set.Close();
	}
	catch (CException *e)
	{
		e -> ReportError ();
		e -> Delete ();
	}		
}

//	Setze Selektion in ListBox: zurück mit Item
int CDoAbgleich::SetSelection (CListCtrl *pList, BOOL bSelect)
{
//	prüfe Parameter
	ASSERT (NULL != pList);

//	akt. Cursorposition in Screen-Coordinaten lesen
	CPoint pt (0,0);
	::GetCursorPos (&pt);	
	
//	Koordinaten konvertieren
	pList->ScreenToClient (&pt);
	pt.x = 2;

//	Item bestimmen
	int iItem = pList->HitTest (pt, NULL);
	if (iItem >= 0)
	{
		UINT uiAttrib = bSelect ? LVIS_SELECTED|LVIS_FOCUSED : LVIS_FOCUSED;
		pList->SetItemState(iItem, uiAttrib, uiAttrib);
	}
	
	return iItem;
}

void CDoAbgleich::OnClickAbfall(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	ASSERT (NULL != m_pAbfallMap);
	SetSelection (&m_lbAbfall);
	m_pAbfallMap -> ChangeSelection ();
	SetSummenMenge ();
	*pResult = 0;
}

void CDoAbgleich::OnClickAbfallVorjahr(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	SetSelection (&m_lbAbfallVJ);
	m_pAbfallMapVJ -> ChangeSelection ();
	SetSummenMenge ();
	*pResult = 0;
}

void CDoAbgleich::OnClickBgs(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	ASSERT (NULL != m_pBgsMap);
	SetSelection (&m_lbBgs);
	m_pBgsMap -> ChangeSelection ();            
	SetSummenMenge ();
	*pResult = 0;
}

void CDoAbgleich::OnRclickAbfall(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	SetSelection (&m_lbAbfall, FALSE);
	m_pAbfallMap -> ChangeSelection ();
	SetSummenMenge ();
	ShowSelection (&m_lbAbfall, m_pAbfallMap, TRUE); 	
	*pResult = 0;
}

void CDoAbgleich::OnRclickAbfallVorjahr(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	SetSelection (&m_lbAbfallVJ, FALSE);
	m_pAbfallMapVJ -> ChangeSelection ();
	SetSummenMenge ();
	ShowSelection (&m_lbAbfallVJ, m_pAbfallMapVJ, m_iModus); 	
	*pResult = 0;
}

void CDoAbgleich::OnRclickBgs(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	SetSelection (&m_lbBgs, FALSE);
	m_pBgsMap -> ChangeSelection ();
	SetSummenMenge ();
	ShowSelection (&m_lbBgs, m_pBgsMap, TRUE); 	
	*pResult = 0;
}

void CDoAbgleich::OnDeleteitemAbfallVorjahr(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	char *pKey = (char *)(pNMListView -> lParam);
	DELETE_VEC (pKey);

	*pResult = 0;
}

void CDoAbgleich::OnDeleteitemAbfall(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	char *pKey = (char *)(pNMListView -> lParam);
	DELETE_VEC (pKey);

	*pResult = 0;
}

void CDoAbgleich::OnDeleteitemBgs(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	char *pKey = (char *)(pNMListView -> lParam);
	DELETE_VEC (pKey);

	*pResult = 0;
}

//	Gesamtmenge in der Abfalltabelle ok ?
BOOL CDoAbgleich::GesAbfMengeOk ()
{
	ASSERT (m_pFoxProDatabase && m_pFoxProDatabase->IsOpen ());
	ASSERT (m_pErzeugerSet && m_pErzeugerSet->IsOpen ());
	ASSERT (NULL != m_pAbfArtenMap);
	ASSERT (m_dMinMenge >= 0);

//	Spezialfall
	if ((0.0 == m_dMinMenge) || (1 == m_iModus))
		return TRUE;
	
	CAbfallSet Set (m_pFoxProDatabase);
	Set.m_nParams = 1;
	VERIFY (Set.m_strFilter.LoadString (IDS_ERZ_NR_FILTER));
	Set.m_strErzNrParam = m_pErzeugerSet->m_strErzNr;
	Set.Open (CRecordset::forwardOnly, m_strAbfallTable,CRecordset::readOnly);
	BOOL bRet = FALSE;
	for (double dMenge = 0.0; !Set.IsEOF (); Set.MoveNext())
	{
	//	prüfe Abfallart
		if (Set.m_strAbfallnummer.IsEmpty ())
			continue;

	//	suche Abfall in Map
		CAbfallArt *pArtInfo = NULL;
		if (!m_pAbfArtenMap -> Lookup (Set.m_strAbfallnummer, (CObject *&) pArtInfo))
			continue;

		ASSERT (NULL != pArtInfo);
	
	//	nur Sonderabfall ?
		if (m_bOnlySonderAbfall && !pArtInfo -> m_bSonderAbfall)
			continue;

	//	Menge addieren
		dMenge += Set.m_dMenge_t;

	//	ggf. zurück
		if (dMenge >= m_dMinMenge)
		{
			bRet = TRUE;
			break;
		}
	}

	if (Set.IsOpen ())
		Set.Close ();
	
	return bRet;
}

//	Gesamtmenge in der Referenztabelle ok ?
BOOL CDoAbgleich::GesBgsMengeOk ()
{
	ASSERT (m_pMdbDatabase && m_pMdbDatabase->IsOpen ());
	ASSERT (m_pErzeugerSet && m_pErzeugerSet->IsOpen ());
	ASSERT (NULL != m_pAbfArtenMap);
	ASSERT (m_dMinMenge >= 0);

//	Spezialfall
	if ((0.0 == m_dMinMenge) || (1 == m_iModus))
		return TRUE;

	CBgsSet Set (m_pMdbDatabase);
	Set.m_nParams = 1;
	VERIFY (Set.m_strFilter.LoadString (IDS_ERZB_NR_FILTER));
	Set.m_strErzNrParam = m_pErzeugerSet->m_strErzNr;
	Set.Open (CRecordset::forwardOnly, m_strBgsTable,CRecordset::readOnly);
	BOOL bRet = FALSE;
	for (double dMenge = 0.0; !Set.IsEOF (); Set.MoveNext())
	{
	//	prüfe Abfallart
		if (Set.m_strAbfallschluesselnummer.IsEmpty ())
			continue;

	//	suche Abfall in Map
		CAbfallArt *pArtInfo = NULL;
		if (!m_pAbfArtenMap -> Lookup (Set.m_strAbfallschluesselnummer, (CObject *&) pArtInfo))
			continue;

		ASSERT (NULL != pArtInfo);
	
	//	nur Sonderabfall ?
		if (m_bOnlySonderAbfall && !pArtInfo -> m_bSonderAbfall)
			continue;

	//	Menge addieren
		dMenge += Set.m_dMenge;

	//	ggf. zurück
		if (dMenge >= m_dMinMenge)
		{
			bRet = TRUE;
			break;
		}
	}

	if (Set.IsOpen ())
		Set.Close ();
	
	return bRet;
}

//	Priorität für den Fall 1 OK ?
BOOL CDoAbgleich::BgsPrioOk ()
{
	ASSERT (m_pBgsSet && m_pBgsSet->IsOpen ());

//	Spezialfall
	if ((1 == m_iModus) || (0 != m_iPrioritaet))
		return TRUE;

	BOOL bRet = FALSE;
	for (m_pBgsSet->MoveFirst (); !m_pBgsSet->IsEOF (); m_pBgsSet->MoveNext ())
	{
		if (m_pBgsSet->m_strPrioritaet == "1")
		{
			bRet = TRUE;
			break;
		}
	}

//	wieder auf 1. Satz
	m_pBgsSet->MoveFirst ();

	return bRet;
}

//	Erstelle temp. Tabelle für mögliche Erzeuger/Abfälle aus BGS-Tabelle
void CDoAbgleich::CreateBgsErzAbfTable ()
{
	ASSERT (m_pMdbDatabase && m_pMdbDatabase->IsOpen ());
	ASSERT (m_pFoxProDatabase && m_pFoxProDatabase->IsOpen ());

	CString strTable;
	VERIFY (strTable.LoadString (IDS_BGS_ERZABF_TABLE));

	
//	wenn Tabelle existiert zurück
	CColumns Set (m_pFoxProDatabase);
	Set.m_strTableNameParam = strTable;		
	BOOL bFound = TRUE;
	try
	{		
		CString str;
		VERIFY (str.LoadString (IDS_NUMMER));
		Set.Open ();
		if (!Set.FieldExists (str, SQL_VARCHAR))
			bFound = FALSE;
	}
	catch (CDBException *e)
	{
		e -> Delete ();
		bFound = FALSE;
	}

//	Set schließen
	if (Set.IsOpen ())
		Set.Close ();
	
//	Tabelle vorhanden
	if (bFound)
		return;

//	Info an Nutzer ausgeben
	OutputUserInfo (IDS_CREATE_TEMP_TABLE);	
	
//	Tabelle erzeugen
	CString strSQL;
	AfxFormatString1 (strSQL, IDS_CREATE_BGS_TABEL, strTable);
	m_pFoxProDatabase->ExecuteSQL (strSQL);	

//	Tabelle umkopieren
	CBgsSet	SourceSet (m_pMdbDatabase);
	SourceSet.m_strSort.Empty ();
	SourceSet.m_strFilter.Empty ();
	SourceSet.m_nParams = 0;
	ASSERT (!m_strBgsTable.IsEmpty ());
	SourceSet.Open (CRecordset::forwardOnly, m_strBgsTable,CRecordset::readOnly);
	CBgsSetRed DestSet (m_pFoxProDatabase);
	DestSet.Open (CRecordset::snapshot, strTable,CRecordset::appendOnly);

	for (;!SourceSet.IsEOF ();SourceSet.MoveNext())
	{
		if (SourceSet.m_strAbfallschluesselnummer.IsEmpty () || 
			SourceSet.m_strErzeugernummer.IsEmpty ())
			continue;

		DestSet.AddNew ();
		DestSet.m_Abfallschluesselnummer = SourceSet.m_strAbfallschluesselnummer;
		DestSet.m_Erzeugernummer = SourceSet.m_strErzeugernummer;
		DestSet.Update ();
	}

//	Set schließen
	if (SourceSet.IsOpen ())
		SourceSet.Close ();
	if (DestSet.IsOpen ())
		DestSet.Close ();
}

void CDoAbgleich::OnWeiter() 
{
#pragma MSG("Weiterschalten im Abgleich ohne Aktion")
	// JG reicht das
	ReadNextErzeuger ();			
}

void CDoAbgleich::ShowAktData()
{
	CString strInfo;
	AfxFormatString2 (strInfo, IDS_ERZEUGER_CAPTION, 
					  m_pErzeugerSet->m_strErzNr,m_pErzeugerSet->m_strAsn);
	SetWindowText(strInfo);
	SetSummenMenge ();

	try
	{
		//	Set Öffnen
		CErzeugerSetErzeugerListe Set (m_pFoxProDatabase);
		Set.m_strTableName = m_strErzeugerTable;
		Set.Open (CRecordset::snapshot, NULL, CRecordset::readOnly);
		Set.m_strErzNrParam = m_pErzeugerSet->m_strErzNr;
		Set.Requery ();

		if (Set.IsEOF ())
		{
			CString strInfo;
			AfxFormatString1 (strInfo, IDS_ERZEUGER_NOT_FOUND, m_pErzeugerSet->m_strErzNr);
			OutputInfo (strInfo);
		}				
		else
		{
			m_ctrlAnfallstelle.SetWindowText(Set.m_strBezAnfall);
			m_ctrlBranchennummer.SetWindowText(Set.m_strBranche);
		}
		Set.Close();

		// jetzt noch versuchen die Branchennummer rauszubekommen
		CSelectSet* pBranchenSet = GetBranchenSet();
		if (NULL == pBranchenSet)
			return;

		if (SearchNummer(pBranchenSet, Set.m_strBranche))
		{
			m_ctrlBranchennummer.SetWindowText(pBranchenSet->m_Name);
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

CSelectSet* CDoAbgleich::GetBranchenSet()
{
	if (NULL == m_pBranchenSet)
	{
		try
		{
			// Tabellennamen bilden
			CString strTableName = ((CGakApp *)AfxGetApp())->BranchenDefaultSQL();
			ASSERT (!strTableName.IsEmpty ());

			CDaoDatabase* pDataBase = NULL;
			if (g_pAbfSet)
			{
				pDataBase = g_pAbfSet->m_pDatabase;
			}

			// jetzt aber los' eh
			m_pBranchenSet = new CSelectSet(pDataBase, strTableName);
		}
		// wie will catch everything
		catch(...)
		{
		}
	}
	
	if (NULL == m_pBranchenSet)
		return NULL;

	// jeder hat ein recht darauf den RS geöffnet zu bekommen
	if (!m_pBranchenSet->IsOpen())
		m_pBranchenSet->Open();
	
	return m_pBranchenSet;
}
