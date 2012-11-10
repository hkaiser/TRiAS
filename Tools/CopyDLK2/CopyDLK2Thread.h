// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 22.11.2002 14:17:35 
//
// @doc
// @module CopyDLK2Thread.h | Declaration of the <c CCopyDLK2Thread> class

/////////////////////////////////////////////////////////////////////////////////////
// WORKER THREAD DERIVED CLASS - produced by Worker Thread Class Generator Rel 1.0
// CopyDLK2Thread.h: Interface for the CCopyDLK2Thread Class.
/////////////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_COPYDLK2THREAD_H__A4C9C0B8_CD6D_11D2_BB7E_3DDE2E3F__INCLUDED_)
#define AFX_COPYDLK2THREAD_H__A4C9C0B8_CD6D_11D2_BB7E_3DDE2E3F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <ospace/std/set>

#include "Thread.h"
#include "CopyErrorList.h"

///////////////////////////////////////////////////////////////////////////////
// Daten, die dem Thread sagen, wo es lang geht
struct CCopyData
{
	CString m_strSourcePath;
	CString m_strDestPath;
	std::set<std::string> m_setFilesToCopy;
	CCopyErrorList m_Errors;
};

///////////////////////////////////////////////////////////////////////////////
// Der Thread selbst
class CCopyDLK2Thread : public CThread  
{
public:
	DECLARE_DYNAMIC(CCopyDLK2Thread)

// Construction & Destruction
	CCopyDLK2Thread(void* pOwnerObject = NULL, LPARAM lParam = 0L);
	virtual ~CCopyDLK2Thread();

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
	// Main Thread Handler
	// The only method that must be implemented
	virtual	DWORD ThreadHandler();
	/////////////////////////////////////////////////////////////////////////////////

	BOOL OnInitializeHandler();
	void OnRunHandler();

private:
	BOOL m_fMustStop;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COPYDLK2THREAD_H__A4C9C0B8_CD6D_11D2_BB7E_3DDE2E3F__INCLUDED_)
