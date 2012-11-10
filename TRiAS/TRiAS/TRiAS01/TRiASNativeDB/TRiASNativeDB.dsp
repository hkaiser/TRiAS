# Microsoft Developer Studio Project File - Name="TRiASNativeDB" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=TRiASNativeDB - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TRiASNativeDB.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TRiASNativeDB.mak" CFG="TRiASNativeDB - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TRiASNativeDB - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "TRiASNativeDB - Win32 Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TRiASNativeDB - Win32 Debug"

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
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Fp"Debug/TRiASNativeDBd.pch" /Yu"StdAfx.h" /Fd"Debug/TRiASNativeDBd.pdb" /FD /GZ /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 trias31d.lib shlwapi.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"Debug/TRiASNativeDBd.dll"
# Begin Custom Build - Copying target to destination ...
OutDir=.\Debug
TargetPath=.\Debug\TRiASNativeDBd.dll
TargetName=TRiASNativeDBd
InputPath=.\Debug\TRiASNativeDBd.dll
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(TRIASDIR_D) 
	xcopy /F "$(OutDir)\$(TargetName).pdb" $(TRIASDIR_D) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASNativeDB - Win32 Release MinSize"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMinSize"
# PROP BASE Intermediate_Dir "ReleaseMinSize"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseMinSize"
# PROP Intermediate_Dir "ReleaseMinSize"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /WX /Gm /GX /Zi /O1 /I "." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"StdAfx.h" /FD /c
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 trias321.lib shlwapi.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# Begin Custom Build - Copying target to destination ...
OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\TRiASNativeDB.dll
TargetName=TRiASNativeDB
InputPath=.\ReleaseMinSize\TRiASNativeDB.dll
SOURCE="$(InputPath)"

"$(TRIASDIR_R)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(TargetPath) $(TRIASDIR_R) 
	xcopy /F "$(OutDir)\$(TargetName).pdb" $(TRIASDIR_R) 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "TRiASNativeDB - Win32 Debug"
# Name "TRiASNativeDB - Win32 Release MinSize"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Object Source Files"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=.\Strings.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASNativeAttribute.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASNativeAttributes.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASNativeDataSource.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASNativeIdent.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASNativeIdents.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASNativeObject.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASNativeObjects.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASNativeObjectsOperations.cpp
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
# ADD CPP /Yc"StdAfx.h"
# End Source File
# Begin Source File

SOURCE=.\TRiASNativeDB.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASNativeDB.def
# End Source File
# Begin Source File

SOURCE=.\TRiASNativeDB.idl

!IF  "$(CFG)" == "TRiASNativeDB - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\TRiASNativeDB.idl

"$(TRIASTLB)\TRiASNativeDB.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl /Oicf /tlb ".\TRiASNativeDB.tlb" /h "TRiASNativeDB.h" /iid "TRiASNativeDB_i.c" "$(InputPath)" 
	xcopy /F ".\TRiASNativeDB.tlb" $(TRIASTLB) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASNativeDB - Win32 Release MinSize"

# ADD MTL /tlb ".\TRiASNativeDB.tlb" /h "TRiASNativeDB.h" /iid "TRiASNativeDB_i.c" /Oicf

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TRiASNativeDB.rc
# End Source File
# Begin Source File

SOURCE=.\Util.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "Object Header Files"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=.\Strings.h
# End Source File
# Begin Source File

SOURCE=.\TRiASNativeAttribute.h
# End Source File
# Begin Source File

SOURCE=.\TRiASNativeAttributes.h
# End Source File
# Begin Source File

SOURCE=.\TRiASNativeDataSource.h
# End Source File
# Begin Source File

SOURCE=.\TRiASNativeIdent.h
# End Source File
# Begin Source File

SOURCE=.\TRiASNativeIdents.h
# End Source File
# Begin Source File

SOURCE=.\TRiASNativeObject.h
# End Source File
# Begin Source File

SOURCE=.\TRiASNativeObjects.h
# End Source File
# Begin Source File

SOURCE=.\TRiASNativeObjectsOperations.h
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

SOURCE=.\TRiASNativeDBConfig.h
# End Source File
# Begin Source File

SOURCE=.\Util.h
# End Source File
# Begin Source File

SOURCE=.\Wrapper.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\RES\Idt1024c.dbd
# End Source File
# Begin Source File

SOURCE=.\RES\Idt_v12.dbd
# End Source File
# Begin Source File

SOURCE=.\RES\Idt_v13.dbd
# End Source File
# Begin Source File

SOURCE=.\RES\Ris2048c.011
# End Source File
# Begin Source File

SOURCE=.\RES\ris2048c_v17.dbd
# End Source File
# Begin Source File

SOURCE=.\RES\ris2048c_v19.dbd
# End Source File
# End Group
# Begin Group "Versioning"

# PROP Default_Filter "*.tpl,*.mak"
# Begin Source File

SOURCE=.\TRiASNativeDB.tpl

!IF  "$(CFG)" == "TRiASNativeDB - Win32 Debug"

USERDEP__TRIAS="version.mak"	
# Begin Custom Build
InputPath=.\TRiASNativeDB.tpl

"TRiASNativeDB.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f version.mak -nologo TRiASNativeDB.def

# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASNativeDB - Win32 Release MinSize"

USERDEP__TRIAS="version.mak"	
# Begin Custom Build
InputPath=.\TRiASNativeDB.tpl

"TRiASNativeDB.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f version.mak -nologo TRiASNativeDB.def

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TRiASNativeDBv.tpl

!IF  "$(CFG)" == "TRiASNativeDB - Win32 Debug"

USERDEP__TRIASN="version.mak"	
# Begin Custom Build
InputPath=.\TRiASNativeDBv.tpl

"TRiASNativeDB.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f version.mak -nologo TRiASNativeDB.rcv

# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASNativeDB - Win32 Release MinSize"

USERDEP__TRIASN="version.mak"	
# Begin Custom Build
InputPath=.\TRiASNativeDBv.tpl

"TRiASNativeDB.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f version.mak -nologo TRiASNativeDB.rcv

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Version.mak
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Version.tpl

!IF  "$(CFG)" == "TRiASNativeDB - Win32 Debug"

USERDEP__VERSI="version.mak"	
# Begin Custom Build
InputPath=.\Version.tpl

"Version.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f version.mak -nologo Version.h

# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASNativeDB - Win32 Release MinSize"

USERDEP__VERSI="version.mak"	
# Begin Custom Build
InputPath=.\Version.tpl

"Version.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f version.mak -nologo Version.h

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Registry Scripts"

# PROP Default_Filter "*.rgs"
# Begin Source File

SOURCE=.\TRiASNativeAttribute.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASNativeAttributes.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASNativeDataSource.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASNativeIdent.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASNativeIdents.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASNativeObject.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASNativeObjects.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASNativeObjectsOperations.rgs
# End Source File
# End Group
# End Target
# End Project
