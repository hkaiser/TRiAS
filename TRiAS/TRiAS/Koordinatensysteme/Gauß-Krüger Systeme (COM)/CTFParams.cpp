// @doc
// @module CTFParams.cpp | implementation file for CCTFParams

#include "stdafx.h"

#include <Pragmas.h>

#include "GKCtf_COM.h"		// renamed JG990125
#include "CTFParams.h"
#include "CoordTransBase.h"	// renamed JG990125

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCTFParams property page

IMPLEMENT_DYNCREATE(CCTFParams, CPropertyPage)

CCTFParams::CCTFParams() 
	: CPropertyPage(CCTFParams::IDD), m_pCTF(NULL)
{
	m_psp.hInstance=_Module.GetResourceInstance();	//HK990128
	//{{AFX_DATA_INIT(CCTFParams)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

// 3 Grad-Meridiane initialisieren
	m_iMin3 = 0;
	m_iMax3 = 0;

// 6 Grad-Meridiane initialisieren
	m_iMin6 = 0;
	m_iMax6 = 0;
}

CCTFParams::~CCTFParams()
{
}

// während der Lebensdauer des Dialoges die zugehörige Properties-
// collection festhalten
void CCTFParams::SetTargetCTF (class CCoordTrans *pCTF)
{
	m_pCTF = pCTF;
}

void CCTFParams::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCTFParams)
	DDX_Control(pDX, IDC_SELELLIPSEGEOD, m_cbCoordSystemGeod);
	DDX_Control(pDX, IDC_GEOCOORDS, m_rbNative);
	DDX_Control(pDX, IDC_GAUCOORDS, m_rbTransMerc);
	DDX_Control(pDX, IDC_MERIDIAN, m_cbMeridian);
	DDX_Control(pDX, IDT_MERIDIAN, m_ftMeridian);
	DDX_Control(pDX, IDC_STRBREITE, m_cbStrBreite);
	DDX_Control(pDX, IDT_STRBREITE, m_ftStrBreite);
	DDX_Control(pDX, IDC_AUTOMERIDIAN, m_rbAutoMeridian);
	DDX_Control(pDX, IDC_SELECTMERIDIAN, m_rbSelectMeridian);
	DDX_Control(pDX, IDC_PRECISIONSPIN, m_sbPrec);
	DDX_Control(pDX, IDC_PRECISION, m_slePrec);
	DDX_Control(pDX, IDC_SELELLIPSE, m_cbCoordSystem);
	DDX_Control(pDX, IDC_COORDSYSTEM, m_ftCoordSystem);
	//}}AFX_DATA_MAP
}

// Minimale/maximale Meridiane berechnen --------------------------------------
void CCTFParams::CalcMeridians (void)
{
	m_iMin3 = 3;
	m_iMin6 = 3;

	m_iMax3 = 15;
	m_iMax6 = 15;
}

void CCTFParams::FillMeridian (int iStrBreite, int iMeridian)
{
char cbBuffer[20];
int iAct = 0;
int iRes = 0;

	m_cbMeridian.ResetContent();	// JG990128
	if (3 == iStrBreite) {
	int i = 0;

		for (i = m_iMin3; i <= m_iMax3; i += 3) {
			_itoa (i, cbBuffer, 10);
		
		int iCurr = m_cbMeridian.AddString (cbBuffer);

			if (iMeridian == i) 
				iAct = iCurr;
			else if (m_pCTF -> GetMeridian() == i) 
				iRes = iCurr; 
		}
	} else {
	int i = 0;

		for (i = m_iMin6; i <= m_iMax6; i += 6) {
			_itoa (i, cbBuffer, 10);
		
		int iCurr = m_cbMeridian.AddString (cbBuffer);

			if (iMeridian == i) 
				iAct = iCurr;
			else if (m_pCTF -> GetMeridian() == i) 
				iRes = iCurr; 
		}
	}

	if (0 == iAct) 
		iAct = iRes;
	m_cbMeridian.SetCurSel (iAct);
}

void CCTFParams::SwitchState (COORDTRANSFORMTYPE rgCTF, COORDTRANSFORMMODE rgCTFMode)
{
	switch (rgCTF) {
	case CTF_Geodetical:
		m_rbTransMerc.SetCheck (0);
		m_rbNative.SetCheck (1);
		m_ftStrBreite.EnableWindow(false);
		m_cbStrBreite.EnableWindow(false);
		m_ftMeridian.EnableWindow(false);
		m_cbMeridian.EnableWindow(false);
		m_rbAutoMeridian.SetCheck(0);
		m_rbAutoMeridian.EnableWindow(false);
		m_rbSelectMeridian.EnableWindow(false);
//		m_sbPrec.EnableWindow(false);
//		m_slePrec.EnableWindow(false);
		m_cbCoordSystem.EnableWindow(false);
		m_cbCoordSystemGeod.EnableWindow(true);
		break;

	case CTF_TransMercator:
		m_rbNative.SetCheck (0);
		m_rbTransMerc.SetCheck (1);
		m_ftStrBreite.EnableWindow(true);
		m_cbStrBreite.EnableWindow(true);
		m_ftMeridian.EnableWindow(true);
		m_rbAutoMeridian.EnableWindow(true);
		m_rbSelectMeridian.EnableWindow(true);
		m_cbCoordSystem.EnableWindow(true);
		m_cbCoordSystemGeod.EnableWindow(false);

		if (m_cbMeridian.GetCount() > 0) {
			if (CTFMODE_AutoMeridian == rgCTFMode) {
				m_rbAutoMeridian.SetCheck (1);
				m_rbSelectMeridian.SetCheck (0);
				m_cbMeridian.EnableWindow(false);
			} else {
				m_rbAutoMeridian.SetCheck (0);
				m_rbSelectMeridian.SetCheck (1);
				m_cbMeridian.EnableWindow(true);
			}
		} else {
			m_rbAutoMeridian.SetCheck (1);
			m_rbSelectMeridian.SetCheck (0);
			m_cbMeridian.EnableWindow(false);
			if (CTFMODE_SelectMeridian == rgCTFMode) 
				::MessageBeep (MB_ICONASTERISK);
		}
//		m_sbPrec.EnableWindow(true);
//		m_slePrec.EnableWindow(true);
		break;

	default:
		ASSERT(false);
		break;
	}
}

///////////////////////////////////////////////////////////////////////////////
// sonstige member
int CCTFParams::GetStrBreite (void)
{
int iIndex = m_cbStrBreite.GetCurSel();
char cbBuffer[20];

	if (-1 == iIndex) iIndex = 0;
	m_cbStrBreite.GetLBText (iIndex, cbBuffer);
	return atoi(cbBuffer);
}

int CCTFParams::GetMeridian (void)
{
int iIndex = m_cbMeridian.GetCurSel();
char cbBuffer[20];

	if (-1 == iIndex) iIndex = 0;
	m_cbMeridian.GetLBText (iIndex, cbBuffer);
	return atoi(cbBuffer);
}


BEGIN_MESSAGE_MAP(CCTFParams, CPropertyPage)
	//{{AFX_MSG_MAP(CCTFParams)
	ON_BN_CLICKED(IDC_AUTOMERIDIAN, OnAutomeridian)
	ON_BN_CLICKED(IDC_GAUCOORDS, OnGaucoords)
	ON_BN_CLICKED(IDC_GEOCOORDS, OnGeocoords)
	ON_BN_CLICKED(IDC_SELECTMERIDIAN, OnSelectmeridian)
	ON_CBN_SELCHANGE(IDC_STRBREITE, OnSelchangeStrbreite)
	ON_CBN_SELCHANGE(IDC_SELELLIPSE, OnSelchangeSelellipse)
	ON_CBN_SELCHANGE(IDC_SELELLIPSEGEOD, OnSelchangeSelellipse)
	ON_EN_CHANGE(IDC_PRECISION, OnChangePrecision)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCTFParams message handlers

BOOL CCTFParams::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	ASSERT(NULL != m_pCTF);			// muß fertig initialisiert sein

	AFX_MANAGE_STATE(AfxGetStaticModuleState())

// Font des Textes des KoordSystemes FETT einstellen
	{
	CWnd *pWnd = GetDlgItem (IDC_COORDSYSTEM);

		ASSERT(NULL != pWnd);

	CFont *pFont = pWnd -> GetFont();
	LOGFONT lf;

		ASSERT(NULL != pFont);
		pFont -> GetObject(sizeof(LOGFONT), &lf);
		lf.lfWeight = FW_BOLD;

		m_Font.CreateFontIndirect (&lf);
		pWnd -> SetFont(&m_Font, false);
	}

// EllipsoidAuswahl (native Koordinaten) initialisieren
CString strEllipse (m_pCTF -> GetEllipseStrings());
CString substr;

//	JG990126 no EllipseChange
	if (m_pCTF -> GetAllowChangeEllipse()) {

		if (AfxExtractSubString (substr, strEllipse, 0, '\n')) {
		CString str (m_pCTF -> GetCoordTypeString(0));

			str += substr;
			m_cbCoordSystem.AddString(str);
		}
		if (AfxExtractSubString (substr, strEllipse, 1, '\n')) {
		CString str (m_pCTF -> GetCoordTypeString(1));

			str += substr;
			m_cbCoordSystem.AddString(str);
		}
		if (AfxExtractSubString (substr, strEllipse, 2, '\n')) {
		CString str (m_pCTF -> GetCoordTypeString(2));

			str += substr;
			m_cbCoordSystem.AddString(str);
		}

		m_cbCoordSystem.ShowWindow(SW_SHOW);		// nur anzeigen, wenn verwendet
		m_cbCoordSystem.SetCurSel (m_pCTF -> GetChangedEllipse());
	} 
	else
		m_cbCoordSystem.ShowWindow(SW_HIDE);

// EllipsoidAuswahl (geodätische Koordinaten) initialisieren
	strEllipse = m_pCTF -> GetEllipseStrings();
	if (m_pCTF -> GetAllowChangeEllipse()) {

		if (AfxExtractSubString (substr, strEllipse, 0, '\n')) {
		CString str (m_pCTF -> GetCoordTypeString(0, CTF_Geodetical));

			str += substr;
			m_cbCoordSystemGeod.AddString(str);
		}
		if (AfxExtractSubString (substr, strEllipse, 1, '\n')) {
		CString str (m_pCTF -> GetCoordTypeString(1, CTF_Geodetical));

			str += substr;
			m_cbCoordSystemGeod.AddString(str);
		}
		if (AfxExtractSubString (substr, strEllipse, 2, '\n')) {
		CString str (m_pCTF -> GetCoordTypeString(2, CTF_Geodetical));

			str += substr;
			m_cbCoordSystemGeod.AddString(str);
		}

		m_cbCoordSystemGeod.ShowWindow(SW_SHOW);		// nur anzeigen, wenn verwendet
		m_cbCoordSystemGeod.SetCurSel (m_pCTF -> GetChangedEllipse());
	} 
	else
		m_cbCoordSystemGeod.ShowWindow(SW_HIDE);

// Koordinatenbezeichnung initialisieren
//	m_rbTransMerc.SetWindowText(m_pCTF -> GetCoordTypeString());

// Internes Koordinatensystem
	if (AfxExtractSubString (substr, strEllipse, 0, '\n')) {
	CString strT (m_pCTF -> GetInternalCoordTypeString());

		strT += substr;
		m_ftCoordSystem.SetWindowText (strT);
	}

// Minimale/maximale Meridian berechnen
	CalcMeridians();

// Comboboxen füllen
	m_cbStrBreite.AddString("3");
	m_cbStrBreite.AddString("6");
	m_cbStrBreite.SetCurSel (3 == m_pCTF -> GetStrBreite() ? 0 : 1);

	FillMeridian (m_pCTF -> GetStrBreite(), m_pCTF -> GetMeridian());

// Controls initialisieren
	SwitchState (m_pCTF -> GetCTFType(), m_pCTF -> GetCTFMode());		// Radiobuttons richten

// Precision initialisieren
	m_sbPrec.SetRange (0, 5);
	m_sbPrec.SetPos (m_pCTF -> GetPrecision());

	return true;  // return true unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return false
}

void CCTFParams::OnOK() 
{
// Werte zurückschreiben
	m_pCTF -> SetStrBreite (GetStrBreite());
	m_pCTF -> SetMeridian (GetMeridian());
	m_pCTF -> SetPrecision (GetPrecision());

// JG990126	no support for geod
	if (m_rbNative.GetCheck()) 
		m_pCTF -> SetCTFType (CTF_Geodetical);	// JG990126
	else
		m_pCTF -> SetCTFType (CTF_TransMercator);

	if (m_rbAutoMeridian.GetCheck())
		m_pCTF -> SetCTFMode (CTFMODE_AutoMeridian);
	else
		m_pCTF -> SetCTFMode (CTFMODE_SelectMeridian);

int iIndex = 0;

	if (m_pCTF -> GetAllowChangeEllipse()) {
		if (m_rbNative.GetCheck()) 
			iIndex = m_cbCoordSystemGeod.GetCurSel();
		else
			iIndex = m_cbCoordSystem.GetCurSel();
		_ASSERTE(0 == iIndex || 1 == iIndex || 2 == iIndex);

		m_pCTF -> SetChangedEllipse ((CCoordTrans::COORDTRANSELLIPSE)iIndex);
	}

	m_pCTF -> UpdateNewSettings (m_rbNative.GetCheck() ? true : false, m_rbAutoMeridian.GetCheck() ? true : false);
	SetModified (false);

	CPropertyPage::OnOK();
}

void CCTFParams::OnAutomeridian() 
{
	SwitchState (m_rbNative.GetCheck() ? CTF_Geodetical/*CTF_Native*//*JG990126*/ : CTF_TransMercator, CTFMODE_AutoMeridian);
	SetModified();
}

void CCTFParams::OnGaucoords() 
{
	SwitchState (CTF_TransMercator);
	SetModified();
}

void CCTFParams::OnGeocoords() 
{
	SwitchState (CTF_Geodetical);	// JG 990126
	SetModified();
}

void CCTFParams::OnSelectmeridian() 
{
	SwitchState (m_rbNative.GetCheck() ? CTF_Geodetical /*JG990126*/ : CTF_TransMercator, CTFMODE_SelectMeridian);
	SetModified();
}

void CCTFParams::OnSelchangeStrbreite() 
{
int iIndex = m_cbStrBreite.GetCurSel();

	ASSERT(0 == iIndex || 1 == iIndex);

	FillMeridian ((iIndex+1)*3, GetMeridian());
	if (m_rbSelectMeridian.GetCheck())
		m_cbMeridian.SetFocus();
	SetModified();
}

void CCTFParams::OnSelchangeSelellipse() 
{
	ASSERT(m_pCTF -> GetAllowChangeEllipse());
	SetModified();
}

void CCTFParams::OnChangePrecision() 
{
	SetModified();
}
