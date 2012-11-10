// TRiASGCSPpg.cpp : Implementation of CTRiASGCSPpg
#include "stdafx.h"
#include "TRiASCSImpl.h"
#include "TRiASGCSPpg.h"
#include "EpsgMgr.h"


/////////////////////////////////////////////////////////////////////////////
// CTRiASGCSPpg

HRESULT	CTRiASGCSPpg::FinalConstruct() {
	return S_OK;
}

void CTRiASGCSPpg::FinalRelease() {}

LRESULT CTRiASGCSPpg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
	TRIASCSGEODETICDATUM	gd;
	TRIASCSELLIPSOID		el;
	WTRiASCS				pCS;
	WTRiASCSGCS				pGCS;
	WTRiASCSTransformInfo	pTI;
	HRESULT	hr;
	CODENAME	*pCode;
	if( S_OK == m_ppUnk[0]->QueryInterface(IID_ITRiASCS, pCS.ppv()) ) {
		if( S_OK == pCS->get_GeographicCS( pGCS.ppi() ) ) {
			try {
				pTI = pGCS;
			} catch(...) {
			}
			/////////////////////////////////////////////////////////////
			// Datum - Combobox füllen
			HWND	hcombo = GetDlgItem( IDC_GEODETIC_DATUM );
			int		nItem;
			for( pCode = _CT_TRIASCSGEODETICDATUM; -1 != pCode->code && NULL != pCode->name; pCode++ ) {
				if( pCode->code < 6120 )	// allgemeine Daten ausschließen
					continue;
				if( !!pTI && S_OK == pTI->CanTransform( pCode->code ) ) {
					nItem = ::SendMessage( hcombo, CB_ADDSTRING, 0, (LPARAM) pCode->name );
					::SendMessage( hcombo, CB_SETITEMDATA, nItem, (DWORD) pCode->code );
				}
			}
			/////////////////////////////////////////////////////////////
			// und Datum einstellen
			hr = pGCS->get_GeodeticDatum( &gd );
			if( tcsGD_Undefined == gd ) {
				gd = tcsGD_DeutscheHauptdreiecksnetz;
				pGCS->put_GeodeticDatum( gd );
			}
			LPCTSTR pName = _EM.Decode( tcsCType_GD, gd );
			_ASSERTE( pName );
			::SendMessage( hcombo, CB_SELECTSTRING, 0, (LPARAM) pName );
			/////////////////////////////////////////////////////////////
			// Ellipsoid - Combobox füllen
			hcombo = GetDlgItem( IDC_ELLIPSOID );
			for( pCode = _CT_TRIASCSELLIPSOID; -1 != pCode->code && NULL != pCode->name; pCode++ ) {
				nItem = ::SendMessage( hcombo, CB_ADDSTRING, 0, (LPARAM) pCode->name );
				::SendMessage( hcombo, CB_SETITEMDATA, nItem, (DWORD) pCode->code );
			}
			/////////////////////////////////////////////////////////////
			// und Ellipsoid einstellen
			hr = pGCS->get_Ellipsoid(&el);
			if( tcsEL_Undefined == el ) {
				el = tcsEL_Bessel1841;
				pGCS->put_Ellipsoid( el );
			}
			pName = _EM.Decode( tcsCType_Ellipsoid, el );
			_ASSERTE( pName );
			::SendMessage( hcombo, CB_SELECTSTRING, 0, (LPARAM) pName );
		}
	}
	::EnableWindow( GetDlgItem( IDC_EDIT_SEMI_MAJOR ), FALSE );
	::EnableWindow( GetDlgItem( IDC_EDIT_SEMI_MINOR ), FALSE );
	::EnableWindow( GetDlgItem( IDC_EDIT_EXCENTRICITY ), FALSE );
	::EnableWindow( GetDlgItem( IDC_EDIT_FLATTENING ), FALSE );
	::EnableWindow( GetDlgItem( IDC_EDIT_FLATTENINGINV ), FALSE );
	UpdateControls();
	return 0;
}

static struct PARMS {
	UINT	Ctrl;
	int		pIndex;
} PARAMS[] = {
	{ IDC_EDIT_SEMI_MAJOR, 0 }
	, { IDC_EDIT_SEMI_MINOR, 1 }
	, { IDC_EDIT_EXCENTRICITY, -1 }
	, { IDC_EDIT_FLATTENING, 2 }
	, { IDC_EDIT_FLATTENINGINV, -2 }
	, {0,0}
};

#include <stdio.h>
static TCHAR szUndef[] =_T("nicht definiert");
void CTRiASGCSPpg::RecalcEllipsoid( TRIASCSELLIPSOID el ) {
	double	elMaj = 0, elMin = 0, elExc = 0, elFlt = 0, elInv = 0;
	TCHAR	buf[256];
	if( tcsEL_UserDefined == el ) {
		::SendMessage( GetDlgItem( IDC_EDIT_SEMI_MAJOR ), WM_GETTEXT, 64, (LPARAM) buf ); elMaj = atof( buf );
		::SendMessage( GetDlgItem( IDC_EDIT_SEMI_MINOR ), WM_GETTEXT, 64, (LPARAM) buf ); elMin = atof( buf );
	} else {
		LPCPARAMETERSET pset = _EM.GetParameters( tcsCType_Ellipsoid, el );
		_ASSERTE( NULL != pset );
		if( NULL == pset )
			return;
		elMaj = pset->p[0];
		elMin = pset->p[1];
		sprintf( buf, _T("%.16lf"), elMaj ); ::SendMessage( GetDlgItem( IDC_EDIT_SEMI_MAJOR ), WM_SETTEXT, 0, (LPARAM) buf );
		sprintf( buf, _T("%.16lf"), elMin ); ::SendMessage( GetDlgItem( IDC_EDIT_SEMI_MINOR ), WM_SETTEXT, 0, (LPARAM) buf );
	}
	if( 0 == elMaj || 0 == elMin ) {
		::MessageBeep(MB_ICONEXCLAMATION);
		elExc = elFlt = elInv = 0;
	} else {
		elFlt = (elMaj - elMin) / elMin;
		elInv = 0 != elFlt ? 1/elFlt : 0;
		elExc = 0;
	}
	sprintf( buf, _T("%.16lf"), elExc );
		::SendMessage( GetDlgItem( IDC_EDIT_EXCENTRICITY ), WM_SETTEXT, 0, (LPARAM) buf );
	sprintf( buf, _T("%.16lf"), elFlt );
		::SendMessage( GetDlgItem( IDC_EDIT_FLATTENING ), WM_SETTEXT, 0, (LPARAM) buf );
	sprintf( buf, _T("%.16lf"), elInv );
	::SendMessage( GetDlgItem( IDC_EDIT_FLATTENINGINV ), WM_SETTEXT, 0, (LPARAM) ( 0 == elInv ? szUndef : buf ) );
}

void CTRiASGCSPpg::UpdateControls( ) {
	TRIASCSGEODETICDATUM	gd;
	TRIASCSELLIPSOID		el;

	HWND	hcombo = GetDlgItem( IDC_GEODETIC_DATUM );
	int	sel = ::SendMessage( hcombo, CB_GETCURSEL, 0, 0 );
	gd = (TRIASCSGEODETICDATUM) ::SendMessage( hcombo, CB_GETITEMDATA, sel, 0 );
	_ASSERTE( tcsGD_Undefined != gd );
	m_bUserDefined = false;
	::EnableWindow( GetDlgItem( IDC_EDIT_SEMI_MAJOR ), FALSE );
	::EnableWindow( GetDlgItem( IDC_EDIT_SEMI_MINOR ), FALSE );
//	::EnableWindow( GetDlgItem( IDC_BTN_DATUMPAR ), FALSE );
	hcombo = GetDlgItem( IDC_ELLIPSOID );
	if( tcsGD_UserDefined != gd ) {
		::EnableWindow( hcombo, FALSE );
		el = (TRIASCSELLIPSOID) _EM.GetParameter( tcsCType_EllipsOfGD, gd );
		LPCTSTR pName = _EM.Decode( tcsCType_Ellipsoid, el );
		::SendMessage( hcombo, CB_SELECTSTRING, 0, (LPARAM) pName );
	} else {
		::EnableWindow( hcombo, TRUE );
		sel = ::SendMessage( hcombo, CB_GETCURSEL, 0, 0 );
		el = (TRIASCSELLIPSOID) ::SendMessage( hcombo, CB_GETITEMDATA, sel, 0 );
		if( tcsEL_UserDefined == el ) {
			m_bUserDefined = true;
			::EnableWindow( GetDlgItem( IDC_EDIT_SEMI_MAJOR ), TRUE );
			::EnableWindow( GetDlgItem( IDC_EDIT_SEMI_MINOR ), TRUE );
//			::EnableWindow( GetDlgItem( IDC_BTN_DATUMPAR ), TRUE );
		}
	}
	RecalcEllipsoid( el );
}

STDMETHODIMP CTRiASGCSPpg::Apply(void) {
	WTRiASCS		pCS;
	WTRiASCSGCS		pGCS;
	TRIASCSGEODETICDATUM	gd;
	TRIASCSELLIPSOID		el;

	HWND	hcombo = GetDlgItem( IDC_GEODETIC_DATUM );
	int	sel = ::SendMessage( hcombo, CB_GETCURSEL, 0, 0 );
	gd = (TRIASCSGEODETICDATUM) ::SendMessage( hcombo, CB_GETITEMDATA, sel, 0 );
	hcombo = GetDlgItem( IDC_ELLIPSOID );
	sel = ::SendMessage( hcombo, CB_GETCURSEL, 0, 0 );
	el = (TRIASCSELLIPSOID) ::SendMessage( hcombo, CB_GETITEMDATA, sel, 0 );
	HRESULT	hr;

	for (UINT i = 0; i < m_nObjects; i++) {
		if( S_OK == m_ppUnk[i]->QueryInterface(IID_ITRiASCS, pCS.ppv()) ) {
			if( S_OK == pCS->get_GeographicCS( pGCS.ppi() ) ) {
				hr = pGCS->put_GeodeticDatum( gd );
				if( tcsGD_UserDefined ==  gd ) {
					hr = pGCS->put_Ellipsoid( el );
				}
			}
		}
	}
	m_bDirty = FALSE;
	return S_OK;
}
