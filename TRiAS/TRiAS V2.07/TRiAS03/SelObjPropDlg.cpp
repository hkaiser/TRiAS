// Select ObjectProperties from PopUpTree
// File: SelObjPropDlg.cpp

#include "trias03p.hxx"
#include "trias03.h"

#include <xtsnguid.h>

#include "SelObjPropDlg.h"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma warning(disable:4355)

CSelObjPropsDlg::CSelObjPropsDlg (Window *pW, ResourceFile &rRF, IObjectProps *pIObjProps)
	: DialogWindow (pW, ResID(IDD_SELECT_OBJPROPS, &rRF)),
	  m_ObjProps (this, IDC_OBJPROPS, pIObjProps)
{
	m_fInitializing = false;
	m_fSelected = false;
}

#pragma warning(default:4355)

CSelObjPropsDlg::~CSelObjPropsDlg (void)
{
}

bool CSelObjPropsDlg::FInit (LPCSTR pcSelect)
{
	m_fInitializing = true;

string str = (NULL != pcSelect) ? pcSelect : TEXT("");
bool fResult = m_ObjProps.InitControl (str);

	if (fResult && NULL != pcSelect) 
		m_strSelected = pcSelect;

	m_fInitializing = false;

return fResult;
}

void CSelObjPropsDlg::OnSelChanged (NotifyEvt)
{
// erst auswerten, wenns richtig losgegangen ist
	if (m_fInitializing) return;		

	m_fSelected = false;
	m_ObjProps.SetHasSelectedItem (false);

HRESULT hr = m_ObjProps.GetSelectedObjProp (m_strSelected, &m_strSelectedFull);

	if (FAILED(hr)) {
		EndDlg();
		return;
	}
	if (S_FALSE == hr) return;

	m_fSelected = true;
	m_ObjProps.SetHasSelectedItem (true);
}

void CSelObjPropsDlg::ButtonClick (ControlEvt e)
{
	if (IDCANCEL == (UINT)e.GetControlID())
		EndDlg(false);
}

LRESULT CSelObjPropsDlg::Dispatch (Event e)
{
	switch (e.Msg()) {
	case WM_ITEMSELECTED:
		if (m_fSelected || m_ObjProps.GetHasSelectedItem()) {
			m_fSelected = false;
			EndDlg(true);
		} 
		break;

	case WM_CANCELDIALOG:
		m_fSelected = false;
		EndDlg(false);
		break;

	default:
		break;
	}

	return DialogWindow::Dispatch(e);
}

void CSelObjPropsDlg::OnItemExpanded (NotifyEvt e)
{
	m_ObjProps.OnItemExpanded(e);
	m_fSelected = false;
}
