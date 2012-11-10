# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=Toporel - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Toporel - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Toporel - Win32 Release" && "$(CFG)" !=\
 "Toporel - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "TopoRel.mak" CFG="Toporel - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Toporel - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Toporel - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "Toporel - Win32 Debug"
RSC=rc.exe
CPP=cl.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "Toporel - Win32 Release"

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
TargetName=toporel
# End Custom Macros

ALL : "$(OUTDIR)\toporel.ext" "..\..\TRIAS\TRIAS32R\toporel.ext"

CLEAN : 
	-@erase "$(INTDIR)\NUMTREE.OBJ"
	-@erase "$(INTDIR)\RELAUSW.OBJ"
	-@erase "$(INTDIR)\TOPOEXT.OBJ"
	-@erase "$(INTDIR)\TOPOREL.OBJ"
	-@erase "$(INTDIR)\TopoRel.pch"
	-@erase "$(INTDIR)\Toporel.res"
	-@erase "$(INTDIR)\TOPORELP.OBJ"
	-@erase "$(OUTDIR)\toporel.exp"
	-@erase "$(OUTDIR)\toporel.ext"
	-@erase "$(OUTDIR)\toporel.lib"
	-@erase "..\..\TRIAS\TRIAS32R\toporel.ext"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /O2 /I "..\z_hxx" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "DLL" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "MSCC8" /D "__CV__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "__ATL_11_USED__" /Yu"toporelp.hxx" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W3 /WX /GX /O2 /I "..\z_hxx" /D "NDEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "DLL" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D\
 "MSCC8" /D "__CV__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D\
 "QI_EXCEPTION" /D "__ATL_11_USED__" /Fp"$(INTDIR)/TopoRel.pch"\
 /Yu"toporelp.hxx" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\WinRel/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /i "..\z_hxx" /d "NDEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/Toporel.res" /i "..\z_hxx" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/TopoRel.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 geometr.lib ixtatr42.lib stdcppr.lib tfrmwork.lib cont32r.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib triastlb.lib /nologo /dll /machine:I386 /out:"WinRel\toporel.ext" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=geometr.lib ixtatr42.lib stdcppr.lib tfrmwork.lib cont32r.lib\
 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib\
 shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib\
 triastlb.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)/toporel.pdb"\
 /machine:I386 /def:".\TOPOREL.DEF" /out:"$(OUTDIR)/toporel.ext"\
 /implib:"$(OUTDIR)/toporel.lib" /SUBSYSTEM:windows,4.0 
DEF_FILE= \
	".\TOPOREL.DEF"
LINK32_OBJS= \
	"$(INTDIR)\NUMTREE.OBJ" \
	"$(INTDIR)\RELAUSW.OBJ" \
	"$(INTDIR)\TOPOEXT.OBJ" \
	"$(INTDIR)\TOPOREL.OBJ" \
	"$(INTDIR)\Toporel.res" \
	"$(INTDIR)\TOPORELP.OBJ"

"$(OUTDIR)\toporel.ext" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying Target to Destination ...
TargetPath=.\WinRel\toporel.ext
TargetName=toporel
InputPath=.\WinRel\toporel.ext
SOURCE=$(InputPath)

"D:\TRIAS\TRIAS32R\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   copy "$(TargetPath)" D:\TRIAS\TRIAS32R

# End Custom Build

!ELSEIF  "$(CFG)" == "Toporel - Win32 Debug"

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
TargetName=toporeld
# End Custom Macros

ALL : "$(OUTDIR)\toporeld.ext" "$(OUTDIR)\TopoRel.bsc"\
 "..\..\TRIAS\TRIAS32D\toporeld.ext"

CLEAN : 
	-@erase "$(INTDIR)\NUMTREE.OBJ"
	-@erase "$(INTDIR)\NUMTREE.SBR"
	-@erase "$(INTDIR)\RELAUSW.OBJ"
	-@erase "$(INTDIR)\RELAUSW.SBR"
	-@erase "$(INTDIR)\TOPOEXT.OBJ"
	-@erase "$(INTDIR)\TOPOEXT.SBR"
	-@erase "$(INTDIR)\TOPOREL.OBJ"
	-@erase "$(INTDIR)\Toporel.res"
	-@erase "$(INTDIR)\TOPOREL.SBR"
	-@erase "$(INTDIR)\TOPORELD.idb"
	-@erase "$(INTDIR)\TOPORELD.pch"
	-@erase "$(INTDIR)\TOPORELD.pdb"
	-@erase "$(INTDIR)\TOPORELP.OBJ"
	-@erase "$(INTDIR)\TOPORELP.SBR"
	-@erase "$(OUTDIR)\TopoRel.bsc"
	-@erase "$(OUTDIR)\toporeld.exp"
	-@erase "$(OUTDIR)\toporeld.ext"
	-@erase "$(OUTDIR)\toporeld.ilk"
	-@erase "$(OUTDIR)\toporeld.lib"
	-@erase "..\..\TRIAS\TRIAS32D\toporeld.ext"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

.\WinDebug\TOPOREL.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /I "..\z_hxx" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "DLL" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "MSCC8" /D "__CV__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "__ATL_11_USED__" /Fr /Fp"WinDebug/TOPORELD.pch" /Yu"toporelp.hxx" /Fd"WinDebug/TOPORELD.pdb" /c
CPP_PROJ=/nologo /MDd /W3 /WX /Gm /GX /Zi /Od /I "..\z_hxx" /D "_DEBUG" /D\
 "WIN32" /D "_WINDOWS" /D "STRICT" /D "DLL" /D "__XT" /D "__DEXPROCS" /D\
 "MSWIND" /D "MSCC8" /D "__CV__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D\
 "QI_EXCEPTION" /D "__ATL_11_USED__" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/TOPORELD.pch"\
 /Yu"toporelp.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/TOPORELD.pdb" /c 
CPP_OBJS=.\WinDebug/
CPP_SBRS=.\WinDebug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /i "..\z_hxx" /d "_DEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/Toporel.res" /i "..\z_hxx" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/TopoRel.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\NUMTREE.SBR" \
	"$(INTDIR)\RELAUSW.SBR" \
	"$(INTDIR)\TOPOEXT.SBR" \
	"$(INTDIR)\TOPOREL.SBR" \
	"$(INTDIR)\TOPORELP.SBR"

"$(OUTDIR)\TopoRel.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 geometd.lib ixtatd42.lib stdcppd.lib tfrm32d.lib cont32d.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib triastld.lib /nologo /dll /debug /machine:I386 /out:"WinDebug\toporeld.ext" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=geometd.lib ixtatd42.lib stdcppd.lib tfrm32d.lib cont32d.lib\
 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib\
 shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib\
 triastld.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)/toporeld.pdb" /debug\
 /machine:I386 /def:".\TOPOREL.DEF" /out:"$(OUTDIR)/toporeld.ext"\
 /implib:"$(OUTDIR)/toporeld.lib" /SUBSYSTEM:windows,4.0 
DEF_FILE= \
	".\TOPOREL.DEF"
LINK32_OBJS= \
	"$(INTDIR)\NUMTREE.OBJ" \
	"$(INTDIR)\RELAUSW.OBJ" \
	"$(INTDIR)\TOPOEXT.OBJ" \
	"$(INTDIR)\TOPOREL.OBJ" \
	"$(INTDIR)\Toporel.res" \
	"$(INTDIR)\TOPORELP.OBJ"

"$(OUTDIR)\toporeld.ext" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying Target to Destination ...
TargetPath=.\WinDebug\toporeld.ext
TargetName=toporeld
InputPath=.\WinDebug\toporeld.ext
SOURCE=$(InputPath)

"D:\TRIAS\TRIAS32D\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   copy "$(TargetPath)" D:\TRIAS\TRIAS32D

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

# Name "Toporel - Win32 Release"
# Name "Toporel - Win32 Debug"

!IF  "$(CFG)" == "Toporel - Win32 Release"

!ELSEIF  "$(CFG)" == "Toporel - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\NUMTREE.CXX

!IF  "$(CFG)" == "Toporel - Win32 Release"

DEP_CPP_NUMTR=\
	"..\z_hxx\ctfx.hxx"\
	"..\z_hxx\ctfxmfc.h"\
	"..\z_hxx\errcodes.hxx"\
	"..\z_hxx\geo_obj.hxx"\
	"..\z_hxx\geokonst.hxx"\
	"..\z_hxx\GeometrM.hxx"\
	"..\z_hxx\selidlsx.hxx"\
	".\TopoRelConfig.h"\
	".\TopoRelP.hxx"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\COPTTREE.HXX"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\GC_CPP.H"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
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
	{$(INCLUDE)}"\PRINT.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\YXVALS.H"\
	

"$(INTDIR)\NUMTREE.OBJ" : $(SOURCE) $(DEP_CPP_NUMTR) "$(INTDIR)"\
 "$(INTDIR)\TopoRel.pch"


!ELSEIF  "$(CFG)" == "Toporel - Win32 Debug"

DEP_CPP_NUMTR=\
	"..\z_hxx\ctfx.hxx"\
	"..\z_hxx\ctfxmfc.h"\
	"..\z_hxx\errcodes.hxx"\
	"..\z_hxx\geo_obj.hxx"\
	"..\z_hxx\geokonst.hxx"\
	"..\z_hxx\GeometrM.hxx"\
	"..\z_hxx\selidlsx.hxx"\
	".\Numtree.hxx"\
	".\RelAusw.hxx"\
	".\RelKonst.hxx"\
	".\TopoRelConfig.h"\
	".\TopoRelM.hxx"\
	".\TopoRelP.hxx"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\COPTTREE.HXX"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\GC_CPP.H"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
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
	{$(INCLUDE)}"\PRINT.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\YXVALS.H"\
	

"$(INTDIR)\NUMTREE.OBJ" : $(SOURCE) $(DEP_CPP_NUMTR) "$(INTDIR)"\
 "$(INTDIR)\TOPORELD.pch"

"$(INTDIR)\NUMTREE.SBR" : $(SOURCE) $(DEP_CPP_NUMTR) "$(INTDIR)"\
 "$(INTDIR)\TOPORELD.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TOPOREL.CXX

!IF  "$(CFG)" == "Toporel - Win32 Release"

DEP_CPP_TOPOR=\
	"..\z_hxx\datbank.hxx"\
	"..\z_hxx\FormatString.hxx"\
	"..\z_hxx\GeomDLL.hxx"\
	"..\z_hxx\geotrias.hxx"\
	"..\z_hxx\ProgressProxy.h"\
	"..\z_hxx\progstat.h"\
	"..\z_hxx\reinguid.h"\
	"..\z_hxx\trelguid.h"\
	".\SmartInterfaces.h"\
	".\TopoRel.hxx"\
	".\TopoRelConfig.h"\
	".\TopoRelP.hxx"\
	".\version.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	

"$(INTDIR)\TOPOREL.OBJ" : $(SOURCE) $(DEP_CPP_TOPOR) "$(INTDIR)"\
 "$(INTDIR)\TopoRel.pch"


!ELSEIF  "$(CFG)" == "Toporel - Win32 Debug"

DEP_CPP_TOPOR=\
	"..\z_hxx\ctfx.hxx"\
	"..\z_hxx\ctfxmfc.h"\
	"..\z_hxx\datbank.hxx"\
	"..\z_hxx\errcodes.hxx"\
	"..\z_hxx\FormatString.hxx"\
	"..\z_hxx\geo_obj.hxx"\
	"..\z_hxx\geokonst.hxx"\
	"..\z_hxx\GeomDLL.hxx"\
	"..\z_hxx\GeometrM.hxx"\
	"..\z_hxx\geotrias.hxx"\
	"..\z_hxx\ProgressProxy.h"\
	"..\z_hxx\progstat.h"\
	"..\z_hxx\reinguid.h"\
	"..\z_hxx\selidlsx.hxx"\
	"..\z_hxx\trelguid.h"\
	".\Numtree.hxx"\
	".\RelAusw.hxx"\
	".\RelKonst.hxx"\
	".\SmartInterfaces.h"\
	".\TopoRel.hxx"\
	".\TopoRelConfig.h"\
	".\TopoRelM.hxx"\
	".\TopoRelP.hxx"\
	".\version.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\COPTTREE.HXX"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\GC_CPP.H"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
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
	{$(INCLUDE)}"\PRINT.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\YXVALS.H"\
	

"$(INTDIR)\TOPOREL.OBJ" : $(SOURCE) $(DEP_CPP_TOPOR) "$(INTDIR)"\
 "$(INTDIR)\TOPORELD.pch"

"$(INTDIR)\TOPOREL.SBR" : $(SOURCE) $(DEP_CPP_TOPOR) "$(INTDIR)"\
 "$(INTDIR)\TOPORELD.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TOPORELP.CXX

!IF  "$(CFG)" == "Toporel - Win32 Release"

DEP_CPP_TOPORE=\
	"..\z_hxx\ctfx.hxx"\
	"..\z_hxx\ctfxmfc.h"\
	"..\z_hxx\errcodes.hxx"\
	"..\z_hxx\geo_obj.hxx"\
	"..\z_hxx\geokonst.hxx"\
	"..\z_hxx\GeometrM.hxx"\
	"..\z_hxx\selidlsx.hxx"\
	".\TopoRelConfig.h"\
	".\TopoRelP.hxx"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLIMPL.CPP"\
	{$(INCLUDE)}"\Atlimpl11.h"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\COPTTREE.HXX"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\GC_CPP.H"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
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
	{$(INCLUDE)}"\PRINT.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\YXVALS.H"\
	
# ADD CPP /Yc"toporelp.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O2 /I "..\z_hxx" /D "NDEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "DLL" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D\
 "MSCC8" /D "__CV__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D\
 "QI_EXCEPTION" /D "__ATL_11_USED__" /Fp"$(INTDIR)/TopoRel.pch"\
 /Yc"toporelp.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\TOPORELP.OBJ" : $(SOURCE) $(DEP_CPP_TOPORE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\TopoRel.pch" : $(SOURCE) $(DEP_CPP_TOPORE) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Toporel - Win32 Debug"

DEP_CPP_TOPORE=\
	"..\z_hxx\ctfx.hxx"\
	"..\z_hxx\ctfxmfc.h"\
	"..\z_hxx\errcodes.hxx"\
	"..\z_hxx\geo_obj.hxx"\
	"..\z_hxx\geokonst.hxx"\
	"..\z_hxx\GeometrM.hxx"\
	"..\z_hxx\selidlsx.hxx"\
	".\Numtree.hxx"\
	".\RelAusw.hxx"\
	".\RelKonst.hxx"\
	".\TopoRelConfig.h"\
	".\TopoRelM.hxx"\
	".\TopoRelP.hxx"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLIMPL.CPP"\
	{$(INCLUDE)}"\Atlimpl11.h"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\COPTTREE.HXX"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\GC_CPP.H"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
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
	{$(INCLUDE)}"\PRINT.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\YXVALS.H"\
	
# ADD CPP /Yc"toporelp.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /I "..\z_hxx" /D "_DEBUG" /D\
 "WIN32" /D "_WINDOWS" /D "STRICT" /D "DLL" /D "__XT" /D "__DEXPROCS" /D\
 "MSWIND" /D "MSCC8" /D "__CV__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D\
 "QI_EXCEPTION" /D "__ATL_11_USED__" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/TOPORELD.pch"\
 /Yc"toporelp.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/TOPORELD.pdb" /c $(SOURCE) \
	

"$(INTDIR)\TOPORELP.OBJ" : $(SOURCE) $(DEP_CPP_TOPORE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\TOPORELP.SBR" : $(SOURCE) $(DEP_CPP_TOPORE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\TOPORELD.pch" : $(SOURCE) $(DEP_CPP_TOPORE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\RELAUSW.CXX

!IF  "$(CFG)" == "Toporel - Win32 Release"

DEP_CPP_RELAU=\
	".\TopoRelConfig.h"\
	".\TopoRelP.hxx"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	

"$(INTDIR)\RELAUSW.OBJ" : $(SOURCE) $(DEP_CPP_RELAU) "$(INTDIR)"\
 "$(INTDIR)\TopoRel.pch"


!ELSEIF  "$(CFG)" == "Toporel - Win32 Debug"

DEP_CPP_RELAU=\
	"..\z_hxx\ctfx.hxx"\
	"..\z_hxx\ctfxmfc.h"\
	"..\z_hxx\errcodes.hxx"\
	"..\z_hxx\geo_obj.hxx"\
	"..\z_hxx\geokonst.hxx"\
	"..\z_hxx\GeometrM.hxx"\
	"..\z_hxx\selidlsx.hxx"\
	".\Numtree.hxx"\
	".\RelAusw.hxx"\
	".\RelKonst.hxx"\
	".\TopoRelConfig.h"\
	".\TopoRelM.hxx"\
	".\TopoRelP.hxx"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\COPTTREE.HXX"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\GC_CPP.H"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
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
	{$(INCLUDE)}"\PRINT.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\YXVALS.H"\
	

"$(INTDIR)\RELAUSW.OBJ" : $(SOURCE) $(DEP_CPP_RELAU) "$(INTDIR)"\
 "$(INTDIR)\TOPORELD.pch"

"$(INTDIR)\RELAUSW.SBR" : $(SOURCE) $(DEP_CPP_RELAU) "$(INTDIR)"\
 "$(INTDIR)\TOPORELD.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TOPOEXT.CXX

!IF  "$(CFG)" == "Toporel - Win32 Release"

DEP_CPP_TOPOE=\
	"..\z_hxx\geotrias.hxx"\
	"..\z_hxx\objgext.hxx"\
	"..\z_hxx\ProgressProxy.h"\
	"..\z_hxx\progstat.h"\
	"..\z_hxx\reinguid.h"\
	"..\z_hxx\trelguid.h"\
	".\SmartInterfaces.h"\
	".\TopoRel.hxx"\
	".\TopoRelConfig.h"\
	".\TopoRelP.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	

"$(INTDIR)\TOPOEXT.OBJ" : $(SOURCE) $(DEP_CPP_TOPOE) "$(INTDIR)"\
 "$(INTDIR)\TopoRel.pch"


!ELSEIF  "$(CFG)" == "Toporel - Win32 Debug"

DEP_CPP_TOPOE=\
	"..\z_hxx\ctfx.hxx"\
	"..\z_hxx\ctfxmfc.h"\
	"..\z_hxx\errcodes.hxx"\
	"..\z_hxx\geo_obj.hxx"\
	"..\z_hxx\geokonst.hxx"\
	"..\z_hxx\GeometrM.hxx"\
	"..\z_hxx\geotrias.hxx"\
	"..\z_hxx\objgext.hxx"\
	"..\z_hxx\ProgressProxy.h"\
	"..\z_hxx\progstat.h"\
	"..\z_hxx\reinguid.h"\
	"..\z_hxx\selidlsx.hxx"\
	"..\z_hxx\trelguid.h"\
	".\Numtree.hxx"\
	".\RelAusw.hxx"\
	".\RelKonst.hxx"\
	".\SmartInterfaces.h"\
	".\TopoRel.hxx"\
	".\TopoRelConfig.h"\
	".\TopoRelM.hxx"\
	".\TopoRelP.hxx"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\COPTTREE.HXX"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\GC_CPP.H"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
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
	{$(INCLUDE)}"\PRINT.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\YXVALS.H"\
	

"$(INTDIR)\TOPOEXT.OBJ" : $(SOURCE) $(DEP_CPP_TOPOE) "$(INTDIR)"\
 "$(INTDIR)\TOPORELD.pch"

"$(INTDIR)\TOPOEXT.SBR" : $(SOURCE) $(DEP_CPP_TOPOE) "$(INTDIR)"\
 "$(INTDIR)\TOPORELD.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TOPOREL.DEF

!IF  "$(CFG)" == "Toporel - Win32 Release"

!ELSEIF  "$(CFG)" == "Toporel - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Toporel.RC
DEP_RSC_TOPOREL=\
	".\toporel.rcv"\
	{$(INCLUDE)}"\resstrg.h"\
	

"$(INTDIR)\Toporel.res" : $(SOURCE) $(DEP_RSC_TOPOREL) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
# End Target
# End Project
################################################################################
