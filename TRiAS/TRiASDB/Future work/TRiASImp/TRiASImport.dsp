# Microsoft Developer Studio Project File - Name="TRiASImport" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=TRiASImport - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TRiASImport.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TRiASImport.mak" CFG="TRiASImport - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TRiASImport - Win32 Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "TRiASImport - Win32 Unicode Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "TRiASImport - Win32 Release MinSize" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "TRiASImport - Win32 Release MinDependency" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "TRiASImport - Win32 Unicode Release MinSize" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "TRiASImport - Win32 Unicode Release MinDependency" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""$/TRiASImport", DGAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TRiASImport - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "__ATL_20_USED__" /D "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 OSpace5d.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"Debug/TRiASImD.dll" /pdbtype:sept
# Begin Custom Build - Copying target to destination ...
TargetPath=.\Debug\TRiASImD.dll
InputPath=.\Debug\TRiASImD.dll
SOURCE=$(InputPath)

"e:\trias.dbg\TRiASImD.dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(TargetPath) e:\trias.dbg

# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Unicode Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
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
TargetPath=.\DebugU\TRiASImport.dll
InputPath=.\DebugU\TRiASImport.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Release MinSize"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMinSize"
# PROP BASE Intermediate_Dir "ReleaseMinSize"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseMinSize"
# PROP Intermediate_Dir "ReleaseMinSize"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_ATL_DLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\TRiASImport.dll
InputPath=.\ReleaseMinSize\TRiASImport.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Release MinDependency"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMinDependency"
# PROP BASE Intermediate_Dir "ReleaseMinDependency"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseMinDependency"
# PROP Intermediate_Dir "ReleaseMinDependency"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\TRiASImport.dll
InputPath=.\ReleaseMinDependency\TRiASImport.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Unicode Release MinSize"

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
# ADD CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
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
TargetPath=.\ReleaseUMinSize\TRiASImport.dll
InputPath=.\ReleaseUMinSize\TRiASImport.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Unicode Release MinDependency"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseUMinDependency"
# PROP BASE Intermediate_Dir "ReleaseUMinDependency"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseUMinDependency"
# PROP Intermediate_Dir "ReleaseUMinDependency"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\TRiASImport.dll
InputPath=.\ReleaseUMinDependency\TRiASImport.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "TRiASImport - Win32 Debug"
# Name "TRiASImport - Win32 Unicode Debug"
# Name "TRiASImport - Win32 Release MinSize"
# Name "TRiASImport - Win32 Release MinDependency"
# Name "TRiASImport - Win32 Unicode Release MinSize"
# Name "TRiASImport - Win32 Unicode Release MinDependency"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\DatabaseBase.cpp
# End Source File
# Begin Source File

SOURCE=.\DBUtil.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgImportOpt.cpp
# End Source File
# Begin Source File

SOURCE=.\dlldatax.c
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\ImportDBEngine.cpp
# End Source File
# Begin Source File

SOURCE=.\ImportDlgExt.cpp
# End Source File
# Begin Source File

SOURCE=D:\Programme\DevStudio\VC\include\OAIDL.IDL

!IF  "$(CFG)" == "TRiASImport - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Release MinSize"

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Release MinDependency"

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Unicode Release MinSize"

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Unicode Release MinDependency"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=D:\Programme\DevStudio\VC\include\OCIDL.IDL

!IF  "$(CFG)" == "TRiASImport - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Release MinSize"

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Release MinDependency"

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Unicode Release MinSize"

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Unicode Release MinDependency"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\pbasic.cpp
# End Source File
# Begin Source File

SOURCE=.\PDB.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Strings.cpp
# End Source File
# Begin Source File

SOURCE=.\ToDo.txt

!IF  "$(CFG)" == "TRiASImport - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Release MinSize"

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Release MinDependency"

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Unicode Release MinSize"

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Unicode Release MinDependency"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\TriasDB\TriasDB.idl

!IF  "$(CFG)" == "TRiASImport - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Release MinSize"

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Release MinDependency"

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Unicode Release MinSize"

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Unicode Release MinDependency"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TRiASImport.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASImport.def
# End Source File
# Begin Source File

SOURCE=.\TRiASImport.idl

!IF  "$(CFG)" == "TRiASImport - Win32 Debug"

# Begin Custom Build - Performing MIDL step
InputPath=.\TRiASImport.idl

BuildCmds= \
	midl /Oicf /h "TRiASImport.h" /iid "TRiASImport_i.c" "TRiASImport.idl"

".\TRiASImport.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TRiASImport.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TRiASImport_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Unicode Debug"

# Begin Custom Build - Performing MIDL step
InputPath=.\TRiASImport.idl

BuildCmds= \
	midl /Oicf /h "TRiASImport.h" /iid "TRiASImport_i.c" "TRiASImport.idl"

".\TRiASImport.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TRiASImport.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TRiASImport_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Release MinSize"

# Begin Custom Build - Performing MIDL step
InputPath=.\TRiASImport.idl

BuildCmds= \
	midl /Oicf /h "TRiASImport.h" /iid "TRiASImport_i.c" "TRiASImport.idl"

".\TRiASImport.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TRiASImport.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TRiASImport_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Release MinDependency"

# Begin Custom Build - Performing MIDL step
InputPath=.\TRiASImport.idl

BuildCmds= \
	midl /Oicf /h "TRiASImport.h" /iid "TRiASImport_i.c" "TRiASImport.idl"

".\TRiASImport.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TRiASImport.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TRiASImport_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Unicode Release MinSize"

# Begin Custom Build - Performing MIDL step
InputPath=.\TRiASImport.idl

BuildCmds= \
	midl /Oicf /h "TRiASImport.h" /iid "TRiASImport_i.c" "TRiASImport.idl"

".\TRiASImport.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TRiASImport.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TRiASImport_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Unicode Release MinDependency"

# Begin Custom Build - Performing MIDL step
InputPath=.\TRiASImport.idl

BuildCmds= \
	midl /Oicf /h "TRiASImport.h" /iid "TRiASImport_i.c" "TRiASImport.idl"

".\TRiASImport.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TRiASImport.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TRiASImport_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TRiASImport.rc

!IF  "$(CFG)" == "TRiASImport - Win32 Debug"

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Release MinSize"

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Release MinDependency"

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Unicode Release MinSize"

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Unicode Release MinDependency"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Include\Idl\TRiASXtensionSite.idl

!IF  "$(CFG)" == "TRiASImport - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Release MinSize"

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Release MinDependency"

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Unicode Release MinSize"

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Unicode Release MinDependency"

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\DatabaseBase.h
# End Source File
# Begin Source File

SOURCE=.\DBUtil.h
# End Source File
# Begin Source File

SOURCE=.\DlgImportOpt.h
# End Source File
# Begin Source File

SOURCE=.\dlldatax.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\ImportDBEngine.h
# End Source File
# Begin Source File

SOURCE=.\ImportDlgExt.h
# End Source File
# Begin Source File

SOURCE=.\pbasic.h
# End Source File
# Begin Source File

SOURCE=.\PDB.h
# End Source File
# Begin Source File

SOURCE=.\PropSheetExt.h
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

SOURCE=.\TRiASGlb.h
# End Source File
# Begin Source File

SOURCE=.\Wrapper.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "Registry Scripts"

# PROP Default_Filter "rgs"
# Begin Source File

SOURCE=.\DatabaseBase.rgs
# End Source File
# Begin Source File

SOURCE=.\FakeImportServer.rgs
# End Source File
# Begin Source File

SOURCE=.\ImportDBEngine.rgs
# End Source File
# Begin Source File

SOURCE=.\ImportDlgExt.rgs
# End Source File
# End Group
# Begin Group "Versioning"

# PROP Default_Filter "tpl,mak"
# Begin Source File

SOURCE=.\TRiASImport.Tpl

!IF  "$(CFG)" == "TRiASImport - Win32 Debug"

USERDEP__TRIAS="Version.mak"	
# Begin Custom Build - Generating definition file (.DEF) ...
InputPath=.\TRiASImport.Tpl

"TRiASImport.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak TRiASImport.Def

# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Release MinSize"

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Release MinDependency"

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Unicode Release MinSize"

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Unicode Release MinDependency"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TRiASImpv.Tpl

!IF  "$(CFG)" == "TRiASImport - Win32 Debug"

USERDEP__TRIASI="Version.mak"	
# Begin Custom Build - Generating version strings ...
InputPath=.\TRiASImpv.Tpl

"TRiASImport.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak TRiASImport.Rcv

# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Release MinSize"

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Release MinDependency"

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Unicode Release MinSize"

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Unicode Release MinDependency"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Version.mak

!IF  "$(CFG)" == "TRiASImport - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Release MinSize"

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Release MinDependency"

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Unicode Release MinSize"

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Unicode Release MinDependency"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Version.tpl

!IF  "$(CFG)" == "TRiASImport - Win32 Debug"

USERDEP__VERSI="Version.mak"	
# Begin Custom Build - Generating version strings ...
InputPath=.\Version.tpl

"version.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak version.h

# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Release MinSize"

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Release MinDependency"

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Unicode Release MinSize"

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Unicode Release MinDependency"

!ENDIF 

# End Source File
# End Group
# Begin Group "Message Strings"

# PROP Default_Filter "hmc,mc"
# Begin Source File

SOURCE=.\IMPMSG.hmc
# End Source File
# Begin Source File

SOURCE=.\Impmsg.mc

!IF  "$(CFG)" == "TRiASImport - Win32 Debug"

# Begin Custom Build - Generating message tables ...
InputDir=.
OutDir=.\Debug
InputPath=.\Impmsg.mc
InputName=Impmsg

BuildCmds= \
	cl -nologo -TC -C -EP -D_DEBUG -u $(InputPath) > $(OutDir)\$(InputName).i \
	mc -e hmc -h $(InputDir) -r "$(OutDir)" "$(OutDir)\$(InputName).i " \
	del "$(OutDir)\$(InputName).i" \
	

"$(OutDir)\Msg00407.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(OutDir)\Msg00409.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(OutDir)\$(InputName).rc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Release MinSize"

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Release MinDependency"

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Unicode Release MinSize"

!ELSEIF  "$(CFG)" == "TRiASImport - Win32 Unicode Release MinDependency"

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
