# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=Dxfimp - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Dxfimp - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Dxfimp - Win32 Release" && "$(CFG)" != "Dxfimp - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "DXFIMP.MAK" CFG="Dxfimp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Dxfimp - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Dxfimp - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "Dxfimp - Win32 Debug"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "Dxfimp - Win32 Release"

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

ALL : "..\..\..\trias\trias\dxfimp.ext"

CLEAN : 
	-@erase "$(INTDIR)\block.obj"
	-@erase "$(INTDIR)\BOGEN.OBJ"
	-@erase "$(INTDIR)\DGEO_OBJ.OBJ"
	-@erase "$(INTDIR)\DXFIMP.OBJ"
	-@erase "$(INTDIR)\DXFIMP.pch"
	-@erase "$(INTDIR)\DXFIMP.res"
	-@erase "$(INTDIR)\DXFIMPIF.OBJ"
	-@erase "$(INTDIR)\DXFLX.OBJ"
	-@erase "$(INTDIR)\DXFY.OBJ"
	-@erase "$(INTDIR)\HEADER.OBJ"
	-@erase "$(INTDIR)\HELPTEXT.OBJ"
	-@erase "$(INTDIR)\IMPRESLT.OBJ"
	-@erase "$(INTDIR)\layers.obj"
	-@erase "$(INTDIR)\Licenz.obj"
	-@erase "$(INTDIR)\MERKMAL.OBJ"
	-@erase "$(INTDIR)\NUMEDIT.OBJ"
	-@erase "$(INTDIR)\OPTPARAM.OBJ"
	-@erase "$(INTDIR)\OPTPRDLG.OBJ"
	-@erase "$(INTDIR)\PHEADER.OBJ"
	-@erase "$(INTDIR)\PUNKTLI.OBJ"
	-@erase "$(INTDIR)\REALEDIT.OBJ"
	-@erase "$(INTDIR)\RECHSTAT.OBJ"
	-@erase "$(INTDIR)\STRUTIL.OBJ"
	-@erase "$(INTDIR)\TMERKMAL.OBJ"
	-@erase "$(INTDIR)\TOOLS.OBJ"
	-@erase "$(OUTDIR)\dxfimp.exp"
	-@erase "$(OUTDIR)\dxfimp.lib"
	-@erase "..\..\..\trias\trias\dxfimp.ext"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(OUTDIR)/DXFIMP.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /O2 /I "\triasdev.mvc\inc.hpp" /I "\triasdev.mvc\inc.hpp\inc" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "DLL" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "__CV__" /Yu"pheader.hpp" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W3 /WX /GX /O2 /I "\triasdev.mvc\inc.hpp" /I\
 "\triasdev.mvc\inc.hpp\inc" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D\
 "DLL" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "__CV__"\
 /Fp"$(INTDIR)/DXFIMP.pch" /Yu"pheader.hpp" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\WinRel/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/DXFIMP.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/DXFIMP.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ixtnsr40.lib stdcppr.lib tfrmwork.lib cont32r.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386 /stub:"rights.exe" /out:"d:\trias\trias\dxfimp.ext"
LINK32_FLAGS=ixtnsr40.lib stdcppr.lib tfrmwork.lib cont32r.lib kernel32.lib\
 user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib\
 ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo\
 /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)/dxfimp.pdb"\
 /machine:I386 /def:".\DXFIMP.DEF" /stub:"rights.exe"\
 /out:"d:\trias\trias\dxfimp.ext" /implib:"$(OUTDIR)/dxfimp.lib" 
DEF_FILE= \
	".\DXFIMP.DEF"
LINK32_OBJS= \
	"$(INTDIR)\block.obj" \
	"$(INTDIR)\BOGEN.OBJ" \
	"$(INTDIR)\DGEO_OBJ.OBJ" \
	"$(INTDIR)\DXFIMP.OBJ" \
	"$(INTDIR)\DXFIMP.res" \
	"$(INTDIR)\DXFIMPIF.OBJ" \
	"$(INTDIR)\DXFLX.OBJ" \
	"$(INTDIR)\DXFY.OBJ" \
	"$(INTDIR)\HEADER.OBJ" \
	"$(INTDIR)\HELPTEXT.OBJ" \
	"$(INTDIR)\IMPRESLT.OBJ" \
	"$(INTDIR)\layers.obj" \
	"$(INTDIR)\Licenz.obj" \
	"$(INTDIR)\MERKMAL.OBJ" \
	"$(INTDIR)\NUMEDIT.OBJ" \
	"$(INTDIR)\OPTPARAM.OBJ" \
	"$(INTDIR)\OPTPRDLG.OBJ" \
	"$(INTDIR)\PHEADER.OBJ" \
	"$(INTDIR)\PUNKTLI.OBJ" \
	"$(INTDIR)\REALEDIT.OBJ" \
	"$(INTDIR)\RECHSTAT.OBJ" \
	"$(INTDIR)\STRUTIL.OBJ" \
	"$(INTDIR)\TMERKMAL.OBJ" \
	"$(INTDIR)\TOOLS.OBJ"

"..\..\..\trias\trias\dxfimp.ext" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Dxfimp - Win32 Debug"

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

ALL : "..\..\..\trias\trias200\dxfimpd.ext" "$(OUTDIR)\DXFIMP.bsc"

CLEAN : 
	-@erase "$(INTDIR)\block.obj"
	-@erase "$(INTDIR)\block.sbr"
	-@erase "$(INTDIR)\BOGEN.OBJ"
	-@erase "$(INTDIR)\BOGEN.SBR"
	-@erase "$(INTDIR)\DGEO_OBJ.OBJ"
	-@erase "$(INTDIR)\DGEO_OBJ.SBR"
	-@erase "$(INTDIR)\DXFIMP.OBJ"
	-@erase "$(INTDIR)\DXFIMP.pch"
	-@erase "$(INTDIR)\DXFIMP.res"
	-@erase "$(INTDIR)\DXFIMP.SBR"
	-@erase "$(INTDIR)\DXFIMPIF.OBJ"
	-@erase "$(INTDIR)\DXFIMPIF.SBR"
	-@erase "$(INTDIR)\DXFLX.OBJ"
	-@erase "$(INTDIR)\DXFLX.SBR"
	-@erase "$(INTDIR)\DXFY.OBJ"
	-@erase "$(INTDIR)\DXFY.SBR"
	-@erase "$(INTDIR)\HEADER.OBJ"
	-@erase "$(INTDIR)\HEADER.SBR"
	-@erase "$(INTDIR)\HELPTEXT.OBJ"
	-@erase "$(INTDIR)\HELPTEXT.SBR"
	-@erase "$(INTDIR)\IMPRESLT.OBJ"
	-@erase "$(INTDIR)\IMPRESLT.SBR"
	-@erase "$(INTDIR)\layers.obj"
	-@erase "$(INTDIR)\layers.sbr"
	-@erase "$(INTDIR)\Licenz.obj"
	-@erase "$(INTDIR)\Licenz.sbr"
	-@erase "$(INTDIR)\MERKMAL.OBJ"
	-@erase "$(INTDIR)\MERKMAL.SBR"
	-@erase "$(INTDIR)\NUMEDIT.OBJ"
	-@erase "$(INTDIR)\NUMEDIT.SBR"
	-@erase "$(INTDIR)\OPTPARAM.OBJ"
	-@erase "$(INTDIR)\OPTPARAM.SBR"
	-@erase "$(INTDIR)\OPTPRDLG.OBJ"
	-@erase "$(INTDIR)\OPTPRDLG.SBR"
	-@erase "$(INTDIR)\PHEADER.OBJ"
	-@erase "$(INTDIR)\PHEADER.SBR"
	-@erase "$(INTDIR)\PUNKTLI.OBJ"
	-@erase "$(INTDIR)\PUNKTLI.SBR"
	-@erase "$(INTDIR)\REALEDIT.OBJ"
	-@erase "$(INTDIR)\REALEDIT.SBR"
	-@erase "$(INTDIR)\RECHSTAT.OBJ"
	-@erase "$(INTDIR)\RECHSTAT.SBR"
	-@erase "$(INTDIR)\STRUTIL.OBJ"
	-@erase "$(INTDIR)\STRUTIL.SBR"
	-@erase "$(INTDIR)\TMERKMAL.OBJ"
	-@erase "$(INTDIR)\TMERKMAL.SBR"
	-@erase "$(INTDIR)\TOOLS.OBJ"
	-@erase "$(INTDIR)\TOOLS.SBR"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\DXFIMP.bsc"
	-@erase "$(OUTDIR)\dxfimpd.exp"
	-@erase "$(OUTDIR)\dxfimpd.lib"
	-@erase "$(OUTDIR)\dxfimpd.pdb"
	-@erase "..\..\..\trias\trias200\dxfimpd.ext"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(OUTDIR)/DXFIMP.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /I "\triasdev.mvc\inc.hpp" /I "\triasdev.mvc\inc.hpp\inc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "DLL" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "__CV__" /Fr /Yu"pheader.hpp" /c
CPP_PROJ=/nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /I "\triasdev.mvc\inc.hpp"\
 /I "\triasdev.mvc\inc.hpp\inc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "STRICT"\
 /D "DLL" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "__CV__" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/DXFIMP.pch" /Yu"pheader.hpp" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\WinDebug/
CPP_SBRS=.\WinDebug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/DXFIMP.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/DXFIMP.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\block.sbr" \
	"$(INTDIR)\BOGEN.SBR" \
	"$(INTDIR)\DGEO_OBJ.SBR" \
	"$(INTDIR)\DXFIMP.SBR" \
	"$(INTDIR)\DXFIMPIF.SBR" \
	"$(INTDIR)\DXFLX.SBR" \
	"$(INTDIR)\DXFY.SBR" \
	"$(INTDIR)\HEADER.SBR" \
	"$(INTDIR)\HELPTEXT.SBR" \
	"$(INTDIR)\IMPRESLT.SBR" \
	"$(INTDIR)\layers.sbr" \
	"$(INTDIR)\Licenz.sbr" \
	"$(INTDIR)\MERKMAL.SBR" \
	"$(INTDIR)\NUMEDIT.SBR" \
	"$(INTDIR)\OPTPARAM.SBR" \
	"$(INTDIR)\OPTPRDLG.SBR" \
	"$(INTDIR)\PHEADER.SBR" \
	"$(INTDIR)\PUNKTLI.SBR" \
	"$(INTDIR)\REALEDIT.SBR" \
	"$(INTDIR)\RECHSTAT.SBR" \
	"$(INTDIR)\STRUTIL.SBR" \
	"$(INTDIR)\TMERKMAL.SBR" \
	"$(INTDIR)\TOOLS.SBR"

"$(OUTDIR)\DXFIMP.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 tfrm32d.lib stdcppd.lib ixtnsd40.lib cont32d.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /debug /machine:I386 /nodefaultlib:"ocs30d.lib" /nodefaultlib:"libcmt.lib" /stub:"rights.exe" /out:"d:\trias\trias200\dxfimpd.ext" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=tfrm32d.lib stdcppd.lib ixtnsd40.lib cont32d.lib kernel32.lib\
 user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib\
 ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll\
 /incremental:no /pdb:"$(OUTDIR)/dxfimpd.pdb" /debug /machine:I386\
 /nodefaultlib:"ocs30d.lib" /nodefaultlib:"libcmt.lib" /def:".\DXFIMP.DEF"\
 /stub:"rights.exe" /out:"d:\trias\trias200\dxfimpd.ext"\
 /implib:"$(OUTDIR)/dxfimpd.lib" /SUBSYSTEM:windows,4.0 
DEF_FILE= \
	".\DXFIMP.DEF"
LINK32_OBJS= \
	"$(INTDIR)\block.obj" \
	"$(INTDIR)\BOGEN.OBJ" \
	"$(INTDIR)\DGEO_OBJ.OBJ" \
	"$(INTDIR)\DXFIMP.OBJ" \
	"$(INTDIR)\DXFIMP.res" \
	"$(INTDIR)\DXFIMPIF.OBJ" \
	"$(INTDIR)\DXFLX.OBJ" \
	"$(INTDIR)\DXFY.OBJ" \
	"$(INTDIR)\HEADER.OBJ" \
	"$(INTDIR)\HELPTEXT.OBJ" \
	"$(INTDIR)\IMPRESLT.OBJ" \
	"$(INTDIR)\layers.obj" \
	"$(INTDIR)\Licenz.obj" \
	"$(INTDIR)\MERKMAL.OBJ" \
	"$(INTDIR)\NUMEDIT.OBJ" \
	"$(INTDIR)\OPTPARAM.OBJ" \
	"$(INTDIR)\OPTPRDLG.OBJ" \
	"$(INTDIR)\PHEADER.OBJ" \
	"$(INTDIR)\PUNKTLI.OBJ" \
	"$(INTDIR)\REALEDIT.OBJ" \
	"$(INTDIR)\RECHSTAT.OBJ" \
	"$(INTDIR)\STRUTIL.OBJ" \
	"$(INTDIR)\TMERKMAL.OBJ" \
	"$(INTDIR)\TOOLS.OBJ"

"..\..\..\trias\trias200\dxfimpd.ext" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Dxfimp - Win32 Release"
# Name "Dxfimp - Win32 Debug"

!IF  "$(CFG)" == "Dxfimp - Win32 Release"

!ELSEIF  "$(CFG)" == "Dxfimp - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\PHEADER.CPP

!IF  "$(CFG)" == "Dxfimp - Win32 Release"

DEP_CPP_PHEAD=\
	"..\..\..\Cv32.mvc\Include\gc.h"\
	".\Dxfimp.hpp"\
	".\Dxfimp.hr"\
	".\DxfImpConfig.h"\
	".\Dxfimpif.hpp"\
	".\Optparam.hpp"\
	".\Pheader.hpp"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\hpp\errcodesodbc.hxx"\
	{$(INCLUDE)}"\hpp\protos.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\ospace\sync\counting.h"\
	{$(INCLUDE)}"\ospace\sync\counting.ipp"\
	{$(INCLUDE)}"\ospace\sync\critical.h"\
	{$(INCLUDE)}"\ospace\sync\critical.ipp"\
	{$(INCLUDE)}"\ospace\sync\eventsem.h"\
	{$(INCLUDE)}"\ospace\sync\lock.h"\
	{$(INCLUDE)}"\ospace\sync\lock.ipp"\
	{$(INCLUDE)}"\ospace\sync\monitor.h"\
	{$(INCLUDE)}"\ospace\sync\monitor.ipp"\
	{$(INCLUDE)}"\ospace\sync\mutex.h"\
	{$(INCLUDE)}"\ospace\sync\mutex.ipp"\
	{$(INCLUDE)}"\ospace\sync\rfifo.h"\
	{$(INCLUDE)}"\ospace\sync\rpriority.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.ipp"\
	{$(INCLUDE)}"\ospace\sync\rwsem.h"\
	{$(INCLUDE)}"\ospace\sync\rwsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\sentinel.h"\
	{$(INCLUDE)}"\ospace\sync\sentinel.ipp"\
	{$(INCLUDE)}"\ospace\sync\sfifo.h"\
	{$(INCLUDE)}"\ospace\sync\simple.h"\
	{$(INCLUDE)}"\ospace\sync\spriority.h"\
	{$(INCLUDE)}"\ospace\thread\_startup.h"\
	{$(INCLUDE)}"\ospace\thread\priority.h"\
	{$(INCLUDE)}"\ospace\thread\thisthrd.h"\
	{$(INCLUDE)}"\ospace\thread\thread.h"\
	{$(INCLUDE)}"\ospace\thread\thread.ipp"\
	{$(INCLUDE)}"\ospace\thread\types.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\syncthrdcs.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_PHEAD=\
	".\win16\DXFIMP.h"\
	
# ADD CPP /Yc"pheader.hpp"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O2 /I "\triasdev.mvc\inc.hpp" /I\
 "\triasdev.mvc\inc.hpp\inc" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D\
 "DLL" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "__CV__"\
 /Fp"$(INTDIR)/DXFIMP.pch" /Yc"pheader.hpp" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\PHEADER.OBJ" : $(SOURCE) $(DEP_CPP_PHEAD) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\DXFIMP.pch" : $(SOURCE) $(DEP_CPP_PHEAD) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Dxfimp - Win32 Debug"

DEP_CPP_PHEAD=\
	"..\..\..\Cv32.mvc\Include\gc.h"\
	".\Dxfimp.hpp"\
	".\Dxfimp.hr"\
	".\DxfImpConfig.h"\
	".\Dxfimpif.hpp"\
	".\Optparam.hpp"\
	".\Pheader.hpp"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\hpp\errcodesodbc.hxx"\
	{$(INCLUDE)}"\hpp\protos.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\ospace\sync\counting.h"\
	{$(INCLUDE)}"\ospace\sync\counting.ipp"\
	{$(INCLUDE)}"\ospace\sync\critical.h"\
	{$(INCLUDE)}"\ospace\sync\critical.ipp"\
	{$(INCLUDE)}"\ospace\sync\eventsem.h"\
	{$(INCLUDE)}"\ospace\sync\eventsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\lock.h"\
	{$(INCLUDE)}"\ospace\sync\lock.ipp"\
	{$(INCLUDE)}"\ospace\sync\monitor.h"\
	{$(INCLUDE)}"\ospace\sync\monitor.ipp"\
	{$(INCLUDE)}"\ospace\sync\mutex.h"\
	{$(INCLUDE)}"\ospace\sync\mutex.ipp"\
	{$(INCLUDE)}"\ospace\sync\rfifo.h"\
	{$(INCLUDE)}"\ospace\sync\rpriority.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.ipp"\
	{$(INCLUDE)}"\ospace\sync\rwsem.h"\
	{$(INCLUDE)}"\ospace\sync\rwsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\sentinel.h"\
	{$(INCLUDE)}"\ospace\sync\sentinel.ipp"\
	{$(INCLUDE)}"\ospace\sync\sfifo.h"\
	{$(INCLUDE)}"\ospace\sync\simple.h"\
	{$(INCLUDE)}"\ospace\sync\spriority.h"\
	{$(INCLUDE)}"\ospace\thread\_startup.h"\
	{$(INCLUDE)}"\ospace\thread\priority.h"\
	{$(INCLUDE)}"\ospace\thread\thisthrd.h"\
	{$(INCLUDE)}"\ospace\thread\thread.h"\
	{$(INCLUDE)}"\ospace\thread\thread.ipp"\
	{$(INCLUDE)}"\ospace\thread\types.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\syncthrdcs.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_PHEAD=\
	".\win16\DXFIMP.h"\
	
# ADD CPP /Yc"pheader.hpp"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /I "\triasdev.mvc\inc.hpp" /I\
 "\triasdev.mvc\inc.hpp\inc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D\
 "DLL" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "__CV__" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/DXFIMP.pch" /Yc"pheader.hpp" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\PHEADER.OBJ" : $(SOURCE) $(DEP_CPP_PHEAD) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\PHEADER.SBR" : $(SOURCE) $(DEP_CPP_PHEAD) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\DXFIMP.pch" : $(SOURCE) $(DEP_CPP_PHEAD) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DXFIMP.RC
DEP_RSC_DXFIM=\
	".\DXFIMP.RCV"\
	

"$(INTDIR)\DXFIMP.res" : $(SOURCE) $(DEP_RSC_DXFIM) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DXFIMP.CPP

!IF  "$(CFG)" == "Dxfimp - Win32 Release"

DEP_CPP_DXFIMP=\
	"..\..\..\Cv32.mvc\Include\gc.h"\
	".\DXFGUIDS.H"\
	".\Dxfimp.hpp"\
	".\Dxfimp.hr"\
	".\DxfImpConfig.h"\
	".\Dxfimpif.hpp"\
	".\Optparam.hpp"\
	".\Pheader.hpp"\
	".\VERSIO32.H"\
	".\VERSION.H"\
	".\Win16\Versio16.h"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\hpp\errcodesodbc.hxx"\
	{$(INCLUDE)}"\hpp\protos.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\ospace\sync\counting.h"\
	{$(INCLUDE)}"\ospace\sync\counting.ipp"\
	{$(INCLUDE)}"\ospace\sync\critical.h"\
	{$(INCLUDE)}"\ospace\sync\critical.ipp"\
	{$(INCLUDE)}"\ospace\sync\eventsem.h"\
	{$(INCLUDE)}"\ospace\sync\lock.h"\
	{$(INCLUDE)}"\ospace\sync\lock.ipp"\
	{$(INCLUDE)}"\ospace\sync\monitor.h"\
	{$(INCLUDE)}"\ospace\sync\monitor.ipp"\
	{$(INCLUDE)}"\ospace\sync\mutex.h"\
	{$(INCLUDE)}"\ospace\sync\mutex.ipp"\
	{$(INCLUDE)}"\ospace\sync\rfifo.h"\
	{$(INCLUDE)}"\ospace\sync\rpriority.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.ipp"\
	{$(INCLUDE)}"\ospace\sync\rwsem.h"\
	{$(INCLUDE)}"\ospace\sync\rwsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\sentinel.h"\
	{$(INCLUDE)}"\ospace\sync\sentinel.ipp"\
	{$(INCLUDE)}"\ospace\sync\sfifo.h"\
	{$(INCLUDE)}"\ospace\sync\simple.h"\
	{$(INCLUDE)}"\ospace\sync\spriority.h"\
	{$(INCLUDE)}"\ospace\thread\_startup.h"\
	{$(INCLUDE)}"\ospace\thread\priority.h"\
	{$(INCLUDE)}"\ospace\thread\thisthrd.h"\
	{$(INCLUDE)}"\ospace\thread\thread.h"\
	{$(INCLUDE)}"\ospace\thread\thread.ipp"\
	{$(INCLUDE)}"\ospace\thread\types.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\syncthrdcs.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_DXFIMP=\
	".\win16\DXFIMP.h"\
	

"$(INTDIR)\DXFIMP.OBJ" : $(SOURCE) $(DEP_CPP_DXFIMP) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"


!ELSEIF  "$(CFG)" == "Dxfimp - Win32 Debug"

DEP_CPP_DXFIMP=\
	"..\..\..\Cv32.mvc\Include\gc.h"\
	".\DXFGUIDS.H"\
	".\Dxfimp.hpp"\
	".\Dxfimp.hr"\
	".\DxfImpConfig.h"\
	".\Dxfimpif.hpp"\
	".\Optparam.hpp"\
	".\Pheader.hpp"\
	".\VERSIO32.H"\
	".\VERSION.H"\
	".\Win16\Versio16.h"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\hpp\errcodesodbc.hxx"\
	{$(INCLUDE)}"\hpp\protos.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\ospace\sync\counting.h"\
	{$(INCLUDE)}"\ospace\sync\counting.ipp"\
	{$(INCLUDE)}"\ospace\sync\critical.h"\
	{$(INCLUDE)}"\ospace\sync\critical.ipp"\
	{$(INCLUDE)}"\ospace\sync\eventsem.h"\
	{$(INCLUDE)}"\ospace\sync\eventsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\lock.h"\
	{$(INCLUDE)}"\ospace\sync\lock.ipp"\
	{$(INCLUDE)}"\ospace\sync\monitor.h"\
	{$(INCLUDE)}"\ospace\sync\monitor.ipp"\
	{$(INCLUDE)}"\ospace\sync\mutex.h"\
	{$(INCLUDE)}"\ospace\sync\mutex.ipp"\
	{$(INCLUDE)}"\ospace\sync\rfifo.h"\
	{$(INCLUDE)}"\ospace\sync\rpriority.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.ipp"\
	{$(INCLUDE)}"\ospace\sync\rwsem.h"\
	{$(INCLUDE)}"\ospace\sync\rwsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\sentinel.h"\
	{$(INCLUDE)}"\ospace\sync\sentinel.ipp"\
	{$(INCLUDE)}"\ospace\sync\sfifo.h"\
	{$(INCLUDE)}"\ospace\sync\simple.h"\
	{$(INCLUDE)}"\ospace\sync\spriority.h"\
	{$(INCLUDE)}"\ospace\thread\_startup.h"\
	{$(INCLUDE)}"\ospace\thread\priority.h"\
	{$(INCLUDE)}"\ospace\thread\thisthrd.h"\
	{$(INCLUDE)}"\ospace\thread\thread.h"\
	{$(INCLUDE)}"\ospace\thread\thread.ipp"\
	{$(INCLUDE)}"\ospace\thread\types.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\syncthrdcs.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_DXFIMP=\
	".\win16\DXFIMP.h"\
	

"$(INTDIR)\DXFIMP.OBJ" : $(SOURCE) $(DEP_CPP_DXFIMP) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"

"$(INTDIR)\DXFIMP.SBR" : $(SOURCE) $(DEP_CPP_DXFIMP) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DXFIMP.DEF

!IF  "$(CFG)" == "Dxfimp - Win32 Release"

!ELSEIF  "$(CFG)" == "Dxfimp - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DXFIMPIF.CPP

!IF  "$(CFG)" == "Dxfimp - Win32 Release"

DEP_CPP_DXFIMPI=\
	"..\..\..\Cv32.mvc\Include\gc.h"\
	".\BLOCK.HPP"\
	".\Dxfimp.hpp"\
	".\Dxfimp.hr"\
	".\DxfImpConfig.h"\
	".\Dxfimpif.hpp"\
	".\HEADER.HPP"\
	".\HELPTEXT.HPP"\
	".\IMPRESLT.HPP"\
	".\LAYERS.HPP"\
	".\LEXTYPES.H"\
	".\MERKMAL.HPP"\
	".\NUMEDIT.HPP"\
	".\Optparam.hpp"\
	".\OPTPRDLG.HPP"\
	".\Pheader.hpp"\
	".\REALEDIT.HPP"\
	".\RECHSTAT.HPP"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\hpp\errcodesodbc.hxx"\
	{$(INCLUDE)}"\hpp\protos.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\ospace\sync\counting.h"\
	{$(INCLUDE)}"\ospace\sync\counting.ipp"\
	{$(INCLUDE)}"\ospace\sync\critical.h"\
	{$(INCLUDE)}"\ospace\sync\critical.ipp"\
	{$(INCLUDE)}"\ospace\sync\eventsem.h"\
	{$(INCLUDE)}"\ospace\sync\lock.h"\
	{$(INCLUDE)}"\ospace\sync\lock.ipp"\
	{$(INCLUDE)}"\ospace\sync\monitor.h"\
	{$(INCLUDE)}"\ospace\sync\monitor.ipp"\
	{$(INCLUDE)}"\ospace\sync\mutex.h"\
	{$(INCLUDE)}"\ospace\sync\mutex.ipp"\
	{$(INCLUDE)}"\ospace\sync\rfifo.h"\
	{$(INCLUDE)}"\ospace\sync\rpriority.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.ipp"\
	{$(INCLUDE)}"\ospace\sync\rwsem.h"\
	{$(INCLUDE)}"\ospace\sync\rwsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\sentinel.h"\
	{$(INCLUDE)}"\ospace\sync\sentinel.ipp"\
	{$(INCLUDE)}"\ospace\sync\sfifo.h"\
	{$(INCLUDE)}"\ospace\sync\simple.h"\
	{$(INCLUDE)}"\ospace\sync\spriority.h"\
	{$(INCLUDE)}"\ospace\thread\_startup.h"\
	{$(INCLUDE)}"\ospace\thread\priority.h"\
	{$(INCLUDE)}"\ospace\thread\thisthrd.h"\
	{$(INCLUDE)}"\ospace\thread\thread.h"\
	{$(INCLUDE)}"\ospace\thread\thread.ipp"\
	{$(INCLUDE)}"\ospace\thread\types.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\syncthrdcs.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_DXFIMPI=\
	".\win16\DXFIMP.h"\
	

"$(INTDIR)\DXFIMPIF.OBJ" : $(SOURCE) $(DEP_CPP_DXFIMPI) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"


!ELSEIF  "$(CFG)" == "Dxfimp - Win32 Debug"

DEP_CPP_DXFIMPI=\
	"..\..\..\Cv32.mvc\Include\gc.h"\
	".\BLOCK.HPP"\
	".\Dxfimp.hpp"\
	".\Dxfimp.hr"\
	".\DxfImpConfig.h"\
	".\Dxfimpif.hpp"\
	".\HEADER.HPP"\
	".\HELPTEXT.HPP"\
	".\IMPRESLT.HPP"\
	".\LAYERS.HPP"\
	".\LEXTYPES.H"\
	".\MERKMAL.HPP"\
	".\NUMEDIT.HPP"\
	".\Optparam.hpp"\
	".\OPTPRDLG.HPP"\
	".\Pheader.hpp"\
	".\REALEDIT.HPP"\
	".\RECHSTAT.HPP"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\hpp\errcodesodbc.hxx"\
	{$(INCLUDE)}"\hpp\protos.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\ospace\sync\counting.h"\
	{$(INCLUDE)}"\ospace\sync\counting.ipp"\
	{$(INCLUDE)}"\ospace\sync\critical.h"\
	{$(INCLUDE)}"\ospace\sync\critical.ipp"\
	{$(INCLUDE)}"\ospace\sync\eventsem.h"\
	{$(INCLUDE)}"\ospace\sync\eventsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\lock.h"\
	{$(INCLUDE)}"\ospace\sync\lock.ipp"\
	{$(INCLUDE)}"\ospace\sync\monitor.h"\
	{$(INCLUDE)}"\ospace\sync\monitor.ipp"\
	{$(INCLUDE)}"\ospace\sync\mutex.h"\
	{$(INCLUDE)}"\ospace\sync\mutex.ipp"\
	{$(INCLUDE)}"\ospace\sync\rfifo.h"\
	{$(INCLUDE)}"\ospace\sync\rpriority.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.ipp"\
	{$(INCLUDE)}"\ospace\sync\rwsem.h"\
	{$(INCLUDE)}"\ospace\sync\rwsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\sentinel.h"\
	{$(INCLUDE)}"\ospace\sync\sentinel.ipp"\
	{$(INCLUDE)}"\ospace\sync\sfifo.h"\
	{$(INCLUDE)}"\ospace\sync\simple.h"\
	{$(INCLUDE)}"\ospace\sync\spriority.h"\
	{$(INCLUDE)}"\ospace\thread\_startup.h"\
	{$(INCLUDE)}"\ospace\thread\priority.h"\
	{$(INCLUDE)}"\ospace\thread\thisthrd.h"\
	{$(INCLUDE)}"\ospace\thread\thread.h"\
	{$(INCLUDE)}"\ospace\thread\thread.ipp"\
	{$(INCLUDE)}"\ospace\thread\types.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\syncthrdcs.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_DXFIMPI=\
	".\win16\DXFIMP.h"\
	

"$(INTDIR)\DXFIMPIF.OBJ" : $(SOURCE) $(DEP_CPP_DXFIMPI) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"

"$(INTDIR)\DXFIMPIF.SBR" : $(SOURCE) $(DEP_CPP_DXFIMPI) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DXFY.CPP

!IF  "$(CFG)" == "Dxfimp - Win32 Release"

DEP_CPP_DXFY_=\
	"..\..\..\Cv32.mvc\Include\gc.h"\
	".\BLOCK.HPP"\
	".\DGEO_OBJ.HPP"\
	".\Dxfimp.hpp"\
	".\Dxfimp.hr"\
	".\DxfImpConfig.h"\
	".\Dxfimpif.hpp"\
	".\HEADER.HPP"\
	".\LAYERS.HPP"\
	".\LEXTYPES.H"\
	".\Optparam.hpp"\
	".\Pheader.hpp"\
	".\PUNKTLI.HPP"\
	".\RECHSTAT.HPP"\
	".\TOOLS.HPP"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\hpp\errcodesodbc.hxx"\
	{$(INCLUDE)}"\hpp\protos.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\ospace\sync\counting.h"\
	{$(INCLUDE)}"\ospace\sync\counting.ipp"\
	{$(INCLUDE)}"\ospace\sync\critical.h"\
	{$(INCLUDE)}"\ospace\sync\critical.ipp"\
	{$(INCLUDE)}"\ospace\sync\eventsem.h"\
	{$(INCLUDE)}"\ospace\sync\lock.h"\
	{$(INCLUDE)}"\ospace\sync\lock.ipp"\
	{$(INCLUDE)}"\ospace\sync\monitor.h"\
	{$(INCLUDE)}"\ospace\sync\monitor.ipp"\
	{$(INCLUDE)}"\ospace\sync\mutex.h"\
	{$(INCLUDE)}"\ospace\sync\mutex.ipp"\
	{$(INCLUDE)}"\ospace\sync\rfifo.h"\
	{$(INCLUDE)}"\ospace\sync\rpriority.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.ipp"\
	{$(INCLUDE)}"\ospace\sync\rwsem.h"\
	{$(INCLUDE)}"\ospace\sync\rwsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\sentinel.h"\
	{$(INCLUDE)}"\ospace\sync\sentinel.ipp"\
	{$(INCLUDE)}"\ospace\sync\sfifo.h"\
	{$(INCLUDE)}"\ospace\sync\simple.h"\
	{$(INCLUDE)}"\ospace\sync\spriority.h"\
	{$(INCLUDE)}"\ospace\thread\_startup.h"\
	{$(INCLUDE)}"\ospace\thread\priority.h"\
	{$(INCLUDE)}"\ospace\thread\thisthrd.h"\
	{$(INCLUDE)}"\ospace\thread\thread.h"\
	{$(INCLUDE)}"\ospace\thread\thread.ipp"\
	{$(INCLUDE)}"\ospace\thread\types.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\syncthrdcs.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_DXFY_=\
	".\win16\DXFIMP.h"\
	

"$(INTDIR)\DXFY.OBJ" : $(SOURCE) $(DEP_CPP_DXFY_) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"


!ELSEIF  "$(CFG)" == "Dxfimp - Win32 Debug"

DEP_CPP_DXFY_=\
	"..\..\..\Cv32.mvc\Include\gc.h"\
	".\BLOCK.HPP"\
	".\DGEO_OBJ.HPP"\
	".\Dxfimp.hpp"\
	".\Dxfimp.hr"\
	".\DxfImpConfig.h"\
	".\Dxfimpif.hpp"\
	".\HEADER.HPP"\
	".\LAYERS.HPP"\
	".\LEXTYPES.H"\
	".\Optparam.hpp"\
	".\Pheader.hpp"\
	".\PUNKTLI.HPP"\
	".\RECHSTAT.HPP"\
	".\TOOLS.HPP"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\hpp\errcodesodbc.hxx"\
	{$(INCLUDE)}"\hpp\protos.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\ospace\sync\counting.h"\
	{$(INCLUDE)}"\ospace\sync\counting.ipp"\
	{$(INCLUDE)}"\ospace\sync\critical.h"\
	{$(INCLUDE)}"\ospace\sync\critical.ipp"\
	{$(INCLUDE)}"\ospace\sync\eventsem.h"\
	{$(INCLUDE)}"\ospace\sync\eventsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\lock.h"\
	{$(INCLUDE)}"\ospace\sync\lock.ipp"\
	{$(INCLUDE)}"\ospace\sync\monitor.h"\
	{$(INCLUDE)}"\ospace\sync\monitor.ipp"\
	{$(INCLUDE)}"\ospace\sync\mutex.h"\
	{$(INCLUDE)}"\ospace\sync\mutex.ipp"\
	{$(INCLUDE)}"\ospace\sync\rfifo.h"\
	{$(INCLUDE)}"\ospace\sync\rpriority.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.ipp"\
	{$(INCLUDE)}"\ospace\sync\rwsem.h"\
	{$(INCLUDE)}"\ospace\sync\rwsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\sentinel.h"\
	{$(INCLUDE)}"\ospace\sync\sentinel.ipp"\
	{$(INCLUDE)}"\ospace\sync\sfifo.h"\
	{$(INCLUDE)}"\ospace\sync\simple.h"\
	{$(INCLUDE)}"\ospace\sync\spriority.h"\
	{$(INCLUDE)}"\ospace\thread\_startup.h"\
	{$(INCLUDE)}"\ospace\thread\priority.h"\
	{$(INCLUDE)}"\ospace\thread\thisthrd.h"\
	{$(INCLUDE)}"\ospace\thread\thread.h"\
	{$(INCLUDE)}"\ospace\thread\thread.ipp"\
	{$(INCLUDE)}"\ospace\thread\types.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\syncthrdcs.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_DXFY_=\
	".\win16\DXFIMP.h"\
	

"$(INTDIR)\DXFY.OBJ" : $(SOURCE) $(DEP_CPP_DXFY_) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"

"$(INTDIR)\DXFY.SBR" : $(SOURCE) $(DEP_CPP_DXFY_) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DXFLX.CPP

!IF  "$(CFG)" == "Dxfimp - Win32 Release"

DEP_CPP_DXFLX=\
	"..\..\..\Cv32.mvc\Include\gc.h"\
	".\Dxfimp.hpp"\
	".\Dxfimp.hr"\
	".\DxfImpConfig.h"\
	".\Dxfimpif.hpp"\
	".\DXFLX.CP"\
	".\LEXTYPES.H"\
	".\Optparam.hpp"\
	".\Pheader.hpp"\
	".\YYTAB.H"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\hpp\errcodesodbc.hxx"\
	{$(INCLUDE)}"\hpp\protos.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\ospace\sync\counting.h"\
	{$(INCLUDE)}"\ospace\sync\counting.ipp"\
	{$(INCLUDE)}"\ospace\sync\critical.h"\
	{$(INCLUDE)}"\ospace\sync\critical.ipp"\
	{$(INCLUDE)}"\ospace\sync\eventsem.h"\
	{$(INCLUDE)}"\ospace\sync\lock.h"\
	{$(INCLUDE)}"\ospace\sync\lock.ipp"\
	{$(INCLUDE)}"\ospace\sync\monitor.h"\
	{$(INCLUDE)}"\ospace\sync\monitor.ipp"\
	{$(INCLUDE)}"\ospace\sync\mutex.h"\
	{$(INCLUDE)}"\ospace\sync\mutex.ipp"\
	{$(INCLUDE)}"\ospace\sync\rfifo.h"\
	{$(INCLUDE)}"\ospace\sync\rpriority.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.ipp"\
	{$(INCLUDE)}"\ospace\sync\rwsem.h"\
	{$(INCLUDE)}"\ospace\sync\rwsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\sentinel.h"\
	{$(INCLUDE)}"\ospace\sync\sentinel.ipp"\
	{$(INCLUDE)}"\ospace\sync\sfifo.h"\
	{$(INCLUDE)}"\ospace\sync\simple.h"\
	{$(INCLUDE)}"\ospace\sync\spriority.h"\
	{$(INCLUDE)}"\ospace\thread\_startup.h"\
	{$(INCLUDE)}"\ospace\thread\priority.h"\
	{$(INCLUDE)}"\ospace\thread\thisthrd.h"\
	{$(INCLUDE)}"\ospace\thread\thread.h"\
	{$(INCLUDE)}"\ospace\thread\thread.ipp"\
	{$(INCLUDE)}"\ospace\thread\types.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\syncthrdcs.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_DXFLX=\
	".\win16\DXFIMP.h"\
	

"$(INTDIR)\DXFLX.OBJ" : $(SOURCE) $(DEP_CPP_DXFLX) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"


!ELSEIF  "$(CFG)" == "Dxfimp - Win32 Debug"

DEP_CPP_DXFLX=\
	"..\..\..\Cv32.mvc\Include\gc.h"\
	".\Dxfimp.hpp"\
	".\Dxfimp.hr"\
	".\DxfImpConfig.h"\
	".\Dxfimpif.hpp"\
	".\DXFLX.CP"\
	".\LEXTYPES.H"\
	".\Optparam.hpp"\
	".\Pheader.hpp"\
	".\YYTAB.H"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\hpp\errcodesodbc.hxx"\
	{$(INCLUDE)}"\hpp\protos.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\ospace\sync\counting.h"\
	{$(INCLUDE)}"\ospace\sync\counting.ipp"\
	{$(INCLUDE)}"\ospace\sync\critical.h"\
	{$(INCLUDE)}"\ospace\sync\critical.ipp"\
	{$(INCLUDE)}"\ospace\sync\eventsem.h"\
	{$(INCLUDE)}"\ospace\sync\eventsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\lock.h"\
	{$(INCLUDE)}"\ospace\sync\lock.ipp"\
	{$(INCLUDE)}"\ospace\sync\monitor.h"\
	{$(INCLUDE)}"\ospace\sync\monitor.ipp"\
	{$(INCLUDE)}"\ospace\sync\mutex.h"\
	{$(INCLUDE)}"\ospace\sync\mutex.ipp"\
	{$(INCLUDE)}"\ospace\sync\rfifo.h"\
	{$(INCLUDE)}"\ospace\sync\rpriority.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.ipp"\
	{$(INCLUDE)}"\ospace\sync\rwsem.h"\
	{$(INCLUDE)}"\ospace\sync\rwsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\sentinel.h"\
	{$(INCLUDE)}"\ospace\sync\sentinel.ipp"\
	{$(INCLUDE)}"\ospace\sync\sfifo.h"\
	{$(INCLUDE)}"\ospace\sync\simple.h"\
	{$(INCLUDE)}"\ospace\sync\spriority.h"\
	{$(INCLUDE)}"\ospace\thread\_startup.h"\
	{$(INCLUDE)}"\ospace\thread\priority.h"\
	{$(INCLUDE)}"\ospace\thread\thisthrd.h"\
	{$(INCLUDE)}"\ospace\thread\thread.h"\
	{$(INCLUDE)}"\ospace\thread\thread.ipp"\
	{$(INCLUDE)}"\ospace\thread\types.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\syncthrdcs.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_DXFLX=\
	".\win16\DXFIMP.h"\
	

"$(INTDIR)\DXFLX.OBJ" : $(SOURCE) $(DEP_CPP_DXFLX) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"

"$(INTDIR)\DXFLX.SBR" : $(SOURCE) $(DEP_CPP_DXFLX) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\OPTPARAM.CPP

!IF  "$(CFG)" == "Dxfimp - Win32 Release"

DEP_CPP_OPTPA=\
	"..\..\..\Cv32.mvc\Include\gc.h"\
	".\Dxfimp.hpp"\
	".\Dxfimp.hr"\
	".\DxfImpConfig.h"\
	".\Dxfimpif.hpp"\
	".\Optparam.hpp"\
	".\Pheader.hpp"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\hpp\errcodesodbc.hxx"\
	{$(INCLUDE)}"\hpp\protos.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\ospace\sync\counting.h"\
	{$(INCLUDE)}"\ospace\sync\counting.ipp"\
	{$(INCLUDE)}"\ospace\sync\critical.h"\
	{$(INCLUDE)}"\ospace\sync\critical.ipp"\
	{$(INCLUDE)}"\ospace\sync\eventsem.h"\
	{$(INCLUDE)}"\ospace\sync\lock.h"\
	{$(INCLUDE)}"\ospace\sync\lock.ipp"\
	{$(INCLUDE)}"\ospace\sync\monitor.h"\
	{$(INCLUDE)}"\ospace\sync\monitor.ipp"\
	{$(INCLUDE)}"\ospace\sync\mutex.h"\
	{$(INCLUDE)}"\ospace\sync\mutex.ipp"\
	{$(INCLUDE)}"\ospace\sync\rfifo.h"\
	{$(INCLUDE)}"\ospace\sync\rpriority.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.ipp"\
	{$(INCLUDE)}"\ospace\sync\rwsem.h"\
	{$(INCLUDE)}"\ospace\sync\rwsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\sentinel.h"\
	{$(INCLUDE)}"\ospace\sync\sentinel.ipp"\
	{$(INCLUDE)}"\ospace\sync\sfifo.h"\
	{$(INCLUDE)}"\ospace\sync\simple.h"\
	{$(INCLUDE)}"\ospace\sync\spriority.h"\
	{$(INCLUDE)}"\ospace\thread\_startup.h"\
	{$(INCLUDE)}"\ospace\thread\priority.h"\
	{$(INCLUDE)}"\ospace\thread\thisthrd.h"\
	{$(INCLUDE)}"\ospace\thread\thread.h"\
	{$(INCLUDE)}"\ospace\thread\thread.ipp"\
	{$(INCLUDE)}"\ospace\thread\types.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\syncthrdcs.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_OPTPA=\
	".\win16\DXFIMP.h"\
	

"$(INTDIR)\OPTPARAM.OBJ" : $(SOURCE) $(DEP_CPP_OPTPA) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"


!ELSEIF  "$(CFG)" == "Dxfimp - Win32 Debug"

DEP_CPP_OPTPA=\
	"..\..\..\Cv32.mvc\Include\gc.h"\
	".\Dxfimp.hpp"\
	".\Dxfimp.hr"\
	".\DxfImpConfig.h"\
	".\Dxfimpif.hpp"\
	".\Optparam.hpp"\
	".\Pheader.hpp"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\hpp\errcodesodbc.hxx"\
	{$(INCLUDE)}"\hpp\protos.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\ospace\sync\counting.h"\
	{$(INCLUDE)}"\ospace\sync\counting.ipp"\
	{$(INCLUDE)}"\ospace\sync\critical.h"\
	{$(INCLUDE)}"\ospace\sync\critical.ipp"\
	{$(INCLUDE)}"\ospace\sync\eventsem.h"\
	{$(INCLUDE)}"\ospace\sync\eventsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\lock.h"\
	{$(INCLUDE)}"\ospace\sync\lock.ipp"\
	{$(INCLUDE)}"\ospace\sync\monitor.h"\
	{$(INCLUDE)}"\ospace\sync\monitor.ipp"\
	{$(INCLUDE)}"\ospace\sync\mutex.h"\
	{$(INCLUDE)}"\ospace\sync\mutex.ipp"\
	{$(INCLUDE)}"\ospace\sync\rfifo.h"\
	{$(INCLUDE)}"\ospace\sync\rpriority.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.ipp"\
	{$(INCLUDE)}"\ospace\sync\rwsem.h"\
	{$(INCLUDE)}"\ospace\sync\rwsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\sentinel.h"\
	{$(INCLUDE)}"\ospace\sync\sentinel.ipp"\
	{$(INCLUDE)}"\ospace\sync\sfifo.h"\
	{$(INCLUDE)}"\ospace\sync\simple.h"\
	{$(INCLUDE)}"\ospace\sync\spriority.h"\
	{$(INCLUDE)}"\ospace\thread\_startup.h"\
	{$(INCLUDE)}"\ospace\thread\priority.h"\
	{$(INCLUDE)}"\ospace\thread\thisthrd.h"\
	{$(INCLUDE)}"\ospace\thread\thread.h"\
	{$(INCLUDE)}"\ospace\thread\thread.ipp"\
	{$(INCLUDE)}"\ospace\thread\types.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\syncthrdcs.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_OPTPA=\
	".\win16\DXFIMP.h"\
	

"$(INTDIR)\OPTPARAM.OBJ" : $(SOURCE) $(DEP_CPP_OPTPA) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"

"$(INTDIR)\OPTPARAM.SBR" : $(SOURCE) $(DEP_CPP_OPTPA) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\HEADER.CPP

!IF  "$(CFG)" == "Dxfimp - Win32 Release"

DEP_CPP_HEADE=\
	"..\..\..\Cv32.mvc\Include\gc.h"\
	".\Dxfimp.hpp"\
	".\Dxfimp.hr"\
	".\DxfImpConfig.h"\
	".\Dxfimpif.hpp"\
	".\HEADER.HPP"\
	".\Optparam.hpp"\
	".\Pheader.hpp"\
	".\TOOLS.HPP"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\Hdrentrx.hxx"\
	{$(INCLUDE)}"\hpp\errcodesodbc.hxx"\
	{$(INCLUDE)}"\hpp\protos.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\ospace\sync\counting.h"\
	{$(INCLUDE)}"\ospace\sync\counting.ipp"\
	{$(INCLUDE)}"\ospace\sync\critical.h"\
	{$(INCLUDE)}"\ospace\sync\critical.ipp"\
	{$(INCLUDE)}"\ospace\sync\eventsem.h"\
	{$(INCLUDE)}"\ospace\sync\lock.h"\
	{$(INCLUDE)}"\ospace\sync\lock.ipp"\
	{$(INCLUDE)}"\ospace\sync\monitor.h"\
	{$(INCLUDE)}"\ospace\sync\monitor.ipp"\
	{$(INCLUDE)}"\ospace\sync\mutex.h"\
	{$(INCLUDE)}"\ospace\sync\mutex.ipp"\
	{$(INCLUDE)}"\ospace\sync\rfifo.h"\
	{$(INCLUDE)}"\ospace\sync\rpriority.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.ipp"\
	{$(INCLUDE)}"\ospace\sync\rwsem.h"\
	{$(INCLUDE)}"\ospace\sync\rwsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\sentinel.h"\
	{$(INCLUDE)}"\ospace\sync\sentinel.ipp"\
	{$(INCLUDE)}"\ospace\sync\sfifo.h"\
	{$(INCLUDE)}"\ospace\sync\simple.h"\
	{$(INCLUDE)}"\ospace\sync\spriority.h"\
	{$(INCLUDE)}"\ospace\thread\_startup.h"\
	{$(INCLUDE)}"\ospace\thread\priority.h"\
	{$(INCLUDE)}"\ospace\thread\thisthrd.h"\
	{$(INCLUDE)}"\ospace\thread\thread.h"\
	{$(INCLUDE)}"\ospace\thread\thread.ipp"\
	{$(INCLUDE)}"\ospace\thread\types.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\Resstrg.h"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\syncthrdcs.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_HEADE=\
	".\win16\DXFIMP.h"\
	

"$(INTDIR)\HEADER.OBJ" : $(SOURCE) $(DEP_CPP_HEADE) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"


!ELSEIF  "$(CFG)" == "Dxfimp - Win32 Debug"

DEP_CPP_HEADE=\
	"..\..\..\Cv32.mvc\Include\gc.h"\
	".\Dxfimp.hpp"\
	".\Dxfimp.hr"\
	".\DxfImpConfig.h"\
	".\Dxfimpif.hpp"\
	".\HEADER.HPP"\
	".\Optparam.hpp"\
	".\Pheader.hpp"\
	".\TOOLS.HPP"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\Hdrentrx.hxx"\
	{$(INCLUDE)}"\hpp\errcodesodbc.hxx"\
	{$(INCLUDE)}"\hpp\protos.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\ospace\sync\counting.h"\
	{$(INCLUDE)}"\ospace\sync\counting.ipp"\
	{$(INCLUDE)}"\ospace\sync\critical.h"\
	{$(INCLUDE)}"\ospace\sync\critical.ipp"\
	{$(INCLUDE)}"\ospace\sync\eventsem.h"\
	{$(INCLUDE)}"\ospace\sync\eventsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\lock.h"\
	{$(INCLUDE)}"\ospace\sync\lock.ipp"\
	{$(INCLUDE)}"\ospace\sync\monitor.h"\
	{$(INCLUDE)}"\ospace\sync\monitor.ipp"\
	{$(INCLUDE)}"\ospace\sync\mutex.h"\
	{$(INCLUDE)}"\ospace\sync\mutex.ipp"\
	{$(INCLUDE)}"\ospace\sync\rfifo.h"\
	{$(INCLUDE)}"\ospace\sync\rpriority.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.ipp"\
	{$(INCLUDE)}"\ospace\sync\rwsem.h"\
	{$(INCLUDE)}"\ospace\sync\rwsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\sentinel.h"\
	{$(INCLUDE)}"\ospace\sync\sentinel.ipp"\
	{$(INCLUDE)}"\ospace\sync\sfifo.h"\
	{$(INCLUDE)}"\ospace\sync\simple.h"\
	{$(INCLUDE)}"\ospace\sync\spriority.h"\
	{$(INCLUDE)}"\ospace\thread\_startup.h"\
	{$(INCLUDE)}"\ospace\thread\priority.h"\
	{$(INCLUDE)}"\ospace\thread\thisthrd.h"\
	{$(INCLUDE)}"\ospace\thread\thread.h"\
	{$(INCLUDE)}"\ospace\thread\thread.ipp"\
	{$(INCLUDE)}"\ospace\thread\types.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\Resstrg.h"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\syncthrdcs.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_HEADE=\
	".\win16\DXFIMP.h"\
	

"$(INTDIR)\HEADER.OBJ" : $(SOURCE) $(DEP_CPP_HEADE) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"

"$(INTDIR)\HEADER.SBR" : $(SOURCE) $(DEP_CPP_HEADE) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRUTIL.CPP

!IF  "$(CFG)" == "Dxfimp - Win32 Release"

DEP_CPP_STRUT=\
	"..\..\..\Cv32.mvc\Include\gc.h"\
	".\Dxfimp.hpp"\
	".\Dxfimp.hr"\
	".\DxfImpConfig.h"\
	".\Dxfimpif.hpp"\
	".\Optparam.hpp"\
	".\Pheader.hpp"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\hpp\errcodesodbc.hxx"\
	{$(INCLUDE)}"\hpp\protos.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\ospace\sync\counting.h"\
	{$(INCLUDE)}"\ospace\sync\counting.ipp"\
	{$(INCLUDE)}"\ospace\sync\critical.h"\
	{$(INCLUDE)}"\ospace\sync\critical.ipp"\
	{$(INCLUDE)}"\ospace\sync\eventsem.h"\
	{$(INCLUDE)}"\ospace\sync\lock.h"\
	{$(INCLUDE)}"\ospace\sync\lock.ipp"\
	{$(INCLUDE)}"\ospace\sync\monitor.h"\
	{$(INCLUDE)}"\ospace\sync\monitor.ipp"\
	{$(INCLUDE)}"\ospace\sync\mutex.h"\
	{$(INCLUDE)}"\ospace\sync\mutex.ipp"\
	{$(INCLUDE)}"\ospace\sync\rfifo.h"\
	{$(INCLUDE)}"\ospace\sync\rpriority.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.ipp"\
	{$(INCLUDE)}"\ospace\sync\rwsem.h"\
	{$(INCLUDE)}"\ospace\sync\rwsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\sentinel.h"\
	{$(INCLUDE)}"\ospace\sync\sentinel.ipp"\
	{$(INCLUDE)}"\ospace\sync\sfifo.h"\
	{$(INCLUDE)}"\ospace\sync\simple.h"\
	{$(INCLUDE)}"\ospace\sync\spriority.h"\
	{$(INCLUDE)}"\ospace\thread\_startup.h"\
	{$(INCLUDE)}"\ospace\thread\priority.h"\
	{$(INCLUDE)}"\ospace\thread\thisthrd.h"\
	{$(INCLUDE)}"\ospace\thread\thread.h"\
	{$(INCLUDE)}"\ospace\thread\thread.ipp"\
	{$(INCLUDE)}"\ospace\thread\types.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\syncthrdcs.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_STRUT=\
	".\win16\DXFIMP.h"\
	

"$(INTDIR)\STRUTIL.OBJ" : $(SOURCE) $(DEP_CPP_STRUT) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"


!ELSEIF  "$(CFG)" == "Dxfimp - Win32 Debug"

DEP_CPP_STRUT=\
	"..\..\..\Cv32.mvc\Include\gc.h"\
	".\Dxfimp.hpp"\
	".\Dxfimp.hr"\
	".\DxfImpConfig.h"\
	".\Dxfimpif.hpp"\
	".\Optparam.hpp"\
	".\Pheader.hpp"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\hpp\errcodesodbc.hxx"\
	{$(INCLUDE)}"\hpp\protos.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\ospace\sync\counting.h"\
	{$(INCLUDE)}"\ospace\sync\counting.ipp"\
	{$(INCLUDE)}"\ospace\sync\critical.h"\
	{$(INCLUDE)}"\ospace\sync\critical.ipp"\
	{$(INCLUDE)}"\ospace\sync\eventsem.h"\
	{$(INCLUDE)}"\ospace\sync\eventsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\lock.h"\
	{$(INCLUDE)}"\ospace\sync\lock.ipp"\
	{$(INCLUDE)}"\ospace\sync\monitor.h"\
	{$(INCLUDE)}"\ospace\sync\monitor.ipp"\
	{$(INCLUDE)}"\ospace\sync\mutex.h"\
	{$(INCLUDE)}"\ospace\sync\mutex.ipp"\
	{$(INCLUDE)}"\ospace\sync\rfifo.h"\
	{$(INCLUDE)}"\ospace\sync\rpriority.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.ipp"\
	{$(INCLUDE)}"\ospace\sync\rwsem.h"\
	{$(INCLUDE)}"\ospace\sync\rwsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\sentinel.h"\
	{$(INCLUDE)}"\ospace\sync\sentinel.ipp"\
	{$(INCLUDE)}"\ospace\sync\sfifo.h"\
	{$(INCLUDE)}"\ospace\sync\simple.h"\
	{$(INCLUDE)}"\ospace\sync\spriority.h"\
	{$(INCLUDE)}"\ospace\thread\_startup.h"\
	{$(INCLUDE)}"\ospace\thread\priority.h"\
	{$(INCLUDE)}"\ospace\thread\thisthrd.h"\
	{$(INCLUDE)}"\ospace\thread\thread.h"\
	{$(INCLUDE)}"\ospace\thread\thread.ipp"\
	{$(INCLUDE)}"\ospace\thread\types.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\syncthrdcs.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_STRUT=\
	".\win16\DXFIMP.h"\
	

"$(INTDIR)\STRUTIL.OBJ" : $(SOURCE) $(DEP_CPP_STRUT) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"

"$(INTDIR)\STRUTIL.SBR" : $(SOURCE) $(DEP_CPP_STRUT) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\RECHSTAT.CPP

!IF  "$(CFG)" == "Dxfimp - Win32 Release"

DEP_CPP_RECHS=\
	"..\..\..\Cv32.mvc\Include\gc.h"\
	".\Dxfimp.hpp"\
	".\Dxfimp.hr"\
	".\DxfImpConfig.h"\
	".\Dxfimpif.hpp"\
	".\Optparam.hpp"\
	".\Pheader.hpp"\
	".\RECHSTAT.HPP"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\hpp\errcodesodbc.hxx"\
	{$(INCLUDE)}"\hpp\protos.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\ospace\sync\counting.h"\
	{$(INCLUDE)}"\ospace\sync\counting.ipp"\
	{$(INCLUDE)}"\ospace\sync\critical.h"\
	{$(INCLUDE)}"\ospace\sync\critical.ipp"\
	{$(INCLUDE)}"\ospace\sync\eventsem.h"\
	{$(INCLUDE)}"\ospace\sync\lock.h"\
	{$(INCLUDE)}"\ospace\sync\lock.ipp"\
	{$(INCLUDE)}"\ospace\sync\monitor.h"\
	{$(INCLUDE)}"\ospace\sync\monitor.ipp"\
	{$(INCLUDE)}"\ospace\sync\mutex.h"\
	{$(INCLUDE)}"\ospace\sync\mutex.ipp"\
	{$(INCLUDE)}"\ospace\sync\rfifo.h"\
	{$(INCLUDE)}"\ospace\sync\rpriority.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.ipp"\
	{$(INCLUDE)}"\ospace\sync\rwsem.h"\
	{$(INCLUDE)}"\ospace\sync\rwsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\sentinel.h"\
	{$(INCLUDE)}"\ospace\sync\sentinel.ipp"\
	{$(INCLUDE)}"\ospace\sync\sfifo.h"\
	{$(INCLUDE)}"\ospace\sync\simple.h"\
	{$(INCLUDE)}"\ospace\sync\spriority.h"\
	{$(INCLUDE)}"\ospace\thread\_startup.h"\
	{$(INCLUDE)}"\ospace\thread\priority.h"\
	{$(INCLUDE)}"\ospace\thread\thisthrd.h"\
	{$(INCLUDE)}"\ospace\thread\thread.h"\
	{$(INCLUDE)}"\ospace\thread\thread.ipp"\
	{$(INCLUDE)}"\ospace\thread\types.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\syncthrdcs.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_RECHS=\
	".\win16\DXFIMP.h"\
	

"$(INTDIR)\RECHSTAT.OBJ" : $(SOURCE) $(DEP_CPP_RECHS) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"


!ELSEIF  "$(CFG)" == "Dxfimp - Win32 Debug"

DEP_CPP_RECHS=\
	"..\..\..\Cv32.mvc\Include\gc.h"\
	".\Dxfimp.hpp"\
	".\Dxfimp.hr"\
	".\DxfImpConfig.h"\
	".\Dxfimpif.hpp"\
	".\Optparam.hpp"\
	".\Pheader.hpp"\
	".\RECHSTAT.HPP"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\hpp\errcodesodbc.hxx"\
	{$(INCLUDE)}"\hpp\protos.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\ospace\sync\counting.h"\
	{$(INCLUDE)}"\ospace\sync\counting.ipp"\
	{$(INCLUDE)}"\ospace\sync\critical.h"\
	{$(INCLUDE)}"\ospace\sync\critical.ipp"\
	{$(INCLUDE)}"\ospace\sync\eventsem.h"\
	{$(INCLUDE)}"\ospace\sync\eventsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\lock.h"\
	{$(INCLUDE)}"\ospace\sync\lock.ipp"\
	{$(INCLUDE)}"\ospace\sync\monitor.h"\
	{$(INCLUDE)}"\ospace\sync\monitor.ipp"\
	{$(INCLUDE)}"\ospace\sync\mutex.h"\
	{$(INCLUDE)}"\ospace\sync\mutex.ipp"\
	{$(INCLUDE)}"\ospace\sync\rfifo.h"\
	{$(INCLUDE)}"\ospace\sync\rpriority.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.ipp"\
	{$(INCLUDE)}"\ospace\sync\rwsem.h"\
	{$(INCLUDE)}"\ospace\sync\rwsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\sentinel.h"\
	{$(INCLUDE)}"\ospace\sync\sentinel.ipp"\
	{$(INCLUDE)}"\ospace\sync\sfifo.h"\
	{$(INCLUDE)}"\ospace\sync\simple.h"\
	{$(INCLUDE)}"\ospace\sync\spriority.h"\
	{$(INCLUDE)}"\ospace\thread\_startup.h"\
	{$(INCLUDE)}"\ospace\thread\priority.h"\
	{$(INCLUDE)}"\ospace\thread\thisthrd.h"\
	{$(INCLUDE)}"\ospace\thread\thread.h"\
	{$(INCLUDE)}"\ospace\thread\thread.ipp"\
	{$(INCLUDE)}"\ospace\thread\types.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\syncthrdcs.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_RECHS=\
	".\win16\DXFIMP.h"\
	

"$(INTDIR)\RECHSTAT.OBJ" : $(SOURCE) $(DEP_CPP_RECHS) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"

"$(INTDIR)\RECHSTAT.SBR" : $(SOURCE) $(DEP_CPP_RECHS) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\IMPRESLT.CPP

!IF  "$(CFG)" == "Dxfimp - Win32 Release"

DEP_CPP_IMPRE=\
	"..\..\..\Cv32.mvc\Include\gc.h"\
	".\Dxfimp.hpp"\
	".\Dxfimp.hr"\
	".\DxfImpConfig.h"\
	".\Dxfimpif.hpp"\
	".\IMPRESLT.HPP"\
	".\Optparam.hpp"\
	".\Pheader.hpp"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\hpp\errcodesodbc.hxx"\
	{$(INCLUDE)}"\hpp\protos.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\ospace\sync\counting.h"\
	{$(INCLUDE)}"\ospace\sync\counting.ipp"\
	{$(INCLUDE)}"\ospace\sync\critical.h"\
	{$(INCLUDE)}"\ospace\sync\critical.ipp"\
	{$(INCLUDE)}"\ospace\sync\eventsem.h"\
	{$(INCLUDE)}"\ospace\sync\lock.h"\
	{$(INCLUDE)}"\ospace\sync\lock.ipp"\
	{$(INCLUDE)}"\ospace\sync\monitor.h"\
	{$(INCLUDE)}"\ospace\sync\monitor.ipp"\
	{$(INCLUDE)}"\ospace\sync\mutex.h"\
	{$(INCLUDE)}"\ospace\sync\mutex.ipp"\
	{$(INCLUDE)}"\ospace\sync\rfifo.h"\
	{$(INCLUDE)}"\ospace\sync\rpriority.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.ipp"\
	{$(INCLUDE)}"\ospace\sync\rwsem.h"\
	{$(INCLUDE)}"\ospace\sync\rwsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\sentinel.h"\
	{$(INCLUDE)}"\ospace\sync\sentinel.ipp"\
	{$(INCLUDE)}"\ospace\sync\sfifo.h"\
	{$(INCLUDE)}"\ospace\sync\simple.h"\
	{$(INCLUDE)}"\ospace\sync\spriority.h"\
	{$(INCLUDE)}"\ospace\thread\_startup.h"\
	{$(INCLUDE)}"\ospace\thread\priority.h"\
	{$(INCLUDE)}"\ospace\thread\thisthrd.h"\
	{$(INCLUDE)}"\ospace\thread\thread.h"\
	{$(INCLUDE)}"\ospace\thread\thread.ipp"\
	{$(INCLUDE)}"\ospace\thread\types.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\syncthrdcs.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_IMPRE=\
	".\win16\DXFIMP.h"\
	

"$(INTDIR)\IMPRESLT.OBJ" : $(SOURCE) $(DEP_CPP_IMPRE) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"


!ELSEIF  "$(CFG)" == "Dxfimp - Win32 Debug"

DEP_CPP_IMPRE=\
	"..\..\..\Cv32.mvc\Include\gc.h"\
	".\Dxfimp.hpp"\
	".\Dxfimp.hr"\
	".\DxfImpConfig.h"\
	".\Dxfimpif.hpp"\
	".\IMPRESLT.HPP"\
	".\Optparam.hpp"\
	".\Pheader.hpp"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\hpp\errcodesodbc.hxx"\
	{$(INCLUDE)}"\hpp\protos.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\ospace\sync\counting.h"\
	{$(INCLUDE)}"\ospace\sync\counting.ipp"\
	{$(INCLUDE)}"\ospace\sync\critical.h"\
	{$(INCLUDE)}"\ospace\sync\critical.ipp"\
	{$(INCLUDE)}"\ospace\sync\eventsem.h"\
	{$(INCLUDE)}"\ospace\sync\eventsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\lock.h"\
	{$(INCLUDE)}"\ospace\sync\lock.ipp"\
	{$(INCLUDE)}"\ospace\sync\monitor.h"\
	{$(INCLUDE)}"\ospace\sync\monitor.ipp"\
	{$(INCLUDE)}"\ospace\sync\mutex.h"\
	{$(INCLUDE)}"\ospace\sync\mutex.ipp"\
	{$(INCLUDE)}"\ospace\sync\rfifo.h"\
	{$(INCLUDE)}"\ospace\sync\rpriority.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.ipp"\
	{$(INCLUDE)}"\ospace\sync\rwsem.h"\
	{$(INCLUDE)}"\ospace\sync\rwsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\sentinel.h"\
	{$(INCLUDE)}"\ospace\sync\sentinel.ipp"\
	{$(INCLUDE)}"\ospace\sync\sfifo.h"\
	{$(INCLUDE)}"\ospace\sync\simple.h"\
	{$(INCLUDE)}"\ospace\sync\spriority.h"\
	{$(INCLUDE)}"\ospace\thread\_startup.h"\
	{$(INCLUDE)}"\ospace\thread\priority.h"\
	{$(INCLUDE)}"\ospace\thread\thisthrd.h"\
	{$(INCLUDE)}"\ospace\thread\thread.h"\
	{$(INCLUDE)}"\ospace\thread\thread.ipp"\
	{$(INCLUDE)}"\ospace\thread\types.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\syncthrdcs.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_IMPRE=\
	".\win16\DXFIMP.h"\
	

"$(INTDIR)\IMPRESLT.OBJ" : $(SOURCE) $(DEP_CPP_IMPRE) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"

"$(INTDIR)\IMPRESLT.SBR" : $(SOURCE) $(DEP_CPP_IMPRE) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TOOLS.CPP

!IF  "$(CFG)" == "Dxfimp - Win32 Release"

DEP_CPP_TOOLS=\
	"..\..\..\Cv32.mvc\Include\gc.h"\
	".\Dxfimp.hpp"\
	".\Dxfimp.hr"\
	".\DxfImpConfig.h"\
	".\Dxfimpif.hpp"\
	".\HEADER.HPP"\
	".\Optparam.hpp"\
	".\Pheader.hpp"\
	".\TOOLS.HPP"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\hpp\errcodesodbc.hxx"\
	{$(INCLUDE)}"\hpp\protos.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\ospace\sync\counting.h"\
	{$(INCLUDE)}"\ospace\sync\counting.ipp"\
	{$(INCLUDE)}"\ospace\sync\critical.h"\
	{$(INCLUDE)}"\ospace\sync\critical.ipp"\
	{$(INCLUDE)}"\ospace\sync\eventsem.h"\
	{$(INCLUDE)}"\ospace\sync\lock.h"\
	{$(INCLUDE)}"\ospace\sync\lock.ipp"\
	{$(INCLUDE)}"\ospace\sync\monitor.h"\
	{$(INCLUDE)}"\ospace\sync\monitor.ipp"\
	{$(INCLUDE)}"\ospace\sync\mutex.h"\
	{$(INCLUDE)}"\ospace\sync\mutex.ipp"\
	{$(INCLUDE)}"\ospace\sync\rfifo.h"\
	{$(INCLUDE)}"\ospace\sync\rpriority.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.ipp"\
	{$(INCLUDE)}"\ospace\sync\rwsem.h"\
	{$(INCLUDE)}"\ospace\sync\rwsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\sentinel.h"\
	{$(INCLUDE)}"\ospace\sync\sentinel.ipp"\
	{$(INCLUDE)}"\ospace\sync\sfifo.h"\
	{$(INCLUDE)}"\ospace\sync\simple.h"\
	{$(INCLUDE)}"\ospace\sync\spriority.h"\
	{$(INCLUDE)}"\ospace\thread\_startup.h"\
	{$(INCLUDE)}"\ospace\thread\priority.h"\
	{$(INCLUDE)}"\ospace\thread\thisthrd.h"\
	{$(INCLUDE)}"\ospace\thread\thread.h"\
	{$(INCLUDE)}"\ospace\thread\thread.ipp"\
	{$(INCLUDE)}"\ospace\thread\types.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\syncthrdcs.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_TOOLS=\
	".\win16\DXFIMP.h"\
	

"$(INTDIR)\TOOLS.OBJ" : $(SOURCE) $(DEP_CPP_TOOLS) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"


!ELSEIF  "$(CFG)" == "Dxfimp - Win32 Debug"

DEP_CPP_TOOLS=\
	"..\..\..\Cv32.mvc\Include\gc.h"\
	".\Dxfimp.hpp"\
	".\Dxfimp.hr"\
	".\DxfImpConfig.h"\
	".\Dxfimpif.hpp"\
	".\HEADER.HPP"\
	".\Optparam.hpp"\
	".\Pheader.hpp"\
	".\TOOLS.HPP"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\hpp\errcodesodbc.hxx"\
	{$(INCLUDE)}"\hpp\protos.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\ospace\sync\counting.h"\
	{$(INCLUDE)}"\ospace\sync\counting.ipp"\
	{$(INCLUDE)}"\ospace\sync\critical.h"\
	{$(INCLUDE)}"\ospace\sync\critical.ipp"\
	{$(INCLUDE)}"\ospace\sync\eventsem.h"\
	{$(INCLUDE)}"\ospace\sync\eventsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\lock.h"\
	{$(INCLUDE)}"\ospace\sync\lock.ipp"\
	{$(INCLUDE)}"\ospace\sync\monitor.h"\
	{$(INCLUDE)}"\ospace\sync\monitor.ipp"\
	{$(INCLUDE)}"\ospace\sync\mutex.h"\
	{$(INCLUDE)}"\ospace\sync\mutex.ipp"\
	{$(INCLUDE)}"\ospace\sync\rfifo.h"\
	{$(INCLUDE)}"\ospace\sync\rpriority.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.ipp"\
	{$(INCLUDE)}"\ospace\sync\rwsem.h"\
	{$(INCLUDE)}"\ospace\sync\rwsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\sentinel.h"\
	{$(INCLUDE)}"\ospace\sync\sentinel.ipp"\
	{$(INCLUDE)}"\ospace\sync\sfifo.h"\
	{$(INCLUDE)}"\ospace\sync\simple.h"\
	{$(INCLUDE)}"\ospace\sync\spriority.h"\
	{$(INCLUDE)}"\ospace\thread\_startup.h"\
	{$(INCLUDE)}"\ospace\thread\priority.h"\
	{$(INCLUDE)}"\ospace\thread\thisthrd.h"\
	{$(INCLUDE)}"\ospace\thread\thread.h"\
	{$(INCLUDE)}"\ospace\thread\thread.ipp"\
	{$(INCLUDE)}"\ospace\thread\types.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\syncthrdcs.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_TOOLS=\
	".\win16\DXFIMP.h"\
	

"$(INTDIR)\TOOLS.OBJ" : $(SOURCE) $(DEP_CPP_TOOLS) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"

"$(INTDIR)\TOOLS.SBR" : $(SOURCE) $(DEP_CPP_TOOLS) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PUNKTLI.CPP

!IF  "$(CFG)" == "Dxfimp - Win32 Release"

DEP_CPP_PUNKT=\
	"..\..\..\Cv32.mvc\Include\gc.h"\
	".\Dxfimp.hpp"\
	".\Dxfimp.hr"\
	".\DxfImpConfig.h"\
	".\Dxfimpif.hpp"\
	".\Optparam.hpp"\
	".\Pheader.hpp"\
	".\PUNKTLI.HPP"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\hpp\errcodesodbc.hxx"\
	{$(INCLUDE)}"\hpp\protos.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\ospace\sync\counting.h"\
	{$(INCLUDE)}"\ospace\sync\counting.ipp"\
	{$(INCLUDE)}"\ospace\sync\critical.h"\
	{$(INCLUDE)}"\ospace\sync\critical.ipp"\
	{$(INCLUDE)}"\ospace\sync\eventsem.h"\
	{$(INCLUDE)}"\ospace\sync\lock.h"\
	{$(INCLUDE)}"\ospace\sync\lock.ipp"\
	{$(INCLUDE)}"\ospace\sync\monitor.h"\
	{$(INCLUDE)}"\ospace\sync\monitor.ipp"\
	{$(INCLUDE)}"\ospace\sync\mutex.h"\
	{$(INCLUDE)}"\ospace\sync\mutex.ipp"\
	{$(INCLUDE)}"\ospace\sync\rfifo.h"\
	{$(INCLUDE)}"\ospace\sync\rpriority.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.ipp"\
	{$(INCLUDE)}"\ospace\sync\rwsem.h"\
	{$(INCLUDE)}"\ospace\sync\rwsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\sentinel.h"\
	{$(INCLUDE)}"\ospace\sync\sentinel.ipp"\
	{$(INCLUDE)}"\ospace\sync\sfifo.h"\
	{$(INCLUDE)}"\ospace\sync\simple.h"\
	{$(INCLUDE)}"\ospace\sync\spriority.h"\
	{$(INCLUDE)}"\ospace\thread\_startup.h"\
	{$(INCLUDE)}"\ospace\thread\priority.h"\
	{$(INCLUDE)}"\ospace\thread\thisthrd.h"\
	{$(INCLUDE)}"\ospace\thread\thread.h"\
	{$(INCLUDE)}"\ospace\thread\thread.ipp"\
	{$(INCLUDE)}"\ospace\thread\types.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\syncthrdcs.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_PUNKT=\
	".\win16\DXFIMP.h"\
	

"$(INTDIR)\PUNKTLI.OBJ" : $(SOURCE) $(DEP_CPP_PUNKT) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"


!ELSEIF  "$(CFG)" == "Dxfimp - Win32 Debug"

DEP_CPP_PUNKT=\
	"..\..\..\Cv32.mvc\Include\gc.h"\
	".\Dxfimp.hpp"\
	".\Dxfimp.hr"\
	".\DxfImpConfig.h"\
	".\Dxfimpif.hpp"\
	".\Optparam.hpp"\
	".\Pheader.hpp"\
	".\PUNKTLI.HPP"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\hpp\errcodesodbc.hxx"\
	{$(INCLUDE)}"\hpp\protos.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\ospace\sync\counting.h"\
	{$(INCLUDE)}"\ospace\sync\counting.ipp"\
	{$(INCLUDE)}"\ospace\sync\critical.h"\
	{$(INCLUDE)}"\ospace\sync\critical.ipp"\
	{$(INCLUDE)}"\ospace\sync\eventsem.h"\
	{$(INCLUDE)}"\ospace\sync\eventsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\lock.h"\
	{$(INCLUDE)}"\ospace\sync\lock.ipp"\
	{$(INCLUDE)}"\ospace\sync\monitor.h"\
	{$(INCLUDE)}"\ospace\sync\monitor.ipp"\
	{$(INCLUDE)}"\ospace\sync\mutex.h"\
	{$(INCLUDE)}"\ospace\sync\mutex.ipp"\
	{$(INCLUDE)}"\ospace\sync\rfifo.h"\
	{$(INCLUDE)}"\ospace\sync\rpriority.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.ipp"\
	{$(INCLUDE)}"\ospace\sync\rwsem.h"\
	{$(INCLUDE)}"\ospace\sync\rwsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\sentinel.h"\
	{$(INCLUDE)}"\ospace\sync\sentinel.ipp"\
	{$(INCLUDE)}"\ospace\sync\sfifo.h"\
	{$(INCLUDE)}"\ospace\sync\simple.h"\
	{$(INCLUDE)}"\ospace\sync\spriority.h"\
	{$(INCLUDE)}"\ospace\thread\_startup.h"\
	{$(INCLUDE)}"\ospace\thread\priority.h"\
	{$(INCLUDE)}"\ospace\thread\thisthrd.h"\
	{$(INCLUDE)}"\ospace\thread\thread.h"\
	{$(INCLUDE)}"\ospace\thread\thread.ipp"\
	{$(INCLUDE)}"\ospace\thread\types.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\syncthrdcs.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_PUNKT=\
	".\win16\DXFIMP.h"\
	

"$(INTDIR)\PUNKTLI.OBJ" : $(SOURCE) $(DEP_CPP_PUNKT) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"

"$(INTDIR)\PUNKTLI.SBR" : $(SOURCE) $(DEP_CPP_PUNKT) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DGEO_OBJ.CPP

!IF  "$(CFG)" == "Dxfimp - Win32 Release"

DEP_CPP_DGEO_=\
	"..\..\..\Cv32.mvc\Include\gc.h"\
	".\BLOCK.HPP"\
	".\BOGEN.HPP"\
	".\DGEO_OBJ.HPP"\
	".\Dxfimp.hpp"\
	".\Dxfimp.hr"\
	".\DxfImpConfig.h"\
	".\Dxfimpif.hpp"\
	".\MERKMAL.HPP"\
	".\Optparam.hpp"\
	".\Pheader.hpp"\
	".\PUNKTLI.HPP"\
	".\TMERKMAL.HPP"\
	".\TOOLS.HPP"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\hpp\errcodesodbc.hxx"\
	{$(INCLUDE)}"\hpp\protos.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\ospace\sync\counting.h"\
	{$(INCLUDE)}"\ospace\sync\counting.ipp"\
	{$(INCLUDE)}"\ospace\sync\critical.h"\
	{$(INCLUDE)}"\ospace\sync\critical.ipp"\
	{$(INCLUDE)}"\ospace\sync\eventsem.h"\
	{$(INCLUDE)}"\ospace\sync\lock.h"\
	{$(INCLUDE)}"\ospace\sync\lock.ipp"\
	{$(INCLUDE)}"\ospace\sync\monitor.h"\
	{$(INCLUDE)}"\ospace\sync\monitor.ipp"\
	{$(INCLUDE)}"\ospace\sync\mutex.h"\
	{$(INCLUDE)}"\ospace\sync\mutex.ipp"\
	{$(INCLUDE)}"\ospace\sync\rfifo.h"\
	{$(INCLUDE)}"\ospace\sync\rpriority.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.ipp"\
	{$(INCLUDE)}"\ospace\sync\rwsem.h"\
	{$(INCLUDE)}"\ospace\sync\rwsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\sentinel.h"\
	{$(INCLUDE)}"\ospace\sync\sentinel.ipp"\
	{$(INCLUDE)}"\ospace\sync\sfifo.h"\
	{$(INCLUDE)}"\ospace\sync\simple.h"\
	{$(INCLUDE)}"\ospace\sync\spriority.h"\
	{$(INCLUDE)}"\ospace\thread\_startup.h"\
	{$(INCLUDE)}"\ospace\thread\priority.h"\
	{$(INCLUDE)}"\ospace\thread\thisthrd.h"\
	{$(INCLUDE)}"\ospace\thread\thread.h"\
	{$(INCLUDE)}"\ospace\thread\thread.ipp"\
	{$(INCLUDE)}"\ospace\thread\types.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\syncthrdcs.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_DGEO_=\
	".\win16\DXFIMP.h"\
	

"$(INTDIR)\DGEO_OBJ.OBJ" : $(SOURCE) $(DEP_CPP_DGEO_) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"


!ELSEIF  "$(CFG)" == "Dxfimp - Win32 Debug"

DEP_CPP_DGEO_=\
	"..\..\..\Cv32.mvc\Include\gc.h"\
	".\BLOCK.HPP"\
	".\BOGEN.HPP"\
	".\DGEO_OBJ.HPP"\
	".\Dxfimp.hpp"\
	".\Dxfimp.hr"\
	".\DxfImpConfig.h"\
	".\Dxfimpif.hpp"\
	".\MERKMAL.HPP"\
	".\Optparam.hpp"\
	".\Pheader.hpp"\
	".\PUNKTLI.HPP"\
	".\TMERKMAL.HPP"\
	".\TOOLS.HPP"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\hpp\errcodesodbc.hxx"\
	{$(INCLUDE)}"\hpp\protos.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\ospace\sync\counting.h"\
	{$(INCLUDE)}"\ospace\sync\counting.ipp"\
	{$(INCLUDE)}"\ospace\sync\critical.h"\
	{$(INCLUDE)}"\ospace\sync\critical.ipp"\
	{$(INCLUDE)}"\ospace\sync\eventsem.h"\
	{$(INCLUDE)}"\ospace\sync\eventsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\lock.h"\
	{$(INCLUDE)}"\ospace\sync\lock.ipp"\
	{$(INCLUDE)}"\ospace\sync\monitor.h"\
	{$(INCLUDE)}"\ospace\sync\monitor.ipp"\
	{$(INCLUDE)}"\ospace\sync\mutex.h"\
	{$(INCLUDE)}"\ospace\sync\mutex.ipp"\
	{$(INCLUDE)}"\ospace\sync\rfifo.h"\
	{$(INCLUDE)}"\ospace\sync\rpriority.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.ipp"\
	{$(INCLUDE)}"\ospace\sync\rwsem.h"\
	{$(INCLUDE)}"\ospace\sync\rwsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\sentinel.h"\
	{$(INCLUDE)}"\ospace\sync\sentinel.ipp"\
	{$(INCLUDE)}"\ospace\sync\sfifo.h"\
	{$(INCLUDE)}"\ospace\sync\simple.h"\
	{$(INCLUDE)}"\ospace\sync\spriority.h"\
	{$(INCLUDE)}"\ospace\thread\_startup.h"\
	{$(INCLUDE)}"\ospace\thread\priority.h"\
	{$(INCLUDE)}"\ospace\thread\thisthrd.h"\
	{$(INCLUDE)}"\ospace\thread\thread.h"\
	{$(INCLUDE)}"\ospace\thread\thread.ipp"\
	{$(INCLUDE)}"\ospace\thread\types.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\syncthrdcs.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_DGEO_=\
	".\win16\DXFIMP.h"\
	

"$(INTDIR)\DGEO_OBJ.OBJ" : $(SOURCE) $(DEP_CPP_DGEO_) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"

"$(INTDIR)\DGEO_OBJ.SBR" : $(SOURCE) $(DEP_CPP_DGEO_) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\BOGEN.CPP

!IF  "$(CFG)" == "Dxfimp - Win32 Release"

DEP_CPP_BOGEN=\
	"..\..\..\Cv32.mvc\Include\gc.h"\
	".\BOGEN.HPP"\
	".\Dxfimp.hpp"\
	".\Dxfimp.hr"\
	".\DxfImpConfig.h"\
	".\Dxfimpif.hpp"\
	".\Optparam.hpp"\
	".\Pheader.hpp"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\hpp\errcodesodbc.hxx"\
	{$(INCLUDE)}"\hpp\protos.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\ospace\sync\counting.h"\
	{$(INCLUDE)}"\ospace\sync\counting.ipp"\
	{$(INCLUDE)}"\ospace\sync\critical.h"\
	{$(INCLUDE)}"\ospace\sync\critical.ipp"\
	{$(INCLUDE)}"\ospace\sync\eventsem.h"\
	{$(INCLUDE)}"\ospace\sync\lock.h"\
	{$(INCLUDE)}"\ospace\sync\lock.ipp"\
	{$(INCLUDE)}"\ospace\sync\monitor.h"\
	{$(INCLUDE)}"\ospace\sync\monitor.ipp"\
	{$(INCLUDE)}"\ospace\sync\mutex.h"\
	{$(INCLUDE)}"\ospace\sync\mutex.ipp"\
	{$(INCLUDE)}"\ospace\sync\rfifo.h"\
	{$(INCLUDE)}"\ospace\sync\rpriority.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.ipp"\
	{$(INCLUDE)}"\ospace\sync\rwsem.h"\
	{$(INCLUDE)}"\ospace\sync\rwsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\sentinel.h"\
	{$(INCLUDE)}"\ospace\sync\sentinel.ipp"\
	{$(INCLUDE)}"\ospace\sync\sfifo.h"\
	{$(INCLUDE)}"\ospace\sync\simple.h"\
	{$(INCLUDE)}"\ospace\sync\spriority.h"\
	{$(INCLUDE)}"\ospace\thread\_startup.h"\
	{$(INCLUDE)}"\ospace\thread\priority.h"\
	{$(INCLUDE)}"\ospace\thread\thisthrd.h"\
	{$(INCLUDE)}"\ospace\thread\thread.h"\
	{$(INCLUDE)}"\ospace\thread\thread.ipp"\
	{$(INCLUDE)}"\ospace\thread\types.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\syncthrdcs.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_BOGEN=\
	".\win16\DXFIMP.h"\
	

"$(INTDIR)\BOGEN.OBJ" : $(SOURCE) $(DEP_CPP_BOGEN) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"


!ELSEIF  "$(CFG)" == "Dxfimp - Win32 Debug"

DEP_CPP_BOGEN=\
	"..\..\..\Cv32.mvc\Include\gc.h"\
	".\BOGEN.HPP"\
	".\Dxfimp.hpp"\
	".\Dxfimp.hr"\
	".\DxfImpConfig.h"\
	".\Dxfimpif.hpp"\
	".\Optparam.hpp"\
	".\Pheader.hpp"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\hpp\errcodesodbc.hxx"\
	{$(INCLUDE)}"\hpp\protos.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\ospace\sync\counting.h"\
	{$(INCLUDE)}"\ospace\sync\counting.ipp"\
	{$(INCLUDE)}"\ospace\sync\critical.h"\
	{$(INCLUDE)}"\ospace\sync\critical.ipp"\
	{$(INCLUDE)}"\ospace\sync\eventsem.h"\
	{$(INCLUDE)}"\ospace\sync\eventsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\lock.h"\
	{$(INCLUDE)}"\ospace\sync\lock.ipp"\
	{$(INCLUDE)}"\ospace\sync\monitor.h"\
	{$(INCLUDE)}"\ospace\sync\monitor.ipp"\
	{$(INCLUDE)}"\ospace\sync\mutex.h"\
	{$(INCLUDE)}"\ospace\sync\mutex.ipp"\
	{$(INCLUDE)}"\ospace\sync\rfifo.h"\
	{$(INCLUDE)}"\ospace\sync\rpriority.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.ipp"\
	{$(INCLUDE)}"\ospace\sync\rwsem.h"\
	{$(INCLUDE)}"\ospace\sync\rwsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\sentinel.h"\
	{$(INCLUDE)}"\ospace\sync\sentinel.ipp"\
	{$(INCLUDE)}"\ospace\sync\sfifo.h"\
	{$(INCLUDE)}"\ospace\sync\simple.h"\
	{$(INCLUDE)}"\ospace\sync\spriority.h"\
	{$(INCLUDE)}"\ospace\thread\_startup.h"\
	{$(INCLUDE)}"\ospace\thread\priority.h"\
	{$(INCLUDE)}"\ospace\thread\thisthrd.h"\
	{$(INCLUDE)}"\ospace\thread\thread.h"\
	{$(INCLUDE)}"\ospace\thread\thread.ipp"\
	{$(INCLUDE)}"\ospace\thread\types.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\syncthrdcs.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_BOGEN=\
	".\win16\DXFIMP.h"\
	

"$(INTDIR)\BOGEN.OBJ" : $(SOURCE) $(DEP_CPP_BOGEN) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"

"$(INTDIR)\BOGEN.SBR" : $(SOURCE) $(DEP_CPP_BOGEN) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TMERKMAL.CPP

!IF  "$(CFG)" == "Dxfimp - Win32 Release"

DEP_CPP_TMERK=\
	"..\..\..\Cv32.mvc\Include\gc.h"\
	".\Dxfimp.hpp"\
	".\Dxfimp.hr"\
	".\DxfImpConfig.h"\
	".\Dxfimpif.hpp"\
	".\Optparam.hpp"\
	".\Pheader.hpp"\
	".\TMERKMAL.HPP"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\hpp\errcodesodbc.hxx"\
	{$(INCLUDE)}"\hpp\protos.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\ospace\sync\counting.h"\
	{$(INCLUDE)}"\ospace\sync\counting.ipp"\
	{$(INCLUDE)}"\ospace\sync\critical.h"\
	{$(INCLUDE)}"\ospace\sync\critical.ipp"\
	{$(INCLUDE)}"\ospace\sync\eventsem.h"\
	{$(INCLUDE)}"\ospace\sync\lock.h"\
	{$(INCLUDE)}"\ospace\sync\lock.ipp"\
	{$(INCLUDE)}"\ospace\sync\monitor.h"\
	{$(INCLUDE)}"\ospace\sync\monitor.ipp"\
	{$(INCLUDE)}"\ospace\sync\mutex.h"\
	{$(INCLUDE)}"\ospace\sync\mutex.ipp"\
	{$(INCLUDE)}"\ospace\sync\rfifo.h"\
	{$(INCLUDE)}"\ospace\sync\rpriority.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.ipp"\
	{$(INCLUDE)}"\ospace\sync\rwsem.h"\
	{$(INCLUDE)}"\ospace\sync\rwsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\sentinel.h"\
	{$(INCLUDE)}"\ospace\sync\sentinel.ipp"\
	{$(INCLUDE)}"\ospace\sync\sfifo.h"\
	{$(INCLUDE)}"\ospace\sync\simple.h"\
	{$(INCLUDE)}"\ospace\sync\spriority.h"\
	{$(INCLUDE)}"\ospace\thread\_startup.h"\
	{$(INCLUDE)}"\ospace\thread\priority.h"\
	{$(INCLUDE)}"\ospace\thread\thisthrd.h"\
	{$(INCLUDE)}"\ospace\thread\thread.h"\
	{$(INCLUDE)}"\ospace\thread\thread.ipp"\
	{$(INCLUDE)}"\ospace\thread\types.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\syncthrdcs.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_TMERK=\
	".\win16\DXFIMP.h"\
	

"$(INTDIR)\TMERKMAL.OBJ" : $(SOURCE) $(DEP_CPP_TMERK) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"


!ELSEIF  "$(CFG)" == "Dxfimp - Win32 Debug"

DEP_CPP_TMERK=\
	"..\..\..\Cv32.mvc\Include\gc.h"\
	".\Dxfimp.hpp"\
	".\Dxfimp.hr"\
	".\DxfImpConfig.h"\
	".\Dxfimpif.hpp"\
	".\Optparam.hpp"\
	".\Pheader.hpp"\
	".\TMERKMAL.HPP"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\hpp\errcodesodbc.hxx"\
	{$(INCLUDE)}"\hpp\protos.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\ospace\sync\counting.h"\
	{$(INCLUDE)}"\ospace\sync\counting.ipp"\
	{$(INCLUDE)}"\ospace\sync\critical.h"\
	{$(INCLUDE)}"\ospace\sync\critical.ipp"\
	{$(INCLUDE)}"\ospace\sync\eventsem.h"\
	{$(INCLUDE)}"\ospace\sync\eventsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\lock.h"\
	{$(INCLUDE)}"\ospace\sync\lock.ipp"\
	{$(INCLUDE)}"\ospace\sync\monitor.h"\
	{$(INCLUDE)}"\ospace\sync\monitor.ipp"\
	{$(INCLUDE)}"\ospace\sync\mutex.h"\
	{$(INCLUDE)}"\ospace\sync\mutex.ipp"\
	{$(INCLUDE)}"\ospace\sync\rfifo.h"\
	{$(INCLUDE)}"\ospace\sync\rpriority.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.ipp"\
	{$(INCLUDE)}"\ospace\sync\rwsem.h"\
	{$(INCLUDE)}"\ospace\sync\rwsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\sentinel.h"\
	{$(INCLUDE)}"\ospace\sync\sentinel.ipp"\
	{$(INCLUDE)}"\ospace\sync\sfifo.h"\
	{$(INCLUDE)}"\ospace\sync\simple.h"\
	{$(INCLUDE)}"\ospace\sync\spriority.h"\
	{$(INCLUDE)}"\ospace\thread\_startup.h"\
	{$(INCLUDE)}"\ospace\thread\priority.h"\
	{$(INCLUDE)}"\ospace\thread\thisthrd.h"\
	{$(INCLUDE)}"\ospace\thread\thread.h"\
	{$(INCLUDE)}"\ospace\thread\thread.ipp"\
	{$(INCLUDE)}"\ospace\thread\types.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\syncthrdcs.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_TMERK=\
	".\win16\DXFIMP.h"\
	

"$(INTDIR)\TMERKMAL.OBJ" : $(SOURCE) $(DEP_CPP_TMERK) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"

"$(INTDIR)\TMERKMAL.SBR" : $(SOURCE) $(DEP_CPP_TMERK) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MERKMAL.CPP

!IF  "$(CFG)" == "Dxfimp - Win32 Release"

DEP_CPP_MERKM=\
	"..\..\..\Cv32.mvc\Include\gc.h"\
	".\Dxfimp.hpp"\
	".\Dxfimp.hr"\
	".\DxfImpConfig.h"\
	".\Dxfimpif.hpp"\
	".\MERKMAL.HPP"\
	".\Optparam.hpp"\
	".\Pheader.hpp"\
	".\TMERKMAL.HPP"\
	".\TOOLS.HPP"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\hpp\errcodesodbc.hxx"\
	{$(INCLUDE)}"\hpp\protos.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\ospace\sync\counting.h"\
	{$(INCLUDE)}"\ospace\sync\counting.ipp"\
	{$(INCLUDE)}"\ospace\sync\critical.h"\
	{$(INCLUDE)}"\ospace\sync\critical.ipp"\
	{$(INCLUDE)}"\ospace\sync\eventsem.h"\
	{$(INCLUDE)}"\ospace\sync\lock.h"\
	{$(INCLUDE)}"\ospace\sync\lock.ipp"\
	{$(INCLUDE)}"\ospace\sync\monitor.h"\
	{$(INCLUDE)}"\ospace\sync\monitor.ipp"\
	{$(INCLUDE)}"\ospace\sync\mutex.h"\
	{$(INCLUDE)}"\ospace\sync\mutex.ipp"\
	{$(INCLUDE)}"\ospace\sync\rfifo.h"\
	{$(INCLUDE)}"\ospace\sync\rpriority.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.ipp"\
	{$(INCLUDE)}"\ospace\sync\rwsem.h"\
	{$(INCLUDE)}"\ospace\sync\rwsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\sentinel.h"\
	{$(INCLUDE)}"\ospace\sync\sentinel.ipp"\
	{$(INCLUDE)}"\ospace\sync\sfifo.h"\
	{$(INCLUDE)}"\ospace\sync\simple.h"\
	{$(INCLUDE)}"\ospace\sync\spriority.h"\
	{$(INCLUDE)}"\ospace\thread\_startup.h"\
	{$(INCLUDE)}"\ospace\thread\priority.h"\
	{$(INCLUDE)}"\ospace\thread\thisthrd.h"\
	{$(INCLUDE)}"\ospace\thread\thread.h"\
	{$(INCLUDE)}"\ospace\thread\thread.ipp"\
	{$(INCLUDE)}"\ospace\thread\types.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\syncthrdcs.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_MERKM=\
	".\win16\DXFIMP.h"\
	

"$(INTDIR)\MERKMAL.OBJ" : $(SOURCE) $(DEP_CPP_MERKM) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"


!ELSEIF  "$(CFG)" == "Dxfimp - Win32 Debug"

DEP_CPP_MERKM=\
	"..\..\..\Cv32.mvc\Include\gc.h"\
	".\Dxfimp.hpp"\
	".\Dxfimp.hr"\
	".\DxfImpConfig.h"\
	".\Dxfimpif.hpp"\
	".\MERKMAL.HPP"\
	".\Optparam.hpp"\
	".\Pheader.hpp"\
	".\TMERKMAL.HPP"\
	".\TOOLS.HPP"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\hpp\errcodesodbc.hxx"\
	{$(INCLUDE)}"\hpp\protos.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\ospace\sync\counting.h"\
	{$(INCLUDE)}"\ospace\sync\counting.ipp"\
	{$(INCLUDE)}"\ospace\sync\critical.h"\
	{$(INCLUDE)}"\ospace\sync\critical.ipp"\
	{$(INCLUDE)}"\ospace\sync\eventsem.h"\
	{$(INCLUDE)}"\ospace\sync\eventsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\lock.h"\
	{$(INCLUDE)}"\ospace\sync\lock.ipp"\
	{$(INCLUDE)}"\ospace\sync\monitor.h"\
	{$(INCLUDE)}"\ospace\sync\monitor.ipp"\
	{$(INCLUDE)}"\ospace\sync\mutex.h"\
	{$(INCLUDE)}"\ospace\sync\mutex.ipp"\
	{$(INCLUDE)}"\ospace\sync\rfifo.h"\
	{$(INCLUDE)}"\ospace\sync\rpriority.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.ipp"\
	{$(INCLUDE)}"\ospace\sync\rwsem.h"\
	{$(INCLUDE)}"\ospace\sync\rwsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\sentinel.h"\
	{$(INCLUDE)}"\ospace\sync\sentinel.ipp"\
	{$(INCLUDE)}"\ospace\sync\sfifo.h"\
	{$(INCLUDE)}"\ospace\sync\simple.h"\
	{$(INCLUDE)}"\ospace\sync\spriority.h"\
	{$(INCLUDE)}"\ospace\thread\_startup.h"\
	{$(INCLUDE)}"\ospace\thread\priority.h"\
	{$(INCLUDE)}"\ospace\thread\thisthrd.h"\
	{$(INCLUDE)}"\ospace\thread\thread.h"\
	{$(INCLUDE)}"\ospace\thread\thread.ipp"\
	{$(INCLUDE)}"\ospace\thread\types.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\syncthrdcs.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_MERKM=\
	".\win16\DXFIMP.h"\
	

"$(INTDIR)\MERKMAL.OBJ" : $(SOURCE) $(DEP_CPP_MERKM) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"

"$(INTDIR)\MERKMAL.SBR" : $(SOURCE) $(DEP_CPP_MERKM) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\HELPTEXT.CPP

!IF  "$(CFG)" == "Dxfimp - Win32 Release"

DEP_CPP_HELPT=\
	"..\..\..\Cv32.mvc\Include\gc.h"\
	".\Dxfimp.hpp"\
	".\Dxfimp.hr"\
	".\DxfImpConfig.h"\
	".\Dxfimpif.hpp"\
	".\HELPTEXT.HPP"\
	".\Optparam.hpp"\
	".\Pheader.hpp"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\hpp\errcodesodbc.hxx"\
	{$(INCLUDE)}"\hpp\protos.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\ospace\sync\counting.h"\
	{$(INCLUDE)}"\ospace\sync\counting.ipp"\
	{$(INCLUDE)}"\ospace\sync\critical.h"\
	{$(INCLUDE)}"\ospace\sync\critical.ipp"\
	{$(INCLUDE)}"\ospace\sync\eventsem.h"\
	{$(INCLUDE)}"\ospace\sync\lock.h"\
	{$(INCLUDE)}"\ospace\sync\lock.ipp"\
	{$(INCLUDE)}"\ospace\sync\monitor.h"\
	{$(INCLUDE)}"\ospace\sync\monitor.ipp"\
	{$(INCLUDE)}"\ospace\sync\mutex.h"\
	{$(INCLUDE)}"\ospace\sync\mutex.ipp"\
	{$(INCLUDE)}"\ospace\sync\rfifo.h"\
	{$(INCLUDE)}"\ospace\sync\rpriority.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.ipp"\
	{$(INCLUDE)}"\ospace\sync\rwsem.h"\
	{$(INCLUDE)}"\ospace\sync\rwsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\sentinel.h"\
	{$(INCLUDE)}"\ospace\sync\sentinel.ipp"\
	{$(INCLUDE)}"\ospace\sync\sfifo.h"\
	{$(INCLUDE)}"\ospace\sync\simple.h"\
	{$(INCLUDE)}"\ospace\sync\spriority.h"\
	{$(INCLUDE)}"\ospace\thread\_startup.h"\
	{$(INCLUDE)}"\ospace\thread\priority.h"\
	{$(INCLUDE)}"\ospace\thread\thisthrd.h"\
	{$(INCLUDE)}"\ospace\thread\thread.h"\
	{$(INCLUDE)}"\ospace\thread\thread.ipp"\
	{$(INCLUDE)}"\ospace\thread\types.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\syncthrdcs.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_HELPT=\
	".\win16\DXFIMP.h"\
	

"$(INTDIR)\HELPTEXT.OBJ" : $(SOURCE) $(DEP_CPP_HELPT) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"


!ELSEIF  "$(CFG)" == "Dxfimp - Win32 Debug"

DEP_CPP_HELPT=\
	"..\..\..\Cv32.mvc\Include\gc.h"\
	".\Dxfimp.hpp"\
	".\Dxfimp.hr"\
	".\DxfImpConfig.h"\
	".\Dxfimpif.hpp"\
	".\HELPTEXT.HPP"\
	".\Optparam.hpp"\
	".\Pheader.hpp"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\hpp\errcodesodbc.hxx"\
	{$(INCLUDE)}"\hpp\protos.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\ospace\sync\counting.h"\
	{$(INCLUDE)}"\ospace\sync\counting.ipp"\
	{$(INCLUDE)}"\ospace\sync\critical.h"\
	{$(INCLUDE)}"\ospace\sync\critical.ipp"\
	{$(INCLUDE)}"\ospace\sync\eventsem.h"\
	{$(INCLUDE)}"\ospace\sync\eventsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\lock.h"\
	{$(INCLUDE)}"\ospace\sync\lock.ipp"\
	{$(INCLUDE)}"\ospace\sync\monitor.h"\
	{$(INCLUDE)}"\ospace\sync\monitor.ipp"\
	{$(INCLUDE)}"\ospace\sync\mutex.h"\
	{$(INCLUDE)}"\ospace\sync\mutex.ipp"\
	{$(INCLUDE)}"\ospace\sync\rfifo.h"\
	{$(INCLUDE)}"\ospace\sync\rpriority.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.ipp"\
	{$(INCLUDE)}"\ospace\sync\rwsem.h"\
	{$(INCLUDE)}"\ospace\sync\rwsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\sentinel.h"\
	{$(INCLUDE)}"\ospace\sync\sentinel.ipp"\
	{$(INCLUDE)}"\ospace\sync\sfifo.h"\
	{$(INCLUDE)}"\ospace\sync\simple.h"\
	{$(INCLUDE)}"\ospace\sync\spriority.h"\
	{$(INCLUDE)}"\ospace\thread\_startup.h"\
	{$(INCLUDE)}"\ospace\thread\priority.h"\
	{$(INCLUDE)}"\ospace\thread\thisthrd.h"\
	{$(INCLUDE)}"\ospace\thread\thread.h"\
	{$(INCLUDE)}"\ospace\thread\thread.ipp"\
	{$(INCLUDE)}"\ospace\thread\types.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\syncthrdcs.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_HELPT=\
	".\win16\DXFIMP.h"\
	

"$(INTDIR)\HELPTEXT.OBJ" : $(SOURCE) $(DEP_CPP_HELPT) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"

"$(INTDIR)\HELPTEXT.SBR" : $(SOURCE) $(DEP_CPP_HELPT) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\NUMEDIT.CPP

!IF  "$(CFG)" == "Dxfimp - Win32 Release"

DEP_CPP_NUMED=\
	"..\..\..\Cv32.mvc\Include\gc.h"\
	".\Dxfimp.hpp"\
	".\Dxfimp.hr"\
	".\DxfImpConfig.h"\
	".\Dxfimpif.hpp"\
	".\NUMEDIT.HPP"\
	".\Optparam.hpp"\
	".\Pheader.hpp"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\hpp\errcodesodbc.hxx"\
	{$(INCLUDE)}"\hpp\protos.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\ospace\sync\counting.h"\
	{$(INCLUDE)}"\ospace\sync\counting.ipp"\
	{$(INCLUDE)}"\ospace\sync\critical.h"\
	{$(INCLUDE)}"\ospace\sync\critical.ipp"\
	{$(INCLUDE)}"\ospace\sync\eventsem.h"\
	{$(INCLUDE)}"\ospace\sync\lock.h"\
	{$(INCLUDE)}"\ospace\sync\lock.ipp"\
	{$(INCLUDE)}"\ospace\sync\monitor.h"\
	{$(INCLUDE)}"\ospace\sync\monitor.ipp"\
	{$(INCLUDE)}"\ospace\sync\mutex.h"\
	{$(INCLUDE)}"\ospace\sync\mutex.ipp"\
	{$(INCLUDE)}"\ospace\sync\rfifo.h"\
	{$(INCLUDE)}"\ospace\sync\rpriority.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.ipp"\
	{$(INCLUDE)}"\ospace\sync\rwsem.h"\
	{$(INCLUDE)}"\ospace\sync\rwsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\sentinel.h"\
	{$(INCLUDE)}"\ospace\sync\sentinel.ipp"\
	{$(INCLUDE)}"\ospace\sync\sfifo.h"\
	{$(INCLUDE)}"\ospace\sync\simple.h"\
	{$(INCLUDE)}"\ospace\sync\spriority.h"\
	{$(INCLUDE)}"\ospace\thread\_startup.h"\
	{$(INCLUDE)}"\ospace\thread\priority.h"\
	{$(INCLUDE)}"\ospace\thread\thisthrd.h"\
	{$(INCLUDE)}"\ospace\thread\thread.h"\
	{$(INCLUDE)}"\ospace\thread\thread.ipp"\
	{$(INCLUDE)}"\ospace\thread\types.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\syncthrdcs.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_NUMED=\
	".\win16\DXFIMP.h"\
	

"$(INTDIR)\NUMEDIT.OBJ" : $(SOURCE) $(DEP_CPP_NUMED) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"


!ELSEIF  "$(CFG)" == "Dxfimp - Win32 Debug"

DEP_CPP_NUMED=\
	"..\..\..\Cv32.mvc\Include\gc.h"\
	".\Dxfimp.hpp"\
	".\Dxfimp.hr"\
	".\DxfImpConfig.h"\
	".\Dxfimpif.hpp"\
	".\NUMEDIT.HPP"\
	".\Optparam.hpp"\
	".\Pheader.hpp"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\hpp\errcodesodbc.hxx"\
	{$(INCLUDE)}"\hpp\protos.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\ospace\sync\counting.h"\
	{$(INCLUDE)}"\ospace\sync\counting.ipp"\
	{$(INCLUDE)}"\ospace\sync\critical.h"\
	{$(INCLUDE)}"\ospace\sync\critical.ipp"\
	{$(INCLUDE)}"\ospace\sync\eventsem.h"\
	{$(INCLUDE)}"\ospace\sync\eventsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\lock.h"\
	{$(INCLUDE)}"\ospace\sync\lock.ipp"\
	{$(INCLUDE)}"\ospace\sync\monitor.h"\
	{$(INCLUDE)}"\ospace\sync\monitor.ipp"\
	{$(INCLUDE)}"\ospace\sync\mutex.h"\
	{$(INCLUDE)}"\ospace\sync\mutex.ipp"\
	{$(INCLUDE)}"\ospace\sync\rfifo.h"\
	{$(INCLUDE)}"\ospace\sync\rpriority.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.ipp"\
	{$(INCLUDE)}"\ospace\sync\rwsem.h"\
	{$(INCLUDE)}"\ospace\sync\rwsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\sentinel.h"\
	{$(INCLUDE)}"\ospace\sync\sentinel.ipp"\
	{$(INCLUDE)}"\ospace\sync\sfifo.h"\
	{$(INCLUDE)}"\ospace\sync\simple.h"\
	{$(INCLUDE)}"\ospace\sync\spriority.h"\
	{$(INCLUDE)}"\ospace\thread\_startup.h"\
	{$(INCLUDE)}"\ospace\thread\priority.h"\
	{$(INCLUDE)}"\ospace\thread\thisthrd.h"\
	{$(INCLUDE)}"\ospace\thread\thread.h"\
	{$(INCLUDE)}"\ospace\thread\thread.ipp"\
	{$(INCLUDE)}"\ospace\thread\types.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\syncthrdcs.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_NUMED=\
	".\win16\DXFIMP.h"\
	

"$(INTDIR)\NUMEDIT.OBJ" : $(SOURCE) $(DEP_CPP_NUMED) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"

"$(INTDIR)\NUMEDIT.SBR" : $(SOURCE) $(DEP_CPP_NUMED) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\REALEDIT.CPP

!IF  "$(CFG)" == "Dxfimp - Win32 Release"

DEP_CPP_REALE=\
	"..\..\..\Cv32.mvc\Include\gc.h"\
	".\Dxfimp.hpp"\
	".\Dxfimp.hr"\
	".\DxfImpConfig.h"\
	".\Dxfimpif.hpp"\
	".\NUMEDIT.HPP"\
	".\Optparam.hpp"\
	".\Pheader.hpp"\
	".\REALEDIT.HPP"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\hpp\errcodesodbc.hxx"\
	{$(INCLUDE)}"\hpp\protos.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\ospace\sync\counting.h"\
	{$(INCLUDE)}"\ospace\sync\counting.ipp"\
	{$(INCLUDE)}"\ospace\sync\critical.h"\
	{$(INCLUDE)}"\ospace\sync\critical.ipp"\
	{$(INCLUDE)}"\ospace\sync\eventsem.h"\
	{$(INCLUDE)}"\ospace\sync\lock.h"\
	{$(INCLUDE)}"\ospace\sync\lock.ipp"\
	{$(INCLUDE)}"\ospace\sync\monitor.h"\
	{$(INCLUDE)}"\ospace\sync\monitor.ipp"\
	{$(INCLUDE)}"\ospace\sync\mutex.h"\
	{$(INCLUDE)}"\ospace\sync\mutex.ipp"\
	{$(INCLUDE)}"\ospace\sync\rfifo.h"\
	{$(INCLUDE)}"\ospace\sync\rpriority.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.ipp"\
	{$(INCLUDE)}"\ospace\sync\rwsem.h"\
	{$(INCLUDE)}"\ospace\sync\rwsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\sentinel.h"\
	{$(INCLUDE)}"\ospace\sync\sentinel.ipp"\
	{$(INCLUDE)}"\ospace\sync\sfifo.h"\
	{$(INCLUDE)}"\ospace\sync\simple.h"\
	{$(INCLUDE)}"\ospace\sync\spriority.h"\
	{$(INCLUDE)}"\ospace\thread\_startup.h"\
	{$(INCLUDE)}"\ospace\thread\priority.h"\
	{$(INCLUDE)}"\ospace\thread\thisthrd.h"\
	{$(INCLUDE)}"\ospace\thread\thread.h"\
	{$(INCLUDE)}"\ospace\thread\thread.ipp"\
	{$(INCLUDE)}"\ospace\thread\types.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\syncthrdcs.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_REALE=\
	".\win16\DXFIMP.h"\
	

"$(INTDIR)\REALEDIT.OBJ" : $(SOURCE) $(DEP_CPP_REALE) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"


!ELSEIF  "$(CFG)" == "Dxfimp - Win32 Debug"

DEP_CPP_REALE=\
	"..\..\..\Cv32.mvc\Include\gc.h"\
	".\Dxfimp.hpp"\
	".\Dxfimp.hr"\
	".\DxfImpConfig.h"\
	".\Dxfimpif.hpp"\
	".\NUMEDIT.HPP"\
	".\Optparam.hpp"\
	".\Pheader.hpp"\
	".\REALEDIT.HPP"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\hpp\errcodesodbc.hxx"\
	{$(INCLUDE)}"\hpp\protos.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\ospace\sync\counting.h"\
	{$(INCLUDE)}"\ospace\sync\counting.ipp"\
	{$(INCLUDE)}"\ospace\sync\critical.h"\
	{$(INCLUDE)}"\ospace\sync\critical.ipp"\
	{$(INCLUDE)}"\ospace\sync\eventsem.h"\
	{$(INCLUDE)}"\ospace\sync\eventsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\lock.h"\
	{$(INCLUDE)}"\ospace\sync\lock.ipp"\
	{$(INCLUDE)}"\ospace\sync\monitor.h"\
	{$(INCLUDE)}"\ospace\sync\monitor.ipp"\
	{$(INCLUDE)}"\ospace\sync\mutex.h"\
	{$(INCLUDE)}"\ospace\sync\mutex.ipp"\
	{$(INCLUDE)}"\ospace\sync\rfifo.h"\
	{$(INCLUDE)}"\ospace\sync\rpriority.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.ipp"\
	{$(INCLUDE)}"\ospace\sync\rwsem.h"\
	{$(INCLUDE)}"\ospace\sync\rwsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\sentinel.h"\
	{$(INCLUDE)}"\ospace\sync\sentinel.ipp"\
	{$(INCLUDE)}"\ospace\sync\sfifo.h"\
	{$(INCLUDE)}"\ospace\sync\simple.h"\
	{$(INCLUDE)}"\ospace\sync\spriority.h"\
	{$(INCLUDE)}"\ospace\thread\_startup.h"\
	{$(INCLUDE)}"\ospace\thread\priority.h"\
	{$(INCLUDE)}"\ospace\thread\thisthrd.h"\
	{$(INCLUDE)}"\ospace\thread\thread.h"\
	{$(INCLUDE)}"\ospace\thread\thread.ipp"\
	{$(INCLUDE)}"\ospace\thread\types.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\syncthrdcs.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_REALE=\
	".\win16\DXFIMP.h"\
	

"$(INTDIR)\REALEDIT.OBJ" : $(SOURCE) $(DEP_CPP_REALE) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"

"$(INTDIR)\REALEDIT.SBR" : $(SOURCE) $(DEP_CPP_REALE) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\OPTPRDLG.CPP

!IF  "$(CFG)" == "Dxfimp - Win32 Release"

DEP_CPP_OPTPR=\
	"..\..\..\Cv32.mvc\Include\gc.h"\
	".\Dxfimp.hpp"\
	".\Dxfimp.hr"\
	".\DxfImpConfig.h"\
	".\Dxfimpif.hpp"\
	".\HELPTEXT.HPP"\
	".\NUMEDIT.HPP"\
	".\Optparam.hpp"\
	".\OPTPRDLG.HPP"\
	".\Pheader.hpp"\
	".\REALEDIT.HPP"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\hpp\errcodesodbc.hxx"\
	{$(INCLUDE)}"\hpp\protos.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\ospace\sync\counting.h"\
	{$(INCLUDE)}"\ospace\sync\counting.ipp"\
	{$(INCLUDE)}"\ospace\sync\critical.h"\
	{$(INCLUDE)}"\ospace\sync\critical.ipp"\
	{$(INCLUDE)}"\ospace\sync\eventsem.h"\
	{$(INCLUDE)}"\ospace\sync\lock.h"\
	{$(INCLUDE)}"\ospace\sync\lock.ipp"\
	{$(INCLUDE)}"\ospace\sync\monitor.h"\
	{$(INCLUDE)}"\ospace\sync\monitor.ipp"\
	{$(INCLUDE)}"\ospace\sync\mutex.h"\
	{$(INCLUDE)}"\ospace\sync\mutex.ipp"\
	{$(INCLUDE)}"\ospace\sync\rfifo.h"\
	{$(INCLUDE)}"\ospace\sync\rpriority.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.ipp"\
	{$(INCLUDE)}"\ospace\sync\rwsem.h"\
	{$(INCLUDE)}"\ospace\sync\rwsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\sentinel.h"\
	{$(INCLUDE)}"\ospace\sync\sentinel.ipp"\
	{$(INCLUDE)}"\ospace\sync\sfifo.h"\
	{$(INCLUDE)}"\ospace\sync\simple.h"\
	{$(INCLUDE)}"\ospace\sync\spriority.h"\
	{$(INCLUDE)}"\ospace\thread\_startup.h"\
	{$(INCLUDE)}"\ospace\thread\priority.h"\
	{$(INCLUDE)}"\ospace\thread\thisthrd.h"\
	{$(INCLUDE)}"\ospace\thread\thread.h"\
	{$(INCLUDE)}"\ospace\thread\thread.ipp"\
	{$(INCLUDE)}"\ospace\thread\types.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\syncthrdcs.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_OPTPR=\
	".\win16\DXFIMP.h"\
	

"$(INTDIR)\OPTPRDLG.OBJ" : $(SOURCE) $(DEP_CPP_OPTPR) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"


!ELSEIF  "$(CFG)" == "Dxfimp - Win32 Debug"

DEP_CPP_OPTPR=\
	"..\..\..\Cv32.mvc\Include\gc.h"\
	".\Dxfimp.hpp"\
	".\Dxfimp.hr"\
	".\DxfImpConfig.h"\
	".\Dxfimpif.hpp"\
	".\HELPTEXT.HPP"\
	".\NUMEDIT.HPP"\
	".\Optparam.hpp"\
	".\OPTPRDLG.HPP"\
	".\Pheader.hpp"\
	".\REALEDIT.HPP"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\hpp\errcodesodbc.hxx"\
	{$(INCLUDE)}"\hpp\protos.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\ospace\sync\counting.h"\
	{$(INCLUDE)}"\ospace\sync\counting.ipp"\
	{$(INCLUDE)}"\ospace\sync\critical.h"\
	{$(INCLUDE)}"\ospace\sync\critical.ipp"\
	{$(INCLUDE)}"\ospace\sync\eventsem.h"\
	{$(INCLUDE)}"\ospace\sync\eventsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\lock.h"\
	{$(INCLUDE)}"\ospace\sync\lock.ipp"\
	{$(INCLUDE)}"\ospace\sync\monitor.h"\
	{$(INCLUDE)}"\ospace\sync\monitor.ipp"\
	{$(INCLUDE)}"\ospace\sync\mutex.h"\
	{$(INCLUDE)}"\ospace\sync\mutex.ipp"\
	{$(INCLUDE)}"\ospace\sync\rfifo.h"\
	{$(INCLUDE)}"\ospace\sync\rpriority.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.ipp"\
	{$(INCLUDE)}"\ospace\sync\rwsem.h"\
	{$(INCLUDE)}"\ospace\sync\rwsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\sentinel.h"\
	{$(INCLUDE)}"\ospace\sync\sentinel.ipp"\
	{$(INCLUDE)}"\ospace\sync\sfifo.h"\
	{$(INCLUDE)}"\ospace\sync\simple.h"\
	{$(INCLUDE)}"\ospace\sync\spriority.h"\
	{$(INCLUDE)}"\ospace\thread\_startup.h"\
	{$(INCLUDE)}"\ospace\thread\priority.h"\
	{$(INCLUDE)}"\ospace\thread\thisthrd.h"\
	{$(INCLUDE)}"\ospace\thread\thread.h"\
	{$(INCLUDE)}"\ospace\thread\thread.ipp"\
	{$(INCLUDE)}"\ospace\thread\types.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\syncthrdcs.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_OPTPR=\
	".\win16\DXFIMP.h"\
	

"$(INTDIR)\OPTPRDLG.OBJ" : $(SOURCE) $(DEP_CPP_OPTPR) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"

"$(INTDIR)\OPTPRDLG.SBR" : $(SOURCE) $(DEP_CPP_OPTPR) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Licenz.cpp

!IF  "$(CFG)" == "Dxfimp - Win32 Release"

DEP_CPP_LICEN=\
	"..\..\..\Cv32.mvc\Include\gc.h"\
	".\Dxfimp.hpp"\
	".\Dxfimp.hr"\
	".\DxfImpConfig.h"\
	".\Dxfimpif.hpp"\
	".\Optparam.hpp"\
	".\Pheader.hpp"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\hpp\errcodesodbc.hxx"\
	{$(INCLUDE)}"\hpp\protos.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\ospace\sync\counting.h"\
	{$(INCLUDE)}"\ospace\sync\counting.ipp"\
	{$(INCLUDE)}"\ospace\sync\critical.h"\
	{$(INCLUDE)}"\ospace\sync\critical.ipp"\
	{$(INCLUDE)}"\ospace\sync\eventsem.h"\
	{$(INCLUDE)}"\ospace\sync\lock.h"\
	{$(INCLUDE)}"\ospace\sync\lock.ipp"\
	{$(INCLUDE)}"\ospace\sync\monitor.h"\
	{$(INCLUDE)}"\ospace\sync\monitor.ipp"\
	{$(INCLUDE)}"\ospace\sync\mutex.h"\
	{$(INCLUDE)}"\ospace\sync\mutex.ipp"\
	{$(INCLUDE)}"\ospace\sync\rfifo.h"\
	{$(INCLUDE)}"\ospace\sync\rpriority.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.ipp"\
	{$(INCLUDE)}"\ospace\sync\rwsem.h"\
	{$(INCLUDE)}"\ospace\sync\rwsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\sentinel.h"\
	{$(INCLUDE)}"\ospace\sync\sentinel.ipp"\
	{$(INCLUDE)}"\ospace\sync\sfifo.h"\
	{$(INCLUDE)}"\ospace\sync\simple.h"\
	{$(INCLUDE)}"\ospace\sync\spriority.h"\
	{$(INCLUDE)}"\ospace\thread\_startup.h"\
	{$(INCLUDE)}"\ospace\thread\priority.h"\
	{$(INCLUDE)}"\ospace\thread\thisthrd.h"\
	{$(INCLUDE)}"\ospace\thread\thread.h"\
	{$(INCLUDE)}"\ospace\thread\thread.ipp"\
	{$(INCLUDE)}"\ospace\thread\types.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\registrx.hxx"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\syncthrdcs.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_LICEN=\
	".\win16\DXFIMP.h"\
	

"$(INTDIR)\Licenz.obj" : $(SOURCE) $(DEP_CPP_LICEN) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"


!ELSEIF  "$(CFG)" == "Dxfimp - Win32 Debug"

DEP_CPP_LICEN=\
	"..\..\..\Cv32.mvc\Include\gc.h"\
	".\Dxfimp.hpp"\
	".\Dxfimp.hr"\
	".\DxfImpConfig.h"\
	".\Dxfimpif.hpp"\
	".\Optparam.hpp"\
	".\Pheader.hpp"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\hpp\errcodesodbc.hxx"\
	{$(INCLUDE)}"\hpp\protos.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\ospace\sync\counting.h"\
	{$(INCLUDE)}"\ospace\sync\counting.ipp"\
	{$(INCLUDE)}"\ospace\sync\critical.h"\
	{$(INCLUDE)}"\ospace\sync\critical.ipp"\
	{$(INCLUDE)}"\ospace\sync\eventsem.h"\
	{$(INCLUDE)}"\ospace\sync\eventsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\lock.h"\
	{$(INCLUDE)}"\ospace\sync\lock.ipp"\
	{$(INCLUDE)}"\ospace\sync\monitor.h"\
	{$(INCLUDE)}"\ospace\sync\monitor.ipp"\
	{$(INCLUDE)}"\ospace\sync\mutex.h"\
	{$(INCLUDE)}"\ospace\sync\mutex.ipp"\
	{$(INCLUDE)}"\ospace\sync\rfifo.h"\
	{$(INCLUDE)}"\ospace\sync\rpriority.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.ipp"\
	{$(INCLUDE)}"\ospace\sync\rwsem.h"\
	{$(INCLUDE)}"\ospace\sync\rwsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\sentinel.h"\
	{$(INCLUDE)}"\ospace\sync\sentinel.ipp"\
	{$(INCLUDE)}"\ospace\sync\sfifo.h"\
	{$(INCLUDE)}"\ospace\sync\simple.h"\
	{$(INCLUDE)}"\ospace\sync\spriority.h"\
	{$(INCLUDE)}"\ospace\thread\_startup.h"\
	{$(INCLUDE)}"\ospace\thread\priority.h"\
	{$(INCLUDE)}"\ospace\thread\thisthrd.h"\
	{$(INCLUDE)}"\ospace\thread\thread.h"\
	{$(INCLUDE)}"\ospace\thread\thread.ipp"\
	{$(INCLUDE)}"\ospace\thread\types.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\registrx.hxx"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\syncthrdcs.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_LICEN=\
	".\win16\DXFIMP.h"\
	

"$(INTDIR)\Licenz.obj" : $(SOURCE) $(DEP_CPP_LICEN) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"

"$(INTDIR)\Licenz.sbr" : $(SOURCE) $(DEP_CPP_LICEN) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\layers.Cpp

!IF  "$(CFG)" == "Dxfimp - Win32 Release"

DEP_CPP_LAYER=\
	"..\..\..\Cv32.mvc\Include\gc.h"\
	".\Dxfimp.hpp"\
	".\Dxfimp.hr"\
	".\DxfImpConfig.h"\
	".\Dxfimpif.hpp"\
	".\LAYERS.HPP"\
	".\Optparam.hpp"\
	".\Pheader.hpp"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\hpp\errcodesodbc.hxx"\
	{$(INCLUDE)}"\hpp\protos.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\ospace\sync\counting.h"\
	{$(INCLUDE)}"\ospace\sync\counting.ipp"\
	{$(INCLUDE)}"\ospace\sync\critical.h"\
	{$(INCLUDE)}"\ospace\sync\critical.ipp"\
	{$(INCLUDE)}"\ospace\sync\eventsem.h"\
	{$(INCLUDE)}"\ospace\sync\lock.h"\
	{$(INCLUDE)}"\ospace\sync\lock.ipp"\
	{$(INCLUDE)}"\ospace\sync\monitor.h"\
	{$(INCLUDE)}"\ospace\sync\monitor.ipp"\
	{$(INCLUDE)}"\ospace\sync\mutex.h"\
	{$(INCLUDE)}"\ospace\sync\mutex.ipp"\
	{$(INCLUDE)}"\ospace\sync\rfifo.h"\
	{$(INCLUDE)}"\ospace\sync\rpriority.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.ipp"\
	{$(INCLUDE)}"\ospace\sync\rwsem.h"\
	{$(INCLUDE)}"\ospace\sync\rwsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\sentinel.h"\
	{$(INCLUDE)}"\ospace\sync\sentinel.ipp"\
	{$(INCLUDE)}"\ospace\sync\sfifo.h"\
	{$(INCLUDE)}"\ospace\sync\simple.h"\
	{$(INCLUDE)}"\ospace\sync\spriority.h"\
	{$(INCLUDE)}"\ospace\thread\_startup.h"\
	{$(INCLUDE)}"\ospace\thread\priority.h"\
	{$(INCLUDE)}"\ospace\thread\thisthrd.h"\
	{$(INCLUDE)}"\ospace\thread\thread.h"\
	{$(INCLUDE)}"\ospace\thread\thread.ipp"\
	{$(INCLUDE)}"\ospace\thread\types.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\syncthrdcs.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_LAYER=\
	".\win16\DXFIMP.h"\
	

"$(INTDIR)\layers.obj" : $(SOURCE) $(DEP_CPP_LAYER) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"


!ELSEIF  "$(CFG)" == "Dxfimp - Win32 Debug"

DEP_CPP_LAYER=\
	"..\..\..\Cv32.mvc\Include\gc.h"\
	".\Dxfimp.hpp"\
	".\Dxfimp.hr"\
	".\DxfImpConfig.h"\
	".\Dxfimpif.hpp"\
	".\LAYERS.HPP"\
	".\Optparam.hpp"\
	".\Pheader.hpp"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\hpp\errcodesodbc.hxx"\
	{$(INCLUDE)}"\hpp\protos.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\ospace\sync\counting.h"\
	{$(INCLUDE)}"\ospace\sync\counting.ipp"\
	{$(INCLUDE)}"\ospace\sync\critical.h"\
	{$(INCLUDE)}"\ospace\sync\critical.ipp"\
	{$(INCLUDE)}"\ospace\sync\eventsem.h"\
	{$(INCLUDE)}"\ospace\sync\eventsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\lock.h"\
	{$(INCLUDE)}"\ospace\sync\lock.ipp"\
	{$(INCLUDE)}"\ospace\sync\monitor.h"\
	{$(INCLUDE)}"\ospace\sync\monitor.ipp"\
	{$(INCLUDE)}"\ospace\sync\mutex.h"\
	{$(INCLUDE)}"\ospace\sync\mutex.ipp"\
	{$(INCLUDE)}"\ospace\sync\rfifo.h"\
	{$(INCLUDE)}"\ospace\sync\rpriority.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.ipp"\
	{$(INCLUDE)}"\ospace\sync\rwsem.h"\
	{$(INCLUDE)}"\ospace\sync\rwsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\sentinel.h"\
	{$(INCLUDE)}"\ospace\sync\sentinel.ipp"\
	{$(INCLUDE)}"\ospace\sync\sfifo.h"\
	{$(INCLUDE)}"\ospace\sync\simple.h"\
	{$(INCLUDE)}"\ospace\sync\spriority.h"\
	{$(INCLUDE)}"\ospace\thread\_startup.h"\
	{$(INCLUDE)}"\ospace\thread\priority.h"\
	{$(INCLUDE)}"\ospace\thread\thisthrd.h"\
	{$(INCLUDE)}"\ospace\thread\thread.h"\
	{$(INCLUDE)}"\ospace\thread\thread.ipp"\
	{$(INCLUDE)}"\ospace\thread\types.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\syncthrdcs.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_LAYER=\
	".\win16\DXFIMP.h"\
	

"$(INTDIR)\layers.obj" : $(SOURCE) $(DEP_CPP_LAYER) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"

"$(INTDIR)\layers.sbr" : $(SOURCE) $(DEP_CPP_LAYER) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\block.cpp

!IF  "$(CFG)" == "Dxfimp - Win32 Release"

DEP_CPP_BLOCK=\
	"..\..\..\Cv32.mvc\Include\gc.h"\
	".\BLOCK.HPP"\
	".\BOGEN.HPP"\
	".\DGEO_OBJ.HPP"\
	".\Dxfimp.hpp"\
	".\Dxfimp.hr"\
	".\DxfImpConfig.h"\
	".\Dxfimpif.hpp"\
	".\MERKMAL.HPP"\
	".\Optparam.hpp"\
	".\Pheader.hpp"\
	".\PUNKTLI.HPP"\
	".\TMERKMAL.HPP"\
	".\TOOLS.HPP"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\hpp\errcodesodbc.hxx"\
	{$(INCLUDE)}"\hpp\protos.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\ospace\sync\counting.h"\
	{$(INCLUDE)}"\ospace\sync\counting.ipp"\
	{$(INCLUDE)}"\ospace\sync\critical.h"\
	{$(INCLUDE)}"\ospace\sync\critical.ipp"\
	{$(INCLUDE)}"\ospace\sync\eventsem.h"\
	{$(INCLUDE)}"\ospace\sync\lock.h"\
	{$(INCLUDE)}"\ospace\sync\lock.ipp"\
	{$(INCLUDE)}"\ospace\sync\monitor.h"\
	{$(INCLUDE)}"\ospace\sync\monitor.ipp"\
	{$(INCLUDE)}"\ospace\sync\mutex.h"\
	{$(INCLUDE)}"\ospace\sync\mutex.ipp"\
	{$(INCLUDE)}"\ospace\sync\rfifo.h"\
	{$(INCLUDE)}"\ospace\sync\rpriority.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.ipp"\
	{$(INCLUDE)}"\ospace\sync\rwsem.h"\
	{$(INCLUDE)}"\ospace\sync\rwsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\sentinel.h"\
	{$(INCLUDE)}"\ospace\sync\sentinel.ipp"\
	{$(INCLUDE)}"\ospace\sync\sfifo.h"\
	{$(INCLUDE)}"\ospace\sync\simple.h"\
	{$(INCLUDE)}"\ospace\sync\spriority.h"\
	{$(INCLUDE)}"\ospace\thread\_startup.h"\
	{$(INCLUDE)}"\ospace\thread\priority.h"\
	{$(INCLUDE)}"\ospace\thread\thisthrd.h"\
	{$(INCLUDE)}"\ospace\thread\thread.h"\
	{$(INCLUDE)}"\ospace\thread\thread.ipp"\
	{$(INCLUDE)}"\ospace\thread\types.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\syncthrdcs.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_BLOCK=\
	".\win16\DXFIMP.h"\
	

"$(INTDIR)\block.obj" : $(SOURCE) $(DEP_CPP_BLOCK) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"


!ELSEIF  "$(CFG)" == "Dxfimp - Win32 Debug"

DEP_CPP_BLOCK=\
	"..\..\..\Cv32.mvc\Include\gc.h"\
	".\BLOCK.HPP"\
	".\BOGEN.HPP"\
	".\DGEO_OBJ.HPP"\
	".\Dxfimp.hpp"\
	".\Dxfimp.hr"\
	".\DxfImpConfig.h"\
	".\Dxfimpif.hpp"\
	".\MERKMAL.HPP"\
	".\Optparam.hpp"\
	".\Pheader.hpp"\
	".\PUNKTLI.HPP"\
	".\TMERKMAL.HPP"\
	".\TOOLS.HPP"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\hpp\errcodesodbc.hxx"\
	{$(INCLUDE)}"\hpp\protos.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\ospace\sync\counting.h"\
	{$(INCLUDE)}"\ospace\sync\counting.ipp"\
	{$(INCLUDE)}"\ospace\sync\critical.h"\
	{$(INCLUDE)}"\ospace\sync\critical.ipp"\
	{$(INCLUDE)}"\ospace\sync\eventsem.h"\
	{$(INCLUDE)}"\ospace\sync\eventsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\lock.h"\
	{$(INCLUDE)}"\ospace\sync\lock.ipp"\
	{$(INCLUDE)}"\ospace\sync\monitor.h"\
	{$(INCLUDE)}"\ospace\sync\monitor.ipp"\
	{$(INCLUDE)}"\ospace\sync\mutex.h"\
	{$(INCLUDE)}"\ospace\sync\mutex.ipp"\
	{$(INCLUDE)}"\ospace\sync\rfifo.h"\
	{$(INCLUDE)}"\ospace\sync\rpriority.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.h"\
	{$(INCLUDE)}"\ospace\sync\rwlock.ipp"\
	{$(INCLUDE)}"\ospace\sync\rwsem.h"\
	{$(INCLUDE)}"\ospace\sync\rwsem.ipp"\
	{$(INCLUDE)}"\ospace\sync\sentinel.h"\
	{$(INCLUDE)}"\ospace\sync\sentinel.ipp"\
	{$(INCLUDE)}"\ospace\sync\sfifo.h"\
	{$(INCLUDE)}"\ospace\sync\simple.h"\
	{$(INCLUDE)}"\ospace\sync\spriority.h"\
	{$(INCLUDE)}"\ospace\thread\_startup.h"\
	{$(INCLUDE)}"\ospace\thread\priority.h"\
	{$(INCLUDE)}"\ospace\thread\thisthrd.h"\
	{$(INCLUDE)}"\ospace\thread\thread.h"\
	{$(INCLUDE)}"\ospace\thread\thread.ipp"\
	{$(INCLUDE)}"\ospace\thread\types.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\syncthrdcs.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_BLOCK=\
	".\win16\DXFIMP.h"\
	

"$(INTDIR)\block.obj" : $(SOURCE) $(DEP_CPP_BLOCK) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"

"$(INTDIR)\block.sbr" : $(SOURCE) $(DEP_CPP_BLOCK) "$(INTDIR)"\
 "$(INTDIR)\DXFIMP.pch"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
