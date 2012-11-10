# Microsoft Developer Studio Project File - Name="EdbsAlk" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=EdbsAlk - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "EdbsALK.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "EdbsALK.mak" CFG="EdbsAlk - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "EdbsAlk - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "EdbsAlk - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/", aaaaaaaa"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "EdbsAlk - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\WinRel"
# PROP BASE Intermediate_Dir ".\WinRel"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
F90=fl32.exe
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GR /GX /Zi /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Fr /YX"stdafx.h" /Fd"Release/EdbsAlk.pdb" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ixtmar50.lib containr.lib ospace5r.lib delayimp.lib dunzip32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"Release\EdbsALK.ext" /delayload:comctl32.dll /delayload:ole32.dll /delayload:oleaut32.dll /delayload:dunzip32.dll /delayload:crp32dll.dll
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying target to destination ...
OutDir=.\Release
TargetPath=.\Release\EdbsALK.ext
TargetName=EdbsALK
InputPath=.\Release\EdbsALK.ext
SOURCE="$(InputPath)"

"$(TRIASDIR_R)\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" "$(TRIASDIR_R)" 
	xcopy /F "$(OutDir)\$(TargetName).pdb" "$(TRIASDIR_R)" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "EdbsAlk - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\WinDebug"
# PROP BASE Intermediate_Dir ".\WinDebug"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
F90=fl32.exe
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GR /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Fr /YX"stdafx.h" /Fd"Debug/EdbsAlk.pdb" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 ixtmad50.lib cont50d.lib ospace5d.lib delayimp.lib dunzip32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"Debug\EdbsALKd.ext" /delayload:comctl32.dll /delayload:ole32.dll /delayload:oleaut32.dll /delayload:dunzip32.dll /delayload:crp32dll.dll
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying target to destination ...
TargetDir=.\Debug
TargetPath=.\Debug\EdbsALKd.ext
TargetName=EdbsALKd
InputPath=.\Debug\EdbsALKd.ext
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" "$(TRIASDIR_D)" 
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_D) 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "EdbsAlk - Win32 Release"
# Name "EdbsAlk - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Group "Config Dialog Sources"

# PROP Default_Filter ""
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

SOURCE=.\EDBS_CfgImpCmn.cpp
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

SOURCE=.\ATKISSAT.CPP
# End Source File
# Begin Source File

SOURCE=.\Cfg.cpp
# End Source File
# Begin Source File

SOURCE=.\CfgDb.cpp
# End Source File
# Begin Source File

SOURCE=.\Cwc.cxx
# End Source File
# Begin Source File

SOURCE=.\CXSTRING.CPP
# End Source File
# Begin Source File

SOURCE=.\dynazip.cpp
# End Source File
# Begin Source File

SOURCE=.\EDBS.CPP
# End Source File
# Begin Source File

SOURCE=.\Edbs.rc
# End Source File
# Begin Source File

SOURCE=.\EDBS_Cfg.idl

!IF  "$(CFG)" == "EdbsAlk - Win32 Release"

# PROP Intermediate_Dir "."
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Running MIDL ...
InputPath=.\EDBS_Cfg.idl
InputName=EDBS_Cfg

BuildCmds= \
	midl /Oicf /win32 /tlb "$(InputName).tlb" /h "$(InputName).h" /iid "$(InputName)_i.c" $(InputPath)

"$(InputName).tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "EdbsAlk - Win32 Debug"

# PROP Intermediate_Dir "."
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Running MIDL ...
InputPath=.\EDBS_Cfg.idl
InputName=EDBS_Cfg

BuildCmds= \
	midl /Oicf /win32 /tlb "$(InputName).tlb" /h "$(InputName).h" /iid "$(InputName)_i.c" $(InputPath)

"$(InputName).tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\EDBS_CfgImp.cpp
# End Source File
# Begin Source File

SOURCE=.\EDBS_CfgImpOBAK.cpp
# End Source File
# Begin Source File

SOURCE=.\EDBS_CfgImpObj.cpp
# End Source File
# Begin Source File

SOURCE=.\EdbsAlk.def
# End Source File
# Begin Source File

SOURCE=.\EDBSFO.CPP
# End Source File
# Begin Source File

SOURCE=.\EDBSSATZ.CPP
# End Source File
# Begin Source File

SOURCE=.\EDITMERK.CPP
# End Source File
# Begin Source File

SOURCE=.\GeoCvt.cpp
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

SOURCE=.\ListCtrlObjects.cpp
# End Source File
# Begin Source File

SOURCE=.\MetaData.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjectAttributeTRiAS.cpp
# End Source File
# Begin Source File

SOURCE=.\OBJPOOL.CPP
# End Source File
# Begin Source File

SOURCE=.\Rule_Attr.cpp
# End Source File
# Begin Source File

SOURCE=.\Rule_Geom.cpp
# End Source File
# Begin Source File

SOURCE=.\Rule_Info.cpp
# End Source File
# Begin Source File

SOURCE=.\Rule_Layer.cpp
# End Source File
# Begin Source File

SOURCE=.\Rule_Line.cpp
# End Source File
# Begin Source File

SOURCE=.\Rule_Text.cpp
# End Source File
# Begin Source File

SOURCE=.\Separator.cpp
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
# Begin Group "Config Dialog Headers"

# PROP Default_Filter ""
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

SOURCE=.\EDBS_CfgImpCmn.h
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

SOURCE=.\Atkissat.h
# End Source File
# Begin Source File

SOURCE=.\Cfg.h
# End Source File
# Begin Source File

SOURCE=.\CfgDb.h
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

SOURCE=.\EDBS_Cfg.h
# End Source File
# Begin Source File

SOURCE=.\EDBS_CfgImp.h
# End Source File
# Begin Source File

SOURCE=.\EDBS_CfgImpOBAK.h
# End Source File
# Begin Source File

SOURCE=.\EDBS_CfgImpObj.h
# End Source File
# Begin Source File

SOURCE=.\EdbsAlkConfig.h
# End Source File
# Begin Source File

SOURCE=.\EDBSFO.HPP
# End Source File
# Begin Source File

SOURCE=.\EDBSGUID.H
# End Source File
# Begin Source File

SOURCE=.\EDBSSATZ.H
# End Source File
# Begin Source File

SOURCE=.\EDITMERK.H
# End Source File
# Begin Source File

SOURCE=.\GeoCvt.h
# End Source File
# Begin Source File

SOURCE=.\GEOOBJ.HPP
# End Source File
# Begin Source File

SOURCE=.\KOORPAAR.H
# End Source File
# Begin Source File

SOURCE=.\Linie.h
# End Source File
# Begin Source File

SOURCE=.\ListCtrlObjects.h
# End Source File
# Begin Source File

SOURCE=.\MetaData.h
# End Source File
# Begin Source File

SOURCE=.\ObjectAttributeTRiAS.h
# End Source File
# Begin Source File

SOURCE=.\OBJPOOL.HPP
# End Source File
# Begin Source File

SOURCE=.\Rule_Attr.h
# End Source File
# Begin Source File

SOURCE=.\Rule_Geom.h
# End Source File
# Begin Source File

SOURCE=.\Rule_Info.h
# End Source File
# Begin Source File

SOURCE=.\Rule_Layer.h
# End Source File
# Begin Source File

SOURCE=.\Rule_Line.h
# End Source File
# Begin Source File

SOURCE=.\Rule_Text.h
# End Source File
# Begin Source File

SOURCE=.\Separator.h
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

SOURCE=.\res\buchauf.bmp
# End Source File
# Begin Source File

SOURCE=.\res\buchzu.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Chkboxs.bmp
# End Source File
# Begin Source File

SOURCE=.\EDBS_CfgImp.rgs
# End Source File
# Begin Source File

SOURCE=.\res\Folders.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Scdcncll.ico
# End Source File
# End Group
# Begin Group "Versioning"

# PROP Default_Filter "*.tpl,*.mak"
# Begin Source File

SOURCE=.\EdbsAlk.tpl

!IF  "$(CFG)" == "EdbsAlk - Win32 Release"

USERDEP__EDBSA="Version.mak"	
# Begin Custom Build
InputPath=.\EdbsAlk.tpl

"EdbsAlk.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f Version.mak EdbsAlk.def

# End Custom Build

!ELSEIF  "$(CFG)" == "EdbsAlk - Win32 Debug"

USERDEP__EDBSA="Version.mak"	
# Begin Custom Build
InputPath=.\EdbsAlk.tpl

"EdbsAlk.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f Version.mak EdbsAlk.def

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\EdbsAlkv.tpl

!IF  "$(CFG)" == "EdbsAlk - Win32 Release"

USERDEP__EDBSAL="Version.mak"	
# Begin Custom Build
InputPath=.\EdbsAlkv.tpl

"EdbsAlk.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f Version.mak EdbsAlk.rcv

# End Custom Build

!ELSEIF  "$(CFG)" == "EdbsAlk - Win32 Debug"

USERDEP__EDBSAL="Version.mak"	
# Begin Custom Build
InputPath=.\EdbsAlkv.tpl

"EdbsAlk.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f Version.mak EdbsAlk.rcv

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\VERSIO32.TPL

!IF  "$(CFG)" == "EdbsAlk - Win32 Release"

USERDEP__VERSI="Version.mak"	
# Begin Custom Build
InputPath=.\VERSIO32.TPL

"Versio32.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f Version.mak Versio32.h

# End Custom Build

!ELSEIF  "$(CFG)" == "EdbsAlk - Win32 Debug"

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
# End Target
# End Project
