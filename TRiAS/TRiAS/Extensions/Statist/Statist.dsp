# Microsoft Developer Studio Project File - Name="Statist" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=Statist - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Statist.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Statist.mak" CFG="Statist - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Statist - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Statist - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Statist - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /Oicf /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 shlwapi.lib containr.lib delayimp.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"Release/Statist.ext" /delayload:ole32.dll /delayload:oleaut32.dll /delayload:comctl32.dll /delayload:advapi32.dll /delayload:shlwapi.dll
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build
OutDir=.\Release
TargetPath=.\Release\Statist.ext
TargetName=Statist
InputPath=.\Release\Statist.ext
SOURCE="$(InputPath)"

"$(TRIASDIR_R)\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(TargetPath) $(TRIASDIR_R) 
	xcopy /F $(OutDir)\$(TargetName).pdb $(TRIASDIR_R) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Statist - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /Oicf /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 shlwapi.lib cont50d.lib delayimp.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"Debug/Statistd.ext" /pdbtype:sept /delayload:ole32.dll /delayload:oleaut32.dll /delayload:comctl32.dll /delayload:advapi32.dll /delayload:shlwapi.dll
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build
OutDir=.\Debug
TargetPath=.\Debug\Statistd.ext
TargetName=Statistd
InputPath=.\Debug\Statistd.ext
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(TargetPath) $(TRIASDIR_D) 
	xcopy /F $(OutDir)\$(TargetName).pdb $(TRIASDIR_D) 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "Statist - Win32 Release"
# Name "Statist - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Maßeinheiten Sources"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=.\TRiASUnitIDs.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASUnitsOfMeasure.cpp
# End Source File
# Begin Source File

SOURCE=.\UnitsOfMeasureDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\UnitsOfMeasurePP.cpp
# End Source File
# End Group
# Begin Group "Xtension Sources"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=.\ConnectedCtf.cpp
# End Source File
# Begin Source File

SOURCE=.\GeoObj.cpp
# End Source File
# Begin Source File

SOURCE=.\HandleToolbar.cpp
# End Source File
# Begin Source File

SOURCE=.\Separator.cpp
# End Source File
# Begin Source File

SOURCE=.\StatFuncName.cpp
# End Source File
# Begin Source File

SOURCE=.\Statist.cpp
# End Source File
# Begin Source File

SOURCE=.\StatistApp.cpp
# End Source File
# Begin Source File

SOURCE=.\StatistUIOwner.cpp
# End Source File
# Begin Source File

SOURCE=.\StatistUtil.cpp
# End Source File
# End Group
# Begin Group "Interface definitions"

# PROP Default_Filter "*.idl"
# Begin Source File

SOURCE=..\..\Include\Idl\Collection.idl
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\Include\Idl\ConfigObjectProperty.Idl
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\StatistApp.idl
# End Source File
# Begin Source File

SOURCE=..\..\Include\Idl\ValueProvider.idl
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "Object Property Sources"

# PROP Default_Filter "*.cpp"
# Begin Group "Object Property UI Sources"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=.\MathOperationPropertyDlg.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\CountAreaIsland.cpp
# End Source File
# Begin Source File

SOURCE=.\CountLinePoints.cpp
# End Source File
# Begin Source File

SOURCE=.\FullAreaFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\LengthOfLine.cpp
# End Source File
# Begin Source File

SOURCE=.\MathOperationProperty.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjektContainer.cpp
# End Source File
# Begin Source File

SOURCE=.\PointCentreCoord.cpp
# End Source File
# Begin Source File

SOURCE=.\PointRefCoord.cpp
# End Source File
# Begin Source File

SOURCE=.\SimpleAreaFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\SimpleAreaRadius.cpp
# End Source File
# Begin Source File

SOURCE=.\SuperficialContents.cpp
# End Source File
# End Group
# Begin Group "Property Action Sources"

# PROP Default_Filter "*.cpp"
# Begin Group "User Interface Sources"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=.\MeshGenerationDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SelectStatistValueDlg.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ConvexHull.cpp
# End Source File
# Begin Source File

SOURCE=.\MeshGeneration.cpp
# End Source File
# Begin Source File

SOURCE=.\SelectStatistValue.cpp
# End Source File
# Begin Source File

SOURCE=.\StatisticObjectProperty.cpp
# End Source File
# End Group
# Begin Group "Controls Sources"

# PROP Default_Filter "*.cpp"
# Begin Group "Property Tree Sources"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ObjPropTree.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjPropTreeCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\StatFuncTreeCtrl.cpp
# End Source File
# End Group
# Begin Group "Value Container Sources"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ObjectClassStatistics.cpp
# End Source File
# Begin Source File

SOURCE=.\ORWndStatistics.cpp
# End Source File
# Begin Source File

SOURCE=.\ORWndValuePageCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\ProjectValuePageCtrl.cpp
# End Source File
# End Group
# End Group
# Begin Group "Value Provider Sources"

# PROP Default_Filter "*.cpp"
# Begin Group "Datasource Provider Sources"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ObjectCountInClass.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjectCountInDatasource.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjectCountProviderCallback.cpp
# End Source File
# End Group
# Begin Group "ORWnd Provider Sources"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ObjectCountInORWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjectCountInORWndClass.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjectCountORWndProviderCallback.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\StatistValueImpl.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\StatistValues.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASSimpleStatistics.cpp
# End Source File
# End Group
# Begin Group "Project Value Explorer Sources"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=.\Categories.cpp
# End Source File
# Begin Source File

SOURCE=.\ProjectValuesCallback.cpp
# End Source File
# Begin Source File

SOURCE=.\ProjectValueWindowImpl.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\Statist.def
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Strings.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "Maßeinheiten Header"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=.\PropPageExt.h
# End Source File
# Begin Source File

SOURCE=.\TRiASUnitIDs.h
# End Source File
# Begin Source File

SOURCE=.\TRiASUnitsOfMeasure.h
# End Source File
# Begin Source File

SOURCE=.\UnitsOfMeasureDlg.h
# End Source File
# Begin Source File

SOURCE=.\UnitsOfMeasurePP.h
# End Source File
# End Group
# Begin Group "Xtension Header"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=.\ConnectedCtf.h
# End Source File
# Begin Source File

SOURCE=.\GeoObj.h
# End Source File
# Begin Source File

SOURCE=.\Separator.h
# End Source File
# Begin Source File

SOURCE=.\StatFuncName.h
# End Source File
# Begin Source File

SOURCE=.\Statist.h
# End Source File
# Begin Source File

SOURCE=.\StatistUIOwner.h
# End Source File
# End Group
# Begin Group "Object Property Header"

# PROP Default_Filter "*.h"
# Begin Group "Object Property UI Header"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=.\MathOperationPropertyDlg.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\CountAreaIsland.h
# End Source File
# Begin Source File

SOURCE=.\CountLinePoints.h
# End Source File
# Begin Source File

SOURCE=.\FullAreaFrame.h
# End Source File
# Begin Source File

SOURCE=.\LengthOfLine.h
# End Source File
# Begin Source File

SOURCE=.\MathOperationProperty.h
# End Source File
# Begin Source File

SOURCE=.\ObjektContainer.h
# End Source File
# Begin Source File

SOURCE=.\PointCentreCoord.h
# End Source File
# Begin Source File

SOURCE=.\PointRefCoord.h
# End Source File
# Begin Source File

SOURCE=.\SimpleAreaFrame.h
# End Source File
# Begin Source File

SOURCE=.\SimpleAreaRadius.h
# End Source File
# Begin Source File

SOURCE=.\SuperficialContents.h
# End Source File
# End Group
# Begin Group "Property Action Header"

# PROP Default_Filter "*.h"
# Begin Group "User Interface Header"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=.\MeshGenerationDlg.h
# End Source File
# Begin Source File

SOURCE=.\SelectStatistValueDlg.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ConvexHull.h
# End Source File
# Begin Source File

SOURCE=.\MeshGeneration.h
# End Source File
# Begin Source File

SOURCE=.\SelectStatistValue.h
# End Source File
# Begin Source File

SOURCE=.\StatisticObjectProperty.h
# End Source File
# End Group
# Begin Group "Controls Header"

# PROP Default_Filter "*.h"
# Begin Group "Property Tree Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ObjPropTree.h
# End Source File
# Begin Source File

SOURCE=.\ObjPropTreeCtrl.h
# End Source File
# Begin Source File

SOURCE=.\ObjPropTreeDlg.h
# End Source File
# Begin Source File

SOURCE=.\PopupTreeDlg.h
# End Source File
# Begin Source File

SOURCE=.\PopupTreeEventCP.h
# End Source File
# Begin Source File

SOURCE=.\StatFuncTreeCtrl.h
# End Source File
# Begin Source File

SOURCE=.\StatFuncTreeDlg.h
# End Source File
# End Group
# Begin Group "Value Container Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\HourglassFX.h
# End Source File
# Begin Source File

SOURCE=.\ObjectClassStatistics.h
# End Source File
# Begin Source File

SOURCE=.\ORWndStatistics.h
# End Source File
# Begin Source File

SOURCE=.\ORWndValuePageCtrl.h
# End Source File
# Begin Source File

SOURCE=.\ProgressFX.h
# End Source File
# Begin Source File

SOURCE=.\ProjectValuePageCtrl.h
# End Source File
# Begin Source File

SOURCE=.\ProjectValuesView.h
# End Source File
# Begin Source File

SOURCE=.\TreeListView.h
# End Source File
# Begin Source File

SOURCE=.\WaitingTreeCtrl.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\StatisticsImageIds.h
# End Source File
# End Group
# Begin Group "Value Provider Header"

# PROP Default_Filter "*.h"
# Begin Group "Datasource Provider Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\InstallObjectCountProvider.h
# End Source File
# Begin Source File

SOURCE=.\ObjectCountInClass.h
# End Source File
# Begin Source File

SOURCE=.\ObjectCountInDatasource.h
# End Source File
# Begin Source File

SOURCE=.\ObjectCountProviderCallback.h
# End Source File
# End Group
# Begin Group "ORWnd Provider Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\InstallObjectCountInORWndProvider.h
# End Source File
# Begin Source File

SOURCE=.\ObjectCountInORWnd.h
# End Source File
# Begin Source File

SOURCE=.\ObjectCountInORWndClass.h
# End Source File
# Begin Source File

SOURCE=.\ObjectCountORWndProviderCallback.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\StatistValue.h
# End Source File
# Begin Source File

SOURCE=.\TRiASSimpleStatistics.h
# End Source File
# End Group
# Begin Group "Project Value Explorer Headers"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=.\Categories.h
# End Source File
# Begin Source File

SOURCE=.\DialogView.h
# End Source File
# Begin Source File

SOURCE=.\ProjectValuesCallback.h
# End Source File
# Begin Source File

SOURCE=.\ProjectValueWindowImpl.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\SmartIFs.h
# End Source File
# Begin Source File

SOURCE=.\StatistConfig.h
# End Source File
# Begin Source File

SOURCE=.\StatistConfigVersion.h
# End Source File
# Begin Source File

SOURCE=.\StatistUtil.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Strings.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Res\Arrow.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Chckmark.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\Res\cursor2.cur
# End Source File
# Begin Source File

SOURCE=.\Res\CustomizeObjProp.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Delaunay.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\down.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\downdis.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\downfoc.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\downsel.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\hourglass.ani
# End Source File
# Begin Source File

SOURCE=.\Res\hourglass.ico
# End Source File
# Begin Source File

SOURCE=".\Res\Hülle.bmp"
# End Source File
# Begin Source File

SOURCE=.\Res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\Res\ObjPropTypes.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\orwndval.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\projectv.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\StatFuncs.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\statist.ico
# End Source File
# Begin Source File

SOURCE=.\Statist.rc
# End Source File
# Begin Source File

SOURCE=.\Res\Statistics.ico
# End Source File
# Begin Source File

SOURCE=.\Res\StatValues.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\StatValuesMask.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\toolbar1.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Voronoi.bmp
# End Source File
# End Group
# Begin Group "Versioning"

# PROP Default_Filter "*.tpl;*.mak"
# Begin Source File

SOURCE=.\Statist.tpl

!IF  "$(CFG)" == "Statist - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\Statist.tpl

"Statist.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak Statist.def

# End Custom Build

!ELSEIF  "$(CFG)" == "Statist - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\Statist.tpl

"Statist.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak Statist.def

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Statistv.tpl

!IF  "$(CFG)" == "Statist - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\Statistv.tpl

"Statist.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak Statist.rcv

# End Custom Build

!ELSEIF  "$(CFG)" == "Statist - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\Statistv.tpl

"Statist.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak Statist.rcv

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

!IF  "$(CFG)" == "Statist - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\Version.tpl

"Version.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak Version.h

# End Custom Build

!ELSEIF  "$(CFG)" == "Statist - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\Version.tpl

"Version.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak Version.h

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Message Strings"

# PROP Default_Filter "*.mc"
# Begin Source File

SOURCE=.\Statist.hmc
# End Source File
# Begin Source File

SOURCE=.\Statist.mc

!IF  "$(CFG)" == "Statist - Win32 Release"

# Begin Custom Build
InputPath=.\Statist.mc

".\Res\Msg00407.Bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	m4 -I%TRIASINCLUDE%\help Statist.mc > Statist.i 
	cl -nologo -EP -C .\Statist.i > .\Statist.ii 
	mc -e hmc -r "res" ".\Statist.ii" 
	del .\Statist.i > nul 
	del .\Statist.ii > nul 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Statist - Win32 Debug"

# Begin Custom Build
InputPath=.\Statist.mc

".\Res\Msg00407.Bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	m4 -I%TRIASINCLUDE%\help Statist.mc > Statist.i 
	cl -nologo -EP -C .\Statist.i > .\Statist.ii 
	mc -e hmc -r "res" ".\Statist.ii" 
	del .\Statist.i > nul 
	del .\Statist.ii > nul 
	
# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Documentation"

# PROP Default_Filter "*.doc"
# Begin Source File

SOURCE=.\Help\CONTENTS.D

!IF  "$(CFG)" == "Statist - Win32 Release"

USERDEP__CONTE="version.mak"	
# Begin Custom Build
InputPath=.\Help\CONTENTS.D

".\Help\Statist.hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	autoduck /L .\help\contents.log /s .\help\Statist.Fmt /rh /t4 /o                                           .\help\contents.rtf  .\help\contents.d .\help\dbmsg.d *.h *.cpp  *.idl $(TRIASINCLUDE)\idl\Collection.idl 
	hcrtf /a /o .\help\Statist.hlp /xn .\help\contents.hpj 
	xcopy /F .\help\Statist.hlp $(TRIASINCLUDE)\help 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Statist - Win32 Debug"

USERDEP__CONTE="version.mak"	
# Begin Custom Build
InputPath=.\Help\CONTENTS.D

".\Help\Statist.hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	autoduck /L .\help\contents.log /s .\help\Statist.Fmt /rh /t4 /o  .\help\contents.rtf  .\help\contents.d statist.hmc *.h *.cpp  *.idl  $(TRIASINCLUDE)\idl\collection.idl 
	hcrtf /a /o .\help\Statist.hlp /xn .\help\contents.hpj 
	xcopy /F .\help\Statist.hlp $(TRIASINCLUDE)\help 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Help\CONTENTS.TPL

!IF  "$(CFG)" == "Statist - Win32 Release"

USERDEP__CONTEN="version.mak"	
# Begin Custom Build
InputPath=.\Help\CONTENTS.TPL

".\help\Contents.hpj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak .\help\Contents.hpj

# End Custom Build

!ELSEIF  "$(CFG)" == "Statist - Win32 Debug"

USERDEP__CONTEN="version.mak"	
# Begin Custom Build
InputPath=.\Help\CONTENTS.TPL

".\help\Contents.hpj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak .\help\Contents.hpj

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\Help\Statist (FDS).doc"
# End Source File
# Begin Source File

SOURCE=.\Help\STATIST.HLP
# End Source File
# Begin Source File

SOURCE=.\Help\StatistFmt.tpl

!IF  "$(CFG)" == "Statist - Win32 Release"

USERDEP__STATI="version.mak"	
# Begin Custom Build
InputPath=.\Help\StatistFmt.tpl

".\Help\Statist.fmt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak .\Help\Statist.fmt

# End Custom Build

!ELSEIF  "$(CFG)" == "Statist - Win32 Debug"

USERDEP__STATI="version.mak"	
# Begin Custom Build
InputPath=.\Help\StatistFmt.tpl

".\Help\Statist.fmt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak .\Help\Statist.fmt

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Registry Scripts"

# PROP Default_Filter "*.rgs"
# Begin Source File

SOURCE=.\MeshGeneration.rgs
# End Source File
# Begin Source File

SOURCE=.\ObjectCountInClass.rgs
# End Source File
# Begin Source File

SOURCE=.\ObjectCountInDatasource.rgs
# End Source File
# Begin Source File

SOURCE=.\ObjectCountInORWnd.rgs
# End Source File
# Begin Source File

SOURCE=.\ObjectCountInORWndClass.rgs
# End Source File
# Begin Source File

SOURCE=.\ObjPropTree.rgs
# End Source File
# Begin Source File

SOURCE=.\ORWndValuePageCtrl.rgs
# End Source File
# Begin Source File

SOURCE=.\ProjectValuePageCtrl.rgs
# End Source File
# Begin Source File

SOURCE=.\SelectStatistValue.rgs
# End Source File
# Begin Source File

SOURCE=.\SimpleStatistics.rgs
# End Source File
# Begin Source File

SOURCE=.\StatisticObjectProperty.rgs
# End Source File
# Begin Source File

SOURCE=.\StatistValue.rgs
# End Source File
# Begin Source File

SOURCE=.\UnitsOfMeasure.rgs
# End Source File
# Begin Source File

SOURCE=.\UnitsOfMeasurePP.rgs
# End Source File
# End Group
# End Target
# End Project
# Section Statist : {554C4156-5345-2820-4469-616C6F672900}
# 	1:24:IDR_PROJECTVALUEPAGECTRL:140
# 	1:24:IDB_PROJECTVALUEPAGECTRL:139
# 	1:24:IDD_PROJECTVALUEPAGECTRL:141
# End Section
# Section Statist : {00000000-0000-0000-0000-800000800000}
# 	1:34:IDS_DESCRIPTION_SELECTSTATISTVALUE:110
# 	1:30:IDD_SELECTSTATISTVALUE_OPTIONS:111
# 	1:22:IDR_SELECTSTATISTVALUE:109
# End Section
