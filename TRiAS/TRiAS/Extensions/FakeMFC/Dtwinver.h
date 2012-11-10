/*
Module : DTWINVER.H
Purpose: Interface of a function to perform
         version detection on OS
Created: PJN / 11-05-1996

Copyright (c) 1996 - 2001 by PJ Naughter.  
All rights reserved.

*/

#ifndef __DTWINVER_H__                                          

////////////////////////////////// Includes ///////////////////////////////////


////////////////////////////////// defines ////////////////////////////////////

//values which get stored in [OS_VERSION_INFO].dwEmulatedPlatformId 
//and [OS_VERSION_INFO].dwUnderlyingPlatformId 
const DWORD DT_PLATFORM_DOS         = 1;
const DWORD DT_PLATFORM_WINDOWS3x   = 2;  
const DWORD DT_PLATFORM_WINDOWS9x   = 3;
const DWORD DT_PLATFORM_NT          = 4; 
const DWORD DT_PLATFORM_WINDOWSCE   = 5;

typedef struct _OS_VERSION_INFO
{
  //What version of OS is being emulated
  DWORD dwEmulatedMajorVersion;
  DWORD dwEmulatedMinorVersion;
  DWORD dwEmulatedBuildNumber;
  DWORD dwEmulatedPlatformId;
#ifdef _WIN32                    
  TCHAR szEmulatedCSDVersion[128];
#else
  char szEmulatedCSDVersion[128];
#endif  
  WORD wEmulatedServicePack;

  //What version of OS is really running                 
  DWORD dwUnderlyingMajorVersion;
  DWORD dwUnderlyingMinorVersion;
  DWORD dwUnderlyingBuildNumber;
  DWORD dwUnderlyingPlatformId;   
#ifdef _WIN32                      
  TCHAR szUnderlyingCSDVersion[128];
#else  
  char szUnderlyingCSDVersion[128];
#endif  
  WORD wUnderlyingServicePack;
} OS_VERSION_INFO, *POS_VERSION_INFO, FAR *LPOS_VERSION_INFO;


class COSVersion
{
public:
//Constructors / Destructors
  COSVersion(); 
  ~COSVersion();

//Methods:
  BOOL GetVersion(LPOS_VERSION_INFO lpVersionInformation);

//Please note that the return values for all the following functions 
//are mutually exclusive for example if you are running on 
//95 OSR2 then IsWindows95 will return FALSE
  BOOL IsWindows30(LPOS_VERSION_INFO lpVersionInformation);
  BOOL IsWindows31(LPOS_VERSION_INFO lpVersionInformation);
  BOOL IsWindows311(LPOS_VERSION_INFO lpVersionInformation);
  BOOL IsWindowsForWorkgroups(LPOS_VERSION_INFO lpVersionInformation);
  BOOL IsWindowsCE(LPOS_VERSION_INFO lpVersionInformation);
  BOOL IsWindows95(LPOS_VERSION_INFO lpVersionInformation);
  BOOL IsWindows95SP1(LPOS_VERSION_INFO lpVersionInformation);
  BOOL IsWindows95OSR2(LPOS_VERSION_INFO lpVersionInformation);
  BOOL IsWindows98(LPOS_VERSION_INFO lpVersionInformation);
  BOOL IsWindows98SP1(LPOS_VERSION_INFO lpVersionInformation);
  BOOL IsWindows98SE(LPOS_VERSION_INFO lpVersionInformation);
  BOOL IsWindowsME(LPOS_VERSION_INFO lpVersionInformation);
  BOOL IsWindowsNT31(LPOS_VERSION_INFO lpVersionInformation);
  BOOL IsWindowsNT35(LPOS_VERSION_INFO lpVersionInformation);
  BOOL IsWindowsNT351(LPOS_VERSION_INFO lpVersionInformation);
  BOOL IsWindowsNT4(LPOS_VERSION_INFO lpVersionInformation);
  BOOL IsWindows2000(LPOS_VERSION_INFO lpVersionInformation);
  BOOL IsWindowsXP(LPOS_VERSION_INFO lpVersionInformation);

//Returns the various flavours of the "os" that is installed. Note that these
//functions are not completely mutually exlusive
  BOOL IsWin32sInstalled(LPOS_VERSION_INFO lpVersionInformation);
  BOOL IsNTPreWin2k(LPOS_VERSION_INFO lpVersionInformation);

  BOOL IsNTWorkstation(LPOS_VERSION_INFO lpVersionInformation);
  BOOL IsNTStandAloneServer(LPOS_VERSION_INFO lpVersionInformation);
  BOOL IsNTPDC(LPOS_VERSION_INFO lpVersionInformation);
  BOOL IsNTBDC(LPOS_VERSION_INFO lpVersionInformation);
  BOOL IsNTEnterpriseServer(LPOS_VERSION_INFO lpVersionInformation);
  BOOL IsNTDatacenterServer(LPOS_VERSION_INFO lpVersionInformation);

  BOOL IsWin2000Professional(LPOS_VERSION_INFO lpVersionInformation);
  BOOL IsWin2000Server(LPOS_VERSION_INFO lpVersionInformation);
  BOOL IsWin2000AdvancedServer(LPOS_VERSION_INFO lpVersionInformation);
  BOOL IsWin2000DatacenterServer(LPOS_VERSION_INFO lpVersionInformation);
  BOOL IsWin2000DomainController(LPOS_VERSION_INFO lpVersionInformation);

  BOOL IsXPPersonal(LPOS_VERSION_INFO lpVersionInformation);
  BOOL IsXPProfessional(LPOS_VERSION_INFO lpVersionInformation);
  BOOL IsXPServer(LPOS_VERSION_INFO lpVersionInformation);
  BOOL IsXPAdvancedServer(LPOS_VERSION_INFO lpVersionInformation);
  BOOL IsXPDatacenterServer(LPOS_VERSION_INFO lpVersionInformation);
  BOOL IsXPDomainController(LPOS_VERSION_INFO lpVersionInformation);

  BOOL IsTerminalServicesInstalled(LPOS_VERSION_INFO lpVersionInformation);
  BOOL ISSmallBusinessEditionInstalled(LPOS_VERSION_INFO lpVersionInformation);
  BOOL Is64Bit(LPOS_VERSION_INFO lpVersionInformation);

protected:
#if !defined(_WIN32) && !defined(_WIN64)
//Defines / typedefs
  #define LPTSTR LPSTR

  typedef struct _OSVERSIONINFO
  { 
    DWORD dwOSVersionInfoSize; 
    DWORD dwMajorVersion; 
    DWORD dwMinorVersion; 
    DWORD dwBuildNumber; 
    DWORD dwPlatformId; 
    char szCSDVersion[128]; 
  } OSVERSIONINFO, *POSVERSIONINFO, FAR *LPOSVERSIONINFO; 
  
  #define CPEX_DEST_STDCALL        0x00000000L
  #define HKEY32                   DWORD                                                               
  #define HKEY_LOCAL_MACHINE       (( HKEY32 ) 0x80000002 )    
  #define TCHAR                    char
  #define _T
  #define _tcsicmp                 strcmpi
  #define _tcscpy                  strcpy
  #define _tcslen                  strlen
  #define _istdigit                isdigit
  #define _ttoi                    atoi
  #define _tcsupr                  strupr
  #define _tcsstr                  strstr
  #define LPCTSTR                  LPCSTR
  #define ERROR_CALL_NOT_IMPLEMENTED  120
  #define REG_DWORD                ( 4 )                                                               
  #define REG_MULTI_SZ             ( 7 )
  #define VER_PLATFORM_WIN32s             0
  #define VER_PLATFORM_WIN32_WINDOWS      1
  #define VER_PLATFORM_WIN32_NT           2
  #define VER_PLATFORM_WIN32_CE           3

//static methods
  static DWORD GetVersion();
  static BOOL GetVersionEx(LPOSVERSIONINFO lpVersionInfo);
  static LONG RegQueryValueEx(HKEY32 hKey, LPSTR  lpszValueName, LPDWORD lpdwReserved, LPDWORD lpdwType, LPBYTE  lpbData, LPDWORD lpcbData);
#if defined(_WINDOWS) && (!defined(_WIN32) && !defined(_WIN64))  
  static BOOL WFWLoaded();                                     
#endif //defined(_WINDOWS) && (!defined(_WIN32) && !defined(_WIN64))    

  typedef DWORD (FAR PASCAL  *lpfnLoadLibraryEx32W) (LPCSTR, DWORD, DWORD);
  typedef BOOL  (FAR PASCAL  *lpfnFreeLibrary32W)   (DWORD);
  typedef DWORD (FAR PASCAL  *lpfnGetProcAddress32W)(DWORD, LPCSTR);
  typedef DWORD (FAR __cdecl *lpfnCallProcEx32W)    (DWORD, DWORD, DWORD, DWORD, ...);
  typedef WORD  (FAR PASCAL  *lpfnWNetGetCaps)      (WORD);

//Static member variables
  static DWORD                 sm_dwRefCount;
  static lpfnLoadLibraryEx32W  sm_lpfnLoadLibraryEx32W;
  static lpfnFreeLibrary32W    sm_lpfnFreeLibrary32W;
  static lpfnGetProcAddress32W sm_lpfnGetProcAddress32W;
  static lpfnCallProcEx32W     sm_lpfnCallProcEx32W;
  static DWORD                 sm_hAdvApi32;    
  static DWORD                 sm_hKernel32;
  static DWORD                 sm_lpfnRegQueryValueExA;
  static DWORD                 sm_lpfnGetVersionExA;
  static DWORD                 sm_lpfnGetVersion;
#endif //defined(_WINDOWS) && (!defined(_WIN32) && !defined(_WIN64))

  typedef BOOL (WINAPI *lpfnGetVersionEx) (LPOSVERSIONINFO);  

  //General methods
  BOOL WhichNTProduct(TCHAR* pszProductType);
  BOOL ValidateProductSuite(LPCTSTR lpszSuiteToValidate);
  WORD GetNTServicePackFromRegistry();
  WORD GetNTServicePackFromCSDString(LPCTSTR pszCSDVersion);
};


#endif //__DTWINVER_H__