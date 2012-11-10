# Microsoft Developer Studio Project File - Name="MsgBlast" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=MsgBlast - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Msgblast.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Msgblast.mak" CFG="MsgBlast - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MsgBlast - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MsgBlast - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MsgBlast - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\WinRel"
# PROP BASE Intermediate_Dir ".\WinRel"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\WinRel"
# PROP Intermediate_Dir ".\WinRel"
# PROP Ignore_Export_Lib 0
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "EBWIN32" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D "WIN32" /D "_WINDOWS" /D "__MFC__" /D "_MBCS" /D "_AFXEXT" /D "_AFXDLL" /D "_WINDLL" /D "OS_WIN_95" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D "OS_NO_ALLOCATORS" /D "QI_EXCEPTION" /D "_ATL_NEW_CCOMSTRUCT" /Yu"StdAfx.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 Ixtmar50.lib TriasTlb.lib ospace5r.lib ebn.lib /nologo /subsystem:windows /dll /machine:I386 /out:".\WinRel\MsgBlast.ext"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "MsgBlast - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\WinDebug"
# PROP BASE Intermediate_Dir ".\WinDebug"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\WinDebug"
# PROP Intermediate_Dir ".\WinDebug"
# PROP Ignore_Export_Lib 0
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "EBWIN32" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D "WIN32" /D "_WINDOWS" /D "__MFC__" /D "_MBCS" /D "_AFXEXT" /D "_AFXDLL" /D "_WINDLL" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D "OS_NO_ALLOCATORS" /D "QI_EXCEPTION" /D "_ATL_NEW_CCOMSTRUCT" /FR /Yu"StdAfx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 Ixtmad50.lib TriasTld.lib ospace5d.lib ebn.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:".\WinDebug\MsgBlstd.ext"
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying target to destination ...
TargetDir=.\WinDebug
TargetPath=.\WinDebug\MsgBlstd.ext
TargetName=MsgBlstd
InputPath=.\WinDebug\MsgBlstd.ext
SOURCE=$(InputPath)

"$(TRIASDIR_D)\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(TargetPath) $(TRIASDIR_D) 
	copy $(TargetDir)\MsgBlstd.pdb $(TRIASDIR_D) 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "MsgBlast - Win32 Release"
# Name "MsgBlast - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\Jumptab.cpp
# End Source File
# Begin Source File

SOURCE=.\MouseAction.cpp
# End Source File
# Begin Source File

SOURCE=.\MsgBlast.CXX
# End Source File
# Begin Source File

SOURCE=.\MsgBlast.DEF
# End Source File
# Begin Source File

SOURCE=.\MsgBlast.idl

!IF  "$(CFG)" == "MsgBlast - Win32 Release"

# Begin Custom Build - Performing MIDL step
InputPath=.\MsgBlast.idl

BuildCmds= \
	midl /Oicf /h "MsgBlast.h" /iid "MsgBlast_i.c" "MsgBlast.idl"

".\MsgBlast.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\MsgBlast.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\MsgBlast_.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "MsgBlast - Win32 Debug"

# Begin Custom Build - Performing MIDL step
InputPath=.\MsgBlast.idl

BuildCmds= \
	midl /Oicf /h "MsgBlast.h" /iid "MsgBlast_i.c" "MsgBlast.idl"

".\MsgBlast.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\MsgBlast.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\MsgBlast_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MsgBlast.RC
# End Source File
# Begin Source File

SOURCE=.\MsgBlastExt.cpp
# End Source File
# Begin Source File

SOURCE=.\MsgMap.cpp
# End Source File
# Begin Source File

SOURCE=.\STDAFX.CPP
# ADD CPP /Yc"StdAfx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\jumptab.h
# End Source File
# Begin Source File

SOURCE=.\MouseAction.h
# End Source File
# Begin Source File

SOURCE=.\MsgBlast.h
# End Source File
# Begin Source File

SOURCE=.\MSGBLAST.HXX
# End Source File
# Begin Source File

SOURCE=.\MsgBlastExt.h
# End Source File
# Begin Source File

SOURCE=.\Msgguid.h
# End Source File
# Begin Source File

SOURCE=.\MsgMap.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\VERSION.H
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Res\MsgBlast.rcp
# End Source File
# Begin Source File

SOURCE=.\MsgBlast.RCV
# End Source File
# Begin Source File

SOURCE=.\MsgBlast.tlb
# End Source File
# End Group
# Begin Group "Registry Scripts"

# PROP Default_Filter "*.rgs"
# Begin Source File

SOURCE=.\MouseAction.rgs
# End Source File
# Begin Source File

SOURCE=.\Res\MsgMap.Rgs
# End Source File
# End Group
# Begin Group "Versioning"

# PROP Default_Filter "*.tpl;*.mak"
# Begin Source File

SOURCE=.\MSGBLAST.TPL
USERDEP__MSGBL="MsgBls16.mak"	

!IF  "$(CFG)" == "MsgBlast - Win32 Release"

# Begin Custom Build - Generating versioning information ...
InputPath=.\MSGBLAST.TPL

"msgblast.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f msgbls16.mak msgblast.def

# End Custom Build

!ELSEIF  "$(CFG)" == "MsgBlast - Win32 Debug"

# Begin Custom Build - Generating versioning information ...
InputPath=.\MSGBLAST.TPL

"msgblast.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f msgbls16.mak msgblast.def

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MSGBLS16.MAK
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\msgblstv.tpl
USERDEP__MSGBLS="MsgBls16.mak"	

!IF  "$(CFG)" == "MsgBlast - Win32 Release"

# Begin Custom Build - Generating versioning information ...
InputPath=.\msgblstv.tpl

"msgblast.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f msgbls16.mak msgblast.rcv

# End Custom Build

!ELSEIF  "$(CFG)" == "MsgBlast - Win32 Debug"

# Begin Custom Build - Generating versioning information ...
InputPath=.\msgblstv.tpl

"msgblast.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f msgbls16.mak msgblast.rcv

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\VERSION.TPL
USERDEP__VERSI="MsgBls16.mak"	

!IF  "$(CFG)" == "MsgBlast - Win32 Release"

# Begin Custom Build - Generating versioning information ...
InputPath=.\VERSION.TPL

"version.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f msgbls16.mak version.h

# End Custom Build

!ELSEIF  "$(CFG)" == "MsgBlast - Win32 Debug"

# Begin Custom Build - Generating versioning information ...
InputPath=.\VERSION.TPL

"version.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f msgbls16.mak version.h

# End Custom Build

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
