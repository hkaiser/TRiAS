# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=Geoedit - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Geoedit - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Geoedit - Win32 Release" && "$(CFG)" !=\
 "Geoedit - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Geoedit.mak" CFG="Geoedit - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Geoedit - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Geoedit - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "Geoedit - Win32 Debug"
RSC=rc.exe
CPP=cl.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "Geoedit - Win32 Release"

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
TargetName=geoedit
# End Custom Macros

ALL : "$(OUTDIR)\geoedit.ext" "..\..\TRIAS\TRIAS32R\geoedit.ext"

CLEAN : 
	-@erase "$(INTDIR)\Ddgeoobj.obj"
	-@erase "$(INTDIR)\DRAGLINE.OBJ"
	-@erase "$(INTDIR)\GEOEDIT.OBJ"
	-@erase "$(INTDIR)\Geoedit.pch"
	-@erase "$(INTDIR)\Geoedit.res"
	-@erase "$(INTDIR)\GEOEDITP.OBJ"
	-@erase "$(INTDIR)\GEOMODIF.OBJ"
	-@erase "$(INTDIR)\GEOMTREE.OBJ"
	-@erase "$(INTDIR)\KREIS.OBJ"
	-@erase "$(INTDIR)\MARKER.OBJ"
	-@erase "$(INTDIR)\MODMENUE.OBJ"
	-@erase "$(INTDIR)\NEU_EIN.OBJ"
	-@erase "$(INTDIR)\SPMODDLG.OBJ"
	-@erase "$(INTDIR)\Toolbttn.obj"
	-@erase "$(OUTDIR)\geoedit.exp"
	-@erase "$(OUTDIR)\geoedit.ext"
	-@erase "$(OUTDIR)\geoedit.lib"
	-@erase "..\..\TRIAS\TRIAS32R\geoedit.ext"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(OUTDIR)/GEOEDIT.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /O2 /Ob0 /I "..\z_hxx" /D "NDEBUG" /D "__ATL_USED__" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "DLL" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "MSCC8" /D "__CV__" /D "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /Yu"geoeditp.hxx" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W3 /WX /GX /O2 /Ob0 /I "..\z_hxx" /D "NDEBUG" /D\
 "__ATL_USED__" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "DLL" /D\
 "__XT" /D "__DEXPROCS" /D "MSWIND" /D "MSCC8" /D "__CV__" /D\
 "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /Fp"$(INTDIR)/Geoedit.pch"\
 /Yu"geoeditp.hxx" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\WinRel/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /i "..\z_hxx" /d "NDEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/Geoedit.res" /i "..\z_hxx" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Geoedit.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 geometr.lib ixtatr42.lib stdcppr.lib tfrmwork.lib cont32r.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /nodefaultlib:"libcmtd.lib" /out:"WinRel/geoedit.ext" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none /nodefaultlib
LINK32_FLAGS=geometr.lib ixtatr42.lib stdcppr.lib tfrmwork.lib cont32r.lib\
 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib\
 shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo\
 /dll /incremental:no /pdb:"$(OUTDIR)/geoedit.pdb" /machine:I386\
 /nodefaultlib:"libcmtd.lib" /def:".\Win32\Geoedit.def"\
 /out:"$(OUTDIR)/geoedit.ext" /implib:"$(OUTDIR)/geoedit.lib"\
 /SUBSYSTEM:windows,4.0 
DEF_FILE= \
	".\Win32\Geoedit.def"
LINK32_OBJS= \
	"$(INTDIR)\Ddgeoobj.obj" \
	"$(INTDIR)\DRAGLINE.OBJ" \
	"$(INTDIR)\GEOEDIT.OBJ" \
	"$(INTDIR)\Geoedit.res" \
	"$(INTDIR)\GEOEDITP.OBJ" \
	"$(INTDIR)\GEOMODIF.OBJ" \
	"$(INTDIR)\GEOMTREE.OBJ" \
	"$(INTDIR)\KREIS.OBJ" \
	"$(INTDIR)\MARKER.OBJ" \
	"$(INTDIR)\MODMENUE.OBJ" \
	"$(INTDIR)\NEU_EIN.OBJ" \
	"$(INTDIR)\SPMODDLG.OBJ" \
	"$(INTDIR)\Toolbttn.obj"

"$(OUTDIR)\geoedit.ext" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying Target to Destination ...
TargetPath=.\WinRel\geoedit.ext
TargetName=geoedit
InputPath=.\WinRel\geoedit.ext
SOURCE=$(InputPath)

"C:\TRIAS\TRIAS32R\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   copy "$(TargetPath)" C:\TRIAS\TRIAS32R

# End Custom Build

!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"

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
TargetName=geoeditd
# End Custom Macros

ALL : "$(OUTDIR)\geoeditd.ext" "$(OUTDIR)\Geoedit.bsc"\
 "..\..\TRIAS\TRIAS32D\geoeditd.ext"

CLEAN : 
	-@erase "$(INTDIR)\Ddgeoobj.obj"
	-@erase "$(INTDIR)\Ddgeoobj.sbr"
	-@erase "$(INTDIR)\DRAGLINE.OBJ"
	-@erase "$(INTDIR)\DRAGLINE.SBR"
	-@erase "$(INTDIR)\GEOEDIT.OBJ"
	-@erase "$(INTDIR)\Geoedit.res"
	-@erase "$(INTDIR)\GEOEDIT.SBR"
	-@erase "$(INTDIR)\GEOEDITD.idb"
	-@erase "$(INTDIR)\GEOEDITD.pch"
	-@erase "$(INTDIR)\GEOEDITD.pdb"
	-@erase "$(INTDIR)\GEOEDITP.OBJ"
	-@erase "$(INTDIR)\GEOEDITP.SBR"
	-@erase "$(INTDIR)\GEOMODIF.OBJ"
	-@erase "$(INTDIR)\GEOMODIF.SBR"
	-@erase "$(INTDIR)\GEOMTREE.OBJ"
	-@erase "$(INTDIR)\GEOMTREE.SBR"
	-@erase "$(INTDIR)\KREIS.OBJ"
	-@erase "$(INTDIR)\KREIS.SBR"
	-@erase "$(INTDIR)\MARKER.OBJ"
	-@erase "$(INTDIR)\MARKER.SBR"
	-@erase "$(INTDIR)\MODMENUE.OBJ"
	-@erase "$(INTDIR)\MODMENUE.SBR"
	-@erase "$(INTDIR)\NEU_EIN.OBJ"
	-@erase "$(INTDIR)\NEU_EIN.SBR"
	-@erase "$(INTDIR)\SPMODDLG.OBJ"
	-@erase "$(INTDIR)\SPMODDLG.SBR"
	-@erase "$(INTDIR)\Toolbttn.obj"
	-@erase "$(INTDIR)\Toolbttn.sbr"
	-@erase "$(OUTDIR)\Geoedit.bsc"
	-@erase "$(OUTDIR)\geoeditd.exp"
	-@erase "$(OUTDIR)\geoeditd.ext"
	-@erase "$(OUTDIR)\geoeditd.ilk"
	-@erase "$(OUTDIR)\geoeditd.lib"
	-@erase "..\..\TRIAS\TRIAS32D\geoeditd.ext"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(OUTDIR)/GEOEDIT.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /I "..\z_hxx" /D "_DEBUG" /D "__ATL_USED__" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "DLL" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "MSCC8" /D "__CV__" /D "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "_DRAGDROP" /Fr /Fp"WinDebug/GEOEDITD.pch" /Yu"geoeditp.hxx" /Fd"WinDebug/GEOEDITD.pdb" /c
CPP_PROJ=/nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /I "..\z_hxx" /D "_DEBUG" /D\
 "__ATL_USED__" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "DLL" /D\
 "__XT" /D "__DEXPROCS" /D "MSWIND" /D "MSCC8" /D "__CV__" /D\
 "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "_DRAGDROP" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/GEOEDITD.pch" /Yu"geoeditp.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/GEOEDITD.pdb" /c 
CPP_OBJS=.\WinDebug/
CPP_SBRS=.\WinDebug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /i "..\z_hxx" /d "_DEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/Geoedit.res" /i "..\z_hxx" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Geoedit.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Ddgeoobj.sbr" \
	"$(INTDIR)\DRAGLINE.SBR" \
	"$(INTDIR)\GEOEDIT.SBR" \
	"$(INTDIR)\GEOEDITP.SBR" \
	"$(INTDIR)\GEOMODIF.SBR" \
	"$(INTDIR)\GEOMTREE.SBR" \
	"$(INTDIR)\KREIS.SBR" \
	"$(INTDIR)\MARKER.SBR" \
	"$(INTDIR)\MODMENUE.SBR" \
	"$(INTDIR)\NEU_EIN.SBR" \
	"$(INTDIR)\SPMODDLG.SBR" \
	"$(INTDIR)\Toolbttn.sbr"

"$(OUTDIR)\Geoedit.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 geometd.lib ixtatd42.lib stdcppd.lib tfrm32d.lib cont32d.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /nodefaultlib:"libcmtd.lib" /out:"WinDebug/geoeditd.ext" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /profile /nodefaultlib
LINK32_FLAGS=geometd.lib ixtatd42.lib stdcppd.lib tfrm32d.lib cont32d.lib\
 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib\
 shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo\
 /dll /incremental:yes /pdb:"$(OUTDIR)/geoeditd.pdb" /debug /machine:I386\
 /nodefaultlib:"libcmtd.lib" /def:".\Win32\Geoedit.def"\
 /out:"$(OUTDIR)/geoeditd.ext" /implib:"$(OUTDIR)/geoeditd.lib"\
 /SUBSYSTEM:windows,4.0 
DEF_FILE= \
	".\Win32\Geoedit.def"
LINK32_OBJS= \
	"$(INTDIR)\Ddgeoobj.obj" \
	"$(INTDIR)\DRAGLINE.OBJ" \
	"$(INTDIR)\GEOEDIT.OBJ" \
	"$(INTDIR)\Geoedit.res" \
	"$(INTDIR)\GEOEDITP.OBJ" \
	"$(INTDIR)\GEOMODIF.OBJ" \
	"$(INTDIR)\GEOMTREE.OBJ" \
	"$(INTDIR)\KREIS.OBJ" \
	"$(INTDIR)\MARKER.OBJ" \
	"$(INTDIR)\MODMENUE.OBJ" \
	"$(INTDIR)\NEU_EIN.OBJ" \
	"$(INTDIR)\SPMODDLG.OBJ" \
	"$(INTDIR)\Toolbttn.obj"

"$(OUTDIR)\geoeditd.ext" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying Target to Destination ...
TargetPath=.\WinDebug\geoeditd.ext
TargetName=geoeditd
InputPath=.\WinDebug\geoeditd.ext
SOURCE=$(InputPath)

"C:\TRIAS\TRIAS32D\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   copy "$(TargetPath)" C:\TRIAS\TRIAS32D

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

# Name "Geoedit - Win32 Release"
# Name "Geoedit - Win32 Debug"

!IF  "$(CFG)" == "Geoedit - Win32 Release"

!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\MARKER.CXX
DEP_CPP_MARKE=\
	"..\z_hxx\ctfx.hxx"\
	"..\z_hxx\datbank.hxx"\
	"..\z_hxx\dragline.hxx"\
	"..\Z_hxx\Errcodes.hxx"\
	"..\z_hxx\geo_obj.hxx"\
	"..\z_hxx\geoedit.h"\
	"..\z_hxx\geokonst.hxx"\
	"..\z_hxx\geometrm.hxx"\
	"..\z_hxx\geotrias.hxx"\
	"..\z_hxx\identlst.hxx"\
	"..\z_hxx\igeometr.hxx"\
	"..\z_hxx\koord.hxx"\
	"..\z_hxx\objgext.hxx"\
	"..\z_hxx\zeichnen.hxx"\
	".\Ddgeoobj.hxx"\
	".\Edikonst.hxx"\
	".\Geoeditm.hxx"\
	".\Geoeditp.hxx"\
	".\Geomtree.hxx"\
	".\Marker.hxx"\
	".\Neu_ein.hxx"\
	{$(INCLUDE)}"\Atl11.h"\
	{$(INCLUDE)}"\Atlbase.h"\
	{$(INCLUDE)}"\Atlcom.h"\
	{$(INCLUDE)}"\Atlcomx.h"\
	{$(INCLUDE)}"\Atlutil.h"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Copttree.hxx"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\Dblpair.hxx"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\Drawobj.hxx"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Funcs03.h"\
	{$(INCLUDE)}"\Geo_inl.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\Justify.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\ospace\Com\Smartif.h"\
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
	{$(INCLUDE)}"\Registrx.hxx"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Rotate.hxx"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\Yxvals.h"\
	

!IF  "$(CFG)" == "Geoedit - Win32 Release"


"$(INTDIR)\MARKER.OBJ" : $(SOURCE) $(DEP_CPP_MARKE) "$(INTDIR)"\
 "$(INTDIR)\Geoedit.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /Ob0 /I "..\z_hxx" /D "NDEBUG" /D\
 "__ATL_USED__" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "DLL" /D\
 "__XT" /D "__DEXPROCS" /D "MSWIND" /D "MSCC8" /D "__CV__" /D\
 "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /Fp"$(INTDIR)/Geoedit.pch"\
 /Yu"geoeditp.hxx" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"

# ADD CPP /Yu"geoeditp.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /I "..\z_hxx" /D "_DEBUG" /D\
 "__ATL_USED__" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "DLL" /D\
 "__XT" /D "__DEXPROCS" /D "MSWIND" /D "MSCC8" /D "__CV__" /D\
 "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "_DRAGDROP" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/GEOEDITD.pch" /Yu"geoeditp.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/GEOEDITD.pdb" /c $(SOURCE) \
	

"$(INTDIR)\MARKER.OBJ" : $(SOURCE) $(DEP_CPP_MARKE) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch"
   $(BuildCmds)

"$(INTDIR)\MARKER.SBR" : $(SOURCE) $(DEP_CPP_MARKE) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GEOMODIF.CXX
DEP_CPP_GEOMO=\
	"..\z_hxx\ctfx.hxx"\
	"..\z_hxx\datbank.hxx"\
	"..\z_hxx\dragline.hxx"\
	"..\Z_hxx\Errcodes.hxx"\
	"..\z_hxx\geo_obj.hxx"\
	"..\z_hxx\geoedit.h"\
	"..\z_hxx\geokonst.hxx"\
	"..\z_hxx\geometrm.hxx"\
	"..\z_hxx\geotrias.hxx"\
	"..\z_hxx\identlst.hxx"\
	"..\z_hxx\igeometr.hxx"\
	"..\z_hxx\koord.hxx"\
	"..\z_hxx\objgext.hxx"\
	"..\z_hxx\operguid.h"\
	"..\z_hxx\ProgressProxy.h"\
	"..\z_hxx\progstat.h"\
	"..\z_hxx\reinguid.h"\
	"..\z_hxx\strecke.hxx"\
	"..\z_hxx\zeichnen.hxx"\
	".\Ddgeoobj.hxx"\
	".\Edikonst.hxx"\
	".\Geoedit.hxx"\
	".\Geoeditm.hxx"\
	".\Geoeditp.hxx"\
	".\Geoeditr.h"\
	".\Geomtree.hxx"\
	".\Marker.hxx"\
	".\Neu_ein.hxx"\
	".\SmartInterfaces.h"\
	".\Spmoddlg.hxx"\
	{$(INCLUDE)}"\Atl11.h"\
	{$(INCLUDE)}"\Atlbase.h"\
	{$(INCLUDE)}"\Atlcom.h"\
	{$(INCLUDE)}"\Atlcomx.h"\
	{$(INCLUDE)}"\Atlutil.h"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Copttree.hxx"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\Dblpair.hxx"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\Drawobj.hxx"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Funcs03.h"\
	{$(INCLUDE)}"\Geo_inl.hxx"\
	{$(INCLUDE)}"\Hdrentrx.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\Justify.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\ospace\Com\Smartif.h"\
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
	{$(INCLUDE)}"\Registrx.hxx"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Rotate.hxx"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\Yxvals.h"\
	

!IF  "$(CFG)" == "Geoedit - Win32 Release"


"$(INTDIR)\GEOMODIF.OBJ" : $(SOURCE) $(DEP_CPP_GEOMO) "$(INTDIR)"\
 "$(INTDIR)\Geoedit.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /Ob0 /I "..\z_hxx" /D "NDEBUG" /D\
 "__ATL_USED__" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "DLL" /D\
 "__XT" /D "__DEXPROCS" /D "MSWIND" /D "MSCC8" /D "__CV__" /D\
 "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /Fp"$(INTDIR)/Geoedit.pch"\
 /Yu"geoeditp.hxx" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"

# ADD CPP /Yu"geoeditp.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /I "..\z_hxx" /D "_DEBUG" /D\
 "__ATL_USED__" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "DLL" /D\
 "__XT" /D "__DEXPROCS" /D "MSWIND" /D "MSCC8" /D "__CV__" /D\
 "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "_DRAGDROP" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/GEOEDITD.pch" /Yu"geoeditp.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/GEOEDITD.pdb" /c $(SOURCE) \
	

"$(INTDIR)\GEOMODIF.OBJ" : $(SOURCE) $(DEP_CPP_GEOMO) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch"
   $(BuildCmds)

"$(INTDIR)\GEOMODIF.SBR" : $(SOURCE) $(DEP_CPP_GEOMO) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DRAGLINE.CXX
DEP_CPP_DRAGL=\
	"..\z_hxx\ctfx.hxx"\
	"..\z_hxx\datbank.hxx"\
	"..\z_hxx\dragline.hxx"\
	"..\Z_hxx\Errcodes.hxx"\
	"..\z_hxx\geo_obj.hxx"\
	"..\z_hxx\geoedit.h"\
	"..\z_hxx\geokonst.hxx"\
	"..\z_hxx\geometrm.hxx"\
	"..\z_hxx\geotrias.hxx"\
	"..\z_hxx\identlst.hxx"\
	"..\z_hxx\igeometr.hxx"\
	"..\z_hxx\koord.hxx"\
	"..\z_hxx\objgext.hxx"\
	"..\z_hxx\ProgressProxy.h"\
	"..\z_hxx\progstat.h"\
	"..\z_hxx\zeichnen.hxx"\
	".\Ddgeoobj.hxx"\
	".\Edikonst.hxx"\
	".\Editguid.h"\
	".\Geoedit.hxx"\
	".\Geoeditm.hxx"\
	".\Geoeditp.hxx"\
	".\Geomtree.hxx"\
	".\Marker.hxx"\
	".\Neu_ein.hxx"\
	".\SmartInterfaces.h"\
	{$(INCLUDE)}"\Atl11.h"\
	{$(INCLUDE)}"\Atlbase.h"\
	{$(INCLUDE)}"\Atlcom.h"\
	{$(INCLUDE)}"\Atlcomx.h"\
	{$(INCLUDE)}"\Atlutil.h"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Copttree.hxx"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\Dblpair.hxx"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\Drawobj.hxx"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Funcs03.h"\
	{$(INCLUDE)}"\Geo_inl.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\Justify.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\ospace\Com\Smartif.h"\
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
	{$(INCLUDE)}"\Registrx.hxx"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Rotate.hxx"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\Yxvals.h"\
	

!IF  "$(CFG)" == "Geoedit - Win32 Release"


"$(INTDIR)\DRAGLINE.OBJ" : $(SOURCE) $(DEP_CPP_DRAGL) "$(INTDIR)"\
 "$(INTDIR)\Geoedit.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /Ob0 /I "..\z_hxx" /D "NDEBUG" /D\
 "__ATL_USED__" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "DLL" /D\
 "__XT" /D "__DEXPROCS" /D "MSWIND" /D "MSCC8" /D "__CV__" /D\
 "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /Fp"$(INTDIR)/Geoedit.pch"\
 /Yu"geoeditp.hxx" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"

# ADD CPP /Yu"geoeditp.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /I "..\z_hxx" /D "_DEBUG" /D\
 "__ATL_USED__" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "DLL" /D\
 "__XT" /D "__DEXPROCS" /D "MSWIND" /D "MSCC8" /D "__CV__" /D\
 "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "_DRAGDROP" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/GEOEDITD.pch" /Yu"geoeditp.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/GEOEDITD.pdb" /c $(SOURCE) \
	

"$(INTDIR)\DRAGLINE.OBJ" : $(SOURCE) $(DEP_CPP_DRAGL) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch"
   $(BuildCmds)

"$(INTDIR)\DRAGLINE.SBR" : $(SOURCE) $(DEP_CPP_DRAGL) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\NEU_EIN.CXX
DEP_CPP_NEU_E=\
	"..\z_hxx\ctfx.hxx"\
	"..\z_hxx\datbank.hxx"\
	"..\z_hxx\dragline.hxx"\
	"..\Z_hxx\Errcodes.hxx"\
	"..\z_hxx\geo_obj.hxx"\
	"..\z_hxx\geoedit.h"\
	"..\z_hxx\geokonst.hxx"\
	"..\z_hxx\geometrm.hxx"\
	"..\z_hxx\geotrias.hxx"\
	"..\z_hxx\identlst.hxx"\
	"..\z_hxx\igeometr.hxx"\
	"..\z_hxx\koord.hxx"\
	"..\z_hxx\objgext.hxx"\
	"..\z_hxx\zeichnen.hxx"\
	".\Ddgeoobj.hxx"\
	".\Edikonst.hxx"\
	".\Geoeditm.hxx"\
	".\Geoeditp.hxx"\
	".\Geomtree.hxx"\
	".\Kreis.hxx"\
	".\Marker.hxx"\
	".\Neu_ein.hxx"\
	{$(INCLUDE)}"\Atl11.h"\
	{$(INCLUDE)}"\Atlbase.h"\
	{$(INCLUDE)}"\Atlcom.h"\
	{$(INCLUDE)}"\Atlcomx.h"\
	{$(INCLUDE)}"\Atlutil.h"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Copttree.hxx"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\Dblpair.hxx"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\Drawobj.hxx"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Funcs03.h"\
	{$(INCLUDE)}"\Geo_inl.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\Justify.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\ospace\Com\Smartif.h"\
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
	{$(INCLUDE)}"\Registrx.hxx"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Rotate.hxx"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\Yxvals.h"\
	

!IF  "$(CFG)" == "Geoedit - Win32 Release"


"$(INTDIR)\NEU_EIN.OBJ" : $(SOURCE) $(DEP_CPP_NEU_E) "$(INTDIR)"\
 "$(INTDIR)\Geoedit.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /Ob0 /I "..\z_hxx" /D "NDEBUG" /D\
 "__ATL_USED__" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "DLL" /D\
 "__XT" /D "__DEXPROCS" /D "MSWIND" /D "MSCC8" /D "__CV__" /D\
 "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /Fp"$(INTDIR)/Geoedit.pch"\
 /Yu"geoeditp.hxx" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"

# ADD CPP /Yu"geoeditp.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /I "..\z_hxx" /D "_DEBUG" /D\
 "__ATL_USED__" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "DLL" /D\
 "__XT" /D "__DEXPROCS" /D "MSWIND" /D "MSCC8" /D "__CV__" /D\
 "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "_DRAGDROP" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/GEOEDITD.pch" /Yu"geoeditp.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/GEOEDITD.pdb" /c $(SOURCE) \
	

"$(INTDIR)\NEU_EIN.OBJ" : $(SOURCE) $(DEP_CPP_NEU_E) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch"
   $(BuildCmds)

"$(INTDIR)\NEU_EIN.SBR" : $(SOURCE) $(DEP_CPP_NEU_E) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\KREIS.CXX
DEP_CPP_KREIS=\
	"..\z_hxx\ctfx.hxx"\
	"..\z_hxx\datbank.hxx"\
	"..\z_hxx\dragline.hxx"\
	"..\Z_hxx\Errcodes.hxx"\
	"..\z_hxx\geo_obj.hxx"\
	"..\z_hxx\geoedit.h"\
	"..\z_hxx\geokonst.hxx"\
	"..\z_hxx\geometrm.hxx"\
	"..\z_hxx\geotrias.hxx"\
	"..\z_hxx\identlst.hxx"\
	"..\z_hxx\igeometr.hxx"\
	"..\z_hxx\koord.hxx"\
	"..\z_hxx\objgext.hxx"\
	"..\z_hxx\zeichnen.hxx"\
	".\Ddgeoobj.hxx"\
	".\Edikonst.hxx"\
	".\Geoeditm.hxx"\
	".\Geoeditp.hxx"\
	".\Geomtree.hxx"\
	".\Marker.hxx"\
	".\Neu_ein.hxx"\
	{$(INCLUDE)}"\Atl11.h"\
	{$(INCLUDE)}"\Atlbase.h"\
	{$(INCLUDE)}"\Atlcom.h"\
	{$(INCLUDE)}"\Atlcomx.h"\
	{$(INCLUDE)}"\Atlutil.h"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Copttree.hxx"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\Dblpair.hxx"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\Drawobj.hxx"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Funcs03.h"\
	{$(INCLUDE)}"\Geo_inl.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\Justify.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\ospace\Com\Smartif.h"\
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
	{$(INCLUDE)}"\Registrx.hxx"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Rotate.hxx"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\Yxvals.h"\
	

!IF  "$(CFG)" == "Geoedit - Win32 Release"


"$(INTDIR)\KREIS.OBJ" : $(SOURCE) $(DEP_CPP_KREIS) "$(INTDIR)"\
 "$(INTDIR)\Geoedit.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /Ob0 /I "..\z_hxx" /D "NDEBUG" /D\
 "__ATL_USED__" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "DLL" /D\
 "__XT" /D "__DEXPROCS" /D "MSWIND" /D "MSCC8" /D "__CV__" /D\
 "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /Fp"$(INTDIR)/Geoedit.pch"\
 /Yu"geoeditp.hxx" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"

# ADD CPP /Yu"geoeditp.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /I "..\z_hxx" /D "_DEBUG" /D\
 "__ATL_USED__" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "DLL" /D\
 "__XT" /D "__DEXPROCS" /D "MSWIND" /D "MSCC8" /D "__CV__" /D\
 "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "_DRAGDROP" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/GEOEDITD.pch" /Yu"geoeditp.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/GEOEDITD.pdb" /c $(SOURCE) \
	

"$(INTDIR)\KREIS.OBJ" : $(SOURCE) $(DEP_CPP_KREIS) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch"
   $(BuildCmds)

"$(INTDIR)\KREIS.SBR" : $(SOURCE) $(DEP_CPP_KREIS) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GEOEDIT.CXX

!IF  "$(CFG)" == "Geoedit - Win32 Release"

DEP_CPP_GEOED=\
	"..\z_hxx\geomdll.hxx"\
	"..\z_hxx\geometrm.hxx"\
	"..\z_hxx\ProgressProxy.h"\
	"..\z_hxx\progstat.h"\
	"..\z_hxx\uiowner.h"\
	".\Editguid.h"\
	".\Geoedit.hxx"\
	".\Geoeditm.hxx"\
	".\Geoeditp.hxx"\
	".\Geoeditr.h"\
	".\SmartInterfaces.h"\
	".\Versio16.h"\
	".\Version.h"\
	".\Win32\Versio32.h"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\Itoolbar.h"\
	{$(INCLUDE)}"\iunredo.hxx"\
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
	{$(INCLUDE)}"\Resstrg.h"\
	{$(INCLUDE)}"\toolguid.h"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TRiASHelper_i.c"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\Undoguid.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\Yxvals.h"\
	

"$(INTDIR)\GEOEDIT.OBJ" : $(SOURCE) $(DEP_CPP_GEOED) "$(INTDIR)"\
 "$(INTDIR)\Geoedit.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /Ob0 /I "..\z_hxx" /D "NDEBUG" /D\
 "__ATL_USED__" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "DLL" /D\
 "__XT" /D "__DEXPROCS" /D "MSWIND" /D "MSCC8" /D "__CV__" /D\
 "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /Fp"$(INTDIR)/Geoedit.pch"\
 /Yu"geoeditp.hxx" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"

DEP_CPP_GEOED=\
	"..\z_hxx\geomdll.hxx"\
	"..\z_hxx\geometrm.hxx"\
	"..\z_hxx\ProgressProxy.h"\
	"..\z_hxx\progstat.h"\
	"..\z_hxx\uiowner.h"\
	".\Editguid.h"\
	".\Geoedit.hxx"\
	".\Geoeditm.hxx"\
	".\Geoeditp.hxx"\
	".\Geoeditr.h"\
	".\SmartInterfaces.h"\
	".\Versio16.h"\
	".\Version.h"\
	".\Win32\Versio32.h"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Itoolbar.h"\
	{$(INCLUDE)}"\iunredo.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\Resstrg.h"\
	{$(INCLUDE)}"\toolguid.h"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TRiASHelper_i.c"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Undoguid.h"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\xtsnguid.h"\
	
# ADD CPP /Yu"geoeditp.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /I "..\z_hxx" /D "_DEBUG" /D\
 "__ATL_USED__" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "DLL" /D\
 "__XT" /D "__DEXPROCS" /D "MSWIND" /D "MSCC8" /D "__CV__" /D\
 "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "_DRAGDROP" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/GEOEDITD.pch" /Yu"geoeditp.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/GEOEDITD.pdb" /c $(SOURCE) \
	

"$(INTDIR)\GEOEDIT.OBJ" : $(SOURCE) $(DEP_CPP_GEOED) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch"
   $(BuildCmds)

"$(INTDIR)\GEOEDIT.SBR" : $(SOURCE) $(DEP_CPP_GEOED) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GEOEDITP.CXX
DEP_CPP_GEOEDI=\
	"..\z_hxx\ctfx.hxx"\
	"..\z_hxx\datbank.hxx"\
	"..\z_hxx\dragline.hxx"\
	"..\Z_hxx\Errcodes.hxx"\
	"..\z_hxx\geo_obj.hxx"\
	"..\z_hxx\geoedit.h"\
	"..\z_hxx\geokonst.hxx"\
	"..\z_hxx\geometrm.hxx"\
	"..\z_hxx\geotrias.hxx"\
	"..\z_hxx\identlst.hxx"\
	"..\z_hxx\igeometr.hxx"\
	"..\z_hxx\koord.hxx"\
	"..\z_hxx\objgext.hxx"\
	"..\z_hxx\zeichnen.hxx"\
	".\Ddgeoobj.hxx"\
	".\Edikonst.hxx"\
	".\Geoeditm.hxx"\
	".\Geoeditp.hxx"\
	".\Geomtree.hxx"\
	".\Marker.hxx"\
	".\Neu_ein.hxx"\
	{$(INCLUDE)}"\Atl11.h"\
	{$(INCLUDE)}"\Atlbase.h"\
	{$(INCLUDE)}"\Atlcom.h"\
	{$(INCLUDE)}"\Atlcomx.h"\
	{$(INCLUDE)}"\Atlimpl.cpp"\
	{$(INCLUDE)}"\Atlimpl11.h"\
	{$(INCLUDE)}"\Atlutil.h"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Copttree.hxx"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\Dblpair.hxx"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\Drawobj.hxx"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Funcs03.h"\
	{$(INCLUDE)}"\Geo_inl.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\Justify.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\ospace\Com\Smartif.h"\
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
	{$(INCLUDE)}"\Registrx.hxx"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Rotate.hxx"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\Yxvals.h"\
	

!IF  "$(CFG)" == "Geoedit - Win32 Release"

# ADD CPP /Yc"geoeditp.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O2 /Ob0 /I "..\z_hxx" /D "NDEBUG" /D\
 "__ATL_USED__" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "DLL" /D\
 "__XT" /D "__DEXPROCS" /D "MSWIND" /D "MSCC8" /D "__CV__" /D\
 "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /Fp"$(INTDIR)/Geoedit.pch"\
 /Yc"geoeditp.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\GEOEDITP.OBJ" : $(SOURCE) $(DEP_CPP_GEOEDI) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Geoedit.pch" : $(SOURCE) $(DEP_CPP_GEOEDI) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"

# ADD CPP /Yc"geoeditp.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /I "..\z_hxx" /D "_DEBUG" /D\
 "__ATL_USED__" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "DLL" /D\
 "__XT" /D "__DEXPROCS" /D "MSWIND" /D "MSCC8" /D "__CV__" /D\
 "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "_DRAGDROP" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/GEOEDITD.pch" /Yc"geoeditp.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/GEOEDITD.pdb" /c $(SOURCE) \
	

"$(INTDIR)\GEOEDITP.OBJ" : $(SOURCE) $(DEP_CPP_GEOEDI) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\GEOEDITP.SBR" : $(SOURCE) $(DEP_CPP_GEOEDI) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\GEOEDITD.pch" : $(SOURCE) $(DEP_CPP_GEOEDI) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GEOMTREE.CXX
DEP_CPP_GEOMT=\
	"..\z_hxx\ctfx.hxx"\
	"..\z_hxx\datbank.hxx"\
	"..\z_hxx\dragline.hxx"\
	"..\Z_hxx\Errcodes.hxx"\
	"..\z_hxx\geo_obj.hxx"\
	"..\z_hxx\geoedit.h"\
	"..\z_hxx\geokonst.hxx"\
	"..\z_hxx\geometrm.hxx"\
	"..\z_hxx\geotrias.hxx"\
	"..\z_hxx\identlst.hxx"\
	"..\z_hxx\igeometr.hxx"\
	"..\z_hxx\koord.hxx"\
	"..\z_hxx\objgext.hxx"\
	"..\z_hxx\zeichnen.hxx"\
	".\Ddgeoobj.hxx"\
	".\Edikonst.hxx"\
	".\Geoeditm.hxx"\
	".\Geoeditp.hxx"\
	".\Geomtree.hxx"\
	".\Marker.hxx"\
	".\Neu_ein.hxx"\
	{$(INCLUDE)}"\Atl11.h"\
	{$(INCLUDE)}"\Atlbase.h"\
	{$(INCLUDE)}"\Atlcom.h"\
	{$(INCLUDE)}"\Atlcomx.h"\
	{$(INCLUDE)}"\Atlutil.h"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Copttree.hxx"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\Dblpair.hxx"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\Drawobj.hxx"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Funcs03.h"\
	{$(INCLUDE)}"\Geo_inl.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\Justify.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\ospace\Com\Smartif.h"\
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
	{$(INCLUDE)}"\Registrx.hxx"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Rotate.hxx"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\Yxvals.h"\
	

!IF  "$(CFG)" == "Geoedit - Win32 Release"


"$(INTDIR)\GEOMTREE.OBJ" : $(SOURCE) $(DEP_CPP_GEOMT) "$(INTDIR)"\
 "$(INTDIR)\Geoedit.pch"


!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"


"$(INTDIR)\GEOMTREE.OBJ" : $(SOURCE) $(DEP_CPP_GEOMT) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch"

"$(INTDIR)\GEOMTREE.SBR" : $(SOURCE) $(DEP_CPP_GEOMT) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MODMENUE.CXX
DEP_CPP_MODME=\
	"..\z_hxx\ctfx.hxx"\
	"..\z_hxx\datbank.hxx"\
	"..\z_hxx\dragline.hxx"\
	"..\Z_hxx\Errcodes.hxx"\
	"..\z_hxx\geo_obj.hxx"\
	"..\z_hxx\geoedit.h"\
	"..\z_hxx\geokonst.hxx"\
	"..\z_hxx\geometrm.hxx"\
	"..\z_hxx\geotrias.hxx"\
	"..\z_hxx\identlst.hxx"\
	"..\z_hxx\igeometr.hxx"\
	"..\z_hxx\koord.hxx"\
	"..\z_hxx\objgext.hxx"\
	"..\z_hxx\ProgressProxy.h"\
	"..\z_hxx\progstat.h"\
	"..\z_hxx\zeichnen.hxx"\
	".\Ddgeoobj.hxx"\
	".\Edikonst.hxx"\
	".\Editguid.h"\
	".\Geoedit.hxx"\
	".\Geoeditm.hxx"\
	".\Geoeditp.hxx"\
	".\Geomtree.hxx"\
	".\Marker.hxx"\
	".\Neu_ein.hxx"\
	".\SmartInterfaces.h"\
	".\Spmoddlg.hxx"\
	{$(INCLUDE)}"\Atl11.h"\
	{$(INCLUDE)}"\Atlbase.h"\
	{$(INCLUDE)}"\Atlcom.h"\
	{$(INCLUDE)}"\Atlcomx.h"\
	{$(INCLUDE)}"\Atlutil.h"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Copttree.hxx"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\Dblpair.hxx"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\Drawobj.hxx"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Funcs03.h"\
	{$(INCLUDE)}"\Geo_inl.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\Justify.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\ospace\Com\Smartif.h"\
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
	{$(INCLUDE)}"\Registrx.hxx"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Rotate.hxx"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\Yxvals.h"\
	

!IF  "$(CFG)" == "Geoedit - Win32 Release"


"$(INTDIR)\MODMENUE.OBJ" : $(SOURCE) $(DEP_CPP_MODME) "$(INTDIR)"\
 "$(INTDIR)\Geoedit.pch"


!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"


"$(INTDIR)\MODMENUE.OBJ" : $(SOURCE) $(DEP_CPP_MODME) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch"

"$(INTDIR)\MODMENUE.SBR" : $(SOURCE) $(DEP_CPP_MODME) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SPMODDLG.CXX
DEP_CPP_SPMOD=\
	"..\z_hxx\ctfx.hxx"\
	"..\z_hxx\datbank.hxx"\
	"..\z_hxx\dragline.hxx"\
	"..\Z_hxx\Errcodes.hxx"\
	"..\z_hxx\geo_obj.hxx"\
	"..\z_hxx\geoedit.h"\
	"..\z_hxx\geokonst.hxx"\
	"..\z_hxx\geometrm.hxx"\
	"..\z_hxx\geotrias.hxx"\
	"..\z_hxx\identlst.hxx"\
	"..\z_hxx\igeometr.hxx"\
	"..\z_hxx\koord.hxx"\
	"..\z_hxx\objgext.hxx"\
	"..\z_hxx\zeichnen.hxx"\
	".\Ddgeoobj.hxx"\
	".\Edikonst.hxx"\
	".\Geoeditm.hxx"\
	".\Geoeditp.hxx"\
	".\Geomtree.hxx"\
	".\Marker.hxx"\
	".\Neu_ein.hxx"\
	".\Spmoddlg.hxx"\
	{$(INCLUDE)}"\Atl11.h"\
	{$(INCLUDE)}"\Atlbase.h"\
	{$(INCLUDE)}"\Atlcom.h"\
	{$(INCLUDE)}"\Atlcomx.h"\
	{$(INCLUDE)}"\Atlutil.h"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Copttree.hxx"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\Dblpair.hxx"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\Drawobj.hxx"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Funcs03.h"\
	{$(INCLUDE)}"\Geo_inl.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\Justify.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\ospace\Com\Smartif.h"\
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
	{$(INCLUDE)}"\Registrx.hxx"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Rotate.hxx"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\Yxvals.h"\
	

!IF  "$(CFG)" == "Geoedit - Win32 Release"


"$(INTDIR)\SPMODDLG.OBJ" : $(SOURCE) $(DEP_CPP_SPMOD) "$(INTDIR)"\
 "$(INTDIR)\Geoedit.pch"


!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"


"$(INTDIR)\SPMODDLG.OBJ" : $(SOURCE) $(DEP_CPP_SPMOD) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch"

"$(INTDIR)\SPMODDLG.SBR" : $(SOURCE) $(DEP_CPP_SPMOD) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Toolbttn.cxx
DEP_CPP_TOOLB=\
	"..\z_hxx\ctfx.hxx"\
	"..\z_hxx\datbank.hxx"\
	"..\z_hxx\dragline.hxx"\
	"..\Z_hxx\Errcodes.hxx"\
	"..\z_hxx\geo_obj.hxx"\
	"..\z_hxx\geoedit.h"\
	"..\z_hxx\geokonst.hxx"\
	"..\z_hxx\geometrm.hxx"\
	"..\z_hxx\geotrias.hxx"\
	"..\z_hxx\identlst.hxx"\
	"..\z_hxx\igeometr.hxx"\
	"..\z_hxx\koord.hxx"\
	"..\z_hxx\objgext.hxx"\
	"..\z_hxx\ProgressProxy.h"\
	"..\z_hxx\progstat.h"\
	"..\z_hxx\uiowner.h"\
	"..\z_hxx\zeichnen.hxx"\
	".\Ddgeoobj.hxx"\
	".\Edikonst.hxx"\
	".\Editguid.h"\
	".\Geoedit.hxx"\
	".\Geoeditm.hxx"\
	".\Geoeditp.hxx"\
	".\Geomtree.hxx"\
	".\Marker.hxx"\
	".\Neu_ein.hxx"\
	".\SmartInterfaces.h"\
	{$(INCLUDE)}"\Atl11.h"\
	{$(INCLUDE)}"\Atlbase.h"\
	{$(INCLUDE)}"\Atlcom.h"\
	{$(INCLUDE)}"\Atlcomx.h"\
	{$(INCLUDE)}"\Atlutil.h"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Copttree.hxx"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\Dblpair.hxx"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\Drawobj.hxx"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Funcs03.h"\
	{$(INCLUDE)}"\Geo_inl.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Itoolbar.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\Justify.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\ospace\Com\Smartif.h"\
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
	{$(INCLUDE)}"\Registrx.hxx"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Rotate.hxx"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\toolguid.h"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\Yxvals.h"\
	

!IF  "$(CFG)" == "Geoedit - Win32 Release"


"$(INTDIR)\Toolbttn.obj" : $(SOURCE) $(DEP_CPP_TOOLB) "$(INTDIR)"\
 "$(INTDIR)\Geoedit.pch"


!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"


"$(INTDIR)\Toolbttn.obj" : $(SOURCE) $(DEP_CPP_TOOLB) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch"

"$(INTDIR)\Toolbttn.sbr" : $(SOURCE) $(DEP_CPP_TOOLB) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Win32\Geoedit.RC
DEP_RSC_GEOEDIT=\
	"..\z_hxx\geoedit.h"\
	".\Win32\delete.cur"\
	".\Win32\Fangen.cur"\
	".\Win32\Geoedit.rcv"\
	".\Win32\innerh.cur"\
	".\Win32\Move.cur"\
	".\Win32\Palette.cur"\
	".\Win32\Split.cur"\
	".\Win32\Stiftf.bmp"\
	".\Win32\Stiftl.bmp"\
	".\Win32\Stiftp.bmp"\
	".\Win32\Stiftv.bmp"\
	".\Win32\tbaredit.bmp"\
	{$(INCLUDE)}"\Resstrg.h"\
	

!IF  "$(CFG)" == "Geoedit - Win32 Release"


"$(INTDIR)\Geoedit.res" : $(SOURCE) $(DEP_RSC_GEOEDIT) "$(INTDIR)"
   $(RSC) /l 0x407 /fo"$(INTDIR)/Geoedit.res" /i "..\z_hxx" /i "Win32" /d\
 "NDEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"


"$(INTDIR)\Geoedit.res" : $(SOURCE) $(DEP_RSC_GEOEDIT) "$(INTDIR)"
   $(RSC) /l 0x407 /fo"$(INTDIR)/Geoedit.res" /i "..\z_hxx" /i "Win32" /d\
 "_DEBUG" $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Win32\Geoedit.def

!IF  "$(CFG)" == "Geoedit - Win32 Release"

!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Ddgeoobj.cxx
DEP_CPP_DDGEO=\
	"..\z_hxx\ctfx.hxx"\
	"..\z_hxx\datbank.hxx"\
	"..\z_hxx\dragline.hxx"\
	"..\Z_hxx\Errcodes.hxx"\
	"..\z_hxx\geo_obj.hxx"\
	"..\z_hxx\geoedit.h"\
	"..\z_hxx\geokonst.hxx"\
	"..\z_hxx\geometrm.hxx"\
	"..\z_hxx\geotrias.hxx"\
	"..\z_hxx\identlst.hxx"\
	"..\z_hxx\igeometr.hxx"\
	"..\z_hxx\koord.hxx"\
	"..\z_hxx\objgext.hxx"\
	"..\z_hxx\ProgressProxy.h"\
	"..\z_hxx\progstat.h"\
	"..\z_hxx\zeichnen.hxx"\
	".\Ddgeoobj.hxx"\
	".\Edikonst.hxx"\
	".\Geoedit.hxx"\
	".\Geoeditm.hxx"\
	".\Geoeditp.hxx"\
	".\Geomtree.hxx"\
	".\Marker.hxx"\
	".\Neu_ein.hxx"\
	".\SmartInterfaces.h"\
	{$(INCLUDE)}"\Atl11.h"\
	{$(INCLUDE)}"\Atlbase.h"\
	{$(INCLUDE)}"\Atlcom.h"\
	{$(INCLUDE)}"\Atlcomx.h"\
	{$(INCLUDE)}"\Atlutil.h"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Copttree.hxx"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\Dblpair.hxx"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\Drawobj.hxx"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Funcs03.h"\
	{$(INCLUDE)}"\Geo_inl.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\iunredo.hxx"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\Justify.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\ospace\Com\Iterenum.h"\
	{$(INCLUDE)}"\ospace\Com\Smartif.h"\
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
	{$(INCLUDE)}"\Print.h"\
	{$(INCLUDE)}"\propactn.h"\
	{$(INCLUDE)}"\Registrx.hxx"\
	{$(INCLUDE)}"\Resstrg.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Rotate.hxx"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TRiASHelper_i.c"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\Undoguid.h"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\Yxvals.h"\
	

!IF  "$(CFG)" == "Geoedit - Win32 Release"


"$(INTDIR)\Ddgeoobj.obj" : $(SOURCE) $(DEP_CPP_DDGEO) "$(INTDIR)"\
 "$(INTDIR)\Geoedit.pch"


!ELSEIF  "$(CFG)" == "Geoedit - Win32 Debug"


"$(INTDIR)\Ddgeoobj.obj" : $(SOURCE) $(DEP_CPP_DDGEO) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch"

"$(INTDIR)\Ddgeoobj.sbr" : $(SOURCE) $(DEP_CPP_DDGEO) "$(INTDIR)"\
 "$(INTDIR)\GEOEDITD.pch"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
