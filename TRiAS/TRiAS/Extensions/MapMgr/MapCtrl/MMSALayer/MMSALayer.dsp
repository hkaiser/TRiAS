# Microsoft Developer Studio Project File - Name="MMSALayer" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=MMSALayer - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MMSALayer.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MMSALayer.mak" CFG="MMSALayer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MMSALayer - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MMSALayer - Win32 Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/TRiAS/TRiAS/Extensions/MapMgr", FXFBAAAA"
# PROP Scc_LocalPath "..\.."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MMSALayer - Win32 Debug"

# PROP BASE Use_MFC 2
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
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "$(TRIASDIR_D)" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /i "$(TRIASINCLUDE)" /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /out:"_Debug/MMSALayerD.dll" /pdbtype:sept
# Begin Custom Build - Copying Target to Destination ...
OutDir=.\_Debug
TargetPath=.\_Debug\MMSALayerD.dll
TargetName=MMSALayerD
InputPath=.\_Debug\MMSALayerD.dll
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(Targetname).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(TargetPath) $(TRIASDIR_D) 
	xcopy /F /Y "$(OutDir)\$(TargetName).pdb" $(TRIASDIR_D) 
	
# End Custom Build
# Begin Special Build Tool
SOURCE="$(InputPath)"
PreLink_Cmds=nmake -nologo -f Version.mak CFG=_DEBUG VERSION
# End Special Build Tool

!ELSEIF  "$(CFG)" == "MMSALayer - Win32 Release MinSize"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMinSize"
# PROP BASE Intermediate_Dir "ReleaseMinSize"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "_Release"
# PROP Intermediate_Dir "_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /WX /GX /Z7 /O1 /D "WIN32" /D "_WINDOWS" /D "NDEBUG" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /i "$(TRIASINCLUDE)" /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
OutDir=.\_Release
TargetPath=.\_Release\MMSALayer.dll
TargetName=MMSALayer
InputPath=.\_Release\MMSALayer.dll
SOURCE="$(InputPath)"

"$(TRIASDIR_R)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F  /Y $(TargetPath) "$(TRIASDIR_R)" 
	xcopy /F /Y "$(OutDir)\$(TargetName).pdb" "$(TRIASDIR_R)" 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "MMSALayer - Win32 Debug"
# Name "MMSALayer - Win32 Release MinSize"
# Begin Group "Quellcodedateien"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\MapSALayer.cpp

!IF  "$(CFG)" == "MMSALayer - Win32 Debug"

# PROP Intermediate_Dir "_Debug"

!ELSEIF  "$(CFG)" == "MMSALayer - Win32 Release MinSize"

# ADD CPP /I "$(TRIASDIR_R)"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MMSALayer.cpp

!IF  "$(CFG)" == "MMSALayer - Win32 Debug"

# PROP Intermediate_Dir "_Debug"

!ELSEIF  "$(CFG)" == "MMSALayer - Win32 Release MinSize"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MMSALayer.def

!IF  "$(CFG)" == "MMSALayer - Win32 Debug"

# PROP Intermediate_Dir "_Debug"

!ELSEIF  "$(CFG)" == "MMSALayer - Win32 Release MinSize"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MMSALayer.idl

!IF  "$(CFG)" == "MMSALayer - Win32 Debug"

# PROP Intermediate_Dir "_Debug"
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Performing MIDL step
InputPath=.\MMSALayer.idl

BuildCmds= \
	midl /Oicf /h "MMSALayer.h" /iid "MMSALayer_i.c" "MMSALayer.idl"

".\MMSALayer.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\MMSALayer.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\MMSALayer_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "MMSALayer - Win32 Release MinSize"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\MMSALayer.idl

BuildCmds= \
	midl /Oicf /h "MMSALayer.h" /iid "MMSALayer_i.c" "MMSALayer.idl"

".\MMSALayer.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\MMSALayer.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\MMSALayer_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MMSALayer.rc

!IF  "$(CFG)" == "MMSALayer - Win32 Debug"

# PROP Intermediate_Dir "_Debug"
# ADD BASE RSC /l 0x407
# ADD RSC /l 0x407

!ELSEIF  "$(CFG)" == "MMSALayer - Win32 Release MinSize"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "MMSALayer - Win32 Debug"

# PROP Intermediate_Dir "_Debug"
# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "MMSALayer - Win32 Release MinSize"

# ADD CPP /Yc"stdafx.h"

!ENDIF 

# End Source File
# End Group
# Begin Group "Header-Dateien"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\MapSALayer.h

!IF  "$(CFG)" == "MMSALayer - Win32 Debug"

# PROP Intermediate_Dir "_Debug"

!ELSEIF  "$(CFG)" == "MMSALayer - Win32 Release MinSize"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MMSALayer.h

!IF  "$(CFG)" == "MMSALayer - Win32 Debug"

# PROP Intermediate_Dir "_Debug"

!ELSEIF  "$(CFG)" == "MMSALayer - Win32 Release MinSize"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Resource.h

!IF  "$(CFG)" == "MMSALayer - Win32 Debug"

# PROP Intermediate_Dir "_Debug"

!ELSEIF  "$(CFG)" == "MMSALayer - Win32 Release MinSize"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\StdAfx.h

!IF  "$(CFG)" == "MMSALayer - Win32 Debug"

# PROP Intermediate_Dir "_Debug"

!ELSEIF  "$(CFG)" == "MMSALayer - Win32 Release MinSize"

!ENDIF 

# End Source File
# End Group
# Begin Group "Ressourcendateien"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\MapSALayer.rgs

!IF  "$(CFG)" == "MMSALayer - Win32 Debug"

# PROP Intermediate_Dir "_Debug"

!ELSEIF  "$(CFG)" == "MMSALayer - Win32 Release MinSize"

!ENDIF 

# End Source File
# End Group
# Begin Group "Versioning"

# PROP Default_Filter "*.mak,*.ver"
# Begin Source File

SOURCE=.\MMSaLayer.ver
# End Source File
# Begin Source File

SOURCE=.\VERSION.H
# End Source File
# Begin Source File

SOURCE=.\Version.mak
# End Source File
# End Group
# End Target
# End Project
