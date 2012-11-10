// StatDlg.cpp : implementation file
//

#include "stdafx.h"		// prec. Header
#include "gak.h"		// CGakApp u. Ressourcen
#include "StatDlg.h"	// zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Konstanten
const short sIniEntryCounts = 2;			//	Anzahl der Eintragungen in INI-Datei

//	Positionen der Labels in der Bitmap
const short OffsetBmpPos = 2;
const short DatabaseBmpPos = 0;
const short TableBmpPos = DatabaseBmpPos + 1;
const short FieldBmpPos = TableBmpPos + OffsetBmpPos;
const short	IndexBmpPos = FieldBmpPos + OffsetBmpPos;
const short	QueryBmpPos = IndexBmpPos + OffsetBmpPos;
const short	RelationBmpPos = QueryBmpPos + OffsetBmpPos;
const short IniBmpPos = RelationBmpPos + OffsetBmpPos;

//	Spalten-Namen
char *ObjektColumnNames [] =
{
	_T("Eigenschaft"), _T("Wert"), NULL
};

char *TableCollectionColumnNames [] =
{
	_T("Name"), _T("Datensätze"), _T("In Benutzung"), _T("Änderbar"), 
	_T("Erzeugt"), _T("Geändert"),  
	NULL
};

char *FieldCollectionColumnNames [] =
{
	_T("Name"), _T("Typ"), _T("Größe"), _T("Größe variabel"), _T("Eingabe erf."), 
	_T("Nullwert erlaubt"), _T("Voreing. Wert"), _T("Tabelle"),
	_T("Gültigkeitsregel"), _T("Gültigkeitstext"), //_T("Fremdname"), 
	NULL
};

char * IndexCollectionColumnNames[] =
{
	_T("Name"), _T("Felder"), _T("Hauptindex"), _T("Enzigartig"), _T("Nullwerte ign."),
	_T("Eingabe erf."), _T("Fremdschlüssel"), 
	_T("Tabelle"), NULL
};

char * QueryCollectionColumnNames[] =
{
	_T("Name"), _T("Typ"), _T("Lief. Datensätze"), _T("Standardabfrage"),
	_T("Änderbar"), _T("Erzeugt"), _T("Geändert"), 
	_T("SQL-Anweisung"), NULL
};

char * RelationCollectionColumnNames[] =
{
	_T("Name"), _T("Tabelle"), _T("Fremdtabelle"), 
	_T("1:N"), _T("Refer. Integrität"), _T("Akt.-Weitergabe"), _T("Löschweitergabe"), 
	_T("Felder"), NULL
};

char * DatabaseCollectionColumnNames[] =
{
	_T("Name"), _T("Transaktion"), _T("Änderbar"), _T("Version"), NULL
};

char * IniInfoCollectionColumnNames[] =
{
	_T("Auswahl"), _T("Auswahlart"), NULL
};

/////////////////////////////////////////////////////////////////////////////
// CStatistikDialog dialog
CStatistikDialog::CStatistikDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CStatistikDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStatistikDialog)
	//}}AFX_DATA_INIT
	m_hActItem = NULL;
	m_tActSelType = NoType;
}

CStatistikDialog ::~CStatistikDialog (void)
{
	if (m_Database.IsOpen ())
		m_Database.Close ();
}


void CStatistikDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStatistikDialog)
	DDX_Control(pDX, IDC_TABLES, m_lcDatabase);
	DDX_Control(pDX, IDT_TABLES, m_trDatabase);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStatistikDialog, CDialog)
	//{{AFX_MSG_MAP(CStatistikDialog)
	ON_NOTIFY(NM_CLICK, IDC_TABLES, OnClickTables)
	ON_NOTIFY(TVN_SELCHANGED, IDT_TABLES, OnSelchangedTables)
	ON_WM_CREATE()
	ON_WM_SYSCOLORCHANGE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStatistikDialog message handlers
void CStatistikDialog::OnClickTables(NMHDR* pNMHDR, LRESULT* pResult) 
{
//	nur Disabeln
	int iIndex = m_lcDatabase.GetNextItem (-1, LVNI_SELECTED);
	if (iIndex >= 0)
		m_lcDatabase.SetItemState (iIndex, 0, LVIS_SELECTED);	// Selektion rücksetzen	
	
	*pResult = 0;
}

BOOL CStatistikDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CGakApp *pApp = (CGakApp *)AfxGetApp ();
	ASSERT (NULL != pApp);
	ASSERT_VALID (pApp);

//	Überschrift für Dialog erzeugen: Nutzername
	CString strInfo, strPar1, strPar2, strCaption;
	AfxFormatString1 (strInfo, IDS_STAT_CAPT_FORMAT, pApp -> UserName ());	
	SetWindowText (strInfo);

//	CListTree init.
/// Attach image list to Tree
	m_trDatabase.SetImageList(&m_ctlImage, TVSIL_NORMAL);

	TV_ITEM item;
	memset (&item, 0, sizeof (TV_ITEM));
	item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	item.iImage = item.iSelectedImage = DatabaseBmpPos;

	TV_INSERTSTRUCT tv;
	memset (&tv, 0, sizeof (TV_INSERTSTRUCT));
	tv.hParent = TVI_ROOT;
	tv.hInsertAfter = TVI_LAST;
	
//	Datenbank öffnen
	CWaitCursor wc;
	m_Database.Open (pApp -> DatabaseName ());

//	Root-Item ist der Name der Datenbank
	CString strFileName, strExt, strNewFileName;
	char *pFileName = strFileName.GetBuffer (_MAX_FNAME);
	char *pExt = strExt.GetBuffer (_MAX_EXT);
	char *pNewFileName = strNewFileName.GetBuffer (_MAX_PATH);
	_splitpath (m_Database.GetName (), NULL, NULL, pFileName, pExt);
	_makepath (pNewFileName, NULL, NULL, pFileName, pExt);

	item.pszText = strupr (pNewFileName);
	item.cchTextMax = strlen (pNewFileName);
	tv.item = item;
	HTREEITEM hRoot = m_trDatabase.InsertItem (&tv);
	if ((NULL == hRoot) || !m_trDatabase.SetItemData (hRoot, DatabaseSel))
		AfxThrowMemoryException ();
	HTREEITEM hItem = NULL;
	
//	Tabellen-Überschrift ausgeben
	int iCnt = m_Database.GetTableDefCount ();
	if (iCnt > 0)
	{
	//	Zähler ohne Systemtabellen
		int iRealTableCnt = 0;
		CDaoTableDefInfo TableInfo;
		int iIndex = 0;
		for (iIndex = 0; iIndex < iCnt; iIndex++)
		{
			m_Database.GetTableDefInfo (iIndex, TableInfo);
			if (TableInfo.m_lAttributes & dbSystemObject)	// keine
				continue;									// Systemtabellen
			iRealTableCnt++;
		}

		if (iRealTableCnt > 0)
		{
			VERIFY (strInfo.LoadString (IDS_TABELLEN));
			strCaption.Format (IDS_COLLECTION_FORMAT, (LPCTSTR)strInfo, iRealTableCnt);
			tv.hParent = hRoot;
			tv.hInsertAfter = TVI_LAST;
			item.pszText = (char *)strCaption.operator LPCTSTR ();
			item.cchTextMax = strCaption.GetLength ();	
			item.iImage = item.iSelectedImage = TableBmpPos;

			tv.item = item;
			HTREEITEM hTables = m_trDatabase.InsertItem (&tv);
			if ((NULL == hTables) || !m_trDatabase.SetItemData (hTables, TableCollectionSel))
				AfxThrowMemoryException ();
	
		//	alle Tabellennamen ausgeben
			item.iImage = item.iSelectedImage = TableBmpPos+1;
			for (iIndex = 0; iIndex < iCnt; iIndex++)
			{
				m_Database.GetTableDefInfo (iIndex, TableInfo);
				if (TableInfo.m_lAttributes & dbSystemObject)	// keine
					continue;									// Systemtabellen

				tv.hParent = hTables;
				tv.hInsertAfter = TVI_SORT;

				item.pszText = (char *)TableInfo.m_strName.operator LPCTSTR ();
				item.cchTextMax = TableInfo.m_strName.GetLength ();	
				tv.item = item;
				HTREEITEM hTable = m_trDatabase.InsertItem (&tv);
				if ((NULL == hTable) || !m_trDatabase.SetItemData (hTable, TableSel))
					AfxThrowMemoryException ();
				tv.hParent = hTable;

			//	Felder ausgeben -> Überschrift
				CDaoTableDef TableDef (&m_Database);
				TableDef.Open (TableInfo.m_strName);
				int iFieldCnt = TableDef.GetFieldCount ();
				if (iFieldCnt > 0)
				{			
					VERIFY (strInfo.LoadString (IDS_FELDER));
					strCaption.Format (IDS_COLLECTION_FORMAT, (LPCTSTR)strInfo, iFieldCnt);
					tv.hInsertAfter = TVI_LAST;
					item.pszText = (char *)strCaption.operator LPCTSTR ();
					item.cchTextMax = strCaption.GetLength ();	
					item.iImage = item.iSelectedImage = FieldBmpPos;
					tv.item = item;
					tv.hParent = m_trDatabase.InsertItem (&tv);
					if ((NULL == tv.hParent) || !m_trDatabase.SetItemData (tv.hParent, FieldCollectionSel))
						AfxThrowMemoryException ();
					tv.hInsertAfter = TVI_SORT;

				//	Felder ausgeben
					CDaoFieldInfo FieldInfo;
					item.iImage = item.iSelectedImage = FieldBmpPos+1;
					for (int iFieldIndex = 0; iFieldIndex < iFieldCnt; iFieldIndex++)
					{
						TableDef.GetFieldInfo (iFieldIndex, FieldInfo);
						item.pszText = (char *)FieldInfo.m_strName.operator LPCTSTR ();
						item.cchTextMax = FieldInfo.m_strName.GetLength ();	
						tv.item = item;
						hItem = m_trDatabase.InsertItem (&tv);
						if ((NULL == hItem) || !m_trDatabase.SetItemData (hItem, FieldSel))
							AfxThrowMemoryException ();
					}
				}	// wenn Felder vorhanden

			//	Indizes ausgeben -> Überschrift
				int iIndexCnt = TableDef.GetIndexCount ();
				if (iIndexCnt > 0)
				{
					VERIFY (strInfo.LoadString (IDS_INDICES));
					strCaption.Format (IDS_COLLECTION_FORMAT, (LPCTSTR)strInfo, iIndexCnt);
					tv.hParent = hTable;
					tv.hInsertAfter = TVI_LAST;
					item.pszText = (char *)strCaption.operator LPCTSTR ();
					item.cchTextMax = strCaption.GetLength ();	
					item.iImage = item.iSelectedImage = IndexBmpPos;
					tv.item = item;
					tv.hParent = m_trDatabase.InsertItem (&tv);
					if ((NULL == tv.hParent) || !m_trDatabase.SetItemData (tv.hParent, IndexCollectionSel))
						AfxThrowMemoryException ();
					tv.hInsertAfter = TVI_SORT;

				//	Indexnamen ausgeben
					CDaoIndexInfo IndexInfo;
					item.iImage = item.iSelectedImage = IndexBmpPos+1;
					for (int iIndexIndex = 0; iIndexIndex < iIndexCnt; iIndexIndex++)
					{
						TableDef.GetIndexInfo (iIndexIndex, IndexInfo);
						item.pszText = (char *)IndexInfo.m_strName.operator LPCTSTR ();
						item.cchTextMax = IndexInfo.m_strName.GetLength ();	
						tv.item = item;
						hItem = m_trDatabase.InsertItem (&tv);
						if ((NULL == hItem) || !m_trDatabase.SetItemData (hItem, IndexSel))
							AfxThrowMemoryException ();
					}
				}	// wenn Indizes vorh.

			//	Tabelle wieder schließen
				if (TableDef.IsOpen ())
					TableDef.Close ();

			//	Index wieder auf Tabellen-Icon
				item.iImage = item.iSelectedImage = TableBmpPos+1;
			}
		}		//	 wenn Tabellen vorhanden (ohne Systemtabellen)
	}			//	 wenn Tabellen vorhanden (+Systemtabellen)

//	Abfragen-Überschrift ausgeben
	iCnt = m_Database.GetQueryDefCount ();
	if (iCnt > 0)
	{
		VERIFY (strInfo.LoadString (IDS_ABFRAGEN));
		strCaption.Format (IDS_COLLECTION_FORMAT, (LPCTSTR)strInfo, iCnt);
		tv.hParent = hRoot;
		tv.hInsertAfter = TVI_LAST;
		item.pszText = (char *)strCaption.operator LPCTSTR ();
		item.cchTextMax = strCaption.GetLength ();	
		item.iImage = item.iSelectedImage = QueryBmpPos;

		tv.item = item;
		tv.hParent = m_trDatabase.InsertItem (&tv);
		if ((NULL == tv.hParent) || !m_trDatabase.SetItemData (tv.hParent, QueryCollectionSel))
			AfxThrowMemoryException ();
		tv.hInsertAfter = TVI_SORT;

	//	alle Abfragen ausgeben
		CDaoQueryDefInfo QueryInfo;
		item.iImage = item.iSelectedImage = QueryBmpPos+1;
		for (int iIndex = 0; iIndex < iCnt; iIndex++)
		{
			m_Database.GetQueryDefInfo (iIndex, QueryInfo);
			item.pszText = (char *)QueryInfo.m_strName.operator LPCTSTR ();
			item.cchTextMax = QueryInfo.m_strName.GetLength ();	
			tv.item = item;
			hItem = m_trDatabase.InsertItem (&tv);
			if ((NULL == hItem) || !m_trDatabase.SetItemData (hItem, QuerySel))
				AfxThrowMemoryException ();
		}
	}	// wenn Abfragen vorhanden

//	Relationen ausgeben: Überschrift
	iCnt = m_Database.GetRelationCount ();
	if (iCnt > 0)
	{
		VERIFY (strInfo.LoadString (IDS_RELATIONS));
		strCaption.Format (IDS_COLLECTION_FORMAT, (LPCTSTR)strInfo, iCnt);
		tv.hParent = hRoot;
		tv.hInsertAfter = TVI_LAST;
		item.pszText = (char *)strCaption.operator LPCTSTR ();
		item.cchTextMax = strCaption.GetLength ();	
		item.iImage = item.iSelectedImage = RelationBmpPos;

		tv.item = item;
		tv.hParent = m_trDatabase.InsertItem (&tv);
		if ((NULL == tv.hParent) || !m_trDatabase.SetItemData (tv.hParent, RelationCollectionSel))
			AfxThrowMemoryException ();
		tv.hInsertAfter = TVI_SORT;

	//	alle Relationen ausgeben
		CDaoRelationInfo RelInfo;
		item.iImage = item.iSelectedImage = RelationBmpPos+1;
		for (int iIndex = 0; iIndex < iCnt; iIndex++)
		{
			m_Database.GetRelationInfo (iIndex, RelInfo);
			item.pszText = (char *)RelInfo.m_strName.operator LPCTSTR ();
			item.cchTextMax = RelInfo.m_strName.GetLength ();	
			tv.item = item;
			hItem = m_trDatabase.InsertItem (&tv);
			if ((NULL == hItem) || !m_trDatabase.SetItemData (hItem, RelationSel))
				AfxThrowMemoryException ();
		}
	}	//	 wenn Realationen vorhanden

	VERIFY (strInfo.LoadString (IDS_INI_ENTRIES));		//	Eintragungen in INI-Datei
	strCaption.Format (IDS_COLLECTION_FORMAT, (LPCTSTR)strInfo, sIniEntryCounts);
	tv.hParent = hRoot;
	tv.hInsertAfter = TVI_LAST;
	item.pszText = (char *)strCaption.operator LPCTSTR ();
	item.cchTextMax = strCaption.GetLength ();	
	item.iImage = item.iSelectedImage = IniBmpPos;

	tv.item = item;
	tv.hParent = m_trDatabase.InsertItem (&tv);
	if ((NULL == tv.hParent) || !m_trDatabase.SetItemData (tv.hParent, IniInfoCollectionSel))
		AfxThrowMemoryException ();
	tv.hInsertAfter = TVI_SORT;

//	Ini-Infos ausgeben
	item.iImage = item.iSelectedImage = IniBmpPos+1;

//	Entsorger
	VERIFY (strInfo.LoadString (IDS_ENTSORGER));
	item.pszText = (char *)strInfo.operator LPCTSTR ();
	item.cchTextMax = strInfo.GetLength ();	
	tv.item = item;
	hItem = m_trDatabase.InsertItem (&tv);
	if ((NULL == hItem) || !m_trDatabase.SetItemData (hItem, IniInfoSel))
		AfxThrowMemoryException ();

//	Transporteure
	VERIFY (strInfo.LoadString (IDS_TRANSP));
	item.pszText = (char *)strInfo.operator LPCTSTR ();
	item.cchTextMax = strInfo.GetLength ();	
	tv.item = item;
	hItem = m_trDatabase.InsertItem (&tv);
	if ((NULL == hItem) || !m_trDatabase.SetItemData (hItem, IniInfoSel))
		AfxThrowMemoryException ();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

int CStatistikDialog::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
//	TODO: Add your specialized creation code here
	m_ctlImage.Create(IDB_IMAGE_LIST,16,0,RGB(255,0,255));
	m_ctlImage.SetBkColor(GetSysColor(COLOR_WINDOW));

	return 0;
}

void CStatistikDialog::OnSysColorChange() 
{
	CDialog::OnSysColorChange();
	
	// TODO: Add your message handler code here
	m_ctlImage.SetBkColor(GetSysColor(COLOR_WINDOW));
}

//	Selektion im Baum hat sich geändert
void CStatistikDialog::OnSelchangedTables(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here

	HTREEITEM hItem = m_trDatabase.GetSelectedItem ();
	if ((NULL != hItem) && (hItem != m_hActItem))	
	{
		try
		{
			CMutex mt;			
			CWaitCursor wc;
			m_hActItem = hItem;		// Item merken
	
		//	lese Item-Typ
			DWORD dwData = m_trDatabase.GetItemData (hItem); 
			ASSERT (0 != dwData);

		//	Spalten-Namen neu ausgeben
			SetColumnNames ((SelectType) dwData);

		//	Werte in Tabelle ausgeben
			OutputItemValues ((SelectType) dwData);
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
	
	*pResult = 0;
}

//	aktueller Selektions-Typ ein Object ?
BOOL CStatistikDialog::IsObject (SelectType tType)
{
	switch (tType)
	{
		case DatabaseSel:
		case TableSel:
		case FieldSel:
		case IndexSel:
		case QuerySel:
		case RelationSel:
		case IniInfoSel:
			return TRUE;		
	}

	return FALSE;
}

//	aktueller Selektions-Typ eine Collection ?
BOOL CStatistikDialog::IsCollection (SelectType tType)
{
	switch (tType)
	{
		case TableCollectionSel:
		case FieldCollectionSel:
		case IndexCollectionSel:
		case QueryCollectionSel:
		case RelationCollectionSel:
		case IniInfoCollectionSel:
			return TRUE;		
	}

	return FALSE;
}

//	Spalten-Namen neu ausgeben
void CStatistikDialog::SetColumnNames (SelectType tType)
{
//	alte Type bereits eingestellt ?
	if (m_tActSelType == tType)
		return;

//	sind alter und neuer Type Collection, dann keine Aktion notwendig
	if (IsObject (tType) && IsObject (m_tActSelType))
	{
		m_tActSelType = tType;		// Typ nur umkopieren
		return;
	}

//	alle Datensätze und Spalten löschen
	VERIFY (m_lcDatabase.DeleteAllItems ());

//	alle Spalten löschen
	while (m_lcDatabase.DeleteColumn (0));
	
	m_tActSelType = tType;		// Typ umkopieren
	char **ppColumnNames = NULL;
	switch (tType)
	{
		case NoType:			// nothing to do
			return;
		break;
		case DatabaseSel:			// Objekte haben nur --> Eigenschaft und Wert als Spaltennamen
		case TableSel:
		case FieldSel:
		case IndexSel:
		case QuerySel:
		case RelationSel:
		case IniInfoSel:
			ppColumnNames = ObjektColumnNames;
		break;
		case TableCollectionSel:
			ppColumnNames = TableCollectionColumnNames;
		break;
		case FieldCollectionSel:
			ppColumnNames = FieldCollectionColumnNames;
		break;
		case IndexCollectionSel:
			ppColumnNames = IndexCollectionColumnNames;
		break;
		case QueryCollectionSel:
			ppColumnNames = QueryCollectionColumnNames;
		break;
		case RelationCollectionSel:
			ppColumnNames = RelationCollectionColumnNames;
		break;
		case IniInfoCollectionSel:
			ppColumnNames = IniInfoCollectionColumnNames;
		break;
		default:
			ASSERT (FALSE);
	}

	ASSERT (NULL != ppColumnNames);
	int iFieldCnt = 0;

//	bei Collection Spalte 'Position' erzeugen
	if (IsCollection (tType))
	{
		CString strFieldName;
		VERIFY (strFieldName.LoadString (IDS_POSITION));
		if (m_lcDatabase.InsertColumn (iFieldCnt, strFieldName) != iFieldCnt)
			AfxThrowMemoryException ();

		iFieldCnt++;		// nächste Spalte
	}

//	Spaltennamen ausgeben
	int iIndex = 0;
	for (char *pName = ppColumnNames [iIndex]; pName && *pName; 
		 iIndex++, pName = ppColumnNames [iIndex])
	{
		if (m_lcDatabase.InsertColumn (iFieldCnt, pName) != iFieldCnt)
			AfxThrowMemoryException ();

		iFieldCnt++;		// nächste Spalte						
	}

//	Spaltenbreiten setzen
	CRect rc;
	m_lcDatabase.GetClientRect (rc);
	if (iFieldCnt == 2)
	{
		m_lcDatabase.SetColumnWidth (0, rc.Width () / 4);			
		m_lcDatabase.SetColumnWidth (1, rc.Width () * 3 / 4);			
	}
	else
	{
		for (int iItem = 0; iItem < iFieldCnt; iItem++)
			m_lcDatabase.SetColumnWidth (iItem, LVSCW_AUTOSIZE_USEHEADER);

	//	Namenspalte vergößern
		m_lcDatabase.SetColumnWidth (1, rc.Width () / 5);			
	}
}

//	Werte in Tabelle ausgeben
void CStatistikDialog::OutputItemValues (SelectType tType)
{
	switch (tType)
	{
		case NoType:			// nothing to do
			return;
		break;
		case DatabaseSel:			
			OutputDatabaseInfo (TRUE);
		break;
		case TableSel:
			OutputTableInfo (TRUE);
		break;
		case FieldSel:
			OutputFieldInfo (TRUE);
		break;
		case IndexSel:
			OutputIndexInfo (TRUE);
		break;
		case QuerySel:
			OutputQueryInfo (TRUE);
		break;
		case RelationSel:
			OutputRelationInfo (TRUE);
		break;
		case IniInfoSel: 
			OutputIniInfo (TRUE);
		break;
		case TableCollectionSel:
			OutputTableInfo (FALSE);
		break;
		case FieldCollectionSel:
			OutputFieldInfo (FALSE);
		break;
		case IndexCollectionSel:
			OutputIndexInfo (FALSE);
		break;
		case QueryCollectionSel:
			OutputQueryInfo (FALSE);
		break;
		case RelationCollectionSel:
			OutputRelationInfo (FALSE);
		break;
		case IniInfoCollectionSel:
			OutputIniInfo (FALSE);
		break;
		default:
			ASSERT (FALSE);
	}		
}

//	"Eigenschaft"-Spalte füllen
int CStatistikDialog::OutputPropertyColumn (char **ppColNames)
{
	ASSERT (NULL != ppColNames);
	ASSERT (NULL != *ppColNames);

	int iIndex = 0;
	for (char *pName = ppColNames [iIndex]; pName && *pName;
		 iIndex++, pName = ppColNames [iIndex])
	{
		if (m_lcDatabase.InsertItem (iIndex, pName) != iIndex)
			AfxThrowMemoryException ();
	}

	return iIndex;
}	

//	Ausgabe der Informationen für die aktuelle selektierte Datenbank
void CStatistikDialog::OutputDatabaseInfo (BOOL bObjekt)
{
	ASSERT (TRUE == bObjekt);		// nur Objekt-Ausgabe
	ASSERT (m_Database.IsOpen ());

//	alle Datensätze löschen
	VERIFY (m_lcDatabase.DeleteAllItems ());

//	Spalte "Eigenschaft" füllen
	int iCnt = OutputPropertyColumn (DatabaseCollectionColumnNames);
	
//	Ausgabe OK ?
	ASSERT (iCnt != (sizeof (DatabaseCollectionColumnNames) / sizeof (char *)));

//	Name der Datenbank
	if (!m_lcDatabase.SetItemText (0, 1, m_Database.GetName ()))
		AfxThrowMemoryException ();
	
	CString strInfo;

//	Transaktion
	VERIFY (strInfo.LoadString (m_Database.CanTransact () ? IDS_JA : IDS_NEIN));
	if (!m_lcDatabase.SetItemText (1, 1, strInfo))
		AfxThrowMemoryException ();

//	Änderbar
	VERIFY (strInfo.LoadString (m_Database.CanUpdate () ? IDS_JA : IDS_NEIN));
	if (!m_lcDatabase.SetItemText (2, 1, strInfo))
		AfxThrowMemoryException ();

//	Version
	if (!m_lcDatabase.SetItemText (3, 1, m_Database.GetVersion ()))
		AfxThrowMemoryException ();
}

//	Ausgabe der Informationen aus der INI-Datei
void CStatistikDialog::OutputIniInfo (BOOL bObjekt)
{
	CGakApp *pApp = (CGakApp *)AfxGetApp ();
	ASSERT (NULL != pApp);
	ASSERT_VALID (pApp);

//	alle Datensätze löschen
	VERIFY (m_lcDatabase.DeleteAllItems ());

//	Objekt-Ausgabe ?
	CString strItemText;
	if (bObjekt)
	{
	//	Spalte "Eigenschaft" füllen
		int iCnt = 0;
		iCnt = OutputPropertyColumn (IniInfoCollectionColumnNames);
	
	//	Ausgabe OK ?
		ASSERT (iCnt != (sizeof (IniInfoCollectionColumnNames) / sizeof (char *)));

	//	lese Item-Text
		ASSERT (NULL != m_hActItem);
		strItemText = m_trDatabase.GetItemText (m_hActItem);
		ASSERT (!strItemText.IsEmpty ());
	}
	else
		VERIFY (strItemText.LoadString (IDS_ENTSORGER));

//	lese Anzahl Einträge
	int iIniCnt = bObjekt ? 1 : sIniEntryCounts;
	
	CString strTemp, strCmp, strInfo;
	VERIFY (strCmp.LoadString (IDS_ENTSORGER));

	int iActCol = 0;
	int iRowIndex = 0;
	for (int iIndex = 0; iIndex < iIniCnt; iIndex++, iActCol = 0)
	{
		if (!bObjekt)
		{
			strTemp.Format ("%d", iIndex+1);					// akt. Nummer bei Collection
			if (m_lcDatabase.InsertItem (iIndex, strTemp) != iIndex)
				AfxThrowMemoryException ();
			iActCol++;
		}

	//	Info-String laden
		if (0 == strItemText.CompareNoCase (strCmp))
			VERIFY (strInfo.LoadString (pApp -> OnlyValidEntsorger () ? IDS_ONLY_VALIDS : IDS_ALLE));
		else
			VERIFY (strInfo.LoadString (pApp -> OnlyValidTransporteure () ? IDS_ONLY_VALIDS : IDS_ALLE));

	//	Name der Auswahltabelle ausgeben
		if (!m_lcDatabase.SetItemText (bObjekt ? iRowIndex++ : iIndex, bObjekt ? 1 : iActCol++, 
									   bObjekt ? strItemText : strCmp))
			AfxThrowMemoryException ();

	//	Info zur Ausahl der Tabelle ausgeben
		if (!m_lcDatabase.SetItemText (bObjekt ? iRowIndex++ : iIndex, bObjekt ? 1 : iActCol++, strInfo))
			AfxThrowMemoryException ();

	//	ggf. SuchInfo umkehren
		if (!bObjekt)
			VERIFY (strCmp.LoadString (IDS_TRANSP));
	}
}

//	Ausgabe der Informationen über vorhandene Relationen
void CStatistikDialog::OutputRelationInfo (BOOL bObjekt)
{
	ASSERT (m_Database.IsOpen ());

//	alle Datensätze löschen
	VERIFY (m_lcDatabase.DeleteAllItems ());

//	Objekt-Ausgabe ?
	CString strItemText;
	if (bObjekt)
	{
	//	Spalte "Eigenschaft" füllen
		int iCnt = 0;
		iCnt = OutputPropertyColumn (RelationCollectionColumnNames);
	
	//	Ausgabe OK ?
		ASSERT (iCnt != (sizeof (RelationCollectionColumnNames) / sizeof (char *)));

	//	lese Item-Text
		ASSERT (NULL != m_hActItem);
		strItemText = m_trDatabase.GetItemText (m_hActItem);
		ASSERT (!strItemText.IsEmpty ());
	}

//	lese Anzahl Relationen
	int iRelCnt = m_Database.GetRelationCount ();
	if (bObjekt)
		iRelCnt = 1;		// nur für 1 Objekt

	CDaoRelationInfo Info;
	CString strTemp;
	int iActCol = 0;
	int iRowIndex = 0;
	for (int iIndex = 0; iIndex < iRelCnt; iIndex++, iActCol = 0)
	{
		if (bObjekt)
			m_Database.GetRelationInfo (strItemText, Info, AFX_DAO_SECONDARY_INFO);	
		else
		{
			m_Database.GetRelationInfo (iIndex, Info, AFX_DAO_SECONDARY_INFO);
			strTemp.Format ("%d", iIndex+1);					// akt. Nummer bei Collection
			if (m_lcDatabase.InsertItem (iIndex, strTemp) != iIndex)
				AfxThrowMemoryException ();
			iActCol++;
		}

	//	Name der Relation ausgeben
		if (!m_lcDatabase.SetItemText (bObjekt ? iRowIndex++ : iIndex, bObjekt ? 1 : iActCol++, Info.m_strName))
			AfxThrowMemoryException ();

	//	Name der Tabelle ausgeben
		if (!m_lcDatabase.SetItemText (bObjekt ? iRowIndex++ : iIndex, bObjekt ? 1 : iActCol++, Info.m_strTable))
			AfxThrowMemoryException ();

	//	Name der Fremdtabelle ausgeben
		if (!m_lcDatabase.SetItemText (bObjekt ? iRowIndex++ : iIndex, bObjekt ? 1 : iActCol++, Info.m_strForeignTable))
			AfxThrowMemoryException ();

	//	Art der Beziehung --> 1 : n ?
		VERIFY (strTemp.LoadString (Info.m_lAttributes & dbRelationUnique ? IDS_NEIN : IDS_JA));
		if (!m_lcDatabase.SetItemText (bObjekt ? iRowIndex++ : iIndex, bObjekt ? 1 : iActCol++, strTemp))
			AfxThrowMemoryException ();

	//	Ref. Integrität
		VERIFY (strTemp.LoadString (Info.m_lAttributes & dbRelationDontEnforce ? IDS_NEIN : IDS_JA));
		if (!m_lcDatabase.SetItemText (bObjekt ? iRowIndex++ : iIndex, bObjekt ? 1 : iActCol++, strTemp))
			AfxThrowMemoryException ();

	//	Akt.- Weitergabe
		VERIFY (strTemp.LoadString (Info.m_lAttributes & dbRelationUpdateCascade ? IDS_JA : IDS_NEIN));
		if (!m_lcDatabase.SetItemText (bObjekt ? iRowIndex++ : iIndex, bObjekt ? 1 : iActCol++, strTemp))
			AfxThrowMemoryException ();

	//	Löschweitergabe
		VERIFY (strTemp.LoadString (Info.m_lAttributes & dbRelationDeleteCascade ? IDS_JA : IDS_NEIN));
		if (!m_lcDatabase.SetItemText (bObjekt ? iRowIndex++ : iIndex, bObjekt ? 1 : iActCol++, strTemp))
			AfxThrowMemoryException ();

	//	zugeh.Feldnamen ausgeben
		strTemp.Empty ();
		for (int iFieldIndex = 0; iFieldIndex < Info.m_nFields; iFieldIndex++)
		{
			strTemp += Info.m_pFieldInfos [iFieldIndex].m_strName;
			if ((iFieldIndex + 1) < Info.m_nFields)
				strTemp += "+";
		}
		if (!m_lcDatabase.SetItemText (bObjekt ? iRowIndex++ : iIndex, bObjekt ? 1 : iActCol++, strTemp))
			AfxThrowMemoryException ();
	}
}

//	Ausgabe der Tabellen-Informationen
void CStatistikDialog::OutputTableInfo (BOOL bObjekt)
{
	ASSERT (m_Database.IsOpen ());

//	alle Datensätze löschen
	VERIFY (m_lcDatabase.DeleteAllItems ());

//	Objekt-Ausgabe ?
	CString strItemText;
	if (bObjekt)
	{
	//	Spalte "Eigenschaft" füllen
		int iCnt = 0;
		iCnt = OutputPropertyColumn (TableCollectionColumnNames);
	
	//	Ausgabe OK ?
		ASSERT (iCnt != (sizeof (TableCollectionColumnNames) / sizeof (char *)));

	//	lese Item-Text
		ASSERT (NULL != m_hActItem);
		strItemText = m_trDatabase.GetItemText (m_hActItem);
		ASSERT (!strItemText.IsEmpty ());
	}

//	lese Anzahl Tabellen
	int iTableCnt = m_Database.GetTableDefCount ();
	if (bObjekt)
		iTableCnt = 1;		// nur für 1 Objekt

	CDaoTableDefInfo Info;
	CString strTemp;
	int iActCol = 0;
	int iRowIndex = 0;
	int iIndex = 0;
	for (int iCntIndex = 0; iCntIndex < iTableCnt; iCntIndex++, iActCol = 0)
	{
		if (bObjekt)
			m_Database.GetTableDefInfo (strItemText, Info, AFX_DAO_ALL_INFO);	
		else
			m_Database.GetTableDefInfo (iCntIndex, Info, AFX_DAO_ALL_INFO);


	//	keine System-Tabelle
		if (Info.m_lAttributes & dbSystemObject)
			continue;			

		if (!bObjekt)
		{
			strTemp.Format ("%d", iIndex+1);					// akt. Nummer bei Collection
			if (m_lcDatabase.InsertItem (iIndex, strTemp) != iIndex)
				AfxThrowMemoryException ();
			iActCol++;
		}			

	//	Name der Tabelle ausgeben
		if (!m_lcDatabase.SetItemText (bObjekt ? iRowIndex++ : iIndex, bObjekt ? 1 : iActCol++, Info.m_strName))
			AfxThrowMemoryException ();

	//	Anzahl Datensätze ausgeben
		strTemp.Format ("%ld", Info.m_lRecordCount);
		if (!m_lcDatabase.SetItemText (bObjekt ? iRowIndex++ : iIndex, bObjekt ? 1 : iActCol++, strTemp))
			AfxThrowMemoryException ();

	//	Tabelle bei Eingabe verwendet
		VERIFY (strTemp.LoadString (((CGakApp *) AfxGetApp ()) -> TableInUse (Info.m_strName) ? IDS_JA : IDS_NEIN));
		if (!m_lcDatabase.SetItemText (bObjekt ? iRowIndex++ : iIndex, bObjekt ? 1 : iActCol++, strTemp))
			AfxThrowMemoryException ();

	//	Änderbar ?
		VERIFY (strTemp.LoadString (Info.m_bUpdatable ? IDS_JA : IDS_NEIN));
		if (!m_lcDatabase.SetItemText (bObjekt ? iRowIndex++ : iIndex, bObjekt ? 1 : iActCol++, strTemp))
			AfxThrowMemoryException ();

	//	Erzeugt
		strTemp = Info.m_dateCreated.Format ((UINT) IDS_DATETIME_FORMAT);
		if (!m_lcDatabase.SetItemText (bObjekt ? iRowIndex++ : iIndex, bObjekt ? 1 : iActCol++, strTemp))
			AfxThrowMemoryException ();

	//	Geändert
		strTemp = Info.m_dateLastUpdated.Format ((UINT) IDS_DATETIME_FORMAT);
		if (!m_lcDatabase.SetItemText (bObjekt ? iRowIndex++ : iIndex, bObjekt ? 1 : iActCol++, strTemp))
			AfxThrowMemoryException ();

		iIndex++;
	}
}

//	Ausgabe der Informationen über vorhandene Abfragen
void CStatistikDialog::OutputQueryInfo (BOOL bObjekt)
{
	ASSERT (m_Database.IsOpen ());

//	alle Datensätze löschen
	VERIFY (m_lcDatabase.DeleteAllItems ());

//	Objekt-Ausgabe ?
	CString strItemText;
	if (bObjekt)
	{
	//	Spalte "Eigenschaft" füllen
		int iCnt = 0;
		iCnt = OutputPropertyColumn (QueryCollectionColumnNames);
	
	//	Ausgabe OK ?
		ASSERT (iCnt != (sizeof (QueryCollectionColumnNames) / sizeof (char *)));

	//	lese Item-Text
		ASSERT (NULL != m_hActItem);
		strItemText = m_trDatabase.GetItemText (m_hActItem);
		ASSERT (!strItemText.IsEmpty ());
	}

//	lese Anzahl Relationen
	int iQueryCnt = m_Database.GetQueryDefCount ();
	if (bObjekt)
		iQueryCnt = 1;		// nur für 1 Objekt

	CDaoQueryDefInfo Info;
	CString strTemp;
	int iActCol = 0;
	int iRowIndex = 0;
	const char *pBilanz = NULL;
	for (int iIndex = 0; iIndex < iQueryCnt; iIndex++, iActCol = 0)
	{
		if (bObjekt)
			m_Database.GetQueryDefInfo (strItemText, Info, AFX_DAO_ALL_INFO);	
		else
		{
			m_Database.GetQueryDefInfo (iIndex, Info, AFX_DAO_ALL_INFO);
			strTemp.Format ("%d", iIndex+1);					// akt. Nummer bei Collection
			if (m_lcDatabase.InsertItem (iIndex, strTemp) != iIndex)
				AfxThrowMemoryException ();
			iActCol++;
		}

	//	Name der Abfrage ausgeben
		if (!m_lcDatabase.SetItemText (bObjekt ? iRowIndex++ : iIndex, bObjekt ? 1 : iActCol++, Info.m_strName))
			AfxThrowMemoryException ();

	//	Typ der Abfrage ausgeben
		if (!m_lcDatabase.SetItemText (bObjekt ? iRowIndex++ : iIndex, bObjekt ? 1 : iActCol++, 
									   GetQueryType (Info.m_nType)))
			AfxThrowMemoryException ();

	//	liefert Datensätze
		VERIFY (strTemp.LoadString (Info.m_bReturnsRecords ? IDS_JA : IDS_NEIN));
		if (!m_lcDatabase.SetItemText (bObjekt ? iRowIndex++ : iIndex, bObjekt ? 1 : iActCol++, strTemp))
			AfxThrowMemoryException ();

	//	Standardabfrage
		pBilanz = strstr(Info.m_strName, BilanzKennung);
		VERIFY (strTemp.LoadString (pBilanz && (pBilanz == Info.m_strName) ? IDS_NEIN : IDS_JA));
		if (!m_lcDatabase.SetItemText (bObjekt ? iRowIndex++ : iIndex, bObjekt ? 1 : iActCol++, strTemp))
			AfxThrowMemoryException ();

	//	Änderbar ?
		VERIFY (strTemp.LoadString (Info.m_bUpdatable ? IDS_JA : IDS_NEIN));
		if (!m_lcDatabase.SetItemText (bObjekt ? iRowIndex++ : iIndex, bObjekt ? 1 : iActCol++, strTemp))
			AfxThrowMemoryException ();

	//	Erzeugt
		strTemp = Info.m_dateCreated.Format ((UINT) IDS_DATETIME_FORMAT);
		if (!m_lcDatabase.SetItemText (bObjekt ? iRowIndex++ : iIndex, bObjekt ? 1 : iActCol++, strTemp))
			AfxThrowMemoryException ();

	//	Geändert
		strTemp = Info.m_dateLastUpdated.Format ((UINT) IDS_DATETIME_FORMAT);
		if (!m_lcDatabase.SetItemText (bObjekt ? iRowIndex++ : iIndex, bObjekt ? 1 : iActCol++, strTemp))
			AfxThrowMemoryException ();

	//	SQL-Anweisung
		if (!m_lcDatabase.SetItemText (bObjekt ? iRowIndex++ : iIndex, bObjekt ? 1 : iActCol++, Info.m_strSQL))
			AfxThrowMemoryException ();
	}
}

//	Ausgabe der Informationen über selektierten Index
void CStatistikDialog::OutputIndexInfo (BOOL bObjekt)
{
	ASSERT (m_Database.IsOpen ());
	ASSERT (NULL != m_hActItem);

//	alle Datensätze löschen
	VERIFY (m_lcDatabase.DeleteAllItems ());

//	Objekt-Ausgabe ?
	CString strItemText;
	if (bObjekt)
	{
	//	Spalte "Eigenschaft" füllen
		int iCnt = 0;
		iCnt = OutputPropertyColumn (IndexCollectionColumnNames);
	
	//	Ausgabe OK ?
		ASSERT (iCnt != (sizeof (IndexCollectionColumnNames) / sizeof (char *)));

	//	lese Item-Text
		strItemText = m_trDatabase.GetItemText (m_hActItem);
		ASSERT (!strItemText.IsEmpty ());
	}

//	lese Namen der zugeh. Tabelle
	HTREEITEM hItem = m_trDatabase.GetParentItem (m_hActItem);		// Tabelle
	ASSERT (NULL != hItem);

//	bei Objekt noch einen Parent höher
	if (bObjekt)
	{
		hItem = m_trDatabase.GetParentItem (hItem);
		ASSERT (NULL != hItem);
	}
	
	CString strTableName (m_trDatabase.GetItemText (hItem));
	ASSERT (!strTableName.IsEmpty ());
	CDaoTableDef TableDef (&m_Database);
	TableDef.Open (strTableName);

//	lese Anzahl Indizes
	int iIndexCnt = TableDef.GetIndexCount ();

	if (bObjekt)
		iIndexCnt = 1;		// nur für 1 Objekt

	CDaoIndexInfo Info;
	CString strTemp;
	int iActCol = 0;
	int iRowIndex = 0;
	for (int iIndex = 0; iIndex < iIndexCnt; iIndex++, iActCol = 0)
	{
		if (bObjekt)
			TableDef.GetIndexInfo (strItemText, Info, AFX_DAO_SECONDARY_INFO);	
		else
		{
			TableDef.GetIndexInfo (iIndex, Info, AFX_DAO_SECONDARY_INFO);
			strTemp.Format ("%d", iIndex+1);					// akt. Nummer bei Collection
			if (m_lcDatabase.InsertItem (iIndex, strTemp) != iIndex)
				AfxThrowMemoryException ();
			iActCol++;
		}

	//	Name des Index ausgeben
		if (!m_lcDatabase.SetItemText (bObjekt ? iRowIndex++ : iIndex, bObjekt ? 1 : iActCol++, Info.m_strName))
			AfxThrowMemoryException ();

	//	zugeh.Feldnamen ausgeben
		strTemp.Empty ();
		for (int iFieldIndex = 0; iFieldIndex < Info.m_nFields; iFieldIndex++)
		{
			strTemp += Info.m_pFieldInfos [iFieldIndex].m_strName;
			if ((iFieldIndex + 1) < Info.m_nFields)
				strTemp += "+";
		}
		if (!m_lcDatabase.SetItemText (bObjekt ? iRowIndex++ : iIndex, bObjekt ? 1 : iActCol++, strTemp))
			AfxThrowMemoryException ();

	//	HauptIndex
		VERIFY (strTemp.LoadString (Info.m_bPrimary ? IDS_JA : IDS_NEIN));
		if (!m_lcDatabase.SetItemText (bObjekt ? iRowIndex++ : iIndex, bObjekt ? 1 : iActCol++, strTemp))
			AfxThrowMemoryException ();

	//	Einzigartig
		VERIFY (strTemp.LoadString (Info.m_bUnique ? IDS_JA : IDS_NEIN));
		if (!m_lcDatabase.SetItemText (bObjekt ? iRowIndex++ : iIndex, bObjekt ? 1 : iActCol++, strTemp))
			AfxThrowMemoryException ();

	//	Nullwerte ignorieren
		VERIFY (strTemp.LoadString (Info.m_bIgnoreNulls ? IDS_JA : IDS_NEIN));
		if (!m_lcDatabase.SetItemText (bObjekt ? iRowIndex++ : iIndex, bObjekt ? 1 : iActCol++, strTemp))
			AfxThrowMemoryException ();

	//	Eingabe erforderlich
		VERIFY (strTemp.LoadString (Info.m_bRequired ? IDS_JA : IDS_NEIN));
		if (!m_lcDatabase.SetItemText (bObjekt ? iRowIndex++ : iIndex, bObjekt ? 1 : iActCol++, strTemp))
			AfxThrowMemoryException ();

	//	Fremdschlüssel
		VERIFY (strTemp.LoadString (Info.m_bForeign ? IDS_JA : IDS_NEIN));
		if (!m_lcDatabase.SetItemText (bObjekt ? iRowIndex++ : iIndex, bObjekt ? 1 : iActCol++, strTemp))
			AfxThrowMemoryException ();

	//	Name der Tabelle
		if (!m_lcDatabase.SetItemText (bObjekt ? iRowIndex++ : iIndex, bObjekt ? 1 : iActCol++, strTableName))
			AfxThrowMemoryException ();			
	}

	if (TableDef.IsOpen ())
		TableDef.Close ();
}

//	Ausgabe der Informationen über selektiertes Feld
void CStatistikDialog::OutputFieldInfo (BOOL bObjekt)
{
	ASSERT (m_Database.IsOpen ());
	ASSERT (NULL != m_hActItem);

//	alle Datensätze löschen
	VERIFY (m_lcDatabase.DeleteAllItems ());

//	Objekt-Ausgabe ?
	CString strItemText;
	if (bObjekt)
	{
	//	Spalte "Eigenschaft" füllen
		int iCnt = 0;
		iCnt = OutputPropertyColumn (FieldCollectionColumnNames);
	
	//	Ausgabe OK ?
		ASSERT (iCnt != (sizeof (FieldCollectionColumnNames) / sizeof (char *)));

	//	lese Item-Text
		strItemText = m_trDatabase.GetItemText (m_hActItem);
		ASSERT (!strItemText.IsEmpty ());
	}

//	lese Namen der zugeh. Tabelle
	HTREEITEM hItem = m_trDatabase.GetParentItem (m_hActItem);		// Tabelle
	ASSERT (NULL != hItem);

//	bei Objekt noch einen Parent höher
	if (bObjekt)
	{
		hItem = m_trDatabase.GetParentItem (hItem);
		ASSERT (NULL != hItem);
	}
	
	CString strTableName (m_trDatabase.GetItemText (hItem));
	ASSERT (!strTableName.IsEmpty ());
	CDaoTableDef TableDef (&m_Database);
	TableDef.Open (strTableName);

//	lese Anzahl Felder
	int iFieldCnt = TableDef.GetFieldCount ();

	if (bObjekt)
		iFieldCnt = 1;		// nur für 1 Objekt

	CDaoFieldInfo Info;
	CString strTemp;
	int iActCol = 0;
	int iRowIndex = 0;
	for (int iIndex = 0; iIndex < iFieldCnt; iIndex++, iActCol = 0)
	{
		if (bObjekt)
			TableDef.GetFieldInfo (strItemText, Info, AFX_DAO_ALL_INFO);	
		else
		{
			TableDef.GetFieldInfo (iIndex, Info, AFX_DAO_ALL_INFO);
			strTemp.Format ("%d", iIndex+1);					// akt. Nummer bei Collection
			if (m_lcDatabase.InsertItem (iIndex, strTemp) != iIndex)
				AfxThrowMemoryException ();
			iActCol++;
		}

	//	Name des Feldes ausgeben
		if (!m_lcDatabase.SetItemText (bObjekt ? iRowIndex++ : iIndex, bObjekt ? 1 : iActCol++, 
									   Info.m_strName))
			AfxThrowMemoryException ();

	//	Type
		if (!m_lcDatabase.SetItemText (bObjekt ? iRowIndex++ : iIndex, bObjekt ? 1 : iActCol++, 
									   GetFieldType (Info.m_nType)))
			AfxThrowMemoryException ();

	//	Größe
		strTemp.Format ("%ld", Info.m_lSize);
		if (!m_lcDatabase.SetItemText (bObjekt ? iRowIndex++ : iIndex, bObjekt ? 1 : iActCol++, strTemp))
			AfxThrowMemoryException ();

	//	Größe variabel
		VERIFY (strTemp.LoadString (Info.m_lAttributes & dbVariableField ? IDS_JA : IDS_NEIN));
		if (!m_lcDatabase.SetItemText (bObjekt ? iRowIndex++ : iIndex, bObjekt ? 1 : iActCol++, strTemp))
			AfxThrowMemoryException ();

	//	Eingabe erforderlich
		VERIFY (strTemp.LoadString (Info.m_bRequired ? IDS_JA : IDS_NEIN));
		if (!m_lcDatabase.SetItemText (bObjekt ? iRowIndex++ : iIndex, bObjekt ? 1 : iActCol++, strTemp))
			AfxThrowMemoryException ();		

	//	Nullwert erlaubt
		VERIFY (strTemp.LoadString (Info.m_bAllowZeroLength ? IDS_JA : IDS_NEIN));
		if (!m_lcDatabase.SetItemText (bObjekt ? iRowIndex++ : iIndex, bObjekt ? 1 : iActCol++, strTemp))
			AfxThrowMemoryException ();		

	//	Default Value
		if (!m_lcDatabase.SetItemText (bObjekt ? iRowIndex++ : iIndex, bObjekt ? 1 : iActCol++, 
									   Info.m_strDefaultValue))
			AfxThrowMemoryException ();		

	//	Name der Tabelle
		if (!m_lcDatabase.SetItemText (bObjekt ? iRowIndex++ : iIndex, bObjekt ? 1 : iActCol++, strTableName))
			AfxThrowMemoryException ();			

	//	Gültigkeitsregel
		if (!m_lcDatabase.SetItemText (bObjekt ? iRowIndex++ : iIndex, bObjekt ? 1 : iActCol++, 
									   Info.m_strValidationRule))
			AfxThrowMemoryException ();		
		
	//	Gültigkeitstext
		if (!m_lcDatabase.SetItemText (bObjekt ? iRowIndex++ : iIndex, bObjekt ? 1 : iActCol++, 
									   Info.m_strValidationText))
			AfxThrowMemoryException ();		

	//	Fremdname
		/*
		if (!m_lcDatabase.SetItemText (bObjekt ? iRowIndex++ : iIndex, bObjekt ? 1 : iActCol++, 
									   Info.m_strForeignName))
			AfxThrowMemoryException ();		
		*/
	}

	if (TableDef.IsOpen ())
		TableDef.Close ();
}

void CStatistikDialog::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);

	if ((SIZE_MAXIMIZED == nType) || (SIZE_RESTORED == nType))
	{
		// TODO: Add your message handler code here
		if (m_trDatabase.m_hWnd)
			m_trDatabase.MoveWindow (0, 0, cx / 4, cy);

		if (m_lcDatabase.m_hWnd)
			m_lcDatabase.MoveWindow (cx / 4, 0, cx * 3 / 4, cy);
	}
}

/*
BOOL CStatistikDialog::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	// TODO: Add your message handler code here and/or call default
	// return CDialog::OnHelpInfo(pHelpInfo);
	ASSERT    (pHelpInfo != NULL);

	if (pHelpInfo -> dwContextId)
		WinHelp (pHelpInfo -> dwContextId, HELP_CONTEXTPOPUP);

	return TRUE;
}
*/

