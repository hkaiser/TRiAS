# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

!IF "$(CFG)" == ""
CFG=ixtnsn32 - Win32 Debug ATL Base
!MESSAGE No configuration specified.  Defaulting to ixtnsn32 - Win32 Debug ATL\
 Base.
!ENDIF 

!IF "$(CFG)" != "ixtnsn32 - Win32 Release" && "$(CFG)" !=\
 "ixtnsn32 - Win32 Debug" && "$(CFG)" != "ixtnsn32 - Win32 Release New" &&\
 "$(CFG)" != "ixtnsn32 - Win32 Debug New" && "$(CFG)" !=\
 "ixtnsn32 - Win32 Debug ATL Base" && "$(CFG)" !=\
 "ixtnsn32 - Win32 Release ATL Base"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "IXTNSN42.MAK" CFG="ixtnsn32 - Win32 Debug ATL Base"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ixtnsn32 - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "ixtnsn32 - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "ixtnsn32 - Win32 Release New" (based on "Win32 (x86) Static Library")
!MESSAGE "ixtnsn32 - Win32 Debug New" (based on "Win32 (x86) Static Library")
!MESSAGE "ixtnsn32 - Win32 Debug ATL Base" (based on\
 "Win32 (x86) Static Library")
!MESSAGE "ixtnsn32 - Win32 Release ATL Base" (based on\
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
# PROP Target_Last_Scanned "ixtnsn32 - Win32 Release ATL Base"
CPP=cl.exe

!IF  "$(CFG)" == "ixtnsn32 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Obj32/Release"
# PROP Intermediate_Dir "Obj32/Release"
OUTDIR=.\Obj32/Release
INTDIR=.\Obj32/Release
# Begin Custom Macros
TargetName=ixtnsr40
# End Custom Macros

ALL : "$(OUTDIR)\ixtnsr40.lib" "..\..\lib32\ixtnsr40.lib"

CLEAN : 
	-@erase "$(INTDIR)\cimpxtsn.obj"
	-@erase "$(INTDIR)\Ctfxmfc.obj"
	-@erase "$(INTDIR)\DBLNUMED.OBJ"
	-@erase "$(INTDIR)\dllbindx.obj"
	-@erase "$(INTDIR)\dummy1.obj"
	-@erase "$(INTDIR)\dummy2.obj"
	-@erase "$(INTDIR)\dummy3.obj"
	-@erase "$(INTDIR)\DUMMY4.OBJ"
	-@erase "$(INTDIR)\dummy5.obj"
	-@erase "$(INTDIR)\DUMPOUT.OBJ"
	-@erase "$(INTDIR)\enmcprop.obj"
	-@erase "$(INTDIR)\enumprop.obj"
	-@erase "$(INTDIR)\EXTREG.OBJ"
	-@erase "$(INTDIR)\HDRENTRX.OBJ"
	-@erase "$(INTDIR)\HELPTEXT.OBJ"
	-@erase "$(INTDIR)\IENUMONR.OBJ"
	-@erase "$(INTDIR)\IENUMSTR.OBJ"
	-@erase "$(INTDIR)\IMPXTCF.OBJ"
	-@erase "$(INTDIR)\IXTNSN42.pch"
	-@erase "$(INTDIR)\NUMEDITX.OBJ"
	-@erase "$(INTDIR)\OBJCONTX.OBJ"
	-@erase "$(INTDIR)\objpropf.obj"
	-@erase "$(INTDIR)\REGISTRY.OBJ"
	-@erase "$(INTDIR)\STRUTIL.OBJ"
	-@erase "$(INTDIR)\VALIDADD.OBJ"
	-@erase "$(INTDIR)\Xtencunk.obj"
	-@erase "$(INTDIR)\XTENSNP.OBJ"
	-@erase "$(INTDIR)\xtsnatl.obj"
	-@erase "$(INTDIR)\xtsnimp.obj"
	-@erase "$(INTDIR)\xtsnprop.obj"
	-@erase "$(OUTDIR)\ixtnsr40.lib"
	-@erase "..\..\lib32\ixtnsr40.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(OUTDIR)/ixtnsn32.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /O2 /Ob2 /D "NDEBUG" /D "STRICT" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "DLL" /D "__XTENSNDLL__" /D "__CV__" /D "WIN32" /D "_WINDOWS" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D "__ATL_11_USED__" /Yu"xtensnp.hxx" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W3 /WX /GX /O2 /Ob2 /D "NDEBUG" /D "STRICT" /D "__XT" /D\
 "__DEXPROCS" /D "MSWIND" /D "DLL" /D "__XTENSNDLL__" /D "__CV__" /D "WIN32" /D\
 "_WINDOWS" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D "__ATL_11_USED__"\
 /Fp"$(INTDIR)/IXTNSN42.pch" /Yu"xtensnp.hxx" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Obj32/Release/
CPP_SBRS=.\.
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/IXTNSN42.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"Obj32/Release\ixtnsr40.lib"
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/ixtnsr40.lib" 
LIB32_OBJS= \
	"$(INTDIR)\cimpxtsn.obj" \
	"$(INTDIR)\Ctfxmfc.obj" \
	"$(INTDIR)\DBLNUMED.OBJ" \
	"$(INTDIR)\dllbindx.obj" \
	"$(INTDIR)\dummy1.obj" \
	"$(INTDIR)\dummy2.obj" \
	"$(INTDIR)\dummy3.obj" \
	"$(INTDIR)\DUMMY4.OBJ" \
	"$(INTDIR)\dummy5.obj" \
	"$(INTDIR)\DUMPOUT.OBJ" \
	"$(INTDIR)\enmcprop.obj" \
	"$(INTDIR)\enumprop.obj" \
	"$(INTDIR)\EXTREG.OBJ" \
	"$(INTDIR)\HDRENTRX.OBJ" \
	"$(INTDIR)\HELPTEXT.OBJ" \
	"$(INTDIR)\IENUMONR.OBJ" \
	"$(INTDIR)\IENUMSTR.OBJ" \
	"$(INTDIR)\IMPXTCF.OBJ" \
	"$(INTDIR)\NUMEDITX.OBJ" \
	"$(INTDIR)\OBJCONTX.OBJ" \
	"$(INTDIR)\objpropf.obj" \
	"$(INTDIR)\REGISTRY.OBJ" \
	"$(INTDIR)\STRUTIL.OBJ" \
	"$(INTDIR)\VALIDADD.OBJ" \
	"$(INTDIR)\Xtencunk.obj" \
	"$(INTDIR)\XTENSNP.OBJ" \
	"$(INTDIR)\xtsnatl.obj" \
	"$(INTDIR)\xtsnimp.obj" \
	"$(INTDIR)\xtsnprop.obj"

"$(OUTDIR)\ixtnsr40.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

# Begin Custom Build - Copying created library ...
TargetPath=.\Obj32\Release\ixtnsr40.lib
TargetName=ixtnsr40
InputPath=.\Obj32\Release\ixtnsr40.lib
SOURCE=$(InputPath)

"\triasdev.mvc\lib32\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   copy "$(TargetPath)" \triasdev.mvc\lib32

# End Custom Build

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Obj32/Debug"
# PROP Intermediate_Dir "Obj32/Debug"
OUTDIR=.\Obj32/Debug
INTDIR=.\Obj32/Debug
# Begin Custom Macros
TargetName=ixtnsd40
# End Custom Macros

ALL : "$(OUTDIR)\ixtnsd40.lib" "$(OUTDIR)\IXTNSN42.bsc"\
 "..\..\lib32\ixtnsd40.lib"

CLEAN : 
	-@erase "$(INTDIR)\cimpxtsn.obj"
	-@erase "$(INTDIR)\cimpxtsn.sbr"
	-@erase "$(INTDIR)\Ctfxmfc.obj"
	-@erase "$(INTDIR)\Ctfxmfc.sbr"
	-@erase "$(INTDIR)\DBLNUMED.OBJ"
	-@erase "$(INTDIR)\DBLNUMED.SBR"
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
	-@erase "$(INTDIR)\DUMPOUT.OBJ"
	-@erase "$(INTDIR)\DUMPOUT.SBR"
	-@erase "$(INTDIR)\enmcprop.obj"
	-@erase "$(INTDIR)\enmcprop.sbr"
	-@erase "$(INTDIR)\enumprop.obj"
	-@erase "$(INTDIR)\enumprop.sbr"
	-@erase "$(INTDIR)\EXTREG.OBJ"
	-@erase "$(INTDIR)\EXTREG.SBR"
	-@erase "$(INTDIR)\HDRENTRX.OBJ"
	-@erase "$(INTDIR)\HDRENTRX.SBR"
	-@erase "$(INTDIR)\HELPTEXT.OBJ"
	-@erase "$(INTDIR)\HELPTEXT.SBR"
	-@erase "$(INTDIR)\IENUMONR.OBJ"
	-@erase "$(INTDIR)\IENUMONR.SBR"
	-@erase "$(INTDIR)\IENUMSTR.OBJ"
	-@erase "$(INTDIR)\IENUMSTR.SBR"
	-@erase "$(INTDIR)\IMPXTCF.OBJ"
	-@erase "$(INTDIR)\IMPXTCF.SBR"
	-@erase "$(INTDIR)\ixtnsd40.idb"
	-@erase "$(INTDIR)\ixtnsd40.pdb"
	-@erase "$(INTDIR)\ixtnsn32.pch"
	-@erase "$(INTDIR)\NUMEDITX.OBJ"
	-@erase "$(INTDIR)\NUMEDITX.SBR"
	-@erase "$(INTDIR)\OBJCONTX.OBJ"
	-@erase "$(INTDIR)\OBJCONTX.SBR"
	-@erase "$(INTDIR)\objpropf.obj"
	-@erase "$(INTDIR)\objpropf.sbr"
	-@erase "$(INTDIR)\REGISTRY.OBJ"
	-@erase "$(INTDIR)\REGISTRY.SBR"
	-@erase "$(INTDIR)\STRUTIL.OBJ"
	-@erase "$(INTDIR)\STRUTIL.SBR"
	-@erase "$(INTDIR)\VALIDADD.OBJ"
	-@erase "$(INTDIR)\VALIDADD.SBR"
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
	-@erase "$(OUTDIR)\ixtnsd40.lib"
	-@erase "$(OUTDIR)\IXTNSN42.bsc"
	-@erase "..\..\lib32\ixtnsd40.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(OUTDIR)/ixtnsn32.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "STRICT" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "DLL" /D "__XTENSNDLL__" /D "__CV__" /D "WIN32" /D "_WINDOWS" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D "__ATL_11_USED__" /FR /Fp"Obj32/Debug/ixtnsn32.pch" /Yu"xtensnp.hxx" /Fd"Obj32/Debug/ixtnsd40.pdb" /c
CPP_PROJ=/nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "STRICT" /D\
 "__XT" /D "__DEXPROCS" /D "MSWIND" /D "DLL" /D "__XTENSNDLL__" /D "__CV__" /D\
 "WIN32" /D "_WINDOWS" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D\
 "__ATL_11_USED__" /FR"$(INTDIR)/" /Fp"$(INTDIR)/ixtnsn32.pch" /Yu"xtensnp.hxx"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/ixtnsd40.pdb" /c 
CPP_OBJS=.\Obj32/Debug/
CPP_SBRS=.\Obj32/Debug/
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/IXTNSN42.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\cimpxtsn.sbr" \
	"$(INTDIR)\Ctfxmfc.sbr" \
	"$(INTDIR)\DBLNUMED.SBR" \
	"$(INTDIR)\dllbindx.sbr" \
	"$(INTDIR)\dummy1.sbr" \
	"$(INTDIR)\dummy2.sbr" \
	"$(INTDIR)\dummy3.sbr" \
	"$(INTDIR)\DUMMY4.SBR" \
	"$(INTDIR)\dummy5.sbr" \
	"$(INTDIR)\DUMPOUT.SBR" \
	"$(INTDIR)\enmcprop.sbr" \
	"$(INTDIR)\enumprop.sbr" \
	"$(INTDIR)\EXTREG.SBR" \
	"$(INTDIR)\HDRENTRX.SBR" \
	"$(INTDIR)\HELPTEXT.SBR" \
	"$(INTDIR)\IENUMONR.SBR" \
	"$(INTDIR)\IENUMSTR.SBR" \
	"$(INTDIR)\IMPXTCF.SBR" \
	"$(INTDIR)\NUMEDITX.SBR" \
	"$(INTDIR)\OBJCONTX.SBR" \
	"$(INTDIR)\objpropf.sbr" \
	"$(INTDIR)\REGISTRY.SBR" \
	"$(INTDIR)\STRUTIL.SBR" \
	"$(INTDIR)\VALIDADD.SBR" \
	"$(INTDIR)\Xtencunk.sbr" \
	"$(INTDIR)\XTENSNP.SBR" \
	"$(INTDIR)\xtsnatl.sbr" \
	"$(INTDIR)\xtsnimp.sbr" \
	"$(INTDIR)\xtsnprop.sbr"

"$(OUTDIR)\IXTNSN42.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"Obj32/Debug\ixtnsd40.lib"
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/ixtnsd40.lib" 
LIB32_OBJS= \
	"$(INTDIR)\cimpxtsn.obj" \
	"$(INTDIR)\Ctfxmfc.obj" \
	"$(INTDIR)\DBLNUMED.OBJ" \
	"$(INTDIR)\dllbindx.obj" \
	"$(INTDIR)\dummy1.obj" \
	"$(INTDIR)\dummy2.obj" \
	"$(INTDIR)\dummy3.obj" \
	"$(INTDIR)\DUMMY4.OBJ" \
	"$(INTDIR)\dummy5.obj" \
	"$(INTDIR)\DUMPOUT.OBJ" \
	"$(INTDIR)\enmcprop.obj" \
	"$(INTDIR)\enumprop.obj" \
	"$(INTDIR)\EXTREG.OBJ" \
	"$(INTDIR)\HDRENTRX.OBJ" \
	"$(INTDIR)\HELPTEXT.OBJ" \
	"$(INTDIR)\IENUMONR.OBJ" \
	"$(INTDIR)\IENUMSTR.OBJ" \
	"$(INTDIR)\IMPXTCF.OBJ" \
	"$(INTDIR)\NUMEDITX.OBJ" \
	"$(INTDIR)\OBJCONTX.OBJ" \
	"$(INTDIR)\objpropf.obj" \
	"$(INTDIR)\REGISTRY.OBJ" \
	"$(INTDIR)\STRUTIL.OBJ" \
	"$(INTDIR)\VALIDADD.OBJ" \
	"$(INTDIR)\Xtencunk.obj" \
	"$(INTDIR)\XTENSNP.OBJ" \
	"$(INTDIR)\xtsnatl.obj" \
	"$(INTDIR)\xtsnimp.obj" \
	"$(INTDIR)\xtsnprop.obj"

"$(OUTDIR)\ixtnsd40.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

# Begin Custom Build - Copying created library ...
OutDir=.\Obj32/Debug
TargetPath=.\Obj32\Debug\ixtnsd40.lib
TargetName=ixtnsd40
InputPath=.\Obj32\Debug\ixtnsd40.lib
SOURCE=$(InputPath)

"\triasdev.mvc\lib32\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   copy "$(TargetPath)" \triasdev.mvc\lib32
   if exist "$(OutDir)\$(TargetName).pdb" copy "$(OutDir)\$(TargetName).pdb"\
                                                      \triasdev.mvc\lib32

# End Custom Build

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release New"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ixtnsn32"
# PROP BASE Intermediate_Dir "ixtnsn32"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Obj42/Release"
# PROP Intermediate_Dir "Obj42/Release"
# PROP Target_Dir ""
OUTDIR=.\Obj42/Release
INTDIR=.\Obj42/Release
# Begin Custom Macros
TargetName=ixtnsr42
# End Custom Macros

ALL : "$(OUTDIR)\ixtnsr42.lib" "..\..\lib32\ixtnsr42.lib"

CLEAN : 
	-@erase "$(INTDIR)\cimpxtsn.obj"
	-@erase "$(INTDIR)\Ctfxmfc.obj"
	-@erase "$(INTDIR)\DBLNUMED.OBJ"
	-@erase "$(INTDIR)\dllbindx.obj"
	-@erase "$(INTDIR)\dummy1.obj"
	-@erase "$(INTDIR)\dummy2.obj"
	-@erase "$(INTDIR)\dummy3.obj"
	-@erase "$(INTDIR)\DUMMY4.OBJ"
	-@erase "$(INTDIR)\dummy5.obj"
	-@erase "$(INTDIR)\DUMPOUT.OBJ"
	-@erase "$(INTDIR)\enmcprop.obj"
	-@erase "$(INTDIR)\enumprop.obj"
	-@erase "$(INTDIR)\EXTREG.OBJ"
	-@erase "$(INTDIR)\HDRENTRX.OBJ"
	-@erase "$(INTDIR)\HELPTEXT.OBJ"
	-@erase "$(INTDIR)\IENUMONR.OBJ"
	-@erase "$(INTDIR)\IENUMSTR.OBJ"
	-@erase "$(INTDIR)\IMPXTCF.OBJ"
	-@erase "$(INTDIR)\IXTNSN42.pch"
	-@erase "$(INTDIR)\NUMEDITX.OBJ"
	-@erase "$(INTDIR)\OBJCONTX.OBJ"
	-@erase "$(INTDIR)\objpropf.obj"
	-@erase "$(INTDIR)\REGISTRY.OBJ"
	-@erase "$(INTDIR)\STRUTIL.OBJ"
	-@erase "$(INTDIR)\VALIDADD.OBJ"
	-@erase "$(INTDIR)\Xtencunk.obj"
	-@erase "$(INTDIR)\XTENSNP.OBJ"
	-@erase "$(INTDIR)\xtsnatl.obj"
	-@erase "$(INTDIR)\xtsnimp.obj"
	-@erase "$(INTDIR)\xtsnprop.obj"
	-@erase "$(OUTDIR)\ixtnsr42.lib"
	-@erase "..\..\lib32\ixtnsr42.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /WX /GX /O2 /Ob2 /D "NDEBUG" /D "STRICT" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "DLL" /D "__XTENSNDLL__" /D "__CV__" /D "WIN32" /D "_WINDOWS" /D "__ATL_USED__" /Yu"xtensnp.hxx" /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MD /W3 /WX /GX /O2 /Ob2 /D "NDEBUG" /D "__ATL_11_USED__" /D "STRICT" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "DLL" /D "__XTENSNDLL__" /D "__CV__" /D "WIN32" /D "_WINDOWS" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /Yu"xtensnp.hxx" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W3 /WX /GX /O2 /Ob2 /D "NDEBUG" /D "__ATL_11_USED__" /D\
 "STRICT" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "DLL" /D "__XTENSNDLL__" /D\
 "__CV__" /D "WIN32" /D "_WINDOWS" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT"\
 /Fp"$(INTDIR)/IXTNSN42.pch" /Yu"xtensnp.hxx" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Obj42/Release/
CPP_SBRS=.\.
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/IXTNSN42.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"Obj32/Release\ixtnsr40.lib"
# ADD LIB32 /nologo /out:"Obj42/Release\ixtnsr42.lib"
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/ixtnsr42.lib" 
LIB32_OBJS= \
	"$(INTDIR)\cimpxtsn.obj" \
	"$(INTDIR)\Ctfxmfc.obj" \
	"$(INTDIR)\DBLNUMED.OBJ" \
	"$(INTDIR)\dllbindx.obj" \
	"$(INTDIR)\dummy1.obj" \
	"$(INTDIR)\dummy2.obj" \
	"$(INTDIR)\dummy3.obj" \
	"$(INTDIR)\DUMMY4.OBJ" \
	"$(INTDIR)\dummy5.obj" \
	"$(INTDIR)\DUMPOUT.OBJ" \
	"$(INTDIR)\enmcprop.obj" \
	"$(INTDIR)\enumprop.obj" \
	"$(INTDIR)\EXTREG.OBJ" \
	"$(INTDIR)\HDRENTRX.OBJ" \
	"$(INTDIR)\HELPTEXT.OBJ" \
	"$(INTDIR)\IENUMONR.OBJ" \
	"$(INTDIR)\IENUMSTR.OBJ" \
	"$(INTDIR)\IMPXTCF.OBJ" \
	"$(INTDIR)\NUMEDITX.OBJ" \
	"$(INTDIR)\OBJCONTX.OBJ" \
	"$(INTDIR)\objpropf.obj" \
	"$(INTDIR)\REGISTRY.OBJ" \
	"$(INTDIR)\STRUTIL.OBJ" \
	"$(INTDIR)\VALIDADD.OBJ" \
	"$(INTDIR)\Xtencunk.obj" \
	"$(INTDIR)\XTENSNP.OBJ" \
	"$(INTDIR)\xtsnatl.obj" \
	"$(INTDIR)\xtsnimp.obj" \
	"$(INTDIR)\xtsnprop.obj"

"$(OUTDIR)\ixtnsr42.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

# Begin Custom Build - Copying created library ...
TargetPath=.\Obj42\Release\ixtnsr42.lib
TargetName=ixtnsr42
InputPath=.\Obj42\Release\ixtnsr42.lib
SOURCE=$(InputPath)

"\triasdev.mvc\lib32\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   copy "$(TargetPath)" \triasdev.mvc\lib32

# End Custom Build

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug New"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ixtnsn30"
# PROP BASE Intermediate_Dir "ixtnsn30"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Atl42/Debug"
# PROP Intermediate_Dir "Atl42/Debug"
# PROP Target_Dir ""
OUTDIR=.\Atl42/Debug
INTDIR=.\Atl42/Debug
# Begin Custom Macros
TargetName=ixtnsd42
# End Custom Macros

ALL : ".\Obj42\Debug\ixtnsd42.lib" ".\Obj42\Debug\IXTNSN42.bsc"\
 "..\..\lib32\ixtnsd42.lib"

CLEAN : 
	-@erase "..\..\lib32\ixtnsd42.lib"
	-@erase ".\Obj42\Debug\cimpxtsn.obj"
	-@erase ".\Obj42\Debug\cimpxtsn.sbr"
	-@erase ".\Obj42\Debug\Ctfxmfc.obj"
	-@erase ".\Obj42\Debug\Ctfxmfc.sbr"
	-@erase ".\Obj42\Debug\DBLNUMED.OBJ"
	-@erase ".\Obj42\Debug\DBLNUMED.SBR"
	-@erase ".\Obj42\Debug\dllbindx.obj"
	-@erase ".\Obj42\Debug\dllbindx.sbr"
	-@erase ".\Obj42\Debug\dummy1.obj"
	-@erase ".\Obj42\Debug\dummy1.sbr"
	-@erase ".\Obj42\Debug\dummy2.obj"
	-@erase ".\Obj42\Debug\dummy2.sbr"
	-@erase ".\Obj42\Debug\dummy3.obj"
	-@erase ".\Obj42\Debug\dummy3.sbr"
	-@erase ".\Obj42\Debug\DUMMY4.OBJ"
	-@erase ".\Obj42\Debug\DUMMY4.SBR"
	-@erase ".\Obj42\Debug\dummy5.obj"
	-@erase ".\Obj42\Debug\dummy5.sbr"
	-@erase ".\Obj42\Debug\DUMPOUT.OBJ"
	-@erase ".\Obj42\Debug\DUMPOUT.SBR"
	-@erase ".\Obj42\Debug\enmcprop.obj"
	-@erase ".\Obj42\Debug\enmcprop.sbr"
	-@erase ".\Obj42\Debug\enumprop.obj"
	-@erase ".\Obj42\Debug\enumprop.sbr"
	-@erase ".\Obj42\Debug\EXTREG.OBJ"
	-@erase ".\Obj42\Debug\EXTREG.SBR"
	-@erase ".\Obj42\Debug\HDRENTRX.OBJ"
	-@erase ".\Obj42\Debug\HDRENTRX.SBR"
	-@erase ".\Obj42\Debug\HELPTEXT.OBJ"
	-@erase ".\Obj42\Debug\HELPTEXT.SBR"
	-@erase ".\Obj42\Debug\IENUMONR.OBJ"
	-@erase ".\Obj42\Debug\IENUMONR.SBR"
	-@erase ".\Obj42\Debug\IENUMSTR.OBJ"
	-@erase ".\Obj42\Debug\IENUMSTR.SBR"
	-@erase ".\Obj42\Debug\IMPXTCF.OBJ"
	-@erase ".\Obj42\Debug\IMPXTCF.SBR"
	-@erase ".\Obj42\Debug\ixtnsd42.idb"
	-@erase ".\Obj42\Debug\ixtnsd42.lib"
	-@erase ".\Obj42\Debug\ixtnsd42.pdb"
	-@erase ".\Obj42\Debug\ixtnsn32.pch"
	-@erase ".\Obj42\Debug\IXTNSN42.bsc"
	-@erase ".\Obj42\Debug\NUMEDITX.OBJ"
	-@erase ".\Obj42\Debug\NUMEDITX.SBR"
	-@erase ".\Obj42\Debug\OBJCONTX.OBJ"
	-@erase ".\Obj42\Debug\OBJCONTX.SBR"
	-@erase ".\Obj42\Debug\objpropf.obj"
	-@erase ".\Obj42\Debug\objpropf.sbr"
	-@erase ".\Obj42\Debug\REGISTRY.OBJ"
	-@erase ".\Obj42\Debug\REGISTRY.SBR"
	-@erase ".\Obj42\Debug\STRUTIL.OBJ"
	-@erase ".\Obj42\Debug\STRUTIL.SBR"
	-@erase ".\Obj42\Debug\VALIDADD.OBJ"
	-@erase ".\Obj42\Debug\VALIDADD.SBR"
	-@erase ".\Obj42\Debug\Xtencunk.obj"
	-@erase ".\Obj42\Debug\Xtencunk.sbr"
	-@erase ".\Obj42\Debug\XTENSNP.OBJ"
	-@erase ".\Obj42\Debug\XTENSNP.SBR"
	-@erase ".\Obj42\Debug\xtsnatl.obj"
	-@erase ".\Obj42\Debug\xtsnatl.sbr"
	-@erase ".\Obj42\Debug\xtsnimp.obj"
	-@erase ".\Obj42\Debug\xtsnimp.sbr"
	-@erase ".\Obj42\Debug\xtsnprop.obj"
	-@erase ".\Obj42\Debug\xtsnprop.sbr"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "STRICT" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "DLL" /D "__XTENSNDLL__" /D "__CV__" /D "WIN32" /D "_WINDOWS" /D "__ATL_USED__" /FR /Fp"Obj32/Debug/ixtnsn32.pch" /Yu"xtensnp.hxx" /Fd"Obj32/Debug/ixtnsd40.pdb" /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "__ATL_11_USED__" /D "STRICT" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "DLL" /D "__XTENSNDLL__" /D "__CV__" /D "WIN32" /D "_WINDOWS" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /FR"Obj42/Debug/" /Fp"Obj42/Debug/ixtnsn32.pch" /Yu"xtensnp.hxx" /Fo"Obj42/Debug/" /Fd"Obj42/Debug/ixtnsd42.pdb" /c
CPP_PROJ=/nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D\
 "__ATL_11_USED__" /D "STRICT" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "DLL" /D\
 "__XTENSNDLL__" /D "__CV__" /D "WIN32" /D "_WINDOWS" /D "__ATL_USED__" /D\
 "OS_NO_STREAM_SUPPORT" /FR"Obj42/Debug/" /Fp"Obj42/Debug/ixtnsn32.pch"\
 /Yu"xtensnp.hxx" /Fo"Obj42/Debug/" /Fd"Obj42/Debug/ixtnsd42.pdb" /c 
CPP_OBJS=.\Obj42/Debug/
CPP_SBRS=.\Obj42/Debug/
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"Obj42/Debug/IXTNSN42.bsc"
BSC32_FLAGS=/nologo /o"Obj42/Debug/IXTNSN42.bsc" 
BSC32_SBRS= \
	".\Obj42\Debug\cimpxtsn.sbr" \
	".\Obj42\Debug\Ctfxmfc.sbr" \
	".\Obj42\Debug\DBLNUMED.SBR" \
	".\Obj42\Debug\dllbindx.sbr" \
	".\Obj42\Debug\dummy1.sbr" \
	".\Obj42\Debug\dummy2.sbr" \
	".\Obj42\Debug\dummy3.sbr" \
	".\Obj42\Debug\DUMMY4.SBR" \
	".\Obj42\Debug\dummy5.sbr" \
	".\Obj42\Debug\DUMPOUT.SBR" \
	".\Obj42\Debug\enmcprop.sbr" \
	".\Obj42\Debug\enumprop.sbr" \
	".\Obj42\Debug\EXTREG.SBR" \
	".\Obj42\Debug\HDRENTRX.SBR" \
	".\Obj42\Debug\HELPTEXT.SBR" \
	".\Obj42\Debug\IENUMONR.SBR" \
	".\Obj42\Debug\IENUMSTR.SBR" \
	".\Obj42\Debug\IMPXTCF.SBR" \
	".\Obj42\Debug\NUMEDITX.SBR" \
	".\Obj42\Debug\OBJCONTX.SBR" \
	".\Obj42\Debug\objpropf.sbr" \
	".\Obj42\Debug\REGISTRY.SBR" \
	".\Obj42\Debug\STRUTIL.SBR" \
	".\Obj42\Debug\VALIDADD.SBR" \
	".\Obj42\Debug\Xtencunk.sbr" \
	".\Obj42\Debug\XTENSNP.SBR" \
	".\Obj42\Debug\xtsnatl.sbr" \
	".\Obj42\Debug\xtsnimp.sbr" \
	".\Obj42\Debug\xtsnprop.sbr"

".\Obj42\Debug\IXTNSN42.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"Obj32/Debug\ixtnsd40.lib"
# ADD LIB32 /nologo /out:"Obj42/Debug\ixtnsd42.lib"
LIB32_FLAGS=/nologo /out:"Obj42/Debug\ixtnsd42.lib" 
LIB32_OBJS= \
	".\Obj42\Debug\cimpxtsn.obj" \
	".\Obj42\Debug\Ctfxmfc.obj" \
	".\Obj42\Debug\DBLNUMED.OBJ" \
	".\Obj42\Debug\dllbindx.obj" \
	".\Obj42\Debug\dummy1.obj" \
	".\Obj42\Debug\dummy2.obj" \
	".\Obj42\Debug\dummy3.obj" \
	".\Obj42\Debug\DUMMY4.OBJ" \
	".\Obj42\Debug\dummy5.obj" \
	".\Obj42\Debug\DUMPOUT.OBJ" \
	".\Obj42\Debug\enmcprop.obj" \
	".\Obj42\Debug\enumprop.obj" \
	".\Obj42\Debug\EXTREG.OBJ" \
	".\Obj42\Debug\HDRENTRX.OBJ" \
	".\Obj42\Debug\HELPTEXT.OBJ" \
	".\Obj42\Debug\IENUMONR.OBJ" \
	".\Obj42\Debug\IENUMSTR.OBJ" \
	".\Obj42\Debug\IMPXTCF.OBJ" \
	".\Obj42\Debug\NUMEDITX.OBJ" \
	".\Obj42\Debug\OBJCONTX.OBJ" \
	".\Obj42\Debug\objpropf.obj" \
	".\Obj42\Debug\REGISTRY.OBJ" \
	".\Obj42\Debug\STRUTIL.OBJ" \
	".\Obj42\Debug\VALIDADD.OBJ" \
	".\Obj42\Debug\Xtencunk.obj" \
	".\Obj42\Debug\XTENSNP.OBJ" \
	".\Obj42\Debug\xtsnatl.obj" \
	".\Obj42\Debug\xtsnimp.obj" \
	".\Obj42\Debug\xtsnprop.obj"

".\Obj42\Debug\ixtnsd42.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

# Begin Custom Build - Copying created library ...
OutDir=.\Atl42/Debug
TargetPath=.\Obj42\Debug\ixtnsd42.lib
TargetName=ixtnsd42
InputPath=.\Obj42\Debug\ixtnsd42.lib
SOURCE=$(InputPath)

"\triasdev.mvc\lib32\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   copy "$(TargetPath)" \triasdev.mvc\lib32
   if exist "$(OutDir)\$(TargetName).pdb" copy "$(OutDir)\$(TargetName).pdb"\
                                                      \triasdev.mvc\lib32

# End Custom Build

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug ATL Base"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ixtnsn30"
# PROP BASE Intermediate_Dir "ixtnsn30"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Atl42/Debug"
# PROP Intermediate_Dir "Atl42/Debug"
# PROP Target_Dir ""
OUTDIR=.\Atl42/Debug
INTDIR=.\Atl42/Debug
# Begin Custom Macros
TargetName=IxtAtd42
# End Custom Macros

ALL : "$(OUTDIR)\IxtAtd42.lib" "$(OUTDIR)\IXTNSN42.bsc"\
 "..\..\lib32\IxtAtd42.lib"

CLEAN : 
	-@erase "$(INTDIR)\Ctfxmfc.obj"
	-@erase "$(INTDIR)\Ctfxmfc.sbr"
	-@erase "$(INTDIR)\DBLNUMED.OBJ"
	-@erase "$(INTDIR)\DBLNUMED.SBR"
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
	-@erase "$(INTDIR)\DUMPOUT.OBJ"
	-@erase "$(INTDIR)\DUMPOUT.SBR"
	-@erase "$(INTDIR)\enmcprop.obj"
	-@erase "$(INTDIR)\enmcprop.sbr"
	-@erase "$(INTDIR)\enumprop.obj"
	-@erase "$(INTDIR)\enumprop.sbr"
	-@erase "$(INTDIR)\EXTREG.OBJ"
	-@erase "$(INTDIR)\EXTREG.SBR"
	-@erase "$(INTDIR)\HDRENTRX.OBJ"
	-@erase "$(INTDIR)\HDRENTRX.SBR"
	-@erase "$(INTDIR)\HELPTEXT.OBJ"
	-@erase "$(INTDIR)\HELPTEXT.SBR"
	-@erase "$(INTDIR)\IENUMONR.OBJ"
	-@erase "$(INTDIR)\IENUMONR.SBR"
	-@erase "$(INTDIR)\IENUMSTR.OBJ"
	-@erase "$(INTDIR)\IENUMSTR.SBR"
	-@erase "$(INTDIR)\IxtAtd42.idb"
	-@erase "$(INTDIR)\IxtAtd42.pch"
	-@erase "$(INTDIR)\IxtAtd42.pdb"
	-@erase "$(INTDIR)\NUMEDITX.OBJ"
	-@erase "$(INTDIR)\NUMEDITX.SBR"
	-@erase "$(INTDIR)\OBJCONTX.OBJ"
	-@erase "$(INTDIR)\OBJCONTX.SBR"
	-@erase "$(INTDIR)\objpropf.obj"
	-@erase "$(INTDIR)\objpropf.sbr"
	-@erase "$(INTDIR)\REGISTRY.OBJ"
	-@erase "$(INTDIR)\REGISTRY.SBR"
	-@erase "$(INTDIR)\STRUTIL.OBJ"
	-@erase "$(INTDIR)\STRUTIL.SBR"
	-@erase "$(INTDIR)\VALIDADD.OBJ"
	-@erase "$(INTDIR)\VALIDADD.SBR"
	-@erase "$(INTDIR)\XtencAtl.obj"
	-@erase "$(INTDIR)\XtencAtl.sbr"
	-@erase "$(INTDIR)\XTENSNP.OBJ"
	-@erase "$(INTDIR)\XTENSNP.SBR"
	-@erase "$(INTDIR)\xtsnatl.obj"
	-@erase "$(INTDIR)\xtsnatl.sbr"
	-@erase "$(INTDIR)\XtsnImpAtl.obj"
	-@erase "$(INTDIR)\XtsnImpAtl.sbr"
	-@erase "$(INTDIR)\xtsnprop.obj"
	-@erase "$(INTDIR)\xtsnprop.sbr"
	-@erase "$(OUTDIR)\IxtAtd42.lib"
	-@erase "$(OUTDIR)\IXTNSN42.bsc"
	-@erase "..\..\lib32\IxtAtd42.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "STRICT" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "DLL" /D "__XTENSNDLL__" /D "__CV__" /D "WIN32" /D "_WINDOWS" /D "__ATL_USED__" /D "__ATL_11_USED__" /FR /Fp"Obj42/Debug/ixtnsn32.pch" /Yu"xtensnp.hxx" /Fd"Obj42/Debug/ixtnsd42.pdb" /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "__ATL_11_USED__" /D "__ATL_XTENSION_BASE__" /D "STRICT" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "DLL" /D "__XTENSNDLL__" /D "__CV__" /D "WIN32" /D "_WINDOWS" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /FR /Fp"Atl42/Debug/IxtAtd42.pch" /Yu"xtensnp.hxx" /Fd"Atl42/Debug/IxtAtd42.pdb" /c
CPP_PROJ=/nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D\
 "__ATL_11_USED__" /D "__ATL_XTENSION_BASE__" /D "STRICT" /D "__XT" /D\
 "__DEXPROCS" /D "MSWIND" /D "DLL" /D "__XTENSNDLL__" /D "__CV__" /D "WIN32" /D\
 "_WINDOWS" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/IxtAtd42.pch" /Yu"xtensnp.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/IxtAtd42.pdb" /c 
CPP_OBJS=.\Atl42/Debug/
CPP_SBRS=.\Atl42/Debug/
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/IXTNSN42.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Ctfxmfc.sbr" \
	"$(INTDIR)\DBLNUMED.SBR" \
	"$(INTDIR)\dllbindx.sbr" \
	"$(INTDIR)\dummy1.sbr" \
	"$(INTDIR)\dummy2.sbr" \
	"$(INTDIR)\dummy3.sbr" \
	"$(INTDIR)\DUMMY4.SBR" \
	"$(INTDIR)\DUMPOUT.SBR" \
	"$(INTDIR)\enmcprop.sbr" \
	"$(INTDIR)\enumprop.sbr" \
	"$(INTDIR)\EXTREG.SBR" \
	"$(INTDIR)\HDRENTRX.SBR" \
	"$(INTDIR)\HELPTEXT.SBR" \
	"$(INTDIR)\IENUMONR.SBR" \
	"$(INTDIR)\IENUMSTR.SBR" \
	"$(INTDIR)\NUMEDITX.SBR" \
	"$(INTDIR)\OBJCONTX.SBR" \
	"$(INTDIR)\objpropf.sbr" \
	"$(INTDIR)\REGISTRY.SBR" \
	"$(INTDIR)\STRUTIL.SBR" \
	"$(INTDIR)\VALIDADD.SBR" \
	"$(INTDIR)\XtencAtl.sbr" \
	"$(INTDIR)\XTENSNP.SBR" \
	"$(INTDIR)\xtsnatl.sbr" \
	"$(INTDIR)\XtsnImpAtl.sbr" \
	"$(INTDIR)\xtsnprop.sbr"

"$(OUTDIR)\IXTNSN42.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"Obj42/Debug\ixtnsd42.lib"
# ADD LIB32 /nologo /out:"Atl42/Debug\IxtAtd42.lib"
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/IxtAtd42.lib" 
LIB32_OBJS= \
	"$(INTDIR)\Ctfxmfc.obj" \
	"$(INTDIR)\DBLNUMED.OBJ" \
	"$(INTDIR)\dllbindx.obj" \
	"$(INTDIR)\dummy1.obj" \
	"$(INTDIR)\dummy2.obj" \
	"$(INTDIR)\dummy3.obj" \
	"$(INTDIR)\DUMMY4.OBJ" \
	"$(INTDIR)\DUMPOUT.OBJ" \
	"$(INTDIR)\enmcprop.obj" \
	"$(INTDIR)\enumprop.obj" \
	"$(INTDIR)\EXTREG.OBJ" \
	"$(INTDIR)\HDRENTRX.OBJ" \
	"$(INTDIR)\HELPTEXT.OBJ" \
	"$(INTDIR)\IENUMONR.OBJ" \
	"$(INTDIR)\IENUMSTR.OBJ" \
	"$(INTDIR)\NUMEDITX.OBJ" \
	"$(INTDIR)\OBJCONTX.OBJ" \
	"$(INTDIR)\objpropf.obj" \
	"$(INTDIR)\REGISTRY.OBJ" \
	"$(INTDIR)\STRUTIL.OBJ" \
	"$(INTDIR)\VALIDADD.OBJ" \
	"$(INTDIR)\XtencAtl.obj" \
	"$(INTDIR)\XTENSNP.OBJ" \
	"$(INTDIR)\xtsnatl.obj" \
	"$(INTDIR)\XtsnImpAtl.obj" \
	"$(INTDIR)\xtsnprop.obj"

"$(OUTDIR)\IxtAtd42.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

# Begin Custom Build - Copying created library ...
OutDir=.\Atl42/Debug
TargetPath=.\Atl42\Debug\IxtAtd42.lib
TargetName=IxtAtd42
InputPath=.\Atl42\Debug\IxtAtd42.lib
SOURCE=$(InputPath)

"\triasdev.mvc\lib32\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   copy "$(TargetPath)" \triasdev.mvc\lib32
   if exist "$(OutDir)\$(TargetName).pdb" copy "$(OutDir)\$(TargetName).pdb"\
                  \triasdev.mvc\lib32

# End Custom Build

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release ATL Base"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ixtnsn32"
# PROP BASE Intermediate_Dir "ixtnsn32"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Atl42/Release"
# PROP Intermediate_Dir "Atl42/Release"
# PROP Target_Dir ""
OUTDIR=.\Atl42/Release
INTDIR=.\Atl42/Release
# Begin Custom Macros
TargetName=ixtAtr42
# End Custom Macros

ALL : "$(OUTDIR)\ixtAtr42.lib" "..\..\lib32\ixtAtr42.lib"

CLEAN : 
	-@erase "$(INTDIR)\Ctfxmfc.obj"
	-@erase "$(INTDIR)\DBLNUMED.OBJ"
	-@erase "$(INTDIR)\dllbindx.obj"
	-@erase "$(INTDIR)\dummy1.obj"
	-@erase "$(INTDIR)\dummy2.obj"
	-@erase "$(INTDIR)\dummy3.obj"
	-@erase "$(INTDIR)\DUMMY4.OBJ"
	-@erase "$(INTDIR)\DUMPOUT.OBJ"
	-@erase "$(INTDIR)\enmcprop.obj"
	-@erase "$(INTDIR)\enumprop.obj"
	-@erase "$(INTDIR)\EXTREG.OBJ"
	-@erase "$(INTDIR)\HDRENTRX.OBJ"
	-@erase "$(INTDIR)\HELPTEXT.OBJ"
	-@erase "$(INTDIR)\IENUMONR.OBJ"
	-@erase "$(INTDIR)\IENUMSTR.OBJ"
	-@erase "$(INTDIR)\IXtAtr42.pch"
	-@erase "$(INTDIR)\NUMEDITX.OBJ"
	-@erase "$(INTDIR)\OBJCONTX.OBJ"
	-@erase "$(INTDIR)\objpropf.obj"
	-@erase "$(INTDIR)\REGISTRY.OBJ"
	-@erase "$(INTDIR)\STRUTIL.OBJ"
	-@erase "$(INTDIR)\VALIDADD.OBJ"
	-@erase "$(INTDIR)\XtencAtl.obj"
	-@erase "$(INTDIR)\XTENSNP.OBJ"
	-@erase "$(INTDIR)\xtsnatl.obj"
	-@erase "$(INTDIR)\XtsnImpAtl.obj"
	-@erase "$(INTDIR)\xtsnprop.obj"
	-@erase "$(OUTDIR)\ixtAtr42.lib"
	-@erase "..\..\lib32\ixtAtr42.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /WX /GX /O2 /Ob2 /D "NDEBUG" /D "STRICT" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "DLL" /D "__XTENSNDLL__" /D "__CV__" /D "WIN32" /D "_WINDOWS" /D "__ATL_USED__" /D "__ATL_11_USED__" /Yu"xtensnp.hxx" /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MD /W3 /WX /GX /O2 /Ob2 /D "NDEBUG" /D "__ATL_11_USED__" /D "__ATL_XTENSION_BASE__" /D "STRICT" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "DLL" /D "__XTENSNDLL__" /D "__CV__" /D "WIN32" /D "_WINDOWS" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /Fp"Atl42/Release/IXtAtr42.pch" /Yu"xtensnp.hxx" /c
CPP_PROJ=/nologo /MD /W3 /WX /GX /O2 /Ob2 /D "NDEBUG" /D "__ATL_11_USED__" /D\
 "__ATL_XTENSION_BASE__" /D "STRICT" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D\
 "DLL" /D "__XTENSNDLL__" /D "__CV__" /D "WIN32" /D "_WINDOWS" /D "__ATL_USED__"\
 /D "OS_NO_STREAM_SUPPORT" /Fp"$(INTDIR)/IXtAtr42.pch" /Yu"xtensnp.hxx"\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Atl42/Release/
CPP_SBRS=.\.
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/IXTNSN42.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"Obj42/Release\ixtnsr42.lib"
# ADD LIB32 /nologo /out:"Atl42/Release\ixtAtr42.lib"
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/ixtAtr42.lib" 
LIB32_OBJS= \
	"$(INTDIR)\Ctfxmfc.obj" \
	"$(INTDIR)\DBLNUMED.OBJ" \
	"$(INTDIR)\dllbindx.obj" \
	"$(INTDIR)\dummy1.obj" \
	"$(INTDIR)\dummy2.obj" \
	"$(INTDIR)\dummy3.obj" \
	"$(INTDIR)\DUMMY4.OBJ" \
	"$(INTDIR)\DUMPOUT.OBJ" \
	"$(INTDIR)\enmcprop.obj" \
	"$(INTDIR)\enumprop.obj" \
	"$(INTDIR)\EXTREG.OBJ" \
	"$(INTDIR)\HDRENTRX.OBJ" \
	"$(INTDIR)\HELPTEXT.OBJ" \
	"$(INTDIR)\IENUMONR.OBJ" \
	"$(INTDIR)\IENUMSTR.OBJ" \
	"$(INTDIR)\NUMEDITX.OBJ" \
	"$(INTDIR)\OBJCONTX.OBJ" \
	"$(INTDIR)\objpropf.obj" \
	"$(INTDIR)\REGISTRY.OBJ" \
	"$(INTDIR)\STRUTIL.OBJ" \
	"$(INTDIR)\VALIDADD.OBJ" \
	"$(INTDIR)\XtencAtl.obj" \
	"$(INTDIR)\XTENSNP.OBJ" \
	"$(INTDIR)\xtsnatl.obj" \
	"$(INTDIR)\XtsnImpAtl.obj" \
	"$(INTDIR)\xtsnprop.obj"

"$(OUTDIR)\ixtAtr42.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

# Begin Custom Build - Copying created library ...
OutDir=.\Atl42/Release
TargetPath=.\Atl42\Release\ixtAtr42.lib
TargetName=ixtAtr42
InputPath=.\Atl42\Release\ixtAtr42.lib
SOURCE=$(InputPath)

"\triasdev.mvc\lib32\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   copy "$(TargetPath)" \triasdev.mvc\lib32
   if exist "$(OutDir)\$(TargetName).pdb" copy "$(OutDir)\$(TargetName).pdb"\
                                                      \triasdev.mvc\lib32

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

# Name "ixtnsn32 - Win32 Release"
# Name "ixtnsn32 - Win32 Debug"
# Name "ixtnsn32 - Win32 Release New"
# Name "ixtnsn32 - Win32 Debug New"
# Name "ixtnsn32 - Win32 Debug ATL Base"
# Name "ixtnsn32 - Win32 Release ATL Base"

!IF  "$(CFG)" == "ixtnsn32 - Win32 Release"

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug"

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release New"

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug New"

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug ATL Base"

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release ATL Base"

!ENDIF 

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
	

!IF  "$(CFG)" == "ixtnsn32 - Win32 Release"

# ADD CPP /Yc"xtensnp.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O2 /Ob2 /D "NDEBUG" /D "STRICT" /D "__XT" /D\
 "__DEXPROCS" /D "MSWIND" /D "DLL" /D "__XTENSNDLL__" /D "__CV__" /D "WIN32" /D\
 "_WINDOWS" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D "__ATL_11_USED__"\
 /Fp"$(INTDIR)/IXTNSN42.pch" /Yc"xtensnp.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\XTENSNP.OBJ" : $(SOURCE) $(DEP_CPP_XTENS) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\IXTNSN42.pch" : $(SOURCE) $(DEP_CPP_XTENS) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug"

# ADD CPP /MD /Yc"xtensnp.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "STRICT" /D\
 "__XT" /D "__DEXPROCS" /D "MSWIND" /D "DLL" /D "__XTENSNDLL__" /D "__CV__" /D\
 "WIN32" /D "_WINDOWS" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D\
 "__ATL_11_USED__" /FR"$(INTDIR)/" /Fp"$(INTDIR)/ixtnsn32.pch" /Yc"xtensnp.hxx"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/ixtnsd40.pdb" /c $(SOURCE) \
	

"$(INTDIR)\XTENSNP.OBJ" : $(SOURCE) $(DEP_CPP_XTENS) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\XTENSNP.SBR" : $(SOURCE) $(DEP_CPP_XTENS) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\ixtnsn32.pch" : $(SOURCE) $(DEP_CPP_XTENS) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release New"

# ADD BASE CPP /Yc"xtensnp.hxx"
# ADD CPP /Yc"xtensnp.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O2 /Ob2 /D "NDEBUG" /D "__ATL_11_USED__" /D\
 "STRICT" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "DLL" /D "__XTENSNDLL__" /D\
 "__CV__" /D "WIN32" /D "_WINDOWS" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT"\
 /Fp"$(INTDIR)/IXTNSN42.pch" /Yc"xtensnp.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\XTENSNP.OBJ" : $(SOURCE) $(DEP_CPP_XTENS) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\IXTNSN42.pch" : $(SOURCE) $(DEP_CPP_XTENS) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug New"

# ADD BASE CPP /MD /Yc"xtensnp.hxx"
# ADD CPP /MD /Yc"xtensnp.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D\
 "__ATL_11_USED__" /D "STRICT" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "DLL" /D\
 "__XTENSNDLL__" /D "__CV__" /D "WIN32" /D "_WINDOWS" /D "__ATL_USED__" /D\
 "OS_NO_STREAM_SUPPORT" /FR"Obj42/Debug/" /Fp"Obj42/Debug/ixtnsn32.pch"\
 /Yc"xtensnp.hxx" /Fo"Obj42/Debug/" /Fd"Obj42/Debug/ixtnsd42.pdb" /c $(SOURCE) \
	

".\Obj42\Debug\XTENSNP.OBJ" : $(SOURCE) $(DEP_CPP_XTENS) "$(INTDIR)"
   $(BuildCmds)

".\Obj42\Debug\XTENSNP.SBR" : $(SOURCE) $(DEP_CPP_XTENS) "$(INTDIR)"
   $(BuildCmds)

".\Obj42\Debug\ixtnsn32.pch" : $(SOURCE) $(DEP_CPP_XTENS) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug ATL Base"

# ADD BASE CPP /MD /Yc"xtensnp.hxx"
# ADD CPP /MD /Yc"xtensnp.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D\
 "__ATL_11_USED__" /D "__ATL_XTENSION_BASE__" /D "STRICT" /D "__XT" /D\
 "__DEXPROCS" /D "MSWIND" /D "DLL" /D "__XTENSNDLL__" /D "__CV__" /D "WIN32" /D\
 "_WINDOWS" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/IxtAtd42.pch" /Yc"xtensnp.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/IxtAtd42.pdb" /c $(SOURCE) \
	

"$(INTDIR)\XTENSNP.OBJ" : $(SOURCE) $(DEP_CPP_XTENS) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\XTENSNP.SBR" : $(SOURCE) $(DEP_CPP_XTENS) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\IxtAtd42.pch" : $(SOURCE) $(DEP_CPP_XTENS) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release ATL Base"

# ADD BASE CPP /Yc"xtensnp.hxx"
# ADD CPP /Yc"xtensnp.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O2 /Ob2 /D "NDEBUG" /D "__ATL_11_USED__" /D\
 "__ATL_XTENSION_BASE__" /D "STRICT" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D\
 "DLL" /D "__XTENSNDLL__" /D "__CV__" /D "WIN32" /D "_WINDOWS" /D "__ATL_USED__"\
 /D "OS_NO_STREAM_SUPPORT" /Fp"$(INTDIR)/IXtAtr42.pch" /Yc"xtensnp.hxx"\
 /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\XTENSNP.OBJ" : $(SOURCE) $(DEP_CPP_XTENS) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\IXtAtr42.pch" : $(SOURCE) $(DEP_CPP_XTENS) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
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
	

!IF  "$(CFG)" == "ixtnsn32 - Win32 Release"


"$(INTDIR)\IMPXTCF.OBJ" : $(SOURCE) $(DEP_CPP_IMPXT) "$(INTDIR)"\
 "$(INTDIR)\IXTNSN42.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /Ob2 /D "NDEBUG" /D "STRICT" /D "__XT" /D\
 "__DEXPROCS" /D "MSWIND" /D "DLL" /D "__XTENSNDLL__" /D "__CV__" /D "WIN32" /D\
 "_WINDOWS" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D "__ATL_11_USED__"\
 /Fp"$(INTDIR)/IXTNSN42.pch" /Yu"xtensnp.hxx" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug"


BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "STRICT" /D\
 "__XT" /D "__DEXPROCS" /D "MSWIND" /D "DLL" /D "__XTENSNDLL__" /D "__CV__" /D\
 "WIN32" /D "_WINDOWS" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D\
 "__ATL_11_USED__" /FR"$(INTDIR)/" /Fp"$(INTDIR)/ixtnsn32.pch" /Yu"xtensnp.hxx"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/ixtnsd40.pdb" /c $(SOURCE) \
	

"$(INTDIR)\IMPXTCF.OBJ" : $(SOURCE) $(DEP_CPP_IMPXT) "$(INTDIR)"\
 "$(INTDIR)\ixtnsn32.pch"
   $(BuildCmds)

"$(INTDIR)\IMPXTCF.SBR" : $(SOURCE) $(DEP_CPP_IMPXT) "$(INTDIR)"\
 "$(INTDIR)\ixtnsn32.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release New"


"$(INTDIR)\IMPXTCF.OBJ" : $(SOURCE) $(DEP_CPP_IMPXT) "$(INTDIR)"\
 "$(INTDIR)\IXTNSN42.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /Ob2 /D "NDEBUG" /D "__ATL_11_USED__" /D\
 "STRICT" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "DLL" /D "__XTENSNDLL__" /D\
 "__CV__" /D "WIN32" /D "_WINDOWS" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT"\
 /Fp"$(INTDIR)/IXTNSN42.pch" /Yu"xtensnp.hxx" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug New"


BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D\
 "__ATL_11_USED__" /D "STRICT" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "DLL" /D\
 "__XTENSNDLL__" /D "__CV__" /D "WIN32" /D "_WINDOWS" /D "__ATL_USED__" /D\
 "OS_NO_STREAM_SUPPORT" /FR"Obj42/Debug/" /Fp"Obj42/Debug/ixtnsn32.pch"\
 /Yu"xtensnp.hxx" /Fo"Obj42/Debug/" /Fd"Obj42/Debug/ixtnsd42.pdb" /c $(SOURCE) \
	

".\Obj42\Debug\IMPXTCF.OBJ" : $(SOURCE) $(DEP_CPP_IMPXT) "$(INTDIR)"\
 ".\Obj42\Debug\ixtnsn32.pch"
   $(BuildCmds)

".\Obj42\Debug\IMPXTCF.SBR" : $(SOURCE) $(DEP_CPP_IMPXT) "$(INTDIR)"\
 ".\Obj42\Debug\ixtnsn32.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug ATL Base"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release ATL Base"

# PROP Exclude_From_Build 1

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
	

!IF  "$(CFG)" == "ixtnsn32 - Win32 Release"


"$(INTDIR)\Xtencunk.obj" : $(SOURCE) $(DEP_CPP_XTENC) "$(INTDIR)"\
 "$(INTDIR)\IXTNSN42.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /Ob2 /D "NDEBUG" /D "STRICT" /D "__XT" /D\
 "__DEXPROCS" /D "MSWIND" /D "DLL" /D "__XTENSNDLL__" /D "__CV__" /D "WIN32" /D\
 "_WINDOWS" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D "__ATL_11_USED__"\
 /Fp"$(INTDIR)/IXTNSN42.pch" /Yu"xtensnp.hxx" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug"


BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "STRICT" /D\
 "__XT" /D "__DEXPROCS" /D "MSWIND" /D "DLL" /D "__XTENSNDLL__" /D "__CV__" /D\
 "WIN32" /D "_WINDOWS" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D\
 "__ATL_11_USED__" /FR"$(INTDIR)/" /Fp"$(INTDIR)/ixtnsn32.pch" /Yu"xtensnp.hxx"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/ixtnsd40.pdb" /c $(SOURCE) \
	

"$(INTDIR)\Xtencunk.obj" : $(SOURCE) $(DEP_CPP_XTENC) "$(INTDIR)"\
 "$(INTDIR)\ixtnsn32.pch"
   $(BuildCmds)

"$(INTDIR)\Xtencunk.sbr" : $(SOURCE) $(DEP_CPP_XTENC) "$(INTDIR)"\
 "$(INTDIR)\ixtnsn32.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release New"


"$(INTDIR)\Xtencunk.obj" : $(SOURCE) $(DEP_CPP_XTENC) "$(INTDIR)"\
 "$(INTDIR)\IXTNSN42.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /Ob2 /D "NDEBUG" /D "__ATL_11_USED__" /D\
 "STRICT" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "DLL" /D "__XTENSNDLL__" /D\
 "__CV__" /D "WIN32" /D "_WINDOWS" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT"\
 /Fp"$(INTDIR)/IXTNSN42.pch" /Yu"xtensnp.hxx" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug New"


BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D\
 "__ATL_11_USED__" /D "STRICT" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "DLL" /D\
 "__XTENSNDLL__" /D "__CV__" /D "WIN32" /D "_WINDOWS" /D "__ATL_USED__" /D\
 "OS_NO_STREAM_SUPPORT" /FR"Obj42/Debug/" /Fp"Obj42/Debug/ixtnsn32.pch"\
 /Yu"xtensnp.hxx" /Fo"Obj42/Debug/" /Fd"Obj42/Debug/ixtnsd42.pdb" /c $(SOURCE) \
	

".\Obj42\Debug\Xtencunk.obj" : $(SOURCE) $(DEP_CPP_XTENC) "$(INTDIR)"\
 ".\Obj42\Debug\ixtnsn32.pch"
   $(BuildCmds)

".\Obj42\Debug\Xtencunk.sbr" : $(SOURCE) $(DEP_CPP_XTENC) "$(INTDIR)"\
 ".\Obj42\Debug\ixtnsn32.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug ATL Base"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release ATL Base"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dummy2.cxx
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
	

!IF  "$(CFG)" == "ixtnsn32 - Win32 Release"


"$(INTDIR)\dummy2.obj" : $(SOURCE) $(DEP_CPP_DUMMY) "$(INTDIR)"\
 "$(INTDIR)\IXTNSN42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug"


"$(INTDIR)\dummy2.obj" : $(SOURCE) $(DEP_CPP_DUMMY) "$(INTDIR)"\
 "$(INTDIR)\ixtnsn32.pch"

"$(INTDIR)\dummy2.sbr" : $(SOURCE) $(DEP_CPP_DUMMY) "$(INTDIR)"\
 "$(INTDIR)\ixtnsn32.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release New"


"$(INTDIR)\dummy2.obj" : $(SOURCE) $(DEP_CPP_DUMMY) "$(INTDIR)"\
 "$(INTDIR)\IXTNSN42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug New"


".\Obj42\Debug\dummy2.obj" : $(SOURCE) $(DEP_CPP_DUMMY) "$(INTDIR)"\
 ".\Obj42\Debug\ixtnsn32.pch"

".\Obj42\Debug\dummy2.sbr" : $(SOURCE) $(DEP_CPP_DUMMY) "$(INTDIR)"\
 ".\Obj42\Debug\ixtnsn32.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug ATL Base"


"$(INTDIR)\dummy2.obj" : $(SOURCE) $(DEP_CPP_DUMMY) "$(INTDIR)"\
 "$(INTDIR)\IxtAtd42.pch"

"$(INTDIR)\dummy2.sbr" : $(SOURCE) $(DEP_CPP_DUMMY) "$(INTDIR)"\
 "$(INTDIR)\IxtAtd42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release ATL Base"


"$(INTDIR)\dummy2.obj" : $(SOURCE) $(DEP_CPP_DUMMY) "$(INTDIR)"\
 "$(INTDIR)\IXtAtr42.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dummy1.cxx
DEP_CPP_DUMMY1=\
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
	

!IF  "$(CFG)" == "ixtnsn32 - Win32 Release"


"$(INTDIR)\dummy1.obj" : $(SOURCE) $(DEP_CPP_DUMMY1) "$(INTDIR)"\
 "$(INTDIR)\IXTNSN42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug"


"$(INTDIR)\dummy1.obj" : $(SOURCE) $(DEP_CPP_DUMMY1) "$(INTDIR)"\
 "$(INTDIR)\ixtnsn32.pch"

"$(INTDIR)\dummy1.sbr" : $(SOURCE) $(DEP_CPP_DUMMY1) "$(INTDIR)"\
 "$(INTDIR)\ixtnsn32.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release New"


"$(INTDIR)\dummy1.obj" : $(SOURCE) $(DEP_CPP_DUMMY1) "$(INTDIR)"\
 "$(INTDIR)\IXTNSN42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug New"


".\Obj42\Debug\dummy1.obj" : $(SOURCE) $(DEP_CPP_DUMMY1) "$(INTDIR)"\
 ".\Obj42\Debug\ixtnsn32.pch"

".\Obj42\Debug\dummy1.sbr" : $(SOURCE) $(DEP_CPP_DUMMY1) "$(INTDIR)"\
 ".\Obj42\Debug\ixtnsn32.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug ATL Base"


"$(INTDIR)\dummy1.obj" : $(SOURCE) $(DEP_CPP_DUMMY1) "$(INTDIR)"\
 "$(INTDIR)\IxtAtd42.pch"

"$(INTDIR)\dummy1.sbr" : $(SOURCE) $(DEP_CPP_DUMMY1) "$(INTDIR)"\
 "$(INTDIR)\IxtAtd42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release ATL Base"


"$(INTDIR)\dummy1.obj" : $(SOURCE) $(DEP_CPP_DUMMY1) "$(INTDIR)"\
 "$(INTDIR)\IXtAtr42.pch"


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
	

!IF  "$(CFG)" == "ixtnsn32 - Win32 Release"


"$(INTDIR)\dummy3.obj" : $(SOURCE) $(DEP_CPP_DUMMY3) "$(INTDIR)"\
 "$(INTDIR)\IXTNSN42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug"


"$(INTDIR)\dummy3.obj" : $(SOURCE) $(DEP_CPP_DUMMY3) "$(INTDIR)"\
 "$(INTDIR)\ixtnsn32.pch"

"$(INTDIR)\dummy3.sbr" : $(SOURCE) $(DEP_CPP_DUMMY3) "$(INTDIR)"\
 "$(INTDIR)\ixtnsn32.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release New"


"$(INTDIR)\dummy3.obj" : $(SOURCE) $(DEP_CPP_DUMMY3) "$(INTDIR)"\
 "$(INTDIR)\IXTNSN42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug New"


".\Obj42\Debug\dummy3.obj" : $(SOURCE) $(DEP_CPP_DUMMY3) "$(INTDIR)"\
 ".\Obj42\Debug\ixtnsn32.pch"

".\Obj42\Debug\dummy3.sbr" : $(SOURCE) $(DEP_CPP_DUMMY3) "$(INTDIR)"\
 ".\Obj42\Debug\ixtnsn32.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug ATL Base"


"$(INTDIR)\dummy3.obj" : $(SOURCE) $(DEP_CPP_DUMMY3) "$(INTDIR)"\
 "$(INTDIR)\IxtAtd42.pch"

"$(INTDIR)\dummy3.sbr" : $(SOURCE) $(DEP_CPP_DUMMY3) "$(INTDIR)"\
 "$(INTDIR)\IxtAtd42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release ATL Base"


"$(INTDIR)\dummy3.obj" : $(SOURCE) $(DEP_CPP_DUMMY3) "$(INTDIR)"\
 "$(INTDIR)\IXtAtr42.pch"


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
	

!IF  "$(CFG)" == "ixtnsn32 - Win32 Release"


"$(INTDIR)\DUMMY4.OBJ" : $(SOURCE) $(DEP_CPP_DUMMY4) "$(INTDIR)"\
 "$(INTDIR)\IXTNSN42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug"


"$(INTDIR)\DUMMY4.OBJ" : $(SOURCE) $(DEP_CPP_DUMMY4) "$(INTDIR)"\
 "$(INTDIR)\ixtnsn32.pch"

"$(INTDIR)\DUMMY4.SBR" : $(SOURCE) $(DEP_CPP_DUMMY4) "$(INTDIR)"\
 "$(INTDIR)\ixtnsn32.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release New"


"$(INTDIR)\DUMMY4.OBJ" : $(SOURCE) $(DEP_CPP_DUMMY4) "$(INTDIR)"\
 "$(INTDIR)\IXTNSN42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug New"


".\Obj42\Debug\DUMMY4.OBJ" : $(SOURCE) $(DEP_CPP_DUMMY4) "$(INTDIR)"\
 ".\Obj42\Debug\ixtnsn32.pch"

".\Obj42\Debug\DUMMY4.SBR" : $(SOURCE) $(DEP_CPP_DUMMY4) "$(INTDIR)"\
 ".\Obj42\Debug\ixtnsn32.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug ATL Base"


"$(INTDIR)\DUMMY4.OBJ" : $(SOURCE) $(DEP_CPP_DUMMY4) "$(INTDIR)"\
 "$(INTDIR)\IxtAtd42.pch"

"$(INTDIR)\DUMMY4.SBR" : $(SOURCE) $(DEP_CPP_DUMMY4) "$(INTDIR)"\
 "$(INTDIR)\IxtAtd42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release ATL Base"


"$(INTDIR)\DUMMY4.OBJ" : $(SOURCE) $(DEP_CPP_DUMMY4) "$(INTDIR)"\
 "$(INTDIR)\IXtAtr42.pch"


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
	

!IF  "$(CFG)" == "ixtnsn32 - Win32 Release"


"$(INTDIR)\cimpxtsn.obj" : $(SOURCE) $(DEP_CPP_CIMPX) "$(INTDIR)"\
 "$(INTDIR)\IXTNSN42.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /Ob2 /D "NDEBUG" /D "STRICT" /D "__XT" /D\
 "__DEXPROCS" /D "MSWIND" /D "DLL" /D "__XTENSNDLL__" /D "__CV__" /D "WIN32" /D\
 "_WINDOWS" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D "__ATL_11_USED__"\
 /Fp"$(INTDIR)/IXTNSN42.pch" /Yu"xtensnp.hxx" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug"


BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "STRICT" /D\
 "__XT" /D "__DEXPROCS" /D "MSWIND" /D "DLL" /D "__XTENSNDLL__" /D "__CV__" /D\
 "WIN32" /D "_WINDOWS" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D\
 "__ATL_11_USED__" /FR"$(INTDIR)/" /Fp"$(INTDIR)/ixtnsn32.pch" /Yu"xtensnp.hxx"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/ixtnsd40.pdb" /c $(SOURCE) \
	

"$(INTDIR)\cimpxtsn.obj" : $(SOURCE) $(DEP_CPP_CIMPX) "$(INTDIR)"\
 "$(INTDIR)\ixtnsn32.pch"
   $(BuildCmds)

"$(INTDIR)\cimpxtsn.sbr" : $(SOURCE) $(DEP_CPP_CIMPX) "$(INTDIR)"\
 "$(INTDIR)\ixtnsn32.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release New"


"$(INTDIR)\cimpxtsn.obj" : $(SOURCE) $(DEP_CPP_CIMPX) "$(INTDIR)"\
 "$(INTDIR)\IXTNSN42.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /Ob2 /D "NDEBUG" /D "__ATL_11_USED__" /D\
 "STRICT" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "DLL" /D "__XTENSNDLL__" /D\
 "__CV__" /D "WIN32" /D "_WINDOWS" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT"\
 /Fp"$(INTDIR)/IXTNSN42.pch" /Yu"xtensnp.hxx" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug New"


BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D\
 "__ATL_11_USED__" /D "STRICT" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "DLL" /D\
 "__XTENSNDLL__" /D "__CV__" /D "WIN32" /D "_WINDOWS" /D "__ATL_USED__" /D\
 "OS_NO_STREAM_SUPPORT" /FR"Obj42/Debug/" /Fp"Obj42/Debug/ixtnsn32.pch"\
 /Yu"xtensnp.hxx" /Fo"Obj42/Debug/" /Fd"Obj42/Debug/ixtnsd42.pdb" /c $(SOURCE) \
	

".\Obj42\Debug\cimpxtsn.obj" : $(SOURCE) $(DEP_CPP_CIMPX) "$(INTDIR)"\
 ".\Obj42\Debug\ixtnsn32.pch"
   $(BuildCmds)

".\Obj42\Debug\cimpxtsn.sbr" : $(SOURCE) $(DEP_CPP_CIMPX) "$(INTDIR)"\
 ".\Obj42\Debug\ixtnsn32.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug ATL Base"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release ATL Base"

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
	

!IF  "$(CFG)" == "ixtnsn32 - Win32 Release"


"$(INTDIR)\enmcprop.obj" : $(SOURCE) $(DEP_CPP_ENMCP) "$(INTDIR)"\
 "$(INTDIR)\IXTNSN42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug"


"$(INTDIR)\enmcprop.obj" : $(SOURCE) $(DEP_CPP_ENMCP) "$(INTDIR)"\
 "$(INTDIR)\ixtnsn32.pch"

"$(INTDIR)\enmcprop.sbr" : $(SOURCE) $(DEP_CPP_ENMCP) "$(INTDIR)"\
 "$(INTDIR)\ixtnsn32.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release New"


"$(INTDIR)\enmcprop.obj" : $(SOURCE) $(DEP_CPP_ENMCP) "$(INTDIR)"\
 "$(INTDIR)\IXTNSN42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug New"


".\Obj42\Debug\enmcprop.obj" : $(SOURCE) $(DEP_CPP_ENMCP) "$(INTDIR)"\
 ".\Obj42\Debug\ixtnsn32.pch"

".\Obj42\Debug\enmcprop.sbr" : $(SOURCE) $(DEP_CPP_ENMCP) "$(INTDIR)"\
 ".\Obj42\Debug\ixtnsn32.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug ATL Base"


"$(INTDIR)\enmcprop.obj" : $(SOURCE) $(DEP_CPP_ENMCP) "$(INTDIR)"\
 "$(INTDIR)\IxtAtd42.pch"

"$(INTDIR)\enmcprop.sbr" : $(SOURCE) $(DEP_CPP_ENMCP) "$(INTDIR)"\
 "$(INTDIR)\IxtAtd42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release ATL Base"


"$(INTDIR)\enmcprop.obj" : $(SOURCE) $(DEP_CPP_ENMCP) "$(INTDIR)"\
 "$(INTDIR)\IXtAtr42.pch"


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
	

!IF  "$(CFG)" == "ixtnsn32 - Win32 Release"


"$(INTDIR)\enumprop.obj" : $(SOURCE) $(DEP_CPP_ENUMP) "$(INTDIR)"\
 "$(INTDIR)\IXTNSN42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug"


"$(INTDIR)\enumprop.obj" : $(SOURCE) $(DEP_CPP_ENUMP) "$(INTDIR)"\
 "$(INTDIR)\ixtnsn32.pch"

"$(INTDIR)\enumprop.sbr" : $(SOURCE) $(DEP_CPP_ENUMP) "$(INTDIR)"\
 "$(INTDIR)\ixtnsn32.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release New"


"$(INTDIR)\enumprop.obj" : $(SOURCE) $(DEP_CPP_ENUMP) "$(INTDIR)"\
 "$(INTDIR)\IXTNSN42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug New"


".\Obj42\Debug\enumprop.obj" : $(SOURCE) $(DEP_CPP_ENUMP) "$(INTDIR)"\
 ".\Obj42\Debug\ixtnsn32.pch"

".\Obj42\Debug\enumprop.sbr" : $(SOURCE) $(DEP_CPP_ENUMP) "$(INTDIR)"\
 ".\Obj42\Debug\ixtnsn32.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug ATL Base"


"$(INTDIR)\enumprop.obj" : $(SOURCE) $(DEP_CPP_ENUMP) "$(INTDIR)"\
 "$(INTDIR)\IxtAtd42.pch"

"$(INTDIR)\enumprop.sbr" : $(SOURCE) $(DEP_CPP_ENUMP) "$(INTDIR)"\
 "$(INTDIR)\IxtAtd42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release ATL Base"


"$(INTDIR)\enumprop.obj" : $(SOURCE) $(DEP_CPP_ENUMP) "$(INTDIR)"\
 "$(INTDIR)\IXtAtr42.pch"


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
	

!IF  "$(CFG)" == "ixtnsn32 - Win32 Release"


"$(INTDIR)\objpropf.obj" : $(SOURCE) $(DEP_CPP_OBJPR) "$(INTDIR)"\
 "$(INTDIR)\IXTNSN42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug"


"$(INTDIR)\objpropf.obj" : $(SOURCE) $(DEP_CPP_OBJPR) "$(INTDIR)"\
 "$(INTDIR)\ixtnsn32.pch"

"$(INTDIR)\objpropf.sbr" : $(SOURCE) $(DEP_CPP_OBJPR) "$(INTDIR)"\
 "$(INTDIR)\ixtnsn32.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release New"


"$(INTDIR)\objpropf.obj" : $(SOURCE) $(DEP_CPP_OBJPR) "$(INTDIR)"\
 "$(INTDIR)\IXTNSN42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug New"


".\Obj42\Debug\objpropf.obj" : $(SOURCE) $(DEP_CPP_OBJPR) "$(INTDIR)"\
 ".\Obj42\Debug\ixtnsn32.pch"

".\Obj42\Debug\objpropf.sbr" : $(SOURCE) $(DEP_CPP_OBJPR) "$(INTDIR)"\
 ".\Obj42\Debug\ixtnsn32.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug ATL Base"


"$(INTDIR)\objpropf.obj" : $(SOURCE) $(DEP_CPP_OBJPR) "$(INTDIR)"\
 "$(INTDIR)\IxtAtd42.pch"

"$(INTDIR)\objpropf.sbr" : $(SOURCE) $(DEP_CPP_OBJPR) "$(INTDIR)"\
 "$(INTDIR)\IxtAtd42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release ATL Base"


"$(INTDIR)\objpropf.obj" : $(SOURCE) $(DEP_CPP_OBJPR) "$(INTDIR)"\
 "$(INTDIR)\IXtAtr42.pch"


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
	

!IF  "$(CFG)" == "ixtnsn32 - Win32 Release"


"$(INTDIR)\xtsnprop.obj" : $(SOURCE) $(DEP_CPP_XTSNP) "$(INTDIR)"\
 "$(INTDIR)\IXTNSN42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug"


"$(INTDIR)\xtsnprop.obj" : $(SOURCE) $(DEP_CPP_XTSNP) "$(INTDIR)"\
 "$(INTDIR)\ixtnsn32.pch"

"$(INTDIR)\xtsnprop.sbr" : $(SOURCE) $(DEP_CPP_XTSNP) "$(INTDIR)"\
 "$(INTDIR)\ixtnsn32.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release New"


"$(INTDIR)\xtsnprop.obj" : $(SOURCE) $(DEP_CPP_XTSNP) "$(INTDIR)"\
 "$(INTDIR)\IXTNSN42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug New"


".\Obj42\Debug\xtsnprop.obj" : $(SOURCE) $(DEP_CPP_XTSNP) "$(INTDIR)"\
 ".\Obj42\Debug\ixtnsn32.pch"

".\Obj42\Debug\xtsnprop.sbr" : $(SOURCE) $(DEP_CPP_XTSNP) "$(INTDIR)"\
 ".\Obj42\Debug\ixtnsn32.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug ATL Base"


"$(INTDIR)\xtsnprop.obj" : $(SOURCE) $(DEP_CPP_XTSNP) "$(INTDIR)"\
 "$(INTDIR)\IxtAtd42.pch"

"$(INTDIR)\xtsnprop.sbr" : $(SOURCE) $(DEP_CPP_XTSNP) "$(INTDIR)"\
 "$(INTDIR)\IxtAtd42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release ATL Base"


"$(INTDIR)\xtsnprop.obj" : $(SOURCE) $(DEP_CPP_XTSNP) "$(INTDIR)"\
 "$(INTDIR)\IXtAtr42.pch"


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
	

!IF  "$(CFG)" == "ixtnsn32 - Win32 Release"


"$(INTDIR)\IENUMONR.OBJ" : $(SOURCE) $(DEP_CPP_IENUM) "$(INTDIR)"\
 "$(INTDIR)\IXTNSN42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug"


"$(INTDIR)\IENUMONR.OBJ" : $(SOURCE) $(DEP_CPP_IENUM) "$(INTDIR)"\
 "$(INTDIR)\ixtnsn32.pch"

"$(INTDIR)\IENUMONR.SBR" : $(SOURCE) $(DEP_CPP_IENUM) "$(INTDIR)"\
 "$(INTDIR)\ixtnsn32.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release New"


"$(INTDIR)\IENUMONR.OBJ" : $(SOURCE) $(DEP_CPP_IENUM) "$(INTDIR)"\
 "$(INTDIR)\IXTNSN42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug New"


".\Obj42\Debug\IENUMONR.OBJ" : $(SOURCE) $(DEP_CPP_IENUM) "$(INTDIR)"\
 ".\Obj42\Debug\ixtnsn32.pch"

".\Obj42\Debug\IENUMONR.SBR" : $(SOURCE) $(DEP_CPP_IENUM) "$(INTDIR)"\
 ".\Obj42\Debug\ixtnsn32.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug ATL Base"


"$(INTDIR)\IENUMONR.OBJ" : $(SOURCE) $(DEP_CPP_IENUM) "$(INTDIR)"\
 "$(INTDIR)\IxtAtd42.pch"

"$(INTDIR)\IENUMONR.SBR" : $(SOURCE) $(DEP_CPP_IENUM) "$(INTDIR)"\
 "$(INTDIR)\IxtAtd42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release ATL Base"


"$(INTDIR)\IENUMONR.OBJ" : $(SOURCE) $(DEP_CPP_IENUM) "$(INTDIR)"\
 "$(INTDIR)\IXtAtr42.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\EXTREG.CXX

!IF  "$(CFG)" == "ixtnsn32 - Win32 Release"

DEP_CPP_EXTRE=\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"\COMCAT.H"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\TrCatIDs.h"\
	{$(INCLUDE)}"\WrongTrCatIDs.h"\
	

"$(INTDIR)\EXTREG.OBJ" : $(SOURCE) $(DEP_CPP_EXTRE) "$(INTDIR)"\
 "$(INTDIR)\IXTNSN42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug"

DEP_CPP_EXTRE=\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"\COMCAT.H"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\TrCatIDs.h"\
	{$(INCLUDE)}"\WrongTrCatIDs.h"\
	

"$(INTDIR)\EXTREG.OBJ" : $(SOURCE) $(DEP_CPP_EXTRE) "$(INTDIR)"\
 "$(INTDIR)\ixtnsn32.pch"

"$(INTDIR)\EXTREG.SBR" : $(SOURCE) $(DEP_CPP_EXTRE) "$(INTDIR)"\
 "$(INTDIR)\ixtnsn32.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release New"

DEP_CPP_EXTRE=\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"\COMCAT.H"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\TrCatIDs.h"\
	{$(INCLUDE)}"\WrongTrCatIDs.h"\
	

"$(INTDIR)\EXTREG.OBJ" : $(SOURCE) $(DEP_CPP_EXTRE) "$(INTDIR)"\
 "$(INTDIR)\IXTNSN42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug New"

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
	

".\Obj42\Debug\EXTREG.OBJ" : $(SOURCE) $(DEP_CPP_EXTRE) "$(INTDIR)"\
 ".\Obj42\Debug\ixtnsn32.pch"

".\Obj42\Debug\EXTREG.SBR" : $(SOURCE) $(DEP_CPP_EXTRE) "$(INTDIR)"\
 ".\Obj42\Debug\ixtnsn32.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug ATL Base"

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
 "$(INTDIR)\IxtAtd42.pch"

"$(INTDIR)\EXTREG.SBR" : $(SOURCE) $(DEP_CPP_EXTRE) "$(INTDIR)"\
 "$(INTDIR)\IxtAtd42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release ATL Base"

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
 "$(INTDIR)\IXtAtr42.pch"


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
	

!IF  "$(CFG)" == "ixtnsn32 - Win32 Release"


"$(INTDIR)\REGISTRY.OBJ" : $(SOURCE) $(DEP_CPP_REGIS) "$(INTDIR)"\
 "$(INTDIR)\IXTNSN42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug"


"$(INTDIR)\REGISTRY.OBJ" : $(SOURCE) $(DEP_CPP_REGIS) "$(INTDIR)"\
 "$(INTDIR)\ixtnsn32.pch"

"$(INTDIR)\REGISTRY.SBR" : $(SOURCE) $(DEP_CPP_REGIS) "$(INTDIR)"\
 "$(INTDIR)\ixtnsn32.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release New"


"$(INTDIR)\REGISTRY.OBJ" : $(SOURCE) $(DEP_CPP_REGIS) "$(INTDIR)"\
 "$(INTDIR)\IXTNSN42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug New"


".\Obj42\Debug\REGISTRY.OBJ" : $(SOURCE) $(DEP_CPP_REGIS) "$(INTDIR)"\
 ".\Obj42\Debug\ixtnsn32.pch"

".\Obj42\Debug\REGISTRY.SBR" : $(SOURCE) $(DEP_CPP_REGIS) "$(INTDIR)"\
 ".\Obj42\Debug\ixtnsn32.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug ATL Base"


"$(INTDIR)\REGISTRY.OBJ" : $(SOURCE) $(DEP_CPP_REGIS) "$(INTDIR)"\
 "$(INTDIR)\IxtAtd42.pch"

"$(INTDIR)\REGISTRY.SBR" : $(SOURCE) $(DEP_CPP_REGIS) "$(INTDIR)"\
 "$(INTDIR)\IxtAtd42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release ATL Base"


"$(INTDIR)\REGISTRY.OBJ" : $(SOURCE) $(DEP_CPP_REGIS) "$(INTDIR)"\
 "$(INTDIR)\IXtAtr42.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\xtsnimp.cxx

!IF  "$(CFG)" == "ixtnsn32 - Win32 Release"

DEP_CPP_XTSNI=\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	

"$(INTDIR)\xtsnimp.obj" : $(SOURCE) $(DEP_CPP_XTSNI) "$(INTDIR)"\
 "$(INTDIR)\IXTNSN42.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /Ob2 /D "NDEBUG" /D "STRICT" /D "__XT" /D\
 "__DEXPROCS" /D "MSWIND" /D "DLL" /D "__XTENSNDLL__" /D "__CV__" /D "WIN32" /D\
 "_WINDOWS" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D "__ATL_11_USED__"\
 /Fp"$(INTDIR)/IXTNSN42.pch" /Yu"xtensnp.hxx" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug"

DEP_CPP_XTSNI=\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "STRICT" /D\
 "__XT" /D "__DEXPROCS" /D "MSWIND" /D "DLL" /D "__XTENSNDLL__" /D "__CV__" /D\
 "WIN32" /D "_WINDOWS" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D\
 "__ATL_11_USED__" /FR"$(INTDIR)/" /Fp"$(INTDIR)/ixtnsn32.pch" /Yu"xtensnp.hxx"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/ixtnsd40.pdb" /c $(SOURCE) \
	

"$(INTDIR)\xtsnimp.obj" : $(SOURCE) $(DEP_CPP_XTSNI) "$(INTDIR)"\
 "$(INTDIR)\ixtnsn32.pch"
   $(BuildCmds)

"$(INTDIR)\xtsnimp.sbr" : $(SOURCE) $(DEP_CPP_XTSNI) "$(INTDIR)"\
 "$(INTDIR)\ixtnsn32.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release New"

DEP_CPP_XTSNI=\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	

"$(INTDIR)\xtsnimp.obj" : $(SOURCE) $(DEP_CPP_XTSNI) "$(INTDIR)"\
 "$(INTDIR)\IXTNSN42.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /Ob2 /D "NDEBUG" /D "__ATL_11_USED__" /D\
 "STRICT" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "DLL" /D "__XTENSNDLL__" /D\
 "__CV__" /D "WIN32" /D "_WINDOWS" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT"\
 /Fp"$(INTDIR)/IXTNSN42.pch" /Yu"xtensnp.hxx" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug New"

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
	

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D\
 "__ATL_11_USED__" /D "STRICT" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "DLL" /D\
 "__XTENSNDLL__" /D "__CV__" /D "WIN32" /D "_WINDOWS" /D "__ATL_USED__" /D\
 "OS_NO_STREAM_SUPPORT" /FR"Obj42/Debug/" /Fp"Obj42/Debug/ixtnsn32.pch"\
 /Yu"xtensnp.hxx" /Fo"Obj42/Debug/" /Fd"Obj42/Debug/ixtnsd42.pdb" /c $(SOURCE) \
	

".\Obj42\Debug\xtsnimp.obj" : $(SOURCE) $(DEP_CPP_XTSNI) "$(INTDIR)"\
 ".\Obj42\Debug\ixtnsn32.pch"
   $(BuildCmds)

".\Obj42\Debug\xtsnimp.sbr" : $(SOURCE) $(DEP_CPP_XTSNI) "$(INTDIR)"\
 ".\Obj42\Debug\ixtnsn32.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug ATL Base"

# PROP Exclude_From_Build 1
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
	

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release ATL Base"

# PROP Exclude_From_Build 1
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
	

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\IENUMSTR.CXX

!IF  "$(CFG)" == "ixtnsn32 - Win32 Release"

DEP_CPP_IENUMS=\
	".\IENUMSTR.HXX"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\IENUMSTR.OBJ" : $(SOURCE) $(DEP_CPP_IENUMS) "$(INTDIR)"\
 "$(INTDIR)\IXTNSN42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug"

DEP_CPP_IENUMS=\
	".\IENUMSTR.HXX"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\IENUMSTR.OBJ" : $(SOURCE) $(DEP_CPP_IENUMS) "$(INTDIR)"\
 "$(INTDIR)\ixtnsn32.pch"

"$(INTDIR)\IENUMSTR.SBR" : $(SOURCE) $(DEP_CPP_IENUMS) "$(INTDIR)"\
 "$(INTDIR)\ixtnsn32.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release New"

DEP_CPP_IENUMS=\
	".\IENUMSTR.HXX"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\IENUMSTR.OBJ" : $(SOURCE) $(DEP_CPP_IENUMS) "$(INTDIR)"\
 "$(INTDIR)\IXTNSN42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug New"

DEP_CPP_IENUMS=\
	".\cimpxtsn.hxx"\
	".\IENUMSTR.HXX"\
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
	{$(INCLUDE)}"\STRDUP.HXX"\
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
	

".\Obj42\Debug\IENUMSTR.OBJ" : $(SOURCE) $(DEP_CPP_IENUMS) "$(INTDIR)"\
 ".\Obj42\Debug\ixtnsn32.pch"

".\Obj42\Debug\IENUMSTR.SBR" : $(SOURCE) $(DEP_CPP_IENUMS) "$(INTDIR)"\
 ".\Obj42\Debug\ixtnsn32.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug ATL Base"

DEP_CPP_IENUMS=\
	".\cimpxtsn.hxx"\
	".\IENUMSTR.HXX"\
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
	{$(INCLUDE)}"\STRDUP.HXX"\
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
	

"$(INTDIR)\IENUMSTR.OBJ" : $(SOURCE) $(DEP_CPP_IENUMS) "$(INTDIR)"\
 "$(INTDIR)\IxtAtd42.pch"

"$(INTDIR)\IENUMSTR.SBR" : $(SOURCE) $(DEP_CPP_IENUMS) "$(INTDIR)"\
 "$(INTDIR)\IxtAtd42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release ATL Base"

DEP_CPP_IENUMS=\
	".\cimpxtsn.hxx"\
	".\IENUMSTR.HXX"\
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
	{$(INCLUDE)}"\STRDUP.HXX"\
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
	

"$(INTDIR)\IENUMSTR.OBJ" : $(SOURCE) $(DEP_CPP_IENUMS) "$(INTDIR)"\
 "$(INTDIR)\IXtAtr42.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\HDRENTRX.CXX
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
	

!IF  "$(CFG)" == "ixtnsn32 - Win32 Release"


"$(INTDIR)\HDRENTRX.OBJ" : $(SOURCE) $(DEP_CPP_HDREN) "$(INTDIR)"\
 "$(INTDIR)\IXTNSN42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug"


"$(INTDIR)\HDRENTRX.OBJ" : $(SOURCE) $(DEP_CPP_HDREN) "$(INTDIR)"\
 "$(INTDIR)\ixtnsn32.pch"

"$(INTDIR)\HDRENTRX.SBR" : $(SOURCE) $(DEP_CPP_HDREN) "$(INTDIR)"\
 "$(INTDIR)\ixtnsn32.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release New"


"$(INTDIR)\HDRENTRX.OBJ" : $(SOURCE) $(DEP_CPP_HDREN) "$(INTDIR)"\
 "$(INTDIR)\IXTNSN42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug New"


".\Obj42\Debug\HDRENTRX.OBJ" : $(SOURCE) $(DEP_CPP_HDREN) "$(INTDIR)"\
 ".\Obj42\Debug\ixtnsn32.pch"

".\Obj42\Debug\HDRENTRX.SBR" : $(SOURCE) $(DEP_CPP_HDREN) "$(INTDIR)"\
 ".\Obj42\Debug\ixtnsn32.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug ATL Base"


"$(INTDIR)\HDRENTRX.OBJ" : $(SOURCE) $(DEP_CPP_HDREN) "$(INTDIR)"\
 "$(INTDIR)\IxtAtd42.pch"

"$(INTDIR)\HDRENTRX.SBR" : $(SOURCE) $(DEP_CPP_HDREN) "$(INTDIR)"\
 "$(INTDIR)\IxtAtd42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release ATL Base"


"$(INTDIR)\HDRENTRX.OBJ" : $(SOURCE) $(DEP_CPP_HDREN) "$(INTDIR)"\
 "$(INTDIR)\IXtAtr42.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\HELPTEXT.CXX
DEP_CPP_HELPT=\
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
	{$(INCLUDE)}"\HELPTXTX.HXX"\
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
	

!IF  "$(CFG)" == "ixtnsn32 - Win32 Release"


"$(INTDIR)\HELPTEXT.OBJ" : $(SOURCE) $(DEP_CPP_HELPT) "$(INTDIR)"\
 "$(INTDIR)\IXTNSN42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug"


"$(INTDIR)\HELPTEXT.OBJ" : $(SOURCE) $(DEP_CPP_HELPT) "$(INTDIR)"\
 "$(INTDIR)\ixtnsn32.pch"

"$(INTDIR)\HELPTEXT.SBR" : $(SOURCE) $(DEP_CPP_HELPT) "$(INTDIR)"\
 "$(INTDIR)\ixtnsn32.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release New"


"$(INTDIR)\HELPTEXT.OBJ" : $(SOURCE) $(DEP_CPP_HELPT) "$(INTDIR)"\
 "$(INTDIR)\IXTNSN42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug New"


".\Obj42\Debug\HELPTEXT.OBJ" : $(SOURCE) $(DEP_CPP_HELPT) "$(INTDIR)"\
 ".\Obj42\Debug\ixtnsn32.pch"

".\Obj42\Debug\HELPTEXT.SBR" : $(SOURCE) $(DEP_CPP_HELPT) "$(INTDIR)"\
 ".\Obj42\Debug\ixtnsn32.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug ATL Base"


"$(INTDIR)\HELPTEXT.OBJ" : $(SOURCE) $(DEP_CPP_HELPT) "$(INTDIR)"\
 "$(INTDIR)\IxtAtd42.pch"

"$(INTDIR)\HELPTEXT.SBR" : $(SOURCE) $(DEP_CPP_HELPT) "$(INTDIR)"\
 "$(INTDIR)\IxtAtd42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release ATL Base"


"$(INTDIR)\HELPTEXT.OBJ" : $(SOURCE) $(DEP_CPP_HELPT) "$(INTDIR)"\
 "$(INTDIR)\IXtAtr42.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\NUMEDITX.CXX
DEP_CPP_NUMED=\
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
	{$(INCLUDE)}"\numeditx.hxx"\
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
	

!IF  "$(CFG)" == "ixtnsn32 - Win32 Release"


"$(INTDIR)\NUMEDITX.OBJ" : $(SOURCE) $(DEP_CPP_NUMED) "$(INTDIR)"\
 "$(INTDIR)\IXTNSN42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug"


"$(INTDIR)\NUMEDITX.OBJ" : $(SOURCE) $(DEP_CPP_NUMED) "$(INTDIR)"\
 "$(INTDIR)\ixtnsn32.pch"

"$(INTDIR)\NUMEDITX.SBR" : $(SOURCE) $(DEP_CPP_NUMED) "$(INTDIR)"\
 "$(INTDIR)\ixtnsn32.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release New"


"$(INTDIR)\NUMEDITX.OBJ" : $(SOURCE) $(DEP_CPP_NUMED) "$(INTDIR)"\
 "$(INTDIR)\IXTNSN42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug New"


".\Obj42\Debug\NUMEDITX.OBJ" : $(SOURCE) $(DEP_CPP_NUMED) "$(INTDIR)"\
 ".\Obj42\Debug\ixtnsn32.pch"

".\Obj42\Debug\NUMEDITX.SBR" : $(SOURCE) $(DEP_CPP_NUMED) "$(INTDIR)"\
 ".\Obj42\Debug\ixtnsn32.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug ATL Base"


"$(INTDIR)\NUMEDITX.OBJ" : $(SOURCE) $(DEP_CPP_NUMED) "$(INTDIR)"\
 "$(INTDIR)\IxtAtd42.pch"

"$(INTDIR)\NUMEDITX.SBR" : $(SOURCE) $(DEP_CPP_NUMED) "$(INTDIR)"\
 "$(INTDIR)\IxtAtd42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release ATL Base"


"$(INTDIR)\NUMEDITX.OBJ" : $(SOURCE) $(DEP_CPP_NUMED) "$(INTDIR)"\
 "$(INTDIR)\IXtAtr42.pch"


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
	

!IF  "$(CFG)" == "ixtnsn32 - Win32 Release"


"$(INTDIR)\OBJCONTX.OBJ" : $(SOURCE) $(DEP_CPP_OBJCO) "$(INTDIR)"\
 "$(INTDIR)\IXTNSN42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug"


"$(INTDIR)\OBJCONTX.OBJ" : $(SOURCE) $(DEP_CPP_OBJCO) "$(INTDIR)"\
 "$(INTDIR)\ixtnsn32.pch"

"$(INTDIR)\OBJCONTX.SBR" : $(SOURCE) $(DEP_CPP_OBJCO) "$(INTDIR)"\
 "$(INTDIR)\ixtnsn32.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release New"


"$(INTDIR)\OBJCONTX.OBJ" : $(SOURCE) $(DEP_CPP_OBJCO) "$(INTDIR)"\
 "$(INTDIR)\IXTNSN42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug New"


".\Obj42\Debug\OBJCONTX.OBJ" : $(SOURCE) $(DEP_CPP_OBJCO) "$(INTDIR)"\
 ".\Obj42\Debug\ixtnsn32.pch"

".\Obj42\Debug\OBJCONTX.SBR" : $(SOURCE) $(DEP_CPP_OBJCO) "$(INTDIR)"\
 ".\Obj42\Debug\ixtnsn32.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug ATL Base"


"$(INTDIR)\OBJCONTX.OBJ" : $(SOURCE) $(DEP_CPP_OBJCO) "$(INTDIR)"\
 "$(INTDIR)\IxtAtd42.pch"

"$(INTDIR)\OBJCONTX.SBR" : $(SOURCE) $(DEP_CPP_OBJCO) "$(INTDIR)"\
 "$(INTDIR)\IxtAtd42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release ATL Base"


"$(INTDIR)\OBJCONTX.OBJ" : $(SOURCE) $(DEP_CPP_OBJCO) "$(INTDIR)"\
 "$(INTDIR)\IXtAtr42.pch"


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
	

!IF  "$(CFG)" == "ixtnsn32 - Win32 Release"


"$(INTDIR)\STRUTIL.OBJ" : $(SOURCE) $(DEP_CPP_STRUT) "$(INTDIR)"\
 "$(INTDIR)\IXTNSN42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug"


"$(INTDIR)\STRUTIL.OBJ" : $(SOURCE) $(DEP_CPP_STRUT) "$(INTDIR)"\
 "$(INTDIR)\ixtnsn32.pch"

"$(INTDIR)\STRUTIL.SBR" : $(SOURCE) $(DEP_CPP_STRUT) "$(INTDIR)"\
 "$(INTDIR)\ixtnsn32.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release New"


"$(INTDIR)\STRUTIL.OBJ" : $(SOURCE) $(DEP_CPP_STRUT) "$(INTDIR)"\
 "$(INTDIR)\IXTNSN42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug New"


".\Obj42\Debug\STRUTIL.OBJ" : $(SOURCE) $(DEP_CPP_STRUT) "$(INTDIR)"\
 ".\Obj42\Debug\ixtnsn32.pch"

".\Obj42\Debug\STRUTIL.SBR" : $(SOURCE) $(DEP_CPP_STRUT) "$(INTDIR)"\
 ".\Obj42\Debug\ixtnsn32.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug ATL Base"


"$(INTDIR)\STRUTIL.OBJ" : $(SOURCE) $(DEP_CPP_STRUT) "$(INTDIR)"\
 "$(INTDIR)\IxtAtd42.pch"

"$(INTDIR)\STRUTIL.SBR" : $(SOURCE) $(DEP_CPP_STRUT) "$(INTDIR)"\
 "$(INTDIR)\IxtAtd42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release ATL Base"


"$(INTDIR)\STRUTIL.OBJ" : $(SOURCE) $(DEP_CPP_STRUT) "$(INTDIR)"\
 "$(INTDIR)\IXtAtr42.pch"


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
	

!IF  "$(CFG)" == "ixtnsn32 - Win32 Release"


"$(INTDIR)\dllbindx.obj" : $(SOURCE) $(DEP_CPP_DLLBI) "$(INTDIR)"\
 "$(INTDIR)\IXTNSN42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug"


"$(INTDIR)\dllbindx.obj" : $(SOURCE) $(DEP_CPP_DLLBI) "$(INTDIR)"\
 "$(INTDIR)\ixtnsn32.pch"

"$(INTDIR)\dllbindx.sbr" : $(SOURCE) $(DEP_CPP_DLLBI) "$(INTDIR)"\
 "$(INTDIR)\ixtnsn32.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release New"


"$(INTDIR)\dllbindx.obj" : $(SOURCE) $(DEP_CPP_DLLBI) "$(INTDIR)"\
 "$(INTDIR)\IXTNSN42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug New"


".\Obj42\Debug\dllbindx.obj" : $(SOURCE) $(DEP_CPP_DLLBI) "$(INTDIR)"\
 ".\Obj42\Debug\ixtnsn32.pch"

".\Obj42\Debug\dllbindx.sbr" : $(SOURCE) $(DEP_CPP_DLLBI) "$(INTDIR)"\
 ".\Obj42\Debug\ixtnsn32.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug ATL Base"


"$(INTDIR)\dllbindx.obj" : $(SOURCE) $(DEP_CPP_DLLBI) "$(INTDIR)"\
 "$(INTDIR)\IxtAtd42.pch"

"$(INTDIR)\dllbindx.sbr" : $(SOURCE) $(DEP_CPP_DLLBI) "$(INTDIR)"\
 "$(INTDIR)\IxtAtd42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release ATL Base"


"$(INTDIR)\dllbindx.obj" : $(SOURCE) $(DEP_CPP_DLLBI) "$(INTDIR)"\
 "$(INTDIR)\IXtAtr42.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DBLNUMED.CXX
DEP_CPP_DBLNU=\
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
	{$(INCLUDE)}"\dblnumex.hxx"\
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
	{$(INCLUDE)}"\numeditx.hxx"\
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
	

!IF  "$(CFG)" == "ixtnsn32 - Win32 Release"


"$(INTDIR)\DBLNUMED.OBJ" : $(SOURCE) $(DEP_CPP_DBLNU) "$(INTDIR)"\
 "$(INTDIR)\IXTNSN42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug"


"$(INTDIR)\DBLNUMED.OBJ" : $(SOURCE) $(DEP_CPP_DBLNU) "$(INTDIR)"\
 "$(INTDIR)\ixtnsn32.pch"

"$(INTDIR)\DBLNUMED.SBR" : $(SOURCE) $(DEP_CPP_DBLNU) "$(INTDIR)"\
 "$(INTDIR)\ixtnsn32.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release New"


"$(INTDIR)\DBLNUMED.OBJ" : $(SOURCE) $(DEP_CPP_DBLNU) "$(INTDIR)"\
 "$(INTDIR)\IXTNSN42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug New"


".\Obj42\Debug\DBLNUMED.OBJ" : $(SOURCE) $(DEP_CPP_DBLNU) "$(INTDIR)"\
 ".\Obj42\Debug\ixtnsn32.pch"

".\Obj42\Debug\DBLNUMED.SBR" : $(SOURCE) $(DEP_CPP_DBLNU) "$(INTDIR)"\
 ".\Obj42\Debug\ixtnsn32.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug ATL Base"


"$(INTDIR)\DBLNUMED.OBJ" : $(SOURCE) $(DEP_CPP_DBLNU) "$(INTDIR)"\
 "$(INTDIR)\IxtAtd42.pch"

"$(INTDIR)\DBLNUMED.SBR" : $(SOURCE) $(DEP_CPP_DBLNU) "$(INTDIR)"\
 "$(INTDIR)\IxtAtd42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release ATL Base"


"$(INTDIR)\DBLNUMED.OBJ" : $(SOURCE) $(DEP_CPP_DBLNU) "$(INTDIR)"\
 "$(INTDIR)\IXtAtr42.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CTFX.CXX
DEP_CPP_CTFX_=\
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
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
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
	
# PROP Exclude_From_Build 1
# End Source File
################################################################################
# Begin Source File

SOURCE=.\DUMPOUT.CXX

!IF  "$(CFG)" == "ixtnsn32 - Win32 Release"

# PROP Exclude_From_Build 0
DEP_CPP_DUMPO=\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	

"$(INTDIR)\DUMPOUT.OBJ" : $(SOURCE) $(DEP_CPP_DUMPO) "$(INTDIR)"\
 "$(INTDIR)\IXTNSN42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug"

DEP_CPP_DUMPO=\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	

"$(INTDIR)\DUMPOUT.OBJ" : $(SOURCE) $(DEP_CPP_DUMPO) "$(INTDIR)"\
 "$(INTDIR)\ixtnsn32.pch"

"$(INTDIR)\DUMPOUT.SBR" : $(SOURCE) $(DEP_CPP_DUMPO) "$(INTDIR)"\
 "$(INTDIR)\ixtnsn32.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release New"

# PROP BASE Exclude_From_Build 0
# PROP Exclude_From_Build 0
DEP_CPP_DUMPO=\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	

"$(INTDIR)\DUMPOUT.OBJ" : $(SOURCE) $(DEP_CPP_DUMPO) "$(INTDIR)"\
 "$(INTDIR)\IXTNSN42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug New"

DEP_CPP_DUMPO=\
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
	

".\Obj42\Debug\DUMPOUT.OBJ" : $(SOURCE) $(DEP_CPP_DUMPO) "$(INTDIR)"\
 ".\Obj42\Debug\ixtnsn32.pch"

".\Obj42\Debug\DUMPOUT.SBR" : $(SOURCE) $(DEP_CPP_DUMPO) "$(INTDIR)"\
 ".\Obj42\Debug\ixtnsn32.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug ATL Base"

DEP_CPP_DUMPO=\
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
	

"$(INTDIR)\DUMPOUT.OBJ" : $(SOURCE) $(DEP_CPP_DUMPO) "$(INTDIR)"\
 "$(INTDIR)\IxtAtd42.pch"

"$(INTDIR)\DUMPOUT.SBR" : $(SOURCE) $(DEP_CPP_DUMPO) "$(INTDIR)"\
 "$(INTDIR)\IxtAtd42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release ATL Base"

# PROP BASE Exclude_From_Build 0
# PROP Exclude_From_Build 0
DEP_CPP_DUMPO=\
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
	

"$(INTDIR)\DUMPOUT.OBJ" : $(SOURCE) $(DEP_CPP_DUMPO) "$(INTDIR)"\
 "$(INTDIR)\IXtAtr42.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\VALIDADD.CXX
DEP_CPP_VALID=\
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
	

!IF  "$(CFG)" == "ixtnsn32 - Win32 Release"

# PROP Exclude_From_Build 0

"$(INTDIR)\VALIDADD.OBJ" : $(SOURCE) $(DEP_CPP_VALID) "$(INTDIR)"\
 "$(INTDIR)\IXTNSN42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug"


"$(INTDIR)\VALIDADD.OBJ" : $(SOURCE) $(DEP_CPP_VALID) "$(INTDIR)"\
 "$(INTDIR)\ixtnsn32.pch"

"$(INTDIR)\VALIDADD.SBR" : $(SOURCE) $(DEP_CPP_VALID) "$(INTDIR)"\
 "$(INTDIR)\ixtnsn32.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release New"

# PROP BASE Exclude_From_Build 0
# PROP Exclude_From_Build 0

"$(INTDIR)\VALIDADD.OBJ" : $(SOURCE) $(DEP_CPP_VALID) "$(INTDIR)"\
 "$(INTDIR)\IXTNSN42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug New"


".\Obj42\Debug\VALIDADD.OBJ" : $(SOURCE) $(DEP_CPP_VALID) "$(INTDIR)"\
 ".\Obj42\Debug\ixtnsn32.pch"

".\Obj42\Debug\VALIDADD.SBR" : $(SOURCE) $(DEP_CPP_VALID) "$(INTDIR)"\
 ".\Obj42\Debug\ixtnsn32.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug ATL Base"


"$(INTDIR)\VALIDADD.OBJ" : $(SOURCE) $(DEP_CPP_VALID) "$(INTDIR)"\
 "$(INTDIR)\IxtAtd42.pch"

"$(INTDIR)\VALIDADD.SBR" : $(SOURCE) $(DEP_CPP_VALID) "$(INTDIR)"\
 "$(INTDIR)\IxtAtd42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release ATL Base"

# PROP BASE Exclude_From_Build 0
# PROP Exclude_From_Build 0

"$(INTDIR)\VALIDADD.OBJ" : $(SOURCE) $(DEP_CPP_VALID) "$(INTDIR)"\
 "$(INTDIR)\IXtAtr42.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\xtsnatl.cpp
DEP_CPP_XTSNA=\
	".\cimpxtsn.hxx"\
	".\Xtensnp.hxx"\
	{$(INCLUDE)}"\ATLIMPL.CPP"\
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
	

!IF  "$(CFG)" == "ixtnsn32 - Win32 Release"

# PROP Exclude_From_Build 0

"$(INTDIR)\xtsnatl.obj" : $(SOURCE) $(DEP_CPP_XTSNA) "$(INTDIR)"\
 "$(INTDIR)\IXTNSN42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug"

# PROP Exclude_From_Build 0

"$(INTDIR)\xtsnatl.obj" : $(SOURCE) $(DEP_CPP_XTSNA) "$(INTDIR)"\
 "$(INTDIR)\ixtnsn32.pch"

"$(INTDIR)\xtsnatl.sbr" : $(SOURCE) $(DEP_CPP_XTSNA) "$(INTDIR)"\
 "$(INTDIR)\ixtnsn32.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release New"

# PROP Exclude_From_Build 0

"$(INTDIR)\xtsnatl.obj" : $(SOURCE) $(DEP_CPP_XTSNA) "$(INTDIR)"\
 "$(INTDIR)\IXTNSN42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug New"

# PROP Exclude_From_Build 0

".\Obj42\Debug\xtsnatl.obj" : $(SOURCE) $(DEP_CPP_XTSNA) "$(INTDIR)"\
 ".\Obj42\Debug\ixtnsn32.pch"

".\Obj42\Debug\xtsnatl.sbr" : $(SOURCE) $(DEP_CPP_XTSNA) "$(INTDIR)"\
 ".\Obj42\Debug\ixtnsn32.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug ATL Base"


"$(INTDIR)\xtsnatl.obj" : $(SOURCE) $(DEP_CPP_XTSNA) "$(INTDIR)"\
 "$(INTDIR)\IxtAtd42.pch"

"$(INTDIR)\xtsnatl.sbr" : $(SOURCE) $(DEP_CPP_XTSNA) "$(INTDIR)"\
 "$(INTDIR)\IxtAtd42.pch"


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release ATL Base"


"$(INTDIR)\xtsnatl.obj" : $(SOURCE) $(DEP_CPP_XTSNA) "$(INTDIR)"\
 "$(INTDIR)\IXtAtr42.pch"


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
	

!IF  "$(CFG)" == "ixtnsn32 - Win32 Release"


"$(INTDIR)\dummy5.obj" : $(SOURCE) $(DEP_CPP_DUMMY5) "$(INTDIR)"\
 "$(INTDIR)\IXTNSN42.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /Ob2 /D "NDEBUG" /D "STRICT" /D "__XT" /D\
 "__DEXPROCS" /D "MSWIND" /D "DLL" /D "__XTENSNDLL__" /D "__CV__" /D "WIN32" /D\
 "_WINDOWS" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D "__ATL_11_USED__"\
 /Fp"$(INTDIR)/IXTNSN42.pch" /Yu"xtensnp.hxx" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug"


BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "STRICT" /D\
 "__XT" /D "__DEXPROCS" /D "MSWIND" /D "DLL" /D "__XTENSNDLL__" /D "__CV__" /D\
 "WIN32" /D "_WINDOWS" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D\
 "__ATL_11_USED__" /FR"$(INTDIR)/" /Fp"$(INTDIR)/ixtnsn32.pch" /Yu"xtensnp.hxx"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/ixtnsd40.pdb" /c $(SOURCE) \
	

"$(INTDIR)\dummy5.obj" : $(SOURCE) $(DEP_CPP_DUMMY5) "$(INTDIR)"\
 "$(INTDIR)\ixtnsn32.pch"
   $(BuildCmds)

"$(INTDIR)\dummy5.sbr" : $(SOURCE) $(DEP_CPP_DUMMY5) "$(INTDIR)"\
 "$(INTDIR)\ixtnsn32.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release New"


"$(INTDIR)\dummy5.obj" : $(SOURCE) $(DEP_CPP_DUMMY5) "$(INTDIR)"\
 "$(INTDIR)\IXTNSN42.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /Ob2 /D "NDEBUG" /D "__ATL_11_USED__" /D\
 "STRICT" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "DLL" /D "__XTENSNDLL__" /D\
 "__CV__" /D "WIN32" /D "_WINDOWS" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT"\
 /Fp"$(INTDIR)/IXTNSN42.pch" /Yu"xtensnp.hxx" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug New"


BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D\
 "__ATL_11_USED__" /D "STRICT" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "DLL" /D\
 "__XTENSNDLL__" /D "__CV__" /D "WIN32" /D "_WINDOWS" /D "__ATL_USED__" /D\
 "OS_NO_STREAM_SUPPORT" /FR"Obj42/Debug/" /Fp"Obj42/Debug/ixtnsn32.pch"\
 /Yu"xtensnp.hxx" /Fo"Obj42/Debug/" /Fd"Obj42/Debug/ixtnsd42.pdb" /c $(SOURCE) \
	

".\Obj42\Debug\dummy5.obj" : $(SOURCE) $(DEP_CPP_DUMMY5) "$(INTDIR)"\
 ".\Obj42\Debug\ixtnsn32.pch"
   $(BuildCmds)

".\Obj42\Debug\dummy5.sbr" : $(SOURCE) $(DEP_CPP_DUMMY5) "$(INTDIR)"\
 ".\Obj42\Debug\ixtnsn32.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug ATL Base"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release ATL Base"

# PROP Exclude_From_Build 1

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
	

!IF  "$(CFG)" == "ixtnsn32 - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release New"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug New"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug ATL Base"


BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D\
 "__ATL_11_USED__" /D "__ATL_XTENSION_BASE__" /D "STRICT" /D "__XT" /D\
 "__DEXPROCS" /D "MSWIND" /D "DLL" /D "__XTENSNDLL__" /D "__CV__" /D "WIN32" /D\
 "_WINDOWS" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/IxtAtd42.pch" /Yu"xtensnp.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/IxtAtd42.pdb" /c $(SOURCE) \
	

"$(INTDIR)\XtencAtl.obj" : $(SOURCE) $(DEP_CPP_XTENCA) "$(INTDIR)"\
 "$(INTDIR)\IxtAtd42.pch"
   $(BuildCmds)

"$(INTDIR)\XtencAtl.sbr" : $(SOURCE) $(DEP_CPP_XTENCA) "$(INTDIR)"\
 "$(INTDIR)\IxtAtd42.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release ATL Base"


"$(INTDIR)\XtencAtl.obj" : $(SOURCE) $(DEP_CPP_XTENCA) "$(INTDIR)"\
 "$(INTDIR)\IXtAtr42.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /Ob2 /D "NDEBUG" /D "__ATL_11_USED__" /D\
 "__ATL_XTENSION_BASE__" /D "STRICT" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D\
 "DLL" /D "__XTENSNDLL__" /D "__CV__" /D "WIN32" /D "_WINDOWS" /D "__ATL_USED__"\
 /D "OS_NO_STREAM_SUPPORT" /Fp"$(INTDIR)/IXtAtr42.pch" /Yu"xtensnp.hxx"\
 /Fo"$(INTDIR)/" /c $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Ctfxmfc.cpp

!IF  "$(CFG)" == "ixtnsn32 - Win32 Release"

DEP_CPP_CTFXM=\
	".\cimpxtsn.hxx"\
	".\CtfxMfc.nocom.cpp"\
	".\StdAfx.h"\
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
	{$(INCLUDE)}"\CSPoint.h"\
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
	
# ADD CPP /Yu"StdAfx.h"

"$(INTDIR)\Ctfxmfc.obj" : $(SOURCE) $(DEP_CPP_CTFXM) "$(INTDIR)"\
 "$(INTDIR)\IXTNSN42.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /Ob2 /D "NDEBUG" /D "STRICT" /D "__XT" /D\
 "__DEXPROCS" /D "MSWIND" /D "DLL" /D "__XTENSNDLL__" /D "__CV__" /D "WIN32" /D\
 "_WINDOWS" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D "__ATL_11_USED__"\
 /Fp"$(INTDIR)/IXTNSN42.pch" /Yu"StdAfx.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug"

DEP_CPP_CTFXM=\
	".\cimpxtsn.hxx"\
	".\CtfxMfc.nocom.cpp"\
	".\StdAfx.h"\
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
	{$(INCLUDE)}"\CSPoint.h"\
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
	
# ADD CPP /Yu"StdAfx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "STRICT" /D\
 "__XT" /D "__DEXPROCS" /D "MSWIND" /D "DLL" /D "__XTENSNDLL__" /D "__CV__" /D\
 "WIN32" /D "_WINDOWS" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D\
 "__ATL_11_USED__" /FR"$(INTDIR)/" /Fp"$(INTDIR)/ixtnsn32.pch" /Yu"StdAfx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/ixtnsd40.pdb" /c $(SOURCE) \
	

"$(INTDIR)\Ctfxmfc.obj" : $(SOURCE) $(DEP_CPP_CTFXM) "$(INTDIR)"\
 "$(INTDIR)\ixtnsn32.pch"
   $(BuildCmds)

"$(INTDIR)\Ctfxmfc.sbr" : $(SOURCE) $(DEP_CPP_CTFXM) "$(INTDIR)"\
 "$(INTDIR)\ixtnsn32.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release New"

DEP_CPP_CTFXM=\
	".\cimpxtsn.hxx"\
	".\CtfxMfc.nocom.cpp"\
	".\StdAfx.h"\
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
	{$(INCLUDE)}"\CSPoint.h"\
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
	
# ADD CPP /Yu"StdAfx.h"

"$(INTDIR)\Ctfxmfc.obj" : $(SOURCE) $(DEP_CPP_CTFXM) "$(INTDIR)"\
 "$(INTDIR)\IXTNSN42.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /Ob2 /D "NDEBUG" /D "__ATL_11_USED__" /D\
 "STRICT" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "DLL" /D "__XTENSNDLL__" /D\
 "__CV__" /D "WIN32" /D "_WINDOWS" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT"\
 /Fp"$(INTDIR)/IXTNSN42.pch" /Yu"StdAfx.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug New"

DEP_CPP_CTFXM=\
	".\cimpxtsn.hxx"\
	".\CtfxMfc.nocom.cpp"\
	".\StdAfx.h"\
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
	
# ADD CPP /Yu"StdAfx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D\
 "__ATL_11_USED__" /D "STRICT" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "DLL" /D\
 "__XTENSNDLL__" /D "__CV__" /D "WIN32" /D "_WINDOWS" /D "__ATL_USED__" /D\
 "OS_NO_STREAM_SUPPORT" /FR"Obj42/Debug/" /Fp"Obj42/Debug/ixtnsn32.pch"\
 /Yu"StdAfx.h" /Fo"Obj42/Debug/" /Fd"Obj42/Debug/ixtnsd42.pdb" /c $(SOURCE) \
	

".\Obj42\Debug\Ctfxmfc.obj" : $(SOURCE) $(DEP_CPP_CTFXM) "$(INTDIR)"\
 ".\Obj42\Debug\ixtnsn32.pch"
   $(BuildCmds)

".\Obj42\Debug\Ctfxmfc.sbr" : $(SOURCE) $(DEP_CPP_CTFXM) "$(INTDIR)"\
 ".\Obj42\Debug\ixtnsn32.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug ATL Base"

DEP_CPP_CTFXM=\
	".\cimpxtsn.hxx"\
	".\CtfxMfc.nocom.cpp"\
	".\StdAfx.h"\
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
	{$(INCLUDE)}"\CSPoint.h"\
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
	
# ADD CPP /Yu"StdAfx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D\
 "__ATL_11_USED__" /D "__ATL_XTENSION_BASE__" /D "STRICT" /D "__XT" /D\
 "__DEXPROCS" /D "MSWIND" /D "DLL" /D "__XTENSNDLL__" /D "__CV__" /D "WIN32" /D\
 "_WINDOWS" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/IxtAtd42.pch" /Yu"StdAfx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/IxtAtd42.pdb" /c $(SOURCE) \
	

"$(INTDIR)\Ctfxmfc.obj" : $(SOURCE) $(DEP_CPP_CTFXM) "$(INTDIR)"\
 "$(INTDIR)\IxtAtd42.pch"
   $(BuildCmds)

"$(INTDIR)\Ctfxmfc.sbr" : $(SOURCE) $(DEP_CPP_CTFXM) "$(INTDIR)"\
 "$(INTDIR)\IxtAtd42.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release ATL Base"

DEP_CPP_CTFXM=\
	".\cimpxtsn.hxx"\
	".\CtfxMfc.nocom.cpp"\
	".\StdAfx.h"\
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
	{$(INCLUDE)}"\CSPoint.h"\
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
	
# ADD CPP /Yu"StdAfx.h"

"$(INTDIR)\Ctfxmfc.obj" : $(SOURCE) $(DEP_CPP_CTFXM) "$(INTDIR)"\
 "$(INTDIR)\IXtAtr42.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /Ob2 /D "NDEBUG" /D "__ATL_11_USED__" /D\
 "__ATL_XTENSION_BASE__" /D "STRICT" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D\
 "DLL" /D "__XTENSNDLL__" /D "__CV__" /D "WIN32" /D "_WINDOWS" /D "__ATL_USED__"\
 /D "OS_NO_STREAM_SUPPORT" /Fp"$(INTDIR)/IXtAtr42.pch" /Yu"StdAfx.h"\
 /Fo"$(INTDIR)/" /c $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\XtsnImpAtl.cpp
DEP_CPP_XTSNIM=\
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
	{$(INCLUDE)}"\XtsnImpAtl.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "ixtnsn32 - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release New"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug New"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Debug ATL Base"


BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D\
 "__ATL_11_USED__" /D "__ATL_XTENSION_BASE__" /D "STRICT" /D "__XT" /D\
 "__DEXPROCS" /D "MSWIND" /D "DLL" /D "__XTENSNDLL__" /D "__CV__" /D "WIN32" /D\
 "_WINDOWS" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/IxtAtd42.pch" /Yu"xtensnp.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/IxtAtd42.pdb" /c $(SOURCE) \
	

"$(INTDIR)\XtsnImpAtl.obj" : $(SOURCE) $(DEP_CPP_XTSNIM) "$(INTDIR)"\
 "$(INTDIR)\IxtAtd42.pch"
   $(BuildCmds)

"$(INTDIR)\XtsnImpAtl.sbr" : $(SOURCE) $(DEP_CPP_XTSNIM) "$(INTDIR)"\
 "$(INTDIR)\IxtAtd42.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ixtnsn32 - Win32 Release ATL Base"


"$(INTDIR)\XtsnImpAtl.obj" : $(SOURCE) $(DEP_CPP_XTSNIM) "$(INTDIR)"\
 "$(INTDIR)\IXtAtr42.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /Ob2 /D "NDEBUG" /D "__ATL_11_USED__" /D\
 "__ATL_XTENSION_BASE__" /D "STRICT" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D\
 "DLL" /D "__XTENSNDLL__" /D "__CV__" /D "WIN32" /D "_WINDOWS" /D "__ATL_USED__"\
 /D "OS_NO_STREAM_SUPPORT" /Fp"$(INTDIR)/IXtAtr42.pch" /Yu"xtensnp.hxx"\
 /Fo"$(INTDIR)/" /c $(SOURCE)


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
