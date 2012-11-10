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
class CBaseObjectProperty : 
	public IObjectProperty2,
	public IPersistStream,
	public CComObjectRoot
{
private:
	bool m_fReadOnly;
	bool m_fIsDirty;

protected:
	LPFNDESTROYED m_pfnDestroy;

	ResID m_resHelpID;
	ULONG m_ulCnt;
	string m_strName;

	bool FInit (const CBaseObjectProperty &rOP);		// Helper for Clone

public:
	BEGIN_COM_MAP(CBaseObjectProperty)
		COM_INTERFACE_ENTRY(IObjectProperty)
		COM_INTERFACE_ENTRY(IPersistStream)
		COM_INTERFACE_ENTRY(IPersist)
	END_COM_MAP()

	DECLARE_NO_REGISTRY()

		CBaseObjectProperty (LPCSTR pcName, ResID resHelp, bool fReadOnly = true);
virtual	~CBaseObjectProperty (void);

// *** IPersist methods ***
	STDMETHOD(GetClassID)(THIS_ CLSID *pClsID) PURE;

// *** IPersistStream methods ***
	STDMETHOD(IsDirty)(THIS);
	STDMETHOD(Load)(THIS_ IStream *pStm);
	STDMETHOD(Save)(THIS_ IStream *pStm, BOOL fClearDirty);
	STDMETHOD(GetSizeMax)(THIS_ ULARGE_INTEGER * pcbSize);

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

	void SetDirty (bool fDirty) { m_fIsDirty = fDirty ? true : false; }
	bool GetDirty (void) { return m_fIsDirty ? true : false; }
};

#if !defined(_FORCE_LEGACY_CODE)
///////////////////////////////////////////////////////////////////////////////
// Objekteigenschaft, die Datenquelle liefert, aus der dieses Objekt stammt
class CObjPropDataSource : 
	public CBaseObjectProperty,
	public CComCoClass<CObjPropDataSource, &CLSID_ObjPropDataSource>
{
public:
	DECLARE_AGGREGATABLE(CObjPropDataSource)		// class factory

		CObjPropDataSource (void);

// *** IPersist methods ***
	STDMETHOD(GetClassID)(THIS_ CLSID *pClsID);

// *** IObjectProperty specific functions ***
	STDMETHOD(Eval)(THIS_ LONG lONr, LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten);
};
#endif // !_FORCE_LEGACY_CODE

///////////////////////////////////////////////////////////////////////////////
// Liefert Objektnummer als Zeichenkette --------------------------------------
class CObjPropONr : 
	public CBaseObjectProperty,
	public CComCoClass<CObjPropONr, &CLSID_ObjPropONr>
{
public:
	DECLARE_AGGREGATABLE(CObjPropONr)		// class factory

		CObjPropONr (void);

// *** IPersist methods ***
	STDMETHOD(GetClassID)(THIS_ CLSID *pClsID);

// *** IObjectProperty specific functions ***
	STDMETHOD(GetPropInfo) (THIS_ LPSTR pBuffer, WORD wLen, DWORD *pdwData);
	STDMETHOD(Eval)(THIS_ LONG lONr, LPSTR pBuffer, ULONG ulLen, 
			ULONG *pulWritten);
};

///////////////////////////////////////////////////////////////////////////////
// Liefert Objektnummer als Zeichenkette --------------------------------------
class CObjPropGUID : 
	public CBaseObjectProperty,
	public CComDualImpl<DSearchObjects, &IID_DSearchObjects, &LIBID_TRiASHelperLib, 
				TYPELIB_HELPER_VERSION_MAJOR, TYPELIB_HELPER_VERSION_MINOR>, 
	public CComISupportErrorInfoImpl<&IID_DSearchObjects>,
	public CComCoClass<CObjPropGUID, &CLSID_ObjPropGUID>
{
public:
	DECLARE_AGGREGATABLE(CObjPropGUID)		// class factory

	BEGIN_COM_MAP(CObjPropGUID)
		COM_INTERFACE_ENTRY(IObjectProperty2)
		COM_INTERFACE_ENTRY(DSearchObjects)
		COM_INTERFACE_ENTRY2(IDispatch, DSearchObjects)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY_CHAIN(CBaseObjectProperty)
	END_COM_MAP()

		CObjPropGUID (void);

// *** IPersist methods ***
	STDMETHOD(GetClassID)(THIS_ CLSID *pClsID);

// *** IObjectProperty specific functions ***
	STDMETHOD(GetPropInfo) (THIS_ LPSTR pBuffer, WORD wLen, DWORD *pdwData);
	STDMETHOD(Eval)(THIS_ LONG lONr, LPSTR pBuffer, ULONG ulLen, 
			ULONG *pulWritten);

// *** IObjectProperty2 specific functions ***
	STDMETHOD(Set)(THIS_ LONG lONr, LPCSTR pcBuffer);

// *** DSearchObjects specific functions
	STDMETHOD(ConsiderSearch)(THIS_ BSTR bstrToMatch, SEARCHMODE rgFlags, ULONG ulCnt);
	STDMETHOD(SearchObjects)(THIS_ BSTR bstrToMatch, SEARCHMODE rgFlags, IEnumObjectsByNumber **ppvObj);
};

///////////////////////////////////////////////////////////////////////////////
// Liefert Identifikator als Zeichenkette -------------------------------------
class CObjPropIdent : 
	public CBaseObjectProperty,
	public CComCoClass<CObjPropIdent, &CLSID_ObjPropIdent>
{
public:
	DECLARE_AGGREGATABLE(CObjPropIdent)		// class factory

		CObjPropIdent (void);

// *** IPersist methods ***
	STDMETHOD(GetClassID)(THIS_ CLSID *pClsID);

// *** IObjectProperty specific functions ***
	STDMETHOD(GetPropInfo) (THIS_ LPSTR pBuffer, WORD wLen, DWORD *pdwData);
	STDMETHOD(Eval)(THIS_ LONG lONr, LPSTR pBuffer, ULONG ulLen, 
			ULONG *pulWritten);
};

///////////////////////////////////////////////////////////////////////////////
// Liefert Objektklassenschlüssel 
class CObjPropObjClassCode : 
	public CBaseObjectProperty,
	public CComCoClass<CObjPropObjClassCode, &CLSID_ObjPropObjClassCode>
{
public:
	DECLARE_AGGREGATABLE(CObjPropObjClassCode)		// class factory

		CObjPropObjClassCode (void);

// *** IPersist methods ***
	STDMETHOD(GetClassID)(THIS_ CLSID *pClsID);

// *** IObjectProperty specific functions ***
	STDMETHOD(Eval)(THIS_ LONG lONr, LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten);
};

///////////////////////////////////////////////////////////////////////////////
// Basisklasse für Objekteigenschaft, die Objekttyp liefert -------------------
class CObjPropObjTyp : 
	public CBaseObjectProperty
{
protected:
	ULONG m_ulP;	// Punkte zählen
	ULONG m_ulL;	// Linien zählen
	ULONG m_ulF;	// Flächen zählen
	ULONG m_ulT;	// Texte zählen
	ULONG m_ulK;	// KO's zählen

public:
		CObjPropObjTyp (LPCSTR pcName, ResID resHelp);

// *** IObjectProperty specific functions ***
	STDMETHOD(Reset)(THIS);
	STDMETHOD(Cumulation)(THIS_ LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten);
};

///////////////////////////////////////////////////////////////////////////////
// Liefert Langform des Objekttyps als Zeichenkette ---------------------------
class CObjPropObjTypLong : 
	public CObjPropObjTyp,
	public CComCoClass<CObjPropObjTypLong, &CLSID_ObjPropObjTypLong>
{
public:
	DECLARE_AGGREGATABLE(CObjPropObjTypLong)		// class factory

		CObjPropObjTypLong (void);

// *** IPersist methods ***
	STDMETHOD(GetClassID)(THIS_ CLSID *pClsID);

// *** IObjectProperty specific functions ***
	STDMETHOD(Eval)(THIS_ LONG lONr, LPSTR pBuffer, ULONG ulLen, 
			ULONG *pulWritten);
};

///////////////////////////////////////////////////////////////////////////////
// Liefert Kurzform des Objekttypes als Einzelzeichen -------------------------
class CObjPropObjTypShort : 
	public CObjPropObjTyp,
	public CComCoClass<CObjPropObjTypShort, &CLSID_ObjPropObjTypShort>
{
public:
	DECLARE_AGGREGATABLE(CObjPropObjTypShort)		// class factory

		CObjPropObjTypShort (void);

// *** IPersist methods ***
	STDMETHOD(GetClassID)(THIS_ CLSID *pClsID);

// *** IObjectProperty specific functions ***
	STDMETHOD(Eval)(THIS_ LONG lONr, LPSTR pBuffer, ULONG ulLen, 
			ULONG *pulWritten);
};

///////////////////////////////////////////////////////////////////////////////
// Liefert Eingabetext als Objekteigenschaft ----------------------------------
class CObjPropQueryField : 
	public CBaseObjectProperty,
	public IInitObjPropQueryField,
	public CComCoClass<CObjPropQueryField, &CLSID_ObjPropQueryField>
{
private:
	string m_strFText;	// letzter eingegebener Text
	int m_iNumber;		// lfde. Nummer dieser OPF
	HWND m_hWnd;		// ParentFenster für Dialog
	LONG m_lCum;		// kumulativer Index

	bool m_fUseForAll;	// für alle weiteren benutzen
	bool m_fFirst;		// das erste mal seit Reset gerufen
	bool m_fInitialized;

public:
	BEGIN_COM_MAP(CObjPropQueryField)
		COM_INTERFACE_ENTRY(IInitObjPropQueryField)
		COM_INTERFACE_ENTRY_CHAIN(CBaseObjectProperty)
	END_COM_MAP()

	DECLARE_AGGREGATABLE(CObjPropQueryField)		// class factory

		CObjPropQueryField (void);

// *** IPersist methods ***
	STDMETHOD(GetClassID)(THIS_ CLSID *pClsID);

// *** IInitObjPropQueryField specific methods
	STDMETHOD(Init)(THIS_ HWND hWnd, int iNumber);

// *** IObjectProperty specific functions ***
	STDMETHOD(GetPropInfo) (THIS_ LPSTR pBuffer, WORD wLen, DWORD *pdwData);
	STDMETHOD(Reset)(THIS);
	STDMETHOD(Eval)(THIS_ LONG lONr, LPSTR pBuffer, ULONG ulLen, 
			ULONG *pulWritten);
	STDMETHOD(Cumulation)(THIS_ LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten);

// sonstige member
	void SetInitialized (bool fInit = true) { m_fInitialized = fInit; }
	void SetParent (HWND hParent) { m_hWnd = hParent; }
	void SetNumber (int iNumber) { m_iNumber = iNumber ; }
};

///////////////////////////////////////////////////////////////////////////////
// Liefert TRiAS-internes Merkmal als Objekteigenschaft (ReadWrite!) ----------
class CObjPropMerkmal : 
	public CBaseObjectProperty,
	public IInitObjPropMerkmal,
	public IPropertyTemplate,
	public IPropertyInfo,
	public IPropertyInfo2,
	public CComDualImpl<DSearchObjects, &IID_DSearchObjects, &LIBID_TRiASHelperLib, 
				TYPELIB_HELPER_VERSION_MAJOR, TYPELIB_HELPER_VERSION_MINOR>, 
	public CComISupportErrorInfoImpl<&IID_DSearchObjects>,
	public CComCoClass<CObjPropMerkmal, &CLSID_ObjPropFeature>
{
private:
	LONG m_lCum;		// kumulativer Index
	TARGETMERKMAL m_TM;	// Struktur für DEX_...

	string m_strTemplate;
	bool m_fTemplateValid;
	bool m_fInitialized;

	short m_iMLen;
	short m_iMTyp;

protected:
	bool FInit (const CObjPropMerkmal &rOP);		// helper for Clone

public:
	static HRESULT WINAPI _Choice (void *pThis, REFIID iid, void **ppvObject, DWORD dw);
	BEGIN_COM_MAP(CObjPropMerkmal)
		COM_INTERFACE_ENTRY(IInitObjPropMerkmal)
		COM_INTERFACE_ENTRY(IPropertyTemplate)
		COM_INTERFACE_ENTRY(IPropertyInfo)
		COM_INTERFACE_ENTRY(IPropertyInfo2)
		COM_INTERFACE_ENTRY_FUNC(IID_IObjectProperty2, 
					offsetofclass(IObjectProperty2, _ComMapClass),
					_Choice)
		COM_INTERFACE_ENTRY(DSearchObjects)
		COM_INTERFACE_ENTRY2(IDispatch, DSearchObjects)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY_CHAIN(CBaseObjectProperty)
	END_COM_MAP()

		CObjPropMerkmal (void);

// *** IPersist methods ***
	STDMETHOD(GetClassID)(THIS_ CLSID *pClsID);

// *** IPersistStream methods ***
	STDMETHOD(Load)(THIS_ IStream *pStm);
	STDMETHOD(Save)(THIS_ IStream *pStm, BOOL fClearDirty);
	STDMETHOD(GetSizeMax)(THIS_ ULARGE_INTEGER * pcbSize);

// *** IInitObjPropMerkmal
	STDMETHOD(Init)(THIS_ LONG lMCode, BOOL fReadOnly);

// *** IPropertyTemplate specific methods
	STDMETHOD(SetTemplate)(THIS_ LPCSTR pcBuffer);
	STDMETHOD(GetTemplate)(THIS_ LPSTR pcBuffer, ULONG ulLen, ULONG *pulWritten);
	STDMETHOD(ApplyTemplate)(THIS_ LONG lONr);

	STDMETHOD(CloneTemplate)(THIS_ IPropertyTemplate **ppITempl);

// *** IPropertyInfo specific functions ***
	STDMETHOD(SetPropInfo) (THIS_ LPCSTR pBuffer, DWORD dwFlags);
	STDMETHOD(SetHelpInfo) (THIS_ LPCSTR pBuffer, LPCSTR pHelpFile, ULONG ulHelpCtx);

// *** IPropertyInfo2 specific functions ***
	STDMETHOD(GetConfigData) (THIS_ VARIANT *pvOptData);

// *** IObjectProperty specific functions ***
	STDMETHOD(GetPropInfo) (THIS_ LPSTR pBuffer, WORD wLen, DWORD *pdwData);
	STDMETHOD(Reset)(THIS);
	STDMETHOD(Eval)(THIS_ LONG lONr, LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten);
	STDMETHOD(HelpInfo)(THIS_ LPSTR pBuffer, ULONG ulLen, LPSTR pHelpFile, ULONG *pulHelpCtx);
	STDMETHOD(Cumulation)(THIS_ LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten);

// *** IObjectProperty2 specific functions ***
	STDMETHOD(Set)(THIS_ LONG lONr, LPCSTR pcBuffer);

// *** DSearchObjects specific functions
	STDMETHOD(ConsiderSearch)(THIS_ BSTR bstrToMatch, SEARCHMODE rgFlags, ULONG ulCnt);
	STDMETHOD(SearchObjects)(THIS_ BSTR bstrToMatch, SEARCHMODE rgFlags, IEnumObjectsByNumber **ppvObj);

// other members
	void SetInitialized (bool fInit = true) { m_fInitialized = fInit ? true : false; }
	void SetTemplateValid (bool fFlag) { m_fTemplateValid = fFlag ? true : false; }

	void SetParams (short iMLen, short iMTyp) { m_iMLen = iMLen; m_iMTyp = iMTyp; }
	void GetParams (short &riMLen, short &riMTyp) { riMLen = m_iMLen; riMTyp = m_iMTyp; }

	void SetMCode (LONG lMCode) { m_TM.lMCode = lMCode; }
	LONG GetMCode (void) { return m_TM.lMCode; }

	string & GetTemplStr (void) { return m_strTemplate; }
	TARGETMERKMAL & GetTM (void) { return m_TM; }
};

#endif // _INTOPROP_HXX
