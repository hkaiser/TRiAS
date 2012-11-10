/* $Header:   G:/cv.win/pvcs/commonvu/src/_drawobj.cxv   3.0.1.0   14 Jul 1992 11:55:22   RONAN  $
 *
 *	_ d r a w o b j . c x x
 *
 *  Copyright (c) 1992 Trischford Limited 
 *  ( A wholly owned subsidary of Computer Associates International, Inc)
 *  All Rights Reserved
 *
 *	Version 3.1			Nov 1992
 *
 *	Mods Log:
 *	1.0	sm		??oct89	Sean Magner - first cut.
 *	1.1 rs		??Nov89	General tidying up. Addition  of RopContext blocks to
 *						save old Rop codes.
 *						Use of interface classes such as LogPen for interfacing
 *						with internal window structures.
 *	1.2	rs		04feb90	Contructors for drawing objects moved out of dynalink
 *						to allow correct initialisation of virtual tables.
 *	1.3 rs		24feb90 Mods to TextObject::BoundingBox to return correct
 *						rectangle.
 *	1.4 rs		26jun90 Added extra destructors to ensure correct linkage
 *						for virtual destructors in application
 *
 */
//	Usage:	#include <nocvdefs.hxx>
//
//	Optimization #defines for CA-CommonView 
//
//
//	Make your own copy of this file and comment out the lines of the
//	objects that you want to use. This will speed up your compiles and
//	make it easier to compile in DOS.
//
//	If you comment out an indented line, you should also comment out 
//	the unindented line above it. The indentations show parent-child
//	derivation hierarchies.
//
//	-------------------------------------------------------------------------

#include "tfrmpre.hxx"

#include	<DrawObj.hxx>

#define abs(x)   ((x) < 0 ? ((x)*-1) : x)

#if defined(WIN32)
extern "C" BOOL DrawRectangle (HDC hDC, int x1, int y1, int x2, int y2);
#endif

// Defines for rastor operations

#define R2_NOT		    6
#define R2_XORPEN	    7	
#define R2_COPYPEN	   13

// The RopContext class is used to save the current rop type and 
// set a new rop type for the duration of its scope.

class RopContext {
	int 	LastRop;
	HDC 	hDC;

public:
	RopContext ( HDC ,  RopType);
	void Restore()					{ SetROP2(hDC,LastRop); }

	~RopContext()				{ SetROP2(hDC,LastRop); }
};

RopContext :: RopContext(HDC h,RopType rop)
{	
	LastRop = GetROP2(hDC = h);

	switch (rop)
	{
	    case ROP_Invert:
			SetROP2( hDC, R2_NOT );
			break;
	    
		case ROP_XOR:
			SetROP2( hDC, R2_XORPEN );
			break;

	    default:
			SetROP2( hDC, R2_COPYPEN );
			break;
	}
}

HDC  _DLLENTRY DrawObject ::  Handle( Service s)
{
	if ((s == API_DRAWOBJECT_HDC) && canvas) {
		return CV_RunTime::Window_GetDrawDC ( 
 				CV_RunTime :: pWindow_to_pImp (canvas)
		       );
	} else if ((s == API_TARGET_HDC) && canvas) {
		return CV_RunTime::Window_GetDrawTargetDC ( 
 				CV_RunTime :: pWindow_to_pImp (canvas)
		       );
	} else
		return 0;
}	

Point _DLLENTRY DrawObject :: GetPosition()
{
	return pt;
}


 _DLLENTRY LineObject ::  LineObject (Point s, Point e, pPen pen) : DrawObject(s )
{
	pt = s;
	end = e;
	mypen = pen;
}

Point _DLLENTRY LineObject::   ChangePosition(Point p)
{
	CoOrd diff_width, diff_height; 
	Point retval = pt;
	diff_width = end.X() - pt.X();
	diff_height = end.Y() - pt.Y();
	pt = p;
	end = Point(pt.X() + diff_width, pt.Y() + diff_height);
	return retval;
}

Dimension _DLLENTRY LineObject::   ChangeSize(Dimension d)
{
	Dimension  dim (end.X() - pt.X(), end.Y() - end.X());
	end = Point(pt.X() + d.Width(), pt.Y() + d.Height());
	return dim;
}



void  _DLLENTRY LineObject ::  Draw()
{
	HDC hDC = Handle(0);
	RopContext ThisRop( hDC, rop );
	pPen oldpen = 0;
	if (rop == ROP_Background)
	{
		LogicalPen lp(mypen ? mypen : (canvas -> GetPen()));
		LogBackBrush lbb(CV_RunTime :: pWindow_to_pImp(canvas));
		Color c;
		*((long*)(&c)) = lbb.GetColor();
		Pen BackPen( ( (StdLineStyle)lp.GetType() ), lp.GetWidth(), c );
		oldpen = canvas->ChangePen(&BackPen);
		canvas -> MoveTo ( pt );
		canvas -> LineTo ( end );
		canvas->ChangePen(oldpen);
	}
	else
	{
		if (mypen) oldpen = canvas->ChangePen(mypen);
		canvas -> MoveTo ( pt );
		canvas -> LineTo ( end );
		if (mypen) canvas->ChangePen(oldpen);
	}
}	// End of "LineObject" FUNCTION "Draw"

Rectangle  _DLLENTRY LineObject ::  BoundingBox ()
{
	return Rectangle (Point ( min( pt.X(), end.X() ), max (pt.Y(), end.Y() ) ),
			  Dimension ( abs (pt.X() - end.X()), abs (pt.Y()- end.Y() ) ) );
}

void  _DLLENTRY RectangleObject ::  Draw()
{
	HDC hDC =  Handle(0);
	LogicalBrush mylb (mybrush ? mybrush : canvas -> GetBrush());
	LogicalPen mylp(mypen ? mypen : canvas -> GetPen());
	LogBackBrush lbb(CV_RunTime :: pWindow_to_pImp(canvas));
	Color c;
	*((long*)(&c)) = lbb.GetColor();
	Pen BackPen(SolidLine, mylp.GetWidth(), c);

// ZORTECH
// cast from short to enum

	Brush BackBrush(c, ( (StdHatchStyle)mylb.HatchType() ) );
	pPen pen = 0;
	pBrush brush = 0;


	if (rop == ROP_Background)
		{
		pen = &BackPen;
		brush = &BackBrush;
		}
	else
		{
		pen = (mypen ? mypen : canvas -> GetPen());
		brush = (mybrush ? mybrush : canvas -> GetBrush());
		}
	RopContext ThisRop( hDC, rop );

	HPEN oldpen;
	
	if	( pen )
		oldpen = (HPEN)SelectObject ( hDC, CV_RunTime::Pen_hPen ( pen ) );
	else
		oldpen = (HPEN)SelectObject ( hDC, GetStockObject ( 7 ));
		// Stock Object 7 is default pen
	HBRUSH oldbrush;
	if ( brush )
		oldbrush = (HBRUSH)SelectObject( hDC, CV_RunTime::Brush_hBrush( brush ) );
	else
		oldbrush = (HBRUSH)SelectObject(hDC, GetStockObject( BLACK_BRUSH ));

#if defined(WIN32)
	DrawRectangle (hDC, pt.X(), pt.Y() + dim.Height() -1,
				pt.X() + dim.Width(), pt.Y() -1);
#else
	rectangle (hDC, pt.X(), pt.Y() + dim.Height() -1,
			pt.X() + dim.Width(), pt.Y() -1);
#endif

	SelectObject ( hDC, oldpen );
	SelectObject ( hDC, oldbrush );
}	// End of "RectangleObject" FUNCTION "Draw"

void  _DLLENTRY EllipseObject ::  Draw()
{
	HDC hDC = Handle(0);
	LogicalBrush mylb ( mybrush ? mybrush : canvas -> GetBrush());
	LogicalPen mylp( mypen ? mypen : canvas -> GetPen());
	LogBackBrush lbb(CV_RunTime :: pWindow_to_pImp(canvas));
	Color c;
	*((long*)(&c)) = lbb.GetColor();
	Pen BackPen(SolidLine, mylp.GetWidth(), c);

	Brush BackBrush(c, ( (StdHatchStyle)mylb.HatchType() ) );
	pPen pen;
	pBrush brush;

	if (rop == ROP_Background)
	    {
	    pen = &BackPen;
	    brush = &BackBrush;
	    }
	else
	    {
	    pen = (mypen ? mypen : canvas -> GetPen());
	    brush = (mybrush ? mybrush : canvas -> GetBrush());
	    }
	RopContext ThisRop( hDC, rop );

	HPEN oldpen;
	if	( pen )
		oldpen = (HPEN)SelectObject ( hDC, CV_RunTime::Pen_hPen ( pen ) );
	else
		oldpen = (HPEN)SelectObject ( hDC, GetStockObject ( 7 ));	 
		// Stock Object 7 is default pen
	HBRUSH oldbrush;
	if ( brush )
		oldbrush = (HBRUSH)SelectObject( hDC, CV_RunTime::Brush_hBrush( brush ) );
	else
    	oldbrush = (HBRUSH)SelectObject(hDC, GetStockObject( BLACK_BRUSH ));

	Ellipse (hDC, pt.X(), pt.Y() + dim.Height() -1 , 
			pt.X() + dim.Width(), pt.Y()-1 );

	SelectObject ( hDC, oldpen );
	SelectObject ( hDC, oldbrush );

}	// End of "EllipseObject" FUNCTION "Draw"

pPen  _DLLENTRY LineObject::  ChangePen( pPen newpen )
{
	pPen oldpen = mypen;
	mypen = newpen;
	return oldpen;
}

Dimension _DLLENTRY ShapeObject::   ChangeSize(Dimension d)
{
	Dimension retval = dim;
	dim  = d;
	return retval;
}


pPen  _DLLENTRY ShapeObject::  ChangePen( pPen newpen )
{
	pPen oldpen = mypen;
	mypen = newpen;
	return oldpen;
}

pBrush  _DLLENTRY ShapeObject::  ChangeBrush( pBrush newbrush )
{
	pBrush oldbrush = mybrush;
	mybrush = newbrush;
	return oldbrush;
}




Rectangle  _DLLENTRY ShapeObject ::  BoundingBox()
{
CoOrd upperleft_x;
CoOrd upperleft_y;

	if (dim.Width() < 0)
	    upperleft_x = pt.X() + dim.Width() + 1;
	else
	    upperleft_x = pt.X();
	if (dim.Height() < 0)
	    upperleft_y = pt.Y();
	else
	    upperleft_y = pt.Y() + dim.Height();
	    
	return Rectangle ( Point(upperleft_x, upperleft_y), 
				Dimension( abs (dim.Width()), abs (dim.Height()) ) );
}


_DLLENTRY TextObject ::TextObject ( const TextObject & copyFrom)
: DrawObject((const DrawObject&) copyFrom)
{
	 text = CV_strdup(copyFrom.text);
	 mycol = copyFrom.mycol;
	 myfont = copyFrom.myfont;
}

TextObject& _DLLENTRY TextObject ::operator=( const TextObject & copyFrom)
{
	 (*this).DrawObject::operator=(copyFrom);
	 if (text) delete text;
	 text = CV_strdup(copyFrom.text);
	 mycol = copyFrom.mycol;
	 myfont = copyFrom.myfont;
	 return *this;
}

void  _DLLENTRY TextObject ::  Draw()
{
	HDC hDC = Handle(0);
	Color color;
	if (rop == ROP_Background)
	{
		LogBackBrush lbb(CV_RunTime :: pWindow_to_pImp(canvas));
		*((long*)(&color)) = lbb.GetColor();
	}
	else
		color =  mycol;

// if Rop code == ROP_Overwrite OR ROP_Background
	{
	RopContext ThisRop(hDC,rop);
	pFont oldfont;

		if (myfont) oldfont = canvas->ChangeFont(myfont);
		Pen textpen(SolidLine, 1, color);
		pPen oldpen = canvas -> ChangePen(&textpen);
		canvas -> TextPrint( text, pt );
		canvas -> ChangePen(oldpen);
		if (myfont) canvas->ChangeFont( oldfont );
	}

// Else use memory device context to render text.
}	// End of "TextObject" FUNCTION "Draw"

Rectangle  _DLLENTRY TextObject ::  BoundingBox()
{
	Dimension size;
	if (canvas)
	{
	pFont oldfont;

		if (myfont) oldfont = canvas->ChangeFont(myfont);
		size = canvas -> TextSize( text );
		if (myfont) canvas->ChangeFont( oldfont );
	}

	return Rectangle ( Point ( pt.X() , pt.Y() + size.Height() ),size);
}

 _DLLENTRY DrawObject ::  DrawObject(Point p)
{
	pt = p;
	rop = ROP_Overwrite;
	canvas = 0;
}

 _DLLENTRY DrawObject ::  DrawObject()
{
	pt = Point(0,0);
	rop = ROP_Overwrite;
	canvas = 0;
}

Point _DLLENTRY DrawObject::   ChangePosition(Point p)
{
	Point retval = pt;
	pt = p;
	return retval;
}

Dimension _DLLENTRY DrawObject::   ChangeSize(Dimension)
{
	return Dimension(0, 0);
}


void CV_RunTime:: 	Window_Draw ( pDrawObject pDO, pWind_Imp p )
{
Window *pWind = pDO -> canvas;

	pDO -> canvas = (Window *)( p -> pRequestor);

DS_fixup AppFixUp;

	pDO -> Draw();
	pDO -> canvas = pWind;
}

void CV_RunTime:: 	Window_DrawEx (pDrawObject pDO, pWind_Imp p, DWORD dwData)
{
Window *pWind = pDO -> canvas;

	pDO -> canvas = (Window *)(p -> pRequestor);

DS_fixup App_fix;

	pDO -> DrawEx (dwData);
	pDO -> canvas = pWind;
}


// Vorsicht: es muß grundsätzlich mindestens ein Draw gegeben sein, da es sonst 
// rekursive Probleme gibt
void  _DLLENTRY DrawObject ::  Draw (void)
{
	this -> DrawEx (0L);
}


void  _DLLENTRY DrawObject ::  DrawEx (DWORD)
{
	this -> Draw();
}


RopType  _DLLENTRY DrawObject ::  ChangeRop ( RopType r )
{
	RopType oldrop = rop;
	rop = r;
	return oldrop;
}

Rectangle  _DLLENTRY DrawObject ::  BoundingBox ()
{
	return Rectangle ( Point(0,0), Dimension (0,0) );
}


BOOL  _DLLENTRY DrawObject ::  HitTest (Point p)
{
	Rectangle Bound = BoundingBox();
	return p.X() >= Bound.Left() && p.X() < Bound.Right() 
			&& p.Y() < Bound.Top() && p.Y() >= Bound.Bottom();
}	// End of "DrawObject" FUNCTION "HitTest"

void  _DLLENTRY DrawObject ::  Process ( Point )
{

}	// End of "DrawObject" FUNCTION "Process"

_DLLENTRY BitmapObject ::  BitmapObject ( Point p, Dimension d, pBitmap pbmp)
	: ShapeObject(p, d, NULL, NULL)
{
	bitmap = pbmp;
	if ((d.Width() ==0) && (d.Height() == 0))
		dim = bitmap -> GetSize();
}

Dimension _DLLENTRY BitmapObject::   ChangeSize(Dimension d)
{
	if ( d.Width() || d.Height() )
		return ShapeObject :: ChangeSize(d);
	else
		return ShapeObject :: ChangeSize(bitmap -> GetSize());
}

Rectangle  _DLLENTRY BitmapObject ::  BoundingBox ()
{
	return ShapeObject :: BoundingBox ();
}

void  _DLLENTRY BitmapObject ::  Draw ()		   
{
	HBITMAP hBitmap = CV_RunTime::Bitmap_hBitmap(bitmap);

	CV_ASSERT_VALID(hBitmap);

	if (hBitmap)
		{
		if (rop == ROP_Background)
		{
			CV_NOTE("BitmapObject :: Draw() - Drawing background only");

			pBrush oldbrush = canvas->ChangeBrush ( canvas -> GetBackground());
			canvas->PaintRectangle ( Rectangle ( pt.Y()+dim.Height(),pt.X(),
											 	pt.Y(),pt.X()+dim.Width() ) );
			canvas->ChangeBrush ( oldbrush );
			return;
		}

		//
		// Convert rop code to the correct raster operation code
		//
		unsigned long rastor_op;

		switch (rop)
		{
			case ROP_Invert :
				rastor_op = (ulong) 0x00990066;
				break;
			case ROP_XOR :
				rastor_op = SRCINVERT;
				break;
			default :
				rastor_op = SRCCOPY;
		}

		Dimension bmsize = bitmap -> GetSize();


		HDC hMemDC = CreateCompatibleDC ( Handle() );
		CV_ASSERT_VALID(hMemDC);
		if (hMemDC)
			{
			HBITMAP hOldBitmap = (HBITMAP)SelectObject (hMemDC, hBitmap );
			Point pt_origin (0,0);

			
			BOOL success = 
			StretchBlt(Handle(), pt.X(), 
						pt.Y() + dim.Height() - 1, 
						dim.Width(),(-dim.Height()), 
						hMemDC, 0, 0, 
						bmsize.Width(), bmsize.Height(),rastor_op);


			CV_ASSERT(success);

			SelectObject(hMemDC, hOldBitmap);
			DeleteDC (hMemDC );
			}
		CV_RunTime :: Window_ResetDC( CV_RunTime :: pWindow_to_pImp(canvas));
		}
}



_DLLENTRY FmtTextObject::	FmtTextObject	( Point where, const char* txt, Color c,
					pFont font)	: TextObject(where, txt, c, font)
{
	tabsize = 8;
}

 _DLLENTRY FmtTextObject::	FmtTextObject	( Point where, const char* txt, pFont font )
	: TextObject(where, txt, font)
{
	tabsize = 8;
}

void  _DLLENTRY FmtTextObject ::  Draw()
{
	TEXTMETRIC tm;
	HDC hDC = Handle(0);

    if ( hDC )
    {
	    Pen pen(SolidLine, 1, mycol);
	    pPen oldpen = canvas->ChangePen(&pen);
	    pFont oldfont = canvas->ChangeFont(myfont);

        GetTextMetrics(hDC, &tm);

	int tabstops = tabsize * tm.tmAveCharWidth ;
    int lineheight = tm.tmAscent + tm.tmDescent + tm.tmExternalLeading ;
	int  Ypos = pt.Y();

	int len_segment = 0;
	char * p = text;
	char * text_segment = p;
	char ch;		   

		do
		{
		switch (ch = *p) {
		case '\n':
		case '\r':
			p++;
		case '\0':
			if (len_segment)
				TabbedTextOut( 	hDC, pt.X(), Ypos, 
						text_segment, len_segment, 
						1, &tabstops, pt.X());
			if (ch == '\n')
				Ypos -= lineheight;
			text_segment = p;
			len_segment = 0;
			break;

		default:
			{
			p++;
			len_segment++;
			}
		};
	}
	while (ch);

	canvas->ChangePen(oldpen);
	canvas->ChangeFont(oldfont);
	}
}	// End of "FmtTextObject" FUNCTION "Draw"		

void  _DLLENTRY FmtTextObject ::  SetTabSize( uint t )
{
	tabsize = t;
}	// End of "FmtTextObject" FUNCTION "SetTabSize"		


_DLLENTRY TextObject::	TextObject	( Point where, const char* txt, Color c,
					pFont font)	: DrawObject(where)
{
	mycol = c;
	myfont = font;
	text	= CV_strdup ( txt );
}	// End of "TextObject" CONSTRUCTOR

 _DLLENTRY TextObject::	TextObject	( Point where, const char* txt, pFont font )
	: DrawObject(where)
{
	*((long*)(&mycol)) = GetSysColor(COLOR_WINDOWTEXT);
	myfont = font;
	text	= CV_strdup ( txt );
}	// End of "TextObject" CONSTRUCTOR




 _DLLENTRY ShapeObject::  ShapeObject (Point p, Dimension d, pPen pen, pBrush brush) 
	: DrawObject(p)
{
	mypen = pen; 
	mybrush = brush; 
	dim = d;
}

 _DLLENTRY RectangleObject ::  RectangleObject(Point p, Dimension d, pPen pen, pBrush brush)
	: ShapeObject(p, d, pen,brush)
{
}

 _DLLENTRY EllipseObject ::  EllipseObject(Point p, Dimension d, pPen pen, pBrush brush)
	: ShapeObject(p, d,  pen, brush )
{
}



 _DLLENTRY LineObject :: ~LineObject() {}

 _DLLENTRY ShapeObject :: ~ShapeObject() {}

 _DLLENTRY RectangleObject :: ~RectangleObject() {} 

 _DLLENTRY EllipseObject :: ~EllipseObject() {}

 _DLLENTRY BitmapObject ::	~BitmapObject() {} 

 _DLLENTRY FmtTextObject:: 	~FmtTextObject(){}

 _DLLENTRY DrawObject:: 	~DrawObject(){}

 _DLLENTRY TextObject:: 	~TextObject()
 {
	delete text;
 }

 // ******************************************************************
 // Copy constructors
 // ******************************************************************

 _DLLENTRY DrawObject ::DrawObject ( const DrawObject & copyFrom)
 {
	 pt = copyFrom.pt;
	 canvas = 0;
	 rop = copyFrom.rop;
 }

 DrawObject& _DLLENTRY DrawObject ::operator=( const DrawObject & copyFrom)
 {
	 pt = copyFrom.pt;
	 canvas = 0;
	 rop = copyFrom.rop;
	 return *this;
 }

 _DLLENTRY ShapeObject ::ShapeObject ( const ShapeObject & copyFrom)
 : DrawObject((const DrawObject&) copyFrom)
 {
	 mypen = copyFrom.mypen;
	 mybrush = copyFrom.mybrush;
	 dim = copyFrom.dim;
 }

 ShapeObject& _DLLENTRY ShapeObject ::operator=( const ShapeObject & copyFrom)
 {
	 (*this).DrawObject::operator=(copyFrom);
	 mypen = copyFrom.mypen;
	 mybrush = copyFrom.mybrush;
	 dim = copyFrom.dim;
	 return *this;
 }




 _DLLENTRY FmtTextObject ::FmtTextObject ( const FmtTextObject & copyFrom)
 : TextObject((const FmtTextObject&) copyFrom)
 {
	 tabsize = copyFrom.tabsize;
 }

 FmtTextObject& _DLLENTRY FmtTextObject ::operator=( const FmtTextObject & copyFrom)
{
	(*this).TextObject::operator=(copyFrom);
	tabsize = copyFrom.tabsize;
	return *this;
}

Dimension _DLLENTRY DrawObject :: GetSize ()
{
	return Dimension(0,0);
}

Dimension _DLLENTRY LineObject :: GetSize ()
{
	return Dimension ( end.X() - pt.X(), end.Y() - pt.Y() );
}

Dimension _DLLENTRY ShapeObject :: GetSize ()
{
	return dim;
}


#if defined(WIN32)

CImageListObject :: CImageListObject (Point ptWhere, CImageList *pList, 
			int iIndex, UINT uiStyle)
		  : ShapeObject (ptWhere, Dimension(0,0), NULL, NULL), 
		    m_pIList(pList), m_iIndex(iIndex), m_uiStyle(uiStyle)
{
}

CImageListObject :: ~CImageListObject (void) {}

void CImageListObject :: SetIndex (int iIndex)
{
	m_iIndex = min(iIndex, m_pIList->GetImageCount());
}

void CImageListObject :: SetStyle (UINT uiStyle)
{
	m_uiStyle = uiStyle;
}

void CImageListObject :: Draw (void)
{
	ImageList_Draw (m_pIList->Handle(), m_iIndex, Handle(), 
			pt.X(), pt.Y(), m_uiStyle);
}

///////////////////////////////////////////////////////////////////////////////
// #HK970110: Polygon/Polyline
CPolygonObject::CPolygonObject(Point ptRef, const Point *pPts, int nCount,
			pPen pP, BOOL fArea, pBrush pBr)
	: DrawObject (ptRef), mypen(pP), mybrush(pBr),
	  m_fArea(fArea), m_pPts(pPts), m_nCount(nCount)
{
}

void CPolygonObject::Draw (void)
{
HDC hDC = Handle(0);
LogicalBrush mylb (mybrush ? mybrush : canvas -> GetBrush());
LogicalPen mylp (mypen ? mypen : canvas -> GetPen());
LogBackBrush lbb (CV_RunTime :: pWindow_to_pImp(canvas));
Color c;

	*((long *)(&c)) = lbb.GetColor();

Pen BackPen(SolidLine, mylp.GetWidth(), c);
Brush BackBrush(c, (StdHatchStyle)mylb.HatchType());
pPen pen;
pBrush brush;

	if (rop == ROP_Background) {
	    pen = &BackPen;
	    brush = &BackBrush;
	} else {
	    pen = (mypen ? mypen : canvas -> GetPen());
	    brush = (mybrush ? mybrush : canvas -> GetBrush());
	}

RopContext ThisRop (hDC, rop);
HPEN oldpen;

	if (pen)
		oldpen = (HPEN)SelectObject (hDC, CV_RunTime::Pen_hPen (pen));
	else
		oldpen = (HPEN)SelectObject (hDC, GetStockObject (7));
		// Stock Object 7 is default pen

HBRUSH oldbrush;

	if (m_fArea) {
		if (brush)
			oldbrush = (HBRUSH)SelectObject (hDC, CV_RunTime::Brush_hBrush(brush));
		else
    		oldbrush = (HBRUSH)SelectObject(hDC, GetStockObject(BLACK_BRUSH));
	}
	
	if (!m_fArea) 
		::Polyline (hDC, (POINT *)m_pPts, m_nCount);
	else
		::Polygon (hDC, (POINT *)m_pPts, m_nCount);

	SelectObject (hDC, oldpen);
	if (m_fArea) 
		SelectObject (hDC, oldbrush);
}

CPolyPolygonObject::CPolyPolygonObject (Point ptRef, const Point *pPts, 
		const int *piPolyCounts, int nCount, 
		pPen pP, BOOL fArea, pBrush pBr)
	: CPolygonObject (ptRef, pPts, nCount, pP, fArea, pBr),
	  m_piPolyCounts(piPolyCounts)
{
}

void CPolyPolygonObject::Draw (void)
{
HDC hDC = Handle(0);
LogicalBrush mylb (mybrush ? mybrush : canvas -> GetBrush());
LogicalPen mylp (mypen ? mypen : canvas -> GetPen());
LogBackBrush lbb (CV_RunTime :: pWindow_to_pImp(canvas));
Color c;

	*((long *)(&c)) = lbb.GetColor();

Pen BackPen(SolidLine, mylp.GetWidth(), c);
Brush BackBrush(c, (StdHatchStyle)mylb.HatchType());
pPen pen;
pBrush brush;

	if (rop == ROP_Background) {
	    pen = &BackPen;
	    brush = &BackBrush;
	} else {
	    pen = (mypen ? mypen : canvas -> GetPen());
	    brush = (mybrush ? mybrush : canvas -> GetBrush());
	}

RopContext ThisRop (hDC, rop);
HPEN oldpen;

	if (pen)
		oldpen = (HPEN)SelectObject (hDC, CV_RunTime::Pen_hPen (pen));
	else
		oldpen = (HPEN)SelectObject (hDC, GetStockObject (7));

HBRUSH oldbrush;

	if (m_fArea) {
		if (brush)
			oldbrush = (HBRUSH)SelectObject (hDC, CV_RunTime::Brush_hBrush(brush));
		else
    		oldbrush = (HBRUSH)SelectObject(hDC, GetStockObject(BLACK_BRUSH));
	}
	if (!m_fArea)
		::PolyPolyline (hDC, (POINT *)m_pPts, (const DWORD *)m_piPolyCounts, m_nCount);
	else
		::PolyPolygon (hDC, (POINT *)m_pPts, m_piPolyCounts, m_nCount);

	SelectObject (hDC, oldpen);
	if (m_fArea) 
		SelectObject (hDC, oldbrush);
}

#endif // WIN32
