/*
   LTERR.H - global error codes
   Copyright (c) 1991-2000 LEAD Technologies, Inc.
   All Rights Reserved.
*/

#ifndef _LTERR_H_
#define _LTERR_H_

#include "ltsys.h"

#define SUCCESS_IGNORETHISCOPYALL        7   /** Function successful. Ignore this marker but copy all remaining markers **/
#define SUCCESS_IGNOREALLMARKERS         6   /** Function successful. Ignore this marker and all remaining markers **/
#define SUCCESS_IGNOREMARKER             5   /** Function successful. Ignore this marker           **/
#define SUCCESS_RETRY                    4   /** Function successful. Retry doing the failed op.   **/
#define SUCCESS_DELETE                   3   /** Function successful. Delete file before quiting   **/
#define SUCCESS_ABORT                    2   /** Function successful. You can quit now.            **/
#define SUCCESS                          1   /** Function successful                               **/
#define FAILURE                          0   /** Function not successful                           **/

#define ERROR_NO_MEMORY                 -1   /** Not enough memory available**/
#define ERROR_NO_BITMAP                 -2   /** Invalid bitmap handle      **/
#define ERROR_MEMORY_TOO_LOW            -3   /** Not enough memory available**/
#define ERROR_FILE_LSEEK                -4   /** Error seeking to position  **/
#define ERROR_FILE_WRITE                -5   /** Error writing file         **/
#define ERROR_FILE_GONE                 -6   /** File not present - abort   **/
#define ERROR_FILE_READ                 -7   /** Error reading file         **/
#define ERROR_INV_FILENAME              -8   /** Invalid filename specified **/
#define ERROR_FILE_FORMAT               -9   /** Invalid file format        **/
#define ERROR_FILENOTFOUND              -10  /** File not found             **/
#define ERROR_INV_RANGE                 -11  /** Invalid width/height       **/
#define ERROR_IMAGE_TYPE                -12  /** Image format recognized, but sub-type not supported **/
#define ERROR_INV_PARAMETER             -13  /** Invalid parameter passed   **/
#define ERROR_FILE_OPEN                 -14  /** Not able to open file      **/
#define ERROR_UNKNOWN_COMP              -15  /** Unknown compression format **/
#define ERROR_FEATURE_NOT_SUPPORTED     -16  /** Feature not supported      **/
#define ERROR_NOT_256_COLOR             -17  /** VGA card only supports 256 colors (8 bit)           **/
#define ERROR_PRINTER                   -18  /** Printer error              **/
#define ERROR_CRC_CHECK                 -19  /** Data CRC check error       **/
#define ERROR_QFACTOR                   -21  /** Invalid QFactor specified  **/
#define ERROR_TARGAINSTALL              -22  /** TARGA not installed        **/
#define ERROR_OUTPUTTYPE                -23  /** Invalid compression format **/
#define ERROR_XORIGIN                   -24  /** X origin specified invalid **/
#define ERROR_YORIGIN                   -25  /** Y origin specified invalid **/
#define ERROR_VIDEOTYPE                 -26  /** Invalid video mode         **/
#define ERROR_BITPERPIXEL               -27  /** Invalid bits/pixel         **/
#define ERROR_WINDOWSIZE                -28  /** Invalid window size        **/
#define ERROR_NORMAL_ABORT              -29  /** Escape key pressed - or user aborted operation      **/
#define ERROR_NOT_INITIALIZED           -30  /** Internal error - call LEAD **/
#define ERROR_CU_BUSY                   -31  /** Internal error - call LEAD **/
#define ERROR_INVALID_TABLE_TYPE        -32  /** Internal error - call LEAD **/
#define ERROR_UNEQUAL_TABLES            -33  /** Internal error - call LEAD **/
#define ERROR_INVALID_BUFFER            -34  /** Internal error - call LEAD **/
#define ERROR_MISSING_TILE_DATA         -35  /** Internal error - call LEAD **/
#define ERROR_INVALID_QVALUE            -36  /** Internal error - call LEAD **/
#define ERROR_INVALIDDATA               -37  /** Internal error - call LEAD **/
#define ERROR_INVALID_COMPRESSED_TYPE   -38  /** Internal error - call LEAD **/
#define ERROR_INVALID_COMPONENT_NUM     -39  /** Internal error - call LEAD **/
#define ERROR_INVALID_PIXEL_TYPE        -40  /** Internal error - call LEAD **/
#define ERROR_INVALID_PIXEL_SAMPLING    -41  /** Internal error - call LEAD **/
#define ERROR_INVALID_SOURCE_FILE       -42  /** Internal error - call LEAD **/
#define ERROR_INVALID_TARGET_FILE       -43  /** Internal error - call LEAD **/
#define ERROR_INVALID_IMAGE_DIMS        -44  /** Internal error - call LEAD **/
#define ERROR_INVALID_TILE_DIMS         -45  /** Internal error - call LEAD **/
#define ERROR_INVALID_PIX_BUFF_DIMS     -46  /** Internal error - call LEAD **/
#define ERROR_SEGMENT_OVERFLOW          -47  /** Internal error - call LEAD **/
#define ERROR_INVALID_SUBSAMPLING       -48  /** Internal error - call LEAD **/
#define ERROR_INVALID_Q_VIS_TABLE       -49  /** Internal error - call LEAD **/
#define ERROR_INVALID_DC_CODE_TABLE     -50  /** Internal error - call LEAD **/
#define ERROR_INVALID_AC_CODE_TABLE     -51  /** Internal error - call LEAD **/
#define ERROR_INSUFFICIENT_DATA         -52  /** Internal error - call LEAD **/
#define ERROR_MISSING_FUNC_POINTER      -53  /** Internal error - call LEAD **/
#define ERROR_TOO_MANY_DC_CODE_TABLES   -54  /** Internal error - call LEAD **/
#define ERROR_TOO_MANY_AC_CODE_TABLES   -55  /** Internal error - call LEAD **/
#define ERROR_INVALID_SUBIMAGE          -56  /** Internal error - call LEAD **/
#define ERROR_INVALID_ABORTION          -57  /** Internal error - call LEAD **/
#define ERROR_CU_NO_SUPPORT             -58  /** Internal error - call LEAD **/
#define ERROR_CU_FAILURE                -59  /** Internal error - call LEAD **/
#define ERROR_BAD_POINTER               -60  /** Internal error - call LEAD **/
#define ERROR_HEADER_DATA_FAILURE       -61  /** Internal error - call LEAD **/
#define ERROR_COMPRESSED_DATA_FAILURE   -62  /** Internal error - call LEAD **/

#define ERROR_FIXEDPAL_DATA             -63  /** fixed palette data not found **/
#define ERROR_LOADFONT_DATA             -64  /** fixed palette data not found **/
#define ERROR_NO_STAMP                  -65  /** stamp not found **/
#define ERROR_G3CODE_INVALID            -70  /** invalid group 3 dat **/
#define ERROR_G3CODE_EOF                -71  /** group3 code end of file **/
#define ERROR_G3CODE_EOL                -72  /** group3 code end of code **/
#define ERROR_PREMATURE_EOF             -73  /** premature EOF at scanline **/
#define ERROR_PREMATURE_EOL             -74  /** premature end-of-line code **/
#define ERROR_UNCOMP_EOF                -75  /** premature end-of-line code **/
#define ERROR_ACT_INCOMP                -76  /** premature end-of-line code **/
#define ERROR_BAD_DECODE_STATE          -77  /** premature end-of-line code **/
#define ERROR_VERSION_NUMBER            -78  /** bad version number **/
#define ERROR_TWAIN_NODSM               -79  /** TWAIN source manager not found **/
#define ERROR_TWAIN_BUMMER              -80  /** TWAIN Failure due to unknown causes **/
#define ERROR_TWAIN_LOWMEMORY           -81  /** TWAIN Not enough memory to perform operation **/
#define ERROR_TWAIN_NODS                -82  /** TWAIN No Data Source **/
#define ERROR_TWAIN_MAXCONNECTIONS      -83  /** TWAIN DS is connected to max possible apps **/
#define ERROR_TWAIN_OPERATIONERROR      -84  /** TWAIN DS or DSM reported error, app shouldn't (no need for your app to report the error) **/
#define ERROR_TWAIN_BADCAP              -85  /** TWAIN Unknown capability **/
#define ERROR_TWAIN_BADPROTOCOL         -86  /** TWAIN Unrecognized MSG DG DAT combination **/
#define ERROR_TWAIN_BADVALUE            -87  /** TWAIN Data parameter out of range **/
#define ERROR_TWAIN_SEQERROR            -88  /** TWAIN DG DAT MSG out of expected sequence **/
#define ERROR_TWAIN_BADDEST             -89  /** TWAIN Unknown destination App/Src in DSM_Entry **/
#define ERROR_TWAIN_CANCEL              -90  /** TWAIN Operation was cancelled **/
#define ERROR_PANWINDOW_NOT_CREATED     -91  /** PanWindow creation failed **/
#define ERROR_NOT_ENOUGH_IMAGES         -92  /** Not enough images - more input images are required **/
#define ERROR_TWAIN_CAPUNSUPPORTED      -93  /** TWAIN capability unsupported **/
#define ERROR_TWAIN_FILEXFER_UNSUPPORTED -94 /** TWAIN File Transfer unsupported **/

#define ERROR_USER_ABORT               -100  /** User has aborted operation **/

#define ERROR_FPX_INVALID_FORMAT_ERROR       -101  /* Invalid FlashPix format */
#define ERROR_FPX_FILE_WRITE_ERROR           -102  /* Error writing file */
#define ERROR_FPX_FILE_READ_ERROR            -103  /* Error reading file */
#define ERROR_FPX_FILE_NOT_FOUND             -104  /* File not found */
#define ERROR_FPX_COLOR_CONVERSION_ERROR     -105  /* Color conversion error */
#define ERROR_FPX_SEVER_INIT_ERROR           -106  /* Server initialize error */
#define ERROR_FPX_LOW_MEMORY_ERROR           -107  /* Not enough memory available */
#define ERROR_FPX_IMAGE_TOO_BIG_ERROR        -108  /* Image too big */
#define ERROR_FPX_INVALID_COMPRESSION_ERROR  -109  /* Invalid compression */
#define ERROR_FPX_INVALID_RESOLUTION         -110  /* Invalid resolution */
#define ERROR_FPX_INVALID_FPX_HANDLE         -111  /* Invalid handle */
#define ERROR_FPX_TOO_MANY_LINES             -112  /* Too many lines */
#define ERROR_FPX_BAD_COORDINATES            -113  /* Invalid coordinates */
#define ERROR_FPX_FILE_SYSTEM_FULL           -114  /* File system full */
#define ERROR_FPX_MISSING_TABLE              -115  /* The table is missing */
#define ERROR_FPX_RETURN_PARAMETER_TOO_LARGE -116  /* Parameter too large */
#define ERROR_FPX_NOT_A_VIEW                 -117  /* Error view */
#define ERROR_FPX_VIEW_IS_TRANFORMLESS       -118  /* The view is transformless */
#define ERROR_FPX_ERROR                      -119  /* General error */
#define ERROR_FPX_UNIMPLEMENTED_FUNCTION     -120  /* Unimplemented function */
#define ERROR_FPX_INVALID_IMAGE_DESC         -121  /* Invalid image description */
#define ERROR_FPX_INVALID_JPEG_TABLE         -122  /* Invalid jpeg table */
#define ERROR_FPX_ILLEGAL_JPEG_ID            -123  /* Illegal jpeg identifier */
#define ERROR_FPX_MEMORY_ALLOCATION_FAILED   -124  /* Memory allocation failed */
#define ERROR_FPX_NO_MEMORY_MANAGEMENT       -125  /* No memory management */
#define ERROR_FPX_OBJECT_CREATION_FAILED     -126  /* Object creation failed */
#define ERROR_FPX_EXTENSION_FAILED           -127  /* Extension_failed */
#define ERROR_FPX_FREE_NULL_PTR              -128  /* Free null pointer */
#define ERROR_FPX_INVALID_TILE               -129  /* Invalid tile */
#define ERROR_FPX_FILE_IN_USE                -130  /* File in use */
#define ERROR_FPX_FILE_CREATE_ERROR          -131  /* Error creating file */
#define ERROR_FPX_FILE_NOT_OPEN_ERROR        -132  /* File not open */
#define ERROR_FPX_USER_ABORT                 -133  /* User abort */
#define ERROR_FPX_OLE_FILE_ERROR             -134  /* OLE File I/O error */

#define ERROR_BAD_TAG                        -140  /* Bad TIFF tag */
#define ERROR_INVALID_STAMP_SIZE             -141  /* Stamp size is too big or invalid bits/pixel, etc */
#define ERROR_BAD_STAMP                      -142  /* Stamp is present but data is corrupted */
#define ERROR_DOCUMENT_NOT_ENABLED           -143  /* Document capability is required to use this function */
#define ERROR_IMAGE_EMPTY                    -144  /* Image is empty */
#define ERROR_NO_CHANGE                      -145  /* The image hasn't changed */
#define ERROR_LZW_LOCKED                     -146  /* The LZW capabilities are locked */
#define ERROR_FPXEXTENSIONS_LOCKED           -147  /* The FlashPix extension capabilities are locked */
#define ERROR_ANN_LOCKED                     -148  /* One or more annotation objects are still locked */
#define ERROR_EXCEPTION                      -149  /* An unspecified exception occured - could be memory access violations */

#define ERROR_DLG_CANCELED                   -150  /* Common dialog was canceled by user */
#define ERROR_DLG_FAILED                     -151  /* An error occured during creation of the common dialog */

#define ERROR_ISIS_NOCURSCANNER              -160  /* ISIS No Scanner selected */
#define ERROR_ISIS_SCANDRIVER_NOT_LOADED     -161  /* ISIS Scanner driver failed to load */
#define ERROR_ISIS_CANCEL                    -162  /* ISIS Operation canceled */
#define ERROR_ISIS_BAD_TAG_OR_VALUE          -163  /* ISIS Bad Tag or Bad Tag Value */
#define ERROR_ISIS_NOT_READY                 -164  /* ISIS Scanner not ready */
#define ERROR_ISIS_NO_PAGE                   -165  /* ISIS No page in the Scanner */
#define ERROR_ISIS_JAM                       -166  /* ISIS Scanner Jam error */
#define ERROR_ISIS_SCANNER_ERROR             -167  /* ISIS Scanner driver rror */
#define ERROR_ISIS_BUSY                      -168  /* ISIS Scanner is busy */
#define ERROR_ISIS_FILE_ERROR                -169  /* ISIS File driver error */
#define ERROR_ISIS_NETWORK_ERROR             -170  /* ISIS Network error */
#define ERROR_ISIS_NOT_INSTALLED             -171  /* ISIS Is not installed - you need to have ISIS installed to use this method/property */
#define ERROR_ISIS_NO_PIXDFLT                -172  /* ISIS Is not installed */
#define ERROR_ISIS_PIXVERSION                -173  /* ISIS Version is incorrect */
#define ERROR_ISIS_PERM_NOACCESS             -174  /* ISIS No permission/access */

#define ERROR_DOC_NOT_INITIALIZED            -180  /* The document was not initialized. */
#define ERROR_DOC_HANDLE                     -181  /* The document handle is NULL. */
#define ERROR_DOC_EMPTY                      -182  /* The document is empty. */
#define ERROR_DOC_INVALID_FONT               -183  /* Invalid font. */
#define ERROR_DOC_INVALID_PAGE               -184  /* Invalid page number. */
#define ERROR_DOC_INVALID_RULE               -185  /* Invalid rule. */
#define ERROR_DOC_INVALID_ZONE               -186  /* Invalid zone number. */
#define ERROR_DOC_TYPE_ZONE                  -187  /* Invalid zone type. */
#define ERROR_DOC_INVALID_COLUMN             -188  /* Invalid column number. */
#define ERROR_DOC_INVALID_LINE               -189  /* Invalid line number. */
#define ERROR_DOC_INVALID_WORD               -190  /* Invalid word number. */
#define ERROR_OCR_LOCKED                     -191  /* OCR methods are locked. */ 
#define ERROR_OCR_NOT_INITIALIZED            -192  /* The OCR engine could not be initialized. */
#define ERROR_OCR_MAX_REGIONS                -193  /* Too many zones. */
#define ERROR_OCR_OPTION                     -194  /* Invalid OCR option. */
#define ERROR_OCR_CONVERT_DIB                -195  /* Cannot convert bitmap to DIB. */
#define ERROR_OCR_CANCELED                   -196  /* OCR canceled by user. */
#define ERROR_OCR_INVALID_OUTPUT             -197  /* The OCR output is invalid. */
#define ERROR_OCR_BLOCKED                    -198  /* The OCR is blocked. */
#define ERROR_OCR_RPCMEM                     -199  /* These errors are used internally only by API code */
#define ERROR_OCR_FATAL                      -200  /* Fatal condition detected call technical support */
#define ERROR_OCR_BADTAG                     -201  /* Bad tag in tag value set */
#define ERROR_OCR_BADVAL                     -202  /* Value bad or out of range */
#define ERROR_OCR_BADTYPE                    -203  /* Wrong type used to make IO_TOKEN_T */
#define ERROR_OCR_NOFILE                     -204  /* Cannot access specified file */
#define ERROR_OCR_BADTOK                     -205  /* invalid IO_TOKEN_T */
#define ERROR_OCR_BADFMT                     -206  /* Invalid input format */
#define ERROR_OCR_BADMATCH                   -207  /* Image incompatible with IO_TOKEN_T */
#define ERROR_OCR_NOSUPPORT                  -208  /* Param combination not supported or file format legal but not supported */
#define ERROR_OCR_BADID                      -209  /* Invalid index for language/lexicon */
#define ERROR_OCR_NOLANG                     -210  /* Language not loaded/installed */
#define ERROR_OCR_LANGOVFL                   -211  /* Too many langauge packs, remove one */
#define ERROR_OCR_NOISRC                     -212  /* No image source declared */
#define ERROR_OCR_NOTIDL                     -213  /* ICR must be idle to make this call */
#define ERROR_OCR_NOVER                      -214  /* ICR not blocked on verification */
#define ERROR_OCR_NODRAW                     -215  /* ICR not blocked on  progress draw */
#define ERROR_OCR_MEMERR                     -216  /* ICR process memory error */
#define ERROR_OCR_BADRGN                     -217  /* Region index error */
#define ERROR_OCR_NOICR                      -218  /* Server not found or down */
#define ERROR_OCR_NOACTV                     -219  /* There are no active io_tokens in API */
#define ERROR_OCR_NOMORE                     -220  /* Nothing (more) to read */
#define ERROR_OCR_NOTWAIT                    -221  /* ICR must be waiting to make this call */
#define ERROR_OCR_LEXOVFL                    -222  /* Too many lexicons, remove one */
#define ERROR_OCR_PREPROC                    -223  /* Bitmap preprocessing failed */
#define ERROR_OCR_BADFILE                    -224  /* Bad file or file content associated with the passed IO_TOKEN_T */
#define ERROR_OCR_BADSCAN                    -225  /* Scanner failure */
#define ERROR_OCR_NOIMG                      -226  /* Preprocessing, Recognition, or region retrieval with no image */
#define ERROR_OCR_NOLICN                     -227  /* Licensed version of API could not acquire a license from server */
#define ERROR_OCR_NOLCSRV                    -228  /* Licensed version of API could not find license server */
#define ERROR_OCR_LMEMERR                    -229  /* Local (API library) memory error */
#define ERROR_OCR_RESCHNG                    -230  /* Image resolution change within a document too many times */
#define ERROR_OCR_BADPLGN                    -231  /* Bad Polygon used to define region extents; probably beyond the dimensions of the source image or bad vertices. */
#define ERROR_OCR_NOSINK                     -232  /* no sink token available for use with regions et. al. */
#define ERROR_OCR_NOSRC                      -233  /* no source token available for use with user defined input et. al. */
#define ERROR_OCR_NOTOK                      -234  /* unable to specify token to unblock ICR - user managed I/O "_APP" */
#define ERROR_OCR_IMBUFOVFL                  -235  /* image buffer full/overflow */
#define ERROR_OCR_TMOUT                      -236  /* timeout error on IPC to server */
#define ERROR_OCR_BADVRS                     -237  /* Server is for wrong version */
#define ERROR_OCR_TAGNNW                     -238  /* Tag cannot have value changed at this time */
#define ERROR_OCR_SRVCAN                     -239  /* Server cancelled processing on its initiative - page may be too complex for selected mode */
#define ERROR_OCR_WRFAIL                     -240  /* I/O write failed (no space) */
#define ERROR_OCR_SCNCAN                     -241  /* Scan canceled by user at scanner (using button or Scanner UI) */
#define ERROR_OCR_RGOCCLD                    -242  /* Region is totally occluded */
#define ERROR_OCR_NOTORNT                    -243  /* Could not orient text */
#define ERROR_OCR_ACCDEN                     -244  /* Access denied to this feature see your sales rep. */
#define ERROR_OCR_BADUOR                     -245  /* Invalid UOR passed to the server */

#define ERROR_RECORDING                      -250  /* Wave device is currently recording */
#define ERROR_COMPRESSOR                     -251  /* Invalid compressor */
#define ERROR_SOUND_DEVICE                   -252  /* Problem with sound card */
#define ERROR_DEVICE_INUSE                   -253  /* The sound card is currently in use */
#define ERROR_INV_TRACKTYPE                  -254  /* Invalid track for operation */
#define ERROR_NO_SOUNDCARD                   -255  /* No sound card is presend */
#define ERROR_NOT_RECORDING                  -256  /* Not currently recording */
#define ERROR_INV_MODE                       -257  /* Invalid open mode for operation */
#define ERROR_NO_VIDEO_MODULE                -258  /* No video module present on machine */
#define ERROR_QUEUE_FULL                     -259  /* The buffer queue is full */
#define ERROR_CONFIGURE_RESTART              -260  /* Configuration was successful, but you need to restart Windows */
#define ERROR_INV_HANDLE                     -261  /* Invalid handle */

#define ERROR_HOST_RESOLVE                   -270  /* Can't resolve hostname */
#define ERROR_CANT_INITIALIZE                -271  /* Can't initialize network */
#define ERROR_NO_CONNECTION                  -272  /* No open network connections */
#define ERROR_HOST_NOT_FOUND                 -273  /* Hostname not found */
#define ERROR_NOT_SERVER                     -274  /* Computer is not a server */
#define ERROR_NO_CONNECTIONS                 -275  /* No connection requests waiting */
#define ERROR_CONNECT_REFUSED                -276  /* Connection was refused */
#define ERROR_IS_CONNECTED                   -277  /* computer is already connected */
#define ERROR_NET_UNREACH                    -278  /* network is unreachable from host */
#define ERROR_TIME_OUT                       -279  /* connect attempt time out without connecting */
#define ERROR_NET_DOWN                       -280  /* network subsystem is down */
#define ERROR_NO_BUFFERS                     -281  /* no buffer space is available, too many connections*/
#define ERROR_NO_FILE_DESCR                  -282  /* no more file handle available */
#define ERROR_DATA_QUEUED                    -283  /* data has been queued to send later */
#define ERROR_UNKNOWN                        -284  /* unkown network error has occured */
#define ERROR_CONNECT_RESET                  -285  /* connection was reset - socket might be unusable */
#define ERROR_TRANSFER_ABORTED               -286  /* transfer was aborted */
#define ERROR_DSHOW_FAILURE                  -287  /* DirectShow isn't installed correctly */
#define ERROR_REGISTRY_READ                  -288  /* Error reading from the registry */
#define ERROR_WAVE_FORMAT                    -289  /* The wave format is not supported */
#define ERROR_BUFFER_TOO_SMALL               -290  /* The buffer size is too small */
#define ERROR_WAVE_CONVERT                   -291  /* Error converting the wave format */
#define ERROR_MULTIMEDIA_NOT_ENABLED         -292  /* Video capability is required to use this function */

#define ERROR_CAP_CONNECT                    -293  /* error connecting to capture device */
#define ERROR_CAP_DISCONNECT                 -294  /* error disconnecting capture device */
#define ERROR_DISK_ISFULL                    -295  /* not enough disk space */
#define ERROR_CAP_OVERLAY                    -296  /* error setting capture overlay */
#define ERROR_CAP_PREVIEW                    -297  /* error setting capture preview */
#define ERROR_CAP_COPY                       -298  /* error copying to clipboard */
#define ERROR_CAP_WINDOW                     -299  /* error with capture window */
#define ERROR_CAP_ISCAPTURING                -300  /* operation invalid during capture */
#define ERROR_NO_STREAMS                     -301  /* no streams to play */
#define ERROR_CREATE_STREAM                  -302  /* error creating streams */
#define ERROR_FRAME_DELETE                   -303  /* error deleting frames */

#define ERROR_DXF_FILTER_MISSING             -309  /* The DXF filter is needed to use this function */
#define ERROR_PAGE_NOT_FOUND                 -310  /* Page not found */
#define ERROR_DELETE_LAST_PAGE               -311  /* You cannot delete a page from a file containing only one page */
#define ERROR_NO_HOTKEY                      -312  /* There is no hotkey */
#define ERROR_CANNOT_CREATE_HOTKEY_WINDOW    -313  /* Error creating the hotkey window */
#define ERROR_MEDICAL_NOT_ENABLED            -314  /* Medical Express capability is required to use this function */
#define ERROR_JBIG_NOT_ENABLED               -315  /* JBIG capability is required to use this function */
#define ERROR_UNDO_STACK_EMPTY               -316  /* Undo stack is empty - too many undos */
#define ERROR_NO_TOOLBAR                     -317  /* ActiveX error - the toolbar window was not created */
#define ERROR_MEDICAL_NET_NOT_ENABLED        -318  /* Medical Network Express capability is required to use this function */
#define ERROR_JBIG_FILTER_MISSING            -319  /* The JBIG filter is needed to use this function */

#define ERROR_CAPTURE_STILL_IN_PROCESS          -320  /* Capture is still in progress */
#define ERROR_INVALID_DELAY                     -321  /* Invalid delay specified */
#define ERROR_INVALID_COUNT                     -322  /* Invalid capture count specified */
#define ERROR_INVALID_INTERVAL                  -323  /* Invalid interval specified */
#define ERROR_HOTKEY_CONFLICTS_WITH_CANCELKEY   -324  /* Hotkey Conflicts With Cancelkey */
#define ERROR_CAPTURE_INVALID_AREA_TYPE         -325  /* Invalid Area Type specified */
#define ERROR_CAPTURE_NO_OPTION_STRUCTURE       -326  /* Invalid or missing options strucuture */
#define ERROR_CAPTURE_INVALID_FILL_PATTERN      -327  /* Invalid fill pattern */
#define ERROR_CAPTURE_INVALID_LINE_STYLE        -328  /* Invalid line style */
#define ERROR_CAPTURE_INVALID_INFOWND_POS       -329  /* Invalid info window position */
#define ERROR_CAPTURE_INVALID_INFOWND_SIZE      -330  /* Invalid info window size */
#define ERROR_CAPTURE_ZERO_AREA_SIZE            -331  /* Zero Area Size for capture */
#define ERROR_CAPTURE_FILE_ACCESS_FAILED        -332  /* The specified filename could not be read */
#define ERROR_CAPTURE_INVALID_32BIT_EXE_OR_DLL  -333  /* The specified filename is not a valid 32bit EXE/DLL */
#define ERROR_CAPTURE_INVALID_RESOURCE_TYPE     -334  /* The specified resource type is not supported */
#define ERROR_CAPTURE_INVALID_RESOURCE_INDEX    -335  /* The index resource is out of range */
#define ERROR_CAPTURE_NO_ACTIVE_WINDOW          -336  /* No active window for capture */
#define ERROR_CAPTURE_CANNOT_CAPTURE_WINDOW     -337  /* Could not capture the window */
#define ERROR_CAPTURE_STRING_ID_NOT_DEFINED     -338  /* String ID Not Defined. */
#define ERROR_CAPTURE_DELAY_LESS_THAN_ZERO      -339  /* Delay value cannot be less than zero */
#define ERROR_CAPTURE_NO_MENU                   -340  /* No menu to capture */

#define ERROR_BROWSE_FAILED                     -350  /* directory browsing failed */
#define ERROR_NOTHING_TO_DO                     -351  /* There is nothing to do! - i.e. no files were found */
#define ERROR_INTERNET_NOT_ENABLED              -352  /* Internet capability is required to use this function */
#define ERROR_LVKRN_MISSING                     -353  /* The LVKRN DLL is needed to use this function */
#define ERROR_CMW_LOCKED                        -354  /* The CMW support is locked */
#define ERROR_CMW_FILTER_MISSING                -355  /* CMW filter is needed to use this function */
#define ERROR_CMP_FILTER_MISSING                -356  /* CMP filter is needed to use this function */
#define ERROR_FAX_FILTER_MISSING                -357  /* FAX filter is needed to use this function */

// start of MPEG specific error codes

#define ERROR_INV_HORZSIZE                      -360   /* The horizontal size is outside the specification */
#define ERROR_INV_VERTSIZE                      -361   /* The veritical size is outside the specification */   
#define ERROR_ASPECTRATIO                       -362   /* Invalid pel aspect ratio */
#define ERROR_BITRATE                           -363   /* Invalid bitrate */
#define ERROR_VBV_BUFFER                        -364   /* VBV Buffer Size is isn't valid */
#define ERROR_CHROMA_FORMAT                     -365   /* Invalid chroma format */
#define ERROR_VIDEO_FORMAT                      -366   /* Invalid video format */
#define ERROR_COLOR_PRIMARY                     -367   /* Invalid number of color primaries */
#define ERROR_TRANSFER_CHAR                     -368   /* Invalid number of transfer characteristics */
#define ERROR_MATRIX_COEFF                      -369   /* Invalid number of matrix coeeficients */
#define ERROR_DISPLAY_HORZSIZE                  -370   /* Invalid horizontal display size */
#define ERROR_DISPLAY_VERTSIZE                  -371   /* Invalid vertical display size */
#define ERROR_INTRA_DCPREC                      -372   /* Invalid Intra DC Precision */
#define ERROR_FCODE                             -373   /* Invalid f code */
#define ERROR_SRCH_WINDOW                       -374   /* Invalid motion data search window */
#define ERROR_PROFILEID                         -375   /* Invalid profile id */
#define ERROR_LEVELID                           -376   /* Invalid level id */
#define ERROR_PROFILEID_NS                      -377   /* Encoder doesn't support scalabale bitstreams */
#define ERROR_INV_COMBINATION                   -378   /* Undefined Profile & Level id combination */
#define ERROR_BPIC_NOTALLOWED                   -379   /* B Pictures not allowed */
#define ERROR_RPTFIRST_MUSTBEZERO               -380   /* Repeat first must be zero */
#define ERROR_FRAME_RATE                        -381   /* Invalid frame rate */

// end MPEG specific error codes

#define ERROR_VECTOR_NOT_ENABLED                -400  /* Vector capability is required to use this function */
#define ERROR_VECTOR_DXF_NOT_ENABLED            -401  /* Vector DXF capability is required to use this function */
#define ERROR_VECTOR_DWG_NOT_ENABLED            -402  /* Vector DWG capability is required to use this function */
#define ERROR_VECTOR_MISC_NOT_ENABLED           -403  /* Vector Misc capability is required to use this function */
#define ERROR_TAG_MISSING                       -404  /* Tag not found */
#define ERROR_VECTOR_DWF_NOT_ENABLED            -405  /* Vector DWF capability is required to use this function */
#define ERROR_NO_UNDO_STACK                     -406  /* There is no undo stack */
#define ERROR_UNDO_DISABLED                     -407  /* The undo is disabled */
#define ERROR_PDF_NOT_ENABLED                   -408  /* PDF capability is required to use this function */
#define ERROR_ENTENSIONS_MISSING                -409  /* EXIF extensions are missing */
#define ERROR_BARCODE_DIGIT_CHECK               -410  /* Invalid error check digit */
#define ERROR_BARCODE_INVALID_TYPE              -411  /* Invalid bar code type */
#define ERROR_BARCODE_TEXTOUT                   -412  /* Invalid bar code text out option */
#define ERROR_BARCODE_WIDTH                     -413  /* Invalid bar code width */
#define ERROR_BARCODE_HEIGHT                    -414  /* Invalid bar code height */
#define ERROR_BARCODE_TOSMALL                   -415  /* Bar code string is too small */
#define ERROR_BARCODE_STRING                    -416  /* Invalid bar code string for a specified bar code type */
#define ERROR_BARCODE_NOTFOUND                  -417  /* No bar code recognition */
#define ERROR_BARCODE_UNITS                     -418  /* Invalid bar code measurement unit */
#define ERROR_BARCODE_MULTIPLEMAXCOUNT          -419  /* Invalid multiple max count */
#define ERROR_BARCODE_GROUP                     -420  /* Invalid bar code group */
#define ERROR_BARCODE_NO_DATA                   -421  /* Invalid BARCODEDATA structure */
#define ERROR_BARCODE_NOTFOUND_DUPLICATED       -422  /* No duplicated bar code */
#define ERROR_BARCODE_LAST_DUPLICATED           -423  /* Reached the last duplicated bar code */
#define ERROR_BARCODE_STRING_LENGTH             -424  /* Invalid bar code data string length */
#define ERROR_BARCODE_LOCATION                  -425  /* Invalid bar code area location */
#define ERROR_BARCODE_1D_LOCKED                 -426  /* Bar Code 1D is locked */
#define ERROR_BARCODE_2D_READ_LOCKED            -427  /* Bar Code Read 2D (CodeOne) is locked */
#define ERROR_BARCODE_2D_WRITE_LOCKED           -428  /* Bar Code Write 2D (CodeOne) is locked */
#define ERROR_BARCODE_PDF_READ_LOCKED           -429  /* Bar Code Read PDF is locked */
#define ERROR_BARCODE_PDF_WRITE_LOCKED          -430  /* Bar Code Write PDF is locked */
#define ERROR_BARCODE_FOUNDCORRUPT              -431  /* Barcode PDF417 symbol is found but cannot read successfully */
#define ERROR_BARCODE_DATAMATRIX_READ_LOCKED    -432  /* Bar Code Read DataMatrix is locked */
#define ERROR_BARCODE_DATAMATRIX_WRITE_LOCKED   -433  /* Bar Code Write DataMatrix is locked */

#define ERROR_NET_FIRST                            -435
#define ERROR_NET_OUT_OF_HANDLES                   -435
#define ERROR_NET_TIMEOUT                          -436
#define ERROR_NET_EXTENDED_ERROR                   -437
#define ERROR_NET_INTERNAL_ERROR                   -438
#define ERROR_NET_INVALID_URL                      -439
#define ERROR_NET_UNRECOGNIZED_SCHEME              -440
#define ERROR_NET_NAME_NOT_RESOLVED                -441
#define ERROR_NET_PROTOCOL_NOT_FOUND               -442
#define ERROR_NET_INVALID_OPTION                   -443
#define ERROR_NET_BAD_OPTION_LENGTH                -444
#define ERROR_NET_OPTION_NOT_SETTABLE              -445
#define ERROR_NET_SHUTDOWN                         -446
#define ERROR_NET_INCORRECT_USER_NAME              -447
#define ERROR_NET_INCORRECT_PASSWORD               -448
#define ERROR_NET_LOGIN_FAILURE                    -449
#define ERROR_NET_INVALID_OPERATION                -450
#define ERROR_NET_OPERATION_CANCELLED              -451
#define ERROR_NET_INCORRECT_HANDLE_TYPE            -452
#define ERROR_NET_INCORRECT_HANDLE_STATE           -453
#define ERROR_NET_NOT_PROXY_REQUEST                -454
#define ERROR_NET_REGISTRY_VALUE_NOT_FOUND         -455
#define ERROR_NET_BAD_REGISTRY_PARAMETER           -456
#define ERROR_NET_NO_DIRECT_ACCESS                 -457
#define ERROR_NET_NO_CONTEXT                       -458
#define ERROR_NET_NO_CALLBACK                      -459
#define ERROR_NET_REQUEST_PENDING                  -460
#define ERROR_NET_INCORRECT_FORMAT                 -461
#define ERROR_NET_ITEM_NOT_FOUND                   -462
#define ERROR_NET_CANNOT_CONNECT                   -463
#define ERROR_NET_CONNECTION_ABORTED               -464
#define ERROR_NET_CONNECTION_RESET                 -465
#define ERROR_NET_FORCE_RETRY                      -466
#define ERROR_NET_INVALID_PROXY_REQUEST            -467
#define ERROR_NET_NEED_UI                          -468
#define ERROR_NET_HANDLE_EXISTS                    -469
#define ERROR_NET_SEC_CERT_DATE_INVALID            -470
#define ERROR_NET_SEC_CERT_CN_INVALID              -471
#define ERROR_NET_HTTP_TO_HTTPS_ON_REDIR           -472
#define ERROR_NET_HTTPS_TO_HTTP_ON_REDIR           -473
#define ERROR_NET_MIXED_SECURITY                   -474
#define ERROR_NET_CHG_POST_IS_NON_SECURE           -475
#define ERROR_NET_POST_IS_NON_SECURE               -476
#define ERROR_NET_CLIENT_AUTH_CERT_NEEDED          -477
#define ERROR_NET_INVALID_CA                       -478
#define ERROR_NET_CLIENT_AUTH_NOT_SETUP            -479
#define ERROR_NET_ASYNC_THREAD_FAILED              -480
#define ERROR_NET_REDIRECT_SCHEME_CHANGE           -481
#define ERROR_NET_DIALOG_PENDING                   -482
#define ERROR_NET_RETRY_DIALOG                     -483
#define ERROR_NET_HTTPS_HTTP_SUBMIT_REDIR          -484
#define ERROR_NET_INSERT_CDROM                     -485
#define ERROR_NET_HTTP_HEADER_NOT_FOUND            -486
#define ERROR_NET_HTTP_DOWNLEVEL_SERVER            -487
#define ERROR_NET_HTTP_INVALID_SERVER_RESPONSE     -488
#define ERROR_NET_HTTP_INVALID_HEADER              -489
#define ERROR_NET_HTTP_INVALID_QUERY_REQUEST       -490
#define ERROR_NET_HTTP_HEADER_ALREADY_EXISTS       -491
#define ERROR_NET_HTTP_REDIRECT_FAILED             -492
#define ERROR_NET_HTTP_NOT_REDIRECTED              -493
#define ERROR_NET_HTTP_COOKIE_NEEDS_CONFIRMATION   -494
#define ERROR_NET_HTTP_COOKIE_DECLINED             -495
#define ERROR_NET_HTTP_REDIRECT_NEEDS_CONFIRMATION -496
#define ERROR_NET_NO_OPEN_REQUEST                  -497

// start VECTOR error codes

#define ERROR_VECTOR_IS_LOCKED                  -500     /* Vector handle is locked */
#define ERROR_VECTOR_IS_EMPTY                   -501     /* Vector is empty */
#define ERROR_VECTOR_LAYER_NOT_FOUND            -502     /* Layer is not found */
#define ERROR_VECTOR_LAYER_IS_LOCKED            -503     /* Layer is locked */
#define ERROR_VECTOR_LAYER_ALREADY_EXISTS       -504     /* Layer already exists */
#define ERROR_VECTOR_OBJECT_NOT_FOUND           -505     /* Object is not found */
#define ERROR_VECTOR_INVALID_OBJECT_TYPE        -506     /* Invalid object type */
#define ERROR_VECTOR_PEN_NOT_FOUND              -507     /* Pen is not found */
#define ERROR_VECTOR_BRUSH_NOT_FOUND            -508     /* Brush is not found */
#define ERROR_VECTOR_FONT_NOT_FOUND             -509     /* Font is not found */
#define ERROR_VECTOR_BITMAP_NOT_FOUND           -510     /* Bitmap is not found */
#define ERROR_VECTOR_POINT_NOT_FOUND            -511     /* Point is not found */
#define ERROR_VECTOR_ENGINE_NOT_FOUND           -512     /* Vector engine not found */
#define ERROR_VECTOR_INVALID_ENGINE             -513     /* Invalid vector engine */
#define ERROR_VECTOR_CLIPBOARD                  -514     /* Clipboard error */
#define ERROR_VECTOR_CLIPBOARD_IS_EMPTY         -515     /* Clipboard is empty */
#define ERROR_VECTOR_CANT_ADD_TEXT              -516     /* Cannot add text */
#define ERROR_VECTOR_CANT_READ_WMF              -517     /* Cannot read WMF */
#define ERROR_VECTOR_GROUP_NOT_FOUND            -518     /* Group is not found */
#define ERROR_VECTOR_GROUP_ALREADY_EXISTS       -519     /* Group already exists */

// end VECTOR error codes


// start JPEG2000 error codes 

#define ERROR_JP2_FAILURE                       -530  /* Error in JP2 Box values */
#define ERROR_JP2_SIGNATURE                     -531  /* The header does not match the JP2 signature - not a JP2 file */
#define ERROR_JP2_UNSUPPORTED                   -532  /* JP2 file has a feature that is usupported */
#define ERROR_J2K_FAILURE                       -533  /* Invalid save options were specified to the encoder */
#define ERROR_J2K_NO_SOC                        -534  /* File header does not contain SOC marker */
#define ERROR_J2K_NO_SOT                        -535  /* File contains complete header but no compressed image data */
#define ERROR_J2K_INFORMATION_SET               -536  /* Invalid save options were specified or file includes invalid encoded values */
#define ERROR_J2K_LOW_TARGET_SIZE               -537  /* Compression ratio, target file size, or tile size was too small for encoder */
#define ERROR_J2K_DECOMPOSITION_LEVEL           -538  /* Specified Wavelet decomposition level was too high */
#define ERROR_J2K_MARKER_VALUE                  -539  /* Decoder could not translate J2K marker - file is corrupt or invalid */
#define ERROR_J2K_UNSUPPORTED                   -540  /* J2K file has image with more than 30 bits per component */
#define ERROR_J2K_FILTER_MISSING                -541  /* J2K filter is needed to use this function */
#define ERROR_J2K_LOCKED                        -542  /* J2K support is locked */

// end JPEG2000 error codes

// start of twain toolkit error codes

#define ERROR_TWAIN_NO_LIBRARY                  -560
#define ERROR_TWAIN_NOT_AVAILABLE               ERROR_TWAIN_NO_LIBRARY
#define ERROR_TWAIN_INVALID_DLL                 -561
#define ERROR_TWAIN_NOT_INITIALIZED             -562
#define ERROR_TWAIN_CANCELED                    -563
#define ERROR_TWAIN_CHECK_STATUS                -564
#define ERROR_TWAIN_END_OF_LIST                 -565
#define ERROR_TWAIN_CAP_NOT_SUPPORTED           -566
#define ERROR_TWAIN_SOURCE_NOT_OPEN             -567
#define ERROR_TWAIN_BAD_VALUE                   -568
#define ERROR_TWAIN_INVALID_STATE               -569
#define ERROR_TWAIN_CAPS_NEG_NOT_ENDED          -570
#define ERROR_TWAIN_OPEN_FILE                   -571
#define ERROR_TWAIN_INV_HANDLE                  -572
#define ERROR_TWAIN_WRITE_TO_FILE               -573
#define ERROR_TWAIN_INV_VERSION_NUM             -574
#define ERROR_TWAIN_READ_FROM_FILE              -575
#define ERROR_TWAIN_NOT_VALID_FILE              -576
#define ERROR_TWAIN_INV_ACCESS_RIGHT            -577
#define ERROR_TWAIN_CUSTOMBASE                  -578
#define ERROR_TWAIN_DENIED                      -579
#define ERROR_TWAIN_FILEEXISTS                  -580
#define ERROR_TWAIN_FILENOTFOUND                -581
#define ERROR_TWAIN_NOTEMPTY                    -582
#define ERROR_TWAIN_PAPERJAM                    -583
#define ERROR_TWAIN_PAPERDOUBLEFEED             -584
#define ERROR_TWAIN_FILEWRITEERROR              -585
#define ERROR_TWAIN_CHECKDEVICEONLINE           -586

#define ERROR_TWAIN_STOP_ENUMERATION            SUCCESS_ABORT
#define ERROR_TWAIN_STOP_SCAN                   -587

// end of twain toolkit error codes 

// start PaintTools error codes

#define ERROR_PAINT_INTERNAL                    -600   /* Internal error (Call LEAD) */
#define ERROR_PAINT_INV_DATA                    -601   /* Internal error (Call LEAD) */
#define ERROR_PAINT_NO_RESOURCES                -602   /* Internal error (Call LEAD) */
#define ERROR_PAINT_NOT_ENABLED                 -603   /* DigitalPaint capability is required to use this function */

// end PaintTools error codes


// start Container error codes

#define ERROR_CONTAINER_INV_HANDLE              -630
#define ERROR_CONTAINER_INV_OPERATION           -631
#define ERROR_CONTAINER_NO_RESOURCES            -632

// end Container error codes


// start Toolbar error codes

#define ERROR_TOOLBAR_NO_RESOURCES              -660
#define ERROR_TOOLBAR_INV_STATE                 -661
#define ERROR_TOOLBAR_INV_HANDLE                -662

// end Toolbar error codes


// start Automation error codes

#define ERROR_AUTOMATION_INV_HANDLE             -690
#define ERROR_AUTOMATION_INV_STATE              -691

// end Automation error codes

// start Segmentation errors

#define ERROR_INV_SEG_HANDLE                    -700
#define ERROR_INV_SEG_DATA                      -701
#define ERROR_INV_LAYER_DATA                    -702
#define ERROR_MRC_NOT_ALLOCATED                 -703
#define ERROR_INV_MIN_SEGMENT                   -704
#define ERROR_SEGMENTATION_FAILURE              -705
#define ERROR_MRC_INV_PAGE                      -706

// end Segmentation errors

// Start Pdf Errors 

//#define ERROR_PDF_NOT_ENABLED                 -408  
#define ERROR_PDF_FILE_ENCRYPTED                -721  /* The Pdf file is encrypted and the szPassword 
                                                         member of the FILEPDFOPTIONS is not set 
                                                         (no password). */
#define ERROR_PDF_INVALID_PASSWORD              -722  /* Invalid password specified */
#define ERROR_PDF_FAX_NOT_ENABLED               -723  /* LFFAX is required for this function */
#define ERROR_PDF_JPEG_NOT_ENABLED              -724  /* LFCMP is required for this function */
#define ERROR_PDF_INV_DOC_STRUCTURING_COMMENTS  -725  /* Invalid Document Structuring comments (Ps and EPS)*/
#define ERROR_PDF_FONTS_DIRECTORY_NOT_FOUND     -726  /* Could not find Fonts directory */
#define ERROR_PDF_CANNOT_EDIT_FILE              -727  /* Cannot insert, delete, append or replace pages. */
#define ERROR_PDF_BAD_CONTENT                   -728  /* File is corrupted */
#define ERROR_PDF_BAD_INITIALIZATION_FILES      -729  /* Either the files required for initializing the PDF engine were 
                                                         not found or they were found but they are incorrect. */
// Start ISAPI Errors
#define ERROR_ISAPI_CONFIG_NOT_FOUND            -740  /* Config Not Found In Registry*/
#define ERROR_ISAPI_DSN_NOT_FOUND               -741  /* DSN Not Found In ODBC*/
#define ERROR_ISAPI_SQL_EXEC                    -742  /* Table Or Fields Not Found In Database*/
#define ERROR_ISAPI_RECORD_NOT_FOUND            -743  /* Record Not Found In Database*/
#define ERROR_ISAPI_DATABASE_SETTING            -744  /* Error On Database Settings in Registry*/
#define ERROR_ISAPI_DATABASE_SAVE_BITMAP        -745  /* Can't Save Bitmap in Database */
#define ERROR_ISAPI_DATABASE_RECORD_DUPLICATE   -746  /* Record is Alredy Exist in Database , 
                                                         Doublecat In Primary Key*/
#define ERROR_ISAPI_SESSION_FULL                -747  /* Can't Add User To ISAPI SESSION*/
#define ERROR_ISAPI_CACHE_SYSTEM_NOT_ENABLED    -748  /* The caching system not enabled in 
                                                         Configuration Settings*/
#define ERROR_ISAPI_CACHE_MAX_SIZE              -749  /* The maximum size of cache limit*/
#define ERROR_ISAPI_CACHE_SETTING               -750  /* Error On Cache System Settings in Registry */
// end ISAPI errors

// Start SVG errors
#define ERROR_SVG_FILE_SIZE_READ                -770
#define ERROR_SVG_ROOT_NOT_SVG                  -771
#define ERROR_SVG_NOFOUND_ROOT_ELEMENT          -772
#define ERROR_SVG_INV_ELEMENT                   -773
#define ERROR_SVG_DUPLICATED_ATTRIBUTE          -774
#define ERROR_SVG_INV_ATTRIBUTE                 -775
#define ERROR_SVG_INV_ATTRIBUTE_VALUE           -776
#define ERROR_SVG_BAD_CSS_PROPERTY              -777
#define ERROR_SVG_MISSING_REQUIRED_ATTRIBUTE    -778
#define ERROR_SVG_DUPLICATED_ID                 -779
#define ERROR_SVG_INV_COORDINATES_NUMBER        -780
#define ERROR_SVG_INV_STRING_COMMA              -781
// End SVG errors

// start ColorSpace SDK errors
#define ERROR_INVALID_FORMAT                               -785
#define ERROR_UNSUPPORTED_METHOD                           -786
#define ERROR_OPENING_PROFILE                              -787
#define ERROR_INVALID_COLOR_PROFILE                        -788
#define ERROR_INVALID_STRUCT_SIZE                          -789
/*#define ERROR_INVALID_PRAMETER_VALUE                     -790 -- duplicate, use ERROR_INV_PARAMETER instead*/
#define ERROR_U_V_NOT_MULTIPLES                            -791
#define ERROR_NO_NONPLANAR_VERTICAL_SUBSAMPLING_SUPPORTED  -792
#define ERROR_PLANAR_ALIGNMENT_NOT_SUPPORTED               -793
#define ERROR_UNSUPPORTED_CONVERSION                       -794
#define ERROR_TRUNCATE_HEIGHT                              -795
#define ERROR_TRUNCATE_WIDTH                               -796
#define ERROR_TRUNCATE_WIDTH_AND_HEIGHT                    -797
// end ColorSpace SDK errors

#define ERROR_LAYER_MISSING                     -800  /* The PSD Layer is missing */
#define ERROR_BAD_MARKER                        -801  /* Bad JPEG marker */
#define ERROR_AUDIO_MISSING                     -802  /* The audio data is not present */
#define ERROR_DICOM_NOT_ENABLED                 -803  /* DICOM support is required to use this function */
#define ERROR_EXTGRAY_NOT_ENABLED               -804  /* Extended grayscale support is required to use this function */
#define ERROR_FILE_READONLY                     -805  /* File is read-only. Cannot open file with write access */
#define ERROR_BAD_RESYNC_MARKER                 -806  /* Bad JPEG Resync marker */
#define ERROR_LTCLR_MISSING                     -807  /* LTCLR DLL is missing */
#define ERROR_MARKER_SIZE_TOO_BIG               -808  /* The size of the JPEG marker cannot exceed 64K */
#define ERROR_MARKER_MISSING                    -809  /* The required JPEG marker is missing */
#define ERROR_EXTENSIONS_MISSING                -810  /* This file does not contain Exif extensions */
#define ERROR_MARKER_INDEX                      -811  /* The marker index is invalid (too big) */
#define ERROR_NO_PROFILE                        -812  /* The ICC profile was not found */
#define ERROR_DECODING_PROFILE                  -813  /* An error has occured while decoding the profile */

#define ERROR_LTCLR_DLL_NOTLOADED       -900  /* The LTCLR DLL is not loaded */
#define ERROR_LTDLGRES_DLL_NOTLOADED    -901  /* The LDLGRES DLL is not loaded */
#define ERROR_LTDLG_COLOR_NOTINITIALIZE -902  /* You must initialize LTDLG using L_DlgInit */ 

#define ERROR_IMAGE_SIZE   -910  /* Image size not sufficient */
#define ERROR_NO_MESSAGE   -911  /* There is no message.*/
#define ERROR_INV_PASSWORD -912  /* Invalid password.*/

#define ERROR_TIFF_COMMAND_NOT_ALLOWED          -913  /* The specified TIFF command is not allowed */
#define ERROR_BAD_TIFF_TAG_VALUE                -914  /* Bad TIFF Tag value. */
#define ERROR_NOT_MULTIPAGE_TIFF_FILE           -915  /* Not Multi-Page TIFF file. */
#define ERROR_DELETE_TIFF_FILE_NOT_ALLOWED      -916  /* Not allowed to delete the TIFF file. */

#define ERROR_LTPRO_NOT_ENABLED                 -930  /* LEADTOOLS Pro Features are not enabled */

#define ERROR_EPRINT_LOCKED                     -1000 /* ePrint is locked, Please execute a License Agreement.*/

#endif                          /* _LTERR_H_ */
