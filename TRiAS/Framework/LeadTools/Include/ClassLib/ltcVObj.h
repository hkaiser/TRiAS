/*----------------------------------------------------------------------------+
| LEADTOOLS for Windows -                                                     |
| Copyright (c) 1991-2000 LEAD Technologies, Inc.                             |
| All Rights Reserved.                                                        |
|-----------------------------------------------------------------------------|
| PROJECT   : LEAD wrappers                                                   |
| FILE NAME : ltcVObj.h                                                       |
| DESC      :                                                                 |
+----------------------------------------------------------------------------*/
#ifndef  _LEAD_VECTOR_OBJECT_H_
#define  _LEAD_VECTOR_OBJECT_H_

/*----------------------------------------------------------------------------+
| Class     : LVectorObject                                                   |
| Desc      :                                                                 |
| Return    :                                                                 | 
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+*/

typedef union VECTOROBJECTUNIONtag
{
   VECTOROBJECT         Object;
   VECTORVERTEX         Vertex;
   VECTORLINE           Line;
   VECTORRECTANGLE      Rectangle;
   VECTORCURVEOPENED    CurveOpened;
   VECTORPOLYLINE       PolyLine;
   VECTORPOLYBEZIER     PolyBezier;
   VECTORCURVECLOSED    CurveClosed;
   VECTORPOLYGON        Polygon;
   VECTORELLIPSE        Ellipse;
   VECTORCIRCLE         Circle;
   VECTORARC            Arc;
   VECTORELLIPTICALARC  EllipticalArc;
   VECTORTEXT           Text;
   VECTORPIE            Pie;
   VECTORCHORD          Chord;
   VECTORPOLYDRAW       PolyDraw;
   VECTORRASTER         Raster;
   VECTORSTOCK          Stock;
   VECTORCLONE          Clone;
} VECTOROBJECTUNION, L_FAR *pVECTOROBJECTUNION;

class LWRP_EXPORT LVectorObject : public LBase
{
   LEAD_DECLAREOBJECT(LVectorObject);
   
   friend LVectorBase;
   friend LVectorLayer;
   friend LVectorGroup;
   friend LVectorDialog;
   friend LAutomation;

private:
   
protected:
   LVectorBase  L_FAR  *m_pLVector;        //vector object belongs to
   L_INT                m_nType;           //type of object
   VECTOROBJECTUNION    m_Desc;            //this is different for each derived class (line, vertex, etc.)
                                           //Used only in constructor and L_VecAddObject()
                                           //freed in the destructor
   
   VECTOROBJECTUNION    m_DescCopy;        //when locked, holds a copy of m_Desc
                                           //when unlocked, this is freed

   L_BOOL               m_bDescValid;      //TRUE if m_Desc is valid
   VECTOROBJECT         m_Object;          //returned when object added
   L_BOOL               m_bObjectValid;    //TRUE if m_bObject is valid
   L_BOOL               m_bLocked;         //TRUE ifcalled LockObject()
   VECTORPOINT         *m_pPoint;          //for saving array of points            
   L_INT                m_nPointCount;
   
private:  
   L_VOID      InitializeClass();
   L_BOOL      ValidateObject();
   L_INT       UpdateObjectDesc();
   L_BOOL      UpdateObjectType();

protected:
   L_VOID      GetDefaultPen(pVECTORPEN pPen);
   L_VOID      GetDefaultBrush(pVECTORBRUSH pBrush);

public : 
   LVectorObject();
   LVectorObject(pVECTOROBJECT pObject,  LVectorBase *pVector=NULL);
   ~LVectorObject();
   
   L_VOID  SetVector(LVectorBase L_FAR* pVector);
   L_INT   GetType();
   L_BOOL  IsValid();
   L_BOOL  IsTypeValid();
   
   virtual L_INT LockObject(pVECTOROBJECT pObject);
   virtual L_INT UnlockObject(pVECTOROBJECT pObject);
   
   L_INT ExplodeObject(L_UINT32 dwFlags = 0);
   L_INT GetObjectParallelogram(pVECTORPOINT pMin, pVECTORPOINT pMax);
   L_INT GetObjectRect(RECT L_FAR *pRect);
   
   L_INT IsObjectInsideParallelogram(const pVECTORPOINT pLeftTop, const pVECTORPOINT pRightBottom, L_BOOL L_FAR *bInside);
   L_INT IsObjectInsideRect(const RECT L_FAR *pRect, L_BOOL L_FAR *bInside);
   
   L_INT SelectObject(L_BOOL bSelect=TRUE);
   L_INT IsObjectSelected(L_BOOL L_FAR *pbSelected);

   L_INT HideObject(L_BOOL bHide=TRUE);
   L_INT IsObjectHidden(L_BOOL L_FAR *pbHidden);
   
   L_INT SetTranslation(const pVECTORPOINT pTranslation);
   L_INT SetRotation(const pVECTORPOINT pRotation, const pVECTORPOINT pOrigin=NULL);
   L_INT SetScale(const pVECTORPOINT pScale, const pVECTORPOINT pOrigin=NULL);
   
   L_INT DeleteObject();
   
   L_INT SetObjectAttributes(  const L_INT *pnROP, const pVECTORPEN pPen, const pVECTORBRUSH pBrush, const pVECTORFONT pFont);
   L_INT GetObjectAttributes(  L_INT *pnROP, pVECTORPEN pPen, pVECTORBRUSH pBrush, pVECTORFONT pFont );

   L_INT SetTooltip( L_CHAR *pszTooltip );
   L_UINT32 GetTooltip( L_CHAR *pBuffer, L_UINT32 uSize );
   L_INT ShowTooltip( pVECTORTOOLTIPDESC pTooltipDesc );
   L_INT HideTooltip( );

   L_INT SetViewContext( const pVECTORPOINT pMin, const pVECTORPOINT pMax );
   L_INT GetViewContext( pVECTORPOINT pMin, pVECTORPOINT pMax );
   L_INT RemoveViewContext( );

   L_INT AddHyperlink( pVECTORLINKDESC pTarget );
   L_INT SetHyperlink( L_UINT32 uIndex, pVECTORLINKDESC pTarget );
   L_INT GetHyperlink( L_UINT32 uIndex, pVECTORLINKDESC pTarget );
   L_UINT32 GetHyperlinkCount( );
   L_INT GotoHyperlink( L_UINT32 uIndex );

   L_INT SetDescription( L_CHAR *pszTarget );
   L_UINT32 GetDescription( L_CHAR *pBuffer, L_UINT32 uSize );
};


//************ LVectorVertex ************************************************************
class LWRP_EXPORT LVectorVertex : public LVectorObject
{
   LEAD_DECLAREOBJECT(LVectorVertex);
   
public : 
   LVectorVertex(pVECTORVERTEX pVertex = NULL);
   LVectorVertex(pVECTOROBJECT pObject,  LVectorBase *pVector=NULL);
   ~LVectorVertex();
   virtual L_INT  LockObject(pVECTORVERTEX pVertex);   
   virtual L_INT  UnlockObject(pVECTORVERTEX pVertex);
};

//************ LVectorLine ************************************************************
class LWRP_EXPORT LVectorLine : public LVectorObject
{
   LEAD_DECLAREOBJECT(LVectorLine);
   
public : 
   LVectorLine(pVECTORLINE pLine = NULL);
   LVectorLine(pVECTOROBJECT pObject,  LVectorBase *pVector=NULL);
   ~LVectorLine();
   virtual L_INT  LockObject(pVECTORLINE pLine);   
   virtual L_INT  UnlockObject(pVECTORLINE pLine);
};

//************ LVectorRectangle ************************************************************
class LWRP_EXPORT LVectorRectangle : public LVectorObject
{
   LEAD_DECLAREOBJECT(LVectorRectangle);
   
public : 
   LVectorRectangle(pVECTORRECTANGLE pRectangle = NULL);
   LVectorRectangle(pVECTOROBJECT pObject,  LVectorBase *pVector=NULL);
   ~LVectorRectangle();
   virtual L_INT  LockObject(pVECTORRECTANGLE pRectangle);   
   virtual L_INT  UnlockObject(pVECTORRECTANGLE pRectangle);
};

//************ LVectorPolyBezier ************************************************************
class LWRP_EXPORT LVectorPolyBezier : public LVectorObject
{
   LEAD_DECLAREOBJECT(LVectorPolyBezier);
   
public : 
   LVectorPolyBezier(pVECTORPOLYBEZIER pPolyBezier = NULL);
   LVectorPolyBezier(pVECTOROBJECT pObject,  LVectorBase *pVector=NULL);
   ~LVectorPolyBezier();
   virtual L_INT  LockObject(pVECTORPOLYBEZIER pPolyBezier);   
   virtual L_INT  UnlockObject(pVECTORPOLYBEZIER pPolyBezier);
};

//************ LVectorPolygon ************************************************************
class LWRP_EXPORT LVectorPolygon : public LVectorObject
{
   LEAD_DECLAREOBJECT(LVectorPolygon);
   
public : 
   LVectorPolygon(pVECTORPOLYGON pPolygon = NULL);
   LVectorPolygon(pVECTOROBJECT pObject,  LVectorBase *pVector=NULL);
   ~LVectorPolygon();
   virtual L_INT  LockObject(pVECTORPOLYGON pPolygon);   
   virtual L_INT  UnlockObject(pVECTORPOLYGON pPolygon);
};

//************ LVectorEllipse ************************************************************
class LWRP_EXPORT LVectorEllipse : public LVectorObject
{
   LEAD_DECLAREOBJECT(LVectorEllipse);
   
public : 
   LVectorEllipse(pVECTORELLIPSE pEllipse = NULL);
   LVectorEllipse(pVECTOROBJECT pObject,  LVectorBase *pVector=NULL);
   ~LVectorEllipse();
   virtual L_INT  LockObject(pVECTORELLIPSE pEllipse);   
   virtual L_INT  UnlockObject(pVECTORELLIPSE pEllipse);
};

//************ LVectorCircle ************************************************************
class LWRP_EXPORT LVectorCircle : public LVectorObject
{
   LEAD_DECLAREOBJECT(LVectorCircle);
   
public : 
   LVectorCircle(pVECTORCIRCLE pCircle = NULL);
   LVectorCircle(pVECTOROBJECT pObject,  LVectorBase *pVector=NULL);
   ~LVectorCircle();
   virtual L_INT  LockObject(pVECTORCIRCLE pCircle);   
   virtual L_INT  UnlockObject(pVECTORCIRCLE pCircle);
};

//************ LVectorArc ************************************************************
class LWRP_EXPORT LVectorArc : public LVectorObject
{
   LEAD_DECLAREOBJECT(LVectorArc);
   
public : 
   LVectorArc(pVECTORARC pArc = NULL);
   LVectorArc(pVECTOROBJECT pObject,  LVectorBase *pVector=NULL);
   ~LVectorArc();
   virtual L_INT  LockObject(pVECTORARC pArc);   
   virtual L_INT  UnlockObject(pVECTORARC pArc);
};

//************ LVectorEllipticalArc **************************************************
class LWRP_EXPORT LVectorEllipticalArc : public LVectorObject
{
   LEAD_DECLAREOBJECT(LVectorEllipticalArc);
   
public : 
   LVectorEllipticalArc(pVECTORELLIPTICALARC pEllipticalArc = NULL);
   LVectorEllipticalArc(pVECTOROBJECT pObject,  LVectorBase *pVector=NULL);
   ~LVectorEllipticalArc();
   virtual L_INT  LockObject(pVECTORELLIPTICALARC pEllipticalArc);   
   virtual L_INT  UnlockObject(pVECTORELLIPTICALARC pEllipticalArc);
};

//************ LVectorText ************************************************************
class LWRP_EXPORT LVectorText : public LVectorObject
{
   LEAD_DECLAREOBJECT(LVectorText);
   
public : 
   LVectorText(pVECTORTEXT pText = NULL);
   LVectorText(pVECTOROBJECT pObject,  LVectorBase *pVector=NULL);
   ~LVectorText();
   virtual L_INT  LockObject(pVECTORTEXT pText);   
   virtual L_INT  UnlockObject(pVECTORTEXT pText);
};

//************ LVectorPie ************************************************************
class LWRP_EXPORT LVectorPie : public LVectorObject
{
   LEAD_DECLAREOBJECT(LVectorPie );
   
public : 
   LVectorPie(pVECTORPIE pPie=NULL);
   LVectorPie(pVECTOROBJECT pObject,  LVectorBase *pVector=NULL);
   ~LVectorPie();
   virtual L_INT  LockObject(pVECTORPIE pPie);   
   virtual L_INT  UnlockObject(pVECTORPIE pPie);
};

//************ LVectorChord ************************************************************
class LWRP_EXPORT LVectorChord : public LVectorObject
{
   LEAD_DECLAREOBJECT(LVectorChord);
   
public : 
   LVectorChord(pVECTORCHORD pChord = NULL);
   LVectorChord(pVECTOROBJECT pObject,  LVectorBase *pVector=NULL);
   ~LVectorChord();
   virtual L_INT  LockObject(pVECTORCHORD pChord);   
   virtual L_INT  UnlockObject(pVECTORCHORD pChord);
};


//************ LVectorPolyDraw ************************************************************
class LWRP_EXPORT LVectorPolyDraw : public LVectorObject
{
   LEAD_DECLAREOBJECT(LVectorPolyDraw);
   
public : 
   LVectorPolyDraw(pVECTORPOLYDRAW pPolyDraw = NULL);
   LVectorPolyDraw(pVECTOROBJECT pObject,  LVectorBase *pVector=NULL);
   ~LVectorPolyDraw();
   virtual L_INT  LockObject(pVECTORPOLYDRAW pPolyDraw);   
   virtual L_INT  UnlockObject(pVECTORPOLYDRAW pPolyDraw);
};

//************ LVectorRaster ************************************************************
class LWRP_EXPORT LVectorRaster : public LVectorObject
{
   LEAD_DECLAREOBJECT(LVectorRaster);
   
public : 
   LVectorRaster(pVECTORRASTER pRaster = NULL);
   LVectorRaster(pVECTOROBJECT pObject,  LVectorBase *pVector=NULL);
   ~LVectorRaster();
   virtual L_INT  LockObject(pVECTORRASTER pRaster);   
   virtual L_INT  UnlockObject(pVECTORRASTER pRaster);
};


//************ LVectorStock ************************************************************
class LWRP_EXPORT LVectorStock : public LVectorObject
{
   LEAD_DECLAREOBJECT(LVectorStock);
   
public : 
   LVectorStock(pVECTORSTOCK pStock = NULL);
   LVectorStock(pVECTOROBJECT pObject,  LVectorBase *pVector=NULL);
   ~LVectorStock();
};

//************ LVectorPolyLine ************************************************************
class LWRP_EXPORT LVectorPolyLine : public LVectorObject
{
   LEAD_DECLAREOBJECT(LVectorPolyLine); 
   
public : 
   LVectorPolyLine(pVECTORPOLYLINE pPolyLine = NULL); 
   LVectorPolyLine(pVECTOROBJECT pObject,  LVectorBase *pVector=NULL);
   ~LVectorPolyLine();   
   virtual L_INT  LockObject(pVECTORPOLYLINE pPolyLine);   
   virtual L_INT  UnlockObject(pVECTORPOLYLINE pPolyLine);
};

//************ LVectorClone ************************************************************
class LWRP_EXPORT LVectorClone : public LVectorObject
{
   LEAD_DECLAREOBJECT(LVectorClone); 
   
public : 
   LVectorClone(pVECTORCLONE pClone = NULL);
   LVectorClone(pVECTOROBJECT pObject,  LVectorBase *pVector=NULL);
   ~LVectorClone();   
   virtual L_INT  LockObject(pVECTORCLONE pClone);   
   virtual L_INT  UnlockObject(pVECTORCLONE pClone);
   virtual L_INT  SetGroup(LVectorGroup *pVectorGroup);
};


#endif //_LEAD_VECTOR_LAYER_H_




/*================================================================= EOF =====*/