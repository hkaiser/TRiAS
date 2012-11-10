// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 05.10.1999 12:17:58 
//
// @doc
// @module ComTSTR.h | Declaration of the <c CComTSTR> class

#if !defined(_COMTSTR_H__03C34CA2_9059_4F39_AF7E_716C63969DF4__INCLUDED_)
#define _COMTSTR_H__03C34CA2_9059_4F39_AF7E_716C63969DF4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

class CComTSTR
{
public:
	TCHAR* m_str;

	CComTSTR() { m_str = 0; }

	~CComTSTR()	{ if (m_str) delete [] m_str; }

	CComTSTR(const OLECHAR* wsz)
	{
		m_str = 0;
		(*this) = wsz; // fwd to operator=
	}

	CComTSTR& operator=(const OLECHAR* wsz)
	{
		if (m_str) delete [] m_str;

	// Always allow enough space for 16-bit chars (ala MBCS)
		m_str = new TCHAR[(lstrlenW(wsz) +1) * ((sizeof(TCHAR)==2) ?  1  : 2 )];

#if defined(_UNICODE) || defined(UNICODE)
		lstrcpyW(m_str, wsz);
#else
		AtlW2AHelper(m_str, wsz, (lstrlenW(wsz)+1)*2);
#endif
		return (*this);
	}

	operator TCHAR*() const
	{
		return m_str;
	}

	unsigned int Length() const
	{
		return (m_str == 0) ? (0) : (lstrlen(m_str));
	}
};

#endif // !defined(_COMTSTR_H__03C34CA2_9059_4F39_AF7E_716C63969DF4__INCLUDED_)
