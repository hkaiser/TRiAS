// triaspge.cpp : implementation file
//

#include "pheader.h"

extern "C" 
{
    #include <xtension.h>   	// TRIAS-Messages
    #include <xtensnx.h>
	#include "odbcext.hr"
}

#include <objinfo.hpp>			// FillMerkm..
#include <waitcur.hpp>			// CWaitCursor
#include <helptext.hpp>			// CHelpText
#include <getodbci.hpp>			// COdbcInfos

#include "importpa.hpp"			// CImportParams 
#include "trs16pge.hpp"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// externe Variablen
extern CImportParams *g_pCParams;		// Parameterfeld
extern int g_sMkBase; 					// Zahlenbasis
extern int g_sIdBase;			
extern CPropertySheetExt *g_pSheet;

/////////////////////////////////////////////////////////////////////////////
// CTriasPage property page

IMPLEMENT_DYNCREATE(CTriasPage, CPropertyPage)

CTriasPage::CTriasPage() : CPropertyPage(CTriasPage::IDD)
{
    //{{AFX_DATA_INIT(CTriasPage)
	//}}AFX_DATA_INIT
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
	ON_LBN_SELCHANGE(IDL_OBJ_MERKM_LIST, OnSelChangeObjektMerkmale)
	ON_LBN_SELCHANGE(IDL_IMP_OBJ_KLASSEN, OnSelChangeObjektKlassen)
	ON_WM_DESTROY()  
	ON_MESSAGE(IDM_SETFOCUS, OnSetFocusToControl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CTriasPage message handlers
BOOL CTriasPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	BOOL bRet = FALSE;
	
// 	TODO: Add extra initialization here
	TRY
	{
		CWaitCursor wc;

	//	Objektklassen ausgeben
		ENUMLONGKEY ELK;	// Struktur für Enumeration mit einem long-Key
		memset (&ELK, 0, sizeof (ELK));
		ELK.eKey = 'i';								// Suchschlüssel (Identifikator)
		ELK.eFcn = (ENUMLONGKEYPROC) FillObjMerkmalList;	// zu rufende Funktion 
		ObjMerkmalInfo oi;
		oi.m_lType = ELK.eKey;
		oi.m_pCListBox = &m_lvObjektKlassen;
		ELK.ePtr = (void*) &oi;								// durchgereichte Daten
	
		if (! DEX_EnumPBDData (ELK))
		{
			DEX_Error (RC_OdbcImport, EC_ILLPARS);	// keine Okjektklassen gefunden				
			TRACE0 ("ODBC-ABGLEICH: Fehler beim enumerieren der Objektklassen-Beschr. !\n");
			return FALSE;
		}
				
	//	alle Merkmals-Beschreibungen ausgeben
		ELK.eKey = 'm';				
		oi.Reset ();										// alles Rücksetzen
		oi.m_lType = ELK.eKey;								// Typ Merkmal
		oi.m_pCListBox = &m_lvObjektMerkmale;				// neues CListControl
	
		if (! DEX_EnumPBDData (ELK))
		{
			DEX_Error (RC_OdbcImport, EC_ILLPARS);	// keine Merkmalsbeschr. gefunden				
			TRACE0 ("ODBC-ABGLEICH: Fehler beim enumerieren der Merkmalsbeschreibungen !\n");
			return FALSE;
		}           
		
		bRet = ReadParams ();
		UpdateWindow ();
		SetOkButton ();
	}	
	CATCH (CMemoryException, me)
	{
		DEX_Error (RC_OdbcImport, EC_NOMEMORY);		
	}
	AND_CATCH (CUserException, ue)
	{
		DEX_Error (RC_OdbcImport, EC_SYSERROR);
	}
	END_CATCH

	if (!bRet)
	{
		GetParent () -> EndDialog (IDCANCEL);
		return TRUE;
	}		    
	           
	PostMessage (IDM_SETFOCUS, 0, 0L);	           
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTriasPage::OnSelChangeObjektKlassen(void) 
{
// 	TODO: Add your control notification handler code here
	SetOkButton ();
}

void CTriasPage::OnSelChangeObjektMerkmale(void) 
{
// 	TODO: Add your control notification handler code here
	SetOkButton ();
}

//	Ok-Button aktivieren/deaktivieren
void CTriasPage :: SetOkButton (void)
{
	if ((m_lvObjektKlassen.GetSelCount() > 0) && 
		(m_lvObjektMerkmale.GetCurSel() >= 0))
#ifdef WIN32		
		GetParent () -> SetWizardButtons (PSWIZB_NEXT | PSWIZB_BACK);
	else
		GetParent () -> SetWizardButtons (PSWIZB_BACK);		
#else 
		g_pSheet -> SetWizardButtons (PSWIZB_NEXT | PSWIZB_BACK);
	else
		g_pSheet -> SetWizardButtons (PSWIZB_BACK);			
#endif		
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
	int *pIndizes = NULL;

//	nur löschen ?
	if (!bGet)
		return TRUE;

	TRY
	{
	//	lese sel. Merkmalskode              
		CString strSel;
		char Buffer [30] = "";			
		int iIndex = m_lvObjektMerkmale.GetCurSel ();
		if (iIndex >= 0)
		{   
			m_lvObjektMerkmale.GetText (iIndex, strSel);
			g_pCParams -> m_ulObjektMKode = strtoul (strSel, NULL, g_sMkBase);
			m_lvObjektMerkmale.SetCurSel (-1);
		}			

	//	lese sel. Objektklassen
		int iCnt = m_lvObjektKlassen.GetSelCount(); 
		if (iCnt > 0)
		{
		//	neuen Speicher anfordern und init.
			pObjKl = new ulong [iCnt + 1];		//	letzter ID wird 0
			memset (pObjKl, 0, sizeof (ulong) * (iCnt + 1));
		
			pIndizes = new int [iCnt];
			memset (pIndizes, 0, sizeof (int) * iCnt);	
			m_lvObjektKlassen.GetSelItems (iCnt, pIndizes);		// Lese Index-Feld

		//	alle IDs lesen
			for (int iIn = 0; iIn < iCnt; iIn++)
			{
			//	lese akt. Index
				m_lvObjektKlassen.GetText (pIndizes [iIn], strSel);
			
			//	lese Id
				pObjKl [iIn] = strtoul (strSel, NULL, g_sIdBase);
			}                         
			
		//	Speicher freigeben
			DELETE_VEC (pIndizes);
			
		//	Selektion zurücksetzen
			m_lvObjektKlassen.SetSel (-1, FALSE);

		//	da alles OK, Liste wird gültig
			g_pCParams -> m_pulObjektKlassen = pObjKl;
		}
	}
	CATCH (CMemoryException, me)
	{
		DELETE_VEC (pObjKl);
		DELETE_VEC (pIndizes);
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
#ifdef WIN32
BOOL CTriasPage :: SelectItem (CListCtrl &list, ulong ulKode, short sType)
#else 
BOOL CTriasPage :: SelectItem (CListBox &list, ulong ulKode, short sType)
#endif
{
//	prüfe Parameter
	ASSERT (ulKode > 0);
	ASSERT (sType == 'i' || sType == 'm');

//	lese zugeh. Kurztext von Trias
	char KurzText [KurzTextLen] = "";
	if (!GetKurzText (ulKode, sType, KurzText, KurzTextLen))
		return FALSE;

	char Buffer [80] = "";
	if ((sType == 'i' && g_sIdBase == 10) ||
	    (sType == 'm' && g_sMkBase == 10))
		wsprintf (Buffer, "%08ld:%s", ulKode, KurzText);
	else
		wsprintf (Buffer, "%08lx:%s", ulKode, KurzText);		
		
//	String selektieren		
	if (sType == 'i')
	{
		int iIndex = list.FindString (-1, Buffer);	
		if (iIndex >= 0)               
		{
			list.SetSel (iIndex, TRUE);
			return TRUE;			
		}			
	}			
	else                            
	{
		list.SelectString (-1, Buffer);						
		return TRUE;			
	}		

	return FALSE;
}       

void CTriasPage::OnDestroy() 
{
	CPropertyPage::OnDestroy();
	
// 	TODO: Add your message handler code here
	GetUserEntries (TRUE);
}
        
LONG CTriasPage :: OnSetFocusToControl (UINT, LONG)
{
	GotoDlgCtrl (&m_lvObjektKlassen);
	return TRUE;		
}
        
        