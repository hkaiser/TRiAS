// WelcomePage.cpp : implementation file
//

#include "fakemfcp.hxx"
#include "fakemfc.h"

#include <registrx.hxx>
#include "Strings.h"

#include "OpenNewPropertySheet.h"
#include "WelcomePage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// lokale Funktionen
int CalcMaxCharCount (CWnd &rField);
LPSTR ShortenPath (LPSTR cbBuffer, int iMaxLen);

/////////////////////////////////////////////////////////////////////////////
// CWelcomePage property page

IMPLEMENT_DYNCREATE(CWelcomePage, CPropertyPage)

CWelcomePage::CWelcomePage() : CPropertyPage(CWelcomePage::IDD)
{
	//{{AFX_DATA_INIT(CWelcomePage)
	//}}AFX_DATA_INIT
	m_iOpenMode = PROJECTOPENMODE_Unknown;

// Caption den aktuellen Erfordernissen anpassen
	TRY {
#if _TRiAS_VER < 0x0420
	CString strOrgCap;

		VERIFY(strOrgCap.LoadString (IDS_WELCOMEDLG));
		m_strCaption.Format (strOrgCap, g_cbTRiAS);
#else
	CString strOrgCap;
	CString strProdName;

		VERIFY(strOrgCap.LoadString (IDS_WELCOMEDLG));
		VERIFY(strProdName.LoadString(IDS_DEFAULTPRODUCTNAME));

	CRegKey regProdName;
	char cbProdName[_MAX_PATH];
	DWORD dwProdNameLen = sizeof(cbProdName);

		if (ERROR_SUCCESS == regProdName.Open(HKEY_CURRENT_USER, "Software", KEY_READ) &&
			ERROR_SUCCESS == regProdName.Open(regProdName, REG_COMPANY_KEY, KEY_READ) &&
			ERROR_SUCCESS == regProdName.Open(regProdName, REG_PRODUCT_KEY, KEY_READ) &&
			ERROR_SUCCESS == regProdName.Open(regProdName, "Config", KEY_READ) &&
			ERROR_SUCCESS == regProdName.QueryValue(cbProdName, "InstalledProduct", &dwProdNameLen) &&
			dwProdNameLen > 1)		// Nullbyte zählt mit
		{
			strProdName = cbProdName;
		} 
		m_strCaption.Format (strOrgCap, g_cbTRiAS, (LPCSTR)strProdName);
#endif // _TRiAS_VER < 0x0420

		m_psp.pszTitle = m_strCaption;
		m_psp.dwFlags |= PSP_USETITLE;

	} CATCH (CMemoryException, e) {
		TRACE("Couldn't change caption for CWelcomePage\r\n");
	} END_CATCH;
}

CWelcomePage::~CWelcomePage()
{
}

void CWelcomePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWelcomePage)
	DDX_Control(pDX, IDC_DONTSHOWFURTHER, m_cbDontShowFurther);
	DDX_Control(pDX, IDC_OPENOLDPROJECT, m_rbOpenOldProject);
	DDX_Control(pDX, IDC_OPENMRUPROJECT, m_rbOpenLast);
	DDX_Control(pDX, IDC_CREATENEWPROJECT, m_rbCreateNew);
	//}}AFX_DATA_MAP
//	DDX_Control(pDX, IDC_LASTPROJECT, m_ftMRUProject);
}


BEGIN_MESSAGE_MAP(CWelcomePage, CPropertyPage)
	//{{AFX_MSG_MAP(CWelcomePage)
	ON_BN_CLICKED(IDC_CREATENEWPROJECT, OnCreateNewProject)
	ON_BN_CLICKED(IDC_OPENMRUPROJECT, OnOpenMruProject)
	ON_BN_CLICKED(IDC_OPENOLDPROJECT, OnOpenOldProject)
	ON_BN_DOUBLECLICKED(IDC_CREATENEWPROJECT, OnDoubleclickedCreatenewproject)
	ON_BN_DOUBLECLICKED(IDC_OPENMRUPROJECT, OnDoubleclickedOpenmruproject)
	ON_BN_DOUBLECLICKED(IDC_OPENOLDPROJECT, OnDoubleclickedOpenoldproject)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWelcomePage message handlers

BOOL CWelcomePage::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_ftMRUProject.SubclassDlgItem(IDC_LASTPROJECT, this);
	m_ftMRUProject.SetPath (TRUE);

// Controls initialisieren
bool fReturn = true;
TCHAR cbBuffer[_MAX_PATH+5];
GETMRUITEM MRU;

	INITSTRUCT(MRU, GETMRUITEM);
	MRU.uiMenuID = g_pTE -> MenuOffset()+1;		// ersten MenuItem nehmen
	MRU.pName = cbBuffer;
	MRU.iLen = sizeof(cbBuffer);
	MRU.fStartup = TRUE;
	if (!DEX_GetMRUItem (MRU)) {
		m_rbOpenLast.EnableWindow (false);

		m_iOpenMode = PROJECTOPENMODE_OpenExistend;			// erster RadioButton
		m_rbOpenOldProject.SetCheck (true);
		m_rbOpenLast.SetCheck (false);
		m_ftMRUProject.SetWindowText (_T(""));
	} else {
		m_iOpenMode = PROJECTOPENMODE_OpenMRU;					// zweiter RadioButton
		m_rbOpenLast.SetCheck (true);
		m_rbOpenOldProject.SetCheck (false);
		m_rbOpenLast.SetFocus();
		m_ftMRUProject.SetWindowText (cbBuffer);
		fReturn = false;
	}
	
	m_rbCreateNew.SetCheck (FALSE);						// dritter RadioButton
	m_iOpenMode = RetrieveOpenMode();

	AdjustButtons();
	return fReturn; // return TRUE unless you set the focus to a control
					// EXCEPTION: OCX Property Pages should return FALSE
}

LRESULT CWelcomePage::OnWizardNext() 
{
	ASSERT(PROJECTOPENMODE_CreateNew == m_iOpenMode);
	return CPropertyPage::OnWizardNext();
}

BOOL CWelcomePage::OnWizardFinish() 
{
// diesen Dialog wieder anzeigen?
	{
	CCurrentUser regMRU (g_cbMRUFiles, true);

		regMRU.SetDWORD (g_cbHideOpenWizard, m_cbDontShowFurther.GetCheck());
	}
	return CPropertyPage::OnWizardFinish();
}

BOOL CWelcomePage::OnSetActive() 
{
	AdjustButtons();
	return CPropertyPage::OnSetActive();
}

///////////////////////////////////////////////////////////////////////////////
// Einer der Radiobuttons wurde gedrückt
void CWelcomePage::OnCreateNewProject() 
{
	m_iOpenMode = RetrieveOpenMode();
	AdjustButtons();
}

void CWelcomePage::OnOpenMruProject() 
{
	m_iOpenMode = RetrieveOpenMode();
	AdjustButtons();
}

void CWelcomePage::OnOpenOldProject() 
{
	m_iOpenMode = RetrieveOpenMode();
	AdjustButtons();
}

void CWelcomePage::OnDoubleclickedCreatenewproject() 
{
CPropertySheet *pSheet = (CPropertySheet *)GetParent();

	ASSERT(NULL != pSheet);
	pSheet -> PressButton (PSBTN_NEXT);
}

void CWelcomePage::OnDoubleclickedOpenmruproject() 
{
CPropertySheet *pSheet = (CPropertySheet *)GetParent();

	ASSERT(NULL != pSheet);
	pSheet -> PressButton (PSBTN_FINISH);
}

void CWelcomePage::OnDoubleclickedOpenoldproject() 
{
CPropertySheet *pSheet = (CPropertySheet *)GetParent();

	ASSERT(NULL != pSheet);
	pSheet -> PressButton (PSBTN_FINISH);
}

PROJECTOPENMODE CWelcomePage::RetrieveOpenMode (void)
{
	if (m_rbOpenOldProject.GetCheck())
		GetPropSheet() -> m_rgOpenMode = PROJECTOPENMODE_OpenExistend;
	else if (m_rbOpenLast.GetCheck())
		GetPropSheet() -> m_rgOpenMode = PROJECTOPENMODE_OpenMRU;
	else {
		ASSERT(m_rbCreateNew.GetCheck());
		GetPropSheet() -> m_rgOpenMode = PROJECTOPENMODE_CreateNew;
	}
	return GetPropSheet() -> GetOpenMode();
}

///////////////////////////////////////////////////////////////////////////////
// Knöpfchen richten
void CWelcomePage::AdjustButtons(void)
{
CPropertySheet *pSheet = (CPropertySheet *)GetParent();

	ASSERT(NULL != pSheet);

DWORD dwBttns = 0;

	if (PROJECTOPENMODE_OpenExistend == m_iOpenMode || 
		PROJECTOPENMODE_OpenMRU == m_iOpenMode) 
	{
		dwBttns = PSWIZB_FINISH;
	}
	else if (PROJECTOPENMODE_CreateNew == m_iOpenMode)
		dwBttns = PSWIZB_NEXT;
	else
		ASSERT(m_iOpenMode != PROJECTOPENMODE_Unknown);

	pSheet -> SetWizardButtons (dwBttns);
}

///////////////////////////////////////////////////////////////////////////////
// Dateinamen verkürzen, damit er sicher ins CStatic reinpaßt
LPSTR ShortenPath (LPSTR cbBuffer, int iMaxLen)
{
	ASSERT(iMaxLen > 4);

// die Übergebene Zeichenkette hat noch das RegistryFormat: "Pfad,0"
char *pT = strrchr (cbBuffer, ',');

	if (NULL != pT) *pT = '\0';		// ",0" abschneiden

// jetzt analysieren und evtl verkürzen
int iLen = strlen (cbBuffer);

	if (iLen <= iMaxLen) 
		return cbBuffer;		// Pfad ist kurz genug

	if (iLen > 4) {
	char *cptr = strchr (cbBuffer + iLen - min(iLen, iMaxLen) + 4, '\\');
	char *cptr1 = strchr (cbBuffer, '\\');

		if (NULL == cptr) cptr = strrchr (cbBuffer, '\\');
		if (NULL != cptr && NULL != cptr1 && cptr > cptr1) {
		int iLenLead = cptr1-cbBuffer;
		int iLenTrail = strlen (cptr);

			if (iLenTrail+iLenLead+4 < iMaxLen) {
			char *pT = strchr (cptr1+1, '\\');
			char *pPrev = cptr1;

				iLenLead = pT-cbBuffer;
				while (NULL != pT && cptr > cptr1 && 
					   iLenTrail+iLenLead+4 < iMaxLen) 
				{
					pPrev = pT;
					iLenLead = pT-cbBuffer;

					pT = strchr (pPrev+1, '\\');
				} 
				cptr1 = pPrev;
			}
			if (NULL != cptr1) *cptr1 = '\0';

		// Zeile neu formatieren
		char cbOut[_MAX_PATH+5];

			wsprintf (cbOut, "%s\\...%s", cbBuffer, cptr);
			strcpy (cbBuffer, cbOut);
		}
	}
	return cbBuffer;
}

///////////////////////////////////////////////////////////////////////////////
// Liefert Anzahl der Zeichen des aktuellen Fonts, die auf einer Zeile
// des gegebenen Fensters Platz haben
int CalcMaxCharCount (CWnd &rField)
{
CDC *pdcT = rField.GetDC();
TEXTMETRIC tm;

	ASSERT(NULL != pdcT);
	pdcT -> GetTextMetrics(&tm);
	rField.ReleaseDC (pdcT);

CRect rc;

	rField.GetClientRect (&rc);
	return (rc.right-rc.left) / tm.tmAveCharWidth;
}
