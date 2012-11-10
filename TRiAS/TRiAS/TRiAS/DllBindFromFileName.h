// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 25.06.99 08:57:23 
//
// @doc
// @module DllBindFromFileName.h | Declaration of the <c CDllBindFromFileName> class

#if !defined(_DLLBINDFROMFILENAME_H__34F56970_2ACB_11D3_94F6_0080C786297B__INCLUDED_)
#define _DLLBINDFROMFILENAME_H__34F56970_2ACB_11D3_94F6_0080C786297B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <ospace/file/path.h>
#include <DLLBind.hxx>

class CDLLBindFromFileName 
{
public:
	CDLLBindFromFileName (HINSTANCE hInst, LPCSTR pcFileName) :
		m_strPath(""), m_pDLL(NULL)
	{
		GenerateFullName (hInst, pcFileName);
		TX_TRY (m_pDLL = new DLLBind(m_strPath.c_str()));
	}
	~CDLLBindFromFileName()
	{
		DELETE_OBJ(m_pDLL);
	}

	LPCSTR GenerateFullName (HINSTANCE hInst, LPCSTR pcFileName)
	{
	char szModule[_MAX_PATH];

		GetModuleFileName (hInst, szModule, _MAX_PATH);

	os_path path (szModule);

		path.filename (pcFileName);

	// #HK990620 work around WinNT4 LoadProcess bug
	char szModuleShort[_MAX_PATH];
	os_string strName = os_string(path).c_str();
	int cbShortName = GetShortPathName (strName.c_str(), szModuleShort, _MAX_PATH);

		if (cbShortName == _MAX_PATH)
			return m_strPath.c_str();
		m_strPath = (cbShortName == 0 || cbShortName == ERROR_INVALID_PARAMETER) ? strName.c_str() : szModuleShort;
		return m_strPath.c_str();
	}

private:
	os_string m_strPath;
	DLLBind *m_pDLL;
};

#endif // !defined(_DLLBINDFROMFILENAME_H__34F56970_2ACB_11D3_94F6_0080C786297B__INCLUDED_)
