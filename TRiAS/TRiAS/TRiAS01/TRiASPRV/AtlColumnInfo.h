// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 11.05.2001 14:12:35 
//
// @doc
// @module AtlColumnInfo.h | Declaration of the <c CAtlColumnInfo> class

#if !defined(_ATLCOLUMNINFO_H__90E1CC39_62EE_457B_BA22_E054C9A54B40__INCLUDED_)
#define _ATLCOLUMNINFO_H__90E1CC39_62EE_457B_BA22_E054C9A54B40__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// wrapper für ATLCOLUMNINFO
class CAtlColumnInfo :
	public ATLCOLUMNINFO
{
public:
	CAtlColumnInfo()
	{
		memset(static_cast<ATLCOLUMNINFO *>(this), '\0', sizeof(ATLCOLUMNINFO));
	}

// ctor für Bookmark Spalten
	CAtlColumnInfo(LPCOLESTR pcoleName, REFGUID rGuid, ULONG ulPropId = 2)
	{
		memset(static_cast<ATLCOLUMNINFO *>(this), '\0', sizeof(ATLCOLUMNINFO));
		pwszName = ::SysAllocString(pcoleName);

		columnid.eKind = DBKIND_GUID_PROPID;
		columnid.uGuid.guid = rGuid;
		columnid.uName.ulPropid = ulPropId;
	}

// ctor für Namens/PropId gestützte Spalten
	CAtlColumnInfo(LPCSTR pcName, BSTR bstrAsName = NULL, ULONG ulPropId = 0)
	{
		memset(static_cast<ATLCOLUMNINFO *>(this), '\0', sizeof(ATLCOLUMNINFO));
		if (NULL != bstrAsName && SysStringLen(bstrAsName) > 0)
			pwszName = ::SysAllocString(bstrAsName);
		else {
			USES_CONVERSION;
			pwszName = ::SysAllocString(A2OLE(pcName));
		}
#if defined(_USE_PROPID_FOR_COLUMNID)
		if (0 != ulPropId) {
			columnid.eKind = DBKIND_PROPID;
			columnid.uName.ulPropid = ulPropId;
		} else 
#endif // defined(_USE_PROPID_FOR_COLUMNID)
		{
			columnid.eKind = DBKIND_NAME;
			columnid.uName.pwszName = pwszName;
		}
	}
	CAtlColumnInfo(LPCOLESTR pcoleName, BSTR bstrAsName = NULL, ULONG ulPropId = 0)
	{
		memset(static_cast<ATLCOLUMNINFO *>(this), '\0', sizeof(ATLCOLUMNINFO));
		if (NULL != bstrAsName && SysStringLen(bstrAsName) > 0)
			pwszName = ::SysAllocString(bstrAsName);
		else 
			pwszName = ::SysAllocString(pcoleName);

#if defined(_USE_PROPID_FOR_COLUMNID)
		if (0 != ulPropId) {
			columnid.eKind = DBKIND_PROPID;
			columnid.uName.ulPropid = ulPropId;
		} else 
#endif // defined(_USE_PROPID_FOR_COLUMNID)
		{
			columnid.eKind = DBKIND_NAME;
			columnid.uName.pwszName = pwszName;
		}
	}
	CAtlColumnInfo(UINT uiResId, BSTR bstrAsName = NULL, ULONG ulPropId = 0)
	{
		memset(static_cast<ATLCOLUMNINFO *>(this), '\0', sizeof(ATLCOLUMNINFO));
		if (NULL != bstrAsName && SysStringLen(bstrAsName) > 0)
			pwszName = ::SysAllocString(bstrAsName);
		else {
		CComBSTR bstr;

			bstr.LoadString(uiResId);
			_ASSERTE(bstr.Length() > 0);
			pwszName = bstr.Detach();
		}

#if defined(_USE_PROPID_FOR_COLUMNID)
		if (0 != ulPropId) {
			columnid.eKind = DBKIND_PROPID;
			columnid.uName.ulPropid = ulPropId;
		} else 
#endif // defined(_USE_PROPID_FOR_COLUMNID)
		{
			columnid.eKind = DBKIND_NAME;
			columnid.uName.pwszName = pwszName;
		}
	}

// copy ctor
	CAtlColumnInfo (const CAtlColumnInfo &rhs)
	{
		*static_cast<ATLCOLUMNINFO *>(this) = rhs;			// bitwise copy
		if (NULL != rhs.pwszName) {
			pwszName = SysAllocString(rhs.pwszName);
			if (DBKIND_NAME == columnid.eKind || 
				DBKIND_GUID_NAME == columnid.eKind || 
				DBKIND_PGUID_NAME == columnid.eKind)
			{
				columnid.uName.pwszName = pwszName;
			}
		}
	}
	CAtlColumnInfo (const ATLCOLUMNINFO &rhs)
	{
		*static_cast<ATLCOLUMNINFO *>(this) = rhs;			// bitwise copy
		if (NULL != rhs.pwszName) {
			pwszName = SysAllocString(rhs.pwszName);
			if (DBKIND_NAME == columnid.eKind || 
				DBKIND_GUID_NAME == columnid.eKind || 
				DBKIND_PGUID_NAME == columnid.eKind)
			{
				columnid.uName.pwszName = pwszName;
			}
		}
	}

	CAtlColumnInfo &operator= (const CAtlColumnInfo &rhs)
	{
		if (this != &rhs) {
			*static_cast<ATLCOLUMNINFO *>(this) = rhs;		// bitwise copy
			if (NULL != rhs.pwszName) {
				pwszName = SysAllocString(rhs.pwszName);
				if (DBKIND_NAME == columnid.eKind || 
					DBKIND_GUID_NAME == columnid.eKind || 
					DBKIND_PGUID_NAME == columnid.eKind)
				{
					columnid.uName.pwszName = pwszName;
				}
			}
		}
		return *this;
	}

	~CAtlColumnInfo()
	{
		if (NULL != pwszName)
			SysFreeString(pwszName);
	}
};

#endif // !defined(_ATLCOLUMNINFO_H__90E1CC39_62EE_457B_BA22_E054C9A54B40__INCLUDED_)
