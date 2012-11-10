/*------------------------------------------------------------------------

File: V_MEMOFD.HXX (Header)

View_MemoField -
gibt den Inhalt eines Memofeldes in ein separates, modales (z.Z. nicht 
editierbares) Fenster aus.

Erarbeitet: J. Benkenstein							   am: 19. Dez. 1991
												  Stand vom: 23. Dez. 1993
---------------------------------------------------------------------------*/

#ifndef V_MEMOFD_HXX
#define V_MEMOFD_HXX
	
// Darstellung des Inhalts eines Memofeldes
class MultiLineDialog : public ModeLessDialog {
protected:
	void ReSize (ReSizeEvt);
	void VertScroll (ScrollEvt);
	void FocusChange (FocusChangeEvt);
public:
	MultiLineEdit MultiLine;
	MultiLineDialog (pWindow, ResID, ResourceFile*);
};

#endif  // V_MEMOFD_HXX
