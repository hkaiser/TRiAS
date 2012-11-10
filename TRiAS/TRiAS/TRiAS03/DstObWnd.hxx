// PropertyAction, welche Objekte aus RechercheFenster auswählt und zusammenstellt
// File: DSTOBWND.HXX

#if !defined(_DSTOBWND_HXX)
#define _DSTOBWND_HXX

#include <ospace/std/map>
#include <ospace/std/vector>

#include <propactn.h>
#include <dstobwnd.h>

#include "propactb.hxx"
#include "dstobdlg.hxx"

///////////////////////////////////////////////////////////////////////////////
// Versioning
#define DESTWINDPA_VERSION_100			0x0100
#define DESTWINDPA_VERSION_101			0x0101
#define DESTWINDPA_LASTKNOWNVERSION		DESTWINDPA_VERSION_101
#define DESTWINDPA_MINORVERSIONMASK		0xff
#define DESTWINDPA_SIGNATURE			0x65505744		// DWPA

///////////////////////////////////////////////////////////////////////////////
// aux defines
#define DEFAULT_MARK_COLOR				RGB(255, 0, 0)
#define MAX_ORWNDS_TOSHOW				100

///////////////////////////////////////////////////////////////////////////////
// 
class CDestObjWndPropAct : 
	public CPropertyActionExt,	// JG 980914
	public CComObjectRoot,
	public IObjectWithSiteImpl<CDestObjWndPropAct>,
	public CComCoClass<CDestObjWndPropAct, &CLSID_DestinationObjectWindow>
{
private:
	CDestObjWndDlg *m_pCfgDlg;
	string m_strDesc;

	bool m_fIsDirty;		// DirtyFlag
	bool m_fIsInitialized;	// ist fertig initialisiert
	bool m_fIsFirstPacket;
	bool m_fPutAllInOne;
	bool m_fShownWarning;
	bool m_fForceNew;

	HWND m_hWnd;

	typedef map<long, HWND, less<long> > CPacketWnds;
	CPacketWnds m_Wnds;

	COLORREF m_cMColor;			// Markierungsfarbe
	os_string m_strCaption;		// ggf. Caption 
	os_string m_strErrorMsg;	// ggf. Fehlermeldung

	ULONG m_lPacket;
	ULONG m_lMissingPacketOffset;

	os_vector<long> m_vecCollectObjects;

protected:
	HRESULT SetEnumLONG (IDataObject *pIDO, IEnum<LONG> *ppEnum, long lPacket, IObjectProperty *pIObjProp);

public:
	BEGIN_COM_MAP(CDestObjWndPropAct)
		COM_INTERFACE_ENTRY(IPropertyAction)
		COM_INTERFACE_ENTRY(IPropertyAction2)
		COM_INTERFACE_ENTRY(IPropertyAction3)
		COM_INTERFACE_ENTRY(IClassProperty)
		COM_INTERFACE_ENTRY(IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersistStream, IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
		COM_INTERFACE_ENTRY(IPropertyInfo)
		COM_INTERFACE_ENTRY(IObjectWithSite)
		COM_INTERFACE_ENTRY(IPersistPropertyBag)
	END_COM_MAP()

	DECLARE_AGGREGATABLE(CDestObjWndPropAct)		// class factory
	DECLARE_STATIC_REGISTRY_RESOURCEID(IDR_PROPINFO_ORWNDDEST)

	BEGIN_CATEGORY_MAP(CDestObjWndPropAct)
		IMPLEMENTED_CATEGORY(CATID_TRiASGeoComponent)
	END_CATEGORY_MAP()

		CDestObjWndPropAct (void);
		~CDestObjWndPropAct (void);

static HRESULT CreateInstance (IClassProperty **ppIClsProp)
	{ return _CreatorClass::CreateInstance(NULL, IID_IClassProperty, (LPVOID *)ppIClsProp); }

// *** IPropertyAction methods
	STDMETHOD (AddConfigPages) (THIS_ LPFNADDPROPSHEETPAGE lpfnAddPage, 
				LPARAM lParam, LPCSTR pcDesc, UINT *puiCnt);
	STDMETHOD (PreConfigPages) (THIS_ IDataObject *pIDataObject, DWORD dwFlags);
	STDMETHOD (DoAction) (THIS_ IDataObject *pEnumObj, DWORD dwReserved);
	STDMETHOD (EndAction) (THIS_ DWORD dwReserved, IDataObject **ppEnumObj);

// *** IClassProperty specific functions ***
	STDMETHOD(GetPropInfo) (THIS_ LPSTR pBuffer, WORD wLen, DWORD *pdwFlags);
	STDMETHOD(HelpInfo)(THIS_ LPSTR pBuffer, ULONG ulLen, 
						LPSTR pHelpFile, ULONG *pulHelpCtx);

// *** IPropertyInfo specific functions 
	STDMETHOD(SetPropInfo) (THIS_ LPCSTR pBuffer, DWORD dwFlags);

// *** IPersist methods
	STDMETHOD(GetClassID)(THIS_ LPCLSID lpClassID);

// *** IPersistStreamInit methods
	STDMETHOD(IsDirty)(THIS);
	STDMETHOD(Load)(THIS_ LPSTREAM pStm);
	STDMETHOD(InitNew)(THIS);
	STDMETHOD(Save)(THIS_ IStream *pStm, BOOL fClearDirty);
	STDMETHOD(GetSizeMax)(THIS_ ULARGE_INTEGER *pcbSize);

// IPersistPropertyBag
	STDMETHOD(Load)(IPropertyBag *pBag, IErrorLog *pLog);

// sonstiges
	void SetDirty (bool fDirty = true);
};

#endif // _DSTOBWND_HXX
