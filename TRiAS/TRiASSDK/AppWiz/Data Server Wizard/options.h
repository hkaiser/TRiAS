// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 11.01.2000 23:49:35 
//
// @doc
// @module options.h | Declaration of the <c COptions> class

#if !defined(_OPTIONS_H__4A530923_00BC_475C_897A_D50DF397A68A__INCLUDED_)
#define _OPTIONS_H__4A530923_00BC_475C_897A_D50DF397A68A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

class COptions
{
public:
	COptions();

	CString m_Name;			// DataServerName
	int m_AccessMode;
	int m_AccessType;
	CString m_FileExt;
	BOOL m_fEmitSampleCode;

	void DefineDlgMacros();
};

extern COptions g_Options;

#define ACCESSMODE_READONLY		0
#define ACCESSMODE_READWRITE	1

#define ACCESSTYPE_FILE			0
#define ACCESSTYPE_DIRECTORY	1
#define ACCESSMODE_NOFILENODIR	2

#endif // !defined(_OPTIONS_H__4A530923_00BC_475C_897A_D50DF397A68A__INCLUDED_)
