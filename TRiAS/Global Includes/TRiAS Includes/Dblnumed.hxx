// NumEdit, welches DoubleWerte einlesen kann ---------------------------------
// File: DBLNUMED.HXX

#if !defined(_DBLNUMED_HXX)
#define _DBLNUMED_HXX

#include <NumEdit.hxx>

class _TRIAS03_ENTRY DoubleNumEdit : public NumEdit {
private:
	double m_dblMin;
	double m_dblMax;

protected:
	void KeyDown (KeyEvt);
	void FocusChange (FocusChangeEvt);
	
public:
		DoubleNumEdit (pDialogWindow, ResID);
		DoubleNumEdit (pWindow, uint, Point, Dimension);
		~DoubleNumEdit (void);

	bool GetValue (double &);
	void SetValue (double);

	void SetMargins (double dMin, double dMax);
	bool GetMargins (double &rdMin, double &rdMax);
};

#endif // _DBLNUMED_HXX

