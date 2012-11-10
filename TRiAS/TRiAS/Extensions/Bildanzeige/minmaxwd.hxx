// Spezielle Klassen, die aus ChildAppWindow ein ExthildAppWindow machen
// File: MINMAXWD.HXX

#if !defined(_MINMAXWD_HXX)
#define _MINMAXWD_HXX

// Event für WM_GETMINMAXINFO
class MinMaxEvent : public Event {
public:
	void SetMinTrackingSize (Dimension);
	void SetMaxTrackingSize (Dimension);
	void SetMaxPosition (Point);
	void SetMaxSize (Dimension);
};

// Typ für WM_GETMINMAXINFO
typedef struct tagRGPT {
	int iInfo[10];
} RGPT;

// Erweiterte ChildWindowKlasse
class ExtChildAppWindow : public ChildAppWindow {
protected:
virtual void MinMaxQuery (MinMaxEvent);
	
	long Dispatch (Event);

public:
// Konstruktor
		ExtChildAppWindow (pWindow pW, DWORD dwExStyle = 0) : 
		   ChildAppWindow (pW, (char *)NULL, dwExStyle) {}
};

#endif // _MINMAXWD_HXX
