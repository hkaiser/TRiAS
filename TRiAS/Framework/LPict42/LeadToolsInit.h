// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 25.11.2004 19:14:07 
//
// @doc
// @module LeadToolsInit.h | Definition of the <c CLeadToolsInit> class

#if !defined(LEADTOOLSINIT_H_HK041125)
#define LEADTOOLSINIT_H_HK041125

const L_UINT32 uiLibsToLoad = LT_KRN|LT_DIS|LT_FIL|LT_IMG|LT_EFX;

class CLeadToolsInit
{
public:
	CLeadToolsInit() : m_fLoaded(false) {}
	~CLeadToolsInit() 
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

	bool EnsureLoaded(CPictException *e = NULL)
	{
	// falls DLL's fehlen, Exception abfangen
		try {
			if (!m_fLoaded) {
				LBase::LoadLibraries(uiLibsToLoad);
				LBase::EnableAutoErrorDisplay(FALSE);
				LFileSettings::PreLoadFilters(1, 2, "TIF,BMP,CMP");
                LSettings::UnlockSupport(L_SUPPORT_TIFLZW, L_KEY_TIFLZW);
				m_fLoaded = true;
			}
		} catch (...) {
			if (NULL != e) 
				e->m_cause = CPictException::errLTInitFailure;
			return false;
		}
		return true;
	}

private:
	bool m_fLoaded;
};

extern CLeadToolsInit g_LeadTools;

#endif // defined(LEADTOOLSINIT_H_HK041125)
