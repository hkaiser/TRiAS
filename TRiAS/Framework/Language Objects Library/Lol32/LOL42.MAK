# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102
# TARGTYPE "Win32 (x86) Static Library" 0x0104

!IF "$(CFG)" == ""
CFG=lol32lib - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to lol32lib - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "lol32 - Win32 LOL Win32DLL Release" && "$(CFG)" !=\
 "lol32 - Win32 LOL Win32DLL Debug" && "$(CFG)" != "lol32lib - Win32 Release" &&\
 "$(CFG)" != "lol32lib - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "lol42.mak" CFG="lol32lib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "lol32 - Win32 LOL Win32DLL Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "lol32 - Win32 LOL Win32DLL Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "lol32lib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "lol32lib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "lol32 - Win32 LOL Win32DLL Debug"

!IF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Release"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
TargetName=lol32
# End Custom Macros

ALL : "$(OUTDIR)\lol32.dll" "c:\trias.mvc\trias200.rel\lol32.dll"\
 "..\..\..\cv.mvc\lib32\lol32.lib"

CLEAN : 
	-@erase "$(INTDIR)\lol32.pch"
	-@erase "$(INTDIR)\lol32.res"
	-@erase "$(INTDIR)\lolpre.obj"
	-@erase "$(INTDIR)\YY_ASRT.OBJ"
	-@erase "$(INTDIR)\YY_AST.OBJ"
	-@erase "$(INTDIR)\YY_BUF.OBJ"
	-@erase "$(INTDIR)\YY_ERR.OBJ"
	-@erase "$(INTDIR)\YY_ERRGN.OBJ"
	-@erase "$(INTDIR)\YY_INP.OBJ"
	-@erase "$(INTDIR)\YY_INPFI.OBJ"
	-@erase "$(INTDIR)\YY_INPGE.OBJ"
	-@erase "$(INTDIR)\YY_INPST.OBJ"
	-@erase "$(INTDIR)\YY_LEX.OBJ"
	-@erase "$(INTDIR)\YY_LEXFA.OBJ"
	-@erase "$(INTDIR)\YY_LEXRD.OBJ"
	-@erase "$(INTDIR)\YY_LEXSM.OBJ"
	-@erase "$(INTDIR)\YY_LOC.OBJ"
	-@erase "$(INTDIR)\YY_PSR.OBJ"
	-@erase "$(INTDIR)\YY_PSRFA.OBJ"
	-@erase "$(INTDIR)\YY_PSRRD.OBJ"
	-@erase "$(INTDIR)\YY_PSRSM.OBJ"
	-@erase "$(INTDIR)\YY_SYM.OBJ"
	-@erase "$(OUTDIR)\lol32.dll"
	-@erase "$(OUTDIR)\lol32.exp"
	-@erase "$(OUTDIR)\lol32.lib"
	-@erase "..\..\..\cv.mvc\lib32\lol32.lib"
	-@erase "c:\trias.mvc\trias200.rel\lol32.dll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(OUTDIR)/lol32.bsc : $(OUTDIR)  $(BSC32_SBRS)
CPP=cl.exe
# ADD BASE CPP /nologo /G3 /Zp1 /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_NDEBUG" /D "__CV__" /D "_USRDLL" /D "_MBCS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /O2 /Op /Ob1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "__LOLDLL__" /D "STRICT" /D "PRECOMPILE" /Fp"Release/lol32.pch" /Yu"lolpre.h" /c
# SUBTRACT CPP /Z<none>
CPP_PROJ=/nologo /MD /W3 /WX /GX /O2 /Op /Ob1 /D "NDEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__LOLDLL__" /D "STRICT" /D "PRECOMPILE" /Fp"$(INTDIR)/lol32.pch"\
 /Yu"lolpre.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

MTL=mktyplib.exe
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
RSC=rc.exe
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "OFFICIAL"
# ADD RSC /l 0x407 /d "NDEBUG" /d "OFFICIAL"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/lol32.res" /d "NDEBUG" /d "OFFICIAL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/lol42.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 oldnames.lib ldllcew.lib /nologo /subsystem:windows /dll /machine:IX86
# ADD LINK32 stdcppr.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:IX86 /out:"Release/lol32.dll" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none /debug
LINK32_FLAGS=stdcppr.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)/lol32.pdb"\
 /machine:IX86 /def:".\Lol32.def" /out:"$(OUTDIR)/lol32.dll"\
 /implib:"$(OUTDIR)/lol32.lib" /SUBSYSTEM:windows,4.0 
DEF_FILE= \
	".\Lol32.def"
LINK32_OBJS= \
	"$(INTDIR)\lol32.res" \
	"$(INTDIR)\lolpre.obj" \
	"$(INTDIR)\YY_ASRT.OBJ" \
	"$(INTDIR)\YY_AST.OBJ" \
	"$(INTDIR)\YY_BUF.OBJ" \
	"$(INTDIR)\YY_ERR.OBJ" \
	"$(INTDIR)\YY_ERRGN.OBJ" \
	"$(INTDIR)\YY_INP.OBJ" \
	"$(INTDIR)\YY_INPFI.OBJ" \
	"$(INTDIR)\YY_INPGE.OBJ" \
	"$(INTDIR)\YY_INPST.OBJ" \
	"$(INTDIR)\YY_LEX.OBJ" \
	"$(INTDIR)\YY_LEXFA.OBJ" \
	"$(INTDIR)\YY_LEXRD.OBJ" \
	"$(INTDIR)\YY_LEXSM.OBJ" \
	"$(INTDIR)\YY_LOC.OBJ" \
	"$(INTDIR)\YY_PSR.OBJ" \
	"$(INTDIR)\YY_PSRFA.OBJ" \
	"$(INTDIR)\YY_PSRRD.OBJ" \
	"$(INTDIR)\YY_PSRSM.OBJ" \
	"$(INTDIR)\YY_SYM.OBJ"

"$(OUTDIR)\lol32.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying Target to Destination ...
OutDir=.\Release
TargetPath=.\Release\lol32.dll
TargetName=lol32
InputPath=.\Release\lol32.dll
SOURCE=$(InputPath)

BuildCmds= \
	copy "$(TargetPath)" c:\trias.mvc\trias200.rel \
	copy "$(OutDir)\$(TargetName).lib" e:\cv.mvc\lib32 \
	

"c:\trias.mvc\trias200.rel\$(TargetName).dll" : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
   $(BuildCmds)

"e:\cv.mvc\lib32\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Debug"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug4"
# PROP Intermediate_Dir "Debug4"
OUTDIR=.\Debug4
INTDIR=.\Debug4
# Begin Custom Macros
TargetName=lol32d
# End Custom Macros

ALL : "$(OUTDIR)\lol32d.dll" "$(OUTDIR)\lol42.bsc"\
 "c:\trias.mvc\trias200\lol32d.dll" "..\..\..\cv.mvc\lib\lol32d.lib"

CLEAN : 
	-@erase "$(INTDIR)\lol32.res"
	-@erase "$(INTDIR)\lol42.pch"
	-@erase "$(INTDIR)\lolpre.obj"
	-@erase "$(INTDIR)\lolpre.sbr"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(INTDIR)\YY_ASRT.OBJ"
	-@erase "$(INTDIR)\YY_ASRT.SBR"
	-@erase "$(INTDIR)\YY_AST.OBJ"
	-@erase "$(INTDIR)\YY_AST.SBR"
	-@erase "$(INTDIR)\YY_BUF.OBJ"
	-@erase "$(INTDIR)\YY_BUF.SBR"
	-@erase "$(INTDIR)\YY_ERR.OBJ"
	-@erase "$(INTDIR)\YY_ERR.SBR"
	-@erase "$(INTDIR)\YY_ERRGN.OBJ"
	-@erase "$(INTDIR)\YY_ERRGN.SBR"
	-@erase "$(INTDIR)\YY_INP.OBJ"
	-@erase "$(INTDIR)\YY_INP.SBR"
	-@erase "$(INTDIR)\YY_INPFI.OBJ"
	-@erase "$(INTDIR)\YY_INPFI.SBR"
	-@erase "$(INTDIR)\YY_INPGE.OBJ"
	-@erase "$(INTDIR)\YY_INPGE.SBR"
	-@erase "$(INTDIR)\YY_INPST.OBJ"
	-@erase "$(INTDIR)\YY_INPST.SBR"
	-@erase "$(INTDIR)\YY_LEX.OBJ"
	-@erase "$(INTDIR)\YY_LEX.SBR"
	-@erase "$(INTDIR)\YY_LEXFA.OBJ"
	-@erase "$(INTDIR)\YY_LEXFA.SBR"
	-@erase "$(INTDIR)\YY_LEXRD.OBJ"
	-@erase "$(INTDIR)\YY_LEXRD.SBR"
	-@erase "$(INTDIR)\YY_LEXSM.OBJ"
	-@erase "$(INTDIR)\YY_LEXSM.SBR"
	-@erase "$(INTDIR)\YY_LOC.OBJ"
	-@erase "$(INTDIR)\YY_LOC.SBR"
	-@erase "$(INTDIR)\YY_PSR.OBJ"
	-@erase "$(INTDIR)\YY_PSR.SBR"
	-@erase "$(INTDIR)\YY_PSRFA.OBJ"
	-@erase "$(INTDIR)\YY_PSRFA.SBR"
	-@erase "$(INTDIR)\YY_PSRRD.OBJ"
	-@erase "$(INTDIR)\YY_PSRRD.SBR"
	-@erase "$(INTDIR)\YY_PSRSM.OBJ"
	-@erase "$(INTDIR)\YY_PSRSM.SBR"
	-@erase "$(INTDIR)\YY_SYM.OBJ"
	-@erase "$(INTDIR)\YY_SYM.SBR"
	-@erase "$(OUTDIR)\lol32d.dll"
	-@erase "$(OUTDIR)\lol32d.exp"
	-@erase "$(OUTDIR)\lol32d.ilk"
	-@erase "$(OUTDIR)\lol32d.lib"
	-@erase "$(OUTDIR)\lol32d.pdb"
	-@erase "$(OUTDIR)\lol42.bsc"
	-@erase "..\..\..\cv.mvc\lib\lol32d.lib"
	-@erase "c:\trias.mvc\trias200\lol32d.dll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(OUTDIR)/lol32.bsc : $(OUTDIR)  $(BSC32_SBRS)
CPP=cl.exe
# ADD BASE CPP /nologo /Zp1 /MT /W3 /GX /Zi /Od /Ob1 /Gf /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "__CV__" /D "_USRDLL" /D "_MBCS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "__LOLDLL__" /D "STRICT" /D "PRECOMPILE" /Fr /Yu"lolpre.h" /c
# SUBTRACT CPP /Gf
CPP_PROJ=/nologo /MDd /W3 /WX /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__LOLDLL__" /D "STRICT" /D "PRECOMPILE" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/lol42.pch" /Yu"lolpre.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug4/
CPP_SBRS=.\Debug4/

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

MTL=mktyplib.exe
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
RSC=rc.exe
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/lol32.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/lol42.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\lolpre.sbr" \
	"$(INTDIR)\YY_ASRT.SBR" \
	"$(INTDIR)\YY_AST.SBR" \
	"$(INTDIR)\YY_BUF.SBR" \
	"$(INTDIR)\YY_ERR.SBR" \
	"$(INTDIR)\YY_ERRGN.SBR" \
	"$(INTDIR)\YY_INP.SBR" \
	"$(INTDIR)\YY_INPFI.SBR" \
	"$(INTDIR)\YY_INPGE.SBR" \
	"$(INTDIR)\YY_INPST.SBR" \
	"$(INTDIR)\YY_LEX.SBR" \
	"$(INTDIR)\YY_LEXFA.SBR" \
	"$(INTDIR)\YY_LEXRD.SBR" \
	"$(INTDIR)\YY_LEXSM.SBR" \
	"$(INTDIR)\YY_LOC.SBR" \
	"$(INTDIR)\YY_PSR.SBR" \
	"$(INTDIR)\YY_PSRFA.SBR" \
	"$(INTDIR)\YY_PSRRD.SBR" \
	"$(INTDIR)\YY_PSRSM.SBR" \
	"$(INTDIR)\YY_SYM.SBR"

"$(OUTDIR)\lol42.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 oldnames.lib ldllcew.lib /nologo /subsystem:windows /dll /map:"FULL" /debug /machine:IX86
# ADD LINK32 stdcppd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:IX86 /out:"Debug4/lol32d.dll" /subsystem:windows:4,0
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=stdcppd.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib /nologo /dll /incremental:yes\
 /pdb:"$(OUTDIR)/lol32d.pdb" /debug /machine:IX86 /def:".\Lol32d.def"\
 /out:"$(OUTDIR)/lol32d.dll" /implib:"$(OUTDIR)/lol32d.lib"\
 /subsystem:windows:4,0 
DEF_FILE= \
	".\Lol32d.def"
LINK32_OBJS= \
	"$(INTDIR)\lol32.res" \
	"$(INTDIR)\lolpre.obj" \
	"$(INTDIR)\YY_ASRT.OBJ" \
	"$(INTDIR)\YY_AST.OBJ" \
	"$(INTDIR)\YY_BUF.OBJ" \
	"$(INTDIR)\YY_ERR.OBJ" \
	"$(INTDIR)\YY_ERRGN.OBJ" \
	"$(INTDIR)\YY_INP.OBJ" \
	"$(INTDIR)\YY_INPFI.OBJ" \
	"$(INTDIR)\YY_INPGE.OBJ" \
	"$(INTDIR)\YY_INPST.OBJ" \
	"$(INTDIR)\YY_LEX.OBJ" \
	"$(INTDIR)\YY_LEXFA.OBJ" \
	"$(INTDIR)\YY_LEXRD.OBJ" \
	"$(INTDIR)\YY_LEXSM.OBJ" \
	"$(INTDIR)\YY_LOC.OBJ" \
	"$(INTDIR)\YY_PSR.OBJ" \
	"$(INTDIR)\YY_PSRFA.OBJ" \
	"$(INTDIR)\YY_PSRRD.OBJ" \
	"$(INTDIR)\YY_PSRSM.OBJ" \
	"$(INTDIR)\YY_SYM.OBJ"

"$(OUTDIR)\lol32d.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying Target to Destination ...
OutDir=.\Debug4
TargetPath=.\Debug4\lol32d.dll
TargetName=lol32d
InputPath=.\Debug4\lol32d.dll
SOURCE=$(InputPath)

BuildCmds= \
	copy "$(TargetPath)" c:\trias.mvc\trias200 \
	copy "$(OutDir)\$(TargetName).lib" e:\cv.mvc\lib \
	

"c:\trias.mvc\trias200\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"e:\cv.mvc\lib\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "lol32lib - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "lol32lib\Release"
# PROP BASE Intermediate_Dir "lol32lib\Release"
# PROP BASE Target_Dir "lol32lib"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "lol32lib\Release"
# PROP Intermediate_Dir "lol32lib\Release"
# PROP Target_Dir "lol32lib"
OUTDIR=.\lol32lib\Release
INTDIR=.\lol32lib\Release

ALL : "$(OUTDIR)\lol32rl.lib"

CLEAN : 
	-@erase "$(INTDIR)\lol32lib.pch"
	-@erase "$(INTDIR)\lolpre.obj"
	-@erase "$(INTDIR)\YY_ASRT.OBJ"
	-@erase "$(INTDIR)\YY_AST.OBJ"
	-@erase "$(INTDIR)\YY_BUF.OBJ"
	-@erase "$(INTDIR)\Yy_cmd.obj"
	-@erase "$(INTDIR)\YY_ERR.OBJ"
	-@erase "$(INTDIR)\YY_ERRGN.OBJ"
	-@erase "$(INTDIR)\Yy_errst.obj"
	-@erase "$(INTDIR)\Yy_help.obj"
	-@erase "$(INTDIR)\YY_INP.OBJ"
	-@erase "$(INTDIR)\YY_INPFI.OBJ"
	-@erase "$(INTDIR)\YY_INPGE.OBJ"
	-@erase "$(INTDIR)\YY_INPST.OBJ"
	-@erase "$(INTDIR)\YY_LEX.OBJ"
	-@erase "$(INTDIR)\YY_LEXFA.OBJ"
	-@erase "$(INTDIR)\YY_LEXRD.OBJ"
	-@erase "$(INTDIR)\YY_LEXSM.OBJ"
	-@erase "$(INTDIR)\YY_LOC.OBJ"
	-@erase "$(INTDIR)\YY_PSR.OBJ"
	-@erase "$(INTDIR)\YY_PSRFA.OBJ"
	-@erase "$(INTDIR)\YY_PSRRD.OBJ"
	-@erase "$(INTDIR)\YY_PSRSM.OBJ"
	-@erase "$(INTDIR)\Yy_signc.obj"
	-@erase "$(INTDIR)\YY_SYM.OBJ"
	-@erase "$(OUTDIR)\lol32rl.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "__LOLDLL__" /D "STRICT" /D "PRECOMPILE" /Yu"lolpre.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "__LOLDLL__" /D "STRICT" /D "PRECOMPILE" /Fp"$(INTDIR)/lol32lib.pch"\
 /Yu"lolpre.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\lol32lib\Release/
CPP_SBRS=.\.

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/lol32lib.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"lol32lib\Release\lol32rl.lib"
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/lol32rl.lib" 
LIB32_OBJS= \
	"$(INTDIR)\lolpre.obj" \
	"$(INTDIR)\YY_ASRT.OBJ" \
	"$(INTDIR)\YY_AST.OBJ" \
	"$(INTDIR)\YY_BUF.OBJ" \
	"$(INTDIR)\Yy_cmd.obj" \
	"$(INTDIR)\YY_ERR.OBJ" \
	"$(INTDIR)\YY_ERRGN.OBJ" \
	"$(INTDIR)\Yy_errst.obj" \
	"$(INTDIR)\Yy_help.obj" \
	"$(INTDIR)\YY_INP.OBJ" \
	"$(INTDIR)\YY_INPFI.OBJ" \
	"$(INTDIR)\YY_INPGE.OBJ" \
	"$(INTDIR)\YY_INPST.OBJ" \
	"$(INTDIR)\YY_LEX.OBJ" \
	"$(INTDIR)\YY_LEXFA.OBJ" \
	"$(INTDIR)\YY_LEXRD.OBJ" \
	"$(INTDIR)\YY_LEXSM.OBJ" \
	"$(INTDIR)\YY_LOC.OBJ" \
	"$(INTDIR)\YY_PSR.OBJ" \
	"$(INTDIR)\YY_PSRFA.OBJ" \
	"$(INTDIR)\YY_PSRRD.OBJ" \
	"$(INTDIR)\YY_PSRSM.OBJ" \
	"$(INTDIR)\Yy_signc.obj" \
	"$(INTDIR)\YY_SYM.OBJ"

"$(OUTDIR)\lol32rl.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "lol32lib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "lol32lib\Debug"
# PROP BASE Intermediate_Dir "lol32lib\Debug"
# PROP BASE Target_Dir "lol32lib"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "lol32lib\Debug"
# PROP Intermediate_Dir "lol32lib\Debug"
# PROP Target_Dir "lol32lib"
OUTDIR=.\lol32lib\Debug
INTDIR=.\lol32lib\Debug

ALL : "$(OUTDIR)\lol32dl.lib"

CLEAN : 
	-@erase "$(INTDIR)\lol32lib.pch"
	-@erase "$(INTDIR)\lolpre.obj"
	-@erase "$(INTDIR)\YY_ASRT.OBJ"
	-@erase "$(INTDIR)\YY_AST.OBJ"
	-@erase "$(INTDIR)\YY_BUF.OBJ"
	-@erase "$(INTDIR)\Yy_cmd.obj"
	-@erase "$(INTDIR)\YY_ERR.OBJ"
	-@erase "$(INTDIR)\YY_ERRGN.OBJ"
	-@erase "$(INTDIR)\Yy_errst.obj"
	-@erase "$(INTDIR)\Yy_help.obj"
	-@erase "$(INTDIR)\YY_INP.OBJ"
	-@erase "$(INTDIR)\YY_INPFI.OBJ"
	-@erase "$(INTDIR)\YY_INPGE.OBJ"
	-@erase "$(INTDIR)\YY_INPST.OBJ"
	-@erase "$(INTDIR)\YY_LEX.OBJ"
	-@erase "$(INTDIR)\YY_LEXFA.OBJ"
	-@erase "$(INTDIR)\YY_LEXRD.OBJ"
	-@erase "$(INTDIR)\YY_LEXSM.OBJ"
	-@erase "$(INTDIR)\YY_LOC.OBJ"
	-@erase "$(INTDIR)\YY_PSR.OBJ"
	-@erase "$(INTDIR)\YY_PSRFA.OBJ"
	-@erase "$(INTDIR)\YY_PSRRD.OBJ"
	-@erase "$(INTDIR)\YY_PSRSM.OBJ"
	-@erase "$(INTDIR)\Yy_signc.obj"
	-@erase "$(INTDIR)\YY_SYM.OBJ"
	-@erase "$(OUTDIR)\lol32dl.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MDd /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "__LOLDLL__" /D "STRICT" /D "PRECOMPILE" /Yu"lolpre.h" /c
CPP_PROJ=/nologo /MDd /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D\
 "__LOLDLL__" /D "STRICT" /D "PRECOMPILE" /Fp"$(INTDIR)/lol32lib.pch"\
 /Yu"lolpre.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\lol32lib\Debug/
CPP_SBRS=.\.

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/lol32lib.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"lol32lib\Debug\lol32dl.lib"
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/lol32dl.lib" 
LIB32_OBJS= \
	"$(INTDIR)\lolpre.obj" \
	"$(INTDIR)\YY_ASRT.OBJ" \
	"$(INTDIR)\YY_AST.OBJ" \
	"$(INTDIR)\YY_BUF.OBJ" \
	"$(INTDIR)\Yy_cmd.obj" \
	"$(INTDIR)\YY_ERR.OBJ" \
	"$(INTDIR)\YY_ERRGN.OBJ" \
	"$(INTDIR)\Yy_errst.obj" \
	"$(INTDIR)\Yy_help.obj" \
	"$(INTDIR)\YY_INP.OBJ" \
	"$(INTDIR)\YY_INPFI.OBJ" \
	"$(INTDIR)\YY_INPGE.OBJ" \
	"$(INTDIR)\YY_INPST.OBJ" \
	"$(INTDIR)\YY_LEX.OBJ" \
	"$(INTDIR)\YY_LEXFA.OBJ" \
	"$(INTDIR)\YY_LEXRD.OBJ" \
	"$(INTDIR)\YY_LEXSM.OBJ" \
	"$(INTDIR)\YY_LOC.OBJ" \
	"$(INTDIR)\YY_PSR.OBJ" \
	"$(INTDIR)\YY_PSRFA.OBJ" \
	"$(INTDIR)\YY_PSRRD.OBJ" \
	"$(INTDIR)\YY_PSRSM.OBJ" \
	"$(INTDIR)\Yy_signc.obj" \
	"$(INTDIR)\YY_SYM.OBJ"

"$(OUTDIR)\lol32dl.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ENDIF 

################################################################################
# Begin Target

# Name "lol32 - Win32 LOL Win32DLL Release"
# Name "lol32 - Win32 LOL Win32DLL Debug"

!IF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Release"

!ELSEIF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=\YXX20\LIB.C8\YY_ASRT.CPP
DEP_CPP_YY_AS=\
	".\..\LOLPRE.H"\
	

!IF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Release"


"$(INTDIR)\YY_ASRT.OBJ" : $(SOURCE) $(DEP_CPP_YY_AS) "$(INTDIR)"\
 "$(INTDIR)\lol32.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /Op /Ob1 /D "NDEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__LOLDLL__" /D "STRICT" /D "PRECOMPILE" /Fp"$(INTDIR)/lol32.pch"\
 /Yu"lolpre.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Debug"

# ADD CPP /Yu"lolpre.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__LOLDLL__" /D "STRICT" /D "PRECOMPILE" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/lol42.pch" /Yu"lolpre.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\YY_ASRT.OBJ" : $(SOURCE) $(DEP_CPP_YY_AS) "$(INTDIR)"\
 "$(INTDIR)\lol42.pch"
   $(BuildCmds)

"$(INTDIR)\YY_ASRT.SBR" : $(SOURCE) $(DEP_CPP_YY_AS) "$(INTDIR)"\
 "$(INTDIR)\lol42.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\YXX20\LIB.C8\YY_AST.CPP
DEP_CPP_YY_AST=\
	".\..\LOLPRE.H"\
	

!IF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Release"


"$(INTDIR)\YY_AST.OBJ" : $(SOURCE) $(DEP_CPP_YY_AST) "$(INTDIR)"\
 "$(INTDIR)\lol32.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /Op /Ob1 /D "NDEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__LOLDLL__" /D "STRICT" /D "PRECOMPILE" /Fp"$(INTDIR)/lol32.pch"\
 /Yu"lolpre.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Debug"

# ADD CPP /Yu"lolpre.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__LOLDLL__" /D "STRICT" /D "PRECOMPILE" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/lol42.pch" /Yu"lolpre.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\YY_AST.OBJ" : $(SOURCE) $(DEP_CPP_YY_AST) "$(INTDIR)"\
 "$(INTDIR)\lol42.pch"
   $(BuildCmds)

"$(INTDIR)\YY_AST.SBR" : $(SOURCE) $(DEP_CPP_YY_AST) "$(INTDIR)"\
 "$(INTDIR)\lol42.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\YXX20\LIB.C8\YY_BUF.CPP
DEP_CPP_YY_BU=\
	".\..\LOLPRE.H"\
	

!IF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Release"


"$(INTDIR)\YY_BUF.OBJ" : $(SOURCE) $(DEP_CPP_YY_BU) "$(INTDIR)"\
 "$(INTDIR)\lol32.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /Op /Ob1 /D "NDEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__LOLDLL__" /D "STRICT" /D "PRECOMPILE" /Fp"$(INTDIR)/lol32.pch"\
 /Yu"lolpre.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Debug"

# ADD CPP /Yu"lolpre.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__LOLDLL__" /D "STRICT" /D "PRECOMPILE" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/lol42.pch" /Yu"lolpre.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\YY_BUF.OBJ" : $(SOURCE) $(DEP_CPP_YY_BU) "$(INTDIR)"\
 "$(INTDIR)\lol42.pch"
   $(BuildCmds)

"$(INTDIR)\YY_BUF.SBR" : $(SOURCE) $(DEP_CPP_YY_BU) "$(INTDIR)"\
 "$(INTDIR)\lol42.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\YXX20\LIB.C8\YY_ERR.CPP
DEP_CPP_YY_ER=\
	".\..\LOLPRE.H"\
	

!IF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Release"


"$(INTDIR)\YY_ERR.OBJ" : $(SOURCE) $(DEP_CPP_YY_ER) "$(INTDIR)"\
 "$(INTDIR)\lol32.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /Op /Ob1 /D "NDEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__LOLDLL__" /D "STRICT" /D "PRECOMPILE" /Fp"$(INTDIR)/lol32.pch"\
 /Yu"lolpre.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Debug"

# ADD CPP /Yu"lolpre.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__LOLDLL__" /D "STRICT" /D "PRECOMPILE" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/lol42.pch" /Yu"lolpre.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\YY_ERR.OBJ" : $(SOURCE) $(DEP_CPP_YY_ER) "$(INTDIR)"\
 "$(INTDIR)\lol42.pch"
   $(BuildCmds)

"$(INTDIR)\YY_ERR.SBR" : $(SOURCE) $(DEP_CPP_YY_ER) "$(INTDIR)"\
 "$(INTDIR)\lol42.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\YXX20\LIB.C8\YY_INP.CPP
DEP_CPP_YY_IN=\
	".\..\LOLPRE.H"\
	

!IF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Release"


"$(INTDIR)\YY_INP.OBJ" : $(SOURCE) $(DEP_CPP_YY_IN) "$(INTDIR)"\
 "$(INTDIR)\lol32.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /Op /Ob1 /D "NDEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__LOLDLL__" /D "STRICT" /D "PRECOMPILE" /Fp"$(INTDIR)/lol32.pch"\
 /Yu"lolpre.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Debug"

# ADD CPP /Yu"lolpre.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__LOLDLL__" /D "STRICT" /D "PRECOMPILE" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/lol42.pch" /Yu"lolpre.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\YY_INP.OBJ" : $(SOURCE) $(DEP_CPP_YY_IN) "$(INTDIR)"\
 "$(INTDIR)\lol42.pch"
   $(BuildCmds)

"$(INTDIR)\YY_INP.SBR" : $(SOURCE) $(DEP_CPP_YY_IN) "$(INTDIR)"\
 "$(INTDIR)\lol42.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\YXX20\LIB.C8\YY_LEX.CPP
DEP_CPP_YY_LE=\
	".\..\LOLPRE.H"\
	

!IF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Release"


"$(INTDIR)\YY_LEX.OBJ" : $(SOURCE) $(DEP_CPP_YY_LE) "$(INTDIR)"\
 "$(INTDIR)\lol32.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /Op /Ob1 /D "NDEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__LOLDLL__" /D "STRICT" /D "PRECOMPILE" /Fp"$(INTDIR)/lol32.pch"\
 /Yu"lolpre.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Debug"

# ADD CPP /Yu"lolpre.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__LOLDLL__" /D "STRICT" /D "PRECOMPILE" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/lol42.pch" /Yu"lolpre.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\YY_LEX.OBJ" : $(SOURCE) $(DEP_CPP_YY_LE) "$(INTDIR)"\
 "$(INTDIR)\lol42.pch"
   $(BuildCmds)

"$(INTDIR)\YY_LEX.SBR" : $(SOURCE) $(DEP_CPP_YY_LE) "$(INTDIR)"\
 "$(INTDIR)\lol42.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\YXX20\LIB.C8\YY_LEXFA.CPP
DEP_CPP_YY_LEX=\
	".\..\LOLPRE.H"\
	".\..\YY_LEX.LOC"\
	

!IF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Release"


"$(INTDIR)\YY_LEXFA.OBJ" : $(SOURCE) $(DEP_CPP_YY_LEX) "$(INTDIR)"\
 "$(INTDIR)\lol32.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /Op /Ob1 /D "NDEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__LOLDLL__" /D "STRICT" /D "PRECOMPILE" /Fp"$(INTDIR)/lol32.pch"\
 /Yu"lolpre.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Debug"

# ADD CPP /Yu"lolpre.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__LOLDLL__" /D "STRICT" /D "PRECOMPILE" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/lol42.pch" /Yu"lolpre.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\YY_LEXFA.OBJ" : $(SOURCE) $(DEP_CPP_YY_LEX) "$(INTDIR)"\
 "$(INTDIR)\lol42.pch"
   $(BuildCmds)

"$(INTDIR)\YY_LEXFA.SBR" : $(SOURCE) $(DEP_CPP_YY_LEX) "$(INTDIR)"\
 "$(INTDIR)\lol42.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\YXX20\LIB.C8\YY_LEXRD.CPP
DEP_CPP_YY_LEXR=\
	".\..\LOLPRE.H"\
	".\..\YY_LEX.LOC"\
	

!IF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Release"


"$(INTDIR)\YY_LEXRD.OBJ" : $(SOURCE) $(DEP_CPP_YY_LEXR) "$(INTDIR)"\
 "$(INTDIR)\lol32.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /Op /Ob1 /D "NDEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__LOLDLL__" /D "STRICT" /D "PRECOMPILE" /Fp"$(INTDIR)/lol32.pch"\
 /Yu"lolpre.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Debug"

# ADD CPP /Yu"lolpre.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__LOLDLL__" /D "STRICT" /D "PRECOMPILE" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/lol42.pch" /Yu"lolpre.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\YY_LEXRD.OBJ" : $(SOURCE) $(DEP_CPP_YY_LEXR) "$(INTDIR)"\
 "$(INTDIR)\lol42.pch"
   $(BuildCmds)

"$(INTDIR)\YY_LEXRD.SBR" : $(SOURCE) $(DEP_CPP_YY_LEXR) "$(INTDIR)"\
 "$(INTDIR)\lol42.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\YXX20\LIB.C8\YY_LEXSM.CPP
DEP_CPP_YY_LEXS=\
	".\..\LOLPRE.H"\
	".\..\YY_LEX.LOC"\
	

!IF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Release"

# ADD CPP /O2

"$(INTDIR)\YY_LEXSM.OBJ" : $(SOURCE) $(DEP_CPP_YY_LEXS) "$(INTDIR)"\
 "$(INTDIR)\lol32.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /Op /Ob1 /D "NDEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__LOLDLL__" /D "STRICT" /D "PRECOMPILE" /Fp"$(INTDIR)/lol32.pch"\
 /Yu"lolpre.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Debug"

# ADD CPP /Yu"lolpre.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__LOLDLL__" /D "STRICT" /D "PRECOMPILE" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/lol42.pch" /Yu"lolpre.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\YY_LEXSM.OBJ" : $(SOURCE) $(DEP_CPP_YY_LEXS) "$(INTDIR)"\
 "$(INTDIR)\lol42.pch"
   $(BuildCmds)

"$(INTDIR)\YY_LEXSM.SBR" : $(SOURCE) $(DEP_CPP_YY_LEXS) "$(INTDIR)"\
 "$(INTDIR)\lol42.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\YXX20\LIB.C8\YY_PSR.CPP
DEP_CPP_YY_PS=\
	".\..\LOLPRE.H"\
	

!IF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Release"


"$(INTDIR)\YY_PSR.OBJ" : $(SOURCE) $(DEP_CPP_YY_PS) "$(INTDIR)"\
 "$(INTDIR)\lol32.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /Op /Ob1 /D "NDEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__LOLDLL__" /D "STRICT" /D "PRECOMPILE" /Fp"$(INTDIR)/lol32.pch"\
 /Yu"lolpre.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Debug"

# ADD CPP /Yu"lolpre.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__LOLDLL__" /D "STRICT" /D "PRECOMPILE" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/lol42.pch" /Yu"lolpre.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\YY_PSR.OBJ" : $(SOURCE) $(DEP_CPP_YY_PS) "$(INTDIR)"\
 "$(INTDIR)\lol42.pch"
   $(BuildCmds)

"$(INTDIR)\YY_PSR.SBR" : $(SOURCE) $(DEP_CPP_YY_PS) "$(INTDIR)"\
 "$(INTDIR)\lol42.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\YXX20\LIB.C8\YY_PSRFA.CPP
DEP_CPP_YY_PSR=\
	".\..\LOLPRE.H"\
	

!IF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Release"


"$(INTDIR)\YY_PSRFA.OBJ" : $(SOURCE) $(DEP_CPP_YY_PSR) "$(INTDIR)"\
 "$(INTDIR)\lol32.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /Op /Ob1 /D "NDEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__LOLDLL__" /D "STRICT" /D "PRECOMPILE" /Fp"$(INTDIR)/lol32.pch"\
 /Yu"lolpre.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Debug"

# ADD CPP /Yu"lolpre.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__LOLDLL__" /D "STRICT" /D "PRECOMPILE" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/lol42.pch" /Yu"lolpre.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\YY_PSRFA.OBJ" : $(SOURCE) $(DEP_CPP_YY_PSR) "$(INTDIR)"\
 "$(INTDIR)\lol42.pch"
   $(BuildCmds)

"$(INTDIR)\YY_PSRFA.SBR" : $(SOURCE) $(DEP_CPP_YY_PSR) "$(INTDIR)"\
 "$(INTDIR)\lol42.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\YXX20\LIB.C8\YY_PSRRD.CPP
DEP_CPP_YY_PSRR=\
	".\..\LOLPRE.H"\
	

!IF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Release"


"$(INTDIR)\YY_PSRRD.OBJ" : $(SOURCE) $(DEP_CPP_YY_PSRR) "$(INTDIR)"\
 "$(INTDIR)\lol32.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /Op /Ob1 /D "NDEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__LOLDLL__" /D "STRICT" /D "PRECOMPILE" /Fp"$(INTDIR)/lol32.pch"\
 /Yu"lolpre.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Debug"

# ADD CPP /Yu"lolpre.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__LOLDLL__" /D "STRICT" /D "PRECOMPILE" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/lol42.pch" /Yu"lolpre.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\YY_PSRRD.OBJ" : $(SOURCE) $(DEP_CPP_YY_PSRR) "$(INTDIR)"\
 "$(INTDIR)\lol42.pch"
   $(BuildCmds)

"$(INTDIR)\YY_PSRRD.SBR" : $(SOURCE) $(DEP_CPP_YY_PSRR) "$(INTDIR)"\
 "$(INTDIR)\lol42.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\YXX20\LIB.C8\YY_PSRSM.CPP
DEP_CPP_YY_PSRS=\
	".\..\LOLPRE.H"\
	

!IF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Release"


"$(INTDIR)\YY_PSRSM.OBJ" : $(SOURCE) $(DEP_CPP_YY_PSRS) "$(INTDIR)"\
 "$(INTDIR)\lol32.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /Op /Ob1 /D "NDEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__LOLDLL__" /D "STRICT" /D "PRECOMPILE" /Fp"$(INTDIR)/lol32.pch"\
 /Yu"lolpre.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Debug"

# ADD CPP /Yu"lolpre.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__LOLDLL__" /D "STRICT" /D "PRECOMPILE" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/lol42.pch" /Yu"lolpre.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\YY_PSRSM.OBJ" : $(SOURCE) $(DEP_CPP_YY_PSRS) "$(INTDIR)"\
 "$(INTDIR)\lol42.pch"
   $(BuildCmds)

"$(INTDIR)\YY_PSRSM.SBR" : $(SOURCE) $(DEP_CPP_YY_PSRS) "$(INTDIR)"\
 "$(INTDIR)\lol42.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\YXX20\LIB.C8\YY_SYM.CPP
DEP_CPP_YY_SY=\
	".\..\LOLPRE.H"\
	

!IF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Release"

# PROP Exclude_From_Build 0

"$(INTDIR)\YY_SYM.OBJ" : $(SOURCE) $(DEP_CPP_YY_SY) "$(INTDIR)"\
 "$(INTDIR)\lol32.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /Op /Ob1 /D "NDEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__LOLDLL__" /D "STRICT" /D "PRECOMPILE" /Fp"$(INTDIR)/lol32.pch"\
 /Yu"lolpre.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Debug"

# ADD CPP /Yu"lolpre.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__LOLDLL__" /D "STRICT" /D "PRECOMPILE" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/lol42.pch" /Yu"lolpre.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\YY_SYM.OBJ" : $(SOURCE) $(DEP_CPP_YY_SY) "$(INTDIR)"\
 "$(INTDIR)\lol42.pch"
   $(BuildCmds)

"$(INTDIR)\YY_SYM.SBR" : $(SOURCE) $(DEP_CPP_YY_SY) "$(INTDIR)"\
 "$(INTDIR)\lol42.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\YXX20\LIB.C8\YY_LOC.CPP
DEP_CPP_YY_LO=\
	".\..\LOLPRE.H"\
	

!IF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Release"


"$(INTDIR)\YY_LOC.OBJ" : $(SOURCE) $(DEP_CPP_YY_LO) "$(INTDIR)"\
 "$(INTDIR)\lol32.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /Op /Ob1 /D "NDEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__LOLDLL__" /D "STRICT" /D "PRECOMPILE" /Fp"$(INTDIR)/lol32.pch"\
 /Yu"lolpre.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Debug"

# ADD CPP /Yu"lolpre.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__LOLDLL__" /D "STRICT" /D "PRECOMPILE" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/lol42.pch" /Yu"lolpre.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\YY_LOC.OBJ" : $(SOURCE) $(DEP_CPP_YY_LO) "$(INTDIR)"\
 "$(INTDIR)\lol42.pch"
   $(BuildCmds)

"$(INTDIR)\YY_LOC.SBR" : $(SOURCE) $(DEP_CPP_YY_LO) "$(INTDIR)"\
 "$(INTDIR)\lol42.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\YXX20\LIB.C8\YY_ERRGN.CPP
DEP_CPP_YY_ERR=\
	".\..\LOLPRE.H"\
	{$(INCLUDE)}"\string"\
	

!IF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Release"


"$(INTDIR)\YY_ERRGN.OBJ" : $(SOURCE) $(DEP_CPP_YY_ERR) "$(INTDIR)"\
 "$(INTDIR)\lol32.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /Op /Ob1 /D "NDEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__LOLDLL__" /D "STRICT" /D "PRECOMPILE" /Fp"$(INTDIR)/lol32.pch"\
 /Yu"lolpre.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Debug"

# ADD CPP /Yu"lolpre.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__LOLDLL__" /D "STRICT" /D "PRECOMPILE" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/lol42.pch" /Yu"lolpre.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\YY_ERRGN.OBJ" : $(SOURCE) $(DEP_CPP_YY_ERR) "$(INTDIR)"\
 "$(INTDIR)\lol42.pch"
   $(BuildCmds)

"$(INTDIR)\YY_ERRGN.SBR" : $(SOURCE) $(DEP_CPP_YY_ERR) "$(INTDIR)"\
 "$(INTDIR)\lol42.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\YXX20\LIB.C8\YY_INPST.CPP
DEP_CPP_YY_INP=\
	".\..\LOLPRE.H"\
	

!IF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Release"


"$(INTDIR)\YY_INPST.OBJ" : $(SOURCE) $(DEP_CPP_YY_INP) "$(INTDIR)"\
 "$(INTDIR)\lol32.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /Op /Ob1 /D "NDEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__LOLDLL__" /D "STRICT" /D "PRECOMPILE" /Fp"$(INTDIR)/lol32.pch"\
 /Yu"lolpre.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Debug"

# ADD CPP /Yu"lolpre.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__LOLDLL__" /D "STRICT" /D "PRECOMPILE" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/lol42.pch" /Yu"lolpre.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\YY_INPST.OBJ" : $(SOURCE) $(DEP_CPP_YY_INP) "$(INTDIR)"\
 "$(INTDIR)\lol42.pch"
   $(BuildCmds)

"$(INTDIR)\YY_INPST.SBR" : $(SOURCE) $(DEP_CPP_YY_INP) "$(INTDIR)"\
 "$(INTDIR)\lol42.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\YXX20\LIB.C8\YY_INPGE.CPP
DEP_CPP_YY_INPG=\
	".\..\LOLPRE.H"\
	

!IF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Release"


"$(INTDIR)\YY_INPGE.OBJ" : $(SOURCE) $(DEP_CPP_YY_INPG) "$(INTDIR)"\
 "$(INTDIR)\lol32.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /Op /Ob1 /D "NDEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__LOLDLL__" /D "STRICT" /D "PRECOMPILE" /Fp"$(INTDIR)/lol32.pch"\
 /Yu"lolpre.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Debug"

# ADD CPP /Yu"lolpre.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__LOLDLL__" /D "STRICT" /D "PRECOMPILE" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/lol42.pch" /Yu"lolpre.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\YY_INPGE.OBJ" : $(SOURCE) $(DEP_CPP_YY_INPG) "$(INTDIR)"\
 "$(INTDIR)\lol42.pch"
   $(BuildCmds)

"$(INTDIR)\YY_INPGE.SBR" : $(SOURCE) $(DEP_CPP_YY_INPG) "$(INTDIR)"\
 "$(INTDIR)\lol42.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\YXX20\LIB.C8\YY_INPFI.CPP
DEP_CPP_YY_INPF=\
	".\..\LOLPRE.H"\
	

!IF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Release"


"$(INTDIR)\YY_INPFI.OBJ" : $(SOURCE) $(DEP_CPP_YY_INPF) "$(INTDIR)"\
 "$(INTDIR)\lol32.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /Op /Ob1 /D "NDEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__LOLDLL__" /D "STRICT" /D "PRECOMPILE" /Fp"$(INTDIR)/lol32.pch"\
 /Yu"lolpre.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Debug"

# ADD CPP /Yu"lolpre.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__LOLDLL__" /D "STRICT" /D "PRECOMPILE" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/lol42.pch" /Yu"lolpre.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\YY_INPFI.OBJ" : $(SOURCE) $(DEP_CPP_YY_INPF) "$(INTDIR)"\
 "$(INTDIR)\lol42.pch"
   $(BuildCmds)

"$(INTDIR)\YY_INPFI.SBR" : $(SOURCE) $(DEP_CPP_YY_INPF) "$(INTDIR)"\
 "$(INTDIR)\lol42.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\lol32.rc

!IF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Release"


"$(INTDIR)\lol32.res" : $(SOURCE) "$(INTDIR)"
   $(RSC) /l 0x407 /fo"$(INTDIR)/lol32.res" /d "NDEBUG" /d "OFFICIAL" $(SOURCE)


!ELSEIF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Debug"

# ADD BASE RSC /l 0x407
# ADD RSC /l 0x409

"$(INTDIR)\lol32.res" : $(SOURCE) "$(INTDIR)"
   $(RSC) /l 0x409 /fo"$(INTDIR)/lol32.res" /d "_DEBUG" $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\YXX20\LIB.C8\lolpre.cpp
DEP_CPP_LOLPR=\
	".\..\LOLPRE.H"\
	

!IF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Release"

# ADD CPP /Yc"lolpre.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O2 /Op /Ob1 /D "NDEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__LOLDLL__" /D "STRICT" /D "PRECOMPILE" /Fp"$(INTDIR)/lol32.pch"\
 /Yc"lolpre.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\lolpre.obj" : $(SOURCE) $(DEP_CPP_LOLPR) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\lol32.pch" : $(SOURCE) $(DEP_CPP_LOLPR) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Debug"

# ADD CPP /Yc"lolpre.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__LOLDLL__" /D "STRICT" /D "PRECOMPILE" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/lol42.pch" /Yc"lolpre.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\lolpre.obj" : $(SOURCE) $(DEP_CPP_LOLPR) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\lolpre.sbr" : $(SOURCE) $(DEP_CPP_LOLPR) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\lol42.pch" : $(SOURCE) $(DEP_CPP_LOLPR) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Lol32d.def

!IF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Debug"

# PROP Exclude_From_Build 0

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Lol32.def

!IF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Release"

!ELSEIF  "$(CFG)" == "lol32 - Win32 LOL Win32DLL Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Target
################################################################################
# Begin Target

# Name "lol32lib - Win32 Release"
# Name "lol32lib - Win32 Debug"

!IF  "$(CFG)" == "lol32lib - Win32 Release"

!ELSEIF  "$(CFG)" == "lol32lib - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=\YXX20\LIB.C8\YY_ASRT.CPP
DEP_CPP_YY_AS=\
	".\..\LOLPRE.H"\
	

"$(INTDIR)\YY_ASRT.OBJ" : $(SOURCE) $(DEP_CPP_YY_AS) "$(INTDIR)"\
 "$(INTDIR)\lol32lib.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\YXX20\LIB.C8\YY_AST.CPP
DEP_CPP_YY_AST=\
	".\..\LOLPRE.H"\
	

"$(INTDIR)\YY_AST.OBJ" : $(SOURCE) $(DEP_CPP_YY_AST) "$(INTDIR)"\
 "$(INTDIR)\lol32lib.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\YXX20\LIB.C8\YY_BUF.CPP
DEP_CPP_YY_BU=\
	".\..\LOLPRE.H"\
	

"$(INTDIR)\YY_BUF.OBJ" : $(SOURCE) $(DEP_CPP_YY_BU) "$(INTDIR)"\
 "$(INTDIR)\lol32lib.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\YXX20\LIB.C8\YY_ERR.CPP
DEP_CPP_YY_ER=\
	".\..\LOLPRE.H"\
	

"$(INTDIR)\YY_ERR.OBJ" : $(SOURCE) $(DEP_CPP_YY_ER) "$(INTDIR)"\
 "$(INTDIR)\lol32lib.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\YXX20\LIB.C8\YY_ERRGN.CPP
DEP_CPP_YY_ERR=\
	".\..\LOLPRE.H"\
	{$(INCLUDE)}"\string"\
	

"$(INTDIR)\YY_ERRGN.OBJ" : $(SOURCE) $(DEP_CPP_YY_ERR) "$(INTDIR)"\
 "$(INTDIR)\lol32lib.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Yxx20\Lib.c8\Yy_errst.cpp
DEP_CPP_YY_ERRS=\
	".\..\LOLPRE.H"\
	

"$(INTDIR)\Yy_errst.obj" : $(SOURCE) $(DEP_CPP_YY_ERRS) "$(INTDIR)"\
 "$(INTDIR)\lol32lib.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\YXX20\LIB.C8\YY_INP.CPP
DEP_CPP_YY_IN=\
	".\..\LOLPRE.H"\
	

"$(INTDIR)\YY_INP.OBJ" : $(SOURCE) $(DEP_CPP_YY_IN) "$(INTDIR)"\
 "$(INTDIR)\lol32lib.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\YXX20\LIB.C8\YY_INPFI.CPP
DEP_CPP_YY_INPF=\
	".\..\LOLPRE.H"\
	

"$(INTDIR)\YY_INPFI.OBJ" : $(SOURCE) $(DEP_CPP_YY_INPF) "$(INTDIR)"\
 "$(INTDIR)\lol32lib.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\YXX20\LIB.C8\YY_INPGE.CPP
DEP_CPP_YY_INPG=\
	".\..\LOLPRE.H"\
	

"$(INTDIR)\YY_INPGE.OBJ" : $(SOURCE) $(DEP_CPP_YY_INPG) "$(INTDIR)"\
 "$(INTDIR)\lol32lib.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\YXX20\LIB.C8\YY_INPST.CPP
DEP_CPP_YY_INP=\
	".\..\LOLPRE.H"\
	

"$(INTDIR)\YY_INPST.OBJ" : $(SOURCE) $(DEP_CPP_YY_INP) "$(INTDIR)"\
 "$(INTDIR)\lol32lib.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\YXX20\LIB.C8\YY_LEX.CPP
DEP_CPP_YY_LE=\
	".\..\LOLPRE.H"\
	

"$(INTDIR)\YY_LEX.OBJ" : $(SOURCE) $(DEP_CPP_YY_LE) "$(INTDIR)"\
 "$(INTDIR)\lol32lib.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\YXX20\LIB.C8\YY_LEXFA.CPP
DEP_CPP_YY_LEX=\
	".\..\LOLPRE.H"\
	".\..\YY_LEX.LOC"\
	

"$(INTDIR)\YY_LEXFA.OBJ" : $(SOURCE) $(DEP_CPP_YY_LEX) "$(INTDIR)"\
 "$(INTDIR)\lol32lib.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\YXX20\LIB.C8\YY_LEXRD.CPP
DEP_CPP_YY_LEXR=\
	".\..\LOLPRE.H"\
	".\..\YY_LEX.LOC"\
	

"$(INTDIR)\YY_LEXRD.OBJ" : $(SOURCE) $(DEP_CPP_YY_LEXR) "$(INTDIR)"\
 "$(INTDIR)\lol32lib.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\YXX20\LIB.C8\YY_LEXSM.CPP
DEP_CPP_YY_LEXS=\
	".\..\LOLPRE.H"\
	".\..\YY_LEX.LOC"\
	

"$(INTDIR)\YY_LEXSM.OBJ" : $(SOURCE) $(DEP_CPP_YY_LEXS) "$(INTDIR)"\
 "$(INTDIR)\lol32lib.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\YXX20\LIB.C8\YY_LOC.CPP
DEP_CPP_YY_LO=\
	".\..\LOLPRE.H"\
	

"$(INTDIR)\YY_LOC.OBJ" : $(SOURCE) $(DEP_CPP_YY_LO) "$(INTDIR)"\
 "$(INTDIR)\lol32lib.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\YXX20\LIB.C8\YY_PSR.CPP
DEP_CPP_YY_PS=\
	".\..\LOLPRE.H"\
	

"$(INTDIR)\YY_PSR.OBJ" : $(SOURCE) $(DEP_CPP_YY_PS) "$(INTDIR)"\
 "$(INTDIR)\lol32lib.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\YXX20\LIB.C8\YY_PSRFA.CPP
DEP_CPP_YY_PSR=\
	".\..\LOLPRE.H"\
	

"$(INTDIR)\YY_PSRFA.OBJ" : $(SOURCE) $(DEP_CPP_YY_PSR) "$(INTDIR)"\
 "$(INTDIR)\lol32lib.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\YXX20\LIB.C8\YY_PSRRD.CPP
DEP_CPP_YY_PSRR=\
	".\..\LOLPRE.H"\
	

"$(INTDIR)\YY_PSRRD.OBJ" : $(SOURCE) $(DEP_CPP_YY_PSRR) "$(INTDIR)"\
 "$(INTDIR)\lol32lib.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\YXX20\LIB.C8\YY_PSRSM.CPP
DEP_CPP_YY_PSRS=\
	".\..\LOLPRE.H"\
	

"$(INTDIR)\YY_PSRSM.OBJ" : $(SOURCE) $(DEP_CPP_YY_PSRS) "$(INTDIR)"\
 "$(INTDIR)\lol32lib.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\YXX20\LIB.C8\YY_SYM.CPP
DEP_CPP_YY_SY=\
	".\..\LOLPRE.H"\
	

"$(INTDIR)\YY_SYM.OBJ" : $(SOURCE) $(DEP_CPP_YY_SY) "$(INTDIR)"\
 "$(INTDIR)\lol32lib.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\YXX20\LIB.C8\lolpre.cpp
DEP_CPP_LOLPR=\
	".\..\LOLPRE.H"\
	

!IF  "$(CFG)" == "lol32lib - Win32 Release"

# ADD CPP /Yc"lolpre.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "__LOLDLL__" /D "STRICT" /D "PRECOMPILE" /Fp"$(INTDIR)/lol32lib.pch"\
 /Yc"lolpre.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\lolpre.obj" : $(SOURCE) $(DEP_CPP_LOLPR) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\lol32lib.pch" : $(SOURCE) $(DEP_CPP_LOLPR) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "lol32lib - Win32 Debug"

# ADD CPP /Yc

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D\
 "__LOLDLL__" /D "STRICT" /D "PRECOMPILE" /Fp"$(INTDIR)/lol32lib.pch" /Yc\
 /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\lolpre.obj" : $(SOURCE) $(DEP_CPP_LOLPR) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\lol32lib.pch" : $(SOURCE) $(DEP_CPP_LOLPR) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Yxx20\Lib.c8\Yy_signc.cpp
DEP_CPP_YY_SI=\
	".\..\LOLPRE.H"\
	

"$(INTDIR)\Yy_signc.obj" : $(SOURCE) $(DEP_CPP_YY_SI) "$(INTDIR)"\
 "$(INTDIR)\lol32lib.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Yxx20\Lib.c8\Yy_help.cpp
DEP_CPP_YY_HE=\
	".\..\LOLPRE.H"\
	

"$(INTDIR)\Yy_help.obj" : $(SOURCE) $(DEP_CPP_YY_HE) "$(INTDIR)"\
 "$(INTDIR)\lol32lib.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Yxx20\Lib.c8\Yy_cmd.cpp
DEP_CPP_YY_CM=\
	".\..\LOLPRE.H"\
	{$(INCLUDE)}"\yy_cmd.h"\
	

"$(INTDIR)\Yy_cmd.obj" : $(SOURCE) $(DEP_CPP_YY_CM) "$(INTDIR)"\
 "$(INTDIR)\lol32lib.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
# End Target
# End Project
################################################################################
