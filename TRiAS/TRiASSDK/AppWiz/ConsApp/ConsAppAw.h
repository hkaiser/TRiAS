#if !defined(AFX_CONSAPPAW_H__AB27041D_0EBC_451E_81C4_BA796EB04563__INCLUDED_)
#define AFX_CONSAPPAW_H__AB27041D_0EBC_451E_81C4_BA796EB04563__INCLUDED_

// ConsAppaw.h : header file
//

class CDialogChooser;

// All function calls made by mfcapwz.dll to this custom AppWizard (except for
//  GetCustomAppWizClass-- see ConsApp.cpp) are through this class.  You may
//  choose to override more of the CCustomAppWiz virtual functions here to
//  further specialize the behavior of this custom AppWizard.
class CConsAppAppWiz : public CCustomAppWiz
{
public:
	virtual CAppWizStepDlg* Next(CAppWizStepDlg* pDlg);
		
	virtual void InitCustomAppWiz();
	virtual void ExitCustomAppWiz();
	virtual void CustomizeProject(IBuildProject* pProject);

	BOOL AddGuid (LPCTSTR pcEntry, BOOL fReplaceDash);
};

// This declares the one instance of the CConsAppAppWiz class.  You can access
//  m_Dictionary and any other public members of this class through the
//  global ConsAppaw.  (Its definition is in ConsAppaw.cpp.)
extern CConsAppAppWiz ConsAppaw;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONSAPPAW_H__AB27041D_0EBC_451E_81C4_BA796EB04563__INCLUDED_)
