# Microsoft Developer Studio Project File - Name="Toporel" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=Toporel - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Toporel.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Toporel.mak" CFG="Toporel - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Toporel - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Toporel - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/TRiAS/TRiAS/GeometrieVerarbeitung", LAEAAAAA"
# PROP Scc_LocalPath ".."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Toporel - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\WinRel"
# PROP BASE Intermediate_Dir ".\WinRel"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\WinRel"
# PROP Intermediate_Dir ".\WinRel"
# PROP Ignore_Export_Lib 0
F90=fl32.exe
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /O1 /I "..\z_hxx" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "MSWIND" /D "MSCC8" /Yu"toporelp.hxx" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /i "..\z_hxx" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 geometr.lib ixtatr50.lib ospace5r.lib tfrmwork.lib containr.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib triastlb.lib /nologo /dll /debug /machine:I386 /out:".\WinRel\TopoRel.ext" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying Target to Destination ...
TargetDir=.\WinRel
TargetPath=.\WinRel\TopoRel.ext
TargetName=TopoRel
InputPath=.\WinRel\TopoRel.ext
SOURCE="$(InputPath)"

"$(TRIASDIR_R)\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(TRIASDIR_R) 
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_R) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Toporel - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\WinDebug"
# PROP BASE Intermediate_Dir ".\WinDebug"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
F90=fl32.exe
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /I "..\z_hxx" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "MSWIND" /D "MSCC8" /Fr /Fp".\Debug\TOPORELD.pch" /Yu"toporelp.hxx" /Fd".\Debug\TOPORELD.pdb" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
# SUBTRACT MTL /mktyplib203
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /i "..\z_hxx" /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 geometd.lib ixtatd50.lib ospace5d.lib tfrm32d.lib cont50d.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib triastld.lib /nologo /dll /debug /machine:I386 /out:".\Debug\toporeld.ext" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying Target to Destination ...
TargetDir=.\Debug
TargetPath=.\Debug\toporeld.ext
TargetName=toporeld
InputPath=.\Debug\toporeld.ext
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(TRIASDIR_D) 
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_D) 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "Toporel - Win32 Release"
# Name "Toporel - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\NUMTREE.CXX
# End Source File
# Begin Source File

SOURCE=.\TOPOEXT.CXX
# End Source File
# Begin Source File

SOURCE=.\TOPOREL.CXX
# End Source File
# Begin Source File

SOURCE=.\TOPOREL.DEF
# End Source File
# Begin Source File

SOURCE=.\Toporel.rc
# End Source File
# Begin Source File

SOURCE=.\TopoRelDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\TopoRelFunctions.cpp
# End Source File
# Begin Source File

SOURCE=.\TOPORELP.CXX
# ADD CPP /Yc"toporelp.hxx"
# End Source File
# Begin Source File

SOURCE=.\TopoRelPropAct.cpp
# End Source File
# Begin Source File

SOURCE=.\TopoRelRefDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\Numtree.hxx
# End Source File
# Begin Source File

SOURCE=.\Relkonst.hxx
# End Source File
# Begin Source File

SOURCE=.\Toporel.hxx
# End Source File
# Begin Source File

SOURCE=.\TopoRelConfig.h
# End Source File
# Begin Source File

SOURCE=.\TopoRelDlg.h
# End Source File
# Begin Source File

SOURCE=.\TopoRelFunctions.h
# End Source File
# Begin Source File

SOURCE=.\Toporelm.hxx
# End Source File
# Begin Source File

SOURCE=.\Toporelp.hxx
# End Source File
# Begin Source File

SOURCE=.\TopoRelPropAct.h
# End Source File
# Begin Source File

SOURCE=.\Toporelr.h
# End Source File
# Begin Source File

SOURCE=.\TopoRelRefDlg.h
# End Source File
# Begin Source File

SOURCE=.\Version.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Res\GeoComponentSequence.dtd
# End Source File
# Begin Source File

SOURCE=.\Res\TopologicalAnalysisMain.tlc
# End Source File
# Begin Source File

SOURCE=.\Res\TopologicalAnalysisORWin.tlc
# End Source File
# Begin Source File

SOURCE=.\TopoRelPropAct.rgs
# End Source File
# End Group
# Begin Group "Versioning"

# PROP Default_Filter "*.tpl;*.mak"
# Begin Source File

SOURCE=..\..\TRiASDev.MVC\Include\GeometryVersion.mak
# End Source File
# Begin Source File

SOURCE=.\Makefile
# End Source File
# Begin Source File

SOURCE=.\TOPOREL.TPL

!IF  "$(CFG)" == "Toporel - Win32 Release"

USERDEP__TOPOR="makefile"	"$(TRIASINCLUDE)\GeometryVersion.mak"	
# Begin Custom Build
InputPath=.\TOPOREL.TPL

"toporel.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f makefile toporel.def

# End Custom Build

!ELSEIF  "$(CFG)" == "Toporel - Win32 Debug"

USERDEP__TOPOR="makefile"	"$(TRIASINCLUDE)\GeometryVersion.mak"	
# Begin Custom Build
InputPath=.\TOPOREL.TPL

"toporel.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f makefile toporel.def

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\toporelv.tpl

!IF  "$(CFG)" == "Toporel - Win32 Release"

USERDEP__TOPORE="makefile"	"$(TRIASINCLUDE)\GeometryVersion.mak"	
# Begin Custom Build
InputPath=.\toporelv.tpl

"toporel.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f makefile toporel.rcv

# End Custom Build

!ELSEIF  "$(CFG)" == "Toporel - Win32 Debug"

USERDEP__TOPORE="makefile"	"$(TRIASINCLUDE)\GeometryVersion.mak"	
# Begin Custom Build
InputPath=.\toporelv.tpl

"toporel.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f makefile toporel.rcv

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Version.tpl

!IF  "$(CFG)" == "Toporel - Win32 Release"

USERDEP__VERSI="makefile"	"$(TRIASINCLUDE)\GeometryVersion.mak"	
# Begin Custom Build
InputPath=.\Version.tpl

"version.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f makefile version.h

# End Custom Build

!ELSEIF  "$(CFG)" == "Toporel - Win32 Debug"

USERDEP__VERSI="makefile"	"$(TRIASINCLUDE)\GeometryVersion.mak"	
# Begin Custom Build
InputPath=.\Version.tpl

"version.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f makefile version.h

# End Custom Build

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
