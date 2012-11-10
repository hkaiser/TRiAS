/*------------------------------------------------------------------------
File: V_DBASE.CPP

View_dBase -
gibt den Inhalt einer ODBC-Tabelle satzweise in eine Listbox aus.

Erarbeitet: J. Benkenstein              am: 19. Dez. 1991
								 Stand vom: 12. März 1994
Überabeitet:	J. Günther					März-Mai.99	OGX Grid
---------------------------------------------------------------------------*/

#include "pheader.h"                    // vorübersetzten Header
#include "odbcext.hr"					// Resource-Konstanten
					    

#include <hpp/odbcerr.hpp>                  // OdbcError 
#include <hpp/getodbci.hpp>
#include "database.hpp"                 // CDataBaseEx
#include "profile.hpp"                 	// DBaseProFile
#include <hpp/toolbar.hpp>					// CToolBarEx
#include <hpp/waitcur.hpp>                  // CWaitCursor 
#include <hpp/columnst.hpp>                 // CColumns
#include <hpp/collist.hpp>                  // CColumnObjArray
#include "recset.hpp"                   // CRecSet
#include <hpp/relation.hpp>                 // DBaseRel
#include <hpp/strdup.hxx>					// StringDup

#include "dispatch.hpp"                 // dBaseDispatch
#include "v_longvr.hpp"					// ViewLongVar

#ifdef WIN32
#include "feldin32.hpp"					// CFeldInfo
#else
#include "feldinfo.hpp"					// CFeldInfo
#endif

#include "v_dbase.hpp"                  // zugeh. Header
#include "Menubitmapper.h"				// Menu mit ICONS(doll)


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Konstanten 
const char cTabSep = '\t';				// Separator für Darstellung der Infos in ListBox
const short sTabConst = 4;				// aus CommonView	
const char fKoordFormat [] = "%.5f";	// Formate der Datentypen		
const char dKoordFormat [] = "%.5lf";	

// externe Funktionen
char *DtoA (double Wert, char *String, const char *Format = NULL); 
void CallMessageQueue (void);		// Steuerung an Windows zum Nachzeichnen

// externe Variablen                    
extern CDataBaseExtTree *g_pDataBaseTree;	// DataSource-Baum
extern "C" HINSTANCE g_hInstance;

// lokale Variablen
static UINT arButtonIdField [] = 
{
	IDM_FIRSTFIELD,
	IDM_LASTFIELD,
		ID_SEPARATOR,
	IDM_FIRSTRECORD,
	IDM_PREVRECORD,
	IDM_NEXTRECORD, 
	IDM_LASTRECORD 
};

BEGIN_MESSAGE_MAP(ShowFile, CDialog)
	//{{AFX_MSG_MAP(ShowFile)
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_WM_CREATE()                   
	ON_WM_SIZE()
	ON_LBN_SELCHANGE(IDL_ROWLIST, OnSelchangeRowList)
	ON_WM_INITMENU()
	ON_WM_TIMER()
	ON_LBN_DBLCLK(IDL_ROWLIST, OnDblclkRowlist)   
	ON_WM_INITMENUPOPUP()
	ON_COMMAND(IDM_FIRSTFIELD, OnFirstField)
	ON_COMMAND(IDM_LASTFIELD, OnLastField)  
	ON_COMMAND(IDM_FIRSTRECORD, OnFirstRecord)      
	ON_COMMAND(IDM_LASTRECORD, OnLastRecord)        
	ON_COMMAND(IDM_NEXTRECORD, OnNextRecord)        
	ON_COMMAND(IDM_PREVRECORD, OnPrevRecord)
	ON_COMMAND(IDM_COPY, ListToClip)                
	ON_COMMAND(ID_FILE_SAVE_AS, Save)                
	ON_COMMAND(IDM_FIELDINFO, OnFieldinfo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REDO, OnUpdateEditRedo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CLEAR, OnUpdateEditClear)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_COMMAND(ID_EDIT_REDO, OnEditRedo)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	ON_UPDATE_COMMAND_UI(IDD_ASC, OnUpdateAnySort)
	ON_UPDATE_COMMAND_UI(IDD_DESC, OnUpdateAnySort)
	ON_COMMAND(IDD_ASC,OnSortGridAsc)
	ON_COMMAND(IDD_DESC,OnSortGridDesc)
	ON_WM_MEASUREITEM()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ShowFile dialog


ShowFile::ShowFile (CWnd * pParent,        		// Zeiger auf Elternfenster     
				   	dBaseDispatch *pDisp,  		// Zeiger auf rufenden dBase-Dispatcher
			   		CPoint &TransLation,       	// x,y-Verschiebung des Fensters
			   		char * pAliasName,       	// Alias-Name der Datei
			   		char * pFieldName,       	// akt. Feld-Name
			   		char * pFieldVal)        	// akt. Feld-Inhalt
				  : CDialog ()
{                   
//  interne Init.                                  
	m_pCDataBase = NULL;			// DataSource-Objekt
	m_pCDispatcher = NULL;          // Dispatcher

	m_pCRecSet = NULL;              // RecordSet

	m_pCColumns = NULL;             // SpaltenInfos      
	m_sRelCnt = 0;                  // Anz. d. Relationen
    m_ppdBaseRel = NULL;            // Zeiger auf Slave-DB/Feld
    m_pRelMenu = NULL;              // Zeiger auf Relations-Menü
    m_sMaxRec = m_sActRec = 0;		// keine Sätze im Set
    m_sCX = m_sCY = 0;				// keine Verschiebung
    
	m_sRC = EC_SYSERROR;            // erstmal alles rücksetzen
	m_bToDelete = TRUE; 
	
//	Steuerung an Windows übergeben (zum "Nachzeichnen")
	CallMessageQueue ();
                           
//  prüfe Parameter: pFieldVal kann NULL sein bei WHERE-Klausel 
	if (!pParent || !pAliasName || !pFieldName || !pDisp) 
	{
		DEX_Error (RC_ctShowFile, (m_sRC = EC_ILLPARS));
		return;
	}       
	m_hProject = DEX_GetObjectProject(pDisp->ActObj());

	                      
	CWaitCursor Cursor;                     // Sanduhr laden
	TRY 
	{                                 
		if (g_pDataBaseTree)
			m_pCDataBase = g_pDataBaseTree -> GetDataSource (pAliasName, m_hProject);
		else
		{
			Profile ProFile(m_hProject);
			DataSourceType tType = NoDataSource;
			StringDup strDSN (ProFile.GetDataSourceName (pAliasName, tType), FALSE);
			if (! strDSN)
			{
				DEX_Error (RC_ctShowFile, (m_sRC = EC_ILLPARS));	
				return;
			}			
			m_pCDataBase = new CDataBaseExt (strDSN, tType);	
			if (m_pCDataBase -> Open () == FALSE)
				m_pCDataBase = NULL;
		}

		if (! m_pCDataBase)
			return;
		m_pCColumns = new CColumns ((CDatabase *) m_pCDataBase);
	}                                                          
	CATCH (CMemoryException, e)
	{   
		DEX_Error (RC_ctShowFile, (m_sRC = EC_NOMEMORY));               
		return;
	}                
	AND_CATCH (CDBException, dbe)   
	{
		OdbcError oe (dbe);
		oe.Show (RC_ctShowFile);                 
		return;                    
	}
	END_CATCH
     
//  Parameter speichern
	m_strAliasName = pAliasName;
	// m_strAliasName.MakeUpper ();                             
	m_pCDispatcher = pDisp;                                    
				 
#ifndef __UseOGX__
//  Recordset init.                                                  
	if (! InitRecordSet (pAliasName, pFieldName, pFieldVal, m_hProject))
	{
		DEX_Error (RC_ctShowFile, (m_sRC = WC_NOTFOUND));
		return;                         
	}
#else
// wenigstens die teuer erkauften Strings merken
// KK000417 - CString werden später als char * verwendet 
//	Folge : bei pFieldVal = NULL hat somit m_strFieldVal einen Wert -> dadurch falsche Query
	m_strFieldName.Empty();
	m_strFieldVal.Empty();

	if ( pFieldName )
		m_strFieldName = pFieldName;
	if (pFieldVal)
		m_strFieldVal  = pFieldVal;

// Original
//	m_strFieldName = pFieldName;
//	m_strFieldVal  = pFieldVal;

// und den tiomer initialisieren
/*	m_nTicksSinceResize = 0;		// speichert die Timeraufrufe seit dem letzten OnSize handling
	m_nTimer = 0;*/
#endif //__UseOGX__

	BOOL bRet = TRUE;

//  modeless dialog erzeugen	
#if _MSC_VER >= 1000
	// modeless erzeugen, da Menu zusätzlich geladen wird, muß der MFC
	// das Handle mitgeteilt werden, wo selbiges zu finden ist
	HINSTANCE hCurrInst = AfxGetInstanceHandle ();
	afxCurrentInstanceHandle = g_hInstance;
	bRet = Create (ShowFile :: IDD, pParent);
	afxCurrentInstanceHandle = hCurrInst;
#else
	bRet = Create (ShowFile :: IDD, pParent);
#endif 

	if (!bRet)
	{
		DEX_Error (RC_ctShowFile, (m_sRC = EC_SYSERROR));
		return;
	}
	
//  Fenster ggf. verschieben        
	CRect rc;
	GetWindowRect (&rc);
	rc += TransLation;						// Translation	
	MoveWindow (&rc);

//	LisBox-Parameter setzen                                 
	int iTabPos = 0;         	
	WORD wUnits = LOWORD (:: GetDialogBaseUnits ());

//	Notvariante für 16 Bit
	CDC *pCDC = GetDC ();
	if (pCDC)
	{
		TRY
		{
			CString strBuffer ('M', m_CColList.m_sMaxNameLen);
			#ifdef WIN32			
			CSize Size = pCDC -> GetTextExtent (strBuffer);
			#else 
			CSize Size = pCDC -> GetTextExtent (strBuffer, strBuffer.GetLength ());			
			#endif
			iTabPos = MulDiv (Size.cx, 4, wUnits);
		}
		CATCH (CMemoryException, e)
		{   
			DEX_Error (RC_ctShowFile, (m_sRC = EC_NOMEMORY));               
			return;
		}
		END_CATCH
		ReleaseDC (pCDC);
	}
	else
		iTabPos = (m_CColList.m_sMaxNameLen + 3) * sTabConst;		// 4 aus CommonView

#ifndef __UseOGX__
		m_lbRowList.SetTabStops (iTabPos);	    
		m_lbRowList.SetHorizontalExtent (wUnits*(m_CColList.m_sMaxNameLen+m_CColList.m_sMaxShowLen+3));	
#endif //__UseOGX__
				
	//{{AFX_DATA_INIT(ShowFile)
	//}}AFX_DATA_INIT
		       
//  Flags setzen      
	m_bToDelete = FALSE;            // Fenster nicht löschen
	m_sRC = EC_OKAY;                // init. OK
}

void ShowFile::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
#ifndef __UseOGX__
	//{{AFX_DATA_MAP(ShowFile)
	DDX_Control(pDX, IDL_ROWLIST, m_lbRowList);
	//}}AFX_DATA_MAP
#endif //__UseOGX__	

}

// Fileinhalt ausgeben
void ShowFile :: Darstellen (void) 
{   
//  prüfe internen Zustand
	if (m_sRC != EC_OKAY)          
		return;                 
	

#ifndef __UseOGX__
	//	Sätze zählen	
		CWaitCursor wc;	  	 
		if ((m_pCRecSet -> IsBOF ()) ||  		// keine Sätze vorhanden
		    (m_CColList.Count () == 0) ||		// keine Felder vorh.
		   ((m_sMaxRec = (short) m_pCRecSet -> GetRecordCount ()) == -1))  	// Fehler beim Zählen der Sätze
		{                                                    
			DEX_Error (RC_DarstShowFile, (m_sRC = WC_NOTFOUND));              
			return;
		}		     

#endif //__UseOGX__
	                                                
	m_sMaxRec++; 		
	m_sActRec = 1;
	
//  Feld/Namen- und Inhalte in Dialog-Fenster ausgeben                                              
	if (OutputList () == TRUE)	// JG das macht doch nichts 
		ShowWindow (SW_SHOWNORMAL);                                     
}                 

ShowFile :: ~ShowFile (void)
{            
	DeleteDataBase ();

#ifdef __UseOGX__
	m_wndRecord.SetRecordset(NULL);
	delete m_pCRecSet;
#endif //__UseOGX__
}   

void ShowFile :: DeleteDataBase (void)
{
//  SpaltenInfo freigeben 
	DELETE_OBJ (m_pCColumns);                   

//	Record-Set			      

#ifndef __UseOGX__
		DELETE_OBJ (m_pCRecSet);             
#endif //__UseOGX__
       
	
//	Data-Source-Objekt-Reference freigeben	
	if (g_pDataBaseTree)
	{
		if (m_pCDataBase)
		{
			g_pDataBaseTree -> RemoveDataSource (m_pCDataBase);
			m_pCDataBase = NULL;
		}       
	}
	else
		DELETE_OBJ (m_pCDataBase);

	m_bToDelete = TRUE;						// Objekt kann gelöscht werden
}	

/////////////////////////////////////////////////////////////////////////////
// ShowFile message handlers
void ShowFile::OnClose()
{
	DeleteRelMenu ();                       // RelationsMenü freigeben
    DeleteRelations ();                 	// zugeh. Einträge löschen 

//  TODO: Add your specialized code here and/or call the base class
	DeleteDataBase ();
	
	CDialog::OnClose();
}

void ShowFile::OnDestroy() 
{
	DeleteRelMenu ();                       // RelationsMenü freigeben
    DeleteRelations ();                 	// zugeh. Einträge löschen 

	CDialog::OnDestroy();
//	TODO: Add your message handler code here
	DeleteDataBase ();	
}

int ShowFile::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1) 
	{
		DEX_Error (RC_ctShowFile, (m_sRC = EC_SYSERROR));
		return -1;
	}               
	
#ifndef __UseOGX__
	// 	ToolBar erzeugen
		if (!m_WndButtons.Create(this) ||
			!m_WndButtons.LoadBitmap(IDB_VIEW_FRAME) ||
			!m_WndButtons.SetButtons(arButtonIdField,
			  sizeof(arButtonIdField)/sizeof(UINT)))
			return -1;

#endif //__UseOGX__

	return 0;
}

void ShowFile::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	
	// zufälligerweise die gleiche Posituion wie beim letzten mal?
	bool bOldPos = false;
	if (m_sCX == cx && m_sCY == cy)
		 bOldPos = true;

	m_sCX = cx;
	m_sCY = cy; 


#ifndef __UseOGX__
	// alte Variante
	if (m_WndButtons.m_hWnd && m_WndButtons.IsWindowVisible ())                      
	{                                     
	#ifdef WIN32                                                      
		CSize Size (m_WndButtons.CalcFixedLayout (TRUE, TRUE));
	#else
		CRect rc;
		m_WndButtons.GetItemRect (0, &rc);
		CSize Size;
		Size.cy = rc.top + rc.bottom;
	#endif		
		m_WndButtons.MoveWindow (0, 0, cx, Size.cy, TRUE);
		m_WndButtons.MoveWindow (0, 0, cx, Size.cy, TRUE);
	}
#endif

#ifdef __UseOGX__
	// neue Variante	der belegte Platz ist nichts
	CSize Size(0, 0);
#endif //__UseOGX__


	if (m_lbRowList.m_hWnd && m_lbRowList.IsWindowVisible ())    
	{  
		// das Verändern der Größe des Grids verhindern
		m_lbRowList.MoveWindow (0, Size.cy, cx, cy - Size.cy);
	}
}

BOOL ShowFile::OnInitDialog(void)
{
	BOOL retval = CDialog::OnInitDialog();

#ifdef __UseOGX__
	m_lbRowList.SubclassDlgItem(IDC_GRID, this);
	m_wndRecord.Create(0, CRect(0,0,1,1), &m_lbRowList, IDC_GRID);
	m_lbRowList.AttachWnd(&m_wndRecord);
	m_wndRecord.Initialize();
	m_wndRecord.SetFocus();

//  Zeileninfotext ändern
	CString strZeilenInfo;
	VERIFY (strZeilenInfo.LoadString(IDS_ZEILENINFO));
	m_wndRecord.GetRecordInfoWnd()->GetBeam()->m_strRecord = strZeilenInfo;

//  Recordset init.                                                  
	if (! InitRecordSet (m_strAliasName, m_strFieldName, m_strFieldVal, m_hProject))
	{
		DEX_Error (RC_ctShowFile, (m_sRC = WC_NOTFOUND));
		return retval;                         
	}
#endif //__UseOGX__

// die Listbox bleibt vorerst in der Ressource, um schnell auf die alte Version zurückschalten zu können
// wir müssen daher hier umschalten
	CWnd* pWnd= NULL;

// Kontextabhängig das Fenster bestimmen
#ifdef __UseOGX__
	pWnd = GetDlgItem(IDL_ROWLIST);
#else
	pWnd = GetDlgItem(IDC_GRID);
#endif //__UseOGX__

// und verabschieden
	if (pWnd)
	{
		pWnd->ShowWindow(false);
		pWnd->EnableWindow(false);
	}

#ifndef __UseOGX__
	#ifdef WIN32                                 
		CSize Size (m_WndButtons.CalcFixedLayout (TRUE, TRUE));
	#else 
		CRect rc;
		m_WndButtons.GetItemRect (0, &rc);
		CSize Size;                      
		Size.cy = rc.top + rc.bottom;
	#endif
		m_WndButtons.MoveWindow (0, 0, m_sCX, Size.cy, TRUE);
#else
	CSize Size(0, 0);
#endif //__UseOGX__

	m_lbRowList.MoveWindow (0, Size.cy, m_sCX, m_sCY - Size.cy);
	     
// Menu anpassen
//	GetMenu()->InsertMenu(0, MF_BYPOSITION | MF_POPUP, (UINT) m_menuSort.GetSafeHmenu(), m_menuSort.GetName());
//	GetMenu()->InsertMenu(0, MF_BYPOSITION | MF_POPUP, (UINT) m_menuWork.GetSafeHmenu(), "Bearbeiten"/*m_menuWork.GetName()*/); 
	return TRUE;  
}

void ShowFile::OnInitMenu(CMenu* pMenu)
{
	CDialog::OnInitMenu(pMenu);
	
	if (m_sMaxRec == 1)			// alles
		return;					// bleibt aus
// #ifndef __UseOGX__
	//      Menüpunkte akt.
		if (m_sActRec == m_sMaxRec)                  // letze Satz ist bereits aktiv
		{
			pMenu -> EnableMenuItem (IDM_NEXTRECORD, MF_GRAYED);
			pMenu -> EnableMenuItem (IDM_LASTRECORD, MF_GRAYED);    
		}
		else                                         // also noch nicht letzter Satz
		{
			pMenu -> EnableMenuItem (IDM_NEXTRECORD, MF_ENABLED);
			pMenu -> EnableMenuItem (IDM_LASTRECORD, MF_ENABLED);                   
		}
		
		if (m_sActRec == 1)                          // bereits auf dem 1. Satz ?
		{
			pMenu -> EnableMenuItem (IDM_FIRSTRECORD, MF_GRAYED);
			pMenu -> EnableMenuItem (IDM_PREVRECORD, MF_GRAYED);    
		}
		else                                         // also noch vor dem 1. Satz
		{
			pMenu -> EnableMenuItem (IDM_FIRSTRECORD, MF_ENABLED);
			pMenu -> EnableMenuItem (IDM_PREVRECORD, MF_ENABLED);                   
	}       
// #endif //__UseOGX__

}                                                             

// "Erster Eintrag" selektiert                                   
void ShowFile :: OnFirstField (void) 
{   

#ifndef __UseOGX__
		m_lbRowList.SetCurSel (0);
#endif //__UseOGX__
	SelchangeRowList ();
}       

// "Letzter Eintrag" selektiert
void ShowFile :: OnLastField (void)
{

#ifndef __UseOGX__
		short Cnt = m_lbRowList.GetCount (); 
		m_lbRowList.SetCurSel (Cnt ? Cnt - 1 : 0);

#endif //__UseOGX__
	SelchangeRowList ();
}       
		   
//      Record-Selektion                                   
void ShowFile :: OnFirstRecord (void) 
{   

#ifndef __UseOGX__
	//	prüfe Parameter
		if (m_sActRec == 1)
			return;
	                  
		CallMessageQueue ();
		CWaitCursor wc; 
		m_sActRec = 1;        
		TRY 
		{                 
			if (m_pCRecSet -> m_bForwardOnly)		// wenn nur Vorwärts-Scrollen
				m_pCRecSet -> Requery ();			// neue Abfrage
			else
				m_pCRecSet -> MoveFirst (); 
		}   
		CATCH_ALL (e)
		{
			DEX_Error (RC_DarstShowFile, EC_SYSERROR);
			return;
		}     
		END_CATCH_ALL
		
		OutputList ();  // neuen Satz ausgeben

#endif //__UseOGX__
}       

void ShowFile :: OnLastRecord (void) 
{                     

#ifndef __UseOGX__
	//	prüfe Parameter
		if (m_sActRec == m_sMaxRec)
			return;
	
		CallMessageQueue ();      
		CWaitCursor wc;         
		m_sActRec = m_sMaxRec;
		TRY 
		{
			
			m_pCRecSet -> MoveLast (); 
			
		}   
		CATCH_ALL (e)
		{
			DEX_Error (RC_DarstShowFile, EC_SYSERROR);
			return;
		}     
		END_CATCH_ALL
		
		OutputList ();  // neuen Satz ausgeben

#endif //__UseOGX__
}       

void ShowFile :: OnNextRecord (void) 
{   

#ifndef __UseOGX__
	//	prüfe Parameter
		if (m_sActRec == m_sMaxRec)
			return;
	
		CallMessageQueue ();                        
		CWaitCursor wc;       
		m_sActRec++;  
		TRY 
		{
			m_pCRecSet -> MoveNext ();
		}   
		CATCH_ALL (e)
		{
			DEX_Error (RC_DarstShowFile, EC_SYSERROR);
			return;
		}     
		END_CATCH_ALL
	
	OutputList ();  // neuen Satz ausgeben
#endif //__UseOGX__
}       

void ShowFile :: OnPrevRecord (void) 
{            

#ifndef __UseOGX__
	//	prüfe Parameter
		if (m_sActRec == 1)
			return;
	
		CallMessageQueue ();
		CWaitCursor wc;            
		m_sActRec--;  
		TRY 
		{
			m_pCRecSet -> MovePrev ();
		}   
		CATCH_ALL (e)
		{
			DEX_Error (RC_DarstShowFile, EC_SYSERROR);
			return;
		}     
		END_CATCH_ALL
						  
		OutputList ();  // neuen Satz ausgeben                                          

#endif //__UseOGX__
}       

//  ListBox-Selection 
afx_msg void ShowFile :: OnSelchangeRowList (void)
{              
	SelchangeRowList ();
}

//  ListBox-Selection
void ShowFile :: SelchangeRowList (void)
{              
#ifndef __UseOGX__
//	selektierten Feldnamen lesen
	CString strSel;    

		short sIndex = m_lbRowList.GetCurSel ();
		if (sIndex == LB_ERR)
			return;

		m_lbRowList.GetText (sIndex, strSel);  

	strSel = strSel.Left (strSel.Find (cTabSep));		// FeldNamen filtern

//  Relationen neu lesen                                                                   
	ReadRelations (strSel, sIndex);                     // Relationen neu lesen
#endif //__UseOGX__
}

//      ColumnsStatus init. 
BOOL ShowFile :: InitRecordSet (const char *pAliasName, const char *pFieldName, const char *pFieldVal, HPROJECT hProject)
{   
	Profile ProFile(hProject);
	
//  Table-Namen bilden und an ColumnStatus übergeben
	StringDup strTableName (ProFile.GetTableName (pAliasName), FALSE);
	if (! strTableName)
	{               
		DEX_Error (RC_ctShowFile, EC_NOTABLENAME);
		return FALSE;
	}                                               

	// diese Zeichenketten dürfen nicht const sein, aber vielleicht werden sie ja mal geändert
	CString strFieldName(pFieldName);
	CString strFieldVal(pFieldVal);
	
//  ColumnStatus öffnen      
	BOOL bOpFlag = TRUE;    
	TRY                
	{                        
		m_pCColumns -> m_strTableNameParam = strTableName;        // Namen für ODBC speichern
		if ((bOpFlag = m_pCColumns -> Open ()) == TRUE)
		{                               
		//  Feldnamens-Liste füllen
			if (bOpFlag = m_CColList.FillColumnList (*m_pCColumns)) 
			{                                           
				m_pCColumns -> Close ();			// keinen 2. Cursor zulassen	
				DELETE_OBJ (m_pCColumns);			// nicht mehr benötigt
				CString strSQL;   
				AfxFormatString1 (strSQL, IDS_SQLSELECT, strTableName); // "SELECT * FROM <tablename> 
				CString strWhere;

				if (bOpFlag = m_CColList.BuildWhereKlausel (strWhere, strFieldName.GetBuffer(2048), strFieldVal.GetBuffer(2048)))
				{
					m_pCRecSet = new CRecSet (*(CDatabase *)m_pCDataBase
												, m_CColList
												, strWhere
#ifdef __UseOGX__
												, strSQL
#endif //__UseOGX__
											); 
					
#ifndef __UseOGX__
	bOpFlag = m_pCRecSet -> Open (CRecordset :: snapshot, strSQL, CRecordset::readOnly);
#endif //__UseOGX__

#ifdef __UseOGX__
					m_wndRecord.SetRecordset(m_pCRecSet);	// JG fill the Grid with data, ;-) clever
					m_wndRecord.OpenRecordset();

					ReadRelations(m_strFieldName, 0);
					SetGridStyle();
#endif //__UseOGX__
				}                   
			}   
		}                       
	}
	CATCH (CDBException, dbe)
	{                   
		OdbcError oe (dbe);
		oe.Show (RC_ctShowFile);                                     
		bOpFlag = FALSE;
	}
	AND_CATCH (CMemoryException, mce)
	{               
		DEX_Error (RC_ctShowFile, EC_NOMEMORY);
		bOpFlag = FALSE;                
	}
	AND_CATCH (CFileException, fe)
	{
		// DEX_Error (RC_ctShowFile, EC_SYSERROR);
		fe -> ReportError ();
		bOpFlag = FALSE;                	
	}
	END_CATCH

	// Ist es eigentlich dirty ReleaseBuffer aufzurufen ohne vorher GetBuffer gemacht zu haben???
	strFieldName.ReleaseBuffer(-1);
	strFieldVal.ReleaseBuffer(-1);

	return bOpFlag;
}                        

//  Feld/Namen- und Inhalte in Dialog-Fenster ausgeben        
BOOL ShowFile :: OutputList (void)
{   
#ifndef __UseOGX__
//  alten Daten u. Submenü löschen
    DeleteRelations ();         // alte Relationen
    DeleteRelMenu ();           // altes Submenü

		m_WndButtons.Enable (0);
		m_WndButtons.Enable (1);
	
	//	ToolBar aktualisieren
		if (m_sActRec == 1)
		{
			m_WndButtons.Disable (3);
			m_WndButtons.Disable (4);	
		}
		else
		{
			m_WndButtons.Enable (3);
	
			if (m_pCRecSet -> m_bForwardOnly)
				m_WndButtons.Disable (4);	
			else					
				m_WndButtons.Enable (4);	
		}		
			
		if (m_sActRec == m_sMaxRec)
		{                            
			m_WndButtons.Disable (5);
			m_WndButtons.Disable (6);
		}                          
		else
		{
			m_WndButtons.Enable (5);
			m_WndButtons.Enable (6);
		}                        
#endif //__UseOGX__


#ifndef __UseOGX__
	//  Listbox ggf. unsichtbar
		if (m_lbRowList.IsWindowVisible ())
			m_lbRowList.ShowWindow (SW_HIDE);  
	
		m_lbRowList.ResetContent ();    // alten Inhalt löschen
			
		TRY 
		{               
			char Buffer [40] = "";
			CString strOutput = m_strAliasName;
			strOutput += ": ";
			strOutput += itoa (m_sActRec, Buffer, 10);
			strOutput += "/";				          
			strOutput += itoa (m_sMaxRec, Buffer, 10);
			SetWindowText (strOutput);         // Caption ausgeben
	
		//  für alle Spalten        
			CRing ri (m_CColList);                      
			int nResult = 0;     
			short sFeldIndex = 1;
			for (ri.First (); ri.Valid (); ri.Next (), sFeldIndex++)
			{
				CColumnObjLock pCO (ri);
				if (pCO == NULL) 
				{                   
					DEX_Error (RC_DarstShowFile, EC_LOCKERROR);
					return FALSE;
				}   
				           
				strOutput = pCO -> ColName ();				// Feldnamen speichern
				strOutput += "\t";              			// Spalten-Separator
				
			//	Feld sollte Info besitzen			
	#if (_MFC_VER >= 0x0420)	// #HK960812: ???
				if ((m_pCRecSet -> GetFieldStatus(sFeldIndex-1) & AFX_SQL_FIELD_FLAG_NULL) == 0)
	#else
				if (! m_pCRecSet -> IsFieldFlagNull (sFeldIndex, 
													 CFieldExchange :: outputColumn))
	#endif // _MFC_VER
				{											     
			
				//  den Spalten-Wert enstprechend dem Typ lesen
					switch (pCO -> RFXType ())
					{              
						case AFX_RFX_TEXT:                      
							strOutput +=  *((CString *) pCO -> Value ());
						break;                                                  
						case AFX_RFX_INT:
							strOutput += itoa (*((int *) pCO -> Value ()), Buffer, pCO -> Radix ());
						break;
						case AFX_RFX_LONG:                                              
							strOutput += ltoa (*((long *) pCO -> Value ()), Buffer, pCO -> Radix ());
						break;
						case AFX_RFX_SINGLE:    
							strOutput += DtoA (*((float *) pCO -> Value ()), Buffer, fKoordFormat); 
						break;
						case AFX_RFX_DOUBLE:
							strOutput += DtoA (*((double *) pCO -> Value ()), Buffer, dKoordFormat);                           
						break;                                          
						case AFX_RFX_BYTE:                                             
							strOutput += itoa (*((BYTE *) pCO -> Value ()), Buffer, 10);
						break;                                                   
						case AFX_RFX_BOOL:            
							strOutput += *((BOOL *) pCO -> Value ()) ? "1" : "0";   
						break;
						case AFX_RFX_DATE:                 
						{               
							CTime *pTime = (CTime *) pCO -> Value ();
							if (pCO -> SQLType () == SQL_DATE ||            // "normales" Datum
								pCO -> SQLType () == SQL_TIMESTAMP)             // oder Zeitstempel
							{   
								strOutput += itoa (pTime -> GetYear (), Buffer, 10);                                                                                                                                               
								strOutput += "-";
								strOutput += itoa (pTime -> GetMonth (), Buffer, 10);
								strOutput += "-";
								strOutput += itoa (pTime -> GetDay (), Buffer, 10);
							}                                               
									
							if (pCO -> SQLType () == SQL_TIME ||            // Zeit
								pCO -> SQLType () == SQL_TIMESTAMP)             // oder Zeitstempel                                                                     
							{
								if (pCO -> SQLType () == SQL_TIMESTAMP)
									strOutput += " ";                                       // als Separator                                                        
									strOutput += itoa (pTime -> GetHour (), Buffer, 10);
									strOutput += ".";
									strOutput += itoa (pTime -> GetMinute (), Buffer, 10);
									strOutput += ".";
									strOutput += itoa (pTime -> GetSecond (), Buffer, 10);                                                                                          
							}
						}                                                                                   
						break;
						case AFX_RFX_BINARY:
						{
							CByteArray *pBA = (CByteArray *) pCO -> Value ();
							if (pBA -> GetSize ())
								strOutput += "*";
							strOutput += pCO -> SQLTypeName ();														
						}					
						break;
						case AFX_RFX_LONGBINARY:               
							strOutput += pCO -> SQLTypeName ();
						break;
						default:
						{                       
							DEX_Error (RC_DarstShowFile, EC_UNKN_FIELD_TYPE);
							return FALSE;                                   
						}                                       
						break;                          
					}       // end_switch
				}				
			
			//  gebildeten String ausgeben                                                
				nResult = m_lbRowList.AddString (strOutput);
				if (nResult == LB_ERR || nResult == LB_ERRSPACE)
				{       
					DEX_Error (RC_DarstShowFile, EC_NOMEMORY);
					return FALSE;                   
				}           
				
				Buffer [0] = '\0';                      // internen Puffer wieder zurücksetzen
			}       // end_for                                      
		}                               
		CATCH (CMemoryException, cme)                   // Exceptions der CString-Funktionen
		{           
			DEX_Error (RC_DarstShowFile, EC_NOMEMORY);
			return FALSE;                                   
	}           
	END_CATCH
	
	m_lbRowList.ShowWindow (SW_SHOWNORMAL);         // ListBox wieder akt.

#endif //__UseOGX__
	return TRUE;
}         

// Relations-Menü löschen
BOOL ShowFile :: DeleteRelMenu (void)
{                      
	BOOL bRes = FALSE;

	if (m_hWnd && m_pRelMenu)
	{                          
		CMenu *pMenu = GetMenu ();
   		if (pMenu) 
   		{                    
			CMenu *pSubMenu = pMenu -> GetSubMenu (2);                  // SubMenü besorgen
			if (pSubMenu) 
			{                
				BOOL bRes = pSubMenu -> RemoveMenu (0, MF_BYPOSITION);  // PopupMenü entf.
				DELETE_OBJ (m_pRelMenu);                                    // Objekt löschen       
				return bRes;
			}                           
		}
	}			

	return FALSE;
}

// alten Relationen löschen
void ShowFile :: DeleteRelations (void)
{
    for (short i = 0; i < m_sRelCnt; i++)
		DELETE_OBJ (m_ppdBaseRel [i]);
    DELETE_VEC (m_ppdBaseRel);
    m_sRelCnt = 0;
}

// Relations-Menü aufbauen
BOOL ShowFile :: CreateRelMenu (void)
{   
    if (m_ppdBaseRel == NULL)        // wenn keine Relation existiert
		return FALSE;
    
	CString strRel;         
//  neues Menü aufbauen
	TRY
	{       
		DELETE_OBJ (m_pRelMenu);			// altes Objekt löschen
		m_pRelMenu = new CMenu;  
		if (m_pRelMenu -> CreateMenu () == FALSE)
		{
			DELETE_OBJ (m_pRelMenu);
			return FALSE;
			}               
		
		if (strRel.LoadString (IDS_RELATIONS) == FALSE)
		{
			DELETE_OBJ (m_pRelMenu);
			return FALSE;       
		}               
		
		CMenu *pMenu = GetMenu ();      // HauptMenü des Dialogs
		CMenu *pSubMenu = pMenu ? pMenu -> GetSubMenu (pMenu -> GetMenuItemCount() -1) : NULL;	// JG das letzte Meü benutzen
		if (!pSubMenu || !pSubMenu -> InsertMenu (0, MF_BYPOSITION | MF_POPUP, 
						 (UINT) m_pRelMenu -> m_hMenu, strRel))
		{                                                
			DELETE_OBJ (m_pRelMenu);
			return FALSE;
		}                       
					
	//  einzelnen Einträge ins Submenü                                    
		CString strMenuEntry;                             
		char Buffer [10] = "";
		for (short sIndex = 0; sIndex < m_sRelCnt; sIndex++) 
		{                                                  
			strMenuEntry = "&";
			strMenuEntry += itoa (sIndex + 1, Buffer, 10);                  
			strMenuEntry += " ";
			strMenuEntry += m_ppdBaseRel [sIndex] -> GetDBName (); 
			strMenuEntry += ": "; 
			strMenuEntry += m_ppdBaseRel [sIndex] -> GetFieldName ();
			if (m_pRelMenu -> AppendMenu (MF_STRING | MF_ENABLED, (uint) IDM_REL + (uint) sIndex, strMenuEntry) == FALSE)
			{
				DELETE_OBJ (m_pRelMenu);
				return FALSE;
			}   
//			m_pRelMenu->EnableMenuItem((uint) IDM_REL + (uint) sIndex. MF_ENABLED | MF_BYCOMMAND);
		}                       
		return TRUE;
    }
    CATCH (CMemoryException, cme)
    {       
		DELETE_OBJ (m_pRelMenu);
		DEX_Error (RC_CreateRelMenu, EC_NOMEMORY);
	}   
    END_CATCH 
    
    return FALSE;       
}

// Relationen lesen
BOOL ShowFile :: ReadRelations (CString &strFieldName, short sColIndex)
{
//  alten Daten u. Submenü löschen
    DeleteRelations ();         // alte Relationen
    DeleteRelMenu ();           // altes Submenü

//  dBase-Relation aufbauen
	TRY
	{
		DBaseRel Master (m_strAliasName, strFieldName); // Aliasname der Master-DB und. zugeh. Feld
		Profile PF(m_hProject);                        
		if (m_sRelCnt = PF.ReadOdbcRelations (Master, &m_ppdBaseRel))
			return CreateRelMenu ();        //  Submenü für dBase-Relationen aufbauen
	}
	CATCH (CMemoryException, cme)
	{   
		DEX_Error (RC_ReadRelShowFile, EC_NOMEMORY);
	}                       
	END_CATCH           
	    
	return FALSE;           
}

// behandelt nur Relations-Menüpunkte      
LRESULT ShowFile :: DefWindowProc (UINT message, WPARAM wParam, LPARAM lParam )
{                                                               
	if ((message == WM_COMMAND) && m_ppdBaseRel)
	{                                                               
		uint nItem = (uint)wParam - (uint)IDM_REL;
		if (nItem >= 0 && nItem < (uint) m_sRelCnt)
		{       
				CString strSel;
#ifndef __UseOGX__
				m_lbRowList.GetText (m_lbRowList.GetCurSel (), strSel);        
				strSel = strSel.Right (strSel.GetLength () - strSel.Find (cTabSep) - 1);		
#else
			// Achtung! ich gehe von davon aus, dass über das Koppelfeld auch die Rel. angebunden werden
				strSel = m_strFieldVal;
#endif //__UseOGX__
			    m_pCDispatcher -> ShowDBaseWindowField (m_ppdBaseRel [nItem] -> GetDBName (),
													    m_ppdBaseRel [nItem] -> GetFieldName(), 
														strSel);
			return NULL;
		}
	}
			 
	return CWnd :: DefWindowProc (message, wParam, lParam);                  
}

//	ListBox-Doppelclick
void ShowFile::OnDblclkRowlist(void )
{                                   

#ifndef __UseOGX__
	//	lese aktuellen Index	
		short sIndex = m_lbRowList.GetCurSel ();
		if (sIndex == LB_ERR)
		{
			DEX_Error (RC_DarstShowFile, EC_SYSERROR);
			return;
		}                   
		
	//	lese zugeh. Feldinfo lesen
		CRing ri (m_CColList);
		if (! ri.Goto (sIndex))
		{
			DEX_Error (RC_DarstShowFile, EC_SYSERROR);
			return;
		}				
		
		CColumnObjLock pCO (ri);
		if (pCO == NULL)
		{
			DEX_Error (RC_DarstShowFile, EC_LOCKERROR);
			return;		
		}	
		
		//  Aktion entsprechend dem Typ: Editieren/Anzeigen
		switch (pCO -> RFXType ())
		{              
			case AFX_RFX_TEXT:  		// später editieren                    
			case AFX_RFX_INT:
			case AFX_RFX_LONG:                                              
			case AFX_RFX_SINGLE:    
			case AFX_RFX_DOUBLE:
			case AFX_RFX_BYTE:                                             
			case AFX_RFX_BOOL:            
			case AFX_RFX_DATE:                 
			break;
			case AFX_RFX_BINARY:  
			{       
			//	ist das Feld NULL ?
	#if (_MFC_VER >= 0x0420)	// #HK960812: ???
				if ((m_pCRecSet -> GetFieldStatus(sIndex) & AFX_SQL_FIELD_FLAG_NULL) == 0)
	#else
				if (! m_pCRecSet -> IsFieldFlagNull (++sIndex, CFieldExchange :: outputColumn))
	#endif // _MFC_VER
				{	
					CByteArray *pBA = (CByteArray *) pCO -> Value ();				                         			                                 
					CString	strFormat;
					if (pBA -> GetSize () > 0)
					{
						strFormat.LoadString (IDS_UNKNOWN_FORMAT);			                                 
						MessageBox (strFormat, pCO -> ColName (), MB_ICONEXCLAMATION | MB_OK);
					}
					else
					{
						strFormat.LoadString (IDS_EMPTY_FIELD);			                                 
						MessageBox (strFormat, pCO -> ColName (), MB_ICONASTERISK | MB_OK);				
					}				
				}				
			}			
			break;
			case AFX_RFX_LONGBINARY:              
			{   
				CString strFormat;              
				CLongBinary *pLB = (CLongBinary *) pCO -> Value ();				                         
				if (pCO -> SQLType () == SQL_LONGVARCHAR)		// Zeichenfeld
				{                                           
				//	Dialog für Anzeige des Feldinhaltes			
	#if (_MFC_VER >= 0x0420)	// #HK960812: ???
					if (m_pCRecSet -> RefreshAllFields (m_sActRec) &&
					   ((m_pCRecSet -> GetFieldStatus(sIndex) & AFX_SQL_FIELD_FLAG_NULL) == 0) &&
						pLB -> m_dwDataLength > 0) 
	#else
					if (m_pCRecSet -> RefreshAllFields (m_sActRec) &&
					   (m_pCRecSet -> IsFieldFlagNull (++sIndex,	// darf nicht NULL sein
									  CFieldExchange :: outputColumn) == FALSE) &&
						pLB -> m_dwDataLength > 0) 
	#endif // _MFC_VER
					{
						CViewLongVar vl (this, pLB, pCO -> ColName ());
						if (vl.Result ())
							vl.Show ();
					}       
					else	// leeres Feld
					{
						strFormat.LoadString (IDS_EMPTY_FIELD);			                                 
						MessageBox (strFormat, pCO -> ColName (), MB_ICONASTERISK | MB_OK);					
					}
				}										
				else		// unbekanntes Format
				{
					strFormat.LoadString (IDS_UNKNOWN_FORMAT);			                                 
					MessageBox (strFormat, pCO -> ColName (), MB_ICONEXCLAMATION | MB_OK);
				}
			}			
			break;
			default:
			{                       
				DEX_Error (RC_DarstShowFile, EC_UNKN_FIELD_TYPE);
				return;                                   
			}                                       
		break;                          
	}       // end_switch

#endif //__UseOGX__
}
 

//	Feldinformationen ausgeben
void ShowFile::OnFieldinfo (void)
{
#ifdef WIN32
	CFeldInfoDialog FI (this, &m_CColList);
#else
	CFeldInfo FI (this, &m_CColList);
#endif
	if (FI.Result ())
		FI.DoModal ();
}

/*
void ShowFile::OnTimer(UINT nIDEvent)
{
	TRACE("Von Zeit zu Zeit");
	if (m_nTicksSinceResize < 0 || nIDEvent != m_nTimer) 
		return;
	
	m_nTicksSinceResize++;
	if (5 == m_nTicksSinceResize)
	{
		m_nTicksSinceResize = -1;	// Tickern beenden
//		m_wndRecord.Redraw();		// neu zeichnen

		// eigentlich noch den timer kaputten
	}
}
*/
void ShowFile::Save()
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState());
	CString strSelector;
//	VERIFY(strSelector.LoadString(IDS_FILESELECTOR));*/

	strSelector = _T("Text Dateien (*.txt)|*.txt|Alle Dateien (*.*)|*.*||");

 	// pop-up file-open dlg to ask for location
 	CFileDialog dlgFile(
 		FALSE,
 		_T(".txt"),
 		NULL,
 		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
 		strSelector);
 
 	if (dlgFile.DoModal() == IDCANCEL)
 		return;
 
 	CFile textFile;
 
 	if (!textFile.Open(dlgFile.GetFileName(),
 		CFile::modeCreate | CFile::modeWrite))
 	{
		CString strErr;
		VERIFY(strErr.LoadString(IDS_FILENOTOPEN));

		strErr.Format(strErr, dlgFile.GetFileName());
 		AfxMessageBox(strErr);
 		return;
 	}
 
 	m_wndRecord.CopyTextToFile( textFile, 
 		CGXRange(0, 1, m_wndRecord.GetRowCount(), m_wndRecord.GetColCount()) );
 
 	textFile.Close();
}

void ShowFile::SetGridStyle()
{
	bool bOldLock = m_wndRecord.LockUpdate();
	m_wndRecord.SetCanAppend(false);				// neue Records ausschalten
	m_wndRecord.ResizeColWidthsToFit(CGXRange().SetTable());
	m_wndRecord.ResizeRowHeightsToFit(CGXRange().SetTable());
	m_wndRecord.LockUpdate(bOldLock );

	m_wndRecord.m_wndParent = this;
}

void ShowFile::OnUpdateAnySort(CCmdUI* pCmdUI) 
{
	ASSERT(pCmdUI);
	if (NULL == pCmdUI)
		return;

	// die aktuelle Spalte holen 
	ROWCOL nRow, nCol;
	if (!m_wndRecord.GetCurrentCell(nRow, nCol) || nCol == 0)
	{
		pCmdUI->Enable(false);

	}
}

void ShowFile::OnSortGridAsc()
{
	// die aktuelle Spalte holen 
	ROWCOL nRow, nCol;
	if (m_wndRecord.GetCurrentCell(nRow, nCol))
	{
		// danach sortieren lassen
		m_wndRecord.DoSort(nCol, 1);
	}
}

void ShowFile::OnSortGridDesc()
{
	// die aktuelle Spalte holen 
	ROWCOL nRow, nCol;
	if (m_wndRecord.GetCurrentCell(nRow, nCol))
	{
		// danach sortieren lassen
		m_wndRecord.DoSort(nCol, -1);
	}
}

void ShowFile::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu) 
{
	if (!bSysMenu)
	{
	
		ASSERT(pPopupMenu != NULL);

//		SetMenuBitmaps(pPopupMenu);	// Menuentries are to small to show a bitmap

		// check the enabled state of various menu items
		CCmdUI state;
		state.m_pMenu = pPopupMenu;
		ASSERT(state.m_pOther == NULL);

		state.m_nIndexMax = pPopupMenu->GetMenuItemCount();
		for (state.m_nIndex = 0; state.m_nIndex < state.m_nIndexMax;
			 state.m_nIndex++)
		{
			state.m_nID = pPopupMenu->GetMenuItemID(state.m_nIndex);
			if (state.m_nID == 0)
				continue; // menu separator or invalid cmd - ignore it

			ASSERT(state.m_pOther == NULL);
			ASSERT(state.m_pMenu != NULL);
			if (state.m_nID == (UINT)-1)
			{
				// possibly a popup menu, route to first item of that popup
				state.m_pSubMenu = pPopupMenu->GetSubMenu(state.m_nIndex);
				if (state.m_pSubMenu == NULL ||
					(state.m_nID = state.m_pSubMenu->GetMenuItemID(0)) == 0 ||
					state.m_nID == (UINT)-1)
				{
					continue; // first item of popup can't be routed to
				}
				state.DoUpdate(this, FALSE);  // popups are never auto disabled
			}
			else
			{
				uint nItem = (uint)state.m_nID - (uint)IDM_REL;
				if (nItem >= 0 && nItem < (uint) m_sRelCnt)
				{
					// Relationen Menü
					// lassen wie's ist
				}
				else
				{
					// normal menu item
					// Auto enable/disable if command is _not_ a system command
					state.m_pSubMenu = NULL;
					state.DoUpdate(this, state.m_nID < 0xF000);
				}
			}
		}
	}

	CDialog::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);
}

void ShowFile::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
	ASSERT(pCmdUI);
	if (NULL == pCmdUI)
		return;
	
	pCmdUI->Enable(m_wndRecord.CanCopy());
}

void ShowFile::OnUpdateEditUndo(CCmdUI* pCmdUI) 
{
	ASSERT(pCmdUI);
	if (NULL == pCmdUI)
		return;
	
	pCmdUI->Enable(m_wndRecord.CanUndo(pCmdUI));
}

void ShowFile::OnUpdateEditRedo(CCmdUI* pCmdUI) 
{
	ASSERT(pCmdUI);
	if (NULL == pCmdUI)
		return;
	
	pCmdUI->Enable(m_wndRecord.CanRedo(pCmdUI));
}

void ShowFile::OnUpdateEditCut(CCmdUI* pCmdUI) 
{
	ASSERT(pCmdUI);
	if (NULL == pCmdUI)
		return;
	
	pCmdUI->Enable(m_wndRecord.CanCut());
}

void ShowFile::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	ASSERT(pCmdUI);
	if (NULL == pCmdUI)
		return;
	
	pCmdUI->Enable(m_wndRecord.CanPaste());
}

void ShowFile::OnUpdateEditClear(CCmdUI* pCmdUI) 
{
	ASSERT(pCmdUI);
	if (NULL == pCmdUI)
		return;
	
	pCmdUI->Enable(m_wndRecord.CanClear());
}

void ShowFile::OnEditCopy()
{
	m_wndRecord.Copy();
}

void ShowFile::OnEditUndo()
{
	m_wndRecord.Undo();
}

void ShowFile::OnEditRedo()
{
	m_wndRecord.Redo();
}

void ShowFile::OnEditCut()
{
	m_wndRecord.Cut();
}

void ShowFile::OnEditPaste()
{
	m_wndRecord.Paste();
}

void ShowFile::OnEditClear()
{
	m_wndRecord.Clear();
}

void ShowFile::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	CDialog::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}
