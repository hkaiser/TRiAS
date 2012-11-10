// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 15.06.99 13:04:08 
//
// @doc
// @module MenuCommands.h | Declaration of the <c CMenuCommands> class

#if !defined(_MENUCOMMANDS_H__0553DC20_2312_11D3_94F0_0080C786297B__INCLUDED_)
#define _MENUCOMMANDS_H__0553DC20_2312_11D3_94F0_0080C786297B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "oleautor.h"

class CMenuCommands 
{
public:
	CMenuCommands() : 
		m_hPrAct(HACTCONNECTION), m_fIsValid(false), m_uiCmdID(10), m_uiMenuOffset(0) 
	{}

	void ReInit (HPROJECT hPr = HACTCONNECTION)
	{
		m_hPrAct = hPr;
		m_fIsValid = true;
		m_uiCmdID = 10;
	}
	void Invalidate()
	{
		m_fIsValid = false;
		m_hPrAct = HACTCONNECTION;
		m_Cmds.erase();
	}
	bool IsValid() { return m_fIsValid; }
	void SetMenuOffset (UINT uiMenuOffset) { m_uiMenuOffset = uiMenuOffset; }
	UINT GetMenuOffset() { return m_uiMenuOffset; }

// Klasse, die einen Menueintrag repräsentiert
	class CMenuCommand
	{
	public:
		CMenuCommand (HPROJECT hPr, BOOL fShowOR, DWORD dwEffect) :
			m_hPr(hPr), m_fShowORWnd(fShowOR), m_dwEffect(dwEffect)
		{}

		HPROJECT GetHandle() { return m_hPr; }
		DWORD GetEffect() { return m_dwEffect; }
		BOOL GetShowORWnd() { return m_fShowORWnd; }

	private:
		HPROJECT m_hPr;
		BOOL m_fShowORWnd;
		DWORD m_dwEffect;
	};
	typedef map<UINT, CMenuCommand, less<UINT> > CCmdIDs;

// Zugriffsfunktionen
	DWORD AnalyzeCommand (UINT uiCmd, HPROJECT *phPr, BOOL *pfShowORWnd)
	{
		ASSERT(NULL != phPr && NULL != pfShowORWnd);
		ASSERT(IsValid());

	DWORD dwEffect = DROPEFFECT_NONE;

		*pfShowORWnd = FALSE;
		*phPr = m_hPrAct;

		uiCmd -= GetMenuOffset();
		switch(uiCmd) {
		case ID_DRAGDROPPOPUP_COPY:
			dwEffect = DROPEFFECT_COPY;
			break;

		case ID_DRAGDROPPOPUP_MOVE:
			dwEffect = DROPEFFECT_MOVE;
			break;

		case ID_DRAGDROPPOPUP_COPYWITHORWINDOW:
			dwEffect = DROPEFFECT_COPY;
			*pfShowORWnd = TRUE;
			break;

		case ID_DRAGDROPPOPUP_MOVEWITHORWINDOW:
			dwEffect = DROPEFFECT_MOVE;
			*pfShowORWnd = TRUE;
			break;

		case ID_DRAGDROPPOPUP_CANCEL:
			break;

		default:
			dwEffect = FindCommand (uiCmd, phPr, pfShowORWnd);
			break;
		}
		return dwEffect;
	}
	BOOL AddCommand (HPROJECT hPr, UINT uiCmd, BOOL fShowORWnd, DWORD dwEffect)
	{
		ASSERT(IsValid());

	pair<CCmdIDs::iterator, bool> p = m_Cmds.insert (CCmdIDs::value_type(uiCmd, CMenuCommand(hPr, fShowORWnd, dwEffect)));

		return p.second;
	}
	DWORD FindCommand (UINT uiCmd, HPROJECT *phPr, BOOL *pfShowORWnd)
	{
		ASSERT(IsValid());

	CCmdIDs::iterator it = m_Cmds.find (uiCmd);

		if (it == m_Cmds.end())
			return DROPEFFECT_NONE;

		*phPr = (*it).second.GetHandle();
		*pfShowORWnd = (*it).second.GetShowORWnd(); 
		return (*it).second.GetEffect();
	}
	UINT GetNextCmdID() { return ++m_uiCmdID; }
	HPROJECT GetDataSourceHandle() { return m_hPrAct; }

private:
	CCmdIDs m_Cmds;
	UINT m_uiCmdID;
	UINT m_uiMenuOffset;
	HPROJECT m_hPrAct;
	bool m_fIsValid;
};

///////////////////////////////////////////////////////////////////////////////
// Wrapper zur korrekten kontextbezogenen Initialisierung der MenuItems
class CMenuCommandWrapper
{
public:
	CMenuCommandWrapper (CMenuCommands &rCmds, HPROJECT hPr = HACTCONNECTION) :
		m_rCmds(rCmds)
	{
		m_rCmds.ReInit(hPr);
	}
	~CMenuCommandWrapper()
	{
		m_rCmds.Invalidate();
	}

private:
	CMenuCommands &m_rCmds;
};


#endif // !defined(_MENUCOMMANDS_H__0553DC20_2312_11D3_94F0_0080C786297B__INCLUDED_)
