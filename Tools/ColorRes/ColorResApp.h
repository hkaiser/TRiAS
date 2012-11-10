// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 09.09.2002 10:01:19
//
// @doc
// @module ColorResApp.h | Declaration of the <c CColorResApp> class

#if !defined(_COLORRESAPP_H_3CEC0E0D_DB51_4509_9D6E_B6BEE377B847_INCLUDED_)
#define _COLORRESAPP_H_3CEC0E0D_DB51_4509_9D6E_B6BEE377B847_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <ospace/std/vector>

#include "InitLeadTools.h"

/////////////////////////////////////////////////////////////////////////////
// CColorResApp class

class CColorResApp : public CWinApp
{
	DECLARE_DYNCREATE(CColorResApp)

public:
	CColorResApp();
	virtual ~CColorResApp();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorResApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CColorResApp)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

public:
	int doWork(LPCTSTR pcInFile, LPCSTR pcOutFile);			// do the main work

	int AnalyzeCmdLine (int iArgc, char *cbArgv[]);
	bool PrintStartupLogo (void);
	int PrintUsage (void);

	bool NoLogo() { return m_fNoLogo; }
	int OptIndex() { return m_iOptIndex; }

protected:
	string LoadStringRes (UINT uiID);
	int GetNextOption (int argc, char *argv[], char *optstring);
	bool FillResolutions(LPCSTR pcOptArgs);

private:
	bool m_fNoLogo;
	bool m_fCopyTfw;
    bool m_fReduceColors;
	L_UINT32 m_uiResizeMode;
	vector<double> m_vecKoeffs;

// command line support
	char *m_pOptArg;
	int m_iOptIndex;
	int m_iOptError;
	int m_iInOpt;

// LeadTools support
	CLeadTools m_LeadTools;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_COLORRESAPP_H_3CEC0E0D_DB51_4509_9D6E_B6BEE377B847_INCLUDED_)
