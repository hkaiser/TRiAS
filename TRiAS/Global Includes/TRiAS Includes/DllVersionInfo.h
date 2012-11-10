// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 23.08.99 08:43:43 
//
// @doc
// @module DllVersionInfo.h | Declaration of the <c CDllVersionInfo> class

#if !defined(_DLLVERSIONINFO_H__118B26A0_5926_11D3_9503_0080C786297B__INCLUDED_)
#define _DLLVERSIONINFO_H__118B26A0_5926_11D3_9503_0080C786297B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

//
//  Handles accessing the VERSIONINFO resource, which is particularly poorly
//  documented by Microsoft, but does define it's items as follows:
//
/* ----- start excerpt ------------
     
====================+===============================================================
Comments            |Specifies additional information that should be displayed for
                    |diagnostic purposes.
====================+===============================================================
CompanyName         |Specifies the company that produced the file-for example,
                    |"Microsoft Corporation" or "Standard Microsystems 
                    |Corporation, Inc.". This string is required.
====================+===============================================================
FileDescription     |Specifies a file description to be presented to users. This
                    |string may be displayed in a list box when the user is 
                    |choosing files to install-for example, "Keyboard Driver for
                    |AT-Style Keyboards" or "Microsoft Word for Windows". This
                    |string is required.
====================+===============================================================
FileVersion         |Specifies the version number of the file-for example, "3.10"
                    |or "5.00.RC2". This string is required.
====================+===============================================================
InternalName        |Specifies the internal name of the file, if one exists-for
                    |example, a module name if the file is a dynamic-link library.
                    |If the file has no internal name, this string should be the
                    |original filename, without extension. This string is 
                    |required.
====================+===============================================================
LegalCopyright      |Specifies all copyright notices that apply to the file. This
                    |should include the full text of all notices, legal symbols,
                    |copyright dates, and so on-for example, "Copyright Microsoft
                    |Corp. 1990,1991". This string is optional.
====================+===============================================================
LegalTrademarks     |Specifies all trademarks and registered trademarks that apply
                    |to the file. This should include the full text of all 
                    |notices, legal symbols, trademark numbers, and so on-for
                    |example, "Windows(TM) is a trademark of Microsoft 
                    |Corporation". This string is optional.
====================+===============================================================
OriginalFilename    |Specifies the original name of the file, not including a
                    |path. This information enables an application to determine
                    |whether a file has been renamed by a user. The format of the
                    |name depends on the file system for which the file was 
                    |created. This string is required.
====================+===============================================================
PrivateBuild        |Specifies information about a private version of the file-for
                    |example, "Built by TESTER1 on \TESTBED". This string should
                    |be present only if the VS_FF_PRIVATEBUILD flag is set in the
                    |dwFileFlags member of the VS_FIXEDFILEINFO structure of the
                    |root block.
====================+===============================================================
ProductName         |Specifies the name of the product with which the file is
                    |distributed-for example, "Microsoft Windows". This string is
                    |required.
====================+===============================================================
ProductVersion      |Specifies the version of the product with which the file is
                    |distributed-for example, "3.10" or "5.00.RC2". This string is
                    |required.
====================+===============================================================
SpecialBuild        |Specifies how this version of the file differs from the
                    |standard version-for example, "Private build for TESTER1
                    |solving mouse problems on M250 and M250E computers". This
                    |string should be present only if the VS_FF_SPECIALBUILD flag
                    |is set in the dwFileFlags member of the VS_FIXEDFILEINFO
                    |structure in the root block.
====================+===============================================================
     
-------- end excerpt   --- */
     
//  CDllVersionInfo objects have a member function for each of the above elements
//  returned as CString objects.
//
//  Values are only retrieved from the VERSIONINFO structure; they cannot be
//  written to.
//
//  If new elements are added to VERSIONINFO structure in the future, they can
//  be retieved using the GetValue() member function. 
//
//
//  Example use:
//
//  CDllVersionInfo  ver;
//  // no parmeter defaults to active EXE.
     
//  CDllVersionInfo  vDoc("DOCTABLE");
//  // String parameter gives name of DLL to get info from 
//  // N.B. Win16: Any DLL in system.
//  //      Win32: Only DLLs in app's memory space. 
//
//  // Note that object creation is a "costly" operation
//  // hence you code should be structured to avoid repeatly 
//  // constructing & destroying CDllVersionInfo objects.
//
//  // Also note that an object is bound to a DLL at construction, 
//  // and there are no copy or assignment operators. Hence an
//  // object can't be "reused".
//
//  cout << ver.ProductName() << " version " << ver.ProductVersion() << endl;
//
//
     
class CDllVersionInfo
{
public:
    inline CDllVersionInfo(LPCTSTR pModName = NULL); 
    inline ~CDllVersionInfo();
     
    CString Comments()        {return GetValue("Comments");} 
    CString CompanyName()     {return GetValue("CompanyName");} 
    CString FileDescription() {return GetValue("FileDescription");} 
    CString FileVersion()     {return GetValue("FileVersion");} 
    CString InternalName()    {return GetValue("InternalName");}
    CString OriginalFilename(){return GetValue("OriginalFilename");} 
    CString ProductName()     {return GetValue("ProductName");} 
    CString ProductVersion()  {return GetValue("ProductVersion");} 
    CString SpecialBuild()    {return GetValue("SpecialBuild");} 
    CString LegalCopyright()  {return GetValue("LegalCopyright");} 
    CString LegalTrademarks() {return GetValue("LegalTrademarks");} 
    CString PrivateBuild()    {return GetValue("PrivateBuild");}
     
    inline CString GetValue(CString const sSubBlock);
     
private:
    CString     m_sSubBlockHead;
    void *      m_VerData;
     
    CDllVersionInfo(const CDllVersionInfo &);   // private copy ctor (can't copy)
    operator=(const CDllVersionInfo &);			// private op=  (can't assign)
};

CDllVersionInfo::CDllVersionInfo(LPCTSTR lpszModuleName /* = NULL */)
        : m_VerData(NULL)
{
    HMODULE     hModule;
    if (lpszModuleName == NULL) {
        hModule = AfxGetInstanceHandle();
    } else {
        hModule = GetModuleHandle(lpszModuleName);
        if (hModule == NULL)
            AfxThrowUserException();
    }

    char    name[_MAX_PATH];
    GetModuleFileName(hModule, name, sizeof(name));

    DWORD   hInfo;
    DWORD   dwLen;
    dwLen = GetFileVersionInfoSize(name, &hInfo);

    if (dwLen == 0)
        AfxThrowUserException();

    m_VerData = (void *) new char[dwLen];
    if (m_VerData == NULL)
        AfxThrowMemoryException();

    GetFileVersionInfo(name, hInfo,  dwLen, m_VerData);


    struct {
        WORD    first;
        WORD    second;
    } *lpBuffer;
     
    VerQueryValue(m_VerData, "\\VarFileInfo\\Translation",
            (LPVOID*) &lpBuffer,(unsigned int *) &dwLen);
     
    if (dwLen==0)
        AfxThrowUserException();
     
    wsprintf(name, "\\StringFileInfo\\%04x%04x\\", 
                    lpBuffer->first, lpBuffer->second);
    m_sSubBlockHead = name;
}

CDllVersionInfo::~CDllVersionInfo()
{
    delete m_VerData;
}
     
CString CDllVersionInfo::GetValue(CString const sSubBlock)
{
    CString sBlock = m_sSubBlockHead + sSubBlock; 
    CString sRet;
     
    unsigned int    uSize;
    LPCTSTR         lpBuffer;
    BOOL bRet = VerQueryValue(m_VerData, 
                    (char *)((LPCTSTR) sBlock), 
                    (void**)&lpBuffer, &uSize);
     
    if (bRet)
        sRet = lpBuffer;
     
    return sRet;
}

#endif // !defined(_DLLVERSIONINFO_H__118B26A0_5926_11D3_9503_0080C786297B__INCLUDED_)
