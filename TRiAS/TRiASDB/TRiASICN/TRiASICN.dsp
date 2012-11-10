# Microsoft Developer Studio Project File - Name="TRiASICN" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=TRiASICN - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TRiASICN.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TRiASICN.mak" CFG="TRiASICN - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TRiASICN - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "TRiASICN - Win32 Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/TRiAS/TRiASDB/TRiASICN", TGRAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TRiASICN - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MTd /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /map /debug /machine:I386 /pdbtype:sept /mapinfo:lines
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying target to destination ...
OutDir=.\Debug
TargetPath=.\Debug\TRiASICN.dll
TargetName=TRiASICN
InputPath=.\Debug\TRiASICN.dll
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(TargetPath) $(TRIASDIR_D) 
	xcopy /F $(OutDir)\$(TargetName).pdb $(TRIASDIR_D) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASICN - Win32 Release MinSize"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMinSize"
# PROP BASE Intermediate_Dir "ReleaseMinSize"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseMinSize"
# PROP Intermediate_Dir "ReleaseMinSize"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_DLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying target to destination ...
TargetDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\TRiASICN.dll
TargetName=TRiASICN
InputPath=.\ReleaseMinSize\TRiASICN.dll
SOURCE="$(InputPath)"

"$(TRIASDIR_R)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(TargetPath) $(TRIASDIR_R) 
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_R) 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "TRiASICN - Win32 Debug"
# Name "TRiASICN - Win32 Release MinSize"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TRiASICN.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASICN.def
# End Source File
# Begin Source File

SOURCE=.\TRiASICN.idl

!IF  "$(CFG)" == "TRiASICN - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Performing MIDL step
InputPath=.\TRiASICN.idl

BuildCmds= \
	midl /Oicf /h "TRiASICN.h" /iid "TRiASICN_i.c" "TRiASICN.idl"

".\TRiASICN.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TRiASICN.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TRiASICN_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASICN - Win32 Release MinSize"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Performing MIDL step
InputPath=.\TRiASICN.idl

BuildCmds= \
	midl /Oicf /h "TRiASICN.h" /iid "TRiASICN_i.c" "TRiASICN.idl"

".\TRiASICN.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TRiASICN.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TRiASICN_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TRiASICN.rc
# End Source File
# Begin Source File

SOURCE=.\TRiASIconHandler.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TRiASIconHandler.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\buchicon.ico
# End Source File
# Begin Source File

SOURCE=.\buchv1.ico
# End Source File
# Begin Source File

SOURCE=.\buchv1_obsolete.ico
# End Source File
# Begin Source File

SOURCE=.\BUCHV2.ICO
# End Source File
# Begin Source File

SOURCE=.\Buchv2_obsolete.ico
# End Source File
# Begin Source File

SOURCE=.\Buchv3.ico
# End Source File
# Begin Source File

SOURCE=.\Buchv3_obsolete.ico
# End Source File
# Begin Source File

SOURCE=.\buchv4.ico
# End Source File
# Begin Source File

SOURCE=.\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\project.ico
# End Source File
# End Group
# Begin Group "Registry Scripts"

# PROP Default_Filter "*.rgs"
# Begin Source File

SOURCE=.\TRiASIconHandler.rgs
# End Source File
# End Group
# Begin Group "Versioning"

# PROP Default_Filter "*.tpl;*.mak"
# Begin Source File

SOURCE=.\TRiASICN.tpl

!IF  "$(CFG)" == "TRiASICN - Win32 Debug"

USERDEP__TRIAS="version.mak"	
# Begin Custom Build - Generating versioninfo ...
InputPath=.\TRiASICN.tpl

"TRiASICN.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak TRiASICN.def

# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASICN - Win32 Release MinSize"

USERDEP__TRIAS="version.mak"	
# Begin Custom Build - Generating versioninfo ...
InputPath=.\TRiASICN.tpl

"TRiASICN.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak TRiASICN.def

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TRiASICNv.tpl

!IF  "$(CFG)" == "TRiASICN - Win32 Debug"

USERDEP__TRIASI="version.mak"	
# Begin Custom Build - Generating versioninfo ...
InputPath=.\TRiASICNv.tpl

"TRiASICN.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak TRiASICN.rcv

# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASICN - Win32 Release MinSize"

USERDEP__TRIASI="version.mak"	
# Begin Custom Build - Generating versioninfo ...
InputPath=.\TRiASICNv.tpl

"TRiASICN.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak TRiASICN.rcv

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Version.mak
# End Source File
# Begin Source File

SOURCE=.\Version.tpl

!IF  "$(CFG)" == "TRiASICN - Win32 Debug"

USERDEP__VERSI="version.mak"	
# Begin Custom Build - Generating versioninfo ...
InputPath=.\Version.tpl

"version.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak version.h

# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASICN - Win32 Release MinSize"

USERDEP__VERSI="version.mak"	
# Begin Custom Build - Generating versioninfo ...
InputPath=.\Version.tpl

"version.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak version.h

# End Custom Build

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
