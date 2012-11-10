/*
   L_OCXERR.H - error codes used by the ActiveX
   Copyright (c) 1991-2000 LEAD Technologies, Inc.
   All Rights Reserved.
*/

#ifndef _L_OCXERR_H_
#define _L_OCXERR_H_

   #define ERROR_FAILURE 20000
   #define ERROR_NO_MEMORY 20001
   #define ERROR_NO_BITMAP 20002
   #define ERROR_MEMORY_TOO_LOW 20003
   #define ERROR_FILE_LSEEK 20004
   #define ERROR_FILE_WRITE 20005
   #define ERROR_FILE_GONE 20006
   #define ERROR_FILE_READ 20007
   #define ERROR_INV_FILENAME 20008
   #define ERROR_FILE_FORMAT 20009
   #define ERROR_FILENOTFOUND 20010
   #define ERROR_INV_RANGE 20011
   #define ERROR_IMAGE_TYPE 20012
   #define ERROR_INV_PARAMETER 20013
   #define ERROR_FILE_OPEN 20014
   #define ERROR_UNKNOWN_COMP 20015
   #define ERROR_FEATURE_NOT_SUPPORTED 20016
   #define ERROR_NOT_256_COLOR 20017
   #define ERROR_PRINTER 20018
   #define ERROR_CRC_CHECK 20019
   #define ERROR_QFACTOR 20021
   #define ERROR_TARGAINSTALL 20022
   #define ERROR_OUTPUTTYPE 20023
   #define ERROR_XORIGIN 20024
   #define ERROR_YORIGIN 20025
   #define ERROR_VIDEOTYPE 20026
   #define ERROR_BITPERPIXEL 20027
   #define ERROR_WINDOWSIZE 20028
   #define ERROR_NORMAL_ABORT 20029
   #define ERROR_NOT_INITIALIZED 20030
   #define ERROR_CU_BUSY 20031
   #define ERROR_INVALID_TABLE_TYPE 20032
   #define ERROR_UNEQUAL_TABLES 20033
   #define ERROR_INVALID_BUFFER 20034
   #define ERROR_MISSING_TILE_DATA 20035
   #define ERROR_INVALID_QVALUE 20036
   #define ERROR_INVALIDDATA 20037
   #define ERROR_INVALID_COMPRESSED_TYPE 20038
   #define ERROR_INVALID_COMPONENT_NUM 20039
   #define ERROR_INVALID_PIXEL_TYPE 20040
   #define ERROR_INVALID_PIXEL_SAMPLING 20041
   #define ERROR_INVALID_SOURCE_FILE 20042
   #define ERROR_INVALID_TARGET_FILE 20043
   #define ERROR_INVALID_IMAGE_DIMS 20044
   #define ERROR_INVALID_TILE_DIMS 20045
   #define ERROR_INVALID_PIX_BUFF_DIMS 20046
   #define ERROR_SEGMENT_OVERFLOW 20047
   #define ERROR_INVALID_SUBSAMPLING 20048
   #define ERROR_INVALID_Q_VIS_TABLE 20049
   #define ERROR_INVALID_DC_CODE_TABLE 20050
   #define ERROR_INVALID_AC_CODE_TABLE 20051
   #define ERROR_INSUFFICIENT_DATA 20052
   #define ERROR_MISSING_FUNC_POINTER 20053
   #define ERROR_TOO_MANY_DC_CODE_TABLES 20054
   #define ERROR_TOO_MANY_AC_CODE_TABLES 20055
   #define ERROR_INVALID_SUBIMAGE 20056
   #define ERROR_INVALID_ABORTION 20057
   #define ERROR_CU_NO_SUPPORT 20058
   #define ERROR_CU_FAILURE 20059
   #define ERROR_BAD_POINTER 20060
   #define ERROR_HEADER_DATA_FAILURE 20061
   #define ERROR_COMPRESSED_DATA_FAILURE 20062

   #define ERROR_FIXEDPAL_DATA 20063
   #define ERROR_LOADFONT_DATA 20064
   #define ERROR_NO_STAMP 20065

   #define ERROR_G3CODE_INVALID 20070
   #define ERROR_G3CODE_EOF 20071
   #define ERROR_G3CODE_EOL 20072
   #define ERROR_PREMATURE_EOF 20073
   #define ERROR_PREMATURE_EOL 20074
   #define ERROR_UNCOMP_EOF 20075
   #define ERROR_ACT_INCOMP 20076
   #define ERROR_BAD_DECODE_STATE 20077
   #define ERROR_VERSION_NUMBER 20078
   #define ERROR_TWAIN_NODSM 20079
   #define ERROR_TWAIN_BUMMER 20080
   #define ERROR_TWAIN_LOWMEMORY 20081
   #define ERROR_TWAIN_NODS 20082
   #define ERROR_TWAIN_MAXCONNECTIONS 20083
   #define ERROR_TWAIN_OPERATIONERROR 20084
   #define ERROR_TWAIN_BADCAP 20085
   #define ERROR_TWAIN_BADPROTOCOL 20086
   #define ERROR_TWAIN_BADVALUE 20087
   #define ERROR_TWAIN_SEQERROR 20088
   #define ERROR_TWAIN_BADDEST 20089
   #define ERROR_TWAIN_CANCEL 20090
   #define ERROR_PANWINDOW_NOT_CREATED 20091
   #define ERROR_NOT_ENOUGH_IMAGES 20092
   #define ERROR_USER_ABORT 20100
   #define ERROR_FPX_INVALID_FORMAT_ERROR 20101
   #define ERROR_FPX_FILE_WRITE_ERROR 20102
   #define ERROR_FPX_FILE_READ_ERROR 20103
   #define ERROR_FPX_FILE_NOT_FOUND 20104
   #define ERROR_FPX_COLOR_CONVERSION_ERROR 20105
   #define ERROR_FPX_SEVER_INIT_ERROR 20106
   #define ERROR_FPX_LOW_MEMORY_ERROR 20107
   #define ERROR_FPX_IMAGE_TOO_BIG_ERROR 20108
   #define ERROR_FPX_INVALID_COMPRESSION_ERROR 20109
   #define ERROR_FPX_INVALID_RESOLUTION 20110
   #define ERROR_FPX_INVALID_FPX_HANDLE 20111
   #define ERROR_FPX_TOO_MANY_LINES 20112
   #define ERROR_FPX_BAD_COORDINATES 20113
   #define ERROR_FPX_FILE_SYSTEM_FULL 20114
   #define ERROR_FPX_MISSING_TABLE 20115
   #define ERROR_FPX_RETURN_PARAMETER_TOO_LARGE 20116
   #define ERROR_FPX_NOT_A_VIEW 20117
   #define ERROR_FPX_VIEW_IS_TRANFORMLESS 20118
   #define ERROR_FPX_ERROR 20119
   #define ERROR_FPX_UNIMPLEMENTED_FUNCTION 20120
   #define ERROR_FPX_INVALID_IMAGE_DESC 20121
   #define ERROR_FPX_INVALID_JPEG_TABLE 20122
   #define ERROR_FPX_ILLEGAL_JPEG_ID 20123
   #define ERROR_FPX_MEMORY_ALLOCATION_FAILED 20124
   #define ERROR_FPX_NO_MEMORY_MANAGEMENT 20125
   #define ERROR_FPX_OBJECT_CREATION_FAILED 20126
   #define ERROR_FPX_EXTENSION_FAILED 20127
   #define ERROR_FPX_FREE_NULL_PTR 20128
   #define ERROR_FPX_INVALID_TILE 20129
   #define ERROR_FPX_FILE_IN_USE 20130
   #define ERROR_FPX_FILE_CREATE_ERROR 20131
   #define ERROR_FPX_FILE_NOT_OPEN_ERROR 20132
   #define ERROR_FPX_USER_ABORT 20133
   #define ERROR_FPX_OLE_FILE_ERROR 20134
   #define ERROR_BAD_TAG 20140
   #define ERROR_INVALID_STAMP_SIZE 20141
   #define ERROR_BAD_STAMP 20142
   #define ERROR_DOCUMENT_NOT_ENABLED 20143
   #define ERROR_IMAGE_EMPTY 20144
   #define ERROR_NO_CHANGE 20145
   #define ERROR_LZW_LOCKED 20146
   #define ERROR_FPXEXTENSIONS_LOCKED 20147
   #define ERROR_ANN_LOCKED 20148
   #define ERROR_DLG_CANCELED 20150
   #define ERROR_DLG_FAILED 20151
   #define ERROR_ISIS_NOCURSCANNER 20160
   #define ERROR_ISIS_SCANDRIVER_NOT_LOADED 20161
   #define ERROR_ISIS_CANCEL 20162
   #define ERROR_ISIS_BAD_TAG_OR_VALUE 20163
   #define ERROR_ISIS_NOT_READY 20164
   #define ERROR_ISIS_NO_PAGE 20165
   #define ERROR_ISIS_JAM 20166
   #define ERROR_ISIS_SCANNER_ERROR 20167
   #define ERROR_ISIS_BUSY 20168
   #define ERROR_ISIS_FILE_ERROR 20169
   #define ERROR_ISIS_NETWORK_ERROR 20170
   #define ERROR_ISIS_NOT_INSTALLED 20171
   #define ERROR_ISIS_NO_PIXDFLT 20172
   #define ERROR_ISIS_PIXVERSION 20173
   #define ERROR_ISIS_PERM_NOACCESS 20174

   #define ERROR_DOC_NOT_INITIALIZED 20180
   #define ERROR_DOC_HANDLE 20181
   #define ERROR_DOC_EMPTY 20182
   #define ERROR_DOC_INVALID_FONT 20183
   #define ERROR_DOC_INVALID_PAGE 20184
   #define ERROR_DOC_INVALID_RULE 20185
   #define ERROR_DOC_INVALID_ZONE 20186
   #define ERROR_DOC_TYPE_ZONE 20187
   #define ERROR_DOC_INVALID_COLUMN 20188
   #define ERROR_DOC_INVALID_LINE 20189
   #define ERROR_DOC_INVALID_WORD 20190
   #define ERROR_OCR_LOCKED 20191
   #define ERROR_OCR_NOT_INITIALIZED 20192
   #define ERROR_OCR_MAX_REGIONS 20193
   #define ERROR_OCR_OPTION 20194
   #define ERROR_OCR_CONVERT_DIB 20195
   #define ERROR_OCR_CANCELED 20196
   #define ERROR_OCR_INVALID_OUTPUT 20197
   #define ERROR_OCR_BLOCKED 20198
   #define ERROR_OCR_RPCMEM 20199
   #define ERROR_OCR_FATAL 20200
   #define ERROR_OCR_BADTAG 20201
   #define ERROR_OCR_BADVAL 20202
   #define ERROR_OCR_BADTYPE 20203
   #define ERROR_OCR_NOFILE 20204
   #define ERROR_OCR_BADTOK 20205
   #define ERROR_OCR_BADFMT 20206
   #define ERROR_OCR_BADMATCH 20207
   #define ERROR_OCR_NOSUPPORT 20208
   #define ERROR_OCR_BADID 20209
   #define ERROR_OCR_NOLANG 20210
   #define ERROR_OCR_LANGOVFL 20211
   #define ERROR_OCR_NOISRC 20212
   #define ERROR_OCR_NOTIDL 20213
   #define ERROR_OCR_NOVER 20214
   #define ERROR_OCR_NODRAW 20215
   #define ERROR_OCR_MEMERR 20216
   #define ERROR_OCR_BADRGN 20217
   #define ERROR_OCR_NOICR 20218
   #define ERROR_OCR_NOACTV 20219
   #define ERROR_OCR_NOMORE 20220
   #define ERROR_OCR_NOTWAIT 20221
   #define ERROR_OCR_LEXOVFL 20222
   #define ERROR_OCR_PREPROC 20223
   #define ERROR_OCR_BADFILE 20224
   #define ERROR_OCR_BADSCAN 20225
   #define ERROR_OCR_NOIMG 20226
   #define ERROR_OCR_NOLICN 20227
   #define ERROR_OCR_NOLCSRV 20228
   #define ERROR_OCR_LMEMERR 20229
   #define ERROR_OCR_RESCHNG 20230
   #define ERROR_OCR_BADPLGN 20231
   #define ERROR_OCR_NOSINK 20232
   #define ERROR_OCR_NOSRC 20233
   #define ERROR_OCR_NOTOK 20234
   #define ERROR_OCR_IMBUFOVFL 20235
   #define ERROR_OCR_TMOUT 20236
   #define ERROR_OCR_BADVRS 20237
   #define ERROR_OCR_TAGNNW 20238
   #define ERROR_OCR_SRVCAN 20239
   #define ERROR_OCR_WRFAIL 20240
   #define ERROR_OCR_SCNCAN 20241
   #define ERROR_OCR_RGOCCLD 20242
   #define ERROR_OCR_NOTORNT 20243
   #define ERROR_OCR_ACCDEN 20244
   #define ERROR_OCR_BADUOR 20245

   #define ERROR_RECORDING 20250
   #define ERROR_COMPRESSOR 20251
   #define ERROR_SOUND_DEVICE 20252
   #define ERROR_DEVICE_INUSE 20253
   #define ERROR_INV_TRACKTYPE 20254
   #define ERROR_NO_SOUNDCARD 20255
   #define ERROR_NOT_RECORDING 20256
   #define ERROR_INV_MODE 20257
   #define ERROR_NO_VIDEO_MODULE 20258
   #define ERROR_QUEUE_FULL 20259

   #define ERROR_HOST_RESOLVE 20270
   #define ERROR_CANT_INITIALIZE 20271
   #define ERROR_NO_CONNECTION 20272
   #define ERROR_HOST_NOT_FOUND 20273
   #define ERROR_NOT_SERVER 20274
   #define ERROR_NO_CONNECTIONS 20275
   #define ERROR_CONNECT_REFUSED 20276
   #define ERROR_IS_CONNECTED 20277
   #define ERROR_NET_UNREACH 20278
   #define ERROR_TIME_OUT 20279
   #define ERROR_NET_DOWN 20280
   #define ERROR_NO_BUFFERS 20281
   #define ERROR_NO_FILE_DESCR 20282
   #define ERROR_DATA_QUEUED 20283
   #define ERROR_UNKNOWN 20284
   #define ERROR_CONNECT_RESET 20285
   #define ERROR_TRANSFER_ABORTED 20286

   #define ERROR_DSHOW_FAILURE 20287

   #define ERROR_REGISTRY_READ 20288
   #define ERROR_WAVE_FORMAT 20289
   #define ERROR_INSUFICIENT_BUFFER 20290
   #define ERROR_WAVE_CONVERT 20291
   #define ERROR_MULTIMEDIA_NOT_ENABLED 20292

   #define ERROR_CAP_CONNECT 20293
   #define ERROR_CAP_DISCONNECT 20294
   #define ERROR_DISK_ISFULL 20295
   #define ERROR_CAP_OVERLAY 20296
   #define ERROR_CAP_PREVIEW 20297
   #define ERROR_CAP_COPY 20298
   #define ERROR_CAP_WINDOW 20299
   #define ERROR_CAP_ISCAPTURING 20300
   #define ERROR_NO_STREAMS 20301
   #define ERROR_CREATE_STREAM 20302
   #define ERROR_FRAME_DELETE 20303

   #define ERROR_DXF_FILTER_MISSING 20309
   #define ERROR_PAGE_NOT_FOUND     20310
   #define ERROR_DELETE_LAST_PAGE   20311
   #define ERROR_NO_HOTKEY          20312
   #define ERROR_CANNOT_CREATE_HOTKEY_WINDOW 20313
   #define ERROR_MEDICAL_NOT_ENABLED 20314
   #define ERROR_JBIG_NOT_ENABLED   20315
   #define ERROR_UNDO_STACK_EMPTY   20316
   #define ERROR_NO_TOOLBAR         20317
   #define ERROR_MEDICAL_NET_NOT_ENABLED 20318
   #define ERROR_JBIG_FILTER_MISSING 20319

   #define ERROR_CAPTURE_STILL_IN_PROCESS          20320
   #define ERROR_INVALID_DELAY                     20321
   #define ERROR_INVALID_COUNT                     20322
   #define ERROR_INVALID_INTERVAL                  20323
   #define ERROR_HOTKEY_CONFILCTS_WITH_CANCELKEY   20324
   #define ERROR_CAPTURE_INVALID_AREA_TYPE         20325
   #define ERROR_CAPTURE_NO_OPTION_STRUCTURE       20326
   #define ERROR_CAPTURE_INVALID_FILL_PATTERN      20327
   #define ERROR_CAPTURE_INVALID_LINE_STYLE        20328
   #define ERROR_CAPTURE_INVALID_INFOWND_POS       20329
   #define ERROR_CAPTURE_INVALID_INFOWND_SIZE      20330
   #define ERROR_CAPTURE_ZERO_AREA_SIZE            20331
   #define ERROR_CAPTURE_FILE_ACCESS_FAILED        20332
   #define ERROR_CAPTURE_INVALID_32BIT_EXE_OR_DLL  20333
   #define ERROR_CAPTURE_INVALID_RESOURCE_TYPE     20334
   #define ERROR_CAPTURE_INVALID_RESOURCE_INDEX    20335
   #define ERROR_CAPTURE_NO_ACTIVE_WINDOW          20336
   #define ERROR_CAPTURE_CANNOT_CAPTURE_WINDOW     20337
   #define ERROR_CAPTURE_STRING_ID_NOT_DEFINED     20338
   #define ERROR_CAPTURE_DELAY_LESS_THAN_ZERO      20339
   #define ERROR_CAPTURE_NO_MENU                   20340
   #define ERROR_BROWSE_FAILED                     20350
   #define ERROR_NOTHING_TO_DO                     20351
   #define ERROR_INTERNET_NOT_ENABLED              20352
   #define ERROR_LVKRN_MISSING                     20353

   #define ERROR_VECTOR_NOT_ENABLED                20400
   #define ERROR_VECTOR_DXF_NOT_ENABLED            20401
   #define ERROR_VECTOR_DWG_NOT_ENABLED            20402
   #define ERROR_VECTOR_MISC_NOT_ENABLED           20403
   #define ERROR_TAG_MISSING                       20404  /* Tag not found */
   #define ERROR_VECTOR_DWF_NOT_ENABLED            20405  /* Vector DWF capability is required to use this function */
   #define ERROR_NO_UNDO_STACK                     20406  /* There is no undo stack */
   #define ERROR_UNDO_DISABLED                     20407  /* The undo is disabled */
   #define ERROR_PDF_NOT_ENABLED                   20408  /* PDF capability is required to use this function */

   #define ERROR_BARCODE_DIGIT_CHECK               20410
   #define ERROR_BARCODE_INVALID_TYPE              20411
   #define ERROR_BARCODE_TEXTOUT                   20412
   #define ERROR_BARCODE_WIDTH                     20413
   #define ERROR_BARCODE_HEIGHT                    20414
   #define ERROR_BARCODE_TOSMALL                   20415
   #define ERROR_BARCODE_STRING                    20416
   #define ERROR_BARCODE_NOTFOUND                  20417
   #define ERROR_BARCODE_UNITS                     20418
   #define ERROR_BARCODE_MULTIPLEMAXCOUNT          20419
   #define ERROR_BARCODE_GROUP                     20420
   #define ERROR_BARCODE_NO_DATA                   20421
   #define ERROR_BARCODE_NOTFOUND_DUPLICATED       20422
   #define ERROR_BARCODE_LAST_DUPLICATED           20423
   #define ERROR_BARCODE_STRING_LENGTH             20424
   #define ERROR_BARCODE_LOCATION                  20425
   #define ERROR_BARCODE_1D_LOCKED                 20426
   #define ERROR_BARCODE_2D_READ_LOCKED            20427
   #define ERROR_BARCODE_2D_WRITE_LOCKED           20428
   #define ERROR_BARCODE_PDF_READ_LOCKED           20429
   #define ERROR_BARCODE_PDF_WRITE_LOCKED          20430
   #define ERROR_BARCODE_FOUNDCORRUPT              20431

   #define ERROR_NET_FIRST                         20435
   #define ERROR_NET_OUT_OF_HANDLES                20435
   #define ERROR_NET_TIMEOUT                       20436
   #define ERROR_NET_EXTENDED_ERROR                20437
   #define ERROR_NET_INTERNAL_ERROR                20438
   #define ERROR_NET_INVALID_URL                   20439
   #define ERROR_NET_UNRECOGNIZED_SCHEME           20440
   #define ERROR_NET_NAME_NOT_RESOLVED             20441
   #define ERROR_NET_PROTOCOL_NOT_FOUND            20442
   #define ERROR_NET_INVALID_OPTION                20443
   #define ERROR_NET_BAD_OPTION_LENGTH             20444
   #define ERROR_NET_OPTION_NOT_SETTABLE           20445
   #define ERROR_NET_SHUTDOWN                      20446
   #define ERROR_NET_INCORRECT_USER_NAME           20447
   #define ERROR_NET_INCORRECT_PASSWORD            20448
   #define ERROR_NET_LOGIN_FAILURE                 20449
   #define ERROR_NET_INVALID_OPERATION             20450
   #define ERROR_NET_OPERATION_CANCELLED           20451
   #define ERROR_NET_INCORRECT_HANDLE_TYPE         20452
   #define ERROR_NET_INCORRECT_HANDLE_STATE        20453
   #define ERROR_NET_NOT_PROXY_REQUEST             20454
   #define ERROR_NET_REGISTRY_VALUE_NOT_FOUND      20455
   #define ERROR_NET_BAD_REGISTRY_PARAMETER        20456
   #define ERROR_NET_NO_DIRECT_ACCESS              20457
   #define ERROR_NET_NO_CONTEXT                    20458
   #define ERROR_NET_NO_CALLBACK                   20459
   #define ERROR_NET_REQUEST_PENDING               20460
   #define ERROR_NET_INCORRECT_FORMAT              20461
   #define ERROR_NET_ITEM_NOT_FOUND                20462
   #define ERROR_NET_CANNOT_CONNECT                20463
   #define ERROR_NET_CONNECTION_ABORTED            20464
   #define ERROR_NET_CONNECTION_RESET              20465
   #define ERROR_NET_FORCE_RETRY                   20466
   #define ERROR_NET_INVALID_PROXY_REQUEST         20467
   #define ERROR_NET_NEED_UI                       20468

   #define ERROR_NET_HANDLE_EXISTS                 20469
   #define ERROR_NET_SEC_CERT_DATE_INVALID         20470
   #define ERROR_NET_SEC_CERT_CN_INVALID           20471
   #define ERROR_NET_HTTP_TO_HTTPS_ON_REDIR        20472
   #define ERROR_NET_HTTPS_TO_HTTP_ON_REDIR        20473
   #define ERROR_NET_MIXED_SECURITY                20474
   #define ERROR_NET_CHG_POST_IS_NON_SECURE        20475
   #define ERROR_NET_POST_IS_NON_SECURE            20476
   #define ERROR_NET_CLIENT_AUTH_CERT_NEEDED       20477
   #define ERROR_NET_INVALID_CA                    20478
   #define ERROR_NET_CLIENT_AUTH_NOT_SETUP         20479
   #define ERROR_NET_ASYNC_THREAD_FAILED           20480
   #define ERROR_NET_REDIRECT_SCHEME_CHANGE        20481
   #define ERROR_NET_DIALOG_PENDING                20482
   #define ERROR_NET_RETRY_DIALOG                  20483
   #define ERROR_NET_HTTPS_HTTP_SUBMIT_REDIR       20484
   #define ERROR_NET_INSERT_CDROM                  20485

   #define ERROR_NET_HTTP_HEADER_NOT_FOUND            20486
   #define ERROR_NET_HTTP_DOWNLEVEL_SERVER            20487
   #define ERROR_NET_HTTP_INVALID_SERVER_RESPONSE     20488
   #define ERROR_NET_HTTP_INVALID_HEADER              20489
   #define ERROR_NET_HTTP_INVALID_QUERY_REQUEST       20490
   #define ERROR_NET_HTTP_HEADER_ALREADY_EXISTS       20491
   #define ERROR_NET_HTTP_REDIRECT_FAILED             20492
   #define ERROR_NET_HTTP_NOT_REDIRECTED              20493
   #define ERROR_NET_HTTP_COOKIE_NEEDS_CONFIRMATION   20494
   #define ERROR_NET_HTTP_COOKIE_DECLINED             20495
   #define ERROR_NET_HTTP_REDIRECT_NEEDS_CONFIRMATION 20496

   #define ERROR_NET_NO_OPEN_REQUEST                  20497

   #define ERROR_VECTOR_IS_LOCKED                  20500     /* Vector handle is locked */
   #define ERROR_VECTOR_IS_EMPTY                   20501
   #define ERROR_VECTOR_LAYER_NOT_FOUND            20502
   #define ERROR_VECTOR_LAYER_IS_LOCKED            20503
   #define ERROR_VECTOR_LAYER_ALREADY_EXISTS       20504
   #define ERROR_VECTOR_OBJECT_NOT_FOUND           20505
   #define ERROR_VECTOR_INVALID_OBJECT_TYPE        20506
   #define ERROR_VECTOR_PEN_NOT_FOUND              20507
   #define ERROR_VECTOR_BRUSH_NOT_FOUND            20508
   #define ERROR_VECTOR_FONT_NOT_FOUND             20509
   #define ERROR_VECTOR_BITMAP_NOT_FOUND           20510
   #define ERROR_VECTOR_POINT_NOT_FOUND            20511
   #define ERROR_VECTOR_ENGINE_NOT_FOUND           20512  
   #define ERROR_VECTOR_INVALID_ENGINE             20513
   #define ERROR_VECTOR_CLIPBOARD                  20514
   #define ERROR_VECTOR_CLIPBOARD_IS_EMPTY         20515
   #define ERROR_VECTOR_CANT_ADD_TEXT              20516
   #define ERROR_VECTOR_CANT_READ_WMF              20517
   #define ERROR_VECTOR_GROUP_NOT_FOUND            20518
   #define ERROR_VECTOR_GROUP_ALREADY_EXISTS       20519
   // start JPEG2000 error codes 
   #define ERROR_JP2_FAILURE                       20530
   #define ERROR_JP2_SIGNATURE                     20531
   #define ERROR_JP2_UNSUPPORTED                   20532
   #define ERROR_J2K_FAILURE                       20533
   #define ERROR_J2K_NO_SOC                        20534
   #define ERROR_J2K_NO_SOT                        20535
   #define ERROR_J2K_INFORMATION_SET               20536
   #define ERROR_J2K_LOW_TARGET_SIZE               20537
   #define ERROR_J2K_DECOMPOSITION_LEVEL           20538
   #define ERROR_J2K_MARKER_VALUE                  20539
   #define ERROR_J2K_UNSUPPORTED                   20540
   #define ERROR_J2K_FILTER_MISSING                20541  /* J2K filter is needed to use this function */
   #define ERROR_J2K_LOCKED                        20542  /* J2K support is locked */
   // end JPEG2000 error codes

   // Start of Twain Toolkit Error Code
   #define ERROR_TWAIN_NO_LIBRARY                  20560
   #define ERROR_TWAIN_NOT_AVAILABLE               ERROR_TWAIN_NO_LIBRARY
   #define ERROR_TWAIN_INVALID_DLL                 20561
   #define ERROR_TWAIN_NOT_INITIALIZED             20562
   #define ERROR_TWAIN_CANCELED                    20563
   #define ERROR_TWAIN_CHECK_STATUS                20564
   #define ERROR_TWAIN_END_OF_LIST                 20565
   #define ERROR_TWAIN_CAP_NOT_SUPPORTED           20566
   #define ERROR_TWAIN_SOURCE_NOT_OPEN             20567
   #define ERROR_TWAIN_BAD_VALUE                   20568
   #define ERROR_TWAIN_INVALID_STATE               20569
   #define ERROR_TWAIN_CAPS_NEG_NOT_ENDED          20570
   #define ERROR_TWAIN_OPEN_FILE                   20571
   #define ERROR_TWAIN_INV_HANDLE                  20572
   #define ERROR_TWAIN_WRITE_TO_FILE               20573
   #define ERROR_TWAIN_INV_VERSION_NUM             20574
   #define ERROR_TWAIN_READ_FROM_FILE              20575
   #define ERROR_TWAIN_NOT_VALID_FILE              20576
   #define ERROR_TWAIN_INV_ACCESS_RIGHT            20577
   #define ERROR_TWAIN_CUSTOMBASE                  20578
   #define ERROR_TWAIN_DENIED                      20579
   #define ERROR_TWAIN_FILEEXISTS                  20580
   #define ERROR_TWAIN_FILENOTFOUND                20581
   #define ERROR_TWAIN_NOTEMPTY                    20582
   #define ERROR_TWAIN_PAPERJAM                    20583
   #define ERROR_TWAIN_PAPERDOUBLEFEED             20584
   #define ERROR_TWAIN_FILEWRITEERROR              20585
   #define ERROR_TWAIN_CHECKDEVICEONLINE           20586
   // End of Twain Toolkit Error Codes

   #define ERROR_PAINT_INTERNAL                    20600   /* Internal error (Call LEAD) */
   #define ERROR_PAINT_INV_DATA                    20601   /* Internal error (Call LEAD) */
   #define ERROR_PAINT_NO_RESOURCES                20602   /* Internal error (Call LEAD) */
   #define ERROR_PAINT_NOT_ENABLED                 20603   /* DigitalPaint capability is required to use this function */

   #define ERROR_CONTAINER_INV_HANDLE              20630
   #define ERROR_CONTAINER_INV_OPERATION           20631
   #define ERROR_CONTAINER_NO_RESOURCES            20632

   #define ERROR_TOOLBAR_NO_RESOURCES              20660
   #define ERROR_TOOLBAR_INV_STATE                 20661
   #define ERROR_TOOLBAR_INV_HANDLE                20662

   #define ERROR_AUTOMATION_INV_HANDLE             20690
   #define ERROR_AUTOMATION_INV_STATE              20691

   // start Segmentation errors
   #define ERROR_INV_SEG_HANDLE                    20700
   #define ERROR_INV_SEG_DATA                      20701
   #define ERROR_INV_LAYER_DATA                    20702
   #define ERROR_MRC_NOT_ALLOCATED                 20703
   #define ERROR_INV_MIN_SEGMENT                   20704
   #define ERROR_SEGMENTATION_FAILURE              20705
   #define ERROR_MRC_INV_PAGE                      20706
   // end Segmentation errors

   // Start Pdf Errors 
   //#define ERROR_PDF_NOT_ENABLED                 20408  
   #define ERROR_PDF_FILE_ENCRYPTED                20721  /* The Pdf file is encrypted and the szPassword 
                                                             member of the FILEPDFOPTIONS is not set 
                                                             (no password).*/
   #define ERROR_PDF_INVALID_PASSWORD              20722  
   #define ERROR_PDF_FAX_NOT_ENABLED               20723  /* This feature requires Fax engine . */
   #define ERROR_PDF_JPEG_NOT_ENABLED              20724  /* This feature requires Jpeg engine . */
   #define ERROR_PDF_INV_DOC_STRUCTURING_COMMENTS  20725  /* Invalid Document Structuring comments (Ps and EPS)*/
   #define ERROR_PDF_FONTS_DIRECTORY_NOT_FOUND     20726  /* Could not find Fonts directory */
   #define ERROR_PDF_CANNOT_EDIT_FILE              20727  /* Cannot insert,delete,append or replace pages .*/
   #define ERROR_PDF_BAD_CONTENT                   20728  /* File is corrupted */
   #define ERROR_PDF_BAD_INITIALIZATION_FILES      20729  /* Either the files required for initializing the PDF engine were 
                                                             not found or they were found but they are not correct .*/
   // Start ISAPI Errors
   #define ERROR_ISAPI_CONFIG_NOT_FOUND            20740  /* Config Not Found In Registry*/
   #define ERROR_ISAPI_DSN_NOT_FOUND               20741  /* DSN Not Found In ODBC*/
   #define ERROR_ISAPI_SQL_EXEC                    20742  /* Table Or Fields Not Found In Database*/
   #define ERROR_ISAPI_RECORD_NOT_FOUND            20743  /* Record Not Found In Database*/
   #define ERROR_ISAPI_DATABASE_SETTING            20744  /* Error On Database Settings in Registry*/
   #define ERROR_ISAPI_DATABASE_SAVE_BITMAP        20745  /* Can't Save Bitmap in Database */
   #define ERROR_ISAPI_DATABASE_RECORD_DUPLICATE   20746  /* Record is Alredy Exist in Database , 
                                                             Doublecat In Primary Key*/
   #define ERROR_ISAPI_SESSION_FULL                20747  /* Can't Add User To ISAPI SESSION*/
   #define ERROR_ISAPI_CACHE_SYSTEM_NOT_ENABLED    20748  /* The caching system not enabled in 
                                                             Configuration Settings*/
   #define ERROR_ISAPI_CACHE_MAX_SIZE              20749  /* The maximum size of cache limit*/
   #define ERROR_ISAPI_CACHE_SETTING               20750  /* Error On Cache System Settings in Registry */
   // end ISAPI errors

   // Start SVG errors
   #define ERROR_SVG_FILE_SIZE_READ                20770
   #define ERROR_SVG_ROOT_NOT_SVG                  20771
   #define ERROR_SVG_NOFOUND_ROOT_ELEMENT          20772
   #define ERROR_SVG_INV_ELEMENT                   20773
   #define ERROR_SVG_DUPLICATED_ATTRIBUTE          20774
   #define ERROR_SVG_INV_ATTRIBUTE                 20775
   #define ERROR_SVG_INV_ATTRIBUTE_VALUE           20776
   #define ERROR_SVG_BAD_CSS_PROPERTY              20777
   #define ERROR_SVG_MISSING_REQUIRED_ATTRIBUTE    20778
   #define ERROR_SVG_DUPLICATED_ID                 20779
   #define ERROR_SVG_INV_COORDINATES_NUMBER        20780
   #define ERROR_SVG_INV_STRING_COMMA              20781
   // End SVG errors

   // start ColorSpace SDK errors
   #define ERROR_INVALID_FORMAT                               20785
   #define ERROR_UNSUPPORTED_METHOD                           20786
   #define ERROR_OPENING_PROFILE                              20787
   #define ERROR_INVALID_COLOR_PROFILE                        20788
   #define ERROR_INVALID_STRUCT_SIZE                          20789
   #define ERROR_U_V_NOT_MULTIPLES                            20791
   #define ERROR_NO_NONPLANAR_VERTICAL_SUBSAMPLING_SUPPORTED  20792
   #define ERROR_PLANAR_ALIGNMENT_NOT_SUPPORTED               20793
   #define ERROR_UNSUPPORTED_CONVERSION                       20794
   #define ERROR_TRUNCATE_HEIGHT                              20795
   #define ERROR_TRUNCATE_WIDTH                               20796
   #define ERROR_TRUNCATE_WIDTH_AND_HEIGHT                    20797
   // end ColorSpace SDK errors

   #define ERROR_LAYER_MISSING                     20800
   #define ERROR_BAD_MARKER                        20801  /* Bad JPEG marker */
   #define ERROR_AUDIO_MISSING                     20802  /* The audio data is not present */
   #define ERROR_DICOM_NOT_ENABLED                 20803  /* Dicom support is required to use this function */
   #define ERROR_EXTGRAY_NOT_ENABLED               20804  /* Extended grayscale support is required to use this function */
   #define ERROR_FILE_READONLY                     20805  /* File is read-only. Cannot open file with write access */

   #define ERROR_LTCLR_DLL_NOTLOADED      20900  /* The Ltclr13n dll is not loaded */
   #define ERROR_LTDLGRES_DLL_NOTLOADED   20901  /* The LtDlgRes13n dll is not loaded */

#endif //_L_OCXERR_H_
