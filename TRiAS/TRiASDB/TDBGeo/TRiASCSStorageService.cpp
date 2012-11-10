// $Header: /TRiAS/TRiASDB/TDBGeo/TRiASCSStorageService.cpp 1	 15.06.98 21:26 Hartmut Kaiser $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 06/13/1998 08:52:22 PM
//
// @doc
// @module TRiASCSStorageService.cpp | Implementation of the <c CTRiASCSStorageService> class

#include "stdafx.h"
#include "TDBGeoImpl.h"

#include <Com/CStructHelper.h>
#include <Com/MemoryHelper.h>
#include <Com/InMemoryStream.h>

#include "TRiASCSStorageService.h"

/////////////////////////////////////////////////////////////////////////////
// CTRiASCSStorageService

STDMETHODIMP CTRiASCSStorageService::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID *arr[] =
	{
		 &IID_ITRiASCSStorageService,
		 &IID_ITRiASCSStorageServiceGDO,
		 &IID_ITRiASCSStorageServiceWks,
	};
	for (int i = 0;i<sizeof(arr) / sizeof(arr[0]);i ++)
	{
		if (InlineIsEqualGUID(* arr[i], riid))
			return S_OK;
	}
	return S_FALSE;
}

namespace
{
	typedef struct tagGEOMETRYNAMEANDTYPE {
		const OLECHAR * pcoleType;
		GEOMETRYTYPE rgType;
	} GEOMETRYNAMEANDTYPE;

	const GEOMETRYNAMEANDTYPE g_cbTypes[] =
	{
		{ g_cbPointGeometry, GEOMETRYTYPE_Point }, 					// Punkt
		{ g_cbOrientedPointGeometry, GEOMETRYTYPE_OrientedPoint },
		{ g_cbPolylineGeometry, GEOMETRYTYPE_Line }, 				// Linie
		{ g_cbPolygonGeometry, GEOMETRYTYPE_Area }, 				// Fläche
		{ g_cbRectangleGeometry, GEOMETRYTYPE_Area }, 				// (Rechtecks-)Fläche
		{ g_cbTextPointGeometry, GEOMETRYTYPE_Text }, 				// Text
		{ g_cbBoundaryGeometry, GEOMETRYTYPE_Boundary }, 			// Fläche mit Inseln
		{ g_cbGeometryCollection, GEOMETRYTYPE_Collection }, 		// GeometryCollection
		{ g_cbLineGeometry, GEOMETRYTYPE_Line }, 					// Linie (Stützstrecke)
		{ NULL, GEOMETRYTYPE_Unknown }, 							// Endekennung
	};

	class CMapGeomType :
		public map<CComBSTR, GEOMETRYTYPE, less<CComBSTR> >
	{
		public:
		CMapGeomType()
		{
			for (const GEOMETRYNAMEANDTYPE * p = g_cbTypes; NULL != p -> pcoleType; p ++)
				insert(value_type(CComBSTR(p -> pcoleType), p -> rgType));
		}
		GEOMETRYTYPE GetType (BSTR bstrType)
		{
			iterator it = find (CComBSTR(bstrType));

			if (it != end())
				return (* it).second;
			return GEOMETRYTYPE_Unknown;
		}
	};
	CMapGeomType g_mapGeomTypes;

// DISPID der Type-Property eines Geometrieobjektes
	#define TYPE_DISPID	0x60020000

} // namespace

STDMETHODIMP CTRiASCSStorageService::RetrieveType (IDispatch * pIDisp, GEOMETRYTYPE * prgType)
{
	return RetrieveGeometryType (pIDisp, prgType);
}

/*static*/
HRESULT CTRiASCSStorageService::RetrieveGeometryType (
	IDispatch *pIDisp, GEOMETRYTYPE *prgType)
{
	COM_TRY {
	// wenns eins von unseren Objekten ist
	WTRiASCSGeometryProperties Native;

		if (SUCCEEDED(pIDisp -> QueryInterface (Native.ppi())))
			return Native -> get_Type (prgType);

	W_DGMGeometry Geom;
	CComBSTR bstrType;

		if (SUCCEEDED(pIDisp -> QueryInterface (IID__DGMGeometry, Geom.ppv())))
		{
			THROW_FAILED_HRESULT(Geom -> get_Type (CLEARED(& bstrType)));
		}
		else
		{
			THROW_FAILED_HRESULT(_com_dispatch_propget(pIDisp, TYPE_DISPID, VT_BSTR, CLEARED(& bstrType)));
		}

	// jetzt GeometrieTyp in Tabelle wiederfinden
		*prgType = g_mapGeomTypes.GetType(bstrType);
		if (GEOMETRYTYPE_Unknown == * prgType)
			return E_UNEXPECTED;		// nichts gefunden

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASCSStorageService::StorageToGeometry(
	VARIANT Blob, GEOMETRYTYPE *prgType, IDispatch **ppIGeometry)
{
	CHECKOUTPOINTER(ppIGeometry);
	COM_TRY	{
	CSafeArray sa (VT_UI1);

		if (V_VT(&Blob) == VT_BSTR) {
		// Daten kommen als BSTR
		SAFEARRAY *psa = NULL;

			THROW_FAILED_HRESULT(VectorFromBstr(V_BSTR(&Blob), &psa));
			if (!sa.Attach(psa, false))
				return E_UNEXPECTED;
		}
		else if (V_VT(&Blob) == (VT_ARRAY | VT_UI1)) {
		// Daten kommen als SafeArray
			if (!sa.Attach (V_ARRAY(&Blob), true))
				return E_INVALIDARG;
		}
		else
			return E_INVALIDARG;

		{
		CSafeArrayLock<BYTE> lock(sa);
		WPersistMemory PM;
#if defined(_USE_CLASSFACTORY_CACHE)
		WUnknown Unk;

			THROW_FAILED_HRESULT(CClassFactoryMap::CreateInstance (*(GUID *)(BYTE *)lock, Unk));	// Geometrieobjekt erzeugen
#else
		WUnknown Unk (*(GUID *)(BYTE *)lock);		// Geometrieobjekt erzeugen
#endif // 	defined(_USE_CLASSFACTORY_CACHE)

			if (SUCCEEDED(Unk -> QueryInterface (PM.ppi()))) {
			// Objekt unterstützt direkte Initialisierung über IPersistMemory
				THROW_FAILED_HRESULT(PM -> Load (lock + sizeof(GUID), lock.Size() - sizeof(GUID)));

			WDispatch disp (PM);
			
				ERROR_FAILED_HRESULT(RetrieveGeometryType(disp, prgType), TGEO_E_UNKNOWN_OBJECTTYPE);
				*ppIGeometry = disp.detach();
			} else
				return E_FAIL;	// Objekt unterstützt nicht direktes laden aus Speicher, GeoMedia-Objekt
		}	// lock goes out of scope

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASCSStorageService::GeometryToStorage(
	GEOMETRYTYPE rgType, IDispatch *pIGeometry, VARIANT *pBlob)
{
	CHECKOUTPOINTER(pBlob);
	COM_TRY	{
	WPersistMemory PS;

		if (SUCCEEDED(pIGeometry -> QueryInterface(PS.ppi()))) {
		// Objekt unterstützt direktes Speichern über IPersistMemory
		ULONG ulSize = 0;
		GUID guid;

			THROW_FAILED_HRESULT(PS -> GetSizeMax (& ulSize));
			THROW_FAILED_HRESULT(PS -> GetClassID(& guid));

		CSafeArray sa (VT_UI1, ulSize + sizeof(GUID));

			{
			CSafeArrayLock<BYTE> lock(sa);

				memcpy (lock, &guid, sizeof(GUID));
				THROW_FAILED_HRESULT(PS -> Save (lock + sizeof(GUID), false, ulSize));
			}

		CComVariant vBlob;

			V_VT(& vBlob) = VT_ARRAY | VT_UI1;
			V_ARRAY(& vBlob) = sa.Detach();
			return vBlob.Detach (pBlob);		// fertig und raus
		} else
			return E_FAIL;	// Objekt unterstützt nicht direktes speichern in Speicher, GeoMedia-Objekt

	} COM_CATCH;
	return S_OK;
}

// Implementation of StorageToObject
STDMETHODIMP CTRiASCSStorageService::StorageToObject(VARIANT Blob, 
	IDispatch **ppIObject)
{
	CHECKOUTPOINTER(ppIObject);
	COM_TRY	{
	CSafeArray sa (VT_UI1);

		if (V_VT(&Blob) == VT_BSTR) {
		// Daten kommen als BSTR
		SAFEARRAY *psa = NULL;

			THROW_FAILED_HRESULT(VectorFromBstr(V_BSTR(&Blob), &psa));
			if (!sa.Attach(psa, false))
				return E_UNEXPECTED;
		}
		else if (V_VT(&Blob) == (VT_ARRAY | VT_UI1)) {
		// Daten kommen als SafeArray
			if (!sa.Attach (V_ARRAY(&Blob), true))
				return E_INVALIDARG;
		}
		else
			return E_INVALIDARG;

		{
		// Objekt aus dem gegebenen Speicherblock auslesen
		CSafeArrayLock<BYTE> lock(sa);
		WStream Strm;
		WUnknown Unk;

			THROW_FAILED_HRESULT(CreateStreamOnTaskMem (lock, FALSE, Strm.ppi()));
			THROW_FAILED_HRESULT(OleLoadFromStream(Strm, IID_IUnknown, Unk.ppv()));

		WDispatch Disp (Unk);

			*ppIObject = Disp.detach();
		}	// lock goes out of scope

	} COM_CATCH;
	return S_OK;
}

// Implementation of ObjectToStorage
STDMETHODIMP CTRiASCSStorageService::ObjectToStorage(IDispatch *pIObject, VARIANT *pBlob)
{
	CHECKOUTPOINTER(pBlob);
	COM_TRY	{
	// Objekt in einen Speicherblock speichern
	CMallocMem<BYTE> Mem;
	WStream Strm;

		THROW_FAILED_HRESULT(CreateStreamOnTaskMem (NULL, TRUE, Strm.ppi()));
		THROW_FAILED_HRESULT(OleSaveToStream (WPersistStream(pIObject), Strm));
		THROW_FAILED_HRESULT(GetTaskMemFromStream (Strm, TRUE, reinterpret_cast<void **>(&Mem)));

	CSafeArray sa (VT_UI1, Mem.GetSize());

		{
		CSafeArrayLock<BYTE> lock(sa);

			memcpy (lock, Mem, Mem.GetSize());
		}

	CComVariant vBlob;

		V_VT(&vBlob) = VT_ARRAY | VT_UI1;
		V_ARRAY(&vBlob) = sa.Detach();
		return vBlob.Detach(pBlob);		// fertig und raus

	} COM_CATCH;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// ITRiASCSStorageServiceGDO

STDMETHODIMP CTRiASCSStorageService::StorageToGeometryGDO(
	VARIANT Blob, GEOMETRYTYPE *prgType, IDispatch **ppIGeometry)
{
	CHECKOUTPOINTER(prgType);
	CHECKOUTPOINTER(ppIGeometry);

	COM_TRY	{
		ERROR_EXPR_TRUE(V_VT(& Blob) != (VT_ARRAY | VT_UI1), E_INVALIDARG);

	CSafeArray sa(VT_UI1);
	
		ERROR_EXPR_TRUE(!sa.Attach(V_ARRAY(& Blob), true), E_INVALIDARG);

	GUID guidOfGeometry;
	WUnknown pUnknownOfGeometry;

		{
		CSafeArrayLock<BYTE> lock(sa);

			memcpy (&guidOfGeometry, lock, sizeof(GUID));

		MapOfGUIDS::iterator i = g_mapGDO2TRiAS.find (guidOfGeometry);
		
			ERROR_EXPR_TRUE(g_mapGDO2TRiAS.end() == i, S_FALSE);	// ist uns unbekannt... soll's der Aufrufer versuchen...
			guidOfGeometry = (*i).second;

		WUnknown pUnknown;
		WPersistMemoryGDO pPersistMemoryGDO;
		
			ERROR_FAILED_HRESULT(pUnknown.CreateInstance(guidOfGeometry), E_FAIL);
			ERROR_FAILED_HRESULT(pUnknown -> QueryInterface(pPersistMemoryGDO.ppi()), E_NOINTERFACE);
			ERROR_FAILED_HRESULT(pPersistMemoryGDO -> LoadGDO(lock + sizeof(GUID), lock.Size() - sizeof(GUID)), STREAM_E_CANNOTLOADITEM);
			pUnknownOfGeometry = pPersistMemoryGDO;
		} // lock goes out of scope

	// einfache Liniengeometrien müssen noch in Polylines umgebaut werden; sonst
	// stolpert TRiAS
		if(IsEqualGUID(CLSID_TRiASCSLineGeometry, guidOfGeometry)) {
		// die alte Line
		W_DGMLineGeometry	p_DGMLineGeometry;

			ERROR_FAILED_HRESULT(pUnknownOfGeometry -> QueryInterface(p_DGMLineGeometry.GetIID(), p_DGMLineGeometry.ppv()), E_FAIL);

		// die neue Line
		W_DGMPolylineGeometry	p_DGMPolylineGeometry;
		W_DGMPoints				p_DGMPoints;
		W_DGMPoint				p_DGMPoint;

			ERROR_FAILED_HRESULT(p_DGMPolylineGeometry.CreateInstance(CLSID_TRiASCSPolylineGeometry), E_FAIL);

		WPersistStreamInit	pPersistStreamInit;

			ERROR_FAILED_HRESULT(p_DGMPolylineGeometry -> QueryInterface(pPersistStreamInit.GetIID(), pPersistStreamInit.ppv()), E_FAIL);
			ERROR_FAILED_HRESULT(pPersistStreamInit -> InitNew(), E_FAIL);

		// jetzt umbauen
		long lCount;

			ERROR_FAILED_HRESULT(p_DGMPolylineGeometry -> get_Points(p_DGMPoints.ppi()), E_FAIL);
			ERROR_FAILED_HRESULT(p_DGMPoints -> get_Count(& lCount), E_FAIL);
			ERROR_EXPR_FALSE(0 == lCount, E_FAIL);
			ERROR_FAILED_HRESULT(p_DGMLineGeometry -> get_Start(p_DGMPoint.ppi()), E_FAIL);
			ERROR_FAILED_HRESULT(p_DGMPoints -> Add(p_DGMPoint, vtMissing), E_FAIL);
			ERROR_FAILED_HRESULT(p_DGMLineGeometry -> get_End(p_DGMPoint.ppi()), E_FAIL);
			ERROR_FAILED_HRESULT(p_DGMPoints -> Add(p_DGMPoint, vtMissing), E_FAIL);
			pUnknownOfGeometry = p_DGMPolylineGeometry;
		}

	WDispatch pDispatchOfGeometry(pUnknownOfGeometry);

		ERROR_FAILED_HRESULT(RetrieveGeometryType(pDispatchOfGeometry, prgType), TGEO_E_UNKNOWN_OBJECTTYPE);
		*ppIGeometry = pDispatchOfGeometry.Detach();

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASCSStorageService::GeometryToStorageGDO(GEOMETRYTYPE rgType, IDispatch * pIGeometry, VARIANT * pBlob)
{
	CHECKINPOINTER(pIGeometry);
	CHECKOUTPOINTER(pBlob);
	COM_TRY	{
	// Beim Speichern können nur unsere Objekte kommen und die *müssen* auch unsere
	// Interfaces unterstützen
	WPersistMemoryGDO PS;

		ERROR_FAILED_HRESULT(pIGeometry -> QueryInterface(PS.ppi()), E_NOINTERFACE);

	ULONG ulSize = 0;
	GUID guid;

		ERROR_FAILED_HRESULT(PS -> GetSizeMax(& ulSize), STREAM_E_INVALIDSIZE);
		ERROR_FAILED_HRESULT(PS -> GetClassID(& guid), TGEO_E_INVALID_OBJECTSTATE);

	MapOfGUIDS::iterator i = g_mapTRiAS2GDO.find(guid);

		ERROR_EXPR_TRUE(g_mapTRiAS2GDO.end() == i, TGEO_E_UNKNOWN_OBJECTTYPE);
		guid = (*i).second;

	CSafeArray sa(VT_UI1, ulSize + sizeof(GUID));

		{
		CSafeArrayLock<BYTE > lock(sa);

			memcpy (lock, &guid, sizeof(GUID));
			ERROR_FAILED_HRESULT(PS -> SaveGDO(lock + sizeof(GUID), false, ulSize), STREAM_E_CANNOTSAVEITEM);
		}	// lock geht 'out of scope'

	CComVariant vBlob;

		V_VT(& vBlob) = VT_ARRAY | VT_UI1;
		V_ARRAY(& vBlob) = sa.Detach();
		ERROR_FAILED_HRESULT(vBlob.Detach (pBlob), STREAM_E_CANNOTSAVEITEM);

	} COM_CATCH;
	return S_OK;
}

// Implementation of GeometryToStorageWkb
STDMETHODIMP CTRiASCSStorageService::GeometryToStorageWkb(GEOMETRYTYPE rgType, IDispatch *pIGeometry, VARIANT *pBlob)
{
	CHECKOUTPOINTER(pBlob);
	COM_TRY	{
	WPersistMemoryWks PS;

		if (SUCCEEDED(pIGeometry -> QueryInterface(PS.ppi()))) {
		// Objekt unterstützt direktes Speichern über IPersistMemory
		ULONG ulSize = 0;
		GUID guid;

			THROW_FAILED_HRESULT(PS -> GetSizeMax (& ulSize));
			THROW_FAILED_HRESULT(PS -> GetClassID(& guid));

		CSafeArray sa (VT_UI1, ulSize + sizeof(GUID));

			{
			CSafeArrayLock<BYTE > lock(sa);

				memcpy (lock, & guid, sizeof(GUID));
				THROW_FAILED_HRESULT(PS -> SaveWkb (lock + sizeof(GUID), false, ulSize));
			}

		CComVariant vBlob;

			V_VT(& vBlob) = VT_ARRAY | VT_UI1;
			V_ARRAY(& vBlob) = sa.Detach();
			return vBlob.Detach (pBlob);		// fertig und raus
		} else
			return E_FAIL;	// Objekt unterstützt nicht direktes speichern in Speicher, GeoMedia-Objekt

	} COM_CATCH;
	return S_OK;
}

// Implementation of StorageToGeometryWkb
STDMETHODIMP CTRiASCSStorageService::StorageToGeometryWkb(VARIANT Blob, GEOMETRYTYPE *prgType, IDispatch **ppIGeometry)
{
	CHECKOUTPOINTER(ppIGeometry);
	COM_TRY	{
	CSafeArray sa (VT_UI1);

		if (V_VT(&Blob) != (VT_ARRAY | VT_UI1) || ! sa.Attach (V_ARRAY(&Blob), true))
			return E_INVALIDARG;

		{
		CSafeArrayLock<BYTE> lock(sa);
		WPersistMemoryWks PM;
#if defined(_USE_CLASSFACTORY_CACHE)
		WUnknown Unk;

			THROW_FAILED_HRESULT(CClassFactoryMap::CreateInstance (*(GUID *)(BYTE *)lock, Unk));	// Geometrieobjekt erzeugen
#else
		WUnknown Unk (*(GUID *)(BYTE *)lock);		// Geometrieobjekt erzeugen
#endif // 	defined(_USE_CLASSFACTORY_CACHE)

			if (SUCCEEDED(Unk -> QueryInterface (PM.ppi()))) {
			// Objekt unterstützt direkte Initialisierung über IPersistMemory
				THROW_FAILED_HRESULT(PM -> LoadWkb (lock + sizeof(GUID), lock.Size() - sizeof(GUID)));

			WDispatch disp (PM);
			
				ERROR_FAILED_HRESULT(RetrieveGeometryType(disp, prgType), TGEO_E_UNKNOWN_OBJECTTYPE);
				*ppIGeometry = disp.detach();
			} else
				return E_FAIL;	// Objekt unterstützt nicht direktes laden aus Speicher, GeoMedia-Objekt
		} // lock goes out of scope

	} COM_CATCH;
	return S_OK;
}

// Implementation of GeometryToStorageWkt
STDMETHODIMP CTRiASCSStorageService::GeometryToStorageWkt(GEOMETRYTYPE rgType, IDispatch *Geometry, BSTR *Wkt)
{
	return E_NOTIMPL;
}

// Implementation of StorageToGeometryWkt
STDMETHODIMP CTRiASCSStorageService::StorageToGeometryWkt(BSTR Wkt, GEOMETRYTYPE *prgType, IDispatch **Geometry)
{
	return E_NOTIMPL;
}

