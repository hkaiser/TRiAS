# Microsoft Developer Studio Project File - Name="LibSDSC" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=LibSDSC - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "LibSDSC.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "LibSDSC.mak" CFG="LibSDSC - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "LibSDSC - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "LibSDSC - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "LibSDSC - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /Z7 /O1 /I ".\include" /I "..\Include" /D "NDEBUG" /D "MSWIND" /D "WIN32" /D "_MBCS" /D "__STDC__" /YX /FD /c
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "LibSDSC - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "LibSDSC___Win32_Debug"
# PROP BASE Intermediate_Dir "LibSDSC___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /I "$(UWINBASE)\usr\include" /I ".\include" /I "..\Include" /D "NDEBUG" /D "MSWIND" /D "WIN32" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /Zp8 /MDd /W3 /GX /Z7 /Od /Op- /I ".\include" /I "..\Include" /D "MSWIND" /D "__STDC__" /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "STRICT" /FR /YX /FD /c
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "LibSDSC - Win32 Release"
# Name "LibSDSC - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\arg.c
# End Source File
# Begin Source File

SOURCE=.\bin.c
# End Source File
# Begin Source File

SOURCE=.\tag.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\include\arg.h
# End Source File
# Begin Source File

SOURCE=.\include\bin.h
# End Source File
# Begin Source File

SOURCE=.\include\sdsc.h
# End Source File
# Begin Source File

SOURCE=.\include\sdscconfig.h
# End Source File
# Begin Source File

SOURCE=.\include\sdsccopyright.h
# End Source File
# Begin Source File

SOURCE=.\include\tag.h
# End Source File
# End Group
# End Target
# End Project
