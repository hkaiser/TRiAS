# Microsoft Developer Studio Project File - Name="Fastdb" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=Fastdb - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Fastdb.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Fastdb.mak" CFG="Fastdb - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Fastdb - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Fastdb - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=xicl6.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Fastdb - Win32 Release"

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
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /Zi /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "_USE_FASTDB" /Yu"stdafx.h" /Fd"Release/Fastdb.pdb" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /Oicf
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386 /def:"Fastdb.def"

!ELSEIF  "$(CFG)" == "Fastdb - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "_USE_FASTDB" /Fp"Debug/Fastdbd.pch" /Yu"stdafx.h" /Fd"Debug/Fastdbd.pdb" /FD /GZ /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /Oicf
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /def:"Fastdb.def" /out:"Debug/Fastdbd.dll" /pdbtype:sept
# Begin Custom Build
TargetDir=.\Debug
TargetPath=.\Debug\Fastdbd.dll
TargetName=Fastdbd
InputPath=.\Debug\Fastdbd.dll
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(TRIASDIR_D) 
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_D) 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "Fastdb - Win32 Release"
# Name "Fastdb - Win32 Debug"
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

SOURCE=.\FastDBCursorProperty.cpp
# End Source File
# Begin Source File

SOURCE=.\FastdbPropertySupportImpl.cpp
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "Interface definitions"

# PROP Default_Filter "*.idl"
# Begin Source File

SOURCE=.\Fastdb.idl
# ADD MTL /h "FastDB.h" /iid "FastDB_i.c"
# End Source File
# End Group
# Begin Group "Fastdb Object Sources"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=.\FastdbDatabase.cpp
# End Source File
# Begin Source File

SOURCE=.\FastdbDBEngine.cpp
# End Source File
# Begin Source File

SOURCE=.\FastdbFeature.cpp
# End Source File
# Begin Source File

SOURCE=.\FastdbFeatures.cpp
# End Source File
# Begin Source File

SOURCE=.\FastdbGeoFeature.cpp
# End Source File
# Begin Source File

SOURCE=.\FastdbGeoFeatures.cpp
# End Source File
# Begin Source File

SOURCE=.\FastdbObject.cpp
# End Source File
# Begin Source File

SOURCE=.\FastdbObjects.cpp
# End Source File
# Begin Source File

SOURCE=.\FastdbObjectsCollection.cpp
# End Source File
# End Group
# Begin Group "Fastdb Database Sources"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=.\DBObjects.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\Fastdb.cpp
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
# Begin Group "Helper Headers"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=.\DBUtil.h
# End Source File
# Begin Source File

SOURCE=.\FastDBCursorProperty.h
# End Source File
# Begin Source File

SOURCE=.\FastdbPropertyBase.h
# End Source File
# Begin Source File

SOURCE=.\FastdbPropertySupport.h
# End Source File
# End Group
# Begin Group "Fastdb Object Headers"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=.\FastdbDatabase.h
# End Source File
# Begin Source File

SOURCE=.\FastdbDBEngine.h
# End Source File
# Begin Source File

SOURCE=.\FastdbFeature.h
# End Source File
# Begin Source File

SOURCE=.\FastdbFeatures.h
# End Source File
# Begin Source File

SOURCE=.\FastdbGeoFeature.h
# End Source File
# Begin Source File

SOURCE=.\FastdbGeoFeatures.h
# End Source File
# Begin Source File

SOURCE=.\FastdbObject.h
# End Source File
# Begin Source File

SOURCE=.\FastdbObjects.h
# End Source File
# Begin Source File

SOURCE=.\FastdbObjectsCollection.h
# End Source File
# End Group
# Begin Group "Fastdb Database Headers"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=.\DBObjects.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\dlldatax.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Fastdb.h
# End Source File
# Begin Source File

SOURCE=.\FastdbApp.h
# End Source File
# Begin Source File

SOURCE=.\FastdbConfig.h
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
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Fastdb.rc
# End Source File
# Begin Source File

SOURCE=.\Debug\MSG00407.bin
# End Source File
# Begin Source File

SOURCE=.\Release\MSG00407.bin
# End Source File
# Begin Source File

SOURCE=.\Debug\MSG00409.bin
# End Source File
# End Group
# Begin Group "Registry Scripts"

# PROP Default_Filter "*.rgs"
# Begin Source File

SOURCE=.\RES\FastDBCursorProperty.rgs
# End Source File
# Begin Source File

SOURCE=.\RES\FastdbDatabase.rgs
# End Source File
# Begin Source File

SOURCE=.\RES\FastdbDBEngine.rgs
# End Source File
# Begin Source File

SOURCE=.\RES\FastdbFeature.rgs
# End Source File
# Begin Source File

SOURCE=.\RES\FastdbFeatures.rgs
# End Source File
# Begin Source File

SOURCE=.\RES\FastdbGeoFeature.rgs
# End Source File
# Begin Source File

SOURCE=.\RES\FastdbGeoFeatures.rgs
# End Source File
# Begin Source File

SOURCE=.\RES\FastdbObject.rgs
# End Source File
# Begin Source File

SOURCE=.\RES\FastdbObjectCursorProperty.rgs
# End Source File
# Begin Source File

SOURCE=.\RES\FastdbObjects.rgs
# End Source File
# Begin Source File

SOURCE=.\RES\FastdbObjectsCollection.rgs
# End Source File
# End Group
# Begin Group "Versioning"

# PROP Default_Filter "*.mak;*.tpl"
# Begin Source File

SOURCE=.\Fastdb.tpl

!IF  "$(CFG)" == "Fastdb - Win32 Release"

# PROP Ignore_Default_Tool 1
USERDEP__FASTD="Version.mak"	
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\Fastdb.tpl

"Fastdb.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak "Fastdb.def"

# End Custom Build

!ELSEIF  "$(CFG)" == "Fastdb - Win32 Debug"

# PROP Ignore_Default_Tool 1
USERDEP__FASTD="Version.mak"	
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\Fastdb.tpl

"Fastdb.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak "Fastdb.def"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RES\Fastdbv.tpl

!IF  "$(CFG)" == "Fastdb - Win32 Release"

# PROP Ignore_Default_Tool 1
USERDEP__FASTDB="Version.mak"	
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\RES\Fastdbv.tpl

"Res/Fastdb.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak "Res/Fastdb.rcv"

# End Custom Build

!ELSEIF  "$(CFG)" == "Fastdb - Win32 Debug"

# PROP Ignore_Default_Tool 1
USERDEP__FASTDB="Version.mak"	
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\RES\Fastdbv.tpl

"Res/Fastdb.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak "Res/Fastdb.rcv"

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

!IF  "$(CFG)" == "Fastdb - Win32 Release"

# PROP Ignore_Default_Tool 1
USERDEP__VERSI="Version.mak"	
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\Version.tpl

"Version.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak Version.h

# End Custom Build

!ELSEIF  "$(CFG)" == "Fastdb - Win32 Debug"

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
# Begin Group "MessageStrings"

# PROP Default_Filter "*.hmc;*.mc"
# Begin Source File

SOURCE=.\Fastdb.mc

!IF  "$(CFG)" == "Fastdb - Win32 Release"

# Begin Custom Build
InputDir=.
OutDir=.\Release
InputPath=.\Fastdb.mc
InputName=Fastdb

BuildCmds= \
	cl -nologo -TC -C -EP -D_DEBUG -u $(InputPath) > $(OutDir)\$(InputName).i \
	mc -e hmc -h $(InputDir) -r "$(OutDir)" "$(OutDir)\$(InputName).i " \
	mc2const -h .\Help  $(OutDir)\$(InputName).i \
	del "$(OutDir)\$(InputName).i" > nul \
	

"$(OutDir)\Msg00407.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"FastDB.hmc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Fastdb - Win32 Debug"

# Begin Custom Build
InputDir=.
OutDir=.\Debug
InputPath=.\Fastdb.mc
InputName=Fastdb

BuildCmds= \
	cl -nologo -TC -C -EP -D_DEBUG -u $(InputPath) > $(OutDir)\$(InputName).i \
	mc -e hmc -h $(InputDir) -r "$(OutDir)" "$(OutDir)\$(InputName).i " \
	mc2const -h .\Help  $(OutDir)\$(InputName).i \
	del "$(OutDir)\$(InputName).i" > nul \
	

"$(OutDir)\Msg00407.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"FastDB.hmc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
