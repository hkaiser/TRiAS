/*----------------------------------------------------------------------------+
| LEADTOOLS for Windows -                                                     |
| Copyright (c) 1991-2000 LEAD Technologies, Inc.                             |
| All Rights Reserved.                                                        |
|-----------------------------------------------------------------------------|
| PROJECT   : LEAD wrappers                                                   |
| FILE NAME : tcprnt.h                                                        |
| DESC      :                                                                 |
+----------------------------------------------------------------------------*/

#ifndef  _LEAD_WRAPPER_DEFINES_H_
#define  _LEAD_WRAPPER_DEFINES_H_

/*----------------------------------------------------------------------------+
| DEFINES                                                                     |
+----------------------------------------------------------------------------*/
#ifdef   _LEAD_WRAPPER_
   #define  LWRP_EXPORT __declspec(dllexport)
#else
   #define  LWRP_EXPORT __declspec(dllimport)
#endif

//--FOR LOADING LEAD LIBRARIES-------------------------------------------------
#define  LT_KRN   0x00000001
#define  LT_DIS   0x00000002
#define  LT_FIL   0x00000004
#define  LT_IMG   0x00000008
#define  LT_EFX   0x00000010
#define  LT_DLG   0x00000020
#define  LT_ISI   0x00000040
#define  LT_TWN   0x00000080
#define  LT_SCR   0x00000100
#define  LT_ANN   0x00000200
#define  LT_CAP   0x00000400
#define  LT_NET   0x00000800
#define  LT_VID   0x00001000
#define  LT_TMB   0x00002000
#define  LT_LST   0x00004000
#define  LV_KRN   0x00010000
#define  LV_DLG   0x00020000
#define  LT_BAR   0x00040000
#define  LD_KRN   0x00080000
#define  LT_AUT   0x00100000
#define  LT_CON   0x00200000
#define  LT_PNT   0x00400000
#define  LT_RESERVED   0x00800000
#define  LT_TLB   0x01000000
#define  LT_PDG   0x02000000
#define  LT_WEB   0x04000000
#define  LT_SGM   0x08000000

#define  LT_ALL_LEADLIB                   \
         LT_KRN|                          \
         LT_DIS|LT_FIL|LT_IMG|LT_EFX|     \
         LT_DLG|LT_ISI|LT_TWN|LT_SCR|     \
         LT_ANN|LT_CAP|LT_NET|LT_VID|     \
         LT_TMB|LT_LST|LV_KRN|LV_DLG|     \
         LT_BAR|LD_KRN|LT_AUT|LT_CON|     \
         LT_RESERVED |LT_TLB|LT_PDG|LT_WEB| LT_SGM

//--FOR REDIRECTING I/O CALLBACKS----------------------------------------------
#define  IO_OPEN              0x0001
#define  IO_CLOSE             0x0002
#define  IO_READ              0x0004
#define  IO_WRITE             0x0008
#define  IO_SEEK              0x0010
#define  IO_REDIRECT_ALL  IO_OPEN|IO_CLOSE|IO_READ|IO_WRITE|IO_SEEK


//--FOR BITMAP WINDOW LEAD SPECIFIC STYLE---------------------------------------
#define L_BS_PROCESSKEYBOARD  0x00000002
#define L_BS_3DAPPEARANCE     0x00000008

//--FOR LEAD SPESIFIC MESSAGE---------------------------------------------------
#define WM_LEAD               WM_USER+200
//--FOR LEAD SPESIFIC ERROR-----------------------------------------------------
#define LEAD_LAST_ERROR       0

//--FOR BITMAP WINDOW-----------------------------------------------------------
#define COPY2CB_FLOATER       0x8000

//--FOR ANNOTATION WINDOW-------------------------------------------------------
#define COPY2CB_ANNOBJECTS    0x4000

#endif //_LEAD_WRAPPER_DEFINES_H_
/*================================================================= EOF =====*/
