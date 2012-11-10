///////////////////////////////////////////////////////////////////////////
// Extmain3.hxx
//
// 21.02.2001 19:41:15
//		 Added ITRiASDBEngineEvents

#if !defined(_EXTMAIN3_HXX__A37D8267_4A3F_11d1_96DC_00A024D6F582__INCLUDED_)
#define _EXTMAIN3_HXX__A37D8267_4A3F_11d1_96DC_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <xtensnxx.h>
#include <triasprv.h>
#include <triastlb.h>
#include <TRiASHelper.h>

#include "strings.h"
#include "mru.h"

#if !defined(_OLD_DRAGNDROP)
#include "DragDropCallback.h"
#include "ViewDrop.h"
#endif // !defined(_OLD_DRAGNDROP)

///////////////////////////////////////////////////////////////////////////////
// TimerID's
#define TIMER_HALFSECOND	1		// 500 ms
#define TIMER_MINUTE		2		// 60 s

// ID des View-Fensters -------------------------------------------------------
#define ID_TRIASVIEW_GEODB		0xE900		// AFX_IDW_PANE_FIRST

///////////////////////////////////////////////////////////////////////////////
// Ausgezogener Event, um an die EventParameter ranzukommen -------------------
#if defined(WIN16)
#if !defined(NAKEDEVT)
#define NAKEDEVT
class NakedEvt : public Event {
public:
		NakedEvt (UINT uiMsg, WPARAM w, LPARAM l)
			{ wMsg = uiMsg; wParam = w; lParam = l; EvtExtra = NULL; }

	UINT wmsg (void) { return wMsg; }
	WPARAM WParam (void) { return wParam; }
	WPARAM wparam (void) { return wParam; }
	LPARAM LParam (void) { return lParam; }
	LPARAM lparam (void) { return lParam; }
};
#endif // !NAKEDEVT
#endif // WIN16

///////////////////////////////////////////////////////////////////////////////
// Eine derzeit geladenen Erweiterung -----------------------------------------
class CMenuItemList;

typedef enum tagEXTENSIONFLAG {
	EF_Global = 0x01,
	EF_UnLoadable = 0x02,
	EF_Visible = 0x04,
	EF_CanImport = 0x08,
	EF_DynImportCfg = 0x10,
	EF_Aggregate = 0x20,
	EF_NoFlags = 0x00,
	EF_Flags = 0x1f,
	EF_DragDropTarget = 0x200,
} EXTENSIONFLAG;

class Extension {
public:
	enum ExtensionType {
		DirectExt = 1,
		OleExt = 2,
	};

private:
	ULONG m_ulRefCnt;	// ReferenzZähler
	
	UINT m_uiMenuOffset;	// ItemOffset

	int m_iMenuIndex;	// Index im HauptMenu
	int m_iORMenuIndex;	// Index im ObjRechMenu
	string m_strMenuString;	// Text im HauptMenu
	string m_strORMenuString;	// Text im ORMenu

	HMENU m_hMenuHandle;	// Handle des PopupMenu's
	HMENU m_hORMenuHandle;	// ObjRechMenu

	string m_strExtName;	// Bezeichnung dieser Erweiterung
	string m_strDLLName;	// Name dieser Erweiterung

	unsigned int m_iToLoad : 2;	// Erweiterung ist geladen

	unsigned int m_fIsGlobal : 1;	// Erweiterung ist global
	unsigned int m_fUnLoadable : 1;	// darf entladen werden
#if !defined(WIN16)
	unsigned int m_fVisible : 1;	// in Dialogen angezeigt
#endif // WIN32
	unsigned int m_fCanImport : 1;		// ImportErweiterung
	unsigned int m_fDynImportCfg : 1;	// dynamisch Importformat abfragen

protected:
	HWND m_hWnd;		// FensterHandle

public:
// Konstruktor/Destruktor
		Extension (HWND, LPCSTR pExtName, LPCSTR pDLLName, int);
		Extension (Extension &);
	virtual	~Extension (void);

virtual	bool MenuInit (MenuInitEvt, HWND = 0) = 0;
virtual	bool MenuSelect (MenuSelectEvt, HWND = 0) = 0;
virtual	bool MenuCommand (MenuCommandEvt, HWND = 0) = 0;
virtual	HRESULT Load (TRIASLOADEX &, IUnknown *pIUnkOut = NULL, HPROJECT hPr = NULL, IUnknown *pIUnk = NULL, bool fShowLicenceErrors = true) = 0;
virtual	bool UnLoad (void) = 0;
virtual	bool Init (short iMode, ITriasXtensionSite *) = 0;

virtual	int GetCapability (WPARAM iCapType) = 0;
virtual	bool EnumObjPropFuncs (ENUMOBJPROPDATA *pEOPD, LONG lRefONr) = 0;
virtual	char *InvokePropFunc (INVOKEOBJPROPDATA *) = 0;
virtual	char *GetHelpText (GETHELPTEXTDATA *) = 0;

virtual HDEX hLib (void) = 0;

virtual ExtensionType isA (void) = 0;
virtual	LRESULT Notify (HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam) = 0;

#if !defined(_OLD_DRAGNDROP)
///////////////////////////////////////////////////////////////////////////////
// Drag'n Drop
virtual HRESULT DragEnter (DRAGDROPTYPE rgType, HWND hWnd, IDataObject *pIDataSource, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect) = 0;
virtual HRESULT DragOver (DRAGDROPTYPE rgType, HWND hWnd, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect) = 0;
virtual HRESULT DragLeave (DRAGDROPTYPE rgType, HWND hWnd) = 0;
virtual HRESULT Drop (DRAGDROPTYPE rgType, HWND hWnd, IDataObject *pIDataSource, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect) = 0;

virtual HRESULT BeginDragDrop (DRAGDROPTYPE rgType, HWND hWnd, DWORD dwFlags, IDataObject *pIDO) = 0;
virtual HRESULT EndDragDrop (DRAGDROPTYPE rgType, HWND hWnd, DWORD dwFlags) = 0;
#endif // !_OLD_DRAGNDROP

// sonstige Memberfunktionen
	short isMyMenu (MenuInitEvt);
	bool isMyORMenu (MenuInitEvt);
	bool isMyID (UINT);
	bool hasMenuItems (short);

virtual bool IsAggregated (void) = 0;

inline	ULONG AddRef (void) { return ++m_ulRefCnt; }
inline	ULONG Release (void) { return m_ulRefCnt ? --m_ulRefCnt : 0L; }

// InlineFunktionen für den direkten Zugriff auf diverse Member
inline	UINT &MenuOffset (void) { return m_uiMenuOffset; }
inline	int &MenuIndex (void) { return m_iMenuIndex; }
inline	int &ORMenuIndex (void) { return m_iORMenuIndex; }
inline	HMENU &MenuHandle (void) { return m_hMenuHandle; }
inline	HMENU &ORMenuHandle (void) { return m_hORMenuHandle; }
inline	string &ExtName (void) { return m_strExtName; }
inline	const string &DLLName (void) const { return m_strDLLName; }
inline	string &MenuString (void) { return m_strMenuString; }
inline	string &ORMenuString (void) { return m_strORMenuString; }
inline	int isLoaded (void) const { return m_iToLoad; }
inline	void SetLoaded (int iLoaded) { m_iToLoad = iLoaded; }
inline	bool isGlobal (void) const { return m_fIsGlobal ? true : false; }
inline	void SetGlobal (bool fGlobal) { m_fIsGlobal = (fGlobal ? true : false); }
inline	bool isUnLoadable (void) const { return m_fUnLoadable ? true : false; }
inline	void SetUnLoadable (bool fUnLoadable) { m_fUnLoadable = (fUnLoadable ? true : false); }
inline	HWND hWnd (void) const { return m_hWnd; }
#if !defined(WIN16)
inline	bool isVisible (void) const { return m_fVisible ? true : false; }
inline	void SetVisible (bool fVisible) { m_fVisible = (fVisible ? true : false); }
#else
inline	bool isVisible (void) const { return true; }
inline	void SetVisible (bool fVisible) {}
#endif
inline	int FCanImport (void) const { return m_fCanImport ? true : false; }
inline	int FDynImportCfg (void) const { return m_fDynImportCfg ? true : false; }
inline	void SetCanImport (bool fFlag) { m_fCanImport = fFlag ? true : false; }
inline	void SetDynImportCfg (bool fFlag) { m_fDynImportCfg = fFlag ? true : false; }
inline	void SetImport (int fImport) 
	{ m_fCanImport = fImport&EF_CanImport; m_fDynImportCfg = fImport&EF_DynImportCfg; }

	EXTENSIONFLAG GetFlags (void);

// Zugriff auf Schlüssel im ExtensionBaum
static	void *GetExtName (void *);
static	int CmpExtNames (void *, void *);
};

class COleExtension : 
	public Extension 
{
private:
	IUnknown *m_pIUnk;			// IUnknown der Erweiterung
	LPTRIASXTENSION	m_pTE;		// OLE-Interface
	LPOBJECTPROPS m_pOPs;		// Objekt-/ClassProperties
	HDEX m_hDex;
	CLSID m_ClsId;			// CLSID dieser Erweiterung
	
	string m_strRegKey;
	UINT m_uiBmp;

	unsigned int m_fHasOPs : 1;	// hat Objekteigenschaften
	unsigned int m_fHasCOPs : 1;	// hat KlassenEigenschaften
	unsigned int m_fAggregated : 1;	// wurde aggregiert
	unsigned int m_fNoDragDropTarget : 1;	// kein DragDropTarget unterstützt
	unsigned int m_fNoDragDropSource : 1;	// kein DragDropSource unterstützt

public:
		COleExtension (HWND hWnd, LPCSTR pTypeName, LPCSTR pProgID, 
			       REFCLSID rClsId, int toLoad, UINT uiBmp, LPCSTR pcRegKey = NULL);
		COleExtension (COleExtension &);
		~COleExtension (void);

// virtuelle Funktionen
	HRESULT Load (TRIASLOADEX &, IUnknown *pIUnkOut = NULL, HPROJECT hPr = NULL, IUnknown *pIXtsn = NULL, bool fShowLicenceErrors = true);
	bool UnLoad (void);
	bool Init (short iMode, ITriasXtensionSite *);

	bool MenuInit (MenuInitEvt, HWND = 0);
	bool MenuSelect (MenuSelectEvt, HWND = 0);
	bool MenuCommand (MenuCommandEvt, HWND = 0);

	ExtensionType isA (void);

	int GetCapability (WPARAM iCapType);
	bool EnumObjPropFuncs (ENUMOBJPROPDATA *pEOPD, LONG lRefONr);
	char *InvokePropFunc (INVOKEOBJPROPDATA *);
	char *GetHelpText (GETHELPTEXTDATA *);
	
	HDEX hLib (void);

	LRESULT Notify (HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam);

	HRESULT GetImportIF (LPIMPORTGEODATA *);
	HRESULT GetConfigInfo (IEnumString **pIStr);

	HRESULT EnumObjPropFuncs (LONG lRefONr, LPENUMOBJPROPS *ppIEnumOPs, 
				  LPOBJECTPROPS *ppIObjProps = NULL);
	HRESULT EnumObjPropFuncsClass (LONG lIdent, LONG lONr, LPENUMOBJPROPS *ppIEnumOPs, 
				  LPOBJECTPROPS *ppIObjProps = NULL);
	HRESULT EnumClsPropFuncs (IEnumLONG *pIEnum, LPENUMCLASSPROPS *ppIEnumOPs, 
				  LPOBJECTPROPS *ppIObjProps = NULL);

#if _TRiAS_VER < 0x0400
	HRESULT HandleLicense (IUnknown *pIUnk);
#endif // _TRiAS_VER < 0x0400

	HRESULT QueryInterface (REFIID riid, LPVOID *ppIUnk);
inline	bool IsExtension (REFCLSID rClsId) { return rClsId == m_ClsId; }

	bool IsAggregated (void) { return m_fAggregated ? true : false; }
	void SetAggregated (bool fFlag) { m_fAggregated = fFlag ? true : false; }
	void DisableDragDrop (void) { m_fNoDragDropTarget = m_fNoDragDropSource = true; }

	const string &GetRegKey() const { return m_strRegKey; }
	UINT GetBmp() { return m_uiBmp; }
	HRESULT GetCLSID (CLSID *pclsID) { *pclsID = m_ClsId; return S_OK; }

#if !defined(_OLD_DRAGNDROP)
///////////////////////////////////////////////////////////////////////////////
// Drag'n Drop
	HRESULT DragEnter (DRAGDROPTYPE rgType, HWND hWnd, IDataObject *pIDataSource, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect);
	HRESULT DragOver (DRAGDROPTYPE rgType, HWND hWnd, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect);
	HRESULT DragLeave (DRAGDROPTYPE rgType, HWND hWnd);
	HRESULT Drop (DRAGDROPTYPE rgType, HWND hWnd, IDataObject *pIDataSource, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect);

	HRESULT BeginDragDrop (DRAGDROPTYPE, HWND, DWORD, IDataObject *);
	HRESULT EndDragDrop (DRAGDROPTYPE rgType, HWND hWnd, DWORD dwFlags);
#endif // !_OLD_DRAGNDROP
};

#define LENoLoad	0x00
#define LEInitOnly	0x01
#define LEFullLoad	0x02

// Liste aller derzeit aktivierten Erweiterungen ------------------------------
EXTERN_C const IID IID_ITRiASDropTarget;
EXTERN_C const IID IID_IDragDropAction;
EXTERN_C const IID IID_IObjectProps;
EXTERN_C const IID IID_IObjectProps2;
EXTERN_C const IID IID_ITriasXtensionSite;

#if defined(__ATL_20_USED__)
typedef IConnectionPointContainerImpl<class ExtensionList> CComTRiASCPC;
#include "CPTriasTlb2.h"		// ConnPntProxies
#else
typedef CComConnectionPointContainerImpl CComTRiASCPC;
#include "CPTriasTlb.h"			// ConnPntProxies
#endif // __ATL_20_USED__

///////////////////////////////////////////////////////////////////////////////
// forward declarations
class CAllProperties;
class ExtDirisWindow;

class ExtensionList : 
	public CComObjectRoot,
	public ITriasXtensionSite,
	public ITRiASDropTarget,
	public IDragDropAction,
#if defined(__ATL_20_USED__)
	public ITRiASDBEngineEvents,
	public ITRiASProjectEvents,
	public ITRiASConnectionEvents,
	public CProxyITRiASNotificationSink<ExtensionList>,
	public CProxyITRiASSysNotificationSink<ExtensionList>,
#endif // __ATL_20_USED__
	public CComTRiASCPC			// ConnectionPointContainer
{
private:
#if !defined(__ATL_20_USED__)
	CProxyITRiASNotificationSink m_cp;
	CProxyITRiASSysNotificationSink m_cpSys;
#endif // !__ATL_20_USED__

// dieses TRiAS ist DatenQuelle des aktuellen Drag'n Drops
	LONG m_lIsDropSourceInst;

public:
// unterstützte ConnectionPoints
#if !defined(__ATL_20_USED__)
	BEGIN_CONNECTION_POINT_MAP(ExtensionList)
		CONNECTION_POINT_ENTRY(m_cp)
		CONNECTION_POINT_ENTRY(m_cpSys)
	END_CONNECTION_POINT_MAP()

// ITRiASNotificationSink bedienen
	HRESULT ServerEvent (SERVEREVT se) { return m_cp.ServerEvent (se); }
	HRESULT ProjectEvent (HPROJECT hPr, PROJECTEVT pe, VARIANT vPrj) { return m_cp.ProjectEvent (long (hPr), pe, vPrj); }
	HRESULT GeoViewEvent (HPROJECT hPr, GEOVIEWEVT ve, VARIANT vData) { return m_cp.GeoViewEvent (long(hPr), ve, vData); }
	HRESULT GeoClassEvent (HPROJECT hPr, GEOCLASSEVT ce, long ulIdent) { return m_cp.GeoClassEvent (long(hPr), ce, ulIdent); }
	HRESULT GeoObjectEvent (HPROJECT hPr, GEOOBJECTEVT oe, long lONr) { return m_cp.GeoObjectEvent (long(hPr), oe, lONr); }
	HRESULT GeoFeatureEvent (HPROJECT hPr, GEOFEATUREEVT fe, long ulMCode) { return m_cp.GeoFeatureEvent (long(hPr), fe, ulMCode); }
	HRESULT GeoRelationEvent (HPROJECT hPr, GEORELATIONEVT re, long ulRCode) { return m_cp.GeoRelationEvent (long(hPr), re, ulRCode); }
    HRESULT ObjectWindowEvent (OBJWNDEVT oe, long hORWnd) { return m_cp.ObjectWindowEvent (oe, hORWnd); }

// ITRiASSysNotificationSink
	HRESULT WindowsMessage (HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
		{ return m_cpSys.WindowsMessage ((long)hWnd, uiMsg, wParam, lParam); }
#else
	BEGIN_CONNECTION_POINT_MAP(ExtensionList)
		CONNECTION_POINT_ENTRY(IID_ITRiASNotificationSink)
		CONNECTION_POINT_ENTRY(IID_ITRiASSysNotificationSink)
	END_CONNECTION_POINT_MAP()

// ITRiASNotificationSink bedienen
	HRESULT ServerEvent (SERVEREVT se) { return Fire_ServerEvent (se); }
	HRESULT ProjectEvent (HPROJECT hPr, PROJECTEVT pe, VARIANT vPrj) { return m_fNotify ? S_OK : Fire_ProjectEvent (long (hPr), pe, vPrj); }
	HRESULT GeoViewEvent (HPROJECT hPr, GEOVIEWEVT ve, VARIANT vData) { return m_fNotify ? S_OK : Fire_GeoViewEvent (long(hPr), ve, vData); }
	HRESULT GeoClassEvent (HPROJECT hPr, GEOCLASSEVT ce, long ulIdent) { return m_fNotify ? S_OK : Fire_GeoClassEvent (long(hPr), ce, ulIdent); }
	HRESULT GeoObjectEvent (HPROJECT hPr, GEOOBJECTEVT oe, long lONr) { return m_fNotify ? S_OK : Fire_GeoObjectEvent (long(hPr), oe, lONr); }
	HRESULT GeoFeatureEvent (HPROJECT hPr, GEOFEATUREEVT fe, long ulMCode) { return m_fNotify ? S_OK : Fire_GeoFeatureEvent (long(hPr), fe, ulMCode); }
	HRESULT GeoRelationEvent (HPROJECT hPr, GEORELATIONEVT re, long ulRCode) { return m_fNotify ? S_OK : Fire_GeoRelationEvent (long(hPr), re, ulRCode); }
    HRESULT ObjectWindowEvent (OBJWNDEVT oe, long hORWnd) { return m_fNotify ? S_OK : Fire_ObjectWindowEvent (oe, hORWnd); }

// ITRiASSysNotificationSink
	HRESULT WindowsMessage (HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
		{ return Fire_WindowsMessage ((long)hWnd, uiMsg, wParam, lParam); }
#endif

public:
	class CExtTree : public CTree {
	protected:
		void UserDelete (void *);

	public:
			CExtTree (void) 
				: CTree (Extension::GetExtName, Extension::CmpExtNames) {}
			~CExtTree (void);
	
	friend class ExtensionList;
	};

private:
	CExtTree m_Exts;				// Baum, der Erweiterungen enthält
	CMenuItemList *m_pMIL;
	CImageList m_ilExtIcons;		// Bildchen für Erweiterungen
	CAllProperties *m_pProps;		// IObjectProps
	string m_strActOProp;			// in ORFenstern anzuzeigende OPF
	DWORD m_dwConnCookie;			// Cookie für ITRiASConnectionEvents
	bool m_fNotify;					// evtl. keine Notifications rumschicken

public:	
// Handling der anzuzeigenden OPF
	string &GetActOProp (void) { return (string &)m_strActOProp; }
	void SetActObjProp (LPCSTR pOPName);
	LPCSTR GetActObjPropName();
	HRESULT QueryActObjProp (IObjectProperty **ppIObjProp);

	HRESULT InvokeActObjProp (LONG lONr, LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten, LPCSTR pcObjProp = NULL);
	HRESULT ResetActObjProp (LPCSTR pcObjProp = NULL);

	void ResetObjProps (bool fReleaseAll = false);
	void ResetClsProps (void);
	void FeatureSetModified (INT_PTR lIdent);
	
	bool IsNotify() { return m_fNotify; }
	void SetNotificationMode (bool fNotify) { m_fNotify = fNotify; }

public:
inline	operator CKeyContainer& (void) { return (CKeyContainer &)m_Exts; }
inline	operator ExtensionList::CExtTree& (void) { return m_Exts; }
	
	void EveryDelete (void);

protected:
		ExtensionList();

	void UserDelete (void *pObj);
	bool FInit();

public:
	friend HRESULT WINAPI QueryObjProp (void* pv, REFIID riid, LPVOID* ppv, DWORD dw);
	friend HRESULT WINAPI QueryObjProp2 (void* pv, REFIID riid, LPVOID* ppv, DWORD dw);
	friend HRESULT WINAPI QueryAggrIF (void* pv, REFIID riid, LPVOID* ppv, DWORD dw);

	BEGIN_COM_MAP(ExtensionList)
		COM_INTERFACE_ENTRY(ITriasXtensionSite)
		COM_INTERFACE_ENTRY(ITRiASDBEngineEvents)
		COM_INTERFACE_ENTRY(ITRiASProjectEvents)
		COM_INTERFACE_ENTRY(ITRiASConnectionEvents)
		COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
		COM_INTERFACE_ENTRY(ITRiASDropTarget)
		COM_INTERFACE_ENTRY(IDragDropAction)
		COM_INTERFACE_ENTRY_FUNC(IID_IObjectProps, 0L, QueryObjProp)
		COM_INTERFACE_ENTRY_FUNC(IID_IObjectProps2, 0L, QueryObjProp2)
		COM_INTERFACE_ENTRY_FUNC(__uuidof(IObjectProps3), 0L, QueryObjProp2)
		COM_INTERFACE_ENTRY_FUNC_BLIND(0L, QueryAggrIF)
	END_COM_MAP()

// *** ITriasXtensionSite methods
	STDMETHOD(GetXtension) (THIS_ REFCLSID rClsID, REFIID rIID, LPVOID *ppIUnk);
	STDMETHOD(CreateInstance) (THIS_ LPUNKNOWN pUnkOuter, REFCLSID rClsID, REFIID riid, LPVOID *ppUnk);

// *** ITRiASDBEngineEvents methods
	STDMETHOD(AskToContinue)(CONTINUEMODE *prgMode);

// *** ITRiASProjectEvents methods
	STDMETHOD(ProjectToCreate)(BSTR Name);
	STDMETHOD(ProjectCreated)(IDispatch *pIPrj);
	STDMETHOD(OpeningProject)(BSTR Name, VARIANT_BOOL *pVal);
	STDMETHOD(ProjectToOpen)(BSTR Name);
	STDMETHOD(ProjectIsOpening)(IDispatch *pIPrj);
	STDMETHOD(ProjectOpened)(IDispatch *pIPrj);
	STDMETHOD(ClosingProject)(IDispatch *pIPrj, VARIANT_BOOL *pVal);
	STDMETHOD(ProjectToClose)(IDispatch *pIPrj);
	STDMETHOD(ProjectClosed)(BSTR Name);
	STDMETHOD(Save)(IDispatch *pIPrj, IUnknown *Stg, VARIANT_BOOL fSameAsLoad);
	STDMETHOD(SaveCompleted)(IDispatch *pIPrj, VARIANT Stg);
	STDMETHOD(HandsOffStorage)(IDispatch *pIPrj);
	STDMETHOD(ErrorOpeningProject)(IDispatch *pIPrj);

// ITRiASConnectionEvents
	STDMETHOD(CreatingConnection)(/*[in]*/ BSTR Name, /*[retval][out]*/ VARIANT_BOOL *pVal);
	STDMETHOD(ConnectionToCreate)(/*[in]*/ BSTR Name);
	STDMETHOD(ConnectionCreated)(/*[in]*/ IDispatch *pIConn);
	STDMETHOD(OpeningConnection)(/*[in]*/ BSTR Name, /*[retval][out]*/ VARIANT_BOOL *pVal);
	STDMETHOD(ConnectionToOpen)(/*[in]*/ BSTR Name);
	STDMETHOD(ConnectionOpened)(/*[in]*/ IDispatch *pIConn);
	STDMETHOD(ClosingConnection)(/*[in]*/ IDispatch *pIConn, /*[retval][out]*/ VARIANT_BOOL *pVal);
	STDMETHOD(ConnectionToClose)(/*[in]*/ IDispatch *pIConn);
	STDMETHOD(ConnectionClosed)(/*[in]*/ BSTR Name);
	STDMETHOD(DeletingConnection)(/*[in]*/ IDispatch *pIConn, /*[retval][out]*/ VARIANT_BOOL *pVal);
	STDMETHOD(ConnectionToDelete)(/*[in]*/ IDispatch *pIConn);
	STDMETHOD(ConnectionDeleted)(/*[in]*/ BSTR Name);
	STDMETHOD(RenamingConnection)(/*[in]*/ BSTR OldName, /*[in]*/ BSTR NewName, /*[retval][out]*/ VARIANT_BOOL *pVal);
	STDMETHOD(ConnectionToRename)(/*[in]*/ BSTR OldName, /*[in]*/ BSTR NewName);
	STDMETHOD(ConnectionRenamed)(/*[in]*/ IDispatch *pIConn);
	STDMETHOD(ChangingConnectedDatasource)(/*[in]*/ IDispatch *pIConn, /*[retval][out]*/ VARIANT_BOOL *pVal);
	STDMETHOD(ConnectedDatasourceToChange)(/*[in]*/ IDispatch *pIConn);
	STDMETHOD(ConnectedDatasourceChanged)(/*[in]*/ IDispatch *pIConn);

// Konstruktor/Destruktor
		~ExtensionList (void);

	short CountLoaded (short *piNotUnLoadable = NULL);
	LPSTR RetrieveDLLName (LPCSTR pExtName);
	LPSTR RetrieveExtName (LPCSTR pDLLName);

	short isLoaded (LPCSTR pDLLName, HDEX &hDex);
	UINT GetMRUBaseID (void);

	bool isGlobal (LPCSTR pDLLName);
	bool isUnLoadable (LPCSTR pDLLName);
	bool isVisible (LPCSTR pDLLName);
	bool FCanImport (LPCSTR pDLLName);

	EXTENSIONFLAG GetFlags (LPCSTR pDLLName);
	string GetRegKey (LPCSTR pDLLName);

	bool DispatchMenuCommand (MenuCommandEvt, HWND = 0);

	bool hasMIL (void) { return m_pMIL != NULL; }
	CMenuItemList &MIL (void) { return *m_pMIL; }
	
	long AddRefExt (LPCSTR pDLLName);
	long ReleaseExt (LPCSTR pDLLName);

	Extension *FindExt (HDEX hDex);

// Bildchen für ImageList holen und speichern
	UINT InitToolboxBitmap (LPCSTR pcPseudoProgID, EXTENSIONFLAG rgFlags);
	UINT GetToolBoxBitmapDWORD (LPCSTR pcPseudoProgID);
	UINT GetToolBoxBitmapSZ (LPCSTR pcPseudoProgID);

	const CImageList &GetImageList() const { return m_ilExtIcons; }
	UINT GetBmp (LPCSTR pDLLName);

	HRESULT GetCLSID (LPCSTR pDLLName, CLSID *pclsID);
	HRESULT RetrieveCLSID (LPCSTR pDLLName, EXTENSIONFLAG rgFlags, CLSID *pclsID);

#if !defined(OLD_DRAGDROP)
// *** ITRiASDropTarget methods
	STDMETHOD(DragEnter) (THIS_ DRAGDROPTYPE rgType, HWND hWnd, IDataObject *pIDataSource, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect);
	STDMETHOD(DragOver) (THIS_ DRAGDROPTYPE rgType, HWND hWnd, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect);
	STDMETHOD(DragLeave) (THIS_ DRAGDROPTYPE rgType, HWND hWnd);
	STDMETHOD(Drop) (THIS_ DRAGDROPTYPE rgType, HWND hWnd, IDataObject *pIDataSource, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect);

// *** IDragDropAction methods
	STDMETHOD(BeginDragDrop) (THIS_ DRAGDROPTYPE rgType, HWND hWnd, DWORD dwFlags, IDataObject *pIDO);
	STDMETHOD(DoDragDrop) (THIS_ DRAGDROPTYPE rgType, HWND hWnd, IDataObject *pIDO, 
		IDropSource *pISrc, DWORD dwOKEffects, DWORD *pdwEffect);
	STDMETHOD(EndDragDrop) (THIS_ DRAGDROPTYPE rgType, HWND hWnd, DWORD dwFlags);

inline bool IsDropSource (void) { return m_lIsDropSourceInst >= 0; }
#endif // !OLD_DRAGDROP

#if defined(_DEBUG)
	bool IsValidExtension (HDEX hDex) { return NULL != FindExt (hDex); }
#endif // _DEBUG

	friend class ExtDirisWindow;
};
DeclareLock (ExtensionList::CExtTree, Extension);

///////////////////////////////////////////////////////////////////////////////
#if !defined(NOEXTDIRISWINDOW)

// HauptfensterKlasse, die Erweiterungen verwaltet ----------------------------
class QueryNotifyHash;
class CManageUndoRedo;

typedef struct tagCREATEOBJEKTINFO CREATEOBJEKTINFO;

// forward declaration only ---------------------------------------------------
#if !defined(NEWXTENSIONPROC)
extern "C" _TRIAS_ENTRY LRESULT PASCAL DexExtensionProc (WPARAM w, LPARAM l);
#else
extern "C" _TRIAS_ENTRY LRESULT PASCAL DexExtensionProcOld (WPARAM w, LPARAM l);
#endif // !NEWXTENSIONPROC
extern "C" _TRIAS_ENTRY LRESULT PASCAL DexExtensionProc2 (HPROJECT hPr, WPARAM w, LPARAM l);
extern "C" _TRIAS_ENTRY LRESULT PASCAL DexxExtensionProc (WPARAM w, LPARAM l);
extern "C" _TRIAS_ENTRY LRESULT PASCAL DexxExtensionProc2 (HPROJECT hPr, WPARAM w, LPARAM l);
extern "C" _TRIAS_ENTRY LRESULT PASCAL DexNotificationProc (WPARAM w, LPARAM l);
extern "C" _TRIAS_ENTRY LRESULT PASCAL DexNotificationProcEx (WPARAM w, LPARAM l, bool fPost);
extern "C" _TRIAS_ENTRY LRESULT PASCAL DexDispatchProc (HWND hWnd, UINT uiMsg, WPARAM w, LPARAM l);

typedef enum CREATEVIEW_RESULT {
	CREATEVIEW_RESULT_FAILED = 0,
	CREATEVIEW_RESULT_OK = 1,
	CREATEVIEW_RESULT_NOREPAINT = 0x80,
};

class ExtDirisWindow : 
	public TopAppWindow
{
private:
	CComObject<ExtensionList> *m_pEL;
	QueryNotifyHash *m_pQNH;		// HashTabelle für QNFY's
	UINT m_iMenuOffset;

	bool m_fIsShown;		// Fenster ist angezeigt
	bool m_fToShow;			// Fenster soll angezeigt werden
	bool m_fToInit3d;		// CTL3D.DLL verwenden
	bool m_fMustInitOPFs;	// OPFs müssen neu gelesen werden
	bool m_fHoldZoom;		// Ausschnitt beibehalten
	bool m_fCleanUp;		// still und leise aufhören
	bool m_fCleanedUp;		// fertig aufgeräumt
	bool m_fClosingDocument;	// Dokument wird geradegeschlossen
	bool m_fHandleMRU;		// MRU's in Menues behandeln
	bool m_fViewSelected;	// (eine) Ansicht wurde selektiert
	bool m_fPaintingView;	// es wird derzeit gezeichnet
	bool m_fViewPainted;	// (eine) Ansicht wurde gezeichnet

	typedef LRESULT (ExtDirisWindow :: *DEXMESSAGE_PROC)(HPROJECT, LPARAM);
	typedef LRESULT (ExtDirisWindow :: *DEXNOTIFY_PROC)(LPARAM);

	DEXMESSAGE_PROC *m_cbDexProcs;	// Sprungverteiler (DEX_...)
	unsigned int m_i1stDexProc;		// erste Funktion
	unsigned int m_iDexProcsNum;	// Anzahl der Funktionen in Tabelle

#if defined(_DEBUG)
	typedef LPCSTR (ExtDirisWindow::*DEXMSGDUMP_PROC)(HPROJECT, LPARAM);
	typedef struct tagDEXMSGDUMP_INFO DEXMSGDUMP_INFO;

	DEXMSGDUMP_INFO *m_pDumpInfos;	// DumpInfos für Messages

	LPCSTR DefaultMsgDumper (HPROJECT hPr, LPARAM lParam);
#endif // _DEBUG

	DEXNOTIFY_PROC *m_cbDexProcsNfy;	// Sprungverteiler (DEXN_...)
	unsigned int m_i1stDexProcNfy;	// erste Funktion
	unsigned int m_iDexProcsNumNfy;	// Anzahl der Funktionen in Tabelle

	CManageUndoRedo *m_pUndoRedo;	// Undo/Redo - Verwaltung

	ErrInstall m_eiExt;			// Fehlerbehandlung für LoadExtension
	LONG m_lEnableCnt;			// Enable()/Disable();

// UI-Objekte des FrameWindows
	Menu IrisMenu;				// Menu
	Menu StartMenu;				// StartMenu
	Icon IrisIcon;				// Standardikone
	Accel IrisAcc;				// Acceleratortabelle
	Accel StartAcc;				// StartUp Acceleratoren
	LPMRUMENU m_pMRU;

	Brush m_brushBK;			// HinterGrundBrush für FrameWindow

// aktuelle Abmessungen des Fensters
	Dimension MSize;		// aktuelle Fenstergröße
	Point MOrig;

// das derzeit geöffnete Dokument
	class IrisWind *m_pView;		// Fenster mit geöffnetes Document

private:
	bool FInitDexProcs (void);		// Initialisierung des Sprungverteilers (DEX_...)
	bool FInitDexProcsNfy (void);	// Initialisierung des Sprungverteilers (DEXN_...)
	bool InitGlobals (void);		// Initialisierung der globalen Variablen 

	bool ShowRedoList (void);
	bool ShowUndoList (void);

	LRESULT OnFindIdentFromNameHelper (HPROJECT, char *pName, bool fIgnoreCase);
	LRESULT OnFindMCodeFromNameHelper (HPROJECT, char *pName, bool fIgnoreCase);

protected:
///////////////////////////////////////////////////////////////////////////////
// Funktionen für Eventverarbeitung
	void Expose (ExposeEvt);			// zeichnen
	void MenuCommand (MenuCommandEvt);	// alle MenuCommands
	void MenuSelect (MenuSelectEvt);	// MenuAuswahl
	void MenuInit (MenuInitEvt);		// MenuInitialisierungen
	LRESULT Dispatch (Event);			// eigener Dispatcher
	BOOL QueryClose (Event);			// EndeAbfrage
	void Close (Event);					// Fenster wird geschlossen
	void ReSize (ReSizeEvt);
	void Move (MoveEvt);
	void Strobe (StrobeEvt e);
	void KeyDown (KeyEvt);				// KeyEvents
	void KeyUp (KeyEvt);

	void MouseButtonDn (MouseEvt);			// MausEvents

protected:
///////////////////////////////////////////////////////////////////////////////
// MenuBefehle
	bool doLoadExtension (LPCSTR pcProgID = NULL, int iStartPage = -1);
	bool doLoadExtensionCust (void);
//	bool doSaveOpt(void);
	bool doCreateNewGeoDB (MenuCommandEvt e);
	bool doCloseDocument (void);		// MenuCommandWrapper
	bool doCloseDocumentNow (void);		// workhorse
	bool doOpenDocument (void);
	bool doImport (void);	
	bool doUndo (void);
	bool doRedo (void);
	bool GenObjectProperties (void);
	bool EnterRechResults (void);
	bool ExecuteSequence (void);
	bool doLoadObjColl (void);
	bool doAbout (void);

	bool doOpenOld (MenuCommandEvt);
	bool doExit (MenuCommandEvt);
	bool doDefault (MenuCommandEvt);

	bool doHelpIndex (void);
	bool doHelpID (void);
	bool doHelpMenu (MenuCommandEvt);

public:
// Konstruktor/Destruktor
		ExtDirisWindow (Rectangle &MWnd);
		~ExtDirisWindow (void);

	void Show (ShowState = Normal);
	void RepositionBars (UINT nIDFirst, UINT nIDLast, UINT nIDLeftOver,
		UINT nFlags = reposDefault, LPRECT lpRectParam = NULL, 
		LPCRECT lpRectClient = NULL, BOOL bStretch = true);

// sonstige Memberfunktionen
#if defined(_USE_LEGACY_CODE)
	CREATEVIEW_RESULT CreateView (LPCSTR pcName = NULL, LPCSTR pcUser = NULL, LPCSTR pcPwd = NULL, short gfMode = 0, DWORD dwMode = 0L);
#endif // defined(_USE_LEGACY_CODE)

	CREATEVIEW_RESULT CreateView (BSTR bstrName);
	CREATEVIEW_RESULT InitializeView (ITRiASProject *pIPrj, bool fCreate);
	HRESULT InstallObjectProperties (bool fForceNew = false);

	HDEX LoadExtension (LPCSTR pExtName, LPCSTR pDLLName, short iToLoad, 
		EXTENSIONFLAG rgFlags = EXTENSIONFLAG(EF_Visible|EF_Global), 
		LPCSTR pcRegKey = NULL, IUnknown *pIXtsn = NULL, bool fShowLicenceErrors = true);
	bool UnLoadExtension (LPCSTR pExtName, bool fForce = false);
	bool ReUnLoadExtension (LPCSTR pExtName, LPCSTR pDLLName, 
				short iMode = LEInitOnly);

	ErrCode LoadAllExtensions (const char *pIni, bool isGlobal = true);
	ErrCode LoadAllExtensionsINI (LPCSTR pIni, bool isGlobal = true);
	bool LoadAllExtensionsRegistry (void);
	bool LoadExtensionRegistry (string &szTRiASKey, DWORD dwPriority);
	void SaveExtStatus (void);		// CleanUp

	LRESULT FullFillWill (HPROJECT, WPARAM, LPARAM);		// Messages bearbeiten
	LRESULT FullFillCPPWill (HPROJECT, WPARAM, LPARAM);
	LRESULT Dispatch (UINT, WPARAM, LPARAM);				// QueryNotifications
	LRESULT DispatchNotification (WPARAM, LPARAM);

	void DoExec (void);				// MessageLoop
	
// Funktionen, die die Messages der Extension bearbeiten
	char *RetrieveActiveProject (char *);
	char *RetrieveMainProFile (char *);

	HWND CreateObjektInfo (DEXXCREATEOBJEKTINFO *);
	HWND CreateObjektInfo (CREATEOBJEKTINFO *);

	HMENU InstallMenuItem (INSTALLMENUITEM *);	// MenuPunkt installieren
	bool RemoveMenuItem (REMOVEMENUITEM *);		// und wieder rausnehmen
	short InstallTool (INSTALLTOOL *);		// Werkzeug einhängen
	bool RemoveTool (short);

	bool LoadLocalExtensions (void);
	bool UnLoadLocalExtensions (void);		// ProjektErweiterungen entladen
	LRESULT EnumExtensions (ENUMNOKEY *pK);	// Erweiterungen enumerieren
	LRESULT GetExtensionInfo (EXTENSIONINFO *pInfo);
	LRESULT GetExtensionPtr (EXTENSIONPTR *pInfo);

	bool FIsShown (void) { return m_fIsShown; }
	bool FToShow (void) { return m_fToShow; }
	bool FToInit3d (void) { return m_fToInit3d; }
	void FToShow (bool fToShow) { m_fToShow = fToShow ? true : false; }
	void FToInit3d (bool fToInit) { m_fToInit3d = fToInit ? true : false; }

	BOOL RenderGeoDB (RENDERGEODB *);

// Menu liefern
	pMenu MainMenu (void) { return &IrisMenu; }
	pMenu StartUpMenu (void) { return &StartMenu; }
	pAccel MainAcc (void) { return &IrisAcc; }

	bool InitMenues (void);
	bool InitProjectMenu (void);

	bool ReReadCaption (bool fDelay = false);	// Caption aus zugehörigem DBHeader lesen
	bool RetrieveBasicCaption (string &rStrCaption, bool fExpand = true, bool fPureCaption = false);

	bool CleanUpFrame (void);					// abschließendes
	void RestoreStartConfig(void);				// nach Projekt schließen zu rufen

#if !defined(NEWXTENSIONPROC)
_TRIAS_ENTRY friend LRESULT PASCAL DexExtensionProc (WPARAM w, LPARAM l);
#else
_TRIAS_ENTRY friend LRESULT PASCAL DexExtensionProcOld (WPARAM w, LPARAM l);
#endif // NEWXTENSIONPROC
_TRIAS_ENTRY friend LRESULT PASCAL DexExtensionProc2 (HPROJECT hPr, WPARAM w, LPARAM l);
_TRIAS_ENTRY friend LRESULT PASCAL DexxExtensionProc (WPARAM w, LPARAM l);
_TRIAS_ENTRY friend LRESULT PASCAL DexxExtensionProc2 (HPROJECT hPr, WPARAM w, LPARAM l);
_TRIAS_ENTRY friend LRESULT PASCAL DexNotificationProc (WPARAM w, LPARAM l);
_TRIAS_ENTRY friend LRESULT PASCAL DexNotificationProcEx (WPARAM w, LPARAM l, bool fPost);
_TRIAS_ENTRY friend LRESULT PASCAL DexDispatchProc (HWND hWnd, UINT uiMsg, WPARAM w, LPARAM l);

// sonstige MRU-Befehle
	BOOL AddNewItem (bool fStartup, LPCSTR pcStr, bool fRO);
	BOOL DelMenuItem (UINT uiMenuItem, bool fStartUp);
	BOOL GetMenuItem (INT uiMenuItem, bool fStartUp, LPSTR pName, int iLen, BOOL &rfRO);

#if !defined(_OLD_DRAGNDROP)
///////////////////////////////////////////////////////////////////////////////
// Drag'n Drop
private:
	class CMainDragDropCallback :
		public CDragDropCallback
	{
	public:
	// CDragDropCallback
		HRESULT DragEnter (IDataObject *pIDataSource, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
		{
		ExtDirisWindow *pThis = ((ExtDirisWindow *)((BYTE *)this - offsetof(ExtDirisWindow, m_DropCB)));

			return pThis -> DragEnter (DRAGDROPTYPE_FRAMEWINDOW, pThis -> Handle(API_WINDOW_HWND), pIDataSource, grfKeyState, pt, pdwEffect); 
		}
		HRESULT DragOver (DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
		{
		ExtDirisWindow *pThis = ((ExtDirisWindow *)((BYTE *)this - offsetof(ExtDirisWindow, m_DropCB)));

			return pThis -> DragOver (DRAGDROPTYPE_FRAMEWINDOW, pThis -> Handle(API_WINDOW_HWND), grfKeyState, pt, pdwEffect); 
		}
		HRESULT DragLeave (void)
		{
		ExtDirisWindow *pThis = ((ExtDirisWindow *)((BYTE *)this - offsetof(ExtDirisWindow, m_DropCB)));

			return pThis -> DragLeave (DRAGDROPTYPE_FRAMEWINDOW, pThis -> Handle(API_WINDOW_HWND)); 
		}
		HRESULT Drop (IDataObject *pIDataSource, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
		{
		ExtDirisWindow *pThis = ((ExtDirisWindow *)((BYTE *)this - offsetof(ExtDirisWindow, m_DropCB)));

			return pThis -> Drop (DRAGDROPTYPE_FRAMEWINDOW, pThis -> Handle(API_WINDOW_HWND), pIDataSource, grfKeyState, pt, pdwEffect); 
		}

		bool FQueryPasteFromData (IDataObject *pIDataObject) { return false; }
		bool FPasteFromData (IDataObject *pIDataObject) { return false; }
		UINT TestDroppablePoint (POINTL *pPt) { return UDROP_NONE; }
		void GiveFeedBack (POINTL *pPt, bool fRemove = false, bool fDraw = true) {}
		bool IsDropSourceInst() 
		{
		ExtDirisWindow *pThis = ((ExtDirisWindow *)((BYTE *)this - offsetof(ExtDirisWindow, m_DropCB)));

			return pThis -> IsDropSource(); 
		}
	};
	friend CMainDragDropCallback;
	CMainDragDropCallback m_DropCB;
	IDropTarget *m_pDropTgt;

public:
// misc. support functions
	HRESULT DragEnter (DRAGDROPTYPE rgType, HWND hWnd, IDataObject *pIDataSource, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
		{ return m_pEL -> DragEnter (rgType, hWnd, pIDataSource, grfKeyState, pt, pdwEffect); }
	HRESULT DragOver (DRAGDROPTYPE rgType, HWND hWnd, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
		{ return m_pEL -> DragOver (rgType, hWnd, grfKeyState, pt, pdwEffect); }
	HRESULT DragLeave (DRAGDROPTYPE rgType, HWND hWnd)
		{ return m_pEL -> DragLeave(rgType, hWnd); }
	HRESULT Drop (DRAGDROPTYPE rgType, HWND hWnd, IDataObject *pIDataSource, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
		{ return m_pEL -> Drop (rgType, hWnd, pIDataSource, grfKeyState, pt, pdwEffect); }

	inline IsDropSource (void) { return m_pEL -> IsDropSource(); }
#endif // !_OLD_DRAGNDROP

public:
// *** ITRiASDBEngineEvents methods
	HRESULT AskToContinue (CONTINUEMODE *prgMode);

// *** ITRiASProjectEvents methods
	HRESULT ProjectToCreate (BSTR Name);
	HRESULT ProjectCreated (IDispatch *pIPrj);
	HRESULT OpeningProject (BSTR Name, VARIANT_BOOL *pVal);
	HRESULT ProjectToOpen (BSTR Name);
	HRESULT ProjectIsOpening (IDispatch *pIPrj);
	HRESULT ProjectOpened (IDispatch *pIPrj);
	HRESULT ClosingProject (IDispatch *pIPrj, VARIANT_BOOL *pVal);
	HRESULT ProjectToClose (IDispatch *pIPrj);
	HRESULT ProjectClosed (BSTR Name);
	HRESULT Save (IDispatch *pIPrj, IUnknown *Stg, VARIANT_BOOL fSameAsLoad);
	HRESULT SaveCompleted (IDispatch *pIPrj, VARIANT Stg);
	HRESULT HandsOffStorage (IDispatch *pIPrj);
	HRESULT ErrorOpeningProject (IDispatch *pIPrj);

///////////////////////////////////////////////////////////////////////////////
// InlineFunktionen
inline DatenBasisObjekt &DBO (short iIndex) { return m_pView -> DBO(iIndex); }	// ausführliche Variante 
inline DatenBasisObjekt &DBO (HPROJECT hPr) { return m_pView -> DBO(hPr); }	// ausführliche Variante 
inline DatenBasisObjekt &DBO (void) { return m_pView -> DBO(); }			// optimierte Variante
inline bool IsValidActiveView (void) { return m_pView ? m_pView -> IsValidView() : false; }			// Fenster, Projekt, Datasource ok
inline bool IsValidActiveProject (void) { return m_pView ? m_pView -> IsValidProject() : false; }	// Fenster und Projekt ok
inline bool SetActViewContainer (ObjContainer &rOC) { return m_pView ? m_pView -> SetActViewContainer (rOC) : false; }
inline bool GetActViewContainer (ObjContainer &rOC) { return m_pView ? m_pView -> GetActViewContainer (rOC) : false; }
inline short ChangeVisInfoExt (HANDLEVISINFO *pHVI) { return m_pView ? m_pView -> ChangeVisInfoExt (pHVI) : false; }
inline bool SaveGeoDB (void) { return m_pView ? m_pView -> SaveGeoDB() : false; }

///////////////////////////////////////////////////////////////////////////////
// Interface zur Liste aller ORFenster des aktuellen Projektes
inline pWindow GetORWindow (HWND hWnd) { return m_pView ? m_pView -> GetORWindow(hWnd) : NULL; }
inline void SetExtend (ObjContainer &rOC) { if (m_pView) m_pView -> SetExtend (rOC); }
inline bool HandleDeleteObject (long lONr) { return m_pView ? m_pView -> HandleDeleteObject (lONr) : false; }
inline bool HandleModifyIdent (long lONr) { return m_pView ? m_pView -> HandleModifyIdent (lONr) : false; }
inline bool HandleCancelMode (bool fCmd) { return m_pView ? m_pView -> HandleCancelMode (fCmd) : false; }
inline HWND SetLastActive (HWND hWnd) { return m_pView ? m_pView -> SetLastActive (hWnd) : NULL; }
inline long GetSelectedObject (HWND hWnd = NULL) { return m_pView ? m_pView -> GetSelectedObject (hWnd) : 0L; }
inline HWND GetActiveORWindow (void) { return m_pView ? m_pView -> GetActiveORWindow() : NULL; }
inline HWND SetActiveORWindow (HWND hWnd) { return m_pView ? m_pView -> SetActiveORWindow(hWnd) : NULL; }
inline ULONG GetORCount (void) { return m_pView ? m_pView -> GetORCount() : 0L; }
inline ULONG GetORObjCount (void) { return m_pView ? m_pView -> GetORObjCount() : 0L; }
inline LONG GetAllSelectedObjects (LONG *plObjs) { return m_pView ? m_pView -> GetAllSelectedObjects (plObjs) : 0L; }
inline bool ChangeActiveColor (CHANGEACTIVECOLOR *pCAC) { return m_pView ? m_pView -> ChangeActiveColor (pCAC) : false; }
inline BOOL EnumSelectedObjects (BOOL (*pFcn)(long, BOOL, void *), void *pData, HWND hWnd = NULL) { return m_pView ? m_pView -> EnumSelectedObjects (pFcn, pData, hWnd) : false; }
inline BOOL EnumSelectedObjectsEx (BOOL (*pFcn)(long, DWORD, void *), void *pData, DWORD dwData, HWND hWnd = NULL) { return m_pView ? m_pView -> EnumSelectedObjectsEx (pFcn, pData, dwData, hWnd) : false; }
inline BOOL EnumAllObjects (BOOL (*fcn)(long, BOOL, void *), void *pData, HWND hWnd = NULL) { return m_pView ? m_pView -> EnumAllObjects (fcn, pData, hWnd) : false; }
inline BOOL EnumORWindows (ENUMNOKEYLONG *pK) { return m_pView ? m_pView -> EnumORWindows (pK) : false; }
inline bool ActivateAllObj (HWND hWnd = NULL) { return m_pView ? m_pView -> ActivateAllObj (hWnd) : false; }
inline void ReReadHeader (void) { if (m_pView) m_pView -> ReReadHeader(); }
inline bool HandleModifyFeature (long lONr, LPCSTR pcFeature) { return m_pView ? m_pView -> HandleModifyFeature(lONr, pcFeature) : false; }
inline void ShowORWindows (ShowState s) { if (m_pView) m_pView -> ShowORWindows(s); }
inline string CorrectCaption (ObjektInfo *pOIDlg, LPCSTR pcTemplate) { return m_pView ? m_pView -> CorrectCaption(pOIDlg, pcTemplate) : g_cbNil; }

inline long GetLastIdent (void) { return m_pView -> GetLastIdent(); }
inline void SetLastIdent (long lIdent) { m_pView -> SetLastIdent (lIdent); }
inline bool EnumProjects (ENUMNOKEY *pK) { return m_pView ? m_pView -> EnumProjects (pK) : false; }
inline HPROJECT GetProjectHandle (LPCSTR pcName) { return m_pView ? m_pView -> GetProjectHandle (pcName) : false; }
inline HPROJECT MakeProjectActive (HPROJECT hPr) { return m_pView ? m_pView -> MakeProjectActive (hPr) : false; }
inline void CloseAllORWindows (void) { if (m_pView) m_pView -> CloseAllORWindows(); }
inline void CloseORWindow (HWND hWnd) { if (m_pView) m_pView -> CloseORWindow (hWnd); }

inline bool myQueryClose (bool fCleanUp) { return m_pView ? m_pView -> myQueryClose(fCleanUp) : true; }
inline bool EditTextObject (pWindow pW, long lONr) { return m_pView ? m_pView -> EditTextObject (pW, lONr) : false; }

// Messagerouting 
inline LRESULT DispatchThroughXtensions (HWND hWnd, Event &e);		// Definiert in EXTQNFY.HXX

// Zugriff auf Member dieser Klasse
inline ExtensionList & EL (void) { return *m_pEL; }

///////////////////////////////////////////////////////////////////////////////
// Funktionsdeklarationen 
#include "extfcns.hxx"		// für MessageMap (DEX_...)
#include "extfcnsn.hxx"		// für MessageMap (DEXN_...)
};

///////////////////////////////////////////////////////////////////////////////
// vorgegebene FunktionsTabellen (compilergeneriert)
typedef LRESULT (ExtDirisWindow::*DEXMESSAGE_PROC)(HPROJECT, LPARAM);
typedef LPCSTR (ExtDirisWindow::*DEXMSGDUMP_PROC)(HPROJECT, LPARAM);

typedef struct tagDEXMESSAGE_ENTRY {
	UINT m_uiMsg;				// MessageID
	DEXMESSAGE_PROC m_pProc;	// zugehörige Funktion
#if defined(_DEBUG)
	LPCSTR m_pcMsgName;			// DEBUG only MessageName "DEX_..."
	DEXMSGDUMP_PROC m_pDumpProc;	// Funktion, welche Parameter dekodiert
	int m_iTraceLevel;			// ab diesem TraceLevel ausgeben
#endif
} DEXMESSAGE_ENTRY;

#if defined(_DEBUG)
// Struktur, die TraceInfos für eine Message enthält (zur Laufzeit generiert)
typedef struct tagDEXMSGDUMP_INFO {
	LPCSTR m_pcMsgName;			// DEBUG only MessageName "DEX_..."
	DEXMSGDUMP_PROC m_pDumpProc;	// Funktion, welche Parameter dekodiert
	int m_iTraceLevel;			// ab diesem TraceLevel ausgeben
} DEXMSGDUMP_INFO;
#endif // _DEBUG

extern "C" const DEXMESSAGE_ENTRY DexMessageEntries[];
#define DEXMESSAGE_ENTRYNUM sizeof(DexMessageEntries)/sizeof(DexMessageEntries[0])

///////////////////////////////////////////////////////////////////////////////
// NotifikationsVerteilerTabelle (compilergeneriert)
typedef LRESULT (ExtDirisWindow :: *DEXNOTIFY_PROC)(LPARAM);
typedef struct tagDEXNOTIFY_ENTRY {
	UINT m_uiMsg;				// MessageID
	DEXNOTIFY_PROC m_pProc;	// zugehörige Funktion
} DEXNOTIFY_ENTRY;

extern "C" const DEXNOTIFY_ENTRY DexMessageEntriesNfy[];
#define DEXMESSAGE_ENTRYNUM_NFY sizeof(DexMessageEntriesNfy)/sizeof(DexMessageEntriesNfy[0])

#endif // NOEXTDIRISWINDOW

///////////////////////////////////////////////////////////////////////////////
// Funktionen, die es unter Win32s nicht gibt ---------------------------------
inline LONG piInterlockedIncrement (LONG *pVal) 
{ 
#if defined(ENABLE_WIN32S_CODE)
	if (IsWin32s()) return ++(*pVal);
	else 
#endif 
		return InterlockedIncrement (pVal); 
}
inline LONG piInterlockedDecrement (LONG *pVal) 
{
#if defined(ENABLE_WIN32S_CODE)
	if (IsWin32s()) return --(*pVal);
	else
#endif // ENABLE_WIN32S_CODE
		return InterlockedDecrement (pVal); 
}

///////////////////////////////////////////////////////////////////////////////
// Funktionen, die bei !_DEBUG inline generiert werden
#if !defined(_DEBUG)
// Messages bearbeiten
inline 
LRESULT ExtDirisWindow::FullFillWill (HPROJECT hPr, WPARAM wParam, LPARAM lParam)
{
	if (m_cbDexProcs) {	// über Sprungverteiler abwickeln
	register UINT uiMsg = wParam-m_i1stDexProc;
	
		if (uiMsg >= 0 && uiMsg < m_iDexProcsNum)
			return (this ->* m_cbDexProcs[uiMsg])(hPr, lParam);
	}	

// alle, die nicht implementiert sind, piepsen
	return OnNotDefinedMessage (hPr, lParam);
}
#endif //!_DEBUG

///////////////////////////////////////////////////////////////////////////////
// globale nützliche Funktionen
LPSTR MakeCursorPath (LPCSTR pcCursor, LPSTR pcBuffer, int iLen = _MAX_PATH);

HRESULT GetRegObject (int iIndex, IEnumGUID *pIEnum, IRegisterTRiASExtension **ppIRegExt);
HRESULT UnGetRegObject (LPCSTR pcProgID, bool fFailIfNotThere, bool fGlobal, IRegisterTRiASExtension **ppIRegExt);

#define CursorPath(p) MakeCursorPath(p,(LPSTR)_alloca(_MAX_PATH))

///////////////////////////////////////////////////////////////////////////////
// Attribute lesen/schreiben/löschen
bool GetTextMerkmalLen (short iTTyp, HGENERIC lTarget, HFEATURE lMCode, int &riLen, LPCSTR pcView = NULL);
bool ReadTextMerkmal (short iTTyp, HGENERIC lTarget, HFEATURE lMCode, char *pText, int iLen, LPCSTR pcView = NULL);
bool WriteTextMerkmal (short iTTyp, HGENERIC lTarget, HFEATURE lMCode, const char *pText, int iFlags = 0, LPCSTR pcView = NULL);

#endif // !defined(_EXTMAIN3_HXX__A37D8267_4A3F_11d1_96DC_00A024D6F582__INCLUDED_)
