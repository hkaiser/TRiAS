// TRiASPCSPpg.cpp : Implementation of CTRiASPCSPpg
#include "stdafx.h"
#include "TRiASCSImpl.h"
#include "TRiASPCSPpg.h"
#include "EpsgMgr.h"

/////////////////////////////////////////////////////////////////////////////
// CTRiASPCSPpg

HRESULT	CTRiASPCSPpg::FinalConstruct() {
	return S_OK;
}

void CTRiASPCSPpg::FinalRelease() {}

STDMETHODIMP CTRiASPCSPpg::Apply(void) {
	WTRiASCS		pCS;
	WTRiASCSPCS		pPCS;
	HWND	hcombo = GetDlgItem( IDC_PROJECTIONALGORITHM );
	int	sel = ::SendMessage( hcombo, CB_GETCURSEL, 0, 0 );
	TRIASCSPROJECTIONALGORITHM pa = (TRIASCSPROJECTIONALGORITHM) ::SendMessage( hcombo, CB_GETITEMDATA, sel, 0 );
	HRESULT	hr;
	for (UINT i = 0; i < m_nObjects; i++) {
		if( S_OK == m_ppUnk[i]->QueryInterface(IID_ITRiASCS, pCS.ppv()) ) {
			if( S_OK == pCS->get_ProjectedCS( pPCS.ppi() ) ) {
				hr = pPCS->put_ProjectionAlgorithm( pa );
			}
		}
	}
	m_bDirty = FALSE;
	return S_OK;
}

LRESULT CTRiASPCSPpg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
	TRIASCSPROJECTIONALGORITHM	pa;
	WTRiASCS		pCS;
	WTRiASCSPCS	pPCS;
	HRESULT			hr;
	CODENAME		*pCode;
	WTRiASCSTransformInfo	pTI;
	RETURN_FAILED_HRESULT( m_ppUnk[0]->QueryInterface(IID_ITRiASCS, pCS.ppv()) );
	RETURN_FAILED_HRESULT( pCS->get_ProjectedCS( pPCS.ppi() ) );
	try {
		pTI = pPCS;
	} catch(...) {
	}
	HWND	hcombo = GetDlgItem( IDC_PROJECTIONALGORITHM );
	int		nItem;
	/////////////////////////////////////////////////////////////
	// Combobox füllen
	for( pCode = _CT_TRIASCSPROJECTIONALGORITHM; -1 != pCode->code && NULL != pCode->name; pCode++ ) {
		if( !!pTI && S_OK == pTI->CanTransform( pCode->code ) ) {
			nItem = ::SendMessage( hcombo, CB_ADDSTRING, 0, (LPARAM) pCode->name );
			::SendMessage( hcombo, CB_SETITEMDATA, nItem, (DWORD) pCode->code );
		}
	}
	/////////////////////////////////////////////////////////////
	// und Projektion einstellen
	hr = pPCS->get_ProjectionAlgorithm( &pa );
	if( tcsPA_Undefined == pa ) {
		pa = tcsPA_GaussKrueger;
		pPCS->put_ProjectionAlgorithm( pa );
	}
	LPCTSTR pName = _EM.Decode( tcsCType_PA, pa );
	::SendMessage( hcombo, CB_SELECTSTRING, 0, (LPARAM) pName );
	UpdateControls();
	return 0;
}

static struct PARMS {
	UINT	ctrlName;
	UINT	ctrlValue;
} CTRLS[] = {
	{ IDC_PARAM1_NAME, IDC_PARAM1 }
	, { IDC_PARAM2_NAME, IDC_PARAM2 }
	, { IDC_PARAM3_NAME, IDC_PARAM3 }
	, { IDC_PARAM4_NAME, IDC_PARAM4 }
	, { IDC_PARAM5_NAME, IDC_PARAM5 }
	, { IDC_PARAM6_NAME, IDC_PARAM6 }
	, { IDC_PARAM7_NAME, IDC_PARAM7 }
	, {0,0}
};

#define _countof(x) (sizeof(x)/sizeof(x[0]))

#include "LocaleHelpers.h"
#include <stdio.h>

HRESULT CTRiASPCSPpg::UpdateControls( ) {
	WTRiASCS					pCS;
	WTRiASCSPCS					pPCS;
	TRIASCSPROJECTIONALGORITHM	pa;
	TRIASCSPROJECTIONPARAMETER	pp;
	RETURN_FAILED_HRESULT( m_ppUnk[0]->QueryInterface(IID_ITRiASCS, pCS.ppv()) );
	RETURN_FAILED_HRESULT( pCS->get_ProjectedCS( pPCS.ppi() ) );
	RETURN_FAILED_HRESULT( pPCS->get_ProjectionAlgorithm( &pa ) );
	_ASSERTE( tcsPA_Undefined != pa );

	PA_AttribsVector	v;
	int nParams = _EM.GetAttribs( pa, v );
	sort( v.begin(), v.end() );
	double						param;
	TCHAR	buf[_MAX_PATH];
	CSetLocale					loc;
	int	nParam = 0;
	for( PA_AttribsVector::iterator i = v.begin(); v.end() != i && nParam < _countof(CTRLS); i++, nParam++ ) {
		pp = (*i);
		RETURN_FAILED_HRESULT( pPCS->get_ProjectionParameter( pp, &param ) );
		sprintf( buf, _T("%.7lf"), param );
		::ShowWindow( GetDlgItem( CTRLS[nParam].ctrlName ), SW_SHOW );
		::ShowWindow( GetDlgItem( CTRLS[nParam].ctrlValue ), SW_SHOW );
		::SendMessage( GetDlgItem( CTRLS[nParam].ctrlName ), WM_SETTEXT, 0, (LPARAM) _EM.GetAttrib( pa, (*i) ) );
		::SendMessage( GetDlgItem( CTRLS[nParam].ctrlValue ), WM_SETTEXT, 0, (LPARAM) buf );
	}
	for( ; nParam < _countof(CTRLS); nParam++ ) {
		::ShowWindow( GetDlgItem( CTRLS[nParam].ctrlName ), SW_HIDE );
		::ShowWindow( GetDlgItem( CTRLS[nParam].ctrlValue ), SW_HIDE );
	}
	_ASSERTE(nParams<nParam);
	return S_OK;
}
