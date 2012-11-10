// Alle ObjektPropertyExtensions aller Erweiterungen --------------------------
// File: ALLOPROP.HXX

#if !defined(_ALLOPROP_HXX)
#define _ALLOPROP_HXX

#include <Com/Thunk.h>

#include <CalClsId.h>
#include <ioprpini.hxx>

///////////////////////////////////////////////////////////////////////////////
// lokal verwendete SmartIF's
DefineSmartInterface(InitObjPropMerkmal);

///////////////////////////////////////////////////////////////////////////////
// Container, für das Zwischenspeichern einer Menge von Objekteigenschaften
typedef map<os_string, WObjectProperty, less<os_string> > CPropsMap;
typedef map<CPropertyName, WObjectProperty, less<CPropertyName> > CPropsMapEx;
typedef list<os_pair<os_string, WObjectProperty> > CPropsList;

///////////////////////////////////////////////////////////////////////////////
// Cache der Objekteigenschaften
class CPropsCache
{
public:
	CPropsCache() {}
	~CPropsCache() {}

	HRESULT FindProps (INT_PTR lIdent, CPropsMapEx **ppProps = NULL)
	{
	HPROJECT hPr = DEX_GetObjectsProject(lIdent);

		if (DEX_GetTRiASDataSourceEx(hPr)) {
		CPrjProps::iterator it = m_PrjProps.find(hPr);

			if (it != m_PrjProps.end()) {
				if (NULL != ppProps) 
					*ppProps = &(*it).second;
				return S_OK;
			}
		}
		else {
		CIdentProps::iterator it = m_IdentProps.find(lIdent);

			if (it != m_IdentProps.end()) {
				if (NULL != ppProps) 
					*ppProps = &(*it).second;
				return S_OK;
			}
		}
		return S_FALSE;
	}

	HRESULT AddProperty (INT_PTR lIdent, CPropertyName &rPropName, IObjectProperty *pIObjProp)
	{
	HPROJECT hPr = DEX_GetObjectsProject(lIdent);
	WObjectProperty Prop (pIObjProp);

		if (DEX_GetTRiASDataSourceEx(hPr)) {
		// TRiAS Datenquelle (alle Idents haben identischen Satz von Objekteigenschaften)
		CPrjProps::iterator it = m_PrjProps.find(hPr);

			if (it == m_PrjProps.end()) {
			pair<CPrjProps::iterator, bool> p = m_PrjProps.insert(
				CPrjProps::value_type(hPr, CPropsMapEx()));

				_ASSERTE(p.second);
				it = p.first;
			}
				
			_ASSERTE(it != m_PrjProps.end());
			(*it).second.insert(CPropsMapEx::value_type(rPropName, Prop));
		}
		else {
		CIdentProps::iterator it = m_IdentProps.find(lIdent);

			if (it == m_IdentProps.end()) {
			pair<CIdentProps::iterator, bool> p = m_IdentProps.insert(
				CIdentProps::value_type(lIdent, CPropsMapEx()));

				_ASSERTE(p.second);
				it = p.first;
			}
			
			_ASSERTE(it != m_IdentProps.end());
			(*it).second.insert(CPropsMapEx::value_type(rPropName, Prop));
		}			
		return S_OK;
	}
	
	HRESULT RemoveProps (INT_PTR lIdent)
	{
	HPROJECT hPr = DEX_GetObjectsProject(lIdent);

		if (DEX_GetTRiASDataSourceEx(hPr)) {
		// Liste der Objekteigenschaften finden
		CPrjProps::iterator itprj = m_PrjProps.find (hPr);

			if (itprj == m_PrjProps.end())
				return E_UNEXPECTED;

		// allen Objekteigenschaften Bescheid sagen
			CPropsMapEx::iterator end = (*itprj).second.end();
			for (CPropsMapEx::iterator it = (*itprj).second.begin(); it != end; ++it) {
			WInitObjPropMerkmal Init;
			
				if (SUCCEEDED((*it).second -> QueryInterface (Init.ppi())))
					Init -> RemoveAllObjects ((INT_PTR)hPr);
			}

		// gesamte Liste freigeben
			m_PrjProps.erase(itprj);
		}
		else {
		// Liste der Objekteigenschaften finden
		CIdentProps::iterator itident = m_IdentProps.find(lIdent);

			if (itident == m_IdentProps.end()) 
				return E_UNEXPECTED;

		// allen Objekteigenschaften Bescheid sagen
			CPropsMapEx::iterator end = (*itident).second.end();
			for (CPropsMapEx::iterator it = (*itident).second.begin(); it != end; ++it) {
			WInitObjPropMerkmal Init;
			
				if (SUCCEEDED((*it).second -> QueryInterface (Init.ppi())))
					Init -> RemoveObjects (lIdent);
			}

		// gesamte Liste freigeben
			m_IdentProps.erase(itident);
		}
		return S_OK;
	}
	
	void Clear() 
	{
		m_PrjProps.clear();
		m_IdentProps.clear();
	}

private:
	typedef map<HPROJECT, CPropsMapEx, less<HPROJECT> > CPrjProps;
	typedef map<INT_PTR, CPropsMapEx, less<INT_PTR> > CIdentProps;

	CPrjProps m_PrjProps;
	CIdentProps m_IdentProps;
};

///////////////////////////////////////////////////////////////////////////////
// Die Menge der Objekteigenschaften ...
class CEnumObjectProperties;		// forward declaration

class CAllProperties : 
	public IObjectProps,
	public IObjectProps3 
{
private:
#if defined(_DEBUG)
	DWORD 			m_dwRefCnt;	// reference count (debugging purposes only)
#endif // _DEBUG
	ExtensionList *m_pEL;		// back pointer
	CEnumAllObjectProperties *m_pObjEnum;	// ObjectProps (derzeit initialisierte)

	typedef CPropsMap CMCodeProps;
	typedef CPropsList CGenProps;
	
	CMCodeProps m_MCodeProps;	// _alle_ MCode-bezogenen Objekteigenschaften des Projektes
	CGenProps m_GenProps;		// Menge der generischen (allgemeinen) Objekteigenschaften
	CPropsCache m_PropsCache;	// _alle_ Objekteigenschaften (gecached über Idents)

	INT_PTR m_lRefONr;
	INT_PTR m_lRefObjs;

#if _TRiAS_VER < 0x0400
	CEnumAllClassProperties *m_pClsEnum;	// ClassProps
#endif // _TRiAS_VER < 0x0400

protected:
	bool FInit (void);
	HRESULT OnNewReferenceObjects (INT_PTR hObjs, INT_PTR lRefObj, bool fExternal);
	
public:
		CAllProperties (ExtensionList *pEL);
		~CAllProperties (void);

static CAllProperties *CreateInstance (ExtensionList *pEL);

// EnumerationsFunktion
	BOOL __stdcall EnumMCodesForObjProp (long lMCode, DWORD dw, vector<HOBJECTS> *pData);
	class CEnumThunk :
		public CStdThunk<CAllProperties>
	{
	public:
		CEnumThunk (CAllProperties *pThis)
			{ InitThunk(reinterpret_cast<TMFP>(CAllProperties::EnumMCodesForObjProp), pThis); }
	};

// MCodeProps verwalten
	HRESULT ResetMCodeProps() 
	{ 
		m_MCodeProps.clear(); 
		m_GenProps.clear(); 
		m_PropsCache.Clear(); 
		return S_OK; 
	}
	HRESULT FindMCodeProp(LPCSTR pcName, IObjectProperty **ppIOP = NULL);
	HRESULT AddMCodeProp(LPCSTR pcName, IObjectProperty *pIOP);
	HRESULT RemoveMCodeProp(LPCSTR pcName);
	
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);
	STDMETHOD_(ULONG, AddRef) (THIS);
	STDMETHOD_(ULONG, Release) (THIS);

// *** IObjectProps specific functions ***
	STDMETHOD(EnumObjectProps) (THIS_ IEnumObjProps **ppEnumProp);
	STDMETHOD(EnumClassProps) (THIS_ IEnumClassProps **ppEnumProp);

// Funktionen, welche gerufen werden, wenn BezugsObjekt/BezugsKlasse geändert wurde
	STDMETHOD(OnNewReferenceObject) (THIS_ INT_PTR lRefONr);
	STDMETHOD(OnNewReferenceClass) (THIS_ IEnumLONG *pEnumObjs);
	STDMETHOD(GetGroupInfo) (THIS_ LPSTR pGroupName, WORD ulLen, DWORD *pdwFlags);

	STDMETHOD(OnNewReferenceObjects) (THIS_ INT_PTR hObjs, INT_PTR lRefObj);

// *** IObjectProps2 specific functions ***
	STDMETHOD(CreateNewProp) (THIS_ LPCSTR pcName, DWORD dwFlags, LONG lONr, VARIANT vOptData, REFIID riid, LPVOID *ppIObjProp);
	STDMETHOD(DeleteProp) (THIS_ LPCSTR pcName, LONG lONr);

// *** IObjectProps3 specific functions ***
	STDMETHOD(CreateNewPropClass) (THIS_ LPCSTR pcName, DWORD dwFlags, LONG lIdent, VARIANT vOptData, REFIID riid, LPVOID *ppIObjProp);
	STDMETHOD(DeletePropClass) (THIS_ LPCSTR pcName, LONG lIdent);

// Definieren einer ObjProperty 
	bool AddPropertyFunction (LPOBJECTPROPERTY pIObjProp, LPCSTR pcGroup = NULL, INT_PTR lObjsRef = 0, bool fTestExisting = false);
	
	bool RemovePropertyFunction (LPCSTR pcName);
	bool RemoveAllObjPropertyFunctions (void);		

	HRESULT CopyObjPropsToEnum (COleExtension *pExt, INT_PTR lRefONr = 0L, INT_PTR lRefObjs = 0);

#if _TRiAS_VER < 0x0400
	bool AddPropertyFunction (LPCLASSPROPERTY pIObjProp, LPCSTR pcGroup = NULL);
	bool RemoveAllClsPropertyFunctions (void);		
	HRESULT CopyClsPropsToEnum (COleExtension *pExt, IEnumLONG *pIEnum = NULL);
#endif // _TRiAS_VER < 0x0400

	bool AddInternalObjProperties (INT_PTR lRefONr);
	bool AddInternalObjPropertiesClass (INT_PTR lRefObjs);
	bool AddInternalClsProperties (void);
	bool AddGeneralObjProperties (INT_PTR lRefONr = 0);

	void FeatureSetModified (INT_PTR lIdent) 
	{ 
		m_lRefObjs = -1L; 
		m_lRefONr = -1L; 
		if (-1 != lIdent && 0 != lIdent)
			m_PropsCache.RemoveProps(lIdent);		// einen konkreten freigeben
		else
			m_PropsCache.Clear();					// alles freigeben
	}

	HRESULT CreateNewInternalProp (LPCSTR pcName, DWORD dwFlags, LONG lONr, VARIANT vOptData, REFIID riid, LPVOID *ppIObjProp);
	HRESULT CreateNewInternalPropIdent (LPCSTR pcName, DWORD dwFlags, LONG lIdent, VARIANT vOptData, REFIID riid, LPVOID *ppIObjProp);

// XML basierte Objekteigenschaften
#if defined(_USE_XML_GEOCOMPONENTS)
	HRESULT LoadXMLObjectProperties(INT_PTR lRefObjs);
	HRESULT LoadXMLObjectPropertiesFromThisGroup(xml::IXMLDOMNode *pINode, INT_PTR lRefObjs);
	HRESULT LoadXMLObjectProperty(BSTR bstrRsc, IObjectProperty **ppIObjProp);
#endif // defined(_USE_XML_GEOCOMPONENTS)
};

#endif // _ALLOPROP_HXX

