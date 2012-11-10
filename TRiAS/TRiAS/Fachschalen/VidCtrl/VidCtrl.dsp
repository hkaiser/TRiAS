# Microsoft Developer Studio Project File - Name="VidCtrl" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=VidCtrl - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VidCtrl.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VidCtrl.mak" CFG="VidCtrl - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "VidCtrl - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "VidCtrl - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "VidCtrl - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /Zi /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Yu"stdafx.h" /Fd"Release/VidCtrl.pdb" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /Oicf /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 containr.lib delayimp.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"Release/VidCtrl.ext" /delayload:crp32dll.dll /delay:unload
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build
TargetDir=.\Release
TargetPath=.\Release\VidCtrl.ext
TargetName=VidCtrl
InputPath=.\Release\VidCtrl.ext
SOURCE="$(InputPath)"

"$(TRIASDIR_R)/$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" "$(TRIASDIR_R)" 
	xcopy /F "$(TargetDir)\$(TargetName).pdb" "$(TRIASDIR_R)" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "VidCtrl - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Fp"Debug/VidCtrld.pch" /Yu"stdafx.h" /Fd"Debug/VidCtrld.pdb" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /Oicf /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 cont50d.lib delayimp.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"Debug/VidCtrld.ext" /pdbtype:sept /delayload:crp32dll.dll /delay:unload
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build
TargetDir=.\Debug
TargetPath=.\Debug\VidCtrld.ext
TargetName=VidCtrld
InputPath=.\Debug\VidCtrld.ext
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" "$(TRIASDIR_D)" 
	xcopy /F "$(TargetDir)\$(TargetName).pdb" "$(TRIASDIR_D)" 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "VidCtrl - Win32 Release"
# Name "VidCtrl - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Docking support Sources"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=.\LayoutMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\MediaPlayer.cpp
# End Source File
# Begin Source File

SOURCE=.\VideoPaneCallback.cpp
# End Source File
# Begin Source File

SOURCE=.\VideoPaneWindowImpl.cpp
# End Source File
# End Group
# Begin Group "Extension Sources"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\HandleToolbar.cpp
# End Source File
# Begin Source File

SOURCE=.\Licence.cpp
# End Source File
# Begin Source File

SOURCE=.\VidCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\VidCtrlExt.cpp
# End Source File
# Begin Source File

SOURCE=.\VideoUIOwner.cpp
# End Source File
# End Group
# Begin Group "Actual Position Sources"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ConnectedCtf.cpp
# End Source File
# Begin Source File

SOURCE=.\HotSpot.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\VidCtrl.def
# End Source File
# Begin Source File

SOURCE=.\VidCtrl.idl
# End Source File
# Begin Source File

SOURCE=.\VidCtrl.rc
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "Docking support Headers"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=.\DialogView.h
# End Source File
# Begin Source File

SOURCE=.\LayoutMgr.h
# End Source File
# Begin Source File

SOURCE=.\MediaPlayer.h
# End Source File
# Begin Source File

SOURCE=.\MediaPlayerEvent.h
# End Source File
# Begin Source File

SOURCE=.\VideoPaneCallback.h
# End Source File
# Begin Source File

SOURCE=.\VideoPaneWindowImpl.h
# End Source File
# End Group
# Begin Group "Extension Headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\VidCtrlExt.h
# End Source File
# Begin Source File

SOURCE=.\VideoUIOwner.h
# End Source File
# End Group
# Begin Group "Actual Position Headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ConnectedCtf.h
# End Source File
# Begin Source File

SOURCE=.\HotSpot.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\VidCtrl.h
# End Source File
# Begin Source File

SOURCE=.\VidCtrlConfig.h
# End Source File
# Begin Source File

SOURCE=.\VidCtrlUtil.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Res\HotSpot.rgs
# End Source File
# Begin Source File

SOURCE=.\Res\videopane.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\videopane.ico
# End Source File
# Begin Source File

SOURCE=.\Res\VideoPaneTab.rgs
# End Source File
# Begin Source File

SOURCE=.\Res\videos.html
# End Source File
# End Group
# Begin Group "Versioning"

# PROP Default_Filter "*.mak;*.tpl"
# Begin Source File

SOURCE=.\Version.mak
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Version.tpl

!IF  "$(CFG)" == "VidCtrl - Win32 Release"

# PROP Ignore_Default_Tool 1
USERDEP__VERSI="Version.mak"	
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\Version.tpl

"Version.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak Version.h

# End Custom Build

!ELSEIF  "$(CFG)" == "VidCtrl - Win32 Debug"

# PROP Ignore_Default_Tool 1
USERDEP__VERSI="Version.mak"	
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\Version.tpl

"Version.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak Version.h

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\VIDCTRL.tpl

!IF  "$(CFG)" == "VidCtrl - Win32 Release"

# PROP Ignore_Default_Tool 1
USERDEP__VIDCT="Version.mak"	
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\VIDCTRL.tpl

"VidCtrl.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak VidCtrl.def

# End Custom Build

!ELSEIF  "$(CFG)" == "VidCtrl - Win32 Debug"

# PROP Ignore_Default_Tool 1
USERDEP__VIDCT="Version.mak"	
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\VIDCTRL.tpl

"VidCtrl.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak VidCtrl.def

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\VIDCTRLv.tpl

!IF  "$(CFG)" == "VidCtrl - Win32 Release"

# PROP Ignore_Default_Tool 1
USERDEP__VIDCTR="Version.mak"	
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\VIDCTRLv.tpl

"VidCtrl.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak VidCtrl.rcv

# End Custom Build

!ELSEIF  "$(CFG)" == "VidCtrl - Win32 Debug"

# PROP Ignore_Default_Tool 1
USERDEP__VIDCTR="Version.mak"	
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\VIDCTRLv.tpl

"VidCtrl.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak VidCtrl.rcv

# End Custom Build

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
# Section VidCtrl : {20D4F5E0-5475-11D2-9774-0000F80855E6}
# 	2:5:Class:CMediaPlayer2
# 	2:10:HeaderFile:mediaplayer2.h
# 	2:8:ImplFile:mediaplayer2.cpp
# End Section
# Section VidCtrl : {22D6F312-B0F6-11D0-94AB-0080C74C7E95}
# 	2:21:DefaultSinkHeaderFile:mediaplayer2.h
# 	2:16:DefaultSinkClass:CMediaPlayer2
# End Section
