// Erweiterungen einiger Klassen von CommonView 2.1
// File: CVEXT.HXX

#if !defined(_CVEXT_HXX)
#define _CVEXT_HXX

#if defined(WIN16)

#if !defined(NOSTROBETOPWIND)

#include <palchevt.hxx>		// PalettenHandling

// TimerBehandlungsklassen ----------------------------------------------------
class _TRIAS03_ENTRY StrobeEvt : public Event {
public:
	uint GetStrobeID (void) { return wParam; }
};

class _TRIAS03_ENTRY Timer {
private:
	uint millisecs;
	uint timerID;

public:
		Timer (uint msecs, uint ID = 1) 
			{ millisecs = msecs; timerID = ID; }
	uint ID (void) { return timerID; }
	uint Interval (void) { return millisecs; }
};

typedef Timer * pTimer;

class _TRIAS03_ENTRY StrobeWindow : public TopAppWindow {

protected:
	long EXPORT03 Dispatch (Event);
	void EXPORT03 Activate (Event);

virtual void EXPORT03 Strobe (StrobeEvt);
virtual void EXPORT03 PaletteChange (PaletteChangeEvt);

public:
// Konstruktor
		StrobeWindow (void) {};

	bool EXPORT03 SetStrobe (pTimer);
	bool EXPORT03 CancelStrobe (pTimer);
};
#endif // NOSTROBETOPWIND

#else

typedef TopAppWindow StrobeWindow;

#endif	// WIN16

#endif // _CVEXT_HXX


