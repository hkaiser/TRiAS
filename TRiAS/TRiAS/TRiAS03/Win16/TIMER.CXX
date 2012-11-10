// Fenster, welches TimerEvents erhhalten kann --------------------------------
// File: TIMER.CXX

#include "trias03p.hxx"

#include <time.h>
#include <cvext.hxx>

#if !defined(NAKEDEVT)
#define NAKEDEVT
class NakedEvt : public Event {
public:
	uint &wmsg (void) { return wMsg; }
	uint wparam (void) { return wParam; }
};
#endif 

long EXPORT03 StrobeWindow :: Dispatch (Event e) 
{
	switch (((NakedEvt &)e).wmsg ()) {
	case WM_TIMER:
	        Strobe ((StrobeEvt &)e);
		return TRUE;

	// PalettenBehandlung
	case WM_PALETTEISCHANGING:
	case WM_PALETTECHANGED:
	case WM_QUERYNEWPALETTE:
		PaletteChange ((PaletteChangeEvt &)e);
		return TRUE;

	default:
		return TopAppWindow :: Dispatch (e);
	}
}

// EventBehandlung für TimerInterrupts ----------------------------------------
void EXPORT03 StrobeWindow :: Strobe (StrobeEvt e) 
{
	Default ((Event &)e);
}

bool EXPORT03 StrobeWindow :: SetStrobe (pTimer pt) 
{
	if (Handle())
		return SetTimer (Handle (), pt -> ID (), pt -> Interval (), 0);
	else
        	return FALSE;
}

Bool EXPORT03 StrobeWindow :: CancelStrobe (pTimer pt) 
{
	if (Handle ())
		return KillTimer (Handle (), pt -> ID ());
	else
		return FALSE;
}

// PalettenBehandlung ---------------------------------------------------------
void EXPORT03 StrobeWindow :: PaletteChange (PaletteChangeEvt e) 
{
	Default ((Event &)e);
}

void EXPORT03 StrobeWindow :: Activate (Event e) 
{
	if (((NakedEvt &)e).wparam()) {		// wenn Fenster aktiv wird
		((NakedEvt &)e).wmsg() = WM_QUERYNEWPALETTE;
		PaletteChange ((PaletteChangeEvt &)e);	// Palette behandeln
	}
	((NakedEvt &)e).wmsg() = WM_ACTIVATE;
	TopAppWindow :: Activate (e);
}
