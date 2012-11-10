// @doc 
// @module ImageHelpDebug.h | Debughelper, um ZeilenNummern und Funktionsnamen zu finden

#if !defined(_IMAGEHELPDEBUG_H__72794DC6_BF64_11D2_95B5_006008447800__INCLUDED_)
#define _IMAGEHELPDEBUG_H__72794DC6_BF64_11D2_95B5_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <Atl/ImageHelpSymbolEngine.h>

class CPEDebug 
{
public:
	CPEDebug();
	~CPEDebug();

	bool Initialize();
	bool DumpDebugInfo (const BYTE* caller, CString &rModule, CString &rFile, CString &rFunc, int *piLineNo);

private:
	CSymbolEngine m_SymEngine;
	IMAGEHLP_SYMBOL *m_pSymbol;
	bool m_fIsInitialized;
	bool m_fTriedToInitialize;
};

#endif // !defined(_IMAGEHELPDEBUG_H__72794DC6_BF64_11D2_95B5_006008447800__INCLUDED_)
