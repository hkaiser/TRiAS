// Anzeigen der DialogBox zur Auswahl des ScriptFiles fuer die naechste
// Recherche
// File: SCRIPTDLG.CXX
// Überarbeitet: J. Benkenstein		 Stand vom 12. Juli 1993

#include "pheader.h"

extern "C" {
		#include <commdlg.h>
		#include <direct.h>
		#include <dlgs.h>
		#include <ctl3d.h>	  		// 3d-Kontrols
}

#include "scripdlg.htp"			 	// Klassenselektion
#include <commonvu.hxx>

#include "komplexr.hr"			   	// zugeh. Konstanten

//  Konstanten
const short FilteSpezSize = 80;	 	// max. Länge der Filter-Spezifikation
const short FileSize = _MAX_PATH;

// lokale Variablen
static UINT iMSGListboxChange = 0;

// externe Variablen
extern "C" {
extern HINSTANCE g_hInstance;					// hInst dieser DLL
}
extern ResourceFile *pRF;

extern "C" { 
UINT FAR __export PASCAL SelScrHook (HWND hDlg, UINT iMsg, UINT wParam, LONG lParam);

char * PASCAL
InitScriptDlg (HWND hWnd) {					   // Eltern-Fenster-Handle
//  prüfe interne Parameter
	if (!pRF)
		return NULL;

	OPENFILENAME ofn;
	memset (&ofn, 0, sizeof (OPENFILENAME));

	pchar szFileName = new char [FileSize];
	if (szFileName == NULL) {
		DEX_Error (RC_InitScriptDlg, EC_NOMEMORY);
		return NULL;
	}
	*szFileName = '\0';

/*  fill in non-variant fields of OPENFILENAME struct. */
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;

//  Datei-Filter lesen
	ResString FilterSpec (ResID (IDS_DQLFILTERSPEC, pRF), FilteSpezSize);
	char Buffer [FilteSpezSize+1] = "";
	lstrcpy (Buffer, FilterSpec.Addr ());

//  Trennzeichen substituieren
	char chReplace = *(Buffer + lstrlen (Buffer) - 1);
	char *pFS = Buffer;
	while (*pFS) {
		if (*(pFS) == chReplace)
			*(pFS) = '\0';
		pFS++;
	}

	ofn.lpstrFilter = Buffer;
	ofn.nFilterIndex = 1;
	ofn.lpstrFile = szFileName;
	ofn.nMaxFile = FileSize;
	ofn.lpstrInitialDir = NULL;
	ResString Ext (ResID (IDS_DQLEXTENSION, pRF), _MAX_EXT);
	ofn.lpstrDefExt = Ext.Addr ();

//  Dialog laden
	HRSRC hFindRes;
	HGLOBAL hRes = LoadResource (g_hInstance, hFindRes = FindResource (g_hInstance,
										   MAKEINTRESOURCE (FILEOPENORD),
										   MAKEINTRESOURCE (RT_DIALOG)));
	if (!hFindRes || !hRes)
		return NULL;
	ofn.hInstance = (HINSTANCE) hRes;
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_SHAREAWARE |
				OFN_ENABLETEMPLATEHANDLE | OFN_NOCHANGEDIR | OFN_ENABLEHOOK;

	ofn.lpfnHook = SelScrHook;

//  relevante Message registr. lassen
	iMSGListboxChange = RegisterWindowMessage (LBSELCHSTRING);

/*  Use standard open dialog */
	if (!GetOpenFileName((LPOPENFILENAME) &ofn)) {
		DELETE_VEC (szFileName);
		FreeResource (hRes);
		return NULL;
	}

	FreeResource (hRes);		
	return szFileName;
}

// Die Funktion gibt die 1. Zeile (vorsaugesetzt es ist ein Kommantar, der mit
// '//' begonnen wird) des selektierten Scriptes		in ein Textfeld aus.
UINT FAR PASCAL SelScrHook (HWND hDlg, UINT iMsg, UINT wParam, LONG lParam)
{
	if (iMsg == WM_INITDIALOG && Ctl3dEnabled())
				Ctl3dSubclassDlg (hDlg, CTL3D_ALL);	 // lediglich CTL3D aktivieren

	if (iMsg == iMSGListboxChange &&	// wenn gültige Nachricht erhalten u.
		wParam == (UINT) lst1) {		// richtige ListBox aktiviert wurde
		HWND hList = GetDlgItem (hDlg, lst1);
		char FName [_MAX_FNAME + _MAX_EXT] = "";

	//  Filenamen lesen
		SendMessage (hList, LB_GETTEXT, LOWORD (lParam), (LPARAM) (LPCSTR) FName);

	//  akt. Verzeichnis lesen
		char Path [_MAX_PATH] = "";
		GetDlgItemText (hDlg, stc1, (LPSTR) Path, sizeof (Path) - 1);
		if (!Path [0] || !FName [0])	// bei Fehler
			return False;			   // im Namen zurück

	//  vollst. Dateinamen bilden
		lstrcat (Path, "\\");
		lstrcat (Path, FName);

	//  Datei Öffnen
		OFSTRUCT of;
		HFILE fh;
		if ((fh = OpenFile (Path, &of, OF_READ)) < 0)
			return False;

	//  evtl. Kommentarzeile lesen
		char Buffer [100] = "";
		_lread (fh, Buffer, sizeof (Buffer) - 1);

		char *pBuff = Buffer;
	//  Kommentar in Text-Control ausgeben
		if (Buffer [0] == '/' && Buffer [1] == '/') 
		{
			Buffer [99] = '\0';	 // Endekennung zur Sicherheit setzen
			pchar pBuffer = Buffer;
			while (*pBuffer++) 
			{
						if (*pBuffer == '\r')  // nur 1. Zeile auswerten
						{
							*pBuffer = '\0';
							break;
						}
			}   
				
		//		führende Leerzeichen Löschen							
				pBuff += 2;				 // Kommentar-Zeichen löschen
				while (*pBuff && (*pBuff == ' '))
						pBuff++;		
		} else // keine Information
		
			LoadString (g_hInstance, IDS_NOCOMMENT, Buffer, sizeof (Buffer));

		SetDlgItemText (hDlg, IDT_COMMENT, pBuff);

		_lclose (fh);   // Datei schließen

		return TRUE;
	}

	return FALSE;   // default Window-Procedure soll event nochmal auswerten
}

}	   // extern "C"
