// Umrechnen von Koordinaten in einem Vektor-----------------------------
// File: TRFVECT.CXX

#include "statistp.hxx"
//#include <igeometr.hxx>

#include "geostat.h"
//#include "dirmath.h"

#include "trfvect.hxx"



// Konstruktor ----------------------------------------------------------------
#if _TRiAS_VER < 0x0400
StatistTrfVect :: StatistTrfVect ( CoordTransX *pCTF, long *pL, long *pR , long Count ) 
#else
StatistTrfVect :: StatistTrfVect ( CoordTransX *pCTF, double *pL, double *pR , long Count ) 
#endif
{
	_pCL = pL;
	_pCR = pR;
	_Count = Count;
	_pCTF = NULL;	
	if ( !pCTF )
		return;
	_pCTF = pCTF;

}

// Destruktor
StatistTrfVect :: ~StatistTrfVect (void) 
{

}


//	DB-Koordinaten in metrische Koordinaten umwandeln
Bool StatistTrfVect :: isDBMetric ( void ) 
{
Bool Metric = FALSE;
	if ( _pCTF == NULL ) {
		return Metric;
	}
	Metric = _pCTF->isMetric();
	return Metric;
		
}
//	DB-Koordinaten in metrische Koordinaten umwandeln
void StatistTrfVect :: FromDBToMetric ( double *pDCL, double *pDCR ) 
{

	double Min,Max;
	if ( _pCTF == NULL )
		return;
	if (!pDCL || !pDCR)
		return;
//---------------------------------------------------
#if defined(WIN32)

	LPVOID pParams = NULL;

// Version 4.0
#if _TRiAS_VER >= 0x0400
	LPVOID pParamI = NULL;
	_pCTF -> GetInvTransformParam (*_pCL, *_pCR, &pParamI);
	double lX = *_pCL;
	double lY = *_pCR;
	_pCTF -> InvTransformEx( &lX ,  &lY , pParamI);
	Punkt P (lX, lY);
	_pCTF -> GetMetricParam (P, &pParams);

#else
	Punkt P (*_pCL, *_pCR);

	_pCTF -> GetMetricParam (P, &pParams);
#endif


	for ( long i = 0; i < _Count ; i++ ) { 
	
#if _TRiAS_VER >= 0x0400
		_pCTF -> InvTransformEx(( _pCL + i ), ( _pCR + i ), pParamI);
		_pCTF->MetricEx (*( _pCL + i ),*( _pCR + i ), &Min, &Max, pParams);
#else

#if _MSC_VER >= 1100
		P.SetX(*( _pCL + i ));
		P.SetY(*( _pCR + i ));
#else
		P.X() = *( _pCL + i );
		P.Y() = *( _pCR + i );                
#endif // 

		_pCTF->MetricEx ( P, &Min, &Max, pParams);
#endif

		*( pDCL + i ) = Min;
		*( pDCR + i ) = Max;

	}

#if _TRiAS_VER >= 0x0400
	_pCTF -> FreeInvTransformParam(pParamI);
#endif
	_pCTF -> FreeMetricParam(pParams);	// #HK981214
	
//	CoTaskMemFree (pParams);		// OLE task allocator

#endif // WIN32
	return;
}
//	DB-Koordinaten in ASC-Koordinaten umwandeln
void StatistTrfVect :: FromDBToASC ( double *pDCL, double *pDCR ) 
{

	if ( _pCTF == NULL )
		return;
	if (!pDCL || !pDCR)
		return;

// Version 4.0
#if _TRiAS_VER >= 0x0400

	LPVOID pParams = NULL;
	_pCTF -> GetInvTransformParam (*_pCL, *_pCR, &pParams);

#else
	double Min,Max;

	Punkt P;
#endif

	for ( long i = 0; i < _Count ; i++ ) { 

#if _TRiAS_VER < 0x0400
		
#if _MSC_VER >= 1100
		P.SetX(*( _pCL + i ));
		P.SetY(*( _pCR + i ));
#else
		P.X() = *( _pCL + i );
		P.Y() = *( _pCR + i );                
#endif // 
	
		_pCTF->UnScale ( P, &Min, &Max);
		*( pDCL + i ) = Min;
		*( pDCR + i ) = Max;
#else
		_pCTF -> InvTransformEx(( _pCL + i ), ( _pCR + i ), pParams);
		*( pDCL + i ) = *( _pCL + i );
		*( pDCR + i ) = *( _pCR + i );

#endif


	}

#if _TRiAS_VER >= 0x0400
	_pCTF -> FreeInvTransformParam(pParams);
#endif

	return;
}

