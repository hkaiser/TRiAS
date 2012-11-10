// Diverse Hilfsfunktionen für den Umgang mit unserem CDataObject -------------
// File: DATAHELP.HPP

#ifndef _DATA_HELP_HPP
#define _DATA_HELP_HPP


template<class T>
inline HRESULT LoadData (IStream *pIStm, T &riVal)
{
	return pIStm -> Read (&riVal, sizeof(T), NULL);
}

template<class T>
inline HRESULT SaveData (IStream *pIStm, T &riVal)
{
	return pIStm -> Write (&riVal, sizeof(T), NULL);
}

// Lesen eines EnumLONG aus einem DataObjekt
HRESULT GetEnumLONGData (IDataObject *pIDataObj, IEnumObjectsByNumber **ppIEnumOut);

// Hinzufügen eines EnumLONG zu einem IDataObject
HRESULT SetEnumLONGData (IEnumObjectsByNumber *pEnum, IDataObject *pDataObj);

HRESULT GetVariantData (IDataObject *pIDO, const FORMATETC *pcfe, CComVariant *pv);
HRESULT SetVariantData (CComVariant &rv, IDataObject *pIDO, const FORMATETC *pcfe);

#endif // _DATA_HELP_HPP


