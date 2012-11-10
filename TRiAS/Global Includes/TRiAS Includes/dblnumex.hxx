// NumEdit, welches DoubleWerte einlesen kann ---------------------------------
// File: DBLNUMEX.HXX

#if !defined(_DBLNUMEX_HXX)
#define _DBLNUMEX_HXX

class DoubleNumEditX : public NumEditX {
protected:
	void KeyDown (KeyEvt);
	
public:
	DoubleNumEditX (pDialogWindow, ResID);
	DoubleNumEditX (pWindow, uint, Point, Dimension);
	~DoubleNumEditX (void);

	bool GetValue (double &);
	void SetValue (double);
};

#endif // _DBLNUMEX_HXX

