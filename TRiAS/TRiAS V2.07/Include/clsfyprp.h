// Allgemeines zur PropertyAction 'CLSID_ClassifyByObjProp' -------------------
// File: CLSFYPRP.H

#if !defined(_CLSFYPRP_H)
#define _CLSFYPRP_H

// GUID ///////////////////////////////////////////////////////////////////////
// 0E54C9E0-20DE-11CF-BA55-00AA0018497C	
DEFINE_GUID(CLSID_ClassifyByObjProp, 0x0E54C9E1L, 0x20DE, 0x11CF, 0xBA, 0x55, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);

// Name ///////////////////////////////////////////////////////////////////////
const char c_cbClsfyPrpName[] = "CLSPROP_ROOT\\Recherche\\Gruppieren von Objekten";

// Erzeugte ZusatzInfos ///////////////////////////////////////////////////////
//
// 1. Info über Objekteigenschaft, nach der klassifiziert wurde
// Objekteigenschaft mit dem für eine Klassifikation verwendeten Wert. 
// Diese Objekteigenschaft (PropertyTemplate) ist in einen Stream serialisiert, 
// der im IDataObject übergeben wird.
// 
// ClipBoardFormat
const char c_cbPAObjectProperty[] = "PersistObjectProperty";
//
// FORMATETC
const FORMATETC c_feClassifyObjects = {
	RegisterClipboardFormat (c_cbPAObjectProperty),	// CLIPFORMAT cf
	NULL,											// DVTARGETDEVICE *ptd
	DVASPECT_CONTENT,								// DWORD dwAspect
	-1,												// LONG lindex	
	TYMED_ISTREAM,									// DWORD tymed
};

///////////////////////////////////////////////////////////////////////////////
// STGMEDIUM enthält eine serialisierte Objekteigenschaft, dazu können die 
// folgenden Helperroutinen verwendet werden.
HRESULT SetObjPropTemplate (os_string &strObjPropName, os_string &strObjProp, IDataObject *pIDO);
HRESULT GetObjProperty (IDataObject *pIDataObj, IObjectProperty **ppIOProp);

#endif // _CLSFYPRP_H
