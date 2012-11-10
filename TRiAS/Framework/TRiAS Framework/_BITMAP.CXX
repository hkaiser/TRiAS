/* $Header:   G:/cv.win/pvcs/commonvu/src/_bitmap.cxv   1.4   04 Oct 1991 12:52:20   RONAN  $
 *
 *	_ b i t m a p . c x x
 *
 *  Copyright (c) 1992 Trischford Limited 
 *  ( A wholly owned subsidary of Computer Associates International, Inc)
 *  All Rights Reserved
 *
 *	Version 3.1			Nov 1992
 *
 *	Mods Log:
 *	0.0		89oct	Created a new to be puiblic interface
 */

#include "tfrmpre.hxx"


_DLLENTRY Bitmap:: Bitmap	( Dimension size, BOOL monochrome, pushort BitString )
{
	bitmap_Imp = new Bitmap_Imp (size, monochrome, BitString);
	
}	// End of "Bitmap" CONSTRUCTOR


_DLLENTRY Bitmap:: Bitmap	(ResID RscName)
{
	bitmap_Imp = new Bitmap_Imp (RscName);

}	// End of "Bitmap" CONSTRUCTOR "(ResID)"


// neuer Konstruktor (from scratch) -------------------------------------------
_DLLENTRY Bitmap :: Bitmap	(HBITMAP hBmp)
{
	bitmap_Imp = new Bitmap_Imp (hBmp);
}

// #HK970824
_DLLENTRY Bitmap::Bitmap (HBITMAP hBmp, BOOL fAutoDetach)
{
	bitmap_Imp = new Bitmap_Imp (hBmp, fAutoDetach);
}

// #HK970123
// LoadMappedBitmap
_DLLENTRY Bitmap::Bitmap (ResID uiRes, LPCOLORMAP pMap, int iMapSize, UINT uiFlags)
{
	bitmap_Imp = new Bitmap_Imp (uiRes, pMap, iMapSize, uiFlags);
}

_DLLENTRY Bitmap:: ~Bitmap	(void)
{
	delete	bitmap_Imp;
	
}	// End of "Bitmap" FUNCTION "Delete"

HBITMAP _DLLENTRY Bitmap::Detach (void)
{
	return	bitmap_Imp->Detach();
}

ulong	 _DLLENTRY Bitmap:: SetBits	( ulong Count, pushort BitString )
{
	return	bitmap_Imp->SetBits(Count, BitString);

}	// End of "Bitmap" FUNCTION "SetBits"


ulong	 _DLLENTRY Bitmap:: GetBits	( ulong Count, pushort BitString )
{
	return	bitmap_Imp->GetBits(Count, BitString);
	
}	// End of "Bitmap" FUNCTION "GetBits"


Dimension	 _DLLENTRY Bitmap:: GetSize	()
{
	return	bitmap_Imp->GetSize();	

}	// End of "Bitmap" FUNCTION "GetSize"


void	 _DLLENTRY Bitmap:: SetSize	( Dimension size )
{
	bitmap_Imp->SetSize( size );
	
}	// End of "Bitmap" FUNCTION "SetSize"


HBITMAP	 _DLLENTRY Bitmap::  Handle ( Service s_ID )
{
	if (NULL == this)
		return NULL;
	if ( s_ID == API_BITMAP_HBITMAP )
		return bitmap_Imp -> Handle(s_ID);
	else
		return 0;
}


