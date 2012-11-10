# Microsoft Developer Studio Project File - Name="Sqd" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=Sqd - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Sqd.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Sqd.mak" CFG="Sqd - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Sqd - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "Sqd - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Sqd - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib  kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 containr.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib  kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "Sqd - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ  /c
# ADD CPP /nologo /W3 /WX /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib  kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 cont50d.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib  kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Sqd - Win32 Release"
# Name "Sqd - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\DGEOOBJ.CPP
# End Source File
# Begin Source File

SOURCE=.\FLTCNVT.CPP
# End Source File
# Begin Source File

SOURCE=.\gdbasc.rc
# End Source File
# Begin Source File

SOURCE=.\GDBLX.CPP

!IF  "$(CFG)" == "Sqd - Win32 Release"

!ELSEIF  "$(CFG)" == "Sqd - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\GDBLX.LX

!IF  "$(CFG)" == "Sqd - Win32 Release"

USERDEP__GDBLX="gdblx.sed"	"gdblx.sk"	
# Begin Custom Build
InputPath=.\GDBLX.LX

"gdblx.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	pclex -l -pgdblx.sk $(InputPath) 
	sed -f gdblx.sed gdblx.c > gdblx.cpp 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Sqd - Win32 Debug"

USERDEP__GDBLX="gdblx.sed"	"gdblx.sk"	
# Begin Custom Build
InputPath=.\GDBLX.LX

"gdblx.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	pclex -l -pgdblx.sk $(InputPath) 
	sed -f gdblx.sed gdblx.c > gdblx.cpp 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\GDBM.CPP
# End Source File
# Begin Source File

SOURCE=.\GDBY.CPP
# End Source File
# Begin Source File

SOURCE=.\GDBY.Y

!IF  "$(CFG)" == "Sqd - Win32 Release"

USERDEP__GDBY_="gdby.sed"	"yacc.par"	
# Begin Custom Build
InputPath=.\GDBY.Y

"gdby.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	@copy yacc.par c:\lib > nul 
	yacc -dv gdby.y 
	sed -f gdby.sed ytab.c > gdby.cpp 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Sqd - Win32 Debug"

USERDEP__GDBY_="yacc.par"	"gdby.sed"	
# Begin Custom Build
InputPath=.\GDBY.Y

"gdby.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	@copy yacc.par c:\lib > nul 
	yacc -dv gdby.y 
	sed -f gdby.sed ytab.c > gdby.cpp 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\HASHTABS.CPP
# End Source File
# Begin Source File

SOURCE=.\INITPARS.CPP
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "Sqd - Win32 Release"

!ELSEIF  "$(CFG)" == "Sqd - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\YYSTYPE.CPP
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\DBVERSIO.H
# End Source File
# Begin Source File

SOURCE=.\DGEOOBJ.HXX
# End Source File
# Begin Source File

SOURCE=.\GDB.H
# End Source File
# Begin Source File

SOURCE=.\HASHTABS.HXX
# End Source File
# Begin Source File

SOURCE=.\MCODES.H
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\copystr.rc2
# End Source File
# Begin Source File

SOURCE=.\res\GdbAsc.rcv
# End Source File
# End Group
# Begin Group "Support files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\GDBLX.SED
# End Source File
# Begin Source File

SOURCE=.\GDBLX.SK
# End Source File
# Begin Source File

SOURCE=.\GDBY.SED
# End Source File
# Begin Source File

SOURCE=.\yacc.par
# End Source File
# End Group
# Begin Group "Versioning"

# PROP Default_Filter "*.mak,*.tpl"
# Begin Source File

SOURCE=.\res\copystrt.tpl

!IF  "$(CFG)" == "Sqd - Win32 Release"

# Begin Custom Build
InputPath=.\res\copystrt.tpl

"res/copystr.rc2" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f version.mak -nologo "res/copystr.rc2"

# End Custom Build

!ELSEIF  "$(CFG)" == "Sqd - Win32 Debug"

# Begin Custom Build
InputPath=.\res\copystrt.tpl

"res/copystr.rc2" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f version.mak -nologo "res/copystr.rc2"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\gdbascv.tpl

!IF  "$(CFG)" == "Sqd - Win32 Release"

# Begin Custom Build
InputPath=.\res\gdbascv.tpl

"res/gdbasc.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f version.mak -nologo "res/gdbasc.rcv"

# End Custom Build

!ELSEIF  "$(CFG)" == "Sqd - Win32 Debug"

# Begin Custom Build
InputPath=.\res\gdbascv.tpl

"res/gdbasc.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f version.mak -nologo "res/gdbasc.rcv"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\version.mak
# End Source File
# Begin Source File

SOURCE=.\version.tpl

!IF  "$(CFG)" == "Sqd - Win32 Release"

USERDEP__VERSI="version.mak"	
# Begin Custom Build
InputPath=.\version.tpl

"dbversio.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f version.mak -nologo dbversio.h

# End Custom Build

!ELSEIF  "$(CFG)" == "Sqd - Win32 Debug"

USERDEP__VERSI="version.mak"	
# Begin Custom Build
InputPath=.\version.tpl

"dbversio.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f version.mak -nologo dbversio.h

# End Custom Build

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
