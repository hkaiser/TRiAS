# Microsoft Developer Studio Project File - Name="gooseexample" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=gooseexample - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "gooseexample.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "gooseexample.mak" CFG="gooseexample - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "gooseexample - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "gooseexample - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=xicl6.exe
RSC=rc.exe

!IF  "$(CFG)" == "gooseexample - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "gooseexample___Win32_Debug"
# PROP BASE Intermediate_Dir "gooseexample___Win32_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MLd /W3 /Gi /GX /Od /I "src/containers" /I "src/linear" /I "src/specfns" /I "src/stats" /I "src/util" /I "src/win32" /D "WIN32" /D "DEBUG" /D "_CONSOLE" /YX /FD /c
# SUBTRACT BASE CPP /WX
# ADD CPP /nologo /MTd /W3 /Gm /Gi /GX /ZI /Od /I "src/containers" /I "src/linear" /I "src/specfns" /I "src/stats" /I "src/util" /I "src/win32" /D "WIN32" /D "DEBUG" /YX /FD /c
# SUBTRACT CPP /WX
# ADD BASE RSC /l 0x406 /d "DEBUG"
# ADD RSC /l 0x406 /d "DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 Library\*.obj /nologo /subsystem:console /incremental:yes /debug /machine:I386
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 /nologo /subsystem:console /incremental:yes /debug /machine:I386
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "gooseexample - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "gooseexample___Win32_Release"
# PROP BASE Intermediate_Dir "gooseexample___Win32_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MLd /W3 /Gi /GX /Od /I "src/containers" /I "src/linear" /I "src/specfns" /I "src/stats" /I "src/util" /I "src/win32" /D "WIN32" /D "DEBUG" /D "_CONSOLE" /YX /FD /c
# SUBTRACT BASE CPP /WX
# ADD CPP /nologo /MT /W3 /Gi /GX /O2 /Ob2 /I "src/containers" /I "src/linear" /I "src/specfns" /I "src/stats" /I "src/util" /I "src/win32" /D "WIN32" /YX /FD /c
# SUBTRACT CPP /WX
# ADD BASE RSC /l 0x406 /d "DEBUG"
# ADD RSC /l 0x406 /d "DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 Library\*.obj /nologo /subsystem:console /incremental:yes /debug /machine:I386
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 Library\*.obj /nologo /subsystem:console /incremental:yes /debug /machine:I386
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "gooseexample - Win32 Debug"
# Name "gooseexample - Win32 Release"
# Begin Group "examples"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\examples\test_ascii_import.cpp
# End Source File
# End Group
# End Target
# End Project
