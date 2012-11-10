// Umrechnen von Koordinaten -----------------------------
// File: TRFKOORD.CXX


#include "statistp.hxx"
#include "geostat.h"
//#include "dirmath.h"

#include "trfkoord.hxx"



// Konstruktor ----------------------------------------------------------------
StatistTrfKoord :: StatistTrfKoord ( CoordTransX *pCTF, long *pContainer ) 
{
	_CONT[0] = *pContainer;
	_CONT[1] = *(pContainer + 1);
	_CONT[2] = *(pContainer + 2);
	_CONT[3] = *(pContainer + 3);
	_pCTF = NULL;
	if ( !pCTF )
		return;
	_pCTF = pCTF;
	_pCoordText = NULL;
}

// Destruktor
StatistTrfKoord :: ~StatistTrfKoord (void) 
{
	DELETE_OBJ ( _pCoordText);
}

//	DB-Koordinaten in Transform-Koordinaten umwandeln
Bool StatistTrfKoord :: Transform ( void ) 
{

double Min,Max;
	if ( _pCTF == NULL ) {
		return FALSE;
	}

	Punkt P;

	Min = (double) _CONT[0];
	Max = (double) _CONT[2];
	Bool TRF = _pCTF->Transform ( &Min, &Max);
	if ( !TRF)
		return FALSE;
	_CONT[0] = (long)Min;
	_CONT[2] = (long)Max;

	Min = (double) _CONT[1];
	Max = (double) _CONT[3];
	_pCTF->Transform ( &Min, &Max);

	_CONT[1] = (long)Min;
	_CONT[3] = (long)Max;

	return TRUE;
}

//	DB-Koordinaten in ASC-Koordinaten umwandeln
void StatistTrfKoord :: FromDBToAsc ( void ) 
{

double Min,Max;
	if ( _pCTF == NULL ) {
		return;
	}

Punkt P;

#if _MSC_VER >= 1100
	P.SetX(_CONT[0]);
	P.SetY(_CONT[2]);
#else
	P.X() = _CONT[0];
	P.Y() = _CONT[2];
#endif // _MSC_VER >= 1100

	_pCTF->UnScale ( P, &Min, &Max);
	_CONT[0] = (long)Min;
	_CONT[2] = (long)Max;

#if _MSC_VER >= 1100
	P.SetX(_CONT[1]);
	P.SetY(_CONT[3]);
#else
	P.X() = _CONT[1];
	P.Y() = _CONT[3];
#endif // _MSC_VER >= 1100

	_pCTF->UnScale ( P, &Min, &Max);

	_CONT[1] = (long)Min;
	_CONT[3] = (long)Max;

}
//	ASC-Koordinaten in DB-Koordinaten umwandeln
void StatistTrfKoord :: FromAscToDB ( void ) 
{

double Min,Max;
	if ( _pCTF == NULL ) {
		return;
	}

Punkt P;

	Min = _CONT[0];
	Max = _CONT[2];
	_pCTF->Scale ( Min, Max, P);
#if _MSC_VER >= 1100
	_CONT[0] = P.GetX();
	_CONT[2] = P.GetY();
#else
	_CONT[0] = P.X();
	_CONT[2] = P.Y();
#endif // _MSC_VER >= 1100


	Min = _CONT[1];
	Max = _CONT[3];
	_pCTF->Scale ( Min, Max, P);

#if _MSC_VER >= 1100
	_CONT[1] = P.GetX();
	_CONT[3] = P.GetY();
#else
	_CONT[1] = P.X();
	_CONT[3] = P.Y();
#endif // _MSC_VER >= 1100


}
//	DB-Koordinaten in metrische Koordinaten umwandeln
Bool StatistTrfKoord :: isDBMetric ( void ) 
{
Bool Metric = FALSE;
	if ( _pCTF == NULL ) {
		return Metric;
	}
	Metric = _pCTF->isMetric();
	return Metric;
		
}
//	DB-Koordinaten in metrische Koordinaten umwandeln
void StatistTrfKoord :: FromDBToMetric ( void ) 
{

double Min,Max;
	if ( _pCTF == NULL ) {
		return;
	}

Punkt P;

	for ( long i = 0; i < 2 ; i++ ) { 
#if _MSC_VER >= 1100
		P.SetX(_CONT[i]);
		P.SetY(_CONT[i+2]);
#else
		P.X() = _CONT[i];
		P.Y() = _CONT[i+2];
#endif // _MSC_VER >= 1100
		
		_pCTF->Metric ( P, &Min, &Max);
		_CONT[i] = (long)Min;
		_CONT[i+2] = (long)Max;
	}
	return;
}
//	DB-Koordinaten in metrische Koordinaten umwandeln
void StatistTrfKoord :: FromAscToMetric ( void ) 
{

double Min,Max;
	if ( _pCTF == NULL ) {
		return;
	}

Punkt P;

	for ( long i = 0; i < 2 ; i++ ) { 
		Min = (double) _CONT[i];
		Max = (double) _CONT[i+2];
		_pCTF->Scale ( Min, Max, P );
		_pCTF->Metric ( P, &Min, &Max);
		_CONT[i] = (long)Min;
		_CONT[i+2] = (long)Max;
	}
	return;
}

//	ASC-Koordinaten liefern
void StatistTrfKoord :: GetKoord ( long *pContainer ) 
{
	*pContainer = _CONT[0];
	*(pContainer + 1) = _CONT[1];
	*(pContainer + 2) = _CONT[2];
	*(pContainer + 3) = _CONT[3];
	return;
}

//	Nichtmetrische Koordinaten in Text
char *StatistTrfKoord :: TransToLoR ( void ) 
{ 
	if ( _pCTF == NULL ) {
		return NULL;
	}

	if ( !_pCoordText)
		_pCoordText = new char [_MAX_PATH];
	if (!_pCoordText)
		return NULL;
	double ValueX = ( double ) _CONT[0];
	double ValueY = ( double ) _CONT[3];

//	_pCoordText = _pCTF->CoordTransToString ( Value, TRUE, _pCoordText, _MAX_PATH);
	_pCoordText = _pCTF->CoordTransToStringEx ( ValueX, ValueY, TRUE, _pCoordText, _MAX_PATH);

	return _pCoordText;
}
char *StatistTrfKoord :: TransToRuR ( void ) 
{
	if ( _pCTF == NULL ) {
		return NULL;
	}

	if ( !_pCoordText)
		_pCoordText = new char [_MAX_PATH];
	if (!_pCoordText)
		return NULL;
	double ValueX = ( double ) _CONT[1];
	double ValueY = ( double ) _CONT[2];

//	_pCoordText = _pCTF->CoordTransToString ( Value, TRUE, _pCoordText, _MAX_PATH);
	_pCoordText = _pCTF->CoordTransToStringEx ( ValueX, ValueY, TRUE, _pCoordText, _MAX_PATH);

	return _pCoordText;
}
char *StatistTrfKoord :: TransToLoH ( void ) 
{
	if ( _pCTF == NULL ) {
		return NULL;
	}

	if ( !_pCoordText)
		_pCoordText = new char [_MAX_PATH];
	if (!_pCoordText)
		return NULL;
	double ValueY = ( double ) _CONT[3];
	double ValueX = ( double ) _CONT[0];

	_pCoordText = _pCTF->CoordTransToStringEx ( ValueX, ValueY, FALSE, _pCoordText, _MAX_PATH);

	return _pCoordText;
}
char *StatistTrfKoord :: TransToRuH ( void ) 
{
	if ( _pCTF == NULL ) {
		return NULL;
	}

	if ( !_pCoordText)
		_pCoordText = new char [_MAX_PATH];
	if (!_pCoordText)
		return NULL;

	double ValueY = ( double ) _CONT[2];
	double ValueX = ( double ) _CONT[1];

//	_pCoordText = _pCTF->CoordTransToString ( Value, FALSE, _pCoordText, _MAX_PATH);
	_pCoordText = _pCTF->CoordTransToStringEx ( ValueX, ValueY, FALSE, _pCoordText, _MAX_PATH);

	return _pCoordText;
}
//---------------------------------TRFKOORD.CXX---------------------------
