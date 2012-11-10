# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=Dbasere - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Dbasere - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Dbasere - Win32 Release" && "$(CFG)" !=\
 "Dbasere - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Dbasere.mak" CFG="Dbasere - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Dbasere - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Dbasere - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "Dbasere - Win32 Release"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "Dbasere - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "winrel"
# PROP Intermediate_Dir "winrel"
OUTDIR=.\winrel
INTDIR=.\winrel

ALL : "..\..\trias\trias\Dbasere.ext"

CLEAN : 
	-@erase "$(INTDIR)\ALIASSEL.OBJ"
	-@erase "$(INTDIR)\DBASEKEY.OBJ"
	-@erase "$(INTDIR)\Dbasere.pch"
	-@erase "$(INTDIR)\DOFILER.OBJ"
	-@erase "$(INTDIR)\DQLLX.OBJ"
	-@erase "$(INTDIR)\DQLMAIN.OBJ"
	-@erase "$(INTDIR)\DQLY.OBJ"
	-@erase "$(INTDIR)\DQLYFCT.OBJ"
	-@erase "$(INTDIR)\EXPEXPR.OBJ"
	-@erase "$(INTDIR)\GEO_OBJ.OBJ"
	-@erase "$(INTDIR)\GROUPS.OBJ"
	-@erase "$(INTDIR)\KOMPLEXR.OBJ"
	-@erase "$(INTDIR)\KOMPLEXR.res"
	-@erase "$(INTDIR)\PHEADER.OBJ"
	-@erase "$(INTDIR)\RECHSTAT.OBJ"
	-@erase "$(INTDIR)\RESOURCE.OBJ"
	-@erase "$(INTDIR)\SCRIPDLG.OBJ"
	-@erase "$(INTDIR)\STSCRIPT.OBJ"
	-@erase "$(INTDIR)\TOOLS.OBJ"
	-@erase "$(INTDIR)\YYSTYPE.OBJ"
	-@erase "$(OUTDIR)\Dbasere.exp"
	-@erase "$(OUTDIR)\Dbasere.lib"
	-@erase "..\..\trias\trias\Dbasere.ext"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /O2 /D "NDEBUG" /D "DEBUG" /D "WIN32" /D "_WINDOWS" /D "MDX" /D "__CV__" /D "__XT" /D "MSWIND" /D "STRICT" /D "__DEXPROCS" /c
# SUBTRACT CPP /Fr /YX
CPP_PROJ=/nologo /MD /W3 /O2 /D "NDEBUG" /D "DEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "MDX" /D "__CV__" /D "__XT" /D "MSWIND" /D "STRICT" /D "__DEXPROCS"\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\winrel/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/KOMPLEXR.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Dbasere.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 tfrmwork.lib cont32r.lib stdcppr.lib ixtnsr40.lib dbasedll.lib ctl3d32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386 /stub:"d:\triasdev\dbasere\rights.exe" /out:"d:\trias\trias\Dbasere.ext"
LINK32_FLAGS=tfrmwork.lib cont32r.lib stdcppr.lib ixtnsr40.lib dbasedll.lib\
 ctl3d32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/Dbasere.pdb" /machine:I386 /def:".\KOMPLEXR.DEF"\
 /stub:"d:\triasdev\dbasere\rights.exe" /out:"d:\trias\trias\Dbasere.ext"\
 /implib:"$(OUTDIR)/Dbasere.lib" 
DEF_FILE= \
	".\KOMPLEXR.DEF"
LINK32_OBJS= \
	"$(INTDIR)\ALIASSEL.OBJ" \
	"$(INTDIR)\DBASEKEY.OBJ" \
	"$(INTDIR)\DOFILER.OBJ" \
	"$(INTDIR)\DQLLX.OBJ" \
	"$(INTDIR)\DQLMAIN.OBJ" \
	"$(INTDIR)\DQLY.OBJ" \
	"$(INTDIR)\DQLYFCT.OBJ" \
	"$(INTDIR)\EXPEXPR.OBJ" \
	"$(INTDIR)\GEO_OBJ.OBJ" \
	"$(INTDIR)\GROUPS.OBJ" \
	"$(INTDIR)\KOMPLEXR.OBJ" \
	"$(INTDIR)\KOMPLEXR.res" \
	"$(INTDIR)\PHEADER.OBJ" \
	"$(INTDIR)\RECHSTAT.OBJ" \
	"$(INTDIR)\RESOURCE.OBJ" \
	"$(INTDIR)\SCRIPDLG.OBJ" \
	"$(INTDIR)\STSCRIPT.OBJ" \
	"$(INTDIR)\TOOLS.OBJ" \
	"$(INTDIR)\YYSTYPE.OBJ"

"..\..\trias\trias\Dbasere.ext" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Dbasere - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "windebug"
# PROP Intermediate_Dir "windebug"
OUTDIR=.\windebug
INTDIR=.\windebug

ALL : "..\..\trias\trias200\dbasr32d.ext"

CLEAN : 
	-@erase "$(INTDIR)\ALIASSEL.OBJ"
	-@erase "$(INTDIR)\DBASEKEY.OBJ"
	-@erase "$(INTDIR)\Dbasere.pch"
	-@erase "$(INTDIR)\DOFILER.OBJ"
	-@erase "$(INTDIR)\DQLLX.OBJ"
	-@erase "$(INTDIR)\DQLMAIN.OBJ"
	-@erase "$(INTDIR)\DQLY.OBJ"
	-@erase "$(INTDIR)\DQLYFCT.OBJ"
	-@erase "$(INTDIR)\EXPEXPR.OBJ"
	-@erase "$(INTDIR)\GEO_OBJ.OBJ"
	-@erase "$(INTDIR)\GROUPS.OBJ"
	-@erase "$(INTDIR)\KOMPLEXR.OBJ"
	-@erase "$(INTDIR)\KOMPLEXR.res"
	-@erase "$(INTDIR)\PHEADER.OBJ"
	-@erase "$(INTDIR)\RECHSTAT.OBJ"
	-@erase "$(INTDIR)\RESOURCE.OBJ"
	-@erase "$(INTDIR)\SCRIPDLG.OBJ"
	-@erase "$(INTDIR)\STSCRIPT.OBJ"
	-@erase "$(INTDIR)\TOOLS.OBJ"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(INTDIR)\YYSTYPE.OBJ"
	-@erase "$(OUTDIR)\dbasr32d.pdb"
	-@erase "..\..\trias\trias200\dbasr32d.ext"
	-@erase ".\dbasere.exp"
	-@erase ".\dbasere.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

.\windebug\DBASERE.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "MDX" /D "__CV__" /D "__XT" /D "MSWIND" /D "STRICT" /D "__DEXPROCS" /Yu"pheader.h" /c
# SUBTRACT CPP /WX /Fr
CPP_PROJ=/nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "MDX" /D "__CV__" /D "__XT" /D "MSWIND" /D "STRICT" /D "__DEXPROCS"\
 /Fp"$(INTDIR)/Dbasere.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\windebug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/KOMPLEXR.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Dbasere.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 tfrm32d.lib cont32d.lib stdcppd.lib ixtnsd40.lib dbase32d.lib ctl3d32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /debug /machine:I386 /nodefaultlib:"libcmt.lib" /stub:"d:\triasdev\dbasere\rights.exe" /out:"d:\trias\trias200\dbasr32d.ext" /implib:"dbasere.lib" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=tfrm32d.lib cont32d.lib stdcppd.lib ixtnsd40.lib dbase32d.lib\
 ctl3d32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)/dbasr32d.pdb" /debug\
 /machine:I386 /nodefaultlib:"libcmt.lib" /def:".\KOMPLEXR.DEF"\
 /stub:"d:\triasdev\dbasere\rights.exe" /out:"d:\trias\trias200\dbasr32d.ext"\
 /implib:"dbasere.lib" /SUBSYSTEM:windows,4.0 
DEF_FILE= \
	".\KOMPLEXR.DEF"
LINK32_OBJS= \
	"$(INTDIR)\ALIASSEL.OBJ" \
	"$(INTDIR)\DBASEKEY.OBJ" \
	"$(INTDIR)\DOFILER.OBJ" \
	"$(INTDIR)\DQLLX.OBJ" \
	"$(INTDIR)\DQLMAIN.OBJ" \
	"$(INTDIR)\DQLY.OBJ" \
	"$(INTDIR)\DQLYFCT.OBJ" \
	"$(INTDIR)\EXPEXPR.OBJ" \
	"$(INTDIR)\GEO_OBJ.OBJ" \
	"$(INTDIR)\GROUPS.OBJ" \
	"$(INTDIR)\KOMPLEXR.OBJ" \
	"$(INTDIR)\KOMPLEXR.res" \
	"$(INTDIR)\PHEADER.OBJ" \
	"$(INTDIR)\RECHSTAT.OBJ" \
	"$(INTDIR)\RESOURCE.OBJ" \
	"$(INTDIR)\SCRIPDLG.OBJ" \
	"$(INTDIR)\STSCRIPT.OBJ" \
	"$(INTDIR)\TOOLS.OBJ" \
	"$(INTDIR)\YYSTYPE.OBJ"

"..\..\trias\trias200\dbasr32d.ext" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

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

# Name "Dbasere - Win32 Release"
# Name "Dbasere - Win32 Debug"

!IF  "$(CFG)" == "Dbasere - Win32 Release"

!ELSEIF  "$(CFG)" == "Dbasere - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ALIASSEL.CXX
DEP_CPP_ALIAS=\
	"..\INC_GLB.32\gc.h"\
	"..\inc_glb.32\syncthrd.hxx"\
	".\..\INC\C4.H"\
	".\..\INC\D4DATA.H"\
	".\..\INC\D4DATAFI.H"\
	".\..\INC\D4DATE.H"\
	".\..\INC\E4ERROR.H"\
	".\..\INC\E4EXPR.H"\
	".\..\INC\E4PARSE.H"\
	".\..\INC\F4FILESE.H"\
	".\..\INC\I4INDEX.H"\
	".\..\INC\L4LINK.H"\
	".\..\INC\M4MEMO.H"\
	".\..\INC\M4MEMORY.H"\
	".\..\INC\S4SORT.H"\
	".\..\INC\U4UTIL.H"\
	".\Aliassel.htp"\
	".\Aliassel.hxx"\
	".\Komplexr.hr"\
	".\Pheader.h"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Crcb.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\Dbliste.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\Xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_ALIAS=\
	".\win16\komplexr.h"\
	

!IF  "$(CFG)" == "Dbasere - Win32 Release"

# ADD CPP /Yu"pheader.h"

"$(INTDIR)\ALIASSEL.OBJ" : $(SOURCE) $(DEP_CPP_ALIAS) "$(INTDIR)"\
 "$(INTDIR)\Dbasere.pch"
   $(CPP) /nologo /MD /W3 /O2 /D "NDEBUG" /D "DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "MDX" /D "__CV__" /D "__XT" /D "MSWIND" /D "STRICT" /D "__DEXPROCS"\
 /Fp"$(INTDIR)/Dbasere.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasere - Win32 Debug"


"$(INTDIR)\ALIASSEL.OBJ" : $(SOURCE) $(DEP_CPP_ALIAS) "$(INTDIR)"\
 "$(INTDIR)\Dbasere.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "MDX" /D "__CV__" /D "__XT" /D "MSWIND" /D "STRICT" /D\
 "__DEXPROCS" /Fp"$(INTDIR)/Dbasere.pch" /Yu"pheader.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\RESOURCE.CXX
DEP_CPP_RESOU=\
	"..\INC_GLB.32\gc.h"\
	"..\inc_glb.32\syncthrd.hxx"\
	".\..\INC\C4.H"\
	".\..\INC\D4DATA.H"\
	".\..\INC\D4DATAFI.H"\
	".\..\INC\D4DATE.H"\
	".\..\INC\E4ERROR.H"\
	".\..\INC\E4EXPR.H"\
	".\..\INC\E4PARSE.H"\
	".\..\INC\F4FILESE.H"\
	".\..\INC\I4INDEX.H"\
	".\..\INC\L4LINK.H"\
	".\..\INC\M4MEMO.H"\
	".\..\INC\M4MEMORY.H"\
	".\..\INC\S4SORT.H"\
	".\..\INC\U4UTIL.H"\
	".\Komplexr.hr"\
	".\Pheader.h"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Crcb.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\Xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_RESOU=\
	".\win16\komplexr.h"\
	

!IF  "$(CFG)" == "Dbasere - Win32 Release"

# ADD CPP /Yu"pheader.h"

"$(INTDIR)\RESOURCE.OBJ" : $(SOURCE) $(DEP_CPP_RESOU) "$(INTDIR)"\
 "$(INTDIR)\Dbasere.pch"
   $(CPP) /nologo /MD /W3 /O2 /D "NDEBUG" /D "DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "MDX" /D "__CV__" /D "__XT" /D "MSWIND" /D "STRICT" /D "__DEXPROCS"\
 /Fp"$(INTDIR)/Dbasere.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasere - Win32 Debug"


"$(INTDIR)\RESOURCE.OBJ" : $(SOURCE) $(DEP_CPP_RESOU) "$(INTDIR)"\
 "$(INTDIR)\Dbasere.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "MDX" /D "__CV__" /D "__XT" /D "MSWIND" /D "STRICT" /D\
 "__DEXPROCS" /Fp"$(INTDIR)/Dbasere.pch" /Yu"pheader.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DQLY.CXX

!IF  "$(CFG)" == "Dbasere - Win32 Release"

DEP_CPP_DQLY_=\
	"..\INC_GLB.32\gc.h"\
	"..\inc_glb.32\syncthrd.hxx"\
	".\..\INC\C4.H"\
	".\..\INC\D4DATA.H"\
	".\..\INC\D4DATAFI.H"\
	".\..\INC\D4DATE.H"\
	".\..\INC\E4ERROR.H"\
	".\..\INC\E4EXPR.H"\
	".\..\INC\E4PARSE.H"\
	".\..\INC\F4FILESE.H"\
	".\..\INC\I4INDEX.H"\
	".\..\INC\L4LINK.H"\
	".\..\INC\M4MEMO.H"\
	".\..\INC\M4MEMORY.H"\
	".\..\INC\S4SORT.H"\
	".\..\INC\U4UTIL.H"\
	".\Dql.h"\
	".\Dqly.c"\
	".\Dqly.htp"\
	".\Dqlyfct.hxx"\
	".\Expexpr.hxx"\
	".\Groups.hxx"\
	".\Komplexr.hxx"\
	".\Pheader.h"\
	".\Rechstat.hxx"\
	".\Tools.hxx"\
	".\Yystype.hxx"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Crcb.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\Dbasekey.hxx"\
	{$(INCLUDE)}"\Dbasprof.hxx"\
	{$(INCLUDE)}"\Dbliste.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\Geo_inl.hxx"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\Objfeld.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\Relation.hxx"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\Xtencunk.hxx"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtsnaux.hxx"\
	
# ADD CPP /Yu"pheader.h"

"$(INTDIR)\DQLY.OBJ" : $(SOURCE) $(DEP_CPP_DQLY_) "$(INTDIR)"\
 "$(INTDIR)\Dbasere.pch"
   $(CPP) /nologo /MD /W3 /O2 /D "NDEBUG" /D "DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "MDX" /D "__CV__" /D "__XT" /D "MSWIND" /D "STRICT" /D "__DEXPROCS"\
 /Fp"$(INTDIR)/Dbasere.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasere - Win32 Debug"

DEP_CPP_DQLY_=\
	"..\INC_GLB.32\gc.h"\
	"..\inc_glb.32\syncthrd.hxx"\
	".\..\INC\C4.H"\
	".\..\INC\D4DATA.H"\
	".\..\INC\D4DATAFI.H"\
	".\..\INC\D4DATE.H"\
	".\..\INC\E4ERROR.H"\
	".\..\INC\E4EXPR.H"\
	".\..\INC\E4PARSE.H"\
	".\..\INC\F4FILESE.H"\
	".\..\INC\I4INDEX.H"\
	".\..\INC\L4LINK.H"\
	".\..\INC\M4MEMO.H"\
	".\..\INC\M4MEMORY.H"\
	".\..\INC\S4SORT.H"\
	".\..\INC\U4UTIL.H"\
	".\Dql.h"\
	".\Dqly.c"\
	".\Dqly.htp"\
	".\Dqlyfct.hxx"\
	".\Expexpr.hxx"\
	".\Groups.hxx"\
	".\Komplexr.hxx"\
	".\Pheader.h"\
	".\Rechstat.hxx"\
	".\Tools.hxx"\
	".\Yystype.hxx"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Crcb.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\Dbasekey.hxx"\
	{$(INCLUDE)}"\Dbasprof.hxx"\
	{$(INCLUDE)}"\Dbliste.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\Geo_inl.hxx"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\Objfeld.hxx"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\Relation.hxx"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\Xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtsnaux.hxx"\
	{$(INCLUDE)}"\yxvals.h"\
	

"$(INTDIR)\DQLY.OBJ" : $(SOURCE) $(DEP_CPP_DQLY_) "$(INTDIR)"\
 "$(INTDIR)\Dbasere.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "MDX" /D "__CV__" /D "__XT" /D "MSWIND" /D "STRICT" /D\
 "__DEXPROCS" /Fp"$(INTDIR)/Dbasere.pch" /Yu"pheader.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PHEADER.CXX
DEP_CPP_PHEAD=\
	"..\INC_GLB.32\gc.h"\
	"..\inc_glb.32\syncthrd.hxx"\
	".\..\INC\C4.H"\
	".\..\INC\D4DATA.H"\
	".\..\INC\D4DATAFI.H"\
	".\..\INC\D4DATE.H"\
	".\..\INC\E4ERROR.H"\
	".\..\INC\E4EXPR.H"\
	".\..\INC\E4PARSE.H"\
	".\..\INC\F4FILESE.H"\
	".\..\INC\I4INDEX.H"\
	".\..\INC\L4LINK.H"\
	".\..\INC\M4MEMO.H"\
	".\..\INC\M4MEMORY.H"\
	".\..\INC\S4SORT.H"\
	".\..\INC\U4UTIL.H"\
	".\Pheader.h"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Crcb.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\Xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Dbasere - Win32 Release"

# ADD CPP /Yc"pheader.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /O2 /D "NDEBUG" /D "DEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "MDX" /D "__CV__" /D "__XT" /D "MSWIND" /D "STRICT" /D "__DEXPROCS"\
 /Fp"$(INTDIR)/Dbasere.pch" /Yc"pheader.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\PHEADER.OBJ" : $(SOURCE) $(DEP_CPP_PHEAD) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Dbasere.pch" : $(SOURCE) $(DEP_CPP_PHEAD) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Dbasere - Win32 Debug"

# ADD CPP /Yc"pheader.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "MDX" /D "__CV__" /D "__XT" /D "MSWIND" /D "STRICT" /D "__DEXPROCS"\
 /Fp"$(INTDIR)/Dbasere.pch" /Yc"pheader.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\PHEADER.OBJ" : $(SOURCE) $(DEP_CPP_PHEAD) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Dbasere.pch" : $(SOURCE) $(DEP_CPP_PHEAD) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\KOMPLEXR.DEF

!IF  "$(CFG)" == "Dbasere - Win32 Release"

!ELSEIF  "$(CFG)" == "Dbasere - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DBASEKEY.CXX
DEP_CPP_DBASE=\
	"..\INC_GLB.32\gc.h"\
	"..\inc_glb.32\syncthrd.hxx"\
	".\..\INC\C4.H"\
	".\..\INC\D4DATA.H"\
	".\..\INC\D4DATAFI.H"\
	".\..\INC\D4DATE.H"\
	".\..\INC\E4ERROR.H"\
	".\..\INC\E4EXPR.H"\
	".\..\INC\E4PARSE.H"\
	".\..\INC\F4FILESE.H"\
	".\..\INC\I4INDEX.H"\
	".\..\INC\L4LINK.H"\
	".\..\INC\M4MEMO.H"\
	".\..\INC\M4MEMORY.H"\
	".\..\INC\S4SORT.H"\
	".\..\INC\U4UTIL.H"\
	".\Dbasekey.htp"\
	".\Pheader.h"\
	".\Tools.hxx"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Crcb.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\Dbasekey.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\Xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Dbasere - Win32 Release"

# ADD CPP /Yu"pheader.h"

"$(INTDIR)\DBASEKEY.OBJ" : $(SOURCE) $(DEP_CPP_DBASE) "$(INTDIR)"\
 "$(INTDIR)\Dbasere.pch"
   $(CPP) /nologo /MD /W3 /O2 /D "NDEBUG" /D "DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "MDX" /D "__CV__" /D "__XT" /D "MSWIND" /D "STRICT" /D "__DEXPROCS"\
 /Fp"$(INTDIR)/Dbasere.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasere - Win32 Debug"


"$(INTDIR)\DBASEKEY.OBJ" : $(SOURCE) $(DEP_CPP_DBASE) "$(INTDIR)"\
 "$(INTDIR)\Dbasere.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "MDX" /D "__CV__" /D "__XT" /D "MSWIND" /D "STRICT" /D\
 "__DEXPROCS" /Fp"$(INTDIR)/Dbasere.pch" /Yu"pheader.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\KOMPLEXR.RC
DEP_RSC_KOMPL=\
	".\..\INCLUDE\RESSTRG.H"\
	".\DEFABOUT.DLG"\
	".\KOMPLEXR.RCV"\
	".\STSCRIPT.TPL"\
	".\XTENSION.ICO"\
	

"$(INTDIR)\KOMPLEXR.res" : $(SOURCE) $(DEP_RSC_KOMPL) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DQLMAIN.CXX

!IF  "$(CFG)" == "Dbasere - Win32 Release"

DEP_CPP_DQLMA=\
	"..\INC_GLB.32\gc.h"\
	"..\inc_glb.32\syncthrd.hxx"\
	".\..\INC\C4.H"\
	".\..\INC\D4DATA.H"\
	".\..\INC\D4DATAFI.H"\
	".\..\INC\D4DATE.H"\
	".\..\INC\E4ERROR.H"\
	".\..\INC\E4EXPR.H"\
	".\..\INC\E4PARSE.H"\
	".\..\INC\F4FILESE.H"\
	".\..\INC\I4INDEX.H"\
	".\..\INC\L4LINK.H"\
	".\..\INC\M4MEMO.H"\
	".\..\INC\M4MEMORY.H"\
	".\..\INC\S4SORT.H"\
	".\..\INC\U4UTIL.H"\
	".\Dql.h"\
	".\Dqlmain.htp"\
	".\Komplexr.hr"\
	".\Komplexr.hxx"\
	".\Pheader.h"\
	".\Rechstat.hxx"\
	".\Yystype.hxx"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\clipbrd.hxx"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Crcb.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\Dbasekey.hxx"\
	{$(INCLUDE)}"\Dbliste.hxx"\
	{$(INCLUDE)}"\Dqlexprt.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\Geo_inl.hxx"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\Objfeld.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\Xtencunk.hxx"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtsnaux.hxx"\
	
NODEP_CPP_DQLMA=\
	".\win16\komplexr.h"\
	
# ADD CPP /Yu"pheader.h"

"$(INTDIR)\DQLMAIN.OBJ" : $(SOURCE) $(DEP_CPP_DQLMA) "$(INTDIR)"\
 "$(INTDIR)\Dbasere.pch"
   $(CPP) /nologo /MD /W3 /O2 /D "NDEBUG" /D "DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "MDX" /D "__CV__" /D "__XT" /D "MSWIND" /D "STRICT" /D "__DEXPROCS"\
 /Fp"$(INTDIR)/Dbasere.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasere - Win32 Debug"

DEP_CPP_DQLMA=\
	"..\INC_GLB.32\gc.h"\
	"..\inc_glb.32\syncthrd.hxx"\
	".\..\INC\C4.H"\
	".\..\INC\D4DATA.H"\
	".\..\INC\D4DATAFI.H"\
	".\..\INC\D4DATE.H"\
	".\..\INC\E4ERROR.H"\
	".\..\INC\E4EXPR.H"\
	".\..\INC\E4PARSE.H"\
	".\..\INC\F4FILESE.H"\
	".\..\INC\I4INDEX.H"\
	".\..\INC\L4LINK.H"\
	".\..\INC\M4MEMO.H"\
	".\..\INC\M4MEMORY.H"\
	".\..\INC\S4SORT.H"\
	".\..\INC\U4UTIL.H"\
	".\Dql.h"\
	".\Dqlmain.htp"\
	".\Komplexr.hr"\
	".\Komplexr.hxx"\
	".\Pheader.h"\
	".\Rechstat.hxx"\
	".\Yystype.hxx"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\clipbrd.hxx"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Crcb.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\Dbasekey.hxx"\
	{$(INCLUDE)}"\Dbliste.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\Dqlexprt.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\Geo_inl.hxx"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\Objfeld.hxx"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\Xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtsnaux.hxx"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_DQLMA=\
	".\win16\komplexr.h"\
	

"$(INTDIR)\DQLMAIN.OBJ" : $(SOURCE) $(DEP_CPP_DQLMA) "$(INTDIR)"\
 "$(INTDIR)\Dbasere.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "MDX" /D "__CV__" /D "__XT" /D "MSWIND" /D "STRICT" /D\
 "__DEXPROCS" /Fp"$(INTDIR)/Dbasere.pch" /Yu"pheader.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GROUPS.CXX
DEP_CPP_GROUP=\
	"..\INC_GLB.32\gc.h"\
	"..\inc_glb.32\syncthrd.hxx"\
	".\..\INC\C4.H"\
	".\..\INC\D4DATA.H"\
	".\..\INC\D4DATAFI.H"\
	".\..\INC\D4DATE.H"\
	".\..\INC\E4ERROR.H"\
	".\..\INC\E4EXPR.H"\
	".\..\INC\E4PARSE.H"\
	".\..\INC\F4FILESE.H"\
	".\..\INC\I4INDEX.H"\
	".\..\INC\L4LINK.H"\
	".\..\INC\M4MEMO.H"\
	".\..\INC\M4MEMORY.H"\
	".\..\INC\S4SORT.H"\
	".\..\INC\U4UTIL.H"\
	".\Groups.hxx"\
	".\Pheader.h"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Crcb.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\Xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Dbasere - Win32 Release"

# ADD CPP /Yu"pheader.h"

"$(INTDIR)\GROUPS.OBJ" : $(SOURCE) $(DEP_CPP_GROUP) "$(INTDIR)"\
 "$(INTDIR)\Dbasere.pch"
   $(CPP) /nologo /MD /W3 /O2 /D "NDEBUG" /D "DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "MDX" /D "__CV__" /D "__XT" /D "MSWIND" /D "STRICT" /D "__DEXPROCS"\
 /Fp"$(INTDIR)/Dbasere.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasere - Win32 Debug"


"$(INTDIR)\GROUPS.OBJ" : $(SOURCE) $(DEP_CPP_GROUP) "$(INTDIR)"\
 "$(INTDIR)\Dbasere.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "MDX" /D "__CV__" /D "__XT" /D "MSWIND" /D "STRICT" /D\
 "__DEXPROCS" /Fp"$(INTDIR)/Dbasere.pch" /Yu"pheader.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\YYSTYPE.CXX
DEP_CPP_YYSTY=\
	"..\INC_GLB.32\gc.h"\
	"..\inc_glb.32\syncthrd.hxx"\
	".\..\INC\C4.H"\
	".\..\INC\D4DATA.H"\
	".\..\INC\D4DATAFI.H"\
	".\..\INC\D4DATE.H"\
	".\..\INC\E4ERROR.H"\
	".\..\INC\E4EXPR.H"\
	".\..\INC\E4PARSE.H"\
	".\..\INC\F4FILESE.H"\
	".\..\INC\I4INDEX.H"\
	".\..\INC\L4LINK.H"\
	".\..\INC\M4MEMO.H"\
	".\..\INC\M4MEMORY.H"\
	".\..\INC\S4SORT.H"\
	".\..\INC\U4UTIL.H"\
	".\Dql.h"\
	".\Pheader.h"\
	".\Yystype.htp"\
	".\Yystype.hxx"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Crcb.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\Dbasekey.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\Geo_inl.hxx"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\Relation.hxx"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\Xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Dbasere - Win32 Release"

# ADD CPP /Yu"pheader.h"

"$(INTDIR)\YYSTYPE.OBJ" : $(SOURCE) $(DEP_CPP_YYSTY) "$(INTDIR)"\
 "$(INTDIR)\Dbasere.pch"
   $(CPP) /nologo /MD /W3 /O2 /D "NDEBUG" /D "DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "MDX" /D "__CV__" /D "__XT" /D "MSWIND" /D "STRICT" /D "__DEXPROCS"\
 /Fp"$(INTDIR)/Dbasere.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasere - Win32 Debug"


"$(INTDIR)\YYSTYPE.OBJ" : $(SOURCE) $(DEP_CPP_YYSTY) "$(INTDIR)"\
 "$(INTDIR)\Dbasere.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "MDX" /D "__CV__" /D "__XT" /D "MSWIND" /D "STRICT" /D\
 "__DEXPROCS" /Fp"$(INTDIR)/Dbasere.pch" /Yu"pheader.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\KOMPLEXR.CXX

!IF  "$(CFG)" == "Dbasere - Win32 Release"

DEP_CPP_KOMPLE=\
	"..\INC_GLB.32\gc.h"\
	"..\inc_glb.32\syncthrd.hxx"\
	".\..\INC\C4.H"\
	".\..\INC\D4DATA.H"\
	".\..\INC\D4DATAFI.H"\
	".\..\INC\D4DATE.H"\
	".\..\INC\E4ERROR.H"\
	".\..\INC\E4EXPR.H"\
	".\..\INC\E4PARSE.H"\
	".\..\INC\F4FILESE.H"\
	".\..\INC\I4INDEX.H"\
	".\..\INC\L4LINK.H"\
	".\..\INC\M4MEMO.H"\
	".\..\INC\M4MEMORY.H"\
	".\..\INC\S4SORT.H"\
	".\..\INC\U4UTIL.H"\
	".\Defabout.hxx"\
	".\Dql.h"\
	".\Klxguid.h"\
	".\Komplexr.hr"\
	".\Komplexr.htp"\
	".\Komplexr.hxx"\
	".\Pheader.h"\
	".\Stscript.hxx"\
	".\Vers32.h"\
	".\Version.h"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\clipbrd.hxx"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Crcb.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\Dbasprof.hxx"\
	{$(INCLUDE)}"\Dbliste.hxx"\
	{$(INCLUDE)}"\Dbtools.hxx"\
	{$(INCLUDE)}"\Dqlexprt.h"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\Geo_inl.hxx"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\Objfeld.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\Xtencunk.hxx"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	
NODEP_CPP_KOMPLE=\
	".\win16\komplexr.h"\
	".\Win16\Vers16.h"\
	
# ADD CPP /Yu"pheader.h"

"$(INTDIR)\KOMPLEXR.OBJ" : $(SOURCE) $(DEP_CPP_KOMPLE) "$(INTDIR)"\
 "$(INTDIR)\Dbasere.pch"
   $(CPP) /nologo /MD /W3 /O2 /D "NDEBUG" /D "DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "MDX" /D "__CV__" /D "__XT" /D "MSWIND" /D "STRICT" /D "__DEXPROCS"\
 /Fp"$(INTDIR)/Dbasere.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasere - Win32 Debug"

DEP_CPP_KOMPLE=\
	"..\INC_GLB.32\gc.h"\
	"..\inc_glb.32\syncthrd.hxx"\
	".\..\INC\C4.H"\
	".\..\INC\D4DATA.H"\
	".\..\INC\D4DATAFI.H"\
	".\..\INC\D4DATE.H"\
	".\..\INC\E4ERROR.H"\
	".\..\INC\E4EXPR.H"\
	".\..\INC\E4PARSE.H"\
	".\..\INC\F4FILESE.H"\
	".\..\INC\I4INDEX.H"\
	".\..\INC\L4LINK.H"\
	".\..\INC\M4MEMO.H"\
	".\..\INC\M4MEMORY.H"\
	".\..\INC\S4SORT.H"\
	".\..\INC\U4UTIL.H"\
	".\Defabout.hxx"\
	".\Dql.h"\
	".\Klxguid.h"\
	".\Komplexr.hr"\
	".\Komplexr.htp"\
	".\Komplexr.hxx"\
	".\Pheader.h"\
	".\Stscript.hxx"\
	".\Vers32.h"\
	".\Version.h"\
	".\Win16\Vers16.h"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\clipbrd.hxx"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Crcb.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\Dbasprof.hxx"\
	{$(INCLUDE)}"\Dbliste.hxx"\
	{$(INCLUDE)}"\Dbtools.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\Dqlexprt.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\Geo_inl.hxx"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\Objfeld.hxx"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\Xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_KOMPLE=\
	".\win16\komplexr.h"\
	

"$(INTDIR)\KOMPLEXR.OBJ" : $(SOURCE) $(DEP_CPP_KOMPLE) "$(INTDIR)"\
 "$(INTDIR)\Dbasere.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "MDX" /D "__CV__" /D "__XT" /D "MSWIND" /D "STRICT" /D\
 "__DEXPROCS" /Fp"$(INTDIR)/Dbasere.pch" /Yu"pheader.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GEO_OBJ.CXX
DEP_CPP_GEO_O=\
	"..\INC_GLB.32\gc.h"\
	"..\inc_glb.32\syncthrd.hxx"\
	".\..\INC\C4.H"\
	".\..\INC\D4DATA.H"\
	".\..\INC\D4DATAFI.H"\
	".\..\INC\D4DATE.H"\
	".\..\INC\E4ERROR.H"\
	".\..\INC\E4EXPR.H"\
	".\..\INC\E4PARSE.H"\
	".\..\INC\F4FILESE.H"\
	".\..\INC\I4INDEX.H"\
	".\..\INC\L4LINK.H"\
	".\..\INC\M4MEMO.H"\
	".\..\INC\M4MEMORY.H"\
	".\..\INC\S4SORT.H"\
	".\..\INC\U4UTIL.H"\
	".\Geo_obj.htp"\
	".\Pheader.h"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Crcb.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\Geo_inl.hxx"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\Xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Dbasere - Win32 Release"

# ADD CPP /Yu"pheader.h"

"$(INTDIR)\GEO_OBJ.OBJ" : $(SOURCE) $(DEP_CPP_GEO_O) "$(INTDIR)"\
 "$(INTDIR)\Dbasere.pch"
   $(CPP) /nologo /MD /W3 /O2 /D "NDEBUG" /D "DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "MDX" /D "__CV__" /D "__XT" /D "MSWIND" /D "STRICT" /D "__DEXPROCS"\
 /Fp"$(INTDIR)/Dbasere.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasere - Win32 Debug"


"$(INTDIR)\GEO_OBJ.OBJ" : $(SOURCE) $(DEP_CPP_GEO_O) "$(INTDIR)"\
 "$(INTDIR)\Dbasere.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "MDX" /D "__CV__" /D "__XT" /D "MSWIND" /D "STRICT" /D\
 "__DEXPROCS" /Fp"$(INTDIR)/Dbasere.pch" /Yu"pheader.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DOFILER.CXX
DEP_CPP_DOFIL=\
	"..\INC_GLB.32\gc.h"\
	"..\inc_glb.32\syncthrd.hxx"\
	".\..\INC\C4.H"\
	".\..\INC\D4DATA.H"\
	".\..\INC\D4DATAFI.H"\
	".\..\INC\D4DATE.H"\
	".\..\INC\E4ERROR.H"\
	".\..\INC\E4EXPR.H"\
	".\..\INC\E4PARSE.H"\
	".\..\INC\F4FILESE.H"\
	".\..\INC\I4INDEX.H"\
	".\..\INC\L4LINK.H"\
	".\..\INC\M4MEMO.H"\
	".\..\INC\M4MEMORY.H"\
	".\..\INC\S4SORT.H"\
	".\..\INC\U4UTIL.H"\
	".\Pheader.h"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Crcb.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\Dllbindx.hxx"\
	{$(INCLUDE)}"\Dofiler.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\Xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Dbasere - Win32 Release"

# ADD CPP /Yu"pheader.h"

"$(INTDIR)\DOFILER.OBJ" : $(SOURCE) $(DEP_CPP_DOFIL) "$(INTDIR)"\
 "$(INTDIR)\Dbasere.pch"
   $(CPP) /nologo /MD /W3 /O2 /D "NDEBUG" /D "DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "MDX" /D "__CV__" /D "__XT" /D "MSWIND" /D "STRICT" /D "__DEXPROCS"\
 /Fp"$(INTDIR)/Dbasere.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasere - Win32 Debug"


"$(INTDIR)\DOFILER.OBJ" : $(SOURCE) $(DEP_CPP_DOFIL) "$(INTDIR)"\
 "$(INTDIR)\Dbasere.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "MDX" /D "__CV__" /D "__XT" /D "MSWIND" /D "STRICT" /D\
 "__DEXPROCS" /Fp"$(INTDIR)/Dbasere.pch" /Yu"pheader.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SCRIPDLG.CXX
DEP_CPP_SCRIP=\
	"..\INC_GLB.32\gc.h"\
	"..\inc_glb.32\syncthrd.hxx"\
	".\..\INC\C4.H"\
	".\..\INC\D4DATA.H"\
	".\..\INC\D4DATAFI.H"\
	".\..\INC\D4DATE.H"\
	".\..\INC\E4ERROR.H"\
	".\..\INC\E4EXPR.H"\
	".\..\INC\E4PARSE.H"\
	".\..\INC\F4FILESE.H"\
	".\..\INC\I4INDEX.H"\
	".\..\INC\L4LINK.H"\
	".\..\INC\M4MEMO.H"\
	".\..\INC\M4MEMORY.H"\
	".\..\INC\S4SORT.H"\
	".\..\INC\U4UTIL.H"\
	".\Komplexr.hr"\
	".\Pheader.h"\
	".\Scripdlg.htp"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Crcb.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\Xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_SCRIP=\
	".\win16\komplexr.h"\
	

!IF  "$(CFG)" == "Dbasere - Win32 Release"

# ADD CPP /Yu"pheader.h"

"$(INTDIR)\SCRIPDLG.OBJ" : $(SOURCE) $(DEP_CPP_SCRIP) "$(INTDIR)"\
 "$(INTDIR)\Dbasere.pch"
   $(CPP) /nologo /MD /W3 /O2 /D "NDEBUG" /D "DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "MDX" /D "__CV__" /D "__XT" /D "MSWIND" /D "STRICT" /D "__DEXPROCS"\
 /Fp"$(INTDIR)/Dbasere.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasere - Win32 Debug"


"$(INTDIR)\SCRIPDLG.OBJ" : $(SOURCE) $(DEP_CPP_SCRIP) "$(INTDIR)"\
 "$(INTDIR)\Dbasere.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "MDX" /D "__CV__" /D "__XT" /D "MSWIND" /D "STRICT" /D\
 "__DEXPROCS" /Fp"$(INTDIR)/Dbasere.pch" /Yu"pheader.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TOOLS.CXX
DEP_CPP_TOOLS=\
	"..\INC_GLB.32\gc.h"\
	"..\inc_glb.32\syncthrd.hxx"\
	".\..\INC\C4.H"\
	".\..\INC\D4DATA.H"\
	".\..\INC\D4DATAFI.H"\
	".\..\INC\D4DATE.H"\
	".\..\INC\E4ERROR.H"\
	".\..\INC\E4EXPR.H"\
	".\..\INC\E4PARSE.H"\
	".\..\INC\F4FILESE.H"\
	".\..\INC\I4INDEX.H"\
	".\..\INC\L4LINK.H"\
	".\..\INC\M4MEMO.H"\
	".\..\INC\M4MEMORY.H"\
	".\..\INC\S4SORT.H"\
	".\..\INC\U4UTIL.H"\
	".\Komplexr.hr"\
	".\Pheader.h"\
	".\Tools.htp"\
	".\Tools.hxx"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Crcb.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\Dbtools.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\Xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_TOOLS=\
	".\win16\komplexr.h"\
	

!IF  "$(CFG)" == "Dbasere - Win32 Release"

# ADD CPP /Yu"pheader.h"

"$(INTDIR)\TOOLS.OBJ" : $(SOURCE) $(DEP_CPP_TOOLS) "$(INTDIR)"\
 "$(INTDIR)\Dbasere.pch"
   $(CPP) /nologo /MD /W3 /O2 /D "NDEBUG" /D "DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "MDX" /D "__CV__" /D "__XT" /D "MSWIND" /D "STRICT" /D "__DEXPROCS"\
 /Fp"$(INTDIR)/Dbasere.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasere - Win32 Debug"


"$(INTDIR)\TOOLS.OBJ" : $(SOURCE) $(DEP_CPP_TOOLS) "$(INTDIR)"\
 "$(INTDIR)\Dbasere.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "MDX" /D "__CV__" /D "__XT" /D "MSWIND" /D "STRICT" /D\
 "__DEXPROCS" /Fp"$(INTDIR)/Dbasere.pch" /Yu"pheader.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DQLLX.CXX

!IF  "$(CFG)" == "Dbasere - Win32 Release"

DEP_CPP_DQLLX=\
	"..\INC_GLB.32\gc.h"\
	"..\inc_glb.32\syncthrd.hxx"\
	".\..\INC\C4.H"\
	".\..\INC\D4DATA.H"\
	".\..\INC\D4DATAFI.H"\
	".\..\INC\D4DATE.H"\
	".\..\INC\E4ERROR.H"\
	".\..\INC\E4EXPR.H"\
	".\..\INC\E4PARSE.H"\
	".\..\INC\F4FILESE.H"\
	".\..\INC\I4INDEX.H"\
	".\..\INC\L4LINK.H"\
	".\..\INC\M4MEMO.H"\
	".\..\INC\M4MEMORY.H"\
	".\..\INC\S4SORT.H"\
	".\..\INC\U4UTIL.H"\
	".\Dql.h"\
	".\Dqllx.c"\
	".\Dqllx.htp"\
	".\Komplexr.hr"\
	".\Komplexr.hxx"\
	".\Pheader.h"\
	".\Ytab.h"\
	".\Yystype.hxx"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\clipbrd.hxx"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Crcb.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\Dbasekey.hxx"\
	{$(INCLUDE)}"\Dbtools.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\Geo_inl.hxx"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\Xtencunk.hxx"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtsnaux.hxx"\
	
NODEP_CPP_DQLLX=\
	".\win16\komplexr.h"\
	
# ADD CPP /Yu"pheader.h"

"$(INTDIR)\DQLLX.OBJ" : $(SOURCE) $(DEP_CPP_DQLLX) "$(INTDIR)"\
 "$(INTDIR)\Dbasere.pch"
   $(CPP) /nologo /MD /W3 /O2 /D "NDEBUG" /D "DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "MDX" /D "__CV__" /D "__XT" /D "MSWIND" /D "STRICT" /D "__DEXPROCS"\
 /Fp"$(INTDIR)/Dbasere.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasere - Win32 Debug"

DEP_CPP_DQLLX=\
	"..\INC_GLB.32\gc.h"\
	"..\inc_glb.32\syncthrd.hxx"\
	".\..\INC\C4.H"\
	".\..\INC\D4DATA.H"\
	".\..\INC\D4DATAFI.H"\
	".\..\INC\D4DATE.H"\
	".\..\INC\E4ERROR.H"\
	".\..\INC\E4EXPR.H"\
	".\..\INC\E4PARSE.H"\
	".\..\INC\F4FILESE.H"\
	".\..\INC\I4INDEX.H"\
	".\..\INC\L4LINK.H"\
	".\..\INC\M4MEMO.H"\
	".\..\INC\M4MEMORY.H"\
	".\..\INC\S4SORT.H"\
	".\..\INC\U4UTIL.H"\
	".\Dql.h"\
	".\Dqllx.c"\
	".\Dqllx.htp"\
	".\Komplexr.hr"\
	".\Komplexr.hxx"\
	".\Pheader.h"\
	".\Ytab.h"\
	".\Yystype.hxx"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\clipbrd.hxx"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Crcb.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\Dbasekey.hxx"\
	{$(INCLUDE)}"\Dbtools.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\Geo_inl.hxx"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\Xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtsnaux.hxx"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_DQLLX=\
	".\win16\komplexr.h"\
	

"$(INTDIR)\DQLLX.OBJ" : $(SOURCE) $(DEP_CPP_DQLLX) "$(INTDIR)"\
 "$(INTDIR)\Dbasere.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "MDX" /D "__CV__" /D "__XT" /D "MSWIND" /D "STRICT" /D\
 "__DEXPROCS" /Fp"$(INTDIR)/Dbasere.pch" /Yu"pheader.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\EXPEXPR.CXX
DEP_CPP_EXPEX=\
	"..\INC_GLB.32\gc.h"\
	"..\inc_glb.32\syncthrd.hxx"\
	".\..\INC\C4.H"\
	".\..\INC\D4DATA.H"\
	".\..\INC\D4DATAFI.H"\
	".\..\INC\D4DATE.H"\
	".\..\INC\E4ERROR.H"\
	".\..\INC\E4EXPR.H"\
	".\..\INC\E4PARSE.H"\
	".\..\INC\F4FILESE.H"\
	".\..\INC\I4INDEX.H"\
	".\..\INC\L4LINK.H"\
	".\..\INC\M4MEMO.H"\
	".\..\INC\M4MEMORY.H"\
	".\..\INC\S4SORT.H"\
	".\..\INC\U4UTIL.H"\
	".\Expexpr.htp"\
	".\Expexpr.hxx"\
	".\Pheader.h"\
	".\Tools.hxx"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Crcb.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\Xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

!IF  "$(CFG)" == "Dbasere - Win32 Release"

# ADD CPP /Yu"pheader.h"

"$(INTDIR)\EXPEXPR.OBJ" : $(SOURCE) $(DEP_CPP_EXPEX) "$(INTDIR)"\
 "$(INTDIR)\Dbasere.pch"
   $(CPP) /nologo /MD /W3 /O2 /D "NDEBUG" /D "DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "MDX" /D "__CV__" /D "__XT" /D "MSWIND" /D "STRICT" /D "__DEXPROCS"\
 /Fp"$(INTDIR)/Dbasere.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasere - Win32 Debug"


"$(INTDIR)\EXPEXPR.OBJ" : $(SOURCE) $(DEP_CPP_EXPEX) "$(INTDIR)"\
 "$(INTDIR)\Dbasere.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "MDX" /D "__CV__" /D "__XT" /D "MSWIND" /D "STRICT" /D\
 "__DEXPROCS" /Fp"$(INTDIR)/Dbasere.pch" /Yu"pheader.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\RECHSTAT.CXX
DEP_CPP_RECHS=\
	"..\INC_GLB.32\gc.h"\
	"..\inc_glb.32\syncthrd.hxx"\
	".\..\INC\C4.H"\
	".\..\INC\D4DATA.H"\
	".\..\INC\D4DATAFI.H"\
	".\..\INC\D4DATE.H"\
	".\..\INC\E4ERROR.H"\
	".\..\INC\E4EXPR.H"\
	".\..\INC\E4PARSE.H"\
	".\..\INC\F4FILESE.H"\
	".\..\INC\I4INDEX.H"\
	".\..\INC\L4LINK.H"\
	".\..\INC\M4MEMO.H"\
	".\..\INC\M4MEMORY.H"\
	".\..\INC\S4SORT.H"\
	".\..\INC\U4UTIL.H"\
	".\Komplexr.hr"\
	".\Pheader.h"\
	".\Rechstat.htp"\
	".\Rechstat.hxx"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Crcb.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\Xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_RECHS=\
	".\win16\komplexr.h"\
	

!IF  "$(CFG)" == "Dbasere - Win32 Release"

# ADD CPP /Yu"pheader.h"

"$(INTDIR)\RECHSTAT.OBJ" : $(SOURCE) $(DEP_CPP_RECHS) "$(INTDIR)"\
 "$(INTDIR)\Dbasere.pch"
   $(CPP) /nologo /MD /W3 /O2 /D "NDEBUG" /D "DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "MDX" /D "__CV__" /D "__XT" /D "MSWIND" /D "STRICT" /D "__DEXPROCS"\
 /Fp"$(INTDIR)/Dbasere.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasere - Win32 Debug"


"$(INTDIR)\RECHSTAT.OBJ" : $(SOURCE) $(DEP_CPP_RECHS) "$(INTDIR)"\
 "$(INTDIR)\Dbasere.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "MDX" /D "__CV__" /D "__XT" /D "MSWIND" /D "STRICT" /D\
 "__DEXPROCS" /Fp"$(INTDIR)/Dbasere.pch" /Yu"pheader.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DQLYFCT.CXX
DEP_CPP_DQLYF=\
	"..\INC_GLB.32\gc.h"\
	"..\inc_glb.32\syncthrd.hxx"\
	".\..\INC\C4.H"\
	".\..\INC\D4DATA.H"\
	".\..\INC\D4DATAFI.H"\
	".\..\INC\D4DATE.H"\
	".\..\INC\E4ERROR.H"\
	".\..\INC\E4EXPR.H"\
	".\..\INC\E4PARSE.H"\
	".\..\INC\F4FILESE.H"\
	".\..\INC\I4INDEX.H"\
	".\..\INC\L4LINK.H"\
	".\..\INC\M4MEMO.H"\
	".\..\INC\M4MEMORY.H"\
	".\..\INC\S4SORT.H"\
	".\..\INC\U4UTIL.H"\
	".\Dqlyfct.htp"\
	".\Komplexr.hr"\
	".\Pheader.h"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Crcb.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\Dbasekey.hxx"\
	{$(INCLUDE)}"\Dbaserel.hxx"\
	{$(INCLUDE)}"\Dbasprof.hxx"\
	{$(INCLUDE)}"\Dbliste.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\Relation.hxx"\
	{$(INCLUDE)}"\Strdup.hxx"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\Xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_DQLYF=\
	".\win16\komplexr.h"\
	

!IF  "$(CFG)" == "Dbasere - Win32 Release"

# ADD CPP /Yu"pheader.h"

"$(INTDIR)\DQLYFCT.OBJ" : $(SOURCE) $(DEP_CPP_DQLYF) "$(INTDIR)"\
 "$(INTDIR)\Dbasere.pch"
   $(CPP) /nologo /MD /W3 /O2 /D "NDEBUG" /D "DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "MDX" /D "__CV__" /D "__XT" /D "MSWIND" /D "STRICT" /D "__DEXPROCS"\
 /Fp"$(INTDIR)/Dbasere.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasere - Win32 Debug"


"$(INTDIR)\DQLYFCT.OBJ" : $(SOURCE) $(DEP_CPP_DQLYF) "$(INTDIR)"\
 "$(INTDIR)\Dbasere.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "MDX" /D "__CV__" /D "__XT" /D "MSWIND" /D "STRICT" /D\
 "__DEXPROCS" /Fp"$(INTDIR)/Dbasere.pch" /Yu"pheader.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\STSCRIPT.CXX
DEP_CPP_STSCR=\
	"..\INC_GLB.32\gc.h"\
	"..\inc_glb.32\syncthrd.hxx"\
	".\..\INC\C4.H"\
	".\..\INC\D4DATA.H"\
	".\..\INC\D4DATAFI.H"\
	".\..\INC\D4DATE.H"\
	".\..\INC\E4ERROR.H"\
	".\..\INC\E4EXPR.H"\
	".\..\INC\E4PARSE.H"\
	".\..\INC\F4FILESE.H"\
	".\..\INC\I4INDEX.H"\
	".\..\INC\L4LINK.H"\
	".\..\INC\M4MEMO.H"\
	".\..\INC\M4MEMORY.H"\
	".\..\INC\S4SORT.H"\
	".\..\INC\U4UTIL.H"\
	".\Aliassel.hxx"\
	".\Komplexr.hr"\
	".\Pheader.h"\
	".\Stscript.htp"\
	".\Stscript.hxx"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Crcb.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\Dbasprof.hxx"\
	{$(INCLUDE)}"\Dbliste.hxx"\
	{$(INCLUDE)}"\Dbtools.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\Dqlexprt.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\Expreing.hxx"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
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
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\Xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_STSCR=\
	".\win16\komplexr.h"\
	

!IF  "$(CFG)" == "Dbasere - Win32 Release"

# ADD CPP /Yu"pheader.h"

"$(INTDIR)\STSCRIPT.OBJ" : $(SOURCE) $(DEP_CPP_STSCR) "$(INTDIR)"\
 "$(INTDIR)\Dbasere.pch"
   $(CPP) /nologo /MD /W3 /O2 /D "NDEBUG" /D "DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "MDX" /D "__CV__" /D "__XT" /D "MSWIND" /D "STRICT" /D "__DEXPROCS"\
 /Fp"$(INTDIR)/Dbasere.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasere - Win32 Debug"


"$(INTDIR)\STSCRIPT.OBJ" : $(SOURCE) $(DEP_CPP_STSCR) "$(INTDIR)"\
 "$(INTDIR)\Dbasere.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "MDX" /D "__CV__" /D "__XT" /D "MSWIND" /D "STRICT" /D\
 "__DEXPROCS" /Fp"$(INTDIR)/Dbasere.pch" /Yu"pheader.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE)


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
