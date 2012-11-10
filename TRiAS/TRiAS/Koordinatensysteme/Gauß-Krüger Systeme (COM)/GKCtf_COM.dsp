# Microsoft Developer Studio Project File - Name="GKCtf_COM" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=GKCTF_COM - WIN32 DEBUG
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "GKCtf_COM.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "GKCtf_COM.mak" CFG="GKCTF_COM - WIN32 DEBUG"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "GKCtf_COM - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "GKCtf_COM - Win32 Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/GKCtf_COM", VSAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "GKCtf_COM - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_USRDLL" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /out:"Debug/GKCtfsd.css"
# Begin Custom Build - Copying Target to Destination ...
TargetDir=.\Debug
TargetPath=.\Debug\GKCtfsd.css
TargetName=GKCtfsd
InputPath=.\Debug\GKCtfsd.css
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\GKCtfsd.css" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(TRIASDIR_D) 
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_D) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "GKCtf_COM - Win32 Release MinSize"

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
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /out:"ReleaseMinSize/GKCtfs.css"
# Begin Custom Build - Copying Target to Destination ...
OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\GKCtfs.css
TargetName=GKCtfs
InputPath=.\ReleaseMinSize\GKCtfs.css
SOURCE="$(InputPath)"

"$(TRIASDIR_R)\GKCtfs.css" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(TargetPath) $(TRIASDIR_R) 
	xcopy /F $(OutDir)\$(TargetName).pdb $(TRIASDIR_R) 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "GKCtf_COM - Win32 Debug"
# Name "GKCtf_COM - Win32 Release MinSize"
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

SOURCE=.\dlldatax.c
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\dllfloat.cpp
# End Source File
# Begin Source File

SOURCE=.\GKBesselCoordTrans.cpp
# End Source File
# Begin Source File

SOURCE=.\GKCtf_COM.cpp
# End Source File
# Begin Source File

SOURCE=.\GKCtf_COM.def
# End Source File
# Begin Source File

SOURCE=.\GKCtf_COM.idl

!IF  "$(CFG)" == "GKCtf_COM - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Performing MIDL step
InputPath=.\GKCtf_COM.idl

BuildCmds= \
	midl /Oicf /h "GKCtf_COM.h" /iid "GKCtf_COM_i.c" "GKCtf_COM.idl"

".\GKCtf_COM.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\GKCtf_COM.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\GKCtf_COM_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "GKCtf_COM - Win32 Release MinSize"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Performing MIDL step
InputPath=.\GKCtf_COM.idl

BuildCmds= \
	midl /Oicf /h "GKCtf_COM.h" /iid "GKCtf_COM_i.c" "GKCtf_COM.idl"

".\GKCtf_COM.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\GKCtf_COM.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\GKCtf_COM_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\GKCtf_COM.rc
# End Source File
# Begin Source File

SOURCE=.\GKEtrsCoordTrans.cpp
# End Source File
# Begin Source File

SOURCE=.\GKKrassCoordTrans.cpp
# End Source File
# Begin Source File

SOURCE=.\GKPropExt.cpp
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

SOURCE=.\CoordTransBase.h
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

SOURCE=.\dlldatax.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\GKBesselCoordTrans.h
# End Source File
# Begin Source File

SOURCE=.\GKEtrsCoordTrans.h
# End Source File
# Begin Source File

SOURCE=.\GKKrassCoordTrans.h
# End Source File
# Begin Source File

SOURCE=.\GKPropExt.h
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

SOURCE=.\Wrapper.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "Versioning"

# PROP Default_Filter "*.mak;*.tpl"
# Begin Source File

SOURCE=.\GKCtf.mak
# End Source File
# Begin Source File

SOURCE=.\GKCtf_COM.tpl

!IF  "$(CFG)" == "GKCtf_COM - Win32 Debug"

USERDEP__GKCTF="gkctf.mak"	
# Begin Custom Build - Generating version strings ...
InputPath=.\GKCtf_COM.tpl

".\GKCtf_COM.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f GKCtf.mak GKCtf_COM.def

# End Custom Build

!ELSEIF  "$(CFG)" == "GKCtf_COM - Win32 Release MinSize"

USERDEP__GKCTF="gkctf.mak"	
# Begin Custom Build
InputPath=.\GKCtf_COM.tpl

"GKCTF_Com.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f GKCtf.mak GKCtf_COM.def

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\GKCtf_COMv.tpl

!IF  "$(CFG)" == "GKCtf_COM - Win32 Debug"

USERDEP__GKCTF_="gkctf.mak"	
# Begin Custom Build - Generating version strings ...
InputPath=.\GKCtf_COMv.tpl

".\GKCtf_COM.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f GKCtf.mak -nologo GKCtf_COM.rcv

# End Custom Build

!ELSEIF  "$(CFG)" == "GKCtf_COM - Win32 Release MinSize"

USERDEP__GKCTF_="gkctf.mak"	
# Begin Custom Build
InputPath=.\GKCtf_COMv.tpl

"GKCtf_COM.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f GKCtf.mak GKCtf_COM.rcv

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Registry Scripts"

# PROP Default_Filter "*.rgs"
# Begin Source File

SOURCE=.\CTFExContext.rgs
# End Source File
# Begin Source File

SOURCE=.\GKBesselCoordTrans.rgs
# End Source File
# Begin Source File

SOURCE=.\GKCtf.rgs
# End Source File
# Begin Source File

SOURCE=.\GKCtf_GCO.rgs
# End Source File
# Begin Source File

SOURCE=.\GKCtf_Internal.rgs
# End Source File
# Begin Source File

SOURCE=.\GKEtrsCoordTrans.rgs
# End Source File
# Begin Source File

SOURCE=.\GKKrassCoordTrans.rgs
# End Source File
# End Group
# End Target
# End Project
