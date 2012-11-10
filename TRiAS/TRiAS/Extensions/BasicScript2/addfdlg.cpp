// addfdlg.cpp : implementation file
//

#include "bscriptp.hxx"
#include "bscript.h"

#include "tmplman.h"
#include "addfdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void	ErrorMessage(HWND h, LPCSTR lpcstrMessage);
BOOL	LoadString(CString & str, int IDS);

/////////////////////////////////////////////////////////////////////////////
// CAddFunctionDlg dialog


CAddFunctionDlg::CAddFunctionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddFunctionDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddFunctionDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}
CAddFunctionDlg::~CAddFunctionDlg()
{
}


void CAddFunctionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddFunctionDlg)
	DDX_Control(pDX, IDC_CHECKNOTIFICATION, m_chckNotification);
	DDX_Control(pDX, IDC_COMBONOTIFICATION, m_cbxNotification);
	DDX_Control(pDX, IDOK, m_bttnOK);
	DDX_Control(pDX, IDC_CHECKFUNCTION, m_chckFunction);
	DDX_Control(pDX, IDC_TYP, m_ctrlTyp);
	DDX_Control(pDX, IDC_DEKLARATION, m_ctrlDeclaration);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddFunctionDlg, CDialog)
	//{{AFX_MSG_MAP(CAddFunctionDlg)
	ON_BN_CLICKED(IDC_CHECKFUNCTION, OnCheckfunction)
	ON_EN_CHANGE(IDC_DEKLARATION, OnChangeDeklaration)
	ON_EN_CHANGE(IDC_TYP, OnChangeTyp)
	ON_BN_CLICKED(IDC_CHECKNOTIFICATION, OnChecknotification)
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_COMBONOTIFICATION, OnSelchangeCombonotification)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddFunctionDlg message handlers

BOOL CAddFunctionDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	SetButtons(false);
	FillComboBox();

	return false;  // return FALSE if you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CAddFunctionDlg::OnOK() 
{
	if (false == SetButtons())
		return;
	CDialog::OnOK();
}
void CAddFunctionDlg::OnCheckfunction() 
{
	SetButtons(true);
}
void CAddFunctionDlg::OnChangeDeklaration() 
{
	SetButtons();	
}

void CAddFunctionDlg::OnChangeTyp() 
{
	SetButtons();	
}

void CAddFunctionDlg::OnChecknotification() 
{
	SetButtons(false);
}

void CAddFunctionDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	SetTemplatePieces();
	DeleteTemplates();
}

void CAddFunctionDlg::OnSelchangeCombonotification() 
{
}

BOOL CAddFunctionDlg::SetButtons(BOOL fCheck)
{
	m_bttnOK.EnableWindow(true);			

	if (1 == m_chckNotification.GetCheck())
	{
		m_ctrlTyp.EnableWindow(false);
		m_ctrlDeclaration.EnableWindow(false);
		m_chckFunction.EnableWindow(false);
		m_cbxNotification.EnableWindow(true);
		return true;
	}
	m_cbxNotification.EnableWindow(false);
	m_ctrlTyp.EnableWindow(true);
	m_ctrlDeclaration.EnableWindow(true);
	m_chckFunction.EnableWindow(true);

	if (1 == m_chckFunction.GetCheck())
	{
		if (fCheck) m_ctrlTyp.SetFocus(); 
		m_ctrlTyp.EnableWindow(true);
		CString strType;
		m_ctrlTyp.GetWindowText(strType);
		if (strType.IsEmpty()) {
			m_bttnOK.EnableWindow(false);			
		}
	}
	else 
	{
		m_ctrlTyp.EnableWindow(false);
		m_ctrlDeclaration.SetFocus();
	}

	CString strDecl;
	m_ctrlDeclaration.GetWindowText(strDecl);
	if (strDecl.IsEmpty()) {
		m_bttnOK.EnableWindow(false);			
		return false;
	}

	return true;
}

HRESULT CAddFunctionDlg::FillComboBox()
{
	HRESULT hr = NOERROR;
	int iResID = IDR_NOTIFCLOSING;
	try
	{
		while (iResID != IDR_NOTIFEND)
		{
			CTemplateManagement *pTM = new CTemplateManagement;
			THROW_FAILED_HRESULT(pTM -> Load(iResID, "Notification")); 

			char str[MAXSTRLENGTH];
			THROW_FAILED_HRESULT(pTM -> GetName(str, MAXSTRLENGTH));
			int i = m_cbxNotification.AddString(str);
			
			if (i == CB_ERRSPACE) _com_issue_error(E_OUTOFMEMORY);
			if (i == CB_ERR) _com_issue_error(E_FAIL);

			m_cbxNotification.SetItemData(i, (DWORD) pTM);

			iResID++;
		}
	}
	catch(_com_error& e)
	{
		hr = _COM_ERROR(e);
	}
	return hr;

}

HRESULT CAddFunctionDlg::MakeTemplate(CTemplateManagement **ppTM)
{
	ASSERT(ppTM);
	if (NULL == ppTM) return E_POINTER;
	*ppTM = NULL;

	try
	{
		*ppTM = new CTemplateManagement;
		if (NULL == *ppTM) _com_issue_error(E_POINTER);
		// Item erzeugen und Templateelemente setzen
		CString strDecl; m_ctrlDeclaration.GetWindowText(strDecl);
		if (strDecl.IsEmpty()) _com_issue_error(E_INVALIDARG);
		// sind Klammern vorhanden
		HRESULT hr = ValidDecl(strDecl);
		if (FAILED(hr))
		{
			MessageDeclError();
			_com_issue_error(hr);
		}
		// Typ muss nicht vorhanden sein
		CString strTyp; m_ctrlTyp.GetWindowText(strTyp);
		if (strTyp.IsEmpty()) strTyp = "Void";		
		// Für Funktionstemplate schaffen
		char strFunctionTemplate[MAXSTRLENGTH];
		strcpy(strFunctionTemplate, strTyp);
		strcat(strFunctionTemplate, ",");
		strcat(strFunctionTemplate, strDecl);
		THROW_FAILED_HRESULT((*ppTM) -> Set(strFunctionTemplate));
	}
	catch(_com_error& e)
	{
		return _COM_ERROR(e);
	}
	return S_OK;
}
HRESULT CAddFunctionDlg::ValidDecl(LPCSTR lpcstr)
{
	// keine Klammern ?
	LPSTR lpstr = (LPSTR)lpcstr;
	BOOL fFound = false;

	while(*lpstr) 
	{// mindestens ein Buchstabe
		lpstr++;
		if ('(' != *lpstr) continue;
		fFound = true;
		break;
	}
	if (false == fFound) return E_INVALIDARG;

	fFound = false;
	
	while(*lpstr) 
	{
		lpstr++;
		// Es muß DANN "Klammer zu" da sein
		if (')' != *lpstr) continue;
		fFound = true;
		break;
	}
	if (false == fFound) return E_INVALIDARG;
	return S_OK;
}
HRESULT CAddFunctionDlg::SetTemplatePieces()
{
	HRESULT hr = NOERROR;
	CTemplateManagement *pTM = NULL;
	BOOL fDelete = false;
	try
	{
		// Wenn Notification, dann alle Funktionselemente aus diesem Item holen
		if (1 == m_chckNotification.GetCheck()) 
		{	// Istein Text im EditCtrl ?
			CString str;
			m_cbxNotification.GetWindowText(str);
			if (str.IsEmpty()) _com_issue_error(E_INVALIDARG);
			// Wenn je, liefere den Index
			int iFind = m_cbxNotification.FindString(-1, str);
			if (CB_ERR == iFind) _com_issue_error(E_FAIL);
			// Den Templtemenager geben lassen
			DWORD dw = m_cbxNotification.GetItemData(iFind);
			if (CB_ERR == dw) _com_issue_error(E_FAIL);
			pTM = (CTemplateManagement *)dw;
		} 
		else 
		{
			fDelete = true;
			THROW_FAILED_HRESULT(MakeTemplate(&pTM));
		}

		char str	[MAXSTRLENGTH]; *str = '\0';
		char strType[MAXSTRLENGTH];	*strType = '\0';
		char strPar [MAXSTRLENGTH];	*strPar = '\0';
		char strName[MAXSTRLENGTH];	*strName = '\0';
		char strComment[MAXSTRLENGTH]; *strComment = '\0';

		THROW_FAILED_HRESULT(pTM -> GetComment(strComment, MAXSTRLENGTH));
		THROW_FAILED_HRESULT(pTM -> GetDeclaration(str, MAXSTRLENGTH));
		THROW_FAILED_HRESULT(pTM -> GetParams(strPar, MAXSTRLENGTH));
		THROW_FAILED_HRESULT(pTM -> GetName(strName, MAXSTRLENGTH));
		THROW_FAILED_HRESULT(pTM -> GetType(strType, MAXSTRLENGTH));

		m_strTyp = strType;		
		m_strParams = strPar;
		m_strDeclaration = str;
		m_strName = strName;
		m_strComment = strComment;
	}
	catch (_com_error& e)
	{
		hr = _COM_ERROR(e);
	}
	if (fDelete) DELETE_OBJ(pTM);
	return hr;
}
HRESULT CAddFunctionDlg::DeleteTemplates()
{
	int iCnt = m_cbxNotification.GetCount();
	for (int i = 0; i < iCnt; i++) 
	{
		CTemplateManagement *pTM = NULL;
		pTM = (CTemplateManagement *)m_cbxNotification.GetItemData(i);
		DELETE_OBJ(pTM);
	}
	return S_OK;
}

void CAddFunctionDlg::MessageDeclError()
{
	CString str; LoadString(str, IDS_ERRORDECL);
	ErrorMessage(this->m_hWnd, str);
}
