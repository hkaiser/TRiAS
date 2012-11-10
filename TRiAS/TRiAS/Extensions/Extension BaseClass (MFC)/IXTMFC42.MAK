# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

!IF "$(CFG)" == ""
CFG=ixtmfc32 - Win32 Debug ATL Base
!MESSAGE No configuration specified.  Defaulting to ixtmfc32 - Win32 Debug ATL\
 Base.
!ENDIF 

!IF "$(CFG)" != "ixtmfc32 - Win32 Release" && "$(CFG)" !=\
 "ixtmfc32 - Win32 Debug" && "$(CFG)" != "ixtmfc32 - Win32 Release New" &&\
 "$(CFG)" != "ixtmfc32 - Win32 Debug New" && "$(CFG)" !=\
 "ixtmfc32 - Win32 Debug ATL Base" && "$(CFG)" !=\
 "ixtmfc32 - Win32 Release ATL Base"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "IXTMFC42.MAK" CFG="ixtmfc32 - Win32 Debug ATL Base"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ixtmfc32 - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "ixtmfc32 - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "ixtmfc32 - Win32 Release New" (based on "Win32 (x86) Static Library")
!MESSAGE "ixtmfc32 - Win32 Debug New" (based on "Win32 (x86) Static Library")
!MESSAGE "ixtmfc32 - Win32 Debug ATL Base" (based on\
 "Win32 (x86) Static Library")
!MESSAGE "ixtmfc32 - Win32 Release ATL Base" (based on\
 "Win32 (x86) Static Library")
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
# PROP Target_Last_Scanned "ixtmfc32 - Win32 Release ATL Base"
CPP=cl.exe

!IF  "$(CFG)" == "ixtmfc32 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Mfc32/Release"
# PROP Intermediate_Dir "Mfc32/Release"
OUTDIR=.\Mfc32/Release
INTDIR=.\Mfc32/Release
# Begin Custom Macros
TargetName=ixtmfr40
# End Custom Macros

ALL : "$(OUTDIR)\ixtmfr40.lib" "..\..\lib32\ixtmfr40.lib"

CLEAN : 
	-@erase "$(INTDIR)\cimpxtsn.obj"
	-@erase "$(INTDIR)\Ctfxmfc.obj"
	-@erase "$(INTDIR)\dllbindx.obj"
	-@erase "$(INTDIR)\dummy1.obj"
	-@erase "$(INTDIR)\dummy2.obj"
	-@erase "$(INTDIR)\dummy3.obj"
	-@erase "$(INTDIR)\DUMMY4.OBJ"
	-@erase "$(INTDIR)\dummy5.obj"
	-@erase "$(INTDIR)\enmcprop.obj"
	-@erase "$(INTDIR)\enumprop.obj"
	-@erase "$(INTDIR)\EXTREG.OBJ"
	-@erase "$(INTDIR)\Hdrentrx.obj"
	-@erase "$(INTDIR)\IENUMONR.OBJ"
	-@erase "$(INTDIR)\IMPXTCF.OBJ"
	-@erase "$(INTDIR)\IXTMFC42.pch"
	-@erase "$(INTDIR)\OBJCONTX.OBJ"
	-@erase "$(INTDIR)\objpropf.obj"
	-@erase "$(INTDIR)\REGISTRY.OBJ"
	-@erase "$(INTDIR)\STRUTIL.OBJ"
	-@erase "$(INTDIR)\Xtencunk.obj"
	-@erase "$(INTDIR)\XTENSNP.OBJ"
	-@erase "$(INTDIR)\xtsnatl.obj"
	-@erase "$(INTDIR)\xtsnimp.obj"
	-@erase "$(INTDIR)\xtsnprop.obj"
	-@erase "$(OUTDIR)\ixtmfr40.lib"
	-@erase "..\..\lib32\ixtmfr40.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

.\WinRel\ixtmfc32.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "__XTENSNDLL__" /D "__MFC__" /D "_AFXEXT" /D "_AFXDLL" /D "_MBCS" /D "__ATL_USED__" /D "__ATL_11_USED__" /D "OS_NO_STREAM_SUPPORT" /Yu"xtensnp.hxx" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DEXPROCS" /D "MSWIND" /D "__XTENSNDLL__" /D "__MFC__" /D "_AFXEXT"\
 /D "_AFXDLL" /D "_MBCS" /D "__ATL_USED__" /D "__ATL_11_USED__" /D\
 "OS_NO_STREAM_SUPPORT" /Fp"$(INTDIR)/IXTMFC42.pch" /Yu"xtensnp.hxx"\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Mfc32/Release/
CPP_SBRS=.\.
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/IXTMFC42.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"Mfc32/Release\ixtmfr40.lib"
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/ixtmfr40.lib" 
LIB32_OBJS= \
	"$(INTDIR)\cimpxtsn.obj" \
	"$(INTDIR)\Ctfxmfc.obj" \
	"$(INTDIR)\dllbindx.obj" \
	"$(INTDIR)\dummy1.obj" \
	"$(INTDIR)\dummy2.obj" \
	"$(INTDIR)\dummy3.obj" \
	"$(INTDIR)\DUMMY4.OBJ" \
	"$(INTDIR)\dummy5.obj" \
	"$(INTDIR)\enmcprop.obj" \
	"$(INTDIR)\enumprop.obj" \
	"$(INTDIR)\EXTREG.OBJ" \
	"$(INTDIR)\Hdrentrx.obj" \
	"$(INTDIR)\IENUMONR.OBJ" \
	"$(INTDIR)\IMPXTCF.OBJ" \
	"$(INTDIR)\OBJCONTX.OBJ" \
	"$(INTDIR)\objpropf.obj" \
	"$(INTDIR)\REGISTRY.OBJ" \
	"$(INTDIR)\STRUTIL.OBJ" \
	"$(INTDIR)\Xtencunk.obj" \
	"$(INTDIR)\XTENSNP.OBJ" \
	"$(INTDIR)\xtsnatl.obj" \
	"$(INTDIR)\xtsnimp.obj" \
	"$(INTDIR)\xtsnprop.obj"

"$(OUTDIR)\ixtmfr40.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

# Begin Custom Build - Copying created library ...
TargetPath=.\Mfc32\Release\ixtmfr40.lib
TargetName=ixtmfr40
InputPath=.\Mfc32\Release\ixtmfr40.lib
SOURCE=$(InputPath)

"\triasdev.mvc\lib32\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   copy "$(TargetPath)" \triasdev.mvc\lib32

# End Custom Build

!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Mfc32/Debug"
# PROP Intermediate_Dir "Mfc32/Debug"
OUTDIR=.\Mfc32/Debug
INTDIR=.\Mfc32/Debug
# Begin Custom Macros
TargetName=ixtmfd40
# End Custom Macros

ALL : "$(OUTDIR)\ixtmfd40.lib" "$(OUTDIR)\IXTMFC42.bsc"\
 "..\..\lib32\ixtmfd40.lib"

CLEAN : 
	-@erase "$(INTDIR)\cimpxtsn.obj"
	-@erase "$(INTDIR)\cimpxtsn.sbr"
	-@erase "$(INTDIR)\Ctfxmfc.obj"
	-@erase "$(INTDIR)\Ctfxmfc.sbr"
	-@erase "$(INTDIR)\dllbindx.obj"
	-@erase "$(INTDIR)\dllbindx.sbr"
	-@erase "$(INTDIR)\dummy1.obj"
	-@erase "$(INTDIR)\dummy1.sbr"
	-@erase "$(INTDIR)\dummy2.obj"
	-@erase "$(INTDIR)\dummy2.sbr"
	-@erase "$(INTDIR)\dummy3.obj"
	-@erase "$(INTDIR)\dummy3.sbr"
	-@erase "$(INTDIR)\DUMMY4.OBJ"
	-@erase "$(INTDIR)\DUMMY4.SBR"
	-@erase "$(INTDIR)\dummy5.obj"
	-@erase "$(INTDIR)\dummy5.sbr"
	-@erase "$(INTDIR)\enmcprop.obj"
	-@erase "$(INTDIR)\enmcprop.sbr"
	-@erase "$(INTDIR)\enumprop.obj"
	-@erase "$(INTDIR)\enumprop.sbr"
	-@erase "$(INTDIR)\EXTREG.OBJ"
	-@erase "$(INTDIR)\EXTREG.SBR"
	-@erase "$(INTDIR)\Hdrentrx.obj"
	-@erase "$(INTDIR)\Hdrentrx.sbr"
	-@erase "$(INTDIR)\IENUMONR.OBJ"
	-@erase "$(INTDIR)\IENUMONR.SBR"
	-@erase "$(INTDIR)\IMPXTCF.OBJ"
	-@erase "$(INTDIR)\IMPXTCF.SBR"
	-@erase "$(INTDIR)\IXTMFC42.pch"
	-@erase "$(INTDIR)\ixtmfd40.idb"
	-@erase "$(INTDIR)\ixtmfd40.pdb"
	-@erase "$(INTDIR)\OBJCONTX.OBJ"
	-@erase "$(INTDIR)\OBJCONTX.SBR"
	-@erase "$(INTDIR)\objpropf.obj"
	-@erase "$(INTDIR)\objpropf.sbr"
	-@erase "$(INTDIR)\REGISTRY.OBJ"
	-@erase "$(INTDIR)\REGISTRY.SBR"
	-@erase "$(INTDIR)\STRUTIL.OBJ"
	-@erase "$(INTDIR)\STRUTIL.SBR"
	-@erase "$(INTDIR)\Xtencunk.obj"
	-@erase "$(INTDIR)\Xtencunk.sbr"
	-@erase "$(INTDIR)\XTENSNP.OBJ"
	-@erase "$(INTDIR)\XTENSNP.SBR"
	-@erase "$(INTDIR)\xtsnatl.obj"
	-@erase "$(INTDIR)\xtsnatl.sbr"
	-@erase "$(INTDIR)\xtsnimp.obj"
	-@erase "$(INTDIR)\xtsnimp.sbr"
	-@erase "$(INTDIR)\xtsnprop.obj"
	-@erase "$(INTDIR)\xtsnprop.sbr"
	-@erase "$(OUTDIR)\IXTMFC42.bsc"
	-@erase "$(OUTDIR)\ixtmfd40.lib"
	-@erase "..\..\lib32\ixtmfd40.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

.\WinDebug\ixtmfc32.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "__XTENSNDLL__" /D "__MFC__" /D "_AFXEXT" /D "_AFXDLL" /D "_MBCS" /D "__ATL_USED__" /D "__ATL_11_USED__" /D "OS_NO_STREAM_SUPPORT" /FR /Yu"xtensnp.hxx" /Fd"Mfc32/Debug/ixtmfd40.pdb" /c
CPP_PROJ=/nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "__XTENSNDLL__" /D\
 "__MFC__" /D "_AFXEXT" /D "_AFXDLL" /D "_MBCS" /D "__ATL_USED__" /D\
 "__ATL_11_USED__" /D "OS_NO_STREAM_SUPPORT" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/IXTMFC42.pch" /Yu"xtensnp.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/ixtmfd40.pdb" /c 
CPP_OBJS=.\Mfc32/Debug/
CPP_SBRS=.\Mfc32/Debug/
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/IXTMFC42.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\cimpxtsn.sbr" \
	"$(INTDIR)\Ctfxmfc.sbr" \
	"$(INTDIR)\dllbindx.sbr" \
	"$(INTDIR)\dummy1.sbr" \
	"$(INTDIR)\dummy2.sbr" \
	"$(INTDIR)\dummy3.sbr" \
	"$(INTDIR)\DUMMY4.SBR" \
	"$(INTDIR)\dummy5.sbr" \
	"$(INTDIR)\enmcprop.sbr" \
	"$(INTDIR)\enumprop.sbr" \
	"$(INTDIR)\EXTREG.SBR" \
	"$(INTDIR)\Hdrentrx.sbr" \
	"$(INTDIR)\IENUMONR.SBR" \
	"$(INTDIR)\IMPXTCF.SBR" \
	"$(INTDIR)\OBJCONTX.SBR" \
	"$(INTDIR)\objpropf.sbr" \
	"$(INTDIR)\REGISTRY.SBR" \
	"$(INTDIR)\STRUTIL.SBR" \
	"$(INTDIR)\Xtencunk.sbr" \
	"$(INTDIR)\XTENSNP.SBR" \
	"$(INTDIR)\xtsnatl.sbr" \
	"$(INTDIR)\xtsnimp.sbr" \
	"$(INTDIR)\xtsnprop.sbr"

"$(OUTDIR)\IXTMFC42.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"Mfc32/Debug\ixtmfd40.lib"
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/ixtmfd40.lib" 
LIB32_OBJS= \
	"$(INTDIR)\cimpxtsn.obj" \
	"$(INTDIR)\Ctfxmfc.obj" \
	"$(INTDIR)\dllbindx.obj" \
	"$(INTDIR)\dummy1.obj" \
	"$(INTDIR)\dummy2.obj" \
	"$(INTDIR)\dummy3.obj" \
	"$(INTDIR)\DUMMY4.OBJ" \
	"$(INTDIR)\dummy5.obj" \
	"$(INTDIR)\enmcprop.obj" \
	"$(INTDIR)\enumprop.obj" \
	"$(INTDIR)\EXTREG.OBJ" \
	"$(INTDIR)\Hdrentrx.obj" \
	"$(INTDIR)\IENUMONR.OBJ" \
	"$(INTDIR)\IMPXTCF.OBJ" \
	"$(INTDIR)\OBJCONTX.OBJ" \
	"$(INTDIR)\objpropf.obj" \
	"$(INTDIR)\REGISTRY.OBJ" \
	"$(INTDIR)\STRUTIL.OBJ" \
	"$(INTDIR)\Xtencunk.obj" \
	"$(INTDIR)\XTENSNP.OBJ" \
	"$(INTDIR)\xtsnatl.obj" \
	"$(INTDIR)\xtsnimp.obj" \
	"$(INTDIR)\xtsnprop.obj"

"$(OUTDIR)\ixtmfd40.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

# Begin Custom Build - Copying created library ...
OutDir=.\Mfc32/Debug
TargetPath=.\Mfc32\Debug\ixtmfd40.lib
TargetName=ixtmfd40
InputPath=.\Mfc32\Debug\ixtmfd40.lib
SOURCE=$(InputPath)

"\triasdev.mvc\lib32\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   copy "$(TargetPath)" \triasdev.mvc\lib32
   if exist "$(OutDir)\$(TargetName).pdb" copy "$(OutDir)\$(TargetName).pdb"

# End Custom Build

!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Release New"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ixtmfc32"
# PROP BASE Intermediate_Dir "ixtmfc32"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Mfc42/Release"
# PROP Intermediate_Dir "Mfc42/Release"
# PROP Target_Dir ""
OUTDIR=.\Mfc42/Release
INTDIR=.\Mfc42/Release
# Begin Custom Macros
TargetName=ixtmfr42
# End Custom Macros

ALL : "$(OUTDIR)\ixtmfr42.lib" "..\..\lib32\ixtmfr42.lib"

CLEAN : 
	-@erase "$(INTDIR)\cimpxtsn.obj"
	-@erase "$(INTDIR)\Ctfxmfc.obj"
	-@erase "$(INTDIR)\dllbindx.obj"
	-@erase "$(INTDIR)\dummy1.obj"
	-@erase "$(INTDIR)\dummy2.obj"
	-@erase "$(INTDIR)\dummy3.obj"
	-@erase "$(INTDIR)\DUMMY4.OBJ"
	-@erase "$(INTDIR)\dummy5.obj"
	-@erase "$(INTDIR)\enmcprop.obj"
	-@erase "$(INTDIR)\enumprop.obj"
	-@erase "$(INTDIR)\EXTREG.OBJ"
	-@erase "$(INTDIR)\Hdrentrx.obj"
	-@erase "$(INTDIR)\IENUMONR.OBJ"
	-@erase "$(INTDIR)\IMPXTCF.OBJ"
	-@erase "$(INTDIR)\IXTMFC42.pch"
	-@erase "$(INTDIR)\OBJCONTX.OBJ"
	-@erase "$(INTDIR)\objpropf.obj"
	-@erase "$(INTDIR)\REGISTRY.OBJ"
	-@erase "$(INTDIR)\STRUTIL.OBJ"
	-@erase "$(INTDIR)\Xtencunk.obj"
	-@erase "$(INTDIR)\XTENSNP.OBJ"
	-@erase "$(INTDIR)\xtsnatl.obj"
	-@erase "$(INTDIR)\xtsnimp.obj"
	-@erase "$(INTDIR)\xtsnprop.obj"
	-@erase "$(OUTDIR)\ixtmfr42.lib"
	-@erase "..\..\lib32\ixtmfr42.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "__XTENSNDLL__" /D "_AFXEXT" /D "__MFC__" /D "_AFXDLL" /D "_MBCS" /D "__ATL_USED__" /Yu"xtensnp.hxx" /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "__XTENSNDLL__" /D "__MFC__" /D "_AFXEXT" /D "_AFXDLL" /D "_MBCS" /D "__ATL_USED__" /D "__ATL_11_USED__" /D "OS_NO_STREAM_SUPPORT" /Yu"xtensnp.hxx" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DEXPROCS" /D "MSWIND" /D "__XTENSNDLL__" /D "__MFC__" /D "_AFXEXT"\
 /D "_AFXDLL" /D "_MBCS" /D "__ATL_USED__" /D "__ATL_11_USED__" /D\
 "OS_NO_STREAM_SUPPORT" /Fp"$(INTDIR)/IXTMFC42.pch" /Yu"xtensnp.hxx"\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Mfc42/Release/
CPP_SBRS=.\.
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/IXTMFC42.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"Mfc32/Release\ixtmfr40.lib"
# ADD LIB32 /nologo /out:"Mfc42/Release\ixtmfr42.lib"
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/ixtmfr42.lib" 
LIB32_OBJS= \
	"$(INTDIR)\cimpxtsn.obj" \
	"$(INTDIR)\Ctfxmfc.obj" \
	"$(INTDIR)\dllbindx.obj" \
	"$(INTDIR)\dummy1.obj" \
	"$(INTDIR)\dummy2.obj" \
	"$(INTDIR)\dummy3.obj" \
	"$(INTDIR)\DUMMY4.OBJ" \
	"$(INTDIR)\dummy5.obj" \
	"$(INTDIR)\enmcprop.obj" \
	"$(INTDIR)\enumprop.obj" \
	"$(INTDIR)\EXTREG.OBJ" \
	"$(INTDIR)\Hdrentrx.obj" \
	"$(INTDIR)\IENUMONR.OBJ" \
	"$(INTDIR)\IMPXTCF.OBJ" \
	"$(INTDIR)\OBJCONTX.OBJ" \
	"$(INTDIR)\objpropf.obj" \
	"$(INTDIR)\REGISTRY.OBJ" \
	"$(INTDIR)\STRUTIL.OBJ" \
	"$(INTDIR)\Xtencunk.obj" \
	"$(INTDIR)\XTENSNP.OBJ" \
	"$(INTDIR)\xtsnatl.obj" \
	"$(INTDIR)\xtsnimp.obj" \
	"$(INTDIR)\xtsnprop.obj"

"$(OUTDIR)\ixtmfr42.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

# Begin Custom Build - Copying created library ...
TargetPath=.\Mfc42\Release\ixtmfr42.lib
TargetName=ixtmfr42
InputPath=.\Mfc42\Release\ixtmfr42.lib
SOURCE=$(InputPath)

"\triasdev.mvc\lib32\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   copy "$(TargetPath)" \triasdev.mvc\lib32

# End Custom Build

!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug New"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ixtmfc30"
# PROP BASE Intermediate_Dir "ixtmfc30"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Mfc42/Debug"
# PROP Intermediate_Dir "Mfc42/Debug"
# PROP Target_Dir ""
OUTDIR=.\Mfc42/Debug
INTDIR=.\Mfc42/Debug
# Begin Custom Macros
TargetName=ixtmfd42
# End Custom Macros

ALL : "$(OUTDIR)\ixtmfd42.lib" "$(OUTDIR)\IXTMFC42.bsc"\
 "..\..\lib32\ixtmfd42.lib"

CLEAN : 
	-@erase "$(INTDIR)\cimpxtsn.obj"
	-@erase "$(INTDIR)\cimpxtsn.sbr"
	-@erase "$(INTDIR)\Ctfxmfc.obj"
	-@erase "$(INTDIR)\Ctfxmfc.sbr"
	-@erase "$(INTDIR)\dllbindx.obj"
	-@erase "$(INTDIR)\dllbindx.sbr"
	-@erase "$(INTDIR)\dummy1.obj"
	-@erase "$(INTDIR)\dummy1.sbr"
	-@erase "$(INTDIR)\dummy2.obj"
	-@erase "$(INTDIR)\dummy2.sbr"
	-@erase "$(INTDIR)\dummy3.obj"
	-@erase "$(INTDIR)\dummy3.sbr"
	-@erase "$(INTDIR)\DUMMY4.OBJ"
	-@erase "$(INTDIR)\DUMMY4.SBR"
	-@erase "$(INTDIR)\dummy5.obj"
	-@erase "$(INTDIR)\dummy5.sbr"
	-@erase "$(INTDIR)\enmcprop.obj"
	-@erase "$(INTDIR)\enmcprop.sbr"
	-@erase "$(INTDIR)\enumprop.obj"
	-@erase "$(INTDIR)\enumprop.sbr"
	-@erase "$(INTDIR)\EXTREG.OBJ"
	-@erase "$(INTDIR)\EXTREG.SBR"
	-@erase "$(INTDIR)\Hdrentrx.obj"
	-@erase "$(INTDIR)\Hdrentrx.sbr"
	-@erase "$(INTDIR)\IENUMONR.OBJ"
	-@erase "$(INTDIR)\IENUMONR.SBR"
	-@erase "$(INTDIR)\IMPXTCF.OBJ"
	-@erase "$(INTDIR)\IMPXTCF.SBR"
	-@erase "$(INTDIR)\IXTMFC42.pch"
	-@erase "$(INTDIR)\ixtmfd42.idb"
	-@erase "$(INTDIR)\ixtmfd42.pdb"
	-@erase "$(INTDIR)\OBJCONTX.OBJ"
	-@erase "$(INTDIR)\OBJCONTX.SBR"
	-@erase "$(INTDIR)\objpropf.obj"
	-@erase "$(INTDIR)\objpropf.sbr"
	-@erase "$(INTDIR)\REGISTRY.OBJ"
	-@erase "$(INTDIR)\REGISTRY.SBR"
	-@erase "$(INTDIR)\STRUTIL.OBJ"
	-@erase "$(INTDIR)\STRUTIL.SBR"
	-@erase "$(INTDIR)\Xtencunk.obj"
	-@erase "$(INTDIR)\Xtencunk.sbr"
	-@erase "$(INTDIR)\XTENSNP.OBJ"
	-@erase "$(INTDIR)\XTENSNP.SBR"
	-@erase "$(INTDIR)\xtsnatl.obj"
	-@erase "$(INTDIR)\xtsnatl.sbr"
	-@erase "$(INTDIR)\xtsnimp.obj"
	-@erase "$(INTDIR)\xtsnimp.sbr"
	-@erase "$(INTDIR)\xtsnprop.obj"
	-@erase "$(INTDIR)\xtsnprop.sbr"
	-@erase "$(OUTDIR)\IXTMFC42.bsc"
	-@erase "$(OUTDIR)\ixtmfd42.lib"
	-@erase "..\..\lib32\ixtmfd42.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "__XTENSNDLL__" /D "__MFC__" /D "_AFXEXT" /D "_AFXDLL" /D "_MBCS" /D "__ATL_USED__" /FR /Yu"xtensnp.hxx" /Fd"Mfc32/Debug/ixtmfd40.pdb" /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "__XTENSNDLL__" /D "__MFC__" /D "_AFXEXT" /D "_AFXDLL" /D "_MBCS" /D "__ATL_USED__" /D "__ATL_11_USED__" /D "OS_NO_STREAM_SUPPORT" /FR /Yu"xtensnp.hxx" /Fd"Mfc42/Debug/ixtmfd42.pdb" /c
CPP_PROJ=/nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "__XTENSNDLL__" /D\
 "__MFC__" /D "_AFXEXT" /D "_AFXDLL" /D "_MBCS" /D "__ATL_USED__" /D\
 "__ATL_11_USED__" /D "OS_NO_STREAM_SUPPORT" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/IXTMFC42.pch" /Yu"xtensnp.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/ixtmfd42.pdb" /c 
CPP_OBJS=.\Mfc42/Debug/
CPP_SBRS=.\Mfc42/Debug/
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/IXTMFC42.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\cimpxtsn.sbr" \
	"$(INTDIR)\Ctfxmfc.sbr" \
	"$(INTDIR)\dllbindx.sbr" \
	"$(INTDIR)\dummy1.sbr" \
	"$(INTDIR)\dummy2.sbr" \
	"$(INTDIR)\dummy3.sbr" \
	"$(INTDIR)\DUMMY4.SBR" \
	"$(INTDIR)\dummy5.sbr" \
	"$(INTDIR)\enmcprop.sbr" \
	"$(INTDIR)\enumprop.sbr" \
	"$(INTDIR)\EXTREG.SBR" \
	"$(INTDIR)\Hdrentrx.sbr" \
	"$(INTDIR)\IENUMONR.SBR" \
	"$(INTDIR)\IMPXTCF.SBR" \
	"$(INTDIR)\OBJCONTX.SBR" \
	"$(INTDIR)\objpropf.sbr" \
	"$(INTDIR)\REGISTRY.SBR" \
	"$(INTDIR)\STRUTIL.SBR" \
	"$(INTDIR)\Xtencunk.sbr" \
	"$(INTDIR)\XTENSNP.SBR" \
	"$(INTDIR)\xtsnatl.sbr" \
	"$(INTDIR)\xtsnimp.sbr" \
	"$(INTDIR)\xtsnprop.sbr"

"$(OUTDIR)\IXTMFC42.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"Mfc32/Debug\ixtmfd40.lib"
# ADD LIB32 /nologo /out:"Mfc42/Debug\ixtmfd42.lib"
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/ixtmfd42.lib" 
LIB32_OBJS= \
	"$(INTDIR)\cimpxtsn.obj" \
	"$(INTDIR)\Ctfxmfc.obj" \
	"$(INTDIR)\dllbindx.obj" \
	"$(INTDIR)\dummy1.obj" \
	"$(INTDIR)\dummy2.obj" \
	"$(INTDIR)\dummy3.obj" \
	"$(INTDIR)\DUMMY4.OBJ" \
	"$(INTDIR)\dummy5.obj" \
	"$(INTDIR)\enmcprop.obj" \
	"$(INTDIR)\enumprop.obj" \
	"$(INTDIR)\EXTREG.OBJ" \
	"$(INTDIR)\Hdrentrx.obj" \
	"$(INTDIR)\IENUMONR.OBJ" \
	"$(INTDIR)\IMPXTCF.OBJ" \
	"$(INTDIR)\OBJCONTX.OBJ" \
	"$(INTDIR)\objpropf.obj" \
	"$(INTDIR)\REGISTRY.OBJ" \
	"$(INTDIR)\STRUTIL.OBJ" \
	"$(INTDIR)\Xtencunk.obj" \
	"$(INTDIR)\XTENSNP.OBJ" \
	"$(INTDIR)\xtsnatl.obj" \
	"$(INTDIR)\xtsnimp.obj" \
	"$(INTDIR)\xtsnprop.obj"

"$(OUTDIR)\ixtmfd42.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

# Begin Custom Build - Copying created library ...
OutDir=.\Mfc42/Debug
TargetPath=.\Mfc42\Debug\ixtmfd42.lib
TargetName=ixtmfd42
InputPath=.\Mfc42\Debug\ixtmfd42.lib
SOURCE=$(InputPath)

"\triasdev.mvc\lib32\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   copy "$(TargetPath)" \triasdev.mvc\lib32
   if exist "$(OutDir)\$(TargetName).pdb" copy "$(OutDir)\$(TargetName).pdb"

# End Custom Build

!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug ATL Base"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ixtmfc32"
# PROP BASE Intermediate_Dir "ixtmfc32"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "MfcAtl/Debug"
# PROP Intermediate_Dir "MfcAtl/Debug"
# PROP Target_Dir ""
OUTDIR=.\MfcAtl/Debug
INTDIR=.\MfcAtl/Debug
# Begin Custom Macros
TargetName=ixtmad42
# End Custom Macros

ALL : "$(OUTDIR)\ixtmad42.lib" "$(OUTDIR)\IXTMAD42.bsc"\
 "..\..\lib32\ixtmad42.lib"

CLEAN : 
	-@erase "$(INTDIR)\Ctfxmfc.obj"
	-@erase "$(INTDIR)\Ctfxmfc.sbr"
	-@erase "$(INTDIR)\dllbindx.obj"
	-@erase "$(INTDIR)\dllbindx.sbr"
	-@erase "$(INTDIR)\dummy1.obj"
	-@erase "$(INTDIR)\dummy1.sbr"
	-@erase "$(INTDIR)\dummy2.obj"
	-@erase "$(INTDIR)\dummy2.sbr"
	-@erase "$(INTDIR)\dummy3.obj"
	-@erase "$(INTDIR)\dummy3.sbr"
	-@erase "$(INTDIR)\DUMMY4.OBJ"
	-@erase "$(INTDIR)\DUMMY4.SBR"
	-@erase "$(INTDIR)\enmcprop.obj"
	-@erase "$(INTDIR)\enmcprop.sbr"
	-@erase "$(INTDIR)\enumprop.obj"
	-@erase "$(INTDIR)\enumprop.sbr"
	-@erase "$(INTDIR)\EXTREG.OBJ"
	-@erase "$(INTDIR)\EXTREG.SBR"
	-@erase "$(INTDIR)\Hdrentrx.obj"
	-@erase "$(INTDIR)\Hdrentrx.sbr"
	-@erase "$(INTDIR)\IENUMONR.OBJ"
	-@erase "$(INTDIR)\IENUMONR.SBR"
	-@erase "$(INTDIR)\ixtmad42.idb"
	-@erase "$(INTDIR)\IXTMAD42.pch"
	-@erase "$(INTDIR)\ixtmad42.pdb"
	-@erase "$(INTDIR)\OBJCONTX.OBJ"
	-@erase "$(INTDIR)\OBJCONTX.SBR"
	-@erase "$(INTDIR)\objpropf.obj"
	-@erase "$(INTDIR)\objpropf.sbr"
	-@erase "$(INTDIR)\REGISTRY.OBJ"
	-@erase "$(INTDIR)\REGISTRY.SBR"
	-@erase "$(INTDIR)\STRUTIL.OBJ"
	-@erase "$(INTDIR)\STRUTIL.SBR"
	-@erase "$(INTDIR)\XtencAtl.obj"
	-@erase "$(INTDIR)\XtencAtl.sbr"
	-@erase "$(INTDIR)\XTENSNP.OBJ"
	-@erase "$(INTDIR)\XTENSNP.SBR"
	-@erase "$(INTDIR)\xtsnatl.obj"
	-@erase "$(INTDIR)\xtsnatl.sbr"
	-@erase "$(INTDIR)\xtsnimp.obj"
	-@erase "$(INTDIR)\xtsnimp.sbr"
	-@erase "$(INTDIR)\XtsnPropAtl.obj"
	-@erase "$(INTDIR)\XtsnPropAtl.sbr"
	-@erase "$(OUTDIR)\IXTMAD42.bsc"
	-@erase "$(OUTDIR)\ixtmad42.lib"
	-@erase "..\..\lib32\ixtmad42.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "__XTENSNDLL__" /D "__MFC__" /D "_AFXEXT" /D "_AFXDLL" /D "_MBCS" /D "__ATL_USED__" /D "__ATL_11_USED__" /FR /Yu"xtensnp.hxx" /Fd"Mfc42/Debug/ixtmfd42.pdb" /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "__ATL_XTENSION_BASE__" /D "WIN32" /D "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "__XTENSNDLL__" /D "__MFC__" /D "_AFXEXT" /D "_AFXDLL" /D "_MBCS" /D "__ATL_USED__" /D "__ATL_11_USED__" /D "OS_NO_STREAM_SUPPORT" /FR /Fp"MfcAtl/Debug/IXTMAD42.pch" /Yu"xtensnp.hxx" /Fd"MfcAtl/Debug/ixtmad42.pdb" /c
CPP_PROJ=/nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D\
 "__ATL_XTENSION_BASE__" /D "WIN32" /D "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D\
 "MSWIND" /D "__XTENSNDLL__" /D "__MFC__" /D "_AFXEXT" /D "_AFXDLL" /D "_MBCS"\
 /D "__ATL_USED__" /D "__ATL_11_USED__" /D "OS_NO_STREAM_SUPPORT"\
 /FR"$(INTDIR)/" /Fp"$(INTDIR)/IXTMAD42.pch" /Yu"xtensnp.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/ixtmad42.pdb" /c 
CPP_OBJS=.\MfcAtl/Debug/
CPP_SBRS=.\MfcAtl/Debug/
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"MfcAtl/Debug/IXTMAD42.bsc"
BSC32_FLAGS=/nologo /o"$(OUTDIR)/IXTMAD42.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Ctfxmfc.sbr" \
	"$(INTDIR)\dllbindx.sbr" \
	"$(INTDIR)\dummy1.sbr" \
	"$(INTDIR)\dummy2.sbr" \
	"$(INTDIR)\dummy3.sbr" \
	"$(INTDIR)\DUMMY4.SBR" \
	"$(INTDIR)\enmcprop.sbr" \
	"$(INTDIR)\enumprop.sbr" \
	"$(INTDIR)\EXTREG.SBR" \
	"$(INTDIR)\Hdrentrx.sbr" \
	"$(INTDIR)\IENUMONR.SBR" \
	"$(INTDIR)\OBJCONTX.SBR" \
	"$(INTDIR)\objpropf.sbr" \
	"$(INTDIR)\REGISTRY.SBR" \
	"$(INTDIR)\STRUTIL.SBR" \
	"$(INTDIR)\XtencAtl.sbr" \
	"$(INTDIR)\XTENSNP.SBR" \
	"$(INTDIR)\xtsnatl.sbr" \
	"$(INTDIR)\xtsnimp.sbr" \
	"$(INTDIR)\XtsnPropAtl.sbr"

"$(OUTDIR)\IXTMAD42.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"Mfc42/Debug\ixtmfd42.lib"
# ADD LIB32 /nologo /out:"MfcAtl/Debug\ixtmad42.lib"
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/ixtmad42.lib" 
LIB32_OBJS= \
	"$(INTDIR)\Ctfxmfc.obj" \
	"$(INTDIR)\dllbindx.obj" \
	"$(INTDIR)\dummy1.obj" \
	"$(INTDIR)\dummy2.obj" \
	"$(INTDIR)\dummy3.obj" \
	"$(INTDIR)\DUMMY4.OBJ" \
	"$(INTDIR)\enmcprop.obj" \
	"$(INTDIR)\enumprop.obj" \
	"$(INTDIR)\EXTREG.OBJ" \
	"$(INTDIR)\Hdrentrx.obj" \
	"$(INTDIR)\IENUMONR.OBJ" \
	"$(INTDIR)\OBJCONTX.OBJ" \
	"$(INTDIR)\objpropf.obj" \
	"$(INTDIR)\REGISTRY.OBJ" \
	"$(INTDIR)\STRUTIL.OBJ" \
	"$(INTDIR)\XtencAtl.obj" \
	"$(INTDIR)\XTENSNP.OBJ" \
	"$(INTDIR)\xtsnatl.obj" \
	"$(INTDIR)\xtsnimp.obj" \
	"$(INTDIR)\XtsnPropAtl.obj"

"$(OUTDIR)\ixtmad42.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

# Begin Custom Build - Copying created library ...
OutDir=.\MfcAtl/Debug
TargetPath=.\MfcAtl\Debug\ixtmad42.lib
TargetName=ixtmad42
InputPath=.\MfcAtl\Debug\ixtmad42.lib
SOURCE=$(InputPath)

"\triasdev.mvc\lib32\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   copy "$(TargetPath)" \triasdev.mvc\lib32
   if exist "$(OutDir)\$(TargetName).pdb" copy "$(OutDir)\$(TargetName).pdb"

# End Custom Build

!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Release ATL Base"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ixtmfc30"
# PROP BASE Intermediate_Dir "ixtmfc30"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "MfcAtl/Release"
# PROP Intermediate_Dir "MfcAtl/Release"
# PROP Target_Dir ""
OUTDIR=.\MfcAtl/Release
INTDIR=.\MfcAtl/Release
# Begin Custom Macros
TargetName=ixtmar42
# End Custom Macros

ALL : "$(OUTDIR)\ixtmar42.lib" "..\..\lib32\ixtmar42.lib"

CLEAN : 
	-@erase "$(INTDIR)\Ctfxmfc.obj"
	-@erase "$(INTDIR)\dllbindx.obj"
	-@erase "$(INTDIR)\dummy1.obj"
	-@erase "$(INTDIR)\dummy2.obj"
	-@erase "$(INTDIR)\dummy3.obj"
	-@erase "$(INTDIR)\DUMMY4.OBJ"
	-@erase "$(INTDIR)\enmcprop.obj"
	-@erase "$(INTDIR)\enumprop.obj"
	-@erase "$(INTDIR)\EXTREG.OBJ"
	-@erase "$(INTDIR)\Hdrentrx.obj"
	-@erase "$(INTDIR)\IENUMONR.OBJ"
	-@erase "$(INTDIR)\IXTMFC42.pch"
	-@erase "$(INTDIR)\OBJCONTX.OBJ"
	-@erase "$(INTDIR)\objpropf.obj"
	-@erase "$(INTDIR)\REGISTRY.OBJ"
	-@erase "$(INTDIR)\STRUTIL.OBJ"
	-@erase "$(INTDIR)\XtencAtl.obj"
	-@erase "$(INTDIR)\XTENSNP.OBJ"
	-@erase "$(INTDIR)\xtsnatl.obj"
	-@erase "$(INTDIR)\xtsnimp.obj"
	-@erase "$(INTDIR)\XtsnPropAtl.obj"
	-@erase "$(OUTDIR)\ixtmar42.lib"
	-@erase "..\..\lib32\ixtmar42.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "__XTENSNDLL__" /D "_AFXEXT" /D "__MFC__" /D "_AFXDLL" /D "_MBCS" /D "__ATL_USED__" /D "__ATL_11_USED__" /Yu"xtensnp.hxx" /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "__ATL_XTENSION_BASE__" /D "WIN32" /D "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "__XTENSNDLL__" /D "__MFC__" /D "_AFXEXT" /D "_AFXDLL" /D "_MBCS" /D "__ATL_USED__" /D "__ATL_11_USED__" /D "OS_NO_STREAM_SUPPORT" /Yu"xtensnp.hxx" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "__ATL_XTENSION_BASE__" /D\
 "WIN32" /D "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "__XTENSNDLL__"\
 /D "__MFC__" /D "_AFXEXT" /D "_AFXDLL" /D "_MBCS" /D "__ATL_USED__" /D\
 "__ATL_11_USED__" /D "OS_NO_STREAM_SUPPORT" /Fp"$(INTDIR)/IXTMFC42.pch"\
 /Yu"xtensnp.hxx" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\MfcAtl/Release/
CPP_SBRS=.\.
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/IXTMFC42.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"Mfc42/Release\ixtmfr42.lib"
# ADD LIB32 /nologo /out:"MfcAtl/Release\ixtmar42.lib"
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/ixtmar42.lib" 
LIB32_OBJS= \
	"$(INTDIR)\Ctfxmfc.obj" \
	"$(INTDIR)\dllbindx.obj" \
	"$(INTDIR)\dummy1.obj" \
	"$(INTDIR)\dummy2.obj" \
	"$(INTDIR)\dummy3.obj" \
	"$(INTDIR)\DUMMY4.OBJ" \
	"$(INTDIR)\enmcprop.obj" \
	"$(INTDIR)\enumprop.obj" \
	"$(INTDIR)\EXTREG.OBJ" \
	"$(INTDIR)\Hdrentrx.obj" \
	"$(INTDIR)\IENUMONR.OBJ" \
	"$(INTDIR)\OBJCONTX.OBJ" \
	"$(INTDIR)\objpropf.obj" \
	"$(INTDIR)\REGISTRY.OBJ" \
	"$(INTDIR)\STRUTIL.OBJ" \
	"$(INTDIR)\XtencAtl.obj" \
	"$(INTDIR)\XTENSNP.OBJ" \
	"$(INTDIR)\xtsnatl.obj" \
	"$(INTDIR)\xtsnimp.obj" \
	"$(INTDIR)\XtsnPropAtl.obj"

"$(OUTDIR)\ixtmar42.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

# Begin Custom Build - Copying created library ...
TargetPath=.\MfcAtl\Release\ixtmar42.lib
TargetName=ixtmar42
InputPath=.\MfcAtl\Release\ixtmar42.lib
SOURCE=$(InputPath)

"\triasdev.mvc\lib32\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   copy "$(TargetPath)" \triasdev.mvc\lib32

# End Custom Build

!ENDIF 

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

################################################################################
# Begin Target

# Name "ixtmfc32 - Win32 Release"
# Name "ixtmfc32 - Win32 Debug"
# Name "ixtmfc32 - Win32 Release New"
# Name "ixtmfc32 - Win32 Debug New"
# Name "ixtmfc32 - Win32 Debug ATL Base"
# Name "ixtmfc32 - Win32 Release ATL Base"

!IF  "$(CFG)" == "ixtmfc32 - Win32 Release"

!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug"

!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Release New"

!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug New"

!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug ATL Base"

!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Release ATL Base"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\IMPXTCF.CXX
DEP_CPP_IMPXT=\
	".\cimpxtsn.hxx"\
	".\IMPXTCF.HXX"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OLENLS.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TrCatIDs.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\WrongTrCatIDs.h"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "ixtmfc32 - Win32 Release"


"$(INTDIR)\IMPXTCF.OBJ" : $(SOURCE) $(DEP_CPP_IMPXT) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DEXPROCS" /D "MSWIND" /D "__XTENSNDLL__" /D "__MFC__" /D "_AFXEXT"\
 /D "_AFXDLL" /D "_MBCS" /D "__ATL_USED__" /D "__ATL_11_USED__" /D\
 "OS_NO_STREAM_SUPPORT" /Fp"$(INTDIR)/IXTMFC42.pch" /Yu"xtensnp.hxx"\
 /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug"


BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "__XTENSNDLL__" /D\
 "__MFC__" /D "_AFXEXT" /D "_AFXDLL" /D "_MBCS" /D "__ATL_USED__" /D\
 "__ATL_11_USED__" /D "OS_NO_STREAM_SUPPORT" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/IXTMFC42.pch" /Yu"xtensnp.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/ixtmfd40.pdb" /c $(SOURCE) \
	

"$(INTDIR)\IMPXTCF.OBJ" : $(SOURCE) $(DEP_CPP_IMPXT) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"
   $(BuildCmds)

"$(INTDIR)\IMPXTCF.SBR" : $(SOURCE) $(DEP_CPP_IMPXT) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Release New"


"$(INTDIR)\IMPXTCF.OBJ" : $(SOURCE) $(DEP_CPP_IMPXT) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DEXPROCS" /D "MSWIND" /D "__XTENSNDLL__" /D "__MFC__" /D "_AFXEXT"\
 /D "_AFXDLL" /D "_MBCS" /D "__ATL_USED__" /D "__ATL_11_USED__" /D\
 "OS_NO_STREAM_SUPPORT" /Fp"$(INTDIR)/IXTMFC42.pch" /Yu"xtensnp.hxx"\
 /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug New"


BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "__XTENSNDLL__" /D\
 "__MFC__" /D "_AFXEXT" /D "_AFXDLL" /D "_MBCS" /D "__ATL_USED__" /D\
 "__ATL_11_USED__" /D "OS_NO_STREAM_SUPPORT" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/IXTMFC42.pch" /Yu"xtensnp.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/ixtmfd42.pdb" /c $(SOURCE) \
	

"$(INTDIR)\IMPXTCF.OBJ" : $(SOURCE) $(DEP_CPP_IMPXT) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"
   $(BuildCmds)

"$(INTDIR)\IMPXTCF.SBR" : $(SOURCE) $(DEP_CPP_IMPXT) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug ATL Base"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Release ATL Base"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\XTENSNP.CXX
DEP_CPP_XTENS=\
	".\cimpxtsn.hxx"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OLENLS.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "ixtmfc32 - Win32 Release"

# ADD CPP /Yc"xtensnp.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DEXPROCS" /D "MSWIND" /D "__XTENSNDLL__" /D "__MFC__" /D "_AFXEXT"\
 /D "_AFXDLL" /D "_MBCS" /D "__ATL_USED__" /D "__ATL_11_USED__" /D\
 "OS_NO_STREAM_SUPPORT" /Fp"$(INTDIR)/IXTMFC42.pch" /Yc"xtensnp.hxx"\
 /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\XTENSNP.OBJ" : $(SOURCE) $(DEP_CPP_XTENS) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\IXTMFC42.pch" : $(SOURCE) $(DEP_CPP_XTENS) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug"

# ADD CPP /Yc"xtensnp.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "__XTENSNDLL__" /D\
 "__MFC__" /D "_AFXEXT" /D "_AFXDLL" /D "_MBCS" /D "__ATL_USED__" /D\
 "__ATL_11_USED__" /D "OS_NO_STREAM_SUPPORT" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/IXTMFC42.pch" /Yc"xtensnp.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/ixtmfd40.pdb" /c $(SOURCE) \
	

"$(INTDIR)\XTENSNP.OBJ" : $(SOURCE) $(DEP_CPP_XTENS) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\XTENSNP.SBR" : $(SOURCE) $(DEP_CPP_XTENS) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\IXTMFC42.pch" : $(SOURCE) $(DEP_CPP_XTENS) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Release New"

# ADD BASE CPP /Yc"xtensnp.hxx"
# ADD CPP /Yc"xtensnp.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DEXPROCS" /D "MSWIND" /D "__XTENSNDLL__" /D "__MFC__" /D "_AFXEXT"\
 /D "_AFXDLL" /D "_MBCS" /D "__ATL_USED__" /D "__ATL_11_USED__" /D\
 "OS_NO_STREAM_SUPPORT" /Fp"$(INTDIR)/IXTMFC42.pch" /Yc"xtensnp.hxx"\
 /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\XTENSNP.OBJ" : $(SOURCE) $(DEP_CPP_XTENS) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\IXTMFC42.pch" : $(SOURCE) $(DEP_CPP_XTENS) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug New"

# ADD BASE CPP /Yc"xtensnp.hxx"
# ADD CPP /Yc"xtensnp.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "__XTENSNDLL__" /D\
 "__MFC__" /D "_AFXEXT" /D "_AFXDLL" /D "_MBCS" /D "__ATL_USED__" /D\
 "__ATL_11_USED__" /D "OS_NO_STREAM_SUPPORT" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/IXTMFC42.pch" /Yc"xtensnp.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/ixtmfd42.pdb" /c $(SOURCE) \
	

"$(INTDIR)\XTENSNP.OBJ" : $(SOURCE) $(DEP_CPP_XTENS) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\XTENSNP.SBR" : $(SOURCE) $(DEP_CPP_XTENS) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\IXTMFC42.pch" : $(SOURCE) $(DEP_CPP_XTENS) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug ATL Base"

# ADD BASE CPP /Yc"xtensnp.hxx"
# ADD CPP /Yc"xtensnp.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D\
 "__ATL_XTENSION_BASE__" /D "WIN32" /D "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D\
 "MSWIND" /D "__XTENSNDLL__" /D "__MFC__" /D "_AFXEXT" /D "_AFXDLL" /D "_MBCS"\
 /D "__ATL_USED__" /D "__ATL_11_USED__" /D "OS_NO_STREAM_SUPPORT"\
 /FR"$(INTDIR)/" /Fp"$(INTDIR)/IXTMAD42.pch" /Yc"xtensnp.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/ixtmad42.pdb" /c $(SOURCE) \
	

"$(INTDIR)\XTENSNP.OBJ" : $(SOURCE) $(DEP_CPP_XTENS) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\XTENSNP.SBR" : $(SOURCE) $(DEP_CPP_XTENS) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\IXTMAD42.pch" : $(SOURCE) $(DEP_CPP_XTENS) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Release ATL Base"

# ADD BASE CPP /Yc"xtensnp.hxx"
# ADD CPP /Yc"xtensnp.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "__ATL_XTENSION_BASE__" /D\
 "WIN32" /D "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "__XTENSNDLL__"\
 /D "__MFC__" /D "_AFXEXT" /D "_AFXDLL" /D "_MBCS" /D "__ATL_USED__" /D\
 "__ATL_11_USED__" /D "OS_NO_STREAM_SUPPORT" /Fp"$(INTDIR)/IXTMFC42.pch"\
 /Yc"xtensnp.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\XTENSNP.OBJ" : $(SOURCE) $(DEP_CPP_XTENS) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\IXTMFC42.pch" : $(SOURCE) $(DEP_CPP_XTENS) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Xtencunk.cxx
DEP_CPP_XTENC=\
	".\cimpxtsn.hxx"\
	".\IMPXTCF.HXX"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OLENLS.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "ixtmfc32 - Win32 Release"


"$(INTDIR)\Xtencunk.obj" : $(SOURCE) $(DEP_CPP_XTENC) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DEXPROCS" /D "MSWIND" /D "__XTENSNDLL__" /D "__MFC__" /D "_AFXEXT"\
 /D "_AFXDLL" /D "_MBCS" /D "__ATL_USED__" /D "__ATL_11_USED__" /D\
 "OS_NO_STREAM_SUPPORT" /Fp"$(INTDIR)/IXTMFC42.pch" /Yu"xtensnp.hxx"\
 /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug"

# ADD CPP /Zi

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "__XTENSNDLL__" /D\
 "__MFC__" /D "_AFXEXT" /D "_AFXDLL" /D "_MBCS" /D "__ATL_USED__" /D\
 "__ATL_11_USED__" /D "OS_NO_STREAM_SUPPORT" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/IXTMFC42.pch" /Yu"xtensnp.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/ixtmfd40.pdb" /c $(SOURCE) \
	

"$(INTDIR)\Xtencunk.obj" : $(SOURCE) $(DEP_CPP_XTENC) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"
   $(BuildCmds)

"$(INTDIR)\Xtencunk.sbr" : $(SOURCE) $(DEP_CPP_XTENC) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Release New"


"$(INTDIR)\Xtencunk.obj" : $(SOURCE) $(DEP_CPP_XTENC) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DEXPROCS" /D "MSWIND" /D "__XTENSNDLL__" /D "__MFC__" /D "_AFXEXT"\
 /D "_AFXDLL" /D "_MBCS" /D "__ATL_USED__" /D "__ATL_11_USED__" /D\
 "OS_NO_STREAM_SUPPORT" /Fp"$(INTDIR)/IXTMFC42.pch" /Yu"xtensnp.hxx"\
 /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug New"

# ADD BASE CPP /Zi
# ADD CPP /Zi

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "__XTENSNDLL__" /D\
 "__MFC__" /D "_AFXEXT" /D "_AFXDLL" /D "_MBCS" /D "__ATL_USED__" /D\
 "__ATL_11_USED__" /D "OS_NO_STREAM_SUPPORT" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/IXTMFC42.pch" /Yu"xtensnp.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/ixtmfd42.pdb" /c $(SOURCE) \
	

"$(INTDIR)\Xtencunk.obj" : $(SOURCE) $(DEP_CPP_XTENC) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"
   $(BuildCmds)

"$(INTDIR)\Xtencunk.sbr" : $(SOURCE) $(DEP_CPP_XTENC) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug ATL Base"

# PROP Exclude_From_Build 1
# ADD BASE CPP /Zi
# ADD CPP /Zi

!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Release ATL Base"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\enmcprop.cxx
DEP_CPP_ENMCP=\
	".\cimpxtsn.hxx"\
	".\enmcprop.hxx"\
	".\synccook.h"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OLENLS.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "ixtmfc32 - Win32 Release"


"$(INTDIR)\enmcprop.obj" : $(SOURCE) $(DEP_CPP_ENMCP) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug"


"$(INTDIR)\enmcprop.obj" : $(SOURCE) $(DEP_CPP_ENMCP) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"

"$(INTDIR)\enmcprop.sbr" : $(SOURCE) $(DEP_CPP_ENMCP) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Release New"


"$(INTDIR)\enmcprop.obj" : $(SOURCE) $(DEP_CPP_ENMCP) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug New"


"$(INTDIR)\enmcprop.obj" : $(SOURCE) $(DEP_CPP_ENMCP) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"

"$(INTDIR)\enmcprop.sbr" : $(SOURCE) $(DEP_CPP_ENMCP) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug ATL Base"


"$(INTDIR)\enmcprop.obj" : $(SOURCE) $(DEP_CPP_ENMCP) "$(INTDIR)"\
 "$(INTDIR)\IXTMAD42.pch"

"$(INTDIR)\enmcprop.sbr" : $(SOURCE) $(DEP_CPP_ENMCP) "$(INTDIR)"\
 "$(INTDIR)\IXTMAD42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Release ATL Base"


"$(INTDIR)\enmcprop.obj" : $(SOURCE) $(DEP_CPP_ENMCP) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\enumprop.cxx
DEP_CPP_ENUMP=\
	".\cimpxtsn.hxx"\
	".\enumprop.hxx"\
	".\synccook.h"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OLENLS.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "ixtmfc32 - Win32 Release"


"$(INTDIR)\enumprop.obj" : $(SOURCE) $(DEP_CPP_ENUMP) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug"


"$(INTDIR)\enumprop.obj" : $(SOURCE) $(DEP_CPP_ENUMP) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"

"$(INTDIR)\enumprop.sbr" : $(SOURCE) $(DEP_CPP_ENUMP) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Release New"


"$(INTDIR)\enumprop.obj" : $(SOURCE) $(DEP_CPP_ENUMP) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug New"


"$(INTDIR)\enumprop.obj" : $(SOURCE) $(DEP_CPP_ENUMP) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"

"$(INTDIR)\enumprop.sbr" : $(SOURCE) $(DEP_CPP_ENUMP) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug ATL Base"


"$(INTDIR)\enumprop.obj" : $(SOURCE) $(DEP_CPP_ENUMP) "$(INTDIR)"\
 "$(INTDIR)\IXTMAD42.pch"

"$(INTDIR)\enumprop.sbr" : $(SOURCE) $(DEP_CPP_ENUMP) "$(INTDIR)"\
 "$(INTDIR)\IXTMAD42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Release ATL Base"


"$(INTDIR)\enumprop.obj" : $(SOURCE) $(DEP_CPP_ENUMP) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\objpropf.cxx
DEP_CPP_OBJPR=\
	".\cimpxtsn.hxx"\
	".\objpropf.hxx"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OLENLS.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "ixtmfc32 - Win32 Release"


"$(INTDIR)\objpropf.obj" : $(SOURCE) $(DEP_CPP_OBJPR) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug"


"$(INTDIR)\objpropf.obj" : $(SOURCE) $(DEP_CPP_OBJPR) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"

"$(INTDIR)\objpropf.sbr" : $(SOURCE) $(DEP_CPP_OBJPR) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Release New"


"$(INTDIR)\objpropf.obj" : $(SOURCE) $(DEP_CPP_OBJPR) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug New"


"$(INTDIR)\objpropf.obj" : $(SOURCE) $(DEP_CPP_OBJPR) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"

"$(INTDIR)\objpropf.sbr" : $(SOURCE) $(DEP_CPP_OBJPR) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug ATL Base"


"$(INTDIR)\objpropf.obj" : $(SOURCE) $(DEP_CPP_OBJPR) "$(INTDIR)"\
 "$(INTDIR)\IXTMAD42.pch"

"$(INTDIR)\objpropf.sbr" : $(SOURCE) $(DEP_CPP_OBJPR) "$(INTDIR)"\
 "$(INTDIR)\IXTMAD42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Release ATL Base"


"$(INTDIR)\objpropf.obj" : $(SOURCE) $(DEP_CPP_OBJPR) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\xtsnprop.cxx
DEP_CPP_XTSNP=\
	".\cimpxtsn.hxx"\
	".\enmcprop.hxx"\
	".\enumprop.hxx"\
	".\objpropf.hxx"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OLENLS.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "ixtmfc32 - Win32 Release"


"$(INTDIR)\xtsnprop.obj" : $(SOURCE) $(DEP_CPP_XTSNP) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DEXPROCS" /D "MSWIND" /D "__XTENSNDLL__" /D "__MFC__" /D "_AFXEXT"\
 /D "_AFXDLL" /D "_MBCS" /D "__ATL_USED__" /D "__ATL_11_USED__" /D\
 "OS_NO_STREAM_SUPPORT" /Fp"$(INTDIR)/IXTMFC42.pch" /Yu"xtensnp.hxx"\
 /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug"


BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "__XTENSNDLL__" /D\
 "__MFC__" /D "_AFXEXT" /D "_AFXDLL" /D "_MBCS" /D "__ATL_USED__" /D\
 "__ATL_11_USED__" /D "OS_NO_STREAM_SUPPORT" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/IXTMFC42.pch" /Yu"xtensnp.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/ixtmfd40.pdb" /c $(SOURCE) \
	

"$(INTDIR)\xtsnprop.obj" : $(SOURCE) $(DEP_CPP_XTSNP) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"
   $(BuildCmds)

"$(INTDIR)\xtsnprop.sbr" : $(SOURCE) $(DEP_CPP_XTSNP) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Release New"


"$(INTDIR)\xtsnprop.obj" : $(SOURCE) $(DEP_CPP_XTSNP) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DEXPROCS" /D "MSWIND" /D "__XTENSNDLL__" /D "__MFC__" /D "_AFXEXT"\
 /D "_AFXDLL" /D "_MBCS" /D "__ATL_USED__" /D "__ATL_11_USED__" /D\
 "OS_NO_STREAM_SUPPORT" /Fp"$(INTDIR)/IXTMFC42.pch" /Yu"xtensnp.hxx"\
 /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug New"


BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "__XTENSNDLL__" /D\
 "__MFC__" /D "_AFXEXT" /D "_AFXDLL" /D "_MBCS" /D "__ATL_USED__" /D\
 "__ATL_11_USED__" /D "OS_NO_STREAM_SUPPORT" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/IXTMFC42.pch" /Yu"xtensnp.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/ixtmfd42.pdb" /c $(SOURCE) \
	

"$(INTDIR)\xtsnprop.obj" : $(SOURCE) $(DEP_CPP_XTSNP) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"
   $(BuildCmds)

"$(INTDIR)\xtsnprop.sbr" : $(SOURCE) $(DEP_CPP_XTSNP) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug ATL Base"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Release ATL Base"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\IENUMONR.CXX
DEP_CPP_IENUM=\
	".\cimpxtsn.hxx"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IENUMONR.HXX"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OLENLS.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "ixtmfc32 - Win32 Release"


"$(INTDIR)\IENUMONR.OBJ" : $(SOURCE) $(DEP_CPP_IENUM) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug"


"$(INTDIR)\IENUMONR.OBJ" : $(SOURCE) $(DEP_CPP_IENUM) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"

"$(INTDIR)\IENUMONR.SBR" : $(SOURCE) $(DEP_CPP_IENUM) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Release New"


"$(INTDIR)\IENUMONR.OBJ" : $(SOURCE) $(DEP_CPP_IENUM) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug New"


"$(INTDIR)\IENUMONR.OBJ" : $(SOURCE) $(DEP_CPP_IENUM) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"

"$(INTDIR)\IENUMONR.SBR" : $(SOURCE) $(DEP_CPP_IENUM) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug ATL Base"


"$(INTDIR)\IENUMONR.OBJ" : $(SOURCE) $(DEP_CPP_IENUM) "$(INTDIR)"\
 "$(INTDIR)\IXTMAD42.pch"

"$(INTDIR)\IENUMONR.SBR" : $(SOURCE) $(DEP_CPP_IENUM) "$(INTDIR)"\
 "$(INTDIR)\IXTMAD42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Release ATL Base"


"$(INTDIR)\IENUMONR.OBJ" : $(SOURCE) $(DEP_CPP_IENUM) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\xtsnimp.cxx

!IF  "$(CFG)" == "ixtmfc32 - Win32 Release"

DEP_CPP_XTSNI=\
	".\cimpxtsn.hxx"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OLENLS.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\xtsnimp.obj" : $(SOURCE) $(DEP_CPP_XTSNI) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug"

DEP_CPP_XTSNI=\
	".\cimpxtsn.hxx"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OLENLS.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\xtsnimp.obj" : $(SOURCE) $(DEP_CPP_XTSNI) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"

"$(INTDIR)\xtsnimp.sbr" : $(SOURCE) $(DEP_CPP_XTSNI) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Release New"

DEP_CPP_XTSNI=\
	".\cimpxtsn.hxx"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OLENLS.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\xtsnimp.obj" : $(SOURCE) $(DEP_CPP_XTSNI) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug New"

DEP_CPP_XTSNI=\
	".\cimpxtsn.hxx"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OLENLS.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\xtsnimp.obj" : $(SOURCE) $(DEP_CPP_XTSNI) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"

"$(INTDIR)\xtsnimp.sbr" : $(SOURCE) $(DEP_CPP_XTSNI) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug ATL Base"

DEP_CPP_XTSNI=\
	".\cimpxtsn.hxx"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OLENLS.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\xtsnimp.obj" : $(SOURCE) $(DEP_CPP_XTSNI) "$(INTDIR)"\
 "$(INTDIR)\IXTMAD42.pch"

"$(INTDIR)\xtsnimp.sbr" : $(SOURCE) $(DEP_CPP_XTSNI) "$(INTDIR)"\
 "$(INTDIR)\IXTMAD42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Release ATL Base"

DEP_CPP_XTSNI=\
	".\cimpxtsn.hxx"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OLENLS.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\xtsnimp.obj" : $(SOURCE) $(DEP_CPP_XTSNI) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\cimpxtsn.cxx
DEP_CPP_CIMPX=\
	".\cimpxtsn.hxx"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OLENLS.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "ixtmfc32 - Win32 Release"


"$(INTDIR)\cimpxtsn.obj" : $(SOURCE) $(DEP_CPP_CIMPX) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DEXPROCS" /D "MSWIND" /D "__XTENSNDLL__" /D "__MFC__" /D "_AFXEXT"\
 /D "_AFXDLL" /D "_MBCS" /D "__ATL_USED__" /D "__ATL_11_USED__" /D\
 "OS_NO_STREAM_SUPPORT" /Fp"$(INTDIR)/IXTMFC42.pch" /Yu"xtensnp.hxx"\
 /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug"


BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "__XTENSNDLL__" /D\
 "__MFC__" /D "_AFXEXT" /D "_AFXDLL" /D "_MBCS" /D "__ATL_USED__" /D\
 "__ATL_11_USED__" /D "OS_NO_STREAM_SUPPORT" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/IXTMFC42.pch" /Yu"xtensnp.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/ixtmfd40.pdb" /c $(SOURCE) \
	

"$(INTDIR)\cimpxtsn.obj" : $(SOURCE) $(DEP_CPP_CIMPX) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"
   $(BuildCmds)

"$(INTDIR)\cimpxtsn.sbr" : $(SOURCE) $(DEP_CPP_CIMPX) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Release New"


"$(INTDIR)\cimpxtsn.obj" : $(SOURCE) $(DEP_CPP_CIMPX) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DEXPROCS" /D "MSWIND" /D "__XTENSNDLL__" /D "__MFC__" /D "_AFXEXT"\
 /D "_AFXDLL" /D "_MBCS" /D "__ATL_USED__" /D "__ATL_11_USED__" /D\
 "OS_NO_STREAM_SUPPORT" /Fp"$(INTDIR)/IXTMFC42.pch" /Yu"xtensnp.hxx"\
 /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug New"


BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "__XTENSNDLL__" /D\
 "__MFC__" /D "_AFXEXT" /D "_AFXDLL" /D "_MBCS" /D "__ATL_USED__" /D\
 "__ATL_11_USED__" /D "OS_NO_STREAM_SUPPORT" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/IXTMFC42.pch" /Yu"xtensnp.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/ixtmfd42.pdb" /c $(SOURCE) \
	

"$(INTDIR)\cimpxtsn.obj" : $(SOURCE) $(DEP_CPP_CIMPX) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"
   $(BuildCmds)

"$(INTDIR)\cimpxtsn.sbr" : $(SOURCE) $(DEP_CPP_CIMPX) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug ATL Base"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Release ATL Base"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\EXTREG.CXX

!IF  "$(CFG)" == "ixtmfc32 - Win32 Release"

DEP_CPP_EXTRE=\
	".\cimpxtsn.hxx"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\COMCAT.H"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OLENLS.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TrCatIDs.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\WrongTrCatIDs.h"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\EXTREG.OBJ" : $(SOURCE) $(DEP_CPP_EXTRE) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug"

DEP_CPP_EXTRE=\
	".\cimpxtsn.hxx"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\COMCAT.H"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OLENLS.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TrCatIDs.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\WrongTrCatIDs.h"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\EXTREG.OBJ" : $(SOURCE) $(DEP_CPP_EXTRE) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"

"$(INTDIR)\EXTREG.SBR" : $(SOURCE) $(DEP_CPP_EXTRE) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Release New"

DEP_CPP_EXTRE=\
	".\cimpxtsn.hxx"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\COMCAT.H"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OLENLS.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TrCatIDs.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\WrongTrCatIDs.h"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\EXTREG.OBJ" : $(SOURCE) $(DEP_CPP_EXTRE) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug New"

DEP_CPP_EXTRE=\
	".\cimpxtsn.hxx"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\COMCAT.H"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OLENLS.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TrCatIDs.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\WrongTrCatIDs.h"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\EXTREG.OBJ" : $(SOURCE) $(DEP_CPP_EXTRE) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"

"$(INTDIR)\EXTREG.SBR" : $(SOURCE) $(DEP_CPP_EXTRE) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug ATL Base"

DEP_CPP_EXTRE=\
	".\cimpxtsn.hxx"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\COMCAT.H"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OLENLS.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TrCatIDs.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\WrongTrCatIDs.h"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\EXTREG.OBJ" : $(SOURCE) $(DEP_CPP_EXTRE) "$(INTDIR)"\
 "$(INTDIR)\IXTMAD42.pch"

"$(INTDIR)\EXTREG.SBR" : $(SOURCE) $(DEP_CPP_EXTRE) "$(INTDIR)"\
 "$(INTDIR)\IXTMAD42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Release ATL Base"

DEP_CPP_EXTRE=\
	".\cimpxtsn.hxx"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\COMCAT.H"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OLENLS.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TrCatIDs.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\WrongTrCatIDs.h"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\EXTREG.OBJ" : $(SOURCE) $(DEP_CPP_EXTRE) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\REGISTRY.CXX
DEP_CPP_REGIS=\
	".\cimpxtsn.hxx"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OLENLS.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "ixtmfc32 - Win32 Release"


"$(INTDIR)\REGISTRY.OBJ" : $(SOURCE) $(DEP_CPP_REGIS) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug"


"$(INTDIR)\REGISTRY.OBJ" : $(SOURCE) $(DEP_CPP_REGIS) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"

"$(INTDIR)\REGISTRY.SBR" : $(SOURCE) $(DEP_CPP_REGIS) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Release New"


"$(INTDIR)\REGISTRY.OBJ" : $(SOURCE) $(DEP_CPP_REGIS) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug New"


"$(INTDIR)\REGISTRY.OBJ" : $(SOURCE) $(DEP_CPP_REGIS) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"

"$(INTDIR)\REGISTRY.SBR" : $(SOURCE) $(DEP_CPP_REGIS) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug ATL Base"


"$(INTDIR)\REGISTRY.OBJ" : $(SOURCE) $(DEP_CPP_REGIS) "$(INTDIR)"\
 "$(INTDIR)\IXTMAD42.pch"

"$(INTDIR)\REGISTRY.SBR" : $(SOURCE) $(DEP_CPP_REGIS) "$(INTDIR)"\
 "$(INTDIR)\IXTMAD42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Release ATL Base"


"$(INTDIR)\REGISTRY.OBJ" : $(SOURCE) $(DEP_CPP_REGIS) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\OBJCONTX.CXX
DEP_CPP_OBJCO=\
	".\cimpxtsn.hxx"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OLENLS.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "ixtmfc32 - Win32 Release"


"$(INTDIR)\OBJCONTX.OBJ" : $(SOURCE) $(DEP_CPP_OBJCO) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug"


"$(INTDIR)\OBJCONTX.OBJ" : $(SOURCE) $(DEP_CPP_OBJCO) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"

"$(INTDIR)\OBJCONTX.SBR" : $(SOURCE) $(DEP_CPP_OBJCO) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Release New"


"$(INTDIR)\OBJCONTX.OBJ" : $(SOURCE) $(DEP_CPP_OBJCO) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug New"


"$(INTDIR)\OBJCONTX.OBJ" : $(SOURCE) $(DEP_CPP_OBJCO) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"

"$(INTDIR)\OBJCONTX.SBR" : $(SOURCE) $(DEP_CPP_OBJCO) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug ATL Base"


"$(INTDIR)\OBJCONTX.OBJ" : $(SOURCE) $(DEP_CPP_OBJCO) "$(INTDIR)"\
 "$(INTDIR)\IXTMAD42.pch"

"$(INTDIR)\OBJCONTX.SBR" : $(SOURCE) $(DEP_CPP_OBJCO) "$(INTDIR)"\
 "$(INTDIR)\IXTMAD42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Release ATL Base"


"$(INTDIR)\OBJCONTX.OBJ" : $(SOURCE) $(DEP_CPP_OBJCO) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRUTIL.CXX
DEP_CPP_STRUT=\
	".\cimpxtsn.hxx"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OLENLS.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "ixtmfc32 - Win32 Release"


"$(INTDIR)\STRUTIL.OBJ" : $(SOURCE) $(DEP_CPP_STRUT) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug"


"$(INTDIR)\STRUTIL.OBJ" : $(SOURCE) $(DEP_CPP_STRUT) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"

"$(INTDIR)\STRUTIL.SBR" : $(SOURCE) $(DEP_CPP_STRUT) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Release New"


"$(INTDIR)\STRUTIL.OBJ" : $(SOURCE) $(DEP_CPP_STRUT) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug New"


"$(INTDIR)\STRUTIL.OBJ" : $(SOURCE) $(DEP_CPP_STRUT) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"

"$(INTDIR)\STRUTIL.SBR" : $(SOURCE) $(DEP_CPP_STRUT) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug ATL Base"


"$(INTDIR)\STRUTIL.OBJ" : $(SOURCE) $(DEP_CPP_STRUT) "$(INTDIR)"\
 "$(INTDIR)\IXTMAD42.pch"

"$(INTDIR)\STRUTIL.SBR" : $(SOURCE) $(DEP_CPP_STRUT) "$(INTDIR)"\
 "$(INTDIR)\IXTMAD42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Release ATL Base"


"$(INTDIR)\STRUTIL.OBJ" : $(SOURCE) $(DEP_CPP_STRUT) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dummy1.cxx
DEP_CPP_DUMMY=\
	".\cimpxtsn.hxx"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OLENLS.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "ixtmfc32 - Win32 Release"


"$(INTDIR)\dummy1.obj" : $(SOURCE) $(DEP_CPP_DUMMY) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug"


"$(INTDIR)\dummy1.obj" : $(SOURCE) $(DEP_CPP_DUMMY) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"

"$(INTDIR)\dummy1.sbr" : $(SOURCE) $(DEP_CPP_DUMMY) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Release New"


"$(INTDIR)\dummy1.obj" : $(SOURCE) $(DEP_CPP_DUMMY) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug New"


"$(INTDIR)\dummy1.obj" : $(SOURCE) $(DEP_CPP_DUMMY) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"

"$(INTDIR)\dummy1.sbr" : $(SOURCE) $(DEP_CPP_DUMMY) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug ATL Base"


"$(INTDIR)\dummy1.obj" : $(SOURCE) $(DEP_CPP_DUMMY) "$(INTDIR)"\
 "$(INTDIR)\IXTMAD42.pch"

"$(INTDIR)\dummy1.sbr" : $(SOURCE) $(DEP_CPP_DUMMY) "$(INTDIR)"\
 "$(INTDIR)\IXTMAD42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Release ATL Base"


"$(INTDIR)\dummy1.obj" : $(SOURCE) $(DEP_CPP_DUMMY) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dummy2.cxx
DEP_CPP_DUMMY2=\
	".\cimpxtsn.hxx"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OLENLS.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "ixtmfc32 - Win32 Release"


"$(INTDIR)\dummy2.obj" : $(SOURCE) $(DEP_CPP_DUMMY2) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug"


"$(INTDIR)\dummy2.obj" : $(SOURCE) $(DEP_CPP_DUMMY2) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"

"$(INTDIR)\dummy2.sbr" : $(SOURCE) $(DEP_CPP_DUMMY2) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Release New"


"$(INTDIR)\dummy2.obj" : $(SOURCE) $(DEP_CPP_DUMMY2) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug New"


"$(INTDIR)\dummy2.obj" : $(SOURCE) $(DEP_CPP_DUMMY2) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"

"$(INTDIR)\dummy2.sbr" : $(SOURCE) $(DEP_CPP_DUMMY2) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug ATL Base"


"$(INTDIR)\dummy2.obj" : $(SOURCE) $(DEP_CPP_DUMMY2) "$(INTDIR)"\
 "$(INTDIR)\IXTMAD42.pch"

"$(INTDIR)\dummy2.sbr" : $(SOURCE) $(DEP_CPP_DUMMY2) "$(INTDIR)"\
 "$(INTDIR)\IXTMAD42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Release ATL Base"


"$(INTDIR)\dummy2.obj" : $(SOURCE) $(DEP_CPP_DUMMY2) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dummy3.cxx
DEP_CPP_DUMMY3=\
	".\cimpxtsn.hxx"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OLENLS.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "ixtmfc32 - Win32 Release"


"$(INTDIR)\dummy3.obj" : $(SOURCE) $(DEP_CPP_DUMMY3) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug"


"$(INTDIR)\dummy3.obj" : $(SOURCE) $(DEP_CPP_DUMMY3) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"

"$(INTDIR)\dummy3.sbr" : $(SOURCE) $(DEP_CPP_DUMMY3) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Release New"


"$(INTDIR)\dummy3.obj" : $(SOURCE) $(DEP_CPP_DUMMY3) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug New"


"$(INTDIR)\dummy3.obj" : $(SOURCE) $(DEP_CPP_DUMMY3) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"

"$(INTDIR)\dummy3.sbr" : $(SOURCE) $(DEP_CPP_DUMMY3) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug ATL Base"


"$(INTDIR)\dummy3.obj" : $(SOURCE) $(DEP_CPP_DUMMY3) "$(INTDIR)"\
 "$(INTDIR)\IXTMAD42.pch"

"$(INTDIR)\dummy3.sbr" : $(SOURCE) $(DEP_CPP_DUMMY3) "$(INTDIR)"\
 "$(INTDIR)\IXTMAD42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Release ATL Base"


"$(INTDIR)\dummy3.obj" : $(SOURCE) $(DEP_CPP_DUMMY3) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DUMMY4.CXX
DEP_CPP_DUMMY4=\
	".\cimpxtsn.hxx"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OLENLS.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "ixtmfc32 - Win32 Release"


"$(INTDIR)\DUMMY4.OBJ" : $(SOURCE) $(DEP_CPP_DUMMY4) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug"


"$(INTDIR)\DUMMY4.OBJ" : $(SOURCE) $(DEP_CPP_DUMMY4) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"

"$(INTDIR)\DUMMY4.SBR" : $(SOURCE) $(DEP_CPP_DUMMY4) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Release New"


"$(INTDIR)\DUMMY4.OBJ" : $(SOURCE) $(DEP_CPP_DUMMY4) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug New"


"$(INTDIR)\DUMMY4.OBJ" : $(SOURCE) $(DEP_CPP_DUMMY4) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"

"$(INTDIR)\DUMMY4.SBR" : $(SOURCE) $(DEP_CPP_DUMMY4) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug ATL Base"


"$(INTDIR)\DUMMY4.OBJ" : $(SOURCE) $(DEP_CPP_DUMMY4) "$(INTDIR)"\
 "$(INTDIR)\IXTMAD42.pch"

"$(INTDIR)\DUMMY4.SBR" : $(SOURCE) $(DEP_CPP_DUMMY4) "$(INTDIR)"\
 "$(INTDIR)\IXTMAD42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Release ATL Base"


"$(INTDIR)\DUMMY4.OBJ" : $(SOURCE) $(DEP_CPP_DUMMY4) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dummy5.cxx
DEP_CPP_DUMMY5=\
	".\cimpxtsn.hxx"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OLENLS.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "ixtmfc32 - Win32 Release"


"$(INTDIR)\dummy5.obj" : $(SOURCE) $(DEP_CPP_DUMMY5) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DEXPROCS" /D "MSWIND" /D "__XTENSNDLL__" /D "__MFC__" /D "_AFXEXT"\
 /D "_AFXDLL" /D "_MBCS" /D "__ATL_USED__" /D "__ATL_11_USED__" /D\
 "OS_NO_STREAM_SUPPORT" /Fp"$(INTDIR)/IXTMFC42.pch" /Yu"xtensnp.hxx"\
 /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug"


BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "__XTENSNDLL__" /D\
 "__MFC__" /D "_AFXEXT" /D "_AFXDLL" /D "_MBCS" /D "__ATL_USED__" /D\
 "__ATL_11_USED__" /D "OS_NO_STREAM_SUPPORT" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/IXTMFC42.pch" /Yu"xtensnp.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/ixtmfd40.pdb" /c $(SOURCE) \
	

"$(INTDIR)\dummy5.obj" : $(SOURCE) $(DEP_CPP_DUMMY5) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"
   $(BuildCmds)

"$(INTDIR)\dummy5.sbr" : $(SOURCE) $(DEP_CPP_DUMMY5) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Release New"


"$(INTDIR)\dummy5.obj" : $(SOURCE) $(DEP_CPP_DUMMY5) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DEXPROCS" /D "MSWIND" /D "__XTENSNDLL__" /D "__MFC__" /D "_AFXEXT"\
 /D "_AFXDLL" /D "_MBCS" /D "__ATL_USED__" /D "__ATL_11_USED__" /D\
 "OS_NO_STREAM_SUPPORT" /Fp"$(INTDIR)/IXTMFC42.pch" /Yu"xtensnp.hxx"\
 /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug New"


BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "__XTENSNDLL__" /D\
 "__MFC__" /D "_AFXEXT" /D "_AFXDLL" /D "_MBCS" /D "__ATL_USED__" /D\
 "__ATL_11_USED__" /D "OS_NO_STREAM_SUPPORT" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/IXTMFC42.pch" /Yu"xtensnp.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/ixtmfd42.pdb" /c $(SOURCE) \
	

"$(INTDIR)\dummy5.obj" : $(SOURCE) $(DEP_CPP_DUMMY5) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"
   $(BuildCmds)

"$(INTDIR)\dummy5.sbr" : $(SOURCE) $(DEP_CPP_DUMMY5) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug ATL Base"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Release ATL Base"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\xtsnatl.cpp
DEP_CPP_XTSNA=\
	".\cimpxtsn.hxx"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"\atlimpl.cpp"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OLENLS.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "ixtmfc32 - Win32 Release"


"$(INTDIR)\xtsnatl.obj" : $(SOURCE) $(DEP_CPP_XTSNA) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug"


"$(INTDIR)\xtsnatl.obj" : $(SOURCE) $(DEP_CPP_XTSNA) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"

"$(INTDIR)\xtsnatl.sbr" : $(SOURCE) $(DEP_CPP_XTSNA) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Release New"


"$(INTDIR)\xtsnatl.obj" : $(SOURCE) $(DEP_CPP_XTSNA) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug New"


"$(INTDIR)\xtsnatl.obj" : $(SOURCE) $(DEP_CPP_XTSNA) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"

"$(INTDIR)\xtsnatl.sbr" : $(SOURCE) $(DEP_CPP_XTSNA) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug ATL Base"


"$(INTDIR)\xtsnatl.obj" : $(SOURCE) $(DEP_CPP_XTSNA) "$(INTDIR)"\
 "$(INTDIR)\IXTMAD42.pch"

"$(INTDIR)\xtsnatl.sbr" : $(SOURCE) $(DEP_CPP_XTSNA) "$(INTDIR)"\
 "$(INTDIR)\IXTMAD42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Release ATL Base"


"$(INTDIR)\xtsnatl.obj" : $(SOURCE) $(DEP_CPP_XTSNA) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dllbindx.cxx
DEP_CPP_DLLBI=\
	".\cimpxtsn.hxx"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OLENLS.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "ixtmfc32 - Win32 Release"


"$(INTDIR)\dllbindx.obj" : $(SOURCE) $(DEP_CPP_DLLBI) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug"


"$(INTDIR)\dllbindx.obj" : $(SOURCE) $(DEP_CPP_DLLBI) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"

"$(INTDIR)\dllbindx.sbr" : $(SOURCE) $(DEP_CPP_DLLBI) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Release New"


"$(INTDIR)\dllbindx.obj" : $(SOURCE) $(DEP_CPP_DLLBI) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug New"


"$(INTDIR)\dllbindx.obj" : $(SOURCE) $(DEP_CPP_DLLBI) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"

"$(INTDIR)\dllbindx.sbr" : $(SOURCE) $(DEP_CPP_DLLBI) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug ATL Base"


"$(INTDIR)\dllbindx.obj" : $(SOURCE) $(DEP_CPP_DLLBI) "$(INTDIR)"\
 "$(INTDIR)\IXTMAD42.pch"

"$(INTDIR)\dllbindx.sbr" : $(SOURCE) $(DEP_CPP_DLLBI) "$(INTDIR)"\
 "$(INTDIR)\IXTMAD42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Release ATL Base"


"$(INTDIR)\dllbindx.obj" : $(SOURCE) $(DEP_CPP_DLLBI) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Hdrentrx.cxx
DEP_CPP_HDREN=\
	".\cimpxtsn.hxx"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Hdrentrx.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OLENLS.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "ixtmfc32 - Win32 Release"


"$(INTDIR)\Hdrentrx.obj" : $(SOURCE) $(DEP_CPP_HDREN) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug"


"$(INTDIR)\Hdrentrx.obj" : $(SOURCE) $(DEP_CPP_HDREN) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"

"$(INTDIR)\Hdrentrx.sbr" : $(SOURCE) $(DEP_CPP_HDREN) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Release New"


"$(INTDIR)\Hdrentrx.obj" : $(SOURCE) $(DEP_CPP_HDREN) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug New"


"$(INTDIR)\Hdrentrx.obj" : $(SOURCE) $(DEP_CPP_HDREN) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"

"$(INTDIR)\Hdrentrx.sbr" : $(SOURCE) $(DEP_CPP_HDREN) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug ATL Base"


"$(INTDIR)\Hdrentrx.obj" : $(SOURCE) $(DEP_CPP_HDREN) "$(INTDIR)"\
 "$(INTDIR)\IXTMAD42.pch"

"$(INTDIR)\Hdrentrx.sbr" : $(SOURCE) $(DEP_CPP_HDREN) "$(INTDIR)"\
 "$(INTDIR)\IXTMAD42.pch"


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Release ATL Base"


"$(INTDIR)\Hdrentrx.obj" : $(SOURCE) $(DEP_CPP_HDREN) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Ctfxmfc.cpp

!IF  "$(CFG)" == "ixtmfc32 - Win32 Release"

DEP_CPP_CTFXM=\
	".\cimpxtsn.hxx"\
	".\Ctfxmfc.nocom.cpp"\
	".\STDAFX.H"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\COMCAT.H"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\ctfxmfc.h"\
	{$(INCLUDE)}"\ctfxmfc.nocom.h"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Hdrentrx.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OLENLS.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\PropertyHelper.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TrCatIDs.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	
# ADD CPP /Yu"stdafx.h"

"$(INTDIR)\Ctfxmfc.obj" : $(SOURCE) $(DEP_CPP_CTFXM) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DEXPROCS" /D "MSWIND" /D "__XTENSNDLL__" /D "__MFC__" /D "_AFXEXT"\
 /D "_AFXDLL" /D "_MBCS" /D "__ATL_USED__" /D "__ATL_11_USED__" /D\
 "OS_NO_STREAM_SUPPORT" /Fp"$(INTDIR)/IXTMFC42.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug"

DEP_CPP_CTFXM=\
	".\cimpxtsn.hxx"\
	".\Ctfxmfc.nocom.cpp"\
	".\STDAFX.H"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\COMCAT.H"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\ctfxmfc.h"\
	{$(INCLUDE)}"\ctfxmfc.nocom.h"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Hdrentrx.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OLENLS.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\PropertyHelper.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TrCatIDs.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	
# ADD CPP /Yu"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "__XTENSNDLL__" /D\
 "__MFC__" /D "_AFXEXT" /D "_AFXDLL" /D "_MBCS" /D "__ATL_USED__" /D\
 "__ATL_11_USED__" /D "OS_NO_STREAM_SUPPORT" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/IXTMFC42.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/ixtmfd40.pdb" /c $(SOURCE) \
	

"$(INTDIR)\Ctfxmfc.obj" : $(SOURCE) $(DEP_CPP_CTFXM) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"
   $(BuildCmds)

"$(INTDIR)\Ctfxmfc.sbr" : $(SOURCE) $(DEP_CPP_CTFXM) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Release New"

DEP_CPP_CTFXM=\
	".\cimpxtsn.hxx"\
	".\Ctfxmfc.nocom.cpp"\
	".\STDAFX.H"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\COMCAT.H"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\ctfxmfc.h"\
	{$(INCLUDE)}"\ctfxmfc.nocom.h"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Hdrentrx.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OLENLS.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\PropertyHelper.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TrCatIDs.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	
# ADD BASE CPP /Yu"stdafx.h"
# ADD CPP /Yu"stdafx.h"

"$(INTDIR)\Ctfxmfc.obj" : $(SOURCE) $(DEP_CPP_CTFXM) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DEXPROCS" /D "MSWIND" /D "__XTENSNDLL__" /D "__MFC__" /D "_AFXEXT"\
 /D "_AFXDLL" /D "_MBCS" /D "__ATL_USED__" /D "__ATL_11_USED__" /D\
 "OS_NO_STREAM_SUPPORT" /Fp"$(INTDIR)/IXTMFC42.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug New"

DEP_CPP_CTFXM=\
	".\cimpxtsn.hxx"\
	".\Ctfxmfc.nocom.cpp"\
	".\STDAFX.H"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\COMCAT.H"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\ctfxmfc.h"\
	{$(INCLUDE)}"\ctfxmfc.nocom.h"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Hdrentrx.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OLENLS.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\PropertyHelper.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TrCatIDs.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	
# ADD BASE CPP /Yu"stdafx.h"
# ADD CPP /Yu"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "__XTENSNDLL__" /D\
 "__MFC__" /D "_AFXEXT" /D "_AFXDLL" /D "_MBCS" /D "__ATL_USED__" /D\
 "__ATL_11_USED__" /D "OS_NO_STREAM_SUPPORT" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/IXTMFC42.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/ixtmfd42.pdb" /c $(SOURCE) \
	

"$(INTDIR)\Ctfxmfc.obj" : $(SOURCE) $(DEP_CPP_CTFXM) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"
   $(BuildCmds)

"$(INTDIR)\Ctfxmfc.sbr" : $(SOURCE) $(DEP_CPP_CTFXM) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug ATL Base"

DEP_CPP_CTFXM=\
	".\cimpxtsn.hxx"\
	".\Ctfxmfc.nocom.cpp"\
	".\STDAFX.H"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\COMCAT.H"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\ctfxmfc.h"\
	{$(INCLUDE)}"\ctfxmfc.nocom.h"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Hdrentrx.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OLENLS.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\PropertyHelper.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TrCatIDs.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	
# ADD BASE CPP /Yu"stdafx.h"
# ADD CPP /Yu"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D\
 "__ATL_XTENSION_BASE__" /D "WIN32" /D "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D\
 "MSWIND" /D "__XTENSNDLL__" /D "__MFC__" /D "_AFXEXT" /D "_AFXDLL" /D "_MBCS"\
 /D "__ATL_USED__" /D "__ATL_11_USED__" /D "OS_NO_STREAM_SUPPORT"\
 /FR"$(INTDIR)/" /Fp"$(INTDIR)/IXTMAD42.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/ixtmad42.pdb" /c $(SOURCE) \
	

"$(INTDIR)\Ctfxmfc.obj" : $(SOURCE) $(DEP_CPP_CTFXM) "$(INTDIR)"\
 "$(INTDIR)\IXTMAD42.pch"
   $(BuildCmds)

"$(INTDIR)\Ctfxmfc.sbr" : $(SOURCE) $(DEP_CPP_CTFXM) "$(INTDIR)"\
 "$(INTDIR)\IXTMAD42.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Release ATL Base"

DEP_CPP_CTFXM=\
	".\cimpxtsn.hxx"\
	".\Ctfxmfc.nocom.cpp"\
	".\STDAFX.H"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\COMCAT.H"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\ctfxmfc.h"\
	{$(INCLUDE)}"\ctfxmfc.nocom.h"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Hdrentrx.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OLENLS.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\PropertyHelper.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TrCatIDs.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	
# ADD BASE CPP /Yu"stdafx.h"
# ADD CPP /Yu"stdafx.h"

"$(INTDIR)\Ctfxmfc.obj" : $(SOURCE) $(DEP_CPP_CTFXM) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "__ATL_XTENSION_BASE__" /D\
 "WIN32" /D "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "__XTENSNDLL__"\
 /D "__MFC__" /D "_AFXEXT" /D "_AFXDLL" /D "_MBCS" /D "__ATL_USED__" /D\
 "__ATL_11_USED__" /D "OS_NO_STREAM_SUPPORT" /Fp"$(INTDIR)/IXTMFC42.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\XtencAtl.cxx
DEP_CPP_XTENCA=\
	".\cimpxtsn.hxx"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OLENLS.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TrCatIDs.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\WrongTrCatIDs.h"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "ixtmfc32 - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Release New"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug New"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug ATL Base"


BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D\
 "__ATL_XTENSION_BASE__" /D "WIN32" /D "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D\
 "MSWIND" /D "__XTENSNDLL__" /D "__MFC__" /D "_AFXEXT" /D "_AFXDLL" /D "_MBCS"\
 /D "__ATL_USED__" /D "__ATL_11_USED__" /D "OS_NO_STREAM_SUPPORT"\
 /FR"$(INTDIR)/" /Fp"$(INTDIR)/IXTMAD42.pch" /Yu"xtensnp.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/ixtmad42.pdb" /c $(SOURCE) \
	

"$(INTDIR)\XtencAtl.obj" : $(SOURCE) $(DEP_CPP_XTENCA) "$(INTDIR)"\
 "$(INTDIR)\IXTMAD42.pch"
   $(BuildCmds)

"$(INTDIR)\XtencAtl.sbr" : $(SOURCE) $(DEP_CPP_XTENCA) "$(INTDIR)"\
 "$(INTDIR)\IXTMAD42.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Release ATL Base"


"$(INTDIR)\XtencAtl.obj" : $(SOURCE) $(DEP_CPP_XTENCA) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "__ATL_XTENSION_BASE__" /D\
 "WIN32" /D "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "__XTENSNDLL__"\
 /D "__MFC__" /D "_AFXEXT" /D "_AFXDLL" /D "_MBCS" /D "__ATL_USED__" /D\
 "__ATL_11_USED__" /D "OS_NO_STREAM_SUPPORT" /Fp"$(INTDIR)/IXTMFC42.pch"\
 /Yu"xtensnp.hxx" /Fo"$(INTDIR)/" /c $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\XtsnPropAtl.cpp
DEP_CPP_XTSNPR=\
	".\cimpxtsn.hxx"\
	".\enmcprop.hxx"\
	".\enumprop.hxx"\
	".\objpropf.hxx"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OLENLS.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XtsnPropAtl.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "ixtmfc32 - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Release New"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug New"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Debug ATL Base"


BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D\
 "__ATL_XTENSION_BASE__" /D "WIN32" /D "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D\
 "MSWIND" /D "__XTENSNDLL__" /D "__MFC__" /D "_AFXEXT" /D "_AFXDLL" /D "_MBCS"\
 /D "__ATL_USED__" /D "__ATL_11_USED__" /D "OS_NO_STREAM_SUPPORT"\
 /FR"$(INTDIR)/" /Fp"$(INTDIR)/IXTMAD42.pch" /Yu"xtensnp.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/ixtmad42.pdb" /c $(SOURCE) \
	

"$(INTDIR)\XtsnPropAtl.obj" : $(SOURCE) $(DEP_CPP_XTSNPR) "$(INTDIR)"\
 "$(INTDIR)\IXTMAD42.pch"
   $(BuildCmds)

"$(INTDIR)\XtsnPropAtl.sbr" : $(SOURCE) $(DEP_CPP_XTSNPR) "$(INTDIR)"\
 "$(INTDIR)\IXTMAD42.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ixtmfc32 - Win32 Release ATL Base"


"$(INTDIR)\XtsnPropAtl.obj" : $(SOURCE) $(DEP_CPP_XTSNPR) "$(INTDIR)"\
 "$(INTDIR)\IXTMFC42.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "__ATL_XTENSION_BASE__" /D\
 "WIN32" /D "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "__XTENSNDLL__"\
 /D "__MFC__" /D "_AFXEXT" /D "_AFXDLL" /D "_MBCS" /D "__ATL_USED__" /D\
 "__ATL_11_USED__" /D "OS_NO_STREAM_SUPPORT" /Fp"$(INTDIR)/IXTMFC42.pch"\
 /Yu"xtensnp.hxx" /Fo"$(INTDIR)/" /c $(SOURCE)


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
