// FORMATETC für in DataObject abgelegte Moniker
// File: MonikerStream.h

#if !defined(_MONIKERSTREAM_H)
#define _MONIKERSTREAM_H

// Erzeugte Infos im durchgereichten IDataObject ------------------------------
// ClipBoardFormate
extern const TCHAR g_cbMkGeoDocument[];		// "TRiASItemMoniker_GeoDocument";
extern const TCHAR g_cbMkGeoClass[];		// "TRiASItemMoniker_GeoClass";
extern const TCHAR g_cbMkGeoView[];			// "TRiASItemMoniker_GeoView";
extern const TCHAR g_cbMkGeoObject[];		// "TRiASItemMoniker_GeoObject";
extern const TCHAR g_cbMkGeoObjects[];		// "TRiASItemMoniker_GeoObjects";

//
// FORMATETC
const FORMATETC c_feMkGeoDocument = 
{
	RegisterClipboardFormat (g_cbMkGeoDocument),	// CLIPFORMAT cf
	NULL,											// DVTARGETDEVICE *ptd
	DVASPECT_CONTENT,								// DWORD dwAspect
	-1,												// LONG lindex	
	TYMED_ISTREAM,									// DWORD tymed
};

const FORMATETC c_feMkGeoClass = 
{
	RegisterClipboardFormat (g_cbMkGeoClass),		// CLIPFORMAT cf
	NULL,											// DVTARGETDEVICE *ptd
	DVASPECT_CONTENT,								// DWORD dwAspect
	-1,												// LONG lindex	
	TYMED_ISTREAM,									// DWORD tymed
};

const FORMATETC c_feMkGeoView = 
{
	RegisterClipboardFormat (g_cbMkGeoView),		// CLIPFORMAT cf
	NULL,											// DVTARGETDEVICE *ptd
	DVASPECT_CONTENT,								// DWORD dwAspect
	-1,												// LONG lindex	
	TYMED_ISTREAM,									// DWORD tymed
};

const FORMATETC c_feMkGeoObject = 
{
	RegisterClipboardFormat (g_cbMkGeoObject),		// CLIPFORMAT cf
	NULL,											// DVTARGETDEVICE *ptd
	DVASPECT_CONTENT,								// DWORD dwAspect
	-1,												// LONG lindex	
	TYMED_ISTREAM,									// DWORD tymed
};

const FORMATETC c_feMkGeoObjects = 
{
	RegisterClipboardFormat (g_cbMkGeoObjects),			// CLIPFORMAT cf
	NULL,											// DVTARGETDEVICE *ptd
	DVASPECT_CONTENT,								// DWORD dwAspect
	-1,												// LONG lindex	
	TYMED_ISTREAM,									// DWORD tymed
};

#endif // _MONIKERSTREAM_H
