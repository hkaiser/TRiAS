// Alle Interface's einer Erweiterung -----------------------------------------
// File: IXTENSN.HXX

#if !defined(_IXTENSN_HXX)
#define _IXTENSN_HXX

#if _MSC_VER < 1100 && !defined(DECLSPEC_UUID)
#define DECLSPEC_UUID(x)
#endif // _MSC_VER < 1100 && !defined(DECLSPEC_UUID)

#include <basetsd.h>
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
interface DECLSPEC_UUID("07963802-3123-101C-BB62-00AA0018497C")
ITriasXtension : public IUnknown
{
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
interface DECLSPEC_UUID("07963815-3123-101C-BB62-00AA0018497C")
ITriasXtensionSite : public IUnknown
{
// *** ITriasXtensionSite methods
	STDMETHOD(GetXtension) (THIS_ REFCLSID rClsID, REFIID rIID, LPVOID *ppIUnk) PURE;
	STDMETHOD(CreateInstance) (THIS_ LPUNKNOWN pUnkOuter, REFCLSID rClsID, REFIID riid, LPVOID *ppUnk) PURE;
};
typedef ITriasXtensionSite *LPTRIASXTENSIONSITE;

#endif // __ITriasXtensionSite_INTERFACE_DEFINED__

#ifndef __ITRiASServiceProvider_INTERFACE_DEFINED__
#define __ITRiASServiceProvider_INTERFACE_DEFINED__

// ITRiASServiceProvider: das GegenStück zu ITriasXtension, aber als BefehlsSchnittstelle
#undef INTERFACE
#define INTERFACE ITRiASServiceProvider

// 4F76AC35-98EF-11D1-BA12-080036D63803	
// DEFINE_GUID(IID_ITRiASServiceProvider, 0x4F76AC35L, 0x98EF, 0x11D1, 0xBA, 0x12, 0x08, 0x00, 0x36, 0xD6, 0x38, 0x03);
interface DECLSPEC_UUID("4F76AC35-98EF-11D1-BA12-080036D63803")
ITRiASServiceProvider : public IUnknown
{
// *** ITRiASServiceProvider methods
	STDMETHOD(DexExtensionProc) (THIS_ WPARAM wParam, LPARAM lParam) PURE;
	STDMETHOD(DexExtensionProc2) (THIS_ HPROJECT hPr, WPARAM wParam, LPARAM lParam) PURE;
	STDMETHOD(DexNotificationProc) (THIS_ WPARAM wParam, LPARAM lParam, BOOL fPost) PURE;
	STDMETHOD(DexDispatchProc) (THIS_ HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam) PURE;
};
typedef ITRiASServiceProvider *LPTRIASSERVICEPROVIDER;

#endif // __ITRiASServiceProvider_INTERFACE_DEFINED__

// Ein erweitertes Interface für Erweiterungen (optional) ---------------------
#undef INTERFACE
#define INTERFACE ITriasXtension2

// 07963814-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_ITriasXtension2, 0x07963814L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
interface DECLSPEC_UUID("07963814-3123-101C-BB62-00AA0018497C")
ITriasXtension2 : public ITriasXtension
{
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
interface DECLSPEC_UUID("07963803-3123-101C-BB62-00AA0018497C")
IObjectProperty : public IUnknown
{
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
interface DECLSPEC_UUID("07963816-3123-101C-BB62-00AA0018497C")
IObjectProperty2 : public IObjectProperty
{
// *** IObjectProperty2 specific functions ***
	STDMETHOD(Set)(THIS_ LONG lONr, LPCSTR pcBuffer) PURE;
};
typedef IObjectProperty2 *LPOBJECTPROPERTY2;

// {467D9F96-BD39-45C7-8EAB-5821BE52E855}
// DEFINE_GUID(IID_IObjectProperty3, 0x467D9F96, 0xBD39, 0x45C7, 0x8E, 0xAB, 0x58, 0x21, 0xBE, 0x52, 0xE8, 0x55);
interface DECLSPEC_UUID("467D9F96-BD39-45C7-8EAB-5821BE52E855")
IObjectProperty3 : public IObjectProperty2
{
	STDMETHOD(SetWithUndo)(THIS_ LONG lONr, LPCSTR pcBuffer) PURE;
};

// IPropertyInfo: Informationen über Objekteigenschaft abfragen und setzen ----
#undef INTERFACE
#define INTERFACE IPropertyInfo

// 07963823-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_IPropertyInfo, 0x07963823L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
interface DECLSPEC_UUID("07963823-3123-101C-BB62-00AA0018497C")
IPropertyInfo : public IUnknown
{
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
interface DECLSPEC_UUID("079638DB-3123-101C-BB62-00AA0018497C")
IPropertyInfo2 : public IPropertyInfo
{
// *** IPropertyInfo2 specific functions ***
	STDMETHOD(GetConfigData) (THIS_ VARIANT *pvOptData) PURE;
	STDMETHOD(EvaluatesForClass) (THIS_ INT_PTR hObjs) PURE;
	STDMETHOD(GetConfigDataEx) (THIS_ INT_PTR hObjs, VARIANT *pvOptData) PURE;
	STDMETHOD(GetPropInfoEx) (THIS_ INT_PTR hObjs, LPSTR pBuffer, WORD wLen, DWORD *pdwData) PURE;
};
typedef IPropertyInfo2 *LPPROPERTYINFO2;

// 56347F59-E542-4C1B-9FC6-99FF3A2A47D3 
interface DECLSPEC_UUID("56347F59-E542-4C1B-9FC6-99FF3A2A47D3")
IPropertyInfo3 : public IPropertyInfo2
{
// *** IPropertyInfo3 specific functions ***
	STDMETHOD(GetEnumConfigData)(THIS_ IEnumLONG **pIFeatures) PURE;
};
typedef IPropertyInfo3 *LPPROPERTYINFO3;

#if !defined(WIN16)

// IPropertyTemplate: voreinstellbare Objekteigenschaft -----------------------
#undef INTERFACE
#define INTERFACE IPropertyTemplate

// 07963821-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_IPropertyTemplate, 0x07963821L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
interface DECLSPEC_UUID("07963821-3123-101C-BB62-00AA0018497C")
IPropertyTemplate : public IUnknown
{
// *** IPropertyTemplate methods ***
	STDMETHOD(SetTemplate)(THIS_ LPCSTR pcBuffer) PURE;
	STDMETHOD(GetTemplate)(THIS_ LPSTR pcBuffer, ULONG ulLen, ULONG *pulWritten) PURE;
	STDMETHOD(ApplyTemplate)(THIS_ LONG lONr) PURE;

	STDMETHOD(CloneTemplate)(THIS_ IPropertyTemplate **ppITempl) PURE;
};
typedef IPropertyTemplate *LPPROPERTYTEMPLATE;

#endif // WIN16

///////////////////////////////////////////////////////////////////////////////
// ClassProperty: eine beliebige ObjektKlassenEigenschaft ---------------------
#undef INTERFACE
#define INTERFACE IClassProperty

// 0796380C-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_IClassProperty, 0x0796380CL, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
interface DECLSPEC_UUID("0796380C-3123-101C-BB62-00AA0018497C")
IClassProperty : public IUnknown
{
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

#if !defined(WIN16)

#include <istatus.h>		// IProgressIndicator

// IActionOnClass: irgend etwas mit den Objekten einer Klasse machen ----------
#undef INTERFACE
#define INTERFACE IPropertyAction

// 0796381A-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_IPropertyAction, 0x0796381AL, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
interface DECLSPEC_UUID("0796381A-3123-101C-BB62-00AA0018497C")
IPropertyAction : public IUnknown
{
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
interface DECLSPEC_UUID("07963889-3123-101C-BB62-00AA0018497C")
IPropertyAction2 : public IPropertyAction
{
// *** IPropertyAction methods
//	STDMETHOD (AddConfigPages) (THIS_ LPFNADDPROPSHEETPAGE lpfnAddPage, 
//		LPARAM lParam, LPCSTR pcDesc/*=NULL*/, UINT *puiCnt/*=NULL*/) PURE;
//	STDMETHOD (PreConfigPages) (THIS_ IDataObject *pIDataObject, DWORD dwFlags) PURE;
//	STDMETHOD (BeginAction) (THIS_ IProgressIndicator *pIProgInd/*=NULL*/) PURE;
//	STDMETHOD (DoAction) (THIS_ IDataObject *pDataObj, DWORD dwReserved) PURE;
//	STDMETHOD (EndAction) (THIS_ DWORD dwReserved, IDataObject **ppOutObj/*=NULL*/) PURE;

// *** IPropertyAction2 methods
	STDMETHOD (InitFromData) (THIS_ IDataObject *pIDO, BOOL fCreate, DWORD dwReserved) PURE;
};
typedef IPropertyAction2 *LPPROPERTYACTION2;

// Flags für dwFlags von AddConfigPages
typedef enum tagADDPAGESFLAGS {
	ADDPAGES_NONE = 0,					// nichts besonderes
	ADDPAGES_FIRSTPAGE = 1,				// hat die erste angezeigte PropertyPage
	ADDPAGES_LASTPAGE = 2,				// hat die letzte angezeigte PropertyPage
	ADDPAGES_FIRSTPROPERTYACTION = 4,	// ist die erste PropertyAction
	ADDPAGES_LASTPROPERTYACTION = 8,	// ist die letzte PropertyAction
} ADDPAGESFLAGS;

#endif // WIN16

// 6EF4A3BA-5BD8-45A8-A3A8-C94C5F248B0C
// DEFINE_GUID(IID_IPropertyAction3, 0x6EF4A3BA, 0x5BD8, 0x45A8, 0xA3, 0xA8, 0xC9, 0x4C, 0x5F, 0x24, 0x8B, 0x0C);
interface DECLSPEC_UUID("6EF4A3BA-5BD8-45A8-A3A8-C94C5F248B0C")
IPropertyAction3 : public IPropertyAction2
{
// *** IPropertyAction methods
//	STDMETHOD (AddConfigPages) (THIS_ LPFNADDPROPSHEETPAGE lpfnAddPage, 
//		LPARAM lParam, LPCSTR pcDesc/*=NULL*/, UINT *puiCnt/*=NULL*/) PURE;
//	STDMETHOD (PreConfigPages) (THIS_ IDataObject *pIDataObject, DWORD dwFlags) PURE;
//	STDMETHOD (BeginAction) (THIS_ IProgressIndicator *pIProgInd/*=NULL*/) PURE;
//	STDMETHOD (DoAction) (THIS_ IDataObject *pDataObj, DWORD dwReserved) PURE;
//	STDMETHOD (EndAction) (THIS_ DWORD dwReserved, IDataObject **ppOutObj/*=NULL*/) PURE;

// *** IPropertyAction2 methods
//	STDMETHOD (InitFromData) (THIS_ IDataObject *pIDO, BOOL fCreate, DWORD dwReserved) PURE;

// *** IPropertyAction3 methods
	STDMETHOD(GetHeaderTitle) (THIS_ LPSTR pBuffer, ULONG wLen) PURE;	
	STDMETHOD(SetHeaderTitle) (THIS_ LPCSTR pcHeaderTitle) PURE;
	STDMETHOD(GetHeaderSubTitle) (THIS_ LPSTR pSubBuffer, ULONG wLen) PURE;	
	STDMETHOD(SetHeaderSubTitle) (THIS_ LPCSTR pcHeaderSubTitle) PURE;
};
typedef IPropertyAction2 *LPPROPERTYACTION2;

///////////////////////////////////////////////////////////////////////////////
// Verwaltet ObjectProperties einer Erweiterung -------------------------------
// Interface zur Enumeration der ObjektPropertyFunktionen ---------------------
#undef INTERFACE
#define INTERFACE IEnumObjProps 

// 07963806-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_IEnumObjProps, 0x07963806L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
interface DECLSPEC_UUID("07963806-3123-101C-BB62-00AA0018497C")
IEnumObjProps : public IEnumUnknown
{
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
interface DECLSPEC_UUID("0796380D-3123-101C-BB62-00AA0018497C")
IEnumClassProps : public IEnumUnknown
{
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
interface DECLSPEC_UUID("07963804-3123-101C-BB62-00AA0018497C")
IObjectProps : public IUnknown
{
// *** IObjectProps specific functions ***
	STDMETHOD(EnumObjectProps) (THIS_ IEnumObjProps **ppEnumProp) PURE;
	STDMETHOD(EnumClassProps) (THIS_ IEnumClassProps **ppEnumProp) PURE;
	STDMETHOD(OnNewReferenceObject) (THIS_ INT_PTR lRefONr) PURE;
	STDMETHOD(OnNewReferenceClass) (THIS_ IEnumLONG *pEnumObjs) PURE;
	STDMETHOD(GetGroupInfo)(THIS_ LPSTR pGroupName, WORD wLen, DWORD *pdwFlags /*=NULL*/) PURE;

// *** IObjectPropsEx specific functions ***
	STDMETHOD(OnNewReferenceObjects) (THIS_ INT_PTR lRefObjs, INT_PTR lRefObj /*=0L*/) PURE;
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

	PROPCAPS_GENERATED = 0x20,				// Objekteigenschaft wird generiert
	PROPCAPS_LOADABLE = 0x40,				// Objekteigenschaft wird dynamisch (aus XML) installiert

//
// 'Eigenschaft', die IPropertyAction unterstützt
// die folgenden Flags gelten für PropertySequences
	PROPCAPS_ACTION_SOURCE = 0x0100,		// erzeugt eine Objektmenge
	PROPCAPS_ACTION_SOURCE_MULTI = 0x0200,	// erzeugt mehrere Objektmengen

	PROPCAPS_ACTION_SINK = 0x0400,			// verarbeitet eine Objektmenge
	PROPCAPS_ACTION_SINK_MULTI = 0x0800,	// verarbeitet mehrere Objektmengen
//
// IPropertyAction erfordert RePaint/RePaintLegend
	PROPCAPS_ACTION_MUSTREPAINT = 0x1000,	// erfordert RePaint
	PROPCAPS_ACTION_MUSTREPAINTLEGEND = 0x2000,	// erfordert RePaintLegend
//
// IPropertyAction ist eine SearchEngine
	PROPCAPS_ACTION_SEARCHENGINE = 0x8000,	

///////////////////////////////////////////////////////////////////////////////
// Typen der Objekteigenschaften
// die folgenden gelten für Objekteigenschaften (doppelt belegt mit Sequences)
	PROPCAPS_OBJPROPTYPE_NOT_FOR_POINTS = 0x00000100,	// für Punktobjekte nicht anwenden
	PROPCAPS_OBJPROPTYPE_NOT_FOR_LINES = 0x00000200,	// für Linienobjekte nicht anwenden
	PROPCAPS_OBJPROPTYPE_NOT_FOR_AREAS = 0x00000400,	// für Flächenobjekte nicht anwenden
	PROPCAPS_OBJPROPTYPE_NOT_FOR_TEXTS = 0x00000800,	// für Textobjekte nicht anwenden

	PROPCAPS_OBJPROPTYPE_STRING = 0x00000000,	// Objekteigenschaft liefert Zeichenkette
	PROPCAPS_OBJPROPTYPE_INTEGER = 0x00010000,	// Objekteigenschaft liefert integer - Zahlen
	PROPCAPS_OBJPROPTYPE_DOUBLE = 0x00020000,	// Objekteigenschaft liefert floatpoint - Zahlen
	PROPCAPS_OBJPROPTYPE_BOOL = 0x00040000,		// Objekteigenschaft liefert Bool
	PROPCAPS_OBJPROPTYPE_DATE = 0x00080000,		// Objekteigenschaft liefert Datum
	PROPCAPS_OBJPROPTYPE_UNKNOWN = 0x00800000,	// Objekteigenschaft unbekannt

	PROPCAPS_OBJPROPTYPE_VOLATILE = 0x01000000,	// Wert der Objekteigenschaft niemals im cache halten

///////////////////////////////////////////////////////////////////////////////
// Typen der PropertyAction-'Container'
	PROPCAPS_CONTAINER_IS_SEQUENCE = 0x80000000,	// Container ist PropertySequence
	PROPCAPS_CONTAINER_IS_CHOICE = 0x40000000,		// Container ist PropertyChoice

///////////////////////////////////////////////////////////////////////////////
// Für Initialisierungszwecke: unbekannte Eigenschaften
	PROPCAPS_UNKNOWN = 0xFFFFFFFF,

} PROPCAPS;

///////////////////////////////////////////////////////////////////////////////
// Interface einer Erweiterung zum Hinzufügen neuer Objekteigenschaften
#undef INTERFACE
#define INTERFACE IObjectProps2

// 079638C3-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_IObjectProps2, 0x079638C3L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
interface DECLSPEC_UUID("079638C3-3123-101C-BB62-00AA0018497C")
IObjectProps2 : public IUnknown
{
// *** IObjectProps2 specific functions ***
	STDMETHOD(CreateNewProp) (THIS_ LPCSTR pcName, DWORD dwFlags, LONG lONr, 
				VARIANT vOptData, REFIID riid, LPVOID *ppIObjProp) PURE;
	STDMETHOD(DeleteProp) (THIS_ LPCSTR pcName, LONG lONr) PURE;
};

///////////////////////////////////////////////////////////////////////////////
// Interface einer Erweiterung zum Hinzufügen neuer Objekteigenschaften
#undef INTERFACE
#define INTERFACE IObjectProps3

// {D6A95B0F-F1F0-4F3D-A975-2AF295AC9C86}
// DEFINE_GUID(IID_IObjectProps3, 0xD6A95B0F, 0xF1F0, 0x4F3D, 0xA9, 0x75, 0x2A, 0xF2, 0x95, 0xAC, 0x9C, 0x86);
interface DECLSPEC_UUID("D6A95B0F-F1F0-4F3D-A975-2AF295AC9C86")
IObjectProps3 : public IObjectProps2
{
// *** IObjectProps3 specific functions ***
	STDMETHOD(CreateNewPropClass) (THIS_ LPCSTR pcName, DWORD dwFlags, LONG lIdent, 
				VARIANT vOptData, REFIID riid, LPVOID *ppIObjProp) PURE;
	STDMETHOD(DeletePropClass) (THIS_ LPCSTR pcName, LONG lIdent) PURE;
};

///////////////////////////////////////////////////////////////////////////////
// Interface für ImportErweiterungen (optional) -------------------------------
#include <istatus.h>

#undef INTERFACE
#define INTERFACE IImportGeoData

// 07963805-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_IImportGeoData, 0x07963805L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
interface DECLSPEC_UUID("07963805-3123-101C-BB62-00AA0018497C")
IImportGeoData : public IUnknown
{
// ** IImportGeoData methods
	STDMETHOD_(DWORD, Capabilities)(THIS) PURE;
	STDMETHOD(Configure) (THIS_ HWND hWnd) PURE;
	STDMETHOD(ImportData) (THIS_ IEnumString *pEnumFiles, DWORD dwFlags) PURE;
	STDMETHOD(GetConfigInfo) (THIS_ IEnumString **ppEnumCfgInfo, DWORD dwReserved) PURE;
};
typedef IImportGeoData *LPIMPORTGEODATA;

/////////////////////////////////////////////////////////////////////////////
// 261288A3-F3DF-11D1-862E-00600875138A
// DEFINE_GUID(IID_IImportGeoDataWithResult, 0x261288a3, 0xf3df, 0x11d1, 0x86, 0x2e, 0x00, 0x60, 0x08, 0x75, 0x13, 0x8a);
interface DECLSPEC_UUID("261288A3-F3DF-11D1-862E-00600875138A")
IImportGeoDataWithResult : public IUnknown
{
// ** IImportGeoDataWithResult methods
	STDMETHOD(ImportDataWithResult) (THIS_ IEnumString *pEnumFiles, DWORD dwFlags, IProgressIndicator *pIStatus, IEnumLONG **ppIObjs) PURE;
};
typedef IImportGeoDataWithResult *LPIMPORTGEODATAWITHRESULT;

/////////////////////////////////////////////////////////////////////////////
// 215799C9-42CC-4E08-AD7A-4B43D75558CC
// DEFINE_GUID(IID_IImportGeoDataSelectCS, 0x215799C9, 0x42CC, 0x4E08, 0xAD, 0x7A, 0x4B, 0x43, 0xD7, 0x55, 0x58, 0xCC);
interface DECLSPEC_UUID("215799C9-42CC-4E08-AD7A-4B43D75558CC")
IImportGeoDataSelectCS : public IUnknown
{
// ** IImportGeoDataWithResultCS methods
	STDMETHOD(put_CS) (THIS_ IUnknown *pICS) PURE;
};
typedef IImportGeoDataSelectCS *LPIMPORTGEODATASELECTCS;

/////////////////////////////////////////////////////////////////////////////
// 01B87FE3-FC0A-4C3B-A8C4-F96EBB2B2CB3
// DEFINE_GUID(IID_ITRiASImportWizardPropExt, 0x01b87fe3, 0xfc0a, 0x4c3b, 0xa8, 0xc4, 0xf9, 0x6e, 0xbb, 0x2b, 0x2c, 0xb3);
interface DECLSPEC_UUID("01B87FE3-FC0A-4C3B-A8C4-F96EBB2B2CB3")
ITRiASImportWizardPropExt : public IUnknown
{
// ** ITRiASImportWizardPropExt methods
	STDMETHOD(InitForImportDialog) (THIS_ IImportGeoData *pIImport, BSTR Caption, UINT dwFlags) PURE;
	STDMETHOD(get_PageCount) (THIS_ UINT *puiCnt) PURE;
	STDMETHOD(put_SelectedFiles) (THIS_ IEnumString *pEnumFiles) PURE;
};
typedef ITRiASImportWizardPropExt *LPTRIASIMPORTWIZARDPROPEXT;

/////////////////////////////////////////////////////////////////////////////
// 51EC1F47-0BBB-4C13-A5C9-EFBC5FFA6A1F 
// DEFINE_GUID(IID_ITRiASImportWizardPropExt2, 0x01b87fe3, 0xfc0a, 0x4c3b, 0xa8, 0xc4, 0xf9, 0x6e, 0xbb, 0x2b, 0x2c, 0xb3);
interface DECLSPEC_UUID("51EC1F47-0BBB-4C13-A5C9-EFBC5FFA6A1F")
ITRiASImportWizardPropExt2 : public ITRiASImportWizardPropExt
{
// ** ITRiASImportWizardPropExt2 methods
	STDMETHOD(put_FirstPageId) (THIS_ UINT uiFirstPageId) PURE;
	STDMETHOD(get_StartPageId) (THIS_ UINT *puiStartPageId) PURE;
	STDMETHOD(put_ContextHandle) (THIS_ INT_PTR hPr) PURE;
	STDMETHOD(put_ImportFlags) (THIS_ DWORD dwFlags) PURE;
};
typedef ITRiASImportWizardPropExt2 *LPTRIASIMPORTWIZARDPROPEXT2;

/////////////////////////////////////////////////////////////////////////////
// Flags, die von Capabilities geliefert werden können 
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

/////////////////////////////////////////////////////////////////////////////
// Flags, die festlegen, was gemacht werden soll 
typedef enum tagTOIMPORT {
	TOIMPORT_GEOMETRY = 0x0001,		// Geometrie importieren
	TOIMPORT_FEATURES = 0x0002,		// Merkmale importieren
	TOIMPORT_RELATIONS = 0x0004,		// Relationen importieren
	TOIMPORT_VISUALISATION = 0x0008,	// Visualisierung importieren
	TOIMPORT_ANSIOEM = 0x0010,		// aus DOS-Zeichensatz konvertieren
} TOIMPORT;

/////////////////////////////////////////////////////////////////////////////
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
	DRAGDROPTYPE_FRAMEWINDOW = 0x0004,	// Hauptfenster
} DRAGDROPTYPE;

// 079638BA-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_IDragDropAction, 0x079638BAL, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
interface DECLSPEC_UUID("079638BA-3123-101C-BB62-00AA0018497C")
IDragDropAction : public IUnknown
{
// *** IDragDropAction
	STDMETHOD(BeginDragDrop) (THIS_ DRAGDROPTYPE rgType, HWND hWndSrc, DWORD dwFlags, IDataObject *pIDO) PURE;
	STDMETHOD(DoDragDrop) (THIS_ DRAGDROPTYPE rgType, HWND hWnd, IDataObject *pIDO, 
		IDropSource *pISrc,	DWORD dwOKEffects, LPDWORD pdwEffect) PURE;
	STDMETHOD(EndDragDrop) (THIS_ DRAGDROPTYPE rgType, HWND hWndSrc, DWORD dwEffect) PURE;
};
typedef IDragDropAction *LPDRAGDROPACTION;

// 079638C0-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_ITRiASDropTarget, 0x079638C0L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
interface DECLSPEC_UUID("079638C0-3123-101C-BB62-00AA0018497C")
ITRiASDropTarget : public IUnknown
{
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

