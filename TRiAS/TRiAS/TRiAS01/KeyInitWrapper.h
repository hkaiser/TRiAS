// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 07/25/1998 02:05:42 PM
//
// @doc
// @module KeyInitWrapper.h | Wrapper für key_init et.al.

#if !defined(_KEYINITWRAPPER_H__63FDD684_2330_11D2_9E9F_006008447800__INCLUDED_)
#define _KEYINITWRAPPER_H__63FDD684_2330_11D2_9E9F_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CKeyInitWrapper
{
private:
	int m_iResult; 

public:
	CKeyInitWrapper (int iKeyIndex)	
	{
		_ASSERTE(iKeyIndex >= 0 && iKeyIndex < size_kt);
		m_iResult = key_init_index (iKeyIndex); 
	}
	~CKeyInitWrapper() { key_deinit(); }

	BOOL IsValid() { return (S_OK == m_iResult) ? TRUE : FALSE; }
	int Result() { return m_iResult; }
};

#endif // !defined(_KEYINITWRAPPER_H__63FDD684_2330_11D2_9E9F_006008447800__INCLUDED_)
