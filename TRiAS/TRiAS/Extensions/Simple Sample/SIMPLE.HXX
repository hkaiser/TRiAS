// Beispielerweiterung --------------------------------------------------------
// File: SIMPLE.HXX

#if !defined(_SIMPLE_HXX)
#define _SIMPLE_HXX

class CSimpleExtension : 
	public CTriasExtension,
	// weitere Interface's
	// public IBla,
	public CComCoClass<CSimpleExtension, &CLSID_SimpleExtension>
{
public:
// Die folgende Zeile nur, wenn aggregierte Erweiterung gefordert ist
//	DECLARE_AGGREGATABLE(CSimpleExtension);

	BEGIN_COM_MAP(CSimpleExtension)
		COM_INTERFACE_ENTRY(ITriasXtension2)	// immer mit eintragen
		COM_INTERFACE_ENTRY(ITriasXtension)		// immer mit eintragen
	// weitere Interface's eintragen
	//	COM_INTERFACE_ENTRY(IBla)
	END_COM_MAP()

// Die folgende Zeile einfügen, wenn der alte Mechanismus der
// Registrierung der Erweiterungen intakt bleibt
	DECLARE_NO_REGISTRY();

		CSimpleExtension (void);

	STDMETHOD_(bool, MenuCommand) (THIS_ WPARAM wParam, HWND hWnd);
};

#endif // _SIMPLE_HXX
