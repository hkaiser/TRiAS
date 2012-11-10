// GDOObjectsColl.h: Definition of the CGDOObjectsCollection class
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GDOOBJECTSCOLL_H__1F057F16_C1E9_11D2_98F2_0060085FC1CE__INCLUDED_)
#define AFX_GDOOBJECTSCOLL_H__1F057F16_C1E9_11D2_98F2_0060085FC1CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CGDOObjectsCollection

class CGDOObjectsCollection : 
	public CComObjectRootEx<CComObjectThreadModel>
	, public IDispatchImpl<IGDOObjectsCollection, &IID_IGDOObjectsCollection, &LIBID_TRiASGDO>
	, public CComCoClass< CGDOObjectsCollection, &CLSID_GDOObjectsCollection >
	, public CErrSupport< CGDOObjectsCollection, &CLSID_GDOObjectsCollection >
	, public ITRiASObjectsCollectionCallback
{
	WUnknown			m_BaseUnk;						// aggregiertes Objekt
	ITRiASObjectsCollection	*m_pTRiASObjectsCollection;
#define	BASE_OF_GDOOBJECTSCOLLECTION	m_pTRiASObjectsCollection

	long				m_lInitData;
	WDGMConnection		m_pDGMConnection;
	WGDatabase			m_pGDatabase;
	WDGMCoordSystemsMgr	m_pDGMCoordSystemsMgr;
	VARIANT_BOOL		m_bWritable;
	WTRiASMDSMap		m_pTRiASMDSMap;				// Metadatenservicemap
	WTRiASMDSKey		m_pTRiASMDSKey;				// Formatierung von Objektklassenschlüsseln
	WTRiASObjectHandleMap	m_pTRiASObjectHandleMap;	// globale Objekthandlemap
	map<CComBSTR,bool>	m_strTablesToDelete;

	HRESULT	IsInitialized( ) { return (!!m_pGDatabase /*&& !!m_pMetadataService*/) ? S_OK : S_FALSE; }

protected:
	HRESULT	ClearMDSMap();
	HRESULT	RemapObjects( WTRiASObjects& objs );
	HRESULT	GetPrimaryCS( CComBSTR &strCSGUID );
//	HRESULT	TryToFindExisting( const CComBSTR& strClassname, ITRiASObjects **ppIObjs );
	HRESULT	CreateTableDef( CComBSTR& strTablename, CComBSTR& strPKeyName, CComBSTR& strPGeomName, short sTypeOfPKey = gdbText, long lSizeOfPKey = 16 );
	HRESULT	CreateObjectsDef(VARIANT NameOrHandle, DWORD dwType, const CLSID *pClsId, ITRiASObjects **ppIObjs);
	HRESULT	GetOrCreateObjectsDef( CComBSTR& strOKS, const CComBSTR& strTablename, const CComBSTR& strClassname, const CComBSTR& strDescription, long lType, ITRiASObjects** ppIObjects );
	HRESULT FindClassname( const BSTR& strFullOKS, CComBSTR& strFoundOKS );

	////////////////////////////////////////////////////////////////////////////////////////////
	// Helfer zum Speichern
	HRESULT	UpdateTables( W_MetadataService& pMetadataService, VARIANT_BOOL *pbChanged );
	HRESULT	UpdateTable( W_MetadataService& pMetadataService, WTRiASObjects& rpTRiASObjects, /*const*/ CComBSTR& strOldTablename, /*const*/ CComBSTR& strNewTablename );
	HRESULT	DeleteTables( W_MetadataService& pMetadataService, VARIANT_BOOL *pbChanged );
	HRESULT	DeleteTable( W_MetadataService& pMetadataService, /*const*/ CComBSTR& strTablename );
	HRESULT	RedescribeTableMetadata( W_MetadataService& pMetadataService );
	HRESULT	RedescribeFieldMetadata( W_MetadataService& pMetadataService, ITRiASFeatures* pTRiASFeatures );

	HRESULT	SetDirty();
public:
//	static HRESULT CreateInstance( IGDOObjectsCollection** ppObjectsCollection );
	CGDOObjectsCollection()
		: m_BaseUnk(NULL)
		, m_lInitData(0)
		, m_bWritable(VARIANT_FALSE)
		, m_pTRiASObjectsCollection(NULL)
	{}

	HRESULT FinalConstruct() 
	{
		COM_TRY {
			RETURN_FAILED_HRESULT(m_BaseUnk.CreateInstance (CLSID_TRiASObjectsCollection, CLSCTX_ALL, GetControllingUnknown()));
		
		WTRiASObjectsCollection BaseObj;
		
			RETURN_FAILED_HRESULT( m_BaseUnk->QueryInterface(BaseObj.GetIID(), BaseObj.ppv()));
			RETURN_FAILED_HRESULT( BaseObj->putref_ObjectsCollectionCallback(this) );
			m_pTRiASObjectsCollection = BaseObj;
			m_pTRiASObjectHandleMap = WTRiASObjectHandleMap(CLSID_TRiASObjectsHandleMap);
			m_pTRiASMDSKey = WTRiASMDSKey(CLSID_TRiASMDSKey);
		} COM_CATCH
		return S_OK;
	}
	void FinalRelease() 
	{
		m_BaseUnk.Assign(NULL);
	}

	_ATLX_DEBUG_ADDREF_RELEASE_IMPL(CGDOObjectsCollection)
	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CGDOObjectsCollection)
	DECLARE_REGISTRY_RESOURCEID(IDR_GDOObjectsCollection)
//	DECLARE_NOT_AGGREGATABLE(CGDOObjectsCollection) 
	DECLARE_GET_CONTROLLING_UNKNOWN()
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	DECLARE_AGGREGATE_EX_SUPPORT();
	BEGIN_COM_MAP(CGDOObjectsCollection)
		COM_INTERFACE_ENTRY(IGDOObjectsCollection)
		COM_INTERFACE_ENTRY2(IDispatch, IGDOObjectsCollection)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)

		COM_INTERFACE_ENTRY(ITRiASObjectsCollectionCallback)

		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_ITRiASBase, m_BaseUnk.p)
		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_ITRiASObjectsCollection, m_BaseUnk.p)

		COM_INTERFACE_ENTRY_AGGREGATE_BLIND(m_BaseUnk.p)
	END_COM_MAP()

public:
// IGDOObjectsCollection
	DECLARE_DEBUG_FUNCENTRY_2(CGDOObjectsCollection,InitTarget
		, /*[in]SAFEARRAY(IUnknown*)*/ SAFEARRAY*, pObjects
		, /*[in]*/ VARIANT_BOOL, bWritable
		);
	DECLARE_DEBUG_FUNCENTRY_2(CGDOObjectsCollection,ReclassObjects
		, /*[in]*/ IGDOObjects*, pObjects
		, /*[in]*/ BSTR, strNewOKS
		);
	DECLARE_DEBUG_FUNCENTRY_2(CGDOObjectsCollection,RenameObjects
		, /*[in]*/ IGDOObjects*, pObjects
		, /*[in]*/ BSTR, strOldName
		);
	DECLARE_DEBUG_FUNCENTRY_1(CGDOObjectsCollection,RedescribeObjects
		, /*[in]*/ IGDOObjects*, pObjects
		);
	DECLARE_DEBUG_FUNCENTRY_0(CGDOObjectsCollection,Save
//		, /*[in,out]*/ VARIANT_BOOL*, pbHaveChanced
		);
	DECLARE_DEBUG_FUNCENTRY_2(CGDOObjectsCollection,Item
		, /*[in]*/ VARIANT, vIndex
		, /*[in]*/ VARIANT*, vItem
		);
// ITRiASObjectsCollectionCallback
	DECLARE_DEBUG_FUNCENTRY_1(CGDOObjectsCollection,get_DefaultType, /*[out, retval]*/ BSTR*, pbstrType );
	DECLARE_DEBUG_FUNCENTRY_0(CGDOObjectsCollection,SetupCollection);
	DECLARE_DEBUG_FUNCENTRY_4(CGDOObjectsCollection,OnCreate, /*[in]*/ VARIANT, NameOrHandle, /*[in, optional, defaultvalue]*/ BSTR, Type, /*[in]*/ OBJECTSCOLLECTIONTYPE, rgType, /*[out, retval]*/ ITRiASObjects**, ppIObjs);
	DECLARE_DEBUG_FUNCENTRY_1(CGDOObjectsCollection,OnDelete, /*[in]*/ VARIANT, vWhich);
    DECLARE_DEBUG_FUNCENTRY_0(CGDOObjectsCollection,OnFinalRelease);
};

#endif // !defined(AFX_GDOOBJECTSCOLL_H__1F057F16_C1E9_11D2_98F2_0060085FC1CE__INCLUDED_)
