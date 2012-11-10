///////////////////////////////////////////////////////////////////////////
// @doc 
// @module OKSHeader.h | Klasse, die MCode für OKS aus Header liest.

#if !defined(_OKSHEADER_H__4356D8D3_D867_11D1_85F5_00600875138A__INCLUDED_)
#define _OKSHEADER_H__4356D8D3_D867_11D1_85F5_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <HeaderEntry.h>

class _TRIAS01_ENTRY COKSHeader
{
private:
	HPROJECT m_hPr;

public:
	COKSHeader(HPROJECT hPr);
	long GetOKSMCode();	
};

#endif // !defined(_OKSHEADER_H__4356D8D3_D867_11D1_85F5_00600875138A__INCLUDED_)
