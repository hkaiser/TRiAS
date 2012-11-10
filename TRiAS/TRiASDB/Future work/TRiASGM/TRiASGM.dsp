# Microsoft Developer Studio Project File - Name="TRiASGM" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=TRiASGM - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TRiASGM.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TRiASGM.mak" CFG="TRiASGM - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TRiASGM - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "TRiASGM - Win32 Release MinSize" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TRiASGM - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "C:\MSDev5\VC\GeoMedia\Include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "__ATL_USED__" /D "QI_EXCEPTION" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "NOMINMAX" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D "OS_NO_STREAM_SUPPORT" /D "OS_NO_ALLOCATORS" /D "__ATL_20_USED__" /D "ATL_NO_NAMESPACE" /D "MSWIND" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 trias31d.lib ospace5d.lib GMCInMemRecSetd.lib MemRecSetsd.lib GeomUtld.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept /libpath:"C:\MSDev5\VC\GeoMedia\lib"
# SUBTRACT LINK32 /nodefaultlib
# Begin Custom Build - Registering ActiveX Control ...
OutDir=.\Debug
TargetPath=.\Debug\TRiASGM.dll
InputPath=.\Debug\TRiASGM.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASGM - Win32 Release MinSize"

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
# ADD CPP /nologo /MD /W3 /WX /GX /Od /I "C:\MSDev5\VC\GeoMedia\Include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "__ATL_USED__" /D "QI_EXCEPTION" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "NOMINMAX" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D "OS_NO_STREAM_SUPPORT" /D "OS_NO_ALLOCATORS" /D "__ATL_20_USED__" /D "ATL_NO_NAMESPACE" /D "MSWIND" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 trias321.lib ospace5r.lib GMCInMemRecSet1.lib MemRecSets1.lib GeomUtl1.lib /nologo /subsystem:windows /dll /machine:I386 /libpath:"C:\MSDev5\VC\GeoMedia\lib"
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\TRiASGM.dll
InputPath=.\ReleaseMinSize\TRiASGM.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "TRiASGM - Win32 Debug"
# Name "TRiASGM - Win32 Release MinSize"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CssHeader.cpp
# End Source File
# Begin Source File

SOURCE=.\dlldatax.c
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\FeatureInMemRecordSet.cpp
# End Source File
# Begin Source File

SOURCE=.\OKSInMemRecordSet.cpp
# End Source File
# Begin Source File

SOURCE=.\RecordsetGenerator.cpp
# End Source File
# Begin Source File

SOURCE=.\RecordsetSource.cpp
# End Source File
# Begin Source File

SOURCE=.\ScaleHeader.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Strings.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASGM.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASGM.def
# End Source File
# Begin Source File

SOURCE=.\TRiASGM.idl

!IF  "$(CFG)" == "TRiASGM - Win32 Debug"

# Begin Custom Build - Performing MIDL step
InputPath=.\TRiASGM.idl

BuildCmds= \
	midl /Oicf /h "TRiASGM.h" /iid "TRiASGM_i.c" "TRiASGM.idl"

".\TRiASGM.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TRiASGM.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TRiASGM_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASGM - Win32 Release MinSize"

# Begin Custom Build - Performing MIDL step
InputPath=.\TRiASGM.idl

BuildCmds= \
	midl /Oicf /h "TRiASGM.h" /iid "TRiASGM_i.c" "TRiASGM.idl"

".\TRiASGM.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TRiASGM.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TRiASGM_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TRiASGM.rc

!IF  "$(CFG)" == "TRiASGM - Win32 Debug"

!ELSEIF  "$(CFG)" == "TRiASGM - Win32 Release MinSize"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TRiASSourceInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASVisInfoObj.cpp
# End Source File
# Begin Source File

SOURCE=.\ViewRecordsetGenerator.cpp
# End Source File
# Begin Source File

SOURCE=.\VisInfo.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CssHeader.h
# End Source File
# Begin Source File

SOURCE=.\dlldatax.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\FeatureInMemRecordset.h
# End Source File
# Begin Source File

SOURCE=.\OKSInMemRecordSet.h
# End Source File
# Begin Source File

SOURCE=.\RecordsetGenerator.h
# End Source File
# Begin Source File

SOURCE=.\RecordsetSource.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\ScaleHeader.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\StreamHelper.h
# End Source File
# Begin Source File

SOURCE=.\Strings.h
# End Source File
# Begin Source File

SOURCE=.\TRiASSourceInfo.h
# End Source File
# Begin Source File

SOURCE=.\TRiASVisInfoObj.h
# End Source File
# Begin Source File

SOURCE=.\ViewRecordsetGenerator.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "Versioning"

# PROP Default_Filter "*.mak;*.tpl"
# Begin Source File

SOURCE=.\TRiASGM.tpl
USERDEP__TRIAS="Version.mak"	

!IF  "$(CFG)" == "TRiASGM - Win32 Debug"

# Begin Custom Build - Generating version information ...
InputPath=.\TRiASGM.tpl

"TRiASGM.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake /nologo /f version.mak TRiASGM.def

# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASGM - Win32 Release MinSize"

# Begin Custom Build - Generating version information ...
InputPath=.\TRiASGM.tpl

"TRiASGM.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake /nologo /f version.mak TRiASGM.def

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TRiASGMv.Tpl
USERDEP__TRIASG="Version.mak"	

!IF  "$(CFG)" == "TRiASGM - Win32 Debug"

# Begin Custom Build - Generating version information ...
InputPath=.\TRiASGMv.Tpl

"TRiASGM.Rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake /nologo /f version.mak TRiASGM.Rcv

# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASGM - Win32 Release MinSize"

# Begin Custom Build - Generating version information ...
InputPath=.\TRiASGMv.Tpl

"TRiASGM.Rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake /nologo /f version.mak TRiASGM.Rcv

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Version.mak
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Version.tpl
USERDEP__VERSI="Version.mak"	

!IF  "$(CFG)" == "TRiASGM - Win32 Debug"

# Begin Custom Build - Generating version information ...
InputPath=.\Version.tpl

"version.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake /nologo /f version.mak version.h

# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASGM - Win32 Release MinSize"

# Begin Custom Build - Generating version information ...
InputPath=.\Version.tpl

"version.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake /nologo /f version.mak version.h

# End Custom Build

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
