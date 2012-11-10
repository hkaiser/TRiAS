// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 09.09.2002 10:19:21 
//
// @doc
// @module InitLeadTools.h | Declaration of the <c CInitLeadTools> class

#if !defined(_INITLEADTOOLS_H__9F9BDA18_CC65_46C1_ACD7_222FE4CC1DD0__INCLUDED_)
#define _INITLEADTOOLS_H__9F9BDA18_CC65_46C1_ACD7_222FE4CC1DD0__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <ltwrappr.h>

const L_UINT32 uiLibsToLoad = LT_KRN|LT_DIS|LT_FIL;

class CLeadTools
{
public:
	CLeadTools() : m_fLoaded(false) {}
	~CLeadTools() 
	{
		UnloadAll();
	}

	void UnloadAll()
	{
		if (m_fLoaded) {
			LBase::UnloadLibraries(uiLibsToLoad);
			m_fLoaded = true;
		}
	}

	bool EnsureLoaded()
	{
	// falls DLL's fehlen, Exception abfangen
		try {
			if (!m_fLoaded) {
				LBase::LoadLibraries(uiLibsToLoad);
				LBase::EnableAutoErrorDisplay(FALSE);
				LFileSettings::PreLoadFilters(1, 1, "TIF");
                LSettings::UnlockSupport(L_SUPPORT_TIFLZW, L_KEY_TIFLZW);
				m_fLoaded = true;
			}
		} 
		catch (...) {
			return false;
		}
		return true;
	}

private:
	bool m_fLoaded;
};

#endif // !defined(_INITLEADTOOLS_H__9F9BDA18_CC65_46C1_ACD7_222FE4CC1DD0__INCLUDED_)
