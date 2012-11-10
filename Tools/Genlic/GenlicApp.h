// $Header: $
// Copyright© 2003 Hartmut Kaiser, All rights reserved
// Created: 13.12.2003 19:54:19
//
// @doc
// @module GenlicApp.h | Declaration of the <c CGenlicApp> class

#if !defined(_GENLICAPP_H_E5F47170_2F79_4D73_BB84_2AF5FC425172_INCLUDED_)
#define _GENLICAPP_H_E5F47170_2F79_4D73_BB84_2AF5FC425172_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

using namespace std;

/////////////////////////////////////////////////////////////////////////////
// CGenlicApp class

class CGenlicApp : public CWinApp
{
	DECLARE_DYNCREATE(CGenlicApp)

public:
	CGenlicApp();
	virtual ~CGenlicApp();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGenlicApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CGenlicApp)
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

	int GenerateLicenseFile(char const *pcLicense);

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

#endif // !defined(_GENLICAPP_H_E5F47170_2F79_4D73_BB84_2AF5FC425172_INCLUDED_)
