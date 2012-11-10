# Microsoft Developer Studio Project File - Name="PerfMon" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=PerfMon - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "PerfMon.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "PerfMon.mak" CFG="PerfMon - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "PerfMon - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "PerfMon - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "PerfMon - Win32 Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "PerfMon - Win32 Unicode Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Tools/PerfMon", HTRAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "PerfMon - Win32 Debug"

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
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "__PERFMONDLL__" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ospace5d.lib loadperf.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"Debug/PerfMond.dll" /pdbtype:sept
# Begin Custom Build - Copying target to destination ...
OutDir=.\Debug
TargetPath=.\Debug\PerfMond.dll
TargetName=PerfMond
InputPath=.\Debug\PerfMond.dll
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(TargetPath) $(TRIASDIR_D) 
	xcopy /F $(OutDir)\$(TargetName).pdb $(TRIASDIR_D) 
	xcopy /F $(OutDir)\$(TargetName).lib $(TRIASLIB) 
	xcopy /F $(OutDir)\$(TargetName).pdb $(TRIASLIB) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "PerfMon - Win32 Unicode Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugU"
# PROP BASE Intermediate_Dir "DebugU"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugU"
# PROP Intermediate_Dir "DebugU"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "_UNICODE" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "__PERFMONDLL__" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\DebugU
TargetPath=.\DebugU\PerfMon.dll
InputPath=.\DebugU\PerfMon.dll
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "PerfMon - Win32 Release MinSize"

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
# ADD BASE CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /Zi /O1 /D "NDEBUG" /D "_ATL_DLL" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "__PERFMONDLL__" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "_AFXDLL" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ospace5r.lib loadperf.lib /nologo /subsystem:windows /dll /debug /machine:I386

!ELSEIF  "$(CFG)" == "PerfMon - Win32 Unicode Release MinSize"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseUMinSize"
# PROP BASE Intermediate_Dir "ReleaseUMinSize"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseUMinSize"
# PROP Intermediate_Dir "ReleaseUMinSize"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O1 /D "NDEBUG" /D "_UNICODE" /D "_ATL_DLL" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "__PERFMONDLL__" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\PerfMon.dll
InputPath=.\ReleaseUMinSize\PerfMon.dll
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "PerfMon - Win32 Debug"
# Name "PerfMon - Win32 Unicode Debug"
# Name "PerfMon - Win32 Release MinSize"
# Name "PerfMon - Win32 Unicode Release MinSize"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "General purpose files"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=.\dlldatax.c
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\PerfMon.cpp
# End Source File
# Begin Source File

SOURCE=.\PerfMon.def
# End Source File
# Begin Source File

SOURCE=.\PerfMonData.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Object sources"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=.\PerfCounter.cpp
# End Source File
# Begin Source File

SOURCE=.\PerfCounterDefinition.cpp
# End Source File
# Begin Source File

SOURCE=.\PerfData.cpp
# End Source File
# Begin Source File

SOURCE=.\PerfInstanceDefinition.cpp
# End Source File
# Begin Source File

SOURCE=.\PerfObject.cpp
# End Source File
# End Group
# Begin Group "Collection sources"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=.\PerfCounterDefinitions.cpp
# End Source File
# Begin Source File

SOURCE=.\PerfCounters.cpp
# End Source File
# Begin Source File

SOURCE=.\PerfInstanceDefinitions.cpp
# End Source File
# Begin Source File

SOURCE=.\PerfObjects.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\PerfMon.idl

!IF  "$(CFG)" == "PerfMon - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Performing MIDL step
InputPath=.\PerfMon.idl

BuildCmds= \
	midl /Oicf /h "PerfMon.h" /iid "PerfMon_i.c" "PerfMon.idl" \
	xcopy /F PerfMon.tlb $(TRIASINCLUDE)\tlb \
	

".\PerfMon.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\PerfMon.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\PerfMon_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "PerfMon - Win32 Unicode Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Performing MIDL step
InputPath=.\PerfMon.idl

BuildCmds= \
	midl /Oicf /h "PerfMon.h" /iid "PerfMon_i.c" "PerfMon.idl"

".\PerfMon.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\PerfMon.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\PerfMon_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "PerfMon - Win32 Release MinSize"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Performing MIDL step
InputPath=.\PerfMon.idl

BuildCmds= \
	midl /Oicf /h "PerfMon.h" /iid "PerfMon_i.c" "PerfMon.idl"

".\PerfMon.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\PerfMon.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\PerfMon_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "PerfMon - Win32 Unicode Release MinSize"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Performing MIDL step
InputPath=.\PerfMon.idl

BuildCmds= \
	midl /Oicf /h "PerfMon.h" /iid "PerfMon_i.c" "PerfMon.idl"

".\PerfMon.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\PerfMon.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\PerfMon_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\PerfMon.rc
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "General purpose headers"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=.\dlldatax.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\EventLogMacros.h
# End Source File
# Begin Source File

SOURCE=.\PerfMonConfig.h
# End Source File
# Begin Source File

SOURCE=.\PerfMonUtil.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Wrapper.h
# End Source File
# End Group
# Begin Group "Object headers"

# PROP Default_Filter "*.h'"
# Begin Source File

SOURCE=.\PerfCounter.h
# End Source File
# Begin Source File

SOURCE=.\PerfCounterDefinition.h
# End Source File
# Begin Source File

SOURCE=.\PerfData.h
# End Source File
# Begin Source File

SOURCE=.\PerfInstanceDefinition.h
# End Source File
# Begin Source File

SOURCE=.\PerfObject.h
# End Source File
# End Group
# Begin Group "Collection headers"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=.\PerfCounterDefinitions.h
# End Source File
# Begin Source File

SOURCE=.\PerfCounters.h
# End Source File
# Begin Source File

SOURCE=.\PerfInstanceDefinitions.h
# End Source File
# Begin Source File

SOURCE=.\PerfObjects.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\MSG00407.bin
# End Source File
# End Group
# Begin Group "Registry Scripts"

# PROP Default_Filter "*.rgs"
# Begin Source File

SOURCE=.\PerfCounterDefinition.rgs
# End Source File
# Begin Source File

SOURCE=.\PerfCounterDefinitions.rgs
# End Source File
# Begin Source File

SOURCE=.\PerfCounterInt32.rgs
# End Source File
# Begin Source File

SOURCE=.\PerfCounterInt64.rgs
# End Source File
# Begin Source File

SOURCE=.\PerfCounters.rgs
# End Source File
# Begin Source File

SOURCE=.\PerfData.rgs
# End Source File
# Begin Source File

SOURCE=.\PerfInstanceDefinition.rgs
# End Source File
# Begin Source File

SOURCE=.\PerfInstanceDefinitions.rgs
# End Source File
# Begin Source File

SOURCE=.\PerfMon.rgs
# End Source File
# Begin Source File

SOURCE=.\PerfObject.rgs
# End Source File
# Begin Source File

SOURCE=.\PerfObjects.rgs
# End Source File
# End Group
# Begin Group "Message Strings"

# PROP Default_Filter "*.mc"
# Begin Source File

SOURCE=.\MemCtrs.h
# End Source File
# Begin Source File

SOURCE=.\MemCtrs.Mc

!IF  "$(CFG)" == "PerfMon - Win32 Debug"

# Begin Custom Build
InputDir=.
InputPath=.\MemCtrs.Mc

"$(InputDir)\Msg00407.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	mc -e h -h $(InputDir) $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "PerfMon - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "PerfMon - Win32 Release MinSize"

!ELSEIF  "$(CFG)" == "PerfMon - Win32 Unicode Release MinSize"

!ENDIF 

# End Source File
# End Group
# Begin Group "Versioning"

# PROP Default_Filter "*.tpl;*.mak"
# Begin Source File

SOURCE=.\PerfMon.tpl

!IF  "$(CFG)" == "PerfMon - Win32 Debug"

USERDEP__PERFM="version.mak"	
# Begin Custom Build - Generating version information ...
InputPath=.\PerfMon.tpl

"PerfMon.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f version.mak -nologo PerfMon.def

# End Custom Build

!ELSEIF  "$(CFG)" == "PerfMon - Win32 Unicode Debug"

USERDEP__PERFM="version.mak"	
# Begin Custom Build - Generating version information ...
InputPath=.\PerfMon.tpl

"PerfMon.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f version.mak -nologo PerfMon.def

# End Custom Build

!ELSEIF  "$(CFG)" == "PerfMon - Win32 Release MinSize"

USERDEP__PERFM="version.mak"	
# Begin Custom Build - Generating version information ...
InputPath=.\PerfMon.tpl

"PerfMon.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f version.mak -nologo PerfMon.def

# End Custom Build

!ELSEIF  "$(CFG)" == "PerfMon - Win32 Unicode Release MinSize"

USERDEP__PERFM="version.mak"	
# Begin Custom Build - Generating version information ...
InputPath=.\PerfMon.tpl

"PerfMon.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f version.mak -nologo PerfMon.def

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\PerfMonv.tpl

!IF  "$(CFG)" == "PerfMon - Win32 Debug"

USERDEP__PERFMO="version.mak"	
# Begin Custom Build - Generating version information ...
InputPath=.\PerfMonv.tpl

"PerfMon.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f version.mak -nologo PerfMon.rcv

# End Custom Build

!ELSEIF  "$(CFG)" == "PerfMon - Win32 Unicode Debug"

USERDEP__PERFMO="version.mak"	
# Begin Custom Build - Generating version information ...
InputPath=.\PerfMonv.tpl

"PerfMon.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f version.mak -nologo PerfMon.rcv

# End Custom Build

!ELSEIF  "$(CFG)" == "PerfMon - Win32 Release MinSize"

USERDEP__PERFMO="version.mak"	
# Begin Custom Build - Generating version information ...
InputPath=.\PerfMonv.tpl

"PerfMon.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f version.mak -nologo PerfMon.rcv

# End Custom Build

!ELSEIF  "$(CFG)" == "PerfMon - Win32 Unicode Release MinSize"

USERDEP__PERFMO="version.mak"	
# Begin Custom Build - Generating version information ...
InputPath=.\PerfMonv.tpl

"PerfMon.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f version.mak -nologo PerfMon.rcv

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Version.mak
# End Source File
# Begin Source File

SOURCE=.\Version.tpl

!IF  "$(CFG)" == "PerfMon - Win32 Debug"

USERDEP__VERSI="version.mak"	
# Begin Custom Build - Generating version information ...
InputPath=.\Version.tpl

"version.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f version.mak -nologo version.h

# End Custom Build

!ELSEIF  "$(CFG)" == "PerfMon - Win32 Unicode Debug"

USERDEP__VERSI="version.mak"	
# Begin Custom Build - Generating version information ...
InputPath=.\Version.tpl

"version.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f version.mak -nologo version.h

# End Custom Build

!ELSEIF  "$(CFG)" == "PerfMon - Win32 Release MinSize"

USERDEP__VERSI="version.mak"	
# Begin Custom Build - Generating version information ...
InputPath=.\Version.tpl

"version.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f version.mak -nologo version.h

# End Custom Build

!ELSEIF  "$(CFG)" == "PerfMon - Win32 Unicode Release MinSize"

USERDEP__VERSI="version.mak"	
# Begin Custom Build - Generating version information ...
InputPath=.\Version.tpl

"version.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f version.mak -nologo version.h

# End Custom Build

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
