// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 18.06.2001 13:23:59 
//
// @doc
// @module DBId.h | Declaration of the <c CDBId> class

#if !defined(_DBID_H__5436703D_415B_4C86_8507_BAE5C332B332__INCLUDED_)
#define _DBID_H__5436703D_415B_4C86_8507_BAE5C332B332__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

class CDBID :
	public DBID
{
public:
	enum DBIDMODE {
		DBIDMODE_Normal = 0,
		DBIDMODE_Quoted = 1,
	};

	CDBID() 
	{
		memset(this, 0, sizeof(DBID));	
	}
	CDBID(LPCSTR pcName, DBIDMODE rgMode = DBIDMODE_Normal)
	{
		memset(this, 0, sizeof(DBID));	
		if (NULL != pcName) {
			eKind = DBKIND_NAME;
			uName.pwszName = (LPOLESTR)CoTaskMemAlloc((strlen(pcName)+1) * sizeof(OLECHAR));
			if (NULL != uName.pwszName) {
				USES_CONVERSION;
				wcscpy (uName.pwszName, A2OLE(pcName));
				if (DBIDMODE_Quoted == rgMode)
					QuoteName(this);
			}
		}
	}
	CDBID(LPCOLESTR pcoleName, DBIDMODE rgMode = DBIDMODE_Normal)
	{
		memset(this, 0, sizeof(DBID));	
		if (NULL != pcoleName) {
			eKind = DBKIND_NAME;
			uName.pwszName = (LPOLESTR)CoTaskMemAlloc((wcslen(pcoleName)+1) * sizeof(OLECHAR));
			if (NULL != uName.pwszName) {
				wcscpy (uName.pwszName, pcoleName);
				if (DBIDMODE_Quoted == rgMode)
					QuoteName(this);
			}
		}
	}
	CDBID(ULONG uiPropId)
	{
		memset(this, 0, sizeof(DBID));	
		if (0 != uiPropId) {
			eKind = DBKIND_PROPID;
			uName.ulPropid = uiPropId;
		}
	}
	CDBID (const DBID &rhs, DBIDMODE rgMode = DBIDMODE_Normal)
	{
		memset(this, 0, sizeof(DBID));	
		CDBIDOps::CopyDBIDs(this, &rhs);
		if (DBIDMODE_Quoted == rgMode)
			QuoteName(this);
	}
	CDBID (const CDBID &rhs, DBIDMODE rgMode = DBIDMODE_Normal)
	{
		memset(this, 0, sizeof(DBID));	
		CDBIDOps::CopyDBIDs(this, &rhs);
		if (DBIDMODE_Quoted == rgMode)
			QuoteName(this);
	}
	~CDBID()
	{
		CDBIDOps::FreeDBIDs(this);
	}

	CDBID &operator= (const CDBID &rhs)
	{
		if (this != &rhs) {
			CDBIDOps::FreeDBIDs(this);
			CDBIDOps::CopyDBIDs(this, &rhs);
		}
		return *this;
	}
	bool operator== (const CDBID &rhs)
	{
		return (S_OK == CDBIDOps::CompareDBIDs(this, &rhs)) ? true : false;
	}

	static bool IsQuotedName (LPOLESTR pwszName)
	{
		return L'`' == pwszName[0] || L'[' == pwszName[0];
	}
	static HRESULT QuoteName (DBID *pDbId)
	{
		if (DBKIND_NAME == pDbId -> eKind || 
			DBKIND_PGUID_NAME == pDbId -> eKind ||
			DBKIND_GUID_NAME == pDbId -> eKind)
		{
			if (NULL != pDbId->uName.pwszName && !IsQuotedName (pDbId->uName.pwszName)) {
			size_t cwchBuffer = wcslen(pDbId->uName.pwszName)+3;
			LPOLESTR pwszName = (LPOLESTR)CoTaskMemAlloc(cwchBuffer * sizeof(WCHAR));

				if (NULL != pwszName) {
				OLECHAR chQuoteBegin = L'[';
				OLECHAR chQuoteEnd = L']';
				 
					if (cwchBuffer != wcscspn (pDbId->uName.pwszName, L"[]")) {
						_ASSERTE(NULL == wcschr (pDbId->uName.pwszName, L'`'));
						chQuoteBegin = chQuoteEnd = L'`';
					}

					pwszName[0] =chQuoteBegin;
					memcpy(pwszName+1, pDbId->uName.pwszName, cwchBuffer*sizeof(WCHAR));
					pwszName[cwchBuffer-2] = chQuoteEnd;
					pwszName[cwchBuffer-1] = L'\0';
					CoTaskMemFree(pDbId->uName.pwszName);
					pDbId->uName.pwszName = pwszName;
				} else
					return E_OUTOFMEMORY;
			}
		}
		return S_OK;
	}
};

#endif // !defined(_DBID_H__5436703D_415B_4C86_8507_BAE5C332B332__INCLUDED_)
