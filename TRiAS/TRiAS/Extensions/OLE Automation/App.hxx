// ApplicationObject ----------------------------------------------------------
// File: APP.HXX

#if !defined(_APP_HXX)
#define _APP_HXX

#pragma warning(disable:4355)

// #include "oleguid.h"
#include <intfy2.hxx>
#include "CPTriasNfy.h"
#include "TagMap.h"

class CDocTree;
class CGeoDoc;
class CAppConnectionPoint;

class CTriasApp : 
#if _ATL_VER >= 0x200
	public IDispatchImpl<_DApplication, &IID_DApplication, &LIBID_TRiAS, 
				TYPELIB_VERSION_MAJOR, TYPELIB_VERSION_MINOR>, 
	public ISupportErrorInfoImpl<&IID_DApplication>,
	public IConnectionPointContainerImpl<CTriasApp>,
	public CProxyINotificationSink2<CTriasApp>,
#else
	public CComDualImpl<_DApplication, &IID_DApplication, &LIBID_TRiAS, 
				TYPELIB_VERSION_MAJOR, TYPELIB_VERSION_MINOR>, 
	public CComISupportErrorInfoImpl<&IID_DApplication>,
	public CComConnectionPointContainerImpl,
#endif // _ATL_VER
	public CComObjectRoot
{
private:
	LPUNKNOWN m_pUnk;					// controlling unknown

	CDocTree *m_pDocTree;				// GeoDoc Tree
#if _ATL_VER < 0x200
	CProxyINotificationSink2 m_cp;
#endif // _ATL_VER

	bool m_fValid;						// Objekt ist fertig initialisiert

	CTagData m_mapTags;

protected:
	DWORD m_dwCookie;					// ConnectionID

	HRESULT FConnect (DWORD *pdwCookie);
	void FDisconnect (DWORD dwCookie);

// Connections registrieren und deregistrieren
	HRESULT FExternalConnect (IDispatch *pIDisp, DWORD *pdwCookie);
	HRESULT FExternalDisconnect (DWORD dwCookie);

// ... helper
	HRESULT CreateAndInitSink (ITriasXtensionSite *pISite, IDispatch *pIDispatch, DWORD *pdwCookie);
	HRESULT CreateAndInitDualSink (ITriasXtensionSite *pISite, DTRiASNotificationSink *pISink, DWORD *pdwCookie);

// Hauptfenster schieben, Größe verändern
	typedef enum {
		MOVESIZEACTION_LEFT = 0,
		MOVESIZEACTION_TOP = 1,
		MOVESIZEACTION_WIDTH = 2,
		MOVESIZEACTION_HEIGHT = 3,
		MOVESIZEACTION_GETLEFT = 4,
		MOVESIZEACTION_GETTOP = 5,
		MOVESIZEACTION_GETWIDTH = 6,
		MOVESIZEACTION_GETHEIGHT = 7,
	} MOVESIZEACTION;
	long MoveSize (MOVESIZEACTION iAction, long x = 0, long y = 0, long cx = 0, long cy = 0);

public:
		 CTriasApp (void);
		~CTriasApp (void);
		
static CTriasApp *CreateInstance (LPUNKNOWN pUnk);

	bool FInit (LPUNKNOWN pUnk);
	void Validate (void) { m_fValid = true; }
	void InvApp (void);

// ATL stuff
	BEGIN_COM_MAP(CTriasApp)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(DApplication)
		COM_INTERFACE_ENTRY(DTRiASBaseClass)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
#if _ATL_VER >= 0x200
		COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
#else
		COM_INTERFACE_ENTRY(IConnectionPointContainer)
#endif // _ATL_VER
	END_COM_MAP()

//	DECLARE_NOT_AGGREGATABLE(CTriasApp)

// unterstützte ConnectionPoints
	BEGIN_CONNECTION_POINT_MAP(CTriasApp)
#if _ATL_VER >= 0x200
		CONNECTION_POINT_ENTRY(IID_INotificationSink2)
#else
		CONNECTION_POINT_ENTRY(m_cp)
#endif // _ATL_VER
	END_CONNECTION_POINT_MAP()

// Verwalten der externen Locks
	ULONG InternalAddRef(void);
	ULONG InternalRelease(void);
	HRESULT FinalExternalConstruct (void);
	void FinalExternalRelease (void);
//	static CComGlobalsThreadModel::AutoCriticalSection m_cs;

///////////////////////////////////////////////////////////////////////////////
// Object Properties
	HRESULT GetObjectProperty (LPCSTR pcName, LONG lONr, IObjectProperty **ppIObjProp);
	HRESULT GetObjectPropertyIdent (LPCSTR pcName, LONG lIdent, IObjectProperty **ppIObjProp);
	HRESULT AddObjectProperty (LPCSTR pcName, DWORD dwFlags, LONG lONr, VARIANT vOptData, IObjectProperty **ppIObjProp);
	HRESULT AddObjectPropertyIdent (LPCSTR pcName, DWORD dwFlags, LONG lIdent, VARIANT vOptData, IObjectProperty **ppIObjProp);
	HRESULT RemoveObjectProperty (LPCSTR pcName, LONG lONr);

	HRESULT GetEnumObjProps (LONG lONr, IEnumObjProps **ppIEnum);
	HRESULT GetEnumObjPropsIdent (LONG lIdent, IEnumObjProps **ppIEnum);
	HRESULT GetObjProps	(REFIID riid, LPVOID *ppIObjProps);

// ... helper
	HRESULT CreateAndInitDualObjProp (DObjectProperty *pDObjProp, LONG *plCookie);
	HRESULT CreateAndInitDispatchObjProp (IDispatch *pIDispatch, LONG *plCookie);

///////////////////////////////////////////////////////////////////////////////
// _IApplication: ProgrammierInterface der TriasApp
// Properties
	STDMETHOD(get_isA)(LONG *plRTTI);
	STDMETHOD(get_Parent)(IDispatch **ppIDisp);
	STDMETHOD(get_Application)(IDispatch **ppIDisp);
	STDMETHOD(put_Parent)(THIS_ IDispatch *pIBase);
	STDMETHOD(put_Application)(THIS_ IDispatch *pIApp);

	STDMETHOD(get_Properties) (THIS_ _DTRiASProperties **ppIProps);
	STDMETHOD(CreateProperty) (THIS_ VARIANT vName, VARIANT vType, VARIANT vValue, _DTRiASProperty **ppIProp);

	STDMETHOD(get_Value)(THIS_ BSTR *pbstrValue);
	STDMETHOD(get_Name)(THIS_ BSTR *pbstrValue);
	STDMETHOD(get_StartupPath)(THIS_ BSTR *pbstrValue);
	STDMETHOD(get_DefaultFilePath)(THIS_ BSTR *pbstrValue);
	STDMETHOD(put_DefaultFilePath)(THIS_ BSTR bstrPath);
	STDMETHOD(get_FullName)(THIS_ BSTR *pbstrValue);

	STDMETHOD(get_Visible)(THIS_ VARIANT_BOOL *piVisible);
	STDMETHOD(put_Visible)(THIS_ VARIANT_BOOL iVisible);
    STDMETHOD(get_Interactive)(THIS_ VARIANT_BOOL *piInteractive);
    STDMETHOD(put_Interactive)(THIS_ VARIANT_BOOL iInteractive);

    STDMETHOD(get_Left)(THIS_ long *plLeft);
    STDMETHOD(put_Left)(THIS_ long lLeft);
    STDMETHOD(get_Top)(THIS_ long *plTop);
    STDMETHOD(put_Top)(THIS_ long lTop);
    STDMETHOD(get_Width)(THIS_ long *plWidth);
    STDMETHOD(put_Width)(THIS_ long lWidth);
    STDMETHOD(get_Height)(THIS_ long *plHeight);
    STDMETHOD(put_Height)(THIS_ long lHeight);

    STDMETHOD(get_StatusBar)(THIS_ BSTR *pbstrText);
    STDMETHOD(put_StatusBar)(THIS_ BSTR bstrText);
    STDMETHOD(get_Caption)(THIS_ BSTR *pbstrText);
    STDMETHOD(put_Caption)(THIS_ BSTR bstrText);

	STDMETHOD(get_Documents)(THIS_ DDocuments **ppIDocs);
	STDMETHOD(get_ActiveDocument)(THIS_ DDocument **ppIDocs);

	STDMETHOD(get_Version)(THIS_ BSTR *pbstrValue);
	STDMETHOD(get_VersionLong)(THIS_ long *plValue);
	STDMETHOD(get_ToolBars)(THIS_ DControlToolBars **ppIToolBars);

// Methods
	STDMETHOD(NewDocument)(THIS_ BSTR bstrName, VARIANT vUser, VARIANT vPassWd, VARIANT vMode, DDocument **ppIDoc);
	STDMETHOD(OpenDocument)(THIS_ BSTR bstrName, VARIANT vUser, VARIANT vPassWd, VARIANT vMode, DDocument **ppIDoc);

	STDMETHOD(GetDocument)(THIS_ VARIANT vProj, VARIANT vMode, DDocument **ppIDoc);
	STDMETHOD(Quit)(THIS_ VARIANT vCleanUp, int *piResult);
	STDMETHOD(Advise)(THIS_ IDispatch *pIDisp, long *plCookie);
	STDMETHOD(UnAdvise)(THIS_ long lCookie);

    STDMETHOD(AddObjectProperty)(THIS_ IDispatch *pIObjProp, long *plCookie);
    STDMETHOD(RemoveObjectProperty)(THIS_ long lCookie);

	STDMETHOD(GetToolBar)(THIS_ BSTR bstrName, DControlToolBar **pToolBar);
	STDMETHOD(AddToolBar)(THIS_ BSTR bstrName, VARIANT Style, DControlToolBar **ppToolBar);
	STDMETHOD(RemoveToolBar)(THIS_ BSTR bstrName);

	STDMETHOD(RunScript)(THIS_ BSTR bstrName);
	STDMETHOD(StopScript)(THIS_ BSTR bstrName);

	STDMETHOD(CreateInstance)(THIS_ BSTR bstrProgID, IDispatch **ppIDisp);

	STDMETHOD(LoadExtension)(THIS_ BSTR bstrProgID, VARIANT vMode, VARIANT vDispXtsn);
	STDMETHOD(UnloadExtension)(THIS_ BSTR bstrProgID);
	STDMETHOD(GetExtension)(THIS_ BSTR bstrProgID, IDispatch **pIDisp);

	STDMETHOD(get_Tag)(THIS_ BSTR bstrTagName, VARIANT *pvTagData);
	STDMETHOD(put_Tag)(THIS_ BSTR bstrTagName, VARIANT vTagData);

///////////////////////////////////////////////////////////////////////////////
// Notifications weiterleiten
	LRESULT OnServerEvent (SERVEREVT se);
	LRESULT OnProjectEvent (PROJECTEVT pe, HPROJECT hPr);
	LRESULT OnProjectClosedEvent (LPCSTR pName);
	LRESULT OnViewEvent (GEOVIEWEVT ve, LPCTSTR pView);
	LRESULT OnClassEvent (GEOCLASSEVT ce, ULONG ulIdent);
	LRESULT OnObjectEvent (GEOOBJECTEVT oe, LONG lONr);
	LRESULT OnFeatureEvent (GEOFEATUREEVT fe, ULONG ulMCode);
	LRESULT OnRelationEvent (GEORELATIONEVT re, ULONG ulRCode);
	LRESULT OnObjectWindowEvent (OBJWNDEVT oe, HWND hORWnd);
// nicht verwendet
//	LRESULT OnMenuInitEvent (HMENU hMenu, LPARAM lParam, HWND hWnd);
//	LRESULT OnMenuSelectEvent (UINT uiMenuID, HMENU hMenu, HWND hWnd);
//	LRESULT OnMenuCommandEvent (WPARAM wParam, HWND hWnd);

	LPCONNECTIONPOINT GetConnectionPoint (void);

///////////////////////////////////////////////////////////////////////////////
// Functions for  GeoDoc Tree 
	bool FAddDoc (CGeoDoc *pDoc) 
		{ return m_pDocTree ? m_pDocTree -> FAddItem (pDoc) : false; }
	HRESULT FGetDocDisp (LPCSTR pName, CGeoDoc **ppDoc = NULL, DDocument **ppIDoc = NULL, DOCMODE rgMode = DOCMODE_Get)
		{ return m_pDocTree ? m_pDocTree -> FAddItem (pName, ppDoc, ppIDoc, rgMode) : E_UNEXPECTED; }
	HRESULT FGetDocDispHandle (HPROJECT hPr, CGeoDoc **ppDoc = NULL, DDocument **ppIDoc = NULL, DOCMODE rgMode = DOCMODE_Get)
		{ return m_pDocTree ? m_pDocTree -> FAddItem (hPr, ppDoc, ppIDoc, rgMode) : E_UNEXPECTED; }

	CGeoDoc *FFindDoc (LPCSTR bName) 
		{ return m_pDocTree ? m_pDocTree -> FFindItem (bName) : NULL; }
	bool FDelDoc (LPCSTR bName) 
		{ return m_pDocTree ? m_pDocTree -> FDeleteItem (bName) : false; }
	bool FInvDoc (LPCSTR pName) 
		{ return m_pDocTree ? m_pDocTree -> FInvalidateItem (pName) : false; }
	bool SetDocName (LPCSTR bOldName, LPCSTR bNewName) 
		{ return m_pDocTree ? m_pDocTree -> SetDocName (bOldName, bNewName) : false; }
	HRESULT GetDispatchIF (IDispatch **ppIDisp)
		{ return ((_DApplication *)this)->QueryInterface (IID_IDispatch, (LPVOID *)ppIDisp); }

// Helper function
	CGeoDoc *FGetGeoDocument (HPROJECT hPr, _DDocument **pIDoc = NULL);
	CGeoDoc *FActGeoDocument (_DDocument **pIDoc = NULL)
		{ return FGetGeoDocument (NULL, pIDoc); }
	HRESULT GetDocMoniker (HPROJECT hPr, IMoniker **ppIMk);

	HRESULT OpenDocument (LPCSTR pcName, LPCSTR pcUser = NULL, 
		LPCSTR pcPassWd = NULL, int iMode = OM_Normal|OM_NoStandard, 
		DWORD dwMode = 0, DDocument **ppIDoc = NULL);

friend class CDocTree;
friend class CGeoDocs;
friend class CTriasAppPro;
};

///////////////////////////////////////////////////////////////////////////////
// sonstige allgemein zu verwendende Datentypen 

// Funktionen vom Typ INITCOLLECTIONPROC werden dazu verwendet, eine Collection
// entsprechend ihrem Typ zu füllen. Dieser FunktionsTyp ist unabhängig vom Typ
// der konkreten Collection.
typedef bool (PASCAL *INITCOLLECTIONPROC)(
	LPUNKNOWN pUnk, CTriasApp *pApp, container_wrappers::CCreator &rCollCr, 
	DWORD dwData = 0);

///////////////////////////////////////////////////////////////////////////////
// GeoDocument specific
typedef enum tagINITDOCSTATUS {
	INITDOCSTATUS_Error = 0,		// Error
	INITDOCSTATUS_Exists = 1,		// Doc already exists outside of this collection
	INITDOCSTATUS_Created = 2,		// Doc was newly created
} INITDOCSTATUS;

typedef INITDOCSTATUS (PASCAL *INITDOCCOLLECTIONPROC)(
	LPUNKNOWN pUnk, CTriasApp *pApp, container_wrappers::CCreator &rCollCr, 
	DWORD dwData = 0, string *pSingle = NULL);


///////////////////////////////////////////////////////////////////////////////
// GeoView specific
typedef enum tagINITVIEWSTATUS {
	INITVIEWSTATUS_Error = 0,		// Error
	INITVIEWSTATUS_Exists = 1,		// View already exists outside of this collection
	INITVIEWSTATUS_Created = 2,		// View was newly created
} INITVIEWSTATUS;

typedef INITVIEWSTATUS (PASCAL *INITVIEWCOLLECTIONPROC)(
	LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc, container_wrappers::CCreator &rCollCr, 
	DWORD dwData = 0, string *pSingle = NULL);

///////////////////////////////////////////////////////////////////////////////
// GeoClass specific
typedef enum tagINITCLSSTATUS {
	INITCLSSTATUS_Error = 0,		// Error
	INITCLSSTATUS_Exists = 1,		// Class already exists outside of this collection
	INITCLSSTATUS_Created = 2,		// Class was newly created
} INITCLSSTATUS;

typedef INITCLSSTATUS (PASCAL *INITCLASSCOLLECTIONPROC)(
	LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc, container_wrappers::CCreator &rCollCr, 
	DWORD dwData = 0, ULONG *pSingle = NULL);

///////////////////////////////////////////////////////////////////////////////
// GeoObject specific
typedef enum tagINITOBJSTATUS {
	INITOBJSTATUS_Error = 0,		// Error
	INITOBJSTATUS_Exists = 1,		// Object already exists outside of this collection
	INITOBJSTATUS_Created = 2,		// Object was newly created
} INITOBJSTATUS;

typedef INITOBJSTATUS (PASCAL *INITOBJCOLLECTIONPROC)(
	LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc, container_wrappers::CCreator &rCollCr, 
	DWORD dwData = 0, LONG *pSingle = NULL);

///////////////////////////////////////////////////////////////////////////////
// GeoFeature specific
typedef enum tagINITFEATSTATUS {
	INITFEATSTATUS_Error = 0,		// Error
	INITFEATSTATUS_Exists = 1,		// Feature already exists outside of this collection
	INITFEATSTATUS_Created = 2,		// Feature was newly created
} INITFEATSTATUS;

typedef INITFEATSTATUS (PASCAL *INITFEATCOLLECTIONPROC)(
	LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc, void *pViewClsObj,
	container_wrappers::CCreator &rCollCr, DWORD dwData = 0, string *pSingle = NULL, 
	DWORD dwFlags = PROPCAPS_NONE);

///////////////////////////////////////////////////////////////////////////////
// GeoObjectWin specific
typedef enum tagINITOBJWINSTATUS {
	INITOBJWINSTATUS_Error = 0,		// Error
	INITOBJWINSTATUS_Exists = 1,	// ObjWin already exists outside of this collection
	INITOBJWINSTATUS_Created = 2,	// ObjWin was newly created
} INITOBJWINSTATUS;

typedef INITOBJWINSTATUS (PASCAL *INITOBJWINCOLLECTIONPROC)(
	LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc, container_wrappers::CCreator &rCollCr, 
	DWORD dwData = 0, HWND *pSingle = NULL);

///////////////////////////////////////////////////////////////////////////////
// DELETECOLLECTIONPROC's 
typedef bool (PASCAL *DELETECOLLECTIONPROC)(LPCSTR bName, CGeoDoc *pDoc);
typedef bool (PASCAL *DELETEDOCCOLLECTIONPROC)(LPCSTR bName, CTriasApp *pApp);
typedef bool (PASCAL *DELETEVIEWCOLLECTIONPROC)(LPCSTR bName, CGeoDoc *pDoc);
typedef bool (PASCAL *DELETECLSCOLLECTIONPROC)(ULONG lIdent, CGeoDoc *pDoc, DWORD dwData);
typedef bool (PASCAL *DELETEOBJCOLLECTIONPROC)(LONG lONr, CGeoDoc *pDoc, DWORD dwData);
typedef bool (PASCAL *DELETEFEATCOLLECTIONPROC)(LPCSTR bName, void *pViewClsObj);
typedef bool (PASCAL *DELETEOBJWINCOLLECTIONPROC)(HWND hWnd, CGeoDoc *pDoc);

///////////////////////////////////////////////////////////////////////////////
// sonstige Helper
HRESULT RegisterAsRunning (DWORD grfFlags, IUnknown *pIUnk, IMoniker *pIMk, DWORD *pdwRegROT);
HRESULT RevokeAsRunning (DWORD *pdwRegROT);
HRESULT NoteChangeTime (DWORD dwRegROT, FILETIME *pft);

///////////////////////////////////////////////////////////////////////////////
// Wrapper um Notifikationen zeitweise auszuschalten
class CNotifyWrapper
{
public:
	CNotifyWrapper()
	{
//		DEX_NotificationMode (TRUE);
	}
	~CNotifyWrapper()
	{
//		DEX_NotificationMode (FALSE);
	}
};

#endif // _APP_HXX

