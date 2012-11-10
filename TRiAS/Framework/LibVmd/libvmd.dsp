# Microsoft Developer Studio Project File - Name="libvmd" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=libvmd - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "libvmd.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "libvmd.mak" CFG="libvmd - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "libvmd - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libvmd - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/visobj/libvmd", CBDAAAAA"
# PROP Scc_LocalPath "."
CPP=xicl6.exe
RSC=rc.exe

!IF  "$(CFG)" == "libvmd - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "_Release"
# PROP Intermediate_Dir "_Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /O1 /I "..\..\FrameWrk\lmfcx42\\" /D "WIN32" /D "_WINDOWS" /D "NDEBUG" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /Fd"_Release/LibVMD.pbd" /FD /c
# ADD BASE RSC /l 0x407
# ADD RSC /l 0x407
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=xilink6.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
# Begin Custom Build - Copy Target
OutDir=.\_Release
TargetName=libvmd
InputPath=.\_Release\libvmd.lib
SOURCE="$(InputPath)"

"$(TRIASLIB)\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(OutDir)\$(TargetName).lib $(TRIASLIB)

# End Custom Build

!ELSEIF  "$(CFG)" == "libvmd - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "_Debug"
# PROP Intermediate_Dir "_Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MDd /W3 /WX /GX /Zi /Od /I "..\..\FrameWrk\lmfcx42\\" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_DEBUG" /FR /Fd"_Debug/LibVMDd.pdb" /FD /c
# ADD BASE RSC /l 0x407
# ADD RSC /l 0x407
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o".\_Debug/libvmdD.bsc"
LIB32=xilink6.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:".\_Debug\libvmdD.lib"
# Begin Custom Build - Copy Target
OutDir=.\_Debug
TargetName=libvmdD
InputPath=.\_Debug\libvmdD.lib
SOURCE="$(InputPath)"

"$(TRIASLIB)\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(OutDir)\$(TargetName).lib $(TRIASLIB)

# End Custom Build

!ENDIF 

# Begin Target

# Name "libvmd - Win32 Release"
# Name "libvmd - Win32 Debug"
# Begin Group "LibVMD"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\VISMOD.H
# End Source File
# Begin Source File

SOURCE=.\VISMOD.INL
# End Source File
# Begin Source File

SOURCE=.\vmdguids.cpp
# End Source File
# Begin Source File

SOURCE=.\vmdinln.cpp
# End Source File
# Begin Source File

SOURCE=.\vmdreg.cpp
# End Source File
# Begin Source File

SOURCE=.\vmdtrias.cpp
# End Source File
# End Group
# Begin Group "DLL Data"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\STDAFX.CPP
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\STDAFX.H
# End Source File
# Begin Source File

SOURCE=.\VismodImpl.h
# End Source File
# End Group
# End Target
# End Project
