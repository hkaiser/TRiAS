/*
Datei: SECTION.CXX

Basisklassen für die Erzeugung des lesbaren Arc/Info-Austausschformates.
Verarbeitung der auftretenden Section im Format.

Erarbeitet: J. Benkenstein				  Begonnen am: 30. April 1993
*/

#include "stdafx.h"               
/*XX*/ #include "TRiASArcImpl.h"

// #HK960812
	#include <float.h>	  // DBL_MAX
	#include <math.h>	   // asin ()

#include <attribs.hxx>	  // VisInfo ...
#include <impexp.hxx>	   // MF, GS ...

#include "ident.hxx"		// ExtIdentDescriptionTree

#include "section.hxx"	  // zugeh. Header
//XX#include "triasarc.hr"	   // Resource-Defines
#include "triasarc.hxx"	 // Konstanten (ArcSize)

//  Konstanten
const char pSectionFormat []	= "%10ld%10ld%10ld%10ld%10ld%10ld%10ld";
const char pPalFormat []		= "%10ld%10ld%10ld";
const char pRealFormat []	   = "% 12E";
const short RealPrecision	   = 8;		// 8 Ziffer für Exponentialausgabe
const double TextHoeFakt		= 0.0003125; // Text-Höhen-Faktor
const double TextWeitFakt	   = 0.75;	 // Textweite = 0.75 * Texthöhe
const short BufferSize = 128;
const short MaxTextSize = 80;			// max. 80 Zeichen pro Text

//  externe Variablen
extern ResourceFile *pRF;
extern double Masstab;		  // akt. Maßstab
extern ExtIdentDescriptionTree *pIDT;
extern short g_sTextTruncCnt;		 // Zähler für abgeschn. Texte	

#ifndef __NT__
#define HUGE __huge
#else
#define HUGE
#endif

//  Prototypen
ErrCode ExportLineCR (int FileHandle, pchar pLine); // Zeile in Datei mit
											// abschließendem \r\n ausgeben
ErrCode ExportLine (int FileHandle, pchar pLine); // Zeile in Datei ausgeben
pchar DtoeA (pchar pBuffer, double Wert);

//  globale Funktionen ------------------------------------------------------
//  Text in zuvor geöffnete Datei ausgeben (ohne Zeilenvorschub)
ErrCode ExportLine (int fh, pchar pText) {
//  Text ausgeben
	if (pText && *pText) {
		register short Len = lstrlen (pText);
		if (_lwrite (fh, pText, Len) != (uint) Len)
			return EC_NOSPACE;
	}

	return EC_OKAY;
}

//  Text in zuvor geöffnete Datei ausgeben (mit Zeilenvorschub)
ErrCode ExportLineCR (int fh, pchar pText) {
	char CR [3] = "\r\n";

	if (ExportLine (fh, pText) != EC_OKAY)  // Text ausgeben
		return EC_NOSPACE;

	if (_lwrite (fh, CR, 2) != 2)
		return EC_NOSPACE;

	return EC_OKAY;
}

//  Konvertiere "double" nach ASCII (scientific format)
pchar DtoeA (pchar pOutBuffer, double Value) {
	char InBuffer [10] = "";
	pchar pInBuffer = NULL;
	int Decimal = 0;
	int Sign = 0;
	pchar pOutBufferSave = pOutBuffer;

	if (!pOutBuffer)
		return NULL;

	pInBuffer = ecvt (Value, RealPrecision, &Decimal, &Sign );
	*pOutBuffer++ = Sign ? '-' : ' ';   //  Vorzeichen
	*pOutBuffer++ = *pInBuffer++;	   //  1. Ziffer
	*pOutBuffer++ = '.';				//  Punkt setzen
	while (*pOutBuffer++ = *pInBuffer++); //  alle weiteren Ziffern kopieren
	pOutBuffer--;

//  Exponent anhängen
	*pOutBuffer++ = 'E';
	if (Value)
		Decimal--;
	*pOutBuffer++ = Decimal >= 0 ? '+' : '-';

	itoa (Decimal, InBuffer, 10);
	pInBuffer = InBuffer;
	if (*pInBuffer == '-')		  // Vorzeichen wurde schon gespeichert
		pInBuffer++;
	if (lstrlen (pInBuffer) < 2)
		*pOutBuffer++ = '0';

	*pOutBuffer = '\0';

	lstrcat (pOutBufferSave, pInBuffer);

	return pOutBufferSave;
}

//  Section -----------------------------------------------------------------
Section :: Section (void) {
	_Xmax = _Ymax = 0;
	_Xmin = _Ymin = DBL_MAX;
}

//  Bildmasse ggf. korrigieren
inline
void Section :: SetXYcon (double &X, double &Y) {
//  X-Koordinaten korr.
	if (X < _Xmin) _Xmin = X;
	if (X > _Xmax) _Xmax = X;

//  Y-Koordinaten korr.
	if (Y < _Ymin) _Ymin = Y;
	if (Y > _Ymax) _Ymax = Y;
}

// an Hand der veränderten Bildmasse wird entschieden, ob eine
// Section Daten gespeichert hat
Bool Section :: hasData (void) {
	if (_Xmax != 0 || _Ymax != 0
	   || _Ymin != DBL_MAX || _Xmin != DBL_MAX)
		return True;
	else
		return False;
}

//  Fußzeile in zuvor geöffnete und positionierte Datei ausgeben
ErrCode Section :: OutputFoot (int FileHandle) {
	char Buffer [80] = "";
	wsprintf (Buffer, pSectionFormat, -1L,0L,0L,0L,0L,0L,0L);
	return ExportLineCR (FileHandle, Buffer);
}

//  ArcSection --------------------------------------------------------------
//  Kopfzeile in zuvor geöffnete und positionierte Datei ausgeben
ErrCode ArcSection :: OutputHead (int FileHandle) {
	ResString Head (ResID (IDS_ARCHEAD, pRF), 10);
	return ExportLineCR (FileHandle, (pchar) Head.Addr ());
}

//  Daten in zuvor geöffnete und positionierte Datei ausgeben.
//  Internen Zähler erhöhen.
ErrCode ArcSection :: OutputData (int fh, GSTRUCT &GS, NodePolyNr &NP,
								  long Count, long AktIndex) {
	register ErrCode EC = EC_OKAY;		  // Rückkehrwert
	char Buffer [80] = "";				  // Arbeitspuffer

//  Daten-Kopf ausgeben
	wsprintf (Buffer, pSectionFormat, _ActNumber, _ActNumber,
			  NP.FirstNode, NP.LastNode, NP.LeftPoly, NP.RightPoly, Count);
	if ((EC = ExportLineCR (fh, Buffer)) != EC_OKAY)
		return EC;

//  alle Koordinaten ausgeben
	long MaxIndex = Count + AktIndex;
	short PointCount = 0;
	for (long i = AktIndex; i < MaxIndex; i++) {
		if ((EC = ExportLine (fh, DtoeA (Buffer, ((double HUGE *)GS.x)[i]))) != EC_OKAY)
			return EC;
		if ((EC = ExportLine (fh, DtoeA (Buffer, ((double HUGE *)GS.y)[i]))) != EC_OKAY)
			return EC;
		SetXYcon (((double HUGE *)GS.x)[i], ((double HUGE *)GS.y)[i]); // Bildmaße ggf. korr.

	//  neue Zeile ?
		if (++PointCount == 2) { // nur 2. Punkte je Zeile
			PointCount = 0;
			if ((EC = ExportLineCR (fh, "")) != EC_OKAY)
				return EC;
		}
	}

//  ggf. letzte \r\n setzen
	if (PointCount == 1) {
			if ((EC = ExportLineCR (fh, "")) != EC_OKAY)
				return EC;
	}

	_ActNumber++;	   // internen Zähler erhöhen
	return EC;
}

//  TexteSection --------------------------------------------------------------
//  Kopfzeile in zuvor geöffnete und positionierte Datei ausgeben
ErrCode TexteSection :: OutputHead (int FileHandle) {
	ResString Head (ResID (IDS_TXTHEAD, pRF), 10);
	return ExportLineCR (FileHandle, (pchar) Head.Addr ());
}

//  Daten in zuvor geöffnete und positionierte Datei ausgeben.
ErrCode TexteSection :: OutputData (int fh, GSTRUCT &GS, pchar pText) {
//  prüfe externe Parameter
	if (!pIDT)
		return EC_SYSERROR;

//  prüfe Parameter
	if (!pText || !*pText)
		return EC_OKAY;

//	hat Text mehr als 80 Zeichen ?
	if (lstrlen (pText) > MaxTextSize)
	{
		g_sTextTruncCnt++;				  // Fehlerhafte Anzahl speichern
		pText [MaxTextSize] = '\0';		  // Text abschneiden	
	}

	register ErrCode EC = EC_OKAY;		  // Rückkehrwert
	char Buffer [80] = "";				  // Arbeitspuffer

//  Daten-Kopf ausgeben: 2 --> Text in Grenzen einpassen
	wsprintf (Buffer, "%10d%10d%10d%10d%10d", 1,2,0,1,lstrlen (pText));
	if ((EC = ExportLineCR (fh, Buffer)) != EC_OKAY)
		return EC;

//  Koordinaten und Höhe berechnen;
	double Hoehe = 0.0;
	if ((EC = pIDT -> FindTextHoehe (GS.Id, Hoehe)) != EC_OKAY)
		return EC;

	if (Masstab)
		Hoehe *= Masstab * TextHoeFakt;

//  Winkel lesen
	double Winkel = 0.0;
	if ((EC = pIDT -> FindTextDrehWinkel (GS.Id, Winkel)) != EC_OKAY)
		return EC;
	Winkel *= -1.0;	 // negativen --> positiven Drehsinn	 

//  Endkoordinaten berechnen
	double Xe, Ye;
	if (Masstab) {
		double BogenMassFaktor  = asin (1.0) / 90.0;
		double Lae = Hoehe * TextWeitFakt * lstrlen (pText);
		Xe = GS.x [0] + (Lae * (cos (BogenMassFaktor * Winkel)));
		Ye = GS.y [0] + (Lae * (sin (BogenMassFaktor * Winkel)));
	} else {
		Xe = Ye = 0.0;	  // berechnet Arc/Info selbst
	}

//  X-Koordinaten ausgeben: Anfang und Ende
	if ((EC = ExportLine (fh, DtoeA (Buffer, GS.x [0]))) != EC_OKAY)
			return EC;
	if ((EC = ExportLine (fh, DtoeA (Buffer, Xe))) != EC_OKAY)
			return EC;

//  2 Real-Nullwerte ausgeben
	register short i = 0;
	for (i = 1; i <= 2; i++) {
		if ((EC = ExportLine (fh, DtoeA (Buffer, 0.0))) != EC_OKAY)
			return EC;
	}

//  Y-Koordinaten ausgeben: Anfang und Ende
	if ((EC = ExportLineCR (fh, DtoeA (Buffer, GS.y [0]))) != EC_OKAY)
			return EC;
	if ((EC = ExportLine (fh, DtoeA (Buffer, Ye))) != EC_OKAY)
			return EC;

//  8 weitere Real-Nullwerte ausgeben
	for (i = 1; i <= 8; i++) {
		if ((EC = ExportLine (fh, DtoeA (Buffer, 0.0))) != EC_OKAY)
			return EC;
		if (i == 4) {   // neue Zeile beginnen
			if ((EC = ExportLineCR (fh, "")) != EC_OKAY)
				return EC;
		}
	}

//  Texthöhe ausgeben
	if ((EC = ExportLineCR (fh, DtoeA (Buffer, Hoehe))) != EC_OKAY)
		return EC;

//  Text-Parameter-Ende ausgeben
	if ((EC = ExportLineCR (fh, DtoeA (Buffer, -0.01))) != EC_OKAY)
		return EC;

//  min. und max. Bildgröße ggf. korrigieren
	SetXYcon (GS.x [0], GS.y [0]);
	if (Masstab)
	{
		Ye += Hoehe;
		SetXYcon (Xe, Ye);
	}

//  Textwert ausgeben
	return ExportLineCR (fh, pText);
}

//  LabelSection --------------------------------------------------------------
//  Kopfzeile in zuvor geöffnete und positionierte Datei ausgeben
ErrCode LabelSection :: OutputHead (int FileHandle) {
	ResString Head (ResID (IDS_LABHEAD, pRF), 10);
	return ExportLineCR (FileHandle, (pchar) Head.Addr ());
}

//  Fußzeile in zuvor geöffnete und positionierte Datei ausgeben
ErrCode LabelSection :: OutputFoot (int FileHandle) {
	char Buffer [30] = "";
	wsprintf (Buffer, "%10d%10d", -1, 0);
	ErrCode EC = EC_OKAY;
	if ((EC = ExportLine (FileHandle, Buffer)) != EC_OKAY)
		return EC;

	if ((EC = ExportLine (FileHandle, DtoeA (Buffer, 0.0))) != EC_OKAY)
		return EC;

	return ExportLineCR (FileHandle, Buffer);
}

//  Daten in zuvor geöffnete und positionierte Datei ausgeben.
ErrCode LabelSection :: OutputData (int fh, double &X, double &Y, short Offset){
	register ErrCode EC = EC_OKAY;		  // Rückkehrwert
	char Buffer [25] = "";				  // Arbeitspuffer

//  Daten-Kopf ausgeben
	wsprintf (Buffer, "%10ld%10ld", _ActNumber, _ActNumber + Offset);
	if ((EC = ExportLine (fh, Buffer)) != EC_OKAY)
		return EC;

//  3 mal X/Y-Koordinaten ausgeben
	for (register i = 1; i <= 3; i++) {
		if ((EC = ExportLine (fh, DtoeA (Buffer, X))) != EC_OKAY)
			return EC;
		if ((EC = ExportLine (fh, DtoeA (Buffer, Y))) != EC_OKAY)
			return EC;
		if (i == 1) {   // neue Zeile beginnen ?
			if ((EC = ExportLineCR (fh, "")) != EC_OKAY)
				return EC;
		}
	}

//  min. und max. Bildgröße ggf. korrigieren
	SetXYcon (X, Y);

	_ActNumber++;	// internen Zähler erhöhen

	return ExportLineCR (fh, "");		// wieder auf neue Zeile
}

//  InfoSection --------------------------------------------------------------
//  Kopfzeile in zuvor geöffnete und positionierte Datei ausgeben
ErrCode InfoSection :: OutputHead (int FileHandle) {
	ResString Head (ResID (IDS_INFOHEAD, pRF), 10);
	return ExportLineCR (FileHandle, (pchar) Head.Addr ());
}

//  Fußzeile in zuvor geöffnete und positionierte Datei ausgeben
ErrCode InfoSection :: OutputFoot (int FileHandle) {
	ResString Head (ResID (IDS_INFOFOOT, pRF), 10);
	return ExportLineCR (FileHandle, (pchar) Head.Addr ());
}

//  CoverSection --------------------------------------------------------------
//  Kopfzeile in zuvor geöffnete und positionierte Datei ausgeben
ErrCode CoverSection :: OutputHead (int FileHandle) {
	ResString Head (ResID (IDS_COVERHEAD, pRF), 10);
	return ExportLineCR (FileHandle, (pchar) Head.Addr ());
}

//  Fußzeile in zuvor geöffnete und positionierte Datei ausgeben
ErrCode CoverSection :: OutputFoot (int FileHandle) {
	ResString Head (ResID (IDS_COVERFOOT, pRF), 10);
	return ExportLineCR (FileHandle, (pchar) Head.Addr ());
}

//  PalSection --------------------------------------------------------------
//  Kopfzeile in zuvor geöffnete und positionierte Datei ausgeben
ErrCode PalSection :: OutputHead (int FileHandle) {
	ResString Head (ResID (IDS_PALHEAD, pRF), 10);
	return ExportLineCR (FileHandle, (pchar) Head.Addr ());
}

ErrCode PalSection :: OutputDataHead (int fh, Section &Sec, long Count) {
	register ErrCode EC = EC_OKAY;
	char Buffer [20] = "";

//  Anzahl der Polygone ausgeben
	wsprintf (Buffer, "%10ld", Count);
	if ((EC = ExportLine (fh, Buffer)) != EC_OKAY)
		return EC;

//  Xmin, Ymin, Xmax und Ymax ausgeben
	if ((EC = ExportLine (fh, DtoeA (Buffer, Sec._Xmin))) != EC_OKAY)
		return EC;
	if ((EC = ExportLine (fh, DtoeA (Buffer, Sec._Ymin))) != EC_OKAY)
		return EC;
	if ((EC = ExportLine (fh, DtoeA (Buffer, Sec._Xmax))) != EC_OKAY)
		return EC;
	return ExportLineCR (fh, DtoeA (Buffer, Sec._Ymax));
}

//  ggf. Zeilenvorschub
ErrCode PalSection :: OutputLastCR (int fh, short &Cnt) {
	if (Cnt) {
		Cnt = 0;
		return ExportLineCR (fh, NULL);
	}

	return EC_OKAY;
}

//  alle 2 Ausgaben Zeilenvorschub
ErrCode PalSection :: _OutputCR (int fh, short &Cnt) {
	if (++Cnt >= 2) {
		Cnt = 0;
		return ExportLineCR (fh, NULL);
	}

	return EC_OKAY;
}

//	Inseltopologie an Maschentopologie anhängen 
ErrCode PalSection :: OutputTopologie (int fhd, int fhs)
{
	if ((fhd <= 0) || (fhs <= 0))
		return EC_ILLPARS;

	ErrCode EC = EC_OKAY;

//	Datei pos.
	if (HFILE_ERROR == _llseek (fhs, 0L, SEEK_SET))  // Inseldatei an den Anfang
		return EC_NOFILE;

//	ggf. letzten Zeilenvorschub
	OutputLastCR (fhd, _MainCnt);

//	Dateien umkop.
	uint ReadCount = 0;
	char Buffer [BufferSize] = "";
	do {
		ReadCount = _lread (fhs, Buffer, BufferSize);
		if (_lwrite (fhd, Buffer, ReadCount) != ReadCount)
			return (EC = EC_NOSPACE);
	} while (ReadCount > 0);

//	Zeilenzähler akt.
	_MainCnt = _IslandCnt;
	_IslandCnt = 0;

	return EC;
}

//	Datenkopf für Insel (als Masche) ausgeben
ErrCode PalSection :: OutputDataHead (int fh, double *pX, double *pY, long lCnt, BOOL bIsland) 
{
	if (!pX || !pY || (lCnt <= 0) || (fh <= 0))
		return EC_ILLPARS;

	register ErrCode EC = EC_OKAY;

//  Zeilenzähler rücksetzen
	OutputLastCR (fh, bIsland ? _IslandCnt : _MainCnt);		//  ggf. Zeilenvorschub

//  berechne Anzahl der Mascheneinträge; beachte max. Größe einer Masche
	short sCnt = (short) (lCnt / ArcSize);
	if (lCnt % ArcSize)
		sCnt++;
	
//  berechne Container der Masche
	double dXmin, dYmin, dXmax, dYmax;
	dXmin = dYmin = DBL_MAX;
	dXmax = dYmax = 0;

	for (long i = 0; i < lCnt; i++)  
	{
		if (dXmin > ((double HUGE *)pX)[i])
			dXmin = ((double HUGE *)pX)[i];
		if (dYmin > ((double HUGE *)pY)[i])
			dYmin = ((double HUGE *)pY)[i];
		if (dXmax < ((double HUGE *)pX)[i])
			dXmax = ((double HUGE *)pX)[i];
		if (dYmax < ((double HUGE *)pY)[i])
			dYmax = ((double HUGE *)pY)[i];
	}

//  Count und Container ausgeben
	CntSection Sec;
	Sec.XMin () = dXmin;
	Sec.YMin () = dYmin;
	Sec.XMax () = dXmax;
	Sec.YMax () = dYmax;
	EC = OutputDataHead (fh, Sec, sCnt);
	return EC;
}

//  Anzahl wird über "GS" berechnet
ErrCode PalSection :: OutputDataHead (int fh, GSTRUCT &GS) {
	register ErrCode EC = EC_OKAY;

//  Zeilenzähler rücksetzen
	OutputLastCR (fh, _MainCnt);		//  ggf. Zeilenvorschub

//  berechne Anzahl aller Mascheneinträge; beachte max. Größe einer Masche
	short Cnt = 0;
	Bool Island = False;			// äußere Masche ist keine Insel
	long *pCount = GS.cnt;
	
//  für alle Maschen                
	for (long i = 0; *pCount; i += *pCount, pCount++) {
	//  prüfe Parameter der zu erwartenden Flächen
		if ((*pCount < 4)							   							// min. Punktanzahl
			|| (((double HUGE *)GS.x)[i] != ((double HUGE *)GS.x)[i+*pCount-1])	// AnfPkt == EndPkt ?
			|| (((double HUGE *)GS.y)[i] != ((double HUGE *)GS.y)[i+*pCount-1]))
				continue;

	//  Inseltest
		if (!Island)				// wenn keine
			Island = True;		  	// dann aber alle folgenden
		else
			Cnt++;				  	// Insel mit führ. Nulleintrag

		Cnt += (short) (*pCount / ArcSize);
		if (*pCount % ArcSize)
			Cnt++;
	}

//  berechne Container der äußeren Masche
	_Xmin = _Ymin = DBL_MAX;
	_Xmax = _Ymax = 0;

	for (long j = 0; j < GS.GSize; j++) 
	{
		if (_Xmin > ((double HUGE *)GS.x)[j])
			_Xmin = ((double HUGE *)GS.x)[j];
		if (_Ymin > ((double HUGE *)GS.y)[j])
			_Ymin = ((double HUGE *)GS.y)[j];
		if (_Xmax < ((double HUGE *)GS.x)[j])
			_Xmax = ((double HUGE *)GS.x)[j];
		if (_Ymax < ((double HUGE *)GS.y)[j])
			_Ymax = ((double HUGE *)GS.y)[j];
	}

//  Count und Container ausgeben
	return OutputDataHead (fh, *this, Cnt);
}

//  "normale" Insel ausgeben
ErrCode PalSection :: OutputMainIsland (int fh, NodePolyNrList *pNL) {
	return _OutputIsland (fh, pNL, _MainCnt);
}

//  Insel für universe polygon ausgeben
ErrCode PalSection :: OutputUniIsland (int fh, NodePolyNrList *pNL) {
	if (!pNL)
		return EC_NOMEMORY;
	_PolyCnt += pNL -> Count () + 1;	// für Insel + 1
	return _OutputIsland (fh, pNL, _UniCnt);
}

//  Insel ausgeben
ErrCode PalSection :: _OutputIsland (int fh, NodePolyNrList *pNL, short &RowCnt) {
//  Parameter-Test
	if (!pNL)
		return EC_SYSERROR;

	char Buffer [40] = "";
	register ErrCode EC = EC_OKAY;

//  Null-Satz ausgeben
	wsprintf (Buffer, pPalFormat, 0L, 0L, 0L);
	if ((EC = ExportLine (fh, Buffer)) != EC_OKAY)
		return EC;
	if ((EC = _OutputCR (fh, RowCnt)) != EC_OKAY)
		return EC;

//  alle Daten ausgeben
	CRing Ri (*pNL);
	if (pNL -> DrehSinn ()) {   // math. positiver Drehsinn
		for (Ri.First (); Ri.Valid (); Ri.Next ()) {
			NodePolyNrLock NC (Ri);
			if (!NC)
				return EC_SYSERROR;
			wsprintf (Buffer, pPalFormat, NC -> ArcNr, NC -> FirstNode,
										  NC -> LeftPoly);
			if ((EC = ExportLine (fh, Buffer)) != EC_OKAY)
				return EC;
			if ((EC = _OutputCR (fh, RowCnt)) != EC_OKAY)
				return EC;
		}
	} else {					// im Uhrzeigersinn
		for (Ri.Last (); Ri.Valid (); Ri.Prev ()) {
			NodePolyNrLock NC (Ri);
			if (!NC)
				return EC_SYSERROR;
			wsprintf (Buffer, pPalFormat, NC -> ArcNr * -1L, NC -> FirstNode,
										  NC -> RightPoly);
			if ((EC = ExportLine (fh, Buffer)) != EC_OKAY)
				return EC;
			if ((EC = _OutputCR (fh, RowCnt)) != EC_OKAY)
				return EC;
		}
	}

	return EC_OKAY;
}

//  äußere Masche ausgeben
ErrCode PalSection :: OutputAussMasche (int fh, NodePolyNrList *pNL, BOOL bIsland) {
//  Parameter-Test
	if (!pNL)
		return EC_SYSERROR;

	char Buffer [40] = "";
	register ErrCode EC = EC_OKAY;

	short &ActCnt = bIsland ? _IslandCnt : _MainCnt;

//  alle Daten ausgeben
	CRing Ri (*pNL);
	if (!pNL -> DrehSinn ()) {		  // im Uhrzeigersinn gedreht
		for (Ri.First (); Ri.Valid (); Ri.Next ()) {
			NodePolyNrLock NC (Ri);
			if (!NC)
				return EC_SYSERROR;
			wsprintf (Buffer, pPalFormat, NC -> ArcNr, NC -> LastNode,
										  NC -> LeftPoly);
			if ((EC = ExportLine (fh, Buffer)) != EC_OKAY)
				return EC;
			if ((EC = _OutputCR (fh, ActCnt)) != EC_OKAY)
				return EC;
		}
	} else {							// math. pos. Richtung
		for (Ri.Last (); Ri.Valid (); Ri.Prev ()) {
			NodePolyNrLock NC (Ri);
			if (!NC)
				return EC_SYSERROR;
			wsprintf (Buffer, pPalFormat, NC -> ArcNr * -1L, NC -> LastNode,
										  NC -> RightPoly);
			if ((EC = ExportLine (fh, Buffer)) != EC_OKAY)
				return EC;
			if ((EC = _OutputCR (fh, ActCnt)) != EC_OKAY)
				return EC;
		}
	}

	return EC_OKAY;
}

//  Verwaltung der Daten für die Knoten-Polygon-Nummern-Liste
//  NodePolyNrList ---------------------------------------------------------
NodePolyNrList :: NodePolyNrList (Bool DrehSinn)
				: CListContainer () {
	_DrehSinn = DrehSinn;
}

NodePolyNrList :: ~ NodePolyNrList (void) {
	EveryDelete ();
}

void EXPORTFLT NodePolyNrList :: UserDelete (void *pObj) {
	((NodePolyNr *) pObj) -> ~NodePolyNr ();
}

// True, wenn neuer Eintrag in Liste gespeichert, sonst False
Bool NodePolyNrList :: Add (NodePolyNr &NP) {
	NodePolyNrCreator NL_Cr (*this);
//XX	return Create (NL_Cr, NodePolyNr) (NP) ? True : False;
/*XX*/	return ContCreate (NL_Cr, NodePolyNr) (NP) ? True : False;
}

//  NodePolyNr ------------------------------------------------------------
NodePolyNr :: NodePolyNr (NodePolyNr &NP) {
	FirstNode = NP.FirstNode;
	LastNode = NP.LastNode;
	LeftPoly = NP.LeftPoly;
	RightPoly = NP.RightPoly;
	ArcNr = NP.ArcNr;
}

//  CntSection --------------------------------------------------------------
//  Kopfzeile in zuvor geöffnete und positionierte Datei ausgeben
ErrCode CntSection :: OutputHead (int FileHandle) {
	ResString Head (ResID (IDS_CNTHEAD, pRF), 10);
	return ExportLineCR (FileHandle, (pchar) Head.Addr ());
}

//  Schwerpunkt-Koordinaten der Fläche ausgeben
ErrCode CntSection :: OutputData (int fh, double &Xs, double &Ys) {
	char Buffer [20] = "";
	register ErrCode EC = EC_OKAY;

	wsprintf (Buffer, "%10ld", 0L);
	if ((EC = ExportLine (fh, Buffer)) != EC_OKAY)
		return EC;

	if ((EC = ExportLine (fh, DtoeA (Buffer, Xs))) != EC_OKAY)
		return EC;

	return ExportLineCR (fh, DtoeA (Buffer, Ys));
}

//  Schwerpunkt-Koordinaten aus übergebenem Container berechnen
//  und ausgeben
ErrCode CntSection :: OutputData (int fh, Section &S) {
	double Xs = S._Xmin + ((S._Xmax - S._Xmin) / 2);
	double Ys = S._Ymin + ((S._Ymax - S._Ymin) / 2);
	return OutputData (fh, Xs, Ys);
}
