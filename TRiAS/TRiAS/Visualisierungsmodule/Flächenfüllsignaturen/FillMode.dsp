# Microsoft Developer Studio Project File - Name="FillMode" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=FillMode - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "FillMode.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "FillMode.mak" CFG="FillMode - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "FillMode - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "FillMode - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=xicl6.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "FillMode - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D "MSWIND" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ospace5r.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:".\Release\FillMode.vmd"
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying Target to Destination ...
OutDir=.\Release
TargetPath=.\Release\FillMode.vmd
TargetName=FillMode
InputPath=.\Release\FillMode.vmd
SOURCE="$(InputPath)"

"$(TRIASDIR_R)\$(TargetName).vmd" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(TRIASDIR_R) 
	xcopy /F "$(OutDir)\$(TargetName).pdb" $(TRIASDIR_R) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "FillMode - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D "MSWIND" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 ospace5d.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:".\Debug\FillMode.vmd"
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying Target to Destination ...
OutDir=.\Debug
TargetPath=.\Debug\FillMode.vmd
TargetName=FillMode
InputPath=.\Debug\FillMode.vmd
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).vmd" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(TRIASDIR_D) 
	xcopy /F "$(OutDir)\$(TargetName).pdb" $(TRIASDIR_D) 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "FillMode - Win32 Release"
# Name "FillMode - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\Cgobject.cxx
# End Source File
# Begin Source File

SOURCE=.\FillArea.cpp
# End Source File
# Begin Source File

SOURCE=.\FillMode.cpp
# End Source File
# Begin Source File

SOURCE=.\FillMode.def
# End Source File
# Begin Source File

SOURCE=.\FillMode.rc
# End Source File
# Begin Source File

SOURCE=.\FillParm.cpp
# End Source File
# Begin Source File

SOURCE=.\Fixupdc.cpp
# End Source File
# Begin Source File

SOURCE=.\helper.cpp
# End Source File
# Begin Source File

SOURCE=.\Registry.cxx
# End Source File
# Begin Source File

SOURCE=.\Regvism.cxx
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\Cgobject.h
# End Source File
# Begin Source File

SOURCE=.\FillArea.h
# End Source File
# Begin Source File

SOURCE=.\FillModeConfig.h
# End Source File
# Begin Source File

SOURCE=.\FillParm.h
# End Source File
# Begin Source File

SOURCE=.\fixupdc.h
# End Source File
# Begin Source File

SOURCE=.\Helper.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\FillMode.rc2
# End Source File
# Begin Source File

SOURCE=.\FILLMODE.RCV
# End Source File
# End Group
# Begin Group "Versioning"

# PROP Default_Filter "*.tpl"
# Begin Source File

SOURCE=.\Fillmode.tpl

!IF  "$(CFG)" == "FillMode - Win32 Release"

USERDEP__FILLM="Version.mak"	
# Begin Custom Build
InputPath=.\Fillmode.tpl

"FillMode.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak FillMode.def

# End Custom Build

!ELSEIF  "$(CFG)" == "FillMode - Win32 Debug"

USERDEP__FILLM="Version.mak"	
# Begin Custom Build
InputPath=.\Fillmode.tpl

"FillMode.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak FillMode.def

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\FillModev.tpl

!IF  "$(CFG)" == "FillMode - Win32 Release"

USERDEP__FILLMO="Version.mak"	
# Begin Custom Build
InputPath=.\FillModev.tpl

"FillMode.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak FillMode.rcv

# End Custom Build

!ELSEIF  "$(CFG)" == "FillMode - Win32 Debug"

USERDEP__FILLMO="Version.mak"	
# Begin Custom Build
InputPath=.\FillModev.tpl

"FillMode.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak FillMode.rcv

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Version.mak
# End Source File
# End Group
# End Target
# End Project
