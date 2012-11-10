// txtredlg.cpp : implementation file
//

#include "stdafx.h"

#include "resource.h"
#include "txtredlg.h"
#include "helper.h"              
#include "waitcur.hpp"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


extern CHelper *m_pHelper;
/////////////////////////////////////////////////////////////////////////////
// CTxtReDlg dialog


CTxtReDlg::CTxtReDlg(CWnd* pParent /*=NULL*/, HWND hWnd, HMENU hMenu, CHelper *pHelper)
	: CDialog(CTxtReDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTxtReDlg)
	//}}AFX_DATA_INIT
	m_pHelper = pHelper;
    m_lMCode = 0;
	m_hWnd = hWnd;
	m_rlCBIdent = 0;
	m_hMenu = hMenu;
}

void CTxtReDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTxtReDlg)
	DDX_Control(pDX, IDC_POSPOINTTEXTS, m_cbPosPtTexts);
	DDX_Control(pDX, IDC_LOESCH, m_rObLoesch);
	DDX_Control(pDX, IDC_RENAME, m_rRename);
	DDX_Control(pDX, IDC_CHECK1, m_cRelat);
	DDX_Control(pDX, IDC_COMBO3, m_cbxMCode);
	DDX_Control(pDX, IDC_COMBOPUTOBCL, m_cbxObClList);
	DDX_Control(pDX, IDOK, m_OK);
	DDX_Control(pDX, IDC_RADIO4, m_rText);
	DDX_Control(pDX, IDC_RADIO1, m_rMCode);
	DDX_Control(pDX, IDC_RADIO2, m_rTxtPerm);
	DDX_Control(pDX, IDC_RADIO3, m_rTxtTemp);	
	DDX_Control(pDX, IDC_PUTOBCL, m_cPutObCl);	
	DDX_Control(pDX, IDC_EDIT2, m_eText);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTxtReDlg, CDialog)
	//{{AFX_MSG_MAP(CTxtReDlg)
	ON_BN_CLICKED(IDC_RADIO1, OnRMCode)
	ON_BN_CLICKED(IDC_RADIO2, OnRPerm)
	ON_BN_CLICKED(IDC_RADIO3, OnRTemp)
	ON_BN_CLICKED(IDC_RADIO4, OnRTxtExpl)
	ON_EN_SETFOCUS(IDC_EDIT2, OnSetFocEd)
	ON_CBN_SELCHANGE(IDC_COMBO3, OnSelCombo)
	ON_EN_CHANGE(IDC_EDIT2, OnInputEd)
	ON_BN_CLICKED(IDC_CHECK1, OnCheckRelat)
	ON_BN_CLICKED(IDC_PUTOBCL, OnPutObCl)
	ON_BN_CLICKED(IDC_RENAME, OnRename)
	ON_BN_CLICKED(IDC_LOESCH, OnLoesch)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CTxtReDlg message handlers

void CTxtReDlg::OnOK()
{	
	CDialog::OnOK();
	
CWaitCursor WC;
CString cbBufIdent (' ',STRLENGTH);
CString cbBufMCode (' ',STRLENGTH);
short iIndex = 0;// Aufruf für Einzelauswahlbox 
bool bTemp = false;
bool bRelat = false;
bool bObLoesch = false;
bool bRename = false;
bool fPosPtTexts = false;
char cGeo = '0';
	     
	if (m_rTxtTemp.GetCheck() == 1) bTemp = true;			
	if ((m_cRelat.GetCheck() == 1) && !bTemp ) bRelat = true;	
	if (m_rObLoesch.GetCheck() == 1 && m_rRename.GetCheck() == 0) bObLoesch = true;
	if (m_rObLoesch.GetCheck() == 0 && m_rRename.GetCheck() == 1) bRename = true;
	
	fPosPtTexts = m_cbPosPtTexts.GetCheck();

	if (m_cPutObCl.GetCheck() == 1)	 {
		iIndex = m_cbxObClList.GetCurSel(); // Aufruf für Einzelauswahlbox 		    	
		m_cbxObClList.GetLBText (iIndex, cbBufIdent); 									
		m_rlCBIdent = strtoul (cbBufIdent, NULL, DEX_GetIdBase());
	}
	else m_rlCBIdent = 0;

	if (Event() == 1) {			 
		iIndex = m_cbxMCode.GetCurSel(); 	    
	    	m_cbxMCode.GetLBText (iIndex, cbBufMCode); 
		m_lMCode = strtoul (cbBufMCode, NULL, DEX_GetMkBase());
	
	// Übergebe der nach "IDOK" automat. refreshten Werte an
	// die Hauptfunktion, Text nach Objektklasse gewählt										
		m_pHelper -> ProvTextObj (m_hWnd, &cGeo, ' ', 0, m_lMCode, bTemp, bRelat, 
					  bObLoesch, bRename, m_rlCBIdent, fPosPtTexts);
	}
	
	if (Event() == 2) {
	CString myText = GetText();
	// Übergebe der nach "IDOK" automat. refreshten Werte an
	// die Hauptfunktion, selbst Text generiert	
		m_pHelper -> ProvTextObj (m_hWnd, &cGeo, myText, 0, 0, bTemp, bRelat, 
					  bObLoesch, bRename, m_rlCBIdent, fPosPtTexts);
	}		
}

bool CTxtReDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	if ( ! (DEX_QueryMode() & QMSysAdmin) ) {
		m_rTxtTemp.ShowWindow(SW_HIDE);
		m_rTxtPerm.ShowWindow(SW_HIDE);
		::ShowWindow(m_stSForm.m_hWnd, SW_HIDE);
	}

	m_rMCode.SetCheck(1);     
	m_rTxtTemp.SetCheck(0);
	m_rTxtPerm.SetCheck(1);
	m_rTxtPerm.EnableWindow(true);
	m_rTxtTemp.EnableWindow(true);
	
	m_cRelat.EnableWindow(true);
	m_cRelat.SetCheck(0);
	m_OK.EnableWindow(true);
	m_rObLoesch.EnableWindow(false);
	m_rRename.SetCheck(1);
	m_rRename.EnableWindow(false);
	m_cbxObClList.EnableWindow(false);	
	m_cPutObCl.EnableWindow(true);	
	m_cPutObCl.SetCheck(0);                                                         
	m_cbPosPtTexts.SetCheck (true);
	
ENUMLONGKEY ELK;    
	
// Hole die Identifik. u. den Merkmalscode mit Text---------------------------------
	ELK.eKey = 'i';
	ELK.eFcn = (ENUMLONGKEYPROC) EnumIdentProc;
	ELK.ePtr = (void*) &m_cbxObClList;
	if ( ! DEX_EnumPBDData(ELK) ) return false;
    
ENUMNOKEY	ENK;      
	ENK.eFcn = (ENUMNOKEYPROC) EnumMCodeProc;    
	ENK.ePtr = (void*) &m_cbxMCode;
	if (!DEX_EnumMCodes(ENK)) return false;	// Merkmalscode holen
                                         
int Index = 0;
	Index = m_cbxMCode.SelectString(-1, "5110000");
	Index = m_cbxMCode.SetCurSel(Index);	
	if (Index == CB_ERR) {                  
		m_cbxMCode.SetCurSel(-1);	
	}
		
	Index = m_cbxObClList.SelectString(-1, "32212000");
	Index = m_cbxObClList.SetCurSel(Index);	
	if (Index == CB_ERR) {
		m_cbxObClList.SetCurSel(-1);		
	}

return true;  // return true  unless you set the focus to a control
}

void CTxtReDlg::OnRMCode()
{
	m_rText.SetCheck(0);
	m_cbxMCode.SetFocus();
	Event();
}

void CTxtReDlg::OnRPerm()
{
	m_rTxtTemp.SetCheck(0);	     
	m_cRelat.EnableWindow(true);
	if (m_cRelat.GetCheck() == 1) m_rObLoesch.EnableWindow(true);

}

void CTxtReDlg::OnRTemp()
{
	m_rTxtPerm.SetCheck(0);
	m_cRelat.EnableWindow(false);        
	m_rObLoesch.EnableWindow(false);
	m_rRename.EnableWindow(false);

}

void CTxtReDlg::OnRTxtExpl()
{
	m_eText.SetFocus();
	m_rMCode.SetCheck(0);
	Event();	
}

short CTxtReDlg::Event()
{
short icIndex = m_cbxMCode.GetCurSel();
short iRadioTxt= m_rText.GetCheck();
short iRadioMC= m_rMCode.GetCheck();
bool  bLeer  = GetText().IsEmpty();
short iWahl = 0;
	m_OK.EnableWindow(false);  
	
	if ((icIndex != CB_ERR) && (iRadioMC == 1) && (iRadioTxt == 0)) {
		m_OK.EnableWindow(true);
		return iWahl = 1;
	}
	else
		if (!bLeer && (iRadioMC == 0) && (iRadioTxt == 1)) {
			m_OK.EnableWindow(true);
			return iWahl = 2;
		}
		else
			return iWahl;
	
return 0;
}


void CTxtReDlg::OnSetFocEd()
{
	m_rText.SetCheck(1);
	m_rMCode.SetCheck(0);
	Event();
}

void CTxtReDlg::OnSelCombo()
{
	m_rText.SetCheck(0);
	m_rMCode.SetCheck(1);
	Event();	
}

void CTxtReDlg::OnInputEd()
{
	Event();	
}


void CTxtReDlg::OnCheckRelat()
{
	short iRelat = m_cRelat.GetCheck();

	if (iRelat == 1) {
		m_rObLoesch.EnableWindow(true);
		m_rRename.EnableWindow(true);  
	}
	else {
		m_rObLoesch.EnableWindow(false);
		m_rRename.EnableWindow(false);
	}
}

void CTxtReDlg::OnPutObCl()
{
	if (m_cPutObCl.GetCheck() == 1) m_cbxObClList.EnableWindow(true);		
	else m_cbxObClList.EnableWindow(false);		
}

void CTxtReDlg::OnRename()
{
	if(m_rRename.GetCheck() == 1)
		m_rObLoesch.SetCheck(0);	
	
}

void CTxtReDlg::OnLoesch()
{
	if(m_rObLoesch.GetCheck() == 1)
		m_rRename.SetCheck(0);	
}
