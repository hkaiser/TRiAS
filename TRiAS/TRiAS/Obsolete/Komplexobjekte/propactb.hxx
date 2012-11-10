// Basisklasse für IPropertyAction --------------------------------------------
// File: PROPACTB.HXX

#if !defined(_PROPACTB_HXX)
#define _PROPACTB_HXX

// Dieses Interface gehört immer zu einem Objekt mit einem IClassProperty-Interface.
// GetPropInfo liefert dabei eines der PROPCAPS_ACTION_...-Flags.
class CPropertyAction : public IPropertyAction {
private:
#if defined(_DEBUG)
	DWORD m_dwRefCnt;
#endif // WIN32
	LPUNKNOWN m_pIUnk;	// controlling Unknown

protected:
// nur über abgeleitete Klassen instanzieren
		CPropertyAction (LPUNKNOWN);	
	
	bool FInit (void);

public:
	virtual	~CPropertyAction (void);

// *** IUnknown methods
	STDMETHOD (QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj);
	STDMETHOD_ (ULONG, AddRef) (THIS);
	STDMETHOD_ (ULONG, Release) (THIS);

// *** IPropertyAction methods
	STDMETHOD (AddConfigPages) (THIS_ LPFNADDPROPSHEETPAGE lpfnAddPage, 
				    LPARAM lParam, DWORD dwFlags, UINT *puiCnt);
	STDMETHOD (BeginAction) (THIS_ IProgressIndicator *pIProgInd);
	STDMETHOD (DoAction) (THIS_ IDataObject *pEnumObj, DWORD dwReserved);
	STDMETHOD (EndAction) (THIS_ DWORD dwReserved, IDataObject **ppEnumObj);
};

#endif // _PROPACTB_HXX
