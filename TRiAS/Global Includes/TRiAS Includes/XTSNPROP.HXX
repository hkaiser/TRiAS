// Basisklasse für ObjektPropertyExtensions -----------------------------------
// File: XTSNPROP.HXX

#if !defined(_XTSNPROP_HXX)
#define _XTSNPROP_HXX

class CEnumObjectProperties;		// forward declaration
class CEnumClassProperties;

///////////////////////////////////////////////////////////////////////////////
// Liste der Installierten Objekteigenschaften
class CObjectProperties : public IObjectProps {
private:
	DWORD 			m_dwRefCnt;	// reference count (debugging purposes only)
	LPUNKNOWN		m_pIUnk;	// controlling unknown

	string 			m_strGroup;	// Name der ObjPropGruppe
	DWORD			m_dwFlags;	// GruppenFlags

	CEnumObjectProperties *	m_pObjEnum;	// ObjectProps
	CEnumClassProperties *	m_pClsEnum;	// ObjectClassProperties

protected:
	bool FInit (void);

public:
		CObjectProperties (LPUNKNOWN pIUnk, LPCSTR pcGroupName, DWORD dwFlags);
		~CObjectProperties (void);

static CObjectProperties *CreateInstance (LPUNKNOWN pIUnk, 
		LPCSTR pcGroupName = NULL, DWORD dwFlags = PROPCAPS_NONE);

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

// Funktion, über welche besondere Informationen abgefragt werden
	STDMETHOD(GetGroupInfo)(THIS_ LPSTR pGroupName, WORD ulLen, DWORD *pdwFlags);

	STDMETHOD(OnNewReferenceObjects) (THIS_ INT_PTR lRefObjs, INT_PTR lRefObj);

// *** diverse Helper (für Kompatibilität mit alter Version)
// Definieren einer ObjProperty 
	ULONG AddPropertyFunction (LPCSTR pFuncName, OBJPROPCALLBACK pFunc, 
					DWORD dwFlags = PROPCAPS_OBJPROPTYPE_STRING);
	ULONG AddPropertyFunctionEx (LPCSTR pFuncName, OBJPROPEXCALLBACK pFunc, 
					DWORD dwData, OBJPROPDELCALLBACK pDelF = NULL, 
					DWORD dwFlags = PROPCAPS_OBJPROPTYPE_STRING);
	ULONG AddPropertyFunction (LPOBJECTPROPERTY pIObjProp);

// Freigeben einer/aller OPFs
	bool RemovePropertyFunction (ULONG ulFuncID);
	bool RemoveAllPropertyFunctions (void);		

// Finden einer registrierten Objekteigenschaft
	HRESULT FindObjProp (char const *pName, IObjectProperty **ppIObjProp);
	
// Definieren einer ObjectClassProperty 
	ULONG AddPropertyFunction (LPCLASSPROPERTY pIClsProp);

// Freigeben einer/aller OCPFs
	bool RemoveClassPropertyFunction (ULONG ulFuncID);
	bool RemoveAllClassPropertyFunctions (void);
	
// Setzen bzw, Abfragen des Gruppenbezeichners
	LPCSTR GetGroupName() const { return m_strGroup.c_str(); }		
	void SetGroupName (LPCSTR pcGroup) { m_strGroup = pcGroup; }
};

#endif // _XTSNPROP_HXX

