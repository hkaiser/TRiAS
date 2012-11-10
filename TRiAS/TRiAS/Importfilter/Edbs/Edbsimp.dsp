# Microsoft Developer Studio Project File - Name="Edbsimp" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=Edbsimp - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Edbsimp.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Edbsimp.mak" CFG="Edbsimp - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Edbsimp - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Edbsimp - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/TRiAS/TRiAS/Importfilter/Edbs", WREAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Edbsimp - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\WinRel"
# PROP BASE Intermediate_Dir ".\WinRel"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\WinRel"
# PROP Intermediate_Dir ".\WinRel"
# PROP Ignore_Export_Lib 0
F90=fl32.exe
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ixtmfr50.lib containr.lib tfrmwork.lib ospace5r.lib delayimp.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:".\WinRel\Edbsimp.ext" /delayload:crp32dll.dll /delayload:ole32.dll /delayload:oleaut32.dll
# Begin Custom Build - Copying target to destination ...
OutDir=.\WinRel
TargetPath=.\WinRel\Edbsimp.ext
TargetName=Edbsimp
InputPath=.\WinRel\Edbsimp.ext
SOURCE="$(InputPath)"

"$(TRIASDIR_R)\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(TargetPath) $(TRIASDIR_R) 
	xcopy /F $(OutDir)\$(TargetName).pdb $(TRIASDIR_R) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Edbsimp - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\WinDebug"
# PROP BASE Intermediate_Dir ".\WinDebug"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\WinDebug"
# PROP Intermediate_Dir ".\WinDebug"
# PROP Ignore_Export_Lib 0
F90=fl32.exe
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Fr /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 ixtmfd50.lib cont50d.lib tfrm32d.lib stdstr5d.lib OSpace5d.lib delayimp.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:".\WinDebug\Edbsimpd.ext" /delayload:crp32dll.dll /delayload:ole32.dll /delayload:oleaut32.dll
# SUBTRACT LINK32 /map /nodefaultlib
# Begin Custom Build - Copying target to destination ...
OutDir=.\WinDebug
TargetPath=.\WinDebug\Edbsimpd.ext
TargetName=Edbsimpd
InputPath=.\WinDebug\Edbsimpd.ext
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(TargetPath) $(TRIASDIR_D) 
	xcopy /F $(OutDir)\$(TargetName).pdb $(TRIASDIR_D) 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "Edbsimp - Win32 Release"
# Name "Edbsimp - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\ATKISSAT.CPP
# End Source File
# Begin Source File

SOURCE=.\Cwc.cxx
# End Source File
# Begin Source File

SOURCE=.\CXSTRING.CPP
# End Source File
# Begin Source File

SOURCE=.\EDBS.CPP
# End Source File
# Begin Source File

SOURCE=.\WIN32\EDBSIMP.DEF
# End Source File
# Begin Source File

SOURCE=.\EDBSSATZ.CPP
# End Source File
# Begin Source File

SOURCE=.\EDITMERK.CPP
# End Source File
# Begin Source File

SOURCE=.\GEOOBJ.CPP
# End Source File
# Begin Source File

SOURCE=.\IMPORT.CPP
# End Source File
# Begin Source File

SOURCE=.\KOORPAAR.CPP
# End Source File
# Begin Source File

SOURCE=.\Licenz.cpp
# End Source File
# Begin Source File

SOURCE=.\LINIE.CPP
# End Source File
# Begin Source File

SOURCE=.\OBJPOOL.CPP
# End Source File
# Begin Source File

SOURCE=.\STDAFX.CPP
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\STRUTIL.CXX
# End Source File
# Begin Source File

SOURCE=.\TRIF.CPP
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\Atkissat.h
# End Source File
# Begin Source File

SOURCE=.\bool.h
# End Source File
# Begin Source File

SOURCE=.\CWC.H
# End Source File
# Begin Source File

SOURCE=.\CXSTRING.H
# End Source File
# Begin Source File

SOURCE=.\EDBS.HPP
# End Source File
# Begin Source File

SOURCE=.\EDBSGUID.H
# End Source File
# Begin Source File

SOURCE=.\EdbsImpConfig.h
# End Source File
# Begin Source File

SOURCE=.\EDBSSATZ.H
# End Source File
# Begin Source File

SOURCE=.\EDITMERK.H
# End Source File
# Begin Source File

SOURCE=.\GEOOBJ.HPP
# End Source File
# Begin Source File

SOURCE=.\Import.hpp
# End Source File
# Begin Source File

SOURCE=.\KOORPAAR.H
# End Source File
# Begin Source File

SOURCE=.\Linie.h
# End Source File
# Begin Source File

SOURCE=.\OBJPOOL.HPP
# End Source File
# Begin Source File

SOURCE=.\Stdafx.h
# End Source File
# Begin Source File

SOURCE=.\TRIF.HPP
# End Source File
# Begin Source File

SOURCE=.\VERSIO16.H
# End Source File
# Begin Source File

SOURCE=.\VERSIO32.H
# End Source File
# Begin Source File

SOURCE=.\Version.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\edbs.ini
# End Source File
# Begin Source File

SOURCE=.\Edbs.rc
# End Source File
# End Group
# Begin Group "Versioning"

# PROP Default_Filter "*.mak,*.tpl"
# Begin Source File

SOURCE=.\EdbsImp.tpl

!IF  "$(CFG)" == "Edbsimp - Win32 Release"

USERDEP__EDBSI="Version.mak"	
# Begin Custom Build
InputPath=.\EdbsImp.tpl

"EdbsImp.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f Version.mak EdbsImp.def

# End Custom Build

!ELSEIF  "$(CFG)" == "Edbsimp - Win32 Debug"

USERDEP__EDBSI="Version.mak"	
# Begin Custom Build
InputPath=.\EdbsImp.tpl

"EdbsImp.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f Version.mak EdbsImp.def

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\EdbsImpv.tpl

!IF  "$(CFG)" == "Edbsimp - Win32 Release"

USERDEP__EDBSIM="Version.mak"	
# Begin Custom Build
InputPath=.\EdbsImpv.tpl

"EdbsImp.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f Version.mak EdbsImp.rcv

# End Custom Build

!ELSEIF  "$(CFG)" == "Edbsimp - Win32 Debug"

USERDEP__EDBSIM="Version.mak"	
# Begin Custom Build
InputPath=.\EdbsImpv.tpl

"EdbsImp.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f Version.mak EdbsImp.rcv

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\VERSIO32.TPL

!IF  "$(CFG)" == "Edbsimp - Win32 Release"

USERDEP__VERSI="Version.mak"	
# Begin Custom Build
InputPath=.\VERSIO32.TPL

"Versio32.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f Version.mak Versio32.h

# End Custom Build

!ELSEIF  "$(CFG)" == "Edbsimp - Win32 Debug"

USERDEP__VERSI="Version.mak"	
# Begin Custom Build
InputPath=.\VERSIO32.TPL

"Versio32.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f Version.mak Versio32.h

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Version.mak
# End Source File
# End Group
# Begin Group "Obsolete Files"

# PROP Default_Filter ""
# Begin Group "Obsolete Sources"

# PROP Default_Filter "*.cpp"
# Begin Group "Config Dialog Sources"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=.\ACTDIA.CPP
# End Source File
# Begin Source File

SOURCE=.\ARTDIA.CPP
# End Source File
# Begin Source File

SOURCE=.\ATTRDIA.CPP
# End Source File
# Begin Source File

SOURCE=.\DEFMM.CPP
# End Source File
# Begin Source File

SOURCE=.\SETUPDLG.CPP
# End Source File
# Begin Source File

SOURCE=.\TRIDDIA.CPP
# End Source File
# Begin Source File

SOURCE=.\TRMMDIA.CPP
# End Source File
# End Group
# Begin Source File

SOURCE=.\REGELN.CPP
# End Source File
# End Group
# Begin Group "Obsolete Headers"

# PROP Default_Filter "*.h"
# Begin Group "Config Dialog Headers"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=.\ACTDIA.HPP
# End Source File
# Begin Source File

SOURCE=.\ARTDIA.HPP
# End Source File
# Begin Source File

SOURCE=.\ATTRDIA.HPP
# End Source File
# Begin Source File

SOURCE=.\DEFMM.HPP
# End Source File
# Begin Source File

SOURCE=.\SETUPDLG.HPP
# End Source File
# Begin Source File

SOURCE=.\TRIDDIA.HPP
# End Source File
# Begin Source File

SOURCE=.\TRMMDIA.HPP
# End Source File
# End Group
# Begin Source File

SOURCE=.\REGELN.HPP
# End Source File
# End Group
# End Group
# End Target
# End Project
