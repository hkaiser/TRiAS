// FeldInfoDialog.cpp : implementation file
//

#include "pheader.h"		// vorübersetzter Header
#include "odbcext.hr"		// Resource-Konstanten

#include <hpp/columnst.hpp>		// CColumnStatus
#include <hpp/collist.hpp>		// CColumnObjArray
#include <hpp/fieldinf.hpp>		// CFeldInfExt

#include "feldin32.hpp"		// zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFeldInfoDialog dialog
CFeldInfoDialog::CFeldInfoDialog(CWnd* pParent, CColumnObjArray *pCA)
	: CDialog(CFeldInfoDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFeldInfoDialog)
		// NOTE: the ClassWizard will add member initialization here
	m_bResult = FALSE;			// noch nichts getan		
	m_pCA = NULL;
	//}}AFX_DATA_INIT

	//	prüfe Parameter
	if (!pParent || !pCA || !pCA -> Count ())
	{
		DEX_Error (RC_ctCFeldInfo, EC_ILLPARS);
		return;
	}	         

	m_sNameSort = m_sTypeSort = m_sLenSort = NotSorted;
	
	m_pCA = pCA;				// Zeiger speichern
	m_bResult = TRUE;			// alles OK
}

void CFeldInfoDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFeldInfoDialog)
	DDX_Control(pDX, IDL_FIELDINFO, m_lcFeldInfo);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFeldInfoDialog, CDialog)
	//{{AFX_MSG_MAP(CFeldInfoDialog)
	ON_WM_DESTROY()
	ON_NOTIFY(LVN_COLUMNCLICK, IDL_FIELDINFO, OnColumnclickFieldInfo)
	ON_WM_SIZE()
	ON_NOTIFY(LVN_DELETEITEM, IDL_FIELDINFO, OnDeleteitemFieldinfo)
	ON_NOTIFY(NM_CLICK, IDL_FIELDINFO, OnClickFieldinfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFeldInfoDialog message handlers

void CFeldInfoDialog::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if (m_lcFeldInfo.m_hWnd && m_lcFeldInfo.IsWindowVisible ())      	
		m_lcFeldInfo.MoveWindow (0, 0, cx, cy);
}

void CFeldInfoDialog::OnDestroy() 
{
	CDialog::OnDestroy();
	
//	TODO: Add your message handler code here
	if (m_lcFeldInfo.GetItemCount () > 0)
		m_lcFeldInfo.DeleteAllItems ();  		
}

//	Sortierung gewünscht
void CFeldInfoDialog::OnColumnclickFieldInfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
//	TODO: Add your control notification handler code here

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
	m_lcFeldInfo.SortItems (CompareFelderFunction, sAttr);
	
	*pResult = 0;
}

BOOL CFeldInfoDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
//	TODO: Add extra initialization here
	CWaitCursor wc;			// Sanduhr einschalten
	m_bResult = FALSE;		// noch nichts getan

	TRY
	{
		CString strText;

	//	"Name"
		if ((strText.LoadString (IDS_IMP_FELDNAME) == FALSE) ||
			(m_lcFeldInfo.InsertColumn (0, strText) != 0))
			AfxThrowUserException ();		

	//	"Typ"
		if ((strText.LoadString (IDS_IMP_FELDTYP) == FALSE) ||
			(m_lcFeldInfo.InsertColumn (1, strText) != 1))
			AfxThrowUserException ();

	// 	"Länge"
		if ((strText.LoadString (IDS_IMP_FELDLAENGE) == FALSE) ||
			(m_lcFeldInfo.InsertColumn (2, strText) != 2))
			AfxThrowUserException ();								

	//	Spaltenbreiten setzen
		m_lcFeldInfo.SetColumnWidth (0, LVSCW_AUTOSIZE_USEHEADER);		
		m_lcFeldInfo.SetColumnWidth (1, LVSCW_AUTOSIZE_USEHEADER);		
		m_lcFeldInfo.SetColumnWidth (2, LVSCW_AUTOSIZE_USEHEADER);

	//	alle Feldinformationen ausgeben
		CString strMemo;
		CString strVariabel;
		CString strTypeName;
		if (! strMemo.LoadString (IDS_MEMO) || !strVariabel.LoadString (IDS_VARIABEL))
			AfxThrowUserException ();				
		CRing ri (*m_pCA);
		int iIndex = 0;						// aktueller SpaltenIndex
		char szLenBuffer [20] = "";			// Längenpuffer
		CFeldInfExt *pFeldInf = NULL;		// ItemData
		for (ri.First (); ri.Valid (); ri.Next ())
		{
			CColumnObjLock pCO (ri);
			if (! pCO)
				AfxThrowUserException ();

		//	Länge bei Memo ändern ?
			if (strMemo.CompareNoCase (pCO -> SQLTypeName ()) == 0)
			{
				lstrcpy (szLenBuffer, strVariabel);
				pFeldInf = new CFeldInfExt (pCO -> ColName (), pCO -> SQLTypeName (), 0, 
							   (iIndex + 1));				
			}	
			else
			{
				ltoa (pCO -> FieldLen (), szLenBuffer, 10);	// Länge bestimmen	
				pFeldInf = new CFeldInfExt (pCO -> ColName (), pCO -> SQLTypeName (), 
							   pCO -> FieldLen (), (iIndex + 1));
			}				

			if ((m_lcFeldInfo.InsertItem  (iIndex, pCO -> ColName ()) == iIndex) &&
				 m_lcFeldInfo.SetItemText (iIndex, 1, pCO -> SQLTypeName ()) && 
				 m_lcFeldInfo.SetItemText (iIndex, 2, szLenBuffer) &&
				 m_lcFeldInfo.SetItemData (iIndex, (DWORD) pFeldInf))
				iIndex++;
			else
				AfxThrowUserException ();
		}	// end for        
	}
	CATCH (CMemoryException, me)
	{
		DEX_Error (RC_ctCFeldInfo, EC_NOMEMORY);
		return FALSE;
	}
	AND_CATCH (CUserException, me)
	{
		DEX_Error (RC_ctCFeldInfo, EC_SYSERROR);		
		return FALSE;
	}		
	END_CATCH

//	Sortierungsart setzen
	m_sNameSort = SortAsc;
	m_sTypeSort = m_sLenSort = NotSorted;
	m_lcFeldInfo.SortItems (CompareFelderFunction, SortName | m_sNameSort); 																			

	return m_bResult = TRUE;  // return TRUE unless you set the focus to a control
							  // EXCEPTION: OCX Property Pages should return FALSE
}

void CFeldInfoDialog::OnDeleteitemFieldinfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
//	TODO: Add your control notification handler code here

	CFeldInfExt *pFI = (CFeldInfExt *) (pNMListView -> lParam);
	ASSERT (pFI != NULL);
	DELETE_OBJ (pFI);
	
	*pResult = 0;
}

void CFeldInfoDialog::OnClickFieldinfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
//	TODO: Add your control notification handler code here
	TRY
	{
		int iIndex = m_lcFeldInfo.GetNextItem (-1, LVNI_SELECTED);
		if (iIndex >= 0)
		{
			CFeldInfExt *pFI = (CFeldInfExt *) m_lcFeldInfo.GetItemData (iIndex);
			ASSERT (pFI != NULL);
			ASSERT (m_pCA != NULL);
			CString strFormat, strCaption;
			if (!strFormat.LoadString (IDS_FELDINFO_FORMAT))
				AfxThrowUserException ();
			
		//	Caption zusammenbauen
			char *pBuffer = strCaption.GetBuffer (strFormat.GetLength () + 
												  pFI -> m_strName.GetLength () + 30);
			wsprintf (pBuffer, strFormat, (const char *) pFI -> m_strName, 
										  pFI -> m_lExtData, m_pCA -> Count ());
			SetWindowText (pBuffer);
		}
	}
	CATCH (CMemoryException, me)
	{
		DEX_Error (RC_ctCFeldInfo, EC_NOMEMORY);
	}
	AND_CATCH (CUserException, me)
	{
		DEX_Error (RC_ctCFeldInfo, EC_SYSERROR);		
	}		
	END_CATCH	

	*pResult = 0;
}
