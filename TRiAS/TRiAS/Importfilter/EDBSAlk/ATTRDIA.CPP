///////////////////////////////////////////////////////////////////////
//	TRiAS - Erweiterung: EDBS - Import
///////////////////////////////////////////////////////////////////////
//	Datei:			attrdia.cpp
//
//	Stand:			10.04.1995
//	Beschreibung:	Dialog zu Definition von EDBS-Attributen
//	Entwicklung:	10.04.95	Beginn der Kodierung
//					19.05.95	Umstellung auf CDefMMList
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#if defined(_USE_CONFIG_DIALOGS)

#include "resource.h"
#include "attrdia.hpp"
#include "cxstring.h"
#include <ctype.h>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

CAttributeDialog :: CAttributeDialog( CWnd* pParent )
	: CDialog( CAttributeDialog::IDD, pParent )
{	//{{AFX_DATA_INIT(CAttributeDialog)
	//}}AFX_DATA_INIT
	pOrigAttrMap = NULL;
	pOrigWertMap = NULL;
	m_modified = FALSE;
}


BEGIN_MESSAGE_MAP( CAttributeDialog, CDialog )
	ON_BN_CLICKED( IDOK, OnOK )
	ON_BN_CLICKED( IDCANCEL, OnCancel )
	ON_BN_CLICKED( IDC_BUTTON1, OnClickedDelAttribut )
	ON_BN_CLICKED( IDC_BUTTON2, OnClickedModAttribut )
	ON_BN_CLICKED( IDC_BUTTON3, OnClickedDelWert )
	ON_BN_CLICKED( IDC_BUTTON4, OnClickedModWert )
	ON_CBN_EDITUPDATE( IDC_COMBO1, OnEditAttrKode )
	ON_CBN_SELCHANGE( IDC_COMBO1, OnAuswahlAttrKode )
	ON_EN_CHANGE( IDC_EDIT1, OnEditAttrBez )
	ON_CBN_EDITUPDATE( IDC_COMBO2, OnEditWertKode )
	ON_CBN_SELCHANGE( IDC_COMBO2, OnAuswahlWertKode )
	ON_EN_CHANGE( IDC_EDIT2, OnEditWertBez )
END_MESSAGE_MAP()


BOOL CAttributeDialog :: OnInitDialog()
{	POSITION	pos;
	CxString	key, wert, eintrag, temp;
	CComboBox	*pBox1, *pBox2;
	CEdit		*pED1, *pED2;
	CButton		*pBtn1, *pBtn2, *pBtn3, *pBtn4;
	char		a, b, c;

	pBtn1 = (CButton*)GetDlgItem( IDC_BUTTON1 );
	pBtn2 = (CButton*)GetDlgItem( IDC_BUTTON2 );
	pBtn3 = (CButton*)GetDlgItem( IDC_BUTTON3 );
	pBtn4 = (CButton*)GetDlgItem( IDC_BUTTON4 );
	ASSERT( pBtn1 );
	ASSERT( pBtn2 );
	ASSERT( pBtn3 );
	ASSERT( pBtn4 );

	pBtn1 -> EnableWindow( FALSE );
	pBtn2 -> EnableWindow( FALSE );
	pBtn3 -> EnableWindow( FALSE );
	pBtn4 -> EnableWindow( FALSE );

	pBox1 = (CComboBox*)GetDlgItem( IDC_COMBO1 );
	pBox2 = (CComboBox*)GetDlgItem( IDC_COMBO2 );
	pED1  = (CEdit*)GetDlgItem( IDC_EDIT1 );
	pED2  = (CEdit*)GetDlgItem( IDC_EDIT2 );
	ASSERT( pBox1 );
	ASSERT( pBox2 );
	ASSERT( pED1 );
	ASSERT( pED2 );

	if ( CDialog::OnInitDialog())
	{	AttrMap.RemoveAll();
		WertMap.RemoveAll();
		BezMap.RemoveAll();
		for ( pos = pOrigAttrMap -> GetStartPosition(); pos != NULL; )
		{	pOrigAttrMap -> GetNextAssoc( pos, key, wert );
			AttrMap.SetAt( key, wert );
			eintrag = key;
			eintrag += ": ";
			eintrag += wert;
			pBox1 -> AddString( eintrag );
		}
		for ( pos = pOrigWertMap -> GetStartPosition(); pos != NULL; )
		{	pOrigWertMap -> GetNextAssoc( pos, eintrag, wert );
			BezMap.SetAt( eintrag, wert );
			eintrag.Teilen( key, eintrag, '=' );
			key.TrimAll();
			eintrag.TrimAll();
			a = b = c = '0';
			wert = key;
			wert += a;
			wert += b;
			wert += c;
			while ( WertMap.Lookup( wert, temp ))
			{	c++;
				if ( c > '9' ) { c = '0'; b++; }
				if ( b > '9' ) { b = '0'; a++; }
				wert = key;
				wert += a;
				wert += b;
				wert += c;
			}
			WertMap.SetAt( wert, eintrag );
	}	}
	else
		return FALSE;

	m_AL.SetElements( pBox1, pED1, pBtn1, pBtn2,
			&AttrMap, CDefMMList::TestModeA3 );
	m_WL.SetElements( pBox2, pED2, pBtn3, pBtn4,
			&AttrWerteMap, CDefMMList::TestMode4 );

	key = m_strStartIdent;
	if ( !key.IsEmpty())
	{	if (( pBox1 -> SelectString( -1, key )) == CB_ERR )
			pBox1 -> SetWindowText( key );
		else
			OnAuswahlAttrKode();
	}

	return TRUE;
}	// OnInitDialog

void CAttributeDialog :: InitWL()
{	CComboBox	*pCB;
	CEdit		*pED;
	CxString	strText, strTemp;
	CxString	strKey, strEntr;
	char		a, b, c;
	int			i;

	pCB = (CComboBox*)GetDlgItem( IDC_COMBO2 );
	pED = (CEdit*)GetDlgItem( IDC_EDIT2 );
	ASSERT( pCB );
	ASSERT( pED );
	pCB -> ResetContent();
	pED -> SetWindowText( "" );

	pCB = (CComboBox*)GetDlgItem( IDC_COMBO1 );
	ASSERT( pCB );

	i = pCB -> GetCurSel();
	if ( i == CB_ERR ) return;

	pCB -> GetLBText( i, strText );
	strText.Teilen( strText, strTemp, ':' );
	m_strCurrAttr = strText;

	AttrWerteMap.RemoveAll();
	m_WL.Reset();

	pCB = (CComboBox*)GetDlgItem( IDC_COMBO2 );
	ASSERT( pCB );

	strText.TrimAll();
	strKey = strText;
	a = b = c = '0';
	strKey += a;
	strKey += b;
	strKey += c;
	strTemp.Empty();
	WertMap.Lookup( strKey, strTemp );
	i = 0;
	while ( !strTemp.IsEmpty())
	{	strKey = strText;
		strKey += " = ";
		strKey += strTemp;
		strEntr.Empty();
		BezMap.Lookup( strKey, strEntr );
		AttrWerteMap.SetAt( strTemp, strEntr );
		strTemp += ": ";
		strTemp += strEntr;
		pCB -> AddString( strTemp );
		c++;
		if ( c > '9' ) { c = '0'; b++; }
		if ( b > '9' ) { b = '0'; a++; }
		strKey = strText;
		strKey += a;
		strKey += b;
		strKey += c;
		strTemp.Empty();
		WertMap.Lookup( strKey, strTemp );
		i++;
	}

	if ( i )
	{	pCB -> SetCurSel( 0 );
		OnAuswahlWertKode();
	}
}	// InitWL

void CAttributeDialog :: SaveWL()
{	CxString	strText, strTemp;
	CxString	strKey, strEntr;
	char		a, b, c;
	int			i;
	POSITION	pos;

	if ( m_strCurrAttr.IsEmpty()) return;

	strText = m_strCurrAttr;
	strText.TrimAll();
	strKey = strText;
	a = b = c = '0';
	strKey += a;
	strKey += b;
	strKey += c;
	strTemp.Empty();
	WertMap.Lookup( strKey, strTemp );
	i = 0;
	while ( !strTemp.IsEmpty())
	{	WertMap.RemoveKey( strKey );
		strKey = strText;
		strKey += " = ";
		strKey += strTemp;
		strEntr.Empty();
		BezMap.RemoveKey( strKey );
		c++;
		if ( c > '9' ) { c = '0'; b++; }
		if ( b > '9' ) { b = '0'; a++; }
		strKey = strText;
		strKey += a;
		strKey += b;
		strKey += c;
		strTemp.Empty();
		WertMap.Lookup( strKey, strTemp );
		i++;
	}

	strKey = strText;
	a = b = c = '0';
	strKey += a;
	strKey += b;
	strKey += c;
	strTemp.Empty();
	pos = AttrWerteMap.GetStartPosition();
	while ( pos )
	{	AttrWerteMap.GetNextAssoc( pos, strTemp, strEntr );
		WertMap.SetAt( strKey, strTemp );
		strKey = strText;
		strKey += " = ";
		strKey += strTemp;
		BezMap.SetAt( strKey, strEntr );
		c++;
		if ( c > '9' ) { c = '0'; b++; }
		if ( b > '9' ) { b = '0'; a++; }
		strKey = strText;
		strKey += a;
		strKey += b;
		strKey += c;
		strTemp.Empty();
	}
}	// SaveWL

void CAttributeDialog :: OnCancel()
{	CxString	text;

	if ( m_AL.Modified() || m_WL.Modified())
	{	text = "Änderungen verwerfen?";
		if ( text.MessageBox( this, "Abbrechen", MB_YESNO | MB_ICONQUESTION ) == IDYES )
			EndDialog( IDCANCEL );
	}
	else
		EndDialog( IDCANCEL );
}	// OnCancel

void CAttributeDialog :: DoDataExchange( CDataExchange* pDX )
{	CDialog :: DoDataExchange( pDX );
	//{{AFX_DATA_MAP(CAttributeDialog)
	//}}AFX_DATA_MAP
}

void CAttributeDialog :: SetStartIdent( const char *txt )
{	if ( txt )	m_strStartIdent = txt;
	else		m_strStartIdent = "";
}	// SetStartIdent


void CAttributeDialog :: OnEditAttrKode()
{	m_AL.OnEditKode();
	CComboBox	*pCB = (CComboBox*)GetDlgItem( IDC_COMBO2 );
	CEdit		*pED = (CEdit*)GetDlgItem( IDC_EDIT2 );
	ASSERT( pCB );
	ASSERT( pED );

	pCB -> ResetContent();
	pED -> SetWindowText( "" );
}	// OnEditAttrKode

void CAttributeDialog :: OnAuswahlAttrKode()
{	if ( m_WL.Modified()) SaveWL();
	InitWL();

	m_AL.OnAuswahlKode();
}	// OnAuswahlAttrKode

void CAttributeDialog :: OnEditAttrBez()
{	m_AL.OnEditBez();
}	// OnEditAttrBez

void CAttributeDialog :: OnAuswahlWertKode()
{	m_WL.OnAuswahlKode();
}	// OnAuswahlWertKode

void CAttributeDialog :: OnClickedDelAttribut()
{	CComboBox	*pCB;
	CEdit		*pED;
	CxString	strText, strTemp;
	CxString	strKey, strEntr;
	char		a, b, c;
	int			i;

	pCB = (CComboBox*)GetDlgItem( IDC_COMBO1 );
	ASSERT( pCB );

	i = pCB -> GetCurSel();
	if ( i == CB_ERR ) return;

	pCB -> GetLBText( i, strText );
	strText.Teilen( strText, strTemp, ':' );

	strText.TrimAll();
	strKey = strText;
	a = b = c = '0';
	strKey += a;
	strKey += b;
	strKey += c;
	strTemp.Empty();
	WertMap.Lookup( strKey, strTemp );
	i = 0;
	while ( !strTemp.IsEmpty())
	{	WertMap.RemoveKey( strKey );
		strKey = strText;
		strKey += " = ";
		strKey += strTemp;
		strEntr.Empty();
		BezMap.RemoveKey( strKey );
		c++;
		if ( c > '9' ) { c = '0'; b++; }
		if ( b > '9' ) { b = '0'; a++; }
		strKey = strText;
		strKey += a;
		strKey += b;
		strKey += c;
		strTemp.Empty();
		WertMap.Lookup( strKey, strTemp );
		i++;
	}
	
	pCB = (CComboBox*)GetDlgItem( IDC_COMBO2 );
	pED = (CEdit*)GetDlgItem( IDC_EDIT2 );
	ASSERT( pCB );
	ASSERT( pED );

	pCB -> Clear();
	pED -> SetWindowText( "" );
	AttrWerteMap.RemoveAll();
	m_WL.Reset();

	m_AL.OnClickedDel();
}	// OnClickedDelAttribut()

void CAttributeDialog :: OnClickedModAttribut()
{	int			i, j;
	CComboBox	*pCB;
	CEdit		*pED;

	pCB = (CComboBox*)GetDlgItem( IDC_COMBO1 );
	ASSERT( pCB );
	i = pCB -> GetCurSel();
	m_AL.OnClickedMod();
	j = pCB -> GetCurSel();
	if (( i != CB_ERR ) || ( i != j ))	// ==> neues Attribut
	{	if ( m_WL.Modified()) SaveWL();

		pCB = (CComboBox*)GetDlgItem( IDC_COMBO2 );
		pED = (CEdit*)GetDlgItem( IDC_EDIT2 );
		ASSERT( pCB );
		ASSERT( pED );

		pCB -> Clear();
		pED -> SetWindowText( "" );
		AttrWerteMap.RemoveAll();
		m_WL.Reset();
	}

	if ( j != CB_ERR ) InitWL();
}	// OnClickedModAttribut()

void CAttributeDialog :: OnEditWertKode()
{	m_WL.OnEditKode();
}	// OnEditWertKode

void CAttributeDialog :: OnEditWertBez()
{	m_WL.OnEditBez();
}	// OnEditWertBez

void CAttributeDialog :: OnClickedDelWert()
{	m_WL.OnClickedDel();
	m_modified = TRUE;
}	// OnClickedDelWert()

void CAttributeDialog :: OnClickedModWert()
{	m_WL.OnClickedMod();
	m_modified = TRUE;
}	// OnClickedModWert()

void CAttributeDialog :: OnOK()
{	POSITION	pos;
	CxString	key, wert;

	if ( m_AL.NotSavedEdit() || m_WL.NotSavedEdit())
	{	wert = "Nicht gespeicherte Änderungen verwerfen?";
		if ( wert.MessageBox( this, "Beenden", MB_YESNO | MB_ICONQUESTION ) == IDNO )
			return;
	}

	if ( m_AL.Modified() || m_modified )
	{	if ( m_WL.Modified())
			SaveWL();

		pOrigAttrMap -> RemoveAll();
		for ( pos = AttrMap.GetStartPosition(); pos != NULL; )
		{	AttrMap.GetNextAssoc( pos, key, wert );
			pOrigAttrMap -> SetAt( key, wert );
		}

		pOrigWertMap -> RemoveAll();
		for ( pos = BezMap.GetStartPosition(); pos != NULL; )
		{	BezMap.GetNextAssoc( pos, key, wert );
			pOrigWertMap -> SetAt( key, wert );
	}	}

	EndDialog( IDOK );
}

#endif // defined(_USE_CONFIG_DIALOGS)

