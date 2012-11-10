# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=Bscriptn - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Bscriptn - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Bscriptn - Win32 Release" && "$(CFG)" !=\
 "Bscriptn - Win32 Debug" && "$(CFG)" != "Bscriptn - Win32 PseudoRelease"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "BSCRIPT4.MAK" CFG="Bscriptn - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Bscriptn - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Bscriptn - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Bscriptn - Win32 PseudoRelease" (based on\
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
# PROP Target_Last_Scanned "Bscriptn - Win32 Debug"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "Bscriptn - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "win32/Release.207"
# PROP Intermediate_Dir "win32/Release.207"
OUTDIR=.\win32/Release.207
INTDIR=.\win32/Release.207
# Begin Custom Macros
TargetName=Bscript
# End Custom Macros

ALL : "$(OUTDIR)\Bscript.ext" "c:\trias.mvc\trias200.rel\Bscript.ext"

CLEAN : 
	-@erase "$(INTDIR)\addfdlg.obj"
	-@erase "$(INTDIR)\bscrext.obj"
	-@erase "$(INTDIR)\BSCREXTF.OBJ"
	-@erase "$(INTDIR)\BSCRIPT.OBJ"
	-@erase "$(INTDIR)\Bscript.pch"
	-@erase "$(INTDIR)\Bscript.res"
	-@erase "$(INTDIR)\BSCRIPTP.OBJ"
	-@erase "$(INTDIR)\cmbnot.obj"
	-@erase "$(INTDIR)\conststr.obj"
	-@erase "$(INTDIR)\cptvw.obj"
	-@erase "$(INTDIR)\ctfgeogk.obj"
	-@erase "$(INTDIR)\Datahelp.obj"
	-@erase "$(INTDIR)\dbfrmvw.obj"
	-@erase "$(INTDIR)\DbFrmVw2.obj"
	-@erase "$(INTDIR)\DebCtrl.obj"
	-@erase "$(INTDIR)\debfdlg.obj"
	-@erase "$(INTDIR)\DUMMYPAR.OBJ"
	-@erase "$(INTDIR)\EBARRAY.OBJ"
	-@erase "$(INTDIR)\Ebc.obj"
	-@erase "$(INTDIR)\editctrl.obj"
	-@erase "$(INTDIR)\expall.obj"
	-@erase "$(INTDIR)\Filtdlg2.obj"
	-@erase "$(INTDIR)\filtscr.obj"
	-@erase "$(INTDIR)\FNDRPLD.OBJ"
	-@erase "$(INTDIR)\MACRO.OBJ"
	-@erase "$(INTDIR)\MLONGSTR.OBJ"
	-@erase "$(INTDIR)\MRU.OBJ"
	-@erase "$(INTDIR)\MSTRSTR.OBJ"
	-@erase "$(INTDIR)\myfiledg.obj"
	-@erase "$(INTDIR)\objfeat.obj"
	-@erase "$(INTDIR)\ofeatpp.obj"
	-@erase "$(INTDIR)\projscr.obj"
	-@erase "$(INTDIR)\Propactb.obj"
	-@erase "$(INTDIR)\RegisterEbs.obj"
	-@erase "$(INTDIR)\relscrpt.obj"
	-@erase "$(INTDIR)\REXPSTR.OBJ"
	-@erase "$(INTDIR)\runebobs.obj"
	-@erase "$(INTDIR)\runerr.obj"
	-@erase "$(INTDIR)\Runscorg.obj"
	-@erase "$(INTDIR)\SCRPTDLG.OBJ"
	-@erase "$(INTDIR)\split.obj"
	-@erase "$(INTDIR)\splitter.obj"
	-@erase "$(INTDIR)\spltree.obj"
	-@erase "$(INTDIR)\Strinfo.obj"
	-@erase "$(INTDIR)\tmplman.obj"
	-@erase "$(INTDIR)\Triasext.obj"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(INTDIR)\Wrapxt.obj"
	-@erase "$(OUTDIR)\Bscript.exp"
	-@erase "$(OUTDIR)\Bscript.ext"
	-@erase "$(OUTDIR)\Bscript.lib"
	-@erase "$(OUTDIR)\Bscript.pdb"
	-@erase "c:\trias.mvc\trias200.rel\Bscript.ext"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GR /GX /Zi /O1 /D "NDEBUG" /D "EBWIN32" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D "WIN32" /D "_WINDOWS" /D "__MFC__" /D "_MBCS" /D "_AFXEXT" /D "_AFXDLL" /D "_WINDLL" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D "OS_NO_ALLOCATORS" /D "QI_EXCEPTION" /D "__ATL_11_USED__" /D "_ATL_NEW_CCOMSTRUCT" /Fp"win32/Release.207/Bscript.pch" /Yu"bscriptp.hxx" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W3 /WX /GR /GX /Zi /O1 /D "NDEBUG" /D "EBWIN32" /D\
 "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D "WIN32" /D "_WINDOWS"\
 /D "__MFC__" /D "_MBCS" /D "_AFXEXT" /D "_AFXDLL" /D "_WINDLL" /D "OS_WIN_95"\
 /D "OS_STL_ASSERT" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D\
 "OS_NO_ALLOCATORS" /D "QI_EXCEPTION" /D "__ATL_11_USED__" /D\
 "_ATL_NEW_CCOMSTRUCT" /Fp"$(INTDIR)/Bscript.pch" /Yu"bscriptp.hxx"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\win32/Release.207/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL" /d "_OLDCATIDS"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/Bscript.res" /d "NDEBUG" /d "_AFXDLL" /d\
 "_OLDCATIDS" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/BSCRIPT4.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ixtmar42.lib stdcppr.lib cont32r.lib ebn.lib winmm.lib ospace2r.lib stdstrmr.lib /nologo /dll /debug /machine:I386 /out:"win32/Release.207/Bscript.ext" /subsystem:windows,4.0
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=ixtmar42.lib stdcppr.lib cont32r.lib ebn.lib winmm.lib\
 ospace2r.lib stdstrmr.lib /nologo /dll /incremental:no\
 /pdb:"$(OUTDIR)/Bscript.pdb" /debug /machine:I386 /def:".\Win32\Bscript.def"\
 /out:"$(OUTDIR)/Bscript.ext" /implib:"$(OUTDIR)/Bscript.lib"\
 /subsystem:windows,4.0 
DEF_FILE= \
	".\Win32\Bscript.def"
LINK32_OBJS= \
	"$(INTDIR)\addfdlg.obj" \
	"$(INTDIR)\bscrext.obj" \
	"$(INTDIR)\BSCREXTF.OBJ" \
	"$(INTDIR)\BSCRIPT.OBJ" \
	"$(INTDIR)\Bscript.res" \
	"$(INTDIR)\BSCRIPTP.OBJ" \
	"$(INTDIR)\cmbnot.obj" \
	"$(INTDIR)\conststr.obj" \
	"$(INTDIR)\cptvw.obj" \
	"$(INTDIR)\ctfgeogk.obj" \
	"$(INTDIR)\Datahelp.obj" \
	"$(INTDIR)\dbfrmvw.obj" \
	"$(INTDIR)\DbFrmVw2.obj" \
	"$(INTDIR)\DebCtrl.obj" \
	"$(INTDIR)\debfdlg.obj" \
	"$(INTDIR)\DUMMYPAR.OBJ" \
	"$(INTDIR)\EBARRAY.OBJ" \
	"$(INTDIR)\Ebc.obj" \
	"$(INTDIR)\editctrl.obj" \
	"$(INTDIR)\expall.obj" \
	"$(INTDIR)\Filtdlg2.obj" \
	"$(INTDIR)\filtscr.obj" \
	"$(INTDIR)\FNDRPLD.OBJ" \
	"$(INTDIR)\MACRO.OBJ" \
	"$(INTDIR)\MLONGSTR.OBJ" \
	"$(INTDIR)\MRU.OBJ" \
	"$(INTDIR)\MSTRSTR.OBJ" \
	"$(INTDIR)\myfiledg.obj" \
	"$(INTDIR)\objfeat.obj" \
	"$(INTDIR)\ofeatpp.obj" \
	"$(INTDIR)\projscr.obj" \
	"$(INTDIR)\Propactb.obj" \
	"$(INTDIR)\RegisterEbs.obj" \
	"$(INTDIR)\relscrpt.obj" \
	"$(INTDIR)\REXPSTR.OBJ" \
	"$(INTDIR)\runebobs.obj" \
	"$(INTDIR)\runerr.obj" \
	"$(INTDIR)\Runscorg.obj" \
	"$(INTDIR)\SCRPTDLG.OBJ" \
	"$(INTDIR)\split.obj" \
	"$(INTDIR)\splitter.obj" \
	"$(INTDIR)\spltree.obj" \
	"$(INTDIR)\Strinfo.obj" \
	"$(INTDIR)\tmplman.obj" \
	"$(INTDIR)\Triasext.obj" \
	"$(INTDIR)\Wrapxt.obj"

"$(OUTDIR)\Bscript.ext" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build
TargetPath=.\win32\Release.207\Bscript.ext
TargetName=Bscript
InputPath=.\win32\Release.207\Bscript.ext
SOURCE=$(InputPath)

"c:\trias.mvc\trias200.rel\$(TargetName).ext" : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
   copy "$(TargetPath)" "c:\trias.mvc\trias200.rel\$(TargetName).ext"

# End Custom Build

!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "win32/Debug.207"
# PROP Intermediate_Dir "win32/Debug.207"
OUTDIR=.\win32/Debug.207
INTDIR=.\win32/Debug.207

ALL : "$(OUTDIR)\bscriptd.ext" "$(OUTDIR)\BSCRIPT4.bsc"

CLEAN : 
	-@erase "$(INTDIR)\addfdlg.obj"
	-@erase "$(INTDIR)\addfdlg.sbr"
	-@erase "$(INTDIR)\bscrext.obj"
	-@erase "$(INTDIR)\bscrext.sbr"
	-@erase "$(INTDIR)\BSCREXTF.OBJ"
	-@erase "$(INTDIR)\BSCREXTF.SBR"
	-@erase "$(INTDIR)\bscript.idb"
	-@erase "$(INTDIR)\BSCRIPT.OBJ"
	-@erase "$(INTDIR)\Bscript.pch"
	-@erase "$(INTDIR)\bscript.pdb"
	-@erase "$(INTDIR)\BSCRIPT.SBR"
	-@erase "$(INTDIR)\Bscriptd.res"
	-@erase "$(INTDIR)\BSCRIPTP.OBJ"
	-@erase "$(INTDIR)\BSCRIPTP.SBR"
	-@erase "$(INTDIR)\cmbnot.obj"
	-@erase "$(INTDIR)\cmbnot.sbr"
	-@erase "$(INTDIR)\conststr.obj"
	-@erase "$(INTDIR)\conststr.sbr"
	-@erase "$(INTDIR)\cptvw.obj"
	-@erase "$(INTDIR)\cptvw.sbr"
	-@erase "$(INTDIR)\ctfgeogk.obj"
	-@erase "$(INTDIR)\ctfgeogk.sbr"
	-@erase "$(INTDIR)\Datahelp.obj"
	-@erase "$(INTDIR)\Datahelp.sbr"
	-@erase "$(INTDIR)\dbfrmvw.obj"
	-@erase "$(INTDIR)\dbfrmvw.sbr"
	-@erase "$(INTDIR)\DbFrmVw2.obj"
	-@erase "$(INTDIR)\DbFrmVw2.sbr"
	-@erase "$(INTDIR)\DebCtrl.obj"
	-@erase "$(INTDIR)\DebCtrl.sbr"
	-@erase "$(INTDIR)\debfdlg.obj"
	-@erase "$(INTDIR)\debfdlg.sbr"
	-@erase "$(INTDIR)\DUMMYPAR.OBJ"
	-@erase "$(INTDIR)\DUMMYPAR.SBR"
	-@erase "$(INTDIR)\EBARRAY.OBJ"
	-@erase "$(INTDIR)\EBARRAY.SBR"
	-@erase "$(INTDIR)\Ebc.obj"
	-@erase "$(INTDIR)\Ebc.sbr"
	-@erase "$(INTDIR)\editctrl.obj"
	-@erase "$(INTDIR)\editctrl.sbr"
	-@erase "$(INTDIR)\expall.obj"
	-@erase "$(INTDIR)\expall.sbr"
	-@erase "$(INTDIR)\Filtdlg2.obj"
	-@erase "$(INTDIR)\Filtdlg2.sbr"
	-@erase "$(INTDIR)\filtscr.obj"
	-@erase "$(INTDIR)\filtscr.sbr"
	-@erase "$(INTDIR)\FNDRPLD.OBJ"
	-@erase "$(INTDIR)\FNDRPLD.SBR"
	-@erase "$(INTDIR)\MACRO.OBJ"
	-@erase "$(INTDIR)\MACRO.SBR"
	-@erase "$(INTDIR)\MLONGSTR.OBJ"
	-@erase "$(INTDIR)\MLONGSTR.SBR"
	-@erase "$(INTDIR)\MRU.OBJ"
	-@erase "$(INTDIR)\MRU.SBR"
	-@erase "$(INTDIR)\MSTRSTR.OBJ"
	-@erase "$(INTDIR)\MSTRSTR.SBR"
	-@erase "$(INTDIR)\myfiledg.obj"
	-@erase "$(INTDIR)\myfiledg.sbr"
	-@erase "$(INTDIR)\objfeat.obj"
	-@erase "$(INTDIR)\objfeat.sbr"
	-@erase "$(INTDIR)\ofeatpp.obj"
	-@erase "$(INTDIR)\ofeatpp.sbr"
	-@erase "$(INTDIR)\projscr.obj"
	-@erase "$(INTDIR)\projscr.sbr"
	-@erase "$(INTDIR)\Propactb.obj"
	-@erase "$(INTDIR)\Propactb.sbr"
	-@erase "$(INTDIR)\RegisterEbs.obj"
	-@erase "$(INTDIR)\RegisterEbs.sbr"
	-@erase "$(INTDIR)\relscrpt.obj"
	-@erase "$(INTDIR)\relscrpt.sbr"
	-@erase "$(INTDIR)\REXPSTR.OBJ"
	-@erase "$(INTDIR)\REXPSTR.SBR"
	-@erase "$(INTDIR)\runebobs.obj"
	-@erase "$(INTDIR)\runebobs.sbr"
	-@erase "$(INTDIR)\runerr.obj"
	-@erase "$(INTDIR)\runerr.sbr"
	-@erase "$(INTDIR)\Runscorg.obj"
	-@erase "$(INTDIR)\Runscorg.sbr"
	-@erase "$(INTDIR)\SCRPTDLG.OBJ"
	-@erase "$(INTDIR)\SCRPTDLG.SBR"
	-@erase "$(INTDIR)\split.obj"
	-@erase "$(INTDIR)\split.sbr"
	-@erase "$(INTDIR)\splitter.obj"
	-@erase "$(INTDIR)\splitter.sbr"
	-@erase "$(INTDIR)\spltree.obj"
	-@erase "$(INTDIR)\spltree.sbr"
	-@erase "$(INTDIR)\Strinfo.obj"
	-@erase "$(INTDIR)\Strinfo.sbr"
	-@erase "$(INTDIR)\tmplman.obj"
	-@erase "$(INTDIR)\tmplman.sbr"
	-@erase "$(INTDIR)\Triasext.obj"
	-@erase "$(INTDIR)\Triasext.sbr"
	-@erase "$(INTDIR)\Wrapxt.obj"
	-@erase "$(INTDIR)\Wrapxt.sbr"
	-@erase "$(OUTDIR)\BSCRIPT4.bsc"
	-@erase "$(OUTDIR)\bscriptd.exp"
	-@erase "$(OUTDIR)\bscriptd.ext"
	-@erase "$(OUTDIR)\bscriptd.lib"
	-@erase "$(OUTDIR)\bscriptd.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(OUTDIR)/BSCRIPTN.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /Gi /GR /GX /Zi /Od /Ob1 /D "_DEBUG" /D "_ATL_NEW_CCOMSTRUCT" /D "EBWIN32" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D "WIN32" /D "_WINDOWS" /D "__MFC__" /D "_MBCS" /D "_AFXEXT" /D "_AFXDLL" /D "_WINDLL" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D "OS_NO_ALLOCATORS" /D "QI_EXCEPTION" /D "__ATL_11_USED__" /FR /Fp"win32/Debug.207/Bscript.pch" /Yu"bscriptp.hxx" /Fd"win32/Debug.207/bscript.pdb" /c
CPP_PROJ=/nologo /MDd /W3 /WX /Gm /Gi /GR /GX /Zi /Od /Ob1 /D "_DEBUG" /D\
 "_ATL_NEW_CCOMSTRUCT" /D "EBWIN32" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D\
 "__XTNSNDLL__" /D "WIN32" /D "_WINDOWS" /D "__MFC__" /D "_MBCS" /D "_AFXEXT" /D\
 "_AFXDLL" /D "_WINDLL" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D\
 "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D "OS_NO_ALLOCATORS" /D\
 "QI_EXCEPTION" /D "__ATL_11_USED__" /FR"$(INTDIR)/" /Fp"$(INTDIR)/Bscript.pch"\
 /Yu"bscriptp.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/bscript.pdb" /c 
CPP_OBJS=.\win32/Debug.207/
CPP_SBRS=.\win32/Debug.207/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /fo"win32/Debug.207/Bscriptd.res" /d "_DEBUG" /d "_AFXDLL" /d "_OLDCATIDS"
# SUBTRACT RSC /x
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/Bscriptd.res" /d "_DEBUG" /d "_AFXDLL" /d\
 "_OLDCATIDS" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/BSCRIPT4.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\addfdlg.sbr" \
	"$(INTDIR)\bscrext.sbr" \
	"$(INTDIR)\BSCREXTF.SBR" \
	"$(INTDIR)\BSCRIPT.SBR" \
	"$(INTDIR)\BSCRIPTP.SBR" \
	"$(INTDIR)\cmbnot.sbr" \
	"$(INTDIR)\conststr.sbr" \
	"$(INTDIR)\cptvw.sbr" \
	"$(INTDIR)\ctfgeogk.sbr" \
	"$(INTDIR)\Datahelp.sbr" \
	"$(INTDIR)\dbfrmvw.sbr" \
	"$(INTDIR)\DbFrmVw2.sbr" \
	"$(INTDIR)\DebCtrl.sbr" \
	"$(INTDIR)\debfdlg.sbr" \
	"$(INTDIR)\DUMMYPAR.SBR" \
	"$(INTDIR)\EBARRAY.SBR" \
	"$(INTDIR)\Ebc.sbr" \
	"$(INTDIR)\editctrl.sbr" \
	"$(INTDIR)\expall.sbr" \
	"$(INTDIR)\Filtdlg2.sbr" \
	"$(INTDIR)\filtscr.sbr" \
	"$(INTDIR)\FNDRPLD.SBR" \
	"$(INTDIR)\MACRO.SBR" \
	"$(INTDIR)\MLONGSTR.SBR" \
	"$(INTDIR)\MRU.SBR" \
	"$(INTDIR)\MSTRSTR.SBR" \
	"$(INTDIR)\myfiledg.sbr" \
	"$(INTDIR)\objfeat.sbr" \
	"$(INTDIR)\ofeatpp.sbr" \
	"$(INTDIR)\projscr.sbr" \
	"$(INTDIR)\Propactb.sbr" \
	"$(INTDIR)\RegisterEbs.sbr" \
	"$(INTDIR)\relscrpt.sbr" \
	"$(INTDIR)\REXPSTR.SBR" \
	"$(INTDIR)\runebobs.sbr" \
	"$(INTDIR)\runerr.sbr" \
	"$(INTDIR)\Runscorg.sbr" \
	"$(INTDIR)\SCRPTDLG.SBR" \
	"$(INTDIR)\split.sbr" \
	"$(INTDIR)\splitter.sbr" \
	"$(INTDIR)\spltree.sbr" \
	"$(INTDIR)\Strinfo.sbr" \
	"$(INTDIR)\tmplman.sbr" \
	"$(INTDIR)\Triasext.sbr" \
	"$(INTDIR)\Wrapxt.sbr"

"$(OUTDIR)\BSCRIPT4.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 ixtmad42.lib stdcppd.lib cont32d.lib ebn.lib winmm.lib ospace2d.lib stdstrmd.lib /nologo /dll /incremental:no /debug /machine:I386 /out:"win32/Debug.207/bscriptd.ext" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none /nodefaultlib
LINK32_FLAGS=ixtmad42.lib stdcppd.lib cont32d.lib ebn.lib winmm.lib\
 ospace2d.lib stdstrmd.lib /nologo /dll /incremental:no\
 /pdb:"$(OUTDIR)/bscriptd.pdb" /debug /machine:I386 /def:".\Win32\Bscript.def"\
 /out:"$(OUTDIR)/bscriptd.ext" /implib:"$(OUTDIR)/bscriptd.lib"\
 /SUBSYSTEM:windows,4.0 
DEF_FILE= \
	".\Win32\Bscript.def"
LINK32_OBJS= \
	"$(INTDIR)\addfdlg.obj" \
	"$(INTDIR)\bscrext.obj" \
	"$(INTDIR)\BSCREXTF.OBJ" \
	"$(INTDIR)\BSCRIPT.OBJ" \
	"$(INTDIR)\Bscriptd.res" \
	"$(INTDIR)\BSCRIPTP.OBJ" \
	"$(INTDIR)\cmbnot.obj" \
	"$(INTDIR)\conststr.obj" \
	"$(INTDIR)\cptvw.obj" \
	"$(INTDIR)\ctfgeogk.obj" \
	"$(INTDIR)\Datahelp.obj" \
	"$(INTDIR)\dbfrmvw.obj" \
	"$(INTDIR)\DbFrmVw2.obj" \
	"$(INTDIR)\DebCtrl.obj" \
	"$(INTDIR)\debfdlg.obj" \
	"$(INTDIR)\DUMMYPAR.OBJ" \
	"$(INTDIR)\EBARRAY.OBJ" \
	"$(INTDIR)\Ebc.obj" \
	"$(INTDIR)\editctrl.obj" \
	"$(INTDIR)\expall.obj" \
	"$(INTDIR)\Filtdlg2.obj" \
	"$(INTDIR)\filtscr.obj" \
	"$(INTDIR)\FNDRPLD.OBJ" \
	"$(INTDIR)\MACRO.OBJ" \
	"$(INTDIR)\MLONGSTR.OBJ" \
	"$(INTDIR)\MRU.OBJ" \
	"$(INTDIR)\MSTRSTR.OBJ" \
	"$(INTDIR)\myfiledg.obj" \
	"$(INTDIR)\objfeat.obj" \
	"$(INTDIR)\ofeatpp.obj" \
	"$(INTDIR)\projscr.obj" \
	"$(INTDIR)\Propactb.obj" \
	"$(INTDIR)\RegisterEbs.obj" \
	"$(INTDIR)\relscrpt.obj" \
	"$(INTDIR)\REXPSTR.OBJ" \
	"$(INTDIR)\runebobs.obj" \
	"$(INTDIR)\runerr.obj" \
	"$(INTDIR)\Runscorg.obj" \
	"$(INTDIR)\SCRPTDLG.OBJ" \
	"$(INTDIR)\split.obj" \
	"$(INTDIR)\splitter.obj" \
	"$(INTDIR)\spltree.obj" \
	"$(INTDIR)\Strinfo.obj" \
	"$(INTDIR)\tmplman.obj" \
	"$(INTDIR)\Triasext.obj" \
	"$(INTDIR)\Wrapxt.obj"

"$(OUTDIR)\bscriptd.ext" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Bscriptn - Win32 PseudoRelease"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Bscriptn"
# PROP BASE Intermediate_Dir "Bscriptn"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "win32/PsRel"
# PROP Intermediate_Dir "win32/PsRel"
# PROP Target_Dir ""
OUTDIR=.\win32/PsRel
INTDIR=.\win32/PsRel

ALL : "$(OUTDIR)\Bscript.ext"

CLEAN : 
	-@erase "$(INTDIR)\addfdlg.obj"
	-@erase "$(INTDIR)\bscrext.obj"
	-@erase "$(INTDIR)\BSCREXTF.OBJ"
	-@erase "$(INTDIR)\BSCRIPT.OBJ"
	-@erase "$(INTDIR)\Bscript.res"
	-@erase "$(INTDIR)\BSCRIPTP.OBJ"
	-@erase "$(INTDIR)\cmbnot.obj"
	-@erase "$(INTDIR)\conststr.obj"
	-@erase "$(INTDIR)\cptvw.obj"
	-@erase "$(INTDIR)\ctfgeogk.obj"
	-@erase "$(INTDIR)\Datahelp.obj"
	-@erase "$(INTDIR)\dbfrmvw.obj"
	-@erase "$(INTDIR)\DbFrmVw2.obj"
	-@erase "$(INTDIR)\DebCtrl.obj"
	-@erase "$(INTDIR)\debfdlg.obj"
	-@erase "$(INTDIR)\DUMMYPAR.OBJ"
	-@erase "$(INTDIR)\EBARRAY.OBJ"
	-@erase "$(INTDIR)\Ebc.obj"
	-@erase "$(INTDIR)\editctrl.obj"
	-@erase "$(INTDIR)\expall.obj"
	-@erase "$(INTDIR)\Filtdlg2.obj"
	-@erase "$(INTDIR)\filtscr.obj"
	-@erase "$(INTDIR)\FNDRPLD.OBJ"
	-@erase "$(INTDIR)\MACRO.OBJ"
	-@erase "$(INTDIR)\MLONGSTR.OBJ"
	-@erase "$(INTDIR)\MRU.OBJ"
	-@erase "$(INTDIR)\MSTRSTR.OBJ"
	-@erase "$(INTDIR)\myfiledg.obj"
	-@erase "$(INTDIR)\objfeat.obj"
	-@erase "$(INTDIR)\ofeatpp.obj"
	-@erase "$(INTDIR)\projscr.obj"
	-@erase "$(INTDIR)\Propactb.obj"
	-@erase "$(INTDIR)\RegisterEbs.obj"
	-@erase "$(INTDIR)\relscrpt.obj"
	-@erase "$(INTDIR)\REXPSTR.OBJ"
	-@erase "$(INTDIR)\runebobs.obj"
	-@erase "$(INTDIR)\runerr.obj"
	-@erase "$(INTDIR)\Runscorg.obj"
	-@erase "$(INTDIR)\SCRPTDLG.OBJ"
	-@erase "$(INTDIR)\split.obj"
	-@erase "$(INTDIR)\splitter.obj"
	-@erase "$(INTDIR)\spltree.obj"
	-@erase "$(INTDIR)\Strinfo.obj"
	-@erase "$(INTDIR)\tmplman.obj"
	-@erase "$(INTDIR)\Triasext.obj"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(INTDIR)\Wrapxt.obj"
	-@erase "$(OUTDIR)\Bscript.exp"
	-@erase "$(OUTDIR)\Bscript.ext"
	-@erase "$(OUTDIR)\Bscript.lib"
	-@erase "$(OUTDIR)\Bscript.pdb"
	-@erase ".\win32\Release\Bscript.pch"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /WX /GR /GX /Zi /O2 /I "c:\msdev\toolkit" /I "c:\msdev\toolkit\include" /D "WIN32" /D "NDEBUG" /D "EBWIN32" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D "_WINDOWS" /D "__MFC__" /D "_MBCS" /D "_AFXEXT" /D "_AFXDLL" /D "_WINDLL" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D "OS_NO_ALLOCATORS" /Fp"win32/Release/Bscript.pch" /Yu"bscriptp.hxx" /c
# ADD CPP /nologo /MD /W3 /WX /GR /GX /Zi /O2 /I "c:\msdev\toolkit" /I "c:\msdev\toolkit\include" /D "WIN32" /D "NDEBUG" /D "EBWIN32" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D "_WINDOWS" /D "__MFC__" /D "_AFXEXT" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D "OS_NO_ALLOCATORS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "QI_EXCEPTION" /Fp"win32/Release/Bscript.pch" /Yu"bscriptp.hxx" /c
CPP_PROJ=/nologo /MD /W3 /WX /GR /GX /Zi /O2 /I "c:\msdev\toolkit" /I\
 "c:\msdev\toolkit\include" /D "WIN32" /D "NDEBUG" /D "EBWIN32" /D "MSWIND" /D\
 "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D "_WINDOWS" /D "__MFC__" /D\
 "_AFXEXT" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_ALTERNATIVE_STRING_NAMES" /D\
 "OS_MULTI_THREADED" /D "OS_NO_ALLOCATORS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS"\
 /D "QI_EXCEPTION" /Fp"win32/Release/Bscript.pch" /Yu"bscriptp.hxx"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\win32/PsRel/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL" /d "PSDEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/Bscript.res" /d "NDEBUG" /d "_AFXDLL" /d\
 "PSDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/BSCRIPT4.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 ixtmfr42.lib stdcppr.lib cont32r.lib ebn.lib winmm.lib ospace2r.lib stdstrmr.lib /nologo /dll /machine:I386 /out:"win32/Release/Bscript.ext" /subsystem:windows,4.0
# SUBTRACT BASE LINK32 /pdb:none /debug
# ADD LINK32 ixtmar42.lib stdcppr.lib cont32r.lib ebn.lib winmm.lib ospace2r.lib stdstrmr.lib /nologo /dll /debug /machine:I386 /out:"win32/PsRel/Bscript.ext" /subsystem:windows,4.0
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=ixtmar42.lib stdcppr.lib cont32r.lib ebn.lib winmm.lib\
 ospace2r.lib stdstrmr.lib /nologo /dll /incremental:no\
 /pdb:"$(OUTDIR)/Bscript.pdb" /debug /machine:I386 /def:".\Win32\Bscript.def"\
 /out:"$(OUTDIR)/Bscript.ext" /implib:"$(OUTDIR)/Bscript.lib"\
 /subsystem:windows,4.0 
DEF_FILE= \
	".\Win32\Bscript.def"
LINK32_OBJS= \
	"$(INTDIR)\addfdlg.obj" \
	"$(INTDIR)\bscrext.obj" \
	"$(INTDIR)\BSCREXTF.OBJ" \
	"$(INTDIR)\BSCRIPT.OBJ" \
	"$(INTDIR)\Bscript.res" \
	"$(INTDIR)\BSCRIPTP.OBJ" \
	"$(INTDIR)\cmbnot.obj" \
	"$(INTDIR)\conststr.obj" \
	"$(INTDIR)\cptvw.obj" \
	"$(INTDIR)\ctfgeogk.obj" \
	"$(INTDIR)\Datahelp.obj" \
	"$(INTDIR)\dbfrmvw.obj" \
	"$(INTDIR)\DbFrmVw2.obj" \
	"$(INTDIR)\DebCtrl.obj" \
	"$(INTDIR)\debfdlg.obj" \
	"$(INTDIR)\DUMMYPAR.OBJ" \
	"$(INTDIR)\EBARRAY.OBJ" \
	"$(INTDIR)\Ebc.obj" \
	"$(INTDIR)\editctrl.obj" \
	"$(INTDIR)\expall.obj" \
	"$(INTDIR)\Filtdlg2.obj" \
	"$(INTDIR)\filtscr.obj" \
	"$(INTDIR)\FNDRPLD.OBJ" \
	"$(INTDIR)\MACRO.OBJ" \
	"$(INTDIR)\MLONGSTR.OBJ" \
	"$(INTDIR)\MRU.OBJ" \
	"$(INTDIR)\MSTRSTR.OBJ" \
	"$(INTDIR)\myfiledg.obj" \
	"$(INTDIR)\objfeat.obj" \
	"$(INTDIR)\ofeatpp.obj" \
	"$(INTDIR)\projscr.obj" \
	"$(INTDIR)\Propactb.obj" \
	"$(INTDIR)\RegisterEbs.obj" \
	"$(INTDIR)\relscrpt.obj" \
	"$(INTDIR)\REXPSTR.OBJ" \
	"$(INTDIR)\runebobs.obj" \
	"$(INTDIR)\runerr.obj" \
	"$(INTDIR)\Runscorg.obj" \
	"$(INTDIR)\SCRPTDLG.OBJ" \
	"$(INTDIR)\split.obj" \
	"$(INTDIR)\splitter.obj" \
	"$(INTDIR)\spltree.obj" \
	"$(INTDIR)\Strinfo.obj" \
	"$(INTDIR)\tmplman.obj" \
	"$(INTDIR)\Triasext.obj" \
	"$(INTDIR)\Wrapxt.obj"

"$(OUTDIR)\Bscript.ext" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Bscriptn - Win32 Release"
# Name "Bscriptn - Win32 Debug"
# Name "Bscriptn - Win32 PseudoRelease"

!IF  "$(CFG)" == "Bscriptn - Win32 Release"

!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"

!ELSEIF  "$(CFG)" == "Bscriptn - Win32 PseudoRelease"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\BSCRIPTP.CXX

!IF  "$(CFG)" == "Bscriptn - Win32 Release"

DEP_CPP_BSCRI=\
	".\BSCRIPTP.HXX"\
	{$(INCLUDE)}"\ATLIMPL.CPP"\
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
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
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
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	
# ADD CPP /Yc"bscriptp.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GR /GX /Zi /O1 /D "NDEBUG" /D "EBWIN32" /D\
 "MSWIND" /D "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D "WIN32" /D "_WINDOWS"\
 /D "__MFC__" /D "_MBCS" /D "_AFXEXT" /D "_AFXDLL" /D "_WINDLL" /D "OS_WIN_95"\
 /D "OS_STL_ASSERT" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D\
 "OS_NO_ALLOCATORS" /D "QI_EXCEPTION" /D "__ATL_11_USED__" /D\
 "_ATL_NEW_CCOMSTRUCT" /Fp"$(INTDIR)/Bscript.pch" /Yc"bscriptp.hxx"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\BSCRIPTP.OBJ" : $(SOURCE) $(DEP_CPP_BSCRI) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Bscript.pch" : $(SOURCE) $(DEP_CPP_BSCRI) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"

DEP_CPP_BSCRI=\
	".\BSCREXT.HXX"\
	".\BSCRIPT.HXX"\
	".\BSCRIPTP.HXX"\
	{$(INCLUDE)}"\ATLIMPL.CPP"\
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
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XtsnPropAtl.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	
# ADD CPP /Yc"bscriptp.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /Gi /GR /GX /Zi /Od /Ob1 /D "_DEBUG" /D\
 "_ATL_NEW_CCOMSTRUCT" /D "EBWIN32" /D "MSWIND" /D "__XT" /D "__DEXPROCS" /D\
 "__XTNSNDLL__" /D "WIN32" /D "_WINDOWS" /D "__MFC__" /D "_MBCS" /D "_AFXEXT" /D\
 "_AFXDLL" /D "_WINDLL" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D\
 "OS_ALTERNATIVE_STRING_NAMES" /D "OS_MULTI_THREADED" /D "OS_NO_ALLOCATORS" /D\
 "QI_EXCEPTION" /D "__ATL_11_USED__" /FR"$(INTDIR)/" /Fp"$(INTDIR)/Bscript.pch"\
 /Yc"bscriptp.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/bscript.pdb" /c $(SOURCE) \
	

"$(INTDIR)\BSCRIPTP.OBJ" : $(SOURCE) $(DEP_CPP_BSCRI) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\BSCRIPTP.SBR" : $(SOURCE) $(DEP_CPP_BSCRI) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Bscript.pch" : $(SOURCE) $(DEP_CPP_BSCRI) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Bscriptn - Win32 PseudoRelease"

DEP_CPP_BSCRI=\
	".\BSCREXT.HXX"\
	".\BSCRIPT.HXX"\
	".\BSCRIPTP.HXX"\
	{$(INCLUDE)}"\ATLIMPL.CPP"\
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
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XtsnPropAtl.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	
# ADD BASE CPP /Yc"bscriptp.hxx"
# ADD CPP /Yc"bscriptp.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GR /GX /Zi /O2 /I "c:\msdev\toolkit" /I\
 "c:\msdev\toolkit\include" /D "WIN32" /D "NDEBUG" /D "EBWIN32" /D "MSWIND" /D\
 "__XT" /D "__DEXPROCS" /D "__XTNSNDLL__" /D "_WINDOWS" /D "__MFC__" /D\
 "_AFXEXT" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_ALTERNATIVE_STRING_NAMES" /D\
 "OS_MULTI_THREADED" /D "OS_NO_ALLOCATORS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS"\
 /D "QI_EXCEPTION" /Fp"win32/Release/Bscript.pch" /Yc"bscriptp.hxx"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\BSCRIPTP.OBJ" : $(SOURCE) $(DEP_CPP_BSCRI) "$(INTDIR)"
   $(BuildCmds)

".\win32\Release\Bscript.pch" : $(SOURCE) $(DEP_CPP_BSCRI) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\BSCRIPT.CXX

!IF  "$(CFG)" == "Bscriptn - Win32 Release"

DEP_CPP_BSCRIP=\
	".\BSCREXT.HXX"\
	".\BSCRIPT.H"\
	".\BSCRIPTP.HXX"\
	".\cmbnot.h"\
	".\CONSTSTR.H"\
	".\expall.h"\
	".\filtdlg2.h"\
	".\FILTSCR.H"\
	".\ISCRPROP.H"\
	".\MACRGUID.H"\
	".\MACRO.H"\
	".\OBJFEAT.H"\
	".\Objmanguid.h"\
	".\ofeatpp.h"\
	".\oftppxt.h"\
	".\PROJSCR.H"\
	".\Propactb.hxx"\
	".\proppext.h"\
	".\RegisterEbs.h"\
	".\RELSCRPT.H"\
	".\RUNEBOBS.H"\
	".\RUNERR.H"\
	".\RUNSCORG.H"\
	".\SCRPTDLG.H"\
	".\SPLIT.H"\
	".\SPLITTER.H"\
	".\STRINFO.H"\
	".\tmplman.h"\
	".\TOOLBARX.H"\
	".\TRIASEXT.H"\
	".\versio32.h"\
	".\VERSION.H"\
	".\Wrapxt.h"\
	{$(INCLUDE)}"\bscrguid.h"\
	{$(INCLUDE)}"\BUILD.H"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\iobjman.h"\
	{$(INCLUDE)}"\Ipropseq.hxx"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\IXTNEXT.HXX"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OLEGUID.H"\
	{$(INCLUDE)}"\propguid.h"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TRiASHelper_i.c"\
	{$(INCLUDE)}"\Triastlb_i.c"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\YVALS.H"\
	
NODEP_CPP_BSCRIP=\
	".\Versio16.h"\
	

"$(INTDIR)\BSCRIPT.OBJ" : $(SOURCE) $(DEP_CPP_BSCRIP) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"

DEP_CPP_BSCRIP=\
	".\BSCREXT.HXX"\
	".\BSCRIPT.H"\
	".\BSCRIPT.HXX"\
	".\BSCRIPTP.HXX"\
	".\cmbnot.h"\
	".\CONSTSTR.H"\
	".\expall.h"\
	".\filtdlg2.h"\
	".\FILTSCR.H"\
	".\ISCRPROP.H"\
	".\MACRGUID.H"\
	".\MACRO.H"\
	".\OBJFEAT.H"\
	".\Objmanguid.h"\
	".\ofeatpp.h"\
	".\oftppxt.h"\
	".\PROJSCR.H"\
	".\Propactb.hxx"\
	".\proppext.h"\
	".\RegisterEbs.h"\
	".\RELSCRPT.H"\
	".\RUNEBOBS.H"\
	".\RUNERR.H"\
	".\RUNSCORG.H"\
	".\SCRPTDLG.H"\
	".\SPLIT.H"\
	".\SPLITTER.H"\
	".\STRINFO.H"\
	".\tmplman.h"\
	".\TOOLBARX.H"\
	".\TRIASEXT.H"\
	".\versio32.h"\
	".\VERSION.H"\
	".\Wrapxt.h"\
	{$(INCLUDE)}"\bscrguid.h"\
	{$(INCLUDE)}"\BUILD.H"\
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
	{$(INCLUDE)}"\FSTREAM"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\iobjman.h"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
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
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\propguid.h"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TRiASHelper_i.c"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XtsnPropAtl.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	
NODEP_CPP_BSCRIP=\
	".\Versio16.h"\
	

"$(INTDIR)\BSCRIPT.OBJ" : $(SOURCE) $(DEP_CPP_BSCRIP) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\BSCRIPT.SBR" : $(SOURCE) $(DEP_CPP_BSCRIP) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 PseudoRelease"

DEP_CPP_BSCRIP=\
	".\BSCREXT.HXX"\
	".\BSCRIPT.H"\
	".\BSCRIPT.HXX"\
	".\BSCRIPTP.HXX"\
	".\cmbnot.h"\
	".\CONSTSTR.H"\
	".\expall.h"\
	".\filtdlg2.h"\
	".\FILTSCR.H"\
	".\ISCRPROP.H"\
	".\MACRGUID.H"\
	".\MACRO.H"\
	".\OBJFEAT.H"\
	".\Objmanguid.h"\
	".\ofeatpp.h"\
	".\oftppxt.h"\
	".\PROJSCR.H"\
	".\Propactb.hxx"\
	".\proppext.h"\
	".\RegisterEbs.h"\
	".\RELSCRPT.H"\
	".\RUNEBOBS.H"\
	".\RUNERR.H"\
	".\RUNSCORG.H"\
	".\SCRPTDLG.H"\
	".\SPLIT.H"\
	".\SPLITTER.H"\
	".\STRINFO.H"\
	".\tmplman.h"\
	".\TOOLBARX.H"\
	".\TRIASEXT.H"\
	".\versio32.h"\
	".\VERSION.H"\
	".\Wrapxt.h"\
	{$(INCLUDE)}"\bscrguid.h"\
	{$(INCLUDE)}"\BUILD.H"\
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
	{$(INCLUDE)}"\FSTREAM"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\iobjman.h"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
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
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\propguid.h"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TRiASHelper_i.c"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XtsnPropAtl.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	
NODEP_CPP_BSCRIP=\
	".\Versio16.h"\
	

"$(INTDIR)\BSCRIPT.OBJ" : $(SOURCE) $(DEP_CPP_BSCRIP) "$(INTDIR)"\
 ".\win32\Release\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\bscrext.cxx
DEP_CPP_BSCRE=\
	".\BSCREXT.HXX"\
	".\BSCRIPT.HXX"\
	".\BSCRIPTP.HXX"\
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
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XtsnPropAtl.h"\
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


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 PseudoRelease"


"$(INTDIR)\bscrext.obj" : $(SOURCE) $(DEP_CPP_BSCRE) "$(INTDIR)"\
 ".\win32\Release\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DUMMYPAR.CPP
DEP_CPP_DUMMY=\
	".\BSCREXT.HXX"\
	".\BSCRIPT.H"\
	".\BSCRIPT.HXX"\
	".\BSCRIPTP.HXX"\
	".\DUMMYPAR.H"\
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
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XtsnPropAtl.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Bscriptn - Win32 Release"


"$(INTDIR)\DUMMYPAR.OBJ" : $(SOURCE) $(DEP_CPP_DUMMY) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"


"$(INTDIR)\DUMMYPAR.OBJ" : $(SOURCE) $(DEP_CPP_DUMMY) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\DUMMYPAR.SBR" : $(SOURCE) $(DEP_CPP_DUMMY) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 PseudoRelease"


"$(INTDIR)\DUMMYPAR.OBJ" : $(SOURCE) $(DEP_CPP_DUMMY) "$(INTDIR)"\
 ".\win32\Release\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MRU.CPP
DEP_CPP_MRU_C=\
	".\BSCREXT.HXX"\
	".\BSCRIPT.HXX"\
	".\BSCRIPTP.HXX"\
	".\MRU.H"\
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
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XtsnPropAtl.h"\
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


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 PseudoRelease"


"$(INTDIR)\MRU.OBJ" : $(SOURCE) $(DEP_CPP_MRU_C) "$(INTDIR)"\
 ".\win32\Release\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\EBARRAY.CXX
DEP_CPP_EBARR=\
	".\BSCREXT.HXX"\
	".\BSCRIPT.HXX"\
	".\BSCRIPTP.HXX"\
	".\EBARRAY.HXX"\
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
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XtsnPropAtl.h"\
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


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 PseudoRelease"


"$(INTDIR)\EBARRAY.OBJ" : $(SOURCE) $(DEP_CPP_EBARR) "$(INTDIR)"\
 ".\win32\Release\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MACRO.CPP
DEP_CPP_MACRO=\
	".\BSCREXT.HXX"\
	".\BSCRIPT.H"\
	".\BSCRIPT.HXX"\
	".\BSCRIPTP.HXX"\
	".\ISCRPROP.H"\
	".\MACRGUID.H"\
	".\MACRO.H"\
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
	{$(INCLUDE)}"\iobjman.h"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XtsnPropAtl.h"\
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


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 PseudoRelease"


"$(INTDIR)\MACRO.OBJ" : $(SOURCE) $(DEP_CPP_MACRO) "$(INTDIR)"\
 ".\win32\Release\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SCRPTDLG.CPP

!IF  "$(CFG)" == "Bscriptn - Win32 Release"

DEP_CPP_SCRPT=\
	".\BSCRIPT.H"\
	".\BSCRIPTP.HXX"\
	".\CONSTSTR.H"\
	".\debfdlg.h"\
	".\ISCRPROP.H"\
	".\MACRGUID.H"\
	".\MACRO.H"\
	".\PROJSCR.H"\
	".\RELSCRPT.H"\
	".\RUNEBOBS.H"\
	".\RUNERR.H"\
	".\RUNSCORG.H"\
	".\SCRPTDLG.H"\
	".\STRINFO.H"\
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
	{$(INCLUDE)}"\iobjman.h"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\SCRPTDLG.OBJ" : $(SOURCE) $(DEP_CPP_SCRPT) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"

DEP_CPP_SCRPT=\
	".\BSCREXT.HXX"\
	".\BSCRIPT.H"\
	".\BSCRIPT.HXX"\
	".\BSCRIPTP.HXX"\
	".\CONSTSTR.H"\
	".\debfdlg.h"\
	".\ISCRPROP.H"\
	".\MACRGUID.H"\
	".\MACRO.H"\
	".\PROJSCR.H"\
	".\RELSCRPT.H"\
	".\RUNEBOBS.H"\
	".\RUNERR.H"\
	".\RUNSCORG.H"\
	".\SCRPTDLG.H"\
	".\STRINFO.H"\
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
	{$(INCLUDE)}"\iobjman.h"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XtsnPropAtl.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\SCRPTDLG.OBJ" : $(SOURCE) $(DEP_CPP_SCRPT) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\SCRPTDLG.SBR" : $(SOURCE) $(DEP_CPP_SCRPT) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 PseudoRelease"

DEP_CPP_SCRPT=\
	".\BSCREXT.HXX"\
	".\BSCRIPT.H"\
	".\BSCRIPT.HXX"\
	".\BSCRIPTP.HXX"\
	".\CONSTSTR.H"\
	".\debfdlg.h"\
	".\ISCRPROP.H"\
	".\MACRGUID.H"\
	".\MACRO.H"\
	".\PROJSCR.H"\
	".\RELSCRPT.H"\
	".\RUNEBOBS.H"\
	".\RUNERR.H"\
	".\RUNSCORG.H"\
	".\SCRPTDLG.H"\
	".\STRINFO.H"\
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
	{$(INCLUDE)}"\iobjman.h"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XtsnPropAtl.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\SCRPTDLG.OBJ" : $(SOURCE) $(DEP_CPP_SCRPT) "$(INTDIR)"\
 ".\win32\Release\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ctfgeogk.CXX
DEP_CPP_CTFGE=\
	".\BSCREXT.HXX"\
	".\BSCRIPT.HXX"\
	".\BSCRIPTP.HXX"\
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
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XtsnPropAtl.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Bscriptn - Win32 Release"


"$(INTDIR)\ctfgeogk.obj" : $(SOURCE) $(DEP_CPP_CTFGE) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"


"$(INTDIR)\ctfgeogk.obj" : $(SOURCE) $(DEP_CPP_CTFGE) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\ctfgeogk.sbr" : $(SOURCE) $(DEP_CPP_CTFGE) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 PseudoRelease"


"$(INTDIR)\ctfgeogk.obj" : $(SOURCE) $(DEP_CPP_CTFGE) "$(INTDIR)"\
 ".\win32\Release\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MLONGSTR.CXX
DEP_CPP_MLONG=\
	".\BSCREXT.HXX"\
	".\BSCRIPT.HXX"\
	".\BSCRIPTP.HXX"\
	".\MLONGSTR.HXX"\
	".\MLONGSTR.INL"\
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
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XtsnPropAtl.h"\
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


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 PseudoRelease"


"$(INTDIR)\MLONGSTR.OBJ" : $(SOURCE) $(DEP_CPP_MLONG) "$(INTDIR)"\
 ".\win32\Release\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MSTRSTR.CXX
DEP_CPP_MSTRS=\
	".\BSCREXT.HXX"\
	".\BSCRIPT.HXX"\
	".\BSCRIPTP.HXX"\
	".\MSTRSTR.HXX"\
	".\MSTRSTR.INL"\
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
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XtsnPropAtl.h"\
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


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 PseudoRelease"


"$(INTDIR)\MSTRSTR.OBJ" : $(SOURCE) $(DEP_CPP_MSTRS) "$(INTDIR)"\
 ".\win32\Release\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\REXPSTR.CPP
DEP_CPP_REXPS=\
	".\BSCREXT.HXX"\
	".\BSCRIPT.HXX"\
	".\BSCRIPTP.HXX"\
	".\REXPSTR.H"\
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
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XtsnPropAtl.h"\
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


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 PseudoRelease"


"$(INTDIR)\REXPSTR.OBJ" : $(SOURCE) $(DEP_CPP_REXPS) "$(INTDIR)"\
 ".\win32\Release\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\BSCREXTF.CPP
DEP_CPP_BSCREX=\
	".\BSCREXT.HXX"\
	".\BSCREXTF.H"\
	".\BSCRIPT.HXX"\
	".\BSCRIPTP.HXX"\
	".\EBARRAY.HXX"\
	".\MLONGSTR.HXX"\
	".\MLONGSTR.INL"\
	".\MSTRSTR.HXX"\
	".\MSTRSTR.INL"\
	".\REXPSTR.H"\
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
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XtsnPropAtl.h"\
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


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 PseudoRelease"


"$(INTDIR)\BSCREXTF.OBJ" : $(SOURCE) $(DEP_CPP_BSCREX) "$(INTDIR)"\
 ".\win32\Release\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Triasext.cxx
DEP_CPP_TRIAS=\
	".\BSCREXT.HXX"\
	".\BSCRIPT.HXX"\
	".\BSCRIPTP.HXX"\
	".\TRIASEXT.H"\
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
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XtsnPropAtl.h"\
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


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 PseudoRelease"


"$(INTDIR)\Triasext.obj" : $(SOURCE) $(DEP_CPP_TRIAS) "$(INTDIR)"\
 ".\win32\Release\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Runscorg.cpp

!IF  "$(CFG)" == "Bscriptn - Win32 Release"

DEP_CPP_RUNSC=\
	".\BSCRIPT.H"\
	".\BSCRIPTP.HXX"\
	".\ISCRPROP.H"\
	".\MACRGUID.H"\
	".\RUNSCORG.H"\
	

"$(INTDIR)\Runscorg.obj" : $(SOURCE) $(DEP_CPP_RUNSC) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"

DEP_CPP_RUNSC=\
	".\BSCREXT.HXX"\
	".\BSCRIPT.H"\
	".\BSCRIPT.HXX"\
	".\BSCRIPTP.HXX"\
	".\ISCRPROP.H"\
	".\MACRGUID.H"\
	".\RUNSCORG.H"\
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
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XtsnPropAtl.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\Runscorg.obj" : $(SOURCE) $(DEP_CPP_RUNSC) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\Runscorg.sbr" : $(SOURCE) $(DEP_CPP_RUNSC) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 PseudoRelease"

DEP_CPP_RUNSC=\
	".\BSCREXT.HXX"\
	".\BSCRIPT.H"\
	".\BSCRIPT.HXX"\
	".\BSCRIPTP.HXX"\
	".\ISCRPROP.H"\
	".\MACRGUID.H"\
	".\RUNSCORG.H"\
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
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XtsnPropAtl.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\Runscorg.obj" : $(SOURCE) $(DEP_CPP_RUNSC) "$(INTDIR)"\
 ".\win32\Release\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Propactb.cxx
DEP_CPP_PROPA=\
	".\BSCREXT.HXX"\
	".\BSCRIPT.HXX"\
	".\BSCRIPTP.HXX"\
	".\CONSTSTR.H"\
	".\DATAHELP.H"\
	".\Propactb.hxx"\
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
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\Helper_i.c"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\propactn.h"\
	{$(INCLUDE)}"\selobwnd.h"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XtsnPropAtl.h"\
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


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 PseudoRelease"


"$(INTDIR)\Propactb.obj" : $(SOURCE) $(DEP_CPP_PROPA) "$(INTDIR)"\
 ".\win32\Release\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\filtscr.cpp

!IF  "$(CFG)" == "Bscriptn - Win32 Release"

DEP_CPP_FILTS=\
	".\BSCRIPT.H"\
	".\BSCRIPTP.HXX"\
	".\CONSTSTR.H"\
	".\DATAHELP.H"\
	".\filtdlg2.h"\
	".\FILTSCR.H"\
	".\ISCRPROP.H"\
	".\MACRGUID.H"\
	".\MACRO.H"\
	".\Propactb.hxx"\
	".\RUNERR.H"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\Ipropseq.hxx"\
	{$(INCLUDE)}"\OLEGUID.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\Pdataobj.hxx"\
	{$(INCLUDE)}"\propactn.h"\
	{$(INCLUDE)}"\selobwnd.h"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\filtscr.obj" : $(SOURCE) $(DEP_CPP_FILTS) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"

DEP_CPP_FILTS=\
	".\BSCREXT.HXX"\
	".\BSCRIPT.H"\
	".\BSCRIPT.HXX"\
	".\BSCRIPTP.HXX"\
	".\CONSTSTR.H"\
	".\DATAHELP.H"\
	".\filtdlg2.h"\
	".\FILTSCR.H"\
	".\ISCRPROP.H"\
	".\MACRGUID.H"\
	".\MACRO.H"\
	".\Propactb.hxx"\
	".\RUNERR.H"\
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
	{$(INCLUDE)}"\FSTREAM"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
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
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Pdataobj.hxx"\
	{$(INCLUDE)}"\propactn.h"\
	{$(INCLUDE)}"\selobwnd.h"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XtsnPropAtl.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\filtscr.obj" : $(SOURCE) $(DEP_CPP_FILTS) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\filtscr.sbr" : $(SOURCE) $(DEP_CPP_FILTS) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 PseudoRelease"

DEP_CPP_FILTS=\
	".\BSCREXT.HXX"\
	".\BSCRIPT.H"\
	".\BSCRIPT.HXX"\
	".\BSCRIPTP.HXX"\
	".\CONSTSTR.H"\
	".\DATAHELP.H"\
	".\filtdlg2.h"\
	".\FILTSCR.H"\
	".\ISCRPROP.H"\
	".\MACRGUID.H"\
	".\MACRO.H"\
	".\Propactb.hxx"\
	".\RUNERR.H"\
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
	{$(INCLUDE)}"\FSTREAM"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
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
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Pdataobj.hxx"\
	{$(INCLUDE)}"\propactn.h"\
	{$(INCLUDE)}"\selobwnd.h"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XtsnPropAtl.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\filtscr.obj" : $(SOURCE) $(DEP_CPP_FILTS) "$(INTDIR)"\
 ".\win32\Release\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\runerr.cpp

!IF  "$(CFG)" == "Bscriptn - Win32 Release"

DEP_CPP_RUNER=\
	".\BSCRIPT.H"\
	".\BSCRIPTP.HXX"\
	".\cmbnot.h"\
	".\DEBCTRL.H"\
	".\ISCRPROP.H"\
	".\MACRGUID.H"\
	".\RELSCRPT.H"\
	".\RUNERR.H"\
	".\RUNSCORG.H"\
	".\SPLIT.H"\
	".\SPLITTER.H"\
	".\TOOLBARX.H"\
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
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\iobjman.h"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OLEGUID.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\runerr.obj" : $(SOURCE) $(DEP_CPP_RUNER) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"

DEP_CPP_RUNER=\
	".\BSCREXT.HXX"\
	".\BSCRIPT.H"\
	".\BSCRIPT.HXX"\
	".\BSCRIPTP.HXX"\
	".\cmbnot.h"\
	".\DEBCTRL.H"\
	".\ISCRPROP.H"\
	".\MACRGUID.H"\
	".\RELSCRPT.H"\
	".\RUNERR.H"\
	".\RUNSCORG.H"\
	".\SPLIT.H"\
	".\SPLITTER.H"\
	".\TOOLBARX.H"\
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
	{$(INCLUDE)}"\FSTREAM"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\iobjman.h"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
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
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XtsnPropAtl.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\runerr.obj" : $(SOURCE) $(DEP_CPP_RUNER) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\runerr.sbr" : $(SOURCE) $(DEP_CPP_RUNER) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 PseudoRelease"

DEP_CPP_RUNER=\
	".\BSCREXT.HXX"\
	".\BSCRIPT.H"\
	".\BSCRIPT.HXX"\
	".\BSCRIPTP.HXX"\
	".\cmbnot.h"\
	".\DEBCTRL.H"\
	".\ISCRPROP.H"\
	".\MACRGUID.H"\
	".\RELSCRPT.H"\
	".\RUNERR.H"\
	".\RUNSCORG.H"\
	".\SPLIT.H"\
	".\SPLITTER.H"\
	".\TOOLBARX.H"\
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
	{$(INCLUDE)}"\FSTREAM"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\iobjman.h"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
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
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XtsnPropAtl.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\runerr.obj" : $(SOURCE) $(DEP_CPP_RUNER) "$(INTDIR)"\
 ".\win32\Release\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FNDRPLD.CPP
DEP_CPP_FNDRP=\
	".\BSCREXT.HXX"\
	".\BSCRIPT.H"\
	".\BSCRIPT.HXX"\
	".\BSCRIPTP.HXX"\
	".\FNDRPLD.H"\
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
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XtsnPropAtl.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Bscriptn - Win32 Release"


"$(INTDIR)\FNDRPLD.OBJ" : $(SOURCE) $(DEP_CPP_FNDRP) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"


"$(INTDIR)\FNDRPLD.OBJ" : $(SOURCE) $(DEP_CPP_FNDRP) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\FNDRPLD.SBR" : $(SOURCE) $(DEP_CPP_FNDRP) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 PseudoRelease"


"$(INTDIR)\FNDRPLD.OBJ" : $(SOURCE) $(DEP_CPP_FNDRP) "$(INTDIR)"\
 ".\win32\Release\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\conststr.cpp
DEP_CPP_CONST=\
	".\BSCREXT.HXX"\
	".\BSCRIPT.HXX"\
	".\BSCRIPTP.HXX"\
	".\CONSTSTR.H"\
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
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XtsnPropAtl.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Bscriptn - Win32 Release"


"$(INTDIR)\conststr.obj" : $(SOURCE) $(DEP_CPP_CONST) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"


"$(INTDIR)\conststr.obj" : $(SOURCE) $(DEP_CPP_CONST) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\conststr.sbr" : $(SOURCE) $(DEP_CPP_CONST) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 PseudoRelease"


"$(INTDIR)\conststr.obj" : $(SOURCE) $(DEP_CPP_CONST) "$(INTDIR)"\
 ".\win32\Release\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Win32\Bscript.def

!IF  "$(CFG)" == "Bscriptn - Win32 Release"

!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"

!ELSEIF  "$(CFG)" == "Bscriptn - Win32 PseudoRelease"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Win32\Bscript.rc
DEP_RSC_BSCRIPT=\
	".\Win32\Azhelp.rc"\
	".\Win32\bswrapperextension.rgs"\
	".\Win32\CreateObjectFeatureFileScript.rgs"\
	".\Win32\CreateObjectFeatureScript.rgs"\
	".\Win32\Dd.rc"\
	".\Win32\Dg.rc"\
	".\Win32\expimpscript.rgs"\
	".\Win32\FilterScript.rgs"\
	".\Win32\Macro.ico"\
	".\Win32\MacroFileScript.rgs"\
	".\Win32\Macros3.bmp"\
	".\Win32\MacroScript.rgs"\
	".\Win32\notif.not"\
	".\Win32\oftppxt.rgs"\
	".\Win32\projectt.bmp"\
	".\Win32\propertyactiond.ebc"\
	".\Win32\PropertyActionr.ebc"\
	".\Win32\RegisterEbs.rgs"\
	".\Win32\RegisterEbs207.rgs"\
	".\Win32\RegisterScript.rgs"\
	".\Win32\StreamInfo.rgs"\
	".\Win32\Toolbar.bmp"\
	".\Win32\Topics.h"\
	
NODEP_RSC_BSCRIPT=\
	".\Win32\Bscrext.rc"\
	".\Win32\Bscript.rcv"\
	

!IF  "$(CFG)" == "Bscriptn - Win32 Release"


"$(INTDIR)\Bscript.res" : $(SOURCE) $(DEP_RSC_BSCRIPT) "$(INTDIR)"
   $(RSC) /l 0x407 /fo"$(INTDIR)/Bscript.res" /i "Win32" /d "NDEBUG" /d\
 "_AFXDLL" /d "_OLDCATIDS" $(SOURCE)


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"


"$(INTDIR)\Bscriptd.res" : $(SOURCE) $(DEP_RSC_BSCRIPT) "$(INTDIR)"
   $(RSC) /l 0x407 /fo"$(INTDIR)/Bscriptd.res" /i "Win32" /d "_DEBUG" /d\
 "_AFXDLL" /d "_OLDCATIDS" $(SOURCE)


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 PseudoRelease"


"$(INTDIR)\Bscript.res" : $(SOURCE) $(DEP_RSC_BSCRIPT) "$(INTDIR)"
   $(RSC) /l 0x407 /fo"$(INTDIR)/Bscript.res" /i "Win32" /d "NDEBUG" /d\
 "_AFXDLL" /d "PSDEBUG" $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\objfeat.cpp

!IF  "$(CFG)" == "Bscriptn - Win32 Release"

DEP_CPP_OBJFE=\
	".\BSCRIPT.H"\
	".\BSCRIPTP.HXX"\
	".\BSParam.h"\
	".\ISCRPROP.H"\
	".\MACRGUID.H"\
	".\MACRO.H"\
	".\OBJFEAT.H"\
	".\RELSCRPT.H"\
	".\RUNERR.H"\
	".\RUNSCORG.H"\
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
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\iobjman.h"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OLEGUID.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\objfeat.obj" : $(SOURCE) $(DEP_CPP_OBJFE) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"

DEP_CPP_OBJFE=\
	".\BSCREXT.HXX"\
	".\BSCRIPT.H"\
	".\BSCRIPT.HXX"\
	".\BSCRIPTP.HXX"\
	".\BSParam.h"\
	".\ISCRPROP.H"\
	".\MACRGUID.H"\
	".\MACRO.H"\
	".\OBJFEAT.H"\
	".\RELSCRPT.H"\
	".\RUNERR.H"\
	".\RUNSCORG.H"\
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
	{$(INCLUDE)}"\FSTREAM"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\iobjman.h"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
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
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XtsnPropAtl.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\objfeat.obj" : $(SOURCE) $(DEP_CPP_OBJFE) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\objfeat.sbr" : $(SOURCE) $(DEP_CPP_OBJFE) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 PseudoRelease"

DEP_CPP_OBJFE=\
	".\BSCREXT.HXX"\
	".\BSCRIPT.H"\
	".\BSCRIPT.HXX"\
	".\BSCRIPTP.HXX"\
	".\BSParam.h"\
	".\ISCRPROP.H"\
	".\MACRGUID.H"\
	".\MACRO.H"\
	".\OBJFEAT.H"\
	".\RELSCRPT.H"\
	".\RUNERR.H"\
	".\RUNSCORG.H"\
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
	{$(INCLUDE)}"\FSTREAM"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\iobjman.h"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
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
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XtsnPropAtl.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\objfeat.obj" : $(SOURCE) $(DEP_CPP_OBJFE) "$(INTDIR)"\
 ".\win32\Release\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Strinfo.cpp
DEP_CPP_STRIN=\
	".\BSCREXT.HXX"\
	".\BSCRIPT.H"\
	".\BSCRIPT.HXX"\
	".\BSCRIPTP.HXX"\
	".\ISCRPROP.H"\
	".\MACRGUID.H"\
	".\STRINFO.H"\
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
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\OLESTREA.H"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\OLESTREA.H"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XtsnPropAtl.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Bscriptn - Win32 Release"


"$(INTDIR)\Strinfo.obj" : $(SOURCE) $(DEP_CPP_STRIN) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"


"$(INTDIR)\Strinfo.obj" : $(SOURCE) $(DEP_CPP_STRIN) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\Strinfo.sbr" : $(SOURCE) $(DEP_CPP_STRIN) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 PseudoRelease"


"$(INTDIR)\Strinfo.obj" : $(SOURCE) $(DEP_CPP_STRIN) "$(INTDIR)"\
 ".\win32\Release\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\split.cpp

!IF  "$(CFG)" == "Bscriptn - Win32 Release"

DEP_CPP_SPLIT=\
	".\addfdlg.h"\
	".\BSCRIPT.H"\
	".\BSCRIPTP.HXX"\
	".\cmbnot.h"\
	".\CONSTSTR.H"\
	".\dbfrmvw.h"\
	".\DbFrmVw2.h"\
	".\DEBCTRL.H"\
	".\debfdlg.h"\
	".\DUMMYPAR.H"\
	".\ISCRPROP.H"\
	".\MACRGUID.H"\
	".\MRU.H"\
	".\PROJSCR.H"\
	".\RELSCRPT.H"\
	".\RUNEBOBS.H"\
	".\RUNERR.H"\
	".\RUNSCORG.H"\
	".\SPLIT.H"\
	".\SPLITTER.H"\
	".\SPLTREE.H"\
	".\STRINFO.H"\
	".\tmplman.h"\
	".\TOOLBARX.H"\
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
	{$(INCLUDE)}"\iobjman.h"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\split.obj" : $(SOURCE) $(DEP_CPP_SPLIT) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"

DEP_CPP_SPLIT=\
	".\addfdlg.h"\
	".\BSCREXT.HXX"\
	".\BSCRIPT.H"\
	".\BSCRIPT.HXX"\
	".\BSCRIPTP.HXX"\
	".\cmbnot.h"\
	".\CONSTSTR.H"\
	".\dbfrmvw.h"\
	".\DbFrmVw2.h"\
	".\DEBCTRL.H"\
	".\debfdlg.h"\
	".\DUMMYPAR.H"\
	".\ISCRPROP.H"\
	".\MACRGUID.H"\
	".\MRU.H"\
	".\PROJSCR.H"\
	".\RELSCRPT.H"\
	".\RUNEBOBS.H"\
	".\RUNERR.H"\
	".\RUNSCORG.H"\
	".\SPLIT.H"\
	".\SPLITTER.H"\
	".\SPLTREE.H"\
	".\STRINFO.H"\
	".\tmplman.h"\
	".\TOOLBARX.H"\
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
	{$(INCLUDE)}"\iobjman.h"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XtsnPropAtl.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\split.obj" : $(SOURCE) $(DEP_CPP_SPLIT) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\split.sbr" : $(SOURCE) $(DEP_CPP_SPLIT) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 PseudoRelease"

DEP_CPP_SPLIT=\
	".\addfdlg.h"\
	".\BSCREXT.HXX"\
	".\BSCRIPT.H"\
	".\BSCRIPT.HXX"\
	".\BSCRIPTP.HXX"\
	".\cmbnot.h"\
	".\CONSTSTR.H"\
	".\dbfrmvw.h"\
	".\DbFrmVw2.h"\
	".\DEBCTRL.H"\
	".\debfdlg.h"\
	".\DUMMYPAR.H"\
	".\ISCRPROP.H"\
	".\MACRGUID.H"\
	".\MRU.H"\
	".\PROJSCR.H"\
	".\RELSCRPT.H"\
	".\RUNEBOBS.H"\
	".\RUNERR.H"\
	".\RUNSCORG.H"\
	".\SPLIT.H"\
	".\SPLITTER.H"\
	".\SPLTREE.H"\
	".\STRINFO.H"\
	".\tmplman.h"\
	".\TOOLBARX.H"\
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
	{$(INCLUDE)}"\iobjman.h"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XtsnPropAtl.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\split.obj" : $(SOURCE) $(DEP_CPP_SPLIT) "$(INTDIR)"\
 ".\win32\Release\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DebCtrl.cpp

!IF  "$(CFG)" == "Bscriptn - Win32 Release"

DEP_CPP_DEBCT=\
	".\BSCRIPT.H"\
	".\BSCRIPTP.HXX"\
	".\BSParam.h"\
	".\cmbnot.h"\
	".\CONSTSTR.H"\
	".\DEBCTRL.H"\
	".\DUMMYPAR.H"\
	".\EDITCTRL.H"\
	".\FNDRPLD.H"\
	".\ISCRPROP.H"\
	".\MACRGUID.H"\
	".\PROJSCR.H"\
	".\RELSCRPT.H"\
	".\RUNEBOBS.H"\
	".\RUNERR.H"\
	".\RUNSCORG.H"\
	".\SPLIT.H"\
	".\SPLITTER.H"\
	".\SPLTREE.H"\
	".\STRINFO.H"\
	".\TOOLBARX.H"\
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
	{$(INCLUDE)}"\iobjman.h"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\DebCtrl.obj" : $(SOURCE) $(DEP_CPP_DEBCT) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"

DEP_CPP_DEBCT=\
	".\BSCREXT.HXX"\
	".\BSCRIPT.H"\
	".\BSCRIPT.HXX"\
	".\BSCRIPTP.HXX"\
	".\BSParam.h"\
	".\cmbnot.h"\
	".\CONSTSTR.H"\
	".\DEBCTRL.H"\
	".\DUMMYPAR.H"\
	".\EDITCTRL.H"\
	".\FNDRPLD.H"\
	".\ISCRPROP.H"\
	".\MACRGUID.H"\
	".\PROJSCR.H"\
	".\RELSCRPT.H"\
	".\RUNEBOBS.H"\
	".\RUNERR.H"\
	".\RUNSCORG.H"\
	".\SPLIT.H"\
	".\SPLITTER.H"\
	".\SPLTREE.H"\
	".\STRINFO.H"\
	".\TOOLBARX.H"\
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
	{$(INCLUDE)}"\iobjman.h"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XtsnPropAtl.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\DebCtrl.obj" : $(SOURCE) $(DEP_CPP_DEBCT) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\DebCtrl.sbr" : $(SOURCE) $(DEP_CPP_DEBCT) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 PseudoRelease"

DEP_CPP_DEBCT=\
	".\BSCREXT.HXX"\
	".\BSCRIPT.H"\
	".\BSCRIPT.HXX"\
	".\BSCRIPTP.HXX"\
	".\BSParam.h"\
	".\cmbnot.h"\
	".\CONSTSTR.H"\
	".\DEBCTRL.H"\
	".\DUMMYPAR.H"\
	".\EDITCTRL.H"\
	".\FNDRPLD.H"\
	".\ISCRPROP.H"\
	".\MACRGUID.H"\
	".\PROJSCR.H"\
	".\RELSCRPT.H"\
	".\RUNEBOBS.H"\
	".\RUNERR.H"\
	".\RUNSCORG.H"\
	".\SPLIT.H"\
	".\SPLITTER.H"\
	".\SPLTREE.H"\
	".\STRINFO.H"\
	".\TOOLBARX.H"\
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
	{$(INCLUDE)}"\iobjman.h"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XtsnPropAtl.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\DebCtrl.obj" : $(SOURCE) $(DEP_CPP_DEBCT) "$(INTDIR)"\
 ".\win32\Release\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\spltree.cpp
DEP_CPP_SPLTR=\
	".\BSCREXT.HXX"\
	".\BSCRIPT.H"\
	".\BSCRIPT.HXX"\
	".\BSCRIPTP.HXX"\
	".\cmbnot.h"\
	".\CONSTSTR.H"\
	".\DEBCTRL.H"\
	".\ISCRPROP.H"\
	".\MACRGUID.H"\
	".\PROJSCR.H"\
	".\RELSCRPT.H"\
	".\SPLIT.H"\
	".\SPLITTER.H"\
	".\SPLTREE.H"\
	".\TOOLBARX.H"\
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
	{$(INCLUDE)}"\iobjman.h"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XtsnPropAtl.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Bscriptn - Win32 Release"


"$(INTDIR)\spltree.obj" : $(SOURCE) $(DEP_CPP_SPLTR) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"


"$(INTDIR)\spltree.obj" : $(SOURCE) $(DEP_CPP_SPLTR) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\spltree.sbr" : $(SOURCE) $(DEP_CPP_SPLTR) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 PseudoRelease"


"$(INTDIR)\spltree.obj" : $(SOURCE) $(DEP_CPP_SPLTR) "$(INTDIR)"\
 ".\win32\Release\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\relscrpt.cpp

!IF  "$(CFG)" == "Bscriptn - Win32 Release"

DEP_CPP_RELSC=\
	".\BSCRIPT.H"\
	".\BSCRIPTP.HXX"\
	".\ISCRPROP.H"\
	".\MACRGUID.H"\
	".\PROJSCR.H"\
	".\RELSCRPT.H"\
	".\RUNEBOBS.H"\
	".\RUNSCORG.H"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\iobjman.h"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\relscrpt.obj" : $(SOURCE) $(DEP_CPP_RELSC) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"

DEP_CPP_RELSC=\
	".\BSCREXT.HXX"\
	".\BSCRIPT.H"\
	".\BSCRIPT.HXX"\
	".\BSCRIPTP.HXX"\
	".\ISCRPROP.H"\
	".\MACRGUID.H"\
	".\PROJSCR.H"\
	".\RELSCRPT.H"\
	".\RUNEBOBS.H"\
	".\RUNSCORG.H"\
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
	{$(INCLUDE)}"\iobjman.h"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XtsnPropAtl.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\relscrpt.obj" : $(SOURCE) $(DEP_CPP_RELSC) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\relscrpt.sbr" : $(SOURCE) $(DEP_CPP_RELSC) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 PseudoRelease"

DEP_CPP_RELSC=\
	".\BSCREXT.HXX"\
	".\BSCRIPT.H"\
	".\BSCRIPT.HXX"\
	".\BSCRIPTP.HXX"\
	".\ISCRPROP.H"\
	".\MACRGUID.H"\
	".\PROJSCR.H"\
	".\RELSCRPT.H"\
	".\RUNEBOBS.H"\
	".\RUNSCORG.H"\
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
	{$(INCLUDE)}"\iobjman.h"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XtsnPropAtl.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\relscrpt.obj" : $(SOURCE) $(DEP_CPP_RELSC) "$(INTDIR)"\
 ".\win32\Release\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\projscr.cpp
DEP_CPP_PROJS=\
	".\BSCREXT.HXX"\
	".\BSCRIPT.H"\
	".\BSCRIPT.HXX"\
	".\BSCRIPTP.HXX"\
	".\CONSTSTR.H"\
	".\ISCRPROP.H"\
	".\MACRGUID.H"\
	".\PROJSCR.H"\
	".\SPLTREE.H"\
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
	{$(INCLUDE)}"\iobjman.h"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XtsnPropAtl.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Bscriptn - Win32 Release"


"$(INTDIR)\projscr.obj" : $(SOURCE) $(DEP_CPP_PROJS) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"


"$(INTDIR)\projscr.obj" : $(SOURCE) $(DEP_CPP_PROJS) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\projscr.sbr" : $(SOURCE) $(DEP_CPP_PROJS) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 PseudoRelease"


"$(INTDIR)\projscr.obj" : $(SOURCE) $(DEP_CPP_PROJS) "$(INTDIR)"\
 ".\win32\Release\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\splitter.cpp
DEP_CPP_SPLITT=\
	".\BSCREXT.HXX"\
	".\BSCRIPT.H"\
	".\BSCRIPT.HXX"\
	".\BSCRIPTP.HXX"\
	".\cmbnot.h"\
	".\SPLIT.H"\
	".\SPLITTER.H"\
	".\TOOLBARX.H"\
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
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XtsnPropAtl.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Bscriptn - Win32 Release"


"$(INTDIR)\splitter.obj" : $(SOURCE) $(DEP_CPP_SPLITT) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"


"$(INTDIR)\splitter.obj" : $(SOURCE) $(DEP_CPP_SPLITT) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\splitter.sbr" : $(SOURCE) $(DEP_CPP_SPLITT) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 PseudoRelease"


"$(INTDIR)\splitter.obj" : $(SOURCE) $(DEP_CPP_SPLITT) "$(INTDIR)"\
 ".\win32\Release\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\editctrl.cpp

!IF  "$(CFG)" == "Bscriptn - Win32 Release"

DEP_CPP_EDITC=\
	".\BSCRIPT.H"\
	".\BSCRIPTP.HXX"\
	".\cmbnot.h"\
	".\CONSTSTR.H"\
	".\DEBCTRL.H"\
	".\DUMMYPAR.H"\
	".\EDITCTRL.H"\
	".\ISCRPROP.H"\
	".\MACRGUID.H"\
	".\MRU.H"\
	".\RELSCRPT.H"\
	".\RUNSCORG.H"\
	".\SPLIT.H"\
	".\SPLITTER.H"\
	".\STRINFO.H"\
	".\TOOLBARX.H"\
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
	{$(INCLUDE)}"\iobjman.h"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\editctrl.obj" : $(SOURCE) $(DEP_CPP_EDITC) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"

DEP_CPP_EDITC=\
	".\BSCREXT.HXX"\
	".\BSCRIPT.H"\
	".\BSCRIPT.HXX"\
	".\BSCRIPTP.HXX"\
	".\cmbnot.h"\
	".\CONSTSTR.H"\
	".\DEBCTRL.H"\
	".\DUMMYPAR.H"\
	".\EDITCTRL.H"\
	".\ISCRPROP.H"\
	".\MACRGUID.H"\
	".\MRU.H"\
	".\RELSCRPT.H"\
	".\RUNSCORG.H"\
	".\SPLIT.H"\
	".\SPLITTER.H"\
	".\STRINFO.H"\
	".\TOOLBARX.H"\
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
	{$(INCLUDE)}"\iobjman.h"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XtsnPropAtl.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\editctrl.obj" : $(SOURCE) $(DEP_CPP_EDITC) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\editctrl.sbr" : $(SOURCE) $(DEP_CPP_EDITC) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 PseudoRelease"

DEP_CPP_EDITC=\
	".\BSCREXT.HXX"\
	".\BSCRIPT.H"\
	".\BSCRIPT.HXX"\
	".\BSCRIPTP.HXX"\
	".\cmbnot.h"\
	".\CONSTSTR.H"\
	".\DEBCTRL.H"\
	".\DUMMYPAR.H"\
	".\EDITCTRL.H"\
	".\ISCRPROP.H"\
	".\MACRGUID.H"\
	".\MRU.H"\
	".\RELSCRPT.H"\
	".\RUNSCORG.H"\
	".\SPLIT.H"\
	".\SPLITTER.H"\
	".\STRINFO.H"\
	".\TOOLBARX.H"\
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
	{$(INCLUDE)}"\iobjman.h"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XtsnPropAtl.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\editctrl.obj" : $(SOURCE) $(DEP_CPP_EDITC) "$(INTDIR)"\
 ".\win32\Release\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\runebobs.cpp

!IF  "$(CFG)" == "Bscriptn - Win32 Release"

DEP_CPP_RUNEB=\
	".\BSCRIPT.H"\
	".\BSCRIPTP.HXX"\
	".\BSParam.h"\
	".\cmbnot.h"\
	".\CONSTSTR.H"\
	".\ISCRPROP.H"\
	".\MACRGUID.H"\
	".\PROJSCR.H"\
	".\RELSCRPT.H"\
	".\RUNEBOBS.H"\
	".\RUNERR.H"\
	".\RUNSCORG.H"\
	".\SPLIT.H"\
	".\SPLITTER.H"\
	".\TOOLBARX.H"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\iobjman.h"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\runebobs.obj" : $(SOURCE) $(DEP_CPP_RUNEB) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"

DEP_CPP_RUNEB=\
	".\BSCREXT.HXX"\
	".\BSCRIPT.H"\
	".\BSCRIPT.HXX"\
	".\BSCRIPTP.HXX"\
	".\BSParam.h"\
	".\cmbnot.h"\
	".\CONSTSTR.H"\
	".\ISCRPROP.H"\
	".\MACRGUID.H"\
	".\PROJSCR.H"\
	".\RELSCRPT.H"\
	".\RUNEBOBS.H"\
	".\RUNERR.H"\
	".\RUNSCORG.H"\
	".\SPLIT.H"\
	".\SPLITTER.H"\
	".\TOOLBARX.H"\
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
	{$(INCLUDE)}"\iobjman.h"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XtsnPropAtl.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\runebobs.obj" : $(SOURCE) $(DEP_CPP_RUNEB) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\runebobs.sbr" : $(SOURCE) $(DEP_CPP_RUNEB) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 PseudoRelease"

DEP_CPP_RUNEB=\
	".\BSCREXT.HXX"\
	".\BSCRIPT.H"\
	".\BSCRIPT.HXX"\
	".\BSCRIPTP.HXX"\
	".\BSParam.h"\
	".\cmbnot.h"\
	".\CONSTSTR.H"\
	".\ISCRPROP.H"\
	".\MACRGUID.H"\
	".\PROJSCR.H"\
	".\RELSCRPT.H"\
	".\RUNEBOBS.H"\
	".\RUNERR.H"\
	".\RUNSCORG.H"\
	".\SPLIT.H"\
	".\SPLITTER.H"\
	".\TOOLBARX.H"\
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
	{$(INCLUDE)}"\iobjman.h"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XtsnPropAtl.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\runebobs.obj" : $(SOURCE) $(DEP_CPP_RUNEB) "$(INTDIR)"\
 ".\win32\Release\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\addfdlg.cpp
DEP_CPP_ADDFD=\
	".\addfdlg.h"\
	".\BSCREXT.HXX"\
	".\BSCRIPT.H"\
	".\BSCRIPT.HXX"\
	".\BSCRIPTP.HXX"\
	".\tmplman.h"\
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
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XtsnPropAtl.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Bscriptn - Win32 Release"


"$(INTDIR)\addfdlg.obj" : $(SOURCE) $(DEP_CPP_ADDFD) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"


"$(INTDIR)\addfdlg.obj" : $(SOURCE) $(DEP_CPP_ADDFD) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\addfdlg.sbr" : $(SOURCE) $(DEP_CPP_ADDFD) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 PseudoRelease"


"$(INTDIR)\addfdlg.obj" : $(SOURCE) $(DEP_CPP_ADDFD) "$(INTDIR)"\
 ".\win32\Release\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\debfdlg.cpp
DEP_CPP_DEBFD=\
	".\BSCREXT.HXX"\
	".\BSCRIPT.H"\
	".\BSCRIPT.HXX"\
	".\BSCRIPTP.HXX"\
	".\debfdlg.h"\
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
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XtsnPropAtl.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Bscriptn - Win32 Release"


"$(INTDIR)\debfdlg.obj" : $(SOURCE) $(DEP_CPP_DEBFD) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"


"$(INTDIR)\debfdlg.obj" : $(SOURCE) $(DEP_CPP_DEBFD) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\debfdlg.sbr" : $(SOURCE) $(DEP_CPP_DEBFD) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 PseudoRelease"


"$(INTDIR)\debfdlg.obj" : $(SOURCE) $(DEP_CPP_DEBFD) "$(INTDIR)"\
 ".\win32\Release\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Ebc.cpp
DEP_CPP_EBC_C=\
	".\BSCREXT.HXX"\
	".\BSCRIPT.HXX"\
	".\BSCRIPTP.HXX"\
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
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XtsnPropAtl.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Bscriptn - Win32 Release"


"$(INTDIR)\Ebc.obj" : $(SOURCE) $(DEP_CPP_EBC_C) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"


"$(INTDIR)\Ebc.obj" : $(SOURCE) $(DEP_CPP_EBC_C) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\Ebc.sbr" : $(SOURCE) $(DEP_CPP_EBC_C) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 PseudoRelease"


"$(INTDIR)\Ebc.obj" : $(SOURCE) $(DEP_CPP_EBC_C) "$(INTDIR)"\
 ".\win32\Release\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\myfiledg.cpp
DEP_CPP_MYFIL=\
	".\BSCREXT.HXX"\
	".\BSCRIPT.H"\
	".\BSCRIPT.HXX"\
	".\BSCRIPTP.HXX"\
	".\myfiledg.h"\
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
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XtsnPropAtl.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Bscriptn - Win32 Release"


"$(INTDIR)\myfiledg.obj" : $(SOURCE) $(DEP_CPP_MYFIL) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"


"$(INTDIR)\myfiledg.obj" : $(SOURCE) $(DEP_CPP_MYFIL) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\myfiledg.sbr" : $(SOURCE) $(DEP_CPP_MYFIL) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 PseudoRelease"


"$(INTDIR)\myfiledg.obj" : $(SOURCE) $(DEP_CPP_MYFIL) "$(INTDIR)"\
 ".\win32\Release\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ofeatpp.cpp
DEP_CPP_OFEAT=\
	".\BSCREXT.HXX"\
	".\BSCRIPT.H"\
	".\BSCRIPT.HXX"\
	".\BSCRIPTP.HXX"\
	".\ISCRPROP.H"\
	".\MACRGUID.H"\
	".\MACRO.H"\
	".\OBJFEAT.H"\
	".\ofeatpp.h"\
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
	{$(INCLUDE)}"\FSTREAM"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\iobjman.h"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
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
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XtsnPropAtl.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Bscriptn - Win32 Release"


"$(INTDIR)\ofeatpp.obj" : $(SOURCE) $(DEP_CPP_OFEAT) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"


"$(INTDIR)\ofeatpp.obj" : $(SOURCE) $(DEP_CPP_OFEAT) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\ofeatpp.sbr" : $(SOURCE) $(DEP_CPP_OFEAT) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 PseudoRelease"


"$(INTDIR)\ofeatpp.obj" : $(SOURCE) $(DEP_CPP_OFEAT) "$(INTDIR)"\
 ".\win32\Release\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Datahelp.cpp
DEP_CPP_DATAH=\
	".\BSCREXT.HXX"\
	".\BSCRIPT.H"\
	".\BSCRIPT.HXX"\
	".\BSCRIPTP.HXX"\
	".\DATAHELP.H"\
	".\MACRGUID.H"\
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
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\oprpguid.h"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\propactn.h"\
	{$(INCLUDE)}"\selobwnd.h"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XtsnPropAtl.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Bscriptn - Win32 Release"


"$(INTDIR)\Datahelp.obj" : $(SOURCE) $(DEP_CPP_DATAH) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"


"$(INTDIR)\Datahelp.obj" : $(SOURCE) $(DEP_CPP_DATAH) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\Datahelp.sbr" : $(SOURCE) $(DEP_CPP_DATAH) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 PseudoRelease"


"$(INTDIR)\Datahelp.obj" : $(SOURCE) $(DEP_CPP_DATAH) "$(INTDIR)"\
 ".\win32\Release\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Filtdlg2.cpp

!IF  "$(CFG)" == "Bscriptn - Win32 Release"

DEP_CPP_FILTD=\
	".\BSCRIPT.H"\
	".\BSCRIPTP.HXX"\
	".\CONSTSTR.H"\
	".\filtdlg2.h"\
	".\ISCRPROP.H"\
	".\MACRGUID.H"\
	".\PROJSCR.H"\
	".\RELSCRPT.H"\
	".\RUNEBOBS.H"\
	".\RUNERR.H"\
	".\RUNSCORG.H"\
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
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\iGeoObjs.h"\
	{$(INCLUDE)}"\iobjman.h"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\itriasap.h"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OLEGUID.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\Filtdlg2.obj" : $(SOURCE) $(DEP_CPP_FILTD) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"

DEP_CPP_FILTD=\
	".\BSCREXT.HXX"\
	".\BSCRIPT.H"\
	".\BSCRIPT.HXX"\
	".\BSCRIPTP.HXX"\
	".\CONSTSTR.H"\
	".\filtdlg2.h"\
	".\ISCRPROP.H"\
	".\MACRGUID.H"\
	".\PROJSCR.H"\
	".\RELSCRPT.H"\
	".\RUNEBOBS.H"\
	".\RUNERR.H"\
	".\RUNSCORG.H"\
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
	{$(INCLUDE)}"\FSTREAM"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\iGeoObjs.h"\
	{$(INCLUDE)}"\iobjman.h"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
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
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XtsnPropAtl.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\Filtdlg2.obj" : $(SOURCE) $(DEP_CPP_FILTD) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\Filtdlg2.sbr" : $(SOURCE) $(DEP_CPP_FILTD) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 PseudoRelease"

DEP_CPP_FILTD=\
	".\BSCREXT.HXX"\
	".\BSCRIPT.H"\
	".\BSCRIPT.HXX"\
	".\BSCRIPTP.HXX"\
	".\CONSTSTR.H"\
	".\filtdlg2.h"\
	".\ISCRPROP.H"\
	".\MACRGUID.H"\
	".\PROJSCR.H"\
	".\RELSCRPT.H"\
	".\RUNEBOBS.H"\
	".\RUNERR.H"\
	".\RUNSCORG.H"\
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
	{$(INCLUDE)}"\FSTREAM"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\iGeoObjs.h"\
	{$(INCLUDE)}"\iobjman.h"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
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
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XtsnPropAtl.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\Filtdlg2.obj" : $(SOURCE) $(DEP_CPP_FILTD) "$(INTDIR)"\
 ".\win32\Release\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Wrapxt.cpp
DEP_CPP_WRAPX=\
	".\BSCREXT.HXX"\
	".\BSCRIPT.H"\
	".\BSCRIPT.HXX"\
	".\BSCRIPTP.HXX"\
	".\CONSTSTR.H"\
	".\MACRGUID.H"\
	".\Wrapxt.h"\
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
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XtsnPropAtl.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Bscriptn - Win32 Release"


"$(INTDIR)\Wrapxt.obj" : $(SOURCE) $(DEP_CPP_WRAPX) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"


"$(INTDIR)\Wrapxt.obj" : $(SOURCE) $(DEP_CPP_WRAPX) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\Wrapxt.sbr" : $(SOURCE) $(DEP_CPP_WRAPX) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 PseudoRelease"


"$(INTDIR)\Wrapxt.obj" : $(SOURCE) $(DEP_CPP_WRAPX) "$(INTDIR)"\
 ".\win32\Release\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\RegisterEbs.cpp

!IF  "$(CFG)" == "Bscriptn - Win32 Release"

DEP_CPP_REGIS=\
	".\BSCRIPT.H"\
	".\BSCRIPTP.HXX"\
	".\CONSTSTR.H"\
	".\MACRGUID.H"\
	".\RegisterEbs.h"\
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
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\RegisterEbs.obj" : $(SOURCE) $(DEP_CPP_REGIS) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"

DEP_CPP_REGIS=\
	".\BSCREXT.HXX"\
	".\BSCRIPT.H"\
	".\BSCRIPT.HXX"\
	".\BSCRIPTP.HXX"\
	".\CONSTSTR.H"\
	".\MACRGUID.H"\
	".\RegisterEbs.h"\
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
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TRiASHelper.h"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XtsnPropAtl.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\RegisterEbs.obj" : $(SOURCE) $(DEP_CPP_REGIS) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\RegisterEbs.sbr" : $(SOURCE) $(DEP_CPP_REGIS) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 PseudoRelease"

DEP_CPP_REGIS=\
	".\BSCREXT.HXX"\
	".\BSCRIPT.H"\
	".\BSCRIPT.HXX"\
	".\BSCRIPTP.HXX"\
	".\CONSTSTR.H"\
	".\MACRGUID.H"\
	".\RegisterEbs.h"\
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
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TRiASHelper.h"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XtsnPropAtl.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\RegisterEbs.obj" : $(SOURCE) $(DEP_CPP_REGIS) "$(INTDIR)"\
 ".\win32\Release\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\tmplman.cpp
DEP_CPP_TMPLM=\
	".\BSCREXT.HXX"\
	".\BSCRIPT.H"\
	".\BSCRIPT.HXX"\
	".\BSCRIPTP.HXX"\
	".\tmplman.h"\
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
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XtsnPropAtl.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Bscriptn - Win32 Release"


"$(INTDIR)\tmplman.obj" : $(SOURCE) $(DEP_CPP_TMPLM) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"


"$(INTDIR)\tmplman.obj" : $(SOURCE) $(DEP_CPP_TMPLM) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\tmplman.sbr" : $(SOURCE) $(DEP_CPP_TMPLM) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 PseudoRelease"


"$(INTDIR)\tmplman.obj" : $(SOURCE) $(DEP_CPP_TMPLM) "$(INTDIR)"\
 ".\win32\Release\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\cptvw.cpp
DEP_CPP_CPTVW=\
	".\BSCREXT.HXX"\
	".\BSCRIPT.H"\
	".\BSCRIPT.HXX"\
	".\BSCRIPTP.HXX"\
	".\cptvw.h"\
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
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XtsnPropAtl.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Bscriptn - Win32 Release"


"$(INTDIR)\cptvw.obj" : $(SOURCE) $(DEP_CPP_CPTVW) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"


"$(INTDIR)\cptvw.obj" : $(SOURCE) $(DEP_CPP_CPTVW) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\cptvw.sbr" : $(SOURCE) $(DEP_CPP_CPTVW) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 PseudoRelease"


"$(INTDIR)\cptvw.obj" : $(SOURCE) $(DEP_CPP_CPTVW) "$(INTDIR)"\
 ".\win32\Release\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dbfrmvw.cpp

!IF  "$(CFG)" == "Bscriptn - Win32 Release"

DEP_CPP_DBFRM=\
	".\BSCRIPT.H"\
	".\BSCRIPTP.HXX"\
	".\cmbnot.h"\
	".\CONSTSTR.H"\
	".\dbfrmvw.h"\
	".\DEBCTRL.H"\
	".\DUMMYPAR.H"\
	".\EDITCTRL.H"\
	".\FNDRPLD.H"\
	".\ISCRPROP.H"\
	".\MACRGUID.H"\
	".\PROJSCR.H"\
	".\RELSCRPT.H"\
	".\RUNEBOBS.H"\
	".\RUNERR.H"\
	".\RUNSCORG.H"\
	".\SPLIT.H"\
	".\SPLITTER.H"\
	".\SPLTREE.H"\
	".\STRINFO.H"\
	".\TOOLBARX.H"\
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
	{$(INCLUDE)}"\iobjman.h"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\dbfrmvw.obj" : $(SOURCE) $(DEP_CPP_DBFRM) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"

DEP_CPP_DBFRM=\
	".\BSCREXT.HXX"\
	".\BSCRIPT.H"\
	".\BSCRIPT.HXX"\
	".\BSCRIPTP.HXX"\
	".\cmbnot.h"\
	".\CONSTSTR.H"\
	".\dbfrmvw.h"\
	".\DEBCTRL.H"\
	".\DUMMYPAR.H"\
	".\EDITCTRL.H"\
	".\FNDRPLD.H"\
	".\ISCRPROP.H"\
	".\MACRGUID.H"\
	".\PROJSCR.H"\
	".\RELSCRPT.H"\
	".\RUNEBOBS.H"\
	".\RUNERR.H"\
	".\RUNSCORG.H"\
	".\SPLIT.H"\
	".\SPLITTER.H"\
	".\SPLTREE.H"\
	".\STRINFO.H"\
	".\TOOLBARX.H"\
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
	{$(INCLUDE)}"\iobjman.h"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XtsnPropAtl.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\dbfrmvw.obj" : $(SOURCE) $(DEP_CPP_DBFRM) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\dbfrmvw.sbr" : $(SOURCE) $(DEP_CPP_DBFRM) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 PseudoRelease"

DEP_CPP_DBFRM=\
	".\BSCREXT.HXX"\
	".\BSCRIPT.H"\
	".\BSCRIPT.HXX"\
	".\BSCRIPTP.HXX"\
	".\cmbnot.h"\
	".\CONSTSTR.H"\
	".\dbfrmvw.h"\
	".\DEBCTRL.H"\
	".\DUMMYPAR.H"\
	".\EDITCTRL.H"\
	".\FNDRPLD.H"\
	".\ISCRPROP.H"\
	".\MACRGUID.H"\
	".\PROJSCR.H"\
	".\RELSCRPT.H"\
	".\RUNEBOBS.H"\
	".\RUNERR.H"\
	".\RUNSCORG.H"\
	".\SPLIT.H"\
	".\SPLITTER.H"\
	".\SPLTREE.H"\
	".\STRINFO.H"\
	".\TOOLBARX.H"\
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
	{$(INCLUDE)}"\iobjman.h"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XtsnPropAtl.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\dbfrmvw.obj" : $(SOURCE) $(DEP_CPP_DBFRM) "$(INTDIR)"\
 ".\win32\Release\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DbFrmVw2.cpp

!IF  "$(CFG)" == "Bscriptn - Win32 Release"

DEP_CPP_DBFRMV=\
	".\BSCRIPT.H"\
	".\BSCRIPTP.HXX"\
	".\cmbnot.h"\
	".\CONSTSTR.H"\
	".\DbFrmVw2.h"\
	".\DEBCTRL.H"\
	".\DUMMYPAR.H"\
	".\EDITCTRL.H"\
	".\FNDRPLD.H"\
	".\ISCRPROP.H"\
	".\MACRGUID.H"\
	".\PROJSCR.H"\
	".\RELSCRPT.H"\
	".\RUNEBOBS.H"\
	".\RUNERR.H"\
	".\RUNSCORG.H"\
	".\SPLIT.H"\
	".\SPLITTER.H"\
	".\SPLTREE.H"\
	".\STRINFO.H"\
	".\TOOLBARX.H"\
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
	{$(INCLUDE)}"\iobjman.h"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\DbFrmVw2.obj" : $(SOURCE) $(DEP_CPP_DBFRMV) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"

DEP_CPP_DBFRMV=\
	".\BSCREXT.HXX"\
	".\BSCRIPT.H"\
	".\BSCRIPT.HXX"\
	".\BSCRIPTP.HXX"\
	".\cmbnot.h"\
	".\CONSTSTR.H"\
	".\DbFrmVw2.h"\
	".\DEBCTRL.H"\
	".\DUMMYPAR.H"\
	".\EDITCTRL.H"\
	".\FNDRPLD.H"\
	".\ISCRPROP.H"\
	".\MACRGUID.H"\
	".\PROJSCR.H"\
	".\RELSCRPT.H"\
	".\RUNEBOBS.H"\
	".\RUNERR.H"\
	".\RUNSCORG.H"\
	".\SPLIT.H"\
	".\SPLITTER.H"\
	".\SPLTREE.H"\
	".\STRINFO.H"\
	".\TOOLBARX.H"\
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
	{$(INCLUDE)}"\iobjman.h"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XtsnPropAtl.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\DbFrmVw2.obj" : $(SOURCE) $(DEP_CPP_DBFRMV) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\DbFrmVw2.sbr" : $(SOURCE) $(DEP_CPP_DBFRMV) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 PseudoRelease"

DEP_CPP_DBFRMV=\
	".\BSCREXT.HXX"\
	".\BSCRIPT.H"\
	".\BSCRIPT.HXX"\
	".\BSCRIPTP.HXX"\
	".\cmbnot.h"\
	".\CONSTSTR.H"\
	".\DbFrmVw2.h"\
	".\DEBCTRL.H"\
	".\DUMMYPAR.H"\
	".\EDITCTRL.H"\
	".\FNDRPLD.H"\
	".\ISCRPROP.H"\
	".\MACRGUID.H"\
	".\PROJSCR.H"\
	".\RELSCRPT.H"\
	".\RUNEBOBS.H"\
	".\RUNERR.H"\
	".\RUNSCORG.H"\
	".\SPLIT.H"\
	".\SPLITTER.H"\
	".\SPLTREE.H"\
	".\STRINFO.H"\
	".\TOOLBARX.H"\
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
	{$(INCLUDE)}"\iobjman.h"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XtsnPropAtl.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\DbFrmVw2.obj" : $(SOURCE) $(DEP_CPP_DBFRMV) "$(INTDIR)"\
 ".\win32\Release\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\cmbnot.cpp
DEP_CPP_CMBNO=\
	".\BSCREXT.HXX"\
	".\BSCRIPT.H"\
	".\BSCRIPT.HXX"\
	".\BSCRIPTP.HXX"\
	".\cmbnot.h"\
	".\tmplman.h"\
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
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XtsnPropAtl.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Bscriptn - Win32 Release"


"$(INTDIR)\cmbnot.obj" : $(SOURCE) $(DEP_CPP_CMBNO) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"


"$(INTDIR)\cmbnot.obj" : $(SOURCE) $(DEP_CPP_CMBNO) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\cmbnot.sbr" : $(SOURCE) $(DEP_CPP_CMBNO) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 PseudoRelease"


"$(INTDIR)\cmbnot.obj" : $(SOURCE) $(DEP_CPP_CMBNO) "$(INTDIR)"\
 ".\win32\Release\Bscript.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\expall.cpp
DEP_CPP_EXPAL=\
	".\BSCREXT.HXX"\
	".\BSCRIPT.H"\
	".\BSCRIPT.HXX"\
	".\BSCRIPTP.HXX"\
	".\CONSTSTR.H"\
	".\expall.h"\
	".\ISCRPROP.H"\
	".\MACRGUID.H"\
	".\MACRO.H"\
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
	{$(INCLUDE)}"\iobjman.h"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\IOSTREAM"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\LIST"\
	{$(INCLUDE)}"\MAP"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\file\path.h"\
	{$(INCLUDE)}"\ospace\file\path.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
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
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XtsnPropAtl.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

!IF  "$(CFG)" == "Bscriptn - Win32 Release"


"$(INTDIR)\expall.obj" : $(SOURCE) $(DEP_CPP_EXPAL) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 Debug"


"$(INTDIR)\expall.obj" : $(SOURCE) $(DEP_CPP_EXPAL) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"

"$(INTDIR)\expall.sbr" : $(SOURCE) $(DEP_CPP_EXPAL) "$(INTDIR)"\
 "$(INTDIR)\Bscript.pch"


!ELSEIF  "$(CFG)" == "Bscriptn - Win32 PseudoRelease"


"$(INTDIR)\expall.obj" : $(SOURCE) $(DEP_CPP_EXPAL) "$(INTDIR)"\
 ".\win32\Release\Bscript.pch"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
