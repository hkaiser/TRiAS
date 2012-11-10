// Allgemeines zur PropertyAction 'CLSID_SelectFromObjectWindow' --------------
// File: SELOBWND.H

#if !defined(_SELOBWND_H)
#define _SELOBWND_H

// GUID ///////////////////////////////////////////////////////////////////////
// 0E54C9EA-20DE-11CF-BA55-00AA0018497C	
DEFINE_GUID(CLSID_SelectFromObjectWindow, 0x0E54C9EAL, 0x20DE, 0x11CF, 0xBA, 0x55, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);

// Name ///////////////////////////////////////////////////////////////////////
const char c_cbSelObjWndName[] = "CLSPROP_ROOT\\TRiAS® (allgemein)\\Objektauswahl aus Recherchefenster";

// Erzeugte ZusatzInfos ///////////////////////////////////////////////////////
// 1. IEnumLONG enthält alle selektierten Objekte
// ClipBoardFormat und FORMATETC sind global für alle PropertyAction's
#include <propactn.h>

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

// 2. FensterHandle des ORFensters (HWND), welches in der Liste ignoriert werden soll
// ClipBoardFormate
const char c_cbPAIgnoreWindow[] = "ObjectWindowToIgnore";

//
// FORMATETC
const FORMATETC c_feIgnoreWindow = {
	RegisterClipboardFormat (c_cbPAIgnoreWindow),	// CLIPFORMAT cf
	NULL,											// DVTARGETDEVICE *ptd
	DVASPECT_CONTENT,								// DWORD dwAspect
	-1,												// LONG lindex	
	TYMED_HGLOBAL,									// DWORD tymed
};

#endif // _SELOBWND_H
