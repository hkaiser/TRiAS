///////////////////////////////////////////////////////////////////////////
// @doc 
// @module PBDData.h | Description goes here

#if !defined(_PBDDATA_H__550665C3_D481_11D1_85EC_00600875138A__INCLUDED_)
#define _PBDDATA_H__550665C3_D481_11D1_85EC_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <NativePbd.h>

///////////////////////////////////////////////////////////////////////////////
// Substitution for PBD_Data et.al.

class CPbdIdent
{
private:
	os_string m_strKText;
	os_string m_strLText;

public:
	CPbdIdent (HPROJECT hPr, long lIdent)
	{
	PBDDATA Data;
	char cbKText[_MAX_PATH] = { '\0' };
	char cbLText[_MAX_PATH] = { '\0' };

		INITSTRUCT(Data, PBDDATA);
		Data.pbdTyp = 'i';
		Data.pbdCode = lIdent;
		Data.pbdKText = cbKText;
		Data.pbdKTextLen = sizeof(cbKText);
		Data.pbdLText = cbLText;
		Data.pbdLTextLen = sizeof(cbLText);

		if (EC_OKAY == DEX_GetPBDDataEx (hPr, Data)) {
			m_strKText = Data.pbdKText;
			m_strLText = Data.pbdLText;
		}
	}

	char *GetKurzText() { return (LPSTR)m_strKText.c_str(); }
	char *GetLangText() { return (LPSTR)m_strLText.c_str(); }
};

#endif // !defined(_PBDDATA_H__550665C3_D481_11D1_85EC_00600875138A__INCLUDED_)
