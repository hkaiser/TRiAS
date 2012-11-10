// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 07.02.2003 12:09:32 
//
// @doc
// @module ManageObjectPropertiesDlg.cpp | Definition of the <c CManageObjectPropertiesDlg> class

#include "trias03p.hxx"
#include "trias03.h"

#include <stddlg.hxx>

#include "ManageObjectPropertiesDlg.h"
#include "NewLoadableObjectProperty.h"

extern char g_pDLLName[_MAX_PATH];

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(ObjectProps);

///////////////////////////////////////////////////////////////////////////////
// 
bool ObjPropsToCfg (DWORD dwFlags)
{
	return (dwFlags & PROPCAPS_LOADABLE);
}

///////////////////////////////////////////////////////////////////////////////
// 
#pragma warning(disable: 4355)
CManageObjectPropertiesDlg::CManageObjectPropertiesDlg(ResourceFile &rRF) :
	CPropertyPage(ResID(IDD_MANAGEOBJECTPROPERTIES, &rRF), 
		ResString(ResID(IDS_MANAGEOBJECTPROPERTIES_CAP, &rRF), _MAX_PATH)),
	m_ObjProps(this, IDC_OBJECTPROPERTIES, NULL, ObjPropsToCfg, false),
	m_pbDelete(this, IDC_DELOBJPROP),
	m_pbProperties(this, IDC_OBJPROP_PROPS)
{
WObjectProps Props;
BOOL fMustReInit = DEX_GetObjectProps (Props.ppi());

	if (Props.IsValid()) {
	// evtl. alle ObjProps installieren
		if (fMustReInit) {
			Props -> OnNewReferenceObject (-1L);	// alles bisherige löschen
			if (FAILED(Props -> OnNewReferenceObject (0L))) 
				return;
			DEX_SetMustInitOPFs(FALSE);
		}
	}
	m_ObjProps.SetObjectProps(Props);
}
#pragma warning(default: 4355)

CManageObjectPropertiesDlg::~CManageObjectPropertiesDlg()
{
}

void CManageObjectPropertiesDlg::OnNewObjProp()
{
ResourceFile RF (g_pDLLName);
CNewLoadableObjectPropertyDlg NewDlg (this, ResID(IDD_NEWOBJPROP, &RF));

	CentreWindow(this, &NewDlg);

Point ptPos = NewDlg.GetPosition();

	ptPos.X() += 30;
	ptPos.Y() -= 30;
	NewDlg.ChangePosition(ptPos);
	NewDlg.Show();
}

void CManageObjectPropertiesDlg::ObDelObjProp()
{
}

void CManageObjectPropertiesDlg::ObObjPropProperties()
{
}

void CManageObjectPropertiesDlg::AdjustButtons()
{
	if (0 == m_ObjProps.CountSelectedItems()) {
		m_pbDelete.Disable();
		m_pbProperties.Disable();
	}
	else {
		m_pbDelete.Enable();
		m_pbProperties.Enable();
	}
}

///////////////////////////////////////////////////////////////////////////////
// Message handler
void CManageObjectPropertiesDlg::WindowInit (Event e)
{
	m_ObjProps.InitControl(os_string(""));
}

void CManageObjectPropertiesDlg::ButtonClick(ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDC_NEWOBJPROP:
		OnNewObjProp();
		break;

	case IDC_DELOBJPROP:
		ObDelObjProp();
		break;

	case IDC_OBJPROP_PROPS:
		ObObjPropProperties();
		break;
	}
}

void CManageObjectPropertiesDlg::OnSelChanged (NotifyEvt e)
{
// Messagereflection
NMTREEVIEW *pnmtv = (NMTREEVIEW *)e.GetNotifyInfo();

// Knöpfchen richten
	AdjustButtons();
}

