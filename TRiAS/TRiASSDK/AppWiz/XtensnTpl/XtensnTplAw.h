#if !defined(AFX_XTENSNTPLAW_H__6A507FFE_EB40_11D2_9BDF_745820524153__INCLUDED_)
#define AFX_XTENSNTPLAW_H__6A507FFE_EB40_11D2_9BDF_745820524153__INCLUDED_

// XtensnTplaw.h : header file
//

class CDialogChooser;

// All function calls made by mfcapwz.dll to this custom AppWizard (except for
//  GetCustomAppWizClass-- see XtensnTpl.cpp) are through this class.  You may
//  choose to override more of the CCustomAppWiz virtual functions here to
//  further specialize the behavior of this custom AppWizard.
class CXtensnTplAppWiz : public CCustomAppWiz
{
public:
	virtual CAppWizStepDlg* Next(CAppWizStepDlg* pDlg);
		
	virtual void InitCustomAppWiz();
	virtual void ExitCustomAppWiz();
	virtual void CustomizeProject(IBuildProject* pProject);

	BOOL AddGuid (LPCTSTR pcEntry, BOOL fReplaceDash = FALSE);
};

// This declares the one instance of the CXtensnTplAppWiz class.  You can access
//  m_Dictionary and any other public members of this class through the
//  global XtensnTplaw.  (Its definition is in XtensnTplaw.cpp.)
extern CXtensnTplAppWiz XtensnTplaw;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XTENSNTPLAW_H__6A507FFE_EB40_11D2_9BDF_745820524153__INCLUDED_)
