// DlgZFkt.cpp : implementation file
//

#include "stdafx.h"
#include "GbmTRiAS.h"
#include "DlgZFkt.h"

#include "Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgZusatzFkt dialog


CDlgZusatzFkt::CDlgZusatzFkt(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgZusatzFkt::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgZusatzFkt)
	m_strEintrag = _T("");
	//}}AFX_DATA_INIT
	m_arrZF = NULL;
}


void CDlgZusatzFkt::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgZusatzFkt)
	DDX_Control(pDX, IDC_LIST1, m_lbListe);
	DDX_LBString(pDX, IDC_LIST1, m_strEintrag);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgZusatzFkt, CDialog)
	//{{AFX_MSG_MAP(CDlgZusatzFkt)
	ON_LBN_DBLCLK(IDC_LIST1, OnOK)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgZusatzFkt message handlers

void CDlgZusatzFkt::OnOK() 
{
	UpdateData( TRUE );

	m_strScriptFileName.Empty();
	m_strScriptResName.Empty();
	m_uiResID = 0;

	if ( !m_strEintrag.IsEmpty())
	{
		m_mapParam.Lookup( m_strEintrag, m_strParameter );

		m_mapFkt.Lookup( m_strEintrag, m_strScriptFileName );

		if ( m_strScriptFileName.IsEmpty())
		{
			m_mapMac.Lookup( m_strEintrag, m_strScriptResName );
			m_uiResID = GetMacroResID( m_strScriptResName );
			if ( m_uiResID != 0 )
				m_strScriptResName.Empty();
		}
	}

	CDialog::OnOK();
}

BOOL CDlgZusatzFkt::OnInitDialog() 
{
	CxString	strEintrag;
	CxString	strBez, strFile;
	CxString	strParam;

	CDialog::OnInitDialog();

	if ( m_arrZF != NULL )
	{
		for ( short i = 0; i < m_arrZF -> GetSize(); i++ )
		{
			strEintrag = m_arrZF -> GetAt( i );
			strEintrag.Teilen( strFile, strBez, ';' );
			strBez.Teilen( strParam, strBez, ';' );
			if ( strBez.IsEmpty())
			{
				strBez = strParam;
				strParam = "S0 Main";
			}

			if ( !strFile.IsEmpty() && !strBez.IsEmpty())
			{
				if ( strFile[0] == '[' )
				{
					strFile = strFile.Mid( 1 );
					strFile = strFile.Left( strFile.GetLength() - 1 );
//					strFile.MakeUpper();
					if ( GetMacroResID( strFile ) != NULL )
					{
						m_lbListe.AddString( strBez );
						m_mapMac.SetAt( strBez, strFile );
						m_mapParam.SetAt( strBez, strParam );
					}
				}
				else if ( strFile[0] == '<' )
				{
					strFile = strFile.Mid( 1 );
					strFile = strFile.Left( strFile.GetLength() - 1 );
//					strFile.MakeUpper();

					m_lbListe.AddString( strBez );
					m_mapMac.SetAt( strBez, strFile );
					m_mapParam.SetAt( strBez, strParam );
				}
				else
				{
					if ( strFile.FileExist())
					{
						m_lbListe.AddString( strBez );
						m_mapFkt.SetAt( strBez, strFile );
						m_mapParam.SetAt( strBez, strParam );
					}
				}
			}
		}
	}

	if ( m_lbListe.GetCount() == 0 )
		m_lbListe.AddString( "Keine Funktion installiert!" );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

UINT CDlgZusatzFkt::GetMacroResID( const char* name )
{
	ASSERT( AfxIsValidString( name ));
	if ( !AfxIsValidString( name ))		return 0;

	UINT		result = 0;
	CString		strName( name );

	if ( strName == "ZF_MAKRO01" )
		result = IDR_ZF_MAKRO01;
	else if ( strName == "K2000" )
		result = IDR_K2000;
	else if ( strName == "TOPOANA" )
		result = IDR_TOPOANA;
	else if ( strName == "GS_ANA" )
		result = IDR_GS_ANA;

	return result;
}
