# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=komp32 - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to komp32 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "komp32 - Win32 Release" && "$(CFG)" != "komp32 - Win32 Debug"\
 && "$(CFG)" != "komp32 - Win32 Pseudodebug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Komp32.mak" CFG="komp32 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "komp32 - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "komp32 - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "komp32 - Win32 Pseudodebug" (based on\
 "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "komp32 - Win32 Release"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "komp32 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WinRel"
# PROP Intermediate_Dir "WinRel"
# PROP Target_Dir ""
OUTDIR=.\WinRel
INTDIR=.\WinRel
# Begin Custom Macros
TargetName=kompias
# End Custom Macros

ALL : "$(OUTDIR)\kompias.ext" "c:\programme\trias\trias\kompias.ext"

CLEAN : 
	-@erase "$(INTDIR)\AuxUIOwner.obj"
	-@erase "$(INTDIR)\Cobjkomp.obj"
	-@erase "$(INTDIR)\Cobjtree.obj"
	-@erase "$(INTDIR)\Ctopobj.obj"
	-@erase "$(INTDIR)\Datahelp.obj"
	-@erase "$(INTDIR)\Gewbaum.obj"
	-@erase "$(INTDIR)\Komp32.pch"
	-@erase "$(INTDIR)\Komp32.res"
	-@erase "$(INTDIR)\Kompcls.obj"
	-@erase "$(INTDIR)\Kompdll.obj"
	-@erase "$(INTDIR)\Kompgeo.obj"
	-@erase "$(INTDIR)\Kompgew.obj"
	-@erase "$(INTDIR)\Komphead.obj"
	-@erase "$(INTDIR)\Kompias.obj"
	-@erase "$(INTDIR)\Kompifce.obj"
	-@erase "$(INTDIR)\Kompmem.obj"
	-@erase "$(INTDIR)\Kompmenu.obj"
	-@erase "$(INTDIR)\Kompp.obj"
	-@erase "$(INTDIR)\Komppage.obj"
	-@erase "$(INTDIR)\Kompprof.obj"
	-@erase "$(INTDIR)\Kompsimu.obj"
	-@erase "$(INTDIR)\Kompwin.obj"
	-@erase "$(INTDIR)\Kparea.obj"
	-@erase "$(INTDIR)\Kpbauw.obj"
	-@erase "$(INTDIR)\Kpbigar.obj"
	-@erase "$(INTDIR)\Kpmcode.obj"
	-@erase "$(INTDIR)\Kpstatus.obj"
	-@erase "$(INTDIR)\Kpsymb.obj"
	-@erase "$(INTDIR)\Kpwinot.obj"
	-@erase "$(INTDIR)\Strutil.obj"
	-@erase "$(INTDIR)\TOOLBAR.OBJ"
	-@erase "$(INTDIR)\Trgeom.obj"
	-@erase "$(INTDIR)\Txtedit.obj"
	-@erase "$(INTDIR)\Vobjprop.obj"
	-@erase "$(OUTDIR)\kompias.exp"
	-@erase "$(OUTDIR)\kompias.ext"
	-@erase "$(OUTDIR)\kompias.lib"
	-@erase ".\macro\Color.ebc"
	-@erase ".\macro\Topolog.ebc"
	-@erase ".\macro\UeberSchwemmung.ebc"
	-@erase "c:\programme\trias\trias\kompias.ext"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__XT" /D "__DEXPROCS" /D "__XTENSNDLL__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D "EBWIN32" /D "__DOCUMENT_FWD_DEFINED__" /D "QI_EXCEPTION" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D "OS_NO_ALLOCATORS" /Yu"kompp.hxx" /c
CPP_PROJ=/nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "STRICT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__XT" /D "__DEXPROCS" /D\
 "__XTENSNDLL__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D "EBWIN32" /D\
 "__DOCUMENT_FWD_DEFINED__" /D "QI_EXCEPTION" /D "OS_WIN_95" /D "OS_STL_ASSERT"\
 /D "OS_NO_WSTRING" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D\
 "OS_NO_ALLOCATORS" /Fp"$(INTDIR)/Komp32.pch" /Yu"kompp.hxx" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\WinRel/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/Komp32.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Komp32.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ixtnsr42.lib ospace2r.lib cont32r.lib tfrmwork.lib stdcppr.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386 /out:"WinRel/kompias.ext"
LINK32_FLAGS=ixtnsr42.lib ospace2r.lib cont32r.lib tfrmwork.lib stdcppr.lib\
 winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/kompias.pdb" /machine:I386 /def:".\Kompakt.def"\
 /out:"$(OUTDIR)/kompias.ext" /implib:"$(OUTDIR)/kompias.lib" 
DEF_FILE= \
	".\Kompakt.def"
LINK32_OBJS= \
	"$(INTDIR)\AuxUIOwner.obj" \
	"$(INTDIR)\Cobjkomp.obj" \
	"$(INTDIR)\Cobjtree.obj" \
	"$(INTDIR)\Ctopobj.obj" \
	"$(INTDIR)\Datahelp.obj" \
	"$(INTDIR)\Gewbaum.obj" \
	"$(INTDIR)\Komp32.res" \
	"$(INTDIR)\Kompcls.obj" \
	"$(INTDIR)\Kompdll.obj" \
	"$(INTDIR)\Kompgeo.obj" \
	"$(INTDIR)\Kompgew.obj" \
	"$(INTDIR)\Komphead.obj" \
	"$(INTDIR)\Kompias.obj" \
	"$(INTDIR)\Kompifce.obj" \
	"$(INTDIR)\Kompmem.obj" \
	"$(INTDIR)\Kompmenu.obj" \
	"$(INTDIR)\Kompp.obj" \
	"$(INTDIR)\Komppage.obj" \
	"$(INTDIR)\Kompprof.obj" \
	"$(INTDIR)\Kompsimu.obj" \
	"$(INTDIR)\Kompwin.obj" \
	"$(INTDIR)\Kparea.obj" \
	"$(INTDIR)\Kpbauw.obj" \
	"$(INTDIR)\Kpbigar.obj" \
	"$(INTDIR)\Kpmcode.obj" \
	"$(INTDIR)\Kpstatus.obj" \
	"$(INTDIR)\Kpsymb.obj" \
	"$(INTDIR)\Kpwinot.obj" \
	"$(INTDIR)\Strutil.obj" \
	"$(INTDIR)\TOOLBAR.OBJ" \
	"$(INTDIR)\Trgeom.obj" \
	"$(INTDIR)\Txtedit.obj" \
	"$(INTDIR)\Vobjprop.obj"

"$(OUTDIR)\kompias.ext" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying Target to Destination. ..
TargetPath=.\WinRel\kompias.ext
TargetName=kompias
InputPath=.\WinRel\kompias.ext
SOURCE=$(InputPath)

"c:\programme\trias\trias\$(TargetName).ext" : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
   copy "$(TargetPath)" c:\programme\trias\trias

# End Custom Build

!ELSEIF  "$(CFG)" == "komp32 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WinDebug"
# PROP Intermediate_Dir "WinDebug"
# PROP Target_Dir ""
OUTDIR=.\WinDebug
INTDIR=.\WinDebug
# Begin Custom Macros
TargetName=kompias
# End Custom Macros

ALL : "$(OUTDIR)\kompias.ext" "$(OUTDIR)\Komp32.bsc"\
 "c:\trias\trias200.deb\kompias.ext"

CLEAN : 
	-@erase "$(INTDIR)\AuxUIOwner.obj"
	-@erase "$(INTDIR)\AuxUIOwner.sbr"
	-@erase "$(INTDIR)\Cobjkomp.obj"
	-@erase "$(INTDIR)\Cobjkomp.sbr"
	-@erase "$(INTDIR)\Cobjtree.obj"
	-@erase "$(INTDIR)\Cobjtree.sbr"
	-@erase "$(INTDIR)\Ctopobj.obj"
	-@erase "$(INTDIR)\Ctopobj.sbr"
	-@erase "$(INTDIR)\Datahelp.obj"
	-@erase "$(INTDIR)\Datahelp.sbr"
	-@erase "$(INTDIR)\Gewbaum.obj"
	-@erase "$(INTDIR)\Gewbaum.sbr"
	-@erase "$(INTDIR)\Komp32.pch"
	-@erase "$(INTDIR)\Komp32.res"
	-@erase "$(INTDIR)\Kompcls.obj"
	-@erase "$(INTDIR)\Kompcls.sbr"
	-@erase "$(INTDIR)\Kompdll.obj"
	-@erase "$(INTDIR)\Kompdll.sbr"
	-@erase "$(INTDIR)\Kompgeo.obj"
	-@erase "$(INTDIR)\Kompgeo.sbr"
	-@erase "$(INTDIR)\Kompgew.obj"
	-@erase "$(INTDIR)\Kompgew.sbr"
	-@erase "$(INTDIR)\Komphead.obj"
	-@erase "$(INTDIR)\Komphead.sbr"
	-@erase "$(INTDIR)\Kompias.obj"
	-@erase "$(INTDIR)\Kompias.sbr"
	-@erase "$(INTDIR)\Kompifce.obj"
	-@erase "$(INTDIR)\Kompifce.sbr"
	-@erase "$(INTDIR)\Kompmem.obj"
	-@erase "$(INTDIR)\Kompmem.sbr"
	-@erase "$(INTDIR)\Kompmenu.obj"
	-@erase "$(INTDIR)\Kompmenu.sbr"
	-@erase "$(INTDIR)\Kompp.obj"
	-@erase "$(INTDIR)\Kompp.sbr"
	-@erase "$(INTDIR)\Komppage.obj"
	-@erase "$(INTDIR)\Komppage.sbr"
	-@erase "$(INTDIR)\Kompprof.obj"
	-@erase "$(INTDIR)\Kompprof.sbr"
	-@erase "$(INTDIR)\Kompsimu.obj"
	-@erase "$(INTDIR)\Kompsimu.sbr"
	-@erase "$(INTDIR)\Kompwin.obj"
	-@erase "$(INTDIR)\Kompwin.sbr"
	-@erase "$(INTDIR)\Kparea.obj"
	-@erase "$(INTDIR)\Kparea.sbr"
	-@erase "$(INTDIR)\Kpbauw.obj"
	-@erase "$(INTDIR)\Kpbauw.sbr"
	-@erase "$(INTDIR)\Kpbigar.obj"
	-@erase "$(INTDIR)\Kpbigar.sbr"
	-@erase "$(INTDIR)\Kpmcode.obj"
	-@erase "$(INTDIR)\Kpmcode.sbr"
	-@erase "$(INTDIR)\Kpstatus.obj"
	-@erase "$(INTDIR)\Kpstatus.sbr"
	-@erase "$(INTDIR)\Kpsymb.obj"
	-@erase "$(INTDIR)\Kpsymb.sbr"
	-@erase "$(INTDIR)\Kpwinot.obj"
	-@erase "$(INTDIR)\Kpwinot.sbr"
	-@erase "$(INTDIR)\Strutil.obj"
	-@erase "$(INTDIR)\Strutil.sbr"
	-@erase "$(INTDIR)\TOOLBAR.OBJ"
	-@erase "$(INTDIR)\TOOLBAR.SBR"
	-@erase "$(INTDIR)\Trgeom.obj"
	-@erase "$(INTDIR)\Trgeom.sbr"
	-@erase "$(INTDIR)\Txtedit.obj"
	-@erase "$(INTDIR)\Txtedit.sbr"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(INTDIR)\Vobjprop.obj"
	-@erase "$(INTDIR)\Vobjprop.sbr"
	-@erase "$(OUTDIR)\Komp32.bsc"
	-@erase "$(OUTDIR)\kompias.exp"
	-@erase "$(OUTDIR)\kompias.ext"
	-@erase "$(OUTDIR)\kompias.ilk"
	-@erase "$(OUTDIR)\kompias.lib"
	-@erase "$(OUTDIR)\kompias.pdb"
	-@erase "c:\trias\trias200.deb\kompias.ext"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__XT" /D "__DEXPROCS" /D "__XTENSNDLL__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D "EBWIN32" /D "__DOCUMENT_FWD_DEFINED__" /D "QI_EXCEPTION" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D "OS_NO_ALLOCATORS" /FR /Yu"kompp.hxx" /c
CPP_PROJ=/nologo /MDd /W3 /WX /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__XT" /D\
 "__DEXPROCS" /D "__XTENSNDLL__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D\
 "EBWIN32" /D "__DOCUMENT_FWD_DEFINED__" /D "QI_EXCEPTION" /D "OS_WIN_95" /D\
 "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "OS_ALTERNATIVE_STRING_NAMES" /D\
 "OS_MULTI_THREADED" /D "OS_NO_ALLOCATORS" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/Komp32.pch" /Yu"kompp.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\WinDebug/
CPP_SBRS=.\WinDebug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /i ".." /d "_DEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/Komp32.res" /i ".." /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Komp32.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\AuxUIOwner.sbr" \
	"$(INTDIR)\Cobjkomp.sbr" \
	"$(INTDIR)\Cobjtree.sbr" \
	"$(INTDIR)\Ctopobj.sbr" \
	"$(INTDIR)\Datahelp.sbr" \
	"$(INTDIR)\Gewbaum.sbr" \
	"$(INTDIR)\Kompcls.sbr" \
	"$(INTDIR)\Kompdll.sbr" \
	"$(INTDIR)\Kompgeo.sbr" \
	"$(INTDIR)\Kompgew.sbr" \
	"$(INTDIR)\Komphead.sbr" \
	"$(INTDIR)\Kompias.sbr" \
	"$(INTDIR)\Kompifce.sbr" \
	"$(INTDIR)\Kompmem.sbr" \
	"$(INTDIR)\Kompmenu.sbr" \
	"$(INTDIR)\Kompp.sbr" \
	"$(INTDIR)\Komppage.sbr" \
	"$(INTDIR)\Kompprof.sbr" \
	"$(INTDIR)\Kompsimu.sbr" \
	"$(INTDIR)\Kompwin.sbr" \
	"$(INTDIR)\Kparea.sbr" \
	"$(INTDIR)\Kpbauw.sbr" \
	"$(INTDIR)\Kpbigar.sbr" \
	"$(INTDIR)\Kpmcode.sbr" \
	"$(INTDIR)\Kpstatus.sbr" \
	"$(INTDIR)\Kpsymb.sbr" \
	"$(INTDIR)\Kpwinot.sbr" \
	"$(INTDIR)\Strutil.sbr" \
	"$(INTDIR)\TOOLBAR.SBR" \
	"$(INTDIR)\Trgeom.sbr" \
	"$(INTDIR)\Txtedit.sbr" \
	"$(INTDIR)\Vobjprop.sbr"

"$(OUTDIR)\Komp32.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 ixtnsd42.lib ixtatd42.lib ospace2d.lib cont32d.lib tfrm32d.lib stdcppd.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"WinDebug/kompias.ext"
LINK32_FLAGS=ixtnsd42.lib ixtatd42.lib ospace2d.lib cont32d.lib tfrm32d.lib\
 stdcppd.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/kompias.pdb" /debug /machine:I386 /def:".\Kompakt.def"\
 /out:"$(OUTDIR)/kompias.ext" /implib:"$(OUTDIR)/kompias.lib" 
DEF_FILE= \
	".\Kompakt.def"
LINK32_OBJS= \
	"$(INTDIR)\AuxUIOwner.obj" \
	"$(INTDIR)\Cobjkomp.obj" \
	"$(INTDIR)\Cobjtree.obj" \
	"$(INTDIR)\Ctopobj.obj" \
	"$(INTDIR)\Datahelp.obj" \
	"$(INTDIR)\Gewbaum.obj" \
	"$(INTDIR)\Komp32.res" \
	"$(INTDIR)\Kompcls.obj" \
	"$(INTDIR)\Kompdll.obj" \
	"$(INTDIR)\Kompgeo.obj" \
	"$(INTDIR)\Kompgew.obj" \
	"$(INTDIR)\Komphead.obj" \
	"$(INTDIR)\Kompias.obj" \
	"$(INTDIR)\Kompifce.obj" \
	"$(INTDIR)\Kompmem.obj" \
	"$(INTDIR)\Kompmenu.obj" \
	"$(INTDIR)\Kompp.obj" \
	"$(INTDIR)\Komppage.obj" \
	"$(INTDIR)\Kompprof.obj" \
	"$(INTDIR)\Kompsimu.obj" \
	"$(INTDIR)\Kompwin.obj" \
	"$(INTDIR)\Kparea.obj" \
	"$(INTDIR)\Kpbauw.obj" \
	"$(INTDIR)\Kpbigar.obj" \
	"$(INTDIR)\Kpmcode.obj" \
	"$(INTDIR)\Kpstatus.obj" \
	"$(INTDIR)\Kpsymb.obj" \
	"$(INTDIR)\Kpwinot.obj" \
	"$(INTDIR)\Strutil.obj" \
	"$(INTDIR)\TOOLBAR.OBJ" \
	"$(INTDIR)\Trgeom.obj" \
	"$(INTDIR)\Txtedit.obj" \
	"$(INTDIR)\Vobjprop.obj"

"$(OUTDIR)\kompias.ext" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying Target to Destination...
TargetPath=.\WinDebug\kompias.ext
TargetName=kompias
InputPath=.\WinDebug\kompias.ext
SOURCE=$(InputPath)

"c:\trias\trias200.deb\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   copy "$(TargetPath)" c:\trias\trias200.deb

# End Custom Build

!ELSEIF  "$(CFG)" == "komp32 - Win32 Pseudodebug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "komp32__"
# PROP BASE Intermediate_Dir "komp32__"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "komp32__"
# PROP Intermediate_Dir "komp32__"
# PROP Target_Dir ""
OUTDIR=.\komp32__
INTDIR=.\komp32__
# Begin Custom Macros
TargetName=kompias
# End Custom Macros

ALL : "$(OUTDIR)\kompias.ext" "c:\programme\trias\trias\kompias.ext"

CLEAN : 
	-@erase "$(INTDIR)\AuxUIOwner.obj"
	-@erase "$(INTDIR)\Cobjkomp.obj"
	-@erase "$(INTDIR)\Cobjtree.obj"
	-@erase "$(INTDIR)\Ctopobj.obj"
	-@erase "$(INTDIR)\Datahelp.obj"
	-@erase "$(INTDIR)\Gewbaum.obj"
	-@erase "$(INTDIR)\Komp32.pch"
	-@erase "$(INTDIR)\Komp32.res"
	-@erase "$(INTDIR)\Kompcls.obj"
	-@erase "$(INTDIR)\Kompdll.obj"
	-@erase "$(INTDIR)\Kompgeo.obj"
	-@erase "$(INTDIR)\Kompgew.obj"
	-@erase "$(INTDIR)\Komphead.obj"
	-@erase "$(INTDIR)\Kompias.obj"
	-@erase "$(INTDIR)\Kompifce.obj"
	-@erase "$(INTDIR)\Kompmem.obj"
	-@erase "$(INTDIR)\Kompmenu.obj"
	-@erase "$(INTDIR)\Kompp.obj"
	-@erase "$(INTDIR)\Komppage.obj"
	-@erase "$(INTDIR)\Kompprof.obj"
	-@erase "$(INTDIR)\Kompsimu.obj"
	-@erase "$(INTDIR)\Kompwin.obj"
	-@erase "$(INTDIR)\Kparea.obj"
	-@erase "$(INTDIR)\Kpbauw.obj"
	-@erase "$(INTDIR)\Kpbigar.obj"
	-@erase "$(INTDIR)\Kpmcode.obj"
	-@erase "$(INTDIR)\Kpstatus.obj"
	-@erase "$(INTDIR)\Kpsymb.obj"
	-@erase "$(INTDIR)\Kpwinot.obj"
	-@erase "$(INTDIR)\Strutil.obj"
	-@erase "$(INTDIR)\TOOLBAR.OBJ"
	-@erase "$(INTDIR)\Trgeom.obj"
	-@erase "$(INTDIR)\Txtedit.obj"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(INTDIR)\Vobjprop.obj"
	-@erase "$(OUTDIR)\kompias.exp"
	-@erase "$(OUTDIR)\kompias.ext"
	-@erase "$(OUTDIR)\kompias.lib"
	-@erase "$(OUTDIR)\kompias.pdb"
	-@erase "c:\programme\trias\trias\kompias.ext"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__XT" /D "__DEXPROCS" /D "__XTENSNDLL__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__XT" /D "__DEXPROCS" /D "__XTENSNDLL__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D "EBWIN32" /D "__DOCUMENT_FWD_DEFINED__" /D "QI_EXCEPTION" /D "OS_NO_WSTRING" /Yu"kompp.hxx" /c
CPP_PROJ=/nologo /MD /W3 /WX /GX /Zi /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "STRICT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__XT" /D "__DEXPROCS" /D\
 "__XTENSNDLL__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D "EBWIN32" /D\
 "__DOCUMENT_FWD_DEFINED__" /D "QI_EXCEPTION" /D "OS_NO_WSTRING"\
 /Fp"$(INTDIR)/Komp32.pch" /Yu"kompp.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\komp32__/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/Komp32.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Komp32.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 ixtnsr40.lib cont32r.lib tfrmwork.lib stdcppr.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386 /out:"WinRel/kompias.ext"
# ADD LINK32 ixtnsr42.lib cont32r.lib tfrmwork.lib stdcppr.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"komp32__/kompias.ext"
LINK32_FLAGS=ixtnsr42.lib cont32r.lib tfrmwork.lib stdcppr.lib winmm.lib\
 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib\
 shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo\
 /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)/kompias.pdb" /debug\
 /machine:I386 /def:".\Kompakt.def" /out:"$(OUTDIR)/kompias.ext"\
 /implib:"$(OUTDIR)/kompias.lib" 
DEF_FILE= \
	".\Kompakt.def"
LINK32_OBJS= \
	"$(INTDIR)\AuxUIOwner.obj" \
	"$(INTDIR)\Cobjkomp.obj" \
	"$(INTDIR)\Cobjtree.obj" \
	"$(INTDIR)\Ctopobj.obj" \
	"$(INTDIR)\Datahelp.obj" \
	"$(INTDIR)\Gewbaum.obj" \
	"$(INTDIR)\Komp32.res" \
	"$(INTDIR)\Kompcls.obj" \
	"$(INTDIR)\Kompdll.obj" \
	"$(INTDIR)\Kompgeo.obj" \
	"$(INTDIR)\Kompgew.obj" \
	"$(INTDIR)\Komphead.obj" \
	"$(INTDIR)\Kompias.obj" \
	"$(INTDIR)\Kompifce.obj" \
	"$(INTDIR)\Kompmem.obj" \
	"$(INTDIR)\Kompmenu.obj" \
	"$(INTDIR)\Kompp.obj" \
	"$(INTDIR)\Komppage.obj" \
	"$(INTDIR)\Kompprof.obj" \
	"$(INTDIR)\Kompsimu.obj" \
	"$(INTDIR)\Kompwin.obj" \
	"$(INTDIR)\Kparea.obj" \
	"$(INTDIR)\Kpbauw.obj" \
	"$(INTDIR)\Kpbigar.obj" \
	"$(INTDIR)\Kpmcode.obj" \
	"$(INTDIR)\Kpstatus.obj" \
	"$(INTDIR)\Kpsymb.obj" \
	"$(INTDIR)\Kpwinot.obj" \
	"$(INTDIR)\Strutil.obj" \
	"$(INTDIR)\TOOLBAR.OBJ" \
	"$(INTDIR)\Trgeom.obj" \
	"$(INTDIR)\Txtedit.obj" \
	"$(INTDIR)\Vobjprop.obj"

"$(OUTDIR)\kompias.ext" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying Target to Destination. ..
TargetPath=.\komp32__\kompias.ext
TargetName=kompias
InputPath=.\komp32__\kompias.ext
SOURCE=$(InputPath)

"c:\programme\trias\trias\$(TargetName).ext" : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
   copy "$(TargetPath)" c:\programme\trias\trias

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

# Name "komp32 - Win32 Release"
# Name "komp32 - Win32 Debug"
# Name "komp32 - Win32 Pseudodebug"

!IF  "$(CFG)" == "komp32 - Win32 Release"

!ELSEIF  "$(CFG)" == "komp32 - Win32 Debug"

!ELSEIF  "$(CFG)" == "komp32 - Win32 Pseudodebug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=\Triasdev.mvc\Xtension\Kompias\Strutil.cxx
DEP_CPP_STRUT=\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompias.h"\
	"..\kompp.hxx"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
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
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_STRUT=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

!IF  "$(CFG)" == "komp32 - Win32 Release"


"$(INTDIR)\Strutil.obj" : $(SOURCE) $(DEP_CPP_STRUT) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "STRICT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__XT" /D "__DEXPROCS" /D\
 "__XTENSNDLL__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D "EBWIN32" /D\
 "__DOCUMENT_FWD_DEFINED__" /D "QI_EXCEPTION" /D "OS_WIN_95" /D "OS_STL_ASSERT"\
 /D "OS_NO_WSTRING" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D\
 "OS_NO_ALLOCATORS" /Fp"$(INTDIR)/Komp32.pch" /Yu"kompp.hxx" /Fo"$(INTDIR)/" /c\
 $(SOURCE)


!ELSEIF  "$(CFG)" == "komp32 - Win32 Debug"

# ADD CPP /MDd

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__XT" /D\
 "__DEXPROCS" /D "__XTENSNDLL__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D\
 "EBWIN32" /D "__DOCUMENT_FWD_DEFINED__" /D "QI_EXCEPTION" /D "OS_WIN_95" /D\
 "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "OS_ALTERNATIVE_STRING_NAMES" /D\
 "OS_MULTI_THREADED" /D "OS_NO_ALLOCATORS" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/Komp32.pch" /Yu"kompp.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\Strutil.obj" : $(SOURCE) $(DEP_CPP_STRUT) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(BuildCmds)

"$(INTDIR)\Strutil.sbr" : $(SOURCE) $(DEP_CPP_STRUT) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "komp32 - Win32 Pseudodebug"


"$(INTDIR)\Strutil.obj" : $(SOURCE) $(DEP_CPP_STRUT) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /Zi /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "STRICT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__XT" /D "__DEXPROCS" /D\
 "__XTENSNDLL__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D "EBWIN32" /D\
 "__DOCUMENT_FWD_DEFINED__" /D "QI_EXCEPTION" /D "OS_NO_WSTRING"\
 /Fp"$(INTDIR)/Komp32.pch" /Yu"kompp.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Triasdev.mvc\Xtension\Kompias\Kompdll.cxx

!IF  "$(CFG)" == "komp32 - Win32 Release"

DEP_CPP_KOMPD=\
	"..\about.hxx"\
	"..\cobjtree.hxx"\
	"..\ctopobj.hxx"\
	"..\gewbaum.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompdef.h"\
	"..\kompdll.hxx"\
	"..\kompgew.hxx"\
	"..\komphead.hxx"\
	"..\kompias.h"\
	"..\kompias.hxx"\
	"..\kompp.hxx"\
	"..\kompprof.hxx"\
	"..\triasdef.h"\
	"..\version.h"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\bscrguid.h"\
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
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\OLEGUID.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_KOMPD=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"..\versio16.h"\
	"C:\TRIASDEV.MVC\Include\dc.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

"$(INTDIR)\Kompdll.obj" : $(SOURCE) $(DEP_CPP_KOMPD) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "komp32 - Win32 Debug"

DEP_CPP_KOMPD=\
	"..\about.hxx"\
	"..\cobjtree.hxx"\
	"..\ctopobj.hxx"\
	"..\gewbaum.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompdef.h"\
	"..\kompdll.hxx"\
	"..\kompgew.hxx"\
	"..\komphead.hxx"\
	"..\kompias.h"\
	"..\kompias.hxx"\
	"..\kompp.hxx"\
	"..\kompprof.hxx"\
	"..\triasdef.h"\
	"..\versio16.h"\
	"..\version.h"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\bscrguid.h"\
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
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\OLEGUID.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_KOMPD=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"C:\TRIASDEV.MVC\Include\dc.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Kompdll.obj" : $(SOURCE) $(DEP_CPP_KOMPD) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(BuildCmds)

"$(INTDIR)\Kompdll.sbr" : $(SOURCE) $(DEP_CPP_KOMPD) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "komp32 - Win32 Pseudodebug"

DEP_CPP_KOMPD=\
	"..\about.hxx"\
	"..\cobjtree.hxx"\
	"..\ctopobj.hxx"\
	"..\gewbaum.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompdef.h"\
	"..\kompdll.hxx"\
	"..\kompgew.hxx"\
	"..\komphead.hxx"\
	"..\kompias.h"\
	"..\kompias.hxx"\
	"..\kompp.hxx"\
	"..\kompprof.hxx"\
	"..\triasdef.h"\
	"..\versio16.h"\
	"..\version.h"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\bscrguid.h"\
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
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\OLEGUID.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_KOMPD=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"C:\TRIASDEV.MVC\Include\dc.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

"$(INTDIR)\Kompdll.obj" : $(SOURCE) $(DEP_CPP_KOMPD) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Triasdev.mvc\Xtension\Kompias\Kompgeo.cxx

!IF  "$(CFG)" == "komp32 - Win32 Release"

DEP_CPP_KOMPG=\
	"..\about.h"\
	"..\about.hxx"\
	"..\cobjtree.hxx"\
	"..\gewbaum.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompdef.h"\
	"..\kompdll.hxx"\
	"..\kompgew.hxx"\
	"..\komphead.hxx"\
	"..\kompias.h"\
	"..\kompias.hxx"\
	"..\kompp.hxx"\
	"..\kompwin.hxx"\
	"..\kpstatus.hxx"\
	"..\triasdef.h"\
	"..\version.h"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\bscrguid.h"\
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
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\OLEGUID.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_KOMPG=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"..\versio16.h"\
	"C:\TRIASDEV.MVC\Include\dc.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

"$(INTDIR)\Kompgeo.obj" : $(SOURCE) $(DEP_CPP_KOMPG) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "komp32 - Win32 Debug"

DEP_CPP_KOMPG=\
	"..\about.h"\
	"..\about.hxx"\
	"..\cobjtree.hxx"\
	"..\gewbaum.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompdef.h"\
	"..\kompdll.hxx"\
	"..\kompgew.hxx"\
	"..\komphead.hxx"\
	"..\kompias.h"\
	"..\kompias.hxx"\
	"..\kompp.hxx"\
	"..\kompwin.hxx"\
	"..\kpstatus.hxx"\
	"..\triasdef.h"\
	"..\versio16.h"\
	"..\version.h"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\bscrguid.h"\
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
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\OLEGUID.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_KOMPG=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"C:\TRIASDEV.MVC\Include\dc.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Kompgeo.obj" : $(SOURCE) $(DEP_CPP_KOMPG) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(BuildCmds)

"$(INTDIR)\Kompgeo.sbr" : $(SOURCE) $(DEP_CPP_KOMPG) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "komp32 - Win32 Pseudodebug"

DEP_CPP_KOMPG=\
	"..\about.h"\
	"..\about.hxx"\
	"..\cobjtree.hxx"\
	"..\gewbaum.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompdef.h"\
	"..\kompdll.hxx"\
	"..\kompgew.hxx"\
	"..\komphead.hxx"\
	"..\kompias.h"\
	"..\kompias.hxx"\
	"..\kompp.hxx"\
	"..\kompwin.hxx"\
	"..\kpstatus.hxx"\
	"..\triasdef.h"\
	"..\versio16.h"\
	"..\version.h"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\bscrguid.h"\
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
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\OLEGUID.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_KOMPG=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"C:\TRIASDEV.MVC\Include\dc.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

"$(INTDIR)\Kompgeo.obj" : $(SOURCE) $(DEP_CPP_KOMPG) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Triasdev.mvc\Xtension\Kompias\Kompgew.cxx
DEP_CPP_KOMPGE=\
	"..\about.h"\
	"..\about.hxx"\
	"..\cobjtree.hxx"\
	"..\gewbaum.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompdef.h"\
	"..\kompdll.hxx"\
	"..\kompgew.hxx"\
	"..\komphead.hxx"\
	"..\kompias.h"\
	"..\kompias.hxx"\
	"..\kompp.hxx"\
	"..\kpmcode.hxx"\
	"..\kpstatus.hxx"\
	"..\triasdef.h"\
	"..\txtedit.hxx"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\bscrguid.h"\
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
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_KOMPGE=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"C:\TRIASDEV.MVC\Include\dc.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

!IF  "$(CFG)" == "komp32 - Win32 Release"


"$(INTDIR)\Kompgew.obj" : $(SOURCE) $(DEP_CPP_KOMPGE) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "komp32 - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Kompgew.obj" : $(SOURCE) $(DEP_CPP_KOMPGE) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(BuildCmds)

"$(INTDIR)\Kompgew.sbr" : $(SOURCE) $(DEP_CPP_KOMPGE) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "komp32 - Win32 Pseudodebug"


"$(INTDIR)\Kompgew.obj" : $(SOURCE) $(DEP_CPP_KOMPGE) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Triasdev.mvc\Xtension\Kompias\Kompias.cxx

!IF  "$(CFG)" == "komp32 - Win32 Release"

DEP_CPP_KOMPI=\
	"..\about.h"\
	"..\about.hxx"\
	"..\cobjtree.hxx"\
	"..\ctopobj.hxx"\
	"..\gewbaum.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompdef.h"\
	"..\kompdll.hxx"\
	"..\kompgew.hxx"\
	"..\kompguid.h"\
	"..\komphead.hxx"\
	"..\kompias.h"\
	"..\kompias.hxx"\
	"..\kompp.hxx"\
	"..\kompprof.hxx"\
	"..\kompsimu.hxx"\
	"..\kompwin.hxx"\
	"..\kpstatus.hxx"\
	"..\triasdef.h"\
	"..\txtedit.hxx"\
	"..\version.h"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ABSTGUID.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\bscrguid.h"\
	{$(INCLUDE)}"\Buffguid.h"\
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
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OBJGGUID.H"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\OLEGUID.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\statguid.h"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_KOMPI=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"..\versio16.h"\
	"C:\TRIASDEV.MVC\Include\dc.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

"$(INTDIR)\Kompias.obj" : $(SOURCE) $(DEP_CPP_KOMPI) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "komp32 - Win32 Debug"

DEP_CPP_KOMPI=\
	"..\about.h"\
	"..\about.hxx"\
	"..\cobjtree.hxx"\
	"..\ctopobj.hxx"\
	"..\gewbaum.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompdef.h"\
	"..\kompdll.hxx"\
	"..\kompgew.hxx"\
	"..\kompguid.h"\
	"..\komphead.hxx"\
	"..\kompias.h"\
	"..\kompias.hxx"\
	"..\kompp.hxx"\
	"..\kompprof.hxx"\
	"..\kompsimu.hxx"\
	"..\kompwin.hxx"\
	"..\kpstatus.hxx"\
	"..\triasdef.h"\
	"..\txtedit.hxx"\
	"..\versio16.h"\
	"..\version.h"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ABSTGUID.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\bscrguid.h"\
	{$(INCLUDE)}"\Buffguid.h"\
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
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OBJGGUID.H"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\OLEGUID.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\statguid.h"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_KOMPI=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"C:\TRIASDEV.MVC\Include\dc.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Kompias.obj" : $(SOURCE) $(DEP_CPP_KOMPI) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(BuildCmds)

"$(INTDIR)\Kompias.sbr" : $(SOURCE) $(DEP_CPP_KOMPI) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "komp32 - Win32 Pseudodebug"

DEP_CPP_KOMPI=\
	"..\about.h"\
	"..\about.hxx"\
	"..\cobjtree.hxx"\
	"..\ctopobj.hxx"\
	"..\gewbaum.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompdef.h"\
	"..\kompdll.hxx"\
	"..\kompgew.hxx"\
	"..\kompguid.h"\
	"..\komphead.hxx"\
	"..\kompias.h"\
	"..\kompias.hxx"\
	"..\kompp.hxx"\
	"..\kompprof.hxx"\
	"..\kompsimu.hxx"\
	"..\kompwin.hxx"\
	"..\kpstatus.hxx"\
	"..\triasdef.h"\
	"..\txtedit.hxx"\
	"..\versio16.h"\
	"..\version.h"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ABSTGUID.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\bscrguid.h"\
	{$(INCLUDE)}"\Buffguid.h"\
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
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OBJGGUID.H"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\OLEGUID.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\statguid.h"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_KOMPI=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"C:\TRIASDEV.MVC\Include\dc.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

"$(INTDIR)\Kompias.obj" : $(SOURCE) $(DEP_CPP_KOMPI) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Triasdev.mvc\Xtension\Kompias\Kompifce.cxx

!IF  "$(CFG)" == "komp32 - Win32 Release"

DEP_CPP_KOMPIF=\
	"..\about.h"\
	"..\about.hxx"\
	"..\cobjtree.hxx"\
	"..\ctopobj.hxx"\
	"..\gewbaum.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompdef.h"\
	"..\kompdll.hxx"\
	"..\komphead.hxx"\
	"..\kompias.h"\
	"..\kompias.hxx"\
	"..\kompp.hxx"\
	"..\objgguid.h"\
	"..\triasdef.h"\
	"..\version.h"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ABSTGUID.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\bscrguid.h"\
	{$(INCLUDE)}"\Buffguid.h"\
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
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\iunredo.hxx"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\OLEGUID.H"\
	{$(INCLUDE)}"\OPERGUID.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\TRELGUID.H"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\UNDOGUID.H"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_KOMPIF=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"..\versio16.h"\
	"C:\TRIASDEV.MVC\Include\dc.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

"$(INTDIR)\Kompifce.obj" : $(SOURCE) $(DEP_CPP_KOMPIF) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "komp32 - Win32 Debug"

DEP_CPP_KOMPIF=\
	"..\about.h"\
	"..\about.hxx"\
	"..\cobjtree.hxx"\
	"..\ctopobj.hxx"\
	"..\gewbaum.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompdef.h"\
	"..\kompdll.hxx"\
	"..\komphead.hxx"\
	"..\kompias.h"\
	"..\kompias.hxx"\
	"..\kompp.hxx"\
	"..\objgguid.h"\
	"..\triasdef.h"\
	"..\versio16.h"\
	"..\version.h"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ABSTGUID.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\bscrguid.h"\
	{$(INCLUDE)}"\Buffguid.h"\
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
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\iunredo.hxx"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\OLEGUID.H"\
	{$(INCLUDE)}"\OPERGUID.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\TRELGUID.H"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\UNDOGUID.H"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_KOMPIF=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"C:\TRIASDEV.MVC\Include\dc.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Kompifce.obj" : $(SOURCE) $(DEP_CPP_KOMPIF) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(BuildCmds)

"$(INTDIR)\Kompifce.sbr" : $(SOURCE) $(DEP_CPP_KOMPIF) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "komp32 - Win32 Pseudodebug"

DEP_CPP_KOMPIF=\
	"..\about.h"\
	"..\about.hxx"\
	"..\cobjtree.hxx"\
	"..\ctopobj.hxx"\
	"..\gewbaum.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompdef.h"\
	"..\kompdll.hxx"\
	"..\komphead.hxx"\
	"..\kompias.h"\
	"..\kompias.hxx"\
	"..\kompp.hxx"\
	"..\objgguid.h"\
	"..\triasdef.h"\
	"..\versio16.h"\
	"..\version.h"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ABSTGUID.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\bscrguid.h"\
	{$(INCLUDE)}"\Buffguid.h"\
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
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\iunredo.hxx"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\OLEGUID.H"\
	{$(INCLUDE)}"\OPERGUID.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\TRELGUID.H"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\UNDOGUID.H"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_KOMPIF=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"C:\TRIASDEV.MVC\Include\dc.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

"$(INTDIR)\Kompifce.obj" : $(SOURCE) $(DEP_CPP_KOMPIF) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Triasdev.mvc\Xtension\Kompias\Kompmem.cxx

!IF  "$(CFG)" == "komp32 - Win32 Release"

DEP_CPP_KOMPM=\
	"..\about.h"\
	"..\about.hxx"\
	"..\cobjtree.hxx"\
	"..\gewbaum.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompdef.h"\
	"..\kompdll.hxx"\
	"..\kompgew.hxx"\
	"..\komphead.hxx"\
	"..\kompias.h"\
	"..\kompias.hxx"\
	"..\kompp.hxx"\
	"..\kompsimu.hxx"\
	"..\kompwin.hxx"\
	"..\kpstatus.hxx"\
	"..\triasdef.h"\
	"..\txtedit.hxx"\
	"..\version.h"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\bscrguid.h"\
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
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\OLEGUID.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_KOMPM=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"..\versio16.h"\
	"C:\TRIASDEV.MVC\Include\dc.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

"$(INTDIR)\Kompmem.obj" : $(SOURCE) $(DEP_CPP_KOMPM) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "komp32 - Win32 Debug"

DEP_CPP_KOMPM=\
	"..\about.h"\
	"..\about.hxx"\
	"..\cobjtree.hxx"\
	"..\gewbaum.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompdef.h"\
	"..\kompdll.hxx"\
	"..\kompgew.hxx"\
	"..\komphead.hxx"\
	"..\kompias.h"\
	"..\kompias.hxx"\
	"..\kompp.hxx"\
	"..\kompsimu.hxx"\
	"..\kompwin.hxx"\
	"..\kpstatus.hxx"\
	"..\triasdef.h"\
	"..\txtedit.hxx"\
	"..\versio16.h"\
	"..\version.h"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\bscrguid.h"\
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
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\OLEGUID.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_KOMPM=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"C:\TRIASDEV.MVC\Include\dc.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Kompmem.obj" : $(SOURCE) $(DEP_CPP_KOMPM) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(BuildCmds)

"$(INTDIR)\Kompmem.sbr" : $(SOURCE) $(DEP_CPP_KOMPM) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "komp32 - Win32 Pseudodebug"

DEP_CPP_KOMPM=\
	"..\about.h"\
	"..\about.hxx"\
	"..\cobjtree.hxx"\
	"..\gewbaum.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompdef.h"\
	"..\kompdll.hxx"\
	"..\kompgew.hxx"\
	"..\komphead.hxx"\
	"..\kompias.h"\
	"..\kompias.hxx"\
	"..\kompp.hxx"\
	"..\kompsimu.hxx"\
	"..\kompwin.hxx"\
	"..\kpstatus.hxx"\
	"..\triasdef.h"\
	"..\txtedit.hxx"\
	"..\versio16.h"\
	"..\version.h"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\bscrguid.h"\
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
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\OLEGUID.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_KOMPM=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"C:\TRIASDEV.MVC\Include\dc.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

"$(INTDIR)\Kompmem.obj" : $(SOURCE) $(DEP_CPP_KOMPM) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Triasdev.mvc\Xtension\Kompias\Kompp.cxx
DEP_CPP_KOMPP=\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompp.hxx"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
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
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_KOMPP=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

!IF  "$(CFG)" == "komp32 - Win32 Release"

# ADD CPP /Yc"kompp.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "STRICT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__XT" /D "__DEXPROCS" /D\
 "__XTENSNDLL__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D "EBWIN32" /D\
 "__DOCUMENT_FWD_DEFINED__" /D "QI_EXCEPTION" /D "OS_WIN_95" /D "OS_STL_ASSERT"\
 /D "OS_NO_WSTRING" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D\
 "OS_NO_ALLOCATORS" /Fp"$(INTDIR)/Komp32.pch" /Yc"kompp.hxx" /Fo"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\Kompp.obj" : $(SOURCE) $(DEP_CPP_KOMPP) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Komp32.pch" : $(SOURCE) $(DEP_CPP_KOMPP) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "komp32 - Win32 Debug"

# ADD CPP /Yc"kompp.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__XT" /D\
 "__DEXPROCS" /D "__XTENSNDLL__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D\
 "EBWIN32" /D "__DOCUMENT_FWD_DEFINED__" /D "QI_EXCEPTION" /D "OS_WIN_95" /D\
 "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "OS_ALTERNATIVE_STRING_NAMES" /D\
 "OS_MULTI_THREADED" /D "OS_NO_ALLOCATORS" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/Komp32.pch" /Yc"kompp.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\Kompp.obj" : $(SOURCE) $(DEP_CPP_KOMPP) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Kompp.sbr" : $(SOURCE) $(DEP_CPP_KOMPP) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Komp32.pch" : $(SOURCE) $(DEP_CPP_KOMPP) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "komp32 - Win32 Pseudodebug"

# ADD CPP /MD /Yc"kompp.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /Zi /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "STRICT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__XT" /D "__DEXPROCS" /D\
 "__XTENSNDLL__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D "EBWIN32" /D\
 "__DOCUMENT_FWD_DEFINED__" /D "QI_EXCEPTION" /D "OS_NO_WSTRING"\
 /Fp"$(INTDIR)/Komp32.pch" /Yc"kompp.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\Kompp.obj" : $(SOURCE) $(DEP_CPP_KOMPP) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Komp32.pch" : $(SOURCE) $(DEP_CPP_KOMPP) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Triasdev.mvc\Xtension\Kompias\Kompwin.cxx
DEP_CPP_KOMPW=\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompdef.h"\
	"..\kompias.h"\
	"..\kompp.hxx"\
	"..\kompwin.hxx"\
	"..\triasdef.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
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
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_KOMPW=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

!IF  "$(CFG)" == "komp32 - Win32 Release"


"$(INTDIR)\Kompwin.obj" : $(SOURCE) $(DEP_CPP_KOMPW) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "komp32 - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Kompwin.obj" : $(SOURCE) $(DEP_CPP_KOMPW) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(BuildCmds)

"$(INTDIR)\Kompwin.sbr" : $(SOURCE) $(DEP_CPP_KOMPW) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "komp32 - Win32 Pseudodebug"


"$(INTDIR)\Kompwin.obj" : $(SOURCE) $(DEP_CPP_KOMPW) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Triasdev.mvc\Xtension\Kompias\Gewbaum.cxx
DEP_CPP_GEWBA=\
	"..\about.h"\
	"..\about.hxx"\
	"..\gewbaum.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompdef.h"\
	"..\kompias.h"\
	"..\kompp.hxx"\
	"..\triasdef.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
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
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_GEWBA=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

!IF  "$(CFG)" == "komp32 - Win32 Release"


"$(INTDIR)\Gewbaum.obj" : $(SOURCE) $(DEP_CPP_GEWBA) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "komp32 - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Gewbaum.obj" : $(SOURCE) $(DEP_CPP_GEWBA) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(BuildCmds)

"$(INTDIR)\Gewbaum.sbr" : $(SOURCE) $(DEP_CPP_GEWBA) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "komp32 - Win32 Pseudodebug"


"$(INTDIR)\Gewbaum.obj" : $(SOURCE) $(DEP_CPP_GEWBA) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Kompakt.def

!IF  "$(CFG)" == "komp32 - Win32 Release"

!ELSEIF  "$(CFG)" == "komp32 - Win32 Debug"

!ELSEIF  "$(CFG)" == "komp32 - Win32 Pseudodebug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Komp32.rc
DEP_RSC_KOMP3=\
	".\ABOUT.H"\
	".\ABOUT.SRC"\
	".\KompaktPageExt.rgs"\
	".\kompdata.bmp"\
	".\KOMPIAS.H"\
	".\KOMPIAS.ICO"\
	".\KOMPIAS.RCV"\
	".\macro\Color.ebc"\
	".\macro\Topolog.ebc"\
	".\macro\UeberSchwemmung.ebc"\
	{$(INCLUDE)}"\RESSTRG.H"\
	

!IF  "$(CFG)" == "komp32 - Win32 Release"

# ADD BASE RSC /l 0x407
# ADD RSC /l 0x407 /i ".."

"$(INTDIR)\Komp32.res" : $(SOURCE) $(DEP_RSC_KOMP3) "$(INTDIR)"\
 ".\macro\Color.ebc" ".\macro\Topolog.ebc" ".\macro\UeberSchwemmung.ebc"
   $(RSC) /l 0x407 /fo"$(INTDIR)/Komp32.res" /i ".." /d "NDEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "komp32 - Win32 Debug"


"$(INTDIR)\Komp32.res" : $(SOURCE) $(DEP_RSC_KOMP3) "$(INTDIR)"
   $(RSC) /l 0x407 /fo"$(INTDIR)/Komp32.res" /i ".." /d "_DEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "komp32 - Win32 Pseudodebug"

# ADD BASE RSC /l 0x407 /i ".."
# ADD RSC /l 0x407 /i ".."

"$(INTDIR)\Komp32.res" : $(SOURCE) $(DEP_RSC_KOMP3) "$(INTDIR)"
   $(RSC) /l 0x407 /fo"$(INTDIR)/Komp32.res" /i ".." /d "NDEBUG" $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Triasdev.mvc\Xtension\Kompias\Komphead.cxx

!IF  "$(CFG)" == "komp32 - Win32 Release"

DEP_CPP_KOMPH=\
	"..\cobjtree.hxx"\
	"..\gewbaum.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompdef.h"\
	"..\kompdll.hxx"\
	"..\komphead.hxx"\
	"..\kompias.h"\
	"..\kompias.hxx"\
	"..\kompp.hxx"\
	"..\kpstatus.hxx"\
	"..\triasdef.h"\
	"..\version.h"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
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
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_KOMPH=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"..\versio16.h"\
	"C:\TRIASDEV.MVC\Include\dc.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

"$(INTDIR)\Komphead.obj" : $(SOURCE) $(DEP_CPP_KOMPH) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "komp32 - Win32 Debug"

DEP_CPP_KOMPH=\
	"..\cobjtree.hxx"\
	"..\gewbaum.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompdef.h"\
	"..\kompdll.hxx"\
	"..\komphead.hxx"\
	"..\kompias.h"\
	"..\kompias.hxx"\
	"..\kompp.hxx"\
	"..\kpstatus.hxx"\
	"..\triasdef.h"\
	"..\versio16.h"\
	"..\version.h"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
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
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_KOMPH=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"C:\TRIASDEV.MVC\Include\dc.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Komphead.obj" : $(SOURCE) $(DEP_CPP_KOMPH) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(BuildCmds)

"$(INTDIR)\Komphead.sbr" : $(SOURCE) $(DEP_CPP_KOMPH) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "komp32 - Win32 Pseudodebug"

DEP_CPP_KOMPH=\
	"..\cobjtree.hxx"\
	"..\gewbaum.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompdef.h"\
	"..\kompdll.hxx"\
	"..\komphead.hxx"\
	"..\kompias.h"\
	"..\kompias.hxx"\
	"..\kompp.hxx"\
	"..\kpstatus.hxx"\
	"..\triasdef.h"\
	"..\versio16.h"\
	"..\version.h"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
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
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_KOMPH=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"C:\TRIASDEV.MVC\Include\dc.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

"$(INTDIR)\Komphead.obj" : $(SOURCE) $(DEP_CPP_KOMPH) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Triasdev.mvc\Xtension\Kompias\Txtedit.cxx
DEP_CPP_TXTED=\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompias.h"\
	"..\kompp.hxx"\
	"..\txtedit.hxx"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
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
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_TXTED=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

!IF  "$(CFG)" == "komp32 - Win32 Release"


"$(INTDIR)\Txtedit.obj" : $(SOURCE) $(DEP_CPP_TXTED) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "komp32 - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Txtedit.obj" : $(SOURCE) $(DEP_CPP_TXTED) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(BuildCmds)

"$(INTDIR)\Txtedit.sbr" : $(SOURCE) $(DEP_CPP_TXTED) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "komp32 - Win32 Pseudodebug"


"$(INTDIR)\Txtedit.obj" : $(SOURCE) $(DEP_CPP_TXTED) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Triasdev.mvc\Xtension\Kompias\Kpmcode.cxx
DEP_CPP_KPMCO=\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompdef.h"\
	"..\kompias.h"\
	"..\kompp.hxx"\
	"..\kpmcode.hxx"\
	"..\triasdef.h"\
	"..\txtedit.hxx"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
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
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_KPMCO=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

!IF  "$(CFG)" == "komp32 - Win32 Release"


"$(INTDIR)\Kpmcode.obj" : $(SOURCE) $(DEP_CPP_KPMCO) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "komp32 - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Kpmcode.obj" : $(SOURCE) $(DEP_CPP_KPMCO) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(BuildCmds)

"$(INTDIR)\Kpmcode.sbr" : $(SOURCE) $(DEP_CPP_KPMCO) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "komp32 - Win32 Pseudodebug"


"$(INTDIR)\Kpmcode.obj" : $(SOURCE) $(DEP_CPP_KPMCO) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Triasdev.mvc\Xtension\Kompias\Kpwinot.cxx

!IF  "$(CFG)" == "komp32 - Win32 Release"

DEP_CPP_KPWIN=\
	"..\about.h"\
	"..\about.hxx"\
	"..\cobjtree.hxx"\
	"..\ctopobj.hxx"\
	"..\gewbaum.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompdef.h"\
	"..\kompdll.hxx"\
	"..\komphead.hxx"\
	"..\kompias.h"\
	"..\kompias.hxx"\
	"..\kompp.hxx"\
	"..\triasdef.h"\
	"..\version.h"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\bscrguid.h"\
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
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IENUMONR.HXX"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\OLEGUID.H"\
	{$(INCLUDE)}"\OPERGUID.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\TRELGUID.H"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_KPWIN=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"..\versio16.h"\
	"C:\TRIASDEV.MVC\Include\dc.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

"$(INTDIR)\Kpwinot.obj" : $(SOURCE) $(DEP_CPP_KPWIN) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "komp32 - Win32 Debug"

DEP_CPP_KPWIN=\
	"..\about.h"\
	"..\about.hxx"\
	"..\cobjtree.hxx"\
	"..\ctopobj.hxx"\
	"..\gewbaum.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompdef.h"\
	"..\kompdll.hxx"\
	"..\komphead.hxx"\
	"..\kompias.h"\
	"..\kompias.hxx"\
	"..\kompp.hxx"\
	"..\triasdef.h"\
	"..\versio16.h"\
	"..\version.h"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\bscrguid.h"\
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
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IENUMONR.HXX"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\OLEGUID.H"\
	{$(INCLUDE)}"\OPERGUID.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\TRELGUID.H"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_KPWIN=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"C:\TRIASDEV.MVC\Include\dc.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Kpwinot.obj" : $(SOURCE) $(DEP_CPP_KPWIN) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(BuildCmds)

"$(INTDIR)\Kpwinot.sbr" : $(SOURCE) $(DEP_CPP_KPWIN) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "komp32 - Win32 Pseudodebug"

DEP_CPP_KPWIN=\
	"..\about.h"\
	"..\about.hxx"\
	"..\cobjtree.hxx"\
	"..\ctopobj.hxx"\
	"..\gewbaum.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompdef.h"\
	"..\kompdll.hxx"\
	"..\komphead.hxx"\
	"..\kompias.h"\
	"..\kompias.hxx"\
	"..\kompp.hxx"\
	"..\triasdef.h"\
	"..\versio16.h"\
	"..\version.h"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\bscrguid.h"\
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
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IENUMONR.HXX"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\OLEGUID.H"\
	{$(INCLUDE)}"\OPERGUID.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\TRELGUID.H"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_KPWIN=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"C:\TRIASDEV.MVC\Include\dc.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

"$(INTDIR)\Kpwinot.obj" : $(SOURCE) $(DEP_CPP_KPWIN) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Triasdev.mvc\Xtension\Kompias\Kompmenu.cxx

!IF  "$(CFG)" == "komp32 - Win32 Release"

DEP_CPP_KOMPME=\
	"..\about.h"\
	"..\about.hxx"\
	"..\cobjtree.hxx"\
	"..\ctopobj.hxx"\
	"..\gewbaum.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompdef.h"\
	"..\kompdll.hxx"\
	"..\kompgew.hxx"\
	"..\komphead.hxx"\
	"..\kompias.h"\
	"..\kompias.hxx"\
	"..\kompp.hxx"\
	"..\kompprof.hxx"\
	"..\kompwin.hxx"\
	"..\kpstatus.hxx"\
	"..\triasdef.h"\
	"..\version.h"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\bscrguid.h"\
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
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\OLEGUID.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_KOMPME=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"..\versio16.h"\
	"C:\TRIASDEV.MVC\Include\dc.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

"$(INTDIR)\Kompmenu.obj" : $(SOURCE) $(DEP_CPP_KOMPME) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "komp32 - Win32 Debug"

DEP_CPP_KOMPME=\
	"..\about.h"\
	"..\about.hxx"\
	"..\cobjtree.hxx"\
	"..\ctopobj.hxx"\
	"..\gewbaum.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompdef.h"\
	"..\kompdll.hxx"\
	"..\kompgew.hxx"\
	"..\komphead.hxx"\
	"..\kompias.h"\
	"..\kompias.hxx"\
	"..\kompp.hxx"\
	"..\kompprof.hxx"\
	"..\kompwin.hxx"\
	"..\kpstatus.hxx"\
	"..\triasdef.h"\
	"..\versio16.h"\
	"..\version.h"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\bscrguid.h"\
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
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\OLEGUID.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_KOMPME=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"C:\TRIASDEV.MVC\Include\dc.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Kompmenu.obj" : $(SOURCE) $(DEP_CPP_KOMPME) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(BuildCmds)

"$(INTDIR)\Kompmenu.sbr" : $(SOURCE) $(DEP_CPP_KOMPME) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "komp32 - Win32 Pseudodebug"

DEP_CPP_KOMPME=\
	"..\about.h"\
	"..\about.hxx"\
	"..\cobjtree.hxx"\
	"..\ctopobj.hxx"\
	"..\gewbaum.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompdef.h"\
	"..\kompdll.hxx"\
	"..\kompgew.hxx"\
	"..\komphead.hxx"\
	"..\kompias.h"\
	"..\kompias.hxx"\
	"..\kompp.hxx"\
	"..\kompprof.hxx"\
	"..\kompwin.hxx"\
	"..\kpstatus.hxx"\
	"..\triasdef.h"\
	"..\versio16.h"\
	"..\version.h"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\bscrguid.h"\
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
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\OLEGUID.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_KOMPME=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"C:\TRIASDEV.MVC\Include\dc.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

"$(INTDIR)\Kompmenu.obj" : $(SOURCE) $(DEP_CPP_KOMPME) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Triasdev.mvc\Xtension\Kompias\Vobjprop.cxx

!IF  "$(CFG)" == "komp32 - Win32 Release"

DEP_CPP_VOBJP=\
	"..\about.h"\
	"..\about.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompdef.h"\
	"..\kompias.h"\
	"..\kompp.hxx"\
	"..\triasdef.h"\
	"..\version.h"\
	"..\vobjprop.hxx"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
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
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_VOBJP=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"..\versio16.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

"$(INTDIR)\Vobjprop.obj" : $(SOURCE) $(DEP_CPP_VOBJP) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "komp32 - Win32 Debug"

DEP_CPP_VOBJP=\
	"..\about.h"\
	"..\about.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompdef.h"\
	"..\kompias.h"\
	"..\kompp.hxx"\
	"..\triasdef.h"\
	"..\versio16.h"\
	"..\version.h"\
	"..\vobjprop.hxx"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
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
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_VOBJP=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Vobjprop.obj" : $(SOURCE) $(DEP_CPP_VOBJP) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(BuildCmds)

"$(INTDIR)\Vobjprop.sbr" : $(SOURCE) $(DEP_CPP_VOBJP) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "komp32 - Win32 Pseudodebug"

DEP_CPP_VOBJP=\
	"..\about.h"\
	"..\about.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompdef.h"\
	"..\kompias.h"\
	"..\kompp.hxx"\
	"..\triasdef.h"\
	"..\versio16.h"\
	"..\version.h"\
	"..\vobjprop.hxx"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
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
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_VOBJP=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

"$(INTDIR)\Vobjprop.obj" : $(SOURCE) $(DEP_CPP_VOBJP) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Triasdev.mvc\Xtension\Kompias\Kompsimu.cxx

!IF  "$(CFG)" == "komp32 - Win32 Release"

DEP_CPP_KOMPS=\
	"..\about.hxx"\
	"..\cobjtree.hxx"\
	"..\gewbaum.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompdef.h"\
	"..\kompdll.hxx"\
	"..\kompias.h"\
	"..\kompias.hxx"\
	"..\kompp.hxx"\
	"..\kompsimu.hxx"\
	"..\triasdef.h"\
	"..\txtedit.hxx"\
	"..\version.h"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\bscrguid.h"\
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
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_KOMPS=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"..\versio16.h"\
	"C:\TRIASDEV.MVC\Include\dc.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

"$(INTDIR)\Kompsimu.obj" : $(SOURCE) $(DEP_CPP_KOMPS) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "komp32 - Win32 Debug"

DEP_CPP_KOMPS=\
	"..\about.hxx"\
	"..\cobjtree.hxx"\
	"..\gewbaum.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompdef.h"\
	"..\kompdll.hxx"\
	"..\kompias.h"\
	"..\kompias.hxx"\
	"..\kompp.hxx"\
	"..\kompsimu.hxx"\
	"..\triasdef.h"\
	"..\txtedit.hxx"\
	"..\version.h"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\bscrguid.h"\
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
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_KOMPS=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"..\versio16.h"\
	"C:\TRIASDEV.MVC\Include\dc.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Kompsimu.obj" : $(SOURCE) $(DEP_CPP_KOMPS) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(BuildCmds)

"$(INTDIR)\Kompsimu.sbr" : $(SOURCE) $(DEP_CPP_KOMPS) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "komp32 - Win32 Pseudodebug"

DEP_CPP_KOMPS=\
	"..\about.hxx"\
	"..\cobjtree.hxx"\
	"..\gewbaum.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompdef.h"\
	"..\kompdll.hxx"\
	"..\kompias.h"\
	"..\kompias.hxx"\
	"..\kompp.hxx"\
	"..\kompsimu.hxx"\
	"..\triasdef.h"\
	"..\txtedit.hxx"\
	"..\version.h"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\bscrguid.h"\
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
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_KOMPS=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"..\versio16.h"\
	"C:\TRIASDEV.MVC\Include\dc.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

"$(INTDIR)\Kompsimu.obj" : $(SOURCE) $(DEP_CPP_KOMPS) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Triasdev.mvc\Xtension\Kompias\Kpstatus.cxx

!IF  "$(CFG)" == "komp32 - Win32 Release"

DEP_CPP_KPSTA=\
	"..\about.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompdef.h"\
	"..\kompias.h"\
	"..\kompp.hxx"\
	"..\kpstatus.hxx"\
	"..\triasdef.h"\
	"..\version.h"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
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
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\statguid.h"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\TRiASHelper_i.c"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_KPSTA=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"..\versio16.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

"$(INTDIR)\Kpstatus.obj" : $(SOURCE) $(DEP_CPP_KPSTA) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "komp32 - Win32 Debug"

DEP_CPP_KPSTA=\
	"..\about.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompdef.h"\
	"..\kompias.h"\
	"..\kompp.hxx"\
	"..\kpstatus.hxx"\
	"..\triasdef.h"\
	"..\versio16.h"\
	"..\version.h"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
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
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\statguid.h"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\TRiASHelper_i.c"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_KPSTA=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Kpstatus.obj" : $(SOURCE) $(DEP_CPP_KPSTA) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(BuildCmds)

"$(INTDIR)\Kpstatus.sbr" : $(SOURCE) $(DEP_CPP_KPSTA) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "komp32 - Win32 Pseudodebug"

DEP_CPP_KPSTA=\
	"..\about.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompdef.h"\
	"..\kompias.h"\
	"..\kompp.hxx"\
	"..\kpstatus.hxx"\
	"..\triasdef.h"\
	"..\versio16.h"\
	"..\version.h"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
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
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\statguid.h"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\TRiASHelper_i.c"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_KPSTA=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

"$(INTDIR)\Kpstatus.obj" : $(SOURCE) $(DEP_CPP_KPSTA) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Triasdev.mvc\Xtension\Kompias\Ctopobj.cxx

!IF  "$(CFG)" == "komp32 - Win32 Release"

DEP_CPP_CTOPO=\
	"..\about.h"\
	"..\cobjtree.hxx"\
	"..\ctopobj.hxx"\
	"..\gewbaum.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompdef.h"\
	"..\kompdll.hxx"\
	"..\kompgew.hxx"\
	"..\komphead.hxx"\
	"..\kompias.h"\
	"..\kompias.hxx"\
	"..\kompp.hxx"\
	"..\kpstatus.hxx"\
	"..\triasdef.h"\
	"..\version.h"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\bscrguid.h"\
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
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\OPERGUID.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\TRELGUID.H"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
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
	
NODEP_CPP_CTOPO=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"..\versio16.h"\
	"C:\TRIASDEV.MVC\Include\dc.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

"$(INTDIR)\Ctopobj.obj" : $(SOURCE) $(DEP_CPP_CTOPO) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "komp32 - Win32 Debug"

DEP_CPP_CTOPO=\
	"..\about.h"\
	"..\cobjtree.hxx"\
	"..\ctopobj.hxx"\
	"..\gewbaum.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompdef.h"\
	"..\kompdll.hxx"\
	"..\kompgew.hxx"\
	"..\komphead.hxx"\
	"..\kompias.h"\
	"..\kompias.hxx"\
	"..\kompp.hxx"\
	"..\kpstatus.hxx"\
	"..\triasdef.h"\
	"..\versio16.h"\
	"..\version.h"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\bscrguid.h"\
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
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\OPERGUID.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\TRELGUID.H"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
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
	
NODEP_CPP_CTOPO=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"C:\TRIASDEV.MVC\Include\dc.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Ctopobj.obj" : $(SOURCE) $(DEP_CPP_CTOPO) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(BuildCmds)

"$(INTDIR)\Ctopobj.sbr" : $(SOURCE) $(DEP_CPP_CTOPO) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "komp32 - Win32 Pseudodebug"

DEP_CPP_CTOPO=\
	"..\about.h"\
	"..\cobjtree.hxx"\
	"..\ctopobj.hxx"\
	"..\gewbaum.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompdef.h"\
	"..\kompdll.hxx"\
	"..\kompgew.hxx"\
	"..\komphead.hxx"\
	"..\kompias.h"\
	"..\kompias.hxx"\
	"..\kompp.hxx"\
	"..\kpstatus.hxx"\
	"..\triasdef.h"\
	"..\versio16.h"\
	"..\version.h"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\bscrguid.h"\
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
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\OPERGUID.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\TRELGUID.H"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
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
	
NODEP_CPP_CTOPO=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"C:\TRIASDEV.MVC\Include\dc.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

"$(INTDIR)\Ctopobj.obj" : $(SOURCE) $(DEP_CPP_CTOPO) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Triasdev.mvc\Xtension\Kompias\Cobjtree.cxx
DEP_CPP_COBJT=\
	"..\about.h"\
	"..\about.hxx"\
	"..\cobjtree.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompdef.h"\
	"..\kompias.h"\
	"..\kompp.hxx"\
	"..\triasdef.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
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
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_COBJT=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

!IF  "$(CFG)" == "komp32 - Win32 Release"


"$(INTDIR)\Cobjtree.obj" : $(SOURCE) $(DEP_CPP_COBJT) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "komp32 - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Cobjtree.obj" : $(SOURCE) $(DEP_CPP_COBJT) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(BuildCmds)

"$(INTDIR)\Cobjtree.sbr" : $(SOURCE) $(DEP_CPP_COBJT) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "komp32 - Win32 Pseudodebug"


"$(INTDIR)\Cobjtree.obj" : $(SOURCE) $(DEP_CPP_COBJT) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Triasdev.mvc\Xtension\Kompias\Cobjkomp.cxx

!IF  "$(CFG)" == "komp32 - Win32 Release"

DEP_CPP_COBJK=\
	"..\about.h"\
	"..\about.hxx"\
	"..\cobjtree.hxx"\
	"..\ctopobj.hxx"\
	"..\gewbaum.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompcls.hxx"\
	"..\kompdef.h"\
	"..\kompdll.hxx"\
	"..\kompgew.hxx"\
	"..\komphead.hxx"\
	"..\kompias.h"\
	"..\kompias.hxx"\
	"..\kompp.hxx"\
	"..\kompwin.hxx"\
	"..\kpstatus.hxx"\
	"..\triasdef.h"\
	"..\version.h"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\bscrguid.h"\
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
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\OLEGUID.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TRiASHelper_i.c"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_COBJK=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"..\versio16.h"\
	"C:\TRIASDEV.MVC\Include\dc.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

"$(INTDIR)\Cobjkomp.obj" : $(SOURCE) $(DEP_CPP_COBJK) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "komp32 - Win32 Debug"

DEP_CPP_COBJK=\
	"..\about.h"\
	"..\about.hxx"\
	"..\cobjtree.hxx"\
	"..\ctopobj.hxx"\
	"..\gewbaum.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompcls.hxx"\
	"..\kompdef.h"\
	"..\kompdll.hxx"\
	"..\kompgew.hxx"\
	"..\komphead.hxx"\
	"..\kompias.h"\
	"..\kompias.hxx"\
	"..\kompp.hxx"\
	"..\kompwin.hxx"\
	"..\kpstatus.hxx"\
	"..\triasdef.h"\
	"..\versio16.h"\
	"..\version.h"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\bscrguid.h"\
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
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\OLEGUID.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TRiASHelper_i.c"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_COBJK=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"C:\TRIASDEV.MVC\Include\dc.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Cobjkomp.obj" : $(SOURCE) $(DEP_CPP_COBJK) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(BuildCmds)

"$(INTDIR)\Cobjkomp.sbr" : $(SOURCE) $(DEP_CPP_COBJK) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "komp32 - Win32 Pseudodebug"

DEP_CPP_COBJK=\
	"..\about.h"\
	"..\about.hxx"\
	"..\cobjtree.hxx"\
	"..\ctopobj.hxx"\
	"..\gewbaum.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompcls.hxx"\
	"..\kompdef.h"\
	"..\kompdll.hxx"\
	"..\kompgew.hxx"\
	"..\komphead.hxx"\
	"..\kompias.h"\
	"..\kompias.hxx"\
	"..\kompp.hxx"\
	"..\kompwin.hxx"\
	"..\kpstatus.hxx"\
	"..\triasdef.h"\
	"..\versio16.h"\
	"..\version.h"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\bscrguid.h"\
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
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\OLEGUID.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TRiASHelper_i.c"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_COBJK=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"C:\TRIASDEV.MVC\Include\dc.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

"$(INTDIR)\Cobjkomp.obj" : $(SOURCE) $(DEP_CPP_COBJK) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Triasdev.mvc\Xtension\Kompias\Kompcls.cxx
DEP_CPP_KOMPC=\
	"..\about.h"\
	"..\about.hxx"\
	"..\cobjtree.hxx"\
	"..\gewbaum.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompcls.hxx"\
	"..\kompdef.h"\
	"..\kompias.h"\
	"..\kompp.hxx"\
	"..\kpstatus.hxx"\
	"..\triasdec.h"\
	"..\triasdef.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
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
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_KOMPC=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

!IF  "$(CFG)" == "komp32 - Win32 Release"


"$(INTDIR)\Kompcls.obj" : $(SOURCE) $(DEP_CPP_KOMPC) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "komp32 - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Kompcls.obj" : $(SOURCE) $(DEP_CPP_KOMPC) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(BuildCmds)

"$(INTDIR)\Kompcls.sbr" : $(SOURCE) $(DEP_CPP_KOMPC) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "komp32 - Win32 Pseudodebug"


"$(INTDIR)\Kompcls.obj" : $(SOURCE) $(DEP_CPP_KOMPC) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Triasdev.mvc\Xtension\Kompias\Kompprof.cxx

!IF  "$(CFG)" == "komp32 - Win32 Release"

DEP_CPP_KOMPPR=\
	"..\about.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompdef.h"\
	"..\kompias.h"\
	"..\kompp.hxx"\
	"..\kompprof.hxx"\
	"..\version.h"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
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
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_KOMPPR=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"..\versio16.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

"$(INTDIR)\Kompprof.obj" : $(SOURCE) $(DEP_CPP_KOMPPR) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "komp32 - Win32 Debug"

DEP_CPP_KOMPPR=\
	"..\about.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompdef.h"\
	"..\kompias.h"\
	"..\kompp.hxx"\
	"..\kompprof.hxx"\
	"..\versio16.h"\
	"..\version.h"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
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
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_KOMPPR=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Kompprof.obj" : $(SOURCE) $(DEP_CPP_KOMPPR) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(BuildCmds)

"$(INTDIR)\Kompprof.sbr" : $(SOURCE) $(DEP_CPP_KOMPPR) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "komp32 - Win32 Pseudodebug"

DEP_CPP_KOMPPR=\
	"..\about.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompdef.h"\
	"..\kompias.h"\
	"..\kompp.hxx"\
	"..\kompprof.hxx"\
	"..\versio16.h"\
	"..\version.h"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
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
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_KOMPPR=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

"$(INTDIR)\Kompprof.obj" : $(SOURCE) $(DEP_CPP_KOMPPR) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Triasdev.mvc\Xtension\Kompias\Komppage.cpp
DEP_CPP_KOMPPA=\
	"..\cobjtree.hxx"\
	"..\ctopobj.hxx"\
	"..\gewbaum.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompdef.h"\
	"..\kompdll.hxx"\
	"..\kompgew.hxx"\
	"..\kompguid.h"\
	"..\komphead.hxx"\
	"..\kompias.h"\
	"..\kompias.hxx"\
	"..\kompp.hxx"\
	"..\komppage.h"\
	"..\triasdef.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\bscrguid.h"\
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
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\IXTNEXT.HXX"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\OLEGUID.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
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
	
NODEP_CPP_KOMPPA=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"C:\TRIASDEV.MVC\Include\dc.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

!IF  "$(CFG)" == "komp32 - Win32 Release"


"$(INTDIR)\Komppage.obj" : $(SOURCE) $(DEP_CPP_KOMPPA) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "komp32 - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Komppage.obj" : $(SOURCE) $(DEP_CPP_KOMPPA) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(BuildCmds)

"$(INTDIR)\Komppage.sbr" : $(SOURCE) $(DEP_CPP_KOMPPA) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "komp32 - Win32 Pseudodebug"


"$(INTDIR)\Komppage.obj" : $(SOURCE) $(DEP_CPP_KOMPPA) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Triasdev.mvc\Xtension\Kompias\Datahelp.cxx

!IF  "$(CFG)" == "komp32 - Win32 Release"

DEP_CPP_DATAH=\
	"..\about.h"\
	"..\about.hxx"\
	"..\cobjtree.hxx"\
	"..\ctopobj.hxx"\
	"..\gewbaum.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompcls.hxx"\
	"..\kompdef.h"\
	"..\kompdll.hxx"\
	"..\kompgew.hxx"\
	"..\komphead.hxx"\
	"..\kompias.h"\
	"..\kompias.hxx"\
	"..\kompp.hxx"\
	"..\kompwin.hxx"\
	"..\kpstatus.hxx"\
	"..\triasdec.h"\
	"..\triasdef.h"\
	"..\version.h"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\bscrguid.h"\
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
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Hdrentrx.hxx"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\OLEGUID.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_DATAH=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"..\versio16.h"\
	"C:\TRIASDEV.MVC\Include\dc.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

"$(INTDIR)\Datahelp.obj" : $(SOURCE) $(DEP_CPP_DATAH) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "komp32 - Win32 Debug"

DEP_CPP_DATAH=\
	"..\about.h"\
	"..\about.hxx"\
	"..\cobjtree.hxx"\
	"..\ctopobj.hxx"\
	"..\gewbaum.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompcls.hxx"\
	"..\kompdef.h"\
	"..\kompdll.hxx"\
	"..\kompgew.hxx"\
	"..\komphead.hxx"\
	"..\kompias.h"\
	"..\kompias.hxx"\
	"..\kompp.hxx"\
	"..\kompwin.hxx"\
	"..\kpstatus.hxx"\
	"..\triasdec.h"\
	"..\triasdef.h"\
	"..\versio16.h"\
	"..\version.h"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\bscrguid.h"\
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
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Hdrentrx.hxx"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\OLEGUID.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_DATAH=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"C:\TRIASDEV.MVC\Include\dc.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Datahelp.obj" : $(SOURCE) $(DEP_CPP_DATAH) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(BuildCmds)

"$(INTDIR)\Datahelp.sbr" : $(SOURCE) $(DEP_CPP_DATAH) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "komp32 - Win32 Pseudodebug"

DEP_CPP_DATAH=\
	"..\about.h"\
	"..\about.hxx"\
	"..\cobjtree.hxx"\
	"..\ctopobj.hxx"\
	"..\gewbaum.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompcls.hxx"\
	"..\kompdef.h"\
	"..\kompdll.hxx"\
	"..\kompgew.hxx"\
	"..\komphead.hxx"\
	"..\kompias.h"\
	"..\kompias.hxx"\
	"..\kompp.hxx"\
	"..\kompwin.hxx"\
	"..\kpstatus.hxx"\
	"..\triasdec.h"\
	"..\triasdef.h"\
	"..\versio16.h"\
	"..\version.h"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\bscrguid.h"\
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
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Hdrentrx.hxx"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\OLEGUID.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_DATAH=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"C:\TRIASDEV.MVC\Include\dc.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

"$(INTDIR)\Datahelp.obj" : $(SOURCE) $(DEP_CPP_DATAH) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Triasdev.mvc\Xtension\Kompias\Trgeom.cxx

!IF  "$(CFG)" == "komp32 - Win32 Release"

DEP_CPP_TRGEO=\
	"..\about.h"\
	"..\about.hxx"\
	"..\cobjtree.hxx"\
	"..\gewbaum.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompdef.h"\
	"..\kompdll.hxx"\
	"..\kompgew.hxx"\
	"..\komphead.hxx"\
	"..\kompias.h"\
	"..\kompias.hxx"\
	"..\kompp.hxx"\
	"..\kompwin.hxx"\
	"..\kpstatus.hxx"\
	"..\triasdef.h"\
	"..\version.h"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\bscrguid.h"\
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
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Hdrentrx.hxx"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\OLEGUID.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_TRGEO=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"..\versio16.h"\
	"C:\TRIASDEV.MVC\Include\dc.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

"$(INTDIR)\Trgeom.obj" : $(SOURCE) $(DEP_CPP_TRGEO) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "komp32 - Win32 Debug"

DEP_CPP_TRGEO=\
	"..\about.h"\
	"..\about.hxx"\
	"..\cobjtree.hxx"\
	"..\gewbaum.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompdef.h"\
	"..\kompdll.hxx"\
	"..\kompgew.hxx"\
	"..\komphead.hxx"\
	"..\kompias.h"\
	"..\kompias.hxx"\
	"..\kompp.hxx"\
	"..\kompwin.hxx"\
	"..\kpstatus.hxx"\
	"..\triasdef.h"\
	"..\versio16.h"\
	"..\version.h"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\bscrguid.h"\
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
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Hdrentrx.hxx"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\OLEGUID.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_TRGEO=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"C:\TRIASDEV.MVC\Include\dc.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Trgeom.obj" : $(SOURCE) $(DEP_CPP_TRGEO) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(BuildCmds)

"$(INTDIR)\Trgeom.sbr" : $(SOURCE) $(DEP_CPP_TRGEO) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "komp32 - Win32 Pseudodebug"

DEP_CPP_TRGEO=\
	"..\about.h"\
	"..\about.hxx"\
	"..\cobjtree.hxx"\
	"..\gewbaum.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompdef.h"\
	"..\kompdll.hxx"\
	"..\kompgew.hxx"\
	"..\komphead.hxx"\
	"..\kompias.h"\
	"..\kompias.hxx"\
	"..\kompp.hxx"\
	"..\kompwin.hxx"\
	"..\kpstatus.hxx"\
	"..\triasdef.h"\
	"..\versio16.h"\
	"..\version.h"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\bscrguid.h"\
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
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Hdrentrx.hxx"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\OLEGUID.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_TRGEO=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"C:\TRIASDEV.MVC\Include\dc.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

"$(INTDIR)\Trgeom.obj" : $(SOURCE) $(DEP_CPP_TRGEO) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Triasdev.mvc\Xtension\Kompias\Kpbauw.cxx

!IF  "$(CFG)" == "komp32 - Win32 Release"

DEP_CPP_KPBAU=\
	"..\about.h"\
	"..\about.hxx"\
	"..\cobjtree.hxx"\
	"..\ctopobj.hxx"\
	"..\gewbaum.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompdef.h"\
	"..\kompdll.hxx"\
	"..\komphead.hxx"\
	"..\kompias.h"\
	"..\kompias.hxx"\
	"..\kompp.hxx"\
	"..\triasdef.h"\
	"..\version.h"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\bscrguid.h"\
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
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IENUMONR.HXX"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\OLEGUID.H"\
	{$(INCLUDE)}"\OPERGUID.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\TRELGUID.H"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_KPBAU=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"..\versio16.h"\
	"C:\TRIASDEV.MVC\Include\dc.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

"$(INTDIR)\Kpbauw.obj" : $(SOURCE) $(DEP_CPP_KPBAU) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "komp32 - Win32 Debug"

DEP_CPP_KPBAU=\
	"..\about.h"\
	"..\about.hxx"\
	"..\cobjtree.hxx"\
	"..\ctopobj.hxx"\
	"..\gewbaum.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompdef.h"\
	"..\kompdll.hxx"\
	"..\komphead.hxx"\
	"..\kompias.h"\
	"..\kompias.hxx"\
	"..\kompp.hxx"\
	"..\triasdef.h"\
	"..\versio16.h"\
	"..\version.h"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\bscrguid.h"\
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
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IENUMONR.HXX"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\OLEGUID.H"\
	{$(INCLUDE)}"\OPERGUID.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\TRELGUID.H"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_KPBAU=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"C:\TRIASDEV.MVC\Include\dc.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Kpbauw.obj" : $(SOURCE) $(DEP_CPP_KPBAU) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(BuildCmds)

"$(INTDIR)\Kpbauw.sbr" : $(SOURCE) $(DEP_CPP_KPBAU) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "komp32 - Win32 Pseudodebug"

DEP_CPP_KPBAU=\
	"..\about.h"\
	"..\about.hxx"\
	"..\cobjtree.hxx"\
	"..\ctopobj.hxx"\
	"..\gewbaum.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompdef.h"\
	"..\kompdll.hxx"\
	"..\komphead.hxx"\
	"..\kompias.h"\
	"..\kompias.hxx"\
	"..\kompp.hxx"\
	"..\triasdef.h"\
	"..\versio16.h"\
	"..\version.h"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\bscrguid.h"\
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
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IENUMONR.HXX"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\OLEGUID.H"\
	{$(INCLUDE)}"\OPERGUID.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\TRELGUID.H"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_KPBAU=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"C:\TRIASDEV.MVC\Include\dc.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

"$(INTDIR)\Kpbauw.obj" : $(SOURCE) $(DEP_CPP_KPBAU) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Triasdev.mvc\Xtension\Kompias\Kparea.cxx

!IF  "$(CFG)" == "komp32 - Win32 Release"

DEP_CPP_KPARE=\
	"..\about.h"\
	"..\about.hxx"\
	"..\cobjtree.hxx"\
	"..\ctopobj.hxx"\
	"..\gewbaum.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompdef.h"\
	"..\kompdll.hxx"\
	"..\komphead.hxx"\
	"..\kompias.h"\
	"..\kompias.hxx"\
	"..\kompp.hxx"\
	"..\triasdef.h"\
	"..\version.h"\
	"..\vobjprop.hxx"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\bscrguid.h"\
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
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\OLEGUID.H"\
	{$(INCLUDE)}"\OPERGUID.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\TRELGUID.H"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_KPARE=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"..\versio16.h"\
	"C:\TRIASDEV.MVC\Include\dc.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

"$(INTDIR)\Kparea.obj" : $(SOURCE) $(DEP_CPP_KPARE) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "komp32 - Win32 Debug"

DEP_CPP_KPARE=\
	"..\about.h"\
	"..\about.hxx"\
	"..\cobjtree.hxx"\
	"..\ctopobj.hxx"\
	"..\gewbaum.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompdef.h"\
	"..\kompdll.hxx"\
	"..\komphead.hxx"\
	"..\kompias.h"\
	"..\kompias.hxx"\
	"..\kompp.hxx"\
	"..\triasdef.h"\
	"..\versio16.h"\
	"..\version.h"\
	"..\vobjprop.hxx"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\bscrguid.h"\
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
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\OLEGUID.H"\
	{$(INCLUDE)}"\OPERGUID.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\TRELGUID.H"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_KPARE=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"C:\TRIASDEV.MVC\Include\dc.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Kparea.obj" : $(SOURCE) $(DEP_CPP_KPARE) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(BuildCmds)

"$(INTDIR)\Kparea.sbr" : $(SOURCE) $(DEP_CPP_KPARE) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "komp32 - Win32 Pseudodebug"

DEP_CPP_KPARE=\
	"..\about.h"\
	"..\about.hxx"\
	"..\cobjtree.hxx"\
	"..\ctopobj.hxx"\
	"..\gewbaum.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompdef.h"\
	"..\kompdll.hxx"\
	"..\komphead.hxx"\
	"..\kompias.h"\
	"..\kompias.hxx"\
	"..\kompp.hxx"\
	"..\triasdef.h"\
	"..\versio16.h"\
	"..\version.h"\
	"..\vobjprop.hxx"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\bscrguid.h"\
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
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\OLEGUID.H"\
	{$(INCLUDE)}"\OPERGUID.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\TRELGUID.H"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_KPARE=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"C:\TRIASDEV.MVC\Include\dc.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

"$(INTDIR)\Kparea.obj" : $(SOURCE) $(DEP_CPP_KPARE) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Triasdev.mvc\Xtension\Kompias\Kpsymb.cxx

!IF  "$(CFG)" == "komp32 - Win32 Release"

DEP_CPP_KPSYM=\
	"..\about.h"\
	"..\about.hxx"\
	"..\cobjtree.hxx"\
	"..\gewbaum.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompdef.h"\
	"..\kompdll.hxx"\
	"..\kompgew.hxx"\
	"..\komphead.hxx"\
	"..\kompias.h"\
	"..\kompias.hxx"\
	"..\kompp.hxx"\
	"..\kompwin.hxx"\
	"..\kpstatus.hxx"\
	"..\triasdef.h"\
	"..\version.h"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\bscrguid.h"\
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
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\OLEGUID.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_KPSYM=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"..\versio16.h"\
	"C:\TRIASDEV.MVC\Include\dc.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

"$(INTDIR)\Kpsymb.obj" : $(SOURCE) $(DEP_CPP_KPSYM) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "komp32 - Win32 Debug"

DEP_CPP_KPSYM=\
	"..\about.h"\
	"..\about.hxx"\
	"..\cobjtree.hxx"\
	"..\gewbaum.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompdef.h"\
	"..\kompdll.hxx"\
	"..\kompgew.hxx"\
	"..\komphead.hxx"\
	"..\kompias.h"\
	"..\kompias.hxx"\
	"..\kompp.hxx"\
	"..\kompwin.hxx"\
	"..\kpstatus.hxx"\
	"..\triasdef.h"\
	"..\versio16.h"\
	"..\version.h"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\bscrguid.h"\
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
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\OLEGUID.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_KPSYM=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"C:\TRIASDEV.MVC\Include\dc.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Kpsymb.obj" : $(SOURCE) $(DEP_CPP_KPSYM) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(BuildCmds)

"$(INTDIR)\Kpsymb.sbr" : $(SOURCE) $(DEP_CPP_KPSYM) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "komp32 - Win32 Pseudodebug"

DEP_CPP_KPSYM=\
	"..\about.h"\
	"..\about.hxx"\
	"..\cobjtree.hxx"\
	"..\gewbaum.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompdef.h"\
	"..\kompdll.hxx"\
	"..\kompgew.hxx"\
	"..\komphead.hxx"\
	"..\kompias.h"\
	"..\kompias.hxx"\
	"..\kompp.hxx"\
	"..\kompwin.hxx"\
	"..\kpstatus.hxx"\
	"..\triasdef.h"\
	"..\versio16.h"\
	"..\version.h"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\bscrguid.h"\
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
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\OLEGUID.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_KPSYM=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"C:\TRIASDEV.MVC\Include\dc.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

"$(INTDIR)\Kpsymb.obj" : $(SOURCE) $(DEP_CPP_KPSYM) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Triasdev.mvc\Xtension\Kompias\Res\KompaktPageExt.rgs

!IF  "$(CFG)" == "komp32 - Win32 Release"

!ELSEIF  "$(CFG)" == "komp32 - Win32 Debug"

!ELSEIF  "$(CFG)" == "komp32 - Win32 Pseudodebug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\macro\Color.ebs

!IF  "$(CFG)" == "komp32 - Win32 Release"

# Begin Custom Build - Compiling Basic ...
InputPath=.\macro\Color.ebs
InputName=Color

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   bsl -c -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ELSEIF  "$(CFG)" == "komp32 - Win32 Debug"

!ELSEIF  "$(CFG)" == "komp32 - Win32 Pseudodebug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Triasdev.mvc\Xtension\Kompias\Kpbigar.cxx

!IF  "$(CFG)" == "komp32 - Win32 Release"

DEP_CPP_KPBIG=\
	"..\about.h"\
	"..\about.hxx"\
	"..\cobjtree.hxx"\
	"..\ctopobj.hxx"\
	"..\gewbaum.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompcls.hxx"\
	"..\kompdef.h"\
	"..\kompdll.hxx"\
	"..\komphead.hxx"\
	"..\kompias.h"\
	"..\kompias.hxx"\
	"..\kompp.hxx"\
	"..\kpstatus.hxx"\
	"..\triasdec.h"\
	"..\triasdef.h"\
	"..\version.h"\
	"..\vobjprop.hxx"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\bscrguid.h"\
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
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\OLEGUID.H"\
	{$(INCLUDE)}"\OPERGUID.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\TRELGUID.H"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_KPBIG=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"..\versio16.h"\
	"C:\TRIASDEV.MVC\Include\dc.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

"$(INTDIR)\Kpbigar.obj" : $(SOURCE) $(DEP_CPP_KPBIG) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "komp32 - Win32 Debug"

DEP_CPP_KPBIG=\
	"..\about.h"\
	"..\about.hxx"\
	"..\cobjtree.hxx"\
	"..\ctopobj.hxx"\
	"..\gewbaum.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompcls.hxx"\
	"..\kompdef.h"\
	"..\kompdll.hxx"\
	"..\komphead.hxx"\
	"..\kompias.h"\
	"..\kompias.hxx"\
	"..\kompp.hxx"\
	"..\kpstatus.hxx"\
	"..\triasdec.h"\
	"..\triasdef.h"\
	"..\versio16.h"\
	"..\version.h"\
	"..\vobjprop.hxx"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\bscrguid.h"\
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
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\OLEGUID.H"\
	{$(INCLUDE)}"\OPERGUID.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\TRELGUID.H"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_KPBIG=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"C:\TRIASDEV.MVC\Include\dc.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Kpbigar.obj" : $(SOURCE) $(DEP_CPP_KPBIG) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(BuildCmds)

"$(INTDIR)\Kpbigar.sbr" : $(SOURCE) $(DEP_CPP_KPBIG) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "komp32 - Win32 Pseudodebug"

DEP_CPP_KPBIG=\
	"..\about.h"\
	"..\about.hxx"\
	"..\cobjtree.hxx"\
	"..\ctopobj.hxx"\
	"..\gewbaum.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompcls.hxx"\
	"..\kompdef.h"\
	"..\kompdll.hxx"\
	"..\komphead.hxx"\
	"..\kompias.h"\
	"..\kompias.hxx"\
	"..\kompp.hxx"\
	"..\kpstatus.hxx"\
	"..\triasdec.h"\
	"..\triasdef.h"\
	"..\versio16.h"\
	"..\version.h"\
	"..\vobjprop.hxx"\
	".\VERSIO32.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\bscrguid.h"\
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
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\OLEGUID.H"\
	{$(INCLUDE)}"\OPERGUID.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\TRELGUID.H"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_KPBIG=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"C:\TRIASDEV.MVC\Include\dc.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

"$(INTDIR)\Kpbigar.obj" : $(SOURCE) $(DEP_CPP_KPBIG) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\macro\Topolog.ebs

!IF  "$(CFG)" == "komp32 - Win32 Release"

# Begin Custom Build - Compiling Basic ...
InputPath=.\macro\Topolog.ebs
InputName=Topolog

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   bsl -c -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ELSEIF  "$(CFG)" == "komp32 - Win32 Debug"

!ELSEIF  "$(CFG)" == "komp32 - Win32 Pseudodebug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\KOMPIAS\TOOLBAR.CPP
DEP_CPP_TOOLB=\
	"..\AuxUIOwner.h"\
	"..\cobjtree.hxx"\
	"..\ctopobj.hxx"\
	"..\gewbaum.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompdef.h"\
	"..\kompdll.hxx"\
	"..\kompgew.hxx"\
	"..\komphead.hxx"\
	"..\kompias.h"\
	"..\kompias.hxx"\
	"..\kompp.hxx"\
	"..\mynotify.h"\
	"..\triasdef.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\bscrguid.h"\
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
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Itoolbar.h"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\toolguid.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XTSNPROP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_TOOLB=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"C:\TRIASDEV.MVC\Include\dc.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

!IF  "$(CFG)" == "komp32 - Win32 Release"


"$(INTDIR)\TOOLBAR.OBJ" : $(SOURCE) $(DEP_CPP_TOOLB) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "komp32 - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\TOOLBAR.OBJ" : $(SOURCE) $(DEP_CPP_TOOLB) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(BuildCmds)

"$(INTDIR)\TOOLBAR.SBR" : $(SOURCE) $(DEP_CPP_TOOLB) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "komp32 - Win32 Pseudodebug"


"$(INTDIR)\TOOLBAR.OBJ" : $(SOURCE) $(DEP_CPP_TOOLB) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\KOMPIAS\AuxUIOwner.cpp
DEP_CPP_AUXUI=\
	"..\AuxUIOwner.h"\
	"..\cobjtree.hxx"\
	"..\ctopobj.hxx"\
	"..\gewbaum.hxx"\
	"..\KompaktConfig.h"\
	"..\kompaktr.h"\
	"..\kompdef.h"\
	"..\kompdll.hxx"\
	"..\kompgew.hxx"\
	"..\kompguid.h"\
	"..\komphead.hxx"\
	"..\kompias.h"\
	"..\kompias.hxx"\
	"..\kompp.hxx"\
	"..\triasdef.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATL\AtlDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpDebug.h"\
	{$(INCLUDE)}"\ATL\ImageHelpSymbolEngine.h"\
	{$(INCLUDE)}"\ATL\PE_Debug.h"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\bscrguid.h"\
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
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\EB.H"\
	{$(INCLUDE)}"\EBOEM.H"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\HELPTXTX.HXX"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\ICTF.h"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Itoolbar.h"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\IXTNEXT.HXX"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\OLEGUID.H"\
	{$(INCLUDE)}"\ospace\COM\Atl.h"\
	{$(INCLUDE)}"\ospace\COM\atlcomx.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\thread.h"\
	{$(INCLUDE)}"\ospace\except\thread.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
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
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SMARTIF.H"\
	{$(INCLUDE)}"\STDDLG.HXX"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\thread.h"\
	{$(INCLUDE)}"\toolguid.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TRiASConfig.h"\
	{$(INCLUDE)}"\TRiASDB.h"\
	{$(INCLUDE)}"\TRiASDBModuleStrings.h"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\Visinfo.h"\
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
	
NODEP_CPP_AUXUI=\
	"..\..\..\INCLUDE\TRiASBaseInterfaces.h"\
	"..\resource.h"\
	"C:\TRIASDEV.MVC\Include\dc.h"\
	"C:\TRIASDEV.MVC\INCLUDE\TRiASBaseInterfaces.h"\
	"C:\TRIASDEV.MVC\INCLUDE\VisInfoInterfaces.h"\
	

!IF  "$(CFG)" == "komp32 - Win32 Release"


"$(INTDIR)\AuxUIOwner.obj" : $(SOURCE) $(DEP_CPP_AUXUI) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "komp32 - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\AuxUIOwner.obj" : $(SOURCE) $(DEP_CPP_AUXUI) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(BuildCmds)

"$(INTDIR)\AuxUIOwner.sbr" : $(SOURCE) $(DEP_CPP_AUXUI) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "komp32 - Win32 Pseudodebug"


"$(INTDIR)\AuxUIOwner.obj" : $(SOURCE) $(DEP_CPP_AUXUI) "$(INTDIR)"\
 "$(INTDIR)\Komp32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\macro\UeberSchwemmung.ebs

!IF  "$(CFG)" == "komp32 - Win32 Release"

# Begin Custom Build - Compiling Basic ...
InputPath=.\macro\UeberSchwemmung.ebs
InputName=UeberSchwemmung

".\macro\$(InputName).ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   bsl -c -n -o.\macro\$(InputName).ebc .\macro\$(InputName).ebs

# End Custom Build

!ELSEIF  "$(CFG)" == "komp32 - Win32 Debug"

!ELSEIF  "$(CFG)" == "komp32 - Win32 Pseudodebug"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
