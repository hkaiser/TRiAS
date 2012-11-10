// QueryRes.cpp : implementation file
//

#include "stdafx.h"		// prec. Header
#include "gak.h"		// CGakApp
#include "TablNDlg.h"	// CTableNameDlg
#include "QueryRes.h"	// zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const int CopyBufferSize = 512 * 1024;	// max. 512 KB-Puffer für Copy ins Clipboard
const short MaxFeldLen = 128;			// max. 128 Zeichen für Feld ausgeben
const char Tab [] = "\t";
const char NL [] = "\n";

/////////////////////////////////////////////////////////////////////////////
// CQueryResult dialog


CQueryResult :: CQueryResult(CWnd* pParent, CDaoRecordset *pSet,
							 const CString& strQueryName)
			  : CDialog(CQueryResult::IDD, pParent)
{
	//{{AFX_DATA_INIT(CQueryResult)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pSet = NULL;

	ASSERT (NULL != pSet);
	ASSERT_VALID (pSet);
	ASSERT (pSet -> IsOpen ());
	m_pSet = pSet;

	m_strQueryName = strQueryName;
}

void CQueryResult::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CQueryResult)
	DDX_Control(pDX, IDS_FOUND, m_stInfo);
	DDX_Control(pDX, IDC_QUERY_LIST, m_lcListe);
	DDX_Control(pDX, IDB_FELDNAMEN, m_btFeldNamen);
	DDX_Control(pDX, IDB_COPY, m_btCopy);
	DDX_Control(pDX, IDB_ALLE, m_btAlle);
	DDX_Control(pDX, IDB_TABLE, m_btTable);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CQueryResult, CDialog)
	//{{AFX_MSG_MAP(CQueryResult)
	ON_BN_CLICKED(IDB_COPY, OnCopy)
	ON_NOTIFY(NM_CLICK, IDC_QUERY_LIST, OnClickQueryList)
	ON_BN_CLICKED(IDB_ONLY_SELECTED, OnOnlySelected)
	ON_BN_CLICKED(IDB_ALLE, OnAlle)
	ON_BN_CLICKED(IDB_TABLE, OnTable)
	ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQueryResult message handlers

BOOL CQueryResult::OnInitDialog() // kein try/catch
{
	CDialog::OnInitDialog();

	ASSERT (NULL != m_pSet);
	ASSERT_VALID (m_pSet);
	ASSERT (m_pSet -> IsOpen ());

	CWaitCursorExt wc (IDS_INIT_QUERY_RESULT, IDS_BEREIT);

//	Button setzen
	m_btFeldNamen.SetCheck (1);		
	m_btAlle.SetCheck (1);

//	Caption setzen
	CString strCaption;
	if (m_strQueryName.IsEmpty ())
		VERIFY (strCaption.LoadString (IDS_QUERY_TEMP));
	else
		AfxFormatString1 (strCaption, IDS_QUERY_RES_CAPTION, m_strQueryName);
	SetWindowText (strCaption);

//	Selektion "beibehalten" setzen
	long lAttr = :: GetWindowLong (m_lcListe.m_hWnd, GWL_STYLE);
	:: SetWindowLong (m_lcListe.m_hWnd, GWL_STYLE, lAttr | LVS_SHOWSELALWAYS);

//	ListBox füllen: zuerst FeldNamen
	int iItem = 0;			// akt. Item
	CString strFeldName;
	VERIFY (strFeldName.LoadString (IDS_SATZ));
	if (m_lcListe.InsertColumn (iItem, strFeldName) != iItem)
		AfxThrowResourceException ();

//	restlichen Feldinformationen lesen
	short sFieldCnt = m_pSet -> GetFieldCount () + 1;			// Anzahl Felder	
	CDaoFieldInfo FieldInfo;
	for (iItem++; iItem < sFieldCnt; iItem++)
	{
		m_pSet -> GetFieldInfo (iItem - 1, FieldInfo);
		if (m_lcListe.InsertColumn (iItem, FieldInfo.m_strName) != iItem)
			AfxThrowResourceException ();
	}

//	Größe aller Felder setzen
	for (iItem = 0; iItem < sFieldCnt; iItem++)
		m_lcListe.SetColumnWidth (iItem, LVSCW_AUTOSIZE_USEHEADER);

//	Feldinhalte ausgeben
	char Empty [] = "";				// leere ZK
	iItem = 0;						// akt. Satz ist der erste
	char Buffer10 [10];				// Zahlenpuffer
	COleVariant vars, vard;			// Feldwert
	const char *pVal = NULL;		// Zeiger auf Feldwert
	CString strJa, strNein, strVal;
	VERIFY (strJa.LoadString (IDS_JA));
	VERIFY (strNein.LoadString (IDS_NEIN));
	m_pSet -> MoveFirst ();
	while (! m_pSet -> IsEOF ())
	{
	//	zuerst SatzNummer ausgeben
		itoa (iItem + 1, Buffer10, 10);
		if (m_lcListe.InsertItem (iItem, Buffer10) != iItem)
			AfxThrowResourceException ();

	//	restlichen Feldwerte		
		for (int iIndex = 1; iIndex < sFieldCnt; iIndex++)
		{
			vars.Clear ();
			vard.Clear ();

		//	Feldinformation lesen
			vars = m_pSet -> GetFieldValue (iIndex - 1);
			if ((VT_EMPTY == vars.vt) || (VT_NULL == vars.vt) || (VT_UNKNOWN == vars.vt))
				pVal = Empty;
			else
			{
				if (VT_BSTR == vars.vt)
					pVal = (char *) vars.pbVal;
				else
				{
					if (VT_BOOL == vars.vt)
						pVal = 0 == vars.pbVal ? strNein : strJa;
					else
					{
						vard.ChangeType (VT_BSTR, vars);		// in Zeichenkette umwandeln
						pVal = AnsiStringNew ((LPCWSTR) vard.pbVal);
					}
				}
			}

		//	Feldlänge begrenzen
			if (strlen (pVal) > MaxFeldLen)
			{
				CString strTemp (pVal);
				strVal = strTemp.Left (MaxFeldLen);
				pVal = strVal;
			}

		//	Info in ListBox ausgeben
			if (!m_lcListe.SetItemText (iItem, iIndex, pVal))
				AfxThrowMemoryException ();
		}

		iItem++;
		m_pSet -> MoveNext ();		// zum nächsten Satz
	}

//	Anzahl gefundener Datensätze ausgeben
	CString strInfo;
	char Buffer [30] = "";
	itoa (m_lcListe.GetItemCount (), Buffer, 10);
	AfxFormatString1 (strInfo, IDS_QUERY_RESULT_FOUND, Buffer);
	m_stInfo.SetWindowText (strInfo);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CQueryResult::OnClickQueryList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	if ((m_btAlle.GetCheck () == 0)	&& 
		(m_lcListe.GetSelectedCount () == 0))
		m_btCopy.EnableWindow (FALSE);
	else
		m_btCopy.EnableWindow (TRUE);

	*pResult = 0;
}

void CQueryResult::OnCopy() 
{
	if (m_btTable.GetCheck () == 1)
		CopyToTable ();
	else
	{
		CopyToClipboard ();
	}
}

void CQueryResult::CopyToClipboard (void)
{
	// TODO: Add your control notification handler code here
	try
	{	
		CMutex mt;
		CWaitCursorExt wc (IDS_COPY_TOCL, IDS_BEREIT);
		ASSERT (NULL != m_pSet);
		ASSERT (m_pSet -> IsOpen ());

		if (!OpenClipboard () || !EmptyClipboard ())
			AfxThrowUserException ();

		int iItem= 0;							// akt. Item

	//	max. Zeilenzahl
		int iItemCnt = 0;
		BOOL bOnlySel = FALSE;
		if (m_btAlle.GetCheck () == 1) 
		{
			bOnlySel = FALSE;
			iItemCnt = m_lcListe.GetItemCount ();
		}
		else
		{
			bOnlySel = TRUE;
			iItemCnt = m_lcListe.GetSelectedCount ();
		}

		CString strRes (' ', __min(iItemCnt * 1024, CopyBufferSize));	// ErgebnisText;

	//	Anzahl Felder		
		int iFieldCnt = m_pSet -> GetFieldCount () + 1;	// plus Standardfeld

	//	lese ggf. Feldnamen
		if (m_btFeldNamen.GetCheck () == 1)
		{
		//	Standard-Spalten-Namen
			VERIFY (strRes.LoadString (IDS_SATZ));

		//	restlichen Feldinformationen lesen
			CDaoFieldInfo FieldInfo;
			for (iItem = 0; iItem < iFieldCnt - 1; iItem++)
			{
				strRes += Tab;
				m_pSet -> GetFieldInfo (iItem, FieldInfo);
				strRes += FieldInfo.m_strName;
			}
			strRes += NL;		// neue Zeile
		}

	//	für alle Items
		int iActItem = -1;
		for (iItem = 0; iItem < iItemCnt; iItem++)
		{
			if (bOnlySel)
				iActItem = m_lcListe.GetNextItem (iActItem, LVNI_SELECTED);
			else
				iActItem = iItem;

			ASSERT (iActItem >= 0);

		//	für alle Spalten
			for (int iCol = 0; iCol < iFieldCnt; iCol++)
			{
				if (iCol)
					strRes += Tab;								
				strRes += m_lcListe.GetItemText (iActItem, iCol);
			}

			strRes += NL;			
		}
	
	//	String ins Clipboard ausgeben
		HGLOBAL hText = :: GlobalAlloc (GMEM_MOVEABLE | GMEM_DDESHARE,
										strRes.GetLength () + 1);
		if (!hText)
			AfxThrowMemoryException ();
		char *pText = (char *) :: GlobalLock (hText);
		if (!pText)
			AfxThrowMemoryException ();
		strcpy (pText, strRes);	
		if (GlobalUnlock (hText) == TRUE)
			AfxThrowMemoryException ();
		if (!SetClipboardData (CF_TEXT, hText))
			AfxThrowUserException ();
	}
	catch (CUserException *e)	// Clipboard-Fehler
	{
		CString strError;
		VERIFY (strError.LoadString (IDS_CLIPB_ERROR));
		MessageBox (strError, AfxGetAppName (), MB_OK | MB_ICONSTOP);		
		e -> Delete ();
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

	 CloseClipboard ();	// auf jeden Fall schließen
}


void CQueryResult::OnOnlySelected() 
{
	// TODO: Add your control notification handler code here
	if (m_lcListe.GetSelectedCount () == 0)
		m_btCopy.EnableWindow (FALSE);
	else
		m_btCopy.EnableWindow (TRUE);	
}

void CQueryResult::OnAlle() 
{
	// TODO: Add your control notification handler code here
	m_btCopy.EnableWindow (TRUE);	
}

void CQueryResult::OnTable() 
{
	// TODO: Add your control notification handler code here
	m_btFeldNamen.SetCheck (1);
}

void CQueryResult::CopyToTable (void)
{
	ASSERT (NULL != m_pSet);
	ASSERT (m_pSet -> IsOpen ());
	ASSERT (NULL != m_pSet -> m_pDatabase);
	ASSERT (m_pSet -> m_pDatabase -> IsOpen ());
	CDaoWorkspace *pWSpace = m_pSet -> m_pDatabase -> m_pWorkspace;
	ASSERT (NULL != pWSpace);
	ASSERT (pWSpace -> IsOpen ());
	try
	{	
		CMutex mt;

		CTableNameDlg Dlg (this, ((CGakApp *)(AfxGetApp ())) -> DatabaseName ());
		if (IDOK != Dlg.DoModal () || Dlg.m_strTableName.IsEmpty () ||
			Dlg.m_strDatabase.IsEmpty ())
			AfxThrowUserException ();

	//	Info an Nutzer ausgeben
		CString strInfo;
		AfxFormatString1 (strInfo, IDS_COPY_IN_TABLE, Dlg.m_strTableName);
		CWaitCursorExt wc (strInfo, IDS_BEREIT);
		pWSpace -> BeginTrans ();		// Beginn der Transaktion

		CDaoDatabase dbOut;
		dbOut.Open (Dlg.m_strDatabase);

	//	neue Tabelle erzeugen
		CDaoTableDef NewTable (&dbOut);
		NewTable.Create (Dlg.m_strTableName);

	//	FeldInfos erzeugen
		int iFieldCnt = m_pSet -> GetFieldCount ();			// Anzahl Felder	
		CDaoFieldInfo FieldInfo;
		for (int iItem = 0; iItem < iFieldCnt; iItem++)
		{
			m_pSet -> GetFieldInfo (iItem, FieldInfo, AFX_DAO_ALL_INFO);
			NewTable.CreateField (FieldInfo);
		}
		NewTable.Append ();

	//	Feldwerte umkopieren: zuerst RecordSet erstellen
		CDaoRecordset DestSet (&dbOut);
		DestSet.Open (&NewTable);	// mit neuen Tabelle öffnen	
		m_pSet -> MoveFirst ();		// wieder auf 1. Satz
		COleVariant var;
		while (! m_pSet -> IsEOF ())
		{
			DestSet.AddNew ();

		//	alle Feldinformation lesen und ausgeben
			for (int iIndex = 0; iIndex < iFieldCnt; iIndex++)
			{
				var.Clear ();											// Puffer löschen
				m_pSet -> GetFieldInfo (iIndex, FieldInfo);				// lese Namen
				var = m_pSet -> GetFieldValue (FieldInfo.m_strName);	// lese Wert
				if (VT_NULL == var.vt)
					DestSet.SetFieldValueNull (FieldInfo.m_strName);
				else
					DestSet.SetFieldValue (FieldInfo.m_strName, var);
			}
			DestSet.Update ();

			m_pSet -> MoveNext ();
		}

		NewTable.Close ();
		DestSet.Close ();
		dbOut.Close ();
		pWSpace -> CommitTrans ();		// Daten in DB speichern
	}
	catch (CUserException *e)
	{
		e -> Delete ();			// nur Abbruch
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
		pWSpace -> Rollback ();
	}
}

BOOL CQueryResult::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	// TODO: Add your message handler code here and/or call default
	// return CDialog::OnHelpInfo(pHelpInfo);
	ASSERT (pHelpInfo != NULL);

	if (pHelpInfo -> dwContextId)
		WinHelp (pHelpInfo -> dwContextId, HELP_CONTEXTPOPUP);

	return TRUE;
}

