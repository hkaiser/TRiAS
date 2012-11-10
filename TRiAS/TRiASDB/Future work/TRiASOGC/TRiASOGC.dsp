# Microsoft Developer Studio Project File - Name="TRiASOGC" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=TRiASOGC - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TRiASOGC.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TRiASOGC.mak" CFG="TRiASOGC - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TRiASOGC - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "TRiASOGC - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=xicl6.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TRiASOGC - Win32 Release"

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
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /YX /FD /c
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /YX /Fd"Release/TRiASOGC.pdb" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /Oicf /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# Begin Custom Build
OutDir=.\Release
TargetPath=.\Release\TRiASOGC.dll
TargetName=TRiASOGC
InputPath=.\Release\TRiASOGC.dll
SOURCE="$(InputPath)"

"$(TRIASDIR_R)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(TRIASDIR_R) 
	xcopy /F "$(OutDir)\$(TargetName).pdb" $(TRIASDIR_R) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASOGC - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"StdAfx.h" /Fd"Debug/TRiASOGCd.pdb" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /Oicf /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /out:"Debug/TRiASOGCd.dll"
# Begin Custom Build
OutDir=.\Debug
TargetPath=.\Debug\TRiASOGCd.dll
TargetName=TRiASOGCd
InputPath=.\Debug\TRiASOGCd.dll
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(TRIASDIR_D) 
	xcopy /F "$(OutDir)\$(TargetName).pdb" $(TRIASDIR_D) 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "TRiASOGC - Win32 Release"
# Name "TRiASOGC - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Helper Sources"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=.\DBUtil.cpp
# End Source File
# Begin Source File

SOURCE=.\dlldatax.c
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\TRiASOGCCursorProperty.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASOGCGeometryBlob.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASOGCPropertySupportImpl.cpp
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "TRiASOGC Object Sources"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=.\TRiASOGCDatabase.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASOGCDBEngine.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASOGCFeature.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASOGCFeatures.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASOGCGeoFeature.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASOGCGeoFeatures.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASOGCObject.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASOGCObjects.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASOGCObjectsCollection.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\SampleData.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "TRiASOGC - Win32 Release"

!ELSEIF  "$(CFG)" == "TRiASOGC - Win32 Debug"

# ADD CPP /Yc"StdAfx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Strings.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASOGC.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASOGC.def
# End Source File
# Begin Source File

SOURCE=.\TRiASOGC.idl
# ADD MTL /h "TRiASOGC.h" /iid "TRiASOGC_i.c"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "Helper Headers"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=.\CPTRiASOGCDBEngineEvents.h
# End Source File
# Begin Source File

SOURCE=.\DBUtil.h
# End Source File
# Begin Source File

SOURCE=.\OGISDataProviderEnum.h
# End Source File
# Begin Source File

SOURCE=.\TRiASOGCCursorProperty.h
# End Source File
# Begin Source File

SOURCE=.\TRiASOGCGeometryBlob.h
# End Source File
# Begin Source File

SOURCE=.\TRiASOGCPropertyBase.h
# End Source File
# Begin Source File

SOURCE=.\TRiASOGCPropertySupport.h
# End Source File
# Begin Source File

SOURCE=.\TRiASOGCSmartIFs.h
# End Source File
# End Group
# Begin Group "TRiASOGC Object Headers"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=.\TRiASOGCDatabase.h
# End Source File
# Begin Source File

SOURCE=.\TRiASOGCDBEngine.h
# End Source File
# Begin Source File

SOURCE=.\TRiASOGCFeature.h
# End Source File
# Begin Source File

SOURCE=.\TRiASOGCFeatures.h
# End Source File
# Begin Source File

SOURCE=.\TRiASOGCGeoFeature.h
# End Source File
# Begin Source File

SOURCE=.\TRiASOGCGeoFeatures.h
# End Source File
# Begin Source File

SOURCE=.\TRiASOGCObject.h
# End Source File
# Begin Source File

SOURCE=.\TRiASOGCObjects.h
# End Source File
# Begin Source File

SOURCE=.\TRiASOGCObjectsCollection.h
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

SOURCE=.\SampleDataTypes.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Strings.h
# End Source File
# Begin Source File

SOURCE=.\TRiASOGC.h
# End Source File
# Begin Source File

SOURCE=.\TRiASOGCApp.h
# End Source File
# Begin Source File

SOURCE=.\TRiASOGCConfig.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\TRiASOGC.rc
# End Source File
# End Group
# Begin Group "Versioning"

# PROP Default_Filter "*.mak,*.tpl"
# Begin Source File

SOURCE=.\TRiASOGC.tpl

!IF  "$(CFG)" == "TRiASOGC - Win32 Release"

# PROP Ignore_Default_Tool 1
USERDEP__TRIAS="version.mak"	
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\TRiASOGC.tpl

"TRiASOGC.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak "TRiASOGC.def"

# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASOGC - Win32 Debug"

# PROP Ignore_Default_Tool 1
USERDEP__TRIAS="version.mak"	
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\TRiASOGC.tpl

"TRiASOGC.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak "TRiASOGC.def"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RES\TRiASOGCv.tpl

!IF  "$(CFG)" == "TRiASOGC - Win32 Release"

# PROP Ignore_Default_Tool 1
USERDEP__TRIASO="version.mak"	
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\RES\TRiASOGCv.tpl

"Res/TRiASOGC.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak "Res/TRiASOGC.rcv"

# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASOGC - Win32 Debug"

# PROP Ignore_Default_Tool 1
USERDEP__TRIASO="version.mak"	
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\RES\TRiASOGCv.tpl

"Res/TRiASOGC.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak "Res/TRiASOGC.rcv"

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

!IF  "$(CFG)" == "TRiASOGC - Win32 Release"

# PROP Ignore_Default_Tool 1
USERDEP__VERSI="version.mak"	
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\Version.tpl

"Version.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak Version.h

# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASOGC - Win32 Debug"

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

SOURCE=.\RES\FakeTRiASDBServer.rgs
# End Source File
# Begin Source File

SOURCE=.\RES\TRiASOGCCursorProperty.rgs
# End Source File
# Begin Source File

SOURCE=.\RES\TRiASOGCDatabase.rgs
# End Source File
# Begin Source File

SOURCE=.\RES\TRiASOGCDBEngine.rgs
# End Source File
# Begin Source File

SOURCE=.\RES\TRiASOGCFeature.rgs
# End Source File
# Begin Source File

SOURCE=.\RES\TRiASOGCFeatures.rgs
# End Source File
# Begin Source File

SOURCE=.\RES\TRiASOGCGeoFeature.rgs
# End Source File
# Begin Source File

SOURCE=.\RES\TRiASOGCGeoFeatures.rgs
# End Source File
# Begin Source File

SOURCE=.\RES\TRiASOGCObject.rgs
# End Source File
# Begin Source File

SOURCE=.\RES\TRiASOGCObjects.rgs
# End Source File
# Begin Source File

SOURCE=.\RES\TRiASOGCObjectsCollection.rgs
# End Source File
# End Group
# End Target
# End Project
