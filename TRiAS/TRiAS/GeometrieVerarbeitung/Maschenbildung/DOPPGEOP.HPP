//	Suche Objekte gleicher Geometrie
//	File: DOPPGEOP.HPP

#if !defined(_DOPPGEOP_HPP)
#define _DOPPGEOP_HPP

#include "GeoObj.h"
#include <ospace/std/set>

#include <Com/PropertyActionBase.h>		// Basisklasse

class CProgressIndicator;

class CDoppGeoPropAction : 
	public CPropertyActionImpl,
	public CComObjectRoot,
	public IObjectWithSiteImpl<CDoppGeoPropAction>,			//KK021217
	public CComCoClass<CDoppGeoPropAction, &CLSID_FindDoubledObjects>
{
private:
	CString m_strDesc;
	BOOL m_bIsInitialized;				// ist fertig initialisiert
	HDEX m_hDex;
	long m_lPacket;

	typedef set<CGObject, less<CGObject> > CGeometries;
	typedef multiset<CGObject, less<CGObject> > CDupGeometries;

	CGeometries m_Geoms;
	CGeometries::const_iterator m_GeomIt;
	CDupGeometries m_DupObjs;

	enum { 
		PA_TYPEFLAGS = 
			PROPCAPS_ACTION_SINK |
			PROPCAPS_ACTION_SOURCE 
	};

public:
	BEGIN_COM_MAP(CDoppGeoPropAction)
		COM_INTERFACE_ENTRY2 (IPropertyAction, IPropertyAction2)
		COM_INTERFACE_ENTRY(IPropertyAction2)
		COM_INTERFACE_ENTRY(IClassProperty)
		COM_INTERFACE_ENTRY(IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersistStream, IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
		COM_INTERFACE_ENTRY(IPersistPropertyBag)
		COM_INTERFACE_ENTRY(IPropertyInfo)
		COM_INTERFACE_ENTRY(IObjectWithSite)			//KK021217
	END_COM_MAP()

	DECLARE_NOT_AGGREGATABLE(CDoppGeoPropAction)		// class factory
	DECLARE_REGISTRY_RESOURCEID(IDR_DOPPELTE_PROPACT_RGS)

	CDoppGeoPropAction (void);
	~CDoppGeoPropAction (void);

static HRESULT CreateInstance (IClassProperty **ppIClsProp)
	{ return _CreatorClass::CreateInstance(NULL, IID_IClassProperty, (LPVOID *)ppIClsProp); }

//	IClassProperty specific functions 
	STDMETHOD(GetPropInfo) (THIS_ LPSTR pBuffer, WORD wLen, DWORD *pdwFlags);
	STDMETHOD(HelpInfo)(THIS_ LPSTR pBuffer, ULONG ulLen, 
					    LPSTR pHelpFile, ULONG *pulHelpCtx);

//	IPropertyAction methods
	STDMETHOD (AddConfigPages) (THIS_ LPFNADDPROPSHEETPAGE lpfnAddPage, 
				LPARAM lParam, LPCSTR pcDesc, UINT *puiCnt);
	STDMETHOD (PreConfigPages) (THIS_ IDataObject *pIDataObject, DWORD dwFlags);
	STDMETHOD (DoAction) (THIS_ IDataObject *pEnumObj, DWORD dwReserved);
	STDMETHOD (EndAction) (THIS_ DWORD dwReserved, IDataObject **ppEnumObj);

//	IPropertyInfo specific functions 
	STDMETHOD(SetPropInfo) (THIS_ LPCSTR pBuffer, DWORD dwFlags);

//	IPersist methods
	STDMETHOD(GetClassID)(THIS_ LPCLSID lpClassID);

//	IPersistStreamInit methods
	STDMETHOD(InitNew)(THIS);

//	IPersistStream methods
	STDMETHOD(GetSizeMax)(ULARGE_INTEGER *pcbSize);
	STDMETHOD(IsDirty)(THIS);
	STDMETHOD(Load)(THIS_ LPSTREAM pStm);
	STDMETHOD(Save)(LPSTREAM pStm, BOOL fClearDirty);

// IPersistPropertyBag
	STDMETHOD(Load)(IPropertyBag *pBag, IErrorLog *pLog);


	STDMETHODIMP GetConfigData (void);			//KK021217

protected:
//	BOOL CompareObjects (
//		CGeometrieObjectListe &Liste, CProgressIndicator *pIndicator,
//		CString const &strCaption, WEnumObjectsByNumber &WEnumObjs,	//	Objektnummern-Ausgabe-Strom
//		BOOL bIsFlaeche = FALSE);

	void FinalRelease (void);

private:
	double m_dTolerance;
	//KK021217 - Attribut-Kurztext, in der bei doppelter GI 0x100 eingetragen wird
	CComBSTR m_bstrError;


};

#endif	// _DOPPGEOP_HPP

