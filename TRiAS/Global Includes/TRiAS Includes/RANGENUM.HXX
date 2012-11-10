// Numedit, welches automatisch vorgegebene Grenzwerte überprüft --------------
// File: RANGENUM.HXX

#if !defined(_RANGENUM_HXX)
#define _RANGENUM_HXX

class RangeNumEdit : public NumEditX {
private:
	Range m_R;		// BereichsTest
	
protected:
	int PostValidate (int iVal);

public:
// Konstruktor
		RangeNumEdit (pDialogWindow p, ResID resID, Range r, 
			      short iBase = 10);
		RangeNumEdit (pWindow parent, uint id, Point p, 
			      Dimension d, Range r, short iBase = 10);
// Destruktor
		~RangeNumEdit (void);
};

#endif // _RANGENUM_HXX

