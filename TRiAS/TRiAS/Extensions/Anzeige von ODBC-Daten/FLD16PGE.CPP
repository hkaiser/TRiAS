// feldpage.cpp : implementation file
//

#include "pheader.h"

extern "C" 
{
    #include <xtension.h>   		// TRIAS-Messages
    #include <xtensnx.h>
    #include "odbcext.hr"			// Resource-Konstanten
}    

#include <columnst.hpp>				// CColumns
#include <helptext.hpp>				// CHelpText
#include <waitcur.hpp>				// CWaitCursor
#include <odbcerr.hpp>				// OdbcError
#include <getodbci.hpp>				// COdbcInfos

#include "importpa.hpp"				// CImportParams
#include "fld16pge.hpp"				// zugeh. Header

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// externe Variablen
extern CImportParams *g_pCParams;		// Parameterfeld
extern CPropertySheetExt *g_pSheet;		

/////////////////////////////////////////////////////////////////////////////
// CFeldPage property page

IMPLEMENT_DYNCREATE(CFeldPage, CPropertyPage)

CFeldPage::CFeldPage() : CPropertyPage(CFeldPage::IDD)
{
	//{{AFX_DATA_IINIT(CFeldPage)
	//}}AFX_DATA_NIT
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
	DDX_Control(pDX, IDE_FELDER_DESCR, m_stDescription);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFeldPage, CPropertyPage)
	//{{AFX_MSG_MAP(CFeldPage)
	ON_LBN_SELCHANGE(IDL_FELD_RECHTSW, OnSelChangeRechtsWert)
	ON_LBN_SELCHANGE(IDL_FELD_HOCHW, OnSelChangeHochWert)
	ON_LBN_SELCHANGE(IDL_FELD_KOPPEL, OnSelChangeKoppelFeld)
	ON_WM_DESTROY()
	ON_MESSAGE(IDM_SETFOCUS, OnSetFocusToControl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CFeldPage message handlers
void CFeldPage::OnSelChangeKoppelFeld()
{       
	int iSel = m_lcKoppelFeld.GetCurSel ();
	
	if (iSel >= 0)
	{                
		CString strSel;
		m_lcKoppelFeld.GetText (iSel, strSel);		
		g_pCParams -> m_COdbcInfos.OutputColumnInfo (strSel, m_stDescription);
	}

	SetOkButton ();	
}                  

void CFeldPage::OnSelChangeHochWert()
{   
	int iSel = m_lcHochWert.GetCurSel ();
	
	if (iSel >= 0)
	{                
		CString strSel;
		m_lcHochWert.GetText (iSel, strSel);		
		g_pCParams -> m_COdbcInfos.OutputColumnInfo (strSel, m_stDescription);
	}
	
	SetOkButton ();	
}                                  

void CFeldPage::OnSelChangeRechtsWert()
{   
	int iSel = m_lcRechtsWert.GetCurSel ();
	
	if (iSel >= 0)
	{                
		CString strSel;
		m_lcRechtsWert.GetText (iSel, strSel);		
		g_pCParams -> m_COdbcInfos.OutputColumnInfo (strSel, m_stDescription);
	}
			
	SetOkButton ();	
}                  
                
void CFeldPage::OnDestroy() 
{
	CPropertyPage::OnDestroy();
	
	// TODO: Add your message handler code here
	GetUserEntries (TRUE);                        
	m_stDescription.GetWindowText (m_strLastInfo);
}
                
//	Ok-Button aktivieren/deaktivieren
void CFeldPage :: SetOkButton (void)
{                                                  
	int iIndexKF = m_lcKoppelFeld.GetCurSel ();
	int iIndexHW = m_lcHochWert.GetCurSel ();
	int iIndexRW = m_lcRechtsWert.GetCurSel ();
	
	if (iIndexKF >= 0 && iIndexHW >= 0 && iIndexRW >= 0)
	{
	//	prüfe ob Felder verschieden sind
		CString strKF, strRW, strHW;
		m_lcKoppelFeld.GetText (iIndexKF, strKF);
		m_lcHochWert.GetText (iIndexHW, strHW);
		m_lcRechtsWert.GetText (iIndexRW, strRW);						

	//	sind alle Felder verschieden voneinander ?
		if (strcmp (strKF, strRW) && strcmp (strKF, strHW) && strcmp (strRW, strHW))
		{
			g_pSheet -> SetWizardButtons (PSWIZB_NEXT | PSWIZB_BACK);
			return;
		}
	}

	g_pSheet -> SetWizardButtons (PSWIZB_BACK);	
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
		int iIndex = m_lcKoppelFeld.GetCurSel ();		
		if (iIndex >= 0)
			m_lcKoppelFeld.GetText (iIndex, g_pCParams -> m_strKoppelFeld);

	//	lese Rechtswert-Feldname
		iIndex = m_lcRechtsWert.GetCurSel ();		
		if (iIndex >= 0)
			m_lcRechtsWert.GetText (iIndex, g_pCParams -> m_strRechtsWert);
	
	//	lese Hochwert-Feldname
		iIndex = m_lcHochWert.GetCurSel ();		
		if (iIndex >= 0)
			m_lcHochWert.GetText (iIndex, g_pCParams -> m_strHochWert);
	}
	CATCH (CMemoryException, me)
	{
		DEX_Error (RC_OdbcImport, EC_NOMEMORY);
		return FALSE;
	}
	END_CATCH		
	
	return TRUE;	
}

void CFeldPage::OnCancel() 
{
	// TODO: Add your specialized code here and/or call the base class
	GetUserEntries (FALSE);
	
	CPropertyPage::OnCancel();
}

BOOL CFeldPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	if (!ReadParams ())                  
	{
		g_pSheet -> EndDialog (IDCANCEL);
		return TRUE;
	}		    
	
	SetOkButton ();
	
	PostMessage (IDM_SETFOCUS, 0, 0L);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CFeldPage::ReadParams (void)
{
//	prüfe globale Parameter
	ASSERT (g_pCParams != NULL);

	TRY
	{
		CWaitCursor wc;				// Sanduhr einschalten
		
		 if (!m_stDescription.InitFont ())
			AfxThrowUserException ();

	//	mögliche Koppel-und Koordinatenfelder ausgeben
		ASSERT (g_pCParams -> m_COdbcInfos.m_pDataBase != NULL);
		ASSERT (g_pCParams -> m_strTableName.GetLength () > 0);
                      
	//	altes Objekt löschen                                                                                          
		CColumns *&pCol = g_pCParams -> m_COdbcInfos.m_pColumns;
		DELETE_OBJ (pCol);
		pCol = new CColumns ((CDatabase *) g_pCParams -> m_COdbcInfos.m_pDataBase);
		pCol -> m_strTableNameParam = g_pCParams -> m_strTableName;       

		BOOL bIsKoordField = FALSE;			// KoordFeld-Flag
		if (pCol -> Open ())				// Set öffnen
		{   
			while (! pCol -> IsEOF ())
			{   
			//	ist dieses Feld ein Koordinatenfeld ?				
				if (pCol -> IsKoordField ())
				{
				//	Feldinfos ausgeben
					bIsKoordField = TRUE;
					if ((m_lcHochWert.AddString (pCol -> m_strColumnName) < 0) || 
						(m_lcRechtsWert.AddString (pCol -> m_strColumnName) < 0))
						AfxThrowUserException ();
				}
				else
					bIsKoordField = FALSE;

			// 	ist dieses Feld ein Koppelfeld ?
				if (bIsKoordField || pCol -> IsKoppelField ())	// Koord~ sind i.a. auch Koppelfelder
				{
				// 	FeldInfos ausgeben
					if (m_lcKoppelFeld.AddString (pCol -> m_strColumnName) < 0)
						AfxThrowUserException ();                        
				}						
										
				pCol -> MoveNext ();		// zum nächsten Feld
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
		DEX_Error (RC_OdbcImport, EC_SYSERROR);		
		return FALSE;
	}
	END_CATCH

//	Selektion setzen
//	Koppelfeld	
	m_lcKoppelFeld.SelectString (-1, g_pCParams -> m_strKoppelFeld);

//	RechtsWert
	m_lcRechtsWert.SelectString (-1, g_pCParams -> m_strRechtsWert);

//	Hochwert
	m_lcHochWert.SelectString (-1, g_pCParams -> m_strHochWert);    
	
//	ggf. Infotext ausgeben
	m_stDescription.SetWindowText (m_strLastInfo);

	return TRUE;
}

LONG CFeldPage :: OnSetFocusToControl (UINT, LONG)
{
	GotoDlgCtrl (&m_lcKoppelFeld);
	return TRUE;		
}

