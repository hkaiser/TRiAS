# Microsoft Developer Studio Project File - Name="bnaimp" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=bnaimp - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "bnaimp.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "bnaimp.mak" CFG="bnaimp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "bnaimp - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "bnaimp - Win32 Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/TRiAS/TRiAS/Importfilter/PolyGIS BNA", HQKBAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "bnaimp - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "MSWIND" /D "_WINDOWS" /D "WIN32" /Yu"bnaimpp.hpp" /FD /GZ /c
# ADD MTL /nologo /D "_DEBUG" /Oicf
# SUBTRACT MTL /mktyplib203
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 Ixtatd50.lib tfrm32d.lib cont50d.lib ospace5d.lib delayimp.lib winmm.lib kernel32.lib gdi32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"Debug/bnaimpd.ext"
# Begin Custom Build - Copying Target to Destination ...
TargetDir=.\Debug
TargetPath=.\Debug\bnaimpd.ext
TargetName=bnaimpd
InputPath=.\Debug\bnaimpd.ext
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(TRIASDIR_D) 
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_D) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "bnaimp - Win32 Release MinSize"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMinSize"
# PROP BASE Intermediate_Dir "ReleaseMinSize"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /Zi /O1 /D "NDEBUG" /D "MSWIND" /D "_WINDOWS" /D "WIN32" /Yu"bnaimpp.hpp" /FD /c
# ADD MTL /nologo /D "NDEBUG" /Oicf
# SUBTRACT MTL /mktyplib203
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 Ixtatr50.lib tfrmwork.lib containr.lib ospace5r.lib delayimp.lib winmm.lib kernel32.lib gdi32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:".\Release/bnaimp.ext"
# Begin Custom Build - Die Registrierung wird durchgeführt
TargetDir=.\Release
TargetPath=.\Release\bnaimp.ext
TargetName=bnaimp
InputPath=.\Release\bnaimp.ext
SOURCE="$(InputPath)"

"$(TRIASDIR_R)\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(TRIASDIR_R) 
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_R) 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "bnaimp - Win32 Debug"
# Name "bnaimp - Win32 Release MinSize"
# Begin Group "Quellcodedateien"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AssociateLayersToClasses.cpp
# End Source File
# Begin Source File

SOURCE=.\BNAConfigDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\bnaimp.cpp

!IF  "$(CFG)" == "bnaimp - Win32 Debug"

# ADD CPP /Yu

!ELSEIF  "$(CFG)" == "bnaimp - Win32 Release MinSize"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\bnaimp.def
# End Source File
# Begin Source File

SOURCE=.\bnaimp.idl

!IF  "$(CFG)" == "bnaimp - Win32 Debug"

# ADD MTL /nologo /tlb "bnaimp.tlb" /h "bnaimp.h" /iid "bnaimp_i.c" /Oicf
# SUBTRACT MTL /mktyplib203

!ELSEIF  "$(CFG)" == "bnaimp - Win32 Release MinSize"

# ADD MTL /tlb "bnaimp.tlb" /h "bnaimp.h" /iid "bnaimp_i.c"
# SUBTRACT MTL /mktyplib203

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\bnaimp.rc
# End Source File
# Begin Source File

SOURCE=.\bnaimpif.CPP
# End Source File
# Begin Source File

SOURCE=.\BNAImportConfig.cpp
# End Source File
# Begin Source File

SOURCE=.\bnaimpp.CPP
# ADD CPP /Yc"bnaimpp.hpp"
# End Source File
# Begin Source File

SOURCE=.\bnalic.cpp
# End Source File
# Begin Source File

SOURCE=.\BNAProgressDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DATLayer.cpp
# End Source File
# Begin Source File

SOURCE=.\InPlaceCombo.cpp
# End Source File
# Begin Source File

SOURCE=.\RELCONT.CPP
# End Source File
# Begin Source File

SOURCE=.\relkey.cpp
# End Source File
# Begin Source File

SOURCE=.\result.cpp
# End Source File
# Begin Source File

SOURCE=.\status.cpp
# End Source File
# End Group
# Begin Group "Header-Dateien"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AssociateLayersToClasses.h
# End Source File
# Begin Source File

SOURCE=.\AutoBuildCount.h
# End Source File
# Begin Source File

SOURCE=.\BNAConfigDlg.h
# End Source File
# Begin Source File

SOURCE=.\bnaerrs.H
# End Source File
# Begin Source File

SOURCE=.\bnaguids.h
# End Source File
# Begin Source File

SOURCE=.\bnaimp.h
# End Source File
# Begin Source File

SOURCE=.\bnaimp.HPP
# End Source File
# Begin Source File

SOURCE=.\bnaImpConfig.h
# End Source File
# Begin Source File

SOURCE=.\bnaimpif.HPP
# End Source File
# Begin Source File

SOURCE=.\BNAImportConfig.h
# End Source File
# Begin Source File

SOURCE=.\bnaimpp.HPP
# End Source File
# Begin Source File

SOURCE=.\bnapars.h
# End Source File
# Begin Source File

SOURCE=.\BNAProgressDlg.h
# End Source File
# Begin Source File

SOURCE=.\INPUT.H
# End Source File
# Begin Source File

SOURCE=.\RELCONT.HPP
# End Source File
# Begin Source File

SOURCE=.\relkey.HXX
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\result.hxx
# End Source File
# Begin Source File

SOURCE=.\status.hxx
# End Source File
# Begin Source File

SOURCE=.\version.h
# End Source File
# End Group
# Begin Group "Ressourcendateien"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Res\bnaimp.ico
# End Source File
# Begin Source File

SOURCE=.\BNAImportConfig.rgs
# End Source File
# Begin Source File

SOURCE=.\Res\Chckmark.bmp
# End Source File
# Begin Source File

SOURCE=.\DATImportConfig.rgs
# End Source File
# Begin Source File

SOURCE=.\Res\plft_lar.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\PolyGISFeature.rgs
# End Source File
# Begin Source File

SOURCE=.\Res\Search.avi
# End Source File
# End Group
# Begin Group "Versioning"

# PROP Default_Filter "*.tpl,*.mak"
# Begin Source File

SOURCE=.\bnaimp.TPL

!IF  "$(CFG)" == "bnaimp - Win32 Debug"

USERDEP__BNAIM="makefile"	
# Begin Custom Build
InputPath=.\bnaimp.TPL

"bnaimp.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f makefile bnaimp.def

# End Custom Build

!ELSEIF  "$(CFG)" == "bnaimp - Win32 Release MinSize"

USERDEP__BNAIM="makefile"	
# Begin Custom Build
InputPath=.\bnaimp.TPL

"bnaimp.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f makefile bnaimp.def

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\bnaimpv.tpl

!IF  "$(CFG)" == "bnaimp - Win32 Debug"

USERDEP__BNAIMP="makefile"	
# Begin Custom Build
InputPath=.\bnaimpv.tpl

"bnaimp.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f makefile bnaimp.rcv

# End Custom Build

!ELSEIF  "$(CFG)" == "bnaimp - Win32 Release MinSize"

USERDEP__BNAIMP="makefile"	
# Begin Custom Build
InputPath=.\bnaimpv.tpl

"bnaimp.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f makefile bnaimp.rcv

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MAKEFILE
# End Source File
# Begin Source File

SOURCE=.\VERSION.TPL

!IF  "$(CFG)" == "bnaimp - Win32 Debug"

USERDEP__VERSI="makefile"	
# Begin Custom Build
InputPath=.\VERSION.TPL

"version.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f makefile version.h

# End Custom Build

!ELSEIF  "$(CFG)" == "bnaimp - Win32 Release MinSize"

USERDEP__VERSI="makefile"	
# Begin Custom Build
InputPath=.\VERSION.TPL

"version.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f makefile version.h

# End Custom Build

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
