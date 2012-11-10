// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 6/25/2001 8:48:23 AM 
//
// @doc
// @module SessionRowsetImpl.h | Declaration of the <c CSessionRowsetImpl> class

#if !defined(_SESSIONROWSETIMPL_H__441CD7EA_6348_4327_896C_DE4E67FE606C__INCLUDED_)
#define _SESSIONROWSETIMPL_H__441CD7EA_6348_4327_896C_DE4E67FE606C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#if _ATL_VER < 0x0700		// die neue ATL hat eine eigene Klasse

///////////////////////////////////////////////////////////////////////////////
// Identisch zu CRowsetImpl<>, nur daﬂ die properties vom ersten template-
// Parameter verwendet werden, nicht die vom dritten
template <class T, class Storage, class CreatorClass,
	class ArrayType = CSimpleArray<Storage>,
	class RowClass = CSimpleRow,
	class RowsetInterface = IRowsetImpl<T, IRowset, RowClass> >
class ATL_NO_VTABLE CSchemaRowsetImpl :
	public CComObjectRootEx<CreatorClass::_ThreadModel>,
	public IAccessorImpl<T>,
	public IRowsetIdentityImpl<T, RowClass>,
	public IRowsetCreatorImpl<T>,
	public IRowsetInfoImpl<T>,
	public IColumnsInfoImpl<T>,
	public IConvertTypeImpl<T>,
	public RowsetInterface
{
public:
	typedef CreatorClass _RowsetCreatorClass;
	typedef ArrayType _RowsetArrayType;
	typedef CSchemaRowsetImpl<T, Storage, CreatorClass, ArrayType, RowClass, RowsetInterface> _RowsetBaseClass;
	
	BEGIN_COM_MAP(CSchemaRowsetImpl)
		COM_INTERFACE_ENTRY(IAccessor)
		COM_INTERFACE_ENTRY(IObjectWithSite)
		COM_INTERFACE_ENTRY(IRowsetInfo)
		COM_INTERFACE_ENTRY(IColumnsInfo)
		COM_INTERFACE_ENTRY(IConvertType)
		COM_INTERFACE_ENTRY(IRowsetIdentity)
		COM_INTERFACE_ENTRY(IRowset)
	END_COM_MAP()
		
	HRESULT FinalConstruct()
	{
		HRESULT hr = IAccessorImpl<T>::FinalConstruct();
		if (FAILED(hr))
			return hr;
		return CConvertHelper::FinalConstruct();
	}
	
	HRESULT NameFromDBID(DBID* pDBID, CComBSTR& bstr, bool bIndex)
	{
		
		if (pDBID->uName.pwszName != NULL)
		{
			bstr = pDBID->uName.pwszName;
			if (m_strCommandText == (BSTR)NULL)
				return E_OUTOFMEMORY;
			return S_OK;
		}
		
		return (bIndex) ? DB_E_NOINDEX : DB_E_NOTABLE;
	}
	
	HRESULT GetCommandFromID(DBID* pTableID, DBID* pIndexID)
	{
		USES_CONVERSION;
		HRESULT hr;
		
		if (pTableID == NULL && pIndexID == NULL)
			return E_INVALIDARG;
		
		if (pTableID != NULL && pTableID->eKind == DBKIND_NAME)
		{
			hr = NameFromDBID(pTableID, m_strCommandText, true);
			if (FAILED(hr))
				return hr;
			if (pIndexID != NULL)
			{
				if (pIndexID->eKind == DBKIND_NAME)
				{
					hr = NameFromDBID(pIndexID, m_strIndexText, false);
					if (FAILED(hr))
					{
						m_strCommandText.Empty();
						return hr;
					}
				}
				else
				{
					m_strCommandText.Empty();
					return DB_E_NOINDEX;
				}
			}
			return S_OK;
		}
		if (pIndexID != NULL && pIndexID->eKind == DBKIND_NAME)
			return NameFromDBID(pIndexID, m_strIndexText, false);
		
		return S_OK;
	}
	
	HRESULT ValidateCommandID(DBID* pTableID, DBID* pIndexID)
	{
		HRESULT hr = S_OK;
		
		if (pTableID != NULL)
		{
			hr = CUtlProps<T>::IsValidDBID(pTableID);
			if (hr != S_OK)
				return hr;
			
		// Check for a NULL TABLE ID (where its a valid pointer but NULL)
			if ((pTableID->eKind == DBKIND_GUID_NAME ||
				pTableID->eKind == DBKIND_NAME ||
				pTableID->eKind == DBKIND_PGUID_NAME)
				&& pTableID->uName.pwszName == NULL)
				return DB_E_NOTABLE;
		}
		
		if (pIndexID != NULL)
			hr = CUtlProps<T>::IsValidDBID(pIndexID);
		
		return hr;
	}
	
	HRESULT SetCommandText(DBID* pTableID, DBID* pIndexID)
	{
		T* pT = (T*)this;
		HRESULT hr = pT->ValidateCommandID(pTableID, pIndexID);
		if (FAILED(hr))
			return hr;
		hr = pT->GetCommandFromID(pTableID, pIndexID);
		return hr;
	}
	void FinalRelease()
	{
		m_rgRowData.RemoveAll();
	}

	static ATLCOLUMNINFO* GetColumnInfo(T* pv, ULONG* pcCols)
	{
		return Storage::GetColumnInfo(pv,pcCols);
	}

	CComBSTR m_strCommandText;
	CComBSTR m_strIndexText;
	ArrayType m_rgRowData;
};

#endif // _ATL_VER < 0x0700

#endif // !defined(_SESSIONROWSETIMPL_H__441CD7EA_6348_4327_896C_DE4E67FE606C__INCLUDED_)
