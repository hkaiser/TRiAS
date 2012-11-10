/*
File: FILEPOS.CXX
realisiert die Verwaltung von Datei-Positionen.

erarbeitet : J. Benkenstein                              Stand vom 11. Mai 1995
*/
// #hk960812: HUGE --> __HUGE
                      
#include "pheader.h"
                      
extern "C" {
	#include <memory.h>         // memset ()
	#include <limits.h>         // LONG_MAX
//	#include <toolhelp.h>       // TIMERINFO 
        #include "arctrias.hr"           // Resource-Konstanten
}

#include <hpp/filebuff.hxx>			// CFileBuffer

#define NOOPTPARAM 
#include "optparam.hxx"         // Params
#include "tools.hxx"            // Ausgabe von Geometrie/Merkmalen
#include "rechstat.hxx"         // RechercheStatus

#include "filepos.hxx"          // zugeh. Header

//  Konstanten
const short MaxDoubleFeld = 8000;		// Max. Größe eines Double-Feldes	
const long MaxVerticeCount = 16000;		// max. Anzahl von Stützpunkten

//  externe Variablen
extern FILE *yyin;                      // Eingabe-Datei
extern LineEntries *pLE;                // Linien-Tabelle
extern Params *pParams;                 // Parameter-Struktur
extern RechercheStatus *pRechStat;      // Recherche-Status
extern ResourceFile *pRF;	

// Prototypen     
Bool GetFileString (FILE *pFile, char *pBuffer, short BufferSize);

//  globale Funktionen ----------------------------------------------------
void* GetPointNr (void *pObj)   {
	return & (((PointEntry *) pObj) -> Nr ());
}

void* GetLineNr (void *pObj)    {
	return & (((LinePos *) pObj) -> Nr ());
}

void* GetPalNr (void *pObj)      {
	return & (((PalPos *) pObj) -> Nr ());
}

int CompareNrs (void *pObj1, void *pObj2) {
	long Nr1 = labs (*((long *) pObj1));
	long Nr2 = labs (*((long *) pObj2));

	if (Nr1 == Nr2)
		return 0;
	else
		if (Nr1 > Nr2)
			return 1;
		else
			return -1;
}

// PointEntry -------------------------------------------------------------
PointEntry :: PointEntry (long Nr, double &X, double &Y) {
	_Nr = Nr;
	_X = X;
	_Y = Y;
}

// Entries -----------------------------------------------------------------
Entries :: Entries (pGetKeyFcn pG, pKeyCmpFcn pK)
		 : CTree (pG, pK) {
	_ActNr = 0L;

	_StartTime = _OptmizeTime = 0;                              
	// memset (&_TI, 0, sizeof (TIMERINFO));
	// _TI.dwSize = sizeof (TIMERINFO);
}

Entries :: ~ Entries (void)
{
	// nothing to do
}

void __export Entries :: UserDelete (void *)
{
	// nothing to do
}

// Gesamte Geometrie ausgeben
Bool Entries :: OutAllGeo (void) {
	long Max = Count ();

	if (! Max)
		return True;

	OutKonvMess (isA ());

	for (long i = 1; i <= Max; i++) {
		if (OutGeo (i) == -1)
			return False;
	}

	return True;
}

//  Nutzerabbruch ?
Bool Entries :: Break (void) {
	App :: Exec (ExecWhileEvent);                                      // Steuerung an TRIAS
	return pRechStat ? pRechStat -> Break () : False;   // Status abfragen
}

//  Optimierung des Baumes ggf. durchführen:
//  Wenn für die letzte Eintragsspeicherung mehr als 10% der Zeit benötigt
//  wurde, die für eine vollst. Optimierung gebraucht wird.
void Entries :: CheckOptimize (void) {
/*
	if (TimerCount (&_TI)) {        // akt. Zeit bestimmen
		if (((_TI.dwmsSinceStart - _StartTime) / 10) > _OptmizeTime) {
			DWORD BeginOpt = _TI.dwmsSinceStart;    // Anf-Zeit merken
			Optimize ();            // Optimierung durchführen
			if (TimerCount (&_TI))                            // End-Zeit best.
				_OptmizeTime = _TI.dwmsSinceStart - BeginOpt;
		}
	}
*/

	DWORD ActTime = timeGetTime ();					// akt. Zeit
	if (((ActTime - _StartTime) / 10) > _OptmizeTime) {
		DWORD BeginOpt = timeGetTime ();    		// Anf-Zeit merken
		Optimize ();                            	// Optimierung durchführen
		_OptmizeTime = timeGetTime () - BeginOpt;	// Opt.-Zeit best.
	}
}

// PointEntries -------------------------------------------------------------
PointEntries :: PointEntries (void)
	      : Entries (GetPointNr, CompareNrs) {
}

void __export PointEntries :: UserDelete (void *pObj) {
	((PointEntry *) pObj) -> ~ PointEntry ();
}

PointEntries :: ~ PointEntries (void) {
	EveryDelete ();
}

//  neuen Punkt speichern
Bool PointEntries :: AddEntry (double &X, double &Y) {
	PointEntryCreator PPC (*this);
	_StartTime = timeGetTime ();
	PointEntry *pPP = ContCreate (PPC, PointEntry) (++_ActNr, X, Y);
	CheckOptimize ();
	if (!pPP) {
		DEX_Error (RC_PointEntriesAddEntry, EC_NOMEMORY);
		return False;
	}

	return True;
}

// Geometrie eines über "Nr" gewählten Punktes ausgeben
// von TRIAS vergebene ObjNummer zurückliefer, die im Fehlerfall -1 ist
long PointEntries :: OutGeo (long Nr) {
//  Nutzerabbruch ?
	if (Break ())
		return -1;

	CTable Tb (*this);
	if (! Tb.Find (&Nr)) {    //  wenn Objekt nicht gefunden
		DEX_Error (RC_PointEntriesOutGeo, EC_NOON);
		return -1;
	}

	PointEntryLock pPP (Tb);
	if (!pPP) {
		DEX_Error (RC_PointEntriesOutGeo, EC_LOCKERROR);
		return -1;
	}

//  Koordinaten ausgeben
	double X = (pPP -> X () + pParams -> XOffset) * pParams -> Scaling;
	double Y = (pPP -> Y () + pParams -> YOffset) * pParams -> Scaling;
	return OutputPunktLinie (&X, &Y, Nr);
}

// LineEntries -------------------------------------------------------------
LineEntries :: LineEntries (pchar pFullCoverName)
	     : Entries (GetLineNr, CompareNrs) {
	_pFile = NULL;
	_Result = True;

//  prüfe Parameter
	if (! pFullCoverName || ! *pFullCoverName) {
		DEX_Error (RC_ctLineEntries, EC_SYSERROR);
		_Result = False;
	}

//  2. Filezeiger zum lesen der Daten setzen
	if ((_pFile = fopen (pFullCoverName, "rt")) == NULL) {
		DEX_Error (RC_ctLineEntries, EC_NOFILE);
		_Result = False;
	}

//  FilePuffer erzeugen
	if (! _FileBuffer.CreateBuffer ())
	{
		DEX_Error (RC_ctLineEntries, EC_NOMEMORY);
		_Result = False;
	}

//  Dateipuffer setzen
	setvbuf (_pFile, _FileBuffer.Addr (), _IOFBF, _FileBuffer.GetSize ());
}

LineEntries :: ~ LineEntries (void) {
	if (_pFile != NULL)
		fclose (_pFile); 
	EveryDelete ();
}

void __export LineEntries :: UserDelete (void *pObj) {
	((LinePos *) pObj) -> ~LinePos ();
}

// akt. Datei-Position speichern
Bool LineEntries :: AddPos (long Pos) {
	CTable Tb (*this);
	if (! Tb.Find (&_ActNr)) {
		DEX_Error (RC_LineEntriesAddPos, EC_NOON);
		return False;
	}
	LinePos *pLP = LinePosLock (Tb);
	if (!pLP) {
		DEX_Error (RC_LineEntriesAddPos, EC_LOCKERROR);
		return False;
	}
	pLP -> Pos () = Pos;

	return True;
}

// Nummer und zugeh. Anz. Stützpunkte speichern
Bool LineEntries :: AddNrCnt (long Nr, long Cnt) {
	_ActNr = Nr;
	LinePosCreator LPC (*this);
	_StartTime = timeGetTime ();
	LinePos *pLP = ContCreate (LPC, LinePos) (_ActNr, Cnt);
	CheckOptimize ();
	if (!pLP) {
		DEX_Error (RC_LineEntriesAddNrCnt, EC_NOMEMORY);
		return False;
	}

	return True;
}

// Anzahl der Punkte lesen, bei Fehler -1
long LineEntries :: GetCnt (long Nr) {
	CTable Tb (*this);
	if (! Tb.Find (&Nr)) {
		DEX_Error (RC_LineEntriesGetCnt, EC_NOON);
		return LONG_MAX;
	}
	LinePos *pLP = LinePosLock (Tb);
	if (!pLP) {
		DEX_Error (RC_LineEntriesGetCnt, EC_LOCKERROR);
		return LONG_MAX;
	}

	return pLP -> Cnt ();
}

// Geometrie ausgeben
// Geometrie in Speicher ausgeben
// und "Cnt" dekrementiert
Bool LineEntries :: OutGeometrie (long Nr, void *pXi, void *pYi, long &ActIndex,
							      BOOL bHuge)
{
	CTable Tb (*this);
	if (! Tb.Find (&Nr)) 
	{
		DEX_Error (RC_LineEntriesOutGeom, EC_NOON);
		return False;
	}
	LinePos *pLP = LinePosLock (Tb);
	if (!pLP) 
	{
		DEX_Error (RC_LineEntriesOutGeom, EC_LOCKERROR);
		return False;
	}

//  akt. Dateiposition einstellen
	if (fseek (_pFile, pLP -> Pos (), SEEK_SET) != 0) 
	{
		DEX_Error (RC_LineEntriesOutGeom, EC_NOREAD);
		return False;
	}

//	Zeiger init.
	double *pX = bHuge ? NULL : (double *) pXi + ActIndex;
	double *pY = bHuge ? NULL : (double *) pYi + ActIndex;			
	double __HUGE *phX = bHuge ? (double __HUGE *) pXi + ActIndex : NULL;
	double __HUGE *phY = bHuge ? (double __HUGE *) pYi + ActIndex : NULL;	

	long Max = pLP -> Cnt ();
	double ActX = 0;
	double ActY = 0;
	char XBuff [30] = "";
	char YBuff [30] = "";
	long Index = 0;
	
//  alle Koordinaten in Speicher ausgeben      	
	if (Nr >= 0)
	{
		for (Index = 0; Index < Max; Index++) 
		{
		//  Daten lesen
			if (! GetFileString (_pFile, XBuff, sizeof (XBuff)) ||
		    	! GetFileString (_pFile, YBuff, sizeof (YBuff)))
			{
				DEX_Error (RC_LineEntriesOutGeom, EC_NOREAD);
				return False;
			}
			ActX = atof (XBuff);
			ActY = atof (YBuff);

		//  Daten vervollständigen
			if (bHuge)
			{
				*((double __HUGE *)phX + Index) = (ActX + pParams -> XOffset) * pParams -> Scaling;
				*((double __HUGE *)phY + Index) = (ActY + pParams -> YOffset) * pParams -> Scaling;				
			}
			else
			{
				*(pX + Index) = (ActX + pParams -> XOffset) * pParams -> Scaling;
				*(pY + Index) = (ActY + pParams -> YOffset) * pParams -> Scaling;
			}				
		}   //  for ausgeben
	}	
	else
	{	// Linie beim Ausgaben drehen
		for (Index = Max - 1; Index >= 0; Index--) 
		{
			if (! GetFileString (_pFile, XBuff, sizeof (XBuff)) ||
		    	! GetFileString (_pFile, YBuff, sizeof (YBuff)))
			{
				DEX_Error (RC_LineEntriesOutGeom, EC_NOREAD);
				return False;
			}
			ActX = atof (XBuff);
			ActY = atof (YBuff);

		//  Daten vervollständigen
			if (bHuge)
			{
				*((double __HUGE *)phX + Index) = (ActX + pParams -> XOffset) * pParams -> Scaling;
				*((double __HUGE *)phY + Index) = (ActY + pParams -> YOffset) * pParams -> Scaling;				
			}
			else
			{
				*(pX + Index) = (ActX + pParams -> XOffset) * pParams -> Scaling;
				*(pY + Index) = (ActY + pParams -> YOffset) * pParams -> Scaling;
			}				
		}   //  for ausgeben
	}		// 	Ausgabe

	ActIndex += Max;                // Index aktualisieren

	return True;
}

//  Geometrie einer vollst. Linie ausgeben
long LineEntries :: OutGeo (long Nr) {
//  Nutzerabbruch ?
	if (Break ())
		return -1;

//  Anzahl Stützpunkte lesen
	CTable Tb (*this);
	if (! Tb.Find (&Nr)) {
		DEX_Error (RC_LineEntriesOutGeo, EC_NOON);
		return -1;
	}
	LinePos *pLP = LinePosLock (Tb);
	if (!pLP) {
		DEX_Error (RC_LineEntriesOutGeo, EC_LOCKERROR);
		return -1;
	}

	long Cnt = pLP -> Cnt ();          // Anzahl Stützpunte lesen
/*	
	if (Cnt > MaxVerticeCount)
	{                       
		pParams -> NotImported++;
		if (pParams -> DebugOutput && pRF)
		{
			char Buffer [128] = "";
			ResString Error (ResID (IDS_TOMANYVERTLINE, pRF), 100);
			wsprintf (Buffer, Error.Addr (), Nr, Cnt);
			OutputDebugString (Buffer);				
		}	
		return -1;
	}		
*/	

//  Stützpunkt-Speicher anlegen
	Bool bHuge = Cnt > MaxDoubleFeld ? TRUE : FALSE;
	double *pX = NULL;
	double *pY = NULL;
	double __HUGE *phX = NULL;
	double __HUGE *phY = NULL;
		 
	if (bHuge)
	{
		phX = new __HUGE double [Cnt];
		phY = new __HUGE double [Cnt];           
		if (! phX || ! phY) 
		{
			DEX_Error (RC_LineEntriesOutGeo, EC_NOMEMORY);
			if (phX)
				delete [Cnt] (double __HUGE *) phX;
			if (phY)
				delete [Cnt] (double __HUGE *) phY;				
			return -1;
		}			
	}
	else
	{
		pX = new double [Cnt];
		pY = new double [Cnt];
		if (! pX || ! pY) 
		{
			DEX_Error (RC_LineEntriesOutGeo, EC_NOMEMORY);
            DELETE_VEC (pX);
            DELETE_VEC (pY);
			return -1;
		}
	}		
		
//  Geometrie in Speicher ausgeben
	long ActIndex = 0;
	Bool Ok = OutGeometrie (Nr, bHuge ? phX : pX, bHuge ? phY : pY, ActIndex, bHuge);

	long ObjNr = -1;
	if (Ok)		// Ausgabe an TRIAS
		ObjNr = OutputPunktLinie (bHuge ? phX : pX, bHuge ? phY : pY, Nr, Cnt, False);  
    
//	Speicher freigeben                                   
	if (bHuge)
	{
		if (phX)
			delete [Cnt] (double __HUGE *) phX;
		if (phY)
			delete [Cnt] (double __HUGE *) phY;				
	}
	else
	{                                   
		DELETE_VEC (pX);
        DELETE_VEC (pY);
	}		

	return ObjNr;
}

// PalPos -----------------------------------------------------------------
PalPos :: PalPos (long Nr, long Size, long *pArcVec) {
	_Nr = Nr;
	_Size = Size;
	_pArc = pArcVec;
}

PalPos :: ~ PalPos (void) {
        DELETE_VEC (_pArc);
}

// PalEntries -------------------------------------------------------------
PalEntries :: PalEntries (void)
			: Entries (GetPalNr, CompareNrs) {
	_First = True;
	_ActSize = _ActInd = 0;
	_pActVec = NULL;
}

void __export PalEntries :: UserDelete (void *pObj) {
	((PalPos *) pObj) -> ~PalPos ();
}

PalEntries :: ~ PalEntries (void) {
	EveryDelete ();
}

// neuen PalVektor erzeugen
Bool PalEntries ::  AddPalVektor (long Size) {
//  Test: universe Polygon ?
	if (_First) {
		_First = False;
		return True;
	}

//  neuen Vektor erzeugen
	_ActSize = Size;
	_ActInd = 0;
	if ((_pActVec = new long [_ActSize]) == NULL) {
		DEX_Error (RC_PalEntriesAddPalV, EC_NOMEMORY);
		return False;
	}

//  Vektor init.
	for (long i = 0; i < _ActSize; i++)
		*(_pActVec + i) = LONG_MAX;                              // 0 --> Insel-Eintrag

	return True;
}

//  neuen PalEintrag in akt. PalVektor speichern
Bool PalEntries :: AddPalEntry (long ArcNr) {
//  Test: universe Polygon
	if (! _pActVec)
		return True;

//  Index-Test
	if (_ActInd < 0 || _ActInd > _ActSize) {
		DEX_Error (RC_PalEntriesAddPalE, EC_SYSERROR);
		return False;
	}

//  Wert speichern
	* (_ActInd + _pActVec) = ArcNr;

	if (++_ActInd == _ActSize) {            // wenn Vektor vollst. gefüllt ist,
		PalPosCreator Pal (*this);        // speichern
		_StartTime = timeGetTime ();
		PalPos *pPP = ContCreate (Pal, PalPos) (++_ActNr, _ActSize, _pActVec);
		CheckOptimize ();
		_ActSize = _ActInd = 0;
		_pActVec = NULL;
		if (pPP == NULL) {
			DEX_Error (RC_PalEntriesAddPalE, EC_NOMEMORY);
			return False;
		}
	}

	return True;
}

// Geometrie einer bestimmten Fläche ausgeben
long PalEntries :: OutGeo (long Nr) {
//  Nutzerabbruch ?
	if (Break ())
		return -1;

//  suche zugeh. ArcVektor
	CTable Tb (*this);
	if (! Tb.Find (&Nr)) {
		DEX_Error (RC_PalEntriesOutGeo, EC_NOON);
		return -1;
	}

	PalPosLock pPP (Tb);
	if (!pPP) {
		DEX_Error (RC_PalEntriesOutGeo, EC_LOCKERROR);
		return -1;
	}

//  bestimme Größe des Konturfeldes und max. Größe des Koord-Feldes
	short KonturSize = 1;                      	// äußere Masche
	long ActNr = LONG_MAX;                    	// Akt. ArcNummer
	long SumCnt = 0;                            // Anzahl der Koordinaten
	long ActCnt = 0;                            // akt. Größe
	long PPSize = pPP -> Size ();
	long lOutCnt = 0;
	for (long i = 0; i < PPSize; i++) {
		if ((ActNr = *(pPP -> ArcVektor () + i)) == 0L) {
			KonturSize++;
			if (lOutCnt == 0)
				lOutCnt = SumCnt;
			continue;          // bei Insel-Flag weiter
		}
		if ((ActCnt = pLE -> GetCnt (ActNr)) == LONG_MAX)
			return -1;
		SumCnt += ActCnt;
	}                                
	
//  Speicher für Koord-Feld anlegen
	Bool bNoIslands = False;
	if (SumCnt > MaxVerticeCount)
	{       
	/*
		if ((lOutCnt == 0) || (lOutCnt > MaxVerticeCount))
		{                       
			pParams -> NotImported++;
			if (pParams -> DebugOutput && pRF)
			{
				char Buffer [128] = "";
				ResString Error (ResID (IDS_AUSSENKONT, pRF), 128);
				wsprintf (Buffer, Error.Addr (), Nr, lOutCnt ? lOutCnt : SumCnt);
				OutputDebugString (Buffer);				
			}	
			return -1;			// Außenkontur zu groß
		}		
	*/
		if (pParams -> DebugOutput && pRF)
		{
			char Buffer1 [128] = "";
			ResString ErrorF (ResID (IDS_FLAECHEREDUCED, pRF), 128);
			wsprintf (Buffer1, ErrorF.Addr (), Nr, SumCnt, lOutCnt, KonturSize);
			OutputDebugString (Buffer1);				
		}			                
		
		if (lOutCnt)
			SumCnt = lOutCnt;					     
		
		bNoIslands = True;											
		KonturSize = 1;			// nur äußere Masche		
	}   
		
	Bool bHuge = SumCnt > MaxDoubleFeld ? TRUE : FALSE;
	double *pX = NULL;
	double *pY = NULL;
	double __HUGE *phX = NULL;
	double __HUGE *phY = NULL;
		 
	if (bHuge)
	{
		phX = new __HUGE double [SumCnt];
		phY = new __HUGE double [SumCnt];           
		if (! phX || ! phY) 
		{
			DEX_Error (RC_PalEntriesOutGeo, EC_NOMEMORY);
			if (phX)
				delete [SumCnt] (double __HUGE *) phX;
			if (phY)
				delete [SumCnt] (double __HUGE *) phY;				
			return -1;
		}			
	}
	else
	{
		pX = new double [SumCnt];
		pY = new double [SumCnt];
		if (! pX || ! pY) 
		{
			DEX_Error (RC_PalEntriesOutGeo, EC_NOMEMORY);
            DELETE_VEC (pX);
            DELETE_VEC (pY);
			return -1;
		}
	}		

//  alle Koordinaten in Speicher ausgeben
	Bool Ok = True;
	long ActIndex = 0;
	for (ActNr = LONG_MAX, i = 0; i < PPSize; i++) {
		if ((ActNr = *(pPP -> ArcVektor () + i)) == 0L)	 // Insel ?
		{
			if (bNoIslands)
				break;
			continue;          // bei Insel-Flag weiter
		}			
		if (! (Ok = pLE -> OutGeometrie (ActNr, bHuge ? phX : pX, bHuge ? phY : pY, 
										 ActIndex, bHuge)))
			break;
	}

//  Konturfeld füllen
	long *pKonturFeld = NULL;
	if (Ok) {
		pKonturFeld = new long [KonturSize];                                    // Feld anlegen
		if (! pKonturFeld) {
			DEX_Error (RC_PalEntriesOutGeo, EC_NOMEMORY);
			Ok = False;
		} else {
			memset (pKonturFeld, 0, sizeof (long) * KonturSize);    // Feld init.
			short KonturIndex = 0;
			for (i = 0; i < PPSize; i++) {
				if ((ActNr = *(pPP -> ArcVektor () + i)) == 0L) {
					if (bNoIslands)
						break;
					KonturIndex++;                               
					continue;               // bei Insel-Flag weiter
				}
				if ((ActCnt = pLE -> GetCnt (ActNr)) == LONG_MAX) {
					Ok = False;
					break;
				}
				pKonturFeld [KonturIndex] += ActCnt;
			}
		}
	}

//  Ausgabe an TRIAS
	long ObjNr = -1;
	if (Ok)
		ObjNr = OutputFlaeche (bHuge ? phX : pX, bHuge ? phY : pY, SumCnt, 
							   KonturSize, pKonturFeld, Nr);
							   
	if ((ObjNr > 0) && bNoIslands)		// erfolgreich nur äußere Kontur
		pParams -> SubImported++;   	// importiert     		 							   
    
//	Speicher freigeben    
	if (bHuge)
	{
		if (phX)
			delete [SumCnt] (double __HUGE *) phX;
		if (phY)
			delete [SumCnt] (double __HUGE *) phY;				
	}                  
	else
	{
        DELETE_VEC (pX);
        DELETE_VEC (pY);
	}		
        DELETE_VEC (pKonturFeld);

	return ObjNr;
}


//  String aus Datei lesen    
Bool GetFileString (FILE *pFile, char *pBuffer, short MaxSize)
{
// prüfe Parameter
	if (! pFile || ! pBuffer)
		return False;

	register char Ch = ' ';
	Bool Ok = False;
	short Max = MaxSize - 1;
	for (register short i = 0; i < Max && Ok == False;) 
	{
		switch (Ch = fgetc (pFile)) 
		{               
			case '\n':              	// String-Ende
			case ' ':
			{
			       if (i == 0)       	// führende Leerz. überlesen
						continue;
			       Ok = True;
			}
			break;
			case EOF:
			{
				DEX_Error (RC_LineEntriesOutGeom, EC_NOREAD);
				return False;
			}
			case 'E':
				Max = i + 4;		// max. noch 3 Zeichen
			default: 
				pBuffer [i++] = Ch;
		}
	}
	pBuffer [i] = '\0';

	return True;
}
