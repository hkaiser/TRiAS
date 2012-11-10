//	Usage #include <drawobj.hxx>
//
//	Public interface to Computer Associates drawing object hierarchy.
//	Used in conjunction with CA-CommonView 3.1
//
//  Copyright (c) 1992 Trischford Limited 
//  ( A wholly owned subsidary of Computer Associates International, Inc)
//  All Rights Reserved
//
//	Version 3.1			Nov 1992
//
//	Tab stops in this file are at	4 * n + 1
//
//-------------------------------------------------------------------------

#ifndef	_DRAWOBJ_HXX
#define	_DRAWOBJ_HXX

#include <CV_Types.hxx>

class _TF_ENTRY32 DrawObject
{
friend class CV_RunTime;
protected:
		Point		pt;
		pWindow		canvas;
		RopType		rop;

		DrawObject ();
		DrawObject ( Point );
		DrawObject ( const DrawObject &);
	
	DrawObject& operator=(const DrawObject &);

virtual void		Draw ();
virtual void		DrawEx (DWORD);		// #HK940215

	HDC		Handle ( Service = NULL );
		
public:
virtual RopType		ChangeRop ( RopType );
virtual Rectangle	BoundingBox ();
virtual BOOL		HitTest ( Point );
virtual void		Process ( Point );

virtual Point 		ChangePosition(Point);
virtual Point 		GetPosition();
virtual Dimension 	GetSize();

virtual Dimension	ChangeSize(Dimension);

virtual		~DrawObject ();
};

class _TF_ENTRY32 LineObject : public DrawObject
{
	pPen		mypen;

protected:
	Point		end;

void		Draw ();

public:
		LineObject ( Point start, Point end, pPen pen = NULL );

Rectangle	BoundingBox ();
pPen		ChangePen ( pPen newpen );

Point 		ChangePosition(Point);
Dimension	ChangeSize(Dimension);

Dimension 	GetSize();

		~LineObject ();
};

class _TF_ENTRY32 ShapeObject : public DrawObject
{
protected:
	pPen		mypen;
	pBrush		mybrush;
	Dimension	dim;
public:
		ShapeObject ( Point, Dimension, pPen pen, pBrush brush );
		ShapeObject(const ShapeObject&);

ShapeObject& operator=(const ShapeObject&);

pPen		ChangePen ( pPen );
pBrush		ChangeBrush ( pBrush );
Rectangle	BoundingBox ();

Dimension	ChangeSize(Dimension);
Dimension 	GetSize();

		~ShapeObject ();
};

class _TF_ENTRY32 RectangleObject : public ShapeObject
{
protected:
void		Draw ();

public:
		RectangleObject ( Point, Dimension, pPen = NULL, pBrush = NULL );
		~RectangleObject ();
};

class _TF_ENTRY32 EllipseObject : public ShapeObject
{
protected:
void		Draw ();

public:
		EllipseObject ( Point, Dimension, Pen* = NULL, Brush* = NULL ); 
		~EllipseObject ();
};

class _TF_ENTRY32 TextObject : public DrawObject
{
protected:
	pchar		text;
	Color		mycol;
	pFont		myfont;

void		Draw ();

public:
		TextObject ( Point, const char* txt, Color, pFont = NULL );
		TextObject ( Point, const char* txt, pFont = NULL );
		TextObject(const TextObject&);

TextObject& operator=(const TextObject&);

Rectangle	BoundingBox ();

		~TextObject ();
};

class _TF_ENTRY32 FmtTextObject : public TextObject
{
    uint        tabsize ;
public:
		FmtTextObject ( Point, const char* txt, Color, pFont = NULL );
		FmtTextObject ( Point, const char* txt, pFont = NULL );
		FmtTextObject(const FmtTextObject&);

FmtTextObject& operator=(const FmtTextObject&);

void        	SetTabSize( uint );
void		Draw ();

		~FmtTextObject ();
};  

class _TF_ENTRY32 BitmapObject : public ShapeObject
{
protected:
	pBitmap		bitmap;

void		Draw ();
public:
		BitmapObject ( Point, Dimension, pBitmap );

Rectangle	BoundingBox ();
Dimension	ChangeSize(Dimension);

		~BitmapObject ();
};

#if defined(WIN32)
#if !defined(NOWIN95CONTROLS)

class _TF_ENTRY32 CImageListObject : public ShapeObject {
protected:
	CImageList *m_pIList;
	int m_iIndex;
	UINT m_uiStyle;

	void Draw (void);

public:
		CImageListObject (Point, CImageList *pIList, 
				  int iIndex, UINT uiStyle = ILD_NORMAL);
		~CImageListObject (void);

	void SetIndex (int iIndex);
	void SetStyle (UINT uiStyle);
};

#endif // NOWIN95CONTROLS

class _TF_ENTRY32 CPolygonObject : 
	public DrawObject
{
protected:
	pPen		mypen;
	pBrush		mybrush;

	const Point *m_pPts;
	int m_nCount;
	BOOL m_fArea;

	void Draw (void);

public: 
		CPolygonObject (Point ptRef, const Point *pPts, int nCount,
			pPen pP = NULL, BOOL fArea = false,	pBrush pBr = NULL);
};

class _TF_ENTRY32 CPolyPolygonObject : 
	public CPolygonObject
{
protected:
	const int *m_piPolyCounts;

	void Draw (void);

public:
		CPolyPolygonObject (Point ptRef, const Point *pPts, 
			const int *piPolyCounts, int nCount, 
			pPen pP = NULL, BOOL fArea = false, pBrush pBr = NULL);
};

#endif // WIN32

#endif // _DRAWOBJ_HXX
