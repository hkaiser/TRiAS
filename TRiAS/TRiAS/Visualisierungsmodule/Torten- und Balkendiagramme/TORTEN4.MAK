# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=torten - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to torten - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "torten - Win32 Release" && "$(CFG)" != "torten - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "TORTEN4.MAK" CFG="torten - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "torten - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "torten - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "torten - Win32 Debug"
CPP=cl.exe
MTL=mktyplib.exe
RSC=rc.exe

!IF  "$(CFG)" == "torten - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\torten.vmd"

CLEAN : 
	-@erase "$(INTDIR)\CBMPBOX.OBJ"
	-@erase "$(INTDIR)\CPALETTE.OBJ"
	-@erase "$(INTDIR)\CPICBOX.OBJ"
	-@erase "$(INTDIR)\DCUSTVIS.OBJ"
	-@erase "$(INTDIR)\DRAWBALK.OBJ"
	-@erase "$(INTDIR)\DRAWRECT.OBJ"
	-@erase "$(INTDIR)\DRAWTORT.OBJ"
	-@erase "$(INTDIR)\FIXUPDC.OBJ"
	-@erase "$(INTDIR)\IMPCUSTM.OBJ"
	-@erase "$(INTDIR)\NUMEDITX.OBJ"
	-@erase "$(INTDIR)\PALTREE.OBJ"
	-@erase "$(INTDIR)\Regvism.obj"
	-@erase "$(INTDIR)\STRUTIL.OBJ"
	-@erase "$(INTDIR)\TORTEN32.res"
	-@erase "$(INTDIR)\TORTEN4.pch"
	-@erase "$(INTDIR)\TORTENP.OBJ"
	-@erase "$(INTDIR)\TYPESEL.OBJ"
	-@erase "$(INTDIR)\VISINFO.OBJ"
	-@erase "$(OUTDIR)\torten.exp"
	-@erase "$(OUTDIR)\torten.lib"
	-@erase "$(OUTDIR)\torten.vmd"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(OUTDIR)/torten.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "MSWIND" /D "__XT" /D "DLL" /D "__DEXPROCS" /D "__CV__" /D "__VMD_DLL__" /Yu"tortenp.hxx" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "STRICT" /D "MSWIND" /D "__XT" /D "DLL" /D "__DEXPROCS" /D "__CV__" /D\
 "__VMD_DLL__" /Fp"$(INTDIR)/TORTEN4.pch" /Yu"tortenp.hxx" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/TORTEN32.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/TORTEN4.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 tfrmwork.lib cont32r.lib stdcppr.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /stub:"obj32/rights.exe" /out:"Release/torten.vmd" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=tfrmwork.lib cont32r.lib stdcppr.lib kernel32.lib user32.lib\
 gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib\
 oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no\
 /pdb:"$(OUTDIR)/torten.pdb" /machine:I386 /def:".\OBJ32\TORTEN32.DEF"\
 /stub:"obj32/rights.exe" /out:"$(OUTDIR)/torten.vmd"\
 /implib:"$(OUTDIR)/torten.lib" /SUBSYSTEM:windows,4.0 
DEF_FILE= \
	".\OBJ32\TORTEN32.DEF"
LINK32_OBJS= \
	"$(INTDIR)\CBMPBOX.OBJ" \
	"$(INTDIR)\CPALETTE.OBJ" \
	"$(INTDIR)\CPICBOX.OBJ" \
	"$(INTDIR)\DCUSTVIS.OBJ" \
	"$(INTDIR)\DRAWBALK.OBJ" \
	"$(INTDIR)\DRAWRECT.OBJ" \
	"$(INTDIR)\DRAWTORT.OBJ" \
	"$(INTDIR)\FIXUPDC.OBJ" \
	"$(INTDIR)\IMPCUSTM.OBJ" \
	"$(INTDIR)\NUMEDITX.OBJ" \
	"$(INTDIR)\PALTREE.OBJ" \
	"$(INTDIR)\Regvism.obj" \
	"$(INTDIR)\STRUTIL.OBJ" \
	"$(INTDIR)\TORTEN32.res" \
	"$(INTDIR)\TORTENP.OBJ" \
	"$(INTDIR)\TYPESEL.OBJ" \
	"$(INTDIR)\VISINFO.OBJ"

"$(OUTDIR)\torten.vmd" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "torten - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\tortend.vmd" "$(OUTDIR)\TORTEN4.bsc"

CLEAN : 
	-@erase "$(INTDIR)\CBMPBOX.OBJ"
	-@erase "$(INTDIR)\CBMPBOX.SBR"
	-@erase "$(INTDIR)\CPALETTE.OBJ"
	-@erase "$(INTDIR)\CPALETTE.SBR"
	-@erase "$(INTDIR)\CPICBOX.OBJ"
	-@erase "$(INTDIR)\CPICBOX.SBR"
	-@erase "$(INTDIR)\DCUSTVIS.OBJ"
	-@erase "$(INTDIR)\DCUSTVIS.SBR"
	-@erase "$(INTDIR)\DRAWBALK.OBJ"
	-@erase "$(INTDIR)\DRAWBALK.SBR"
	-@erase "$(INTDIR)\DRAWRECT.OBJ"
	-@erase "$(INTDIR)\DRAWRECT.SBR"
	-@erase "$(INTDIR)\DRAWTORT.OBJ"
	-@erase "$(INTDIR)\DRAWTORT.SBR"
	-@erase "$(INTDIR)\FIXUPDC.OBJ"
	-@erase "$(INTDIR)\FIXUPDC.SBR"
	-@erase "$(INTDIR)\IMPCUSTM.OBJ"
	-@erase "$(INTDIR)\IMPCUSTM.SBR"
	-@erase "$(INTDIR)\NUMEDITX.OBJ"
	-@erase "$(INTDIR)\NUMEDITX.SBR"
	-@erase "$(INTDIR)\PALTREE.OBJ"
	-@erase "$(INTDIR)\PALTREE.SBR"
	-@erase "$(INTDIR)\Regvism.obj"
	-@erase "$(INTDIR)\Regvism.sbr"
	-@erase "$(INTDIR)\STRUTIL.OBJ"
	-@erase "$(INTDIR)\STRUTIL.SBR"
	-@erase "$(INTDIR)\TORTEN32.res"
	-@erase "$(INTDIR)\tortend.idb"
	-@erase "$(INTDIR)\tortend.pch"
	-@erase "$(INTDIR)\tortend.pdb"
	-@erase "$(INTDIR)\TORTENP.OBJ"
	-@erase "$(INTDIR)\TORTENP.SBR"
	-@erase "$(INTDIR)\TYPESEL.OBJ"
	-@erase "$(INTDIR)\TYPESEL.SBR"
	-@erase "$(INTDIR)\VISINFO.OBJ"
	-@erase "$(INTDIR)\VISINFO.SBR"
	-@erase "$(OUTDIR)\TORTEN4.bsc"
	-@erase "$(OUTDIR)\tortend.exp"
	-@erase "$(OUTDIR)\tortend.ilk"
	-@erase "$(OUTDIR)\tortend.lib"
	-@erase "$(OUTDIR)\tortend.vmd"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(OUTDIR)/torten.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "MSWIND" /D "__XT" /D "DLL" /D "__DEXPROCS" /D "__CV__" /D "__VMD_DLL__" /FR /Fp"Debug/tortend.pch" /Yu"tortenp.hxx" /Fd"Debug/tortend.pdb" /c
CPP_PROJ=/nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "MSWIND" /D "__XT" /D "DLL" /D "__DEXPROCS" /D\
 "__CV__" /D "__VMD_DLL__" /FR"$(INTDIR)/" /Fp"$(INTDIR)/tortend.pch"\
 /Yu"tortenp.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/tortend.pdb" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/TORTEN32.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/TORTEN4.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\CBMPBOX.SBR" \
	"$(INTDIR)\CPALETTE.SBR" \
	"$(INTDIR)\CPICBOX.SBR" \
	"$(INTDIR)\DCUSTVIS.SBR" \
	"$(INTDIR)\DRAWBALK.SBR" \
	"$(INTDIR)\DRAWRECT.SBR" \
	"$(INTDIR)\DRAWTORT.SBR" \
	"$(INTDIR)\FIXUPDC.SBR" \
	"$(INTDIR)\IMPCUSTM.SBR" \
	"$(INTDIR)\NUMEDITX.SBR" \
	"$(INTDIR)\PALTREE.SBR" \
	"$(INTDIR)\Regvism.sbr" \
	"$(INTDIR)\STRUTIL.SBR" \
	"$(INTDIR)\TORTENP.SBR" \
	"$(INTDIR)\TYPESEL.SBR" \
	"$(INTDIR)\VISINFO.SBR"

"$(OUTDIR)\TORTEN4.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 tfrm32d.lib cont32d.lib stdcppd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /stub:"obj32/rights.exe" /out:"Debug/tortend.vmd" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=tfrm32d.lib cont32d.lib stdcppd.lib kernel32.lib user32.lib\
 gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib\
 oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes\
 /pdb:"$(OUTDIR)/tortend.pdb" /debug /machine:I386 /def:".\OBJ32\TORTEN32.DEF"\
 /stub:"obj32/rights.exe" /out:"$(OUTDIR)/tortend.vmd"\
 /implib:"$(OUTDIR)/tortend.lib" /SUBSYSTEM:windows,4.0 
DEF_FILE= \
	".\OBJ32\TORTEN32.DEF"
LINK32_OBJS= \
	"$(INTDIR)\CBMPBOX.OBJ" \
	"$(INTDIR)\CPALETTE.OBJ" \
	"$(INTDIR)\CPICBOX.OBJ" \
	"$(INTDIR)\DCUSTVIS.OBJ" \
	"$(INTDIR)\DRAWBALK.OBJ" \
	"$(INTDIR)\DRAWRECT.OBJ" \
	"$(INTDIR)\DRAWTORT.OBJ" \
	"$(INTDIR)\FIXUPDC.OBJ" \
	"$(INTDIR)\IMPCUSTM.OBJ" \
	"$(INTDIR)\NUMEDITX.OBJ" \
	"$(INTDIR)\PALTREE.OBJ" \
	"$(INTDIR)\Regvism.obj" \
	"$(INTDIR)\STRUTIL.OBJ" \
	"$(INTDIR)\TORTEN32.res" \
	"$(INTDIR)\TORTENP.OBJ" \
	"$(INTDIR)\TYPESEL.OBJ" \
	"$(INTDIR)\VISINFO.OBJ"

"$(OUTDIR)\tortend.vmd" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "torten - Win32 Release"
# Name "torten - Win32 Debug"

!IF  "$(CFG)" == "torten - Win32 Release"

!ELSEIF  "$(CFG)" == "torten - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\TYPESEL.CXX

!IF  "$(CFG)" == "torten - Win32 Release"

DEP_CPP_TYPES=\
	".\cpalette.hxx"\
	".\cpicbox.hxx"\
	".\impcustm.hxx"\
	".\paltree.hxx"\
	".\paltree.inl"\
	".\torten.h"\
	".\tortenp.hxx"\
	".\typesel.h"\
	".\typesel.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Icustom.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
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
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\TYPESEL.OBJ" : $(SOURCE) $(DEP_CPP_TYPES) "$(INTDIR)"\
 "$(INTDIR)\TORTEN4.pch"


!ELSEIF  "$(CFG)" == "torten - Win32 Debug"

DEP_CPP_TYPES=\
	".\cpalette.hxx"\
	".\cpicbox.hxx"\
	".\impcustm.hxx"\
	".\paltree.hxx"\
	".\paltree.inl"\
	".\torten.h"\
	".\tortenp.hxx"\
	".\typesel.h"\
	".\typesel.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Icustom.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
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
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\TYPESEL.OBJ" : $(SOURCE) $(DEP_CPP_TYPES) "$(INTDIR)"\
 "$(INTDIR)\tortend.pch"

"$(INTDIR)\TYPESEL.SBR" : $(SOURCE) $(DEP_CPP_TYPES) "$(INTDIR)"\
 "$(INTDIR)\tortend.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DCUSTVIS.CXX

!IF  "$(CFG)" == "torten - Win32 Release"

DEP_CPP_DCUST=\
	".\dcustvis.hxx"\
	".\impcustm.hxx"\
	".\torten.h"\
	".\tortenid.h"\
	".\tortenp.hxx"\
	".\tortenr.h"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Icustom.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\vismguid.h"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\DCUSTVIS.OBJ" : $(SOURCE) $(DEP_CPP_DCUST) "$(INTDIR)"\
 "$(INTDIR)\TORTEN4.pch"


!ELSEIF  "$(CFG)" == "torten - Win32 Debug"

DEP_CPP_DCUST=\
	".\dcustvis.hxx"\
	".\impcustm.hxx"\
	".\torten.h"\
	".\tortenid.h"\
	".\tortenp.hxx"\
	".\tortenr.h"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Icustom.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\vismguid.h"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\DCUSTVIS.OBJ" : $(SOURCE) $(DEP_CPP_DCUST) "$(INTDIR)"\
 "$(INTDIR)\tortend.pch"

"$(INTDIR)\DCUSTVIS.SBR" : $(SOURCE) $(DEP_CPP_DCUST) "$(INTDIR)"\
 "$(INTDIR)\tortend.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRUTIL.CXX

!IF  "$(CFG)" == "torten - Win32 Release"

DEP_CPP_STRUT=\
	".\tortenp.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\STRUTIL.OBJ" : $(SOURCE) $(DEP_CPP_STRUT) "$(INTDIR)"\
 "$(INTDIR)\TORTEN4.pch"


!ELSEIF  "$(CFG)" == "torten - Win32 Debug"

DEP_CPP_STRUT=\
	".\tortenp.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\STRUTIL.OBJ" : $(SOURCE) $(DEP_CPP_STRUT) "$(INTDIR)"\
 "$(INTDIR)\tortend.pch"

"$(INTDIR)\STRUTIL.SBR" : $(SOURCE) $(DEP_CPP_STRUT) "$(INTDIR)"\
 "$(INTDIR)\tortend.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DRAWTORT.CXX

!IF  "$(CFG)" == "torten - Win32 Release"

DEP_CPP_DRAWT=\
	".\fixupdc.hxx"\
	".\impcustm.hxx"\
	".\paltree.hxx"\
	".\torten.h"\
	".\tortenp.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Icustom.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\DRAWTORT.OBJ" : $(SOURCE) $(DEP_CPP_DRAWT) "$(INTDIR)"\
 "$(INTDIR)\TORTEN4.pch"


!ELSEIF  "$(CFG)" == "torten - Win32 Debug"

DEP_CPP_DRAWT=\
	".\fixupdc.hxx"\
	".\impcustm.hxx"\
	".\paltree.hxx"\
	".\torten.h"\
	".\tortenp.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Icustom.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\DRAWTORT.OBJ" : $(SOURCE) $(DEP_CPP_DRAWT) "$(INTDIR)"\
 "$(INTDIR)\tortend.pch"

"$(INTDIR)\DRAWTORT.SBR" : $(SOURCE) $(DEP_CPP_DRAWT) "$(INTDIR)"\
 "$(INTDIR)\tortend.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PALTREE.CXX

!IF  "$(CFG)" == "torten - Win32 Release"

DEP_CPP_PALTR=\
	".\impcustm.hxx"\
	".\paltree.hxx"\
	".\paltree.inl"\
	".\tortenp.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Icustom.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\PALTREE.OBJ" : $(SOURCE) $(DEP_CPP_PALTR) "$(INTDIR)"\
 "$(INTDIR)\TORTEN4.pch"


!ELSEIF  "$(CFG)" == "torten - Win32 Debug"

DEP_CPP_PALTR=\
	".\impcustm.hxx"\
	".\paltree.hxx"\
	".\paltree.inl"\
	".\tortenp.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Icustom.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\PALTREE.OBJ" : $(SOURCE) $(DEP_CPP_PALTR) "$(INTDIR)"\
 "$(INTDIR)\tortend.pch"

"$(INTDIR)\PALTREE.SBR" : $(SOURCE) $(DEP_CPP_PALTR) "$(INTDIR)"\
 "$(INTDIR)\tortend.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DRAWBALK.CXX

!IF  "$(CFG)" == "torten - Win32 Release"

DEP_CPP_DRAWB=\
	".\fixupdc.hxx"\
	".\impcustm.hxx"\
	".\paltree.hxx"\
	".\torten.h"\
	".\tortenp.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Icustom.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\DRAWBALK.OBJ" : $(SOURCE) $(DEP_CPP_DRAWB) "$(INTDIR)"\
 "$(INTDIR)\TORTEN4.pch"


!ELSEIF  "$(CFG)" == "torten - Win32 Debug"

DEP_CPP_DRAWB=\
	".\fixupdc.hxx"\
	".\impcustm.hxx"\
	".\paltree.hxx"\
	".\torten.h"\
	".\tortenp.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Icustom.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\DRAWBALK.OBJ" : $(SOURCE) $(DEP_CPP_DRAWB) "$(INTDIR)"\
 "$(INTDIR)\tortend.pch"

"$(INTDIR)\DRAWBALK.SBR" : $(SOURCE) $(DEP_CPP_DRAWB) "$(INTDIR)"\
 "$(INTDIR)\tortend.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\IMPCUSTM.CXX

!IF  "$(CFG)" == "torten - Win32 Release"

DEP_CPP_IMPCU=\
	".\impcustm.hxx"\
	".\paltree.hxx"\
	".\torten.h"\
	".\tortenid.h"\
	".\tortenp.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Icustom.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\vismguid.h"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\IMPCUSTM.OBJ" : $(SOURCE) $(DEP_CPP_IMPCU) "$(INTDIR)"\
 "$(INTDIR)\TORTEN4.pch"


!ELSEIF  "$(CFG)" == "torten - Win32 Debug"

DEP_CPP_IMPCU=\
	".\impcustm.hxx"\
	".\paltree.hxx"\
	".\torten.h"\
	".\tortenid.h"\
	".\tortenp.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Icustom.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\vismguid.h"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\IMPCUSTM.OBJ" : $(SOURCE) $(DEP_CPP_IMPCU) "$(INTDIR)"\
 "$(INTDIR)\tortend.pch"

"$(INTDIR)\IMPCUSTM.SBR" : $(SOURCE) $(DEP_CPP_IMPCU) "$(INTDIR)"\
 "$(INTDIR)\tortend.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CPALETTE.CXX

!IF  "$(CFG)" == "torten - Win32 Release"

DEP_CPP_CPALE=\
	".\cpalette.hxx"\
	".\fixupdc.hxx"\
	".\impcustm.hxx"\
	".\paltree.hxx"\
	".\paltree.inl"\
	".\torten.h"\
	".\tortenp.hxx"\
	".\typesel.h"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Icustom.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
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
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\CPALETTE.OBJ" : $(SOURCE) $(DEP_CPP_CPALE) "$(INTDIR)"\
 "$(INTDIR)\TORTEN4.pch"


!ELSEIF  "$(CFG)" == "torten - Win32 Debug"

DEP_CPP_CPALE=\
	".\cpalette.hxx"\
	".\fixupdc.hxx"\
	".\impcustm.hxx"\
	".\paltree.hxx"\
	".\paltree.inl"\
	".\torten.h"\
	".\tortenp.hxx"\
	".\typesel.h"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Icustom.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\ODDLGWIN.HXX"\
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
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\CPALETTE.OBJ" : $(SOURCE) $(DEP_CPP_CPALE) "$(INTDIR)"\
 "$(INTDIR)\tortend.pch"

"$(INTDIR)\CPALETTE.SBR" : $(SOURCE) $(DEP_CPP_CPALE) "$(INTDIR)"\
 "$(INTDIR)\tortend.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CPICBOX.CXX

!IF  "$(CFG)" == "torten - Win32 Release"

DEP_CPP_CPICB=\
	".\cpicbox.hxx"\
	".\impcustm.hxx"\
	".\tortenp.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Icustom.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\CPICBOX.OBJ" : $(SOURCE) $(DEP_CPP_CPICB) "$(INTDIR)"\
 "$(INTDIR)\TORTEN4.pch"


!ELSEIF  "$(CFG)" == "torten - Win32 Debug"

DEP_CPP_CPICB=\
	".\cpicbox.hxx"\
	".\impcustm.hxx"\
	".\tortenp.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Icustom.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\CPICBOX.OBJ" : $(SOURCE) $(DEP_CPP_CPICB) "$(INTDIR)"\
 "$(INTDIR)\tortend.pch"

"$(INTDIR)\CPICBOX.SBR" : $(SOURCE) $(DEP_CPP_CPICB) "$(INTDIR)"\
 "$(INTDIR)\tortend.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FIXUPDC.CXX

!IF  "$(CFG)" == "torten - Win32 Release"

DEP_CPP_FIXUP=\
	".\fixupdc.hxx"\
	".\tortenp.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\FIXUPDC.OBJ" : $(SOURCE) $(DEP_CPP_FIXUP) "$(INTDIR)"\
 "$(INTDIR)\TORTEN4.pch"


!ELSEIF  "$(CFG)" == "torten - Win32 Debug"

DEP_CPP_FIXUP=\
	".\fixupdc.hxx"\
	".\tortenp.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\FIXUPDC.OBJ" : $(SOURCE) $(DEP_CPP_FIXUP) "$(INTDIR)"\
 "$(INTDIR)\tortend.pch"

"$(INTDIR)\FIXUPDC.SBR" : $(SOURCE) $(DEP_CPP_FIXUP) "$(INTDIR)"\
 "$(INTDIR)\tortend.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TORTENP.CXX

!IF  "$(CFG)" == "torten - Win32 Release"

DEP_CPP_TORTE=\
	".\tortenp.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\VMDM.HXX"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	
# ADD CPP /Yc"tortenp.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "STRICT" /D "MSWIND" /D "__XT" /D "DLL" /D "__DEXPROCS" /D "__CV__" /D\
 "__VMD_DLL__" /Fp"$(INTDIR)/TORTEN4.pch" /Yc"tortenp.hxx" /Fo"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\TORTENP.OBJ" : $(SOURCE) $(DEP_CPP_TORTE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\TORTEN4.pch" : $(SOURCE) $(DEP_CPP_TORTE) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "torten - Win32 Debug"

DEP_CPP_TORTE=\
	".\tortenp.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\VMDM.HXX"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	
# ADD CPP /Yc"tortenp.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "MSWIND" /D "__XT" /D "DLL" /D "__DEXPROCS" /D\
 "__CV__" /D "__VMD_DLL__" /FR"$(INTDIR)/" /Fp"$(INTDIR)/tortend.pch"\
 /Yc"tortenp.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/tortend.pdb" /c $(SOURCE) \
	

"$(INTDIR)\TORTENP.OBJ" : $(SOURCE) $(DEP_CPP_TORTE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\TORTENP.SBR" : $(SOURCE) $(DEP_CPP_TORTE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\tortend.pch" : $(SOURCE) $(DEP_CPP_TORTE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CBMPBOX.CXX

!IF  "$(CFG)" == "torten - Win32 Release"

DEP_CPP_CBMPB=\
	".\impcustm.hxx"\
	".\tortenp.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
	{$(INCLUDE)}"\CBMPBOX.HXX"\
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
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Icustom.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\CBMPBOX.OBJ" : $(SOURCE) $(DEP_CPP_CBMPB) "$(INTDIR)"\
 "$(INTDIR)\TORTEN4.pch"


!ELSEIF  "$(CFG)" == "torten - Win32 Debug"

DEP_CPP_CBMPB=\
	".\impcustm.hxx"\
	".\tortenp.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
	{$(INCLUDE)}"\CBMPBOX.HXX"\
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
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Icustom.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\CBMPBOX.OBJ" : $(SOURCE) $(DEP_CPP_CBMPB) "$(INTDIR)"\
 "$(INTDIR)\tortend.pch"

"$(INTDIR)\CBMPBOX.SBR" : $(SOURCE) $(DEP_CPP_CBMPB) "$(INTDIR)"\
 "$(INTDIR)\tortend.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\VISINFO.CXX

!IF  "$(CFG)" == "torten - Win32 Release"

DEP_CPP_VISIN=\
	".\tortenp.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\VISINFO.OBJ" : $(SOURCE) $(DEP_CPP_VISIN) "$(INTDIR)"\
 "$(INTDIR)\TORTEN4.pch"


!ELSEIF  "$(CFG)" == "torten - Win32 Debug"

DEP_CPP_VISIN=\
	".\tortenp.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\VISINFO.OBJ" : $(SOURCE) $(DEP_CPP_VISIN) "$(INTDIR)"\
 "$(INTDIR)\tortend.pch"

"$(INTDIR)\VISINFO.SBR" : $(SOURCE) $(DEP_CPP_VISIN) "$(INTDIR)"\
 "$(INTDIR)\tortend.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\NUMEDITX.CXX

!IF  "$(CFG)" == "torten - Win32 Release"

DEP_CPP_NUMED=\
	".\tortenp.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\numeditx.hxx"\
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
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\NUMEDITX.OBJ" : $(SOURCE) $(DEP_CPP_NUMED) "$(INTDIR)"\
 "$(INTDIR)\TORTEN4.pch"


!ELSEIF  "$(CFG)" == "torten - Win32 Debug"

DEP_CPP_NUMED=\
	".\tortenp.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\numeditx.hxx"\
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
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\NUMEDITX.OBJ" : $(SOURCE) $(DEP_CPP_NUMED) "$(INTDIR)"\
 "$(INTDIR)\tortend.pch"

"$(INTDIR)\NUMEDITX.SBR" : $(SOURCE) $(DEP_CPP_NUMED) "$(INTDIR)"\
 "$(INTDIR)\tortend.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DRAWRECT.CXX

!IF  "$(CFG)" == "torten - Win32 Release"

# SUBTRACT CPP /D "__CV__" /Yu

"$(INTDIR)\DRAWRECT.OBJ" : $(SOURCE) "$(INTDIR)"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "STRICT" /D "MSWIND" /D "__XT" /D "DLL" /D "__DEXPROCS" /D "__VMD_DLL__"\
 /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "torten - Win32 Debug"

# SUBTRACT CPP /D "__CV__" /Yu

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "MSWIND" /D "__XT" /D "DLL" /D "__DEXPROCS" /D\
 "__VMD_DLL__" /FR"$(INTDIR)/" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/tortend.pdb" /c\
 $(SOURCE) \
	

"$(INTDIR)\DRAWRECT.OBJ" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\DRAWRECT.SBR" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Regvism.cxx

!IF  "$(CFG)" == "torten - Win32 Release"

DEP_CPP_REGVI=\
	".\torten.h"\
	".\tortenp.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\Regvism.obj" : $(SOURCE) $(DEP_CPP_REGVI) "$(INTDIR)"\
 "$(INTDIR)\TORTEN4.pch"


!ELSEIF  "$(CFG)" == "torten - Win32 Debug"

DEP_CPP_REGVI=\
	".\torten.h"\
	".\tortenp.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\Regvism.obj" : $(SOURCE) $(DEP_CPP_REGVI) "$(INTDIR)"\
 "$(INTDIR)\tortend.pch"

"$(INTDIR)\Regvism.sbr" : $(SOURCE) $(DEP_CPP_REGVI) "$(INTDIR)"\
 "$(INTDIR)\tortend.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\OBJ32\TORTEN32.DEF

!IF  "$(CFG)" == "torten - Win32 Release"

!ELSEIF  "$(CFG)" == "torten - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\OBJ32\TORTEN32.RC
DEP_RSC_TORTEN=\
	".\OBJ32\torten32.rcv"\
	
NODEP_RSC_TORTEN=\
	".\OBJ32\torten.h"\
	".\OBJ32\typesel.h"\
	

!IF  "$(CFG)" == "torten - Win32 Release"


"$(INTDIR)\TORTEN32.res" : $(SOURCE) $(DEP_RSC_TORTEN) "$(INTDIR)"
   $(RSC) /l 0x407 /fo"$(INTDIR)/TORTEN32.res" /i "OBJ32" /d "NDEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "torten - Win32 Debug"


"$(INTDIR)\TORTEN32.res" : $(SOURCE) $(DEP_RSC_TORTEN) "$(INTDIR)"
   $(RSC) /l 0x407 /fo"$(INTDIR)/TORTEN32.res" /i "OBJ32" /d "_DEBUG" $(SOURCE)


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
