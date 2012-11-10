// Klasse, die ObjEigenschaften simuliert  ---------------------
// File: VOBJPROP.CXX

#include "kompp.hxx"
#include "version.h"
#include "kompias.h"
#include "about.h"
#include <igeometr.hxx>
#include "triasdef.h"
#include "kompdef.h"
#include "vobjprop.hxx"

#include "about.hxx"

//--------------------------------------------------------------------------
#pragma warning (disable: 4355)

ObjPropClass :: ObjPropClass ( CoordTransX *pCTF )
{
// Variablen initialisieren
	_lONr = 0L;
	_dLaenge = 0.0;
	_pBuffer = NULL;
	_uLen = 0;
	_pCTF = NULL;
	if ( pCTF)
		_pCTF = pCTF;
}

#pragma warning (default: 4355)

ObjPropClass :: ~ObjPropClass (void) 
{
	DELETE_OBJ (_pBuffer);
}
//-------------------------------------------------------------------------
void ObjPropClass :: Eval ( long lONr, LPSTR pBuffer, ULONG uLen, ULONG * pW)
{
	_lONr = lONr;
	_uLen = uLen;

	if ( !_pBuffer )
		_pBuffer = new char [uLen];
	if (!pBuffer)
		return;
	_dLaenge = GetLinienParams();
	*pBuffer = '\0';
	*_pBuffer = '\0';
	ST_DtoA ( _pBuffer, "%10.2f",_dLaenge);
	strcpy ( pBuffer, _pBuffer);
	return;
}
//--------------------------------------------------------------------------
double ObjPropClass :: GetLinienParams ( void) 
{
// allgemeine Info's zur Linie ranholen
OBJSTATISTIK OS;
double LL = 0.0;

	OS.dwSize = sizeof(OBJSTATISTIK);
	OS.lONr = _lONr;
	if (!DEX_GetObjStatistik (OS))
		return 0.0;

	if (OS.iObjTyp == OT_KANTE) {
		OBJGEOMETRIE OG;
		double *pX = new double [OS.lCnt];
		double *pY = new double [OS.lCnt];

		if (pX == NULL || pY == NULL) {
			DELETE_OBJ (pX);
			DELETE_OBJ (pY);
			return 0.0;
		}

		memset (&OG,'\0',sizeof(OBJGEOMETRIE));
		OG.dwSize = sizeof(OBJGEOMETRIE);
		OG.lONr = _lONr;
		OG.lCnt = OS.lCnt;
		OG.pdblX = pX;
		OG.pdblY = pY;
		OG.iFlags = OGConverted;
		if (DEX_GetObjGeometrie (OG)) {
			//Linienparameter
			LL = GetPolyLen ( pX, pY, OG.lCnt );
		}

	// aufräumen
		DELETE_OBJ (pX);
		DELETE_OBJ (pY);
	}
	return LL;
}	
//----------------Linienberechnung--------------------------------------
double ObjPropClass :: GetPolyLen ( double *pX, double *pY, long Count) 
{ 

	if ( _pCTF == NULL )
		return 0.0;

	double polylen =0.0;
	long i;
	double *pX1,*pY1,*pXX,*pYY;
	
	Bool Metric = _pCTF->isMetric();	// metrische Koord.???

	Punkt P;
	double Min,Max;

	if ( !Metric) {

		for ( long i = 0; i < Count ; i++ ) { 
	
			Min = *( pX + i );
			Max = *( pY + i );
			_pCTF->Scale ( Min, Max, P );

			_pCTF->Metric ( P, &Min, &Max);

			*( pX + i ) = Min;
			*( pY + i ) = Max;

		}

	}

	pXX = pX;
	pX1 = pX + 1;
	pYY = pY;
	pY1 = pY + 1;

	for ( i = 1 ; i < Count ; i++ )  {
		polylen = polylen + sqrt ( ( *pX1 - *pXX ) * ( *pX1 - *pXX ) +( *pY1 - *pYY ) * ( *pY1 - *pYY ) );
		if ( i < Count-1) {
		  pXX = pX1 ;
		  pX1 = pX1 + 1;
		  pYY = pY1;
		  pY1 = pY1 + 1;
		}
	}
	return polylen;
}
//------------------------------------------------------------------
//------------VOBJPROP.CXX
