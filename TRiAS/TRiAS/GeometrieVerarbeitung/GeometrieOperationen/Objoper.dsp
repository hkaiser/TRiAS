# Microsoft Developer Studio Project File - Name="Objoper" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=Objoper - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Objoper.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Objoper.mak" CFG="Objoper - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Objoper - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Objoper - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/TRiAS/TRiAS/GeometrieVerarbeitung", LAEAAAAA"
# PROP Scc_LocalPath ".."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Objoper - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\WinRel"
# PROP BASE Intermediate_Dir ".\WinRel"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
F90=fl32.exe
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /O1 /I "..\z_hxx" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "MSWIND" /D "MSCC8" /Yu"objoperp.hxx" /Fd".\Release/ObjOper.pdb" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /Oicf /win32
# SUBTRACT MTL /mktyplib203
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /i "..\Z_HXX" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 geometr.lib ixtatr50.lib tfrmwork.lib containr.lib ospace5r.lib delayimp.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /def:".\OBJOPER.DEF" /out:".\Release\ObjOper.ext" /delayload:crp32dll.dll /delayload:ole32.dll /delayload:oleaut32.dll /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying Target to Destination ...
TargetDir=.\Release
TargetPath=.\Release\ObjOper.ext
TargetName=ObjOper
InputPath=.\Release\ObjOper.ext
SOURCE="$(InputPath)"

"$(TRIASDIR_R)\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(TargetPath) $(TRIASDIR_R) 
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_R) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Objoper - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /ZI /Od /I "..\z_hxx" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "MSWIND" /D "MSCC8" /Fr /Fp".\Debug\OBJOPERD.pch" /Yu"objoperp.hxx" /Fd".\Debug\OBJOPERD.pdb" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /Oicf /win32
# SUBTRACT MTL /mktyplib203
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /i "..\Z_HXX" /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 geometd.lib ixtatd50.lib ospace5d.lib tfrm32d.lib cont50d.lib delayimp.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /def:".\OBJOPER.DEF" /out:".\Debug\objoperd.ext" /delayload:crp32dll.dll /delayload:ole32.dll /delayload:oleaut32.dll /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying Target to Destination ...
TargetDir=.\Debug
TargetPath=.\Debug\objoperd.ext
TargetName=objoperd
InputPath=.\Debug\objoperd.ext
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(TRIASDIR_D) 
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_D) 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "Objoper - Win32 Release"
# Name "Objoper - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\AreaBuildPropAct.cpp
# End Source File
# Begin Source File

SOURCE=.\AreasBuildingDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgFunctions.cpp
# End Source File
# Begin Source File

SOURCE=.\IObjOper.idl
# ADD MTL /tlb "" /h "IObjOper.h" /iid "IObjOper.c" /Oicf
# SUBTRACT MTL /mktyplib203
# End Source File
# Begin Source File

SOURCE=.\License.cpp
# End Source File
# Begin Source File

SOURCE=.\LineSplitPropAct.cpp
# End Source File
# Begin Source File

SOURCE=.\LinesSplittingDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjekteVereinigen.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\ObjOper.cxx
# End Source File
# Begin Source File

SOURCE=.\OBJOPER.DEF
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Objoper.rc
# End Source File
# Begin Source File

SOURCE=.\Objoperi.cxx
# End Source File
# Begin Source File

SOURCE=.\OBJOPERP.CXX
# ADD CPP /Yc"objoperp.hxx"
# End Source File
# Begin Source File

SOURCE=.\Operationen.cxx
# End Source File
# Begin Source File

SOURCE=.\OPEREXT.CXX
# End Source File
# Begin Source File

SOURCE=.\OptionsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionsPropAct.cpp
# End Source File
# Begin Source File

SOURCE=.\PropAct.cpp
# End Source File
# Begin Source File

SOURCE=.\PropSeq.cpp
# End Source File
# Begin Source File

SOURCE=.\RegardOperatDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RegOperatPropAct.cpp
# End Source File
# Begin Source File

SOURCE=.\SetsOperatDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SetsOperatPropAct.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\AreaBuildPropAct.h
# End Source File
# Begin Source File

SOURCE=.\AreasBuildingDlg.h
# End Source File
# Begin Source File

SOURCE=.\DlgFunctions.h
# End Source File
# Begin Source File

SOURCE=.\IObjOper.h
# End Source File
# Begin Source File

SOURCE=.\LineSplitPropAct.h
# End Source File
# Begin Source File

SOURCE=.\LinesSplittingDlg.h
# End Source File
# Begin Source File

SOURCE=.\ObjekteVereinigen.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\ObjOper.hxx
# End Source File
# Begin Source File

SOURCE=.\ObjOperConfig.h
# End Source File
# Begin Source File

SOURCE=.\ObjOperDlg.h
# End Source File
# Begin Source File

SOURCE=.\OBJOPERM.HXX
# End Source File
# Begin Source File

SOURCE=.\Objoperp.hxx
# End Source File
# Begin Source File

SOURCE=.\OBJOPERR.H
# End Source File
# Begin Source File

SOURCE=.\OptionsDlg.h
# End Source File
# Begin Source File

SOURCE=.\OptionsPropAct.h
# End Source File
# Begin Source File

SOURCE=.\PropAct.h
# End Source File
# Begin Source File

SOURCE=.\PropSeq.h
# End Source File
# Begin Source File

SOURCE=.\RegardOperatDlg.h
# End Source File
# Begin Source File

SOURCE=.\RegOperatPropAct.h
# End Source File
# Begin Source File

SOURCE=.\SetsOperatDlg.h
# End Source File
# Begin Source File

SOURCE=.\SetsOperatPropAct.h
# End Source File
# Begin Source File

SOURCE=.\SmartInterfaces.h
# End Source File
# Begin Source File

SOURCE=.\VERSION.H
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\And_reduced.bmp
# End Source File
# Begin Source File

SOURCE=.\Bound.bmp
# End Source File
# Begin Source File

SOURCE=.\Exter.bmp
# End Source File
# Begin Source File

SOURCE=.\Inter.bmp
# End Source File
# Begin Source File

SOURCE=.\Debug\ObjekteVereinigen.ebc
# End Source File
# Begin Source File

SOURCE=.\Release\ObjekteVereinigen.ebc
# End Source File
# Begin Source File

SOURCE=.\WinDebug\ObjekteVereinigen.ebc
# End Source File
# Begin Source File

SOURCE=.\WinRel\ObjekteVereinigen.ebc
# End Source File
# Begin Source File

SOURCE=.\Debug\ObjekteVereinigenBli.ebc
# End Source File
# Begin Source File

SOURCE=.\Release\ObjekteVereinigenBli.ebc
# End Source File
# Begin Source File

SOURCE=.\WinDebug\ObjekteVereinigenBli.ebc
# End Source File
# Begin Source File

SOURCE=.\WinRel\ObjekteVereinigenBli.ebc
# End Source File
# Begin Source File

SOURCE=.\Or.bmp
# End Source File
# Begin Source File

SOURCE=.\Xor_reduced.bmp
# End Source File
# End Group
# Begin Group "Registry Scripts"

# PROP Default_Filter "*.rgs"
# Begin Source File

SOURCE=.\AreaBulidPropAct3.rgs
# End Source File
# Begin Source File

SOURCE=.\LineSplitPropAct3.rgs
# End Source File
# Begin Source File

SOURCE=.\ObjekteVereinigen3.rgs
# End Source File
# Begin Source File

SOURCE=.\OptionsPropAct3.rgs
# End Source File
# Begin Source File

SOURCE=.\RegOperatPropAct3.rgs
# End Source File
# Begin Source File

SOURCE=.\SetsOperatPropAct3.rgs
# End Source File
# End Group
# Begin Group "Basic Scripts"

# PROP Default_Filter "*.ebs"
# Begin Source File

SOURCE=.\ObjekteVereinigen.ebs

!IF  "$(CFG)" == "Objoper - Win32 Release"

# Begin Custom Build - Compiling script $(InputPath) ...
OutDir=.\Release
InputPath=.\ObjekteVereinigen.ebs
InputName=ObjekteVereinigen

"$(OutDir)\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -c -n -o $(OutDir)\$(InputName).ebc -DPROPACT $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "Objoper - Win32 Debug"

# Begin Custom Build - Compiling script $(InputPath) ...
OutDir=.\Debug
InputPath=.\ObjekteVereinigen.ebs
InputName=ObjekteVereinigen

"$(OutDir)\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -n -o $(OutDir)\$(InputName).ebc -DPROPACT $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ObjekteVereinigenBli.ebs
# PROP Exclude_From_Build 1
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

SOURCE=.\OBJOPER.TPL

!IF  "$(CFG)" == "Objoper - Win32 Release"

USERDEP__OBJOP="makefile"	"$(TRIASINCLUDE)\GeometryVersion.mak"	
# Begin Custom Build
InputPath=.\OBJOPER.TPL

"objoper.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f makefile objoper.def

# End Custom Build

!ELSEIF  "$(CFG)" == "Objoper - Win32 Debug"

USERDEP__OBJOP="makefile"	"$(TRIASINCLUDE)\GeometryVersion.mak"	
# Begin Custom Build
InputPath=.\OBJOPER.TPL

"objoper.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f makefile objoper.def

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\objoperv.tpl

!IF  "$(CFG)" == "Objoper - Win32 Release"

USERDEP__OBJOPE="makefile"	"$(TRIASINCLUDE)\GeometryVersion.mak"	
# Begin Custom Build
InputPath=.\objoperv.tpl

"objoper.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f makefile objoper.rcv

# End Custom Build

!ELSEIF  "$(CFG)" == "Objoper - Win32 Debug"

USERDEP__OBJOPE="makefile"	"$(TRIASINCLUDE)\GeometryVersion.mak"	
# Begin Custom Build
InputPath=.\objoperv.tpl

"objoper.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f makefile objoper.rcv

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Version.tpl

!IF  "$(CFG)" == "Objoper - Win32 Release"

USERDEP__VERSI="makefile"	"$(TRIASINCLUDE)\GeometryVersion.mak"	
# Begin Custom Build
InputPath=.\Version.tpl

"version.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f makefile version.h

# End Custom Build

!ELSEIF  "$(CFG)" == "Objoper - Win32 Debug"

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
