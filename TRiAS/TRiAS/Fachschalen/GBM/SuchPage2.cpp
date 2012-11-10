// SuchPage2.cpp : implementation file
//

#include "stdafx.h"
#include "GbmTRiAS.h"
#include "SuchPage2.h"
#include "MyPropS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSuchPage2 property page

IMPLEMENT_DYNCREATE(CSuchPage2, CPropertyPage)

CSuchPage2::CSuchPage2() : CPropertyPage(CSuchPage2::IDD)
{
	//{{AFX_DATA_INIT(CSuchPage2)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pSetStrasse = NULL;
	m_bInit = FALSE;
}

CSuchPage2::~CSuchPage2()
{
}

void CSuchPage2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSuchPage2)
	DDX_Control(pDX, IDC_COMBO1, m_cbStrasse);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSuchPage2, CPropertyPage)
	//{{AFX_MSG_MAP(CSuchPage2)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeStrasse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSuchPage2 message handlers

BOOL CSuchPage2::OnSetActive() 
{
	BOOL		result;
	short		n;
	CString		pfad, key, text;
	POSITION	pos;

	CMySuchSheet	*parent = (CMySuchSheet*)GetParent();


	if ( parent -> m_iNextPage != 2 )
	{
		parent -> SetActivePage( parent -> m_iNextPage );
		result = FALSE;
	}
	else
	{
		if ( m_strIdent.GetLength() > 2 )
			parent -> SetWizardButtons( PSWIZB_FINISH|PSWIZB_BACK );
		else
			parent -> SetWizardButtons( PSWIZB_DISABLEDFINISH|PSWIZB_BACK );

		result = CPropertyPage::OnSetActive();
	}

	if ( m_bInit )	return result;
	m_bInit = TRUE;

	BeginWaitCursor();
	m_pSetStrasse -> InitListen();
	n = m_pSetStrasse -> GetZahlStrassen( m_iOISY );
	if ( n > 0 )
		m_pmapStrassen = m_pSetStrasse -> GetStrassen( m_iOISY );
	else
		m_pmapStrassen = NULL;

	m_cbStrasse.ResetContent();

	if ( m_pmapStrassen != NULL )
	{
		for( pos = m_pmapStrassen -> GetStartPosition(); pos != NULL; )
		{
			m_pmapStrassen -> GetNextAssoc( pos, key, text );
			if ( !text.IsEmpty())
				m_cbStrasse.AddString( text );
		}
	}

	if ( m_strIDE.GetLength() > 2 )
		m_strIDE = m_strIDE.Left( 2 );

	UpdateData( FALSE );
	EndWaitCursor();

	return result;
}

BOOL CSuchPage2::OnWizardFinish() 
{
	UpdateData( TRUE );
	return CPropertyPage::OnWizardFinish();
}

void CSuchPage2::OnSelchangeStrasse() 
{
	POSITION	pos;
	CString		item, key, text;

	CMySuchSheet	*parent = (CMySuchSheet*)GetParent();

	BeginWaitCursor();

	m_strIdent.Empty();
	if ( m_cbStrasse.GetCurSel() != CB_ERR )
	{
		m_cbStrasse.GetLBText( m_cbStrasse.GetCurSel(), item );
		for ( pos = m_pmapStrassen -> GetStartPosition(); pos != NULL; )
		{
			m_pmapStrassen -> GetNextAssoc( pos, key, text );
			if ( text == item )
			{
				m_strIdent = m_strIDE;
				m_strIdent += key;
				break;
			}
		}
	}

	if ( m_strIdent.GetLength() > 2 )
		parent -> SetWizardButtons( PSWIZB_FINISH|PSWIZB_BACK );
	else
		parent -> SetWizardButtons( PSWIZB_DISABLEDFINISH|PSWIZB_BACK );

	UpdateData( FALSE );
	EndWaitCursor();
}
