# Microsoft Developer Studio Project File - Name="MapCtrl" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=MAPCTRL - WIN32 DEBUG
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MapCtrl.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MapCtrl.mak" CFG="MAPCTRL - WIN32 DEBUG"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MapCtrl - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MapCtrl - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Xtension/MapMgr/MapCtrl", TSDAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MapCtrl - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "_Debug"
# PROP Intermediate_Dir "_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MTd /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /Gi /GX /ZI /Od /I "$(TRIASDIR_D)" /I "$(TRIASINCLUDE)" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /i "$(TRIASINCLUDE)" /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /out:"_Debug/MapCtrlD.dll" /pdbtype:sept
# Begin Special Build Tool
SOURCE="$(InputPath)"
PreLink_Cmds=nmake -nologo -f Version.mak CFG=_DEBUG VERSION
# End Special Build Tool

!ELSEIF  "$(CFG)" == "MapCtrl - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "MapCtrl_"
# PROP BASE Intermediate_Dir "MapCtrl_"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "_Release"
# PROP Intermediate_Dir "_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O1 /I "$(TRIASDIR_R)" /D "WIN32" /D "_WINDOWS" /D "NDEBUG" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /i "$(TRIASINCLUDE)" /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
# Begin Special Build Tool
SOURCE="$(InputPath)"
PreLink_Cmds=nmake -nologo -f Version.mak CFG=NDEBUG VERSION
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "MapCtrl - Win32 Debug"
# Name "MapCtrl - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\MapCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\MapCtrl.def
# End Source File
# Begin Source File

SOURCE=.\MapCtrl.idl

!IF  "$(CFG)" == "MapCtrl - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Performing MIDL step
InputPath=.\MapCtrl.idl

BuildCmds= \
	midl /Oicf /h "MapCtrl.h" /iid "MapCtrl_i.c" "MapCtrl.idl" \
	xcopy /F  MapCtrl.tlb $(TRIASTLB) \
	

".\MapCtrl.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\MapCtrl.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\MapCtrl_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "MapCtrl - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Performing MIDL step
InputPath=.\MapCtrl.idl

BuildCmds= \
	midl /Oicf /h "MapCtrl.h" /iid "MapCtrl_i.c" "MapCtrl.idl" \
	xcopy /F MapCtrl.tlb $(TRIASTLB) \
	

".\MapCtrl.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\MapCtrl.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\MapCtrl_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MapCtrl.rc
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\MapCtrlImpl.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Version"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Version.h
# End Source File
# Begin Source File

SOURCE=.\Version.mak
# End Source File
# Begin Source File

SOURCE=.\Version\Version.rcv

!IF  "$(CFG)" == "MapCtrl - Win32 Debug"

# Begin Custom Build - Generating Version.rcv
InputPath=.\Version\Version.rcv

"$(TRIASINCLUDE)\Version.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(InputPath) $(TRIASINCLUDE)

# End Custom Build

!ELSEIF  "$(CFG)" == "MapCtrl - Win32 Release"

# Begin Custom Build - Generating Version.rcv
InputPath=.\Version\Version.rcv

"$(TRIASINCLUDE)\Version.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(InputPath) $(TRIASINCLUDE)

# End Custom Build

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
