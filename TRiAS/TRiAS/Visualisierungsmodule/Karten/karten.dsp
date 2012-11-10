# Microsoft Developer Studio Project File - Name="karten" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=karten - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "karten.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "karten.mak" CFG="karten - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "karten - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "karten - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/visobj/karten", BADAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "karten - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Ext "vmd"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "_Release"
# PROP Intermediate_Dir "_Release"
# PROP Target_Ext "vmd"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /O1 /I "..\..\FrameWrk\lmfcx42\\" /I "..\..\FrameWrk\lpict42\\" /I "..\libvmd\\" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "NDEBUG" /Fr /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /I "..\..\vmd32\release" /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# SUBTRACT LINK32 /pdb:none /incremental:yes /map
# Begin Custom Build - Copy Target
OutDir=.\_Release
TargetName=karten
InputPath=.\_Release\karten.vmd
SOURCE="$(InputPath)"

"$(TRIASDIR_R)\$(TargetName).vmd" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(OutDir)\$(TargetName).vmd $(TRIASDIR_R) 
	xcopy /F $(OutDir)\$(TargetName).pdb $(TRIASDIR_R) 
	
# End Custom Build
# Begin Special Build Tool
SOURCE="$(InputPath)"
PreLink_Cmds=nmake -nologo -f Version.mak CFG=NDEBUG VERSION
# End Special Build Tool

!ELSEIF  "$(CFG)" == "karten - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Ext "vmd"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "_Debug"
# PROP Intermediate_Dir "_Debug"
# PROP Target_Ext "vmd"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /I "..\..\FrameWrk\lmfcx42\\" /I "..\..\FrameWrk\lpict42\\" /I "..\libvmd\\" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_DEBUG" /Fr /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /I "..\..\vmd32\debug" /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /out:"_Debug/kartenD.vmd" /libpath:"..\..\lib"
# SUBTRACT LINK32 /incremental:no
# Begin Custom Build
OutDir=.\_Debug
TargetName=kartenD
InputPath=.\_Debug\kartenD.vmd
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).vmd" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(OutDir)\$(TargetName).vmd" "$(TRIASDIR_D)" 
	xcopy /F "$(OutDir)\$(TargetName).pdb" "$(TRIASDIR_D)" 
	
# End Custom Build
# Begin Special Build Tool
SOURCE="$(InputPath)"
PreLink_Cmds=nmake -nologo -f Version.mak CFG=_DEBUG VERSION
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "karten - Win32 Release"
# Name "karten - Win32 Debug"
# Begin Group "Karten"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\colorctrl.h
# End Source File
# Begin Source File

SOURCE=.\dialogs.cpp
# End Source File
# Begin Source File

SOURCE=.\dialogs.h
# End Source File
# Begin Source File

SOURCE=.\DlgPgBW.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPgBW.h
# End Source File
# Begin Source File

SOURCE=.\ImagePropertySheet.cpp
# End Source File
# Begin Source File

SOURCE=.\ImagePropertySheet.h
# End Source File
# Begin Source File

SOURCE=.\tkarten.cpp
# End Source File
# Begin Source File

SOURCE=.\TKarten.h
# End Source File
# Begin Source File

SOURCE=.\tkdraw.cpp
# End Source File
# Begin Source File

SOURCE=.\tkguids.cpp
# End Source File
# End Group
# Begin Group "DLL Data"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\karten.cpp
# End Source File
# Begin Source File

SOURCE=.\karten.h
# End Source File
# Begin Source File

SOURCE=.\Karten.idl

!IF  "$(CFG)" == "karten - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\Karten.idl
InputName=Karten

BuildCmds= \
	nmake -nologo -f version.mak CFG=NDEBUG

".\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\$(InputName).tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(TRIASTLB)\$(InputName).tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "karten - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\Karten.idl
InputName=Karten

BuildCmds= \
	nmake -nologo -f version.mak CFG=_DEBUG

".\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\$(InputName).tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(TRIASTLB)\$(InputName).tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\karten.odl
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\KartenImpl.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\stdafx.h
# End Source File
# Begin Source File

SOURCE=.\Version.mak

!IF  "$(CFG)" == "karten - Win32 Release"

# Begin Custom Build
InputPath=.\Version.mak

BuildCmds= \
	nmake -nologo -f version.mak CFG=NDEBUG

"./Karten.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"./Karten.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"./Karten.ver" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "karten - Win32 Debug"

# Begin Custom Build
InputPath=.\Version.mak

BuildCmds= \
	nmake -nologo -f version.mak CFG=_DEBUG

"./Karten.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"./Karten.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"./Karten.ver" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Versioning"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\karten.def
# End Source File
# Begin Source File

SOURCE=.\Karten.rcv
# End Source File
# Begin Source File

SOURCE=.\Karten.ver
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\karten.rc

!IF  "$(CFG)" == "karten - Win32 Release"

!ELSEIF  "$(CFG)" == "karten - Win32 Debug"

# ADD BASE RSC /l 0x407 /i "_Debug" /i ".\_Debug"
# ADD RSC /l 0x407 /i "_Debug" /i ".\_Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RES\msg00407.bin
# End Source File
# Begin Source File

SOURCE=.\RES\TKARTEN.BMP
# End Source File
# Begin Source File

SOURCE=.\RES\VMDICO.ICO
# End Source File
# End Group
# Begin Group "Help Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\help\Karten.d
# End Source File
# Begin Source File

SOURCE=.\Karten.mc

!IF  "$(CFG)" == "karten - Win32 Release"

# Begin Custom Build
InputPath=.\Karten.mc

BuildCmds= \
	nmake -nologo -f version.mak CFG=NDEBUG

".\Karten.hmc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\res\msg00407.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\res\msg00409.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "karten - Win32 Debug"

# Begin Custom Build
InputPath=.\Karten.mc

BuildCmds= \
	nmake -nologo -f version.mak CFG=_DEBUG

".\Karten.hmc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\res\msg00407.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\res\msg00409.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
# Section karten : {77472C71-3566-11D0-B4BF-00A024145748}
# 	2:5:Class:CColorControl
# 	2:10:HeaderFile:colorctrl.h
# 	2:8:ImplFile:colorctrl.cpp
# End Section
# Section OLE Controls
# 	{77472C73-3566-11D0-B4BF-00A024145748}
# End Section
# Section karten : {77472C73-3566-11D0-B4BF-00A024145748}
# 	0:8:Colors.h:C:\TRIASDEV.MVC\visobj\karten\src\Colors.h
# 	0:10:Colors.cpp:C:\TRIASDEV.MVC\visobj\karten\src\Colors.cpp
# 	2:21:DefaultSinkHeaderFile:colorctrl.h
# 	2:16:DefaultSinkClass:CColorControl
# End Section
