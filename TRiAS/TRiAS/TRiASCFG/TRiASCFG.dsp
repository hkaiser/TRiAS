# Microsoft Developer Studio Project File - Name="TRiASCFG" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=TRiASCFG - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TRiASCFG.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TRiASCFG.mak" CFG="TRiASCFG - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TRiASCFG - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "TRiASCFG - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=xicl6.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TRiASCFG - Win32 Release"

# PROP BASE Use_MFC 0
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
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "TRIASCFG_EXPORTS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /Zi /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "TRiASCFG_EXPORTS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 shlwapi.lib shfolder.lib delayimp.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /delayload:shfolder.dll /delayload:shlwapi.dll
# Begin Custom Build
OutDir=.\Release
TargetName=TRiASCFG
InputPath=.\Release\TRiASCFG.dll
SOURCE="$(InputPath)"

"$(TRIASDIR_R)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(OutDir)\$(TargetName).dll" "$(TRIASDIR_R)" 
	xcopy /F "$(OutDir)\$(TargetName).pdb" "$(TRIASDIR_R)" 
	xcopy /F "$(OutDir)\$(TargetName).lib" "$(TRIASLIB)" 
	xcopy /F "$(OutDir)\$(TargetName).pdb" "$(TRIASLIB)" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASCFG - Win32 Debug"

# PROP BASE Use_MFC 0
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
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "TRIASCFG_EXPORTS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "TRiASCFG_EXPORTS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 shlwapi.lib shfolder.lib delayimp.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"Debug/TRiASCFGD.dll" /pdbtype:sept /delayload:shfolder.dll /delayload:shlwapi.dll
# Begin Custom Build
OutDir=.\Debug
TargetName=TRiASCFGD
InputPath=.\Debug\TRiASCFGD.dll
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(OutDir)\$(TargetName).dll" "$(TRIASDIR_D)" 
	xcopy /F "$(OutDir)\$(TargetName).pdb" "$(TRIASDIR_D)" 
	xcopy /F "$(OutDir)\$(TargetName).lib" "$(TRIASLIB)" 
	xcopy /F "$(OutDir)\$(TargetName).pdb" "$(TRIASLIB)" 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "TRiASCFG - Win32 Release"
# Name "TRiASCFG - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\LoadXmlService.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Strings.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASCFG.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASCFG.def
# End Source File
# Begin Source File

SOURCE=.\TRiASCFG.idl

!IF  "$(CFG)" == "TRiASCFG - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\TRiASCFG.idl

"TRiASCFG.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl /win32 /Oicf /h "TRiASCFG.h" /iid "TRiASCFG_i.c"  "TRiASCFG.idl" 
	xcopy /F "TRiASCFG.tlb" $(TRIASTLB) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASCFG - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\TRiASCFG.idl

"TRiASCFG.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl /win32 /Oicf /h "TRiASCFG.h" /iid "TRiASCFG_i.c"  "TRiASCFG.idl" 
	xcopy /F "TRiASCFG.tlb" $(TRIASTLB) 
	
# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\LoadXmlService.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TRiASCFGConfig.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Group "DTD Files"

# PROP Default_Filter "*.dtd"
# Begin Source File

SOURCE=.\Res\GeoComponentCatalog.dtd
# End Source File
# Begin Source File

SOURCE=.\Res\GeoComponentSequence.dtd
# End Source File
# End Group
# Begin Group "XML Files"

# PROP Default_Filter "*.xml"
# Begin Group "GeoComponent Sources"

# PROP Default_Filter "*.xml"
# Begin Source File

SOURCE=.\Res\AddObjectsToClassORWnd.xml
# End Source File
# Begin Source File

SOURCE=.\Res\ClassifyOKS.xml
# End Source File
# Begin Source File

SOURCE=.\Res\ClassifyORWnd.xml
# End Source File
# Begin Source File

SOURCE=.\Res\ComplementaryObjectsORWnd.xml
# End Source File
# Begin Source File

SOURCE=.\Res\CopyObjectsOKS.xml
# End Source File
# Begin Source File

SOURCE=.\Res\CopyObjectsORWnd.xml
# End Source File
# Begin Source File

SOURCE=.\Res\DeleteObjectPropertiesOKS.xml
# End Source File
# Begin Source File

SOURCE=.\Res\DeleteObjectPropertiesORWnd.xml
# End Source File
# Begin Source File

SOURCE=.\Res\DeleteObjectsFromClassORWnd.xml
# End Source File
# Begin Source File

SOURCE=.\Res\DeleteObjectsOKS.xml
# End Source File
# Begin Source File

SOURCE=.\Res\DeleteObjectsORWnd.xml
# End Source File
# Begin Source File

SOURCE=.\Res\GenerateLabelsOKS.xml
# End Source File
# Begin Source File

SOURCE=.\Res\GenerateLabelsORWnd.xml
# End Source File
# Begin Source File

SOURCE=.\Res\GenerateObjPropsOKS.xml
# End Source File
# Begin Source File

SOURCE=.\Res\GenerateObjPropsORWnd.xml
# End Source File
# Begin Source File

SOURCE=.\Res\ImportData.xml
# End Source File
# Begin Source File

SOURCE=.\Res\LoadObjectCollection.xml
# End Source File
# Begin Source File

SOURCE=.\Res\ModifyObjClassOKS.xml
# End Source File
# Begin Source File

SOURCE=.\Res\ModifyObjClassORWnd.xml
# End Source File
# Begin Source File

SOURCE=.\Res\ORWndDifference.xml
# End Source File
# Begin Source File

SOURCE=.\Res\ORWndIntersection.xml
# End Source File
# Begin Source File

SOURCE=.\Res\ORWndInvDifference.xml
# End Source File
# Begin Source File

SOURCE=.\Res\ORWndSymmetricDifference.xml
# End Source File
# Begin Source File

SOURCE=.\Res\ORWndUnion.xml
# End Source File
# Begin Source File

SOURCE=.\Res\SaveObjectCollection.xml
# End Source File
# Begin Source File

SOURCE=.\Res\SearchAndReplaceOKS.xml
# End Source File
# Begin Source File

SOURCE=.\Res\SearchAndReplaceORWnd.xml
# End Source File
# Begin Source File

SOURCE=.\Res\SearchObjectsOKS.xml
# End Source File
# Begin Source File

SOURCE=.\Res\SearchObjectsORWnd.xml
# End Source File
# Begin Source File

SOURCE=.\Res\SelectAndCalculateOKS.xml
# End Source File
# Begin Source File

SOURCE=.\Res\SelectAndCalculateORWnd.xml
# End Source File
# Begin Source File

SOURCE=.\Res\SelectObjectsOKS.xml
# End Source File
# End Group
# Begin Group "Object Property Sources"

# PROP Default_Filter "*.xml"
# Begin Source File

SOURCE=.\Res\SearchAndCalculate.xml
# End Source File
# End Group
# Begin Source File

SOURCE=.\Res\GeoComponentCatalog.xml
# End Source File
# Begin Source File

SOURCE=.\Res\ObjectPropertyCatalog.xml
# End Source File
# End Group
# Begin Source File

SOURCE=.\TRiASCFG.rc
# End Source File
# End Group
# Begin Group "Versioning"

# PROP Default_Filter "*.mak;*.tpl"
# Begin Source File

SOURCE=.\TRiASCFG.tpl

!IF  "$(CFG)" == "TRiASCFG - Win32 Release"

USERDEP__TRIAS="version.mak"	
# Begin Custom Build
InputPath=.\TRiASCFG.tpl

"TRiASCFG.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak TRiASCFG.def

# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASCFG - Win32 Debug"

USERDEP__TRIAS="version.mak"	
# Begin Custom Build
InputPath=.\TRiASCFG.tpl

"TRiASCFG.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak TRiASCFG.def

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TRiASCFGv.tpl

!IF  "$(CFG)" == "TRiASCFG - Win32 Release"

USERDEP__TRIASC="version.mak"	
# Begin Custom Build
InputPath=.\TRiASCFGv.tpl

"TRiASCFG.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak TRiASCFG.rcv

# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASCFG - Win32 Debug"

USERDEP__TRIASC="version.mak"	
# Begin Custom Build
InputPath=.\TRiASCFGv.tpl

"TRiASCFG.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak TRiASCFG.rcv

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Version.mak
# End Source File
# End Group
# Begin Group "XML Spy Projects"

# PROP Default_Filter "*.spp"
# Begin Source File

SOURCE=.\Res\GeoComponents.spp
# End Source File
# End Group
# Begin Group "Registry Scripts"

# PROP Default_Filter "*.rgs"
# Begin Source File

SOURCE=.\LoadXmlService.rgs
# End Source File
# End Group
# End Target
# End Project
