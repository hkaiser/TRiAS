// Memberfunktionen fuer DialogBox "Druckereinstellung" -----------------------
// File: PRNTSEL.CXX

#include "triaspre.hxx"

#include <printer.hxx>

#include "prntabrt.hxx"
#include "prntsel.hxx"

extern HelpDisplay *IrisHD;

// Konstruktor ----------------------------------------------------------------
#pragma warning (disable:4355)

PrinterSelektion :: PrinterSelektion (pWindow pW) 
		  : DialogWindow (pW, PRINTER_SELEKTION),
		    OKButton (this, IDOK),              // Buttons
		    CancelButton (this, IDCANCEL),
		    ModeButton (this, IDB_PRNTSELECT),
		    HelpButton (this, IDB_PRSHELP),
		    PrinterNames (this, IDL_PRNTSELECT) // ListBox
{
// ListBox mit den Daten aller im System installierten Drucker füllen
// Anzahl der in System installierten Drucker feststellen
// Speicher für EingabeZeile holen
char *PString = new char [801];         // Feld für DruckerNamen (80 Zeichen, 10 Drucker)

	if (PString == NULL) {
	// Fehler: kein Speicher mehr
		db_error (EC_NOMEMORY, RC_ctPrntSel);
		return;
	}

// Alle installierten Druckernamen holen
int bytes = GetProfileString ("devices", (LPSTR)NULL, "", PString, 801);
register int i, j;

	for (i = 0, j = 0; i < 10; i++, j++) {
		if (j >= bytes || PString[j] == '\0') 
			break;
		cbPrinters[i].SetDeviceName (&PString[j]);
		while (PString[j] && j < bytes) 
			j++;            // nächsten Namen suchen
	}
	numPrinters = i;

// derzeit aktiven Drucker holen
char ActPrinter[81];
int actualPrinter = -1;
char *ActPtr;
char ActivePrinter[81];

	GetProfileString ("windows", "device", "", ActPrinter, 81);
	ActPtr = strtok (ActPrinter, ",");
	if (ActPtr) {
		strncpy (ActivePrinter, ActPtr, 80);
		ActivePrinter[80] = '\0';
	}

// Printerpars vollständig laden        
	for (i = 0; i < numPrinters; i++) {
	PrinterPars *pPP = &cbPrinters[i];
	
	// PrinterPars füllen
		if (!pPP -> FillStructures()) continue;

	// Listbox füllen
		wsprintf (PString, "%s an %s", pPP -> DeviceName(), 
					       pPP -> PortName());
		PrinterNames.AddString (PString);
	
	// Vergleich,ob dieser Drucker der aktuelle ist
		if (!strcmp (pPP -> DeviceName(), ActivePrinter))
			actualPrinter = i;
	}
// Speicher wieder freigeben
	DELETE (PString);

	if (numPrinters) {
	// aktuell aktiven Drucker kennzeichnen
		PrinterNames.ChangeCurrentIndex (actualPrinter);
	} else {
	// kein Drucker installiert --> Buttons passivieren
		OKButton.Disable();
		ModeButton.Disable();
	}
}

#pragma warning (default:4355)

// Destruktor -----------------------------------------------------------------
PrinterSelektion :: ~PrinterSelektion (void)
{
}


// EventHandler ---------------------------------------------------------------
void PrinterSelektion :: ButtonClick (ControlEvt e) {

	switch ((unsigned int)e.GetControlID()) {
	case IDOK:
		{
		int actualPrinter = PrinterNames.GetCurrentIndex();
		char OutString[81];
		PrinterPars *pPP = &cbPrinters[actualPrinter];

			wsprintf (OutString, "%s,%s,%s", pPP -> DeviceName(),
							 pPP -> DriverName(),
							 pPP -> PortName());
			WriteProfileString ("windows", "device", OutString);
		
		// allen anderen sagen, daß sich was geändert hat
			SendMessage ((HWND)0xffff, WM_WININICHANGE, 0, (long)(void *)"windows");
		}
		EndDlg (1);     // raus, neue Einstellung übernehmen
		break;

	case IDCANCEL:
		EndDlg();               // raus, alles vergessen
		break;

	case IDB_PRNTSELECT:
	// DruckerTreiber aufrufen
		DeviceMode ();
		break;

	case IDB_PRSHELP:
		IrisHD -> Show (IDB_PRSHELP);
		break;
	}
}

void PrinterSelektion :: ListBoxClk (ControlEvt) 
{
	DeviceMode();           // sofort Treiber aktivieren
}


typedef void (CALLBACK *DEVICEMODEPROC)(HWND, HINSTANCE, LPCSTR, LPCSTR);

void PrinterSelektion :: DeviceMode (void) 
{
string strDriver;
int actualPrinter = PrinterNames.GetCurrentIndex();
PrinterPars *pPP = &cbPrinters[actualPrinter];

// Druckertreibernamen generieren
	strDriver = pPP -> DriverName();
	strDriver += ".DRV";

// Treiber laden und binden
HINSTANCE hLib = LoadLibrary (strDriver.c_str());

	if ((UINT)hLib >= 32) {       // ok, Treiber geladen
	DEVICEMODEPROC DevMode = (DEVICEMODEPROC)GetProcAddress (hLib, "DEVICEMODE");
	
	// TreiberParametrisierung rufen
		(*DevMode)(Handle (API_CLIENT_HWND), hLib,
			   pPP -> DeviceName(), 
			   pPP -> PortName()
		);
	// Treiber wieder freigeben
		FreeLibrary (hLib);
	} else {                // Treiber nicht auffindbar
		db_error (WC_NOLIBRARY, RC_ctPrntSel);
	}
}

