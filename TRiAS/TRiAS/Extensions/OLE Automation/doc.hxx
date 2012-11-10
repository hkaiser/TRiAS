// Ein geöffnetes Dokumente (Controlling Unknown) -----------------------------
// File: DOC.HXX

#if !defined(_DOC_HXX)
#define _DOC_HXX

#include "TagMap.h"

///////////////////////////////////////////////////////////////////////////////
// forward declarations
class CTriasApp;

class CGeoView;
class CClass;
class CGeoObject;
class CViewTree;
class CClsTrees;
class CObjTrees;

EXTERN_C const CLSID CLSID_GeoDocumentIntern;

///////////////////////////////////////////////////////////////////////////////
// hier benötigte SmartInterfaces
DefineSmartInterface(Moniker);
DefineSmartInterface(OleClientSite);		// #AD19991108
DefineSmartInterface(OleAdviseHolder);		// #AD19991108
DefineSmartInterface(DataObject);			// #AD20000210
DefineSmartInterface(DataAdviseHolder);		// #AD20000308

///////////////////////////////////////////////////////////////////////////////
// ein TRiAS Projekt
class CGeoDoc : 
	public CComDualImpl<_DDocument, &IID_DDocument, &LIBID_TRiAS, 
				TYPELIB_VERSION_MAJOR, TYPELIB_VERSION_MINOR>, 
	public CComISupportErrorInfoImpl<&IID_DDocument>,
	public IPersistFile,
	public IPersistStorage,
	public IDataObject,			// #AD000125
	public IOleObject,			// #AD991027
	public IOleItemContainer,
	public IManageDocumentContext,
	public CComObjectRoot,
	public CComCoClass<CGeoDoc, &CLSID_GeoDocumentIntern>		// #AD000306
{
	D_CLASS(CGeoDoc);
	DECLARE_GET_CONTROLLING_UNKNOWN();

private:
	LPUNKNOWN m_pUnk;			// controlling unknown
	CTriasApp *m_pApp;			// Trias.Application

	CViewTree *m_pViewTree;		// GeoView Tree
	CClsTrees *m_pClsTrees;		// GeoClasses Trees
	CObjTrees *m_pObjTrees;		// GeoObjects Trees
 	CObjWinTree *m_pObjWinTree;	// GeoObjectWin Tree

	char *m_pBuffer;
	char *m_pName;				// ProjectName
	HPROJECT m_hPr;				// Project Handle
	HPROJECT m_hPrCtx;			// aktuelle Kontext-Datenquelle

	unsigned int m_fValid : 1;	// CGeoDoc is valid
	unsigned int m_fIsDragSource : 1;	// dieses CGeoDoc ist DatenQuelle

	CTagData m_mapTags;

	void Invalidate (void) { m_fValid = false; }
		
protected:
// Connections registrieren und deregistrieren
	DWORD m_dwCookie;			// ConnectionID

	HRESULT FConnect (DWORD *pdwCookie);
	void FDisconnect (DWORD dwCookie);

// Linking support
	WMoniker m_FileMK;
	DWORD m_dwRegROT;			// file moniker
	DWORD m_dwRegROTAll;		// wildcard moniker

	WDataObject	m_DataObject;
	WOleClientSite m_ClientSite;     // for embedded item
	WOleAdviseHolder m_AdviseHolder;
	WDataAdviseHolder m_DataAdviseHolder;
	CDocObjectServer* m_pDocObjectServer;	// if DocObject, ptr to doc site
	CString m_strHostObj;					// name of document in container
	CString m_strHost;						// name of container
	CSize	m_SizeExtContent;
	CSize	m_SizeExtThumbnail;
	CSize	m_SizeExtIcon;
	CSize	m_SizeExtPrint;
	DWORD	m_dwLastAskedAspect;
	COleDataSource* GetDataSource()	{ return &m_dataSource; }

	virtual void OnSetHostNames(LPCTSTR lpszHost, LPCTSTR lpszHostObj);

public:
		CGeoDoc (void);
		~CGeoDoc (void);
		
static HRESULT CreateInstance (
		LPUNKNOWN pUnk, CTriasApp *pApp, LPCSTR bName, CGeoDoc **ppDoc, 
		DOCMODE rgMode = DOCMODE_Get);

	HRESULT FInit (LPUNKNOWN pUnk, CTriasApp *pApp, DOCMODE rgMode, LPCSTR bName);
	bool FInitInternal (LPCSTR bName);

// ATL stuff
	BEGIN_COM_MAP(CGeoDoc)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(DDocument)
		COM_INTERFACE_ENTRY(DTRiASBaseClass)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY(IPersistFile)
		COM_INTERFACE_ENTRY(IPersistStorage)
		COM_INTERFACE_ENTRY(IDataObject)		// #AD000125
		COM_INTERFACE_ENTRY(IOleObject)			// #AD991027
		COM_INTERFACE_ENTRY2(IPersist, IPersistFile)
		COM_INTERFACE_ENTRY(IOleItemContainer)
		COM_INTERFACE_ENTRY(IOleContainer)
		COM_INTERFACE_ENTRY(IParseDisplayName)
		COM_INTERFACE_ENTRY(IManageDocumentContext)
	END_COM_MAP()

	DECLARE_AGGREGATABLE(CGeoDoc)
	static HRESULT WINAPI UpdateRegistry(BOOL bRegister);

///////////////////////////////////////////////////////////////////////////////
// Verwalten der externen Locks
	ULONG InternalAddRef(void);
	ULONG InternalRelease(void);
	HRESULT FinalExternalConstruct (void);
	void FinalExternalRelease (void);
//	static CComGlobalsThreadModel::AutoCriticalSection m_cs;

///////////////////////////////////////////////////////////////////////////////
// *** _IDocument methods
	STDMETHOD(get_isA)(LONG *plRTTI);
   	STDMETHOD(get_Parent)(IDispatch **ppIDisp);
    STDMETHOD(get_Application)(IDispatch **ppIDisp);
	STDMETHOD(put_Parent)(THIS_ IDispatch * pIBase);
	STDMETHOD(put_Application)(THIS_ IDispatch * pIApp);
    	
	STDMETHOD(get_Properties) (THIS_ _DTRiASProperties **ppIProps);
	STDMETHOD(CreateProperty) (THIS_ VARIANT vName, VARIANT vType, VARIANT vValue, _DTRiASProperty **ppIProp);

    STDMETHOD(get_Value)(THIS_ BSTR *pbstrValue);
   	STDMETHOD(get_Name)(THIS_ BSTR *pbstrValue);
   	STDMETHOD(get_Path)(THIS_ BSTR *pbstrPath);
    STDMETHOD(get_FullName)(THIS_ BSTR *pbstrValue);
	STDMETHOD(get_ActiveViewName)(THIS_ BSTR *pbstrView);
	STDMETHOD(put_ActiveViewName)(THIS_ BSTR bstrView);
    	
	STDMETHOD(get_ObjectCount)(long *plCnt);
	STDMETHOD(get_ViewCount)(long *plCnt);
	STDMETHOD(get_ClassCount)(long *plCnt);

	STDMETHOD(get_Author)(THIS_ BSTR *pbstrValue);
	STDMETHOD(put_Author)(THIS_ BSTR bstrValue);
	STDMETHOD(get_Comments)(THIS_ BSTR *pbstrValue);
	STDMETHOD(put_Comments)(THIS_ BSTR bstrValue);
	STDMETHOD(get_Keywords)(THIS_ BSTR *pbstrValue);
	STDMETHOD(put_Keywords)(THIS_ BSTR bstrValue);
	STDMETHOD(get_Subject)(THIS_ BSTR *pbstrValue);
	STDMETHOD(put_Subject)(THIS_ BSTR bstrValue);
	STDMETHOD(get_Title)(THIS_ BSTR *pbstrValue);
	STDMETHOD(put_Title)(THIS_ BSTR bstrValue);
	STDMETHOD(get_Saved)(THIS_ VARIANT_BOOL *pfSaved);
	STDMETHOD(get_ReadOnly)(THIS_ VARIANT_BOOL *pfReadOnly);

    STDMETHOD(CloseIt)(THIS_ VARIANT vtSave, VARIANT vtFName);
    STDMETHOD(Save)(THIS);
    STDMETHOD(SaveAs)(THIS_ BSTR bstrName);
	STDMETHOD(RevertToSaved)(THIS);

   	STDMETHOD(GetHeaderEntry)(THIS_ BSTR bstrHeaderKey, BSTR *pbstrText);
    STDMETHOD(SetHeaderEntry)(THIS_ BSTR bstrHeaderKey, VARIANT vText);
   	STDMETHOD(GetHeaderEntry2)(THIS_ BSTR bstrHeaderKey, HEADERFLAG *prgFlags, BSTR *pbstrText);
    STDMETHOD(SetHeaderEntry2)(THIS_ BSTR bstrHeaderKey, VARIANT vText, VARIANT vFlags);
   	STDMETHOD(GetHeaderEntryEx)(THIS_ BSTR bstrDataSource, BSTR bstrHeaderKey, BSTR *pbstrText);
    STDMETHOD(SetHeaderEntryEx)(THIS_ BSTR bstrDataSource, BSTR bstrHeaderKey, VARIANT vText);
   	STDMETHOD(GetHeaderEntryEx2)(THIS_ BSTR bstrDataSource, BSTR bstrHeaderKey, HEADERFLAG *prgFlags, BSTR *pbstrText);
    STDMETHOD(SetHeaderEntryEx2)(THIS_ BSTR bstrDataSource, BSTR bstrHeaderKey, VARIANT vText, VARIANT vFlags);

	STDMETHOD(RePaint)(THIS_ VARIANT vXMin, VARIANT vYMin, VARIANT vXMax, VARIANT vYMax);
	STDMETHOD(ReBuild)(THIS_ VARIANT vFull);

    STDMETHOD(GetViews)(THIS_ DViews **ppIViews);
    STDMETHOD(GetView)(THIS_ BSTR bstrViewName, VARIANT vMode, DView **pIView);
    	
    STDMETHOD(GetClasses)(THIS_ VARIANT vClss, VARIANT vLogMode, DGeoClasses **ppIClss);
	STDMETHOD(GetClass)(THIS_ VARIANT vCls, VARIANT vMode, DGeoClass **ppICls);
	STDMETHOD(AddClass)(THIS_ VARIANT vCls, VARIANT vDataSrc, DGeoClass **ppICls);
	STDMETHOD(GetClassEx)(THIS_ VARIANT vCls, VARIANT vDataSrc, VARIANT vMode, DGeoClass **ppICls);

    STDMETHOD(GetObjects)(THIS_ VARIANT vObjs, VARIANT vLogMode, DGeoObjects **ppIObjs);
    STDMETHOD(QueryObjects)(THIS_ VARIANT vFeature, VARIANT vToSearch, VARIANT vMode, DGeoObjects **ppIObjs);
    STDMETHOD(GetObject)(THIS_ VARIANT vObj, VARIANT vMode, DGeoObject **ppIObj);
	STDMETHOD(AddObject)(THIS_ VARIANT vObj, VARIANT vClass, DGeoObject **ppIObj);

    STDMETHOD(GetGeoObjectWins)(THIS_ VARIANT vObjWins, VARIANT vLogMode, DGeoObjectWins **ppIWins);
	STDMETHOD(GetGeoObjectWin)(THIS_ VARIANT vWnd, VARIANT vMode, DGeoObjectWin **ppIWin);

    STDMETHOD(CreateGeoObjectsCollection)(THIS_ DGeoObjects **ppIObjs);

	STDMETHOD(get_RefScale)(THIS_ long *plRefScale);
	STDMETHOD(put_RefScale)(THIS_ long lRefScale);

	STDMETHOD(GetViewRect)(THIS_ double *pdX, double *pdY, VARIANT *pvX, VARIANT *pvY);
	STDMETHOD(SetViewRect)(THIS_ double dX1, double dY1, VARIANT vX2, VARIANT vY2);

	STDMETHOD(get_IsDirty)(THIS_ VARIANT_BOOL *pbstrValue);
	STDMETHOD(put_IsDirty)(THIS_ VARIANT_BOOL bstrValue);

	STDMETHOD(get_PreventRepaint)(THIS_ VARIANT_BOOL *pbstrValue);
	STDMETHOD(put_PreventRepaint)(THIS_ VARIANT_BOOL bstrValue);

	STDMETHOD(get_Connections)(THIS_ ITRiASConnections **ppIConns);
	STDMETHOD(Render)(long lLeft, long lBottom, long lRight, long lTop,
		VARIANT vLeftDb, VARIANT vBottomDb, VARIANT vRightDb, VARIANT vTopDb,
		VARIANT vDriver, VARIANT vDevice, VARIANT vPort, IDispatch **ppIPictDisp);

	STDMETHOD(get_Tag)(THIS_ BSTR bstrTagName, VARIANT *pvTagData);
	STDMETHOD(put_Tag)(THIS_ BSTR bstrTagName, VARIANT vTagData);

///////////////////////////////////////////////////////////////////////////////
// IPersist methods
	STDMETHOD(GetClassID)(THIS_ CLSID *pClsID);

///////////////////////////////////////////////////////////////////////////////
// IPersistFile methods
	STDMETHOD(IsDirty)(THIS);
	STDMETHOD(Load)(THIS_ LPCOLESTR pszFileName, DWORD dwMode);
	STDMETHOD(Save)(THIS_ LPCOLESTR pszFileName, BOOL fRemember);
	STDMETHOD(SaveCompleted)(THIS_ LPCOLESTR pszFileName);
	STDMETHOD(GetCurFile)(THIS_ LPOLESTR *ppszFileName);

///////////////////////////////////////////////////////////////////////////////
// IPersistStorage methods
//	STDMETHOD(IsDirty)(THIS);
	STDMETHOD(InitNew)(THIS_ IStorage *pIStg);
	STDMETHOD(Load)(THIS_ IStorage *pIStg);
	STDMETHOD(Save)(THIS_ IStorage *pIStg, BOOL fSameAsLoad);
	STDMETHOD(SaveCompleted)(THIS_ IStorage *pIStg);
	STDMETHOD(HandsOffStorage)(THIS);

///////////////////////////////////////////////////////////////////////////////
// IDataObject methods
	STDMETHOD(GetData)(THIS_ LPFORMATETC pFE, LPSTGMEDIUM pSTM);
	STDMETHOD(GetDataHere)(THIS_ LPFORMATETC pFE, LPSTGMEDIUM pSTM);
	STDMETHOD(QueryGetData)(THIS_ FORMATETC *pformatetc);
	STDMETHOD(GetCanonicalFormatEtc)(THIS_ FORMATETC *pformatectIn, FORMATETC *pformatetcOut);
	STDMETHOD(SetData)(THIS_ FORMATETC *pformatetc, STGMEDIUM *pmedium, BOOL fRelease);
	STDMETHOD(EnumFormatEtc)(THIS_ DWORD dwDirection, IEnumFORMATETC **ppenumFormatEtc);
	STDMETHOD(DAdvise)(THIS_ FORMATETC *pformatetc, DWORD advf, IAdviseSink *pAdvSink, DWORD *pdwConnection);
	STDMETHOD(DUnadvise)(THIS_ DWORD dwConnection);
	STDMETHOD(EnumDAdvise)(THIS_ IEnumSTATDATA **ppenumAdvise);

// Helper methods
public:
	bool m_bWait4StopPaint;
	bool m_bPaintStarted;
	void RegisterStartPaint();
	void RegisterStopPaint();

protected:
	HRESULT	CreateDataObject();
	BOOL	GetMetafileData(LPFORMATETC pFE, LPSTGMEDIUM pSTM);

public:
// see COleDataSource for a description of these overridables
	virtual BOOL OnRenderGlobalData(LPFORMATETC lpFormatEtc, HGLOBAL* phGlobal);
	virtual BOOL OnRenderFileData(LPFORMATETC lpFormatEtc, CFile* pFile);
	virtual BOOL OnRenderData(LPFORMATETC lpFormatEtc, LPSTGMEDIUM lpStgMedium);
	virtual BOOL OnSetData(LPFORMATETC lpFormatEtc, LPSTGMEDIUM lpStgMedium, BOOL bRelease);
		// HGLOBAL version will be called first, then CFile* version

	// CItemDataSource implements OnRender reflections to COleServerItem
	class CItemDataSource : public COleDataSource
	{
		D_CLASS(CGeoDoc::CItemDataSource);

	protected:
	// the GetData and SetData interfaces forward to m_pItem
		virtual BOOL OnRenderGlobalData(LPFORMATETC lpFormatEtc, HGLOBAL* phGlobal);
		virtual BOOL OnRenderFileData(LPFORMATETC lpFormatEtc, CFile* pFile);
		virtual BOOL OnRenderData(LPFORMATETC lpFormatEtc, LPSTGMEDIUM lpStgMedium);
			// HGLOBAL version will be called first, then CFile* version

		virtual BOOL OnSetData(LPFORMATETC lpFormatEtc, LPSTGMEDIUM lpStgMedium, BOOL bRelease);
	};
	CItemDataSource m_dataSource;

///////////////////////////////////////////////////////////////////////////////
// IOleObject methods
	STDMETHOD(SetClientSite)(THIS_ LPOLECLIENTSITE pIOleClientSite);
	STDMETHOD(GetClientSite)(THIS_ LPOLECLIENTSITE *ppSite);
	STDMETHOD(SetHostNames)(THIS_ LPCOLESTR pszApp, LPCOLESTR pszObj);
	STDMETHOD(Close)(THIS_ DWORD dwSaveOption);
	STDMETHOD(SetMoniker)(THIS_ DWORD dwWhich, LPMONIKER pmk);
	STDMETHOD(GetMoniker)(THIS_ DWORD dwAssign, DWORD dwWhich, LPMONIKER *ppmk);
	STDMETHOD(InitFromData)(THIS_ LPDATAOBJECT pIDataObject, BOOL fCreation, DWORD dwReserved);
	STDMETHOD(GetClipboardData)(THIS_ DWORD dwReserved, LPDATAOBJECT *ppIDataObj);
	STDMETHOD(DoVerb)(THIS_ LONG iVerb, LPMSG pMSG, LPOLECLIENTSITE pActiveSite, LONG lIndex, HWND hWndParent, LPCRECT pRectPos);
	STDMETHOD(EnumVerbs)(THIS_ LPENUMOLEVERB *ppEnum);
	STDMETHOD(Update)(THIS_ void);
	STDMETHOD(IsUpToDate)(THIS_ void);
	STDMETHOD(GetUserClassID)(THIS_ LPCLSID pClsID);
	STDMETHOD(GetUserType)(THIS_ DWORD dwForm, LPOLESTR *ppszType);
	STDMETHOD(SetExtent)(THIS_ DWORD dwAspect, LPSIZEL pszl);
	STDMETHOD(GetExtent)(THIS_ DWORD dwAspect, LPSIZEL pszl);
	STDMETHOD(Advise)(THIS_ LPADVISESINK pIAdviseSink, LPDWORD pdwConn);
	STDMETHOD(Unadvise)(THIS_ DWORD dwConn);
	STDMETHOD(EnumAdvise)(THIS_ LPENUMSTATDATA *ppEnum);
	STDMETHOD(GetMiscStatus)(THIS_ DWORD dwAspect, LPDWORD pdwStatus);
	STDMETHOD(SetColorScheme)(THIS_ LPLOGPALETTE pLP);

///////////////////////////////////////////////////////////////////////////////
// IParseDisplayName methods
	STDMETHOD(ParseDisplayName)(THIS_ IBindCtx *pbc, LPOLESTR pszDisplayName, ULONG *pchEaten, IMoniker **ppmkOut);

// IOleContainer methods
	STDMETHOD(EnumObjects)(THIS_ DWORD grfFlags, IEnumUnknown **ppenum);
	STDMETHOD(LockContainer)(THIS_ BOOL fLock);

// IOleItemContainer methods
	STDMETHOD(GetObject)(THIS_ LPOLESTR pszItem, DWORD dwSpeedNeeded, IBindCtx *pbc, REFIID riid, void **ppvObject);
	STDMETHOD(GetObjectStorage)(THIS_ LPOLESTR pszItem, IBindCtx *pbc, REFIID riid, void **ppvStorage);
	STDMETHOD(IsRunning)(THIS_ LPOLESTR pszItem);

	HRESULT GetRunning (LPOLESTR pszItem, DWORD dwSpeedNeeded, IBindCtx *pbc, REFIID riid, LPVOID *ppvObject, bool fTestRunningOnly);
	HRESULT GetGeoClass (LPCTSTR pcItem, DWORD dwSpeedNeeded, IBindCtx *pbc, REFIID riid, LPVOID *ppvObj, bool fTestRunningOnly);
	HRESULT GetGeoView (LPCTSTR pcItem, DWORD dwSpeedNeeded, IBindCtx *pbc, REFIID riid, LPVOID *ppvObj, bool fTestRunningOnly);
	HRESULT GetGeoObject (LPCTSTR pcItem, DWORD dwSpeedNeeded, IBindCtx *pbc, REFIID riid, LPVOID *ppvObj, bool fTestRunningOnly);
	HRESULT GetGeoObjects10 (LPCTSTR pcItem, DWORD dwSpeedNeeded, IBindCtx *pbc, REFIID riid, LPVOID *ppvObj, bool fTestRunningOnly);
	HRESULT GetGeoObjects36 (LPCTSTR pcItem, DWORD dwSpeedNeeded, IBindCtx *pbc, REFIID riid, LPVOID *ppvObj, bool fTestRunningOnly);
	HRESULT GetFromProject (LPCTSTR pcItem, DWORD dwSpeedNeeded, IBindCtx *pbc, REFIID riid, LPVOID *ppvObj, bool fTestRunningOnly);

	HRESULT ParseFromProject (IBindCtx *pbc, LPOLESTR pszDisplayName, ULONG *pchEaten, IMoniker **ppmkOut);
	HRESULT NoParseDisplayName (IBindCtx *pbc, LPOLESTR pszDisplayName,	ULONG *pchEaten, IMoniker **ppmkOut);

// IManageDocumentContext
	STDMETHOD(GetCtxHandle)(THIS_ INT_PTR *pCtx)
	{
		if (NULL == pCtx) return E_POINTER;

		*pCtx = reinterpret_cast<INT_PTR>(GetCtxDataSource());
		return S_OK;
	}
	STDMETHOD(SetCtxHandle)(THIS_ INT_PTR Ctx)
	{
		SetCtxDataSource (reinterpret_cast<HPROJECT>(Ctx));
		return S_OK;
	}
	 
///////////////////////////////////////////////////////////////////////////////
// Drag'n Drop
	HRESULT GetMoniker (IMoniker **ppIMk);

	bool FQueryPasteFromData (IDataObject *pIDataObject);
	bool FPasteFromData (IDataObject *pIDataObject, HPROJECT hPr, BOOL fShowORWindow = FALSE);
	UINT TestDroppablePoint (POINTL *pPt);

	bool IsDocSource (void) { return ((OLE2AutoExtension *)g_pTE)->IsDocSource(m_hPr); }

friend HRESULT CreateItemMonikerFromEnumLONG (IEnumLONG *pEnum, IMoniker **ppIMk);

	HRESULT FPasteGeoClass (_DDocument *pIDocX, _DView *pIViewX, _DGeoClass *pIClsX, HPROJECT hPr, BOOL fShowORWindow);
	HRESULT FPasteGeoObjects (_DDocument *pIDocX, _DView *pIViewX, _DGeoObjects *pIObjsX, HPROJECT hPr, BOOL fShowORWindow);
	HRESULT FPasteGeoObject (_DDocument *pIDocX, _DView *pIViewX, _DGeoObject *pIObjX, HPROJECT hPr, BOOL fShowORWindow);

///////////////////////////////////////////////////////////////////////////////
// sonstige Funktionen
	HPROJECT GetProjectHandle (void);

inline const char *GetValue (void) const { return m_pName;}

	char *GetName (bool fForce = false);	// fForce == true --> internal use only !!
	HRESULT SetName (const char *pName, bool fIgnoreValid = false);
	HRESULT SetName (LPCOLESTR pcoleName, bool fIgnoreValid = false)
		{ return SetName(AnsiString(pcoleName), fIgnoreValid); }

	bool Remove (void);					// remove physically
	bool CloseIt (void);

inline void Validate (void) { m_fValid = true; }
inline bool IsValid (void) { return m_fValid ? true : false; }

///////////////////////////////////////////////////////////////////////////////
// Hilfsfunktionen für OLE
	void OnOpen();			// Open embedded
	void OnShow();			// Zeige Server-Window
	void OnHide();			// Verbirg Server-Window
	void OnDataChanged();	// Nachricht an Client: Daten holen!

// for the tree's
	LPCSTR FGetBSTR (void);				// liefert SuchSchlüssel
friend int FCmpBSTR (LPCSTR, LPCSTR);	// vergleicht 2 Schlüssel

// Functions for  Views Tree -----------------------------------------------------
	CGeoView *FGetViewDisp (LPCSTR bName, DView **ppIView = NULL, VIEWMODE rgMode = VIEWMODE_Get)
		{ return m_pViewTree ? m_pViewTree -> FAddItem (bName, ppIView, rgMode) : NULL; }

	bool FDelView (LPCSTR bName) 
		{ return m_pViewTree ? m_pViewTree -> FDeleteItem (bName) : false; }
	bool FInvView (LPCSTR pName) 
		{ return m_pViewTree ? m_pViewTree -> FInvalidateItem (pName) : false; }

	bool SetViewName (LPCSTR bOldName, LPCSTR bNewName) 
		{ return m_pViewTree ? m_pViewTree -> SetViewName (bOldName, bNewName) : false; }

	HRESULT FGetGeoView (LPCSTR pcView, bool fCreate, DView **ppIView);
		
// Functions for  GeoClasses Trees -----------------------------------------------------
	CClass *FGetClassDisp (ULONG lIdent, DGeoClass **ppICls = NULL, GEOCLASSMODE rgMode = GEOCLASSMODE_Get, LPCSTR pcSrc = NULL)
		{ return m_pClsTrees ? m_pClsTrees -> FAddItem (lIdent, ppICls, rgMode, pcSrc) : NULL; }
	CClass *FGetClassDisp (LPCSTR bName, DGeoClass **ppICls, GEOCLASSMODE rgMode = GEOCLASSMODE_Get, LPCSTR pcSrc = NULL)
		{ return m_pClsTrees ? m_pClsTrees -> FAddItem (bName, ppICls, rgMode, pcSrc) : NULL; }
	bool FDelClass (ULONG lIdent) 
		{ return m_pClsTrees ? m_pClsTrees -> FDeleteItem (lIdent) : false; }
	bool FDelClass (LPCSTR bName, LPCSTR pcSrc = NULL) 
		{ return m_pClsTrees ? m_pClsTrees -> FDeleteItem (bName, pcSrc) : false; }
	bool FInvClass (ULONG lIdent) 
		{ return m_pClsTrees ? m_pClsTrees -> FInvalidateItem (lIdent) : false; }
	bool SetClassName (ULONG lIdent, LPCSTR bNewName) 
		{ return m_pClsTrees ? m_pClsTrees -> SetClassName (lIdent, bNewName) : false; }
	ULONG GetIdentFromClsName (LPCSTR bName, LPCSTR pcSrc = NULL) 
		{ return m_pClsTrees ? m_pClsTrees -> GetIdentFromClsName (bName, pcSrc) : INVALID_IDENT; }	

// Functions for  GeoObjects Trees -----------------------------------------------------
	CGeoObject *FGetObjectDisp (LONG lONr, DGeoObject **ppIObj = NULL, GEOOBJECTMODE rgMode = GEOOBJECTMODE_Get, VARIANT *pvClass = NULL)
		{ return m_pObjTrees ? m_pObjTrees -> FAddItem (lONr, ppIObj, rgMode, pvClass) : NULL; }
	CGeoObject *FGetObjectDisp (BSTR bName, DGeoObject **ppIObj = NULL, GEOOBJECTMODE rgMode = GEOOBJECTMODE_Get, VARIANT *pvClass = NULL)
		{ return m_pObjTrees ? m_pObjTrees -> FAddItem (bName, ppIObj, rgMode, pvClass) : NULL; }
	bool FDelObject (LONG lONr) 
		{ return m_pObjTrees ? m_pObjTrees -> FDeleteItem (lONr) : false; }
	bool FDelObject (LPCSTR bName) 
		{ return m_pObjTrees ? m_pObjTrees -> FDeleteItem (bName) : false; }
	bool FInvObject (LONG lONr) 
		{ return m_pObjTrees ? m_pObjTrees -> FInvalidateItem (lONr) : false; }
	ULONG ChangeObjectIdent (LONG lONr, ULONG lNewIdent)
		{ return m_pObjTrees ? m_pObjTrees -> ChangeObjectIdent (lONr, lNewIdent) : INVALID_IDENT; }
	bool SetObjectName (LONG lONr, LPCSTR bNewName) 
		{ return m_pObjTrees ? m_pObjTrees -> SetObjectName (lONr, bNewName) : false; }
	LONG GetONrFromObjName (LPCSTR bName) 
		{ return m_pObjTrees ? m_pObjTrees -> GetONrFromObjName (bName) : INVALID_ONR; }
	ULONG ObjectClassified (INT_PTR lONr) { return m_pObjTrees ? m_pObjTrees -> ChangeObjectIdent(lONr, 0L, true) : INVALID_IDENT; }

	HRESULT FGetGeoObject (LONG lONr, DGeoObject **ppIObj);

// Functions for  GeoObjWin Tree -----------------------------------------------------
	CGeoObjectWin *FGetObjWinDisp (HWND hWnd, DGeoObjectWin **ppIWin = NULL, GEOOBJWINMODE rgMode = GEOOBJWINMODE_Get)
		{ return m_pObjWinTree ? m_pObjWinTree -> FAddItem (hWnd, ppIWin, rgMode) : NULL; }
	CGeoObjectWin *FGetObjWinDisp (LPCSTR bName, DGeoObjectWin **ppIWin = NULL, GEOOBJWINMODE rgMode = GEOOBJWINMODE_Get)
		{ return m_pObjWinTree ? m_pObjWinTree -> FAddItem (bName, ppIWin, rgMode) : NULL; }
	bool FDelObjWin (HWND hWnd) 
		{ return m_pObjWinTree ? m_pObjWinTree -> FDeleteItem (hWnd) : false; }
	bool FInvObjWin (HWND hWnd) 
		{ return m_pObjWinTree ? m_pObjWinTree -> FInvalidateItem (hWnd) : false; }
	bool SetObjWinName (HWND hWnd, LPCSTR bNewName) 
		{ return m_pObjWinTree ? m_pObjWinTree -> SetObjWinName (hWnd, bNewName) : false; }
	HWND GethWndFromObjWinName (LPCSTR bName) 
		{ return m_pObjWinTree ? m_pObjWinTree -> GethWndFromObjWinName (bName) : INVALID_HWND; }	

	HRESULT FGetGeoObjectWin (HWND hWnd, DGeoObjectWin **ppIWin);

// Kontext-Datenquelle verwalten
	void SetCtxDataSource (HPROJECT hPrCtx) { m_hPrCtx = hPrCtx; }
	HPROJECT GetCtxDataSource() { return m_hPrCtx; }

// End of Doc--<Trees Functions -----------------------------------------------------------------
	char *ProjectName (void);

	void RePaint (long iXMin = -1, long iYMin = -1, long iXMax = -1, long iYMax = -1);
	void ReBuildMethod (bool fFull);

	void InvDoc (void);
	HRESULT Rename (LPCSTR bName);
	HRESULT RenamingFile (void);
	HRESULT ProjectSaved (void);

	HRESULT CreateNewGeoObjects (DGeoObjects **ppIObjs);

friend class CDocTree;
};

//////////////////////////////////////////////////////////////////////////////
// Return values for TestDroppablePoint 
#define UDROP_NONE              0x0000      // Exclusive
#define UDROP_CLIENT            0x0001      // Inclusive
#define UDROP_INSETLEFT         0x0002      // L/R are exclusive
#define UDROP_INSETRIGHT        0x0004
#define UDROP_INSETHORZ         (UDROP_INSETLEFT|UDROP_INSETRIGHT)

#define UDROP_INSETTOP          0x0008      // T/B are exclusive
#define UDROP_INSETBOTTOM       0x0010
#define UDROP_INSETVERT         (UDROP_INSETTOP|UDROP_INSETBOTTOM)

#define UDROP_INSET				(UDROP_INSETHORZ|UDROP_INSETVERT)

///////////////////////////////////////////////////////////////////////////////
// Strukturen/Datentypen für Binding
typedef HRESULT (CGeoDoc::* GETOBJECTPROC) (LPCTSTR pcItem, DWORD dwSpeedNeeded, IBindCtx *pbc, REFIID riid, LPVOID *ppvObj, bool fTestRunningOnly);
typedef HRESULT (CGeoDoc::* PARSEDISPLAYNAMEPROC) (IBindCtx *pbc, LPOLESTR pszDisplayName, ULONG *pchEaten, IMoniker **ppmkOut);

typedef struct tagKNOWNOBJECT {
	LPCTSTR pcObjName;					// ObjektTyp
	size_t iObjNameSize;				// Länge des ObjektTypBezeichners
	GETOBJECTPROC fnGetObject;
	bool fEatGetObjectPrefix;
	PARSEDISPLAYNAMEPROC fnParseDisplayName;
} KNOWNOBJECT;

#endif // _DOC_HXX
