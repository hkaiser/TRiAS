// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 18.09.2000 15:50:38 
//
// @doc
// @module CrtMemDebug.h | Declaration of the <c CCrtMemDebug> class

#if !defined(_CRTMEMDEBUG_H__BF199793_1789_4D6C_AD11_E194E27EEF1C__INCLUDED_)
#define _CRTMEMDEBUG_H__BF199793_1789_4D6C_AD11_E194E27EEF1C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#if defined(_DEBUG)
#include <crtdbg.h>

///////////////////////////////////////////////////////////////////////////////
// Verwaltung der MemDbgFlags
class CCrtMemDebug
{
public:
	CCrtMemDebug(int iFlags) 
	{
		m_iOldFlags = _crtDbgFlag;
		_CrtSetDbgFlag(iFlags);
	}
	~CCrtMemDebug() 
	{
		_CrtSetDbgFlag(m_iOldFlags);
	}

private:
	int m_iOldFlags;
};

#else

class CCrtMemDebug
{
public:
	CCrtMemDebug(int) {}
	~CCrtMemDebug() {}
};

#endif // defined(_DEBUG)

#endif // !defined(_CRTMEMDEBUG_H__BF199793_1789_4D6C_AD11_E194E27EEF1C__INCLUDED_)
