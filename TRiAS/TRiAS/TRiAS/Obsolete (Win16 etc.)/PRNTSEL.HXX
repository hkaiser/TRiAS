// Klassendefinition fuer Dialogbox "Druckereinrichtung"
// File: PRNTSEL.HXX

#if !defined(_PRNTSEL_HXX)
#define _PRNTSEL_HXX

class PrinterSelektion : public DialogWindow {
private:
	PushButton OKButton;			// Buttons
	PushButton CancelButton;
	PushButton ModeButton;
	PushButton HelpButton;
	ListBox PrinterNames;			// ListBox

	PrinterPars cbPrinters[10];		// Liste der DruckerParameter
	int numPrinters;			// Anzahl der Druckerparameter

protected:
	void ListBoxClk (ControlEvt e);
	void ButtonClick (ControlEvt e);
	void DeviceMode (void);			// Druckertreiber aktivieren

public:
// Konstruktor
		PrinterSelektion (pWindow pW);

// Destruktor
		~PrinterSelektion (void);
};


#endif // _PRNTSEL_HXX
