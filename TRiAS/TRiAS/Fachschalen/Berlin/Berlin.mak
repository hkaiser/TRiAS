# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=Berlin - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Berlin - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Berlin - Win32 Release" && "$(CFG)" != "Berlin - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Berlin.mak" CFG="Berlin - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Berlin - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Berlin - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "Berlin - Win32 Release"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "Berlin - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
TargetName=BerlinUpdate
# End Custom Macros

ALL : "$(OUTDIR)\BerlinUpdate.ext" "c:\programme\trias\trias\BerlinUpdate.ext"

CLEAN : 
	-@erase "$(INTDIR)\AuxUIOwner.obj"
	-@erase "$(INTDIR)\BERLIN.OBJ"
	-@erase "$(INTDIR)\Berlin.pch"
	-@erase "$(INTDIR)\BERLIN.res"
	-@erase "$(INTDIR)\ObjekteNummerieren.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\BerlinUpdate.exp"
	-@erase "$(OUTDIR)\BerlinUpdate.ext"
	-@erase "$(OUTDIR)\BerlinUpdate.lib"
	-@erase ".\macro\Alb.ebc"
	-@erase ".\macro\BLINK.ebc"
	-@erase ".\macro\FTeil.ebc"
	-@erase ".\macro\GiTest.ebc"
	-@erase ".\macro\IDENT.ebc"
	-@erase ".\macro\INSEL.ebc"
	-@erase ".\macro\NUMMER.ebc"
	-@erase ".\macro\ObjekteNummerieren.ebc"
	-@erase ".\macro\ObjNummer.ebc"
	-@erase "c:\programme\trias\trias\BerlinUpdate.ext"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O1 /D "BERLINDATA" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__XT" /D "__DEXPROCS" /D "__XTENSNDLL__" /D "__ATL_11_USED__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D "EBWIN32" /D "__DOCUMENT_FWD_DEFINED__" /D "QI_EXCEPTION" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D "OS_NO_ALLOCATORS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MT /W3 /GX /O1 /D "BERLINDATA" /D "NDEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__XT" /D\
 "__DEXPROCS" /D "__XTENSNDLL__" /D "__ATL_11_USED__" /D "__ATL_USED__" /D\
 "OS_NO_STREAM_SUPPORT" /D "EBWIN32" /D "__DOCUMENT_FWD_DEFINED__" /D\
 "QI_EXCEPTION" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D\
 "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D "OS_NO_ALLOCATORS"\
 /Fp"$(INTDIR)/Berlin.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/BERLIN.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Berlin.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ixtatr42.lib triastlb.lib ospace2r.lib cont32r.lib tfrmwork.lib stdcppr.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386 /out:"Release/BerlinUpdate.ext"
LINK32_FLAGS=ixtatr42.lib triastlb.lib ospace2r.lib cont32r.lib tfrmwork.lib\
 stdcppr.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/BerlinUpdate.pdb" /machine:I386\
 /def:"\TRIASDEV.MVC\XTENSION\makroext\BERLIN.DEF"\
 /out:"$(OUTDIR)/BerlinUpdate.ext" /implib:"$(OUTDIR)/BerlinUpdate.lib" 
DEF_FILE= \
	"..\BERLIN.DEF"
LINK32_OBJS= \
	"$(INTDIR)\AuxUIOwner.obj" \
	"$(INTDIR)\BERLIN.OBJ" \
	"$(INTDIR)\BERLIN.res" \
	"$(INTDIR)\ObjekteNummerieren.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\BerlinUpdate.ext" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying Target to Destination...
TargetPath=.\Release\BerlinUpdate.ext
TargetName=BerlinUpdate
InputPath=.\Release\BerlinUpdate.ext
SOURCE=$(InputPath)

"c:\programme\trias\trias\$(TargetName).ext" : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
   copy "$(TargetPath)" c:\programme\trias\trias

# End Custom Build

!ELSEIF  "$(CFG)" == "Berlin - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
TargetName=Berlind
# End Custom Macros

ALL : "$(OUTDIR)\Berlind.ext" "$(OUTDIR)\Berlin.bsc"\
 "c:\trias\trias200.deb\Berlind.ext"

CLEAN : 
	-@erase "$(INTDIR)\AuxUIOwner.obj"
	-@erase "$(INTDIR)\AuxUIOwner.sbr"
	-@erase "$(INTDIR)\BERLIN.OBJ"
	-@erase "$(INTDIR)\Berlin.pch"
	-@erase "$(INTDIR)\BERLIN.res"
	-@erase "$(INTDIR)\BERLIN.SBR"
	-@erase "$(INTDIR)\ObjekteNummerieren.obj"
	-@erase "$(INTDIR)\ObjekteNummerieren.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\Berlin.bsc"
	-@erase "$(OUTDIR)\Berlind.exp"
	-@erase "$(OUTDIR)\Berlind.ext"
	-@erase "$(OUTDIR)\Berlind.ilk"
	-@erase "$(OUTDIR)\Berlind.lib"
	-@erase "$(OUTDIR)\Berlind.pdb"
	-@erase "c:\trias\trias200.deb\Berlind.ext"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__XT" /D "__DEXPROCS" /D "__XTENSNDLL__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D "EBWIN32" /D "__DOCUMENT_FWD_DEFINED__" /D "QI_EXCEPTION" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D "OS_NO_ALLOCATORS" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "STRICT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__XT" /D "__DEXPROCS" /D\
 "__XTENSNDLL__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D "EBWIN32" /D\
 "__DOCUMENT_FWD_DEFINED__" /D "QI_EXCEPTION" /D "OS_WIN_95" /D "OS_STL_ASSERT"\
 /D "OS_NO_WSTRING" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D\
 "OS_NO_ALLOCATORS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/Berlin.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /i "..." /d "_DEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/BERLIN.res" /i "..." /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Berlin.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\AuxUIOwner.sbr" \
	"$(INTDIR)\BERLIN.SBR" \
	"$(INTDIR)\ObjekteNummerieren.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\Berlin.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 ixtatd42.lib triastld.lib ospace2d.lib stdcppd.lib tfrm32d.lib cont32d.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"Debug/Berlind.ext"
LINK32_FLAGS=ixtatd42.lib triastld.lib ospace2d.lib stdcppd.lib tfrm32d.lib\
 cont32d.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/Berlind.pdb" /debug /machine:I386\
 /def:"\TRIASDEV.MVC\XTENSION\makroext\BERLIN.DEF" /out:"$(OUTDIR)/Berlind.ext"\
 /implib:"$(OUTDIR)/Berlind.lib" 
DEF_FILE= \
	"..\BERLIN.DEF"
LINK32_OBJS= \
	"$(INTDIR)\AuxUIOwner.obj" \
	"$(INTDIR)\BERLIN.OBJ" \
	"$(INTDIR)\BERLIN.res" \
	"$(INTDIR)\ObjekteNummerieren.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\Berlind.ext" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying Target to Destination...
TargetPath=.\Debug\Berlind.ext
TargetName=Berlind
InputPath=.\Debug\Berlind.ext
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

# Name "Berlin - Win32 Release"
# Name "Berlin - Win32 Debug"

!IF  "$(CFG)" == "Berlin - Win32 Release"

!ELSEIF  "$(CFG)" == "Berlin - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\makroext\StdAfx.cpp
DEP_CPP_STDAF=\
	"..\BerlinConfig.h"\
	"..\stdafx.h"\
	"C:\MSDEV\ATL11\INCLUDE\atlcomx.h"\
	"C:\MSDEV\ATL11\INCLUDE\atlutil.h"\
	{$(INCLUDE)}"\atl11.h"\
	{$(INCLUDE)}"\Atl\AtlDebug.h"\
	{$(INCLUDE)}"\Atl\ImageHelpDebug.h"\
	{$(INCLUDE)}"\Atl\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\Atl\PE_Debug.h"\
	{$(INCLUDE)}"\atlbase.h"\
	{$(INCLUDE)}"\atlcom.h"\
	{$(INCLUDE)}"\atlimpl.cpp"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\eb.h"\
	{$(INCLUDE)}"\eboem.h"\
	{$(INCLUDE)}"\eieruhr.hxx"\
	{$(INCLUDE)}"\eonrguid.h"\
	{$(INCLUDE)}"\errcodes.hxx"\
	{$(INCLUDE)}"\errinstx.hxx"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ixtensn.hxx"\
	{$(INCLUDE)}"\ospace\com\atl.h"\
	{$(INCLUDE)}"\ospace\com\atlcomx.h"\
	{$(INCLUDE)}"\ospace\com\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\com\smartif.debug.h"\
	{$(INCLUDE)}"\ospace\com\smartif.h"\
	{$(INCLUDE)}"\ospace\com\smartif.nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
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
	{$(INCLUDE)}"\registrx.hxx"\
	{$(INCLUDE)}"\ristypes.hxx"\
	{$(INCLUDE)}"\smartif.h"\
	{$(INCLUDE)}"\stddlg.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TRiASHelper_i.c"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\xtensnn.h"\
	{$(INCLUDE)}"\xtensnx.h"\
	{$(INCLUDE)}"\xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\xtsnprop.hxx"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_STDAF=\
	"C:\TRIASDEV.MVC\Include\dc.h"\
	

!IF  "$(CFG)" == "Berlin - Win32 Release"

# ADD CPP /MD /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O1 /D "BERLINDATA" /D "NDEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__XT" /D\
 "__DEXPROCS" /D "__XTENSNDLL__" /D "__ATL_11_USED__" /D "__ATL_USED__" /D\
 "OS_NO_STREAM_SUPPORT" /D "EBWIN32" /D "__DOCUMENT_FWD_DEFINED__" /D\
 "QI_EXCEPTION" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D\
 "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D "OS_NO_ALLOCATORS"\
 /Fp"$(INTDIR)/Berlin.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Berlin.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Berlin - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "STRICT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__XT" /D "__DEXPROCS" /D\
 "__XTENSNDLL__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D "EBWIN32" /D\
 "__DOCUMENT_FWD_DEFINED__" /D "QI_EXCEPTION" /D "OS_WIN_95" /D "OS_STL_ASSERT"\
 /D "OS_NO_WSTRING" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D\
 "OS_NO_ALLOCATORS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/Berlin.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StdAfx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Berlin.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\makroext\BERLIN.CPP

!IF  "$(CFG)" == "Berlin - Win32 Release"

DEP_CPP_BERLI=\
	"..\AuxUIOwner.h"\
	"..\BerlinConfig.h"\
	"..\BerlinExt.h"\
	"..\blnguid.h"\
	"..\ObjekteNummerieren.h"\
	"..\ObjektNummerierenGuid.h"\
	"..\stdafx.h"\
	"..\version.h"\
	"C:\MSDEV\ATL11\INCLUDE\atlcomx.h"\
	"C:\MSDEV\ATL11\INCLUDE\atlutil.h"\
	{$(INCLUDE)}"\atl11.h"\
	{$(INCLUDE)}"\Atl\AtlDebug.h"\
	{$(INCLUDE)}"\Atl\ImageHelpDebug.h"\
	{$(INCLUDE)}"\Atl\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\Atl\PE_Debug.h"\
	{$(INCLUDE)}"\atlbase.h"\
	{$(INCLUDE)}"\atlcom.h"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\bscrguid.h"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\eb.h"\
	{$(INCLUDE)}"\eboem.h"\
	{$(INCLUDE)}"\eieruhr.hxx"\
	{$(INCLUDE)}"\eonrguid.h"\
	{$(INCLUDE)}"\errcodes.hxx"\
	{$(INCLUDE)}"\errinstx.hxx"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\itoolbar.h"\
	{$(INCLUDE)}"\ixtensn.hxx"\
	{$(INCLUDE)}"\ocidl.h"\
	{$(INCLUDE)}"\ospace\com\atl.h"\
	{$(INCLUDE)}"\ospace\com\atlcomx.h"\
	{$(INCLUDE)}"\ospace\com\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\com\smartif.debug.h"\
	{$(INCLUDE)}"\ospace\com\smartif.h"\
	{$(INCLUDE)}"\ospace\com\smartif.nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
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
	{$(INCLUDE)}"\propactn.h"\
	{$(INCLUDE)}"\registrx.hxx"\
	{$(INCLUDE)}"\ristypes.hxx"\
	{$(INCLUDE)}"\ScriptPropActGuid.h"\
	{$(INCLUDE)}"\smartif.h"\
	{$(INCLUDE)}"\stddlg.hxx"\
	{$(INCLUDE)}"\toolguid.h"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TRiASHelper_i.c"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\xtensnn.h"\
	{$(INCLUDE)}"\xtensnx.h"\
	{$(INCLUDE)}"\xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\xtsnprop.hxx"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_BERLI=\
	"C:\TRIASDEV.MVC\Include\dc.h"\
	
# ADD CPP /MD /O1 /Yu"stdafx.h"

"$(INTDIR)\BERLIN.OBJ" : $(SOURCE) $(DEP_CPP_BERLI) "$(INTDIR)"\
 "$(INTDIR)\Berlin.pch"
   $(CPP) /nologo /MD /W3 /GX /O1 /D "BERLINDATA" /D "NDEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__XT" /D\
 "__DEXPROCS" /D "__XTENSNDLL__" /D "__ATL_11_USED__" /D "__ATL_USED__" /D\
 "OS_NO_STREAM_SUPPORT" /D "EBWIN32" /D "__DOCUMENT_FWD_DEFINED__" /D\
 "QI_EXCEPTION" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D\
 "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D "OS_NO_ALLOCATORS"\
 /Fp"$(INTDIR)/Berlin.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Berlin - Win32 Debug"

DEP_CPP_BERLI=\
	"..\AuxUIOwner.h"\
	"..\BerlinExt.h"\
	"..\blnguid.h"\
	"..\ObjekteNummerieren.h"\
	"..\ObjektNummerierenGuid.h"\
	"..\stdafx.h"\
	"..\version.h"\
	{$(INCLUDE)}"\bscrguid.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\eb.h"\
	{$(INCLUDE)}"\eboem.h"\
	{$(INCLUDE)}"\eonrguid.h"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\itoolbar.h"\
	{$(INCLUDE)}"\ocidl.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
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
	{$(INCLUDE)}"\propactn.h"\
	{$(INCLUDE)}"\ScriptPropActGuid.h"\
	{$(INCLUDE)}"\toolguid.h"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TRiASHelper_i.c"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\xtsnguid.h"\
	
NODEP_CPP_BERLI=\
	"C:\TRIASDEV.MVC\Include\dc.h"\
	
# ADD CPP /Yu"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "STRICT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__XT" /D "__DEXPROCS" /D\
 "__XTENSNDLL__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D "EBWIN32" /D\
 "__DOCUMENT_FWD_DEFINED__" /D "QI_EXCEPTION" /D "OS_WIN_95" /D "OS_STL_ASSERT"\
 /D "OS_NO_WSTRING" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D\
 "OS_NO_ALLOCATORS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/Berlin.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\BERLIN.OBJ" : $(SOURCE) $(DEP_CPP_BERLI) "$(INTDIR)"\
 "$(INTDIR)\Berlin.pch"
   $(BuildCmds)

"$(INTDIR)\BERLIN.SBR" : $(SOURCE) $(DEP_CPP_BERLI) "$(INTDIR)"\
 "$(INTDIR)\Berlin.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\makroext\BERLIN.RC

!IF  "$(CFG)" == "Berlin - Win32 Release"

DEP_RSC_BERLIN=\
	"..\Berlin.rcv"\
	"..\metadata.bmp"\
	"..\Res\ObjekteNummerieren.rgs"\
	".\macro\Alb.ebc"\
	".\macro\BLINK.ebc"\
	".\macro\FTeil.ebc"\
	".\macro\GiTest.ebc"\
	".\macro\IDENT.ebc"\
	".\macro\INSEL.ebc"\
	".\macro\NUMMER.ebc"\
	".\macro\ObjekteNummerieren.ebc"\
	
NODEP_RSC_BERLIN=\
	".\macro\ObjNummer.ebc"\
	

"$(INTDIR)\BERLIN.res" : $(SOURCE) $(DEP_RSC_BERLIN) "$(INTDIR)"\
 ".\macro\Alb.ebc" ".\macro\ObjNummer.ebc" ".\macro\FTeil.ebc"\
 ".\macro\GiTest.ebc" ".\macro\IDENT.ebc" ".\macro\INSEL.ebc"\
 ".\macro\NUMMER.ebc" ".\macro\BLINK.ebc" ".\macro\ObjekteNummerieren.ebc"
   $(RSC) /l 0x407 /fo"$(INTDIR)/BERLIN.res" /i\
 "\TRIASDEV.MVC\XTENSION\makroext" /d "NDEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "Berlin - Win32 Debug"

DEP_RSC_BERLIN=\
	"..\Berlin.rcv"\
	"..\metadata.bmp"\
	"..\Res\ObjekteNummerieren.rgs"\
	".\macro\Alb.ebc"\
	".\macro\BLINK.ebc"\
	".\macro\FTeil.ebc"\
	".\macro\GiTest.ebc"\
	".\macro\IDENT.ebc"\
	".\macro\INSEL.ebc"\
	".\macro\NUMMER.ebc"\
	".\macro\ObjekteNummerieren.ebc"\
	".\macro\ObjNummer.ebc"\
	

"$(INTDIR)\BERLIN.res" : $(SOURCE) $(DEP_RSC_BERLIN) "$(INTDIR)"
   $(RSC) /l 0x407 /fo"$(INTDIR)/BERLIN.res" /i "..." /i\
 "\TRIASDEV.MVC\XTENSION\makroext" /d "_DEBUG" $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\makroext\BERLIN.DEF

!IF  "$(CFG)" == "Berlin - Win32 Release"

!ELSEIF  "$(CFG)" == "Berlin - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\makroext\AuxUIOwner.cpp

!IF  "$(CFG)" == "Berlin - Win32 Release"

DEP_CPP_AUXUI=\
	"..\AuxUIOwner.h"\
	"..\BerlinConfig.h"\
	"..\BerlinExt.h"\
	"..\blnguid.h"\
	"..\stdafx.h"\
	"C:\MSDEV\ATL11\INCLUDE\atlcomx.h"\
	"C:\MSDEV\ATL11\INCLUDE\atlutil.h"\
	{$(INCLUDE)}"\atl11.h"\
	{$(INCLUDE)}"\Atl\AtlDebug.h"\
	{$(INCLUDE)}"\Atl\ImageHelpDebug.h"\
	{$(INCLUDE)}"\Atl\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\Atl\PE_Debug.h"\
	{$(INCLUDE)}"\atlbase.h"\
	{$(INCLUDE)}"\atlcom.h"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\bscrguid.h"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\dirisole.h"\
	{$(INCLUDE)}"\eb.h"\
	{$(INCLUDE)}"\eboem.h"\
	{$(INCLUDE)}"\eieruhr.hxx"\
	{$(INCLUDE)}"\eonrguid.h"\
	{$(INCLUDE)}"\errcodes.hxx"\
	{$(INCLUDE)}"\errinstx.hxx"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\itoolbar.h"\
	{$(INCLUDE)}"\ixtensn.hxx"\
	{$(INCLUDE)}"\ixtnext.hxx"\
	{$(INCLUDE)}"\ocidl.h"\
	{$(INCLUDE)}"\oleguid.h"\
	{$(INCLUDE)}"\ospace\com\atl.h"\
	{$(INCLUDE)}"\ospace\com\atlcomx.h"\
	{$(INCLUDE)}"\ospace\com\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\com\smartif.debug.h"\
	{$(INCLUDE)}"\ospace\com\smartif.h"\
	{$(INCLUDE)}"\ospace\com\smartif.nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
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
	{$(INCLUDE)}"\registrx.hxx"\
	{$(INCLUDE)}"\ristypes.hxx"\
	{$(INCLUDE)}"\smartif.h"\
	{$(INCLUDE)}"\stddlg.hxx"\
	{$(INCLUDE)}"\toolguid.h"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\Triastlb_i.c"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\xtensnn.h"\
	{$(INCLUDE)}"\xtensnx.h"\
	{$(INCLUDE)}"\xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\xtsnprop.hxx"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_AUXUI=\
	"C:\TRIASDEV.MVC\Include\dc.h"\
	
# ADD CPP /MD /Yu"stdafx.h"

"$(INTDIR)\AuxUIOwner.obj" : $(SOURCE) $(DEP_CPP_AUXUI) "$(INTDIR)"\
 "$(INTDIR)\Berlin.pch"
   $(CPP) /nologo /MD /W3 /GX /O1 /D "BERLINDATA" /D "NDEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__XT" /D\
 "__DEXPROCS" /D "__XTENSNDLL__" /D "__ATL_11_USED__" /D "__ATL_USED__" /D\
 "OS_NO_STREAM_SUPPORT" /D "EBWIN32" /D "__DOCUMENT_FWD_DEFINED__" /D\
 "QI_EXCEPTION" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D\
 "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D "OS_NO_ALLOCATORS"\
 /Fp"$(INTDIR)/Berlin.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Berlin - Win32 Debug"

DEP_CPP_AUXUI=\
	"..\AuxUIOwner.h"\
	"..\BerlinExt.h"\
	"..\blnguid.h"\
	"..\stdafx.h"\
	{$(INCLUDE)}"\bscrguid.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\dirisole.h"\
	{$(INCLUDE)}"\eb.h"\
	{$(INCLUDE)}"\eboem.h"\
	{$(INCLUDE)}"\eonrguid.h"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\itoolbar.h"\
	{$(INCLUDE)}"\ixtnext.hxx"\
	{$(INCLUDE)}"\ocidl.h"\
	{$(INCLUDE)}"\oleguid.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
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
	{$(INCLUDE)}"\toolguid.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\Triastlb_i.c"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	
NODEP_CPP_AUXUI=\
	"C:\TRIASDEV.MVC\Include\dc.h"\
	

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "STRICT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__XT" /D "__DEXPROCS" /D\
 "__XTENSNDLL__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D "EBWIN32" /D\
 "__DOCUMENT_FWD_DEFINED__" /D "QI_EXCEPTION" /D "OS_WIN_95" /D "OS_STL_ASSERT"\
 /D "OS_NO_WSTRING" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D\
 "OS_NO_ALLOCATORS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/Berlin.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\AuxUIOwner.obj" : $(SOURCE) $(DEP_CPP_AUXUI) "$(INTDIR)"\
 "$(INTDIR)\Berlin.pch"
   $(BuildCmds)

"$(INTDIR)\AuxUIOwner.sbr" : $(SOURCE) $(DEP_CPP_AUXUI) "$(INTDIR)"\
 "$(INTDIR)\Berlin.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\macro\Alb.ebs

!IF  "$(CFG)" == "Berlin - Win32 Release"

# Begin Custom Build - Compiling Basic ...
InputPath=.\macro\Alb.ebs
InputName=Alb

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   bsl -c -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ELSEIF  "$(CFG)" == "Berlin - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\macro\ObjNummer.ebs

!IF  "$(CFG)" == "Berlin - Win32 Release"

# Begin Custom Build - Compiling Basic ...
InputPath=.\macro\ObjNummer.ebs
InputName=ObjNummer

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   bsl -c -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ELSEIF  "$(CFG)" == "Berlin - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\macro\FTeil.ebs

!IF  "$(CFG)" == "Berlin - Win32 Release"

# Begin Custom Build - Compiling Basic ...
InputPath=.\macro\FTeil.ebs
InputName=FTeil

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   bsl -c -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ELSEIF  "$(CFG)" == "Berlin - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\macro\GiTest.ebs

!IF  "$(CFG)" == "Berlin - Win32 Release"

# Begin Custom Build - Compiling Basic ...
InputPath=.\macro\GiTest.ebs
InputName=GiTest

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   bsl -c -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ELSEIF  "$(CFG)" == "Berlin - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\macro\IDENT.EBS

!IF  "$(CFG)" == "Berlin - Win32 Release"

# Begin Custom Build - Compiling Basic ...
InputPath=.\macro\IDENT.EBS
InputName=IDENT

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   bsl -c -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ELSEIF  "$(CFG)" == "Berlin - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\macro\INSEL.EBS

!IF  "$(CFG)" == "Berlin - Win32 Release"

# Begin Custom Build - Compiling Basic ...
InputPath=.\macro\INSEL.EBS
InputName=INSEL

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   bsl -c -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ELSEIF  "$(CFG)" == "Berlin - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\macro\Nummer.ebf

!IF  "$(CFG)" == "Berlin - Win32 Release"

!ELSEIF  "$(CFG)" == "Berlin - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\macro\NUMMER.EBS

!IF  "$(CFG)" == "Berlin - Win32 Release"

# Begin Custom Build - Compiling Basic ...
InputPath=.\macro\NUMMER.EBS
InputName=NUMMER

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   bsl -c -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ELSEIF  "$(CFG)" == "Berlin - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\macro\BLINK.EBS

!IF  "$(CFG)" == "Berlin - Win32 Release"

# Begin Custom Build - Compiling Basic ...
InputPath=.\macro\BLINK.EBS
InputName=BLINK

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   bsl -c -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ELSEIF  "$(CFG)" == "Berlin - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Triasdev.mvc\XTENSION\makroext\Res\ObjekteNummerieren.rgs

!IF  "$(CFG)" == "Berlin - Win32 Release"

!ELSEIF  "$(CFG)" == "Berlin - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\makroext\ObjekteNummerieren.cpp
DEP_CPP_OBJEK=\
	"..\BerlinConfig.h"\
	"..\ObjekteNummerieren.h"\
	"..\ObjektNummerierenGuid.h"\
	"..\stdafx.h"\
	"C:\MSDEV\ATL11\INCLUDE\atlcomx.h"\
	"C:\MSDEV\ATL11\INCLUDE\atlutil.h"\
	{$(INCLUDE)}"\atl11.h"\
	{$(INCLUDE)}"\Atl\AtlDebug.h"\
	{$(INCLUDE)}"\Atl\ImageHelpDebug.h"\
	{$(INCLUDE)}"\Atl\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\Atl\PE_Debug.h"\
	{$(INCLUDE)}"\atlbase.h"\
	{$(INCLUDE)}"\atlcom.h"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\bscrguid.h"\
	{$(INCLUDE)}"\commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\cv_defs.h"\
	{$(INCLUDE)}"\cv_types.hxx"\
	{$(INCLUDE)}"\cvInline.hxx"\
	{$(INCLUDE)}"\cxxtypes.hxx"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\dirisole.h"\
	{$(INCLUDE)}"\eb.h"\
	{$(INCLUDE)}"\eboem.h"\
	{$(INCLUDE)}"\eieruhr.hxx"\
	{$(INCLUDE)}"\eonrguid.h"\
	{$(INCLUDE)}"\errcodes.hxx"\
	{$(INCLUDE)}"\errinstx.hxx"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ixtensn.hxx"\
	{$(INCLUDE)}"\oleguid.h"\
	{$(INCLUDE)}"\ospace\com\atl.h"\
	{$(INCLUDE)}"\ospace\com\atlcomx.h"\
	{$(INCLUDE)}"\ospace\com\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\com\smartif.debug.h"\
	{$(INCLUDE)}"\ospace\com\smartif.h"\
	{$(INCLUDE)}"\ospace\com\smartif.nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
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
	{$(INCLUDE)}"\propactn.h"\
	{$(INCLUDE)}"\registrx.hxx"\
	{$(INCLUDE)}"\ristypes.hxx"\
	{$(INCLUDE)}"\ScriptPropActGuid.h"\
	{$(INCLUDE)}"\smartif.h"\
	{$(INCLUDE)}"\statguid.h"\
	{$(INCLUDE)}"\stddlg.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TRiASHelper_i.c"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\xtensnn.h"\
	{$(INCLUDE)}"\xtensnx.h"\
	{$(INCLUDE)}"\xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\xtsnprop.hxx"\
	{$(INCLUDE)}"\yxvals.h"\
	
NODEP_CPP_OBJEK=\
	"C:\TRIASDEV.MVC\Include\dc.h"\
	

!IF  "$(CFG)" == "Berlin - Win32 Release"

# ADD CPP /MD

"$(INTDIR)\ObjekteNummerieren.obj" : $(SOURCE) $(DEP_CPP_OBJEK) "$(INTDIR)"\
 "$(INTDIR)\Berlin.pch"
   $(CPP) /nologo /MD /W3 /GX /O1 /D "BERLINDATA" /D "NDEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__XT" /D\
 "__DEXPROCS" /D "__XTENSNDLL__" /D "__ATL_11_USED__" /D "__ATL_USED__" /D\
 "OS_NO_STREAM_SUPPORT" /D "EBWIN32" /D "__DOCUMENT_FWD_DEFINED__" /D\
 "QI_EXCEPTION" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D\
 "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D "OS_NO_ALLOCATORS"\
 /Fp"$(INTDIR)/Berlin.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Berlin - Win32 Debug"


BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "STRICT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__XT" /D "__DEXPROCS" /D\
 "__XTENSNDLL__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D "EBWIN32" /D\
 "__DOCUMENT_FWD_DEFINED__" /D "QI_EXCEPTION" /D "OS_WIN_95" /D "OS_STL_ASSERT"\
 /D "OS_NO_WSTRING" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D\
 "OS_NO_ALLOCATORS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/Berlin.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\ObjekteNummerieren.obj" : $(SOURCE) $(DEP_CPP_OBJEK) "$(INTDIR)"\
 "$(INTDIR)\Berlin.pch"
   $(BuildCmds)

"$(INTDIR)\ObjekteNummerieren.sbr" : $(SOURCE) $(DEP_CPP_OBJEK) "$(INTDIR)"\
 "$(INTDIR)\Berlin.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\macro\ObjekteNummerieren.ebs

!IF  "$(CFG)" == "Berlin - Win32 Release"

# Begin Custom Build - Compiling Basic ...
InputPath=.\macro\ObjekteNummerieren.ebs
InputName=ObjekteNummerieren

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   bsl -c -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ELSEIF  "$(CFG)" == "Berlin - Win32 Debug"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
