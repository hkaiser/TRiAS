# Microsoft Developer Studio Project File - Name="MapMgr" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=MapMgr - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MapMgr.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MapMgr.mak" CFG="MapMgr - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MapMgr - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MapMgr - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Xtension/MapMgr", KIDAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MapMgr - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Ext "ext"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "_Debug"
# PROP Intermediate_Dir "_Debug"
# PROP Target_Ext "ext"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MTd /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /i "$(TRIASINCLUDE)" /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 lpict42d.lib lmfcx42d.lib delayimp.lib /nologo /subsystem:windows /dll /debug /machine:I386 /def:".\MapMgr.def" /out:"_Debug/MapMgrD.ext" /pdbtype:sept /delayload:crp32dll.dll
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying Target to Destination ...
OutDir=.\_Debug
TargetPath=.\_Debug\MapMgrD.ext
TargetName=MapMgrD
InputPath=.\_Debug\MapMgrD.ext
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F /Y $(TargetPath) $(TRIASDIR_D) 
	xcopy /F /Y "$(OutDir)\$(TargetName).pdb" $(TRIASDIR_D) 
	
# End Custom Build
# Begin Special Build Tool
SOURCE="$(InputPath)"
PreLink_Cmds=nmake -nologo -f Version.mak CFG=_DEBUG VERSION
# End Special Build Tool

!ELSEIF  "$(CFG)" == "MapMgr - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "MapMgr__"
# PROP BASE Intermediate_Dir "MapMgr__"
# PROP BASE Target_Ext "ext"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "_Release"
# PROP Intermediate_Dir "_Release"
# PROP Target_Ext "ext"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /WX /GX /Z7 /O1 /I "$(TRIASDIR_R)" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /i "$(TRIASINCLUDE)" /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 lpict42.lib lmfcx42.lib delayimp.lib /nologo /subsystem:windows /dll /incremental:no /debug /machine:I386 /def:".\MapMgr.def" /delayload:crp32dll.dll
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
OutDir=.\_Release
TargetPath=.\_Release\MapMgr.ext
TargetName=MapMgr
InputPath=.\_Release\MapMgr.ext
SOURCE="$(InputPath)"

"$(TRIASDIR_R)\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F  /Y $(TargetPath) "$(TRIASDIR_R)" 
	xcopy /F /Y "$(OutDir)\$(TargetName).pdb" "$(TRIASDIR_R)" 
	
# End Custom Build
# Begin Special Build Tool
SOURCE="$(InputPath)"
PreLink_Cmds=nmake -nologo -f Version.mak CFG=NDEBUG VERSION
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "MapMgr - Win32 Debug"
# Name "MapMgr - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "TRiAS Extension"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MapImport.cpp
# End Source File
# Begin Source File

SOURCE=.\MapImport.h
# End Source File
# Begin Source File

SOURCE=.\MapMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\MapMgr.def
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "External Controls"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\maskedit.cpp
# End Source File
# Begin Source File

SOURCE=.\maskedit.h
# End Source File
# Begin Source File

SOURCE=.\triascsui.cpp
# End Source File
# Begin Source File

SOURCE=.\triascsui.h
# End Source File
# End Group
# Begin Group "MapImport"

# PROP Default_Filter ""
# Begin Group "Verzeichnisauswahl"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DDXGetFolder.cpp
# End Source File
# Begin Source File

SOURCE=.\DDXGetFolder.h
# End Source File
# Begin Source File

SOURCE=.\Dlgdir.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlgdir.h
# End Source File
# End Group
# Begin Group "Dateiauswahl"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DDXGetFile.cpp
# End Source File
# Begin Source File

SOURCE=.\DDXGetFile.h
# End Source File
# End Group
# Begin Group "Obsolete Dialogs"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\PpgImportFile.cpp
# End Source File
# Begin Source File

SOURCE=.\PpgImportFile.h
# End Source File
# Begin Source File

SOURCE=.\PpgIntergraph.cpp
# End Source File
# Begin Source File

SOURCE=.\ppgintergraph.h
# End Source File
# Begin Source File

SOURCE=.\PpgMapInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\PpgMapInfo.h
# End Source File
# Begin Source File

SOURCE=.\PpgNomenclatur.cpp
# End Source File
# Begin Source File

SOURCE=.\PpgNomenclatur.h
# End Source File
# Begin Source File

SOURCE=.\PpgRefPoints.cpp
# End Source File
# Begin Source File

SOURCE=.\PpgRefPoints.h
# End Source File
# Begin Source File

SOURCE=.\PpgSelAddFile.cpp
# End Source File
# Begin Source File

SOURCE=.\PpgSelAddFile.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\CheckFile.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\CoordSystemTree.cpp
# End Source File
# Begin Source File

SOURCE=.\CoordSystemTree.h
# End Source File
# Begin Source File

SOURCE=.\FileReduce.cpp
# End Source File
# Begin Source File

SOURCE=.\ImportDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ImportDlg.h
# End Source File
# Begin Source File

SOURCE=.\PpgBase.cpp
# End Source File
# Begin Source File

SOURCE=.\PpgBase.h
# End Source File
# Begin Source File

SOURCE=.\PpgSelDataSource.cpp
# End Source File
# Begin Source File

SOURCE=.\PpgSelDataSource.h
# End Source File
# Begin Source File

SOURCE=.\PpgSelFilesOrDirs.cpp
# End Source File
# Begin Source File

SOURCE=.\PpgSelFilesOrDirs.h
# End Source File
# Begin Source File

SOURCE=.\PpgSelMapType.cpp
# End Source File
# Begin Source File

SOURCE=.\PpgSelMapType.h
# End Source File
# Begin Source File

SOURCE=.\SelectCoordSys.cpp
# End Source File
# Begin Source File

SOURCE=.\SelectCoordSys.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\licence.cpp
# End Source File
# Begin Source File

SOURCE=.\MapCtrl\MapCtrlTree.h
# End Source File
# Begin Source File

SOURCE=.\MapMgr.idl

!IF  "$(CFG)" == "MapMgr - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Performing MIDL step
InputPath=.\MapMgr.idl

BuildCmds= \
	midl /Oicf /h "MapMgr.h" /iid "MapMgr_i.c" "MapMgr.idl"

".\MapMgr.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\MapMgr.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\MapMgr_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "MapMgr - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Performing MIDL step
InputPath=.\MapMgr.idl

BuildCmds= \
	midl /Oicf /h "MapMgr.h" /iid "MapMgr_i.c" "MapMgr.idl"

".\MapMgr.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\MapMgr.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\MapMgr_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MapMgrImpl.h
# End Source File
# Begin Source File

SOURCE=.\PictHolder.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Version.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Group "Registry Scripts"

# PROP Default_Filter "*.rgs"
# Begin Source File

SOURCE=.\MapMgr.rgs
# End Source File
# Begin Source File

SOURCE=.\res\PictHolder.rgs
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CoordSys.bmp
# End Source File
# Begin Source File

SOURCE=.\res\idr_main.ico
# End Source File
# Begin Source File

SOURCE=.\res\ImportLSaAnh.ico
# End Source File
# Begin Source File

SOURCE=.\res\luftbild.bmp
# End Source File
# Begin Source File

SOURCE=.\res\MapMgr.ico
# End Source File
# Begin Source File

SOURCE=.\MapMgr.rc
# End Source File
# Begin Source File

SOURCE=.\res\maptypes.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ProjectTypes.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ProjectTypesMask.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# End Group
# Begin Group "Versioning"

# PROP Default_Filter "*.mak,*.ver"
# Begin Source File

SOURCE=.\MapMgr.ver
# End Source File
# Begin Source File

SOURCE=.\Version.mak
# End Source File
# End Group
# Begin Source File

SOURCE=.\PictHolder.h
# End Source File
# End Target
# End Project
