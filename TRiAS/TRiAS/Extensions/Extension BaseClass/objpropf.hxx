// Implementation einer Objekteigenschaft über eine Funktion 'alten Typus' ----
// File: OBJPROPF.HXX

#if !defined(_OBJPROPF_HXX)
#define _OBJPROPF_HXX

class CFuncObjectProperty : public IObjectProperty {
private:
	DWORD m_dwRefCnt;		// reference count

	string m_strName;		// Name der ObjpropertyFunktion
	DWORD m_dwFlags;

	OBJPROPCALLBACK m_pPropF;	// zu rufende Funktion
	OBJPROPDELCALLBACK m_pDelF;	// evtl. Löschfunktion
	DWORD m_dwData;			// evtl. durchzureichende Daten
	bool m_fExType;			// m_dwData verwenden

	LPSTR InvokeHelper (LONG lONr, LPSTR pBuff, short iLen);

protected:
	bool FInit (void) { return true; }

public:
		CFuncObjectProperty (LPCSTR pName, OBJPROPCALLBACK pPropProc, 
					DWORD dwFlags = PROPCAPS_OBJPROPTYPE_STRING);
		CFuncObjectProperty (LPCSTR pName, OBJPROPEXCALLBACK pPropProcEx, 
					DWORD dwData, OBJPROPDELCALLBACK pDelProc = NULL, 
					DWORD dwFlags = PROPCAPS_OBJPROPTYPE_STRING);
		~CFuncObjectProperty (void);

static CFuncObjectProperty *CreateInstance (
					LPCSTR pName, OBJPROPCALLBACK pPropProc,
					DWORD dwFlags = PROPCAPS_OBJPROPTYPE_STRING);
static CFuncObjectProperty *CreateInstance (
					LPCSTR pName, OBJPROPEXCALLBACK pPropProcEx, 
					DWORD dwData, OBJPROPDELCALLBACK pDelProc = NULL,
					DWORD dwFlags = PROPCAPS_OBJPROPTYPE_STRING);
	
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);
	STDMETHOD_(ULONG, AddRef) (THIS);
	STDMETHOD_(ULONG, Release) (THIS);

// *** IObjectProperty specific functions ***
	STDMETHOD(GetPropInfo) (THIS_ LPSTR pBuffer, WORD wLen, DWORD *pdwFlags);

	STDMETHOD(Reset)(THIS);
	STDMETHOD_(ULONG, Count)(THIS);
	STDMETHOD(HelpInfo)(THIS_ LPSTR pBuffer, ULONG ulLen, 
			    LPSTR pHelpFile, ULONG *pulHelpCtx);

	STDMETHOD(Eval)(LONG lONr, LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten);
	STDMETHOD(Cumulation)(THIS_ LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten);
};

#endif // _OBJPROPF_HXX

