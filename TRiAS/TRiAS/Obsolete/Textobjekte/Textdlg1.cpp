// textdlg.cpp : implementation file
//

#include "stdafx.h"

#include "resource.h"
#include "helper.h"
#include "textdlg.h"
#include "iterator.hpp"    
#include "textex1.hpp"
#include "waitcur.hpp"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTextDlg dialog     
CTextDlg::CTextDlg(CWnd* pParent /*=NULL*/, CHelper *pHelper)
	: CDialog(CTextDlg::IDD, pParent),
	  m_lbIdList()
{
	//{{AFX_DATA_INIT(CTextDlg)
	//}}AFX_DATA_INIT
	m_iERR = 0;
	m_pHelper = pHelper;               
	m_rlCBIdent = 0;
}

void CTextDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTextDlg)
	DDX_Control(pDX, IDC_POSPOINTTEXTS, m_cbPosPtTexts);
	DDX_Control(pDX, IDC_RLOESCH, m_rObLoesch);
	DDX_Control(pDX, IDC_CHECK1, m_cRelat);
	DDX_Control(pDX, IDC_EDIT1, m_eText);
	DDX_Control(pDX, IDOK, m_OKButton);
	DDX_Control(pDX, IDC_COMBO1, m_cbxMCodeList);
	DDX_Control(pDX, IDC_ComboPutOCl, m_cbxObClList);
	DDX_Control(pDX, IDC_LIST1, m_lbIdList);
	DDX_Control(pDX, IDC_RADIO1, m_rText);
	DDX_Control(pDX, IDC_RADIO2, m_rMCode);
	DDX_Control(pDX, IDC_RADIO3, m_rTxtPerm);
	DDX_Control(pDX, IDC_RADIO4, m_rTxtTemp);	
	DDX_Control(pDX, IDC_PUTOBCL, m_cPutObCl);	
	DDX_Control(pDX, IDC_RRENAME, m_rRename);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTextDlg, CDialog)
	//{{AFX_MSG_MAP(CTextDlg)
	ON_LBN_SELCHANGE(IDC_LIST1, OnSelList)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelCom)
	ON_BN_CLICKED(IDC_RADIO1, OnRadioTxt)
	ON_EN_SETFOCUS(IDC_EDIT1, OnSetFocusE1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadioMCText)
	ON_EN_CHANGE(IDC_EDIT1, OnInputE1)
	ON_BN_CLICKED(IDC_RADIO3, OnRadioTxtPerm)
	ON_BN_CLICKED(IDC_RADIO4, OnRadioTxtTemp)
	ON_BN_CLICKED(IDC_ALLID, OnAllId)
	ON_BN_CLICKED(IDC_CHECK1, OnCheckRelat)
	ON_BN_CLICKED(IDC_PUTOBCL, OnPutObCl)
	ON_BN_CLICKED(IDC_RRENAME, OnRename)
	ON_BN_CLICKED(IDC_RLOESCH, OnObLoesch)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTextDlg message handlers

#define MODE_CREATEFROMFEATURE	1
#define MODE_CREATEFROMTEXT	2

void CTextDlg::OnOK()
{	
	CDialog::OnOK();

CWaitCursor WC;
CLBIterator ILB (m_lbIdList);
CString cbBufCBMCode (' ', STRLENGTH);
CString cbBufCBIdent (' ', STRLENGTH);
short iIndex = 0; // Aufruf für Einzelauswahlbox 
bool bTemp = false;
bool bRelat = false;                                                
bool bRename = false;
bool bObLoesch = false;
bool fPosPtTexts = false;
char cGeo;

	if (-1 != m_iERR) {
		bTemp = m_rTxtTemp.GetCheck();
		bRelat = m_cRelat.GetCheck() && !bTemp;
		bObLoesch = m_rObLoesch.GetCheck() && m_rRename.GetCheck();
		bRename = !m_rObLoesch.GetCheck() && m_rRename.GetCheck();
		fPosPtTexts = m_cbPosPtTexts.GetCheck();

		if (m_cPutObCl.GetCheck())	 {
			iIndex = m_cbxObClList.GetCurSel(); // Aufruf für Einzelauswahlbox 		    	
			if (iIndex >= 0) {
				m_cbxObClList.GetLBText (iIndex, cbBufCBIdent); 									
				m_rlCBIdent = strtoul (cbBufCBIdent, NULL, DEX_GetIdBase());
			} else 
				m_rlCBIdent = 0;
		}
		else m_rlCBIdent = 0;
		
		if (Event() == MODE_CREATEFROMFEATURE) {
			iIndex = m_cbxMCodeList.GetCurSel();
			
			ASSERT(iIndex >= 0);

			m_cbxMCodeList.GetLBText (iIndex, cbBufCBMCode); 
			m_rlMCode = strtoul (cbBufCBMCode, NULL, DEX_GetMkBase());
	            	
            while (ILB.GetNextItem (m_rlIdent, &cGeo)) {
	        // Übergebe der nach "IDOK" automat. refreshten Werte an
	        // die Hauptfunktion, Text nach Objektklasse gewählt											
				m_pHelper  -> ProvTextObj (0, &cGeo, ' ', m_rlIdent, 
							m_rlMCode, bTemp, bRelat, 
							bObLoesch, bRename, m_rlCBIdent,
							fPosPtTexts);
			}
		}
		if (Event() == MODE_CREATEFROMTEXT) {
		CString myText = GetText();	
		
		        while (ILB.GetNextItem (m_rlIdent, &cGeo)) {
	        	// Übergebe der nach "IDOK" automat. refreshten Werte an
	        	// die Hauptfunktion, selbst Text generiert	
				m_pHelper  -> ProvTextObj (0, &cGeo, myText, m_rlIdent, 
							0, bTemp, bRelat, bObLoesch, bRename, 
							m_rlCBIdent, fPosPtTexts);
			}
		}
	}
}

bool CTextDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CenterWindow();			// Fenster zentrieren

	m_OKButton.EnableWindow(false);
	m_rMCode.SetCheck(1);	

// temporär ausschliessen	
	if ( ! (DEX_QueryMode() & QMSysAdmin) ) {
		m_rTxtTemp.ShowWindow(SW_HIDE);
		m_rTxtPerm.ShowWindow(SW_HIDE);
		::ShowWindow (m_stSForm.m_hWnd, SW_HIDE);
	}

	m_rTxtTemp.SetCheck(0);
	m_rTxtPerm.SetCheck(1);
	m_rTxtPerm.EnableWindow(true);
	m_rTxtTemp.EnableWindow(true);

	m_cbPosPtTexts.SetCheck (true);
		
	m_cPutObCl.SetCheck(0);
	m_cPutObCl.EnableWindow(true);
	m_rRename.SetCheck(1);
	m_cRelat.EnableWindow(true);
	m_rRename.EnableWindow(false);
	m_rObLoesch.EnableWindow(false);
	m_cbxObClList.EnableWindow(false);		

// in PBD verfügbare Idents besorgen
ENUMLONGKEY ELK;

	ELK.eKey = 'i';
	ELK.eFcn = (ENUMLONGKEYPROC) EnumIdentProc;
	ELK.ePtr = (void*) &m_cbxObClList;
	if (!DEX_EnumPBDData (ELK)) 
		return false;

// in aktueller Sicht verfügbare Identifikator/Objekttyp - Kombinationen
ENUMTEXTKEYEX ETKEX;

	ETKEX.eKey = NULL;				// Suchschlüssel (aktuelle Sicht)
	ETKEX.eFcn = (ENUMTEXTKEYEXPROC) EnumIdentProcEx;	// zu rufende Funktion
	ETKEX.ePtr = (void *) &m_lbIdList;		// durchgereichte Daten
	ETKEX.eData = OTPunkt | OTLinie | OTFlaeche;	// zusätzliche Parameter
	if (!DEX_EnumSightIdentsEx (ETKEX)) 
		return false;			// alle Identifikatoren einer Sicht fuer Combobox

// verfügbare MerkmalsCodes in Combobox listen
ENUMNOKEY ENK;
	
	ENK.eFcn = (ENUMNOKEYPROC) EnumMCodeProc;
	ENK.ePtr = (void *) &m_cbxMCodeList;
	m_cbxMCodeList.ResetContent();
	if (!DEX_EnumMCodes (ENK)) return false;

return true;
}



void CTextDlg::OnSelList()
{
	Event();
}                      

                                                              
void CTextDlg::OnSelCom()
{
	m_rMCode.SetCheck(1);
	m_rText.SetCheck(0);
	Event();
}


void CTextDlg::OnRadioTxt()
{
	m_eText.SetFocus();
	m_rMCode.SetCheck(0);
	Event();
}

void CTextDlg::OnSetFocusE1()
{
	m_rText.SetCheck(1);
	m_rMCode.SetCheck(0);
	Event();
}

void CTextDlg::OnRadioMCText()
{
	m_rText.SetCheck(0);
	m_rMCode.SetCheck(1);
	m_cbxMCodeList.SetFocus();
	Event();
}

void CTextDlg::OnInputE1()
{
	Event();
}

// Funktion , die alle Fälle für OK-Button abdeckt
short CTextDlg::Event()
{
int icIndex = m_cbxMCodeList.GetCurSel();	// MCode ausgewählt
int ilSCnt = m_lbIdList.GetSelCount();		// Anzahl der selektierten Idents
bool iRadioMC = m_rMCode.GetCheck();		// Merkmal als Text
bool bLeer  = GetText().IsEmpty();
	
	m_OKButton.EnableWindow (false);

	if ((0 != ilSCnt) && ((CB_ERR != icIndex) && iRadioMC))
	{
		m_OKButton.EnableWindow (true);
		return MODE_CREATEFROMFEATURE;
	}
	else if ((ilSCnt != 0) && (!iRadioMC && !bLeer)) {
		m_OKButton.EnableWindow (true);
		return MODE_CREATEFROMTEXT;
	}
	else
		return 0;

return m_iERR = -1;		// ??? m_iErr == -1
}

  
void CTextDlg::OnRadioTxtPerm()
{
	m_rTxtPerm.SetCheck(1);
	m_rTxtTemp.SetCheck(0);	   
	m_cRelat.EnableWindow(true);   
	
	if(m_cRelat.GetCheck())
		m_rObLoesch.EnableWindow(true);

	m_rRename.EnableWindow(true);
}

void CTextDlg::OnRadioTxtTemp()
{
	m_rTxtPerm.SetCheck(0);
	m_rTxtTemp.SetCheck(1);	
	m_cRelat.EnableWindow(false);   
	m_rRename.EnableWindow(false);
	m_rObLoesch.EnableWindow(false);
}


void CTextDlg::OnAllId()
{
	m_iERR = m_lbIdList.SetSel (-1, true);
	if (m_iERR == LB_ERR) m_iERR = -1;		// ??? LB_ERR ist gleich -1 !!

	Event();
}



void CTextDlg::OnCheckRelat()
{
	if (m_cRelat.GetCheck()) {
		m_rRename.EnableWindow(true);
		m_rObLoesch.EnableWindow(true);
	}
	else {
		m_rObLoesch.EnableWindow(false);
		m_rRename.EnableWindow(false);
	}
}


void CTextDlg::OnPutObCl()
{
	m_cbxObClList.EnableWindow (m_cPutObCl.GetCheck());		
}


void CTextDlg::OnRename()
{
	m_rObLoesch.SetCheck(0);	
	m_rRename.SetCheck(1);	
}

void CTextDlg::OnObLoesch()
{
	m_rObLoesch.SetCheck(1);	
	m_rRename.SetCheck(0);	
}
