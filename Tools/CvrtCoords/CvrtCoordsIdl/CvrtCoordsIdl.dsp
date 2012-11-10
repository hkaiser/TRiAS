# Microsoft Developer Studio Project File - Name="CvrtCoordsIdl" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Generic Project" 0x010a

CFG=CvrtCoordsIdl - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "CvrtCoordsIdl.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CvrtCoordsIdl.mak" CFG="CvrtCoordsIdl - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CvrtCoordsIdl - Win32 Release" (based on "Win32 (x86) Generic Project")
!MESSAGE "CvrtCoordsIdl - Win32 Debug" (based on "Win32 (x86) Generic Project")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
MTL=midl.exe

!IF  "$(CFG)" == "CvrtCoordsIdl - Win32 Release"

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

!ELSEIF  "$(CFG)" == "CvrtCoordsIdl - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "CvrtCoordsIdl - Win32 Release"
# Name "CvrtCoordsIdl - Win32 Debug"
# Begin Group "Source FIles"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\CvrtCoords.idl

!IF  "$(CFG)" == "CvrtCoordsIdl - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=..\CvrtCoords.idl

BuildCmds= \
	midl /notlb /h ..\CvrtCoords_i.h /iid ..\CvrtCoords_i.c ..\CvrtCoords.idl

"..\CvrtCoords_i.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\CvrtCoords_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "CvrtCoordsIdl - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=..\CvrtCoords.idl

BuildCmds= \
	midl /notlb /h ..\CvrtCoords_i.h /iid ..\CvrtCoords_i.c ..\CvrtCoords.idl

"..\CvrtCoords_i.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\CvrtCoords_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
