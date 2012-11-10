///////////////////////////////////////////////////////////////////////
//	TRiAS - Erweiterung: EDBS - Import
///////////////////////////////////////////////////////////////////////
//	Datei:			triddia.cpp
//
//	Stand:			07.04.1995
//	Beschreibung:	Dialog zu Definition von TRiAS-Identfikatoren
//	Entwicklung:	07.04.95	Beginn der Kodierung
//					19.05.95	Umstellung auf CDefMMList
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#if defined(_USE_CONFIG_DIALOGS)

#include "resource.h"
#include "triddia.hpp"
#include "cxstring.h"
#include <ctype.h>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

CTriasIdentDialog :: CTriasIdentDialog( CWnd* pParent )
	: CDialog( CTriasIdentDialog::IDD, pParent )
{	//{{AFX_DATA_INIT(CTriasIdentDialog)
	//}}AFX_DATA_INIT
}

void CTriasIdentDialog :: OnOK()
{	POSITION	pos;
	CxString	key, wert;

	if ( m_DL.NotSavedEdit())
	{	wert = "Nicht gespeicherte Änderungen verwerfen?";
		if ( wert.MessageBox( this, "Beenden", MB_YESNO | MB_ICONQUESTION ) == IDNO )
			return;
	}

	if ( m_DL.Modified())
	{	pOriginalMap -> RemoveAll();
		for ( pos = MerkmalMap.GetStartPosition(); pos != NULL; )
		{	MerkmalMap.GetNextAssoc( pos, key, wert );
			pOriginalMap -> SetAt( key, wert );
	}	}

	EndDialog( IDOK );
}

void CTriasIdentDialog :: OnCancel()
{	CxString	text;

	if ( m_DL.Modified())
	{	text = "Änderungen verwerfen?";
		if ( text.MessageBox( this, "Abbrechen", MB_YESNO | MB_ICONQUESTION ) == IDYES )
			EndDialog( IDCANCEL );
	}
	else
		EndDialog( IDCANCEL );
}	// OnCancel

void CTriasIdentDialog :: DoDataExchange( CDataExchange* pDX )
{	CDialog :: DoDataExchange( pDX );
	//{{AFX_DATA_MAP(CTriasIdentDialog)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP( CTriasIdentDialog, CDialog )
	ON_BN_CLICKED( IDC_BUTTON1, OnClickedDelMerkmal )
	ON_BN_CLICKED( IDC_BUTTON2, OnClickedModMerkmal )
	ON_BN_CLICKED( IDOK, OnOK )
	ON_BN_CLICKED( IDCANCEL, OnCancel )
	ON_CBN_EDITUPDATE( IDC_COMBO1, OnEditIdentKode )
	ON_CBN_SELCHANGE( IDC_COMBO1, OnAuswahlIdentKode )
	ON_EN_CHANGE( IDC_EDIT1, OnEditIdentBez )
END_MESSAGE_MAP()

void CTriasIdentDialog :: OnClickedDelMerkmal()
{	m_DL.OnClickedDel();
}	// OnClickedDelMerkmal()

void CTriasIdentDialog :: OnClickedModMerkmal()
{	m_DL.OnClickedMod();
}	// OnClickedModMerkmal()

BOOL CTriasIdentDialog :: OnInitDialog()
{	POSITION	pos;
	CxString	key, wert, eintrag;
	CComboBox	*pBox;
	CButton		*pBtn1, *pBtn2;
	CEdit		*pED;
	CStatic		*pS;

	pBtn1 = (CButton*)GetDlgItem( IDC_BUTTON1 );
	if ( pBtn1 ) pBtn1 -> EnableWindow( FALSE );

	pBtn2 = (CButton*)GetDlgItem( IDC_BUTTON2 );
	if ( pBtn2 ) pBtn2 -> EnableWindow( FALSE );

	SetWindowText( m_strCaption );

	pS = (CStatic*)GetDlgItem( IDC_TEXT1 );
	if ( pS ) pS -> SetWindowText( m_strText1 );

	pS = (CStatic*)GetDlgItem( IDC_TEXT2 );
	if ( pS ) pS -> SetWindowText( m_strText2 );

	pBox = (CComboBox*)GetDlgItem( IDC_COMBO1 );
	if ( CDialog::OnInitDialog())
	{	MerkmalMap.RemoveAll();
		for ( pos = pOriginalMap -> GetStartPosition();
				pos != NULL; )
		{	pOriginalMap -> GetNextAssoc( pos, key, wert );
			MerkmalMap.SetAt( key, wert );
			eintrag = key;
			eintrag += ": ";
			eintrag += wert;
			pBox -> AddString( eintrag );
	}	}
	else
		return FALSE;

	pED = (CEdit*)GetDlgItem( IDC_EDIT1 );
	switch ( m_iTestProc )
	{	case 1:		// 
			m_DL.SetElements( pBox, pED, pBtn1, pBtn2,
					&MerkmalMap, CDefMMList::TestMode8 );
			break;
		case 2:
			m_DL.SetElements( pBox, pED, pBtn1, pBtn2,
					&MerkmalMap, CDefMMList::TestMode8x );
			break;
	}

	key = m_strStartIdent;
	if ( !key.IsEmpty())
	{	if (( pBox -> SelectString( -1, key )) == CB_ERR )
		{	switch ( m_iTestProc )
			{	case 1:		// 
					if ( key.AnzahlHexZiffern() == 8 )
					{	pBox -> SetWindowText( key );
						m_DL.KodeGeaendert();
					}
					break;
				case 2:
					if ( key.AnzahlHexZiffern() < 8 )
					{	pBox -> SetWindowText( key );
						m_DL.KodeGeaendert();
					}
					break;
		}	}
		else
			OnAuswahlIdentKode();
	}

	return TRUE;
}	// OnInitDialog

void CTriasIdentDialog :: OnEditIdentKode()
{	m_DL.OnEditKode();
}	// OnEditIdentKode

void CTriasIdentDialog :: OnAuswahlIdentKode()
{	m_DL.OnAuswahlKode();
}	// OnAuswahlIdentKode

void CTriasIdentDialog :: OnEditIdentBez()
{	m_DL.OnEditBez();
}	// OnEditIdentBez

void CTriasIdentDialog :: SetCaptText( const char *txt )
{	if ( txt )	m_strCaption = txt;
	else		m_strCaption = "Merkmal - Dialog";
}	// SetCaptText

void CTriasIdentDialog :: SetText1( const char *txt )
{	if ( txt )	m_strText1 = txt;
	else		m_strText1 = "Text 1";
}	// SetText1

void CTriasIdentDialog :: SetText2( const char *txt )
{	if ( txt )	m_strText2 = txt;
	else		m_strText2 = "Text 2";
}	// SetText2

void CTriasIdentDialog :: SetStartIdent( const char *txt )
{	if ( txt )	m_strStartIdent = txt;
	else		m_strStartIdent = "";
}	// SetStartIdent

#endif // defined(_USE_CONFIG_DIALOGS)

