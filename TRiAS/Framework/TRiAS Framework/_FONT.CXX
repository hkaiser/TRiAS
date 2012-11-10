/* $Header:   G:/cv.win/pvcs/commonvu/src/_font.cxv   3.0   25 Mar 1992 15:20:30   RONAN  $
 *
 *	_ f o n t . c x x
 *
 *  Copyright (c) 1992 Trischford Limited 
 *  ( A wholly owned subsidary of Computer Associates International, Inc)
 *  All Rights Reserved
 *
 *	Version 3.1			Nov 1992
 *
 *	Mods Log:
 *	0.0	oct89	created anew as source for public interface class
 */


#include "tfrmpre.hxx"

#if defined(_TRIAS_OLDIMPLEMENTATION2)
#define CVFont	Font
#endif // _TRIAS_OLDIMPLEMENTATION2

 _DLLENTRY CVFont::  CVFont	( StdFamily family, Dimension size, const char* typeface )
{
	font_Imp	= new Font_Imp (family, size, typeface);
	CV_ASSERT_VALID(font_Imp);
}

#if _MSC_VER < 1100
 _DLLENTRY CVFont::  CVFont	( StdFont id )
#else
 _DLLENTRY CVFont::  CVFont	( StdFonts id )
#endif // _MSC_VER < 1100
{
	font_Imp	= new Font_Imp (id);
	CV_ASSERT_VALID(font_Imp);
}


 _DLLENTRY CVFont::  CVFont	(HFONT hF)
{
	font_Imp	= new Font_Imp (hF);
	CV_ASSERT_VALID(font_Imp);
}

_DLLENTRY CVFont::  CVFont	(HFONT hF, BOOL fAutoDetach)
{
	font_Imp	= new Font_Imp (hF, fAutoDetach);
	CV_ASSERT_VALID(font_Imp);
}

HFONT _DLLENTRY CVFont::Detach (void)
{
	return font_Imp -> Detach();
}

void _DLLENTRY CVFont :: Init (void)
{
	CV_ASSERT_VALID(font_Imp);
	font_Imp -> Init (NULL);
}


BOOL	 _DLLENTRY CVFont:: 	isLight ()
{	
	CV_ASSERT_VALID(font_Imp);
	return	font_Imp->isLight(); 
}

BOOL	 _DLLENTRY CVFont:: 	isNormal ()
{	
	CV_ASSERT_VALID(font_Imp);
	return	font_Imp->isNormal(); 
}

BOOL	 _DLLENTRY CVFont:: 	isBold ()
{	
	CV_ASSERT_VALID(font_Imp);
	return	font_Imp->isBold(); 
}		
		
BOOL	 _DLLENTRY CVFont:: 	isItalic ()
{	
	CV_ASSERT_VALID(font_Imp);
	return	font_Imp->isItalic(); 
}

BOOL	 _DLLENTRY CVFont:: 	isUnderline ()
{	
	CV_ASSERT_VALID(font_Imp);
	return	font_Imp->isUnderline(); 
}

BOOL	 _DLLENTRY CVFont:: 	isStrikethru ()
{	
	CV_ASSERT_VALID(font_Imp);
	return	font_Imp->isStrikethru(); 
}		


BOOL	 _DLLENTRY CVFont:: 	isPitchFixed ()
{	
	CV_ASSERT_VALID(font_Imp);
	return	font_Imp->isPitchFixed(); 
}

BOOL	 _DLLENTRY CVFont:: 	isPitchVariable ()
{	
	CV_ASSERT_VALID(font_Imp);
	return	font_Imp->isPitchVariable(); }	

void	 _DLLENTRY CVFont:: 	SetLight ()
{  	
	CV_ASSERT_VALID(font_Imp);
	font_Imp->SetLight(); }

void	 _DLLENTRY CVFont:: 	SetNormal ()
{ 	
	CV_ASSERT_VALID(font_Imp);
	font_Imp->SetNormal(); }

void	 _DLLENTRY CVFont:: 	SetBold ()
{	
	CV_ASSERT_VALID(font_Imp);
	font_Imp->SetBold(); }	 

void	 _DLLENTRY CVFont:: 	SetItalic ()
{	
	CV_ASSERT_VALID(font_Imp);
	font_Imp->SetItalic(); }

void	 _DLLENTRY CVFont:: 	SetUnderline ()
{	
	CV_ASSERT_VALID(font_Imp);
	font_Imp->SetUnderline(); }

void	 _DLLENTRY CVFont:: 	SetStrikethru ()
{	
	CV_ASSERT_VALID(font_Imp);
	font_Imp->SetStrikethru(); }	 

void	 _DLLENTRY CVFont:: 	SetFixedPitch ()
{	
	CV_ASSERT_VALID(font_Imp);
	font_Imp->SetFixedPitch(); }

void	 _DLLENTRY CVFont:: 	SetVariablePitch ()
{	
	CV_ASSERT_VALID(font_Imp);
	font_Imp->SetVariablePitch(); }

// #HK920824 ------------------------------------------------------------------
short _DLLENTRY CVFont :: SetOrientation (short newOr) 
{	
	CV_ASSERT_VALID(font_Imp);
	return short(font_Imp -> SetOrientation (newOr));	
}

short _DLLENTRY CVFont :: SetEscapement (short newOr) 
{
	CV_ASSERT_VALID(font_Imp);
	return short(font_Imp -> SetEscapement (newOr));	
}


 _DLLENTRY CVFont:: ~CVFont	()
{
	CV_ASSERT_VALID(font_Imp);
	delete	font_Imp;
}
							   
HFONT  _DLLENTRY CVFont::  Handle ( Service s_ID)
{
	return font_Imp -> Handle(s_ID);
}


BOOL _DLLENTRY CVFont::GetLogFont (LOGFONT **ppLogFont)
{
	CV_ASSERT_VALID(font_Imp);
	return font_Imp -> GetLogFont (ppLogFont);
}

