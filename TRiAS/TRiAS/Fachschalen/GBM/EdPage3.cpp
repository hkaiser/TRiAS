// EdPage3.cpp : implementation file
//

#include "stdafx.h"
#include "GbmTRiAS.h"
#include "EdPage3.h"

#include "ErfassPrivDlg.h"
#include "DeleteDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditPage3 property page

IMPLEMENT_DYNCREATE(CEditPage3, CPropertyPage)

CEditPage3::CEditPage3() : CPropertyPage(CEditPage3::IDD)
{
	//{{AFX_DATA_INIT(CEditPage3)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	for ( short i = 0; i < MAX_ANZAHL_DT; i++ )
	{
		m_strD[i].Empty();
		m_rF[i] = 0;
		m_rAF[i] = 0;
		m_bA[i] = FALSE;
	}
}

CEditPage3::~CEditPage3()
{
}

void CEditPage3::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditPage3)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_TEXTD1, m_strD[0]);
	DDX_Text(pDX, IDC_TEXTD2, m_strD[1]);
	DDX_Text(pDX, IDC_TEXTD3, m_strD[2]);
	DDX_Text(pDX, IDC_TEXTD4, m_strD[3]);
	DDX_Text(pDX, IDC_TEXTD5, m_strD[4]);
	DDX_Text(pDX, IDC_TEXTD6, m_strD[5]);
	DDX_Text(pDX, IDC_TEXTD7, m_strD[6]);
	DDX_Text(pDX, IDC_TEXTD8, m_strD[7]);
	DDX_Text(pDX, IDC_TEXTD9, m_strD[8]);
	DDX_Text(pDX, IDC_TEXTD10, m_strD[9]);
	DDX_Text(pDX, IDC_TEXTD11, m_strD[10]);
	DDX_Text(pDX, IDC_TEXTD12, m_strD[11]);
	DDX_Text(pDX, IDC_TEXTD13, m_strD[12]);
	DDX_Text(pDX, IDC_TEXTD14, m_strD[13]);
	DDX_Text(pDX, IDC_TEXTD15, m_strD[14]);
	DDX_Text(pDX, IDC_TEXTD16, m_strD[15]);
	DDX_Text(pDX, IDC_TEXTD17, m_strD[16]);
	DDX_Text(pDX, IDC_TEXTD18, m_strD[17]);
	DDX_Text(pDX, IDC_TEXTD19, m_strD[18]);
	DDX_Text(pDX, IDC_TEXTD20, m_strD[19]);
	short i = m_iGebZahl - m_iOffset;

	if ( i > 0 )
	{	SpecialDDX_Text(pDX, IDC_EDIT10, m_rF[0]);
		SpecialDDX_Text(pDX, IDC_EDIT11, m_rAF[0]);
		SpecialDDX_Check(pDX, IDC_CHECK1, m_bA[0]);	}
	else
	{	HideControl(pDX, IDC_EDIT10);
		HideControl(pDX, IDC_EDIT11);
		HideControl(pDX, IDC_CHECK1);	}

	if ( i > 1 )
	{	SpecialDDX_Text(pDX, IDC_EDIT12, m_rF[1]);
		SpecialDDX_Text(pDX, IDC_EDIT13, m_rAF[1]);
		SpecialDDX_Check(pDX, IDC_CHECK2, m_bA[1]);	}
	else
	{	HideControl(pDX, IDC_EDIT12);
		HideControl(pDX, IDC_EDIT13);
		HideControl(pDX, IDC_CHECK2);	}

	if ( i > 2 )
	{	SpecialDDX_Text(pDX, IDC_EDIT14, m_rF[2]);
		SpecialDDX_Text(pDX, IDC_EDIT15, m_rAF[2]);
		SpecialDDX_Check(pDX, IDC_CHECK3, m_bA[2]);	}
	else
	{	HideControl(pDX, IDC_EDIT14);
		HideControl(pDX, IDC_EDIT15);
		HideControl(pDX, IDC_CHECK3);	}

	if ( i > 3 )
	{	SpecialDDX_Text(pDX, IDC_EDIT16, m_rF[3]);
		SpecialDDX_Text(pDX, IDC_EDIT17, m_rAF[3]);
		SpecialDDX_Check(pDX, IDC_CHECK4, m_bA[3]);	}
	else
	{	HideControl(pDX, IDC_EDIT16);
		HideControl(pDX, IDC_EDIT17);
		HideControl(pDX, IDC_CHECK4);	}

	if ( i > 4 )
	{	SpecialDDX_Text(pDX, IDC_EDIT18, m_rF[4]);
		SpecialDDX_Text(pDX, IDC_EDIT19, m_rAF[4]);
		SpecialDDX_Check(pDX, IDC_CHECK5, m_bA[4]);	}
	else
	{	HideControl(pDX, IDC_EDIT18);
		HideControl(pDX, IDC_EDIT19);
		HideControl(pDX, IDC_CHECK5);	}

	if ( i > 5 )
	{	SpecialDDX_Text(pDX, IDC_EDIT20, m_rF[5]);
		SpecialDDX_Text(pDX, IDC_EDIT21, m_rAF[5]);
		SpecialDDX_Check(pDX, IDC_CHECK6, m_bA[5]);	}
	else
	{	HideControl(pDX, IDC_EDIT20);
		HideControl(pDX, IDC_EDIT21);
		HideControl(pDX, IDC_CHECK6);	}

	if ( i > 6 )
	{	SpecialDDX_Text(pDX, IDC_EDIT22, m_rF[6]);
		SpecialDDX_Text(pDX, IDC_EDIT23, m_rAF[6]);
		SpecialDDX_Check(pDX, IDC_CHECK7, m_bA[6]);	}
	else
	{	HideControl(pDX, IDC_EDIT22);
		HideControl(pDX, IDC_EDIT23);
		HideControl(pDX, IDC_CHECK7);	}

	if ( i > 7 )
	{	SpecialDDX_Text(pDX, IDC_EDIT24, m_rF[7]);
		SpecialDDX_Text(pDX, IDC_EDIT25, m_rAF[7]);
		SpecialDDX_Check(pDX, IDC_CHECK8, m_bA[7]);	}
	else
	{	HideControl(pDX, IDC_EDIT24);
		HideControl(pDX, IDC_EDIT25);
		HideControl(pDX, IDC_CHECK8);	}

	if ( i > 8 )
	{	SpecialDDX_Text(pDX, IDC_EDIT26, m_rF[8]);
		SpecialDDX_Text(pDX, IDC_EDIT27, m_rAF[8]);
		SpecialDDX_Check(pDX, IDC_CHECK9, m_bA[8]);	}
	else
	{	HideControl(pDX, IDC_EDIT26);
		HideControl(pDX, IDC_EDIT27);
		HideControl(pDX, IDC_CHECK9);	}

	if ( i > 9 )
	{	SpecialDDX_Text(pDX, IDC_EDIT28, m_rF[9]);
		SpecialDDX_Text(pDX, IDC_EDIT29, m_rAF[9]);
		SpecialDDX_Check(pDX, IDC_CHECK10, m_bA[9]);	}
	else
	{	HideControl(pDX, IDC_EDIT28);
		HideControl(pDX, IDC_EDIT29);
		HideControl(pDX, IDC_CHECK10);	}

	if ( i > 10 )
	{	SpecialDDX_Text(pDX, IDC_EDIT30, m_rF[10]);
		SpecialDDX_Text(pDX, IDC_EDIT31, m_rAF[10]);
		SpecialDDX_Check(pDX, IDC_CHECK11, m_bA[10]);	}
	else
	{	HideControl(pDX, IDC_EDIT30);
		HideControl(pDX, IDC_EDIT31);
		HideControl(pDX, IDC_CHECK11);	}

	if ( i > 11 )
	{	SpecialDDX_Text(pDX, IDC_EDIT32, m_rF[11]);
		SpecialDDX_Text(pDX, IDC_EDIT33, m_rAF[11]);
		SpecialDDX_Check(pDX, IDC_CHECK12, m_bA[11]);	}
	else
	{	HideControl(pDX, IDC_EDIT32);
		HideControl(pDX, IDC_EDIT33);
		HideControl(pDX, IDC_CHECK12);	}

	if ( i > 12 )
	{	SpecialDDX_Text(pDX, IDC_EDIT34, m_rF[12]);
		SpecialDDX_Text(pDX, IDC_EDIT35, m_rAF[12]);
		SpecialDDX_Check(pDX, IDC_CHECK13, m_bA[12]);	}
	else
	{	HideControl(pDX, IDC_EDIT34);
		HideControl(pDX, IDC_EDIT35);
		HideControl(pDX, IDC_CHECK13);	}

	if ( i > 13 )
	{	SpecialDDX_Text(pDX, IDC_EDIT36, m_rF[13]);
		SpecialDDX_Text(pDX, IDC_EDIT37, m_rAF[13]);
		SpecialDDX_Check(pDX, IDC_CHECK14, m_bA[13]);	}
	else
	{	HideControl(pDX, IDC_EDIT36);
		HideControl(pDX, IDC_EDIT37);
		HideControl(pDX, IDC_CHECK14);	}

	if ( i > 14 )
	{	SpecialDDX_Text(pDX, IDC_EDIT38, m_rF[14]);
		SpecialDDX_Text(pDX, IDC_EDIT39, m_rAF[14]);
		SpecialDDX_Check(pDX, IDC_CHECK15, m_bA[14]);	}
	else
	{	HideControl(pDX, IDC_EDIT38);
		HideControl(pDX, IDC_EDIT39);
		HideControl(pDX, IDC_CHECK15);	}

	if ( i > 15 )
	{	SpecialDDX_Text(pDX, IDC_EDIT40, m_rF[15]);
		SpecialDDX_Text(pDX, IDC_EDIT41, m_rAF[15]);
		SpecialDDX_Check(pDX, IDC_CHECK16, m_bA[15]);	}
	else
	{	HideControl(pDX, IDC_EDIT40);
		HideControl(pDX, IDC_EDIT41);
		HideControl(pDX, IDC_CHECK16);	}

	if ( i > 16 )
	{	SpecialDDX_Text(pDX, IDC_EDIT42, m_rF[16]);
		SpecialDDX_Text(pDX, IDC_EDIT43, m_rAF[16]);
		SpecialDDX_Check(pDX, IDC_CHECK17, m_bA[16]);	}
	else
	{	HideControl(pDX, IDC_EDIT42);
		HideControl(pDX, IDC_EDIT43);
		HideControl(pDX, IDC_CHECK17);	}

	if ( i > 17 )
	{	SpecialDDX_Text(pDX, IDC_EDIT44, m_rF[17]);
		SpecialDDX_Text(pDX, IDC_EDIT45, m_rAF[17]);
		SpecialDDX_Check(pDX, IDC_CHECK18, m_bA[17]);	}
	else
	{	HideControl(pDX, IDC_EDIT44);
		HideControl(pDX, IDC_EDIT45);
		HideControl(pDX, IDC_CHECK18);	}

	if ( i > 18 )
	{	SpecialDDX_Text(pDX, IDC_EDIT46, m_rF[18]);
		SpecialDDX_Text(pDX, IDC_EDIT47, m_rAF[18]);
		SpecialDDX_Check(pDX, IDC_CHECK19, m_bA[18]);	}
	else
	{	HideControl(pDX, IDC_EDIT46);
		HideControl(pDX, IDC_EDIT47);
		HideControl(pDX, IDC_CHECK19);	}

	if ( i > 19 )
	{	SpecialDDX_Text(pDX, IDC_EDIT48, m_rF[19]);
		SpecialDDX_Text(pDX, IDC_EDIT49, m_rAF[19]);
		SpecialDDX_Check(pDX, IDC_CHECK20, m_bA[19]);	}
	else
	{	HideControl(pDX, IDC_EDIT48);
		HideControl(pDX, IDC_EDIT49);
		HideControl(pDX, IDC_CHECK20);	}

	if ( pDX -> m_bSaveAndValidate )		RestoreData();
}

void CEditPage3::SpecialDDX_Text( CDataExchange *pDX, UINT id, double &r )
{
	if ( !pDX -> m_bSaveAndValidate )
	{
		CWnd    *pWnd = GetDlgItem( id );
		if ( pWnd )
		{
			pWnd -> ShowWindow( SW_SHOW );
			pWnd -> EnableWindow( TRUE );
		}
	}

	DDX_Text( pDX, id, r );
}

void CEditPage3::SpecialDDX_Check( CDataExchange *pDX, UINT id, BOOL &r )
{
	if ( !pDX -> m_bSaveAndValidate )
	{
		CWnd    *pWnd = GetDlgItem( id );
		if ( pWnd )
		{
			pWnd -> ShowWindow( SW_SHOW );
			pWnd -> EnableWindow( TRUE );
		}
	}

	DDX_Check( pDX, id, r );
}

void CEditPage3::HideControl( CDataExchange *pDX, UINT id )
{
	if ( !pDX -> m_bSaveAndValidate )
	{
		CWnd    *pWnd = GetDlgItem( id );
		if ( pWnd )
		{
			pWnd -> ShowWindow( SW_HIDE );
			pWnd -> EnableWindow( FALSE );
		}
	}
}


BEGIN_MESSAGE_MAP(CEditPage3, CPropertyPage)
	//{{AFX_MSG_MAP(CEditPage3)
	ON_BN_CLICKED(IDC_BUTTON1, OnNeu)
	ON_BN_CLICKED(IDC_BUTTON2, OnDelete)
	ON_BN_CLICKED(IDC_BUTTON3, OnWeiter)
	ON_BN_CLICKED(IDC_BUTTON4, OnZurueck)
	ON_BN_CLICKED(IDC_CHECK1, OnAnschl1)
	ON_BN_CLICKED(IDC_CHECK10, OnAnschl10)
	ON_BN_CLICKED(IDC_CHECK11, OnAnschl11)
	ON_BN_CLICKED(IDC_CHECK12, OnAnschl12)
	ON_BN_CLICKED(IDC_CHECK13, OnAnschl13)
	ON_BN_CLICKED(IDC_CHECK14, OnAnschl14)
	ON_BN_CLICKED(IDC_CHECK15, OnAnschl15)
	ON_BN_CLICKED(IDC_CHECK16, OnAnschl16)
	ON_BN_CLICKED(IDC_CHECK17, OnAnschl17)
	ON_BN_CLICKED(IDC_CHECK18, OnAnschl18)
	ON_BN_CLICKED(IDC_CHECK19, OnAnschl19)
	ON_BN_CLICKED(IDC_CHECK2, OnAnschl2)
	ON_BN_CLICKED(IDC_CHECK20, OnAnschl20)
	ON_BN_CLICKED(IDC_CHECK3, OnAnschl3)
	ON_BN_CLICKED(IDC_CHECK4, OnAnschl4)
	ON_BN_CLICKED(IDC_CHECK5, OnAnschl5)
	ON_BN_CLICKED(IDC_CHECK6, OnAnschl6)
	ON_BN_CLICKED(IDC_CHECK7, OnAnschl7)
	ON_BN_CLICKED(IDC_CHECK8, OnAnschl8)
	ON_BN_CLICKED(IDC_CHECK9, OnAnschl9)
	ON_EN_CHANGE(IDC_EDIT10, OnChangeEdit10)
	ON_EN_CHANGE(IDC_EDIT11, OnChangeEdit11)
	ON_EN_CHANGE(IDC_EDIT12, OnChangeEdit12)
	ON_EN_CHANGE(IDC_EDIT13, OnChangeEdit13)
	ON_EN_CHANGE(IDC_EDIT14, OnChangeEdit14)
	ON_EN_CHANGE(IDC_EDIT15, OnChangeEdit15)
	ON_EN_CHANGE(IDC_EDIT16, OnChangeEdit16)
	ON_EN_CHANGE(IDC_EDIT17, OnChangeEdit17)
	ON_EN_CHANGE(IDC_EDIT18, OnChangeEdit18)
	ON_EN_CHANGE(IDC_EDIT19, OnChangeEdit19)
	ON_EN_CHANGE(IDC_EDIT20, OnChangeEdit20)
	ON_EN_CHANGE(IDC_EDIT21, OnChangeEdit21)
	ON_EN_CHANGE(IDC_EDIT22, OnChangeEdit22)
	ON_EN_CHANGE(IDC_EDIT23, OnChangeEdit23)
	ON_EN_CHANGE(IDC_EDIT24, OnChangeEdit24)
	ON_EN_CHANGE(IDC_EDIT25, OnChangeEdit25)
	ON_EN_CHANGE(IDC_EDIT26, OnChangeEdit26)
	ON_EN_CHANGE(IDC_EDIT27, OnChangeEdit27)
	ON_EN_CHANGE(IDC_EDIT28, OnChangeEdit28)
	ON_EN_CHANGE(IDC_EDIT29, OnChangeEdit29)
	ON_EN_CHANGE(IDC_EDIT30, OnChangeEdit30)
	ON_EN_CHANGE(IDC_EDIT31, OnChangeEdit31)
	ON_EN_CHANGE(IDC_EDIT32, OnChangeEdit32)
	ON_EN_CHANGE(IDC_EDIT33, OnChangeEdit33)
	ON_EN_CHANGE(IDC_EDIT34, OnChangeEdit34)
	ON_EN_CHANGE(IDC_EDIT35, OnChangeEdit35)
	ON_EN_CHANGE(IDC_EDIT36, OnChangeEdit36)
	ON_EN_CHANGE(IDC_EDIT37, OnChangeEdit37)
	ON_EN_CHANGE(IDC_EDIT38, OnChangeEdit38)
	ON_EN_CHANGE(IDC_EDIT39, OnChangeEdit39)
	ON_EN_CHANGE(IDC_EDIT40, OnChangeEdit40)
	ON_EN_CHANGE(IDC_EDIT41, OnChangeEdit41)
	ON_EN_CHANGE(IDC_EDIT42, OnChangeEdit42)
	ON_EN_CHANGE(IDC_EDIT43, OnChangeEdit43)
	ON_EN_CHANGE(IDC_EDIT44, OnChangeEdit44)
	ON_EN_CHANGE(IDC_EDIT45, OnChangeEdit45)
	ON_EN_CHANGE(IDC_EDIT46, OnChangeEdit46)
	ON_EN_CHANGE(IDC_EDIT47, OnChangeEdit47)
	ON_EN_CHANGE(IDC_EDIT48, OnChangeEdit48)
	ON_EN_CHANGE(IDC_EDIT49, OnChangeEdit49)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditPage3 message handlers

void CEditPage3::SetGeaendert( BOOL flag )
{
	((CErfassPrivDlg*)GetParent()) -> SetDGeaendert( flag );
}

void CEditPage3::InitData()
{
	short		i, n;
	CWnd		*pWnd;
	CPG2DSatz	*pSatz;

	for ( i = 0; i < 20; i++ )
	{
		m_strD[i].Empty();
		m_rF[i] = 0;
		m_rAF[i] = 0;
		m_bA[i] = FALSE;
	}

	m_iGebZahl = m_parrPG2H -> GetSize();
	n = m_iGebZahl - m_iOffset;
	if ( n > 20 ) n = 20;
	for ( i = 0; i < n; i++ )
	{
		pSatz = (CPG2DSatz*)m_parrPG2H -> GetAt( i + m_iOffset );
		m_strD[i] = pSatz -> m_NFP2_FLN;
		m_rF[i] = pSatz -> m_NFP2_FLG;
		m_rAF[i] = pSatz -> m_NFP2_ABF;
		pSatz -> m_NFP2_ANS.MakeUpper();
		m_bA[i] = TestYES( pSatz -> m_NFP2_ANS );
	}

	pWnd = GetDlgItem( IDC_BUTTON2 );
	ASSERT( pWnd );
	pWnd -> EnableWindow( m_iGebZahl > 0 );

	pWnd = GetDlgItem( IDC_BUTTON3 );
	ASSERT( pWnd );
	pWnd -> EnableWindow(( m_iGebZahl - m_iOffset ) > 20 );

	pWnd = GetDlgItem( IDC_BUTTON4 );
	ASSERT( pWnd );
	pWnd -> EnableWindow( m_iOffset > 0 );
}

void CEditPage3::RestoreData()
{
	short		i, n;
	CPG2DSatz	*pSatz;

	n = m_iGebZahl - m_iOffset;
	if ( n > 20 ) n = 20;
	for ( i = 0; i < n; i++ )
	{
		pSatz = (CPG2DSatz*)m_parrPG2H -> GetAt( i + m_iOffset );
		pSatz -> m_NFP2_FLN = m_strD[i];
		pSatz -> m_NFP2_FLG = m_rF[i];
		pSatz -> m_NFP2_ABF = m_rAF[i];
		if ( m_bA[i])	pSatz -> m_NFP2_ANS = "Y";
		else			pSatz -> m_NFP2_ANS = "N";
	}
}

BOOL CEditPage3::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	m_iOffset = 0;
	m_iGebZahl = m_parrPG2H -> GetSize();
	InitData();
	UpdateData( FALSE );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEditPage3::OnNeu() 
{
	CxString	text;
	CPG2DSatz	*pSatz;

	UpdateData();

	pSatz = new CPG2DSatz;
	ASSERT( pSatz );

	text.Empty();
	text.printf( "D%d", m_iGebZahl + 1 );
	pSatz -> m_NFP2_FLN = text;
	pSatz -> m_NFP2_FLG = 0;
	pSatz -> m_NFP2_ABF = 0;
	pSatz -> m_NFP2_ANS = "N";

	m_parrPG2H -> Add( pSatz );
	m_iGebZahl = m_parrPG2H -> GetSize();

	SetGeaendert();

	InitData();
	UpdateData( FALSE );
}

void CEditPage3::OnDelete() 
{
	CDeleteDialog	dlg;
	CxString		text;
	char			*txt, *pt;
	short			i;

	UpdateData();

	text = ((CPG2DSatz*)m_parrPG2H -> GetAt( 0 )) -> m_NFP2_FLN;
	for ( i = 1; i < m_parrPG2H -> GetSize(); i++ )
	{
		text += '|';
		text += ((CPG2DSatz*)m_parrPG2H -> GetAt( i )) -> m_NFP2_FLN;
	}
	dlg.m_strListe = text;
	dlg.m_strTitel.LoadString( IDS_DELE_HF );
	if ( dlg.m_strTitel.IsEmpty())
		dlg.m_strTitel = "Hofflächen löschen";

	if ( dlg.DoModal() == IDOK )
	{
		text = dlg.m_strListe;
		if ( !text.IsEmpty())
		{
			txt = text.GetBuffer( 0 );
			pt = txt;
			while ( *pt )
			{
				while ( *pt && ( *pt != '|' )) pt++;
				if ( *pt )
				{
					*pt = '\0';
					m_parrPG2H -> Remove( txt );
					*pt = '|';
					pt++;
					txt = pt;
				}
				else
				{
					m_parrPG2H -> Remove( txt );
				}
			}

			// Immer neu nummerieren!
			for ( i = 0; i < m_parrPG2H -> GetSize(); i++ )
			{
				text.Empty();
				text.printf( "D%d", i + 1 );
				((CPG2DSatz*)m_parrPG2H -> GetAt( i )) -> m_NFP2_FLN = text;
			}

			SetGeaendert();
			InitData();
			UpdateData( FALSE );
		}
	}
}	// OnDelete

void CEditPage3::OnWeiter() 
{
	UpdateData();
	m_iOffset++;
	if ( m_iOffset > ( m_iGebZahl - 2 )) m_iOffset = m_iGebZahl - 2;
	InitData();
	UpdateData( FALSE );
}

void CEditPage3::OnZurueck() 
{
	UpdateData();
	m_iOffset--;
	if ( m_iOffset < 0 ) m_iOffset = 0;
	InitData();
	UpdateData( FALSE );
}

void CEditPage3::OnAnschl1()	{	SetGeaendert();	}
void CEditPage3::OnAnschl10()	{	SetGeaendert();	}
void CEditPage3::OnAnschl11()	{	SetGeaendert();	}
void CEditPage3::OnAnschl12()	{	SetGeaendert();	}
void CEditPage3::OnAnschl13()	{	SetGeaendert();	}
void CEditPage3::OnAnschl14()	{	SetGeaendert();	}
void CEditPage3::OnAnschl15()	{	SetGeaendert();	}
void CEditPage3::OnAnschl16()	{	SetGeaendert();	}
void CEditPage3::OnAnschl17()	{	SetGeaendert();	}
void CEditPage3::OnAnschl18()	{	SetGeaendert();	}
void CEditPage3::OnAnschl19()	{	SetGeaendert();	}
void CEditPage3::OnAnschl2()	{	SetGeaendert();	}
void CEditPage3::OnAnschl20()	{	SetGeaendert();	}
void CEditPage3::OnAnschl3()	{	SetGeaendert();	}
void CEditPage3::OnAnschl4()	{	SetGeaendert();	}
void CEditPage3::OnAnschl5()	{	SetGeaendert();	}
void CEditPage3::OnAnschl6()	{	SetGeaendert();	}
void CEditPage3::OnAnschl7()	{	SetGeaendert();	}
void CEditPage3::OnAnschl8()	{	SetGeaendert();	}
void CEditPage3::OnAnschl9()	{	SetGeaendert();	}
void CEditPage3::OnChangeEdit10()	{	SetGeaendert();	}
void CEditPage3::OnChangeEdit11()	{	SetGeaendert();	}
void CEditPage3::OnChangeEdit12()	{	SetGeaendert();	}
void CEditPage3::OnChangeEdit13()	{	SetGeaendert();	}
void CEditPage3::OnChangeEdit14()	{	SetGeaendert();	}
void CEditPage3::OnChangeEdit15()	{	SetGeaendert();	}
void CEditPage3::OnChangeEdit16()	{	SetGeaendert();	}
void CEditPage3::OnChangeEdit17()	{	SetGeaendert();	}
void CEditPage3::OnChangeEdit18()	{	SetGeaendert();	}
void CEditPage3::OnChangeEdit19()	{	SetGeaendert();	}
void CEditPage3::OnChangeEdit20()	{	SetGeaendert();	}
void CEditPage3::OnChangeEdit21()	{	SetGeaendert();	}
void CEditPage3::OnChangeEdit22()	{	SetGeaendert();	}
void CEditPage3::OnChangeEdit23()	{	SetGeaendert();	}
void CEditPage3::OnChangeEdit24()	{	SetGeaendert();	}
void CEditPage3::OnChangeEdit25()	{	SetGeaendert();	}
void CEditPage3::OnChangeEdit26()	{	SetGeaendert();	}
void CEditPage3::OnChangeEdit27()	{	SetGeaendert();	}
void CEditPage3::OnChangeEdit28()	{	SetGeaendert();	}
void CEditPage3::OnChangeEdit29()	{	SetGeaendert();	}
void CEditPage3::OnChangeEdit30()	{	SetGeaendert();	}
void CEditPage3::OnChangeEdit31()	{	SetGeaendert();	}
void CEditPage3::OnChangeEdit32()	{	SetGeaendert();	}
void CEditPage3::OnChangeEdit33()	{	SetGeaendert();	}
void CEditPage3::OnChangeEdit34()	{	SetGeaendert();	}
void CEditPage3::OnChangeEdit35()	{	SetGeaendert();	}
void CEditPage3::OnChangeEdit36()	{	SetGeaendert();	}
void CEditPage3::OnChangeEdit37()	{	SetGeaendert();	}
void CEditPage3::OnChangeEdit38()	{	SetGeaendert();	}
void CEditPage3::OnChangeEdit39()	{	SetGeaendert();	}
void CEditPage3::OnChangeEdit40()	{	SetGeaendert();	}
void CEditPage3::OnChangeEdit41()	{	SetGeaendert();	}
void CEditPage3::OnChangeEdit42()	{	SetGeaendert();	}
void CEditPage3::OnChangeEdit43()	{	SetGeaendert();	}
void CEditPage3::OnChangeEdit44()	{	SetGeaendert();	}
void CEditPage3::OnChangeEdit45()	{	SetGeaendert();	}
void CEditPage3::OnChangeEdit46()	{	SetGeaendert();	}
void CEditPage3::OnChangeEdit47()	{	SetGeaendert();	}
void CEditPage3::OnChangeEdit48()	{	SetGeaendert();	}
void CEditPage3::OnChangeEdit49()	{	SetGeaendert();	}
