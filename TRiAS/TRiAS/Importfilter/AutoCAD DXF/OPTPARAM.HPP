/*
File: OPTPARAM.HPP
Das Modul dient zur Eingabe und Verwaltung optionaler Parameter.

Erarbeitet: J.Benkenstein                       Stand vom 21.08.1995
*/

#ifndef _OPTPARAM_HPP
#define _OPTPARAM_HPP

// Konstanten
const short MaxFileSize = _MAX_PATH;			 // max. Länge für Dateinamen
const ulong UniqueIdent = 51200000;      // Merkmalskode für unique Ident
const ulong TextObjMKode = 99999100;     // Merkmalskode für Textwert
const long StandardID = 1000;		

#ifndef NOPARAMS                                             
//  Definition aller möglichen Parameter
class Params {
public:  
	char *m_pEbenen;
	char *pFileName;			// 8 Zeichen langer Dateiname
    ulong TextMKode, UnIdMKode, MaxLineNr, TextCnt, LineCnt, PointCnt, 
	 	  AreaCnt, NotImported, BugImported,
		  m_ulTextWinkel, m_ulTextHoehe, m_ulSymWinkel, m_ulComment;
    Bool bDebugOutput, BildMasseOk, bAnsiiText, bImpMerkmale, bCloseLine,
		 m_bImpTextHoehe, m_bImpTextDrehWi, m_bImpSymDrehWi, m_bImpComment,
		 m_bImpBlocks, m_bImpSystemBlocks;
// KK991007
	Bool m_bOffset;	//	Anzeige Offset Import/Datenquelle

	double XOffset, YOffset;

    Params (void);
    ~ Params (void);

	Bool SetFileParams (char *pPath); // Dateinamen speichern 
									  // u. max. Zeilenzahl setzen		
    void Reset (void);      // alle Werte auf Standardwerte setzen

// KK991007
	char *FileName() { return pFileName; };

};
#endif // NOPARAMS
#endif  // _OPTPARAM_HPP

