// PaletteBehandlung ----------------------------------------------------------
// File: PALCHEVT.HXX

#if !defined(_PALCHEVT_HXX)
#define _PALCHEVT_HXX

#if !defined(WIN32)

class PaletteChangeEvt : public Event {
public:
	enum PalAction { 
		PaletteIsChanging = WM_PALETTEISCHANGING,
		PaletteChanged = WM_PALETTECHANGED,
		QueryNewPalette = WM_QUERYNEWPALETTE,
	};

	PalAction GetPalAction (void) { return (PalAction)wMsg; }
	HWND hPalChgWnd (void) { return (HWND)wParam; }
};

#endif // WIN32

#endif // _PALCHEVT_HXX
