/*----------------------------------------------------------------------------+
| LEADTOOLS for Windows -                                                     |
| Copyright (c) 1991-2000 LEAD Technologies, Inc.                             |
| All Rights Reserved.                                                        |
|-----------------------------------------------------------------------------|
| PROJECT   : LEAD wrappers                                                   |
| FILE NAME : ltcCnvrt.h                                                      |
| DESC      :                                                                 |
+----------------------------------------------------------------------------*/

#ifndef  _LEAD_SHAPE_H_
#define  _LEAD_SHAPE_H_

//#include "windows.h"
//#include "lttyp.h"
//#include "..\..\include\l_bitmap.h"
/*----------------------------------------------------------------------------+
| DEFINES                                                                     |
+----------------------------------------------------------------------------*/
#define RECTANGLE_TYPE_RECT           0 
#define RECTANGLE_TYPE_ELLIPSE        1 
#define RECTANGLE_TYPE_ROUNDRECT      2
#define RECTANGLE_TYPE_TRIANGLE       3

/*----------------------------------------------------------------------------+
| Class     : LShape                                                          |
| Desc      :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : September  1998                                                 |
+----------------------------------------------------------------------------*/
class LShape
{
public:
   L_VOID *m_extLShape;
   
protected:
   HWND m_hWnd;
   RECT m_rcBoundRect;
public:
   LShape(HWND hWnd);
   virtual ~LShape();
   virtual L_VOID  Draw();
   virtual L_VOID  Draw(HDC hdc);
   virtual L_VOID  StartPos(POINT& point);
   virtual L_VOID  MoveStartPos(L_INT x,L_INT y);
   virtual L_VOID  NewPos(POINT&   point);
   virtual L_VOID  EndPos(POINT&   point);
   virtual LPPOINT GetPoint();
   virtual L_UINT  GetPointCount();

   L_VOID  GetBoundRect(LPRECT lpRect);
   L_VOID  SetBoundRect(RECT& rect);
   virtual HRGN  CreateRegionHandle();
   L_VOID  ClearDrawing();
};
/*----------------------------------------------------------------------------+
| Class     : LRectangle                                                      |
| Desc      :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : September  1998                                                 |
+----------------------------------------------------------------------------*/
class LRectangle : public LShape
{
public:
   L_VOID *m_extLRectangle;
   
private:
   RECT  m_Rect; 
   L_INT m_nType;  
   POINT points[4];
public:
   LRectangle(HWND hWnd,L_INT nRectType);
   virtual ~LRectangle();
   virtual L_VOID  Draw();
   virtual L_VOID  Draw(HDC hdc);
   virtual L_VOID  StartPos(POINT& point);
   virtual L_VOID  MoveStartPos(L_INT x,L_INT y);

   virtual L_VOID  NewPos(POINT&   point);
   virtual L_VOID  EndPos(POINT&   point);
   virtual LPPOINT GetPoint();
   virtual L_UINT  GetPointCount();
   virtual HRGN    CreateRegionHandle();
};

/*----------------------------------------------------------------------------+
| Class     : LPointBase                                                      |
| Desc      :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : September  1998                                                 |
+----------------------------------------------------------------------------*/
#define POINT_ALLOCATE_SIZE  50
class LPointBase: public LShape
{
public:
   L_VOID *m_extLPointBase;
   
protected:
   HGLOBAL   hPoint;
   LPPOINT   lpPoint;
   L_UINT    m_uPointCount;
   L_UINT    m_uSize;
   
public:
   LPointBase(HWND hWnd);
   virtual ~LPointBase();
   virtual L_VOID  Draw();
   virtual L_VOID  Draw(HDC hdc);
   virtual L_VOID  StartPos(POINT& point);
   virtual L_VOID  MoveStartPos(L_INT x,L_INT y);
   virtual L_VOID  NewPos(POINT&   point);
   virtual L_VOID  EndPos(POINT&   point);
   virtual LPPOINT GetPoint();
   virtual L_UINT  GetPointCount();
   virtual HRGN    CreateRegionHandle();
};
/*----------------------------------------------------------------------------+
| Class     : LFreeHand                                                       |
| Desc      :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : September  1998                                                 |
+----------------------------------------------------------------------------*/
class LFreeHand: public LPointBase
{
   
public:
   L_VOID *m_extLFreeHand;
   
public:
   LFreeHand(HWND hWnd);
   virtual ~LFreeHand();
};
/*----------------------------------------------------------------------------+
| Class     : LFreeHand                                                       |
| Desc      :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : September  1998                                                 |
+----------------------------------------------------------------------------*/
class LPolygon: public LPointBase
{
public:
   L_VOID *m_extLPolygon;

protected:
   L_BOOL m_Start;
   POINT  m_EndPoint;
protected:
public:
   LPolygon(HWND hWnd);
   virtual ~LPolygon();
   virtual L_VOID  StartPos(POINT& point);
   virtual L_VOID  NewPos  (POINT&   point);
   virtual L_VOID  EndPos  (POINT&   point);
   virtual L_VOID  Draw();
   virtual L_VOID Draw(HDC hdc);
};

class LCurve : public LPointBase
{
public:
   L_VOID *m_extLPolygon;

protected:
   L_BOOL m_Start;
   POINT  m_EndPoint;
   CURVE*  m_pCurve;
   virtual L_VOID DrawPoint(HDC hdc,const POINT& piont);
   virtual L_VOID RedrawPoints(HDC hdc );
public:
   LCurve(HWND hWnd,CURVE* pCurve);
   virtual L_VOID Draw();
   virtual L_VOID Draw(HDC hdc);
   virtual L_VOID  NewPos(POINT&   point);
   virtual L_VOID  EndPos(POINT&   point);
   virtual L_VOID  StartPos(POINT& point);
};
class LBezier : public LCurve
{ 
public:
   LBezier(HWND hWnd,CURVE* pCurve);
   virtual L_VOID Draw();
   virtual L_VOID Draw(HDC hdc);
};


#endif //_LEAD_SHAPE_H_