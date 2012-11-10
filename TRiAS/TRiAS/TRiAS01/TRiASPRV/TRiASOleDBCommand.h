// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 17.05.2001 18:19:23 
//
// @doc
// @module TRiASOleDBCommand.h | Declaration of the <c CTRiASOleDBCommand> class

#if !defined(_TRIASOLEDBCOMMAND_H__4A2C9B47_61A4_4785_813B_BDD6208EB05F__INCLUDED_)
#define _TRIASOLEDBCOMMAND_H__4A2C9B47_61A4_4785_813B_BDD6208EB05F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <Atl/OleDB/ICommandPrepareImpl.h>
#include <Atl/OleDB/IColumnsRowsetImpl.h>
#include <Atl/CieThis.h>

///////////////////////////////////////////////////////////////////////////////
// CTRiASOleDBCommand
// B789D932-7E81-4058-85A9-DC71969B3AEB
EXTERN_C const GUID __declspec(selectany) CLSID_TRiASOleDBCommand = 
	{ 0xB789D932, 0x7E81, 0x4058, 0x85, 0xA9, 0xDC, 0x71, 0x96, 0x9B, 0x3A, 0xEB };

class ATL_NO_VTABLE CTRiASOleDBCommand : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CTRiASOleDBErrorBase<CTRiASOleDBCommand, &IID_ICommand>,
	public IAccessorImpl<CTRiASOleDBCommand>,
	public ICommandTextImpl<CTRiASOleDBCommand>,
	public ICommandPropertiesImpl<CTRiASOleDBCommand>,
	public IObjectWithSiteImpl<CTRiASOleDBCommand>,
	public IConvertTypeImpl<CTRiASOleDBCommand>,
	public IColumnsInfoImpl<CTRiASOleDBCommand>,
	public ICommandPrepareImpl<CTRiASOleDBCommand>,
	public IInternalConnectionCommandImpl<CTRiASOleDBCommand>,
	public ISupportErrorInfo
{
public:
	CTRiASOleDBCommand() :
		m_pGenColInfo(NULL)
	{
	}
	~CTRiASOleDBCommand()
	{
		DELETE_OBJ(m_pGenColInfo);
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CTRiASOleDBCommand)

	BEGIN_COM_MAP(CTRiASOleDBCommand)
		COM_INTERFACE_ENTRY(ICommand)
		COM_INTERFACE_ENTRY(IObjectWithSite)
		COM_INTERFACE_ENTRY(IAccessor)
		COM_INTERFACE_ENTRY(ICommandProperties)
		COM_INTERFACE_ENTRY2(ICommandText, ICommand)
		COM_INTERFACE_ENTRY(IColumnsInfo)
		COM_INTERFACE_ENTRY(IConvertType)
		COM_INTERFACE_ENTRY(ICommandPrepare)
		COM_INTERFACE_ENTRY(IInternalConnection)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY_THIS_EX(CLSID_TRiASOleDBCommand)
	END_COM_MAP()

// ICommand
public:
	DECLARE_PROTECT_FINAL_CONSTRUCT()
	DECLARE_GET_CONTROLLING_UNKNOWN()
	HRESULT FinalConstruct()
	{
	HRESULT hr = CConvertHelper::FinalConstruct();
	
		if (FAILED (hr)) return hr;
		hr = IAccessorImpl<CTRiASOleDBCommand>::FinalConstruct();
		if (FAILED(hr)) return hr;
		return CUtlProps<CTRiASOleDBCommand>::FInit();
	}
	void FinalRelease()
	{
		IAccessorImpl<CTRiASOleDBCommand>::FinalRelease();
	}

	HRESULT WINAPI Execute(IUnknown * pUnkOuter, REFIID riid, DBPARAMS * pParams, LONG * pcRowsAffected, IUnknown ** ppRowset);

// GetColumnInfo an RowSet weiterreichen
	static ATLCOLUMNINFO* GetColumnInfo(CTRiASOleDBCommand* pv, ULONG* pcInfo)
	{
		return pv -> GetRawColumnInfo(pcInfo);
	}
	ATLCOLUMNINFO *GetRawColumnInfo(ULONG *pcCols); 
	HRESULT PrepareColumnInfo();

	BEGIN_PROPSET_MAP(CTRiASOleDBCommand)
		BEGIN_PROPERTY_SET(DBPROPSET_ROWSET)
			PROPERTY_INFO_ENTRY_EX(IAccessor, VT_BOOL, DBPROPFLAGS_ROWSET | DBPROPFLAGS_READ, VARIANT_TRUE, 0)
			PROPERTY_INFO_ENTRY_EX(IColumnsInfo, VT_BOOL, DBPROPFLAGS_ROWSET | DBPROPFLAGS_READ, VARIANT_TRUE, 0)
			PROPERTY_INFO_ENTRY_EX(IColumnsRowset, VT_BOOL, DBPROPFLAGS_ROWSET | DBPROPFLAGS_READ, VARIANT_TRUE, 0)
			PROPERTY_INFO_ENTRY_EX(IConvertType, VT_BOOL, DBPROPFLAGS_ROWSET | DBPROPFLAGS_READ, VARIANT_TRUE, 0)
			PROPERTY_INFO_ENTRY_EX(IRowset, VT_BOOL, DBPROPFLAGS_ROWSET | DBPROPFLAGS_READ, VARIANT_TRUE, 0)
			PROPERTY_INFO_ENTRY_EX(IRowsetIdentity, VT_BOOL, DBPROPFLAGS_ROWSET | DBPROPFLAGS_READ, VARIANT_TRUE, 0)
			PROPERTY_INFO_ENTRY_EX(IRowsetInfo, VT_BOOL, DBPROPFLAGS_ROWSET | DBPROPFLAGS_READ, VARIANT_TRUE, 0)
			PROPERTY_INFO_ENTRY_EX(CANFETCHBACKWARDS,VT_BOOL, DBPROPFLAGS_ROWSET | DBPROPFLAGS_READ | DBPROPFLAGS_WRITE, 0, 0)
			PROPERTY_INFO_ENTRY_EX(CANHOLDROWS, VT_BOOL, DBPROPFLAGS_ROWSET | DBPROPFLAGS_READ | DBPROPFLAGS_WRITE, VARIANT_TRUE, 0)
			PROPERTY_INFO_ENTRY_EX(CANSCROLLBACKWARDS, VT_BOOL, DBPROPFLAGS_ROWSET | DBPROPFLAGS_READ | DBPROPFLAGS_WRITE, VARIANT_TRUE, 0)
			PROPERTY_INFO_ENTRY_EX(IRowsetLocate, VT_BOOL, DBPROPFLAGS_ROWSET | DBPROPFLAGS_READ | DBPROPFLAGS_WRITE, VARIANT_TRUE, 0)
			PROPERTY_INFO_ENTRY_EX(IRowsetBookmark, VT_BOOL, DBPROPFLAGS_ROWSET | DBPROPFLAGS_READ | DBPROPFLAGS_WRITE, VARIANT_TRUE, 0)
			PROPERTY_INFO_ENTRY_EX(IRowsetScroll, VT_BOOL, DBPROPFLAGS_ROWSET | DBPROPFLAGS_READ | DBPROPFLAGS_WRITE, VARIANT_TRUE, 0)
			PROPERTY_INFO_ENTRY_EX(BOOKMARKS, VT_BOOL, DBPROPFLAGS_ROWSET | DBPROPFLAGS_READ | DBPROPFLAGS_WRITE , VARIANT_TRUE, 0)
			PROPERTY_INFO_ENTRY_EX(BOOKMARKSKIPPED,VT_BOOL, DBPROPFLAGS_ROWSET | DBPROPFLAGS_READ, VARIANT_TRUE, 0)
			PROPERTY_INFO_ENTRY_EX(BOOKMARKTYPE, VT_I4, DBPROPFLAGS_ROWSET | DBPROPFLAGS_READ, DBPROPVAL_BMK_NUMERIC, 0)
			PROPERTY_INFO_ENTRY_EX(LITERALBOOKMARKS, VT_BOOL, DBPROPFLAGS_ROWSET | DBPROPFLAGS_READ | DBPROPFLAGS_WRITE, VARIANT_TRUE, 0)
			PROPERTY_INFO_ENTRY_EX(ORDEREDBOOKMARKS, VT_BOOL, DBPROPFLAGS_ROWSET | DBPROPFLAGS_READ | DBPROPFLAGS_WRITE, VARIANT_FALSE, 0)
			PROPERTY_INFO_ENTRY_EX(LITERALIDENTITY, VT_BOOL, DBPROPFLAGS_ROWSET | DBPROPFLAGS_READ, VARIANT_TRUE, 0)
			PROPERTY_INFO_ENTRY_EX(STRONGIDENTITY, VT_BOOL, DBPROPFLAGS_ROWSET | DBPROPFLAGS_READ, VARIANT_TRUE, 0)
			PROPERTY_INFO_ENTRY_EX(MAXOPENROWS, VT_I4, DBPROPFLAGS_ROWSET | DBPROPFLAGS_READ | DBPROPFLAGS_WRITE, 0, 0)
			PROPERTY_INFO_ENTRY_EX(MAXROWS, VT_I4, DBPROPFLAGS_ROWSET | DBPROPFLAGS_READ | DBPROPFLAGS_WRITE, 0, 0)

			PROPERTY_INFO_ENTRY_EX(ISupportErrorInfo, VT_BOOL, DBPROPFLAGS_ROWSET | DBPROPFLAGS_READ, VARIANT_TRUE, 0)
			PROPERTY_INFO_ENTRY_EX(DEFERRED, VT_BOOL, DBPROPFLAGS_ROWSET | DBPROPFLAGS_READ | DBPROPFLAGS_WRITE, VARIANT_TRUE, 0)
			PROPERTY_INFO_ENTRY_EX(CACHEDEFERRED, VT_BOOL, DBPROPFLAGS_ROWSET | DBPROPFLAGS_READ | DBPROPFLAGS_WRITE, VARIANT_TRUE, 0)

//			PROPERTY_INFO_ENTRY_VALUE(NOTIFICATIONPHASES, DBPROPVAL_NP_OKTODO | DBPROPVAL_NP_ABOUTTODO | DBPROPVAL_NP_SYNCHAFTER |DBPROPVAL_NP_FAILEDTODO | DBPROPVAL_NP_DIDEVENT)
//			PROPERTY_INFO_ENTRY_EX(NOTIFYROWDELETE, VT_I4, DBPROPVAL_NP_OKTODO | DBPROPVAL_NP_ABOUTTODO | DBPROPVAL_NP_SYNCHAFTER | DBPROPVAL_NP_FAILEDTODO | DBPROPVAL_NP_DIDEVENT, VARIANT_TRUE, 0)
//			PROPERTY_INFO_ENTRY_EX(NOTIFYROWINSERT, VT_I4, DBPROPVAL_NP_OKTODO | DBPROPVAL_NP_ABOUTTODO | DBPROPVAL_NP_SYNCHAFTER | DBPROPVAL_NP_FAILEDTODO | DBPROPVAL_NP_DIDEVENT, VARIANT_TRUE, 0)
//			PROPERTY_INFO_ENTRY_EX(NOTIFYCOLUMNSET, VT_I4, DBPROPVAL_NP_OKTODO | DBPROPVAL_NP_ABOUTTODO | DBPROPVAL_NP_SYNCHAFTER | DBPROPVAL_NP_FAILEDTODO | DBPROPVAL_NP_DIDEVENT, VARIANT_TRUE, 0)
//			PROPERTY_INFO_ENTRY_EX(NOTIFYROWSETFETCHPOSITIONCHANGE, VT_I4, DBPROPVAL_NP_OKTODO | DBPROPVAL_NP_ABOUTTODO | DBPROPVAL_NP_SYNCHAFTER | DBPROPVAL_NP_FAILEDTODO | DBPROPVAL_NP_DIDEVENT, VARIANT_TRUE, 0)
//			PROPERTY_INFO_ENTRY_EX(NOTIFICATIONGRANULARITY, VT_I4, DBPROPFLAGS_ROWSET | DBPROPFLAGS_READ | DBPROPVAL_NT_MULTIPLEROWS, VARIANT_TRUE, 0)
//			PROPERTY_INFO_ENTRY_EX(SERVERCURSOR, VT_BOOL, DBPROPFLAGS_ROWSET | DBPROPFLAGS_READ , VARIANT_TRUE, 0)

//			PROPERTY_INFO_ENTRY_EX(IRowsetChange, VT_BOOL, DBPROPFLAGS_ROWSET | DBPROPFLAGS_READ | DBPROPFLAGS_WRITE, VARIANT_TRUE, 0)
//			PROPERTY_INFO_ENTRY_EX(UPDATABILITY, VT_I4, DBPROPFLAGS_ROWSET | DBPROPFLAGS_READ | DBPROPFLAGS_WRITE, DBPROPVAL_UP_CHANGE | DBPROPVAL_UP_DELETE | DBPROPVAL_UP_INSERT, 0)
//			PROPERTY_INFO_ENTRY_EX(REMOVEDELETED, VT_BOOL, DBPROPFLAGS_ROWSET | DBPROPFLAGS_READ | DBPROPFLAGS_WRITE, VARIANT_TRUE, 0)
//			PROPERTY_INFO_ENTRY_EX(OWNINSERT, VT_BOOL, DBPROPFLAGS_ROWSET | DBPROPFLAGS_READ | DBPROPFLAGS_WRITE, VARIANT_TRUE, 0)
//			PROPERTY_INFO_ENTRY_EX(OWNUPDATEDELETE, VT_BOOL, DBPROPFLAGS_ROWSET | DBPROPFLAGS_READ | DBPROPFLAGS_WRITE, VARIANT_TRUE, 0)
			PROPERTY_INFO_ENTRY_EX(OTHERINSERT, VT_BOOL, DBPROPFLAGS_ROWSET | DBPROPFLAGS_READ | DBPROPFLAGS_WRITE, VARIANT_FALSE, 0)
			PROPERTY_INFO_ENTRY_EX(OTHERUPDATEDELETE, VT_BOOL, DBPROPFLAGS_ROWSET | DBPROPFLAGS_READ | DBPROPFLAGS_WRITE, VARIANT_FALSE, 0)
		END_PROPERTY_SET(DBPROPSET_ROWSET)
	END_PROPSET_MAP()

// overloads from ICommandPrepareImpl
	HRESULT PrepareCommand(ULONG cExpectedRuns);
	HRESULT UnprepareCommand();

// ISupportErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
	{
		return (InlineIsEqualGUID(riid, IID_ICommand)) ? S_OK : S_FALSE;
	}

// ICommandText
	STDMETHOD(SetCommandText)(REFGUID rguidDialect, LPCOLESTR pwszCommand)
	{
		SetErrorInfo(0, NULL);

		RETURN_ERROR(ICommandTextImpl<CTRiASOleDBCommand>::SetCommandText(rguidDialect, pwszCommand));
		if (NULL != m_pGenColInfo) {
		ObjectLock lock(this);

			m_pGenColInfo -> SetPrepared(false);
		}
		return S_OK;
	}

// IColumnsInfo
	STDMETHOD(GetColumnInfo)(ULONG *pcColumns, DBCOLUMNINFO **prgInfo, OLECHAR **ppStringsBuffer)
	{
		ATLTRACE2(atlTraceDBProvider, 0, "CTRiASOleDBCommand::GetColumnInfo\n");
		SetErrorInfo(0, NULL);
		if (pcColumns == NULL || prgInfo == NULL || ppStringsBuffer == NULL) {
			if (prgInfo != NULL)
				*prgInfo = NULL;
			if (ppStringsBuffer != NULL)
				*ppStringsBuffer = NULL;
			if (pcColumns != NULL)
				*pcColumns = NULL;
			return OleDBError(E_INVALIDARG);
		}
		
	// NULL out pointers in case of an error
		*prgInfo = NULL;
		*ppStringsBuffer = NULL;
		*pcColumns = 0;

	ObjectLock lock(this);

		RETURN_ERROR(CheckCommandText(GetUnknown()));
		if (!m_fIsPrepared)
			return OleDBError(DB_E_NOTPREPARED);

		return IColumnsInfoImpl<CTRiASOleDBCommand>::GetColumnInfo(pcColumns, prgInfo, ppStringsBuffer);
	}
	STDMETHOD(MapColumnIDs)(ULONG cColumnIDs, const DBID rgColumnIDs[], ULONG rgColumns[])
	{
		ATLTRACE2(atlTraceDBProvider, 0, "CTRiASOleDBCommand::MapColumnIDs\n");
		SetErrorInfo(0, NULL);
		if ((cColumnIDs != 0 && rgColumnIDs == NULL) || rgColumns == NULL)
			return OleDBError(E_INVALIDARG);

	ObjectLock lock(this);

		RETURN_ERROR(CheckCommandText(GetUnknown()));
		if (!m_fIsPrepared)
			return OleDBError(DB_E_NOTPREPARED);

		return IColumnsInfoImpl<CTRiASOleDBCommand>::MapColumnIDs(cColumnIDs, rgColumnIDs, rgColumns);
	}

// eine Property wurde geändert
	HRESULT OnPropertyChanged(ULONG iCurSet, DBPROP *pDBProp)
	{
		ATLASSERT(pDBProp != NULL);
		
	DWORD dwPropertyID = pDBProp->dwPropertyID;
		
		if (dwPropertyID == DBPROP_IRowsetLocate ||
			dwPropertyID == DBPROP_IRowsetBookmark ||
			dwPropertyID == DBPROP_LITERALBOOKMARKS ||
			dwPropertyID == DBPROP_ORDEREDBOOKMARKS)
		{
		CComVariant var (pDBProp->vValue);
			
			if (var.boolVal == VARIANT_TRUE) {
			// Set the bookmarks property as these are chained
			CComVariant bookVar(true);
			CDBPropSet set(DBPROPSET_ROWSET);

				set.AddProperty(DBPROP_BOOKMARKS, bookVar);
				
			// If you set IRowsetLocate to true, then the rowset can
			// handle backward scrolling
				if (dwPropertyID == DBPROP_IRowsetLocate)
					set.AddProperty(DBPROP_CANSCROLLBACKWARDS, bookVar);
				
			const GUID* ppGuid[1];

				ppGuid[0] = &DBPROPSET_ROWSET;
				return CUtlProps<CTRiASOleDBCommand>::SetProperties(0, 1, &set, 1, ppGuid);
			}
		}

	// ausschalten der Bookmarks verhindert alles andere
		if (dwPropertyID == DBPROP_BOOKMARKS) {
		CComVariant var (pDBProp->vValue);
			
			if (var.boolVal == VARIANT_FALSE) {
			// Reset the bookmarks property as these are chained
			CComVariant bookVar(false);
			CDBPropSet set(DBPROPSET_ROWSET);

				set.AddProperty(DBPROP_IRowsetLocate, bookVar);
				set.AddProperty(DBPROP_IRowsetBookmark, bookVar);
				set.AddProperty(DBPROP_LITERALBOOKMARKS, bookVar);
				set.AddProperty(DBPROP_ORDEREDBOOKMARKS, bookVar);
				
			const GUID* ppGuid[1];

				ppGuid[0] = &DBPROPSET_ROWSET;
				return CUtlProps<CTRiASOleDBCommand>::SetProperties(0, 1, &set, 1, ppGuid);
			}
		}
		return S_OK;
	}

// Zugriffsmöglichkeit für abgeleitete Rowsets
	CGenerateColumnInfoBase *GetGeneratedColunmInfo() 
	{ 
		if (NULL == m_pGenColInfo) {
			ATLTRY(m_pGenColInfo = new CGenerateColumnInfo<&IID_ICommand>());
		}
		return m_pGenColInfo;
	}

protected:
	HRESULT PrepareSelect(CTRiASOleDBSource *pDataSource);

private:
	CGenerateColumnInfoBase *m_pGenColInfo;
};

#endif // !defined(_TRIASOLEDBCOMMAND_H__4A2C9B47_61A4_4785_813B_BDD6208EB05F__INCLUDED_)
