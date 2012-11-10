// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 12/30/1998 09:21:58 PM
//
// @doc
// @module LockMutex.h | Helperklasse, um einen Mutex zu verwalten

#if !defined(_LOCKMUTEX_H__467452AA_9CBA_11D2_9F09_006008447800__INCLUDED_)
#define _LOCKMUTEX_H__467452AA_9CBA_11D2_9F09_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#define SHARED_MEMORY_MUTEX_TIMEOUT ((DWORD)1000L)

class CLockMemMutex
{
public:
	CLockMemMutex (IPerfContextHelper *pICtx, DWORD dwTimeOut = SHARED_MEMORY_MUTEX_TIMEOUT) 
		: m_lStatus(ERROR_SUCCESS), m_Ctx(pICtx)
	{
		m_lStatus = pICtx -> LockMemory (dwTimeOut);
	}
	~CLockMemMutex()
	{
		if (S_OK == m_lStatus)
			 m_Ctx -> UnlockMemory();
	}

	HRESULT Status() { return m_lStatus; }
	bool operator! () { return S_OK != m_lStatus ? true : false; }
	operator bool () { return S_OK == m_lStatus ? true : false;; }

private:
	HANDLE m_hMtx;
	HRESULT m_lStatus;
	WPerfContextHelper m_Ctx;
};

#endif // !defined(_LOCKMUTEX_H__467452AA_9CBA_11D2_9F09_006008447800__INCLUDED_)
