/*
Datei: COVER.CXX

Basisklassen für die Erzeugung des lesbaren Arc/Info-Austausschformates.
Verwaltung der mölglichen Arc/Info-Covers.

Erarbeitet: J. Benkenstein				  Begonnen am: 3. Mai 1993
*/

#include "stdafx.h"               
/*XX*/ #include "TRiASArcImpl.h"

extern "C" {
	#include <fcntl.h>	  	// O_TEXT
	#include <io.h>		 	// setmode ()
	#include <string.h>		// strlwr ()
}

#include <attribs.hxx>		// VisInfo ...
#include <impexp.hxx>		// MF, GS ...

#include "section.hxx"		// ArcSection, LabelSection u.a.
#include "info.hxx"			// Boundaries, PassPoints u.a.
#include "geo.hxx"			// Laenge () u.a.
#include "merkmdes.hxx"		// ExtMerkmalDescriptionTree
#include "cover.hxx"		// zugehörige Header-Datei
#include "triasarc.hxx"		// ArcSize  
//XX #include "triasarc.hr"		// Resource-Defines

// KK000330
#include "e00compr.h"			// Komprimierung


// Konstanten
const char szTempFileName [] = "TEMP.$$$";		// temp. Filename
const short TabSize = 8;						// 8 Leerzeichen pro Tabulator

//  externe Variablen
extern ResourceFile *pRF;
extern ExtMerkmalDescriptionTree *pMDT;
extern long StandTextMKode;			// Merkmalskode eines Textwertes
extern Bool PolyExist;				// Labelpunkte ausgeben
extern Bool Insel;					// Insel separat exp.

// KK000330
extern nComprLevel;					// Komprimierungsart
extern char *pSourceFileName;				// gewählter AusgabeFilename
extern char *pTempFileName;				// temporärer File



//  Prototypen
ErrCode ExportLineCR (int FileHandle, pchar pLine); // Zeile in Datei mit
											// abschließendem \r\n ausgeben
ErrCode ExportLine (int FileHandle, pchar pLine); // Zeile in Datei ausgeben
ErrCode OutputWarnung (short ResourceId, long Value); // Warnung ausgeben

pchar CheckUmlaute (pchar pText);

//  globale Funktion -------------------------------------------------------
//  - deutsche Umlaute und "ß" ersetzen
//  - Zeiger auf neuen Namen liefern (muß über delete freigegeben werden)
pchar CheckUmlaute (pchar pName) {
//  Parameter prüfen
	if (!pName)
		return NULL;

	short MaxSize = lstrlen (pName);

//  Puffer für Dateinamen anfordern
	pchar pOldName = new char [MaxSize + 1];
	if (!pOldName)
		return NULL;
	lstrcpy (pOldName, pName);

//  Zielpuffer anfordern, Platz für Umlautekonvertierung
	pchar pNewName = new char [(2 * MaxSize) + 1];
	if (!pNewName) {
		DELETE_VEC (pOldName);
		return NULL;
	}
	*pNewName = '\0';

//  Zeiger merken
	pchar pNewNameSave = pNewName;
	pchar pOldNameSave = pOldName;

//  deutsche Umlaute und "ß" ersetzen
	while (*pOldName) {
		switch (*pOldName) {
			case 'á':
				*pNewName++ = 's';
				*pNewName = 's';
			break;
			case '„':
				*pNewName++ = 'a';
				*pNewName = 'e';
			break;
			case 'Ž':
				*pNewName++ = 'A';
				*pNewName = 'e';
			break;
			case '':
				*pNewName++ = 'u';
				*pNewName = 'e';
			break;
			case 'š':
				*pNewName++ = 'U';
				*pNewName = 'e';
			break;
			case '”':
				*pNewName++ = 'o';
				*pNewName = 'e';
			break;
			case '™':
				*pNewName++ = 'O';
				*pNewName = 'e';
			break;
			default:
				*pNewName = *pOldName;
		}
		pNewName++;
		pOldName++;
	}   // end while

	*pNewName = '\0';					// akt. Ende setzen
	DELETE_VEC (pOldNameSave);			   // alten Puffer löschen

	return pNewNameSave;				 // mit neuem Puffer zurück
}
//--------------------------------------------------------------------------
//---------------------------------------------------------------------------
ErrCode Cover :: TransferTempDaten (void)
{
	if (nComprLevel == E00_COMPR_NONE) 
		return EC_OKAY;

	char FName [_MAX_FNAME] = "";
	char Ext   [_MAX_EXT] = "";

	_splitpath (_of.szPathName, NULL, NULL, FName, Ext);

	char Drive [_MAX_DRIVE] = "";
    char Dir   [_MAX_DIR] = "";
	_splitpath (pSourceFileName, Drive, Dir, NULL, NULL);

	char *pNewName = NULL;
	pNewName = new char [_MAX_PATH];
	if ( !pNewName )
		return EC_OKAY;

	_makepath (pNewName, Drive, Dir, FName, Ext);



	E00ReadPtr  hReadPtr;
    E00WritePtr hWritePtr;

	char * pszInFile = _of.szPathName;
	char * pszOutFile = pNewName;
    const char  *pszLine;
    int         nStatus = 0;


    /* ----------------------------------------------------------------
     * Open files and proceed with the conversion
     * ---------------------------------------------------------------*/

    hReadPtr = E00ReadOpen(pszInFile);

    if (hReadPtr)
    {
		if (hReadPtr->bIsCompressed ) {	// Datei ist nicht komprimiert
	        CPLFree(hReadPtr);				// kein Handlungsbedarf
			hReadPtr = NULL;
			return EC_OKAY;
		}

        hWritePtr = E00WriteOpen(pszOutFile, nComprLevel);

        if (hWritePtr)
        {
            /* Read lines from input until we reach EOF 
             */
            while((pszLine = E00ReadNextLine(hReadPtr)) != NULL)
            {
                if ((nStatus = CPLGetLastErrorNo()) == 0)
                    nStatus = E00WriteNextLine(hWritePtr, pszLine);

                if (nStatus != 0)
                {
                    /* An error happened while converting the last 
                     * line... abort*/
                    break;
                }
            }

            /* Close files.
             */
            E00WriteClose(hWritePtr);
	        E00ReadClose(hReadPtr);

			DELETE_OBJ(pNewName);
			remove (pszInFile);
			return EC_OKAY;

        }
        else
            nStatus = CPLGetLastErrorNo();

        E00ReadClose(hReadPtr);

		DELETE_OBJ(pNewName);


		return EC_OKAY;
    }
    else
        nStatus = CPLGetLastErrorNo();


	DELETE_OBJ(pNewName);

	return EC_OKAY;
}

//  Cover ------------------------------------------------------------------
//  Cover erzeugen, of-Struktur füllen
ErrCode Cover :: CreateCover (OFSTRUCT &of, pchar pPath, uint ResIDext) {
	char Drive   [_MAX_DRIVE]   = "";
	char Dir	 [_MAX_DIR]	 = "";
	char FName   [_MAX_FNAME]   = "";
	char NewPath [_MAX_PATH]	= "";

	int fh;

//  Extension anhängen
	ResString Ext (ResID (ResIDext, pRF), _MAX_EXT);
	_splitpath (pPath, Drive, Dir, FName, NULL);
	_makepath (NewPath, Drive, Dir, FName, Ext.Addr ());

//  Datei öffnen
	if ((fh = OpenFile (NewPath, &of, OF_CREATE | OF_READWRITE)) < 0)
		return EC_NOFILE;

	return (ErrCode) _lclose (fh);
}

//  Datei öffnen, Datei-Handle und _RC setzen
Cover :: Cover (pchar pCoverName) {
	_RC = CreateCover (_of, pCoverName, IDS_EXPEXT);
}

//  Datei löschen
ErrCode Cover :: DeleteCover (void) {
//  prüfe interne Parameter
	if (_RC != EC_OKAY)
		return _RC;

	remove (_of.szPathName);

	return (_RC = EC_OKAY);	 
}

//  Ausgabe des Kopfes der CoverSection
ErrCode Cover :: OutputFirstData (int FileHandle) {
	if (FileHandle == 0)
		return EC_SYSERROR;
	CoverSection CS;
	return CS.OutputHead (FileHandle);
}
//-----------------------------------------------------------------------
//  Ausgabe der Zeile für den Import des Covers ins SML-Makro
//  Datei muß geöffnet und positioniert sein
ErrCode Cover :: OutputImportMakro (int FileHandle) { // _RC setzen
//  prüfe interne Parameter
	if (_RC != EC_OKAY)
		return _RC;

	char Buffer [100] = "";
	char FName [_MAX_FNAME] = "";
	ResString OutFormat (ResID (IDS_IMPORT, pRF), 80);
	_splitpath (_of.szPathName, NULL, NULL, FName, NULL);
	wsprintf (Buffer, OutFormat.Addr (), FName, FName, FName);

	return ExportLineCR (FileHandle, strlwr (Buffer));
}

//  Ausgabe :
//	  + InfoSection-Kopf
//	  + TIC- und BND-Datei
//	  + kopiere Inhalt evtl. angeg. Dateien in Main-Cover
//		Dateien müssen geöffnet und positioniert sein
//	  + InfoSectio-Ende
//	  + CoverSection-Ende
// _RC setzen
ErrCode Cover :: OutputLastData (int mfh, int fh, Section *pS) {
//  prüfe Parameter
	if (!mfh || !pS)
		return _RC = EC_SYSERROR;

	Params Par;
	Par.FileHandle = mfh;

//  prüfe interne Parameter
	if (_RC != EC_OKAY)
		return _RC;

//  InfoSection-Kopfzeile ausgeben
	InfoSection IS;
	if ((_RC = IS.OutputHead (mfh)) != EC_OKAY)
		return _RC;

//  Zeichnungsgrenzen ausgeben
	char FName [_MAX_FNAME] = "";
	_splitpath (_of.szPathName, NULL, NULL, FName, NULL);
	Boundaries Bound;
	if ((_RC = Bound.OutputHead (mfh, FName)) != EC_OKAY)
		return _RC;
	Par.pFileName = FName;
	if ((_RC = Bound.OutputFormat (&Par)) != EC_OKAY)
		return _RC;
	if ((_RC = Bound.OutputData (mfh, &pS->_Xmin, &pS->_Ymin,
									  &pS->_Xmax, &pS->_Ymax, NULL)) != EC_OKAY)
		return _RC;

//  4 Passpunkte ausgeben
	PassPoints PP;
	if ((_RC = PP.OutputHead (mfh, FName)) != EC_OKAY)
		return _RC;
	if ((_RC = PP.OutputFormat (&Par)) != EC_OKAY)
		return _RC;
	if ((_RC = PP.OutputData (mfh, &pS->_Xmin, &pS->_Ymin,
								   &pS->_Xmax, &pS->_Ymax, NULL)) != EC_OKAY)
		return _RC;

//  kopiere Inhalt evtl. geg. Datei in MainCover
	if (fh) {
		if ((_RC = FileCopy (mfh, fh)) != EC_OKAY)
			return _RC;
	}

//  InfoSection-Fußzeile ausgeben
	if ((_RC = IS.OutputFoot (mfh)) != EC_OKAY)
		return _RC;

//  CoverSection-Ende ausgeben
	CoverSection CS;
	if ((_RC = CS.OutputFoot (mfh)) != EC_OKAY)
		return _RC;

	return _RC;
}

//  Inhalt der Datei kopieren, _RC wird gesetzt
//  Dateien müssen geöffnet und positioniert sein
ErrCode Cover :: FileCopy (int fhd, int fhs) {
//  prüfe interne Parameter
	if (_RC != EC_OKAY)
		return _RC;

	if (!fhs || !fhd)
		return EC_ILLPARS;

//  Dateipuffer anlegen
	const short BufferSize = 8 * 1024;
	pchar pBuffer = new char [BufferSize];
	if (!pBuffer)
		return (_RC = EC_NOMEMORY);

	uint ReadCount = 0;
	do {
		ReadCount = _lread (fhs, pBuffer, BufferSize);
		if (_lwrite (fhd, pBuffer, ReadCount) != ReadCount)
		{                                  
			DELETE_VEC (pBuffer);   // Puffer freigeben
			return _RC = EC_NOSPACE;
		}	
	} while (ReadCount > 0);

	DELETE_VEC (pBuffer);   // Puffer freigeben

	return _RC;
}

//  TexteCover -------------------------------------------------------------
//  Ausgabe
		// + Kopf der CoverSection
		// + Kopf der TexteSection
ErrCode TexteCover :: OutputFirstData (int) {
//  TexteCover öffnen und Dateizeiger ans akt. Ende setzen
	int fh;
	if ((fh = OpenFile (_of.szPathName, &_of, OF_WRITE)) < 0)
		return _RC = EC_NOFILE;
	setmode (fh, O_TEXT);
	_llseek (fh, 0L, SEEK_END);

//  Kopf der CoverSection ausgeben
	if ((_RC = Cover :: OutputFirstData (fh)) != EC_OKAY) {
		_lclose (fh);
		return _RC;
	}

//  Beginn der TexteSection ausgeben
	if ((_RC = _TS.OutputHead (fh)) != EC_OKAY) {
		_lclose (fh);
		return _RC;
	}

	return (_RC = (ErrCode) _lclose (fh));
}

//  Ausgabe
//	  + der Ende-Zeile der TexteSection
//	  + Aufruf der korr. Funktion der Basisklasse
ErrCode TexteCover :: OutputLastData (int, int, Section *) {
//  TexteCover öffnen und Dateizeiger ans akt. Ende setzen
	int fh;
	if ((fh = OpenFile (_of.szPathName, &_of, OF_WRITE)) < 0)
		return _RC = EC_NOFILE;
	setmode (fh, O_TEXT);
	_llseek (fh, 0L, SEEK_END);

//  TexteSection-Ende ausgeben
	if ((_RC = _TS.OutputFoot (fh)) != EC_OKAY) {
		_lclose (fh);
		return _RC;
	}

//  abschließenden Infos ausgeben (TIC/BND usw.)
	if ((_RC = Cover :: OutputLastData (fh, NULL, &_TS)) != EC_OKAY) {
		_lclose (fh);
		return _RC;
	}

	return (_RC = (ErrCode) _lclose (fh));
}

//  Ausgabe der eigentlichen Daten
ErrCode TexteCover :: OutputData (GSTRUCT &GS, MFELD *pMF, char*) {
//  prüfe Parameter
	if (!pMF)
		return EC_SYSERROR;

	if (GS.GSize != 1)
		return OutputWarnung (IDS_NOTEXT, GS.ON);

//  TexteCover öffnen und Dateizeiger ans akt. Ende setzen
	int fh;
	if ((fh = OpenFile (_of.szPathName, &_of, OF_WRITE)) < 0)
		return _RC = EC_NOFILE;
	setmode (fh, O_TEXT);
	_llseek (fh, 0L, SEEK_END);

//  Text suchen
	pchar pFindText = pMF -> MText;	 // Voreinstellung ist 1. Merkmal
	while (pMF -> MCode) {
		if (pMF -> MCode == StandTextMKode) {   // wenn Kode gefunden
			pFindText = pMF -> MText;			// dessen Wert ist Textwert
			break;
		}
		pMF++;  // näschte Merkmal
	}

//  Text ggf. ausgeben
	if (!pFindText || !*pFindText)
		return (_RC = EC_OKAY);

	pchar pTextUml = CheckUmlaute (pFindText);
	if (!pTextUml) {
		_lclose (fh);
		return (_RC = EC_NOMEMORY);
	}

//	Anzahl der Tabulatoren zählen
	short sTabCnt = 0;
	for (char *pT = pTextUml; pT && *pT; pT++)
	{
		if (pT = strstr (pT, "\\t"))
			sTabCnt++;
		else
			break;
	}	

//	Text-Puffer erzeugen
	char *pText = NULL;
	short sTextLen = strlen (pTextUml) + (sTabCnt * TabSize) + 1;
	pText = new char [sTextLen];	
	if (!pText) 
	{
		DELETE_VEC (pTextUml);
		_lclose (fh);
		return (_RC = EC_NOMEMORY);
	}
	memset (pText, 0, sTextLen);		// Text init.

//	Steuerzeichen auflösen
	short sRowPos = 0;					// Zeilenposition
	char *pActPos = pText;				// absolute Zeichenposition
	for (char *pR = pTextUml; pR && *pR; pR++)
	{
		sRowPos++;						// akt. Zeilenpos. beginnt am 1. Zeichen

		if ('\\' != *pR)
		{
			*pActPos++ = *pR;			// normales Zeichen
			continue;
		}
		
		if (!*++pR)						// prüfe nächste Zeichen
			break;

	//	was für ein Steuerzeichen folgt ?
		switch (*pR)
		{
			case 'n':
			{
				*pActPos++ = '\\';		// durch einfachen Backslash ersetzen
				sRowPos = 0;			// akt. Position rücksetzen
			}
			break;
			case 't':					// Tabs auflösen
			{
				register short sL = 0 == (sRowPos % TabSize) ? 1 : TabSize - (sRowPos % TabSize) + 1;
				for (register short i = 1; i <= sL; i++)
					*pActPos++ = ' ';
				sRowPos = 0;			// akt. Position rücksetzen
			}
			break;				
			case ' ':
				*pActPos++ = ' ';		// durch einfaches Leerzeichen ersetzen
			break;
			default:					// unbekanntes Steuerzeichen überlesen
			break;				
		}
	}
	
	if ((_RC = _TS.OutputData (fh, GS, pText)) != EC_OKAY) {
		_lclose (fh);
		DELETE_VEC (pText);
		DELETE_VEC (pTextUml);
		return _RC;
	}
	DELETE_VEC (pText);
	DELETE_VEC (pTextUml);

	return (_RC = (ErrCode) _lclose (fh));
}

//  True, wenn im Cover Daten speichert wurden, sonst False
Bool TexteCover :: hasData (void) {
	return _TS.hasData ();
}

//  PointCover -------------------------------------------------------------
//  Main-Cover und PAT anlegen
PointCover :: PointCover (pchar pCoverName)
		   : Cover (pCoverName) {		   // MainCover anlegen
	if (_RC != EC_OKAY)	 //  wenn Fehler beim MainCover anlegen
		return;

//  PAT erzeugen
	_RC = CreateCover (_ofp, pCoverName, IDS_PATEXT);
}

//  alle zugeh. Coverages löschen
ErrCode PointCover :: DeleteCover (void) {
	remove (_ofp.szPathName);					   // PAT löschen
	return Cover :: DeleteCover ();				 // MainCover löschen
}

//  Ausgabe
//	  + Kopf der CoverSection
//	  + Kopf der LabelSection
//	  + Kopf unf Format der PAT
ErrCode PointCover :: OutputFirstData (int) {
//  PointCover öffnen und Dateizeiger ans akt. Ende setzen
	int fh;
	if ((fh = OpenFile (_of.szPathName, &_of, OF_WRITE)) < 0)
		return _RC = EC_NOFILE;
	setmode (fh, O_TEXT);
	_llseek (fh, 0L, SEEK_END);

//  Kopf der CoverSection ausgeben
	if ((_RC = Cover :: OutputFirstData (fh)) != EC_OKAY) {
		_lclose (fh);
		return _RC;
	}

//  LabelSection-Kopf ausgeben
	if ((_RC = _LS.OutputHead (fh)) != EC_OKAY) {
		_lclose (fh);
		return _RC;
	}
	_lclose (fh);	// LabelCover schließen

//  PAT öffnen und Dateizeiger ans akt. Ende setzen
	if ((fh = OpenFile (_ofp.szPathName, &_ofp, OF_WRITE)) < 0)
		return _RC = EC_NOFILE;
	setmode (fh, O_TEXT);
	_llseek (fh, 0L, SEEK_END);

//  Kopf der PAT ausgeben
	if ((_RC = _PAT.OutputHead (fh, _ofp.szPathName)) != EC_OKAY) {
		_lclose (fh);
		return _RC;
	}

//  Datenformat der PAT ausgeben
	Params Par;
	Par.FileHandle = fh;
	Par.pFileName = _ofp.szPathName;
	if ((_RC = _PAT.OutputFormat (&Par)) != EC_OKAY) {
		_lclose (fh);
		return _RC;
	}

	return (_RC = (ErrCode) _lclose (fh));  // PAT schließen
}

//  Ausgabe
//	  + Ende-Zeile der LabelSection
//	  + Anzahl Datensätze in PAT ausgeben
//	  + Aufruf der korr. Funktion der Basisklasse
//		dabei: PAT in MainCover kopieren
//	  + lösche PAT
ErrCode PointCover :: OutputLastData (int, int, Section *) {
//  PointCover öffnen und Dateizeiger ans akt. Ende setzen
	int fh;
	if ((fh = OpenFile (_of.szPathName, &_of, OF_WRITE)) < 0)
		return _RC = EC_NOFILE;
	setmode (fh, O_TEXT);
	_llseek (fh, 0L, SEEK_END);

//  LabelSection-Ende ausgeben
	if ((_RC = _LS.OutputFoot (fh)) != EC_OKAY) {
		_lclose (fh);
		return _RC;
	}

//  PAT öffnen und DataCount ausgeben
	int fhp;
	if ((fhp = OpenFile (_ofp.szPathName, &_ofp, OF_WRITE)) < 0) {
		_lclose (fh);
		return _RC = EC_NOFILE;
	}
	setmode (fhp, O_TEXT);
	if ((_RC = _PAT.SetDataCount (fhp, _PAT.GetCount ())) != EC_OKAY) {
		_lclose (fh);
		_lclose (fhp);
		return _RC;
	}

//  abschließenden Infos ausgeben (TIC/BND usw.)
	_lclose (fhp);			  // internen Puffer leeren
	if ((fhp = OpenFile (_ofp.szPathName, &_ofp, OF_READ)) < 0) {
		_lclose (fh);
		return _RC = EC_NOFILE;
	}
	setmode (fhp, O_TEXT);
	_llseek (fhp, 0L, SEEK_SET);

	if ((_RC = Cover :: OutputLastData (fh, fhp, &_LS)) != EC_OKAY) {
		_lclose (fhp);
		_lclose (fh);
		return _RC;
	}
	_lclose (fhp);  // PAT schließen

//  PAT löschen
	remove (_ofp.szPathName);

	return (_RC = (ErrCode) _lclose (fh));
}

//  Ausgabe der eigentlichen Daten
ErrCode PointCover :: OutputData (GSTRUCT &GS, MFELD *pMF, char *pKurzText) {
//  prüfe Parameter
	if (GS.GSize != 1)
		return OutputWarnung (IDS_NOPOINT, GS.ON);

//  PointCover öffnen und Dateizeiger ans akt. Ende setzen
	int fh;
	if ((fh = OpenFile (_of.szPathName, &_of, OF_WRITE)) < 0)
		return _RC = EC_NOFILE;
	setmode (fh, O_TEXT);
	_llseek (fh, 0L, SEEK_END);

//  Punkt ausgeben
	if ((_RC = _LS.OutputData (fh, GS.x [0] , GS.y [0])) != EC_OKAY) {
		_lclose (fh);
		return _RC;
	}
	_lclose (fh);   // MainCover schließen

//  PAT öffnen und Dateizeiger ans akt. Ende setzen
	if ((fh = OpenFile (_ofp.szPathName, &_ofp, OF_WRITE)) < 0)
		return _RC = EC_NOFILE;
	setmode (fh, O_TEXT);
	_llseek (fh, 0L, SEEK_END);
	double FlI, La;
	FlI = La = 0;		   // Flächeninhalt und Länge sind hier 0
	short Type = _Point;                                   
	if ((_RC = _PAT.OutputData (fh, &FlI, &La, pMF, &Type, pKurzText)) != EC_OKAY) {
		_lclose (fh);
		 return _RC;
	}

	return (_RC = (ErrCode) _lclose (fh));  // PAT schließen
}

//  True, wenn im Cover Daten speichert wurden, sonst False
Bool PointCover :: hasData (void) {
	return _LS.hasData ();
}

//  ArcCover -------------------------------------------------------------
//  Main- und Label-Cover sowie PAT anlegen
ArcCover :: ArcCover (pchar pCoverName)
		  : Cover (pCoverName) {			// MainCover anlegen
	if (_RC != EC_OKAY)	 // wenn Fehler beim anlegen des MainCovers
		return;

	_RC = CreateCover (_ofa, pCoverName, IDS_AATEXT); // AAT anlegen
}

//  alle zugeh. Coverages löschen
ErrCode ArcCover :: DeleteCover (void) {
	remove (_ofa.szPathName);					   // AAT löschen
	return Cover :: DeleteCover ();				 // MainCover löschen
}

//  Ausgabe
//	  + Kopf der ArcSection
//	  + Kopf unf Format der AAT
ErrCode ArcCover :: OutputFirstData (int) {
//  ArcCover öffnen und Dateizeiger ans akt. Ende setzen
	int fh;
	if ((fh = OpenFile (_of.szPathName, &_of, OF_WRITE)) < 0)
		return _RC = EC_NOFILE;
	setmode (fh, O_TEXT);
	_llseek (fh, 0L, SEEK_END);

//  Kopf der CoverSection ausgeben
	if ((_RC = Cover :: OutputFirstData (fh)) != EC_OKAY) {
		_lclose (fh);
		return _RC;
	}

//  Kopfzeile der ArcSection ausgeben
	if ((_RC = _AS.OutputHead (fh)) != EC_OKAY) {
		_lclose (fh);
		return _RC;
	}
	_lclose (fh);   // MainCover schließen

//  AAT öffnen und Dateizeiger ans akt. Ende setzen
	if ((fh = OpenFile (_ofa.szPathName, &_ofa, OF_WRITE)) < 0)
		return _RC = EC_NOFILE;
	setmode (fh, O_TEXT);
	_llseek (fh, 0L, SEEK_END);

//  Kopf der AAT ausgeben
	if ((_RC = _AAT.OutputHead (fh, _ofa.szPathName)) != EC_OKAY) {
		_lclose (fh);
		return _RC;
	}

//  Datenformat der AAT ausgeben
	Params Par;
	Par.FileHandle = fh;
	Par.pFileName = _ofa.szPathName;
	if ((_RC = _AAT.OutputFormat (&Par)) != EC_OKAY) {
		_lclose (fh);
		return _RC;
	}

	return (_RC = (ErrCode) _lclose (fh));  // AAT schließen
}

//  Ausgabe
//	  + Ende-Zeile der ArcSection
//	  + Aufruf der korr. Funktion der Basisklasse
//		kopiere Dabei AAT in MainCover
//	  + lösche AAT
ErrCode ArcCover :: OutputLastData (int, int, Section *) {
//  ArcCover öffnen und Dateizeiger ans akt. Ende setzen
	int fh;
	if ((fh = OpenFile (_of.szPathName, &_of, OF_WRITE)) < 0)
		return _RC = EC_NOFILE;
	setmode (fh, O_TEXT);
	_llseek (fh, 0L, SEEK_END);

//  ArcSection-Ende ausgeben
	if ((_RC = _AS.OutputFoot (fh)) != EC_OKAY) {
		_lclose (fh);
		return _RC;
	}

//  AAT öffnen und DatCount ausgeben
	int fha;
	if ((fha = OpenFile (_ofa.szPathName, &_ofa, OF_WRITE)) < 0) {
		_lclose (fh);
		return _RC = EC_NOFILE;
	}
	setmode (fha, O_TEXT);
	if ((_RC = _AAT.SetDataCount (fha, _AAT.GetCount ())) != EC_OKAY) {
		_lclose (fh);
		_lclose (fha);
		return _RC;
	}

//  abschließenden Infos ausgeben (TIC/BND usw.)
	_lclose (fha);			  // internen Puffer leeren
	if ((fha = OpenFile (_ofa.szPathName, &_ofa, OF_READ)) < 0) {
		_lclose (fh);
		return _RC = EC_NOFILE;
	}
	setmode (fha, O_TEXT);
	_llseek (fha, 0L, SEEK_SET);

	if ((_RC = Cover :: OutputLastData (fh, fha, &_AS)) != EC_OKAY) {
		_lclose (fha);
		_lclose (fh);
		return _RC;
	}
	_lclose (fha);  // AAT schließen

//  AAT löschen
	remove (_ofa.szPathName);

	return (_RC = (ErrCode) _lclose (fh));  // MainCover schließen
}

//  Ausgabe der eigentlichen Daten
ErrCode ArcCover :: OutputData (GSTRUCT &GS, MFELD *pMF, char *pKurzText) {
//  ArcCover öffnen und Dateizeiger ans akt. Ende setzen
	int fh;
	if ((fh = OpenFile (_of.szPathName, &_of, OF_WRITE)) < 0)
		return _RC = EC_NOFILE;
	setmode (fh, O_TEXT);
	_llseek (fh, 0L, SEEK_END);

//  AAT öffnen und Dateizeiger ans akt. Ende setzen
	int fha;
	if ((fha = OpenFile (_ofa.szPathName, &_ofa, OF_WRITE)) < 0) {
		_lclose (fh);
		return _RC = EC_NOFILE;
	}
	setmode (fha, O_TEXT);
	_llseek (fha, 0L, SEEK_END);

//  NodePoly-Objekt erzeugen
	NodePolyNr NP;

//  für jeweils max. 500 Stützpunkte pro Arc
	for (long i = 0; i < GS.GSize; i += ArcSize - 1) {
		long ActCnt = min (GS.GSize - i, ArcSize);

	//  Merkmale ausgeben
		double La = Laenge (GS, ActCnt, i);	 // Länge berechnen
		if (La <= 0.0) {
			OutputWarnung (IDS_NOLINE, GS.ON);
#if defined(_DEBUG)
			_ASSERTE(La >= 0.0);
			double xxx = Laenge (GS, ActCnt, i);	 // mal im Debugger nachsehen
#endif
			break;
		}

		if ((_RC = _AAT.OutputData (fha, &La, NULL, pMF, NULL, pKurzText)) != EC_OKAY)
			break;

	//  Linie ausgeben
		if ((_RC = _AS.OutputData (fh, GS, NP, ActCnt, i)) != EC_OKAY)
			break;
	}

//  Dateien schließen
	_lclose (fh);
	_lclose (fha);

	return _RC;
}

//  True, wenn im Cover Daten speichert wurden, sonst False
Bool ArcCover :: hasData (void) {
	return _AS.hasData ();
}

//  PolyCover -------------------------------------------------------------
//  alle Coverages anlegen
PolyCover :: PolyCover (pchar pCoverName)
		   : Cover (pCoverName) {		   // MainCover anlegen
	_NodeNr = 1;	// akt. Knoten- u. Polygon-Nummer setzen
	_ArcNr = 1;	 // akt. ArcNummer
	_PolyNr = 2;	// akt. Poylgon-Nummer: 1 --> universe Polygon

	if (_RC != EC_OKAY)	 // wenn Fehler beim anlegen des MainCovers
		return;

//  PalCoverages erzeugen
	if ((_RC = CreateCover (_ofpm, pCoverName, IDS_LABMAINEXT)) != EC_OKAY)
		return;

	if ((_RC = CreateCover (_ofpu, pCoverName, IDS_LABUNIEXT)) != EC_OKAY)
		return;

//  CNT-Cover erzeugen
	if ((_RC = CreateCover (_ofc, pCoverName, IDS_CNTEXT)) != EC_OKAY)
		return;

//  ggf. Label-Cover erzeugen
	if (PolyExist) {
		if ((_RC = CreateCover (_ofl, pCoverName, IDS_POLYLAB)) != EC_OKAY)
			return;
	}

//  PAT erzeugen
	_RC = CreateCover (_ofp, pCoverName, IDS_PATEXT);
}

//  alle zugeh. Coverages löschen
ErrCode PolyCover :: DeleteCover (void) {
	remove (_ofpm.szPathName);					   // PalCoverages löschen
	remove (_ofpu.szPathName);
	remove (_ofp.szPathName);					   // PAT löschen
	remove (_ofc.szPathName);					   // CNT löschen
	if (PolyExist)
		remove (_ofl.szPathName);				   // LAB löschen
	return Cover :: DeleteCover ();				 // MainCover löschen
}

//  Ausgabe
//	  + Kopf der ArcSection
//	  + Kopf und Datenformat der PAT
//	  + leeres universe polygon ausgeben
ErrCode PolyCover :: OutputFirstData (int) {
//  PolyCover öffnen und Dateizeiger ans akt. Ende setzen
	int fh;
	if ((fh = OpenFile (_of.szPathName, &_of, OF_WRITE)) < 0)
		return _RC = EC_NOFILE;
	setmode (fh, O_TEXT);
	_llseek (fh, 0L, SEEK_END);

//  Kopf der CoverSection ausgeben
	if ((_RC = Cover :: OutputFirstData (fh)) != EC_OKAY) {
		_lclose (fh);
		return _RC;
	}

//  Kopfzeile der ArcSection ausgeben
	if ((_RC = _AS.OutputHead (fh)) != EC_OKAY) {
		_lclose (fh);
		return _RC;
	}
	_lclose (fh);   // MainCover schließen

//  PAT öffnen und Dateizeiger ans akt. Ende setzen
	if ((fh = OpenFile (_ofp.szPathName, &_ofp, OF_WRITE)) < 0)
		return _RC = EC_NOFILE;
	setmode (fh, O_TEXT);
	_llseek (fh, 0L, SEEK_END);

//  Kopf der PAT ausgeben
	if ((_RC = _PAT.OutputHead (fh, _ofp.szPathName)) != EC_OKAY) {
		_lclose (fh);
		return _RC;
	}

//  Datenformat der PAT ausgeben
	Params Par;
	Par.FileHandle = fh;
	Par.pFileName = _ofp.szPathName;
	if ((_RC = _PAT.OutputFormat (&Par)) != EC_OKAY) {
		_lclose (fh);
		return _RC;
	}

//  universe Polygon ausgeben
	if (!pMDT)
		return EC_SYSERROR;
	Par.ActCol = pMDT -> ActColumn ();
	if ((_RC = _PAT.OutputEmptyUniPoly (Par)) != EC_OKAY) {
		_lclose (fh);
		return _RC;
	}

	return _RC = (ErrCode) _lclose (fh);	// PAT schließen
}

//  Ausgabe
//	  + Ende-Zeile der ArcSection
//	  + komplette CNT-Section
//	  + komplette LabelSection
//	  + Kopf der PalSection
//	  + kopiere PalCoverages in MainCover
//	  + lösche PalCoverages
//	  + vervollständige universe Polygon
//	  + Anzahl Datensätze in PAT
//	  + Aufruf der korr. Funktion der Basisklasse
//		dabei: PAT in MainCover kopieren
//	  + lösche PAT
ErrCode PolyCover :: OutputLastData (int, int, Section *) {
//  PolyCover öffnen und Dateizeiger ans akt. Ende setzen
	int fh;
	if ((fh = OpenFile (_of.szPathName, &_of, OF_WRITE)) < 0)
		return _RC = EC_NOFILE;
	setmode (fh, O_TEXT);
	_llseek (fh, 0L, SEEK_END);

//  ArcSection-Ende ausgeben
	if ((_RC = _AS.OutputFoot (fh)) != EC_OKAY) {
		_lclose (fh);
		return _RC;
	}

//  komplette CNT-Section in MainCover ausgeben: zuerst Kopf
	if ((_RC = _CS.OutputHead (fh)) != EC_OKAY) {	   // in MainCover
		_lclose (fh);
		return _RC;
	}

//  universe-Eintrag für CNT-Section
	if ((_RC = _CS.OutputData (fh, _AS)) != EC_OKAY) {  // in MainCover
		_lclose (fh);
		return _RC;
	}

//  CNT-Cover öffnen, Dateizeiger an den Anfang
	int fhc;
	if ((fhc = OpenFile (_ofc.szPathName, &_ofc, OF_READ)) < 0) {
		_lclose (fh);
		return _RC = EC_NOFILE;
	}
	setmode (fhc, O_TEXT);
	_llseek (fhc, 0L, SEEK_SET);

//  kopiere CNT-Cover in MainCover, lösche CNT-Cover
	if ((_RC = FileCopy (fh, fhc)) != EC_OKAY) {
		_lclose (fh);
		_lclose (fhc);
		return _RC;
	}
	_lclose (fhc);
	remove (_ofc.szPathName);

//  Endezeile für CNT-Section ausgeben
	if ((_RC = _CS.OutputFoot (fh)) != EC_OKAY) {
		_lclose (fh);
		return _RC;
	}

//  ggf. komplette Label-Section in MainCover ausgeben: zuerst Kopf
	if (PolyExist) {
		if ((_RC = _LS.OutputHead (fh)) != EC_OKAY) {   // in MainCover
			_lclose (fh);
			return _RC;
		}

	//  Label-Cover öffnen, Dateizeiger an den Anfang
		int fhl;
		if ((fhl = OpenFile (_ofl.szPathName, &_ofl, OF_READ)) < 0) {
			_lclose (fh);
			return _RC = EC_NOFILE;
		}
		setmode (fhl, O_TEXT);
		_llseek (fhl, 0L, SEEK_SET);

	//  kopiere Label-Cover in MainCover, lösche Label-Cover
		if ((_RC = FileCopy (fh, fhl)) != EC_OKAY) {
			_lclose (fh);
			_lclose (fhl);
			return _RC;
		}
		_lclose (fhl);
		remove (_ofl.szPathName);

	//  Endezeile der Label-Section ausgeben
		if ((_RC = _LS.OutputFoot (fh)) != EC_OKAY) {   // in MainCover
			_lclose (fh);
			return _RC;
		}
	}		   // end label section

//  Kopf der PalSection ausgeben
	if ((_RC = _PS.OutputHead (fh)) != EC_OKAY) {   // in MainCover
		_lclose (fh);
		return _RC;
	}

//  Kopf des universe polygon ausgeben
	if ((_RC = _PS.OutputDataHead (fh, _AS, _PS.PolyCount ())) != EC_OKAY) {
		_lclose (fh);
		return _RC;
	}

//  Uni-PalCoverage öffnen und Dateizeiger ans akt. Ende
	int fhpu;
	if ((fhpu = OpenFile (_ofpu.szPathName, &_ofpu, OF_READWRITE)) < 0) {
		_lclose (fh);
		return _RC = EC_NOFILE;
	}
	setmode (fhpu, O_TEXT);
	_llseek (fhpu, 0L, SEEK_END);

//  ggf. Zeilenvorschub ausgeben
	short TmpCnt = _PS.UniCount ();
	if ((_RC = _PS.OutputLastCR (fhpu, TmpCnt)) != EC_OKAY) {
		_lclose (fh);
		_lclose (fhpu);
		return _RC;
	}

//  kopiere Uni-PalCover in MainCover
	_llseek (fhpu, 0L, SEEK_SET);
	if ((_RC = FileCopy (fh, fhpu)) != EC_OKAY) {   // universe Polygon
		_lclose (fh);
		_lclose (fhpu);
		return _RC;
	}
	_lclose (fhpu);
	remove (_ofpu.szPathName);

//  Main-PalCover öffnen und Dateizeiger ans akt. Ende
	int fhpm;
	if ((fhpm = OpenFile (_ofpm.szPathName, &_ofpm, OF_READWRITE)) < 0) {
		_lclose (fh);
		_lclose (fhpm);
		return _RC = EC_NOFILE;
	}
	setmode (fhpm, O_TEXT);
	_llseek (fhpm, 0L, SEEK_END);

//  ggf. Zeilenvorschub ausgeben
	TmpCnt = _PS.MainCount ();
	if ((_RC = _PS.OutputLastCR (fhpm, TmpCnt)) != EC_OKAY) {
		_lclose (fh);
		_lclose (fhpm);
		return _RC;
	}

//  kopiere Main-PalCover in MainCover
	_llseek (fhpm, 0L, SEEK_SET);
	if ((_RC = FileCopy (fh, fhpm)) != EC_OKAY) { // kop. alle weiteren Maschen
		_lclose (fh);
		_lclose (fhpm);
		return _RC;
	}
	_lclose (fhpm);
	remove (_ofpm.szPathName);

//  Fußzeile der PalSection ausgeben
	if ((_RC = _PS.OutputFoot (fh)) != EC_OKAY) {
		_lclose (fh);
		return _RC;
	}

//  PAT öffnen
	int fhp;
	if ((fhp = OpenFile (_ofp.szPathName, &_ofp, OF_WRITE)) < 0) {
		_lclose (fh);
		return _RC = EC_NOFILE;
	}
	setmode (fhp, O_TEXT);

//  universe polygon vervollständigen
	if ((_RC = _PAT.OutputFillUniPoly (fhp, _AS)) != EC_OKAY) {
		_lclose (fh);
		_lclose (fhp);
		return _RC;
	}

//  DataCount ausgeben
	if ((_RC = _PAT.SetDataCount (fhp, _PAT.GetCount ())) != EC_OKAY) {
		_lclose (fh);
		_lclose (fhp);
		return _RC;
	}

//  abschließenden Infos ausgeben (TIC/BND usw.)
	_lclose (fhp);			  // internen Puffer leeren
	if ((fhp = OpenFile (_ofp.szPathName, &_ofp, OF_READ)) < 0) {
		_lclose (fh);
		return _RC = EC_NOFILE;
	}
	setmode (fhp, O_TEXT);
	_llseek (fhp, 0L, SEEK_SET);

	if ((_RC = Cover :: OutputLastData (fh, fhp, &_AS)) != EC_OKAY) {
		_lclose (fhp);
		_lclose (fh);
		return _RC;
	}
	_lclose (fhp);

	remove (_ofp.szPathName);

	return (_RC = (ErrCode) _lclose (fh));
}

//  Ausgabe der eigentlichen Daten
ErrCode PolyCover :: OutputData (GSTRUCT &GS, MFELD *pMF, char *pKurzText) {
	if (Insel)	// Inseln separat ausgeben
		return OutputDataExt (GS, pMF, pKurzText);

//  Werte init.
	short Type = _Poly;					// FeatureClass
	NodePolyNr NP;						// Arc-Topologie
	NodePolyNrList *pNL = NULL;			// Speicherung der Nummern
	long *pCount = GS.cnt;				// Anzahl der Stützpunkte in Konturen
	long AktIndex = 0;					// aktueller Stützpunkt
	double FlI = 0;						// FlächenInhalt
	double Xs = 0;						// Schwerpunkt-
	double Ys = 0;						// Koordinaten
	Bool Island = False;				// äußere Masche ist keine Insel
	double La = Laenge (GS, *pCount);	// Umfang der aüßeren Masche

//  Schwerpunkt und Flächeninhalt für äußere Masche berechnen
	SchwerPunkt (GS, FlI, Xs, Ys, *pCount);
	if (!FlI)
		return OutputWarnung (IDS_NOAREA, GS.ON);

//  PAT öffnen und Dateizeiger ans akt. Ende setzen
	int fhp;
	if ((fhp = OpenFile (_ofp.szPathName, &_ofp, OF_WRITE)) < 0) {
		return _RC = EC_NOFILE;
	}
	setmode (fhp, O_TEXT);
	_llseek (fhp, 0L, SEEK_END);

//  Merkmale nur für äußere Masche ausgeben
	if ((_RC = _PAT.OutputData (fhp, &FlI, &La, pMF, &Type, pKurzText)) != EC_OKAY)
		return _RC;
	_lclose (fhp);

//  CNT öffnen und Dateizeiger ans akt. Ende setzen
	int fhc;
	if ((fhc = OpenFile (_ofc.szPathName, &_ofc, OF_WRITE)) < 0) {
		return _RC = EC_NOFILE;
	}
	setmode (fhc, O_TEXT);
	_llseek (fhc, 0L, SEEK_END);

//  Schwerpunkt ausgeben
	if ((_RC = _CS.OutputData (fhc, Xs, Ys)) != EC_OKAY)
		return _RC;
	_lclose (fhc);

//  ggf. LabelPunkt ausgeben
	if (PolyExist) {
		int fhl;
		if ((fhl = OpenFile (_ofl.szPathName, &_ofl, OF_WRITE)) < 0) {
			return _RC = EC_NOFILE;
		}
		setmode (fhl, O_TEXT);
		_llseek (fhl, 0L, SEEK_END);

	//  Schwerpunkt ausgeben
		CheckLabelPoint (Xs, Ys, GS);  // Schwerpkt. ggf. korr.
		if ((_RC = _LS.OutputData (fhl, Xs, Ys, 1)) != EC_OKAY)
			return _RC;
		_lclose (fhl);
	}

//  PolyCover öffnen und Dateizeiger ans akt. Ende setzen
	int fh;
	if ((fh = OpenFile (_of.szPathName, &_of, OF_WRITE)) < 0)
		return _RC = EC_NOFILE;
	setmode (fh, O_TEXT);
	_llseek (fh, 0L, SEEK_END);

//  PalCoverages öffnen und Dateizeiger ans akt. Ende setzen
	int fhpm;	   // Main-PalCover
	if ((fhpm = OpenFile (_ofpm.szPathName, &_ofpm, OF_WRITE)) < 0) {
		_lclose (fh);
		return _RC = EC_NOFILE;
	}
	setmode (fhpm, O_TEXT);
	_llseek (fhpm, 0L, SEEK_END);
	int fhpu;	   // Uni-PalCover
	if ((fhpu = OpenFile (_ofpu.szPathName, &_ofpu, OF_WRITE)) < 0) {
		_lclose (fh);
		_lclose (fhpm);
		return _RC = EC_NOFILE;
	}
	setmode (fhpu, O_TEXT);
	_llseek (fhpu, 0L, SEEK_END);

//  Fläche - einschließlich evtl. Innenflächen - ausgeben
	for (; _RC == EC_OKAY && *pCount;
			Island = True,				// alle weiteren Maschen sind Inseln
			AktIndex += *pCount,		// Stützpunkt-Index aktualisieren
			pCount++) {					// nächste Fläche
		if (Island) {   // für äußere Fläche bereits berechnet
			if (! (FlI = FlInhalt (GS, *pCount, AktIndex))) {
				OutputWarnung (IDS_NOAREA, GS.ON);
				continue;
			}
		}
		Bool DrehSinn = FlI > 0 ? True : False;

	//  Polygon-Topolgie aufbauen
		if (DrehSinn) {				//  bei positivem Drehsinn
			NP.LeftPoly = _PolyNr;
			NP.RightPoly = 1;		//  universe Polygon
		} else {					//  bei negativem Drehsinn
			NP.LeftPoly = 1;
			NP.RightPoly = _PolyNr;
		}

	//  Nuummern-Liste erzeugen
		pNL = new NodePolyNrList (DrehSinn);
		if (!pNL)
			_RC = EC_NOMEMORY;

	//  für jeweils max. 500 Stützpunkte pro Arc
		long FNode = _NodeNr;	// 1. Knoten merken
		for (long i = AktIndex; _RC == EC_OKAY && i < *pCount + AktIndex;
			 i += ArcSize - 1) {
			long ActCnt = min (*pCount - (i - AktIndex), ArcSize);

		//  NodeTopologie aufbauen
			NP.FirstNode = _NodeNr++;
			if (i == AktIndex && ActCnt == *pCount)// wenn kein Splitten notw.
				NP.LastNode = NP.FirstNode;
			else {
				if (ActCnt < ArcSize)			//  bei letzten Ausgabe
					NP.LastNode = FNode;		//  wieder zum Anfangsknoten
				else
					NP.LastNode = _NodeNr;		// 1. oder Zwischenknoten
			}
			NP.ArcNr = _ArcNr;

		//  Stützpunkte ausgeben
			if (_RC == EC_OKAY)
				_RC = _AS.OutputData (fh, GS, NP, ActCnt, i);

		//  Topologie speichern
			if (_RC == EC_OKAY)
				_RC = pNL -> Add (NP) ? EC_OKAY : EC_NOMEMORY;

			_ArcNr++;		   // nächste Arc-Nr
		}

	//  Topologie ausgeben
		if (!Island) {									// äußere Masche
			if (_RC == EC_OKAY)
				_RC = _PS.OutputUniIsland (fhpu, pNL);  // Insel für universe polygon
			if (_RC == EC_OKAY)
				_RC = _PS.OutputDataHead (fhpm, GS);
			if (_RC == EC_OKAY)
				_RC = _PS.OutputAussMasche (fhpm, pNL);
		} else									  // "normale" Insel
			if (_RC == EC_OKAY)
				_RC = _PS.OutputMainIsland (fhpm, pNL);

		_PolyNr++;					// nächste Polygon-Nummer
		DELETE_OBJ (pNL);			// alte Liste löschen
	}

	DELETE_OBJ (pNL);				// alte Liste ggf.löschen

//  alle Dateien schließen
	_lclose (fh);
	_lclose (fhpm);
	_lclose (fhpu);

	return _RC;
}

//  True, wenn im Cover Daten speichert wurden, sonst False
Bool PolyCover :: hasData (void) {
	return _AS.hasData ();
}

//  Ausgabe der eigentlichen Daten
//	Obige Funktion wurde insofern erweitert, daß die Inseln nochmals als
//	äußere Maschen ausgegeben werden. Fehlt diese Ausgabe, ist nach einem uvtl. clean
//	die Attributierung völlig durcheinander.
ErrCode PolyCover :: OutputDataExt (GSTRUCT &GS, MFELD *pMF, char *pKurzText) {
//	prüfe interne Parameter
	if (_RC != EC_OKAY)
		return _RC;

//  Werte init.
	short Type = _Poly;					// FeatureClass
	NodePolyNr NP;						// Arc-Topologie
	NodePolyNrList *pNL = NULL;			// Speicherung der Nummern
	long *pCount = GS.cnt;				// Anzahl der Stützpunkte in Konturen
	long AktIndex = 0;					// aktueller Stützpunkt
	double FlI = 0;						// FlächenInhalt
	double Xs = 0;						// Schwerpunkt-
	double Ys = 0;						// Koordinaten
	Bool Island = False;				// äußere Masche ist keine Insel
	double La = 0.0;					// Umfang der akt. Masche
	
//	FileHandle aller benötigter Dateien;
	int fhp,	// PAT
		fhc,	// CNT	
		fhl,	// LAB	
		fh,		// ARC
		fhpm,	// PAL main
		fhpu,	// PAL universe
		fhpmh;	// PAL-Inseln

//	init.
	fhp = fhc = fhl = fh = fhpm = fhpu = fhpmh = 0;

//  Alle Dateien öffnen: Zuerst PAT und Dateizeiger ans akt. Ende setzen (1)
	if ((fhp = OpenFile (_ofp.szPathName, &_ofp, OF_WRITE)) > 0) 
	{		
		setmode (fhp, O_TEXT);
		_llseek (fhp, 0L, SEEK_END);
	}
	else
		_RC = EC_NOFILE;

//  CNT öffnen und Dateizeiger ans akt. Ende setzen (2)
	if (EC_OKAY == _RC)
	{
		if ((fhc = OpenFile (_ofc.szPathName, &_ofc, OF_WRITE)) > 0)
		{
			setmode (fhc, O_TEXT);
			_llseek (fhc, 0L, SEEK_END);
		}
		else
			_RC = EC_NOFILE;
	}

//  LAB-Datei öffnen (3)
	if (EC_OKAY == _RC) 
	{
		if (PolyExist) 
		{
			if ((fhl = OpenFile (_ofl.szPathName, &_ofl, OF_WRITE)) > 0) 
			{
				setmode (fhl, O_TEXT);
				_llseek (fhl, 0L, SEEK_END);
			}
			else
				_RC = EC_NOFILE;
		}
	}

//  PolyCover öffnen und Dateizeiger ans akt. Ende setzen (4)
	if (EC_OKAY == _RC)
	{
		if ((fh = OpenFile (_of.szPathName, &_of, OF_WRITE)) > 0)
		{
			setmode (fh, O_TEXT);
			_llseek (fh, 0L, SEEK_END);
		}
		else
			_RC = EC_NOFILE;
	}

//  PalCoverages öffnen und Dateizeiger ans akt. Ende setzen (5)
	if (EC_OKAY == _RC)
	{
		if ((fhpm = OpenFile (_ofpm.szPathName, &_ofpm, OF_WRITE)) > 0) 
		{
			setmode (fhpm, O_TEXT);
			_llseek (fhpm, 0L, SEEK_END);
		}
		else
			_RC = EC_NOFILE;
	}

//	universe PalCover (6)
	if (EC_OKAY == _RC)
	{
		if ((fhpu = OpenFile (_ofpu.szPathName, &_ofpu, OF_WRITE)) > 0) 
		{
			setmode (fhpu, O_TEXT);
			_llseek (fhpu, 0L, SEEK_END);
		}
		else
			_RC = EC_NOFILE;
	}

//	Insel-Topologie
	if (EC_OKAY == _RC)
	{
		OFSTRUCT ofpm;
		if ((fhpmh = OpenFile (szTempFileName, &ofpm, OF_CREATE | OF_WRITE | OF_READ)) > 0)
			setmode (fhpmh, O_TEXT);
		else
			_RC = EC_NOFILE;
	}

//  Fläche - einschließlich evtl. Innenflächen - ausgeben
	BOOL DrehSinn = True;
	long lMainPolyNr = 0;				// PolyNr der äußeren Masche
	Bool bOutputIsland = False;			// Insel ausgegeben
	for (; _RC == EC_OKAY && *pCount;
			Island = True,				// alle weiteren Maschen sind Inseln
			AktIndex += *pCount,		// Stützpunkt-Index aktualisieren
			pCount++) 					// nächste Fläche
	{
	//  Schwerpunkt und Flächeninhalt der akt. Fläche berechnen
		SchwerPunkt (GS, FlI, Xs, Ys, *pCount, AktIndex);
		if (!FlI)
		{
			OutputWarnung (IDS_NOAREA, GS.ON);
			continue;
		}
		DrehSinn = FlI > 0 ? True : False;				// Drehsinn speichern

	//  Polygon-Topolgie aufbauen
		if (DrehSinn) 				//  bei positivem Drehsinn
		{
			NP.LeftPoly = _PolyNr;
			NP.RightPoly = Island ? lMainPolyNr : 1; //  universe Polygon
		} 
		else 						//  bei negativem Drehsinn
		{
			NP.LeftPoly = Island ? lMainPolyNr : 1;
			NP.RightPoly = _PolyNr;
		}

	//  Nuummern-Liste erzeugen
		pNL = new NodePolyNrList (DrehSinn);
		if (!pNL)
		{
			_RC = EC_NOMEMORY;
			break;
		}

	//	Unfang der akt. Flächen berechnen
		La = Laenge (GS, *pCount, AktIndex);

	//  Merkmale der akt. Fläche ausgeben
		if ((_RC = _PAT.OutputData (fhp, &FlI, &La, Island ? NULL : pMF, &Type, pKurzText)) != EC_OKAY)
			break;
		
	//  CNT-Punkt ausgeben (Schwerpunkt)
		if ((_RC = _CS.OutputData (fhc, Xs, Ys)) != EC_OKAY)
			break;

	//  ggf. korrigierten Schwerpunkt ausgeben
		if (PolyExist)
		{
			if (Island)
				CheckLabelPoint (Xs, Ys, &GS.x [AktIndex], &GS.y [AktIndex], *pCount);	// Schwerpkt. ggf. korr.
			else
				CheckLabelPoint (Xs, Ys, GS);
			if ((_RC = _LS.OutputData (fhl, Xs, Ys, 1)) != EC_OKAY)
				break;
		}

	//  für jeweils max. 500 Stützpunkte pro Arc
		long FNode = _NodeNr;		// 1. Knoten merken
		long ActCnt = 0;			// akt. Anzahl Stützpunkte	
		for (long i = AktIndex; _RC == EC_OKAY && i < *pCount + AktIndex; i += ArcSize - 1) 
		{
			ActCnt = min (*pCount - (i - AktIndex), ArcSize);

		//  NodeTopologie aufbauen
			NP.FirstNode = _NodeNr++;
			if ((i == AktIndex) && (ActCnt == *pCount))		// wenn kein Splitten notw.
				NP.LastNode = NP.FirstNode;
			else 
			{
				if (ActCnt < ArcSize)				//  bei letzten Ausgabe
					NP.LastNode = FNode;			//  wieder zum Anfangsknoten
				else
					NP.LastNode = _NodeNr;			// 1. oder Zwischenknoten
			}
			NP.ArcNr = _ArcNr;

		//  Stützpunkte ausgeben
			if (_RC == EC_OKAY)
				_RC = _AS.OutputData (fh, GS, NP, ActCnt, i);

		//  Topologie speichern
			if (_RC == EC_OKAY)
				_RC = pNL -> Add (NP) ? EC_OKAY : EC_NOMEMORY;

			_ArcNr++;		   // nächster Arc-Nr
		}

	//  Topologie ausgeben
		if (!Island) 									// äußere Masche
		{
			lMainPolyNr = _PolyNr;
			if (_RC == EC_OKAY)
				_RC = _PS.OutputUniIsland (fhpu, pNL);  // Insel für universe polygon
			if (_RC == EC_OKAY)
				_RC = _PS.OutputDataHead (fhpm, GS);
			if (_RC == EC_OKAY)
				_RC = _PS.OutputAussMasche (fhpm, pNL);
		} 
		else											// "normale" Insel
		{
		//	Ausgabe in MainPalCover
			if (_RC == EC_OKAY)
				_RC = _PS.OutputMainIsland (fhpm, pNL);

		//	Insel nochmals "drauf" legen   --> Ausgabe in extra Datei
			if (_RC == EC_OKAY)
				_RC = _PS.OutputDataHead (fhpmh, &GS.x [AktIndex], &GS.y [AktIndex], *pCount, TRUE);	// Insel
			if (_RC == EC_OKAY)
				_RC = _PS.OutputAussMasche (fhpmh, pNL, TRUE);		// Insel
			bOutputIsland = True;
		}

		_PolyNr++;					// nächste Polygon-Nummer
		DELETE_OBJ (pNL);			// alte Liste löschen
	}

//	alte Liste ggf.löschen
	DELETE_OBJ (pNL);				

//	PolyCover mit Insel-Topologie ergänzen
	if ((EC_OKAY == _RC) && bOutputIsland)
		_RC = _PS.OutputTopologie (fhpm, fhpmh);

//  alle Dateien schließen
	if (fhp > 0)
		_lclose (fhp);
	if (fhc > 0)
		_lclose (fhc);
	if (fhl > 0)
		_lclose (fhl);
	if (fh > 0)
		_lclose (fh);
	if (fhpm > 0)
		_lclose (fhpm);
	if (fhpu > 0)
		_lclose (fhpu);
	if (fhpmh > 0)
	{
		_lclose (fhpmh);
		remove (szTempFileName);
	}

	return _RC;
}
