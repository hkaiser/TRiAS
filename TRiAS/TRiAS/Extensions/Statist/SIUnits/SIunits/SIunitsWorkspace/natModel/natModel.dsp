# Microsoft Developer Studio Project File - Name="natModel" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=natModel - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "natModel.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "natModel.mak" CFG="natModel - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "natModel - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "natModel - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "natModel - Win32 Release"

# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Cmd_Line "NMAKE /f natModel.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "natModel.exe"
# PROP BASE Bsc_Name "natModel.bsc"
# PROP BASE Target_Dir ""
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Cmd_Line "NMAKE /f natModel.mak"
# PROP Rebuild_Opt "/a"
# PROP Target_File "natModel.exe"
# PROP Bsc_Name "natModel.bsc"
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "natModel - Win32 Debug"

# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Cmd_Line "NMAKE /f natModel.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "natModel.exe"
# PROP BASE Bsc_Name "natModel.bsc"
# PROP BASE Target_Dir ""
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Cmd_Line "NMAKE /C /f natModel.mak"
# PROP Rebuild_Opt "/a"
# PROP Target_File "..\..\include\natModel.h"
# PROP Bsc_Name "natModel.bsc"
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "natModel - Win32 Release"
# Name "natModel - Win32 Debug"

!IF  "$(CFG)" == "natModel - Win32 Release"

!ELSEIF  "$(CFG)" == "natModel - Win32 Debug"

!ENDIF 

# Begin Source File

SOURCE=.\natModel.mak
# End Source File
# Begin Source File

SOURCE=..\..\SIunits\NT_natModel.h
# End Source File
# End Target
# End Project
