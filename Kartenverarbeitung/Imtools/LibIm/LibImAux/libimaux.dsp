# Microsoft Developer Studio Project File - Name="libimaux" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=LIBIMAUX - WIN32 RELEASE
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "libimaux.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "libimaux.mak" CFG="LIBIMAUX - WIN32 RELEASE"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "libimaux - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libimaux - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "libimaux - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /Z7 /O1 /I "..\..\Tools\Include" /I "..\..\libsdsc\include" /I "..\Include" /I "..\..\Include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "__STDC__" /D "MSWIND" /YX /FD /c
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"Release\libimtools.lib"

!ELSEIF  "$(CFG)" == "libimaux - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "libimaux___Win32_Debug"
# PROP BASE Intermediate_Dir "libimaux___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /I "$(UWINBASE)\usr\include" /I "..\..\Tools\Include" /I "..\..\libsdsc\include" /I "..\Include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "_POSIX_" /D __STDC__=1 /D _X86_=1 /D "unix" /D "MSWIND" /YX /FD /c
# ADD CPP /nologo /Zp8 /MDd /W3 /GX /Z7 /Od /I "..\..\Tools\Include" /I "..\..\libsdsc\include" /I "..\Include" /I "..\..\Include" /D "_LIB" /D "MSWIND" /D "__STDC__" /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "STRICT" /YX /FD /c
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"Release\libimtools.lib"
# ADD LIB32 /nologo /out:"Debug\libimtools.lib"

!ENDIF 

# Begin Target

# Name "libimaux - Win32 Release"
# Name "libimaux - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\tools\imfeedback.c
# End Source File
# Begin Source File

SOURCE=..\..\tools\imregister.c
# End Source File
# Begin Source File

SOURCE=..\..\tools\imtools.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\tools\include\imtools.h
# End Source File
# End Group
# End Target
# End Project
