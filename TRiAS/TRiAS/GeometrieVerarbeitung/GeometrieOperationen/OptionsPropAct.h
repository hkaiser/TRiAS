// Deklarationen: PropertyAction für Optionen der Objektoperationen
// File: OptionsPropAct.h
// W. Mörtl

#ifndef _OPTIONSPROPACT_H
#define _OPTIONSPROPACT_H

#include "SmartInterfaces.h"

#include "ObjOperR.h"		// Ressourcekonstanten (IDR_OPTIONSPROPACT, ...)

#include <Com/OleClientSiteNotImpl.h>
#include "OptionsDlg.h"		// OPTIONSRESULT



///////////////////////////////////////////////////////////////////////////////////////////////
// Klasse für die Optionen der Geometrieoperationen
// IGetGeoOperatOptions ist das Interface, das COptionsPropAct für die CRegOperatPropAct- bzw.
// CSetsOperatPropAct-Klasse bereitstellt, d.h. das Interface, über das diese Klassen
// COptionsPropAct rufen können
class COptionsPropAct : 
	public CPropertyAction,
	public CComObjectRoot,
	public IGetGeoOperatOptions,
#if _TRiAS_VER >= 0x0300
	public IObjectWithSiteImpl<COptionsPropAct>,
	public IOleClientSiteNotImpl,
#endif // _TRiAS_VER >= 0x0300
	public CComCoClass<COptionsPropAct, &CLSID_OptionsPropAct>
{
private:
	HPROJECT m_hPr;

	class COptionsDlg* m_pOptionsDlg;
	string m_sDesc;				// Beschreibungstext
	bool m_bIsDirty;			// Dialogparameter wurden verändert (true)
	bool m_bIsInitialized;		// Dialog wurde initialisiert (true)
	bool m_bHasInitData;		// Initialisierungsdaten für den Dialog wurden von Load()
								// bereitgestellt, konnten aber noch nicht an diesen
								// weitergereicht werden (true)

	typedef list<WEnumLONG> CPassObjs;// Klasse der von der PropertyPage durchzureichenden Objekte
	CPassObjs m_PassObjs;		// von der PropertyPage durchzureichende Objekte selbst
	CPassObjs::iterator m_ObjsIter;

	OPTIONSRESULT m_caSelInfo;

//	WProgressIndicator2 m_wProgInd;	// eigener ProgressIndicator, wenn keiner runtergereicht wird
//	PIFLAGS m_rgFlags;			// Flags des eigenen ProgressIndicator

	WMoniker m_mkSite;			// Moniker der PropertySequence

protected:
	HRESULT GetThisMoniker(DWORD dwWhichMoniker, IMoniker **ppmk);

public:
	// Konstruktor, Destruktor
		COptionsPropAct (void);
		~COptionsPropAct (void);

	DECLARE_AGGREGATABLE (COptionsPropAct)		// class factory
	DECLARE_REGISTRY_RESOURCEID (IDR_OPTIONSPROPACT)

	BEGIN_COM_MAP(COptionsPropAct)
		COM_INTERFACE_ENTRY2 (IPropertyAction, IPropertyAction2)
		COM_INTERFACE_ENTRY (IPropertyAction2)
		COM_INTERFACE_ENTRY (IPersistPropertyBag)
		COM_INTERFACE_ENTRY (IClassProperty)
		COM_INTERFACE_ENTRY (IPersistStreamInit)
		COM_INTERFACE_ENTRY2 (IPersistStream, IPersistStreamInit)
		COM_INTERFACE_ENTRY2 (IPersist, IPersistStreamInit)
		COM_INTERFACE_ENTRY (IPropertyInfo)
		COM_INTERFACE_ENTRY (IGetGeoOperatOptions)
#if _TRiAS_VER >= 0x0300
		COM_INTERFACE_ENTRY (IOleClientSite)
		COM_INTERFACE_ENTRY (IObjectWithSite)
#endif // _TRiAS_VER >= 0x0300
	END_COM_MAP()

// IObjectWithSite
	STDMETHOD(SetSite)(IUnknown *pUnkSite);

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
	STDMETHOD (IsDirty)(THIS);
	STDMETHOD (Load)(THIS_ LPSTREAM pStm);
	STDMETHOD (Save)(THIS_ LPSTREAM pStm, BOOL fClearDirty);
	STDMETHOD (GetSizeMax)(THIS_ ULARGE_INTEGER *pcbSize);
	STDMETHOD (InitNew)(THIS);

// IPersistPropertyBag
	STDMETHOD(Load)(THIS_ IPropertyBag *pBag, IErrorLog *pLog);

// IGetGeoOperatOptions methods
	STDMETHOD (GetOptions) (THIS_ DWORD* pdwOptions);

// IOleClientSite
	STDMETHOD (GetMoniker) (THIS_ DWORD dwAssign, DWORD dwWhichMoniker, IMoniker **ppmk);

// sonstiges
	void SetDirty (bool bDirty = true);
};

#endif // _OPTIONSPROPACT_H
