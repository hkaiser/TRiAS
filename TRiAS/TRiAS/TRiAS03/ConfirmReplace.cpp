// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 06.03.2001 18:48:49 
//
// @doc
// @module ConfirmReplace.cpp | Definition of the <c CConfirmReplace> class

#include "trias03p.hxx"

#if defined(_USE_CONFIRMREPLACE_DIALOG)

#include "trias03.h"
#include "ConfirmReplace.h"

///////////////////////////////////////////////////////////////////////////////
// Dialog, welcher für ein Objekt 'Ersetzen' bestätigt
CConfirmReplaceDlg::CConfirmReplaceDlg(Window *pParent, ResID resDlg) :
	DialogWindow(pParent, resDlg, false),
	m_pbReplace(this, IDB_REPLACE),
	m_pbReplaceAll(this, IDB_REPLACEALL),
	m_sleObjProp(this, IDC_OBJECT_PROPS),
	m_sleOldValue(this, IDC_OLDVALUE),
	m_sleNewValue(this, IDC_NEWVALUE)
{
	m_pfContinue = NULL;
	m_rgConfirm = CONFIRMATION_Unknown;
	INITSTRUCT(m_ao, ACTIVATEOBJECT);
	m_ao.crAct = RGB(0, 0, 255);
	m_fSelected = false;
}

CConfirmReplaceDlg::~CConfirmReplaceDlg()
{
	_ASSERTE(!m_fSelected);
}

///////////////////////////////////////////////////////////////////////////////
// Werte für ein Objekt anzeigen und Antwort abwarten
namespace {
	class CEnableBlinking
	{
	public:
		CEnableBlinking(CConfirmReplaceDlg *pDlg) : 
			m_pDlg(pDlg), m_timer(CEnableBlinking::TIMER_INTERVAL, CEnableBlinking::TIMER_ID)
		{
			pDlg -> StartSelection();
			pDlg -> SetStrobe(&m_timer);
		}
		~CEnableBlinking()
		{
			m_pDlg -> CancelStrobe(&m_timer);
			m_pDlg -> EndSelection();
		}

		enum {
			TIMER_INTERVAL = 500,	// ms
			TIMER_ID = 100,
		};

	private:
		CConfirmReplaceDlg *m_pDlg;
		Timer m_timer;
	};
}

void CConfirmReplaceDlg::StartSelection()
{
	_ASSERTE(NULL != m_ao.lONr);
	DEX_SelectObject(m_ao);
	m_fSelected = true;
}

void CConfirmReplaceDlg::EndSelection()
{
	_ASSERTE(NULL != m_ao.lONr);
	DEX_UnselectObject(m_ao.lONr);
	m_fSelected = false;
}

CConfirmReplaceDlg::CONFIRMATION CConfirmReplaceDlg::HandleNextObject(
	INT_PTR lONr, BSTR bstrOldValue, BSTR bstrNewValue, BSTR *pbstrNewValue)
{
	USES_CONVERSION;

LPCSTR pcNewValue = OLE2A(bstrNewValue);
LPCSTR pcObjDesc = DEX_GetObjectDescriptionString(lONr);

	m_sleOldValue.SetText(OLE2A(bstrOldValue));
	m_sleNewValue.SetText(pcNewValue);
	if (NULL != pcObjDesc) {
		m_sleObjProp.SetText(pcObjDesc);
		CoTaskMemFree((void *)pcObjDesc);
	}

	m_pfContinue = NULL;
	m_rgConfirm = CONFIRMATION_Unknown;
	m_ao.lONr = lONr;

CEnableBlinking blink(this);

	App::Exec(ExecNormal, &m_pfContinue);

char cbBuffer[4*_MAX_PATH];

	m_sleNewValue.GetText(cbBuffer, sizeof(cbBuffer));
	if (NULL != pbstrNewValue && strcmp (cbBuffer, pcNewValue) && 
		(CONFIRMATION_Replace == m_rgConfirm || CONFIRMATION_ReplaceAll == m_rgConfirm))
	{
		m_rgConfirm = CONFIRMATION(m_rgConfirm | CONFIRMATION_NewValue);	// Neuer Wert wurde editiert
		*pbstrNewValue = CComBSTR(cbBuffer).Detach();
	}
	return m_rgConfirm;
}

void CConfirmReplaceDlg::ButtonClick(ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDCANCEL:
		m_rgConfirm = CONFIRMATION_Cancel;
		if (NULL != m_pfContinue)
			*m_pfContinue = FALSE;
		break;

	case IDOK:
		m_rgConfirm = CONFIRMATION_SearchNext;
		if (NULL != m_pfContinue)
			*m_pfContinue = FALSE;
		break;

	case IDB_REPLACE:
		m_rgConfirm = CONFIRMATION_Replace;
		if (NULL != m_pfContinue)
			*m_pfContinue = FALSE;
		break;

	case IDB_REPLACEALL:
		m_rgConfirm = CONFIRMATION_ReplaceAll;
		if (NULL != m_pfContinue)
			*m_pfContinue = FALSE;
		break;

	case IDB_SHOW_OBJECT:
		DEX_ZoomInToObject(m_ao.lONr);
		break;
	}
}

void CConfirmReplaceDlg::Strobe (StrobeEvt e)
{
	_ASSERTE(CEnableBlinking::TIMER_ID == e.GetStrobeID());
	if (m_fSelected)
		EndSelection();
	else
		StartSelection();
}

#endif // defined(_USE_CONFIRMREPLACE_DIALOG)
