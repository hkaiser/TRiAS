# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=Acaddxf - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Acaddxf - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Acaddxf - Win32 Release" && "$(CFG)" !=\
 "Acaddxf - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Acaddxf.mak" CFG="Acaddxf - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Acaddxf - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Acaddxf - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "Acaddxf - Win32 Debug"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "Acaddxf - Win32 Release"

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

ALL : "..\..\..\trias\trias\ACADDXF.flt"

CLEAN : 
	-@erase "$(INTDIR)\ACADDXF.OBJ"
	-@erase "$(INTDIR)\Acaddxf.pch"
	-@erase "$(INTDIR)\ACADDXF.res"
	-@erase "$(INTDIR)\COMMFIL.OBJ"
	-@erase "$(INTDIR)\EXPCAPS.OBJ"
	-@erase "$(INTDIR)\IDENTDES.OBJ"
	-@erase "$(INTDIR)\LIBMAIN.OBJ"
	-@erase "$(INTDIR)\MERKMDES.OBJ"
	-@erase "$(INTDIR)\PALETTE.OBJ"
	-@erase "$(INTDIR)\PHEADER.OBJ"
	-@erase "$(INTDIR)\RESOURCE.OBJ"
	-@erase "$(INTDIR)\STRUTIL.OBJ"
	-@erase "$(INTDIR)\VISINFO.OBJ"
	-@erase "$(OUTDIR)\ACADDXF.exp"
	-@erase "$(OUTDIR)\ACADDXF.lib"
	-@erase "..\..\..\trias\trias\ACADDXF.flt"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /O2 /I "\Triasdev.mvc\inc.hpp" /I "\Triasdev.mvc\inc.hpp\inc" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "__XT" /D "DLL" /D "MSWIND" /D "STRICT" /D "__CV__" /Yu"pheader.h" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W3 /WX /GX /O2 /I "\Triasdev.mvc\inc.hpp" /I\
 "\Triasdev.mvc\inc.hpp\inc" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "__XT" /D\
 "DLL" /D "MSWIND" /D "STRICT" /D "__CV__" /Fp"$(INTDIR)/Acaddxf.pch"\
 /Yu"pheader.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\WinRel/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/ACADDXF.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Acaddxf.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 tfrmwork.lib cont32r.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386 /stub:"rights.exe" /out:"d:/trias/trias/ACADDXF.flt"
LINK32_FLAGS=tfrmwork.lib cont32r.lib kernel32.lib user32.lib gdi32.lib\
 winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib\
 uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll\
 /incremental:no /pdb:"$(OUTDIR)/ACADDXF.pdb" /machine:I386 /def:".\ACADDXF.DEF"\
 /stub:"rights.exe" /out:"d:/trias/trias/ACADDXF.flt"\
 /implib:"$(OUTDIR)/ACADDXF.lib" 
DEF_FILE= \
	".\ACADDXF.DEF"
LINK32_OBJS= \
	"$(INTDIR)\ACADDXF.OBJ" \
	"$(INTDIR)\ACADDXF.res" \
	"$(INTDIR)\COMMFIL.OBJ" \
	"$(INTDIR)\EXPCAPS.OBJ" \
	"$(INTDIR)\IDENTDES.OBJ" \
	"$(INTDIR)\LIBMAIN.OBJ" \
	"$(INTDIR)\MERKMDES.OBJ" \
	"$(INTDIR)\PALETTE.OBJ" \
	"$(INTDIR)\PHEADER.OBJ" \
	"$(INTDIR)\RESOURCE.OBJ" \
	"$(INTDIR)\STRUTIL.OBJ" \
	"$(INTDIR)\VISINFO.OBJ"

"..\..\..\trias\trias\ACADDXF.flt" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Acaddxf - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Windebug"
# PROP Intermediate_Dir "WinDebug"
OUTDIR=.\Windebug
INTDIR=.\WinDebug

ALL : "..\..\..\trias\trias200\acaddxf.flt"

CLEAN : 
	-@erase "$(INTDIR)\ACADDXF.OBJ"
	-@erase "$(INTDIR)\Acaddxf.pch"
	-@erase "$(INTDIR)\ACADDXF.res"
	-@erase "$(INTDIR)\COMMFIL.OBJ"
	-@erase "$(INTDIR)\EXPCAPS.OBJ"
	-@erase "$(INTDIR)\IDENTDES.OBJ"
	-@erase "$(INTDIR)\LIBMAIN.OBJ"
	-@erase "$(INTDIR)\MERKMDES.OBJ"
	-@erase "$(INTDIR)\PALETTE.OBJ"
	-@erase "$(INTDIR)\PHEADER.OBJ"
	-@erase "$(INTDIR)\RESOURCE.OBJ"
	-@erase "$(INTDIR)\STRUTIL.OBJ"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(INTDIR)\VISINFO.OBJ"
	-@erase "$(OUTDIR)\acaddxf.exp"
	-@erase "$(OUTDIR)\acaddxf.lib"
	-@erase "$(OUTDIR)\acaddxf.pdb"
	-@erase "..\..\..\trias\trias200\acaddxf.flt"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

.\Windebug\ACADDXF.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /Zi /Od /I "\Triasdev.mvc\inc.hpp" /I "\Triasdev.mvc\inc.hpp\inc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "__XT" /D "DLL" /D "MSWIND" /D "STRICT" /D "__CV__" /Yu"pheader.h" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MDd /W3 /WX /Gm /Zi /Od /I "\Triasdev.mvc\inc.hpp" /I\
 "\Triasdev.mvc\inc.hpp\inc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "__XT" /D\
 "DLL" /D "MSWIND" /D "STRICT" /D "__CV__" /Fp"$(INTDIR)/Acaddxf.pch"\
 /Yu"pheader.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\WinDebug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/ACADDXF.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Acaddxf.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 tfrm32d.lib cont32d.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib /nologo /dll /incremental:no /debug /machine:I386 /stub:"rights.exe" /out:"d:\trias\trias200\acaddxf.flt" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /profile /nodefaultlib
LINK32_FLAGS=tfrm32d.lib cont32d.lib kernel32.lib user32.lib gdi32.lib\
 winspool.lib comdlg32.lib advapi32.lib shell32.lib /nologo /dll /incremental:no\
 /pdb:"$(OUTDIR)/acaddxf.pdb" /debug /machine:I386 /def:".\ACADDXF.DEF"\
 /stub:"rights.exe" /out:"d:\trias\trias200\acaddxf.flt"\
 /implib:"$(OUTDIR)/acaddxf.lib" /SUBSYSTEM:windows,4.0 
DEF_FILE= \
	".\ACADDXF.DEF"
LINK32_OBJS= \
	"$(INTDIR)\ACADDXF.OBJ" \
	"$(INTDIR)\ACADDXF.res" \
	"$(INTDIR)\COMMFIL.OBJ" \
	"$(INTDIR)\EXPCAPS.OBJ" \
	"$(INTDIR)\IDENTDES.OBJ" \
	"$(INTDIR)\LIBMAIN.OBJ" \
	"$(INTDIR)\MERKMDES.OBJ" \
	"$(INTDIR)\PALETTE.OBJ" \
	"$(INTDIR)\PHEADER.OBJ" \
	"$(INTDIR)\RESOURCE.OBJ" \
	"$(INTDIR)\STRUTIL.OBJ" \
	"$(INTDIR)\VISINFO.OBJ"

"..\..\..\trias\trias200\acaddxf.flt" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Acaddxf - Win32 Release"
# Name "Acaddxf - Win32 Debug"

!IF  "$(CFG)" == "Acaddxf - Win32 Release"

!ELSEIF  "$(CFG)" == "Acaddxf - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ACADDXF.DEF

!IF  "$(CFG)" == "Acaddxf - Win32 Release"

!ELSEIF  "$(CFG)" == "Acaddxf - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ACADDXF.RC
DEP_RSC_ACADD=\
	".\171.sbl"\
	".\172.sbl"\
	".\173.sbl"\
	".\174.sbl"\
	".\175.sbl"\
	".\176.sbl"\
	".\177.sbl"\
	".\178.sbl"\
	".\180.sbl"\
	".\181.sbl"\
	".\182.sbl"\
	".\183.sbl"\
	".\184.sbl"\
	".\185.sbl"\
	".\186.sbl"\
	".\187.sbl"\
	".\188.sbl"\
	".\189.sbl"\
	".\190.sbl"\
	".\191.sbl"\
	".\192.sbl"\
	".\193.sbl"\
	".\194.sbl"\
	".\195.sbl"\
	".\196.sbl"\
	".\197.sbl"\
	".\198.sbl"\
	".\199.sbl"\
	".\200.sbl"\
	".\201.sbl"\
	".\202.sbl"\
	".\203.sbl"\
	".\204.sbl"\
	".\205.sbl"\
	".\206.sbl"\
	".\207.sbl"\
	".\208.sbl"\
	".\209.sbl"\
	".\21.sbl"\
	".\210.sbl"\
	".\211.sbl"\
	".\212.sbl"\
	".\213.sbl"\
	".\214.sbl"\
	".\215.sbl"\
	".\216.sbl"\
	".\217.sbl"\
	".\218.sbl"\
	".\219.sbl"\
	".\220.sbl"\
	".\222.sbl"\
	".\228.sbl"\
	".\229.sbl"\
	".\230.sbl"\
	".\231.sbl"\
	".\232.sbl"\
	".\233.sbl"\
	".\234.sbl"\
	".\235.sbl"\
	".\236.sbl"\
	".\250.sbl"\
	".\251.sbl"\
	".\252.sbl"\
	".\26.sbl"\
	".\3.sbl"\
	".\47.sbl"\
	".\5.sbl"\
	".\6.sbl"\
	".\ACADDXF.RCV"\
	".\linetab.tpl"\
	".\visinfo.tpl"\
	

"$(INTDIR)\ACADDXF.res" : $(SOURCE) $(DEP_RSC_ACADD) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRUTIL.CXX
DEP_CPP_STRUT=\
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
	

"$(INTDIR)\STRUTIL.OBJ" : $(SOURCE) $(DEP_CPP_STRUT) "$(INTDIR)"\
 "$(INTDIR)\Acaddxf.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\VISINFO.CXX
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
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\defattr.h"\
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
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Yxvals.h"\
	

"$(INTDIR)\VISINFO.OBJ" : $(SOURCE) $(DEP_CPP_VISIN) "$(INTDIR)"\
 "$(INTDIR)\Acaddxf.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\RESOURCE.CXX
DEP_CPP_RESOU=\
	"..\..\INC_GLB.32\gc.h"\
	"..\..\inc_glb.32\syncthrd.hxx"\
	".\Acaddxf.hr"\
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
	
NODEP_CPP_RESOU=\
	".\win16\acaddxf.h"\
	

"$(INTDIR)\RESOURCE.OBJ" : $(SOURCE) $(DEP_CPP_RESOU) "$(INTDIR)"\
 "$(INTDIR)\Acaddxf.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MERKMDES.CXX

!IF  "$(CFG)" == "Acaddxf - Win32 Release"

DEP_CPP_MERKM=\
	"..\..\INC_GLB.32\gc.h"\
	"..\..\inc_glb.32\syncthrd.hxx"\
	".\Acaddxf.hr"\
	".\Acaddxf.hxx"\
	".\Identdes.hxx"\
	".\Merkmdes.hxx"\
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
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Impexp.hxx"\
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
	{$(INCLUDE)}"\Strdup.hxx"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_MERKM=\
	".\win16\acaddxf.h"\
	

"$(INTDIR)\MERKMDES.OBJ" : $(SOURCE) $(DEP_CPP_MERKM) "$(INTDIR)"\
 "$(INTDIR)\Acaddxf.pch"


!ELSEIF  "$(CFG)" == "Acaddxf - Win32 Debug"

DEP_CPP_MERKM=\
	".\Acaddxf.hr"\
	".\Acaddxf.hxx"\
	".\Identdes.hxx"\
	".\Merkmdes.hxx"\
	".\Pheader.h"\
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
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
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
	".\win16\acaddxf.h"\
	

"$(INTDIR)\MERKMDES.OBJ" : $(SOURCE) $(DEP_CPP_MERKM) "$(INTDIR)"\
 "$(INTDIR)\Acaddxf.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\COMMFIL.CXX
DEP_CPP_COMMF=\
	"..\..\INC_GLB.32\gc.h"\
	"..\..\inc_glb.32\syncthrd.hxx"\
	".\Acaddxf.hxx"\
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
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Impexp.hxx"\
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
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Yxvals.h"\
	

"$(INTDIR)\COMMFIL.OBJ" : $(SOURCE) $(DEP_CPP_COMMF) "$(INTDIR)"\
 "$(INTDIR)\Acaddxf.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\EXPCAPS.CXX
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
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Impexp.hxx"\
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
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Yxvals.h"\
	

"$(INTDIR)\EXPCAPS.OBJ" : $(SOURCE) $(DEP_CPP_EXPCA) "$(INTDIR)"\
 "$(INTDIR)\Acaddxf.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ACADDXF.CXX

!IF  "$(CFG)" == "Acaddxf - Win32 Release"

DEP_CPP_ACADDX=\
	"..\..\INC_GLB.32\gc.h"\
	"..\..\inc_glb.32\syncthrd.hxx"\
	".\Acaddxf.hr"\
	".\Acaddxf.hxx"\
	".\Identdes.hxx"\
	".\Merkmdes.hxx"\
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
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Impexp.hxx"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Strdup.hxx"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_ACADDX=\
	".\win16\acaddxf.h"\
	

"$(INTDIR)\ACADDXF.OBJ" : $(SOURCE) $(DEP_CPP_ACADDX) "$(INTDIR)"\
 "$(INTDIR)\Acaddxf.pch"


!ELSEIF  "$(CFG)" == "Acaddxf - Win32 Debug"

DEP_CPP_ACADDX=\
	"..\..\INC_GLB.32\gc.h"\
	"..\..\inc_glb.32\syncthrd.hxx"\
	".\Acaddxf.hr"\
	".\Acaddxf.hxx"\
	".\Identdes.hxx"\
	".\Merkmdes.hxx"\
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
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Impexp.hxx"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Strdup.hxx"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_ACADDX=\
	".\win16\acaddxf.h"\
	

"$(INTDIR)\ACADDXF.OBJ" : $(SOURCE) $(DEP_CPP_ACADDX) "$(INTDIR)"\
 "$(INTDIR)\Acaddxf.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\IDENTDES.CXX

!IF  "$(CFG)" == "Acaddxf - Win32 Release"

DEP_CPP_IDENT=\
	"..\..\INC_GLB.32\gc.h"\
	"..\..\inc_glb.32\syncthrd.hxx"\
	".\Acaddxf.hr"\
	".\Acaddxf.hxx"\
	".\Identdes.hxx"\
	".\Merkmdes.hxx"\
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
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\expfltm.hxx"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Impexp.hxx"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Strdup.hxx"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_IDENT=\
	".\win16\acaddxf.h"\
	

"$(INTDIR)\IDENTDES.OBJ" : $(SOURCE) $(DEP_CPP_IDENT) "$(INTDIR)"\
 "$(INTDIR)\Acaddxf.pch"


!ELSEIF  "$(CFG)" == "Acaddxf - Win32 Debug"

DEP_CPP_IDENT=\
	".\Acaddxf.hr"\
	".\Acaddxf.hxx"\
	".\Identdes.hxx"\
	".\Merkmdes.hxx"\
	".\Pheader.h"\
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
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
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
	
NODEP_CPP_IDENT=\
	".\win16\acaddxf.h"\
	

"$(INTDIR)\IDENTDES.OBJ" : $(SOURCE) $(DEP_CPP_IDENT) "$(INTDIR)"\
 "$(INTDIR)\Acaddxf.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PHEADER.CXX
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
	

!IF  "$(CFG)" == "Acaddxf - Win32 Release"

# ADD CPP /Yc"pheader.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O2 /I "\Triasdev.mvc\inc.hpp" /I\
 "\Triasdev.mvc\inc.hpp\inc" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "__XT" /D\
 "DLL" /D "MSWIND" /D "STRICT" /D "__CV__" /Fp"$(INTDIR)/Acaddxf.pch"\
 /Yc"pheader.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\PHEADER.OBJ" : $(SOURCE) $(DEP_CPP_PHEAD) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Acaddxf.pch" : $(SOURCE) $(DEP_CPP_PHEAD) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Acaddxf - Win32 Debug"

# ADD CPP /Yc"pheader.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /Zi /Od /I "\Triasdev.mvc\inc.hpp" /I\
 "\Triasdev.mvc\inc.hpp\inc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "__XT" /D\
 "DLL" /D "MSWIND" /D "STRICT" /D "__CV__" /Fp"$(INTDIR)/Acaddxf.pch"\
 /Yc"pheader.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\PHEADER.OBJ" : $(SOURCE) $(DEP_CPP_PHEAD) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Acaddxf.pch" : $(SOURCE) $(DEP_CPP_PHEAD) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\LIBMAIN.CXX
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
 "$(INTDIR)\Acaddxf.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\PALETTE.CXX
DEP_CPP_PALET=\
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
	

"$(INTDIR)\PALETTE.OBJ" : $(SOURCE) $(DEP_CPP_PALET) "$(INTDIR)"\
 "$(INTDIR)\Acaddxf.pch"


# End Source File
# End Target
# End Project
################################################################################
