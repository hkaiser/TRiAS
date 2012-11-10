// Basisklasse für ObjektKlassenEigenschaft -----------------------------------
// File CLSPROPB.HXX

#if !defined(_CLSPROPB_HXX)
#define _CLSPROPB_HXX

class CClassProperty : public IClassProperty {
private:
	DWORD m_dwRefCnt;

// IPersist-Interface, damit alle den ClsID abfragen können
	class XPersist : public IPersist {
	private:
	#if defined(_DEBUG)
		DWORD m_dwRefCnt;
	#endif // _DEBUG
		IUnknown *m_pIUnk;			// controlling Unknown
		REFCLSID m_rClsID;			// ClsID dieser PropAction

	public:
	// Konstruktor/Destruktor
			XPersist (IUnknown *pIUnk, REFCLSID rClsID);
			~XPersist (void) {}

	// *** IUnknown methods ***
		STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);
		STDMETHOD_(ULONG, AddRef) (THIS);
		STDMETHOD_(ULONG, Release) (THIS);

	// *** IPersist methods ***
		STDMETHOD(GetClassID) (THIS_ CLSID *pClsID);
	};
	XPersist m_Persist;

protected:
// nur über abgeleitete Klassen instanzieren
		CClassProperty (REFCLSID rClsID);

	bool FInit (void);

public:
	virtual ~CClassProperty (void);

// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);
	STDMETHOD_(ULONG, AddRef) (THIS);
	STDMETHOD_(ULONG, Release) (THIS);

// *** IClassProperty specific functions ***
	STDMETHOD(GetPropInfo) (THIS_ LPSTR pBuffer, WORD wLen, DWORD *pdwFlags);
	STDMETHOD(Reset)(THIS);
	STDMETHOD_(ULONG, Count)(THIS);
	STDMETHOD(HelpInfo)(THIS_ LPSTR pBuffer, ULONG ulLen, 
			    LPSTR pHelpFile, ULONG *pulHelpCtx);

	STDMETHOD(Eval)(THIS_ IEnumLONG *pEnumObj, LPSTR pBuffer, 
			ULONG ulLen, ULONG *pulWritten) ;
	STDMETHOD(Cumulation)(THIS_ LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten);
};

#endif // _CLSPROPB_HXX
