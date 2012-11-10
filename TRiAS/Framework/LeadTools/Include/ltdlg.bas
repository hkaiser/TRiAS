Attribute VB_Name = "ltdlg"
' flags for the Help Callbacks for L_Dlg* function
Global Const DLG_HELP_FILEOPEN = 1
Global Const DLG_HELP_FILEOPEN95 = 2
Global Const DLG_HELP_FILESAVE = 3
Global Const DLG_HELP_FILESAVE95 = 4
Global Const DLG_HELP_COLORRES = 5
Global Const DLG_HELP_GETANGLE = 6
Global Const DLG_HELP_GETSIZE = 7
Global Const DLG_HELP_GETFILTER = 8
Global Const DLG_HELP_GETCHANGE = 9
Global Const DLG_HELP_GETRANGE = 10
Global Const DLG_HELP_GETGAMMA = 11
Global Const DLG_HELP_GETNOISE = 12
Global Const DLG_HELP_GETEMBOSS = 13

' flags for L_DlgFileOpen()
Global Const DLG_FO_AUTOPROCESS = &H1             ' Dlg should autoprocess image and fill the pBitmap
Global Const DLG_FO_PROGRESSIVE = &H2            ' FileOpen Dlg should have Prog. File options
Global Const DLG_FO_MULTIPAGE = &H4              ' FileOpen Dlg should have Multipage options
Global Const DLG_FO_LOADROTATED = &H8            ' FileOpen Dlg should have Load Rotated option
Global Const DLG_FO_LOADCOMPRESSED = &H10        ' FileOpen Dlg should have Load 1-bit compressed option
Global Const DLG_FO_FILEINFO = &H20              ' FileOpen Dlg should have FileInfo button
Global Const DLG_FO_SHOWPREVIEW = &H40           ' FileOpen Dlg should have ThumbNail and should create the
                                                ' preview if none is stored in the file
Global Const DLG_FO_SHOWSTAMP = &H80             ' FileOpen Dlg should have ThumbNail and should only load
                                                ' the preview stamp if one is stored in the file
Global Const DLG_FO_95STYLE = &H100              ' FileOpen Dlg should have Windows95 Explorer style look
Global Const DLG_FO_DELPAGE = &H200                 ' FileOpen Dlg should have Delete Page option
Global Const DLG_FO_RESDLG = &H400                  ' If AutoProcess, and format supports resolution, show
Global Const DLG_FO_NOFILEMUSTEXIST = &H800          ' Do not verify that the path exists
Global Const DLG_FO_NOPATHMUSTEXIST = &H1000         ' Do not verify that the file exists
Global Const DLG_GETRES_95CONTEXTHELP = &H2000       ' GetRes Dlg should contain context sensitive help icon
Global Const DLG_FO_FILEINFO_TOTALPAGES = &H4000   ' when filling FILEINFO, get TOTALPAGES
Global Const DLG_FO_FILEINFO_PDFDLG = &H8000   ' If AutoProcess, and format is PDF , show PDF options dlg

' flags for L_DlgFileSave()
Global Const DLG_FS_AUTOPROCESS = &H1            ' Dlg should autoprocess image and fill the pBitmap
Global Const DLG_FS_PROGRESSIVE = &H2            ' FileSave Dlg should have Prog. File options
Global Const DLG_FS_MULTIPAGE = &H4              ' FileSave Dlg should have Multipage options
Global Const DLG_FS_STAMP = &H8                  ' FileSave Dlg should have save with stamp options
Global Const DLG_FS_QFACTOR = &H10               ' FileSave Dlg should have QFactor option
Global Const DLG_FS_95STYLE = &H20               ' FileSave Dlg should have Windows95 Explorer style look
' file format flags for L_DlgFileSave()
Global Const DLG_FS_LEAD = &H0
Global Const DLG_FS_LEAD1BIT = &H1
Global Const DLG_FS_JFIF = &H2
Global Const DLG_FS_CALS = &H4
Global Const DLG_FS_PNG = &H8
Global Const DLG_FS_DICOM = &H10
Global Const DLG_FS_FAX = &H20
Global Const DLG_FS_EPS = &H40
Global Const DLG_FS_EXIF = &H80
Global Const DLG_FS_FPX = &H100
Global Const DLG_FS_IMG = &H200
Global Const DLG_FS_GIF = &H400
Global Const DLG_FS_IOCA = &H800
Global Const DLG_FS_PCT = &H1000
Global Const DLG_FS_MAC = &H2000
Global Const DLG_FS_AWD = &H4000
Global Const DLG_FS_MSP = &H8000
Global Const DLG_FS_OS2BMP = &H10000
Global Const DLG_FS_PCX = &H20000
Global Const DLG_FS_PSD = &H40000
Global Const DLG_FS_RAS = &H80000
Global Const DLG_FS_TGA = &H100000
Global Const DLG_FS_TIFF = &H200000
Global Const DLG_FS_BMP = &H400000
Global Const DLG_FS_WFX = &H800000
Global Const DLG_FS_WMF = &H1000000
Global Const DLG_FS_WPG = &H2000000
Global Const DLG_FS_ICO = &H4000000
Global Const DLG_FS_CUR = &H8000000
Global Const DLG_FS_ALL = &HFFFFFFF             ' all file formats

' flags for Image processing dialog functions
Global Const DLG_IMG_AUTOPROCESS = &H10000000      ' Dlg should autoprocess image and fill the pBitmap
Global Const DLG_IMG_SHOWPREVIEW = &H1000000       ' ImageProcess Dlg should preview of image

Global Const DLG_IMG_RESIZE = &H1                  ' resize dialog
Global Const DLG_IMG_RESAMPLE = &H2                ' resample dialog
Global Const DLG_IMG_ROTATE = &H3                  ' rotate dialog
Global Const DLG_IMG_SHEAR = &H4                   ' shear dialog

Global Const DLG_IMG_GRADIENT = &H1                ' gradient dialog
Global Const DLG_IMG_LAPLACIAN = &H2               ' laplacian dialog
Global Const DLG_IMG_SOBEL = &H4                   ' sobel dialog
Global Const DLG_IMG_PREWITT = &H8                 ' prewitt dialog
Global Const DLG_IMG_SHIFTDIFF = &H10              ' shiftdiff dialog
Global Const DLG_IMG_LINESEG = &H20                ' lineseg dialog
Global Const DLG_IMG_EROSION = &H40                ' erosion dialog
Global Const DLG_IMG_DILATION = &H80               ' dilation dialog

Global Const DLG_IMG_SHARPEN = &H1                 ' sharpen dialog
Global Const DLG_IMG_BRIGHTNESS = &H2              ' brightness dialog
Global Const DLG_IMG_CONTRAST = &H4                ' contrast dialog
Global Const DLG_IMG_SATURATION = &H8              ' saturation dialog
Global Const DLG_IMG_HISTOCONTRAST = &H10          ' histo contrast dialog
Global Const DLG_IMG_HUE = &H20                    ' hue dialog
Global Const DLG_IMG_HALFTONE = &H40               ' halftone dialog
Global Const DLG_IMG_POSTERIZE = &H80              ' posterize dialog
Global Const DLG_IMG_MOSAIC = &H100                ' mosaic dialog
Global Const DLG_IMG_AVERAGE = &H200               ' average dialog
Global Const DLG_IMG_MEDIAN = &H400                ' median dialog
Global Const DLG_IMG_OILIFY = &H800                ' oilify dialog
Global Const DLG_IMG_MIN = &H1000                  ' min filter dialog
Global Const DLG_IMG_MAX = &H2000                  ' max filter dialog
Global Const DLG_IMG_SOLARIZE = &H4000             ' solarize dialog

Global Const DLG_IMG_ADDNOISE = &H1C               ' add noise dialog
Global Const DLG_IMG_GAMMACORRECT = &H1D           ' gamma correct dialog
Global Const DLG_IMG_EMBOSS = &H1E                 ' emboss filter dialog
Global Const DLG_IMG_INTENSITYDETECT = &H1F        ' emboss filter dialog

Global Const DLG_IMG_TOOL_RESIZE = &H4000
Global Const DLG_IMG_TOOL_ONSCREEN = &H8000
Global Const DLG_IMG_TOOL_SHOWEFFECT = &H10000
Global Const DLG_IMG_FORCELINKCHANNELS = &H20000   'To Force the dialog to apply "Link all channels" all the times.

' flags for L_DlgColorRes()
Global Const DLG_CR_SHOWPREVIEW = &H1              ' shows preview of image
Global Const DLG_CR_AUTOPROCESS = &H2              ' process the image on OK

Global Const DLG_CR_1BIT = &H4                     ' 1-bit is an option
Global Const DLG_CR_2BIT = &H8                     ' 2-bit is an option
Global Const DLG_CR_3BIT = &H10                    ' 3-bit is an option
Global Const DLG_CR_4BIT = &H20                    ' 4-bit is an option
Global Const DLG_CR_5BIT = &H40                    ' 5-bit is an option
Global Const DLG_CR_6BIT = &H80                    ' 6-bit is an option
Global Const DLG_CR_7BIT = &H100                   ' 7-bit is an option
Global Const DLG_CR_8BIT = &H200                   ' 8-bit is an option
Global Const DLG_CR_12BIT = &H400                  ' 12-bit is an option
Global Const DLG_CR_16BIT = &H800                  ' 16-bit is an option
Global Const DLG_CR_24BIT = &H1000                 ' 24-bit is an option
Global Const DLG_CR_32BIT = &H2000                 ' 32-bit is an option
Global Const DLG_CR_BITALL = &H3FFC                ' All BitsPerPixel are options

Global Const DLG_CR_DITHER_NONE = &H4000           ' no dithering is an option
Global Const DLG_CR_DITHER_FLOYD = &H8000          ' floyd dithering is an option
Global Const DLG_CR_DITHER_STUCKI = &H10000        ' stucki dithering is an option
Global Const DLG_CR_DITHER_BURKES = &H20000        ' burkes dithering is an option
Global Const DLG_CR_DITHER_SIERRA = &H40000        ' sierra dithering is an option
Global Const DLG_CR_DITHER_STEVENSON = &H80000     ' stevenson dithering is an option
Global Const DLG_CR_DITHER_JARVIS = &H100000       ' jarvis dithering is an option
Global Const DLG_CR_DITHER_ORDERED = &H200000      ' ordered dithering is an option
Global Const DLG_CR_DITHER_ALL = &H3FC000          ' All dithering methods are options

Global Const DLG_CR_PAL_FIXED = &H400000           ' fixed palette is an option
Global Const DLG_CR_PAL_OPTIMIZED = &H800000       ' fixed palette is an option
Global Const DLG_CR_PAL_IDENTITY = &H1000000       ' identity palette is an option
Global Const DLG_CR_PAL_NETSCAPE = &H2000000       ' netscape palette is an option
Global Const DLG_CR_PAL_ALL = &H3C00000            ' All palette options are options

Global Const DLG_CR_ORDER = &H4000000              ' color order is an option





' Error constants
Global Const DLG_ERROR_FAILURE                     = &H80000000
Global Const DLG_ERROR_NO_MEMORY                   = &H80000001 
Global Const DLG_ERROR_NO_BITMAP                   = &H80000002
Global Const DLG_ERROR_MEMORY_TOO_LOW              = &H80000003
Global Const DLG_ERROR_FILE_LSEEK                  = &H80000004
Global Const DLG_ERROR_FILE_WRITE                  = &H80000005
Global Const DLG_ERROR_FILE_GONE                   = &H80000006
Global Const DLG_ERROR_FILE_READ                   = &H80000007
Global Const DLG_ERROR_INV_FILENAME                = &H80000008
Global Const DLG_ERROR_FILE_FORMAT                 = &H80000009
Global Const DLG_ERROR_FILE_NOT_FOUND              = &H8000000A
Global Const DLG_ERROR_INV_RANGE                   = &H8000000B
Global Const DLG_ERROR_IMAGE_TYPE                  = &H8000000C
Global Const DLG_ERROR_INV_PARAMETER               = &H8000000D
Global Const DLG_ERROR_FILE_OPEN                   = &H8000000E
Global Const DLG_ERROR_UNKNOWN_COMP                = &H8000000F
Global Const DLG_ERROR_NOT_SUPPORTED               = &H80000010
Global Const DLG_ERROR_NOT_256_COLOR               = &H80000011
Global Const DLG_ERROR_PRINTER                     = &H80000012
Global Const DLG_ERROR_CRC_CHECK                   = &H80000013
                                                   
Global Const DLG_ERROR_QFACTOR                     = &H80000015
Global Const DLG_ERROR_TARGAINSTALL                = &H80000016
Global Const DLG_ERROR_OUTPUTTYPE                  = &H80000017
Global Const DLG_ERROR_XORIGIN                     = &H80000018
Global Const DLG_ERROR_YORIGIN                     = &H80000019
Global Const DLG_ERROR_VIDEOTYPE                   = &H8000001A
Global Const DLG_ERROR_BITPERPIXEL                 = &H8000001B
Global Const DLG_ERROR_WINDOWSIZE                  = &H8000001C
Global Const DLG_ERROR_NORMAL_ABORT                = &H8000001D

Global Const DLG_ERROR_FIXEDPAL_DATA               = &H8000003F
Global Const DLG_ERROR_LOADFONT_DATA               = &H80000040
Global Const DLG_ERROR_NO_STAMP                    = &H80000041

Global Const DLG_ERROR_G3CODE_INVALID              = &H80000046
Global Const DLG_ERROR_G3CODE_EOF                  = &H80000047
Global Const DLG_ERROR_G3CODE_EOL                  = &H80000048
Global Const DLG_ERROR_PREMATURE_EOF               = &H80000049
Global Const DLG_ERROR_PREMATURE_EOL               = &H8000004A
Global Const DLG_ERROR_UNCOMP_EOF                  = &H8000004B
Global Const DLG_ERROR_ACT_INCOMP                  = &H8000004C
Global Const DLG_ERROR_BAD_DECODE_STATE            = &H8000004D
Global Const DLG_ERROR_VERSION_NUMBER              = &H8000004E
Global Const DLG_ERROR_TWAIN_NODSM                 = &H8000004F
Global Const DLG_ERROR_TWAIN_BUMMER                = &H80000050
Global Const DLG_ERROR_TWAIN_LOWMEMORY             = &H80000051
Global Const DLG_ERROR_TWAIN_NODS                  = &H80000052
Global Const DLG_ERROR_TWAIN_MAXCONNECTIONS        = &H80000053
Global Const DLG_ERROR_TWAIN_OPERATIONERROR        = &H80000054
Global Const DLG_ERROR_TWAIN_BADCAP                = &H80000055
Global Const DLG_ERROR_TWAIN_BADPROTOCOL           = &H80000056
Global Const DLG_ERROR_TWAIN_BADVALUE              = &H80000057
Global Const DLG_ERROR_TWAIN_SEQERROR              = &H80000058
Global Const DLG_ERROR_TWAIN_BADDEST               = &H80000059
Global Const DLG_ERROR_TWAIN_CANCEL                = &H8000005A
Global Const DLG_ERROR_PANWINDOW_NOT_CREATED       = &H8000005B
Global Const DLG_ERROR_NOT_ENOUGH_IMAGES           = &H8000005C

Global Const DLG_ERROR_USER_ABORT                  = &H80000064

Global Const DLG_ERROR_FPX_INVALID_FORMAT          = &H80000065  
Global Const DLG_ERROR_FPX_FILE_WRITE              = &H80000066  
Global Const DLG_ERROR_FPX_FILE_READ               = &H80000067  
Global Const DLG_ERROR_FPX_FILE_NOT_FOUND          = &H80000068  
Global Const DLG_ERROR_FPX_COLOR_CONVERSION        = &H80000069  
Global Const DLG_ERROR_FPX_SERVER_INIT             = &H8000006A  
Global Const DLG_ERROR_FPX_LOW_MEMORY              = &H8000006B  
Global Const DLG_ERROR_FPX_IMAGE_TOO_BIG           = &H8000006C  
Global Const DLG_ERROR_FPX_INVALID_COMPRESSION     = &H8000006D  
Global Const DLG_ERROR_FPX_INVALID_RESOLUTION      = &H8000006E  
Global Const DLG_ERROR_FPX_INVALID_FPX_HANDLE      = &H8000006F  
Global Const DLG_ERROR_FPX_TOO_MANY_LINES          = &H80000070  
Global Const DLG_ERROR_FPX_BAD_COORDINATES         = &H80000071  
Global Const DLG_ERROR_FPX_FILE_SYSTEM_FULL        = &H80000072  
Global Const DLG_ERROR_FPX_MISSING_TABLE           = &H80000073  
Global Const DLG_ERROR_FPX_RETURN_PARAMETER_TOO_LARGE = &H80000074
Global Const DLG_ERROR_FPX_NOT_A_VIEW              = &H80000075  
Global Const DLG_ERROR_FPX_VIEW_IS_TRANSFORMLESS   = &H80000076  
Global Const DLG_ERROR_FPX_ERROR                   = &H80000077  
Global Const DLG_ERROR_FPX_UNIMPLEMENTED_FUNCTION  = &H80000078  
Global Const DLG_ERROR_FPX_INVALID_IMAGE_DESC      = &H80000079  
Global Const DLG_ERROR_FPX_INVALID_JPEG_TABLE      = &H8000007A  
Global Const DLG_ERROR_FPX_ILLEGAL_JPEG_ID         = &H8000007B  
Global Const DLG_ERROR_FPX_MEMORY_ALLOCATION_FAILED = &H8000007C  
Global Const DLG_ERROR_FPX_NO_MEMORY_MANAGEMENT    = &H8000007D  
Global Const DLG_ERROR_FPX_OBJECT_CREATION_FAILED  = &H8000007E  
Global Const DLG_ERROR_FPX_EXTENSION_FAILED        = &H8000007F  
Global Const DLG_ERROR_FPX_FREE_NULL_PTR           = &H80000080  
Global Const DLG_ERROR_FPX_INVALID_TILE            = &H80000081  
Global Const DLG_ERROR_FPX_FILE_IN_USE             = &H80000082  
Global Const DLG_ERROR_FPX_FILE_CREATE_ERROR       = &H80000083
Global Const DLG_ERROR_FPX_FILE_NOT_OPEN_ERROR     = &H80000084
Global Const DLG_ERROR_FPX_USER_ABORT              = &H80000085
Global Const DLG_ERROR_FPX_OLE_FILE_ERROR          = &H80000086

Global Const DLG_ERROR_BAD_TAG                     = &H8000008C  
Global Const DLG_ERROR_INVALID_STAMP_SIZE          = &H8000008D  
Global Const DLG_ERROR_BAD_STAMP                   = &H8000008E  
Global Const DLG_ERROR_DOCUMENT_NOT_ENABLED        = &H8000008F  
Global Const DLG_ERROR_IMAGE_EMPTY                 = &H80000090  
Global Const DLG_ERROR_NO_CHANGE                   = &H80000091  
Global Const DLG_ERROR_LZW_LOCKED                  = &H80000092  
Global Const DLG_ERROR_FPXEXTENSIONS_LOCKED        = &H80000093 
Global Const DLG_ERROR_ANN_LOCKED                  = &H80000094

Global Const DLG_ERROR_DLG_CANCELED                = &H80000096    
Global Const DLG_ERROR_DLG_FAILED                  = &H80000097
