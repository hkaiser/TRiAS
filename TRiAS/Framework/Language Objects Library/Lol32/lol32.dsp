# Microsoft Developer Studio Project File - Name="lol32" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=lol32 - Win32 LOL Win32DLL Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "lol32.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "lol32.mak" CFG="lol32 - Win32 LOL Win32DLL Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "lol32 - Win32 LOL Win32DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "lol32 - Win32 LOL Win32DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=xicl6.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Release"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\WinRel"
# PROP BASE Intermediate_Dir "..\WinRel"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\Release"
# PROP Intermediate_Dir "..\Release"
# PROP Ignore_Export_Lib 0
F90=fl32.exe
# ADD BASE CPP /nologo /G3 /Zp1 /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_NDEBUG" /D "__CV__" /D "_USRDLL" /D "_MBCS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /O1 /Op /I "$(YXX)\lib.c8" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "__LOLDLL__" /D "STRICT" /D "PRECOMPILE" /D "OS_NO_ALLOCATORS" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "OS_ALTERNATIVE_STRING_NAMES" /D "yy_user_config_" /Yu"lolpre.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "OFFICIAL"
# ADD RSC /l 0x407 /d "NDEBUG" /d "OFFICIAL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 oldnames.lib ldllcew.lib /nologo /subsystem:windows /dll /machine:IX86
# ADD LINK32 ospace5r.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:IX86 /out:"..\Release\lol.dll" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying Target to Destination ...
OutDir=.\..\Release
TargetDir=\YXX20\LIB.C8\Release
TargetPath=\YXX20\LIB.C8\Release\lol.dll
TargetName=lol
InputPath=\YXX20\LIB.C8\Release\lol.dll
SOURCE="$(InputPath)"

BuildCmds= \
	xcopy /F "$(TargetPath)" $(TRIASDIR_R) \
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_R) \
	xcopy /F "$(OutDir)\$(TargetName).lib" $(TRIASLIB) \
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASLIB) \
	

"$(TRIASDIR_R)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(TRIASLIB)\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Debug"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\WinDebug"
# PROP BASE Intermediate_Dir "..\WinDebug"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\Debug4"
# PROP Intermediate_Dir "..\Debug4"
# PROP Ignore_Export_Lib 0
F90=fl32.exe
# ADD BASE CPP /nologo /Zp1 /MT /W3 /GX /Zi /Od /Ob1 /Gf /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "__CV__" /D "_USRDLL" /D "_MBCS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /I "$(YXX)\lib.c8" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "__LOLDLL__" /D "STRICT" /D "PRECOMPILE" /D "OS_NO_ALLOCATORS" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "OS_ALTERNATIVE_STRING_NAMES" /D "yy_user_config_" /Fr /Yu"lolpre.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 oldnames.lib ldllcew.lib /nologo /subsystem:windows /dll /map:"FULL" /debug /machine:IX86
# ADD LINK32 ospace5d.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:IX86 /out:"..\Debug4\lol50d.dll"
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying Target to Destination ...
OutDir=.\..\Debug4
TargetPath=\YXX20\LIB.C8\Debug4\lol50d.dll
TargetName=lol50d
InputPath=\YXX20\LIB.C8\Debug4\lol50d.dll
SOURCE="$(InputPath)"

BuildCmds= \
	xcopy /F "$(TargetPath)" $(TRIASDIR_D) \
	xcopy /F "$(OutDir)\$(TargetName).pdb" $(TRIASDIR_D) \
	xcopy /F "$(OutDir)\$(TargetName).lib" $(TRIASLIB) \
	xcopy /F "$(OutDir)\$(TargetName).pdb" $(TRIASLIB) \
	

"$(TRIASDIR_D)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(TRIASLIB)\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# Begin Target

# Name "lol32 - Win32 LOL Win32DLL Release"
# Name "lol32 - Win32 LOL Win32DLL Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=..\lol32.rc

!IF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Release"

# ADD BASE RSC /l 0x407 /i "\YXX20\LIB.C8"
# ADD RSC /l 0x407 /fo"..\Release\lol32.res" /i "\YXX20\LIB.C8" /i "$(YXX)\LIB.C8"

!ELSEIF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Debug"

# ADD BASE RSC /l 0x407 /i "\YXX20\LIB.C8"
# ADD RSC /l 0x407 /fo"..\Debug4\lol32.res" /i "\YXX20\LIB.C8" /i "$(YXX)\lib.c8"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\lolpre.cpp
# ADD CPP /Yc"lolpre.h"
# End Source File
# Begin Source File

SOURCE=..\YY_ASRT.CPP

!IF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Release"

!ELSEIF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Debug"

# ADD CPP /Yu"lolpre.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\YY_AST.CPP

!IF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Release"

!ELSEIF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Debug"

# ADD CPP /Yu"lolpre.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\YY_BKTRK.CPP
# End Source File
# Begin Source File

SOURCE=..\YY_BUF.CPP

!IF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Release"

!ELSEIF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Debug"

# ADD CPP /Yu"lolpre.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\YY_ERR.CPP

!IF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Release"

!ELSEIF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Debug"

# ADD CPP /Yu"lolpre.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\YY_ERRGN.CPP

!IF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Release"

!ELSEIF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Debug"

# ADD CPP /Yu"lolpre.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\YY_INP.CPP

!IF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Release"

!ELSEIF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Debug"

# ADD CPP /Yu"lolpre.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\YY_INPFI.CPP

!IF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Release"

!ELSEIF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Debug"

# ADD CPP /Yu"lolpre.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\YY_INPGE.CPP

!IF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Release"

!ELSEIF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Debug"

# ADD CPP /Yu"lolpre.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\YY_INPST.CPP

!IF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Release"

!ELSEIF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Debug"

# ADD CPP /Yu"lolpre.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\YY_LEX.CPP

!IF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Release"

!ELSEIF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Debug"

# ADD CPP /Yu"lolpre.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\YY_LEXFA.CPP

!IF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Release"

!ELSEIF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Debug"

# ADD CPP /Yu"lolpre.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\YY_LEXRD.CPP

!IF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Release"

!ELSEIF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Debug"

# ADD CPP /Yu"lolpre.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\YY_LEXSM.CPP

!IF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Debug"

# ADD CPP /Yu"lolpre.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\YY_LOC.CPP

!IF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Release"

!ELSEIF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Debug"

# ADD CPP /Yu"lolpre.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\yy_myref.cpp
# End Source File
# Begin Source File

SOURCE=..\YY_PSR.CPP

!IF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Release"

!ELSEIF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Debug"

# ADD CPP /Yu"lolpre.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\YY_PSRFA.CPP

!IF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Release"

!ELSEIF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Debug"

# ADD CPP /Yu"lolpre.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\YY_PSRRD.CPP

!IF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Release"

!ELSEIF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Debug"

# ADD CPP /Yu"lolpre.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\YY_PSRSK.CPP
# End Source File
# Begin Source File

SOURCE=..\YY_PSRSM.CPP

!IF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Release"

!ELSEIF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Debug"

# ADD CPP /Yu"lolpre.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\YY_RDCSK.CPP
# End Source File
# Begin Source File

SOURCE=..\YY_REF.CPP
# End Source File
# Begin Source File

SOURCE=..\YY_SYM.CPP

!IF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Release"

!ELSEIF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Debug"

# ADD CPP /Yu"lolpre.h"

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=..\lolpre.h
# End Source File
# Begin Source File

SOURCE=..\..\INC.C8\YY_ALL.CFG
# End Source File
# Begin Source File

SOURCE=..\..\INC.C8\YY_ANSI.H
# End Source File
# Begin Source File

SOURCE=..\..\INC.C8\YY_ASRT.H
# End Source File
# Begin Source File

SOURCE=..\..\INC.C8\YY_AST.H
# End Source File
# Begin Source File

SOURCE=..\..\INC.C8\YY_BOOL.H
# End Source File
# Begin Source File

SOURCE=..\..\INC.C8\YY_BUF.H
# End Source File
# Begin Source File

SOURCE=..\..\INC.C8\YY_CFG.H
# End Source File
# Begin Source File

SOURCE=..\..\INC.C8\YY_ERR.H
# End Source File
# Begin Source File

SOURCE=..\..\INC.C8\YY_ERRGN.H
# End Source File
# Begin Source File

SOURCE=..\..\INC.C8\YY_INP.H
# End Source File
# Begin Source File

SOURCE=..\..\INC.C8\YY_INPFI.H
# End Source File
# Begin Source File

SOURCE=..\..\INC.C8\YY_INPGE.H
# End Source File
# Begin Source File

SOURCE=..\..\INC.C8\YY_INPST.H
# End Source File
# Begin Source File

SOURCE=..\..\INC.C8\YY_LEX.H
# End Source File
# Begin Source File

SOURCE=..\..\INC.C8\YY_LEXFA.H
# End Source File
# Begin Source File

SOURCE=..\..\INC.C8\YY_LEXRD.H
# End Source File
# Begin Source File

SOURCE=..\..\INC.C8\YY_LEXSM.H
# End Source File
# Begin Source File

SOURCE=..\..\INC.C8\YY_LOC.H
# End Source File
# Begin Source File

SOURCE=..\YY_MYREF.H
# End Source File
# Begin Source File

SOURCE=..\..\INC.C8\YY_PSR.H
# End Source File
# Begin Source File

SOURCE=..\..\INC.C8\YY_PSRFA.H
# End Source File
# Begin Source File

SOURCE=..\..\INC.C8\YY_PSRRD.H
# End Source File
# Begin Source File

SOURCE=..\..\INC.C8\YY_PSRSM.H
# End Source File
# Begin Source File

SOURCE=..\..\INC.C8\YY_STARG.H
# End Source File
# Begin Source File

SOURCE=..\..\INC.C8\YY_STDEF.H
# End Source File
# Begin Source File

SOURCE=..\..\INC.C8\YY_STDIO.H
# End Source File
# Begin Source File

SOURCE=..\..\INC.C8\YY_STDLB.H
# End Source File
# Begin Source File

SOURCE=..\..\INC.C8\YY_STRNG.H
# End Source File
# Begin Source File

SOURCE=..\..\INC.C8\YY_SYM.H
# End Source File
# Begin Source File

SOURCE=..\..\INC.C8\YY_TRACE.H
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
