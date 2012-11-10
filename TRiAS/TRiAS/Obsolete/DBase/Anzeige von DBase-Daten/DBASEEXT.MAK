# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=Dbaseext - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Dbaseext - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Dbaseext - Win32 Release" && "$(CFG)" !=\
 "Dbaseext - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Dbaseext.mak" CFG="Dbaseext - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Dbaseext - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Dbaseext - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "Dbaseext - Win32 Release"
MTL=mktyplib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Dbaseext - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WinRel"
# PROP Intermediate_Dir "WinRel"
OUTDIR=.\WinRel
INTDIR=.\WinRel

ALL : "..\..\trias\trias\Dbaseext.ext"

CLEAN : 
	-@erase "$(INTDIR)\AFNAMEL.OBJ"
	-@erase "$(INTDIR)\DBASE.OBJ"
	-@erase "$(INTDIR)\DBASEEXT.OBJ"
	-@erase "$(INTDIR)\Dbaseext.pch"
	-@erase "$(INTDIR)\DBASEEXT.res"
	-@erase "$(INTDIR)\DBASEOPF.OBJ"
	-@erase "$(INTDIR)\EXTTABL.OBJ"
	-@erase "$(INTDIR)\GIZMOBAR.OBJ"
	-@erase "$(INTDIR)\PHEADER.OBJ"
	-@erase "$(INTDIR)\TABLENAM.OBJ"
	-@erase "$(INTDIR)\V_DBASE.OBJ"
	-@erase "$(INTDIR)\V_DBASE1.OBJ"
	-@erase "$(INTDIR)\V_MEMOFD.OBJ"
	-@erase "$(OUTDIR)\Dbaseext.exp"
	-@erase "$(OUTDIR)\Dbaseext.lib"
	-@erase "..\..\trias\trias\Dbaseext.ext"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "DLL" /D "__XT" /D "__CV__" /D "STRICT" /D "MSWIND" /D "MDX" /D "WINDOWS" /D "__DEXPROCS" /YX /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "DLL"\
 /D "__XT" /D "__CV__" /D "STRICT" /D "MSWIND" /D "MDX" /D "WINDOWS" /D\
 "__DEXPROCS" /Fp"$(INTDIR)/Dbaseext.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\WinRel/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/DBASEEXT.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Dbaseext.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 tfrmwork.lib cont32r.lib stdcppr.lib ixtnsr40.lib dbasedll.lib ctl3d32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386 /nodefaultlib:"libcmt.lib" /stub:"d:\triasdev\dbaseext\rights.exe" /out:"d:\trias\trias\Dbaseext.ext"
LINK32_FLAGS=tfrmwork.lib cont32r.lib stdcppr.lib ixtnsr40.lib dbasedll.lib\
 ctl3d32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/Dbaseext.pdb" /machine:I386 /nodefaultlib:"libcmt.lib"\
 /def:".\DBASEEXT.DEF" /stub:"d:\triasdev\dbaseext\rights.exe"\
 /out:"d:\trias\trias\Dbaseext.ext" /implib:"$(OUTDIR)/Dbaseext.lib" 
DEF_FILE= \
	".\DBASEEXT.DEF"
LINK32_OBJS= \
	"$(INTDIR)\AFNAMEL.OBJ" \
	"$(INTDIR)\DBASE.OBJ" \
	"$(INTDIR)\DBASEEXT.OBJ" \
	"$(INTDIR)\DBASEEXT.res" \
	"$(INTDIR)\DBASEOPF.OBJ" \
	"$(INTDIR)\EXTTABL.OBJ" \
	"$(INTDIR)\GIZMOBAR.OBJ" \
	"$(INTDIR)\PHEADER.OBJ" \
	"$(INTDIR)\TABLENAM.OBJ" \
	"$(INTDIR)\V_DBASE.OBJ" \
	"$(INTDIR)\V_DBASE1.OBJ" \
	"$(INTDIR)\V_MEMOFD.OBJ"

"..\..\trias\trias\Dbaseext.ext" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Dbaseext - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WinDebug"
# PROP Intermediate_Dir "WinDebug"
OUTDIR=.\WinDebug
INTDIR=.\WinDebug

ALL : "..\..\trias\trias200\dbasx32d.ext"

CLEAN : 
	-@erase "$(INTDIR)\AFNAMEL.OBJ"
	-@erase "$(INTDIR)\DBASE.OBJ"
	-@erase "$(INTDIR)\DBASEEXT.OBJ"
	-@erase "$(INTDIR)\Dbaseext.pch"
	-@erase "$(INTDIR)\DBASEEXT.res"
	-@erase "$(INTDIR)\DBASEOPF.OBJ"
	-@erase "$(INTDIR)\EXTTABL.OBJ"
	-@erase "$(INTDIR)\GIZMOBAR.OBJ"
	-@erase "$(INTDIR)\PHEADER.OBJ"
	-@erase "$(INTDIR)\TABLENAM.OBJ"
	-@erase "$(INTDIR)\V_DBASE.OBJ"
	-@erase "$(INTDIR)\V_DBASE1.OBJ"
	-@erase "$(INTDIR)\V_MEMOFD.OBJ"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\dbasx32d.exp"
	-@erase "$(OUTDIR)\dbasx32d.lib"
	-@erase "$(OUTDIR)\dbasx32d.pdb"
	-@erase "..\..\trias\trias200\dbasx32d.ext"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(OUTDIR)/DBASEEXT.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "DLL" /D "__XT" /D "__CV__" /D "STRICT" /D "MSWIND" /D "MDX" /D "WINDOWS" /D "__DEXPROCS" /Yu"pheader.h" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MDd /W3 /WX /Gm /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "DLL" /D "__XT" /D "__CV__" /D "STRICT" /D "MSWIND" /D "MDX" /D "WINDOWS" /D\
 "__DEXPROCS" /Fp"$(INTDIR)/Dbaseext.pch" /Yu"pheader.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\WinDebug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/DBASEEXT.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Dbaseext.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 tfrm32d.lib cont32d.lib stdcppd.lib ixtnsd40.lib dbase32d.lib ctl3d32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /debug /machine:I386 /nodefaultlib:"libcmt.lib" /stub:"d:\triasdev\dbaseext\rights.exe" /out:"d:\trias\trias200\dbasx32d.ext" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=tfrm32d.lib cont32d.lib stdcppd.lib ixtnsd40.lib dbase32d.lib\
 ctl3d32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)/dbasx32d.pdb" /debug\
 /machine:I386 /nodefaultlib:"libcmt.lib" /def:".\DBASEEXT.DEF"\
 /stub:"d:\triasdev\dbaseext\rights.exe" /out:"d:\trias\trias200\dbasx32d.ext"\
 /implib:"$(OUTDIR)/dbasx32d.lib" /SUBSYSTEM:windows,4.0 
DEF_FILE= \
	".\DBASEEXT.DEF"
LINK32_OBJS= \
	"$(INTDIR)\AFNAMEL.OBJ" \
	"$(INTDIR)\DBASE.OBJ" \
	"$(INTDIR)\DBASEEXT.OBJ" \
	"$(INTDIR)\DBASEEXT.res" \
	"$(INTDIR)\DBASEOPF.OBJ" \
	"$(INTDIR)\EXTTABL.OBJ" \
	"$(INTDIR)\GIZMOBAR.OBJ" \
	"$(INTDIR)\PHEADER.OBJ" \
	"$(INTDIR)\TABLENAM.OBJ" \
	"$(INTDIR)\V_DBASE.OBJ" \
	"$(INTDIR)\V_DBASE1.OBJ" \
	"$(INTDIR)\V_MEMOFD.OBJ"

"..\..\trias\trias200\dbasx32d.ext" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Dbaseext - Win32 Release"
# Name "Dbaseext - Win32 Debug"

!IF  "$(CFG)" == "Dbaseext - Win32 Release"

!ELSEIF  "$(CFG)" == "Dbaseext - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\V_DBASE1.CXX

!IF  "$(CFG)" == "Dbaseext - Win32 Release"

DEP_CPP_V_DBA=\
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
	".\Afnamel.hxx"\
	".\Dbaseext.hr"\
	".\Exttabl.hxx"\
	".\Gizmobar.hxx"\
	".\Pheader.h"\
	".\V_dbase.htp"\
	".\V_dbase.hxx"\
	".\V_memofd.hxx"\
	".\Waitcur.hxx"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Bttncur.h"\
	{$(INCLUDE)}"\Clipbrd.hxx"\
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
	{$(INCLUDE)}"\Dbaserel.hxx"\
	{$(INCLUDE)}"\Dbasprof.hxx"\
	{$(INCLUDE)}"\Dbliste.hxx"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Gizmobar.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
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
	{$(INCLUDE)}"\Print.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\Resstrg.h"\
	{$(INCLUDE)}"\Stddlg.hxx"\
	{$(INCLUDE)}"\Strdup.hxx"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_V_DBA=\
	".\win16\dbaseext.h"\
	
# ADD CPP /Yu"pheader.h"

"$(INTDIR)\V_DBASE1.OBJ" : $(SOURCE) $(DEP_CPP_V_DBA) "$(INTDIR)"\
 "$(INTDIR)\Dbaseext.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "DLL"\
 /D "__XT" /D "__CV__" /D "STRICT" /D "MSWIND" /D "MDX" /D "WINDOWS" /D\
 "__DEXPROCS" /Fp"$(INTDIR)/Dbaseext.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbaseext - Win32 Debug"

DEP_CPP_V_DBA=\
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
	".\Afnamel.hxx"\
	".\Dbaseext.hr"\
	".\Exttabl.hxx"\
	".\Gizmobar.hxx"\
	".\Pheader.h"\
	".\V_dbase.htp"\
	".\V_dbase.hxx"\
	".\V_memofd.hxx"\
	".\Waitcur.hxx"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Bttncur.h"\
	{$(INCLUDE)}"\Clipbrd.hxx"\
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
	{$(INCLUDE)}"\Dbaserel.hxx"\
	{$(INCLUDE)}"\Dbasprof.hxx"\
	{$(INCLUDE)}"\Dbliste.hxx"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Gizmobar.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
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
	{$(INCLUDE)}"\Print.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\Resstrg.h"\
	{$(INCLUDE)}"\Stddlg.hxx"\
	{$(INCLUDE)}"\Strdup.hxx"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_V_DBA=\
	".\win16\dbaseext.h"\
	

"$(INTDIR)\V_DBASE1.OBJ" : $(SOURCE) $(DEP_CPP_V_DBA) "$(INTDIR)"\
 "$(INTDIR)\Dbaseext.pch"
   $(CPP) /nologo /MDd /W3 /WX /Gm /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "DLL" /D "__XT" /D "__CV__" /D "STRICT" /D "MSWIND" /D "MDX" /D "WINDOWS" /D\
 "__DEXPROCS" /Fp"$(INTDIR)/Dbaseext.pch" /Yu"pheader.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GIZMOBAR.CXX

!IF  "$(CFG)" == "Dbaseext - Win32 Release"

DEP_CPP_GIZMO=\
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
	".\Gizmobar.htp"\
	".\Gizmobar.hxx"\
	".\Pheader.h"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Bttncur.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Crcb.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\Gizmobar.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
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
	{$(INCLUDE)}"\Print.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Yxvals.h"\
	
# ADD CPP /Yu"pheader.h"

"$(INTDIR)\GIZMOBAR.OBJ" : $(SOURCE) $(DEP_CPP_GIZMO) "$(INTDIR)"\
 "$(INTDIR)\Dbaseext.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "DLL"\
 /D "__XT" /D "__CV__" /D "STRICT" /D "MSWIND" /D "MDX" /D "WINDOWS" /D\
 "__DEXPROCS" /Fp"$(INTDIR)/Dbaseext.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbaseext - Win32 Debug"

DEP_CPP_GIZMO=\
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
	".\Gizmobar.htp"\
	".\Gizmobar.hxx"\
	".\Pheader.h"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Bttncur.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Crcb.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\Gizmobar.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
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
	{$(INCLUDE)}"\Print.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Yxvals.h"\
	

"$(INTDIR)\GIZMOBAR.OBJ" : $(SOURCE) $(DEP_CPP_GIZMO) "$(INTDIR)"\
 "$(INTDIR)\Dbaseext.pch"
   $(CPP) /nologo /MDd /W3 /WX /Gm /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "DLL" /D "__XT" /D "__CV__" /D "STRICT" /D "MSWIND" /D "MDX" /D "WINDOWS" /D\
 "__DEXPROCS" /Fp"$(INTDIR)/Dbaseext.pch" /Yu"pheader.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\AFNAMEL.CXX

!IF  "$(CFG)" == "Dbaseext - Win32 Release"

DEP_CPP_AFNAM=\
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
	".\Afnamel.hxx"\
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
	{$(INCLUDE)}"\Dbasprof.hxx"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
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
	{$(INCLUDE)}"\Print.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Yxvals.h"\
	
# ADD CPP /Yu"pheader.h"

"$(INTDIR)\AFNAMEL.OBJ" : $(SOURCE) $(DEP_CPP_AFNAM) "$(INTDIR)"\
 "$(INTDIR)\Dbaseext.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "DLL"\
 /D "__XT" /D "__CV__" /D "STRICT" /D "MSWIND" /D "MDX" /D "WINDOWS" /D\
 "__DEXPROCS" /Fp"$(INTDIR)/Dbaseext.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbaseext - Win32 Debug"

DEP_CPP_AFNAM=\
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
	".\Afnamel.hxx"\
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
	{$(INCLUDE)}"\Dbasprof.hxx"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
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
	{$(INCLUDE)}"\Print.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Yxvals.h"\
	

"$(INTDIR)\AFNAMEL.OBJ" : $(SOURCE) $(DEP_CPP_AFNAM) "$(INTDIR)"\
 "$(INTDIR)\Dbaseext.pch"
   $(CPP) /nologo /MDd /W3 /WX /Gm /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "DLL" /D "__XT" /D "__CV__" /D "STRICT" /D "MSWIND" /D "MDX" /D "WINDOWS" /D\
 "__DEXPROCS" /Fp"$(INTDIR)/Dbaseext.pch" /Yu"pheader.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\V_MEMOFD.CXX

!IF  "$(CFG)" == "Dbaseext - Win32 Release"

DEP_CPP_V_MEM=\
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
	".\Dbaseext.hr"\
	".\Pheader.h"\
	".\V_memofd.htp"\
	".\V_memofd.hxx"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Crcb.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
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
	{$(INCLUDE)}"\Print.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_V_MEM=\
	".\win16\dbaseext.h"\
	
# ADD CPP /Yu"pheader.h"

"$(INTDIR)\V_MEMOFD.OBJ" : $(SOURCE) $(DEP_CPP_V_MEM) "$(INTDIR)"\
 "$(INTDIR)\Dbaseext.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "DLL"\
 /D "__XT" /D "__CV__" /D "STRICT" /D "MSWIND" /D "MDX" /D "WINDOWS" /D\
 "__DEXPROCS" /Fp"$(INTDIR)/Dbaseext.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbaseext - Win32 Debug"

DEP_CPP_V_MEM=\
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
	".\Dbaseext.hr"\
	".\Pheader.h"\
	".\V_memofd.htp"\
	".\V_memofd.hxx"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Crcb.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
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
	{$(INCLUDE)}"\Print.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_V_MEM=\
	".\win16\dbaseext.h"\
	
# ADD CPP /GX-
# SUBTRACT CPP /Fr

"$(INTDIR)\V_MEMOFD.OBJ" : $(SOURCE) $(DEP_CPP_V_MEM) "$(INTDIR)"\
 "$(INTDIR)\Dbaseext.pch"
   $(CPP) /nologo /MDd /W3 /WX /Gm /GX- /Zi /Od /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "DLL" /D "__XT" /D "__CV__" /D "STRICT" /D "MSWIND" /D "MDX" /D\
 "WINDOWS" /D "__DEXPROCS" /Fp"$(INTDIR)/Dbaseext.pch" /Yu"pheader.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DBASE.CXX

!IF  "$(CFG)" == "Dbaseext - Win32 Release"

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
	".\Dbase.htp"\
	".\Dbase.hxx"\
	".\Exttabl.hxx"\
	".\Pheader.h"\
	".\V_dbase.hxx"\
	".\V_memofd.hxx"\
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
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
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
	{$(INCLUDE)}"\Print.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Yxvals.h"\
	
# ADD CPP /Yu"pheader.h"

"$(INTDIR)\DBASE.OBJ" : $(SOURCE) $(DEP_CPP_DBASE) "$(INTDIR)"\
 "$(INTDIR)\Dbaseext.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "DLL"\
 /D "__XT" /D "__CV__" /D "STRICT" /D "MSWIND" /D "MDX" /D "WINDOWS" /D\
 "__DEXPROCS" /Fp"$(INTDIR)/Dbaseext.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbaseext - Win32 Debug"

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
	".\Dbase.htp"\
	".\Dbase.hxx"\
	".\Exttabl.hxx"\
	".\Pheader.h"\
	".\V_dbase.hxx"\
	".\V_memofd.hxx"\
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
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
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
	{$(INCLUDE)}"\Print.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Yxvals.h"\
	

"$(INTDIR)\DBASE.OBJ" : $(SOURCE) $(DEP_CPP_DBASE) "$(INTDIR)"\
 "$(INTDIR)\Dbaseext.pch"
   $(CPP) /nologo /MDd /W3 /WX /Gm /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "DLL" /D "__XT" /D "__CV__" /D "STRICT" /D "MSWIND" /D "MDX" /D "WINDOWS" /D\
 "__DEXPROCS" /Fp"$(INTDIR)/Dbaseext.pch" /Yu"pheader.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\V_DBASE.CXX

!IF  "$(CFG)" == "Dbaseext - Win32 Release"

DEP_CPP_V_DBAS=\
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
	".\Afnamel.hxx"\
	".\Dbase.hxx"\
	".\Dbaseext.hr"\
	".\Dbaseext.hxx"\
	".\Exttabl.hxx"\
	".\Gizmobar.hxx"\
	".\Pheader.h"\
	".\V_dbase.htp"\
	".\V_dbase.hxx"\
	".\V_memofd.hxx"\
	".\Waitcur.hxx"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Bttncur.h"\
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
	{$(INCLUDE)}"\Dbaserel.hxx"\
	{$(INCLUDE)}"\Dbasprof.hxx"\
	{$(INCLUDE)}"\Dbliste.hxx"\
	{$(INCLUDE)}"\Dbtools.hxx"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Gizmobar.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
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
	{$(INCLUDE)}"\Print.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\Resstrg.h"\
	{$(INCLUDE)}"\Strdup.hxx"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnprop.hxx"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_V_DBAS=\
	".\win16\dbaseext.h"\
	
# ADD CPP /Yu"pheader.h"

"$(INTDIR)\V_DBASE.OBJ" : $(SOURCE) $(DEP_CPP_V_DBAS) "$(INTDIR)"\
 "$(INTDIR)\Dbaseext.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "DLL"\
 /D "__XT" /D "__CV__" /D "STRICT" /D "MSWIND" /D "MDX" /D "WINDOWS" /D\
 "__DEXPROCS" /Fp"$(INTDIR)/Dbaseext.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbaseext - Win32 Debug"

DEP_CPP_V_DBAS=\
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
	".\Afnamel.hxx"\
	".\Dbase.hxx"\
	".\Dbaseext.hr"\
	".\Dbaseext.hxx"\
	".\Exttabl.hxx"\
	".\Gizmobar.hxx"\
	".\Pheader.h"\
	".\V_dbase.htp"\
	".\V_dbase.hxx"\
	".\V_memofd.hxx"\
	".\Waitcur.hxx"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Bttncur.h"\
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
	{$(INCLUDE)}"\Dbaserel.hxx"\
	{$(INCLUDE)}"\Dbasprof.hxx"\
	{$(INCLUDE)}"\Dbliste.hxx"\
	{$(INCLUDE)}"\Dbtools.hxx"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Gizmobar.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
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
	{$(INCLUDE)}"\Print.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\Resstrg.h"\
	{$(INCLUDE)}"\Strdup.hxx"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnprop.hxx"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_V_DBAS=\
	".\win16\dbaseext.h"\
	

"$(INTDIR)\V_DBASE.OBJ" : $(SOURCE) $(DEP_CPP_V_DBAS) "$(INTDIR)"\
 "$(INTDIR)\Dbaseext.pch"
   $(CPP) /nologo /MDd /W3 /WX /Gm /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "DLL" /D "__XT" /D "__CV__" /D "STRICT" /D "MSWIND" /D "MDX" /D "WINDOWS" /D\
 "__DEXPROCS" /Fp"$(INTDIR)/Dbaseext.pch" /Yu"pheader.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DBASEOPF.CXX

!IF  "$(CFG)" == "Dbaseext - Win32 Release"

DEP_CPP_DBASEO=\
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
	".\Dbase.hxx"\
	".\Dbaseext.hr"\
	".\Dbaseext.hxx"\
	".\Dbaseopf.htp"\
	".\Pheader.h"\
	".\Tablenam.hxx"\
	".\Waitcur.hxx"\
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
	{$(INCLUDE)}"\Dbaserel.hxx"\
	{$(INCLUDE)}"\Dbasprof.hxx"\
	{$(INCLUDE)}"\Dbliste.hxx"\
	{$(INCLUDE)}"\Dbtools.hxx"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
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
	{$(INCLUDE)}"\Print.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\Resstrg.h"\
	{$(INCLUDE)}"\Strdup.hxx"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnprop.hxx"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_DBASEO=\
	".\win16\dbaseext.h"\
	
# ADD CPP /Yu"pheader.h"

"$(INTDIR)\DBASEOPF.OBJ" : $(SOURCE) $(DEP_CPP_DBASEO) "$(INTDIR)"\
 "$(INTDIR)\Dbaseext.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "DLL"\
 /D "__XT" /D "__CV__" /D "STRICT" /D "MSWIND" /D "MDX" /D "WINDOWS" /D\
 "__DEXPROCS" /Fp"$(INTDIR)/Dbaseext.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbaseext - Win32 Debug"

DEP_CPP_DBASEO=\
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
	".\Dbase.hxx"\
	".\Dbaseext.hr"\
	".\Dbaseext.hxx"\
	".\Dbaseopf.htp"\
	".\Pheader.h"\
	".\Tablenam.hxx"\
	".\Waitcur.hxx"\
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
	{$(INCLUDE)}"\Dbaserel.hxx"\
	{$(INCLUDE)}"\Dbasprof.hxx"\
	{$(INCLUDE)}"\Dbliste.hxx"\
	{$(INCLUDE)}"\Dbtools.hxx"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
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
	{$(INCLUDE)}"\Print.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\Resstrg.h"\
	{$(INCLUDE)}"\Strdup.hxx"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnprop.hxx"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_DBASEO=\
	".\win16\dbaseext.h"\
	

"$(INTDIR)\DBASEOPF.OBJ" : $(SOURCE) $(DEP_CPP_DBASEO) "$(INTDIR)"\
 "$(INTDIR)\Dbaseext.pch"
   $(CPP) /nologo /MDd /W3 /WX /Gm /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "DLL" /D "__XT" /D "__CV__" /D "STRICT" /D "MSWIND" /D "MDX" /D "WINDOWS" /D\
 "__DEXPROCS" /Fp"$(INTDIR)/Dbaseext.pch" /Yu"pheader.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DBASEEXT.DEF

!IF  "$(CFG)" == "Dbaseext - Win32 Release"

!ELSEIF  "$(CFG)" == "Dbaseext - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\EXTTABL.CXX

!IF  "$(CFG)" == "Dbaseext - Win32 Release"

DEP_CPP_EXTTA=\
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
	".\Exttabl.htp"\
	".\Exttabl.hxx"\
	".\Pheader.h"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Crcb.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
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
	{$(INCLUDE)}"\Print.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Yxvals.h"\
	
# ADD CPP /Yu"pheader.h"

"$(INTDIR)\EXTTABL.OBJ" : $(SOURCE) $(DEP_CPP_EXTTA) "$(INTDIR)"\
 "$(INTDIR)\Dbaseext.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "DLL"\
 /D "__XT" /D "__CV__" /D "STRICT" /D "MSWIND" /D "MDX" /D "WINDOWS" /D\
 "__DEXPROCS" /Fp"$(INTDIR)/Dbaseext.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbaseext - Win32 Debug"

DEP_CPP_EXTTA=\
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
	".\Exttabl.htp"\
	".\Exttabl.hxx"\
	".\Pheader.h"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Crcb.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
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
	{$(INCLUDE)}"\Print.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Yxvals.h"\
	

"$(INTDIR)\EXTTABL.OBJ" : $(SOURCE) $(DEP_CPP_EXTTA) "$(INTDIR)"\
 "$(INTDIR)\Dbaseext.pch"
   $(CPP) /nologo /MDd /W3 /WX /Gm /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "DLL" /D "__XT" /D "__CV__" /D "STRICT" /D "MSWIND" /D "MDX" /D "WINDOWS" /D\
 "__DEXPROCS" /Fp"$(INTDIR)/Dbaseext.pch" /Yu"pheader.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DBASEEXT.RC
DEP_RSC_DBASEE=\
	".\DBASEEXT.RCV"\
	".\DBPOS120.BMP"\
	".\DBPOS72.BMP"\
	".\DBPOS96.BMP"\
	{$(INCLUDE)}"\Resstrg.h"\
	

"$(INTDIR)\DBASEEXT.res" : $(SOURCE) $(DEP_RSC_DBASEE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DBASEEXT.CXX

!IF  "$(CFG)" == "Dbaseext - Win32 Release"

DEP_CPP_DBASEEX=\
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
	".\Dbase.hxx"\
	".\Dbaseext.hr"\
	".\Dbaseext.htp"\
	".\Dbaseext.hxx"\
	".\Dbasguid.h"\
	".\Pheader.h"\
	".\Vers32.h"\
	".\Version.h"\
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
	{$(INCLUDE)}"\Dbaserel.hxx"\
	{$(INCLUDE)}"\Dbasprof.hxx"\
	{$(INCLUDE)}"\Dbtools.hxx"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
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
	{$(INCLUDE)}"\Print.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\Resstrg.h"\
	{$(INCLUDE)}"\Strdup.hxx"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\xtsnprop.hxx"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_DBASEEX=\
	".\win16\dbaseext.h"\
	".\win16\vers16.h"\
	
# ADD CPP /Yu"pheader.h"

"$(INTDIR)\DBASEEXT.OBJ" : $(SOURCE) $(DEP_CPP_DBASEEX) "$(INTDIR)"\
 "$(INTDIR)\Dbaseext.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "DLL"\
 /D "__XT" /D "__CV__" /D "STRICT" /D "MSWIND" /D "MDX" /D "WINDOWS" /D\
 "__DEXPROCS" /Fp"$(INTDIR)/Dbaseext.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbaseext - Win32 Debug"

DEP_CPP_DBASEEX=\
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
	".\Dbase.hxx"\
	".\Dbaseext.hr"\
	".\Dbaseext.htp"\
	".\Dbaseext.hxx"\
	".\Dbasguid.h"\
	".\Pheader.h"\
	".\Vers32.h"\
	".\Version.h"\
	".\win16\vers16.h"\
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
	{$(INCLUDE)}"\Dbaserel.hxx"\
	{$(INCLUDE)}"\Dbasprof.hxx"\
	{$(INCLUDE)}"\Dbtools.hxx"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
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
	{$(INCLUDE)}"\Print.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\Resstrg.h"\
	{$(INCLUDE)}"\Strdup.hxx"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\xtsnprop.hxx"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_DBASEEX=\
	".\win16\dbaseext.h"\
	

"$(INTDIR)\DBASEEXT.OBJ" : $(SOURCE) $(DEP_CPP_DBASEEX) "$(INTDIR)"\
 "$(INTDIR)\Dbaseext.pch"
   $(CPP) /nologo /MDd /W3 /WX /Gm /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "DLL" /D "__XT" /D "__CV__" /D "STRICT" /D "MSWIND" /D "MDX" /D "WINDOWS" /D\
 "__DEXPROCS" /Fp"$(INTDIR)/Dbaseext.pch" /Yu"pheader.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PHEADER.CXX

!IF  "$(CFG)" == "Dbaseext - Win32 Release"

DEP_CPP_PHEAD=\
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
	{$(INCLUDE)}"\Crcb.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
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
	{$(INCLUDE)}"\Print.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Yxvals.h"\
	
# ADD CPP /Yc"pheader.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "DLL"\
 /D "__XT" /D "__CV__" /D "STRICT" /D "MSWIND" /D "MDX" /D "WINDOWS" /D\
 "__DEXPROCS" /Fp"$(INTDIR)/Dbaseext.pch" /Yc"pheader.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\PHEADER.OBJ" : $(SOURCE) $(DEP_CPP_PHEAD) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Dbaseext.pch" : $(SOURCE) $(DEP_CPP_PHEAD) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Dbaseext - Win32 Debug"

DEP_CPP_PHEAD=\
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
	{$(INCLUDE)}"\Crcb.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
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
	{$(INCLUDE)}"\Print.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Yxvals.h"\
	
# ADD CPP /GX- /Yc"pheader.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX- /Zi /Od /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "DLL" /D "__XT" /D "__CV__" /D "STRICT" /D "MSWIND" /D "MDX" /D\
 "WINDOWS" /D "__DEXPROCS" /Fp"$(INTDIR)/Dbaseext.pch" /Yc"pheader.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\PHEADER.OBJ" : $(SOURCE) $(DEP_CPP_PHEAD) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Dbaseext.pch" : $(SOURCE) $(DEP_CPP_PHEAD) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TABLENAM.CXX

!IF  "$(CFG)" == "Dbaseext - Win32 Release"

DEP_CPP_TABLE=\
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
	".\Tablenam.hxx"\
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
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
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
	{$(INCLUDE)}"\Print.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Yxvals.h"\
	
# ADD CPP /Yu"pheader.h"

"$(INTDIR)\TABLENAM.OBJ" : $(SOURCE) $(DEP_CPP_TABLE) "$(INTDIR)"\
 "$(INTDIR)\Dbaseext.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "DLL"\
 /D "__XT" /D "__CV__" /D "STRICT" /D "MSWIND" /D "MDX" /D "WINDOWS" /D\
 "__DEXPROCS" /Fp"$(INTDIR)/Dbaseext.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbaseext - Win32 Debug"

DEP_CPP_TABLE=\
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
	".\Tablenam.hxx"\
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
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
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
	{$(INCLUDE)}"\Print.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Yxvals.h"\
	

"$(INTDIR)\TABLENAM.OBJ" : $(SOURCE) $(DEP_CPP_TABLE) "$(INTDIR)"\
 "$(INTDIR)\Dbaseext.pch"
   $(CPP) /nologo /MDd /W3 /WX /Gm /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "DLL" /D "__XT" /D "__CV__" /D "STRICT" /D "MSWIND" /D "MDX" /D "WINDOWS" /D\
 "__DEXPROCS" /Fp"$(INTDIR)/Dbaseext.pch" /Yu"pheader.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE)


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
