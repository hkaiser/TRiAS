/*
Datei: INFO.CXX

Basisklassen für die Erzeugung des lesbaren Arc/Info-Austausschformates.
Verwaltung der im Format auftretenden Informations- (Sachdaten-) Dateien.

Erarbeitet: J. Benkenstein				  Begonnen am: 30. April 1993
*/

#include "stdafx.h"               
/*XX*/ #include "TRiASArcImpl.h"

// #HK960812
	#include <string.h>	 	// memset ()
	#include <math.h>	   	// fabs ()
	#include <ctype.h>	  	// toupper ()

#include <attribs.hxx>	  	// VisInfo ...
#include <impexp.hxx>	   	// MF, GS ...

#include "merkmdes.hxx"	 	// ExtMerkmalDescriptionTree		
#include "section.hxx"	  	// Section  
#include "geo.hxx"		  	// Laenge ()		
#include "info.hxx"		 	// zugeh. Header
//XX#include "triasarc.hr"	   	// Resource-Defines
#include "triasarc.hxx"	 	// FileNameSize	 

//  Konstanten
const char pHeadFieldFormat [] = "%4d%4d";	// Kopf-Feld-Format
const char pHeadLenFormat [] = "%4d";		// Kopf-RekordLen-Format
const char pHeadDataFormat [] = "%10ld";	// Kopf-DataCount-Format
const double BoundFakt = 0.05;	  			// Bildmaße um 5% vergr./verkleinern
const double MinBound  = 20.0;	  			// min. Extension-Vergrößerung
const double MinPassExt = 5.0;	  			// min. Entfernung zw. PassPunkten
const short LenAttrFakt = 10;
const long InselUserId = 99999;				// User-Id bei Inseln

//  externe Variablen
extern ExtMerkmalDescriptionTree *pMDT;
extern ResourceFile *pRF;
extern Bool FourCoverages;      // Ausgabe in 4 Covers
extern long ObjKlasseMK;		// von TRIAS vergebener Merkmalskode für Objekt-Klasse 

//  Prototypen
ErrCode ExportLineCR (int FileHandle, pchar pLine); // Zeile in Datei mit
											// abschließendem \r\n ausgeben
ErrCode ExportLine (int FileHandle, pchar pLine); // Zeile in Datei ausgeben
pchar DtoeA (pchar pBuffer, double Wert);
pchar CheckUmlaute (pchar pName);		   // dt. Umlaute ersetzen
pchar Trim (pchar pText);   // abschließende Leerzeichen löschen

extern "C" {
pchar OutputResourceTemplate (uint ResourceID, int FileHandle);
}

//  Params -----------------------------------------------------------------
Params :: Params (void) {
	MFELD *pMF = NULL;
	AttrType Type = PAT;
	ResourceId = 0;
	ActOut = LastLen = Count = TotalLen = ActCol = 0;
	FileHandle = 0;
	pFileName = NULL;
	pIdentKurzText = NULL;
}

//  Info -------------------------------------------------------------------
//  Basisklasse für die Verwaltung und Ausgabe einer Sachdaten-Datei.
Info :: Info (void) {
	_FieldCountPos = _RecordLenPos = _DataCountPos = 0L;
}

//  Ausgabe des Formatkopfes - Filename muß frei von Umlauten sein.
//  Die Dateipositionen von
//		  - FieldCount (Anzahl der Felder),
//		  - RercordLen (Summe der Länge aller Felder) und
//		  - DataCount (Summe der Datensätze) werden gespeichert.
ErrCode Info :: OutputHead (int FileHandle, pchar pFileName, uint FileExtId,
						short FieldCount, short RecordLen, long DataCount) {
	ErrCode EC = EC_OKAY;	   // Rückkehrwert
	char Buffer [80] = "";	  // Arbeitspuffer
	char Buffer1 [20] = "";	 
	char FileName [_MAX_FNAME] = "";

//  Dateinamen und Kennung ausgeben
	_splitpath (pFileName, NULL, NULL, FileName, NULL);
	ResString Ext (ResID (FileExtId, pRF), _MAX_EXT);
	ResString Kennung (ResID (IDS_INFOKENNUNG, pRF), 5);
	lstrcpy (Buffer1, FileName);
	lstrcat (Buffer1, Ext.Addr ());	 
	wsprintf (Buffer, "%-12s%22s", Buffer1, Kennung.Addr ());
	if ((EC = ExportLine (FileHandle, Buffer)) != EC_OKAY)
		return EC;

	_FieldCountPos = _llseek (FileHandle, 0L, SEEK_CUR); // Pos. speichern

//  Anzahl der Felder ausgeben
	wsprintf (Buffer, pHeadFieldFormat, FieldCount, FieldCount);
	if ((EC = ExportLine (FileHandle, Buffer)) != EC_OKAY)
		return EC;

	_RecordLenPos =  _llseek (FileHandle, 0L, SEEK_CUR); // Pos. speichern

//  Rekordlänge ausgeben
	wsprintf (Buffer, pHeadLenFormat, RecordLen);
	if ((EC = ExportLine (FileHandle, Buffer)) != EC_OKAY)
		return EC;

	_DataCountPos = _llseek (FileHandle, 0L, SEEK_CUR); // Pos. speichern

//  Anzahl der folgenden Datensätze ausgeben
	wsprintf (Buffer, pHeadDataFormat, DataCount);
	return ExportLineCR (FileHandle, Buffer);
}

//  Neue Anzahl Sachdaten in zuvor geöffnete Datei ausgeben.
ErrCode Info :: SetDataCount (int FileHandle, long NewDataCount) {
//  gültige Dateiposition ?
	if (! _DataCountPos)
		return EC_SYSERROR;

//  Datei positionieren
	_llseek (FileHandle, _DataCountPos, SEEK_SET);

//  neuen Daten bilden und ausgeben
	char Buffer [15] = "";
	wsprintf (Buffer, pHeadDataFormat, NewDataCount);
	ErrCode EC = EC_OKAY;
	if ((EC = ExportLine (FileHandle, Buffer)) != EC_OKAY)
		return EC;

	_llseek (FileHandle, 0L, SEEK_END); // wieder auf das akt. Ende pos.

	return EC;
}

//  Neue Anzahl Felder in zuvor geöffnete Datei ausgeben.
ErrCode Info :: SetFieldCount (int FileHandle, short NewFieldCount) {
//  gültige Dateiposition ?
	if (! _FieldCountPos)
		return EC_SYSERROR;

//  Datei positionieren
	_llseek (FileHandle, _FieldCountPos, SEEK_SET);

//  neuen Daten bilden und ausgeben
	char Buffer [15] = "";
	wsprintf (Buffer, pHeadFieldFormat, NewFieldCount, NewFieldCount);
	ErrCode EC = EC_OKAY;
	if ((EC = ExportLine (FileHandle, Buffer)) != EC_OKAY)
		return EC;

	_llseek (FileHandle, 0L, SEEK_END); // wieder ausf das akt. Ende pos.

	return EC;
}

//  Neue Satzlänge in zuvor geöffnete Datei ausgeben.
ErrCode Info :: SetRecordLen (int FileHandle, short NewRecordLen) {
//  gültige Dateiposition ?
	if (! _RecordLenPos)
		return EC_SYSERROR;

//  Datei positionieren
	_llseek (FileHandle, _RecordLenPos, SEEK_SET);

//  neuen Daten bilden und ausgeben
	char Buffer [15] = "";
	wsprintf (Buffer, pHeadLenFormat, NewRecordLen);
	ErrCode EC = EC_OKAY;
	if ((EC = ExportLine (FileHandle, Buffer)) != EC_OKAY)
		return EC;

	_llseek (FileHandle, 0L, SEEK_END); // wieder ausf das akt. Ende pos.

	return EC;
}

//  Format der Sachdaten aus Resource lesen und ausgeben
ErrCode Info :: OutputFormat (Params *pP) {
	return OutputResourceTemplate (pP -> ResourceId, pP -> FileHandle) ?
		   EC_OKAY : EC_NORESOURCE;
}

//  Boundaries -------------------------------------------------------------
//  Die Klasse realiesiert die Ausgabe der Zeichnungsgrenzen in die BND-Datei.
ErrCode Boundaries :: OutputHead (int FileHandle, pchar pFileName) {
	return Info :: OutputHead (FileHandle, pFileName, IDS_BNDEXT, 4, 16, 1);
}

//  Werte der Zeichnungsgrenzen ausgeben
ErrCode Boundaries:: OutputData (int FileHandle, void *pXmin, void *pYmin,
								 void *pXmax, void *pYmax, void*) {
//  prüfe Parameter
	if (!pXmin || !pYmin || !pXmax || !pYmax)
		return EC_SYSERROR;

	double XMin = * (double *) (pXmin);
	double YMin = * (double *) (pYmin);
	double XMax = * (double *) (pXmax);
	double YMax = * (double *) (pYmax);
	char Buffer [20] = "";		  // Arbeitspuffer
	register ErrCode EC = EC_OKAY;  // Rückkehrwert

	double Xext = max ((XMax - XMin) * BoundFakt, MinBound);
	double Yext = max ((YMax - YMin) * BoundFakt, MinBound);

//  XMin/YMin ausgeben
	double Xmin = XMin - Xext;
	if (Xmin < 0)
		Xmin = 0;
	double Ymin = YMin - Yext;
	if (Ymin < 0)
		Ymin = 0;		
		
	if ((EC = ExportLine (FileHandle, DtoeA (Buffer, Xmin))) != EC_OKAY)
		return EC;
	if ((EC = ExportLine (FileHandle, DtoeA (Buffer, Ymin))) != EC_OKAY)
		return EC;

//  XMax/YMax ausgeben
	if ((EC = ExportLine (FileHandle, DtoeA (Buffer, XMax + Xext))) != EC_OKAY)
		return EC;
	return ExportLineCR (FileHandle, DtoeA (Buffer, YMax + Yext));
}

//  Format der Sachdaten aus Resource lesen und ausgeben
ErrCode Boundaries :: OutputFormat (Params *pP) {
	pP -> ResourceId = BND_FORMAT;
	return Info :: OutputFormat (pP);
}

//  PassPoints -------------------------------------------------------------
//  Die Klasse realisiert die Ausgabe von 4 Passpunkten in die TIC-Datei.
ErrCode PassPoints :: OutputHead (int FileHandle, pchar pFileName) {
	return Info :: OutputHead (FileHandle, pFileName, IDS_TICEXT, 3, 12, 4);
}

//  4 Passpunkte ausgeben
ErrCode PassPoints :: OutputData (int FileHandle, void *pXmin, void *pYmin,
								 void *pXmax, void *pYmax, void*) {
	const char CountFormat [] = "%10d"; // Anzahlformat
	char Buffer [20] = "";			  // Arbeitspuffer
	register ErrCode EC = EC_OKAY;	  // Rückkehrwert

//  prüfe Parameter
	if (!pXmin || !pYmin || !pXmax || !pYmax)
		return EC_SYSERROR;

	double XMin = * (double *) (pXmin);
	double YMin = * (double *) (pYmin);
	double XMax = * (double *) (pXmax);
	double YMax = * (double *) (pYmax);

//  Koordinaten ggf. korr.
	if (XMax - XMin < MinPassExt) {
		XMin -= MinPassExt;
		XMax += MinPassExt;
	}
	if (YMax - YMin < MinPassExt) {
		YMin -= MinPassExt;
		YMax += MinPassExt;
	}
	if (XMin < 0)
		XMin = 0;
		
	if (YMin < 0)
		YMin = 0;		

//  P1: XMin/YMin ausgeben (untere linke Punkt)
	wsprintf (Buffer, CountFormat, 1);
	if ((EC = ExportLine (FileHandle, Buffer)) != EC_OKAY)
		return EC;

	if ((EC = ExportLine (FileHandle, DtoeA (Buffer, XMin))) != EC_OKAY)
		return EC;
	if ((EC = ExportLineCR (FileHandle, DtoeA (Buffer, YMin))) != EC_OKAY)
		return EC;

//  P2: untere rechte Punkte
	wsprintf (Buffer, CountFormat, 2);
	if ((EC = ExportLine (FileHandle, Buffer)) != EC_OKAY)
		return EC;

	if ((EC = ExportLine (FileHandle, DtoeA (Buffer, XMax))) != EC_OKAY)
		return EC;
	if ((EC = ExportLineCR (FileHandle, DtoeA (Buffer, YMin))) != EC_OKAY)
		return EC;

//  P3: linke obere Punkte
	wsprintf (Buffer, CountFormat, 3);
	if ((EC = ExportLine (FileHandle, Buffer)) != EC_OKAY)
		return EC;
	if ((EC = ExportLine (FileHandle, DtoeA (Buffer, XMin))) != EC_OKAY)
		return EC;
	if ((EC = ExportLineCR (FileHandle, DtoeA (Buffer, YMax))) != EC_OKAY)
		return EC;

//  P4: XMax/YMax ausgeben
	wsprintf (Buffer, CountFormat, 4);
	if ((EC = ExportLine (FileHandle, Buffer)) != EC_OKAY)
		return EC;
	if ((EC = ExportLine (FileHandle, DtoeA (Buffer, XMax))) != EC_OKAY)
		return EC;
	return ExportLineCR (FileHandle, DtoeA (Buffer, YMax));
}

//  Format der Sachdaten aus Resource lesen und ausgeben
ErrCode PassPoints :: OutputFormat (Params *pP) {
	pP -> ResourceId = TIC_FORMAT;
	return Info :: OutputFormat (pP);
}

//  AttrTable --------------------------------------------------------------
//  Basisklasse für die Verwaltung der Sachdaten in einer Attributtabelle
ErrCode AttrTable :: OutputFormat (Params *pP) {
//  prüfe Parameter
	if (!pP || !pP -> pFileName)
		return EC_SYSERROR;

	char Buffer [512] = "";
	_splitpath (pP -> pFileName, NULL, NULL, Buffer, NULL);
	Buffer [FileNameSize] = '\0';
	char Buffer1 [20] = "";
	char Buffer2 [20] = "";
	lstrcpy (Buffer1, Buffer);
	ResString Text (ResID (IDS_INTERNID, pRF), 5);  // "#" lesen
	lstrcat (Buffer1, Text.Addr ());
	while (lstrlen (Buffer1) < 9)
		lstrcat (Buffer1, " ");
	lstrcpy (Buffer2, Buffer);
	Text = ResString (ResID (IDS_USERID, pRF), 80);	 // "-ID" lesen
	lstrcat (Buffer2, Text.Addr ());
	while (lstrlen (Buffer2) < 11)
		lstrcat (Buffer2, " ");

//  eigentliches Format-File lesen
	pchar pFormat = OutputResourceTemplate (pP -> ResourceId, NULL);
	if (!pFormat) {
		DELETE_VEC (pFormat);
		return EC_NOMEMORY;
	}
	wsprintf (Buffer, pFormat, Buffer1, Buffer2);

	ErrCode EC = EC_OKAY;
	if ((EC = ExportLine (pP -> FileHandle, Buffer)) != EC_OKAY) {
		DELETE_VEC (pFormat);
		return EC;
	}   
	DELETE_VEC (pFormat);

//  Namen der Merkmale ausgeben
	if (!pMDT)		  // zurück wenn Parameter nicht OK
		return EC_SYSERROR;

	long ActOut = pP -> ActOut;
	short LastLen = pP -> LastLen;
	short Count = pP -> Count;
	short TotalLen = pP -> TotalLen;
	short ActCol = pP -> ActCol;
	short Width, InWidth, Dec, Typ;


	CTable Tb (*pMDT);
	for (Tb.First (); Tb.Valid (); Tb.Next ()) {
		ExtMerkmalDescriptionLock pEMD (Tb);
		if (!pEMD)
			return EC_SYSERROR;

	//  Feldnamen ausgeben
		pchar pName = pEMD -> GetName ();
		if (!pName)
			return EC_SYSERROR;
		wsprintf (Buffer, "%-14.14s", pName);
		DELETE_VEC (pName);
		if ((EC = ExportLine (pP -> FileHandle, Buffer)) != EC_OKAY)
			return EC;

	//  Schreibspalte merken
		switch (pP -> Type) {
			case PAT:
				pEMD -> Column () = ActCol;
			break;
			case AAT:
				pEMD -> ArcColumn () = ActCol;
			break;
			default:
				return EC_SYSERROR;
		}

	//  Feldtyp u.a Parameter speichern
		switch (toupper (pEMD -> MTyp ())) {
			case 'A': {
				Width = pEMD -> MLen ();
				InWidth = Width;
				Dec = -1;
				Typ = 20;
				ActCol += Width;
			}
			break;
			case 'I': {
				Width = 4;
				InWidth = 5;
				Dec = -1;
				Typ = 50;
				ActCol += 11;
			}
			break;
			case 'F': {
				Width = 4;
				InWidth = 12;
				Dec = 3;
				Typ = 60;
				ActCol += 14;
			}
			break;
			case 'B':   // Sicht-Merkmal
			case 'C':   // Id-Merkmal
			default:
				return WC_UNKMERKMTYP;
		}
		ActOut += LastLen * LenAttrFakt;
		LastLen = Width;
		TotalLen += Width;
		wsprintf (Buffer, "%5d-1%5ld-1%4d%2d%3d-1  -1  -1-1%20d", Width, ActOut,
						  InWidth, Dec, Typ, ++Count);
		if ((EC = ExportLineCR (pP -> FileHandle, Buffer)) != EC_OKAY)
			return EC;


	}

//  im Datenformat-Kopf Parameter korrigieren
	if ((EC = SetRecordLen (pP -> FileHandle, TotalLen)) != EC_OKAY)
		return EC;
	if ((EC = SetFieldCount (pP -> FileHandle, Count)) != EC_OKAY)
		return EC;

//  Gesamtlänge neu setzen
	switch (pP -> Type) {
		case PAT:
			pMDT -> ActColumn () = ActCol;
		break;
		case AAT:
			pMDT -> ActArcColumn () = ActCol;
		break;
		default:
			return EC_SYSERROR;
	}

	return EC_OKAY;
}

//  alle Sachdaten ausgeben
ErrCode AttrTable :: OutputData (int fh, void *pData1, void *pData2,
										 void *, void *, void*) {
//  prüfe Parameter
	Params *pP = (Params *) pData1;	 	// Parameter-Struktur
	pchar pRow = (pchar) pData2;		// Ausgabe-Zeile
	if (!pMDT || !pP || !pRow)
		return EC_SYSERROR;

	ErrCode EC = EC_OKAY;			   	// Returnkode
	char Buffer [MaxColumn+1] = "";	 	// Arbeitspuffer

//  alle Sachdaten ausgeben
	pchar pBuffer = NULL;
	short MCol = 0;
	short ColWidth = 0;
	Bool DeleteMText = False;

	if (pP -> pMF && pMDT -> Count ()) { // wenn Sachdaten u. Beschr. ex.
		while (pP -> pMF -> MCode) {
		//  akt. Schreibspalte bestimmen
			switch (pP -> Type) {
				case PAT:		   // Polygon-Attribut-Tabelle
					MCol = pMDT -> FindColumn (pP -> pMF -> MCode);
				break;
				case AAT:		   // Arc-Attribut-Tabelle
					MCol = pMDT -> FindArcColumn (pP -> pMF -> MCode);
				break;
				default:			// zurück
					return EC_SYSERROR; // bei unbekannter Attribut-Tabelle
				break;
				}

		//  Spalten-Test
			if (!MCol) {		// bei ungültigem Merkmal
				pP -> pMF++;	// weiter mit nächstem Merkmal
				continue;
			}

		//  Merkmastyp bestimmen
			switch (toupper (pP -> pMF -> MTyp)) {
				case 'A': {
					pBuffer = pP -> pMF -> MText;
					if (pBuffer && *pBuffer) {
						if (pBuffer = CheckUmlaute (pBuffer))
							DeleteMText = True;
						else
							return EC_NOMEMORY;
					}
				}
				break;
				case 'I': {
					wsprintf (Buffer, "%11.11d", *(short *)(pP -> pMF -> MWert));
					pBuffer = Buffer;
				}
				break;
				case 'F':
					pBuffer = DtoeA (Buffer, *(double *)(pP -> pMF -> MWert));
				break;
				default:
					return WC_UNKMERKMTYP;
				break;
			}

		//  Text ausgeben
			ColWidth = pMDT -> FindColumnWidth (pP -> pMF -> MCode);
			if (! ColWidth)			 // bei Fehler
				return EC_SYSERROR;	 // zurück
			memcpy (pRow + MCol, pBuffer, min (lstrlen (pBuffer), ColWidth));

			pP -> pMF++;		  // nächstes Merkmal

			if (DeleteMText) {
				DeleteMText = False;
				DELETE_VEC (pBuffer);
			}

		}
	}
                                             
//  Objekt-Klasse ggf. ausgeben
	if (FourCoverages && pP -> pIdentKurzText)
	{           
	//	Schreibspalte bestimmen
		MCol = pP -> Type == PAT ? pMDT -> FindColumn (ObjKlasseMK) : 
								   pMDT -> FindArcColumn (ObjKlasseMK);	
		if (!MCol)
			return EC_SYSERROR;
		if (! (ColWidth = pMDT -> FindColumnWidth (ObjKlasseMK)))	// Spaltenweite bestimmen
			return EC_SYSERROR;					
		memcpy (pRow + MCol, pP -> pIdentKurzText, 
				min (lstrlen (pP -> pIdentKurzText), ColWidth));											
	}                                           
                                             
//  Dateiausgabe
	*(pRow + pP -> ActCol) = '\0';
	short Cnt = 0;
	for (pBuffer = pRow; pBuffer < pRow + pP -> ActCol; pBuffer += MaxColumn) {
		Cnt = min (MaxColumn, lstrlen (pBuffer));
		memcpy (Buffer, pBuffer, Cnt);
		Buffer [Cnt] = '\0';
		if ((EC = ExportLineCR (fh, Trim (Buffer))) != EC_OKAY)
			return EC;
	}

	return EC_OKAY;
}

//  PatTable ---------------------------------------------------------------
//  leeres universe polygon ausgeben
ErrCode PatTable :: OutputEmptyUniPoly (Params &Par) {
//  Dateiposition merken
	_UniPos = _llseek (Par.FileHandle, 0L, SEEK_CUR);

//  Zeile init.
	pchar pRow = new char [Par.ActCol + 1];
	if (!pRow)
		return EC_NOMEMORY;
	memset (pRow, ' ', Par.ActCol + 1);
	*pRow = '\0';

//  "leere Werte für universe Polygon ausgeben
	char Buffer [MaxColumn + 1] = "";
	DtoeA (Buffer, 0.0);
	*Buffer = '-';
	memcpy (pRow, Buffer, lstrlen (Buffer));	//  Flächeninhalt
	*Buffer = ' ';
	memcpy (pRow+14, Buffer, lstrlen (Buffer)); //  Länge
	wsprintf (Buffer, "%11ld%11ld", 1L, 0L);
	memcpy (pRow+28, Buffer, lstrlen (Buffer));

//  Dateiausgabe
	*(pRow + Par.ActCol) = '\0';
	short Cnt = 0;
	pchar pBuffer = NULL;
	ErrCode EC = EC_OKAY;
	for (pBuffer = pRow; pBuffer < pRow + Par.ActCol; pBuffer += Cnt) {
		Cnt = min (MaxColumn, lstrlen (pBuffer));
		memcpy (Buffer, pBuffer, Cnt);
		Buffer [Cnt] = '\0';
		if ((EC = ExportLineCR (Par.FileHandle, Trim (Buffer))) != EC_OKAY)
			break;
	}
	DELETE_VEC (pRow);

//  Anzahl ausgegebener Datensätze erhöhen
	_Count++;

	return EC;
}

//  universe Polygon vervollständigen
//  Section beinhaltet Bildmaße
ErrCode PatTable :: OutputFillUniPoly (int fh, Section &Sec) {
//  Uni-Dateiposition setzen
	_llseek (fh, _UniPos, SEEK_SET);

//  Berechnungs-Struktur init.
	double Lae = (2 * (Sec._Xmax - Sec._Xmin)) +
				 (2 * (Sec._Ymax - Sec._Ymin));

	double FlI = (Sec._Xmax - Sec._Xmin) * (Sec._Ymax - Sec._Ymin);
	if (FlI >= 0.0)
		FlI *= -1.0;

//  berechnete Werte ausgeben
	char Buffer [30] = "";
	ErrCode EC = EC_OKAY;
	if ((EC = ExportLine (fh, DtoeA (Buffer, FlI))) != EC_OKAY)
		return EC;
	if ((EC = ExportLine (fh, DtoeA (Buffer, Lae))) != EC_OKAY)
		return EC;

//  ans akt. Datei-Ende
	_llseek (fh, 0L, SEEK_END);

	return EC_OKAY;
}

//  Kopfzeile ausgeben
ErrCode PatTable :: OutputHead (int FileHandle, pchar pPath) {
	return Info :: OutputHead (FileHandle, pPath, IDS_PATEXT, 5, 17, 0);
}

//  Format der Sachdaten aus Resource lesen und ausgeben
ErrCode PatTable :: OutputFormat (Params *pP) {
//  prüfe Parameter
	if (!pP)
		return EC_SYSERROR;

//  weitere Werte init.
	pP -> ResourceId = PAT_FORMAT;
	pP -> Type = PAT;
	pP -> ActOut = 134;
	pP -> LastLen = 4;
	pP -> Count = 4;
	pP -> TotalLen = 16;
	pP -> ActCol = 50;

//  eigentliches Format ausgeben
	return AttrTable :: OutputFormat (pP);
}

//  Merkmalssatz ausgeben
ErrCode PatTable :: OutputData (int fh, void *pData1, void *pData2,
								void *pData3, void *pData4, void *pData5) {
	ErrCode EC = EC_OKAY;				// Return-Kode
	char Buffer [MaxColumn+1] = "";		// Arbeitspuffer
	Params Par;							// Parameter-Struktur
	Par.pMF = pData3 ? (MFELD *) pData3 : NULL;		// Merkmalsfeld
	Par.ActCol = pMDT -> ActColumn ();				// akt. Max. Länge
	Par.Type = PAT;     
	Par.pIdentKurzText = (char *) pData5;

//  neue Zeile init.
	pchar pRow = new char [Par.ActCol + 1];
	if (!pRow)
		return EC_NOMEMORY;
	memset (pRow, ' ', Par.ActCol + 1);
	*pRow = '\0';

//  Standardmerkmale ausgeben
	_Count++;										// Anzahl ausgeg. Sätze
	DtoeA (Buffer, fabs (*(double *)(pData1)));		// Flächeninhalt
	memcpy (pRow, Buffer, lstrlen (Buffer));

	double dLa = *((double *)(pData2));
	if (dLa < 0)
		dLa = 0;
	DtoeA (Buffer, dLa);			// Länge
	memcpy (pRow+14, Buffer, lstrlen (Buffer));

	long Cnt = _Count;
	if (NULL == pData3)								// bei Inseln
		Cnt = InselUserId;
	else
	{
		if (pData4 && (*(short *) pData4) == _Poly)
			Cnt--;
	}
	wsprintf (Buffer, "%11ld%11ld", _Count, Cnt);	// Satznummer und User-ID	
	memcpy (pRow+28, Buffer, lstrlen (Buffer));

//  Sachdaten ausgeben
	EC = AttrTable :: OutputData (fh, &Par, pRow, NULL, NULL, NULL);

	DELETE_VEC (pRow);

	return EC;
}

//  AatTable ---------------------------------------------------------------
//  Kopfzeile ausgeben
ErrCode AatTable :: OutputHead (int FileHandle, pchar pPath) {
	return Info :: OutputHead (FileHandle, pPath, IDS_AATEXT, 7, 28, 0);
}

//  Format der Sachdaten aus Resource lesen und ausgeben
ErrCode AatTable :: OutputFormat (Params *pP) {
//  prüfe Parameter
	if (!pP)
		return EC_SYSERROR;

//  weitere Werte init.
	pP -> ResourceId = AAT_FORMAT;
	pP -> Type = AAT;
	pP -> ActOut = 254;
	pP -> LastLen = 4;
	pP -> Count = 7;
	pP -> TotalLen = 28;
	pP -> ActCol = 80;

//  eigentliches Format ausgeben
	return AttrTable :: OutputFormat (pP);
}

//  Merkmalssatz ausgeben
ErrCode AatTable :: OutputData (int fh, void *pData1, void *,
								void *pData3, void *, void *pData5) {
	ErrCode EC = EC_OKAY;			   // Return-Kode
	char Buffer [MaxColumn+1] = "";	 // Arbeitspuffer
	Params Par;						 // Parameter-Struktur
	Par.pMF = (MFELD *) pData3;		 // Merkmalsfeld
	Par.ActCol = pMDT -> ActArcColumn ();   // akt. Max. Länge
	Par.Type = AAT;
	Par.pIdentKurzText = (char *) pData5;

//  neue Zeile init.
	pchar pRow = new char [Par.ActCol + 1];
	if (!pRow)
		return EC_NOMEMORY;
	memset (pRow, ' ', Par.ActCol + 1);
	*pRow = '\0';

//  Standardmerkmale ausgeben
	_Count++;								   // Anzahl ausgeg. Sätze
	wsprintf (Buffer, "%11d%11d%11d%11d", 0, 0, 0, 0); // Knoten
	memcpy (pRow, Buffer, lstrlen (Buffer));
	DtoeA (Buffer, * (double *)(pData1));	   // Länge
	memcpy (pRow+44, Buffer, lstrlen (Buffer));
	wsprintf (Buffer, "%11ld%11ld", _Count, _Count);	// Anzahl
	memcpy (pRow+58, Buffer, lstrlen (Buffer));

//  alle Sachdaten ausgeben
	EC = AttrTable :: OutputData (fh, &Par, pRow, NULL, NULL, NULL);

	DELETE_VEC (pRow);

	return EC;
}

// abschließende Leerzeichen löschen
pchar Trim (pchar pText) {
	if (!pText)
		return NULL;

	pchar pEnd = pText + lstrlen (pText);
	while (--pEnd >= pText && *pEnd == ' ')
		*pEnd = '\0';

	return pText;
}
