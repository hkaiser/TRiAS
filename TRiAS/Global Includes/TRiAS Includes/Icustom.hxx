// Interfacedeklaration für erweiterte Visualisierungsmodule ------------------
// File: ICUSTOM.HXX


#if !defined(_ICUSTOM_HXX)
#define _ICUSTOM_HXX

// Interfacedeklarationen für Module, die spezielle Visualisierung vornehmen --

// Interface, über welches die gesamte Symbolisierung gesteuert wird ----------
#undef  INTERFACE
#define INTERFACE IVisModule

// Datentypen für Notifikationen ----------------------------------------------
typedef enum tagPROJECTCHANGE {
	PROJECTCHANGE_OPENED = 0,	// neues Projekt geöffnet
	PROJECTCHANGE_CLOSED = 1,	// Projekt geschlossen
} PROJECTCHANGE;

typedef enum tagVIEWCHANGE {
	VIEWCHANGE_SELECTED = 0,	// neue Sicht ausgewählt
	VIEWCHANGE_DELETED = 1,		// Sicht gelöscht
} VIEWCHANGE;


DECLARE_INTERFACE_(IVisModule, IUnknown)
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG,Release) (THIS) PURE;

// *** Own Methods ***
	STDMETHOD(QueryParameters) (THIS_ HWND hWnd, long lONr, 
				    class VisInfo *pVI, char *pVisStr,
				    char *pBuffer, short iLen, short *piOTypes) PURE;
	STDMETHOD(SymbolizeObject) (THIS_ HWND hWnd, long &rlONr, short &iOType,
				    char *pBuffer, short iLen) PURE;
	STDMETHOD(DrawObject) (THIS_ HWND hWnd, HDC hDC, HDC hTargetDC, 
			       long lONr, short &fDrawFlags, 
			       class VisInfo *pVI, char *pVisString) PURE;
	STDMETHOD_(void,OnProjectChange)(THIS_ HWND hWndM, PROJECTCHANGE rgPC, 
					 char *pPrName) PURE;
	STDMETHOD_(void,OnViewChange)(THIS_ HWND hWndM, VIEWCHANGE rgVC, 
				      char *pView) PURE;
	STDMETHOD_(void,OnPaletteChange)(THIS_ HWND hWndM, HPALETTE hPal) PURE;
};
typedef IVisModule * LPVISMODULE;


#if defined(INITGUIDS)
#include <initguid.h>
#endif

///////////////////////////////////////////////////////////////////////////////
// 321C58E0-0C60-101B-AAE1-E7E7E7E7E7E7
DEFINE_GUID(CLSID_VisModule, 0x321C58E0L, 0x0C60, 0x101B, 0xAA, 0xE1, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7);

// neue FehlerCodes -----------------------------------------------------------
// IVisModule :: DrawObject
#define VISMODULE_E_GENERALERROR	MAKE_SCODE(SEVERITY_ERROR, FACILITY_NULL, 1)
#define VISMODULE_E_BADOBJECTTYPE	MAKE_SCODE(SEVERITY_ERROR, FACILITY_NULL, 2)

#define VISMODULE_S_DRAWOBJECT			MAKE_SCODE(SEVERITY_SUCCESS, FACILITY_ITF, 1)
#define VISMODULE_S_OBJECTISDRAWN	MAKE_SCODE(SEVERITY_SUCCESS, FACILITY_ITF, 2)
#define VISMODULE_S_ANALYZEONLY		MAKE_SCODE(SEVERITY_SUCCESS, FACILITY_ITF, 3)

#endif // _ICUSTOM_HXX
