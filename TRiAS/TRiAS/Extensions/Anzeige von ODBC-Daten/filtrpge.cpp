// filtrpge.cpp : implementation file
//

#include "pheader.h"
#include "odbcext.hr"				// Resource-Konstanten

#include <hpp/columnst.hpp>				// CColumns
#include <hpp/helptext.hpp>				// CHelpText
#include <hpp/getodbci.hpp>				// COdbcInfos
#include <hpp/waitcur.hpp>				// CWaitCursor
#include <hpp/odbcerr.hpp>				// OdbcError
#include "database.hpp"				// CDataBaseExt
#include <hpp/chklausl.hpp>             // CheckWhereKlausel ()
#include <hpp/fieldinf.hpp>             // CFieldInf        

#include "importpa.hpp"				// CImportParams
#include "filtrpge.hpp"				// zugeh. Header

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//	lokale Variablen
static uint OperatorDescArray [MaxOperators];
static uint FunctionDescArray [MaxFunctions];

//	externe Variablen
extern CImportParams *g_pCParams;
#ifndef WIN32
extern CPropertySheetExt *g_pSheet;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFilterPage property page

IMPLEMENT_DYNCREATE(CFilterPage, CPropertyPage)

CFilterPage::CFilterPage() : CPropertyPage(CFilterPage::IDD)
{
	//{{AFX_DATA_INIT(CFilterPage)
	//}}AFX_DATA_INIT
#ifdef WIN32
	m_sNameSort = m_sTypeSort = m_sLenSort = NotSorted;
#endif	
	m_bIsChecked = FALSE;			// wenn Ausdruck geprüft wurde
}

CFilterPage::~CFilterPage()
{
}

void CFilterPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFilterPage)
	DDX_Control(pDX, IDT_IMP_FILTER_DESCR, m_Description);
	DDX_Control(pDX, IDB_FILTER_CHECK, m_btFilterCheck);
	DDX_Control(pDX, IDL_FILTER_FELD, m_lcFelder);
	DDX_Control(pDX, IDL_FILTER_OPERA, m_lbOperatoren);
	DDX_Control(pDX, IDL_FILTER_FUNKT, m_lbFunktionen);
	DDX_Control(pDX, IDE_FILTER_KLAUSEL, m_edKlausel);
	//}}AFX_DATA_MAP
}

#ifdef WIN32
BEGIN_MESSAGE_MAP(CFilterPage, CPropertyPage)
	//{{AFX_MSG_MAP(CFilterPage)
	ON_EN_CHANGE(IDE_FILTER_KLAUSEL, OnChangeFilterKlausel)
	ON_LBN_SELCHANGE(IDL_FILTER_FUNKT, OnSelchangeFilterFunkt)
	ON_LBN_DBLCLK(IDL_FILTER_FUNKT, OnDblclkFilterFunkt)
	ON_LBN_DBLCLK(IDL_FILTER_OPERA, OnDblclkFilterOpera)
	ON_LBN_SELCHANGE(IDL_FILTER_OPERA, OnSelchangeFilterOpera)
	ON_NOTIFY(LVN_DELETEITEM, IDL_FILTER_FELD, OnDeleteitemFilterFeld)
	ON_NOTIFY(LVN_COLUMNCLICK, IDL_FILTER_FELD, OnColumnclickFilterFeld)
	ON_NOTIFY(NM_DBLCLK, IDL_FILTER_FELD, OnDblclkFilterFeld)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDB_FILTER_CHECK, OnFilterCheck)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#else 			// WIN16                     
BEGIN_MESSAGE_MAP(CFilterPage, CPropertyPage)
	ON_EN_CHANGE(IDE_FILTER_KLAUSEL, OnChangeFilterKlausel)  
	ON_LBN_SELCHANGE(IDL_FILTER_FUNKT, OnSelchangeFilterFunkt)
	ON_LBN_SELCHANGE(IDL_FILTER_OPERA, OnSelchangeFilterOpera)
	ON_LBN_SELCHANGE(IDL_FILTER_FELD, OnSelchangeFilterFeld)	
	ON_LBN_DBLCLK(IDL_FILTER_FUNKT, OnDblclkFilterFunkt)
	ON_LBN_DBLCLK(IDL_FILTER_OPERA, OnDblclkFilterOpera)
	ON_LBN_DBLCLK(IDL_FILTER_FELD, OnDblclkFilterFeld)
	ON_BN_CLICKED(IDB_FILTER_CHECK, OnFilterCheck)
	ON_WM_DESTROY()
	ON_MESSAGE(IDM_SETFOCUS, OnSetFocusToControl)
END_MESSAGE_MAP()	
#endif			// WIN16

/////////////////////////////////////////////////////////////////////////////
// CFilterPage message handlers: ok !
void CFilterPage::OnFilterCheck() 
{
//	prüfe Parameter
	ASSERT (g_pCParams != NULL);

// 	TODO: Add your control notification handler code here
	m_btFilterCheck.EnableWindow (FALSE);		// keine weiteren Eingaben zulassen
	CString strKlausel, strError;
	m_edKlausel.GetWindowText (strKlausel);
	short sErrorPos = -1;
	
	m_bIsChecked = :: CheckWhereKlausel ((CDatabase *) g_pCParams -> m_COdbcInfos.m_pDataBase, 
									   g_pCParams -> m_strTableName, strKlausel, 
									   strError, sErrorPos);
		
	if (!strError.IsEmpty ())
		m_Description.SetWindowText (strError);					
			
	if (sErrorPos != -1)
		m_edKlausel.SetSel (sErrorPos, sErrorPos);
			
//	Fehlermeldung ggf. ausgeben									  
	if (! m_bIsChecked)          
	{
		m_edKlausel.SetFocus ();
		:: MessageBeep (MB_ICONHAND);			
	}		

//	Ok-Button setzen
	SetOkButton ();
}

void CFilterPage::OnChangeFilterKlausel() 
{
// 	TODO: Add your control notification handler code here
	BOOL bEnable = m_edKlausel.LineLength () > 0 ? TRUE : FALSE;
	m_btFilterCheck.EnableWindow (bEnable); 	
	SetOkButton ();		
}

//	Funktions-Beschreibung ausgeben
void CFilterPage::OnSelchangeFilterFunkt() 
{
// 	TODO: Add your control notification handler code here
	int iActSel = m_lbFunktionen.GetCurSel ();		
	if ((iActSel >= 0) && (iActSel < MaxFunctions))		// wenn Index gültig
	{                          
		uint uResID = FunctionDescArray [iActSel];
		if (uResID)
			m_Description.Output (uResID);			// Beschreibung ausgeben
	}	
}				

//	Operator-Beschreibung ausgeben
void CFilterPage::OnSelchangeFilterOpera() 
{
// 	TODO: Add your control notification handler code here

	int iActSel = m_lbOperatoren.GetCurSel ();		
	if ((iActSel >= 0) && (iActSel < MaxOperators))		// wenn Index gültig
	{                          
		uint uResID = OperatorDescArray [iActSel];
		if (uResID)
			m_Description.Output (uResID);			// Beschreibung ausgeben
	}
}   

#ifndef WIN32
//	Feld-Beschreibung ausgeben
void CFilterPage::OnSelchangeFilterFeld() 
{
// 	TODO: Add your control notification handler code here
	int iActSel = m_lcFelder.GetCurSel ();		
	if (iActSel >= 0)		// wenn Index gültig
	{                          
		ASSERT (g_pCParams != NULL);
		CString strSel;
		m_lcFelder.GetText (iActSel, strSel);		
		g_pCParams -> m_COdbcInfos.OutputColumnInfo (strSel, m_Description);
	}
}   
#endif	// WIN16

//	neue Filter-Funktion gewählt
void CFilterPage::OnDblclkFilterFunkt() 
{
	int iCurSel = m_lbFunktionen.GetCurSel ();
	if (iCurSel < 0)
		return;

// 	TODO: Add your control notification handler code here
	TRY
	{   
		CString strFunction, strFormat, strValue;		
		m_lbFunktionen.GetText (iCurSel, strFunction);
		strFormat.LoadString (IDS_SCALE_FCN_FORMAT);
		char *pBuffer = strValue.GetBuffer (strFormat.GetLength () + 
											strFunction.GetLength () + 10);
		wsprintf (pBuffer, strFormat, (const char *) strFunction);
		m_edKlausel.ReplaceSel (pBuffer);	
	}
	CATCH (CMemoryException, me)
	{   
		DEX_Error (RC_OdbcImport, EC_NOMEMORY);
	}	
	END_CATCH		
}

//	neuer Operator gewählt 
void CFilterPage::OnDblclkFilterOpera() 
{
// 	TODO: Add your control notification handler code here
	int iCurSel = m_lbOperatoren.GetCurSel ();
	if (iCurSel < 0)
		return;

	TRY
	{
		CString strSel;
		
	//	Operator lesen
		CString strOperator;
		m_lbOperatoren.GetText (iCurSel, strOperator);
		                                           
	//	Wert komplettieren
	//	if ((sIndex < 3) || 	// für diese Operatoren
	//		(sIndex > 5))		// keine führenden Leerzeichen
		strSel = " ";
		strSel += strOperator;
		strSel += " ";

		m_edKlausel.ReplaceSel (strSel);    // Wert im Editfeld einfügen
	}
	CATCH (CMemoryException, me)
	{
		DEX_Error (RC_CCreateWhereKlDlg, EC_NOMEMORY);
	}		
	END_CATCH
}

#ifdef WIN32
void CFilterPage::OnDblclkFilterFeld(NMHDR* pNMHDR, LRESULT* pResult) 
{
// 	TODO: Add your control notification handler code here
	TRY
	{   
		int iIndex = m_lcFelder.GetNextItem (-1, LVNI_SELECTED);
		if (iIndex >= 0)
		{
			CFeldInf *pFI = (CFeldInf *) m_lcFelder.GetItemData (iIndex);
			ASSERT (pFI != NULL);
			CString strFeldName;
			AfxFormatString1 (strFeldName, IDS_FIELDNAME_FORMAT, pFI -> m_strName);
			m_edKlausel.ReplaceSel (strFeldName);		
		}
	}
	CATCH (CMemoryException, me)
	{   
		DEX_Error (RC_CCreateWhereKlDlg, EC_NOMEMORY);
	}	
	END_CATCH

	*pResult = 0;
}           
#else 
void CFilterPage::OnDblclkFilterFeld() 
{
// 	TODO: Add your control notification handler code here
	TRY
	{   
		int iIndex = m_lcFelder.GetCurSel ();
		if (iIndex >= 0)			// gültiger Index
		{
			CString strFeldName, strSel;
			m_lcFelder.GetText (iIndex, strSel);		// Feldnamen lesen
			AfxFormatString1 (strFeldName, IDS_FIELDNAME_FORMAT, strSel);
			m_edKlausel.ReplaceSel (strFeldName);		
		}
	}
	CATCH (CMemoryException, me)
	{   
		DEX_Error (RC_CCreateWhereKlDlg, EC_NOMEMORY);
	}	
	END_CATCH
}           
#endif		// WIN16
            
#ifdef WIN32            
//	Sortierung gewünscht !
void CFilterPage::OnColumnclickFilterFeld(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here

	ASSERT (pNMListView != NULL);

	short sAttr = 0;
	if (pNMListView -> iSubItem == 0)		// Feldnamen sortieren
	{
		sAttr = SortName;			
		if ((m_sNameSort == SortDesc) || (m_sNameSort == NotSorted))
			sAttr |= (m_sNameSort = SortAsc);
		else
			sAttr |= (m_sNameSort = SortDesc);
	}
	else									
	{										
		if (pNMListView -> iSubItem == 1)	// Feldtypen sortieren
		{
			sAttr = SortType;
			if ((m_sTypeSort == SortDesc) || (m_sTypeSort == NotSorted))
				sAttr |= (m_sTypeSort = SortAsc);
			else
				sAttr |= (m_sTypeSort = SortDesc);
		}
		else
		{
	 		sAttr = SortLen;				// Feldlängen sortieren
			if ((m_sLenSort == SortDesc) || (m_sLenSort == NotSorted))
				sAttr |= (m_sLenSort = SortAsc);
			else
				sAttr |= (m_sLenSort = SortDesc);
		}
	}

	CWaitCursor wc;
	m_lcFelder.SortItems (CompareFelderFunction, sAttr);

	*pResult = 0;
}           
#endif		// WIN32

//	Parameter lesen
BOOL CFilterPage :: ReadParams (void)
{
	ASSERT (g_pCParams != NULL);					// Parameter prüfen

	TRY
	{
#ifdef WIN32	
	//	zuerst Filter prüfen
		if (m_strDataSource != g_pCParams -> m_strDataSource ||
			m_strTableName != g_pCParams -> m_strTableName ||
			m_strFilter != g_pCParams -> m_strFilter)
		{
			m_strFilter = g_pCParams -> m_strFilter;			
			m_edKlausel.SetWindowText (m_strFilter);
			m_bIsChecked = FALSE;
		}

	//	hat sich DataSource oder Tabelle geändert ?
		if (m_strDataSource == g_pCParams -> m_strDataSource &&
			m_strTableName == g_pCParams -> m_strTableName)
			return TRUE;
#endif			

	//	Neuinit. beginnt
		CWaitCursor wc;						// Sanduhr einschalten
		
		ASSERT (g_pCParams -> m_COdbcInfos.m_pDataBase != NULL);
		ASSERT (g_pCParams -> m_strTableName.GetLength () > 0);
    
#ifdef WIN32    
	//	neuen Parameter speichern
		m_strTableName = g_pCParams -> m_strTableName;

	//	ListBoxen löschen
		if (m_lcFelder.GetItemCount () > 0)
			m_lcFelder.DeleteAllItems ();             
		
	//	mögliche Koppelfelder ausgeben
		CColumns Col ((CDatabase *) g_pCParams -> m_COdbcInfos.m_pDataBase);
		Col.m_strTableNameParam = g_pCParams -> m_strTableName;    // Namen für ODBC speichern
		int iKI = 0;					// Koppelfeld-Index
		char szLenBuffer [30] = "";		// Längenpuffer
		CFeldInf *pFeldInfo = NULL;		// ItemData
		if (Col.Open ())				// Set öffnen
		{   
			while (! Col.IsEOF ())
			{   
			//	ist dieses Feld ein Koordinatenfeld ?				
				if (Col.IsKoppelField ())
				{
				//	ItemData erzeugen
					pFeldInfo = new CFeldInf (Col.m_strColumnName, Col.m_strTypeName, Col.m_lLength);

				//	Feldinfos ausgeben
					ltoa (Col.m_lLength, szLenBuffer, 10);	// Länge bestimmen
					if ((m_lcFelder.InsertItem (iKI, Col.m_strColumnName) == iKI) &&
					 	m_lcFelder.SetItemText (iKI, 1, (char*)(const char*)Col.m_strTypeName) && 
					 	m_lcFelder.SetItemText (iKI, 2, szLenBuffer) &&
						m_lcFelder.SetItemData (iKI, (DWORD) pFeldInfo))


						iKI++;
					else
						AfxThrowUserException();					
				}
				Col.MoveNext ();		// zum nächsten Feld
			}	// end_while
		}
		else
		{
			DEX_Error (RC_OdbcImport, EC_NOOPENDSN);
			return FALSE;
		}   
#else	// WIN16: 	mögliche Koppelfelder ausgeben	     
		CColumns *pCol = g_pCParams -> m_COdbcInfos.m_pColumns;       
		ASSERT (pCol != NULL && pCol -> IsOpen ());
		pCol -> MoveFirst ();
		while (! pCol -> IsEOF ())
		{   
			if (pCol -> IsKoppelField ())	// 	ist dieses Feld ein Koppelfeld ?
			{
			// 	Feldname ausgeben
				if (m_lcFelder.AddString (pCol -> m_strColumnName) < 0)
					AfxThrowUserException ();                        
			}						
										
			pCol -> MoveNext ();		// zum nächsten Feld
		}
#endif 	// WIN16
                
#ifdef WIN32                
	//	ggf. Funktionsfeld neu init.
		if (m_strDataSource != g_pCParams -> m_strDataSource)
		{
			m_strDataSource = g_pCParams -> m_strDataSource;		// Namen speichern

			if (m_lbFunktionen.GetCount () > 0)						// ListBox löschen
				m_lbFunktionen.ResetContent ();
#endif		// WIN32				

		//	Functionfeld init.      
			memset (&FunctionDescArray, 0, sizeof (FunctionDescArray) /
										   sizeof (uint));
									   
		//	lese String-Funktionen-Flag
			UDWORD	fFuncs = 0;            
			RETCODE nRetCode;		
			AFX_SQL_ASYNC (g_pCParams -> m_COdbcInfos.m_pDataBase, 
						   :: SQLGetInfo (g_pCParams -> m_COdbcInfos.m_pDataBase -> m_hdbc, 
						   SQL_STRING_FUNCTIONS, &fFuncs, sizeof (fFuncs), NULL));
		
		//	prüfe Ret-Kode									  
			if (nRetCode != SQL_SUCCESS)                                 
				AfxThrowUserException ();
		    
		//	gebe zugeh. String-Funktionen in ListBox aus und speichere 
		//	deren Beschreibungs-ResID
			uint uIndex = 0;				// Beschreibungs-Array-Index init.
			GetScaleFunction (uIndex, IDS_STRING_ACII, SQL_FN_STR_ASCII, fFuncs);
			GetScaleFunction (uIndex, IDS_STRING_CHAR, SQL_FN_STR_CHAR, fFuncs);
			GetScaleFunction (uIndex, IDS_STRING_CONCAT, SQL_FN_STR_CONCAT, fFuncs);
			GetScaleFunction (uIndex, IDS_STRING_INSERT, SQL_FN_STR_INSERT, fFuncs);
			GetScaleFunction (uIndex, IDS_STRING_LCASE, SQL_FN_STR_LCASE, fFuncs);
			GetScaleFunction (uIndex, IDS_STRING_LEFT, SQL_FN_STR_LEFT, fFuncs);
			GetScaleFunction (uIndex, IDS_STRING_LENGTH, SQL_FN_STR_LENGTH, fFuncs);
			GetScaleFunction (uIndex, IDS_STRING_LOCATE, SQL_FN_STR_LOCATE, fFuncs);
			GetScaleFunction (uIndex, IDS_STRING_LTRIM, SQL_FN_STR_LTRIM, fFuncs);
			GetScaleFunction (uIndex, IDS_STRING_REPEAT, SQL_FN_STR_REPEAT, fFuncs);
			GetScaleFunction (uIndex, IDS_STRING_REPLACE, SQL_FN_STR_REPLACE, fFuncs);
			GetScaleFunction (uIndex, IDS_STRING_RIGHT, SQL_FN_STR_RIGHT, fFuncs);
			GetScaleFunction (uIndex, IDS_STRING_RTRIM, SQL_FN_STR_RTRIM, fFuncs);
			GetScaleFunction (uIndex, IDS_STRING_SUBSTRING, SQL_FN_STR_SUBSTRING, fFuncs);
			GetScaleFunction (uIndex, IDS_STRING_UCASE, SQL_FN_STR_UCASE, fFuncs);				
		
		//	lese Konvertierungs-Funktionen 
			fFuncs = 0;            
			AFX_SQL_ASYNC (g_pCParams -> m_COdbcInfos.m_pDataBase, :: 
						   SQLGetInfo (g_pCParams -> m_COdbcInfos.m_pDataBase -> m_hdbc, 
						   SQL_CONVERT_FUNCTIONS, &fFuncs, sizeof (fFuncs), NULL));
		
		//	prüfe Ret-Kode									  
			if (nRetCode != SQL_SUCCESS)                                 
				AfxThrowUserException ();
			GetScaleFunction (uIndex, IDS_CVT_CONVERT, SQL_FN_CVT_CONVERT, fFuncs);
		
		//	lese numerische Funktionen
			fFuncs = 0;            
			AFX_SQL_ASYNC (g_pCParams -> m_COdbcInfos.m_pDataBase, 
						   :: SQLGetInfo (g_pCParams -> m_COdbcInfos.m_pDataBase -> m_hdbc, 
						   SQL_NUMERIC_FUNCTIONS, &fFuncs, sizeof (fFuncs), NULL));					
					   
			if (nRetCode != SQL_SUCCESS)                                 
				AfxThrowUserException ();
			GetScaleFunction (uIndex, IDS_NUM_ABS, SQL_FN_NUM_ABS, fFuncs);
			GetScaleFunction (uIndex, IDS_NUM_ACOS, SQL_FN_NUM_ACOS, fFuncs);
			GetScaleFunction (uIndex, IDS_NUM_ASIN, SQL_FN_NUM_ASIN, fFuncs);
			GetScaleFunction (uIndex, IDS_NUM_ATAN, SQL_FN_NUM_ATAN, fFuncs);
			GetScaleFunction (uIndex, IDS_NUM_ATAN2, SQL_FN_NUM_ATAN2, fFuncs);
			GetScaleFunction (uIndex, IDS_NUM_CEILING, SQL_FN_NUM_CEILING, fFuncs);
			GetScaleFunction (uIndex, IDS_NUM_COS, SQL_FN_NUM_COS, fFuncs);
			GetScaleFunction (uIndex, IDS_NUM_COT, SQL_FN_NUM_COT, fFuncs);
			GetScaleFunction (uIndex, IDS_NUM_EXP, SQL_FN_NUM_EXP, fFuncs);
			GetScaleFunction (uIndex, IDS_NUM_FLOOR, SQL_FN_NUM_FLOOR, fFuncs);
			GetScaleFunction (uIndex, IDS_NUM_LOG, SQL_FN_NUM_LOG, fFuncs);
			GetScaleFunction (uIndex, IDS_NUM_MOD, SQL_FN_NUM_MOD, fFuncs);
			GetScaleFunction (uIndex, IDS_NUM_PI, SQL_FN_NUM_PI, fFuncs);
			GetScaleFunction (uIndex, IDS_NUM_RAND, SQL_FN_NUM_RAND, fFuncs);
			GetScaleFunction (uIndex, IDS_NUM_SIGN, SQL_FN_NUM_SIGN, fFuncs);
			GetScaleFunction (uIndex, IDS_NUM_SIN, SQL_FN_NUM_SIN, fFuncs);
			GetScaleFunction (uIndex, IDS_NUM_SQRT, SQL_FN_NUM_SQRT, fFuncs);
			GetScaleFunction (uIndex, IDS_NUM_TAN, SQL_FN_NUM_TAN, fFuncs);				
		
		//	lese Datums-Funktionen
			fFuncs = 0;            
			AFX_SQL_ASYNC (g_pCParams -> m_COdbcInfos.m_pDataBase, 
					       :: SQLGetInfo (g_pCParams -> m_COdbcInfos.m_pDataBase -> m_hdbc, 
						   SQL_TIMEDATE_FUNCTIONS, &fFuncs, sizeof (fFuncs), NULL));					
					   
			if (nRetCode != SQL_SUCCESS)                                 
				AfxThrowUserException ();
			GetScaleFunction (uIndex, IDS_TD_NOW, SQL_FN_TD_NOW, fFuncs);
			GetScaleFunction (uIndex, IDS_TD_CURDATE, SQL_FN_TD_CURDATE, fFuncs);
			GetScaleFunction (uIndex, IDS_TD_DAYOFMONTH, SQL_FN_TD_DAYOFMONTH, fFuncs);		
			GetScaleFunction (uIndex, IDS_TD_DAYOFWEEK, SQL_FN_TD_DAYOFWEEK, fFuncs);
			GetScaleFunction (uIndex, IDS_TD_DAYOFYEAR, SQL_FN_TD_DAYOFYEAR, fFuncs);		
			GetScaleFunction (uIndex, IDS_TD_MONTH, SQL_FN_TD_MONTH, fFuncs);
			GetScaleFunction (uIndex, IDS_TD_QUARTER, SQL_FN_TD_QUARTER, fFuncs);		
			GetScaleFunction (uIndex, IDS_TD_WEEK, SQL_FN_TD_WEEK, fFuncs);
			GetScaleFunction (uIndex, IDS_TD_YEAR, SQL_FN_TD_YEAR, fFuncs);
			GetScaleFunction (uIndex, IDS_TD_CURTIME, SQL_FN_TD_CURTIME, fFuncs);		
			GetScaleFunction (uIndex, IDS_TD_HOUR, SQL_FN_TD_HOUR, fFuncs);
			GetScaleFunction (uIndex, IDS_TD_MINUTE, SQL_FN_TD_MINUTE, fFuncs);
			GetScaleFunction (uIndex, IDS_TD_SECOND, SQL_FN_TD_SECOND, fFuncs);					
#ifdef WIN32			
		}   	// Felder immer neu init.
#endif		
	} 
	CATCH (CMemoryException, me)
	{
		DEX_Error (RC_OdbcImport, EC_NOMEMORY);
		return FALSE;
	}
	AND_CATCH (CUserException, me)
	{
		DEX_Error (RC_OdbcImport, EC_SYSERROR);		
		return FALSE;
	}
	AND_CATCH (CDBException, dbe)
	{
		OdbcError oe (dbe);
		oe.Show (RC_OdbcImport);                                     			
		return FALSE;
	}
	AND_CATCH (CFileException, fe)
	{
		// DEX_Error (RC_OdbcImport, EC_SYSERROR);		
		fe -> ReportError ();
		return FALSE;
	}
	END_CATCH

#ifdef WIN32
//	Sortierungsart setzen
	m_sNameSort = SortAsc;
	m_sTypeSort = m_sLenSort = NotSorted;
	m_lcFelder.SortItems (CompareFelderFunction, SortName | m_sNameSort); 
#endif																				

	return TRUE;
}

#ifdef WIN32
//	SatzInfo löschen: ok !
void CFilterPage::OnDeleteitemFilterFeld(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here

	CFeldInf *pFI = (CFeldInf *) (pNMListView -> lParam);
	ASSERT (pFI != NULL);
	DELETE_OBJ (pFI);
	
	*pResult = 0;
}                   
#endif		// WIN32

//	Seite wird zerstört: ok !
void CFilterPage::OnDestroy() 
{   
	CPropertyPage::OnDestroy();
// 	TODO: Add your message handler code here
#ifdef WIN32	
	if (m_lcFelder.GetItemCount ())
		m_lcFelder.DeleteAllItems ();  
#else		
	GetUserEntries (TRUE);		
	m_Description.GetWindowText (m_strLastInfo);
#endif	
}                   

//	Dialog init.: ok !
BOOL CFilterPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	BOOL bOk = FALSE;
	
// 	TODO: Add extra initialization here
	TRY
	{                   
		 if (!m_Description.InitFont ())
			AfxThrowUserException ();
                        
		CString strText;                        
#ifdef WIN32
	//	"FeldName"
		if (! strText.LoadString (IDS_IMP_FELDNAME) || 
		   (m_lcFelder.InsertColumn (0, strText) != 0))
			AfxThrowUserException ();

	//	"Typ"
		if (! strText.LoadString (IDS_IMP_FELDTYP) || 
		   (m_lcFelder.InsertColumn (1, strText) != 1))
			AfxThrowUserException ();									

	// 	"Länge"
		if (! strText.LoadString (IDS_IMP_FELDLAENGE) || 
		   (m_lcFelder.InsertColumn (2, strText) != 2))
			AfxThrowUserException ();														

	//	Spaltenbreiten setzen
		m_lcFelder.SetColumnWidth (0, LVSCW_AUTOSIZE_USEHEADER);		
		m_lcFelder.SetColumnWidth (1, LVSCW_AUTOSIZE_USEHEADER);		
		m_lcFelder.SetColumnWidth (2, LVSCW_AUTOSIZE_USEHEADER);		

	//	Selektion "beibehalten" setzen
		long lAttr = :: GetWindowLong (m_lcFelder.m_hWnd, GWL_STYLE);
		:: SetWindowLong (m_lcFelder.m_hWnd, GWL_STYLE, lAttr | LVS_SHOWSELALWAYS);
#endif		

	// 	Edit-Feld begrenzen
		m_edKlausel.LimitText (KlauselSize);

	//	Operatorfeld init.      
		memset (&OperatorDescArray, 0, sizeof (OperatorDescArray) / sizeof (uint));			
									   
		uint uActResID = IDS_AND_OP;
		for (short sIndex = 0; sIndex < MaxOperators; sIndex++, uActResID += 2)
		{   
		//	akt. String laden
			if (strText.LoadString (uActResID) &&			// String aus Resource laden
			   (m_lbOperatoren.AddString (strText) >= 0))	// String in ListBox
			    OperatorDescArray [sIndex] = uActResID + 1;	// ResID speichern							
			else
				AfxThrowUserException ();
		}     
		bOk = TRUE;
	}
	CATCH (CMemoryException, me)
	{
		DEX_Error (RC_OdbcImport, EC_NOMEMORY);
	}
	AND_CATCH (CUserException, me)
	{
		DEX_Error (RC_OdbcImport, EC_SYSERROR);		
	}
	END_CATCH   
	
	if (!bOk)
	{
		GetParent () -> EndDialog (IDCANCEL);
		return FALSE;
	}
	
#ifndef WIN32
	if (!ReadParams ())
	{
		GetParent () -> EndDialog (IDCANCEL);
		return FALSE;
	}

//	Control-Status setzen
	m_lcFelder.EnableWindow (m_lcFelder.GetCount () > 0 ? TRUE : FALSE);
	m_lbFunktionen.EnableWindow (m_lbFunktionen.GetCount () > 0 ? TRUE : FALSE);
	m_lbOperatoren.EnableWindow (m_lbOperatoren.GetCount () > 0 ? TRUE : FALSE);
	m_btFilterCheck.EnableWindow (m_edKlausel.LineLength () > 0 ? TRUE : FALSE);
	
	m_edKlausel.SetWindowText (g_pCParams -> m_strFilter);
	m_edKlausel.SetFocus ();
	
	if (g_pCParams -> m_strFilter.IsEmpty ())
		m_bIsChecked = FALSE;
	else
		if (g_pCParams -> m_strFilter != m_strFilter)
			m_bIsChecked = FALSE;	// sonst bleibt alte Flag erhalten					 
			       
//	letzte Info setzen			       
	m_Description.SetWindowText (m_strLastInfo);			
	
	SetOkButton ();

	UpdateWindow ();
	PostMessage (IDM_SETFOCUS, 0, 0L);
#endif	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//	globales Ok-Button setzen: ok !
void CFilterPage :: SetOkButton (void)
{
	if (m_bIsChecked || m_edKlausel.LineLength () <= 0)
#ifdef WIN32
		GetParent () -> SetWizardButtons (PSWIZB_NEXT | PSWIZB_BACK);
	else
		GetParent () -> SetWizardButtons (PSWIZB_BACK);							
#else
		g_pSheet -> SetWizardButtons (PSWIZB_NEXT | PSWIZB_BACK);
	else                                                            
		g_pSheet -> SetWizardButtons (PSWIZB_BACK);							
#endif		// WIN16
}

//	Nutzereingaben lesen: ok !
BOOL CFilterPage :: GetUserEntries (BOOL bGet)	
{
	ASSERT (g_pCParams != NULL);

//	zuerst alten Infos löschen
	g_pCParams -> m_strFilter.Empty ();
	if (!bGet)
		return TRUE;
                 
	m_edKlausel.GetWindowText (m_strFilter);
	m_edKlausel.GetWindowText (g_pCParams -> m_strFilter);
	
	return TRUE; 		
}

//	prüfe und lese Beschreibungs-Info einer skalaren Funktion
void CFilterPage :: GetScaleFunction (uint &uIndex, uint uResID,
									  UDWORD uwCheckFlag, UDWORD fFlag)
{
	if (uwCheckFlag & fFlag)
	{                            
		CString strText;
		TRY 
		{
			if (!strText.LoadString (uResID))
				AfxThrowUserException ();
			if (m_lbFunktionen.AddString (strText) < 0)
				AfxThrowMemoryException ();

			FunctionDescArray [uIndex] = ++uResID;							
			uIndex++;    
		}
		CATCH (CMemoryException, me)
		{        
			THROW_LAST ();		// diese Exception zum nächsten Handler
		}
		AND_CATCH (CUserException, ue)
		{
			THROW_LAST ();		// auch diese Exception zum nächsten Handler
		}
		END_CATCH			
	}
}	 	

void CFilterPage::OnCancel() 
{
	// TODO: Add your specialized code here and/or call the base class
	GetUserEntries (FALSE);
	
	CPropertyPage::OnCancel();
}

BOOL CFilterPage::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
#ifdef WIN32	
	if (!ReadParams ())
	{
		GetParent () -> EndDialog (IDCANCEL);
		return FALSE;
	}

	SetOkButton ();
	
//	Control-Status setzen
	m_lcFelder.EnableWindow (m_lcFelder.GetItemCount () > 0 ? TRUE : FALSE);
	m_lbFunktionen.EnableWindow (m_lbFunktionen.GetCount () > 0 ? TRUE : FALSE);
	m_lbOperatoren.EnableWindow (m_lbOperatoren.GetCount () > 0 ? TRUE : FALSE);
	m_btFilterCheck.EnableWindow (m_edKlausel.LineLength () > 0 ? TRUE : FALSE);

	UpdateWindow ();
#endif	
	
	return CPropertyPage::OnSetActive();
}

BOOL CFilterPage::OnKillActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	GetUserEntries (TRUE);
	
	return CPropertyPage::OnKillActive();
}

#ifndef WIN32                
LONG CFilterPage :: OnSetFocusToControl (UINT, LONG)
{
	GotoDlgCtrl (&m_edKlausel);
	return TRUE;		
}            
#endif

                
                
