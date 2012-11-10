// Diverse Hilfsfunktionen für den Umgang mit unserem CDataObject -------------
// File: DataObjectHelp.h
// H. Kaiser

#ifndef _DATAOBJECTHELP_H
#define _DATAOBJECTHELP_H


_GEOMETR_ENTRY HRESULT CreateStreamOnHGlobalFromIUnknown (IUnknown *pIUnk, IStream **ppIStream);
_GEOMETR_ENTRY HRESULT CreateEnumLONGFromStream (IStream *pIStream, REFIID riid, LPVOID *ppEnumOut);
_GEOMETR_ENTRY HRESULT SetEnumLONGData (IEnum<LONG> *pIEnum, IDataObject *pIDataObj);
_GEOMETR_ENTRY HRESULT GetEnumLONGData (IDataObject *pIDataObj, IEnum<LONG> **ppIEnumOut = NULL);
_GEOMETR_ENTRY HRESULT GetEnumLONGData (IDataObject *pIDataObj, REFIID riid, LPVOID *ppv = NULL);
_GEOMETR_ENTRY HRESULT SetHWNDData (HWND hWnd, IDataObject *pDataObj);
_GEOMETR_ENTRY HRESULT GetHWNDData (IDataObject *pIDataObj, HWND *phWnd);
//_GEOMETR_ENTRY HRESULT SetVariantData (CComVariant &rv, IDataObject *pIDO, const FORMATETC *pcfe);
//_GEOMETR_ENTRY HRESULT GetVariantData (IDataObject *pIDO, const FORMATETC *pcfe, CComVariant *pv);
_GEOMETR_ENTRY HRESULT GetPacketNumber (IDataObject *pIDO, long *plNumber);
_GEOMETR_ENTRY HRESULT SetPacketNumber (IDataObject *pIDO, long lNumber);

#endif // _DATAOBJECTHELP_H
