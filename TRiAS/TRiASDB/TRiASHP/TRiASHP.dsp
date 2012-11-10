# Microsoft Developer Studio Project File - Name="TRiASHP" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=TRIASHP - WIN32 RELEASE
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TRiASHP.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TRiASHP.mak" CFG="TRIASHP - WIN32 RELEASE"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TRiASHP - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "TRiASHP - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Tools/AscBna", KUJBAAAA"
# PROP Scc_LocalPath "..\..\triasdev\ascbna"
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TRiASHP - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /Zi /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /Oicf /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ospace5r.lib Shapelib.lib lol.lib delayimp.lib /nologo /subsystem:windows /dll /debug /machine:I386 /def:"TRiASHP.def" /delayload:crp32dll.dll /delayload:ole32.dll /delayload:oleaut32.dll
# Begin Custom Build
TargetDir=.\Release
TargetPath=.\Release\TRiASHP.dll
TargetName=TRiASHP
InputPath=.\Release\TRiASHP.dll
SOURCE="$(InputPath)"

"$(TRIASDIR_R)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(TargetPath) $(TRIASDIR_R) 
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_R) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASHP - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /Fd"Debug/TRiASHPD.pdb" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /Oicf /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 OSpace5d.lib Shapelibd.lib lol50d.lib delayimp.lib /nologo /subsystem:windows /dll /debug /machine:I386 /def:"TRiASHP.def" /out:"Debug/TRiASHPD.dll" /pdbtype:sept /delayload:crp32dll.dll /delayload:ole32.dll /delayload:oleaut32.dll
# Begin Custom Build
TargetDir=.\Debug
TargetPath=.\Debug\TRiASHPD.dll
TargetName=TRiASHPD
InputPath=.\Debug\TRiASHPD.dll
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(TargetPath) $(TRIASDIR_D) 
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_D) 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "TRiASHP - Win32 Release"
# Name "TRiASHP - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Helper Sources"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=.\DBUtil.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASHPCursorProperty.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASHPGeometryBlob.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASHPPropertySupportImpl.cpp
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "TRiASHP Object Sources"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=.\TRiASHPDatabase.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASHPDBEngine.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASHPFeature.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASHPFeatures.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASHPGeoFeature.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASHPGeoFeatures.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASHPObject.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASHPObjects.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASHPObjectsCollection.cpp
# End Source File
# End Group
# Begin Group "Shape Wrapper Sources"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=.\Shape\ogrshape.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Shape\ogrshapedatasource.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Shape\ogrshapedriver.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Shape\ogrshapelayer.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Shape\shape2ogr.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\ShapeDataSource.cpp
# End Source File
# Begin Source File

SOURCE=.\ShapeGeometryTree.cpp
# End Source File
# Begin Source File

SOURCE=.\ShapeLayer.cpp
# End Source File
# End Group
# Begin Group "EsriCfg Sources"

# PROP Default_Filter "*.cpp;*.yxx"
# Begin Source File

SOURCE=.\EsriCfg.yxx

!IF  "$(CFG)" == "TRiASHP - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TRiASHP - Win32 Debug"

# Begin Custom Build
InputPath=.\EsriCfg.yxx

BuildCmds= \
	yxx -mph -debug -no_stats -table readable EsriCfg.yxx \
	sed -e s/yy_export//g esricfgy.h > tmp \
	del esricfgy.h \
	ren tmp esricfgy.h \
	sed -e s/yy_export//g esricfgl.h > tmp \
	del esricfgl.h \
	ren tmp esricfgl.h \
	sed -e s/yy_export//g yy_myref.h > tmp \
	del yy_myref.h \
	ren tmp yy_myref.h \
	

"esricfgy.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"esricfgy.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"esricfgl.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"esricfgl.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"yy_myref.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ESRICFGL.CPP

!IF  "$(CFG)" == "TRiASHP - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TRiASHP - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\esricfgm.cpp

!IF  "$(CFG)" == "TRiASHP - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TRiASHP - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\esricfgmain.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\ESRICFGY.CPP

!IF  "$(CFG)" == "TRiASHP - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TRiASHP - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\NodeRef.cpp

!IF  "$(CFG)" == "TRiASHP - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TRiASHP - Win32 Debug"

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE=.\dlldatax.c
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Strings.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASHP.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASHP.idl

!IF  "$(CFG)" == "TRiASHP - Win32 Release"

!ELSEIF  "$(CFG)" == "TRiASHP - Win32 Debug"

# ADD MTL /h "TRiASHP.h" /iid "TRiASHP_i.c"

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "Helper Headers"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=.\DBUtil.h
# End Source File
# Begin Source File

SOURCE=.\TRiASHPCursorProperty.h
# End Source File
# Begin Source File

SOURCE=.\TRiASHPGeometryBlob.h
# End Source File
# Begin Source File

SOURCE=.\TRiASHPPropertyBase.h
# End Source File
# Begin Source File

SOURCE=.\TRiASHPPropertySupport.h
# End Source File
# End Group
# Begin Group "TRiASHP Object Headers"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=.\TRiASHPDatabase.h
# End Source File
# Begin Source File

SOURCE=.\TRiASHPDBEngine.h
# End Source File
# Begin Source File

SOURCE=.\TRiASHPFeature.h
# End Source File
# Begin Source File

SOURCE=.\TRiASHPFeatures.h
# End Source File
# Begin Source File

SOURCE=.\TRiASHPGeoFeature.h
# End Source File
# Begin Source File

SOURCE=.\TRiASHPGeoFeatures.h
# End Source File
# Begin Source File

SOURCE=.\TRiASHPObject.h
# End Source File
# Begin Source File

SOURCE=.\TRiASHPObjects.h
# End Source File
# Begin Source File

SOURCE=.\TRiASHPObjectsCollection.h
# End Source File
# End Group
# Begin Group "Shape Wrapper Headers"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=.\Shape\ogrshape.h

!IF  "$(CFG)" == "TRiASHP - Win32 Release"

!ELSEIF  "$(CFG)" == "TRiASHP - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ShapeDataSource.h
# End Source File
# Begin Source File

SOURCE=.\ShapeGeometryTree.h
# End Source File
# Begin Source File

SOURCE=.\ShapeLayer.h
# End Source File
# End Group
# Begin Group "EsriCfg Headers"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=.\ESRICFGL.H
# End Source File
# Begin Source File

SOURCE=.\EsriCfgm.h
# End Source File
# Begin Source File

SOURCE=.\ESRICFGY.H
# End Source File
# Begin Source File

SOURCE=.\NodeRef.h
# End Source File
# Begin Source File

SOURCE=.\YY_MYREF.H
# End Source File
# End Group
# Begin Source File

SOURCE=.\dlldatax.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Strings.h
# End Source File
# Begin Source File

SOURCE=.\TRiASHP.h
# End Source File
# Begin Source File

SOURCE=.\TRiASHPApp.h
# End Source File
# Begin Source File

SOURCE=.\TRiASHPConfig.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Debug\MSG00407.bin
# End Source File
# Begin Source File

SOURCE=.\Release\MSG00407.bin
# End Source File
# Begin Source File

SOURCE=.\TRiASHP.rc
# End Source File
# End Group
# Begin Group "Versioning"

# PROP Default_Filter "*.tpl"
# Begin Source File

SOURCE=.\TRiASHP.tpl

!IF  "$(CFG)" == "TRiASHP - Win32 Release"

# PROP Ignore_Default_Tool 1
USERDEP__TRIAS="version.mak"	
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\TRiASHP.tpl

"TRiASHP.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak "TRiASHP.def"

# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASHP - Win32 Debug"

# PROP Ignore_Default_Tool 1
USERDEP__TRIAS="version.mak"	
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\TRiASHP.tpl

"TRiASHP.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak "TRiASHP.def"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RES\TRiASHPv.tpl

!IF  "$(CFG)" == "TRiASHP - Win32 Release"

# PROP Ignore_Default_Tool 1
USERDEP__TRIASH="version.mak"	
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\RES\TRiASHPv.tpl

"Res/TRiASHP.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak "Res/TRiASHP.rcv"

# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASHP - Win32 Debug"

# PROP Ignore_Default_Tool 1
USERDEP__TRIASH="version.mak"	
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\RES\TRiASHPv.tpl

"Res/TRiASHP.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak "Res/TRiASHP.rcv"

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

!IF  "$(CFG)" == "TRiASHP - Win32 Release"

# PROP Ignore_Default_Tool 1
USERDEP__VERSI="version.mak"	
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\Version.tpl

"Version.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak Version.h

# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASHP - Win32 Debug"

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
# Begin Group "Registry Scripts"

# PROP Default_Filter "*.rgs"
# Begin Source File

SOURCE=.\RES\TRiASHPCursorProperty.rgs
# End Source File
# Begin Source File

SOURCE=.\RES\TRiASHPDatabase.rgs
# End Source File
# Begin Source File

SOURCE=.\RES\TRiASHPDBEngine.rgs
# End Source File
# Begin Source File

SOURCE=.\RES\TRiASHPFeature.rgs
# End Source File
# Begin Source File

SOURCE=.\RES\TRiASHPFeatures.rgs
# End Source File
# Begin Source File

SOURCE=.\RES\TRiASHPGeoFeature.rgs
# End Source File
# Begin Source File

SOURCE=.\RES\TRiASHPGeoFeatures.rgs
# End Source File
# Begin Source File

SOURCE=.\RES\TRiASHPObject.rgs
# End Source File
# Begin Source File

SOURCE=.\RES\TRiASHPObjects.rgs
# End Source File
# Begin Source File

SOURCE=.\RES\TRiASHPObjectsCollection.rgs
# End Source File
# End Group
# Begin Group "MessageStrings"

# PROP Default_Filter "*.mc"
# Begin Source File

SOURCE=.\TRiASHP.mc

!IF  "$(CFG)" == "TRiASHP - Win32 Release"

# Begin Custom Build
InputDir=.
OutDir=.\Release
InputPath=.\TRiASHP.mc
InputName=TRiASHP

BuildCmds= \
	cl -nologo -TC -C -EP -D_DEBUG -u $(InputPath) > $(OutDir)\$(InputName).i \
	mc -e hmc -h $(InputDir) -r "$(OutDir)" "$(OutDir)\$(InputName).i " \
	mc2const -h .\Help  $(OutDir)\$(InputName).i \
	del "$(OutDir)\$(InputName).i" > nul \
	

"$(OutDir)\Msg00407.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"TRiASHP.hmc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASHP - Win32 Debug"

# Begin Custom Build
InputDir=.
OutDir=.\Debug
InputPath=.\TRiASHP.mc
InputName=TRiASHP

BuildCmds= \
	cl -nologo -TC -C -EP -D_DEBUG -u $(InputPath) > $(OutDir)\$(InputName).i \
	mc -e hmc -h $(InputDir) -r "$(OutDir)" "$(OutDir)\$(InputName).i " \
	mc2const -h .\Help  $(OutDir)\$(InputName).i \
	del "$(OutDir)\$(InputName).i" > nul \
	

"$(OutDir)\Msg00407.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"TRiASHP.hmc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
