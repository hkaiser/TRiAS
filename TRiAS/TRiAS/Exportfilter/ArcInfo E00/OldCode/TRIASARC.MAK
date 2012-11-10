# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=Triasarc - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Triasarc - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Triasarc - Win32 Release" && "$(CFG)" !=\
 "Triasarc - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Triasarc.mak" CFG="Triasarc - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Triasarc - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Triasarc - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "Triasarc - Win32 Debug"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "Triasarc - Win32 Release"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WinRel"
# PROP Intermediate_Dir "WinRel"
OUTDIR=.\WinRel
INTDIR=.\WinRel

ALL : "..\..\..\trias\trias\TRIASARC.flt"

CLEAN : 
	-@erase "$(INTDIR)\COMMFIL.OBJ"
	-@erase "$(INTDIR)\COVER.OBJ"
	-@erase "$(INTDIR)\COVNAME.OBJ"
	-@erase "$(INTDIR)\EXPCAPS.OBJ"
	-@erase "$(INTDIR)\EXPPARAM.OBJ"
	-@erase "$(INTDIR)\FILEOBJ.OBJ"
	-@erase "$(INTDIR)\GEO.OBJ"
	-@erase "$(INTDIR)\HELPTEXT.OBJ"
	-@erase "$(INTDIR)\IDENT.OBJ"
	-@erase "$(INTDIR)\INFO.OBJ"
	-@erase "$(INTDIR)\LIBMAIN.OBJ"
	-@erase "$(INTDIR)\MERKMDES.OBJ"
	-@erase "$(INTDIR)\MERKNAME.OBJ"
	-@erase "$(INTDIR)\NAMEEDIT.OBJ"
	-@erase "$(INTDIR)\NUMEDIT.OBJ"
	-@erase "$(INTDIR)\PHEADER.OBJ"
	-@erase "$(INTDIR)\RESOURCE.OBJ"
	-@erase "$(INTDIR)\SECTION.OBJ"
	-@erase "$(INTDIR)\TRIASARC.OBJ"
	-@erase "$(INTDIR)\Triasarc.pch"
	-@erase "$(INTDIR)\TRIASARC.res"
	-@erase "$(INTDIR)\VISINFO.OBJ"
	-@erase "$(OUTDIR)\TRIASARC.exp"
	-@erase "$(OUTDIR)\TRIASARC.lib"
	-@erase "..\..\..\trias\trias\TRIASARC.flt"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /Zp1 /MT /W3 /GX /Ox /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "__CV__" /D "STRICT" /D "MSWIND" /D "DLL" /D "__XT" /D "_USRDLL" /D "_MBCS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /O2 /I "\triasdev.mvc\inc.hpp" /I "\triasdev.mvc\inc.hpp\inc" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "__CV__" /D "STRICT" /D "MSWIND" /D "DLL" /D "__XT" /Yu"pheader.h" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W3 /WX /GX /O2 /I "\triasdev.mvc\inc.hpp" /I\
 "\triasdev.mvc\inc.hpp\inc" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "__CV__" /D\
 "STRICT" /D "MSWIND" /D "DLL" /D "__XT" /Fp"$(INTDIR)/Triasarc.pch"\
 /Yu"pheader.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\WinRel/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/TRIASARC.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Triasarc.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 oldnames.lib ldllcew.lib framelib.lib containr.lib /nologo /subsystem:windows /dll /map:"FULL" /machine:IX86
# ADD LINK32 tfrmwork.lib cont32r.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:IX86 /stub:"rights.exe" /out:"d:\trias\trias\TRIASARC.flt"
# SUBTRACT LINK32 /map
LINK32_FLAGS=tfrmwork.lib cont32r.lib kernel32.lib user32.lib gdi32.lib\
 winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib\
 uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll\
 /incremental:no /pdb:"$(OUTDIR)/TRIASARC.pdb" /machine:IX86\
 /def:".\TRIASARC.DEF" /stub:"rights.exe" /out:"d:\trias\trias\TRIASARC.flt"\
 /implib:"$(OUTDIR)/TRIASARC.lib" 
DEF_FILE= \
	".\TRIASARC.DEF"
LINK32_OBJS= \
	"$(INTDIR)\COMMFIL.OBJ" \
	"$(INTDIR)\COVER.OBJ" \
	"$(INTDIR)\COVNAME.OBJ" \
	"$(INTDIR)\EXPCAPS.OBJ" \
	"$(INTDIR)\EXPPARAM.OBJ" \
	"$(INTDIR)\FILEOBJ.OBJ" \
	"$(INTDIR)\GEO.OBJ" \
	"$(INTDIR)\HELPTEXT.OBJ" \
	"$(INTDIR)\IDENT.OBJ" \
	"$(INTDIR)\INFO.OBJ" \
	"$(INTDIR)\LIBMAIN.OBJ" \
	"$(INTDIR)\MERKMDES.OBJ" \
	"$(INTDIR)\MERKNAME.OBJ" \
	"$(INTDIR)\NAMEEDIT.OBJ" \
	"$(INTDIR)\NUMEDIT.OBJ" \
	"$(INTDIR)\PHEADER.OBJ" \
	"$(INTDIR)\RESOURCE.OBJ" \
	"$(INTDIR)\SECTION.OBJ" \
	"$(INTDIR)\TRIASARC.OBJ" \
	"$(INTDIR)\TRIASARC.res" \
	"$(INTDIR)\VISINFO.OBJ"

"..\..\..\trias\trias\TRIASARC.flt" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Triasarc - Win32 Debug"

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

ALL : "..\..\..\trias\trias200\triasarc.flt"

CLEAN : 
	-@erase "$(INTDIR)\COMMFIL.OBJ"
	-@erase "$(INTDIR)\COVER.OBJ"
	-@erase "$(INTDIR)\COVNAME.OBJ"
	-@erase "$(INTDIR)\EXPCAPS.OBJ"
	-@erase "$(INTDIR)\EXPPARAM.OBJ"
	-@erase "$(INTDIR)\FILEOBJ.OBJ"
	-@erase "$(INTDIR)\GEO.OBJ"
	-@erase "$(INTDIR)\HELPTEXT.OBJ"
	-@erase "$(INTDIR)\IDENT.OBJ"
	-@erase "$(INTDIR)\INFO.OBJ"
	-@erase "$(INTDIR)\LIBMAIN.OBJ"
	-@erase "$(INTDIR)\MERKMDES.OBJ"
	-@erase "$(INTDIR)\MERKNAME.OBJ"
	-@erase "$(INTDIR)\NAMEEDIT.OBJ"
	-@erase "$(INTDIR)\NUMEDIT.OBJ"
	-@erase "$(INTDIR)\PHEADER.OBJ"
	-@erase "$(INTDIR)\RESOURCE.OBJ"
	-@erase "$(INTDIR)\SECTION.OBJ"
	-@erase "$(INTDIR)\TRIASARC.OBJ"
	-@erase "$(INTDIR)\Triasarc.pch"
	-@erase "$(INTDIR)\TRIASARC.res"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(INTDIR)\VISINFO.OBJ"
	-@erase "$(OUTDIR)\triasarc.exp"
	-@erase "$(OUTDIR)\triasarc.lib"
	-@erase "$(OUTDIR)\triasarc.pdb"
	-@erase "..\..\..\trias\trias200\triasarc.flt"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

.\windebug\TRIASARC.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /Zp1 /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "__CV__" /D "STRICT" /D "MSWIND" /D "DLL" /D "__XT" /D "_USRDLL" /D "_MBCS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /I "\triasdev.mvc\inc.hpp" /I "\triasdev.mvc\inc.hpp\inc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "__CV__" /D "STRICT" /D "MSWIND" /D "DLL" /D "__XT" /Yu"pheader.h" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MDd /W3 /WX /Gm /GX /Zi /Od /I "\triasdev.mvc\inc.hpp" /I\
 "\triasdev.mvc\inc.hpp\inc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "__CV__" /D\
 "STRICT" /D "MSWIND" /D "DLL" /D "__XT" /Fp"$(INTDIR)/Triasarc.pch"\
 /Yu"pheader.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\windebug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/TRIASARC.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Triasarc.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 oldnames.lib ldllcew.lib framelib.lib containr.lib /nologo /subsystem:windows /dll /map:"FULL" /debug /machine:IX86
# ADD LINK32 tfrm32d.lib cont32d.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /debug /machine:IX86 /stub:"rights.exe" /out:"d:\trias\trias200\triasarc.flt" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=tfrm32d.lib cont32d.lib kernel32.lib user32.lib gdi32.lib\
 winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib\
 uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no\
 /pdb:"$(OUTDIR)/triasarc.pdb" /debug /machine:IX86 /def:".\TRIASARC.DEF"\
 /stub:"rights.exe" /out:"d:\trias\trias200\triasarc.flt"\
 /implib:"$(OUTDIR)/triasarc.lib" /SUBSYSTEM:windows,4.0 
DEF_FILE= \
	".\TRIASARC.DEF"
LINK32_OBJS= \
	"$(INTDIR)\COMMFIL.OBJ" \
	"$(INTDIR)\COVER.OBJ" \
	"$(INTDIR)\COVNAME.OBJ" \
	"$(INTDIR)\EXPCAPS.OBJ" \
	"$(INTDIR)\EXPPARAM.OBJ" \
	"$(INTDIR)\FILEOBJ.OBJ" \
	"$(INTDIR)\GEO.OBJ" \
	"$(INTDIR)\HELPTEXT.OBJ" \
	"$(INTDIR)\IDENT.OBJ" \
	"$(INTDIR)\INFO.OBJ" \
	"$(INTDIR)\LIBMAIN.OBJ" \
	"$(INTDIR)\MERKMDES.OBJ" \
	"$(INTDIR)\MERKNAME.OBJ" \
	"$(INTDIR)\NAMEEDIT.OBJ" \
	"$(INTDIR)\NUMEDIT.OBJ" \
	"$(INTDIR)\PHEADER.OBJ" \
	"$(INTDIR)\RESOURCE.OBJ" \
	"$(INTDIR)\SECTION.OBJ" \
	"$(INTDIR)\TRIASARC.OBJ" \
	"$(INTDIR)\TRIASARC.res" \
	"$(INTDIR)\VISINFO.OBJ"

"..\..\..\trias\trias200\triasarc.flt" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Triasarc - Win32 Release"
# Name "Triasarc - Win32 Debug"

!IF  "$(CFG)" == "Triasarc - Win32 Release"

!ELSEIF  "$(CFG)" == "Triasarc - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\PHEADER.CXX

!IF  "$(CFG)" == "Triasarc - Win32 Release"

DEP_CPP_PHEAD=\
	"..\..\INC_GLB.32\gc.h"\
	"..\..\inc_glb.32\syncthrd.hxx"\
	".\Pheader.h"\
	{$(INCLUDE)}"\Bool.h"\
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
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\expfltm.hxx"\
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
	
# ADD CPP /Yc"pheader.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O2 /I "\triasdev.mvc\inc.hpp" /I\
 "\triasdev.mvc\inc.hpp\inc" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "__CV__" /D\
 "STRICT" /D "MSWIND" /D "DLL" /D "__XT" /Fp"$(INTDIR)/Triasarc.pch"\
 /Yc"pheader.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\PHEADER.OBJ" : $(SOURCE) $(DEP_CPP_PHEAD) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Triasarc.pch" : $(SOURCE) $(DEP_CPP_PHEAD) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Triasarc - Win32 Debug"

DEP_CPP_PHEAD=\
	".\Pheader.h"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\Print.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	
# ADD CPP /Yc"pheader.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /I "\triasdev.mvc\inc.hpp" /I\
 "\triasdev.mvc\inc.hpp\inc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "__CV__" /D\
 "STRICT" /D "MSWIND" /D "DLL" /D "__XT" /Fp"$(INTDIR)/Triasarc.pch"\
 /Yc"pheader.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\PHEADER.OBJ" : $(SOURCE) $(DEP_CPP_PHEAD) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Triasarc.pch" : $(SOURCE) $(DEP_CPP_PHEAD) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\COVNAME.CXX

!IF  "$(CFG)" == "Triasarc - Win32 Release"

DEP_CPP_COVNA=\
	".\Covname.hxx"\
	".\Ident.hxx"\
	".\Nameedit.hxx"\
	".\Pheader.h"\
	".\Triasarc.hr"\
	".\Triasarc.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\Impexp.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\Print.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\Waitcur.hxx"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	
NODEP_CPP_COVNA=\
	".\win16\TRIASARC.h"\
	

"$(INTDIR)\COVNAME.OBJ" : $(SOURCE) $(DEP_CPP_COVNA) "$(INTDIR)"\
 "$(INTDIR)\Triasarc.pch"


!ELSEIF  "$(CFG)" == "Triasarc - Win32 Debug"

DEP_CPP_COVNA=\
	"..\..\INC_GLB.32\gc.h"\
	"..\..\inc_glb.32\syncthrd.hxx"\
	".\Covname.hxx"\
	".\Ident.hxx"\
	".\Nameedit.hxx"\
	".\Pheader.h"\
	".\Triasarc.hr"\
	".\Triasarc.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Impexp.hxx"\
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
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\Waitcur.hxx"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_COVNA=\
	".\win16\TRIASARC.h"\
	

"$(INTDIR)\COVNAME.OBJ" : $(SOURCE) $(DEP_CPP_COVNA) "$(INTDIR)"\
 "$(INTDIR)\Triasarc.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\EXPCAPS.CXX

!IF  "$(CFG)" == "Triasarc - Win32 Release"

DEP_CPP_EXPCA=\
	".\Pheader.h"\
	{$(INCLUDE)}"\Attribs.hxx"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\Impexp.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\Print.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	

"$(INTDIR)\EXPCAPS.OBJ" : $(SOURCE) $(DEP_CPP_EXPCA) "$(INTDIR)"\
 "$(INTDIR)\Triasarc.pch"


!ELSEIF  "$(CFG)" == "Triasarc - Win32 Debug"

DEP_CPP_EXPCA=\
	"..\..\INC_GLB.32\gc.h"\
	"..\..\inc_glb.32\syncthrd.hxx"\
	".\Pheader.h"\
	{$(INCLUDE)}"\Attribs.hxx"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Impexp.hxx"\
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
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Yxvals.h"\
	

"$(INTDIR)\EXPCAPS.OBJ" : $(SOURCE) $(DEP_CPP_EXPCA) "$(INTDIR)"\
 "$(INTDIR)\Triasarc.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\EXPPARAM.CXX

!IF  "$(CFG)" == "Triasarc - Win32 Release"

DEP_CPP_EXPPA=\
	"..\..\INC_GLB.32\gc.h"\
	"..\..\inc_glb.32\syncthrd.hxx"\
	".\Covname.hxx"\
	".\Expparam.hxx"\
	".\Helptext.hxx"\
	".\Merkname.hxx"\
	".\Nameedit.hxx"\
	".\Numedit.hxx"\
	".\Pheader.h"\
	".\Triasarc.hr"\
	{$(INCLUDE)}"\Bool.h"\
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
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\expfltm.hxx"\
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
	
NODEP_CPP_EXPPA=\
	".\win16\TRIASARC.h"\
	

"$(INTDIR)\EXPPARAM.OBJ" : $(SOURCE) $(DEP_CPP_EXPPA) "$(INTDIR)"\
 "$(INTDIR)\Triasarc.pch"


!ELSEIF  "$(CFG)" == "Triasarc - Win32 Debug"

DEP_CPP_EXPPA=\
	".\Covname.hxx"\
	".\Expparam.hxx"\
	".\Helptext.hxx"\
	".\Merkname.hxx"\
	".\Nameedit.hxx"\
	".\Numedit.hxx"\
	".\Pheader.h"\
	".\Triasarc.hr"\
	
NODEP_CPP_EXPPA=\
	".\win16\TRIASARC.h"\
	

"$(INTDIR)\EXPPARAM.OBJ" : $(SOURCE) $(DEP_CPP_EXPPA) "$(INTDIR)"\
 "$(INTDIR)\Triasarc.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FILEOBJ.CXX

!IF  "$(CFG)" == "Triasarc - Win32 Release"

DEP_CPP_FILEO=\
	"..\..\INC_GLB.32\gc.h"\
	"..\..\inc_glb.32\syncthrd.hxx"\
	".\Fileobj.hxx"\
	".\Pheader.h"\
	{$(INCLUDE)}"\Bool.h"\
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
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\expfltm.hxx"\
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
	

"$(INTDIR)\FILEOBJ.OBJ" : $(SOURCE) $(DEP_CPP_FILEO) "$(INTDIR)"\
 "$(INTDIR)\Triasarc.pch"


!ELSEIF  "$(CFG)" == "Triasarc - Win32 Debug"

DEP_CPP_FILEO=\
	".\Fileobj.hxx"\
	".\Pheader.h"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\Print.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	

"$(INTDIR)\FILEOBJ.OBJ" : $(SOURCE) $(DEP_CPP_FILEO) "$(INTDIR)"\
 "$(INTDIR)\Triasarc.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GEO.CXX

!IF  "$(CFG)" == "Triasarc - Win32 Release"

DEP_CPP_GEO_C=\
	".\Geo.hxx"\
	".\Pheader.h"\
	{$(INCLUDE)}"\Attribs.hxx"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\Impexp.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\Print.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	

"$(INTDIR)\GEO.OBJ" : $(SOURCE) $(DEP_CPP_GEO_C) "$(INTDIR)"\
 "$(INTDIR)\Triasarc.pch"


!ELSEIF  "$(CFG)" == "Triasarc - Win32 Debug"

DEP_CPP_GEO_C=\
	"..\..\INC_GLB.32\gc.h"\
	"..\..\inc_glb.32\syncthrd.hxx"\
	".\Geo.hxx"\
	".\Pheader.h"\
	{$(INCLUDE)}"\Attribs.hxx"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Impexp.hxx"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Yxvals.h"\
	

"$(INTDIR)\GEO.OBJ" : $(SOURCE) $(DEP_CPP_GEO_C) "$(INTDIR)"\
 "$(INTDIR)\Triasarc.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\HELPTEXT.CXX

!IF  "$(CFG)" == "Triasarc - Win32 Release"

DEP_CPP_HELPT=\
	"..\..\INC_GLB.32\gc.h"\
	"..\..\inc_glb.32\syncthrd.hxx"\
	".\Helptext.hxx"\
	".\Pheader.h"\
	".\Triasarc.hr"\
	{$(INCLUDE)}"\Bool.h"\
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
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\expfltm.hxx"\
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
	
NODEP_CPP_HELPT=\
	".\win16\TRIASARC.h"\
	

"$(INTDIR)\HELPTEXT.OBJ" : $(SOURCE) $(DEP_CPP_HELPT) "$(INTDIR)"\
 "$(INTDIR)\Triasarc.pch"


!ELSEIF  "$(CFG)" == "Triasarc - Win32 Debug"

DEP_CPP_HELPT=\
	".\Helptext.hxx"\
	".\Pheader.h"\
	".\Triasarc.hr"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\Print.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	
NODEP_CPP_HELPT=\
	".\win16\TRIASARC.h"\
	

"$(INTDIR)\HELPTEXT.OBJ" : $(SOURCE) $(DEP_CPP_HELPT) "$(INTDIR)"\
 "$(INTDIR)\Triasarc.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\IDENT.CXX

!IF  "$(CFG)" == "Triasarc - Win32 Release"

DEP_CPP_IDENT=\
	".\Cover.hxx"\
	".\Expparam.hxx"\
	".\Helptext.hxx"\
	".\Ident.hxx"\
	".\Info.hxx"\
	".\Numedit.hxx"\
	".\Pheader.h"\
	".\Section.hxx"\
	".\Triasarc.hr"\
	".\Triasarc.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\defattr.h"\
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
	{$(INCLUDE)}"\Print.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Strdup.hxx"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	
NODEP_CPP_IDENT=\
	".\win16\TRIASARC.h"\
	

"$(INTDIR)\IDENT.OBJ" : $(SOURCE) $(DEP_CPP_IDENT) "$(INTDIR)"\
 "$(INTDIR)\Triasarc.pch"


!ELSEIF  "$(CFG)" == "Triasarc - Win32 Debug"

DEP_CPP_IDENT=\
	"..\..\INC_GLB.32\gc.h"\
	"..\..\inc_glb.32\syncthrd.hxx"\
	".\Cover.hxx"\
	".\Expparam.hxx"\
	".\Helptext.hxx"\
	".\Ident.hxx"\
	".\Info.hxx"\
	".\Numedit.hxx"\
	".\Pheader.h"\
	".\Section.hxx"\
	".\Triasarc.hr"\
	".\Triasarc.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Impexp.hxx"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Strdup.hxx"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_IDENT=\
	".\win16\TRIASARC.h"\
	

"$(INTDIR)\IDENT.OBJ" : $(SOURCE) $(DEP_CPP_IDENT) "$(INTDIR)"\
 "$(INTDIR)\Triasarc.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\INFO.CXX

!IF  "$(CFG)" == "Triasarc - Win32 Release"

DEP_CPP_INFO_=\
	".\Geo.hxx"\
	".\Info.hxx"\
	".\Merkmdes.hxx"\
	".\Pheader.h"\
	".\Section.hxx"\
	".\Triasarc.hr"\
	".\Triasarc.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\Impexp.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\Print.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	
NODEP_CPP_INFO_=\
	".\win16\TRIASARC.h"\
	

"$(INTDIR)\INFO.OBJ" : $(SOURCE) $(DEP_CPP_INFO_) "$(INTDIR)"\
 "$(INTDIR)\Triasarc.pch"


!ELSEIF  "$(CFG)" == "Triasarc - Win32 Debug"

DEP_CPP_INFO_=\
	"..\..\INC_GLB.32\gc.h"\
	"..\..\inc_glb.32\syncthrd.hxx"\
	".\Geo.hxx"\
	".\Info.hxx"\
	".\Merkmdes.hxx"\
	".\Pheader.h"\
	".\Section.hxx"\
	".\Triasarc.hr"\
	".\Triasarc.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Impexp.hxx"\
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
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_INFO_=\
	".\win16\TRIASARC.h"\
	

"$(INTDIR)\INFO.OBJ" : $(SOURCE) $(DEP_CPP_INFO_) "$(INTDIR)"\
 "$(INTDIR)\Triasarc.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MERKMDES.CXX

!IF  "$(CFG)" == "Triasarc - Win32 Release"

DEP_CPP_MERKM=\
	".\Merkmdes.hxx"\
	".\Pheader.h"\
	".\Triasarc.hr"\
	".\Triasarc.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\defattr.h"\
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
	{$(INCLUDE)}"\Print.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\Strdup.hxx"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	
NODEP_CPP_MERKM=\
	".\win16\TRIASARC.h"\
	

"$(INTDIR)\MERKMDES.OBJ" : $(SOURCE) $(DEP_CPP_MERKM) "$(INTDIR)"\
 "$(INTDIR)\Triasarc.pch"


!ELSEIF  "$(CFG)" == "Triasarc - Win32 Debug"

DEP_CPP_MERKM=\
	"..\..\INC_GLB.32\gc.h"\
	"..\..\inc_glb.32\syncthrd.hxx"\
	".\Merkmdes.hxx"\
	".\Pheader.h"\
	".\Triasarc.hr"\
	".\Triasarc.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Impexp.hxx"\
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
	{$(INCLUDE)}"\Strdup.hxx"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_MERKM=\
	".\win16\TRIASARC.h"\
	

"$(INTDIR)\MERKMDES.OBJ" : $(SOURCE) $(DEP_CPP_MERKM) "$(INTDIR)"\
 "$(INTDIR)\Triasarc.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TRIASARC.CXX

!IF  "$(CFG)" == "Triasarc - Win32 Release"

DEP_CPP_TRIAS=\
	".\Ident.hxx"\
	".\Merkmdes.hxx"\
	".\Pheader.h"\
	".\Triasarc.hr"\
	".\Triasarc.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\Impexp.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\Print.h"\
	{$(INCLUDE)}"\Resstrg.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	
NODEP_CPP_TRIAS=\
	".\win16\TRIASARC.h"\
	

"$(INTDIR)\TRIASARC.OBJ" : $(SOURCE) $(DEP_CPP_TRIAS) "$(INTDIR)"\
 "$(INTDIR)\Triasarc.pch"


!ELSEIF  "$(CFG)" == "Triasarc - Win32 Debug"

DEP_CPP_TRIAS=\
	"..\..\INC_GLB.32\gc.h"\
	"..\..\inc_glb.32\syncthrd.hxx"\
	".\Ident.hxx"\
	".\Merkmdes.hxx"\
	".\Pheader.h"\
	".\Triasarc.hr"\
	".\Triasarc.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Impexp.hxx"\
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
	{$(INCLUDE)}"\Resstrg.h"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_TRIAS=\
	".\win16\TRIASARC.h"\
	

"$(INTDIR)\TRIASARC.OBJ" : $(SOURCE) $(DEP_CPP_TRIAS) "$(INTDIR)"\
 "$(INTDIR)\Triasarc.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\NAMEEDIT.CXX

!IF  "$(CFG)" == "Triasarc - Win32 Release"

DEP_CPP_NAMEE=\
	"..\..\INC_GLB.32\gc.h"\
	"..\..\inc_glb.32\syncthrd.hxx"\
	".\Nameedit.hxx"\
	".\Pheader.h"\
	{$(INCLUDE)}"\Bool.h"\
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
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\expfltm.hxx"\
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
	

"$(INTDIR)\NAMEEDIT.OBJ" : $(SOURCE) $(DEP_CPP_NAMEE) "$(INTDIR)"\
 "$(INTDIR)\Triasarc.pch"


!ELSEIF  "$(CFG)" == "Triasarc - Win32 Debug"

DEP_CPP_NAMEE=\
	".\Nameedit.hxx"\
	".\Pheader.h"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\Print.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	

"$(INTDIR)\NAMEEDIT.OBJ" : $(SOURCE) $(DEP_CPP_NAMEE) "$(INTDIR)"\
 "$(INTDIR)\Triasarc.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\NUMEDIT.CXX

!IF  "$(CFG)" == "Triasarc - Win32 Release"

DEP_CPP_NUMED=\
	"..\..\INC_GLB.32\gc.h"\
	"..\..\inc_glb.32\syncthrd.hxx"\
	".\Numedit.hxx"\
	".\Pheader.h"\
	{$(INCLUDE)}"\Bool.h"\
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
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\expfltm.hxx"\
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
	

"$(INTDIR)\NUMEDIT.OBJ" : $(SOURCE) $(DEP_CPP_NUMED) "$(INTDIR)"\
 "$(INTDIR)\Triasarc.pch"


!ELSEIF  "$(CFG)" == "Triasarc - Win32 Debug"

DEP_CPP_NUMED=\
	".\Numedit.hxx"\
	".\Pheader.h"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\Print.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	

"$(INTDIR)\NUMEDIT.OBJ" : $(SOURCE) $(DEP_CPP_NUMED) "$(INTDIR)"\
 "$(INTDIR)\Triasarc.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\RESOURCE.CXX

!IF  "$(CFG)" == "Triasarc - Win32 Release"

DEP_CPP_RESOU=\
	"..\..\INC_GLB.32\gc.h"\
	"..\..\inc_glb.32\syncthrd.hxx"\
	".\Pheader.h"\
	".\Triasarc.hr"\
	{$(INCLUDE)}"\Bool.h"\
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
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\expfltm.hxx"\
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
	
NODEP_CPP_RESOU=\
	".\win16\TRIASARC.h"\
	

"$(INTDIR)\RESOURCE.OBJ" : $(SOURCE) $(DEP_CPP_RESOU) "$(INTDIR)"\
 "$(INTDIR)\Triasarc.pch"


!ELSEIF  "$(CFG)" == "Triasarc - Win32 Debug"

DEP_CPP_RESOU=\
	".\Pheader.h"\
	".\Triasarc.hr"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\Print.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	
NODEP_CPP_RESOU=\
	".\win16\TRIASARC.h"\
	

"$(INTDIR)\RESOURCE.OBJ" : $(SOURCE) $(DEP_CPP_RESOU) "$(INTDIR)"\
 "$(INTDIR)\Triasarc.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SECTION.CXX

!IF  "$(CFG)" == "Triasarc - Win32 Release"

DEP_CPP_SECTI=\
	".\Ident.hxx"\
	".\Pheader.h"\
	".\Section.hxx"\
	".\Triasarc.hr"\
	".\Triasarc.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\Impexp.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\Print.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	
NODEP_CPP_SECTI=\
	".\win16\TRIASARC.h"\
	

"$(INTDIR)\SECTION.OBJ" : $(SOURCE) $(DEP_CPP_SECTI) "$(INTDIR)"\
 "$(INTDIR)\Triasarc.pch"


!ELSEIF  "$(CFG)" == "Triasarc - Win32 Debug"

DEP_CPP_SECTI=\
	"..\..\INC_GLB.32\gc.h"\
	"..\..\inc_glb.32\syncthrd.hxx"\
	".\Ident.hxx"\
	".\Pheader.h"\
	".\Section.hxx"\
	".\Triasarc.hr"\
	".\Triasarc.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Impexp.hxx"\
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
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_SECTI=\
	".\win16\TRIASARC.h"\
	

"$(INTDIR)\SECTION.OBJ" : $(SOURCE) $(DEP_CPP_SECTI) "$(INTDIR)"\
 "$(INTDIR)\Triasarc.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MERKNAME.CXX

!IF  "$(CFG)" == "Triasarc - Win32 Release"

DEP_CPP_MERKN=\
	".\Merkmdes.hxx"\
	".\Merkname.hxx"\
	".\Nameedit.hxx"\
	".\Pheader.h"\
	".\Triasarc.hr"\
	".\Triasarc.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\Impexp.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\Print.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\Waitcur.hxx"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	
NODEP_CPP_MERKN=\
	".\win16\TRIASARC.h"\
	

"$(INTDIR)\MERKNAME.OBJ" : $(SOURCE) $(DEP_CPP_MERKN) "$(INTDIR)"\
 "$(INTDIR)\Triasarc.pch"


!ELSEIF  "$(CFG)" == "Triasarc - Win32 Debug"

DEP_CPP_MERKN=\
	"..\..\INC_GLB.32\gc.h"\
	"..\..\inc_glb.32\syncthrd.hxx"\
	".\Merkmdes.hxx"\
	".\Merkname.hxx"\
	".\Nameedit.hxx"\
	".\Pheader.h"\
	".\Triasarc.hr"\
	".\Triasarc.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Impexp.hxx"\
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
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\Waitcur.hxx"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_MERKN=\
	".\win16\TRIASARC.h"\
	

"$(INTDIR)\MERKNAME.OBJ" : $(SOURCE) $(DEP_CPP_MERKN) "$(INTDIR)"\
 "$(INTDIR)\Triasarc.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\VISINFO.CXX

!IF  "$(CFG)" == "Triasarc - Win32 Release"

DEP_CPP_VISIN=\
	".\Pheader.h"\
	{$(INCLUDE)}"\Attribs.hxx"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\Print.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	

"$(INTDIR)\VISINFO.OBJ" : $(SOURCE) $(DEP_CPP_VISIN) "$(INTDIR)"\
 "$(INTDIR)\Triasarc.pch"


!ELSEIF  "$(CFG)" == "Triasarc - Win32 Debug"

DEP_CPP_VISIN=\
	"..\..\INC_GLB.32\gc.h"\
	"..\..\inc_glb.32\syncthrd.hxx"\
	".\Pheader.h"\
	{$(INCLUDE)}"\Attribs.hxx"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Gc_cpp.h"\
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
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Yxvals.h"\
	

"$(INTDIR)\VISINFO.OBJ" : $(SOURCE) $(DEP_CPP_VISIN) "$(INTDIR)"\
 "$(INTDIR)\Triasarc.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TRIASARC.RC
DEP_RSC_TRIASA=\
	".\AATFORMT.DAT"\
	".\BNDFORMT.DAT"\
	".\PATFORMT.DAT"\
	".\TICFORMT.DAT"\
	".\TRIASARC.RCV"\
	

"$(INTDIR)\TRIASARC.res" : $(SOURCE) $(DEP_RSC_TRIASA) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\COMMFIL.CXX

!IF  "$(CFG)" == "Triasarc - Win32 Release"

DEP_CPP_COMMF=\
	".\Pheader.h"\
	".\Triasarc.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\Impexp.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\Print.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	

"$(INTDIR)\COMMFIL.OBJ" : $(SOURCE) $(DEP_CPP_COMMF) "$(INTDIR)"\
 "$(INTDIR)\Triasarc.pch"


!ELSEIF  "$(CFG)" == "Triasarc - Win32 Debug"

DEP_CPP_COMMF=\
	"..\..\INC_GLB.32\gc.h"\
	"..\..\inc_glb.32\syncthrd.hxx"\
	".\Pheader.h"\
	".\Triasarc.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Impexp.hxx"\
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
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Yxvals.h"\
	

"$(INTDIR)\COMMFIL.OBJ" : $(SOURCE) $(DEP_CPP_COMMF) "$(INTDIR)"\
 "$(INTDIR)\Triasarc.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\COVER.CXX

!IF  "$(CFG)" == "Triasarc - Win32 Release"

DEP_CPP_COVER=\
	".\Cover.hxx"\
	".\Geo.hxx"\
	".\Info.hxx"\
	".\Merkmdes.hxx"\
	".\Pheader.h"\
	".\Section.hxx"\
	".\Triasarc.hr"\
	".\Triasarc.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\Impexp.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\Print.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	
NODEP_CPP_COVER=\
	".\win16\TRIASARC.h"\
	

"$(INTDIR)\COVER.OBJ" : $(SOURCE) $(DEP_CPP_COVER) "$(INTDIR)"\
 "$(INTDIR)\Triasarc.pch"


!ELSEIF  "$(CFG)" == "Triasarc - Win32 Debug"

DEP_CPP_COVER=\
	"..\..\INC_GLB.32\gc.h"\
	"..\..\inc_glb.32\syncthrd.hxx"\
	".\Cover.hxx"\
	".\Geo.hxx"\
	".\Info.hxx"\
	".\Merkmdes.hxx"\
	".\Pheader.h"\
	".\Section.hxx"\
	".\Triasarc.hr"\
	".\Triasarc.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Impexp.hxx"\
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
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_COVER=\
	".\win16\TRIASARC.h"\
	

"$(INTDIR)\COVER.OBJ" : $(SOURCE) $(DEP_CPP_COVER) "$(INTDIR)"\
 "$(INTDIR)\Triasarc.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TRIASARC.DEF

!IF  "$(CFG)" == "Triasarc - Win32 Release"

!ELSEIF  "$(CFG)" == "Triasarc - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\LIBMAIN.CXX

!IF  "$(CFG)" == "Triasarc - Win32 Release"

DEP_CPP_LIBMA=\
	"..\..\INC_GLB.32\gc.h"\
	"..\..\inc_glb.32\syncthrd.hxx"\
	".\Pheader.h"\
	{$(INCLUDE)}"\Bool.h"\
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
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\expfltm.hxx"\
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
	

"$(INTDIR)\LIBMAIN.OBJ" : $(SOURCE) $(DEP_CPP_LIBMA) "$(INTDIR)"\
 "$(INTDIR)\Triasarc.pch"


!ELSEIF  "$(CFG)" == "Triasarc - Win32 Debug"

DEP_CPP_LIBMA=\
	".\Pheader.h"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\Print.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	

"$(INTDIR)\LIBMAIN.OBJ" : $(SOURCE) $(DEP_CPP_LIBMA) "$(INTDIR)"\
 "$(INTDIR)\Triasarc.pch"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
