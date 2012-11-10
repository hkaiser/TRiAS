// editmerk.cpp : implementation file
//

#include "stdafx.h"
//#include "edbs.h"
#include "editmerk.h"
#include "cxstring.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditMerkmal dialog


CEditMerkmal::CEditMerkmal(CWnd* pParent /*=NULL*/)
	: CDialog(CEditMerkmal::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEditMerkmal)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CEditMerkmal::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditMerkmal)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEditMerkmal, CDialog)
	//{{AFX_MSG_MAP(CEditMerkmal)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CEditMerkmal :: OnInitDialog()
{
	CComboBox *pBox1, *pBox2;
	CxString eintrag, key, wert, temp;
	POSITION pos;
	char a, b, c;
	BOOL result = CDialog::OnInitDialog();

	pBox1 = (CComboBox*)GetDlgItem( IDC_COMBO1 );
	pBox2 = (CComboBox*)GetDlgItem( IDC_COMBO2 );
	ASSERT( pBox1 );
	ASSERT( pBox2 );

	if ( result )
	{	CopyMap( &TriasIdentMap, m_pTriasIdentMap );
		CopyMap( &TriasXIdentMap, m_pTriasXIdentMap );
		CopyMap( &AttribTexteMap, m_pAttribTexteMap );
		CopyMap( &WertTexteMap, m_pWertTexteMap );

		for ( pos = m_pAttribTexteMap -> GetStartPosition(); pos != NULL; )
		{	m_pAttribTexteMap -> GetNextAssoc( pos, key, wert );
			eintrag = key;
			eintrag += ": ";
			eintrag += wert;
			pBox1 -> AddString( eintrag );
		}

		for ( pos = m_pWertTexteMap -> GetStartPosition(); pos != NULL; )
		{	m_pWertTexteMap -> GetNextAssoc( pos, eintrag, wert );
			eintrag.Teilen( key, eintrag, '=' );
			key.TrimAll();
			eintrag.TrimAll();
			a = b = c = '0';
			wert = key;
			wert += a;
			wert += b;
			wert += c;
			while ( m_pWertTexteMap -> Lookup( wert, temp ))
			{	c++;
				if ( c > '9' ) { c = '0'; b++; }
				if ( b > '9' ) { b = '0'; a++; }
				wert = key;
				wert += a;
				wert += b;
				wert += c;
			}
//			m_pWertMap.SetAt( wert, eintrag );
		}
	}

	return result;
}	// OnInitDialog


void CEditMerkmal :: CopyMap( CMapStringToString *z, CMapStringToString *q )
{	POSITION	pos;
	CString		key, wert;

	z -> RemoveAll();
	for ( pos = q -> GetStartPosition(); pos != NULL; )
	{	q -> GetNextAssoc( pos, key, wert );
		z -> SetAt( key, wert );
	}
}	// CopyMap


/////////////////////////////////////////////////////////////////////////////
// CEditMerkmal message handlers
