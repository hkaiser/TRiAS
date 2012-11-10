/* $Header:   G:/cv.win/pvcs/commonvu/src/_font_im.cxv   3.0   25 Mar 1992 15:20:34   RONAN  $
 *
 *      _ f o n t . c x x
 *
 *  Copyright (c) 1992 Trischford Limited 
 *  ( A wholly owned subsidary of Computer Associates International, Inc)
 *  All Rights Reserved
 *
 *	Version 3.1			Nov 1992
 *
 *      Mods Log:
 *      0.1     jk              29sep88 Set FntFamily to family not FF_DONTCARE.
 *      0.0     ferg    05oct88 --------- Milestone 2. Beta 2 shipped -------
 *      0.2 jk          24oct88 Destructor for Font
 *      0.3 jk          29nov88 ------ Milestone 2A. Beta 2A shipped ------
 *      0.4 jk          02dec88 Fast Compile defines added.
 *  	1.0 rs              29mar89 -------Release 1.0 ship date ----------------
 *  	1.1 rs              07jul89 -------Release 1.0a ship date ---------------
 *      1.2     rs              21Nov89 1.1 additions to font.
 *                              13Dec89 Full implementation of fonts for 1.1
 *	2.0 rs		19Jun90 rs from nc Apr90 - Hiding
 */

#include "tfrmpre.hxx"
#include 		<_link.hxx>

struct DevInfo;

#if _MSC_VER <= 1020
void * operator new (size_t, void * addr) { return addr; }
#endif // _MSC_VER

//	MS Windows standard Font pitches :-
#define	Pitch_Mask			3

#define ANSI_CHARSET	    0
#define DEFAULT_CHARSET     1
#define SYMBOL_CHARSET	    2
#define SHIFTJIS_CHARSET    128
#define HANGEUL_CHARSET     129
#define CHINESEBIG5_CHARSET 136
#define OEM_CHARSET	    255

#define DEFAULT_QUALITY	      0
#define DRAFT_QUALITY	      1
#define PROOF_QUALITY	      2

#define OUT_DEFAULT_PRECIS	0
#define OUT_STRING_PRECIS	1
#define OUT_CHARACTER_PRECIS	2
#define OUT_STROKE_PRECIS	3
#define OUT_TT_PRECIS		4
#define OUT_DEVICE_PRECIS	5
#define OUT_RASTER_PRECIS	6
#define OUT_TT_ONLY_PRECIS	7

//#define CLIP_LH_ANGLES		0x10
//#define CLIP_TT_ALWAYS		0x20
//#define CLIP_EMBEDDED		0x80

/* EnumFonts Masks */
#define RASTER_FONTTYPE     0x0001
//#define DEVICE_FONTTYPE     0X0002
#define trueTYPE_FONTTYPE   0x0004

//	MS Windows standard Font families :-
//#define FF_DONTCARE         0x00
#define FF_FAMILYMASK		0x0070

static int StdPointSize[] = 
	{
	8, 		
	10, 	
	12, 	
	8,   	
	10, 		
	12, 		
	14, 		
	18, 		
	24, 		
	8, 		
	10, 		
	12, 		
	14, 		
	18, 		
	24, 		
	8,
	};

static int StdFamilyType[] = 
	{
	FF_MODERN, 		
	FF_MODERN, 	
	FF_MODERN, 	

	FF_ROMAN,   	
	FF_ROMAN, 		
	FF_ROMAN, 		
	FF_ROMAN, 		
	FF_ROMAN, 		
	FF_ROMAN, 		

	FF_SWISS, 		
	FF_SWISS, 		
	FF_SWISS, 		
	FF_SWISS, 		
	FF_SWISS, 		
	FF_SWISS, 		
	FF_DONTCARE
	};

LOGFONT * StdCvFonts[16];

static bool InitScreenStdFonts() ;


LogFont :: LogFont (HFONT h)
{
	GetObject (h, sizeof(LOGFONT), this);
}

LogFont :: LogFont (int width, int height, const char *typef) 
{
		lfHeight = height;
		lfWidth  = width;
		lfEscapement = lfItalic	= lfUnderline =
		lfStrikeOut = 0;
		lfOrientation = 0;
		lfWeight = NORMALWEIGHT;
		if (IsTrueTypeEnabled())
			{
			if (UseTrueTypeOnly())
				lfOutPrecision =  OUT_TT_ONLY_PRECIS;
			else
				lfOutPrecision =  OUT_TT_PRECIS;
			lfQuality =  DRAFT_QUALITY;
			}
		else
			{
			lfOutPrecision =  OUT_RASTER_PRECIS;
			lfQuality =  DRAFT_QUALITY;
			}
		lfClipPrecision =  CLIP_STROKE_PRECIS | 0x10;	// CLIP_LH_ANGLES
		if (typef && (lstrlen(typef) < 32))
			{
			lstrcpy(lfFaceName,typef);
			lfCharSet = DEFAULT_CHARSET;
			}
		else
			{
			lfCharSet = ANSI_CHARSET;
			lfFaceName[0] = '\0';
			}
	   	lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
}

LogFont :: LogFont (const LogFont & ref)
{ 
	Copy((LOGFONT*)&ref); 
}

void LogFont :: Copy (LOGFONT * ref)
{
	CopyWOAttributes(ref);
	lfWeight = ref->lfWeight;
	lfItalic = ref->lfItalic;
	lfUnderline = ref->lfUnderline;
	lfStrikeOut = ref->lfStrikeOut;
	lfPitchAndFamily = ref->lfPitchAndFamily;
}


void LogFont :: CopyWOAttributes(LOGFONT * ref)
{
	// Copy without overriding attributes
	lfHeight = ref->lfHeight;
	lfWidth = ref->lfWidth;
	lfEscapement = ref->lfEscapement;
	lfOrientation = ref->lfOrientation;
	lfCharSet = ref->lfCharSet;
	lfOutPrecision = ref->lfOutPrecision;
	lfClipPrecision = ref->lfClipPrecision;
	lfQuality = ref->lfQuality;
	lfPitchAndFamily &= Pitch_Mask;
	if (lfPitchAndFamily == DEFAULT_PITCH)
		lfPitchAndFamily |= (ref->lfPitchAndFamily & FF_FAMILYMASK);
	else
		lfPitchAndFamily = ref->lfPitchAndFamily;
	lstrcpy(lfFaceName,ref->lfFaceName);
}

#ifdef BETA

class CV_TextMetric {
	TEXTMETRIC tm;
	char face[80];
public:
	
	CV_TextMetric(HANDLE hFont, HANDLE hDC);
	void Describe();
};

CV_TextMetric :: CV_TextMetric (HANDLE hFont, HANDLE hDC)
{
	HFONT hOldFont = (HFONT)SelectObject(hDC, hFont);
	GetTextMetrics(hDC, &tm);
	GetTextFace(hDC, 79, face);
	SelectObject(hDC, hOldFont);
}

void CV_TextMetric ::Describe()
{
	char * Family = "Unknown";
	switch (tm.tmPitchAndFamily & FF_FAMILYMASK)
		{
		case FF_ROMAN:
			Family = "Roman";
			break;

		case FF_SWISS:
  			Family = "Swiss";
			break;

		case FF_MODERN:
			Family = "Modern";
			break;

		case FF_SCRIPT:
			Family = "Script";
			break;

		case FF_DECORATIVE:
			Family = "Decorative";
			break;

		default:
			Family = "Dont Care";
		};
}

void LogFont ::Describe()
{
	char * Family = "Unknown";
	switch (lfPitchAndFamily & FF_FAMILYMASK)
		{
		case FF_ROMAN:
			Family = "Roman";
			break;

		case FF_SWISS:
  			Family = "Swiss";
			break;

		case FF_MODERN:
			Family = "Modern";
			break;

		case FF_SCRIPT:
			Family = "Script";
			break;

		case FF_DECORATIVE:
			Family = "Decorative";
			break;

		default:
			Family = "Dont Care";
		};
}
#endif

/*
 *      Font_Imp::Font_Imp()
 */
Font_Imp::  Font_Imp  ( StdFamily family, Dimension size, const char* typeface )
         :  FntSize ( size )
{
	hFont = 0;
	FntTmpLft = 1;
	m_fAutoDetach = false;
	lft = (LOGFONT *)new LogFont (FntSize.Width (), FntSize.Height (), typeface);
	IsStdFont = 0;

	switch (family) {
	case Decorative:
		lft->lfPitchAndFamily	|= FF_DECORATIVE; break;
	case Modern:
		lft->lfPitchAndFamily	|=  FF_MODERN; break;
	case Roman:
		lft->lfPitchAndFamily |= FF_ROMAN; break;
	case Script:
		lft->lfPitchAndFamily	|= FF_SCRIPT; 
		lft -> lfOutPrecision =  OUT_STROKE_PRECIS;
		lft -> lfCharSet = DEFAULT_CHARSET;
		break;
	case Swiss:
		lft->lfPitchAndFamily	|= FF_SWISS; break;
	default:
		lft->lfPitchAndFamily	|= FF_DONTCARE;
	}
	FntChanged	= 1;
}       // End of "Font_Imp" CONSTRUCTOR

                                                                                                        // * 0.2 Begin *
Font_Imp::  ~Font_Imp ()
{
	if (m_fAutoDetach)
		Detach();
	if (hFont)
        DeleteObject ( hFont );
	if (lft && FntTmpLft)
		delete lft;
}       // End of "Font_Imp" DESTRUCTOR
                                                                                                        // * 0.2 End *
HFONT Font_Imp::Detach (void)
{
HFONT hF = hFont;

	hFont = NULL;
	return hF;
}

// * 1.2 * start
#if _MSC_VER < 1100
Font_Imp ::  Font_Imp ( StdFont sf)
#else
Font_Imp ::  Font_Imp ( StdFonts sf)
#endif // _MSC_VER < 1100

 :       FntSize ( Dimension(0,0) )
{
    	hFont  = 0;
	IsStdFont = 0;
	m_fAutoDetach = false;
	StdFontType = (uchar) sf;
	FntTmpLft = 1;
	FntChanged	= 1;
	lft = (LOGFONT *)new LogFont (0,0,(char *)0); 
}


Font_Imp ::  Font_Imp (HFONT hF, BOOL fAutoDetach)
	  :  FntSize ( Dimension(0,0) )
{
    	hFont  = hF;
	m_fAutoDetach = fAutoDetach;
	IsStdFont = 0;
	FntTmpLft = 1;
	FntChanged = 0;
	lft = (LOGFONT *)new LogFont (hF); 
	FntSize.Height() = lft -> lfHeight;
	FntSize.Width() = lft -> lfWidth;
}


void	Font_Imp ::  SetLight ()			
{	
	if (lft->lfWeight != LIGHTWEIGHT)
		{
		lft->lfWeight = LIGHTWEIGHT;	
		FntChanged = 1;
		}
}

void	Font_Imp ::  SetNormal ()		
{	
	if (lft->lfWeight	!= NORMALWEIGHT)
		{
		lft->lfWeight	= NORMALWEIGHT;	
		FntChanged = 1;
		}
}

void	Font_Imp ::  SetBold ()			
{	
	if (lft->lfWeight	!= HEAVYWEIGHT)
		{
		lft->lfWeight	= HEAVYWEIGHT;	
		FntChanged = 1;
		}
}


void	Font_Imp ::  SetItalic ()		
{	
	if (lft->lfItalic		!= 1)
		{
		lft->lfItalic		= 1;	
		FntChanged = 1;
		}
}

void	Font_Imp ::  SetUnderline ()		
{	
	if (lft->lfUnderline	!= 1)
		{
		lft->lfUnderline	= 1;	
		FntChanged = 1;
		}
}

void	Font_Imp ::  SetStrikethru ()	
{	
	if (lft->lfStrikeOut	!= 1)
		{
		lft->lfStrikeOut	= 1;	
		FntChanged = 1;
		}
}


void	Font_Imp ::  SetFixedPitch ()	
{	
	if ((lft->lfPitchAndFamily & Pitch_Mask) != FIXED_PITCH)
		{
		lft->lfPitchAndFamily  = ((lft->lfPitchAndFamily & (~Pitch_Mask)) | FIXED_PITCH);
		FntChanged = 1;
		}
}

void	Font_Imp ::  SetVariablePitch ()	
{	
	if ((lft->lfPitchAndFamily & Pitch_Mask) != VARIABLE_PITCH)
		{
		lft->lfPitchAndFamily  = ((lft->lfPitchAndFamily & (~Pitch_Mask)) | VARIABLE_PITCH);
		FntChanged = 1;
		}
}

// #HK920824 ------------------------------------------------------------------
#if !defined(WIN32)
short Font_Imp :: SetOrientation (short newOr) 
{
short oldOr = lft -> lfOrientation;
#else
LONG Font_Imp :: SetOrientation (short newOr) 
{
LONG oldOr = lft -> lfOrientation;
#endif

	if (lft -> lfOrientation != newOr) {
		lft -> lfOrientation = newOr;
		FntChanged = 1;
	}

return oldOr;
}


#if !defined(WIN32)
short Font_Imp :: SetEscapement (short newOr) 
{
short oldOr = lft -> lfEscapement;
#else
LONG Font_Imp :: SetEscapement (short newOr) 
{
LONG oldOr = lft -> lfEscapement;
#endif

	if (lft -> lfEscapement != newOr) {
		lft -> lfEscapement = newOr;
		FntChanged = 1;
	}

return oldOr;
}

// #HK970903
BOOL _DLLENTRY Font_Imp::GetLogFont (LOGFONT **ppLogFont)
{
	if (NULL == ppLogFont)
		return false;
	
	*ppLogFont = lft;
	return true;
}
// #HK970903

// * 1.2 * end

void	Font_Imp::  Init( LOGFONT **arr , HDC hdc)
{
	// Arr == 0 indicates initialisation for Screen
	bool IsScreen = (arr ? false  : true);

	if (hFont && FntChanged)
		{
		DeleteObject(hFont);
		hFont = 0;
		FntChanged = 0;
		}
	if (IsStdFont && !hFont)
		{
		if ((arr == 0) && InitScreenStdFonts())
			arr = StdCvFonts;
		if (arr)
			((LogFont *)lft) -> CopyWOAttributes(arr[StdFontType]);
		if (!IsScreen)	
			lft -> lfOutPrecision = OUT_DEVICE_PRECIS;

#ifdef BETA
// 		lft -> Describe();
#endif
    	hFont = CreateFontIndirect ( lft );
		FntChanged = 0;
		}
	else
		if (!hFont)
	{
		lft->lfHeight = FntSize.Height ();
		lft->lfWidth = FntSize.Width ();

#ifdef BETA
//		lft -> Describe();
#endif
    	hFont = CreateFontIndirect ( lft );
		FntChanged = 0;
		}
#ifdef BETA 
/*
	if (hFont && hdc)
		{
		CV_TextMetric FontMatched(hFont, hdc);
		FontMatched.Describe();
		}
*/
#endif
}	//	End of "Font_Imp" FUNCTION "Init"


struct DevInfo {
	int LogPixelsX;
	int LogPixelsY;
	int ExactScaling : 1;
	int IntScaling	: 1;
 	int Technology;
	int PointDiffs[16];
	LOGFONT **stdfontarr;

	DevInfo (HDC, LOGFONT *arr[]); 
};


DevInfo :: 	DevInfo (HDC hdc, LOGFONT *arr[])
{
	LogPixelsX = GetDeviceCaps(hdc, LOGPIXELSX);
	LogPixelsY = GetDeviceCaps(hdc, LOGPIXELSY);
	ExactScaling = GetDeviceCaps(hdc, TEXTCAPS) & 0x0100;
	IntScaling = GetDeviceCaps(hdc, TEXTCAPS) & 0x0080;
	Technology =  GetDeviceCaps(hdc, TECHNOLOGY);
	for (int i = 0; i < 16; i++)
		PointDiffs[i] = 100;
	stdfontarr = arr;
}


char *InitPrStdFonts( HDC hdc) 
{
	LOGFONT **arrfonts;
	char* FontMem;
	FontMem = new char [(sizeof(LOGFONT*) * 16) + (17 *sizeof(LOGFONT))];
	arrfonts = (LOGFONT**)FontMem;

	// Quick hack of fonts - to be rewritten

	DevInfo di(hdc, arrfonts);
	for (int i = 0; i < 16; i++)
		{
		arrfonts[i] = new (&(FontMem[(i * sizeof(LOGFONT)) + (16 * sizeof(LOGFONT*))])) LOGFONT; 
		arrfonts[i] -> lfQuality =  PROOF_QUALITY;
		arrfonts[i] -> lfOutPrecision =  OUT_DEVICE_PRECIS;
        arrfonts[i]-> lfHeight= -(((di.LogPixelsY * StdPointSize[i])+36)/72);
		arrfonts[i]->lfPitchAndFamily =  StdFamilyType[i] | DEFAULT_PITCH;
		}
	GetObject(GetStockObject ( DEVICE_DEFAULT_FONT ), sizeof(LOGFONT), (char*)(arrfonts[(int)SystemFont8]));
  	lstrcpy(arrfonts[(int)SystemFont8] -> lfFaceName, "Courier");
	return FontMem;
}

static bool InitScreenStdFonts( ) 
{
static bool	Setup = false;
static char FontMem[16 * sizeof(LOGFONT)];

	if (!Setup)
		{
		Setup = true;

		HDC hdc = CreateIC ("DISPLAY", NULL, NULL, NULL) ;
		DevInfo di(hdc, StdCvFonts);

		for (int i = 0; i < 16; i++)
			{
			StdCvFonts[i] = new (&(FontMem[i * sizeof(LOGFONT)])) LOGFONT; 
            StdCvFonts[i]-> lfHeight= -(((di.LogPixelsY * StdPointSize[i])+36)/72);
            StdCvFonts[i]-> lfWidth= 0;
			StdCvFonts[i]->lfPitchAndFamily =  StdFamilyType[i];
			}
		DeleteDC(hdc);
		}
	return Setup;
}



