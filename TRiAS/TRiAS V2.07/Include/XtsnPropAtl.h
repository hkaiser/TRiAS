// Basisklasse für ObjektPropertyExtensions -----------------------------------
// File: XTSNPROPATL.H

#if !defined(_XTSNPROPATL_H)
#define _XTSNPROPATL_H

class CEnumObjectProperties;		// forward declaration
class CEnumClassProperties;
class CTriasExtension;

EXTERN_C const GUID IID_IObjectProps;

///////////////////////////////////////////////////////////////////////////////
// Liste der Installierten Objekteigenschaften
class CObjectProperties : 
	public IObjectProps
{
protected:
	string 			m_strGroup;	// Name der ObjPropGruppe
	DWORD			m_dwFlags;	// GruppenFlags

	CEnumObjectProperties *	m_pObjEnum;	// ObjectProps
	CEnumClassProperties *	m_pClsEnum;	// ObjectClassProperties

public:
		CObjectProperties (void);
		~CObjectProperties (void);

	HRESULT FinalConstruct (void);

// *** IObjectProps specific functions ***
	STDMETHOD(EnumObjectProps) (THIS_ IEnumObjProps **ppEnumProp);
	STDMETHOD(EnumClassProps) (THIS_ IEnumClassProps **ppEnumProp);

// Funktionen, welche gerufen werden, wenn BezugsObjekt/BezugsKlasse geändert wurde
	STDMETHOD(OnNewReferenceObject) (THIS_ LONG lRefONr);
	STDMETHOD(OnNewReferenceClass) (THIS_ IEnumLONG *pEnumObjs);

// Funktion, über welche besondere Informationen abgefragt werden
	STDMETHOD(GetGroupInfo)(THIS_ LPSTR pGroupName, WORD ulLen, DWORD *pdwFlags);

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

// Definieren einer ObjectClassProperty 
	ULONG AddPropertyFunction (LPCLASSPROPERTY pIClsProp);

// Freigeben einer/aller OCPFs
	bool RemoveClassPropertyFunction (ULONG ulFuncID);
	bool RemoveAllClassPropertyFunctions (void);		
};

#endif // _XTSNPROPATL_H

