// Beispielerweiterung --------------------------------------------------------
// File: TRSABISEXT.H

#if !defined(_TRSABISEXT_H)
#define _TRSABISEXT_H

class CTRiASSabisExt : 
	public CTriasExtension,
	public CComCoClass<CTRiASSabisExt, &CLSID_TRiASSabis>
{
public:
	BEGIN_COM_MAP(CTRiASSabisExt)
		COM_INTERFACE_ENTRY(ITriasXtension2)	// immer mit eintragen
		COM_INTERFACE_ENTRY(ITriasXtension)		// immer mit eintragen
	END_COM_MAP()

// Die folgende Zeile einfügen, wenn der alte Mechanismus der
// Registrierung der Erweiterungen intakt bleibt
	DECLARE_NO_REGISTRY();
	DECLARE_NOT_AGGREGATABLE_SINGLE(CTRiASSabisExt, g_pTE);

	CTRiASSabisExt (void);
	~CTRiASSabisExt() 
	{
	}

	STDMETHOD_(BOOL, InitExtension) (THIS_ short iMode);
	STDMETHOD_(BOOL, UnLoadExtension) (THIS);

protected:

private:
};

#endif // _TRSABISEXT_H
