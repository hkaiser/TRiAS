// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 08.12.2000 23:25:44 
//
// @doc
// @module RechResultORWnd.cpp | Definition of the <c CRechResultORWnd> class

#include "triaspre.hxx"

#include "triasres.h"
#include "Strings.h"

#include "RechResultORWnd.h"

#pragma warning(disable: 4355)

///////////////////////////////////////////////////////////////////////////////
// Vorgeben der anzuzeigenden Rechercheergebnisse
CRechResultORWndDlg::CRechResultORWndDlg(pWindow pW) :
	DialogWindow (pW, IDD_ORWND_SELECTRESULT),
	m_ObjPropSrc (this, IDC_OBJPROPERTY, IDC_SELECT_OBJPROP),
	m_cbIdent (this, IDCB_RECHRES_IDENT),
	m_cbObjTyp (this, IDCB_RECHRES_OBJTYP),
	m_cbDataSource (this, IDC_DATASOURCE),
	m_cbObjProp (this, IDC_OBJECTPROPERTY)
{
	m_fFlags = 0;
	m_ObjPropSrc.FInit();
	if (DEX_GetOpenConnectionCount (QDCAllOpen|QDCCountQueryDefs) <= 1)
		m_cbDataSource.Hide();
}

#pragma warning(default: 4355)

CRechResultORWndDlg::~CRechResultORWndDlg()
{
}

///////////////////////////////////////////////////////////////////////////////
// EventHandler
void CRechResultORWndDlg::ButtonClick(ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDOK:
		EndDlg (true);
		break;
		
	case IDCANCEL:
		EndDlg (false);
		break;
		
	case IDCB_RECHRES_IDENT:
		m_fFlags &= ~ROHideIdent;
		if (!m_cbIdent.isChecked())
			m_fFlags |= ROHideIdent;
		break;

	case IDCB_RECHRES_OBJTYP:
		m_fFlags &= ~ROHideObjTyp;
		if (!m_cbObjTyp.isChecked())
			m_fFlags |= ROHideObjTyp;
		break;

	case IDC_DATASOURCE:
		if (DEX_GetOpenConnectionCount (QDCAllOpen|QDCCountQueryDefs) > 1) {
			m_fFlags &= ~ROHideDatasource;
			if (!m_cbDataSource.isChecked())
				m_fFlags |= ROHideDatasource;
		}
		break;

	case IDC_OBJECTPROPERTY:
		if (!m_cbObjProp.isChecked()) {
			m_ObjPropSrc.SaveData (m_strActOProp);
			m_ObjPropSrc.ResetSelection();
		} 
		else if (m_strActOProp.size() > 0)
			m_ObjPropSrc.InitFromData (m_strActOProp.c_str());
		break;

	case IDC_SELECT_OBJPROP:
		if (!m_ObjPropSrc.ShowObjPropDlg()) 
			m_cbObjProp.SetChecked(false);
		else
			m_cbObjProp.SetChecked(true);
		break;
	}
}

// Implementation of GetSelectedObjProp
HRESULT CRechResultORWndDlg::GetSelectedObjProp(IObjectProperty **ppIOP)
{
	return m_ObjPropSrc.GetSelectedObjProp(ppIOP);
}

// Implementation of SetSelectedObjProp
HRESULT CRechResultORWndDlg::SetSelectedObjProp(IObjectProperty *pIOP)
{
	if (NULL != pIOP) {
	char cbBuffer[_MAX_PATH];

		if (SUCCEEDED(pIOP -> GetPropInfo(cbBuffer, sizeof(cbBuffer), NULL)) &&
			SUCCEEDED(m_ObjPropSrc.InitFromData(cbBuffer)))
		{
			m_cbObjProp.SetChecked(TRUE);
			return S_OK;
		}
	}
	m_cbObjProp.SetChecked(FALSE);
	return E_FAIL;
}

// Implementation of SetSelectedObjProp
HRESULT CRechResultORWndDlg::SetSelectedObjPropName(LPCSTR pcName)
{
	if (NULL != pcName && '\0' != pcName[0]) {
		if (SUCCEEDED(m_ObjPropSrc.InitFromData(pcName))) {
			m_cbObjProp.SetChecked(TRUE);
			return S_OK;
		}
	}
	m_cbObjProp.SetChecked(FALSE);
	return E_FAIL;
}

// Implementation of GetNewFlags
int CRechResultORWndDlg::GetNewFlags()
{
	return m_fFlags;
}

// Implementation of SetFlags
void CRechResultORWndDlg::SetFlags(int iFlags)
{
	m_fFlags = iFlags;

// Controls vorinitialisieren
	m_cbIdent.SetChecked((ROHideIdent & m_fFlags) ? FALSE : TRUE);
	m_cbObjTyp.SetChecked((ROHideObjTyp & m_fFlags) ? FALSE : TRUE);
	if (DEX_GetOpenConnectionCount (QDCAllOpen|QDCCountQueryDefs) > 1)
		m_cbDataSource.SetChecked((ROHideDatasource & m_fFlags) ? FALSE : TRUE);
}

