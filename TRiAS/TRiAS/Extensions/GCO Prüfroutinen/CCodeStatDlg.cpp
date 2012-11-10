// $Header: $
// Copyright© 1999-2001 VNS GmbH Potsdam, All rights reserved
// Created: 04.12.2002 09:44:34
//
// @doc
// @module CCodeStatDlg.cpp | Implementation of the <c CCCodeStatDlg> class

#include "stdafx.h"

#include <TRiASHelper.h>
#include <xtsnguid.h>

#include "errorcode.h"
#include "LineTools.h"
#include "LineToolsUtil.h"

#include <Errcodes.hxx>
#include <errinstx.hxx>

#include "CCodeStatDlg.h"

#include <Xtensnn.h>
#include "LineToolsExt.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CCCodeStatDlg

CCCodeStatDlg* CCCodeStatDlg::CreateInstance (LPCSTR pcCaption)
{
CCCodeStatDlg *pCfgDlg = NULL;

	COM_TRY {
	// Dialog erzeugen
		pCfgDlg = new CCCodeStatDlg();

	// Caption setzen
		pCfgDlg -> m_strCaption = pcCaption;
		pCfgDlg -> m_psp.pszTitle = pCfgDlg -> m_strCaption;
		pCfgDlg -> m_psp.dwFlags |= PSP_USETITLE;

	} COM_CATCH_OP_RETURN(delete pCfgDlg, NULL);
	return pCfgDlg; 
}

IMPLEMENT_DYNCREATE(CCCodeStatDlg, CPropertyPage)

CCCodeStatDlg::CCCodeStatDlg() 
	: CPropertyPage(CCCodeStatDlg::IDD)
{
	//{{AFX_DATA_INIT(CCCodeStatDlg)
	m_bMultiGeometry = FALSE;
	//}}AFX_DATA_INIT
	m_dwFlags = 0;
	m_iErrorCode = 0;
	m_bShowErrors = 0;
	m_bErrorStatist = 0;
	m_bNoKey = m_bSyntax = m_bDuplicateKey = m_bOtherFeature = m_bDuplGeometry = m_bMultiGeometry = 0;

	m_bODER = 1;
	m_bUND = 0;

}

CCCodeStatDlg::~CCCodeStatDlg()
{
}

void CCCodeStatDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCCodeStatDlg)
		DDX_Control(pDX, IDC_NOKEY, m_btnNoKey);
		DDX_Control(pDX, IDC_SYNTAXERROR, m_btnSyntax);
		DDX_Control(pDX, IDC_DUPLICATEKEY, m_btnDuplicateKey);
		DDX_Control(pDX, IDC_OTHERFEATURE, m_btnOtherFeature);
		DDX_Control(pDX, IDC_DUPLGEOMETRY, m_btnDuplGeometry);
		DDX_Control(pDX, IDC_MULTIGEOMETRY, m_btnMultiGeometry);
		DDX_Control(pDX, IDC_CONTROLCODE, m_nTextLink);
		DDX_Control(pDX, IDC_CONTROLORIGINAL, m_nTextOriginal);
		DDX_Control(pDX, IDC_CONTROLERROR, m_nTextError);
		DDX_Control(pDX, IDC_UNDVERKNUEPFUNG, m_btnUND);
		DDX_Control(pDX, IDC_ODERVERKNUEPFUNG, m_btnODER);
		DDX_Control(pDX, IDC_ERRORSTATIST, m_btnErrorStatist);
		DDX_Control(pDX, IDC_ERRBESCHREIBUNG, m_nTextHelp);
		DDX_Check(pDX, IDC_NOKEY, m_bNoKey);
		DDX_Check(pDX, IDC_SYNTAXERROR, m_bSyntax);
		DDX_Check(pDX, IDC_DUPLICATEKEY, m_bDuplicateKey);
		DDX_Check(pDX, IDC_OTHERFEATURE, m_bOtherFeature);
		DDX_Check(pDX, IDC_DUPLGEOMETRY, m_bDuplGeometry);
		DDX_Check(pDX, IDC_MULTIGEOMETRY, m_bMultiGeometry);
		DDX_Check(pDX, IDC_UNDVERKNUEPFUNG, m_bUND);
		DDX_Check(pDX, IDC_ODERVERKNUEPFUNG, m_bODER);
		DDX_Check(pDX, IDC_ERRORSTATIST, m_bErrorStatist);
		DDX_Text(pDX, IDC_ERRBESCHREIBUNG, m_nDescription);
	//}}AFX_DATA_MAP
}



BEGIN_MESSAGE_MAP(CCCodeStatDlg, CPropertyPage)
	//{{AFX_MSG_MAP(CCCodeStatDlg)
	ON_BN_CLICKED(IDC_NOKEY, OnNokey)
	ON_BN_CLICKED(IDC_SYNTAXERROR, OnSyntaxerror)
	ON_BN_CLICKED(IDC_DUPLICATEKEY, OnDuplicatekey)
	ON_BN_CLICKED(IDC_OTHERFEATURE, OnOtherfeature)
 	ON_BN_CLICKED(IDC_DUPLGEOMETRY, OnDuplgeometry)
	ON_BN_CLICKED(IDC_MULTIGEOMETRY, OnMultigeometry)
	ON_BN_CLICKED(IDC_UNDVERKNUEPFUNG, OnUndverknuepfung)
	ON_BN_CLICKED(IDC_ODERVERKNUEPFUNG, OnOderverknuepfung)
	ON_BN_CLICKED(IDC_ERRORSTATIST, OnErrorstatist)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CCCodeStatDlg::AdjustSheetButtons()
{
//CPropertySheet *pSheet = DYNAMIC_DOWNCAST(CPropertySheet, GetParent());
CPropertySheet *pSheet = (CPropertySheet *) GetParent();

	ASSERT(NULL != pSheet);	

DWORD dwBttns = 0;

	if (!(m_dwFlags & ADDPAGES_FIRSTPAGE))
		dwBttns = PSWIZB_BACK;			// nicht erste Seite

	if (!GetDisableNextPage()) {
		if (m_dwFlags & ADDPAGES_LASTPAGE) 
			dwBttns |= PSWIZB_FINISH;	// letzte Seite
		else 
			dwBttns |= PSWIZB_NEXT;		// nicht letzte seite
	} else if (m_dwFlags & ADDPAGES_LASTPAGE)
		dwBttns |= PSWIZB_DISABLEDFINISH;

	dwBttns |= (!m_iErrorCode) ? PSWIZB_DISABLEDFINISH : PSWIZB_FINISH;

	// FehlerStatistik auswerten
	dwBttns |= (!m_bErrorStatist) ? PSWIZB_DISABLEDFINISH : PSWIZB_FINISH;

	pSheet -> SetWizardButtons(dwBttns);


}
////////////////////////////////////////////////////////////////////////////

BOOL CCCodeStatDlg::GetDisableNextPage()
{
	// TODO: return TRUE, if 'Next >' - button should be disabled

	//return FALSE;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CCCodeStatDlg message handlers

BOOL CCCodeStatDlg::OnSetActive() 
{

	if ( !m_bUseAll) {
		m_bDuplGeometry = FALSE;
		m_bMultiGeometry = FALSE;
		m_btnDuplGeometry.EnableWindow( FALSE);
		m_btnMultiGeometry.EnableWindow( FALSE );
	}

	m_btnErrorStatist.EnableWindow( FALSE);

	if ( m_bShowErrors) {
		m_btnErrorStatist.EnableWindow( TRUE);
	}

	m_btnUND.EnableWindow( TRUE);
	m_btnODER.EnableWindow( TRUE );

	OnSetButton();

	m_btnODER.SetState(m_bODER);
	m_btnUND.SetState(m_bUND);

	USES_CONVERSION;

	m_nTextLink.SetWindowText (W2A(m_bstrGCO));
	m_nTextOriginal.SetWindowText (W2A(m_bstrGCOriginal));
	m_nTextError.SetWindowText (W2A(m_bstrError));

	AdjustSheetButtons();
	return CPropertyPage::OnSetActive();
}

void CCCodeStatDlg::OnSetButton(void) 
{
	m_btnNoKey.SetCheck(m_bNoKey);
	m_btnSyntax.SetCheck(m_bSyntax);
	m_btnDuplicateKey.SetCheck(m_bDuplicateKey);

	m_btnOtherFeature.SetCheck(m_bOtherFeature);
	m_btnDuplGeometry.SetCheck(m_bDuplGeometry);
	m_btnMultiGeometry.SetCheck(m_bMultiGeometry);
	return;

}
void CCCodeStatDlg::OnNokey() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	if ( !m_bNoKey)
		m_iErrorCode = m_iErrorCode | GCS_NOTHING;
	else
		m_iErrorCode = m_iErrorCode & ~GCS_NOTHING;

	UpdateData();

	OnSetErrorCode() ;
	AdjustSheetButtons();

	
}

void CCCodeStatDlg::OnSyntaxerror() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	if ( !m_bSyntax)
		m_iErrorCode = m_iErrorCode | GCS_SYNTAX;
	else
		m_iErrorCode = m_iErrorCode & ~GCS_SYNTAX;

	UpdateData();
	OnSetErrorCode() ;
	AdjustSheetButtons();
	
}

void CCCodeStatDlg::OnDuplicatekey() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	if ( !m_bDuplicateKey)
		m_iErrorCode = m_iErrorCode | GCS_DUPLICATE;
	else
		m_iErrorCode = m_iErrorCode & ~GCS_DUPLICATE;

	UpdateData();
	OnSetErrorCode() ;
	AdjustSheetButtons();

	
}

void CCCodeStatDlg::OnOtherfeature() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	if (!m_bOtherFeature)
		m_iErrorCode = m_iErrorCode | GCS_OTHER;
	else 
		m_iErrorCode = m_iErrorCode & ~GCS_OTHER;

	UpdateData();
	OnSetErrorCode() ;
	AdjustSheetButtons();
	
}

void CCCodeStatDlg::OnDuplgeometry() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen

	if (!m_bDuplGeometry)
		m_iErrorCode = m_iErrorCode | GI_DUPLICATE;
	else
		m_iErrorCode = m_iErrorCode & ~GI_DUPLICATE;

	UpdateData();
	OnSetErrorCode() ;
	AdjustSheetButtons();
	
}
/////////////////////////////////////////////////////////////////////////////////////////////////////

void CCCodeStatDlg::OnMultigeometry() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	if (!m_bMultiGeometry)
		m_iErrorCode = m_iErrorCode | GI_MULTI;
	else
		m_iErrorCode = m_iErrorCode & ~GI_MULTI;

	UpdateData();
	OnSetErrorCode() ;
	AdjustSheetButtons();
	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CCCodeStatDlg ::SetConfigData (CComBSTR strLink, CComBSTR strOriginal,CComBSTR strError, bool bUseAll, bool bShowErrors)
{

	m_bstrGCO = strLink;
	m_bstrGCOriginal = strOriginal;

	m_bstrError = strError;
	m_bUseAll = bUseAll;
	m_bShowErrors = bShowErrors;

	return S_OK;
}
////////////////////////////////////////////////////////////////////////////////////////////////
void CCCodeStatDlg::SetInformation(void)
{
	m_nDescription.Empty();

	m_nTextHelp.SetWindowText (m_nDescription);

	CString sK;

	if (m_bUND ) {	// Nur bestimmte Kombinationen sinnvoll

		sK.LoadString(IDS_UNDBESCHREIBUNG);

		if ( (m_bNoKey + m_bSyntax + m_bDuplicateKey + m_bOtherFeature ) > 1) {
			m_nDescription.Empty();
			m_nTextHelp.SetWindowText (m_nDescription);
			sK.LoadString(IDS_CODEWIDERSPRUCH);
			m_nDescription += sK;
		} else {
//			if (m_bDuplGeometry && ((m_bNoKey + m_bSyntax + m_bDuplicateKey + m_bOtherFeature ) == 1 ))
			if ( ((m_bNoKey + m_bSyntax + m_bDuplicateKey + m_bOtherFeature ) == 1 ))
				m_nDescription += sK;
		}


	} else {
		if ( (m_bNoKey + m_bSyntax + m_bDuplicateKey + m_bOtherFeature ) > 0) {
			sK.LoadString(IDS_ODERBESCHREIBUNG);
			m_nDescription += sK;
		}
	}

	m_nTextHelp.SetWindowText (m_nDescription);


	UpdateData();
}
////////////////////////////////////////////////////////////////////////////
void CCCodeStatDlg::OnSetErrorCode() 
{

	// Beschreibungstexterstellung


	SetInformation();


//	m_bNoKey = m_bSyntax = m_bDuplicateKey = m_bOtherFeature = m_bDuplGeometry = m_bMultiGeometry ;

	if (m_bUND ) {	// Nur bestimmte Kombinationen sinnvoll

		if ( (m_bNoKey + m_bSyntax + m_bDuplicateKey + m_bOtherFeature ) > 1) {


			m_bNoKey = m_bSyntax = m_bDuplicateKey = m_bOtherFeature = 0 ;
			OnSetButton();
			m_iErrorCode = 0;

			if ( (m_bMultiGeometry + m_bDuplGeometry ) == 1) {

				if (m_bMultiGeometry)
					m_iErrorCode = m_iErrorCode | GI_MULTI;

				if (m_bDuplGeometry)
					m_iErrorCode = m_iErrorCode | GI_DUPLICATE;

			}
		}

		if ( (m_bMultiGeometry + m_bDuplGeometry ) > 1) {
			m_bMultiGeometry = m_bDuplGeometry = 0;
			OnSetButton();
			m_iErrorCode = m_iErrorCode & ~GI_MULTI;
			m_iErrorCode = m_iErrorCode & ~GI_DUPLICATE;
		}

	}

}
////////////////////////////////////////////////////////////////////////////////////////////////
void CCCodeStatDlg::OnUndverknuepfung() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen

	m_bUND = m_btnUND.GetState();
	m_bODER = m_btnODER.GetState();

	UpdateData();

	OnSetErrorCode() ;

	AdjustSheetButtons();

	
}

void CCCodeStatDlg::OnOderverknuepfung() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
	m_bUND = m_btnUND.GetState();
	m_bODER = m_btnODER.GetState();

	UpdateData();
	OnSetErrorCode() ;

	AdjustSheetButtons();

	UpdateData();
 }

void CCCodeStatDlg::OnErrorstatist() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	if (!m_bErrorStatist)
		m_bErrorStatist = 1;
	else
		m_bErrorStatist = 0;

	UpdateData();
	OnSetErrorCode() ;
	AdjustSheetButtons();
	
}
