Attribute VB_Name = "OcxAddon"

' These are the constants, structures and functions recomended
' for using the LEADTOOLS DLL functions with OCX (16 and 32 bit)

'********* unlock keys for L_UnlockSupport ******'
Global Const L_KEY_DOCUMENT = ""
Global Const L_KEY_GIFLZW = ""
Global Const L_KEY_TIFLZW = ""
Global Const L_KEY_FPXEXTENSIONS = ""
Global Const L_KEY_OCR = ""
Global Const L_KEY_MULTIMEDIA = ""
Global Const L_KEY_MEDICAL = ""
Global Const L_KEY_MEDICAL_NET = ""
Global Const L_KEY_VECTOR = ""
Global Const L_KEY_BARCODES_1D = ""
Global Const L_KEY_BARCODES_2D_READ = ""
Global Const L_KEY_BARCODES_2D_WRITE = ""
Global Const L_KEY_BARCODES_PDF_READ = ""
Global Const L_KEY_BARCODES_PDF_WRITE = ""
Global Const L_KEY_INTERNET = ""
Global Const L_KEY_VECTOR_DWG = ""
Global Const L_KEY_VECTOR_DXF = ""
Global Const L_KEY_VECTOR_MISC = ""
Global Const L_KEY_VECTOR_ALL = ""
Global Const L_KEY_VECTOR_DWF = ""
Global Const L_KEY_MRC = ""
Global Const L_KEY_PDF = ""
Global Const L_KEY_VECTOR_VIEW = ""
Global Const L_KEY_J2K = ""
Global Const L_KEY_CMW = ""
Global Const L_KEY_DICOM = ""
Global Const L_KEY_EXTGRAY = ""
Global Const L_KEY_BITONAL = ""
Global Const L_KEY_MEDICAL_SECURITY = ""
Global Const L_KEY_PDF_SAVE = ""
Global Const L_KEY_OCR_PDF_SUPPORT = ""
Global Const L_KEY_BARCODES_DATAMATRIX_READ = ""
Global Const L_KEY_BARCODES_DATAMATRIX_WRITE = ""

Global Const L_SUPPORT_DOCUMENT = 0
Global Const L_SUPPORT_GIFLZW = 1
Global Const L_SUPPORT_TIFLZW = 2
Global Const L_SUPPORT_FPXEXTENSIONS = 3
Global Const L_SUPPORT_OCR = 4
Global Const L_SUPPORT_MULTIMEDIA = 5
Global Const L_SUPPORT_MEDICAL = 6
Global Const L_SUPPORT_VECTOR = 7
Global Const L_SUPPORT_MEDICAL_NET = 8
Global Const L_SUPPORT_BARCODES_1D = 9
Global Const L_SUPPORT_BARCODES_2D_READ = 10
Global Const L_SUPPORT_BARCODES_2D_WRITE = 11
Global Const L_SUPPORT_BARCODES_PDF_READ = 12
Global Const L_SUPPORT_BARCODES_PDF_WRITE = 13
Global Const L_SUPPORT_INTERNET = 14
Global Const L_SUPPORT_VECTOR_DWG = 15
Global Const L_SUPPORT_VECTOR_DXF = 16
Global Const L_SUPPORT_VECTOR_MISC = 17
Global Const L_SUPPORT_VECTOR_ALL = 18
Global Const L_SUPPORT_VECTOR_DWF = 19
Global Const L_SUPPORT_MRC = 20
Global Const L_SUPPORT_PDF = 21
Global Const L_SUPPORT_VECTOR_VIEW = 22
Global Const L_SUPPORT_DIGITALPAINT = 23
Global Const L_SUPPORT_J2K = 24
Global Const L_SUPPORT_CMW = 25
Global Const L_SUPPORT_DICOM = 26
Global Const L_SUPPORT_EXTGRAY = 27
Global Const L_SUPPORT_BITONAL = 28
Global Const L_SUPPORT_MEDICAL_SECURITY = 29
Global Const L_SUPPORT_PDF_SAVE = 30
Global Const L_SUPPORT_OCR_PDF_OUTPUT = 31
Global Const L_SUPPORT_BARCODES_DATAMATRIX_READ = 32
Global Const L_SUPPORT_BARCODES_DATAMATRIX_WRITE = 33
Global Const L_SUPPORT_MAX = 33

'******** LEADTools VB Addon Error Codes ********'
' Error codes returned by LEAD DLL functions

Global Const L_SUCCESS_IGNOREMARKER = 5   ' Function successful. Ignore this marker
Global Const L_SUCCESS_RETRY = 4          ' Function successful. Retry doing the failed op.
Global Const L_SUCCESS_DELETE = 3         ' Function successful. Delete file before quiting
Global Const L_SUCCESS_ABORT = 2          ' Function successful. You can quit now.
Global Const L_SUCCESS = 1                ' Function successful
Global Const L_FAILURE = 0                ' Function not successful
Global Const L_ERROR_NO_MEMORY = -1       'not enough memory
Global Const L_ERROR_NO_BITMAP = -2       'invalid bitmap handle
Global Const L_ERROR_MEMORY_TOO_LOW = -3  'not enough memory
Global Const L_ERROR_FILE_LSEEK = -4      'error seeking
Global Const L_ERROR_FILE_WRITE = -5      'error writing
Global Const L_ERROR_FILE_GONE = -6       'file not present
Global Const L_ERROR_FILE_READ = -7       'error reading
Global Const L_ERROR_INV_FILENAME = -8    'invalid filename
Global Const L_ERROR_FILE_FORMAT = -9     'invalid file format
Global Const L_ERROR_FILENOTFOUND = -10   'file not found
Global Const L_ERROR_INV_RANGE = -11      'invalid width/height
Global Const L_ERROR_IMAGE_TYPE = -12     'format recognized, but sub-type not supported
Global Const L_ERROR_INV_PARAMETER = -13  'invalid parameter passed
Global Const L_ERROR_FILE_OPEN = -14      'not able to open file
Global Const L_ERROR_UNKNOWN_COMP = -15   'unknown compression format
Global Const L_ERROR_FEATURE_NOT_SUPPORTED = -16  'feature not supported
Global Const L_ERROR_NOT_256_COLOR = -17  'VGA card only supports 256 colors
Global Const L_ERROR_PRINTER = -18        'printer error
Global Const L_ERROR_CRC_CHECK = -19      'data crc check error
Global Const L_ERROR_QFACTOR = -21        'invalid QFactor (out of range or a preset w/ non-LEAD)
Global Const L_ERROR_TARGAINSTALL = -22   'TARGA not installed
Global Const L_ERROR_OUTPUTTYPE = -23     'invalid compression format
Global Const L_ERROR_XORIGIN = -24        'invalid X origin
Global Const L_ERROR_YORIGIN = -25        'invalid Y origin
Global Const L_ERROR_VIDEOTYPE = -26      'invalid video mode
Global Const L_ERROR_BITPERPIXEL = -27    'invalid bits/pixel
Global Const L_ERROR_WINDOWSIZE = -28     'invalid window size
Global Const L_ERROR_NORMAL_ABORT = -29   'escape key pressed
Global Const L_ERROR_NOT_INITIALIZED = -30 'internal
Global Const L_ERROR_CU_BUSY = -31        'internal
Global Const L_ERROR_INVALID_TABLE_TYPE = -32 'internal
Global Const L_ERROR_UNEQUAL_TABLES = -33 'internal
Global Const L_ERROR_INVALID_BUFFER = -34 'internal
Global Const L_ERROR_MISSING_TILE_DATA = -35  'internal
Global Const L_ERROR_INVALID_QVALUE = -36 'internal
Global Const L_ERROR_INVALIDDATA = -37   'internal
Global Const L_ERROR_INVALID_COMPRESSED_TYPE = -38 'internal
Global Const L_ERROR_INVALID_COMPONENT_NUM = -39   'internal
Global Const L_ERROR_INVALID_PIXEL_TYPE = -40      'internal
Global Const L_ERROR_INVALID_PIXEL_SAMPLING = -41  'internal
Global Const L_ERROR_INVALID_SOURCE_FILE = -42     'internal
Global Const L_ERROR_INVALID_TARGET_FILE = -43     'internal
Global Const L_ERROR_INVALID_IMAGE_DIMS = -44      'internal
Global Const L_ERROR_INVALID_TILE_DIMS = -45       'internal
Global Const L_ERROR_INVALID_PIX_BUFF_DIMS = -46   'internal
Global Const L_ERROR_SEGMENT_OVERFLOW = -47        'internal
Global Const L_ERROR_INVALID_SUBSAMPLING = -48     'internal
Global Const L_ERROR_INVALID_Q_VIS_TABLE = -49     'internal
Global Const L_ERROR_INVALID_DC_CODE_TABLE = -50   'internal
Global Const L_ERROR_INVALID_AC_CODE_TABLE = -51   'internal
Global Const L_ERROR_INSUFFICIENT_DATA = -52       'internal
Global Const L_ERROR_MISSING_FUNC_POINTER = -53    'internal
Global Const L_ERROR_TOO_MANY_DC_CODE_TABLES = -54 'internal
Global Const L_ERROR_TOO_MANY_AC_CODE_TABLES = -55 'internal
Global Const L_ERROR_INVALID_SUBIMAGE = -56        'internal
Global Const L_ERROR_INVALID_ABORTION = -57        'internal
Global Const L_ERROR_CU_NO_SUPPORT = -58           'internal
Global Const L_ERROR_CU_FAILURE = -59              'internal
Global Const L_ERROR_BAD_POINTER = -60             'internal
Global Const L_ERROR_HEADER_DATA_FAILURE = -61     'internal
Global Const L_ERROR_COMPRESSED_DATA_FAILURE = -62 'internal
Global Const L_ERROR_FIXEDPAL_DATA = -63     'fixed palette data not found
Global Const L_ERROR_LOADFONT_DATA = -64     'font data not found
Global Const L_ERROR_NO_STAMP = -65          'stamp not found
Global Const L_ERROR_G3CODE_INVALID = -70    'invalid group 3 data
Global Const L_ERROR_G3CODE_EOF = -71        'group 3 code end of file
Global Const L_ERROR_G3CODE_EOL = -72        'group 3 code end of code
Global Const L_ERROR_PREMATURE_EOF = -73     'premature EOF at scan line
Global Const L_ERROR_PREMATURE_EOL = -74     'premature EOL code
Global Const L_ERROR_UNCOMP_EOF = -75        'premature EOF
Global Const L_ERROR_ACT_INCOMP = -76        'premature EOL
Global Const L_ERROR_BAD_DECODE_STATE = -77  'premature EOL
Global Const L_ERROR_VERSION_NUMBER = -78    'bad version number
Global Const L_ERROR_TWAIN_NODSM = -79       'source manager not found
Global Const L_ERROR_TWAIN_BUMMER = -80      'Failure due to unknown causes
Global Const L_ERROR_TWAIN_LOWMEMORY = -81   'Not enough memory to perform operation
Global Const L_ERROR_TWAIN_NODS = -82        'No Data Source
Global Const L_ERROR_TWAIN_MAXCONNECTIONS = -83  ' DS is connected to max possible apps
Global Const L_ERROR_TWAIN_OPERATIONERROR = -84  ' DS or DSM reported error, app shouldn't
Global Const L_ERROR_TWAIN_BADCAP = -85      'Unknown capability
Global Const L_ERROR_TWAIN_BADPROTOCOL = -86 'Unrecognized MSG DG DAT combination
Global Const L_ERROR_TWAIN_BADVALUE = -87    'Data parameter out of range
Global Const L_ERROR_TWAIN_SEQERROR = -88    'DG DAT MSG out of expected sequence
Global Const L_ERROR_TWAIN_BADDEST = -89     'Unknown destination App/Src in DSM_Entry
Global Const L_ERROR_TWAIN_CANCEL = -90      'Operation was cancelled
Global Const L_ERROR_PANWINDOW_NOT_CREATED = -91 ' PanWindow was not created
Global Const L_ERROR_NOT_ENOUGH_IMAGES = -92 'Not enough images

Global Const L_ERROR_USER_ABORT = -100       'User has aborted operation

Global Const L_ERROR_FPX_INVALID_FORMAT_ERROR = -101          ' FlashPix errors
Global Const L_ERROR_FPX_FILE_WRITE_ERROR = -102
Global Const L_ERROR_FPX_FILE_READ_ERROR = -103
Global Const L_ERROR_FPX_FILE_NOT_FOUND = -104
Global Const L_ERROR_FPX_COLOR_CONVERSION_ERROR = -105
Global Const L_ERROR_FPX_SEVER_INIT_ERROR = -106
Global Const L_ERROR_FPX_LOW_MEMORY_ERROR = -107
Global Const L_ERROR_FPX_IMAGE_TOO_BIG_ERROR = -108
Global Const L_ERROR_FPX_INVALID_COMPRESSION_ERROR = -109
Global Const L_ERROR_FPX_INVALID_RESOLUTION = -110
Global Const L_ERROR_FPX_INVALID_FPX_HANDLE = -111
Global Const L_ERROR_FPX_TOO_MANY_LINES = -112
Global Const L_ERROR_FPX_BAD_COORDINATES = -113
Global Const L_ERROR_FPX_FILE_SYSTEM_FULL = -114
Global Const L_ERROR_FPX_MISSING_TABLE = -115
Global Const L_ERROR_FPX_RETURN_PARAMETER_TOO_LARGE = -116
Global Const L_ERROR_FPX_NOT_A_VIEW = -117
Global Const L_ERROR_FPX_VIEW_IS_TRANFORMLESS = -118
Global Const L_ERROR_FPX_ERROR = -119
Global Const L_ERROR_FPX_UNIMPLEMENTED_FUNCTION = -120
Global Const L_ERROR_FPX_INVALID_IMAGE_DESC = -121
Global Const L_ERROR_FPX_INVALID_JPEG_TABLE = -122
Global Const L_ERROR_FPX_ILLEGAL_JPEG_ID = -123
Global Const L_ERROR_FPX_MEMORY_ALLOCATION_FAILED = -124
Global Const L_ERROR_FPX_NO_MEMORY_MANAGEMENT = -125
Global Const L_ERROR_FPX_OBJECT_CREATION_FAILED = -126
Global Const L_ERROR_FPX_EXTENSION_FAILED = -127
Global Const L_ERROR_FPX_FREE_NULL_PTR = -128
Global Const L_ERROR_FPX_INVALID_TILE = -129
Global Const L_ERROR_FPX_FILE_IN_USE = -130
Global Const L_ERROR_FPX_FILE_CREATE_ERROR = -131
Global Const L_ERROR_FPX_FILE_NOT_OPEN_ERROR = -132
Global Const L_ERROR_FPX_USER_ABORT = -133
Global Const L_ERROR_FPX_OLE_FILE_ERROR = -134
Global Const L_ERROR_BAD_TAG = -140 ' Bad TIFF tag
Global Const L_ERROR_INVALID_STAMP_SIZE = -141 ' stamp size is too big or invalid bits/pixel, etc
Global Const L_ERROR_BAD_STAMP = -142 ' Stamp is present but data is corrupted
Global Const L_ERROR_DOCUMENT_NOT_ENABLED = -143 ' Express capability is required to use this function
Global Const L_ERROR_IMAGE_EMPTY = -144 ' Image is empty
Global Const L_ERROR_NO_CHANGE = -145 ' The image hasn't changed
Global Const L_ERROR_LZW_LOCKED = -146 ' LZW is locked

Global Const L_ERROR_FPXEXTENSIONS_LOCKED = -147 ' FPX Extensions is locked
Global Const L_ERROR_ANN_LOCKED = -148           ' the annotation object is locked
Global Const L_ERROR_EXCEPTION = -149

Global Const L_ERROR_DLG_CANCELED = -150 ' common dialog was canceled by user
Global Const L_ERROR_DLG_FAILED = -151 ' an error occured during creation of the common dialog

Global Const L_ERROR_ISIS_NOCURSCANNER = -160 ' No ISIS Scanner selected
Global Const L_ERROR_ISIS_SCANDRIVER_NOT_LOADED = -161 ' ISIS Scanner driver failed to load
Global Const L_ERROR_ISIS_CANCEL = -162 ' ISIS operation canceled
Global Const L_ERROR_ISIS_BAD_TAG_OR_VALUE = -163 ' Bad ISIS Tag or Bad Tag Value
Global Const L_ERROR_ISIS_NOT_READY = -164 ' ISIS Scanner not ready
Global Const L_ERROR_ISIS_NO_PAGE = -165 ' No page in the ISIS Scanner
Global Const L_ERROR_ISIS_JAM = -166 ' ISIS Scanner Jam error
Global Const L_ERROR_ISIS_SCANNER_ERROR = -167 ' ISIS Scanner driver rror
Global Const L_ERROR_ISIS_BUSY = -168 ' ISIS Scanner is busy
Global Const L_ERROR_ISIS_FILE_ERROR = -169 ' ISIS File driver error
Global Const L_ERROR_ISIS_NETWORK_ERROR = -170 ' ISIS Network error
Global Const L_ERROR_ISIS_NOT_INSTALLED = -171 ' ISIS is not installed

Global Const L_ERROR_DOC_NOT_INITIALIZED = -180
Global Const L_ERROR_DOC_HANDLE = -181
Global Const L_ERROR_DOC_EMPTY = -182
Global Const L_ERROR_DOC_INVALID_FONT = -183
Global Const L_ERROR_DOC_INVALID_PAGE = -184
Global Const L_ERROR_DOC_INVALID_RULE = -185
Global Const L_ERROR_DOC_INVALID_ZONE = -186
Global Const L_ERROR_DOC_TYPE_ZONE = -187
Global Const L_ERROR_DOC_INVALID_COLUMN = -188
Global Const L_ERROR_DOC_INVALID_LINE = -189
Global Const L_ERROR_DOC_INVALID_WORD = -190
Global Const L_ERROR_OCR_LOCKED = -191
Global Const L_ERROR_OCR_NOT_INITIALIZED = -192
Global Const L_ERROR_OCR_MAX_REGIONS = -193
Global Const L_ERROR_OCR_OPTION = -194
Global Const L_ERROR_OCR_CONVERT_DIB = -195
Global Const L_ERROR_OCR_CANCELED = -196
Global Const L_ERROR_OCR_INVALID_OUTPUT = -197
Global Const L_ERROR_OCR_BLOCKED = -198
Global Const L_ERROR_OCR_RPCMEM = -199
Global Const L_ERROR_OCR_FATAL = -200
Global Const L_ERROR_OCR_BADTAG = -201
Global Const L_ERROR_OCR_BADVAL = -202
Global Const L_ERROR_OCR_BADTYPE = -203
Global Const L_ERROR_OCR_NOFILE = -204
Global Const L_ERROR_OCR_BADTOK = -205
Global Const L_ERROR_OCR_BADFMT = -206
Global Const L_ERROR_OCR_BADMATCH = -207
Global Const L_ERROR_OCR_NOSUPPORT = -208
Global Const L_ERROR_OCR_BADID = -209
Global Const L_ERROR_OCR_NOLANG = -210
Global Const L_ERROR_OCR_LANGOVFL = -211
Global Const L_ERROR_OCR_NOISRC = -212
Global Const L_ERROR_OCR_NOTIDL = -213
Global Const L_ERROR_OCR_NOVER = -214
Global Const L_ERROR_OCR_NODRAW = -215
Global Const L_ERROR_OCR_MEMERR = -216
Global Const L_ERROR_OCR_BADRGN = -217
Global Const L_ERROR_OCR_NOICR = -218
Global Const L_ERROR_OCR_NOACTV = -219
Global Const L_ERROR_OCR_NOMORE = -220
Global Const L_ERROR_OCR_NOTWAIT = -221
Global Const L_ERROR_OCR_LEXOVFL = -222
Global Const L_ERROR_OCR_PREPROC = -223
Global Const L_ERROR_OCR_BADFILE = -224
Global Const L_ERROR_OCR_BADSCAN = -225
Global Const L_ERROR_OCR_NOIMG = -226
Global Const L_ERROR_OCR_NOLICN = -227
Global Const L_ERROR_OCR_NOLCSRV = -228
Global Const L_ERROR_OCR_LMEMERR = -229
Global Const L_ERROR_OCR_RESCHNG = -230
Global Const L_ERROR_OCR_BADPLGN = -231
Global Const L_ERROR_OCR_NOSINK = -232
Global Const L_ERROR_OCR_NOSRC = -233
Global Const L_ERROR_OCR_NOTOK = -234
Global Const L_ERROR_OCR_IMBUFOVFL = -235
Global Const L_ERROR_OCR_TMOUT = -236
Global Const L_ERROR_OCR_BADVRS = -237
Global Const L_ERROR_OCR_TAGNNW = -238
Global Const L_ERROR_OCR_SRVCAN = -239
Global Const L_ERROR_OCR_WRFAIL = -240
Global Const L_ERROR_OCR_SCNCAN = -241
Global Const L_ERROR_OCR_RGOCCLD = -242
Global Const L_ERROR_OCR_NOTORNT = -243
Global Const L_ERROR_OCR_ACCDEN = -244
Global Const L_ERROR_OCR_BADUOR = -245
             
Global Const L_ERROR_RECORDING = -250                       ' wave device is currently recording
Global Const L_ERROR_COMPRESSOR = -251                      ' invalid compressor
Global Const L_ERROR_SOUND_DEVICE = -252                    ' problem with sound card
Global Const L_ERROR_DEVICE_INUSE = -253                    ' the sound card is currently in use
Global Const L_ERROR_INV_TRACKTYPE = -254                   ' invalid track for operation
Global Const L_ERROR_NO_SOUNDCARD = -255                    ' no sound card is presend
Global Const L_ERROR_NOT_RECORDING = -256                   ' not currently recording
Global Const L_ERROR_INV_MODE = -257                        ' invalid open mode for operation
Global Const L_ERROR_NO_VIDEO_MODULE = -258                 ' no video module present on machine
Global Const L_ERROR_QUEUE_FULL = -259                      ' the buffer queue is full

Global Const L_ERROR_HOST_RESOLVE = -270
Global Const L_ERROR_CANT_INITIALIZE = -271
Global Const L_ERROR_NO_CONNECTION = -272
Global Const L_ERROR_HOST_NOT_FOUND = -273
Global Const L_ERROR_NOT_SERVER = -274
Global Const L_ERROR_NO_CONNECTIONS = -275
Global Const L_ERROR_CONNECT_REFUSED = -276
Global Const L_ERROR_IS_CONNECTED = -277                    ' computer is already connected
Global Const L_ERROR_NET_UNREACH = -278                     ' network is unreachable from host
Global Const L_ERROR_TIME_OUT = -279                        ' connect attempt time out without connecting
Global Const L_ERROR_NET_DOWN = -280                        ' network subsystem is down
Global Const L_ERROR_NO_BUFFERS = -281                      ' no buffer space is available, to many connections
Global Const L_ERROR_NO_FILE_DESCR = -282                   ' no more file handle available
Global Const L_ERROR_DATA_QUEUED = -283                     ' data has been queued to send later
Global Const L_ERROR_UNKNOWN = -284                         ' unkown network error has occured
Global Const L_ERROR_CONNECT_RESET = -285                   ' connection was reset - socket might be unusable
Global Const L_ERROR_TRANSFER_ABORTED = -286                ' transfer was aborted

Global Const L_ERROR_DSHOW_FAILURE = -287                   ' DirectShow isn't installed correctly

Global Const L_ERROR_REGISTRY_READ = -288                   ' Error reading from the registry
Global Const L_ERROR_WAVE_FORMAT = -289                     ' The wave format is not supported
Global Const L_ERROR_INSUFICIENT_BUFFER = -290              ' The buffer size is too small
Global Const L_ERROR_WAVE_CONVERT = -291                    ' Error converting the wave format
Global Const L_ERROR_MULTIMEDIA_NOT_ENABLED = -292                    ' Video capabilities not unlocked

Global Const L_ERROR_CAP_CONNECT = -293                     ' error connecting to capture device
Global Const L_ERROR_CAP_DISCONNECT = -294                  ' error disconnecting capture device
Global Const L_ERROR_DISK_ISFULL = -295                     ' not enough disk space
Global Const L_ERROR_CAP_OVERLAY = -296                     ' error setting capture overlay
Global Const L_ERROR_CAP_PREVIEW = -297                     ' error setting capture preview
Global Const L_ERROR_CAP_COPY = -298                        ' error copying to clipboard
Global Const L_ERROR_CAP_WINDOW = -299                      ' error with capture window
Global Const L_ERROR_CAP_ISCAPTURING = -300                 ' operation invalid during capture
Global Const L_ERROR_NO_STREAMS = -301                      ' no streams to play
Global Const L_ERROR_CREATE_STREAM = -302                   ' error creating streams
Global Const L_ERROR_FRAME_DELETE = -303                    ' error deleting frames

Global Const L_ERROR_PAGE_NOT_FOUND = -310                    ' Page not found
Global Const L_ERROR_DELETE_LAST_PAGE = -311                  ' You cannot delete a page from a file containing only one page
Global Const L_ERROR_NO_HOTKEY = -312
Global Const L_ERROR_CANNOT_CREATE_HOTKEY_WINDOW = -313
Global Const L_ERROR_MEDICAL_NOT_ENABLED = -314            ' Medical Express capability is required to use this function
Global Const L_ERROR_JBIG_NOT_ENABLED = -315               ' JBIG capability is required to use this function
Global Const L_ERROR_UNDO_STACK_EMPTY = -316               ' Undo stack is empty - too many undos
Global Const L_ERROR_NO_TOOLBAR = -317                     ' ActiveX error - the toolbar window was not created

Global Const L_ERROR_CAPTURE_STILL_IN_PROCESS = -320
Global Const L_ERROR_INVALID_DELAY = -321
Global Const L_ERROR_INVALID_COUNT = -322
Global Const L_ERROR_INVALID_INTERVAL = -323
Global Const L_ERROR_HOTKEY_CONFILCTS_WITH_CANCELKEY = -324
Global Const L_ERROR_CAPTURE_INVALID_AREA_TYPE = -325
Global Const L_ERROR_CAPTURE_NO_OPTION_STRUCTURE = -326
Global Const L_ERROR_CAPTURE_INVALID_FILL_PATTERN = -327
Global Const L_ERROR_CAPTURE_INVALID_LINE_STYLE = -328
Global Const L_ERROR_CAPTURE_INVALID_INFOWND_POS = -329
Global Const L_ERROR_CAPTURE_INVALID_INFOWND_SIZE = -330
Global Const L_ERROR_CAPTURE_ZERO_AREA_SIZE = -331
Global Const L_ERROR_CAPTURE_FILE_ACCESS_FAILED = -332
Global Const L_ERROR_CAPTURE_INVALID_32BIT_EXE_OR_DLL = -333
Global Const L_ERROR_CAPTURE_INVALID_RESOURCE_TYPE = -334
Global Const L_ERROR_CAPTURE_INVALID_RESOURCE_INDEX = -335
Global Const L_ERROR_CAPTURE_NO_ACTIVE_WINDOW = -336
Global Const L_ERROR_CAPTURE_CANNOT_CAPTURE_WINDOW = -337
Global Const L_ERROR_CAPTURE_STRING_ID_NOT_DEFINED = -338
Global Const L_ERROR_CAPTURE_DELAY_LESS_THAN_ZERO = -339
Global Const L_ERROR_CAPTURE_NO_MENU = -340

Global Const L_ERROR_BROWSE_FAILED = -350               ' directory browsing failed
Global Const L_ERROR_NOTHING_TO_DO = -351
Global Const L_ERROR_INTERNET_NOT_ENABLED = -352
Global Const L_ERROR_LVKRN_MISSING = -353

Global Const L_ERROR_CMW_LOCKED = -354                 ' The CMW support is locked
Global Const L_ERROR_CMW_FILTER_MISSING = -355         ' CMW filter is needed to use this function
Global Const L_ERROR_CMP_FILTER_MISSING = -356         ' CMP filter is needed to use this function
Global Const L_ERROR_FAX_FILTER_MISSING = -357         ' FAX filter is needed to use this function


'  start of MPEG specific error codes

Global Const L_ERROR_INV_HORZSIZE = -360                ' The horizontal size is outside the specification
Global Const L_ERROR_INV_VERTSIZE = -361                ' The veritical size is outside the specification
Global Const L_ERROR_ASPECTRATIO = -362                 ' Invalid pel aspect ratio
Global Const L_ERROR_BITRATE = -363                     ' Invalid bitrate
Global Const L_ERROR_VBV_BUFFER = -364                  ' VBV Buffer Size is isn't valid
Global Const L_ERROR_CHROMA_FORMAT = -365               ' Invalid chroma format
Global Const L_ERROR_VIDEO_FORMAT = -366                ' Invalid video format
Global Const L_ERROR_COLOR_PRIMARY = -367               ' Invalid number of color primaries
Global Const L_ERROR_TRANSFER_CHAR = -368               ' Invalid number of transfer characteristics
Global Const L_ERROR_MATRIX_COEFF = -369                ' Invalid number of matrix coeeficients
Global Const L_ERROR_DISPLAY_HORZSIZE = -370            ' Invalid horizontal display size
Global Const L_ERROR_DISPLAY_VERTSIZE = -371            ' Invalid vertical display size
Global Const L_ERROR_INTRA_DCPREC = -372                ' Invalid Intra DC Precision
Global Const L_ERROR_FCODE = -373                       ' Invalid f code
Global Const L_ERROR_SRCH_WINDOW = -374                 ' Invalid motion data search window
Global Const L_ERROR_PROFILEID = -375                   ' Invalid profile id
Global Const L_ERROR_LEVELID = -376                     ' Invalid level id
Global Const L_ERROR_PROFILEID_NS = -377                ' Encoder doesn't support scalabale bitstreams
Global Const L_ERROR_INV_COMBINATION = -378             ' Undefined Profile & Level id combination
Global Const L_ERROR_BPIC_NOTALLOWED = -379             ' B Pictures not allowed
Global Const L_ERROR_RPTFIRST_MUSTBEZERO = -380         ' Repeat first must be zero
Global Const L_ERROR_FRAME_RATE = -381                  ' Invalid frame rate

'  end MPEG specific error codes

Global Const L_ERROR_VECTOR_NOT_ENABLED = -400          ' Vector capability is required to use this function
Global Const L_ERROR_VECTOR_DXF_NOT_ENABLED = -401      ' Vector DXF capability is required to use this function
Global Const L_ERROR_VECTOR_DWG_NOT_ENABLED = -402      ' Vector DWG capability is required to use this function
Global Const L_ERROR_VECTOR_MISC_NOT_ENABLED = -403     ' Vector misc capability is required to use this function
Global Const L_ERROR_TAG_MISSING = -404                 ' Tag not found
Global Const L_ERROR_VECTOR_DWF_NOT_ENABLED = -405      ' Vector DWF capability is required to use this function
Global Const L_ERROR_NO_UNDO_STACK = -406                ' There is no undo stack
Global Const L_ERROR_UNDO_DISABLED = -407                ' The undo is disabled
Global Const L_ERROR_PDF_NOT_ENABLED = -408              ' PDF capability is required to use this function
Global Const ERROR_ENTENSIONS_MISSING = -409             ' EXIF extensions are missing

Global Const L_ERROR_BARCODE_DIGIT_CHECK = -410
Global Const L_ERROR_BARCODE_INVALID_TYPE = -411
Global Const L_ERROR_BARCODE_TEXTOUT = -412
Global Const L_ERROR_BARCODE_WIDTH = -413
Global Const L_ERROR_BARCODE_HEIGHT = -414
Global Const L_ERROR_BARCODE_TOSMALL = -415
Global Const L_ERROR_BARCODE_STRING = -416
Global Const L_ERROR_BARCODE_NOTFOUND = -417
Global Const L_ERROR_BARCODE_UNITS = -418
Global Const L_ERROR_BARCODE_MULTIPLEMAXCOUNT = -419
Global Const L_ERROR_BARCODE_GROUP = -420
Global Const L_ERROR_BARCODE_NO_DATA = -421
Global Const L_ERROR_BARCODE_NOTFOUND_DUPLICATED = -422
Global Const L_ERROR_BARCODE_LAST_DUPLICATED = -423
Global Const L_ERROR_BARCODE_STRING_LENGTH = -424
Global Const L_ERROR_BARCODE_LOCATION = -425
Global Const L_ERROR_BARCODE_1D_LOCKED = -426
Global Const L_ERROR_BARCODE_2D_READ_LOCKED = -427
Global Const L_ERROR_BARCODE_2D_WRITE_LOCKED = -428
Global Const L_ERROR_BARCODE_PDF_READ_LOCKED = -429
Global Const L_ERROR_BARCODE_PDF_WRITE_LOCKED = -430
Global Const L_ERROR_VECTOR_IS_EMPTY = -501
Global Const L_ERROR_VECTOR_LAYER_NOT_FOUND = -502
Global Const L_ERROR_VECTOR_LAYER_IS_LOCKED = -503
Global Const L_ERROR_VECTOR_GROUP_NOT_FOUND = -504
Global Const L_ERROR_VECTOR_OBJECT_NOT_FOUND = -505
Global Const L_ERROR_VECTOR_INVALID_OBJECT_TYPE = -506
Global Const L_ERROR_VECTOR_PEN_NOT_FOUND = -507
Global Const L_ERROR_VECTOR_BRUSH_NOT_FOUND = -508
Global Const L_ERROR_VECTOR_FONT_NOT_FOUND = -509
Global Const L_ERROR_VECTOR_BITMAP_NOT_FOUND = -510
Global Const L_ERROR_VECTOR_POINT_NOT_FOUND = -511
Global Const L_ERROR_VECTOR_ENGINE_NOT_FOUND = -512
Global Const L_ERROR_VECTOR_INVALID_ENGINE = -513
Global Const L_ERROR_VECTOR_CLIPBOARD = -514
Global Const L_ERROR_VECTOR_CLIPBOARD_IS_EMPTY = -515
Global Const L_ERROR_VECTOR_CANT_ADD_TEXT = -516
Global Const L_ERROR_VECTOR_CANT_READ_WMF = -517

Global Const L_ERROR_TWAIN_NO_LIBRARY = -560
Global Const L_ERROR_TWAIN_NOT_AVAILABLE = -560
Global Const L_ERROR_TWAIN_INVALID_DLL = -561
Global Const L_ERROR_TWAIN_NOT_INITIALIZED = -562
Global Const L_ERROR_TWAIN_CANCELED = -563
Global Const L_ERROR_TWAIN_CHECK_STATUS = -564
Global Const L_ERROR_TWAIN_END_OF_LIST = -565
Global Const L_ERROR_TWAIN_CAP_NOT_SUPPORTED = -566
Global Const L_ERROR_TWAIN_SOURCE_NOT_OPEN = -567
Global Const L_ERROR_TWAIN_BAD_VALUE = -568
Global Const L_ERROR_TWAIN_INVALID_STATE = -569
Global Const L_ERROR_TWAIN_CAPS_NEG_NOT_ENDED = -570
Global Const L_ERROR_TWAIN_OPEN_FILE = -571
Global Const L_ERROR_TWAIN_INV_HANDLE = -572
Global Const L_ERROR_TWAIN_WRITE_TO_FILE = -573
Global Const L_ERROR_TWAIN_INV_VERSION_NUM = -574
Global Const L_ERROR_TWAIN_READ_FROM_FILE = -575
Global Const L_ERROR_TWAIN_NOT_VALID_FILE = -576
Global Const L_ERROR_TWAIN_INV_ACCESS_RIGHT = -577
Global Const L_ERROR_TWAIN_CUSTOMBASE = -578
Global Const L_ERROR_TWAIN_DENIED = -579
Global Const L_ERROR_TWAIN_FILEEXISTS = -580
Global Const L_ERROR_TWAIN_FILENOTFOUND = -581
Global Const L_ERROR_TWAIN_NOTEMPTY = -582
Global Const L_ERROR_TWAIN_PAPERJAM = -583
Global Const L_ERROR_TWAIN_PAPERDOUBLEFEED = -584
Global Const L_ERROR_TWAIN_FILEWRITEERROR = -585
Global Const L_ERROR_TWAIN_CHECKDEVICEONLINE = -586

Global Const L_ERROR_TWAIN_STOP_ENUMERATION = L_SUCCESS_ABORT


' start PaintTools error codes

Global Const L_ERROR_PAINT_INTERNAL = -600         ' Internal error (Call LEAD)
Global Const L_ERROR_PAINT_INV_DATA = -601         ' Internal error (Call LEAD)
Global Const L_ERROR_PAINT_NO_RESOURCES = -602     ' Internal error (Call LEAD)
Global Const L_ERROR_PAINT_NOT_ENABLED = -603      ' DigitalPaint capability is required to use this function

' end PaintTools error codes


' start Container error codes

Global Const L_ERROR_CONTAINER_INV_HANDLE = -630
Global Const L_ERROR_CONTAINER_INV_OPERATION = -631
Global Const L_ERROR_CONTAINER_NO_RESOURCES = -632

' end Container error codes

' start Toolbar error codes

Global Const L_ERROR_TOOLBAR_NO_RESOURCES = -660
Global Const L_ERROR_TOOLBAR_INV_STATE = -661
Global Const L_ERROR_TOOLBAR_INV_HANDLE = -662

' end Toolbar error codes


' start Automation error codes

Global Const L_ERROR_AUTOMATION_INV_HANDLE = -690
Global Const L_ERROR_AUTOMATION_INV_STATE = -691

' end Automation error codes

' start Segmentation errors

Global Const L_ERROR_INV_SEG_HANDLE = -700
Global Const L_ERROR_INV_SEG_DATA = -701
Global Const L_ERROR_INV_LAYER_DATA = -702
Global Const L_ERROR_MRC_NOT_ALLOCATED = -703
Global Const L_ERROR_INV_MIN_SEGMENT = -704
Global Const L_ERROR_SEGMENTATION_FAILURE = -705
Global Const L_ERROR_MRC_INV_PAGE = -706

' end Segmentation errors

Global Const L_ERROR_PDF_FILE_ENCRYPTED = -721                 ' The PDF file is encrypted and the szPassword member of the FILEPDFOPTIONS is not set (no password)
Global Const L_ERROR_PDF_INVALID_PASSWORD = -722
Global Const L_ERROR_PDF_FAX_NOT_ENABLED = -723                ' This feature requires Fax engine
Global Const L_ERROR_PDF_JPEG_NOT_ENABLED = -724               ' This feature requires Jpeg engine
Global Const L_ERROR_PDF_INV_DOC_STRUCTURING_COMMENTS = -725   ' Invalid Document Structuring comments (Ps and EPS)
Global Const L_ERROR_PDF_FONTS_DIRECTORY_NOT_FOUND = -726      ' Could not find Fonts directory
Global Const L_ERROR_PDF_CANNOT_EDIT_FILE = -727               ' Cannot insert,delete,append or replace pages
Global Const L_ERROR_PDF_BAD_CONTENT = -728                    ' File is corrupted
Global Const L_ERROR_PDF_BAD_INITIALIZATION_FILES = -729       ' Either the files required for initializing the PDF engine were
                                                               ' not found or they were found but they are not correct

' Start SVG errors
Global Const L_ERROR_SVG_FILE_SIZE_READ = -770
Global Const L_ERROR_SVG_ROOT_NOT_SVG = -771
Global Const L_ERROR_SVG_NOFOUND_ROOT_ELEMENT = -772
Global Const L_ERROR_SVG_INV_ELEMENT = -773
Global Const L_ERROR_SVG_DUPLICATED_ATTRIBUTE = -774
Global Const L_ERROR_SVG_INV_ATTRIBUTE = -775
Global Const L_ERROR_SVG_INV_ATTRIBUTE_VALUE = -776
Global Const L_ERROR_SVG_BAD_CSS_PROPERTY = -777
Global Const L_ERROR_SVG_MISSING_REQUIRED_ATTRIBUTE = -778
Global Const L_ERROR_SVG_DUPLICATED_ID = -779
Global Const L_ERROR_SVG_INV_COORDINATES_NUMBER = -780
Global Const L_ERROR_SVG_INV_STRING_COMMA = -781
' End SVG errors

' start ColorSpace SDK errors
Global Const L_ERROR_INVALID_FORMAT = -785
Global Const L_ERROR_UNSUPPORTED_METHOD = -786
Global Const L_ERROR_OPENING_PROFILE = -787
Global Const L_ERROR_INVALID_COLOR_PROFILE = -788
Global Const L_ERROR_INVALID_STRUCT_SIZE = -789
Global Const L_ERROR_U_V_NOT_MULTIPLES = -791
Global Const L_ERROR_NO_NONPLANAR_VERTICAL_SUBSAMPLING_SUPPORTED = -792
Global Const L_ERROR_PLANAR_ALIGNMENT_NOT_SUPPORTED = -793
Global Const L_ERROR_UNSUPPORTED_CONVERSION = -794
Global Const L_ERROR_TRUNCATE_HEIGHT = -795
Global Const L_ERROR_TRUNCATE_WIDTH = -796
Global Const L_ERROR_TRUNCATE_WIDTH_AND_HEIGHT = -797
' end ColorSpace SDK errors

Global Const L_ERROR_LAYER_MISSING = -800
Global Const L_ERROR_BAD_MARKER = -801          ' Bad JPEG marker
Global Const L_ERROR_AUDIO_MISSING = -802       ' The audio data is not present

'******** LEADTools VB Addon Constants ********'
Global Const L_MAXPATH = 260

' View perspectives
Global Const TOP_LEFT = 0                    ' The top left part of the screen
Global Const BOTTOM_LEFT = 2                 ' The bottom left part of the screen
Global Const TOP_RIGHT = 1                   ' The top right part of the screen
Global Const BOTTOM_LEFT180 = 1              ' TOP_RIGHT is BOTTOM_LEFT rotated clockwise by 180 degrees
Global Const BOTTOM_RIGHT = 3                ' The bottom right part of the screen
Global Const TOP_LEFT180 = 3                 ' BOTTOM_RIGHT is TOP_LEFT rotated clockwise by 180 degrees
Global Const RIGHT_TOP = 4                   ' First row is the right side, first column is top side
Global Const TOP_LEFT90 = 4                  ' RIGHT_TOP is TOP_LEFT rotated clocwise by 90 degrees
Global Const LEFT_BOTTOM = 8                 ' First row is the left side, first column is top side
Global Const TOP_LEFT270 = 8                 ' LEFT_BOTTOM is TOP_LEFT rotated clocwise by 270 degrees
Global Const LEFT_TOP = 5                    ' First row is the left side, first column is the top side
Global Const BOTTOM_LEFT90 = 5               ' LEFT_TOP is BOTTOM_LEFT rotated clockwise by 90 degrees
Global Const RIGHT_BOTTOM = 7                ' First row is the right side, first column is the bottom side
Global Const BOTTOM_LEFT270 = 7              ' RIGHT_BOTTOM is BOTTOM_LEFT rotated clockwise by 270 degrees

' Memory allocation mechanism
Global Const TYPE_CONV = &H1                   ' Use conventional memory first
Global Const TYPE_USER = &H2                   ' Create a bitmap where the user maintains the data pointer
Global Const TYPE_DISK = &H80                  ' Use Disk (if possible)
Global Const TYPE_NODISK = &H100               ' Do not use disk
Global Const TYPE_COMPRESSED = &H200           ' keep 1 bit images compressed in memory
Global Const TYPE_SUPERCOMPRESSED = &H400      ' keep 24 bit images compressed in memory - slow access

' Compression method for TIF
Global Const COMP_NONE = 0                  ' None
Global Const COMP_LZW = 1                   ' LZW Method
Global Const COMP_CCITT = 3                 ' TIFF  CCITT
Global Const COMP_CCITTG3_FAX1D = 4         ' CCITT Group3 one dimensional
Global Const COMP_CCITTG3_FAX2D = 5         ' CCITT Group3 two dimensional
Global Const COMP_CCITTG4_FAX = 6           ' CCITT Group4 two dimensional
Global Const NONE = COMP_NONE
Global Const LZW = COMP_LZW

' Compression types for L_ChangeBitmapCompression
'Global Const COMP_NONE = 0
Global Const COMP_RLE = 1
Global Const COMP_SUPER = 2


' Dithering methods
Global Const NO_DITHERING = 0              ' Dithering Methods
Global Const FLOYD_STEIN_DITHERING = 1
Global Const STUCKI_DITHERING = 2
Global Const BURKES_DITHERING = 3
Global Const SIERRA_DITHERING = 4
Global Const STEVENSON_ARCE_DITHERING = 5
Global Const JARVIS_DITHERING = 6
Global Const ORDERED_DITHERING = 7
Global Const CLUSTERED_DITHERING = 8
Global Const LAST_DITHERING = 8

' Bitmap data color orders
Global Const ORDER_RGB = 0                    ' RGB ordering
Global Const ORDER_BGR = 1                    ' BRG ordering
Global Const ORDER_SOURCE = -1
Global Const ORDER_GRAY = 2

' File format constants used by LEAD
Global Const FILE_PCX = 1
Global Const FILE_GIF = 2
Global Const FILE_TIF = 3
Global Const FILE_TGA = 4
Global Const FILE_CMP = 5
Global Const FILE_BMP = 6
Global Const FROM_BUFFER = 7
Global Const FILE_BITMAP = 9
Global Const FILE_JFIF = 10
Global Const FILE_JTIF = 11
Global Const FILE_BIN = 12
Global Const FILE_HANDLE = 13
Global Const FILE_OS2 = 14
Global Const FILE_WMF = 15
Global Const FILE_EPS = 16
Global Const FILE_TIFLZW = 17
Global Const FILE_LEAD = 20
Global Const FILE_LEAD1JFIF = 21
Global Const FILE_LEAD1JTIF = 22
Global Const FILE_LEAD2JFIF = 23
Global Const FILE_LEAD2JTIf = 24
Global Const FILE_CCITT = 25
Global Const FILE_LEAD1BIT = 26
Global Const FILE_CCITT_GROUP3_1DIM = 27
Global Const FILE_CCITT_GROUP3_2DIM = 28
Global Const FILE_CCITT_GROUP4 = 29
Global Const FILE_LEAD_NOLOSS = 30
Global Const FILE_LEAD1BITA = 31          ' old LEAD 1 bit, lossless compression

Global Const FILE_CALS = 50
Global Const FILE_MAC = 51
Global Const FILE_IMG = 52
Global Const FILE_MSP = 53
Global Const FILE_WPG = 54
Global Const FILE_RAS = 55
Global Const FILE_PCT = 56
Global Const FILE_PCD = 57
Global Const FILE_DXF = 58
Global Const FILE_AVI = 59
Global Const FILE_WAV = 60
Global Const FILE_FLI = 61
Global Const FILE_CGM = 62
Global Const FILE_EPSTIFF = 63
Global Const FILE_EPSWMF = 64
Global Const FILE_CMPNOLOSS = 65
Global Const FILE_FAX_G3_1D = 66
Global Const FILE_FAX_G3_2D = 67
Global Const FILE_FAX_G4 = 68
Global Const FILE_WFX_G3_1D = 69
Global Const FILE_WFX_G4 = 70
Global Const FILE_ICA_G3_1D = 71
Global Const FILE_ICA_G3_2D = 72
Global Const FILE_ICA_G4 = 73
Global Const FILE_OS2_2 = 74
Global Const FILE_PNG = 75
Global Const FILE_PSD = 76
Global Const FILE_RAWICA_G3_1D = 77       ' Raw IOCA formats
Global Const FILE_RAWICA_G3_2D = 78
Global Const FILE_RAWICA_G4 = 79
Global Const FILE_FPX = 80                ' FlashPix, no compression
Global Const FILE_FPX_SINGLE_COLOR = 81   ' FlashPix, compression 'single color' method
Global Const FILE_FPX_JPEG = 82           ' FlashPix, compression JPEG
Global Const FILE_FPX_JPEG_QFACTOR = 83   ' FlashPix, compression JPEG, specify qFactor
Global Const FILE_BMP_RLE = 84             ' compressed Windows BMP
Global Const FILE_TIF_CMYK = 85            ' TIFF no compression,      CMYK data
Global Const FILE_TIFLZW_CMYK = 86         ' TIFF LZW compression,     CMYK data
Global Const FILE_TIF_PACKBITS = 87        ' TIFF PackBits compression, RGB data
Global Const FILE_TIF_PACKBITS_CMYK = 88   ' TIFF PackBits compression, CMYK data
Global Const FILE_DICOM_GRAY = 89          ' DICOM Grayscale
Global Const FILE_DICOM_COLOR = 90         ' DICOM Color
Global Const FILE_WIN_ICO = 91             ' Windows Icon
Global Const FILE_WIN_CUR = 92             ' Windows Cursor
Global Const FILE_TIF_YCC = 93             ' TIFF YCbCr color space, no compression
Global Const FILE_TIFLZW_YCC = 94          ' TIFF YCbCr color space, LZW compression
Global Const FILE_TIF_PACKBITS_YCC = 95    ' TIFF YCbCr color space, PackBits compression
Global Const FILE_EXIF = 96                ' uncompressed RGB Exif file
Global Const FILE_EXIF_YCC = 97            ' uncompressed YCbCr Exif file
Global Const FILE_EXIF_JPEG = 98           ' JPEG compressed Exif file
Global Const FILE_AWD = 99                 ' Microsoft Fax format
Global Const FILE_EXIF_JPEG_411 = 101      ' JPEG 4:1:1 compressed Exif file
Global Const FILE_PBM_ASCII = 102
Global Const FILE_PBM_BINARY = 103
Global Const FILE_PGM_ASCII = 104
Global Const FILE_PGM_BINARY = 105
Global Const FILE_PPM_ASCII = 106
Global Const FILE_PPM_BINARY = 107
Global Const FILE_CUT = 108
Global Const FILE_XPM = 109
Global Const FILE_XBM = 110
Global Const FILE_IFF_ILBM = 111
Global Const FILE_IFF_CAT = 112
Global Const FILE_XWD = 113
Global Const FILE_CLP = 114
Global Const FILE_JBIG = 115
Global Const FILE_EMF = 116
Global Const FILE_ICA_IBM_MMR = 117
Global Const FILE_RAWICA_IBM_MMR = 118
Global Const FILE_ANI = 119
Global Const FILE_ANI_RLE = 120
Global Const FILE_LASERDATA = 121
Global Const FILE_INTERGRAPH_RLE = 122
Global Const FILE_INTERGRAPH_VECTOR = 123
Global Const FILE_DWG = 124
Global Const FILE_DICOM_RLE_GRAY = 125
Global Const FILE_DICOM_RLE_COLOR = 126
Global Const FILE_DICOM_JPEG_GRAY = 127
Global Const FILE_DICOM_JPEG_COLOR = 128
Global Const FILE_CALS4 = 129
Global Const FILE_CALS2 = 130
Global Const FILE_CALS3 = 131
Global Const FILE_XWD10 = 132
Global Const FILE_XWD11 = 133
Global Const FILE_FLC = 134
Global Const FILE_KDC = 135
Global Const FILE_DRW = 136
Global Const FILE_PLT = 137
Global Const FILE_TIF_CMP = 138
Global Const FILE_TIF_JBIG = 139
Global Const FILE_TIF_DXF = 140
Global Const FILE_TIF_UNKNOWN = 141
Global Const FILE_SGI = 142
Global Const FILE_SGI_RLE = 143
Global Const FILE_VECTOR_DUMP = 144
Global Const FILE_DWF = 145
Global Const FILE_RAS_PDF = 146
Global Const FILE_RAS_PDF_G3_1D = 147
Global Const FILE_RAS_PDF_G3_2D = 148
Global Const FILE_RAS_PDF_G4 = 149
Global Const FILE_RAS_PDF_JPEG = 150
Global Const FILE_RAS_PDF_JPEG_422 = 151
Global Const FILE_RAS_PDF_JPEG_411 = 152
Global Const FILE_RAW = 153
Global Const FILE_RASTER_DUMP = 154
Global Const FILE_TIFF_CUSTOM = 155
Global Const FILE_RAW_RGB = 156
Global Const FILE_RAW_RLE4 = 157
Global Const FILE_RAW_RLE8 = 158
Global Const FILE_RAW_BITFIELDS = 159
Global Const FILE_RAW_PACKBITS = 160
Global Const FILE_RAW_JPEG = 161
Global Const FILE_FAX_G3_1D_NOEOL = 162
Global Const FILE_RAW_CCITT = 162
Global Const FILE_JP2 = 163
Global Const FILE_J2K = 164
Global Const FILE_CMW = 165
Global Const FILE_TIF_J2K = 166
Global Const FILE_TIF_CMW = 167
Global Const FILE_MRC = 168
Global Const FILE_GERBER = 169
Global Const FILE_MPEG1 = 243
Global Const FILE_MPEG2 = 246
Global Const FILE_SVG = 247
Global Const FILE_NTIF = 248

Global Const FILE_PTOCA = 249                   ' PTOCA
Global Const FILE_SCT = 250
Global Const FILE_PCL = 251
Global Const FILE_AFP = 252
Global Const FILE_ICA_UNCOMPRESSED = 253
Global Const FILE_RAWICA_UNCOMPRESSED = 254
Global Const FILE_SHP = 255                     ' ESRI
Global Const FILE_SMP = 256
Global Const FILE_SMP_G3_1D = 257               'CCITT Group 3 1D
Global Const FILE_SMP_G3_2D = 258               'CCITT Group 3 2D
Global Const FILE_SMP_G4 = 259                  'CCITT Group 4

' Compression type
Global Const LEAD = 0
Global Const JFIF = 1
Global Const JTIF = 2
Global Const LEAD1JFIF = 3
Global Const LEAD1JTIF = 4
Global Const LEAD2JFIF = 5
Global Const LEAD2JTIF = 6

Global Const LEAD_0 = 0
Global Const LEAD_1 = 1

Global Const TIFF_CCITT = 3
Global Const TIFF_CCITTG3_FAX1D = 4
Global Const TIFF_CCITTG3_FAX2D = 5
Global Const TIFF_CCITTG4_FAX = 6

' Constants to be used for checking bitmap handle flag Integer
Global Const ALLOCATED = 1      'Is a bitmap allocated
Global Const CONV_MEM = 2       'Is it allocated in conventional memory
Global Const EXP_MEM = 4        'Is it allocated in expanded memory
Global Const EXT_MEM = 8        'Is it allocated in extended memory
Global Const DISK_MEM = 16      'Is it allocated in the disk
Global Const READOFFDISK = 32   'Internal use
Global Const LOCKED_MEM = 64    'Is memory locked in windows
Global Const INTERLACED = 128   'Bitmap data is interlaced
Global Const GRAYSCALE = 256    'Is the bitmap gray scale
Global Const WASOPTIMIZED = 512 'Is the bitmap optimized
Global Const FIXEDPALETTE = 1024 'Do we use fixed palette
Global Const TRUEPALETTE = 2048 'Does the image have true palette
Global Const RESIZE = 4096      'Internal use
Global Const READWRITEDIRECT = 8192 'Internal use
Global Const PALETTEINDEXES = 16284 'Internal use
Global Const DITHER24 = 32568       'if this is set to TRUE, and the image to be
                                    'decompressed is requested As 24 bit, the data
                                    'will be dithered for a smoother display.

' Preset QFactors, for LEAD format ONLY
Global Const QFACTOR_PQ1 = -1
Global Const QFACTOR_PQ2 = -2
Global Const QFACTOR_QFS = -3
Global Const QFACTOR_QMS = -4
Global Const QFACTOR_QS = -5
Global Const QFACTOR_SQS = -6
Global Const QFACTOR_SQT = -7
Global Const QFACTOR_MCQ = -8
Global Const QFACTOR_MC = -9

' Flags for L_CombineBitmap
Global Const CB_SRC_NOP = &H0
Global Const CB_SRC_NOT = &H1
Global Const CB_SRC_0 = &H2
Global Const CB_SRC_1 = &H3

Global Const CB_DST_NOP = &H0
Global Const CB_DST_NOT = &H10
Global Const CB_DST_0 = &H20
Global Const CB_DST_1 = &H30

Global Const CB_OP_AND = &H0
Global Const CB_OP_OR = &H100
Global Const CB_OP_XOR = &H200
Global Const CB_OP_ADD = &H300
Global Const CB_OP_SUBSRC = &H400
Global Const CB_OP_SUBDST = &H500
Global Const CB_OP_MUL = &H600
Global Const CB_OP_DIVSRC = &H700
Global Const CB_OP_DIVDST = &H800
Global Const CB_OP_AVG = &H900
Global Const CB_OP_MIN = &HA00
Global Const CB_OP_MAX = &HB00

Global Const CB_RES_NOP = &H0
Global Const CB_RES_NOT = &H1000
Global Const CB_RES_0 = &H2000
Global Const CB_RES_1 = &H3000

' Flags for L_EmbossBitmap
Global Const EMBOSS_N = 0
Global Const EMBOSS_NE = 1
Global Const EMBOSS_E = 2
Global Const EMBOSS_SE = 3
Global Const EMBOSS_S = 4
Global Const EMBOSS_SW = 5
Global Const EMBOSS_W = 6
Global Const EMBOSS_NW = 7

' Flags for L_GetHistogram, L_RemapBitmapIntensity, and L_AddNoiseBitmap
Global Const CHANNEL_MASTER = 0        ' All Channels
Global Const CHANNEL_RED = 1           ' Red Channel Only
Global Const CHANNEL_GREEN = 2         ' Green Channel Only
Global Const CHANNEL_BLUE = 3          ' Blue Channel Only

' Flags for L_CopyToClipboardExt
Global Const COPY2CB_EMPTY = 1   ' Empty the clipboard
Global Const COPY2CB_DIB = 2     ' Copy DIB data to the clipboard
Global Const COPY2CB_DDB = 4     ' Copy DDB data to the clipboard
Global Const COPY2CB_PALETTE = 8 ' Copy palette data to the clipboard
Global Const COPY2CB_RGN = 10    ' Copy region data to the clipboard

' Flags for L_SetLoadInfoCallback
Global Const LOADINFO_ORDERRGB = &H2            ' Auto-store image lines
Global Const LOADINFO_WHITEONBLACK = &H4        ' Allow fixed palettes only
Global Const LOADINFO_LSB = &H8                 ' Don't send interlaced lines
Global Const LOADINFO_REVERSE = &H40            ' Reverse (mirror) each line

Global Const LOADINFO_TOPLEFT = &H1             ' Allocate image memory
Global Const LOADINFO_TOPLEFT90 = &H10          ' Image has TOP_LEFT90 View Perspective
Global Const LOADINFO_TOPLEFT270 = &H20         ' Image has TOP_LEFT90 View Perspective
Global Const LOADINFO_TOPLEFT180 = &H80         ' Image has TOP_LEFT180 View Perspective
Global Const LOADINFO_BOTTOMLEFT90 = &H100      ' Image has BOTTOM_LEFT90 View Perspective
Global Const LOADINFO_BOTTOMLEFT180 = &H200     ' Image has BOTTOM_LEFT180 View Perspective
Global Const LOADINFO_BOTTOMLEFT270 = &H400     ' Image has BOTTOM_LEFT270 View Perspective

' Flags that make up FILEINFO.Flags
Global Const FILEINFO_INTERLACED = &H1
Global Const FILEINFO_PROGRESSIVE = &H2
Global Const FILEINFO_HAS_STAMP = &H4
Global Const FILEINFO_HAS_GLOBALBACKGROUND = &H8
Global Const FILEINFO_HAS_GLOBALPALETTE = &H10
Global Const FILEINFO_COMPRESSED = &H40      ' the image can be loaded compressed
Global Const FILEINFO_NOPALETTE = &H80       ' Grayscale TIF without a palette
Global Const FILEINFO_ROTATED = &H100        ' Image with an extended ViewPerspective
Global Const FILEINFO_SIGNED = &H200         ' Image with signed values for pixels
Global Const FILEINFO_LOSSLESSJPEG = &H400   ' Internal flag, indicating that the JPEG file uses the lossless compression.
                                             ' This flag will probably be removed in future versions
Global Const FILEINFO_HAS_ALPHA = &H800      ' The file has alpha channel information
Global Const FILEINFO_FORMATVALID = &H1000   ' Only the format type is valid
Global Const FILEINFO_INFOVALID = &H2000     ' The whole FILEINFO structure is valid
Global Const FILEINFO_LINK = &H4000          ' The file is a Windows 9x/NT link
Global Const FILEINFO_IFDVALID = &H8000      ' The IFD field is valid

'Flags for L_FileInfo (not to make up FILEINFO.Flags!)
Global Const FILEINFO_TOTALPAGES = &H1         'fill in FILEINFO.TotalPages

' Flags for L_LoadFile
Global Const LOADFILE_ALLOCATE = 1     ' Allocate image memory
Global Const LOADFILE_STORE = 2        ' Auto-store image lines
Global Const LOADFILE_FIXEDPALETTE = 4 ' Allow fixed palettes only
Global Const LOADFILE_NOINTERLACE = 8  ' Don't send interlaced lines
Global Const LOADFILE_ALLPAGES = &H10  ' Load all pages
Global Const LOADFILE_COMPRESSED = &H40      ' Allow compressed 1 bit images
Global Const LOADFILE_SUPERCOMPRESSED = &H80    ' Load 1-bit or 24-bit images supercompressed
 
' Flags for the FILEREADCALLBACK function
Global Const FILEREAD_FIRSTPASS = &H1
Global Const FILEREAD_LASTPASS = &H2
Global Const FILEREAD_FIRSTROW = &H4
Global Const FILEREAD_LASTROW = &H8
Global Const FILEREAD_COMPRESSED = &H10

' L_2DSetViewMode flags
Global Const L2D_USE_BEST = 0
Global Const L2D_USE_WIDTH_HEIGHT = 1
Global Const L2D_USE_WIDTH = 2
Global Const L2D_USE_HEIGHT = 3

' Flags for L_SaveFile
Global Const SAVEFILE_FIXEDPALETTE = 1     ' Save with Fixed Palette
Global Const SAVEFILE_OPTIMIZEDPALETTE = 2 ' Save with Bitmap's Palette
Global Const SAVEFILE_MULTIPAGE = 4        ' Save As multipage

'   flags for L_SizeBitmap
Global Const SIZE_NORMAL = &H0
Global Const SIZE_FAVORBLACK = &H1
Global Const SIZE_RESAMPLE = &H2
Global Const SIZE_BICUBIC = &H4

' Flags for L_TwainAcquireExt
Global Const TWAIN_SHOWUI = 1      ' Show the User Interface
Global Const TWAIN_SHOWSTATUS = 2  ' Show the Status Indicator,
                                   ' if it is selectable
Global Const TWAIN_NATIVEXFER = 4  ' Use native transfer
Global Const TWAIN_KEEPOPEN = 8    ' Keep the data source open
Global Const TWAIN_UPDATE_DEFAULTS_ONLY = &H10 ' Update only properties with the default values
Global Const TWAIN_UPDATE_NON_DEFAULTS = &H20 ' Update only properties with non-default values
Global Const TWAIN_UPDATE_ALL = &H30           ' Update all properties
Global Const TWAIN_CACHE_SOURCE = &H80        ' Close the data source after each scan - slower scanning


' Flags for TWAIN Properties
Global Const TWAIN_PIX_DEFAULT = -1 ' Use Default Type/Bits
Global Const TWAIN_PIX_HALF = 0     ' Halftone, 1 BPP
Global Const TWAIN_PIX_GRAY = 1     ' GrayScale, 4 0r 8 BPP
Global Const TWAIN_PIX_RGB = 2      ' Color, 24 BPP
Global Const TWAIN_PIX_PALETTE = 3  ' Color, 4 or 8 BPP
Global Const TWAIN_PIX_LAST = 3

Global Const TWAIN_DEFAULT_BRIGHTNESS = 2000
Global Const TWAIN_DEFAULT_CONTRAST = 2000
Global Const TWAIN_DEFAULT_ORIENTATION = -1
Global Const TWAIN_FEEDER_DONTCARE = 2

Global Const TWAIN_ROT0 = 0
Global Const TWAIN_ROT90 = 1
Global Const TWAIN_ROT180 = 2
Global Const TWAIN_ROT270 = 3
Global Const TWAIN_PORTRAIT = 0
Global Const TWAIN_LANDSCAPE = 1

Global Const TWAIN_DUPLEX_NONE = 0
Global Const TWAIN_DUPLEX_1PASS = 1
Global Const TWAIN_DUPLEX_2PASS = 2
Global Const TWAIN_DEFAULT = 2000
Global Const TWAIN_UNSUPPORTED = 2001

' Constants for L_ISIS functions
Global Const ISIS_DEFAULT_DIGITS = 4
Global Const ISIS_DEFAULT = -99
Global Const ISIS_SHOWUI = &H1
Global Const ISIS_MULTI_NOSAVE = &H2

' supported ISIS TAGS and possible values
Global Const TAG_XRESOLUTION = &H11A
Global Const TAG_YRESOLUTION = &H11B
Global Const TAG_XPOSITION = &H11E
Global Const TAG_YPOSITION = &H11F
Global Const TAG_IMAGELENGTH = &H101
Global Const TAG_IMAGEWIDTH = &H100

Global Const TAG_FEEDER = &H503
Global Const TAG_FEEDER_FEED = &H1
Global Const TAG_FEEDER_FLAT = &H2
Global Const TAG_FEEDER_MANUAL = &H4
Global Const TAG_FEEDER_TELLFEED = &H10000
Global Const TAG_FEEDER_TELLFLAT = &H20000
Global Const TAG_FEEDER_TELLSCAN = &H40000
Global Const TAG_FEEDER_CENTERFEED = &H80000
Global Const TAG_FEEDER_CENTERFLAT = &H100000
Global Const TAG_FEEDER_PAUSE = &H200000

Global Const TAG_SAMPLESPERPIXEL = &H115

Global Const TAG_BITSPERSAMPLE = &H102

Global Const TAG_CONTRAST = &H501
Global Const TAG_CONTRAST_AUTO = 0

Global Const TAG_BRIGHTNESS = &H502
Global Const TAG_BRIGHTNESS_AUTO = -3
Global Const TAG_BRIGHTNESS_DARKEN = -2
Global Const TAG_BRIGHTNESS_NORM = -1
Global Const TAG_BRIGHTNESS_LIGHTEN = 0

Global Const TAG_COMPRESSION = &H103
Global Const TAG_COMPRESSION_NONE = 1
Global Const TAG_COMPRESSION_MG3 = 2
Global Const TAG_COMPRESSION_G3 = 3
Global Const TAG_COMPRESSION_G4 = 4
Global Const TAG_COMPRESSION_LZW = 5
Global Const TAG_COMPRESSION_JPEG = 6
Global Const TAG_COMPRESSION_PACK = 32773
Global Const TAG_COMPRESSION_32771 = 32771
Global Const TAG_COMPRESSION_JBIG = 34661
Global Const TAG_COMPRESSION_PCX = 50000
Global Const TAG_COMPRESSION_4BYTE = 50001
Global Const TAG_COMPRESSION_GIF = 50005
Global Const TAG_COMPRESSION_BMP = 50006

Global Const TAG_PLANARCONFIGURATION = &H11C
Global Const TAG_PLANARCONFIG_LINE = 1
Global Const TAG_PLANARCONFIG_LINE_PACK = 1
Global Const TAG_PLANARCONFIG_PAGE = 2
Global Const TAG_PLANARCONFIG_LINE_UNPACK = 5000

Global Const TAG_SCANORIENTATION = &H113
Global Const TAG_SCANORIENTATION_PORT = 1
Global Const TAG_SCANORIENTATION_LAND = 2
Global Const TAG_SCANORIENTATION_180 = 3
Global Const TAG_SCANORIENTATION_270 = 4
Global Const TAG_SCANORIENTATION_PORTM = 5
Global Const TAG_SCANORIENTATION_LANDM = 6
Global Const TAG_SCANORIENTATION_180M = 7
Global Const TAG_SCANORIENTATION_270M = 8

Global Const TAG_MAXPAGES = &H504

Global Const TAG_SCANAHEAD = &H50D
Global Const TAG_SCANAHEAD_NO = 0
Global Const TAG_SCANAHEAD_YES = 1

Global Const TAG_GAMMA = &H50F
Global Const TAG_GAMMA_NORMAL = &H0
Global Const TAG_GAMMA_AUTO = &H0
Global Const TAG_GAMMA_DOWNLOAD1 = &H1
Global Const TAG_GAMMA_DOWNLOAD2 = &H2
Global Const TAG_GAMMA_DOWNLOAD3 = &H3
Global Const TAG_GAMMA_DOWNLOAD4 = &H4
Global Const TAG_GAMMA_DOWNLOAD5 = &H5
Global Const TAG_GAMMA_DOWNLOAD6 = &H6
Global Const TAG_GAMMA_CRT = &H7

Global Const TAG_SCANTYPE = &H514
Global Const TAG_SCANTYPE_AUTOMATIC = &H0
Global Const TAG_SCANTYPE_TRANSPARENCY = &H1
Global Const TAG_SCANTYPE_FLATBED = &H2
Global Const TAG_SCANTYPE_FEEDER = &H3
Global Const TAG_SCANTYPE_FRONTONLY = &H3
Global Const TAG_SCANTYPE_DUPLEX = &H4
Global Const TAG_SCANTYPE_FRONTBACK = &H4
Global Const TAG_SCANTYPE_BACKFRONT = &H5
Global Const TAG_SCANTYPE_BACKONLY = &H6

Global Const TAG_PHOTOMETRICINTERPRETATION = &H106
Global Const TAG_PHOTOMETRIC_WHITE0 = &H0
Global Const TAG_PHOTOMETRIC_WHITE1 = &H1
Global Const TAG_PHOTOMETRIC_RGB = &H2
Global Const TAG_PHOTOMETRIC_PALETTE = &H3
Global Const TAG_PHOTOMETRIC_BGR = &H120

' ASCII tags
Global Const TAG_PAGESIZE = &H50E

Global Const TAG_SCANAHEAD_MAXPAGES = &H57C


' Flags for L_ColorResBitmap
Global Const CRF_FIXEDPALETTE = &H1            ' versus custom palette
Global Const CRF_OPTIMIZEDPALETTE = &H2        ' versus fixed palette
Global Const CRF_IDENTITYPALETTE = &H8         ' versus ALL 256 colors
Global Const CRF_USERPALETTE = &H10            ' user generated palette
Global Const CRF_FASTMATCHPALETTE = &H20       ' With user, for fast color match
Global Const CRF_NETSCAPEPALETTE = &H40        ' use netscape fixed palette
Global Const CRF_BYTEORDERBGR = &H4            ' versus RGB
Global Const CRF_BYTEORDERRGB = &H0            ' versus BGR
Global Const CRF_BYTEORDERGRAY = &H80          ' Convert to grayscale (12 & 16 bit only)
Global Const CRF_PALETTEOPTIONS = &H1FF        ' Mask to find palette option
Global Const CRF_USERHPALETTE = &H100          ' user generated palette

Global Const CRF_NODITHERING = &H0                      ' No Dithering
Global Const CRF_FLOYDSTEINDITHERING = &H10000          ' Floyd Stein Dithering
Global Const CRF_STUCKIDITHERING = &H20000              ' Stucki Dithering
Global Const CRF_BURKESDITHERING = &H30000              ' Burkes Dithering
Global Const CRF_SIERRADITHERING = &H40000              ' Sierra Dithering
Global Const CRF_STEVENSONARCEDITHERING = &H50000       ' Stevenson Arce Dithering
Global Const CRF_JARVISDITHERING = &H60000              ' Jarvis Dithering
Global Const CRF_ORDEREDDITHERING = &H70000             ' Ordered Dithering
Global Const CRF_CLUSTEREDDITHERING = &H80000           ' Clustered Dithering
Global Const CRF_DITHERINGOPTIONS = &HFF0000            ' Mask to find dither option

Global Const RGB_RESERVED = &H1                   ' Do not map to the entry
Global Const RGB_EMPTY = &H2                      ' The entry is empty

' Flags for L_ColorSeparateBitmap/L_ColorMergeBitmap
Global Const COLORSEP_RGB = 0
Global Const COLORSEP_CMYK = 1
Global Const COLORSEP_HSV = 2
Global Const COLORSEP_HLS = 3
Global Const COLORSEP_CMY = 4

Global Const RGB_SPACE = 1
Global Const YUV_SPACE = 2
Global Const GRAY_SPACE = 4

Global Const SWAP_RG = 1
Global Const SWAP_RB = 2
Global Const SWAP_GB = 4
Global Const SWAP_RGBR = 8
Global Const SWAP_RBGR = &H10

' Flags for L_ResizeBitmapRgn

Global Const RGN_EXPAND = 1
Global Const RGN_CONTRACT = 2

' Flags for L_CreateFadedMask
Global Const FADE_OUTER = &H1
Global Const FADE_DUMPFILL = &H2
Global Const FADE_FILLCOLOR_START = &H4
Global Const FADE_WHITETOBLACK = &H8
Global Const FADE_NOTRANSPARENCY = &H10
Global Const FADE_TRANSPARENCY_DUMPCOLOR = &H20

' Flags for L_CombineBitmapExt
Global Const CB_SRC_MASTER = 0
Global Const CB_SRC_RED = &H10000
Global Const CB_SRC_GREEN = &H20000
Global Const CB_SRC_BLUE = &H30000

Global Const CB_DST_MASTER = 0
Global Const CB_DST_RED = &H100000
Global Const CB_DST_GREEN = &H200000
Global Const CB_DST_BLUE = &H300000

Global Const CB_RES_MASTER = 0
Global Const CB_RES_RED = &H1000000
Global Const CB_RES_GREEN = &H2000000
Global Const CB_RES_BLUE = &H3000000

' Flags for L_AddBitmaps
Global Const BC_AVG = &H1
Global Const BC_ADD = &H2

' Flags for L_AntiAliasBitmap
Global Const ANTIALIAS_1 = 0
Global Const ANTIALIAS_2 = 1
Global Const ANTIALIAS_3 = 2
Global Const ANTIALIAS_DIAG = 3
Global Const ANTIALIAS_HORZ = 4
Global Const ANTIALIAS_VERT = 5

' Flags for L_EdgeDetectorBitmap
Global Const EDG_SOBEL_VERT = &H101
Global Const EDG_SOBEL_HORZ = &H102
Global Const EDG_SOBEL_ALL = &H103


Global Const EDG_PREWITT_VERT = &H201
Global Const EDG_PREWITT_HORZ = &H202
Global Const EDG_PREWITT_ALL = &H203


Global Const EDG_LAPLACE_1 = &H301
Global Const EDG_LAPLACE_2 = &H302
Global Const EDG_LAPLACE_3 = &H303
Global Const EDG_LAPLACE_DIAG = &H304
Global Const EDG_LAPLACE_HORZ = &H305
Global Const EDG_LAPLACE_VERT = &H306

Global Const EDG_GRADIENT_N = &H401
Global Const EDG_GRADIENT_NE = &H402
Global Const EDG_GRADIENT_E = &H403
Global Const EDG_GRADIENT_SE = &H404
Global Const EDG_GRADIENT_S = &H405
Global Const EDG_GRADIENT_SW = &H406
Global Const EDG_GRADIENT_W = &H407
Global Const EDG_GRADIENT_NW = &H408

' Flags for L_GetFunctionalLookupTable
Global Const GL_EXP = 0
Global Const GL_LN = 1
Global Const GL_LINEAR = 2

' Flags for L_HalfToneBitmap
Global Const HT_PRINT = 0
Global Const HT_VIEW = 1
Global Const HT_RECT = 2
Global Const HT_CIRC = 3
Global Const HT_ELLIPS = 4
Global Const HT_RAND = 5
Global Const HT_LINEAR = 6

' Flags for L_AddFrame
Global Const FRAME_QUALITY_LOW = 0
Global Const FRAME_QUALITY_HIGH = 1

Global Const FRAME_INSIDE = 0
Global Const FRAME_OUTSIDE = 1

' Flags for L_AddBorder
Global Const BORDER_INSIDE = 0
Global Const BORDER_OUTSIDE = 1

Global Const BORDER_STYLE_TRANSPARENT = 0
Global Const BORDER_STYLE_OPAQUE = 1
Global Const BORDER_STYLE_GRADIENT = 2
Global Const BORDER_STYLE_TILES = 3

Global Const BORDER_EFFECT_CURVEDIN = 1
Global Const BORDER_EFFECT_CURVEDOUT = 2
Global Const BORDER_EFFECT_RAISED = 3

Global Const BORDER_SHADOW_LEFT = 0
Global Const BORDER_SHADOW_RIGHT = 1
Global Const BORDER_SHADOW_SURROUND = 2

Global Const BORDER_GRAD_INSIDEOUT = 0
Global Const BORDER_GRAD_CENTEROUT = 1
Global Const BORDER_GRAD_CORNEROUT = 2

' LEAD FILEPLTOPTIONS structure
Type FILEPLTOPTIONS
   Size As Long
   PenWidth(0 To 7) As Long
   PenColor(0 To 7) As Long
End Type

' LEAD FILEPDFOPTIONS structure
Type FILEPDFOPTIONS
   nSize As Long
   bUseLibFonts As Long
   nXResolution As Long
   nYResolution As Long
   nDisplayDepth As Long
   nTextAlpha As Long
   nGraphicsAlpha As Long
   szPassword As String * 64
End Type

' J2K/new CMP Options
' Limitations imposed by the standard
Global Const J2K_MAX_COMPONENTS_NUM = 3
Global Const J2K_MAX_DECOMP_LEVEL = 20

' Progressions Order
Global Const J2K_LAYER_RESOLUTION_COMPONENT_POSITION = 0
Global Const J2K_RESOLUTION_LAYER_COMPONENT_POSITION = 1
Global Const J2K_RESOLUTION_POSITION_COMPONENT_LAYER = 2
Global Const J2K_POSITION_COMPONENT_RESOLUTION_LAYER = 3
Global Const J2K_COMPONENT_POSITION_RESOLUTION_LAYER = 4

' Ways of controlling the compression
Global Const J2K_COMPRESSION_LOSSLESS = 0    ' lossless compression
Global Const J2K_COMPRESSION_RATIO = 1       ' use fCompressionRatio
Global Const J2K_COMPRESSION_TARGETSIZE = 2  ' use uTargetFileSize
Global Const J2K_COMPRESSION_QFACTOR = 3     ' use qFactor

' LEAD FILEJ2KOPTIONS structure
Type FILEJ2KOPTIONS
   nSize As Long
   bUseColorTransform As Long
   bDerivedQuantization As Long
   uCompressionControl As Long
   fCompressionRatio As Long
   uTargetFileSize  As Long
   uXOsiz As Long
   uYOsiz As Long
   uXTsiz As Long
   uYTsiz As Long
   uXTOsiz As Long
   uYTOsiz As Long
   uXRsiz(0 To 2) As Long
   uYRsiz(0 To 2) As Long
   uDecompLevel As Long
   uProgressOrder As Long
   nCodBlockWidth As Long
   nCodBlockHeight As Long
   CodBlockStyleFlags As Long
   uGuardBits As Long
   nDerivedBaseMantissa As Long
   nDerivedBaseExponent As Long
   bUseSOPMarker As Long
   bUseEPHMarker As Long
End Type

' LEAD BALANCING structure
Type BALANCING
   toRed As Double
   toGreen As Double
   toBlue As Double
End Type

' Flags for L_ConvertBitmapSignedToUnsigned
Global Const SHIFT_ZERO_TO_CENTER = 0
Global Const SHIFT_MIN_TO_ZERO = 1
Global Const SHIFT_NEG_TO_ZERO = 2

' Flags for L_ConvertColorSpace & L_ClrInit
Global Const CCS_RGB = 0         ' Color space is RGB
Global Const CCS_YUV = 1         ' Color space is YUV
Global Const CCS_CMYK = 2        ' Color space is CMYK
Global Const CCS_HSV = 3         ' Color space is HSV
Global Const CCS_HLS = 4         ' Color space is HLS
Global Const CCS_YIQ = 5         ' Color space is YIQ
Global Const CCS_CMY = 6         ' Color space is CMY
Global Const CCS_LAB = 7         ' Color space is CIELAB
Global Const CCS_XYZ = 8         ' Color space is XYZ
Global Const CCS_YCCK = &HB      ' Color space is YCCK
Global Const CCS_BGR = &HC       ' Color space is BGR

Global Const CCS_Y41P = &HD      ' Color space is Y41P
Global Const CCS_UYVY = &HE      ' Color space is UYVY
Global Const CCS_YUY2 = &H9      ' Color space is YUY2
Global Const CCS_YVU9 = &HA      ' Color space is YVU9
Global Const CCS_YCC = &HF       ' Color space is YCC

' Flags for L_ConvertBufferExt
Global Const CVT_SRCGRAY = &H1
Global Const CVT_DSTGRAY = &H2
Global Const CVT_SRCUSEBITS = &H4
Global Const CVT_DSTUSEBITS = &H8

' Flags for L_VersionInfo
Global Const TOOLKIT_LEVEL_DOCUMENT = 0
Global Const TOOLKIT_LEVEL_RASTER = 1
Global Const TOOLKIT_LEVEL_MEDICAL = 2

' Flags for L_SetDisplayMode
Global Const DISPLAYMODE_ORDEREDDITHER = &H1
Global Const DISPLAYMODE_FASTPAINT = &H2
Global Const DISPLAYMODE_INDEXEDPAINT = &H4
Global Const DISPLAYMODE_DITHEREDPAINT = &H8
Global Const DISPLAYMODE_SCALETOGRAY = &H10
Global Const DISPLAYMODE_HALFTONEPRINT = &H20
Global Const DISPLAYMODE_FAVORBLACK = &H40
Global Const DISPLAYMODE_FIXEDPALETTE = &H80
Global Const DISPLAYMODE_RESETPOSITIONS = &HFFFF

' Flags for L_UnderlayBitmap
Global Const UB_TILE = 0
Global Const UB_STRETCH = 1

' Flags for L_*Comment
Global Const CMNT_SZARTIST = 0    ' Person who created image
Global Const CMNT_SZCOPYRIGHT = 1 ' Copyright notice
Global Const CMNT_SZDATETIME = 2  ' "YYYY:MM:DD HH:MM:SS" format
Global Const CMNT_SZDESC = 3      ' Description of image
Global Const CMNT_SZHOSTCOMP = 4  ' Computer/OP system in use
Global Const CMNT_SZMAKE = 5      ' Manufacturer of equip. used to gen. the image
Global Const CMNT_SZMODEL = 6     ' Model Name/Number of equip. ...
Global Const CMNT_SZNAMEOFDOC = 7 ' Doc name image was scanned from
Global Const CMNT_SZNAMEOFPAGE = 8 ' Page name image was scanned from
Global Const CMNT_SZSOFTWARE = 9  ' Name and Version of software packages used to gen the image

Global Const CMNT_SZPATIENTNAME = 10 ' Patient name (DICOM)
Global Const CMNT_SZPATIENTID = 11 ' Patient ID (DICOM)
Global Const CMNT_SZPATIENTBIRTHDATE = 12 ' Patient birthdate (DICOM)
Global Const CMNT_SZPATIENTSEX = 13 ' Patient sex (DICOM)
Global Const CMNT_SZSTUDYINSTANCE = 14 ' Study instance ID (DICOM)
Global Const CMNT_SZSTUDYDATE = 15 ' Study date (DICOM)
Global Const CMNT_SZSTUDYTIME = 16 ' Study time (DICOM)
Global Const CMNT_SZSTUDYREFERRINGPHYSICIAN = 17 ' Referring physician (DICOM)
Global Const CMNT_SZSERIESMODALITY = 18 ' Series modality (DICOM)
Global Const CMNT_SZSERIESID = 19 ' Series ID (DICOM)
Global Const CMNT_SZSERIESNUMBER = 20 ' Series number (DICOM)

' Exif 1.0 and 1.1 comments
Global Const CMNT_EXIFVERSION = 21 ' Exif version
Global Const CMNT_SZDATETIMEORIGINAL = 22 ' Date and time the original image image is captured (Exif)
Global Const CMNT_SZDATETIMEDIGITIZED = 23 ' Date and time the file is generated (Exif)
Global Const CMNT_SHUTTERSPEEDVALUE = 24 ' Shutter speed (Exif)
Global Const CMNT_APERTURE = 25 ' Aperture value (Exif)
Global Const CMNT_BRIGHTNESS = 26 ' Brightness value (Exif)
Global Const CMNT_EXPOSUREBIAS = 27 ' Exposure bias (Exif)
Global Const CMNT_MAXAPERTURE = 28 ' Minimum lens f-number (Exif)
Global Const CMNT_SUBJECTDISTANCE = 29 ' Distance from lens to subject (m) (Exif)
Global Const CMNT_METERINGMODE = 30 ' Photometry mode (Exif)
Global Const CMNT_LIGHTSOURCE = 31 ' Light source (Exif)
Global Const CMNT_FLASH = 32 ' Flash On/Off (Exif)
Global Const CMNT_FOCALLENGTH = 33 ' Focal length (Exif)
Global Const CMNT_EXPOSURETIME = 34 ' Exposure  (Exif)
Global Const CMNT_FNUMBER = 35 ' F-numnber (Exif)
Global Const CMNT_MAKERNOTE = 36 ' Maker note (Exif)
Global Const CMNT_USERCOMMENT = 37 ' User comment (Exif)
Global Const CMNT_SZSUBSECTIME = 38 ' Date Time subsec (Exif)
Global Const CMNT_SZSUBSECTIMEORIGINAL = 39 ' Date Time original subsec (Exif)
Global Const CMNT_SZSUBSECTIMEDIGITIZED = 40 ' Date Time digitized subsec (Exif)

' Exif 1.1 GPS comments
Global Const CMNT_GPSVERSIONID = 41
Global Const CMNT_GPSLATITUDEREF = 42
Global Const CMNT_GPSLATITUDE = 43
Global Const CMNT_GPSLONGITUDEREF = 44
Global Const CMNT_GPSLONGITUDE = 45
Global Const CMNT_GPSALTITUDEREF = 46
Global Const CMNT_GPSALTITUDE = 47
Global Const CMNT_GPSTIMESTAMP = 48
Global Const CMNT_GPSSATELLITES = 49
Global Const CMNT_GPSSTATUS = 50
Global Const CMNT_GPSMEASUREMODE = 51
Global Const CMNT_GPSDOP = 52
Global Const CMNT_GPSSPEEDREF = 53
Global Const CMNT_GPSSPEED = 54
Global Const CMNT_GPSTRACKREF = 55
Global Const CMNT_GPSTRACK = 56
Global Const CMNT_GPSIMGDIRECTIONREF = 57
Global Const CMNT_GPSIMGDIRECTION = 58
Global Const CMNT_GPSMAPDATUM = 59
Global Const CMNT_GPSDESTLATITUDEREF = 60
Global Const CMNT_GPSDESTLATITUDE = 61
Global Const CMNT_GPSDESTLONGITUDEREF = 62
Global Const CMNT_GPSDESTLONGITUDE = 63
Global Const CMNT_GPSDESTBEARINGREF = 64
Global Const CMNT_GPSDESTBEARING = 65
Global Const CMNT_GPSDESTDISTANCEREF = 66
Global Const CMNT_GPSDESTDISTANCE = 67

' Exif 2.0 comments - comments introduced since Exif 1.1
Global Const CMNT_SUPPORTEDFLASHPIXVERSION = 158   ' Supported FlashPix version (Exif)
Global Const CMNT_COLORSPACE = 159                 ' Color space (Exif)
Global Const CMNT_EXPOSUREPROGRAM = 160            ' Exposure program (Exif)
Global Const CMNT_SZSPECTRALSENSITIVITY = 161      ' Spectral sensitivity (Exif)
Global Const CMNT_ISOSPEEDRATINGS = 162            ' ISO speed ratings (Exif)
Global Const CMNT_OPTOELECTRICCOEFFICIENT = 163    ' Optoelectric coefficient (Exif)
Global Const CMNT_SZRELATEDSOUNDFILE = 164         ' Related audio file (Exif)
Global Const CMNT_FLASHENERGY = 165                ' Flash energy (Exif)
Global Const CMNT_SPATIALFREQUENCYRESPONSE = 166   ' Spatial frequency response (Exif)
Global Const CMNT_FOCALPLANEXRESOLUTION = 167      ' Focal plane X Resolution (Exif)
Global Const CMNT_FOCALPLANEYRESOLUTION = 168      ' Focal plane Y Resolution (Exif)
Global Const CMNT_SUBJECTLOCATION = 169            ' Subject location (Exif)
Global Const CMNT_EXPOSUREINDEX = 170              ' Exposure index (Exif)
Global Const CMNT_SENSINGMETHOD = 171              ' Sensing method (Exif)
Global Const CMNT_FILESOURCE = 172                 ' File source (Exif)
Global Const CMNT_SCENETYPE = 173                  ' Scene type (Exif)
Global Const CMNT_CFAPATTERN = 174                 ' CFA Pattern (Exif)

Global Const CMNT_SZTITLE = 175               ' Title or caption for image
Global Const CMNT_SZDISCLAIMER = 176          ' Legal Disclaimer
Global Const CMNT_SZWARNING = 177             ' Warning of nature of content
Global Const CMNT_MISC = 178                  ' Miscellaneous comment


Global Const CMNT_J2K_BINARY = 179 ' Jpeg 2000 binary comment
Global Const CMNT_J2K_LATIN = 180  ' Jpeg 2000 latin comment

' IPTC comments
Global Const IPTC_SEPARATOR = 1 ' '\001' is a separator used for repeatable comments

Global Const CMNT_IPTC_FIRST = 181   ' The first IPTC comment
Global Const CMNT_IPTC_VERSION = 181   ' The version of IPTC comments (read-only)
Global Const CMNT_IPTC_OBJECTTYPEREFERENCE = 182
Global Const CMNT_IPTC_OBJECTATTRIBUTEREFERENCE = 183
Global Const CMNT_IPTC_OBJECTNAME = 184
Global Const CMNT_IPTC_EDITSTATUS = 185
Global Const CMNT_IPTC_EDITORIALUPDATE = 186
Global Const CMNT_IPTC_URGENCY = 187
Global Const CMNT_IPTC_SUBJECTREFERENCE = 188
Global Const CMNT_IPTC_CATEGORY = 189
Global Const CMNT_IPTC_SUPPLEMENTALCATEGORY = 190
Global Const CMNT_IPTC_FIXTUREIDENTIFIER = 191
Global Const CMNT_IPTC_KEYWORDS = 192
Global Const CMNT_IPTC_CONTENTLOCATIONCODE = 193
Global Const CMNT_IPTC_CONTENTLOCATIONNAME = 194
Global Const CMNT_IPTC_RELEASEDATE = 195
Global Const CMNT_IPTC_RELEASETIME = 196
Global Const CMNT_IPTC_EXPIRATIONDATE = 197
Global Const CMNT_IPTC_EXPIRATIONTIME = 198
Global Const CMNT_IPTC_SPECIALINSTRUCTIONS = 199
Global Const CMNT_IPTC_ACTIONADVISED = 200
Global Const CMNT_IPTC_REFERENCESERVICE = 201
Global Const CMNT_IPTC_REFERENCEDATE = 202
Global Const CMNT_IPTC_REFERENCENUMBER = 203
Global Const CMNT_IPTC_DATECREATED = 204
Global Const CMNT_IPTC_TIMECREATED = 205
Global Const CMNT_IPTC_DIGITALCREATIONDATE = 206
Global Const CMNT_IPTC_DIGITALCREATIONTIME = 207
Global Const CMNT_IPTC_ORIGINATINGPROGRAM = 208
Global Const CMNT_IPTC_PROGRAMVERSION = 209
Global Const CMNT_IPTC_OBJECTCYCLE = 210
Global Const CMNT_IPTC_BYLINE = 211
Global Const CMNT_IPTC_BYLINETITLE = 212
Global Const CMNT_IPTC_CITY = 213
Global Const CMNT_IPTC_SUBLOCATION = 214
Global Const CMNT_IPTC_PROVINCE_STATE = 215
Global Const CMNT_IPTC_PRIMARYLOCATIONCODE = 216
Global Const CMNT_IPTC_PRIMARYLOCATIONNAME = 217
Global Const CMNT_IPTC_ORIGINALTRANSMISSIONREFERENCE = 218
Global Const CMNT_IPTC_HEADLINE = 219
Global Const CMNT_IPTC_CREDIT = 220
Global Const CMNT_IPTC_SOURCE = 221
Global Const CMNT_IPTC_COPYRIGHT = 222
Global Const CMNT_IPTC_CONTACT = 223
Global Const CMNT_IPTC_CAPTION = 224
Global Const CMNT_IPTC_AUTHOR = 225
Global Const CMNT_IPTC_LANGUAGEIDENTIFIER = 226
Global Const CMNT_IPTC_LAST = 226   ' The last IPTC comment
Global Const CMNT_SUBJECTAREA = 227 'The location and area of the main
                                    'subject in the overall scene.
                                    'Data Type: SHORT. Length: 2, 3 or 4
Global Const CMNT_CUSTOMRENDERED = 228           'Data Type: SHORT. Length: 1
Global Const CMNT_EXPOSUREMODE = 229             'Data Type: SHORT. Length: 1
Global Const CMNT_WHITEBALANCE = 230             'Data Type: SHORT. Length: 1
Global Const CMNT_DIGITALZOOMRATIO = 231         'Data Type: RATIONAL. Length: 1
Global Const CMNT_FOCALLENGTHIN35MMFILM = 232    'Data Type: SHORT. Length: 1
Global Const CMNT_SCENECAPTURETYPE = 233         'Data Type: SHORT. Length: 1
Global Const CMNT_GAINCONTROL = 234              'Data Type: SHORT. Length: 1
Global Const CMNT_CONTRAST = 235                 'Data Type: SHORT. Length: 1
Global Const CMNT_SATURATION = 236               'Data Type: SHORT. Length: 1
Global Const CMNT_SHARPNESS = 237                'Data Type: SHORT. Length: 1
Global Const CMNT_DEVICESETTINGDESCRIPTION = 238 'Data Type: BYTE. Length: any
Global Const CMNT_SUBJECTDISTANCERANGE = 239     'Data Type: SHORT. Length: 1
Global Const CMNT_SZIMAGEUNIQUEID = 240          'Data Type: ASCII. Length: 33

' ***NEW*** Exif GPS 2.2 comments
Global Const CMNT_GPSPROCESSINGMETHOD = 241      'Data Type: BYTE. Length: any
Global Const CMNT_GPSAREAINFORMATION = 242       'Data Type: BYTE. Length: any
Global Const CMNT_GPSDATESTAMP = 243             'Data Type: ASCII. Length: 11
Global Const CMNT_GPSDIFFERENTIAL = 244          'Data Type: SHORT. Length: 1


Global Const CMNT_LAST = 244                     ' Last defined number for comments
Global Const CMNT_ALL = &HFFFF

'TIFF Tag types
Global Const TAG_BYTE = 1
Global Const TAG_ASCII = 2
Global Const TAG_SBYTE = 6
Global Const TAG_UNDEFINED = 7
Global Const TAG_SHORT = 3
Global Const TAG_SSHORT = 8
Global Const TAG_LONG = 4
Global Const TAG_SLONG = 9
Global Const TAG_FLOAT = 11
Global Const TAG_RATIONAL = 5
Global Const TAG_SRATIONAL = 10
Global Const TAG_DOUBLE = 12

' Kodak PCD resolution constants
Global Const L_PCD_BASE_OVER_64 = 0 '  64 x   96
Global Const L_PCD_BASE_OVER_16 = 1 ' 128 x  192
Global Const L_PCD_BASE_OVER_4 = 2  ' 256 x  384
Global Const L_PCD_BASE = 3         ' 512 x  768
Global Const L_PCD_4BASE = 4        '1024 x 1536
Global Const L_PCD_16BASE = 5       '2048 x 3072

Global Const BFLT_DONTCARE = 256

' Filter constants
Global Const BFLT_EROSION_OMNI = 0
Global Const BFLT_EROSION_HORZ = 1
Global Const BFLT_EROSION_VERT = 2
Global Const BFLT_EROSION_DIAG = 3
Global Const BFLT_DILATION_OMNI = 4
Global Const BFLT_DILATION_HORZ = 5
Global Const BFLT_DILATION_VERT = 6
Global Const BFLT_DILATION_DIAG = 7

Global Const FLT_EMBOSS_N = 0
Global Const FLT_EMBOSS_NE = 1
Global Const FLT_EMBOSS_E = 2
Global Const FLT_EMBOSS_SE = 3
Global Const FLT_EMBOSS_S = 4
Global Const FLT_EMBOSS_SW = 5
Global Const FLT_EMBOSS_W = 6
Global Const FLT_EMBOSS_NW = 7

Global Const FLT_GRADIENT_N = 8
Global Const FLT_GRADIENT_NE = 9
Global Const FLT_GRADIENT_E = 10
Global Const FLT_GRADIENT_SE = 11
Global Const FLT_GRADIENT_S = 12
Global Const FLT_GRADIENT_SW = 13
Global Const FLT_GRADIENT_W = 14
Global Const FLT_GRADIENT_NW = 15

Global Const FLT_LAPLACE_1 = 16
Global Const FLT_LAPLACE_2 = 17
Global Const FLT_LAPLACE_3 = 18
Global Const FLT_LAPLACE_DIAG = 19
Global Const FLT_LAPLACE_HORZ = 20
Global Const FLT_LAPLACE_VERT = 21

Global Const FLT_SOBEL_HORZ = 22
Global Const FLT_SOBEL_VERT = 23

Global Const FLT_PREWITT_HORZ = 24
Global Const FLT_PREWITT_VERT = 25

Global Const FLT_SHIFTDIFF_DIAG = 26
Global Const FLT_SHIFTDIFF_HORZ = 27
Global Const FLT_SHIFTDIFF_VERT = 28

Global Const FLT_LINESEG_HORZ = 29
Global Const FLT_LINESEG_VERT = 30
Global Const FLT_LINESEG_LTOR = 31
Global Const FLT_LINESEG_RTOL = 32

'Flags for L_PicturizeBitmap
Global Const PICTURIZE_LOADALL = &H1       ' Load all files in memory
Global Const PICTURIZE_RESIZE = &H2        ' Resize all images that are not the required size
Global Const PICTURIZE_RESAMPLE = &H4      ' Resample all images that are not the required size
Global Const PICTURIZE_ONCE = &H10         ' Use the image only once though the process
Global Const PICTURIZE_SAMELEVEL = &H20    ' Use all images in equility to the number of an image usage
Global Const PICTURIZE_BESTFIT = &H40      ' Use all images to best fit the image

Global Const CONTOUR_THIN = 0
Global Const CONTOUR_LINK_BLACKWHITE = 1
Global Const CONTOUR_LINK_GRAY = 2
Global Const CONTOUR_LINK_COLOR = 3
Global Const CONTOUR_APPROX_COLOR = 4

Global Const DEFAULT_THRESHOLD = 15      ' default for background threshold value
Global Const DEFAULT_DELTADIRECTION = 35 ' default for maximum angle for the thinning algorithm
Global Const DEFAULT_MAXIMUMERROR = 5    ' default for maximum approximation error

' BumpNickConstants
Global Const SMOOTH_BUMP = 0
Global Const SMOOTH_NICK = 1
Global Const SMOOTH_NONE = 2

' DocImagingReturnConstants
Global Const SUCCESS_REMOVE = 1
Global Const SUCCESS_NOREMOVE = 2
Global Const LINEREMOVE_HORIZONTAL = 1
Global Const LINEREMOVE_VERTICAL = 2
Global Const SUCCESS_INVERT = 1
Global Const SUCCESS_NOINVERT = 2

' SmoothConstants
Global Const SMOOTH_HORIZONTAL_ELEMENT = 0
Global Const SMOOTH_VERTICAL_ELEMENT = 1

' BorderConstants
Global Const BORDER_LEFT = 1
Global Const BORDER_RIGHT = 2
Global Const BORDER_TOP = 4
Global Const BORDER_BOTTOM = 8
Global Const BORDER_ALL = &HF
Global Const BORDER_DELTA_MAX = &HFFFFFFFF

' HolePunchConstants
Global Const HOLEPUNCH_LEFT = 1
Global Const HOLEPUNCH_RIGHT = 2
Global Const HOLEPUNCH_TOP = 3
Global Const HOLEPUNCH_BOTTOM = 4

' DocImagingFlags
Global Const FLAG_USE_DPI = &H1
Global Const FLAG_SINGLE_REGION = &H2
Global Const FLAG_LEAD_REGION = &H4
Global Const FLAG_CALLBACK_REGION = &H8
Global Const FLAG_IMAGE_UNCHANGED = &H10
Global Const FLAG_USE_SIZE = &H20
Global Const FLAG_USE_COUNT = &H40
Global Const FLAG_USE_LOCATION = &H80
Global Const FLAG_FAVOR_LONG = &H100
Global Const FLAG_REMOVE_ENTIRE = &H200
Global Const FLAG_USE_GAP = &H400
Global Const FLAG_USE_VARIANCE = &H800

' SmoothFlags
Global Const SMOOTH_SINGLE_REGION = &H2          ' FLAG_SINGLE_REGION
Global Const SMOOTH_LEAD_REGION = &H4            ' FLAG_LEAD_REGION
Global Const SMOOTH_IMAGE_UNCHANGED = &H10       ' FLAG_IMAGE_UNCHANGED
Global Const SMOOTH_FAVOR_LONG = &H100           ' FLAG_FAVOR_LONG
Global Const SMOOTH_ALLFLAGS = &H116             ' SMOOTH_SINGLE_REGION|SMOOTH_LEAD_REGION|SMOOTH_IMAGE_UNCHANGED|SMOOTH_FAVOR_LONG

' LineRemoveFlags
Global Const LINE_USE_DPI = &H1                  ' FLAG_USE_DPI
Global Const LINE_SINGLE_REGION = &H2            ' FLAG_SINGLE_REGION
Global Const LINE_LEAD_REGION = &H4              ' FLAG_LEAD_REGION
Global Const LINE_CALLBACK_REGION = &H8          ' FLAG_CALLBACK_REGION
Global Const LINE_IMAGE_UNCHANGED = &H10         ' FLAG_IMAGE_UNCHANGED
Global Const LINE_REMOVE_ENTIRE = &H200          ' FLAG_REMOVE_ENTIRE
Global Const LINE_USE_GAP = &H400                ' FLAG_USE_GAP
Global Const LINE_USE_VARIANCE = &H800           ' FLAG_USE_VARIANCE
Global Const LINE_ALLFLAGS = &HE1F               ' LINE_USE_DPI|LINE_SINGLE_REGION|LINE_LEAD_REGION|LINE_CALLBACK_REGION|LINE_REMOVE_ENTIRE|LINE_USE_GAP|LINE_USE_VARIANCE

' BorderRemoveFlags
Global Const BORDER_LEAD_REGION = &H4             ' FLAG_LEAD_REGION
Global Const BORDER_CALLBACK_REGION = &H8         ' FLAG_CALLBACK_REGION
Global Const BORDER_SINGLE_REGION = &H2           ' FLAG_SINGLE_REGION
Global Const BORDER_IMAGE_UNCHANGED = &H10        ' FLAG_IMAGE_UNCHANGED
Global Const BORDER_USE_VARIANCE = &H800          ' FLAG_USE_VARIANCE
Global Const BORDER_ALLFLAGS = &H81E              ' BORDER_LEAD_REGION|BORDER_CALLBACK_REGION|BORDER_SINGLE_REGION|BORDER_IMAGE_UNCHANGED|BORDER_USE_VARIANCE

' InvertedTextFlags
Global Const INVERTEDTEXT_USE_DPI = &H1                ' FLAG_USE_DPI
Global Const INVERTEDTEXT_SINGLE_REGION = &H2          ' FLAG_SINGLE_REGION
Global Const INVERTEDTEXT_LEAD_REGION = &H4            ' FLAG_LEAD_REGION
Global Const INVERTEDTEXT_CALLBACK_REGION = &H8        ' FLAG_CALLBACK_REGION
Global Const INVERTEDTEXT_IMAGE_UNCHANGED = &H10       ' FLAG_IMAGE_UNCHANGED
Global Const INVERTEDTEXT_ALLFLAGS = &H1F              ' INVERTEDTEXT_USE_DPI|INVERTEDTEXT_SINGLE_REGION|INVERTEDTEXT_LEAD_REGION|INVERTEDTEXT_CALLBACK_REGION|INVERTEDTEXT_IMAGE_UNCHANGED

' DotRemoveFlags
Global Const DOT_USE_DPI = &H1                   ' FLAG_USE_DPI
Global Const DOT_SINGLE_REGION = &H2             ' FLAG_SINGLE_REGION
Global Const DOT_LEAD_REGION = &H4               ' FLAG_LEAD_REGION
Global Const DOT_CALLBACK_REGION = &H8           ' FLAG_CALLBACK_REGION
Global Const DOT_IMAGE_UNCHANGED = &H10          ' FLAG_IMAGE_UNCHANGED
Global Const DOT_USE_SIZE = &H20                 ' FLAG_USE_SIZE
Global Const DOT_ALLFLAGS = &H3F                 ' DOT_USE_DPI|DOT_SINGLE_REGION|DOT_LEAD_REGION|DOT_CALLBACK_REGION|DOT_IMAGE_UNCHANGED|DOT_USE_SIZE

' HolePunchRemoveFlags
Global Const HOLEPUNCH_USE_DPI = &H1                 ' FLAG_USE_DPI
Global Const HOLEPUNCH_SINGLE_REGION = &H2           ' FLAG_SINGLE_REGION
Global Const HOLEPUNCH_LEAD_REGION = &H4             ' FLAG_LEAD_REGION
Global Const HOLEPUNCH_CALLBACK_REGION = &H8         ' FLAG_CALLBACK_REGION
Global Const HOLEPUNCH_IMAGE_UNCHANGED = &H10        ' FLAG_IMAGE_UNCHANGED
Global Const HOLEPUNCH_USE_SIZE = &H20               ' FLAG_USE_SIZE
Global Const HOLEPUNCH_USE_COUNT = &H40              ' FLAG_USE_COUNT
Global Const HOLEPUNCH_USE_LOCATION = &H80           ' FLAG_USE_LOCATION
Global Const HOLEPUNCH_ALLFLAGS = &HFF               ' HOLEPUNCH_USE_DPI|HOLEPUNCH_SINGLE_REGION|HOLEPUNCH_LEAD_REGION|HOLEPUNCH_CALLBACK_REGION|HOLEPUNCH_IMAGE_UNCHANGED|HOLEPUNCH_USE_SIZE|HOLEPUNCH_USE_COUNT|HOLEPUNCH_USE_LOCATION

'   L_PaintDCBuffer Constants
Global Const PAINTDC_COMPRESSED = -1

' StartMagGlass Constants
Global Const CROSSHAIR_NONE = 0
Global Const CROSSHAIR_FINE = 1
Global Const CROSSHAIR_INVERTPEN = 2
Global Const CROSSHAIR_INVERTSCREEN = 3

' Paint effect constants
' NOTE: some of these are defined in L_OCXEFX.BAS

'effect types
'No effect
Global Const EFX_EFFECT_NONE_CLASS = 1000
Global Const EFX_EFFECT_NONE = (EFX_EFFECT_NONE_CLASS + 0)
Global Const EFX_EFFECT_NO_PICTURE = (EFX_EFFECT_NONE_CLASS + 1)
Global Const EFX_EFFECT_NONE_MAX = (EFX_EFFECT_NONE_CLASS + 1)

'Linear wipe
Global Const EFX_EFFECT_WIPE_CLASS = 2000

'Rectangular wipe
Global Const EFX_EFFECT_WIPE_RECTANGLE_CLASS = 3000
Global Const EFX_EFFECT_WIPE_RECTANGLE_IN = (EFX_EFFECT_WIPE_RECTANGLE_CLASS + 0)
Global Const EFX_EFFECT_WIPE_RECTANGLE_OUT = (EFX_EFFECT_WIPE_RECTANGLE_CLASS + 1)
Global Const EFX_EFFECT_WIPE_RECTANGLE_INTER_IN_THEN_IN = (EFX_EFFECT_WIPE_RECTANGLE_CLASS + 2)
Global Const EFX_EFFECT_WIPE_RECTANGLE_INTER_OUT_THEN_OUT = (EFX_EFFECT_WIPE_RECTANGLE_CLASS + 3)
Global Const EFX_EFFECT_WIPE_RECTANGLE_INTER_IN_THEN_OUT = (EFX_EFFECT_WIPE_RECTANGLE_CLASS + 4)
Global Const EFX_EFFECT_WIPE_RECTANGLE_INTER_OUT_THEN_IN = (EFX_EFFECT_WIPE_RECTANGLE_CLASS + 5)
Global Const EFX_EFFECT_WIPE_RECTANGLE_MAX = (EFX_EFFECT_WIPE_RECTANGLE_CLASS + 5)

'Circular wipe
Global Const EFX_EFFECT_WIPE_CIRCLE_CLASS = 4000

'Push
Global Const EFX_EFFECT_PUSH_CLASS = 5000

'Slide
Global Const EFX_EFFECT_SLIDE_CLASS = 6000

'Roll
Global Const EFX_EFFECT_ROLL_CLASS = 7000

'Rotate
Global Const EFX_EFFECT_ROTATE_CLASS = 8000

'Zoom
Global Const EFX_EFFECT_ZOOM_CLASS = 9000
Global Const EFX_EFFECT_ZOOM_TO_C = (EFX_EFFECT_ZOOM_CLASS + 0)
Global Const EFX_EFFECT_ZOOM_FROM_C = (EFX_EFFECT_ZOOM_CLASS + 1)
Global Const EFX_EFFECT_ZOOM_MAX = (EFX_EFFECT_ZOOM_CLASS + 1)

'Drip
Global Const EFX_EFFECT_DRIP_CLASS = 10000
Global Const EFX_EFFECT_DRIP_T_TO_B = (EFX_EFFECT_DRIP_CLASS + 0)
Global Const EFX_EFFECT_DRIP_B_TO_T = (EFX_EFFECT_DRIP_CLASS + 1)
Global Const EFX_EFFECT_DRIP_L_TO_R = (EFX_EFFECT_DRIP_CLASS + 2)
Global Const EFX_EFFECT_DRIP_R_TO_L = (EFX_EFFECT_DRIP_CLASS + 3)
Global Const EFX_EFFECT_DRIP_MAX = (EFX_EFFECT_DRIP_CLASS + 3)

'Blind
Global Const EFX_EFFECT_BLIND_CLASS = 11000
Global Const EFX_EFFECT_BLIND_T_TO_B = (EFX_EFFECT_BLIND_CLASS + 0)
Global Const EFX_EFFECT_BLIND_L_TO_R = (EFX_EFFECT_BLIND_CLASS + 1)
Global Const EFX_EFFECT_BLIND_GROWING_L_TO_R = (EFX_EFFECT_BLIND_CLASS + 2)
Global Const EFX_EFFECT_BLIND_GROWING_R_TO_L = (EFX_EFFECT_BLIND_CLASS + 3)
Global Const EFX_EFFECT_BLIND_GROWING_T_TO_B = (EFX_EFFECT_BLIND_CLASS + 4)
Global Const EFX_EFFECT_BLIND_GROWING_B_TO_T = (EFX_EFFECT_BLIND_CLASS + 5)
Global Const EFX_EFFECT_BLIND2_T_TO_B_AND_L_TO_R = (EFX_EFFECT_BLIND_CLASS + 6)
Global Const EFX_EFFECT_BLIND_MAX = (EFX_EFFECT_BLIND_CLASS + 6)

'Random
Global Const EFX_EFFECT_RANDOM_CLASS = 12000
Global Const EFX_EFFECT_RANDOM_BARS_R_TO_L = (EFX_EFFECT_RANDOM_CLASS + 0)
Global Const EFX_EFFECT_RANDOM_BARS_L_TO_R = (EFX_EFFECT_RANDOM_CLASS + 1)
Global Const EFX_EFFECT_RANDOM_BARS_B_TO_T = (EFX_EFFECT_RANDOM_CLASS + 2)
Global Const EFX_EFFECT_RANDOM_BARS_T_TO_B = (EFX_EFFECT_RANDOM_CLASS + 3)
Global Const EFX_EFFECT_RANDOM_LINES = (EFX_EFFECT_RANDOM_CLASS + 4)
Global Const EFX_EFFECT_RANDOM_BLOCKS = (EFX_EFFECT_RANDOM_CLASS + 5)
Global Const EFX_EFFECT_RANDOM_BLOCKS_R_TO_L = (EFX_EFFECT_RANDOM_CLASS + 6)
Global Const EFX_EFFECT_RANDOM_BLOCKS_L_TO_R = (EFX_EFFECT_RANDOM_CLASS + 7)
Global Const EFX_EFFECT_RANDOM_BLOCKS_B_TO_T = (EFX_EFFECT_RANDOM_CLASS + 8)
Global Const EFX_EFFECT_RANDOM_BLOCKS_T_TO_B = (EFX_EFFECT_RANDOM_CLASS + 9)
Global Const EFX_EFFECT_RANDOM_MAX = (EFX_EFFECT_RANDOM_CLASS + 9)

'Checkerboard
Global Const EFX_EFFECT_CHECKERBOARD_CLASS = 13000
Global Const EFX_EFFECT_CHECKERBOARD_T_TO_B_THEN_T_TO_B = (EFX_EFFECT_CHECKERBOARD_CLASS + 0)
Global Const EFX_EFFECT_CHECKERBOARD_B_TO_T_THEN_B_TO_T = (EFX_EFFECT_CHECKERBOARD_CLASS + 1)
Global Const EFX_EFFECT_CHECKERBOARD_L_TO_R_THEN_L_TO_R = (EFX_EFFECT_CHECKERBOARD_CLASS + 2)
Global Const EFX_EFFECT_CHECKERBOARD_R_TO_L_THEN_R_TO_L = (EFX_EFFECT_CHECKERBOARD_CLASS + 3)
Global Const EFX_EFFECT_CHECKERBOARD_T_TO_B_THEN_B_TO_T = (EFX_EFFECT_CHECKERBOARD_CLASS + 4)
Global Const EFX_EFFECT_CHECKERBOARD_B_TO_T_THEN_T_TO_B = (EFX_EFFECT_CHECKERBOARD_CLASS + 5)
Global Const EFX_EFFECT_CHECKERBOARD_L_TO_R_THEN_R_TO_L = (EFX_EFFECT_CHECKERBOARD_CLASS + 6)
Global Const EFX_EFFECT_CHECKERBOARD_R_TO_L_THEN_L_TO_R = (EFX_EFFECT_CHECKERBOARD_CLASS + 7)
Global Const EFX_EFFECT_CHECKERBOARD_MAX = (EFX_EFFECT_CHECKERBOARD_CLASS + 7)

'Blocks
Global Const EFX_EFFECT_BLOCKS_CLASS = 14000
Global Const EFX_EFFECT_BLOCKS_T_TO_B = (EFX_EFFECT_BLOCKS_CLASS + 0)
Global Const EFX_EFFECT_BLOCKS_B_TO_T = (EFX_EFFECT_BLOCKS_CLASS + 1)
Global Const EFX_EFFECT_BLOCKS_L_TO_R = (EFX_EFFECT_BLOCKS_CLASS + 2)
Global Const EFX_EFFECT_BLOCKS_R_TO_L = (EFX_EFFECT_BLOCKS_CLASS + 3)
Global Const EFX_EFFECT_BLOCKS_SWIRL_CW_TO_C = (EFX_EFFECT_BLOCKS_CLASS + 4)
Global Const EFX_EFFECT_BLOCKS_SWIRL_CW_FROM_C = (EFX_EFFECT_BLOCKS_CLASS + 5)
Global Const EFX_EFFECT_BLOCKS_SWIRL_CCW_TO_C = (EFX_EFFECT_BLOCKS_CLASS + 6)
Global Const EFX_EFFECT_BLOCKS_SWIRL_CCW_FROM_C = (EFX_EFFECT_BLOCKS_CLASS + 7)
Global Const EFX_EFFECT_BLOCKS_MAX = (EFX_EFFECT_BLOCKS_CLASS + 7)

'Circle
Global Const EFX_EFFECT_CIRCLE_CLASS = 15000

'Ellipse
Global Const EFX_EFFECT_ELLIPSE_CLASS = 16000

'old effect constants
'Global Const EFFECT_NONE = EFX_EFFECT_NONE
'Global Const EFFECT_WIPE_DOWN = EFX_EFFECT_WIPE_T_TO_B
'Global Const EFFECT_WIPE_UP = EFX_EFFECT_WIPE_B_TO_T
'Global Const EFFECT_WIPE_RIGHT = EFX_EFFECT_WIPE_L_TO_R
'Global Const EFFECT_WIPE_LEFT = EFX_EFFECT_WIPE_R_TO_L
'Global Const EFFECT_RANDOM_PIXEL = EFX_EFFECT_RANDOM_BLOCKS                                 'close match - use the grain size
'Global Const EFFECT_RANDOM_SMALLBOX = EFX_EFFECT_RANDOM_BLOCKS                              'close match - use the grain size
'Global Const EFFECT_RANDOM_MEDIUMBOX = EFX_EFFECT_RANDOM_BLOCKS                             'close match - use the grain size
'Global Const EFFECT_RANDOM_LARGEBOX = EFX_EFFECT_RANDOM_BLOCKS                              'close match - use the grain size
'Global Const EFFECT_RANDOM_HLINE = EFX_EFFECT_RANDOM_LINES                                 'close match - use the grain size
'Global Const EFFECT_RANDOM_VLINE = EFX_EFFECT_RANDOM_LINES                                 'close match - use the grain size
'Global Const EFFECT_VMIDDLE = EFX_EFFECT_WIPE2_C_TO_LB_AND_RT
'Global Const EFFECT_HMIDDLE = EFX_EFFECT_WIPE2_C_TO_LT_AND_RB
'Global Const EFFECT_HINTERLACE = EFX_EFFECT_BLIND_T_TO_B                                   'close match
'Global Const EFFECT_VINTERLACE = EFX_EFFECT_BLIND_L_TO_R                                   'close match
'Global Const EFFECT_HINTERLACE_OUTWARD = EFX_EFFECT_WIPE_INTERV_C_TO_L_AND_R               'close match
'Global Const EFFECT_VINTERLACE_OUTWARD = EFX_EFFECT_WIPE_INTERH_C_TO_T_AND_B               'close match
'Global Const EFFECT_OUTTOIN = EFX_EFFECT_WIPE_RECTANGLE_IN
'Global Const EFFECT_INTOOUT = EFX_EFFECT_WIPE_RECTANGLE_OUT
'Global Const EFFECT_OUTTOIN_INTERLACE = EFX_EFFECT_WIPE_RECTANGLE_INTER_IN_THEN_IN         'close match
'Global Const EFFECT_INTOOUT_INTERLACE = EFX_EFFECT_WIPE_RECTANGLE_INTER_OUT_THEN_OUT       'close match
'Global Const EFFECT_SPIRAL_IN = EFX_EFFECT_BLOCKS_SWIRL_CW_TO_C
'Global Const EFFECT_SPIRAL_OUT = EFX_EFFECT_BLOCKS_SWIRL_CW_FROM_C
'Global Const EFFECT_HMIDDLE_INWARD = EFX_EFFECT_WIPE2_LT_AND_RB_TO_C
'Global Const EFFECT_VMIDDLE_INWARD = EFX_EFFECT_WIPE2_LB_AND_RT_TO_C
'Global Const EFFECT_VINTERLACE_INWARD = EFX_EFFECT_WIPE_INTERH_T_AND_B_TO_C                'close match
'Global Const EFFECT_HINTERLACE_INWARD = EFX_EFFECT_WIPE_INTERV_L_AND_R_TO_C                'close match
'Global Const EFFECT_VINTERLACE_RIGHT = EFX_EFFECT_BLIND_T_TO_B                             'close match
'Global Const EFFECT_VINTERLACE_LEFT = EFX_EFFECT_BLIND_T_TO_B                              'close match
'Global Const EFFECT_HINTERLACE_UP = EFX_EFFECT_BLIND_L_TO_R                                'close match
'Global Const EFFECT_HINTERLACE_DOWN = EFX_EFFECT_BLIND_L_TO_R                              'close match'

'   region processing defines
Global Const RGN_AND = 0
Global Const RGN_SET = 1
Global Const RGN_ANDNOTBITMAP = 2
Global Const RGN_ANDNOTRGN = 3
Global Const RGN_OR = 4
Global Const RGN_XOR = 5
Global Const RGN_SETNOT = 6

Global Const POLY_WINDING = 0
Global Const POLY_ALTERNATE = 1

Global Const FRAME_MOVING0 = 0
Global Const FRAME_MOVING1 = 1
Global Const FRAME_MOVING2 = 2
Global Const FRAME_MOVING3 = 3
Global Const FRAME_MOVING4 = 4
Global Const FRAME_MOVING5 = 5
Global Const FRAME_MOVING6 = 6
Global Const FRAME_MOVING7 = 7

' Flags for the LOADFILEOPTIONS structure
Global Const ELO_REVERSEBITS = &H1
Global Const ELO_GLOBALBACKGROUND = &H2
Global Const ELO_GLOBALPALETTE = &H4
Global Const ELO_GLOBALLOOP = &H8
Global Const ELO_ROTATED = &H10               ' Load files with extended ViewPerspective - do not rotate them
Global Const ELO_IGNOREVIEWTRANSFORMS = &H20  ' Load the image without the viewing transformations
Global Const ELO_IGNORECOLORTRANSFORMS = &H40 ' Load the image without the color transformations
Global Const ELO_SIGNED = &H80                ' Load images with signed pixels without conversion
Global Const ELO_DISABLEMMX = &H100            ' Do not use MMX optimized code
Global Const ELO_DISABLEP3 = &H200             ' Do not use P3-specific optimized code
Global Const ELO_USEIFD = &H400                 ' Use the IFD offset

' Flags for the SAVEFILEOPTIONS structure
Global Const ESO_REVERSEBITS = &H1
Global Const ESO_NOSUBFILETYPE = &H2
Global Const ESO_GLOBALBACKGROUND = &H4
Global Const ESO_GLOBALPALETTE = &H8
Global Const ESO_INTERLACED = &H10
Global Const ESO_GLOBALLOOP = &H20
Global Const ESO_NOPALETTE = &H40             ' save grayscale TIF without a palette
Global Const ESO_SAVEWITHSTAMP = &H80         ' save a stamp if format supports it
Global Const ESO_FIXEDPALETTESTAMP = &H100     ' save fixed palette stamps
Global Const ESO_YCCSTAMP = &H200              ' save YCbCr stamps
Global Const ESO_REPLACEPAGE = &H400           ' Replace the page specified by PageNumber
Global Const ESO_INSERTPAGE = &H800            ' Insert image before the page specified by PageNumber
Global Const ESO_JPEGSTAMP = &H1000             ' save JPEG compressed stamps
Global Const ESO_DISABLEMMX = &H2000            ' Do not use MMX optimized code
Global Const ESO_SAVEOLDJTIF = &H4000           ' Write old style JTIF files
Global Const ESO_NOPAGENUMBER = &H8000          ' Do not save/update the PageNumber tag
Global Const ESO_DISABLEP3 = &H10000            ' Do not use P3-specific optimized code
Global Const ESO_USEIFD = &H20000               ' Use the IFD offset
Global Const ESO_MOTOROLAORDER = &H40000        ' When possible, save files in Motorola byte order

Global Const ESO_WITHOUTTIMESTAMP = &H80000 ' save without time stamp

Global Const ESO_PDF_TEXT_ENCODING_NONE = &H0       ' PDF, no text encoding
Global Const ESO_PDF_TEXT_ENCODING_ASCII_BASE85 = &H100000  ' PDF, ASCII BASE85 text encoding
Global Const ESO_PDF_TEXT_ENCODING_ASCII_HEX = &H200000  ' PDF, ASCII HEX text encoding

Global Const ESO_PDF_TEXT_ENCODING_MASK = &H300000  ' mask of the flags used for PDF text encoding
Global Const ESO_PAD4 = &H400000  ' Each line is padded to a multiple of 4 bytes (raw data only)
Global Const ESO_PLT_BEZIER_CURVES = &H800000  ' PLT filter should save bezier curves
Global Const ESO_PDF_SAVE_USE_BITMAP_DPI = &H1000000  ' Use bitmap  DPI in calculating page dimensions when saving a PDF file
Global Const ESO_PHOTOMETRICINTERPRETATIONVALID = &H2000000
Global Const ESO_TILEINFOVALID = &H4000000  ' Use TileWidth and TileHeight when saving TIFF files


'    playback state constants

Global Const PLAYSTATE_PRECLEAR = &H0
Global Const PLAYSTATE_POSTCLEAR = &H1
Global Const PLAYSTATE_PRERENDER = &H2
Global Const PLAYSTATE_RENDER = &H3
Global Const PLAYSTATE_POSTRENDER = &H4
Global Const PLAYSTATE_WAITINPUT = &H5
Global Const PLAYSTATE_WAITDELAY = &H6
Global Const PLAYSTATE_WAITINPUTDELAY = &H7
Global Const PLAYSTATE_PREDISPOSE = &H8
Global Const PLAYSTATE_POSTDISPOSE = &H9
Global Const PLAYSTATE_END = &HA

'    playback disposal constants

Global Const PLAYDISPOSE_NONE = 0
Global Const PLAYDISPOSE_LEAVE = 1
Global Const PLAYDISPOSE_RESTOREBACKGROUND = 2
Global Const PLAYDISPOSE_RESTOREPREVIOUS = 3


'   transition types

'Linear
Global Const EFX_GRADIENT_LINE_CLASS = 1000
Global Const EFX_GRADIENT_LINE_L_TO_R = (EFX_GRADIENT_LINE_CLASS + 0)
Global Const EFX_GRADIENT_LINE_R_TO_L = (EFX_GRADIENT_LINE_CLASS + 1)
Global Const EFX_GRADIENT_LINE_T_TO_B = (EFX_GRADIENT_LINE_CLASS + 2)
Global Const EFX_GRADIENT_LINE_B_TO_T = (EFX_GRADIENT_LINE_CLASS + 3)
Global Const EFX_GRADIENT_LINE_LT_TO_RB = (EFX_GRADIENT_LINE_CLASS + 4)
Global Const EFX_GRADIENT_LINE_LB_TO_RT = (EFX_GRADIENT_LINE_CLASS + 5)
Global Const EFX_GRADIENT_LINE_RT_TO_LB = (EFX_GRADIENT_LINE_CLASS + 6)
Global Const EFX_GRADIENT_LINE_RB_TO_LT = (EFX_GRADIENT_LINE_CLASS + 7)
Global Const EFX_GRADIENT_LINE2_L_AND_R_TO_C = (EFX_GRADIENT_LINE_CLASS + 8)
Global Const EFX_GRADIENT_LINE2_C_TO_L_AND_R = (EFX_GRADIENT_LINE_CLASS + 9)
Global Const EFX_GRADIENT_LINE2_T_AND_B_TO_C = (EFX_GRADIENT_LINE_CLASS + 10)
Global Const EFX_GRADIENT_LINE2_C_TO_T_AND_B = (EFX_GRADIENT_LINE_CLASS + 11)
Global Const EFX_GRADIENT_LINE2_LT_AND_RB_TO_C = (EFX_GRADIENT_LINE_CLASS + 12)
Global Const EFX_GRADIENT_LINE2_C_TO_LT_AND_RB = (EFX_GRADIENT_LINE_CLASS + 13)
Global Const EFX_GRADIENT_LINE2_RT_AND_LB_TO_C = (EFX_GRADIENT_LINE_CLASS + 14)
Global Const EFX_GRADIENT_LINE2_C_TO_RT_AND_LB = (EFX_GRADIENT_LINE_CLASS + 15)
Global Const EFX_GRADIENT_LINE_MAX = (EFX_GRADIENT_LINE_CLASS + 15)

'Angular
Global Const EFX_GRADIENT_ANGLE_CLASS = 2000
Global Const EFX_GRADIENT_ANGLE_TO_LT = (EFX_GRADIENT_ANGLE_CLASS + 0)
Global Const EFX_GRADIENT_ANGLE_TO_LB = (EFX_GRADIENT_ANGLE_CLASS + 1)
Global Const EFX_GRADIENT_ANGLE_TO_RT = (EFX_GRADIENT_ANGLE_CLASS + 2)
Global Const EFX_GRADIENT_ANGLE_TO_RB = (EFX_GRADIENT_ANGLE_CLASS + 3)
Global Const EFX_GRADIENT_ANGLE_FROM_LT = (EFX_GRADIENT_ANGLE_CLASS + 4)
Global Const EFX_GRADIENT_ANGLE_FROM_LB = (EFX_GRADIENT_ANGLE_CLASS + 5)
Global Const EFX_GRADIENT_ANGLE_FROM_RT = (EFX_GRADIENT_ANGLE_CLASS + 6)
Global Const EFX_GRADIENT_ANGLE_FROM_RB = (EFX_GRADIENT_ANGLE_CLASS + 7)
Global Const EFX_GRADIENT_ANGLE_MAX = (EFX_GRADIENT_ANGLE_CLASS + 7)

'Rectangular
Global Const EFX_GRADIENT_RECTANGLE_CLASS = 3000
Global Const EFX_GRADIENT_RECTANGLE_TO_C = (EFX_GRADIENT_RECTANGLE_CLASS + 0)
Global Const EFX_GRADIENT_RECTANGLE_FROM_C = (EFX_GRADIENT_RECTANGLE_CLASS + 1)
Global Const EFX_GRADIENT_RECTANGLE_MAX = (EFX_GRADIENT_RECTANGLE_CLASS + 1)

'Elliptical
Global Const EFX_GRADIENT_ELLIPSE_CLASS = 4000
Global Const EFX_GRADIENT_ELLIPSE_TO_C = (EFX_GRADIENT_ELLIPSE_CLASS + 0)
Global Const EFX_GRADIENT_ELLIPSE_FROM_C = (EFX_GRADIENT_ELLIPSE_CLASS + 1)
Global Const EFX_GRADIENT_ELLIPSE_MAX = (EFX_GRADIENT_ELLIPSE_CLASS + 1)

'Conical
Global Const EFX_GRADIENT_CONE_CLASS = 5000
Global Const EFX_GRADIENT_CONE_FROM_L = (EFX_GRADIENT_CONE_CLASS + 0)
Global Const EFX_GRADIENT_CONE_FROM_R = (EFX_GRADIENT_CONE_CLASS + 1)
Global Const EFX_GRADIENT_CONE_FROM_T = (EFX_GRADIENT_CONE_CLASS + 2)
Global Const EFX_GRADIENT_CONE_FROM_B = (EFX_GRADIENT_CONE_CLASS + 3)
Global Const EFX_GRADIENT_CONE_FROM_LT = (EFX_GRADIENT_CONE_CLASS + 4)
Global Const EFX_GRADIENT_CONE_FROM_LB = (EFX_GRADIENT_CONE_CLASS + 5)
Global Const EFX_GRADIENT_CONE_FROM_RT = (EFX_GRADIENT_CONE_CLASS + 6)
Global Const EFX_GRADIENT_CONE_FROM_RB = (EFX_GRADIENT_CONE_CLASS + 7)
Global Const EFX_GRADIENT_CONE_MAX = (EFX_GRADIENT_CONE_CLASS + 7)

Global Const EFX_PATTERN_CLASS = 0
Global Const EFX_PATTERN_SOLID = (EFX_PATTERN_CLASS + 0)
Global Const EFX_PATTERN_TRANSPARENT = (EFX_PATTERN_CLASS + 1)
Global Const EFX_PATTERN_HORZ_LINE = (EFX_PATTERN_CLASS + 2)
Global Const EFX_PATTERN_VERT_LINE = (EFX_PATTERN_CLASS + 3)
Global Const EFX_PATTERN_DOWNWARD_DIAG = (EFX_PATTERN_CLASS + 4)
Global Const EFX_PATTERN_UPWARD_DIAG = (EFX_PATTERN_CLASS + 5)
Global Const EFX_PATTERN_CROSS = (EFX_PATTERN_CLASS + 6)
Global Const EFX_PATTERN_DIAG_CROSS = (EFX_PATTERN_CLASS + 7)
Global Const EFX_PATTERN_MAX = (EFX_PATTERN_CLASS + 7)

'Pattern
Global Const EFX_TRANS_PATTERN_CLASS = 0
Global Const EFX_TRANS_SOLID = (EFX_TRANS_PATTERN_CLASS + 0)
Global Const EFX_TRANS_HORZ_LINE = (EFX_TRANS_PATTERN_CLASS + 1)
Global Const EFX_TRANS_VERT_LINE = (EFX_TRANS_PATTERN_CLASS + 2)
Global Const EFX_TRANS_DOWNWARD_DIAG = (EFX_TRANS_PATTERN_CLASS + 3)
Global Const EFX_TRANS_UPWARD_DIAG = (EFX_TRANS_PATTERN_CLASS + 4)
Global Const EFX_TRANS_CROSS = (EFX_TRANS_PATTERN_CLASS + 5)
Global Const EFX_TRANS_DIAG_CROSS = (EFX_TRANS_PATTERN_CLASS + 6)
Global Const EFX_TRANS_PATTERN_MAX = (EFX_TRANS_PATTERN_CLASS + 6)

'Linear gradient
Global Const EFX_TRANS_GRADIENT_LINE_CLASS = EFX_GRADIENT_LINE_CLASS
Global Const EFX_TRANS_GRADIENT_LINE_L_TO_R = EFX_GRADIENT_LINE_L_TO_R
Global Const EFX_TRANS_GRADIENT_LINE_R_TO_L = EFX_GRADIENT_LINE_R_TO_L
Global Const EFX_TRANS_GRADIENT_LINE_T_TO_B = EFX_GRADIENT_LINE_T_TO_B
Global Const EFX_TRANS_GRADIENT_LINE_B_TO_T = EFX_GRADIENT_LINE_B_TO_T
Global Const EFX_TRANS_GRADIENT_LINE_LT_TO_RB = EFX_GRADIENT_LINE_LT_TO_RB
Global Const EFX_TRANS_GRADIENT_LINE_LB_TO_RT = EFX_GRADIENT_LINE_LB_TO_RT
Global Const EFX_TRANS_GRADIENT_LINE_RT_TO_LB = EFX_GRADIENT_LINE_RT_TO_LB
Global Const EFX_TRANS_GRADIENT_LINE_RB_TO_LT = EFX_GRADIENT_LINE_RB_TO_LT
Global Const EFX_TRANS_GRADIENT_LINE2_L_AND_R_TO_C = EFX_GRADIENT_LINE2_L_AND_R_TO_C
Global Const EFX_TRANS_GRADIENT_LINE2_C_TO_L_AND_R = EFX_GRADIENT_LINE2_C_TO_L_AND_R
Global Const EFX_TRANS_GRADIENT_LINE2_T_AND_B_TO_C = EFX_GRADIENT_LINE2_T_AND_B_TO_C
Global Const EFX_TRANS_GRADIENT_LINE2_C_TO_T_AND_B = EFX_GRADIENT_LINE2_C_TO_T_AND_B
Global Const EFX_TRANS_GRADIENT_LINE2_LT_AND_RB_TO_C = EFX_GRADIENT_LINE2_LT_AND_RB_TO_C
Global Const EFX_TRANS_GRADIENT_LINE2_C_TO_LT_AND_RB = EFX_GRADIENT_LINE2_C_TO_LT_AND_RB
Global Const EFX_TRANS_GRADIENT_LINE2_RT_AND_LB_TO_C = EFX_GRADIENT_LINE2_RT_AND_LB_TO_C
Global Const EFX_TRANS_GRADIENT_LINE2_C_TO_RT_AND_LB = EFX_GRADIENT_LINE2_C_TO_RT_AND_LB
Global Const EFX_TRANS_GRADIENT_LINE_MAX = EFX_GRADIENT_LINE_MAX

'Angular gradient
Global Const EFX_TRANS_GRADIENT_ANGLE_CLASS = EFX_GRADIENT_ANGLE_CLASS
Global Const EFX_TRANS_GRADIENT_ANGLE_TO_LT = EFX_GRADIENT_ANGLE_TO_LT
Global Const EFX_TRANS_GRADIENT_ANGLE_TO_LB = EFX_GRADIENT_ANGLE_TO_LB
Global Const EFX_TRANS_GRADIENT_ANGLE_TO_RT = EFX_GRADIENT_ANGLE_TO_RT
Global Const EFX_TRANS_GRADIENT_ANGLE_TO_RB = EFX_GRADIENT_ANGLE_TO_RB
Global Const EFX_TRANS_GRADIENT_ANGLE_FROM_LT = EFX_GRADIENT_ANGLE_FROM_LT
Global Const EFX_TRANS_GRADIENT_ANGLE_FROM_LB = EFX_GRADIENT_ANGLE_FROM_LB
Global Const EFX_TRANS_GRADIENT_ANGLE_FROM_RT = EFX_GRADIENT_ANGLE_FROM_RT
Global Const EFX_TRANS_GRADIENT_ANGLE_FROM_RB = EFX_GRADIENT_ANGLE_FROM_RB
Global Const EFX_TRANS_GRADIENT_ANGLE_MAX = EFX_GRADIENT_ANGLE_MAX

'Rectangular gradient
Global Const EFX_TRANS_GRADIENT_RECTANGLE_CLASS = EFX_GRADIENT_RECTANGLE_CLASS
Global Const EFX_TRANS_GRADIENT_RECTANGLE_TO_C = EFX_GRADIENT_RECTANGLE_TO_C
Global Const EFX_TRANS_GRADIENT_RECTANGLE_FROM_C = EFX_GRADIENT_RECTANGLE_FROM_C
Global Const EFX_TRANS_GRADIENT_RECTANGLE_MAX = EFX_GRADIENT_RECTANGLE_MAX

'Elliptical gradient
Global Const EFX_TRANS_GRADIENT_ELLIPSE_CLASS = EFX_GRADIENT_ELLIPSE_CLASS
Global Const EFX_TRANS_GRADIENT_ELLIPSE_TO_C = EFX_GRADIENT_ELLIPSE_TO_C
Global Const EFX_TRANS_GRADIENT_ELLIPSE_FROM_C = EFX_GRADIENT_ELLIPSE_FROM_C
Global Const EFX_TRANS_GRADIENT_ELLIPSE_MAX = EFX_GRADIENT_ELLIPSE_MAX

'Conical gradient
Global Const EFX_TRANS_GRADIENT_CONE_CLASS = EFX_GRADIENT_CONE_CLASS
Global Const EFX_TRANS_GRADIENT_CONE_FROM_L = EFX_GRADIENT_CONE_FROM_L
Global Const EFX_TRANS_GRADIENT_CONE_FROM_R = EFX_GRADIENT_CONE_FROM_R
Global Const EFX_TRANS_GRADIENT_CONE_FROM_T = EFX_GRADIENT_CONE_FROM_T
Global Const EFX_TRANS_GRADIENT_CONE_FROM_B = EFX_GRADIENT_CONE_FROM_B
Global Const EFX_TRANS_GRADIENT_CONE_FROM_LT = EFX_GRADIENT_CONE_FROM_LT
Global Const EFX_TRANS_GRADIENT_CONE_FROM_LB = EFX_GRADIENT_CONE_FROM_LB
Global Const EFX_TRANS_GRADIENT_CONE_FROM_RT = EFX_GRADIENT_CONE_FROM_RT
Global Const EFX_TRANS_GRADIENT_CONE_FROM_RB = EFX_GRADIENT_CONE_FROM_RB
Global Const EFX_TRANS_GRADIENT_CONE_MAX = EFX_GRADIENT_CONE_MAX

Global Const EFX_FRAME_INNER_INSET = &H0
Global Const EFX_FRAME_INNER_RAISED = &H1
Global Const EFX_FRAME_INNER_MASK = &HF
Global Const EFX_FRAME_OUTER_INSET = &H0
Global Const EFX_FRAME_OUTER_RAISED = &H10
Global Const EFX_FRAME_OUTER_MASK = &HF0
Global Const EFX_FRAME_ADJUST_RECT = &H100

Global Const EFX_TEXT_INSETLIGHT = &H0
Global Const EFX_TEXT_INSETHEAVY = &H1
Global Const EFX_TEXT_RAISEDLIGHT = &H2
Global Const EFX_TEXT_RAISEDHEAVY = &H3
Global Const EFX_TEXT_DROPSHADOW = &H4
Global Const EFX_TEXT_BLOCKSHADOW = &H5
Global Const EFX_TEXT_OUTLINEBLOCK = &H6
Global Const EFX_TEXT_INSETEXTRALIGHT = &H7
Global Const EFX_TEXT_INSETEXTRAHEAVY = &H8
Global Const EFX_TEXT_RAISEDEXTRALIGHT = &H9
Global Const EFX_TEXT_RAISEDEXTRAHEAVY = &HA
Global Const EFX_TEXT_STYLEMASK = &HF

Global Const EFX_TEXT_LEFT = &H0
Global Const EFX_TEXT_HCENTER = &H10
Global Const EFX_TEXT_RIGHT = &H20
Global Const EFX_TEXT_HMASK = &HF0

Global Const EFX_TEXT_TOP = &H0
Global Const EFX_TEXT_VCENTER = &H100
Global Const EFX_TEXT_BOTTOM = &H200
Global Const EFX_TEXT_VMASK = &HF00

Global Const EFX_TEXT_WORDWRAP = &H1000

'   Shapes
'Square
Global Const EFX_SHAPE_SQUARE_CLASS = 1000
Global Const EFX_SHAPE_SQUARE = (EFX_SHAPE_SQUARE_CLASS + 0)
Global Const EFX_SHAPE_SQUARE_ROUNDED = (EFX_SHAPE_SQUARE_CLASS + 1)
Global Const EFX_SHAPE_SQUARE_MAX = (EFX_SHAPE_SQUARE_CLASS + 1)

'Rectangle
Global Const EFX_SHAPE_RECTANGLE_CLASS = 2000
Global Const EFX_SHAPE_RECTANGLE = (EFX_SHAPE_RECTANGLE_CLASS + 0)
Global Const EFX_SHAPE_RECTANGLE_ROUNDED = (EFX_SHAPE_RECTANGLE_CLASS + 1)
Global Const EFX_SHAPE_RECTANGLE_MAX = (EFX_SHAPE_RECTANGLE_CLASS + 1)

'Parallelogram
Global Const EFX_SHAPE_PARALLELOGRAM_CLASS = 3000
Global Const EFX_SHAPE_PARALLELOGRAM_L = (EFX_SHAPE_PARALLELOGRAM_CLASS + 0)
Global Const EFX_SHAPE_PARALLELOGRAM_R = (EFX_SHAPE_PARALLELOGRAM_CLASS + 1)
Global Const EFX_SHAPE_PARALLELOGRAM_T = (EFX_SHAPE_PARALLELOGRAM_CLASS + 2)
Global Const EFX_SHAPE_PARALLELOGRAM_B = (EFX_SHAPE_PARALLELOGRAM_CLASS + 3)
Global Const EFX_SHAPE_PARALLELOGRAM_MAX = (EFX_SHAPE_PARALLELOGRAM_CLASS + 3)

'Trapezoid
Global Const EFX_SHAPE_TRAPEZOID_CLASS = 4000
Global Const EFX_SHAPE_TRAPEZOID_L = (EFX_SHAPE_TRAPEZOID_CLASS + 0)
Global Const EFX_SHAPE_TRAPEZOID_R = (EFX_SHAPE_TRAPEZOID_CLASS + 1)
Global Const EFX_SHAPE_TRAPEZOID_T = (EFX_SHAPE_TRAPEZOID_CLASS + 2)
Global Const EFX_SHAPE_TRAPEZOID_B = (EFX_SHAPE_TRAPEZOID_CLASS + 3)
Global Const EFX_SHAPE_TRAPEZOID_MAX = (EFX_SHAPE_TRAPEZOID_CLASS + 3)

'Triangle
Global Const EFX_SHAPE_TRIANGLE_CLASS = 5000
Global Const EFX_SHAPE_TRIANGLE_EQUILATERAL_L = (EFX_SHAPE_TRIANGLE_CLASS + 0)
Global Const EFX_SHAPE_TRIANGLE_EQUILATERAL_R = (EFX_SHAPE_TRIANGLE_CLASS + 1)
Global Const EFX_SHAPE_TRIANGLE_EQUILATERAL_T = (EFX_SHAPE_TRIANGLE_CLASS + 2)
Global Const EFX_SHAPE_TRIANGLE_EQUILATERAL_B = (EFX_SHAPE_TRIANGLE_CLASS + 3)
Global Const EFX_SHAPE_TRIANGLE_ISOSCELES_L = (EFX_SHAPE_TRIANGLE_CLASS + 4)
Global Const EFX_SHAPE_TRIANGLE_ISOSCELES_R = (EFX_SHAPE_TRIANGLE_CLASS + 5)
Global Const EFX_SHAPE_TRIANGLE_ISOSCELES_T = (EFX_SHAPE_TRIANGLE_CLASS + 6)
Global Const EFX_SHAPE_TRIANGLE_ISOSCELES_B = (EFX_SHAPE_TRIANGLE_CLASS + 7)
Global Const EFX_SHAPE_TRIANGLE_RIGHT_LT = (EFX_SHAPE_TRIANGLE_CLASS + 8)
Global Const EFX_SHAPE_TRIANGLE_RIGHT_LB = (EFX_SHAPE_TRIANGLE_CLASS + 9)
Global Const EFX_SHAPE_TRIANGLE_RIGHT_RT = (EFX_SHAPE_TRIANGLE_CLASS + 10)
Global Const EFX_SHAPE_TRIANGLE_RIGHT_RB = (EFX_SHAPE_TRIANGLE_CLASS + 11)
Global Const EFX_SHAPE_TRIANGLE_MAX = (EFX_SHAPE_TRIANGLE_CLASS + 11)

'Other polygons
Global Const EFX_SHAPE_OTHER_CLASS = 6000
Global Const EFX_SHAPE_OCTAGON = (EFX_SHAPE_OTHER_CLASS + 0)
Global Const EFX_SHAPE_DIAMOND = (EFX_SHAPE_OTHER_CLASS + 1)
Global Const EFX_SHAPE_PENTAGON = (EFX_SHAPE_OTHER_CLASS + 2)
Global Const EFX_SHAPE_HEXAGON = (EFX_SHAPE_OTHER_CLASS + 3)
Global Const EFX_SHAPE_LINE = (EFX_SHAPE_OTHER_CLASS + 4)
Global Const EFX_SHAPE_REGION = (EFX_SHAPE_OTHER_CLASS + 5)
Global Const EFX_SHAPE_OTHER_MAX = (EFX_SHAPE_OTHER_CLASS + 5)

'Circle
Global Const EFX_SHAPE_CIRCLE_CLASS = 7000
Global Const EFX_SHAPE_CIRCLE = (EFX_SHAPE_CIRCLE_CLASS + 0)
Global Const EFX_SHAPE_CIRCLE_90_LT = (EFX_SHAPE_CIRCLE_CLASS + 1)
Global Const EFX_SHAPE_CIRCLE_90_LB = (EFX_SHAPE_CIRCLE_CLASS + 2)
Global Const EFX_SHAPE_CIRCLE_90_RT = (EFX_SHAPE_CIRCLE_CLASS + 3)
Global Const EFX_SHAPE_CIRCLE_90_RB = (EFX_SHAPE_CIRCLE_CLASS + 4)
Global Const EFX_SHAPE_CIRCLE_180_L = (EFX_SHAPE_CIRCLE_CLASS + 5)
Global Const EFX_SHAPE_CIRCLE_180_R = (EFX_SHAPE_CIRCLE_CLASS + 6)
Global Const EFX_SHAPE_CIRCLE_180_T = (EFX_SHAPE_CIRCLE_CLASS + 7)
Global Const EFX_SHAPE_CIRCLE_180_B = (EFX_SHAPE_CIRCLE_CLASS + 8)
Global Const EFX_SHAPE_CIRCLE_270_LT = (EFX_SHAPE_CIRCLE_CLASS + 9)
Global Const EFX_SHAPE_CIRCLE_270_LB = (EFX_SHAPE_CIRCLE_CLASS + 10)
Global Const EFX_SHAPE_CIRCLE_270_RT = (EFX_SHAPE_CIRCLE_CLASS + 11)
Global Const EFX_SHAPE_CIRCLE_270_RB = (EFX_SHAPE_CIRCLE_CLASS + 12)
Global Const EFX_SHAPE_CIRCLE_MAX = (EFX_SHAPE_CIRCLE_CLASS + 12)

'Ellipse
Global Const EFX_SHAPE_ELLIPSE_CLASS = 8000
Global Const EFX_SHAPE_ELLIPSE = (EFX_SHAPE_ELLIPSE_CLASS + 0)
Global Const EFX_SHAPE_ELLIPSE_90_LT = (EFX_SHAPE_ELLIPSE_CLASS + 1)
Global Const EFX_SHAPE_ELLIPSE_90_LB = (EFX_SHAPE_ELLIPSE_CLASS + 2)
Global Const EFX_SHAPE_ELLIPSE_90_RT = (EFX_SHAPE_ELLIPSE_CLASS + 3)
Global Const EFX_SHAPE_ELLIPSE_90_RB = (EFX_SHAPE_ELLIPSE_CLASS + 4)
Global Const EFX_SHAPE_ELLIPSE_180_L = (EFX_SHAPE_ELLIPSE_CLASS + 5)
Global Const EFX_SHAPE_ELLIPSE_180_R = (EFX_SHAPE_ELLIPSE_CLASS + 6)
Global Const EFX_SHAPE_ELLIPSE_180_T = (EFX_SHAPE_ELLIPSE_CLASS + 7)
Global Const EFX_SHAPE_ELLIPSE_180_B = (EFX_SHAPE_ELLIPSE_CLASS + 8)
Global Const EFX_SHAPE_ELLIPSE_270_LT = (EFX_SHAPE_ELLIPSE_CLASS + 9)
Global Const EFX_SHAPE_ELLIPSE_270_LB = (EFX_SHAPE_ELLIPSE_CLASS + 10)
Global Const EFX_SHAPE_ELLIPSE_270_RT = (EFX_SHAPE_ELLIPSE_CLASS + 11)
Global Const EFX_SHAPE_ELLIPSE_270_RB = (EFX_SHAPE_ELLIPSE_CLASS + 12)
Global Const EFX_SHAPE_ELLIPSE_MAX = (EFX_SHAPE_ELLIPSE_CLASS + 12)

'Star
Global Const EFX_SHAPE_STAR_CLASS = 9000
Global Const EFX_SHAPE_STAR4 = (EFX_SHAPE_STAR_CLASS + 0)
Global Const EFX_SHAPE_STAR5 = (EFX_SHAPE_STAR_CLASS + 1)
Global Const EFX_SHAPE_STAR8 = (EFX_SHAPE_STAR_CLASS + 2)
Global Const EFX_SHAPE_STAR16 = (EFX_SHAPE_STAR_CLASS + 3)
Global Const EFX_SHAPE_STAR24 = (EFX_SHAPE_STAR_CLASS + 4)
Global Const EFX_SHAPE_STAR32 = (EFX_SHAPE_STAR_CLASS + 5)
Global Const EFX_SHAPE_STAR_MAX = (EFX_SHAPE_STAR_CLASS + 5)

'Cross
Global Const EFX_SHAPE_CROSS_CLASS = 10000
Global Const EFX_SHAPE_CROSS_SMALL = (EFX_SHAPE_CROSS_CLASS + 0)
Global Const EFX_SHAPE_CROSS_MEDIUM = (EFX_SHAPE_CROSS_CLASS + 1)
Global Const EFX_SHAPE_CROSS_LARGE = (EFX_SHAPE_CROSS_CLASS + 2)
Global Const EFX_SHAPE_CROSS_MAX = (EFX_SHAPE_CROSS_CLASS + 2)

'Arrow
Global Const EFX_SHAPE_ARROW_CLASS = 11000
Global Const EFX_SHAPE_ARROW_L = (EFX_SHAPE_ARROW_CLASS + 0)
Global Const EFX_SHAPE_ARROW_R = (EFX_SHAPE_ARROW_CLASS + 1)
Global Const EFX_SHAPE_ARROW_T = (EFX_SHAPE_ARROW_CLASS + 2)
Global Const EFX_SHAPE_ARROW_B = (EFX_SHAPE_ARROW_CLASS + 3)
Global Const EFX_SHAPE_ARROW2_L_AND_R = (EFX_SHAPE_ARROW_CLASS + 4)
Global Const EFX_SHAPE_ARROW2_T_AND_B = (EFX_SHAPE_ARROW_CLASS + 5)
Global Const EFX_SHAPE_ARROW2_L_AND_T = (EFX_SHAPE_ARROW_CLASS + 6)
Global Const EFX_SHAPE_ARROW2_L_AND_B = (EFX_SHAPE_ARROW_CLASS + 7)
Global Const EFX_SHAPE_ARROW2_R_AND_T = (EFX_SHAPE_ARROW_CLASS + 8)
Global Const EFX_SHAPE_ARROW2_R_AND_B = (EFX_SHAPE_ARROW_CLASS + 9)
Global Const EFX_SHAPE_ARROW3_L_AND_T_AND_R = (EFX_SHAPE_ARROW_CLASS + 10)
Global Const EFX_SHAPE_ARROW3_T_AND_R_AND_B = (EFX_SHAPE_ARROW_CLASS + 11)
Global Const EFX_SHAPE_ARROW3_L_AND_B_AND_R = (EFX_SHAPE_ARROW_CLASS + 12)
Global Const EFX_SHAPE_ARROW3_L_AND_T_AND_B = (EFX_SHAPE_ARROW_CLASS + 13)
Global Const EFX_SHAPE_ARROW4_L_AND_T_AND_R_AND_B = (EFX_SHAPE_ARROW_CLASS + 14)
Global Const EFX_SHAPE_ARROW_MAX = (EFX_SHAPE_ARROW_CLASS + 14)

Global Const EFX_BORDERSTYLE_TRANSPARENT = 0
Global Const EFX_BORDERSTYLE_SOLID = 1
Global Const EFX_BORDERSTYLE_DASH = 2
Global Const EFX_BORDERSTYLE_DOT = 3
Global Const EFX_BORDERSTYLE_DASHDOT = 4
Global Const EFX_BORDERSTYLE_DASHDOTDOT = 5

Global Const EFX_FILLSTYLE_SOLID = 0
Global Const EFX_FILLSTYLE_TRANSPARENT = 1
Global Const EFX_FILLSTYLE_HORIZONTAL = 2
Global Const EFX_FILLSTYLE_VERTICAL = 3
Global Const EFX_FILLSTYLE_FDIAGONAL = 4
Global Const EFX_FILLSTYLE_BDIAGONAL = 5
Global Const EFX_FILLSTYLE_CROSS = 6
Global Const EFX_FILLSTYLE_DIAGCROSS = 7

Global Const EFX_BACKSTYLE_TRANSPARENT = 0
Global Const EFX_BACKSTYLE_OPAQUE = 1
Global Const EFX_BACKSTYLE_TRANSLUCENT = 2
Global Const EFX_BACKSTYLE_TILEDIMAGE = 3
Global Const EFX_BACKSTYLE_TRANSLUCENTTILEDIMAGE = 4

Global Const EFX_INNERSTYLE_NONE = 0
Global Const EFX_INNERSTYLE_INSET = 1
Global Const EFX_INNERSTYLE_RAISED = 2

Global Const EFX_OUTERSTYLE_NONE = 0
Global Const EFX_OUTERSTYLE_INSET = 1
Global Const EFX_OUTERSTYLE_RAISED = 2

'Flags for LTDLG DLL
' flags for the Help Callbacks for L_Dlg* function
Global Const DLG_HELP_FILEOPEN = 1
Global Const DLG_HELP_FILESAVE = 2
Global Const DLG_HELP_COLORRES = 3
Global Const DLG_HELP_GETANGLE = 4
Global Const DLG_HELP_GETSIZE = 5
Global Const DLG_HELP_GETFILTER = 6
Global Const DLG_HELP_GETCHANGE = 7
Global Const DLG_HELP_GETRANGE = 8
Global Const DLG_HELP_GETGAMMA = 9
Global Const DLG_HELP_GETNOISE = 10
Global Const DLG_HELP_GETEMBOSS = 11
Global Const DLG_HELP_WINDOWLEVEL = 12
Global Const DLG_HELP_GETEFFECT = 13
Global Const DLG_HELP_GETSHAPE = 14
Global Const DLG_HELP_GETTEXT = 15
Global Const DLG_HELP_GETGRADIENT = 16
Global Const DLG_HELP_GETTRANSITION = 17
Global Const DLG_HELP_GETDIR = 18
Global Const DLG_HELP_GETRES = 19
Global Const DLG_HELP_CONTOUR = 20
Global Const DLG_HELP_HALFTONE = 21
Global Const DLG_HELP_COLOR = 22

' flags for L_DlgFileOpen()

Global Const DLG_FO_AUTOPROCESS = &H1              ' Dlg should autoprocess image and fill the pBitmap
Global Const DLG_FO_PROGRESSIVE = &H2              ' FileOpen Dlg should have Prog. File options
Global Const DLG_FO_MULTIPAGE = &H4                ' FileOpen Dlg should have Multipage options
Global Const DLG_FO_LOADROTATED = &H8              ' FileOpen Dlg should have Load Rotated option
Global Const DLG_FO_LOADCOMPRESSED = &H10          ' FileOpen Dlg should have Load 1-bit compressed option
Global Const DLG_FO_FILEINFO = &H20                ' FileOpen Dlg should have FileInfo button
Global Const DLG_FO_SHOWPREVIEW = &H40             ' FileOpen Dlg should have ThumbNail and should create the preview if none is stored in the file
Global Const DLG_FO_SHOWSTAMP = &H80               ' FileOpen Dlg should have ThumbNail and should only load the preview stamp if one is stored in the file
Global Const DLG_FO_DELPAGE = &H200                ' FileOpen Dlg should have Delete Page button
Global Const DLG_FO_RESDLG = &H400                 ' If AutoProcess, and format supports resolution, show GetRes dlg
Global Const DLG_FO_NOFILEMUSTEXIST = &H800        ' Do not verify that the path exists
Global Const DLG_FO_NOPATHMUSTEXIST = &H1000       ' Do not verify that the file exists
Global Const DLG_GETRES_95CONTEXTHELP = &H2000     ' GetRes Dlg should contain context sensitive help icon
Global Const DLG_FO_FILEINFO_TOTALPAGES = &H4000   ' when filling FILEINFO, get TOTALPAGES
Global Const DLG_FO_FILEINFO_PDFDLG = &H8000       ' If AutoProcess, and format is PDF , show PDF options dlg
Global Const DLG_FO_ENABLESIZING = &H10000         ' Enable sizing for the dialog


' flags for L_DlgFileSave()
Global Const DLG_FS_AUTOPROCESS = &H1      ' Dlg should autoprocess image and fill the pBitmap
Global Const DLG_FS_PROGRESSIVE = &H2      ' FileSave Dlg should have Prog. File options
Global Const DLG_FS_MULTIPAGE = &H4        ' FileSave Dlg should have Multipage options
Global Const DLG_FS_STAMP = &H8            ' FileSave Dlg should have save with stamp options
Global Const DLG_FS_QFACTOR = &H10         ' FileSave Dlg should have QFactor option
Global Const DLG_FS_ENABLESIZING = &H100   ' Enable sizing for the dialog

' file save format option constants for L_DlgFileSave
' top-level formats
Global Const FS_LEAD24 = 0
Global Const FS_LEAD8 = 1
Global Const FS_LEAD1BIT = 2
Global Const FS_JFIF24 = 3
Global Const FS_JFIF16 = 4
Global Const FS_JFIF12 = 5
Global Const FS_JFIF8 = 6
Global Const FS_CALS = 7
Global Const FS_PNG1 = 8
Global Const FS_PNG4 = 9
Global Const FS_PNG8 = 10
Global Const FS_PNG24 = 11
Global Const FS_PNG32 = 12
Global Const FS_DICOM8 = 13
Global Const FS_DICOM16 = 14
Global Const FS_DICOM24 = 15
Global Const FS_FAX = 16
Global Const FS_EPS = 17
Global Const FS_EXIF = 18
Global Const FS_FPX24 = 19
Global Const FS_FPX8 = 20
Global Const FS_IMG = 21
Global Const FS_GIF1 = 22
Global Const FS_GIF2 = 23
Global Const FS_GIF3 = 24
Global Const FS_GIF4 = 25
Global Const FS_GIF5 = 26
Global Const FS_GIF6 = 27
Global Const FS_GIF7 = 28
Global Const FS_GIF8 = 29
Global Const FS_IOCA = 30
Global Const FS_MODCA = 31
Global Const FS_PCT1 = 32
Global Const FS_PCT4 = 33
Global Const FS_PCT8 = 34
Global Const FS_PCT24 = 35
Global Const FS_MAC = 36
Global Const FS_AWD = 37
Global Const FS_MSP = 38
Global Const FS_OS2BMP1 = 39
Global Const FS_OS2BMP4 = 40
Global Const FS_OS2BMP8 = 41
Global Const FS_OS2BMP24 = 42
Global Const FS_PCX1 = 43
Global Const FS_PCX4 = 44
Global Const FS_PCX8 = 45
Global Const FS_PCX24 = 46
Global Const FS_PSD1 = 47
Global Const FS_PSD8 = 48
Global Const FS_PSD24 = 49
Global Const FS_RAS1 = 50
Global Const FS_RAS4 = 51
Global Const FS_RAS8 = 52
Global Const FS_RAS24 = 53
Global Const FS_RAS32 = 54
Global Const FS_TGA8 = 55
Global Const FS_TGA16 = 56
Global Const FS_TGA24 = 57
Global Const FS_TGA32 = 58
Global Const FS_TIFF1 = 59
Global Const FS_TIFF2 = 60
Global Const FS_TIFF3 = 61
Global Const FS_TIFF4 = 62
Global Const FS_TIFF5 = 63
Global Const FS_TIFF6 = 64
Global Const FS_TIFF7 = 65
Global Const FS_TIFF8 = 66
Global Const FS_TIFF12 = 67
Global Const FS_TIFF16 = 68
Global Const FS_TIFF24 = 69
Global Const FS_TIFF32 = 70
Global Const FS_BMP1 = 71
Global Const FS_BMP4 = 72
Global Const FS_BMP8 = 73
Global Const FS_BMP16 = 74
Global Const FS_BMP24 = 75
Global Const FS_BMP32 = 76
Global Const FS_WFX = 77
Global Const FS_WMF8 = 78
Global Const FS_WMF24 = 79
Global Const FS_EMF8 = 80
Global Const FS_EMF24 = 81
Global Const FS_WPG1 = 82
Global Const FS_WPG4 = 83
Global Const FS_WPG8 = 84
Global Const FS_ICO1 = 85
Global Const FS_ICO4 = 86
Global Const FS_ICO8 = 87
Global Const FS_ICO24 = 88
Global Const FS_CUR1 = 89
Global Const FS_CUR4 = 90
Global Const FS_CUR8 = 91
Global Const FS_CUR24 = 92
Global Const FS_JBIG1 = 93
Global Const FS_JBIG2 = 94
Global Const FS_JBIG3 = 95
Global Const FS_JBIG4 = 96
Global Const FS_JBIG5 = 97
Global Const FS_JBIG6 = 98
Global Const FS_JBIG7 = 99
Global Const FS_JBIG8 = 100
Global Const FS_CUT = 101
Global Const FS_PPM = 102
Global Const FS_PGM = 103
Global Const FS_PBM = 104
Global Const FS_IFF1 = 105
Global Const FS_IFF2 = 106
Global Const FS_IFF3 = 107
Global Const FS_IFF4 = 108
Global Const FS_IFF5 = 109
Global Const FS_IFF6 = 110
Global Const FS_IFF7 = 111
Global Const FS_IFF8 = 112
Global Const FS_IFF24 = 113
Global Const FS_XBM = 114
Global Const FS_XPM8 = 115
Global Const FS_XPM16 = 116
Global Const FS_XPM24 = 117
Global Const FS_XPM32 = 118
Global Const FS_ITG = 119
Global Const FS_TIFF48 = 120
Global Const FS_TIFF64 = 121
Global Const FS_FLC8 = 122
Global Const FS_ANI1 = 123
Global Const FS_ANI4 = 124
Global Const FS_ANI8 = 125
Global Const FS_ANI24 = 126
Global Const FS_XWD10_1 = 127
Global Const FS_XWD10_4 = 128
Global Const FS_XWD10_8 = 129
Global Const FS_XWD11_1 = 130
Global Const FS_XWD11_4 = 131
Global Const FS_XWD11_8 = 132
Global Const FS_XWD11_16 = 133
Global Const FS_XWD11_24 = 134
Global Const FS_XWD11_32 = 135
Global Const FS_SGI8 = 136
Global Const FS_SGI24 = 136
Global Const FS_SGI32 = 138
Global Const FS_CLP1 = 139
Global Const FS_CLP4 = 140
Global Const FS_CLP8 = 141
Global Const FS_CLP24 = 142
Global Const FS_RAW = 143
Global Const FS_PDF1 = 144
Global Const FS_PDF2 = 145
Global Const FS_PDF4 = 146
Global Const FS_PDF8 = 147
Global Const FS_PDF24 = 148
Global Const FS_J2K8 = 149
Global Const FS_J2K24 = 150
Global Const FS_CMW8 = 151
Global Const FS_CMW24 = 152
Global Const FS_J2K12 = 153
Global Const FS_J2K16 = 154
Global Const FS_CMW12 = 155
Global Const FS_CMW16 = 156
Global Const FS_WBMP = 157
Global Const FS_SCT24 = 158
Global Const FS_SCT32 = 159
Global Const FS_MAX = 160


' FileSave sub-format values
' LEAD CMP file subtypes (8,24-bit)
Global Const DLG_FS_SUB_CMP_NONPROGRESSIVE = &H1
Global Const DLG_FS_SUB_CMP_PROGRESSIVE = &H2
' JPEG file subtypes (24-bit)
Global Const DLG_FS_SUB_JPEG24_YUV_444 = &H1
Global Const DLG_FS_SUB_JPEG24_YUV_422 = &H2
Global Const DLG_FS_SUB_JPEG24_YUV_411 = &H4
Global Const DLG_FS_SUB_JPEG24_PROG_444 = &H8
Global Const DLG_FS_SUB_JPEG24_PROG_422 = &H10
Global Const DLG_FS_SUB_JPEG24_PROG_411 = &H20
Global Const DLG_FS_SUB_JPEG24_LOSSLESS = &H40
' JPEG file subtypes (12-bit)
Global Const DLG_FS_SUB_JPEG12_YUV_400 = &H1
Global Const DLG_FS_SUB_JPEG12_LOSSLESS = &H2
' JPEG file subtypes (8-bit)
Global Const DLG_FS_SUB_JPEG8_YUV_400 = &H1
Global Const DLG_FS_SUB_JPEG8_PROG_400 = &H2
Global Const DLG_FS_SUB_JPEG8_LOSSLESS = &H4
' JPEG 2000 file subtypes (8,24-bit)
Global Const DLG_FS_SUB_J2K_STREAM = &H1
Global Const DLG_FS_SUB_J2K_JP2 = &H2
' DICOM file subtypes (8-bit)
Global Const DLG_FS_SUB_DICOM8_GRAY = &H1
Global Const DLG_FS_SUB_DICOM8_COLOR = &H2
' DICOM file subtypes (Other-bit)
Global Const DLG_FS_SUB_DICOM_RLE_GRAY = &H1
Global Const DLG_FS_SUB_DICOM_RLE_COLOR = &H2
Global Const DLG_FS_SUB_DICOM_JPEG_GRAY = &H4
Global Const DLG_FS_SUB_DICOM_LOSSLESSJPEG_GRAY = &H8
Global Const DLG_FS_SUB_DICOM_JPEG_COLOR = &H10
Global Const DLG_FS_SUB_DICOM_LOSSLESSJPEG_COLOR = &H20
' RAW FAX, IOCA, & MODCA subtypes
Global Const DLG_FS_SUB_FAX_G3_1D = &H1
Global Const DLG_FS_SUB_FAX_G3_2D = &H2
Global Const DLG_FS_SUB_FAX_G4 = &H4
' EXIF file subtypes
Global Const DLG_FS_SUB_EXIF_UNCOMPRESSEDRGB = &H1
Global Const DLG_FS_SUB_EXIF_UNCOMPRESSEDYCC = &H2
Global Const DLG_FS_SUB_EXIF_JPEG_411 = &H4
Global Const DLG_FS_SUB_EXIF_JPEG_422 = &H8
' FPX file subtypes
Global Const DLG_FS_SUB_FPX_UNCOMPRESSED = &H1
Global Const DLG_FS_SUB_FPX_SINGLECOLOR = &H2
Global Const DLG_FS_SUB_FPX_DEFQFACTOR = &H4
Global Const DLG_FS_SUB_FPX_SPECQFACTOR = &H8
' GIF file subtypes
Global Const DLG_FS_SUB_GIF_INTERLACED89A = &H1
Global Const DLG_FS_SUB_GIF_NONINTERLACED89A = &H2
' OS/2 BMP file subtypes
Global Const DLG_FS_SUB_OS2_VER1 = &H1
Global Const DLG_FS_SUB_OS2_VER2 = &H2
' TIFF file subtypes (1-bit)
Global Const DLG_FS_SUB_TIFF1_CCITT = &H1
Global Const DLG_FS_SUB_TIFF1_CCITT_G3_1D = &H2
Global Const DLG_FS_SUB_TIFF1_CCITT_G3_2D = &H4
Global Const DLG_FS_SUB_TIFF1_CCITT_G4 = &H8
Global Const DLG_FS_SUB_TIFF1_UNCOMPRESSEDRGB = &H10
Global Const DLG_FS_SUB_TIFF1_RLERGB = &H20
Global Const DLG_FS_SUB_TIFF1_LZWRGB = &H40
' TIFF file subtypes (2,3,4,5,6,7-bit)
Global Const DLG_FS_SUB_TIFFOTHER_UNCOMPRESSED = &H1
Global Const DLG_FS_SUB_TIFFOTHER_RLE = &H2
Global Const DLG_FS_SUB_TIFFOTHER_LZW = &H4
' TIFF file subtypes (8-bit)
Global Const DLG_FS_SUB_TIFF8_UNCOMPRESSEDRGB = &H1
Global Const DLG_FS_SUB_TIFF8_RLERGB = &H2
Global Const DLG_FS_SUB_TIFF8_JPEG_GRAY_YCC = &H4
Global Const DLG_FS_SUB_TIFF8_LOSSLESSJPEG = &H8
Global Const DLG_FS_SUB_TIFF8_LZWRGB = &H10
Global Const DLG_FS_SUB_TIFF8_JBIG = &H20
Global Const DLG_FS_SUB_TIFF8_CMP = &H40
Global Const DLG_FS_SUB_TIFF8_J2K = &H80
Global Const DLG_FS_SUB_TIFF8_CMW = &H100
' TIFF file subtypes (12-bit)
Global Const DLG_FS_SUB_TIFF12_UNCOMPRESSED = &H1
Global Const DLG_FS_SUB_TIFF12_RLE = &H2
Global Const DLG_FS_SUB_TIFF12_LOSSLESSJPEG = &H4
Global Const DLG_FS_SUB_TIFF12_JPEG_GRAY_YCC = &H8
Global Const DLG_FS_SUB_TIFF12_LZW = &H10
Global Const DLG_FS_SUB_TIFF12_J2K = &H20
Global Const DLG_FS_SUB_TIFF12_CMW = &H40
' TIFF file subtypes (16-bit)
Global Const DLG_FS_SUB_TIFF16_UNCOMPRESSED = &H1
Global Const DLG_FS_SUB_TIFF16_RLE = &H2
Global Const DLG_FS_SUB_TIFF16_LOSSLESSJPEG = &H4
Global Const DLG_FS_SUB_TIFF16_LZW = &H8
Global Const DLG_FS_SUB_TIFF16_J2K = &H10
Global Const DLG_FS_SUB_TIFF16_CMW = &H20
' TIFF file subtypes (24-bit)
Global Const DLG_FS_SUB_TIFF24_UNCOMPRESSEDRGB = &H1
Global Const DLG_FS_SUB_TIFF24_UNCOMPRESSEDCMYK = &H2
Global Const DLG_FS_SUB_TIFF24_UNCOMPRESSEDYCC = &H4
Global Const DLG_FS_SUB_TIFF24_RLERGB = &H8
Global Const DLG_FS_SUB_TIFF24_RLECMYK = &H10
Global Const DLG_FS_SUB_TIFF24_RLEYCC = &H20
Global Const DLG_FS_SUB_TIFF24_JPEG_YCC_444 = &H40
Global Const DLG_FS_SUB_TIFF24_JPEG_YCC_422 = &H80
Global Const DLG_FS_SUB_TIFF24_JPEG_YCC_411 = &H100
Global Const DLG_FS_SUB_TIFF24_LOSSLESSJPEG = &H200
Global Const DLG_FS_SUB_TIFF24_LZWRGB = &H400
Global Const DLG_FS_SUB_TIFF24_LZWCMYK = &H800
Global Const DLG_FS_SUB_TIFF24_LZWYCC = &H1000
Global Const DLG_FS_SUB_TIFF24_CMP_NONPROGRESSIVE = &H2000
Global Const DLG_FS_SUB_TIFF24_CMP_PROGRESSIVE = &H4000
Global Const DLG_FS_SUB_TIFF24_J2K = &H8000
Global Const DLG_FS_SUB_TIFF24_CMW = &H10000
' TIFF file subtypes (32-bit)
Global Const DLG_FS_SUB_TIFF32_UNCOMPRESSEDRGB = &H1
Global Const DLG_FS_SUB_TIFF32_UNCOMPRESSEDCMYK = &H2
Global Const DLG_FS_SUB_TIFF32_RLERGB = &H4
Global Const DLG_FS_SUB_TIFF32_RLECMYK = &H8
Global Const DLG_FS_SUB_TIFF32_LZWRGB = &H10
Global Const DLG_FS_SUB_TIFF32_LZWCMYK = &H20
' BMP file subtypes (4 and 8-bit only)
Global Const DLG_FS_SUB_BMP_UNCOMPRESSED = &H1
Global Const DLG_FS_SUB_BMP_RLECOMPRESSED = &H2
' WFX file subtypes
Global Const DLG_FS_SUB_WFX_CCITT_G3_1D = &H1
Global Const DLG_FS_SUB_WFX_CCITT_G4 = &H2
' PPM file subtypes
Global Const DLG_FS_SUB_PPM_ASCII = &H1
Global Const DLG_FS_SUB_PPM_BINARY = &H2
' PGM file subtypes
Global Const DLG_FS_SUB_PGM_ASCII = &H1
Global Const DLG_FS_SUB_PGM_BINARY = &H2
' PBM file subtypes
Global Const DLG_FS_SUB_PBM_ASCII = &H1
Global Const DLG_FS_SUB_PBM_BINARY = &H2
' IFF file subtypes
' All BitsPerPixel have subtypes
Global Const DLG_FS_SUB_IFF_ILBM_RLE = &H1
Global Const DLG_FS_SUB_IFF_CAT_RLE = &H2
' SGI file subtypes
' All BitsPerPixel have subtypes
Global Const DLG_FS_SUB_SGI_UNCOMPRESSED = &H1
Global Const DLG_FS_SUB_SGI_RLECOMPRESSED = &H2

' flags for L_DlgGetDir()
Global Const DLG_GD_95CONTEXTHELP = &H2         ' Dlg should contain context sensitive help icon

' flags for Image processing dialog functions

Global Const DLG_IMG_AUTOPROCESS = &H80000000   ' Dlg should autoprocess image and fill the pBitmap
Global Const DLG_IMG_SHOWPREVIEW = &H40000000   ' ImageProcess Dlg should preview of image
Global Const DLG_IMG_HIDEBACKCOLOR = &H20000000 ' GetAngle Dlg should hide Background Color button
Global Const DLG_IMG_95CONTEXTHELP = &H10000000 ' Dlg should contain context sensitive help icon
Global Const DLG_IMG_SHOWRESIZEOPT = &H8000000  ' GetAngle Dlg should show resize options

Global Const DLG_IMG_TOOL = &H2000000           ' GetAngle Dlg should show the toolbar
Global Const DLG_IMG_PERCENTAGE = &H1000000     ' Image resize Dlg should Percentage value combo
Global Const DLG_IMG_IDENTICALVAL = &H100000    ' Image resize Dlg should Identical value check box
Global Const DLG_IMG_MAINTAINASPECT = &H200000  ' Dlg should Maintain aspect check box
Global Const DLG_IMG_RESOLUTIONGRP = &H400000   ' Image resize Dlg should Resolution group information

Global Const DLG_IMG_ROTATE = &H1               ' rotate dialog
Global Const DLG_IMG_SHEAR = &H2                ' shear dialog

Global Const DLG_IMG_GRADIENT = &H1             ' gradient dialog
Global Const DLG_IMG_LAPLACIAN = &H2            ' laplacian dialog
Global Const DLG_IMG_SOBEL = &H4                ' sobel dialog
Global Const DLG_IMG_PREWITT = &H8              ' prewitt dialog
Global Const DLG_IMG_SHIFTDIFF = &H10           ' shiftdiff dialog
Global Const DLG_IMG_LINESEG = &H20             ' lineseg dialog
Global Const DLG_IMG_EROSION = &H40             ' erosion dialog
Global Const DLG_IMG_DILATION = &H80            ' dilation dialog

Global Const DLG_IMG_SHARPEN = &H1              ' sharpen dialog
Global Const DLG_IMG_BRIGHTNESS = &H2           ' brightness dialog
Global Const DLG_IMG_CONTRAST = &H4             ' contrast dialog
Global Const DLG_IMG_SATURATION = &H8           ' saturation dialog
Global Const DLG_IMG_HISTOCONTRAST = &H10       ' histo contrast dialog
Global Const DLG_IMG_HUE = &H20                 ' hue dialog
Global Const DLG_IMG_POSTERIZE = &H40           ' posterize dialog
Global Const DLG_IMG_MOSAIC = &H80              ' mosaic dialog
Global Const DLG_IMG_AVERAGE = &H100            ' average dialog
Global Const DLG_IMG_MEDIAN = &H200             ' median dialog
Global Const DLG_IMG_OILIFY = &H400             ' oilify dialog
Global Const DLG_IMG_MIN = &H800                ' min filter dialog
Global Const DLG_IMG_MAX = &H1000               ' max filter dialog
Global Const DLG_IMG_SOLARIZE = &H2000          ' solarize dialog

Global Const DLG_IMG_ADDNOISE = &H1C            ' add noise dialog
Global Const DLG_IMG_GAMMACORRECT = &H1D        ' gamma correct dialog
Global Const DLG_IMG_EMBOSS = &H1E              ' emboss filter dialog
Global Const DLG_IMG_INTENSITYDETECT = &H1F     ' intensity detect dialog

' flags for L_DlgColorRes()
Global Const DLG_CR_SHOWPREVIEW = &H1     ' shows preview of image
Global Const DLG_CR_AUTOPROCESS = &H2     ' process the image on OK
Global Const DLG_CR_95CONTEXTHELP = &H4   ' Dlg should contain context sensitive help icon

Global Const DLG_CR_OPENPALFILEBTN = &H8  ' Dlg should contain Open palett file button
Global Const DLG_CR_TOOL = &H10           ' Dlg should contain toolbar in the dialog
Global Const DLG_CR_ORDER = &H20          ' color order is an option

Global Const DLG_CR_1BIT = &H1      ' 1-bit is an option
Global Const DLG_CR_2BIT = &H2      ' 2-bit is an option
Global Const DLG_CR_3BIT = &H4      ' 3-bit is an option
Global Const DLG_CR_4BIT = &H8      ' 4-bit is an option
Global Const DLG_CR_5BIT = &H10     ' 5-bit is an option
Global Const DLG_CR_6BIT = &H20     ' 6-bit is an option
Global Const DLG_CR_7BIT = &H40     ' 7-bit is an option
Global Const DLG_CR_8BIT = &H80     ' 8-bit is an option
Global Const DLG_CR_12BIT = &H100   ' 12-bit is an option
Global Const DLG_CR_16BIT = &H200   '  16-bit is an option
Global Const DLG_CR_24BIT = &H400   ' 24-bit is an option
Global Const DLG_CR_32BIT = &H800   ' 32-bit is an option
Global Const DLG_CR_48BIT = &H1000  ' 48-bit is an option
Global Const DLG_CR_64BIT = &H2000  ' 64-bit is an option
Global Const DLG_CR_BITALL = &H3FFF ' All BitsPerPixel are options

Global Const DLG_CR_DITHER_NONE = &H4000        ' no dithering is an option
Global Const DLG_CR_DITHER_FLOYD = &H8000       ' floyd dithering is an option
Global Const DLG_CR_DITHER_STUCKI = &H10000     ' stucki dithering is an option
Global Const DLG_CR_DITHER_BURKES = &H20000     ' burkes dithering is an option
Global Const DLG_CR_DITHER_SIERRA = &H40000     ' sierra dithering is an option
Global Const DLG_CR_DITHER_STEVENSON = &H80000  ' stevenson dithering is an option
Global Const DLG_CR_DITHER_JARVIS = &H100000    ' jarvis dithering is an option
Global Const DLG_CR_DITHER_CLUSTER = &H200000   ' clustered dithering is an option
Global Const DLG_CR_DITHER_ORDERED = &H400000   ' ordered dithering is an option
Global Const DLG_CR_DITHER_ALL = &H7FC000       ' All dithering methods are options

Global Const DLG_CR_PAL_FIXED = &H800000        ' fixed palette is an option
Global Const DLG_CR_PAL_OPTIMIZED = &H1000000   ' fixed palette is an option
Global Const DLG_CR_PAL_IDENTITY = &H2000000    ' identity palette is an option
Global Const DLG_CR_PAL_NETSCAPE = &H4000000    ' netscape palette is an option
Global Const DLG_CR_PAL_SVGA = &H8000000        ' SVGA palette is an option
Global Const DLG_CR_PAL_UNIFORM = &H10000000    ' Uniform palette is an option
Global Const DLG_CR_PAL_MSIE = &H20000000       ' MSIE palette is an option
Global Const DLG_CR_PAL_ALL = &H3F800000        ' All palette options are options


' flags for L_DlgWindowLevel()
Global Const DLG_WL_SHOWPREVIEW = &H1
Global Const DLG_WL_AUTOPROCESS = &H2
Global Const DLG_WL_95CONTEXTHELP = &H4              ' Dlg should contain context sensitive help icon

'PaintEffectDlgConstants
Global Const DLG_EFX_SHOWPREVIEW = &H1
Global Const DLG_EFX_AUTOPREVIEW = &H2
Global Const DLG_EFX_DELAY = &H4
Global Const DLG_EFX_GRAIN = &H8
Global Const DLG_EFX_PASSES = &H10
Global Const DLG_EFX_TRANSPARENT = &H20
Global Const DLG_EFX_WAND = &H40
Global Const DLG_EFX_NO_TREEVIEW = &H80
Global Const DLG_EFX_CLASS_NONE = &H100
Global Const DLG_EFX_CLASS_WIPE = &H200
Global Const DLG_EFX_CLASS_WIPERECT = &H400
Global Const DLG_EFX_CLASS_WIPECIRCLE = &H800
Global Const DLG_EFX_CLASS_PUSH = &H1000
Global Const DLG_EFX_CLASS_SLIDE = &H2000
Global Const DLG_EFX_CLASS_ROLL = &H4000
Global Const DLG_EFX_CLASS_ROTATE = &H8000
Global Const DLG_EFX_CLASS_ZOOM = &H10000
Global Const DLG_EFX_CLASS_DRIP = &H20000
Global Const DLG_EFX_CLASS_BLIND = &H40000
Global Const DLG_EFX_CLASS_RANDOM = &H80000
Global Const DLG_EFX_CLASS_CHECK = &H100000
Global Const DLG_EFX_CLASS_BLOCKS = &H200000
Global Const DLG_EFX_CLASS_CIRCLE = &H400000
Global Const DLG_EFX_CLASS_ELLIPSE = &H800000
Global Const DLG_EFX_95CONTEXTHELP = &H1000000        ' Dlg should contain context sensitive help icon

'GradientDlgConstants
Global Const DLG_GRAD_SHOWPREVIEW = &H1
Global Const DLG_GRAD_AUTOPREVIEW = &H2
Global Const DLG_GRAD_STARTCOLOR = &H4
Global Const DLG_GRAD_ENDCOLOR = &H8
Global Const DLG_GRAD_STEPS = &H10
Global Const DLG_GRAD_NO_TREEVIEW = &H20
Global Const DLG_GRAD_CLASS_LINEAR = &H40
Global Const DLG_GRAD_CLASS_ANGULAR = &H80
Global Const DLG_GRAD_CLASS_RECTANGULAR = &H100
Global Const DLG_GRAD_CLASS_ELLIPTICAL = &H200
Global Const DLG_GRAD_CLASS_CONICAL = &H400
Global Const DLG_GRAD_95CONTEXTHELP = &H800   ' Dlg should contain context sensitive help icon

'TransitionDlgConstants
Global Const DLG_TRANS_SHOWPREVIEW = &H1
Global Const DLG_TRANS_AUTOPREVIEW = &H2
Global Const DLG_TRANS_FORECOLOR = &H4
Global Const DLG_TRANS_BACKCOLOR = &H8
Global Const DLG_TRANS_DELAY = &H10
Global Const DLG_TRANS_GRAIN = &H20
Global Const DLG_TRANS_EFFECT = &H40
Global Const DLG_TRANS_PASSES = &H80
Global Const DLG_TRANS_WAND = &H100
Global Const DLG_TRANS_TRANSPARENT = &H200
Global Const DLG_TRANS_GRADIENT = &H400
Global Const DLG_TRANS_95CONTEXTHELP = &H800   ' Dlg should contain context sensitive help icon

'ShapeDlgConstants
Global Const DLG_SHAPE_SHOWPREVIEW = &H1
Global Const DLG_SHAPE_AUTOPREVIEW = &H2
Global Const DLG_SHAPE_BACKSTYLE = &H4
Global Const DLG_SHAPE_FILLSTYLE = &H8
Global Const DLG_SHAPE_FORE_BACK_COLOR = &H10
Global Const DLG_SHAPE_BORDERSTYLE = &H20
Global Const DLG_SHAPE_BORDERWIDTH = &H40
Global Const DLG_SHAPE_BORDERCOLOR = &H80
Global Const DLG_SHAPE_INNERSTYLE = &H100
Global Const DLG_SHAPE_INNERWIDTH = &H200
Global Const DLG_SHAPE_INNER_HILITE_SHADOW = &H400
Global Const DLG_SHAPE_OUTERSTYLE = &H800
Global Const DLG_SHAPE_OUTERWIDTH = &H1000
Global Const DLG_SHAPE_OUTER_HILITE_SHADOW = &H2000
Global Const DLG_SHAPE_SHADOWCOLOR = &H4000
Global Const DLG_SHAPE_SHADOW_X_Y = &H8000
Global Const DLG_SHAPE_BROWSEIMAGE = &H10000
Global Const DLG_SHAPE_NO_TREEVIEW = &H20000
Global Const DLG_SHAPE_CLASS_SQUARE = &H40000
Global Const DLG_SHAPE_CLASS_RECTANGLE = &H80000
Global Const DLG_SHAPE_CLASS_PARALLELOGRAM = &H100000
Global Const DLG_SHAPE_CLASS_TRAPEZOID = &H200000
Global Const DLG_SHAPE_CLASS_TRIANGLE = &H400000
Global Const DLG_SHAPE_CLASS_OTHER = &H800000
Global Const DLG_SHAPE_CLASS_CIRCLE = &H1000000
Global Const DLG_SHAPE_CLASS_ELLIPSE = &H2000000
Global Const DLG_SHAPE_CLASS_STAR = &H4000000
Global Const DLG_SHAPE_CLASS_CROSS = &H8000000
Global Const DLG_SHAPE_CLASS_ARROW = &H10000000
Global Const DLG_SHAPE_95CONTEXTHELP = &H20000000   ' Dlg should contain context sensitive help icon

'TextDlgConstants
Global Const DLG_TEXT_SHOWPREVIEW = &H1
Global Const DLG_TEXT_AUTOPREVIEW = &H2
Global Const DLG_TEXT_SAMPLETEXT = &H4
Global Const DLG_TEXT_STYLE = &H8
Global Const DLG_TEXT_COLOR = &H10
Global Const DLG_TEXT_BORDERCOLOR = &H20
Global Const DLG_TEXT_ALIGN = &H40
Global Const DLG_TEXT_ANGLE = &H80
Global Const DLG_TEXT_WORDWRAP = &H100
Global Const DLG_TEXT_FONT = &H200
Global Const DLG_TEXT_FOREIMAGE = &H400
Global Const DLG_TEXT_BROWSEIMAGE = &H800
Global Const DLG_TEXT_SHADOWCOLOR = &H1000
Global Const DLG_TEXT_SHADOW_X_Y = &H2000
Global Const DLG_TEXT_95CONTEXTHELP = &H4000   ' Dlg should contain context sensitive help icon

' flags for L_DlgContourFilter()
Global Const DLG_CONTOUR_SHOWPREVIEW = &H1              ' shows preview of image
Global Const DLG_CONTOUR_AUTOPROCESS = &H2              ' AutoProcess on close
Global Const DLG_CONTOUR_OPTION = &H4                   ' Contour Option is an option
Global Const DLG_CONTOUR_THRESHOLD = &H8                ' Threshold is an option
Global Const DLG_CONTOUR_DELTADIRECTION = &H10           ' DeltaDirection is an option
Global Const DLG_CONTOUR_MAXIMUMERROR = &H20             ' MaximumError is an option
Global Const DLG_CONTOUR_95CONTEXTHELP = &H40            ' Dlg should contain context sensitive help icon

Global Const DLG_CONTOUR_OPTION_THIN = &H1
Global Const DLG_CONTOUR_OPTION_LINK_BW = &H2
Global Const DLG_CONTOUR_OPTION_LINK_GRAY = &H4
Global Const DLG_CONTOUR_OPTION_LINK_COLOR = &H8
Global Const DLG_CONTOUR_OPTION_APPROX_COLOR = &H10

'possible values for uSaveMulti
'FileSaveDlgMultipageConstants
Global Const SAVE_OVERWRITE = 0
Global Const SAVE_APPEND = 1
Global Const SAVE_REPLACE = 2
Global Const SAVE_INSERT = 3

Global Const DLG_OFN_OVERWRITEPROMPT = &H2   ' FileSave will prompt if file exists
Global Const DLG_OFN_NOCHANGEDIR = &H8       ' restore dir to original after close
Global Const DLG_OFN_ALLOWMULTI = &H200      ' allow multiple files to be selected

Global Const DLG_HALFTONE_SHOWPREVIEW = &H1
Global Const DLG_HALFTONE_AUTOPROCESS = &H2
Global Const DLG_HALFTONE_95CONTEXTHELP = &H4
Global Const DLG_HALFTONE_TOOL = &H8

'Capture Resource Types
Global Const CAPTURE_ICON = 1
Global Const CAPTURE_BITMAP = 2
Global Const CAPTURE_CURSOR = 3

'Capture Area Types
Global Const CAPTURE_AREA_TRIANGLE = 1
Global Const CAPTURE_AREA_RECT = 2
Global Const CAPTURE_AREA_ROUNDRECT = 3
Global Const CAPTURE_AREA_ELLIPSE = 4
Global Const CAPTURE_AREA_POLYGON = 5
Global Const CAPTURE_AREA_FREEHAND = 6

'Window-Client Capture Options
Global Const CAPTURE_CLIENT_AREA = 1
Global Const CAPTURE_WINDOW = 2

Global Const SCOD_MIN_TIME = 0
Global Const SCOD_MAX_TIME = 60
Global Const SCOD_MAX_REPEAT = 120
Global Const SCOD_MIN_REPEAT = 0

'flags for L_CaptureFromExe (Types of resources)
Global Const RESTYPE_BITMAP = &H1
Global Const RESTYPE_ICON = &H2
Global Const RESTYPE_CURSOR = &H4

'flags for L_CaptureFromExeDlg (Dialog Type - nDialogType)
Global Const LTCAPDLG_TABVIEW = &H0
Global Const LTCAPDLG_TREEVIEW = &H1

'Optional Cursor for L_CaptureArea (LEADCAPTUREAREAOPTION.hDrawCursor)
Global Const CAPTURE_AREA_CROSSLINES_CURSOR = -1

'flags for L_CaptureArea - Area Fill Pattern
Global Const CAPTURE_AREA_PATTERN_HORIZONTAL = 0  ' -----
Global Const CAPTURE_AREA_PATTERN_VERTICAL = 1    ' |||||
Global Const CAPTURE_AREA_PATTERN_FDIAGONAL = 2   ' \\\\\
Global Const CAPTURE_AREA_PATTERN_BDIAGONAL = 3   ' /////
Global Const CAPTURE_AREA_PATTERN_CROSS = 4       ' +++++
Global Const CAPTURE_AREA_PATTERN_DIAGCROSS = 5   ' xxxxx
Global Const CAPTURE_AREA_PATTERN_SOLID = 6       'Solid Fill

'Flags for L_Capture Area - Area Line Style
Global Const CAPTURE_AREA_LINE_SOLID = 0          ' Solid
Global Const CAPTURE_AREA_LINE_DASH = 1           ' -------
Global Const CAPTURE_AREA_LINE_DOT = 2            ' .......
Global Const CAPTURE_AREA_LINE_DASHDOT = 3        ' _._._._
Global Const CAPTURE_AREA_LINE_DASHDOTDOT = 4     ' _.._.._

'Flags for L_CaptureArea = Capture Area Info Window Optional Size
Global Const CAPTURE_AREA_INFOWND_SIZE_TINY = -1
Global Const CAPTURE_AREA_INFOWND_SIZE_SMALL = -2
Global Const CAPTURE_AREA_INFOWND_SIZE_MEDIUM = -3
Global Const CAPTURE_AREA_INFOWND_SIZE_LARGE = -4
Global Const CAPTURE_AREA_INFOWND_SIZE_XLARGE = -5

'Flags for L_CaptureArea - Capture Area Info Window Optional Position

'flags for L_Capture Area - X position of Info window -  LEADCAPTUREAREAOPTION.nInfoLeft
Global Const CAPTURE_AREA_INFOWND_POS_LEFT = -1
Global Const CAPTURE_AREA_INFOWND_POS_RIGHT = -2

'flags for L_Capture Area - Y position of Info window - LEADCAPTUREAREAOPTION.nInfoTop
Global Const CAPTURE_AREA_INFOWND_POS_TOP = -3
Global Const CAPTURE_AREA_INFOWND_POS_BOTTOM = -4

'flags for L_CaptureArea - LEADCAPTUREAREAOPTION.uFlags
Global Const CAPTURE_AREA_SHOW_DRAWCURSOR = &H1
Global Const CAPTURE_AREA_INCLUDE_CURSOR = &H2
Global Const CAPTURE_AREA_ENABLE_KEYBOARD = &H4
Global Const CAPTURE_AREA_SHOW_OPAQUE_TEXT = &H8
Global Const CAPTURE_AREA_SHOW_CURSORPOS = &H10
Global Const CAPTURE_AREA_SHOW_CAPTURESIZE = &H20
Global Const CAPTURE_AREA_SHOW_INFOWINDOW = &H40
Global Const CAPTURE_AREA_SENSITIVE_INFOWINDOW = &H80
Global Const CAPTURE_AREA_BITMAP_WITH_REGION = &H100
Global Const CAPTURE_AREA_USE_DEFAULT_VALUES = &H200

'zooming factors (exclusive)
Global Const CAPTURE_AREA_ZOOM_NORM = &H1000
Global Const CAPTURE_AREA_ZOOM_BY2X = &H2000
Global Const CAPTURE_AREA_ZOOM_BY3X = &H3000
Global Const CAPTURE_AREA_ZOOM_BY4X = &H4000
Global Const CAPTURE_AREA_ZOOM_BY5X = &H5000
Global Const CAPTURE_AREA_ZOOM_BY6X = &H6000
Global Const CAPTURE_AREA_ZOOM_BY7X = &H7000
Global Const CAPTURE_AREA_ZOOM_BY8X = &H8000
Global Const CAPTURE_AREA_ZOOM_BY9X = &H9000
Global Const CAPTURE_AREA_ZOOM_BY10X = &HA000
Global Const CAPTURE_AREA_ZOOM_BY11X = &HB000
Global Const CAPTURE_AREA_ZOOM_BY12X = &HC000
Global Const CAPTURE_AREA_ZOOM_BY13X = &HD000
Global Const CAPTURE_AREA_ZOOM_BY14X = &HE000
Global Const CAPTURE_AREA_ZOOM_BY15X = &HF000

'flags for L_CaptureSelectedObject
Global Const CAPTURE_OBJECT_INVERT = &H1
Global Const CAPTURE_OBJECT_ENABLE_KEYBOARD = &H2

'flags for L_RotateBitmap
Global Const ROTATE_RESIZE = &H1
Global Const ROTATE_RESAMPLE = &H2
Global Const ROTATE_BICUBIC = &H4

'******** LEADTools 32 bit structures ********'
' L_Resize structure
Type RESIZEDATA
 OldWidth As Long
 OldHeight As Long
 NewWidth As Long
 NewHeight As Long
 XIncrease As Long
 YIncrease As Long
 XFactor(0 To 255) As String
 YFactor(0 To 255) As String
End Type

Type POINT           ' Windows SDK structure
   x As Long
   y As Long
End Type

' Windows RECT structure
Type RECT
 left As Long
 top As Long
 right As Long
 bottom As Long
End Type

' Windows OPENFILENAME structure
Type OPENFILENAME
   lStructSize As Long
   hwndOwner As Long
   hInstance As Long
   lpstrFilter As String
   lpstrCustomFilter As String
   nMaxCustFilter As Long
   nFilterIndex As Long
   lpstrFile As String
   nMaxFile As Long
   lpstrFileTitle As String
   nMaxFileTitle As Long
   lpstrInitialDir As String
   lpstrTitle As String
   Flags As Long
   nFileOffset As Integer
   nFileExtension As Integer
   lpstrDefExt As String
   lCustData As Long
   lpfnHook As Long
   lpTemplateName As String
End Type

' LEAD FILEOPENPARM structure
Type FILEOPENPARM
   nSize As Long
   szFileName As String * 260
   pBitmap As Long
   pThumbnail As Long
   pFileInfo As Long
   nPageNumber As Long
   nPasses As Long
   bLoadCompressed As Long
   bLoadRotated As Long
   bPreviewEnabled As Long
End Type

' LEAD FILESAVEPARM structure
Type FILESAVEPARM
   nSize As Long
   szFileName As String * 260
   pBitmap As Long
   nBitsPerPixel As Long
   nFormat As Long
   nQFactor As Long
   uSaveMulti As Long
   bSaveInterlaced As Long
   bSaveProgressive As Long
   nPasses As Long
   bSaveWithStamp As Long
   nStampBits As Long
   nStampWidth As Long
   nStampHeight As Long
   nPageNumber As Long
   nSubTypeIndex As Long
End Type

Type FILESAVEFORMAT
   nSize As Long
   nFormat As Long
   uSubFormats As Long
End Type

' LEAD EFXDLGPARM structure
Type EFXDLGPARM
   nSize As Long
   uEffect As Long
   uGrain As Long
   uDelay As Long
   uMaxPass As Long
   bTransparent As Long
   crTransparent As Long
   uWandWidth As Long
   crWand As Long
End Type

' LEAD SHAPEDLGPARM structure
Type SHAPEDLGPARM
   nSize As Long
   uShape As Long
   crBack As Long
   uBackStyle As Long
   crFill As Long
   uFillStyle As Long
   crBorder As Long
   uBorderStyle As Long
   uBorderWidth As Long
   crInnerHilite As Long
   crInnerShadow As Long
   uInnerStyle As Long
   uInnerWidth As Long
   crOuterHilite As Long
   crOuterShadow As Long
   uOuterStyle As Long
   uOuterWidth As Long
   nShadowX As Long
   nShadowY As Long
   crShadow As Long
End Type

'LEAD TEXTDLGPARM structure
Type TEXTDLGPARM
   nSize As Long
   pszSampleText As String
   nMaxCount As Long
   nAngle As Long
   uStyle As Long
   uAlign As Long
   bWordWrap As Long
   hFont As Long
   crText As Long
   crHilite As Long
   crShadow As Long
   nXDepth As Long
   nYDepth As Long
   bUseForeImage As Long
End Type

'LEAD GRADDLGPARM structure
Type GRADDLGPARM
   nSize As Long
   uStyle As Long
   crStart As Long
   crEnd As Long
   uSteps As Long
End Type

'LEAD TRANSDLGPARM structure
Type TRANSDLGPARM
   nSize As Long
   uTransition As Long
   crBack As Long
   crFore As Long
   uSteps As Long
   uEffect As Long
   uGrain As Long
   uDelay As Long
   uMaxPass As Long
   bTransparent As Long
   crTransparent As Long
   uWandWidth As Long
   crWand As Long
End Type

'LEAD GETNOISEDLGPARM structure
Type GETNOISEDLGPARM
   nSize As Long           ' size of this structure
   uRange As Long          ' the noise value
   uChannel As Long        ' the channel.
End Type

' LEAD GETEMBOSSDLGPARM structure
Type GETEMBOSSDLGPARM
   nSize As Long
   uDepth As Long
   uDirection As Long
End Type

' LEAD GETCHANGEDLGPARM structure
Type GETCHANGEDLGPARM
   nSize As Long           ' size of this structure
   nChange As Long            ' the change value
   uProcess As Long           ' flag indicating which function was chosen.
End Type

' LEAD GETCHANGEDLGPARM structure
Type HALFTONEDLGPARM
   nSize As Long           ' size of this structure
   nAngle As Long          ' the change value
   uType As Long                 ' flag indicating which function was chosen.
End Type

' LEAD COLORRESDLGPARM structure
Type COLORRESDLGPARM
   nSize As Long
   nBitsPerPixel As Long   ' the desired bits per pixel
   uColorResFlags As Long  ' user's choice of flags
   hpalCustom As Long
End Type

' LEAD GETANGLEDLGPARM structure
Type GETANGLEDLGPARM
   nSize As Long
   nAngle As Long          ' Angle
   bFlag As Long           ' option flag for the dialog
   uResize As Long
   crBack As Long          ' Background color
End Type

' LEAD GETSIZEDLGPARM structure
Type GETSIZEDLGPARM
   nSize As Long           ' size of this structure
   nWidth As Long          ' the new width
   nHeight As Long         ' the new width
   uResize As Long         ' Flags for the Method of resizing
   nResolutionX As Long
   nResolutionY As Long
End Type

'LEAD GETGAMMADLGPARM structure
Type GETGAMMADLGPARM
   nSize As Long
   nRedValue As Long
   nGreenValue As Long
   nBlueValue As Long
   bAllChannels As Long
End Type

' LEAD GETRANGEDLGPARM structure
Type GETRANGEDLGPARM
   nSize As Long
   uLow As Long
   uHigh As Long
End Type

' LEAD CONTOURFILTERDLGPARM structure
Type CONTOURFILTERDLGPARM
   nSize As Long
   nThreshold As Integer
   nDeltaDirection As Integer
   nMaxError As Integer
   nOption As Long
   uOptionFlags As Long
End Type

'LEAD GETDIRECTORYDLGPARM structure
Type GETDIRECTORYDLGPARM
   nSize As Long          ' size of this structure
   pszDirectory As String
   nBuffSize As Long
   pszFilter As String
   nFilterIndex As Long
   pszTitle As String
End Type

' LEAD WINDOWLEVELDLGPARM structure
Type WINDOWLEVELDLGPARM
   nSize As Long          ' size of this structure
   pLUT As Long
   uLUTLength As Long
   nLowBit As Long
   nHighBit As Long
   nLow As Long
   nHigh As Long
   crStart As Long
   crEnd As Long
End Type

' Windows BitmapInfoHeader structure
Type BITMAPINFOHEADER
 biSize As Long
 biWidth As Long
 biHeight As Long
 biPlanes As Integer
 biBitCount As Integer
 biCompression As Long
 biSizeImage As Long
 biXPelsPerMeter As Long
 biYPelsPerMeter As Long
 biClrUsed As Long
 biClrImportant As Long
End Type

Type BITMAPINFO
        bmiHeader As BITMAPINFOHEADER
End Type

' LEAD BitmapHandle structure
Type LEADBitmapHandle
 Reserved1 As Long
 Reserved2 As Long
 
 Width As Long
 Height As Long
 BitsPerPixel As Long
 BytesPerLine As Long
 CurrentPos As Long
 CurrentRow As Long

 Flags As Long

 nColors As Long

 hPalette As Long
 
 ViewPerspective As Long
 Order As Long
 Size As Long
 pDitherData As Long
 DitheringMethod As Long
 pRgnInfo As Long             ' Internal use
 XResolution As Long
 YResolution As Long
 left As Long                 ' Left playback offset
 top As Long                  ' Top playback offset
 Delay As Long                ' Playback delay (ms)
 Background As Long           ' Playback background color (COLORREF)
 Transparency As Long         ' Playback transparent color (COLORREF)
 DisposalMethod As Long       ' Playback disposal method
 LowBit As Long               ' low bit set by L_WindowLevel
 HighBit As Long              ' high bit set by L_WindowLeve
 pLUT As Long                 ' LUT set by L_WindowLevel
 LUTLength As Long            ' no of entries pointed by LUT
 DataOffset As Long           ' Internal use
 MinVal As Long               ' min val for a grayscale bitmap
 MaxVal As Long               ' max val for a grayscale bitmap
 PaintLowBit As Long          ' low bit set by L_WindowLevelBitmap
 PaintHighBit As Long         ' high bit set by L_WindowLevelBitmap
 PaintGamma As Long
 PaintContrast As Long
 PaintIntensity As Long
 pPaintLUT As Long
 Reserved As Long
End Type

' Add Frame.
' LEAD ADDFRAMEINFO structure
Type AddFrameInfo
   hBitmapFrame As LEADBitmapHandle
   bKeepFrameState As Long
   bUseMask As Long
   crMask As Long
   SmoothEdge As Long
   nLocation As Long
   nQuality As Long
End Type

' Add Border
' LEAD ADDBORDERINFO structure
Type AddBorderInfo
   nLeftThickness As Long
   nTopThickness As Long
   nRightThickness As Long
   nBottomThickness As Long
   nLocation As Long
   nStyle As Long
   nEffectStyle As Long
   hTileBitmap As LEADBitmapHandle
   nGradientStyle As Long
   crGradientStart As Long
   crGradientEnd As Long
   nCurveIntesity As Long
   bSoftCurve As Long
   bShadow As Long
   nShadowSize As Long
   nShadowDirection As Long
   bBumpyShadow As Long
End Type

' FileInfo structure
Type FileInfo
 Format As Long            'File Format
 Name As String * 16       'File Name
 Width As Long             'Image Width
 Height As Long            'Image Height
 BitsPerPixel As Long      'Bits Per Pixel
 SizeDisk As Long          'Size of File on Disk
 SizeMem As Long           'Size of Image in Memory
 Compression As String * 20 'Compression Method Name
 ViewPerspective As Long   'Image View Perspective
 Order As Long             'RGB Order
 PageNumber As Long        'Page Number
 TotalPages As Long        'Total Number of Pages
 XResolution As Long       'X Resolution of the Image, If the Format Supports This.
 YResolution As Long       'Y Resolution of the Image, If the Format Supports This.
 uFlags As Long            'Flags describing the file
 GlobalLoop As Long        'Global animation loop count 0 = infinity
 GlobalWidth As Long       'Global width
 GlobalHeight As Long      'Global height
 GlobalBackground As Long  'Global background color (see Flags)
 GlobalPalette(256) As Long 'Global palette as 256 RGBQUADs (see Flags)
 IFD As Long               'IFD offset (for TIF files only)
 Layers As Long            'The number of layers in the file
End Type

' Version structure
Type VERSIONINFO
 Product As String * 60
 Level As Long
 MajorNumber As Long
 MinorNumber As Long
 Date As String * 16
 Time As String * 16
End Type


' TWAIN Interface Properties structure
Type TWAINPROPERTIES
 AppManufacturer As String * 36
 AppProdFamily As String * 36
 AppProdName As String * 36
 SourceName As String * 36
 nMaxPages As Long
 nPixelType As Long
 nBits As Long
 nRes As Long
 nXPos As Long
 nYPos As Long
 nWidth As Long
 nHeight As Long
 nBrightness As Long
 nContrast As Long
 nOrientation As Long
 nFeederEnabled As Long
 nEnableAutoFeed As Long
End Type

' PCDInfo structure for resolutions
Type PCDINFO
 resolution(0 To 5) As Long
End Type

' TIFF Tag structure
Type TIFF_TAG
 tag_id As Long
 Type As Long
 count As Long
 lData As Long
End Type

' structure for L_CreateThumbnailFromFile
Type ThumbOptions
   nWidth As Long
   nHeight As Long
   nBits As Long
   uCRFlags As Long
   bMaintainAspect As Long
   bForceSize As Long
   crBackColor As Long
   bLoadStamp As Long
   bResample As Long
End Type

' Extended file option structures
Type LOADFILEOPTION
 lSize As Long
 XResolution As Long
 YResolution As Long
 Flags As Long
 Passes As Long
 PageNumber As Long
 GlobalLoop As Long
 IFD As Long
End Type

Type SAVEFILEOPTION
 lSize As Long
 Reserved1 As Long
 Reserved2 As Long
 Flags As Long
 Passes As Long
 PageNumber As Long
 GlobalWidth As Long
 GlobalHeight As Long
 GlobalLoop As Long
 GlobalBackground As Long
 GlobalPalette(256) As Long
 StampWidth As Long
 StampHeight As Long
 StampBits As Long
 Constrained As Boolean
 FieldPic As Boolean
 FrameRate As Long
 FramesGOP As Long
 PelAspectRatio As Long
 ProfileID As Long
 LevelID As Long
 ChromaFormat As Long
 VideoFormat As Long
 IntraDcPrec As Long
 BitRate As Long
 UserInfo As String * 255
 IFD As Long
 szPassword As String * 255 ' password for saving encrypted files
 PhotometricInterpretation As Long
 TileWidth As Long
 TileHeight As Long
End Type

' PhotometricInterpretation values
Global Const PME_MINISWHITE = 0     ' min value is white
Global Const PME_MINISBLACK = 1     ' min value is black
Global Const PME_RGB = 2            ' RGB color model
Global Const PME_PALETTE = 3        ' color map indexed
Global Const PME_MASK = 4           ' holdout mask
Global Const PME_SEPARATED = 5      ' !color separations
Global Const PME_YCBCR = 6          ' !CCIR 601
Global Const PME_CIELAB = 8         ' !1976 CIE L*a*b*

' Binary filter structure
Type BINARYFLT
 bfltMax As Long            ' select maximimum value
 bfltDim As Long            ' filter dimensions
 bfltMatrix(0 To 0) As Long 'array of filter coefficients
End Type

' Spatial filter structure
Type SPATIALFLT
 fltDivisor As Long 'sum divisor
 fltBias As Long    'sum bias
 fltDim As Long     'filter dimensions
 fltMatrix(0 To 0) As Long 'array of filter coefficients
End Type

' LEAD GETFILTERDLGPARM structure
Type GETFILTERDLGPARM
   nSize As Long
   pSpatialFlt As SPATIALFLT
   pBinaryFlt As BINARYFLT
   bSpatialFilter As Long
End Type

' Structure used by L_SetLoadInfoCallback
Type LOADINFO
   Format As Long            ' File format: FILE_PCX, ...
   Width As Long             ' Image width
   Height As Long            ' Image height
   BitsPerPixel As Long      ' Bits per pixel
   XResolution As Long       ' X resolution (DPI)
   YResolution As Long       ' Y resolution (DPI)
   Offset As Long            ' Data offset
   Flags As Long             ' Special flags
   ' for RAW file filter
   rgbQuad(256) As Long
   
   ' for RAW BITFIELDS - contains R,G,B color masks
   rgbColorMask(0 To 2) As Long

   ' for RAW_PACKBITS
   uStripSize As Long      ' size of strip after compression
   nPhotoInt As Long       ' TIFF tag  0-6  TIFF tag
   nPlanarConfig As Long   ' TIFF tag  1 = Chunky,  2 = Planar format
End Type

' Region transform structure
Type RGNXFORM
   uViewPerspective As Long
   nXScalarNum As Long
   nXScalarDen As Long
   nYScalarNum As Long
   nYScalarDen As Long
   nXOffset  As Long
   nYOffset As Long
End Type

'    structure used by L_ReadLoadResolutions
Type DIMENSION
   nWidth As Long
   nHeight As Long
End Type

'   LEADCAPTUREOPTION structure
Type LEADCAPTUREOPTION
   hCursor As Long
   hStatusCursor As Long
   nHotKey As Long
   uHotKeyModifiers As Long
   nCancelKey As Long
   nDelay As Long
   uCount As Long
   nInterval As Long
End Type

'   LEADCAPTUREINFO structure
Type LEADCAPTUREINFO
   hWnd As Long
   rcArea As RECT
   nResType As Long
   nIndex As Long
   pszResID As String
   szReserved As String * 256
   pszExeName As String
   nMaxExeName As Long
End Type

'   LEADCAPTUREAREAOPTION structure
Type LEADCAPTUREAREAOPTION
   uSize As Long
   uAreaType As Long
   nFillPattern As Long
   crFillForeColor As Long
   crFillBackColor As Long
   uDrawLineStyle As Long
   crDrawLineColor As Long
   uEllipseWidth As Long
   uEllipseHeight As Long
   uFlags As Long
   hDrawCursor As Long
   crTextForeColor As Long
   crTextBackColor As Long
   nInfoLeft As Long
   nInfoTop As Long
   nInfoWidth As Long
   nInfoHeight As Long
End Type

'   CAPTUROBJECTOPTIONS structure
Type LEADCAPTUREOBJECTOPTION
   uFlags As Long
   uBorderWidth As Long
   hSelectCursor As Long
End Type

'******** LEADTools 32-bit BarCode Constants ********
' Bar Code Status
Global Const BARCODE_NORMAL = 1
Global Const BARCODE_ERRORCHECK = 2

' Bar Code Read/Write Flags for 1D
Global Const BARCODE_MARKERS = &H1
Global Const BARCODE_BLOCK_SEARCH = &H2

' Bar Code Write Flags for CodeOne and PDF417
Global Const BARCODE_TRUNCATE = &H10
Global Const BARCODE_MSGAPPEND = &H20
Global Const BARCODE_INITREADER = &H40
Global Const BARCODE_COLROWASLIMITS = &H80
Global Const BARCODE_DISABLE_COMPRESSOPN = &H100

' Units of measurment in an image
Global Const BARCODE_SCANLINES_PER_PIXELS = 0       ' Use scanlines/pixels
Global Const BARCODE_INCHES = 1                     ' Use Inches, you must multiply one inch by 100
Global Const BARCODE_MILLIMETERS = 2                ' Use Millimeters

' Bar Code Direction, used for Read 1D and PDF417
Global Const BARCODE_DIR_LEFT_TO_RIGHT = &H1
Global Const BARCODE_DIR_RIGHT_TO_LEFT = &H2
Global Const BARCODE_DIR_TOP_TO_BOTTOM = &H4
Global Const BARCODE_DIR_BOTTOM_TO_TOP = &H8

' Bar Code Justification for Write CodeOne and PDF417
Global Const BARCODE_JUSTIFY_RIGHT = &H1000
Global Const BARCODE_JUSTIFY_H_CENTER = &H2000
Global Const BARCODE_JUSTIFY_BOTTOM = &H4000
Global Const BARCODE_JUSTIFY_V_CENTER = &H8000

' PDF417 ECC LEVEL Constants
Global Const BARCODE_PDF417_ECCLEVEL_0 = &H1
Global Const BARCODE_PDF417_ECCLEVEL_1 = &H2
Global Const BARCODE_PDF417_ECCLEVEL_2 = &H4
Global Const BARCODE_PDF417_ECCLEVEL_3 = &H8
Global Const BARCODE_PDF417_ECCLEVEL_4 = &H10
Global Const BARCODE_PDF417_ECCLEVEL_5 = &H20
Global Const BARCODE_PDF417_ECCLEVEL_6 = &H40
Global Const BARCODE_PDF417_ECCLEVEL_7 = &H80
Global Const BARCODE_PDF417_ECCLEVEL_8 = &H100
Global Const BARCODE_PDF417_ECCUSE_PERCENT = &HFFF

' Bar Code (1D) Read/Write Types
Global Const BARCODE_1D_EAN_13 = &H1
Global Const BARCODE_1D_EAN_8 = &H2
Global Const BARCODE_1D_UPC_A = &H4
Global Const BARCODE_1D_UPC_E = &H8
Global Const BARCODE_1D_CODE_3_OF_9 = &H10
Global Const BARCODE_1D_CODE_128 = &H20
Global Const BARCODE_1D_CODE_I2_OF_5 = &H40
Global Const BARCODE_1D_CODA_BAR = &H80

' The following define used only for read any bar code (1D) type in the image
Global Const BARCODE_1D_READ_ANYTYPE = &H100

' Bar Code CodeOne Read Types
Global Const BARCODE_R_CODEONE_A_TO_H = &H200
Global Const BARCODE_R_CODEONE_T = &H400
Global Const BARCODE_R_CODEONE_S = &H800
Global Const BARCODE_R_CODEONE_ANYTYPE = &H1000

' Bar Code PDF417 Read/Write Type
Global Const BARCODE_PDF417 = &H2000

' Code One Write/Return Read Type Sub Types
Global Const BARCODE_CODEONE_DEF = &H4000
Global Const BARCODE_CODEONE_TDEF = &H8000
Global Const BARCODE_CODEONE_SDEF = &H10000
Global Const BARCODE_CODEONE_A = &H20000
Global Const BARCODE_CODEONE_B = &H40000
Global Const BARCODE_CODEONE_C = &H80000
Global Const BARCODE_CODEONE_D = &H100000
Global Const BARCODE_CODEONE_E = &H200000
Global Const BARCODE_CODEONE_F = &H400000
Global Const BARCODE_CODEONE_G = &H800000
Global Const BARCODE_CODEONE_H = &H1000000
Global Const BARCODE_CODEONE_T16 = &H2000000
Global Const BARCODE_CODEONE_T32 = &H4000000
Global Const BARCODE_CODEONE_T48 = &H8000000
Global Const BARCODE_CODEONE_S10 = &H10000000
Global Const BARCODE_CODEONE_S20 = &H20000000
Global Const BARCODE_CODEONE_S30 = &H40000000

'******** LEADTools 32-bit BarCode Structures ********
Type BARCODEDATA
   nGroup As Long              ' used only for CodeOne and PDF417
   ulType As Long
   nUnits As Long
   rcBarLocation As RECT
   nSizeofBarCodeData As Long
   pszBarCodeData As Long
   nIndexDuplicate As Long     ' for reading only
   nTotalCount As Long         ' for reading only
End Type

Type BARCODE1D
   bOutShowText As Boolean     ' for writing only
   nDirection As Long          ' for reading only
   bErrorCheck As Boolean
   nGranularity As Long
   nMinLength As Long
   nMaxLength As Long
   nWhiteLines As Long
End Type

Type BARCODEREADPDF
   nDirection As Long
End Type

Type BARCODEWRITECODEONE
   nElementX As Long
   nElementY As Long
   nJustify As Long
End Type

Type BARCODEWRITEPDF
   wEccPerc As Integer
   wEccLevel As Integer
   wAspectHeight As Integer
   wAspectWidth As Integer
   wModAspectRatio As Integer
   wColumns As Integer
   wRows As Integer
   wModule As Integer
   nJustify As Long
End Type

Type BARCODEVERSION
   Product(1 To 60) As Integer
   MajorNumber As Long
   MinorNumber As Long
   Date(1 To 16) As Integer
   Time(1 To 16) As Integer
End Type

'********************* Functions available in the LEAD Addon Toolkit *****************


' Functions in the LTKRN DLL
Declare Function L_ClearNegativePixels Lib "LTKRN13N" (hBitmap As LEADBitmapHandle) As Long
Declare Function L_ColorResBitmapList Lib "LTKRN13N" (ByVal hList&, ByVal nBitsPerPixel&, ByVal uFlags&, pPalette&, ByVal hPalette&, ByVal uColors&) As Long
Declare Function L_CopyBitmapListItems Lib "LTKRN13N" (ByRef phList&, ByVal hList&, ByVal uIndex&, ByVal uCount&) As Long
Declare Function L_MoveBitmapListItems Lib "LTKRN13N" (ByRef phList&, ByVal hList&, ByVal uIndex&, ByVal uCount&) As Long
Declare Function L_CreateBitmapList Lib "LTKRN13N" (ByRef phList&) As Long
Declare Function L_DeleteBitmapListItems Lib "LTKRN13N" (ByVal hList&, ByVal uIndex&, ByVal uCount&) As Long
Declare Function L_DestroyBitmapList Lib "LTKRN13N" (ByVal hList&) As Long
Declare Function L_GetBitmapAlpha Lib "LTKRN13N" (ByRef pBitmap As LEADBitmapHandle, ByRef pAlpha As LEADBitmapHandle) As Long
Declare Function L_GetBitmapListCount Lib "LTKRN13N" (ByVal hList&, ByRef puCount&) As Long
Declare Function L_GetBitmapListItem Lib "LTKRN13N" (ByVal hList&, ByVal uIndex&, ByRef pBitmap As LEADBitmapHandle) As Long
Declare Function L_InsertBitmapListItem Lib "LTKRN13N" (ByVal hList&, ByVal uIndex&, ByRef pBitmap As LEADBitmapHandle) As Long
Declare Function L_RemoveBitmapListItem Lib "LTKRN13N" (ByVal hList&, ByVal uIndex&, ByRef pBitmap As LEADBitmapHandle) As Long
Declare Function L_SetBitmapAlpha Lib "LTKRN13N" (ByRef pBitmap As LEADBitmapHandle, ByRef pAlpha As LEADBitmapHandle) As Long
Declare Function L_SetBitmapDataPointer Lib "LTKRN13N" (hBitmap As LEADBitmapHandle, ByVal pData$, ByVal dwSize&) As Integer
Declare Function L_SetBitmapListItem Lib "LTKRN13N" (ByVal hList&, ByVal uIndex&, ByRef pBitmap As LEADBitmapHandle) As Long
Declare Function L_TranslateBitmapColor Lib "LTKRN13N" (ByRef pBitmapDst As LEADBitmapHandle, ByRef pBitmapSrc As LEADBitmapHandle, ByVal crColor&) As Long
Declare Function L_TrimBitmap Lib "LTKRN13N" (hBitmap As LEADBitmapHandle, ByVal nCol&, ByVal nRow&, ByVal uWidth&, ByVal uHeight&) As Long
Declare Function L_CompressRow Lib "LTKRN13N" (ByRef pRunBuffer As Long, ByVal pBuffer$, ByVal nCol&, ByVal nWidth&) As Long
Declare Function L_CompressRows Lib "LTKRN13N" (ByRef pRunBuffer As Long, ByVal pBuffer$, ByVal nWidth&, ByVal nRows&) As Long
Declare Function L_ExpandRow Lib "LTKRN13N" (ByRef pRunBuffer As Long, ByVal pBuffer$, ByVal nCol&, ByVal nWidth&) As Long
Declare Function L_ExpandRows Lib "LTKRN13N" (ByRef pRunBuffer As Long, ByVal pBuffer$, ByVal nWidth&, ByVal nRows&) As Long
Declare Function L_GetBitmapRowCompressed Lib "LTKRN13N" (pBitmap As LEADBitmapHandle, ByVal pWorkBuffer$, ByRef pRunBuffer As Long, ByVal nRow&, ByVal nLines&) As Long
Declare Function L_GetBitmapRowColCompressed Lib "LTKRN13N" (pBitmap As LEADBitmapHandle, ByVal pWorkBuffer$, ByRef pRunBuffer As Long, ByVal nRow&, ByVal nCol&, ByVal uWidth&) As Long
Declare Function L_PutBitmapRowCompressed Lib "LTKRN13N" (pBitmap As LEADBitmapHandle, ByVal pWorkBuffer$, ByRef pRunBuffer As Long, ByVal nRow&, ByVal nLines&) As Long
Declare Function L_PutBitmapRowColCompressed Lib "LTKRN13N" (pBitmap As LEADBitmapHandle, ByVal pWorkBuffer$, ByRef pRunBuffer As Long, ByVal nRow&, ByVal nCol&, ByVal uWidth&) As Long
Declare Sub L_AccessBitmap Lib "LTKRN13N" (hBitmap As LEADBitmapHandle)
Declare Function L_AllocateBitmap Lib "LTKRN13N" (hBitmap As LEADBitmapHandle, ByVal nMemType&) As Long
Declare Function L_ChangeBitmapHeight Lib "LTKRN13N" (hBitmap As LEADBitmapHandle, ByVal nHeight&) As Long
Declare Function L_ChangeBitmapViewPerspective Lib "LTKRN13N" (hBitmapDst As LEADBitmapHandle, hBitmapSrc As LEADBitmapHandle, ByVal nViewPerspective&) As Long
Declare Function L_ChangeFromDIB Lib "LTKRN13N" (hBitmap As LEADBitmapHandle, ByVal hDIB&) As Long
Declare Function L_ChangeToDIB Lib "LTKRN13N" (hBitmap As LEADBitmapHandle) As Long
Declare Function L_ClearBitmap Lib "LTKRN13N" (hBitmap As LEADBitmapHandle) As Long
Declare Function L_ColorResBitmap Lib "LTKRN13N" (hBitmapSrc As LEADBitmapHandle, hBitmapDst As LEADBitmapHandle, ByVal nBits&, ByVal uFlags&, pPal&, ByVal hPalette&, ByVal uColors&, ByVal pCallback&, ByVal pUserData&) As Long
Declare Function L_CombineBitmap Lib "LTKRN13N" (hBitmapDst As LEADBitmapHandle, ByVal nXDst%, ByVal nYDst%, ByVal nWidth%, ByVal nHeight%, hBitmapSrc As LEADBitmapHandle, _
                                                 ByVal nXSrc%, ByVal nYSrc%, ByVal uFlags&) As Long
Declare Function L_ConvertBuffer Lib "LTKRN13N" (pBuf$, ByVal pWidth&, ByVal BPPSrc&, ByVal BPPDst&, ByVal OrderSrc&, ByVal OrderDst&, pPalSrc&, pPalDst&) As Long
Declare Function L_ConvertBufferExt Lib "LTKRN13N" (pBuf$, ByVal pWidth&, ByVal BPPSrc&, ByVal BPPDst&, ByVal OrderSrc%, ByVal OrderDst&, pPalSrc&, pPalDst&, _
                                                    ByVal uFlags&, ByVal uLowBit&, ByVal uHighBit&) As Long
Declare Function L_ConvertFromDIB Lib "LTKRN13N" (hBitmap As LEADBitmapHandle, lpbmiBitmap As BITMAPINFO, pData$) As Long
Declare Function L_ConvertToDIB Lib "LTKRN13N" (hBitmap As LEADBitmapHandle) As Long
Declare Function L_CopyBitmap Lib "LTKRN13N" (hBitmapDst As LEADBitmapHandle, hBitmapSrc As LEADBitmapHandle) As Long
Declare Function L_CopyBitmapData Lib "LTKRN13N" (hBitmapDst As LEADBitmapHandle, hBitmapSrc As LEADBitmapHandle) As Long
Declare Sub L_CopyBitmapHandle Lib "LTKRN13N" (hBitmapDst As LEADBitmapHandle, hBitmapSrc As LEADBitmapHandle)
Declare Function L_CopyBitmapRect Lib "LTKRN13N" (hBitmapDst As LEADBitmapHandle, hBitmapSrc As LEADBitmapHandle, ByVal nXPos&, ByVal nYPos&, ByVal nWidth&, ByVal nHeight&) As Long
Declare Function L_CreateBitmap Lib "LTKRN13N" (hBitmap As LEADBitmapHandle, ByVal uMemory&, ByVal uWidth&, ByVal uHeight&, ByVal uBits&, ByVal uOrder&, pPal&, ByVal uViewPerspective&, ByVal pData&, ByVal dwSize&) As Long
Declare Function L_CreateLeadDC Lib "LTKRN13N" (hBitmap As LEADBitmapHandle) As Long
Declare Function L_CreateUserMatchTable Lib "LTKRN13N" (pPal&, ByVal uColors&) As Long
Declare Function L_DefaultDithering Lib "LTKRN13N" (ByVal uMethod&) As Long
Declare Function L_DeleteLeadDC Lib "LTKRN13N" (ByVal hDC&) As Long
Declare Function L_DitherLine Lib "LTKRN13N" (hBitmap As LEADBitmapHandle, pBufSrc$, pBufDst$) As Long
Declare Function L_DupPalette Lib "LTKRN13N" (ByVal hPalette&) As Long
Declare Function L_FillBitmap Lib "LTKRN13N" (hBitmap As LEADBitmapHandle, ByVal crFill&) As Long
Declare Function L_FlipBitmap Lib "LTKRN13N" (hBitmap As LEADBitmapHandle) As Long
Declare Function L_FlipBitmapViewPerspective Lib "LTKRN13N" (hBitmap As LEADBitmapHandle) As Long
Declare Sub L_FreeBitmap Lib "LTKRN13N" (hBitmap As LEADBitmapHandle)
Declare Function L_FreeUserMatchTable Lib "LTKRN13N" (pTableRef&) As Long
Declare Function L_GetBitmapColors Lib "LTKRN13N" (hBitmap As LEADBitmapHandle, ByVal nIndex&, ByVal nCount&, pPal&) As Long

'Declare Function L_GetBitmapRow Lib "LTKRN13N" (hBitmap As LEADBitmapHandle, ByVal pBuf$, ByVal nRow&, ByVal nNumberOfBytes&) As Long
Declare Function L_GetBitmapRow Lib "LTKRN13N" (hBitmap As LEADBitmapHandle, ByVal pBuff As Long, ByVal nRow&, ByVal nNumberOfBytes&) As Long

Declare Function L_GetBitmapRowCol Lib "LTKRN13N" (hBitmap As LEADBitmapHandle, ByVal pBuf$, ByVal nRow&, ByVal nCol&, ByVal nNumberOfBytes&) As Long
Declare Function L_GetFixedPalette Lib "LTKRN13N" (pPal&, ByVal nBits&) As Long
Declare Function L_GetPixelColor Lib "LTKRN13N" (hBitmap As LEADBitmapHandle, ByVal nRow&, ByVal nCol&) As Long
Declare Function L_GrayScaleBitmap Lib "LTKRN13N" (hBitmap As LEADBitmapHandle, ByVal nBits&) As Long
Declare Function L_InitBitmap Lib "LTKRN13N" (hBitmap As LEADBitmapHandle, ByVal nWidth&, ByVal nHeight&, ByVal nBits&) As Long
Declare Function L_IsGrayScaleBitmap Lib "LTKRN13N" (hBitmap As LEADBitmapHandle) As Long
Declare Function L_IsSupportLocked Lib "LTKRN13N" (ByVal uType&) As Long
Declare Function L_PointFromBitmap Lib "LTKRN13N" (hBitmap As LEADBitmapHandle, ByVal nViewPerspective&, nX&, nY&) As Long
Declare Function L_PointToBitmap Lib "LTKRN13N" (hBitmap As LEADBitmapHandle, ByVal nViewPerspective&, nX&, nY&) As Long
Declare Function L_PutBitmapColors Lib "LTKRN13N" (hBitmap As LEADBitmapHandle, ByVal nIndex&, ByVal nCount&, pPal&) As Long
Declare Function L_PutBitmapRow Lib "LTKRN13N" (hBitmap As LEADBitmapHandle, ByVal pBuf$, ByVal nRow&, ByVal uBytes&) As Long
Declare Function L_PutBitmapRowCol Lib "LTKRN13N" (hBitmap As LEADBitmapHandle, ByVal pBuf$, ByVal nRow&, ByVal nCol&, ByVal uBytes&) As Long
Declare Function L_PutPixelColor Lib "LTKRN13N" (hBitmap As LEADBitmapHandle, ByVal nRow&, ByVal nCol&, ByVal crFill&) As Long
Declare Function L_RectFromBitmap Lib "LTKRN13N" (hBitmap As LEADBitmapHandle, ByVal nViewPerspective&, pRect As RECT) As Long
Declare Function L_RectToBitmap Lib "LTKRN13N" (hBitmap As LEADBitmapHandle, ByVal nViewPerspective&, pRect As RECT) As Long
Declare Sub L_RedirectIO Lib "LTKRN13N" (ByVal pfnOpenCallback&, ByVal pfnReadCallback&, ByVal pfnWriteCallback&, ByVal pfnSeekCallback&, ByVal pfnCloseCallback&, ByVal pUserData&)
Declare Sub L_ReleaseBitmap Lib "LTKRN13N" (hBitmap As LEADBitmapHandle)
Declare Function L_Resize Lib "LTKRN13N" (pBuf$, ByVal CurrentRow&, ByVal nBits&, pXSize&, pYSize&, pResizeData As RESIZEDATA) As Long
Declare Function L_ResizeBitmap Lib "LTKRN13N" (hBitmapSrc As LEADBitmapHandle, hBitmapDst As LEADBitmapHandle) As Long
Declare Function L_ReverseBitmap Lib "LTKRN13N" (hBitmap As LEADBitmapHandle) As Long
Declare Function L_ReverseBitmapViewPerspective Lib "LTKRN13N" (hBitmap As LEADBitmapHandle) As Long
Declare Function L_RotateBitmap Lib "LTKRN13N" (hBitmap As LEADBitmapHandle, ByVal nAngle&, ByVal uFlags&, ByVal crFill&) As Long
Declare Function L_RotateBitmapViewPerspective Lib "LTKRN13N" (hBitmap As LEADBitmapHandle, ByVal nAngle&) As Long
Declare Function L_SetStatusCallBack Lib "LTKRN13N" (ByVal pfnStatusCallback&, ByVal pUserData&) As Long
Declare Function L_GetStatusCallBack Lib "LTKRN13N" (pfnStatusCallback&) As Long
Declare Function L_SetUserMatchTable Lib "LTKRN13N" (pTableRef&) As Long
Declare Function L_ShearBitmap Lib "LTKRN13N" (hBitmap As LEADBitmapHandle, ByVal nAngle&, ByVal fHorizontal&, ByVal crFill&) As Long
Declare Function L_SizeBitmap Lib "LTKRN13N" (hBitmap As LEADBitmapHandle, ByVal nNewWidth&, ByVal nNewHeight&, ByVal nFlags&) As Long
Declare Function L_StartDithering Lib "LTKRN13N" (hBitmap As LEADBitmapHandle, pPal&, ByVal uColors&) As Long
Declare Function L_StartResize Lib "LTKRN13N" (ByVal OldWidth&, ByVal OldHeight&, ByVal NewWidth&, ByVal NewHeight&, ppResizeData&) As Long 'ppResizeData is a pointer to a pointer!
Declare Function L_StopDithering Lib "LTKRN13N" (hBitmap As LEADBitmapHandle) As Long
Declare Function L_StopResize Lib "LTKRN13N" (pResizeData As RESIZEDATA) As Long
Declare Sub L_UnlockSupport Lib "LTKRN13N" (ByVal uType&, ByVal pKey$)
Declare Function L_VersionInfo Lib "LTKRN13N" (VersionInfoStruct As VERSIONINFO) As Long

Declare Function L_ToggleBitmapCompression Lib "LTKRN13N" (hBitmap As LEADBitmapHandle) As Long
Declare Function L_StartResizeBitmap Lib "LTKRN13N" (hBitmap As LEADBitmapHandle, ByVal nNewWidth&, ByVal nNewHeight&, ByVal nNewBits&, ByRef pPalette&, ByVal nColors&, _
                             ByVal uFlags&, ByVal pfnCallback&, ByVal pCallbackData&, ByRef pResizeData&) As Long
Declare Function L_GetResizedRowCol Lib "LTKRN13N" (ByVal pResizeData&, ByVal pBuffer$, ByVal nRow&, ByVal nCol&, ByVal uBytes&) As Long
Declare Function L_StopResizeBitmap Lib "LTKRN13N" (ByVal pResizeData&) As Long

Declare Function L_ChangeBitmapCompression Lib "LTKRN13N" (hBitmap As LEADBitmapHandle, ByVal nComp&) As Long
Declare Function L_GetPixelData Lib "LTKRN13N" (hBitmap As LEADBitmapHandle, ByVal pData$, ByVal nRow&, ByVal nCol&, ByVal nBytes&) As Long
Declare Function L_PutPixelData Lib "LTKRN13N" (hBitmap As LEADBitmapHandle, ByVal pData$, ByVal nRow&, ByVal nCol&, ByVal nBytes&) As Long


' functions in LTDIS DLL
Declare Function L_AppendPlayback Lib "LTDIS13N" (ByVal hPlayback&, hBitmap As LEADBitmapHandle) As Long
Declare Function L_CancelPlaybackWait Lib "LTDIS13N" (ByVal hPlayback&) As Long
Declare Function L_ChangeFromDDB Lib "LTDIS13N" (ByVal hDC&, hBitmap As LEADBitmapHandle, ByVal hBitmap&, ByVal hPalette&) As Long
Declare Function L_ChangeToDDB Lib "LTDIS13N" (ByVal hDC&, hBitmap As LEADBitmapHandle) As Long
Declare Function L_ConvertFromDDB Lib "LTDIS13N" (ByVal hDC&, hBitmap As LEADBitmapHandle, ByVal hBitmap&, ByVal hPalette&) As Long
Declare Function L_ConvertToDDB Lib "LTDIS13N" (ByVal hDC&, hBitmap As LEADBitmapHandle) As Long
Declare Function L_ClearPlaybackUpdateRect Lib "LTDIS13N" (ByVal hPlayback%) As Integer
Declare Function L_ClipboardReady Lib "LTDIS13N" () As Long
Declare Function L_ConvertColorSpace Lib "LTDIS13N" (pBufSrc$, pBufDst$, ByVal nWidth&, ByVal nFormatSrc&, ByVal nFormatDst&) As Long
Declare Function L_CopyFromClipboard Lib "LTDIS13N" (ByVal hWnd&, hBitmap As LEADBitmapHandle) As Long
Declare Function L_CopyToClipboard Lib "LTDIS13N" (ByVal hWnd&, hBitmap As LEADBitmapHandle) As Long
Declare Function L_CopyToClipboardExt Lib "LTDIS13N" (ByVal hWnd&, hBitmap As LEADBitmapHandle, ByVal uFlags&) As Long
Declare Function L_CreatePaintPalette Lib "LTDIS13N" (ByVal hDC&, hBitmap As LEADBitmapHandle) As Long
Declare Function L_CreatePlayback Lib "LTDIS13N" (ByRef phPlayback&, ByRef pBitmap As LEADBitmapHandle, ByVal hList&) As Long
Declare Function L_DestroyPlayback Lib "LTDIS13N" (ByVal hPlayback&, ByRef phList&) As Long
Declare Function L_GetDisplayMode Lib "LTDIS13N" () As Long
Declare Function L_GetPaintContrast Lib "LTDIS13N" (hBitmap As LEADBitmapHandle) As Long
Declare Function L_GetPaintGamma Lib "LTDIS13N" (hBitmap As LEADBitmapHandle) As Long
Declare Function L_GetPaintIntensity Lib "LTDIS13N" (hBitmap As LEADBitmapHandle) As Long
Declare Function L_GetPlaybackDelay Lib "LTDIS13N" (ByVal hPlayback&, ByRef puDelay&) As Long
Declare Function L_GetPlaybackIndex Lib "LTDIS13N" (ByVal hPlayback&, ByRef pnIndex&) As Long
Declare Function L_GetPlaybackState Lib "LTDIS13N" (ByVal hPlayback&, ByRef puState&) As Long
Declare Function L_GetPlaybackUpdateRect Lib "LTDIS13N" (ByVal hPlayback&, prcUpdate As RECT, ByVal fClear&) As Long
Declare Function L_PaintDC Lib "LTDIS13N" (ByVal hDC&, hBitmap As LEADBitmapHandle, pSrc As RECT, pClipSrc As RECT, pDst As RECT, pClipDst As RECT, ByVal uROP3&) As Long
Declare Function L_PaintDCBuffer Lib "LTDIS13N" (ByVal hDC&, hBitmap As LEADBitmapHandle, pSrc As RECT, pClipSrc As RECT, pDst As RECT, pClipDst As RECT, ByVal uROP3&, pBuf$, ByVal nRow&, ByVal nCount&) As Long
Declare Function L_PrintBitmap Lib "LTDIS13N" (hBitmap As LEADBitmapHandle, ByVal nXPos&, ByVal nYPos&, ByVal nXSize&, ByVal nYSize&, ByVal nEndDoc&) As Long
Declare Function L_PrintBitmapExt Lib "LTDIS13N" (ByVal hDC&, hBitmap As LEADBitmapHandle, ByVal nXPos&, ByVal nYPos&, ByVal nXSize&, ByVal nYSize&, ByVal fEndDoc&) As Long
Declare Function L_PrintBitmapFast Lib "LTDIS13N" (ByVal hDC&, hBitmap As LEADBitmapHandle, ByVal nXPos&, ByVal nYPos&, ByVal nXSize&, ByVal nYSize&, ByVal fEndDoc&) As Long
Declare Function L_ProcessPlayback Lib "LTDIS13N" (ByVal hPlayback&, ByRef puState&) As Long
Declare Function L_ScreenCaptureBitmap Lib "LTDIS13N" (ByVal hDC&, hBitmap As LEADBitmapHandle, pRect As RECT) As Long
Declare Function L_SetDisplayMode Lib "LTDIS13N" (ByVal uFlagPos&, ByVal uFlagSet&) As Long
Declare Function L_SetPaintContrast Lib "LTDIS13N" (hBitmap As LEADBitmapHandle, ByVal nValue&) As Long
Declare Function L_SetPaintGamma Lib "LTDIS13N" (hBitmap As LEADBitmapHandle, ByVal nValue&) As Long
Declare Function L_SetPaintIntensity Lib "LTDIS13N" (hBitmap As LEADBitmapHandle, ByVal nValue&) As Long
Declare Function L_SetPlaybackIndex Lib "LTDIS13N" (ByVal hPlayback&, ByVal nIndex&) As Long
Declare Function L_UnderlayBitmap Lib "LTDIS13N" (hBitmap As LEADBitmapHandle, hUlayBitmap As LEADBitmapHandle, ByVal uFlags&) As Long
Declare Function L_ValidatePlaybackLines Lib "LTDIS13N" (ByVal hPlayback&, ByVal nRow&, ByVal nLines&) As Long
Declare Function L_WindowLevel Lib "LTDIS13N" (hBitmap As LEADBitmapHandle, ByVal nLowBit&, ByVal nHighBit&, ByVal pLUT$, ByVal nLUTLen&, ByVal uFlags&) As Long
Declare Function L_CreatePanWindow Lib "LTDIS13N" (ByVal hWndParent&, hBitmap As LEADBitmapHandle, ByVal ulDisplayFlags&, ByVal nLeft&, ByVal nTop&, ByVal nWidth&, _
                                                   ByVal nHeight&, ByVal pszClassName$, ByVal hIcon&, ByVal hCursor&, _
                                                   ByVal bSysMenu As Boolean, ByVal pfnPanCallback&, ByVal pUserData&) As Long
Declare Function L_UpdatePanWindow Lib "LTDIS13N" (ByVal hPanWindow&, hBitmap As LEADBitmapHandle, ByVal ulDisplayFlags&, ByVal crPen&, ByVal pszTitle$, prcDst As RECT) As Long
Declare Function L_DestroyPanWindow Lib "LTDIS13N" (ByVal hPanWindow&) As Long
Declare Function L_WindowLevelFillLUT Lib "LTDIS13N" (ByVal pLUT&, ByVal ulLUTLen&, ByVal crStart&, ByVal crEnd&, _
                                                      ByVal nLow&, ByVal nHigh&, ByVal nLowBit&, ByVal nHighBit&, _
                                                      ByVal nMinValue&, ByVal nMaxValue&, ByVal bInside As Boolean) As Long
Declare Function L_ConvertFromWMF Lib "LTDIS13N" (hBitmap As LEADBitmapHandle, ByVal hWmf&, ByVal uWidth&, ByVal uHeight&) As Long
Declare Function L_ChangeFromWMF Lib "LTDIS13N" (hBitmap As LEADBitmapHandle, ByVal hWmf&, ByVal uWidth&, ByVal uHeight&) As Long
Declare Function L_ConvertToWMF Lib "LTDIS13N" (hBitmap As LEADBitmapHandle) As Long
Declare Function L_ChangeToWMF Lib "LTDIS13N" (hBitmap As LEADBitmapHandle) As Long

Declare Function L_ConvertFromEMF Lib "LTDIS13N" (hBitmap As LEADBitmapHandle, ByVal hEmf&, ByVal uWidth&, ByVal uHeight&) As Long
Declare Function L_ChangeFromEMF Lib "LTDIS13N" (hBitmap As LEADBitmapHandle, ByVal hEmf&, ByVal uWidth&, ByVal uHeight&) As Long
Declare Function L_ConvertToEMF Lib "LTDIS13N" (hBitmap As LEADBitmapHandle) As Long
Declare Function L_ChangeToEMF Lib "LTDIS13N" (hBitmap As LEADBitmapHandle) As Long

Declare Function L_StartMagGlass Lib "LTDIS13N" (ByVal hWnd&, hBitmap As LEADBitmapHandle, pRectDst As RECT, ByVal nWidth&, ByVal nHeight&, ByVal nZoom&, _
                                                 ByVal clrPen&, ByVal hMagCursor&, ByVal clrBack&, ByVal bEllipse As Boolean, ByVal nBorderSize&, ByVal b3D As Boolean, _
                                                 ByVal uPaintFlags&, pMask&, ByVal uMaskCount&, ByVal nCrosshair&, ByVal bIgnoreRgn As Boolean, ByVal bCenter As Boolean) As Long


Declare Function L_StartMagGlassExt Lib "LTDIS13N" (ByVal hWnd&, hBitmap As LEADBitmapHandle, pRectDst As RECT, ByVal nWidth&, ByVal nHeight&, ByVal nZoom&, _
                                                    ByVal clrPen&, ByVal hMagCursor&, ByVal clrBack&, ByVal bEllipse As Boolean, ByVal nBorderSize&, ByVal b3D As Boolean, _
                                                    ByVal uPaintFlags&, pMask&, ByVal uMaskCount&, ByVal uMagGlassFlags&, _
                                                    ByVal nCrosshair&, ByVal bIgnoreRgn As Boolean, ByVal bCenter As Boolean, ByVal pfnCallback&, ByVal pUserData&) As Long

Declare Function L_StopMagGlass Lib "LTDIS13N" (ByVal hWnd&) As Long
Declare Function L_UpdateMagGlassRect Lib "LTDIS13N" (ByVal hWnd&, prcDst As RECT) As Long
Declare Function L_UpdateMagGlassPaintFlags Lib "LTDIS13N" (ByVal hWnd&, ByVal uPaintFlags&) As Long
Declare Function L_UpdateMagGlassShape Lib "LTDIS13N" (ByVal hWnd&, ByVal uMagGlassShape&, ByVal hMagGlassRgn&) As Long
Declare Function L_UpdateMagGlassExt Lib "LTDIS13N" (ByVal hWnd&, ByVal pColor&, ByVal pMaskPlane&, ByVal nMaskPlaneStart&, ByVal nMaskPlaneEnd&, ByVal bUpdateBitmap&) As Long
Declare Function L_WindowHasMagGlass Lib "LTDIS13N" (ByVal hWnd&) As Long
Declare Function L_GetBitmapClipSegments Lib "LTDIS13N" (hBitmap As LEADBitmapHandle, ByVal nRow&, ByVal pSegmentBuffer&, ByVal puSegmentCount&) As Long
Declare Function L_GetBitmapClipSegmentsMax Lib "LTDIS13N" (hBitmap As LEADBitmapHandle, ByVal puMaxSegments&) As Long

' Region processing functions

Declare Function L_BitmapHasRgn Lib "LTDIS13N" (pBitmap As LEADBitmapHandle) As Long
Declare Function L_ColorBitmapRgn Lib "LTDIS13N" (ByVal hDC&, pBitmap As LEADBitmapHandle, pXForm As RGNXFORM, ByVal crColor&) As Long
Declare Function L_CreateMaskFromBitmapRgn Lib "LTDIS13N" (pBitmap As LEADBitmapHandle, pMask As LEADBitmapHandle) As Long
Declare Function L_FrameBitmapRgn Lib "LTDIS13N" (ByVal hDevice&, pBitmap As LEADBitmapHandle, pXForm As RGNXFORM, ByVal uType&) As Long
Declare Function L_FreeBitmapRgn Lib "LTDIS13N" (pBitmap As LEADBitmapHandle) As Long
Declare Function L_GetBitmapRgnArea Lib "LTDIS13N" (pBitmap As LEADBitmapHandle, puArea&) As Long
Declare Function L_GetBitmapRgnBounds Lib "LTDIS13N" (pBitmap As LEADBitmapHandle, pXForm As RGNXFORM, pRect As RECT) As Long
Declare Function L_GetBitmapRgnHandle Lib "LTDIS13N" (pBitmap As LEADBitmapHandle, pXForm As RGNXFORM, phRgn&) As Long
Declare Function L_IsPtInBitmapRgn Lib "LTDIS13N" (pBitmap As LEADBitmapHandle, ByVal nRow&, ByVal nCol&) As Long
Declare Function L_OffsetBitmapRgn Lib "LTDIS13N" (pBitmap As LEADBitmapHandle, ByVal nRowOffset&, ByVal nColOffset&) As Long
Declare Function L_PaintRgnDC Lib "LTDIS13N" (ByVal hDevice&, lpBitmap As LEADBitmapHandle, pSrc As RECT, pClipSrc As RECT, pDst As RECT, pClipDst As RECT, ByVal uROP3&) As Long
Declare Function L_PaintRgnDCBuffer Lib "LTDIS13N" (ByVal hDC&, lpBitmap As LEADBitmapHandle, pSrc As RECT, pClipSrc As RECT, pDst As RECT, pClipDst As RECT, ByVal uROP3&, ByVal lpBuffer&, ByVal nRow&, ByVal nCount&) As Long
Declare Function L_SetBitmapRgnColor Lib "LTDIS13N" (pBitmap As LEADBitmapHandle, ByVal crColor&, ByVal uCombineMode&) As Long
Declare Function L_SetBitmapRgnEllipse Lib "LTDIS13N" (pBitmap As LEADBitmapHandle, pXForm As RGNXFORM, pRect As RECT, ByVal uCombineMode&) As Long
Declare Function L_SetBitmapRgnFromMask Lib "LTDIS13N" (pBitmap As LEADBitmapHandle, pXForm As RGNXFORM, pMask As LEADBitmapHandle, ByVal uCombineMode&) As Long
Declare Function L_SetBitmapRgnHandle Lib "LTDIS13N" (pBitmap As LEADBitmapHandle, pXForm As RGNXFORM, ByVal hRGN&, ByVal uCombineMode&) As Long
Declare Function L_SetBitmapRgnPolygon Lib "LTDIS13N" (pBitmap As LEADBitmapHandle, pXForm As RGNXFORM, pPoints As POINT, ByVal uPoints&, ByVal uFillMode&, ByVal uCombineMode&) As Long
Declare Function L_SetBitmapRgnRect Lib "LTDIS13N" (pBitmap As LEADBitmapHandle, pXForm As RGNXFORM, pRect As RECT, ByVal uCombineMode&) As Long
Declare Function L_SetBitmapRgnRoundRect Lib "LTDIS13N" (pBitmap As LEADBitmapHandle, pXForm As RGNXFORM, pRect As RECT, ByVal nWidthEllipse&, ByVal nHeightEllipse&, ByVal uCombineMode&) As Long



' Functions in LTFIL DLL
Declare Function L_IgnoreFilters Lib "LTFIL13N" (ByVal pFilters$) As Long
Declare Function L_PreLoadFilters Lib "LTFIL13N" (ByVal nFixed&, ByVal nCached&, ByVal pFilters$) As Long
Declare Function L_CompressBuffer Lib "LTFIL13N" (pBuffer$) As Long
Declare Function L_DeletePage Lib "LTFIL13N" (ByVal pFileName$, ByVal nPage&, ByVal uFlags&, pSaveOptions As SAVEFILEOPTION) As Long
Declare Function L_EndCompressBuffer Lib "LTFIL13N" () As Long
Declare Function L_ReadLoadResolutions Lib "LTFIL13N" (ByVal pszFile$, ByRef pDimensions, ByRef pDimensionCount&, pLoadOptions As LOADFILEOPTION) As Long
Declare Function L_FeedLoad Lib "LTFIL13N" (ByVal hLoad&, ByVal pBuffer&, ByVal dwBufferSize&) As Long
Declare Function L_FileConvert Lib "LTFIL13N" (ByVal pFileSrc$, ByVal pFileDst$, ByVal nFormat&, ByVal nNewWidth&, ByVal nNewHeight&, ByVal nNewBits&, ByVal QFactor&, pLoadOptions As LOADFILEOPTION, pSaveOptions As SAVEFILEOPTION, pFileInfo As FileInfo) As Long
Declare Function L_FileInfo Lib "LTFIL13N" (ByVal pFile$, pFileInfo As FileInfo, ByVal uFlags&, pLoadOptions As LOADFILEOPTION) As Long
Declare Function L_FileInfoMemory Lib "LTFIL13N" (ByVal pMem$, pFileInfo As FileInfo, ByVal nSizeOfFile&, ByVal uFlags&, pLoadOptions As LOADFILEOPTION) As Long
Declare Function L_GetComment Lib "LTFIL13N" (ByVal uType&, pBuf$, ByVal uLength&) As Long
Declare Function L_GetCompressFileStamp Lib "LTFIL13N" (ByVal pFile$, hBitmap As LEADBitmapHandle, pLoadOptions As LOADFILEOPTION) As Long
Declare Function L_GetLoadResolution Lib "LTFIL13N" (ByVal nFormat&, pWidth&, pHeight&, pLoadOptions As LOADFILEOPTION) As Long
Declare Function L_GetPCDResolution Lib "LTFIL13N" (ByVal pFile$, pPCDInfo As PCDINFO) As Long
Declare Function L_GetTag Lib "LTFIL13N" (ByVal uTag&, pType&, pCount&, pData&) As Long
Declare Function L_GetWMFResolution Lib "LTFIL13N" (lpResolution&) As Long
Declare Function L_LoadBitmap Lib "LTFIL13N" (ByVal pFile$, hBitmap As LEADBitmapHandle, ByVal nBits&, ByVal nOrder&, pLoadOptions As LOADFILEOPTION, pFileInfo As FileInfo) As Long
Declare Function L_LoadBitmapMemory Lib "LTFIL13N" (pMem$, hBitmap As LEADBitmapHandle, ByVal nBits&, ByVal nOrder&, ByVal nMemSize&, pLoadOptions As LOADFILEOPTION, pFileInfo As FileInfo) As Long
Declare Function L_LoadBitmapList Lib "LTFIL13N" (ByVal lpszFile$, ByVal phList&, ByVal nBitsTo&, ByVal nColorOrder&, pLoadOptions As LOADFILEOPTION, pFileInfo As FileInfo) As Long
Declare Function L_LoadFile Lib "LTFIL13N" (ByVal pFile$, hBitmap As LEADBitmapHandle, ByVal nBits&, ByVal nOrder&, ByVal uFlags&, ByVal pCallback&, ByVal pUserData&, pLoadOptions As LOADFILEOPTION, pFileInfo As FileInfo) As Long 'pCallBack and pUserData should be 0
Declare Function L_LoadFileOffset Lib "LTFIL13N" (ByVal fd&, ByVal nOffsetBegin&, ByVal nBytesToLoad&, hBitmap As LEADBitmapHandle, ByVal nBits&, ByVal nOrder&, ByVal uFlags&, ByVal pCallback&, ByVal pUserData&, pLoadOptions As LOADFILEOPTION, pFileInfo As FileInfo) As Long
Declare Function L_ReadFileComment Lib "LTFIL13N" (ByVal pFile$, ByVal uType&, pBuf$, ByVal uLength&, pLoadOptions As LOADFILEOPTION) As Long
Declare Function L_ReadFileCommentMemory Lib "LTFIL13N" (ByVal pBuffer$, ByVal uType&, pBuf$, ByVal uLength&, ByVal nBuffSize&, pLoadOptions As LOADFILEOPTION) As Long
Declare Function L_ReadFileTag Lib "LTFIL13N" (ByVal pFile$, ByVal uTag&, pType&, pCount&, ByVal pData&, pLoadOptions As LOADFILEOPTION) As Long
Declare Function L_ReadFileTagMemory Lib "LTFIL13N" (ByVal pBuffer$, ByVal uTag&, pType&, pCount&, ByVal pData&, ByVal nBuffSize&, pLoadOptions As LOADFILEOPTION) As Long
Declare Function L_SaveBitmap Lib "LTFIL13N" (ByVal pFile$, hBitmap As LEADBitmapHandle, ByVal nFormat&, ByVal nBits&, ByVal nQFactor&, pSaveOptions As SAVEFILEOPTION) As Long
Declare Function L_SaveBitmapList Lib "LTFIL13N" (ByVal lpszFile$, ByVal hList&, ByVal nFormat&, ByVal nBits&, ByVal nQFactor&, pSaveOptions As SAVEFILEOPTION) As Long
Declare Function L_SaveBitmapMemory Lib "LTFIL13N" (pMemHandle&, hBitmap As LEADBitmapHandle, ByVal nFormat&, ByVal nBits&, ByVal nQFactor&, uSize&, pSaveOptions As SAVEFILEOPTION) As Long
Declare Function L_SaveFile Lib "LTFIL13N" (ByVal pFile$, hBitmap As LEADBitmapHandle, ByVal nFormat&, ByVal nBits&, ByVal nQFactor&, ByVal uFlags&, ByVal pCallback&, ByVal pUserData, pSaveOptions As SAVEFILEOPTION) As Long 'pCallBack and pUserData should be 0
Declare Function L_SaveFileMemory Lib "LTFIL13N" (pMemHandle&, hBitmap As LEADBitmapHandle, ByVal nFormat&, ByVal nBits&, ByVal nQFactor&, ByVal uFlags&, ByVal pCallback&, ByVal pUserData, ByVal nBuffSize&, pSaveOptions As SAVEFILEOPTION) As Integer 'pCallBack and pUserData should be 0
Declare Function L_SaveFileOffset Lib "LTFIL13N" (ByVal fd&, ByVal nOffsetBegin&, nSizeWritten&, hBitmap As LEADBitmapHandle, ByVal nFormat&, ByVal nBits&, ByVal nQFactor&, ByVal uFlags&, ByVal pCallback&, ByVal pUserData&, pSaveOptions As SAVEFILEOPTION) As Long
Declare Function L_SetComment Lib "LTFIL13N" (ByVal uType&, ByVal pBuf$, ByVal uLength&) As Long
Declare Function L_SetLoadInfoCallback Lib "LTFIL13N" (ByVal pfnCallback&, ByVal pUserData&) As Long
Declare Function L_SetPCDResolution Lib "LTFIL13N" (ByVal nRes&) As Long
Declare Function L_SetTag Lib "LTFIL13N" (ByVal uTag&, pType&, pCount&, pData&) As Long
Declare Function L_SetWMFResolution Lib "LTFIL13N" (ByVal nResolution&) As Long
Declare Function L_StartCompressBuffer Lib "LTFIL13N" (pBitmap As LEADBitmapHandle, ByVal pfnCallback&, ByVal uInputBytes&, ByVal uOutputBytes&, ByVal pOutputBuffer&, ByVal nOutputType&, ByVal nQFactor&, ByVal pUserData&) As Long
Declare Function L_StartFeedLoad Lib "LTFIL13N" (pBitmap As LEADBitmapHandle, ByVal nBitsPerPixel&, ByVal nOrder&, ByVal uFlags&, ByVal pfnCallback&, ByVal pUserData&, phLoad&, pFileInfo As FileInfo) As Long
Declare Function L_StopFeedLoad Lib "LTFIL13N" (ByVal hLoad&) As Long
Declare Function L_WriteFileStamp Lib "LTFIL13N" (ByVal pszFileName$, pBitmap As LEADBitmapHandle) As Long
Declare Function L_ReadFileStamp Lib "LTFIL13N" (ByVal pszFileName$, pBitmap As LEADBitmapHandle, pLoadOptions As LOADFILEOPTION) As Long

Declare Function L_ReadFileTransforms Lib "LTFIL13N" (ByVal pszFile$, ByVal pTransforms&, pLoadOptions As LOADFILEOPTION) As Long
Declare Function L_WriteFileTransforms Lib "LTFIL13N" (ByVal pszFile$, ByVal pTransforms&, ByVal nFlags&, pSaveOptions As SAVEFILEOPTION) As Long
Declare Function L_GetFileCommentSize Lib "LTFIL13N" (ByVal pszFile$, ByVal uType&, uLength&, pLoadOptions As LOADFILEOPTION) As Long

Declare Function L_GetSaveResolution Lib "LTFIL13N" (puCount&, ByVal pResolutions&) As Long
Declare Function L_SetLoadResolution Lib "LTFIL13N" (ByVal nFormat&, ByVal nWidth&, ByVal nHeight&) As Long

Declare Function L_2DSetViewport Lib "LTFIL13N" (ByVal nWidth&, ByVal nHeight&) As Long
Declare Function L_2DGetViewport Lib "LTFIL13N" (nWidth&, nHeight&) As Long
Declare Function L_2DSetViewMode Lib "LTFIL13N" (ByVal nViewMode&) As Long
Declare Function L_2DGetViewMode Lib "LTFIL13N" () As Long

Declare Function L_LoadBitmapResize Lib "LTFIL13N" (ByVal pszFile$, hSmallBitmap As LEADBitmapHandle, ByVal nDestWidth, ByVal nDestHeight, ByVal nDestBits, _
                                                    ByVal uFlags, ByVal nOrder&, ByRef LoadOptions As LOADFILEOPTION, FileInfo As FileInfo) As Long
Declare Function L_SaveBitmapBuffer Lib "LTFIL13N" (ByVal pBuffer&, ByVal uInitialBufferSize&, ByVal puFinalFileSize&, hBitmap As LEADBitmapHandle, _
                                                    ByVal nFormat&, ByVal nBitsPerPixel&, ByVal nQFactor&, ByVal pfnSaveBufferCB&, ByVal lpUserData&, _
                                                    ByRef SaveOptions As SAVEFILEOPTION) As Long
Declare Function L_SaveFileBuffer Lib "LTFIL13N" (ByVal pBuffer$, ByVal uInitialBufferSize&, ByVal puFinalFileSize&, hBitmap As LEADBitmapHandle, ByVal nFormat&, _
                                                  ByVal nBitsPerPixel&, ByVal nQFactor&, ByVal uFlags&, ByVal pfnFileSaveCB&, ByVal pfnSaveBufferCB&, _
                                                  ByVal lpUserData&, ByRef SaveOptions As SAVEFILEOPTION) As Long

Declare Function L_GetDefaultLoadFileOption Lib "LTFIL13N" (ByRef pOption As LOADFILEOPTION, ByVal uSize&) As Long
Declare Function L_GetDefaultSaveFileOption Lib "LTFIL13N" (ByRef pOption As SAVEFILEOPTION, ByVal uSize&) As Long
Declare Function L_VecLoadFile Lib "LTFIL13N" (ByVal pszFile$, ByVal pVector&, ByRef LoadOptions As LOADFILEOPTION, FileInfo As FileInfo) As Long
Declare Function L_VecLoadMemory Lib "LTFIL13N" (ByVal pBuffer&, ByVal pVector&, ByVal nBufferSize&, ByRef LoadOptions As LOADFILEOPTION, FileInfo As FileInfo) As Long
Declare Function L_VecStartFeedLoad Lib "LTFIL13N" (ByVal pVector&, ByVal phLoad&, ByRef LoadOptions As LOADFILEOPTION, FileInfo As FileInfo) As Long
Declare Function L_VecFeedLoad Lib "LTFIL13N" (ByVal hLoad&, ByVal pInBuffer&, ByVal dwBufferSize&) As Long
Declare Function L_VecStopFeedLoad Lib "LTFIL13N" (ByVal hLoad&) As Long
Declare Function L_VecSaveFile Lib "LTFIL13N" (ByVal pszFile$, ByVal pVector&, ByVal nFormat&, ByRef SaveOptions As SAVEFILEOPTION) As Long
Declare Function L_VecSaveMemory Lib "LTFIL13N" (ByVal hHandle&, ByVal pVector&, ByVal nFormat&, ByVal uSize&, ByRef SaveOptions As SAVEFILEOPTION) As Long
Declare Function L_WriteFileTag Lib "LTFIL13N" (ByVal pszFile$, ByRef SaveOptions As SAVEFILEOPTION) As Long
Declare Function L_WriteFileComment Lib "LTFIL13N" (ByVal pszFile$, ByRef SaveOptions As SAVEFILEOPTION) As Long
Declare Function L_DocLoadFile Lib "LTFIL13N" (ByVal pszFile$, ByVal pDocument&, ByRef LoadOptions As LOADFILEOPTION) As Long
Declare Function L_DocLoadMemory Lib "LTFIL13N" (ByVal pBuffer$, ByVal pDocument&, ByVal nBufferSize&, ByRef LoadOptions As LOADFILEOPTION) As Long
Declare Function L_DocStartFeedLoad Lib "LTFIL13N" (ByVal pDocument&, ByVal phLoad&, ByRef LoadOptions As LOADFILEOPTION) As Long
Declare Function L_DocFeedLoad Lib "LTFIL13N" (ByVal hLoad&, ByVal pInBuffer&, ByVal dwBufferSize&) As Long
Declare Function L_DocStopFeedLoad Lib "LTFIL13N" (ByVal hLoad&) As Long
Declare Function L_DocSaveFile Lib "LTFIL13N" (ByVal pszFile&, ByVal pDocument&, ByVal nFormat&, ByRef SaveOptions As SAVEFILEOPTION) As Long
Declare Function L_DocSaveMemory Lib "LTFIL13N" (ByVal hHandle&, ByVal pDocument&, ByVal nFormat&, ByVal uSize&, ByRef SaveOptions As SAVEFILEOPTION) As Long
Declare Function L_GetPLTOptions Lib "LTFIL13N" (FilePltOpt As FILEPLTOPTIONS) As Long
Declare Function L_SetPLTOptions Lib "LTFIL13N" (FilePltOpt As FILEPLTOPTIONS) As Long
Declare Function L_CreateThumbnailFromFile Lib "LTFIL13N" (ByVal pszFile$, hBitmap As LEADBitmapHandle, ThumbOptions As ThumbOptions, ByVal pfnCallback&, _
                                                           ByVal pUserData&, ByRef LoadOptions As LOADFILEOPTION, FileInfo As FileInfo) As Long
Declare Function L_GetPDFOptions Lib "LTFIL13N" (FilePDFOpt As FILEPDFOPTIONS, ByVal nSize&) As Long
Declare Function L_SetPDFOptions Lib "LTFIL13N" (FilePDFOpt As FILEPDFOPTIONS) As Long
Declare Function L_GetJ2KOptions Lib "LTFIL13N" (Options As FILEJ2KOPTIONS, ByVal nSize&) As Long
Declare Function L_GetDefaultJ2KOptions Lib "LTFIL13N" (Options As FILEJ2KOPTIONS, ByVal nSize&) As Long
Declare Function L_SetJ2KOptions Lib "LTFIL13N" (Options As FILEJ2KOPTIONS) As Long

' Functions in LTIMG DLL
Declare Function L_GetMinMaxBits Lib "LTIMG13N" (hBitmap As LEADBitmapHandle, LowBit As Long, HighBit As Long) As Long
Declare Function L_GetMinMaxVal Lib "LTIMG13N" (hBitmap As LEADBitmapHandle, MinVal As Long, MaxVal As Long) As Long
Declare Function L_WindowLevelBitmap Lib "LTIMG13N" (hBitmap As LEADBitmapHandle, ByVal nLowBit&, ByVal nHighBit&, ByVal pLUT$, ByVal nLUTLen&, ByVal OrderDst&) As Long
Declare Function L_AddBitmapNoise Lib "LTIMG13N" (hBitmap As LEADBitmapHandle, ByVal uRange&, ByVal uChannel&) As Long
Declare Function L_AutoTrimBitmap Lib "LTIMG13N" (hBitmap As LEADBitmapHandle, ByVal uThreshold&) As Long
Declare Function L_AverageFilterBitmap Lib "LTIMG13N" (hBitmap As LEADBitmapHandle, ByVal uDim&) As Long
Declare Function L_BinaryFilterBitmap Lib "LTIMG13N" (hBitmap As LEADBitmapHandle, pFilter As BINARYFLT) As Long
Declare Function L_ChangeBitmapContrast Lib "LTIMG13N" (hBitmap As LEADBitmapHandle, ByVal nChange&) As Long
Declare Function L_ChangeBitmapHue Lib "LTIMG13N" (hBitmap As LEADBitmapHandle, ByVal nAngle&) As Long
Declare Function L_ChangeBitmapIntensity Lib "LTIMG13N" (hBitmap As LEADBitmapHandle, ByVal nChange&) As Long
Declare Function L_ChangeBitmapSaturation Lib "LTIMG13N" (hBitmap As LEADBitmapHandle, ByVal nChange&) As Long
Declare Function L_ColorMergeBitmap Lib "LTIMG13N" (hBitmap As LEADBitmapHandle, ByVal hBitmaps As Long, ByVal uFlags&) As Long
Declare Function L_ColorSeparateBitmap Lib "LTIMG13N" (hBitmap As LEADBitmapHandle, ByVal hBitmaps As Long, ByVal uFlags&) As Long
Declare Function L_DeskewBitmap Lib "LTIMG13N" (hBitmap As LEADBitmapHandle, ByRef pnAngle&) As Long
Declare Function L_DespeckleBitmap Lib "LTIMG13N" (hBitmap As LEADBitmapHandle) As Long
Declare Function L_EmbossBitmap Lib "LTIMG13N" (hBitmap As LEADBitmapHandle, ByVal uDirection&, ByVal uDepth&) As Long
Declare Function L_GetAutoTrimRect Lib "LTIMG13N" (hBitmap As LEADBitmapHandle, ByVal uThreshold&, ByRef pRect As RECT) As Long
Declare Function L_GetBitmapColorCount Lib "LTIMG13N" (hBitmap As LEADBitmapHandle, ByRef puCount&) As Long
Declare Function L_GammaCorrectBitmap Lib "LTIMG13N" (hBitmap As LEADBitmapHandle, ByVal uGamma&) As Long
Declare Function L_HistoContrastBitmap Lib "LTIMG13N" (hBitmap As LEADBitmapHandle, ByVal nChange&) As Long
Declare Function L_IntensityDetectBitmap Lib "LTIMG13N" (hBitmap As LEADBitmapHandle, ByVal uLow&, ByVal uHigh&) As Long
Declare Function L_InvertBitmap Lib "LTIMG13N" (hBitmap As LEADBitmapHandle) As Long
Declare Function L_MaxFilterBitmap Lib "LTIMG13N" (hBitmap As LEADBitmapHandle, ByVal uDim&) As Long
Declare Function L_MedianFilterBitmap Lib "LTIMG13N" (hBitmap As LEADBitmapHandle, ByVal uDim&) As Long
Declare Function L_MinFilterBitmap Lib "LTIMG13N" (hBitmap As LEADBitmapHandle, ByVal uDim&) As Long
Declare Function L_MosaicBitmap Lib "LTIMG13N" (hBitmap As LEADBitmapHandle, ByVal uDim&) As Long
Declare Function L_OilifyBitmap Lib "LTIMG13N" (hBitmap As LEADBitmapHandle, ByVal uDim&) As Long
Declare Function L_PosterizeBitmap Lib "LTIMG13N" (hBitmap As LEADBitmapHandle, ByVal uLevels&) As Long
Declare Function L_PicturizeBitmap Lib "LTIMG13N" (hBitmap As LEADBitmapHandle, ByVal pszDir$, ByVal uFlags&, ByVal CellWidth&, _
                                                   ByVal CellHeight&, ByVal pfnCallback&, ByVal UserData&) As Integer
Declare Function L_SharpenBitmap Lib "LTIMG13N" (hBitmap As LEADBitmapHandle, ByVal nSharpness&) As Long
Declare Function L_SolarizeBitmap Lib "LTIMG13N" (hBitmap As LEADBitmapHandle, ByVal uThreshold&) As Long
Declare Function L_SpatialFilterBitmap Lib "LTIMG13N" (hBitmap As LEADBitmapHandle, pFilter As SPATIALFLT) As Long
Declare Function L_StretchBitmapIntensity Lib "LTIMG13N" (hBitmap As LEADBitmapHandle) As Long

Declare Function L_ContourFilterBitmap Lib "LTIMG13N" (hBitmap As LEADBitmapHandle, ByVal nThreshold%, ByVal nDeltaDirection%, _
                                                       ByVal nMaximumError%, ByVal nOption&) As Long


' New functions in v13
Declare Function L_GaussianFilterBitmap Lib "LTIMG13N" (hBitmap As LEADBitmapHandle, ByVal nRadius&) As Long
Declare Function L_UnsharpMaskBitmap Lib "LTIMG13N" (hBitmap As LEADBitmapHandle, ByVal nAmount&, ByVal nRadius&, ByVal nThreshold&, ByVal uColorType&) As Long
Declare Function L_LineProfile Lib "LTIMG13N" (hBitmap As LEADBitmapHandle, FirstPoint As POINT, SecondPoint As POINT, ByVal pRed&, ByVal pGreen&, ByVal pBlue&) As Long
Declare Function L_GrayScaleBitmapExt Lib "LTIMG13N" (hBitmap As LEADBitmapHandle, ByVal RedFact&, ByVal GreenFact&, ByVal BlueFact&) As Long
Declare Function L_SwapColors Lib "LTIMG13N" (hBitmap As LEADBitmapHandle, ByVal nFlags&) As Long
Declare Function L_BalanceColors Lib "LTIMG13N" (hBitmap As LEADBitmapHandle, pRedFact As BALANCING, pGreenFact As BALANCING, pBlueFact As BALANCING) As Long
Declare Function L_ConvertToColoredGray Lib "LTIMG13N" (hBitmap As LEADBitmapHandle, ByVal RedFact&, ByVal GreenFact&, ByVal BlueFact&, ByVal RedGrayFact&, ByVal GreenGrayFact&, ByVal BlueGrayFact&) As Long
Declare Function L_HistoEqualizeBitmap Lib "LTIMG13N" (hBitmap As LEADBitmapHandle, ByVal nFlag&) As Long
Declare Function L_RemoveRedeyeBitmap Lib "LTIMG13N" (hBitmap As LEADBitmapHandle, ByVal rcNewColor&, ByVal uThreshold&, ByVal nLightness&) As Long
Declare Function L_ResizeBitmapRgn Lib "LTIMG13N" (hBitmap As LEADBitmapHandle, ByVal uInflate&, ByVal uFlag&, ByVal bAsFrame&) As Long
Declare Function L_CreateFadedMask Lib "LTIMG13N" (hBitmap As LEADBitmapHandle, hMaskBitmap As LEADBitmapHandle, ByVal nLength&, ByVal nFadeRate&, ByVal nStepSize&, ByVal nInflate&, ByVal uFlag&, ByVal nMaxGray&, ByVal crTransparent&) As Long
Declare Function L_FeatherAlphaBlendBitmap Lib "LTIMG13N" (hBitmapDest As LEADBitmapHandle, ByVal nXDst&, ByVal nYDst&, ByVal nWidth&, ByVal nHeight&, _
                                                           hBitmapSrc As LEADBitmapHandle, ByVal nXSrc&, ByVal nYSrc&, hBitmapMsk As LEADBitmapHandle) As Long
Declare Function L_AlphaBlendBitmap Lib "LTIMG13N" (hBitmapDest As LEADBitmapHandle, ByVal nXDst&, ByVal nYDst&, ByVal nWidth&, ByVal nHeight&, _
                                                    BitmapSrc As LEADBitmapHandle, ByVal nXSrc&, ByVal nYSrc&, ByVal nOpacity) As Long
Declare Function L_CombineBitmapExt Lib "LTIMG13N" (hBitmapDst As LEADBitmapHandle, ByVal nXDst&, ByVal nYDst&, ByVal nWidth&, ByVal nHeight&, _
                                                    hBitmapSrc As LEADBitmapHandle, ByVal nXSrc&, ByVal nYSrc&, ByVal uFlag&) As Long
Declare Function L_AddBitmaps Lib "LTIMG13N" (hList As Long, ByVal uFlag) As Long
Declare Function L_AntiAliasBitmap Lib "LTIMG13N" (hBitmap As LEADBitmapHandle, ByVal uThreshold&, ByVal uDim&, ByVal uFilter&) As Long
Declare Function L_EdgeDetectorBitmap Lib "LTIMG13N" (hBitmap As LEADBitmapHandle, ByVal uThreshold&, ByVal uFilter&) As Long
Declare Function L_MotionBlurBitmap Lib "LTIMG13N" (hBitmap As LEADBitmapHandle, ByVal uDim&, ByVal nAngle&, ByVal bUnidirectional&) As Long
Declare Function L_PicturizeBitmapList Lib "LTIMG13N" (hBitmap As LEADBitmapHandle, ByVal uxDim&, ByVal uyDim&, ByVal uLightnessFact&, hList As Long) As Long
Declare Function L_PicturizeBitmapSingle Lib "LTIMG13N" (hBitmap As LEADBitmapHandle, hThumbBitmap As LEADBitmapHandle, ByVal uxDim&, ByVal uyDim&, ByVal uGammaFact&) As Long
Declare Function L_RemapBitmapIntensity Lib "LTIMG13N" (hBitmap As LEADBitmapHandle, ByVal pLUT&, ByVal uLUTLen&, ByVal uChannel&) As Long
Declare Function L_GetBitmapHistogram Lib "LTIMG13N" (hBitmap As LEADBitmapHandle, ByVal pHisto&, ByVal uHistoLen&, ByVal uChannel&) As Long
Declare Function L_GetUserLookUpTable Lib "LTIMG13N" (ByVal LookupTable&, ByVal uLookupLen&, ByVal apUserPoint&, ByVal UserPointCount&, ByVal puPointCount&) As Long
Declare Function L_GetFunctionalLookupTable Lib "LTIMG13N" (ByVal LookupTable&, ByVal uLookupLen&, ByVal uStart&, ByVal uEnd&, ByVal nFactor&, ByVal uFlag&) As Long
Declare Function L_HalfToneBitmap Lib "LTIMG13N" (hBitmap As LEADBitmapHandle, ByVal uType&, ByVal nAngle&, ByVal uDim&) As Long
Declare Function L_ConvertBitmapSignedToUnsigned Lib "LTIMG13N" (hBitmap As LEADBitmapHandle, ByVal uShift&) As Long
Declare Function L_AddBorder Lib "LTIMG13N" (hBitmap As LEADBitmapHandle, AddBorderInfo As AddBorderInfo) As Long
Declare Function L_AddFrame Lib "LTIMG13N" (hBitmap As LEADBitmapHandle, AddFrameInfo As AddFrameInfo) As Long


' Functions in LTTWN DLL

Declare Function L_IsTwainAvailable Lib "LTTWN13N" (ByVal hWnd&) As Long
Declare Function L_TwainAcquire Lib "LTTWN13N" (ByVal hWnd&, hBitmap As LEADBitmapHandle) As Long
Declare Function L_TwainAcquireExt Lib "LTTWN13N" (ByVal hWnd&, hBitmap As LEADBitmapHandle, ByVal uFlags&, ByVal pCallback&, ByVal pUserData&) As Long 'pCallBack and pUserData should be passed As 0
Declare Function L_TwainEnumSources Lib "LTTWN13N" (ByVal hWnd&, ByVal pfnCallback&, ByVal pUserData&)
Declare Function L_TwainGetProps Lib "LTTWN13N" (pTwain As TWAINPROPERTIES) As Long
Declare Function L_TwainSelect Lib "LTTWN13N" (ByVal hWnd&) As Long
Declare Function L_TwainSetProps Lib "LTTWN13N" (ByVal hWnd&, pTwain As TWAINPROPERTIES, ByVal nFlags&) As Long

' Functions in LTEFX DLL
Declare Function L_EfxDraw3dShape Lib "LTEFX13N" (ByVal hDC&, ByVal uShape&, pRect As RECT, ByVal crBack&, ByVal hdcBack&, prcBack As RECT, _
                                                  ByVal uBackStyle&, ByVal crFill&, ByVal uFillStyle&, ByVal crBorder&, ByVal uBorderStyle&, _
                                                  ByVal uBorderWidth&, ByVal crInnerHilite&, ByVal crInnerShadow&, ByVal uInnerStyle&, _
                                                  ByVal uInnerWidth&, ByVal crOuterHilite&, ByVal crOuterShadow&, ByVal uOuterStyle&, _
                                                  ByVal uOuterWidth&, ByVal nShadowX&, ByVal nShadowY&, ByVal crShadow&, ByVal hRGN&) As Long
Declare Function L_EfxDraw3dText Lib "LTEFX13N" (ByVal hDC&, ByVal szText$, pRect As RECT, ByVal uFlags&, ByVal nXDepth&, ByVal nYDepth&, _
                                                 ByVal crText&, ByVal crShadow&, ByVal crHilite&, ByVal hFont&, ByVal hdcFore&) As Long
Declare Function L_EfxDrawFrame Lib "LTEFX13N" (ByVal hDC&, pRect As RECT, ByVal uFlags&, ByVal uFrameWidth&, ByVal crFrame&, ByVal uInnerWidth&, _
                                                ByVal crInner1&, ByVal crInner2&, ByVal uOuterWidth&, ByVal crOuter1&, ByVal crOuter2&) As Long
Declare Function L_EfxDrawRotated3dText Lib "LTEFX13N" (ByVal hDC&, ByVal szText$, pRect As RECT, ByVal nAngle&, ByVal uFlags&, ByVal nXDepth&, _
                                                        ByVal nYDepth&, ByVal crText&, ByVal crShadow&, ByVal crHilite&, ByVal hFont&, ByVal hdcFore&) As Long
Declare Function L_EfxEffectBlt Lib "LTEFX13N" (ByVal hDC&, ByVal nXDest&, ByVal nYDest&, ByVal nWidth&, ByVal nHeight&, ByVal hdcSrc&, ByVal nXSrc&, _
                                                ByVal nYSrc&, ByVal uEffect&, ByVal uGrain&, ByVal uDelay&, ByVal uPass&, ByVal uMaxPass&, _
                                                                                                ByVal fTransparency&, ByVal crTransparency&, ByVal uWandWidth&, ByVal crWand&, ByVal uROP&) As Long
Declare Function L_EfxGradientFillRect Lib "LTEFX13N" (ByVal hDC&, pRect As RECT, ByVal uStyle&, ByVal crStart&, ByVal crEnd&, ByVal uSteps&) As Long
Declare Function L_EfxPaintBitmap Lib "LTEFX13N" (ByVal hDC&, pBITMAPHANDLE As LEADBitmapHandle, pSrc As RECT, pSrcClip As RECT, pDest As RECT, _
                                                  pDestClip As RECT, ByVal uEffect&, ByVal uGrain&, ByVal uDelay&, ByVal uPass&, ByVal uMaxPass&, _
                                                  ByVal fTransparency&, ByVal crTransparency&, ByVal uWandWidth&, ByVal crWand&, ByVal uROP&) As Long
Declare Function L_EfxPaintTransition Lib "LTEFX13N" (ByVal hDC&, ByVal uTransition&, ByVal crBack&, ByVal crFore&, ByVal uSteps&, pDest As RECT, _
                                                      ByVal uEffect&, ByVal uGrain&, ByVal uDelay&, ByVal uPass&, ByVal uMaxPass&, ByVal fTransparency&, _
                                                      ByVal crTransparency&, ByVal uWandWidth&, ByVal crWand&, ByVal uROP&) As Long
Declare Function L_EfxPatternFillRect Lib "LTEFX13N" (ByVal hDC&, pRect As RECT, ByVal uStyle&, ByVal crBack&, ByVal crFore&) As Long
Declare Function L_PaintDCEffect Lib "LTEFX13N" (ByVal hDC&, hBitmap As LEADBitmapHandle, pSrc As RECT, pClipSrc As RECT, pDst As RECT, pClipDst As RECT, ByVal uROP3&, ByVal uEffect&) As Long
Declare Function L_PaintRgnDCEffect Lib "LTEFX13N" (ByVal hDC&, lpBitmap As LEADBitmapHandle, pSrc As RECT, pClipSrc As RECT, pDst As RECT, pClipDst As RECT, ByVal uROP3&, ByVal uEffect&) As Long


'  Functions for Control bitmap access
Declare Function L_GetControlBitmap Lib "LTOCX13N.OCX" (Ctrl As Control, hBitmap As LEADBitmapHandle) As Long
Declare Function L_SetControlBitmap Lib "LTOCX13N.OCX" (Ctrl As Control, hBitmap As LEADBitmapHandle) As Long

'  Functions in LTDLG DLL
Declare Function L_DlgFileOpen Lib "LTDLG13N" (ByVal hwndOwner&, ofn As OPENFILENAME, foParm As FILEOPENPARM, ByVal uFlags&, ByVal pCallback&, ByVal pUserData&) As Long
Declare Function L_DlgGetAngle Lib "LTDLG13N" (ByVal hWnd&, hBitmap As LEADBitmapHandle, DlgParams As GETANGLEDLGPARM, ByVal uFlags&, ByVal pCallback&, ByVal pUserData&) As Long
Declare Function L_DlgGetSize Lib "LTDLG13N" (ByVal hWnd&, hBitmap As LEADBitmapHandle, DlgParams As GETSIZEDLGPARM, ByVal uFlags&, ByVal pCallback&, ByVal pUserData&) As Long
Declare Function L_DlgGetFilter Lib "LTDLG13N" (ByVal hWnd&, hBitmap As LEADBitmapHandle, DlgParams As GETFILTERDLGPARM, ByVal uFlags&, ByVal pCallback&, ByVal pUserData&) As Long
Declare Function L_DlgGetChange Lib "LTDLG13N" (ByVal hWnd&, hBitmap As LEADBitmapHandle, DlgParams As GETCHANGEDLGPARM, ByVal uFlags&, ByVal pCallback&, ByVal pUserData&) As Long
Declare Function L_DlgGetGamma Lib "LTDLG13N" (ByVal hWnd&, hBitmap As LEADBitmapHandle, DlgParams As GETGAMMADLGPARM, ByVal uFlags&, ByVal pCallback&, ByVal pUserData&) As Long
Declare Function L_DlgGetNoise Lib "LTDLG13N" (ByVal hWnd&, hBitmap As LEADBitmapHandle, DlgParams As GETNOISEDLGPARM, ByVal uFlags&, ByVal pCallback&, ByVal pUserData&) As Long
Declare Function L_DlgGetEmboss Lib "LTDLG13N" (ByVal hWnd&, hBitmap As LEADBitmapHandle, DlgParams As GETEMBOSSDLGPARM, ByVal uFlags&, ByVal pCallback&, ByVal pUserData&) As Long
Declare Function L_DlgColorRes Lib "LTDLG13N" (ByVal hWnd&, hBitmap As LEADBitmapHandle, DlgParams As COLORRESDLGPARM, ByVal uFlags&, ByVal uExFlags&, ByVal pCallback&, ByVal pUserData&) As Long
Declare Function L_DlgFileSave Lib "LTDLG13N" (ByVal hWnd&, ofn As OPENFILENAME, fsParm As FILESAVEPARM, ByVal uFlags&, SaveFormats As FILESAVEFORMAT, ByVal nSaveFormats&, ByVal pCallback&, ByVal pUserData&) As Long
Declare Function L_DlgWindowLevel Lib "LTDLG13N" (ByVal hWnd&, hBitmap As LEADBitmapHandle, DlgParams As WINDOWLEVELDLGPARM, ByVal uFlags&, ByVal pCallback&, ByVal pUserData&) As Long
Declare Function L_DlgGetEffect Lib "LTDLG13N" (ByVal hWnd&, hBitmap As LEADBitmapHandle, EfxParm As EFXDLGPARM, ByVal uFlags&, ByVal pCallback&, ByVal pUserData&) As Long
Declare Function L_DlgGetShape Lib "LTDLG13N" (ByVal hWnd&, hBitmap As LEADBitmapHandle, hBackgroundBitmap As LEADBitmapHandle, ShapeParm As SHAPEDLGPARM, ByVal uFlags&, ByVal pCallback&, ByVal pUserData&) As Long
Declare Function L_DlgGetText Lib "LTDLG13N" (ByVal hWnd&, hBitmap As LEADBitmapHandle, hForegroundBitmap As LEADBitmapHandle, TextParm As TEXTDLGPARM, ByVal uFlags&, ByVal pCallback&, ByVal pUserData&) As Long
Declare Function L_DlgGetGradient Lib "LTDLG13N" (ByVal hWnd&, hBitmap As LEADBitmapHandle, GradParm As GRADDLGPARM, ByVal uFlags&, ByVal pCallback&, ByVal pUserData&) As Long
Declare Function L_DlgGetTransition Lib "LTDLG13N" (ByVal hWnd&, hBitmap As LEADBitmapHandle, TransParm As TRANSDLGPARM, ByVal uFlags&, ByVal pCallback&, ByVal pUserData&) As Long
Declare Function L_DlgGetDirectory Lib "LTDLG13N" (ByVal hWnd&, DlgParams As GETDIRECTORYDLGPARM, ByVal uFlags&, ByVal pCallback&, ByVal pUserData&) As Long
Declare Function L_DlgContourFilter Lib "LTDLG13N" (ByVal hWnd&, hBitmap As LEADBitmapHandle, ContourParm As CONTOURFILTERDLGPARM, ByVal uFlags&, ByVal pCallback&, ByVal pUserData&) As Long
Declare Function L_DlgHalftone Lib "LTDLG13N" (ByVal hWnd&, hBitmap As LEADBitmapHandle, DlgParams As HALFTONEDLGPARM, ByVal uFlags&, ByVal pCallback&, ByVal pUserData&) As Long
Declare Function L_DlgGetRange Lib "LTDLG13N" (ByVal hWnd&, hBitmap As LEADBitmapHandle, DlgParams As GETRANGEDLGPARM, ByVal uFlags&, ByVal pCallback&, ByVal pUserData&) As Long

' dialog string functions
Declare Function L_DlgGetStringLen Lib "LTDLG13N" (ByVal uString&, puLen&) As Long
Declare Function L_DlgGetString Lib "LTDLG13N" (ByVal uString&, ByVal pString$) As Long
Declare Function L_DlgSetString Lib "LTDLG13N" (ByVal uString&, ByVal pString$) As Long
Declare Function L_DlgSetFont Lib "LTDLG13N" (ByVal hFont&) As Long

'  Functions in LTISI DLL
Declare Function L_IsISISAvailable Lib "LTISI13N" () As Boolean
Declare Function L_ISISAcquire Lib "LTISI13N" (ByVal hWnd&, hBitmap As LEADBitmapHandle, ByVal uFlags&) As Long
Declare Function L_ISISAcquireMulti Lib "LTISI13N" (ByVal hWnd&, ByVal pszBaseFileName$, ByVal uFlags&, ByVal nFormat&, ByVal bMultiPageFile&, pnPagesDiscarded&, ByVal pfnCallback&, ByVal pUserData&) As Long
Declare Function L_ISISSelect Lib "LTISI13N" (ByVal hWnd&, ByVal pszCurScanDriver$) As Long
Declare Function L_ISISLoadDriver Lib "LTISI13N" (ByVal pszDriverName$) As Long
Declare Function L_ISISUnloadDriver Lib "LTISI13N" () As Long
Declare Function L_ISISSetTagLong Lib "LTISI13N" (ByVal uTag&, ByVal lValue&) As Long
Declare Function L_ISISGetTagLong Lib "LTISI13N" (ByVal uTag&, plValue&) As Long
Declare Function L_ISISSetTagShort Lib "LTISI13N" (ByVal uTag&, ByVal nValue&) As Long
Declare Function L_ISISGetTagShort Lib "LTISI13N" (ByVal uTag&, pnValue&) As Long
Declare Function L_ISISSetScanOptions Lib "LTISI13N" (ByVal hWnd&) As Long
Declare Function L_ISISSetTagASCII Lib "LTISI13N" (ByVal uTag&, ByVal pszValue$) As Long
Declare Function L_ISISGetTagASCII Lib "LTISI13N" (ByVal uTag&, ByVal pszValue$, ByVal puSize&, ByVal bDefault&) As Long
Declare Function L_ISISGetTagASCIIChoice Lib "LTISI13N" (ByVal uTag&, ByVal nIndex&, ByVal pszValue$, ByVal puSize&) As Long
Declare Function L_ISISGetTagLongChoice Lib "LTISI13N" (ByVal uTag&, ByVal nIndex&, ByVal plValue$) As Long
Declare Function L_ISISGetTagShortChoice Lib "LTISI13N" (ByVal uTag&, ByVal nIndex&, ByVal pnValue$) As Long

'  Functions in LTSCR DLL
Declare Function L_SetCaptureOption Lib "LTSCR13N" (pOptions As LEADCAPTUREOPTION) As Long
Declare Function L_GetCaptureOption Lib "LTSCR13N" (pOptions As LEADCAPTUREOPTION) As Long
Declare Function L_CaptureWindow Lib "LTSCR13N" (pBitmap As LEADBitmapHandle, ByVal hWnd&, ByVal wctCaptureType&, pCaptureInfo As LEADCAPTUREINFO, ByVal pfnCaptureCallback&, ByVal pUserData&) As Long
Declare Function L_CaptureActiveWindow Lib "LTSCR13N" (pBitmap As LEADBitmapHandle, pCaptureInfo As LEADCAPTUREINFO, ByVal pfnCaptureCallback&, ByVal pUserData&) As Long
Declare Function L_CaptureActiveClient Lib "LTSCR13N" (pBitmap As LEADBitmapHandle, pCaptureInfo As LEADCAPTUREINFO, ByVal pfnCaptureCallback&, ByVal pUserData&) As Long
Declare Function L_CaptureWallPaper Lib "LTSCR13N" (pBitmap As LEADBitmapHandle, pCaptureInfo As LEADCAPTUREINFO, ByVal pfnCaptureCallback&, ByVal pUserData&) As Long
Declare Function L_CaptureFullScreen Lib "LTSCR13N" (pBitmap As LEADBitmapHandle, pCaptureInfo As LEADCAPTUREINFO, ByVal pfnCaptureCallback&, ByVal pUserData&) As Long
Declare Function L_CaptureMenuUnderCursor Lib "LTSCR13N" (pBitmap As LEADBitmapHandle, pCaptureInfo As LEADCAPTUREINFO, ByVal pfnCaptureCallback&, ByVal pUserData&) As Long
Declare Function L_CaptureWindowUnderCursor Lib "LTSCR13N" (pBitmap As LEADBitmapHandle, pCaptureInfo As LEADCAPTUREINFO, ByVal pfnCaptureCallback&, ByVal pUserData&) As Long
Declare Function L_CaptureSelectedObject Lib "LTSCR13N" (pBitmap As LEADBitmapHandle, pObjectOptions As LEADCAPTUREOBJECTOPTION, pCaptureInfo As LEADCAPTUREINFO, ByVal pfnCaptureCallback&, ByVal pUserData&) As Long
Declare Function L_CaptureArea Lib "LTSCR13N" (pBitmap As LEADBitmapHandle, pAreaOption As LEADCAPTUREAREAOPTION, pCaptureInfo As LEADCAPTUREINFO, ByVal pfnCaptureCallback&, ByVal pUserData&) As Long
Declare Function L_CaptureMouseCursor Lib "LTSCR13N" (pBitmap As LEADBitmapHandle, ByVal crFill&, pCaptureInfo As LEADCAPTUREINFO, ByVal pfnCaptureCallback&, ByVal pUserData&) As Long
Declare Function L_CaptureSetHotKeyCallback Lib "LTSCR13N" (ByVal nHotKey&, ByVal uHotKeyModifiers&, ByVal pfnCaptureHotKeyCB&, ByVal pUserData&) As Long
Declare Function L_SetCaptureOptionDlg Lib "LTSCR13N" (ByVal hwndOwner&, pOptions As LEADCAPTUREOPTION) As Long
Declare Function L_CaptureAreaOptionDlg Lib "LTSCR13N" (ByVal hParentWnd&, pAreaOption As LEADCAPTUREAREAOPTION, ByVal nUseDefault&) As Long
Declare Function L_CaptureObjectOptionDlg Lib "LTSCR13N" (ByVal hParentWnd&, pObjectOptions As LEADCAPTUREOBJECTOPTION, ByVal nUseDefault&) As Long
Declare Function L_GetDefaultAreaOption Lib "LTSCR13N" (pAreaOption As LEADCAPTUREAREAOPTION) As Long
Declare Function L_GetDefaultObjectOption Lib "LTSCR13N" (pObjectOptions As LEADCAPTUREOBJECTOPTION) As Long
Declare Function L_StopCapture Lib "LTSCR13N" () As Long
Declare Function L_CaptureFromExeDlg Lib "LTSCR13N" (pBitmap As LEADBitmapHandle, ByVal pszFileName$, pTransparentColor&, ByVal nResType&, ByVal nDialogType&, pCaptureInfo As LEADCAPTUREINFO, ByVal pfnCaptureCallback&, ByVal pUserData&) As Long
Declare Function L_CaptureFromExe Lib "LTSCR13N" (pBitmap As LEADBitmapHandle, ByVal pszFileName$, ByVal nResType&, ByVal pResID$, ByVal bCaptureByIndex&, ByVal clrBackGnd&, ByVal pfnCaptureCallback&, ByVal pUserData&) As Long
Declare Function L_CaptureGetResCount Lib "LTSCR13N" (ByVal pszFileName$, ByVal nResType&, pnCount&) As Long

' Functions in the LTBAR DLL
Declare Function L_BarCodeRead Lib "LTBAR13N" (pBitmap As LEADBitmapHandle, prcSearch As RECT, ByVal ulSearchType&, _
                                               ByVal nUnits&, ByVal ulFlags&, ByVal nMultipleMaxCount&, _
                                               pBarCode1D As BARCODE1D, pBarCodePDF As BARCODEREADPDF, _
                                               ByVal ppBarCodeData&) As Long

Declare Function L_BarCodeWrite Lib "LTBAR13N" (pBitmap As LEADBitmapHandle, pBarCodeData As BARCODEDATA, ByVal ulFlags&, _
                                                pBarCode1D As BARCODE1D, pBarCode2D As BARCODEWRITECODEONE, pBarCodePDF As BARCODEWRITEPDF, lprcSize As RECT) As Long

Declare Sub L_BarCodeFree Lib "LTBAR13N" (ByVal ppBarCodeData&)

Declare Function L_BarCodeIsDuplicated Lib "LTBAR13N" (pBarCodeDataItem As BARCODEDATA) As Boolean

Declare Function L_BarCodeGetDuplicated Lib "LTBAR13N" (pBarCodeDataItem As BARCODEDATA) As Long

Declare Function L_BarCodeGetNextBuplicated Lib "LTBAR13N" (pBarCodeData As BARCODEDATA, ByVal nCurIndex&) As Long

Declare Function L_BarCodeInit Lib "LTBAR13N" (ByVal nMajorType&) As Long
Declare Sub L_BarCodeExit Lib "LTBAR13N" ()
Declare Function L_BarCodeVersionInfo Lib "LTBAR13N" (pBarCodeVersion As BARCODEVERSION) As Long
