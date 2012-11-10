// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 12/27/1998 09:46:40 PM
//
// @doc
// @module Main.h | Description goes here

#if !defined(_MAIN_H__4674529D_9CBA_11D2_9F09_006008447800__INCLUDED_)
#define _MAIN_H__4674529D_9CBA_11D2_9F09_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <Com/PerfMonContext.h>

using namespace PerfMon;

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
__Interface<PerfMon::IPerfContext>;

/////////////////////////////////////////////////////////////////////////////
// Application
class CTestPerfMon
{
public:
	CTestPerfMon() : m_fInitialized(false) {}
	~CTestPerfMon() 
	{
		m_PerfContext.Assign(NULL);
	}

	HRESULT InitApplication(PERFMONSTARTMODE rgMode);
	HRESULT Start (void);
	void ExitApplication();

private:
	__Interface<PerfMon::IPerfContext> m_PerfContext;
	bool m_fInitialized;
};

#endif // !defined(_MAIN_H__4674529D_9CBA_11D2_9F09_006008447800__INCLUDED_)
