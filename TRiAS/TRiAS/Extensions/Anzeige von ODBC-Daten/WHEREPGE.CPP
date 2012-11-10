// WherePge.cpp : implementation file
//
#include "pheader.h"
#include "odbcext.hr"				// Resource-Konstanten

//	STL-Header
#include <ospace/com/iterenum.h>
#include <ospace/std/map>           // map
#include <ospace/std/set>
#include <ospace/std/algorithm>		// for_each

#include <hpp/columnst.hpp>				// CColumns
#include <hpp/helptext.hpp>				// CHelpText
#include <hpp/getodbci.hpp>				// COdbcInfos
#include <hpp/odbcerr.hpp>				// OdbcError
#include <hpp/fieldinf.hpp>             // CFieldInfo        
#include <hpp/TabDlgs.hpp>				// CTabbedDialogs
#include <hpp/FContDlg.h>				// CFieldContentsDlg
#include <hpp/tooltipb.h>				// CToolTipButton	
#include <hpp/propactb.hpp>			// Basisklasse

#include <xtsnguid.h>
#include <xtsnpropatl.h>			// CObjectProperties

#include "UserDlg.h"				// CUserDlg
#include "FileDlg.h"				// CFileDsnPage
#include "odbcguid.h"	

#include "odbcext.hpp"
#include "database.hpp"				// CDataBaseExt
#include "profile.hpp"     			// Profile
#include "whereprp.h"				// CLSID_WhereKlauselPropAct
#include "whereprp.hpp"				// CWhereKlauselPropAct
#include "RechStat.h"				// CRechStat
#include "WherePge.h"				// zugeh. Header

#include "myhelper.h"				// JG Project Enumeration

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

DefineSortingEnumerator(LONG);		// definiert SEnumLONG
DefineSmartEnumerator(LONG);		// definiert WEnumLONG (Wrapper für IEnum<LONG>)

DefineEnumInputIterator(LONG);		// definiert InEnumLONG
DefineEnumOutputIterator(LONG);		// definiert OutEnumLONG

//	Datentypen
typedef struct {
	CObjClassMap_t *pMap;
	IEnumObjectsByNumber *pStream;	
} SearchInfo;

// externe Funktionen
void CallMessageQueue (void);				

// von TRIAS gerufene Funktion
BOOL CALLBACK GetObjekt (long lONr, BOOL iNotLast, void *pData)
{
//	prüfe Objektnummer
	if ((lONr != 0) && (lONr != -1))
	{
	//	lese Objektklasse vom Objekt
		ULONG ulIdent = (ULONG) DEX_GetObjIdent (lONr);
		
	//	prüfe Ident in map
		ASSERT (NULL != pData);

	SearchInfo *pInfo = (SearchInfo *)pData;

		ASSERT (NULL != pInfo -> pMap);
		ASSERT (NULL != pInfo -> pStream);

	CObjClassMap_t_tit map_it = pInfo -> pMap -> find (ulIdent);

		if (map_it != pInfo -> pMap -> end())
			pInfo -> pStream -> AddItem (lONr);
		else {
			map_it = pInfo -> pMap -> find(0);		// Standard= gegeben ?
			if (map_it != pInfo -> pMap -> end ())
				pInfo -> pStream -> AddItem (lONr);
		}
	}
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CWherePage property page
// IMPLEMENT_DYNCREATE(CWherePage, CPropertyPage)

CWherePage::CWherePage(UINT uiResID) : CPropertyPage(uiResID), 
						   m_tbDsn (3),
						   m_btContents (IDS_SHOW_FIELD_CONTENTS)
{
	//{{AFX_DATA_INIT(CWherePage)
	//}}AFX_DATA_INIT
	m_tpDataSource = NoDataSource;
	m_pFunctionsArray = NULL;
	m_pOperatorsArray = NULL;
	m_pAction = NULL;
	m_pIEnumObjs = NULL;		// Eingabestrom
	m_bIsChecked = FALSE;

	m_pFunctionsArray = new UINT [MaxFunctions];
	memset (m_pFunctionsArray, 0, MaxFunctions);
	m_pOperatorsArray = new UINT [MaxOperators];
	memset (m_pOperatorsArray, 0, MaxOperators);
}

CWherePage::~CWherePage()
{
	DELETE_VEC (m_pFunctionsArray);
	DELETE_VEC (m_pOperatorsArray);
	if (m_pIEnumObjs)
	{
		m_pIEnumObjs -> Release ();
		m_pIEnumObjs = NULL;
	}
}

void CWherePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWherePage)
	DDX_Control(pDX, IDB_CONTENTS, m_btContents);
	DDX_Control(pDX, IDL_FILTER_TABLES, m_cbTables);
	DDX_Control(pDX, IDT_IMP_FILTER_DESCR, m_stDescription);
	DDX_Control(pDX, IDL_FILTER_OPERA, m_cbOperators);
	DDX_Control(pDX, IDL_FILTER_FUNKT, m_cbFunctions);
	DDX_Control(pDX, IDE_FILTER_KLAUSEL, m_edFilter);
	DDX_Control(pDX, IDL_FILTER_FELD, m_cbFields);
	DDX_Control(pDX, IDC_TAB_DSN, m_tbDsn);
	DDX_Control(pDX, IDB_FILTER_CHECK, m_btCheck);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWherePage, CPropertyPage)
	//{{AFX_MSG_MAP(CWherePage)
	ON_BN_CLICKED(IDB_FILTER_CHECK, OnFilterCheck)
	ON_EN_CHANGE(IDE_FILTER_KLAUSEL, OnChangeFilterKlausel)
	ON_CBN_SELCHANGE(IDL_FILTER_FELD, OnSelchangeFilterFeld)
	ON_CBN_SELCHANGE(IDL_FILTER_FUNKT, OnSelchangeFilterFunkt)
	ON_CBN_SELCHANGE(IDL_FILTER_OPERA, OnSelchangeFilterOpera)
	ON_CBN_SELCHANGE(IDL_FILTER_TABLES, OnSelchangeTables)
	ON_BN_CLICKED(IDB_CONTENTS, OnContents)
	ON_CBN_SETFOCUS(IDL_FILTER_FELD, OnSetfocusFilterFeld)
	ON_CBN_SETFOCUS(IDL_FILTER_FUNKT, OnSetfocusFilterFunkt)
	ON_CBN_SETFOCUS(IDL_FILTER_OPERA, OnSetfocusFilterOpera)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWherePage message handlers

BOOL CWherePage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	TRY
	{                   
	//	TODO: Add extra initialization here
	//  Font fnr Beschreibungsfeld einstellen
		m_stDescription.InitFont ();

	//	DataSource-Dialoge erzeugen
		CString strCaption;
		VERIFY (strCaption.LoadString (IDS_USER_DSN_CAPT));
		m_dlgUserDsn.m_tType = UserDataSource;
		VERIFY (0 == m_tbDsn.AddDialog (&m_dlgUserDsn, IDD_USER_DSN, strCaption));
		VERIFY (strCaption.LoadString (IDS_SYSTEM_DSN_CAPT));
		m_dlgSystemDsn.m_tType = SystemDataSource;
		VERIFY (1 == m_tbDsn.AddDialog (&m_dlgSystemDsn, IDD_USER_DSN, strCaption));
		VERIFY (strCaption.LoadString (IDS_FILE_DSN_CAPT));
		m_dlgFileDsn.m_tType = FileDataSource;
		VERIFY (2 == m_tbDsn.AddDialog (&m_dlgFileDsn, IDD_FILE_DSN, strCaption));

	//	Eingabelänge begrenzen
		m_edFilter.LimitText (KlauselSize);

		uint uActResID = IDS_AND_OP;
		CString strText;
		ASSERT (NULL != m_pOperatorsArray);
		for (short sIndex = 0; sIndex < MaxOperators; sIndex++, uActResID += 2)
		{   
		//	akt. String laden
			if (strText.LoadString (uActResID) &&			// String aus Resource laden
				(m_cbOperators.AddString (strText) >= 0))	// String in ListBox
				m_pOperatorsArray [sIndex] = uActResID + 1;	// ResID speichern							
			else
				AfxThrowUserException ();
		}     

	//	Filter ausgeben
		m_edFilter.SetWindowText (m_strFilter);			
		
	//	evtl. übergebenen DataSource einstellen
		if (ReadOdbcInfos (m_strDataSource, m_tpDataSource))
		{
			switch (m_tpDataSource)
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
					ASSERT (FALSE);
			}		
			
		//	wenn Tabelle übergeben, dann Feldnamen ausgeben
			if (!m_strTable.IsEmpty ())
			{
				int iIndex = m_cbTables.FindStringExact (-1, m_strTable);
				if (iIndex >= 0)
				{
					m_cbTables.SetCurSel (iIndex);
					m_OdbcInfos.OutputColumnNames (m_strTable, m_cbFields);					
				}
				else
					m_strTable.Empty ();
			}
		}
		else	//	übergebene Werte sind ungültig
		{
			m_tbDsn.SetActiveDialog (0);
			m_strDataSource.Empty ();
			m_tpDataSource = NoDataSource;
			m_strTable.Empty ();
		}

		VERIFY (m_btContents.Create ());

		VERIFY (S_OK == CoCreateInstance (CLSID_EnumObjectsByNumber, NULL, CLSCTX_INPROC_SERVER,
										  IID_IEnumObjectsByNumber, (LPVOID *)&m_pIEnumObjs));
	}
	CATCH (CMemoryException, me)
	{
		me -> ReportError ();
	}
	AND_CATCH (CUserException, me)
	{
		DEX_Error (RC_CCreateWhereKlDlg, EC_SYSERROR);		
	}
	END_CATCH   

	SetControlState ();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CWherePage::SetButtons (void /*BOOL bDisableNext*/)
{
	CPropertySheet *pSheet = GetPropertySheet();
	if (NULL == pSheet)
		return;

	DWORD dwBttns = 0;
	int iCnt = m_bIsChecked ? 1 : 0;

	if (!(m_dwFlags & ADDPAGES_FIRSTPAGE))
		dwBttns |= PSWIZB_BACK;

	if (0 < iCnt /*&& !bDisableNext*/) {
		if (m_dwFlags & ADDPAGES_LASTPAGE)
			dwBttns |= PSWIZB_FINISH;
		else
			dwBttns |= PSWIZB_NEXT;
	} else if (m_dwFlags & ADDPAGES_LASTPAGE)
		dwBttns |= PSWIZB_DISABLEDFINISH;

	pSheet -> SetWizardButtons (dwBttns);
}

void CWherePage:: SetControlState ()
{
	if (m_OdbcInfos.m_pDataBase && m_OdbcInfos.m_pDataBase -> IsOpen ())
	{
		m_cbTables.EnableWindow (m_cbTables.GetCount () > 0);		
		m_cbFields.EnableWindow (m_cbFields.GetCount () > 0);		
		m_cbOperators.EnableWindow (m_cbOperators.GetCount () > 0);		
		m_cbFunctions.EnableWindow (m_cbFunctions.GetCount () > 0);		
		m_edFilter.EnableWindow (TRUE);
		m_btCheck.EnableWindow ((m_edFilter.LineLength () > 0) && !m_strTable.IsEmpty ());
		m_btContents.EnableWindow (m_cbFields.GetCurSel () >= 0);
	}
	else
	{
		m_cbTables.EnableWindow (FALSE);		
		m_cbFields.EnableWindow (FALSE);		
		m_cbOperators.EnableWindow (FALSE);		
		m_cbFunctions.EnableWindow (FALSE);		
		m_edFilter.EnableWindow (FALSE);
		m_btCheck.EnableWindow (FALSE);
		m_btContents.EnableWindow (FALSE);
	}
}

//	DataSource hat sich geändert
BOOL CWherePage::ReadOdbcInfos (const char *pDataSource, DataSourceType tType)
{
	BOOL bOk = FALSE;

	TRY	{
	//	zuerst alle Infos rücksetzen
	CWaitCursor wc;

		m_stDescription.SetWindowText ("");
		m_cbTables.ResetContent ();
		m_cbFunctions.ResetContent ();
		m_cbFields.ResetContent ();
		EnableWindow (FALSE);
		
	//	jetzt Parameter prüfen
		if (!pDataSource || !*pDataSource || 
			((tType != UserDataSource) && (tType != SystemDataSource) && (tType != FileDataSource)))
			AfxThrowUserException ();

	//	Datasource erzeugen
		if (!m_OdbcInfos.CreateDataBase (pDataSource, tType))
			AfxThrowUserException ();

	//	Kommentar zum DSN ausgeben		
		VERIFY (m_OdbcInfos.OutputDataBaseInfo (m_stDescription));

	//	Tabellen ausgeben: Feldnamen erst nach Tabellen-Auswahl ausgeben
		VERIFY (m_OdbcInfos.OutputTableNames (&m_cbTables));	

	//	Funktionen ausgeben
		VERIFY (m_OdbcInfos.OutputFunctions (&m_cbFunctions, m_pFunctionsArray, MaxFunctions));

	//	Operationflag setzen
		bOk = TRUE;
	}
	CATCH (CMemoryException, me)
	{
		me -> ReportError ();
	}
	AND_CATCH (CUserException, me)
	{
		bOk = FALSE;		//	nur auffangen
	}
	AND_CATCH (CDBException, db)
	{
		db -> ReportError ();
	}
	END_CATCH   

//	alle Controls aktualisieren
	SetControlState ();
	EnableWindow (TRUE);

	return bOk;
}

BOOL CWherePage::OnCommand(WPARAM wParam, LPARAM lParam) 
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
	
	BOOL bOk = ReadOdbcInfos (pInfo -> pName, pInfo -> tType);
	
		m_strDataSource = bOk ? pInfo -> pName : "";
		m_tpDataSource = bOk ? pInfo -> tType : NoDataSource;
		m_strTable.Empty ();
		m_bIsChecked = FALSE;		
		SetButtons ();
		return TRUE;
	}
	else
		return CDialog::OnCommand(wParam, lParam);
}

void CWherePage::OnFilterCheck() 
{
//	prüfe Parameter
	ASSERT (!m_strDataSource.IsEmpty ());
	ASSERT (!m_strTable.IsEmpty ());
	ASSERT ((UserDataSource == m_tpDataSource) || (SystemDataSource == m_tpDataSource) ||
			(FileDataSource == m_tpDataSource));
	ASSERT (NULL != m_OdbcInfos.m_pDataBase && m_OdbcInfos.m_pDataBase -> IsOpen ());

	CWaitCursor wc;			

list<HPROJECT> ProjectList;

	EnumAllProjects(ProjectList);
	m_bIsChecked = FALSE;	// wird nur geändert, falls sich irgendwo Erfolg einstellt

	for(list<HPROJECT>::iterator i =  ProjectList.begin(); i != ProjectList.end(); ++i)
	{
		TRY	{
//			CWaitCursor wc;			
			EnableWindow (FALSE);
			
		//	lese zu DataSource/Tabelle den Aliasnamen
		Profile ProFile((*i));
		
			m_strAlias = ProFile.GetAliasName (m_strDataSource, m_tpDataSource, m_strTable);
			if (m_strAlias.IsEmpty ())
				AfxThrowUserException ();

		//	lese Tabellenkoppelfeld
			m_strKoppelFeld = ProFile.GetKoppelFeld (m_strAlias);
			if (m_strKoppelFeld.IsEmpty ())
				AfxThrowUserException ();

		//	Recordset aufbauen und String parsen
			// CRecordset rs (m_OdbcInfos.m_pDataBase);
			TRY	{
			CString strSelect;
			
				m_edFilter.GetWindowText (m_strFilter);
				strSelect.Format (IDS_SELECT_PARSE_FORMAT, m_strKoppelFeld, m_strTable, m_strFilter);
				//if (rs.Open (CRecordset::forwardOnly, strSelect, CRecordset::readOnly))
				m_OdbcInfos.m_pDataBase -> ExecuteSQL (strSelect);
/*				VERIFY (strSelect.LoadString (IDS_OK_KRIT));
				m_stDescription.SetWindowText (strSelect);*/
				m_bIsChecked = TRUE;
			}
			CATCH (CDBException, db)
			{
//				m_bIsChecked = FALSE;
				:: MessageBeep (MB_ICONHAND);
				CString strErr (db -> m_strError);
				int iPos = strErr.GetLength () - 1;
				if (strErr.Find ('\n') == iPos)
					strErr = strErr.Left (--iPos);
				m_stDescription.SetWindowText (strErr);
			}	
			END_CATCH
			//rs.Close ();
		}
		CATCH (CMemoryException, me)
		{
			me -> ReportError ();
		}
		AND_CATCH (CUserException, me)
		{
//			m_bIsChecked = FALSE;
/*			CString strError;
			VERIFY (strError.LoadString (IDS_NO_ODBC_CONNECTIONS));
			MessageBox (strError, AfxGetAppName (), MB_OK | MB_ICONINFORMATION);*/
		}
		END_CATCH   
	}
	if (!m_bIsChecked)
	{
		CString strError;
		VERIFY (strError.LoadString (IDS_NO_ODBC_CONNECTIONS));
		MessageBox (strError, AfxGetAppName (), MB_OK | MB_ICONINFORMATION);
	}
	else
	{
		CString strSelect;
		VERIFY (strSelect.LoadString (IDS_OK_KRIT));
		m_stDescription.SetWindowText (strSelect);
	}

	SetButtons ();
	EnableWindow (TRUE);
}

void CWherePage::OnChangeFilterKlausel() 
{
	// TODO: Add your control notification handler code here
	m_bIsChecked = FALSE;
	m_btCheck.EnableWindow ((m_edFilter.LineLength () > 0) && !m_strTable.IsEmpty ());	
	ASSERT (NULL != m_pAction);
	m_pAction -> SetDirty (TRUE);
	SetButtons ();
}

void CWherePage::OnSelchangeFilterFeld() 
{
	// TODO: Add your control notification handler code here
	int iActSel = m_cbFields.GetCurSel ();		
	if (iActSel >= 0)		// wenn Index gültig
	{                          
		CString strSel;
		m_cbFields.GetLBText (iActSel, strSel);		
		m_OdbcInfos.OutputColumnInfo (strSel, m_stDescription);
		CopyField ();
		m_edFilter.SetFocus ();
	}

	SetControlState ();
}

void CWherePage::OnSelchangeFilterFunkt() 
{
	ASSERT (NULL != m_pFunctionsArray);

	// TODO: Add your control notification handler code here
	int iActSel = m_cbFunctions.GetCurSel ();		
	if ((iActSel >= 0) && (iActSel < MaxFunctions))		// wenn Index gültig
	{                          
		uint uResID = m_pFunctionsArray [iActSel];
		if (uResID)
			m_stDescription.Output (uResID);			// Beschreibung ausgeben
		CopyFunction ();
		m_edFilter.SetFocus ();
	}	

	SetControlState ();
}

void CWherePage::OnSelchangeFilterOpera() 
{
	// TODO: Add your control notification handler code here
	ASSERT (NULL != m_pOperatorsArray);

	int iActSel = m_cbOperators.GetCurSel ();		
	if ((iActSel >= 0) && (iActSel < MaxOperators))		// wenn Index gültig
	{                          
		uint uResID = m_pOperatorsArray [iActSel];
		if (uResID)
			m_stDescription.Output (uResID);			// Beschreibung ausgeben
		CopyOperator ();
		m_edFilter.SetFocus ();
	}

	SetControlState ();
}

void CWherePage::OnSelchangeTables() 
{
	// TODO: Add your control notification handler code here
	int iSel = m_cbTables.GetCurSel ();
	if (iSel >= 0)
	{		
		CWaitCursor wc;
		m_cbTables.EnableWindow (FALSE);
		m_cbTables.GetLBText (iSel, m_strTable);
		VERIFY (m_OdbcInfos.OutputColumnNames (m_strTable, m_cbFields));
		m_cbTables.EnableWindow (TRUE);
		// CopyTable ();
	}

	SetControlState ();
}

void CWherePage::CopyField ()
{
	// TODO: Add your control notification handler code here
	TRY
	{   
		int iIndex = m_cbFields.GetCurSel ();
		if (iIndex >= 0)			// gültiger Index
		{
			CString strFeldName, strSel, strTableName;
			m_cbTables.GetLBText (m_cbTables.GetCurSel (), strSel);
			ASSERT (!strSel.IsEmpty ());
			AfxFormatString1 (strTableName, IDS_FIELDNAME_FORMAT, strSel);
			m_cbFields.GetLBText (iIndex, strSel);		// Feldnamen lesen
			AfxFormatString1 (strFeldName, IDS_FIELDNAME_FORMAT, strSel);
			strSel = strTableName + TableSQLSepStr + strFeldName;
			m_edFilter.ReplaceSel (strSel);		
			// m_bIsChecked = FALSE;		
		}
	}
	CATCH (CMemoryException, me)
	{   
		DEX_Error (RC_CCreateWhereKlDlg, EC_NOMEMORY);
	}	
	END_CATCH
}

void CWherePage::CopyFunction ()
{
	// TODO: Add your control notification handler code here
	int iCurSel = m_cbFunctions.GetCurSel ();
	if (iCurSel < 0)
		return;

// 	TODO: Add your control notification handler code here
	TRY
	{   
		CString strFunction, strValue;		
		m_cbFunctions.GetLBText (iCurSel, strFunction);
		strValue.Format (IDS_SCALE_FCN_FORMAT, strFunction);
		
	//	akt. Position merken
		int iStart, iPos;
		m_edFilter.GetSel (iStart, iPos);
		iPos = strValue.Find ('(') + 1;
		m_edFilter.ReplaceSel (strValue);	
		iStart += iPos;
		m_edFilter.SetSel (iStart, iStart);
		// m_bIsChecked = FALSE;		
	}
	CATCH (CMemoryException, me)
	{   
		DEX_Error (RC_CCreateWhereKlDlg, EC_NOMEMORY);
	}	
	END_CATCH		
}

void CWherePage::CopyOperator ()
{
	// TODO: Add your control notification handler code here
	int iCurSel = m_cbOperators.GetCurSel ();
	if (iCurSel < 0)
		return;

	TRY
	{
		CString strSel;
		
	//	Operator lesen
		CString strOperator;
		m_cbOperators.GetLBText (iCurSel, strOperator);
		                                           
		strSel = " ";
		strSel += strOperator;
		strSel += " ";

		m_edFilter.ReplaceSel (strSel);    // Wert im Editfeld einfügen
		// m_bIsChecked = FALSE;		
	}
	CATCH (CMemoryException, me)
	{
		DEX_Error (RC_CCreateWhereKlDlg, EC_NOMEMORY);
	}		
	END_CATCH
}

/*
void CWherePage::CopyTable ()
{
	// TODO: Add your control notification handler code here
	int iCurSel = m_cbTables.GetCurSel ();
	if (iCurSel < 0)
		return;

	TRY
	{
		CString strSel;
		
	//	Tabelle lesen
		CString strTable, strInfo;
		m_cbTables.GetLBText (iCurSel, strTable);
		AfxFormatString1 (strInfo, IDS_FIELDNAME_FORMAT,strTable);
		strInfo += TableSQLSepStr;
		m_edFilter.ReplaceSel (strInfo);    // Wert im Editfeld einfügen
	}
	CATCH (CMemoryException, me)
	{
		DEX_Error (RC_CCreateWhereKlDlg, EC_NOMEMORY);
	}		
	END_CATCH
}
*/

void CWherePage::OnContents() 
{
	// TODO: Add your control notification handler code here
	TRY
	{
	//	prüfe Parameter
		ASSERT (NULL != m_OdbcInfos.m_pDataBase && m_OdbcInfos.m_pDataBase -> IsOpen ());
		ASSERT (!m_strTable.IsEmpty ());

	//	Anfrage an Nutzer
		CString strInfo;
		VERIFY (strInfo.LoadString (IDS_OUTPUT_FELD_CONTENTS));
		if (IDYES != MessageBox (strInfo, AfxGetAppName (), MB_YESNO | MB_ICONQUESTION))
			AfxThrowUserException ();
		
	//	lese Tabelle/Feld
		EnableWindow (FALSE);
		CString strField, strSelect;
		m_cbFields.GetLBText (m_cbFields.GetCurSel (), strField);
		ASSERT (!strField.IsEmpty ());

	//	SpaltenInfo anzeigen
		CFieldContentsDlg Dlg (this, m_OdbcInfos.m_pDataBase, m_strTable, strField);
		if (IDOK == Dlg.DoModal () && !Dlg.m_strSelection.IsEmpty ())
		{
			m_edFilter.ReplaceSel (Dlg.m_strSelection);		
			// m_bIsChecked = FALSE;		
		}
	}
	CATCH (CMemoryException, me)
	{
		DEX_Error (RC_CCreateWhereKlDlg, EC_NOMEMORY);
	}
	AND_CATCH (CUserException, ue)
	{
		//	nur auffangen
	}
	END_CATCH   	

	SetControlState ();
	EnableWindow (TRUE);
}

void CWherePage::OnSetfocusFilterFeld() 
{
	// TODO: Add your control notification handler code here
	int iFSel = m_cbFields.GetCurSel ();		
	int iTSel = m_cbTables.GetCurSel ();

	if (iFSel < 0 || iTSel < 0)
		return;

//	Beschreibung ausgeben
	CString strSel;
	m_cbFields.GetLBText (iFSel, strSel);
	m_OdbcInfos.OutputColumnInfo (strSel, m_stDescription);
}


void CWherePage::OnSetfocusFilterFunkt() 
{
	// TODO: Add your control notification handler code here
	int iSel = m_cbFunctions.GetCurSel ();
	if ((iSel >= 0) && (iSel < MaxFunctions))		// wenn Index gültig
	{                          
		uint uResID = m_pFunctionsArray [iSel];
		if (uResID)
			m_stDescription.Output (uResID);			// Beschreibung ausgeben
	}
}

void CWherePage::OnSetfocusFilterOpera() 
{
	// TODO: Add your control notification handler code here
	int iSel = m_cbOperators.GetCurSel ();
	if ((iSel >= 0) && (iSel < MaxOperators))		// wenn Index gültig
	{                          
		uint uResID = m_pOperatorsArray [iSel];
		if (uResID)
			m_stDescription.Output (uResID);			// Beschreibung ausgeben
	}
}

BOOL CWherePage::OnSetActive() 
{
//	ggf. Eintrag prüfen
	if (!m_bIsChecked && m_btCheck.IsWindowEnabled())
		OnFilterCheck();
	else
		SetButtons ();
	
	return CPropertyPage::OnSetActive();
}

// liest Objektmenge
HRESULT CWherePage::GetEnumLONG (IEnumObjectsByNumber **ppIEnum)
{
	if (NULL == ppIEnum) 
		return E_POINTER;
	if (NULL == m_pIEnumObjs) 
		return E_OUTOFMEMORY;

//	IEnumObjectsByNumber abfragen
	return m_pIEnumObjs -> QueryInterface (IID_IEnumObjectsByNumber, (LPVOID *)ppIEnum);
}

// Page erzeugen
CWherePage *CWherePage::CreateInstance (UINT uiResID, CWhereKlauselPropAct *pAction)		
{
	ASSERT (NULL != pAction);
	ASSERT (uiResID > 0);

	CWherePage *pDlg = NULL;

	try
	{
		pDlg = new CWherePage (uiResID);
	}
	catch (CMemoryException *e)
	{
		e -> ReportError ();
		e -> Delete ();
		return NULL;
	}
	pDlg -> m_pAction = pAction;

	return pDlg;
}

BOOL CWherePage::ReadParams (CRecordset &RecSet, ULONG &ulMerkmalsKode, CString &strClasses, HPROJECT hPr)
{
//	prüfe Parameter
	if (m_strDataSource.IsEmpty () || m_strFilter.IsEmpty () || m_strTable.IsEmpty () ||
	   ((m_tpDataSource != UserDataSource) && (m_tpDataSource != FileDataSource) &&
	    (m_tpDataSource != SystemDataSource)))
	{
		return FALSE;
	}

	ASSERT(!RecSet.IsOpen());

//	Database erzeugen
	if (!m_OdbcInfos.m_pDataBase || !m_OdbcInfos.m_pDataBase -> IsOpen())
	{
		if (!m_OdbcInfos.CreateDataBase (m_strDataSource, m_tpDataSource))
			return FALSE;
	}		

//	weitere Parameter lesen
Profile ProFile(hPr);

	m_strAlias = ProFile.GetAliasName (m_strDataSource, m_tpDataSource, m_strTable);
	if (m_strAlias.IsEmpty ())
		return FALSE;

//	lese Koppelfeld
	m_strKoppelFeld = ProFile.GetKoppelFeld (m_strAlias);
	if (m_strKoppelFeld.IsEmpty ())
		return FALSE;

//	lese Merkmalskode
	ulMerkmalsKode = ProFile.GetMerkmalsKode (m_strAlias);
	if (ulMerkmalsKode <= 0)
		return FALSE;

//	lese alle Objektklassen, die diese Anbindung haben
	strClasses = ProFile.GetObjClasses (m_strAlias, m_strKoppelFeld, ulMerkmalsKode);
	if (strClasses.IsEmpty ())
		return FALSE;
	
	RecSet.m_pDatabase = m_OdbcInfos.m_pDataBase;

CString strSelect;

	strSelect.Format (IDS_SELECT_PARSE_FORMAT, m_strKoppelFeld, m_strTable, m_strFilter);
	if (!RecSet.Open (CRecordset::forwardOnly, strSelect, CRecordset::readOnly))
		return FALSE;
	
	return TRUE;
}

// übergibt Objektmenge
HRESULT CWherePage::SetEnumLONG (IEnumObjectsByNumber *pIEnum)
{
CRechStat *pStat = NULL;
HRESULT hRet = NULL;

	try	{
	//	Eingabeset übergeben
		if (pIEnum)	{
		ULONG ulCnt = 0;
		HRESULT hr = pIEnum -> GetCount (&ulCnt);
		
			if (FAILED (hr))
				return hr;

		//	wenn keine Objekte in der Eingabemenge
			if (ulCnt <= 0)
				return S_OK;	//	dann zurück
		}

	// alle Projekte durchgehen
	list<HPROJECT> ProjectList;

		EnumAllProjects(ProjectList);
		for (list<HPROJECT>::iterator it = ProjectList.begin(); it != ProjectList.end(); ++it) {
			try {	// Exceptions für dieses Project auffangen 	
			//	lese alle Parameter, die für die Anbindung notwendig sind
			ULONG ulMerkmalsKode = 0;
			CRecordset RecSet;
			CString strClasses;

				if (!ReadParams (RecSet, ulMerkmalsKode, strClasses, (*it)))
					AfxThrowNotSupportedException ();

			//	prüfe Parameter
				ASSERT (RecSet.IsOpen());
				ASSERT (!m_strKoppelFeld.IsEmpty());
				ASSERT (0 != ulMerkmalsKode);
				if (RecSet.IsEOF() || strClasses.IsEmpty())
					AfxThrowNotSupportedException ();

			//	Objklassen map füllen
			CObjClassMap_t map;

				if (!FillMapWithClasses (*it, map, strClasses))
					continue;

			//	Var. init
			CWaitCursor wc;
			SearchInfo Info;		

				Info.pMap = &map;
				Info.pStream = m_pIEnumObjs;

			ENUMRECHTEXTMERKMAL tm;

				INITSTRUCT(tm, ENUMRECHTEXTMERKMAL);
				tm.pView = NULL;
				tm.lMCode = (long) ulMerkmalsKode;
				tm.pMWert = NULL;		// aktueller Wert
				tm.iMode = SMExactMatch | SMActViewOnly;
				tm.pData = (void *) &Info;
				tm.eFcn = GetObjekt;

			CString strSetVal;

			//	alle Sätze im Set durchsuchen
				if (NULL == pStat) {
					pStat = new CRechStat; 
					VERIFY (pStat -> Create (IDD_RECH_STATUS, this));
				}
				for (int iCnt = 1; !RecSet.IsEOF (); RecSet.MoveNext (), ++iCnt) {
				//	Werte akt.
					if (0 == iCnt % 100) {
						if (!pStat -> IsWindowVisible())
							pStat -> ShowWindow (SW_SHOW);

					char Buffer10 [10] = "";

						pStat -> m_strNumber = itoa (iCnt, Buffer10, 10);
						pStat -> UpdateData (FALSE);
					}
					CallMessageQueue ();

				//	lese akt. Feldinhalt
					RecSet.GetFieldValue (m_strKoppelFeld, strSetVal);
					if (strSetVal.IsEmpty ())
						continue;

				//	lese TRIAS-Objekt mit zugehörigen Feldinhalt
					tm.pMWert = (char *)(const char *)strSetVal;

					DEX_EnumRechTextMerkmal (tm);
				}

			//	Set schließen
				RecSet.Close ();
			}	// end of try
			catch (CNotSupportedException *se)		//	keine Anbidung vorhanden
			{
				se -> Delete ();					//	keine Sätze gefunden, JG990313 können wir aber übergehen wird später ja nochmal geprüft
			}
		}	// end of iteration

	//	jetzt ggf. Verschnitt mit Eingabeobjektmenge durchführen
		if (NULL != pIEnum)	{
		WEnumLONG EnumOut (CLSID_EnumObjectsByNumber);
		OutEnumLONG iter_out ((IEnum<LONG> *)EnumOut);		// throws hr

		//	Schnittmenge zwischen Eingabemenge und Recherchergebnis bilden
			set_intersection(InEnumLONG(pIEnum), InEnumLONG(),
						     InEnumLONG(m_pIEnumObjs), InEnumLONG(), 
						     iter_out);						// throws bad_...

			m_pIEnumObjs -> Release();
			THROW_FAILED_HRESULT(EnumOut -> QueryInterface (IID_IEnumObjectsByNumber, (LPVOID *)&m_pIEnumObjs));
		}			
		hRet = S_OK;
	}
	catch (HRESULT hr)
	{
		DEX_Error (RC_CCreateWhereKlDlg, EC_SYSERROR);
		hRet = hr;
	}
	catch (CMemoryException *me)
	{
		DEX_Error (RC_CCreateWhereKlDlg, EC_NOMEMORY);		
		me -> Delete ();
		hRet =  E_OUTOFMEMORY; 	
	}
	catch (CUserException *ue)
	{
		ue -> Delete ();					//	Abbruch
		hRet =  E_ABORT;
	}
	catch (CDBException *db)
	{
		db -> ReportError ();
		db -> Delete ();
		hRet =  E_ABORT;
	}
	catch (CNotSupportedException *se)		//	keine Anbidung vorhanden
	{
		se -> Delete ();					//	keine Sätze gefunden
		hRet = NO_ERROR;
	}
	catch (...) 
	{
		hRet =  E_OUTOFMEMORY;
	}
	if (pStat)
		pStat -> DestroyWindow ();

	return hRet;
}

