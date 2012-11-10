# Microsoft Developer Studio Project File - Name="DynQuery" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=DynQuery - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Dynquery.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Dynquery.mak" CFG="DynQuery - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DynQuery - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "DynQuery - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DynQuery - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\WinRel"
# PROP BASE Intermediate_Dir ".\WinRel"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\WinRel"
# PROP Intermediate_Dir ".\WinRel"
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "__ATL_USED__" /D "QI_EXCEPTION" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D "OS_NO_STREAM_SUPPORT" /D "OS_NO_ALLOCATORS" /D "__ATL_11_USED__" /D "_ATL_NEW_CCOMSTRUCT" /D "EBWIN32" /FR /Yu"StdAfx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ixtmar42.lib stdcppr.lib cont32r.lib ospace2r.lib /nologo /subsystem:windows /dll /machine:I386 /out:".\WinRel\DynQuery.ext" /stub:"rights.exe"
# Begin Custom Build - Copying Target to Destination ...
TargetPath=.\WinRel\DynQuery.ext
TargetName=DynQuery
InputPath=.\WinRel\DynQuery.ext
SOURCE=$(InputPath)

"c:\trias.mvc\trias200.rel\$(TargetName).ext" : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
	copy $(TargetPath) c:\trias.mvc\trias200.rel

# End Custom Build

!ELSEIF  "$(CFG)" == "DynQuery - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\WinDebug"
# PROP BASE Intermediate_Dir ".\WinDebug"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\WinDebug"
# PROP Intermediate_Dir ".\WinDebug"
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "__ATL_USED__" /D "QI_EXCEPTION" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D "OS_NO_STREAM_SUPPORT" /D "OS_NO_ALLOCATORS" /D "__ATL_11_USED__" /D "_ATL_NEW_CCOMSTRUCT" /D "EBWIN32" /FR /Yu"StdAfx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 ixtmad42.lib stdcppd.lib cont32d.lib ospace2d.lib /nologo /subsystem:windows /dll /incremental:no /debug /debugtype:both /machine:I386 /out:".\WinDebug\DynQuery.ext" /stub:"rights.exe"
# Begin Custom Build - Copying Target to Destination ...
TargetPath=.\WinDebug\DynQuery.ext
TargetName=DynQuery
InputPath=.\WinDebug\DynQuery.ext
SOURCE=$(InputPath)

"c:\trias.mvc\trias200\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(TargetPath) c:\trias.mvc\trias200

# End Custom Build

!ENDIF 

# Begin Target

# Name "DynQuery - Win32 Release"
# Name "DynQuery - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\DynQueries.cpp
# End Source File
# Begin Source File

SOURCE=.\DynQuery.CXX
# End Source File
# Begin Source File

SOURCE=.\DynQuery.DEF
# End Source File
# Begin Source File

SOURCE=.\DynQuery.idl

!IF  "$(CFG)" == "DynQuery - Win32 Release"

# Begin Custom Build
InputPath=.\DynQuery.idl

"Release/DynQuery.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl /oldtlb /Oicf /tlb "Release/DynQuery.tlb" "DynQuery.idl"

# End Custom Build

!ELSEIF  "$(CFG)" == "DynQuery - Win32 Debug"

# Begin Custom Build
InputPath=.\DynQuery.idl

BuildCmds= \
	midl /oldtlb /Oicf /h "DynQuery.h" /iid "DynQuery_i.c" /tlb\
 "Debug/DynQuery.tlb" "DynQuery.idl"

"DynQuery.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Debug/DynQuery.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"DynQuery_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DynQuery.RC
# End Source File
# Begin Source File

SOURCE=.\DynQueryObjEnums.cpp
# End Source File
# Begin Source File

SOURCE=.\Res\GetObjectsFromORWnd.ebs

!IF  "$(CFG)" == "DynQuery - Win32 Release"

# Begin Custom Build - Compiling Basic Script ...
InputDir=.\Res
InputPath=.\Res\GetObjectsFromORWnd.ebs
InputName=GetObjectsFromORWnd

"$(InputDir)\$(InputName)r.ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -c -n -o $(InputDir)\$(InputName)r.ebc -DNDEBUG $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "DynQuery - Win32 Debug"

# Begin Custom Build - Compiling Basic Script ...
InputDir=.\Res
InputPath=.\Res\GetObjectsFromORWnd.ebs
InputName=GetObjectsFromORWnd

"$(InputDir)\$(InputName)d.ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -n -o $(InputDir)\$(InputName)d.ebc -DDEBUG $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Helper.cpp
# End Source File
# Begin Source File

SOURCE=.\STDAFX.CXX
# ADD CPP /Yc"StdAfx.h"
# End Source File
# Begin Source File

SOURCE=.\Strings.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\DYNQGUID.H
# End Source File
# Begin Source File

SOURCE=.\DynQueries.h
# End Source File
# Begin Source File

SOURCE=.\DYNQUERY.HXX
# End Source File
# Begin Source File

SOURCE=.\DynQueryObjEnums.h
# End Source File
# Begin Source File

SOURCE=.\STDAFX.H
# End Source File
# Begin Source File

SOURCE=.\Strings.h
# End Source File
# Begin Source File

SOURCE=.\VERSION.H
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\DynQuery.RCV
# End Source File
# Begin Source File

SOURCE=.\Res\GetObjectsFromORWndd.ebc
# End Source File
# Begin Source File

SOURCE=.\Res\GetObjectsFromORWndr.ebc
# End Source File
# End Group
# Begin Group "Registry Scripts"

# PROP Default_Filter "*.rgs"
# Begin Source File

SOURCE=.\DynQueryObjEnums.rgs
# End Source File
# End Group
# End Target
# End Project
