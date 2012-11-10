/*----------------------------------------------------------------------------+
| LEADTOOLS for Windows -                                                     |
| Copyright (c) 1991-2000 LEAD Technologies, Inc.                             |
| All Rights Reserved.                                                        |
|-----------------------------------------------------------------------------|
| PROJECT   : LEAD wrappers                                                   |
| FILE NAME : ltcHttp.h                                                       |
| DESC      :                                                                 |
+----------------------------------------------------------------------------*/

#ifndef _LEAD_INET_HTTP_H_
#define _LEAD_INET_HTTP_H_

class LInetHttp;
/*----------------------------------------------------------------------------+
| Class     : LInetHttp                                                       |
| Desc      :                                                                 |
| Return    :                                                                 | 
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : August 2000                                                     |
+----------------------------------------------------------------------------*/
//-----------------------------------------------------------------------------
class LWRP_EXPORT LInetHttp : public LBase
//-----------------------------------------------------------------------------
{
   LEAD_DECLAREOBJECT(LInetHttp);

// Data Members
private:

   HINET          m_hInetHttp;
   L_BOOL         m_bOpenReq;

// Member Functions
public:
            LInetHttp();
            LInetHttp(L_CHAR L_FAR *pszServer, L_CHAR L_FAR *pszUserName = NULL, L_CHAR L_FAR *pszPassword = NULL,
                      L_INT nPort = 80);

   virtual  ~LInetHttp();
   L_INT    Connect(L_CHAR L_FAR *pszServer, L_CHAR L_FAR *pszUserName = NULL, L_CHAR L_FAR *pszPassword = NULL,
                    L_INT nPort = 80);

   L_VOID   Disconnect();
   L_INT    OpenRequest(L_UINT uType, L_CHAR L_FAR *pszTarget, L_UINT dwFlags = 0, L_CHAR L_FAR *pszReferer = NULL,
                        L_CHAR L_FAR *pszVersion = NULL);

   L_VOID   CloseRequest();
   L_INT    SendBitmap(LBitmapBase *pBitmapBase, L_INT nFormat, L_INT nQFactor, L_CHAR L_FAR *pszContentType,
                       pNAMEVALUE pNameValue, pSAVEFILEOPTION pSaveFileOption = NULL);

   L_INT    SendBitmap(pBITMAPHANDLE pBitmap, L_INT nFormat, L_INT nBitsPerPixel, L_INT nQFactor,
                       L_CHAR L_FAR *pszContentType, pNAMEVALUE pNameValue, pSAVEFILEOPTION pSaveFileOption = NULL);

   L_INT    SendData(LBuffer *pData, L_CHAR L_FAR *pszContentType, pNAMEVALUE pNameValue);
   L_INT    SendData(L_CHAR L_FAR *pszData, L_UINT uSize, L_CHAR L_FAR *pszContentType, pNAMEVALUE pNameValue);
   L_INT    SendForm(pNAMEVALUE pNameValue, L_UINT uCount);
   L_INT    SendRequest(L_CHAR L_FAR *pszHeader, L_UINT32 ulHeaderSize, L_CHAR L_FAR *pszOptional,
                        L_UINT32 ulOptionalSize);
   
   L_INT    GetResponse(LBuffer *pData);
   L_UINT   GetServerStatus();
};

#endif //_LEAD_INET_HTTP_H_
/*================================================================= EOF =====*/
