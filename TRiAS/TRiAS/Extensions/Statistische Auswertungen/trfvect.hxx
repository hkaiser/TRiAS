// Klassendeklarationen fÅr Koordinatentransformationen
// File: TRFVECT.HXX

#if !defined(_TRFVECT_HXX)
#define _TRFVECT_HXX

#if !defined(NOTRFKOORD)

// Verwaltung einer Koordinatentrf.
class StatistTrfVect {
private:
#if _TRiAS_VER < 0x0400
	long *_pCL;
	long *_pCR;
#else
	double *_pCL;
	double *_pCR;
#endif

	long _Count;
	CoordTransX *_pCTF;

public:
// Konstruktor/Destruktor
#if _TRiAS_VER < 0x0400
		StatistTrfVect ( CoordTransX *pCTF, long *pL, long *pR, long Count);
#else
		StatistTrfVect ( CoordTransX *pCTF, double *pL, double *pR, long Count);
#endif
		~StatistTrfVect (void);

// Memberfunktionen
	void FromDBToMetric ( double *pDX, double *pDY );
	void FromDBToASC ( double *pDX, double *pDY );
	Bool isDBMetric( void );
};

#endif // NOTRFKVECT

#endif // _TRFVECT_HXX
