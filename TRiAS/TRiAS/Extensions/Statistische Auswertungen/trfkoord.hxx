// Klassendeklarationen fÅr Koordinatentransformationen
// File: TRFKOORD.HXX

#if !defined(_TRFKOORD_HXX)
#define _TRFKOORD_HXX

#if !defined(NOTRFKOORD)

// Verwaltung einer Koordinatentrf.
class StatistTrfKoord {
private:
	long _CONT[4];	// Container
	CoordTransX *_pCTF;
	char *_pCoordText;

public:
// Konstruktor/Destruktor
		StatistTrfKoord ( CoordTransX *pCTF, long *pContainer);
		~StatistTrfKoord (void);

// Memberfunktionen
	void FromAscToDB ( void );
	void FromDBToAsc ( void );
	void FromAscToMetric ( void );
	void FromDBToMetric ( void );
	void GetKoord ( long *pContainer);
	Bool isDBMetric( void );
	Bool Transform ( void );
	char *TransToLoR (void);
	char *TransToRuR (void);
	char *TransToLoH (void);
	char *TransToRuH (void);

};

#endif // NOTRFKOORD

#endif // _TRFKOORD_HXX
