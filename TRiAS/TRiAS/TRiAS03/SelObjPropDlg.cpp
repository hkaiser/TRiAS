// Select ObjectProperties from PopUpTree
// File: SelObjPropDlg.cpp

#include "trias03p.hxx"
#include "trias03.h"

#include <xtsnguid.h>

#include <SelObjPropDlg.h>

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma warning(disable:4355)

CSelObjPropsDlg::CSelObjPropsDlg (Window *pW, IObjectProps *pIObjProps, INCLUDEOBJPROP pFcn)
	: DialogWindow (pW, IDD_SELECT_OBJPROPS), 
	  m_ObjProps (this, IDC_OBJPROPS, pIObjProps, pFcn),
	  m_strSelected(""),
	  m_strSelectedFull("")
{
	m_fInitializingOrDestroying = false;
	m_fSelected = false;
}

#pragma warning(default:4355)

CSelObjPropsDlg::~CSelObjPropsDlg (void)
{
	m_fInitializingOrDestroying = true;		// OnSelChanged darf nicht mehr bearbeitet werden
}

bool CSelObjPropsDlg::FInit (LPCSTR pcSelect)
{
	m_fInitializingOrDestroying = true;

string str = (NULL != pcSelect) ? pcSelect : TEXT("");
bool fResult = m_ObjProps.InitControl (str);

	if (fResult && NULL != pcSelect) 
		m_strSelected = pcSelect;

	m_fInitializingOrDestroying = false;
	return fResult;
}

void CSelObjPropsDlg::OnSelChanged (NotifyEvt)
{
// erst auswerten, wenns richtig losgegangen ist
	if (m_fInitializingOrDestroying) return;		

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
		EndDlg (FALSE);
}

LRESULT CSelObjPropsDlg::Dispatch (Event e)
{
	switch (e.Msg()) {
	case WM_ITEMSELECTED:
		if (m_fSelected || m_ObjProps.GetHasSelectedItem()) {
			m_fSelected = false;
			EndDlg (TRUE);
		} 
		break;

	case WM_CANCELDIALOG:
		if (0 == Result()) {
		// nur, wenn noch kein EndDlg(TRUE) da war
			m_fSelected = false;
			EndDlg (FALSE);
		}
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

// Implementation of ReSize
void CSelObjPropsDlg::ReSize(ReSizeEvt e)
{
// TreeControl auch mit in seiner Größe verändern
	m_ObjProps.ChangeSize(e.GetNewSize());
}

