# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=Caddyasc - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Caddyasc - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Caddyasc - Win32 Release" && "$(CFG)" !=\
 "Caddyasc - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Caddyasc.mak" CFG="Caddyasc - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Caddyasc - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Caddyasc - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "Caddyasc - Win32 Debug"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "Caddyasc - Win32 Release"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "winrel"
# PROP Intermediate_Dir "winrel"
OUTDIR=.\winrel
INTDIR=.\winrel

ALL : "..\..\..\trias\trias\Caddyasc.flt"

CLEAN : 
	-@erase "$(INTDIR)\CADDYASC.OBJ"
	-@erase "$(INTDIR)\Caddyasc.pch"
	-@erase "$(INTDIR)\CADDYASC.res"
	-@erase "$(INTDIR)\CADDYREC.OBJ"
	-@erase "$(INTDIR)\COMMFIL.OBJ"
	-@erase "$(INTDIR)\EXPCAPS.OBJ"
	-@erase "$(INTDIR)\LIBMAIN.OBJ"
	-@erase "$(INTDIR)\PHEADER.OBJ"
	-@erase "$(INTDIR)\RESOURCE.OBJ"
	-@erase "$(INTDIR)\STRUTIL.OBJ"
	-@erase "$(INTDIR)\VISINFO.OBJ"
	-@erase "$(OUTDIR)\Caddyasc.exp"
	-@erase "$(OUTDIR)\Caddyasc.lib"
	-@erase "..\..\..\trias\trias\Caddyasc.flt"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

.\windebug\CADDYASC.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /Zp1 /MT /W3 /GX /Ox /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "__CV__" /D "STRICT" /D "MSWIND" /D "DLL" /D "__XT" /D "_USRDLL" /D "_MBCS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "__CV__" /D "STRICT" /D "MSWIND" /D "DLL" /D "__XT" /D "_MBCS" /Yu"pheader.h" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W3 /WX /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "__CV__" /D "STRICT" /D "MSWIND" /D "DLL" /D "__XT" /D "_MBCS"\
 /Fp"$(INTDIR)/Caddyasc.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\winrel/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/CADDYASC.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Caddyasc.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 oldnames.lib ldllcew.lib containr.lib framelib.lib /nologo /subsystem:windows /dll /map:"FULL" /machine:IX86
# ADD LINK32 tfrmwork.lib cont32r.lib oldnames.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:IX86 /stub:"rights.exe" /out:"d:\trias\trias\Caddyasc.flt"
# SUBTRACT LINK32 /map
LINK32_FLAGS=tfrmwork.lib cont32r.lib oldnames.lib kernel32.lib user32.lib\
 gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib\
 oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll\
 /incremental:no /pdb:"$(OUTDIR)/Caddyasc.pdb" /machine:IX86\
 /def:".\CADDYASC.DEF" /stub:"rights.exe" /out:"d:\trias\trias\Caddyasc.flt"\
 /implib:"$(OUTDIR)/Caddyasc.lib" 
DEF_FILE= \
	".\CADDYASC.DEF"
LINK32_OBJS= \
	"$(INTDIR)\CADDYASC.OBJ" \
	"$(INTDIR)\CADDYASC.res" \
	"$(INTDIR)\CADDYREC.OBJ" \
	"$(INTDIR)\COMMFIL.OBJ" \
	"$(INTDIR)\EXPCAPS.OBJ" \
	"$(INTDIR)\LIBMAIN.OBJ" \
	"$(INTDIR)\PHEADER.OBJ" \
	"$(INTDIR)\RESOURCE.OBJ" \
	"$(INTDIR)\STRUTIL.OBJ" \
	"$(INTDIR)\VISINFO.OBJ"

"..\..\..\trias\trias\Caddyasc.flt" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Caddyasc - Win32 Debug"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "windebug"
# PROP Intermediate_Dir "windebug"
OUTDIR=.\windebug
INTDIR=.\windebug

ALL : "..\..\..\trias\trias200\caddyasc.flt"

CLEAN : 
	-@erase "$(INTDIR)\CADDYASC.OBJ"
	-@erase "$(INTDIR)\Caddyasc.pch"
	-@erase "$(INTDIR)\CADDYASC.res"
	-@erase "$(INTDIR)\CADDYREC.OBJ"
	-@erase "$(INTDIR)\COMMFIL.OBJ"
	-@erase "$(INTDIR)\EXPCAPS.OBJ"
	-@erase "$(INTDIR)\LIBMAIN.OBJ"
	-@erase "$(INTDIR)\PHEADER.OBJ"
	-@erase "$(INTDIR)\RESOURCE.OBJ"
	-@erase "$(INTDIR)\STRUTIL.OBJ"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(INTDIR)\VISINFO.OBJ"
	-@erase "$(OUTDIR)\caddyasc.exp"
	-@erase "$(OUTDIR)\caddyasc.lib"
	-@erase "$(OUTDIR)\caddyasc.pdb"
	-@erase "..\..\..\trias\trias200\caddyasc.flt"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

.\windebug\CADDYASC.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /Zp1 /MT /W3 /GX /Zi /Od /Ob1 /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "__CV__" /D "STRICT" /D "MSWIND" /D "DLL" /D "__XT" /D "_USRDLL" /D "_MBCS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /Zi /Od /Ob1 /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "__CV__" /D "STRICT" /D "MSWIND" /D "DLL" /D "__XT" /Yu"pheader.h" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MDd /W3 /WX /Gm /Zi /Od /Ob1 /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "__CV__" /D "STRICT" /D "MSWIND" /D "DLL" /D "__XT"\
 /Fp"$(INTDIR)/Caddyasc.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\windebug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/CADDYASC.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Caddyasc.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 oldnames.lib ldllcew.lib containr.lib framelib.lib /nologo /subsystem:windows /dll /map:"FULL" /debug /machine:IX86
# ADD LINK32 cont32d.lib tfrm32d.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /debug /machine:IX86 /nodefaultlib:"ocs30d.lib" /nodefaultlib:"libcmt.lib" /stub:"rights.exe" /out:"d:\trias\trias200\caddyasc.flt" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=cont32d.lib tfrm32d.lib kernel32.lib user32.lib gdi32.lib\
 winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib\
 uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no\
 /pdb:"$(OUTDIR)/caddyasc.pdb" /debug /machine:IX86 /nodefaultlib:"ocs30d.lib"\
 /nodefaultlib:"libcmt.lib" /def:".\CADDYASC.DEF" /stub:"rights.exe"\
 /out:"d:\trias\trias200\caddyasc.flt" /implib:"$(OUTDIR)/caddyasc.lib"\
 /SUBSYSTEM:windows,4.0 
DEF_FILE= \
	".\CADDYASC.DEF"
LINK32_OBJS= \
	"$(INTDIR)\CADDYASC.OBJ" \
	"$(INTDIR)\CADDYASC.res" \
	"$(INTDIR)\CADDYREC.OBJ" \
	"$(INTDIR)\COMMFIL.OBJ" \
	"$(INTDIR)\EXPCAPS.OBJ" \
	"$(INTDIR)\LIBMAIN.OBJ" \
	"$(INTDIR)\PHEADER.OBJ" \
	"$(INTDIR)\RESOURCE.OBJ" \
	"$(INTDIR)\STRUTIL.OBJ" \
	"$(INTDIR)\VISINFO.OBJ"

"..\..\..\trias\trias200\caddyasc.flt" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Caddyasc - Win32 Release"
# Name "Caddyasc - Win32 Debug"

!IF  "$(CFG)" == "Caddyasc - Win32 Release"

!ELSEIF  "$(CFG)" == "Caddyasc - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\PHEADER.CXX

!IF  "$(CFG)" == "Caddyasc - Win32 Release"

DEP_CPP_PHEAD=\
	".\Pheader.h"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\Xtensnm.hxx"\
	
# ADD CPP /Yc"pheader.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "__CV__" /D "STRICT" /D "MSWIND" /D "DLL" /D "__XT" /D "_MBCS"\
 /Fp"$(INTDIR)/Caddyasc.pch" /Yc"pheader.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\PHEADER.OBJ" : $(SOURCE) $(DEP_CPP_PHEAD) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Caddyasc.pch" : $(SOURCE) $(DEP_CPP_PHEAD) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Caddyasc - Win32 Debug"

DEP_CPP_PHEAD=\
	"..\..\INC_GLB.32\gc.h"\
	"..\..\INC_GLB.32\syncthrd.hxx"\
	".\Pheader.h"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ixtensn.hxx"\
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
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\Xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\yxvals.h"\
	
# ADD CPP /Yc"pheader.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /Zi /Od /Ob1 /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "__CV__" /D "STRICT" /D "MSWIND" /D "DLL" /D "__XT"\
 /Fp"$(INTDIR)/Caddyasc.pch" /Yc"pheader.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\PHEADER.OBJ" : $(SOURCE) $(DEP_CPP_PHEAD) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Caddyasc.pch" : $(SOURCE) $(DEP_CPP_PHEAD) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CADDYREC.CXX

!IF  "$(CFG)" == "Caddyasc - Win32 Release"

DEP_CPP_CADDY=\
	".\Caddyasc.hr"\
	".\Caddyasc.hxx"\
	".\Caddyrec.hxx"\
	".\Pheader.h"\
	{$(INCLUDE)}"\Attribs.hxx"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Defattr.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\Impexp.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Strdup.hxx"\
	{$(INCLUDE)}"\Trias01m.hxx"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\Xtensnm.hxx"\
	
NODEP_CPP_CADDY=\
	".\win16\CADDYASC.h"\
	
# ADD CPP /Yu"pheader.h"

"$(INTDIR)\CADDYREC.OBJ" : $(SOURCE) $(DEP_CPP_CADDY) "$(INTDIR)"\
 "$(INTDIR)\Caddyasc.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "__CV__" /D "STRICT" /D "MSWIND" /D "DLL" /D "__XT" /D "_MBCS"\
 /Fp"$(INTDIR)/Caddyasc.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Caddyasc - Win32 Debug"

DEP_CPP_CADDY=\
	"..\..\INC_GLB.32\gc.h"\
	"..\..\INC_GLB.32\syncthrd.hxx"\
	".\Caddyasc.hr"\
	".\Caddyasc.hxx"\
	".\Caddyrec.hxx"\
	".\Pheader.h"\
	{$(INCLUDE)}"\Attribs.hxx"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\Defattr.h"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\ienumobj.hxx"\
	{$(INCLUDE)}"\Impexp.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ixtensn.hxx"\
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
	{$(INCLUDE)}"\Strdup.hxx"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\Trias01m.hxx"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\Xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_CADDY=\
	".\win16\CADDYASC.h"\
	

"$(INTDIR)\CADDYREC.OBJ" : $(SOURCE) $(DEP_CPP_CADDY) "$(INTDIR)"\
 "$(INTDIR)\Caddyasc.pch"
   $(CPP) /nologo /MDd /W3 /WX /Gm /Zi /Od /Ob1 /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "__CV__" /D "STRICT" /D "MSWIND" /D "DLL" /D "__XT"\
 /Fp"$(INTDIR)/Caddyasc.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\COMMFIL.CXX

!IF  "$(CFG)" == "Caddyasc - Win32 Release"

DEP_CPP_COMMF=\
	".\Caddyasc.hxx"\
	".\Pheader.h"\
	{$(INCLUDE)}"\Attribs.hxx"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Defattr.h"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\Impexp.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\Xtensnm.hxx"\
	
# ADD CPP /Yu"pheader.h"

"$(INTDIR)\COMMFIL.OBJ" : $(SOURCE) $(DEP_CPP_COMMF) "$(INTDIR)"\
 "$(INTDIR)\Caddyasc.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "__CV__" /D "STRICT" /D "MSWIND" /D "DLL" /D "__XT" /D "_MBCS"\
 /Fp"$(INTDIR)/Caddyasc.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Caddyasc - Win32 Debug"

DEP_CPP_COMMF=\
	"..\..\INC_GLB.32\gc.h"\
	"..\..\INC_GLB.32\syncthrd.hxx"\
	".\Caddyasc.hxx"\
	".\Pheader.h"\
	{$(INCLUDE)}"\Attribs.hxx"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\Defattr.h"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\ienumobj.hxx"\
	{$(INCLUDE)}"\Impexp.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ixtensn.hxx"\
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
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\Xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

"$(INTDIR)\COMMFIL.OBJ" : $(SOURCE) $(DEP_CPP_COMMF) "$(INTDIR)"\
 "$(INTDIR)\Caddyasc.pch"
   $(CPP) /nologo /MDd /W3 /WX /Gm /Zi /Od /Ob1 /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "__CV__" /D "STRICT" /D "MSWIND" /D "DLL" /D "__XT"\
 /Fp"$(INTDIR)/Caddyasc.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\EXPCAPS.CXX

!IF  "$(CFG)" == "Caddyasc - Win32 Release"

DEP_CPP_EXPCA=\
	".\Caddyasc.hxx"\
	".\Pheader.h"\
	{$(INCLUDE)}"\Attribs.hxx"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Defattr.h"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\Impexp.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\Xtensnm.hxx"\
	
# ADD CPP /Yu"pheader.h"

"$(INTDIR)\EXPCAPS.OBJ" : $(SOURCE) $(DEP_CPP_EXPCA) "$(INTDIR)"\
 "$(INTDIR)\Caddyasc.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "__CV__" /D "STRICT" /D "MSWIND" /D "DLL" /D "__XT" /D "_MBCS"\
 /Fp"$(INTDIR)/Caddyasc.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Caddyasc - Win32 Debug"

DEP_CPP_EXPCA=\
	"..\..\INC_GLB.32\gc.h"\
	"..\..\INC_GLB.32\syncthrd.hxx"\
	".\Caddyasc.hxx"\
	".\Pheader.h"\
	{$(INCLUDE)}"\Attribs.hxx"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\Defattr.h"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\ienumobj.hxx"\
	{$(INCLUDE)}"\Impexp.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ixtensn.hxx"\
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
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\Xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

"$(INTDIR)\EXPCAPS.OBJ" : $(SOURCE) $(DEP_CPP_EXPCA) "$(INTDIR)"\
 "$(INTDIR)\Caddyasc.pch"
   $(CPP) /nologo /MDd /W3 /WX /Gm /Zi /Od /Ob1 /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "__CV__" /D "STRICT" /D "MSWIND" /D "DLL" /D "__XT"\
 /Fp"$(INTDIR)/Caddyasc.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CADDYASC.CXX

!IF  "$(CFG)" == "Caddyasc - Win32 Release"

DEP_CPP_CADDYA=\
	".\Caddyasc.hr"\
	".\Caddyasc.hxx"\
	".\Caddyrec.hxx"\
	".\Pheader.h"\
	{$(INCLUDE)}"\Attribs.hxx"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Defattr.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\Impexp.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\Resstrg.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Strdup.hxx"\
	{$(INCLUDE)}"\Trias01m.hxx"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\Xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	
NODEP_CPP_CADDYA=\
	".\win16\CADDYASC.h"\
	
# ADD CPP /Yu"pheader.h"

"$(INTDIR)\CADDYASC.OBJ" : $(SOURCE) $(DEP_CPP_CADDYA) "$(INTDIR)"\
 "$(INTDIR)\Caddyasc.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "__CV__" /D "STRICT" /D "MSWIND" /D "DLL" /D "__XT" /D "_MBCS"\
 /Fp"$(INTDIR)/Caddyasc.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Caddyasc - Win32 Debug"

DEP_CPP_CADDYA=\
	"..\..\INC_GLB.32\gc.h"\
	"..\..\INC_GLB.32\syncthrd.hxx"\
	".\Caddyasc.hr"\
	".\Caddyasc.hxx"\
	".\Caddyrec.hxx"\
	".\Pheader.h"\
	{$(INCLUDE)}"\Attribs.hxx"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\Defattr.h"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\ienumobj.hxx"\
	{$(INCLUDE)}"\Impexp.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ixtensn.hxx"\
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
	{$(INCLUDE)}"\Resstrg.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Strdup.hxx"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\Trias01m.hxx"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\Xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_CADDYA=\
	".\win16\CADDYASC.h"\
	

"$(INTDIR)\CADDYASC.OBJ" : $(SOURCE) $(DEP_CPP_CADDYA) "$(INTDIR)"\
 "$(INTDIR)\Caddyasc.pch"
   $(CPP) /nologo /MDd /W3 /WX /Gm /Zi /Od /Ob1 /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "__CV__" /D "STRICT" /D "MSWIND" /D "DLL" /D "__XT"\
 /Fp"$(INTDIR)/Caddyasc.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRUTIL.CXX

!IF  "$(CFG)" == "Caddyasc - Win32 Release"

DEP_CPP_STRUT=\
	".\Pheader.h"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\Xtensnm.hxx"\
	
# ADD CPP /Yu"pheader.h"

"$(INTDIR)\STRUTIL.OBJ" : $(SOURCE) $(DEP_CPP_STRUT) "$(INTDIR)"\
 "$(INTDIR)\Caddyasc.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "__CV__" /D "STRICT" /D "MSWIND" /D "DLL" /D "__XT" /D "_MBCS"\
 /Fp"$(INTDIR)/Caddyasc.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Caddyasc - Win32 Debug"

DEP_CPP_STRUT=\
	"..\..\INC_GLB.32\gc.h"\
	"..\..\INC_GLB.32\syncthrd.hxx"\
	".\Pheader.h"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ixtensn.hxx"\
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
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\Xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

"$(INTDIR)\STRUTIL.OBJ" : $(SOURCE) $(DEP_CPP_STRUT) "$(INTDIR)"\
 "$(INTDIR)\Caddyasc.pch"
   $(CPP) /nologo /MDd /W3 /WX /Gm /Zi /Od /Ob1 /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "__CV__" /D "STRICT" /D "MSWIND" /D "DLL" /D "__XT"\
 /Fp"$(INTDIR)/Caddyasc.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\VISINFO.CXX

!IF  "$(CFG)" == "Caddyasc - Win32 Release"

DEP_CPP_VISIN=\
	".\Pheader.h"\
	{$(INCLUDE)}"\Attribs.hxx"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Defattr.h"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\Xtensnm.hxx"\
	
# ADD CPP /Yu"pheader.h"

"$(INTDIR)\VISINFO.OBJ" : $(SOURCE) $(DEP_CPP_VISIN) "$(INTDIR)"\
 "$(INTDIR)\Caddyasc.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "__CV__" /D "STRICT" /D "MSWIND" /D "DLL" /D "__XT" /D "_MBCS"\
 /Fp"$(INTDIR)/Caddyasc.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Caddyasc - Win32 Debug"

DEP_CPP_VISIN=\
	"..\..\INC_GLB.32\gc.h"\
	"..\..\INC_GLB.32\syncthrd.hxx"\
	".\Pheader.h"\
	{$(INCLUDE)}"\Attribs.hxx"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\Defattr.h"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ixtensn.hxx"\
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
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\Xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

"$(INTDIR)\VISINFO.OBJ" : $(SOURCE) $(DEP_CPP_VISIN) "$(INTDIR)"\
 "$(INTDIR)\Caddyasc.pch"
   $(CPP) /nologo /MDd /W3 /WX /Gm /Zi /Od /Ob1 /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "__CV__" /D "STRICT" /D "MSWIND" /D "DLL" /D "__XT"\
 /Fp"$(INTDIR)/Caddyasc.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CADDYASC.RC
DEP_RSC_CADDYAS=\
	".\CADDYASC.RCV"\
	".\visinfo.tpl"\
	

"$(INTDIR)\CADDYASC.res" : $(SOURCE) $(DEP_RSC_CADDYAS) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\CADDYASC.DEF

!IF  "$(CFG)" == "Caddyasc - Win32 Release"

!ELSEIF  "$(CFG)" == "Caddyasc - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\RESOURCE.CXX

!IF  "$(CFG)" == "Caddyasc - Win32 Release"

DEP_CPP_RESOU=\
	".\Caddyasc.hr"\
	".\Pheader.h"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\Xtensnm.hxx"\
	
NODEP_CPP_RESOU=\
	".\win16\CADDYASC.h"\
	
# ADD CPP /Yu"pheader.h"

"$(INTDIR)\RESOURCE.OBJ" : $(SOURCE) $(DEP_CPP_RESOU) "$(INTDIR)"\
 "$(INTDIR)\Caddyasc.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "__CV__" /D "STRICT" /D "MSWIND" /D "DLL" /D "__XT" /D "_MBCS"\
 /Fp"$(INTDIR)/Caddyasc.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Caddyasc - Win32 Debug"

DEP_CPP_RESOU=\
	"..\..\INC_GLB.32\gc.h"\
	"..\..\INC_GLB.32\syncthrd.hxx"\
	".\Caddyasc.hr"\
	".\Pheader.h"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ixtensn.hxx"\
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
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\Xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_RESOU=\
	".\win16\CADDYASC.h"\
	

"$(INTDIR)\RESOURCE.OBJ" : $(SOURCE) $(DEP_CPP_RESOU) "$(INTDIR)"\
 "$(INTDIR)\Caddyasc.pch"
   $(CPP) /nologo /MDd /W3 /WX /Gm /Zi /Od /Ob1 /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "__CV__" /D "STRICT" /D "MSWIND" /D "DLL" /D "__XT"\
 /Fp"$(INTDIR)/Caddyasc.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\LIBMAIN.CXX

!IF  "$(CFG)" == "Caddyasc - Win32 Release"

DEP_CPP_LIBMA=\
	".\Pheader.h"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\Xtensnm.hxx"\
	
# ADD CPP /Yu"pheader.h"

"$(INTDIR)\LIBMAIN.OBJ" : $(SOURCE) $(DEP_CPP_LIBMA) "$(INTDIR)"\
 "$(INTDIR)\Caddyasc.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "__CV__" /D "STRICT" /D "MSWIND" /D "DLL" /D "__XT" /D "_MBCS"\
 /Fp"$(INTDIR)/Caddyasc.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Caddyasc - Win32 Debug"

DEP_CPP_LIBMA=\
	"..\..\INC_GLB.32\gc.h"\
	"..\..\INC_GLB.32\syncthrd.hxx"\
	".\Pheader.h"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ixtensn.hxx"\
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
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\Xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\yxvals.h"\
	

"$(INTDIR)\LIBMAIN.OBJ" : $(SOURCE) $(DEP_CPP_LIBMA) "$(INTDIR)"\
 "$(INTDIR)\Caddyasc.pch"
   $(CPP) /nologo /MDd /W3 /WX /Gm /Zi /Od /Ob1 /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "__CV__" /D "STRICT" /D "MSWIND" /D "DLL" /D "__XT"\
 /Fp"$(INTDIR)/Caddyasc.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
