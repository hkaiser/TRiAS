// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: $$date_n_time$$
//
// @doc
// @module $$safe_root$$App.h | Declaration of the <c C$$safe_root$$App> class

#if !defined(_$$SAFE_ROOT$$APP_H_$$MAINAPP_H_GUID$$_INCLUDED_)
#define _$$SAFE_ROOT$$APP_H_$$MAINAPP_H_GUID$$_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

using namespace std;

/////////////////////////////////////////////////////////////////////////////
// C$$safe_root$$App class

class C$$safe_root$$App : public CWinApp
{
	DECLARE_DYNCREATE(C$$safe_root$$App)

public:
	C$$safe_root$$App();
	virtual ~C$$safe_root$$App();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C$$safe_root$$App)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(C$$safe_root$$App)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

public:
	int doWork(LPCTSTR pcInFile);			// do the main work

	int AnalyzeCmdLine (int iArgc, char *cbArgv[]);
	bool PrintStartupLogo (void);
	int PrintUsage (void);

	bool NoLogo() { return m_fNoLogo; }
	int OptIndex() { return m_iOptIndex; }

protected:
	string LoadStringRes (UINT uiID);
	int GetNextOption (int argc, char *argv[], char *optstring);

private:
	bool m_fNoLogo;
	string m_strOutFile;

// command line support
	char *m_pOptArg;
	int m_iOptIndex;
	int m_iOptError;
	int m_iInOpt;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_$$SAFE_ROOT$$APP_H_$$MAINAPP_H_GUID$$_INCLUDED_)
