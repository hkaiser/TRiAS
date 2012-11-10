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
#include "ObjectClassStatistics.h"
#include "ObjectCountInClass.h"
#include "ObjectCountInDatasource.h"
#include "ObjectCountProviderCallback.h"
#include "InstallObjectCountProvider.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// 
BOOL CObjectCountInDatasourceProviderCallback::EnumClasses(INT_PTR lIdent, BOOL, void *pData)
{
	*reinterpret_cast<short *>(pData) |= DEX_GetIdentObjTypes(lIdent);
	return TRUE;
}

short CObjectCountInDatasourceProviderCallback::GetObjectTypes()
{
// Objektklassen durchgehen
CStdThunkImpl<CObjectCountInDatasourceProviderCallback, ENUMNOKEYPROC> 
	Thunk(this, &CObjectCountInDatasourceProviderCallback::EnumClasses);
ENUMNOKEY ENK;
short iOTypes = 0;

	ENK.eFcn = Thunk.GetThunk();
	ENK.ePtr = reinterpret_cast<void *>(&iOTypes);

	if (DEX_EnumClasses(m_hPr, ENK)) 
		return iOTypes;
	return 0;
}

BOOL CObjectCountInDatasourceProviderCallback::PopulateItem(CObjectClassStatistics *pTarget, 
	HTREEITEM hParent)
{
	COM_TRY {
	short iOTypes = GetObjectTypes();

	// ValueProvider: Objektanzahl (Punkte)
		if (iOTypes & OTPunkt) {
			THROW_FAILED_HRESULT(InstallObjectCountInDatasourceProvider(pTarget, m_hItem, 
				m_hPr, OBJECTTYPE_Point, IMG_STATFUNC_POINT, 0, TLVIS_NORMAL, 
				(CObjectClassStatistics::CValueProviderCallbackDatasource *)NULL));
		}

	// ValueProvider: Objektanzahl (Linien)
		if (iOTypes & OTLinie) {
			THROW_FAILED_HRESULT(InstallObjectCountInDatasourceProvider(pTarget, m_hItem, 
				m_hPr, OBJECTTYPE_Line, IMG_STATFUNC_LINE, 0, TLVIS_NORMAL, 
				(CObjectClassStatistics::CValueProviderCallbackDatasource *)NULL));
		}

	// ValueProvider: Objektanzahl (Flächen)
		if (iOTypes & OTFlaeche) {
			THROW_FAILED_HRESULT(InstallObjectCountInDatasourceProvider(pTarget, m_hItem, 
				m_hPr, OBJECTTYPE_Area, IMG_STATFUNC_AREA, 0, TLVIS_NORMAL, 
				(CObjectClassStatistics::CValueProviderCallbackDatasource *)NULL));
		}

	// ValueProvider: Objektanzahl (Texte)
		if (iOTypes & OTText) {
			THROW_FAILED_HRESULT(InstallObjectCountInDatasourceProvider(pTarget, m_hItem, 
				m_hPr, OBJECTTYPE_Text, IMG_STATFUNC_TEXT, 0, TLVIS_NORMAL, 
				(CObjectClassStatistics::CValueProviderCallbackDatasource *)NULL));
		}

	} COM_CATCH_RETURN(FALSE);
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// 
BOOL CObjectCountInClassProviderCallback::PopulateItem(CObjectClassStatistics *pTarget, 
	HTREEITEM hParent)
{
	COM_TRY {
	short iOTypes = DEX_GetIdentObjTypes(m_lIdent);

	// ValueProvider: Objektanzahl (Punkte)
		if (iOTypes & OTPunkt) {
			THROW_FAILED_HRESULT(InstallObjectCountInClassProvider(pTarget, m_hItem, 
				m_lIdent, OBJECTTYPE_Point, IMG_STATFUNC_POINT, 0, TLVIS_NORMAL, 
				(CObjectClassStatistics::CValueProviderCallbackClass *)NULL));
		}

	// ValueProvider: Objektanzahl (Linien)
		if (iOTypes & OTLinie) {
			THROW_FAILED_HRESULT(InstallObjectCountInClassProvider(pTarget, m_hItem, 
				m_lIdent, OBJECTTYPE_Line, IMG_STATFUNC_LINE, 0, TLVIS_NORMAL, 
				(CObjectClassStatistics::CValueProviderCallbackClass *)NULL));
		}

	// ValueProvider: Objektanzahl (Flächen)
		if (iOTypes & OTFlaeche) {
			THROW_FAILED_HRESULT(InstallObjectCountInClassProvider(pTarget, m_hItem, 
				m_lIdent, OBJECTTYPE_Area, IMG_STATFUNC_AREA, 0, TLVIS_NORMAL, 
				(CObjectClassStatistics::CValueProviderCallbackClass *)NULL));
		}

	// ValueProvider: Objektanzahl (Texte)
		if (iOTypes & OTText) {
			THROW_FAILED_HRESULT(InstallObjectCountInClassProvider(pTarget, m_hItem, 
				m_lIdent, OBJECTTYPE_Text, IMG_STATFUNC_TEXT, 0, TLVIS_NORMAL, 
				(CObjectClassStatistics::CValueProviderCallbackClass *)NULL));
		}

	} COM_CATCH_RETURN(FALSE);
	return TRUE;
}
