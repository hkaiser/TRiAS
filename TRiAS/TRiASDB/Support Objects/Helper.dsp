# Microsoft Developer Studio Project File - Name="Helper" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=Helper - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Helper.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Helper.mak" CFG="Helper - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Helper - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Helper - Win32 Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/TRiAS/TRiAS/Support Objects", SOLAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Helper - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ospace5d.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"Debug/Helperd.dll"
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
TargetDir=.\Debug
TargetPath=.\Debug\Helperd.dll
TargetName=Helperd
InputPath=.\Debug\Helperd.dll
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(TargetPath) $(TRIASDIR_D) 
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_D) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Helper - Win32 Release MinSize"

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
# ADD CPP /nologo /MD /W3 /GX /Zi /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ospace5r.lib /nologo /subsystem:windows /dll /debug /machine:I386
# Begin Custom Build
TargetDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\Helper.dll
TargetName=Helper
InputPath=.\ReleaseMinSize\Helper.dll
SOURCE="$(InputPath)"

"$(TRIASDIR_R)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(TargetPath) $(TRIASDIR_R) 
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_R) 
	xcopy /F Helper.h $(TRIASINCLUDE) 
	xcopy /F Helper_i.c $(TRIASINCLUDE) 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "Helper - Win32 Debug"
# Name "Helper - Win32 Release MinSize"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CookieHelper.cpp
# End Source File
# Begin Source File

SOURCE=.\Helper.cpp
# End Source File
# Begin Source File

SOURCE=.\Helper.def
# End Source File
# Begin Source File

SOURCE=.\Helper.idl

!IF  "$(CFG)" == "Helper - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Performing MIDL step ...
InputPath=.\Helper.idl

BuildCmds= \
	midl /win32 /Oicf /h "Helper.h" /iid "Helper_i.c" "Helper.idl" \
	xcopy /F .\Helper.tlb $(TRIASTLB) \
	xcopy /F Helper.h $(TRIASINCLUDE) \
	xcopy /F Helper_i.c $(TRIASINCLUDE) \
	

".\Helper.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Helper.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Helper_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Helper - Win32 Release MinSize"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Performing MIDL step
InputPath=.\Helper.idl

BuildCmds= \
	midl /win32 /Oicf /h "Helper.h" /iid "Helper_i.c" "Helper.idl" \
	xcopy /F .\Helper.tlb $(TRIASTLB) \
	xcopy /F Helper.h $(TRIASINCLUDE) \
	xcopy /F Helper_i.c $(TRIASINCLUDE) \
	

".\Helper.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Helper.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\Helper_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Helper.rc
# ADD BASE RSC /l 0x407
# ADD RSC /l 0x407 /d _MSC_VER=1100
# End Source File
# Begin Source File

SOURCE=.\MatchBase.cpp
# End Source File
# Begin Source File

SOURCE=.\MatchFuzzy.cpp
# End Source File
# Begin Source File

SOURCE=.\MatchPlainExact.cpp
# End Source File
# Begin Source File

SOURCE=.\MatchRegExprExakt.cpp
# End Source File
# Begin Source File

SOURCE=.\RegExpr.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\StringPair.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CookieHelper.h
# End Source File
# Begin Source File

SOURCE=.\CPCookieHelperEvents.h
# End Source File
# Begin Source File

SOURCE=.\HelperConfig.h
# End Source File
# Begin Source File

SOURCE=.\MatchBase.h
# End Source File
# Begin Source File

SOURCE=.\MatchFuzzy.h
# End Source File
# Begin Source File

SOURCE=.\MatchPlainExact.h
# End Source File
# Begin Source File

SOURCE=.\MatchRegExprExakt.h
# End Source File
# Begin Source File

SOURCE=.\PersistHelper.h
# End Source File
# Begin Source File

SOURCE=.\RegExpr.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\StringPair.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "Registry Scripts"

# PROP Default_Filter "*.rgs"
# Begin Source File

SOURCE=.\CookieHelper.rgs
# End Source File
# Begin Source File

SOURCE=.\MatchFuzzy.rgs
# End Source File
# Begin Source File

SOURCE=.\MatchPlainTextExakt.rgs
# End Source File
# Begin Source File

SOURCE=.\MatchRegExprExakt.rgs
# End Source File
# Begin Source File

SOURCE=.\RegExpr.rgs
# End Source File
# Begin Source File

SOURCE=.\StringPair.rgs
# End Source File
# End Group
# Begin Group "Versioning"

# PROP Default_Filter "*.mak;*.tpl"
# Begin Source File

SOURCE=.\HELPER.TPL

!IF  "$(CFG)" == "Helper - Win32 Debug"

USERDEP__HELPE="version.mak"	
# Begin Custom Build - Generating version information ...
InputPath=.\HELPER.TPL

"helper.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f version.mak helper.def

# End Custom Build

!ELSEIF  "$(CFG)" == "Helper - Win32 Release MinSize"

USERDEP__HELPE="version.mak"	
# Begin Custom Build - Generating version information ...
InputPath=.\HELPER.TPL

"helper.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f version.mak helper.def

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\HELPERV.TPL

!IF  "$(CFG)" == "Helper - Win32 Debug"

USERDEP__HELPER="version.mak"	
# Begin Custom Build - Generating version information ...
InputPath=.\HELPERV.TPL

"helper.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f version.mak helper.rcv

# End Custom Build

!ELSEIF  "$(CFG)" == "Helper - Win32 Release MinSize"

USERDEP__HELPER="version.mak"	
# Begin Custom Build - Generating version information ...
InputPath=.\HELPERV.TPL

"helper.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f version.mak helper.rcv

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Version.mak
# End Source File
# Begin Source File

SOURCE=.\Version.tpl

!IF  "$(CFG)" == "Helper - Win32 Debug"

USERDEP__VERSI="version.mak"	
# Begin Custom Build - Generating version information ...
InputPath=.\Version.tpl

"version.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f version.mak version.h

# End Custom Build

!ELSEIF  "$(CFG)" == "Helper - Win32 Release MinSize"

USERDEP__VERSI="version.mak"	
# Begin Custom Build - Generating version information ...
InputPath=.\Version.tpl

"version.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f version.mak version.h

# End Custom Build

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
