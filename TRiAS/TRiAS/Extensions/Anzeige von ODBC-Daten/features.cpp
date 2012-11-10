//
// feature name<->code handling
//

#include "pheader.h"
#include "features.h"
#include <ospace/com/smartif.h>
/*
#import "tlb/TRiASDB.tlb"	raw_interfaces_only raw_dispinterfaces no_namespace	named_guids \
	exclude("IPersistStreamInit", "IPersist", "IStream", "ISequentialStream") \
	exclude("_LARGE_INTEGER", "_ULARGE_INTEGER", "tagSTATSTG", "_FILETIME")
*/
//DefineSmartInterface(TRiASConnection);
DefineSmartInterface(TRiASDatabase);
DefineSmartInterface(TRiASObjectHandleMap);
DefineSmartInterface(TRiASObjects);
DefineSmartInterface(TRiASFeature);


HRESULT GetFeatureHandle (INT_PTR lIdent, LPCSTR pcName, INT_PTR *phFeat)
{
	if (NULL == phFeat)
		return E_POINTER;
	
	*phFeat = NULL;

WTRiASFeature Feat;

	// Kein RETURN_FAILED_HRESULT, da es kein Fehler ist wenn zu einer Klasse eine nicht dazugehörende 
	// Eigenschaft nicht gefunden wird (hier ist die ASSERTION richtig doof) 
	HRESULT hr = GetFeature (lIdent, pcName, Feat.ppi());
	if (FAILED(hr))
		return hr;

INT_PTR lHandle = NULL;

	RETURN_FAILED_HRESULT(Feat -> get_Handle (&lHandle));
	*phFeat = lHandle;
	return S_OK;
}

HRESULT GetFeature (INT_PTR lIdent, LPCSTR pcName, ITRiASFeature **ppIFeat)
{
WTRiASObjects Objs;
HRESULT hr = GetObjectsDef (lIdent, Objs.ppi());

	if (FAILED(hr))
		return hr;
			
	return Objs -> get_Feature (CComVariant(pcName), VARIANT_FALSE, CComBSTR(""), ppIFeat);
}

HRESULT GetObjectsDef (ULONG ulIdent, ITRiASObjects **ppIObjs)
{
	if (NULL == ppIObjs)
		return E_POINTER;
	*ppIObjs = NULL;

	COM_TRY {
	// aus Database-Tabelle entfernen
	WTRiASObjectHandleMap Map (CLSID_TRiASObjectsHandleMap);
	WTRiASObjects Objs;
	
	// wiederauffinden des Objects-Objektes
		if (!Map || 0 == ulIdent || FAILED(Map -> GetObject (ulIdent, Objs.ppu()))) 
			return /*HRESULT_FROM_ERRCODE(WC_NOTFOUND);/*/ E_FAIL;
				   
		*ppIObjs = Objs.detach();

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// GetFeatureName
HRESULT GetFeatureName (INT_PTR hFeat, LPSTR pBuffer, int iLen)
{
	USES_CONVERSION;

	COM_TRY {
	WTRiASObjectHandleMap Map (CLSID_TRiASFeatureHandleMap);

		if (!Map.IsValid())
			return E_FAIL;

	WTRiASFeature Feat;
		// Kein RETURN_FAILED_HRESULT, da es kein Fehler ist wenn zu einer Klasse eine nicht dazugehörende 
		// Eigenschaft nicht gefunden wird (hier ist die ASSERTION richtig doof) 
		HRESULT hr = Map -> GetObject (hFeat, Feat.ppu());
		if (FAILED(hr))
			return hr;

	CComBSTR bstrName;
	
		THROW_FAILED_HRESULT(Feat -> get_Name (&bstrName));

	int iToCopy = min ((UINT)iLen-1, bstrName.Length());

		strncpy (pBuffer, OLE2A( bstrName ), iToCopy);
		pBuffer[iToCopy] = '\0';

	} COM_CATCH;
	return S_OK;
}
