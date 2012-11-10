// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 23.08.2002 09:52:45 
//
// @doc
// @module SelectObjPropsToExport.cpp | Definition of the <c CSelectObjPropsToExport> class

#include "stdafx.h"
#include "ExportImpl.h"

#include "SelectObjPropsToExport.h"
#include "ExportUtil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// CSelectObjPropsToExport dialog

/*static*/ 
CSelectObjPropsToExport* CSelectObjPropsToExport::CreateInstance (LPCSTR pcCaption)
{
	CSelectObjPropsToExport *pCfgDlg = NULL;
	COM_TRY {
	// Dialog erzeugen
		pCfgDlg = new CSelectObjPropsToExport();

	// Caption setzen
		pCfgDlg -> m_strCaption = pcCaption;
		pCfgDlg -> m_psp.pszTitle = pCfgDlg -> m_strCaption;
		pCfgDlg -> m_psp.dwFlags |= PSP_USETITLE;

	} COM_CATCH_OP_RETURN(delete pCfgDlg, NULL);
	return pCfgDlg; 
}

CSelectObjPropsToExport::CSelectObjPropsToExport() :
	CPropertyPage(CSelectObjPropsToExport::IDD),
	m_tcObjProps(IncludeObjProp, true, true)
{
	//{{AFX_DATA_INIT(CSelectObjPropsToExport)
	m_strDesc = _T("");
	//}}AFX_DATA_INIT
	m_dwFlags = 0;
}


void CSelectObjPropsToExport::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelectObjPropsToExport)
	DDX_Control(pDX, IDC_OBJECTPROPERTIES, m_tcObjProps);
	DDX_Control(pDX, IDC_STATIC_DESC, m_sepDesc);
	DDX_Text(pDX, IDC_OBJPROP_DESCRIPTION, m_strDesc);
	//}}AFX_DATA_MAP
}

///////////////////////////////////////////////////////////////////////////////
// 
void CSelectObjPropsToExport::AdjustSheetButtons()
{
CPropertySheet *pSheet = (CPropertySheet *)GetParent();

	ASSERT(NULL != pSheet);	

DWORD dwBttns = 0;

	if (!(m_dwFlags & ADDPAGES_FIRSTPAGE))
		dwBttns = PSWIZB_BACK;			// nicht erste Seite

	if (!GetDisableNextPage()) {
		if (m_dwFlags & ADDPAGES_LASTPAGE) 
			dwBttns |= PSWIZB_FINISH;	// letzte Seite
		else 
			dwBttns |= PSWIZB_NEXT;		// nicht letzte Seite
	} else if (m_dwFlags & ADDPAGES_LASTPAGE)
		dwBttns |= PSWIZB_DISABLEDFINISH;

	pSheet -> SetWizardButtons(dwBttns);
}

BOOL CSelectObjPropsToExport::GetDisableNextPage() 
{
	// TODO: return TRUE, if 'Next >' - button should be disabled
	return (0 == m_tcObjProps.CountSelectedItems()) ? TRUE : FALSE;
}

HRESULT CSelectObjPropsToExport::GetObjectProperty (IObjectProperty **ppIObjProp)
{
// Beschreibungstext setzen
CString strObjProp, strObjPropFull;

	if (S_OK == m_tcObjProps.GetSelectedObjProp(strObjProp, &strObjPropFull)) {
	// derzeit selektierte Objekteigenschaft näher beschreiben
	WObjectProps Props (m_tcObjProps.GetObjectProps());
	WEnumObjProps Enum;
	WObjectProperty ObjProp;

		if (SUCCEEDED(Props -> EnumObjectProps(Enum.ppi())) &&
			SUCCEEDED(Enum -> FindByName(strObjPropFull, ppIObjProp)))
		{
			return S_OK;
		}
	}
	return S_FALSE;
}

BEGIN_MESSAGE_MAP(CSelectObjPropsToExport, CPropertyPage)
	//{{AFX_MSG_MAP(CSelectObjPropsToExport)
	ON_NOTIFY(TVN_CHECKSTATECHANGED, IDC_OBJECTPROPERTIES, OnCheckStateChangedObjectproperties)
	ON_NOTIFY(TVN_SELCHANGED, IDC_OBJECTPROPERTIES, OnSelchangedObjectproperties)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////////////
// CSelectObjPropsToExport message handlers

BOOL CSelectObjPropsToExport::OnInitDialog() 
{
	CDialog::OnInitDialog();
	COM_TRY {
	// Liste der Objekteigenschaften initialisieren
	WObjectProps Props;

		GetObjectProps (Props.ppi());
		m_tcObjProps.Init (Props, m_lstSelObjProps);

	} COM_CATCH_RETURN(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CSelectObjPropsToExport::OnSetActive() 
{
	AdjustSheetButtons();
	return CPropertyPage::OnSetActive();
}

LRESULT CSelectObjPropsToExport::OnWizardNext()
{
	m_tcObjProps.GetSelectedObjProps(m_lstSelObjProps);
	return CPropertyPage::OnWizardNext();
}

BOOL CSelectObjPropsToExport::OnWizardFinish()
{
	m_tcObjProps.GetSelectedObjProps(m_lstSelObjProps);
	return CPropertyPage::OnWizardFinish();
}

///////////////////////////////////////////////////////////////////////////////
// Reaktion auf Nutzerinteraktion
void CSelectObjPropsToExport::OnCheckStateChangedObjectproperties(NMHDR* pNMHDR, LRESULT* pResult) 
{
	AdjustSheetButtons();
	*pResult = 0;
}

void CSelectObjPropsToExport::OnSelchangedObjectproperties(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

// erst ans Control schicken
	m_tcObjProps.OnSelchanged(pNMHDR, pResult);

// Beschreibungstext setzen
WObjectProperty ObjProp;

	m_strDesc.Empty();
	if (S_OK == GetObjectProperty(ObjProp.ppi())) {
	// derzeit selektierte Objekteigenschaft näher beschreiben
	char cbBuffer[_MAX_PATH];
	
		if (SUCCEEDED(ObjProp -> HelpInfo(cbBuffer, sizeof(cbBuffer), NULL, NULL)))
			m_strDesc = cbBuffer;
	} 

// Knöpfchen richten
	UpdateData(FALSE);
	AdjustSheetButtons();
	
	*pResult = 0;
}
