/*------------------------------------------------------------------------

File: V_MEMOFD.HXX (Header)

View_MemoField -
gibt den Inhalt eines Memofeldes in ein separates, modales (z.Z. nicht 
editierbares) Fenster aus.

Erarbeitet: J. Benkenstein							   am: 19. Dez. 1991
												  Stand vom: 23. Dez. 1993
---------------------------------------------------------------------------*/

#include "pheader.h"

#include "V_MEMOFD.htp"		 	// Selektion der zu comp. Klassen
#include <commonvu.hxx>
			 
#include "dbaseext.hr"		   	// globale Konstanten
#include "v_memofd.hxx"		 	// zugehöriges Header-File

#pragma warning (disable : 4355)
MultiLineDialog :: MultiLineDialog (pWindow pW, ResID Res, ResourceFile* pRF)
: ModeLessDialog (pW, Res), MultiLine (this, ResID (IDE_MEMO, pRF)) {
// "einpassen" des Controls
	MultiLine.ChangePosition (Point (0, 0));
	Rectangle Rect (CanvasRect ());
	Dimension Dim (Rect.Right () - Rect.Left (), Rect.Top() - Rect.Bottom ());
	MultiLine.ChangeSize (Dim);
}							   
#pragma warning (default : 4355)

// MultiLineEdit neuzeichnen
void __export MultiLineDialog :: ReSize (ReSizeEvt RSE)
{
	Dimension Dim (RSE.GetNewWidth (), RSE.GetNewHeight ());
	MultiLine.ChangePosition (Point (0, 0));
	MultiLine.ChangeSize (Dim);
}


void __export MultiLineDialog :: VertScroll (ScrollEvt SE) {
	if (SE.GetScrollType () != ThumbDrag)
		MultiLine.ScrollVertical (SE.GetPos () - SE.GetOldPos ());
}

void __export MultiLineDialog :: FocusChange (FocusChangeEvt) {
	MultiLine.ChangeSelection (Selection (0, 0));
}
