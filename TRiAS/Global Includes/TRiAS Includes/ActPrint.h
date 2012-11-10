// Formatbeschreibung für aktuelle Druckerdaten
// File: ACTPRINT.H

#if !defined(_ACTPRINT_H)
#define _ACTPRINT_H

// Wird verwendet, um alle PropertyPages des DruckerDialoges vom derzeit
// zu verwendenden Drucker zu informieren.
const char c_cbActPrinter[] = "ActPrinterData";

const FORMATETC g_cfeActPrinter =
{
	RegisterClipboardFormat (c_cbActPrinter),		// CLIPFORMAT cf
	NULL,											// DVTARGETDEVICE *ptd
	DVASPECT_CONTENT,								// DWORD dwAspect
	-1,												// LONG lindex	
	TYMED_HGLOBAL,									// DWORD tymed
};

#endif // _ACTPRINT_H
