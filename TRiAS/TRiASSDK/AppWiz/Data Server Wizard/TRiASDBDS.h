// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 11.01.2000 23:48:55 
//
// @doc
// @module TRiASDBDS.h | Declaration of the <c CTRiASDBDS> class

#if !defined(AFX_TRIASDBDS_H__1724BBE1_E51D_11D2_9BD8_E6AA20524153__INCLUDED_)
#define AFX_TRIASDBDS_H__1724BBE1_E51D_11D2_9BD8_E6AA20524153__INCLUDED_

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// Miscellaneous utility functions

void DefineMacro(LPCTSTR lpszKey, LPCTSTR lpszValue);
void UndefMacro(LPCTSTR lpszKey);

void DefineIntMacro(LPCTSTR pszKey, int iValue);
void DefineIntMacro(LPCTSTR pszKey, int iItem, int iValue);
void DefineBoolMacro(LPCTSTR pszKey, BOOL bValue);
void DefineBoolMacro(LPCTSTR pszKey, int iItem, BOOL bValue);
void DefineStringMacro(LPCTSTR pszKey, LPCTSTR pszValue);
void DefineStringMacro(LPCTSTR pszKey, int iItem, LPCTSTR pszValue);

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRIASDBDS_H__1724BBE1_E51D_11D2_9BD8_E6AA20524153__INCLUDED_)
