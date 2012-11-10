// Alle Interface's einer Erweiterung -----------------------------------------
// File: IXTENSN.HXX

#if !defined(_IXTENSN_HXX)
#define _IXTENSN_HXX

#include <ienumobj.hxx>		// IEnumLONG, IQueryEnumLONG

// ClassFactory für eine Erweiterung ------------------------------------------

// 07963800-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(CLSID_XtensionClassFactory, 0x07963800L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);

///////////////////////////////////////////////////////////////////////////////
// Interface für Basisfunktionalität einer Erweiterung (muß implementiert werden)
#undef INTERFACE
#define INTERFACE ITriasXtension

// 07963801-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(CLSID_TriasXtension, 0x07963801L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
	
// 07963802-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_ITriasXtension, 0x07963802L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
DECLARE_INTERFACE_(ITriasXtension, IUnknown)
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** ITriasXtension specific functions ***
	STDMETHOD_(HDEX, LoadExtension) (THIS_ TRIASLOADEX *pTL, HWND hWnd) PURE;
	STDMETHOD_(BOOL, InitExtension) (THIS_ short iMode) PURE;
	STDMETHOD_(BOOL, UnLoadExtension) (THIS) PURE;
	STDMETHOD_(BOOL, MenuInit) (THIS_ HMENU hMenu, LPARAM lParam, HWND hWnd) PURE;
	STDMETHOD_(BOOL, MenuSelect) (THIS_ UINT uiMenuID, HMENU hMenu, HWND hWnd) PURE;
	STDMETHOD_(BOOL, MenuCommand) (THIS_ UINT uiMenuID, HWND hWnd) PURE;
	STDMETHOD_(LRESULT, Notification) (THIS_ WPARAM wParam, LPARAM lParam) PURE;
	STDMETHOD_(LRESULT, WindowsNotification) (THIS_ UINT wMsg, WPARAM wParam, 
						  LPARAM lParam) PURE;
	STDMETHOD_(LRESULT, GetCapabilities) (THIS_ UINT uiCap) PURE;
};
typedef ITriasXtension *LPTRIASXTENSION;

#ifndef __ITriasXtensionSite_INTERFACE_DEFINED__
#define __ITriasXtensionSite_INTERFACE_DEFINED__

// ITriasXtensionSite: das GegenStück zu ITriasXtension -----------------------
#undef INTERFACE
#define INTERFACE ITriasXtensionSite

// 07963815-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_ITriasXtensionSite, 0x07963815L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
DECLARE_INTERFACE_(ITriasXtensionSite, IUnknown)
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** ITriasXtensionSite methods
	STDMETHOD(GetXtension) (THIS_ REFCLSID rClsID, REFIID rIID, LPVOID *ppIUnk) PURE;
	STDMETHOD(CreateInstance) (THIS_ LPUNKNOWN pUnkOuter, REFCLSID rClsID, REFIID riid, LPVOID *ppUnk) PURE;
};
typedef ITriasXtensionSite *LPTRIASXTENSIONSITE;

#endif // __ITriasXtensionSite_INTERFACE_DEFINED__

// Ein erweitertes Interface für Erweiterungen (optional) ---------------------
#undef INTERFACE
#define INTERFACE ITriasXtension2

// 07963814-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_ITriasXtension2, 0x07963814L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
DECLARE_INTERFACE_(ITriasXtension2, ITriasXtension)
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** ITriasXtension specific functions ***
	STDMETHOD_(HDEX, LoadExtension) (THIS_ TRIASLOADEX *pTL, HWND hWnd) PURE;
	STDMETHOD_(BOOL, InitExtension) (THIS_ short iMode) PURE;
	STDMETHOD_(BOOL, UnLoadExtension) (THIS) PURE;
	STDMETHOD_(BOOL, MenuInit) (THIS_ HMENU hMenu, LPARAM lParam, HWND hWnd) PURE;
	STDMETHOD_(BOOL, MenuSelect) (THIS_ UINT uiMenuID, HMENU hMenu, HWND hWnd) PURE;
	STDMETHOD_(BOOL, MenuCommand) (THIS_ UINT uiMenuID, HWND hWnd) PURE;
	STDMETHOD_(LRESULT, Notification) (THIS_ WPARAM wParam, LPARAM lParam) PURE;
	STDMETHOD_(LRESULT, WindowsNotification) (THIS_ UINT wMsg, WPARAM wParam, 
						  LPARAM lParam) PURE;
	STDMETHOD_(LRESULT, GetCapabilities) (THIS_ UINT uiCap) PURE;

// *** ITriasXtension2 specific functions ***
	STDMETHOD(SetXtensionSite) (THIS_ ITriasXtensionSite *pXtnSite) PURE;
};
typedef ITriasXtension2 *LPTRIASXTENSION2;

// Werte für Argument von 'GetCapabilities()' ----------------------------------
const int GETCAPS_NOTLOADED = DEXCAP_NOTLOADED;		// ist noch nicht geladen

///////////////////////////////////////////////////////////////////////////////
// Interface's für ObjectPropertyFuncions (optional) ---------------------------
// ObjectProperty: eine beliebige Objekteigenschaft ----------------------------
#undef INTERFACE
#define INTERFACE IObjectProperty

// 07963803-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_IObjectProperty, 0x07963803L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
DECLARE_INTERFACE_(IObjectProperty, IUnknown)
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS) PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** IObjectProperty specific functions ***
	STDMETHOD(GetPropInfo) (THIS_ LPSTR pBuffer, WORD wLen, DWORD *pdwFlags/*=NULL*/) PURE;

	STDMETHOD(Reset)(THIS) PURE;
	STDMETHOD_(ULONG, Count)(THIS) PURE;
	STDMETHOD(HelpInfo)(THIS_ LPSTR pBuffer, ULONG ulLen, 
			    LPSTR pHelpFile/*=NULL*/, ULONG *pulHelpCtx/*=NULL*/) PURE;

	STDMETHOD(Eval)(THIS_ LONG lONr, LPSTR pBuffer, ULONG ulLen, 
				ULONG *pulWritten/*=NULL*/) PURE;
	STDMETHOD(Cumulation)(THIS_ LPSTR pBuffer, ULONG ulLen, 
				ULONG *pulWritten/*=NULL*/) PURE;
};
typedef IObjectProperty *LPOBJECTPROPERTY;

// ObjectProperty2: Objekteigenschaft, die gesetzt werden kann ----------------
#undef INTERFACE
#define INTERFACE IObjectProperty2

// 07963816-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_IObjectProperty2, 0x07963816L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
DECLARE_INTERFACE_(IObjectProperty2, IObjectProperty)
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS) PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** IObjectProperty specific functions ***
	STDMETHOD(GetPropInfo) (THIS_ LPSTR pBuffer, WORD wLen, DWORD *pdwFlags/*=NULL*/) PURE;

	STDMETHOD(Reset)(THIS) PURE;
	STDMETHOD_(ULONG, Count)(THIS) PURE;
	STDMETHOD(HelpInfo)(THIS_ LPSTR pBuffer, ULONG ulLen, 
			    LPSTR pHelpFile/*=NULL*/, ULONG *pulHelpCtx/*=NULL*/) PURE;

	STDMETHOD(Eval)(THIS_ LONG lONr, LPSTR pBuffer, ULONG ulLen, 
				ULONG *pulWritten/*=NULL*/) PURE;
	STDMETHOD(Cumulation)(THIS_ LPSTR pBuffer, ULONG ulLen, 
				ULONG *pulWritten/*=NULL*/) PURE;

// *** IObjectProperty2 specific functions ***
	STDMETHOD(Set)(THIS_ LONG lONr, LPCSTR pcBuffer) PURE;
};
typedef IObjectProperty2 *LPOBJECTPROPERTY2;

// IPropertyInfo: Informationen über Objekteigenschaft abfragen und setzen ----
#undef INTERFACE
#define INTERFACE IPropertyInfo

// 07963823-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_IPropertyInfo, 0x07963823L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
DECLARE_INTERFACE_(IPropertyInfo, IUnknown)
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS) PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** IPropertyInfo specific functions ***
// first two are the same as in IObjectProperty
	STDMETHOD(GetPropInfo) (THIS_ LPSTR pBuffer, WORD wLen, DWORD *pdwFlags/*=NULL*/) PURE;
	STDMETHOD(HelpInfo) (THIS_ LPSTR pBuffer, ULONG ulLen, 
			    LPSTR pHelpFile/*=NULL*/, ULONG *pulHelpCtx/*=NULL*/) PURE;
// next are unique to this interface
	STDMETHOD(SetPropInfo) (THIS_ LPCSTR pBuffer, DWORD dwFlags) PURE;
	STDMETHOD(SetHelpInfo) (THIS_ LPCSTR pBuffer,
				LPCSTR pHelpFile/*=NULL*/, ULONG ulHelpCtx/*=0*/) PURE;
};
typedef IPropertyInfo *LPPROPERTYINFO;

// IPropertyInfo: Informationen über Objekteigenschaft abfragen und setzen ----
#undef INTERFACE
#define INTERFACE IPropertyInfo2

// 079638DB-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_IPropertyInfo2, 0x079638DBL, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
DECLARE_INTERFACE_(IPropertyInfo2, IUnknown)
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS) PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** IPropertyInfo specific functions ***
// first two are the same as in IObjectProperty
	STDMETHOD(GetPropInfo) (THIS_ LPSTR pBuffer, WORD wLen, DWORD *pdwFlags/*=NULL*/) PURE;
	STDMETHOD(HelpInfo) (THIS_ LPSTR pBuffer, ULONG ulLen, 
			    LPSTR pHelpFile/*=NULL*/, ULONG *pulHelpCtx/*=NULL*/) PURE;
// next are unique to this interface
	STDMETHOD(SetPropInfo) (THIS_ LPCSTR pBuffer, DWORD dwFlags) PURE;
	STDMETHOD(SetHelpInfo) (THIS_ LPCSTR pBuffer,
				LPCSTR pHelpFile/*=NULL*/, ULONG ulHelpCtx/*=0*/) PURE;

// *** IPropertyInfo2 specific functions ***
	STDMETHOD(GetConfigData) (THIS_ VARIANT *pvOptData) PURE;
};
typedef IPropertyInfo2 *LPPROPERTYINFO2;

#if defined(WIN32)

// IPropertyTemplate: voreinstellbare Objekteigenschaft -----------------------
#undef INTERFACE
#define INTERFACE IPropertyTemplate

// 07963821-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_IPropertyTemplate, 0x07963821L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
DECLARE_INTERFACE_(IPropertyTemplate, IUnknown)
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS) PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** IPropertyTemplate methods ***
	STDMETHOD(SetTemplate)(THIS_ LPCSTR pcBuffer) PURE;
	STDMETHOD(GetTemplate)(THIS_ LPSTR pcBuffer, ULONG ulLen, ULONG *pulWritten) PURE;
	STDMETHOD(ApplyTemplate)(THIS_ LONG lONr) PURE;

	STDMETHOD(CloneTemplate)(THIS_ IPropertyTemplate **ppITempl) PURE;
};
typedef IPropertyTemplate *LPPROPERTYTEMPLATE;

#endif // WIN32

///////////////////////////////////////////////////////////////////////////////
// ClassProperty: eine beliebige ObjektKlassenEigenschaft ---------------------
#undef INTERFACE
#define INTERFACE IClassProperty

// 0796380C-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_IClassProperty, 0x0796380CL, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
DECLARE_INTERFACE_(IClassProperty, IUnknown)
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS) PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** IClassProperty specific functions ***
	STDMETHOD(GetPropInfo) (THIS_ LPSTR pBuffer, WORD wLen, DWORD *pdwFlags /*=NULL*/) PURE;

	STDMETHOD(Reset)(THIS) PURE;
	STDMETHOD_(ULONG, Count)(THIS) PURE;
	STDMETHOD(HelpInfo)(THIS_ LPSTR pBuffer, ULONG ulLen, 
			    LPSTR pHelpFile, ULONG *pulHelpCtx) PURE;

	STDMETHOD(Eval)(THIS_ IEnumLONG *pEnumObj, LPSTR pBuffer, 
			ULONG ulLen, ULONG *pulWritten) PURE;
	STDMETHOD(Cumulation)(THIS_ LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten) PURE;
};
typedef IClassProperty *LPCLASSPROPERTY;

#if defined(WIN32)

#include <istatus.h>		// IProgressIndicator

// IActionOnClass: irgend etwas mit den Objekten einer Klasse machen ----------
#undef INTERFACE
#define INTERFACE IPropertyAction

// 0796381A-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_IPropertyAction, 0x0796381AL, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
DECLARE_INTERFACE_ (IPropertyAction, IUnknown)
{
// *** IUnknown methods
	STDMETHOD (QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
	STDMETHOD_ (ULONG, AddRef) (THIS) PURE;
	STDMETHOD_ (ULONG, Release) (THIS) PURE;

// *** IPropertyAction methods
	STDMETHOD (AddConfigPages) (THIS_ LPFNADDPROPSHEETPAGE lpfnAddPage, 
		LPARAM lParam, LPCSTR pcDesc/*=NULL*/, UINT *puiCnt/*=NULL*/) PURE;
	STDMETHOD (PreConfigPages) (THIS_ IDataObject *pIDataObject, DWORD dwFlags) PURE;
	STDMETHOD (BeginAction) (THIS_ IProgressIndicator *pIProgInd/*=NULL*/) PURE;
	STDMETHOD (DoAction) (THIS_ IDataObject *pDataObj, DWORD dwReserved) PURE;
	STDMETHOD (EndAction) (THIS_ DWORD dwReserved, IDataObject **ppOutObj/*=NULL*/) PURE;
};
typedef IPropertyAction *LPPROPERTYACTION;

#undef INTERFACE
#define INTERFACE IPropertyAction2

// 07963889-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_IPropertyAction2, 0x07963889L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
DECLARE_INTERFACE_ (IPropertyAction2, IUnknown)
{
// *** IUnknown methods
	STDMETHOD (QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
	STDMETHOD_ (ULONG, AddRef) (THIS) PURE;
	STDMETHOD_ (ULONG, Release) (THIS) PURE;

// *** IPropertyAction methods
	STDMETHOD (AddConfigPages) (THIS_ LPFNADDPROPSHEETPAGE lpfnAddPage, 
		LPARAM lParam, LPCSTR pcDesc/*=NULL*/, UINT *puiCnt/*=NULL*/) PURE;
	STDMETHOD (PreConfigPages) (THIS_ IDataObject *pIDataObject, DWORD dwFlags) PURE;
	STDMETHOD (BeginAction) (THIS_ IProgressIndicator *pIProgInd/*=NULL*/) PURE;
	STDMETHOD (DoAction) (THIS_ IDataObject *pDataObj, DWORD dwReserved) PURE;
	STDMETHOD (EndAction) (THIS_ DWORD dwReserved, IDataObject **ppOutObj/*=NULL*/) PURE;

// *** IPropertyAction2 methods
	STDMETHOD (InitFromData) (THIS_ IDataObject *pIDO, BOOL fCreate, DWORD dwReserved) PURE;
};
typedef IPropertyAction2 *LPPROPERTYACTION2;

// Flags für dwFlags von AddConfigPages
typedef enum tagADDPAGESFLAGS {
	ADDPAGES_NONE = 0,		// nichts besonderes
	ADDPAGES_FIRSTPAGE = 1,		// ist die erste PropertyAction
	ADDPAGES_LASTPAGE = 2,		// ist die letzte PropertyAction
} ADDPAGESFLAGS;

#endif // WIN32

///////////////////////////////////////////////////////////////////////////////
// Verwaltet ObjectProperties einer Erweiterung -------------------------------
// Interface zur Enumeration der ObjektPropertyFunktionen ---------------------
#undef INTERFACE
#define INTERFACE IEnumObjProps 

// 07963806-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_IEnumObjProps, 0x07963806L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
DECLARE_INTERFACE_ (IEnumObjProps, IEnumUnknown)
{
// *** IUnknown methods
	STDMETHOD (QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
	STDMETHOD_ (ULONG, AddRef) (THIS) PURE;
	STDMETHOD_ (ULONG, Release) (THIS) PURE;
	
// *** IEnumUnknown methods
	STDMETHOD (Next) (THIS_ ULONG celt, LPUNKNOWN *rgelt, ULONG *pceltFetched) PURE;
	STDMETHOD (Skip) (THIS_ ULONG celt) PURE;
	STDMETHOD (Reset) (THIS) PURE;
	STDMETHOD (Clone) (THIS_ IEnumUnknown ** ppenm) PURE;
	
// IEnumObjProps methods
	STDMETHOD(FindByName) (THIS_ LPCSTR pName, IObjectProperty **ppObjProp) PURE;
};
typedef IEnumObjProps *LPENUMOBJPROPS;

// Interface zur Enumeration der ObjektKlassenPropertyFunktionen --------------
#undef INTERFACE
#define INTERFACE IEnumClassProps 

// 0796380D-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_IEnumClassProps, 0x0796380DL, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
DECLARE_INTERFACE_ (IEnumClassProps, IEnumUnknown)
{
// *** IUnknown methods
	STDMETHOD (QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
	STDMETHOD_ (ULONG, AddRef) (THIS) PURE;
	STDMETHOD_ (ULONG, Release) (THIS) PURE;
	
// *** IEnumUnknown methods
	STDMETHOD (Next) (THIS_ ULONG celt, LPUNKNOWN *rgelt, ULONG *pceltFetched) PURE;
	STDMETHOD (Skip) (THIS_ ULONG celt) PURE;
	STDMETHOD (Reset) (THIS) PURE;
	STDMETHOD (Clone) (THIS_ IEnumUnknown ** ppenm) PURE;
	
// IEnumClassProps methods
	STDMETHOD(FindByName) (THIS_ LPCSTR pName, IClassProperty **ppObjProp) PURE;
};
typedef IEnumClassProps *LPENUMCLASSPROPS;

///////////////////////////////////////////////////////////////////////////////
// Interface einer Erweiterung zur Verwaltung von Objekt- und KlassenEigenschaften
// (optional)
#undef INTERFACE
#define INTERFACE IObjectProps

// 07963804-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_IObjectProps, 0x07963804L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
DECLARE_INTERFACE_(IObjectProps, IUnknown)
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** IObjectProps specific functions ***
	STDMETHOD(EnumObjectProps) (THIS_ IEnumObjProps **ppEnumProp) PURE;
	STDMETHOD(EnumClassProps) (THIS_ IEnumClassProps **ppEnumProp) PURE;
	STDMETHOD(OnNewReferenceObject) (THIS_ LONG lRefONr) PURE;
	STDMETHOD(OnNewReferenceClass) (THIS_ IEnumLONG *pEnumObj) PURE;
	STDMETHOD(GetGroupInfo)(THIS_ LPSTR pGroupName, WORD wLen, DWORD *pdwFlags /*=NULL*/) PURE;
};
typedef IObjectProps *LPOBJECTPROPS;

typedef enum tagPROPCAPS {
	PROPCAPS_NONE = 0x00,					// Normale ObjProps (ReadOnly)
	PROPCAPS_NOTREADONLY = 0x01,			// NotReadOnlyObjProps
	PROPCAPS_RESTRICTED = 0x02,				// Systeminterne ObjProps
	PROPCAPS_USEABLEASTEMPLATE = 0x04,		// kann als Vorlage genutzt werden
//
// Eigenschaften erfordern in irgend einer Form eine Nutzerinteraktion
	PROPCAPS_INTERACTIVE = 0x08,			// erfordert Nutzerinteraktion für Wert
	PROPCAPS_INTERACTIVE_INIT = 0x10,		// erfordert Interaktion bei Initialisierung
//
// 'Eigenschaft', die IPropertyAction unterstützt
	PROPCAPS_ACTION_SOURCE = 0x0100,		// erzeugt eine Objektmenge
	PROPCAPS_ACTION_SOURCE_MULTI = 0x0200,	// erzeugt mehrere Objektmengen

	PROPCAPS_ACTION_SINK = 0x0400,			// verarbeitet eine Objektmenge
	PROPCAPS_ACTION_SINK_MULTI = 0x0800,	// verarbeitet mehrere Objektmengen
//
// IPropertyAction erfordert RePaint/RePaintLegend
	PROPCAPS_ACTION_MUSTREPAINT = 0x1000,	// erfordert RePaint
	PROPCAPS_ACTION_MUSTREPAINTLEGEND = 0x2000,	// erfordert RePaintLegend

#if defined(WIN32)
//
// IPropertyAction ist eine SearchEngine
	PROPCAPS_ACTION_SEARCHENGINE = 0x8000,	

///////////////////////////////////////////////////////////////////////////////
// Typen der Objekteigenschaften
	PROPCAPS_OBJPROPTYPE_STRING = 0x00000000,	// Objekteigenschaft liefert Zeichenkette
	PROPCAPS_OBJPROPTYPE_INTEGER = 0x00010000,	// Objekteigenschaft liefert integer - Zahlen
	PROPCAPS_OBJPROPTYPE_DOUBLE = 0x00020000,	// Objekteigenschaft liefert floatpoint - Zahlen
	PROPCAPS_OBJPROPTYPE_BOOL = 0x00040000,		// Objekteigenschaft liefert Bool
	PROPCAPS_OBJPROPTYPE_DATE = 0x00080000,		// Objekteigenschaft liefert Datum
	PROPCAPS_OBJPROPTYPE_UNKNOWN = 0x00800000,	// Objekteigenschaft unbekannt

///////////////////////////////////////////////////////////////////////////////
// Typen der PropertyAction-'Container'
	PROPCAPS_CONTAINER_IS_SEQUENCE = 0x80000000,	// Container ist PropertySequence
	PROPCAPS_CONTAINER_IS_CHOICE = 0x40000000,		// Container ist PropertyChoice

///////////////////////////////////////////////////////////////////////////////
// Für Initialisierungszwecke: unbekannte Eigenschaften
	PROPCAPS_UNKNOWN = 0xFFFFFFFF,
#endif // WIN32
} PROPCAPS;

///////////////////////////////////////////////////////////////////////////////
// Interface einer Erweiterung zum Hinzufügen neuer Objekteigenschaften
#undef INTERFACE
#define INTERFACE IObjectProps2

// 079638C3-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_IObjectProps2, 0x079638C3L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
DECLARE_INTERFACE_(IObjectProps2, IUnknown)
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** IObjectProps2 specific functions ***
	STDMETHOD(CreateNewProp) (THIS_ LPCSTR pcName, DWORD dwFlags, LONG lONr, 
				VARIANT vOptData, REFIID riid, LPVOID *ppIObjProp) PURE;
	STDMETHOD(DeleteProp) (THIS_ LPCSTR pcName, LONG lONr) PURE;
};

///////////////////////////////////////////////////////////////////////////////
// Interface für ImportErweiterungen (optional) -------------------------------
#undef INTERFACE
#define INTERFACE IImportGeoData

// 07963805-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_IImportGeoData, 0x07963805L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
DECLARE_INTERFACE_(IImportGeoData, IUnknown)
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// ** IImportGeoData methods
	STDMETHOD_(DWORD, Capabilities)(THIS) PURE;
	STDMETHOD(Configure) (THIS_ HWND hWnd) PURE;
	STDMETHOD(ImportData) (THIS_ IEnumString *pEnumFiles, DWORD dwFlags) PURE;
	STDMETHOD(GetConfigInfo) (THIS_ IEnumString **ppEnumCfgInfo, DWORD dwReserved) PURE;
};
typedef IImportGeoData *LPIMPORTGEODATA;

// Flags, die von Capabilities geliefert werden können ------------------------
typedef enum tagIMPORTCAPS {
	IMPORTCAPS_NOTIMPLEMENTED = 0x0000,	// default

	IMPORTCAPS_CANIMPORTGEOMETRY = 0x0001,	// prinzipielle Fähigkeiten
	IMPORTCAPS_CANIMPORTFEATURES = 0x0002,
	IMPORTCAPS_CANIMPORTRELATIONS = 0x0004,
	IMPORTCAPS_CANIMPORTVISUALISATION = 0x0008,
	IMPORTCAPS_CANIMPORTANSIOEM = 0x0010,
	IMPORTCAPS_CANIMPORTALL = 0x001F,

	IMPORTCAPS_OPTIMPORTGEOMETRY = 0x0100,	// abschaltbare Fähigkeiten
	IMPORTCAPS_OPTIMPORTFEATURES = 0x0200,
	IMPORTCAPS_OPTIMPORTRELATIONS = 0x0400,
	IMPORTCAPS_OPTIMPORTVISUALISATION = 0x0800,
	IMPORTCAPS_OPTIMPORTANSIOEM = 0x1000,
	IMPORTCAPS_OPTIMPORTALL = 0x1F00,

	IMPORTCAPS_MULTIPLEFILES = 0x2000,	// kann mehrere Dateien verarbeiten
	IMPORTCAPS_SHOULDCONFIG = 0x4000,	// kann KonfigurationsFenster anzeigen

	IMPORTCAPS_DYNCONFIGINFO = int(0x8000),	// liefert dynamische DateiInfo's
} IMPORTCAPS;

// Flags, die festlegen, was gemacht werden soll ------------------------------
typedef enum tagTOIMPORT {
	TOIMPORT_GEOMETRY = 0x0001,		// Geometrie importieren
	TOIMPORT_FEATURES = 0x0002,		// Merkmale importieren
	TOIMPORT_RELATIONS = 0x0004,		// Relationen importieren
	TOIMPORT_VISUALISATION = 0x0008,	// Visualisierung importieren
	TOIMPORT_ANSIOEM = 0x0010,		// aus DOS-Zeichensatz konvertieren
} TOIMPORT;

// Interface für das starten einer Drag'n Drop Operation, gibt einer Erweiterung
// die Möglichkeit, zusätzliche Daten ins DataObject einzufügen. DoDragDropAction 
// wird gerufen, _nachdem_ TRiAS seine Daten ins DataObject eingefügt hat.
#undef INTERFACE
#define INTERFACE IDragDropAction

// Fenster, aus dem die Daten rausgezogen werden sollen
typedef enum tagDRAGDROPTYPE {
	DRAGDROPTYPE_VIEWWINDOW = 0x0001,	// Dokumentfenster
	DRAGDROPTYPE_ORWINDOW = 0x0002,		// Objektrecherchefenster
	DRAGDROPTYPE_LEGENDWINDOW = 0x0003,	// Legende
} DRAGDROPTYPE;

// 079638BA-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_IDragDropAction, 0x079638BAL, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
DECLARE_INTERFACE_(IDragDropAction, IUnknown)
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** IDragDropAction
	STDMETHOD(BeginDragDrop) (THIS_ DRAGDROPTYPE rgType, HWND hWndSrc, DWORD dwFlags, IDataObject *pIDO) PURE;
	STDMETHOD(DoDragDrop) (THIS_ DRAGDROPTYPE rgType, HWND hWnd, IDataObject *pIDO, 
		IDropSource *pISrc,	DWORD dwOKEffects, LPDWORD pdwEffect) PURE;
	STDMETHOD(EndDragDrop) (THIS_ DRAGDROPTYPE rgType, HWND hWndSrc, DWORD dwEffect) PURE;
};
typedef IDragDropAction *LPDRAGDROPACTION;

// 079638C0-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_ITRiASDropTarget, 0x079638C0L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
DECLARE_INTERFACE_(ITRiASDropTarget, IUnknown)
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** ITRiASDropTarget
	STDMETHOD(DragEnter) (THIS_ DRAGDROPTYPE rgType, HWND hWnd,	IDataObject *pIDataSource, 
		DWORD grfKeyState, POINTL pt, DWORD *pdwEffect) PURE;
	STDMETHOD(DragOver) (THIS_ DRAGDROPTYPE rgType, HWND hWnd, 
		DWORD grfKeyState, POINTL pt, DWORD *pdwEffect) PURE;
	STDMETHOD(DragLeave) (THIS_ DRAGDROPTYPE rgType, HWND hWnd) PURE;
	STDMETHOD(Drop) (THIS_ DRAGDROPTYPE rgType, HWND hWnd, IDataObject *pIDataSource, 
		DWORD grfKeyState, POINTL pt, DWORD *pdwEffect) PURE;
};
typedef ITRiASDropTarget *LPTRIASDROPTARGET;

// Weiterhin sollte jede Erweiterung seine eigentliche spezifische Funktionalität 
// über ein Custom-Interface nach außen zur Verfügung stellen.

#endif // _IXTENSN_HXX

