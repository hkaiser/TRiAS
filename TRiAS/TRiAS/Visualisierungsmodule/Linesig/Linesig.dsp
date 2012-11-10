# Microsoft Developer Studio Project File - Name="LINESIG" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=LINESIG - WIN32 DEBUG
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Linesig.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Linesig.mak" CFG="LINESIG - WIN32 DEBUG"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "LINESIG - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "LINESIG - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/visobj/Linesig", LBDAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "LINESIG - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\LINESIG0"
# PROP BASE Intermediate_Dir ".\LINESIG0"
# PROP BASE Target_Ext "vmd"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "_Release"
# PROP Intermediate_Dir "_Release"
# PROP Target_Ext "vmd"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /Zp1 /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "__XT" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /O1 /I "..\..\FrameWrk\lmfcx42\\" /I "..\..\FrameWrk\lpict42\\" /I "..\libvmd\\" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "NDEBUG" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /I "..\..\vmd32\release" /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "__DATE__" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_WIN32" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /out:"c:\trias\trias200\linesig.vmd"
# SUBTRACT BASE LINK32 /map
# ADD LINK32 /nologo /subsystem:windows /dll /incremental:no /debug /machine:I386
# SUBTRACT LINK32 /pdb:none /map
# Begin Custom Build
OutDir=.\_Release
TargetName=Linesig
InputPath=.\_Release\Linesig.vmd
SOURCE="$(InputPath)"

"$(TRIASDIR_R)\$(TargetName).vmd" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(OutDir)\$(TargetName).vmd" "$(TRIASDIR_R)" 
	xcopy /F "$(OutDir)\$(TargetName).pdb" "$(TRIASDIR_R)" 
	
# End Custom Build
# Begin Special Build Tool
SOURCE="$(InputPath)"
PreLink_Cmds=nmake -nologo -f Version.mak CFG=NDEBUG VERSION
# End Special Build Tool

!ELSEIF  "$(CFG)" == "LINESIG - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\_Debug"
# PROP BASE Intermediate_Dir ".\_Debug"
# PROP BASE Target_Ext "vmd"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "_Debug"
# PROP Intermediate_Dir "_Debug"
# PROP Target_Ext "vmd"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /Zp1 /MD /W3 /Gm /GX /Zi /D "NDEBUG" /D "_WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /I "..\..\FrameWrk\lmfcx42\\" /I "..\..\FrameWrk\lpict42\\" /I "..\libvmd\\" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_DEBUG" /Fr /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /I "..\..\vmd32\release" /D "NDEBUG" /win32
# ADD MTL /nologo /I "..\..\vmd32\debug" /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "__DATE__" /d "_AFXDLL" /d "_WIN32"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_WIN32" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /pdb:none /machine:I386 /out:"c:\trias\trias200\release\LINESIG.vmd"
# SUBTRACT BASE LINK32 /map /debug
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /out:"_Debug/LinesigD.vmd" /libpath:"..\..\lib"
# SUBTRACT LINK32 /pdb:none /map
# Begin Custom Build
OutDir=.\_Debug
TargetName=LinesigD
InputPath=.\_Debug\LinesigD.vmd
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

# Name "LINESIG - Win32 Release"
# Name "LINESIG - Win32 Debug"
# Begin Group "Linesig"

# PROP Default_Filter ""
# Begin Group "Dialogs"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\dlglines.cpp
# End Source File
# Begin Source File

SOURCE=.\dlglines.h
# End Source File
# Begin Source File

SOURCE=.\lsigppg.cpp
# End Source File
# Begin Source File

SOURCE=.\lsigppg.h
# End Source File
# Begin Source File

SOURCE=.\PgError.cpp
# End Source File
# Begin Source File

SOURCE=.\PgError.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\linesig.cpp
# End Source File
# Begin Source File

SOURCE=.\lsignat.cpp
# End Source File
# Begin Source File

SOURCE=.\lsignat.h
# End Source File
# Begin Source File

SOURCE=.\METADEBG.CPP

!IF  "$(CFG)" == "LINESIG - Win32 Release"

!ELSEIF  "$(CFG)" == "LINESIG - Win32 Debug"

# PROP BASE Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MetaEnum.cpp
# End Source File
# Begin Source File

SOURCE=.\METAFILE.CPP
# End Source File
# Begin Source File

SOURCE=.\metafile.h
# End Source File
# Begin Source File

SOURCE=.\MetaMemory.cpp
# End Source File
# Begin Source File

SOURCE=.\Segment.cpp
# End Source File
# End Group
# Begin Group "DLL Data"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\linesig.h
# End Source File
# Begin Source File

SOURCE=.\Linesig.idl

!IF  "$(CFG)" == "LINESIG - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\Linesig.idl

BuildCmds= \
	nmake -nologo -f version.mak CFG=NDEBUG

".\LINESIG.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\LINESIG.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(TRIASTLB)\LINESIG.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "LINESIG - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\Linesig.idl

BuildCmds= \
	nmake -nologo -f version.mak CFG=_DEBUG

".\LINESIG.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\LINESIG.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(TRIASTLB)\LINESIG.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\LinesigImpl.h
# End Source File
# Begin Source File

SOURCE=.\STDAFX.CPP
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\stdafx.h
# End Source File
# Begin Source File

SOURCE=.\Version.mak

!IF  "$(CFG)" == "LINESIG - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\Version.mak

BuildCmds= \
	nmake -nologo -f version.mak CFG=NDEBUG

".\LINESIG.ver" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\LINESIG.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\LINESIG.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "LINESIG - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\Version.mak

BuildCmds= \
	nmake -nologo -f version.mak CFG=_DEBUG

".\LINESIG.ver" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\LINESIG.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\LINESIG.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Versioning"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Linesig.DEF
# End Source File
# Begin Source File

SOURCE=.\Linesig.rcv
# End Source File
# Begin Source File

SOURCE=.\Linesig.ver
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\BMP_WMFB.BMP
# End Source File
# Begin Source File

SOURCE=.\RES\default1.bin
# End Source File
# Begin Source File

SOURCE=.\LINESIG.rc
# End Source File
# Begin Source File

SOURCE=.\WMF\MetaFile.RCV
# End Source File
# Begin Source File

SOURCE=.\RES\msg00407.bin
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\RES\VMDICO.ICO
# End Source File
# End Group
# Begin Group "Help Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\help\Linesig.d

!IF  "$(CFG)" == "LINESIG - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\help\Linesig.d
InputName=Linesig

"$(TRIASINCLUDE)\help\$(InputName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak CFG=NDEBUG

# End Custom Build

!ELSEIF  "$(CFG)" == "LINESIG - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\help\Linesig.d
InputName=Linesig

"$(TRIASINCLUDE)\help\$(InputName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak CFG=_DEBUG

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Linesig.mc

!IF  "$(CFG)" == "LINESIG - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\Linesig.mc

BuildCmds= \
	nmake -nologo -f version.mak CFG=NDEBUG

".\LINESIG.hmc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\res\msg00407.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\res\msg00409.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "LINESIG - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\Linesig.mc

BuildCmds= \
	nmake -nologo -f version.mak CFG=_DEBUG

".\LINESIG.hmc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
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
