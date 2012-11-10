/*----------------------------------------------------------------------------+
| LEADTOOLS for Windows -                                                     |
| Copyright (c) 1991-2000 LEAD Technologies, Inc.                             |
| All Rights Reserved.                                                        |
|-----------------------------------------------------------------------------|
| PROJECT   : LEAD wrappers                                                   |
| FILE NAME : ltcVMfil.h                                                      |
| DESC      :                                                                 |
+----------------------------------------------------------------------------*/
#ifndef  _LEAD_VECTOR_MEMORY_FILE_H_
#define  _LEAD_VECTOR_MEMORY_FILE_H_

/*----------------------------------------------------------------------------+
| Class     : LVectorMemoryFile                                               |
| Desc      :                                                                 |
| Return    :                                                                 | 
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+*/
class LWRP_EXPORT LVectorMemoryFile :public LBaseFile
{
   LEAD_DECLAREOBJECT(LVectorMemoryFile);

   public : 
      LVectorMemoryFile();
      LVectorMemoryFile(LVectorBase L_FAR* pVector);
      virtual ~LVectorMemoryFile();

      L_BOOL  IsValid();

      virtual L_INT  LoadMemory(
                                 LBuffer& LMemoryBuffer,
                                 pLOADFILEOPTION pLoadFileOption = NULL,
                                 pFILEINFO pFileInfo = NULL
                               );

      virtual L_INT SaveMemory(
                                 LBuffer L_FAR* pLMemoryBuffer,
                                 L_INT nFormat,
                                 pSAVEFILEOPTION pSaveFileOption = NULL
                              );
};

#endif //_LEAD_VECTOR_MEMORY_FILE_H_

