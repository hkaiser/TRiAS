// TRiASCSPpg.cpp : Implementation of CTRiASCSPpg
#include "stdafx.h"
#include "TRiASCS.h"
#include "TRiASCSPpg.h"

/////////////////////////////////////////////////////////////////////////////
// CTRiASCSPpg

HRESULT	CTRiASCSPpg::FinalConstruct() {
	return S_OK;
}

void CTRiASCSPpg::FinalRelease() {}

LRESULT CTRiASCSPpg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
	TRIASCSTYPE	csType;
	ITRiASCS* pCS;
	if( S_OK == m_ppUnk[0]->QueryInterface(IID_ITRiASCS, (void**)&pCS) ) {
		int	nSelect = 0;
		HRESULT hr = pCS->get_CoordSystemType( &csType );
		switch( csType ) {
		case tcsCS_Geographic : nSelect = IDC_CHECKCS_GCS; break;
		case tcsCS_Projected :
		default:
			nSelect = IDC_CHECKCS_PCS;
			break;
		}
		pCS->Release();
		CheckRadioButton( IDC_CHECKCS_GCS, IDC_CHECKCS_PCS, nSelect );
	}
	return 0;
}

STDMETHODIMP CTRiASCSPpg::Apply(void) {
	ITRiASCS* pCS;
	TRIASCSTYPE	csType;
	if( IsDlgButtonChecked( IDC_CHECKCS_PCS ) ) {
		csType = tcsCS_Projected;
	} else if( IsDlgButtonChecked( IDC_CHECKCS_GCS ) ) {
		csType = tcsCS_Geographic;
	} else {
		_ASSERTE(0);
	}
	HRESULT	hr;
	for (UINT i = 0; i < m_nObjects; i++) {
		if( S_OK == m_ppUnk[i]->QueryInterface(IID_ITRiASCS, (void**)&pCS) ) {
			hr = pCS->put_CoordSystemType( csType );
			pCS->Release();
		}
	}
	m_bDirty = FALSE;
	return S_OK;
}
