# Microsoft Developer Studio Project File - Name="TRiASMI" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=TRiASMI - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TRiASMI.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TRiASMI.mak" CFG="TRiASMI - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TRiASMI - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "TRiASMI - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/TRiAS/TRiASDB/TRiASMI", OPGBAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TRiASMI - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /O1 /I ".\Mitab-1.3.0" /I ".\Mitab-1.3.0\cpl" /I ".\Mitab-1.3.0\ogr" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /Fd"Release/TRiASMI.pdb" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /Oicf /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 delayimp.lib /nologo /subsystem:windows /dll /debug /machine:I386 /def:"TRiASMI.def" /delayload:crp32dll.dll /delayload:ole32.dll /delayload:oleaut32.dll
# Begin Custom Build
TargetDir=.\Release
TargetPath=.\Release\TRiASMI.dll
TargetName=TRiASMI
InputPath=.\Release\TRiASMI.dll
SOURCE="$(InputPath)"

"$(TRIASDIR_R)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(TargetPath) $(TRIASDIR_R) 
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_R) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASMI - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I ".\Mitab-1.3.0" /I ".\Mitab-1.3.0\cpl" /I ".\Mitab-1.3.0\ogr" /D "_DEBUG" /D "DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /Fd"Debug/TRiASMId.pdb" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /Oicf /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 delayimp.lib /nologo /subsystem:windows /dll /debug /machine:I386 /def:"TRiASMI.def" /out:"Debug/TRiASMId.dll" /delayload:crp32dll.dll /delayload:ole32.dll /delayload:oleaut32.dll
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build
TargetDir=.\Debug
TargetPath=.\Debug\TRiASMId.dll
TargetName=TRiASMId
InputPath=.\Debug\TRiASMId.dll
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(TargetPath) $(TRIASDIR_D) 
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_D) 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "TRiASMI - Win32 Release"
# Name "TRiASMI - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Helper Sources"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=.\DBUtil.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASMICursorProperty.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASMIGeometryBlob.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASMIPropertySupportImpl.cpp
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "TRiASMI Object Sources"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=.\TRiASMIDatabase.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASMIDBEngine.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASMIFeature.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASMIFeatures.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASMIGeoFeature.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASMIGeoFeatures.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASMIObject.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASMIObjects.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASMIObjectsCollection.cpp
# End Source File
# End Group
# Begin Group "MiTab Wrapper Sources"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=.\mitab_capi_ex.cpp
# End Source File
# Begin Source File

SOURCE=.\MiTabCSFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\MiTabDatasource.cpp
# End Source File
# Begin Source File

SOURCE=.\MiTabLayer.cpp
# End Source File
# Begin Source File

SOURCE=.\MiTabTree.cpp
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

SOURCE=.\TRiASMI.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASMI.idl
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

SOURCE=.\TRiASMICursorProperty.h
# End Source File
# Begin Source File

SOURCE=.\TRiASMIGeometryBlob.h
# End Source File
# Begin Source File

SOURCE=.\TRiASMIPropertyBase.h
# End Source File
# Begin Source File

SOURCE=.\TRiASMIPropertySupport.h
# End Source File
# Begin Source File

SOURCE=.\TRiASMISmartIfs.h
# End Source File
# End Group
# Begin Group "TRiASMI Object Headers"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=.\TRiASMIDatabase.h
# End Source File
# Begin Source File

SOURCE=.\TRiASMIDBEngine.h
# End Source File
# Begin Source File

SOURCE=.\TRiASMIFeature.h
# End Source File
# Begin Source File

SOURCE=.\TRiASMIFeatures.h
# End Source File
# Begin Source File

SOURCE=.\TRiASMIGeoFeature.h
# End Source File
# Begin Source File

SOURCE=.\TRiASMIGeoFeatures.h
# End Source File
# Begin Source File

SOURCE=.\TRiASMIObject.h
# End Source File
# Begin Source File

SOURCE=.\TRiASMIObjects.h
# End Source File
# Begin Source File

SOURCE=.\TRiASMIObjectsCollection.h
# End Source File
# End Group
# Begin Group "MiTab Wrapper Headers"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=.\mitab_capi_ex.h
# End Source File
# Begin Source File

SOURCE=.\MiTabCSFactory.h
# End Source File
# Begin Source File

SOURCE=.\MiTabDatasource.h
# End Source File
# Begin Source File

SOURCE=.\MiTabLayer.h
# End Source File
# Begin Source File

SOURCE=.\MiTabTree.h
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

SOURCE=.\TRiASMI.h
# End Source File
# Begin Source File

SOURCE=.\TRiASMIApp.h
# End Source File
# Begin Source File

SOURCE=.\TRiASMIConfig.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\RES\MapInfo.ico
# End Source File
# Begin Source File

SOURCE=.\Debug\MSG00407.bin
# End Source File
# Begin Source File

SOURCE=.\Release\MSG00407.bin
# End Source File
# Begin Source File

SOURCE=.\TRiASMI.rc
# End Source File
# End Group
# Begin Group "Versioning"

# PROP Default_Filter "*.mak,*.tpl"
# Begin Source File

SOURCE=.\TRiASMI.tpl

!IF  "$(CFG)" == "TRiASMI - Win32 Release"

# PROP Ignore_Default_Tool 1
USERDEP__TRIAS="Version.mak"	
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\TRiASMI.tpl

"TRiASMI.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak "TRiASMI.def"

# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASMI - Win32 Debug"

# PROP Ignore_Default_Tool 1
USERDEP__TRIAS="Version.mak"	
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\TRiASMI.tpl

"TRiASMI.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak "TRiASMI.def"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RES\TRiASMIv.tpl

!IF  "$(CFG)" == "TRiASMI - Win32 Release"

# PROP Ignore_Default_Tool 1
USERDEP__TRIASM="Version.mak"	
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\RES\TRiASMIv.tpl

"Res/TRiASMI.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak "Res/TRiASMI.rcv"

# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASMI - Win32 Debug"

# PROP Ignore_Default_Tool 1
USERDEP__TRIASM="Version.mak"	
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\RES\TRiASMIv.tpl

"Res/TRiASMI.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak "Res/TRiASMI.rcv"

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

!IF  "$(CFG)" == "TRiASMI - Win32 Release"

# PROP Ignore_Default_Tool 1
USERDEP__VERSI="Version.mak"	
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\Version.tpl

"Version.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak Version.h

# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASMI - Win32 Debug"

# PROP Ignore_Default_Tool 1
USERDEP__VERSI="Version.mak"	
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

SOURCE=.\RES\TRiASMICursorProperty.rgs
# End Source File
# Begin Source File

SOURCE=.\RES\TRiASMIDatabase.rgs
# End Source File
# Begin Source File

SOURCE=.\RES\TRiASMIDBEngine.rgs
# End Source File
# Begin Source File

SOURCE=.\RES\TRiASMIFeature.rgs
# End Source File
# Begin Source File

SOURCE=.\RES\TRiASMIFeatures.rgs
# End Source File
# Begin Source File

SOURCE=.\RES\TRiASMIGeoFeature.rgs
# End Source File
# Begin Source File

SOURCE=.\RES\TRiASMIGeoFeatures.rgs
# End Source File
# Begin Source File

SOURCE=.\RES\TRiASMIObject.rgs
# End Source File
# Begin Source File

SOURCE=.\RES\TRiASMIObjects.rgs
# End Source File
# Begin Source File

SOURCE=.\RES\TRiASMIObjectsCollection.rgs
# End Source File
# End Group
# Begin Group "MessageStrings"

# PROP Default_Filter "*.mc"
# Begin Source File

SOURCE=.\TRiASMI.mc

!IF  "$(CFG)" == "TRiASMI - Win32 Release"

# Begin Custom Build
InputDir=.
OutDir=.\Release
InputPath=.\TRiASMI.mc
InputName=TRiASMI

BuildCmds= \
	cl -nologo -TC -C -EP -D_DEBUG -u $(InputPath) > $(OutDir)\$(InputName).i \
	mc -e hmc -h $(InputDir) -r "$(OutDir)" "$(OutDir)\$(InputName).i " \
	mc2const -h .\Help  $(OutDir)\$(InputName).i \
	del "$(OutDir)\$(InputName).i" > nul \
	

"$(OutDir)\Msg00407.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"TRiASMI.hmc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASMI - Win32 Debug"

# Begin Custom Build
InputDir=.
OutDir=.\Debug
InputPath=.\TRiASMI.mc
InputName=TRiASMI

BuildCmds= \
	cl -nologo -TC -C -EP -D_DEBUG -u $(InputPath) > $(OutDir)\$(InputName).i \
	mc -e hmc -h $(InputDir) -r "$(OutDir)" "$(OutDir)\$(InputName).i " \
	mc2const -h .\Help  $(OutDir)\$(InputName).i \
	rem del "$(OutDir)\$(InputName).i" > nul \
	

"$(OutDir)\Msg00407.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"TRiASMI.hmc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
