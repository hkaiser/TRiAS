// Interne Objekteigenschaften ------------------------------------------------
// File: INTOPROP.HXX

#if !defined(_INTOPROP_HXX)
#define _INTOPROP_HXX

#if !defined(_LPFNDESTROY_DEFINED)
#define _LPFNDESTROY_DEFINED
// Type for an object-destroyed callback
typedef void (FAR PASCAL *LPFNDESTROYED)(void);

#endif // _LPFNDESTROY_DEFINED

///////////////////////////////////////////////////////////////////////////////
// Basisklasse für eine Objekteigenschaft -------------------------------------
class CBaseObjectProperty : public IObjectProperty2 {
private:
	DWORD m_dwRefCnt;
	bool m_fReadOnly;

protected:
	LPFNDESTROYED m_pfnDestroy;

	ResID m_resHelpID;
	ULONG m_ulCnt;
	string m_strName;

public:
		CBaseObjectProperty (LPFNDESTROYED pfn, LPCSTR pcName, ResID resHelp, bool fReadOnly = true);
	virtual	~CBaseObjectProperty (void);

// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);
	STDMETHOD_(ULONG, AddRef) (THIS);
	STDMETHOD_(ULONG, Release) (THIS);

// *** IObjectProperty specific functions ***
	STDMETHOD(GetPropInfo) (THIS_ LPSTR pBuffer, WORD wLen, DWORD *pdwData);
	STDMETHOD(Reset)(THIS);
	STDMETHOD_(ULONG, Count)(THIS);
	STDMETHOD(HelpInfo)(THIS_ LPSTR pBuffer, ULONG ulLen, 
			    LPSTR pHelpFile, ULONG *pulHelpCtx);
	STDMETHOD(Cumulation)(THIS_ LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten);

	STDMETHOD(Eval)(THIS_ LONG lONr, LPSTR pBuffer, ULONG ulLen, 
			ULONG *pulWritten) PURE;

// *** IObjectProperty2 specific functions ***
	STDMETHOD(Set)(THIS_ LONG lONr, LPCSTR pcBuffer);

// sonstige Member
	void SetRO (bool fRO) { m_fReadOnly = fRO ? true : false; }
	bool GetRO (void) { return m_fReadOnly; }

	void SetName (LPCSTR pcName) { if (NULL != pcName) m_strName = pcName; }
	LPCSTR GetName (void) { return m_strName.c_str(); }
	string &GetNameStr (void) { return m_strName; }

	bool HasDeleteFcn (void) { return (NULL != m_pfnDestroy); }
};

///////////////////////////////////////////////////////////////////////////////
// Liefert Objektnummer als Zeichenkette --------------------------------------
class CObjPropONr : public CBaseObjectProperty {
public:
		CObjPropONr (LPFNDESTROYED pfn);

// *** IObjectProperty specific functions ***
	STDMETHOD(Eval)(THIS_ LONG lONr, LPSTR pBuffer, ULONG ulLen, 
			ULONG *pulWritten);
};

///////////////////////////////////////////////////////////////////////////////
// Liefert Identifikator als Zeichenkette -------------------------------------
class CObjPropIdent : public CBaseObjectProperty {
public:
		CObjPropIdent (LPFNDESTROYED pfn);

// *** IObjectProperty specific functions ***
	STDMETHOD(Eval)(THIS_ LONG lONr, LPSTR pBuffer, ULONG ulLen, 
			ULONG *pulWritten);
};

///////////////////////////////////////////////////////////////////////////////
// Basisklasse für Objekteigenschaft, die Objekttyp liefert -------------------
class CObjPropObjTyp : public CBaseObjectProperty {
protected:
	ULONG m_ulP;	// Punkte zählen
	ULONG m_ulL;	// Linien zählen
	ULONG m_ulF;	// Flächen zählen
	ULONG m_ulT;	// Texte zählen
	ULONG m_ulK;	// KO's zählen

public:
		CObjPropObjTyp (LPFNDESTROYED pfn, LPCSTR pcName, ResID resHelp);

// *** IObjectProperty specific functions ***
	STDMETHOD(Reset)(THIS);
	STDMETHOD(Cumulation)(THIS_ LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten);
};

///////////////////////////////////////////////////////////////////////////////
// Liefert Langform des Objekttyps als Zeichenkette ---------------------------
class CObjPropObjTypLong : public CObjPropObjTyp {
public:
		CObjPropObjTypLong (LPFNDESTROYED pfn);

// *** IObjectProperty specific functions ***
	STDMETHOD(Eval)(THIS_ LONG lONr, LPSTR pBuffer, ULONG ulLen, 
			ULONG *pulWritten);
};

///////////////////////////////////////////////////////////////////////////////
// Liefert Kurzform des Objekttypes als Einzelzeichen -------------------------
class CObjPropObjTypShort : public CObjPropObjTyp {
public:
		CObjPropObjTypShort (LPFNDESTROYED pfn);

// *** IObjectProperty specific functions ***
	STDMETHOD(Eval)(THIS_ LONG lONr, LPSTR pBuffer, ULONG ulLen, 
			ULONG *pulWritten);
};

///////////////////////////////////////////////////////////////////////////////
// Liefert Eingabetext als Objekteigenschaft ----------------------------------
class CObjPropQueryField : public CBaseObjectProperty {
private:
	string m_strFText;	// letzter eigegbener Text
	bool m_fUseForAll;	// für alle weiteren benutzen
	bool m_fFirst;		// das erste mal seit Reset gerufen
	int m_iNumber;		// lfde. Nummer dieser OPF
	HWND m_hWnd;		// ParentFenster für Dialog

	LONG m_lCum;		// kumulativer Index

	bool m_fInitialized;

// InitialisierungsInterface
	class CInitObjPropQueryField : public IInitObjPropQueryField {
	friend class CObjPropQueryField;
	private:
#if defined(_DEBUG)
		DWORD m_dwRefCnt;
#endif // _DEBUG
		IUnknown *m_pIUnk;
		CObjPropQueryField *m_pOProp;

	public:
			CInitObjPropQueryField (IUnknown *pIUnk, CObjPropQueryField *pOProp);
			~CInitObjPropQueryField (void);

	// *** IUnknown methods ***
		STDMETHOD(QueryInterface)(THIS_ REFIID riid, void **ppvObject);
		STDMETHOD_(ULONG, AddRef)(THIS);
		STDMETHOD_(ULONG, Release)(THIS);

	// *** IInitObjPropMerkmal
		STDMETHOD(Init)(THIS_ HWND hWnd, int iNumber);
	};
	CInitObjPropQueryField m_Init;

public:
		CObjPropQueryField (LPFNDESTROYED pfn);

// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);

// *** IObjectProperty specific functions ***
	STDMETHOD(Reset)(THIS);
	STDMETHOD(Eval)(THIS_ LONG lONr, LPSTR pBuffer, ULONG ulLen, 
			ULONG *pulWritten);
	STDMETHOD(Cumulation)(THIS_ LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten);

	void SetInitialized (bool fInit = true) { m_fInitialized = fInit; }
	void SetParent (HWND hParent) { m_hWnd = hParent; }
	void SetNumber (int iNumber) { m_iNumber = iNumber ; }
};

///////////////////////////////////////////////////////////////////////////////
// Liefert TRiAS-internes Merkmal als Objekteigenschaft (ReadWrite!) ----------
class CObjPropMerkmal : public CBaseObjectProperty {
private:
	LONG m_lCum;		// kumulativer Index
	TARGETMERKMAL m_TM;	// Struktur für DEX_...

	string m_strTemplate;
	bool m_fTemplateValid;
	bool m_fIsDirty;
	bool m_fInitialized;

// IPersistStream Interface
	class CPersistObjPropMerkmal : public IPersistStream {
	friend class CObjPropMerkmal;
	private:
#if defined(_DEBUG)
		DWORD m_dwRefCnt;
#endif // _DEBUG
		IUnknown *m_pIUnk;
		CObjPropMerkmal *m_pOProp;

	public:
			CPersistObjPropMerkmal (IUnknown *pIUnk, CObjPropMerkmal *pOProp);
			~CPersistObjPropMerkmal (void);

	// *** IUnknown methods ***
		STDMETHOD(QueryInterface)(THIS_ REFIID riid, void **ppvObject);
		STDMETHOD_(ULONG, AddRef)(THIS);
		STDMETHOD_(ULONG, Release)(THIS);

	// *** IPersist methods ***
		STDMETHOD(GetClassID)(THIS_ CLSID *pClsID);

	// *** IPersistStream methods ***
		STDMETHOD(IsDirty)(THIS);
		STDMETHOD(Load)(THIS_ IStream *pStm);
		STDMETHOD(Save)(THIS_ IStream *pStm, BOOL fClearDirty);
		STDMETHOD(GetSizeMax)(THIS_ ULARGE_INTEGER * pcbSize);
	};
	CPersistObjPropMerkmal m_Persist;

// InitialisierungsInterface
	class CInitObjPropMerkmal : public IInitObjPropMerkmal {
	friend class CObjPropMerkmal;
	private:
#if defined(_DEBUG)
		DWORD m_dwRefCnt;
#endif // _DEBUG
		IUnknown *m_pIUnk;
		CObjPropMerkmal *m_pOProp;

	public:
			CInitObjPropMerkmal (IUnknown *pIUnk, CObjPropMerkmal *pOProp);
			~CInitObjPropMerkmal (void);

	// *** IUnknown methods ***
		STDMETHOD(QueryInterface)(THIS_ REFIID riid, void **ppvObject);
		STDMETHOD_(ULONG, AddRef)(THIS);
		STDMETHOD_(ULONG, Release)(THIS);

	// *** IInitObjPropMerkmal
		STDMETHOD(Init)(THIS_ LONG lMCode, BOOL fReadOnly);
	};
	CInitObjPropMerkmal m_Init;

// Implementation des IPropertyTemplate-Interfaces
	class CTemplateObjPropMerkmal : public IPropertyTemplate {
	friend class CObjPropMerkmal;
	private:
#if defined(_DEBUG)
		DWORD m_dwRefCnt;
#endif // _DEBUG
		IUnknown *m_pIUnk;
		CObjPropMerkmal *m_pOProp;

	public:
			CTemplateObjPropMerkmal (IUnknown *pIUnk, CObjPropMerkmal *pOProp);
			~CTemplateObjPropMerkmal (void);

	// *** IUnknown methods ***
		STDMETHOD(QueryInterface)(THIS_ REFIID riid, void **ppvObject);
		STDMETHOD_(ULONG, AddRef)(THIS);
		STDMETHOD_(ULONG, Release)(THIS);

	// *** IPropertyTemplate specific methods
		STDMETHOD(SetTemplate)(THIS_ LPCSTR pcBuffer);
		STDMETHOD(GetTemplate)(THIS_ LPSTR pcBuffer, ULONG ulLen, ULONG *pulWritten);
		STDMETHOD(ApplyTemplate)(THIS_ LONG lONr);

		STDMETHOD(CloneTemplate)(THIS_ IPropertyTemplate **ppITempl);
	};
	CTemplateObjPropMerkmal m_Template;

// Implementation des IPropertyInfo-Interfaces
	class CObjPropMerkmalInfo : public IPropertyInfo {
	friend class CObjPropMerkmal;
	private:
#if defined(_DEBUG)
		DWORD m_dwRefCnt;
#endif // _DEBUG
		IUnknown *m_pIUnk;
		CObjPropMerkmal *m_pOProp;

	public:
			CObjPropMerkmalInfo (IUnknown *pIUnk, CObjPropMerkmal *pOProp);
			~CObjPropMerkmalInfo (void);

	// *** IUnknown methods ***
		STDMETHOD(QueryInterface)(THIS_ REFIID riid, void **ppvObject);
		STDMETHOD_(ULONG, AddRef)(THIS);
		STDMETHOD_(ULONG, Release)(THIS);

	// *** IPropertyInfo specific functions ***
		STDMETHOD(GetPropInfo) (THIS_ LPSTR pBuffer, WORD wLen, DWORD *pdwFlags);
		STDMETHOD(GetHelpInfo) (THIS_ LPSTR pBuffer, ULONG ulLen, 
					LPSTR pHelpFile, ULONG *pulHelpCtx);
		STDMETHOD(SetPropName) (THIS_ LPCSTR pBuffer);
		STDMETHOD(SetHelpInfo) (THIS_ LPCSTR pBuffer,
					LPCSTR pHelpFile, ULONG ulHelpCtx);
	};
	CObjPropMerkmalInfo m_Info;

public:
		CObjPropMerkmal (LPFNDESTROYED pfn);
		CObjPropMerkmal (const CObjPropMerkmal &rOP);
		
	void SetMCode (LONG lMCode) { m_TM.lMCode = lMCode; }
	LONG GetMCode (void) { return m_TM.lMCode; }

	void SetDirty (bool fDirty) { m_fIsDirty = fDirty ? true : false; }
	bool GetDirty (void) { return m_fIsDirty ? true : false; }

	string & GetTemplStr (void) { return m_strTemplate; }
	TARGETMERKMAL & GetTM (void) { return m_TM; }

	HRESULT SetTemplate (LPCSTR pcBuffer);
	HRESULT GetTemplate (LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten);
	HRESULT ApplyTemplate (LONG lONr);

// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);

// *** IObjectProperty specific functions ***
	STDMETHOD(GetPropInfo) (THIS_ LPSTR pBuffer, WORD wLen, DWORD *pdwData);
	STDMETHOD(Reset)(THIS);
	STDMETHOD(Eval)(THIS_ LONG lONr, LPSTR pBuffer, ULONG ulLen, 
			ULONG *pulWritten);
	STDMETHOD(HelpInfo)(THIS_ LPSTR pBuffer, ULONG ulLen, 
			    LPSTR pHelpFile, ULONG *pulHelpCtx);
	STDMETHOD(Cumulation)(THIS_ LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten);

// *** IObjectProperty2 specific functions ***
	STDMETHOD(Set)(THIS_ LONG lONr, LPCSTR pcBuffer);

	void SetInitialized (bool fInit = true) { m_fInitialized = fInit ? true : false; }
	void SetTemplateValid (bool fFlag) { m_fTemplateValid = fFlag ? true : false; }
};

#endif // _INTOPROP_HXX
