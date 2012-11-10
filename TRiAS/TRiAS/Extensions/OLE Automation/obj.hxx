// Ein Objekt (Controlling Unknown) -------------------------------------------
// File: OBJ.HXX

#if !defined(_OBJ_HXX)
#define _OBJ_HXX

#include <Atl/CieThis.h>
#include "class.hxx"

class CTriasApp;
class CGeoDoc;
class CFeatObjTree;
class CGeoFeatureBase;

// {5D54A535-19D3-46AB-911C-DC17C3AB0009}
extern "C" const IID __declspec(selectany) CLSID_GeoObject = 
	{0x5d54a535,0x19d3,0x46ab,{0x91,0x1c,0xdc,0x17,0xc3,0xab,0x00,0x09}};

class CGeoObject : 
	public CComDualImpl<DGeoObject, &IID_DGeoObject, &LIBID_TRiAS, 
				TYPELIB_VERSION_MAJOR, TYPELIB_VERSION_MINOR>, 
	public CComISupportErrorInfoImpl<&IID_DGeoObject>,
	public CComObjectRoot
{
	D_CLASS(CGeoObject);

private:
	LPUNKNOWN m_pUnk;		// controlling unknown
	CTriasApp *m_pApp;		// Trias.Application
	CGeoDoc *m_pDoc;		// Trias.Project

	CFeatObjTree *m_pFeatObjTree;	// Object GeoFeatures Tree

	LONG m_lONr;			// ObjectNumber
	char *m_pName;			// ObjectName
	
	bool m_fValid;			// object exists

	void Invalidate (void);

public:
	void Validate (void);

protected:
friend HRESULT GetEnumLongFromGeoObjects (DGeoObjects *pIObjs, IEnumLONG **ppIEnum);
	
	HRESULT GetEnumFromONr (LONG lONr, IEnumLONG **ppIEnum, bool fAddMe = false);
	HRESULT RetrieveHandle (VARIANT &rvORWnd, HWND *phWnd);
	HRESULT GetVisInfoClsId (CLSID *pClsId);

public:
		CGeoObject (void);
		~CGeoObject (void);
		
static CGeoObject *CreateInstance (
		LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc, 
		LONG lONr, GEOOBJECTMODE rgMode = GEOOBJECTMODE_Get, VARIANT *pvCls = NULL);
static CGeoObject *CreateInstance (
		LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc, 
		LPCSTR bName, GEOOBJECTMODE rgMode = GEOOBJECTMODE_Get, VARIANT *pvCls = NULL);

	bool FInit (LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc, 
		GEOOBJECTMODE rgMode, LPCSTR bName, VARIANT *pvCls);
	bool FInit (LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc, 
		GEOOBJECTMODE rgMode, LONG lONr, VARIANT *pvCls);

///////////////////////////////////////////////////////////////////////////////
// ATL stuff
	BEGIN_COM_MAP(CGeoObject)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(DGeoObject)
		COM_INTERFACE_ENTRY(DTRiASBaseClass)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY_THIS_EX(CLSID_GeoObject)
	END_COM_MAP()

	DECLARE_NOT_AGGREGATABLE(CGeoObject)

///////////////////////////////////////////////////////////////////////////////
// Verwalten der externen Locks
	ULONG InternalAddRef(void);
	ULONG InternalRelease(void);
	HRESULT FinalExternalConstruct (void);
	void FinalExternalRelease (void);
//	static CComGlobalsThreadModel::AutoCriticalSection m_cs;

	bool MayRelease() { return m_dwRef <= OBJ_EXTERNAL_THRESHOLD; }
	bool ReleaseItems() { m_pFeatObjTree -> EveryDelete(); return true; }		// alles, was dran hängt freigeben
	
///////////////////////////////////////////////////////////////////////////////
// *** _IGeoObject methods 
	STDMETHOD(get_isA)(LONG *plRTTI);
	STDMETHOD(get_Parent)(IDispatch **ppIDisp);
	STDMETHOD(get_Application)(IDispatch **ppIDisp);
	STDMETHOD(put_Parent)(THIS_ IDispatch *pIBase);
	STDMETHOD(put_Application)(THIS_ IDispatch *pIApp);

	STDMETHOD(get_Properties) (THIS_ _DTRiASProperties **ppIProps);
	STDMETHOD(CreateProperty) (THIS_ VARIANT vName, VARIANT vType, VARIANT vValue, _DTRiASProperty **ppIProp);

	STDMETHOD(get_Value)(THIS_ long *plONr);
	STDMETHOD(get_Name)(THIS_ BSTR *pbstrName);
	STDMETHOD(put_Name)(THIS_ BSTR bstrName);

	STDMETHOD(get_ObjType)(THIS_ OBJECTTYPE *pObjType);
	STDMETHOD(get_ObjClass)(THIS_ DGeoClass **pICls);
	
	STDMETHOD(ObjDistance)(THIS_ DGeoObject *pIObj, VARIANT vMode, VARIANT vMinMax, double *pdblDist);
	STDMETHOD(ClassDistance)(THIS_ DGeoClass *pICls, VARIANT *pvObj, VARIANT vModeArg, VARIANT vMinMaxArg, double *pdblDist);

    STDMETHOD(GetGeometryPt)(THIS_ double *pdblX, double *pdblY, OBJECTTYPE *piOTyp);
	STDMETHOD(GetGeometry)(THIS_ long *plCnt, VARIANT *pvXArr, VARIANT *pvYArr, VARIANT *pvKCnt, VARIANT *pvConture, OBJECTTYPE *piOTyp);
    STDMETHOD(GetGeometryPtCS)(THIS_ VARIANT CS, double *pdblX, double *pdblY, OBJECTTYPE *piOTyp);
	STDMETHOD(GetGeometryCS)(THIS_ VARIANT CS, long *plCnt, VARIANT *pvXArr, VARIANT *pvYArr, VARIANT *pvKCnt, VARIANT *pvConture, OBJECTTYPE *piOTyp);

	STDMETHOD(PutGeometryPt)(THIS_ OBJECTTYPE rgOTyp, double dX, double dY, VARIANT iMode, VARIANT_BOOL *pfResult);
	STDMETHOD(PutGeometry)(THIS_ OBJECTTYPE rgOTyp, VARIANT vaXArr, VARIANT vaYArr, VARIANT vaConture, VARIANT vMode, VARIANT_BOOL *pfResult);
	STDMETHOD(PutGeometryPtCS)(THIS_ VARIANT CS, OBJECTTYPE rgOTyp, double dX, double dY, VARIANT iMode, VARIANT_BOOL *pfResult);
	STDMETHOD(PutGeometryCS)(THIS_ VARIANT CS, OBJECTTYPE rgOTyp, VARIANT vaXArr, VARIANT vaYArr, VARIANT vaConture, VARIANT vMode, VARIANT_BOOL *pfResult);

	STDMETHOD(GetText)(THIS_ BSTR *pbstrText);
	STDMETHOD(PutText)(THIS_ BSTR bstrText);

	STDMETHOD(TopRelation)(THIS_ DGeoObject *pIObj, TOPRELATION *prgRTyp);
    STDMETHOD(GetTopRelationObjects)(THIS_ TOPRELATION rgRelTyp, DGeoObjects **ppIObjs);
    STDMETHOD(GetBufferObjects)(THIS_ double dblWidth, VARIANT vCount, VARIANT vFullCircle, VARIANT vIdent, DGeoObjects **ppIObjs);
    STDMETHOD(GetBufferObjectEx)(THIS_ double dblWidth, VARIANT vFullCircle, VARIANT vSide, VARIANT vConvexMode, VARIANT vPrecision, DGeoObject **ppIObj);
    STDMETHOD(GetCircleBufferObjects)(THIS_ double dblWidth, VARIANT vCount, VARIANT vFullCircle, VARIANT vIdent, DGeoObjects **ppIObjs);
    STDMETHOD(GetIntersectObjects)(THIS_ DGeoObject *pIObj, VARIANT vResultMode, DGeoObjects **ppIObjs);
    STDMETHOD(GetIntersectObjectsCollection)(THIS_ DGeoObjects *pIObjs, VARIANT vResultMode, DGeoObjects **ppIObjs);
    STDMETHOD(GetIntersectObjectsClass)(THIS_ DGeoClass *pICls, VARIANT vResultMode, DGeoObjects **ppIObjs);

    STDMETHOD(GeometryIntersection)(THIS_ DGeoObject *pIObj, VARIANT vIdent, DGeoObjects **ppIObjs);
    STDMETHOD(GeometryUnion)(THIS_ DGeoObject *pIObj, VARIANT vIdent, DGeoObjects **ppIObjs);

	STDMETHOD(RePaint)(THIS_ VARIANT vComplete);

	STDMETHOD(GetFeatures)(THIS_ VARIANT vFeatures, VARIANT vLogMode, DGeoFeatures **ppIFeats);
	STDMETHOD(GetFeature)(THIS_ VARIANT vFeature, VARIANT vMode, VARIANT vProps, DGeoFeature **ppIFeat);

    STDMETHOD(GetVisInfo)(THIS_ VARIANT vView, DVisInfo **ppIVisInfo);
    STDMETHOD(SetVisInfo)(THIS_ DVisInfo *pIVisInfo, VARIANT vView);

    STDMETHOD(GetCommonContourObjects)(THIS_ DGeoObjects *pIInObjs, VARIANT vIdent, VARIANT vResultMode, DGeoObjects **ppIObjs);
    STDMETHOD(GetGeometryRect)(THIS_ double *pdblXMin, double *pdblYMin, double *pdblXMax, double *pdblYMax, OBJECTTYPE *piOTyp);
    STDMETHOD(GetGeometryRectCS)(THIS_ VARIANT CS, double *pdblXMin, double *pdblYMin, double *pdblXMax, double *pdblYMax, OBJECTTYPE *piOTyp);

    STDMETHOD(get_Selected)(THIS_ VARIANT vObjWin, VARIANT_BOOL *pfSelected);
    STDMETHOD(put_Selected)(THIS_ VARIANT vObjWin, VARIANT_BOOL fSelected);
    STDMETHOD(get_Activated)(THIS_ VARIANT vObjWin, VARIANT_BOOL *pfActivated);
    STDMETHOD(put_Activated)(THIS_ VARIANT vObjWin, VARIANT_BOOL fActivated);

	STDMETHOD(AddFeature)(THIS_ VARIANT vFeature, VARIANT vProps, VARIANT vOptData, DGeoFeature **ppIFeat);
	STDMETHOD(RemoveFeature)(THIS_ VARIANT vFeature);

	STDMETHOD(get_Feature)(THIS_ BSTR bstrName, VARIANT *pvValue);
	STDMETHOD(put_Feature)(THIS_ BSTR bstrName, VARIANT vValue);

    STDMETHOD(ResetVisInfo)(THIS_ VARIANT vView);

    STDMETHOD(Hilight)(THIS_ TRIASCOLOR crAct);
    STDMETHOD(UnHilight)(THIS);

	STDMETHOD(ShiftGeometrySegment) (THIS_ double DestX, double DestY, 
		VARIANT TargetBeginX, VARIANT TargetBeginY,	VARIANT TargetEndX, VARIANT TargetEndY,
		VARIANT MoveDir, VARIANT ContinueBegin, VARIANT ContinueEnd, VARIANT Eps,
		VARIANT ClipXMin, VARIANT ClipYMin, VARIANT ClipXMax, VARIANT ClipYMax, 
		DGeoObject **NewObj);

	STDMETHOD(get_Guid)(THIS_ BSTR *Ident);
	STDMETHOD(put_Guid)(THIS_ BSTR Ident);
	STDMETHOD(get_UniqueID)(THIS_ BSTR *Ident);
	STDMETHOD(put_UniqueID)(THIS_ BSTR Ident);
	STDMETHOD(get_OldUniqueID)(THIS_ BSTR *Ident);
	STDMETHOD(put_OldUniqueID)(THIS_ BSTR Ident);

	STDMETHOD(GeometryXOR) (THIS_ DGeoObjects *pIObjs, DGeoObjects **ppIObjs);

	STDMETHOD(MakeRectangular)(THIS_ VARIANT vRefLine, VARIANT vEps90, VARIANT vEps180, VARIANT vEpsCom, VARIANT vEnumCommon, DGeoObjects **Objs);

	STDMETHOD(GetRelatedObject)(THIS_ DGeoObject **ppIObj);
	STDMETHOD(CreateObjectRelation)(THIS_ DGeoObject *pIObjIn);
	STDMETHOD(RemoveObjectRelation)(THIS_ DGeoObject **ppIObj);

	STDMETHOD(AnalyzeGeometry)(THIS_ VARIANT_BOOL *pbSuccess);
	STDMETHOD(AnalyzeGeometryObject)(THIS_ DGeoObject *pIObjIn, VARIANT vMode, VARIANT_BOOL *pbSuccess);

	STDMETHOD(get_Visible)(THIS_ VARIANT vView, VARIANT_BOOL *pfValue);
	STDMETHOD(put_Visible)(THIS_ VARIANT vView, VARIANT_BOOL fValue);

	STDMETHOD(get_Connection)(THIS_ ITRiASConnection **ppIConn);

	STDMETHOD(CloneObject)(THIS_ VARIANT vClass, DGeoObject **ppIObj);	// #HK001022

///////////////////////////////////////////////////////////////////////////////
// sonstige Member 
	const char *GetName (void);
	bool SetName (const char *pName, bool fCreate = true, bool fIgnoreValid = false);

	ULONG GetObjIdent (void);
	ULONG GetObjIdentEx (void);
	ULONG ChangeObjIdent (ULONG lNewIdent, bool fIsNotification = false);
	
	short GetObjectType (void);
	short GetStatistik (long &rlCnt, short &riKCnt);
	bool GetGeometryPt (double &rdX, double &rdY, IUnknown *pICS = NULL);
	bool GetGeometry (short iOTyp, long lCnt, double __huge *, double __huge *,
					  short, long *, IUnknown *pICS = NULL);
	bool PutGeometryPt (short iOTyp, double dX, double dY, short iMode, IUnknown *pICS = NULL);
	bool PutGeometry (short iOTyp, long lCnt, double __huge *, double __huge *,
					  short, long *, short iMode, IUnknown *pICS = NULL);
	bool GetTextObjectText (BSTR *pbstrText);
	bool PutTextObjectText (BSTR bstrText);
	bool Remove (void);

	void RePaint (bool fComplete);		// Objekt neu zeichnen
			
inline	LONG GetValue (bool fForce = false) { return !fForce && !m_fValid ? INVALID_ONR : m_lONr; }
inline	bool IsValid  (void) { return m_fValid ? true : false; }

///////////////////////////////////////////////////////////////////////////////
// for the tree's
	LONG & FGetLONG (void);			// liefert SuchSchlüssel
	LPCSTR FGetBSTR (void);			// liefert SuchSchlüssel

friend int FCmpLONG (const LONG &, const LONG &);	// vergleicht 2 Schlüssel
friend int FCmpBSTR (LPCSTR, LPCSTR);				// vergleicht 2 Schlüssel

// Functions for GeoFeatures Tree 
	CGeoFeatureBase *FGetFeatureDisp (LPCSTR bName, DGeoFeature **ppIFeat = NULL, 
		PROPCAPS rgProps = PROPCAPS_UNKNOWN, FEATUREMODE rgMode = FEATUREMODE_Get, 
		VARIANT *pvOptData = NULL, IObjectProperty *pIObjProp = NULL)
	{ return m_pFeatObjTree ? m_pFeatObjTree -> FAddItem (bName, ppIFeat, rgMode, rgProps, pvOptData, pIObjProp) : NULL; }
	bool FDelFeature (LPCSTR bName) 
		{ return m_pFeatObjTree ? m_pFeatObjTree -> FDeleteItem (bName) : false; }
	bool FInvFeature (LPCSTR pName) 
		{ return m_pFeatObjTree ? m_pFeatObjTree -> FInvalidateItem (pName) : false; }
	bool SetFeatureName (LPCSTR bOldName, LPCSTR bNewName) 
		{ return m_pFeatObjTree ? m_pFeatObjTree -> SetFeatureName (bOldName, bNewName) : false; }

// Helperfunktion
	HRESULT GetDispatchIF (IDispatch **ppIDisp)
		{ return ((_DGeoObject *)this)->QueryInterface (IID_IDispatch, (LPVOID *)ppIDisp); }

friend class CObjTrees;
friend class CONrTree;
friend class CObjNameTree;
};

#endif // _OBJ_HXX
