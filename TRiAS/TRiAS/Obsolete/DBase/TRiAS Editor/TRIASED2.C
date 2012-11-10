/****************************************************************************

	PROGRAM: TriasED2.c

	PURPOSE: Beinhaltet in TriasED.c benötigte Funktionen

erstellt durch JB am 12. März 1992
Stand vom 11. Jan. 1993
****************************************************************************/

#include "pheader.h"
                                
extern HWND hEditWnd;		   /* handle to edit window */
extern HWND hwnd;			   /* handle to main window			 */
extern char szFindWhat [];

/* Selektierten Text lesen */
char *GetSelectedText (char *pszResultText, int iMaxCopy) {

	char szLineBuffer [iMaxLineLength];
	DWORD dwSel = Edit_GetSel (hEditWnd);
	int iAnfSel = LOWORD (dwSel);
	int iEndSel = HIWORD (dwSel);
	int iCopyCount;
	int iLineNr;
	register int i;
		
	iCopyCount = iEndSel - iAnfSel;
	if (iCopyCount) {

/* akt. Zeile lesen */
		for (i = 0; i < sizeof (szLineBuffer); i++)
			szLineBuffer [i] = '\0';
		iLineNr = Edit_LineFromChar (hEditWnd, -1);
		Edit_GetLine (hEditWnd, iLineNr, szLineBuffer,
					  sizeof (szLineBuffer) -1);

/* berechne Indizes für Kopieren des sel. Strings */
		iAnfSel -= Edit_LineIndex (hEditWnd, iLineNr);

/* korrigiere ggf. Anz. zu kopierender Zeichen */
		if (Edit_LineFromChar (hEditWnd, iEndSel) != iLineNr) {
			iEndSel = strlen (szLineBuffer);
			iCopyCount = iEndSel - iAnfSel;
		}

/* begrenze ggf. Anz. zu kopierender Zeichen */
		if (iCopyCount > iMaxCopy)
			iCopyCount = iMaxCopy;

/* überflüssige Zeichen überschreiben */
		memmove (szLineBuffer, szLineBuffer+iAnfSel, iCopyCount);
		szLineBuffer [iCopyCount] = '\0';	 // setze Endekennzeichen

/* in Zielstring kopieren */
		strcpy (pszResultText, szLineBuffer);
	}
	return (pszResultText);
}

char *GetFirstLine (char *pszLine) {

	char szLineBuffer [iMaxLineLength];
	int iEndSel = HIWORD (Edit_GetSel (hEditWnd));
	int iCopyCount;
	int iLineNr;
	register int i;

/* lese akt. Zeile */
	for (i = 0; i < sizeof (szLineBuffer); i++)
		 szLineBuffer [i] = '\0';
	iLineNr = Edit_LineFromChar (hEditWnd, iEndSel);
	Edit_GetLine (hEditWnd, iLineNr, szLineBuffer,
				  sizeof (szLineBuffer) -1);

/* berechne Indizes für Kopieren des sel. Strings */
   iEndSel -= Edit_LineIndex (hEditWnd, iLineNr);

/* berechne Anz. zu kopierender Zeichen */
   iCopyCount = strlen (szLineBuffer) - iEndSel;

/* überflüssige Zeichen überschreiben */
   memmove (szLineBuffer, szLineBuffer+iEndSel, iCopyCount);
   szLineBuffer [iCopyCount] = '\0';	// setze Endekennzeichen

/* in Zielstring kopieren */
   strcpy (pszLine, szLineBuffer);

   return (pszLine);
}

/* suche 1. Auftreten des KeyStrings in Line */
char *CompareStrings (char *pszLine, char *pszKeyStr) {
	return (strstr (pszLine, pszKeyStr));
}

/* Text suchen und selektieten Punkt übergeben  */
BOOL SearchText (char* pszKeyStr, POINT* pPoint) {

	register int i;
	int iEnd;
	char szLine [iMaxLineLength];
	char *pszAktPos;
	int iStart = HIWORD (Edit_GetSel (hEditWnd));
	int iLineNr = Edit_LineFromChar (hEditWnd, iStart);
	int iMaxLineNr = Edit_GetLineCount (hEditWnd);
	int iLineLength = Edit_LineLength (hEditWnd, iStart);

/*  1. (akt.) Zeile untersuchen */
	if (iLineLength) {
		for (i = 0; i < sizeof (szLine); i++)
			szLine [i] = '\0';
		GetFirstLine (szLine);
		if (pszAktPos = CompareStrings (szLine, pszKeyStr)) {
			iStart += pszAktPos - szLine;
			iEnd = iStart + strlen (pszKeyStr);
			pPoint->x = iStart; pPoint->y = iEnd;
			return (TRUE);
		}
		else
		   iStart += strlen (szLine) + 2; // einschl. 0D0A
	}
	else
		iStart += 2;

/* alle restlichen Zeilen untersuchen */
	for (++iLineNr; iLineNr < iMaxLineNr; iLineNr++) {
		if (iLineLength = Edit_LineLength (hEditWnd, iStart)) {
			for (i = 0; i < sizeof (szLine); i++)
				szLine [i] = '\0';
			Edit_GetLine (hEditWnd, iLineNr, szLine, sizeof (szLine) -1);
			if (pszAktPos = CompareStrings (szLine, pszKeyStr)) {
				iStart += pszAktPos - szLine;
				iEnd = iStart + strlen (pszKeyStr);
				pPoint->x = iStart; pPoint->y = iEnd;
				return (TRUE);
			}
			else
				iStart += iLineLength + 2;
		}
		else
			iStart += 2;
	}

/* Punkt auf ungültigen Wert setzen */
	pPoint->x = -1; pPoint->y = -1;
	return (FALSE);
}

//  TextCursor auf übergebene Position setzen
void SetTextCursor (HWND hWin, char *pCmdLine) {
	short iEnd = 1,						 /* Cursor-Position x/y */
		  iStart = 1;
	char *pStrBeg = pCmdLine;

//  Position im String suchen
	pStrBeg = strstr (pStrBeg, "-p");	  // bei Datei-Übergabe
	if (pStrBeg)  {						 // Position OK
		pStrBeg += 2;
		iStart = atoi (pStrBeg);
		if (!iStart)
			iStart = 1;
		else {  // nächsten Separator suchen
			while (*pStrBeg && *pStrBeg >= '0' && *pStrBeg <= '9')
				pStrBeg++;
			if (*pStrBeg == ',')
				iEnd = atoi (++pStrBeg);
		}
	}
						
//  korrigiere ggf. End-Pos.
	if (iEnd < iStart)
		iEnd = iStart;

//  Text markieren
	Edit_SetSel (hWin, --iStart, --iEnd);
}

//  bilde "kurzen" Dateinamen
BOOL ShortFileName (char *pFullName, char *pShortName) {
	char Ext [_MAX_EXT] = "";

	if (!pFullName || !pShortName)
		return FALSE;

	_splitpath (pFullName, NULL, NULL, pShortName, Ext);
	lstrcat (pShortName, Ext);
	strupr (pShortName);

	return TRUE;
}

//  Text des Edit-Fenster ins Clipboard kopieren
BOOL CopyTextToClipBoard (HWND hMainWnd, HWND hEditWnd) {
	DWORD dwLen = 0;
	HGLOBAL hBuffer = 0;
	void FAR*pBuffer = NULL;
	BOOL bRet = TRUE;

//  Länge des Textes bestimmen
	dwLen = Edit_GetTextLength (hEditWnd) + 1;
	if (!dwLen)		  // kein Text gefunden
		return FALSE;

//  Speicher anfordern
	hBuffer = GlobalAlloc (GMEM_MOVEABLE | GMEM_ZEROINIT | GMEM_SHARE, dwLen);
	if (!hBuffer) {
		MessageBox (hMainWnd, "Nicht genügend Speicher.", "TriasED",
						   MB_OK | MB_ICONHAND);
		return FALSE;
	}
	pBuffer = GlobalLock (hBuffer);
	if (!pBuffer) {
		GlobalFree (hBuffer);
		MessageBox (hMainWnd, "Fehler beim Verriegeln des Speichers.", "TriasED",
							  MB_OK | MB_ICONHAND);
		return FALSE;
	}

//  Editor-Text lesen
	Edit_GetText (hEditWnd, pBuffer, LOWORD (dwLen));
	GlobalUnlock (hBuffer);	 // Speicher entriegeln

//  Text kopieren
	if (bRet = OpenClipboard (hMainWnd)) {
		if (bRet = EmptyClipboard ()) {		  // Clipboard "leeren"
			hBuffer = SetClipboardData (CF_TEXT, hBuffer); // Daten kopieren
			bRet = hBuffer ? TRUE : FALSE;
			// freigeben der Daten mit CloseClipboard ()
		} else
			GlobalFree (hBuffer);	   // Speicher freigeben
	} else
		GlobalFree (hBuffer);	   // Speicher freigeben

	CloseClipboard ();		  // Clipboard schließen


//  ggf. Fehlermeldung ausgeben
	if (bRet == FALSE)
		MessageBox (hMainWnd, "Fehler beim Kopieren der Daten.", "TriasED",
							  MB_OK | MB_ICONHAND);

	return bRet;
}

//  FileNamen ins ClipBoard kopieren
BOOL CopyFileNameToClipBoard (HWND hMainWnd, char *pFileName) 
{
	DWORD dwLen = 0;
	HGLOBAL hBuffer = 0;
	char FAR *pBuffer = NULL;
	BOOL bRet = TRUE;
	
//	prüfe Parameter
	if (!pFileName)
		return FALSE;	

//  Länge des Textes bestimmen
	dwLen = lstrlen (pFileName) + 1;
	if (!dwLen)		  // kein Text gefunden
		return FALSE;

//  Speicher anfordern
	hBuffer = GlobalAlloc (GMEM_MOVEABLE | GMEM_ZEROINIT | GMEM_SHARE, dwLen);
	if (!hBuffer) {
		MessageBox (hMainWnd, "Nicht genügend Speicher.", "TriasED", MB_OK | MB_ICONHAND);
		return FALSE;
	}
	pBuffer = (char FAR *) GlobalLock (hBuffer);
	if (!pBuffer) {
		GlobalFree (hBuffer);
		MessageBox (hMainWnd, "Fehler beim Verriegeln des Speichers.", "TriasED",
							   MB_OK | MB_ICONHAND);
		return FALSE;
	}

//  Text kopieren
	lstrcpy (pBuffer, pFileName);
	GlobalUnlock (hBuffer);	 // Speicher entriegeln

//  Text kopieren
	if (bRet = OpenClipboard (hMainWnd)) {
		if (bRet = EmptyClipboard ()) {		  // Clipboard "leeren"
			hBuffer = SetClipboardData (CF_TEXT, hBuffer); // Daten kopieren
			bRet = hBuffer ? TRUE : FALSE;
			// freigeben der Daten mit CloseClipboard ()
		} else
			GlobalFree (hBuffer);	   // Speicher freigeben
	} else
		GlobalFree (hBuffer);	   // Speicher freigeben

	CloseClipboard ();		  // Clipboard schließen


//  ggf. Fehlermeldung ausgeben
	if (bRet == FALSE)
		MessageBox (hMainWnd, "Fehler beim Kopieren der Daten.", "TriasED",
							   MB_OK | MB_ICONHAND);

	return bRet;
}


UINT FAR PASCAL Init3dHook (HWND hWnd, UINT iMsg, WPARAM wParam , LPARAM lParam) {
	if (iMsg == WM_INITDIALOG && Ctl3dEnabled())
		Ctl3dSubclassDlg (hWnd, CTL3D_ALL);	 // lediglich CTL3D aktivieren

	return FALSE;
}

//	Fehlermeldung ausgeben
BOOL OutputErrorMessage (HWND hWnd, char *pErrText)
{   
	char *pFirst = NULL;
	
	if (!pErrText)
		return FALSE;
		
	pFirst = strstr (pErrText, "-e");
	if (!pFirst)
		return FALSE;
	pFirst += 2;
	if (!*pFirst)
		return FALSE;

//	Fehlermeldung ausgeben		
	MessageBeep (MB_ICONASTERISK);
	MessageBox (hWnd, pFirst, "TriasED", MB_OK | MB_ICONINFORMATION);	
}
