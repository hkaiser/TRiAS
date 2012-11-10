// rsltpge.cpp : implementation file
//

#include "pheader.h"
#include "odbcext.hr"

#include <hpp/objinfo.hpp>				// GetKurzText ()
#include <hpp/getodbci.hpp>				// COdbcInfos
#include "database.hpp"				// CDataBaseExt
#include <hpp/waitcur.hpp>				// CWaitCursor
#include <hpp/helptext.hpp>				// CHelpText
#include "profile.hpp"				// DBaseProfile
#include "importpa.hpp"				// CImportParams

#include "rsltpge.hpp"				// zugeh. Header

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Konstanten
const short sResultBufferSize = 256;		// Ergebnis-Puffer-Größe
const short sValBufferSize = 30;			// Zahlenpuffer

//	externe Variablen
extern CImportParams *g_pCParams;
extern int g_sMkBase;				

#ifndef WIN32
	extern CPropertySheetExt *g_pSheet;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResultPage property page
IMPLEMENT_DYNCREATE(CResultPage, CPropertyPage)

CResultPage::CResultPage() : CPropertyPage(CResultPage::IDD)
{
	//{{AFX_DATA_INIT(CResultPage)
	//}}AFX_DATA_INIT
}

CResultPage::~CResultPage()
{
}

void CResultPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CResultPage)
	DDX_Control(pDX, IDC_IMP_RES_AKTION, m_stAktion);
	DDX_Control(pDX, IDC_IMP_RES_DEF, m_stDef);
	DDX_Control(pDX, IDE_IMP_RES_OBJKL, m_edObjektKlassen);
	DDX_Control(pDX, IDC_IMP_RES_TABLE, m_stTable);
	DDX_Control(pDX, IDC_IMP_RES_RECHTSW, m_stRechtsWert);
	DDX_Control(pDX, IDC_IMP_RES_OBJMERKM, m_stObjektMerkmal);
	DDX_Control(pDX, IDC_IMP_RES_NOTEXISTS, m_stNotExists);
	DDX_Control(pDX, IDC_IMP_RES_KOPPELF, m_stKoppelFeld);
	DDX_Control(pDX, IDC_IMP_RES_HOCHW, m_stHochWert);
	DDX_Control(pDX, IDC_IMP_RES_FILTER, m_stFilter);
	DDX_Control(pDX, IDC_IMP_RES_DSN, m_stDsn);
	DDX_Control(pDX, IDC_IMP_RES_ADD, m_stAdd);
	//}}AFX_DATA_MAP
}

#ifndef WIN32
BEGIN_MESSAGE_MAP(CResultPage, CPropertyPage)
	//{{AFX_MSG_MAP(CResultPage)
	ON_WM_DESTROY()
	ON_MESSAGE(IDM_SETFOCUS, OnSetFocusToControl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif

/////////////////////////////////////////////////////////////////////////////
// CResultPage message handlers
BOOL CResultPage::OnSetActive() 
{
//	TODO: Add your specialized code here and/or call the base class
#ifdef WIN32
	GetParent () -> SetWizardButtons (PSWIZB_BACK | PSWIZB_NEXT);
	GetUserEntries ();
#else 
	ASSERT (g_pSheet != NULL);
	g_pSheet -> SetWizardButtons (PSWIZB_BACK | PSWIZB_NEXT);
#endif	

	return CPropertyPage::OnSetActive();
}
                                       
//	lese Nutzereingaben                                       
void CResultPage::GetUserEntries (void)
{
	ASSERT (g_pCParams != NULL);
	ASSERT (g_pCParams -> InfoComplete ());  // Infos OK ?
	
	BOOL bRet = FALSE;		// noch nichts getan

//	Ergebnisse ausgeben
	TRY
	{
		CString strHelp;
		m_stDef.SetWindowText (g_pCParams -> m_strDefinition);
		m_stTable.SetWindowText (g_pCParams -> m_strTableName);
		m_stKoppelFeld.SetWindowText (g_pCParams -> m_strKoppelFeld);
		m_stRechtsWert.SetWindowText (g_pCParams -> m_strRechtsWert);
		m_stHochWert.SetWindowText (g_pCParams -> m_strHochWert);
		m_stDsn.SetWindowText (g_pCParams -> m_strDataSource);
		if (g_pCParams -> m_strFilter.IsEmpty ())
		{
			if (!strHelp.LoadString (IDS_IMP_OHNE))				
				AfxThrowUserException ();
			m_stFilter.SetWindowText (strHelp);
		}
		else
			m_stFilter.SetWindowText (g_pCParams -> m_strFilter);

	//	Objektmerkmal
		char szValBuffer [sValBufferSize] = "";			// Zahlenpuffer
		char szKurzText [KurzTextLen + sizeof (szValBuffer)] = "";	// Kurztext-Puffer
		ultoa (g_pCParams -> m_ulObjektMKode, szValBuffer, g_sMkBase);
		if (GetKurzText (g_pCParams -> m_ulObjektMKode, 'm', szKurzText, KurzTextLen))
			lstrcat (szKurzText, ":");
		lstrcat (szKurzText, szValBuffer);
		m_stObjektMerkmal.SetWindowText (szKurzText);

	//	Objektklassen 
		int iCnt = 0;		// Anzahl 
		ulong *pulIds = g_pCParams -> m_pulObjektKlassen;
		while (*pulIds++ != 0)
			iCnt++;

	//	Speicher anfordern
		CString strBuffer;
		char *pBuffer = strBuffer.GetBuffer ((iCnt+1) * sizeof (szKurzText));	
		*pBuffer = '\0';

	//	alle Ids anhängen
		for (pulIds = g_pCParams -> m_pulObjektKlassen; *pulIds; pulIds++)
		{
			if (GetKurzText (*pulIds, 'i', szKurzText, KurzTextLen))
			{
				lstrcat (pBuffer, szKurzText);
				lstrcat (pBuffer, ":");
			}
			if (FAILED(ClassFromIdentX (*pulIds, szValBuffer, sizeof(szValBuffer))))
				continue;
			lstrcat (pBuffer, szValBuffer);
			lstrcat (pBuffer, ",");
		}
		pBuffer [lstrlen (pBuffer) - 1] = '\0';		// letzte Komma abschn.
		m_edObjektKlassen.SetWindowText (pBuffer);	// Text ausgeben

	//	Abgleichsart
		if (!strHelp.LoadString (g_pCParams -> m_bAction ? IDS_IMP_RES_TRIAS :
														   IDS_IMP_RES_TABLE))
			AfxThrowUserException ();
		m_stAktion.SetWindowText (strHelp);

	//	nicht existierende
		CString strFormat;
		if (!strFormat.LoadString (g_pCParams -> m_bDelNotExist ? IDS_DELETE :
																  IDS_IGNORE))
			AfxThrowUserException ();
		AfxFormatString1 (strHelp, g_pCParams -> m_bAction ? IDS_IMP_RES_DNET :
															 IDS_IMP_RES_DNEB, strFormat); 
		m_stNotExists.SetWindowText (strHelp);
																
	//	nicht vorhandene 
		if (!strFormat.LoadString (g_pCParams -> m_bAddNotExist ? IDS_IMPORTED :
																  IDS_IGNORE))
			AfxThrowUserException ();				
		AfxFormatString1 (strHelp, g_pCParams -> m_bAction ? IDS_IMP_RES_ADDB :
															 IDS_IMP_RES_ADDT, strFormat); 
		m_stAdd.SetWindowText (strHelp);        
		bRet = TRUE;
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
		GetParent () -> EndDialog (IDCANCEL);
}

#ifdef WIN32
LRESULT CResultPage::OnWizardNext() 
{
// TODO: Add your specialized code here and/or call the base class
//	schreibe akt. Stand in Projekt-Ini
	StoreUserEntries ();                     
	return CPropertyPage::OnWizardNext();
}           
#endif
                  
//	akt. Eingaben speichern                  
void CResultPage::StoreUserEntries (void)
	
{    
	ASSERT (g_pCParams != NULL);

	BOOL bRet = FALSE;					// noch nichts getan
	TRY
	{
		Profile ProFile;			// Ini-Name
		CString strSection, strEntry;
		
	//	Schreibe Section-Eintrag selbst
		if (!strSection.LoadString (IDS_IMPORT_SECTION))
			AfxThrowUserException ();
		if (! WritePrivateProfileString (strSection, g_pCParams -> m_strDefinition, 
										 "1", ProFile.GetProFileName ()))
			AfxThrowFileException (CFileException::generic);
		
	//	diese Section bleibt aktiv
		strSection = g_pCParams -> m_strDefinition;

	//	Löschflag1
		if (!strEntry.LoadString (IDS_IMP_DELNOTEXIST))
			AfxThrowUserException ();
		if (! WritePrivateProfileString (strSection, strEntry, 
										 g_pCParams -> m_bDelNotExist ? "1" : "0",
										 ProFile.GetProFileName ()))
			AfxThrowFileException (CFileException::generic);
		
	//	Löschflag2
		if (!strEntry.LoadString (IDS_IMP_IMPNOTEXIST))
			AfxThrowUserException ();
		if (! WritePrivateProfileString (strSection, strEntry, 
										 g_pCParams -> m_bAddNotExist ? "1" : "0",
										 ProFile.GetProFileName ()))
			AfxThrowFileException (CFileException::generic);			

	//	Aktion
		if (!strEntry.LoadString (IDS_IMP_AKTION))
			AfxThrowUserException ();
		if (! WritePrivateProfileString (strSection, strEntry, 
										 g_pCParams -> m_bAction ? "1" : "0",
										 ProFile.GetProFileName ()))
			AfxThrowFileException (CFileException::generic);			

	//	Felder
		if (!strEntry.LoadString (IDS_IMP_FELDER))
			AfxThrowUserException ();
		CString strHelp = g_pCParams -> m_strKoppelFeld + "," + g_pCParams -> m_strRechtsWert + "," +
				  g_pCParams -> m_strHochWert;					  
		if (! WritePrivateProfileString (strSection, strEntry, strHelp,			
										 ProFile.GetProFileName ()))
			AfxThrowFileException (CFileException::generic);	

	//	Filter
		if (!strEntry.LoadString (IDS_IMP_FILTER))
			AfxThrowUserException ();
		strHelp = "\"" + g_pCParams -> m_strFilter + "\"";
		if (! WritePrivateProfileString (strSection, strEntry, strHelp,			
										 ProFile.GetProFileName ()))
			AfxThrowFileException (CFileException::generic);			

	//	Tabellenname
		if (!strEntry.LoadString (IDS_IMP_TABLENAME))
			AfxThrowUserException ();
		if (! WritePrivateProfileString (strSection, strEntry, 
										 g_pCParams -> m_strTableName,
										 ProFile.GetProFileName ()))
			AfxThrowFileException (CFileException::generic);			

	//	DataSourceName
		if (!strEntry.LoadString (IDS_IMP_DATASOURCENAME))
			AfxThrowUserException ();
		if (! WritePrivateProfileString (strSection, strEntry, 
										 g_pCParams -> m_strDataSource,
										 ProFile.GetProFileName ()))
			AfxThrowFileException (CFileException::generic);			

	//	DataSourceTyp 
		if (!strEntry.LoadString (IDS_IMP_DATASOURCE_TYPE))
			AfxThrowUserException ();
		char Buffer10 [10] = "";
		if (! WritePrivateProfileString (strSection, strEntry,
										 itoa ((int) g_pCParams -> m_tDsn, Buffer10, 10),
										 ProFile.GetProFileName ()))
			AfxThrowFileException (CFileException::generic);			

	//	Merkmalskode
		if (!strEntry.LoadString (IDS_MERKMALKODE))
			AfxThrowUserException ();
		char szValBuff [sValBufferSize] = "";
		if (! WritePrivateProfileString (strSection, strEntry, 
										 ultoa 	(g_pCParams -> m_ulObjektMKode, szValBuff, g_sMkBase),
										 ProFile.GetProFileName ()))
			AfxThrowFileException (CFileException::generic);			

	//	Objekt-Klassen
		if (!strEntry.LoadString (IDS_IMP_OBJEKTKLASSEN))
			AfxThrowUserException ();

		ASSERT (g_pCParams -> m_pulObjektKlassen != NULL);
		int iCnt = 0;		// Anzahl Objektklassen
		ulong *pulIds = g_pCParams -> m_pulObjektKlassen;
		while (*pulIds++ != 0)
			iCnt++;

	//	Speicher anfordern
		CString strBuffer;
		char *pBuffer = strBuffer.GetBuffer ((iCnt * 20) + 10);	
		*pBuffer = '\0';
		itoa (iCnt, pBuffer, 10);

	//	jetzt alle Ids anhängen
		for (pulIds = g_pCParams -> m_pulObjektKlassen; *pulIds; pulIds++)
		{
			lstrcat (pBuffer, ",");
			if (FAILED(ClassFromIdentX (*pulIds, szValBuff, sizeof(szValBuff))))
				continue;
			lstrcat (pBuffer, szValBuff);
		}
		if (! WritePrivateProfileString (strSection, strEntry, pBuffer,
										 ProFile.GetProFileName ()))
			AfxThrowFileException (CFileException::generic);			

		bRet = TRUE;
	}
	CATCH (CMemoryException, me)
	{
		DEX_Error (RC_OdbcImport, EC_NOMEMORY);
	}
	AND_CATCH (CUserException, ue)
	{
		DEX_Error (RC_OdbcImport, EC_SYSERROR);
	}
	AND_CATCH (CFileException, fe)
	{
		// DEX_Error (RC_OdbcImport,  EC_NOWRITE);
		fe -> ReportError ();
	}
	END_CATCH

	if (!bRet)
		GetParent () -> EndDialog (IDCANCEL);
}

#ifndef WIN32	
void CResultPage::OnDestroy() 
{
	CPropertyPage::OnDestroy();
	
	// TODO: Add your message handler code here
	StoreUserEntries ();	
} 

BOOL CResultPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	GetUserEntries ();   
	PostMessage (IDM_SETFOCUS, 0, 0L);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

LONG CResultPage :: OnSetFocusToControl (UINT, LONG)
{
	GotoDlgCtrl (&m_stDef);
	return TRUE;		
}            
#endif

