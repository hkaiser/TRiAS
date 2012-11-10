# Microsoft Developer Studio Project File - Name="RunCmdAs" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=RunCmdAs - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "RunCmdAs.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "RunCmdAs.mak" CFG="RunCmdAs - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RunCmdAs - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "RunCmdAs - Win32 Release MinSize" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=xicl6.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "RunCmdAs - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I ".\DownHill\Include" /I "." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"StdAfx.h" /FD /GZ /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /out:"Debug/RunCmdAsd.exe" /pdbtype:sept
# Begin Custom Build - Performing registration
OutDir=.\Debug
TargetPath=.\Debug\RunCmdAsd.exe
InputPath=.\Debug\RunCmdAsd.exe
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "RunCmdAs - Win32 Release MinSize"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMinSize"
# PROP BASE Intermediate_Dir "ReleaseMinSize"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseMinSize"
# PROP Intermediate_Dir "ReleaseMinSize"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I ".\DownHill\Include" /I "." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"StdAfx.h" /FD /c
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# Begin Custom Build - Performing registration
OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\RunCmdAs.exe
InputPath=.\ReleaseMinSize\RunCmdAs.exe
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "RunCmdAs - Win32 Debug"
# Name "RunCmdAs - Win32 Release MinSize"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "u2nt"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Downhill\lib\dh_dir.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Downhill\lib\dh_env.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Downhill\lib\dh_file.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Downhill\lib\dh_grp.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Downhill\lib\dh_mem.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Downhill\lib\dh_pipe.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Downhill\lib\dh_proc.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Downhill\lib\dh_sig.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Downhill\lib\dh_str.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Downhill\lib\dh_time.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Downhill\lib\dh_uio.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Downhill\lib\dh_usr.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# Begin Source File

SOURCE=.\ExecuteCmdAs.cpp
# End Source File
# Begin Source File

SOURCE=.\RunCmdAs.cpp
# End Source File
# Begin Source File

SOURCE=.\RunCmdAs.idl
# ADD MTL /tlb ".\RunCmdAs.tlb" /h "RunCmdAs.h" /iid "RunCmdAs_i.c" /Oicf
# End Source File
# Begin Source File

SOURCE=.\RunCmdAs.rc
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"StdAfx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "u2nt Headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Downhill\include\ar.h
# End Source File
# Begin Source File

SOURCE=.\Downhill\include\dirent.h
# End Source File
# Begin Source File

SOURCE=.\Downhill\include\downhill.h
# End Source File
# Begin Source File

SOURCE=.\Downhill\include\errno.h
# End Source File
# Begin Source File

SOURCE=.\Downhill\include\fcntl.h
# End Source File
# Begin Source File

SOURCE=.\Downhill\include\grp.h
# End Source File
# Begin Source File

SOURCE=.\Downhill\include\malloc.h
# End Source File
# Begin Source File

SOURCE=.\Downhill\include\netdb.h
# End Source File
# Begin Source File

SOURCE=.\Downhill\include\pwd.h
# End Source File
# Begin Source File

SOURCE=.\Downhill\include\ranlib.h
# End Source File
# Begin Source File

SOURCE=.\Downhill\include\signal.h
# End Source File
# Begin Source File

SOURCE=.\Downhill\include\stdio.h
# End Source File
# Begin Source File

SOURCE=.\Downhill\include\stdlib.h
# End Source File
# Begin Source File

SOURCE=.\Downhill\include\string.h
# End Source File
# Begin Source File

SOURCE=.\Downhill\include\strings.h
# End Source File
# Begin Source File

SOURCE=.\Downhill\include\unistd.h
# End Source File
# Begin Source File

SOURCE=.\Downhill\include\utime.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ExecuteCmdAs.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\ExecuteCmdAs.rgs
# End Source File
# Begin Source File

SOURCE=.\RunCmdAs.rgs
# End Source File
# End Group
# Begin Group "Versioning"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\RunCmdAsv.Tpl

!IF  "$(CFG)" == "RunCmdAs - Win32 Debug"

USERDEP__RUNCM="version.mak"	
# Begin Custom Build
InputPath=.\RunCmdAsv.Tpl

"RunCmdAs.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak RunCmdAs.rcv

# End Custom Build

!ELSEIF  "$(CFG)" == "RunCmdAs - Win32 Release MinSize"

USERDEP__RUNCM="version.mak"	
# Begin Custom Build
InputPath=.\RunCmdAsv.Tpl

"RunCmdAs.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak RunCmdAs.rcv

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Version.mak
# End Source File
# Begin Source File

SOURCE=.\Version.tpl

!IF  "$(CFG)" == "RunCmdAs - Win32 Debug"

USERDEP__VERSI="version.mak"	
# Begin Custom Build
InputPath=.\Version.tpl

"version.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak version.h

# End Custom Build

!ELSEIF  "$(CFG)" == "RunCmdAs - Win32 Release MinSize"

USERDEP__VERSI="version.mak"	
# Begin Custom Build
InputPath=.\Version.tpl

"version.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak version.h

# End Custom Build

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
