/**************************************************************************
 *FILETYPE:- header
 *FILE    :- crypkey.h
 *PURPOSE :- common functions and defines for the CrypKey Library
 *PROGRAM :- CrypKey Software Licensing System
 *LINKS   :- To any application that needs real protection
 *AUTHOR  :- James McCartney
 *COPYRTS :- Kenonic Controls, Calgary, Alberta
 *CREATED :- Feb 12, 1992
 *REVISED :- 08-11-92 [JSM]
               get_authorization(): must pass it a ptr to a long to get
                 the level
               init_crypkey(): returns 0 if ok, -1 if failure
               save_site_key(): one more error check - filewrite failure
             20-11-92 [JSM]
               added get_num_copies(),
               regisiter_site(), transfer_out(), transfer_in()
               added return code defines for last 3 functions above
             04-01-93 [JSM]
               added return codes for init_crypkey()
             17-08-94 [JSM]
               made this a version specifically for DLL
             25-05-95 [DJF]
               added an extra possible branch in
               #defining 'far' for use under Win32 ('s' and NT)
             28-08-95 [DJF]
               changed ckChalenge() support Win32;
               get_authorization2() added for languages that cannot
               pass integers by reference instead of by value;
               added extra error checks for init_crypkey();
               added two extra general errors
             28-05-96 [JSM]
               made changes to add RTT error codes to the system
 **************************************************************************/

#ifdef DLL
  #include "windows.h"
  #ifdef WIN32
    #define FUNCTYPE PASCAL
  #else
    #define FUNCTYPE PASCAL _export
  #endif
#else
  #define FUNCTYPE __cdecl
#endif

#ifdef __cplusplus
extern "C" {
#endif

/************************ Misc Defines ************************************/
#define ABS_MAX_USERS 127 // absolute maxiumum multi users on network

#define UCHAR unsigned char
#define ULONG unsigned long
#define UINT unsigned int
#ifndef USHORT
#define USHORT unsigned short
#endif
#define ONEDAY 86400
#define FALSE 0
#define TRUE 1

//[DJF] far pointers are not use in Win32, and named differently in MSC version 6.x
#ifdef WIN32
  #define far 
#elif (_MSC_VER <= 600)
  #define far  _far
#else
  #define far __far
#endif

/*********************** Program Defines **********************************/
/** restriction types **/
#define RESTR_NONE 0
#define RESTR_TIME 1
#define RESTR_RUNS 2

/** general error return codes ***/
//--NOTE: These errors can come from any function listed below
#define FILE_INFO_FAIL       -100
#define NETWORK_DISCONNECTED -101
#define NETWORK_NO_CKSERVE   -102
#define NETWORK_BAD_REPLY    -103
// currently only checked on Win32, DOS and Windows will add this saftey check later
#define INIT_NOT_SUCCEEDED   -104
#define THUNK_FAILURE        -105 // Can't find the thunk DLLs (only on Win32)
#define BAD_THUNK            -106 // DLL has been replaced with impostor
#define NO_MEMORY            -107 // some malloc did not work
#define OLD_THUNK            -108 // DLL has been replaced with older version
                                     //Or older version is already running
#define THUNK_BLOCKED        -109 // THUNK dll is being used but not released
                                  //  by another app

/** return codes for init_crypkey() **/
#define INIT_OK                      0
#define INIT_FILE_NOT_FOUND         -1
#define INIT_MASTERKEY_CRC_FAILURE  -2
#define INIT_BAD_PRODUCT_NAME       -3
#define INIT_KEYFILE_CREATION_FAIL  -4
#define INIT_NETWORK_NOT_PURCHASED  -5
#define INIT_NT_NOT_PURCHASED       -6
#define INIT_NT32BIT_NOT_PURCHASED  -7
#define INIT_WIN95_NOT_PURCHASED    -8
#define INIT_WIN32S_NOT_PURCHASED   -9
// currently only checked on Win32, DOS and Windows will add this saftey check later
#define INIT_MULTIPLE_CALL_TO_INIT  -10
#define INIT_THUNK_LIB_NOT_FOUND    -11  // only on Win32
#define INIT_THUNK32_DDL_CORRUPT    -12  // only on Win32
#define INIT_THUNK16_DDL_CORRUPT    -13  // only on Win32
#define INIT_32_DDL_CORRUPT         -14  // only on Win32

/** return codes for get authorization() **/
#define AUTH_OK                  0
#define AUTH_INIT_FAIL          -1
#define AUTH_DISALLOW_FLOPPY    -2
#define AUTH_BAD_PATH           -3
#define AUTH_NOT_PRESENT        -4
#define AUTH_DIFFERENT          -5
#define AUTH_BAD_MASTERKEY      -6
#define AUTH_SITEKEY_CRC        -7
#define AUTH_TIME_TOO_EARLY     -8
#define AUTH_TIME_SETBACK       -9
#define AUTH_TIME_RUNOUT        -10
#define AUTH_RUNS_RESTR         -11
#define AUTH_NOT_ENOUGH_RUNS    -12
#define MISSING_RST_FILE        -13
#define AUTH_MISSING_RST_FILE   -13
#define RST_BAD_CRC             -14
#define AUTH_RST_BAD_CRC        -14
#define RST_BAD_LOCATION        -15
#define AUTH_RST_BAD_LOCATION   -15
#define ENTRY_CHECK_FAIL        -16
#define AUTH_ENTRY_CHECK_FAIL   -16
#define AUTH_NETTABLEFILE_FAIL  -17
#define AUTH_NETMAX_EXCEEDED    -18
#define AUTH_NETWORK_NOT_ALLOWED -19
#define AUTH_RSTFILE_WRITE_PROTECT -20
#define AUTH_TIME_CLOCK_TAMPERING  -21

/** return codes for get_site_code() **/
#define GSC_OK                       0
#define GSC_CRYPKEY_NOT_INITIALIZED -1
#define GSC_ENTRY_FILEOPEN_FAIL     -2

/** return codes for save_site_key() **/
#define SITE_KEY_OK                 0
#define SITE_KEY_ENTRY_CHECK_FAIL  -1
#define SITE_KEY_ENTRY_CRC_FAIL    -2
#define SITE_KEY_FILEWRITE_FAILURE -3
#define SITE_KEY_NO_LICENSE_TO_ADD_TO -4

/** return codes for register_transfer() **/
#define REG_OK                             0
#define REG_THIS_ALREADY_AUTHORIZED       -1
#define REG_COULDNOT_OPEN_TARGET_REGFILE  -2
#define REG_TARGET_ALREADY_REGISTERED     -3
#define REG_SOURCE_ALREADY_REGISTERED     -4
#define REG_CANNOT_OPEN_REGFILE           -5
#define REG_CANNOT_WRITE_REGFILE          -6

/** return codes for transfer_out() **/
#define TO_OK                           0
#define TO_THIS_NOT_AUTHORIZED         -1
#define TO_REGFILE_NOT_FOUND           -2
#define TO_REGFILE_CRC_FAILURE         -3
#define TO_DIFFERENT_APPLICATION       -4
#define TO_TARGET_ALREADY_HAS_LICENSE  -5
#define TO_SITEKEYFILE_NOT_FOUND       -6
#define TO_COULDNOT_WRITE_SITEKEYFILE  -7
#define TO_RSTKEYFILE_NOT_FOUND        -8
#define TO_COULDNOT_WRITE_RSTKEYFILE   -9
#define TO_COULDNOT_WRITE_REGKEYFILE   -10
#define TO_SOURCE_WRITE_PROTECTED      -11

/** return codes for transfer_in() **/
#define TI_OK                            0
#define TI_THIS_ALREADY_AUTHORIZED      -1
#define TI_HARDDISK_REGFILE_NOT_FOUND   -2
#define TI_HARDDISK_REGFILE_CRC_FAILURE -3
#define TI_REGFILE_NOT_FOUND            -4
#define TI_REGFILE_CRC_FAILURE          -5
#define TI_HARDDISK_REGFILE_MOVED       -6
#define TI_REG_FILES_DONT_MATCH         -7
#define TI_SOURCE_HAS_NO_LICENSE        -8
#define TI_SITEKEYFILE_NOT_FOUND        -9
#define TI_DIFFERENT_SITEKEY            -10
#define TI_COULDNOT_WRITE_SITEKEYFILE   -11
#define TI_RSTKEYFILE_NOT_FOUND         -12
#define TI_DIFFERENT_RSTFILE            -13
#define TI_COULDNOT_WRITE_RSTKEYFILE    -14

/** return codes for direct_transfer() **/
#define DT_OK                            0
#define DT_THIS_NOT_AUTHORIZED          -1
#define DT_TARGET_APP_NOT_FOUND         -2
#define DT_FLOPPY_NOT_ALLOWED           -3
#define DT_SITEKEYFILE_NOT_FOUND        -4
#define DT_RSTKEYFILE_NOT_FOUND         -5
#define DT_COULDNOT_WRITE_SITEKEYFILE   -6
#define DT_SOURCE_WRITE_PROTECTED       -7
#define DT_SOURCE_SAME_AS_TARGET        -8

/** return codes for readyToTry() **/
/**Note - Most of these error codes will never be seen - they are only given
         so that you can report them to us if they occur. The only code you
         may be interested in is RTT_DONE_THIS, which will come up often,
         and signifies the trial license has already been given.
         If you get any other error, report it to us. **/

#define MAXRTT 120 //(This was not needed - NO LIMIT in VERSION4.3) for security 
                   //reasons, this was the max days/runs you could give
#define RTT_OK                           0
#define RTT_COULD_NOT_GET_SITE_CODE     -1
#define RTT_COULD_NOT_GET_SITE_KEY      -2
#define RTT_COULD_NOT_SAVE_SITE_KEY     -3
#define RTT_RESERVED_4                  -4
#define RTT_BAD_DOS                     -5
#define RTT_BAD_TRUENAME                -6
#define RTT_NO_REDIRECT                 -7
#define RTT_NO_DPB                      -8
#define RTT_NO_MEM                      -9
#define RTT_CANT_GET_CLUSTER            -10
#define RTT_BAD_STAT                    -11
#define RTT_NO_ROOM                     -12
#define RTT_BAD_SECTOR_READ             -13
#define RTT_BAD_SECTOR_WRITE            -14
#define RTT_FILE_SEARCH                 -15
#define RTT_FILE_ACCESS                 -16
#define RTT_FILE_NOT_FOUND              -17
#define RTT_FILE_OPEN                   -18
#define RTT_DONE_THIS                   -19
#define RTT_NO_SIG                      -20
#define RTT_NO_LISTFILE                 -21
#define RTT_CANT_FIND_DRIVE             -22
#define RTT_NO_GOOD_PUTS                -23
#define RTT_NO_REAL_DRIVE               -24
#define RTT_32BIT_FILE_ACCESS           -25
#define RTT_CLOSE_ALL_FILES             -26
#define RTT_MAX_RTTREQ_EXCEEDED         -27 //Max is currently set to 30 days or runs

/** return codes for KillLicense() **/
#define KL_OK                       0
#define KL_CRYPKEY_NOT_INITIALIZED -1
#define KL_CRYPKEY_NOT_AUTHORIZED  -2
#define KL_LICENSE_WRITE_PROTECTED -3

/** function codes for get1_rest_info() **/
#define G1_OUT_OF_RANGE              -1

/** function codes for get_num_copies() **/
#define GNC_CRYPKEY_NOT_INITIALIZED  -1

/** function codes for get_option() **/
#define OPTION_ON             1
#define OPTION_OFF            0
#define OPTION_UNAUTHORIZED  -1

/** function codes for get_restriction_info() **/
#define GRI_OK         0
#define GRI_INVALID   -1

/** function codes for explain_err() **/
#define EXP_AUTH_ERR            1  // get_authorization() errcodes
#define EXP_GET_SITECODE_ERR    2  // save_site_key() errcodes
#define EXP_SAVE_SITEKEY_ERR    3  // save_site_key() errcodes
#define EXP_REG_ERR             4  // register_transfer() errorcodes
#define EXP_TO_ERR              5  // transfer_out() errorcodes
#define EXP_TI_ERR              6  // transfer_in() errorcodes
#define EXP_DT_ERR              7  // direct_transfer() errorcodes
#define EXP_INIT_ERR            8  // init_crypkey() errorcodes
#define EXP_RTT_ERR             9  // readyToTry() errorcodes
#define EXP_KL_ERR              10  // readyToTry() errorcodes


/************************ Functions *************************************/

/** initialization **/

int FUNCTYPE init_crypkey(char far *filepath, char far *masterkey,
                          char far *userkey, int allow_floppy,
                          unsigned network_max_checktime);
void FUNCTYPE end_crypkey(void);

/** getting current authorization **/
int FUNCTYPE get_authorization(unsigned long far *level, int decrement);

// 28-08-95 [DJF] added to allow calls from languages that don't support
//          specifying pointers to integers (i.e. by reference, not value),
//          if it succeeds, get_level() and get_option() can then be used
int FUNCTYPE get_authorization2(int decrement);

/** killing current authorization **/
int FUNCTYPE KillLicense(char *confirmCode);

// 28-08-95 [DJF] changed to better support Win32
//UINT FUNCTYPE ckChallenge(UINT random1, UINT random2);
unsigned short FUNCTYPE ckChallenge(unsigned short random1, unsigned short random2);
long FUNCTYPE CKChallenge32(long random1, long random2);

char far * FUNCTYPE explain_err(int functioncode, int errcode);
int FUNCTYPE get_restriction_info(int far *authopt, ULONG far *start_date,
                                 int far *num_allowed, int far *num_used);
int FUNCTYPE get_num_copies(void);
int FUNCTYPE get_num_multi_users(void);

/** changing current authorization **/
int FUNCTYPE get_site_code(char far *site_code);
int FUNCTYPE save_site_key(char far *sitekey);

/** transfering license **/
int FUNCTYPE direct_transfer(char far *target);
int FUNCTYPE register_transfer(char far *target);
int FUNCTYPE transfer_out(char far *target);
int FUNCTYPE transfer_in(char far *target);

/** utility **/
char far * FUNCTYPE spc(char far *in);
void FUNCTYPE rmv_spc(char far *in);
extern ULONG FUNCTYPE systime(ULONG far *l);
int FUNCTYPE crypkeyVersion();

/**** Alternative Functions to help out  languages other than 'C' ***/
//Note these functions just give different ways of accessing the same info
//as the functions above

char * FUNCTYPE get_site_code2(void);
int FUNCTYPE get1_rest_info(int which);
void FUNCTYPE explain_err2(int func, int err, char *text);
int FUNCTYPE get_option(int numDefineOpts, int optnum);
unsigned long FUNCTYPE get_level(int numDefineOpts);

//New names for above functions + some new ones
int FUNCTYPE crypkeyVersion(void);
int FUNCTYPE DirectTransfer(char far *target);
void FUNCTYPE EndCrypkey(void);
char far * FUNCTYPE ExplainErr(int functioncode, int errcode);
void FUNCTYPE ExplainErr2(int func, int err, char *text);
int FUNCTYPE Get1RestInfo(int which);
int FUNCTYPE GetAuthorization(unsigned long *level, int decrement);
int FUNCTYPE GetAuthorization2(int decrement);
unsigned long FUNCTYPE GetLevel(int numDefineOpts);
unsigned short FUNCTYPE GetNetHandle(void);
int FUNCTYPE GetNumCopies(void);
int FUNCTYPE GetNumMultiUsers();
int FUNCTYPE GetOption(int numDefineOpts, int optnum);
int FUNCTYPE GetRestrictionInfo(int far *authopt, ULONG far *start_date, int far *num_allowed, int far *num_used);
int FUNCTYPE GetSiteCode(char far *site_code);
char * FUNCTYPE GetSiteCode2(void);
int FUNCTYPE InitCrypkey(char far *filepath, char far *masterkey, char far *userkey, int allow_floppy, unsigned network_max_checktime);
int FUNCTYPE readyToTry(unsigned long authlevel, int numDays);
int FUNCTYPE readyToTryDays(unsigned long authlevel, int numDays, int version, int copies);
int FUNCTYPE readyToTryRuns(unsigned long authlevel, int numRuns, int version, int copies);
int FUNCTYPE RegisterTransfer(char far *target);
int FUNCTYPE SaveSiteKey(char far *sitekey);
void FUNCTYPE SetNetHandle(unsigned short net_handle);
int FUNCTYPE TransferIn(char far *target);
int FUNCTYPE TransferOut(char far *target);
//these new names differ from old names only by case
#define ReadyToTryRuns readyToTryRuns
#define ReadyToTryDays readyToTryDays
#define ReadyToTry readyToTry
#define getNetHandle GetNetHandle
#define setNetHandle SetNetHandle
#define CrypkeyVersion crypkeyVersion
#define CKChallenge ckChallenge

#ifdef __cplusplus
}
#endif

