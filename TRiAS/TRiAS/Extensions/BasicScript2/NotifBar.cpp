// NotifBar.cpp : implementation file
//

#include "bscriptp.hxx"
#include "bscript.h"

#include "tmplman.h"
#include "NotifBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNotifBar dialog

void CNotifBar::DoDataExchange(CDataExchange* pDX)
{
	CDialogBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNotifBar)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNotifBar, CDialogBar)
	//{{AFX_MSG_MAP(CNotifBar)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, OnToolTipText)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, OnToolTipText)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNotifBar message handlers
#define _countof(array) (sizeof(array)/sizeof(array[0]))

bool CNotifBar::OnToolTipText(UINT, NMHDR* pNMHDR, LRESULT* pResult)
{
	ASSERT(pNMHDR->code == TTN_NEEDTEXTA || pNMHDR->code == TTN_NEEDTEXTW);

// allow top level routing frame to handle the message
	if (GetRoutingFrame() != NULL)
		return FALSE;

	*pResult = 0;

// need to handle both ANSI and UNICODE versions of the message
TOOLTIPTEXTA* pTTTA = (TOOLTIPTEXTA*)pNMHDR;
TOOLTIPTEXTW* pTTTW = (TOOLTIPTEXTW*)pNMHDR;
CString strTipText ("");

	/*if (m_pMainFrm -> ShowToolTips()) */{		// nur wenn Tooltips angezeigt werden sollen
	UINT nID = pNMHDR->idFrom;

		if (pNMHDR->code == TTN_NEEDTEXTA && (pTTTA->uFlags & TTF_IDISHWND) ||
			pNMHDR->code == TTN_NEEDTEXTW && (pTTTW->uFlags & TTF_IDISHWND))
		{
			// idFrom is actually the HWND of the tool
			nID = ((UINT)(WORD)::GetDlgCtrlID((HWND)nID));
		}

		if (nID != 0) {	// will be zero on a separator
		// this is the command id, not the button index
		CString str;
		
		// don't handle the message if no string resource found
			if (str.LoadString (nID) == 0)
				return FALSE;
			AfxExtractSubString(strTipText, str, 1, '\n');
		}
	}

#ifndef _UNICODE
	if (pNMHDR->code == TTN_NEEDTEXTA)
		lstrcpyn(pTTTA->szText, strTipText, _countof(pTTTA->szText));
	else
		_mbstowcsz(pTTTW->szText, strTipText, _countof(pTTTW->szText));
#else
	if (pNMHDR->code == TTN_NEEDTEXTA)
		_wcstombsz(pTTTA->szText, strTipText, _countof(pTTTA->szText));
	else
		lstrcpyn(pTTTW->szText, strTipText, _countof(pTTTW->szText));
#endif

// bring the tooltip window above other popup windows
	::SetWindowPos(pNMHDR->hwndFrom, HWND_TOP, 0, 0, 0, 0,
		SWP_NOACTIVATE|SWP_NOSIZE|SWP_NOMOVE);
	return true;    // message was handled
}

/////////////////////////////////////////////////////////////////////////////
// Füllen der Combo
HRESULT CNotifBar::FillCombo()
{
CComboBox* pCBox = (CComboBox*)GetDlgItem(IDC_COMBONOTIFICATION);

	ASSERT(pCBox);
	if (NULL == pCBox) return E_POINTER;

HRESULT hr = NOERROR;
int iResID = IDR_NOTIFCLOSING;
CTemplateManagement *pTM = NULL;

	COM_TRY {
		while (iResID != IDR_NOTIFEND) {
			pTM = new CTemplateManagement;
			THROW_FAILED_HRESULT(pTM -> Load (iResID, "Notification")); 

		char str[MAXSTRLENGTH];
		
			THROW_FAILED_HRESULT(pTM -> GetName (str, MAXSTRLENGTH));

		int i = pCBox -> AddString(str);
			
			if (i == CB_ERRSPACE) _com_issue_error(E_OUTOFMEMORY);
			if (i == CB_ERR) _com_issue_error(E_FAIL);

			pCBox -> SetItemData(i, (DWORD) pTM);
			pTM = NULL;
			iResID++;
		}
	} COM_CATCH_OP(delete pTM);
	return S_OK;
}

BOOL CNotifBar::OnSelChange (
	CString &strType, CString &strDecl, CString &strName, CString &strParams, CString &strComment)
{
	if (FAILED(SetTemplatePieces()))
		return false;

	return GetItems(strType, strDecl, strName, strParams, strComment);
}

BOOL CNotifBar::Create (CWnd* pParent)
{
	if (!CDialogBar::Create(pParent, IDD_TOOLBARNOTIFICATION,
		CBRS_TOP|CBRS_TOOLTIPS|CBRS_FLYBY, IDD_TOOLBARNOTIFICATION))
	{
		TRACE0("Failed to create DlgBar\n");
		return false;      // fail to create
	}
	return SUCCEEDED(FillCombo());
}

BOOL CNotifBar::OnDestroy ()
{
	CComboBox* pCBox = (CComboBox*)GetDlgItem(IDC_COMBONOTIFICATION);
	ASSERT(pCBox);
	if (NULL == pCBox) return FALSE;
	
int iCnt = pCBox -> GetCount();

	for (int i = 0; i < iCnt; i++) {
	CTemplateManagement *pTM = (CTemplateManagement *)pCBox -> GetItemData(i);

		DELETE_OBJ(pTM);
	}
	return TRUE;
}

HRESULT CNotifBar::SetTemplatePieces()
{
CComboBox* pCBox = (CComboBox *)GetDlgItem(IDC_COMBONOTIFICATION);

	ASSERT(pCBox);
	if (NULL == pCBox) return E_POINTER;
	
HRESULT hr = NOERROR;
CTemplateManagement *pTM = NULL;

	COM_TRY {
	// Wenn Notification, dann alle Funktionselemente aus diesem Item holen
	// Ist ein Text im EditCtrl ?
	CString str;
	int iFind = pCBox -> GetCurSel();

		if (CB_ERR == iFind) _com_issue_error(E_FAIL);

	// Den Templtemenager geben lassen
	DWORD dw = pCBox -> GetItemData(iFind);

		if (CB_ERR == dw) _com_issue_error(E_FAIL);
		pTM = (CTemplateManagement *)dw;

	char strDecl[MAXSTRLENGTH]; *strDecl = '\0';
	char strType[MAXSTRLENGTH];	*strType = '\0';
	char strPar [MAXSTRLENGTH];	*strPar = '\0';
	char strName[MAXSTRLENGTH];	*strName = '\0';
	char strComment[MAXSTRLENGTH]; *strComment = '\0';

		THROW_FAILED_HRESULT(pTM -> GetComment(strComment, MAXSTRLENGTH));
		THROW_FAILED_HRESULT(pTM -> GetDeclaration(strDecl, MAXSTRLENGTH));
		THROW_FAILED_HRESULT(pTM -> GetParams(strPar, MAXSTRLENGTH));
		THROW_FAILED_HRESULT(pTM -> GetName(strName, MAXSTRLENGTH));
		THROW_FAILED_HRESULT(pTM -> GetType(strType, MAXSTRLENGTH));

		m_strType = strType;		
		m_strParams = strPar;
		m_strDeclaration = strDecl;
		m_strName = strName;
		m_strComment = strComment;

	} COM_CATCH;
	return S_OK;
}

BOOL CNotifBar::GetItems (
	CString &strType, CString &strDecl, CString &strName, CString &strParams, CString &strComment)
{
	strType = m_strType;		
	strParams = m_strParams;
	strDecl = m_strDeclaration;
	strName = m_strName;
	strComment = m_strComment;
	return true;
}
