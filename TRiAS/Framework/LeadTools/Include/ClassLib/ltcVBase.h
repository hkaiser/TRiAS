/*----------------------------------------------------------------------------+
| LEADTOOLS for Windows -                                                     |
| Copyright (c) 1991-2000 LEAD Technologies, Inc.                             |
| All Rights Reserved.                                                        |
|-----------------------------------------------------------------------------|
| PROJECT   : LEAD wrappers                                                   |
| FILE NAME : ltcVBase.h                                                      |
| DESC      :                                                                 |
+----------------------------------------------------------------------------*/

#ifndef  _LEAD_VECTOR_BASE_H_
#define  _LEAD_VECTOR_BASE_H_


#define VECTOR_RESET_ROTATE          (0x00000001)
#define VECTOR_RESET_SCALE           (0x00000002)
#define VECTOR_RESET_TRANSLATE       (0x00000004)
#define VECTOR_RESET_CAMERA          (0x00000008)
#define VECTOR_RESET_PARALLELOGRAM   (0x00000010)
#define VECTOR_RESET_ORIGIN          (0x00000020)
#define VECTOR_RESET_PAN             (0x00000040)
#define VECTOR_RESET_ALL             (VECTOR_RESET_ROTATE         | \
                                      VECTOR_RESET_SCALE          | \
                                      VECTOR_RESET_TRANSLATE      | \
                                      VECTOR_RESET_CAMERA         | \
                                      VECTOR_RESET_PARALLELOGRAM  | \
                                      VECTOR_RESET_ORIGIN         | \
                                      VECTOR_RESET_PAN              \
                                      )

#define VECTOR_EVENT_IGNORE 30000  //All class library events start at 30000
#define VECTOR_EVENT_RESET  30001


/*----------------------------------------------------------------------------+
| CLASSES DECLARATION                                                         |
+----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------+
| Class     : LVectorBase                                                     |
| Desc      :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+*/
class LWRP_EXPORT LVectorBase:public LBase
{
   LEAD_DECLAREOBJECT(LVectorBase);
   LEAD_DECLARE_CLASS_MAP();

   friend class LBitmapDictionary;
   friend LWRP_EXPORT LBase L_FAR* LEAD_GetObject(LWRAPPEROBJECTTYPE nType,LBase L_FAR* This,LPLEADCREATEOBJECT pCreateObj);

   private:
      LVectorDialog        L_FAR*   m_pLVectorDialog;
      LVectorFile          L_FAR*   m_pLVectorFile;
      LVectorMemoryFile    L_FAR*   m_pLVectorMemoryFile;
      LVectorLayer         L_FAR*   m_pLVectorLayer;
      LVectorObject        L_FAR*   m_pLVectorObject;

      L_BOOL                        m_bNotifyOnChange;
      L_BOOL                        m_bAlwaysEndNotification;
      L_BOOL                        m_bRedirectStatusCallBack;
      //L_BOOL                        m_bIsAllocated;
      L_BOOL                        m_bEnableFileName;

      //For LVKRN event callback
      pVECTOREVENTPROC m_OldEventProc;
      L_VOID          *m_pOldEventUserData;  

      //
      VECTOREVENT      m_Event;


   protected:  
      L_CHAR                        m_szFileName[MAX_PATH+1];
      VECTORHANDLE                  m_VectorHandle;
      //pVECTORHANDLE                 m_pVectorHandle;

    private:  
      L_VOID InitializeClass();     //Initialize all the local variables for LBitmapBase

      static L_INT EXT_CALLBACK EnumObjectsCS ( pVECTORHANDLE pVector, const pVECTOROBJECT pObject, L_VOID L_FAR * pUserData);
      static L_INT EXT_CALLBACK EnumVerticesCS( pVECTORHANDLE pVector, pVECTORPOINT pVertex, L_VOID L_FAR *pUserData);
      static L_INT EXT_CALLBACK EnumLayersCS  ( pVECTORHANDLE pVector, const pVECTORLAYER pLayer, L_VOID L_FAR *pUserData );
      static L_INT EXT_CALLBACK EnumGroupsCS  ( pVECTORHANDLE pVector, const pVECTORGROUP pGroup, L_VOID L_FAR *pUserData );
      
      static L_INT EXT_CALLBACK VectorEventProcCS(
                     pVECTORHANDLE pVector, 
                     L_UINT uLevel, 
                     pVECTOREVENT pEvent, 
                     L_VOID L_FAR *pUserData 
                     ); 
      virtual L_INT     Initialize();

   protected : 
      virtual L_INT  EnumObjectsCallBack( pVECTORHANDLE pVector, pVECTOROBJECT pObject);
      virtual L_INT  EnumVerticesCallBack( pVECTORHANDLE pVector, pVECTORPOINT pVertex);
      virtual L_INT  EnumLayersCallBack(pVECTORHANDLE pVector, pVECTORLAYER pLayer);   
      virtual L_INT  EnumGroupsCallBack(pVECTORHANDLE pVector, pVECTORGROUP pGroup);   
      virtual L_INT  VectorEventProcCallBack(
                           pVECTORHANDLE pVector, 
                           L_UINT uLevel, 
                           pVECTOREVENT pEvent, 
                           L_VOID L_FAR *pUserData 
                           );
      virtual L_INT  ResetView(L_UINT uFlags = VECTOR_RESET_ALL);

   public:
      virtual L_INT  EventOff(L_UINT uType, L_BOOL bAddUndoNode);
      virtual L_INT  EventOn(L_UINT uType, L_INT nErrorCode);


   public : 
      LVectorBase();
      LVectorBase(pVECTORHANDLE pVectorHandle);

      virtual ~LVectorBase();

      L_INT             GetFileName(L_CHAR L_FAR* pszBuffer,L_UINT L_FAR* puBuffSize);
      L_VOID            SetFileName(L_CHAR L_FAR* pszFileName);
      L_BOOL            IsFileNameEnabled();
      L_BOOL            EnableFileName(L_BOOL bEnableFileName=TRUE);


      pVECTORHANDLE     GetHandle(); 
      L_INT             SetHandle(pVECTORHANDLE pVectorHandle,L_BOOL bFreePrev=TRUE);

      LVectorBase&      operator=(LVectorBase& LBitmapSrc); 

      virtual L_INT     StartChanging(L_UINT nChangeType,L_UINT nChangeCategory);
      virtual L_VOID    EndChanging(L_UINT nChangeType,L_UINT nChangeCategory,L_INT nRetCode);
      virtual L_BOOL    EnableChangeNotification(L_BOOL bEnable=TRUE);
      virtual L_BOOL    IsChangeNotificationEnabled();
      virtual L_BOOL    EnableAlwaysEndNotification(L_BOOL bEnable=TRUE);
      virtual L_BOOL    IsAlwaysEndNotification();
      


      virtual L_INT     Load(L_CHAR L_FAR * pszFile, 
                               pLOADFILEOPTION pLoadOptions = NULL,
                               pFILEINFO pFileInfo = NULL);

      virtual L_INT     Load(pLOADFILEOPTION pLoadOptions = NULL,
                              pFILEINFO pFileInfo = NULL);

      virtual L_INT     Save(  L_CHAR L_FAR * pszFile, 
                                 L_INT nFormat,
                                 pSAVEFILEOPTION pSaveOptions=NULL);

      virtual L_INT     Save(  L_INT nFormat,
                                 pSAVEFILEOPTION pSaveOptions=NULL);

      virtual L_BOOL    EnableRedirectStatusCallBack(L_BOOL bEnable=TRUE);
      virtual L_BOOL    IsRedirectStatusCallBackEnabled();
      virtual L_BOOL    IsAllocated() ;

      //Event Functions
      virtual L_INT     Event(pVECTOREVENT );

      //general functions
      virtual L_INT     Free();
      virtual L_INT     Empty();
      virtual L_INT     IsEmpty(L_BOOL L_FAR *pbEmpty);
      virtual L_INT     Copy(LVectorBase& LBitmapSrc, L_UINT32 dwFlags=0);

      virtual L_INT     SetDisplayOptions( const pVECTOR_DISPLAY_OPTIONS pOptions );
      virtual L_INT     GetDisplayOptions( pVECTOR_DISPLAY_OPTIONS pOptions );

      virtual L_INT     InvertColors( );

      virtual L_INT     SetViewport(const RECT L_FAR *pViewport);
      virtual L_INT     GetViewport(RECT L_FAR * pViewport);
      virtual L_INT     SetPan(const POINT L_FAR *pPan);
      virtual L_INT     GetPan(POINT L_FAR * pPan);
      virtual L_INT     Paint(HDC hdc, L_BOOL bEraseBkgnd );
      virtual L_INT     Realize( pBITMAPHANDLE pBitmap, L_BOOL bEraseBkgnd = TRUE);
      virtual L_INT     Realize(LBitmapBase &BitmapBase, L_BOOL bEraseBkgnd = TRUE);
      virtual L_INT     Is3D(L_BOOL L_FAR *pbIs3D);
      virtual L_INT     IsLocked(L_BOOL L_FAR *pbLocked);
      virtual L_INT     SetLocked(L_BOOL bLock);

      virtual L_INT     SetBackgroundColor(L_COLOR color = 0);
      virtual L_INT     GetBackgroundColor(L_COLOR L_FAR *pColor);

      virtual L_INT     LogicalToPhysical(POINT L_FAR *pDst, const pVECTORPOINT pSrc);
      virtual L_INT     PhysicalToLogical(pVECTORPOINT pDst, const POINT L_FAR *pSrc);

      virtual L_INT     SetPalette(HPALETTE );
      virtual HPALETTE  GetPalette();
      
      virtual L_INT     SetViewMode(L_INT nMode = VECTOR_VIEWMODE_FIT);
      virtual L_INT     GetViewMode();

      virtual L_INT     Reset(L_UINT uFlags = VECTOR_RESET_ALL);



      //transformation functions      
      virtual L_INT     SetTranslation(const pVECTORPOINT pTranslation, L_UINT32 dwFlags=0);
      virtual L_INT     GetTranslation(pVECTORPOINT pTranslation );
      
      virtual L_INT     SetRotation(const pVECTORPOINT pRotation, const pVECTORPOINT pOrigin=NULL, L_UINT32 dwFlags=0);
      virtual L_INT     GetRotation(pVECTORPOINT pRotation);

      virtual L_INT     SetScale(const pVECTORPOINT pScale, const pVECTORPOINT pOrigin=NULL, L_UINT32 dwFlags=0);
      virtual L_INT     GetScale(pVECTORPOINT pScale);

      virtual L_INT     SetOrigin( const pVECTORPOINT pOrigin = NULL);
      virtual L_INT     GetOrigin(  pVECTORPOINT pOrigin );

      virtual L_INT     ApplyTransformation();
      virtual L_INT     ZoomRect( const RECT L_FAR *pRect );

      //Attributes functions
      virtual L_INT     SetBindVerticesMode(L_INT nMode);
      virtual L_INT     GetBindVerticesMode();

      virtual L_INT     SetParallelogram( const pVECTORPOINT pMin, const pVECTORPOINT pMax );
      virtual L_INT     GetParallelogram( pVECTORPOINT pMin, pVECTORPOINT pMax );

      virtual L_INT     EnumVertices(L_UINT32 dwFlags=0);

      //Camera functions
      virtual L_INT     SetCamera(const pVECTORCAMERA pVectorCamera=NULL);
      virtual L_INT     GetCamera(pVECTORCAMERA pVectorCamera);

      //Metafile functions
      virtual L_INT     ConvertToEMF( HDC hdc, HENHMETAFILE L_FAR *phEnhMetaFile, L_UINT uDPI, const RECT L_FAR *pRect = NULL);
      virtual L_INT     ConvertFromEMF( HDC hdc, HENHMETAFILE hEMF);
      virtual L_INT     ConvertToWMF( HDC hdc, HMETAFILE L_FAR *phMetaFile, L_UINT uDPI, const RECT L_FAR *pRect = NULL);
      virtual L_INT     ConvertFromWMF( HDC hdc, HMETAFILE hWMF);

      //Engine functions
      virtual L_INT     GetEngine();
      virtual L_INT     AttachToWindow(HWND hWnd, L_INT nEngine = VECTOR_ENGINE_GDI, L_UINT32 dwFlags = VECTOR_ENGINE_DOUBLEBUFFER);

      //Marker Functions
      virtual L_INT     SetMarker( const pVECTORMARKER pMarker );
      virtual L_INT     GetMarker( pVECTORMARKER pMarker );

      //Hit test functions
      virtual L_INT     SetHitTest( const pVECTORHITTEST pHitTest );
      virtual L_INT     GetHitTest( pVECTORHITTEST pHitTest );
      virtual L_INT     HitTest(const POINT L_FAR *pPoint, LVectorObject L_FAR *pLVectorObject);

      //Polygon functions
      virtual L_INT     SetPolygonMode(L_INT nMode = VECTOR_POLYGON_LINE);
      virtual L_INT     GetPolygonMode();

      virtual L_INT     SetUseLights(L_BOOL bUseLights=TRUE);
      virtual L_INT     GetUseLights();
      virtual L_INT     SetAmbientColor(L_COLOR color);
      virtual L_INT     GetAmbientColor(L_COLOR L_FAR *pColor);

      //Clipboard functions
      virtual L_BOOL    IsClipboardReady();
      virtual L_INT     CopyToClipboard( HWND hWnd=NULL, L_UINT32 dwFlags=0);
      virtual L_INT     CopyFromClipboard( HWND hWnd=NULL, L_UINT32 dwFlags=0);

      //Layer functions
      virtual L_INT     AddLayer( LVectorLayer *pVectorLayer, L_UINT32 dwFlags = VECTOR_FLAGS_RENAME_DUPLICATES);
      virtual L_INT     GetLayerByName(  const L_CHAR L_FAR *pszName, LVectorLayer *pVectorLayer );
      virtual L_INT     GetLayerCount();
      virtual L_INT     GetLayerByIndex( const  L_INT nIndex, LVectorLayer *pVectorLayer );
      virtual L_INT     EnumLayers();
      virtual L_INT     SetActiveLayer(  LVectorLayer *pVectorLayer );
      virtual L_INT     GetActiveLayer( LVectorLayer *pVectorLayer );

      virtual L_INT     CopyLayer(
                                 L_FAR LVectorLayer  *pVectorLayerDst,    // can be NULL 
                                 L_FAR LVectorLayer  *pVectorLayerSrc,   // Must be non-null 
                                 L_UINT32 dwFlags = 0                    // copy flags 
                                 );

      //Group functions
      virtual L_INT     AddGroup( LVectorGroup *pVectorGroup, L_UINT32 dwFlags = VECTOR_FLAGS_RENAME_DUPLICATES);
      virtual L_INT     GetGroupByName(  const L_CHAR L_FAR *pszName, LVectorGroup *pVectorGroup );
      virtual L_INT     GetGroupCount();
      virtual L_INT     GetGroupByIndex( const  L_INT nIndex, LVectorGroup *pVectorGroup );
      virtual L_INT     EnumGroups();
      virtual L_INT     CopyGroup(
                                 L_FAR LVectorGroup  *pVectorGroupDst,    // can be NULL 
                                 L_FAR LVectorGroup  *pVectorGroupSrc,   // Must be non-null 
                                 L_UINT32 dwFlags = 0                    // copy flags 
                                 );

  
         


      //Object functions
      virtual L_INT     GetObjectParallelogram(pVECTORPOINT pMin, pVECTORPOINT pMax, L_UINT32 dwFlags=0);      
      virtual L_INT     GetObjectRect(RECT L_FAR *pRect, L_UINT32 dwFlags=0);
      virtual L_INT     IsObjectInsideParallelogram(const pVECTORPOINT pLeftTop, const pVECTORPOINT pRightBottom, L_BOOL L_FAR *bInside, L_UINT32 dwFlags  = 0);
      virtual L_INT     IsObjectInsideRect(const RECT L_FAR *pRect, L_BOOL L_FAR *bInside, L_UINT32 dwFlags = 0);
      virtual L_INT     EnumObjects( L_UINT32 dwFlags=0);

      virtual L_INT     CopyObject(
                              L_FAR LVectorLayer  *pLayerDst,  //can be null
                              L_FAR LVectorObject *pObjectDst, //can be null
                              L_FAR LVectorObject *pObjectSrc  //Must be non-null
                              );

     virtual L_INT     CopyObject(
                              L_FAR LVectorObject *pObjectSrc  //Must be non-null
                              );


      virtual L_INT     DeleteObject(L_UINT32 dwFlags = 0 );
      virtual L_INT     ExplodeObject(L_UINT32 dwFlags = 0);

      virtual L_INT     IsObjectSelected(L_BOOL L_FAR *pbSelected);
      virtual L_INT     IsObjectHidden(L_BOOL L_FAR *pbHidden);
      virtual L_INT     SetObjectAttributes(  const L_INT *pnROP, const pVECTORPEN pPen, const pVECTORBRUSH pBrush, const pVECTORFONT pFont, L_UINT32 dwFlags=0);
      virtual L_INT     AddObject(LVectorObject *pVectorObject);      

};

#endif //_LEAD_VECTOR_BASE_H_
/*================================================================= EOF =====*/
