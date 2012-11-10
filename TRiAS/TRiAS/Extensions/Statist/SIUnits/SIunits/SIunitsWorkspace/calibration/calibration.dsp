# Microsoft Developer Studio Project File - Name="calibration" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=calibration - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "calibration.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "calibration.mak" CFG="calibration - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "calibration - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "calibration - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "calibration - Win32 Release"

# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Cmd_Line "NMAKE /f calibration.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "calibration.exe"
# PROP BASE Bsc_Name "calibration.bsc"
# PROP BASE Target_Dir ""
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Cmd_Line "NMAKE /f calibration.mak"
# PROP Rebuild_Opt "/a"
# PROP Target_File "calibration.exe"
# PROP Bsc_Name "calibration.bsc"
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "calibration - Win32 Debug"

# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Cmd_Line "NMAKE /f calibration.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "calibration.exe"
# PROP BASE Bsc_Name "calibration.bsc"
# PROP BASE Target_Dir ""
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Cmd_Line "NMAKE /C /f calibration.mak"
# PROP Rebuild_Opt "/a"
# PROP Target_File "..\..\include\calibration"
# PROP Bsc_Name "calibration.bsc"
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "calibration - Win32 Release"
# Name "calibration - Win32 Debug"

!IF  "$(CFG)" == "calibration - Win32 Release"

!ELSEIF  "$(CFG)" == "calibration - Win32 Debug"

!ENDIF 

# Begin Source File

SOURCE=..\..\SIunits\calibration
# End Source File
# Begin Source File

SOURCE=.\calibration.mak
# End Source File
# End Target
# End Project
