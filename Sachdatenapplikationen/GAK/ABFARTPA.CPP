// abfartpa.cpp : implementation file
//

#include "stdafx.h"			// 	prec. Header
#include "gak.h"		// CGakApp u. Ressourcen
#include "res.h"			//	Resourcen
#include "editext.h"		//	CEditExt
#include "numedit.h"		//	CRealEdit

#include "gaksete.h"		// CDaoRecordsetExt	
#include "abfset.h"			// CAbfSet
#include "selset.h"		// CSelectSet
#include "entsset.h"	// CEntsorgerSet
#include "transset.h"	// CTranspSet
#include "abfArset.h"		// CAbfArtSet

#include "selnum.h"			// CSelNummerDlg

#include "abfartpa.h"		//	zugeh. Header
#include "tmpswitch.h"		// CTmpSwitch exceptionsicheres temp. umschalten einer Variablen

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// erterne Variablen
extern CAbfSet *g_pAbfSet;

/////////////////////////////////////////////////////////////////////////////
// CAbfartParams dialog
CAbfartParams::CAbfartParams(CWnd* pParent, BOOL bReadOnly)
	: CSelNumberDlgUsage(CAbfartParams::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAbfartParams)
	m_strEntsorger = "";
	m_strTransp = "";
	m_strAbfArt = "";
	m_strMenge = "";
	m_strNachweis = "";
	m_strVerfahren = "";
	m_strPrioritaet = "";
	m_strEntsorgerBemerkung = _T("");
	m_strTransportBemerkung = _T("");
	//}}AFX_DATA_INIT

	m_bReadOnly = bReadOnly;

	m_iPosX = m_iPosY = 0;
	m_dMinMengeRec = 0;
	enumState = CHANGENOTHING;
	m_pTransSet = NULL;
	m_pEntsorgerSet = NULL;
	m_pAbfallart = NULL;
}

CAbfartParams::~CAbfartParams()
{
	enumState = CHANGENOTHING;
	DELETE_OBJ(m_pTransSet);
	DELETE_OBJ(m_pEntsorgerSet);
}

void CAbfartParams::DoDataExchange(CDataExchange* pDX)
{
	CSelNumberDlgUsage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAbfartParams)
	DDX_Control(pDX, IDE_ENTSORGER, m_edEntsorger);
	DDX_Control(pDX, IDE_TRANSPORTEUR, m_edTransp);
	DDX_Control(pDX, IDE_MENGE2, m_edMenge);
	DDX_Control(pDX, IDOK, m_btOk);
	DDX_Text(pDX, IDE_ENTSORGER, m_strEntsorger);
	DDX_Text(pDX, IDE_TRANSPORTEUR, m_strTransp);
	DDX_Text(pDX, IDE_ABFALLART, m_strAbfArt);
	DDX_Text(pDX, IDE_ENSN_NR, m_strNachweis);
	DDX_Text(pDX, IDE_RD_VERFAHREN, m_strVerfahren);
	DDX_Text(pDX, IDE_PRIO, m_strPrioritaet);
	DDX_Text(pDX, IDC_ENTSORGKOMMENTAR, m_strEntsorgerBemerkung);
	DDX_Text(pDX, IDC_BEFOERDKOMMENTAR, m_strTransportBemerkung);
	//}}AFX_DATA_MAP

	// jetzt folgen nur noch Lesezugriffe
	if (pDX->m_bSaveAndValidate)
		return;		

	CString strEmpty;
	// Datensatz nicht vorhanden
	if ((NULL == m_pTransSet) || (m_pTransSet->m_Nummer != m_strTransp))
	{
		DDX_Text(pDX, IDC_BEFOERDNAME, strEmpty);
		DDX_Text(pDX, IDC_BEFOERDSTR, strEmpty);
		DDX_Text(pDX, IDC_BEFOERDORT, strEmpty);

	}
	else
	{
		DDX_Text(pDX, IDC_BEFOERDNAME, m_pTransSet->m_Name);
		DDX_Text(pDX, IDC_BEFOERDSTR, m_pTransSet->m_Strasse);
		DDX_Text(pDX, IDC_BEFOERDORT, m_pTransSet->m_Ortsname);
	}

	if ((NULL == m_pEntsorgerSet) || (m_pEntsorgerSet->m_Nummer != m_strEntsorger))
	{
		DDX_Text(pDX, IDC_ENTSORGNAME, strEmpty);
		DDX_Text(pDX, IDC_ENTSORGSTR, strEmpty);
		DDX_Text(pDX, IDC_ENTSORGORT, strEmpty);
		DDX_Text(pDX, IDC_ENTSORGANLAGE, strEmpty);
	}
	else
	{
		DDX_Text(pDX, IDC_ENTSORGNAME, m_pEntsorgerSet->m_Name);
		DDX_Text(pDX, IDC_ENTSORGSTR, m_pEntsorgerSet->m_Strasse);
		DDX_Text(pDX, IDC_ENTSORGORT, m_pEntsorgerSet->m_Ortsname);
		DDX_Text(pDX, IDC_ENTSORGANLAGE, m_pEntsorgerSet->m_Anlage);
	}
	
	if ((NULL == m_pAbfallart) || (m_pAbfallart->m_Nummer != m_strAbfArt))
	{
		DDX_Text(pDX, IDC_ABFALLBEZ, strEmpty);
	}
	else
	{
		DDX_Text(pDX, IDC_ABFALLBEZ, m_pAbfallart->m_Name);
	}
}

BEGIN_MESSAGE_MAP(CAbfartParams, CSelNumberDlgUsage)
	//{{AFX_MSG_MAP(CAbfartParams)
	ON_EN_CHANGE(IDE_MENGE2, OnChangeMenge)
	ON_COMMAND(IDM_CUT, OnCut)
	ON_COMMAND(IDM_COPY, OnCopy)
	ON_COMMAND(IDM_INSERT, OnInsert)
	ON_COMMAND(IDM_DELETE, OnDelete)
	ON_COMMAND(IDM_SELECT, OnSelect)	
	ON_COMMAND(IDM_BACK, OnBack)
	ON_BN_CLICKED(IDC_SELECTBEFOERD, OnSelectbefoerd)
	ON_EN_CHANGE(IDE_ENTSORGER, OnChangeEntsorger)
	ON_EN_CHANGE(IDE_TRANSPORTEUR, OnChangeTransporteur)
	ON_BN_CLICKED(IDC_SELECTENTSORG, OnSelectentsorg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAbfartParams message handlers

BOOL CAbfartParams::OnInitDialog()
{
	CDialog::OnInitDialog();

	try
	{
		CDaoDatabase* pDatabase = NULL;
		if (NULL != g_pAbfSet)
		{
			 pDatabase = g_pAbfSet->m_pDatabase;
		}

		// EntsorgerSet
		m_pEntsorgerSet = new CEntsorgerSet (pDatabase, 
									((CGakApp *)AfxGetApp ())->EntsorgerDefaultSQL());
		m_pEntsorgerSet -> Open ();

		// TransporteurSet
		m_pTransSet = new CTranspSet (pDatabase, 
								 ((CGakApp *)AfxGetApp())->TransporteureDefaultSQL());
		m_pTransSet -> Open ();

		// Abfallart
		m_pAbfallart = new CAbfArtSet (pDatabase, 
								 ((CGakApp *)AfxGetApp())->AbfallArtenDefaultSQL());
		m_pAbfallart -> Open ();
		SearchNummer(m_pAbfallart, m_strAbfArt);
	}
	catch (CDaoException *e)
	{
		:: DisplayDaoException (e);
		e -> Delete ();
	}
	catch (CException *e)
	{
		e -> ReportError ();
		e -> Delete ();
	}



	ASSERT (m_dMinMengeRec >= 0.0);
	
//	Eingabelängen begrenzen	
	m_edTransp.LimitText (sMaxTranspLen);
	m_edEntsorger.LimitText (sMaxEntsorgerLen);	                                                                         
	((CEdit *) (GetDlgItem (IDE_ENSN_NR))) -> LimitText (sMaxEnSnLen);
	((CEdit *) (GetDlgItem (IDE_RD_VERFAHREN))) -> LimitText (sMaxVerfahrenLen);
	((CEdit *) (GetDlgItem (IDE_PRIO))) -> LimitText (sMaxPrioLen);

//	ReadOnly-Status setzen
	((CEdit *) (GetDlgItem (IDE_ENSN_NR))) -> SetReadOnly (m_bReadOnly);
	((CEdit *) (GetDlgItem (IDE_RD_VERFAHREN))) -> SetReadOnly (m_bReadOnly);
	((CEdit *) (GetDlgItem (IDE_PRIO))) -> SetReadOnly (m_bReadOnly);
	((CEdit *) (GetDlgItem (IDE_ENTSORGER))) -> SetReadOnly (m_bReadOnly);
	((CEdit *) (GetDlgItem (IDE_TRANSPORTEUR))) -> SetReadOnly (m_bReadOnly);
	((CEdit *) (GetDlgItem (IDE_MENGE2))) -> SetReadOnly (m_bReadOnly);
	
//	Überschrift akt.	                 
//	CString strCaption;
//	AfxFormatString1 (strCaption, IDS_ABFART_CAPTION2, m_strCaption);
	SetWindowText (m_strCaption);      
	                    
//	OK-Button akt.
	m_btOk.EnableWindow (atof (m_strMenge) >= m_dMinMengeRec); 	
	m_edMenge.SetWindowText (m_strMenge);
	m_edTransp.SetWindowText (m_strTransp);
	m_edEntsorger.SetWindowText (m_strEntsorger);

//	Fenster verschieben
//	CRect rc;
//	GetWindowRect (&rc);
//	MoveWindow (m_iPosX, m_iPosY, rc.Width (), rc.Height (), TRUE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}   

void CAbfartParams::OnChangeMenge()
{
	// TODO: Add your control notification handler code here
	m_edMenge.GetWindowText (m_strMenge);
	m_btOk.EnableWindow (m_bReadOnly || (atof (m_strMenge) >= m_dMinMengeRec)); 		
}   


void CAbfartParams::OnOK()
{
	// TODO: Add extra validation here
	if (!m_bReadOnly)
	{
		m_edMenge.GetWindowText (m_strMenge);	
		m_edTransp.GetWindowText (m_strTransp);
		m_edEntsorger.GetWindowText (m_strEntsorger);
		UpdateData (TRUE);
	}

	CDialog::OnOK();
}
    
void CAbfartParams::OnCut()
{
	// TODO: Add your command handler code here
	HasFocus () -> Cut ();	
}
                               
void CAbfartParams::OnBack()
{
	// TODO: Add your command handler code here
	if (HasFocus () -> CanUndo ())
		HasFocus () -> Undo ();
}

void CAbfartParams::OnCopy()
{
	// TODO: Add your command handler code here
	HasFocus () -> Copy ();			
}

void CAbfartParams::OnDelete()
{
	// TODO: Add your command handler code here
	HasFocus () -> Clear ();		
}

void CAbfartParams::OnInsert()
{
	// TODO: Add your command handler code here
	HasFocus () -> Paste ();	
}

void CAbfartParams::OnSelect()
{
	// TODO: Add your command handler code here
	HasFocus () -> SetSel (0, -1);
}
void CAbfartParams::DoChangeName(CString& strName)
{
}

void CAbfartParams::DoChangeNummer(CString& strNummer)
{
	switch (enumState)
	{
	case CHANGETRANSPORT:
		m_strTransp = strNummer;
		UpdateData(FALSE);
		OnChangeTransporteur();
		break;
	case CHANGEENTSORGER:
		m_strEntsorger = strNummer;
		UpdateData(FALSE);
		OnChangeEntsorger();
		break;
	default:
		return;
	}

	// do nothing
	enumState = CHANGENOTHING;
}

void CAbfartParams::OnSelectbefoerd() 
{
	enumState = CHANGETRANSPORT;
	DELETE_OBJ(m_pNumberDlg);
	Change (((CGakApp *)AfxGetApp())->TransporteureDefaultSQL(), IDS_TRANSP_CAPTION, m_strTransp, m_pTransSet); 
}

void CAbfartParams::OnSelectentsorg() 
{
	enumState = CHANGEENTSORGER;
	DELETE_OBJ(m_pNumberDlg);
	Change (((CGakApp *)AfxGetApp ())->EntsorgerDefaultSQL(), IDS_ENTS_CAPTION, m_strEntsorger, m_pEntsorgerSet);
}

void CAbfartParams::OnChangeEntsorger() 
{
	if (NULL != m_pEntsorgerSet)
	{
		UpdateData(TRUE);
		SearchNummer(m_pEntsorgerSet, m_strEntsorger);
		UpdateData(FALSE);
	}
}

void CAbfartParams::OnChangeTransporteur() 
{
	if (NULL != m_pTransSet)
	{
		UpdateData(TRUE);
		SearchNummer(m_pTransSet, m_strTransp);
		UpdateData(FALSE);
	}
}

BOOL SearchNummer(CSelectSet* pSet, CString& strNummer)
{
	try
	{
		CString strFind;
		AfxFormatString1 (strFind, IDS_FIND_NUMMER, strNummer);
		if (pSet -> FindFirst (strFind))
		{
			return TRUE;
		}
	}
	catch (CDaoException *e)
	{
		:: DisplayDaoException (e);
		e -> Delete ();
	}
	catch (CException* e)
	{
		e -> ReportError ();
		e -> Delete ();
	}
	catch(...)
	{
	}
	
	return FALSE;
}
