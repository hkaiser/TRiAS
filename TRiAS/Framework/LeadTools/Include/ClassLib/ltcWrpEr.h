/*----------------------------------------------------------------------------+
| LEADTOOLS for Windows -                                                     |
| Copyright (c) 1991-2000 LEAD Technologies, Inc.                             |
| All Rights Reserved.                                                        |
|-----------------------------------------------------------------------------|
| PROJECT   : LEAD wrappers                                                   |
| FILE NAME : tcprnt.h                                                        |
| DESC      :                                                                 |
+----------------------------------------------------------------------------*/

#ifndef  _LEAD_WRAPPER_ERRORS_H_
#define  _LEAD_WRAPPER_ERRORS_H_

/*----------------------------------------------------------------------------+
| DEFINES                                                                     |
+----------------------------------------------------------------------------*/

//-----------------------------------------------------------------------------

//--WRAPPER SPECIFIC ERRORS----------------------------------------------------
#define END_LEAD_ERROR                             -917
#define WRAPPER_START_ERROR                        -1000

#define WRPERR_BITMAP_NOT_ALLOCATED                -1000
#define WRPERR_INVALID_CLASS                       -1001
#define WRPERR_INVALID_PARAMETERS                  -1002
#define WRPERR_BITMAP_BPP                          -1003
#define WRPERR_BITMAP_DITHER_NOT_STARTED           -1004
#define WRPERR_BITMAP_ALREADY_ALLOCATED            -1005
#define WRPERR_BITMAP_PREPARE_FAILED               -1006
#define WRPERR_BITMAP_ITEM_IN_LIST                 -1007
#define WRPERR_BITMAP_CONVERT                      -1008
#define WRPERR_INET_ITEM_NOTFOUND                  -1009
#define WRPERR_INET_NOMORE_SPACE                   -1010
#define WRPERR_INET_ALREADY_CONNECTED              -1011
#define WRPERR_MMCAPTURE_WINDOW_ALREADY_CREATED    -1012
#define WRPERR_MMEDIA_ALREADY_CREATED              -1013
#define WRPERR_PLAYBACK_ALREADY_CREATED            -1014
#define WRPERR_LIST_ALREADY_CREATED                -1015
#define WRPERR_LIST_NOT_CREATED                    -1016
#define WRPERR_CLASS_NOT_READY                     -1017
#define WRPERR_BUFFER_NO_MEMORY                    -1018
#define WRPERR_BUFFER_ERRSIZE                      -1019
#define WRPERR_BUFFER_INVALID_HANDLE               -1020
#define WRPERR_FILE_FEEDLOAD_NOT_STARTED           -1021
#define WRPERR_MEMFILE_COMP_NOT_STARTED            -1022
#define WRPERR_ANN_INVALID_FILE                    -1023
#define WRPERR_ANN_INVALID_FILEMEM                 -1024
#define WRPERR_ANN_INVALID_OBJECT                  -1025
#define WRPERR_ANN_DESTROYTOOLBAR_FAILED           -1026
#define WRPERR_ANN_ALLOCATED_MEMORY                -1027
#define WRPERR_BUFFER_NOTVALID                     -1028
#define WRPERR_BUFFER_REALLOCATE                   -1029
#define WRPERR_BUFFER_COPY                         -1030
#define WRPERR_BUFFER_RESIZE_NOT_STARTED           -1031
#define WRPERR_BUFFER_LOCKED                       -1032
#define WRPERR_BITMAPWND_PANNOTCREATED             -1033
#define WRPERR_BITMAPWND_REGISTER                  -1034
#define WRPERR_BITMAPWND_CREATEWINDOW              -1035
#define WRPERR_ANIMATION_ALREADY_STARTED           -1036
#define WRPERR_ANIMATION_IS_RUNNING                -1037
#define WRPERR_ANNWND_CANT_CREATE_OBJECT           -1038
#define WRPERR_LTKRN_DLL_NOT_LOADED                -1039
#define WRPERR_LTDIS_DLL_NOT_LOADED                -1040
#define WRPERR_LTFIL_DLL_NOT_LOADED                -1041
#define WRPERR_LTIMG_DLL_NOT_LOADED                -1042
#define WRPERR_LTEFX_DLL_NOT_LOADED                -1043
#define WRPERR_LTDLG_DLL_NOT_LOADED                -1044
#define WRPERR_LTISI_DLL_NOT_LOADED                -1045
#define WRPERR_LTTWN_DLL_NOT_LOADED                -1046
#define WRPERR_LTSCR_DLL_NOT_LOADED                -1047
#define WRPERR_LTANN_DLL_NOT_LOADED                -1048
#define WRPERR_LTCAP_DLL_NOT_LOADED                -1049
#define WRPERR_LTNET_DLL_NOT_LOADED                -1050
#define WRPERR_LTVID_DLL_NOT_LOADED                -1051   
#define WRPERR_BITMAPLIST_ITEM_OPERATION_ERROR     -1052
#define WRPERR_BITMAPLIST_NOT_CREATED              -1053
#define WRPERR_ANIMATION_INVALID_FILE              -1054
#define WRPERR_NOT_LEAD_BITMAP                     -1055
#define WRPERR_BITMAP_IS_ALIST_MEMBER              -1056
#define WRPERR_WINDOW_NOT_CREATED                  -1057
#define WRPERR_OPERATION_NOT_ALLOWED               -1058
#define WRPERR_OPERATION_CANCELED                  -1059
#define WRPERR_LTTMB_DLL_NOT_LOADED                -1060   
#define WRPERR_LTLST_DLL_NOT_LOADED                -1061   
#define WRPERR_IMAGELISTCONTROL_CREATE             -1062
#define WRPERR_LVKRN_DLL_NOT_LOADED                -1063  //LVKRN.DLL is not loaded
#define WRPERR_NO_VECTOR                           -1064  //No LVectorBase object associated with LVectorDialog object 
#define WRPERR_VECTOR_NOT_ALLOCATED                -1065  //No vector loaded into LVectorBase object
#define WRPERR_LVDLG_DLL_NOT_LOADED                -1066  //LVDLG.DLL is not loaded
#define WRPERR_FEATURE_NOT_SUPPORTED_IN_DIRECTX    -1067  //Feature not supported when using DirectX engine to process vector images
#define WRPERR_FEATURE_NOT_SUPPORTED               -1068  //Feature not supported
#define WRPERR_VECTOR_NOT_ASSOCIATED               -1069  //No LVectorBase object associated with object
#define WRPERR_VECTOR_INVALID_LAYER                -1070  //Invalid LVectorLayer object
#define WRPERR_VECTOR_INVALID_OBJECT               -1071  //LVectorObject not associated with valid vector object
#define WRPERR_VECTOR_INVALID_OBJECT_TYPE          -1072  //LVectorObject has been invalidated (can happen on ExplodeObject)
#define WRPERR_VECTOR_INVALID_OBJECT_DESC          -1073  //UnlockObject() being called on invalid object descriptor
#define WRPERR_VECTOR_LOCK_ERROR                   -1074  //Returned when calling LockObject() on an already locked object
#define WRPERR_LTBAR_DLL_NOT_LOADED                -1075  //LTBAR.DLL is not loaded
#define WRPERR_LTAUT_DLL_NOT_LOADED                -1076
#define WRPERR_LTCON_DLL_NOT_LOADED                -1077
#define WRPERR_LDKRN_DLL_NOT_LOADED                -1078
#define WRPERR_LTTLB_DLL_NOT_LOADED                -1080
#define WRPERR_LTPNT_DLL_NOT_LOADED                -1081
#define WRPERR_LTPDG_DLL_NOT_LOADED                -1082
#define WRPERR_VECTOR_INVALID_GROUP                -1083
#define WRPERR_LTWEB_DLL_NOT_LOADED                -1084
#define WRPERR_LTSGM_DLL_NOT_LOADED                -1085

#define WRPERR_END_ERROR                           -1085
#endif //_LEAD_WRAPPER_ERRORS_H_ 
/*================================================================= EOF =====*/

