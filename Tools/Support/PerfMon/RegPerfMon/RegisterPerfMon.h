// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 08.09.99 15:56:07 
//
// @doc
// @module RegisterPerfMon.h | Declaration of the <c CRegisterPerfMon> class

#if !defined(_REGISTERPERFMON_H__B03E6C9D_8CFC_43A9_8F74_057F73912D76__INCLUDED_)
#define _REGISTERPERFMON_H__B03E6C9D_8CFC_43A9_8F74_057F73912D76__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

class CRegisterPerfMon 
{
protected:
	std::string m_strPathName;

public:
	CRegisterPerfMon (LPCSTR pcPathName);
	~CRegisterPerfMon (void);
		
	bool Register (bool bSilent);
	bool Unregister (bool bSilent);

	bool SupportsSelfRegister (void);

	const std::string &GetPath() const { return m_strPathName; }
};
	
#endif // !defined(_REGISTERPERFMON_H__B03E6C9D_8CFC_43A9_8F74_057F73912D76__INCLUDED_)
