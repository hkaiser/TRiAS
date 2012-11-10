// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 15.11.1999 21:25:31 
//
// @doc
// @module PropertyWrapper.h | Declaration of the <c CPropertyWrapper> class

#if !defined(_PROPERTYWRAPPER_H__E3730EF9_700E_4D7C_B9C8_9C95F6013FD3__INCLUDED_)
#define _PROPERTYWRAPPER_H__E3730EF9_700E_4D7C_B9C8_9C95F6013FD3__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <Com/PropertyHelper.h>

class CPropertyWrapper
{
public:
	template<class S, class T>
	CPropertyWrapper (ITRiASPropertyBase *pIPropBase, S Key, T Value, LCID lcid = LOCALE_NEUTRAL) : 
		m_PropBase(pIPropBase), m_vKey(Key)
	{
		SetPropertyBy (pIPropBase, m_vKey, Value, true, lcid);
	}
	~CPropertyWrapper()
	{
		DelPropertyBy (m_PropBase, m_vKey);
	}

private:
	__Interface<ITRiASPropertyBase> m_PropBase;
	CComVariant m_vKey;
};

#endif // !defined(_PROPERTYWRAPPER_H__E3730EF9_700E_4D7C_B9C8_9C95F6013FD3__INCLUDED_)
