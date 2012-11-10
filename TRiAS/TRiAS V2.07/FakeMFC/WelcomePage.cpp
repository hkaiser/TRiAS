// WelcomePage.cpp : implementation file
//

#include "fakemfcp.hxx"
#include "fakemfc.h"

#include <registrx.hxx>

#include "WelcomePage.h"
#include "Strings.h"

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
	m_iOpenMode = OPENMODE_Unknown;

// Caption den aktuellen Erfordernissen anpassen
	TRY {
	CString strOrgCap;

		VERIFY(strOrgCap.LoadString (IDS_WELCOMEDLG));
		m_strCaption.Format (strOrgCap, g_cbTRiAS);
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
	DDX_Control(pDX, IDC_LASTPROJECT, m_ftMRUProject);
	DDX_Control(pDX, IDC_DONTSHOWFURTHER, m_cbDontShowFurther);
	DDX_Control(pDX, IDC_OPENOLDPROJECT, m_rbOpenOldProject);
	DDX_Control(pDX, IDC_OPENMRUPROJECT, m_rbOpenLast);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWelcomePage, CPropertyPage)
	//{{AFX_MSG_MAP(CWelcomePage)
	ON_BN_CLICKED(IDC_CREATENEWPROJECT, OnCreateNewProject)
	ON_BN_CLICKED(IDC_OPENMRUPROJECT, OnOpenMruProject)
	ON_BN_CLICKED(IDC_OPENOLDPROJECT, OnOpenOldProject)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWelcomePage message handlers

BOOL CWelcomePage::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
// Controls initialisieren
bool fReturn = true;

	{
	CCurrentUser regMRU (g_cbMRUFiles);
	TCHAR cbBuffer[_MAX_PATH+5];
	ULONG ulLen = sizeof(cbBuffer);

		if (!regMRU.GetSubSZ (g_cbLastFile, cbBuffer, ulLen)) {
			m_rbOpenLast.EnableWindow (false);

			m_iOpenMode = OPENMODE_OpenExistend;			// erster RadioButton
			m_rbOpenOldProject.SetCheck (true);
			m_rbOpenLast.SetCheck (false);
			m_ftMRUProject.SetWindowText (_T(""));
		} else {
			m_iOpenMode = OPENMODE_OpenMRU;					// zweiter RadioButton
			m_rbOpenLast.SetCheck (true);
			m_rbOpenOldProject.SetCheck (false);
			m_rbOpenLast.SetFocus();

		CString strT (ShortenPath (cbBuffer, CalcMaxCharCount(m_ftMRUProject)));

			strT.TrimRight();
			strT = _T("(") + strT + _T(")");
			m_ftMRUProject.SetWindowText (strT);
			fReturn = false;
		}
	}
	AdjustButtons();
	return fReturn; // return TRUE unless you set the focus to a control
					// EXCEPTION: OCX Property Pages should return FALSE
}

LRESULT CWelcomePage::OnWizardNext() 
{
	ASSERT(OPENMODE_CreateNew == m_iOpenMode);
	
	return CPropertyPage::OnWizardNext();
}

BOOL CWelcomePage::OnWizardFinish() 
{
// diesen Dialog wieder anzeigen?
	{
	CCurrentUser regMRU (g_cbMRUFiles, true);

		regMRU.SetDWORD (g_cbShowOpenWizard, m_cbDontShowFurther.GetCheck());
	}

// Ausführen der gewünschten Aktion
CWnd *pWnd = g_pTE -> MWind();

	ASSERT(NULL != pWnd);

// entsprechende MenuKommandos in TRiAS auslösen
	switch (m_iOpenMode) {
	case OPENMODE_OpenExistend:		// OpenProject
		pWnd -> PostMessage (WM_COMMAND, IDM_OPEN);
		break;

	case OPENMODE_OpenMRU:		// OpenMRUProject
		pWnd -> PostMessage (WM_COMMAND, IDM_OPENOLD1);
		break;

	case OPENMODE_CreateNew:		// CreateNewProject
		ASSERT(OPENMODE_CreateNew != m_iOpenMode);	// darf nicht passieren
		break;
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

CWelcomePage::OPENMODE CWelcomePage::RetrieveOpenMode (void)
{
	if (m_rbOpenOldProject.GetCheck())
		return CWelcomePage::OPENMODE_OpenExistend;
	if (m_rbOpenLast.GetCheck())
		return CWelcomePage::OPENMODE_OpenMRU;

	return CWelcomePage::OPENMODE_CreateNew;
}

///////////////////////////////////////////////////////////////////////////////
// Knöpfchen richten
void CWelcomePage::AdjustButtons(void)
{
CPropertySheet *pSheet = (CPropertySheet *)GetParent();

	ASSERT(NULL != pSheet);

DWORD dwBttns = 0;

	if (OPENMODE_OpenExistend == m_iOpenMode || 
		OPENMODE_OpenMRU == m_iOpenMode) 
	{
		dwBttns = PSWIZB_FINISH;
	}
	else if (OPENMODE_CreateNew == m_iOpenMode)
		dwBttns = PSWIZB_NEXT;
	else
		ASSERT(m_iOpenMode != OPENMODE_Unknown);

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
