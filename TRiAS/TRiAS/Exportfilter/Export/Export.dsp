# Microsoft Developer Studio Project File - Name="Export" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=Export - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Export.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Export.mak" CFG="Export - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Export - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Export - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Export - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "_Release"
# PROP Intermediate_Dir "_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /Oicf /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 delayimp.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"_Release/Export.ext" /delayload:comctl32.dll /delayload:ole32.dll /delayload:oleaut32.dll /delayload:shell32.dll /delayload:advapi32.dll
# Begin Custom Build
OutDir=.\_Release
TargetName=Export
InputPath=.\_Release\Export.ext
SOURCE="$(InputPath)"

"$(TRIASDIR_R)\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(OutDir)\$(TargetName).ext" "$(TRIASDIR_R)" 
	xcopy /F "$(OutDir)\$(TargetName).pdb" "$(TRIASDIR_R)" 
	
# End Custom Build
# Begin Special Build Tool
SOURCE="$(InputPath)"
PreLink_Cmds=nmake -nologo -f Version.mak CFG=NDEBUG VERSION
# End Special Build Tool

!ELSEIF  "$(CFG)" == "Export - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /WX /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /Fr /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /Oicf /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 delayimp.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"_Debug/Exportd.ext" /delayload:comctl32.dll /delayload:ole32.dll /delayload:oleaut32.dll /delayload:shell32.dll /delayload:advapi32.dll
# SUBTRACT LINK32 /incremental:no
# Begin Custom Build
OutDir=.\_Debug
TargetName=Exportd
InputPath=.\_Debug\Exportd.ext
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(OutDir)\$(TargetName).ext" "$(TRIASDIR_D)" 
	xcopy /F "$(OutDir)\$(TargetName).pdb" "$(TRIASDIR_D)" 
	
# End Custom Build
# Begin Special Build Tool
SOURCE="$(InputPath)"
PreLink_Cmds=nmake -nologo -f Version.mak CFG=_DEBUG VERSION
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "Export - Win32 Release"
# Name "Export - Win32 Debug"
# Begin Group "Export"

# PROP Default_Filter ""
# Begin Group "OldCode"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\OldCode\AutoBuildCount.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\OldCode\dbobject.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\OldCode\EXPORT.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\OldCode\EXPORT.H
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\OldCode\ExportApp.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\OldCode\ExportApp.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\OldCode\strings.cxx
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\OldCode\strings.h
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Source File

SOURCE=.\Convert.cpp
# End Source File
# Begin Source File

SOURCE=.\CoordSystemTree.cpp
# End Source File
# Begin Source File

SOURCE=.\CoordSystemTree.h
# End Source File
# Begin Source File

SOURCE=.\ExportPropertyAction.cpp
# End Source File
# Begin Source File

SOURCE=.\ExportPropertyAction.h
# End Source File
# Begin Source File

SOURCE=.\ExportPropertyActionDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ExportPropertyActionDlg.h
# End Source File
# Begin Source File

SOURCE=.\ExportUtil.cpp
# End Source File
# Begin Source File

SOURCE=.\ExportUtil.h
# End Source File
# Begin Source File

SOURCE=.\ExportXtension.cpp
# End Source File
# Begin Source File

SOURCE=.\ExportXTension.h
# End Source File
# Begin Source File

SOURCE=.\ObjGeomW.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjGeomW.h
# End Source File
# Begin Source File

SOURCE=.\ObjPropTree.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjPropTree.h
# End Source File
# Begin Source File

SOURCE=.\PathDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\PathDialog.h
# End Source File
# Begin Source File

SOURCE=.\SelectCoordSysActionDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SelectCoordSysActionDlg.h
# End Source File
# Begin Source File

SOURCE=.\SelectObjPropsToExport.cpp
# End Source File
# Begin Source File

SOURCE=.\SelectObjPropsToExport.h
# End Source File
# Begin Source File

SOURCE=.\Separator.cpp
# End Source File
# Begin Source File

SOURCE=.\Separator.h
# End Source File
# Begin Source File

SOURCE=.\StaticFilespec.cpp
# End Source File
# Begin Source File

SOURCE=.\StaticFilespec.h
# End Source File
# Begin Source File

SOURCE=.\Strings.cpp
# End Source File
# Begin Source File

SOURCE=.\Strings.h
# End Source File
# End Group
# Begin Group "DLL Data"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Export.cpp
# End Source File
# Begin Source File

SOURCE=.\Export.idl

!IF  "$(CFG)" == "Export - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\Export.idl

BuildCmds= \
	nmake -nologo -f version.mak CFG=NDEBUG

".\Export.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Export.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(TRIASTLB)\Export.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Export - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\Export.idl

BuildCmds= \
	nmake -nologo -f version.mak CFG=_DEBUG

".\Export.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Export.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(TRIASTLB)\Export.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ExportConfig.h
# End Source File
# Begin Source File

SOURCE=.\ExportImpl.cpp
# End Source File
# Begin Source File

SOURCE=.\ExportImpl.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Version.mak
# PROP Exclude_From_Scan -1

!IF  "$(CFG)" == "Export - Win32 Release"

# PROP BASE Exclude_From_Build 1
# Begin Custom Build
InputPath=.\Version.mak

BuildCmds= \
	nmake -nologo -f version.mak CFG=NDEBUG

".\Export.ver" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Export.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Export.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Export - Win32 Debug"

# PROP BASE Exclude_From_Build 1
# Begin Custom Build
InputPath=.\Version.mak

BuildCmds= \
	nmake -nologo -f version.mak CFG=_DEBUG

".\Export.ver" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Export.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Export.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Chckmark.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\CoordSys.bmp
# End Source File
# Begin Source File

SOURCE=.\Export.rc
# End Source File
# Begin Source File

SOURCE=.\res\ExportDataOKS.xml
# End Source File
# Begin Source File

SOURCE=.\res\ExportDataORWnd.xml
# End Source File
# Begin Source File

SOURCE=.\ExportPropertyAction.rgs
# End Source File
# Begin Source File

SOURCE=.\ExportXTension.rgs
# End Source File
# Begin Source File

SOURCE=.\ExportXTension0.rgs
# End Source File
# Begin Source File

SOURCE=.\res\GeoComponentSequence.dtd
# End Source File
# Begin Source File

SOURCE=.\res\msg00407.bin
# End Source File
# Begin Source File

SOURCE=.\res\msg00409.bin
# End Source File
# Begin Source File

SOURCE=.\res\ObjPropTypes.bmp
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# End Group
# Begin Group "Generated Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Export.def
# End Source File
# Begin Source File

SOURCE=.\Export.h
# End Source File
# Begin Source File

SOURCE=.\Export.hmc
# End Source File
# Begin Source File

SOURCE=.\Export.rcv
# End Source File
# Begin Source File

SOURCE=.\Export.ver
# End Source File
# End Group
# Begin Group "Help Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\help\Export.d

!IF  "$(CFG)" == "Export - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\help\Export.d
InputName=Export

"$(TRIASINCLUDE)\help\$(InputName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak CFG=NDEBUG

# End Custom Build

!ELSEIF  "$(CFG)" == "Export - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\help\Export.d
InputName=Export

"$(TRIASINCLUDE)\help\$(InputName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak CFG=_DEBUG

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Export.mc

!IF  "$(CFG)" == "Export - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\Export.mc

BuildCmds= \
	nmake -nologo -f version.mak CFG=NDEBUG

".\Export.hmc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\res\msg00407.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\res\msg00409.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Export - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\Export.mc

BuildCmds= \
	nmake -nologo -f version.mak CFG=_DEBUG

".\Export.hmc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
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
# Section Export : {00000000-0000-0000-0000-800000800000}
# 	1:23:IDR_SELECTEXPORTOBJECTS:106
# 	1:35:IDS_DESCRIPTION_SELECTEXPORTOBJECTS:108
# 	1:31:IDD_SELECTEXPORTOBJECTS_OPTIONS:109
# End Section
