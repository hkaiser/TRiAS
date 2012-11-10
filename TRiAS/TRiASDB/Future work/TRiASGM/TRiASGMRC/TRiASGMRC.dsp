# Microsoft Developer Studio Project File - Name="TRiASGMRC" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=TRiASGMRC - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TRiASGMRC.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TRiASGMRC.mak" CFG="TRiASGMRC - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TRiASGMRC - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe
# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /fo"Release/TRiASGM1.res" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386 /out:"..\Debug\resdlls\0009\TRiASGM1.drx" /NOENTRY
# SUBTRACT LINK32 /pdb:none
# Begin Target

# Name "TRiASGMRC - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter ".rc"
# Begin Source File

SOURCE=.\TRiASGM.rc
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ".h"
# End Group
# Begin Group "Registry Scripts"

# PROP Default_Filter "*.rgs"
# Begin Source File

SOURCE=.\RecordsetGenerator.rgs
# End Source File
# Begin Source File

SOURCE=.\RecordsetSource.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASAreaVisInfo.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASLineVisInfo.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASPointVisInfo.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASTextVisInfo.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASVisInfo.rgs
# End Source File
# Begin Source File

SOURCE=.\ViewRecordsetGenerator.rgs
# End Source File
# End Group
# End Target
# End Project
