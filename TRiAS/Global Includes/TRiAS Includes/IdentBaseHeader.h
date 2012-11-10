///////////////////////////////////////////////////////////////////////////
// @doc 
// @module IdentBaseHeader.h | Identifikator-Zahlenbasis aus Header lesen

#if !defined(_IDENTBASEHEADER_H__4356D8D5_D867_11D1_85F5_00600875138A__INCLUDED_)
#define _IDENTBASEHEADER_H__4356D8D5_D867_11D1_85F5_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <HeaderEntry.h>

class _TRIAS01_ENTRY CIdentBaseHeader
{
private:
	HPROJECT m_hPr;

public:
	CIdentBaseHeader (HPROJECT hPr);
	int GetIdentBase();
};

#endif // !defined(_IDENTBASEHEADER_H__4356D8D5_D867_11D1_85F5_00600875138A__INCLUDED_)
