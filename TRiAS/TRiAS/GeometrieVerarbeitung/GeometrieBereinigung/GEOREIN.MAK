# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=Georein - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Georein - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Georein - Win32 Release" && "$(CFG)" !=\
 "Georein - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Georein.mak" CFG="Georein - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Georein - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Georein - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "Georein - Win32 Debug"
MTL=mktyplib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Georein - Win32 Release"

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
TargetName=georein
# End Custom Macros

ALL : "$(OUTDIR)\georein.ext" "..\..\TRIAS\TRIAS32R\georein.ext"

CLEAN : 
	-@erase "$(INTDIR)\Badpunkt.obj"
	-@erase "$(INTDIR)\Doppunkt.obj"
	-@erase "$(INTDIR)\Entartet.obj"
	-@erase "$(INTDIR)\Geofehl.obj"
	-@erase "$(INTDIR)\Geomtest.obj"
	-@erase "$(INTDIR)\GEOREIN.OBJ"
	-@erase "$(INTDIR)\Georein.pch"
	-@erase "$(INTDIR)\Georein.res"
	-@erase "$(INTDIR)\GEOREINP.OBJ"
	-@erase "$(INTDIR)\Gerrlist.obj"
	-@erase "$(INTDIR)\Greinext.obj"
	-@erase "$(INTDIR)\Insel_ex.obj"
	-@erase "$(INTDIR)\Insel_in.obj"
	-@erase "$(INTDIR)\Kollinea.obj"
	-@erase "$(INTDIR)\Kontinzi.obj"
	-@erase "$(INTDIR)\Offen.obj"
	-@erase "$(INTDIR)\Pa.obj"
	-@erase "$(INTDIR)\Selbinzi.obj"
	-@erase "$(INTDIR)\Spitze.obj"
	-@erase "$(INTDIR)\Umlauf.obj"
	-@erase "$(OUTDIR)\georein.exp"
	-@erase "$(OUTDIR)\georein.ext"
	-@erase "$(OUTDIR)\georein.lib"
	-@erase "..\..\TRIAS\TRIAS32R\georein.ext"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /O2 /I "..\z_hxx" /D "NDEBUG" /D "__ATL_USED__" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "DLL" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "MSCC8" /D "__CV__" /D "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "__ATL_11_USED__" /Yu"georeinp.hxx" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W3 /WX /GX /O2 /I "..\z_hxx" /D "NDEBUG" /D\
 "__ATL_USED__" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "DLL" /D "__XT" /D\
 "__DEXPROCS" /D "MSWIND" /D "MSCC8" /D "__CV__" /D "OS_NO_STREAM_SUPPORT" /D\
 "QI_EXCEPTION" /D "__ATL_11_USED__" /Fp"$(INTDIR)/Georein.pch"\
 /Yu"georeinp.hxx" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\WinRel/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /i "..\z_hxx" /d "NDEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/Georein.res" /i "..\z_hxx" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Georein.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 geometr.lib ixtatr42.lib stdcppr.lib tfrmwork.lib cont32r.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"WinRel/georein.ext" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=geometr.lib ixtatr42.lib stdcppr.lib tfrmwork.lib cont32r.lib\
 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib\
 shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo\
 /dll /incremental:no /pdb:"$(OUTDIR)/georein.pdb" /machine:I386\
 /def:".\GEOREIN.DEF" /out:"$(OUTDIR)/georein.ext"\
 /implib:"$(OUTDIR)/georein.lib" /SUBSYSTEM:windows,4.0 
DEF_FILE= \
	".\GEOREIN.DEF"
LINK32_OBJS= \
	"$(INTDIR)\Badpunkt.obj" \
	"$(INTDIR)\Doppunkt.obj" \
	"$(INTDIR)\Entartet.obj" \
	"$(INTDIR)\Geofehl.obj" \
	"$(INTDIR)\Geomtest.obj" \
	"$(INTDIR)\GEOREIN.OBJ" \
	"$(INTDIR)\Georein.res" \
	"$(INTDIR)\GEOREINP.OBJ" \
	"$(INTDIR)\Gerrlist.obj" \
	"$(INTDIR)\Greinext.obj" \
	"$(INTDIR)\Insel_ex.obj" \
	"$(INTDIR)\Insel_in.obj" \
	"$(INTDIR)\Kollinea.obj" \
	"$(INTDIR)\Kontinzi.obj" \
	"$(INTDIR)\Offen.obj" \
	"$(INTDIR)\Pa.obj" \
	"$(INTDIR)\Selbinzi.obj" \
	"$(INTDIR)\Spitze.obj" \
	"$(INTDIR)\Umlauf.obj"

"$(OUTDIR)\georein.ext" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying Target to Destination ...
TargetPath=.\WinRel\georein.ext
TargetName=georein
InputPath=.\WinRel\georein.ext
SOURCE=$(InputPath)

"D:\TRIAS\TRIAS32R\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   copy "$(TargetPath)" D:\TRIAS\TRIAS32R

# End Custom Build

!ELSEIF  "$(CFG)" == "Georein - Win32 Debug"

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
TargetName=georeind
# End Custom Macros

ALL : "$(OUTDIR)\georeind.ext" "$(OUTDIR)\Georein.bsc"\
 "..\..\TRIAS\TRIAS32D\georeind.ext"

CLEAN : 
	-@erase "$(INTDIR)\Badpunkt.obj"
	-@erase "$(INTDIR)\Badpunkt.sbr"
	-@erase "$(INTDIR)\Doppunkt.obj"
	-@erase "$(INTDIR)\Doppunkt.sbr"
	-@erase "$(INTDIR)\Entartet.obj"
	-@erase "$(INTDIR)\Entartet.sbr"
	-@erase "$(INTDIR)\Geofehl.obj"
	-@erase "$(INTDIR)\Geofehl.sbr"
	-@erase "$(INTDIR)\Geomtest.obj"
	-@erase "$(INTDIR)\Geomtest.sbr"
	-@erase "$(INTDIR)\GEOREIN.OBJ"
	-@erase "$(INTDIR)\Georein.res"
	-@erase "$(INTDIR)\GEOREIN.SBR"
	-@erase "$(INTDIR)\GEOREIND.idb"
	-@erase "$(INTDIR)\GEOREIND.pch"
	-@erase "$(INTDIR)\GEOREIND.pdb"
	-@erase "$(INTDIR)\GEOREINP.OBJ"
	-@erase "$(INTDIR)\GEOREINP.SBR"
	-@erase "$(INTDIR)\Gerrlist.obj"
	-@erase "$(INTDIR)\Gerrlist.sbr"
	-@erase "$(INTDIR)\Greinext.obj"
	-@erase "$(INTDIR)\Greinext.sbr"
	-@erase "$(INTDIR)\Insel_ex.obj"
	-@erase "$(INTDIR)\Insel_ex.sbr"
	-@erase "$(INTDIR)\Insel_in.obj"
	-@erase "$(INTDIR)\Insel_in.sbr"
	-@erase "$(INTDIR)\Kollinea.obj"
	-@erase "$(INTDIR)\Kollinea.sbr"
	-@erase "$(INTDIR)\Kontinzi.obj"
	-@erase "$(INTDIR)\Kontinzi.sbr"
	-@erase "$(INTDIR)\Offen.obj"
	-@erase "$(INTDIR)\Offen.sbr"
	-@erase "$(INTDIR)\Pa.obj"
	-@erase "$(INTDIR)\Pa.sbr"
	-@erase "$(INTDIR)\Selbinzi.obj"
	-@erase "$(INTDIR)\Selbinzi.sbr"
	-@erase "$(INTDIR)\Spitze.obj"
	-@erase "$(INTDIR)\Spitze.sbr"
	-@erase "$(INTDIR)\Umlauf.obj"
	-@erase "$(INTDIR)\Umlauf.sbr"
	-@erase "$(OUTDIR)\Georein.bsc"
	-@erase "$(OUTDIR)\georeind.exp"
	-@erase "$(OUTDIR)\georeind.ext"
	-@erase "$(OUTDIR)\georeind.lib"
	-@erase "..\..\TRIAS\TRIAS32D\georeind.ext"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

.\WinDebug\GEOREIN.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /I "..\z_hxx" /D "_DEBUG" /D "__ATL_USED__" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "DLL" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "MSCC8" /D "__CV__" /D "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "__ATL_11_USED__" /Fr /Fp"WinDebug/GEOREIND.pch" /Yu"georeinp.hxx" /Fd"WinDebug/GEOREIND.pdb" /c
# SUBTRACT CPP /X
CPP_PROJ=/nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /I "..\z_hxx" /D "_DEBUG" /D\
 "__ATL_USED__" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "DLL" /D "__XT" /D\
 "__DEXPROCS" /D "MSWIND" /D "MSCC8" /D "__CV__" /D "OS_NO_STREAM_SUPPORT" /D\
 "QI_EXCEPTION" /D "__ATL_11_USED__" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/GEOREIND.pch"\
 /Yu"georeinp.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/GEOREIND.pdb" /c 
CPP_OBJS=.\WinDebug/
CPP_SBRS=.\WinDebug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /i "..\z_hxx" /d "_DEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/Georein.res" /i "..\z_hxx" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Georein.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Badpunkt.sbr" \
	"$(INTDIR)\Doppunkt.sbr" \
	"$(INTDIR)\Entartet.sbr" \
	"$(INTDIR)\Geofehl.sbr" \
	"$(INTDIR)\Geomtest.sbr" \
	"$(INTDIR)\GEOREIN.SBR" \
	"$(INTDIR)\GEOREINP.SBR" \
	"$(INTDIR)\Gerrlist.sbr" \
	"$(INTDIR)\Greinext.sbr" \
	"$(INTDIR)\Insel_ex.sbr" \
	"$(INTDIR)\Insel_in.sbr" \
	"$(INTDIR)\Kollinea.sbr" \
	"$(INTDIR)\Kontinzi.sbr" \
	"$(INTDIR)\Offen.sbr" \
	"$(INTDIR)\Pa.sbr" \
	"$(INTDIR)\Selbinzi.sbr" \
	"$(INTDIR)\Spitze.sbr" \
	"$(INTDIR)\Umlauf.sbr"

"$(OUTDIR)\Georein.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 geometd.lib ixtatd42.lib stdcppd.lib tfrm32d.lib cont32d.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /profile /debug /machine:I386 /out:"WinDebug/georeind.ext" /SUBSYSTEM:windows,4.0
LINK32_FLAGS=geometd.lib ixtatd42.lib stdcppd.lib tfrm32d.lib cont32d.lib\
 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib\
 shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo\
 /dll /profile /debug /machine:I386 /def:".\GEOREIN.DEF"\
 /out:"$(OUTDIR)/georeind.ext" /implib:"$(OUTDIR)/georeind.lib"\
 /SUBSYSTEM:windows,4.0 
DEF_FILE= \
	".\GEOREIN.DEF"
LINK32_OBJS= \
	"$(INTDIR)\Badpunkt.obj" \
	"$(INTDIR)\Doppunkt.obj" \
	"$(INTDIR)\Entartet.obj" \
	"$(INTDIR)\Geofehl.obj" \
	"$(INTDIR)\Geomtest.obj" \
	"$(INTDIR)\GEOREIN.OBJ" \
	"$(INTDIR)\Georein.res" \
	"$(INTDIR)\GEOREINP.OBJ" \
	"$(INTDIR)\Gerrlist.obj" \
	"$(INTDIR)\Greinext.obj" \
	"$(INTDIR)\Insel_ex.obj" \
	"$(INTDIR)\Insel_in.obj" \
	"$(INTDIR)\Kollinea.obj" \
	"$(INTDIR)\Kontinzi.obj" \
	"$(INTDIR)\Offen.obj" \
	"$(INTDIR)\Pa.obj" \
	"$(INTDIR)\Selbinzi.obj" \
	"$(INTDIR)\Spitze.obj" \
	"$(INTDIR)\Umlauf.obj"

"$(OUTDIR)\georeind.ext" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying Target to Destination ...
TargetPath=.\WinDebug\georeind.ext
TargetName=georeind
InputPath=.\WinDebug\georeind.ext
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

# Name "Georein - Win32 Release"
# Name "Georein - Win32 Debug"

!IF  "$(CFG)" == "Georein - Win32 Release"

!ELSEIF  "$(CFG)" == "Georein - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\GEOREIN.CXX

!IF  "$(CFG)" == "Georein - Win32 Release"

DEP_CPP_GEORE=\
	"..\z_hxx\abstguid.h"\
	"..\z_hxx\ctfx.hxx"\
	"..\z_hxx\ctfxmfc.h"\
	"..\z_hxx\datbank.hxx"\
	"..\z_hxx\errcodes.hxx"\
	"..\z_hxx\ErrorCorrection.hxx"\
	"..\z_hxx\FormatString.hxx"\
	"..\z_hxx\geo_obj.hxx"\
	"..\z_hxx\geokonst.hxx"\
	"..\z_hxx\GeomDLL.hxx"\
	"..\z_hxx\GeometrM.hxx"\
	"..\z_hxx\geotrias.hxx"\
	"..\z_hxx\koord.hxx"\
	"..\z_hxx\objgguid.h"\
	"..\z_hxx\reinguid.h"\
	"..\z_hxx\trelguid.h"\
	".\..\..\..\Triasdev.Mvc\INCLUDE\RESSTRG.H"\
	".\Geofehl.hxx"\
	".\georein.hxx"\
	".\GeoreinConfig.h"\
	".\GeoReinM.hxx"\
	".\GeoReinP.hxx"\
	".\Gerrlist.hxx"\
	".\Pa.hxx"\
	".\ReinKonst.hxx"\
	".\SmartInterfaces.h"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
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
	{$(INCLUDE)}"\numeditx.hxx"\
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
	{$(INCLUDE)}"\REGISTRX.HXX"\
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
	

"$(INTDIR)\GEOREIN.OBJ" : $(SOURCE) $(DEP_CPP_GEORE) "$(INTDIR)"\
 "$(INTDIR)\Georein.pch"


!ELSEIF  "$(CFG)" == "Georein - Win32 Debug"

DEP_CPP_GEORE=\
	"..\z_hxx\datbank.hxx"\
	"..\z_hxx\GeomDLL.hxx"\
	".\..\..\..\Triasdev.Mvc\INCLUDE\RESSTRG.H"\
	".\georein.hxx"\
	".\GeoreinConfig.h"\
	".\GeoReinP.hxx"\
	".\Pa.hxx"\
	".\SmartInterfaces.h"\
	".\version.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
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
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\GEOREIN.OBJ" : $(SOURCE) $(DEP_CPP_GEORE) "$(INTDIR)"\
 "$(INTDIR)\GEOREIND.pch"

"$(INTDIR)\GEOREIN.SBR" : $(SOURCE) $(DEP_CPP_GEORE) "$(INTDIR)"\
 "$(INTDIR)\GEOREIND.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GEOREINP.CXX
DEP_CPP_GEOREI=\
	"..\z_hxx\ctfx.hxx"\
	"..\z_hxx\ctfxmfc.h"\
	"..\z_hxx\errcodes.hxx"\
	"..\z_hxx\ErrorCorrection.hxx"\
	"..\z_hxx\FormatString.hxx"\
	"..\z_hxx\geo_obj.hxx"\
	"..\z_hxx\geokonst.hxx"\
	"..\z_hxx\GeometrM.hxx"\
	"..\z_hxx\geotrias.hxx"\
	"..\z_hxx\koord.hxx"\
	".\Geofehl.hxx"\
	".\GeoreinConfig.h"\
	".\GeoReinM.hxx"\
	".\GeoReinP.hxx"\
	".\Gerrlist.hxx"\
	".\ReinKonst.hxx"\
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
	{$(INCLUDE)}"\REGISTRX.HXX"\
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
	

!IF  "$(CFG)" == "Georein - Win32 Release"

# ADD CPP /Yc"georeinp.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O2 /I "..\z_hxx" /D "NDEBUG" /D "__ATL_USED__"\
 /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "DLL" /D "__XT" /D "__DEXPROCS" /D\
 "MSWIND" /D "MSCC8" /D "__CV__" /D "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D\
 "__ATL_11_USED__" /Fp"$(INTDIR)/Georein.pch" /Yc"georeinp.hxx" /Fo"$(INTDIR)/"\
 /c $(SOURCE) \
	

"$(INTDIR)\GEOREINP.OBJ" : $(SOURCE) $(DEP_CPP_GEOREI) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Georein.pch" : $(SOURCE) $(DEP_CPP_GEOREI) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Georein - Win32 Debug"

# ADD CPP /Yc"georeinp.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /I "..\z_hxx" /D "_DEBUG" /D\
 "__ATL_USED__" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "DLL" /D "__XT" /D\
 "__DEXPROCS" /D "MSWIND" /D "MSCC8" /D "__CV__" /D "OS_NO_STREAM_SUPPORT" /D\
 "QI_EXCEPTION" /D "__ATL_11_USED__" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/GEOREIND.pch"\
 /Yc"georeinp.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/GEOREIND.pdb" /c $(SOURCE) \
	

"$(INTDIR)\GEOREINP.OBJ" : $(SOURCE) $(DEP_CPP_GEOREI) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\GEOREINP.SBR" : $(SOURCE) $(DEP_CPP_GEOREI) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\GEOREIND.pch" : $(SOURCE) $(DEP_CPP_GEOREI) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Badpunkt.cxx
DEP_CPP_BADPU=\
	"..\z_hxx\ctfx.hxx"\
	"..\z_hxx\ctfxmfc.h"\
	"..\z_hxx\errcodes.hxx"\
	"..\z_hxx\ErrorCorrection.hxx"\
	"..\z_hxx\FormatString.hxx"\
	"..\z_hxx\geo_obj.hxx"\
	"..\z_hxx\geokonst.hxx"\
	"..\z_hxx\GeometrM.hxx"\
	"..\z_hxx\geotrias.hxx"\
	"..\z_hxx\koord.hxx"\
	".\badpunkt.hxx"\
	".\Geofehl.hxx"\
	".\GeoreinConfig.h"\
	".\GeoReinM.hxx"\
	".\GeoReinP.hxx"\
	".\Gerrlist.hxx"\
	".\ReinKonst.hxx"\
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
	{$(INCLUDE)}"\REGISTRX.HXX"\
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
	

!IF  "$(CFG)" == "Georein - Win32 Release"


"$(INTDIR)\Badpunkt.obj" : $(SOURCE) $(DEP_CPP_BADPU) "$(INTDIR)"\
 "$(INTDIR)\Georein.pch"


!ELSEIF  "$(CFG)" == "Georein - Win32 Debug"


"$(INTDIR)\Badpunkt.obj" : $(SOURCE) $(DEP_CPP_BADPU) "$(INTDIR)"\
 "$(INTDIR)\GEOREIND.pch"

"$(INTDIR)\Badpunkt.sbr" : $(SOURCE) $(DEP_CPP_BADPU) "$(INTDIR)"\
 "$(INTDIR)\GEOREIND.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Doppunkt.cxx
DEP_CPP_DOPPU=\
	"..\z_hxx\ctfx.hxx"\
	"..\z_hxx\ctfxmfc.h"\
	"..\z_hxx\errcodes.hxx"\
	"..\z_hxx\ErrorCorrection.hxx"\
	"..\z_hxx\FormatString.hxx"\
	"..\z_hxx\geo_obj.hxx"\
	"..\z_hxx\geokonst.hxx"\
	"..\z_hxx\GeometrM.hxx"\
	"..\z_hxx\geotrias.hxx"\
	"..\z_hxx\koord.hxx"\
	".\doppunkt.hxx"\
	".\Geofehl.hxx"\
	".\GeoreinConfig.h"\
	".\GeoReinM.hxx"\
	".\GeoReinP.hxx"\
	".\Gerrlist.hxx"\
	".\ReinKonst.hxx"\
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
	{$(INCLUDE)}"\REGISTRX.HXX"\
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
	

!IF  "$(CFG)" == "Georein - Win32 Release"


"$(INTDIR)\Doppunkt.obj" : $(SOURCE) $(DEP_CPP_DOPPU) "$(INTDIR)"\
 "$(INTDIR)\Georein.pch"


!ELSEIF  "$(CFG)" == "Georein - Win32 Debug"


"$(INTDIR)\Doppunkt.obj" : $(SOURCE) $(DEP_CPP_DOPPU) "$(INTDIR)"\
 "$(INTDIR)\GEOREIND.pch"

"$(INTDIR)\Doppunkt.sbr" : $(SOURCE) $(DEP_CPP_DOPPU) "$(INTDIR)"\
 "$(INTDIR)\GEOREIND.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Entartet.cxx
DEP_CPP_ENTAR=\
	"..\z_hxx\ctfx.hxx"\
	"..\z_hxx\ctfxmfc.h"\
	"..\z_hxx\errcodes.hxx"\
	"..\z_hxx\ErrorCorrection.hxx"\
	"..\z_hxx\FormatString.hxx"\
	"..\z_hxx\geo_obj.hxx"\
	"..\z_hxx\geokonst.hxx"\
	"..\z_hxx\GeometrM.hxx"\
	"..\z_hxx\geotrias.hxx"\
	"..\z_hxx\koord.hxx"\
	".\entartet.hxx"\
	".\Geofehl.hxx"\
	".\GeoreinConfig.h"\
	".\GeoReinM.hxx"\
	".\GeoReinP.hxx"\
	".\Gerrlist.hxx"\
	".\ReinKonst.hxx"\
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
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\GC_CPP.H"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Hdrentrx.hxx"\
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
	{$(INCLUDE)}"\REGISTRX.HXX"\
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
	

!IF  "$(CFG)" == "Georein - Win32 Release"


"$(INTDIR)\Entartet.obj" : $(SOURCE) $(DEP_CPP_ENTAR) "$(INTDIR)"\
 "$(INTDIR)\Georein.pch"


!ELSEIF  "$(CFG)" == "Georein - Win32 Debug"


"$(INTDIR)\Entartet.obj" : $(SOURCE) $(DEP_CPP_ENTAR) "$(INTDIR)"\
 "$(INTDIR)\GEOREIND.pch"

"$(INTDIR)\Entartet.sbr" : $(SOURCE) $(DEP_CPP_ENTAR) "$(INTDIR)"\
 "$(INTDIR)\GEOREIND.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Geofehl.cxx
DEP_CPP_GEOFE=\
	"..\z_hxx\ctfx.hxx"\
	"..\z_hxx\ctfxmfc.h"\
	"..\z_hxx\errcodes.hxx"\
	"..\z_hxx\ErrorCorrection.hxx"\
	"..\z_hxx\FormatString.hxx"\
	"..\z_hxx\geo_obj.hxx"\
	"..\z_hxx\geokonst.hxx"\
	"..\z_hxx\GeometrM.hxx"\
	"..\z_hxx\geotrias.hxx"\
	"..\z_hxx\koord.hxx"\
	".\Geofehl.hxx"\
	".\GeoreinConfig.h"\
	".\GeoReinM.hxx"\
	".\GeoReinP.hxx"\
	".\Gerrlist.hxx"\
	".\ReinKonst.hxx"\
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
	{$(INCLUDE)}"\REGISTRX.HXX"\
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
	

!IF  "$(CFG)" == "Georein - Win32 Release"


"$(INTDIR)\Geofehl.obj" : $(SOURCE) $(DEP_CPP_GEOFE) "$(INTDIR)"\
 "$(INTDIR)\Georein.pch"


!ELSEIF  "$(CFG)" == "Georein - Win32 Debug"


"$(INTDIR)\Geofehl.obj" : $(SOURCE) $(DEP_CPP_GEOFE) "$(INTDIR)"\
 "$(INTDIR)\GEOREIND.pch"

"$(INTDIR)\Geofehl.sbr" : $(SOURCE) $(DEP_CPP_GEOFE) "$(INTDIR)"\
 "$(INTDIR)\GEOREIND.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Geomtest.cxx

!IF  "$(CFG)" == "Georein - Win32 Release"

DEP_CPP_GEOMT=\
	"..\z_hxx\abstguid.h"\
	"..\z_hxx\BasicFunctions.hxx"\
	"..\z_hxx\objgguid.h"\
	"..\z_hxx\reinguid.h"\
	"..\z_hxx\strecke.hxx"\
	"..\z_hxx\trelguid.h"\
	".\badpunkt.hxx"\
	".\doppunkt.hxx"\
	".\entartet.hxx"\
	".\georein.hxx"\
	".\GeoreinConfig.h"\
	".\GeoReinP.hxx"\
	".\insel_ex.hxx"\
	".\insel_in.hxx"\
	".\kollinea.hxx"\
	".\kontinzi.hxx"\
	".\offen.hxx"\
	".\selbinzi.hxx"\
	".\SmartInterfaces.h"\
	".\spitze.hxx"\
	".\umlauf.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	

"$(INTDIR)\Geomtest.obj" : $(SOURCE) $(DEP_CPP_GEOMT) "$(INTDIR)"\
 "$(INTDIR)\Georein.pch"


!ELSEIF  "$(CFG)" == "Georein - Win32 Debug"

DEP_CPP_GEOMT=\
	"..\z_hxx\abstguid.h"\
	"..\z_hxx\BasicFunctions.hxx"\
	"..\z_hxx\objgguid.h"\
	"..\z_hxx\reinguid.h"\
	"..\z_hxx\strecke.hxx"\
	"..\z_hxx\trelguid.h"\
	".\badpunkt.hxx"\
	".\doppunkt.hxx"\
	".\entartet.hxx"\
	".\georein.hxx"\
	".\GeoreinConfig.h"\
	".\GeoReinP.hxx"\
	".\insel_ex.hxx"\
	".\insel_in.hxx"\
	".\kollinea.hxx"\
	".\kontinzi.hxx"\
	".\offen.hxx"\
	".\selbinzi.hxx"\
	".\SmartInterfaces.h"\
	".\spitze.hxx"\
	".\umlauf.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	

"$(INTDIR)\Geomtest.obj" : $(SOURCE) $(DEP_CPP_GEOMT) "$(INTDIR)"\
 "$(INTDIR)\GEOREIND.pch"

"$(INTDIR)\Geomtest.sbr" : $(SOURCE) $(DEP_CPP_GEOMT) "$(INTDIR)"\
 "$(INTDIR)\GEOREIND.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Gerrlist.cxx
DEP_CPP_GERRL=\
	"..\z_hxx\ctfx.hxx"\
	"..\z_hxx\ctfxmfc.h"\
	"..\z_hxx\errcodes.hxx"\
	"..\z_hxx\ErrorCorrection.hxx"\
	"..\z_hxx\FormatString.hxx"\
	"..\z_hxx\geo_obj.hxx"\
	"..\z_hxx\geokonst.hxx"\
	"..\z_hxx\GeometrM.hxx"\
	"..\z_hxx\geotrias.hxx"\
	"..\z_hxx\koord.hxx"\
	".\Geofehl.hxx"\
	".\GeoreinConfig.h"\
	".\GeoReinM.hxx"\
	".\GeoReinP.hxx"\
	".\Gerrlist.hxx"\
	".\ReinKonst.hxx"\
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
	{$(INCLUDE)}"\REGISTRX.HXX"\
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
	

!IF  "$(CFG)" == "Georein - Win32 Release"


"$(INTDIR)\Gerrlist.obj" : $(SOURCE) $(DEP_CPP_GERRL) "$(INTDIR)"\
 "$(INTDIR)\Georein.pch"


!ELSEIF  "$(CFG)" == "Georein - Win32 Debug"


"$(INTDIR)\Gerrlist.obj" : $(SOURCE) $(DEP_CPP_GERRL) "$(INTDIR)"\
 "$(INTDIR)\GEOREIND.pch"

"$(INTDIR)\Gerrlist.sbr" : $(SOURCE) $(DEP_CPP_GERRL) "$(INTDIR)"\
 "$(INTDIR)\GEOREIND.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Insel_ex.cxx
DEP_CPP_INSEL=\
	"..\z_hxx\ctfx.hxx"\
	"..\z_hxx\ctfxmfc.h"\
	"..\z_hxx\errcodes.hxx"\
	"..\z_hxx\ErrorCorrection.hxx"\
	"..\z_hxx\FormatString.hxx"\
	"..\z_hxx\geo_obj.hxx"\
	"..\z_hxx\geokonst.hxx"\
	"..\z_hxx\GeometrM.hxx"\
	"..\z_hxx\geotrias.hxx"\
	"..\z_hxx\koord.hxx"\
	".\Geofehl.hxx"\
	".\GeoreinConfig.h"\
	".\GeoReinM.hxx"\
	".\GeoReinP.hxx"\
	".\Gerrlist.hxx"\
	".\insel_ex.hxx"\
	".\ReinKonst.hxx"\
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
	{$(INCLUDE)}"\REGISTRX.HXX"\
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
	

!IF  "$(CFG)" == "Georein - Win32 Release"


"$(INTDIR)\Insel_ex.obj" : $(SOURCE) $(DEP_CPP_INSEL) "$(INTDIR)"\
 "$(INTDIR)\Georein.pch"


!ELSEIF  "$(CFG)" == "Georein - Win32 Debug"


"$(INTDIR)\Insel_ex.obj" : $(SOURCE) $(DEP_CPP_INSEL) "$(INTDIR)"\
 "$(INTDIR)\GEOREIND.pch"

"$(INTDIR)\Insel_ex.sbr" : $(SOURCE) $(DEP_CPP_INSEL) "$(INTDIR)"\
 "$(INTDIR)\GEOREIND.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Insel_in.cxx
DEP_CPP_INSEL_=\
	"..\z_hxx\ctfx.hxx"\
	"..\z_hxx\ctfxmfc.h"\
	"..\z_hxx\errcodes.hxx"\
	"..\z_hxx\ErrorCorrection.hxx"\
	"..\z_hxx\FormatString.hxx"\
	"..\z_hxx\geo_obj.hxx"\
	"..\z_hxx\geokonst.hxx"\
	"..\z_hxx\GeometrM.hxx"\
	"..\z_hxx\geotrias.hxx"\
	"..\z_hxx\koord.hxx"\
	".\Geofehl.hxx"\
	".\GeoreinConfig.h"\
	".\GeoReinM.hxx"\
	".\GeoReinP.hxx"\
	".\Gerrlist.hxx"\
	".\insel_in.hxx"\
	".\ReinKonst.hxx"\
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
	{$(INCLUDE)}"\REGISTRX.HXX"\
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
	

!IF  "$(CFG)" == "Georein - Win32 Release"


"$(INTDIR)\Insel_in.obj" : $(SOURCE) $(DEP_CPP_INSEL_) "$(INTDIR)"\
 "$(INTDIR)\Georein.pch"


!ELSEIF  "$(CFG)" == "Georein - Win32 Debug"


"$(INTDIR)\Insel_in.obj" : $(SOURCE) $(DEP_CPP_INSEL_) "$(INTDIR)"\
 "$(INTDIR)\GEOREIND.pch"

"$(INTDIR)\Insel_in.sbr" : $(SOURCE) $(DEP_CPP_INSEL_) "$(INTDIR)"\
 "$(INTDIR)\GEOREIND.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Kollinea.cxx
DEP_CPP_KOLLI=\
	"..\z_hxx\ctfx.hxx"\
	"..\z_hxx\ctfxmfc.h"\
	"..\z_hxx\errcodes.hxx"\
	"..\z_hxx\ErrorCorrection.hxx"\
	"..\z_hxx\FormatString.hxx"\
	"..\z_hxx\geo_obj.hxx"\
	"..\z_hxx\geokonst.hxx"\
	"..\z_hxx\GeometrM.hxx"\
	"..\z_hxx\geotrias.hxx"\
	"..\z_hxx\koord.hxx"\
	".\Geofehl.hxx"\
	".\GeoreinConfig.h"\
	".\GeoReinM.hxx"\
	".\GeoReinP.hxx"\
	".\Gerrlist.hxx"\
	".\kollinea.hxx"\
	".\ReinKonst.hxx"\
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
	{$(INCLUDE)}"\REGISTRX.HXX"\
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
	

!IF  "$(CFG)" == "Georein - Win32 Release"


"$(INTDIR)\Kollinea.obj" : $(SOURCE) $(DEP_CPP_KOLLI) "$(INTDIR)"\
 "$(INTDIR)\Georein.pch"


!ELSEIF  "$(CFG)" == "Georein - Win32 Debug"


"$(INTDIR)\Kollinea.obj" : $(SOURCE) $(DEP_CPP_KOLLI) "$(INTDIR)"\
 "$(INTDIR)\GEOREIND.pch"

"$(INTDIR)\Kollinea.sbr" : $(SOURCE) $(DEP_CPP_KOLLI) "$(INTDIR)"\
 "$(INTDIR)\GEOREIND.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Kontinzi.cxx
DEP_CPP_KONTI=\
	"..\z_hxx\ctfx.hxx"\
	"..\z_hxx\ctfxmfc.h"\
	"..\z_hxx\errcodes.hxx"\
	"..\z_hxx\ErrorCorrection.hxx"\
	"..\z_hxx\FormatString.hxx"\
	"..\z_hxx\geo_obj.hxx"\
	"..\z_hxx\geokonst.hxx"\
	"..\z_hxx\GeometrM.hxx"\
	"..\z_hxx\geotrias.hxx"\
	"..\z_hxx\koord.hxx"\
	".\Geofehl.hxx"\
	".\GeoreinConfig.h"\
	".\GeoReinM.hxx"\
	".\GeoReinP.hxx"\
	".\Gerrlist.hxx"\
	".\kontinzi.hxx"\
	".\ReinKonst.hxx"\
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
	{$(INCLUDE)}"\REGISTRX.HXX"\
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
	

!IF  "$(CFG)" == "Georein - Win32 Release"


"$(INTDIR)\Kontinzi.obj" : $(SOURCE) $(DEP_CPP_KONTI) "$(INTDIR)"\
 "$(INTDIR)\Georein.pch"


!ELSEIF  "$(CFG)" == "Georein - Win32 Debug"


"$(INTDIR)\Kontinzi.obj" : $(SOURCE) $(DEP_CPP_KONTI) "$(INTDIR)"\
 "$(INTDIR)\GEOREIND.pch"

"$(INTDIR)\Kontinzi.sbr" : $(SOURCE) $(DEP_CPP_KONTI) "$(INTDIR)"\
 "$(INTDIR)\GEOREIND.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Offen.cxx
DEP_CPP_OFFEN=\
	"..\z_hxx\ctfx.hxx"\
	"..\z_hxx\ctfxmfc.h"\
	"..\z_hxx\errcodes.hxx"\
	"..\z_hxx\ErrorCorrection.hxx"\
	"..\z_hxx\FormatString.hxx"\
	"..\z_hxx\geo_obj.hxx"\
	"..\z_hxx\geokonst.hxx"\
	"..\z_hxx\GeometrM.hxx"\
	"..\z_hxx\geotrias.hxx"\
	"..\z_hxx\koord.hxx"\
	".\Geofehl.hxx"\
	".\GeoreinConfig.h"\
	".\GeoReinM.hxx"\
	".\GeoReinP.hxx"\
	".\Gerrlist.hxx"\
	".\offen.hxx"\
	".\ReinKonst.hxx"\
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
	{$(INCLUDE)}"\REGISTRX.HXX"\
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
	

!IF  "$(CFG)" == "Georein - Win32 Release"


"$(INTDIR)\Offen.obj" : $(SOURCE) $(DEP_CPP_OFFEN) "$(INTDIR)"\
 "$(INTDIR)\Georein.pch"


!ELSEIF  "$(CFG)" == "Georein - Win32 Debug"


"$(INTDIR)\Offen.obj" : $(SOURCE) $(DEP_CPP_OFFEN) "$(INTDIR)"\
 "$(INTDIR)\GEOREIND.pch"

"$(INTDIR)\Offen.sbr" : $(SOURCE) $(DEP_CPP_OFFEN) "$(INTDIR)"\
 "$(INTDIR)\GEOREIND.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Selbinzi.cxx
DEP_CPP_SELBI=\
	"..\z_hxx\ctfx.hxx"\
	"..\z_hxx\ctfxmfc.h"\
	"..\z_hxx\errcodes.hxx"\
	"..\z_hxx\ErrorCorrection.hxx"\
	"..\z_hxx\FormatString.hxx"\
	"..\z_hxx\geo_obj.hxx"\
	"..\z_hxx\geokonst.hxx"\
	"..\z_hxx\GeometrM.hxx"\
	"..\z_hxx\geotrias.hxx"\
	"..\z_hxx\koord.hxx"\
	".\Geofehl.hxx"\
	".\GeoreinConfig.h"\
	".\GeoReinM.hxx"\
	".\GeoReinP.hxx"\
	".\Gerrlist.hxx"\
	".\ReinKonst.hxx"\
	".\selbinzi.hxx"\
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
	{$(INCLUDE)}"\REGISTRX.HXX"\
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
	

!IF  "$(CFG)" == "Georein - Win32 Release"


"$(INTDIR)\Selbinzi.obj" : $(SOURCE) $(DEP_CPP_SELBI) "$(INTDIR)"\
 "$(INTDIR)\Georein.pch"


!ELSEIF  "$(CFG)" == "Georein - Win32 Debug"


"$(INTDIR)\Selbinzi.obj" : $(SOURCE) $(DEP_CPP_SELBI) "$(INTDIR)"\
 "$(INTDIR)\GEOREIND.pch"

"$(INTDIR)\Selbinzi.sbr" : $(SOURCE) $(DEP_CPP_SELBI) "$(INTDIR)"\
 "$(INTDIR)\GEOREIND.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Spitze.cxx

!IF  "$(CFG)" == "Georein - Win32 Release"

DEP_CPP_SPITZ=\
	".\GeoreinConfig.h"\
	".\GeoReinP.hxx"\
	".\spitze.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	

"$(INTDIR)\Spitze.obj" : $(SOURCE) $(DEP_CPP_SPITZ) "$(INTDIR)"\
 "$(INTDIR)\Georein.pch"


!ELSEIF  "$(CFG)" == "Georein - Win32 Debug"

DEP_CPP_SPITZ=\
	".\GeoreinConfig.h"\
	".\GeoReinP.hxx"\
	".\spitze.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	

"$(INTDIR)\Spitze.obj" : $(SOURCE) $(DEP_CPP_SPITZ) "$(INTDIR)"\
 "$(INTDIR)\GEOREIND.pch"

"$(INTDIR)\Spitze.sbr" : $(SOURCE) $(DEP_CPP_SPITZ) "$(INTDIR)"\
 "$(INTDIR)\GEOREIND.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Umlauf.cxx
DEP_CPP_UMLAU=\
	"..\z_hxx\ctfx.hxx"\
	"..\z_hxx\ctfxmfc.h"\
	"..\z_hxx\errcodes.hxx"\
	"..\z_hxx\ErrorCorrection.hxx"\
	"..\z_hxx\FormatString.hxx"\
	"..\z_hxx\geo_obj.hxx"\
	"..\z_hxx\geokonst.hxx"\
	"..\z_hxx\GeometrM.hxx"\
	"..\z_hxx\geotrias.hxx"\
	"..\z_hxx\koord.hxx"\
	".\Geofehl.hxx"\
	".\GeoreinConfig.h"\
	".\GeoReinM.hxx"\
	".\GeoReinP.hxx"\
	".\Gerrlist.hxx"\
	".\ReinKonst.hxx"\
	".\umlauf.hxx"\
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
	{$(INCLUDE)}"\REGISTRX.HXX"\
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
	

!IF  "$(CFG)" == "Georein - Win32 Release"


"$(INTDIR)\Umlauf.obj" : $(SOURCE) $(DEP_CPP_UMLAU) "$(INTDIR)"\
 "$(INTDIR)\Georein.pch"


!ELSEIF  "$(CFG)" == "Georein - Win32 Debug"


"$(INTDIR)\Umlauf.obj" : $(SOURCE) $(DEP_CPP_UMLAU) "$(INTDIR)"\
 "$(INTDIR)\GEOREIND.pch"

"$(INTDIR)\Umlauf.sbr" : $(SOURCE) $(DEP_CPP_UMLAU) "$(INTDIR)"\
 "$(INTDIR)\GEOREIND.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Greinext.cxx

!IF  "$(CFG)" == "Georein - Win32 Release"

DEP_CPP_GREIN=\
	"..\z_hxx\abstguid.h"\
	"..\z_hxx\datbank.hxx"\
	"..\z_hxx\objgext.hxx"\
	"..\z_hxx\objgguid.h"\
	"..\z_hxx\reinguid.h"\
	"..\z_hxx\trelguid.h"\
	".\georein.hxx"\
	".\GeoreinConfig.h"\
	".\GeoReinP.hxx"\
	".\SmartInterfaces.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\TSTRING"\
	

"$(INTDIR)\Greinext.obj" : $(SOURCE) $(DEP_CPP_GREIN) "$(INTDIR)"\
 "$(INTDIR)\Georein.pch"


!ELSEIF  "$(CFG)" == "Georein - Win32 Debug"

DEP_CPP_GREIN=\
	"..\z_hxx\datbank.hxx"\
	"..\z_hxx\objgext.hxx"\
	".\georein.hxx"\
	".\GeoreinConfig.h"\
	".\GeoReinP.hxx"\
	".\SmartInterfaces.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\TSTRING"\
	

"$(INTDIR)\Greinext.obj" : $(SOURCE) $(DEP_CPP_GREIN) "$(INTDIR)"\
 "$(INTDIR)\GEOREIND.pch"

"$(INTDIR)\Greinext.sbr" : $(SOURCE) $(DEP_CPP_GREIN) "$(INTDIR)"\
 "$(INTDIR)\GEOREIND.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Pa.cxx
DEP_CPP_PA_CX=\
	"..\z_hxx\ctfx.hxx"\
	"..\z_hxx\ctfxmfc.h"\
	"..\z_hxx\errcodes.hxx"\
	"..\z_hxx\ErrorCorrection.hxx"\
	"..\z_hxx\FormatString.hxx"\
	"..\z_hxx\geo_obj.hxx"\
	"..\z_hxx\geokonst.hxx"\
	"..\z_hxx\GeometrM.hxx"\
	"..\z_hxx\geotrias.hxx"\
	"..\z_hxx\koord.hxx"\
	".\Geofehl.hxx"\
	".\GeoreinConfig.h"\
	".\GeoReinM.hxx"\
	".\GeoReinP.hxx"\
	".\Gerrlist.hxx"\
	".\ReinKonst.hxx"\
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
	{$(INCLUDE)}"\REGISTRX.HXX"\
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
	

!IF  "$(CFG)" == "Georein - Win32 Release"


"$(INTDIR)\Pa.obj" : $(SOURCE) $(DEP_CPP_PA_CX) "$(INTDIR)"\
 "$(INTDIR)\Georein.pch"


!ELSEIF  "$(CFG)" == "Georein - Win32 Debug"


"$(INTDIR)\Pa.obj" : $(SOURCE) $(DEP_CPP_PA_CX) "$(INTDIR)"\
 "$(INTDIR)\GEOREIND.pch"

"$(INTDIR)\Pa.sbr" : $(SOURCE) $(DEP_CPP_PA_CX) "$(INTDIR)"\
 "$(INTDIR)\GEOREIND.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GEOREIN.DEF

!IF  "$(CFG)" == "Georein - Win32 Release"

!ELSEIF  "$(CFG)" == "Georein - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Georein.rc
DEP_RSC_GEOREIN=\
	".\..\..\..\Triasdev.Mvc\INCLUDE\RESSTRG.H"\
	".\georein.rcv"\
	

"$(INTDIR)\Georein.res" : $(SOURCE) $(DEP_RSC_GEOREIN) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
# End Target
# End Project
################################################################################
