// feldpage.cpp : implementation file
//

#include "pheader.h"
#include "odbcext.hr"				// Resource-Konstanten

#include <hpp/columnst.hpp>				// CColumns
#include <hpp/helptext.hpp>				// CHelpText
#include <hpp/waitcur.hpp>				// CWaitCursor
#include <hpp/odbcerr.hpp>				// OdbcError
#include <hpp/getodbci.hpp>				// COdbcInfos

#include "importpa.hpp"				// CImportParams
#include "feldpage.hpp"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

enum SortType { SortName = 1, SortType = 2, SortLen = 4, SortAsc = 8, SortDesc = 16, NotSorted = 32};

// externe Variablen
extern CImportParams *g_pCParams;		// Parameterfeld

//	lokale Variablen
static CFeldInformTree *pFeldTree = NULL;	

//	globale Funktionen
void* __export GetFeldInform (void *pObj)
{
	return &(((CFeldInform *) pObj) -> m_lId);
}

int __export CompareFeldInform (void *pl1, void *pl2)
{
	return *(long *)pl1 - *(long *)pl2;
}

int __export CALLBACK CompareFeldFunction (LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	ASSERT (pFeldTree != NULL);

	const char *pT1 = NULL;
	const char *pT2 = NULL;

	if (lParamSort & SortName || lParamSort & SortType)
	{
		if (lParamSort & SortName)
		{
			pT1 = pFeldTree -> GetFeldName ((long) lParam1);
			pT2 = pFeldTree ->GetFeldName ((long) lParam2);
		}
		else
		{
			pT1 = pFeldTree ->GetFeldType ((long) lParam1);
			pT2 = pFeldTree ->GetFeldType ((long) lParam2);
		}

	//	prüfe Parameter
		ASSERT (pT1 != NULL && AfxIsValidString (pT1));
		ASSERT (pT2 != NULL && AfxIsValidString (pT2));		
		if (lParamSort & SortAsc)			
			return strcmpi (pT1, pT2);		// aufsteigende Sortierung
		else
			return strcmpi (pT2, pT1);		// absteigende Sortierung				
	}
	else 	// sortiere nach Länge
	{
		long l1 = pFeldTree ->GetFeldLen ((long) lParam1);		
		long l2 = pFeldTree ->GetFeldLen ((long) lParam2);		
		if (lParamSort & SortAsc)
			return l1 - l2;
		else
			return l2 - l1;
	}		
}

// CFeldInform --------------------------------------------------------------
CFeldInform :: CFeldInform (long lId, long lLen, const char *pName, const char *pType)
{
//	hier keinerlei Typ-Prüfung
	TRY
	{
		m_lId = lId;
		m_lLen = lLen;
		m_strName = pName;
		m_strType = pType;	
	}
	CATCH (CMemoryException, me)
	{
		THROW_LAST ();
	}
	END_CATCH 
}

// CFeldInformTree ----------------------------------------------------------
CFeldInformTree :: CFeldInformTree (void)
				 : CTree (GetFeldInform, CompareFeldInform)
{
	// nothing to do
}				  	

CFeldInformTree :: ~CFeldInformTree (void)
{
	EveryDelete ();		// alle Einträge löschen
}

void CFeldInformTree :: UserDelete (void *pObj)
{
	((CFeldInform *) pObj) -> ~CFeldInform ();
}

//	Schreibfunktion(en)
BOOL CFeldInformTree :: AddFeldInform (long lId, long lLen, const char *pName, const char *pType)
{
	CTable tb (*this);
	if (tb.Find (&lId))
		return TRUE;	

//	prüfe Parameter vor dem Speichern
	ASSERT (lLen > 0);
	ASSERT (pName != NULL && AfxIsValidString (pName));
	ASSERT (pType != NULL && AfxIsValidString (pType));

//	Feldinfo speichern
	TRY
	{
		CFeldInformCreator Cr (*this);
		ContCreate (Cr, CFeldInform) (lId, lLen, pName, pType);
	}
	CATCH (CMemoryException, me)
	{
		DEX_Error (RC_OdbcImport, EC_NOMEMORY);
		return FALSE;
	}
	END_CATCH

	return TRUE;
}

//	Lese-Funktionen
//	Feldname
const char *CFeldInformTree :: GetFeldName (long lId)
{
	CTable tb (*this);
	if (tb.Find (&lId))
	{
		CFeldInformLock l (tb);
		if (l)
			return l -> Name ();
		else
		{
			DEX_Error (RC_OdbcImport, EC_LOCKERROR);
		}
	}		
	return NULL;
}

//	Feldtyp
const char *CFeldInformTree :: GetFeldType (long lId)
{
	CTable tb (*this);
	if (tb.Find (&lId))
	{
		CFeldInformLock l (tb);
		if (l)
			return l -> Type ();
		else
		{
			DEX_Error (RC_OdbcImport, EC_LOCKERROR);
		}
	}		
	return NULL;
}

//	Feldlänge
long CFeldInformTree :: GetFeldLen (long lId)
{
	CTable tb (*this);
	if (tb.Find (&lId))
	{
		CFeldInformLock l (tb);
		if (l)
			return l -> m_lLen;
		else
		{
			DEX_Error (RC_OdbcImport, EC_LOCKERROR);
		}
	}		
	return NULL;
}

/////////////////////////////////////////////////////////////////////////////
// CFeldPage property page

IMPLEMENT_DYNCREATE(CFeldPage, CPropertyPage)

CFeldPage::CFeldPage() : CPropertyPage(CFeldPage::IDD)
{
	//{{AFX_DATA_IINIT(CFeldPage)
	//}}AFX_DATA_NIT

	m_sKoppNameSort = m_sKoppTypeSort = m_sKoppLenSort = NotSorted;
	m_sRechtsNameSort = m_sRechtsTypeSort = m_sRechtsLenSort = NotSorted;
	m_sHochNameSort = m_sHochTypeSort = m_sHochLenSort = NotSorted;

	pFeldTree = &m_FeldTree;
}

CFeldPage::~CFeldPage()
{
}

void CFeldPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFeldPage)
	DDX_Control(pDX, IDL_FELD_RECHTSW, m_lcRechtsWert);
	DDX_Control(pDX, IDL_FELD_KOPPEL, m_lcKoppelFeld);
	DDX_Control(pDX, IDL_FELD_HOCHW, m_lcHochWert);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFeldPage, CPropertyPage)
	//{{AFX_MSG_MAP(CFeldPage)
	ON_NOTIFY(LVN_COLUMNCLICK, IDL_FELD_RECHTSW, OnColumnclickFeldRechtsw)
	ON_NOTIFY(LVN_COLUMNCLICK, IDL_FELD_KOPPEL, OnColumnclickFeldKoppel)
	ON_NOTIFY(LVN_COLUMNCLICK, IDL_FELD_HOCHW, OnColumnclickFeldHochw)
	ON_NOTIFY(NM_CLICK, IDL_FELD_RECHTSW, OnClickFeldRechtsw)
	ON_NOTIFY(NM_CLICK, IDL_FELD_KOPPEL, OnClickFeldKoppel)
	ON_NOTIFY(NM_CLICK, IDL_FELD_HOCHW, OnClickFeldHochw)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CFeldPage message handlers
void CFeldPage::OnColumnclickFeldRechtsw(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
// 	TODO: Add your control notification handler code here

	ASSERT (pNMListView != NULL);

	short sAttr = 0;
	if (pNMListView -> iSubItem == 0)		// Feldnamen sortieren
	{
		sAttr = SortName;			
		if ((m_sRechtsNameSort == SortDesc) || (m_sRechtsNameSort == NotSorted))
			sAttr |= (m_sRechtsNameSort = SortAsc);
		else
			sAttr |= (m_sRechtsNameSort = SortDesc);
	}
	else									
	{										
		if (pNMListView -> iSubItem == 1)	// Feldtypen sortieren
		{
			sAttr = SortType;
			if ((m_sRechtsTypeSort == SortDesc) || (m_sRechtsTypeSort == NotSorted))
				sAttr |= (m_sRechtsTypeSort = SortAsc);
			else
				sAttr |= (m_sRechtsTypeSort = SortDesc);
		}
		else
		{
	 		sAttr = SortLen;				// Feldlängen sortieren
			if ((m_sRechtsLenSort == SortDesc) || (m_sRechtsLenSort == NotSorted))
				sAttr |= (m_sRechtsLenSort = SortAsc);
			else
				sAttr |= (m_sRechtsLenSort = SortDesc);
		}
	}

	CWaitCursor wc;
	m_lcRechtsWert.SortItems (CompareFeldFunction, sAttr);
	
	*pResult = 0;
}

void CFeldPage::OnColumnclickFeldKoppel(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
// 	TODO: Add your control notification handler code here

	ASSERT (pNMListView != NULL);

	short sAttr = 0;
	if (pNMListView -> iSubItem == 0)		// Feldnamen sortieren
	{
		sAttr = SortName;			
		if ((m_sKoppNameSort == SortDesc) || (m_sKoppNameSort == NotSorted))
			sAttr |= (m_sKoppNameSort = SortAsc);
		else
			sAttr |= (m_sKoppNameSort = SortDesc);
	}
	else									
	{										
		if (pNMListView -> iSubItem == 1)	// Feldtypen sortieren
		{
			sAttr = SortType;
			if ((m_sKoppTypeSort == SortDesc) || (m_sKoppTypeSort == NotSorted))
				sAttr |= (m_sKoppTypeSort = SortAsc);
			else
				sAttr |= (m_sKoppTypeSort = SortDesc);
		}
		else
		{
	 		sAttr = SortLen;				// Feldlängen sortieren
			if ((m_sKoppLenSort == SortDesc) || (m_sKoppLenSort == NotSorted))
				sAttr |= (m_sKoppLenSort = SortAsc);
			else
				sAttr |= (m_sKoppLenSort = SortDesc);
		}
	}

	CWaitCursor wc;
	m_lcKoppelFeld.SortItems (CompareFeldFunction, sAttr);

	*pResult = 0;
}

void CFeldPage::OnColumnclickFeldHochw(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
// 	TODO: Add your control notification handler code here

	ASSERT (pNMListView != NULL);

	short sAttr = 0;
	if (pNMListView -> iSubItem == 0)		// Feldnamen sortieren
	{
		sAttr = SortName;			
		if ((m_sHochNameSort == SortDesc) || (m_sHochNameSort == NotSorted))
			sAttr |= (m_sHochNameSort = SortAsc);
		else
			sAttr |= (m_sHochNameSort = SortDesc);
	}
	else									
	{										
		if (pNMListView -> iSubItem == 1)	// Feldtypen sortieren
		{
			sAttr = SortType;
			if ((m_sHochTypeSort == SortDesc) || (m_sHochTypeSort == NotSorted))
				sAttr |= (m_sHochTypeSort = SortAsc);
			else
				sAttr |= (m_sHochTypeSort = SortDesc);
		}
		else
		{
	 		sAttr = SortLen;				// Feldlängen sortieren
			if ((m_sHochLenSort == SortDesc) || (m_sHochLenSort == NotSorted))
				sAttr |= (m_sHochLenSort = SortAsc);
			else
				sAttr |= (m_sHochLenSort = SortDesc);
		}
	}

	CWaitCursor wc;
	m_lcHochWert.SortItems (CompareFeldFunction, sAttr);
	
	*pResult = 0;
}

void CFeldPage::OnClickFeldRechtsw(NMHDR* pNMHDR, LRESULT* pResult) 
{
// 	TODO: Add your control notification handler code here
	SetOkButton ();
	
	*pResult = 0;
}

void CFeldPage::OnClickFeldKoppel(NMHDR* pNMHDR, LRESULT* pResult) 
{
// 	TODO: Add your control notification handler code here
	SetOkButton ();
	
	*pResult = 0;
}

void CFeldPage::OnClickFeldHochw(NMHDR* pNMHDR, LRESULT* pResult) 
{
// 	TODO: Add your control notification handler code here
	SetOkButton ();
	
	*pResult = 0;
}

void CFeldPage::OnDestroy() 
{
	CPropertyPage::OnDestroy();
	
// 	TODO: Add your message handler code here
	if (m_lcKoppelFeld.GetItemCount () > 0)
		m_lcKoppelFeld.DeleteAllItems ();  	
	if (m_lcRechtsWert.GetItemCount () > 0)
		m_lcRechtsWert.DeleteAllItems ();
	if (m_lcHochWert.GetItemCount () > 0)
		m_lcHochWert.DeleteAllItems ();
}

BOOL CFeldPage::ReadParams (void)
{
//	prüfe globale Parameter
	ASSERT (g_pCParams != NULL);

	TRY
	{
	//	hat sich DataSource oder Tabelle geändert ?
		if (m_strDataSource == g_pCParams -> m_strDataSource &&
			m_strTableName == g_pCParams -> m_strTableName)
			return TRUE;		// alles bleibt beim alten

		CWaitCursor wc;				// Sanduhr einschalten
	
	//	neuen Werte merken
		m_strDataSource = g_pCParams -> m_strDataSource;
		m_strTableName = g_pCParams -> m_strTableName;

		if (m_lcKoppelFeld.GetItemCount () > 0)
			m_lcKoppelFeld.DeleteAllItems ();
		if (m_lcRechtsWert.GetItemCount () > 0)
			m_lcRechtsWert.DeleteAllItems ();
		if (m_lcHochWert.GetItemCount () > 0)
			m_lcHochWert.DeleteAllItems ();
	
	//	FeldInformBaum leeren
		if (m_FeldTree.Count () > 0)
			m_FeldTree.EveryDelete ();

	//	mögliche Koppel-und Koordinatenfelder ausgeben
		ASSERT (g_pCParams -> m_COdbcInfos.m_pDataBase != NULL);
		ASSERT (g_pCParams -> m_strTableName.GetLength () > 0);

		CColumns Col ((CDatabase *) g_pCParams -> m_COdbcInfos.m_pDataBase);
		Col.m_strTableNameParam = g_pCParams -> m_strTableName;    // Namen für ODBC speichern
		int iKI = 0;					// Koppelfeld-Index
		int iKK = 0;					// Index-Koordinaten-Felder
		long lItemData = 0;				// ItemData
		char szLenBuffer [20] = "";		// Längenpuffer
		BOOL bIsKoordField = FALSE;		// KoordFeld-Flag
		BOOL bIsKoppelField = FALSE;	// Koppelfeld-Flag
		if (Col.Open ())				// Set öffnen
		{   
			while (! Col.IsEOF ())
			{   
				lItemData++;							// Feldzähler erhöhen
				ltoa (Col.m_lLength, szLenBuffer, 10);	// Länge immer bestimmen

			//	ist dieses Feld ein Koordinatenfeld ?				
				if (Col.IsKoordField ())
				{
				//	Feldinfos ausgeben
					bIsKoordField = TRUE;
					if ((m_lcHochWert.InsertItem (iKK, Col.m_strColumnName) == iKK) &&
					 	m_lcHochWert.SetItemText (iKK, 1, (char*)(const char*)Col.m_strTypeName) && 
					 	m_lcHochWert.SetItemText (iKK, 2, szLenBuffer) &&
						m_lcHochWert.SetItemData (iKK, lItemData))
					{
						if ((m_lcRechtsWert.InsertItem (iKK, Col.m_strColumnName) == iKK) &&
					 		 m_lcRechtsWert.SetItemText (iKK, 1, (char*)(const char*)Col.m_strTypeName) && 
					 		 m_lcRechtsWert.SetItemText (iKK, 2, szLenBuffer) &&						
							 m_lcRechtsWert.SetItemData (iKK, lItemData))	
							iKK++;
						else
							AfxThrowUserException ();
					}
					else
						AfxThrowUserException ();
				}
				else
					bIsKoordField = FALSE;

			// 	ist dieses Feld ein Koppelfeld ?
				if (bIsKoordField || Col.IsKoppelField ())	// Koord~ sind i.a. auch Koppelfelder
				{
				// 	FeldInfos ausgeben
					bIsKoppelField = TRUE;
				   	if ((m_lcKoppelFeld.InsertItem (iKI, Col.m_strColumnName) == iKI) &&
					 	m_lcKoppelFeld.SetItemText (iKI, 1, (char*)(const char *)Col.m_strTypeName) && 
					 	m_lcKoppelFeld.SetItemText (iKI, 2, szLenBuffer) &&
						m_lcKoppelFeld.SetItemData (iKI, lItemData))
						iKI++;
					else
						AfxThrowUserException ();
				}
				else
					bIsKoppelField = FALSE;
					
			//	FeldInformationen ggf.speichern
				if (bIsKoordField || bIsKoppelField)
				{
					if (! m_FeldTree.AddFeldInform (lItemData, Col.m_lLength, Col.m_strColumnName, 
																		   Col.m_strTypeName))
						AfxThrowUserException ();
				}
										
				Col.MoveNext ();		// zum nächsten Feld
			}	// end_while
		}
		else
		{
			DEX_Error (RC_OdbcImport, EC_NOOPENDSN);
			return FALSE;
		}
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

// 	entarteten Baum optimieren	
	m_FeldTree.Optimize ();		

//	Sortierung nach Feldnamen durchführen
	m_sKoppTypeSort = m_sKoppLenSort = NotSorted;
	m_sRechtsTypeSort = m_sRechtsLenSort = NotSorted;
	m_sHochTypeSort = m_sHochLenSort = NotSorted;

	m_sHochNameSort = m_sRechtsNameSort = m_sKoppNameSort = SortAsc;
	m_lcKoppelFeld.SortItems (CompareFeldFunction, SortName | m_sKoppNameSort);	
	m_lcRechtsWert.SortItems (CompareFeldFunction, SortName | m_sRechtsNameSort);	
	m_lcHochWert.SortItems (CompareFeldFunction, SortName | m_sHochNameSort);	

//	Selektion setzen
	LV_FINDINFO fi;
	memset (&fi, 0, sizeof (fi));
	fi.flags = LVFI_STRING;		

//	Koppelfeld	
	short iCnt = -1;
	fi.psz = g_pCParams -> m_strKoppelFeld;
	if (!g_pCParams -> m_strKoppelFeld.IsEmpty ())
		iCnt = m_lcKoppelFeld.FindItem (&fi);
	m_lcKoppelFeld.SetItemState (iCnt, LVIS_SELECTED, LVIS_SELECTED);
	m_lcKoppelFeld.EnsureVisible (iCnt, FALSE);

//	RechtsWert
	iCnt = -1;
	fi.psz = g_pCParams -> m_strRechtsWert;
	if (!g_pCParams -> m_strRechtsWert.IsEmpty ())
		iCnt = m_lcRechtsWert.FindItem (&fi);
	m_lcRechtsWert.SetItemState (iCnt, LVIS_SELECTED, LVIS_SELECTED);
	m_lcRechtsWert.EnsureVisible (iCnt, FALSE);

//	Hochwert
	iCnt = -1;
	fi.psz = g_pCParams -> m_strHochWert;
	if (!g_pCParams -> m_strHochWert.IsEmpty ())
		iCnt = m_lcHochWert.FindItem (&fi);
	m_lcHochWert.SetItemState (iCnt, LVIS_SELECTED, LVIS_SELECTED);
	m_lcHochWert.EnsureVisible (iCnt, FALSE);

	return TRUE;
}

//	Ok-Button aktivieren/deaktivieren
void CFeldPage :: SetOkButton (void)
{
	ASSERT (g_pCParams != NULL);

	if ((m_lcKoppelFeld.GetSelectedCount() > 0) && 
		(m_lcHochWert.GetSelectedCount() > 0) &&
		(m_lcRechtsWert.GetSelectedCount() > 0))
	{
	//	prüfe ob Felder verschieden sind
		long lIK = (long) m_lcKoppelFeld.GetItemData (m_lcKoppelFeld.GetNextItem (-1, LVNI_SELECTED));
		long lIR = (long) m_lcRechtsWert.GetItemData (m_lcRechtsWert.GetNextItem (-1, LVNI_SELECTED));
		long lIH = (long) m_lcHochWert.GetItemData (m_lcHochWert.GetNextItem (-1, LVNI_SELECTED));
		const char *pT1 = m_FeldTree.GetFeldName (lIK);
		const char *pT2 = m_FeldTree.GetFeldName (lIR);
		const char *pT3 = m_FeldTree.GetFeldName (lIH);

	//	prüfe erhaltene Parameter
		ASSERT (pT1 != NULL && AfxIsValidString (pT1));
		ASSERT (pT2 != NULL && AfxIsValidString (pT2));
		ASSERT (pT3 != NULL && AfxIsValidString (pT3));

	//	sind alle Felder verschieden voneinander ?
		if (strcmp (pT1, pT2) && strcmp (pT1, pT3) && strcmp (pT2, pT3))
		{
#ifdef WIN32
			GetParent () -> SetWizardButtons (PSWIZB_NEXT | PSWIZB_BACK);
#else		
			g_pCParams -> OkEnable (Felder);				
#endif
			return;
		}
	}

#ifdef WIN32
	GetParent () -> SetWizardButtons (PSWIZB_BACK);	
#else
	g_pCParams -> OkDisable (Felder);			
#endif
}

// Nutzereingaben lesen
BOOL CFeldPage :: GetUserEntries (BOOL bGet)	
{
	ASSERT (g_pCParams != NULL);

//	Parameter löschen
	g_pCParams -> m_strKoppelFeld.Empty ();
	g_pCParams -> m_strRechtsWert.Empty ();
	g_pCParams -> m_strHochWert.Empty ();
	if (!bGet)
		return TRUE;		// nur Infos löschen
	
	TRY
	{
	//	lese Koppelfeldname
		int iIndex = m_lcKoppelFeld.GetNextItem (-1, LVNI_SELECTED);		
		const char *pFeld = NULL;
		if (iIndex >= 0)
		{
			pFeld = m_FeldTree.GetFeldName (m_lcKoppelFeld.GetItemData (iIndex));
			ASSERT (pFeld != NULL);						// das sollte nicht passieren
			if (pFeld)
				g_pCParams -> m_strKoppelFeld = pFeld;
		}

	//	lese Rechtswert-Feldname
		iIndex = m_lcRechtsWert.GetNextItem (-1, LVNI_SELECTED);		
		pFeld = NULL;
		if (iIndex >= 0)
		{
			pFeld = m_FeldTree.GetFeldName (m_lcRechtsWert.GetItemData (iIndex));
			ASSERT (pFeld != NULL);						// das sollte nicht passieren
			if (pFeld)
				g_pCParams -> m_strRechtsWert = pFeld;
		}
	
	//	lese Hochwert-Feldname
		iIndex = m_lcHochWert.GetNextItem (-1, LVNI_SELECTED);		
		pFeld = NULL;
		if (iIndex >= 0)
		{
			pFeld = m_FeldTree.GetFeldName (m_lcHochWert.GetItemData (iIndex));
			ASSERT (pFeld != NULL);						// das sollte nicht passieren
			if (pFeld)
				g_pCParams -> m_strHochWert = pFeld;
		}
	}
	CATCH (CMemoryException, me)
	{
		DEX_Error (RC_OdbcImport, EC_NOMEMORY);
		return FALSE;
	}
	END_CATCH		
	
	return TRUE;	
}

BOOL CFeldPage::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	if (!ReadParams ())
	{
		GetParent () -> EndDialog (IDCANCEL);
		return FALSE;
	}

	SetOkButton ();

//	Controls akt./deakt.
	m_lcRechtsWert.EnableWindow (m_lcRechtsWert.GetItemCount () > 0 ? TRUE : FALSE);
	m_lcHochWert.EnableWindow (m_lcHochWert.GetItemCount () > 0 ? TRUE : FALSE);
	m_lcRechtsWert.EnableWindow (m_lcRechtsWert.GetItemCount () > 0 ? TRUE : FALSE);

	UpdateWindow ();
	
	return CPropertyPage::OnSetActive();
}

void CFeldPage::OnCancel() 
{
	// TODO: Add your specialized code here and/or call the base class
	GetUserEntries (FALSE);
	
	CPropertyPage::OnCancel();
}

LRESULT CFeldPage::OnWizardNext() 
{
	// TODO: Add your specialized code here and/or call the base class
	GetUserEntries (TRUE);
	
	return CPropertyPage::OnWizardNext();
}

LRESULT CFeldPage::OnWizardBack() 
{
	// TODO: Add your specialized code here and/or call the base class
	GetUserEntries (TRUE);

	return CPropertyPage::OnWizardBack();
}

BOOL CFeldPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	BOOL bOk = FALSE;
	
//	TODO: Add extra initialization here
	TRY
	{
	//	ListControls init.: "Name"
		CString strText;
		if ((strText.LoadString (IDS_IMP_FELDNAME) == FALSE) ||
			(m_lcKoppelFeld.InsertColumn (0, strText) != 0) ||
			(m_lcRechtsWert.InsertColumn (0, strText) != 0) ||
			(m_lcHochWert.InsertColumn (0, strText) != 0))
			AfxThrowUserException ();

	//	"Typ"
		if ((strText.LoadString (IDS_IMP_FELDTYP) == FALSE) ||
			(m_lcKoppelFeld.InsertColumn (1, strText) != 1) ||
			(m_lcRechtsWert.InsertColumn (1, strText) != 1) ||
			(m_lcHochWert.InsertColumn (1, strText) != 1))
			AfxThrowUserException ();

	// 	"Länge"
		if ((strText.LoadString (IDS_IMP_FELDLAENGE) == FALSE) ||
			(m_lcKoppelFeld.InsertColumn (2, strText) != 2) ||
			(m_lcRechtsWert.InsertColumn (2, strText) != 2) ||
			(m_lcHochWert.InsertColumn (2, strText) != 2))
			AfxThrowUserException ();					

	//	Spaltenbreiten setzen
		m_lcKoppelFeld.SetColumnWidth (0, LVSCW_AUTOSIZE_USEHEADER);		
		m_lcKoppelFeld.SetColumnWidth (1, LVSCW_AUTOSIZE_USEHEADER);		
		m_lcKoppelFeld.SetColumnWidth (2, LVSCW_AUTOSIZE_USEHEADER);		

		m_lcRechtsWert.SetColumnWidth (0, LVSCW_AUTOSIZE_USEHEADER);	
		m_lcRechtsWert.SetColumnWidth (1, LVSCW_AUTOSIZE_USEHEADER);
		m_lcRechtsWert.SetColumnWidth (2, LVSCW_AUTOSIZE_USEHEADER);	

		m_lcHochWert.SetColumnWidth (0, LVSCW_AUTOSIZE_USEHEADER);
		m_lcHochWert.SetColumnWidth (1, LVSCW_AUTOSIZE_USEHEADER);
		m_lcHochWert.SetColumnWidth (2, LVSCW_AUTOSIZE_USEHEADER);

	//	Selektion "beibehalten" setzen
		long lAttr = :: GetWindowLong (m_lcKoppelFeld.m_hWnd, GWL_STYLE);
		:: SetWindowLong (m_lcKoppelFeld.m_hWnd, GWL_STYLE, lAttr | LVS_SHOWSELALWAYS);

		lAttr = :: GetWindowLong (m_lcHochWert.m_hWnd, GWL_STYLE);
		:: SetWindowLong (m_lcHochWert.m_hWnd, GWL_STYLE, lAttr | LVS_SHOWSELALWAYS);

		lAttr = :: GetWindowLong (m_lcRechtsWert.m_hWnd, GWL_STYLE);
		:: SetWindowLong (m_lcRechtsWert.m_hWnd, GWL_STYLE, lAttr | LVS_SHOWSELALWAYS);						
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
		GetParent () -> EndDialog (IDCANCEL);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
