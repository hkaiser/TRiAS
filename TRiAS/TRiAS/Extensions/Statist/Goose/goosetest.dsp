# Microsoft Developer Studio Project File - Name="goosetest" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=goosetest - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "goosetest.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "goosetest.mak" CFG="goosetest - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "goosetest - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "goosetest - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=xicl6.exe
RSC=rc.exe

!IF  "$(CFG)" == "goosetest - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "goosetest___Win32_Debug"
# PROP BASE Intermediate_Dir "goosetest___Win32_Debug"
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

!ELSEIF  "$(CFG)" == "goosetest - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "goosetest___Win32_Release"
# PROP BASE Intermediate_Dir "goosetest___Win32_Release"
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

# Name "goosetest - Win32 Debug"
# Name "goosetest - Win32 Release"
# Begin Group "test"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\test\test_A001.cpp
# End Source File
# Begin Source File

SOURCE=.\test\test_A002.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\test\test_B001.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\test\test_B002.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\test\test_B003.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\test\test_B004.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\test\test_B005.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\test\test_B006.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\test\test_E001.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\test\test_E002.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\test\test_E003.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\test\test_E004.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\test\test_G001.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\test\test_H001.cpp
# PROP Exclude_From_Build 1
# End Source File
# End Group
# End Target
# End Project
