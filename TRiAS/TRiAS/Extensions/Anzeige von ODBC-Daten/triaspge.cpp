// triaspge.cpp : implementation file
//

#include "pheader.h"
#include "odbcext.hr"

#include <hpp/objinfo.hpp>			// FillMerkm..
#include <hpp/waitcur.hpp>			// CWaitCursor
#include <hpp/helptext.hpp>			// CHelpText
#include <hpp/getodbci.hpp>			// COdbcInfos

#include "importpa.hpp"			// CImportParams 
#include "triaspge.hpp"
	
#include "fakename.h"			// den Namen der App dynamisch anpassen

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// externe Variablen
extern CImportParams *g_pCParams;		// Parameterfeld

//	globale Sortier-Funktion und Enumerators
enum ParamSort { SortText = 1, SortKode = 2, SortAsc = 4, SortDesc = 8 , NotSorted = 16};

int __export CALLBACK CompareFunction (LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	ASSERT ((lParam1 != 0) && (lParam2 != 0));

	CObjektInfo *pOi1 = (CObjektInfo *) lParam1;
	CObjektInfo *pOi2 = (CObjektInfo *) lParam2;

//	prüfe Parameter
	ASSERT ((pOi1 != NULL) && (pOi2 != NULL));
	ASSERT ((pOi1 -> m_ulKode > 0) && (pOi2 -> m_ulKode > 0));

	if (lParamSort & SortText)		// Text sortieren
	{
		if (lParamSort & SortAsc)		  // aufsteigend
			return strcmpi ((const char *) pOi1 -> m_strDescr, (const char *) pOi2 -> m_strDescr);
		else							 // absteigend
			return strcmpi ((const char *) pOi2 -> m_strDescr, (const char *) pOi1 -> m_strDescr);			
	}
	else		// Kodes sortieren
	{
		if (lParamSort & SortAsc)		  // aufsteigend
			return (pOi1 -> m_ulKode - pOi2 -> m_ulKode);
		else							  // absteigend
			return (pOi2 -> m_ulKode - pOi1 -> m_ulKode);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTriasPage property page

IMPLEMENT_DYNCREATE(CTriasPage, CPropertyPage)

CTriasPage::CTriasPage() : CPropertyPage(CTriasPage::IDD)
{
        //{{AFX_DATA_INIT(CTriasPage)
	//}}AFX_DATA_INIT
//	Sortierungsart setzen 
	m_sSortIdKode = m_sSortIdDescr = m_sSortMerkmKode = m_sSortMerkmDescr = NotSorted;
}

CTriasPage::~CTriasPage()
{
}

void CTriasPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
        //{{AFX_DATA_MAP(CTriasPage)
	DDX_Control(pDX, IDL_OBJ_MERKM_LIST, m_lvObjektMerkmale);
	DDX_Control(pDX, IDL_IMP_OBJ_KLASSEN, m_lvObjektKlassen);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTriasPage, CPropertyPage)
        //{{AFX_MSG_MAP(CTriasPage)
	ON_NOTIFY(LVN_COLUMNCLICK, IDL_IMP_OBJ_KLASSEN, OnColumnclickObjKlList)
	ON_NOTIFY(LVN_COLUMNCLICK, IDL_OBJ_MERKM_LIST, OnColumnclickObjMerkmList)
	ON_NOTIFY(LVN_DELETEITEM, IDL_IMP_OBJ_KLASSEN, OnDeleteItemObjektKlassen)
	ON_NOTIFY(LVN_DELETEITEM, IDL_OBJ_MERKM_LIST, OnDeleteItemObjektMerkmal)
	ON_NOTIFY(NM_CLICK, IDL_OBJ_MERKM_LIST, OnClickObjektMerkmale)
	ON_NOTIFY(NM_CLICK, IDL_IMP_OBJ_KLASSEN, OnClickObjektKlassen)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CTriasPage message handlers
BOOL CTriasPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	FakeName(this);	// den TRiASNamen ändern
	
BOOL bRet = FALSE;
	
	TRY {
	// Column-Namen lesen
	CWaitCursor wc;
	CString strDescr, strIdent;

		if (! strDescr.LoadString (IDS_BESCREIBUNG) || ! strIdent.LoadString (IDS_IDENT) ||
		    (m_lvObjektKlassen.InsertColumn (0, strDescr) != 0) ||
			(m_lvObjektKlassen.InsertColumn (1, strIdent) != 1))
		{
			AfxThrowUserException ();
		}

	//	Spalten-Breiten einstellen
		m_lvObjektKlassen.SetColumnWidth (0, LVSCW_AUTOSIZE_USEHEADER);
		m_lvObjektKlassen.SetColumnWidth (1, LVSCW_AUTOSIZE_USEHEADER);	

		if (DEX_GetOpenConnectionCount (QDCAllOpen) > 1) {
		CString strConn;

			if (!strConn.LoadString(IDS_CONNECTION) || 2 != m_lvObjektKlassen.InsertColumn (2, strConn))
				AfxThrowUserException ();
			m_lvObjektKlassen.SetColumnWidth (2, LVSCW_AUTOSIZE_USEHEADER);	
		}

	//	Objektklassen ausgeben
	ENUMLONGKEY ELK;	// Struktur für Enumeration mit einem long-Key
	
		memset (&ELK, 0, sizeof (ELK));
		ELK.eKey = 'i';								// Suchschlüssel (Identifikator)
		ELK.eFcn = (ENUMLONGKEYPROC) FillObjMerkmalListView;	// zu rufende Funktion 
	
	ObjMerkmalInfo oi;
	
		oi.m_lType = ELK.eKey;
		oi.m_pCListCtrl = &m_lvObjektKlassen;
		ELK.ePtr = (void*) &oi;								// durchgereichte Daten
	
		if (! DEX_EnumPBDData (ELK))
		{
			DEX_Error (RC_OdbcImport, EC_ILLPARS);	// keine Okjektklassen gefunden				
			TRACE0 ("ODBC-ABGLEICH: Fehler beim enumerieren der Objektklassen-Beschr. !\n");
			return FALSE;
		}
				
	//	Selektion "beibehalten" setzen
		m_lvObjektKlassen.ModifyStyle (0L, LVS_SHOWSELALWAYS, 0);

	// new for 'Nashville' (#HK960823)
#if defined(ListView_GetExtendedListViewStyle)
		if (IsWin40()) 
			m_lvObjektKlassen.ModifyStyleEx (0L, LVS_EX_FULLROWSELECT|LVS_EX_HEADERDRAGDROP, 0);
#endif 

	//	Sortierung nach Beschreibung
		m_sSortIdDescr = SortAsc;
		m_lvObjektKlassen.SortItems (CompareFunction, SortText | m_sSortIdDescr);
		
	//	Spalten-Namen für Objektmerkmale ausgeben
		strIdent.LoadString (IDS_MERKMALKODE);		
		m_lvObjektMerkmale.InsertColumn (0, strDescr);
		m_lvObjektMerkmale.InsertColumn (1, strIdent);

	//	Spaltenbreiten einstellen
		m_lvObjektMerkmale.SetColumnWidth (0, LVSCW_AUTOSIZE_USEHEADER);
		m_lvObjektMerkmale.SetColumnWidth (1, LVSCW_AUTOSIZE_USEHEADER);

	//	alle Merkmals-Beschreibungen ausgeben
		ELK.eKey = 'm';				
		oi.Reset ();										// alles Rücksetzen
		oi.m_lType = ELK.eKey;								// Typ Merkmal
		oi.m_pCListCtrl = &m_lvObjektMerkmale;				// neues CListControl
	
		if (! DEX_EnumPBDData (ELK))
		{
			DEX_Error (RC_OdbcImport, EC_ILLPARS);	// keine Merkmalsbeschr. gefunden				
			TRACE0 ("ODBC-ABGLEICH: Fehler beim enumerieren der Merkmalsbeschreibungen !\n");
			return FALSE;
		}
		
	//	Selektion "beibehalten" setzen
		m_lvObjektMerkmale.ModifyStyle (0L, LVS_SHOWSELALWAYS, 0);

	// new for 'Nashville' (#HK960823)
#if defined(ListView_GetExtendedListViewStyle)
		if (IsWin40()) 
			m_lvObjektMerkmale.ModifyStyleEx (0L, LVS_EX_FULLROWSELECT|LVS_EX_HEADERDRAGDROP, 0);
#endif 

	//	Sortierung nach Beschreibung
		m_sSortMerkmDescr = SortAsc;
		m_lvObjektMerkmale.SortItems (CompareFunction, SortText | m_sSortMerkmDescr);
		UpdateWindow ();
		bRet = TRUE;
	
	} CATCH (CMemoryException, me) {
		DEX_Error (RC_OdbcImport, EC_NOMEMORY);		
	} AND_CATCH (CUserException, ue) {
		DEX_Error (RC_OdbcImport, EC_SYSERROR);
	} END_CATCH

	if (!bRet)
		GetParent () -> EndDialog (IDCANCEL);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTriasPage::OnColumnclickObjKlList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
// 	TODO: Add your control notification handler code here

	short sAttr = 0;
	if (pNMListView -> iSubItem == 0)		// Text sortieren
	{
		sAttr = SortText;			
		if ((m_sSortIdDescr == SortDesc) || (m_sSortIdDescr == NotSorted))
			sAttr |= (m_sSortIdDescr = SortAsc);
		else
			sAttr |= (m_sSortIdDescr = SortDesc);
	}
	else									// Kode sortieren
	{										
	 	sAttr = SortKode;			
		if ((m_sSortIdKode == SortDesc) || (m_sSortIdKode == NotSorted))
			sAttr |= (m_sSortIdKode = SortAsc);
		else
			sAttr |= (m_sSortIdKode = SortDesc);
	}

	CWaitCursor wc;
	m_lvObjektKlassen.SortItems (CompareFunction, sAttr);

	*pResult = 0;
}

void CTriasPage::OnColumnclickObjMerkmList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here

	short sAttr = 0;
	if (pNMListView -> iSubItem == 0)		// Text sortieren
	{
		sAttr = SortText;			
		if ((m_sSortMerkmDescr == SortDesc) || (m_sSortMerkmDescr == NotSorted))
			sAttr |= (m_sSortMerkmDescr = SortAsc);
		else
			sAttr |= (m_sSortMerkmDescr = SortDesc);
	}
	else									// Kode sortieren
	{										
	 	sAttr = SortKode;			
		if ((m_sSortMerkmKode == SortDesc) || (m_sSortMerkmKode == NotSorted))
			sAttr |= (m_sSortMerkmKode = SortAsc);
		else
			sAttr |= (m_sSortMerkmKode = SortDesc);
	}

	CWaitCursor wc;
	m_lvObjektMerkmale.SortItems (CompareFunction, sAttr);

	*pResult = 0;
}

void CTriasPage::OnDeleteItemObjektKlassen(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here

	CObjektInfo *pOi = (CObjektInfo *) (pNMListView -> lParam);
	ASSERT (pOi != NULL);
	DELETE_OBJ (pOi);

	*pResult = 0;
}

void CTriasPage::OnDeleteItemObjektMerkmal(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here

	CObjektInfo *pOi = (CObjektInfo *) (pNMListView -> lParam);
	ASSERT (pOi != NULL);
	DELETE_OBJ (pOi);
	
	*pResult = 0;
}

void CTriasPage::OnClickObjektKlassen(NMHDR* pNMHDR, LRESULT* pResult) 
{
// 	TODO: Add your control notification handler code here
	SetOkButton ();
	
	*pResult = 0;
}

void CTriasPage::OnClickObjektMerkmale(NMHDR* pNMHDR, LRESULT* pResult) 
{
// 	TODO: Add your control notification handler code here
	SetOkButton ();

	*pResult = 0;
}

//	Ok-Button aktivieren/deaktivieren
void CTriasPage :: SetOkButton (void)
{
	if ((m_lvObjektKlassen.GetSelectedCount() > 0) && 
		(m_lvObjektMerkmale.GetSelectedCount() > 0))
		GetParent () -> SetWizardButtons (PSWIZB_NEXT | PSWIZB_BACK);
	else
		GetParent () -> SetWizardButtons (PSWIZB_BACK);
}

void CTriasPage::OnDestroy() 
{
	CPropertyPage::OnDestroy();
	
// 	TODO: Add your message handler code here
	if (m_lvObjektKlassen.GetItemCount ())
		m_lvObjektKlassen.DeleteAllItems ();	
	if (m_lvObjektMerkmale.GetItemCount ())
		m_lvObjektMerkmale.DeleteAllItems ();	
}

// 	Nutzereingaben lesen
BOOL CTriasPage :: GetUserEntries (BOOL bGet)
{
	ASSERT (g_pCParams != NULL);

//	alten Speicher ggf. löschen
	ulong *pObjKl = g_pCParams -> m_pulObjektKlassen;
	DELETE_VEC (pObjKl);
	g_pCParams -> m_pulObjektKlassen = NULL;
	g_pCParams -> m_ulObjektMKode = 0;

//	nur löschen ?
	if (!bGet)
		return TRUE;

	TRY
	{
	//	lese sel. Merkmalskode
		int iIndex = m_lvObjektMerkmale.GetNextItem (-1, LVNI_SELECTED);
		CObjektInfo *pOi = NULL;
		if (iIndex >= 0)
		{
			pOi = (CObjektInfo *) m_lvObjektMerkmale.GetItemData (iIndex); 
			ASSERT (pOi != NULL);			// das sollte nicht passieren
			if (pOi)
			{
				g_pCParams -> m_ulObjektMKode = pOi -> m_ulKode;
				m_lvObjektMerkmale.SetItemState (iIndex, 0, LVIS_SELECTED);
			}
		}			

	//	lese sel. Objektklassen
		UINT uiCnt = m_lvObjektKlassen.GetSelectedCount ();
		if (uiCnt > 0)
		{
		//	neuen Speicher anfordern und init.
			pObjKl = new ulong [uiCnt + 1];		//	letzter ID wird 0
			memset (pObjKl, 0, sizeof (ulong) * (uiCnt + 1));

		//	alle IDs lesen
			iIndex = -1;			// Suche beginnt am Anfang
			for (uint uiIn = 0; uiIn < uiCnt; uiIn++)
			{
			//	lese akt. Index
				iIndex = m_lvObjektKlassen.GetNextItem (iIndex, LVNI_SELECTED);							
				ASSERT (iIndex >= 0);				// muß gültiger Wert sein
			
			//	lese Id
				pOi = (CObjektInfo *) m_lvObjektKlassen.GetItemData (iIndex);			
				ASSERT (pOi != NULL);
				pObjKl [uiIn] = pOi -> m_ulKode;

			//	Selektion zurücksetzen
				m_lvObjektKlassen.SetItemState (iIndex, 0, LVIS_SELECTED);
			}

		//	da alles OK, Liste wird gültig
			g_pCParams -> m_pulObjektKlassen = pObjKl;
		}
	}
	CATCH (CMemoryException, me)
	{
		DELETE_VEC (pObjKl);
		g_pCParams -> m_ulObjektMKode = 0;
		DEX_Error (RC_OdbcImport, EC_NOMEMORY);
		return FALSE;
	}
	END_CATCH

	return TRUE;
}

void CTriasPage::OnCancel() 
{
//	TODO: Add your specialized code here and/or call the base class
	GetUserEntries (FALSE);
	
	CPropertyPage::OnCancel();
}

BOOL CTriasPage::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	if (!ReadParams ())
	{
		GetParent () -> EndDialog (IDCANCEL);
		return FALSE;
	}

	SetOkButton ();
	UpdateWindow ();
	
	return CPropertyPage::OnSetActive();
}

//	lese akt. Parameter
BOOL CTriasPage::ReadParams (void)
{
	ASSERT (g_pCParams != NULL);

	if (g_pCParams -> m_ulObjektMKode > 0)
		SelectItem (m_lvObjektMerkmale, g_pCParams -> m_ulObjektMKode, 'm');

//	selektiere Objektklassen
	for (ulong *pId = g_pCParams -> m_pulObjektKlassen; pId && *pId != 0; pId++)		
		SelectItem (m_lvObjektKlassen, *pId, 'i');

	return TRUE;
}

//	Selektiere Item
BOOL CTriasPage :: SelectItem (CListCtrl &list, ulong ulKode, short sType)
{
//	prüfe Parameter
	ASSERT (ulKode > 0);
	ASSERT (sType == 'i' || sType == 'm');

//	lese zugeh. Kurztext von Trias
	char KurzText [KurzTextLen] = "";
	if (!GetKurzText (ulKode, sType, KurzText, KurzTextLen))
		return FALSE;

//	Suchstruktur init.
	LV_FINDINFO fi;						
	memset (&fi, 0, sizeof (fi));
	fi.flags = LVFI_STRING;
	fi.psz = KurzText;

//	suche Item in ListControl		
	int	iItem = list.FindItem (&fi, -1);
	if (iItem >= 0)
	{
		list.EnsureVisible (iItem, FALSE);
		return list.SetItemState (iItem, LVIS_SELECTED, LVIS_SELECTED);						
	}

	return FALSE;
}

BOOL CTriasPage::OnKillActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	GetUserEntries (TRUE);
	
	return CPropertyPage::OnKillActive();
}
