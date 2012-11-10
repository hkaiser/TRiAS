// EditPage7.cpp : implementation file
//

#include "stdafx.h"
#include "GbmTRiAS.h"
#include "EditPage7.h"
#include "SetNF_PG4.h"

#include "ErfassPrivDlg.h"
#include "DeleteDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditPage7 property page

IMPLEMENT_DYNCREATE(CEditPage7, CPropertyPage)

CEditPage7::CEditPage7() : CPropertyPage(CEditPage7::IDD)
{
	//{{AFX_DATA_INIT(CEditPage7)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	for ( short i = 0; i < 4; i++ )
	{
		m_lNenn[i]   = 1000;
		m_lZaehl[i]  = 1000;
		m_bHer[i]    = TRUE;
		m_strTeil[i] = "";
		m_strOrt[i]  = "";
		m_strPLZ[i]  = "";
		m_strStr[i]  = "";
		m_strName[i] = "";
	}
	m_iEigZahl = 0;
	m_iOffset  = 0;
	m_bMiteigentum = TRUE;
}

CEditPage7::~CEditPage7()
{
}

void CEditPage7::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditPage7)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_ETXT1, m_strEig[0]);
	DDX_Text(pDX, IDC_ETXT2, m_strEig[1]);
	DDX_Text(pDX, IDC_ETXT3, m_strEig[2]);
	DDX_Text(pDX, IDC_ETXT4, m_strEig[3]);
	short	i = m_iEigZahl - m_iOffset;

	if ( i > 0 )
	{	SpecialDDX_Text(pDX, IDC_NTXT1, m_strName[0]);
		SpecialDDX_Text(pDX, IDC_STXT1, m_strStr[0]);
		SpecialDDX_Text(pDX, IDC_PTXT1, m_strPLZ[0]);
		SpecialDDX_Text(pDX, IDC_EDIT1, m_strOrt[0]);
		SpecialDDX_Text(pDX, IDC_EDIT2, m_lZaehl[0]);
		SpecialDDX_Text(pDX, IDC_EDIT3, m_lNenn[0]);
		SpecialDDX_Text(pDX, IDC_EDIT4, m_strTeil[0]);
		SpecialDDX_Check(pDX, IDC_CHK1, m_bHer[0]);
		ShowControl(pDX, IDC_FRAME1);
	}
	else
	{	ShowControl(pDX, IDC_NTXT1, FALSE);
		ShowControl(pDX, IDC_STXT1, FALSE);
		ShowControl(pDX, IDC_PTXT1, FALSE);
		ShowControl(pDX, IDC_EDIT1, FALSE);
		ShowControl(pDX, IDC_EDIT2, FALSE);
		ShowControl(pDX, IDC_EDIT3, FALSE);
		ShowControl(pDX, IDC_EDIT4, FALSE);
		ShowControl(pDX, IDC_CHK1, FALSE);
		ShowControl(pDX, IDC_FRAME1, FALSE);
	}
	

	if ( i > 1 )
	{	SpecialDDX_Text(pDX, IDC_NTXT2, m_strName[1]);
		SpecialDDX_Text(pDX, IDC_STXT2, m_strStr[1]);
		SpecialDDX_Text(pDX, IDC_PTXT2, m_strPLZ[1]);
		SpecialDDX_Text(pDX, IDC_EDIT5, m_strOrt[1]);
		SpecialDDX_Text(pDX, IDC_EDIT6, m_lZaehl[1]);
		SpecialDDX_Text(pDX, IDC_EDIT7, m_lNenn[1]);
		SpecialDDX_Text(pDX, IDC_EDIT8, m_strTeil[1]);
		SpecialDDX_Check(pDX, IDC_CHK2, m_bHer[1]);
		ShowControl(pDX, IDC_FRAME2);
	}
	else
	{	ShowControl(pDX, IDC_NTXT2, FALSE);
		ShowControl(pDX, IDC_STXT2, FALSE);
		ShowControl(pDX, IDC_PTXT2, FALSE);
		ShowControl(pDX, IDC_EDIT5, FALSE);
		ShowControl(pDX, IDC_EDIT6, FALSE);
		ShowControl(pDX, IDC_EDIT7, FALSE);
		ShowControl(pDX, IDC_EDIT8, FALSE);
		ShowControl(pDX, IDC_CHK2, FALSE);
		ShowControl(pDX, IDC_FRAME2, FALSE);
	}

	if ( i > 2 )
	{	SpecialDDX_Text(pDX, IDC_NTXT3, m_strName[2]);
		SpecialDDX_Text(pDX, IDC_STXT3, m_strStr[2]);
		SpecialDDX_Text(pDX, IDC_PTXT3, m_strPLZ[2]);
		SpecialDDX_Text(pDX, IDC_EDIT53, m_strOrt[2]);
		SpecialDDX_Text(pDX, IDC_EDIT9, m_lZaehl[2]);
		SpecialDDX_Text(pDX, IDC_EDIT10, m_lNenn[2]);
		SpecialDDX_Text(pDX, IDC_EDIT11, m_strTeil[2]);
		SpecialDDX_Check(pDX, IDC_CHK3, m_bHer[2]);
		ShowControl(pDX, IDC_FRAME3);
	}
	else
	{	ShowControl(pDX, IDC_NTXT3, FALSE);
		ShowControl(pDX, IDC_STXT3, FALSE);
		ShowControl(pDX, IDC_PTXT3, FALSE);
		ShowControl(pDX, IDC_EDIT53, FALSE);
		ShowControl(pDX, IDC_EDIT9, FALSE);
		ShowControl(pDX, IDC_EDIT10, FALSE);
		ShowControl(pDX, IDC_EDIT11, FALSE);
		ShowControl(pDX, IDC_CHK3, FALSE);
		ShowControl(pDX, IDC_FRAME3, FALSE);
	}

	if ( i > 3 )
	{	SpecialDDX_Text(pDX, IDC_NTXT4, m_strName[3]);
		SpecialDDX_Text(pDX, IDC_STXT4, m_strStr[3]);
		SpecialDDX_Text(pDX, IDC_PTXT4, m_strPLZ[3]);
		SpecialDDX_Text(pDX, IDC_EDIT12, m_strOrt[3]);
		SpecialDDX_Text(pDX, IDC_EDIT13, m_lZaehl[3]);
		SpecialDDX_Text(pDX, IDC_EDIT14, m_lNenn[3]);
		SpecialDDX_Text(pDX, IDC_EDIT15, m_strTeil[3]);
		SpecialDDX_Check(pDX, IDC_CHK4, m_bHer[3]);
		ShowControl(pDX, IDC_FRAME4);
	}
	else
	{	ShowControl(pDX, IDC_NTXT4, FALSE);
		ShowControl(pDX, IDC_STXT4, FALSE);
		ShowControl(pDX, IDC_PTXT4, FALSE);
		ShowControl(pDX, IDC_EDIT12, FALSE);
		ShowControl(pDX, IDC_EDIT13, FALSE);
		ShowControl(pDX, IDC_EDIT14, FALSE);
		ShowControl(pDX, IDC_EDIT15, FALSE);
		ShowControl(pDX, IDC_CHK4, FALSE);
		ShowControl(pDX, IDC_FRAME4, FALSE);
	}

	if ( pDX -> m_bSaveAndValidate )		RestoreData();
}


BEGIN_MESSAGE_MAP(CEditPage7, CPropertyPage)
	//{{AFX_MSG_MAP(CEditPage7)
	ON_BN_CLICKED(IDC_BUTTON1, OnNeu)
	ON_BN_CLICKED(IDC_BUTTON2, OnDelete)
	ON_BN_CLICKED(IDC_BUTTON3, OnWeiter)
	ON_BN_CLICKED(IDC_BUTTON4, OnZurueck)
	ON_BN_CLICKED(IDC_CHK1, OnModify)
	ON_BN_CLICKED(IDC_CHK2, OnModify)
	ON_BN_CLICKED(IDC_CHK3, OnModify)
	ON_BN_CLICKED(IDC_CHK4, OnModify)
	ON_EN_CHANGE(IDC_EDIT1, OnModify)
	ON_EN_CHANGE(IDC_EDIT10, OnModify)
	ON_EN_CHANGE(IDC_EDIT11, OnModify)
	ON_EN_CHANGE(IDC_EDIT12, OnModify)
	ON_EN_CHANGE(IDC_EDIT13, OnModify)
	ON_EN_CHANGE(IDC_EDIT14, OnModify)
	ON_EN_CHANGE(IDC_EDIT15, OnModify)
	ON_EN_CHANGE(IDC_EDIT2, OnModify)
	ON_EN_CHANGE(IDC_EDIT3, OnModify)
	ON_EN_CHANGE(IDC_EDIT4, OnModify)
	ON_EN_CHANGE(IDC_EDIT5, OnModify)
	ON_EN_CHANGE(IDC_EDIT53, OnModify)
	ON_EN_CHANGE(IDC_EDIT6, OnModify)
	ON_EN_CHANGE(IDC_EDIT7, OnModify)
	ON_EN_CHANGE(IDC_EDIT8, OnModify)
	ON_EN_CHANGE(IDC_EDIT9, OnModify)
	ON_EN_CHANGE(IDC_NTXT1, OnModify)
	ON_EN_CHANGE(IDC_NTXT2, OnModify)
	ON_EN_CHANGE(IDC_NTXT3, OnModify)
	ON_EN_CHANGE(IDC_NTXT4, OnModify)
	ON_EN_CHANGE(IDC_PTXT1, OnModify)
	ON_EN_CHANGE(IDC_PTXT2, OnModify)
	ON_EN_CHANGE(IDC_PTXT3, OnModify)
	ON_EN_CHANGE(IDC_PTXT4, OnModify)
	ON_BN_CLICKED(IDC_RADIO1, OnModify)
	ON_BN_CLICKED(IDC_RADIO2, OnModify)
	ON_EN_CHANGE(IDC_STXT1, OnModify)
	ON_EN_CHANGE(IDC_STXT2, OnModify)
	ON_EN_CHANGE(IDC_STXT3, OnModify)
	ON_EN_CHANGE(IDC_STXT4, OnModify)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditPage7 message handlers

void CEditPage7::SpecialDDX_Text( CDataExchange *pDX, UINT id, long &d )
{
	if ( !pDX -> m_bSaveAndValidate )
	{
		CWnd	*pWnd = GetDlgItem( id );
		if ( pWnd )
		{
			pWnd -> ShowWindow( SW_SHOW );
			pWnd -> EnableWindow( TRUE );
	}	}

	DDX_Text( pDX, id, d );
}

void CEditPage7::SpecialDDX_Text( CDataExchange *pDX, UINT id, CString &txt )
{
	if ( !pDX -> m_bSaveAndValidate )
	{
		CWnd	*pWnd = GetDlgItem( id );
		if ( pWnd )
		{
			pWnd -> ShowWindow( SW_SHOW );
			pWnd -> EnableWindow( TRUE );
	}	}

	DDX_Text( pDX, id, txt );
}

void CEditPage7::SpecialDDX_Check( CDataExchange *pDX, UINT id, BOOL &r )
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

void CEditPage7::ShowControl( CDataExchange *pDX, UINT id, BOOL show )
{
	if ( !pDX -> m_bSaveAndValidate )
	{
		CWnd	*pWnd = GetDlgItem( id );
		if ( pWnd )
		{
			if ( show )
			{
				pWnd -> ShowWindow( SW_SHOW );
				pWnd -> EnableWindow( TRUE );
			}
			else
			{
				pWnd -> ShowWindow( SW_HIDE );
				pWnd -> EnableWindow( FALSE );
	}	}	}
}

BOOL CEditPage7::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	m_iOffset = 0;
	m_iEigZahl = m_parrEigent -> GetSize();
	InitData();
	UpdateData( FALSE );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEditPage7::InitData()
{
	short			i, n;
	CWnd			*pWnd;
	CEigentuemer	*pSatz;
	CxString		text;

	for ( i = 0; i < 4; i++ )
	{
		m_lNenn[i]   = 1000;
		m_lZaehl[i]  = 1000;
		m_bHer[i]    = TRUE;
		m_strTeil[i] = "";
		m_strOrt[i]  = "";
		m_strPLZ[i]  = "";
		m_strStr[i]  = "";
		m_strName[i] = "";
	}

	m_iEigZahl = m_parrEigent -> GetSize();
	n = m_iEigZahl - m_iOffset;
	if ( n > 4 )	n = 4;
	for ( i = 0; i < n; i++ )
	{
		pSatz = (CEigentuemer*)m_parrEigent -> GetAt( i + m_iOffset );
		text.Empty();
		text.printf( "Eigentümer %d", int( i + m_iOffset + 1 ));
		m_strEig[i]  = text;
		m_strName[i] = pSatz -> m_NFP4_ENA;
		m_strStr[i]  = pSatz -> m_NFP4_EAN;
		m_strPLZ[i]  = pSatz -> m_NFP4_EPL;
		m_strOrt[i]  = pSatz -> m_NFP4_EOR;
		m_lNenn[i]   = pSatz -> m_NFP4_PN;
		m_lZaehl[i]  = pSatz -> m_NFP4_PZ;
		m_bHer[i]    = TestYES( pSatz -> m_NFP4_HER );
	}

	pWnd = GetDlgItem( IDC_BUTTON2 );
	ASSERT( pWnd );
	pWnd -> EnableWindow( m_iEigZahl > 0 );

	pWnd = GetDlgItem( IDC_BUTTON3 );
	ASSERT( pWnd );
	pWnd -> EnableWindow(( m_iEigZahl - m_iOffset ) > 4 );

	pWnd = GetDlgItem( IDC_BUTTON4 );
	ASSERT( pWnd );
	pWnd -> EnableWindow( m_iOffset > 0 );

	pWnd = GetDlgItem( IDC_RADIO1 );
	ASSERT( pWnd );
	if ( m_iEigZahl > 1 )
	{
		((CButton*)pWnd) -> SetCheck( m_bMiteigentum ? 1 : 0 );
		pWnd -> EnableWindow( TRUE );
	}
	else
	{
		((CButton*)pWnd) -> SetCheck( 0 );
		pWnd -> EnableWindow( FALSE );
	}

	pWnd = GetDlgItem( IDC_RADIO2 );
	ASSERT( pWnd );
	if ( m_iEigZahl > 1 )
	{
		((CButton*)pWnd) -> SetCheck( m_bMiteigentum ? 0 : 1 );
		pWnd -> EnableWindow( TRUE );
	}
	else
	{
		((CButton*)pWnd) -> SetCheck( 0 );
		pWnd -> EnableWindow( FALSE );
	}
}

void CEditPage7::RestoreData()
{
	short			i, n;
	double			anteil, gesamt;
	CEigentuemer	*pSatz;

	m_bDivError = FALSE;
	m_bSummError = FALSE;
	gesamt = 0.0;
	n = m_iEigZahl - m_iOffset;
	if ( n > 4 ) n = 4;
	for ( i = 0; i < n; i++ )
	{
		if ( m_bHer[i])
		{
			anteil = 0.0;
			if ( 0L != m_lNenn[i])	anteil = (double)m_lZaehl[i] / (double)m_lNenn[i];
			else					m_bDivError = TRUE;
			gesamt += anteil;
		}

		pSatz = (CEigentuemer*)m_parrEigent -> GetAt( i + m_iOffset );
		pSatz -> m_NFP4_ENA = m_strName[i];
		pSatz -> m_NFP4_EAN = m_strStr[i];
		pSatz -> m_NFP4_EPL = m_strPLZ[i];
		pSatz -> m_NFP4_EOR = m_strOrt[i];
		pSatz -> m_NFP4_PN  = m_lNenn[i];
		pSatz -> m_NFP4_PZ  = m_lZaehl[i];
		if ( m_bHer[i])	pSatz -> m_NFP4_HER = "Y";
		else			pSatz -> m_NFP4_HER = "N";
		pSatz -> m_NFP4_NR  = i + m_iOffset;
	}
	if (( gesamt < 0.9999 ) || ( gesamt > 1.0001 ))	m_bSummError = TRUE;

	CWnd	*pWnd = GetDlgItem( IDC_RADIO1 );
	ASSERT( pWnd );
	int	res = ((CButton*)pWnd) -> GetCheck();
	if ( m_iEigZahl > 1 )
		m_bMiteigentum = (((CButton*)pWnd) -> GetCheck() == 1 );

}

void CEditPage7::OnNeu() 
{
	CEigentuemer	*pSatz;

	UpdateData();

	pSatz = new CEigentuemer;
	ASSERT( pSatz );

	m_parrEigent -> Add( pSatz );
	m_iEigZahl = m_parrEigent -> GetSize();

	SetGeaendert();

	InitData();
	UpdateData( FALSE );
}

void CEditPage7::OnDelete() 
{
	CDeleteDialog	dlg;
	CxString		text, item;
	char			*txt, *pt;
	short			i;

	UpdateData();

	text.Empty();
	text = "Eigentümer 1";
	for ( i = 1; i < m_parrEigent -> GetSize(); i++ )
	{
		text += '|';
		item.Empty();
		item.printf( "Eigentümer %d", i+1 );
		text += item;
	}
	dlg.m_strListe = text;
	dlg.m_strTitel.LoadString( IDS_DELE_EIG );
	if ( dlg.m_strTitel.IsEmpty())
		dlg.m_strTitel = "Eigentümer löschen";

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
					m_parrEigent -> Remove( txt );
					*pt = '|';
					pt++;
					txt = pt;
				}
				else
				{
					m_parrEigent -> Remove( txt );
			}	}


			SetGeaendert();
			InitData();
			UpdateData( FALSE );
	}	}
}

void CEditPage7::OnWeiter() 
{
	UpdateData();
	m_iOffset++;
	if ( m_iOffset > ( m_iEigZahl - 2 )) m_iOffset = m_iEigZahl - 2;
	InitData();
	UpdateData( FALSE );
}

void CEditPage7::OnZurueck() 
{
	UpdateData();
	m_iOffset--;
	if ( m_iOffset < 0 ) m_iOffset = 0;
	InitData();
	UpdateData( FALSE );
}

void CEditPage7::SetGeaendert( BOOL f)
{
	((CErfassPrivDlg*)GetParent()) -> SetEGeaendert( f );
}	// SetGeaendert

void CEditPage7::OnModify() 
{
	SetGeaendert();
}
