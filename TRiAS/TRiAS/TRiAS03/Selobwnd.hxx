// PropertyAction, welche Objekte aus RechercheFenster auswählt und zusammenstellt
// File: SELOBWND.HXX

#if !defined(_SELOBWND_HXX)
#define _SELOBWND_HXX

#include <propactn.h>
#include <selobwnd.h>

#include "propactb.hxx"		// CPropertyAction
#include "selobdlg.hxx"		// CSelectObjWndDlg

///////////////////////////////////////////////////////////////////////////////
// Versioning
#define SRCWINDPA_VERSION_0100			0x0100
#define SRCWINDPA_VERSION_0101			0x0101
#define SRCWINDPA_VERSION_0102			0x0102
#define SRCWINDPA_VERSION_0103			0x0103
#define SRCWINDPA_LASTKNOWNVERSION		SRCWINDPA_VERSION_0103
#define SRCWINDPA_MINORVERSIONMASK		0xff
#define SRCWINDPA_SIGNATURE				0x65505753		// SWPA

///////////////////////////////////////////////////////////////////////////////
// 
class CSelObjWndPropAct : 
	public CPropertyActionExt,	// JG 980916
	public CComObjectRoot,
	public IObjectWithSiteImpl<CSelObjWndPropAct>,
	public CComCoClass<CSelObjWndPropAct, &CLSID_SelectFromObjectWindow>
{
private:
	class CSelectObjWndDlg *m_pCfgDlg;
	string m_strDesc;

	bool m_fIsDirty;		// DirtyFlag
	bool m_fIsInitialized;	// ist fertig initialisiert
	bool m_fHasInitData;
	bool m_fCloseWhenReady;
	bool m_fDisableCloseWhenReady;
	bool m_fShowConfigAlways;
	bool m_fWindowWasShown;

	HWND m_hWnd;
	DWORD m_dwFlags;
	LONG m_lActObj;

protected:
	HRESULT GetEnumLONG (LONG lONr, IEnum<LONG> **ppIEnum);
	HRESULT GetWindowToIgnore (HWND *phWnd = NULL);
	long GetRealMinCount();

	bool WindowShouldBeHidden()
	{
		// das Fenster wird nicht angezeigt, wenn es gefordert ist (NoShow)
		// oder wenn nur die minimale Anzahl von OR Fensters geöffnet ist und
		// die anzeige nicht erzwungen wurde
		return (
			IsNoShow() || 
			(	!m_fShowConfigAlways && 
				GetRealMinCount() > DEX_ActiveObjectsCount()
			)
		); 
	}

public:
	BEGIN_COM_MAP(CSelObjWndPropAct)
		COM_INTERFACE_ENTRY(IPropertyAction)
		COM_INTERFACE_ENTRY(IPropertyAction2)
		COM_INTERFACE_ENTRY(IPropertyAction3)
		COM_INTERFACE_ENTRY(IClassProperty)
		COM_INTERFACE_ENTRY(IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersistStream, IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
		COM_INTERFACE_ENTRY(IPropertyInfo)
		COM_INTERFACE_ENTRY(IPersistPropertyBag)
		COM_INTERFACE_ENTRY(IObjectWithSite)
	END_COM_MAP()

	DECLARE_AGGREGATABLE(CSelObjWndPropAct)		// class factory
	DECLARE_STATIC_REGISTRY_RESOURCEID(IDR_PROPINFO_OBJWND)

		CSelObjWndPropAct (void);
		~CSelObjWndPropAct (void);

static HRESULT CreateInstance (IClassProperty **ppIClsProp)
	{ return _CreatorClass::CreateInstance(NULL, IID_IClassProperty, (LPVOID *)ppIClsProp); }

// IClassProperty specific functions 
	STDMETHOD(GetPropInfo) (THIS_ LPSTR pBuffer, WORD wLen, DWORD *pdwFlags);
	STDMETHOD(HelpInfo)(THIS_ LPSTR pBuffer, ULONG ulLen, 
					    LPSTR pHelpFile, ULONG *pulHelpCtx);

// IPropertyAction methods
	STDMETHOD (AddConfigPages) (THIS_ LPFNADDPROPSHEETPAGE lpfnAddPage, 
					LPARAM lParam, LPCSTR pcDesc, UINT *puiCnt);
	STDMETHOD (PreConfigPages) (THIS_ IDataObject *pIDataObj, DWORD dwFlags);
	STDMETHOD (BeginAction) (THIS_ IProgressIndicator *pPI);
	STDMETHOD (EndAction) (THIS_ DWORD dwReserved, IDataObject **ppEnumObj);

// IPropertyInfo specific functions 
	STDMETHOD(SetPropInfo) (THIS_ LPCSTR pBuffer, DWORD dwFlags);

// IPersist methods
	STDMETHOD(GetClassID)(THIS_ LPCLSID lpClassID);

// IPersistStreamInit methods
	STDMETHOD(IsDirty)(THIS);
	STDMETHOD(GetSizeMax)(ULARGE_INTEGER *pcbSize);
	STDMETHOD(Load)(THIS_ LPSTREAM pStm);
	STDMETHOD(Save)(THIS_ LPSTREAM pStm, BOOL fClearDirty);
	STDMETHOD(InitNew)(THIS);

// IPersistPropertyBag
	STDMETHOD(Load) (THIS_ IPropertyBag *pBag, IErrorLog *pLog);

// sonstiges
	void SetDirty (bool fDirty = true);

private:
	SELECTMODE m_rgMode;
	long m_lMinWindowCount;		// Dialog erst ab dieser Anzahl von existierenden Fenstern anzeigen
	HWND m_hWndIgnore;			// dieses Fenster nicht in Liste anbieten
	bool m_fMakePackets;		// einzelne Fenster in einzelne Pakete verpacken
	bool m_fAllowForOneObjectSelection;		// nur ein Objekt selektierbar machen
	ULONG m_ulPacket;			// Paketnummer
};

#endif // _SELOBWND_HXX
