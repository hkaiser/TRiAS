# Microsoft Developer Studio Project File - Name="TDBPGIS" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=TDBPGIS - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TDBPGIS.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TDBPGIS.mak" CFG="TDBPGIS - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TDBPGIS - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "TDBPGIS - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=xicl6.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TDBPGIS - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"StdAfx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /Oicf
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386

!ELSEIF  "$(CFG)" == "TDBPGIS - Win32 Debug"

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
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"StdAfx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /Oicf
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /out:"Debug/TDBPGISd.dll"
# SUBTRACT LINK32 /pdbtype:<none>
# Begin Custom Build
TargetDir=.\Debug
TargetPath=.\Debug\TDBPGISd.dll
TargetName=TDBPGISd
InputPath=.\Debug\TDBPGISd.dll
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(TRIASDIR_D) 
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_D) 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "TDBPGIS - Win32 Release"
# Name "TDBPGIS - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Helper Sources"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DBUtil.cpp
# End Source File
# Begin Source File

SOURCE=.\TDBPGISCursorProperty.cpp
# End Source File
# Begin Source File

SOURCE=.\TDBPGISGeometryBlob.cpp
# End Source File
# Begin Source File

SOURCE=.\TDBPGISPropertySupportImpl.cpp
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "TDBPGIS Object Sources"

# PROP Default_Filter ""
# Begin Group "User Interface Sources"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DDXGetFile.cpp
# End Source File
# Begin Source File

SOURCE=.\FindPolyGISWiz.cpp
# End Source File
# Begin Source File

SOURCE=.\FindPolyGISWizPropExt.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\TDBPGISDatabase.cpp
# End Source File
# Begin Source File

SOURCE=.\TDBPGISDBEngine.cpp
# End Source File
# Begin Source File

SOURCE=.\TDBPGISFeature.cpp
# End Source File
# Begin Source File

SOURCE=.\TDBPGISFeatures.cpp
# End Source File
# Begin Source File

SOURCE=.\TDBPGISGeoFeature.cpp
# End Source File
# Begin Source File

SOURCE=.\TDBPGISGeoFeatures.cpp
# End Source File
# Begin Source File

SOURCE=.\TDBPGISObject.cpp
# End Source File
# Begin Source File

SOURCE=.\TDBPGISObjects.cpp
# End Source File
# Begin Source File

SOURCE=.\TDBPGISObjectsCollection.cpp
# End Source File
# End Group
# Begin Group "PolyGIS Wrapper Sources"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\PolyGISDatasource.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\dlldatax.c
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\SampleData.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "TDBPGIS - Win32 Release"

# ADD CPP /MD /Yc"StdAfx.h"

!ELSEIF  "$(CFG)" == "TDBPGIS - Win32 Debug"

# ADD CPP /Zi /Yc"StdAfx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Strings.cpp
# End Source File
# Begin Source File

SOURCE=.\TDBPGIS.cpp
# End Source File
# Begin Source File

SOURCE=.\TDBPGIS.def
# End Source File
# Begin Source File

SOURCE=.\TDBPGIS.idl

!IF  "$(CFG)" == "TDBPGIS - Win32 Release"

# ADD MTL /h "TDBPGIS.h" /iid "TDBPGIS_i.c"

!ELSEIF  "$(CFG)" == "TDBPGIS - Win32 Debug"

# ADD MTL /h "TDBPGIS.h" /iid "TDBPGIS_i.c"

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "Helper Headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DBUtil.h
# End Source File
# Begin Source File

SOURCE=.\TDBPGISCursorProperty.h
# End Source File
# Begin Source File

SOURCE=.\TDBPGISGeometryBlob.h
# End Source File
# Begin Source File

SOURCE=.\TDBPGISPropertyBase.h
# End Source File
# Begin Source File

SOURCE=.\TDBPGISPropertySupport.h
# End Source File
# Begin Source File

SOURCE=.\TDBPGISSmartIFs.h
# End Source File
# End Group
# Begin Group "TDBPGIS Object Headers"

# PROP Default_Filter ""
# Begin Group "User Interface Headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\FindPolyGISWiz.h
# End Source File
# Begin Source File

SOURCE=.\FindPolyGISWizPropExt.h
# End Source File
# Begin Source File

SOURCE=..\TriasDB\OpenWizPropExt.h
# End Source File
# Begin Source File

SOURCE=.\PropSheetExt.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\TDBPGISDatabase.h
# End Source File
# Begin Source File

SOURCE=.\TDBPGISDBEngine.h
# End Source File
# Begin Source File

SOURCE=.\TDBPGISFeature.h
# End Source File
# Begin Source File

SOURCE=.\TDBPGISFeatures.h
# End Source File
# Begin Source File

SOURCE=.\TDBPGISGeoFeature.h
# End Source File
# Begin Source File

SOURCE=.\TDBPGISGeoFeatures.h
# End Source File
# Begin Source File

SOURCE=.\TDBPGISObject.h
# End Source File
# Begin Source File

SOURCE=.\TDBPGISObjects.h
# End Source File
# Begin Source File

SOURCE=.\TDBPGISObjectsCollection.h
# End Source File
# End Group
# Begin Group "PolyGIS Wrapper Headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\PolyGISDatasource.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\CPTDBPGISDBEngineEvents.h
# End Source File
# Begin Source File

SOURCE=.\DDXGetFile.h
# End Source File
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

SOURCE=.\SampleDataTypes.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Strings.h
# End Source File
# Begin Source File

SOURCE=.\TDBPGIS.h
# End Source File
# Begin Source File

SOURCE=.\TDBPGISApp.h
# End Source File
# Begin Source File

SOURCE=.\TDBPGISConfig.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\RES\polygis.ico
# End Source File
# Begin Source File

SOURCE=.\TDBPGIS.rc
# End Source File
# Begin Source File

SOURCE=.\RES\Topkarte.bmp
# End Source File
# End Group
# Begin Group "Versioning"

# PROP Default_Filter "*.mak,*.tpl"
# Begin Source File

SOURCE=.\TDBPGIS.tpl

!IF  "$(CFG)" == "TDBPGIS - Win32 Release"

# PROP Ignore_Default_Tool 1
USERDEP__TDBPG="version.mak"	
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\TDBPGIS.tpl

"TDBPGIS.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak "TDBPGIS.def"

# End Custom Build

!ELSEIF  "$(CFG)" == "TDBPGIS - Win32 Debug"

# PROP Ignore_Default_Tool 1
USERDEP__TDBPG="version.mak"	
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\TDBPGIS.tpl

"TDBPGIS.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak "TDBPGIS.def"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RES\TDBPGISv.tpl

!IF  "$(CFG)" == "TDBPGIS - Win32 Release"

# PROP Ignore_Default_Tool 1
USERDEP__TDBPGI="version.mak"	
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\RES\TDBPGISv.tpl

"Res/TDBPGIS.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak "Res/TDBPGIS.rcv"

# End Custom Build

!ELSEIF  "$(CFG)" == "TDBPGIS - Win32 Debug"

# PROP Ignore_Default_Tool 1
USERDEP__TDBPGI="version.mak"	
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\RES\TDBPGISv.tpl

"Res/TDBPGIS.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak "Res/TDBPGIS.rcv"

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

!IF  "$(CFG)" == "TDBPGIS - Win32 Release"

# PROP Ignore_Default_Tool 1
USERDEP__VERSI="version.mak"	
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\Version.tpl

"Version.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak Version.h

# End Custom Build

!ELSEIF  "$(CFG)" == "TDBPGIS - Win32 Debug"

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

SOURCE=.\RES\FindPolyGISWizPropExt.rgs
# End Source File
# Begin Source File

SOURCE=.\RES\TDBPGISCursorProperty.rgs
# End Source File
# Begin Source File

SOURCE=.\RES\TDBPGISDatabase.rgs
# End Source File
# Begin Source File

SOURCE=.\RES\TDBPGISDBEngine.rgs
# End Source File
# Begin Source File

SOURCE=.\RES\TDBPGISFeature.rgs
# End Source File
# Begin Source File

SOURCE=.\RES\TDBPGISFeatures.rgs
# End Source File
# Begin Source File

SOURCE=.\RES\TDBPGISGeoFeature.rgs
# End Source File
# Begin Source File

SOURCE=.\RES\TDBPGISGeoFeatures.rgs
# End Source File
# Begin Source File

SOURCE=.\RES\TDBPGISObject.rgs
# End Source File
# Begin Source File

SOURCE=.\RES\TDBPGISObjects.rgs
# End Source File
# Begin Source File

SOURCE=.\RES\TDBPGISObjectsCollection.rgs
# End Source File
# End Group
# End Target
# End Project
