// Ein ObjektrechercheFenster in TRiAS ----------------------------------------
// File: OBJWIN.HXX

#if !defined(_OBJWIN_HXX)
#define _OBJWIN_HXX

class CTriasApp;
class CGeoDoc;

class CGeoObjectWin : 
	public CComDualImpl<DGeoObjectWin, &IID_DGeoObjectWin, &LIBID_TRiAS, 
				TYPELIB_VERSION_MAJOR, TYPELIB_VERSION_MINOR>, 
	public CComISupportErrorInfoImpl<&IID_DGeoObjectWin>,
	public CComObjectRoot
{
private:
	LPUNKNOWN m_pUnk;		// controlling unknown
	CTriasApp *m_pApp;		// Trias.Application
	CGeoDoc *m_pDoc;		// Trias.Project

	HWND m_hORWnd;			// ObjektRechercheFenster
	char *m_pName;			// Caption
	bool m_fValid;			// Objekt existiert
 	
	void Invalidate (void);

protected:
	HRESULT HandleGeoObject (CGeoObject *pObject, GEOOBJECTMODE rgMode);
	HRESULT HandleClass (CClass *pClass, GEOCLASSMODE rgMode);

///////////////////////////////////////////////////////////////////////////////
// Lage- und Größenveränderung
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
		CGeoObjectWin (void);
		~CGeoObjectWin (void);
		
static CGeoObjectWin *CreateInstance (LPUNKNOWN pUnk, CTriasApp *pApp, 
		CGeoDoc *pDoc, HWND hWnd, GEOOBJWINMODE rgMode);

static CGeoObjectWin *CreateInstance (LPUNKNOWN pUnk, CTriasApp *pApp, 
		CGeoDoc *pDoc, LPCSTR bName, GEOOBJWINMODE rgMode);

	bool FInit (LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc,
		HWND hWnd, GEOOBJWINMODE rgMode);
	bool FInit (LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc,
		LPCSTR bName, GEOOBJWINMODE rgMode);

///////////////////////////////////////////////////////////////////////////////
// ATL stuff
	BEGIN_COM_MAP(CGeoObjectWin)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(DGeoObjectWin)
		COM_INTERFACE_ENTRY(DTRiASBaseClass)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

	DECLARE_NOT_AGGREGATABLE(CGeoObjectWin)

///////////////////////////////////////////////////////////////////////////////
// Verwalten der externen Locks
	ULONG InternalAddRef(void);
	ULONG InternalRelease(void);
	HRESULT FinalExternalConstruct (void);
	void FinalExternalRelease (void);
//	static CComGlobalsThreadModel::AutoCriticalSection m_cs;

///////////////////////////////////////////////////////////////////////////////
// *** _IGeoObjectWin methods 
	STDMETHOD(get_isA)(LONG *plRTTI);
	STDMETHOD(get_Parent)(IDispatch **ppIDisp);
	STDMETHOD(get_Application)(IDispatch **ppIDisp);
	STDMETHOD(put_Parent)(THIS_ IDispatch * pIBase);
	STDMETHOD(put_Application)(THIS_ IDispatch * pIApp);

	STDMETHOD(get_Properties) (THIS_ _DTRiASProperties **ppIProps);
	STDMETHOD(CreateProperty) (THIS_ VARIANT vName, VARIANT vType, VARIANT vValue, _DTRiASProperty **ppIProp);

	STDMETHOD(get_Value)(THIS_ long *phWnd);
	
	STDMETHOD(get_Name)(THIS_ BSTR *pbstrValue);
	STDMETHOD(put_Name)(THIS_ BSTR bstrValue);
	
	STDMETHOD(get_Visible)(THIS_ VARIANT_BOOL *pfVisible);
	STDMETHOD(put_Visible)(THIS_ VARIANT_BOOL fVisible);

	STDMETHOD(GetActObject)(THIS_ DGeoObject **ppIObj);
	STDMETHOD(SetActObject)(THIS_ DGeoObject *pIObj);

	STDMETHOD(GetClasses)(THIS_ VARIANT vClss, VARIANT vLogMode, DGeoClasses **ppIClss);
	STDMETHOD(GetClass)(THIS_ VARIANT vCls, VARIANT vMode, DGeoClass **ppICls);

	STDMETHOD(GetObjects)(THIS_ VARIANT vObjs, VARIANT vLogMode, DGeoObjects **ppIObjs);
	STDMETHOD(GetObject)(THIS_ VARIANT vObj,  VARIANT vMode, DGeoObject **ppIObj);

	STDMETHOD(AddMenuItem)(THIS_ int iSubMenu, int iPos, BSTR bstrText, VARIANT vHelpText);
	STDMETHOD(GetSelectedObjects)(THIS_ DGeoObjects **ppIObjs);
	STDMETHOD(SetShownFeature)(THIS_ BSTR bstrFeatName);

    STDMETHOD(get_Left)(THIS_ long *plLeft);
    STDMETHOD(put_Left)(THIS_ long lLeft);
    STDMETHOD(get_Top)(THIS_ long *plTop);
    STDMETHOD(put_Top)(THIS_ long lTop);
    STDMETHOD(get_Width)(THIS_ long *plWidth);
    STDMETHOD(put_Width)(THIS_ long lWidth);
    STDMETHOD(get_Height)(THIS_ long *plHeight);
    STDMETHOD(put_Height)(THIS_ long lHeight);

    STDMETHOD(IsActive)(THIS_ VARIANT_BOOL *IsActWin);
    STDMETHOD(SetActive)(THIS);

    STDMETHOD(get_Color)(THIS_ long *plColor);
    STDMETHOD(put_Color)(THIS_ long lColor);

///////////////////////////////////////////////////////////////////////////////
// sonstige Member
	bool ClassIsMemberOfObjWin  (CClass *pClass);
	bool FRemoveIdentFromObjWin (ULONG lIdent);

	bool ObjectIsMemberOfObjWin (CGeoObject *pObject);
	bool AddObjectToObjWin		(CGeoObject *pObject);
	bool RemoveObjectFromObjWin (CGeoObject *pObject);

	HWND GetValue (bool fForce = false);
	char *GetName (bool fForce = false);
	bool SetName (const char *pName, bool fCreate = true, bool fIgnoreValid = false);
	bool Remove (void);

inline void Validate (void) { m_fValid = true; }
inline bool IsValid  (void) { return m_fValid ? true : false; }

///////////////////////////////////////////////////////////////////////////////
// for the tree's
	 HWND& FGetHWND (void);				// liefert SuchSchlüssel

friend int FCmpHWND (const HWND &, const HWND &);	// vergleicht 2 Schlüssel
friend class CObjWinTree;
};

#endif // _OBJWIN_HXX
