/*----------------------------------------------------------------------------+
| LEADTOOLS for Windows -                                                     |
| Copyright (c) 1991-2000 LEAD Technologies, Inc.                             |
| All Rights Reserved.                                                        |
|-----------------------------------------------------------------------------|
| PROJECT   : LEAD wrappers                                                   |
| FILE NAME : ltcfile.h                                                       |
| DESC      :                                                                 |
+----------------------------------------------------------------------------*/

#ifndef  _LEAD_FILE_H_
#define  _LEAD_FILE_H_

#ifndef WriteFileComment
#define WriteFileComment z001WriteFileComment
#endif 

/*----------------------------------------------------------------------------+
| CLASSES DECLARATION                                                         |
+----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------+
| Class     : LFile                                                           |
| Desc      :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : September 1998                                                  |
+----------------------------------------------------------------------------*/
class LWRP_EXPORT LBaseFile :public LBase
{
   LEAD_DECLAREOBJECT(LBaseFile);

   public:
      L_VOID *m_extLBaseFile;
      
   protected:  
      static   L_INT    EXT_CALLBACK LoadInfoCS(L_INT fd,pLOADINFO pInfo, L_VOID L_FAR * pBaseFile);
   
      static   L_INT    EXT_CALLBACK RedirectOpenCS(
                                       L_CHAR L_FAR *pFile,
                                       L_INT nMode,
                                       L_INT nShare,
                                       LBaseFile L_FAR*pUserData
                                      );
      static   L_INT    EXT_CALLBACK RedirectCloseCS(L_INT FD,
                                       LBaseFile L_FAR*pUserData);

      static   L_UINT   EXT_CALLBACK RedirectReadCS(
                                       L_INT FD,
                                       L_CHAR L_FAR *pBuf,
                                       L_INT nCount,
                                       LBaseFile L_FAR*pUserData
                                      );
      static   L_UINT    EXT_CALLBACK RedirectWriteCS(
                                          L_INT FD,
                                          L_CHAR L_FAR *pBuf,
                                          L_INT nCount,
                                          LBaseFile L_FAR*pUserData
                                       );
      static   L_INT32  EXT_CALLBACK RedirectSeekCS(
                                       L_INT FD,
                                       L_INT32 lnPos,
                                       L_INT nCount,
                                       LBaseFile L_FAR*pUserData
                                      );

   protected:  
      virtual  L_INT    LoadInfoCallBack(L_INT fd,pLOADINFO pInfo);

      virtual  L_INT    RedirectOpenCallBack(
                                             L_CHAR L_FAR *pFile,
                                             L_INT nMode,
                                             L_INT nShare
                                            );
      virtual  L_INT    RedirectCloseCallBack(L_INT FD);
      virtual  L_UINT   RedirectReadCallBack(
                                             L_INT FD,
                                             L_CHAR L_FAR *pBuf,
                                             L_INT nCount
                                            );
      virtual  L_UINT   RedirectWriteCallBack(
                                                L_INT FD,
                                                L_CHAR L_FAR *pBuf,
                                                L_INT nCount
                                             );
      virtual  L_INT32  RedirectSeekCallBack(
                                             L_INT FD,
                                             L_INT32 lnPos,
                                             L_INT nCount
                                            );

   protected:  
      LBitmapBase L_FAR*      m_pBitmap;
      LVectorBase L_FAR*      m_pVector;
      L_BOOL                  m_bEnableLoadInfoCB;
      L_BOOL                  m_bEnableRedirectIOCB;
      L_UINT                  m_uEnableFlags;

   public:
      LBaseFile();
      virtual ~LBaseFile();

      L_BOOL IsLoadInfoCallBackEnabled();
      L_BOOL EnableLoadInfoCallBack(L_BOOL bEnable);

      L_UINT GetRedirectIOFlags();
      L_VOID SetRedirectIOFlags(L_UINT uEnableFlags=IO_REDIRECT_ALL);
      L_BOOL IsRedirectIOEnabled();
      L_BOOL EnableRedirectIO(L_BOOL bEnable);

      L_VOID SetBitmap(LBitmapBase L_FAR* pBitmap);
      L_VOID SetVector(LVectorBase L_FAR* pVector);
      static L_INT GetDefaultLoadFileOption(pLOADFILEOPTION pLoadFileOption);
      static L_INT GetDefaultSaveFileOption(pSAVEFILEOPTION pSaveFileOption);
};

/*----------------------------------------------------------------------------+
| Class     : LFile                                                           |
| Desc      :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : 27 may 1998                                                     |
+----------------------------------------------------------------------------*/
class LWRP_EXPORT LFile : public LBaseFile
{
   LEAD_DECLAREOBJECT(LFile);

   public:
      L_VOID *m_extLFile;
      
   protected:  
     L_CHAR          m_szFileName[MAX_PATH+1];   
     L_BOOL          m_bFeedLoadStarted;
     LBitmapBase     m_FeedLoadBitmap;
     HGLOBAL         m_hFeedLoad;

   private:
      static L_INT  EXT_CALLBACK LoadFileTileCS(
                                    pFILEINFO  pFileInfo,
                                    pBITMAPHANDLE pBitmap,
                                    L_UCHAR  L_FAR * pBuffer,
                                    L_UINT  uFlags,
                                    L_INT  nRow,
                                    L_INT nLines,
                                    L_VOID L_FAR * pUserData
                                  );

      static L_INT  EXT_CALLBACK LoadFileCS(
                                 pFILEINFO pFileInfo,
                                 pBITMAPHANDLE pBitmap,
                                 L_UCHAR L_FAR * pBuffer,
                                 L_UINT  uFlags,
                                 L_INT  nRow,
                                 L_INT  nLines,
                                 L_VOID L_FAR* pUserData
                              );

      static L_INT  EXT_CALLBACK LoadFileOffsetCS(
                                       pFILEINFO pFileInfo,
                                       pBITMAPHANDLE pBitmap,
                                       L_UCHAR L_FAR* pBuffer,
                                       L_UINT uFlags,
                                       L_INT nRow,
                                       L_INT nLines,
                                       L_VOID L_FAR* pUserData
                                    );

      static L_INT  EXT_CALLBACK  FeedLoadCS(
                                 pFILEINFO pFileInfo,
                                 pBITMAPHANDLE pBitmap,
                                 L_UCHAR L_FAR * pBuffer, 
                                 L_UINT uFlags,L_INT nRow,
                                 L_INT nLines,
                                 L_VOID L_FAR * pUserData
                               );

      static L_INT  EXT_CALLBACK SaveFileOffsetCS(
                                       pBITMAPHANDLE pBitmap,
                                       L_UCHAR L_FAR* pBuffer,
                                       L_UINT uRow,
                                       L_UINT uLines,
                                       L_VOID L_FAR* pUserData
                                    );

      static L_INT  EXT_CALLBACK SaveFileCS(
                                 pBITMAPHANDLE pBitmap,
                                 L_UCHAR L_FAR * pBuffer,
                                 L_UINT uRow,
                                 L_UINT uLines,
                                 L_VOID L_FAR*  pUserData
                              );

      static L_INT  EXT_CALLBACK SaveFileTileCS(
                                    pBITMAPHANDLE pBitmap,
                                    L_UCHAR L_FAR * pBuffer,
                                    L_UINT uRow,
                                    L_UINT uLines,
                                    L_VOID L_FAR*  pUserData
                                  );

      static   L_INT  EXT_CALLBACK BrowseDirCS(
                                   pBITMAPHANDLE pBitmap,
                                   L_CHAR L_FAR * pszFilename,
                                   pFILEINFO pFileInfo,
                                   L_INT nStatus,
                                   L_INT nPercent,
                                   L_VOID L_FAR*  pUserData
                                 );

      static   L_INT  EXT_CALLBACK TransformFileCS(L_UINT uMarker,
                                                   L_UINT uMarkerSize,
                                                   L_UCHAR * pMarkerData,
                                                   L_VOID * pUserData,
                                                   L_UINT uTransform,
                                                   LEADMARKERCALLBACK pfnLEADCallback,
                                                   L_VOID * pLEADUserData);
   
   protected:     
      virtual    L_INT  LoadFileTileCallBack(
                                             pFILEINFO pFileInfo,
                                             LBitmapBase L_FAR* pLBitmap,
                                             LBuffer L_FAR* pLBuffer,
                                             L_UINT uFlags,
                                             L_INT nRow,
                                             L_INT nLines
                                            );

      virtual    L_INT  LoadFileCallBack(
                                          pFILEINFO pFileInfo,
                                          LBitmapBase L_FAR* pLBitmap,
                                          LBuffer L_FAR* pLBuffer,
                                          L_UINT uFlags,
                                          L_INT nRow,
                                          L_INT nLines
                                        );

      virtual    L_INT  LoadFileOffsetCallBack(
                                                pFILEINFO pFileInfo,
                                                LBitmapBase L_FAR* pLBitmap,
                                                LBuffer L_FAR* pLBuffer,
                                                L_UINT uFlags,
                                                L_INT nRow,
                                                L_INT nLines
                                              );

      virtual    L_INT  FeedLoadCallBack(
                                          pFILEINFO pFileInfo,
                                          LBitmapBase L_FAR* pLBitmap,
                                          LBuffer L_FAR* pLBuffer, 
                                          L_UINT uFlags,
                                          L_INT nRow,
                                          L_INT nLines
                                        );

      virtual    L_INT  SaveFileOffsetCallBack(
                                                LBitmapBase L_FAR* pLBitmap,
                                                LBuffer L_FAR* pLBuffer,
                                                L_UINT uRow,
                                                L_UINT uLines
                                              );

      virtual    L_INT  SaveFileCallBack(
                                          LBitmapBase L_FAR* pLBitmap,
                                          LBuffer L_FAR* pLBuffer,
                                          L_UINT uRow,
                                          L_UINT uLines
                                        );

      virtual    L_INT  SaveFileTileCallBack(
                                             LBitmapBase L_FAR* pLBitmap,
                                             LBuffer L_FAR* pLBuffer,
                                             L_UINT uRow,
                                             L_UINT uLines
                                           );

      virtual    L_INT  BrowseDirCallBack(
                                           LBitmapBase L_FAR* pLBitmap,
                                           L_CHAR L_FAR * pszFilename,
                                           pFILEINFO pFileInfo,
                                           L_INT nStatus,
                                           L_INT nPercent
                                         );

      virtual    L_INT  TransformFileCallBack(L_UINT uMarker,
                                              L_UINT uMarkerSize,
                                              L_UCHAR * pMarkerData,
                                              L_UINT uTransform,
                                              LEADMARKERCALLBACK pfnLEADCallback,
                                              L_VOID * pLEADUserData);

   public : 
      LFile();
      LFile(LBitmapBase L_FAR* pLBitmap);
      LFile(LBitmapBase L_FAR* pLBitmap,L_CHAR L_FAR* pFileName);
      virtual ~LFile();

      L_BOOL        IsValid();

      L_CHAR L_FAR* GetFileName();
      L_INT         GetFileName(L_CHAR L_FAR* pBuffer,L_UINT L_FAR* puBuffSize);
      L_VOID        SetFileName(L_CHAR L_FAR* pFileName);
      L_VOID        SetBitmap(LBitmapBase* pBitmap);

      virtual L_INT DeletePage(L_INT nPage,L_UINT uFlags=0,pSAVEFILEOPTION pSaveFileOption=NULL);
      virtual L_INT ReadLoadResolutions(
                                    pDIMENSION pDimensions,
                                    L_INT L_FAR* pDimensionCount,
                                    pLOADFILEOPTION pLoadFileOption=NULL
                                  );
      virtual L_INT ReadFileTransforms(   pFILETRANSFORMS pTransforms,
                                          pLOADFILEOPTION pLoadFileOption=NULL);
      virtual L_INT WriteFileTransforms(
                                          pFILETRANSFORMS pTransforms,
                                          L_INT  nFlags=0,
                                          pSAVEFILEOPTION pSaveFileOption=NULL
                                       );
      virtual L_INT StartFeedLoad(
                                    L_INT nBitsPerPixel=0,
                                    L_INT nOrder=ORDER_BGRORGRAY,
                                    L_UINT uFlags=LOADFILE_ALLOCATE|LOADFILE_STORE,
                                    pLOADFILEOPTION pLoadFileOption=NULL,
                                    pFILEINFO pFileInfo=NULL
                                    );
      virtual L_INT FeedLoad(LBuffer L_FAR* pLBuffer);
      virtual L_INT StopFeedLoad();  
      virtual L_INT GetInfo(
                              pFILEINFO pFileInfo,
                              L_UINT uFlags=FILEINFO_TOTALPAGES,
                              pLOADFILEOPTION pLoadFileOption=NULL
                           ); 
      virtual L_INT GetCommentSize( L_UINT uType,
                                    L_UINT L_FAR* puSize,
                                    pLOADFILEOPTION pLoadFileOption=NULL);
      virtual L_INT GetPCDResolution(pPCDINFO pPCDInfo);
      virtual L_INT LoadBitmap(
                                 L_INT nBitsPerPixel,
                                 L_INT nOrder,
                                 L_INT nPage,
                                 pFILEINFO pFileInfo = NULL
                              );     
      virtual L_INT LoadBitmap(
                                 L_INT nBitsPerPixel=0,
                                 L_INT nOrder=ORDER_BGRORGRAY,
                                 pLOADFILEOPTION pLoadFileOption = NULL,
                                 pFILEINFO pFileInfo = NULL
                              );

      virtual L_INT LoadBitmapResize(L_INT nDestWidth,
                                     L_INT nDestHeight,
                                     L_INT nDestBits,
                                     L_UINT32 uFlags,
                                     L_INT nOrder,
                                     pLOADFILEOPTION pLoadOptions,
                                     pFILEINFO pFileInfo);

      virtual L_INT LoadBitmapList(
                                    LBitmapList L_FAR* pLFileBitmapList,
                                    L_INT nBitsTo=0,
                                    L_INT nColorOrder=ORDER_BGRORGRAY,
                                    pLOADFILEOPTION pLoadFileOption = NULL,
                                    pFILEINFO pFileInfo = NULL
                                  );
      virtual L_INT LoadFile(
                              L_INT nBitsPerPixel,
                              L_INT nOrder,
                              L_UINT uFlags,
                              L_INT nPage,
                              pFILEINFO pFileInfo = NULL
                            );

      virtual L_INT LoadFile(
                              L_INT nBitsPerPixel=0,
                              L_INT nOrder=ORDER_BGRORGRAY,
                              L_UINT uFlags=LOADFILE_ALLOCATE | LOADFILE_STORE,
                              pLOADFILEOPTION pLoadFileOption = NULL,
                              pFILEINFO pFileInfo = NULL
                            );

      virtual L_INT LoadTile(
                              L_INT nCol,
                              L_INT nRow,
                              L_UINT uWidth,
                              L_UINT uHeight,
                              L_INT nBitsPerPixel=0,
                              L_INT nOrder=ORDER_BGRORGRAY, 
                              L_UINT uFlags=LOADFILE_ALLOCATE | LOADFILE_STORE,
                              pLOADFILEOPTION pLoadFileOption = NULL,
                              pFILEINFO pFileInfo = NULL
                            );
      virtual L_INT LoadOffset(
                                 L_INT fd,
                                 L_INT32 nOffsetBegin,
                                 L_INT32 nBytesToLoad,
                                 L_INT nBitsPerPixel=0,
                                 L_INT nOrder=ORDER_BGRORGRAY,
                                 L_UINT uFlags=LOADFILE_ALLOCATE|LOADFILE_STORE,
                                 pLOADFILEOPTION pLoadFileOption = NULL,
                                 pFILEINFO pFileInfo = NULL
                              );

      virtual L_INT LoadLayer(L_INT nBitsPerPixel,
                              L_INT nOrder,
                              L_INT nLayer,
                              pLAYERINFO pLayerInfo = NULL,
                              pLOADFILEOPTION pLoadOptions = NULL);


      virtual L_INT ReadComment( L_UINT uType,
                                 LBuffer L_FAR* pLBuffer,
                                 pLOADFILEOPTION pLoadFileOption = NULL);
      virtual L_INT ReadCommentExt(
                                    L_UINT uType,
                                    LPFILECOMMENTS  pComments,
                                    L_UCHAR L_HUGE* pBuffer,
                                    L_UINT L_FAR*   puLength,
                                    pLOADFILEOPTION pLoadFileOption = NULL
                                  );
      virtual L_INT ReadStamp(pLOADFILEOPTION pLoadFileOption = NULL); 
      virtual L_INT ReadTag(
                              L_UINT16 uTag,
                              L_UINT16 L_FAR* pType,
                              L_UINT32 L_FAR* pCount,
                              LBuffer L_FAR* pLBuffer,
                              pLOADFILEOPTION pLoadFileOption = NULL
                           ); 
      virtual L_INT SaveBitmap(
                                 L_INT nFormat,
                                 L_INT nBitsPerPixel,
                                 L_INT nQFactor,
                                 L_INT nPageNumber,
                                 L_UINT uFlags
                              );

        virtual L_INT SaveBitmap(
                                 L_INT nFormat,
                                 L_INT nBitsPerPixel=0,
                                 L_INT nQFactor=2,
                                 L_UINT uFlags=SAVE_OVERWRITE,
                                 pSAVEFILEOPTION pSaveFileOption = NULL
                              );

      virtual L_INT SaveBitmapList(
                                    LBitmapList L_FAR* pList,
                                    L_INT nFormat,
                                    L_INT nBits=0,
                                    L_INT nQFactor=2,
                                    pSAVEFILEOPTION pSaveFileOption = NULL
                                  );
      virtual L_INT SaveFile(
                              L_INT nFormat,
                              L_INT nBitsPerPixel=0,
                              L_INT nQFactor=2,
                              L_UINT uFlags=0,
                              pSAVEFILEOPTION pSaveFileOption = NULL
                            );
      virtual L_INT SaveOffset(
                                 L_INT fd,
                                 L_INT32 nOffsetBegin,
                                 L_INT32 L_FAR* pnSizeWritten,
                                 L_INT nFormat,
                                 L_INT nBitsPerPixel=0,
                                 L_INT nQFactor=2, 
                                 L_INT uFlags=0,
                                 pSAVEFILEOPTION pSaveFileOption = NULL
                              );
      virtual L_INT SaveTile( L_INT nCol,
                              L_INT nRow,
                              pSAVEFILEOPTION pSaveFileOption = NULL
                              );

      virtual L_INT SaveBitmapWithLayers(L_INT nFormat,
                                         L_INT nBitsPerPixel,
                                         L_INT nQFactor,
                                         LBitmapList * pLayers,
                                         pLAYERINFO pLayerInfo = NULL,
                                         L_INT nLayers = 0,
                                         pSAVEFILEOPTION pSaveOptions = NULL);

      virtual L_INT WriteComment(
                                    L_UINT uType,
                                    LPFILECOMMENTS  pComments,
                                    pSAVEFILEOPTION pSaveFileOption = NULL
                                );

      virtual L_INT z001WriteFileComment(pSAVEFILEOPTION pSaveFileOption=NULL);



      virtual L_INT WriteStamp(pSAVEFILEOPTION pSaveFileOption = NULL);
      static  L_INT FileConvert(
                                 L_CHAR L_FAR * pszFileDst,
                                 L_CHAR L_FAR * pszFileSrc,
                                 L_INT nType,
                                 L_INT nWidth,
                                 L_INT nHeight,
                                 L_INT nBitsPerPixel,
                                 L_INT nQFactor,
                                 pLOADFILEOPTION pLoadFileOption = NULL,
                                 pSAVEFILEOPTION pSaveFileOption = NULL,
                                 pFILEINFO pFileInfo = NULL
                               );
      static  L_INT GetProperQualityFactor(L_INT nFileFormat);
      virtual L_INT BrowseDir( L_CHAR L_FAR* pszPath,
                               L_CHAR L_FAR* pszFilter,
                               L_INT nThumbWidth=80,
                               L_INT nThumbHeight=80,
                               L_INT nBits=24,
                               L_UINT32 uCRFlags=CRF_BYTEORDERBGR|CRF_FIXEDPALETTE|CRF_FLOYDSTEINDITHERING,
                               L_BOOL bMaintainAspect=TRUE,
                               L_BOOL bForceSize=FALSE,
                               COLORREF crBackColor=RGB(128,128,128),
                               L_BOOL bLoadStamp=FALSE,
                               L_BOOL bResample=FALSE,
                               L_BOOL bStopOnError=FALSE,
                               L_BOOL bIncludeSubDirs=FALSE,
                               L_BOOL bExpandMultipage=FALSE,
                               L_INT32 lSizeDisk=0,
                               L_INT32 lSizeMem=0);

      virtual L_INT ReadFileExtensions(pEXTENSIONLIST * ppExtensionList,
                                       pLOADFILEOPTION pLoadOptions = NULL);

      virtual L_INT FreeExtensions(pEXTENSIONLIST pExtensionList);

      virtual L_INT LoadExtensionStamp(pEXTENSIONLIST pExtensionList);

      virtual L_INT GetExtensionAudio(pEXTENSIONLIST pExtensionList,
                                      L_INT nStream,
                                      L_CHAR ** ppBuffer,
                                      L_UINT * puSize);

      virtual L_INT TransformFile(L_CHAR * pszFileDst,
                                  L_UINT uTransform,
                                  pLOADFILEOPTION pLoadOptions = NULL);
};

/*----------------------------------------------------------------------------+
| Class     : LMemoryFile                                                     |
| Desc      :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : 27 may 1998                                                     |
+----------------------------------------------------------------------------*/
class LWRP_EXPORT LMemoryFile :public LBaseFile
{
   LEAD_DECLAREOBJECT(LMemoryFile);

   public:
      L_VOID *m_extLMemoryFile;
      LBuffer * m_pLSaveBuffer;  // For the callback functionality of SaveBitmapBuffer and SaveFileBuffer
      
   private:  
      LBuffer     LCompressOutputBuffer;
      L_BOOL      bCompressStarted;

   private:  

      static L_INT  EXT_CALLBACK LoadMemoryCS(
                                    pFILEINFO pFileInfo,
                                    pBITMAPHANDLE pBitmap,
                                    L_UCHAR L_FAR *pBuffer,
                                    L_UINT uFlags,
                                    L_INT nRow,
                                    L_INT nLines,
                                    L_VOID L_FAR *pUserData
                                );

      static L_INT  EXT_CALLBACK CompressBufferCS(
                                       pBITMAPHANDLE pBitmap,
                                       L_UCHAR L_FAR * pBuffer,
                                       L_UINT uBytes,
                                       L_VOID L_FAR * pUserData
                                    );

      static L_INT EXT_CALLBACK SaveBitmapBufferCS(L_UINT32 uRequiredSize,
                                      L_UCHAR ** ppBuffer,
                                      L_UINT32 * pdwBufferSize,
                                      L_VOID * pUserData);

      static L_INT EXT_CALLBACK SaveFileBufferCS(L_UINT32 uRequiredSize,
                                    L_UCHAR ** ppBuffer,
                                    L_UINT32 * pdwBufferSize,
                                    L_VOID * pUserData);

      static L_INT EXT_CALLBACK SaveFileCS(pBITMAPHANDLE pBitmap,
                              L_UCHAR * pBuffer,
                              L_UINT uRow,
                              L_UINT uLines,
                              L_VOID * pUserData);

   protected : 

      virtual L_INT LoadMemoryCallBack(
                                          pFILEINFO pFileInfo,
                                          LBitmapBase L_FAR* pLBitmap,
                                          LBuffer L_FAR* pLBuffer,
                                          L_UINT uFlags,
                                          L_INT nRow,
                                          L_INT nLines
                                      );

      virtual L_INT CompressBufferCallBack(
                                             LBitmapBase L_FAR* pLBitmap,
                                             LBuffer L_FAR* pLBuffer
                                          );

      virtual L_INT SaveBitmapBufferCallBack(LBuffer * pLBuffer, L_UINT32 uRequiredSize);
      
      virtual L_INT SaveFileBufferCallBack(LBuffer * pLBuffer, L_UINT32 uRequiredSize);

      virtual L_INT SaveFileCallBack(LBitmapBase * pLBitmap,
                                     LBuffer * pLBuffer,
                                     L_UINT uRow,
                                     L_UINT uLines);

   public : 
      LMemoryFile();
      LMemoryFile(LBitmapBase L_FAR* pBitmap);
      virtual ~LMemoryFile();

      L_BOOL  IsValid();

      virtual L_INT  GetInfo(
                                    LBuffer& LMemoryBuffer,
                                    pFILEINFO pFileInfo,
                                    L_UINT uFlags=FILEINFO_TOTALPAGES,
                                    pLOADFILEOPTION pLoadFileOption = NULL
                                   );
      virtual L_INT  LoadBitmap(
                                       LBuffer& LMemoryBuffer,
                                       L_INT nBitsPerPixel=0,
                                       L_INT nOrder=ORDER_BGRORGRAY,
                                       pLOADFILEOPTION pLoadFileOption = NULL,
                                       pFILEINFO pFileInfo = NULL
                                     );
      virtual L_INT  LoadMemory(
                                 LBuffer& LMemoryBuffer,
                                 L_INT nBitsPerPixel=0,
                                 L_INT nOrder=ORDER_BGRORGRAY,
                                 L_UINT uFlags=LOADFILE_ALLOCATE|LOADFILE_STORE,
                                 pLOADFILEOPTION pLoadFileOption = NULL,
                                 pFILEINFO pFileInfo = NULL
                               );
      virtual L_INT  ReadComment(
                                 LBuffer& LMemoryBuffer,
                                 LBuffer L_FAR* pLCommentBuffer,
                                 L_UINT uType,
                                 pLOADFILEOPTION pLoadFileOption = NULL
                              );
      virtual L_INT32  ReadTag(
                                 LBuffer& LMemoryBuffer,
                                 LBuffer L_FAR* pLTagDataBuffer,
                                 L_UINT16 uTag,
                                 L_UINT16 L_FAR* pType,
                                 L_UINT32 L_FAR* pCount,
                                 pLOADFILEOPTION pLoadFileOption = NULL
                               );
      virtual L_INT SaveBitmap(
                                 LBuffer L_FAR* pLMemoryBuffer,
                                 L_INT nFormat,
                                 L_INT nBitsPerPixel=0,
                                 L_INT nQFactor=2,
                                 pSAVEFILEOPTION pSaveFileOption = NULL
                              );

      virtual L_INT SaveBitmapBuffer(LBuffer * pLBuffer,
                                     L_UINT32 * puFileSize,
                                     L_INT nFormat,
                                     L_INT nBitsPerPixel,
                                     L_INT nQFactor,
                                     pSAVEFILEOPTION pSaveOptions);

      virtual L_INT SaveFileBuffer(LBuffer * pLBuffer,
                                   L_UINT32 * puFileSize,
                                   L_INT nFormat,
                                   L_INT nBitsPerPixel,
                                   L_INT nQFactor,
                                   L_UINT uFlags,
                                   pSAVEFILEOPTION pSaveOptions);

      virtual L_INT StartCompressBuffer(
                                          L_UINT32 uInputBytes,
                                          L_UINT uOutputBytes,
                                          L_INT nOutputType,
                                          L_INT nQFactor=2,
                                          pSAVEFILEOPTION pSaveFileOption = NULL
                                       );
      virtual L_INT CompressBuffer(LBuffer L_FAR* pLBuffer); 
      virtual L_INT EndCompressBuffer();  
};

#endif //_LEAD_FILE_H_
/*================================================================= EOF =====*/
