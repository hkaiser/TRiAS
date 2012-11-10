# Microsoft Developer Studio Project File - Name="LoadableCommands" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=LoadableCommands - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "LoadableCommands.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "LoadableCommands.mak" CFG="LoadableCommands - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "LoadableCommands - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "LoadableCommands - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "LoadableCommands - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /Zi /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /Oicf /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /out:"Release/LoadableCommands.ext"
# Begin Custom Build
OutDir=.\Release
TargetName=LoadableCommands
InputPath=.\Release\LoadableCommands.ext
SOURCE="$(InputPath)"

"$(TRIASDIR_R)\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(OutDir)\$(TargetName).ext" "$(TRIASDIR_R)" 
	xcopy /F "$(OutDir)\$(TargetName).pdb" "$(TRIASDIR_R)" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "LoadableCommands - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Fp"Debug/LoadableCommandsd.pch" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /Oicf /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /out:"Debug/LoadableCommandsd.ext" /pdbtype:sept
# Begin Custom Build
OutDir=.\Debug
TargetName=LoadableCommandsd
InputPath=.\Debug\LoadableCommandsd.ext
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(OutDir)\$(TargetName).ext" "$(TRIASDIR_D)" 
	xcopy /F "$(OutDir)\$(TargetName).pdb" "$(TRIASDIR_D)" 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "LoadableCommands - Win32 Release"
# Name "LoadableCommands - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\LoadableCommands.cpp
# End Source File
# Begin Source File

SOURCE=.\LoadableCommands.def
# End Source File
# Begin Source File

SOURCE=.\LoadableCommands.idl
# End Source File
# Begin Source File

SOURCE=.\LoadableCommands.rc
# End Source File
# Begin Source File

SOURCE=.\LoadableCommandsExt.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\LoadableCommands.h
# End Source File
# Begin Source File

SOURCE=.\LoadableCommandsConfig.h
# End Source File
# Begin Source File

SOURCE=.\LoadableCommandsExt.h
# End Source File
# Begin Source File

SOURCE=.\LoadableCommandsUtil.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "Versioning"

# PROP Default_Filter "*.mak;*.tpl"
# Begin Source File

SOURCE=.\LoadableCommands.tpl

!IF  "$(CFG)" == "LoadableCommands - Win32 Release"

# PROP Ignore_Default_Tool 1
USERDEP__LOADA="version.mak"	
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\LoadableCommands.tpl

"LoadableCommands.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak LoadableCommands.def

# End Custom Build

!ELSEIF  "$(CFG)" == "LoadableCommands - Win32 Debug"

# PROP Ignore_Default_Tool 1
USERDEP__LOADA="version.mak"	
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\LoadableCommands.tpl

"LoadableCommands.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak LoadableCommands.def

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\LoadableCommandsv.tpl

!IF  "$(CFG)" == "LoadableCommands - Win32 Release"

# PROP Ignore_Default_Tool 1
USERDEP__LOADAB="version.mak"	
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\LoadableCommandsv.tpl

"LoadableCommands.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak LoadableCommands.rcv

# End Custom Build

!ELSEIF  "$(CFG)" == "LoadableCommands - Win32 Debug"

# PROP Ignore_Default_Tool 1
USERDEP__LOADAB="version.mak"	
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\LoadableCommandsv.tpl

"LoadableCommands.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak LoadableCommands.rcv

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Version.mak
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Version.tpl

!IF  "$(CFG)" == "LoadableCommands - Win32 Release"

# PROP Ignore_Default_Tool 1
USERDEP__VERSI="version.mak"	
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\Version.tpl

"Version.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak Version.h

# End Custom Build

!ELSEIF  "$(CFG)" == "LoadableCommands - Win32 Debug"

# PROP Ignore_Default_Tool 1
USERDEP__VERSI="version.mak"	
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\Version.tpl

"Version.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak Version.h

# End Custom Build

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
