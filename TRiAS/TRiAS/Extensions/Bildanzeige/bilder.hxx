// BeispielErweiterungsklasse, um den gesamten Mechanismus zu dokumentieren
// File: BILDER.HXX

#if !defined(_BILDER_HXX)
#define _BILDER_HXX

// zusätzlich exportierte Funktionen
extern "C" BOOL _XTENSN_EXPORT PASCAL SHOWIMAGE (char *, char *);
extern "C" void _XTENSN_EXPORT PASCAL HIDEIMAGE (void);


class CBilderExtension : public CTriasExtension {
private:
	char *_pBDir;		// zentrales Bildverzeichnis
	char *_pLocDir;		// lokales ProjektVerzeichnis
	HWND _hWnd;		// ORFenster mit Fokus
	long _lONr;		// selektiertes Objekt
	long _lIdent;		// zugehöriger Ident
	BildWindow *_pBW;	// anzuzeigendes Bild

protected:
// überladene virtuelle Funktion(en)
	STDMETHOD_(BOOL, InitExtension) (THIS_ short iMode);
	STDMETHOD_(BOOL, UnLoadExtension) (THIS);
	STDMETHOD_(BOOL, MenuInit) (THIS_ HMENU hMenu, LPARAM lParam, HWND hWnd);
	STDMETHOD_(BOOL, MenuCommand) (THIS_ UINT uiMenuID, HWND hWnd);
	STDMETHOD_(LRESULT, Notification) (THIS_ WPARAM wParam, LPARAM lParam);

public:
// Konstruktor / Destruktor
		CBilderExtension (void);
		~CBilderExtension (void);

	char *GetImageName (void);
	char *GetImageCaption (void);
	BOOL ShowImage (char *pImageName, char *pImageCaption);
	void HideImage (void);

friend BOOL _XTENSN_EXPORT PASCAL SHOWIMAGE (char *, char *);
friend void _XTENSN_EXPORT PASCAL HIDEIMAGE (void);
};

#endif 	// _BILDER_HXX
