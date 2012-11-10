// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 19.11.2000 13:45:16 
//
// @doc
// @module CloseCommandWrapper.h | Declaration of the <c CCloseCommandWrapper> class

#if !defined(_CLOSECOMMANDWRAPPER_H__1A159423_FE0C_4E9D_AC2B_0F09DBC1DDE1__INCLUDED_)
#define _CLOSECOMMANDWRAPPER_H__1A159423_FE0C_4E9D_AC2B_0F09DBC1DDE1__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "Objekte.hxx"

class CCloseCommandWrapper
{
public:
	CCloseCommandWrapper(ObjektInfo &rORWnd) : m_rORWnd(rORWnd)
	{
		StartCommand();
	}
	~CCloseCommandWrapper() 
	{
		ResetCommand();
	}

protected:
	void StartCommand()
	{
		++m_rORWnd.m_lCommandActive;
	}
	void ResetCommand()
	{
		if (0 == --m_rORWnd.m_lCommandActive && m_rORWnd.m_fMustDestroy) {
			m_rORWnd.m_fMustDestroy = false;
			DEX_RemoveORWnd(m_rORWnd.hWnd());	// jetzt schlieﬂen
		}
	}
	
private:
	ObjektInfo &m_rORWnd;
};

#endif // !defined(_CLOSECOMMANDWRAPPER_H__1A159423_FE0C_4E9D_AC2B_0F09DBC1DDE1__INCLUDED_)
