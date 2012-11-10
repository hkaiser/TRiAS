// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 12.05.2002 21:49:58 
//
// @doc
// @module SummaryProp.h | Declaration of the <c CSummaryProp> class

#if !defined(_SUMMARYPROP_H__86B0D7A2_3F39_4EC1_A75D_6020902C0AEA__INCLUDED_)
#define _SUMMARYPROP_H__86B0D7A2_3F39_4EC1_A75D_6020902C0AEA__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <Com/PropVariant.h>

///////////////////////////////////////////////////////////////////////////////
// spezielles PropVariant für SummaryInfo
class CSummaryProp :
	public CPropVariant
{
public:
	CSummaryProp(ULONG ulPropId, LPCSTR pcValue) :
		m_ulPropId(ulPropId)
	{
		vt = VT_LPSTR;
		pcVal = NULL;
		if (NULL != pcValue) {
			pcVal = (char *)CoTaskMemAlloc(strlen(pcValue)+1);
			if (NULL != pcVal)
				strcpy(pcVal, pcValue);
		}
	}
	CSummaryProp(ULONG ulPropId, PROPVARIANT const &varSrc) :
		CPropVariant(varSrc), m_ulPropId(ulPropId)
	{
	}
	CSummaryProp(ULONG ulPropId, VARIANT const &varSrc) :
		CPropVariant(varSrc), m_ulPropId(ulPropId)
	{
	}
	HRESULT WriteToPropertyStorage(IPropertyStorage *pIProps)
	{
		return CPropVariant::WriteToPropertyStorage(pIProps, NULL, m_ulPropId);
	}

private:
	ULONG m_ulPropId;
};

#endif // !defined(_SUMMARYPROP_H__86B0D7A2_3F39_4EC1_A75D_6020902C0AEA__INCLUDED_)
