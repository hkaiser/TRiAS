// Deklarationen: PropertyAction für Operationen von GeoObjekten mit Bezugsobjekt(en)
// File: RegOperatPropAct.h
// W. Mörtl

#ifndef _REGOPERATPROPACT_H
#define _REGOPERATPROPACT_H


#include "SmartInterfaces.h"

#include "ObjOperR.h"			// Ressourcekonstanten (IDR_REGOPERATPROPACT, ...)

#include "RegardOperatDlg.h"	// REGOPERATRESULT



///////////////////////////////////////////////////////////////////////////////////////////////
// Klasse für die Mengenoperationen von GeoObjekten
// ISetGeoOperatOptionsTarget ist das Interface, über welches die CRegOperatPropAct- bzw.
// CSetsOperatPropAct-Klasse das Interface der Klasse COptionsPropAct übergeben bekommt
class CRegOperatPropAct : 
	public CPropertyAction,
	public CComObjectRoot,
	public ISetGeoOperatOptionsTarget,
#if _TRiAS_VER >= 0x0300
	public IObjectWithSiteImpl<CRegOperatPropAct>,
#endif // _TRiAS_VER >= 0x0300
	public CComCoClass<CRegOperatPropAct, &CLSID_RegOperatPropAct>
{
private:
	HDEX m_hDex;				// Handle der nachgeladenen Erweiterung ObjOper.ext
	HPROJECT m_hPr;

	class CRegardOperatDlg* m_pRegOperDlg;
	string m_sDesc;				// Beschreibungstext
	bool m_bIsDirty;			// Dialogparameter wurden verändert (true)
	bool m_bIsInitialized;		// Dialog wurde initialisiert (true)
	bool m_bHasInitData;		// Initialisierungsdaten für den Dialog wurden von Load()
								// bereitgestellt, konnten aber noch nicht an diesen
								// weitergereicht werden (true)

	typedef list<WEnumLONG> CInObjs;// Klasse der an die PropertyPage übergebenen Objekte
	CInObjs m_InObjs;			// an die PropertyPage übergebene Objekte selbst
	CInObjs::iterator m_ObjsIter;

	REGOPERATRESULT m_caSelInfo;

	WGetGeoOperatOptions m_wOperOptions;
	WMoniker m_mkOperOptions;

protected:
	HRESULT EnsureOptionsIF();

public:
	// Konstruktor, Destruktor
		CRegOperatPropAct (void);
		~CRegOperatPropAct (void);

	void FinalRelease (void);

	DECLARE_AGGREGATABLE (CRegOperatPropAct)		// class factory
	DECLARE_REGISTRY_RESOURCEID (IDR_REGOPERATPROPACT)

	BEGIN_COM_MAP(CRegOperatPropAct)
		COM_INTERFACE_ENTRY2 (IPropertyAction, IPropertyAction2)
		COM_INTERFACE_ENTRY (IPropertyAction2)
		COM_INTERFACE_ENTRY (IPersistPropertyBag)
		COM_INTERFACE_ENTRY (IClassProperty)
		COM_INTERFACE_ENTRY (IPersistStreamInit)
		COM_INTERFACE_ENTRY2 (IPersistStream, IPersistStreamInit)
		COM_INTERFACE_ENTRY2 (IPersist, IPersistStreamInit)
		COM_INTERFACE_ENTRY (IPropertyInfo)
		COM_INTERFACE_ENTRY (ISetGeoOperatOptionsTarget)
#if _TRiAS_VER >= 0x0300
		COM_INTERFACE_ENTRY (IObjectWithSite)
#endif // _TRiAS_VER >= 0x0300
	END_COM_MAP()

// IClassProperty specific functions
	STDMETHOD(GetPropInfo) (THIS_ LPSTR pBuffer, WORD wLen, DWORD *pdwFlags);
	STDMETHOD(HelpInfo)(THIS_ LPSTR pBuffer, ULONG ulLen, LPSTR pHelpFile, ULONG *pulHelpCtx);

// IPropertyAction methods
	STDMETHOD (AddConfigPages) (THIS_ LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam,
								LPCSTR pcDesc, UINT *puiCnt);
	STDMETHOD (PreConfigPages) (THIS_ IDataObject* pIDataObj, DWORD dwFlags);
	STDMETHOD (BeginAction) (THIS_ IProgressIndicator* pIProgInd = 0);
	STDMETHOD (DoAction) (THIS_ IDataObject *pEnumObj, DWORD dwReserved);
	STDMETHOD (EndAction) (THIS_ DWORD dwReserved, IDataObject **ppEnumObj);

// IPropertyInfo specific functions 
	STDMETHOD(SetPropInfo) (THIS_ LPCSTR pBuffer, DWORD dwFlags);

// IPersist methods
	STDMETHOD(GetClassID)(THIS_ LPCLSID lpClassID);

// IPersistStreamInit methods
	STDMETHOD(IsDirty)(THIS);
	STDMETHOD(Load)(THIS_ LPSTREAM pStm);
	STDMETHOD(Save)(THIS_ LPSTREAM pStm, BOOL fClearDirty);
	STDMETHOD(GetSizeMax)(THIS_ ULARGE_INTEGER *pcbSize);
	STDMETHOD(InitNew)(THIS);

// IPersistPropertyBag
	STDMETHOD(Load)(THIS_ IPropertyBag *pBag, IErrorLog *pLog);

// ISetGeoOperatOptionsTarget methods
	STDMETHOD (SetOperatOptionsSite) (IGetGeoOperatOptions* pOperOptions);

// sonstiges
	void SetDirty (bool bDirty = true);
};

#endif // _REGOPERATPROPACT_H
