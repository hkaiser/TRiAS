# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=Raster - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Raster - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Raster - Win32 Release" && "$(CFG)" != "Raster - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Raster.mak" CFG="Raster - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Raster - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Raster - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "Raster - Win32 Debug"
MTL=mktyplib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Raster - Win32 Release"

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
TargetName=Gitter
# End Custom Macros

ALL : "$(OUTDIR)\Gitter.ext" "..\..\TRIAS\TRIAS32R\Gitter.ext"

CLEAN : 
	-@erase "$(INTDIR)\Gitter.obj"
	-@erase "$(INTDIR)\GitterDlg_old.obj"
	-@erase "$(INTDIR)\Raster.pch"
	-@erase "$(INTDIR)\Raster.res"
	-@erase "$(INTDIR)\RASTERP.OBJ"
	-@erase "$(OUTDIR)\Gitter.exp"
	-@erase "$(OUTDIR)\Gitter.ext"
	-@erase "$(OUTDIR)\Gitter.lib"
	-@erase "..\..\TRIAS\TRIAS32R\Gitter.ext"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /O2 /I "..\z_hxx" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "DLL" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "MSCC8" /D "__CV__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "__ATL_11_USED__" /Yu"rasterp.hxx" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W3 /WX /GX /O2 /I "..\z_hxx" /D "NDEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "DLL" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D\
 "MSCC8" /D "__CV__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D\
 "QI_EXCEPTION" /D "__ATL_11_USED__" /Fp"$(INTDIR)/Raster.pch" /Yu"rasterp.hxx"\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\WinRel/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /i "..\z_hxx" /d "NDEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/Raster.res" /i "..\z_hxx" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Raster.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 geometr.lib ixtatr42.lib stdcppr.lib tfrmwork.lib cont32r.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib triastlb.lib /nologo /dll /machine:I386 /out:"WinRel\Gitter.ext" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=geometr.lib ixtatr42.lib stdcppr.lib tfrmwork.lib cont32r.lib\
 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib\
 shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib\
 triastlb.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)/Gitter.pdb"\
 /machine:I386 /def:".\RASTER.DEF" /out:"$(OUTDIR)/Gitter.ext"\
 /implib:"$(OUTDIR)/Gitter.lib" /SUBSYSTEM:windows,4.0 
DEF_FILE= \
	".\RASTER.DEF"
LINK32_OBJS= \
	"$(INTDIR)\Gitter.obj" \
	"$(INTDIR)\GitterDlg_old.obj" \
	"$(INTDIR)\Raster.res" \
	"$(INTDIR)\RASTERP.OBJ"

"$(OUTDIR)\Gitter.ext" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying Target to Destination ...
TargetPath=.\WinRel\Gitter.ext
TargetName=Gitter
InputPath=.\WinRel\Gitter.ext
SOURCE=$(InputPath)

"D:\TRIAS\TRIAS32R\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   copy "$(TargetPath)" D:\TRIAS\TRIAS32R

# End Custom Build

!ELSEIF  "$(CFG)" == "Raster - Win32 Debug"

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
TargetName=GitterD
# End Custom Macros

ALL : "$(OUTDIR)\GitterD.ext" "$(OUTDIR)\Raster.bsc"\
 "..\..\TRIAS\TRIAS32D\GitterD.ext"

CLEAN : 
	-@erase "$(INTDIR)\Gitter.obj"
	-@erase "$(INTDIR)\Gitter.sbr"
	-@erase "$(INTDIR)\GitterDlg_old.obj"
	-@erase "$(INTDIR)\GitterDlg_old.sbr"
	-@erase "$(INTDIR)\Raster.res"
	-@erase "$(INTDIR)\RASTERD.idb"
	-@erase "$(INTDIR)\RASTERD.pch"
	-@erase "$(INTDIR)\RASTERD.pdb"
	-@erase "$(INTDIR)\RASTERP.OBJ"
	-@erase "$(INTDIR)\RASTERP.SBR"
	-@erase "$(OUTDIR)\GitterD.exp"
	-@erase "$(OUTDIR)\GitterD.ext"
	-@erase "$(OUTDIR)\GitterD.ilk"
	-@erase "$(OUTDIR)\GitterD.lib"
	-@erase "$(OUTDIR)\Raster.bsc"
	-@erase "..\..\TRIAS\TRIAS32D\GitterD.ext"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

.\WinDebug\RASTER.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /I "..\z_hxx" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "DLL" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "MSCC8" /D "__CV__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "__ATL_11_USED__" /Fr /Fp"WinDebug/RASTERD.pch" /Yu"rasterp.hxx" /Fd"WinDebug/RASTERD.pdb" /c
CPP_PROJ=/nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /I "..\z_hxx" /D "_DEBUG" /D\
 "WIN32" /D "_WINDOWS" /D "STRICT" /D "DLL" /D "__XT" /D "__DEXPROCS" /D\
 "MSWIND" /D "MSCC8" /D "__CV__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D\
 "QI_EXCEPTION" /D "__ATL_11_USED__" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/RASTERD.pch"\
 /Yu"rasterp.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/RASTERD.pdb" /c 
CPP_OBJS=.\WinDebug/
CPP_SBRS=.\WinDebug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /i "..\z_hxx" /d "_DEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/Raster.res" /i "..\z_hxx" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Raster.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Gitter.sbr" \
	"$(INTDIR)\GitterDlg_old.sbr" \
	"$(INTDIR)\RASTERP.SBR"

"$(OUTDIR)\Raster.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 geometd.lib ixtatd42.lib stdcppd.lib tfrm32d.lib cont32d.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib triastld.lib /nologo /dll /pdb:"WinDebug/RASTERD.pdb" /debug /machine:I386 /out:"WinDebug\GitterD.ext" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=geometd.lib ixtatd42.lib stdcppd.lib tfrm32d.lib cont32d.lib\
 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib\
 shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib\
 triastld.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)/RASTERD.pdb" /debug\
 /machine:I386 /def:".\RASTER.DEF" /out:"$(OUTDIR)/GitterD.ext"\
 /implib:"$(OUTDIR)/GitterD.lib" /SUBSYSTEM:windows,4.0 
DEF_FILE= \
	".\RASTER.DEF"
LINK32_OBJS= \
	"$(INTDIR)\Gitter.obj" \
	"$(INTDIR)\GitterDlg_old.obj" \
	"$(INTDIR)\Raster.res" \
	"$(INTDIR)\RASTERP.OBJ"

"$(OUTDIR)\GitterD.ext" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying Target to Destination ...
TargetPath=.\WinDebug\GitterD.ext
TargetName=GitterD
InputPath=.\WinDebug\GitterD.ext
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

# Name "Raster - Win32 Release"
# Name "Raster - Win32 Debug"

!IF  "$(CFG)" == "Raster - Win32 Release"

!ELSEIF  "$(CFG)" == "Raster - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\RASTERP.CXX
DEP_CPP_RASTE=\
	"..\Z_HXX\ctfx.hxx"\
	"..\z_hxx\ctfxmfc.h"\
	"..\Z_hxx\errcodes.hxx"\
	"..\z_hxx\FormatString.hxx"\
	"..\z_hxx\geo_obj.hxx"\
	"..\z_hxx\geokonst.hxx"\
	"..\z_hxx\GeometrM.hxx"\
	"..\z_hxx\identlst.hxx"\
	"..\z_hxx\objgext.hxx"\
	".\GitterConfig.h"\
	".\RasterM.hxx"\
	".\RasterP.hxx"\
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
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
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
	

!IF  "$(CFG)" == "Raster - Win32 Release"

# ADD CPP /Yc"rasterp.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O2 /I "..\z_hxx" /D "NDEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "DLL" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D\
 "MSCC8" /D "__CV__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D\
 "QI_EXCEPTION" /D "__ATL_11_USED__" /Fp"$(INTDIR)/Raster.pch" /Yc"rasterp.hxx"\
 /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\RASTERP.OBJ" : $(SOURCE) $(DEP_CPP_RASTE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Raster.pch" : $(SOURCE) $(DEP_CPP_RASTE) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Raster - Win32 Debug"

# ADD CPP /Yc"rasterp.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /I "..\z_hxx" /D "_DEBUG" /D\
 "WIN32" /D "_WINDOWS" /D "STRICT" /D "DLL" /D "__XT" /D "__DEXPROCS" /D\
 "MSWIND" /D "MSCC8" /D "__CV__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D\
 "QI_EXCEPTION" /D "__ATL_11_USED__" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/RASTERD.pch"\
 /Yc"rasterp.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/RASTERD.pdb" /c $(SOURCE) \
	

"$(INTDIR)\RASTERP.OBJ" : $(SOURCE) $(DEP_CPP_RASTE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\RASTERP.SBR" : $(SOURCE) $(DEP_CPP_RASTE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\RASTERD.pch" : $(SOURCE) $(DEP_CPP_RASTE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\RASTER.DEF

!IF  "$(CFG)" == "Raster - Win32 Release"

!ELSEIF  "$(CFG)" == "Raster - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Raster.rc
DEP_RSC_RASTER=\
	".\..\..\..\Triasdev.Mvc\INCLUDE\RESSTRG.H"\
	".\raster.rcv"\
	

"$(INTDIR)\Raster.res" : $(SOURCE) $(DEP_RSC_RASTER) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\GitterDlg_old.cxx

!IF  "$(CFG)" == "Raster - Win32 Release"

DEP_CPP_GITTE=\
	"..\z_hxx\datbank.hxx"\
	"..\z_hxx\koord.hxx"\
	".\GitterConfig.h"\
	".\GitterDlg_old.hxx"\
	".\RasterP.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\TSTRING"\
	

"$(INTDIR)\GitterDlg_old.obj" : $(SOURCE) $(DEP_CPP_GITTE) "$(INTDIR)"\
 "$(INTDIR)\Raster.pch"


!ELSEIF  "$(CFG)" == "Raster - Win32 Debug"

DEP_CPP_GITTE=\
	"..\z_hxx\datbank.hxx"\
	"..\z_hxx\koord.hxx"\
	".\GitterConfig.h"\
	".\GitterDlg_old.hxx"\
	".\RasterP.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	

"$(INTDIR)\GitterDlg_old.obj" : $(SOURCE) $(DEP_CPP_GITTE) "$(INTDIR)"\
 "$(INTDIR)\RASTERD.pch"

"$(INTDIR)\GitterDlg_old.sbr" : $(SOURCE) $(DEP_CPP_GITTE) "$(INTDIR)"\
 "$(INTDIR)\RASTERD.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Gitter.cxx

!IF  "$(CFG)" == "Raster - Win32 Release"

DEP_CPP_GITTER=\
	"..\z_hxx\datbank.hxx"\
	"..\z_hxx\GeomDLL.hxx"\
	"..\z_hxx\geotrias.hxx"\
	"..\z_hxx\koord.hxx"\
	"..\z_hxx\PopupMenu.hxx"\
	"..\z_hxx\ProgressProxy.h"\
	"..\z_hxx\progstat.h"\
	"..\z_hxx\reinguid.h"\
	".\..\..\..\Triasdev.Mvc\INCLUDE\RESSTRG.H"\
	".\Gitter.hxx"\
	".\GitterConfig.h"\
	".\GitterDlg_old.hxx"\
	".\RasterP.hxx"\
	".\RASTGUID.H"\
	".\SmartInterfaces.h"\
	".\version.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\Exceptio.hpp"\
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
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\YXVALS.H"\
	

"$(INTDIR)\Gitter.obj" : $(SOURCE) $(DEP_CPP_GITTER) "$(INTDIR)"\
 "$(INTDIR)\Raster.pch"


!ELSEIF  "$(CFG)" == "Raster - Win32 Debug"

DEP_CPP_GITTER=\
	"..\z_hxx\datbank.hxx"\
	"..\z_hxx\GeomDLL.hxx"\
	"..\z_hxx\geotrias.hxx"\
	"..\z_hxx\koord.hxx"\
	"..\z_hxx\PopupMenu.hxx"\
	".\..\..\..\Triasdev.Mvc\INCLUDE\RESSTRG.H"\
	".\Gitter.hxx"\
	".\GitterConfig.h"\
	".\GitterDlg_old.hxx"\
	".\RasterP.hxx"\
	".\RASTGUID.H"\
	".\version.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\TSTRING"\
	

"$(INTDIR)\Gitter.obj" : $(SOURCE) $(DEP_CPP_GITTER) "$(INTDIR)"\
 "$(INTDIR)\RASTERD.pch"

"$(INTDIR)\Gitter.sbr" : $(SOURCE) $(DEP_CPP_GITTER) "$(INTDIR)"\
 "$(INTDIR)\RASTERD.pch"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
