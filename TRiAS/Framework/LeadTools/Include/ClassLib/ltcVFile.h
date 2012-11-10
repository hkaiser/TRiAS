/*----------------------------------------------------------------------------+
| LEADTOOLS for Windows -                                                     |
| Copyright (c) 1991-2000 LEAD Technologies, Inc.                             |
| All Rights Reserved.                                                        |
|-----------------------------------------------------------------------------|
| PROJECT   : LEAD wrappers                                                   |
| FILE NAME : ltcVFile.h                                                      |
| DESC      :                                                                 |
+----------------------------------------------------------------------------*/
#ifndef  _LEAD_VECTOR_FILE_H_
#define  _LEAD_VECTOR_FILE_H_

/*----------------------------------------------------------------------------+
| Class     : LVectorFile                                                     |
| Desc      :                                                                 |
| Return    :                                                                 | 
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+*/
class LWRP_EXPORT LVectorFile : public LBaseFile
{
   LEAD_DECLAREOBJECT(LVectorFile);
   protected:  
     L_CHAR          m_szFileName[MAX_PATH+1];   
     L_BOOL          m_bFeedLoadStarted;
     LVectorBase     m_FeedLoadVector;
     HGLOBAL         m_hFeedLoad;

   public : 
      LVectorFile();
      LVectorFile(LVectorBase L_FAR* pLVector);
      LVectorFile(LVectorBase L_FAR* pLVector,L_CHAR L_FAR* pFileName);
      virtual ~LVectorFile();

      L_BOOL        IsValid();

      const L_CHAR L_FAR* GetFileName();
      L_INT         GetFileName(L_CHAR L_FAR* pBuffer,L_UINT L_FAR* puBuffSize);
      L_VOID        SetFileName(L_CHAR L_FAR* pFileName);
      L_VOID        SetVector(LVectorBase* pVector);

      /* new */
      virtual L_INT LoadFile( pLOADFILEOPTION pLoadOptions = NULL,
                              pFILEINFO pFileInfo = NULL);
      virtual L_INT StartFeedLoad(
                                 pLOADFILEOPTION pLoadFileOption=NULL,
                                 pFILEINFO pFileInfo = NULL
                                 );

      virtual L_INT FeedLoad(LBuffer L_FAR* pLBuffer);
      virtual L_INT StopFeedLoad(); 
      
      virtual L_INT SaveFile(
                              L_INT nFormat,
                              pSAVEFILEOPTION pSaveFileOption = NULL
                            );

};
#endif  _LEAD_VECTOR_FILE_H_

