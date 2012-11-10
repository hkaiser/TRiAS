# Microsoft Developer Studio Project File - Name="AscBna" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=AscBna - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "AscBna.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "AscBna.mak" CFG="AscBna - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AscBna - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "AscBna - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=xicl6.exe
RSC=rc.exe

!IF  "$(CFG)" == "AscBna - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Yu"StdAfx.h" /FD /c
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "AscBna - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Yu"StdAfx.h" /FD /GZ /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "AscBna - Win32 Release"
# Name "AscBna - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ASCBNA.LX

!IF  "$(CFG)" == "AscBna - Win32 Release"

# Begin Custom Build
InputDir=.
InputPath=.\ASCBNA.LX
InputName=ASCBNA

"$(InputDir)\$(InputName)l.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	pclex -s -ppclex.sk -l "$(InputPath)" 
	if exist "$(InputDir)\$(InputName)l.cpp" del "$(InputDir)\$(InputName)l.cpp" 
	copy ascbna.c "$(InputDir)\$(InputName)l.cpp" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "AscBna - Win32 Debug"

# Begin Custom Build
InputDir=.
InputPath=.\ASCBNA.LX
InputName=ASCBNA

"$(InputDir)\$(InputName)l.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	pclex -s -ppclex.sk -l "$(InputPath)" 
	if exist "$(InputDir)\$(InputName)l.cpp" del "$(InputDir)\$(InputName)l.cpp" 
	copy ascbna.c "$(InputDir)\$(InputName)l.cpp" 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ASCBNA.Y
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\ASCBNAC.cpp
# End Source File
# Begin Source File

SOURCE=.\ascbnal.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\ASCBNAM.cpp
# End Source File
# Begin Source File

SOURCE=.\ASCBNAY.CPP
# End Source File
# Begin Source File

SOURCE=.\PUTBNA.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"StdAfx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ASCBNA.H
# End Source File
# Begin Source File

SOURCE=.\AscBnaConfig.h
# End Source File
# Begin Source File

SOURCE=.\ASCBNAY.H
# End Source File
# Begin Source File

SOURCE=.\ASCERRS.H
# End Source File
# Begin Source File

SOURCE=.\CoordSystems.h
# End Source File
# Begin Source File

SOURCE=.\DBVERSIO.H
# End Source File
# Begin Source File

SOURCE=.\INPUT.H
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "Versioning"

# PROP Default_Filter "*.tpl,*.mak"
# Begin Source File

SOURCE=.\DBVERSIO.tpl

!IF  "$(CFG)" == "AscBna - Win32 Release"

USERDEP__DBVER="Version.mak"	
# Begin Custom Build
InputPath=.\DBVERSIO.tpl

"DBVersio.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f Version.mak -nologo DBVersio.h

# End Custom Build

!ELSEIF  "$(CFG)" == "AscBna - Win32 Debug"

USERDEP__DBVER="Version.mak"	
# Begin Custom Build
InputPath=.\DBVERSIO.tpl

"DBVersio.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f Version.mak -nologo DBVersio.h

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Version.mak
# End Source File
# End Group
# End Target
# End Project
