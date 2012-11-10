// Memberfunktionen für ExtChildAppWindow -------------------------------------
// File: MINMAXWD.CXX

#include "bilderp.hxx"

// spezielles Event, um wMsg abfragen zu können
class NakedEvent : public Event {
public:
	unsigned int Msg (void) { return wMsg; }
};

// Eigener Eventhandler und eigener Dispatcher
long _XTENSN_EXPORT ExtChildAppWindow :: Dispatch (Event e) 
{
// wenn WM_GETMINMAXINFO --> umlenken
	if (((NakedEvent &)e).Msg() == WM_GETMINMAXINFO) {
		MinMaxQuery ((MinMaxEvent &)e);
		return 0;
	}

// ansonsten normaler Dispatcher
return ChildAppWindow :: Dispatch (e);
}

// Dummy-EventHandler für MinMaxEvent etc. ------------------------------------
void _XTENSN_EXPORT ExtChildAppWindow :: MinMaxQuery (MinMaxEvent e) 
{
// wenn kein eigener MinMaxQuery-Handler definiert wird, einfach ignorieren
	Default ((Event &)e);
}

// Memberfunktionen für MinMaxEvent -------------------------------------------
void MinMaxEvent :: SetMinTrackingSize (Dimension D) 
{
// Fensterbegrenzungen für Kleinermachen setzen
	((RGPT *)lParam)->iInfo[6] = D.Width();
	((RGPT *)lParam)->iInfo[7] = D.Height();
}

void MinMaxEvent :: SetMaxTrackingSize (Dimension D) 
{
// Begrenzungen für Größermachen setzen
	((RGPT *)lParam)->iInfo[8] = D.Width();
	((RGPT *)lParam)->iInfo[9] = D.Height();
}

void MinMaxEvent :: SetMaxPosition (Point P) 
{
// Position im 'maximized' Zustand
	((RGPT *)lParam)->iInfo[4] = P.X();
	((RGPT *)lParam)->iInfo[5] = P.Y();
}

void MinMaxEvent :: SetMaxSize (Dimension D) 
{
// Größe im 'maximized' Zustand
	((RGPT *)lParam)->iInfo[2] = D.Width();
	((RGPT *)lParam)->iInfo[3] = D.Height();
}

