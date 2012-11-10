# Microsoft Developer Studio Project File - Name="ObjMan" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=ObjMan - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Objman.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Objman.mak" CFG="ObjMan - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ObjMan - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ObjMan - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ObjMan - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ospace5r.lib /nologo /subsystem:windows /dll /debug /machine:I386
# Begin Custom Build - Copying target to destination ...
TargetDir=.\Release
TargetPath=.\Release\Objman.dll
TargetName=Objman
InputPath=.\Release\Objman.dll
SOURCE="$(InputPath)"

"$(TRIASDIR_R)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(TargetPath) $(TRIASDIR_R) 
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_R) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "ObjMan - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GR /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 ospace5d.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:".\Debug\Objmand.dll"
# SUBTRACT LINK32 /pdb:none /incremental:no
# Begin Custom Build - Copying target to destination ...
TargetDir=.\Debug
TargetPath=.\Debug\Objmand.dll
TargetName=Objmand
InputPath=.\Debug\Objmand.dll
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(TargetPath)" $(TRIASDIR_D) 
	copy "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_D) 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "ObjMan - Win32 Release"
# Name "ObjMan - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\enumex.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjMan.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjMan.def
# End Source File
# Begin Source File

SOURCE=.\Objman.idl

!IF  "$(CFG)" == "ObjMan - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Running MIDL ...
InputPath=.\Objman.idl

BuildCmds= \
	midl /Oicf /h "iobjman.h" /iid "objman_i.c" /I c:\Msdev5\vc\include         "ObjMan.idl"

"iobjman.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"iobjman_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "ObjMan - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Running MIDL ...
InputPath=.\Objman.idl

BuildCmds= \
	midl /Oicf /h "iobjman.h" /iid "objman_i.c"  "ObjMan.idl" \
	copy iobjman.h $(TRIASINCLUDE) \
	copy objman_i.c $(TRIASINCLUDE) \
	

"$(TRIASINCLUDE)\iobjman.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(TRIASINCLUDE)\objman_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ObjMan.rc
# End Source File
# Begin Source File

SOURCE=.\ObjMn.cpp
# End Source File
# Begin Source File

SOURCE=.\Oleitcon.cpp
# End Source File
# Begin Source File

SOURCE=.\Perstor.cpp
# End Source File
# Begin Source File

SOURCE=.\Perstr.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\timedlg.cpp
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\DLLDATAX.H
# End Source File
# Begin Source File

SOURCE=.\Enumex.h
# End Source File
# Begin Source File

SOURCE=.\Iobjmex.h
# End Source File
# Begin Source File

SOURCE=.\Macrguid.h
# End Source File
# Begin Source File

SOURCE=.\Objmanguid.h
# End Source File
# Begin Source File

SOURCE=.\Objmn.h
# End Source File
# Begin Source File

SOURCE=.\Stdafx.h
# End Source File
# Begin Source File

SOURCE=.\timedlg.h
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Objman.tlb
# End Source File
# End Group
# Begin Group "Registry Scripts"

# PROP Default_Filter "*.rgs"
# Begin Source File

SOURCE=.\objman.rgs
# End Source File
# End Group
# Begin Group "Versioning"

# PROP Default_Filter "*.mak;*.tpl"
# Begin Source File

SOURCE=.\Objman.tpl

!IF  "$(CFG)" == "ObjMan - Win32 Release"

USERDEP__OBJMA="objman16.mak"	
# Begin Custom Build
InputPath=.\Objman.tpl

"objman.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f objman16.mak objman.def

# End Custom Build

!ELSEIF  "$(CFG)" == "ObjMan - Win32 Debug"

USERDEP__OBJMA="objman16.mak"	
# Begin Custom Build
InputPath=.\Objman.tpl

"objman.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f objman16.mak objman.def

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Objman16.mak
# End Source File
# Begin Source File

SOURCE=.\objmanv.tpl

!IF  "$(CFG)" == "ObjMan - Win32 Release"

USERDEP__OBJMAN="objman16.mak"	
# Begin Custom Build
InputPath=.\objmanv.tpl

"objman.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f objman16.mak objman.rcv

# End Custom Build

!ELSEIF  "$(CFG)" == "ObjMan - Win32 Debug"

USERDEP__OBJMAN="objman16.mak"	
# Begin Custom Build
InputPath=.\objmanv.tpl

"objman.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f objman16.mak objman.rcv

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Versio32.tpl

!IF  "$(CFG)" == "ObjMan - Win32 Release"

USERDEP__VERSI="objman16.mak"	
# Begin Custom Build
InputPath=.\Versio32.tpl

"versio32.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f objman16.mak versio32.h

# End Custom Build

!ELSEIF  "$(CFG)" == "ObjMan - Win32 Debug"

USERDEP__VERSI="objman16.mak"	
# Begin Custom Build
InputPath=.\Versio32.tpl

"versio32.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f objman16.mak versio32.h

# End Custom Build

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
