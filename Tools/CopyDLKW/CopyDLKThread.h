// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 10.03.2002 10:59:10 
//
// @doc
// @module CopyDLKThread.h | Declaration of the <c CCopyDLKThread> class

/////////////////////////////////////////////////////////////////////////////////////
// WORKER THREAD DERIVED CLASS - produced by Worker Thread Class Generator Rel 1.0
// CopyDLKThread.h: Interface for the CCopyDLKThread Class.
/////////////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_COPYDLKTHREAD_H__A4C9C0B8_CD6D_11D2_BB7E_3C8B2D1E__INCLUDED_)
#define AFX_COPYDLKTHREAD_H__A4C9C0B8_CD6D_11D2_BB7E_3C8B2D1E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Thread.h"

class CCopyDLKThread : public CThread  
{
public:
	DECLARE_DYNAMIC(CCopyDLKThread)

// Construction & Destruction
	CCopyDLKThread(void* pOwnerObject = NULL, LPARAM lParam = 0L);
	virtual ~CCopyDLKThread();

// Operations & Overridables
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	BOOL Stop();

protected:
// Overridables
	virtual void OnKill();

/////////////////////////////////////////////////////////////////////////////////
// Main Thread Handler, the only method that must be implemented
	virtual	DWORD ThreadHandler();

	BOOL OnInitializeHandler();
	void OnRunHandler();

private:
	BOOL m_fMustStop;
	set<string> m_vecFiles;
};

struct CCopyData
{
	CString m_strSourcePath;
	CString m_strDestPath;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COPYDLKTHREAD_H__A4C9C0B8_CD6D_11D2_BB7E_3C8B2D1E__INCLUDED_)
