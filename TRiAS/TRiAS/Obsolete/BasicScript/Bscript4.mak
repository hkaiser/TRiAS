# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=Bscriptn - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Bscriptn - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Bscriptn - Win32 Release" && "$(CFG)" !=\
 "Bscriptn - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Bscript4.mak" CFG="Bscriptn - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Bscriptn - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Bscriptn - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "Bscriptn - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "Bscriptn - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "win32/Release"
# PROP Intermediate_Dir "win32/Release"
OUTDIR=.\win32/Release
INTDIR=.\win32/Release
# Begin Custom Macros
TargetName=Bscript
# End Custom Macros

ALL : "$(OUTDIR)\Bscript.ext" "c:\trias.mvc\trias200.rel\Bscript.ext"

CLEAN : 
	-@erase "$(INTDIR)\Analimp.obj"
	-@erase "$(INTDIR)\Anpasimp.obj"
	-@erase "$(INTDIR)\bscrext.obj"
	-@erase "$(INTDIR)\BSCREXTF.OBJ"
	-@erase "$(INTDIR)\BSCRIPT.OBJ"
	-@erase "$(INTDIR)\Bscript.pch"
	-@erase "$(INTDIR)\Bscript.res"
	-@erase "$(INTDIR)\BSCRIPTA.OBJ"
	-@erase "$(INTDIR)\BSCRIPTP.OBJ"
	-@erase "$(INTDIR)\Bscrmenu.obj"
	-@erase "$(INTDIR)\Commimp.obj"
	-@erase "$(INTDIR)\Commsi.obj"
	-@erase "$(INTDIR)\Conststr.obj"
	-@erase "$(INTDIR)\CTFGEOGK.OBJ"
	-@erase "$(INTDIR)\custdlg.obj"
	-@erase "$(INTDIR)\CUSTPPXT.OBJ"
	-@erase "$(INTDIR)\Datahelp.obj"
	-@erase "$(INTDIR)\DUMMYPAR.OBJ"
	-@erase "$(INTDIR)\EBARRAY.OBJ"
	-@erase "$(INTDIR)\EBC.OBJ"
	-@erase "$(INTDIR)\ENUMSCPT.OBJ"
	-@erase "$(INTDIR)\filtdlg.obj"
	-@erase "$(INTDIR)\filtscr.obj"
	-@erase "$(INTDIR)\FNDRPLD.OBJ"
	-@erase "$(INTDIR)\list.obj"
	-@erase "$(INTDIR)\MACRO.OBJ"
	-@erase "$(INTDIR)\MACROIMP.OBJ"
	-@erase "$(INTDIR)\Macroorg.obj"
	-@erase "$(INTDIR)\MLONGSTR.OBJ"
	-@erase "$(INTDIR)\MRU.OBJ"
	-@erase "$(INTDIR)\MSTRSTR.OBJ"
	-@erase "$(INTDIR)\PERSTIMP.OBJ"
	-@erase "$(INTDIR)\Procimp.obj"
	-@erase "$(INTDIR)\Propactb.obj"
	-@erase "$(INTDIR)\REXPSTR.OBJ"
	-@erase "$(INTDIR)\runerr.obj"
	-@erase "$(INTDIR)\Runscorg.obj"
	-@erase "$(INTDIR)\saveimp.obj"
	-@erase "$(INTDIR)\SCRPTDLG.OBJ"
	-@erase "$(INTDIR)\STRMIMP.OBJ"
	-@erase "$(INTDIR)\Tmplinst.obj"
	-@erase "$(INTDIR)\Triasext.obj"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\Bscript.exp"
	-@erase "$(OUTDIR)\Bscript.ext"
	-@erase "$(OUTDIR)\Bscript.lib"
	-@erase "c:\trias.mvc\trias200.rel\Bscript.ext"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GR /GX /Zi /O1 /D "NDEBUG" /D "EBWIN32" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D "WIN32" /D "_WINDOWS" /D "__MFC__" /D "_MBCS" /D "_AFXEXT" /D "_AFXDLL" /D "_WINDLL" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D "OS_NO_ALLOCATORS" /D "QI_EXCEPTION" /Fp"win32/Release/Bscript.pch" /Yu"bscriptp.hxx" /c
CPP_PROJ=/nologo /MD /W3 /WX /GR /GX /Zi /O1 /D "NDEBUG" /D "EBWIN32" /D\
 "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D "WIN32" /D "_WINDOWS"\
 /D "__MFC__" /D "_MBCS" /D "_AFXEXT" /D "_AFXDLL" /D "_WINDLL" /D "OS_WIN_95"\
 /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "OS_ALTERNATIVE_STRING_NAMES" /D\
 "OS_MULTI_THREADED" /D "OS_NO_ALLOCATORS" /D "QI_EXCEPTION"\
 /Fp"$(INTDIR)/Bscript.pch" /Yu"bscriptp.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 
CPP_OBJS=.\win32/Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/Bscript.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Bscript4.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ixtmfr42.lib stdcppr.lib cont32r.lib ospace2r.lib ebn.lib stdstrmr.lib /nologo /dll /machine:I386 /stub:"win32/rights.exe" /out:"win32/Release/Bscript.ext" /subsystem:windows,4.0
# SUBTRACT LINK32 /pdb:none /debug
LINK32_FLAGS=ixtmfr42.lib stdcppr.lib cont32r.lib ospace2r.lib ebn.lib\
 stdstrmr.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)/Bscript.pdb"\
 /machine:I386 /def:".\Win32\Bscript.def" /stub:"win32/rights.exe"\
 /out:"$(OUTDIR)/Bscript.ext" /implib:"$(OUTDIR)/Bscript.lib"\
 /subsystem:windows,4.0 
DEF_FILE= \
	".\Win32\Bscript.def"
LINK32_OBJS= \
	"$(INTDIR)\Analimp.obj" \
	"$(INTDIR)\Anpasimp.obj" \
	"$(INTDIR)\bscrext.obj" \
	"$(INTDIR)\BSCREXTF.OBJ" \
	"$(INTDIR)\BSCRIPT.OBJ" \
	"$(INTDIR)\Bscript.res" \
	"$(INTDIR)\BSCRIPTA.OBJ" \
	"$(INTDIR)\BSCRIPTP.OBJ" \
	"$(INTDIR)\Bscrmenu.obj" \
	"$(INTDIR)\Commimp.obj" \
	"$(INTDIR)\Commsi.obj" \
	"$(INTDIR)\Conststr.obj" \
	"$(INTDIR)\CTFGEOGK.OBJ" \
	"$(INTDIR)\custdlg.obj" \
	"$(INTDIR)\CUSTPPXT.OBJ" \
	"$(INTDIR)\Datahelp.obj" \
	"$(INTDIR)\DUMMYPAR.OBJ" \
	"$(INTDIR)\EBARRAY.OBJ" \
	"$(INTDIR)\EBC.OBJ" \
	"$(INTDIR)\ENUMSCPT.OBJ" \
	"$(INTDIR)\filtdlg.obj" \
	"$(INTDIR)\filtscr.obj" \
	"$(INTDIR)\FNDRPLD.OBJ" \
	"$(INTDIR)\list.obj" \
	"$(INTDIR)\MACRO.OBJ" \
	"$(INTDIR)\MACROIMP.OBJ" \
	"$(INTDIR)\Macroorg.obj" \
	"$(INTDIR)\MLONGSTR.OBJ" \
	"$(INTDIR)\MRU.OBJ" \
	"$(INTDIR)\MSTRSTR.OBJ" \
	"$(INTDIR)\PERSTIMP.OBJ" \
	"$(INTDIR)\Procimp.obj" \
	"$(INTDIR)\Propactb.obj" \
	"$(INTDIR)\REXPSTR.OBJ" \
	"$(INTDIR)\runerr.obj" \
	"$(INTDIR)\Runscorg.obj" \
	"$(INTDIR)\saveimp.obj" \
	"$(INTDIR)\SCRPTDLG.OBJ" \
	"$(INTDIR)\STRMIMP.OBJ" \
	"$(INTDIR)\Tmplinst.obj" \
	"$(INTDIR)\Triasext.obj"

"$(OUTDIR)\Bscript.ext" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build
TargetPath=.\win32\Release\Bscript.ext
TargetName=Bscript
InputPath=.\win32\Release\Bscript.ext
SOURCE=$(InputPath)

"c:\trias.mvc\trias200.rel\$(TargetName).ext" : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
   copy $(TargetPath) c:\trias.mvc\trias200.rel

# End Custom Build

!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "win32/Debug"
# PROP Intermediate_Dir "win32/Debug"
OUTDIR=.\win32/Debug
INTDIR=.\win32/Debug
# Begin Custom Macros
TargetName=bscriptd
# End Custom Macros

ALL : "$(OUTDIR)\bscriptd.ext" "$(OUTDIR)\Bscript4.bsc"\
 "c:\trias.mvc\trias200\bscriptd.ext"

CLEAN : 
	-@erase "$(INTDIR)\Analimp.obj"
	-@erase "$(INTDIR)\Analimp.sbr"
	-@erase "$(INTDIR)\Anpasimp.obj"
	-@erase "$(INTDIR)\Anpasimp.sbr"
	-@erase "$(INTDIR)\bscrext.obj"
	-@erase "$(INTDIR)\bscrext.sbr"
	-@erase "$(INTDIR)\BSCREXTF.OBJ"
	-@erase "$(INTDIR)\BSCREXTF.SBR"
	-@erase "$(INTDIR)\bscript.idb"
	-@erase "$(INTDIR)\BSCRIPT.OBJ"
	-@erase "$(INTDIR)\Bscript.pch"
	-@erase "$(INTDIR)\bscript.pdb"
	-@erase "$(INTDIR)\Bscript.res"
	-@erase "$(INTDIR)\BSCRIPT.SBR"
	-@erase "$(INTDIR)\BSCRIPTA.OBJ"
	-@erase "$(INTDIR)\BSCRIPTA.SBR"
	-@erase "$(INTDIR)\BSCRIPTP.OBJ"
	-@erase "$(INTDIR)\BSCRIPTP.SBR"
	-@erase "$(INTDIR)\Bscrmenu.obj"
	-@erase "$(INTDIR)\Bscrmenu.sbr"
	-@erase "$(INTDIR)\Commimp.obj"
	-@erase "$(INTDIR)\Commimp.sbr"
	-@erase "$(INTDIR)\Commsi.obj"
	-@erase "$(INTDIR)\Commsi.sbr"
	-@erase "$(INTDIR)\Conststr.obj"
	-@erase "$(INTDIR)\Conststr.sbr"
	-@erase "$(INTDIR)\CTFGEOGK.OBJ"
	-@erase "$(INTDIR)\CTFGEOGK.SBR"
	-@erase "$(INTDIR)\custdlg.obj"
	-@erase "$(INTDIR)\custdlg.sbr"
	-@erase "$(INTDIR)\CUSTPPXT.OBJ"
	-@erase "$(INTDIR)\CUSTPPXT.SBR"
	-@erase "$(INTDIR)\Datahelp.obj"
	-@erase "$(INTDIR)\Datahelp.sbr"
	-@erase "$(INTDIR)\DUMMYPAR.OBJ"
	-@erase "$(INTDIR)\DUMMYPAR.SBR"
	-@erase "$(INTDIR)\EBARRAY.OBJ"
	-@erase "$(INTDIR)\EBARRAY.SBR"
	-@erase "$(INTDIR)\EBC.OBJ"
	-@erase "$(INTDIR)\EBC.SBR"
	-@erase "$(INTDIR)\ENUMSCPT.OBJ"
	-@erase "$(INTDIR)\ENUMSCPT.SBR"
	-@erase "$(INTDIR)\filtdlg.obj"
	-@erase "$(INTDIR)\filtdlg.sbr"
	-@erase "$(INTDIR)\filtscr.obj"
	-@erase "$(INTDIR)\filtscr.sbr"
	-@erase "$(INTDIR)\FNDRPLD.OBJ"
	-@erase "$(INTDIR)\FNDRPLD.SBR"
	-@erase "$(INTDIR)\list.obj"
	-@erase "$(INTDIR)\list.sbr"
	-@erase "$(INTDIR)\MACRO.OBJ"
	-@erase "$(INTDIR)\MACRO.SBR"
	-@erase "$(INTDIR)\MACROIMP.OBJ"
	-@erase "$(INTDIR)\MACROIMP.SBR"
	-@erase "$(INTDIR)\Macroorg.obj"
	-@erase "$(INTDIR)\Macroorg.sbr"
	-@erase "$(INTDIR)\MLONGSTR.OBJ"
	-@erase "$(INTDIR)\MLONGSTR.SBR"
	-@erase "$(INTDIR)\MRU.OBJ"
	-@erase "$(INTDIR)\MRU.SBR"
	-@erase "$(INTDIR)\MSTRSTR.OBJ"
	-@erase "$(INTDIR)\MSTRSTR.SBR"
	-@erase "$(INTDIR)\PERSTIMP.OBJ"
	-@erase "$(INTDIR)\PERSTIMP.SBR"
	-@erase "$(INTDIR)\Procimp.obj"
	-@erase "$(INTDIR)\Procimp.sbr"
	-@erase "$(INTDIR)\Propactb.obj"
	-@erase "$(INTDIR)\Propactb.sbr"
	-@erase "$(INTDIR)\REXPSTR.OBJ"
	-@erase "$(INTDIR)\REXPSTR.SBR"
	-@erase "$(INTDIR)\runerr.obj"
	-@erase "$(INTDIR)\runerr.sbr"
	-@erase "$(INTDIR)\Runscorg.obj"
	-@erase "$(INTDIR)\Runscorg.sbr"
	-@erase "$(INTDIR)\saveimp.obj"
	-@erase "$(INTDIR)\saveimp.sbr"
	-@erase "$(INTDIR)\SCRPTDLG.OBJ"
	-@erase "$(INTDIR)\SCRPTDLG.SBR"
	-@erase "$(INTDIR)\Stghelp.obj"
	-@erase "$(INTDIR)\Stghelp.sbr"
	-@erase "$(INTDIR)\STRMIMP.OBJ"
	-@erase "$(INTDIR)\STRMIMP.SBR"
	-@erase "$(INTDIR)\Tmplinst.obj"
	-@erase "$(INTDIR)\Tmplinst.sbr"
	-@erase "$(INTDIR)\Triasext.obj"
	-@erase "$(INTDIR)\Triasext.sbr"
	-@erase "$(OUTDIR)\Bscript4.bsc"
	-@erase "$(OUTDIR)\bscriptd.exp"
	-@erase "$(OUTDIR)\bscriptd.ext"
	-@erase "$(OUTDIR)\bscriptd.lib"
	-@erase "$(OUTDIR)\bscriptd.pdb"
	-@erase "c:\trias.mvc\trias200\bscriptd.ext"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(OUTDIR)/BSCRIPTN.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /Gi /GR /GX /Zi /Od /Ob1 /D "_DEBUG" /D "EBWIN32" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D "WIN32" /D "_WINDOWS" /D "__MFC__" /D "_MBCS" /D "_AFXEXT" /D "_AFXDLL" /D "_WINDLL" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D "OS_NO_ALLOCATORS" /D "QI_EXCEPTION" /FR /Fp"win32/Debug/Bscript.pch" /Yu"bscriptp.hxx" /Fd"win32/Debug/bscript.pdb" /c
CPP_PROJ=/nologo /MDd /W3 /WX /Gm /Gi /GR /GX /Zi /Od /Ob1 /D "_DEBUG" /D\
 "EBWIN32" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D "WIN32" /D\
 "_WINDOWS" /D "__MFC__" /D "_MBCS" /D "_AFXEXT" /D "_AFXDLL" /D "_WINDLL" /D\
 "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D\
 "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D "OS_NO_ALLOCATORS" /D\
 "QI_EXCEPTION" /FR"$(INTDIR)/" /Fp"$(INTDIR)/Bscript.pch" /Yu"bscriptp.hxx"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/bscript.pdb" /c 
CPP_OBJS=.\win32/Debug/
CPP_SBRS=.\win32/Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# SUBTRACT RSC /x
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/Bscript.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Bscript4.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Analimp.sbr" \
	"$(INTDIR)\Anpasimp.sbr" \
	"$(INTDIR)\bscrext.sbr" \
	"$(INTDIR)\BSCREXTF.SBR" \
	"$(INTDIR)\BSCRIPT.SBR" \
	"$(INTDIR)\BSCRIPTA.SBR" \
	"$(INTDIR)\BSCRIPTP.SBR" \
	"$(INTDIR)\Bscrmenu.sbr" \
	"$(INTDIR)\Commimp.sbr" \
	"$(INTDIR)\Commsi.sbr" \
	"$(INTDIR)\Conststr.sbr" \
	"$(INTDIR)\CTFGEOGK.SBR" \
	"$(INTDIR)\custdlg.sbr" \
	"$(INTDIR)\CUSTPPXT.SBR" \
	"$(INTDIR)\Datahelp.sbr" \
	"$(INTDIR)\DUMMYPAR.SBR" \
	"$(INTDIR)\EBARRAY.SBR" \
	"$(INTDIR)\EBC.SBR" \
	"$(INTDIR)\ENUMSCPT.SBR" \
	"$(INTDIR)\filtdlg.sbr" \
	"$(INTDIR)\filtscr.sbr" \
	"$(INTDIR)\FNDRPLD.SBR" \
	"$(INTDIR)\list.sbr" \
	"$(INTDIR)\MACRO.SBR" \
	"$(INTDIR)\MACROIMP.SBR" \
	"$(INTDIR)\Macroorg.sbr" \
	"$(INTDIR)\MLONGSTR.SBR" \
	"$(INTDIR)\MRU.SBR" \
	"$(INTDIR)\MSTRSTR.SBR" \
	"$(INTDIR)\PERSTIMP.SBR" \
	"$(INTDIR)\Procimp.sbr" \
	"$(INTDIR)\Propactb.sbr" \
	"$(INTDIR)\REXPSTR.SBR" \
	"$(INTDIR)\runerr.sbr" \
	"$(INTDIR)\Runscorg.sbr" \
	"$(INTDIR)\saveimp.sbr" \
	"$(INTDIR)\SCRPTDLG.SBR" \
	"$(INTDIR)\Stghelp.sbr" \
	"$(INTDIR)\STRMIMP.SBR" \
	"$(INTDIR)\Tmplinst.sbr" \
	"$(INTDIR)\Triasext.sbr"

"$(OUTDIR)\Bscript4.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 ixtmfd42.lib stdcppd.lib cont32d.lib ospace2d.lib ebn.lib stdstrmd.lib /nologo /dll /incremental:no /debug /machine:I386 /nodefaultlib:"nafxcwd.lib" /nodefaultlib:"libcmtd.lib" /stub:"win32/rights.exe" /out:"win32/Debug/bscriptd.ext" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none /nodefaultlib
LINK32_FLAGS=ixtmfd42.lib stdcppd.lib cont32d.lib ospace2d.lib ebn.lib\
 stdstrmd.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)/bscriptd.pdb" /debug\
 /machine:I386 /nodefaultlib:"nafxcwd.lib" /nodefaultlib:"libcmtd.lib"\
 /def:".\Win32\Bscript.def" /stub:"win32/rights.exe"\
 /out:"$(OUTDIR)/bscriptd.ext" /implib:"$(OUTDIR)/bscriptd.lib"\
 /SUBSYSTEM:windows,4.0 
DEF_FILE= \
	".\Win32\Bscript.def"
LINK32_OBJS= \
	"$(INTDIR)\Analimp.obj" \
	"$(INTDIR)\Anpasimp.obj" \
	"$(INTDIR)\bscrext.obj" \
	"$(INTDIR)\BSCREXTF.OBJ" \
	"$(INTDIR)\BSCRIPT.OBJ" \
	"$(INTDIR)\Bscript.res" \
	"$(INTDIR)\BSCRIPTA.OBJ" \
	"$(INTDIR)\BSCRIPTP.OBJ" \
	"$(INTDIR)\Bscrmenu.obj" \
	"$(INTDIR)\Commimp.obj" \
	"$(INTDIR)\Commsi.obj" \
	"$(INTDIR)\Conststr.obj" \
	"$(INTDIR)\CTFGEOGK.OBJ" \
	"$(INTDIR)\custdlg.obj" \
	"$(INTDIR)\CUSTPPXT.OBJ" \
	"$(INTDIR)\Datahelp.obj" \
	"$(INTDIR)\DUMMYPAR.OBJ" \
	"$(INTDIR)\EBARRAY.OBJ" \
	"$(INTDIR)\EBC.OBJ" \
	"$(INTDIR)\ENUMSCPT.OBJ" \
	"$(INTDIR)\filtdlg.obj" \
	"$(INTDIR)\filtscr.obj" \
	"$(INTDIR)\FNDRPLD.OBJ" \
	"$(INTDIR)\list.obj" \
	"$(INTDIR)\MACRO.OBJ" \
	"$(INTDIR)\MACROIMP.OBJ" \
	"$(INTDIR)\Macroorg.obj" \
	"$(INTDIR)\MLONGSTR.OBJ" \
	"$(INTDIR)\MRU.OBJ" \
	"$(INTDIR)\MSTRSTR.OBJ" \
	"$(INTDIR)\PERSTIMP.OBJ" \
	"$(INTDIR)\Procimp.obj" \
	"$(INTDIR)\Propactb.obj" \
	"$(INTDIR)\REXPSTR.OBJ" \
	"$(INTDIR)\runerr.obj" \
	"$(INTDIR)\Runscorg.obj" \
	"$(INTDIR)\saveimp.obj" \
	"$(INTDIR)\SCRPTDLG.OBJ" \
	"$(INTDIR)\Stghelp.obj" \
	"$(INTDIR)\STRMIMP.OBJ" \
	"$(INTDIR)\Tmplinst.obj" \
	"$(INTDIR)\Triasext.obj"

"$(OUTDIR)\bscriptd.ext" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build
TargetPath=.\win32\Debug\bscriptd.ext
TargetName=bscriptd
InputPath=.\win32\Debug\bscriptd.ext
SOURCE=$(InputPath)

"c:\trias.mvc\trias200\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   copy $(TargetPath) c:\trias.mvc\trias200

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

# Name "Bscriptn - Win32 Release"
# Name "Bscriptn - Win32 Debug"

!IF  "$(CFG)" == "Bscriptn - Win32 Release"

!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\BSCRIPTP.CXX
DEP_CPP_BSCRI=\
	".\bscrext.hxx"\
	".\bscript.hxx"\
	".\bscriptp.hxx"\
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
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\iterator"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\Triastlb_i.c"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Bscriptn - Win32 Release"

# ADD CPP /Yc"bscriptp.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GR /GX /Zi /O1 /D "NDEBUG" /D "EBWIN32" /D\
 "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D "WIN32" /D "_WINDOWS"\
 /D "__MFC__" /D "_MBCS" /D "_AFXEXT" /D "_AFXDLL" /D "_WINDLL" /D "OS_WIN_95"\
 /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "OS_ALTERNATIVE_STRING_NAMES" /D\
 "OS_MULTI_THREADED" /D "OS_NO_ALLOCATORS" /D "QI_EXCEPTION"\
 /Fp"$(INTDIR)/Bscript.pch" /Yc"bscriptp.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\BSCRIPTP.OBJ" : $(SOURCE) $(DEP_CPP_BSCRI) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Bscript.pch" : $(SOURCE) $(DEP_CPP_BSCRI) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"

# ADD CPP /Yc"bscriptp.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /Gi /GR /GX /Zi /Od /Ob1 /D "_DEBUG" /D\
 "EBWIN32" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D "WIN32" /D\
 "_WINDOWS" /D "__MFC__" /D "_MBCS" /D "_AFXEXT" /D "_AFXDLL" /D "_WINDLL" /D\
 "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D\
 "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D "OS_NO_ALLOCATORS" /D\
 "QI_EXCEPTION" /FR"$(INTDIR)/" /Fp"$(INTDIR)/Bscript.pch" /Yc"bscriptp.hxx"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/bscript.pdb" /c $(SOURCE) \
	

"$(INTDIR)\BSCRIPTP.OBJ" : $(SOURCE) $(DEP_CPP_BSCRI) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\BSCRIPTP.SBR" : $(SOURCE) $(DEP_CPP_BSCRI) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Bscript.pch" : $(SOURCE) $(DEP_CPP_BSCRI) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Bscrmenu.cxx
DEP_CPP_BSCRM=\
	".\bscrext.hxx"\
	".\bscript.h"\
	".\bscript.hxx"\
	".\bscriptp.hxx"\
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
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\iterator"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\Triastlb_i.c"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	
NODEP_CPP_BSCRM=\
	".\bscriptr.h"\
	

!IF  "$(CFG)" == "Bscriptn - Win32 Release"


"$(INTDIR)\Bscrmenu.obj" : $(SOURCE) $(DEP_CPP_BSCRM) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"


"$(INTDIR)\Bscrmenu.obj" : $(SOURCE) $(DEP_CPP_BSCRM) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\Bscrmenu.sbr" : $(SOURCE) $(DEP_CPP_BSCRM) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\BSCRIPT.CXX

!IF  "$(CFG)" == "Bscriptn - Win32 Release"

DEP_CPP_BSCRIP=\
	".\analimp.h"\
	".\anpasimp.h"\
	".\bscript.h"\
	".\bscripta.h"\
	".\bscriptp.hxx"\
	".\commsi.h"\
	".\conststr.h"\
	".\enumscpt.h"\
	".\imacorg.h"\
	".\imacro.h"\
	".\listitem.h"\
	".\macrguid.h"\
	".\macro.h"\
	".\macroimp.h"\
	".\macroorg.h"\
	".\myenum.h"\
	".\perstimp.h"\
	".\procimp.h"\
	".\registry.hxx"\
	".\runerr.h"\
	".\runscorg.h"\
	".\saveimp.h"\
	".\scrptdlg.h"\
	".\strmimp.h"\
	".\toolbarx.h"\
	".\triasext.h"\
	".\version.h"\
	".\waitcur.h"\
	".\Win32\VERSIO32.H"\
	{$(INCLUDE)}"\bscrguid.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\Ipropseq.hxx"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\IXTNEXT.HXX"\
	{$(INCLUDE)}"\OLEGUID.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\propguid.h"\
	{$(INCLUDE)}"\Triastlb_i.c"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\YVALS.H"\
	
NODEP_CPP_BSCRIP=\
	".\bscriptr.h"\
	".\Versio16.h"\
	

"$(INTDIR)\BSCRIPT.OBJ" : $(SOURCE) $(DEP_CPP_BSCRIP) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"

DEP_CPP_BSCRIP=\
	".\analimp.h"\
	".\anpasimp.h"\
	".\bscrext.hxx"\
	".\bscript.h"\
	".\bscript.hxx"\
	".\bscripta.h"\
	".\bscriptp.hxx"\
	".\commsi.h"\
	".\conststr.h"\
	".\enumscpt.h"\
	".\imacorg.h"\
	".\imacro.h"\
	".\listitem.h"\
	".\macrguid.h"\
	".\macro.h"\
	".\macroimp.h"\
	".\macroorg.h"\
	".\myenum.h"\
	".\perstimp.h"\
	".\procimp.h"\
	".\registry.hxx"\
	".\runerr.h"\
	".\runscorg.h"\
	".\saveimp.h"\
	".\scrptdlg.h"\
	".\strmimp.h"\
	".\toolbarx.h"\
	".\triasext.h"\
	".\version.h"\
	".\waitcur.h"\
	".\Win32\VERSIO32.H"\
	{$(INCLUDE)}"\bscrguid.h"\
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
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\Ipropseq.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\IXTNEXT.HXX"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OLEGUID.H"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\iterator"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\propguid.h"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\Triastlb_i.c"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	
NODEP_CPP_BSCRIP=\
	".\bscriptr.h"\
	".\Versio16.h"\
	

"$(INTDIR)\BSCRIPT.OBJ" : $(SOURCE) $(DEP_CPP_BSCRIP) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\BSCRIPT.SBR" : $(SOURCE) $(DEP_CPP_BSCRIP) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\bscrext.cxx
DEP_CPP_BSCRE=\
	".\bscrext.hxx"\
	".\bscript.hxx"\
	".\bscriptp.hxx"\
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
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\iterator"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\Triastlb_i.c"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Bscriptn - Win32 Release"


"$(INTDIR)\bscrext.obj" : $(SOURCE) $(DEP_CPP_BSCRE) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"


"$(INTDIR)\bscrext.obj" : $(SOURCE) $(DEP_CPP_BSCRE) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\bscrext.sbr" : $(SOURCE) $(DEP_CPP_BSCRE) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\BSCRIPTA.CPP
DEP_CPP_BSCRIPT=\
	".\bscrext.hxx"\
	".\bscript.h"\
	".\bscript.hxx"\
	".\bscripta.h"\
	".\bscriptp.hxx"\
	".\conststr.h"\
	".\dummypar.h"\
	".\enumscpt.h"\
	".\fndrpld.h"\
	".\imacorg.h"\
	".\imacro.h"\
	".\macrguid.h"\
	".\mru.h"\
	".\registry.hxx"\
	".\runerr.h"\
	".\scrptdlg.h"\
	".\toolbarx.h"\
	".\waitcur.h"\
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
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OLEGUID.H"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\iterator"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\Triastlb_i.c"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	
NODEP_CPP_BSCRIPT=\
	".\bscriptr.h"\
	

!IF  "$(CFG)" == "Bscriptn - Win32 Release"


"$(INTDIR)\BSCRIPTA.OBJ" : $(SOURCE) $(DEP_CPP_BSCRIPT) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"


"$(INTDIR)\BSCRIPTA.OBJ" : $(SOURCE) $(DEP_CPP_BSCRIPT) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\BSCRIPTA.SBR" : $(SOURCE) $(DEP_CPP_BSCRIPT) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DUMMYPAR.CPP
DEP_CPP_DUMMY=\
	".\bscrext.hxx"\
	".\bscript.h"\
	".\bscript.hxx"\
	".\bscriptp.hxx"\
	".\dummypar.h"\
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
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\iterator"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\Triastlb_i.c"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	
NODEP_CPP_DUMMY=\
	".\bscriptr.h"\
	

!IF  "$(CFG)" == "Bscriptn - Win32 Release"


"$(INTDIR)\DUMMYPAR.OBJ" : $(SOURCE) $(DEP_CPP_DUMMY) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"


"$(INTDIR)\DUMMYPAR.OBJ" : $(SOURCE) $(DEP_CPP_DUMMY) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\DUMMYPAR.SBR" : $(SOURCE) $(DEP_CPP_DUMMY) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MRU.CPP
DEP_CPP_MRU_C=\
	".\bscrext.hxx"\
	".\bscript.hxx"\
	".\bscriptp.hxx"\
	".\mru.h"\
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
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\iterator"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\Triastlb_i.c"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Bscriptn - Win32 Release"


"$(INTDIR)\MRU.OBJ" : $(SOURCE) $(DEP_CPP_MRU_C) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"


"$(INTDIR)\MRU.OBJ" : $(SOURCE) $(DEP_CPP_MRU_C) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\MRU.SBR" : $(SOURCE) $(DEP_CPP_MRU_C) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\EBARRAY.CXX
DEP_CPP_EBARR=\
	".\bscrext.hxx"\
	".\bscript.hxx"\
	".\bscriptp.hxx"\
	".\ebarray.hxx"\
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
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\iterator"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\Triastlb_i.c"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Bscriptn - Win32 Release"


"$(INTDIR)\EBARRAY.OBJ" : $(SOURCE) $(DEP_CPP_EBARR) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"


"$(INTDIR)\EBARRAY.OBJ" : $(SOURCE) $(DEP_CPP_EBARR) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\EBARRAY.SBR" : $(SOURCE) $(DEP_CPP_EBARR) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\EBC.CPP
DEP_CPP_EBC_C=\
	".\bscrext.hxx"\
	".\bscript.hxx"\
	".\bscriptp.hxx"\
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
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\iterator"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\Triastlb_i.c"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Bscriptn - Win32 Release"

# PROP Exclude_From_Build 0

"$(INTDIR)\EBC.OBJ" : $(SOURCE) $(DEP_CPP_EBC_C) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"

# PROP Exclude_From_Build 0

"$(INTDIR)\EBC.OBJ" : $(SOURCE) $(DEP_CPP_EBC_C) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\EBC.SBR" : $(SOURCE) $(DEP_CPP_EBC_C) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MACRO.CPP
DEP_CPP_MACRO=\
	".\bscrext.hxx"\
	".\bscript.hxx"\
	".\bscriptp.hxx"\
	".\enumscpt.h"\
	".\imacro.h"\
	".\macrguid.h"\
	".\macro.h"\
	".\macroimp.h"\
	".\perstimp.h"\
	".\strmimp.h"\
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
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\iterator"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\Triastlb_i.c"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Bscriptn - Win32 Release"


"$(INTDIR)\MACRO.OBJ" : $(SOURCE) $(DEP_CPP_MACRO) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"


"$(INTDIR)\MACRO.OBJ" : $(SOURCE) $(DEP_CPP_MACRO) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\MACRO.SBR" : $(SOURCE) $(DEP_CPP_MACRO) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MACROIMP.CPP
DEP_CPP_MACROI=\
	".\bscrext.hxx"\
	".\bscript.h"\
	".\bscript.hxx"\
	".\bscriptp.hxx"\
	".\enumscpt.h"\
	".\imacorg.h"\
	".\imacro.h"\
	".\macrguid.h"\
	".\macro.h"\
	".\macroimp.h"\
	".\perstimp.h"\
	".\strmimp.h"\
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
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\rtti\cast.h"\
	{$(INCLUDE)}"\ospace\rtti\cast.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\rtti\regmacro.h"\
	{$(INCLUDE)}"\ospace\rtti\rtti.h"\
	{$(INCLUDE)}"\ospace\rtti\smacros.h"\
	{$(INCLUDE)}"\ospace\source.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\iterator"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\bstream.h"\
	{$(INCLUDE)}"\ospace\stream\bstream.ipp"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\stream\protocol.h"\
	{$(INCLUDE)}"\ospace\stream\protocol.ipp"\
	{$(INCLUDE)}"\ospace\stream\rtti.h"\
	{$(INCLUDE)}"\ospace\stream\smacros.h"\
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
	{$(INCLUDE)}"\ospace\type\types.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\Triastlb_i.c"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	
NODEP_CPP_MACROI=\
	".\bscriptr.h"\
	

!IF  "$(CFG)" == "Bscriptn - Win32 Release"


"$(INTDIR)\MACROIMP.OBJ" : $(SOURCE) $(DEP_CPP_MACROI) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"


"$(INTDIR)\MACROIMP.OBJ" : $(SOURCE) $(DEP_CPP_MACROI) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\MACROIMP.SBR" : $(SOURCE) $(DEP_CPP_MACROI) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PERSTIMP.CPP
DEP_CPP_PERST=\
	".\bscrext.hxx"\
	".\bscript.h"\
	".\bscript.hxx"\
	".\bscriptp.hxx"\
	".\enumscpt.h"\
	".\imacro.h"\
	".\macrguid.h"\
	".\macro.h"\
	".\macroimp.h"\
	".\perstimp.h"\
	".\strmimp.h"\
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
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\iterator"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\Triastlb_i.c"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	
NODEP_CPP_PERST=\
	".\bscriptr.h"\
	

!IF  "$(CFG)" == "Bscriptn - Win32 Release"


"$(INTDIR)\PERSTIMP.OBJ" : $(SOURCE) $(DEP_CPP_PERST) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"


"$(INTDIR)\PERSTIMP.OBJ" : $(SOURCE) $(DEP_CPP_PERST) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\PERSTIMP.SBR" : $(SOURCE) $(DEP_CPP_PERST) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRMIMP.CPP
DEP_CPP_STRMI=\
	".\bscrext.hxx"\
	".\bscript.hxx"\
	".\bscriptp.hxx"\
	".\enumscpt.h"\
	".\imacro.h"\
	".\macrguid.h"\
	".\macro.h"\
	".\macroimp.h"\
	".\perstimp.h"\
	".\strmimp.h"\
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
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\iterator"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\Triastlb_i.c"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Bscriptn - Win32 Release"


"$(INTDIR)\STRMIMP.OBJ" : $(SOURCE) $(DEP_CPP_STRMI) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"


"$(INTDIR)\STRMIMP.OBJ" : $(SOURCE) $(DEP_CPP_STRMI) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\STRMIMP.SBR" : $(SOURCE) $(DEP_CPP_STRMI) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ENUMSCPT.CPP
DEP_CPP_ENUMS=\
	".\bscrext.hxx"\
	".\bscript.hxx"\
	".\bscriptp.hxx"\
	".\enumscpt.h"\
	".\imacro.h"\
	".\macrguid.h"\
	".\macro.h"\
	".\macroimp.h"\
	".\perstimp.h"\
	".\strmimp.h"\
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
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\iterator"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\Triastlb_i.c"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Bscriptn - Win32 Release"


"$(INTDIR)\ENUMSCPT.OBJ" : $(SOURCE) $(DEP_CPP_ENUMS) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"


"$(INTDIR)\ENUMSCPT.OBJ" : $(SOURCE) $(DEP_CPP_ENUMS) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\ENUMSCPT.SBR" : $(SOURCE) $(DEP_CPP_ENUMS) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SCRPTDLG.CPP
DEP_CPP_SCRPT=\
	".\bscrext.hxx"\
	".\bscript.h"\
	".\bscript.hxx"\
	".\bscriptp.hxx"\
	".\conststr.h"\
	".\enumscpt.h"\
	".\imacorg.h"\
	".\imacro.h"\
	".\macrguid.h"\
	".\macro.h"\
	".\macroimp.h"\
	".\perstimp.h"\
	".\registry.hxx"\
	".\runerr.h"\
	".\runscorg.h"\
	".\scrptdlg.h"\
	".\strmimp.h"\
	".\waitcur.h"\
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
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\iterator"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\Triastlb_i.c"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	
NODEP_CPP_SCRPT=\
	".\bscriptr.h"\
	

!IF  "$(CFG)" == "Bscriptn - Win32 Release"


"$(INTDIR)\SCRPTDLG.OBJ" : $(SOURCE) $(DEP_CPP_SCRPT) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"


"$(INTDIR)\SCRPTDLG.OBJ" : $(SOURCE) $(DEP_CPP_SCRPT) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\SCRPTDLG.SBR" : $(SOURCE) $(DEP_CPP_SCRPT) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CTFGEOGK.CXX
DEP_CPP_CTFGE=\
	".\bscrext.hxx"\
	".\bscript.hxx"\
	".\bscriptp.hxx"\
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
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\iterator"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\Triastlb_i.c"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Bscriptn - Win32 Release"


"$(INTDIR)\CTFGEOGK.OBJ" : $(SOURCE) $(DEP_CPP_CTFGE) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"


"$(INTDIR)\CTFGEOGK.OBJ" : $(SOURCE) $(DEP_CPP_CTFGE) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\CTFGEOGK.SBR" : $(SOURCE) $(DEP_CPP_CTFGE) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MLONGSTR.CXX
DEP_CPP_MLONG=\
	".\bscrext.hxx"\
	".\bscript.hxx"\
	".\bscriptp.hxx"\
	".\mlongstr.hxx"\
	".\mlongstr.inl"\
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
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\iterator"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\Triastlb_i.c"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Bscriptn - Win32 Release"


"$(INTDIR)\MLONGSTR.OBJ" : $(SOURCE) $(DEP_CPP_MLONG) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"


"$(INTDIR)\MLONGSTR.OBJ" : $(SOURCE) $(DEP_CPP_MLONG) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\MLONGSTR.SBR" : $(SOURCE) $(DEP_CPP_MLONG) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MSTRSTR.CXX
DEP_CPP_MSTRS=\
	".\bscrext.hxx"\
	".\bscript.hxx"\
	".\bscriptp.hxx"\
	".\mstrstr.hxx"\
	".\mstrstr.inl"\
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
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\iterator"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\Triastlb_i.c"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Bscriptn - Win32 Release"


"$(INTDIR)\MSTRSTR.OBJ" : $(SOURCE) $(DEP_CPP_MSTRS) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"


"$(INTDIR)\MSTRSTR.OBJ" : $(SOURCE) $(DEP_CPP_MSTRS) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\MSTRSTR.SBR" : $(SOURCE) $(DEP_CPP_MSTRS) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\REXPSTR.CPP
DEP_CPP_REXPS=\
	".\bscrext.hxx"\
	".\bscript.hxx"\
	".\bscriptp.hxx"\
	".\rexpstr.h"\
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
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\iterator"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\Triastlb_i.c"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Bscriptn - Win32 Release"


"$(INTDIR)\REXPSTR.OBJ" : $(SOURCE) $(DEP_CPP_REXPS) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"


"$(INTDIR)\REXPSTR.OBJ" : $(SOURCE) $(DEP_CPP_REXPS) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\REXPSTR.SBR" : $(SOURCE) $(DEP_CPP_REXPS) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\BSCREXTF.CPP
DEP_CPP_BSCREX=\
	".\bscrext.hxx"\
	".\bscrextf.h"\
	".\bscript.hxx"\
	".\bscriptp.hxx"\
	".\ebarray.hxx"\
	".\mlongstr.hxx"\
	".\mlongstr.inl"\
	".\mstrstr.hxx"\
	".\mstrstr.inl"\
	".\rexpstr.h"\
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
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\iterator"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\Triastlb_i.c"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Bscriptn - Win32 Release"


"$(INTDIR)\BSCREXTF.OBJ" : $(SOURCE) $(DEP_CPP_BSCREX) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"


"$(INTDIR)\BSCREXTF.OBJ" : $(SOURCE) $(DEP_CPP_BSCREX) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\BSCREXTF.SBR" : $(SOURCE) $(DEP_CPP_BSCREX) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Commimp.cpp
DEP_CPP_COMMI=\
	".\bscrext.hxx"\
	".\bscript.hxx"\
	".\bscriptp.hxx"\
	".\commimp.h"\
	".\imacorg.h"\
	".\imacro.h"\
	".\macrguid.h"\
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
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\rtti\cast.h"\
	{$(INCLUDE)}"\ospace\rtti\cast.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\rtti\regmacro.h"\
	{$(INCLUDE)}"\ospace\rtti\rtti.h"\
	{$(INCLUDE)}"\ospace\rtti\smacros.h"\
	{$(INCLUDE)}"\ospace\source.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\iterator"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\bstream.h"\
	{$(INCLUDE)}"\ospace\stream\bstream.ipp"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\stream\protocol.h"\
	{$(INCLUDE)}"\ospace\stream\protocol.ipp"\
	{$(INCLUDE)}"\ospace\stream\rtti.h"\
	{$(INCLUDE)}"\ospace\stream\smacros.h"\
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
	{$(INCLUDE)}"\ospace\type\types.h"\
	{$(INCLUDE)}"\ospace\uss\std\string.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\Triastlb_i.c"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Bscriptn - Win32 Release"


"$(INTDIR)\Commimp.obj" : $(SOURCE) $(DEP_CPP_COMMI) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"


"$(INTDIR)\Commimp.obj" : $(SOURCE) $(DEP_CPP_COMMI) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\Commimp.sbr" : $(SOURCE) $(DEP_CPP_COMMI) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Commsi.cpp
DEP_CPP_COMMS=\
	".\bscrext.hxx"\
	".\bscript.h"\
	".\bscript.hxx"\
	".\bscriptp.hxx"\
	".\commimp.h"\
	".\commsi.h"\
	".\imacorg.h"\
	".\imacro.h"\
	".\listitem.h"\
	".\macrguid.h"\
	".\menuver.h"\
	".\myenum.h"\
	".\tmplinst.h"\
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
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FSTREAM"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\IXTNEXT.HXX"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\OLESTREA.H"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\cast.h"\
	{$(INCLUDE)}"\ospace\rtti\cast.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\rtti\regmacro.h"\
	{$(INCLUDE)}"\ospace\rtti\rtti.h"\
	{$(INCLUDE)}"\ospace\rtti\smacros.h"\
	{$(INCLUDE)}"\ospace\source.h"\
	{$(INCLUDE)}"\ospace\std\fstream"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\iterator"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream.h"\
	{$(INCLUDE)}"\ospace\stream\_startup.h"\
	{$(INCLUDE)}"\ospace\stream\ascii.h"\
	{$(INCLUDE)}"\ospace\stream\bstream.h"\
	{$(INCLUDE)}"\ospace\stream\bstream.ipp"\
	{$(INCLUDE)}"\ospace\stream\fstrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\fstrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\stream\istrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\istrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\ndr.h"\
	{$(INCLUDE)}"\ospace\stream\ndr.ipp"\
	{$(INCLUDE)}"\ospace\stream\ndrtypes.h"\
	{$(INCLUDE)}"\ospace\stream\ostrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\ostrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\protocol.h"\
	{$(INCLUDE)}"\ospace\stream\protocol.ipp"\
	{$(INCLUDE)}"\ospace\stream\rtti.h"\
	{$(INCLUDE)}"\ospace\stream\smacros.h"\
	{$(INCLUDE)}"\ospace\stream\strbuf.h"\
	{$(INCLUDE)}"\ospace\stream\strbuf.ipp"\
	{$(INCLUDE)}"\ospace\stream\strmdev.h"\
	{$(INCLUDE)}"\ospace\stream\strmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\tstream.h"\
	{$(INCLUDE)}"\ospace\stream\tstream.ipp"\
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
	{$(INCLUDE)}"\ospace\type\types.h"\
	{$(INCLUDE)}"\ospace\uss\std\map.cc"\
	{$(INCLUDE)}"\ospace\uss\std\map.h"\
	{$(INCLUDE)}"\ospace\uss\std\string.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\Triastlb_i.c"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	
NODEP_CPP_COMMS=\
	".\bscriptr.h"\
	

!IF  "$(CFG)" == "Bscriptn - Win32 Release"


"$(INTDIR)\Commsi.obj" : $(SOURCE) $(DEP_CPP_COMMS) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"


"$(INTDIR)\Commsi.obj" : $(SOURCE) $(DEP_CPP_COMMS) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\Commsi.sbr" : $(SOURCE) $(DEP_CPP_COMMS) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Procimp.cpp
DEP_CPP_PROCI=\
	".\analimp.h"\
	".\anpasimp.h"\
	".\bscrext.hxx"\
	".\bscript.h"\
	".\bscript.hxx"\
	".\bscriptp.hxx"\
	".\commsi.h"\
	".\custdlg.h"\
	".\imacorg.h"\
	".\imacro.h"\
	".\listitem.h"\
	".\macrguid.h"\
	".\macroorg.h"\
	".\myenum.h"\
	".\procimp.h"\
	".\saveimp.h"\
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
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\rtti\cast.h"\
	{$(INCLUDE)}"\ospace\rtti\cast.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\rtti\regmacro.h"\
	{$(INCLUDE)}"\ospace\rtti\rtti.h"\
	{$(INCLUDE)}"\ospace\rtti\smacros.h"\
	{$(INCLUDE)}"\ospace\source.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\iterator"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\bstream.h"\
	{$(INCLUDE)}"\ospace\stream\bstream.ipp"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\stream\protocol.h"\
	{$(INCLUDE)}"\ospace\stream\protocol.ipp"\
	{$(INCLUDE)}"\ospace\stream\rtti.h"\
	{$(INCLUDE)}"\ospace\stream\smacros.h"\
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
	{$(INCLUDE)}"\ospace\type\types.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\Triastlb_i.c"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	
NODEP_CPP_PROCI=\
	".\bscriptr.h"\
	

!IF  "$(CFG)" == "Bscriptn - Win32 Release"


"$(INTDIR)\Procimp.obj" : $(SOURCE) $(DEP_CPP_PROCI) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"


"$(INTDIR)\Procimp.obj" : $(SOURCE) $(DEP_CPP_PROCI) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\Procimp.sbr" : $(SOURCE) $(DEP_CPP_PROCI) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Analimp.cpp
DEP_CPP_ANALI=\
	".\analimp.h"\
	".\anpasimp.h"\
	".\bscrext.hxx"\
	".\bscript.h"\
	".\bscript.hxx"\
	".\bscriptp.hxx"\
	".\commsi.h"\
	".\custdlg.h"\
	".\imacorg.h"\
	".\imacro.h"\
	".\listitem.h"\
	".\macrguid.h"\
	".\macroorg.h"\
	".\myenum.h"\
	".\procimp.h"\
	".\saveimp.h"\
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
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\iterator"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\Triastlb_i.c"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	
NODEP_CPP_ANALI=\
	".\bscriptr.h"\
	

!IF  "$(CFG)" == "Bscriptn - Win32 Release"


"$(INTDIR)\Analimp.obj" : $(SOURCE) $(DEP_CPP_ANALI) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"


"$(INTDIR)\Analimp.obj" : $(SOURCE) $(DEP_CPP_ANALI) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\Analimp.sbr" : $(SOURCE) $(DEP_CPP_ANALI) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Macroorg.cpp
DEP_CPP_MACROO=\
	".\analimp.h"\
	".\anpasimp.h"\
	".\bscrext.hxx"\
	".\bscript.h"\
	".\bscript.hxx"\
	".\bscriptp.hxx"\
	".\commsi.h"\
	".\custdlg.h"\
	".\imacorg.h"\
	".\imacro.h"\
	".\listitem.h"\
	".\macrguid.h"\
	".\macroorg.h"\
	".\myenum.h"\
	".\procimp.h"\
	".\saveimp.h"\
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
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\iterator"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\Triastlb_i.c"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	
NODEP_CPP_MACROO=\
	".\bscriptr.h"\
	

!IF  "$(CFG)" == "Bscriptn - Win32 Release"


"$(INTDIR)\Macroorg.obj" : $(SOURCE) $(DEP_CPP_MACROO) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"


"$(INTDIR)\Macroorg.obj" : $(SOURCE) $(DEP_CPP_MACROO) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\Macroorg.sbr" : $(SOURCE) $(DEP_CPP_MACROO) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\list.cpp
DEP_CPP_LIST_=\
	".\bscrext.hxx"\
	".\bscript.h"\
	".\bscript.hxx"\
	".\bscriptp.hxx"\
	".\commimp.h"\
	".\imacorg.h"\
	".\imacro.h"\
	".\listitem.h"\
	".\macrguid.h"\
	".\myenum.h"\
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
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\rtti\cast.h"\
	{$(INCLUDE)}"\ospace\rtti\cast.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\rtti\regmacro.h"\
	{$(INCLUDE)}"\ospace\rtti\rtti.h"\
	{$(INCLUDE)}"\ospace\rtti\smacros.h"\
	{$(INCLUDE)}"\ospace\source.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\iterator"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\bstream.h"\
	{$(INCLUDE)}"\ospace\stream\bstream.ipp"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\stream\protocol.h"\
	{$(INCLUDE)}"\ospace\stream\protocol.ipp"\
	{$(INCLUDE)}"\ospace\stream\rtti.h"\
	{$(INCLUDE)}"\ospace\stream\smacros.h"\
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
	{$(INCLUDE)}"\ospace\type\types.h"\
	{$(INCLUDE)}"\ospace\uss\std\string.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\Triastlb_i.c"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	
NODEP_CPP_LIST_=\
	".\bscriptr.h"\
	

!IF  "$(CFG)" == "Bscriptn - Win32 Release"


"$(INTDIR)\list.obj" : $(SOURCE) $(DEP_CPP_LIST_) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"


"$(INTDIR)\list.obj" : $(SOURCE) $(DEP_CPP_LIST_) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\list.sbr" : $(SOURCE) $(DEP_CPP_LIST_) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Anpasimp.cpp
DEP_CPP_ANPAS=\
	".\analimp.h"\
	".\anpasimp.h"\
	".\bscrext.hxx"\
	".\bscript.h"\
	".\bscript.hxx"\
	".\bscriptp.hxx"\
	".\commsi.h"\
	".\custdlg.h"\
	".\imacorg.h"\
	".\imacro.h"\
	".\listitem.h"\
	".\macrguid.h"\
	".\macroorg.h"\
	".\myenum.h"\
	".\procimp.h"\
	".\saveimp.h"\
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
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\rtti\cast.h"\
	{$(INCLUDE)}"\ospace\rtti\cast.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\rtti\regmacro.h"\
	{$(INCLUDE)}"\ospace\rtti\rtti.h"\
	{$(INCLUDE)}"\ospace\rtti\smacros.h"\
	{$(INCLUDE)}"\ospace\source.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\iterator"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\bstream.h"\
	{$(INCLUDE)}"\ospace\stream\bstream.ipp"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\stream\protocol.h"\
	{$(INCLUDE)}"\ospace\stream\protocol.ipp"\
	{$(INCLUDE)}"\ospace\stream\rtti.h"\
	{$(INCLUDE)}"\ospace\stream\smacros.h"\
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
	{$(INCLUDE)}"\ospace\type\types.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\Triastlb_i.c"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	
NODEP_CPP_ANPAS=\
	".\bscriptr.h"\
	

!IF  "$(CFG)" == "Bscriptn - Win32 Release"


"$(INTDIR)\Anpasimp.obj" : $(SOURCE) $(DEP_CPP_ANPAS) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"


"$(INTDIR)\Anpasimp.obj" : $(SOURCE) $(DEP_CPP_ANPAS) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\Anpasimp.sbr" : $(SOURCE) $(DEP_CPP_ANPAS) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\custdlg.cpp
DEP_CPP_CUSTD=\
	".\bscrext.hxx"\
	".\bscript.h"\
	".\bscript.hxx"\
	".\bscriptp.hxx"\
	".\custdlg.h"\
	".\imacorg.h"\
	".\imacro.h"\
	".\macrguid.h"\
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
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\iterator"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\Triastlb_i.c"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	
NODEP_CPP_CUSTD=\
	".\bscriptr.h"\
	

!IF  "$(CFG)" == "Bscriptn - Win32 Release"


"$(INTDIR)\custdlg.obj" : $(SOURCE) $(DEP_CPP_CUSTD) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"


"$(INTDIR)\custdlg.obj" : $(SOURCE) $(DEP_CPP_CUSTD) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\custdlg.sbr" : $(SOURCE) $(DEP_CPP_CUSTD) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Triasext.cxx
DEP_CPP_TRIAS=\
	".\bscrext.hxx"\
	".\bscript.hxx"\
	".\bscriptp.hxx"\
	".\triasext.h"\
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
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\iterator"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\Triastlb_i.c"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Bscriptn - Win32 Release"


"$(INTDIR)\Triasext.obj" : $(SOURCE) $(DEP_CPP_TRIAS) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"


"$(INTDIR)\Triasext.obj" : $(SOURCE) $(DEP_CPP_TRIAS) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\Triasext.sbr" : $(SOURCE) $(DEP_CPP_TRIAS) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\saveimp.cpp
DEP_CPP_SAVEI=\
	".\analimp.h"\
	".\anpasimp.h"\
	".\bscrext.hxx"\
	".\bscript.h"\
	".\bscript.hxx"\
	".\bscriptp.hxx"\
	".\commsi.h"\
	".\imacorg.h"\
	".\imacro.h"\
	".\listitem.h"\
	".\macrguid.h"\
	".\macroorg.h"\
	".\myenum.h"\
	".\procimp.h"\
	".\saveimp.h"\
	".\stghelp.hxx"\
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
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\rtti\cast.h"\
	{$(INCLUDE)}"\ospace\rtti\cast.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\rtti\regmacro.h"\
	{$(INCLUDE)}"\ospace\rtti\rtti.h"\
	{$(INCLUDE)}"\ospace\rtti\smacros.h"\
	{$(INCLUDE)}"\ospace\source.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\iterator"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream\bstream.h"\
	{$(INCLUDE)}"\ospace\stream\bstream.ipp"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\stream\protocol.h"\
	{$(INCLUDE)}"\ospace\stream\protocol.ipp"\
	{$(INCLUDE)}"\ospace\stream\rtti.h"\
	{$(INCLUDE)}"\ospace\stream\smacros.h"\
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
	{$(INCLUDE)}"\ospace\type\types.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\Triastlb_i.c"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	
NODEP_CPP_SAVEI=\
	".\bscriptr.h"\
	

!IF  "$(CFG)" == "Bscriptn - Win32 Release"


"$(INTDIR)\saveimp.obj" : $(SOURCE) $(DEP_CPP_SAVEI) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"


"$(INTDIR)\saveimp.obj" : $(SOURCE) $(DEP_CPP_SAVEI) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\saveimp.sbr" : $(SOURCE) $(DEP_CPP_SAVEI) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Tmplinst.cpp
DEP_CPP_TMPLI=\
	".\imacorg.h"\
	".\imacro.h"\
	".\macrguid.h"\
	".\myenum.h"\
	".\tmplinst.h"\
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
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\Ipropseq.hxx"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\rtti\cast.h"\
	{$(INCLUDE)}"\ospace\rtti\cast.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\rtti\regmacro.h"\
	{$(INCLUDE)}"\ospace\rtti\rtti.h"\
	{$(INCLUDE)}"\ospace\rtti\smacros.h"\
	{$(INCLUDE)}"\ospace\source.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stream\bstream.h"\
	{$(INCLUDE)}"\ospace\stream\bstream.ipp"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\stream\protocol.h"\
	{$(INCLUDE)}"\ospace\stream\protocol.ipp"\
	{$(INCLUDE)}"\ospace\stream\rtti.h"\
	{$(INCLUDE)}"\ospace\stream\smacros.h"\
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
	{$(INCLUDE)}"\ospace\type\types.h"\
	{$(INCLUDE)}"\ospace\uss\std\list.cc"\
	{$(INCLUDE)}"\ospace\uss\std\list.h"\
	{$(INCLUDE)}"\ospace\uss\std\map.cc"\
	{$(INCLUDE)}"\ospace\uss\std\map.h"\
	{$(INCLUDE)}"\ospace\uss\std\string.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Bscriptn - Win32 Release"


"$(INTDIR)\Tmplinst.obj" : $(SOURCE) $(DEP_CPP_TMPLI) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"


"$(INTDIR)\Tmplinst.obj" : $(SOURCE) $(DEP_CPP_TMPLI) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\Tmplinst.sbr" : $(SOURCE) $(DEP_CPP_TMPLI) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Stghelp.cxx
DEP_CPP_STGHE=\
	".\bscrext.hxx"\
	".\bscript.hxx"\
	".\bscriptp.hxx"\
	".\stghelp.hxx"\
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
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\iterator"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\Triastlb_i.c"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Bscriptn - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"


BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /Gi /GR /GX /Zi /Od /Ob1 /D "_DEBUG" /D\
 "EBWIN32" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D "WIN32" /D\
 "_WINDOWS" /D "__MFC__" /D "_MBCS" /D "_AFXEXT" /D "_AFXDLL" /D "_WINDLL" /D\
 "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D\
 "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D "OS_NO_ALLOCATORS" /D\
 "QI_EXCEPTION" /FR"$(INTDIR)/" /Fp"$(INTDIR)/Bscript.pch" /Yu"bscriptp.hxx"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/bscript.pdb" /c $(SOURCE) \
	

"$(INTDIR)\Stghelp.obj" : $(SOURCE) $(DEP_CPP_STGHE) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"
   $(BuildCmds)

"$(INTDIR)\Stghelp.sbr" : $(SOURCE) $(DEP_CPP_STGHE) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Runscorg.cpp
DEP_CPP_RUNSC=\
	".\bscrext.hxx"\
	".\bscript.h"\
	".\bscript.hxx"\
	".\bscriptp.hxx"\
	".\runscorg.h"\
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
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\iterator"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\Triastlb_i.c"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	
NODEP_CPP_RUNSC=\
	".\bscriptr.h"\
	

!IF  "$(CFG)" == "Bscriptn - Win32 Release"


"$(INTDIR)\Runscorg.obj" : $(SOURCE) $(DEP_CPP_RUNSC) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"


"$(INTDIR)\Runscorg.obj" : $(SOURCE) $(DEP_CPP_RUNSC) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\Runscorg.sbr" : $(SOURCE) $(DEP_CPP_RUNSC) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\filtdlg.cpp
DEP_CPP_FILTD=\
	".\bscrext.hxx"\
	".\bscript.h"\
	".\bscript.hxx"\
	".\bscripta.h"\
	".\bscriptp.hxx"\
	".\conststr.h"\
	".\enumscpt.h"\
	".\filtdlg.h"\
	".\imacorg.h"\
	".\imacro.h"\
	".\macrguid.h"\
	".\macro.h"\
	".\macroimp.h"\
	".\perstimp.h"\
	".\runerr.h"\
	".\strmimp.h"\
	".\toolbarx.h"\
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
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OLEGUID.H"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\iterator"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\Triastlb_i.c"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	
NODEP_CPP_FILTD=\
	".\bscriptr.h"\
	

!IF  "$(CFG)" == "Bscriptn - Win32 Release"


"$(INTDIR)\filtdlg.obj" : $(SOURCE) $(DEP_CPP_FILTD) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"


"$(INTDIR)\filtdlg.obj" : $(SOURCE) $(DEP_CPP_FILTD) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\filtdlg.sbr" : $(SOURCE) $(DEP_CPP_FILTD) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Propactb.cxx
DEP_CPP_PROPA=\
	".\bscrext.hxx"\
	".\bscript.hxx"\
	".\bscriptp.hxx"\
	".\propactb.hxx"\
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
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\iterator"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\Triastlb_i.c"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Bscriptn - Win32 Release"


"$(INTDIR)\Propactb.obj" : $(SOURCE) $(DEP_CPP_PROPA) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"


"$(INTDIR)\Propactb.obj" : $(SOURCE) $(DEP_CPP_PROPA) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\Propactb.sbr" : $(SOURCE) $(DEP_CPP_PROPA) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\filtscr.cpp
DEP_CPP_FILTS=\
	".\bscrext.hxx"\
	".\bscript.h"\
	".\bscript.hxx"\
	".\bscriptp.hxx"\
	".\datahelp.h"\
	".\enumscpt.h"\
	".\filtdlg.h"\
	".\filtscr.h"\
	".\imacorg.h"\
	".\imacro.h"\
	".\macrguid.h"\
	".\macro.h"\
	".\macroimp.h"\
	".\perstimp.h"\
	".\propactb.hxx"\
	".\runerr.h"\
	".\strmimp.h"\
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
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\Ipropseq.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OLEGUID.H"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\iterator"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Pdataobj.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\Triastlb_i.c"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	
NODEP_CPP_FILTS=\
	".\bscriptr.h"\
	

!IF  "$(CFG)" == "Bscriptn - Win32 Release"


"$(INTDIR)\filtscr.obj" : $(SOURCE) $(DEP_CPP_FILTS) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"


"$(INTDIR)\filtscr.obj" : $(SOURCE) $(DEP_CPP_FILTS) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\filtscr.sbr" : $(SOURCE) $(DEP_CPP_FILTS) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Datahelp.cpp
DEP_CPP_DATAH=\
	".\bscrext.hxx"\
	".\bscript.h"\
	".\bscript.hxx"\
	".\bscriptp.hxx"\
	".\datahelp.h"\
	".\imacorg.h"\
	".\macrguid.h"\
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
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\oprpguid.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\iterator"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\Triastlb_i.c"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	
NODEP_CPP_DATAH=\
	".\bscriptr.h"\
	

!IF  "$(CFG)" == "Bscriptn - Win32 Release"


"$(INTDIR)\Datahelp.obj" : $(SOURCE) $(DEP_CPP_DATAH) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"


"$(INTDIR)\Datahelp.obj" : $(SOURCE) $(DEP_CPP_DATAH) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\Datahelp.sbr" : $(SOURCE) $(DEP_CPP_DATAH) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\runerr.cpp
DEP_CPP_RUNER=\
	".\bscrext.hxx"\
	".\bscript.h"\
	".\bscript.hxx"\
	".\bscripta.h"\
	".\bscriptp.hxx"\
	".\runerr.h"\
	".\toolbarx.h"\
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
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OLEGUID.H"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\iterator"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\Triastlb_i.c"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	
NODEP_CPP_RUNER=\
	".\bscriptr.h"\
	

!IF  "$(CFG)" == "Bscriptn - Win32 Release"


"$(INTDIR)\runerr.obj" : $(SOURCE) $(DEP_CPP_RUNER) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"


"$(INTDIR)\runerr.obj" : $(SOURCE) $(DEP_CPP_RUNER) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\runerr.sbr" : $(SOURCE) $(DEP_CPP_RUNER) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CUSTPPXT.CPP
DEP_CPP_CUSTP=\
	".\bscrext.hxx"\
	".\bscript.h"\
	".\bscript.hxx"\
	".\bscriptp.hxx"\
	".\custdlg.h"\
	".\CustPPxt.h"\
	".\imacorg.h"\
	".\imacro.h"\
	".\macrguid.h"\
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
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\IXTNEXT.HXX"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\iterator"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\Triastlb_i.c"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	
NODEP_CPP_CUSTP=\
	".\bscriptr.h"\
	

!IF  "$(CFG)" == "Bscriptn - Win32 Release"


"$(INTDIR)\CUSTPPXT.OBJ" : $(SOURCE) $(DEP_CPP_CUSTP) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"


"$(INTDIR)\CUSTPPXT.OBJ" : $(SOURCE) $(DEP_CPP_CUSTP) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\CUSTPPXT.SBR" : $(SOURCE) $(DEP_CPP_CUSTP) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FNDRPLD.CPP
DEP_CPP_FNDRP=\
	".\bscrext.hxx"\
	".\bscript.h"\
	".\bscript.hxx"\
	".\bscriptp.hxx"\
	".\fndrpld.h"\
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
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\iterator"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\Triastlb_i.c"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	
NODEP_CPP_FNDRP=\
	".\bscriptr.h"\
	

!IF  "$(CFG)" == "Bscriptn - Win32 Release"


"$(INTDIR)\FNDRPLD.OBJ" : $(SOURCE) $(DEP_CPP_FNDRP) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"


"$(INTDIR)\FNDRPLD.OBJ" : $(SOURCE) $(DEP_CPP_FNDRP) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\FNDRPLD.SBR" : $(SOURCE) $(DEP_CPP_FNDRP) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Conststr.cpp
DEP_CPP_CONST=\
	".\bscrext.hxx"\
	".\bscript.hxx"\
	".\bscriptp.hxx"\
	".\conststr.h"\
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
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\iterator"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\Triastlb_i.c"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VECTOR"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Bscriptn - Win32 Release"


"$(INTDIR)\Conststr.obj" : $(SOURCE) $(DEP_CPP_CONST) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"


"$(INTDIR)\Conststr.obj" : $(SOURCE) $(DEP_CPP_CONST) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\Conststr.sbr" : $(SOURCE) $(DEP_CPP_CONST) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Win32\Bscript.def

!IF  "$(CFG)" == "Bscriptn - Win32 Release"

!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Win32\Bscript.rc
DEP_RSC_BSCRIPT_=\
	".\Win32\Azhelp.rc"\
	".\Win32\Bscrext.rc"\
	".\Win32\Bscript.rcv"\
	".\Win32\Dd.rc"\
	".\Win32\Dg.rc"\
	".\Win32\Macro.ico"\
	".\win32\Res\FilterScript.rgs"\
	".\Win32\Toolbar.bmp"\
	".\Win32\Topics.h"\
	

!IF  "$(CFG)" == "Bscriptn - Win32 Release"


"$(INTDIR)\Bscript.res" : $(SOURCE) $(DEP_RSC_BSCRIPT_) "$(INTDIR)"
   $(RSC) /l 0x407 /fo"$(INTDIR)/Bscript.res" /i "Win32" /d "NDEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"


"$(INTDIR)\Bscript.res" : $(SOURCE) $(DEP_RSC_BSCRIPT_) "$(INTDIR)"
   $(RSC) /l 0x407 /fo"$(INTDIR)/Bscript.res" /i "Win32" /d "_DEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\win32\Res\FilterScript.rgs

!IF  "$(CFG)" == "Bscriptn - Win32 Release"

!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
