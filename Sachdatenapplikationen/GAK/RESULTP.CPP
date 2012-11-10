// ResultP.cpp : implementation file
//

#include "stdafx.h"
#include "gak.h"
#include "ResultP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResultParam property page

IMPLEMENT_DYNCREATE(CResultParam, CPropertyPage)

CResultParam::CResultParam() : CPropertyPage(CResultParam::IDD)
{
	//{{AFX_DATA_INIT(CResultParam)
	m_strQueryName = _T("");
	m_strInfo = _T("");
	//}}AFX_DATA_INIT
	m_pQueryDef = NULL;
}

CResultParam::~CResultParam()
{
}

void CResultParam::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CResultParam)
	DDX_Text(pDX, IDT_QUERY_NAME, m_strQueryName);
	DDX_Text(pDX, IDE_RESULT, m_strInfo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CResultParam, CPropertyPage)
	//{{AFX_MSG_MAP(CResultParam)
	ON_COMMAND(ID_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResultParam message handlers

BOOL CResultParam::OnSetActive() 
{
// TODO: Add your specialized code here and/or call the base class
//	prüfe Parameter
	ASSERT (NULL != m_pQueryDef && m_pQueryDef -> IsOpen ());

	int iCnt = m_pQueryDef -> GetParameterCount();
	
//	zuerst Namen der Abfrage ausgeben
	AfxFormatString1 (m_strQueryName, IDS_QUERY_PARAM_TITLE, m_pQueryDef->GetName());

//	Parameter Text zusammenbauen
	CString strVal, strJa, strNein;
	CDaoParameterInfo Info;
	VERIFY (strJa.LoadString (IDS_JA));
	VERIFY (strNein.LoadString (IDS_NEIN));
	m_strInfo.Empty ();
	for (int iIndex = 0; iIndex < iCnt; iIndex++)
	{
	//	lese Parameterwert
		m_pQueryDef -> GetParameterInfo (iIndex, Info, AFX_DAO_SECONDARY_INFO);

	//	zuerst Namen des Parameters anhängen
		m_strInfo += Info.m_strName + ": ";

	//	jetzt eingegebenen Wert lesen
		GetQueryParamValue (Info, strVal);
		if (Info.m_nType == dbBoolean)
		{
			if (strVal == ("0"))
				m_strInfo += strNein;
			else
				m_strInfo += strJa;
		}
		else
			m_strInfo += strVal;

		m_strInfo += '\r';
		m_strInfo += '\n';
	}
	
	UpdateData (FALSE);

//	Wizard-Button setzen
	CPropertySheet *pSheet = (CPropertySheet*)GetParent ();
	ASSERT (NULL != pSheet);
	ASSERT_VALID (pSheet);

	DWORD dwFlags =  pSheet -> GetActiveIndex () > 0 ? PSWIZB_BACK : 0;
	pSheet -> SetWizardButtons(dwFlags|PSWIZB_FINISH);
	return CPropertyPage::OnSetActive();
}

void CResultParam :: OnHelp ()
{
	AfxGetApp () -> WinHelp (IDD+HelpDialogOffset);
}
