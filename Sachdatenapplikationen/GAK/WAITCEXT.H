/*
Datei: WAITCEXT.H

Das Modul realisiert neben dem Umschalten des Cursors in eine Sanduhr
die Ausgabe eines Textes in die Statusbar der Applikation.

Erarbeitet: J.Benkenstein				Stand vom: 4.6.1996

*/

#ifndef _WAITCEXT_H
#define _WAITCEXT_H

class CMainFrame;
class CWaitCursorExt
{
private:
	CString m_strOldText;				// alter Text

protected:
	CMainFrame *GetFrame (void);		// lese Mainframe
	void Init (const CString &strText, UINT uiOldText);

public:
	CWaitCursorExt (UINT uiResID, UINT uiOldText = 0);		// der auszugebenden Zeichenkette
	CWaitCursorExt (const char *pText, UINT uiOldText = 0);
	~CWaitCursorExt (void);				// vorigen Cursor wiederherstellen
										// alten Text wieder ausgeben	
	void Restore (void);				// restore houre glass cursor
};

#endif		// _WAITCEXT_H
	

