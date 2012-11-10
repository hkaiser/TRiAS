// Beispielerweiterung --------------------------------------------------------
// File: FEATURE.HXX

#if !defined(_FEATURE_HXX)
#define _FEATURE_HXX

#include <xtsnprop.hxx>

// Funktion, die gerufen wird, wenn zwei Objekte identisch sind. Wenn von dieser
// Funktion true geliefert wird, dann soll das 2. Objekt aus der Liste gelöscht
// werden.
class CFeatureExtension : public CTriasExtension {
private:
	CObjectProperties *m_pProps;	// Objekteigenschaften

protected:
// MenuBefehle
	bool ClassifyObjects (void);	// Objekte klassifizieren
	bool ClassifyORObjects (void);

public:
		CFeatureExtension (void);
		~CFeatureExtension (void);

// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);

// *** ITriasXtension specific functions ***
	STDMETHOD_(bool, InitExtension) (THIS_ short iMode);
	STDMETHOD_(bool, UnLoadExtension) (THIS);
	STDMETHOD_(bool, MenuInit) (THIS_ HMENU hMenu, LPARAM lParam, HWND hWnd);
	STDMETHOD_(bool, MenuCommand) (THIS_ WPARAM wParam, HWND hWnd);
	STDMETHOD_(LRESULT, Notification) (THIS_ WPARAM wParam, LPARAM lParam);
};

#endif // _FEATURE_HXX
