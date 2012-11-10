// Datei auswählen
// File: DATEIWAE.CXX
// J. Benkenstein, H. Kaiser

#include "abstandp.hxx"

#include <commdlg.h>    // OFN_CREATEPROMPT, OFN_OVERWRITEPROMPT ...
#include <stddlg.hxx>   // COpenDialog


#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



extern "C" HINSTANCE g_hInstance;
extern ResourceFile* pRF;



// Hook-Funktion für AbstandsWerte :: DateiAuswaehlen()
LRESULT FAR PASCAL _ABSTAND_EXPORT Init3d (HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
static AbstandsWerte* pAW = NULL;

	switch (Msg)
	{
		case WM_INITDIALOG:
			pAW = (AbstandsWerte*) (((OPENFILENAME*) lParam) -> lCustData);

			// Radio-Button initialisieren, Überschreiben wird voreingestellt
			SendDlgItemMessage (hDlg, IDR_UEBERSCHREIBEN, BM_SETCHECK, true, 0);
			SendDlgItemMessage (hDlg, IDR_ANHAENGEN, BM_SETCHECK, false, 0);
			break;

		case WM_DESTROY:	// letzte Message an uns
			pAW = NULL;		// Ausgangszustand wieder herstellen
			break;

		case WM_COMMAND:
			// wenn OKButton gedrückt wurde, wird getestet, welcher Radiobutton ausgewählt wurde;
			// ist dwResult == 1, dann Überschreiben, sonst Anhängen
			if (wParam == IDOK)
			{
			DWORD dwResult;

				dwResult = IsDlgButtonChecked (hDlg, IDR_UEBERSCHREIBEN);
				if (pAW == NULL) break;
				pAW -> SetSpForm ((bool) dwResult);
			}
			break;
	}
	return false;   // erstmal alles weiterleiten

} // Init3d




//-------------------------------------------------------------------------------------------
// Datei auswählen und festlegen, ob der Inhalt einer schon vorhandenen Datei überschrieben
// werden soll (default) oder die neuen Daten angehangen werden sollen
char* AbstandsWerte :: DateiAuswaehlen (pWindow pParentWindow)
{
ResString Spec (ResID (IDS_FILESPEC, pRF), 30);
CSaveAsDialog sad (pParentWindow, (char*) Spec.Addr());

	sad.AddFlags (OFN_HIDEREADONLY);

ResString Caption (ResID (IDS_SELECTCAPTION, pRF), 30);

// Standarddialog für Auswahl einer Datei ergänzen durch Dialog IDD_DATEI
// (zusätzlich 2 Radio-Button für Überschreiben bzw. Anhängen)
HGLOBAL hRes = LoadResource (g_hInstance, FindResource (g_hInstance,
							 MAKEINTRESOURCE (ResID (IDD_DATEI, pRF)),
							 MAKEINTRESOURCE (RT_DIALOG)));
	if (! hRes)
		return NULL;

	sad.SetTemplate (hRes);
	sad.SetCaption (Caption.Addr());
	sad.SetHookFcn ((HOOKFCN) Init3d);
	sad.SetCustomData ((DWORD)(void*) this);
	    
bool bUeber = true;	// bei einer schon existierenden Datei wird "Überschreiben" gewählt
					// und die nochmalige Nachfrage mit "ja" bestätigt
bool bRet;			// true bei "OK", false bei "Abbrechen" in DialogBox
char* pFileName = NULL;	// (evtl.) neuer Dateiname

	// nachfolgende do-Schleife wird nur dann mehrfach durchlaufen, wenn bei einer schon vorhandenen
	// Datei "Überschreiben" gewählt wurde, aber die Sicherheitsabfrage "Soll wirklich überschrieben werden?"
	// dann plötzlich mit "Nein" beantwortet wird
	do
	{
		sad.Show();
		bRet = sad.Result();	// true bei "OK", false bei "Abbrechen" in DialogBox

		//  neuen Dateinamen einlesen
		if (bRet)
		{
			DELETE_VEC (pFileName);

		int iLen = sad.GetFileNameLen();

			if (pFileName = new char [_MAX_PATH+1])
			{
				sad.GetFileName (pFileName, iLen);
			}
			else
			{
				DEX_Error (RC_dateiwae, EC_NOMEMORY);
				bRet = false;
			}

		FILE* ftemp = NULL;
	
			if (_bSpForm &&					// "Überschreiben" gewählt für eine schon existierende Datei
				(ftemp = fopen (pFileName, "r")))	// wenn Datei schon existiert, dann fopen() != NULL
			{
				if (ftemp) fclose (ftemp);
				bUeber = Ueberschreiben (pFileName);
			}
			else
				bUeber = true;
		}
	}
	while (bUeber == false);

	return bRet ? pFileName : NULL;
}


//-------------------------------------------------------------------------------------------
// Warnungs-Fenster öffnen, wenn für die Abspeicherung der Ergebnisse eine schon vorhandene
// Datei sowie der Button "Überschreiben" gewählt wurde;
// Rückgabe von true, wenn "Ja" = "Überschreiben" gewählt wurde, Rückgabe von false bei "Nein"
// bzw. nicht ausreichendem dynamischen Speicher
bool AbstandsWerte :: Ueberschreiben (char* pFileName)
{
	_ASSERTE (pFileName != NULL);

const int BuffSize = _MAX_PATH+100;
char* pcBuff = new char [BuffSize];

	if (! pcBuff)
	{
		DEX_Error (RC_dateiwae, EC_NOMEMORY);
		return false;
	}
	
ResString Capt (ResID (IDS_SELECTCAPTION, pRF), 30);
ResString Inhalt (ResID (IDS_BOXTEXT2, pRF), BuffSize);

	wsprintf (pcBuff, Inhalt.Addr(), pFileName);

MessBox mb (Capt.Addr(), pcBuff, this);

	mb.SetType (ExclamationIcon | YesNoButtons);
	if (mb.Show() == YesReply)
	{
		DELETE_VEC (pcBuff);
		return true;	// "Ja" = "Überschreiben" gewählt
	}
	
	DELETE_VEC (pcBuff);
	return false;		// "Nein" gewählt
} // Ueberschreiben
