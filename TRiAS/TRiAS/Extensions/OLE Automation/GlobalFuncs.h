// File: GlobalFuncs.h

#if !defined(_GLOBALFUNCS_H)
#define _GLOBALFUNCS_H

///////////////////////////////////////////////////////////////////////////////
// globale Funktionen
HRESULT GetEnumLongFromGeoObjects (_DGeoObjects *pIObjs, IEnumLONG **ppIEnum);
HRESULT GetGeoObjectsFromEnumlong (IEnumLONG *pIEnum, _DGeoObjects **ppIObjs);

HRESULT SetEnumLONGData (IEnumLONG *pEnum, IDataObject *pDataObj);
HRESULT GetEnumLONGData (IDataObject *pIDataObj, IEnumLONG **ppIEnumOut);

HRESULT CreateItemMonikerFromEnumLONG (IEnumLONG *pEnum, IMoniker **ppIMk);
HRESULT SetMonikerData (IMoniker *pIMk, IDataObject *pIDO, const FORMATETC *pcfe);
HRESULT GetMonikerData (IDataObject *pIDO, const FORMATETC *pcfe, IMoniker **ppIMk = NULL);
HRESULT BindMonikerFromDataObject (IDataObject *pIDO, const FORMATETC *pcfe, REFIID riid, LPVOID *ppv);

HRESULT SetVariantData (CComVariant &rv, IDataObject *pIDO, const FORMATETC *pcfe);
HRESULT GetVariantData (IDataObject *pIDO, const FORMATETC *pcfe, CComVariant *pv = NULL);

#endif // _GLOBALFUNCS_H
