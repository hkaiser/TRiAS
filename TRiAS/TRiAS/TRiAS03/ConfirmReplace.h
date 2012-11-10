// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 06.03.2001 18:37:33 
//
// @doc
// @module ConfirmReplace.h | Declaration of the <c CConfirmReplace> class

#if !defined(_CONFIRMREPLACE_H__F5544B13_F0C4_45E5_BAFA_46CD866676EC__INCLUDED_)
#define _CONFIRMREPLACE_H__F5544B13_F0C4_45E5_BAFA_46CD866676EC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// Dialog, welcher für ein Objekt 'Ersetzen' bestätigt
class CConfirmReplaceDlg :
	public DialogWindow
{
public:
	CConfirmReplaceDlg(Window *pParent, ResID resDlg);
	~CConfirmReplaceDlg();

	enum CONFIRMATION {
		CONFIRMATION_Unknown = -1,
		CONFIRMATION_Cancel = 0,
		CONFIRMATION_SearchNext = 1,
		CONFIRMATION_Replace = 2,
		CONFIRMATION_ReplaceAll = 3,
		CONFIRMATION_NewValue = 0x80,	// combine with Replace or ReplaceAll
	};
	CONFIRMATION HandleNextObject (INT_PTR lONr, BSTR bstrOldValue, BSTR bstrNewValue, BSTR *pbstrNewValue);

	enum {
		IDD = IDD_REPLACE_CONFIRM
	};

	void StartSelection();
	void EndSelection();

protected:
	void ButtonClick(ControlEvt e);
	void Strobe (StrobeEvt e);

private:
	PushButton m_pbReplace;
	PushButton m_pbReplaceAll;
	SingleLineEdit m_sleObjProp;
	SingleLineEdit m_sleOldValue;
	SingleLineEdit m_sleNewValue;

	BOOL *m_pfContinue;
	CONFIRMATION m_rgConfirm;
	ACTIVATEOBJECT m_ao;
	bool m_fSelected;
};

#endif // !defined(_CONFIRMREPLACE_H__F5544B13_F0C4_45E5_BAFA_46CD866676EC__INCLUDED_)
