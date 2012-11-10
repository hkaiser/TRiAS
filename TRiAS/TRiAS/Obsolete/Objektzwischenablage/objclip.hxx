// Erweiterung fuer Anzeige und Verwaltung der ObjektZwischenablage
// File: OBJCLIP.HXX

#if !defined(_OBJCLIP_HXX)
#define _OBJCLIP_HXX

class ObjClipExtension : public CTriasExtension {
private:
	ObjClipboardViewer *_pViewer;	// ViewerWindow
	
protected:
// überladene virtuelle Funktion(en)
	STDMETHOD_(bool, InitExtension) (THIS_ short iMode);
	STDMETHOD_(bool, UnLoadExtension) (THIS);
	STDMETHOD_(bool, MenuInit) (THIS_ HMENU hMenu, LPARAM lParam, HWND hWnd);
	STDMETHOD_(bool, MenuCommand) (THIS_ UINT uiMenuID, HWND hWnd);
	STDMETHOD_(LRESULT, Notification) (THIS_ WPARAM wParam, LPARAM lParam);

public:
// Konstruktor / Destruktor
		ObjClipExtension (void);
		~ObjClipExtension (void);
};

#endif 	// _OBJCLIP_HXX
