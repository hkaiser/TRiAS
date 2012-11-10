# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=Stat32 - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Stat32 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Stat32 - Win32 Release" && "$(CFG)" != "Stat32 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Stat32.mak" CFG="Stat32 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Stat32 - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Stat32 - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "Stat32 - Win32 Debug"
MTL=mktyplib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Stat32 - Win32 Release"

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
# Begin Custom Macros
TargetName=geostat
# End Custom Macros

ALL : "$(OUTDIR)\geostat.ext" "c:\programme\trias\trias\geostat.ext"

CLEAN : 
	-@erase "$(INTDIR)\Classgi.obj"
	-@erase "$(INTDIR)\Classkey.obj"
	-@erase "$(INTDIR)\Dbclass.obj"
	-@erase "$(INTDIR)\Dbinfo.obj"
	-@erase "$(INTDIR)\Dblnumed.obj"
	-@erase "$(INTDIR)\Geostat.obj"
	-@erase "$(INTDIR)\Idkey.obj"
	-@erase "$(INTDIR)\Objkey.obj"
	-@erase "$(INTDIR)\Objprop.obj"
	-@erase "$(INTDIR)\Sclipbrd.obj"
	-@erase "$(INTDIR)\Stat32.pch"
	-@erase "$(INTDIR)\Stat32.res"
	-@erase "$(INTDIR)\Statifce.obj"
	-@erase "$(INTDIR)\Statistp.obj"
	-@erase "$(INTDIR)\StatPage.obj"
	-@erase "$(INTDIR)\Stohwnd.obj"
	-@erase "$(INTDIR)\Strutil.obj"
	-@erase "$(INTDIR)\Trfkoord.obj"
	-@erase "$(INTDIR)\Trfvect.obj"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\geostat.exp"
	-@erase "$(OUTDIR)\geostat.ext"
	-@erase "$(OUTDIR)\geostat.lib"
	-@erase ".\macro\Topolog.ebc"
	-@erase "c:\programme\trias\trias\geostat.ext"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /Od /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__XT" /D "__DEXPROCS" /D "__XTENSNDLL__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D "EBWIN32" /D "QI_EXCEPTION" /Yu"statistp.hxx" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W3 /WX /GX /Zi /Od /D "NDEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "STRICT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__XT" /D "__DEXPROCS" /D\
 "__XTENSNDLL__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D "EBWIN32" /D\
 "QI_EXCEPTION" /Fp"$(INTDIR)/Stat32.pch" /Yu"statistp.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\WinRel/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /i ".." /d "NDEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/Stat32.res" /i ".." /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Stat32.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ixtnsr42.lib cont32r.lib tfrmwork.lib stdcppr.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386 /stub:"rights.exe" /out:"WinRel/geostat.ext"
LINK32_FLAGS=ixtnsr42.lib cont32r.lib tfrmwork.lib stdcppr.lib winmm.lib\
 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib\
 shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo\
 /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)/geostat.pdb"\
 /machine:I386 /def:".\Stat32.def" /stub:"rights.exe"\
 /out:"$(OUTDIR)/geostat.ext" /implib:"$(OUTDIR)/geostat.lib" 
DEF_FILE= \
	".\Stat32.def"
LINK32_OBJS= \
	"$(INTDIR)\Classgi.obj" \
	"$(INTDIR)\Classkey.obj" \
	"$(INTDIR)\Dbclass.obj" \
	"$(INTDIR)\Dbinfo.obj" \
	"$(INTDIR)\Dblnumed.obj" \
	"$(INTDIR)\Geostat.obj" \
	"$(INTDIR)\Idkey.obj" \
	"$(INTDIR)\Objkey.obj" \
	"$(INTDIR)\Objprop.obj" \
	"$(INTDIR)\Sclipbrd.obj" \
	"$(INTDIR)\Stat32.res" \
	"$(INTDIR)\Statifce.obj" \
	"$(INTDIR)\Statistp.obj" \
	"$(INTDIR)\StatPage.obj" \
	"$(INTDIR)\Stohwnd.obj" \
	"$(INTDIR)\Strutil.obj" \
	"$(INTDIR)\Trfkoord.obj" \
	"$(INTDIR)\Trfvect.obj"

"$(OUTDIR)\geostat.ext" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying Target to Destination ...
TargetPath=.\WinRel\geostat.ext
TargetName=geostat
InputPath=.\WinRel\geostat.ext
SOURCE=$(InputPath)

"c:\programme\trias\trias\$(TargetName).ext" : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
   copy "$(TargetPath)" c:\programme\trias\trias

# End Custom Build

!ELSEIF  "$(CFG)" == "Stat32 - Win32 Debug"

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
# Begin Custom Macros
TargetName=geostatd
# End Custom Macros

ALL : "$(OUTDIR)\geostatd.ext" "$(OUTDIR)\Stat32.bsc"\
 "c:\trias\trias200.deb\geostatd.ext"

CLEAN : 
	-@erase "$(INTDIR)\Classgi.obj"
	-@erase "$(INTDIR)\Classgi.sbr"
	-@erase "$(INTDIR)\Classkey.obj"
	-@erase "$(INTDIR)\Classkey.sbr"
	-@erase "$(INTDIR)\Dbclass.obj"
	-@erase "$(INTDIR)\Dbclass.sbr"
	-@erase "$(INTDIR)\Dbinfo.obj"
	-@erase "$(INTDIR)\Dbinfo.sbr"
	-@erase "$(INTDIR)\Dblnumed.obj"
	-@erase "$(INTDIR)\Dblnumed.sbr"
	-@erase "$(INTDIR)\Geostat.obj"
	-@erase "$(INTDIR)\Geostat.sbr"
	-@erase "$(INTDIR)\Idkey.obj"
	-@erase "$(INTDIR)\Idkey.sbr"
	-@erase "$(INTDIR)\Objkey.obj"
	-@erase "$(INTDIR)\Objkey.sbr"
	-@erase "$(INTDIR)\Objprop.obj"
	-@erase "$(INTDIR)\Objprop.sbr"
	-@erase "$(INTDIR)\Sclipbrd.obj"
	-@erase "$(INTDIR)\Sclipbrd.sbr"
	-@erase "$(INTDIR)\Stat32.pch"
	-@erase "$(INTDIR)\Stat32.res"
	-@erase "$(INTDIR)\Statifce.obj"
	-@erase "$(INTDIR)\Statifce.sbr"
	-@erase "$(INTDIR)\Statistp.obj"
	-@erase "$(INTDIR)\Statistp.sbr"
	-@erase "$(INTDIR)\StatPage.obj"
	-@erase "$(INTDIR)\StatPage.sbr"
	-@erase "$(INTDIR)\Stohwnd.obj"
	-@erase "$(INTDIR)\Stohwnd.sbr"
	-@erase "$(INTDIR)\Strutil.obj"
	-@erase "$(INTDIR)\Strutil.sbr"
	-@erase "$(INTDIR)\Trfkoord.obj"
	-@erase "$(INTDIR)\Trfkoord.sbr"
	-@erase "$(INTDIR)\Trfvect.obj"
	-@erase "$(INTDIR)\Trfvect.sbr"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\geostatd.exp"
	-@erase "$(OUTDIR)\geostatd.ext"
	-@erase "$(OUTDIR)\geostatd.ilk"
	-@erase "$(OUTDIR)\geostatd.lib"
	-@erase "$(OUTDIR)\geostatd.pdb"
	-@erase "$(OUTDIR)\Stat32.bsc"
	-@erase "c:\trias\trias200.deb\geostatd.ext"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(OUTDIR)/STAT32.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__XT" /D "__DEXPROCS" /D "__XTENSNDLL__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D "EBWIN32" /D "QI_EXCEPTION" /Fr /Yu"statistp.hxx" /c
CPP_PROJ=/nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__XT" /D\
 "__DEXPROCS" /D "__XTENSNDLL__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D\
 "EBWIN32" /D "QI_EXCEPTION" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Stat32.pch"\
 /Yu"statistp.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\WinDebug/
CPP_SBRS=.\WinDebug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /i ".." /d "_DEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/Stat32.res" /i ".." /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Stat32.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Classgi.sbr" \
	"$(INTDIR)\Classkey.sbr" \
	"$(INTDIR)\Dbclass.sbr" \
	"$(INTDIR)\Dbinfo.sbr" \
	"$(INTDIR)\Dblnumed.sbr" \
	"$(INTDIR)\Geostat.sbr" \
	"$(INTDIR)\Idkey.sbr" \
	"$(INTDIR)\Objkey.sbr" \
	"$(INTDIR)\Objprop.sbr" \
	"$(INTDIR)\Sclipbrd.sbr" \
	"$(INTDIR)\Statifce.sbr" \
	"$(INTDIR)\Statistp.sbr" \
	"$(INTDIR)\StatPage.sbr" \
	"$(INTDIR)\Stohwnd.sbr" \
	"$(INTDIR)\Strutil.sbr" \
	"$(INTDIR)\Trfkoord.sbr" \
	"$(INTDIR)\Trfvect.sbr"

"$(OUTDIR)\Stat32.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 ixtnsd42.lib cont32d.lib tfrm32d.lib stdcppd.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /stub:"rights.exe" /out:"WinDebug/geostatd.ext" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=ixtnsd42.lib cont32d.lib tfrm32d.lib stdcppd.lib winmm.lib\
 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib\
 shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo\
 /dll /incremental:yes /pdb:"$(OUTDIR)/geostatd.pdb" /debug /machine:I386\
 /def:".\Stat32.def" /stub:"rights.exe" /out:"$(OUTDIR)/geostatd.ext"\
 /implib:"$(OUTDIR)/geostatd.lib" /SUBSYSTEM:windows,4.0 
DEF_FILE= \
	".\Stat32.def"
LINK32_OBJS= \
	"$(INTDIR)\Classgi.obj" \
	"$(INTDIR)\Classkey.obj" \
	"$(INTDIR)\Dbclass.obj" \
	"$(INTDIR)\Dbinfo.obj" \
	"$(INTDIR)\Dblnumed.obj" \
	"$(INTDIR)\Geostat.obj" \
	"$(INTDIR)\Idkey.obj" \
	"$(INTDIR)\Objkey.obj" \
	"$(INTDIR)\Objprop.obj" \
	"$(INTDIR)\Sclipbrd.obj" \
	"$(INTDIR)\Stat32.res" \
	"$(INTDIR)\Statifce.obj" \
	"$(INTDIR)\Statistp.obj" \
	"$(INTDIR)\StatPage.obj" \
	"$(INTDIR)\Stohwnd.obj" \
	"$(INTDIR)\Strutil.obj" \
	"$(INTDIR)\Trfkoord.obj" \
	"$(INTDIR)\Trfvect.obj"

"$(OUTDIR)\geostatd.ext" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying Target to Destination ...
TargetPath=.\WinDebug\geostatd.ext
TargetName=geostatd
InputPath=.\WinDebug\geostatd.ext
SOURCE=$(InputPath)

"c:\trias\trias200.deb\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   copy "$(TargetPath)" c:\trias\trias200.deb

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

# Name "Stat32 - Win32 Release"
# Name "Stat32 - Win32 Debug"

!IF  "$(CFG)" == "Stat32 - Win32 Release"

!ELSEIF  "$(CFG)" == "Stat32 - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Classgi.cxx
DEP_CPP_CLASS=\
	".\CLASSGI.HXX"\
	".\CLASSKEY.HXX"\
	".\Dbinfo.hxx"\
	".\DIRMATH.H"\
	".\GEOSTAT.H"\
	".\GeoStatConfig.h"\
	".\Idkey.hxx"\
	".\OBJKEY.HXX"\
	".\STATISTP.HXX"\
	"C:\Cv32.mvc\Include\gc.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\CTF.H"\
	{$(INCLUDE)}"\CTFM.HXX"\
	{$(INCLUDE)}"\CTFX.HXX"\
	{$(INCLUDE)}"\ctfxmfc.h"\
	{$(INCLUDE)}"\ctfxmfc.nocom.h"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\DBLNUMEX.HXX"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\DLLBINDX.HXX"\
	{$(INCLUDE)}"\EIERUHR.HXX"\
	{$(INCLUDE)}"\ERRCODES.HXX"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\EXCEPTIO.HPP"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\IENUMOBJ.HXX"\
	{$(INCLUDE)}"\IGEOMETR.HXX"\
	{$(INCLUDE)}"\ISTATUS.H"\
	{$(INCLUDE)}"\IXTENSN.HXX"\
	{$(INCLUDE)}"\NUMEDITX.HXX"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OSPACE\COM\ATL.H"\
	{$(INCLUDE)}"\OSPACE\COM\ATLCOMX.H"\
	{$(INCLUDE)}"\ospace\com\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\com\smartif.debug.h"\
	{$(INCLUDE)}"\OSPACE\COM\SMARTIF.H"\
	{$(INCLUDE)}"\ospace\com\smartif.nodebug.h"\
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
	{$(INCLUDE)}"\PROTOS.H"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\RISTYPES.HXX"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\TRIAS01M.HXX"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\XTENSION.H"\
	{$(INCLUDE)}"\XTENSNM.HXX"\
	{$(INCLUDE)}"\XTENSNX.H"\
	{$(INCLUDE)}"\XTENSNXX.H"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\YXVALS.H"\
	

!IF  "$(CFG)" == "Stat32 - Win32 Release"


"$(INTDIR)\Classgi.obj" : $(SOURCE) $(DEP_CPP_CLASS) "$(INTDIR)"\
 "$(INTDIR)\Stat32.pch"


!ELSEIF  "$(CFG)" == "Stat32 - Win32 Debug"


"$(INTDIR)\Classgi.obj" : $(SOURCE) $(DEP_CPP_CLASS) "$(INTDIR)"\
 "$(INTDIR)\Stat32.pch"

"$(INTDIR)\Classgi.sbr" : $(SOURCE) $(DEP_CPP_CLASS) "$(INTDIR)"\
 "$(INTDIR)\Stat32.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Trfvect.cxx
DEP_CPP_TRFVE=\
	".\GEOSTAT.H"\
	".\GeoStatConfig.h"\
	".\STATISTP.HXX"\
	".\TRFVECT.HXX"\
	"C:\Cv32.mvc\Include\gc.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\CTF.H"\
	{$(INCLUDE)}"\CTFM.HXX"\
	{$(INCLUDE)}"\CTFX.HXX"\
	{$(INCLUDE)}"\ctfxmfc.h"\
	{$(INCLUDE)}"\ctfxmfc.nocom.h"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\DBLNUMEX.HXX"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\DLLBINDX.HXX"\
	{$(INCLUDE)}"\EIERUHR.HXX"\
	{$(INCLUDE)}"\ERRCODES.HXX"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\EXCEPTIO.HPP"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\IENUMOBJ.HXX"\
	{$(INCLUDE)}"\ISTATUS.H"\
	{$(INCLUDE)}"\IXTENSN.HXX"\
	{$(INCLUDE)}"\NUMEDITX.HXX"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OSPACE\COM\ATL.H"\
	{$(INCLUDE)}"\OSPACE\COM\ATLCOMX.H"\
	{$(INCLUDE)}"\ospace\com\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\com\smartif.debug.h"\
	{$(INCLUDE)}"\OSPACE\COM\SMARTIF.H"\
	{$(INCLUDE)}"\ospace\com\smartif.nodebug.h"\
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
	{$(INCLUDE)}"\PROTOS.H"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\RISTYPES.HXX"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\TRIAS01M.HXX"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\XTENSION.H"\
	{$(INCLUDE)}"\XTENSNM.HXX"\
	{$(INCLUDE)}"\XTENSNX.H"\
	{$(INCLUDE)}"\XTENSNXX.H"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\YXVALS.H"\
	

!IF  "$(CFG)" == "Stat32 - Win32 Release"


"$(INTDIR)\Trfvect.obj" : $(SOURCE) $(DEP_CPP_TRFVE) "$(INTDIR)"\
 "$(INTDIR)\Stat32.pch"


!ELSEIF  "$(CFG)" == "Stat32 - Win32 Debug"


"$(INTDIR)\Trfvect.obj" : $(SOURCE) $(DEP_CPP_TRFVE) "$(INTDIR)"\
 "$(INTDIR)\Stat32.pch"

"$(INTDIR)\Trfvect.sbr" : $(SOURCE) $(DEP_CPP_TRFVE) "$(INTDIR)"\
 "$(INTDIR)\Stat32.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dbclass.cxx
DEP_CPP_DBCLA=\
	".\CLASSKEY.HXX"\
	".\DBCLASS.HXX"\
	".\Dbinfo.hxx"\
	".\DIRMATH.H"\
	".\GEOSTAT.H"\
	".\GeoStatConfig.h"\
	".\Idkey.hxx"\
	".\OBJKEY.HXX"\
	".\SCLIPBRD.HXX"\
	".\STATISTP.HXX"\
	".\TRFKOORD.HXX"\
	"C:\Cv32.mvc\Include\gc.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\clipbrd.hxx"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\CTF.H"\
	{$(INCLUDE)}"\CTFM.HXX"\
	{$(INCLUDE)}"\CTFX.HXX"\
	{$(INCLUDE)}"\ctfxmfc.h"\
	{$(INCLUDE)}"\ctfxmfc.nocom.h"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\DBLNUMEX.HXX"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\DLLBINDX.HXX"\
	{$(INCLUDE)}"\EIERUHR.HXX"\
	{$(INCLUDE)}"\ERRCODES.HXX"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\EXCEPTIO.HPP"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\IENUMOBJ.HXX"\
	{$(INCLUDE)}"\IGEOMETR.HXX"\
	{$(INCLUDE)}"\ISTATUS.H"\
	{$(INCLUDE)}"\IXTENSN.HXX"\
	{$(INCLUDE)}"\NUMEDITX.HXX"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OSPACE\COM\ATL.H"\
	{$(INCLUDE)}"\OSPACE\COM\ATLCOMX.H"\
	{$(INCLUDE)}"\ospace\com\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\com\smartif.debug.h"\
	{$(INCLUDE)}"\OSPACE\COM\SMARTIF.H"\
	{$(INCLUDE)}"\ospace\com\smartif.nodebug.h"\
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
	{$(INCLUDE)}"\PROTOS.H"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\RISTYPES.HXX"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\TRIAS01M.HXX"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\XTENSION.H"\
	{$(INCLUDE)}"\XTENSNM.HXX"\
	{$(INCLUDE)}"\XTENSNX.H"\
	{$(INCLUDE)}"\XTENSNXX.H"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\YXVALS.H"\
	

!IF  "$(CFG)" == "Stat32 - Win32 Release"


"$(INTDIR)\Dbclass.obj" : $(SOURCE) $(DEP_CPP_DBCLA) "$(INTDIR)"\
 "$(INTDIR)\Stat32.pch"


!ELSEIF  "$(CFG)" == "Stat32 - Win32 Debug"


"$(INTDIR)\Dbclass.obj" : $(SOURCE) $(DEP_CPP_DBCLA) "$(INTDIR)"\
 "$(INTDIR)\Stat32.pch"

"$(INTDIR)\Dbclass.sbr" : $(SOURCE) $(DEP_CPP_DBCLA) "$(INTDIR)"\
 "$(INTDIR)\Stat32.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dbinfo.cxx
DEP_CPP_DBINF=\
	".\CLASSKEY.HXX"\
	".\Dbinfo.hxx"\
	".\DIRMATH.H"\
	".\GEOSTAT.H"\
	".\GeoStatConfig.h"\
	".\Idkey.hxx"\
	".\OBJKEY.HXX"\
	".\SCLIPBRD.HXX"\
	".\STATISTP.HXX"\
	".\TRFKOORD.HXX"\
	"C:\Cv32.mvc\Include\gc.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\clipbrd.hxx"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\CTF.H"\
	{$(INCLUDE)}"\CTFM.HXX"\
	{$(INCLUDE)}"\CTFX.HXX"\
	{$(INCLUDE)}"\ctfxmfc.h"\
	{$(INCLUDE)}"\ctfxmfc.nocom.h"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\DBLNUMEX.HXX"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\DLLBINDX.HXX"\
	{$(INCLUDE)}"\EIERUHR.HXX"\
	{$(INCLUDE)}"\ERRCODES.HXX"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\EXCEPTIO.HPP"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\IENUMOBJ.HXX"\
	{$(INCLUDE)}"\IGEOMETR.HXX"\
	{$(INCLUDE)}"\ISTATUS.H"\
	{$(INCLUDE)}"\IXTENSN.HXX"\
	{$(INCLUDE)}"\NUMEDITX.HXX"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OSPACE\COM\ATL.H"\
	{$(INCLUDE)}"\OSPACE\COM\ATLCOMX.H"\
	{$(INCLUDE)}"\ospace\com\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\com\smartif.debug.h"\
	{$(INCLUDE)}"\OSPACE\COM\SMARTIF.H"\
	{$(INCLUDE)}"\ospace\com\smartif.nodebug.h"\
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
	{$(INCLUDE)}"\PROTOS.H"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\RISTYPES.HXX"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\TRIAS01M.HXX"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\XTENSION.H"\
	{$(INCLUDE)}"\XTENSNM.HXX"\
	{$(INCLUDE)}"\XTENSNX.H"\
	{$(INCLUDE)}"\XTENSNXX.H"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\YXVALS.H"\
	

!IF  "$(CFG)" == "Stat32 - Win32 Release"


"$(INTDIR)\Dbinfo.obj" : $(SOURCE) $(DEP_CPP_DBINF) "$(INTDIR)"\
 "$(INTDIR)\Stat32.pch"


!ELSEIF  "$(CFG)" == "Stat32 - Win32 Debug"


"$(INTDIR)\Dbinfo.obj" : $(SOURCE) $(DEP_CPP_DBINF) "$(INTDIR)"\
 "$(INTDIR)\Stat32.pch"

"$(INTDIR)\Dbinfo.sbr" : $(SOURCE) $(DEP_CPP_DBINF) "$(INTDIR)"\
 "$(INTDIR)\Stat32.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dblnumed.cxx
DEP_CPP_DBLNU=\
	".\DIRMATH.H"\
	".\GEOSTAT.H"\
	".\GeoStatConfig.h"\
	".\STATISTP.HXX"\
	"C:\Cv32.mvc\Include\gc.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\CTF.H"\
	{$(INCLUDE)}"\CTFM.HXX"\
	{$(INCLUDE)}"\CTFX.HXX"\
	{$(INCLUDE)}"\ctfxmfc.h"\
	{$(INCLUDE)}"\ctfxmfc.nocom.h"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\DBLNUMEX.HXX"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\DLLBINDX.HXX"\
	{$(INCLUDE)}"\EIERUHR.HXX"\
	{$(INCLUDE)}"\ERRCODES.HXX"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\EXCEPTIO.HPP"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\IENUMOBJ.HXX"\
	{$(INCLUDE)}"\IGEOMETR.HXX"\
	{$(INCLUDE)}"\ISTATUS.H"\
	{$(INCLUDE)}"\IXTENSN.HXX"\
	{$(INCLUDE)}"\NUMEDITX.HXX"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OSPACE\COM\ATL.H"\
	{$(INCLUDE)}"\OSPACE\COM\ATLCOMX.H"\
	{$(INCLUDE)}"\ospace\com\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\com\smartif.debug.h"\
	{$(INCLUDE)}"\OSPACE\COM\SMARTIF.H"\
	{$(INCLUDE)}"\ospace\com\smartif.nodebug.h"\
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
	{$(INCLUDE)}"\PROTOS.H"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\RISTYPES.HXX"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\TRIAS01M.HXX"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\XTENSION.H"\
	{$(INCLUDE)}"\XTENSNM.HXX"\
	{$(INCLUDE)}"\XTENSNX.H"\
	{$(INCLUDE)}"\XTENSNXX.H"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\YXVALS.H"\
	

!IF  "$(CFG)" == "Stat32 - Win32 Release"


"$(INTDIR)\Dblnumed.obj" : $(SOURCE) $(DEP_CPP_DBLNU) "$(INTDIR)"\
 "$(INTDIR)\Stat32.pch"


!ELSEIF  "$(CFG)" == "Stat32 - Win32 Debug"


"$(INTDIR)\Dblnumed.obj" : $(SOURCE) $(DEP_CPP_DBLNU) "$(INTDIR)"\
 "$(INTDIR)\Stat32.pch"

"$(INTDIR)\Dblnumed.sbr" : $(SOURCE) $(DEP_CPP_DBLNU) "$(INTDIR)"\
 "$(INTDIR)\Stat32.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Geostat.cxx
DEP_CPP_GEOST=\
	".\ABOUT.H"\
	".\ABOUT.HXX"\
	".\CLASSGI.HXX"\
	".\CLASSKEY.HXX"\
	".\DBCLASS.HXX"\
	".\Dbinfo.hxx"\
	".\DIRMATH.H"\
	".\GEOSGUID.H"\
	".\GEOSTAT.H"\
	".\GEOSTAT.HXX"\
	".\GeoStatConfig.h"\
	".\Idkey.hxx"\
	".\OBJKEY.HXX"\
	".\STATISTP.HXX"\
	".\STOHWND.HXX"\
	".\TRFKOORD.HXX"\
	".\TRFVECT.HXX"\
	".\VERSIO16.H"\
	".\VERSIO32.H"\
	".\Version.h"\
	"C:\Cv32.mvc\Include\gc.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\bscrguid.h"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\CTF.H"\
	{$(INCLUDE)}"\CTFM.HXX"\
	{$(INCLUDE)}"\CTFX.HXX"\
	{$(INCLUDE)}"\ctfxmfc.h"\
	{$(INCLUDE)}"\ctfxmfc.nocom.h"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\DBLNUMEX.HXX"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\DLLBINDX.HXX"\
	{$(INCLUDE)}"\eb.h"\
	{$(INCLUDE)}"\eboem.h"\
	{$(INCLUDE)}"\EIERUHR.HXX"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\ERRCODES.HXX"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\EXCEPTIO.HPP"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\IENUMOBJ.HXX"\
	{$(INCLUDE)}"\IGEOMETR.HXX"\
	{$(INCLUDE)}"\ISTATUS.H"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\IXTENSN.HXX"\
	{$(INCLUDE)}"\NUMEDITX.HXX"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OBJGGUID.H"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\OLEGUID.H"\
	{$(INCLUDE)}"\OPERGUID.H"\
	{$(INCLUDE)}"\OSPACE\COM\ATL.H"\
	{$(INCLUDE)}"\OSPACE\COM\ATLCOMX.H"\
	{$(INCLUDE)}"\ospace\com\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\com\smartif.debug.h"\
	{$(INCLUDE)}"\OSPACE\COM\SMARTIF.H"\
	{$(INCLUDE)}"\ospace\com\smartif.nodebug.h"\
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
	{$(INCLUDE)}"\PROTOS.H"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\RISTYPES.HXX"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\statguid.h"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\TRELGUID.H"\
	{$(INCLUDE)}"\TRIAS01M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TRiASHelper_i.c"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\XTENSION.H"\
	{$(INCLUDE)}"\XTENSNM.HXX"\
	{$(INCLUDE)}"\XTENSNX.H"\
	{$(INCLUDE)}"\XTENSNXX.H"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\YXVALS.H"\
	
NODEP_CPP_GEOST=\
	"C:\TRIASDEV.MVC\INCLUDE\dc.h"\
	

!IF  "$(CFG)" == "Stat32 - Win32 Release"


"$(INTDIR)\Geostat.obj" : $(SOURCE) $(DEP_CPP_GEOST) "$(INTDIR)"\
 "$(INTDIR)\Stat32.pch"


!ELSEIF  "$(CFG)" == "Stat32 - Win32 Debug"


"$(INTDIR)\Geostat.obj" : $(SOURCE) $(DEP_CPP_GEOST) "$(INTDIR)"\
 "$(INTDIR)\Stat32.pch"

"$(INTDIR)\Geostat.sbr" : $(SOURCE) $(DEP_CPP_GEOST) "$(INTDIR)"\
 "$(INTDIR)\Stat32.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Idkey.cxx
DEP_CPP_IDKEY=\
	".\DIRMATH.H"\
	".\GEOSTAT.H"\
	".\GeoStatConfig.h"\
	".\Idkey.hxx"\
	".\OBJKEY.HXX"\
	".\STATISTP.HXX"\
	"C:\Cv32.mvc\Include\gc.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\CTF.H"\
	{$(INCLUDE)}"\CTFM.HXX"\
	{$(INCLUDE)}"\CTFX.HXX"\
	{$(INCLUDE)}"\ctfxmfc.h"\
	{$(INCLUDE)}"\ctfxmfc.nocom.h"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\DBLNUMEX.HXX"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\DLLBINDX.HXX"\
	{$(INCLUDE)}"\EIERUHR.HXX"\
	{$(INCLUDE)}"\ERRCODES.HXX"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\EXCEPTIO.HPP"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\IENUMOBJ.HXX"\
	{$(INCLUDE)}"\IGEOMETR.HXX"\
	{$(INCLUDE)}"\ISTATUS.H"\
	{$(INCLUDE)}"\IXTENSN.HXX"\
	{$(INCLUDE)}"\NUMEDITX.HXX"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OSPACE\COM\ATL.H"\
	{$(INCLUDE)}"\OSPACE\COM\ATLCOMX.H"\
	{$(INCLUDE)}"\ospace\com\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\com\smartif.debug.h"\
	{$(INCLUDE)}"\OSPACE\COM\SMARTIF.H"\
	{$(INCLUDE)}"\ospace\com\smartif.nodebug.h"\
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
	{$(INCLUDE)}"\PROTOS.H"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\RISTYPES.HXX"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\TRIAS01M.HXX"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\XTENSION.H"\
	{$(INCLUDE)}"\XTENSNM.HXX"\
	{$(INCLUDE)}"\XTENSNX.H"\
	{$(INCLUDE)}"\XTENSNXX.H"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\YXVALS.H"\
	

!IF  "$(CFG)" == "Stat32 - Win32 Release"


"$(INTDIR)\Idkey.obj" : $(SOURCE) $(DEP_CPP_IDKEY) "$(INTDIR)"\
 "$(INTDIR)\Stat32.pch"


!ELSEIF  "$(CFG)" == "Stat32 - Win32 Debug"


"$(INTDIR)\Idkey.obj" : $(SOURCE) $(DEP_CPP_IDKEY) "$(INTDIR)"\
 "$(INTDIR)\Stat32.pch"

"$(INTDIR)\Idkey.sbr" : $(SOURCE) $(DEP_CPP_IDKEY) "$(INTDIR)"\
 "$(INTDIR)\Stat32.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Objkey.cxx
DEP_CPP_OBJKE=\
	".\DIRMATH.H"\
	".\GEOSTAT.H"\
	".\GeoStatConfig.h"\
	".\OBJKEY.HXX"\
	".\STATISTP.HXX"\
	"C:\Cv32.mvc\Include\gc.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\CTF.H"\
	{$(INCLUDE)}"\CTFM.HXX"\
	{$(INCLUDE)}"\CTFX.HXX"\
	{$(INCLUDE)}"\ctfxmfc.h"\
	{$(INCLUDE)}"\ctfxmfc.nocom.h"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\DBLNUMEX.HXX"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\DLLBINDX.HXX"\
	{$(INCLUDE)}"\EIERUHR.HXX"\
	{$(INCLUDE)}"\ERRCODES.HXX"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\EXCEPTIO.HPP"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\IENUMOBJ.HXX"\
	{$(INCLUDE)}"\IGEOMETR.HXX"\
	{$(INCLUDE)}"\ISTATUS.H"\
	{$(INCLUDE)}"\IXTENSN.HXX"\
	{$(INCLUDE)}"\NUMEDITX.HXX"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OSPACE\COM\ATL.H"\
	{$(INCLUDE)}"\OSPACE\COM\ATLCOMX.H"\
	{$(INCLUDE)}"\ospace\com\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\com\smartif.debug.h"\
	{$(INCLUDE)}"\OSPACE\COM\SMARTIF.H"\
	{$(INCLUDE)}"\ospace\com\smartif.nodebug.h"\
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
	{$(INCLUDE)}"\PROTOS.H"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\RISTYPES.HXX"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\TRIAS01M.HXX"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\XTENSION.H"\
	{$(INCLUDE)}"\XTENSNM.HXX"\
	{$(INCLUDE)}"\XTENSNX.H"\
	{$(INCLUDE)}"\XTENSNXX.H"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\YXVALS.H"\
	

!IF  "$(CFG)" == "Stat32 - Win32 Release"


"$(INTDIR)\Objkey.obj" : $(SOURCE) $(DEP_CPP_OBJKE) "$(INTDIR)"\
 "$(INTDIR)\Stat32.pch"


!ELSEIF  "$(CFG)" == "Stat32 - Win32 Debug"


"$(INTDIR)\Objkey.obj" : $(SOURCE) $(DEP_CPP_OBJKE) "$(INTDIR)"\
 "$(INTDIR)\Stat32.pch"

"$(INTDIR)\Objkey.sbr" : $(SOURCE) $(DEP_CPP_OBJKE) "$(INTDIR)"\
 "$(INTDIR)\Stat32.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Objprop.cxx
DEP_CPP_OBJPR=\
	".\ABOUT.HXX"\
	".\CLASSKEY.HXX"\
	".\Dbinfo.hxx"\
	".\DIRMATH.H"\
	".\GEOSTAT.H"\
	".\GEOSTAT.HXX"\
	".\GeoStatConfig.h"\
	".\Idkey.hxx"\
	".\OBJKEY.HXX"\
	".\STATISTP.HXX"\
	".\STOHWND.HXX"\
	".\TRFKOORD.HXX"\
	".\TRFVECT.HXX"\
	"C:\Cv32.mvc\Include\gc.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\bscrguid.h"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\CTF.H"\
	{$(INCLUDE)}"\CTFM.HXX"\
	{$(INCLUDE)}"\CTFX.HXX"\
	{$(INCLUDE)}"\ctfxmfc.h"\
	{$(INCLUDE)}"\ctfxmfc.nocom.h"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\DBLNUMEX.HXX"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\DLLBINDX.HXX"\
	{$(INCLUDE)}"\eb.h"\
	{$(INCLUDE)}"\eboem.h"\
	{$(INCLUDE)}"\EIERUHR.HXX"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\ERRCODES.HXX"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\EXCEPTIO.HPP"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\IENUMOBJ.HXX"\
	{$(INCLUDE)}"\IGEOMETR.HXX"\
	{$(INCLUDE)}"\ISTATUS.H"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\IXTENSN.HXX"\
	{$(INCLUDE)}"\NUMEDITX.HXX"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OBJGGUID.H"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\OLEGUID.H"\
	{$(INCLUDE)}"\OSPACE\COM\ATL.H"\
	{$(INCLUDE)}"\OSPACE\COM\ATLCOMX.H"\
	{$(INCLUDE)}"\ospace\com\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\com\smartif.debug.h"\
	{$(INCLUDE)}"\OSPACE\COM\SMARTIF.H"\
	{$(INCLUDE)}"\ospace\com\smartif.nodebug.h"\
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
	{$(INCLUDE)}"\PROTOS.H"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\RISTYPES.HXX"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\TRELGUID.H"\
	{$(INCLUDE)}"\TRIAS01M.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\XTENSION.H"\
	{$(INCLUDE)}"\XTENSNM.HXX"\
	{$(INCLUDE)}"\XTENSNX.H"\
	{$(INCLUDE)}"\XTENSNXX.H"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\YXVALS.H"\
	
NODEP_CPP_OBJPR=\
	"C:\TRIASDEV.MVC\INCLUDE\dc.h"\
	

!IF  "$(CFG)" == "Stat32 - Win32 Release"


"$(INTDIR)\Objprop.obj" : $(SOURCE) $(DEP_CPP_OBJPR) "$(INTDIR)"\
 "$(INTDIR)\Stat32.pch"


!ELSEIF  "$(CFG)" == "Stat32 - Win32 Debug"


"$(INTDIR)\Objprop.obj" : $(SOURCE) $(DEP_CPP_OBJPR) "$(INTDIR)"\
 "$(INTDIR)\Stat32.pch"

"$(INTDIR)\Objprop.sbr" : $(SOURCE) $(DEP_CPP_OBJPR) "$(INTDIR)"\
 "$(INTDIR)\Stat32.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Sclipbrd.cxx
DEP_CPP_SCLIP=\
	".\CLASSKEY.HXX"\
	".\DIRMATH.H"\
	".\GEOSTAT.H"\
	".\GeoStatConfig.h"\
	".\Idkey.hxx"\
	".\OBJKEY.HXX"\
	".\SCLIPBRD.HXX"\
	".\STATISTP.HXX"\
	"C:\Cv32.mvc\Include\gc.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\CTF.H"\
	{$(INCLUDE)}"\CTFM.HXX"\
	{$(INCLUDE)}"\CTFX.HXX"\
	{$(INCLUDE)}"\ctfxmfc.h"\
	{$(INCLUDE)}"\ctfxmfc.nocom.h"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\DBLNUMEX.HXX"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\DLLBINDX.HXX"\
	{$(INCLUDE)}"\EIERUHR.HXX"\
	{$(INCLUDE)}"\ERRCODES.HXX"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\EXCEPTIO.HPP"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\IENUMOBJ.HXX"\
	{$(INCLUDE)}"\IGEOMETR.HXX"\
	{$(INCLUDE)}"\ISTATUS.H"\
	{$(INCLUDE)}"\IXTENSN.HXX"\
	{$(INCLUDE)}"\NUMEDITX.HXX"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OSPACE\COM\ATL.H"\
	{$(INCLUDE)}"\OSPACE\COM\ATLCOMX.H"\
	{$(INCLUDE)}"\ospace\com\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\com\smartif.debug.h"\
	{$(INCLUDE)}"\OSPACE\COM\SMARTIF.H"\
	{$(INCLUDE)}"\ospace\com\smartif.nodebug.h"\
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
	{$(INCLUDE)}"\PROTOS.H"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\RISTYPES.HXX"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\TRIAS01M.HXX"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\XTENSION.H"\
	{$(INCLUDE)}"\XTENSNM.HXX"\
	{$(INCLUDE)}"\XTENSNX.H"\
	{$(INCLUDE)}"\XTENSNXX.H"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\YXVALS.H"\
	

!IF  "$(CFG)" == "Stat32 - Win32 Release"


"$(INTDIR)\Sclipbrd.obj" : $(SOURCE) $(DEP_CPP_SCLIP) "$(INTDIR)"\
 "$(INTDIR)\Stat32.pch"


!ELSEIF  "$(CFG)" == "Stat32 - Win32 Debug"


"$(INTDIR)\Sclipbrd.obj" : $(SOURCE) $(DEP_CPP_SCLIP) "$(INTDIR)"\
 "$(INTDIR)\Stat32.pch"

"$(INTDIR)\Sclipbrd.sbr" : $(SOURCE) $(DEP_CPP_SCLIP) "$(INTDIR)"\
 "$(INTDIR)\Stat32.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Statistp.cxx
DEP_CPP_STATI=\
	".\GeoStatConfig.h"\
	".\STATISTP.HXX"\
	"C:\Cv32.mvc\Include\gc.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLIMPL.CPP"\
	{$(INCLUDE)}"\Atlimpl11.h"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\CTF.H"\
	{$(INCLUDE)}"\CTFM.HXX"\
	{$(INCLUDE)}"\CTFX.HXX"\
	{$(INCLUDE)}"\ctfxmfc.h"\
	{$(INCLUDE)}"\ctfxmfc.nocom.h"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\DBLNUMEX.HXX"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\DLLBINDX.HXX"\
	{$(INCLUDE)}"\EIERUHR.HXX"\
	{$(INCLUDE)}"\ERRCODES.HXX"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\EXCEPTIO.HPP"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\IENUMOBJ.HXX"\
	{$(INCLUDE)}"\ISTATUS.H"\
	{$(INCLUDE)}"\IXTENSN.HXX"\
	{$(INCLUDE)}"\NUMEDITX.HXX"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OSPACE\COM\ATL.H"\
	{$(INCLUDE)}"\OSPACE\COM\ATLCOMX.H"\
	{$(INCLUDE)}"\ospace\com\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\com\smartif.debug.h"\
	{$(INCLUDE)}"\OSPACE\COM\SMARTIF.H"\
	{$(INCLUDE)}"\ospace\com\smartif.nodebug.h"\
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
	{$(INCLUDE)}"\PROTOS.H"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\RISTYPES.HXX"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\TRIAS01M.HXX"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\XTENSION.H"\
	{$(INCLUDE)}"\XTENSNM.HXX"\
	{$(INCLUDE)}"\XTENSNX.H"\
	{$(INCLUDE)}"\XTENSNXX.H"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\YXVALS.H"\
	

!IF  "$(CFG)" == "Stat32 - Win32 Release"

# ADD CPP /Yc"statistp.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /Zi /Od /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "STRICT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__XT" /D "__DEXPROCS" /D\
 "__XTENSNDLL__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D "EBWIN32" /D\
 "QI_EXCEPTION" /Fp"$(INTDIR)/Stat32.pch" /Yc"statistp.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\Statistp.obj" : $(SOURCE) $(DEP_CPP_STATI) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Stat32.pch" : $(SOURCE) $(DEP_CPP_STATI) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Stat32 - Win32 Debug"

# ADD CPP /Yc"statistp.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__XT" /D\
 "__DEXPROCS" /D "__XTENSNDLL__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D\
 "EBWIN32" /D "QI_EXCEPTION" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Stat32.pch"\
 /Yc"statistp.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\Statistp.obj" : $(SOURCE) $(DEP_CPP_STATI) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Statistp.sbr" : $(SOURCE) $(DEP_CPP_STATI) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Stat32.pch" : $(SOURCE) $(DEP_CPP_STATI) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Stohwnd.cxx
DEP_CPP_STOHW=\
	".\GEOSTAT.H"\
	".\GeoStatConfig.h"\
	".\STATISTP.HXX"\
	".\STOHWND.HXX"\
	"C:\Cv32.mvc\Include\gc.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\CTF.H"\
	{$(INCLUDE)}"\CTFM.HXX"\
	{$(INCLUDE)}"\CTFX.HXX"\
	{$(INCLUDE)}"\ctfxmfc.h"\
	{$(INCLUDE)}"\ctfxmfc.nocom.h"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\DBLNUMEX.HXX"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\DLLBINDX.HXX"\
	{$(INCLUDE)}"\EIERUHR.HXX"\
	{$(INCLUDE)}"\ERRCODES.HXX"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\EXCEPTIO.HPP"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\IENUMOBJ.HXX"\
	{$(INCLUDE)}"\ISTATUS.H"\
	{$(INCLUDE)}"\IXTENSN.HXX"\
	{$(INCLUDE)}"\NUMEDITX.HXX"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OSPACE\COM\ATL.H"\
	{$(INCLUDE)}"\OSPACE\COM\ATLCOMX.H"\
	{$(INCLUDE)}"\ospace\com\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\com\smartif.debug.h"\
	{$(INCLUDE)}"\OSPACE\COM\SMARTIF.H"\
	{$(INCLUDE)}"\ospace\com\smartif.nodebug.h"\
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
	{$(INCLUDE)}"\PROTOS.H"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\RISTYPES.HXX"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\TRIAS01M.HXX"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\XTENSION.H"\
	{$(INCLUDE)}"\XTENSNM.HXX"\
	{$(INCLUDE)}"\XTENSNX.H"\
	{$(INCLUDE)}"\XTENSNXX.H"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\YXVALS.H"\
	

!IF  "$(CFG)" == "Stat32 - Win32 Release"


"$(INTDIR)\Stohwnd.obj" : $(SOURCE) $(DEP_CPP_STOHW) "$(INTDIR)"\
 "$(INTDIR)\Stat32.pch"


!ELSEIF  "$(CFG)" == "Stat32 - Win32 Debug"


"$(INTDIR)\Stohwnd.obj" : $(SOURCE) $(DEP_CPP_STOHW) "$(INTDIR)"\
 "$(INTDIR)\Stat32.pch"

"$(INTDIR)\Stohwnd.sbr" : $(SOURCE) $(DEP_CPP_STOHW) "$(INTDIR)"\
 "$(INTDIR)\Stat32.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Strutil.cxx
DEP_CPP_STRUT=\
	".\GEOSTAT.H"\
	".\GeoStatConfig.h"\
	".\STATISTP.HXX"\
	"C:\Cv32.mvc\Include\gc.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\CTF.H"\
	{$(INCLUDE)}"\CTFM.HXX"\
	{$(INCLUDE)}"\CTFX.HXX"\
	{$(INCLUDE)}"\ctfxmfc.h"\
	{$(INCLUDE)}"\ctfxmfc.nocom.h"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\DBLNUMEX.HXX"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\DLLBINDX.HXX"\
	{$(INCLUDE)}"\EIERUHR.HXX"\
	{$(INCLUDE)}"\ERRCODES.HXX"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\EXCEPTIO.HPP"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\IENUMOBJ.HXX"\
	{$(INCLUDE)}"\ISTATUS.H"\
	{$(INCLUDE)}"\IXTENSN.HXX"\
	{$(INCLUDE)}"\NUMEDITX.HXX"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OSPACE\COM\ATL.H"\
	{$(INCLUDE)}"\OSPACE\COM\ATLCOMX.H"\
	{$(INCLUDE)}"\ospace\com\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\com\smartif.debug.h"\
	{$(INCLUDE)}"\OSPACE\COM\SMARTIF.H"\
	{$(INCLUDE)}"\ospace\com\smartif.nodebug.h"\
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
	{$(INCLUDE)}"\PROTOS.H"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\RISTYPES.HXX"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\TRIAS01M.HXX"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\XTENSION.H"\
	{$(INCLUDE)}"\XTENSNM.HXX"\
	{$(INCLUDE)}"\XTENSNX.H"\
	{$(INCLUDE)}"\XTENSNXX.H"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\YXVALS.H"\
	

!IF  "$(CFG)" == "Stat32 - Win32 Release"


"$(INTDIR)\Strutil.obj" : $(SOURCE) $(DEP_CPP_STRUT) "$(INTDIR)"\
 "$(INTDIR)\Stat32.pch"


!ELSEIF  "$(CFG)" == "Stat32 - Win32 Debug"


"$(INTDIR)\Strutil.obj" : $(SOURCE) $(DEP_CPP_STRUT) "$(INTDIR)"\
 "$(INTDIR)\Stat32.pch"

"$(INTDIR)\Strutil.sbr" : $(SOURCE) $(DEP_CPP_STRUT) "$(INTDIR)"\
 "$(INTDIR)\Stat32.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Trfkoord.cxx
DEP_CPP_TRFKO=\
	".\GEOSTAT.H"\
	".\GeoStatConfig.h"\
	".\STATISTP.HXX"\
	".\TRFKOORD.HXX"\
	"C:\Cv32.mvc\Include\gc.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\CTF.H"\
	{$(INCLUDE)}"\CTFM.HXX"\
	{$(INCLUDE)}"\CTFX.HXX"\
	{$(INCLUDE)}"\ctfxmfc.h"\
	{$(INCLUDE)}"\ctfxmfc.nocom.h"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\DBLNUMEX.HXX"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\DLLBINDX.HXX"\
	{$(INCLUDE)}"\EIERUHR.HXX"\
	{$(INCLUDE)}"\ERRCODES.HXX"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\EXCEPTIO.HPP"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\IENUMOBJ.HXX"\
	{$(INCLUDE)}"\ISTATUS.H"\
	{$(INCLUDE)}"\IXTENSN.HXX"\
	{$(INCLUDE)}"\NUMEDITX.HXX"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OSPACE\COM\ATL.H"\
	{$(INCLUDE)}"\OSPACE\COM\ATLCOMX.H"\
	{$(INCLUDE)}"\ospace\com\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\com\smartif.debug.h"\
	{$(INCLUDE)}"\OSPACE\COM\SMARTIF.H"\
	{$(INCLUDE)}"\ospace\com\smartif.nodebug.h"\
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
	{$(INCLUDE)}"\PROTOS.H"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\RISTYPES.HXX"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\TRIAS01M.HXX"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\XTENSION.H"\
	{$(INCLUDE)}"\XTENSNM.HXX"\
	{$(INCLUDE)}"\XTENSNX.H"\
	{$(INCLUDE)}"\XTENSNXX.H"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\YXVALS.H"\
	

!IF  "$(CFG)" == "Stat32 - Win32 Release"


"$(INTDIR)\Trfkoord.obj" : $(SOURCE) $(DEP_CPP_TRFKO) "$(INTDIR)"\
 "$(INTDIR)\Stat32.pch"


!ELSEIF  "$(CFG)" == "Stat32 - Win32 Debug"


"$(INTDIR)\Trfkoord.obj" : $(SOURCE) $(DEP_CPP_TRFKO) "$(INTDIR)"\
 "$(INTDIR)\Stat32.pch"

"$(INTDIR)\Trfkoord.sbr" : $(SOURCE) $(DEP_CPP_TRFKO) "$(INTDIR)"\
 "$(INTDIR)\Stat32.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Classkey.cxx
DEP_CPP_CLASSK=\
	".\CLASSKEY.HXX"\
	".\DIRMATH.H"\
	".\GEOSTAT.H"\
	".\GeoStatConfig.h"\
	".\OBJKEY.HXX"\
	".\STATISTP.HXX"\
	"C:\Cv32.mvc\Include\gc.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\CTF.H"\
	{$(INCLUDE)}"\CTFM.HXX"\
	{$(INCLUDE)}"\CTFX.HXX"\
	{$(INCLUDE)}"\ctfxmfc.h"\
	{$(INCLUDE)}"\ctfxmfc.nocom.h"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\DBLNUMEX.HXX"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\DLLBINDX.HXX"\
	{$(INCLUDE)}"\EIERUHR.HXX"\
	{$(INCLUDE)}"\ERRCODES.HXX"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\EXCEPTIO.HPP"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\IENUMOBJ.HXX"\
	{$(INCLUDE)}"\IGEOMETR.HXX"\
	{$(INCLUDE)}"\ISTATUS.H"\
	{$(INCLUDE)}"\IXTENSN.HXX"\
	{$(INCLUDE)}"\NUMEDITX.HXX"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OSPACE\COM\ATL.H"\
	{$(INCLUDE)}"\OSPACE\COM\ATLCOMX.H"\
	{$(INCLUDE)}"\ospace\com\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\com\smartif.debug.h"\
	{$(INCLUDE)}"\OSPACE\COM\SMARTIF.H"\
	{$(INCLUDE)}"\ospace\com\smartif.nodebug.h"\
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
	{$(INCLUDE)}"\PROTOS.H"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\RISTYPES.HXX"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\TRIAS01M.HXX"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\XTENSION.H"\
	{$(INCLUDE)}"\XTENSNM.HXX"\
	{$(INCLUDE)}"\XTENSNX.H"\
	{$(INCLUDE)}"\XTENSNXX.H"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\YXVALS.H"\
	

!IF  "$(CFG)" == "Stat32 - Win32 Release"


"$(INTDIR)\Classkey.obj" : $(SOURCE) $(DEP_CPP_CLASSK) "$(INTDIR)"\
 "$(INTDIR)\Stat32.pch"


!ELSEIF  "$(CFG)" == "Stat32 - Win32 Debug"


"$(INTDIR)\Classkey.obj" : $(SOURCE) $(DEP_CPP_CLASSK) "$(INTDIR)"\
 "$(INTDIR)\Stat32.pch"

"$(INTDIR)\Classkey.sbr" : $(SOURCE) $(DEP_CPP_CLASSK) "$(INTDIR)"\
 "$(INTDIR)\Stat32.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StatPage.cpp
DEP_CPP_STATP=\
	".\GEOSGUID.H"\
	".\GeoStatConfig.h"\
	".\GEOSTATR.H"\
	".\STATISTP.HXX"\
	".\STATPAGE.H"\
	"C:\Cv32.mvc\Include\gc.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\CTF.H"\
	{$(INCLUDE)}"\CTFM.HXX"\
	{$(INCLUDE)}"\CTFX.HXX"\
	{$(INCLUDE)}"\ctfxmfc.h"\
	{$(INCLUDE)}"\ctfxmfc.nocom.h"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\DBLNUMEX.HXX"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\DLLBINDX.HXX"\
	{$(INCLUDE)}"\EIERUHR.HXX"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\ERRCODES.HXX"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\EXCEPTIO.HPP"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\IENUMOBJ.HXX"\
	{$(INCLUDE)}"\ISTATUS.H"\
	{$(INCLUDE)}"\IXTENSN.HXX"\
	{$(INCLUDE)}"\IXTNEXT.HXX"\
	{$(INCLUDE)}"\NUMEDITX.HXX"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OSPACE\COM\ATL.H"\
	{$(INCLUDE)}"\OSPACE\COM\ATLCOMX.H"\
	{$(INCLUDE)}"\ospace\com\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\com\smartif.debug.h"\
	{$(INCLUDE)}"\OSPACE\COM\SMARTIF.H"\
	{$(INCLUDE)}"\ospace\com\smartif.nodebug.h"\
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
	{$(INCLUDE)}"\PROTOS.H"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\RISTYPES.HXX"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\TRIAS01M.HXX"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\XTENSION.H"\
	{$(INCLUDE)}"\XTENSNM.HXX"\
	{$(INCLUDE)}"\XTENSNX.H"\
	{$(INCLUDE)}"\XTENSNXX.H"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\YXVALS.H"\
	

!IF  "$(CFG)" == "Stat32 - Win32 Release"


"$(INTDIR)\StatPage.obj" : $(SOURCE) $(DEP_CPP_STATP) "$(INTDIR)"\
 "$(INTDIR)\Stat32.pch"


!ELSEIF  "$(CFG)" == "Stat32 - Win32 Debug"


"$(INTDIR)\StatPage.obj" : $(SOURCE) $(DEP_CPP_STATP) "$(INTDIR)"\
 "$(INTDIR)\Stat32.pch"

"$(INTDIR)\StatPage.sbr" : $(SOURCE) $(DEP_CPP_STATP) "$(INTDIR)"\
 "$(INTDIR)\Stat32.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Stat32.def

!IF  "$(CFG)" == "Stat32 - Win32 Release"

# PROP Exclude_From_Build 0

!ELSEIF  "$(CFG)" == "Stat32 - Win32 Debug"

# PROP Exclude_From_Build 0

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Stat32.rc
DEP_RSC_STAT3=\
	".\ABOUT.H"\
	".\About.src"\
	".\GEOSTAT.H"\
	".\Lupe.ico"\
	".\macro\Topolog.ebc"\
	".\Res\StatistikPageExt.rgs"\
	".\Stat32.rcv"\
	{$(INCLUDE)}"\Resstrg.h"\
	

"$(INTDIR)\Stat32.res" : $(SOURCE) $(DEP_RSC_STAT3) "$(INTDIR)"\
 ".\macro\Topolog.ebc"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Res\StatistikPageExt.rgs

!IF  "$(CFG)" == "Stat32 - Win32 Release"

!ELSEIF  "$(CFG)" == "Stat32 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Statifce.cxx
DEP_CPP_STATIF=\
	".\ABOUT.H"\
	".\ABOUT.HXX"\
	".\CLASSGI.HXX"\
	".\CLASSKEY.HXX"\
	".\DBCLASS.HXX"\
	".\Dbinfo.hxx"\
	".\DIRMATH.H"\
	".\GEOSTAT.H"\
	".\GEOSTAT.HXX"\
	".\GeoStatConfig.h"\
	".\Idkey.hxx"\
	".\OBJKEY.HXX"\
	".\STATISTP.HXX"\
	".\STOHWND.HXX"\
	".\TRFKOORD.HXX"\
	".\TRFVECT.HXX"\
	".\VERSIO16.H"\
	".\VERSIO32.H"\
	".\Version.h"\
	"C:\Cv32.mvc\Include\gc.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\bscrguid.h"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\containr.hxx"\
	{$(INCLUDE)}"\CTF.H"\
	{$(INCLUDE)}"\CTFM.HXX"\
	{$(INCLUDE)}"\CTFX.HXX"\
	{$(INCLUDE)}"\ctfxmfc.h"\
	{$(INCLUDE)}"\ctfxmfc.nocom.h"\
	{$(INCLUDE)}"\ctrlines.hxx"\
	{$(INCLUDE)}"\ctrtypes.hxx"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\DBLNUMEX.HXX"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\DLLBINDX.HXX"\
	{$(INCLUDE)}"\eb.h"\
	{$(INCLUDE)}"\eboem.h"\
	{$(INCLUDE)}"\EIERUHR.HXX"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\ERRCODES.HXX"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\EXCEPTIO.HPP"\
	{$(INCLUDE)}"\freestor.hxx"\
	{$(INCLUDE)}"\gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\IENUMOBJ.HXX"\
	{$(INCLUDE)}"\IGEOMETR.HXX"\
	{$(INCLUDE)}"\ISTATUS.H"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\iunredo.hxx"\
	{$(INCLUDE)}"\IXTENSN.HXX"\
	{$(INCLUDE)}"\NUMEDITX.HXX"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\OLEGUID.H"\
	{$(INCLUDE)}"\OPERGUID.H"\
	{$(INCLUDE)}"\OSPACE\COM\ATL.H"\
	{$(INCLUDE)}"\OSPACE\COM\ATLCOMX.H"\
	{$(INCLUDE)}"\ospace\com\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\com\smartif.debug.h"\
	{$(INCLUDE)}"\OSPACE\COM\SMARTIF.H"\
	{$(INCLUDE)}"\ospace\com\smartif.nodebug.h"\
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
	{$(INCLUDE)}"\PROTOS.H"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\RISTYPES.HXX"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\syncthrd.hxx"\
	{$(INCLUDE)}"\sys\types.h"\
	{$(INCLUDE)}"\tassert.hxx"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\TRELGUID.H"\
	{$(INCLUDE)}"\TRIAS01M.HXX"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\Triastlb_i.c"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\UNDOGUID.H"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\XTENSION.H"\
	{$(INCLUDE)}"\XTENSNM.HXX"\
	{$(INCLUDE)}"\XTENSNX.H"\
	{$(INCLUDE)}"\XTENSNXX.H"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\YXVALS.H"\
	
NODEP_CPP_STATIF=\
	"C:\TRIASDEV.MVC\INCLUDE\dc.h"\
	

!IF  "$(CFG)" == "Stat32 - Win32 Release"


"$(INTDIR)\Statifce.obj" : $(SOURCE) $(DEP_CPP_STATIF) "$(INTDIR)"\
 "$(INTDIR)\Stat32.pch"


!ELSEIF  "$(CFG)" == "Stat32 - Win32 Debug"


"$(INTDIR)\Statifce.obj" : $(SOURCE) $(DEP_CPP_STATIF) "$(INTDIR)"\
 "$(INTDIR)\Stat32.pch"

"$(INTDIR)\Statifce.sbr" : $(SOURCE) $(DEP_CPP_STATIF) "$(INTDIR)"\
 "$(INTDIR)\Stat32.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Macro\Topolog.ebs

!IF  "$(CFG)" == "Stat32 - Win32 Release"

# Begin Custom Build
InputPath=.\Macro\Topolog.ebs
InputName=Topolog

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   bsl -c -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ELSEIF  "$(CFG)" == "Stat32 - Win32 Debug"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
