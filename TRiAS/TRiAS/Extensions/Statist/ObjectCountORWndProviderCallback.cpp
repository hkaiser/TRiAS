// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 16.12.2002 20:38:20 
//
// @doc
// @module ObjectCountProviderCallback.cpp | Definition of the <c CObjectCountProviderCallback> class

#include "StdAfx.h"
#include "Statist.h"
#include <triastlb.h>

#include <Com/Thunk.h>

#include "TreeListView.h"
#include "ORWndStatistics.h"
#include "ObjectCountInORWndClass.h"
#include "ObjectCountInORWnd.h"
#include "ObjectCountORWndProviderCallback.h"
#include "InstallObjectCountInORWndProvider.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// 
BOOL 
CObjectCountInORWndProviderCallback::EnumClasses(INT_PTR lIdent, 
    DWORD dwTypes, void *pData)
{
	*reinterpret_cast<short *>(pData) |= dwTypes;
	return TRUE;
}

short CObjectCountInORWndProviderCallback::GetObjectTypes()
{
// Objektklassen durchgehen
CStdThunkImpl<CObjectCountInORWndProviderCallback, ENUMNOKEYLONGPROC> 
	Thunk(this, &CObjectCountInORWndProviderCallback::EnumClasses);
ENUMNOKEYLONG ENK;
short iOTypes = 0;

	ENK.eFcn = Thunk.GetThunk();
	ENK.ePtr = reinterpret_cast<void *>(&iOTypes);

	if (DEXOR_EnumIdentsEx(m_hWnd, ENK)) 
		return iOTypes;
	return 0;
}

BOOL CObjectCountInORWndProviderCallback::PopulateItem(CORWndStatistics *pTarget, 
	HTREEITEM hParent)
{
	COM_TRY {
	short iOTypes = GetObjectTypes();

	// ValueProvider: Objektanzahl (Punkte)
		if (iOTypes & OTPunkt) {
			THROW_FAILED_HRESULT(InstallObjectCountInORWndProvider(pTarget, m_hItem, 
				m_hWnd, OBJECTTYPE_Point, IMG_STATFUNC_POINT, 0, TLVIS_NORMAL, 
				(CORWndStatistics::CValueProviderCallbackORWnd *)NULL));
		}

	// ValueProvider: Objektanzahl (Linien)
		if (iOTypes & OTLinie) {
			THROW_FAILED_HRESULT(InstallObjectCountInORWndProvider(pTarget, m_hItem, 
				m_hWnd, OBJECTTYPE_Line, IMG_STATFUNC_LINE, 0, TLVIS_NORMAL, 
				(CORWndStatistics::CValueProviderCallbackORWnd *)NULL));
		}

	// ValueProvider: Objektanzahl (Flächen)
		if (iOTypes & OTFlaeche) {
			THROW_FAILED_HRESULT(InstallObjectCountInORWndProvider(pTarget, m_hItem, 
				m_hWnd, OBJECTTYPE_Area, IMG_STATFUNC_AREA, 0, TLVIS_NORMAL, 
				(CORWndStatistics::CValueProviderCallbackORWnd *)NULL));
		}

	// ValueProvider: Objektanzahl (Texte)
		if (iOTypes & OTText) {
			THROW_FAILED_HRESULT(InstallObjectCountInORWndProvider(pTarget, m_hItem, 
				m_hWnd, OBJECTTYPE_Text, IMG_STATFUNC_TEXT, 0, TLVIS_NORMAL, 
				(CORWndStatistics::CValueProviderCallbackORWnd *)NULL));
		}

	} COM_CATCH_RETURN(FALSE);
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// 
BOOL 
CObjectCountInORWndClassProviderCallback::EnumClasses(INT_PTR lIdent, 
    DWORD dwTypes, void *pData)
{
    if (INVALID_HOBJECTS == m_lIdent || lIdent == m_lIdent)
	    *reinterpret_cast<short *>(pData) |= dwTypes;
	return TRUE;
}

short CObjectCountInORWndClassProviderCallback::GetObjectTypes()
{
// Objektklassen durchgehen
CStdThunkImpl<CObjectCountInORWndClassProviderCallback, ENUMNOKEYLONGPROC> 
	Thunk(this, &CObjectCountInORWndClassProviderCallback::EnumClasses);
ENUMNOKEYLONG ENK;
short iOTypes = 0;

	ENK.eFcn = Thunk.GetThunk();
	ENK.ePtr = reinterpret_cast<void *>(&iOTypes);

	if (DEXOR_EnumIdentsEx(m_hWnd, ENK)) 
		return iOTypes;
	return 0;
}

BOOL CObjectCountInORWndClassProviderCallback::PopulateItem(CORWndStatistics *pTarget, 
	HTREEITEM hParent)
{
	COM_TRY {
	short iOTypes = GetObjectTypes();

	// ValueProvider: Objektanzahl (Punkte)
		if (iOTypes & OTPunkt) {
			THROW_FAILED_HRESULT(InstallObjectCountInORWndClassProvider(pTarget, m_hItem, 
				m_hWnd, m_lIdent, OBJECTTYPE_Point, IMG_STATFUNC_POINT, 0, TLVIS_NORMAL, 
				(CORWndStatistics::CValueProviderCallbackORWndClass *)NULL));
		}

	// ValueProvider: Objektanzahl (Linien)
		if (iOTypes & OTLinie) {
			THROW_FAILED_HRESULT(InstallObjectCountInORWndClassProvider(pTarget, m_hItem, 
				m_hWnd, m_lIdent, OBJECTTYPE_Line, IMG_STATFUNC_LINE, 0, TLVIS_NORMAL, 
				(CORWndStatistics::CValueProviderCallbackORWndClass *)NULL));
		}

	// ValueProvider: Objektanzahl (Flächen)
		if (iOTypes & OTFlaeche) {
			THROW_FAILED_HRESULT(InstallObjectCountInORWndClassProvider(pTarget, m_hItem, 
				m_hWnd, m_lIdent, OBJECTTYPE_Area, IMG_STATFUNC_AREA, 0, TLVIS_NORMAL, 
				(CORWndStatistics::CValueProviderCallbackORWndClass *)NULL));
		}

	// ValueProvider: Objektanzahl (Texte)
		if (iOTypes & OTText) {
			THROW_FAILED_HRESULT(InstallObjectCountInORWndClassProvider(pTarget, m_hItem, 
				m_hWnd, m_lIdent, OBJECTTYPE_Text, IMG_STATFUNC_TEXT, 0, TLVIS_NORMAL, 
				(CORWndStatistics::CValueProviderCallbackORWndClass *)NULL));
		}

	} COM_CATCH_RETURN(FALSE);
	return TRUE;
}
