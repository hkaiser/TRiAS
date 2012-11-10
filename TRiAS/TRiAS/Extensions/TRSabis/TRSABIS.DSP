# Microsoft Developer Studio Project File - Name="TRSABIS" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=TRSABIS - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TRSABIS.MAK".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TRSABIS.MAK" CFG="TRSABIS - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TRSABIS - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "TRSABIS - Win32 Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/TRiAS/TRiAS/Extensions/TRSabis", RKSAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TRSABIS - Win32 Debug"

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
F90=fl32.exe
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXEXT" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /out:"Debug/TRSABISd.ext" /pdbtype:sept
# Begin Custom Build - Copying target to destination ...
TargetDir=.\Debug
TargetPath=.\Debug\TRSABISd.ext
TargetName=TRSABISd
InputPath=.\Debug\TRSABISd.ext
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(TargetPath) $(TRIASDIR_D) 
	xcopy /F $(TargetDir)\TRSABISd.pdb $(TRIASDIR_D) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "TRSABIS - Win32 Release MinSize"

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
F90=fl32.exe
# ADD BASE CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /Zi /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXEXT" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /out:"ReleaseMinSize/TRSABIS.ext"
# Begin Custom Build - Registering ActiveX Control...
TargetDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\TRSABIS.ext
TargetName=TRSABIS
InputPath=.\ReleaseMinSize\TRSABIS.ext
SOURCE="$(InputPath)"

"$(TRIASDIR_R)\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(TargetPath) $(TRIASDIR_R) 
	xcopy /F $(TargetDir)\TRSABIS.pdb $(TRIASDIR_R) 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "TRSABIS - Win32 Debug"
# Name "TRSABIS - Win32 Release MinSize"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Interface definitions"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\idl\ChildWindow.idl
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\TRSABIS.idl

!IF  "$(CFG)" == "TRSABIS - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Performing MIDL step
InputPath=.\TRSABIS.idl

BuildCmds= \
	midl /Oicf /h "TRSABIS.h" /iid "TRSABIS_i.c" "TRSABIS.idl"

".\TRSABIS.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TRSABIS.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TRSABIS_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TRSABIS - Win32 Release MinSize"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Performing MIDL step
InputPath=.\TRSABIS.idl

BuildCmds= \
	midl /Oicf /h "TRSABIS.h" /iid "TRSABIS_i.c" "TRSABIS.idl"

".\TRSABIS.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TRSABIS.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TRSABIS_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Simple Child Sources"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\SabisChildWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASChild.cpp
# End Source File
# End Group
# Begin Group "Tab Child Sources"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MkSABiSTabChildWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\SabisTabChildWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\SABiSTabChildWindowCallback.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASTabChild.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\DummyUIOwner.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TRSABIS.def
# End Source File
# Begin Source File

SOURCE=.\TrSabisExt.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "Simple Child Headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\SabisChildWindow.h
# End Source File
# Begin Source File

SOURCE=.\TRiASChild.h
# End Source File
# End Group
# Begin Group "Tab Child Headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MkSABiSTabChildWindow.h
# End Source File
# Begin Source File

SOURCE=.\SabisTabChildWindow.h
# End Source File
# Begin Source File

SOURCE=.\SABiSTabChildWindowCallback.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\DummyUIOwner.h
# End Source File
# Begin Source File

SOURCE=.\macros.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TRiASTabChild.h
# End Source File
# Begin Source File

SOURCE=.\TrSabisExt.h
# End Source File
# Begin Source File

SOURCE=.\version.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\sabis.ico
# End Source File
# Begin Source File

SOURCE=.\TRSABIS.rc
# End Source File
# End Group
# Begin Group "Versioning"

# PROP Default_Filter "*.tpl;*.mak"
# Begin Source File

SOURCE=.\TrSabis.tpl

!IF  "$(CFG)" == "TRSABIS - Win32 Debug"

USERDEP__TRSAB="TrSabis16.mak"	
# Begin Custom Build - Generieren der Versionsinformation ...
InputPath=.\TrSabis.tpl

"TrSabis.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f TrSabis16.mak TrSabis.def

# End Custom Build

!ELSEIF  "$(CFG)" == "TRSABIS - Win32 Release MinSize"

USERDEP__TRSAB="TrSabis16.mak"	
# Begin Custom Build - Generieren der Versionsinformation ...
InputPath=.\TrSabis.tpl

"TrSabis.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f TrSabis16.mak TrSabis.def

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TrSabis16.MAK
# End Source File
# Begin Source File

SOURCE=.\trsabisv.tpl

!IF  "$(CFG)" == "TRSABIS - Win32 Debug"

USERDEP__TRSABI="TrSabis16.mak"	
# Begin Custom Build - Generieren der Versionsinformation ...
InputPath=.\trsabisv.tpl

"TrSabis.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f TrSabis16.mak TrSabis.rcv

# End Custom Build

!ELSEIF  "$(CFG)" == "TRSABIS - Win32 Release MinSize"

USERDEP__TRSABI="TrSabis16.mak"	
# Begin Custom Build - Generieren der Versionsinformation ...
InputPath=.\trsabisv.tpl

"TrSabis.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f TrSabis16.mak TrSabis.rcv

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Version.Tpl

!IF  "$(CFG)" == "TRSABIS - Win32 Debug"

USERDEP__VERSI="TrSabis16.mak"	
# Begin Custom Build - Generieren der Versionsinformation ...
InputPath=.\Version.Tpl

"Version.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f TrSabis16.mak Version.h

# End Custom Build

!ELSEIF  "$(CFG)" == "TRSABIS - Win32 Release MinSize"

USERDEP__VERSI="TrSabis16.mak"	
# Begin Custom Build - Generieren der Versionsinformation ...
InputPath=.\Version.Tpl

"Version.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f TrSabis16.mak Version.h

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Registry Scripts"

# PROP Default_Filter "*.rgs"
# Begin Source File

SOURCE=.\DummyUIOwner.rgs
# End Source File
# Begin Source File

SOURCE=.\MkSABiSTabChildWindow.rgs
# End Source File
# Begin Source File

SOURCE=.\SabisChildWindow.rgs
# End Source File
# End Group
# End Target
# End Project
