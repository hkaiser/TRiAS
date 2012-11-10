// Klasse, welches die Linienlaenge eines Objekts bestimmt --------
// File: VOBJPROP.HXX

#if !defined(_VOBJPROP_HXX)
#define _VOBJPROP_HXX

class ObjPropClass {
private:
	long _lONr;
	double _dLaenge;
	LPSTR _pBuffer;
	ULONG _uLen;  
	CoordTransX *_pCTF;

public:
// Konstruktor/Destruktor
	ObjPropClass ( CoordTransX *);
	~ObjPropClass (void);

	long &Object ( void ) { return _lONr; };
	void Eval ( long lONr, LPSTR pBuffer, ULONG uLen, ULONG * pW);
	double &Laenge ( void ) { return _dLaenge; };
	void Release ( void ) { return; };
	double GetPolyLen ( double *, double *, long);
	double GetLinienParams ( void );
};

#endif // _VOBJPROP_HXX
