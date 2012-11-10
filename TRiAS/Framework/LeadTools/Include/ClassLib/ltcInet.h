/*----------------------------------------------------------------------------+
| LEADTOOLS for Windows -                                                     |
| Copyright (c) 1991-2000 LEAD Technologies, Inc.                             |
| All Rights Reserved.                                                        |
|-----------------------------------------------------------------------------|
| PROJECT   : LEAD wrappers                                                   |
| FILE NAME : ltcInet.h                                                       |
| DESC      :                                                                 |
+----------------------------------------------------------------------------*/

#ifndef _LEAD_INET_CAPTURE_H_
#define _LEAD_INET_CAPTURE_H_

/************************************************************************************
 *                                                                                  *
 *                            CONNECTION LIST FLAGS                                 *
 *                                                                                  *
 ************************************************************************************/

#define  COMPUTER_DESC     0x0001           /* Description column only  */
#define  COMPUTER_ADDRESS  0x0002           /* Address column only      */

#define  SERVER            0x0001           /* Server type */
#define  CLIENT            0x0002           /* Client type */

#include "commctrl.h"
#include "ltcDictn.h"
//#include "ltcMmcp.h"

/*----------------------------------------------------------------------------+
| FORWARDS                                                                     |
+----------------------------------------------------------------------------*/
class LInetPacket;

/*----------------------------------------------------------------------------+
| DEFINES                                                                     |
+----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------+
| CLASSES DECLARATION                                                         |
+----------------------------------------------------------------------------*/
class LInet;
/*----------------------------------------------------------------------------+
| Class     : LInet                                                           |
| Desc      :                                                                 |
| Return    :                                                                 | 
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : June 1999                                                       |
+----------------------------------------------------------------------------*/
//-----------------------------------------------------------------------------
class LWRP_EXPORT LInet : public LBase
//-----------------------------------------------------------------------------
{
   LEAD_DECLAREOBJECT(LInet);

   public:
      L_VOID *m_extLInet;

private:   
   static   L_UINT   m_uStartedCount;
   static   HICON    m_hDefSrvIcon;
   static   HICON    m_hDefClnIcon;

   L_BOOL            m_bStarted;
   L_BOOL            m_bAutoWnd;
   L_BOOL            m_bEnableAutoProcess;
   L_UINT            m_uType;
   L_UINT            m_uColumns;
   HTREEITEM         m_hRemoteItem;
   HTREEITEM         m_hTreeServer;
   HTREEITEM         m_hTreeClient;
   HWND              m_hCtrlWnd;
   HICON             m_hTempSrvIcon;
   HICON             m_hTempClnIcon;
   LDictionary       m_ConnectionList;
//   LMMCapture        m_MMCapture;
   L_CHAR L_FAR      *m_pszName;
   L_CHAR L_FAR      *m_pszIP;
   L_BOOL            m_bWndItem;
   LPWAVEFORMATDATA  m_pRemoteWaveFormat;
   LPWAVEFORMATDATA  m_pBadWaveFormat;
   L_UINT32          m_uWaveFormatSize;
   L_UINT32          m_uBadWaveFormatSize;

protected:
   L_COMP            m_hComputer;
   L_COMP            m_hServer;
   HWND              m_hImgWnd;

public:
   L_VOID            *m_pUserDataEx;

private:
   L_BOOL            IsServer();
   L_VOID            FillWnd(L_UINT uColumns);
   L_VOID            FillIcon(HICON hSrvIcon, HICON hClnIcon);
   L_VOID            InsertInWnd(HTREEITEM hOrder, LInet L_FAR *plRemoteComp);
   L_VOID            RemoveFromWnd(HTREEITEM hOrder);
   L_UINT            GetType();
   L_INT             SetHandle(L_COMP hComputer);
   L_VOID            CloseServers(L_BOOL bGraceful);
   L_VOID            CloseClients(L_BOOL bGraceful);
   L_INT             PrepareTree();


   static   L_INT EXT_CALLBACK InetCS(L_COMP hConnection, L_INT nMessage, L_INT nError,
                         L_CHAR L_FAR *pBuffer, L_UINT32 ulSize, L_VOID L_FAR *pUserData);

   static   L_VOID EXT_CALLBACK CommandCS(
      L_COMP      hComputer,   
      CMDTYPE     uCommand,
      L_UINT      uCommandID,
      L_INT       nError,
      L_UINT      uParams, 
      pPARAMETER  pParams, 
      L_UINT      uExtra,
      L_CHAR L_FAR*pExtra,
      L_VOID L_FAR*pUserData
      );

   static L_VOID EXT_CALLBACK ResponseCS(
   L_COMP      hComputer,
   CMDTYPE     uCommand,
   L_UINT      uCommandID,
   L_INT       nError,
   L_INT       nStatus,
   L_UINT      uParams, 
   pPARAMETER  pParams, 
   L_UINT      uExtra, 
   L_CHAR L_FAR*pExtra,
   L_VOID L_FAR*pUserData
);


protected:
   virtual  L_INT OnConnect(LInet L_FAR *plConnection, L_INT nError);
   virtual  L_INT OnDataReady(LInet L_FAR *plConnection, L_INT nError, L_CHAR L_FAR *pBuffer, L_UINT32 ulSize);
   virtual  L_INT OnClose(LInet L_FAR *plConnection, L_INT nError);
   virtual  L_INT OnConnectRequest(LInet L_FAR *plConnection, L_INT nError);
   virtual  L_INT OnDataSent(LInet L_FAR *plConnection, L_INT nError);
   virtual  L_INT OnDataSending(LInet L_FAR *plConnection, L_INT nError);
   virtual  L_INT OnDataStart(LInet L_FAR *plConnection, L_INT nError);
   virtual  L_INT OnDataReceiving(LInet L_FAR *plConnection, L_INT nError, L_CHAR L_FAR *pBuffer, L_UINT32 ulSize);
   virtual  L_INT OnImageReceived(LInet L_FAR *plConnection, L_INT nError, LBitmapBase L_FAR *pBitmap);
//   virtual  L_INT OnMMediaReceived(LInet L_FAR *plConnection, L_INT nError, LMultimedia L_FAR *pMedia);
//   virtual  L_INT OnSoundReceived(LInet L_FAR *plConnection, L_INT nError,
//                                  LPWAVEFORMATDATA pWaveFormatData, L_UINT32 ulWaveFormatSize,
//                                  LPWAVEDATA pWaveData);
   virtual  L_INT OnUser1Received(LInet L_FAR *plConnection, L_INT nError, L_CHAR L_FAR *pBuffer, L_UINT32 ulSize);
   virtual  L_INT OnUser2Received(LInet L_FAR *plConnection, L_INT nError, L_CHAR L_FAR *pBuffer, L_UINT32 ulSize);
   virtual  L_INT OnUser3Received(LInet L_FAR *plConnection, L_INT nError, L_CHAR L_FAR *pBuffer, L_UINT32 ulSize);
   virtual  L_INT OnUser4Received(LInet L_FAR *plConnection, L_INT nError, L_CHAR L_FAR *pBuffer, L_UINT32 ulSize);

   virtual  L_INT CommandCallBack(LInet L_FAR * plConnection,
                                  CMDTYPE     uCommand,
                                  L_UINT      uCommandID,
                                  L_INT       nError,
                                  L_UINT      uParams, 
                                  pPARAMETER  pParams, 
                                  L_UINT      uExtra,
                                  L_CHAR L_FAR*pExtra);

   virtual L_INT ResponseCallBack(LInet L_FAR * plConnection,
                                  CMDTYPE     uCommand,
                                  L_UINT      uCommandID,
                                  L_INT       nError,
                                  L_INT       nStatus,
                                  L_UINT      uParams, 
                                  pPARAMETER  pParams, 
                                  L_UINT      uExtra,
                                  L_CHAR L_FAR*pExtra);
   
public:
   LInet();
   virtual        ~LInet();
   LInet&         operator=(LInet& LInetSrc);
   virtual  L_INT Connect(const L_CHAR L_FAR *pszAddress, L_INT nPort);
   virtual  L_INT Close(LInet L_FAR *plRemoteComp, L_BOOL bGraceful = FALSE);
   virtual  L_INT AcceptConnect(LInet L_FAR *plRemoteComp);
   virtual  L_INT ServerInit(L_INT nPort);
   virtual  L_INT ServerShutdown();
   L_INT CloseAll(L_UINT uType = SERVER | CLIENT, L_BOOL bGraceful = FALSE);
   L_CHAR   L_FAR *GetHostName(L_INT nType = HOST_NAME_DESCRP);
   L_INT    StartUp (L_VOID);
   L_INT    ShutDown(L_VOID);
   L_INT    EnableAutoProcess(L_BOOL bProcess = TRUE);
   L_BOOL   IsAutoProcessEnabled();
   L_INT    ReadData(LInet L_FAR *plRemoteComp, L_CHAR L_FAR *pBuffer, L_UINT32 L_FAR *pulBufferLength);
   L_INT    SendBitmap(LInet L_FAR *plRemoteComp, pBITMAPHANDLE phBitmap, L_INT nFormat, L_INT nBitsPerPixel,
      L_INT nQFactor, L_UINT32 L_FAR *pulImageLength);
   L_INT    SendData(LInet L_FAR *plRemoteComp, L_CHAR L_FAR *pBuffer, L_UINT32 L_FAR *pulBufferLength, IDATATYPE uDataType);
   L_INT    SendMMData(LInet L_FAR *plRemoteComp, L_CHAR L_FAR *pBuffer, L_UINT32 L_FAR *pulBufferLength);
   L_INT    SendRawData(LInet L_FAR *plRemoteComp, L_CHAR L_FAR *pBuffer, L_UINT32 L_FAR *pulBufferLength);
   L_INT    SendSound(LInet L_FAR *plRemoteComp, LPWAVEFORMATDATA pWaveFormatData, LPWAVEDATA pWaveData,
      L_UINT32 L_FAR *puldwDataSize);
   L_UINT32 GetQueueSize();
   L_INT    ClearQueue();
   L_COMP   L_FAR *GetHandle();
   L_BOOL   IsValid();
   L_INT    ExistsItem(LInet L_FAR *plRemoteComp);
   LInet L_FAR *GetItem(L_INT uIndex);
   LInet L_FAR *GetItem(L_COMP* phComputer);
   LInet L_FAR *GetFirstItem(LInet L_FAR *plRemoteComp = NULL);
   LInet L_FAR *GetLastItem(LInet L_FAR *plRemoteComp = NULL);
   LInet L_FAR *GetNextItem(LInet L_FAR *plRemoteComp, L_BOOL bByType = FALSE);
   LInet L_FAR *GetPrevItem(LInet L_FAR *plRemoteComp, L_BOOL bByType = FALSE);
   L_UINT   GetItemsCount();
   L_INT    CreateWnd(HWND hParentWnd, pCONLISTOPTIONS pOptions, L_INT nID = 0,
      L_UINT32 uStyles = WS_VISIBLE, L_INT nX = 0, L_INT nY = 0,
      L_INT nCx = 320, L_INT nCy = 200);
   L_VOID   DestroyWnd();
   L_INT    ExpandWnd(L_BOOL bFlag = TRUE);
   L_BOOL   AddWndItem(LInet L_FAR *plRemoteComp);
   L_VOID   EnableAutoWnd(L_BOOL bFlag = TRUE);
   L_BOOL   IsAutoWndEnabled();
   L_VOID   RemoveWndItem(LInet L_FAR *plRemoteComp);
   L_VOID   RemoveAllWndItems();
   L_BOOL   IsWndItem(LInet L_FAR *plConnection);
   L_VOID   SetImageWindow(HWND hWnd);
   
   //Version 12 functions
   L_INT    SendCmd( 
      LInet L_FAR *plRemoteComp, 
      CMDTYPE uCommand,
      L_UINT uCommandID,
      LInetPacket *pInetPacket=NULL
      );
   
   L_INT    SendRsp(
      LInet L_FAR *plRemoteComp, 
      CMDTYPE uCommand,
      L_UINT uCommandID,
      LInetPacket *pInetPacket,
      L_INT nStatus);
   
   L_INT    SendLoadCmd(
      LInet L_FAR *plRemoteComp,
      L_UINT uCommandID,
      L_CHAR L_FAR*pszFile,
      L_INT nBitsPerPixel = 0,
      L_INT nOrder = ORDER_BGR,
      L_UINT uFlags = LOADFILE_ALLOCATE|LOADFILE_STORE);
   
   L_INT    SendLoadRsp(
      LInet L_FAR *plRemoteComp,
      L_UINT uCommandID,
      L_UINT uBitmapID,
      L_UINT uExtra,
      L_CHAR L_FAR*pExtra,
      L_INT nStatus);
   
   L_INT  SendCreateWinCmd(
      LInet L_FAR *plRemoteComp,
      L_UINT uCommandID,
      L_CHAR L_FAR*pszClassName,
      L_CHAR L_FAR*pszWindowName,
      L_UINT ulFlags,
      L_INT nLeft,
      L_INT nTop,
      L_INT nWidth, 
      L_INT nHeight,
      L_UINT uParentID);
   
   L_INT  SendCreateWinRsp(
      LInet L_FAR *plRemoteComp,
      L_UINT uCommandID,
      L_UINT uWindowID,
      L_UINT uLength,
      L_CHAR L_FAR*pExtraInfo,
      L_INT nStatus);
   
   L_INT  SendAttachBitmapCmd(
      LInet L_FAR *plRemoteComp,
      L_UINT uCommandID,
      L_UINT uBitmapID,
      L_UINT uWindowID);
   
   L_INT  SendAttachBitmapRsp(
      LInet L_FAR *plRemoteComp,
      L_UINT uCommandID,
      L_UINT uExtra,
      L_CHAR L_FAR *pExtra,
      L_INT nStatus);  

   L_INT  SendSaveCmd(
      LInet L_FAR *plRemoteComp,
      L_UINT uCommandID,
      L_CHAR L_FAR*pszFile,
      L_UINT uBitmapID,
      L_INT nFormat,
      L_INT nBitsPerPixel = 0, 
      L_INT nQFactor = 2,
      L_UINT uFlags = SAVEFILE_OPTIMIZEDPALETTE);

   L_INT SendSaveRsp(
      LInet L_FAR *plRemoteComp,
      L_UINT uCommandID,
      L_UINT uExtra,
      L_CHAR L_FAR*pExtra,
      L_INT nStatus);

/** NEW **/

 L_INT SendSizeWinCmd(
      LInet L_FAR *plRemoteComp,
      L_UINT uCommandID,
      L_UINT uWindowID,
      L_INT nLeft,
      L_INT nTop,
      L_INT nWidth,
      L_INT nHeight);
   
   L_INT SendSizeWinRsp(
      LInet L_FAR *plRemoteComp,
      L_UINT uCommandID,
      L_UINT uLength,
      L_CHAR L_FAR*pExtraInfo,
      L_INT nStatus);
   
   L_INT SendShowWinCmd(
      LInet L_FAR *plRemoteComp,
      L_UINT uCommandID,
      L_UINT uWindowID,
      L_INT nCmdShow);
   
   L_INT SendShowWinRsp(
      LInet L_FAR *plRemoteComp,
      L_UINT uCommandID,
      L_UINT uLength,
      L_CHAR L_FAR*pExtraInfo,
      L_INT nStatus);
   
   L_INT SendCloseWinCmd(
      LInet L_FAR *plRemoteComp,
      L_UINT uCommandID,
      L_UINT uWindowID);
   
   L_INT SendCloseWinRsp(
      LInet L_FAR *plRemoteComp,
      L_UINT uCommandID,
      L_UINT uLength,
      L_CHAR L_FAR*pExtraInfo,
      L_INT nStatus);
   
   L_INT SendFreeBitmapCmd(
      LInet L_FAR *plRemoteComp,
      L_UINT uCommandID,
      L_UINT uBitmapID);
   
   L_INT SendFreeBitmapRsp(
      LInet L_FAR *plRemoteComp,
      L_UINT uCommandID,
      L_UINT uLength,
      L_CHAR L_FAR*pExtraInfo,
      L_INT nStatus);
   
   L_INT SendSetRectCmd(
      LInet L_FAR *plRemoteComp,
      L_UINT uCommandID,
      L_UINT uWindowID,
      RECTTYPE nType,
      L_INT nLeft,
      L_INT nTop,
      L_INT nWidth,
      L_INT nHeight);
   
   L_INT SendSetRectRsp(
      LInet L_FAR *plRemoteComp,
      L_UINT uCommandID,
      L_UINT uLength,
      L_CHAR L_FAR*pExtraInfo,
      L_INT nStatus);

  /** NEW **/

  };


/*----------------------------------------------------------------------------+
| Class     : LInetPacket                                                     |
| Desc      :                                                                 |
| Return    :                                                                 | 
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+*/
class LWRP_EXPORT LInetPacket : public LBase
{
   LEAD_DECLAREOBJECT(LInetPacket);

   public:
      L_VOID *m_extLInetPacket;

private:
   HINETPACK       m_hPacket;
   L_UINT          m_uExtra;
   L_VOID L_FAR   *m_pExtra;
   L_UINT          m_uParamCount;
   pPARAMETER      m_pParamsCopy;
   
public : 
   LInetPacket();
   LInetPacket(L_UINT uExtra, L_VOID L_FAR *pExtra, L_CHAR L_FAR *pszFormat, ...);
   ~LInetPacket();

   HINETPACK GetHandle();
   L_INT SetExtraData(L_UINT uExtra, L_VOID L_FAR *pExtra);
   L_INT SetFormats(L_CHAR L_FAR *pszFormat, ...);
};

#endif //_LEAD_INET_CAPTURE_H_


/*================================================================= EOF =====*/