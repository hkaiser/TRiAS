// ErzInfo.cpp : implementation file
//

#include "stdafx.h"
#include "res.h"			//	Resource-Konstanten
#include "ErzInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CErzInfo dialog


CErzInfo::CErzInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CErzInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CErzInfo)
	m_strAnfOrt = _T("");
	m_strAnf = _T("");
	m_strBranche = _T("");
	m_strFax = _T("");
	m_strPartner = _T("");
	m_strTel = _T("");
	m_strFirma = _T("");
	m_strStrasse = _T("");
	//}}AFX_DATA_INIT
}


void CErzInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CErzInfo)
	DDX_Text(pDX, IDT_ANF_ORT, m_strAnfOrt);
	DDX_Text(pDX, IDT_ANF_STELLE, m_strAnf);
	DDX_Text(pDX, IDT_BRANCHE, m_strBranche);
	DDX_Text(pDX, IDT_FAX, m_strFax);
	DDX_Text(pDX, IDT_PARTNER, m_strPartner);
	DDX_Text(pDX, IDT_TEL, m_strTel);
	DDX_Text(pDX, IDT_FIRMA, m_strFirma);
	DDX_Text(pDX, IDT_STRASSE, m_strStrasse);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CErzInfo, CDialog)
	//{{AFX_MSG_MAP(CErzInfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CErzInfo message handlers

BOOL CErzInfo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CString strFormat, strCaption;
	GetWindowText (strFormat);
	ASSERT (!m_strErzNr.IsEmpty ());
	strCaption.Format (strFormat, m_strErzNr);
	SetWindowText (strCaption);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

