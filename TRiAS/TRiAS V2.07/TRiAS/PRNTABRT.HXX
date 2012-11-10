// Klasse fuer Dialogbox "Drucken abbrechen"
// File: PRNTABRT.HXX

#if !defined(_PRNTABRT_HXX)
#define _PRNTABRT_HXX

class PrintAbort : public ModeLessDialog {
private:
	FixedText m_DeviceName;
	FixedText m_PrintStatus;
	Printer *m_P;

protected:
	void ButtonClick (ControlEvt e);
	
public:
// Konstruktor
		PrintAbort (pWindow pW, Printer *p, const char *Device);

// Memberfunktionen
	void SetStatus (const char *StatusString);
};

#endif // _PRNTABRT_HXX
