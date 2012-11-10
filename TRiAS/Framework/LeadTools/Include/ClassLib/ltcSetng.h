/*----------------------------------------------------------------------------+
| LEADTOOLS for Windows -                                                     |
| Copyright (c) 1991-2000 LEAD Technologies, Inc.                             |
| All Rights Reserved.                                                        |
|-----------------------------------------------------------------------------|
| PROJECT   : LEAD wrappers                                                   |
| FILE NAME : ltcsetng.h                                                      |
| DESC      :                                                                 |
+----------------------------------------------------------------------------*/

#ifndef  _LEAD_SETTINGS_H_
#define  _LEAD_SETTINGS_H_

/*----------------------------------------------------------------------------+
| CLASSES DECLARATION                                                         |
+----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------+
| Class     : LSettings                                                       |
| Desc      :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : September 1998                                                  |
+----------------------------------------------------------------------------*/
class LWRP_EXPORT LSettings :public LBase 
{
   LEAD_DECLAREOBJECT(LSettings);

   public:
      L_VOID *m_extLSettings;
      
   public : 
      LSettings();
      virtual ~LSettings();

      static L_BOOL           IsSupportLocked(L_UINT uType);   
      static L_VOID           UnlockSupport(L_UINT uType,L_CHAR L_FAR * pKey);
};

/*----------------------------------------------------------------------------+
| Class     : LFileSetting                                                    |
| Desc      :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : 26 may 1998                                                     |
+----------------------------------------------------------------------------*/
class LWRP_EXPORT LFileSettings: public LSettings
{
   LEAD_DECLAREOBJECT(LFileSettings);

   public:
      L_VOID *m_extLFileSettings;
      
   public : 
      LFileSettings();
      virtual ~LFileSettings();

      static L_INT   GetWMFResolution(L_INT L_FAR * lpResolution);  
      static L_INT   SetWMFResolution(L_INT nResolution);  
      static L_INT   IgnoreFilters(L_CHAR L_FAR * pszFilters); 
      static L_INT   GetPCDResolution(L_CHAR L_FAR * pszFile, pPCDINFO pPCDInfo);  
      static L_INT   SetPCDResolution(L_INT nResolution);  

      static L_INT   PreLoadFilters(
                                    L_INT nFixedFilters,
                                    L_INT nCachedFilters,
                                    L_CHAR L_FAR* pszFilters
                                   );  
      static L_INT   GetComment(
                                 L_UINT uType,
                                 L_UCHAR L_FAR * pComment,
                                 L_UINT uLength
                               ); 
      static L_INT   SetComment(
                                 L_UINT uType,
                                 L_UCHAR L_FAR * pComment,
                                 L_UINT  uLength
                               );  
      static L_INT   GetLoadResolution(
                                    L_INT nFormat,
                                    L_UINT32 L_FAR * pWidth,
                                    L_UINT32 L_FAR * pHeight,
                                    pLOADFILEOPTION pLoadFileOption=NULL
                                 ); 
      static L_INT   SetLoadResolution(
                                    L_INT nFormat,
                                    L_UINT32  nWidth,
                                    L_UINT32 nHeight
                                 );  
      static L_INT32 GetTag(
                              L_UINT16 uTag,
                              L_UINT16 L_FAR * pType,
                              L_UINT32 L_FAR * pCount,
                              L_VOID L_FAR *  pData
                           );  
      static L_INT   SetTag(
                              L_UINT16 uTag,
                              L_UINT16 uType,
                              L_UINT32  uCount,
                              L_VOID L_FAR * pData
                           );  

      static L_INT  SetSaveResolution (L_UINT uCount, 
                                       pDIMENSION pResolutions);

      static L_INT GetSaveResolution (L_UINT L_FAR* puCount, pDIMENSION pResolutions);

      static L_INT SetViewport2D(L_INT nWidth, L_INT nHeight);
      static L_INT GetViewport2D(L_INT L_FAR*pnWidth,L_INT L_FAR*pnHeight);
      static L_INT SetViewMode2D(L_INT nViewMode);
      static L_INT GetViewMode2D();

      static L_INT GetJ2KOptions( pFILEJ2KOPTIONS pOptions, L_INT nSize );
      static L_INT GetDefaultJ2KOptions( pFILEJ2KOPTIONS pOptions, L_INT nSize );
      static L_INT SetJ2KOptions( const pFILEJ2KOPTIONS pOptions);
      
};

/*----------------------------------------------------------------------------+
| Class     : LBitmapSetting                                                  |
| Desc      :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : 26 may 1998                                                     |
+----------------------------------------------------------------------------*/
class LWRP_EXPORT LBitmapSettings: public LSettings
{
   LEAD_DECLAREOBJECT(LBitmapSettings);

   public:
      L_VOID *m_extLBitmapSettings;
      
   public : 
      LBitmapSettings();
      virtual ~LBitmapSettings();

      static L_INT            DefaultDithering(L_UINT uMethod);  
      static L_UINT32         GetDisplayMode();       
      static L_UINT32         SetDisplayMode(
                                             L_UINT32 uFlagPos,
                                             L_UINT32 uFlagSet
                                            );      
      static L_INT            FreeUserMatchTable(L_UINT L_FAR * pTable); 
      static L_UINT L_FAR *   SetUserMatchTable(L_UINT L_FAR * pTable);  
      static L_UINT L_FAR *   CreateUserMatchTable(
                                                   LPRGBQUAD pPalette,
                                                   L_UINT uColors
                                                  ); 
};      

#endif //_LEAD_SETTINGS_H_
/*================================================================= EOF =====*/
