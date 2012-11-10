# Microsoft Developer Studio Project File - Name="si" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=si - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "si.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "si.mak" CFG="si - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "si - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "si - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "si - Win32 Release"

# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Cmd_Line "NMAKE /f si.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "si.exe"
# PROP BASE Bsc_Name "si.bsc"
# PROP BASE Target_Dir ""
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Cmd_Line "NMAKE /f si.mak"
# PROP Rebuild_Opt "/a"
# PROP Target_File "si.exe"
# PROP Bsc_Name "si.bsc"
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "si - Win32 Debug"

# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Cmd_Line "NMAKE /f si.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "si.exe"
# PROP BASE Bsc_Name "si.bsc"
# PROP BASE Target_Dir ""
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Cmd_Line "NMAKE /C /f si.mak"
# PROP Rebuild_Opt "/a"
# PROP Target_File "..\..\include\si.h"
# PROP Bsc_Name "si.bsc"
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "si - Win32 Release"
# Name "si - Win32 Debug"

!IF  "$(CFG)" == "si - Win32 Release"

!ELSEIF  "$(CFG)" == "si - Win32 Debug"

!ENDIF 

# Begin Source File

SOURCE=..\..\SIunits\NT_si.h
# End Source File
# Begin Source File

SOURCE=.\si.mak
# End Source File
# End Target
# End Project
