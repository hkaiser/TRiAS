# Microsoft Developer Studio Project File - Name="MMFkSanh" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=MMFKSANH - WIN32 DEBUG
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MMFkSanh.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MMFkSanh.mak" CFG="MMFKSANH - WIN32 DEBUG"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MMFkSanh - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MMFkSanh - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Xtension/MapMgr/MapCtrl/MMFkSanh", UTDAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MMFkSanh - Win32 Debug"

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
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "$(TRIASDIR_D)" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /i "$(TRIASINCLUDE)" /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /out:"_Debug/MMFkSanhD.dll" /pdbtype:sept
# Begin Custom Build - Copying Target to Destination ...
OutDir=.\_Debug
TargetPath=.\_Debug\MMFkSanhD.dll
TargetName=MMFkSanhD
InputPath=.\_Debug\MMFkSanhD.dll
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(Targetname).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(TargetPath) $(TRIASDIR_D) 
	xcopy /F /Y "$(OutDir)\$(TargetName).pdb" $(TRIASDIR_D) 
	
# End Custom Build
# Begin Special Build Tool
SOURCE="$(InputPath)"
PreLink_Cmds=nmake -nologo -f Version.mak CFG=_DEBUG VERSION
# End Special Build Tool

!ELSEIF  "$(CFG)" == "MMFkSanh - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "MMFkSanh"
# PROP BASE Intermediate_Dir "MMFkSanh"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "_Release"
# PROP Intermediate_Dir "_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MD /W3 /GX /O1 /I "$(TRIASINCLUDE)" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /WX /GX /Z7 /O1 /I "$(TRIASDIR_R)" /D "WIN32" /D "_WINDOWS" /D "NDEBUG" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x407 /i "$(TRIASINCLUDE)" /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /i "$(TRIASINCLUDE)" /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
OutDir=.\_Release
TargetPath=.\_Release\MMFkSanh.dll
TargetName=MMFkSanh
InputPath=.\_Release\MMFkSanh.dll
SOURCE="$(InputPath)"

"$(TRIASDIR_R)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F  /Y $(TargetPath) "$(TRIASDIR_R)" 
	xcopy /F /Y "$(OutDir)\$(TargetName).pdb" "$(TRIASDIR_R)" 
	
# End Custom Build
# Begin Special Build Tool
SOURCE="$(InputPath)"
PreLink_Cmds=nmake -nologo -f Version.mak CFG=NDEBUG VERSION
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "MMFkSanh - Win32 Debug"
# Name "MMFkSanh - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\dlldatax.c
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\MapLVermA.cpp
# End Source File
# Begin Source File

SOURCE=.\MapLVermA.h
# End Source File
# Begin Source File

SOURCE=.\MMFkSanh.cpp
# End Source File
# Begin Source File

SOURCE=.\MMFkSanh.def
# End Source File
# Begin Source File

SOURCE=.\MMFkSanh.idl

!IF  "$(CFG)" == "MMFkSanh - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Performing MIDL step
InputPath=.\MMFkSanh.idl

BuildCmds= \
	midl /Oicf /h "MMFkSanh.h" /iid "MMFkSanh_i.c" "MMFkSanh.idl"

".\MMFkSanh.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\MMFkSanh.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\MMFkSanh_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "MMFkSanh - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Performing MIDL step
InputPath=.\MMFkSanh.idl

BuildCmds= \
	midl /Oicf /h "MMFkSanh.h" /iid "MMFkSanh_i.c" "MMFkSanh.idl"

".\MMFkSanh.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\MMFkSanh.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\MMFkSanh_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MMFkSanh.rc
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Y_MOSS.CPP
# End Source File
# Begin Source File

SOURCE=.\Y_MOSS.y

!IF  "$(CFG)" == "MMFkSanh - Win32 Debug"

# Begin Custom Build
InputPath=.\Y_MOSS.y
InputName=Y_MOSS

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	pcyacc -n -C$(InputName).cpp -pyynamesp.skl $(InputName).y

# End Custom Build

!ELSEIF  "$(CFG)" == "MMFkSanh - Win32 Release"

# Begin Custom Build
InputPath=.\Y_MOSS.y
InputName=Y_MOSS

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	pcyacc -n -C$(InputName).cpp -pyynamesp.skl $(InputName).y

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\dlldatax.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\MapCtrlImpl.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\MapLVermA.rgs
# End Source File
# End Group
# Begin Group "Versioning"

# PROP Default_Filter "*.mak,*.ver"
# Begin Source File

SOURCE=.\MMFkSanh.ver
# End Source File
# Begin Source File

SOURCE=.\Version.h
# End Source File
# Begin Source File

SOURCE=.\Version.mak
# End Source File
# End Group
# End Target
# End Project
