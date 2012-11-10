// Diverse Hilfsfunktionen für den Umgang mit unserem CDataObject -------------
// File: DATAHELP.H

#ifndef _DATAHELP_H
#define _DATAHELP_H

////////////////////////////////////////////////////////////////////////////////
// ClipBoardFormate
////////////////////////////////////////////////////////////////////////////////

// Erwartete Zusatzinfos //////////////////////////////////////////////////////
// 1. FensterHandle des ORFensters (HWND) , aus welchem Befehl ausgelöst wurde
// ClipBoardFormate
const char c_cbPAObjectWindow[] = "ObjectWindow";

//
// FORMATETC
const FORMATETC c_feObjectWindow = {
	RegisterClipboardFormat (c_cbPAObjectWindow),	// CLIPFORMAT cf
	NULL,											// DVTARGETDEVICE *ptd
	DVASPECT_CONTENT,								// DWORD dwAspect
	-1,												// LONG lindex	
	TYMED_HGLOBAL,									// DWORD tymed
};

// Erzeugte Infos im durchgereichten IDataObject ------------------------------
// 1. IEnumLONG mit allen selektierten Objekten. Dieser Enumerator ist in einen
// Stream serialisiert, der im CDataObject übergeben wird.
// 
const char c_cbPASelectedObjects[] = "EnumSelectedObjects";

//
// FORMATETC
const FORMATETC c_feSelectedObjects = {
	RegisterClipboardFormat (c_cbPASelectedObjects),// CLIPFORMAT cf
	NULL,											// DVTARGETDEVICE *ptd
	DVASPECT_CONTENT,								// DWORD dwAspect
	-1,												// LONG lindex	
	TYMED_ISTREAM,									// DWORD tymed
};

// Funktionen für EnumLONG ////////////////////////////////////////////////////

// Serialisieren/DeSerialisieren eines IUnknowns 
// in diesem Falle ein IDataObject
HRESULT CreateStreamOnHGlobalFromIUnknown (IUnknown *pIUnk, REFCLSID rClsID, 
										   IStream **ppIStream);
// die folgende Funktion ist das konkrete äquivalent für 'OleLoadFromStream' --
HRESULT CreateEnumLONGFromStream (IStream *pIStream, IEnum<LONG> **ppEnumOut);
// Hinzufügen eines EnumLONG zu einem IDataObject -----------------------------
HRESULT SetEnumLONGData (IEnum<LONG> *pEnum, REFCLSID rClsID, 
						 IDataObject *pDataObj);
// Dient zum Lesen der Daten (EnumLONG) vom Stream im Datenobjekt
HRESULT GetEnumLONGData (IDataObject *pIDataObj, IEnum<LONG> **ppIEnumOut);
// Hinzufügen eines HWND zu einem IDataObject ---------------------------------
HRESULT SetHWNDData (HWND hWnd, IDataObject *pDataObj);
// Lesen eines HWND aus einem DataObjekt ----------------------------------
HRESULT GetHWNDData (IDataObject *pIDataObj, HWND *phWnd);

#endif // _DATAHELP_H