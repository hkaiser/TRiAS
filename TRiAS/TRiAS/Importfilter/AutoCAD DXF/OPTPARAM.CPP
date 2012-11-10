/*
File: OPTPARAM.CPP
Das Modul dient zur Eingabe und Verwaltung optionaler Parameter.

Erarbeitet: J. Benkenstein                   Stand vom 21. August 1995
*/

#include "pheader.hpp"
#include <io.h>				// _filelength ()
#include <fcntl.h>			// _O_READ u.a.

// Konstanten
const ulong AvrChrPerLine = 7;			// 7 Zeichen pro Zeile durchschnittlich

// externe Funktionen
void yyerror (short);

// Params ------------------------------------------------------------------
Params :: Params (void) 
{
// KK990927
/*-------------------------------------------------
	bCloseLine = True;						// Linien wenn möglich schließen
	bAnsiiText = bImpMerkmale = True;		// Ansii-Text erzeugen, Merkmale imp.
	bDebugOutput = False;					// keine Infos in Debug-Fenster ausgeben
	pFileName = NULL;                		// "kurzer" CoverName (DOS-Name)
	m_pEbenen = NULL;						// Ebenen-Blöcke
	UnIdMKode = 0;                          // unique Ident-MK
	TextMKode  = 0;                        	// TextMerkmalskode
	XOffset = YOffset = 0.0;				// X/Y-Verschiebung
	m_bImpBlocks = True;					
	m_bImpSystemBlocks = False;
	m_bImpComment = m_bImpSymDrehWi = m_bImpTextHoehe = m_bImpTextDrehWi = True;
	m_ulComment = m_ulSymWinkel = m_ulTextWinkel = m_ulTextHoehe = (ulong) -1;
	NotImported = TextCnt = LineCnt = PointCnt = AreaCnt =  BugImported = 0;
	BildMasseOk = False;
-----------------------------------------------------------*/
	m_bOffset = False;	//	Anzeige Offset Import/Datenquelle

	Reset ();
}

Params :: ~ Params (void) 
{
	DELETE_VEC (pFileName);
	DELETE_VEC (m_pEbenen);
}

// alle Werte auf Standardwerte setzen
void Params :: Reset (void) {

	MaxLineNr = 0;
	DELETE_VEC (pFileName);
// KK990927

	bCloseLine = True;						// Linien wenn möglich schließen
	bAnsiiText = bImpMerkmale = True;		// Ansii-Text erzeugen, Merkmale imp.
	bDebugOutput = False;					// keine Infos in Debug-Fenster ausgeben
	pFileName = NULL;                		// "kurzer" CoverName (DOS-Name)
	m_pEbenen = NULL;						// Ebenen-Blöcke
	UnIdMKode = 0;                          // unique Ident-MK
	TextMKode  = 0;                        	// TextMerkmalskode
	XOffset = YOffset = 0.0;				// X/Y-Verschiebung
	m_bImpBlocks = True;					
	m_bImpSystemBlocks = False;
	m_bImpComment = m_bImpSymDrehWi = m_bImpTextHoehe = m_bImpTextDrehWi = True;
	m_ulComment = m_ulSymWinkel = m_ulTextWinkel = m_ulTextHoehe = (ulong) -1;
	NotImported = TextCnt = LineCnt = PointCnt = AreaCnt =  BugImported = 0;
	BildMasseOk = False;

}

Bool Params :: SetFileParams (char *pPath) 
{
	if (!pPath || !*pPath)
	{
		yyerror (IDS_SYSERROR);
		return False;
	}

	Bool bOk = False;		// Operation-Flag
	int fh = _open (pPath, _O_RDONLY | _O_BINARY);
	if (fh != -1)
	{
		ulong Len = _filelength (fh);
		if (Len > 0) 
		{
			MaxLineNr = Len / AvrChrPerLine;						
			bOk = _close (fh) == 0 ? True : False;
		}
		_close (fh);
	}

	if (bOk = False)
	{
		yyerror (IDS_OPENERROR);
		return False;
	}


	DELETE_VEC (pFileName);    // alten Namen löschen
	char FileName [_MAX_FNAME] = "";
	_splitpath (pPath, NULL, NULL, FileName, NULL);
	if (lstrlen (FileName) > MaxFileSize)
		*(FileName + MaxFileSize) = '\0';

	pFileName = new char [lstrlen (FileName) + 1];
	if (! pFileName) 
	{
		yyerror (IDS_NOMEMORY);
		return False;
	}
	lstrcpy (pFileName, FileName);
	strupr (pFileName);

	if (bAnsiiText)	
		OemToAnsi (pFileName, pFileName);

	return True;
}

