// ExportDialogFenster -- Memberfunktionen
// File: EXPDLG.CXX

#include "triaspre.hxx"

#include <impexp.hxx>

#include "expdlg.hxx"

extern pWindow CurrActDirisW;

// Memberfunktionen -----------------------------------------------------------
// Konstruktor 
#pragma warning (disable: 4355)

ExportDlg :: ExportDlg (pWindow pW)
	   : DialogWindow (pW, DIRISEXPORT),
	     OKButton (this, IDOK),                             // PushButtons
	     CancelButton (this, IDCANCEL),
	     HelpButton (this, IDB_EXPORTHELP),
	     TransformButton (this, IDB_SCALING),
	     OverWriteRButton (this, IDR_EXPORTOVERWRITE),      // RadioButtons
	     ConcatinateRButton (this, IDR_EXPORTCONCAT),
	     LBFiles (this, IDL_EXPORTFILES, IDT_EXPORTDIR),    // ListBox
	     CBFormats (this, IDC_EXPORTFORMAT),                // ComboBox
	     CBSights (this, IDC_EXPORTSIGHTS),
	     CBPosition (this, IDR_EXPORTPOSITION),
	     SLEFileName (this, IDE_EXPORTNAME)                 // EditControl
{
// ComboBox (Sichten) initialisieren
char **Names = (char **)new char *[MAXSIGHTS];

	if (Names == 0) return;

short numSights = MAXSIGHTS;
char ActSight[SIGHTMENUITEM+1];

ErrCode EC = ((IrisWind *)CurrActDirisW) -> DBO().GetSightNames ((char **)Names, numSights);	

	if (EC != EC_OKAY)
		return;
	((IrisWind *)CurrActDirisW) -> DBO().GetActiveSightName (ActSight, SIGHTMENUITEM+1);

short ActIndex = 0;

	if (ActSight[0] == '\0') ActIndex = -1;
	else {
		for (register short i = 0; i < numSights; i++) {
			if (!strcmp (Names[i], ActSight)) 
				ActIndex = i;		// aktuelle Sicht voreinstellen
			CBSights.AddString (Names[i]);
			DELETE (Names[i]);
		}
	}
	CBSights.ChangeCurrentIndex (ActIndex);	// erster Eintrag aktiv
	DELETE (Names);

// liest Formate ein, setzt aktuelles Format
	if (ReadFormats () != EC_OKAY) 
		return;         // InitialisierungsFehler

// DateiListbox etc. initialisieren
	if (_numFilters == 0) {
	const char *Ext = ResString (IDS_ALLFILES, 5);		// alle Dateien anzeigen

		LBFiles.List (Ext, FLB_SubDir | FLB_Drives);
		SLEFileName.SetText (Ext);
	} else {
		LBFiles.List (_FilterInfo[0].FilterExt, FLB_SubDir | FLB_Drives);
		SLEFileName.SetText (_FilterInfo[0].FilterExt);
	}
// RadioButtons initialisieren
	_OverWriteFlag = OMOverwrite;
	OverWriteRButton.SetState (TRUE);
	ConcatinateRButton.SetState (FALSE);
	CBPosition.SetChecked (_iPos = FALSE);
}


#pragma warning (default: 4355)

// FilterNamen aus DIRIS.INI einlesen -----------------------------------------
ErrCode ExportDlg :: ReadFormats (void) {
ResString Params (IDS_IRISPARS, 15);
ResString Filters (IDS_FILTERS, 15);
ResString Profile (IDS_PROFILE, 15);

	_numFilters = GetPrivateProfileInt (Params, 
				ResString(IDS_NUMFILTERS, 15), 0, Profile);

char *FilterNamesStr;

	if (_numFilters > 0) {
	// wenn Systemfarben gegeben sind
		FilterNamesStr = new char [_numFilters*81+1];
		_FilterInfo = new FILTERINFO [_numFilters];

		if (FilterNamesStr == NULL || _FilterInfo == NULL) 
			return (ErrCode)db_error (EC_NOMEMORY, RC_ctExportDlg);

		GetPrivateProfileString (Filters, NULL, "", FilterNamesStr, 
						  _numFilters*81+1, Profile);
		_FilterInfo[0].FilterName = FilterNamesStr;

	int len = 0;
	int i;

		for (i = 1; i < _numFilters; i++) 
			_FilterInfo[i].FilterName = 
			    &FilterNamesStr[len += strlen(_FilterInfo[i-1].FilterName)+1];
		for (i = 0; i < _numFilters; i++) {
		// FilterBeschreibung aus ProfileDatei einlesen
		FILTERINFO *pFI = &_FilterInfo[i];

			pFI -> DLLName = new char [81];
			if (pFI  -> DLLName == NULL)
				return (ErrCode)db_error (EC_NOMEMORY, RC_ctExportDlg);
			GetPrivateProfileString (Filters, 
						 pFI -> FilterName, 
						 "", 
						 pFI -> DLLName, 
						 81, 
						 Profile);
			CBFormats.AddString (pFI -> FilterName); // Combobox
			pFI -> DLLName = strtok (pFI -> DLLName, ", "); // FilterFormatName
			pFI -> ShortName = strtok (NULL, ", ");         // KurzName
			pFI -> FilterExt = strtok (NULL, ", ");         // Extension
		}
		CBFormats.ChangeCurrentIndex (0);               // erster Eintrag aktiv
	} else {
		OKButton.Disable();     // keine Formate - kein Export
		_FilterInfo = NULL;
	}

return EC_OKAY;
}

// Destruktor -----------------------------------------------------------------
ExportDlg :: ~ExportDlg (void) {

	if (_numFilters > 0) {
		for (register int i = 0; i < _numFilters; i++) {
			DELETE (_FilterInfo[i].DLLName);
		}
		DELETE (_FilterInfo[0].FilterName);
	}
	DELETE (_FilterInfo);
}

// Eventhandler ---------------------------------------------------------------
void ExportDlg :: ListBoxSel (ControlEvt e) {           // Click

	switch ((uint)e.GetControlID()) {
	case IDL_EXPORTFILES:           // FileListBox
		LBFiles.GetCurrentFile (_FileName);     // aktueller DateiName
		SLEFileName.SetText (_FileName);
		break;

	case IDC_EXPORTFORMAT:          // FormatComboBox
		{                       // neues Format voreinstellen
		short CurrIndex = CBFormats.GetCurrentIndex();

			LBFiles.List (_FilterInfo[CurrIndex].FilterExt, FLB_SubDir | FLB_Drives);
			SLEFileName.SetText (_FilterInfo[CurrIndex].FilterExt);
		}
		break;
	}
}


void ExportDlg :: ListBoxClk (ControlEvt e) {           // DoubleClick

	switch ((uint)e.GetControlID()) {
	case IDL_EXPORTFILES:           // FileListBox
		SelectFile();                   // Dateiexistenz berprfen
		LBFiles.ChangeCurrentIndex (0); // erster Eintrag aktiv
		break;

	case IDC_EXPORTFORMAT:          // Format-ComboBox
		// do nothing
		break;

	case IDC_EXPORTSIGHTS:		// Sichten-ComboBox
		// do nothing
		break;
	}
}


void ExportDlg :: ButtonClick (ControlEvt e) {

	switch ((uint)e.GetControlID()) {
	case IDOK:              // ok - Eingabe fertig
		SelectFile();
		break;

	case IDB_SCALING:	// ok, Skalierung noch festlegen
		SelectFile (TRUE);
		break;

	case IDCANCEL:
		*_FileName = '\0';      // DateiName nicht gegeben
		EndDlg();               // abbrechen
		break;

	case IDB_EXPORTHELP:
		break;

	case IDR_EXPORTOVERWRITE:
		_OverWriteFlag = OMOverwrite;                  // Datei neu anlegen
		OverWriteRButton.SetState (TRUE);
		ConcatinateRButton.SetState (FALSE);
		break;

	case IDR_EXPORTCONCAT:
		_OverWriteFlag = OMConcatinate;                // an Datei anh„ngen
		OverWriteRButton.SetState (FALSE);
		ConcatinateRButton.SetState (TRUE);
		break;

	case IDR_EXPORTPOSITION:	// Positionsrahmen mit ausgeben
		_iPos = CBPosition.isChecked();		// CheckBox ist Auto
		break;
	}
}

// šberprfen, ob Dateiname gltig ist ----------------------------------------
void ExportDlg :: SelectFile (Bool toTransform) {

	SLEFileName.GetText (_FileName, FULLPATHSIZE+1);
	switch (LBFiles.Validate (_FileName)) {
	case FlbFileOk:                 // Datei gefunden
	case FlbFileNotFound:           // neue Datei
		EndDlg (toTransform ? 2 : 1);	// wenn TransformationsParameter 
						// einzustellen sind, dann 2
		break;

	case FlbFileInvalid:            // ungltiger DateiName
		ErrorWindow (NULL, ResString (IDS_FILEERROR, 30), 
			     ResString (IDS_BADFILE, 120));
		break;

	case FlbFileExpanded:
		break;
	}
	SLEFileName.SetText (_FileName);
}

// Funktionen, die Resultate der ExportDlgBox liefern -------------------------
char *ExportDlg :: GetFileSpec (char *cptr, short len)
{
	if (cptr == NULL) {
		return _FileName;                       // nur Pointer liefern
	} else {
		strncpy (cptr, _FileName, len);         // Namen kopieren
		cptr[len] = '\0';
		return cptr;
	}
}

char *ExportDlg :: GetDLLName (char *cptr, short len) 
{
	if (cptr == NULL) {
		return _FilterInfo[CBFormats.GetCurrentIndex()].DLLName;
	} else {
		strncpy (cptr, _FilterInfo[CBFormats.GetCurrentIndex()].DLLName, len);
		cptr[len] = '\0';
		return cptr;
	}
}

char *ExportDlg :: GetShortName (char *cptr, short len) 
{
	if (cptr == NULL) {
		return _FilterInfo[CBFormats.GetCurrentIndex()].ShortName;
	} else {
		strncpy (cptr, _FilterInfo[CBFormats.GetCurrentIndex()].ShortName, len);
		cptr[len] = '\0';
		return cptr;
	}
}

char *ExportDlg :: GetSight (char *cptr, short len) 
{
	CBSights.GetCurrentString (CurrSight);
	if (cptr == NULL) {
		return CurrSight;
	} else {
		strncpy (cptr, CurrSight, len);
		cptr[len] = '\0';
		return cptr;
	}
}

