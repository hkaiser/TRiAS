# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=Tproj32 - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Tproj32 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Tproj32 - Win32 Release" && "$(CFG)" !=\
 "Tproj32 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Tproj32.mak" CFG="Tproj32 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Tproj32 - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Tproj32 - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "Tproj32 - Win32 Debug"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "Tproj32 - Win32 Release"

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
TargetName=Tproject
# End Custom Macros

ALL : "$(OUTDIR)\Tproject.ext"\
 "..\..\..\..\programme\trias200\trias\Tproject.ext"

CLEAN : 
	-@erase "$(INTDIR)\MENUKEY.OBJ"
	-@erase "$(INTDIR)\PROJPROF.OBJ"
	-@erase "$(INTDIR)\TEPRODEF.OBJ"
	-@erase "$(INTDIR)\TPMCODE.OBJ"
	-@erase "$(INTDIR)\Tpmember.obj"
	-@erase "$(INTDIR)\Tproj32.pch"
	-@erase "$(INTDIR)\TPROJ32.res"
	-@erase "$(INTDIR)\TPROJECT.OBJ"
	-@erase "$(INTDIR)\TPROJP.OBJ"
	-@erase "$(INTDIR)\TXTEDIT.OBJ"
	-@erase "$(OUTDIR)\Tproject.exp"
	-@erase "$(OUTDIR)\Tproject.ext"
	-@erase "$(OUTDIR)\Tproject.lib"
	-@erase "..\..\..\..\programme\trias200\trias\Tproject.ext"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__XT" /D "__DEXPROCS" /D "__XTENSDLL__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /Yu"tprojp.hxx" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "STRICT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__XT" /D "__DEXPROCS" /D\
 "__XTENSDLL__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT"\
 /Fp"$(INTDIR)/Tproj32.pch" /Yu"tprojp.hxx" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\WinRel/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /i ".." /d "NDEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/TPROJ32.res" /i ".." /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# SUBTRACT BSC32 /nologo
BSC32_FLAGS=/o"$(OUTDIR)/Tproj32.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ixtnsr40.lib cont32r.lib tfrmwork.lib stdcppr.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386 /out:"WinRel/Tproject.ext"
LINK32_FLAGS=ixtnsr40.lib cont32r.lib tfrmwork.lib stdcppr.lib winmm.lib\
 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib\
 shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo\
 /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)/Tproject.pdb"\
 /machine:I386 /def:".\TPROJ32.DEF" /out:"$(OUTDIR)/Tproject.ext"\
 /implib:"$(OUTDIR)/Tproject.lib" 
DEF_FILE= \
	".\TPROJ32.DEF"
LINK32_OBJS= \
	"$(INTDIR)\MENUKEY.OBJ" \
	"$(INTDIR)\PROJPROF.OBJ" \
	"$(INTDIR)\TEPRODEF.OBJ" \
	"$(INTDIR)\TPMCODE.OBJ" \
	"$(INTDIR)\Tpmember.obj" \
	"$(INTDIR)\TPROJ32.res" \
	"$(INTDIR)\TPROJECT.OBJ" \
	"$(INTDIR)\TPROJP.OBJ" \
	"$(INTDIR)\TXTEDIT.OBJ"

"$(OUTDIR)\Tproject.ext" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying Target to Destination ...
TargetPath=.\WinRel\Tproject.ext
TargetName=Tproject
InputPath=.\WinRel\Tproject.ext
SOURCE=$(InputPath)

"e:\programme\trias200\trias\$(TargetName).ext" : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
   copy "$(TargetPath)" e:\programme\trias200\trias

# End Custom Build

!ELSEIF  "$(CFG)" == "Tproj32 - Win32 Debug"

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
TargetName=Tprojecd
# End Custom Macros

ALL : "$(OUTDIR)\Tprojecd.ext" "$(OUTDIR)\Tproj32.bsc"\
 "..\..\..\..\trias\trias200\Tprojecd.ext"

CLEAN : 
	-@erase "$(INTDIR)\MENUKEY.OBJ"
	-@erase "$(INTDIR)\MENUKEY.SBR"
	-@erase "$(INTDIR)\PROJPROF.OBJ"
	-@erase "$(INTDIR)\PROJPROF.SBR"
	-@erase "$(INTDIR)\TEPRODEF.OBJ"
	-@erase "$(INTDIR)\TEPRODEF.SBR"
	-@erase "$(INTDIR)\TPMCODE.OBJ"
	-@erase "$(INTDIR)\TPMCODE.SBR"
	-@erase "$(INTDIR)\Tpmember.obj"
	-@erase "$(INTDIR)\Tpmember.sbr"
	-@erase "$(INTDIR)\Tproj32.pch"
	-@erase "$(INTDIR)\TPROJ32.res"
	-@erase "$(INTDIR)\TPROJECT.OBJ"
	-@erase "$(INTDIR)\TPROJECT.SBR"
	-@erase "$(INTDIR)\TPROJP.OBJ"
	-@erase "$(INTDIR)\TPROJP.SBR"
	-@erase "$(INTDIR)\TXTEDIT.OBJ"
	-@erase "$(INTDIR)\TXTEDIT.SBR"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\Tproj32.bsc"
	-@erase "$(OUTDIR)\Tprojecd.exp"
	-@erase "$(OUTDIR)\Tprojecd.ext"
	-@erase "$(OUTDIR)\Tprojecd.ilk"
	-@erase "$(OUTDIR)\Tprojecd.lib"
	-@erase "$(OUTDIR)\Tprojecd.pdb"
	-@erase "..\..\..\..\trias\trias200\Tprojecd.ext"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "STRICT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__XT" /D "__DEXPROCS" /D "__XTENSNDLL__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /FR /Yu"tprojp.hxx" /c
CPP_PROJ=/nologo /MDd /W3 /WX /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "STRICT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__XT" /D\
 "__DEXPROCS" /D "__XTENSNDLL__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT"\
 /FR"$(INTDIR)/" /Fp"$(INTDIR)/Tproj32.pch" /Yu"tprojp.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\WinDebug/
CPP_SBRS=.\WinDebug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /i ".." /d "_DEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/TPROJ32.res" /i ".." /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Tproj32.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\MENUKEY.SBR" \
	"$(INTDIR)\PROJPROF.SBR" \
	"$(INTDIR)\TEPRODEF.SBR" \
	"$(INTDIR)\TPMCODE.SBR" \
	"$(INTDIR)\Tpmember.sbr" \
	"$(INTDIR)\TPROJECT.SBR" \
	"$(INTDIR)\TPROJP.SBR" \
	"$(INTDIR)\TXTEDIT.SBR"

"$(OUTDIR)\Tproj32.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 ixtnsd42.lib cont32d.lib tfrm32d.lib stdcppd.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"WinDebug/Tprojecd.ext"
LINK32_FLAGS=ixtnsd42.lib cont32d.lib tfrm32d.lib stdcppd.lib winmm.lib\
 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib\
 shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo\
 /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)/Tprojecd.pdb" /debug\
 /machine:I386 /def:".\TPROJ32.DEF" /out:"$(OUTDIR)/Tprojecd.ext"\
 /implib:"$(OUTDIR)/Tprojecd.lib" 
DEF_FILE= \
	".\TPROJ32.DEF"
LINK32_OBJS= \
	"$(INTDIR)\MENUKEY.OBJ" \
	"$(INTDIR)\PROJPROF.OBJ" \
	"$(INTDIR)\TEPRODEF.OBJ" \
	"$(INTDIR)\TPMCODE.OBJ" \
	"$(INTDIR)\Tpmember.obj" \
	"$(INTDIR)\TPROJ32.res" \
	"$(INTDIR)\TPROJECT.OBJ" \
	"$(INTDIR)\TPROJP.OBJ" \
	"$(INTDIR)\TXTEDIT.OBJ"

"$(OUTDIR)\Tprojecd.ext" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying Target to Destination ...
TargetPath=.\WinDebug\Tprojecd.ext
TargetName=Tprojecd
InputPath=.\WinDebug\Tprojecd.ext
SOURCE=$(InputPath)

"e:\trias\trias200\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   copy "$(TargetPath)" e:\trias\trias200

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

# Name "Tproj32 - Win32 Release"
# Name "Tproj32 - Win32 Debug"

!IF  "$(CFG)" == "Tproj32 - Win32 Release"

!ELSEIF  "$(CFG)" == "Tproj32 - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\TPROJECT\TPROJP.CXX

!IF  "$(CFG)" == "Tproj32 - Win32 Release"

DEP_CPP_TPROJ=\
	"..\..\..\..\Cv32.mvc\Include\Gc.h"\
	"..\..\..\..\msdev\atl11\include\atlbase.h"\
	"..\..\..\..\msdev\atl11\include\atlcom.h"\
	"..\..\..\..\msdev\atl11\include\atlcomx.h"\
	"..\..\..\..\msdev\atl11\include\atlutil.h"\
	".\..\TPROJP.HXX"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTFX.HXX"\
	{$(INCLUDE)}"\ctfxmfc.h"\
	{$(INCLUDE)}"\ctfxmfc.nocom.h"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
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
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
# ADD CPP /Yc"tprojp.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "STRICT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__XT" /D "__DEXPROCS" /D\
 "__XTENSDLL__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT"\
 /Fp"$(INTDIR)/Tproj32.pch" /Yc"tprojp.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\TPROJP.OBJ" : $(SOURCE) $(DEP_CPP_TPROJ) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Tproj32.pch" : $(SOURCE) $(DEP_CPP_TPROJ) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tproj32 - Win32 Debug"

DEP_CPP_TPROJ=\
	"..\..\..\..\Cv32.mvc\Include\Gc.h"\
	"..\..\..\..\msdev\atl11\include\atlbase.h"\
	"..\..\..\..\msdev\atl11\include\atlcom.h"\
	"..\..\..\..\msdev\atl11\include\atlcomx.h"\
	"..\..\..\..\msdev\atl11\include\atlutil.h"\
	".\..\TPROJP.HXX"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTFX.HXX"\
	{$(INCLUDE)}"\ctfxmfc.h"\
	{$(INCLUDE)}"\ctfxmfc.nocom.h"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
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
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
# ADD CPP /WX /Yc"tprojp.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "STRICT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__XT" /D\
 "__DEXPROCS" /D "__XTENSNDLL__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT"\
 /FR"$(INTDIR)/" /Fp"$(INTDIR)/Tproj32.pch" /Yc"tprojp.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\TPROJP.OBJ" : $(SOURCE) $(DEP_CPP_TPROJ) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\TPROJP.SBR" : $(SOURCE) $(DEP_CPP_TPROJ) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Tproj32.pch" : $(SOURCE) $(DEP_CPP_TPROJ) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\TPROJECT\TPMCODE.CXX

!IF  "$(CFG)" == "Tproj32 - Win32 Release"

DEP_CPP_TPMCO=\
	"..\..\..\..\Cv32.mvc\Include\Gc.h"\
	"..\..\..\..\msdev\atl11\include\atlbase.h"\
	"..\..\..\..\msdev\atl11\include\atlcom.h"\
	"..\..\..\..\msdev\atl11\include\atlcomx.h"\
	"..\..\..\..\msdev\atl11\include\atlutil.h"\
	"..\tproject.h"\
	".\..\DEFPROJ.H"\
	".\..\TPMCODE.HXX"\
	".\..\TPROJP.HXX"\
	".\..\TXTEDIT.HXX"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTFX.HXX"\
	{$(INCLUDE)}"\ctfxmfc.h"\
	{$(INCLUDE)}"\ctfxmfc.nocom.h"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
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
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	

"$(INTDIR)\TPMCODE.OBJ" : $(SOURCE) $(DEP_CPP_TPMCO) "$(INTDIR)"\
 "$(INTDIR)\Tproj32.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "STRICT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__XT" /D "__DEXPROCS" /D\
 "__XTENSDLL__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT"\
 /Fp"$(INTDIR)/Tproj32.pch" /Yu"tprojp.hxx" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Tproj32 - Win32 Debug"

DEP_CPP_TPMCO=\
	"..\..\..\..\Cv32.mvc\Include\Gc.h"\
	"..\..\..\..\msdev\atl11\include\atlbase.h"\
	"..\..\..\..\msdev\atl11\include\atlcom.h"\
	"..\..\..\..\msdev\atl11\include\atlcomx.h"\
	"..\..\..\..\msdev\atl11\include\atlutil.h"\
	"..\tproject.h"\
	".\..\DEFPROJ.H"\
	".\..\TPMCODE.HXX"\
	".\..\TPROJP.HXX"\
	".\..\TXTEDIT.HXX"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTFX.HXX"\
	{$(INCLUDE)}"\ctfxmfc.h"\
	{$(INCLUDE)}"\ctfxmfc.nocom.h"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
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
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
# ADD CPP /Yu"tprojp.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "STRICT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__XT" /D\
 "__DEXPROCS" /D "__XTENSNDLL__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT"\
 /FR"$(INTDIR)/" /Fp"$(INTDIR)/Tproj32.pch" /Yu"tprojp.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\TPMCODE.OBJ" : $(SOURCE) $(DEP_CPP_TPMCO) "$(INTDIR)"\
 "$(INTDIR)\Tproj32.pch"
   $(BuildCmds)

"$(INTDIR)\TPMCODE.SBR" : $(SOURCE) $(DEP_CPP_TPMCO) "$(INTDIR)"\
 "$(INTDIR)\Tproj32.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\TPROJECT\PROJPROF.CXX

!IF  "$(CFG)" == "Tproj32 - Win32 Release"

DEP_CPP_PROJP=\
	"..\..\..\..\Cv32.mvc\Include\Gc.h"\
	"..\..\..\..\msdev\atl11\include\atlbase.h"\
	"..\..\..\..\msdev\atl11\include\atlcom.h"\
	"..\..\..\..\msdev\atl11\include\atlcomx.h"\
	"..\..\..\..\msdev\atl11\include\atlutil.h"\
	"..\tproject.h"\
	".\..\about.h"\
	".\..\DEFPROJ.H"\
	".\..\MENUKEY.HXX"\
	".\..\PROJPROF.HXX"\
	".\..\TEPRODEF.HXX"\
	".\..\TPROJP.HXX"\
	".\..\TXTEDIT.HXX"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTFX.HXX"\
	{$(INCLUDE)}"\ctfxmfc.h"\
	{$(INCLUDE)}"\ctfxmfc.nocom.h"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
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
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
# ADD CPP /Yu

"$(INTDIR)\PROJPROF.OBJ" : $(SOURCE) $(DEP_CPP_PROJP) "$(INTDIR)"\
 "$(INTDIR)\Tproj32.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "STRICT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__XT" /D "__DEXPROCS" /D\
 "__XTENSDLL__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT"\
 /Fp"$(INTDIR)/Tproj32.pch" /Yu"tprojp.hxx" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Tproj32 - Win32 Debug"

DEP_CPP_PROJP=\
	"..\..\..\..\Cv32.mvc\Include\Gc.h"\
	"..\..\..\..\msdev\atl11\include\atlbase.h"\
	"..\..\..\..\msdev\atl11\include\atlcom.h"\
	"..\..\..\..\msdev\atl11\include\atlcomx.h"\
	"..\..\..\..\msdev\atl11\include\atlutil.h"\
	"..\tproject.h"\
	".\..\about.h"\
	".\..\DEFPROJ.H"\
	".\..\MENUKEY.HXX"\
	".\..\PROJPROF.HXX"\
	".\..\TEPRODEF.HXX"\
	".\..\TPROJP.HXX"\
	".\..\TXTEDIT.HXX"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTFX.HXX"\
	{$(INCLUDE)}"\ctfxmfc.h"\
	{$(INCLUDE)}"\ctfxmfc.nocom.h"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
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
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
# ADD CPP /Yu"tprojp.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "STRICT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__XT" /D\
 "__DEXPROCS" /D "__XTENSNDLL__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT"\
 /FR"$(INTDIR)/" /Fp"$(INTDIR)/Tproj32.pch" /Yu"tprojp.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\PROJPROF.OBJ" : $(SOURCE) $(DEP_CPP_PROJP) "$(INTDIR)"\
 "$(INTDIR)\Tproj32.pch"
   $(BuildCmds)

"$(INTDIR)\PROJPROF.SBR" : $(SOURCE) $(DEP_CPP_PROJP) "$(INTDIR)"\
 "$(INTDIR)\Tproj32.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\TPROJECT\TPROJECT.CXX

!IF  "$(CFG)" == "Tproj32 - Win32 Release"

DEP_CPP_TPROJE=\
	"..\..\..\..\Cv32.mvc\Include\Gc.h"\
	"..\..\..\..\msdev\atl11\include\atlbase.h"\
	"..\..\..\..\msdev\atl11\include\atlcom.h"\
	"..\..\..\..\msdev\atl11\include\atlcomx.h"\
	"..\..\..\..\msdev\atl11\include\atlutil.h"\
	"..\tproject.h"\
	".\..\about.h"\
	".\..\ABOUT.HXX"\
	".\..\DEFPROJ.H"\
	".\..\MENUKEY.HXX"\
	".\..\PROJPROF.HXX"\
	".\..\TEPRODEF.HXX"\
	".\..\TPMCODE.HXX"\
	".\..\TPRJGUID.H"\
	".\..\TPROJECT.HXX"\
	".\..\TPROJP.HXX"\
	".\..\TXTEDIT.HXX"\
	".\..\VERSIO16.H"\
	".\..\VERSION.H"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTFX.HXX"\
	{$(INCLUDE)}"\ctfxmfc.h"\
	{$(INCLUDE)}"\ctfxmfc.nocom.h"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
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
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	

"$(INTDIR)\TPROJECT.OBJ" : $(SOURCE) $(DEP_CPP_TPROJE) "$(INTDIR)"\
 "$(INTDIR)\Tproj32.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "STRICT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__XT" /D "__DEXPROCS" /D\
 "__XTENSDLL__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT"\
 /Fp"$(INTDIR)/Tproj32.pch" /Yu"tprojp.hxx" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Tproj32 - Win32 Debug"

DEP_CPP_TPROJE=\
	"..\..\..\..\Cv32.mvc\Include\Gc.h"\
	"..\..\..\..\msdev\atl11\include\atlbase.h"\
	"..\..\..\..\msdev\atl11\include\atlcom.h"\
	"..\..\..\..\msdev\atl11\include\atlcomx.h"\
	"..\..\..\..\msdev\atl11\include\atlutil.h"\
	"..\tproject.h"\
	".\..\about.h"\
	".\..\ABOUT.HXX"\
	".\..\DEFPROJ.H"\
	".\..\MENUKEY.HXX"\
	".\..\PROJPROF.HXX"\
	".\..\TEPRODEF.HXX"\
	".\..\TPMCODE.HXX"\
	".\..\TPRJGUID.H"\
	".\..\TPROJECT.HXX"\
	".\..\TPROJP.HXX"\
	".\..\TXTEDIT.HXX"\
	".\..\VERSIO16.H"\
	".\..\VERSION.H"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTFX.HXX"\
	{$(INCLUDE)}"\ctfxmfc.h"\
	{$(INCLUDE)}"\ctfxmfc.nocom.h"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
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
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
# ADD CPP /Yu"tprojp.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "STRICT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__XT" /D\
 "__DEXPROCS" /D "__XTENSNDLL__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT"\
 /FR"$(INTDIR)/" /Fp"$(INTDIR)/Tproj32.pch" /Yu"tprojp.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\TPROJECT.OBJ" : $(SOURCE) $(DEP_CPP_TPROJE) "$(INTDIR)"\
 "$(INTDIR)\Tproj32.pch"
   $(BuildCmds)

"$(INTDIR)\TPROJECT.SBR" : $(SOURCE) $(DEP_CPP_TPROJE) "$(INTDIR)"\
 "$(INTDIR)\Tproj32.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\TPROJECT\TEPRODEF.CXX
DEP_CPP_TEPRO=\
	"..\..\..\..\Cv32.mvc\Include\Gc.h"\
	"..\..\..\..\msdev\atl11\include\atlbase.h"\
	"..\..\..\..\msdev\atl11\include\atlcom.h"\
	"..\..\..\..\msdev\atl11\include\atlcomx.h"\
	"..\..\..\..\msdev\atl11\include\atlutil.h"\
	"..\tproject.h"\
	".\..\DEFPROJ.H"\
	".\..\MENUKEY.HXX"\
	".\..\TEPRODEF.HXX"\
	".\..\TPROJP.HXX"\
	".\..\TXTEDIT.HXX"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTFX.HXX"\
	{$(INCLUDE)}"\ctfxmfc.h"\
	{$(INCLUDE)}"\ctfxmfc.nocom.h"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
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
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	

!IF  "$(CFG)" == "Tproj32 - Win32 Release"


"$(INTDIR)\TEPRODEF.OBJ" : $(SOURCE) $(DEP_CPP_TEPRO) "$(INTDIR)"\
 "$(INTDIR)\Tproj32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Tproj32 - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\TEPRODEF.OBJ" : $(SOURCE) $(DEP_CPP_TEPRO) "$(INTDIR)"\
 "$(INTDIR)\Tproj32.pch"
   $(BuildCmds)

"$(INTDIR)\TEPRODEF.SBR" : $(SOURCE) $(DEP_CPP_TEPRO) "$(INTDIR)"\
 "$(INTDIR)\Tproj32.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\TPROJECT\MENUKEY.CXX
DEP_CPP_MENUK=\
	"..\..\..\..\Cv32.mvc\Include\Gc.h"\
	"..\..\..\..\msdev\atl11\include\atlbase.h"\
	"..\..\..\..\msdev\atl11\include\atlcom.h"\
	"..\..\..\..\msdev\atl11\include\atlcomx.h"\
	"..\..\..\..\msdev\atl11\include\atlutil.h"\
	"..\tproject.h"\
	".\..\DEFPROJ.H"\
	".\..\MENUKEY.HXX"\
	".\..\TPROJP.HXX"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTFX.HXX"\
	{$(INCLUDE)}"\ctfxmfc.h"\
	{$(INCLUDE)}"\ctfxmfc.nocom.h"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
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
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	

!IF  "$(CFG)" == "Tproj32 - Win32 Release"

# ADD CPP /Yu"tprojp.hxx"

"$(INTDIR)\MENUKEY.OBJ" : $(SOURCE) $(DEP_CPP_MENUK) "$(INTDIR)"\
 "$(INTDIR)\Tproj32.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "STRICT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__XT" /D "__DEXPROCS" /D\
 "__XTENSDLL__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT"\
 /Fp"$(INTDIR)/Tproj32.pch" /Yu"tprojp.hxx" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Tproj32 - Win32 Debug"

# ADD CPP /Yu"tprojp.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "STRICT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__XT" /D\
 "__DEXPROCS" /D "__XTENSNDLL__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT"\
 /FR"$(INTDIR)/" /Fp"$(INTDIR)/Tproj32.pch" /Yu"tprojp.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\MENUKEY.OBJ" : $(SOURCE) $(DEP_CPP_MENUK) "$(INTDIR)"\
 "$(INTDIR)\Tproj32.pch"
   $(BuildCmds)

"$(INTDIR)\MENUKEY.SBR" : $(SOURCE) $(DEP_CPP_MENUK) "$(INTDIR)"\
 "$(INTDIR)\Tproj32.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\TPROJECT\TXTEDIT.CXX
DEP_CPP_TXTED=\
	"..\..\..\..\Cv32.mvc\Include\Gc.h"\
	"..\..\..\..\msdev\atl11\include\atlbase.h"\
	"..\..\..\..\msdev\atl11\include\atlcom.h"\
	"..\..\..\..\msdev\atl11\include\atlcomx.h"\
	"..\..\..\..\msdev\atl11\include\atlutil.h"\
	"..\tproject.h"\
	".\..\DEFPROJ.H"\
	".\..\TPROJP.HXX"\
	".\..\TXTEDIT.HXX"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTFX.HXX"\
	{$(INCLUDE)}"\ctfxmfc.h"\
	{$(INCLUDE)}"\ctfxmfc.nocom.h"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
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
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	

!IF  "$(CFG)" == "Tproj32 - Win32 Release"


"$(INTDIR)\TXTEDIT.OBJ" : $(SOURCE) $(DEP_CPP_TXTED) "$(INTDIR)"\
 "$(INTDIR)\Tproj32.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "STRICT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__XT" /D "__DEXPROCS" /D\
 "__XTENSDLL__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT"\
 /Fp"$(INTDIR)/Tproj32.pch" /Yu"tprojp.hxx" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Tproj32 - Win32 Debug"

# ADD CPP /Yu"tprojp.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "STRICT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__XT" /D\
 "__DEXPROCS" /D "__XTENSNDLL__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT"\
 /FR"$(INTDIR)/" /Fp"$(INTDIR)/Tproj32.pch" /Yu"tprojp.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\TXTEDIT.OBJ" : $(SOURCE) $(DEP_CPP_TXTED) "$(INTDIR)"\
 "$(INTDIR)\Tproj32.pch"
   $(BuildCmds)

"$(INTDIR)\TXTEDIT.SBR" : $(SOURCE) $(DEP_CPP_TXTED) "$(INTDIR)"\
 "$(INTDIR)\Tproj32.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TPROJ32.RC
DEP_RSC_TPROJ3=\
	"..\tproject.h"\
	".\about.h"\
	".\About.src"\
	".\Region.ico"\
	".\Tproj32.rcv"\
	{$(INCLUDE)}"\Resstrg.h"\
	

"$(INTDIR)\TPROJ32.res" : $(SOURCE) $(DEP_RSC_TPROJ3) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\TPROJ32.DEF

!IF  "$(CFG)" == "Tproj32 - Win32 Release"

!ELSEIF  "$(CFG)" == "Tproj32 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Triasdev.mvc\Xtension\Tproject\Tpmember.cxx
DEP_CPP_TPMEM=\
	"..\..\..\..\Cv32.mvc\Include\Gc.h"\
	"..\..\..\..\msdev\atl11\include\atlbase.h"\
	"..\..\..\..\msdev\atl11\include\atlcom.h"\
	"..\..\..\..\msdev\atl11\include\atlcomx.h"\
	"..\..\..\..\msdev\atl11\include\atlutil.h"\
	"..\tproject.h"\
	".\..\about.h"\
	".\..\ABOUT.HXX"\
	".\..\DEFPROJ.H"\
	".\..\MENUKEY.HXX"\
	".\..\PROJPROF.HXX"\
	".\..\TEPRODEF.HXX"\
	".\..\TPMCODE.HXX"\
	".\..\TPROJECT.HXX"\
	".\..\TPROJP.HXX"\
	".\..\TXTEDIT.HXX"\
	".\..\VERSIO16.H"\
	".\..\VERSION.H"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTFX.HXX"\
	{$(INCLUDE)}"\ctfxmfc.h"\
	{$(INCLUDE)}"\ctfxmfc.nocom.h"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
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
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	

!IF  "$(CFG)" == "Tproj32 - Win32 Release"


"$(INTDIR)\Tpmember.obj" : $(SOURCE) $(DEP_CPP_TPMEM) "$(INTDIR)"\
 "$(INTDIR)\Tproj32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Tproj32 - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Tpmember.obj" : $(SOURCE) $(DEP_CPP_TPMEM) "$(INTDIR)"\
 "$(INTDIR)\Tproj32.pch"
   $(BuildCmds)

"$(INTDIR)\Tpmember.sbr" : $(SOURCE) $(DEP_CPP_TPMEM) "$(INTDIR)"\
 "$(INTDIR)\Tproj32.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
