// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 12.01.2000 09:43:16 
//
// @doc
// @module TRiASDBDSAw.h | Declaration of the <c CTRiASDBDSAw> class

#if !defined(AFX_TRIASDBDSAW_H__1724BBE5_E51D_11D2_9BD8_E6AA20524153__INCLUDED_)
#define AFX_TRIASDBDSAW_H__1724BBE5_E51D_11D2_9BD8_E6AA20524153__INCLUDED_

#include <ObjModel/AppGuid.h>
#include <ObjModel/BldAuto.h>

class CDialogChooser;

// All function calls made by mfcapwz.dll to this custom AppWizard (except for
//  GetCustomAppWizClass-- see TRiASDBDS.cpp) are through this class.  You may
//  choose to override more of the CCustomAppWiz virtual functions here to
//  further specialize the behavior of this custom AppWizard.
class CTRiASDBDSAppWiz : 
	public CCustomAppWiz
{
public:
	virtual CAppWizStepDlg* Next(CAppWizStepDlg* pDlg);
	virtual CAppWizStepDlg* Back(CAppWizStepDlg* pDlg);
		
	virtual void InitCustomAppWiz();
	virtual void ExitCustomAppWiz();
	virtual void CustomizeProject(IBuildProject* pProject);
	virtual void GetPlatforms(CStringList& Platforms);

	BOOL FindOrCreateGuid (LPCTSTR pcEntry, LPCSTR pcProgID, BOOL fReplaceDash = FALSE);
	BOOL FindOrCreateLibID (LPCTSTR pcEntry, LPCSTR pcProgID);
	BOOL EmitGaranties();

protected:
	BOOL AddGuid (LPCTSTR pcEntry, BOOL fReplaceDash = FALSE);
	void SetRootOptions();

private:
	CDialogChooser* m_pChooser;
	CString m_Initials;
};

// This declares the one instance of the CTRiASDBDSAppWiz class.  You can access
//  m_Dictionary and any other public members of this class through the
//  global TRiASDBDSaw.  (Its definition is in TRiASDBDSaw.cpp.)
extern CTRiASDBDSAppWiz TRiASDBDSaw;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRIASDBDSAW_H__1724BBE5_E51D_11D2_9BD8_E6AA20524153__INCLUDED_)
