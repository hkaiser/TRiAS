// Allgemeines zur PropertyAction 'CLSID_ClassifyByObjProp' -------------------
// File: CLSFYPRP.H

#if !defined(_CLSFYPRP_H)
#define _CLSFYPRP_H

// GUID ///////////////////////////////////////////////////////////////////////
// 0E54C9E1-20DE-11CF-BA55-00AA0018497C	
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

// 2. Wert der Objekteigenschaft, nach der Klassifiziert wurde
// ClipBoardFormat
const char c_cbPAPropertyValue[] = "PersistObjectPropertyValue";
//
// FORMATETC
const FORMATETC c_feClassifyValue = {
	RegisterClipboardFormat (c_cbPAPropertyValue),	// CLIPFORMAT cf
	NULL,											// DVTARGETDEVICE *ptd
	DVASPECT_CONTENT,								// DWORD dwAspect
	-1,												// LONG lindex	
	TYMED_ISTREAM,									// DWORD tymed
};

// 3. Caption für evtl. Fenster mitgeben
// ClipBoardFormat
const char c_cbPAORWndCaption[] = "PersistORWndCaption";
//
// FORMATETC
const FORMATETC c_feORWndCaption = {
	RegisterClipboardFormat (c_cbPAORWndCaption),	// CLIPFORMAT cf
	NULL,											// DVTARGETDEVICE *ptd
	DVASPECT_CONTENT,								// DWORD dwAspect
	-1,												// LONG lindex	
	TYMED_ISTREAM,									// DWORD tymed
};

// 4. Farbe für evtl. Fenster mitgeben
// ClipBoardFormat
const char c_cbPAORWndColor[] = "PersistORWndMarkColor";
//
// FORMATETC
const FORMATETC c_fePAORWndColor = {
	RegisterClipboardFormat (c_cbPAORWndColor),		// CLIPFORMAT cf
	NULL,											// DVTARGETDEVICE *ptd
	DVASPECT_CONTENT,								// DWORD dwAspect
	-1,												// LONG lindex	
	TYMED_ISTREAM,									// DWORD tymed
};

// 5. evtl. Fehlertext fürs Fenster mitgeben
// ClipBoardFormat
const char c_cbPAORWndErrMsg[] = "PersistORWndErrorMessage";
//
// FORMATETC
const FORMATETC c_fePAORWndErrMsg = {
	RegisterClipboardFormat (c_cbPAORWndErrMsg),	// CLIPFORMAT cf
	NULL,											// DVTARGETDEVICE *ptd
	DVASPECT_CONTENT,								// DWORD dwAspect
	-1,												// LONG lindex	
	TYMED_ISTREAM,									// DWORD tymed
};

///////////////////////////////////////////////////////////////////////////////
// STGMEDIUM enthält eine serialisierte Objekteigenschaft, dazu können die 
// folgenden Helperroutinen verwendet werden.
HRESULT SetObjPropTemplate (string &strObjPropName, string &strObjProp, IDataObject *pIDO);
HRESULT SetClassifyValue(string &rstrObjProp);

#endif // _CLSFYPRP_H
