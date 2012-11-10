// DeleteDialog.cpp : implementation file
//

#include "stdafx.h"
#include "GbmTRiAS.h"
#include "DeleteDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDeleteDialog dialog


CDeleteDialog::CDeleteDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CDeleteDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDeleteDialog)
	m_strTitel = _T("");
	//}}AFX_DATA_INIT
}


void CDeleteDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDeleteDialog)
	DDX_Control(pDX, IDC_LIST1, m_lbListe);
	DDX_Text(pDX, IDC_TEXT0, m_strTitel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDeleteDialog, CDialog)
	//{{AFX_MSG_MAP(CDeleteDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDeleteDialog message handlers

BOOL CDeleteDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	char	*txt, *pt;

	if ( !m_strListe.IsEmpty())
	{
		txt = m_strListe.GetBuffer( 0 );
		pt = txt;
		while ( *pt )
		{
			while ( *pt && ( *pt != '|' )) pt++;
			if ( *pt )
			{
				*pt = '\0';
				m_lbListe.AddString( txt );
				*pt = '|';
				pt++;
				txt = pt;
			}
			else
			{
				m_lbListe.AddString( txt );
		}	}
		m_strListe.ReleaseBuffer();
	}

	m_strListe.Empty();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDeleteDialog::OnOK() 
{
	CString		text, item;
	short		i;

	if ( m_lbListe.GetSelCount() == 0 )
		CDialog::OnCancel();
	else
	{
		if ( MessageBox( "Tatsächlich löschen!", NULL, MB_OKCANCEL|MB_ICONQUESTION )
				== IDOK )
		{
			text.Empty();
			for ( i = 0; i < m_lbListe.GetCount(); i++ )
			{
				if ( m_lbListe.GetSel( i ))
				{
					m_lbListe.GetText( i, item );
					text += item;
					text += '|';
				}
			}
			m_strListe = text;
			CDialog::OnOK();
	}	}
}
