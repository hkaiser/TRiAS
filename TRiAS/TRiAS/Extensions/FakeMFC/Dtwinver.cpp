/*
Module : Dtwinver.cpp
Purpose: Implementation of a comprehensive function to perform OS version detection
Created: PJN / 11-05-1996
History: PJN / 24-02-1997 A number of updates including support for NT 3.1, 
                          single mode dos in Windows 95 and better Windows
                          version detecion under real mode dos.
         PJN / 13-09-1998 1.  Added explicit support for Windows 98 
                          2.  Updated documentation to use HTML. 
                          3.  Minor update to the web page describing it. 
         PJN / 22-06-1999 1.  UNICODE enabled the code.
                          2.  Removed need for the dwOSVersionInfoSize variable
                          3.  Added support for detecting Build Number of 95 and 98 from DOS code path.
                          4.  Now ships as standard with VC 5 workspace files
                          5.  Added explicit support for Windows 95 SP 1
                          6.  Added explicit support for Windows 95 OSR 2
                          7.  Added explicit support for Windows 98 Second Edition
                          8.  Added explicit support for Windows 2000
                          9.  Added explicit support for Windows CE
                          10. Added explicit support for Windows Terminal Server's
                          11. Added explicit support for NT Stand Alone Server's.
                          12. Added explicit support for NT Primary Domain Controller's
                          13. Added explicit support for NT Backup Domain Controller's
         PJN / 23-07-1999 Tested out support for Windows 98 SE, minor changes required
         PJN / 26-07-1999 Added explicit support for Windows 98 SP 1
         PJN / 28-07-1999 1. Fixed a problem when application is build in non-huge/large 
                          memory model in Win16
                          2. Added explicit support for returning NT and Win9x service pack information 
                          from Win32 and Win16 code paths
                          3. Updated test program to not bother reporting on any info which does not 
                          exist. e.g. if there is no service pack installed, then we don't bother 
                          displaying any info about service packs
                          4. Added explicit support for NT Enterprise Edition
         PJN / 30-06-2000 1. Added explicit support for Windows Millennium Edition
         PJN / 29-01-2001 1.  Added explicit support for Windows XP (Whistler) Personal
                          2.  Added explicit support for Windows XP (Whistler) Professional
                          3.  Added explicit support for Windows XP (Whistler) Server
                          4.  Added explicit support for Windows XP (Whistler) Advanced Server
                          5.  Added explicit support for Windows XP (Whistler) Datacenter
                          6.  Added explicit support for Windows XP (Whistler) 64 bit (all flavours)
                          7.  Made all the code into a C++ class called COSVersion
                          8.  Rewrote all the generic thunk code to be easier to follow
                          9. Generic think code now uses CallProcEx32W
                          10.  Added explicit support for BackOffice Small Business Edition
                          11. Added explicit support for Terminal Services
                          12. 16 bit code path now can determine ProductSuite and ProductType type
                          thro additional generic thunk code
                          13. Provided a 64 bit test binary and make batch file (make64.bat) for 
                          those lucky enough to have an Itanium processor and a beta of 64 bit Windows XP (Whistler).
                          14. Provided a Embedded C++ workspace and X86 Release binary.
                          15. Updated copyright information           
         PJN / 10-02-2001 1. Updated function names etc following MS decision to call Whistler "Windows XP"


Copyright (c) 1997 - 2001 by PJ Naughter.  (Web: www.naughter.com, Email: pjna@naughter.com)

All rights reserved.

Copyright / Usage Details:

You are allowed to include the source code in any product (commercial, shareware, freeware or otherwise) 
when your product is released in binary form. You are allowed to modify the source code in any way you want 
except you cannot modify the copyright details at the top of each module. If you want to distribute source 
code with your application, then you are only allowed to distribute versions released by the author. This is 
to maintain a single distribution point for the source code. 
*/


/////////////////////////////////  Includes  //////////////////////////////////
#include <StdAfx.h>

#include "dtwinver.h"


/////////////////////////////////  Local function / variables /////////////////

#if defined(_WIN32)

//Taken from Windows CE winbase.h file
#ifndef VER_PLATFORM_WIN32_CE
  #define VER_PLATFORM_WIN32_CE         3
#endif

#endif //defined(_WIN32) 

#if defined(_WINDOWS) && (!defined(_WIN32) && !defined(_WIN64))  //required for universal thunks
  DWORD COSVersion::sm_dwRefCount = 0;
  COSVersion::lpfnLoadLibraryEx32W COSVersion::sm_lpfnLoadLibraryEx32W = NULL;
  COSVersion::lpfnFreeLibrary32W COSVersion::sm_lpfnFreeLibrary32W = NULL;
  COSVersion::lpfnGetProcAddress32W COSVersion::sm_lpfnGetProcAddress32W = NULL;
  COSVersion::lpfnCallProcEx32W COSVersion::sm_lpfnCallProcEx32W = NULL;
  DWORD COSVersion::sm_hAdvApi32 = 0;    
  DWORD COSVersion::sm_hKernel32 = 0;
  DWORD COSVersion::sm_lpfnRegQueryValueExA= 0;
  DWORD COSVersion::sm_lpfnGetVersionExA = 0;
  DWORD COSVersion::sm_lpfnGetVersion = 0;
#endif //defined(_WINDOWS) && !defined(_WIN32)

#ifdef _DOS
  WORD WinVer;
  BYTE bRunningWindows;
  void GetWinInfo();
#endif //ifdef _DOS



////////////////////////////////// Implementation /////////////////////////////
COSVersion::COSVersion()
{
#if defined(_WINDOWS) && (!defined(_WIN32) && !defined(_WIN64))
  if (sm_dwRefCount == 0)
  {
    // Get Kernel dll handle
    HMODULE hKernel = GetModuleHandle("KERNEL");
    if (hKernel)
    {
      // Dynamically link to the functions we want, setting the capability
      sm_lpfnLoadLibraryEx32W  = (lpfnLoadLibraryEx32W)  GetProcAddress(hKernel, "LoadLibraryEx32W");
      sm_lpfnFreeLibrary32W    = (lpfnFreeLibrary32W)    GetProcAddress(hKernel, "FreeLibrary32W");
      sm_lpfnGetProcAddress32W = (lpfnGetProcAddress32W) GetProcAddress(hKernel, "GetProcAddress32W");
      sm_lpfnCallProcEx32W     = (lpfnCallProcEx32W)     GetProcAddress(hKernel, "_CallProcEx32W");
      if (sm_lpfnLoadLibraryEx32W && sm_lpfnFreeLibrary32W)
      {
        sm_hAdvApi32 = sm_lpfnLoadLibraryEx32W("ADVAPI32.DLL", NULL, 0);
        if (sm_hAdvApi32)                                                   
          sm_lpfnRegQueryValueExA = sm_lpfnGetProcAddress32W(sm_hAdvApi32, "RegQueryValueExA"); 
        sm_hKernel32 = sm_lpfnLoadLibraryEx32W("KERNEL32.DLL", NULL, 0);
        if (sm_hKernel32)
        {                                                               
          sm_lpfnGetVersionExA = sm_lpfnGetProcAddress32W(sm_hKernel32, "GetVersionExA");
          sm_lpfnGetVersion = sm_lpfnGetProcAddress32W(sm_hKernel32, "GetVersion");
        }
      }
    }
  }
  ++sm_dwRefCount;
#endif
}

COSVersion::~COSVersion()
{                        
#if defined(_WINDOWS) && (!defined(_WIN32) && !defined(_WIN64))
  --sm_dwRefCount;
  if (sm_dwRefCount == 0)
  {
    if (sm_lpfnFreeLibrary32W)
    {           
      if (sm_hAdvApi32)
        sm_lpfnFreeLibrary32W(sm_hAdvApi32);
      if (sm_hKernel32)
        sm_lpfnFreeLibrary32W(sm_hKernel32);
    }
  }
#endif
}


#if defined(_WINDOWS) && (!defined(_WIN32) && !defined(_WIN64))
BOOL COSVersion::WFWLoaded()
{
  const WORD WNNC_NET_MultiNet         = 0x8000;
  const WORD WNNC_SUBNET_WinWorkgroups = 0x0004;
  const WORD WNNC_NET_TYPE             = 0x0002;
  BOOL rVal;
   
  HINSTANCE hUserInst = LoadLibrary("USER.EXE");
  lpfnWNetGetCaps lpWNetGetCaps = (lpfnWNetGetCaps) GetProcAddress(hUserInst, "WNetGetCaps");
  if (lpWNetGetCaps != NULL)
  {
    // Get the network type
    WORD wNetType = lpWNetGetCaps(WNNC_NET_TYPE);
    if (wNetType & WNNC_NET_MultiNet)
    {
      // a multinet driver is installed
      if (LOBYTE(wNetType) & WNNC_SUBNET_WinWorkgroups) // It is WFW
        rVal = TRUE;
      else // It is not WFW
        rVal = FALSE;
    }
    else
     rVal = FALSE;
  }
  else
    rVal = FALSE;
   
  // Clean up the module instance
  if (hUserInst)
    FreeLibrary(hUserInst);
    
  return rVal;  
}

LONG COSVersion::RegQueryValueEx(HKEY32 hKey, LPSTR  lpszValueName, LPDWORD lpdwReserved, LPDWORD lpdwType, LPBYTE  lpbData, LPDWORD lpcbData)
{                                             
  //Assume the worst
  DWORD dwResult = ERROR_CALL_NOT_IMPLEMENTED;

  if (sm_lpfnRegQueryValueExA)
    dwResult = sm_lpfnCallProcEx32W(CPEX_DEST_STDCALL | 6, 0x3e, sm_lpfnRegQueryValueExA, hKey, lpszValueName, lpdwReserved, lpdwType, lpbData, lpcbData);

  return dwResult;
}                 

BOOL COSVersion::GetVersionEx(LPOSVERSIONINFO lpVersionInfo)
{
  //Assume the worst
  BOOL bSuccess = FALSE;

  if (sm_lpfnGetVersionExA)
    bSuccess = (BOOL) sm_lpfnCallProcEx32W(CPEX_DEST_STDCALL | 1, 1, sm_lpfnGetVersionExA, lpVersionInfo, 0);

  return bSuccess;
}

DWORD COSVersion::GetVersion()
{
  //Assume the worst
  DWORD dwVersion = 0;

  if (sm_lpfnGetVersion)
    dwVersion = (BOOL) sm_lpfnCallProcEx32W(CPEX_DEST_STDCALL | 0, 0, sm_lpfnGetVersion, 0);

  return dwVersion;
}
#endif //defined(_WINDOWS) && !defined(_WIN32)

BOOL COSVersion::GetVersion(LPOS_VERSION_INFO lpVersionInformation)
{                
  //By Default assume no service pack is installed
  lpVersionInformation->wEmulatedServicePack = 0;
  lpVersionInformation->wUnderlyingServicePack = 0;

  #ifdef UNDER_CE
    OSVERSIONINFO osvi;
    memset(&osvi, 0, sizeof(OSVERSIONINFO));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    if (!GetVersionEx(&osvi))
      return FALSE;

    lpVersionInformation->dwEmulatedMajorVersion = osvi.dwMajorVersion; 
    lpVersionInformation->dwEmulatedMinorVersion = osvi.dwMinorVersion; 
    lpVersionInformation->dwEmulatedBuildNumber = LOWORD(osvi.dwBuildNumber); //ignore HIWORD
    _tcscpy(lpVersionInformation->szEmulatedCSDVersion, osvi.szCSDVersion);
    lpVersionInformation->dwEmulatedPlatformId = DT_PLATFORM_WINDOWSCE;

    //underlying OS is the same
    lpVersionInformation->dwUnderlyingMajorVersion = lpVersionInformation->dwEmulatedMajorVersion; 
    lpVersionInformation->dwUnderlyingMinorVersion = lpVersionInformation->dwEmulatedMinorVersion; 
    lpVersionInformation->dwUnderlyingBuildNumber = lpVersionInformation->dwEmulatedBuildNumber;
    lpVersionInformation->dwUnderlyingPlatformId = lpVersionInformation->dwEmulatedPlatformId;
    _tcscpy(lpVersionInformation->szUnderlyingCSDVersion, lpVersionInformation->szEmulatedCSDVersion);
  #elif defined(_WIN32) || defined(_WIN64)
    //determine dynamically if GetVersionEx is available, if 
    //not then drop back to using GetVersion

    // Get Kernel handle
    HMODULE hKernel32 = GetModuleHandle(_T("KERNEL32.DLL"));
    if (hKernel32 == NULL)
      return FALSE;

    #ifdef _UNICODE
      lpfnGetVersionEx lpGetVersionEx = (lpfnGetVersionEx) GetProcAddress(hKernel32, "GetVersionExW");
    #else
      lpfnGetVersionEx lpGetVersionEx = (lpfnGetVersionEx) GetProcAddress(hKernel32, "GetVersionExA");
    #endif

    if (lpGetVersionEx)
    {
      OSVERSIONINFO osvi;
      memset(&osvi, 0, sizeof(OSVERSIONINFO));
      osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
      if (!lpGetVersionEx(&osvi))
        return FALSE;

      lpVersionInformation->dwEmulatedMajorVersion = osvi.dwMajorVersion; 
      lpVersionInformation->dwEmulatedMinorVersion = osvi.dwMinorVersion; 
      lpVersionInformation->dwEmulatedBuildNumber = LOWORD(osvi.dwBuildNumber); //ignore HIWORD
      _tcscpy(lpVersionInformation->szEmulatedCSDVersion, osvi.szCSDVersion);
    
      //Explicitely map the win32 dwPlatformId to our own values 
      //Also work out the various service packs which are installed
      if (osvi.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS)
      {
        lpVersionInformation->dwEmulatedPlatformId = DT_PLATFORM_WINDOWS9x;

        //Deterine the Win9x Service pack installed
        if (IsWindows95SP1(lpVersionInformation))
        {
          lpVersionInformation->wEmulatedServicePack = 1;
          lpVersionInformation->wUnderlyingServicePack = 1;
        }
        else if (IsWindows95OSR2(lpVersionInformation))
        {
          lpVersionInformation->wEmulatedServicePack = 2;
          lpVersionInformation->wUnderlyingServicePack = 2;
        }
        else if (IsWindows98SP1(lpVersionInformation))
        {
          lpVersionInformation->wEmulatedServicePack = 1;
          lpVersionInformation->wUnderlyingServicePack = 1;
        }
      }
      else if (osvi.dwPlatformId == VER_PLATFORM_WIN32_NT)
      {
        lpVersionInformation->dwEmulatedPlatformId = DT_PLATFORM_NT;

        //Determine the NT Service pack
        lpVersionInformation->wEmulatedServicePack = GetNTServicePackFromCSDString(osvi.szCSDVersion);
        lpVersionInformation->wUnderlyingServicePack = lpVersionInformation->wEmulatedServicePack;
      }
      else if (osvi.dwPlatformId == VER_PLATFORM_WIN32_CE)
        lpVersionInformation->dwEmulatedPlatformId = DT_PLATFORM_WINDOWSCE;

      if (osvi.dwPlatformId == VER_PLATFORM_WIN32s)  //32 bit app running on Windows 3.x
      {
        lpVersionInformation->dwEmulatedPlatformId = DT_PLATFORM_WINDOWS9x;

        lpVersionInformation->dwUnderlyingMajorVersion = 3; 
        lpVersionInformation->dwUnderlyingMinorVersion = 10; 
        lpVersionInformation->dwUnderlyingBuildNumber = 0;
        lpVersionInformation->dwUnderlyingPlatformId = DT_PLATFORM_WINDOWS3x;
        _tcscpy(lpVersionInformation->szUnderlyingCSDVersion, _T(""));
      }
      else
      {
        lpVersionInformation->dwUnderlyingMajorVersion = lpVersionInformation->dwEmulatedMajorVersion; 
        lpVersionInformation->dwUnderlyingMinorVersion = lpVersionInformation->dwEmulatedMinorVersion; 
        lpVersionInformation->dwUnderlyingBuildNumber = lpVersionInformation->dwEmulatedBuildNumber;
        lpVersionInformation->dwUnderlyingPlatformId = lpVersionInformation->dwEmulatedPlatformId;
        _tcscpy(lpVersionInformation->szUnderlyingCSDVersion, lpVersionInformation->szEmulatedCSDVersion);
      }
    }
    else
    {
      //Since GetVersionEx is not available we need to fall back on plain
      //old GetVersion. Because GetVersionEx is available on all but v3.1 of NT
      //we can fill in some of the parameters ourselves.
      DWORD dwVersion = ::GetVersion();

      lpVersionInformation->dwEmulatedMajorVersion =  (DWORD)(LOBYTE(LOWORD(dwVersion)));
      lpVersionInformation->dwEmulatedMinorVersion =  (DWORD)(HIBYTE(LOWORD(dwVersion)));
      lpVersionInformation->dwEmulatedBuildNumber = 0;
      lpVersionInformation->dwEmulatedPlatformId   = DT_PLATFORM_NT;   
      lpVersionInformation->dwUnderlyingMajorVersion = lpVersionInformation->dwEmulatedMajorVersion;
      lpVersionInformation->dwUnderlyingMinorVersion = lpVersionInformation->dwEmulatedMinorVersion;
      lpVersionInformation->dwUnderlyingBuildNumber  = lpVersionInformation->dwEmulatedBuildNumber;
      lpVersionInformation->dwUnderlyingPlatformId   = lpVersionInformation->dwEmulatedPlatformId;   
      _tcscpy(lpVersionInformation->szUnderlyingCSDVersion, lpVersionInformation->szEmulatedCSDVersion);

      //Need to determine the NT Service pack by querying the registry directory.
      lpVersionInformation->wEmulatedServicePack = GetNTServicePackFromRegistry();
      lpVersionInformation->wUnderlyingServicePack = lpVersionInformation->wEmulatedServicePack;
    }
  #else //We must be runing on an emulated or real version of Win16 or DOS
    #ifdef _WINDOWS //Running on some version of Windows                   
      DWORD dwVersion = GetVersion();
      // GetVersion does not differentiate between Windows 3.1 and Windows 3.11
      
      lpVersionInformation->dwEmulatedMajorVersion = LOBYTE(LOWORD(dwVersion)); 
      lpVersionInformation->dwEmulatedMinorVersion = HIBYTE(LOWORD(dwVersion));
      lpVersionInformation->dwEmulatedBuildNumber  = 0; //no build number with Win3.1x
      lpVersionInformation->dwEmulatedPlatformId   = DT_PLATFORM_WINDOWS3x;
      
      //Call to get the underlying OS here through 16 -> 32 bit Generic Thunk
      BOOL bFoundUnderlyingOS = FALSE;
      OSVERSIONINFO osvi;                      
      memset(&osvi, 0, sizeof(OSVERSIONINFO));
      osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
      if (GetVersionEx(&osvi))
      {
        lpVersionInformation->dwUnderlyingMajorVersion = osvi.dwMajorVersion; 
        lpVersionInformation->dwUnderlyingMinorVersion = osvi.dwMinorVersion; 
        lpVersionInformation->dwUnderlyingBuildNumber = LOWORD(osvi.dwBuildNumber); //ignore HIWORD
        _fstrcpy(lpVersionInformation->szUnderlyingCSDVersion, osvi.szCSDVersion);
       
        //Explicitely map the win32 dwPlatformId to our own values
        if (osvi.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS)
        {
          lpVersionInformation->dwUnderlyingPlatformId = DT_PLATFORM_WINDOWS9x;

          //Deterine the Win9x Service pack installed
          if (IsWindows95SP1(lpVersionInformation))
            lpVersionInformation->wUnderlyingServicePack = 1;
          else if (IsWindows95OSR2(lpVersionInformation))
            lpVersionInformation->wUnderlyingServicePack = 2;
          else if (IsWindows98SP1(lpVersionInformation))
            lpVersionInformation->wUnderlyingServicePack = 1;
        }
        else if (osvi.dwPlatformId == VER_PLATFORM_WIN32_NT)
        {
          lpVersionInformation->dwUnderlyingPlatformId = DT_PLATFORM_NT;
  
          //Determine the NT Service pack
          lpVersionInformation->wUnderlyingServicePack = GetNTServicePackFromCSDString(osvi.szCSDVersion);
        }
        else
          return FALSE;
       
        bFoundUnderlyingOS = TRUE;
      }
      else
      {
        //We failed to get GetVersionEx so try to GetVersion instead. We known that we must be on
        //Windows NT 3.5 or earlier since anything released later by MS had this function.
        DWORD dwVersion = GetVersion();
        if (dwVersion)
        {              
          lpVersionInformation->dwUnderlyingMajorVersion = (DWORD)(LOBYTE(LOWORD(dwVersion)));
          lpVersionInformation->dwUnderlyingMinorVersion = (DWORD)(HIBYTE(LOWORD(dwVersion)));
          lpVersionInformation->dwUnderlyingBuildNumber  = 0;
          lpVersionInformation->dwUnderlyingPlatformId   = DT_PLATFORM_NT; 
          _fstrcpy(lpVersionInformation->szUnderlyingCSDVersion, "");
   
          bFoundUnderlyingOS = TRUE;
        }
      }

      if (!bFoundUnderlyingOS)
      {
        //must be running on a real version of 16 bit Windows whose underlying OS is DOS
        lpVersionInformation->dwUnderlyingMajorVersion = HIBYTE(HIWORD(dwVersion)); 
        lpVersionInformation->dwUnderlyingMinorVersion = LOBYTE(HIWORD(dwVersion)); 
        lpVersionInformation->dwUnderlyingBuildNumber = 0; 
        lpVersionInformation->dwUnderlyingPlatformId = DT_PLATFORM_DOS;
        _fstrcpy(lpVersionInformation->szUnderlyingCSDVersion, "");
      }
    #else //Must be some version of real or emulated DOS
      //Retreive the current version of emulated DOS
      BYTE DosMinor;
      BYTE DosMajor;
      _asm
      {
        mov ax, 3306h
        int 21h
        mov byte ptr [DosMajor], bl
        mov byte ptr [DosMinor], bh
      }
      lpVersionInformation->dwEmulatedPlatformId = DT_PLATFORM_DOS;
      lpVersionInformation->dwEmulatedMajorVersion = (DWORD) DosMajor; 
      lpVersionInformation->dwEmulatedMinorVersion = (DWORD) DosMinor;                
      lpVersionInformation->dwEmulatedBuildNumber = 0; //no build number with DOS

      //We can detect if NT is running as it reports DOS v5.5
      if ((lpVersionInformation->dwEmulatedMajorVersion == 5) &&
          (lpVersionInformation->dwEmulatedMinorVersion == 50))    //NT reports DOS v5.5
      {
        _fstrcpy(lpVersionInformation->szUnderlyingCSDVersion, "Microsoft Windows NT");    
        //could not find method of determing version of NT from DOS,
        //so assume 3.50
        lpVersionInformation->dwUnderlyingMajorVersion = 3; 
        lpVersionInformation->dwUnderlyingMinorVersion = 50; 
        lpVersionInformation->dwUnderlyingBuildNumber = 0;  //cannot get access to build number from DOS
        lpVersionInformation->dwUnderlyingPlatformId = DT_PLATFORM_NT;
      }            
      else
      {
        //Get the underlying OS here via the int 2FH interface of Windows
        GetWinInfo();
        if (bRunningWindows)
        { 
          if (lpVersionInformation->dwEmulatedMajorVersion >= 7)  //Windows 9x marks itself as DOS 7 or DOS 8
            lpVersionInformation->dwUnderlyingPlatformId = DT_PLATFORM_WINDOWS9x;
          else                                                              
          {
            //Could not find method of differentiating between WFW & Win3.1 under DOS,
            //so assume Win3.1                                     
            lpVersionInformation->dwUnderlyingPlatformId = DT_PLATFORM_WINDOWS3x;      
          }  
          _fstrcpy(lpVersionInformation->szUnderlyingCSDVersion, "Microsoft Windows");
          lpVersionInformation->dwUnderlyingMajorVersion = (WinVer & 0xFF00) >> 8; 
          lpVersionInformation->dwUnderlyingMinorVersion = WinVer & 0x00FF; 

          if (lpVersionInformation->dwEmulatedMajorVersion >= 8)  //Windows Me reports itself as DOS v8.0
            lpVersionInformation->dwUnderlyingBuildNumber = 3000; //This is the build number for Windows ME.
          else
          {
            if (lpVersionInformation->dwEmulatedMinorVersion == 0)
              lpVersionInformation->dwUnderlyingBuildNumber = 950; //Windows 95 Gold reports DOS v7.0                      
            else if (lpVersionInformation->dwUnderlyingMinorVersion > 0 && 
                     lpVersionInformation->dwUnderlyingMinorVersion < 3) 
            {                                                            
              //Testing for 95 SP1 has not been done, so the above check
              //may or may not work
              lpVersionInformation->dwUnderlyingBuildNumber = 1080; 
            }
            else if (lpVersionInformation->dwUnderlyingMinorVersion == 3)
              lpVersionInformation->dwUnderlyingBuildNumber = 1212; //Windows 95 OSR2 reports DOS 7.03 from 16 bit code
            else
              lpVersionInformation->dwUnderlyingBuildNumber = 1998; //Windows 98 or SE. There is no way to differentiate from real mode
                                                                    //between the two of them
          }
        }
        else //must be on a real version of DOS
        {                               
          lpVersionInformation->dwUnderlyingMajorVersion = (DWORD) DosMajor; 
          lpVersionInformation->dwUnderlyingMinorVersion = (DWORD) DosMinor;                
          lpVersionInformation->dwUnderlyingBuildNumber = 0; //no build number with DOS
          lpVersionInformation->dwUnderlyingPlatformId = DT_PLATFORM_DOS;
          _fstrcpy(lpVersionInformation->szUnderlyingCSDVersion, "");
        }
      }  
    #endif  
  #endif

  return TRUE;
}
      
#if defined(_WINDOWS) && !defined(UNDER_CE)
BOOL COSVersion::WhichNTProduct(TCHAR* pszProductType)
{
  //Assume the worst
  BOOL bSuccess = FALSE;

  //Open and the product options key
  HKEY hKey;
  if (RegOpenKey(HKEY_LOCAL_MACHINE, _T("System\\CurrentControlSet\\Control\\ProductOptions"), &hKey) == ERROR_SUCCESS)
  {
    const int MY_BUFSIZE = 100;
    TCHAR sTemp[MY_BUFSIZE];
    DWORD dwBufLen = MY_BUFSIZE * sizeof(TCHAR);

#if (defined(_WIN32) || defined(_WIN64))
    if (::RegQueryValueEx(hKey, _T("ProductType"), NULL, NULL, (LPBYTE) sTemp, &dwBufLen) == ERROR_SUCCESS)
#else
    if (RegQueryValueEx(hKey, _T("ProductType"), NULL, NULL, (LPBYTE) sTemp, &dwBufLen) == ERROR_SUCCESS)
#endif
    {
      _tcscpy(pszProductType, sTemp);
      bSuccess = TRUE;
    }

    RegCloseKey(hKey);
  }

  return bSuccess;
}
#else
BOOL COSVersion::WhichNTProduct(TCHAR* /*pszProductType*/)
{
  return FALSE;
}
#endif //#if defined(_WINDOWS) && !defined(UNDER_CE)
                                   
#ifdef _DOS             
void GetWinInfo()
{ 
  BYTE MajorVer;
  BYTE MinorVer;

  //use some inline assembly to determine if Windows if
  //running and what version is active
  _asm
  {
  ; check for Windows 3.1
    mov     ax,160ah                ; WIN31CHECK
    int     2fh                     ; check if running under Win 3.1.
    or      ax,ax
    jz      RunningUnderWin31       ; can check if running in standard
                                    ; or enhanced mode
   
  ; check for Windows 3.0 enhanced mode
    mov     ax,1600h                ; WIN386CHECK
    int     2fh
    test    al,7fh
    jnz     RunningUnderWin30Enh    ; enhanced mode
   
  ; check for 3.0 WINOLDAP
    mov     ax,4680h                ; IS_WINOLDAP_ACTIVE
    int     2fh
    or      ax,ax                   ; running under 3.0 derivative?
    jnz     NotRunningUnderWin
   
  ; rule out MS-DOS 5.0 task switcher
    mov     ax,4b02h                ; detect switcher
    push    bx
    push    es
    push    di
    xor     bx,bx
    mov     di,bx
    mov     es,bx
    int     2fh
    pop     di
    pop     es
    pop     bx
    or      ax,ax
    jz      NotRunningUnderWin      ; MS-DOS 5.0 task switcher found
   
  ; check for standard mode Windows 3.0
    mov     ax,1605h                ; PMODE_START
    int     2fh
    cmp     cx,-1
    jz      RunningUnderWin30Std
   
  ; check for real mode Windows 3.0
    mov     ax,1606h                ; PMODE_STOP
    int     2fh                     ; in case someone is counting
    ; Real mode Windows 3.0 is running
    mov     byte ptr [bRunningWindows], 1
    mov     byte ptr [MajorVer], 3h    
    mov     byte ptr [MinorVer], 0h        
    jmp     ExitLabel
   
  RunningUnderWin30Std:
    ; Standard mode Windows 3.0 is running
    mov     byte ptr [bRunningWindows], 1
    mov     byte ptr [MajorVer], 3h    
    mov     byte ptr [MinorVer], 0h        
    jmp     ExitLabel
   
  RunningUnderWin31:
    ; At this point: CX == 3 means Windows 3.1 enhanced mode
    ;                CX == 2 means Windows 3.1 standard mode
    mov     byte ptr [bRunningWindows], 1
    
    ; Get the version of Windows 
    mov     ax, 1600h   ; Get Enhanced-Mode Windows Installed State
    int     2Fh
    mov     byte ptr [MajorVer], al
    mov     byte ptr [MinorVer], ah
    jmp     ExitLabel
   
  RunningUnderWin30Enh:
    ; Enhanced mode Windows 3.0 is running
    mov     byte ptr [bRunningWindows], 1    
    mov     byte ptr [MajorVer], 3h    
    mov     byte ptr [MinorVer], 0h        
    jmp     ExitLabel
   
  NotRunningUnderWin:                    
    mov     byte ptr [bRunningWindows], 0
    
  ExitLabel:
  }             
  
  WinVer = (WORD) ((MajorVer << 8) + MinorVer);
} 
#endif //_DOS 

BOOL COSVersion::IsWindowsCE(LPOS_VERSION_INFO lpVersionInformation)
{
  return (lpVersionInformation->dwUnderlyingPlatformId == DT_PLATFORM_WINDOWSCE);
}

BOOL COSVersion::IsWindows95(LPOS_VERSION_INFO lpVersionInformation)
{
  return (lpVersionInformation->dwUnderlyingPlatformId == DT_PLATFORM_WINDOWS9x &&
          lpVersionInformation->dwUnderlyingMajorVersion == 4 && 
          lpVersionInformation->dwUnderlyingMinorVersion == 0 &&
          lpVersionInformation->dwUnderlyingBuildNumber == 950);
}

BOOL COSVersion::IsWindows95SP1(LPOS_VERSION_INFO lpVersionInformation)
{
  return (lpVersionInformation->dwUnderlyingPlatformId == DT_PLATFORM_WINDOWS9x &&
          lpVersionInformation->dwUnderlyingMajorVersion == 4 && 
          lpVersionInformation->dwUnderlyingBuildNumber > 950 && 
          lpVersionInformation->dwUnderlyingBuildNumber <= 1080);
}

BOOL COSVersion::IsWindows95OSR2(LPOS_VERSION_INFO lpVersionInformation)
{
  return (lpVersionInformation->dwUnderlyingPlatformId == DT_PLATFORM_WINDOWS9x &&
          lpVersionInformation->dwUnderlyingMajorVersion == 4 && 
          lpVersionInformation->dwUnderlyingMinorVersion < 10 &&
          lpVersionInformation->dwUnderlyingBuildNumber > 1080);
}

BOOL COSVersion::IsWindows98(LPOS_VERSION_INFO lpVersionInformation)
{
  return (lpVersionInformation->dwUnderlyingPlatformId == DT_PLATFORM_WINDOWS9x &&
          lpVersionInformation->dwUnderlyingMajorVersion == 4 && 
          lpVersionInformation->dwUnderlyingMinorVersion == 10 &&
          lpVersionInformation->dwUnderlyingBuildNumber == 1998);
}

BOOL COSVersion::IsWindows98SP1(LPOS_VERSION_INFO lpVersionInformation)
{
  return (lpVersionInformation->dwUnderlyingPlatformId == DT_PLATFORM_WINDOWS9x &&
          lpVersionInformation->dwUnderlyingMajorVersion == 4 && 
          lpVersionInformation->dwUnderlyingMinorVersion == 10 &&
          lpVersionInformation->dwUnderlyingBuildNumber > 1998 &&
          lpVersionInformation->dwUnderlyingBuildNumber < 2183);
}

BOOL COSVersion::IsWindows98SE(LPOS_VERSION_INFO lpVersionInformation)
{
  return (lpVersionInformation->dwUnderlyingPlatformId == DT_PLATFORM_WINDOWS9x &&
          lpVersionInformation->dwUnderlyingMajorVersion == 4 && 
          lpVersionInformation->dwUnderlyingMinorVersion == 10 &&
          lpVersionInformation->dwUnderlyingBuildNumber >= 2183);
}

BOOL COSVersion::IsWindowsME(LPOS_VERSION_INFO lpVersionInformation)
{
  return (lpVersionInformation->dwUnderlyingPlatformId == DT_PLATFORM_WINDOWS9x &&
          lpVersionInformation->dwUnderlyingMajorVersion == 4 &&
          lpVersionInformation->dwUnderlyingMinorVersion == 90);
}

BOOL COSVersion::IsWindowsNT31(LPOS_VERSION_INFO lpVersionInformation)
{
  return (lpVersionInformation->dwUnderlyingPlatformId == DT_PLATFORM_NT &&
          lpVersionInformation->dwUnderlyingMajorVersion == 3 && 
          lpVersionInformation->dwUnderlyingMinorVersion == 10);
}

BOOL COSVersion::IsWindowsNT35(LPOS_VERSION_INFO lpVersionInformation)
{
  return (lpVersionInformation->dwUnderlyingPlatformId == DT_PLATFORM_NT &&
          lpVersionInformation->dwUnderlyingMajorVersion == 3 && 
          lpVersionInformation->dwUnderlyingMinorVersion == 50);
}

BOOL COSVersion::IsWindowsNT351(LPOS_VERSION_INFO lpVersionInformation)
{
  return (lpVersionInformation->dwUnderlyingPlatformId == DT_PLATFORM_NT &&
          lpVersionInformation->dwUnderlyingMajorVersion == 3 && 
          lpVersionInformation->dwUnderlyingMinorVersion == 51);
}

BOOL COSVersion::IsWindowsNT4(LPOS_VERSION_INFO lpVersionInformation)
{
  return (lpVersionInformation->dwUnderlyingPlatformId == DT_PLATFORM_NT &&
          lpVersionInformation->dwUnderlyingMajorVersion == 4);
}

BOOL COSVersion::IsWindows2000(LPOS_VERSION_INFO lpVersionInformation)
{
  return (lpVersionInformation->dwUnderlyingPlatformId == DT_PLATFORM_NT &&
          lpVersionInformation->dwUnderlyingMajorVersion == 5 &&
          lpVersionInformation->dwUnderlyingMinorVersion == 0);
}

BOOL COSVersion::IsWindowsXP(LPOS_VERSION_INFO lpVersionInformation)
{
  return (lpVersionInformation->dwUnderlyingPlatformId == DT_PLATFORM_NT &&
          lpVersionInformation->dwUnderlyingMajorVersion == 5 &&
          lpVersionInformation->dwUnderlyingMinorVersion != 0);
}

WORD COSVersion::GetNTServicePackFromCSDString(LPCTSTR pszCSDVersion)
{
  WORD wServicePack = 0;
  if (_tcslen(pszCSDVersion))
  {
    //Parse out the CSDVersion string
    int i=0;      
    while (pszCSDVersion[i] != _T('\0') && !_istdigit(pszCSDVersion[i]))
      i++;
    wServicePack = (WORD) (_ttoi(&pszCSDVersion[i]));
  }

  return wServicePack;
}

#if defined(_WINDOWS) && !defined(UNDER_CE)
WORD COSVersion::GetNTServicePackFromRegistry()
{
  //By default assume no service pack
  WORD wServicePack = 0;

  HKEY hCurrentVersion;
  if (RegOpenKey(HKEY_LOCAL_MACHINE, _T("Software\\Microsoft\\Windows NT\\CurrentVersion"),
                 &hCurrentVersion) == ERROR_SUCCESS)
  {
    BYTE byData[128];
    DWORD dwType;
    DWORD dwSize = 128;
#if defined(_WIN32) || defined(_WIN64)
    if (::RegQueryValueEx(hCurrentVersion, _T("CSDVersion"), NULL, &dwType, byData, &dwSize) == ERROR_SUCCESS)
#else
    if (RegQueryValueEx(hCurrentVersion, _T("CSDVersion"), NULL, &dwType, byData, &dwSize) == ERROR_SUCCESS)    
#endif    
    {
      if (dwType == REG_SZ)
      {
        //Stored as a string on all other versions of NT
        wServicePack = GetNTServicePackFromCSDString((TCHAR*) byData);
      }
      else if (dwType == REG_DWORD)
      {
        //Handle the service pack number being stored as a DWORD which happens on NT 3.1
        wServicePack = HIBYTE((WORD) *((DWORD*) &byData));
      }
    }

    //Don't forget to close the registry key we were using      
    RegCloseKey(hCurrentVersion);
  }

  return wServicePack;
}

BOOL COSVersion::ValidateProductSuite(LPCTSTR lpszSuiteToValidate) 
{
  // Open the ProductOptions key.
  HKEY hKey = NULL;
  LONG lResult = RegOpenKey(HKEY_LOCAL_MACHINE, _T("System\\CurrentControlSet\\Control\\ProductOptions"), &hKey);
  if (lResult != ERROR_SUCCESS)
    return FALSE;

  // Determine required size of ProductSuite buffer.
  DWORD dwType = 0;
  DWORD dwSize = 0;                   
#if defined(_WIN32) || defined(_WIN64)  
  lResult = ::RegQueryValueEx(hKey, _T("ProductSuite"), NULL, &dwType, NULL, &dwSize);
#else
  lResult = RegQueryValueEx(hKey, _T("ProductSuite"), NULL, &dwType, NULL, &dwSize);
#endif  
  if (lResult != ERROR_SUCCESS || !dwSize)
  {
    RegCloseKey(hKey);
    return FALSE;
  }

  // Allocate buffer.
  LPTSTR lpszProductSuites = (LPTSTR) new BYTE[dwSize];

  // Retrieve array of product suite strings.
#if defined(_WIN32) || defined(_WIN64)    
  lResult = ::RegQueryValueEx(hKey, _T("ProductSuite"), NULL, &dwType, (LPBYTE) lpszProductSuites, &dwSize);
#else                                                                                                     
  lResult = RegQueryValueEx(hKey, _T("ProductSuite"), NULL, &dwType, (LPBYTE) lpszProductSuites, &dwSize);
#endif  
  if (lResult != ERROR_SUCCESS || dwType != REG_MULTI_SZ)
  {
    //Don't forget to free up the resource we used
    delete [] lpszProductSuites;
    RegCloseKey(hKey);

    return FALSE;
  }

  //All string comparisons will be sub string only and case insensitive
  LPTSTR lpszLocalSuite = new TCHAR[_tcslen(lpszSuiteToValidate)+1];
  _tcscpy(lpszLocalSuite, lpszSuiteToValidate);
  _tcsupr(lpszLocalSuite);

  // Search for suite name in array of strings.
  BOOL bValidated = FALSE;
  LPTSTR lpszSuite = lpszProductSuites;
  while (*lpszSuite) 
  {
    //Ensure the string is upper case
    _tcsupr(lpszSuite);

    //Does the suite match up with the current item?
    if (_tcsstr(lpszSuite, lpszLocalSuite)) 
    {
      bValidated = TRUE;
      break;
    }
    lpszSuite += (lstrlen(lpszSuite) + 1);
  }

  //Don't forget to free up the resource we used
  delete [] lpszLocalSuite;
  delete [] lpszProductSuites;
  RegCloseKey(hKey);

  return bValidated;
}
#else 
WORD COSVersion::GetNTServicePackFromRegistry()
{
  return 0;
}

BOOL COSVersion::ValidateProductSuite(LPCTSTR /*lpszSuiteToValidate*/) 
{
  return FALSE;
}
#endif //#if defined(_WINDOWS) && !defined(UNDER_CE)
             
#if defined(_WIN64) || defined(_WIN32)             
BOOL COSVersion::IsWindows30(LPOS_VERSION_INFO /*lpVersionInformation*/)
#else
BOOL COSVersion::IsWindows30(LPOS_VERSION_INFO lpVersionInformation)
#endif //#if defined(_WIN64) || defined(_Win32             
{
#ifdef _WIN64
  return FALSE;
#elif _WIN32
  return FALSE;
#else
  return (lpVersionInformation->dwUnderlyingPlatformId == DT_PLATFORM_WINDOWS3x &&
          lpVersionInformation->dwUnderlyingMinorVersion == 0);
#endif
}

#if defined(_WIN64) || defined(_WIN32)             
BOOL COSVersion::IsWindows31(LPOS_VERSION_INFO /*lpVersionInformation*/)
#else
BOOL COSVersion::IsWindows31(LPOS_VERSION_INFO lpVersionInformation)
#endif //#if defined(_WIN64) || defined(_Win32             
{
#ifdef _WIN64
  return FALSE;
#elif _WIN32
  return FALSE;
#else
  return (lpVersionInformation->dwUnderlyingPlatformId == DT_PLATFORM_WINDOWS3x &&
          lpVersionInformation->dwUnderlyingMinorVersion == 10);
#endif
}

#if defined(_WIN64) || defined(_WIN32)            
BOOL COSVersion::IsWindows311(LPOS_VERSION_INFO /*lpVersionInformation*/)
#else
BOOL COSVersion::IsWindows311(LPOS_VERSION_INFO lpVersionInformation)
#endif //#if defined(_WIN64) || defined(_Win32             
{
#ifdef _WIN64
  return FALSE;
#elif _WIN32
  return FALSE;
#else
  return (lpVersionInformation->dwUnderlyingPlatformId == DT_PLATFORM_WINDOWS3x &&
          lpVersionInformation->dwUnderlyingMinorVersion == 11);
#endif
}

#if defined(_WINDOWS) && (!defined(_WIN32) && !defined(_WIN64))  
BOOL COSVersion::IsWindowsForWorkgroups(LPOS_VERSION_INFO lpVersionInformation)
#else
BOOL COSVersion::IsWindowsForWorkgroups(LPOS_VERSION_INFO /*lpVersionInformation*/)
#endif //#if defined(_WINDOWS) && (defined(_WIN32) || defined(_WIN64))  
{
#if defined(_WINDOWS) && (!defined(_WIN32) && !defined(_WIN64))  
  return (lpVersionInformation->dwUnderlyingPlatformId == DT_PLATFORM_WINDOWS3x &&
          WFWLoaded());
#else
  return FALSE;          
#endif //#if defined(_WINDOWS) && (!defined(_WIN32) && !defined(_WIN64))  
}


#if defined(_WIN32)
BOOL COSVersion::IsWin32sInstalled(LPOS_VERSION_INFO lpVersionInformation)
#else
BOOL COSVersion::IsWin32sInstalled(LPOS_VERSION_INFO /*lpVersionInformation*/)
#endif //#if defined(_WIN64) || defined(_Win32             
{
#ifdef _WIN64
  return FALSE;
#elif _WIN32
  return (lpVersionInformation->dwUnderlyingPlatformId == DT_PLATFORM_WINDOWS3x);
#else
  return FALSE;
#endif
}

BOOL COSVersion::IsNTPreWin2k(LPOS_VERSION_INFO lpVersionInformation)
{
  return (lpVersionInformation->dwUnderlyingPlatformId == DT_PLATFORM_NT &&
          lpVersionInformation->dwUnderlyingMajorVersion <= 4);
}

BOOL COSVersion::IsNTPDC(LPOS_VERSION_INFO lpVersionInformation)
{                                                               
  TCHAR pszProductType[100];
  return (IsNTPreWin2k(lpVersionInformation) &&
          WhichNTProduct(pszProductType) &&
          _tcsicmp(pszProductType, _T("LANMANNT")) == 0);
}

BOOL COSVersion::IsNTStandAloneServer(LPOS_VERSION_INFO lpVersionInformation)
{
  TCHAR pszProductType[100];
  return (IsNTPreWin2k(lpVersionInformation) &&
          WhichNTProduct(pszProductType) &&
          _tcsicmp(pszProductType, _T("SERVERNT")) == 0);
}

BOOL COSVersion::IsNTBDC(LPOS_VERSION_INFO lpVersionInformation)
{
  TCHAR pszProductType[100];
  return (IsNTPreWin2k(lpVersionInformation) &&
          WhichNTProduct(pszProductType) &&
          _tcsicmp(pszProductType, _T("LANSECNT")) == 0);
}

BOOL COSVersion::IsTerminalServicesInstalled(LPOS_VERSION_INFO /*lpVersionInformation*/)
{
  return ValidateProductSuite(_T("Terminal Server"));
}

BOOL COSVersion::ISSmallBusinessEditionInstalled(LPOS_VERSION_INFO /*lpVersionInformation*/)
{
  return ValidateProductSuite(_T("SBS"));
}

BOOL COSVersion::IsNTWorkstation(LPOS_VERSION_INFO lpVersionInformation)
{
  TCHAR pszProductType[100];
  return (IsNTPreWin2k(lpVersionInformation) &&
          WhichNTProduct(pszProductType) &&
          _tcsicmp(pszProductType, _T("WinNT")) == 0);
}

BOOL COSVersion::IsNTEnterpriseServer(LPOS_VERSION_INFO lpVersionInformation)
{
  return (IsNTPreWin2k(lpVersionInformation) &&
          ValidateProductSuite(_T("Enterprise")));
}

BOOL COSVersion::IsNTDatacenterServer(LPOS_VERSION_INFO lpVersionInformation)
{
  TCHAR pszProductType[100];
  return (IsNTPreWin2k(lpVersionInformation) &&
          WhichNTProduct(pszProductType) &&
          _tcsicmp(pszProductType, _T("Center")) == 0);
}

BOOL COSVersion::IsWin2000Professional(LPOS_VERSION_INFO lpVersionInformation)
{
  TCHAR pszProductType[100];
  return (IsWindows2000(lpVersionInformation) &&
          WhichNTProduct(pszProductType) &&
          _tcsicmp(pszProductType, _T("WinNT")) == 0);
}

BOOL COSVersion::IsWin2000Server(LPOS_VERSION_INFO lpVersionInformation)
{
  TCHAR pszProductType[100];
  return (IsWindows2000(lpVersionInformation) &&
          WhichNTProduct(pszProductType) &&
          _tcsicmp(pszProductType, _T("SERVERNT")) == 0);
}

BOOL COSVersion::IsWin2000AdvancedServer(LPOS_VERSION_INFO lpVersionInformation)
{
  return (IsWindows2000(lpVersionInformation) &&
          ValidateProductSuite(_T("Enterprise")));
}

BOOL COSVersion::IsWin2000DatacenterServer(LPOS_VERSION_INFO lpVersionInformation)
{
  return (IsWindows2000(lpVersionInformation) &&
          ValidateProductSuite(_T("Data")));
}

BOOL COSVersion::IsWin2000DomainController(LPOS_VERSION_INFO lpVersionInformation)
{
  TCHAR pszProductType[100];
  return (IsWindows2000(lpVersionInformation) &&
          WhichNTProduct(pszProductType) &&
          _tcsicmp(pszProductType, _T("LanmanNT")) == 0);
}

BOOL COSVersion::IsXPPersonal(LPOS_VERSION_INFO lpVersionInformation)
{
  return (IsWindowsXP(lpVersionInformation) &&
          ValidateProductSuite(_T("Personal")));
}

BOOL COSVersion::IsXPProfessional(LPOS_VERSION_INFO lpVersionInformation)
{
  TCHAR pszProductType[100];
  return (IsWindowsXP(lpVersionInformation) &&
          WhichNTProduct(pszProductType) &&
          _tcsicmp(pszProductType, _T("WinNT")) == 0);
}

BOOL COSVersion::IsXPServer(LPOS_VERSION_INFO lpVersionInformation)
{
  TCHAR pszProductType[100];
  return (IsWindowsXP(lpVersionInformation) &&
          WhichNTProduct(pszProductType) &&
          _tcsicmp(pszProductType, _T("SERVERNT")) == 0);
}

BOOL COSVersion::IsXPAdvancedServer(LPOS_VERSION_INFO lpVersionInformation)
{
  return (IsWindowsXP(lpVersionInformation) &&
          ValidateProductSuite(_T("Enterprise")));
}

BOOL COSVersion::IsXPDatacenterServer(LPOS_VERSION_INFO lpVersionInformation)
{
  return (IsWindowsXP(lpVersionInformation) &&
          ValidateProductSuite(_T("Data")));
}

BOOL COSVersion::IsXPDomainController(LPOS_VERSION_INFO lpVersionInformation)
{
  TCHAR pszProductType[100];
  return (IsWindowsXP(lpVersionInformation) &&
           WhichNTProduct(pszProductType) &&
           _tcsicmp(pszProductType, _T("LanmanNT")) == 0);
}

BOOL COSVersion::Is64Bit(LPOS_VERSION_INFO /*lpVersionInformation*/)
{
#ifdef _WIN64
  return TRUE;
#else
  return FALSE;
#endif
}