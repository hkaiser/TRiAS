# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=Edbsimp - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Edbsimp - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Edbsimp - Win32 Release" && "$(CFG)" !=\
 "Edbsimp - Win32 Debug" && "$(CFG)" != "Edbsimp - Win32 SmartDebug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Edbsimp.mak" CFG="Edbsimp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Edbsimp - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Edbsimp - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Edbsimp - Win32 SmartDebug" (based on\
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
# PROP Target_Last_Scanned "Edbsimp - Win32 Debug"
MTL=mktyplib.exe
RSC=rc.exe
CPP=cl.exe

!IF  "$(CFG)" == "Edbsimp - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Win32\WinRel"
# PROP Intermediate_Dir "Win32\WinRel"
OUTDIR=.\Win32\WinRel
INTDIR=.\Win32\WinRel

ALL : ".\WinRel\Edbsimp.ext" "$(OUTDIR)\Edbsimp.pch"

CLEAN : 
	-@erase "$(INTDIR)\ABOUTDLG.OBJ"
	-@erase "$(INTDIR)\ACTDIA.OBJ"
	-@erase "$(INTDIR)\ARTDIA.OBJ"
	-@erase "$(INTDIR)\ATKISSAT.OBJ"
	-@erase "$(INTDIR)\ATTRDIA.OBJ"
	-@erase "$(INTDIR)\Cwc.obj"
	-@erase "$(INTDIR)\CXSTRING.OBJ"
	-@erase "$(INTDIR)\DEFMM.OBJ"
	-@erase "$(INTDIR)\EDBS.OBJ"
	-@erase "$(INTDIR)\Edbs.res"
	-@erase "$(INTDIR)\EDBSFO.OBJ"
	-@erase "$(INTDIR)\Edbsimp.pch"
	-@erase "$(INTDIR)\EDBSSATZ.OBJ"
	-@erase "$(INTDIR)\EDITMERK.OBJ"
	-@erase "$(INTDIR)\GEOOBJ.OBJ"
	-@erase "$(INTDIR)\HDRENTRX.OBJ"
	-@erase "$(INTDIR)\IMPORT.OBJ"
	-@erase "$(INTDIR)\KOORPAAR.OBJ"
	-@erase "$(INTDIR)\Licenz.obj"
	-@erase "$(INTDIR)\LINIE.OBJ"
	-@erase "$(INTDIR)\OBJPOOL.OBJ"
	-@erase "$(INTDIR)\REGELN.OBJ"
	-@erase "$(INTDIR)\SETUPDLG.OBJ"
	-@erase "$(INTDIR)\STDAFX.OBJ"
	-@erase "$(INTDIR)\STRUTIL.OBJ"
	-@erase "$(INTDIR)\TRIDDIA.OBJ"
	-@erase "$(INTDIR)\TRIF.OBJ"
	-@erase "$(INTDIR)\TRMMDIA.OBJ"
	-@erase "$(OUTDIR)\Edbsimp.exp"
	-@erase "$(OUTDIR)\Edbsimp.lib"
	-@erase ".\WinRel\Edbsimp.ext"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "__MFC__" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "__XT" /D "__DEXPROCS" /YX"stdafx.h" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__MFC__" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "__XT" /D "__DEXPROCS"\
 /Fp"$(INTDIR)/Edbsimp.pch" /YX"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Win32\WinRel/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/Edbs.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Edbsimp.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ixtmfr40.lib cont32r.lib tfrmwork.lib stdcppr.lib /nologo /subsystem:windows /dll /machine:I386 /out:"WinRel/Edbsimp.ext"
LINK32_FLAGS=ixtmfr40.lib cont32r.lib tfrmwork.lib stdcppr.lib /nologo\
 /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)/Edbsimp.pdb"\
 /machine:I386 /def:".\Edbsimp.def" /out:"WinRel/Edbsimp.ext"\
 /implib:"$(OUTDIR)/Edbsimp.lib" 
DEF_FILE= \
	".\Edbsimp.def"
LINK32_OBJS= \
	"$(INTDIR)\ABOUTDLG.OBJ" \
	"$(INTDIR)\ACTDIA.OBJ" \
	"$(INTDIR)\ARTDIA.OBJ" \
	"$(INTDIR)\ATKISSAT.OBJ" \
	"$(INTDIR)\ATTRDIA.OBJ" \
	"$(INTDIR)\Cwc.obj" \
	"$(INTDIR)\CXSTRING.OBJ" \
	"$(INTDIR)\DEFMM.OBJ" \
	"$(INTDIR)\EDBS.OBJ" \
	"$(INTDIR)\Edbs.res" \
	"$(INTDIR)\EDBSFO.OBJ" \
	"$(INTDIR)\EDBSSATZ.OBJ" \
	"$(INTDIR)\EDITMERK.OBJ" \
	"$(INTDIR)\GEOOBJ.OBJ" \
	"$(INTDIR)\HDRENTRX.OBJ" \
	"$(INTDIR)\IMPORT.OBJ" \
	"$(INTDIR)\KOORPAAR.OBJ" \
	"$(INTDIR)\Licenz.obj" \
	"$(INTDIR)\LINIE.OBJ" \
	"$(INTDIR)\OBJPOOL.OBJ" \
	"$(INTDIR)\REGELN.OBJ" \
	"$(INTDIR)\SETUPDLG.OBJ" \
	"$(INTDIR)\STDAFX.OBJ" \
	"$(INTDIR)\STRUTIL.OBJ" \
	"$(INTDIR)\TRIDDIA.OBJ" \
	"$(INTDIR)\TRIF.OBJ" \
	"$(INTDIR)\TRMMDIA.OBJ"

".\WinRel\Edbsimp.ext" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Edbsimp - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Win32\WinDebug"
# PROP Intermediate_Dir "Win32\WinDebug"
OUTDIR=.\Win32\WinDebug
INTDIR=.\Win32\WinDebug

ALL : "..\..\..\..\TRiAS\TRiAS32d\Edbsimpd.ext" "$(OUTDIR)\Edbsimp.pch"\
 "$(OUTDIR)\Edbsimp.bsc"

CLEAN : 
	-@erase "$(INTDIR)\ABOUTDLG.OBJ"
	-@erase "$(INTDIR)\ABOUTDLG.SBR"
	-@erase "$(INTDIR)\ACTDIA.OBJ"
	-@erase "$(INTDIR)\ACTDIA.SBR"
	-@erase "$(INTDIR)\ARTDIA.OBJ"
	-@erase "$(INTDIR)\ARTDIA.SBR"
	-@erase "$(INTDIR)\ATKISSAT.OBJ"
	-@erase "$(INTDIR)\ATKISSAT.SBR"
	-@erase "$(INTDIR)\ATTRDIA.OBJ"
	-@erase "$(INTDIR)\ATTRDIA.SBR"
	-@erase "$(INTDIR)\Cwc.obj"
	-@erase "$(INTDIR)\Cwc.sbr"
	-@erase "$(INTDIR)\CXSTRING.OBJ"
	-@erase "$(INTDIR)\CXSTRING.SBR"
	-@erase "$(INTDIR)\DEFMM.OBJ"
	-@erase "$(INTDIR)\DEFMM.SBR"
	-@erase "$(INTDIR)\EDBS.OBJ"
	-@erase "$(INTDIR)\Edbs.res"
	-@erase "$(INTDIR)\EDBS.SBR"
	-@erase "$(INTDIR)\EDBSFO.OBJ"
	-@erase "$(INTDIR)\EDBSFO.SBR"
	-@erase "$(INTDIR)\Edbsimp.pch"
	-@erase "$(INTDIR)\EDBSSATZ.OBJ"
	-@erase "$(INTDIR)\EDBSSATZ.SBR"
	-@erase "$(INTDIR)\EDITMERK.OBJ"
	-@erase "$(INTDIR)\EDITMERK.SBR"
	-@erase "$(INTDIR)\GEOOBJ.OBJ"
	-@erase "$(INTDIR)\GEOOBJ.SBR"
	-@erase "$(INTDIR)\HDRENTRX.OBJ"
	-@erase "$(INTDIR)\HDRENTRX.SBR"
	-@erase "$(INTDIR)\IMPORT.OBJ"
	-@erase "$(INTDIR)\IMPORT.SBR"
	-@erase "$(INTDIR)\KOORPAAR.OBJ"
	-@erase "$(INTDIR)\KOORPAAR.SBR"
	-@erase "$(INTDIR)\Licenz.obj"
	-@erase "$(INTDIR)\Licenz.sbr"
	-@erase "$(INTDIR)\LINIE.OBJ"
	-@erase "$(INTDIR)\LINIE.SBR"
	-@erase "$(INTDIR)\OBJPOOL.OBJ"
	-@erase "$(INTDIR)\OBJPOOL.SBR"
	-@erase "$(INTDIR)\REGELN.OBJ"
	-@erase "$(INTDIR)\REGELN.SBR"
	-@erase "$(INTDIR)\SETUPDLG.OBJ"
	-@erase "$(INTDIR)\SETUPDLG.SBR"
	-@erase "$(INTDIR)\STDAFX.OBJ"
	-@erase "$(INTDIR)\STDAFX.SBR"
	-@erase "$(INTDIR)\STRUTIL.OBJ"
	-@erase "$(INTDIR)\STRUTIL.SBR"
	-@erase "$(INTDIR)\TRIDDIA.OBJ"
	-@erase "$(INTDIR)\TRIDDIA.SBR"
	-@erase "$(INTDIR)\TRIF.OBJ"
	-@erase "$(INTDIR)\TRIF.SBR"
	-@erase "$(INTDIR)\TRMMDIA.OBJ"
	-@erase "$(INTDIR)\TRMMDIA.SBR"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\Edbsimp.bsc"
	-@erase "$(OUTDIR)\Edbsimpd.exp"
	-@erase "$(OUTDIR)\Edbsimpd.lib"
	-@erase "$(OUTDIR)\Edbsimpd.pdb"
	-@erase "..\..\..\..\TRiAS\TRiAS32d\Edbsimpd.ext"
	-@erase "..\..\..\..\TRiAS\TRiAS32d\Edbsimpd.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "__MFC__" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "__XT" /D "__DEXPROCS" /Fr /YX"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__MFC__" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "__XT" /D\
 "__DEXPROCS" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Edbsimp.pch" /YX"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Win32\WinDebug/
CPP_SBRS=.\Win32\WinDebug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/Edbs.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Edbsimp.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\ABOUTDLG.SBR" \
	"$(INTDIR)\ACTDIA.SBR" \
	"$(INTDIR)\ARTDIA.SBR" \
	"$(INTDIR)\ATKISSAT.SBR" \
	"$(INTDIR)\ATTRDIA.SBR" \
	"$(INTDIR)\Cwc.sbr" \
	"$(INTDIR)\CXSTRING.SBR" \
	"$(INTDIR)\DEFMM.SBR" \
	"$(INTDIR)\EDBS.SBR" \
	"$(INTDIR)\EDBSFO.SBR" \
	"$(INTDIR)\EDBSSATZ.SBR" \
	"$(INTDIR)\EDITMERK.SBR" \
	"$(INTDIR)\GEOOBJ.SBR" \
	"$(INTDIR)\HDRENTRX.SBR" \
	"$(INTDIR)\IMPORT.SBR" \
	"$(INTDIR)\KOORPAAR.SBR" \
	"$(INTDIR)\Licenz.sbr" \
	"$(INTDIR)\LINIE.SBR" \
	"$(INTDIR)\OBJPOOL.SBR" \
	"$(INTDIR)\REGELN.SBR" \
	"$(INTDIR)\SETUPDLG.SBR" \
	"$(INTDIR)\STDAFX.SBR" \
	"$(INTDIR)\STRUTIL.SBR" \
	"$(INTDIR)\TRIDDIA.SBR" \
	"$(INTDIR)\TRIF.SBR" \
	"$(INTDIR)\TRMMDIA.SBR"

"$(OUTDIR)\Edbsimp.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 ixtmfd40.lib cont32d.lib stdcppd.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"D:\TRiAS\TRiAS32d\Edbsimpd.ext"
# SUBTRACT LINK32 /map /nodefaultlib
LINK32_FLAGS=ixtmfd40.lib cont32d.lib stdcppd.lib /nologo /subsystem:windows\
 /dll /incremental:yes /pdb:"$(OUTDIR)/Edbsimpd.pdb" /debug /machine:I386\
 /def:".\Edbsimp.def" /out:"D:\TRiAS\TRiAS32d\Edbsimpd.ext"\
 /implib:"$(OUTDIR)/Edbsimpd.lib" 
DEF_FILE= \
	".\Edbsimp.def"
LINK32_OBJS= \
	"$(INTDIR)\ABOUTDLG.OBJ" \
	"$(INTDIR)\ACTDIA.OBJ" \
	"$(INTDIR)\ARTDIA.OBJ" \
	"$(INTDIR)\ATKISSAT.OBJ" \
	"$(INTDIR)\ATTRDIA.OBJ" \
	"$(INTDIR)\Cwc.obj" \
	"$(INTDIR)\CXSTRING.OBJ" \
	"$(INTDIR)\DEFMM.OBJ" \
	"$(INTDIR)\EDBS.OBJ" \
	"$(INTDIR)\Edbs.res" \
	"$(INTDIR)\EDBSFO.OBJ" \
	"$(INTDIR)\EDBSSATZ.OBJ" \
	"$(INTDIR)\EDITMERK.OBJ" \
	"$(INTDIR)\GEOOBJ.OBJ" \
	"$(INTDIR)\HDRENTRX.OBJ" \
	"$(INTDIR)\IMPORT.OBJ" \
	"$(INTDIR)\KOORPAAR.OBJ" \
	"$(INTDIR)\Licenz.obj" \
	"$(INTDIR)\LINIE.OBJ" \
	"$(INTDIR)\OBJPOOL.OBJ" \
	"$(INTDIR)\REGELN.OBJ" \
	"$(INTDIR)\SETUPDLG.OBJ" \
	"$(INTDIR)\STDAFX.OBJ" \
	"$(INTDIR)\STRUTIL.OBJ" \
	"$(INTDIR)\TRIDDIA.OBJ" \
	"$(INTDIR)\TRIF.OBJ" \
	"$(INTDIR)\TRMMDIA.OBJ"

"..\..\..\..\TRiAS\TRiAS32d\Edbsimpd.ext" : "$(OUTDIR)" $(DEF_FILE)\
 $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Edbsimp - Win32 SmartDebug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Edbsimp_"
# PROP BASE Intermediate_Dir "Edbsimp_"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Win32\SmartDebug"
# PROP Intermediate_Dir "Win32\SmartDebug"
# PROP Target_Dir ""
OUTDIR=.\Win32\SmartDebug
INTDIR=.\Win32\SmartDebug

ALL : "..\..\..\..\Programme\TRiAS\TRiAS\Edbsimp.ext" "$(OUTDIR)\Edbsimp.pch"\
 "$(OUTDIR)\Edbsimp.bsc"

CLEAN : 
	-@erase "$(INTDIR)\ABOUTDLG.OBJ"
	-@erase "$(INTDIR)\ABOUTDLG.SBR"
	-@erase "$(INTDIR)\ACTDIA.OBJ"
	-@erase "$(INTDIR)\ACTDIA.SBR"
	-@erase "$(INTDIR)\ARTDIA.OBJ"
	-@erase "$(INTDIR)\ARTDIA.SBR"
	-@erase "$(INTDIR)\ATKISSAT.OBJ"
	-@erase "$(INTDIR)\ATKISSAT.SBR"
	-@erase "$(INTDIR)\ATTRDIA.OBJ"
	-@erase "$(INTDIR)\ATTRDIA.SBR"
	-@erase "$(INTDIR)\Cwc.obj"
	-@erase "$(INTDIR)\Cwc.sbr"
	-@erase "$(INTDIR)\CXSTRING.OBJ"
	-@erase "$(INTDIR)\CXSTRING.SBR"
	-@erase "$(INTDIR)\DEFMM.OBJ"
	-@erase "$(INTDIR)\DEFMM.SBR"
	-@erase "$(INTDIR)\EDBS.OBJ"
	-@erase "$(INTDIR)\Edbs.res"
	-@erase "$(INTDIR)\EDBS.SBR"
	-@erase "$(INTDIR)\EDBSFO.OBJ"
	-@erase "$(INTDIR)\EDBSFO.SBR"
	-@erase "$(INTDIR)\Edbsimp.pch"
	-@erase "$(INTDIR)\EDBSSATZ.OBJ"
	-@erase "$(INTDIR)\EDBSSATZ.SBR"
	-@erase "$(INTDIR)\EDITMERK.OBJ"
	-@erase "$(INTDIR)\EDITMERK.SBR"
	-@erase "$(INTDIR)\GEOOBJ.OBJ"
	-@erase "$(INTDIR)\GEOOBJ.SBR"
	-@erase "$(INTDIR)\HDRENTRX.OBJ"
	-@erase "$(INTDIR)\HDRENTRX.SBR"
	-@erase "$(INTDIR)\IMPORT.OBJ"
	-@erase "$(INTDIR)\IMPORT.SBR"
	-@erase "$(INTDIR)\KOORPAAR.OBJ"
	-@erase "$(INTDIR)\KOORPAAR.SBR"
	-@erase "$(INTDIR)\Licenz.obj"
	-@erase "$(INTDIR)\Licenz.sbr"
	-@erase "$(INTDIR)\LINIE.OBJ"
	-@erase "$(INTDIR)\LINIE.SBR"
	-@erase "$(INTDIR)\OBJPOOL.OBJ"
	-@erase "$(INTDIR)\OBJPOOL.SBR"
	-@erase "$(INTDIR)\REGELN.OBJ"
	-@erase "$(INTDIR)\REGELN.SBR"
	-@erase "$(INTDIR)\SETUPDLG.OBJ"
	-@erase "$(INTDIR)\SETUPDLG.SBR"
	-@erase "$(INTDIR)\STDAFX.OBJ"
	-@erase "$(INTDIR)\STDAFX.SBR"
	-@erase "$(INTDIR)\STRUTIL.OBJ"
	-@erase "$(INTDIR)\STRUTIL.SBR"
	-@erase "$(INTDIR)\TRIDDIA.OBJ"
	-@erase "$(INTDIR)\TRIDDIA.SBR"
	-@erase "$(INTDIR)\TRIF.OBJ"
	-@erase "$(INTDIR)\TRIF.SBR"
	-@erase "$(INTDIR)\TRMMDIA.OBJ"
	-@erase "$(INTDIR)\TRMMDIA.SBR"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\Edbsimp.bsc"
	-@erase "$(OUTDIR)\Edbsimp.exp"
	-@erase "$(OUTDIR)\Edbsimp.lib"
	-@erase "$(OUTDIR)\Edbsimp.pdb"
	-@erase "..\..\..\..\Programme\TRiAS\TRiAS\Edbsimp.ext"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "__MFC__" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "__XT" /D "__DEXPROCS" /YX"stdafx.h" /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MD /W3 /GX /Zi /Od /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "__MFC__" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "__XT" /D "__DEXPROCS" /Fr /YX"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /Zi /Od /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__MFC__" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "__XT" /D "__DEXPROCS"\
 /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Edbsimp.pch" /YX"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Win32\SmartDebug/
CPP_SBRS=.\Win32\SmartDebug/
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/Edbs.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Edbsimp.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\ABOUTDLG.SBR" \
	"$(INTDIR)\ACTDIA.SBR" \
	"$(INTDIR)\ARTDIA.SBR" \
	"$(INTDIR)\ATKISSAT.SBR" \
	"$(INTDIR)\ATTRDIA.SBR" \
	"$(INTDIR)\Cwc.sbr" \
	"$(INTDIR)\CXSTRING.SBR" \
	"$(INTDIR)\DEFMM.SBR" \
	"$(INTDIR)\EDBS.SBR" \
	"$(INTDIR)\EDBSFO.SBR" \
	"$(INTDIR)\EDBSSATZ.SBR" \
	"$(INTDIR)\EDITMERK.SBR" \
	"$(INTDIR)\GEOOBJ.SBR" \
	"$(INTDIR)\HDRENTRX.SBR" \
	"$(INTDIR)\IMPORT.SBR" \
	"$(INTDIR)\KOORPAAR.SBR" \
	"$(INTDIR)\Licenz.sbr" \
	"$(INTDIR)\LINIE.SBR" \
	"$(INTDIR)\OBJPOOL.SBR" \
	"$(INTDIR)\REGELN.SBR" \
	"$(INTDIR)\SETUPDLG.SBR" \
	"$(INTDIR)\STDAFX.SBR" \
	"$(INTDIR)\STRUTIL.SBR" \
	"$(INTDIR)\TRIDDIA.SBR" \
	"$(INTDIR)\TRIF.SBR" \
	"$(INTDIR)\TRMMDIA.SBR"

"$(OUTDIR)\Edbsimp.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 ixtmfr40.lib cont32r.lib tfrmwork.lib stdcppr.lib /nologo /subsystem:windows /dll /machine:I386 /out:"WinRel/Edbsimp.ext"
# ADD LINK32 ixtmfr40.lib cont32r.lib tfrmwork.lib stdcppr.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"d:\Programme\TRiAS\TRiAS\Edbsimp.ext"
LINK32_FLAGS=ixtmfr40.lib cont32r.lib tfrmwork.lib stdcppr.lib /nologo\
 /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)/Edbsimp.pdb" /debug\
 /machine:I386 /def:".\Edbsimp.def" /out:"d:\Programme\TRiAS\TRiAS\Edbsimp.ext"\
 /implib:"$(OUTDIR)/Edbsimp.lib" 
DEF_FILE= \
	".\Edbsimp.def"
LINK32_OBJS= \
	"$(INTDIR)\ABOUTDLG.OBJ" \
	"$(INTDIR)\ACTDIA.OBJ" \
	"$(INTDIR)\ARTDIA.OBJ" \
	"$(INTDIR)\ATKISSAT.OBJ" \
	"$(INTDIR)\ATTRDIA.OBJ" \
	"$(INTDIR)\Cwc.obj" \
	"$(INTDIR)\CXSTRING.OBJ" \
	"$(INTDIR)\DEFMM.OBJ" \
	"$(INTDIR)\EDBS.OBJ" \
	"$(INTDIR)\Edbs.res" \
	"$(INTDIR)\EDBSFO.OBJ" \
	"$(INTDIR)\EDBSSATZ.OBJ" \
	"$(INTDIR)\EDITMERK.OBJ" \
	"$(INTDIR)\GEOOBJ.OBJ" \
	"$(INTDIR)\HDRENTRX.OBJ" \
	"$(INTDIR)\IMPORT.OBJ" \
	"$(INTDIR)\KOORPAAR.OBJ" \
	"$(INTDIR)\Licenz.obj" \
	"$(INTDIR)\LINIE.OBJ" \
	"$(INTDIR)\OBJPOOL.OBJ" \
	"$(INTDIR)\REGELN.OBJ" \
	"$(INTDIR)\SETUPDLG.OBJ" \
	"$(INTDIR)\STDAFX.OBJ" \
	"$(INTDIR)\STRUTIL.OBJ" \
	"$(INTDIR)\TRIDDIA.OBJ" \
	"$(INTDIR)\TRIF.OBJ" \
	"$(INTDIR)\TRMMDIA.OBJ"

"..\..\..\..\Programme\TRiAS\TRiAS\Edbsimp.ext" : "$(OUTDIR)" $(DEF_FILE)\
 $(LINK32_OBJS)
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

# Name "Edbsimp - Win32 Release"
# Name "Edbsimp - Win32 Debug"
# Name "Edbsimp - Win32 SmartDebug"

!IF  "$(CFG)" == "Edbsimp - Win32 Release"

!ELSEIF  "$(CFG)" == "Edbsimp - Win32 Debug"

!ELSEIF  "$(CFG)" == "Edbsimp - Win32 SmartDebug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\GEOOBJ.CPP

!IF  "$(CFG)" == "Edbsimp - Win32 Release"

DEP_CPP_GEOOB=\
	".\CXSTRING.H"\
	".\GEOOBJ.HPP"\
	".\REGELN.HPP"\
	".\Stdafx.h"\
	".\TRIF.HPP"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\OLE16.H"\
	

"$(INTDIR)\GEOOBJ.OBJ" : $(SOURCE) $(DEP_CPP_GEOOB) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Edbsimp - Win32 Debug"

DEP_CPP_GEOOB=\
	".\CXSTRING.H"\
	".\GEOOBJ.HPP"\
	".\Import.hpp"\
	".\REGELN.HPP"\
	".\Stdafx.h"\
	".\TRIF.HPP"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\ERRCODES.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\IENUMOBJ.HXX"\
	{$(INCLUDE)}"\ISTATUS.H"\
	{$(INCLUDE)}"\IXTENSN.HXX"\
	{$(INCLUDE)}"\OLE16.H"\
	{$(INCLUDE)}"\Ospace\config.h"\
	{$(INCLUDE)}"\Ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\Ospace\std\iosfwd"\
	{$(INCLUDE)}"\Ospace\std\istream"\
	{$(INCLUDE)}"\Ospace\std\ostream"\
	{$(INCLUDE)}"\Ospace\std\string"\
	{$(INCLUDE)}"\Ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\Ospace\stl\allocate.h"\
	{$(INCLUDE)}"\Ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\Ospace\stl\common.h"\
	{$(INCLUDE)}"\Ospace\stl\config.h"\
	{$(INCLUDE)}"\Ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\Ospace\stl\iterator.h"\
	{$(INCLUDE)}"\Ospace\stl\ops.h"\
	{$(INCLUDE)}"\Ospace\stl\pair.h"\
	{$(INCLUDE)}"\Ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\Ospace\string\basic.cc"\
	{$(INCLUDE)}"\Ospace\string\basic.h"\
	{$(INCLUDE)}"\Ospace\string\basic.ipp"\
	{$(INCLUDE)}"\Ospace\string\config.h"\
	{$(INCLUDE)}"\Ospace\string\search.cc"\
	{$(INCLUDE)}"\Ospace\string\search.h"\
	{$(INCLUDE)}"\Ospace\string\string.h"\
	{$(INCLUDE)}"\Ospace\string\traits.cc"\
	{$(INCLUDE)}"\Ospace\string\traits.h"\
	{$(INCLUDE)}"\Ospace\type\prim.h"\
	{$(INCLUDE)}"\Ospace\utility\memory.h"\
	{$(INCLUDE)}"\TRIASM.HXX"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\XTENSION.H"\
	{$(INCLUDE)}"\XTENSNM.HXX"\
	{$(INCLUDE)}"\XTENSNX.H"\
	{$(INCLUDE)}"\XTSNAUX.HXX"\
	{$(INCLUDE)}"\XTSNIMP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	

"$(INTDIR)\GEOOBJ.OBJ" : $(SOURCE) $(DEP_CPP_GEOOB) "$(INTDIR)"

"$(INTDIR)\GEOOBJ.SBR" : $(SOURCE) $(DEP_CPP_GEOOB) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Edbsimp - Win32 SmartDebug"

DEP_CPP_GEOOB=\
	".\CXSTRING.H"\
	".\GEOOBJ.HPP"\
	".\REGELN.HPP"\
	".\Stdafx.h"\
	".\TRIF.HPP"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\OLE16.H"\
	

"$(INTDIR)\GEOOBJ.OBJ" : $(SOURCE) $(DEP_CPP_GEOOB) "$(INTDIR)"

"$(INTDIR)\GEOOBJ.SBR" : $(SOURCE) $(DEP_CPP_GEOOB) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TRMMDIA.CPP
DEP_CPP_TRMMD=\
	".\CXSTRING.H"\
	".\Import.hpp"\
	".\Stdafx.h"\
	".\TRMMDIA.HPP"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\ERRCODES.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\IENUMOBJ.HXX"\
	{$(INCLUDE)}"\ISTATUS.H"\
	{$(INCLUDE)}"\IXTENSN.HXX"\
	{$(INCLUDE)}"\OLE16.H"\
	{$(INCLUDE)}"\Ospace\config.h"\
	{$(INCLUDE)}"\Ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\Ospace\std\iosfwd"\
	{$(INCLUDE)}"\Ospace\std\istream"\
	{$(INCLUDE)}"\Ospace\std\ostream"\
	{$(INCLUDE)}"\Ospace\std\string"\
	{$(INCLUDE)}"\Ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\Ospace\stl\allocate.h"\
	{$(INCLUDE)}"\Ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\Ospace\stl\common.h"\
	{$(INCLUDE)}"\Ospace\stl\config.h"\
	{$(INCLUDE)}"\Ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\Ospace\stl\iterator.h"\
	{$(INCLUDE)}"\Ospace\stl\ops.h"\
	{$(INCLUDE)}"\Ospace\stl\pair.h"\
	{$(INCLUDE)}"\Ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\Ospace\string\basic.cc"\
	{$(INCLUDE)}"\Ospace\string\basic.h"\
	{$(INCLUDE)}"\Ospace\string\basic.ipp"\
	{$(INCLUDE)}"\Ospace\string\config.h"\
	{$(INCLUDE)}"\Ospace\string\search.cc"\
	{$(INCLUDE)}"\Ospace\string\search.h"\
	{$(INCLUDE)}"\Ospace\string\string.h"\
	{$(INCLUDE)}"\Ospace\string\traits.cc"\
	{$(INCLUDE)}"\Ospace\string\traits.h"\
	{$(INCLUDE)}"\Ospace\type\prim.h"\
	{$(INCLUDE)}"\Ospace\utility\memory.h"\
	{$(INCLUDE)}"\TRIASM.HXX"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\XTENSION.H"\
	{$(INCLUDE)}"\XTENSNM.HXX"\
	{$(INCLUDE)}"\XTENSNX.H"\
	{$(INCLUDE)}"\XTSNAUX.HXX"\
	{$(INCLUDE)}"\XTSNIMP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	

!IF  "$(CFG)" == "Edbsimp - Win32 Release"


"$(INTDIR)\TRMMDIA.OBJ" : $(SOURCE) $(DEP_CPP_TRMMD) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Edbsimp - Win32 Debug"


"$(INTDIR)\TRMMDIA.OBJ" : $(SOURCE) $(DEP_CPP_TRMMD) "$(INTDIR)"

"$(INTDIR)\TRMMDIA.SBR" : $(SOURCE) $(DEP_CPP_TRMMD) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Edbsimp - Win32 SmartDebug"


"$(INTDIR)\TRMMDIA.OBJ" : $(SOURCE) $(DEP_CPP_TRMMD) "$(INTDIR)"

"$(INTDIR)\TRMMDIA.SBR" : $(SOURCE) $(DEP_CPP_TRMMD) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\STDAFX.CPP
DEP_CPP_STDAF=\
	".\Import.hpp"\
	".\Stdafx.h"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\ERRCODES.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\IENUMOBJ.HXX"\
	{$(INCLUDE)}"\ISTATUS.H"\
	{$(INCLUDE)}"\IXTENSN.HXX"\
	{$(INCLUDE)}"\OLE16.H"\
	{$(INCLUDE)}"\Ospace\config.h"\
	{$(INCLUDE)}"\Ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\Ospace\std\iosfwd"\
	{$(INCLUDE)}"\Ospace\std\istream"\
	{$(INCLUDE)}"\Ospace\std\ostream"\
	{$(INCLUDE)}"\Ospace\std\string"\
	{$(INCLUDE)}"\Ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\Ospace\stl\allocate.h"\
	{$(INCLUDE)}"\Ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\Ospace\stl\common.h"\
	{$(INCLUDE)}"\Ospace\stl\config.h"\
	{$(INCLUDE)}"\Ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\Ospace\stl\iterator.h"\
	{$(INCLUDE)}"\Ospace\stl\ops.h"\
	{$(INCLUDE)}"\Ospace\stl\pair.h"\
	{$(INCLUDE)}"\Ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\Ospace\string\basic.cc"\
	{$(INCLUDE)}"\Ospace\string\basic.h"\
	{$(INCLUDE)}"\Ospace\string\basic.ipp"\
	{$(INCLUDE)}"\Ospace\string\config.h"\
	{$(INCLUDE)}"\Ospace\string\search.cc"\
	{$(INCLUDE)}"\Ospace\string\search.h"\
	{$(INCLUDE)}"\Ospace\string\string.h"\
	{$(INCLUDE)}"\Ospace\string\traits.cc"\
	{$(INCLUDE)}"\Ospace\string\traits.h"\
	{$(INCLUDE)}"\Ospace\type\prim.h"\
	{$(INCLUDE)}"\Ospace\utility\memory.h"\
	{$(INCLUDE)}"\TRIASM.HXX"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\XTENSION.H"\
	{$(INCLUDE)}"\XTENSNM.HXX"\
	{$(INCLUDE)}"\XTENSNX.H"\
	{$(INCLUDE)}"\XTSNAUX.HXX"\
	{$(INCLUDE)}"\XTSNIMP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	

!IF  "$(CFG)" == "Edbsimp - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__MFC__" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "__XT" /D "__DEXPROCS"\
 /Fp"$(INTDIR)/Edbsimp.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\STDAFX.OBJ" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Edbsimp.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Edbsimp - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__MFC__" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "__XT" /D\
 "__DEXPROCS" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Edbsimp.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\STDAFX.OBJ" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\STDAFX.SBR" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Edbsimp.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Edbsimp - Win32 SmartDebug"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /Zi /Od /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__MFC__" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "__XT" /D "__DEXPROCS"\
 /Fr"$(INTDIR)/" /Fp"$(INTDIR)/Edbsimp.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\STDAFX.OBJ" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\STDAFX.SBR" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Edbsimp.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TRIDDIA.CPP
DEP_CPP_TRIDD=\
	".\CXSTRING.H"\
	".\DEFMM.HPP"\
	".\Import.hpp"\
	".\Stdafx.h"\
	".\TRIDDIA.HPP"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\ERRCODES.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\IENUMOBJ.HXX"\
	{$(INCLUDE)}"\ISTATUS.H"\
	{$(INCLUDE)}"\IXTENSN.HXX"\
	{$(INCLUDE)}"\OLE16.H"\
	{$(INCLUDE)}"\Ospace\config.h"\
	{$(INCLUDE)}"\Ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\Ospace\std\iosfwd"\
	{$(INCLUDE)}"\Ospace\std\istream"\
	{$(INCLUDE)}"\Ospace\std\ostream"\
	{$(INCLUDE)}"\Ospace\std\string"\
	{$(INCLUDE)}"\Ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\Ospace\stl\allocate.h"\
	{$(INCLUDE)}"\Ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\Ospace\stl\common.h"\
	{$(INCLUDE)}"\Ospace\stl\config.h"\
	{$(INCLUDE)}"\Ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\Ospace\stl\iterator.h"\
	{$(INCLUDE)}"\Ospace\stl\ops.h"\
	{$(INCLUDE)}"\Ospace\stl\pair.h"\
	{$(INCLUDE)}"\Ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\Ospace\string\basic.cc"\
	{$(INCLUDE)}"\Ospace\string\basic.h"\
	{$(INCLUDE)}"\Ospace\string\basic.ipp"\
	{$(INCLUDE)}"\Ospace\string\config.h"\
	{$(INCLUDE)}"\Ospace\string\search.cc"\
	{$(INCLUDE)}"\Ospace\string\search.h"\
	{$(INCLUDE)}"\Ospace\string\string.h"\
	{$(INCLUDE)}"\Ospace\string\traits.cc"\
	{$(INCLUDE)}"\Ospace\string\traits.h"\
	{$(INCLUDE)}"\Ospace\type\prim.h"\
	{$(INCLUDE)}"\Ospace\utility\memory.h"\
	{$(INCLUDE)}"\TRIASM.HXX"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\XTENSION.H"\
	{$(INCLUDE)}"\XTENSNM.HXX"\
	{$(INCLUDE)}"\XTENSNX.H"\
	{$(INCLUDE)}"\XTSNAUX.HXX"\
	{$(INCLUDE)}"\XTSNIMP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	

!IF  "$(CFG)" == "Edbsimp - Win32 Release"


"$(INTDIR)\TRIDDIA.OBJ" : $(SOURCE) $(DEP_CPP_TRIDD) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Edbsimp - Win32 Debug"


"$(INTDIR)\TRIDDIA.OBJ" : $(SOURCE) $(DEP_CPP_TRIDD) "$(INTDIR)"

"$(INTDIR)\TRIDDIA.SBR" : $(SOURCE) $(DEP_CPP_TRIDD) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Edbsimp - Win32 SmartDebug"


"$(INTDIR)\TRIDDIA.OBJ" : $(SOURCE) $(DEP_CPP_TRIDD) "$(INTDIR)"

"$(INTDIR)\TRIDDIA.SBR" : $(SOURCE) $(DEP_CPP_TRIDD) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\EDITMERK.CPP
DEP_CPP_EDITM=\
	".\CXSTRING.H"\
	".\EDITMERK.H"\
	".\Import.hpp"\
	".\Stdafx.h"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\ERRCODES.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\IENUMOBJ.HXX"\
	{$(INCLUDE)}"\ISTATUS.H"\
	{$(INCLUDE)}"\IXTENSN.HXX"\
	{$(INCLUDE)}"\OLE16.H"\
	{$(INCLUDE)}"\Ospace\config.h"\
	{$(INCLUDE)}"\Ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\Ospace\std\iosfwd"\
	{$(INCLUDE)}"\Ospace\std\istream"\
	{$(INCLUDE)}"\Ospace\std\ostream"\
	{$(INCLUDE)}"\Ospace\std\string"\
	{$(INCLUDE)}"\Ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\Ospace\stl\allocate.h"\
	{$(INCLUDE)}"\Ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\Ospace\stl\common.h"\
	{$(INCLUDE)}"\Ospace\stl\config.h"\
	{$(INCLUDE)}"\Ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\Ospace\stl\iterator.h"\
	{$(INCLUDE)}"\Ospace\stl\ops.h"\
	{$(INCLUDE)}"\Ospace\stl\pair.h"\
	{$(INCLUDE)}"\Ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\Ospace\string\basic.cc"\
	{$(INCLUDE)}"\Ospace\string\basic.h"\
	{$(INCLUDE)}"\Ospace\string\basic.ipp"\
	{$(INCLUDE)}"\Ospace\string\config.h"\
	{$(INCLUDE)}"\Ospace\string\search.cc"\
	{$(INCLUDE)}"\Ospace\string\search.h"\
	{$(INCLUDE)}"\Ospace\string\string.h"\
	{$(INCLUDE)}"\Ospace\string\traits.cc"\
	{$(INCLUDE)}"\Ospace\string\traits.h"\
	{$(INCLUDE)}"\Ospace\type\prim.h"\
	{$(INCLUDE)}"\Ospace\utility\memory.h"\
	{$(INCLUDE)}"\TRIASM.HXX"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\XTENSION.H"\
	{$(INCLUDE)}"\XTENSNM.HXX"\
	{$(INCLUDE)}"\XTENSNX.H"\
	{$(INCLUDE)}"\XTSNAUX.HXX"\
	{$(INCLUDE)}"\XTSNIMP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	

!IF  "$(CFG)" == "Edbsimp - Win32 Release"


"$(INTDIR)\EDITMERK.OBJ" : $(SOURCE) $(DEP_CPP_EDITM) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Edbsimp - Win32 Debug"


"$(INTDIR)\EDITMERK.OBJ" : $(SOURCE) $(DEP_CPP_EDITM) "$(INTDIR)"

"$(INTDIR)\EDITMERK.SBR" : $(SOURCE) $(DEP_CPP_EDITM) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Edbsimp - Win32 SmartDebug"


"$(INTDIR)\EDITMERK.OBJ" : $(SOURCE) $(DEP_CPP_EDITM) "$(INTDIR)"

"$(INTDIR)\EDITMERK.SBR" : $(SOURCE) $(DEP_CPP_EDITM) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CXSTRING.CPP
DEP_CPP_CXSTR=\
	".\CXSTRING.H"\
	".\Import.hpp"\
	".\Stdafx.h"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\ERRCODES.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\IENUMOBJ.HXX"\
	{$(INCLUDE)}"\ISTATUS.H"\
	{$(INCLUDE)}"\IXTENSN.HXX"\
	{$(INCLUDE)}"\OLE16.H"\
	{$(INCLUDE)}"\Ospace\config.h"\
	{$(INCLUDE)}"\Ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\Ospace\std\iosfwd"\
	{$(INCLUDE)}"\Ospace\std\istream"\
	{$(INCLUDE)}"\Ospace\std\ostream"\
	{$(INCLUDE)}"\Ospace\std\string"\
	{$(INCLUDE)}"\Ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\Ospace\stl\allocate.h"\
	{$(INCLUDE)}"\Ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\Ospace\stl\common.h"\
	{$(INCLUDE)}"\Ospace\stl\config.h"\
	{$(INCLUDE)}"\Ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\Ospace\stl\iterator.h"\
	{$(INCLUDE)}"\Ospace\stl\ops.h"\
	{$(INCLUDE)}"\Ospace\stl\pair.h"\
	{$(INCLUDE)}"\Ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\Ospace\string\basic.cc"\
	{$(INCLUDE)}"\Ospace\string\basic.h"\
	{$(INCLUDE)}"\Ospace\string\basic.ipp"\
	{$(INCLUDE)}"\Ospace\string\config.h"\
	{$(INCLUDE)}"\Ospace\string\search.cc"\
	{$(INCLUDE)}"\Ospace\string\search.h"\
	{$(INCLUDE)}"\Ospace\string\string.h"\
	{$(INCLUDE)}"\Ospace\string\traits.cc"\
	{$(INCLUDE)}"\Ospace\string\traits.h"\
	{$(INCLUDE)}"\Ospace\type\prim.h"\
	{$(INCLUDE)}"\Ospace\utility\memory.h"\
	{$(INCLUDE)}"\TRIASM.HXX"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\XTENSION.H"\
	{$(INCLUDE)}"\XTENSNM.HXX"\
	{$(INCLUDE)}"\XTENSNX.H"\
	{$(INCLUDE)}"\XTSNAUX.HXX"\
	{$(INCLUDE)}"\XTSNIMP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	

!IF  "$(CFG)" == "Edbsimp - Win32 Release"


"$(INTDIR)\CXSTRING.OBJ" : $(SOURCE) $(DEP_CPP_CXSTR) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Edbsimp - Win32 Debug"


"$(INTDIR)\CXSTRING.OBJ" : $(SOURCE) $(DEP_CPP_CXSTR) "$(INTDIR)"

"$(INTDIR)\CXSTRING.SBR" : $(SOURCE) $(DEP_CPP_CXSTR) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Edbsimp - Win32 SmartDebug"


"$(INTDIR)\CXSTRING.OBJ" : $(SOURCE) $(DEP_CPP_CXSTR) "$(INTDIR)"

"$(INTDIR)\CXSTRING.SBR" : $(SOURCE) $(DEP_CPP_CXSTR) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ABOUTDLG.CPP
DEP_CPP_ABOUT=\
	".\ABOUTDLG.HPP"\
	".\Import.hpp"\
	".\Stdafx.h"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\ERRCODES.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\IENUMOBJ.HXX"\
	{$(INCLUDE)}"\ISTATUS.H"\
	{$(INCLUDE)}"\IXTENSN.HXX"\
	{$(INCLUDE)}"\OLE16.H"\
	{$(INCLUDE)}"\Ospace\config.h"\
	{$(INCLUDE)}"\Ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\Ospace\std\iosfwd"\
	{$(INCLUDE)}"\Ospace\std\istream"\
	{$(INCLUDE)}"\Ospace\std\ostream"\
	{$(INCLUDE)}"\Ospace\std\string"\
	{$(INCLUDE)}"\Ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\Ospace\stl\allocate.h"\
	{$(INCLUDE)}"\Ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\Ospace\stl\common.h"\
	{$(INCLUDE)}"\Ospace\stl\config.h"\
	{$(INCLUDE)}"\Ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\Ospace\stl\iterator.h"\
	{$(INCLUDE)}"\Ospace\stl\ops.h"\
	{$(INCLUDE)}"\Ospace\stl\pair.h"\
	{$(INCLUDE)}"\Ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\Ospace\string\basic.cc"\
	{$(INCLUDE)}"\Ospace\string\basic.h"\
	{$(INCLUDE)}"\Ospace\string\basic.ipp"\
	{$(INCLUDE)}"\Ospace\string\config.h"\
	{$(INCLUDE)}"\Ospace\string\search.cc"\
	{$(INCLUDE)}"\Ospace\string\search.h"\
	{$(INCLUDE)}"\Ospace\string\string.h"\
	{$(INCLUDE)}"\Ospace\string\traits.cc"\
	{$(INCLUDE)}"\Ospace\string\traits.h"\
	{$(INCLUDE)}"\Ospace\type\prim.h"\
	{$(INCLUDE)}"\Ospace\utility\memory.h"\
	{$(INCLUDE)}"\TRIASM.HXX"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\XTENSION.H"\
	{$(INCLUDE)}"\XTENSNM.HXX"\
	{$(INCLUDE)}"\XTENSNX.H"\
	{$(INCLUDE)}"\XTSNAUX.HXX"\
	{$(INCLUDE)}"\XTSNIMP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	

!IF  "$(CFG)" == "Edbsimp - Win32 Release"


"$(INTDIR)\ABOUTDLG.OBJ" : $(SOURCE) $(DEP_CPP_ABOUT) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Edbsimp - Win32 Debug"


"$(INTDIR)\ABOUTDLG.OBJ" : $(SOURCE) $(DEP_CPP_ABOUT) "$(INTDIR)"

"$(INTDIR)\ABOUTDLG.SBR" : $(SOURCE) $(DEP_CPP_ABOUT) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Edbsimp - Win32 SmartDebug"


"$(INTDIR)\ABOUTDLG.OBJ" : $(SOURCE) $(DEP_CPP_ABOUT) "$(INTDIR)"

"$(INTDIR)\ABOUTDLG.SBR" : $(SOURCE) $(DEP_CPP_ABOUT) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\KOORPAAR.CPP

!IF  "$(CFG)" == "Edbsimp - Win32 Release"

DEP_CPP_KOORP=\
	".\Import.hpp"\
	".\KOORPAAR.H"\
	".\Stdafx.h"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\ERRCODES.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\IENUMOBJ.HXX"\
	{$(INCLUDE)}"\ISTATUS.H"\
	{$(INCLUDE)}"\IXTENSN.HXX"\
	{$(INCLUDE)}"\OLE16.H"\
	{$(INCLUDE)}"\Ospace\config.h"\
	{$(INCLUDE)}"\Ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\Ospace\std\iosfwd"\
	{$(INCLUDE)}"\Ospace\std\istream"\
	{$(INCLUDE)}"\Ospace\std\ostream"\
	{$(INCLUDE)}"\Ospace\std\string"\
	{$(INCLUDE)}"\Ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\Ospace\stl\allocate.h"\
	{$(INCLUDE)}"\Ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\Ospace\stl\common.h"\
	{$(INCLUDE)}"\Ospace\stl\config.h"\
	{$(INCLUDE)}"\Ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\Ospace\stl\iterator.h"\
	{$(INCLUDE)}"\Ospace\stl\ops.h"\
	{$(INCLUDE)}"\Ospace\stl\pair.h"\
	{$(INCLUDE)}"\Ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\Ospace\string\basic.cc"\
	{$(INCLUDE)}"\Ospace\string\basic.h"\
	{$(INCLUDE)}"\Ospace\string\basic.ipp"\
	{$(INCLUDE)}"\Ospace\string\config.h"\
	{$(INCLUDE)}"\Ospace\string\search.cc"\
	{$(INCLUDE)}"\Ospace\string\search.h"\
	{$(INCLUDE)}"\Ospace\string\string.h"\
	{$(INCLUDE)}"\Ospace\string\traits.cc"\
	{$(INCLUDE)}"\Ospace\string\traits.h"\
	{$(INCLUDE)}"\Ospace\type\prim.h"\
	{$(INCLUDE)}"\Ospace\utility\memory.h"\
	{$(INCLUDE)}"\TRIASM.HXX"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\XTENSION.H"\
	{$(INCLUDE)}"\XTENSNM.HXX"\
	{$(INCLUDE)}"\XTENSNX.H"\
	{$(INCLUDE)}"\XTSNAUX.HXX"\
	{$(INCLUDE)}"\XTSNIMP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	

"$(INTDIR)\KOORPAAR.OBJ" : $(SOURCE) $(DEP_CPP_KOORP) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Edbsimp - Win32 Debug"

DEP_CPP_KOORP=\
	".\KOORPAAR.H"\
	".\Stdafx.h"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\OLE16.H"\
	{$(INCLUDE)}"\Ospace\config.h"\
	{$(INCLUDE)}"\Ospace\std\string"\
	{$(INCLUDE)}"\Tstring"\
	

"$(INTDIR)\KOORPAAR.OBJ" : $(SOURCE) $(DEP_CPP_KOORP) "$(INTDIR)"

"$(INTDIR)\KOORPAAR.SBR" : $(SOURCE) $(DEP_CPP_KOORP) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Edbsimp - Win32 SmartDebug"

DEP_CPP_KOORP=\
	".\Import.hpp"\
	".\KOORPAAR.H"\
	".\Stdafx.h"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\ERRCODES.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\IENUMOBJ.HXX"\
	{$(INCLUDE)}"\ISTATUS.H"\
	{$(INCLUDE)}"\IXTENSN.HXX"\
	{$(INCLUDE)}"\OLE16.H"\
	{$(INCLUDE)}"\Ospace\config.h"\
	{$(INCLUDE)}"\Ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\Ospace\std\iosfwd"\
	{$(INCLUDE)}"\Ospace\std\istream"\
	{$(INCLUDE)}"\Ospace\std\ostream"\
	{$(INCLUDE)}"\Ospace\std\string"\
	{$(INCLUDE)}"\Ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\Ospace\stl\allocate.h"\
	{$(INCLUDE)}"\Ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\Ospace\stl\common.h"\
	{$(INCLUDE)}"\Ospace\stl\config.h"\
	{$(INCLUDE)}"\Ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\Ospace\stl\iterator.h"\
	{$(INCLUDE)}"\Ospace\stl\ops.h"\
	{$(INCLUDE)}"\Ospace\stl\pair.h"\
	{$(INCLUDE)}"\Ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\Ospace\string\basic.cc"\
	{$(INCLUDE)}"\Ospace\string\basic.h"\
	{$(INCLUDE)}"\Ospace\string\basic.ipp"\
	{$(INCLUDE)}"\Ospace\string\config.h"\
	{$(INCLUDE)}"\Ospace\string\search.cc"\
	{$(INCLUDE)}"\Ospace\string\search.h"\
	{$(INCLUDE)}"\Ospace\string\string.h"\
	{$(INCLUDE)}"\Ospace\string\traits.cc"\
	{$(INCLUDE)}"\Ospace\string\traits.h"\
	{$(INCLUDE)}"\Ospace\type\prim.h"\
	{$(INCLUDE)}"\Ospace\utility\memory.h"\
	{$(INCLUDE)}"\TRIASM.HXX"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\XTENSION.H"\
	{$(INCLUDE)}"\XTENSNM.HXX"\
	{$(INCLUDE)}"\XTENSNX.H"\
	{$(INCLUDE)}"\XTSNAUX.HXX"\
	{$(INCLUDE)}"\XTSNIMP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	

"$(INTDIR)\KOORPAAR.OBJ" : $(SOURCE) $(DEP_CPP_KOORP) "$(INTDIR)"

"$(INTDIR)\KOORPAAR.SBR" : $(SOURCE) $(DEP_CPP_KOORP) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\EDBSSATZ.CPP
DEP_CPP_EDBSS=\
	".\EDBSSATZ.H"\
	".\Import.hpp"\
	".\Stdafx.h"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\ERRCODES.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\IENUMOBJ.HXX"\
	{$(INCLUDE)}"\ISTATUS.H"\
	{$(INCLUDE)}"\IXTENSN.HXX"\
	{$(INCLUDE)}"\OLE16.H"\
	{$(INCLUDE)}"\Ospace\config.h"\
	{$(INCLUDE)}"\Ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\Ospace\std\iosfwd"\
	{$(INCLUDE)}"\Ospace\std\istream"\
	{$(INCLUDE)}"\Ospace\std\ostream"\
	{$(INCLUDE)}"\Ospace\std\string"\
	{$(INCLUDE)}"\Ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\Ospace\stl\allocate.h"\
	{$(INCLUDE)}"\Ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\Ospace\stl\common.h"\
	{$(INCLUDE)}"\Ospace\stl\config.h"\
	{$(INCLUDE)}"\Ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\Ospace\stl\iterator.h"\
	{$(INCLUDE)}"\Ospace\stl\ops.h"\
	{$(INCLUDE)}"\Ospace\stl\pair.h"\
	{$(INCLUDE)}"\Ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\Ospace\string\basic.cc"\
	{$(INCLUDE)}"\Ospace\string\basic.h"\
	{$(INCLUDE)}"\Ospace\string\basic.ipp"\
	{$(INCLUDE)}"\Ospace\string\config.h"\
	{$(INCLUDE)}"\Ospace\string\search.cc"\
	{$(INCLUDE)}"\Ospace\string\search.h"\
	{$(INCLUDE)}"\Ospace\string\string.h"\
	{$(INCLUDE)}"\Ospace\string\traits.cc"\
	{$(INCLUDE)}"\Ospace\string\traits.h"\
	{$(INCLUDE)}"\Ospace\type\prim.h"\
	{$(INCLUDE)}"\Ospace\utility\memory.h"\
	{$(INCLUDE)}"\TRIASM.HXX"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\XTENSION.H"\
	{$(INCLUDE)}"\XTENSNM.HXX"\
	{$(INCLUDE)}"\XTENSNX.H"\
	{$(INCLUDE)}"\XTSNAUX.HXX"\
	{$(INCLUDE)}"\XTSNIMP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	

!IF  "$(CFG)" == "Edbsimp - Win32 Release"


"$(INTDIR)\EDBSSATZ.OBJ" : $(SOURCE) $(DEP_CPP_EDBSS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Edbsimp - Win32 Debug"


"$(INTDIR)\EDBSSATZ.OBJ" : $(SOURCE) $(DEP_CPP_EDBSS) "$(INTDIR)"

"$(INTDIR)\EDBSSATZ.SBR" : $(SOURCE) $(DEP_CPP_EDBSS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Edbsimp - Win32 SmartDebug"


"$(INTDIR)\EDBSSATZ.OBJ" : $(SOURCE) $(DEP_CPP_EDBSS) "$(INTDIR)"

"$(INTDIR)\EDBSSATZ.SBR" : $(SOURCE) $(DEP_CPP_EDBSS) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\REGELN.CPP
DEP_CPP_REGEL=\
	".\CXSTRING.H"\
	".\Import.hpp"\
	".\REGELN.HPP"\
	".\Stdafx.h"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\ERRCODES.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\IENUMOBJ.HXX"\
	{$(INCLUDE)}"\ISTATUS.H"\
	{$(INCLUDE)}"\IXTENSN.HXX"\
	{$(INCLUDE)}"\OLE16.H"\
	{$(INCLUDE)}"\Ospace\config.h"\
	{$(INCLUDE)}"\Ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\Ospace\std\iosfwd"\
	{$(INCLUDE)}"\Ospace\std\istream"\
	{$(INCLUDE)}"\Ospace\std\ostream"\
	{$(INCLUDE)}"\Ospace\std\string"\
	{$(INCLUDE)}"\Ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\Ospace\stl\allocate.h"\
	{$(INCLUDE)}"\Ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\Ospace\stl\common.h"\
	{$(INCLUDE)}"\Ospace\stl\config.h"\
	{$(INCLUDE)}"\Ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\Ospace\stl\iterator.h"\
	{$(INCLUDE)}"\Ospace\stl\ops.h"\
	{$(INCLUDE)}"\Ospace\stl\pair.h"\
	{$(INCLUDE)}"\Ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\Ospace\string\basic.cc"\
	{$(INCLUDE)}"\Ospace\string\basic.h"\
	{$(INCLUDE)}"\Ospace\string\basic.ipp"\
	{$(INCLUDE)}"\Ospace\string\config.h"\
	{$(INCLUDE)}"\Ospace\string\search.cc"\
	{$(INCLUDE)}"\Ospace\string\search.h"\
	{$(INCLUDE)}"\Ospace\string\string.h"\
	{$(INCLUDE)}"\Ospace\string\traits.cc"\
	{$(INCLUDE)}"\Ospace\string\traits.h"\
	{$(INCLUDE)}"\Ospace\type\prim.h"\
	{$(INCLUDE)}"\Ospace\utility\memory.h"\
	{$(INCLUDE)}"\TRIASM.HXX"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\XTENSION.H"\
	{$(INCLUDE)}"\XTENSNM.HXX"\
	{$(INCLUDE)}"\XTENSNX.H"\
	{$(INCLUDE)}"\XTSNAUX.HXX"\
	{$(INCLUDE)}"\XTSNIMP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	

!IF  "$(CFG)" == "Edbsimp - Win32 Release"


"$(INTDIR)\REGELN.OBJ" : $(SOURCE) $(DEP_CPP_REGEL) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Edbsimp - Win32 Debug"


"$(INTDIR)\REGELN.OBJ" : $(SOURCE) $(DEP_CPP_REGEL) "$(INTDIR)"

"$(INTDIR)\REGELN.SBR" : $(SOURCE) $(DEP_CPP_REGEL) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Edbsimp - Win32 SmartDebug"


"$(INTDIR)\REGELN.OBJ" : $(SOURCE) $(DEP_CPP_REGEL) "$(INTDIR)"

"$(INTDIR)\REGELN.SBR" : $(SOURCE) $(DEP_CPP_REGEL) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SETUPDLG.CPP
DEP_CPP_SETUP=\
	".\ARTDIA.HPP"\
	".\ATTRDIA.HPP"\
	".\CWC.H"\
	".\CXSTRING.H"\
	".\DEFMM.HPP"\
	".\Import.hpp"\
	".\REGELN.HPP"\
	".\SETUPDLG.HPP"\
	".\Stdafx.h"\
	".\TRIDDIA.HPP"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\ERRCODES.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\IENUMOBJ.HXX"\
	{$(INCLUDE)}"\ISTATUS.H"\
	{$(INCLUDE)}"\IXTENSN.HXX"\
	{$(INCLUDE)}"\OLE16.H"\
	{$(INCLUDE)}"\Ospace\config.h"\
	{$(INCLUDE)}"\Ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\Ospace\std\iosfwd"\
	{$(INCLUDE)}"\Ospace\std\istream"\
	{$(INCLUDE)}"\Ospace\std\ostream"\
	{$(INCLUDE)}"\Ospace\std\string"\
	{$(INCLUDE)}"\Ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\Ospace\stl\allocate.h"\
	{$(INCLUDE)}"\Ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\Ospace\stl\common.h"\
	{$(INCLUDE)}"\Ospace\stl\config.h"\
	{$(INCLUDE)}"\Ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\Ospace\stl\iterator.h"\
	{$(INCLUDE)}"\Ospace\stl\ops.h"\
	{$(INCLUDE)}"\Ospace\stl\pair.h"\
	{$(INCLUDE)}"\Ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\Ospace\string\basic.cc"\
	{$(INCLUDE)}"\Ospace\string\basic.h"\
	{$(INCLUDE)}"\Ospace\string\basic.ipp"\
	{$(INCLUDE)}"\Ospace\string\config.h"\
	{$(INCLUDE)}"\Ospace\string\search.cc"\
	{$(INCLUDE)}"\Ospace\string\search.h"\
	{$(INCLUDE)}"\Ospace\string\string.h"\
	{$(INCLUDE)}"\Ospace\string\traits.cc"\
	{$(INCLUDE)}"\Ospace\string\traits.h"\
	{$(INCLUDE)}"\Ospace\type\prim.h"\
	{$(INCLUDE)}"\Ospace\utility\memory.h"\
	{$(INCLUDE)}"\TRIASM.HXX"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\XTENSION.H"\
	{$(INCLUDE)}"\XTENSNM.HXX"\
	{$(INCLUDE)}"\XTENSNX.H"\
	{$(INCLUDE)}"\XTSNAUX.HXX"\
	{$(INCLUDE)}"\XTSNIMP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	

!IF  "$(CFG)" == "Edbsimp - Win32 Release"


"$(INTDIR)\SETUPDLG.OBJ" : $(SOURCE) $(DEP_CPP_SETUP) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Edbsimp - Win32 Debug"


"$(INTDIR)\SETUPDLG.OBJ" : $(SOURCE) $(DEP_CPP_SETUP) "$(INTDIR)"

"$(INTDIR)\SETUPDLG.SBR" : $(SOURCE) $(DEP_CPP_SETUP) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Edbsimp - Win32 SmartDebug"


"$(INTDIR)\SETUPDLG.OBJ" : $(SOURCE) $(DEP_CPP_SETUP) "$(INTDIR)"

"$(INTDIR)\SETUPDLG.SBR" : $(SOURCE) $(DEP_CPP_SETUP) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ARTDIA.CPP
DEP_CPP_ARTDI=\
	".\ARTDIA.HPP"\
	".\CXSTRING.H"\
	".\DEFMM.HPP"\
	".\EDITMERK.H"\
	".\Import.hpp"\
	".\Stdafx.h"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\ERRCODES.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\IENUMOBJ.HXX"\
	{$(INCLUDE)}"\ISTATUS.H"\
	{$(INCLUDE)}"\IXTENSN.HXX"\
	{$(INCLUDE)}"\OLE16.H"\
	{$(INCLUDE)}"\Ospace\config.h"\
	{$(INCLUDE)}"\Ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\Ospace\std\iosfwd"\
	{$(INCLUDE)}"\Ospace\std\istream"\
	{$(INCLUDE)}"\Ospace\std\ostream"\
	{$(INCLUDE)}"\Ospace\std\string"\
	{$(INCLUDE)}"\Ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\Ospace\stl\allocate.h"\
	{$(INCLUDE)}"\Ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\Ospace\stl\common.h"\
	{$(INCLUDE)}"\Ospace\stl\config.h"\
	{$(INCLUDE)}"\Ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\Ospace\stl\iterator.h"\
	{$(INCLUDE)}"\Ospace\stl\ops.h"\
	{$(INCLUDE)}"\Ospace\stl\pair.h"\
	{$(INCLUDE)}"\Ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\Ospace\string\basic.cc"\
	{$(INCLUDE)}"\Ospace\string\basic.h"\
	{$(INCLUDE)}"\Ospace\string\basic.ipp"\
	{$(INCLUDE)}"\Ospace\string\config.h"\
	{$(INCLUDE)}"\Ospace\string\search.cc"\
	{$(INCLUDE)}"\Ospace\string\search.h"\
	{$(INCLUDE)}"\Ospace\string\string.h"\
	{$(INCLUDE)}"\Ospace\string\traits.cc"\
	{$(INCLUDE)}"\Ospace\string\traits.h"\
	{$(INCLUDE)}"\Ospace\type\prim.h"\
	{$(INCLUDE)}"\Ospace\utility\memory.h"\
	{$(INCLUDE)}"\TRIASM.HXX"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\XTENSION.H"\
	{$(INCLUDE)}"\XTENSNM.HXX"\
	{$(INCLUDE)}"\XTENSNX.H"\
	{$(INCLUDE)}"\XTSNAUX.HXX"\
	{$(INCLUDE)}"\XTSNIMP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	

!IF  "$(CFG)" == "Edbsimp - Win32 Release"


"$(INTDIR)\ARTDIA.OBJ" : $(SOURCE) $(DEP_CPP_ARTDI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Edbsimp - Win32 Debug"


"$(INTDIR)\ARTDIA.OBJ" : $(SOURCE) $(DEP_CPP_ARTDI) "$(INTDIR)"

"$(INTDIR)\ARTDIA.SBR" : $(SOURCE) $(DEP_CPP_ARTDI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Edbsimp - Win32 SmartDebug"


"$(INTDIR)\ARTDIA.OBJ" : $(SOURCE) $(DEP_CPP_ARTDI) "$(INTDIR)"

"$(INTDIR)\ARTDIA.SBR" : $(SOURCE) $(DEP_CPP_ARTDI) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\HDRENTRX.CPP
DEP_CPP_HDREN=\
	".\Import.hpp"\
	".\Stdafx.h"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\ERRCODES.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\HDRENTRX.HXX"\
	{$(INCLUDE)}"\IENUMOBJ.HXX"\
	{$(INCLUDE)}"\ISTATUS.H"\
	{$(INCLUDE)}"\IXTENSN.HXX"\
	{$(INCLUDE)}"\OLE16.H"\
	{$(INCLUDE)}"\Ospace\config.h"\
	{$(INCLUDE)}"\Ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\Ospace\std\iosfwd"\
	{$(INCLUDE)}"\Ospace\std\istream"\
	{$(INCLUDE)}"\Ospace\std\ostream"\
	{$(INCLUDE)}"\Ospace\std\string"\
	{$(INCLUDE)}"\Ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\Ospace\stl\allocate.h"\
	{$(INCLUDE)}"\Ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\Ospace\stl\common.h"\
	{$(INCLUDE)}"\Ospace\stl\config.h"\
	{$(INCLUDE)}"\Ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\Ospace\stl\iterator.h"\
	{$(INCLUDE)}"\Ospace\stl\ops.h"\
	{$(INCLUDE)}"\Ospace\stl\pair.h"\
	{$(INCLUDE)}"\Ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\Ospace\string\basic.cc"\
	{$(INCLUDE)}"\Ospace\string\basic.h"\
	{$(INCLUDE)}"\Ospace\string\basic.ipp"\
	{$(INCLUDE)}"\Ospace\string\config.h"\
	{$(INCLUDE)}"\Ospace\string\search.cc"\
	{$(INCLUDE)}"\Ospace\string\search.h"\
	{$(INCLUDE)}"\Ospace\string\string.h"\
	{$(INCLUDE)}"\Ospace\string\traits.cc"\
	{$(INCLUDE)}"\Ospace\string\traits.h"\
	{$(INCLUDE)}"\Ospace\type\prim.h"\
	{$(INCLUDE)}"\Ospace\utility\memory.h"\
	{$(INCLUDE)}"\TRIASM.HXX"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\XTENSION.H"\
	{$(INCLUDE)}"\XTENSNM.HXX"\
	{$(INCLUDE)}"\XTENSNX.H"\
	{$(INCLUDE)}"\XTSNAUX.HXX"\
	{$(INCLUDE)}"\XTSNIMP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	

!IF  "$(CFG)" == "Edbsimp - Win32 Release"


"$(INTDIR)\HDRENTRX.OBJ" : $(SOURCE) $(DEP_CPP_HDREN) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Edbsimp - Win32 Debug"


"$(INTDIR)\HDRENTRX.OBJ" : $(SOURCE) $(DEP_CPP_HDREN) "$(INTDIR)"

"$(INTDIR)\HDRENTRX.SBR" : $(SOURCE) $(DEP_CPP_HDREN) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Edbsimp - Win32 SmartDebug"


"$(INTDIR)\HDRENTRX.OBJ" : $(SOURCE) $(DEP_CPP_HDREN) "$(INTDIR)"

"$(INTDIR)\HDRENTRX.SBR" : $(SOURCE) $(DEP_CPP_HDREN) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DEFMM.CPP
DEP_CPP_DEFMM=\
	".\CXSTRING.H"\
	".\DEFMM.HPP"\
	".\Import.hpp"\
	".\Stdafx.h"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\ERRCODES.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\IENUMOBJ.HXX"\
	{$(INCLUDE)}"\ISTATUS.H"\
	{$(INCLUDE)}"\IXTENSN.HXX"\
	{$(INCLUDE)}"\OLE16.H"\
	{$(INCLUDE)}"\Ospace\config.h"\
	{$(INCLUDE)}"\Ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\Ospace\std\iosfwd"\
	{$(INCLUDE)}"\Ospace\std\istream"\
	{$(INCLUDE)}"\Ospace\std\ostream"\
	{$(INCLUDE)}"\Ospace\std\string"\
	{$(INCLUDE)}"\Ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\Ospace\stl\allocate.h"\
	{$(INCLUDE)}"\Ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\Ospace\stl\common.h"\
	{$(INCLUDE)}"\Ospace\stl\config.h"\
	{$(INCLUDE)}"\Ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\Ospace\stl\iterator.h"\
	{$(INCLUDE)}"\Ospace\stl\ops.h"\
	{$(INCLUDE)}"\Ospace\stl\pair.h"\
	{$(INCLUDE)}"\Ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\Ospace\string\basic.cc"\
	{$(INCLUDE)}"\Ospace\string\basic.h"\
	{$(INCLUDE)}"\Ospace\string\basic.ipp"\
	{$(INCLUDE)}"\Ospace\string\config.h"\
	{$(INCLUDE)}"\Ospace\string\search.cc"\
	{$(INCLUDE)}"\Ospace\string\search.h"\
	{$(INCLUDE)}"\Ospace\string\string.h"\
	{$(INCLUDE)}"\Ospace\string\traits.cc"\
	{$(INCLUDE)}"\Ospace\string\traits.h"\
	{$(INCLUDE)}"\Ospace\type\prim.h"\
	{$(INCLUDE)}"\Ospace\utility\memory.h"\
	{$(INCLUDE)}"\TRIASM.HXX"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\XTENSION.H"\
	{$(INCLUDE)}"\XTENSNM.HXX"\
	{$(INCLUDE)}"\XTENSNX.H"\
	{$(INCLUDE)}"\XTSNAUX.HXX"\
	{$(INCLUDE)}"\XTSNIMP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	

!IF  "$(CFG)" == "Edbsimp - Win32 Release"


"$(INTDIR)\DEFMM.OBJ" : $(SOURCE) $(DEP_CPP_DEFMM) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Edbsimp - Win32 Debug"


"$(INTDIR)\DEFMM.OBJ" : $(SOURCE) $(DEP_CPP_DEFMM) "$(INTDIR)"

"$(INTDIR)\DEFMM.SBR" : $(SOURCE) $(DEP_CPP_DEFMM) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Edbsimp - Win32 SmartDebug"


"$(INTDIR)\DEFMM.OBJ" : $(SOURCE) $(DEP_CPP_DEFMM) "$(INTDIR)"

"$(INTDIR)\DEFMM.SBR" : $(SOURCE) $(DEP_CPP_DEFMM) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\EDBS.CPP

!IF  "$(CFG)" == "Edbsimp - Win32 Release"

DEP_CPP_EDBS_=\
	".\CXSTRING.H"\
	".\EDBS.HPP"\
	".\EDBSGUID.H"\
	".\GEOOBJ.HPP"\
	".\Import.hpp"\
	".\OBJPOOL.HPP"\
	".\Stdafx.h"\
	".\VERSIO16.H"\
	".\VERSIO32.H"\
	".\Version.h"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\EONRGUID.H"\
	{$(INCLUDE)}"\ERRCODES.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\IENUMOBJ.HXX"\
	{$(INCLUDE)}"\ISTATUS.H"\
	{$(INCLUDE)}"\IXTENSN.HXX"\
	{$(INCLUDE)}"\OLE16.H"\
	{$(INCLUDE)}"\Ospace\config.h"\
	{$(INCLUDE)}"\Ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\Ospace\std\iosfwd"\
	{$(INCLUDE)}"\Ospace\std\istream"\
	{$(INCLUDE)}"\Ospace\std\ostream"\
	{$(INCLUDE)}"\Ospace\std\string"\
	{$(INCLUDE)}"\Ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\Ospace\stl\allocate.h"\
	{$(INCLUDE)}"\Ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\Ospace\stl\common.h"\
	{$(INCLUDE)}"\Ospace\stl\config.h"\
	{$(INCLUDE)}"\Ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\Ospace\stl\iterator.h"\
	{$(INCLUDE)}"\Ospace\stl\ops.h"\
	{$(INCLUDE)}"\Ospace\stl\pair.h"\
	{$(INCLUDE)}"\Ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\Ospace\string\basic.cc"\
	{$(INCLUDE)}"\Ospace\string\basic.h"\
	{$(INCLUDE)}"\Ospace\string\basic.ipp"\
	{$(INCLUDE)}"\Ospace\string\config.h"\
	{$(INCLUDE)}"\Ospace\string\search.cc"\
	{$(INCLUDE)}"\Ospace\string\search.h"\
	{$(INCLUDE)}"\Ospace\string\string.h"\
	{$(INCLUDE)}"\Ospace\string\traits.cc"\
	{$(INCLUDE)}"\Ospace\string\traits.h"\
	{$(INCLUDE)}"\Ospace\type\prim.h"\
	{$(INCLUDE)}"\Ospace\utility\memory.h"\
	{$(INCLUDE)}"\STATGUID.H"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TRiASHelper_i.c"\
	{$(INCLUDE)}"\TRIASM.HXX"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\XTENSION.H"\
	{$(INCLUDE)}"\XTENSNM.HXX"\
	{$(INCLUDE)}"\XTENSNX.H"\
	{$(INCLUDE)}"\XTSNAUX.HXX"\
	{$(INCLUDE)}"\XTSNGUID.H"\
	{$(INCLUDE)}"\XTSNIMP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	

"$(INTDIR)\EDBS.OBJ" : $(SOURCE) $(DEP_CPP_EDBS_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Edbsimp - Win32 Debug"

DEP_CPP_EDBS_=\
	".\CXSTRING.H"\
	".\EDBS.HPP"\
	".\EDBSGUID.H"\
	".\GEOOBJ.HPP"\
	".\Import.hpp"\
	".\OBJPOOL.HPP"\
	".\Stdafx.h"\
	".\VERSIO16.H"\
	".\VERSIO32.H"\
	".\Version.h"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\EONRGUID.H"\
	{$(INCLUDE)}"\ISTATUS.H"\
	{$(INCLUDE)}"\OLE16.H"\
	{$(INCLUDE)}"\Ospace\config.h"\
	{$(INCLUDE)}"\Ospace\std\string"\
	{$(INCLUDE)}"\STATGUID.H"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TRiASHelper_i.c"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\XTSNGUID.H"\
	

"$(INTDIR)\EDBS.OBJ" : $(SOURCE) $(DEP_CPP_EDBS_) "$(INTDIR)"

"$(INTDIR)\EDBS.SBR" : $(SOURCE) $(DEP_CPP_EDBS_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Edbsimp - Win32 SmartDebug"

DEP_CPP_EDBS_=\
	".\CXSTRING.H"\
	".\EDBS.HPP"\
	".\EDBSGUID.H"\
	".\GEOOBJ.HPP"\
	".\Import.hpp"\
	".\OBJPOOL.HPP"\
	".\Stdafx.h"\
	".\VERSIO16.H"\
	".\VERSIO32.H"\
	".\Version.h"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\EONRGUID.H"\
	{$(INCLUDE)}"\ERRCODES.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\IENUMOBJ.HXX"\
	{$(INCLUDE)}"\ISTATUS.H"\
	{$(INCLUDE)}"\IXTENSN.HXX"\
	{$(INCLUDE)}"\OLE16.H"\
	{$(INCLUDE)}"\Ospace\config.h"\
	{$(INCLUDE)}"\Ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\Ospace\std\iosfwd"\
	{$(INCLUDE)}"\Ospace\std\istream"\
	{$(INCLUDE)}"\Ospace\std\ostream"\
	{$(INCLUDE)}"\Ospace\std\string"\
	{$(INCLUDE)}"\Ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\Ospace\stl\allocate.h"\
	{$(INCLUDE)}"\Ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\Ospace\stl\common.h"\
	{$(INCLUDE)}"\Ospace\stl\config.h"\
	{$(INCLUDE)}"\Ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\Ospace\stl\iterator.h"\
	{$(INCLUDE)}"\Ospace\stl\ops.h"\
	{$(INCLUDE)}"\Ospace\stl\pair.h"\
	{$(INCLUDE)}"\Ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\Ospace\string\basic.cc"\
	{$(INCLUDE)}"\Ospace\string\basic.h"\
	{$(INCLUDE)}"\Ospace\string\basic.ipp"\
	{$(INCLUDE)}"\Ospace\string\config.h"\
	{$(INCLUDE)}"\Ospace\string\search.cc"\
	{$(INCLUDE)}"\Ospace\string\search.h"\
	{$(INCLUDE)}"\Ospace\string\string.h"\
	{$(INCLUDE)}"\Ospace\string\traits.cc"\
	{$(INCLUDE)}"\Ospace\string\traits.h"\
	{$(INCLUDE)}"\Ospace\type\prim.h"\
	{$(INCLUDE)}"\Ospace\utility\memory.h"\
	{$(INCLUDE)}"\STATGUID.H"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TRiASHelper_i.c"\
	{$(INCLUDE)}"\TRIASM.HXX"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\XTENSION.H"\
	{$(INCLUDE)}"\XTENSNM.HXX"\
	{$(INCLUDE)}"\XTENSNX.H"\
	{$(INCLUDE)}"\XTSNAUX.HXX"\
	{$(INCLUDE)}"\XTSNGUID.H"\
	{$(INCLUDE)}"\XTSNIMP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	

"$(INTDIR)\EDBS.OBJ" : $(SOURCE) $(DEP_CPP_EDBS_) "$(INTDIR)"

"$(INTDIR)\EDBS.SBR" : $(SOURCE) $(DEP_CPP_EDBS_) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ATTRDIA.CPP
DEP_CPP_ATTRD=\
	".\ATTRDIA.HPP"\
	".\CXSTRING.H"\
	".\DEFMM.HPP"\
	".\Import.hpp"\
	".\Stdafx.h"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\ERRCODES.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\IENUMOBJ.HXX"\
	{$(INCLUDE)}"\ISTATUS.H"\
	{$(INCLUDE)}"\IXTENSN.HXX"\
	{$(INCLUDE)}"\OLE16.H"\
	{$(INCLUDE)}"\Ospace\config.h"\
	{$(INCLUDE)}"\Ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\Ospace\std\iosfwd"\
	{$(INCLUDE)}"\Ospace\std\istream"\
	{$(INCLUDE)}"\Ospace\std\ostream"\
	{$(INCLUDE)}"\Ospace\std\string"\
	{$(INCLUDE)}"\Ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\Ospace\stl\allocate.h"\
	{$(INCLUDE)}"\Ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\Ospace\stl\common.h"\
	{$(INCLUDE)}"\Ospace\stl\config.h"\
	{$(INCLUDE)}"\Ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\Ospace\stl\iterator.h"\
	{$(INCLUDE)}"\Ospace\stl\ops.h"\
	{$(INCLUDE)}"\Ospace\stl\pair.h"\
	{$(INCLUDE)}"\Ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\Ospace\string\basic.cc"\
	{$(INCLUDE)}"\Ospace\string\basic.h"\
	{$(INCLUDE)}"\Ospace\string\basic.ipp"\
	{$(INCLUDE)}"\Ospace\string\config.h"\
	{$(INCLUDE)}"\Ospace\string\search.cc"\
	{$(INCLUDE)}"\Ospace\string\search.h"\
	{$(INCLUDE)}"\Ospace\string\string.h"\
	{$(INCLUDE)}"\Ospace\string\traits.cc"\
	{$(INCLUDE)}"\Ospace\string\traits.h"\
	{$(INCLUDE)}"\Ospace\type\prim.h"\
	{$(INCLUDE)}"\Ospace\utility\memory.h"\
	{$(INCLUDE)}"\TRIASM.HXX"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\XTENSION.H"\
	{$(INCLUDE)}"\XTENSNM.HXX"\
	{$(INCLUDE)}"\XTENSNX.H"\
	{$(INCLUDE)}"\XTSNAUX.HXX"\
	{$(INCLUDE)}"\XTSNIMP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	

!IF  "$(CFG)" == "Edbsimp - Win32 Release"


"$(INTDIR)\ATTRDIA.OBJ" : $(SOURCE) $(DEP_CPP_ATTRD) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Edbsimp - Win32 Debug"


"$(INTDIR)\ATTRDIA.OBJ" : $(SOURCE) $(DEP_CPP_ATTRD) "$(INTDIR)"

"$(INTDIR)\ATTRDIA.SBR" : $(SOURCE) $(DEP_CPP_ATTRD) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Edbsimp - Win32 SmartDebug"


"$(INTDIR)\ATTRDIA.OBJ" : $(SOURCE) $(DEP_CPP_ATTRD) "$(INTDIR)"

"$(INTDIR)\ATTRDIA.SBR" : $(SOURCE) $(DEP_CPP_ATTRD) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ATKISSAT.CPP

!IF  "$(CFG)" == "Edbsimp - Win32 Release"

DEP_CPP_ATKIS=\
	".\Atkissat.h"\
	".\KOORPAAR.H"\
	".\Linie.h"\
	".\Stdafx.h"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\OLE16.H"\
	{$(INCLUDE)}"\Ospace\std\string"\
	{$(INCLUDE)}"\Tstring"\
	

"$(INTDIR)\ATKISSAT.OBJ" : $(SOURCE) $(DEP_CPP_ATKIS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Edbsimp - Win32 Debug"

DEP_CPP_ATKIS=\
	".\Atkissat.h"\
	".\Import.hpp"\
	".\KOORPAAR.H"\
	".\Linie.h"\
	".\Stdafx.h"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\ERRCODES.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\IENUMOBJ.HXX"\
	{$(INCLUDE)}"\ISTATUS.H"\
	{$(INCLUDE)}"\IXTENSN.HXX"\
	{$(INCLUDE)}"\OLE16.H"\
	{$(INCLUDE)}"\Ospace\config.h"\
	{$(INCLUDE)}"\Ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\Ospace\std\iosfwd"\
	{$(INCLUDE)}"\Ospace\std\istream"\
	{$(INCLUDE)}"\Ospace\std\ostream"\
	{$(INCLUDE)}"\Ospace\std\string"\
	{$(INCLUDE)}"\Ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\Ospace\stl\allocate.h"\
	{$(INCLUDE)}"\Ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\Ospace\stl\common.h"\
	{$(INCLUDE)}"\Ospace\stl\config.h"\
	{$(INCLUDE)}"\Ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\Ospace\stl\iterator.h"\
	{$(INCLUDE)}"\Ospace\stl\ops.h"\
	{$(INCLUDE)}"\Ospace\stl\pair.h"\
	{$(INCLUDE)}"\Ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\Ospace\string\basic.cc"\
	{$(INCLUDE)}"\Ospace\string\basic.h"\
	{$(INCLUDE)}"\Ospace\string\basic.ipp"\
	{$(INCLUDE)}"\Ospace\string\config.h"\
	{$(INCLUDE)}"\Ospace\string\search.cc"\
	{$(INCLUDE)}"\Ospace\string\search.h"\
	{$(INCLUDE)}"\Ospace\string\string.h"\
	{$(INCLUDE)}"\Ospace\string\traits.cc"\
	{$(INCLUDE)}"\Ospace\string\traits.h"\
	{$(INCLUDE)}"\Ospace\type\prim.h"\
	{$(INCLUDE)}"\Ospace\utility\memory.h"\
	{$(INCLUDE)}"\TRIASM.HXX"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\XTENSION.H"\
	{$(INCLUDE)}"\XTENSNM.HXX"\
	{$(INCLUDE)}"\XTENSNX.H"\
	{$(INCLUDE)}"\XTSNAUX.HXX"\
	{$(INCLUDE)}"\XTSNIMP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	

"$(INTDIR)\ATKISSAT.OBJ" : $(SOURCE) $(DEP_CPP_ATKIS) "$(INTDIR)"

"$(INTDIR)\ATKISSAT.SBR" : $(SOURCE) $(DEP_CPP_ATKIS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Edbsimp - Win32 SmartDebug"

DEP_CPP_ATKIS=\
	".\Atkissat.h"\
	".\KOORPAAR.H"\
	".\Linie.h"\
	".\Stdafx.h"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\OLE16.H"\
	{$(INCLUDE)}"\Tstring"\
	

"$(INTDIR)\ATKISSAT.OBJ" : $(SOURCE) $(DEP_CPP_ATKIS) "$(INTDIR)"

"$(INTDIR)\ATKISSAT.SBR" : $(SOURCE) $(DEP_CPP_ATKIS) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TRIF.CPP

!IF  "$(CFG)" == "Edbsimp - Win32 Release"

DEP_CPP_TRIF_=\
	".\CXSTRING.H"\
	".\REGELN.HPP"\
	".\Stdafx.h"\
	".\TRIF.HPP"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ERRCODES.HXX"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\HDRENTRX.HXX"\
	{$(INCLUDE)}"\OLE16.H"\
	{$(INCLUDE)}"\Ospace\config.h"\
	{$(INCLUDE)}"\Ospace\std\string"\
	{$(INCLUDE)}"\Ospace\stl\config.h"\
	{$(INCLUDE)}"\Ospace\string\string.h"\
	{$(INCLUDE)}"\Ospace\string\traits.h"\
	{$(INCLUDE)}"\Ospace\type\prim.h"\
	{$(INCLUDE)}"\Ospace\utility\memory.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\XTENSION.H"\
	{$(INCLUDE)}"\XTENSNN.H"\
	{$(INCLUDE)}"\XTENSNX.H"\
	

"$(INTDIR)\TRIF.OBJ" : $(SOURCE) $(DEP_CPP_TRIF_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Edbsimp - Win32 Debug"

DEP_CPP_TRIF_=\
	".\CXSTRING.H"\
	".\REGELN.HPP"\
	".\Stdafx.h"\
	".\TRIF.HPP"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\ERRCODES.HXX"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\HDRENTRX.HXX"\
	{$(INCLUDE)}"\OLE16.H"\
	{$(INCLUDE)}"\Ospace\config.h"\
	{$(INCLUDE)}"\Ospace\std\string"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\XTENSION.H"\
	{$(INCLUDE)}"\XTENSNM.HXX"\
	{$(INCLUDE)}"\XTENSNN.H"\
	{$(INCLUDE)}"\XTENSNX.H"\
	

"$(INTDIR)\TRIF.OBJ" : $(SOURCE) $(DEP_CPP_TRIF_) "$(INTDIR)"

"$(INTDIR)\TRIF.SBR" : $(SOURCE) $(DEP_CPP_TRIF_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Edbsimp - Win32 SmartDebug"

DEP_CPP_TRIF_=\
	".\CXSTRING.H"\
	".\REGELN.HPP"\
	".\Stdafx.h"\
	".\TRIF.HPP"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\ERRCODES.HXX"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\HDRENTRX.HXX"\
	{$(INCLUDE)}"\OLE16.H"\
	{$(INCLUDE)}"\XTENSION.H"\
	{$(INCLUDE)}"\XTENSNM.HXX"\
	{$(INCLUDE)}"\XTENSNN.H"\
	{$(INCLUDE)}"\XTENSNX.H"\
	

"$(INTDIR)\TRIF.OBJ" : $(SOURCE) $(DEP_CPP_TRIF_) "$(INTDIR)"

"$(INTDIR)\TRIF.SBR" : $(SOURCE) $(DEP_CPP_TRIF_) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ACTDIA.CPP
DEP_CPP_ACTDI=\
	".\ACTDIA.HPP"\
	".\Import.hpp"\
	".\Stdafx.h"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\ERRCODES.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\IENUMOBJ.HXX"\
	{$(INCLUDE)}"\ISTATUS.H"\
	{$(INCLUDE)}"\IXTENSN.HXX"\
	{$(INCLUDE)}"\OLE16.H"\
	{$(INCLUDE)}"\Ospace\config.h"\
	{$(INCLUDE)}"\Ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\Ospace\std\iosfwd"\
	{$(INCLUDE)}"\Ospace\std\istream"\
	{$(INCLUDE)}"\Ospace\std\ostream"\
	{$(INCLUDE)}"\Ospace\std\string"\
	{$(INCLUDE)}"\Ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\Ospace\stl\allocate.h"\
	{$(INCLUDE)}"\Ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\Ospace\stl\common.h"\
	{$(INCLUDE)}"\Ospace\stl\config.h"\
	{$(INCLUDE)}"\Ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\Ospace\stl\iterator.h"\
	{$(INCLUDE)}"\Ospace\stl\ops.h"\
	{$(INCLUDE)}"\Ospace\stl\pair.h"\
	{$(INCLUDE)}"\Ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\Ospace\string\basic.cc"\
	{$(INCLUDE)}"\Ospace\string\basic.h"\
	{$(INCLUDE)}"\Ospace\string\basic.ipp"\
	{$(INCLUDE)}"\Ospace\string\config.h"\
	{$(INCLUDE)}"\Ospace\string\search.cc"\
	{$(INCLUDE)}"\Ospace\string\search.h"\
	{$(INCLUDE)}"\Ospace\string\string.h"\
	{$(INCLUDE)}"\Ospace\string\traits.cc"\
	{$(INCLUDE)}"\Ospace\string\traits.h"\
	{$(INCLUDE)}"\Ospace\type\prim.h"\
	{$(INCLUDE)}"\Ospace\utility\memory.h"\
	{$(INCLUDE)}"\TRIASM.HXX"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\XTENSION.H"\
	{$(INCLUDE)}"\XTENSNM.HXX"\
	{$(INCLUDE)}"\XTENSNX.H"\
	{$(INCLUDE)}"\XTSNAUX.HXX"\
	{$(INCLUDE)}"\XTSNIMP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	

!IF  "$(CFG)" == "Edbsimp - Win32 Release"


"$(INTDIR)\ACTDIA.OBJ" : $(SOURCE) $(DEP_CPP_ACTDI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Edbsimp - Win32 Debug"


"$(INTDIR)\ACTDIA.OBJ" : $(SOURCE) $(DEP_CPP_ACTDI) "$(INTDIR)"

"$(INTDIR)\ACTDIA.SBR" : $(SOURCE) $(DEP_CPP_ACTDI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Edbsimp - Win32 SmartDebug"


"$(INTDIR)\ACTDIA.OBJ" : $(SOURCE) $(DEP_CPP_ACTDI) "$(INTDIR)"

"$(INTDIR)\ACTDIA.SBR" : $(SOURCE) $(DEP_CPP_ACTDI) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\EDBSFO.CPP
DEP_CPP_EDBSF=\
	".\EDBSFO.HPP"\
	".\Import.hpp"\
	".\Stdafx.h"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\ERRCODES.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\IENUMOBJ.HXX"\
	{$(INCLUDE)}"\ISTATUS.H"\
	{$(INCLUDE)}"\IXTENSN.HXX"\
	{$(INCLUDE)}"\OLE16.H"\
	{$(INCLUDE)}"\Ospace\config.h"\
	{$(INCLUDE)}"\Ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\Ospace\std\iosfwd"\
	{$(INCLUDE)}"\Ospace\std\istream"\
	{$(INCLUDE)}"\Ospace\std\ostream"\
	{$(INCLUDE)}"\Ospace\std\string"\
	{$(INCLUDE)}"\Ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\Ospace\stl\allocate.h"\
	{$(INCLUDE)}"\Ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\Ospace\stl\common.h"\
	{$(INCLUDE)}"\Ospace\stl\config.h"\
	{$(INCLUDE)}"\Ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\Ospace\stl\iterator.h"\
	{$(INCLUDE)}"\Ospace\stl\ops.h"\
	{$(INCLUDE)}"\Ospace\stl\pair.h"\
	{$(INCLUDE)}"\Ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\Ospace\string\basic.cc"\
	{$(INCLUDE)}"\Ospace\string\basic.h"\
	{$(INCLUDE)}"\Ospace\string\basic.ipp"\
	{$(INCLUDE)}"\Ospace\string\config.h"\
	{$(INCLUDE)}"\Ospace\string\search.cc"\
	{$(INCLUDE)}"\Ospace\string\search.h"\
	{$(INCLUDE)}"\Ospace\string\string.h"\
	{$(INCLUDE)}"\Ospace\string\traits.cc"\
	{$(INCLUDE)}"\Ospace\string\traits.h"\
	{$(INCLUDE)}"\Ospace\type\prim.h"\
	{$(INCLUDE)}"\Ospace\utility\memory.h"\
	{$(INCLUDE)}"\TRIASM.HXX"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\XTENSION.H"\
	{$(INCLUDE)}"\XTENSNM.HXX"\
	{$(INCLUDE)}"\XTENSNX.H"\
	{$(INCLUDE)}"\XTSNAUX.HXX"\
	{$(INCLUDE)}"\XTSNIMP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	

!IF  "$(CFG)" == "Edbsimp - Win32 Release"


"$(INTDIR)\EDBSFO.OBJ" : $(SOURCE) $(DEP_CPP_EDBSF) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Edbsimp - Win32 Debug"


"$(INTDIR)\EDBSFO.OBJ" : $(SOURCE) $(DEP_CPP_EDBSF) "$(INTDIR)"

"$(INTDIR)\EDBSFO.SBR" : $(SOURCE) $(DEP_CPP_EDBSF) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Edbsimp - Win32 SmartDebug"


"$(INTDIR)\EDBSFO.OBJ" : $(SOURCE) $(DEP_CPP_EDBSF) "$(INTDIR)"

"$(INTDIR)\EDBSFO.SBR" : $(SOURCE) $(DEP_CPP_EDBSF) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\OBJPOOL.CPP
DEP_CPP_OBJPO=\
	".\CXSTRING.H"\
	".\EDBS.HPP"\
	".\GEOOBJ.HPP"\
	".\Import.hpp"\
	".\OBJPOOL.HPP"\
	".\REGELN.HPP"\
	".\Stdafx.h"\
	".\TRIF.HPP"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\ERRCODES.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\IENUMOBJ.HXX"\
	{$(INCLUDE)}"\ISTATUS.H"\
	{$(INCLUDE)}"\IXTENSN.HXX"\
	{$(INCLUDE)}"\OLE16.H"\
	{$(INCLUDE)}"\Ospace\config.h"\
	{$(INCLUDE)}"\Ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\Ospace\std\iosfwd"\
	{$(INCLUDE)}"\Ospace\std\istream"\
	{$(INCLUDE)}"\Ospace\std\ostream"\
	{$(INCLUDE)}"\Ospace\std\string"\
	{$(INCLUDE)}"\Ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\Ospace\stl\allocate.h"\
	{$(INCLUDE)}"\Ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\Ospace\stl\common.h"\
	{$(INCLUDE)}"\Ospace\stl\config.h"\
	{$(INCLUDE)}"\Ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\Ospace\stl\iterator.h"\
	{$(INCLUDE)}"\Ospace\stl\ops.h"\
	{$(INCLUDE)}"\Ospace\stl\pair.h"\
	{$(INCLUDE)}"\Ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\Ospace\string\basic.cc"\
	{$(INCLUDE)}"\Ospace\string\basic.h"\
	{$(INCLUDE)}"\Ospace\string\basic.ipp"\
	{$(INCLUDE)}"\Ospace\string\config.h"\
	{$(INCLUDE)}"\Ospace\string\search.cc"\
	{$(INCLUDE)}"\Ospace\string\search.h"\
	{$(INCLUDE)}"\Ospace\string\string.h"\
	{$(INCLUDE)}"\Ospace\string\traits.cc"\
	{$(INCLUDE)}"\Ospace\string\traits.h"\
	{$(INCLUDE)}"\Ospace\type\prim.h"\
	{$(INCLUDE)}"\Ospace\utility\memory.h"\
	{$(INCLUDE)}"\TRIASM.HXX"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\XTENSION.H"\
	{$(INCLUDE)}"\XTENSNM.HXX"\
	{$(INCLUDE)}"\XTENSNX.H"\
	{$(INCLUDE)}"\XTSNAUX.HXX"\
	{$(INCLUDE)}"\XTSNIMP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	

!IF  "$(CFG)" == "Edbsimp - Win32 Release"


"$(INTDIR)\OBJPOOL.OBJ" : $(SOURCE) $(DEP_CPP_OBJPO) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Edbsimp - Win32 Debug"


"$(INTDIR)\OBJPOOL.OBJ" : $(SOURCE) $(DEP_CPP_OBJPO) "$(INTDIR)"

"$(INTDIR)\OBJPOOL.SBR" : $(SOURCE) $(DEP_CPP_OBJPO) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Edbsimp - Win32 SmartDebug"


"$(INTDIR)\OBJPOOL.OBJ" : $(SOURCE) $(DEP_CPP_OBJPO) "$(INTDIR)"

"$(INTDIR)\OBJPOOL.SBR" : $(SOURCE) $(DEP_CPP_OBJPO) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\IMPORT.CPP

!IF  "$(CFG)" == "Edbsimp - Win32 Release"

DEP_CPP_IMPOR=\
	".\ACTDIA.HPP"\
	".\Atkissat.h"\
	".\CWC.H"\
	".\CXSTRING.H"\
	".\EDBS.HPP"\
	".\EDBSSATZ.H"\
	".\GEOOBJ.HPP"\
	".\Import.hpp"\
	".\KOORPAAR.H"\
	".\Linie.h"\
	".\OBJPOOL.HPP"\
	".\REGELN.HPP"\
	".\SETUPDLG.HPP"\
	".\Stdafx.h"\
	".\TRIF.HPP"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTATUS.H"\
	{$(INCLUDE)}"\OLE16.H"\
	{$(INCLUDE)}"\Ospace\config.h"\
	{$(INCLUDE)}"\Ospace\std\string"\
	{$(INCLUDE)}"\Ospace\string\string.h"\
	{$(INCLUDE)}"\Ospace\string\traits.h"\
	{$(INCLUDE)}"\Ospace\type\prim.h"\
	{$(INCLUDE)}"\Tstring"\
	

"$(INTDIR)\IMPORT.OBJ" : $(SOURCE) $(DEP_CPP_IMPOR) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Edbsimp - Win32 Debug"

DEP_CPP_IMPOR=\
	".\ACTDIA.HPP"\
	".\Atkissat.h"\
	".\CWC.H"\
	".\CXSTRING.H"\
	".\EDBS.HPP"\
	".\EDBSSATZ.H"\
	".\GEOOBJ.HPP"\
	".\Import.hpp"\
	".\KOORPAAR.H"\
	".\Linie.h"\
	".\OBJPOOL.HPP"\
	".\REGELN.HPP"\
	".\SETUPDLG.HPP"\
	".\Stdafx.h"\
	".\TRIF.HPP"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\ERRCODES.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\IENUMOBJ.HXX"\
	{$(INCLUDE)}"\ISTATUS.H"\
	{$(INCLUDE)}"\IXTENSN.HXX"\
	{$(INCLUDE)}"\OLE16.H"\
	{$(INCLUDE)}"\Ospace\config.h"\
	{$(INCLUDE)}"\Ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\Ospace\std\iosfwd"\
	{$(INCLUDE)}"\Ospace\std\istream"\
	{$(INCLUDE)}"\Ospace\std\ostream"\
	{$(INCLUDE)}"\Ospace\std\string"\
	{$(INCLUDE)}"\Ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\Ospace\stl\allocate.h"\
	{$(INCLUDE)}"\Ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\Ospace\stl\common.h"\
	{$(INCLUDE)}"\Ospace\stl\config.h"\
	{$(INCLUDE)}"\Ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\Ospace\stl\iterator.h"\
	{$(INCLUDE)}"\Ospace\stl\ops.h"\
	{$(INCLUDE)}"\Ospace\stl\pair.h"\
	{$(INCLUDE)}"\Ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\Ospace\string\basic.cc"\
	{$(INCLUDE)}"\Ospace\string\basic.h"\
	{$(INCLUDE)}"\Ospace\string\basic.ipp"\
	{$(INCLUDE)}"\Ospace\string\config.h"\
	{$(INCLUDE)}"\Ospace\string\search.cc"\
	{$(INCLUDE)}"\Ospace\string\search.h"\
	{$(INCLUDE)}"\Ospace\string\string.h"\
	{$(INCLUDE)}"\Ospace\string\traits.cc"\
	{$(INCLUDE)}"\Ospace\string\traits.h"\
	{$(INCLUDE)}"\Ospace\type\prim.h"\
	{$(INCLUDE)}"\Ospace\utility\memory.h"\
	{$(INCLUDE)}"\TRIASM.HXX"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\XTENSION.H"\
	{$(INCLUDE)}"\XTENSNM.HXX"\
	{$(INCLUDE)}"\XTENSNX.H"\
	{$(INCLUDE)}"\XTSNAUX.HXX"\
	{$(INCLUDE)}"\XTSNIMP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	

"$(INTDIR)\IMPORT.OBJ" : $(SOURCE) $(DEP_CPP_IMPOR) "$(INTDIR)"

"$(INTDIR)\IMPORT.SBR" : $(SOURCE) $(DEP_CPP_IMPOR) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Edbsimp - Win32 SmartDebug"

DEP_CPP_IMPOR=\
	".\ACTDIA.HPP"\
	".\Atkissat.h"\
	".\CWC.H"\
	".\CXSTRING.H"\
	".\EDBS.HPP"\
	".\EDBSSATZ.H"\
	".\GEOOBJ.HPP"\
	".\Import.hpp"\
	".\KOORPAAR.H"\
	".\Linie.h"\
	".\OBJPOOL.HPP"\
	".\REGELN.HPP"\
	".\SETUPDLG.HPP"\
	".\Stdafx.h"\
	".\TRIF.HPP"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTATUS.H"\
	{$(INCLUDE)}"\OLE16.H"\
	{$(INCLUDE)}"\Ospace\config.h"\
	{$(INCLUDE)}"\Ospace\std\string"\
	{$(INCLUDE)}"\Ospace\stl\config.h"\
	{$(INCLUDE)}"\Ospace\string\string.h"\
	{$(INCLUDE)}"\Ospace\string\traits.h"\
	{$(INCLUDE)}"\Ospace\type\prim.h"\
	{$(INCLUDE)}"\Ospace\utility\memory.h"\
	{$(INCLUDE)}"\Tstring"\
	

"$(INTDIR)\IMPORT.OBJ" : $(SOURCE) $(DEP_CPP_IMPOR) "$(INTDIR)"

"$(INTDIR)\IMPORT.SBR" : $(SOURCE) $(DEP_CPP_IMPOR) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\LINIE.CPP

!IF  "$(CFG)" == "Edbsimp - Win32 Release"

DEP_CPP_LINIE=\
	".\KOORPAAR.H"\
	".\Linie.h"\
	".\Stdafx.h"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\OLE16.H"\
	{$(INCLUDE)}"\Ospace\std\string"\
	{$(INCLUDE)}"\Tstring"\
	

"$(INTDIR)\LINIE.OBJ" : $(SOURCE) $(DEP_CPP_LINIE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Edbsimp - Win32 Debug"

DEP_CPP_LINIE=\
	".\Import.hpp"\
	".\KOORPAAR.H"\
	".\Linie.h"\
	".\Stdafx.h"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\ERRCODES.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\IENUMOBJ.HXX"\
	{$(INCLUDE)}"\ISTATUS.H"\
	{$(INCLUDE)}"\IXTENSN.HXX"\
	{$(INCLUDE)}"\OLE16.H"\
	{$(INCLUDE)}"\Ospace\config.h"\
	{$(INCLUDE)}"\Ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\Ospace\std\iosfwd"\
	{$(INCLUDE)}"\Ospace\std\istream"\
	{$(INCLUDE)}"\Ospace\std\ostream"\
	{$(INCLUDE)}"\Ospace\std\string"\
	{$(INCLUDE)}"\Ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\Ospace\stl\allocate.h"\
	{$(INCLUDE)}"\Ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\Ospace\stl\common.h"\
	{$(INCLUDE)}"\Ospace\stl\config.h"\
	{$(INCLUDE)}"\Ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\Ospace\stl\iterator.h"\
	{$(INCLUDE)}"\Ospace\stl\ops.h"\
	{$(INCLUDE)}"\Ospace\stl\pair.h"\
	{$(INCLUDE)}"\Ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\Ospace\string\basic.cc"\
	{$(INCLUDE)}"\Ospace\string\basic.h"\
	{$(INCLUDE)}"\Ospace\string\basic.ipp"\
	{$(INCLUDE)}"\Ospace\string\config.h"\
	{$(INCLUDE)}"\Ospace\string\search.cc"\
	{$(INCLUDE)}"\Ospace\string\search.h"\
	{$(INCLUDE)}"\Ospace\string\string.h"\
	{$(INCLUDE)}"\Ospace\string\traits.cc"\
	{$(INCLUDE)}"\Ospace\string\traits.h"\
	{$(INCLUDE)}"\Ospace\type\prim.h"\
	{$(INCLUDE)}"\Ospace\utility\memory.h"\
	{$(INCLUDE)}"\TRIASM.HXX"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\XTENSION.H"\
	{$(INCLUDE)}"\XTENSNM.HXX"\
	{$(INCLUDE)}"\XTENSNX.H"\
	{$(INCLUDE)}"\XTSNAUX.HXX"\
	{$(INCLUDE)}"\XTSNIMP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	

"$(INTDIR)\LINIE.OBJ" : $(SOURCE) $(DEP_CPP_LINIE) "$(INTDIR)"

"$(INTDIR)\LINIE.SBR" : $(SOURCE) $(DEP_CPP_LINIE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Edbsimp - Win32 SmartDebug"

DEP_CPP_LINIE=\
	".\KOORPAAR.H"\
	".\Linie.h"\
	".\Stdafx.h"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\OLE16.H"\
	{$(INCLUDE)}"\Tstring"\
	

"$(INTDIR)\LINIE.OBJ" : $(SOURCE) $(DEP_CPP_LINIE) "$(INTDIR)"

"$(INTDIR)\LINIE.SBR" : $(SOURCE) $(DEP_CPP_LINIE) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRUTIL.CXX
DEP_CPP_STRUT=\
	".\Import.hpp"\
	".\Stdafx.h"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\ERRCODES.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\IENUMOBJ.HXX"\
	{$(INCLUDE)}"\ISTATUS.H"\
	{$(INCLUDE)}"\IXTENSN.HXX"\
	{$(INCLUDE)}"\OLE16.H"\
	{$(INCLUDE)}"\Ospace\config.h"\
	{$(INCLUDE)}"\Ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\Ospace\std\iosfwd"\
	{$(INCLUDE)}"\Ospace\std\istream"\
	{$(INCLUDE)}"\Ospace\std\ostream"\
	{$(INCLUDE)}"\Ospace\std\string"\
	{$(INCLUDE)}"\Ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\Ospace\stl\allocate.h"\
	{$(INCLUDE)}"\Ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\Ospace\stl\common.h"\
	{$(INCLUDE)}"\Ospace\stl\config.h"\
	{$(INCLUDE)}"\Ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\Ospace\stl\iterator.h"\
	{$(INCLUDE)}"\Ospace\stl\ops.h"\
	{$(INCLUDE)}"\Ospace\stl\pair.h"\
	{$(INCLUDE)}"\Ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\Ospace\string\basic.cc"\
	{$(INCLUDE)}"\Ospace\string\basic.h"\
	{$(INCLUDE)}"\Ospace\string\basic.ipp"\
	{$(INCLUDE)}"\Ospace\string\config.h"\
	{$(INCLUDE)}"\Ospace\string\search.cc"\
	{$(INCLUDE)}"\Ospace\string\search.h"\
	{$(INCLUDE)}"\Ospace\string\string.h"\
	{$(INCLUDE)}"\Ospace\string\traits.cc"\
	{$(INCLUDE)}"\Ospace\string\traits.h"\
	{$(INCLUDE)}"\Ospace\type\prim.h"\
	{$(INCLUDE)}"\Ospace\utility\memory.h"\
	{$(INCLUDE)}"\TRIASM.HXX"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\XTENSION.H"\
	{$(INCLUDE)}"\XTENSNM.HXX"\
	{$(INCLUDE)}"\XTENSNX.H"\
	{$(INCLUDE)}"\XTSNAUX.HXX"\
	{$(INCLUDE)}"\XTSNIMP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	

!IF  "$(CFG)" == "Edbsimp - Win32 Release"


"$(INTDIR)\STRUTIL.OBJ" : $(SOURCE) $(DEP_CPP_STRUT) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Edbsimp - Win32 Debug"


"$(INTDIR)\STRUTIL.OBJ" : $(SOURCE) $(DEP_CPP_STRUT) "$(INTDIR)"

"$(INTDIR)\STRUTIL.SBR" : $(SOURCE) $(DEP_CPP_STRUT) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Edbsimp - Win32 SmartDebug"


"$(INTDIR)\STRUTIL.OBJ" : $(SOURCE) $(DEP_CPP_STRUT) "$(INTDIR)"

"$(INTDIR)\STRUTIL.SBR" : $(SOURCE) $(DEP_CPP_STRUT) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Cwc.cxx
DEP_CPP_CWC_C=\
	".\CWC.H"\
	".\Import.hpp"\
	".\Stdafx.h"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\ERRCODES.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\IENUMOBJ.HXX"\
	{$(INCLUDE)}"\ISTATUS.H"\
	{$(INCLUDE)}"\IXTENSN.HXX"\
	{$(INCLUDE)}"\OLE16.H"\
	{$(INCLUDE)}"\Ospace\config.h"\
	{$(INCLUDE)}"\Ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\Ospace\std\iosfwd"\
	{$(INCLUDE)}"\Ospace\std\istream"\
	{$(INCLUDE)}"\Ospace\std\ostream"\
	{$(INCLUDE)}"\Ospace\std\string"\
	{$(INCLUDE)}"\Ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\Ospace\stl\allocate.h"\
	{$(INCLUDE)}"\Ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\Ospace\stl\common.h"\
	{$(INCLUDE)}"\Ospace\stl\config.h"\
	{$(INCLUDE)}"\Ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\Ospace\stl\iterator.h"\
	{$(INCLUDE)}"\Ospace\stl\ops.h"\
	{$(INCLUDE)}"\Ospace\stl\pair.h"\
	{$(INCLUDE)}"\Ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\Ospace\string\basic.cc"\
	{$(INCLUDE)}"\Ospace\string\basic.h"\
	{$(INCLUDE)}"\Ospace\string\basic.ipp"\
	{$(INCLUDE)}"\Ospace\string\config.h"\
	{$(INCLUDE)}"\Ospace\string\search.cc"\
	{$(INCLUDE)}"\Ospace\string\search.h"\
	{$(INCLUDE)}"\Ospace\string\string.h"\
	{$(INCLUDE)}"\Ospace\string\traits.cc"\
	{$(INCLUDE)}"\Ospace\string\traits.h"\
	{$(INCLUDE)}"\Ospace\type\prim.h"\
	{$(INCLUDE)}"\Ospace\utility\memory.h"\
	{$(INCLUDE)}"\TRIASM.HXX"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\XTENSION.H"\
	{$(INCLUDE)}"\XTENSNM.HXX"\
	{$(INCLUDE)}"\XTENSNX.H"\
	{$(INCLUDE)}"\XTSNAUX.HXX"\
	{$(INCLUDE)}"\XTSNIMP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	

!IF  "$(CFG)" == "Edbsimp - Win32 Release"


"$(INTDIR)\Cwc.obj" : $(SOURCE) $(DEP_CPP_CWC_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Edbsimp - Win32 Debug"


"$(INTDIR)\Cwc.obj" : $(SOURCE) $(DEP_CPP_CWC_C) "$(INTDIR)"

"$(INTDIR)\Cwc.sbr" : $(SOURCE) $(DEP_CPP_CWC_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Edbsimp - Win32 SmartDebug"


"$(INTDIR)\Cwc.obj" : $(SOURCE) $(DEP_CPP_CWC_C) "$(INTDIR)"

"$(INTDIR)\Cwc.sbr" : $(SOURCE) $(DEP_CPP_CWC_C) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Licenz.cpp
DEP_CPP_LICEN=\
	".\Import.hpp"\
	".\Stdafx.h"\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\ERRCODES.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\IENUMOBJ.HXX"\
	{$(INCLUDE)}"\ISTATUS.H"\
	{$(INCLUDE)}"\IXTENSN.HXX"\
	{$(INCLUDE)}"\OLE16.H"\
	{$(INCLUDE)}"\Ospace\config.h"\
	{$(INCLUDE)}"\Ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\Ospace\std\iosfwd"\
	{$(INCLUDE)}"\Ospace\std\istream"\
	{$(INCLUDE)}"\Ospace\std\ostream"\
	{$(INCLUDE)}"\Ospace\std\string"\
	{$(INCLUDE)}"\Ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\Ospace\stl\allocate.h"\
	{$(INCLUDE)}"\Ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\Ospace\stl\common.h"\
	{$(INCLUDE)}"\Ospace\stl\config.h"\
	{$(INCLUDE)}"\Ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\Ospace\stl\iterator.h"\
	{$(INCLUDE)}"\Ospace\stl\ops.h"\
	{$(INCLUDE)}"\Ospace\stl\pair.h"\
	{$(INCLUDE)}"\Ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\Ospace\string\basic.cc"\
	{$(INCLUDE)}"\Ospace\string\basic.h"\
	{$(INCLUDE)}"\Ospace\string\basic.ipp"\
	{$(INCLUDE)}"\Ospace\string\config.h"\
	{$(INCLUDE)}"\Ospace\string\search.cc"\
	{$(INCLUDE)}"\Ospace\string\search.h"\
	{$(INCLUDE)}"\Ospace\string\string.h"\
	{$(INCLUDE)}"\Ospace\string\traits.cc"\
	{$(INCLUDE)}"\Ospace\string\traits.h"\
	{$(INCLUDE)}"\Ospace\type\prim.h"\
	{$(INCLUDE)}"\Ospace\utility\memory.h"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\TRIASM.HXX"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\XTENCUNK.HXX"\
	{$(INCLUDE)}"\XTENSION.H"\
	{$(INCLUDE)}"\XTENSNM.HXX"\
	{$(INCLUDE)}"\XTENSNX.H"\
	{$(INCLUDE)}"\XTSNAUX.HXX"\
	{$(INCLUDE)}"\XTSNIMP.HXX"\
	{$(INCLUDE)}"\Yxvals.h"\
	

!IF  "$(CFG)" == "Edbsimp - Win32 Release"


"$(INTDIR)\Licenz.obj" : $(SOURCE) $(DEP_CPP_LICEN) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Edbsimp - Win32 Debug"


"$(INTDIR)\Licenz.obj" : $(SOURCE) $(DEP_CPP_LICEN) "$(INTDIR)"

"$(INTDIR)\Licenz.sbr" : $(SOURCE) $(DEP_CPP_LICEN) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Edbsimp - Win32 SmartDebug"


"$(INTDIR)\Licenz.obj" : $(SOURCE) $(DEP_CPP_LICEN) "$(INTDIR)"

"$(INTDIR)\Licenz.sbr" : $(SOURCE) $(DEP_CPP_LICEN) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\edbs.ini

!IF  "$(CFG)" == "Edbsimp - Win32 Release"

!ELSEIF  "$(CFG)" == "Edbsimp - Win32 Debug"

!ELSEIF  "$(CFG)" == "Edbsimp - Win32 SmartDebug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Edbs.rc
DEP_RSC_EDBS_R=\
	".\BITMAP1.BMP"\
	".\edbs.ini"\
	".\edbs.rcv"\
	

!IF  "$(CFG)" == "Edbsimp - Win32 Release"


"$(INTDIR)\Edbs.res" : $(SOURCE) $(DEP_RSC_EDBS_R) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Edbsimp - Win32 Debug"


"$(INTDIR)\Edbs.res" : $(SOURCE) $(DEP_RSC_EDBS_R) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Edbsimp - Win32 SmartDebug"


"$(INTDIR)\Edbs.res" : $(SOURCE) $(DEP_RSC_EDBS_R) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Edbsimp.def

!IF  "$(CFG)" == "Edbsimp - Win32 Release"

!ELSEIF  "$(CFG)" == "Edbsimp - Win32 Debug"

!ELSEIF  "$(CFG)" == "Edbsimp - Win32 SmartDebug"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
