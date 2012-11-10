# Microsoft Developer Studio Project File - Name="GeodCtf_COM" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=GeodCtf_COM - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "GeodCtf_COM.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "GeodCtf_COM.mak" CFG="GeodCtf_COM - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "GeodCtf_COM - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "GeodCtf_COM - Win32 Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/GeodCtf_COM", ZQAAAAAA"
# PROP Scc_LocalPath "."
CPP=xicl6.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "GeodCtf_COM - Win32 Debug"

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
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ospace5d.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"Debug/GeodCtfd.css" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying Target to Destination ...
TargetDir=.\Debug
TargetPath=.\Debug\GeodCtfd.css
TargetName=GeodCtfd
InputPath=.\Debug\GeodCtfd.css
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\GeodCtfd.css" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(TRIASDIR_D) 
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_D) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "GeodCtf_COM - Win32 Release MinSize"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMinSize"
# PROP BASE Intermediate_Dir "ReleaseMinSize"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseMinSize"
# PROP Intermediate_Dir "ReleaseMinSize"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_ATL_DLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /out:"ReleaseMinSize/GeodCtfs.css"
# Begin Custom Build - Copying target to destination ...
TargetDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\GeodCtfs.css
TargetName=GeodCtfs
InputPath=.\ReleaseMinSize\GeodCtfs.css
SOURCE="$(InputPath)"

"$(TRIASDIR_R)\$(TargetName).css" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(TRIASDIR_R) 
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_R) 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "GeodCtf_COM - Win32 Debug"
# Name "GeodCtf_COM - Win32 Release MinSize"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CoordTransBase.cpp
# End Source File
# Begin Source File

SOURCE=.\CTFExContext.cpp
# End Source File
# Begin Source File

SOURCE=.\CTFParams.cpp
# End Source File
# Begin Source File

SOURCE=.\DebugSupport.cpp

!IF  "$(CFG)" == "GeodCtf_COM - Win32 Debug"

!ELSEIF  "$(CFG)" == "GeodCtf_COM - Win32 Release MinSize"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\dllfloat.cpp
# End Source File
# Begin Source File

SOURCE=.\GeodBesselCoordTrans.cpp
# End Source File
# Begin Source File

SOURCE=.\GeodCtf_COM.cpp
# End Source File
# Begin Source File

SOURCE=.\GeodCtf_COM.def
# End Source File
# Begin Source File

SOURCE=.\GeodCtf_COM.idl

!IF  "$(CFG)" == "GeodCtf_COM - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Performing MIDL step
InputPath=.\GeodCtf_COM.idl

BuildCmds= \
	midl /Oicf /h "GeodCtf_COM.h" /iid "GeodCtf_COM_i.c" "GeodCtf_COM.idl"

".\GeodCtf_COM.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\GeodCtf_COM.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\GeodCtf_COM_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "GeodCtf_COM - Win32 Release MinSize"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Performing MIDL step
InputPath=.\GeodCtf_COM.idl

BuildCmds= \
	midl /Oicf /h "GeodCtf_COM.h" /iid "GeodCtf_COM_i.c" "GeodCtf_COM.idl"

".\GeodCtf_COM.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\GeodCtf_COM.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\GeodCtf_COM_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\GeodCtf_COM.rc
# End Source File
# Begin Source File

SOURCE=.\GeodCTFPropExt.cpp
# End Source File
# Begin Source File

SOURCE=.\GeodEtrsCoordTrans.cpp
# End Source File
# Begin Source File

SOURCE=.\GeodKrassCoordTrans.cpp
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
# Begin Source File

SOURCE=.\CoordPara.h
# End Source File
# Begin Source File

SOURCE=.\CoordTransBase.h
# End Source File
# Begin Source File

SOURCE=.\CPCTFTransformEvents.h
# End Source File
# Begin Source File

SOURCE=.\CTFExContext.h
# End Source File
# Begin Source File

SOURCE=.\CTFParams.h
# End Source File
# Begin Source File

SOURCE=.\CTFPropSheetExt.h
# End Source File
# Begin Source File

SOURCE=.\GeodBesselCoordTrans.h
# End Source File
# Begin Source File

SOURCE=.\GeodCTFPropExt.h
# End Source File
# Begin Source File

SOURCE=.\GeodEtrsCoordTrans.h
# End Source File
# Begin Source File

SOURCE=.\GeodKrassCoordTrans.h
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

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\GeodCtf_COM.rcv
# End Source File
# Begin Source File

SOURCE=.\GeodCtf_COM.tlb
# End Source File
# End Group
# Begin Group "Versioning"

# PROP Default_Filter "tpl"
# Begin Source File

SOURCE=.\GeodCtf.mak

!IF  "$(CFG)" == "GeodCtf_COM - Win32 Debug"

# PROP Intermediate_Dir ".\Debug"

!ELSEIF  "$(CFG)" == "GeodCtf_COM - Win32 Release MinSize"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\GeodCtf_COM.tpl

!IF  "$(CFG)" == "GeodCtf_COM - Win32 Debug"

USERDEP__GEODC="GeodCTF.mak"	
# Begin Custom Build - Generating version strings ...
InputPath=.\GeodCtf_COM.tpl

"GeodCtf_COM.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f GeodCtf.mak GeodCtf_COM.def

# End Custom Build

!ELSEIF  "$(CFG)" == "GeodCtf_COM - Win32 Release MinSize"

USERDEP__GEODC="GeodCtf.mak"	
# Begin Custom Build
InputPath=.\GeodCtf_COM.tpl

"GeodCtf_COM.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f GeodCtf.mak GeodCtf_COM.def

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\GeodCtf_COMv.tpl

!IF  "$(CFG)" == "GeodCtf_COM - Win32 Debug"

USERDEP__GEODCT="GeodCTF.mak"	
# Begin Custom Build - Generating version strings ...
InputPath=.\GeodCtf_COMv.tpl

"GeodCtf_COM.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f GeodCtf.mak -nologo GeodCtf_COM.rcv

# End Custom Build

!ELSEIF  "$(CFG)" == "GeodCtf_COM - Win32 Release MinSize"

USERDEP__GEODCT="GeodCtf.mak"	
# Begin Custom Build
InputPath=.\GeodCtf_COMv.tpl

"GeodCtf_COM.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f GeodCtf.mak GeodCtf_COM.rcv

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Registry Scripts"

# PROP Default_Filter "rgs"
# Begin Source File

SOURCE=.\CTFExContext.rgs
# End Source File
# Begin Source File

SOURCE=.\GeodBesselCoordTrans.rgs
# End Source File
# Begin Source File

SOURCE=.\GeodCtf.rgs
# End Source File
# Begin Source File

SOURCE=.\GeodEtrsCoordTrans.rgs
# End Source File
# Begin Source File

SOURCE=.\GeodKrassCoordTrans.rgs
# End Source File
# End Group
# End Target
# End Project
