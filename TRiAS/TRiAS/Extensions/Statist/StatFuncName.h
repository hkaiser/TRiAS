// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 22.02.2001 18:24:35 
//
// @doc
// @module StatFuncName.h | Declaration of the <c CStatFuncName> class

#if !defined(_STATFUNCNAME_H__BDADEBC9_0FAD_4EC9_A05D_A219122384E8__INCLUDED_)
#define _STATFUNCNAME_H__BDADEBC9_0FAD_4EC9_A05D_A219122384E8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
//
typedef enum tagSTATFUNCTYPE {
	UNKNOWN_STATFUNC_ROOT = 0,
	STATFUNC_ROOT = 1,
} STATFUNCTYPE;

class CStatFuncName 
{
private:
	STATFUNCTYPE m_rgType;
	os_string m_strGroup;
	os_string m_strSubGroup;
	os_string m_strName;
	os_string m_strFullName;

	bool m_fhasGroup;
	bool m_fhasSubGroup;
	bool m_fHasFullName;

protected:
	bool ParseName (LPCSTR pcName);

public:
	CStatFuncName (void);
	CStatFuncName (LPCSTR pcFullName);
	CStatFuncName (IGenericStatistics *pIStatFunc);
	CStatFuncName (STATFUNCTYPE rgType, LPCSTR pcGroup, LPCSTR pcSubGroup, LPCSTR pcName);
	~CStatFuncName (void) {}

	STATFUNCTYPE GetType (void) { return m_rgType; }
	os_string &GetGroup (void) { return m_strGroup; }
	os_string &GetSubGroup (void) { return m_strSubGroup; }
	os_string &GetName (void) { return m_strName; }

	bool hasGroup() { return m_fhasGroup ? true : false; }
	bool hasSubGroup() { return m_fhasSubGroup ? true : false; }

	bool GetFullName (os_string &);
	bool GetFullName (LPSTR pBuffer, WORD wLen);
	bool SetType (STATFUNCTYPE rgType);
	bool SetGroup (LPCSTR pcGroup);
	bool SetSubGroup (LPCSTR pcGroup);
	bool SetName (LPCSTR pcName);

	bool operator== (CStatFuncName &rP);

friend int Compare (CStatFuncName &rP1, CStatFuncName &rP2);
};

#endif // !defined(_STATFUNCNAME_H__BDADEBC9_0FAD_4EC9_A05D_A219122384E8__INCLUDED_)
