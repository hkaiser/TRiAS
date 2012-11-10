// Memberfunktionen fuer kombiniertes Edit/SpinButton/FixedText-Control -------
// File: SPINCTRL.CXX

#include "trias03p.hxx"

#include <muscroll.hxx>
#include <numedit.hxx>
#include <spinctrl.hxx>

// Konstruktoren --------------------------------------------------------------
SpinEdit :: SpinEdit (pDialogWindow pW, ResID rsc, Range R) 
	  : NumEdit (pW, rsc, 10) 
{
	_R = R;
}

Range SpinEdit :: SetRange (Range newR) 
{
Range oldR = _R;

	_R = newR;

return oldR;
}

int SpinEdit :: PostValidate (int Value) {

	if (Value < _R.Min()) return _R.Min();
	if (Value > _R.Max()) return _R.Max();
	return Value;
}


// Eigentliches kombiniertes Control ------------------------------------------
SpinControl :: SpinControl (pDialogWindow pW, uint rscEdit, uint rscSpin, Range R) 
	     : SpinButton (pW, rscSpin),
	       SpinControlEdit (pW, rscEdit, R)
{
	SpinButton.SetScrollRange (R);
}

short SpinControl :: SetValue (short newVal) {

	SpinControlEdit.SetValue (newVal);
	return SpinButton.SetCurrPos (newVal);
}

