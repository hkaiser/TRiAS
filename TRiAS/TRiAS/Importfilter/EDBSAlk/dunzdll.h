// Copyright (c) 1993-1996 Inner Media, Inc., All Rights Reserved
// Function prototypes and structures for DynaZIP DUNZIP32.DLL.
// Message Callback Return Codes not part of standard Windows Message Box
#pragma pack(2)

//------------------------------------------------------------------------------------
// ZIPINFO Definitions 
#ifndef ZINFO
#define ZINFO

// Maximum sizes for ZIPINFO members
#define ZIPINFO_DATETIME_SIZE     18
#define ZIPINFO_FNAME_SIZE        260

// File attribute bits used in attr member of ZIPINFO structure
#define READONLY  0x00001L
#define HIDDEN    0x00002L
#define SYSTEM    0x00004L
#define VOLUME    0x00008L
#define SUBDIR    0x00010L
#define ARCHIVE   0x00020L
#define ENCRYPT   0x08000L
#define LFNAME    0x10000L

typedef struct {
  unsigned short index;
  unsigned long  oSize;
  unsigned long  cSize;
  unsigned short cMethod;
  unsigned short cOption;
  unsigned short cPathType;
  unsigned long crc_32;
  char szDateTime[ZIPINFO_DATETIME_SIZE];
  char szFileName[ZIPINFO_FNAME_SIZE];
  unsigned long attr;
  unsigned long  lziResv1;
  unsigned long  lziResv2;
} ZIPINFO;

#endif

//------------------------------------------------------------------------------------
// DynaZIP Rename Callback Structure
#ifndef DZR
#define DZR

typedef struct DZRENAME_tag{
  char Name[260];
  int  Date;
  int  Time;
  long Attr;
  char OrigName[260];
}DZRENAME;

#endif

//--------------------------------------------------------------------------------------------
// External Progress monitor
#ifndef DZSTATINFO
#define DZSTATINFO

typedef struct {
  unsigned long perc;
  char theString[352];
} STATINFO;

#endif

//------------------------------------------------------------------------------------
// DynaZIP UNZIP Function numbers used in function member of UNZIPCMDSTRUCT
#ifndef DZUNZIPACTIONS
#define DZUNZIPACTIONS

#define UNZIP_NOACTION              0
#define UNZIP_COUNTALLZIPMEMBERS    1
#define UNZIP_GETNEXTZIPINFO        2
#define UNZIP_COUNTNAMEDZIPMEMBERS  3
#define UNZIP_GETNEXTNAMEDZIPINFO   4
#define UNZIP_GETCOMMENTSIZE        5
#define UNZIP_GETCOMMENT            6
#define UNZIP_GETINDEXEDZIPINFO     7
#define UNZIP_EXTRACT               8 
#define UNZIP_FILETOMEM             9 

#endif

//------------------------------------------------------------------------------------
// Bit definitions used in wUnzipSubOptions member of UNZIPCMDSTRUCT
#ifndef DZUNZIPSUBOPTIONS
#define DZUNZIPSUBOPTIONS

#define USO_OVERWRITE_RO    0x0001
#define USO_MINORCANCEL     0x0002
#define USO_EXTERNALPROG    0x0004
#define USO_EXTPROGCANCEL   0x0008
#define USO_IGNORELONGNAMES 0x0010
#define USO_MANGLELONGNAMES 0x0020

#define USO_FORCEREMOVEABLE 0x0080
#define USO_LOGZIPRESULTS   0x0100

#endif

//------------------------------------------------------------------------------------
// Definition for the DynaZIP UNZIPCMDSTRUCT used to pass parameters to DUNZIP32.DLL
#ifndef UNZIPSTRUCT
#define UNZIPSTRUCT

typedef struct {
  int unzipStructSize;  
  int function;
  LPSTR lpszZIPFile;
  ZIPINFO FAR *zInfo;
  LPSTR lpszFilespec;
  int index;
  LPSTR lpszDestination;
  BOOL freshenFlag;
  BOOL updateFlag; 
  BOOL overWriteFlag;
  BOOL quietFlag;
  BOOL testFlag;
  BOOL noDirectoryNamesFlag;
  BOOL recurseFlag;
  BOOL noDirectoryItemsFlag;
  FARPROC lpMinorStatus;
  void FAR * lpMinorUserData;
  FARPROC lpMajorStatus;
  void FAR * lpMajorUserData;
  int returnCount;
  LPSTR lpszReturnString;
  BOOL bDiagnostic;
  BOOL bLF2CRLFFlag;
  BOOL  decryptFlag;
  LPSTR lpszDecryptCode;
  // added for rev 2.00
  FARPROC lpMessageDisplay;
  void FAR * lpMessageDisplayData;
  WORD wUnzipSubOptions;
  // added for rev 3.00
  long lResv1;
  long lResv2;
  FARPROC lpRenameProc;
  void FAR * lpRenameUserData;
  LPSTR lpszExtProgTitle;
  void FAR * lpMemBlock;
  long lMemBlockSize;
  long lStartingOffset;

}UNZIPCMDSTRUCT;

#endif

//------------------------------------------------------------------------------------
// Definitions for Structures used when calling DynaZIP DLLs direct from Visual Basic
#ifndef VBUNZIPBLOCKSTRUCT
#define VBUNZIPBLOCKSTRUCT

typedef struct{
  char szZIPFile[260];
  char szFileSpec[5120];
  char szDestination[260];
  char szReturnString[2048];
  char szDecryptCode[66];
  // New for Rev 3.00
  char szExtProgTitle[260];
}VBDUNZIPBLOCK;

#endif

//------------------------------------------------------------------------------------
// Visual Basic Status display definitions used with direct calls to DynaZIP DLLs
#ifndef VBSTATUSBLOCK
#define VBSTATUSBLOCK

typedef struct {
  HANDLE hMinorStat;
  HANDLE hMajorStat;
  // added for rev 2.00
  HANDLE hResv1;
  HANDLE hResv2;
}VBSTATBLK;

//------------------------------------------------------------------------------------
// Window messages and other definitions used by Custom DynaZIP Status Controls
#define WM_SETSTATUSBASEMSG     WM_USER+28
#define WM_GETSTATUSBASEMSG     WM_USER+29
#define WM_SETSTATUSPERCENT     WM_USER+30
#define WM_GETSTATUSPERCENT     WM_USER+31
#define WM_SHOWSTATUSWINDOW     WM_USER+32
#define WM_HIDESTATUSWINDOW     WM_USER+33
#define WM_GETCONTROLDATA       WM_USER+34
#define WM_SETCONTROLDATA       WM_USER+35
#define WM_GETCANCELFLAG        WM_USER+36
#define WM_SETCANCELFLAG        WM_USER+37 

// DynaZIP Status window misc defines
// ControlData bit mask definition
//  Bit  00 - Allow Bkgnd Processing    1 = allow bkgnd process / 0 = No bkgnd process allowed
//  Bit  01 - Allow Cancel              1 = allow Cancel        / 0 = No Cancel allowed
//  Bits 02 - 15                        reserved and undefined
//
#define CONTROLDATA_BKGNDPROC   0x01
#define CONTROLDATA_CANCEL      0x02
#define CONTROLDATA_MASK        0x03        


// Status Window FRAME extra words
#define WW_STATPERCENT          0
#define WW_STATPERCENT_OLD      2

#define STATUS_EXTRAS           4

#endif

//------------------------------------------------------------------------------------
// Definitions for Message Display Callback IDs 
#ifndef DZMESSAGEIDS
#define DZMESSAGEIDS

#define MSGID_DISK             0 
#define MSGID_DISKOFDISK       1
#define MSGID_ZOPEN            2
#define MSGID_ZREAD            3
#define MSGID_ZWRITE           4
#define MSGID_NOREMOVE         5
#define MSGID_SAMEVOL          6
#define MSGID_ZFORMAT          7
#define MSGID_OVERWRT          8
#define MSGID_CODEERR          9
#define MSGID_MVBADFIRSTDISK  10
#define MSGID_ERROR           11
#define MSGID_WARN            12
#define MSGID_CHANGE          13

#endif

//------------------------------------------------------------------------------------
// Definitions for Dialog Button IDs and Return Codes from DynaZIP default Dialogs
#ifndef DZDIALOGIDS
#define DZDIALOGIDS

#define IDYESTOALL        100
#define IDRENAME          101
#define MB_YESNOCANCELYTA 0x000F

#endif

//------------------------------------------------------------------------------------
// DynaZIP UNZIP Return codes
#ifndef DZUNZIPERRORCODES
#define DZUNZIPERRORCODES

#define UE_OK           0       // success
#define UE_EOF          2       // unexpected end of zip file
#define UE_STRUCT       3       // structure error in zip file
#define UE_MEM1         4       // out of memory
#define UE_MEM2         5       // out of memory
#define UE_NOFILE       9       // file not found error
#define UE_BORED        11      // nothing to do 
#define UE_SAMEVOL      12      // same volume for src and dest not allowed for multi-volume
#define UE_INDEX        25      // index out of bounds
#define UE_OUTPUT       28      // error creating output file
#define UE_OPEN         29      // error opening output file
#define UE_BADCRC       39      // crc error
#define UE_ABORT        40      // application cancelled operation
#define UE_ENCRYPT      41      // file skipped, encrypted
#define UE_UNKNOWN      42      // unknown compression method
#define UE_BADKEY       44      // bad or missing decrypt code
#define UE_BUSY         45      // re-entry not permitted
#define UE_NOVOL        46      // can't unzip a volume item
#define UE_CMDERR       47      // bad command structure
#define UE_CANCEL       48      // user cancelled this operation
#define UE_SKIP         49      // user skipped this operation
#define UE_DISKFULL     50      // disk full

#endif

//------------------------------------------------------------------------------------
// Functions exported by DynaZIP DUNZIP32.DLL
#ifndef DZUNZIPEXPORTS
#define DZUNZIPEXPORTS

#ifdef __cplusplus
extern "C" {
#endif

int  FAR PASCAL dunzip(UNZIPCMDSTRUCT FAR * ucs);
void FAR PASCAL setUnzipExternalCancel(BOOL bExtCancel);
BOOL FAR PASCAL getUnzipExternalCancel(void);
int  FAR PASCAL dunzipGetVerInfo(int iVerType, void FAR *pv);

#ifdef __cplusplus
}
#endif

#endif

#pragma pack()
