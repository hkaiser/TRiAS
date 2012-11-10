# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=Arctrias - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Arctrias - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Arctrias - Win32 Release" && "$(CFG)" !=\
 "Arctrias - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Arctrias.mak" CFG="Arctrias - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Arctrias - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Arctrias - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "Arctrias - Win32 Debug"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "Arctrias - Win32 Release"

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

ALL : "..\..\..\trias\trias\ARCTRIAS.ext"

CLEAN : 
	-@erase "$(INTDIR)\ARCIMP.OBJ"
	-@erase "$(INTDIR)\ARCIMPIF.OBJ"
	-@erase "$(INTDIR)\ARCLX.OBJ"
	-@erase "$(INTDIR)\Arctrias.pch"
	-@erase "$(INTDIR)\ARCTRIAS.res"
	-@erase "$(INTDIR)\ARCY.OBJ"
	-@erase "$(INTDIR)\FILEPOS.OBJ"
	-@erase "$(INTDIR)\HEADER.OBJ"
	-@erase "$(INTDIR)\HELPTEXT.OBJ"
	-@erase "$(INTDIR)\IMPRESLT.OBJ"
	-@erase "$(INTDIR)\Licenz.obj"
	-@erase "$(INTDIR)\MERKMAL.OBJ"
	-@erase "$(INTDIR)\NUMEDIT.OBJ"
	-@erase "$(INTDIR)\OPTPARAM.OBJ"
	-@erase "$(INTDIR)\PHEADER.OBJ"
	-@erase "$(INTDIR)\REALEDIT.OBJ"
	-@erase "$(INTDIR)\RECHSTAT.OBJ"
	-@erase "$(INTDIR)\STRUTIL.OBJ"
	-@erase "$(INTDIR)\TEXTCONN.OBJ"
	-@erase "$(INTDIR)\TOOLS.OBJ"
	-@erase "$(OUTDIR)\ARCTRIAS.exp"
	-@erase "$(OUTDIR)\ARCTRIAS.lib"
	-@erase "..\..\..\trias\trias\ARCTRIAS.ext"
	-@erase ".\FULL"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /Zp1 /MT /W3 /GX /Ox /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "__CV__" /D "STRICT" /D "MSWIND" /D "DLL" /D "__XT" /D "_USRDLL" /D "_MBCS" /FR /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "\triasdev.mvc\inc.hpp" /I "\triasdev.mvc\inc.hpp\inc" /D "NDEBUG" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /D "__CV__" /D "STRICT" /D "MSWIND" /D "DLL" /D "__XT" /D "__DEXPROCS" /Yu"pheader.h" /c
# SUBTRACT CPP /WX /Fr
CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "\triasdev.mvc\inc.hpp" /I\
 "\triasdev.mvc\inc.hpp\inc" /D "NDEBUG" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /D\
 "__CV__" /D "STRICT" /D "MSWIND" /D "DLL" /D "__XT" /D "__DEXPROCS"\
 /Fp"$(INTDIR)/Arctrias.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\WinRel/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/ARCTRIAS.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Arctrias.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 oldnames.lib ldllcew.lib framelib.lib containr.lib xtension.lib odbcinst.lib ctl3dv2.lib toolhelp.lib /nologo /subsystem:windows /dll /map:"FULL" /machine:IX86
# ADD LINK32 tfrmwork.lib cont32r.lib stdcppr.lib ixtnsr40.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /map:"FULL" /machine:IX86 /nodefaultlib:"libcmt.lib" /stub:"rights.exe" /out:"d:\trias\trias\ARCTRIAS.ext"
# SUBTRACT LINK32 /nodefaultlib
LINK32_FLAGS=tfrmwork.lib cont32r.lib stdcppr.lib ixtnsr40.lib winmm.lib\
 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib\
 shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo\
 /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)/ARCTRIAS.pdb"\
 /map:"FULL" /machine:IX86 /nodefaultlib:"libcmt.lib" /def:".\ARCTRIAS.DEF"\
 /stub:"rights.exe" /out:"d:\trias\trias\ARCTRIAS.ext"\
 /implib:"$(OUTDIR)/ARCTRIAS.lib" 
DEF_FILE= \
	".\ARCTRIAS.DEF"
LINK32_OBJS= \
	"$(INTDIR)\ARCIMP.OBJ" \
	"$(INTDIR)\ARCIMPIF.OBJ" \
	"$(INTDIR)\ARCLX.OBJ" \
	"$(INTDIR)\ARCTRIAS.res" \
	"$(INTDIR)\ARCY.OBJ" \
	"$(INTDIR)\FILEPOS.OBJ" \
	"$(INTDIR)\HEADER.OBJ" \
	"$(INTDIR)\HELPTEXT.OBJ" \
	"$(INTDIR)\IMPRESLT.OBJ" \
	"$(INTDIR)\Licenz.obj" \
	"$(INTDIR)\MERKMAL.OBJ" \
	"$(INTDIR)\NUMEDIT.OBJ" \
	"$(INTDIR)\OPTPARAM.OBJ" \
	"$(INTDIR)\PHEADER.OBJ" \
	"$(INTDIR)\REALEDIT.OBJ" \
	"$(INTDIR)\RECHSTAT.OBJ" \
	"$(INTDIR)\STRUTIL.OBJ" \
	"$(INTDIR)\TEXTCONN.OBJ" \
	"$(INTDIR)\TOOLS.OBJ"

"..\..\..\trias\trias\ARCTRIAS.ext" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Arctrias - Win32 Debug"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WinDebug"
# PROP Intermediate_Dir "WinDebug"
OUTDIR=.\WinDebug
INTDIR=.\WinDebug

ALL : "..\..\..\trias\trias200\ARCTRIAD.ext"

CLEAN : 
	-@erase "$(INTDIR)\ARCIMP.OBJ"
	-@erase "$(INTDIR)\ARCIMPIF.OBJ"
	-@erase "$(INTDIR)\ARCLX.OBJ"
	-@erase "$(INTDIR)\Arctrias.pch"
	-@erase "$(INTDIR)\ARCTRIAS.res"
	-@erase "$(INTDIR)\ARCY.OBJ"
	-@erase "$(INTDIR)\FILEPOS.OBJ"
	-@erase "$(INTDIR)\HEADER.OBJ"
	-@erase "$(INTDIR)\HELPTEXT.OBJ"
	-@erase "$(INTDIR)\IMPRESLT.OBJ"
	-@erase "$(INTDIR)\Licenz.obj"
	-@erase "$(INTDIR)\MERKMAL.OBJ"
	-@erase "$(INTDIR)\NUMEDIT.OBJ"
	-@erase "$(INTDIR)\OPTPARAM.OBJ"
	-@erase "$(INTDIR)\PHEADER.OBJ"
	-@erase "$(INTDIR)\REALEDIT.OBJ"
	-@erase "$(INTDIR)\RECHSTAT.OBJ"
	-@erase "$(INTDIR)\STRUTIL.OBJ"
	-@erase "$(INTDIR)\TEXTCONN.OBJ"
	-@erase "$(INTDIR)\TOOLS.OBJ"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\ARCTRIAD.exp"
	-@erase "$(OUTDIR)\ARCTRIAD.lib"
	-@erase "$(OUTDIR)\ARCTRIAD.pdb"
	-@erase "..\..\..\trias\trias200\ARCTRIAD.ext"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

.\WinDebug\ARCTRIAS.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /Zp1 /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "__CV__" /D "STRICT" /D "MSWIND" /D "DLL" /D "__XT" /D "_USRDLL" /D "_MBCS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /Ob1 /I "\triasdev.mvc\inc.hpp" /I "\triasdev.mvc\inc.hpp\inc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "__CV__" /D "STRICT" /D "MSWIND" /D "DLL" /D "__XT" /D "__DEXPROCS" /Yu"pheader.h" /c
# SUBTRACT CPP /WX /Fr
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /Ob1 /I "\triasdev.mvc\inc.hpp" /I\
 "\triasdev.mvc\inc.hpp\inc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "__CV__" /D\
 "STRICT" /D "MSWIND" /D "DLL" /D "__XT" /D "__DEXPROCS"\
 /Fp"$(INTDIR)/Arctrias.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\WinDebug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/ARCTRIAS.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Arctrias.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 oldnames.lib ldllcew.lib framelib.lib containr.lib xtension.lib odbcinst.lib ctl3dv2.lib toolhelp.lib /nologo /subsystem:windows /dll /map:"FULL" /debug /machine:IX86
# ADD LINK32 tfrm32d.lib stdcppd.lib ixtnsd40.lib cont32d.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /debug /machine:IX86 /stub:"rights.exe" /out:"d:\trias\trias200\ARCTRIAD.ext" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=tfrm32d.lib stdcppd.lib ixtnsd40.lib cont32d.lib winmm.lib\
 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib\
 shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo\
 /dll /incremental:no /pdb:"$(OUTDIR)/ARCTRIAD.pdb" /debug /machine:IX86\
 /def:".\ARCTRIAS.DEF" /stub:"rights.exe" /out:"d:\trias\trias200\ARCTRIAD.ext"\
 /implib:"$(OUTDIR)/ARCTRIAD.lib" /SUBSYSTEM:windows,4.0 
DEF_FILE= \
	".\ARCTRIAS.DEF"
LINK32_OBJS= \
	"$(INTDIR)\ARCIMP.OBJ" \
	"$(INTDIR)\ARCIMPIF.OBJ" \
	"$(INTDIR)\ARCLX.OBJ" \
	"$(INTDIR)\ARCTRIAS.res" \
	"$(INTDIR)\ARCY.OBJ" \
	"$(INTDIR)\FILEPOS.OBJ" \
	"$(INTDIR)\HEADER.OBJ" \
	"$(INTDIR)\HELPTEXT.OBJ" \
	"$(INTDIR)\IMPRESLT.OBJ" \
	"$(INTDIR)\Licenz.obj" \
	"$(INTDIR)\MERKMAL.OBJ" \
	"$(INTDIR)\NUMEDIT.OBJ" \
	"$(INTDIR)\OPTPARAM.OBJ" \
	"$(INTDIR)\PHEADER.OBJ" \
	"$(INTDIR)\REALEDIT.OBJ" \
	"$(INTDIR)\RECHSTAT.OBJ" \
	"$(INTDIR)\STRUTIL.OBJ" \
	"$(INTDIR)\TEXTCONN.OBJ" \
	"$(INTDIR)\TOOLS.OBJ"

"..\..\..\trias\trias200\ARCTRIAD.ext" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Arctrias - Win32 Release"
# Name "Arctrias - Win32 Debug"

!IF  "$(CFG)" == "Arctrias - Win32 Release"

!ELSEIF  "$(CFG)" == "Arctrias - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\PHEADER.CXX
DEP_CPP_PHEAD=\
	"..\..\INC_GLB.32\gc.h"\
	"..\..\Inc_glb.32\syncthrd.hxx"\
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
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\Yxvals.h"\
	

!IF  "$(CFG)" == "Arctrias - Win32 Release"

# ADD CPP /Yc"pheader.h"

BuildCmds= \
	$(CPP) /nologo /MT /W3 /GX /O2 /I "\triasdev.mvc\inc.hpp" /I\
 "\triasdev.mvc\inc.hpp\inc" /D "NDEBUG" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /D\
 "__CV__" /D "STRICT" /D "MSWIND" /D "DLL" /D "__XT" /D "__DEXPROCS"\
 /Fp"$(INTDIR)/Arctrias.pch" /Yc"pheader.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\PHEADER.OBJ" : $(SOURCE) $(DEP_CPP_PHEAD) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Arctrias.pch" : $(SOURCE) $(DEP_CPP_PHEAD) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Arctrias - Win32 Debug"

# ADD CPP /Yc"pheader.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /Ob1 /I "\triasdev.mvc\inc.hpp" /I\
 "\triasdev.mvc\inc.hpp\inc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "__CV__" /D\
 "STRICT" /D "MSWIND" /D "DLL" /D "__XT" /D "__DEXPROCS"\
 /Fp"$(INTDIR)/Arctrias.pch" /Yc"pheader.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\PHEADER.OBJ" : $(SOURCE) $(DEP_CPP_PHEAD) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Arctrias.pch" : $(SOURCE) $(DEP_CPP_PHEAD) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ARCY.CXX

!IF  "$(CFG)" == "Arctrias - Win32 Release"

DEP_CPP_ARCY_=\
	"..\..\INC_GLB.32\gc.h"\
	"..\..\Inc_glb.32\syncthrd.hxx"\
	".\Filepos.hxx"\
	".\Merkmal.hxx"\
	".\Optparam.hxx"\
	".\Pheader.h"\
	".\Rechstat.hxx"\
	".\Textconn.hxx"\
	".\Tools.hxx"\
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
	{$(INCLUDE)}"\Filebuff.hxx"\
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
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\Yxvals.h"\
	

"$(INTDIR)\ARCY.OBJ" : $(SOURCE) $(DEP_CPP_ARCY_) "$(INTDIR)"\
 "$(INTDIR)\Arctrias.pch"


!ELSEIF  "$(CFG)" == "Arctrias - Win32 Debug"

DEP_CPP_ARCY_=\
	".\Filepos.hxx"\
	".\Merkmal.hxx"\
	".\Optparam.hxx"\
	".\Pheader.h"\
	".\Rechstat.hxx"\
	".\Textconn.hxx"\
	".\Tools.hxx"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Filebuff.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\Print.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	

"$(INTDIR)\ARCY.OBJ" : $(SOURCE) $(DEP_CPP_ARCY_) "$(INTDIR)"\
 "$(INTDIR)\Arctrias.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FILEPOS.CXX
DEP_CPP_FILEP=\
	"..\..\INC_GLB.32\gc.h"\
	"..\..\Inc_glb.32\syncthrd.hxx"\
	".\Arctrias.hr"\
	".\Filepos.hxx"\
	".\Optparam.hxx"\
	".\Pheader.h"\
	".\Rechstat.hxx"\
	".\Tools.hxx"\
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
	{$(INCLUDE)}"\Filebuff.hxx"\
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
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_FILEP=\
	".\win16\ARCTRIAS.h"\
	

"$(INTDIR)\FILEPOS.OBJ" : $(SOURCE) $(DEP_CPP_FILEP) "$(INTDIR)"\
 "$(INTDIR)\Arctrias.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\HEADER.CXX

!IF  "$(CFG)" == "Arctrias - Win32 Release"

DEP_CPP_HEADE=\
	"..\..\INC_GLB.32\gc.h"\
	"..\..\Inc_glb.32\syncthrd.hxx"\
	".\Header.hxx"\
	".\Optparam.hxx"\
	".\Pheader.h"\
	".\Tools.hxx"\
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
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Hdrentrx.hxx"\
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
	{$(INCLUDE)}"\Resstrg.h"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\Yxvals.h"\
	

"$(INTDIR)\HEADER.OBJ" : $(SOURCE) $(DEP_CPP_HEADE) "$(INTDIR)"\
 "$(INTDIR)\Arctrias.pch"


!ELSEIF  "$(CFG)" == "Arctrias - Win32 Debug"

DEP_CPP_HEADE=\
	".\Header.hxx"\
	".\Optparam.hxx"\
	".\Pheader.h"\
	".\Tools.hxx"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Hdrentrx.hxx"\
	{$(INCLUDE)}"\Print.h"\
	{$(INCLUDE)}"\Resstrg.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	

"$(INTDIR)\HEADER.OBJ" : $(SOURCE) $(DEP_CPP_HEADE) "$(INTDIR)"\
 "$(INTDIR)\Arctrias.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\HELPTEXT.CXX
DEP_CPP_HELPT=\
	"..\..\INC_GLB.32\gc.h"\
	"..\..\Inc_glb.32\syncthrd.hxx"\
	".\Arctrias.hr"\
	".\Helptext.hxx"\
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
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_HELPT=\
	".\win16\ARCTRIAS.h"\
	

"$(INTDIR)\HELPTEXT.OBJ" : $(SOURCE) $(DEP_CPP_HELPT) "$(INTDIR)"\
 "$(INTDIR)\Arctrias.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\IMPRESLT.CXX
DEP_CPP_IMPRE=\
	"..\..\INC_GLB.32\gc.h"\
	"..\..\Inc_glb.32\syncthrd.hxx"\
	".\Arctrias.hr"\
	".\Impreslt.hxx"\
	".\Optparam.hxx"\
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
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_IMPRE=\
	".\win16\ARCTRIAS.h"\
	

"$(INTDIR)\IMPRESLT.OBJ" : $(SOURCE) $(DEP_CPP_IMPRE) "$(INTDIR)"\
 "$(INTDIR)\Arctrias.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MERKMAL.CXX
DEP_CPP_MERKM=\
	"..\..\INC_GLB.32\gc.h"\
	"..\..\Inc_glb.32\syncthrd.hxx"\
	".\Filepos.hxx"\
	".\Merkmal.hxx"\
	".\Optparam.hxx"\
	".\Pheader.h"\
	".\Textconn.hxx"\
	".\Tools.hxx"\
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
	{$(INCLUDE)}"\Filebuff.hxx"\
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
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\Yxvals.h"\
	

"$(INTDIR)\MERKMAL.OBJ" : $(SOURCE) $(DEP_CPP_MERKM) "$(INTDIR)"\
 "$(INTDIR)\Arctrias.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\NUMEDIT.CXX
DEP_CPP_NUMED=\
	"..\..\INC_GLB.32\gc.h"\
	"..\..\Inc_glb.32\syncthrd.hxx"\
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
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\Yxvals.h"\
	

"$(INTDIR)\NUMEDIT.OBJ" : $(SOURCE) $(DEP_CPP_NUMED) "$(INTDIR)"\
 "$(INTDIR)\Arctrias.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\OPTPARAM.CXX

!IF  "$(CFG)" == "Arctrias - Win32 Release"

DEP_CPP_OPTPA=\
	"..\..\INC_GLB.32\gc.h"\
	"..\..\Inc_glb.32\syncthrd.hxx"\
	".\Arctrias.hr"\
	".\Helptext.hxx"\
	".\Numedit.hxx"\
	".\Optparam.hxx"\
	".\Pheader.h"\
	".\Realedit.hxx"\
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
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_OPTPA=\
	".\win16\ARCTRIAS.h"\
	

"$(INTDIR)\OPTPARAM.OBJ" : $(SOURCE) $(DEP_CPP_OPTPA) "$(INTDIR)"\
 "$(INTDIR)\Arctrias.pch"


!ELSEIF  "$(CFG)" == "Arctrias - Win32 Debug"

DEP_CPP_OPTPA=\
	".\Arctrias.hr"\
	".\Helptext.hxx"\
	".\Numedit.hxx"\
	".\Optparam.hxx"\
	".\Pheader.h"\
	".\Realedit.hxx"\
	

"$(INTDIR)\OPTPARAM.OBJ" : $(SOURCE) $(DEP_CPP_OPTPA) "$(INTDIR)"\
 "$(INTDIR)\Arctrias.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\REALEDIT.CXX
DEP_CPP_REALE=\
	"..\..\INC_GLB.32\gc.h"\
	"..\..\Inc_glb.32\syncthrd.hxx"\
	".\Numedit.hxx"\
	".\Pheader.h"\
	".\Realedit.hxx"\
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
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\Yxvals.h"\
	

"$(INTDIR)\REALEDIT.OBJ" : $(SOURCE) $(DEP_CPP_REALE) "$(INTDIR)"\
 "$(INTDIR)\Arctrias.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\RECHSTAT.CXX
DEP_CPP_RECHS=\
	"..\..\INC_GLB.32\gc.h"\
	"..\..\Inc_glb.32\syncthrd.hxx"\
	".\Arctrias.hr"\
	".\Pheader.h"\
	".\Rechstat.hxx"\
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
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_RECHS=\
	".\win16\ARCTRIAS.h"\
	

"$(INTDIR)\RECHSTAT.OBJ" : $(SOURCE) $(DEP_CPP_RECHS) "$(INTDIR)"\
 "$(INTDIR)\Arctrias.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRUTIL.CXX
DEP_CPP_STRUT=\
	"..\..\INC_GLB.32\gc.h"\
	"..\..\Inc_glb.32\syncthrd.hxx"\
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
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\Yxvals.h"\
	

"$(INTDIR)\STRUTIL.OBJ" : $(SOURCE) $(DEP_CPP_STRUT) "$(INTDIR)"\
 "$(INTDIR)\Arctrias.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\TEXTCONN.CXX
DEP_CPP_TEXTC=\
	"..\..\INC_GLB.32\gc.h"\
	"..\..\Inc_glb.32\syncthrd.hxx"\
	".\Arctrias.hr"\
	".\Pheader.h"\
	".\Textconn.hxx"\
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
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_TEXTC=\
	".\win16\ARCTRIAS.h"\
	

"$(INTDIR)\TEXTCONN.OBJ" : $(SOURCE) $(DEP_CPP_TEXTC) "$(INTDIR)"\
 "$(INTDIR)\Arctrias.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\TOOLS.CXX

!IF  "$(CFG)" == "Arctrias - Win32 Release"

DEP_CPP_TOOLS=\
	"..\..\INC_GLB.32\gc.h"\
	"..\..\Inc_glb.32\syncthrd.hxx"\
	".\Arctrias.hr"\
	".\Optparam.hxx"\
	".\Pheader.h"\
	".\Tools.hxx"\
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
	{$(INCLUDE)}"\Errinstx.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
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
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_TOOLS=\
	".\win16\ARCTRIAS.h"\
	

"$(INTDIR)\TOOLS.OBJ" : $(SOURCE) $(DEP_CPP_TOOLS) "$(INTDIR)"\
 "$(INTDIR)\Arctrias.pch"


!ELSEIF  "$(CFG)" == "Arctrias - Win32 Debug"

DEP_CPP_TOOLS=\
	"..\..\INC_GLB.32\gc.h"\
	"..\..\Inc_glb.32\syncthrd.hxx"\
	".\Arctrias.hr"\
	".\Optparam.hxx"\
	".\Pheader.h"\
	".\Tools.hxx"\
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
	{$(INCLUDE)}"\Errinstx.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
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
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_TOOLS=\
	".\win16\ARCTRIAS.h"\
	

"$(INTDIR)\TOOLS.OBJ" : $(SOURCE) $(DEP_CPP_TOOLS) "$(INTDIR)"\
 "$(INTDIR)\Arctrias.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ARCTRIAS.RC
DEP_RSC_ARCTR=\
	".\ARCTRIAS.RCV"\
	{$(INCLUDE)}"\Resstrg.h"\
	

"$(INTDIR)\ARCTRIAS.res" : $(SOURCE) $(DEP_RSC_ARCTR) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ARCLX.CXX
DEP_CPP_ARCLX=\
	"..\..\INC_GLB.32\gc.h"\
	"..\..\Inc_glb.32\syncthrd.hxx"\
	".\Arclx.cx"\
	".\Optparam.hxx"\
	".\Pheader.h"\
	".\Yytab.h"\
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
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\Yxvals.h"\
	

"$(INTDIR)\ARCLX.OBJ" : $(SOURCE) $(DEP_CPP_ARCLX) "$(INTDIR)"\
 "$(INTDIR)\Arctrias.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ARCTRIAS.DEF

!IF  "$(CFG)" == "Arctrias - Win32 Release"

!ELSEIF  "$(CFG)" == "Arctrias - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ARCIMP.CXX
DEP_CPP_ARCIM=\
	"..\..\INC_GLB.32\gc.h"\
	"..\..\Inc_glb.32\syncthrd.hxx"\
	".\Arcguid.h"\
	".\Arcimp.hxx"\
	".\Arcimpif.hxx"\
	".\Arctrias.hr"\
	".\Helptext.hxx"\
	".\Numedit.hxx"\
	".\Optparam.hxx"\
	".\Pheader.h"\
	".\Realedit.hxx"\
	".\Versio32.h"\
	".\Version.h"\
	".\Win16\Versio16.h"\
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
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\Filebuff.hxx"\
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
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_ARCIM=\
	".\win16\ARCTRIAS.h"\
	

"$(INTDIR)\ARCIMP.OBJ" : $(SOURCE) $(DEP_CPP_ARCIM) "$(INTDIR)"\
 "$(INTDIR)\Arctrias.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ARCIMPIF.CXX

!IF  "$(CFG)" == "Arctrias - Win32 Release"

DEP_CPP_ARCIMP=\
	"..\..\INC_GLB.32\gc.h"\
	"..\..\Inc_glb.32\syncthrd.hxx"\
	".\Arcimpif.hxx"\
	".\Arctrias.hr"\
	".\Filepos.hxx"\
	".\Header.hxx"\
	".\Helptext.hxx"\
	".\Impreslt.hxx"\
	".\Merkmal.hxx"\
	".\Numedit.hxx"\
	".\Optparam.hxx"\
	".\Pheader.h"\
	".\Realedit.hxx"\
	".\Rechstat.hxx"\
	".\Textconn.hxx"\
	".\Tools.hxx"\
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
	{$(INCLUDE)}"\Filebuff.hxx"\
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
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_ARCIMP=\
	".\win16\ARCTRIAS.h"\
	

"$(INTDIR)\ARCIMPIF.OBJ" : $(SOURCE) $(DEP_CPP_ARCIMP) "$(INTDIR)"\
 "$(INTDIR)\Arctrias.pch"


!ELSEIF  "$(CFG)" == "Arctrias - Win32 Debug"

DEP_CPP_ARCIMP=\
	".\Arcimpif.hxx"\
	".\Arctrias.hr"\
	".\Filepos.hxx"\
	".\Header.hxx"\
	".\Helptext.hxx"\
	".\Impreslt.hxx"\
	".\Merkmal.hxx"\
	".\Numedit.hxx"\
	".\Optparam.hxx"\
	".\Pheader.h"\
	".\Realedit.hxx"\
	".\Rechstat.hxx"\
	".\Textconn.hxx"\
	".\Tools.hxx"\
	{$(INCLUDE)}"\Filebuff.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	

"$(INTDIR)\ARCIMPIF.OBJ" : $(SOURCE) $(DEP_CPP_ARCIMP) "$(INTDIR)"\
 "$(INTDIR)\Arctrias.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Licenz.cpp
DEP_CPP_LICEN=\
	"..\..\INC_GLB.32\gc.h"\
	"..\..\Inc_glb.32\syncthrd.hxx"\
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
	{$(INCLUDE)}"\registrx.hxx"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Tstring.hpp"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnimp.hxx"\
	{$(INCLUDE)}"\Yxvals.h"\
	

"$(INTDIR)\Licenz.obj" : $(SOURCE) $(DEP_CPP_LICEN) "$(INTDIR)"\
 "$(INTDIR)\Arctrias.pch"


# End Source File
# End Target
# End Project
################################################################################
