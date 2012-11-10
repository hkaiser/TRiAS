// PropertyAction, welche Objekte aus RechercheFenster auswählt und zusammenstellt
// File: OBJFEAT.H

#if !defined(_OBJFEAT_H)
#define _OBJFEAT_H

class CRelScripts;
class CRunBreakPoint; 

class	CObjectFeatureScript2 :
	public IAddScriptProperty,
	public IObjectProperty
{
public:
	CObjectFeatureScript2();
	~CObjectFeatureScript2();
	
	// *** IAddScriptProperty-Methods ***
	STDMETHOD(SetName)(LPCSTR lpcstr);
	STDMETHOD(GetName)(LPSTR lpstr, UINT ui);
	STDMETHOD(SetCooky)(DWORD dwID) { m_dwID = dwID; return S_OK; }
	STDMETHOD(GetCooky)(DWORD *pdwID) {*pdwID = m_dwID; if (*pdwID) return S_OK; return S_FALSE; }
	STDMETHOD(Install)	(void);
	STDMETHOD(Uninstall)(void);
// IObjectProperty methods
	STDMETHOD(Reset)(void); // Basicwiderspiegelung
	STDMETHOD(Eval)(LONG lONr, LPSTR pBuffer, ULONG ulLen,ULONG *pulWritten);
	STDMETHOD(Cumulation)(LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten);

	STDMETHOD_(ULONG, Count)(void);
	STDMETHOD(GetPropInfo) (LPSTR pBuffer, WORD wLen, DWORD *pdwFlags);
	STDMETHOD(HelpInfo)(LPSTR pBuffer, ULONG ulLen, LPSTR pHelpFile, ULONG *pulHelpCtx);

private:
	DWORD			m_dwID;
	CebScript *		m_pScript;
	CRelScripts*	m_pRelScripts;
	CString			m_strScriptName;
	ULONG			m_ulAccessCount;
	CRunBreakPoint *m_pSuspendDeb;

	HRESULT GetObjectFeatureScripts(IObjectManagement **ppIObj);
	HRESULT GetInfoObjFeatureScripts(IStreamInfo **ppISI);

	HRESULT OnDemandDebugger (LPCSTR lpcstr, CRunBreakPoint **ppSuspendDeb);
	HRESULT RunThread(CebThread & Thread);
	void	UnLoadRelScripts(void);
	HRESULT LoadRelatedWhileRunning(void);
	HRESULT UnLoadRelatedAfterRunning(void);
	HRESULT LoadRelScripts(void);

	// Konvertierung der Objektnummer
	HRESULT ConvertLongToObject (long lObjNr, _DDocument *pIDoc, _DGeoObject **ppIObj);
	HRESULT GetDocument (_DDocument **ppIDoc);
	
	HRESULT	Run(LPCSTR lpcstrEntryName, 
				BSPARAM *pBSParams = NULL, 
				int iCountPar = 0, 
				LPVOID *lplpExtVariant = NULL, 
				ebWORD wExtVariantType = 0); 
	HRESULT SetEntryInfo(CebEntryInfo & EntryInfo, LPCSTR lpcstrEntry, BSPARAM * pPars, int iCountPar);

	//////////////////////////////////////////////////////////////////////////////////////
	// Running für Scriptabarbeitung

//	Function Cumulation() As Variant
	HRESULT RunCumulation(LPSTR pFeatureName, ULONG ulLen, ULONG *pulWritten);
//	Function Count() As Long
	HRESULT RunCount (ULONG *plCount);
//	Sub Reset()
	HRESULT RunReset();
//	Function GetProperty (Obj As GeoObject) As Variant
	HRESULT RunEvaluation(LONG lONr, LPSTR pFeatureName, ULONG ulLen, ULONG *pulWritten);
//	Sub BeginProperty()
	HRESULT RunInstall(void);
//	Sub EndProperty()
	HRESULT RunUninstall(void);
//	Function PropertyFlags() As Long
	HRESULT RunPropertyFlags (DWORD *plProps);
//	Function HelpInfo (ByRef Optional HelpFile As Variant, ByRef Optional HelpCtx As Variant) As Variant
// Function Description() As Variant
	HRESULT RunGetDescription (LPSTR pBuffer, ULONG ulLen);
//	Sub SetProperty (Obj As GeoObject, ByRef Value As Variant)

	HRESULT SetRunTimeErrorInfo(CebThread  & Thread);
	HRESULT GetScript(LPCSTR lpcstrName);
	HRESULT GetInstance(CebInstance **ppInst);
	HRESULT GetCode(ebHCODE *phCode);
	HRESULT	GetText(LPSTR *pp);
	HRESULT SetLong(CebThread & Thread, BOOL fBreak, BOOL fAuto, LPCSTR lpcstr);
	HRESULT GetStringFromVariant(CComVariant vString, LPSTR lpstr, ULONG ulLen, ULONG *pulWritten);
};

class	CObjectFeatureScript :
	public CMacroScript2,
	public CObjectFeatureScript2,
	public CComObjectRoot,
	public CComCoClass<CObjectFeatureScript, &CLSID_CreateObjectFeatureScript>
{
public:
	
	BEGIN_COM_MAP(CObjectFeatureScript)
//	COM_MAP(CMacroScript2)
		COM_INTERFACE_ENTRY(IPersistStream)
		COM_INTERFACE_ENTRY(IScriptProperty)
		COM_INTERFACE_ENTRY(IPersistStreamInit)
//	COM_MAP(CObjectFeatureScript2)
		COM_INTERFACE_ENTRY(IObjectProperty)
		COM_INTERFACE_ENTRY(IAddScriptProperty)
	END_COM_MAP()

	// *** IPersist-Method ***
	STDMETHOD(GetClassID)(LPCLSID pClsID); 

	DECLARE_REGISTRY_RESOURCEID(IDR_OBJECTFEATURESCRIPT_REG)
};

class CObjectFeatureFileScript :
	public CObjectFeatureScript2,
	public CMacroFileScript2,
	public CComObjectRoot,
	public CComCoClass<CObjectFeatureFileScript, &CLSID_CreateObjectFeatureFileScript>
{
public:
	BEGIN_COM_MAP(CObjectFeatureFileScript)
	// COM_MAP(CMacroFileScript2)
		COM_INTERFACE_ENTRY(IScriptProperty)
		COM_INTERFACE_ENTRY(IPersistFile)
//	COM_MAP(CObjectFeatureScript2)
		COM_INTERFACE_ENTRY(IObjectProperty)
		COM_INTERFACE_ENTRY(IAddScriptProperty)
	END_COM_MAP()

	// *** IPersist-Method ***
	STDMETHOD(GetClassID)(LPCLSID pClsID); 

	DECLARE_REGISTRY_RESOURCEID(IDR_OBJECTFEATUREFILESCRIPT_REG)
}; 

#endif // _OBJFEAT_H
