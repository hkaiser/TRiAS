// EdPage5.cpp : implementation file
//

#include "stdafx.h"
#include "GbmTRiAS.h"
#include "EdPage5.h"

#include "ErfassPrivDlg.h"
#include "DeleteDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditPage5 property page

IMPLEMENT_DYNCREATE(CEditPage5, CPropertyPage)

CEditPage5::CEditPage5() : CPropertyPage(CEditPage5::IDD)
{
	//{{AFX_DATA_INIT(CEditPage5)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	int	i;
	for ( i = 0; i < 10; i++ )
	{
		m_strG[i].Empty();
		m_rGF[i] = 0;
		m_rVZ[i] = 0;
		m_rGH[i] = 0;
		m_bV[i] = FALSE;
	}
}

CEditPage5::~CEditPage5()
{
}

void CEditPage5::SpecialDDX_Text( CDataExchange *pDX, UINT id, double &r )
{
	if ( !pDX -> m_bSaveAndValidate )
	{
		CWnd	*pWnd = GetDlgItem( id );
		if ( pWnd )
		{
			pWnd -> ShowWindow( SW_SHOW );
			pWnd -> EnableWindow( TRUE );
	}	}

	DDX_Text( pDX, id, r );
}

void CEditPage5::SpecialDDX_Check( CDataExchange *pDX, UINT id, BOOL &r )
{
	if ( !pDX -> m_bSaveAndValidate )
	{
		CWnd	*pWnd = GetDlgItem( id );
		if ( pWnd )
		{
			pWnd -> ShowWindow( SW_SHOW );
			pWnd -> EnableWindow( TRUE );
	}	}

	DDX_Check( pDX, id, r );
}

void CEditPage5::HideControl( CDataExchange *pDX, UINT id )
{
	if ( !pDX -> m_bSaveAndValidate )
	{
		CWnd	*pWnd = GetDlgItem( id );
		if ( pWnd )
		{
			pWnd -> ShowWindow( SW_HIDE );
			pWnd -> EnableWindow( FALSE );
	}	}
}

void CEditPage5::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditPage5)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_TEXTG1, m_strG[0]);
	DDX_Text(pDX, IDC_TEXTG2, m_strG[1]);
	DDX_Text(pDX, IDC_TEXTG3, m_strG[2]);
	DDX_Text(pDX, IDC_TEXTG4, m_strG[3]);
	DDX_Text(pDX, IDC_TEXTG5, m_strG[4]);
	DDX_Text(pDX, IDC_TEXTG6, m_strG[5]);
	DDX_Text(pDX, IDC_TEXTG7, m_strG[6]);
	DDX_Text(pDX, IDC_TEXTG8, m_strG[7]);
	DDX_Text(pDX, IDC_TEXTG9, m_strG[8]);
	DDX_Text(pDX, IDC_TEXTG10, m_strG[9]);
	short i = m_iGebZahl - m_iOffset;

	if ( i > 0 )
	{	SpecialDDX_Text(pDX, IDC_ED_GF1, m_rGF[0]);
		SpecialDDX_Text(pDX, IDC_ED_VZ1, m_rVZ[0]);
		SpecialDDX_Text(pDX, IDC_ED_GH1, m_rGH[0]);
		SpecialDDX_Check(pDX, IDC_ED_VA1, m_bV[0]);	}
	else
	{	HideControl(pDX, IDC_ED_GF1);
		HideControl(pDX, IDC_ED_VZ1);
		HideControl(pDX, IDC_ED_GH1);
		HideControl(pDX, IDC_ED_VA1);	}
	
	if ( i > 1 )
	{	SpecialDDX_Text(pDX, IDC_ED_GF2, m_rGF[1]);
		SpecialDDX_Text(pDX, IDC_ED_VZ2, m_rVZ[1]);
		SpecialDDX_Text(pDX, IDC_ED_GH2, m_rGH[1]);
		SpecialDDX_Check(pDX, IDC_ED_VA2, m_bV[1]);	}
	else
	{	HideControl(pDX, IDC_ED_GF2);
		HideControl(pDX, IDC_ED_VZ2);
		HideControl(pDX, IDC_ED_GH2);
		HideControl(pDX, IDC_ED_VA2);	}
	
	if ( i > 2 )
	{	SpecialDDX_Text(pDX, IDC_ED_GF3, m_rGF[2]);
		SpecialDDX_Text(pDX, IDC_ED_VZ3, m_rVZ[2]);
		SpecialDDX_Text(pDX, IDC_ED_GH3, m_rGH[2]);
		SpecialDDX_Check(pDX, IDC_ED_VA3, m_bV[2]);	}
	else
	{	HideControl(pDX, IDC_ED_GF3);
		HideControl(pDX, IDC_ED_VZ3);
		HideControl(pDX, IDC_ED_GH3);
		HideControl(pDX, IDC_ED_VA3);	}
	
	if ( i > 3 )
	{	SpecialDDX_Text(pDX, IDC_ED_GF4, m_rGF[3]);
		SpecialDDX_Text(pDX, IDC_ED_VZ4, m_rVZ[3]);
		SpecialDDX_Text(pDX, IDC_ED_GH4, m_rGH[3]);
		SpecialDDX_Check(pDX, IDC_ED_VA4, m_bV[3]);	}
	else
	{	HideControl(pDX, IDC_ED_GF4);
		HideControl(pDX, IDC_ED_VZ4);
		HideControl(pDX, IDC_ED_GH4);
		HideControl(pDX, IDC_ED_VA4);	}
	
	if ( i > 4 )
	{	SpecialDDX_Text(pDX, IDC_ED_GF5, m_rGF[4]);
		SpecialDDX_Text(pDX, IDC_ED_VZ5, m_rVZ[4]);
		SpecialDDX_Text(pDX, IDC_ED_GH5, m_rGH[4]);
		SpecialDDX_Check(pDX, IDC_ED_VA5, m_bV[4]);	}
	else
	{	HideControl(pDX, IDC_ED_GF5);
		HideControl(pDX, IDC_ED_VZ5);
		HideControl(pDX, IDC_ED_GH5);
		HideControl(pDX, IDC_ED_VA5);	}
	
	if ( i > 5 )
	{	SpecialDDX_Text(pDX, IDC_ED_GF6, m_rGF[5]);
		SpecialDDX_Text(pDX, IDC_ED_VZ6, m_rVZ[5]);
		SpecialDDX_Text(pDX, IDC_ED_GH6, m_rGH[5]);
		SpecialDDX_Check(pDX, IDC_ED_VA6, m_bV[5]);	}
	else
	{	HideControl(pDX, IDC_ED_GF6);
		HideControl(pDX, IDC_ED_VZ6);
		HideControl(pDX, IDC_ED_GH6);
		HideControl(pDX, IDC_ED_VA6);	}
	
	if ( i > 6 )
	{	SpecialDDX_Text(pDX, IDC_ED_GF7, m_rGF[6]);
		SpecialDDX_Text(pDX, IDC_ED_VZ7, m_rVZ[6]);
		SpecialDDX_Text(pDX, IDC_ED_GH7, m_rGH[6]);
		SpecialDDX_Check(pDX, IDC_ED_VA7, m_bV[6]);	}
	else
	{	HideControl(pDX, IDC_ED_GF7);
		HideControl(pDX, IDC_ED_VZ7);
		HideControl(pDX, IDC_ED_GH7);
		HideControl(pDX, IDC_ED_VA7);	}
	
	if ( i > 7 )
	{	SpecialDDX_Text(pDX, IDC_ED_GF8, m_rGF[7]);
		SpecialDDX_Text(pDX, IDC_ED_VZ8, m_rVZ[7]);
		SpecialDDX_Text(pDX, IDC_ED_GH8, m_rGH[7]);
		SpecialDDX_Check(pDX, IDC_ED_VA8, m_bV[7]);	}
	else
	{	HideControl(pDX, IDC_ED_GF8);
		HideControl(pDX, IDC_ED_VZ8);
		HideControl(pDX, IDC_ED_GH8);
		HideControl(pDX, IDC_ED_VA8);	}
	
	if ( i > 8 )
	{	SpecialDDX_Text(pDX, IDC_ED_GF9, m_rGF[8]);
		SpecialDDX_Text(pDX, IDC_ED_VZ9, m_rVZ[8]);
		SpecialDDX_Text(pDX, IDC_ED_GH9, m_rGH[8]);
		SpecialDDX_Check(pDX, IDC_ED_VA9, m_bV[8]);	}
	else
	{	HideControl(pDX, IDC_ED_GF9);
		HideControl(pDX, IDC_ED_VZ9);
		HideControl(pDX, IDC_ED_GH9);
		HideControl(pDX, IDC_ED_VA9);	}
	
	if ( i > 9 )
	{	SpecialDDX_Text(pDX, IDC_ED_GF10, m_rGF[9]);
		SpecialDDX_Text(pDX, IDC_ED_VZ10, m_rVZ[9]);
		SpecialDDX_Text(pDX, IDC_ED_GH10, m_rGH[9]);
		SpecialDDX_Check(pDX, IDC_ED_VA10, m_bV[9]);	}
	else
	{	HideControl(pDX, IDC_ED_GF10);
		HideControl(pDX, IDC_ED_VZ10);
		HideControl(pDX, IDC_ED_GH10);
		HideControl(pDX, IDC_ED_VA10);	}

	if ( pDX -> m_bSaveAndValidate )		RestoreData();
}


BEGIN_MESSAGE_MAP(CEditPage5, CPropertyPage)
	//{{AFX_MSG_MAP(CEditPage5)
	ON_BN_CLICKED(IDC_BUTTON1, OnNeu)
	ON_BN_CLICKED(IDC_BUTTON2, OnDelete)
	ON_BN_CLICKED(IDC_BUTTON3, OnWeiter)
	ON_BN_CLICKED(IDC_BUTTON4, OnZurueck)
	ON_EN_CHANGE(IDC_ED_GF1, OnChangeEdGf1)
	ON_EN_CHANGE(IDC_ED_GF10, OnChangeEdGf10)
	ON_EN_CHANGE(IDC_ED_GF2, OnChangeEdGf2)
	ON_EN_CHANGE(IDC_ED_GF3, OnChangeEdGf3)
	ON_EN_CHANGE(IDC_ED_GF4, OnChangeEdGf4)
	ON_EN_CHANGE(IDC_ED_GF5, OnChangeEdGf5)
	ON_EN_CHANGE(IDC_ED_GF6, OnChangeEdGf6)
	ON_EN_CHANGE(IDC_ED_GF7, OnChangeEdGf7)
	ON_EN_CHANGE(IDC_ED_GF8, OnChangeEdGf8)
	ON_EN_CHANGE(IDC_ED_GF9, OnChangeEdGf9)
	ON_EN_CHANGE(IDC_ED_GH1, OnChangeEdGh1)
	ON_EN_CHANGE(IDC_ED_GH10, OnChangeEdGh10)
	ON_EN_CHANGE(IDC_ED_GH2, OnChangeEdGh2)
	ON_EN_CHANGE(IDC_ED_GH3, OnChangeEdGh3)
	ON_EN_CHANGE(IDC_ED_GH4, OnChangeEdGh4)
	ON_EN_CHANGE(IDC_ED_GH5, OnChangeEdGh5)
	ON_EN_CHANGE(IDC_ED_GH6, OnChangeEdGh6)
	ON_EN_CHANGE(IDC_ED_GH7, OnChangeEdGh7)
	ON_EN_CHANGE(IDC_ED_GH8, OnChangeEdGh8)
	ON_EN_CHANGE(IDC_ED_GH9, OnChangeEdGh9)
	ON_BN_CLICKED(IDC_ED_VA1, OnEdVa1)
	ON_BN_CLICKED(IDC_ED_VA10, OnEdVa10)
	ON_BN_CLICKED(IDC_ED_VA2, OnEdVa2)
	ON_BN_CLICKED(IDC_ED_VA3, OnEdVa3)
	ON_BN_CLICKED(IDC_ED_VA4, OnEdVa4)
	ON_BN_CLICKED(IDC_ED_VA5, OnEdVa5)
	ON_BN_CLICKED(IDC_ED_VA6, OnEdVa6)
	ON_BN_CLICKED(IDC_ED_VA7, OnEdVa7)
	ON_BN_CLICKED(IDC_ED_VA8, OnEdVa8)
	ON_BN_CLICKED(IDC_ED_VA9, OnEdVa9)
	ON_EN_CHANGE(IDC_ED_VZ1, OnChangeEdVz1)
	ON_EN_CHANGE(IDC_ED_VZ10, OnChangeEdVz10)
	ON_EN_CHANGE(IDC_ED_VZ2, OnChangeEdVz2)
	ON_EN_CHANGE(IDC_ED_VZ3, OnChangeEdVz3)
	ON_EN_CHANGE(IDC_ED_VZ4, OnChangeEdVz4)
	ON_EN_CHANGE(IDC_ED_VZ5, OnChangeEdVz5)
	ON_EN_CHANGE(IDC_ED_VZ6, OnChangeEdVz6)
	ON_EN_CHANGE(IDC_ED_VZ7, OnChangeEdVz7)
	ON_EN_CHANGE(IDC_ED_VZ8, OnChangeEdVz8)
	ON_EN_CHANGE(IDC_ED_VZ9, OnChangeEdVz9)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditPage5 message handlers

BOOL CEditPage5::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	m_iOffset = 0;
	m_iGebZahl = m_parrPG1GB -> GetSize();
	InitData();
	UpdateData( FALSE );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEditPage5 :: InitData()
{
	short		i, n;
	CWnd		*pWnd;
	CPG1GBSatz	*pSatz;
	CxString	text;

	for ( i = 0; i < 10; i++ )
	{
		m_strG[i].Empty();
		m_rGF[i] = 0;
		m_rVZ[i] = 0;
		m_rGH[i] = 0;
		m_bV[i] = FALSE;
	}

	m_iGebZahl = m_parrPG1GB -> GetSize();
	n = m_iGebZahl - m_iOffset;
	if ( n > 10 ) n = 10;
	for ( i = 0; i < n; i++ )
	{
		pSatz = (CPG1GBSatz*)m_parrPG1GB -> GetAt( i + m_iOffset );
		text.Empty();
		text.printf( "Gebäude %d", int( pSatz -> m_NFP1_GNR ));
		m_strG[i] = text;
		m_rGF[i] = pSatz -> m_NFP1_GFL;
		m_rVZ[i] = pSatz -> m_NFP1_VOL;
		m_rGH[i] = pSatz -> m_NFP1_HOH;
		m_bV[i] = TestYES( pSatz -> m_NFP1_ANL );
	}

	pWnd = GetDlgItem( IDC_BUTTON2 );
	ASSERT( pWnd );
	pWnd -> EnableWindow( m_iGebZahl > 0 );

	pWnd = GetDlgItem( IDC_BUTTON3 );
	ASSERT( pWnd );
	pWnd -> EnableWindow(( m_iGebZahl - m_iOffset ) > 10 );

	pWnd = GetDlgItem( IDC_BUTTON4 );
	ASSERT( pWnd );
	pWnd -> EnableWindow( m_iOffset > 0 );
}	// InitData

void CEditPage5 :: RestoreData()
{
	short		i, n;
	CPG1GBSatz	*pSatz;
	char		*txt;

	n = m_iGebZahl - m_iOffset;
	if ( n > 10 ) n = 10;
	for ( i = 0; i < n; i++ )
	{
		pSatz = (CPG1GBSatz*)m_parrPG1GB -> GetAt( i + m_iOffset );
		txt = m_strG[i].GetBuffer(0);
		while ( *txt && ( *txt != ' ' ))	txt++;
		if ( *txt )		pSatz -> m_NFP1_GNR = atoi( ++txt );
		else			pSatz -> m_NFP1_GNR = 0;
		m_strG[i].ReleaseBuffer();
//		pSatz -> m_NFP1_GNR = m_strG[i];
		pSatz -> m_NFP1_GFL = m_rGF[i];
		pSatz -> m_NFP1_VOL = m_rVZ[i];
		pSatz -> m_NFP1_HOH = m_rGH[i];
		if ( m_bV[i])	pSatz -> m_NFP1_ANL = "Y";
		else			pSatz -> m_NFP1_ANL = "N";
	}
}	// RestoreData

void CEditPage5::OnNeu() 
{
//	CxString	text;
	CPG1GBSatz	*pSatz;

	UpdateData();

	pSatz = new CPG1GBSatz;
	ASSERT( pSatz );

//	text.Empty();
//	text.printf( "Gebäude %d", m_iGebZahl + 1 );
//	pSatz -> m_NFP1_GNR = text;
	pSatz -> m_NFP1_GNR = m_iGebZahl + 1;
	pSatz -> m_NFP1_GFL = 0;
	pSatz -> m_NFP1_VOL = 0;
	pSatz -> m_NFP1_HOH = 0;
	pSatz -> m_NFP1_ANL = "N";

	m_parrPG1GB -> Add( pSatz );
	m_iGebZahl = m_parrPG1GB -> GetSize();

	SetGeaendert();

	InitData();
	UpdateData( FALSE );
}

void CEditPage5::OnDelete() 
{
	CDeleteDialog	dlg;
	CxString		text, item;
	char			*txt, *pt;
	short			i;

	UpdateData();

//	text = ((CPG1GBSatz*)m_parrPG1GB -> GetAt( 0 )) -> m_NFP1_GNR;
	text.Empty();
	text.printf( "Gebäude %d", int(((CPG1GBSatz*)m_parrPG1GB -> GetAt( 0 )) -> m_NFP1_GNR ));
	for ( i = 1; i < m_parrPG1GB -> GetSize(); i++ )
	{
		text += '|';
		item.Empty();
		item.printf( "Gebäude %d", int(((CPG1GBSatz*)m_parrPG1GB -> GetAt( i )) -> m_NFP1_GNR ));
		text += item;
//		text += ((CPG1GBSatz*)m_parrPG1GB -> GetAt( i )) -> m_NFP1_GNR;
	}
	dlg.m_strListe = text;
	dlg.m_strTitel.LoadString( IDS_DELE_GB );
	if ( dlg.m_strTitel.IsEmpty())
		dlg.m_strTitel = "Gebäude löschen";

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
					m_parrPG1GB -> Remove( txt );
					*pt = '|';
					pt++;
					txt = pt;
				}
				else
				{
					m_parrPG1GB -> Remove( txt );
			}	}

			for ( i = 0; i < m_parrPG1GB -> GetSize(); i++ )
			{
				((CPG1GBSatz*)m_parrPG1GB -> GetAt( i )) -> m_NFP1_GNR = i + 1;
			}			

			SetGeaendert();
			InitData();
			UpdateData( FALSE );
	}	}
}

void CEditPage5::OnWeiter() 
{
	UpdateData();
	m_iOffset++;
	if ( m_iOffset > ( m_iGebZahl - 2 )) m_iOffset = m_iGebZahl - 2;
	InitData();
	UpdateData( FALSE );
}

void CEditPage5::OnZurueck() 
{
	UpdateData();
	m_iOffset--;
	if ( m_iOffset < 0 ) m_iOffset = 0;
	InitData();
	UpdateData( FALSE );
}

void CEditPage5::SetGeaendert( BOOL f )
{	((CErfassPrivDlg*)GetParent()) -> SetGBGeaendert( f );
}	// SetGeaendert

void CEditPage5::OnChangeEdGf1()	{	SetGeaendert();	}
void CEditPage5::OnChangeEdGf10()	{	SetGeaendert();	}
void CEditPage5::OnChangeEdGf2()	{	SetGeaendert();	}
void CEditPage5::OnChangeEdGf3()	{	SetGeaendert();	}
void CEditPage5::OnChangeEdGf4()	{	SetGeaendert();	}
void CEditPage5::OnChangeEdGf5()	{	SetGeaendert();	}
void CEditPage5::OnChangeEdGf6()	{	SetGeaendert();	}
void CEditPage5::OnChangeEdGf7()	{	SetGeaendert();	}
void CEditPage5::OnChangeEdGf8()	{	SetGeaendert();	}
void CEditPage5::OnChangeEdGf9()	{	SetGeaendert();	}
void CEditPage5::OnChangeEdGh1()	{	SetGeaendert();	}
void CEditPage5::OnChangeEdGh10()	{	SetGeaendert();	}
void CEditPage5::OnChangeEdGh2()	{	SetGeaendert();	}
void CEditPage5::OnChangeEdGh3()	{	SetGeaendert();	}
void CEditPage5::OnChangeEdGh4()	{	SetGeaendert();	}
void CEditPage5::OnChangeEdGh5()	{	SetGeaendert();	}
void CEditPage5::OnChangeEdGh6()	{	SetGeaendert();	}
void CEditPage5::OnChangeEdGh7()	{	SetGeaendert();	}
void CEditPage5::OnChangeEdGh8()	{	SetGeaendert();	}
void CEditPage5::OnChangeEdGh9()	{	SetGeaendert();	}
void CEditPage5::OnEdVa1()	{	SetGeaendert();	}
void CEditPage5::OnEdVa10()	{	SetGeaendert();	}
void CEditPage5::OnEdVa2()	{	SetGeaendert();	}
void CEditPage5::OnEdVa3()	{	SetGeaendert();	}
void CEditPage5::OnEdVa4()	{	SetGeaendert();	}
void CEditPage5::OnEdVa5()	{	SetGeaendert();	}
void CEditPage5::OnEdVa6()	{	SetGeaendert();	}
void CEditPage5::OnEdVa7()	{	SetGeaendert();	}
void CEditPage5::OnEdVa8()	{	SetGeaendert();	}
void CEditPage5::OnEdVa9()	{	SetGeaendert();	}
void CEditPage5::OnChangeEdVz1()	{	SetGeaendert();	}
void CEditPage5::OnChangeEdVz10()	{	SetGeaendert();	}
void CEditPage5::OnChangeEdVz2()	{	SetGeaendert();	}
void CEditPage5::OnChangeEdVz3()	{	SetGeaendert();	}
void CEditPage5::OnChangeEdVz4()	{	SetGeaendert();	}
void CEditPage5::OnChangeEdVz5()	{	SetGeaendert();	}
void CEditPage5::OnChangeEdVz6()	{	SetGeaendert();	}
void CEditPage5::OnChangeEdVz7()	{	SetGeaendert();	}
void CEditPage5::OnChangeEdVz8()	{	SetGeaendert();	}
void CEditPage5::OnChangeEdVz9()	{	SetGeaendert();	}
