// @doc
// @module TRiASCSGeometryCollection.cpp | Implementation of CTRiASCSGeometryCollection.

#include "StdAfx.h"
#include "TDBGeoImpl.h"

#include "MakeEnumVariant.h"
#include "TRiASCSGeometryCollection.h"
#include "TDBGEO.h"

/////////////////////////////////////////////////////////////////////////////
// local heap for this class
IMPLEMENT_ONE_SIZE_PRIVATE_LOCAL_HEAP_LIST(CTRiASCSGeometryCollection);

#if defined(_DEBUG)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

/////////////////////////////////////////////////////////////////////////////
// RUNTIME_PERFINSTANCE_MAP
RT_PERFINSTANCEDATA_ENTRY(CTRiASCSGeometryCollection, g_cbCounts)

/////////////////////////////////////////////////////////////////////////////
//
STDMETHODIMP CTRiASCSGeometryCollection::get_Count (long * pVal)
{
	CHECKOUTPOINTER(pVal);

ObjectLock l(this);

	return m_Enum -> Count((ULONG *)pVal);
}

STDMETHODIMP CTRiASCSGeometryCollection::Remove (VARIANT Which)
{
	COM_TRY {
	// Index des gewünschten Punktes feststellen
	ObjectLock l(this);
	CComVariant vWhich;

		THROW_FAILED_HRESULT(vWhich.ChangeType (VT_I4, & Which));
#if defined(_DEBUG)
	ULONG ulCount = 0L;

		THROW_FAILED_HRESULT(m_Enum -> Count(& ulCount));
		_ASSERTE(-1 == V_I4(& vWhich) || (0 < V_I4(& vWhich) && V_I4(&vWhich) <= (LONG)ulCount));
#endif // _DEBUG
		THROW_FAILED_HRESULT(m_Enum -> RemoveItem (V_I4(& vWhich)));

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASCSGeometryCollection::Add (IDispatch * pIPoint, VARIANT Which)
{
	CHECKINPOINTER(pIPoint);
	COM_TRY {
		ERROR_EXPR_FALSE(V_ISINTEGER(&Which) || V_ISEMPTY(& Which) || V_ISERROR(& Which), TGEO_E_COERCE);
	
	ObjectLock l(this);
	ULONG nIndex = 0;

		if(V_ISINTEGER(& Which)) {
		// vorgegebener Index
		CComVariant vWhich(Which);
		
			WIN_ERROR_NOTSUCCESS(vWhich.ChangeType(VT_UI4), TGEO_E_COERCE);
			nIndex = V_UI4(& vWhich);
			ERROR_EXPR_TRUE(0 == nIndex, TGEO_E_INDEXISZERO);
		} else if(V_ISEMPTY(& Which) || V_ISERROR(& Which)) {
		// einfach anhängen
			nIndex = 0;
		} else {
			MAKE_ERROR(TGEO_E_INTERNAL);	// das sollte eigentlich nicht passieren
		}
		nIndex -= 1;		// in Enumeratoren wird von 0 aus gezählt...
		ERROR_FAILED_HRESULT(m_Enum -> AddItem (WDispatch(pIPoint), nIndex), TGEO_E_ACCESSELEMENT);

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASCSGeometryCollection::get_NewEnum (IUnknown * * ppIEnum)
{
	CHECKOUTPOINTER(ppIEnum);

ObjectLock l(this);

	return MakeEnumVARIANT (m_Enum, GetUnknown(), ppIEnum);
}

//STDMETHODIMP CTRiASCSGeometryCollection::Item (VARIANT Which, _DGMPoint **ppIPoint)
STDMETHODIMP CTRiASCSGeometryCollection::Item (VARIANT Which, IDispatch * * ppIPoint)
{
	CHECKOUTPOINTER(ppIPoint);
	COM_TRY	{
		ERROR_EXPR_FALSE(V_ISINTEGER(&Which), TGEO_E_COERCE);
	
	CComVariant vWhich(Which);
	
		WIN_ERROR_NOTSUCCESS(vWhich.ChangeType (VT_I4), TGEO_E_COERCE);
	
	ULONG nIndex = V_UI4(&vWhich);
	
		ERROR_EXPR_TRUE(0 == nIndex, TGEO_E_INDEXISZERO);
		nIndex -= 1;
	
	ObjectLock l(this);
	WDispatch disp;
	
		ERROR_FAILED_HRESULT(m_Enum -> GetItem (nIndex, &disp), TGEO_E_ACCESSELEMENT);
		*ppIPoint = disp.detach();

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASCSGeometryCollection::get_Type (BSTR * pVal)
{
	CHECKOUTPOINTER(pVal);

CComBSTR bstr (g_cbGeometryCollection);

	if (!bstr)
		return E_OUTOFMEMORY;
	*pVal = bstr.Detach();
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStream
HRESULT CTRiASCSGeometryCollection::IsDirty (void)
{
	if (m_fIsDirty)
		return S_OK;

// ganze Collection testen
HRESULT	hRes = S_FALSE;

	COM_TRY	{
	ObjectLock l(this);
	WEnumWDispatch Enum;
	WDispatch Point;

		THROW_FAILED_HRESULT(m_Enum -> Clone (Enum.ppi()));
		for (Enum -> Reset(); S_OK == Enum -> Next (1, & Point, NULL);)
		{
			hRes = WPersistStream(Point) -> IsDirty();
			if (S_OK == hRes)
				break;
		}

	} COM_CATCH;
	return hRes;
}

HRESULT CTRiASCSGeometryCollection::Load (LPSTREAM pStm)
{
	ERROR_EXPR_TRUE(m_fIsInitialized, STREAM_E_OBJECTALREADYINITIALIZED);
	CHECKINPOINTER(pStm);

	COM_TRY {
	ObjectLock lock(this);
	WDispatch Disp;
	long cnt;

		THROW_FAILED_HRESULT(LoadItem(pStm, cnt));
		for (long l = 0; l<cnt; l ++)
		{
			THROW_FAILED_HRESULT(::OleLoadFromStream (pStm, IID_IDispatch, Disp.ppv()));
			m_Enum -> AddItem (Disp, - 1L);
		}

	} COM_CATCH;

	m_fIsDirty = false;
	m_fIsInitialized = true;
	return S_OK;
}

HRESULT CTRiASCSGeometryCollection::Save (LPSTREAM pStm, BOOL fClearDirty)
{
	CHECKINPOINTER(pStm);

bool fWasDirty = false;

	if (!fClearDirty)
		fWasDirty = (S_OK == IsDirty()) ? true : false;

	COM_TRY	{
	ObjectLock l(this);
	WEnumWDispatch Enum;
	WDispatch Disp;
	ULONG ulCount = 0L;

		THROW_FAILED_HRESULT(m_Enum -> Clone (Enum.ppi()));
		THROW_FAILED_HRESULT(Enum -> Count (&ulCount));
		THROW_FAILED_HRESULT(SaveItem (pStm, ulCount));
		for (Enum -> Reset(); S_OK == Enum -> Next (1, &Disp, NULL); /**/)
		{
			THROW_FAILED_HRESULT(::OleSaveToStream (WPersistStream(Disp), pStm));
		}

	} COM_CATCH;

	if (fClearDirty)
		m_fIsDirty = false;
	else
		m_fIsDirty = fWasDirty;

	return S_OK;
}

HRESULT CTRiASCSGeometryCollection::GetSizeMax (ULARGE_INTEGER * pcbSize)
{
	CHECKINPOINTER(pcbSize);

	pcbSize -> QuadPart = 0;
	COM_TRY	{
	ObjectLock l(this);
	WEnumWDispatch Enum;
	WDispatch Disp;
	ULARGE_INTEGER temp;

		THROW_FAILED_HRESULT(m_Enum -> Clone (Enum.ppi()));
		for (Enum -> Reset(); S_OK == Enum -> Next (1, & Disp, NULL);)
		{
			WPersistStream(Disp) -> GetSizeMax (& temp);
			pcbSize -> QuadPart += temp.QuadPart;
		}

	} COM_CATCH;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit
HRESULT CTRiASCSGeometryCollection::InitNew (void)
{
	ERROR_EXPR_TRUE(m_fIsInitialized, STREAM_E_OBJECTALREADYINITIALIZED);

	RETURN_FAILED_HRESULT(CreateNewEnum (m_Enum.ppi()));
	m_fIsDirty = false;
	m_fIsInitialized = true;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistMemory
HRESULT CTRiASCSGeometryCollection::Load (void * pvMem, ULONG cbSize)
{
	CHECKINPOINTER(pvMem);

	COM_TRY {
	ObjectLock lock(this);
#if defined(_DEBUG)
	ULONG uiOrgSize = cbSize;
	void * pvStart = pvMem;
#endif // _DEBUG
	long cnt = 0;

		LoadAndAdvance(cnt, pvMem);
		cbSize -= sizeof(long);

		for (long l = 0; l<cnt; l ++) {
		// Größe des Objektes einlesen
		ULONG ulSize = 0;

			LoadAndAdvance(ulSize, pvMem);
#if defined(_DEBUG)
			cbSize -= ulSize;
			cbSize -= sizeof(long);
#endif // _DEBUG

		// Objekt erzeugen und einlesen
		GUID guid;

			LoadAndAdvance(guid, pvMem);
			ulSize -= sizeof(GUID);

//		MapOfGUIDS::iterator it = g_mapOfGUIDS.find(guid);
//
//			_ASSERTE(g_mapOfGUIDS.end() != it);
//			if (g_mapOfGUIDS.end() == it) {
//				ATLTRACE("Unbekannte TRiAS Geometrie: %s\n", os_string(CIID(guid)).c_str());
//				return E_FAIL;
//			}
//			guid = (*it).second;

#if defined(_USE_CLASSFACTORY_CACHE)
		WPersistMemory obj;

			THROW_FAILED_HRESULT(CClassFactoryMap::CreateInstance (guid, obj));	// Geometrieobjekt erzeugen
#else
		WPersistMemory obj (guid);		// Geometrieobjekt erzeugen
#endif // 	defined(_USE_CLASSFACTORY_CACHE)

			THROW_FAILED_HRESULT(obj -> Load(pvMem, ulSize));
			pvMem = (BYTE *)pvMem + ulSize;

		// neues Objekt zur Enumeration hinzufügen
			m_Enum -> AddItem (WDispatch(obj), - 1);
		}

		_ASSERTE(0 == cbSize);
		_ASSERTE(ULONG((BYTE *)pvMem - (BYTE *)pvStart) == uiOrgSize);

		m_fIsDirty = false;
		m_fIsInitialized = true;

	} COM_CATCH;
	return S_OK;
}

HRESULT CTRiASCSGeometryCollection::Save (void * pvMem, BOOL fClearDirty, ULONG cbSize)
{
	CHECKINPOINTER(pvMem);
	COM_TRY	{
	ObjectLock l(this);
	WEnumWDispatch Enum;
	WDispatch disp;

		THROW_FAILED_HRESULT(m_Enum -> Clone (Enum.ppi()));

	ULONG ulCnt = 0L;
	GUID guid;

		THROW_FAILED_HRESULT(Enum -> Count(&ulCnt));
		SaveAndAdvance(pvMem, ulCnt);
		cbSize -= sizeof(long);

		for (Enum -> Reset(); S_OK == Enum -> Next (1, & disp, NULL); /**/)	{
		WPersistMemory obj(disp);
		ULONG ulSize = 0;

			THROW_FAILED_HRESULT(obj -> GetSizeMax(&ulSize));
			SaveAndAdvance (pvMem, ulSize + sizeof(GUID));

			THROW_FAILED_HRESULT(obj -> GetClassID(&guid));
			SaveAndAdvance (pvMem, guid);

			THROW_FAILED_HRESULT(obj -> Save (pvMem, fClearDirty, ulSize));
			pvMem = (BYTE *)pvMem + ulSize;
		}
	} COM_CATCH;

	if (fClearDirty)
		m_fIsDirty = false;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistMemoryGDO
HRESULT CTRiASCSGeometryCollection::LoadGDO(VOID * pvMem, ULONG cbSize)
{
	CHECKINPOINTER(pvMem);
	COM_TRY	{
	ObjectLock lock(this);
#if defined(_DEBUG)
	ULONG uiOrgSize = cbSize;
	void * pvStart = pvMem;
#endif // _DEBUG

	long cnt = 0;
	GUID guid;
	MapOfGUIDS::iterator it;

		LoadAndAdvance(cnt, pvMem);
		cbSize -= sizeof(long);

		for (long l = 0; l<cnt; l ++)	{
		ULONG ulSize = 0;				// Größe des Objektes
		
			LoadAndAdvance(ulSize, pvMem);

#if defined(_DEBUG)
			cbSize -= ulSize;				// zu Prüfzwecken mitrechnen
			cbSize -= sizeof(long);
#endif
			LoadAndAdvance(guid, pvMem);
			ulSize -= sizeof(GUID);

			it = g_mapGDO2TRiAS.find(guid);
			ERROR_EXPR_TRUE(g_mapGDO2TRiAS.end() == it, TGEO_E_UNKNOWN_OBJECTTYPE);
			guid = (* it).second;

		WPersistMemoryGDO obj (guid);

			ERROR_FAILED_HRESULT(obj -> LoadGDO(pvMem, ulSize), STREAM_E_CANNOTLOADITEM);
			pvMem = (BYTE *) pvMem + ulSize;

		// neues Objekt zur Enumeration hinzufügen
			m_Enum -> AddItem (WDispatch(obj), - 1);
		}
#if defined(_DEBUG)
		ERROR_EXPR_FALSE(0 == cbSize, STREAM_E_CORRUPTED);
		ERROR_EXPR_FALSE(ULONG((BYTE *) pvMem - (BYTE *) pvStart) == uiOrgSize, STREAM_E_CORRUPTED);
#endif
		m_fIsDirty = false;
		m_fIsInitialized = true;
	} COM_CATCH;
	return S_OK;
}

HRESULT CTRiASCSGeometryCollection::SaveGDO(VOID * pvMem, BOOL fClearDirty, ULONG cbSize)
{
	CHECKINPOINTER(pvMem);
	COM_TRY {
	ObjectLock l(this);
	WEnumWDispatch Enum;

		ERROR_FAILED_HRESULT(m_Enum -> Clone(Enum.ppi()), E_FAIL);

	ULONG ulCnt = 0L;
	ULONG ulSize = 0L;
	GUID guid;
	MapOfGUIDS::iterator it;

		ERROR_FAILED_HRESULT(Enum -> Count(& ulCnt), E_FAIL);
		SaveAndAdvance(pvMem, ulCnt);
		cbSize -= sizeof(long);

	WDispatch disp;

		for (Enum -> Reset(); S_OK == Enum -> Next (1, & disp, NULL); /**/)	{
		WPersistMemoryGDO obj(disp);
		
			ERROR_FAILED_HRESULT(obj -> GetSizeMax(& ulSize), E_FAIL);
			ERROR_FAILED_HRESULT(obj -> GetClassID(& guid), E_FAIL);

		/////////////////////////////////////////////////////////////////////////////
		// Geomedia - GUID ummappen
			it = g_mapTRiAS2GDO.find(guid);
			ERROR_EXPR_TRUE(g_mapTRiAS2GDO.end() == it, TGEO_E_UNKNOWN_OBJECTTYPE);
			guid = (*it).second;

			SaveAndAdvance (pvMem, ulSize + sizeof(GUID));
			SaveAndAdvance (pvMem, guid);
			ERROR_FAILED_HRESULT(obj -> SaveGDO(pvMem, fClearDirty, ulSize), E_FAIL);
			pvMem = (BYTE *)pvMem + ulSize;
		}
		if (fClearDirty)
			m_fIsDirty = false;
	} COM_CATCH;
	return S_OK;
}

HRESULT CTRiASCSGeometryCollection::GetSizeMax (ULONG * pcbSize)
{
	CHECKOUTPOINTER(pcbSize);
	ERROR_EXPR_TRUE(! m_fIsInitialized, STREAM_E_OBJECTNOTINITIALIZED);

	*pcbSize = 0;
	COM_TRY {
	ObjectLock l(this);
	WEnumWDispatch Enum;
	WDispatch disp;
	ULONG temp;

		THROW_FAILED_HRESULT(m_Enum -> Clone (Enum.ppi()));
		for (Enum -> Reset(); S_OK == Enum -> Next (1, & disp, NULL); /**/)
		{
			WPersistMemory(disp) -> GetSizeMax (&temp);
			*pcbSize += temp + sizeof(GUID) + sizeof(long);
		}
		*pcbSize += sizeof(long);		// Anzahl der Blobs

	} COM_CATCH;
	return S_OK;
}

// ITRiASTransformGeometry
HRESULT CTRiASCSGeometryCollection::Transform(struct CSID csGUID, ITRiASCSTransform * pCSTransform)
{
	COM_TRY	{
	ObjectLock l(this);
	WEnumWDispatch Enum;
	WDispatch disp;

		THROW_FAILED_HRESULT(m_Enum -> Clone (Enum.ppi()));
		for (Enum -> Reset(); S_OK == Enum -> Next (1, & disp, NULL); /**/)
		{
			ERROR_FAILED_HRESULT(WTRiASTransformGeometry(disp) -> Transform(csGUID, pCSTransform), GCOLL_E_CANNOTTRANSFORMGEOMETRY);
		}

	} COM_CATCH;
	return S_OK;
}

HRESULT CTRiASCSGeometryCollection::TransformInverse(struct CSID csGUID, ITRiASCSTransform * pCSTransform)
{
	COM_TRY	{
	ObjectLock l(this);
	WEnumWDispatch Enum;
	WDispatch disp;

		THROW_FAILED_HRESULT(m_Enum -> Clone (Enum.ppi()));
		for (Enum -> Reset(); S_OK == Enum -> Next (1, &disp, NULL); /**/)
		{
				ERROR_FAILED_HRESULT(WTRiASTransformGeometry(disp) -> TransformInverse(csGUID, pCSTransform), GCOLL_E_CANNOTTRANSFORMGEOMETRY);
		}

	} COM_CATCH;
	return S_OK;
}

// ITRiASCloneGeometry
STDMETHODIMP CTRiASCSGeometryCollection::Clone (IDispatch * * ppIClonedObj)
{
	CHECKOUTPOINTER(ppIClonedObj);

CComObject<CTRiASCSGeometryCollection> *pNew = NULL;

	COM_TRY {
	ObjectLock l(this);

		THROW_FAILED_HRESULT(CComObject<CTRiASCSGeometryCollection > ::CreateInstance(& pNew));
		pNew -> AddRef();		// pending AddRef

	// alle Elemente des Enumerators kopieren
	WEnumWDispatch Enum, newEnum;
	WDispatch disp;

		newEnum = pNew -> m_Enum;
		THROW_FAILED_HRESULT(m_Enum -> Clone (Enum.ppi()));
		for (Enum -> Reset(); S_OK == Enum -> Next (1, & disp, NULL); /**/) {
		WDispatch newdisp;

			THROW_FAILED_HRESULT(WTRiASCloneGeometry(disp) -> Clone (newdisp.ppi()));
			THROW_FAILED_HRESULT(newEnum -> AddItem(newdisp, - 1));
		}

	// sonstige Werte kopieren
		pNew -> m_fIsDirty = false;
		pNew -> m_fIsInitialized = true;

	// Resultat liefern
		*ppIClonedObj = static_cast<_DGMGeometry *>(pNew);

	} COM_CATCH_OP (
		RELEASE(pNew);
	);
	return S_OK;
}

STDMETHODIMP CTRiASCSGeometryCollection::get_Type(/*[out, retval]*/ GEOMETRYTYPE * pVal)
{
	CHECKINPOINTER(pVal);

	*pVal = GEOMETRYTYPE_Collection;
	return S_OK;
}

STDMETHODIMP CTRiASCSGeometryCollection::get_Envelope (ITRiASSimpleRectangle * * Rect)
{
	CHECKINPOINTER(Rect);
	COM_TRY	{
	ObjectLock l(this);
	WEnumWDispatch Enum;
	WDispatch disp;
	CCSRectangleGeometry envelSum (INIT_DBL_MIN, INIT_DBL_MIN, INIT_DBL_MAX, INIT_DBL_MAX, 1);
	WTRiASSimpleRectangle envelCurr;
	
		THROW_FAILED_HRESULT(m_Enum -> Clone (Enum.ppi()));
		for (Enum -> Reset(); S_OK == Enum -> Next (1, & disp, NULL); /**/)	{
		WTRiASCSGeometryProperties(disp) -> get_Envelope (envelCurr.ppi());

#ifdef _DEBUG
		double x0, y0;
		W_DGMPoint pt;

			envelCurr -> get_Origin (pt.ppi());
			pt -> get_X (&x0);
			pt -> get_Y (&y0);
			if (0 == x0 || 0 == y0) {
				_ASSERTE(0);
				WTRiASCSGeometryProperties(disp) -> get_Envelope (envelCurr.ppi());	// schauen wir doch nochmal... ;-))
			}
#endif
			envelSum = envelSum + CCSRectangleGeometry(envelCurr);
		}
		*Rect = envelSum.detach();	// Rect ist jetzt Owner des Rechteckes

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASCSGeometryCollection::get_InitString (BSTR *pbstrMkName)
{
	return E_NOTIMPL;
}

STDMETHODIMP CTRiASCSGeometryCollection::put_InitString (BSTR bstrMkName)
{
	return E_NOTIMPL;
}

///////////////////////////////////////////////////////////////////////////////
// OGC well-known binary format
HRESULT CTRiASCSGeometryCollection::GetSizeMaxWkb(ULONG *pcbSize)
{
	CHECKOUTPOINTER(pcbSize);
	ERROR_EXPR_TRUE(! m_fIsInitialized, STREAM_E_OBJECTNOTINITIALIZED);

	*pcbSize = sizeof(BYTE)+sizeof(UINT)+sizeof(UINT);
	COM_TRY {
	ObjectLock l(this);
	WEnumWDispatch Enum;
	WDispatch disp;
	ULONG temp;

		THROW_FAILED_HRESULT(m_Enum -> Clone (Enum.ppi()));
		for (Enum -> Reset(); S_OK == Enum -> Next (1, & disp, NULL); /**/)
		{
			WPersistMemoryWks(disp) -> GetSizeMax (&temp);
			*pcbSize += temp;
		}
		*pcbSize += sizeof(long);		// Anzahl der Blobs

	} COM_CATCH;
	return S_OK;
}

HRESULT CTRiASCSGeometryCollection::LoadWkb(LPVOID pMem, ULONG cbSize)
{
	return E_NOTIMPL;
}

HRESULT CTRiASCSGeometryCollection::SaveWkb(LPVOID pvMem, BOOL fClearDirty, ULONG cbSize)
{
	CHECKINPOINTER(pvMem);
	COM_TRY	{
	ObjectLock l(this);
	WEnumWDispatch Enum;
	WDispatch disp;

		THROW_FAILED_HRESULT(m_Enum -> Clone (Enum.ppi()));

	ULONG ulCnt = 0L;

		THROW_FAILED_HRESULT(Enum -> Count(&ulCnt));

		SaveAndAdvance(pvMem, (BYTE)wkbNDR);
		SaveAndAdvance(pvMem, (UINT)wkbGeometryCollection);
		SaveAndAdvance(pvMem, (UINT)ulCnt);

		for (Enum -> Reset(); S_OK == Enum -> Next (1, & disp, NULL); /**/)	{
		WPersistMemoryWks obj(disp);
		ULONG ulSize = 0;

			THROW_FAILED_HRESULT(obj -> GetSizeMaxWkb(&ulSize));
			THROW_FAILED_HRESULT(obj -> SaveWkb (pvMem, fClearDirty, ulSize));
			pvMem = (BYTE *)pvMem + ulSize;
		}
	
	} COM_CATCH;

	if (fClearDirty)
		m_fIsDirty = false;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// OGC well-known text format
HRESULT CTRiASCSGeometryCollection::LoadWkt(BSTR WKT)
{
	return E_NOTIMPL;
}

HRESULT CTRiASCSGeometryCollection::SaveWkt(BSTR *pbstrWKT, BOOL fClearDirty)
{
	CHECKOUTPOINTER(pbstrWKT);
	COM_TRY	{
	ObjectLock l(this);
	WEnumWDispatch Enum;
	WDispatch disp;
	CComBSTR bstrWKT (L"GEOMETRYCOLLECTION(");

		THROW_FAILED_HRESULT(m_Enum -> Clone (Enum.ppi()));
		for (Enum -> Reset(); S_OK == Enum -> Next (1, &disp, NULL); /**/)	{
		WPersistMemoryWks obj(disp);
		CComBSTR bstr;

			THROW_FAILED_HRESULT(obj -> SaveWkt (&bstr, fClearDirty));
			bstrWKT.AppendBSTR(bstr);
		}
		bstrWKT.Append(L")");
		
		*pbstrWKT = bstrWKT.Detach();

	} COM_CATCH;

	if (fClearDirty)
		m_fIsDirty = false;
	return S_OK;
}

