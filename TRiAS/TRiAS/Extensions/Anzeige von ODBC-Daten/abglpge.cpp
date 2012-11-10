// abglpge.cpp : implementation file
//

#include "pheader.h"
#include "odbcext.hr"

#include <hpp/helptext.hpp>				// CHelpText
#include <hpp/getodbci.hpp>				// COdbcInfos
#include "profile.hpp"				// DBaseProfile
#include <hpp/waitcur.hpp>				// CWaitCursor

#include "importpa.hpp"				// CImportParams
#include "abglpge.hpp"				// zugeh. Header

#include "myhelper.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// 	Konstanten
const short ImpSectBuffSize = 512;		// ImportPuffergröße
const short EntryBufferSize = 256;		// Puffergröße einer Zeile 

// externe Variablen
extern CImportParams *g_pCParams;	
extern int g_sMkBase;				
#ifndef WIN32
extern CPropertySheetExt *g_pSheet;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAbgleichPage property page

IMPLEMENT_DYNCREATE(CAbgleichPage, CPropertyPage)

CAbgleichPage::CAbgleichPage() : CPropertyPage(CAbgleichPage::IDD)
{
	//{{AFX_DATA_INIT(CAbgleichPage)
	//}}AFX_DATA_INIT               
}

CAbgleichPage::~CAbgleichPage()
{    
}

void CAbgleichPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAbgleichPage)
	DDX_Control(pDX, IDL_ABGLEICH, m_lbAuswahl);
	DDX_Control(pDX, IDE_ABGLEICH, m_edAuswahl);
	//}}AFX_DATA_MAP
}

#ifdef WIN32
BEGIN_MESSAGE_MAP(CAbgleichPage, CPropertyPage)
	//{{AFX_MSG_MAP(CAbgleichPage)
	ON_EN_CHANGE(IDE_ABGLEICH, OnEditchangeAbgleich)
	ON_LBN_SELCHANGE(IDL_ABGLEICH, OnSelchangeAbgleich)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#else 
	BEGIN_MESSAGE_MAP(CAbgleichPage, CPropertyPage)
	//{{AFX_MSG_MAP(CAbgleichPage)
	ON_EN_CHANGE(IDE_ABGLEICH, OnEditchangeAbgleich)
	ON_LBN_SELCHANGE(IDL_ABGLEICH, OnSelchangeAbgleich)
	ON_WM_DESTROY()
	ON_MESSAGE(IDM_SETFOCUS, OnSetFocusToControl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// WIN32


/////////////////////////////////////////////////////////////////////////////
// CAbgleichPage message handlers
BOOL CAbgleichPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	// TODO: Add extra initialization here

	if (!ReadParams ())
	{
		GetParent () -> EndDialog (IDCANCEL);
		return TRUE;
	}		
		
#ifndef WIN32
	m_edAuswahl.SetWindowText (g_pCParams -> m_strDefinition);	
	SetOkButton (); 
	PostMessage (IDM_SETFOCUS, 0, 0L);
#endif	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAbgleichPage::OnEditchangeAbgleich() 
{
// 	TODO: Add your control notification handler code here
	SetOkButton ();
}

//	Nutzereingaben lesen
BOOL CAbgleichPage :: GetUserEntries (BOOL bGet)	
{
	ASSERT (g_pCParams != NULL);

	g_pCParams -> m_strDefinition.Empty ();
	if (!bGet)
		return TRUE;

//	lese Definition-Name
	m_edAuswahl.GetWindowText (g_pCParams -> m_strDefinition); 	

	return TRUE;
}

void CAbgleichPage::OnCancel() 
{
//	TODO: Add your specialized code here and/or call the base class
	GetUserEntries (FALSE);

	CPropertyPage::OnCancel();
}

BOOL CAbgleichPage::OnKillActive() 
{
//	TODO: Add your specialized code here and/or call the base class
	GetUserEntries (TRUE);
	
	return CPropertyPage::OnKillActive();
}
      
BOOL CAbgleichPage::OnSetActive() 
{
//	TODO: Add your specialized code here and/or call the base class
#ifdef WIN32
	SetOkButton (); 
#endif	
	
	return CPropertyPage::OnSetActive();
}

void CAbgleichPage::SetOkButton ()
{       
	if (m_edAuswahl.GetWindowTextLength () > 0)
#ifdef WIN32	
		GetParent () -> SetWizardButtons (PSWIZB_NEXT);
	else
		GetParent () -> SetWizardButtons (0);
#else
		g_pSheet -> SetWizardButtons (PSWIZB_NEXT);
	else
		g_pSheet -> SetWizardButtons (0);		
#endif		
}

//	lese Definitionen aus der INI-Datei
BOOL CAbgleichPage::ReadParams (void)
{
	TRY
	{
		Profile ProFile;			// Ini-Name
		CString strSection, strBuffer;
		if (!strSection.LoadString (IDS_IMPORT_SECTION))
			AfxThrowUserException ();

	//	Lesepuffer für alle Einträge anf.
		char *pBuffer = strBuffer.GetBuffer (ImpSectBuffSize);
		
		if (GetPrivateProfileString (strSection, NULL, "", pBuffer, 
									 ImpSectBuffSize, ProFile.GetProFileName ()))
		{
		//	alle Einträge lesen
			for (; *pBuffer; pBuffer += lstrlen (pBuffer) + 1)			
			{
				if (m_lbAuswahl.AddString (pBuffer) < 0)
					AfxThrowUserException ();
			}
		}           
		
		return TRUE;
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

	return FALSE;
}

//	lese Einstellungen zur akt. Selektion
BOOL CAbgleichPage :: ReadActSelection (const char *pSection)
{
//	prüfe Parameter
	ASSERT (pSection != NULL && AfxIsValidString (pSection));
	ASSERT (g_pCParams != NULL);

	TRY
	{
		CWaitCursor wc;
	//	alle alten Infos löschen
		g_pCParams -> CleanUp ();

		Profile ProFile;			// Ini-Name
		CString strEntry, strBuffer;
		char *pBuffer = strBuffer.GetBuffer (EntryBufferSize);

	//	lese Löschflag1
		if (!strEntry.LoadString (IDS_IMP_DELNOTEXIST))
			AfxThrowUserException ();
		g_pCParams -> m_bDelNotExist = GetPrivateProfileInt (pSection, strEntry, 0, 
									   ProFile.GetProFileName ()) > 0 ? TRUE : FALSE;
	//	lese Löschflag2
		if (!strEntry.LoadString (IDS_IMP_IMPNOTEXIST))
			AfxThrowUserException ();
		g_pCParams -> m_bAddNotExist = GetPrivateProfileInt (pSection, strEntry, 0, 
									   ProFile.GetProFileName ()) > 0 ? TRUE : FALSE;
	
	//	Merkmalskode
		if (!strEntry.LoadString (IDS_MERKMALKODE))
			AfxThrowUserException ();
		if (GetPrivateProfileString (pSection, strEntry, "", pBuffer, 
									 EntryBufferSize, ProFile.GetProFileName ()))
		{
// JG Alter Code MCodes in der Datenbank
#pragma MSG("MCodes in der Datenbank")
 			g_pCParams -> m_ulObjektMKode = strtoul (pBuffer, NULL, g_sMkBase); 
			
		}
	//	DataSourceName
		if (!strEntry.LoadString (IDS_IMP_DATASOURCENAME))
			AfxThrowUserException ();
		if (GetPrivateProfileString (pSection, strEntry, "", pBuffer, 
									 EntryBufferSize, ProFile.GetProFileName ()))
			g_pCParams -> m_strDataSource = pBuffer;

	//	lese DataSourceTyp
		if (!strEntry.LoadString (IDS_IMP_DATASOURCE_TYPE))
			AfxThrowUserException ();
		g_pCParams -> m_tDsn = (DataSourceType) GetPrivateProfileInt (pSection, strEntry, 
																	  (int) UserDataSource, 
																	  ProFile.GetProFileName ());

	//	Aktion
		if (!strEntry.LoadString (IDS_IMP_AKTION))
			AfxThrowUserException ();
		g_pCParams -> m_bAction = GetPrivateProfileInt (pSection, strEntry, 1, 
								  ProFile.GetProFileName ()) > 0 ? TRUE : FALSE;

	//	Tabellenname
		if (!strEntry.LoadString (IDS_IMP_TABLENAME))
			AfxThrowUserException ();
		if (GetPrivateProfileString (pSection, strEntry, "", pBuffer, 
									 EntryBufferSize, ProFile.GetProFileName ()))
			g_pCParams -> m_strTableName = pBuffer;			

	//	Filter
		if (!strEntry.LoadString (IDS_IMP_FILTER))
			AfxThrowUserException ();
		if (GetPrivateProfileString (pSection, strEntry, "", pBuffer, 
									 EntryBufferSize, ProFile.GetProFileName ()))
			g_pCParams -> m_strFilter = pBuffer;			

	//	Felder
		if (!strEntry.LoadString (IDS_IMP_FELDER))
			AfxThrowUserException ();
		if (GetPrivateProfileString (pSection, strEntry, "", pBuffer, 
									 EntryBufferSize, ProFile.GetProFileName ()))
		{
			char *pBeg = strchr (pBuffer, ',');	// suche 1. Separator
			if (pBeg)
			{
				CString strHelp = pBuffer;
				g_pCParams -> m_strKoppelFeld = strHelp.Left (pBeg - pBuffer);

			//	suche nächstes Feld
				char *pEnd = NULL;				
				if (*++pBeg && (pEnd = strchr (pBeg, ',')))	// suche 2. Sep.
				{
					g_pCParams -> m_strRechtsWert = strHelp.Mid (pBeg - pBuffer, pEnd - pBeg);
					if (*++pEnd)
						g_pCParams -> m_strHochWert = pEnd;
				}
			}
		}

	//	Objekt-Klassen
		if (!strEntry.LoadString (IDS_IMP_OBJEKTKLASSEN))
			AfxThrowUserException ();
		int iCnt = GetPrivateProfileInt (pSection, strEntry, 0, ProFile.GetProFileName ());
		if (iCnt == 0)		// keine Einträge vorhanden
			return TRUE;

	//	neues Id-Feld anlegen
		ulong *pIdFeld = new ulong [iCnt + 1];
		memset (pIdFeld, 0, sizeof (ulong) * (iCnt + 1));	// Feld init.
		g_pCParams -> m_pulObjektKlassen = pIdFeld;			// Zeiger speichern

	//	jetzt eigentlichen Text lesen		
		if (GetPrivateProfileString (pSection, strEntry, "", pBuffer, 
									 EntryBufferSize, ProFile.GetProFileName ()))
		{
			char *pFirst = strchr (pBuffer, ',');		// 1. Zeichen hinter Anz.
			if (pFirst && *++pFirst)				
			{
				ulong ulVal = 0;
				for (int i = 0; i < iCnt; i++)
				{
					if (FAILED(IdentFromClassX (pFirst, &ulVal, FALSE)) || (ulVal <= 0))
						break;
					pIdFeld [i] = ulVal;
					
				//	Zeiger weitersetzen
					while (*++pFirst && *pFirst != ',');
						
				//	am Ende ?			
					if (!*pFirst || !*++pFirst)		//	auf nächste Zahl
						break;
				}
			}
		}
			
		return TRUE;
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

	return FALSE;
}

void CAbgleichPage::OnSelchangeAbgleich() 
{
// TODO: Add your control notification handler code here
	int iIndex = m_lbAuswahl.GetCurSel ();
	if (iIndex == LB_ERR)
		return;

//	Text ins Edit-Control setzen
	CString strText;
	m_lbAuswahl.GetText (iIndex, strText); 
	m_edAuswahl.SetWindowText (strText);

	if (!ReadActSelection (strText))
		GetParent () -> EndDialog (IDCANCEL);	// bei Fehler
}

void CAbgleichPage::OnDestroy() 
{
	CPropertyPage::OnDestroy();
	// TODO: Add your message handler code here
#ifndef WIN32	
	GetUserEntries (TRUE);
#endif	
}            

#ifndef WIN32
LONG CAbgleichPage :: OnSetFocusToControl (UINT, LONG)
{
	GotoDlgCtrl (&m_edAuswahl);
	return TRUE;		
}
#endif

