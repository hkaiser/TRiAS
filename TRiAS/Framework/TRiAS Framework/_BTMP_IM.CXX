/* $Header:   G:/cv.win/pvcs/commonvu/src/_btmp_im.cxv   3.0.1.0   14 Jul 1992 11:48:24   RONAN  $
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
 *	0.0	ferg	05oct88	--------- Milestone 2.. Beta 2 shipped--------
 *	0.1	jk		24oct88 Delete function made into destructor.
 *	0.2	jk		15nov88	Bitmap Ctor from resource.
 *	0.3	ferg	15nov88	get AppInst from DLL data seg using _AppFind.
 *	0.4 jk		29nov88	------ Milestone 2A. Beta 2A shipped ------
 *	0.5 jk		02dec88	Fast Compile defines added.
 *  1.0	rs		29mar89 -------Release 1.0 ship date ----------------
 *  1.1	rs		07jul89 -------Release 1.0a ship date ---------------
 *	1.2 rs		01feb90	Rewrite of Bitmap::Dimension to work in all 
 *						circumstances.
 *	2.0 rs		19Jun90 rs from nc Apr90 - Hiding
 */

#include "tfrmpre.hxx"

Bitmap_Imp::  Bitmap_Imp (Dimension size, BOOL monochrome, pushort BitString)
{

	m_fAutoDetach = false;
	DeviceDependent = true;
	BitsPerPixel = 1;
	if (monochrome) 
		ColorPlanes = 1;
	else 
		ColorPlanes = 3;

//	Currently, only 3-Plane 1-Bit colour and 1-Plane 1-Bit mono are supported

bool	allocated_locally	= false;


	if	( !BitString )
	{
		uint	nWords;		// Number of words (16-Bits) to allocate


		nWords		= ((( size.Width () * BitsPerPixel + 15 ) >> 4 )	// # words per row
						* size.Height ())				// by # rows
						* ColorPlanes;	// by # planes

		BitString	= new unsigned short[ nWords ];

		while	( nWords-- )
			BitString[ nWords ]	= 0;

		allocated_locally		= true;
	}	// End of IF

	hBitmap	= CreateBitmap	(	size.Width (),	size.Height (),
								ColorPlanes,
								BitsPerPixel,
								BitString );
	CV_ASSERT_VALID(hBitmap);
	if	( allocated_locally )
		delete	BitString;

}	// End of "Bitmap_Imp" CONSTRUCTOR

															// * 0.2 Begin *
Bitmap_Imp::  Bitmap_Imp	(ResID RscName)
{
	m_fAutoDetach = false;
	DeviceDependent = true;
	if ((uint)RscName != 0 || (LPCSTR)RscName != NULL) {
		hBitmap	= LoadBitmap (CV_RunTime :: ResID_handle(RscName, _AppImpFind(), RT_BITMAP),
							(char*)(ulong)(uint)RscName);
		CV_ASSERT_VALID(hBitmap);
	} else
		hBitmap = NULL;
}	// End of "Bitmap_Imp" CONSTRUCTOR "(const char*)"
															// * 0.2 End *

Bitmap_Imp::  Bitmap_Imp	(HBITMAP hBm, BOOL fAutoDetach)
{
	m_fAutoDetach = fAutoDetach;
	DeviceDependent = true;
	hBitmap	= hBm;
	CV_ASSERT_VALID(hBitmap);
}	// End of "Bitmap_Imp" CONSTRUCTOR "(HBITMAP)"
															// * 0.2 End *
// #HK970123
// LoadMappedBitmap
Bitmap_Imp::Bitmap_Imp (ResID RscName, LPCOLORMAP pMap, int iMapSize, UINT uiFlags)
{
	m_fAutoDetach = false;
	DeviceDependent = true;
	if ((uint)RscName != 0 || (LPCSTR)RscName != NULL) {
		hBitmap	= ::CreateMappedBitmap (CV_RunTime::ResID_handle(RscName, _AppImpFind(), RT_BITMAP),
						(uint)RscName, uiFlags, pMap, iMapSize);
		CV_ASSERT_VALID(hBitmap);
	} else
		hBitmap = NULL;
}

Bitmap_Imp::  ~Bitmap_Imp	()			// * 0.1 *
{
//	CV_ASSERT_VALID(hBitmap);
	if (m_fAutoDetach)
		Detach();
	
	if (hBitmap) DeleteObject (hBitmap);
}	// End of "Bitmap_Imp" FUNCTION "Delete"

HBITMAP Bitmap_Imp::Detach (void)
{
HBITMAP hBmp = hBitmap;

	hBitmap = NULL;
	return hBmp;
}

ulong	Bitmap_Imp::  SetBits	( ulong Count, pushort BitString )
{
	CV_ASSERT_VALID(hBitmap);
	return	SetBitmapBits (hBitmap, Count, BitString);
}	// End of "Bitmap_Imp" FUNCTION "SetBits"


ulong	Bitmap_Imp::  GetBits	( ulong Count, pushort BitString )
{
	CV_ASSERT_VALID(hBitmap);
	return	GetBitmapBits ( hBitmap, Count, BitString );

}	// End of "Bitmap_Imp" FUNCTION "GetBits"


Dimension	Bitmap_Imp::  GetSize	()			// * 1.2 start *
{
	BITMAP bm;

	CV_ASSERT_VALID(hBitmap);
	GetObject(hBitmap, sizeof (BITMAP), (char  *)&bm);
	return Dimension(bm.bmWidth, bm.bmHeight);
}	


void	Bitmap_Imp::  SetSize	( Dimension size )
{
	CV_ASSERT_VALID(hBitmap);
#if !defined(WIN32)
	SetBitmapDimension (hBitmap, size.Width (), size.Height ());
#else
	SetBitmapDimensionEx (hBitmap, size.Width(), size.Height(), NULL);
#endif
}	


