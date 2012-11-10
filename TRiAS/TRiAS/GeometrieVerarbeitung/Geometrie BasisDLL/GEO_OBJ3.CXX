// Weitere Methoden für Elementarobjekte EKante
// File: GEO_OBJ3.CXX
// W. Mörtl

#include "GeometrP.hxx"

#include "cliplist.hxx"

#include <TRiASHelper.h>	// tagPIFLAGS in progstat.h
#include <registrx.hxx>		// CCurrentUser
#include "progstat.h"		// BaseProgressStatus


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



// --------------------------------------------------------------------------------------------------
// Methoden für ElementarObjekt: EKANTE
// Memberfunktionen
// Punkt(e) hinzufügen
// lLen > 0 Punkte werden vor Stützpunktnummer -1 <= lIndex <= _Size eingefügt;
// wenn lIndex == -1 bzw. _Size, dann werden Punkte am Ende angehangen
void _GEOMETR_EXPORT EKante :: AddPunkt (PunktVec* pPV, long lLen, long lIndex)
{
	_ASSERTE (pPV != 0);
	_ASSERTE (lLen > 0);
	_ASSERTE (lIndex >= -1);
	_ASSERTE (lIndex <= _Size);

	if (lIndex == -1)				// ans Ende anhängen
		lIndex = _Size;
	if (lLen == 0 ||
	    lIndex < 0 || lIndex > _Size) // ungültige Werte
	{
		DEX_Error (RC_AddPunkt, EC_ILLPARS);
		MessageBox (__hWndM, "Fehlerhafter Parameter in Routine EKante::AddPunkt", "Achtung:", MB_ICONEXCLAMATION | MB_OK);
		return;						// nichts einfügen
	}

PunktVec* pNewSPF = new PunktVec (_Size+lLen);

	if (! pNewSPF)
	{
		DEX_Error (RC_AddPunkt, EC_NOMEMORY);
		return;      
	}
	for (long i = 0; i < lIndex; i++)
		(*pNewSPF)[i] = SP(i);          // Beginn kopieren
	for (long j = 0; j < lLen; i++, j++)
		(*pNewSPF)[i] = (*pPV)[j];      // Einfügen
	for (j = lIndex; i < _Size + lLen; i++, j++)
		(*pNewSPF)[i] = SP(j);
	DELETE_OBJ (_SPF);
	_Size += lLen;
	_SPF = pNewSPF;
} // AddPunkt


// --------------------------------------------------------------------------------------------
// Aus den Vektoren x[] bzw. y[] der Länge lCnt werden die Koordinaten vom Anfangsindex lAnfId
// bis einschließlich zum Endindex lEndId in die this-Kante vor Stützpunktnummer
// -1 <= lIndex <= _Size eingefügt; wenn lIndex == -1 bzw. _Size, dann werden die Koordinaten
// am Ende angehangen; für den Fall, daß die Vektoren geschlossen sind, d.h. x[0] == x[lCnt-1]
// und y[0] == y[lCnt-1], werden für lAnfId > lEndId die Koorinaten x[lCnt-1] und y[lCnt-1]
// nicht übernommen
HRESULT _GEOMETR_EXPORT EKante :: AddPunkt (KoOrd x[], KoOrd y[], long lCnt, long lAnfId,
											long lEndId, long lIndex)
{
	_ASSERTE (x != 0);
	_ASSERTE (y != 0);

// Punktefolge ist geschlossen (true) oder offen (false)
bool bClosed = (x[0] == x[lCnt-1] && y[0] == y[lCnt-1]);

// bAnfEnd == true, wenn die Parameter lAnfId und lEndId so gesetzt sind, daß die Abarbeitung
// der Punktefolge über den Endpunkt hinaus gehen bzw. vor dem Anfangspunkt fortgesetzt werden
// müßte, sonst false
bool bAnfEnd = (lAnfId > lEndId);

	if (-1 == lIndex)
		lIndex = _Size;					// neue Koordinaten ans Ende anhängen

	if (lAnfId < 0 || lAnfId >= lCnt ||	// ungültige Parameter
	    lEndId < 0 || lEndId >= lCnt ||
		lIndex < 0 || lIndex > _Size ||
	    (!bClosed && bAnfEnd))			// Linie nicht geschlossen obwohl Anfangsindex > Endindex
	{
		DEX_Error (RC_AddPunkt, EC_ILLPARS);
		return E_INVALIDARG;
	}

long lLen;		// Anzahl der zu übernehmende Punkte

if (bAnfEnd)    // zu übernehmende Punktefolge geht über Anfangs/Endpunkt hinweg
	lLen = lCnt - lAnfId + lEndId;
else
	lLen = lEndId - lAnfId + 1;

PunktVec* newSPF = new PunktVec (_Size + lLen);

	if (0 == newSPF)
	{
		DEX_Error (RC_geo_obj3, EC_NOMEMORY);
		return E_OUTOFMEMORY;      
	}

long i, j;

	for (i = 0; i < lIndex; i++)
		(*newSPF)[i] = SP(i);					// Beginn kopieren

	for (j = lAnfId; j <= lEndId; i++, j++)
	{
		(*newSPF)[i].X() = x[j];				// Einfügen
		(*newSPF)[i].Y() = y[j];
	}

	for (j = lIndex; i < _Size + lLen; i++, j++)// Rest kopieren
		(*newSPF)[i] = SP(j);

	DELETE_OBJ (_SPF);
	_Size += lLen;
	_SPF = newSPF;

	return S_OK;

} // AddLinePart


// --------------------------------------------------------------------------------------------
// Die Punkte vom Anfangsindex lAnfId bis einschließlich zum Endindex lEndId der Kontur pML
// werden vor Stützpunktnummer -1 <= lIndex <= _Size eingefügt; wenn lIndex == -1 bzw. _Size,
// dann werden Punkte am Ende angehangen; für den Fall, daß die Kontur geschlossen ist, d.h.
// pML[VekL-1] == pML[0], wird pML[VekL-1] nicht übernommen, wenn lAnfId > lEndId gilt
void _GEOMETR_EXPORT EKante :: AddKonturTeil (MarkLine* pML, long lAnfId, long lEndId,
											  long lIndex)
{
	_ASSERTE (pML != 0);
	_ASSERTE (lAnfId >= 0);
	_ASSERTE (lEndId >= 0);
	_ASSERTE (lIndex >= -1);
	_ASSERTE (lIndex <= _Size);

	if (! pML) return;
	
long VekL = pML->ADP();    // Konturlänge

// bAnfEnd == true, wenn die Parameter lAnfId und lEndId so gesetzt sind, daß die Abarbeitung
// der Punktefolge über den Endpunkt hinaus gehen bzw. vor dem Anfangspunkt fortgesetzt werden
// müßte, sonst false
bool bAnfEnd = (lAnfId > lEndId);

	if (lIndex == -1)	// ans Ende anhängen
		lIndex = _Size;
	if (lAnfId < 0 || lAnfId >= VekL ||		// ungültige Parameter
	    lEndId < 0 || lEndId >= VekL ||
	    lIndex < 0 || lIndex > _Size ||
	    (!pML->IsClosed() && bAnfEnd))		// Kontur nicht geschlossen obwohl Anfangsindex > Endindex
	{
		DEX_Error (RC_AddKonturTeil, EC_ILLPARS);
		MessageBox (__hWndM, "Fehlerhafter Parameter in Routine EKante::AddKonturTeil", "Achtung:", MB_ICONEXCLAMATION | MB_OK);
		return;										// nichts einfügen
	}

long lLen;   // Anzahl der zu übernehmende Punkte

	if (bAnfEnd)    // zu übernehmende Punktefolge geht über Anfangs/Endpunkt hinweg
		lLen = VekL - lAnfId + lEndId;
	else
		lLen = lEndId - lAnfId + 1;

PunktVec* pNewSPF = new PunktVec (_Size+lLen);

	if (! pNewSPF)
	{
		DEX_Error (RC_AddKonturTeil, EC_NOMEMORY);
		return;      
	}
	for (long i = 0; i < lIndex; i++)       // Beginn kopieren
		(*pNewSPF)[i] = SP(i);

long j = lAnfId;
long lAW;       // Abbruchwert von j in while-Schleife

	(lEndId < VekL-1) ? (lAW = lEndId + 1) : (lAW = 0);

	do                            // Einfügen
	{
		// pML [VekL-1] nicht einfügen, wenn bAnfEnd == true
		if (bAnfEnd == false || j != VekL-1)
		{
			(*pNewSPF)[i] = pML->SP(j);
			i++;
		}
		(j < VekL-1) ? (j++) : (j = 0);
	}
	while (j != lAW);

	for (j = lIndex; i < _Size+lLen; i++, j++)      // Rest kopieren
		(*pNewSPF)[i] = SP(j);

	DELETE_OBJ (_SPF);
	_Size += lLen;
	_SPF = pNewSPF;
	
} // AddKonturTeil


// --------------------------------------------------------------------------------------------
// Die Punkte vom Anfangsindex lAnfId bis einschließlich zum Endindex lEndId aus dem
// Punkt-Vektor pPt werden an das Ende der this-EKante angehangen; für MD == MOVEDIR_UP wird die
// zu übernehmende Punktefolge aufsteigend, sonst absteigend durchlaufen; wenn der Punktvektor
// geschlossen ist, d.h. pPt[lVekL-1] == pPt[0] gilt, und die Parameter MD, lAnfId und lEndId
// so gesetzt sind, daß der gemeinsame Anfangs/Endpunkt mit übernommen werden muß, wird
// pPt[lVekL-1] übergangen
void _GEOMETR_EXPORT EKante :: AddKantenStueck1 (PunktVec* pPt, long lAnfId, long lEndId,
												 MoveDir MD)
{
	_ASSERTE (pPt != 0);
	_ASSERTE (lAnfId >= 0);
	_ASSERTE (lEndId >= 0);

long lVekL = pPt->VekL();

	_ASSERTE (lAnfId < lVekL);
	_ASSERTE (lEndId < lVekL);
 
	if (! pPt ||						// ungültige Parameter
		lAnfId < 0 || lAnfId >= lVekL ||
	    lEndId < 0 || lEndId >= lVekL)
	{
		DEX_Error (RC_AddKantenStueck, EC_ILLPARS);
		MessageBox (__hWndM, "Fehlerhafter Parameter in Routine EKante::AddKantenStueck1/I", "Achtung:", MB_ICONEXCLAMATION | MB_OK);
		return;							// nichts anhängen
	}
	
// pPt geschlossen (true) oder offen (false)
bool bClosed = (*pPt)[lVekL-1] == (*pPt)[0];

// bAnfEnd == true, wenn die Parameter MD, lAnfId und lEndId so gesetzt sind, daß die
// Abarbeitung der Punktefolge über den Endpunkt hinaus gehen bzw. vor dem Anfangspunkt
// fortgesetzt werden müßte, sonst false
bool bAnfEnd = (MOVEDIR_UP == MD && lAnfId > lEndId) ||
				(MOVEDIR_DOWN == MD && lAnfId < lEndId);

	_ASSERTE (bClosed || !bAnfEnd);

	if (!bClosed && bAnfEnd)	// Punktvektor nicht geschlossen
	{
		DEX_Error (RC_AddKantenStueck, EC_ILLPARS);
		MessageBox (__hWndM, "Fehlerhafter Parameter in Routine EKante::AddKantenStueck1/II", "Achtung:", MB_ICONEXCLAMATION | MB_OK);
		return;							// nichts anhängen
	}

long lLen;   // Anzahl der zu übernehmenden Punkte

	if (bAnfEnd)    // zu übernehmende Punktefolge geht über Anfangs/Endpunkt hinweg
		lLen = lVekL - labs (lEndId - lAnfId);
	else
		lLen = labs(lEndId - lAnfId) + 1;

PunktVec* pNewSPF = new PunktVec (_Size+lLen);

	if (! pNewSPF)
	{
		DEX_Error (RC_AddKantenStueck, EC_NOMEMORY);
		return;      
	}
	for (long i = 0; i < _Size; i++)        // this-EKante kopieren
		(*pNewSPF)[i] = SP(i);

long j = lAnfId;
long lAW;       // Abbruchwert von j in do-while-Schleife

	if (MOVEDIR_UP == MD)		// Punktefolge wird aufsteigend durchlaufen
		(lEndId < lVekL-1) ? (lAW = lEndId + 1) : (lAW = 0);
	else			// Punktefolge wird absteigend durchlaufen
		(lEndId > 0) ? (lAW = lEndId - 1) : (lAW = lVekL - 1);

	do                    // Punktefolge anhängen
	{
		// (*pPt) [lVekL-1] nicht einfügen, wenn bAnfEnd == true
		if (bAnfEnd == false || j != lVekL-1)
		{
			(*pNewSPF)[i] = (*pPt)[j];
			i++;
		}
		if (MOVEDIR_UP == MD)		// Punktefolge wird aufsteigend durchlaufen
			(j < lVekL-1) ? (j++) : (j = 0);
		else			// Punktefolge wird absteigend durchlaufen
			(j > 0) ? (j--) : (j = lVekL-1);
	}
	while (j != lAW);

	DELETE_OBJ (_SPF);
	_Size += lLen;
	_SPF = pNewSPF;

} // AddKantenStueck1


// --------------------------------------------------------------------------------------------
// wie AddKantenStueck1, nur für MarkLine statt PunktVec
void _GEOMETR_EXPORT EKante :: AddKantenStueck2 (MarkLine* pML, long lAnfId, long lEndId,
												 MoveDir MD)
{
	_ASSERTE (pML != 0);
	_ASSERTE (lAnfId >= 0);
	_ASSERTE (lEndId >= 0);

long lVekL = pML->ADP();

	_ASSERTE (lAnfId < lVekL);
	_ASSERTE (lEndId < lVekL);
 
	if (! pML ||						// ungültige Parameter
		lAnfId < 0 || lAnfId >= lVekL ||
	    lEndId < 0 || lEndId >= lVekL)
	{
		DEX_Error (RC_AddKantenStueck, EC_ILLPARS);
		MessageBox (__hWndM, "Fehlerhafter Parameter in Routine EKante::AddKantenStueck2/I", "Achtung:", MB_ICONEXCLAMATION | MB_OK);
		return;							// nichts anhängen
	}
	
// pML geschlossen (true) oder offen (false)
bool bClosed = pML->IsClosed();

// bAnfEnd == true, wenn die Parameter MD, lAnfId und lEndId so gesetzt sind, daß die
// Abarbeitung der Punktefolge über den Endpunkt hinaus gehen bzw. vor dem Anfangspunkt
// fortgesetzt werden müßte, sonst false
bool bAnfEnd = (MOVEDIR_UP == MD && lAnfId > lEndId) ||
				(MOVEDIR_DOWN == MD && lAnfId < lEndId);

	_ASSERTE (bClosed || !bAnfEnd);

	if (!bClosed && bAnfEnd)		// Punktvektor nicht geschlossen
	{
		DEX_Error (RC_AddKantenStueck, EC_ILLPARS);
		MessageBox (__hWndM, "Fehlerhafter Parameter in Routine EKante::AddKantenStueck2/II", "Achtung:", MB_ICONEXCLAMATION | MB_OK);
		return;						// nichts anhängen
	}

long lLen;   // Anzahl der zu übernehmenden Punkte

	if (bAnfEnd)    // zu übernehmende Punktefolge geht über Anfangs/Endpunkt hinweg
		lLen = lVekL - labs (lEndId - lAnfId);
	else
		lLen = labs(lEndId - lAnfId) + 1;

PunktVec* pNewSPF = new PunktVec (_Size+lLen);

	if (! pNewSPF)
	{
		DEX_Error (RC_AddKantenStueck, EC_NOMEMORY);
		return;      
	}
	for (long i = 0; i < _Size; i++)        // this-EKante kopieren
		(*pNewSPF)[i] = SP(i);

long j = lAnfId;
long lAW;       // Abbruchwert von j in do-while-Schleife

	if (MOVEDIR_UP == MD)		// Punktefolge wird aufsteigend durchlaufen
		(lEndId < lVekL-1) ? (lAW = lEndId + 1) : (lAW = 0);
	else			// Punktefolge wird absteigend durchlaufen
		(lEndId > 0) ? (lAW = lEndId - 1) : (lAW = lVekL - 1);

	do                    // Punktefolge anhängen
	{
		// (*pML) [lVekL-1] nicht einfügen, wenn bAnfEnd == true
		if (bAnfEnd == false || j != lVekL-1)
		{
			(*pNewSPF)[i] = pML->SP(j);
			i++;
		}
		if (MOVEDIR_UP == MD)	// Punktefolge wird aufsteigend durchlaufen
			(j < lVekL-1) ? (j++) : (j = 0);
		else					// Punktefolge wird absteigend durchlaufen
			(j > 0) ? (j--) : (j = lVekL-1);
	}
	while (j != lAW);

	DELETE_OBJ (_SPF);
	_Size += lLen;
	_SPF = pNewSPF;

} // AddKantenStueck2


// --------------------------------------------------------------------------------------------
// Punkt(e) löschen
// lLen > 0 Punkte werden ab Stützpunktnummer 0 <= lIndex < _Size gelöscht;
// wenn lLen > _Size-lIndex, werden ab lIndex alle restlichen Punkte gelöscht
void _GEOMETR_EXPORT EKante :: SubPunkt (long lLen, long lIndex)
{
	_ASSERTE (lLen > 0);
	_ASSERTE (lIndex >= 0);
	_ASSERTE (lIndex < _Size);
	
	if (lLen > _Size-lIndex) lLen = _Size - lIndex;
	if (lLen < 0 || lIndex < 0 || lIndex > _Size-1)
	{
		DEX_Error (RC_SubPunktKante, EC_ILLPARS);
		MessageBox (__hWndM, "Fehlerhafter Parameter in Routine EKante::SubPunkt", "Achtung:", MB_ICONEXCLAMATION | MB_OK);
		return;
	}


// Punkte löschen (durch Auslassen beim Umkopieren)
PunktVec* pNewSPF = new PunktVec (_Size-lLen);

	if (! pNewSPF)
	{
		DEX_Error (RC_SubPunktKante, EC_NOMEMORY);
		return;      
	}

long i = 0;

	while (i < lIndex)
	{
		(*pNewSPF)[i] = SP(i);		// Beginn kopieren
		i++;
	}

	while (i < _Size-lLen)
	{
		(*pNewSPF)[i] = SP(i+lLen);	// Rest kopieren
		i++;
	}

	DELETE_OBJ (_SPF);
	_Size -= lLen;
	_SPF = pNewSPF;
} // SubPunkt


//---------------------------------------------------------------------------------------------
// Test auf Geometriefehler
// Doppelpunkt liegt vor (true), wenn der Abstand zum nachfolgenden Punkt höchstens
// dEps (in Meter) beträgt, sonst false;
// dpUF ist der Transformationsfaktor, mit dessen Hilfe ein in Metern vorgegebener Wert in x-
// bzw. y-Richtung multipliziert werden muß, um auf Datenbank-Verhältnisse zu kommen;
// i und j sind die Indizes des Punktepaares (j ist optional; fehlt j, wird j=i-1 gesetzt);
// in bNull wird zurückgegeben, ob der Abstand exakt 0 m beträgt (true) oder nicht (false)
bool _GEOMETR_EXPORT EKante :: isDoppel (bool& bNull, double dEps, DoublePair dpUF,
										 bool bMetric, long i, long j)
{
	if (j == -1) j = i - 1;
	if (i < 0 || j < 0 || i >= _Size || j >= _Size || _Size < 2 ||
		i == j)
		return false;

	if (bMetric)	// metrische Datenbank
	{
	double dAbstDB = AbstandPktPktE (SP(i), SP(j));

		(0 == dAbstDB) ? (bNull = true) : (bNull = false);
		return (dAbstDB <= dpUF.X() * dEps ||
				dAbstDB <= 2.*dGlEps);
	}

	// geodätische Datenbank
	_ASSERTE (dpUF.X() > 0.);
	_ASSERTE (dpUF.Y() > 0.);

// seit 12.01.99 Unterscheidung in dAbstDB und dAbstM
double dAbstDB = AbstandPktPktE (SP(i), SP(j));	// Abstand in Datenbank-Verhältnissen

double dx = (SP(j).X() - SP(i).X()) / dpUF.X();	// aus Datenbank-Verhältnissen zurück
double dy = (SP(j).Y() - SP(i).Y()) / dpUF.Y();	// zu Werten in Metern
double dAbstM = sqrt (dx*dx + dy*dy);			// Abstand in Meter

	(0 == dAbstDB) ? (bNull = true) : (bNull = false);
	return (dAbstM <= dEps ||
			dAbstDB <= 2.*dGlEps);
} // isDoppel


// --------------------------------------------------------------------------------------------
// 2 hintereinanderliegende Strecken (Schenkel) einer Kante bzw. Flächenkontur bilden eine
// Spitze (return-Wert "true"), wenn gilt:
//   - der Winkel, den die beiden Strecken bilden <= dSpEps
//   - einer der beiden Basispunkte liegt am anderen Schenkel näher als dGlEps (13.11.98).
// i, j und k sind die Indizes des Punktetripels (j und k sind optional, fehlen sie, wird j=i-1
// und k=j-1 gesetzt);
// In bNull wird zurückgegeben, ob der Winkel exakt 0° beträgt (true) oder nicht (false).
bool _GEOMETR_EXPORT EKante :: isSpitz (bool& bNull, double dSpEps, long i, long j, long k)
{
	bNull = false;	// der Winkel ist (vorerst) > 0°

	if (_Size < 3) return false;

	// mit dem nachfolgenden Test wird überprüft, ob eine aus 3 Stützpunkten bestehende Kante
	// geschlossen ist;
	// die in diesem Fall vorliegende Spitze soll NICHT als Spitze diagnostiziert werden,
	// da sonst der Spitzen-Stützpunkt und nachfolgend einer der beiden identischen Basispunkte
	// gelöscht werden, wodurch die Kante unnötigerweise zu einem Punkt entarten würde;
	// sinnvoller ist es, die Spitze zu ignorieren und durch isDoppel einen der beiden
	// identischen Basispunkte zu löschen, wodurch die ursprüngliche 3-punktige Kante auf eine
	// 2-punktige reduziert wird und damit nicht entartet (08.07.98)
	if (3 == _Size &&
		SP(0).X() == SP(_Size-1).X() && SP(0).Y() == SP(_Size-1).Y())	// Kante geschlossen
		return false;

	if (j == -1) j = i - 1;
	if (k == -1) k = j - 1;

	if (i < 0 || j < 0 || k < 0 || i >= _Size || j >= _Size || k >= _Size ||
		i == j || i == k || j == k)		// 08.07.98
		return false;

	// wenn die beiden Basispunkte P1 und P3 gleich sind, ist bei P2 eine Spitze
	if (SP(i).X() == SP(k).X() && SP(i).Y() == SP(k).Y())
	{
		bNull = true;	// der Winkel hat exakt 0°
		return true;
	}

	// es muß gelten P1 != P2 und P2 != P3 (06.01.98)
	if (!MittVergl (SP(i), SP(j), SP(k), 0))
		return false;

// Es muß auch folgender Fall abgefangen werden: Der Winkel ist zwar nicht kleiner als dSpEps,
// aber einer der beiden Basispunkte liegt am anderen Schenkel näher als dGlEps. Das soll auch
// als Spitze gelten, weil sonst zum Überlappungstest (bei dem ebenfalls mit dGlEps gearbeitet
// wird) Widersprüche entstehen. (13.11.98)
double dAbst;

	if (LotStrecke (SP(i), SP(j), SP(k), dAbst) && dAbst < dGlEps)
		return true;

	if (LotStrecke (SP(k), SP(j), SP(i), dAbst) && dAbst < dGlEps)
		return true;

double d1x = SP(j).X() - SP(i).X();
double d1y = SP(j).Y() - SP(i).Y();
double d2x = SP(j).X() - SP(k).X();
double d2y = SP(j).Y() - SP(k).Y();

double hw2 = d1x*d2x+d1y*d2y;
double hw3 = cos(dSpEps*Pi/180.)*sqrt((d1x*d1x+d1y*d1y)*(d2x*d2x+d2y*d2y));

	// mit dem Test hw2 >= hw3 werden sowohl der Winkel dSpEps als auch der Winkel 360°-dSpEps
	// geprüft, da für den Test für 360°-dSpEps nur i und k vertauscht werden müßten, was
	// nur zum Vertauschen von d1x (d1y) mit d2x (d2y) führen würde: also nichts Neues im
	// Westen
	return (hw2 >= hw3);

} // isSpitz


//--------------------------------------------------------------------------------------------
// Kollinearität zwischen 3 aufeinanderfolgenden Punkten (true), sonst false;
// i, j und k sind die Indizes des Punktetripels (j und k sind optional,
// fehlen sie, wird j=i-1 und k=j-1 gesetzt)
bool _GEOMETR_EXPORT EKante :: isKoll (long i, long j, long k)
{
	if (_Size < 3) return false;

	if (j == -1) j = i-1;
	if (k == -1) k = j-1;


	if (i < 0 || j < 0 || k < 0 || i >= _Size || j >= _Size ||
		k >= _Size || i == j || i == k || j == k)
		return false;

// die 3 Punkte müssen paarweise verschieden sein
bool hw1 = PaarVergl (SP(i), SP(j), SP(k), 0);
bool hw2 = Kollinear (SP(i), SP(j), SP(k));

	return (hw1 && hw2);
} // isKoll


//--------------------------------------------------------------------------------------------
// Test auf Selbstüberschneidung (return-Wert: true), sonst false, mit Rückgabewert Fo
//   KEINE      keine Selbstüberschneidung, GP1 und GP2 unbestimmt
//   ECHT       echte Überschneidung, GP1 enthält Schnittpunkt, GP2 unbestimmt
//   RAND       Strecken berühren sich in jeweils genau einem Stützpunkt, GP1 enthält
//              Berührungspunkt, GP2 unbestimmt
//   INNEN      Randpunkt der einen Strecke liegt im "Inneren" der anderen Strecke
//              GP1 enthält Berührungspunkt, GP2 unbestimmt
//   UEBERLAPP  Strecken liegen teilweise oder vollständig übereinander, GP1 und GP2
//              sind die beiden Endpunkte des gemeinsamen Bereiches
bool _GEOMETR_EXPORT EKante :: isSelbInz (Strecke& S1, EPunkt& AP, EPunkt& EP, long j, long jj,
										  EPunkt& GP1, EPunkt& GP2, SchnittErg& Fo)
{
	_ASSERTE (j >= 0);
	_ASSERTE (jj >= 0);

DoublePair DP1, DP2;

	Fo = GemeinsamePunkte (S1.AP(), S1.EP(), AP, EP, DP1, DP2);

	if (KEINE == Fo) return false;

	GP1.X() = DtoL (DP1.X());
	GP1.Y() = DtoL (DP1.Y());
	GP2.X() = DtoL (DP2.X());
	GP2.Y() = DtoL (DP2.Y());

	// für Randpunkt- und Innenberührungen sind noch zusätzliche Untersuchungen notwendig;
	// damit Selbstüberschneidungen nicht mehrfach diagnostiziert werden, werden unter
	// bestimmten Bedingungen einige Selbstüberschneidungen zu "keine Selbstüberschneidung"
	// umdefiniert
	if (RAND == Fo || INNEN == Fo)
	{
	bool bGeschl = SP(0) == SP(_Size-1);	// Kante geschlossen (true) oder offen (false)

		// Randpunktberührungen werden i.a. 4-mal (am Anfang bzw. Ende einer offenen Kante 2-mal),
		// Innenberührungen i.a. 2-mal (am Anfang bzw. Ende einer offenen Kante 1-mal) erkannt,
		// wobei i.a. nur der Fall GP1 == SP(j+1) && GP1 == SP(jj+1) als der einzig relevante
		// angesehen wird; damit wird auch ausgeschlossen, daß die normale Kantenfortsetzung
		// bzw. das Geschlossensein der Kante als scheinbare Wiederholungspunkte (Fo == RAND)
		// diagnostiziert werden

		// mit der nachfolgenden if-Anweisung wird erst noch der Fall abgefangen, daß eine
		// Rand- bzw. Innenberührung am Anfang einer offenen Kante vorliegt; das Ende einer
		// offenen Kante braucht nicht extra abgetestet zu werden, da die Testungen ja sowieso
		// auf die Streckenendpunkte S1.EP() bzw. SP(jj+1) orientiert sind 
		if (!bGeschl && GP1 == SP(0))
			if ((RAND == Fo && GP1 == SP(jj+1)) || INNEN == Fo)	// (#WM021212)
				return true;

		if (GP1 == SP(j) || GP1 == SP(jj))
		{
			Fo = KEINE;
			return false;
		}

	// Randpunkt- bzw. Innenberührungen am Rande von Überlappungsbereichen sollen neben der
	// Überlappung nicht extra ausgewiesen werden
	bool bEj = true;	// es gibt noch ein Pj2
	bool bEjj = true;	// es gibt noch ein Pjj2
	EPunkt Pj2, Pjj2;	// i.a. SP(j+2) bzw. SP(jj+2)

		if (j < _Size-2)
			Pj2 = SP(j+2);
		else
		{
			if (bGeschl) Pj2 = SP(1);
			else bEj = false;	// es gibt kein Pj2 mehr, da Kante offen und j == _Size-2
		}
		if (jj < _Size-2)
			Pjj2 = SP(jj+2);
		else
		{
			if (bGeschl) Pjj2 = SP(1);
			else bEjj = false;
		}
			
		if (RAND == Fo)    // Randpunktberührung
		{
			if ((bEjj &&        Kollinear (SP(j), SP(j+1), Pjj2)) ||
				(bEj && bEjj && Kollinear (SP(j+1), Pj2, Pjj2)) ||
				(bEj &&         Kollinear (SP(jj), SP(jj+1), Pj2)) ||
				(bEj && bEjj && Kollinear (SP(jj+1), Pjj2, Pj2)))
			{
				Fo = KEINE;
				return false;
			}
		}
		else				// Innenberührung, d.h. Fo == INNEN
		{
		// Bei Innenberührung muß unterschieden werden, ob Endpunkt der j-Strecke innerhalb der
		// jj-Strecke liegt (GP1 == SP(j+1) oder Endpunkt der jj-Strecke innerhalb der
		// j-Strecke (GP1 == SP(jj+1)
			if ((bEj && GP1 == SP(j+1) && Kollinear (SP(jj), SP(jj+1), Pj2)) ||
				(bEjj && GP1 == SP(jj+1) && Kollinear (SP(j), SP(j+1), Pjj2)))
			{
				Fo = KEINE;
				return false;
			}
		}
	}

	return true;

} // isSelbInz


// --------------------------------------------------------------------------------------------
// Umlaufsinn einer geschlossenen Kante ist mathematisch positiv (true) bzw. negativ (false)
bool _GEOMETR_EXPORT EKante :: GetTurning (void)
{
	_ASSERTE (SP(0) == SP(_Size-1));

	if (PolygonArea() > 0)
		return true;
	return false;

} // GetTurning


//-------------------------------------------------------------------------------------------------
// Richtung einer Kante umorientieren
void _GEOMETR_EXPORT EKante :: OrientDreh (void)
{
	for (long i = 0; i < _Size/2; i++)
	{
	KoOrd x = SP(_Size-i-1).X();
	KoOrd y = SP(_Size-i-1).Y();

		SP(_Size-i-1).X() = SP(i).X();
		SP(_Size-i-1).Y() = SP(i).Y();
		SP(i).X() = x;
		SP(i).Y() = y;
	}
} // OrientDreh


// --------------------------------------------------------------------------------------------
// Punkt einer Stützpunktfolge mit der kleinsten x-Koordinate unter allen Punkten mit der
// kleinsten y-Koordinate bestimmen; Rückgabe des Punktindex
long _GEOMETR_EXPORT EKante :: IndTiefsterPunkt (void)
{
KoOrd xmin = LONG_MAX;
KoOrd ymin = LONG_MAX;
long lIndex = 0;

	for (long i = 0; i < _Size; i++)
	{
		if (SP(i).Y() < ymin)
		{
			xmin = SP(i).X();
			ymin = SP(i).Y();
			lIndex = i;
		}
		if (SP(i).Y() == ymin && SP(i).X() < xmin)
		{
			xmin = SP(i).X();
			lIndex = i;
		}
	}

	return lIndex;

} // IndTiefsterPunkt


// --------------------------------------------------------------------------------------------
// Umordnen der Stützpunktfolge einer geschlossenen Kante bzw. Flächenkontur, (true), so daß
// der neue Anfangspunkt der Punkt mit der kleinsten x-Koordinate unter allen Punkten mit der
// kleinsten y-Koordinate ist; bei offener Kante bzw. unzureichendem Speicherplatz Rückgabe von
// false
bool _GEOMETR_EXPORT EKante :: Umordnen (void)
{
	if (!(SP(0) == SP(_Size-1)))		// Kante nicht geschlossen
		return false;

long AnfIndex = IndTiefsterPunkt();	// bisheriger Index des neuen Anfangspunktes
PunktVec* pUmgeoK = new PunktVec (_Size);

	if (pUmgeoK == 0)
	{
		DEX_Error (RC_geo_obj3, EC_NOMEMORY);
		return false;      
	}
	for (long i = AnfIndex; i < _Size-1; i++)
		(*pUmgeoK)[i-AnfIndex] = SP(i);
	for (i = 0; i <= AnfIndex; i++)
		(*pUmgeoK)[i+_Size-AnfIndex-1] = SP(i);
	DELETE_OBJ (_SPF);
	_SPF = pUmgeoK;

	return true;

} // Umordnen


// --------------------------------------------------------------------------------------------
// Berechnet den vorzeichenbehafteten Inhalt einer geschlossenen Kante, der bei einem Fehler
// gleich 0 ist (programmiert von J. Benkenstein)
//   Inhalt > 0 --> Verlauf der Kante im math. positiven Drehsinn
//   Inhalt < 0 --> negativer Drehsinn
//   Formel: Anfangswert + Summe über alle x(n) * (y(n+1) - y(n-1)) von n = 1
// 	  bis Anzahl Punkte (AP) - 2, mit den Punkten P0, P1, ... P(AP-1) und
//	  dem Anfangswert = x(AP-1) * (y1 - y(AP-2))
double _GEOMETR_EXPORT EKante :: PolygonArea (CoordTransX* pCT)
{
// teste Parameter der Kante
    if (SP(0) != SP(_Size-1) ||		// wenn AnfPkt verschieden EndPkt oder
		_Size < 3)					// zu wenig Punkte, dann
		return 0;					// mit ungültigem Wert zurück

	if (! pCT)
	{
	// berechne Anfangswert des Flächeninhalts
	double dFl = (double)SP(_Size-1).X() * (double)(SP(1).Y() - SP(_Size-2).Y());

	// berechne Summe
		if (_Size >= 3)	// mindestens 3 Stützpunkte	
			for (long i = 1; i < _Size - 1; i++)
				dFl += (double)SP(i).X() * (double)(SP(i+1).Y() - SP(i-1).Y());

		return (dFl / 2.);        // Inhalt halbieren und zurück
	}


// Berechnung mit CoordTransX pCT (H. Kaiser)
// berechne Anfangswert des Flächeninhalts
DoublePair DP1, DP2, DP3;

LPVOID pCTFData = 0;
double Fl = 0.0;

	if (pCT->GetMetricParam (SP(1), &pCTFData)) {
	// Koordinatentransformation an erstem Punkt orientieren
		pCT->MetricEx (SP(_Size-1), &DP1.X(), &DP1.Y(), pCTFData);
		pCT->MetricEx (SP(1), &DP2.X(), &DP2.Y(), pCTFData);
		pCT->MetricEx (SP(_Size-2), &DP3.X(), &DP3.Y(), pCTFData);
	
		Fl = DP1.X() * (DP2.Y() - DP3.Y());

	// berechne Summe
		for (long i = 1; i < _Size - 1; i++) {
			pCT->MetricEx (SP(i), &DP1.X(), &DP1.Y(), pCTFData);
			pCT->MetricEx (SP(i+1), &DP2.X(), &DP2.Y(), pCTFData);
			pCT->MetricEx (SP(i-1), &DP3.X(), &DP3.Y(), pCTFData);
		
			Fl += DP1.X() * (DP2.Y() - DP3.Y());
		}
		
		if (pCTFData) pCT->FreeMetricParam (pCTFData);
	}
	else
	{
		pCT->Metric (SP(_Size-1), &DP1.X(), &DP1.Y());
		pCT->Metric (SP(1), &DP2.X(), &DP2.Y());
		pCT->Metric (SP(_Size-2), &DP3.X(), &DP3.Y());
		
		Fl = DP1.X() * (DP2.Y() - DP3.Y());

	// berechne Summe
		for (long i = 1; i < _Size - 1; i++) {
			pCT->Metric (SP(i), &DP1.X(), &DP1.Y());
			pCT->Metric (SP(i+1), &DP2.X(), &DP2.Y());
			pCT->Metric (SP(i-1), &DP3.X(), &DP3.Y());
			
			Fl += DP1.X() * (DP2.Y() - DP3.Y());
		}
	}

	return (Fl / 2.);	// Inhalt halbieren und zurück

} // PolygonArea


// --------------------------------------------------------------------------------------------
// Test, ob bei Berührung zweier Kanten ein unmittelbarer Seitenwechsel erfolgt oder nicht;
// dabei bedeutet unmittelbarer Seitenwechsel, daß die eine Kante sofort (nicht erst nach einer
// Überlappungsstrecke) auf der gegenüberliegenden Seite der anderen Kante fortgeführt wird,
// also ein echte Überschneidung und nicht nur eine Berührung erfolgt. Am Ende einer offenen
// Kante liegt per Definition kein Seitenwechsel vor.
// j bzw. jj sind die Indizes der Stützpunkte der this- bzw. pKt-EKante, GP ist der gemeinsame
// Punkt und Fo kennzeichnet eine Randpunkt- (Fo == RAND) bzw. Innenberührung (Fo == INNEN).
// return-Werte sind
//   true    Seitenwechsel, d. h. Schnitt
//   false   kein Seitenwechsel, d. h. Berührung
bool EKante :: Seitenwechsel (EKante* pKt, long j, long jj, DoublePair GP, SchnittErg& Fo)
{
	_ASSERTE (pKt != 0);
	_ASSERTE (j >= 0);
	_ASSERTE (jj >= 0);
	_ASSERTE (Fo == RAND || Fo == INNEN);

	// Mit den beiden nachfolgenden if-Bedingungen wird der Fall ausgeschlossen, daß auf
	// Seitenwechsel am Ende einer offenen Kante getestet wird.
	if (SP(0) != SP(_Size-1) &&			// this-EKante offen
		(SP(0).EpsGleich (GP) ||		// Anfangs- bzw.
		SP(_Size-1).EpsGleich (GP)))	// Endpunkt ist der gemeinsame Punkt
		return false;	// am Ende einer offenen Kante liegt kein Seitenwechsel vor

long lKL = pKt->ASP();

	if (pKt->SP(0) != pKt->SP(lKL-1) &&		// pKt-EKante offen
		(pKt->SP(0).EpsGleich (GP) ||
		pKt->SP(lKL-1).EpsGleich (GP)))
		return false;


EPunkt Pj0, Pj1, Pjj0, Pjj1, Pj2, Pjj2;

	if (SP(j+1).EpsGleich (GP))
	{
		Pj0 = SP(j);
		Pj1 = SP(j+1);
		(j < _Size-2) ? (Pj2 = SP(j+2)) : (Pj2 = SP(1));
	}
	else if (SP(j).EpsGleich (GP))
	{
		(j > 0) ? (Pj0 = SP(j-1)) : (Pj0 = SP(_Size-2));
		Pj1 = SP(j);
		Pj2 = SP(j+1);
	}
	else	// kann nur bei Fo == INNEN auftreten
	{
		_ASSERTE (Fo == INNEN);

		Pj0 = SP(j);
		Pj1 = SP(j+1);
	}

	if (pKt->SP(jj+1).EpsGleich (GP))
	{
		Pjj0 = pKt->SP(jj);
		Pjj1 = pKt->SP(jj+1);
		(jj < lKL-2) ? (Pjj2 = pKt->SP(jj+2)) : (Pjj2 = pKt->SP(1));
	}
	else if (pKt->SP(jj).EpsGleich (GP))
	{
		(jj > 0) ? (Pjj0 = pKt->SP(jj-1)) : (Pjj0 = pKt->SP(lKL-2));
		Pjj1 = pKt->SP(jj);
		Pjj2 = pKt->SP(jj+1);
	}
	else	// kann nur bei Fo == INNEN auftreten
	{
		_ASSERTE (Fo == INNEN);

		Pjj0 = pKt->SP(jj);
		Pjj1 = pKt->SP(jj+1);
	}


double qwj1, qwj2, qwjj1, qwjj2;	// Quasi-Winkel von Strecken mit der Waagrechten

	qwj1 = QuasiWinkel (GP.X(), GP.Y(), Pj0.X(), Pj0.Y());
	qwjj1 = QuasiWinkel (GP.X(), GP.Y(), Pjj0.X(), Pjj0.Y());

	// wegen der nicht mehr zu ertragenden Dreckeffekte der Digitalgeometrie kann eine
	// scheinbare Innenberührung in Wirklichkeit eine Randpunktberührung sein (06.11.98)
	if (INNEN == Fo && Pj1.EpsGleich (GP) && Pjj1.EpsGleich (GP))
		Fo = RAND;

	if (RAND == Fo)	// Randpunktberührung
	{
		qwj2 = QuasiWinkel (GP.X(), GP.Y(), Pj2.X(), Pj2.Y());
		qwjj2 = QuasiWinkel (GP.X(), GP.Y(), Pjj2.X(), Pjj2.Y());
	}
	else			// Innenberührung
	{
		// Bei Innenberührung muß unterschieden werden, ob Endpunkt von this-Strecke innerhalb
		// der pKt-Strecke liegt oder Endpunkt von pKt-Strecke innerhalb der this-Strecke
		if (Pj1.EpsGleich (GP))	// Endpunkt von this-Strecke innerhalb der pKt-Strecke
		{
			qwj2 = QuasiWinkel (GP.X(), GP.Y(), Pj2.X(), Pj2.Y());
			qwjj2 = QuasiWinkel (GP.X(), GP.Y(), Pjj1.X(), Pjj1.Y());
		}
		else    // Endpunkt von pKt-Strecke innerhalb der this-Strecke
		{
			qwj2 = QuasiWinkel (GP.X(), GP.Y(), Pj1.X(), Pj1.Y());
			qwjj2 = QuasiWinkel (GP.X(), GP.Y(), Pjj2.X(), Pjj2.Y());
		}
	}

	// der gemeinsame Punkt signalisiert keine echte Randpunkt- bzw. Innenberührung sondern
	// ist der Endpunkt eines Überlappungsbereiches
	if (qwj1 == qwjj1 || qwj1 == qwjj2 ||
		qwj2 == qwjj1 || qwj2 == qwjj2)
	{
		Fo = UEBERLAPP;
		return false;
	}

// ???????????????????????????????????????????????????????????????????????????????????????????????????????
// Nun sitze ich am 28.11.97 um 17:02:35 Uhr hier und entscheide mich dazu, die nachfolgende
// if-Anweisung wieder herauszunehmen. Der Test auf eine Fast-UEBERLAPP erfolgt ja schon in der
// Routine GemeinsamePunkte(); dort jedoch immer mit den URSPRÜNGLICHEN Stützpunkten - hier
// jedoch u.a. mit dem evtl. EINGEFÜGTEN Punkt GP. Der Test ist somit nicht identisch und
// liefert in diffizilen Fällen unterschiedliche Ergebnisse (z. B. hier UEBERLAPP, dort nicht).
// Also müßte ich beide Tests in Übereinstimmung bringen oder einen eben weglassen. Was ich
// hiermit tue. Ob das der richtige Weg ist, wird die nachfolgende Generation zu beurteilen
// haben. (Diesen Text am 31.12.98 immer noch nicht gelöscht.)
/*
	// durch die mir nun schon zum Halse raushängenden Rundungsprobleme der Digitalgeometrie
	// ist es möglich, daß die Winkel qwj1, qwj2, qwjj1, qwjj2 nicht haarscharf gleich sind,
	// aber eben doch gleich sein müßten; deshalb nun noch ein Test (16.07.97)
	if (FastGleich (GP, qwj1, Pj0, qwjj1, Pjj0) ||
		FastGleich (GP, qwj1, Pj0, qwjj2, HPjj) ||
		FastGleich (GP, qwj2, HPj, qwjj1, Pjj0) ||
		FastGleich (GP, qwj2, HPj, qwjj2, HPjj))
	{
		Fo = UEBERLAPP;
		return false;
	}
*/
// ???????????????????????????????????????????????????????????????????????????????????????????????????????

// Ermittlung der jeweils kleineren bzw. größeren der beiden j- bzw. jj-Winkel
double kj, kjj, gj, gjj;	// die kleineren bzw. größeren der beiden j- bzw. jj-Winkel

	if (qwj1 < qwj2) { kj = qwj1; gj = qwj2; }
	else { kj = qwj2; gj = qwj1; }
	if (qwjj1 < qwjj2) { kjj = qwjj1; gjj = qwjj2; }
	else { kjj = qwjj2; gjj = qwjj1; }

	// Ist die geordnete Folge der Quasi-Winkel zwischen j und jj alternierend, dann liegt
	// Seitenwechsel (true) vor, sonst false
	if ((kj < kjj && kjj < gj && gj < gjj) ||
	    (kjj < kj && kj < gjj && gjj < gj))
		return true;	// Seitenwechsel
	return false;		// kein Seitenwechsel

} // Seitenwechsel


// --------------------------------------------------------------------------------------------
// Test auf Überschneidung der Strecken zweier Kanten mit return-Wert
//   KEINE       keine Überschneidung, GP1 und GP2 unbestimmt
//   ECHT        Überschneidung, so daß Schnittpunkt GP1 jeweils im "Inneren" der beiden
//               Strecken liegt, GP2 unbestimmt
//   RAND_MIT    Überschneidung, so daß Schnittpunkt GP1 bei beiden Strecken ein Randpunkt
//               ist und ein sofortiger Seitenwechsel erfolgt, GP2 unbestimmt (Randpunkt-
//               berührung)
//   INNEN_MIT   Überschneidung, so daß Schnittpunkt GP1 bei einer Strecke ein Randpunkt
//               ist, bei der anderen in deren "Inneren" liegt und ein sofortiger Seiten-
//               wechsel erfolgt, GP2 unbestimmt (Innenberührung)
//   UEBERLAPP   Überlappung beider Strecken, GP1 und GP2 sind die beiden Endpunkte des
//               gemeinsamen Bereiches
//   RAND_OHNE   Berührung im Punkt GP1, der bei beiden Strecken ein Randpunkt ist, ein
//               Seitenwechsel erfolgt nicht, GP2 unbestimmt (Randpunktberührung)
//   INNEN_OHNE  Berührung im Punkt GP1, der bei einer Strecke ein Randpunkt ist, bei der
//               anderen in deren "Inneren" liegt, ein Seitenwechsel erfolgt nicht, GP2
//               unbestimmt (Innenberührung)
// Bei Überlappung werden in dieser Routine keine Untersuchungen zum Seitenwechsel
// durchgeführt.
// j bzw. jj die Indizes der Stützpunkte der this- bzw. pKt-EKante

SchnittErg _GEOMETR_EXPORT EKante :: KantenSchnitt (EKante* pKt, long j, long jj,
													DoublePair& GP1, DoublePair& GP2)
{
	_ASSERTE (pKt != 0);
	_ASSERTE (j >= 0);
	_ASSERTE (jj >= 0);

SchnittErg Fo = GemeinsamePunkte (SP(j), SP(j+1), pKt->SP(jj), pKt->SP(jj+1), GP1, GP2);

	// kein (Fo == KEINE), echter (Fo == ECHT) Schnitt bzw. Überlappung (Fo == UEBERLAPP)
	// erfordert keine weiteren Untersuchungen zum Seitenwechsel nach der Berührung
	if (KEINE == Fo || ECHT == Fo || UEBERLAPP == Fo)
		return Fo;

	// Randpunktberührungen werden i.a. 4-mal (am Anfang bzw. Ende einer offenen Kante 2-mal),
	// Innenberührungen i.a. 2-mal (am Anfang bzw. Ende einer offenen Kante 1-mal) erkannt,
	// wobei i.a. bei Randpunktberührungen der Fall GP1 == SP(j+1) == pKt->SP(jj+1) und bei
	// Innenberührungen der Fall GP1 == SP(j+1) bzw. GP1 == pKt->SP(jj+1) als der einzig
	// relevante angesehen wird, wodurch sich eine Vereinfachung beim Test auf Seitenwechsel
	// ergibt. Alle anderen Fälle werden wie "kein Schnitt" markiert und nicht weiter
	// ausgewertet.
	if (SP(j).EpsGleich (GP1) || pKt->SP(jj).EpsGleich (GP1))
	{
		// mit nachfolgendem Test wird der Fall abgefangen, daß eine Rand- bzw. Innenberührung
		// am Anfang einer offenen Kante vorliegt; das Ende einer offenen Kante braucht nicht
		// extra abgetestet zu werden, da die Testungen ja sowieso auf den Streckenendpunkt
		// SP(j+1) bzw. pKt->SP(jj+1) orientiert sind 
		if ((j > 0 || SP(0) == SP(_Size-1)) &&	// nicht am Anfang der geschlossenen this-Kante
			(jj > 0 || pKt->SP(0) == pKt->SP(pKt->ASP()-1)))
			return KEINE;			// wie "kein Schnitt" markiert
	}

bool bSW = Seitenwechsel (pKt, j, jj, GP1, Fo);	// Test auf Seitenwechsel

	// wenn die Routine Seitenwechsel() in Fo den Wert UEBERLAPP zurückgibt, dann lag keine
	// echte Randpunkt- bzw. Innenberührung sondern der	Endpunkt eines Überlappungsbereiches
	// vor; dieser Fall wird aber noch an anderer Stelle erkannt
	if (UEBERLAPP == Fo)
		return KEINE;

	// Randberührung (Fo == RAND) kann mit (bSW == true) bzw. ohne (bSW == false)
	// Seitenwechsel erfolgen
	if (RAND == Fo)
	{
		if (bSW) return RAND_MIT;
		return RAND_OHNE;
	}

	// Innenberührungen (Fo == INNEN) kann mit (bSW == true) bzw. ohne (bSW == false)
	// Seitenwechsel erfolgen. Es bleibt nur noch Fo == INNEN übrig.
	if (bSW) return INNEN_MIT;
	return INNEN_OHNE;
	
} // KantenSchnitt


// --------------------------------------------------------------------------------------------
// Aufbereitung einer Kante, die (evtl.) von einer EKante pSKt geschnitten wird;
// in pML wird die this-EKante als Vektor von markierten Punkten zurückgegeben, der durch evtl.
// Schnitt- oder Überlappungspunkte ergänzt wurden. Aus der ursprünglichen Stützpunktfolg wird
// der Vektor pML mit markierten Punkten erzeugt; diese Punkte erhalten als Markierung
//    NORMAL     "ganz normaler" Punkt.
// Bei Gemeinsamkeiten der this-EKante mit der pSKt-EKante werden in diesen Vektor zusätzliche
// Punkte mit folgenden Markierungen eingefügt
//   INNERHALB   Stützpunkt innerhalb eines Überlappungsbereiches zwischen this-EKante und
//               pSKt-EKante
//   SCHNITT     Punkt, an dem die pSKt-EKante die this-Flächenkontur mit Seitenwechsel
//               schneidet
// Es wird bAbbr = true, wenn die Operation durch den Anwender abgebrochen wird;
// return-Wert der Routine ist false, wenn die beiden Objektcontainer durchschnittsleer sind,
// bei Abbruch der Operation durch den Anwender, bei falschen Parametern bzw. unzureichendem
// dynamischen Speicher. Anderenfalls true, d.h. wenn eine weitere Auswertung sinnvoll ist.
bool EKante :: Aufbereitung0 (EKante* pSKt, MarkLine*& pML, bool& bAbbr, void* pPSt)
{
	_ASSERTE (pSKt != 0);	// pPSt kann 0 sein
	_ASSERTE (pML != 0);

	bAbbr = false;
	if (!pSKt || !pML) return false;

bool bSonst = false;	// es wurden keine Punkte eines Überlappungsbereiches bzw.
						//  Berührungspunkte (ohne Seitenwechsel) eingefügt
bool bSchnitt, bLeer;	// Parameter für Aufbereitung(); werden hier nicht ausgewertet
MarkLine* pML2 = 0;

bool bRet = Aufbereitung (pSKt, pML, pML2, bSonst, bSchnitt, bLeer, bAbbr, pPSt);

	if (bAbbr || !bRet)		// 03.11.98
		return false;

	if (bSonst)				// 21.05.99
		MarkierungModify0 (pML);

	return true;
		
} // Aufbereitung0


// --------------------------------------------------------------------------------------------
// Aufbereitung einer Flächenkontur, die (evtl.) von einer EKante pSKt geschnitten wird;
// in pML1 wird die Flächenkontur, in pML2 die schneidende pSKt-EKante jeweils als Vektor von
// markierten Punkten zurückgegeben, die durch evtl. Schnitt-, Endpunkte von
// Überlappungsbereichen oder Berührungspunkte ergänzt wurden. Aus den ursprünglichen
// Stützpunktfolgen werden die Vektoren pML1 und pML2 mit markierten Punkten erzeugt; diese
// Punkte erhalten als Markierung
//    NORMAL     "ganz normaler" Punkt.
// Bei Gemeinsamkeiten der this-Flächenkontur mit der pSKt-EKante werden in diese Vektoren
// zusätzliche Punkte mit folgenden Markierungen eingefügt
//   INNERHALB   Stützpunkt innerhalb eines Überlappungsbereiches zwischen this-Flächenkontur
//               und pSKt-EKante oder am Ende eines Überlappungsbereiches, wenn dieser genau am
//               Ende der pSKt-EKante liegt
//   RAND_INN    Endpunkt eines Überlappungsbereiches, wobei die zu- bzw. abführende
//               pSKt-Strecke innerhalb der this-Flächenkontur liegt
//	 BERUE_INN   Punkt mit Randpunkt- bzw. Innenberührung ohne Seitenwechsel, wobei die
//               beteiligten pSKt-Strecken aus dem Inneren der this-Flächenkontur kommen
//   SCHNITT     Punkt, an dem die pSKt-EKante die this-Flächenkontur mit Seitenwechsel
//               schneidet
// Es wird bAbbr = true, wenn die Operation durch den Anwender abgebrochen wird; bLeer = true,
// wenn die Objektcontainer der this-Flächenkontur und der schneidenden pSKt-EKante
// durchschnittsleer sind. return-Wert der Routine ist false, wenn die beiden Objektcontainer
// durchschnittsleer sind, bei Abbruch der Operation durch den Anwender, bei falschen Parametern
// bzw. unzureichendem dynamischen Speicher. Anderenfalls true, d.h. wenn eine weitere
// Auswertung sinnvoll ist.

bool EKante :: Aufbereitung1 (EKante* pSKt, MarkLine*& pML1, MarkLine*& pML2, bool& bAbbr,
							  void* pPSt)
{
	_ASSERTE (pSKt != 0);	// pPSt kann 0 sein
	_ASSERTE (pML1 != 0);
	_ASSERTE (pML2 != 0);

	bAbbr = false;
	if (! pSKt || ! pML1 || ! pML2) return false;

bool bSonst = false;	// es wurden keine Punkte eines Überlappungsbereiches bzw.
						//  Berührungspunkte (ohne Seitenwechsel) eingefügt
bool bSchnitt = false;	// es wurden keine Schnittpunkte eingefügt
bool bLeer;				// Parameter der Routine Aufbereitung() (wird hier nicht ausgewertet)

bool bRet = Aufbereitung (pSKt, pML1, pML2, bSonst, bSchnitt, bLeer, bAbbr, pPSt);

	if (bAbbr || !bRet)		// 03.11.98
		return false;

	if (bSonst)
		MarkierungModify1 (pML1, pML2);
		
	if (bSonst || bSchnitt)
		SpezMarkierungModify (this, pML1, pML2);
		
	return true;
		
} // Aufbereitung1


// --------------------------------------------------------------------------------------------
// Aufbereitung einer Kante bzw. Flächenkontur, die (evtl.) von einer Flächenkontur pSKont
// geschnitten wird; in pML1 wird die Kante bzw. Flächenkontur, in pML2 die schneidende Kontur
// pSKont jeweils als Vektor von markierten Punkten zurückgegeben, die durch evtl. Schnitt-,
// Endpunkte von Überlappungsbereichen oder Berührungspunkte ergänzt wurden. Aus den
// ursprünglichen Stützpunktfolgen werden die Vektoren pML1 und pML2 mit markierten Punkten
// erzeugt; diese Punkte erhalten als Markierung
//    NORMAL     "ganz normaler" Punkt;
// Bei Gemeinsamkeiten des this-Objektes mit der Kontur pSKont werden in diese Vektoren
// zusätzliche Punkte mit folgenden Markierungen eingefügt
//   INNERHALB   Stützpunkt innerhalb eines Überlappungsbereiches zwischen this-Objekt und
//               Kontur pSKont oder am Ende eines Überlappungsbereiches, wenn dieser genau am
//               Ende einer offenen Kante liegt
//   RAND_INN    Endpunkt eines Überlappungsbereiches, wobei die zu- bzw. abführende
//               this-Strecke innerhalb von pSKont liegt
//   RAND_UMG    Endpunkt eines Überlappungsbereiches, wobei die zu- bzw. abführende
//               this-Strecke außerhalb von pSKont liegt
//	 BERUE_INN   Punkt mit Randpunkt- bzw. Innenberührung ohne Seitenwechsel, wobei die
//               beteiligten Strecken aus dem Inneren der Bezugsfläche kommen
//	 BERUE_UMG   Punkt mit Randpunkt- bzw. Innenberührung ohne Seitenwechsel, wobei die
//   SCHNITT     Punkt, an dem die Kontur pSKont das this-Objekt mit Seitenwechsel schneidet
// Es wird bAbbr = true, wenn die Operation durch den Anwender abgebrochen wird; bLeer = true,
// wenn die Objektcontainer der this-EKante und der schneidenden Kontur pSKont durchschnittsleer sind.
// return-Wert der Routine ist false, wenn die beiden Objektcontainer durchschnittsleer sind, bei
// Abbruch der Operation durch den Anwender, bei falschen Parametern bzw. unzureichendem dynamischen
// Speicher. Anderenfalls true, d.h. wenn eine weitere Auswertung sinnvoll ist.

bool EKante :: Aufbereitung2 (EKante* pSKont, MarkLine*& pML1, MarkLine*& pML2, bool& bLeer,
							  bool& bAbbr, void* pPSt)
{
	_ASSERTE (pSKont != 0);		// pPSt kann 0 sein
	_ASSERTE (pML1 != 0);
	_ASSERTE (pML2 != 0);

	bLeer = false;
	bAbbr = false;
	if (!pSKont || !pML1 || !pML2) return false;

bool bSonst = false;	// es wurden Punkte eines Überlappungsbereiches bzw. Berührungspunkte
						// (ohne Seitenwechsel) eingefügt (true)
bool bSchnitt;			// Parameter von Aufbereitung(); wird hier nicht ausgewertet

bool bRet = Aufbereitung (pSKont, pML1, pML2, bSonst, bSchnitt, bLeer, bAbbr, pPSt);

	if (bLeer || bAbbr || !bRet)		// 08.10.98
		return false;

	if (bSonst)
		MarkierungModify2 (pML1, pML2);
		
	return true;
		
} // Aufbereitung2


// --------------------------------------------------------------------------------------------
//
// >>>>>>>>          zentrale Routine für alle geometrischen Operationen          <<<<<<<<
//
// Punkte, die die Vektoren pML1 und pML2 gemeinsam haben, werden mit entsprechenden
// Markierungen und Referenzen versehen; gemeinsame Punkte (Schnitt-, Berührungs-,
// Überlappungspunkte), die noch nicht in pML1 bzw. pML2 enthalten sind, werden mit den
// entsprechenden Markierungen hinzugefügt
bool EKante :: Aufbereitung (EKante* pSKt, MarkLine*& pML1, MarkLine*& pML2, bool& bSonst,
							 bool& bSchnitt, bool& bLeer, bool& bAbbr, void* pPSt)
{
	_ASSERTE (pSKt != 0);
	_ASSERTE (pML1 != 0);	// pML2 == 0 bei echter Kante (d.h. keine Flächenkontur) 

long lFSL = pSKt->ASP();			// Länge der pSKt-EKante
ObjRechteck OCth = GetCont();		// Objektcontainer der this-Flächenkontur
ObjRechteck OCfs = pSKt->GetCont();	// Objektcontainer der schneidenden pSKt-EKante

	bLeer = false;

	if (! OCth.Durchschnitt (OCfs))	// beide Objektcontainer sind durchschnittsleer
	{
		bLeer = true;
		if (pPSt)
		{
		// Abfrage, ob Operation abgebrochen werden soll
		HRESULT hr = ((BaseProgressStatus*)pPSt)->IsCanceled();

			if (FAILED(hr)) return false;

			if (S_OK == hr)
			{
				bAbbr = true;
				return false;
			}

// !!!!!!!!!!!!!!! wird später ersetzt durch 2. Parameter in IncrementPosition() !!!!!!!!!!!!!!!!!!!!
			for (long lll = 0; lll < lFSL - 1; lll++)
			{
			// akt. Wert für Prozentberechnung erhöhen
			HRESULT hr = ((BaseProgressStatus*)pPSt)->IncrementPosition (0);

				if (FAILED(hr)) return false;
			}
		}

		return false;	// beide Objektcontainer sind durchschnittsleer
	}

// An dieser Stelle war einmal folgender Einschub:
	// Wenn this- bzw. pSKt-EKante als Zwischenergebniss einer Objektoperation entstanden sind,
	// können sie Spitzen, Kollinearitäten oder doppelte Punkte enthalten, die nachfolgend
	// beseitigt werden.
// Mit der Version 28 von geo_obj3.cxx im SourceSafe habe ich am 01.03.99 diesen Einschub herausgenommen,
// weil ich unerklärlicherweise der Annahme war, daß dies nicht mehr erforderlich ist. Heute am 27.07.99
// merke ich, daß dies ein Irrtum war.
// Der erneute Einsatz dieser Funktion PartialCleaningForLines() erfolgt erst einmal VOR den Stellen, wo
// die MarkLine-Pointer angelegt werden.

	if (pML2)
		DblPointTestBetween2Lines (pSKt);

	for (long j = 0; j < _Size; j++)
	{
		pML1->SetX (j, SP(j).X());		// 1. Markierung wird standardmäßig auf NORMAL gesetzt
		pML1->SetY (j, SP(j).Y());
	}

	if (pML2)
		for (long jj = 0; jj < lFSL; jj++)
		{
			pML2->SetX (jj, pSKt->SP(jj).X());
			pML2->SetY (jj, pSKt->SP(jj).Y());
		}

long k11, k12, k21, k22;	// Hilfsindizes
DoublePair ZPA, ZPE;		// evtl. gemeinsame Punkte beider Kanten
bool bAdd11, bAdd12, bAdd21, bAdd22;	// zusätzlicher Punkt wird eingefügt (true) bzw. es
										// wird nur die Markierung modifiziert (false)

	// Test von jeder pSKt-Strecke mit jeder this-Strecke
	for (long jj = 0; jj < lFSL-1; jj++)		// pSKt-Strecken
	{
		if (pPSt)
		{
		// Abfrage, ob Operation abgebrochen werden soll
		HRESULT hr = ((BaseProgressStatus*)pPSt)->IsCanceled();

			if (FAILED(hr)) return false;
			if (S_OK == hr)
			{
				bAbbr = true;
				return false;
			}

			// akt. Wert für Prozentberechnung inkrementieren
			hr = ((BaseProgressStatus*)pPSt)->IncrementPosition (0);
			if (FAILED(hr)) return false;
		}

		if (IdenticalPoints (pSKt->SP(jj).X(), pSKt->SP(jj).Y(), pSKt->SP(jj+1).X(),
							 pSKt->SP(jj+1).Y()))	// Strecke entartet
			continue;	// Verzweiflungstat (16.07.99)
		
	ObjRechteck OC2 = BuildRectangle (pSKt->SP(jj), pSKt->SP(jj+1));
		
		for (j = 0; j < _Size-1; j++)		// this-Strecken
		{
			if (IdenticalPoints (SP(j).X(), SP(j).Y(), SP(j+1).X(), SP(j+1).Y()))
				continue;	// Verzweiflungstat (16.07.99)

		// Test, ob die Container der beiden zu vergleichenden Strecken untereinander
		// durchschnittsleer sind
		ObjRechteck OC1 = BuildRectangle (SP(j), SP(j+1));

			if (! OC1.EpsDurchschnitt (OC2))
				continue;       // die Container beider Strecken sind durchschnittsleer

		SchnittErg Fo = KantenSchnitt (pSKt, j, jj, ZPA, ZPE);
	
			if (Fo == KEINE)
				continue;		// für for-Schleife

			// Schnitt mit Seitenwechsel, dies umfaßt echter Schnitt (Fo == ECHT),
			// Randpunkt- (Fo == RAND_MIT) bzw. Innenberührung (Fo == INNEN_MIT)
			if (Fo == ECHT || Fo == RAND_MIT || Fo == INNEN_MIT)
			{
				// Index k von pML1 bzw. von pML2 ermitteln, vor dem der zusätzliche Punkt ZPA
				// einzufügen ist
				if (!EinfIndex (SP(j), SP(j+1), j, pML1, ZPA, k11))
					return false;
				EinfMarkPunkt (pML1, k11, ZPA, SCHNITT, bAdd11);
				if (pML2)
				{
					if (!EinfIndex (pSKt->SP(jj), pSKt->SP(jj+1), jj, pML2, ZPA, k12))
						return false;
					EinfMarkPunkt (pML2, k12, ZPA, SCHNITT, bAdd12);
					pML1->RefIndexModifizieren (pML2, bAdd11, bAdd12, k11, k12);
				}
				bSchnitt = true;
				continue;		// für for-Schleife
			}

			// Überlappung
			else if (Fo == UEBERLAPP)
			{
				if (!EinfIndex (SP(j), SP(j+1), j, pML1, ZPA, k11))
					return false;
				EinfMarkPunkt (pML1, k11, ZPA, INNERHALB, bAdd11);
				if (pML2)
				{
					if (!EinfIndex (pSKt->SP(jj), pSKt->SP(jj+1), jj, pML2, ZPA, k12))
						return false;
					EinfMarkPunkt (pML2, k12, ZPA, INNERHALB, bAdd12);
					pML1->RefIndexModifizieren (pML2, bAdd11, bAdd12, k11, k12);
				}

				if (!EinfIndex (SP(j), SP(j+1), j, pML1, ZPE, k21))
					return false;
				EinfMarkPunkt (pML1, k21, ZPE, INNERHALB, bAdd21);
				if (pML2)
				{
					if (!EinfIndex (pSKt->SP(jj), pSKt->SP(jj+1), jj, pML2, ZPE, k22))
						return false;
					EinfMarkPunkt (pML2, k22, ZPE, INNERHALB, bAdd22);
					pML1->RefIndexModifizieren (pML2, bAdd21, bAdd22, k21, k22);
				}

				bSonst = true;
				continue;		// für for-Schleife
			}
		
			// Randpunkt- (Fo == RAND_OHNE) bzw. Innenberührung (Fo == INNEN_OHNE) ohne
			// Seitenwechsel, jedoch nur dann, wenn pML2 != 0, d.h. nicht Schnitt Kante mit
			// Kante
			else if (Fo == RAND_OHNE || Fo == INNEN_OHNE)
			{
				if (!EinfIndex (SP(j), SP(j+1), j, pML1, ZPA, k11))
					return false;
				EinfMarkPunkt (pML1, k11, ZPA, BERUEHR, bAdd11);
				if (pML2)
				{
					if (!EinfIndex (pSKt->SP(jj), pSKt->SP(jj+1), jj, pML2, ZPA, k12))
						return false;
					EinfMarkPunkt (pML2, k12, ZPA, BERUEHR, bAdd12);
					pML1->RefIndexModifizieren (pML2, bAdd11, bAdd12, k11, k12);
				}
				bSonst = true;
			}
		} // for
	} // for

	return true;

} // Aufbereitung


// --------------------------------------------------------------------------------------------
// Einschneidendste Änderung seit der Erfindung des Mikrochips (24.03.99)
// Test auf doppelte Punkte zwischen 2 Kanten:
// Punkte der this-Kante, die mit einem pKt-Punkt eps-gleich sind, auf diesen pKt-Punkt setzen
void EKante :: DblPointTestBetween2Lines (EKante* pKt)
{
	_ASSERTE (pKt != 0);

long lFSL = pKt->ASP();	// Länge der pSKt-EKante

	for (long j = 0; j < _Size; j++)
		for (long jj = 0; jj < lFSL; jj++)
			if (SP(j).EpsGleich (pKt->SP(jj), dGlEps, dGlEps, false))	// Maximum-Norm
			{
				SP(j).X() = pKt->SP(jj).X();
				SP(j).Y() = pKt->SP(jj).Y();
				break;
			}

} // DblPointTestBetween2Lines


// --------------------------------------------------------------------------------------------
// Kante mit weiteren Punkten aus einem (offenen) MarkLine-Vektor pML2 ergänzen, und zwar ab
// dem Index ii des MarkLine-Vektors pML2, der dem Index i des MarkLine-Vektors pML1
// entspricht. Die Punktefolge von pML2 ist so zu durchlaufen, daß die pML2-Punkte nicht
// außerhalb der pML1-Fläche liegen bis einschließlich des nächsten Schnitt-
// (Mark1 == SCHNITT), Rand- (RAND_INN) oder Berührungspunktes (BERUE_INN, BERUE_ER, BERUE_LE).
// Der Index i von pML1, bei dem der weitere Aufbau der Kante fortgesetzt werden soll, wird
// zurückgegeben.
void EKante :: SpezAddPunkt1 (MarkLine* pML1, MarkLine* pML2, long& i, Mar1 mark)
{
	_ASSERTE (pML1 != 0);
	_ASSERTE (pML2 != 0);
	_ASSERTE (i >= 0);

	if (!pML1 || !pML2) return;
	
long lVekL1 = pML1->ADP();	// Länge des Vektors pML1
long lVekL2 = pML2->ADP();	//  bzw. pML2
MoveDir MD;					// Index von pML2 ist aufsteigend (MOVEDIR_UP) bzw. absteigend
							// (MOVEDIR_DOWN) zu durchlaufen
double w1, w2, w3;			// Quasiwinkel

// Index des pML2-Punktes, der mit Punkt pML1[i] übereinstimmt
long ii = pML1->GetRefInd(i);

	_ASSERTE (ii >= 0);

	// Bestimmen, ob Indizes von pML2 aufsteigend oder absteigend zu durchlaufen sind
	if (ii == 0 || mark == BERUE_ER)
		MD = MOVEDIR_UP;
	else
	{
		if (ii == lVekL2-1 || mark == BERUE_LE)
			MD = MOVEDIR_DOWN;
		else
		{
			// Bei einem Berührungspunkt (mark == BERUE_INN) liegen die Strecken
			//((*pML2)[ii], (*pML2)[ii+1]) sowie ((*pML2)[ii], (*pML2)[ii-1]) innerhalb von
			// pML1. Deshalb ist hier zu fragen, auf welche der beiden Strecken man stößt, wenn
			// man sich ausgehend von der Strecke ((*pML1)[i-1], (*pML1)[i]) im Uhrzeigersinn
			// bewegt.
			if (mark == BERUE_INN)
			{
			long i1	;	// der i vorangehende Index von pML1
			
				(i > 0) ? (i1 = i - 1) : (i1 = lVekL1 - 2);
				w1 = QuasiWinkel (pML1->x(i), pML1->y(i), pML1->x(i1), pML1->y(i1));
				w2 = QuasiWinkel (pML2->x(ii), pML2->y(ii), pML2->x(ii-1), pML2->y(ii-1));
				w3 = QuasiWinkel (pML2->x(ii), pML2->y(ii), pML2->x(ii+1), pML2->y(ii+1));

				// w1 entweder der größte oder der kleinste der 3 Quasiwinkel
				if ((w1 < w2 && w1 < w3) || (w1 > w2 && w1 > w3))
					// es geht bei max (w2, w3) weiter
					(w2 > w3) ? (MD = MOVEDIR_DOWN) : (MD = MOVEDIR_UP);
				else	// w1 der mittlere der 3 Quasiwinkel
						// es geht bei min (w2, w3) weiter
					(w2 < w3) ? (MD = MOVEDIR_DOWN) : (MD = MOVEDIR_UP);
			}
			else	// mark == SCHNITT oder RAND_INN
			{
				if (INNERH == pML1->Position (pML2, ii))
					MD = MOVEDIR_UP;
				else MD = MOVEDIR_DOWN;
			}
		}
	}
			
long lAnfId;		// Anfangsindex für den Teil, der aus pML2 übernommen wird
bool bErst = true;	// nachfolgende do-Schleife das erste Mal durchlaufen
Mar1 mark12;		// 1. Markierung eines pML2-Punktes
long j1	;			// der auf j folgende Index von pML1

	do
	{
		// nächstes ii für pML2 ermitteln
		(MOVEDIR_UP == MD) ? (ii++) : (ii--);	// pML2 auf- bzw. absteigend durchlaufen
		if (bErst)
		{
			lAnfId = ii;
			bErst = false;
		}
		mark12 = pML2->GetMk1(ii);
		
		// Bei Berührungspunkt (mark12 == BERUE_INN) steht die Frage, ob bei der "anderen"
		// pML2-Strecke fortzufahren oder pML2 zu verlassen ist. Dazu wird geprüft, auf
		// welche Strecke man stößt, wenn man sich im Uhrzeigersinn ausgehend von der
		// aktuellen pML2-Strecke um den Berührungspunkt dreht.
		if (mark12 == BERUE_INN && ii > 0 && ii < lVekL2-1)
		{
			for (long j = 0; j < lVekL1; j++)
				if (pML2->x(ii) == pML1->x(j) && pML2->y(ii) == pML1->y(j)) break;

			if (j < lVekL1-2) j1 = j + 1;
			else j1 = 0;
			w1 = QuasiWinkel (pML1->x(j), pML1->y(j), pML1->x(j1), pML1->y(j1));
			w2 = QuasiWinkel (pML2->x(ii), pML2->y(ii), pML2->x(ii-1), pML2->y(ii-1));
			w3 = QuasiWinkel (pML2->x(ii), pML2->y(ii), pML2->x(ii+1), pML2->y(ii+1));
			if (MOVEDIR_UP == MD)	// w2 ist Bezugswinkel
			{
				// w2 entweder der größte oder der kleinste der 3 Quasiwinkel
				if ((w2 < w1 && w2 < w3) || (w2 > w1 && w2 > w3))
				{
					if (w1 > w3) break;	// es geht bei max (w1, w3) weiter
					else continue;
				}
				else	// w2 der mittlere der 3 Quasiwinkel
				{
					if (w1 < w3) break;	// es geht bei min (w1, w3) weiter
					else continue;
				}
			}
			else		// w3 ist Bezugswinkel
			{
				// w3 entweder der größte oder der kleinste der 3 Quasiwinkel
				if ((w3 < w1 && w3 < w2) || (w3 > w1 && w3 > w2))
				{
					if (w1 > w2) break;	// es geht bei max (w1, w2) weiter
					else continue;
				}
				else	// w3 der mittlere der 3 Quasiwinkel
				{
					if (w1 < w2) break;	// es geht bei min (w1, w2) weiter
					else continue;
				}
			}
		}
	}
	// mark12 == BERUE_INN ist nur dann ein Abbruchkriterium, wenn an dieser Stelle die
	// aufzubauende Teilfläche geschlossen wird, d.h. der aktuelle pML2-Punkt gleich dem
	// Anfangspunkt AP ist (nach dem Negationszeichen in der while-Bedingung stehen die
	// Abbruchbedingungen)
	while (!(mark12 == SCHNITT || mark12 == RAND_INN || mark12 == BERUE_ER ||
		   mark12 == BERUE_LE ||
		   ii <= 0 || ii >= lVekL2-1));

// Index des pML1-Punktes, der mit dem letzten der this-EKante hinzuzufügenden Punkt pML2[ii]
// übereinstimmt; wird ein solcher Punkt nicht gefunden, weil der Anfangs- oder Endpunkt der
// pML2-Kante innerhalb von pML1 liegt, wird nichts an die this-EKante angehangen und i
// unverändert zurückgegeben
long j = pML2->GetRefInd(ii);

	if (j >= 0)		// standardmäßig ist der RefInd = -1
	{
		// Teil von pML2 an Ende der this-EKante anhängen
		AddKantenStueck2 (pML2, lAnfId, ii, MD);
		i = j;
	}
} // SpezAddPunkt1


// --------------------------------------------------------------------------------------------
// Kante mit weiteren Punkten aus einem geschlossenen MarkLine-Vektor pML2[] ergänzen, und zwar
// ab Index i des MarkVertex-Vektors pML1[]; die Punktefolge von pML2[] ist aufsteigend
// (MD == MOVEDIR_UP) bzw. absteigend (MD == MOVEDIR_DOWN) - auch über den
// Anfangs/Endpunkt von pML2[] hinaus - zu durchlaufen, bis einschließlich des nächsten
// Schnittpunktes (Markierung Mark1 == SCHNITT) bzw. Randpunktes (Mark1 == RAND_INN oder
// RAND_UMG) oder Berührungspunktes (Mark1 == BERUE_INN). Dabei sind die Punkte mit der
// Markierung RAND_INN für den Fall zuständig, daß pML2[] aufsteigend durchlaufen wird,
// anderenfalls (Markierung RAND_UMG bzw. BERUE_UMG) für den absteigenden Fall. Der Index i von
// pML1[], bei dem der weitere Aufbau der Kante fortgesetzt werden soll, wird zurückgegeben.
void EKante :: SpezAddPunkt2 (MarkLine* pML1, MarkLine* pML2, long& i, MoveDir MD,
							  ulong ulLageAusw)
{
	_ASSERTE (pML1 != 0);
	_ASSERTE (pML2 != 0);
	_ASSERTE (i >= 0);

	if (! pML1 || ! pML2) return;

long lVekL1 = pML1->ADP();   // Länge des Vektors pML1
long lVekL2 = pML2->ADP();   //  bzw. pML2

// Index des pML2-Punktes, der mit Punkt pML1[i] übereinstimmt
long ii = pML1->GetRefInd(i);

	_ASSERTE (ii >= 0);

long lAnfId;		// Anfangsindex für den Teil der Flächenkontur, der aus pML2 übernommen
					// wird
bool bErst = true;	// nachfolgende do-Schleife das erste Mal durchlaufen
Mar1 mark12;		// 1. Markierung eines pML2-Punktes

int iKInd1 = pML1->GetKInd();		_ASSERTE (iKInd1 >= 0);
int iKInd2 = pML2->GetKInd();		_ASSERTE (iKInd2 >= 0);
bool bMax;		// SEHR wichtiger Parameter von EckeMitBeruehrung() 

	if (0 == iKInd1 && 0 == iKInd2)
		bMax = true;
	else if (0 == iKInd1 && iKInd2 > 0)
		bMax = true;
	else if (iKInd1 > 0 && 0 == iKInd2)
		bMax = false;
	else	// if (iKInd1 > 0 && iKInd2 > 0)
		bMax = true;

bool bWechsel;		// bei BERUE_INN bzw. BERUE_UMG ist bei pML1 fortzusetzen (true); wird
					// durch EckeMitBeruehrung() gesetzt

	do
	{
		// nächstes ii für pML2 ermitteln
		if (MOVEDIR_UP == MD)	// pML2 aufsteigend durchlaufen
			(ii < lVekL2-2) ? (ii++) : (ii = 0);
		else					// pML2 absteigend durchlaufen
			(ii > 0) ? (ii--) : (ii = lVekL2-2);
		if (bErst)
		{
			lAnfId = ii;
			bErst = false;
		}
		mark12 = pML2->GetMk1(ii);
		if ((mark12 == BERUE_INN && (ulLageAusw & LINN)) ||
			(mark12 == BERUE_UMG && (ulLageAusw & LAUSS)))
			pML2->EckeMitBeruehrung (pML1, ii, MD, MOVEDIR_UP, bMax, bWechsel);
	}
	// Abbruch der do-Schleife bei Schnitt- bzw. bestimmten Randpunkten
	// (nach dem Negationszeichen in der while-Bedingung stehen die Abbruchbedingungen)
	while (!(mark12 == SCHNITT ||
			(mark12 == RAND_INN && (ulLageAusw & LINN)) ||
			(mark12 == RAND_UMG && (ulLageAusw & LAUSS)) ||
			(mark12 == BERUE_INN && (ulLageAusw & LINN) && bWechsel) ||
			(mark12 == BERUE_UMG && (ulLageAusw & LAUSS) && bWechsel)));

	// Teil der Kontur von pML2 an Ende der this-EKante anhängen
	AddKantenStueck2 (pML2, lAnfId, ii, MD);
	
	// Index des pML1-Punktes, der mit dem letzten der this-EKante hinzugefügten Punkt pML2[ii]
	// übereinstimmt
	i = pML2->GetRefInd(ii);

	_ASSERTE (i >= 0);
		
} // SpezAddPunkt2


// --------------------------------------------------------------------------------------------
// Enthaltensein eines real-Punktes (x,y) in der Fläche, die durch eine geschlossene Kante bzw.
// eine Flächenkontur gebildet wird; return-Wert ist
//   INNERH   Punkt liegt innerhalb der Fläche
//   KONTUR   Punkt liegt auf Flächenrand
//   AUSSERH  Punkt liegt außerhalb der Fläche
//   OFFEN    Flächenrand nicht geschlossen
// Der real-Punkt ist der Anfangspunkt einer waagrechten Testlinie, deren Endpunkt "unendlich"
// weit rechts liegt.
Posit EKante :: Position_real (double x, double y)
{
	_ASSERTE (_Size >= 2);

	if (SP(0) != SP(_Size-1))    // Kante nicht geschlossen
		return OFFEN;

long AnzSchn = 0;	// Zähler für echte Schnitte der Testlinie mit Kante
long j = _Size-2;	// Index des letzten Konturpunktes, von dem bekannt ist, daß er nicht auf
					// der Testlinie liegt

	while (TurnDirection (x, y, LONG_MAX, y, SP(j).X(), SP(j).Y()) == 0)
	{
		j--;
		if (j < 0)
			return OFFEN;	// entartete Fläche, d.h. alle Punkte liegen auf einer Geraden,
							// die mit der Trägergeraden der TLinie identsch ist
	}

int r1, r2, r3, r4;   // Hilfswerte für Bewegungsrichtung

	for (long i = 0; i < _Size-1; i++)
	{
		// Test, ob Punkt auf Kante liegt
		if (0 == TurnDirection (SP(i).X(), SP(i).Y(), SP(i+1).X(), SP(i+1).Y(), x, y))
			return KONTUR;       // Punkt liegt auf Kante

		// Im if-Zweig der nachfolgenden Anweisung wird der Fall behandelt, daß der Stützpunkt
		// SP(i) nicht auf der waagrechten Testlinie liegt.
		// Liegt SP(i) auf der Testlinie (else-Zweig), wird SP(i) i.a. ignoriert.
		// Liegt jedoch der zu testende Punkt (x,y) im Dreieck SP(i-1),SP(i),SP(i+1), ergibt
		// sich durch das Weglassen von SP(i) eine Fehlinterpretation. Deshalb ist dieser Fall
		// gesondert abzutesten.
		if (TurnDirection (x, y, LONG_MAX, y, SP(i).X(), SP(i).Y()) != 0)
		{
			r1 = TurnDirection (SP(i).X(), SP(i).Y(), SP(j).X(), SP(j).Y(), x, y);
			r2 = TurnDirection (SP(i).X(), SP(i).Y(), SP(j).X(), SP(j).Y(), LONG_MAX, y);
			r3 = TurnDirection (x, y, LONG_MAX, y, SP(i).X(), SP(i).Y());
			r4 = TurnDirection (x, y, LONG_MAX, y, SP(j).X(), SP(j).Y());
			j = i;
			// Zähler inkrementieren, wenn echter Schnitt zwischen Strecke (SP(i), SP(j)) und
			// Teststrecke vorliegt
			if ((r1 * r2 <= 0) && (r3 * r4 <= 0))
				AnzSchn++;
		}
		else    // SP(i) liegt auf der Teststrecke
		{
		long iv = i - 1;

			if (0 == i) iv = _Size-2;
			
			// liegt (x,y) AUF der Strecke (SP(i-1), SP(i)), ist alles klar
			if (0 == TurnDirection (SP(iv).X(), SP(iv).Y(), SP(i).X(), SP(i).Y(), x, y))
				return KONTUR;

			// ansonsten wird getestet, ob (x,y) IM Dreieck SP(i-1), SP(i), SP(i+1) liegt; wenn
			// ja, wird überprüft, ob die Ecke bei SP(i) konvex oder konkav ist
			r1 = TurnDirection (SP(iv).X(), SP(iv).Y(), SP(i).X(), SP(i).Y(), x, y);
			r2 = TurnDirection (SP(i).X(), SP(i).Y(), SP(i+1).X(), SP(i+1).Y(), x, y);
			r3 = TurnDirection (SP(i+1).X(), SP(i+1).Y(), SP(iv).X(), SP(iv).Y(), x, y);

			if (r1 >= 0 && r2 >= 0 && r3 >= 0)	// konvexe Ecke der this-Fläche:
				return INNERH;					//  Punkt liegt innerhalb
			if (r1 <= 0 && r2 <= 0 && r3 <= 0)	// konkave Ecke der this-Fläche:
				return AUSSERH;					//  Punkt liegt außerhalb
			// (x,y) liegt nicht im Dreieck SP(i-1), SP(i), SP(i+1)
		}
	}
	if (AnzSchn & 1)	// ungerader Zähler bedeutet Enthaltensein
		return INNERH;
	return AUSSERH;

} // Position_real


// --------------------------------------------------------------------------------------------
// Lage der this- und der pKt-Kontur zueinander; return-Wert ist
//	INNERH		pKt vollständig innerhalb der this-EKante
//	INNERHB		pKt innerhalb, aber mit Berührung der this-EKante	????
//	KONTUR		pKt vollständig auf dem Rand						????
//	AUSSERH		pKt vollständig außerhalb der this-EKante
//	AUSSERHB	pKt außerhalb, aber mit Berührung der this-EKante
//	INNAUSS		pKt teilweise innerhalb, teilweise außerhalb
//	UMSCHL		pKt außerhalb der this-EKante, aber umschließt diese vollständig
//	UMSCHLB		pKt außerhalb der this-EKante, aber mit Berührung der this-EKante und umschließt
//				dieses vollständig
//	OFFEN		this-EKante nicht geschlossen
//	UNKLAR		vorzeitiges Ende bei falschen Parametern oder unzureichendem dynamischen
//              Speicher
// In bOverlap wird angezeigt, ob ein Überlappungsbereich vorliegt (true) oder nicht (false), in
// iTouchOut wird noch die Anzahl der Berührungspunkte mit "Zuführung" aus der Umgebung von pKont
// zurückgegeben
Posit _GEOMETR_EXPORT EKante :: LageKonturZuKontur (EKante* pKt, MarkLine*& pML1,
												MarkLine*& pML2, bool& bOverlap, int& iTouchOut)
{
	_ASSERTE (pKt != 0);
	_ASSERTE (pML1 != 0);
	_ASSERTE (pML2 != 0);

	if (!pKt || !pML1 || !pML2) return UNKLAR;

	if (SP(0) != SP(_Size-1))
		return OFFEN;

bool bLeer;	// Container der beiden mit Aufbereitung2() verglichenen Objekte sind
			// durchschnittsleer (true)
bool bAbbr;	// Parameter von Routine Aufbereitung2(); wird hier nicht ausgewertet

// 08.10.98: Ist das immer so korrekt ???
	Aufbereitung2 (pKt, pML1, pML2, bLeer, bAbbr, 0);

	if (! bLeer)	
		return KantenPosit (pKt, pML1, bOverlap, iTouchOut);
	return AUSSERH;

} // LageKonturZuKontur


// --------------------------------------------------------------------------------------------
// Es wird ein Punkt zurückgegeben, der garantiert innerhalb der geschlossenen this-EKante
// liegt.
bool _GEOMETR_EXPORT EKante :: InneliegenderPunkt (double& dInX, double& dInY)
{
	if (_Size < 4 || SP(0) != SP(_Size-1))	// this-EKante entartet oder nicht geschlossen
	{
		DEX_Error (RC_InneliegenderPunkt, EC_ILLPARS);
		MessageBox (__hWndM, "Fehlerhafter Parameter in Routine EKante::InneliegenderPunkt", "Achtung:", MB_ICONEXCLAMATION | MB_OK);
		return false;
	}

// zuerst wird getestet, ob der Mittelpunkt des umschließenden Rechtecks innerhalb der
// geschlossenen this-EKante liegt
ObjRechteck OC = GetCont ();

	dInX = (OC.XMax() + OC.XMin()) / 2.;	// Mittelpunkt des umschließenden
	dInY = (OC.YMax() + OC.YMin()) / 2.;	// Rechtecks

	if (INNERH == Position_real (dInX, dInY))
		return true;	// liegt innerhalb

// klappt das noch nicht, wird durch den Mittelpunkt (dInX, dInY) eine waagrechte Testkante TKt
// gelegt, welche mit der this-Kante geschnitten wird; von den ECHTEN Schnittpunkten werden
// die beiden mit den kleinsten x-Koordinaten gesucht; der Mittelpunkt zwischen diesen beiden
// Schnittpunkten muß mit Wahrscheinlichkeit 1 innerhalb der this-EKante liegen
double dTestY = dInY;
double dSchrittY = OC.YMax() - OC.YMin();
KoOrd x[2] = { -MAXKOORD, MAXKOORD };
KoOrd y[2] = { DtoL(dTestY), DtoL(dTestY) };
EKante TKt (x, y, 2);	// waagrechte Testkante (aus 1 Strecke bestehend) durch den
						// Mittelpunkt des umschließenden Rechtecks
DoublePair ZPA, ZPE;	// evtl. gemeinsame Punkte beider Kanten
double xs1 = DBL_MAX,	// die beiden kleinsten x-Koordinaten von allen
	   xs2 = DBL_MAX;	// Schnittpunkten der this-EKante mit der waagrechten Testkante

long j = -1;

	do
	{
		j++;

		if (!Intersection (SP(j).X(), SP(j).Y(), SP(j+1).X(), SP(j+1).Y(),
						   TKt.SP(0).X(), TKt.SP(0).Y(), TKt.SP(1).X(), TKt.SP(1).Y()))
			continue;       // die beiden Strecken haben keinen Punkt gemeinsam

	SchnittErg Fo = KantenSchnitt (&TKt, j, 0, ZPA, ZPE);

		if (ECHT == Fo || INNEN_MIT == Fo || RAND_MIT == Fo)
		{
			if (ZPA.X() < xs1)
			{
				xs2 = xs1;
				xs1 = ZPA.X();
			}
			else if (ZPA.X() < xs2) xs2 = ZPA.X();
		}

		// Überlappungen machen an dieser Stelle Probleme, deshalb wird die waagrechte
		// Testkante etwas parallel verschoben
		else if (UEBERLAPP == Fo)
		{
			if (dTestY + dSchrittY < OC.YMax())
				dTestY += dSchrittY;
			else
			{
				dTestY = (dTestY + OC.YMin()) / 2.;
				dSchrittY /= 2.;
			}

			TKt.SP(0).Y() = TKt.SP(1).Y() = DtoL(dTestY);
			xs1 = xs2 = DBL_MAX;
			j = -1;
		}
	}
	while (j < _Size - 2);

	_ASSERTE (xs1 < DBL_MAX);
	_ASSERTE (xs2 < DBL_MAX);

	dInX = (xs2 + xs1) / 2.;
	dInY = dTestY;

	if (INNERH == Position_real (dInX, dTestY))
		return true;

	_ASSERTE (false);

	return false;

} // InneliegenderPunkt


// --------------------------------------------------------------------------------------------
// Lage der this-EKante bezüglich der Fläche pFl; es werden auch Inseln von pFl mit
// berücksichtigt, d.h. liegt this-EKante innerhalb einer pFl-Insel, dann liegt this-EKante
// außerhalb von pFl
Posit _GEOMETR_EXPORT EKante :: EnthaltenIn (EFlaeche* pFl, void* pPSt)
{
	_ASSERTE (pFl != 0);	// pPSt kann 0 sein

	if (! pFl) return UNKLAR;

ObjRechteck OC1 = GetCont();
ObjRechteck OC2 = pFl->GetCont();

	if (OC1.Durchschnitt (OC2) == false)
		return AUSSERH;		// Container haben keinen Punkt gemeinsam

int iKAnz = pFl->KantenAnz();
bool bOverlap;  // 3. Parameter von Routine KantenPosit() (wird hier nicht ausgewertet)
int iTouchOut;	// 4. Parameter von Routine KantenPosit() (wird hier nicht ausgewertet)
Posit posLage;
bool bInnenB = false;	// this-EKante liegt zur pFl-Außenkontur INNERHB (true)
bool bAussenB = false;	// this-EKante liegt zu mindestens einer pFl-Innenkontur AUSSERHB (true)
bool bAbbr;		// Parameter von Routine Aufbereitung2(); wird hier nicht ausgewertet
bool bLeer;		// Container der beiden mit Aufbereitung2() verglichenen Objekte sind
				// durchschnittsleer (true)

bool bClosed = false;	// this-EKante offen/geschlossen (false/true)

	if (SP(0) == SP(ASP()-1)) bClosed = true;
						
	for (int i = 0; i < iKAnz; i++)
	{
	MarkLine* pML1 = new MarkLine (_Size, -1, bClosed);
	MarkLine* pML2 = new MarkLine (pFl->KA(i).ASP(), i, true);

		if (!pML1 || !pML1->Vektor() || !pML2 || !pML2->Vektor())
		{
			DEX_Error (RC_EnthaltenInKante, EC_NOMEMORY);
			DELETE_OBJ (pML1);
			return UNKLAR;
		}

		if (!Aufbereitung2 (&pFl->KA(i), pML1, pML2, bLeer, bAbbr, pPSt))
		{
			DELETE_OBJ (pML1); DELETE_OBJ (pML2);
			// bLeer == true bedeutet, daß der Container der i-ten pFl-Kontur und Container der
			// this-EKante durchschnittsleer sind. Für Außenkontur (i = 0) wurde dies schon oben
			// abgefangen. Hier kann der Fall nur noch bei Innenkonturen auftreten (i > 0).
			// Dabei ist die Lage noch nicht klärbar.
			if (bLeer) continue;

			// false-Rückgabe von Aufbereitung2() bedeutet Abbruch durch den Anwender, falsche
			// Parameter oder unzureichender dynamischer Speicher
			return UNKLAR;
		}

		posLage = KantenPosit (&pFl->KA(i), pML1, bOverlap, iTouchOut);
		DELETE_OBJ (pML1); DELETE_OBJ (pML2);
		
		// Test mit pFl-Innenkonturen (i > 0) nur erforderlich, wenn der Test mit der
		// pFl-Außenkontur posLage == INNERH oder posLage == INNERHB ergeben hat
		if (i == 0)
		{
			// UMSCHL bzw. UMSCHLB gelten nur für 2 Flächen; auch wenn eine Kante eine Fläche
			// umschließt, liegt die Kante außerhalb der Fläche
			if (UMSCHL == posLage)
				posLage = AUSSERH;
			else if (UMSCHLB == posLage)
				posLage = AUSSERHB;
			if (posLage != INNERH && posLage != INNERHB)
				return posLage;
			if (posLage == INNERHB)
				bInnenB = true;
		}
			
		if (i > 0)			// pFl-Innenkonturen wurden noch mit herangezogen
		{
			// für INNERH, INNERHB, INNAUSS, KONTUR und UNKLAR ist alles klar
			if (posLage == INNERH || posLage == INNERHB || posLage == INNAUSS ||
				posLage == KONTUR || posLage == UNKLAR)
			{
				if (posLage == INNERH)	// vollständig innerhalb einer pFl-Insel heißt
					return AUSSERH;		//  außerhalb der pFl-Fläche
				if (posLage == INNERHB)	// innerhalb der Außenkontur, aber bez. einer
					return AUSSERHB;	//  Innenkontur INNERHB bedeutet AUSSERHB
				return posLage;
			}
				
			// für AUSSERH bzw. AUSSERHB ist posLage noch nicht eindeutig klärbar
			if (posLage == AUSSERHB)
				bAussenB = true;
		}
	}
	
	// dieser Programmteil wird nur erreicht, wenn this-EKante innerhalb der Außenkontur liegt
	// (posLage == INNERH bzw. posLage == INNERHB) und bez. aller Innenkonturen (so es sie
	// überhaupt gibt) AUSSERH oder AUSSERHB gilt;
	// gilt bez. der Außenkontur INNERHB (bInnenB = true) oder bez. der Innenkonturen
	// mindestens einmal AUSSERHB (bAussenB == true), dann gilt bez. der gesamten pFl-Fläche
	// INNERHB, sonst INNERH
	if (bAussenB || bInnenB)
		return INNERHB;
	else return INNERH;

} // EKante :: EnthaltenIn


// --------------------------------------------------------------------------------------------
// Lage der this-EKante und der pKt-EKante zueinander; return-Wert ist
//	INNERH   pKt liegt vollständig auf this-EKante
//	AUSSERH  beide Kanten haben keinen Punkt gemeinsam
//	INNAUSS  es gibt mindestens 1 gemeinsamen Punkt und mindestens ein pKt-Punkt ist nicht
//           gleichzeitig auch Punkt der this-EKante
//	UNKLAR   unzulässige(r) Parameter
Posit _GEOMETR_EXPORT EKante :: KantenLage (EKante* pKt)
{
	_ASSERTE (pKt != 0);

	if (! pKt) return UNKLAR;

ObjRechteck OC1 = GetCont();
ObjRechteck OC2 = pKt->GetCont();

	if (OC1.Durchschnitt (OC2) == false)
		return AUSSERH;	// Container haben keinen Punkt gemeinsam
	
long lKL = pKt->ASP();
KoOrd APX = pKt->SP(0).X();		// Anfangspunkt von pKt
KoOrd APY = pKt->SP(0).Y();
KoOrd EPX = pKt->SP(lKL-1).X();	// Endpunkt von pKt
KoOrd EPY = pKt->SP(lKL-1).Y();
DoublePair ZPA, ZPE;	// Anfangs- bzw. Endpunkt von Überlappungsbereichen
bool bOverlap = false;	// es gibt einen/keinen Überlappungsbereich zwischen this-EKante und pKt
						// (true/false)
bool bAP = false;		// Überlappungsbereich beginnt/nicht beim Anfangspunkt von pKt
						// (true/false)
bool bEP = false;		// Überlappungsbereich geht/nicht bis zum Endpunkt von pKt (true/false)

	// Test von jeder Strecke der this-EKante mit jeder pKt-Strecke
	for (long j = 0; j < _Size-1; j++)
	{
	ObjRechteck OCj = BuildRectangle (SP(j), SP(j+1));

		for (long jj = 0; jj < lKL-1; jj++)
		{
		ObjRechteck OCjj = BuildRectangle (pKt->SP(jj), pKt->SP(jj+1));
	
			if (! OCj.Durchschnitt (OCjj))
				continue;	// Container von this- und pKt-Strecke sind durchschnittsleer

			// Test, ob die Strecken, deren Container nicht durchschnittsleer sind, trotzdem
			// keinen gemeinsamen Punkt haben
			if ((TurnDirection (SP(j).X(), SP(j).Y(), SP(j+1).X(), SP(j+1).Y(),
								pKt->SP(jj).X(), pKt->SP(jj).Y()) *
				 TurnDirection (SP(j).X(), SP(j).Y(), SP(j+1).X(), SP(j+1).Y(),
								pKt->SP(jj+1).X(), pKt->SP(jj+1).Y()) > 0) ||
		    	(TurnDirection (pKt->SP(jj).X(), pKt->SP(jj).Y(), pKt->SP(jj+1).X(),
								pKt->SP(jj+1).Y(), SP(j).X(), SP(j).Y()) *
				 TurnDirection (pKt->SP(jj).X(), pKt->SP(jj).Y(), pKt->SP(jj+1).X(),
								pKt->SP(jj+1).Y(), SP(j+1).X(), SP(j+1).Y()) > 0))
				continue;	// this- und pKt-Strecke haben keine Gemeinsamkeiten

		SchnittErg Fo = KantenSchnitt (pKt, j, jj, ZPA, ZPE);

			if (ECHT == Fo || RAND_MIT == Fo || INNEN_MIT == Fo)
				return INNAUSS;		// mindestens ein Schnitt- bzw. Berührungspunkt

			if (RAND_OHNE == Fo || INNEN_OHNE == Fo)
			{
				// Da es am Anfang bzw. Ende einer offenen Kante per Definition keinen
				// Seitenwechsel gibt, muß hier noch gesondert getestet werden, ob nicht
				// vielleicht eine Überlappung vorliegt (05.11.98)
				if (!OverlapTest (pKt, jj, ZPA) &&
					!pKt->OverlapTest (this, j, ZPA))
					return INNAUSS;		// mindestens ein Berührungspunkt
			}

			if (UEBERLAPP == Fo)
			{
				if ((ZPA.X() == APX && ZPA.Y() == APY) ||
					(ZPE.X() == APX && ZPE.Y() == APY))
					bAP = true;
				if ((ZPA.X() == EPX && ZPA.Y() == EPY) ||
					(ZPE.X() == EPX && ZPE.Y() == EPY))
					bEP = true;
				bOverlap = true;
			}
		} // for
	} // for

	// Überlappungsbereich, aber kein Schnitt- bzw. Berührungspunkt, d.h. entweder liegt pKt
	// vollständig auf this-EKante bzw. beide Kanten sind völlig identisch (return INNERH) oder
	// this-EKante liegt vollständig auf pKt, ist aber kürzer als pKt (return INNAUSS)
	if (bOverlap)
	{
		if (bAP && bEP)
			return INNERH;
		return INNAUSS;
	}

	return AUSSERH;

} // KantenLage


// --------------------------------------------------------------------------------------------
// Lage der this-EKante (Vergleichsobjekt) und der pKt-EKante (Bezugsobjekt) zueinander;
// return-Wert (im OGC-Format) sind
//	EQUAL		beide Objekte sind vollständig identisch
//	WITHIN		Vergleichsobjekt liegt innerhalb des Bezugsobjektes
//	CONTAIN		Bezugsobjekt liegt innerhalb des Vergleichsobjektes
//	OVERLAP		Vergleichsobjekt liegt teilweise innerhalb, teilweise außerhalb des
//				Bezugsobjektes (der Durchschnitt beider Objekte muß eine Kante sein) 
//	ENTER		Vergleichsobjekt liegt teilweise innerhalb, teilweise außerhalb des
//				Bezugsobjektes (der Durchschnitt beider Objekte muß ein Punkt sein)
//	TOUCH		Vergleichsobjekt berührt das Bezugsobjekt von außen
//	DISJOINT	Vergleichsobjekt hat keinerlei Gemeinsamkeiten mit dem Bezugsobjekt
//	UNCLEAR		vorzeitiges Ende bei falschen Parametern, unzureichendem dynamischen
//				Speicher oder Abbruch durch den Anwender
OGCPosit _GEOMETR_EXPORT EKante :: LinesLocation (EKante* pKt)
{
	_ASSERTE (pKt != 0);

	if (! pKt) return UNCLEAR;

ObjRechteck OC1 = GetCont();
ObjRechteck OC2 = pKt->GetCont();

	if (!OC1.Durchschnitt (OC2))
		return DISJOINT;	// Container haben keinen Punkt gemeinsam

long lKL = pKt->ASP();
bool bOverlap = false;	// es gibt zwischen beiden Kanten mindestens 1 Überlappung (true)
bool bCross = false;	// es gibt zwischen beiden Kanten mindestens 1 Einschnitt (true)
bool bTouch = false;	// es gibt zwischen beiden Kanten mindestens 1 Berührung (true)
bool bClosedV = (SP(0) == SP(_Size-1));			// Vergleichsobjekt geschlossen (true)
bool bClosedB = (pKt->SP(0) == pKt->SP(lKL-1));	// Bezugsobjekt geschlossen (true)

long lIns;	// Index, bei dem ZPA bzw. ZPE eingefügt werden soll
bool bAdd;	// Parameter von EinfMarkPunkt(); wird hier nicht ausgewertet
DoublePair ZPA, ZPE;		// evtl. gemeinsame Punkte beider Kanten
MarkLine* pML1 = new MarkLine (_Size, -1, bClosedV);
MarkLine* pML2 = new MarkLine (lKL, -1, bClosedB);

	if (!pML1 || !pML1->Vektor() || !pML2 || !pML2->Vektor())
	{
		DEX_Error (RC_geo_obj3, EC_NOMEMORY);
		DELETE_OBJ (pML1);
		return UNCLEAR;
	}

	for (long j = 0; j < _Size; j++)
	{
		pML1->SetX (j, SP(j).X());		// 1. Markierung wird standardmäßig auf NORMAL gesetzt
		pML1->SetY (j, SP(j).Y());
	}

	for (long jj = 0; jj < lKL; jj++)
	{
		pML2->SetX (jj, pKt->SP(jj).X());
		pML2->SetY (jj, pKt->SP(jj).Y());
	}


	// Test von jeder this-Strecke mit jeder pKt-Strecke
	for (j = 0; j < _Size-1; j++)
	{
	ObjRechteck OC1 = BuildRectangle (SP(j), SP(j+1));

		for (long jj = 0; jj < lKL-1; jj++)
		{
		ObjRechteck OC2 = BuildRectangle (pKt->SP(jj), pKt->SP(jj+1));

			if (! OC1.EpsDurchschnitt (OC2))
				continue;	// this- und pKt-Strecke haben keine Gemeinsamkeiten

		SchnittErg Fo = KantenSchnitt (pKt, j, jj, ZPA, ZPE);

			if (KEINE == Fo)
				continue;

		bool bCurrentOverlap = false;	// UEBERLAPP beim aktuellen Test

			if (UEBERLAPP == Fo)
			{
				bOverlap = true;
				bCurrentOverlap = true;
			}

			else if (ECHT == Fo || RAND_MIT == Fo || INNEN_MIT == Fo)
				bCross = true;

			else if (RAND_OHNE == Fo || INNEN_OHNE == Fo)
			{
				if (0 == j || j == _Size - 2 || 0 == jj || jj == lKL - 2)
				{
					// Da es am Anfang bzw. Ende einer offenen Kante per Definition keinen
					// Seitenwechsel gibt, muß hier noch gesondert getestet werden, ob nicht
					// vielleicht eine Überlappung vorliegt
					if (OverlapTest (pKt, jj, ZPA) || pKt->OverlapTest (this, j, ZPA))
						continue;	// in for-Schleife weiter
					else if ((!bClosedV &&		// Vergleichsobjekt offen
							 (SP(0).EpsGleich (ZPA,0.,0.) ||
							  SP(_Size-1).EpsGleich (ZPA,0.,0.))) ||
							 (!bClosedB &&		// Bezugsobjekt offen
							 (pKt->SP(0).EpsGleich (ZPA,0.,0.) ||
							  pKt->SP(lKL-1).EpsGleich (ZPA,0.,0.))))
						bTouch = true;
					else
						bCross = true;
				}
				else
					bCross = true;
			}

			if (bCurrentOverlap)
			{
				if (!EinfIndex (SP(j), SP(j+1), j, pML1, ZPA, lIns))
					return UNCLEAR;
				EinfMarkPunkt (pML1, lIns, ZPA, INNERHALB, bAdd);
				if (!EinfIndex (pKt->SP(jj), pKt->SP(jj+1), jj, pML2, ZPA, lIns))
					return UNCLEAR;
				EinfMarkPunkt (pML2, lIns, ZPA, INNERHALB, bAdd);

				if (!EinfIndex (SP(j), SP(j+1), j, pML1, ZPE, lIns))
					return UNCLEAR;
				EinfMarkPunkt (pML1, lIns, ZPE, INNERHALB, bAdd);
				if (!EinfIndex (pKt->SP(jj), pKt->SP(jj+1), jj, pML2, ZPE, lIns))
					return UNCLEAR;
				EinfMarkPunkt (pML2, lIns, ZPE, INNERHALB, bAdd);
			}
		} // for
	} // for

	// wenn mehr als einer der 3 bool-Werte bOverlap, bCross und bTouch "true" ist, dann gilt
	// die folgende Priorität:
	//		bOverlap ist entscheidender als bCross ist entscheidender als bTouch;
	// deshalb ist die nachfolgende Reihenfolge der Abfrage dieser Werte von Bedeutung
	if (bOverlap)
	{
		if (bCross || bTouch)
			return OVERLAP;

	long lCnt1 = pML1->ADP();
	long lCnt2 = pML2->ADP();

		if (pML1->IsClosed()) lCnt1--;
		if (pML2->IsClosed()) lCnt2--;

		// die 1. Position in pML1 mit Markierung "INNERHALB" suchen (muß es immer geben)
		for (j = 0; j < lCnt1; j++)
			if (INNERHALB == pML1->GetMk1 (j))
				break;

		_ASSERTE (j < lCnt1);

		// danach die 1. Position, die nicht mit "INNERHALB" markiert ist, suchen (muß es nicht
		// geben)
		for (; j < lCnt1; j++)
			if (INNERHALB != pML1->GetMk1 (j))
				break;

		// die 1. Position in pML2 mit Markierung "INNERHALB" suchen
		for (long jj = 0; jj < lCnt2; jj++)
			if (INNERHALB == pML2->GetMk1 (jj))
				break;

		_ASSERTE (jj < lCnt2);

		for (; jj < lCnt2; jj++)
			if (INNERHALB != pML2->GetMk1 (jj))
				break;

		if (lCnt1 == lCnt2 && j == lCnt1 && jj == lCnt2)
			return EQUAL;

		if (j == lCnt1 && jj < lCnt2)
		{
			for (; jj < lCnt2; jj++)
				if (INNERHALB == pML2->GetMk1 (jj))
					return OVERLAP;
			return WITHIN;
		}

		if (j < lCnt1 && jj == lCnt2)
		{
			for (; j < lCnt1; j++)
				if (INNERHALB == pML1->GetMk1 (j))
					return OVERLAP;
			return CONTAIN;
		}

		return OVERLAP;
	}

	if (bCross)
		return ENTER;

	if (bTouch)
		return TOUCH;

	return DISJOINT;

} // LinesLocation


// --------------------------------------------------------------------------------------------
// Hilfsroutine für KantenLage();
// Test, ob die angezeigte Berührung nur scheinbar ist, weil sie am Rand eines
// Überlappungsbereiches diagnostiziert wurde; dann ist der return-Wert true;
// der Test wird nur am Anfangs- bzw. Endpunkt von offenen Kanten durchgeführt
bool EKante :: OverlapTest (EKante* pKt, long jj, DoublePair GP)
{
	if (SP(0) == SP(_Size-1))	// this-EKante geschlossen
		return false;

	_ASSERTE (pKt != 0);

DoublePair GP1, GP2;	// Parameter von GemeinsamePunkte(); werden hier nicht weiter
						// ausgewertet
SchnittErg Fo1 = KEINE, Fo2 = KEINE;	// return-Werte von GemeinsamePunkte()
long lKL = pKt->ASP();

long lGPI;				// Index des pKt-Punktes, der mit GP Eps-gleich ist
long lGPV, lGPN;		// Vorläufer- bzw. Nachfolger-Index von lGPI

	(pKt->SP(jj).EpsGleich (GP)) ? (lGPI = jj) : (lGPI = jj+1);

	if (pKt->SP(0) != pKt->SP(lKL-1))	// pKt-EKante offen
	{
		(lGPI > 0) ? (lGPV = lGPI-1) : (lGPV = -1);
		(lGPI < lKL-1) ? (lGPN = lGPI+1) : (lGPN = -1);
	}
	else								// pKt-EKante geschlossen
	{
		(lGPI > 0) ? (lGPV = lGPI-1) : (lGPV = lKL-2);
		(lGPI < lKL-1) ? (lGPN = lGPI+1) : (lGPN = 1);
	}

	if (SP(0).EpsGleich (GP))			// Anfangspunkt
	{
		if (lGPV >= 0)
			Fo2 = GemeinsamePunkte (SP(0), SP(1), pKt->SP(lGPI), pKt->SP(lGPV), GP1, GP2);

		if (lGPN >= 0)
			Fo1 = GemeinsamePunkte (SP(0), SP(1), pKt->SP(lGPI), pKt->SP(lGPN), GP1, GP2);
	}

	else if (SP(_Size-1).EpsGleich (GP))	// Endpunkt
	{
		if (lGPV >= 0)
			Fo2 = GemeinsamePunkte (SP(_Size-1), SP(_Size-2), pKt->SP(lGPI), pKt->SP(lGPV),
									GP1, GP2);
		if (lGPN >= 0)
			Fo1 = GemeinsamePunkte (SP(_Size-1), SP(_Size-2), pKt->SP(lGPI), pKt->SP(lGPN),
									GP1, GP2);
	}

	if (UEBERLAPP != Fo1 && UEBERLAPP != Fo2)
		return false;		// mindestens ein Berührungspunkt
	return true;

} // OverlapTest


// --------------------------------------------------------------------------------------------
// Verbindung zweier Kanten (this- und pKt-EKante);
// dazu wird der kleinste Abstand zwischen dem Anfangs- bzw. Endpunkt der this-EKante und dem
// Anfangs- bzw. Endpunkt der pKt-EKante mit der euklidischen Norm gesucht; ist dieser
// Abstand <= ulFill, dann werden die Kanten hier verbunden (Rückgabe von true); sonst keine
// Verbindung und Rückgabe von false
bool _GEOMETR_EXPORT EKante :: LinienVereinigung (EKante* pKt, ulong ulFill)
{
	_ASSERTE (pKt != 0);

	if (! pKt) return false;
	
long lKL = pKt->ASP();
EPunkt AP1 = SP(0);
EPunkt EP1 = SP(_Size-1);
EPunkt AP2 = pKt->SP(0);
EPunkt EP2 = pKt->SP(lKL-1);
int iKZ;	// Kennzeichen dafür, wie die vereinigte Linie zu bilden ist
			//   1  EP1, AP1, AP2, EP2
			//   2  AP2, EP2, AP1, EP1
			//   3  AP1, EP1, AP2, EP2
			//   4  AP1, EP1, EP2, AP2
ulong ulKlAbst = LONG_MAX;       // kleinster Abstand
ulong ulAbst1, ulAbst2, ulAbst3, ulAbst4;

	ulAbst1 = DtoL (AbstandPktPktE (AP1, AP2));
	if (ulAbst1 < ulKlAbst)
	{
		ulKlAbst = ulAbst1;
		iKZ = 1;
	}
	ulAbst2 = DtoL (AbstandPktPktE (AP1, EP2));
	if (ulAbst2 < ulKlAbst)
	{
		ulKlAbst = ulAbst2;
		iKZ = 2;
	}
	ulAbst3 = DtoL (AbstandPktPktE (EP1, AP2));
	if (ulAbst3 < ulKlAbst)
	{
		ulKlAbst = ulAbst3;
		iKZ = 3;
	}
	ulAbst4 = DtoL (AbstandPktPktE (EP1, EP2));
	if (ulAbst4 < ulKlAbst)
	{
		ulKlAbst = ulAbst4;
		iKZ = 4;
	}

	if (ulKlAbst > ulFill)
		return false;       // keine Vereinigung, da Lücke zu groß

	if ((ulAbst1 == 0 && ulAbst4 == 0) || (ulAbst2 == 0 && ulAbst3 == 0))
		return false;       // beide Kanten sind identisch
		
long k;		// Laufindex für evtl. Umkehrung der Durchlaufrichtung der this-EKante
EPunkt PP;

	switch (iKZ)
	{   
		case 1:  // vereinigte Kante ist EP1, AP1, AP2, EP2
			for (k = 0; k < _Size/2; k++)	// Durchlaufrichtung der this-EKante umkehren
			{
				PP = SP(_Size-k-1);
				SP(_Size-k-1) = SP(k);
				SP(k) = PP;
			}
			if (ulKlAbst != 0)		// "Lücke" zwischen beiden Kanten
				AddKantenStueck1 (pKt->Vektor(), 0, lKL-1, MOVEDIR_UP);
			else					// keine "Lücke", deshalb SP(0) nicht übernehmen
				AddKantenStueck1 (pKt->Vektor(), 1, lKL-1, MOVEDIR_UP);
			break;

		case 2:  // vereinigte Kante ist EP1, AP1, EP2, AP2
			for (k = 0; k < _Size/2; k++)
			{
				PP = SP(_Size-k-1);
				SP(_Size-k-1) = SP(k);
				SP(k) = PP;
			}
			if (ulKlAbst != 0)
				AddKantenStueck1 (pKt->Vektor(), lKL-1, 0, MOVEDIR_DOWN);
			else
				AddKantenStueck1 (pKt->Vektor(), lKL-2, 0, MOVEDIR_DOWN);
			break;

		case 3:  // vereinigte Kante ist AP1, EP1, AP2, EP2
			if (ulKlAbst != 0)
				AddKantenStueck1 (pKt->Vektor(), 0, lKL-1, MOVEDIR_UP);
			else
				AddKantenStueck1 (pKt->Vektor(), 1, lKL-1, MOVEDIR_UP);
			break;

		case 4:  // vereinigte Kante ist AP1, EP1, EP2, AP2
			if (ulKlAbst != 0)
				AddKantenStueck1 (pKt->Vektor(), lKL-1, 0, MOVEDIR_DOWN);
			else
				AddKantenStueck1 (pKt->Vektor(), lKL-2, 0, MOVEDIR_DOWN);
	}
	return true;
} // LinienVereinigung


// --------------------------------------------------------------------------------------------
// Verbindung zweier Kanten (this- und pKt-EKante);
// dazu wird der kleinste Abstand zwischen dem Anfangs- bzw. Endpunkt der this-EKante und dem
// Anfangs- bzw. Endpunkt der pKt-EKante mit der Maximum-Norm gesucht; gilt für die absolute
// Differenz der x-Koordinaten <= ulFillX sowie der y-Kordinaten <= ulFillY der beiden
// entsprechenden Punkte, dann werden die Kanten hier verbunden (Rückgabe von true); sonst
// keine Verbindung und Rückgabe von false
bool _GEOMETR_EXPORT EKante :: LinienVereinigung2 (EKante* pKt, ulong ulFillX, ulong ulFillY)
{
	_ASSERTE (pKt != 0);

	if (! pKt) return false;
	
long lKL = pKt->ASP();
EPunkt AP1 = SP(0);
EPunkt EP1 = SP(_Size-1);
EPunkt AP2 = pKt->SP(0);
EPunkt EP2 = pKt->SP(lKL-1);
int iKZ;	// Kennzeichen dafür, wie die vereinigte Linie zu bilden ist
			//   1  EP1, AP1, AP2, EP2
			//   2  AP2, EP2, AP1, EP1
			//   3  AP1, EP1, AP2, EP2
			//   4  AP1, EP1, EP2, AP2
ulong ulKlAbst = LONG_MAX;       // kleinster Abstand
ulong ulKlAbstX, ulKlAbstY;
ulong ulAbst1, ulAbst2, ulAbst3, ulAbst4;

	ulAbst1 = AbstandPktPktM (AP1, AP2);
	if (ulAbst1 < ulKlAbst)
	{
		ulKlAbstX = labs (AP1.X() -  AP2.X());
		ulKlAbstY = labs (AP1.Y() -  AP2.Y());
		ulKlAbst = ulAbst1;
		iKZ = 1;
	}
	ulAbst2 = DtoL (AbstandPktPktE (AP1, EP2));
	if (ulAbst2 < ulKlAbst)
	{
		ulKlAbstX = labs (AP1.X() -  EP2.X());
		ulKlAbstY = labs (AP1.Y() -  EP2.Y());
		ulKlAbst = ulAbst2;
		iKZ = 2;
	}
	ulAbst3 = AbstandPktPktM (EP1, AP2);
	if (ulAbst3 < ulKlAbst)
	{
		ulKlAbstX = labs (EP1.X() -  AP2.X());
		ulKlAbstY = labs (EP1.Y() -  AP2.Y());
		ulKlAbst = ulAbst3;
		iKZ = 3;
	}
	ulAbst4 = AbstandPktPktM (EP1, EP2);
	if (ulAbst4 < ulKlAbst)
	{
		ulKlAbstX = labs (EP1.X() -  EP2.X());
		ulKlAbstY = labs (EP1.Y() -  EP2.Y());
		ulKlAbst = ulAbst4;
		iKZ = 4;
	}

	if (ulKlAbstX > ulFillX || ulKlAbstY > ulFillY)
		return false;       // keine Vereinigung, da Lücke zu groß

	if ((0 == ulAbst1 && 0 == ulAbst4) || (0 == ulAbst2 && 0 == ulAbst3))
		return false;       // beide Kanten sind identisch
		
long k;		// Laufindex für evtl. Umkehrung der Durchlaufrichtung der this-EKante
EPunkt PP;

	switch (iKZ)
	{   
		case 1:  // vereinigte Kante ist EP1, AP1, AP2, EP2
			for (k = 0; k < _Size/2; k++)	// Durchlaufrichtung der this-EKante umkehren
			{
				PP = SP(_Size-k-1);
				SP(_Size-k-1) = SP(k);
				SP(k) = PP;
			}
			if (ulKlAbst != 0)		// "Lücke" zwischen beiden Kanten
				AddKantenStueck1 (pKt->Vektor(), 0, lKL-1, MOVEDIR_UP);
			else					// keine "Lücke", deshalb SP(0) nicht übernehmen
				AddKantenStueck1 (pKt->Vektor(), 1, lKL-1, MOVEDIR_UP);
			break;

		case 2:  // vereinigte Kante ist EP1, AP1, EP2, AP2
			for (k = 0; k < _Size/2; k++)
			{
				PP = SP(_Size-k-1);
				SP(_Size-k-1) = SP(k);
				SP(k) = PP;
			}
			if (ulKlAbst != 0)
				AddKantenStueck1 (pKt->Vektor(), lKL-1, 0, MOVEDIR_DOWN);
			else
				AddKantenStueck1 (pKt->Vektor(), lKL-2, 0, MOVEDIR_DOWN);
			break;

		case 3:  // vereinigte Kante ist AP1, EP1, AP2, EP2
			if (ulKlAbst != 0)
				AddKantenStueck1 (pKt->Vektor(), 0, lKL-1, MOVEDIR_UP);
			else
				AddKantenStueck1 (pKt->Vektor(), 1, lKL-1, MOVEDIR_UP);
			break;

		case 4:  // vereinigte Kante ist AP1, EP1, EP2, AP2
			if (ulKlAbst != 0)
				AddKantenStueck1 (pKt->Vektor(), lKL-1, 0, MOVEDIR_DOWN);
			else
				AddKantenStueck1 (pKt->Vektor(), lKL-2, 0, MOVEDIR_DOWN);
	}
	return true;
} // LinienVereinigung2


// --------------------------------------------------------------------------------------------
// this-Kontur wird durch pKont-Kontur geschnitten und die dabei evtl. neu erzeugten Flächen
// entspr. des vorgegebenen ulLageAusw (LINN bzw. LAUSS) in CL abgelegt;
// Test, ob die Objektcontainer der this-Kontur und der schneidenden pKont-Kontur
// durchschnittsleer sind, wird in Routine Aufbereitung2() durchgeführt;
// iKI1 ist der Index der this-Kontur, iKI2 der pKont-Kontur
bool EKante :: SchnittKonturMitKontur (EKante* pKont, int iKI1, int iKI2, ulong ulLageAusw,
									   ClipListe& CL)
{
	_ASSERTE (pKont != 0);

// aus Stützpunktfolge der this-Flächenkontur wird Vektor pML1, aus Stützpunktfolge der
// pKont-Kontur wird Vektor pML2 mit markierten Punkten erzeugt; diese Vektoren werden in
// Aufbereitung2() evtl. noch erweitert
bool bLeer, bAbbr;	// Parameter der Routine Aufbereitung2(); werden hier nicht ausgewertet
MarkLine* pML1 = new MarkLine (_Size, iKI1, true);
MarkLine* pML2 = new MarkLine (pKont->ASP(), iKI2, true);

	if (! pML1 || ! pML1->Vektor() || ! pML2 || ! pML2->Vektor())
	{
		DEX_Error (RC_geo_obj3, EC_NOMEMORY);
		DELETE_OBJ (pML1); DELETE_OBJ (pML2);
		return false;
	}

bool bRet = false;			// return-Wert
EFlaeche HF0 (this, 1);		// Hilfsflächen für AddClipObjekt, die aus der this-Kontur bzw.
EFlaeche HF1 (pKont, 1);	// aus der pKont-Kontur gebildet werden

	// pML1 und pML2 werden evtl. durch Routine Aufbereitung2() modifiziert; zurückgegeben
	// werden die um die Schnittpunkte erweiterten Vektoren pML1 und pML2
	if (!Aufbereitung2 (pKont, pML1, pML2, bLeer, bAbbr, 0))
	{
		if (bLeer && ulLageAusw & LAUSS)
		{
			// Objektnummer und Identifikator spielen hier keine Rolle, da Ergebnis als Insel
			// in eine Fläche eingefügt wird
			GeoFlaeche (0, 0, HF0).AddClipObjekt (CL);
			bRet = true;
		}

		DELETE_OBJ (pML1); DELETE_OBJ (pML2);
		return bRet;
	}

// Routine KantenPosit() ermittelt, ob die zu schneidende this-Kontur pML1 durch die
// pKont-Kontur zerlegt wird oder nicht
bool bOverlap;   // Parameter von KantenPosit(); werden
int iTouchOut;	// hier nicht ausgewertet
Posit posLage = KantenPosit (pKont, pML1, bOverlap, iTouchOut);

	switch (posLage)
	{
		case INNERH:	// this-Kontur innerhalb pKont-Kontur
		case INNERHB:
		case KONTUR:	// this-Kontur und pKont-Kontur sind identisch
		case GLEICH:	// this-Kontur und pKont-Kontur sind identisch
			if (ulLageAusw & LINN)
			{
				GeoFlaeche (0, 0, HF0).AddClipObjekt (CL);
				bRet = true;
			}
			break;

		case AUSSERH:	// this-Kontur außerhalb pKont-Kontur 
		case AUSSERHB:
			if (ulLageAusw & LAUSS)
			{
				GeoFlaeche (0, 0, HF0).AddClipObjekt (CL);
				bRet = true;
			}
			break;

		case UMSCHL:	// pKont-Kontur innerhalb this-Kontur
		case UMSCHLB:
			if (ulLageAusw & LINN)
			{
				GeoFlaeche (0, 0, HF1).AddClipObjekt (CL);
				bRet = true;
			}
			else		// ulLageAusw == LAUSS
				bRet = TeilFlaechen2 (pML1, pML2, 0, 0, ulLageAusw, CL);
			break;

		case INNAUSS:	// Zerlegen in Teilflächen
			bRet = TeilFlaechen2 (pML1, pML2, 0, 0, ulLageAusw, CL);
			break;

		case UNKLAR:	// Parameterfehler
			bRet = false;
			break;
	}

	DELETE_OBJ (pML1); DELETE_OBJ (pML2);
	return bRet;

} // SchnittKonturMitKontur


// --------------------------------------------------------------------------------------------
// Test, ob this-EKante und pKt-EKante geometrisch identisch sind; wenn ja, dann ist der
// return-Wert "true"
bool EKante :: GeometricalSameLines (EKante* pKt)
{
	_ASSERTE (pKt != 0);

long lCnt = pKt->ASP();

	if (_Size != lCnt)
		return false;

	if (SP(0) == pKt->SP(0))
	{
		for (long j = 1; j < _Size; j++)
			if (SP(j) != pKt->SP(j))
				return false;
		return true;
	}

	if (SP(0) == pKt->SP(lCnt-1))
	{
		for (long j = 1; j < _Size; j++)
			if (SP(j) != pKt->SP(_Size - j - 1))
				return false;
		return true;
	}

	return false;

} // GeometricalSameLines


// --------------------------------------------------------------------------------------------
// Test, ob eine Schleife am Kantenende bei Punkt (lXK,lYK) vorhanden ist und eine vorgebbare
// Mindestanzahl von Stützpunkten hat; wenn ja (true), wird in lPInd der Index zurückgegeben
bool EKante :: IsLoopLarge (KoOrd lXK, KoOrd lYK, long& lPInd)
{
// Abfrage in der RegDB, welche Mindestgröße eine abzutrennende Schleife haben muss
CCurrentUser cuExtConfig (KEY_READ, RegistryExtPathRein);
DWORD dwWert;
int iLoopLength;

	if (cuExtConfig.GetDWORD (RegSchleife, dwWert))
		iLoopLength = dwWert;
	else
		iLoopLength = iLoopLen;

	lPInd = -1;	// Index des "inneren" Stützpunktes, bei dem das Kantenende die Kante berührt

	for (long i = 1; i < _Size-1; i++)
	{
		if (lXK == SP(i).X() && lYK == SP(i).Y())
		{
			lPInd = i;	// Schleife ist vorhanden
			break;
		}			
	}

	if (-1 == lPInd) return false;	// keine Schleife bei Punkt (lXK,lYK) vorhanden

	// Schleife ist am Anfang der Kante
	if (lXK == SP(0).X() && lYK == SP(0).Y())
	{
		if (lPInd + 1 < iLoopLength)	// Schleife muss mindestens aus iLoopLength Stützpunkten bestehen
			return false;	// Schleife zu klein
	}

	// Schleife ist am Ende der Kante
	else if (lXK == SP(_Size-1).X() && lYK == SP(_Size-1).Y())
	{
		if (_Size - lPInd < iLoopLength)
			return false;	// Schleife zu klein
	}
	
	return true;
} // IsLoopLarge
