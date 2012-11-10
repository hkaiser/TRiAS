#include "stdafx.h"
#include "UICtrl.h"
#include "PpgMaskEdit.h"

/////////////////////////////////////////////////////////////////////////////
// CPpgMaskEdit

LRESULT CPpgMaskEdit::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
	USES_CONVERSION;
	BSTR	s;
	for (UINT i = 0; i < m_nObjects; i++) {
		CComQIPtr<IMaskEdit, &IID_IMaskEdit> pMaskEdit(m_ppUnk[i]);
		pMaskEdit->get_Mask( &s );
		LPCTSTR	lpszMask = W2A(s);
		SetDlgItemText( IDC_EDIT_MASK, lpszMask );
		::SysFreeString( s );
	}
	return 0;
}
	
STDMETHODIMP CPpgMaskEdit::Apply(void) {
	if( !m_bDirty )
		return S_OK;
	ATLTRACE(_T("CPpgMaskEdit::Apply\n"));
	USES_CONVERSION;
	TCHAR	szMask[1024];
	GetDlgItemText( IDC_EDIT_MASK, szMask, sizeof(szMask) );
	CComBSTR	strMask( szMask );
	for (UINT i = 0; i < m_nObjects; i++) {
		CComQIPtr<IMaskEdit, &IID_IMaskEdit> pMaskEdit(m_ppUnk[i]);
		pMaskEdit->put_Mask( strMask );
		// Do something interesting here
		// ICircCtl* pCirc;
		// m_ppUnk[i]->QueryInterface(IID_ICircCtl, (void**)&pCirc);
		// pCirc->put_Caption(CComBSTR("something special"));
		// pCirc->Release();
	}
	m_bDirty = FALSE;
	return S_OK;
}
