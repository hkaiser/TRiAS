// Routinen zur Druckerverwaltung und zum Drucken
// File: PRINTER.CXX

#include "triaspre.hxx"

#include "triasres.h"

#include <funcs03.h>
#include <rect.hxx>
#include <printer.hxx>

#include "strings.h"

#include "extmain3.hxx"
#include "prntabrt.hxx"
#include "prlayout.hxx"
#include "legdinfo.hxx"
#include "legende.hxx"
#include "prntlayt.hxx"

#if defined(_USE_LEGEND_LAYOUT)
#include "PrintLegendLayout.h"
#endif // defined(_USE_LEGEND_LAYOUT)

#if defined(_DEBUG) && !defined(WIN16)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern bool PrintEFlag;
extern bool LegendToRepaint;

bool GenerateLegendOnly = false;	// PseudoZeichnen, um genaue Legende zu haben

static short iBandNo = 0;

// lokale Funktionen ----------------------------------------------------------
bool IrisWind::PrintGraphics (char *pJobName, const ObjContainer &rOC) 
{
// Notification rumschicken und Fragen, ob gedruckt werden darf
	if (DEXN_PrintingProject())
		return false;	// jemand hat was dagegen

PrintLayout *pPL = NULL;

	if (!ShowPrintLayoutDialog(this, rOC, &pPL))
		return FALSE;

	_ASSERTE(NULL != pPL);

CEierUhr Wait1 (this, CursorPath(g_cbCursorPrint));
PrinterPars PP;
IrisPrinter p (pJobName, pPL, DBO(), m_pPD ? *m_pPD : PP);

	Wait1.Hide();
	DELETE_OBJ (pPL);					// Speicher wieder freigeben

bool fReturn = false;

	if (p.isValid()) {
	CDBOContext Ctx (this, DBO(), AspectRatio);			// Bildschirm-Einstellung verwalten
	string strDevice (p.DeviceName());					// PrinterAbortBox anzeigen

		m_pPrinter = &p;

		strDevice += ResString (IDS_ONPRINTERPORT, 16);
		strDevice += p.PortName();

		TX_TRY(p.m_pABox = new PrintAbort (this, &p, strDevice.c_str()));
		if (NULL != p.m_pABox) {
			p.m_pABox -> SetStatus (ResString (IDS_PRINTGEN, 60));
			p.m_pABox -> Show();        // AbortBox anzeigen
			App :: Exec (ExecWhileEvent);

		// Ausgabe starten
			iBandNo = 0;
			if (IsWin40() || IsWinNT())
				p.Start();			// Win95, WinNT: no banding required
			else
				p.StartBanding();

			fReturn = true;			// erfolgreich gedruckt
		} else {
			m_pPrinter = NULL;
			db_error (EC_NOMEMORY, RC_PrintGraphics);
		}
	} 

// Normalzustand wieder herstellen
	m_pPrinter = NULL;		// fertig mit Drucken

// wir sind fertig mit drucken
	if (fReturn)
		DEXN_ProjectPrinted();
	return fReturn;
}

// Eigentliche DruckRoutine ---------------------------------------------------
BOOL IrisPrinter::PrinterExpose (PrinterExposeEvt e) 
{
BOOL fReturn = CPrintBase::Expose(this, e.GetExposedArea(), Pars());

// Status anzeigen
	{
	char OutBuff[80];

		wsprintf (OutBuff, ResString(IDS_PRINTBAND, 50).Addr(), 
			  ++iBandNo, 1);
		m_pABox -> SetStatus (OutBuff); 
	}
	return fReturn;
}

// Konstruktor ----------------------------------------------------------------
IrisPrinter::IrisPrinter (char *jobName, PrintLayout *pPL, DatenBasisObjekt &rDBO, PrinterPars &rPD) 
	: BandingPrinter (jobName, &rPD), CPrintBase(pPL, rDBO), m_rPD (rPD)
{
	m_pABox = NULL;		// AbortBox - zeiger nullsetzen

// FormatierungsInfo setzen
	CPrintBase::SetDotsPerMM (Pars().GetDotsPerMM());		// ScalingParameter
	CPrintBase::SetAspect (Pars().GetAspectRatio());
}

// Destruktor -----------------------------------------------------------------
IrisPrinter::~IrisPrinter (void) 
{
	DELETE_OBJ (m_pABox);
}

// ----------------------------------------------------------------------------
// FehlerFunktion, alle Fehler sind fatal
BOOL IrisPrinter::PrinterError (PrinterErrorEvt) 
{
	return false;
}

#if defined(WIN16)
bool IrisWind::PrinterMode (void) 
{
	if (m_pPD) 
		m_pPD -> SetUp();
	return true;
}
#endif // WIN16

///////////////////////////////////////////////////////////////////////////////
// DruckLayout-Dialog anzeigen und Eingaben liefern
int IrisWind::ShowPrintLayoutDialog (PRINTLAYOUTDIALOG *pLDlg)
{
// zu verwendenden Bildausschnitt besorgen
ObjContainer OC;

	if (NULL != m_pDRO && m_pDRO -> isValidDragObject()) {
	// Ausschnitt ist selektiert: Koordinaten transformieren
	Point pt1 = ((DragRectangleObject *)m_pDRO)->LowerLeft();
	Point pt2 = ((DragRectangleObject *)m_pDRO)->UpperRight();
	Punkt pnt1 = DCtoOC (pt1);
	Punkt pnt2 = DCtoOC (pt2);

		OC = ObjContainer(pnt1, pnt2);
	} else {
	// aktuellen Bildschirmausschnitt verwenden
		OC = DBO().GetExtend();
	}

PrintLayout *pPL = NULL;
Window Wnd (pLDlg -> m_hWndParent);		// fake parent window

	if (!ShowPrintLayoutDialog((NULL != pLDlg -> m_hWndParent) ? &Wnd : this, OC, &pPL, true))
		return FALSE;

	_ASSERTE(NULL != pPL);

// Resultat liefern
BOOL fResult = pPL -> RetrieveLayout (pLDlg -> m_pLayout);
	
	DELETE_OBJ(pPL);
	return fResult;
}

BOOL IrisWind::ShowPrintLayoutDialog(Window *pW, const ObjContainer &rOC, PrintLayout **ppPL, bool fPreview)
{
// PrintLayout einstellen
CEierUhr Wait (this, CursorPath(g_cbCursorPrint));
PrinterPars PP;		// nur für alle Fälle

	if (NULL == m_pPD) {
	// DefaultPrinter einstellen, wenn dieser nicht verfügbar ist, dann wird 
	// das im DruckDialog ausgewertet
		TX_TRY(m_pPD = new PrinterPars);				// erstmal nur anlegen
		if (NULL != m_pPD) 
			m_pPD -> InitFromDefaultPrinter();
	}

// den eigentlichen Dialog zusammenbauen
bool fLegend = false;
CPrintLayoutSheet Sheet (pW);
CPrintLayoutDlg PLDlg (rOC, DBO().pCT(), m_pPD ? *m_pPD : PP, fLegend, fPreview);
WDataObject DataObj;

	PLDlg.GetDataObject (DataObj.ppi());	// Fehler nicht fatal	
	Sheet.AddPage (&PLDlg);

#if defined(_USE_LEGEND_LAYOUT)
CPrintLegendLayoutDlg LegDlg (m_pPD ? *m_pPD : PP, fLegend);

	Sheet.AddPage (&LegDlg);
#endif // defined(_USE_LEGEND_LAYOUT)

string strKey (g_cbDocSubKey);
WTRiASProject Prj;

	DBO().GetTRiASProject (Prj.ppi());		// Fehler ignorieren

	strKey += string(g_cbDel) + g_cbPrintLayout;
	Sheet.LoadPages (DataObj, g_cbDocKey, strKey.c_str(), Prj);	// zusätzliche Pages aus Registry laden

	Wait.Hide();
	Sheet.Show(Centre);

int fResult = Sheet.Result();

	CoFreeUnusedLibraries();			// DLL's wieder freigeben
	if (0 == fResult || IDCANCEL == fResult) 
		return FALSE;			// abgebrochen

// Drucken beginnen
PrintLayout *pPL = PLDlg.GetLayout();

	if (NULL == pPL) 
		return FALSE;

	PLDlg.SaveEntries();				// letzte Einträge speichern
#if defined(_USE_LEGEND_LAYOUT)
	LegDlg.SaveEntries();
#endif // defined(_USE_LEGEND_LAYOUT)

	if (IDOK == fResult) {
		if (NULL != ppPL)
			*ppPL = pPL;				// Ergebnis liefern
		return TRUE;
	}

	DELETE_OBJ(pPL);
	return FALSE;
}


