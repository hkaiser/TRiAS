// Wertepaar zweier DoubleWerte
// File DBLPAIR.HXX

#if !defined(_DBLPAIR_HXX)
#define _DBLPAIR_HXX

class DoublePair {
protected:
	double _X;
	double _Y;

public:
		DoublePair (double x = 0.0, double y = 0.0) 
						{ _X = x; _Y = y; }

	double &Width (void) const { return _X; }
	double &Height (void) const { return _Y; }
	double & X (void) { return _X; }
	double & Y (void) { return _Y; }
};

#endif 	// _DBLPAIR_HXX
