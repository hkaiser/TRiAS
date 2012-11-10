// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 12.01.2000 00:03:49 
//
// @doc
// @module Chooser.h | Declaration of the <c CChooser> class

#if !defined(_CHOOSER_H__9743BC9F_D2A1_40DC_9205_A41BC42D12BF__INCLUDED_)
#define _CHOOSER_H__9743BC9F_D2A1_40DC_9205_A41BC42D12BF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

// List of the steps we can pop up
enum {
	DLG_CONFIG = 1,
};

#define NUM_DLGS 1

class CAppWizStepDlg;

class CDialogChooser
{
public:
	CDialogChooser();
	~CDialogChooser();

	// All calls by mfcapwz.dll to CCustomWizAppWiz::Next &
	//  CCustomWizAppWiz::Back are delegated to these member
	//  functions, which keep track of what dialog is up
	//  now, and what to pop up next.
	CAppWizStepDlg* Next(CAppWizStepDlg* pDlg);
	CAppWizStepDlg* Back(CAppWizStepDlg* pDlg);

protected:
	int m_nCurrDlg;     // Current step's DLG_ enum from above, or 0 for
						//  the intial "New Project" dialog.
	CAppWizStepDlg* m_pDlgs[NUM_DLGS+1];
						// Instances of the dialog classes of our steps
	void UpdateTitleIfNecessary();
};

#endif // !defined(_CHOOSER_H__9743BC9F_D2A1_40DC_9205_A41BC42D12BF__INCLUDED_)
