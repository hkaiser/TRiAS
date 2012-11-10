// @doc 
// @module MemDiffExt.h | Declaration of the <c CMemDiffExtExtension> class

#if !defined(_MEMDIFFEXT_H__AC1E7ED0_D127_4D47_A9FA_0ECC0D66EF81__INCLUDED_)
#define _MEMDIFFEXT_H__AC1E7ED0_D127_4D47_A9FA_0ECC0D66EF81__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <Com/Thunk.h>

#include "resource.h"       // main symbols
#include "Mem/MemDiff.h"

/////////////////////////////////////////////////////////////////////////////
// CMemDiffExtExtension
class ATL_NO_VTABLE CMemDiffExtExtension : 
	public CComCoClass<CMemDiffExtExtension, &CLSID_MemDiffExt>,
	public CTriasExtension 
{
public:
	typedef CStdThunk<CMemDiffExtExtension>::TMFP TMFP;

	CMemDiffExtExtension() :
		m_hSnapShot1(false), m_hSnapShot2(false), m_fVerbose(true),
		m_pStartMenu(NULL), m_pPopupMenu(NULL)
	{
		m_Thunk.InitThunk((TMFP)OutputLine, this);
	}
	~CMemDiffExtExtension() 
	{
		DELETE_OBJ(m_pStartMenu);
		DELETE_OBJ(m_pPopupMenu);
	}

	DECLARE_NO_REGISTRY()
	DECLARE_NOT_AGGREGATABLE_SINGLE(CMemDiffExtExtension, g_pTE)

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CMemDiffExtExtension)
		COM_INTERFACE_ENTRY(IUnknown)
		COM_INTERFACE_ENTRY_CHAIN(CTriasExtension)
	END_COM_MAP()

// ITriasXtension
public:
	STDMETHOD_(BOOL, InitExtension) (short iMode);
	STDMETHOD_(BOOL, UnLoadExtension) (void);
	STDMETHOD_(BOOL, MenuInit) (THIS_ HMENU hMenu, LPARAM lParam, HWND hWnd);
	STDMETHOD_(BOOL, MenuSelect) (THIS_ UINT uiMenuID, HMENU hMenu, HWND hWnd);
	STDMETHOD_(BOOL, MenuCommand) (THIS_ UINT uiMenuID, HWND hWnd);

protected:
	bool FindMenuItem (CMenu *pMenu, UINT uiID);
	void CompareSnapShots ();
	BOOL __stdcall OutputLine (LPCSTR pcOutStr, size_t uiLen);
	MDOUTPUTPROC GetOutputProc() { return (MDOUTPUTPROC)m_Thunk.GetThunk(); }

	BOOL InstallPopupMenu(UINT uiWhere, CMenu *& pPopupMenu);
	void RemovePopupMenu (UINT uiWhere);

private:
	HANDLE m_hSnapShot1;
	HANDLE m_hSnapShot2;
	bool m_fVerbose;

	CMenu *m_pStartMenu;
	CMenu *m_pPopupMenu;

	CStdThunk<CMemDiffExtExtension> m_Thunk;
};

#endif // !defined(_MEMDIFFEXT_H__AC1E7ED0_D127_4D47_A9FA_0ECC0D66EF81__INCLUDED_)
