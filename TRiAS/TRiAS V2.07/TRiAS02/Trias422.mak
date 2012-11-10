# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=Trias322 - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Trias322 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Trias322 - Win32 Release" && "$(CFG)" !=\
 "Trias322 - Win32 Debug" && "$(CFG)" != "Trias322 - Win32 Pseudo Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Trias422.mak" CFG="Trias322 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Trias322 - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Trias322 - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Trias322 - Win32 Pseudo Debug" (based on\
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
# PROP Target_Last_Scanned "Trias322 - Win32 Debug"
CPP=cl.exe
MTL=mktyplib.exe
RSC=rc.exe

!IF  "$(CFG)" == "Trias322 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
TargetName=Trias322
# End Custom Macros

ALL : "$(OUTDIR)\Trias322.dll" "c:\trias.mvc\trias200.rel\Trias322.dll"\
 "..\lib32\Trias322.lib"

CLEAN : 
	-@erase "$(INTDIR)\ATTRIBS.OBJ"
	-@erase "$(INTDIR)\COMMFIL.OBJ"
	-@erase "$(INTDIR)\CTF.OBJ"
	-@erase "$(INTDIR)\DATETIME.OBJ"
	-@erase "$(INTDIR)\DB.OBJ"
	-@erase "$(INTDIR)\dbasrt02.obj"
	-@erase "$(INTDIR)\DBGETGI.OBJ"
	-@erase "$(INTDIR)\DEL.OBJ"
	-@erase "$(INTDIR)\DELGI.OBJ"
	-@erase "$(INTDIR)\DELGIF.OBJ"
	-@erase "$(INTDIR)\DELGIL.OBJ"
	-@erase "$(INTDIR)\DELGIP.OBJ"
	-@erase "$(INTDIR)\DELID.OBJ"
	-@erase "$(INTDIR)\DELKAN.OBJ"
	-@erase "$(INTDIR)\DELKANF.OBJ"
	-@erase "$(INTDIR)\DELLINK.OBJ"
	-@erase "$(INTDIR)\DELMIN.OBJ"
	-@erase "$(INTDIR)\DELREL.OBJ"
	-@erase "$(INTDIR)\DELRELKO.OBJ"
	-@erase "$(INTDIR)\DLLBIND.OBJ"
	-@erase "$(INTDIR)\DRAWRECT.OBJ"
	-@erase "$(INTDIR)\EFONT.OBJ"
	-@erase "$(INTDIR)\EPEN.OBJ"
	-@erase "$(INTDIR)\EVALKOEF.OBJ"
	-@erase "$(INTDIR)\FINDREL.OBJ"
	-@erase "$(INTDIR)\FNDGI.OBJ"
	-@erase "$(INTDIR)\FNDKA.OBJ"
	-@erase "$(INTDIR)\FNDLI.OBJ"
	-@erase "$(INTDIR)\FNDMA.OBJ"
	-@erase "$(INTDIR)\FNDPU.OBJ"
	-@erase "$(INTDIR)\FNDTXT.OBJ"
	-@erase "$(INTDIR)\FNDTXTN.OBJ"
	-@erase "$(INTDIR)\FREETEXT.OBJ"
	-@erase "$(INTDIR)\GEO_OBJ.OBJ"
	-@erase "$(INTDIR)\GEO_OBJ1.OBJ"
	-@erase "$(INTDIR)\GEOTEXT.OBJ"
	-@erase "$(INTDIR)\GERADE.OBJ"
	-@erase "$(INTDIR)\GETAPU.OBJ"
	-@erase "$(INTDIR)\GETDBLM.OBJ"
	-@erase "$(INTDIR)\GETGI.OBJ"
	-@erase "$(INTDIR)\GETGIF.OBJ"
	-@erase "$(INTDIR)\GETGIL.OBJ"
	-@erase "$(INTDIR)\GETGIP.OBJ"
	-@erase "$(INTDIR)\GETKAN.OBJ"
	-@erase "$(INTDIR)\GETLONGM.OBJ"
	-@erase "$(INTDIR)\GETMERKL.OBJ"
	-@erase "$(INTDIR)\GETMI.OBJ"
	-@erase "$(INTDIR)\GETMIT.OBJ"
	-@erase "$(INTDIR)\GETRCODE.OBJ"
	-@erase "$(INTDIR)\GETREL.OBJ"
	-@erase "$(INTDIR)\GETRIF.OBJ"
	-@erase "$(INTDIR)\GETRIG.OBJ"
	-@erase "$(INTDIR)\GETRIL.OBJ"
	-@erase "$(INTDIR)\GETRIP.OBJ"
	-@erase "$(INTDIR)\GETTEXT.OBJ"
	-@erase "$(INTDIR)\GETTEXTL.OBJ"
	-@erase "$(INTDIR)\GETTEXTN.OBJ"
	-@erase "$(INTDIR)\GIWINDOW.OBJ"
	-@erase "$(INTDIR)\HDRENTRY.OBJ"
	-@erase "$(INTDIR)\HTFUNC.OBJ"
	-@erase "$(INTDIR)\HTMANR.OBJ"
	-@erase "$(INTDIR)\IDENT.OBJ"
	-@erase "$(INTDIR)\IGLAGE.OBJ"
	-@erase "$(INTDIR)\IGPTNL.OBJ"
	-@erase "$(INTDIR)\ISALIKE.OBJ"
	-@erase "$(INTDIR)\KOMPLEX.OBJ"
	-@erase "$(INTDIR)\LIBMAIN2.OBJ"
	-@erase "$(INTDIR)\MDELKI.OBJ"
	-@erase "$(INTDIR)\MDELKM.OBJ"
	-@erase "$(INTDIR)\MDELKR.OBJ"
	-@erase "$(INTDIR)\MERKINFO.OBJ"
	-@erase "$(INTDIR)\MERKMAL.OBJ"
	-@erase "$(INTDIR)\MFIND.OBJ"
	-@erase "$(INTDIR)\MGETKM.OBJ"
	-@erase "$(INTDIR)\MGETKR.OBJ"
	-@erase "$(INTDIR)\MGETKT.OBJ"
	-@erase "$(INTDIR)\MGETL.OBJ"
	-@erase "$(INTDIR)\MGETTX.OBJ"
	-@erase "$(INTDIR)\MGETWM.OBJ"
	-@erase "$(INTDIR)\MODID.OBJ"
	-@erase "$(INTDIR)\MPUTKI.OBJ"
	-@erase "$(INTDIR)\MPUTKM.OBJ"
	-@erase "$(INTDIR)\MPUTKR.OBJ"
	-@erase "$(INTDIR)\MPUTKT.OBJ"
	-@erase "$(INTDIR)\MPUTTX.OBJ"
	-@erase "$(INTDIR)\ObjGuid.obj"
	-@erase "$(INTDIR)\OBJMTREE.OBJ"
	-@erase "$(INTDIR)\OLISTE.OBJ"
	-@erase "$(INTDIR)\OVLFOBJ.OBJ"
	-@erase "$(INTDIR)\OVLLOBJ.OBJ"
	-@erase "$(INTDIR)\OVLPOBJ.OBJ"
	-@erase "$(INTDIR)\PALETTE.OBJ"
	-@erase "$(INTDIR)\PBD.OBJ"
	-@erase "$(INTDIR)\PBDIDS.OBJ"
	-@erase "$(INTDIR)\PBDTEMP.OBJ"
	-@erase "$(INTDIR)\PROFDLL.OBJ"
	-@erase "$(INTDIR)\PUINFL.OBJ"
	-@erase "$(INTDIR)\PUTFOBJ.OBJ"
	-@erase "$(INTDIR)\PUTIDENT.OBJ"
	-@erase "$(INTDIR)\PUTKOBJ.OBJ"
	-@erase "$(INTDIR)\PUTLINK.OBJ"
	-@erase "$(INTDIR)\PUTLOBJ.OBJ"
	-@erase "$(INTDIR)\PUTMIT.OBJ"
	-@erase "$(INTDIR)\PUTPKT.OBJ"
	-@erase "$(INTDIR)\PUTPOBJ.OBJ"
	-@erase "$(INTDIR)\PUTREL.OBJ"
	-@erase "$(INTDIR)\PUTTEMPL.OBJ"
	-@erase "$(INTDIR)\PUTTOBJ.OBJ"
	-@erase "$(INTDIR)\PUTTXTC.OBJ"
	-@erase "$(INTDIR)\PUTTXTCN.OBJ"
	-@erase "$(INTDIR)\QTFUNC.OBJ"
	-@erase "$(INTDIR)\RECT.OBJ"
	-@erase "$(INTDIR)\REGISTRY.OBJ"
	-@erase "$(INTDIR)\RELATIO.OBJ"
	-@erase "$(INTDIR)\RIGIN.OBJ"
	-@erase "$(INTDIR)\RIGINFO.OBJ"
	-@erase "$(INTDIR)\RIGKP.OBJ"
	-@erase "$(INTDIR)\STINFL.OBJ"
	-@erase "$(INTDIR)\Strings.obj"
	-@erase "$(INTDIR)\STRUTIL.OBJ"
	-@erase "$(INTDIR)\TRIAS02P.OBJ"
	-@erase "$(INTDIR)\Trias322.res"
	-@erase "$(INTDIR)\Trias422.pch"
	-@erase "$(INTDIR)\VISERROR.OBJ"
	-@erase "$(INTDIR)\VISINFO.OBJ"
	-@erase "$(OUTDIR)\Trias322.dll"
	-@erase "$(OUTDIR)\Trias322.exp"
	-@erase "$(OUTDIR)\Trias322.lib"
	-@erase "..\lib32\Trias322.lib"
	-@erase "c:\trias.mvc\trias200.rel\Trias322.dll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

.\WinRel\TRIAS322.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "DLL" /D "__CV__" /D "__TRIAS02DLL__" /D "OS_NO_ALLOCATORS" /D "OS_NO_STREAM_SUPPORT" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "OS_ALTERNATIVE_STRING_NAMES" /D "__ATL_USED__" /D "__ATL_11_USED__" /D "QI_EXCEPTION" /Yu"trias02p.hxx" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "STRICT" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "DLL" /D "__CV__" /D\
 "__TRIAS02DLL__" /D "OS_NO_ALLOCATORS" /D "OS_NO_STREAM_SUPPORT" /D "OS_WIN_95"\
 /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "OS_ALTERNATIVE_STRING_NAMES" /D\
 "__ATL_USED__" /D "__ATL_11_USED__" /D "QI_EXCEPTION"\
 /Fp"$(INTDIR)/Trias422.pch" /Yu"trias02p.hxx" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/Trias322.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Trias422.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ospace2r.lib trias321.lib cont32r.lib tfrmwrkl.lib tfrmwork.lib stdcppr.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /stub:"obj32\rights.exe" /out:"Release/Trias322.dll" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none /debug
LINK32_FLAGS=ospace2r.lib trias321.lib cont32r.lib tfrmwrkl.lib tfrmwork.lib\
 stdcppr.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)/Trias322.pdb"\
 /machine:I386 /def:".\obj32\TRIAS322.DEF" /stub:"obj32\rights.exe"\
 /out:"$(OUTDIR)/Trias322.dll" /implib:"$(OUTDIR)/Trias322.lib"\
 /SUBSYSTEM:windows,4.0 
DEF_FILE= \
	".\obj32\TRIAS322.DEF"
LINK32_OBJS= \
	"$(INTDIR)\ATTRIBS.OBJ" \
	"$(INTDIR)\COMMFIL.OBJ" \
	"$(INTDIR)\CTF.OBJ" \
	"$(INTDIR)\DATETIME.OBJ" \
	"$(INTDIR)\DB.OBJ" \
	"$(INTDIR)\dbasrt02.obj" \
	"$(INTDIR)\DBGETGI.OBJ" \
	"$(INTDIR)\DEL.OBJ" \
	"$(INTDIR)\DELGI.OBJ" \
	"$(INTDIR)\DELGIF.OBJ" \
	"$(INTDIR)\DELGIL.OBJ" \
	"$(INTDIR)\DELGIP.OBJ" \
	"$(INTDIR)\DELID.OBJ" \
	"$(INTDIR)\DELKAN.OBJ" \
	"$(INTDIR)\DELKANF.OBJ" \
	"$(INTDIR)\DELLINK.OBJ" \
	"$(INTDIR)\DELMIN.OBJ" \
	"$(INTDIR)\DELREL.OBJ" \
	"$(INTDIR)\DELRELKO.OBJ" \
	"$(INTDIR)\DLLBIND.OBJ" \
	"$(INTDIR)\DRAWRECT.OBJ" \
	"$(INTDIR)\EFONT.OBJ" \
	"$(INTDIR)\EPEN.OBJ" \
	"$(INTDIR)\EVALKOEF.OBJ" \
	"$(INTDIR)\FINDREL.OBJ" \
	"$(INTDIR)\FNDGI.OBJ" \
	"$(INTDIR)\FNDKA.OBJ" \
	"$(INTDIR)\FNDLI.OBJ" \
	"$(INTDIR)\FNDMA.OBJ" \
	"$(INTDIR)\FNDPU.OBJ" \
	"$(INTDIR)\FNDTXT.OBJ" \
	"$(INTDIR)\FNDTXTN.OBJ" \
	"$(INTDIR)\FREETEXT.OBJ" \
	"$(INTDIR)\GEO_OBJ.OBJ" \
	"$(INTDIR)\GEO_OBJ1.OBJ" \
	"$(INTDIR)\GEOTEXT.OBJ" \
	"$(INTDIR)\GERADE.OBJ" \
	"$(INTDIR)\GETAPU.OBJ" \
	"$(INTDIR)\GETDBLM.OBJ" \
	"$(INTDIR)\GETGI.OBJ" \
	"$(INTDIR)\GETGIF.OBJ" \
	"$(INTDIR)\GETGIL.OBJ" \
	"$(INTDIR)\GETGIP.OBJ" \
	"$(INTDIR)\GETKAN.OBJ" \
	"$(INTDIR)\GETLONGM.OBJ" \
	"$(INTDIR)\GETMERKL.OBJ" \
	"$(INTDIR)\GETMI.OBJ" \
	"$(INTDIR)\GETMIT.OBJ" \
	"$(INTDIR)\GETRCODE.OBJ" \
	"$(INTDIR)\GETREL.OBJ" \
	"$(INTDIR)\GETRIF.OBJ" \
	"$(INTDIR)\GETRIG.OBJ" \
	"$(INTDIR)\GETRIL.OBJ" \
	"$(INTDIR)\GETRIP.OBJ" \
	"$(INTDIR)\GETTEXT.OBJ" \
	"$(INTDIR)\GETTEXTL.OBJ" \
	"$(INTDIR)\GETTEXTN.OBJ" \
	"$(INTDIR)\GIWINDOW.OBJ" \
	"$(INTDIR)\HDRENTRY.OBJ" \
	"$(INTDIR)\HTFUNC.OBJ" \
	"$(INTDIR)\HTMANR.OBJ" \
	"$(INTDIR)\IDENT.OBJ" \
	"$(INTDIR)\IGLAGE.OBJ" \
	"$(INTDIR)\IGPTNL.OBJ" \
	"$(INTDIR)\ISALIKE.OBJ" \
	"$(INTDIR)\KOMPLEX.OBJ" \
	"$(INTDIR)\LIBMAIN2.OBJ" \
	"$(INTDIR)\MDELKI.OBJ" \
	"$(INTDIR)\MDELKM.OBJ" \
	"$(INTDIR)\MDELKR.OBJ" \
	"$(INTDIR)\MERKINFO.OBJ" \
	"$(INTDIR)\MERKMAL.OBJ" \
	"$(INTDIR)\MFIND.OBJ" \
	"$(INTDIR)\MGETKM.OBJ" \
	"$(INTDIR)\MGETKR.OBJ" \
	"$(INTDIR)\MGETKT.OBJ" \
	"$(INTDIR)\MGETL.OBJ" \
	"$(INTDIR)\MGETTX.OBJ" \
	"$(INTDIR)\MGETWM.OBJ" \
	"$(INTDIR)\MODID.OBJ" \
	"$(INTDIR)\MPUTKI.OBJ" \
	"$(INTDIR)\MPUTKM.OBJ" \
	"$(INTDIR)\MPUTKR.OBJ" \
	"$(INTDIR)\MPUTKT.OBJ" \
	"$(INTDIR)\MPUTTX.OBJ" \
	"$(INTDIR)\ObjGuid.obj" \
	"$(INTDIR)\OBJMTREE.OBJ" \
	"$(INTDIR)\OLISTE.OBJ" \
	"$(INTDIR)\OVLFOBJ.OBJ" \
	"$(INTDIR)\OVLLOBJ.OBJ" \
	"$(INTDIR)\OVLPOBJ.OBJ" \
	"$(INTDIR)\PALETTE.OBJ" \
	"$(INTDIR)\PBD.OBJ" \
	"$(INTDIR)\PBDIDS.OBJ" \
	"$(INTDIR)\PBDTEMP.OBJ" \
	"$(INTDIR)\PROFDLL.OBJ" \
	"$(INTDIR)\PUINFL.OBJ" \
	"$(INTDIR)\PUTFOBJ.OBJ" \
	"$(INTDIR)\PUTIDENT.OBJ" \
	"$(INTDIR)\PUTKOBJ.OBJ" \
	"$(INTDIR)\PUTLINK.OBJ" \
	"$(INTDIR)\PUTLOBJ.OBJ" \
	"$(INTDIR)\PUTMIT.OBJ" \
	"$(INTDIR)\PUTPKT.OBJ" \
	"$(INTDIR)\PUTPOBJ.OBJ" \
	"$(INTDIR)\PUTREL.OBJ" \
	"$(INTDIR)\PUTTEMPL.OBJ" \
	"$(INTDIR)\PUTTOBJ.OBJ" \
	"$(INTDIR)\PUTTXTC.OBJ" \
	"$(INTDIR)\PUTTXTCN.OBJ" \
	"$(INTDIR)\QTFUNC.OBJ" \
	"$(INTDIR)\RECT.OBJ" \
	"$(INTDIR)\REGISTRY.OBJ" \
	"$(INTDIR)\RELATIO.OBJ" \
	"$(INTDIR)\RIGIN.OBJ" \
	"$(INTDIR)\RIGINFO.OBJ" \
	"$(INTDIR)\RIGKP.OBJ" \
	"$(INTDIR)\STINFL.OBJ" \
	"$(INTDIR)\Strings.obj" \
	"$(INTDIR)\STRUTIL.OBJ" \
	"$(INTDIR)\TRIAS02P.OBJ" \
	"$(INTDIR)\Trias322.res" \
	"$(INTDIR)\VISERROR.OBJ" \
	"$(INTDIR)\VISINFO.OBJ"

"$(OUTDIR)\Trias322.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying Target to Destination ...
OutDir=.\Release
TargetPath=.\Release\Trias322.dll
TargetName=Trias322
InputPath=.\Release\Trias322.dll
SOURCE=$(InputPath)

BuildCmds= \
	rem copy "$(TargetPath)" c:\trias.mvc\trias200.rel \
	rem copy "$(OutDir)\$(TargetName).lib" e:\triasdev.mvc\lib32 \
	

"c:\trias.mvc\trias200.rel\$(TargetName).dll" : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
   $(BuildCmds)

"\triasdev.mvc\lib32\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug4"
# PROP Intermediate_Dir "Debug4"
OUTDIR=.\Debug4
INTDIR=.\Debug4
# Begin Custom Macros
TargetName=trias32d
# End Custom Macros

ALL : "$(OUTDIR)\trias32d.dll" "$(OUTDIR)\Trias422.bsc"\
 "c:\trias.mvc\trias200\trias32d.dll" "..\lib32\trias32d.lib"

CLEAN : 
	-@erase "$(INTDIR)\ATTRIBS.OBJ"
	-@erase "$(INTDIR)\ATTRIBS.SBR"
	-@erase "$(INTDIR)\COMMFIL.OBJ"
	-@erase "$(INTDIR)\COMMFIL.SBR"
	-@erase "$(INTDIR)\CTF.OBJ"
	-@erase "$(INTDIR)\CTF.SBR"
	-@erase "$(INTDIR)\DATETIME.OBJ"
	-@erase "$(INTDIR)\DATETIME.SBR"
	-@erase "$(INTDIR)\DB.OBJ"
	-@erase "$(INTDIR)\DB.SBR"
	-@erase "$(INTDIR)\dbasrt02.obj"
	-@erase "$(INTDIR)\dbasrt02.sbr"
	-@erase "$(INTDIR)\DBGETGI.OBJ"
	-@erase "$(INTDIR)\DBGETGI.SBR"
	-@erase "$(INTDIR)\DEL.OBJ"
	-@erase "$(INTDIR)\DEL.SBR"
	-@erase "$(INTDIR)\DELGI.OBJ"
	-@erase "$(INTDIR)\DELGI.SBR"
	-@erase "$(INTDIR)\DELGIF.OBJ"
	-@erase "$(INTDIR)\DELGIF.SBR"
	-@erase "$(INTDIR)\DELGIL.OBJ"
	-@erase "$(INTDIR)\DELGIL.SBR"
	-@erase "$(INTDIR)\DELGIP.OBJ"
	-@erase "$(INTDIR)\DELGIP.SBR"
	-@erase "$(INTDIR)\DELID.OBJ"
	-@erase "$(INTDIR)\DELID.SBR"
	-@erase "$(INTDIR)\DELKAN.OBJ"
	-@erase "$(INTDIR)\DELKAN.SBR"
	-@erase "$(INTDIR)\DELKANF.OBJ"
	-@erase "$(INTDIR)\DELKANF.SBR"
	-@erase "$(INTDIR)\DELLINK.OBJ"
	-@erase "$(INTDIR)\DELLINK.SBR"
	-@erase "$(INTDIR)\DELMIN.OBJ"
	-@erase "$(INTDIR)\DELMIN.SBR"
	-@erase "$(INTDIR)\DELREL.OBJ"
	-@erase "$(INTDIR)\DELREL.SBR"
	-@erase "$(INTDIR)\DELRELKO.OBJ"
	-@erase "$(INTDIR)\DELRELKO.SBR"
	-@erase "$(INTDIR)\DLLBIND.OBJ"
	-@erase "$(INTDIR)\DLLBIND.SBR"
	-@erase "$(INTDIR)\DRAWRECT.OBJ"
	-@erase "$(INTDIR)\DRAWRECT.SBR"
	-@erase "$(INTDIR)\EFONT.OBJ"
	-@erase "$(INTDIR)\EFONT.SBR"
	-@erase "$(INTDIR)\EPEN.OBJ"
	-@erase "$(INTDIR)\EPEN.SBR"
	-@erase "$(INTDIR)\EVALKOEF.OBJ"
	-@erase "$(INTDIR)\EVALKOEF.SBR"
	-@erase "$(INTDIR)\FINDREL.OBJ"
	-@erase "$(INTDIR)\FINDREL.SBR"
	-@erase "$(INTDIR)\FNDGI.OBJ"
	-@erase "$(INTDIR)\FNDGI.SBR"
	-@erase "$(INTDIR)\FNDKA.OBJ"
	-@erase "$(INTDIR)\FNDKA.SBR"
	-@erase "$(INTDIR)\FNDLI.OBJ"
	-@erase "$(INTDIR)\FNDLI.SBR"
	-@erase "$(INTDIR)\FNDMA.OBJ"
	-@erase "$(INTDIR)\FNDMA.SBR"
	-@erase "$(INTDIR)\FNDPU.OBJ"
	-@erase "$(INTDIR)\FNDPU.SBR"
	-@erase "$(INTDIR)\FNDTXT.OBJ"
	-@erase "$(INTDIR)\FNDTXT.SBR"
	-@erase "$(INTDIR)\FNDTXTN.OBJ"
	-@erase "$(INTDIR)\FNDTXTN.SBR"
	-@erase "$(INTDIR)\FREETEXT.OBJ"
	-@erase "$(INTDIR)\FREETEXT.SBR"
	-@erase "$(INTDIR)\GEO_OBJ.OBJ"
	-@erase "$(INTDIR)\GEO_OBJ.SBR"
	-@erase "$(INTDIR)\GEO_OBJ1.OBJ"
	-@erase "$(INTDIR)\GEO_OBJ1.SBR"
	-@erase "$(INTDIR)\GEOTEXT.OBJ"
	-@erase "$(INTDIR)\GEOTEXT.SBR"
	-@erase "$(INTDIR)\GERADE.OBJ"
	-@erase "$(INTDIR)\GERADE.SBR"
	-@erase "$(INTDIR)\GETAPU.OBJ"
	-@erase "$(INTDIR)\GETAPU.SBR"
	-@erase "$(INTDIR)\GETDBLM.OBJ"
	-@erase "$(INTDIR)\GETDBLM.SBR"
	-@erase "$(INTDIR)\GETGI.OBJ"
	-@erase "$(INTDIR)\GETGI.SBR"
	-@erase "$(INTDIR)\GETGIF.OBJ"
	-@erase "$(INTDIR)\GETGIF.SBR"
	-@erase "$(INTDIR)\GETGIL.OBJ"
	-@erase "$(INTDIR)\GETGIL.SBR"
	-@erase "$(INTDIR)\GETGIP.OBJ"
	-@erase "$(INTDIR)\GETGIP.SBR"
	-@erase "$(INTDIR)\GETKAN.OBJ"
	-@erase "$(INTDIR)\GETKAN.SBR"
	-@erase "$(INTDIR)\GETLONGM.OBJ"
	-@erase "$(INTDIR)\GETLONGM.SBR"
	-@erase "$(INTDIR)\GETMERKL.OBJ"
	-@erase "$(INTDIR)\GETMERKL.SBR"
	-@erase "$(INTDIR)\GETMI.OBJ"
	-@erase "$(INTDIR)\GETMI.SBR"
	-@erase "$(INTDIR)\GETMIT.OBJ"
	-@erase "$(INTDIR)\GETMIT.SBR"
	-@erase "$(INTDIR)\GETRCODE.OBJ"
	-@erase "$(INTDIR)\GETRCODE.SBR"
	-@erase "$(INTDIR)\GETREL.OBJ"
	-@erase "$(INTDIR)\GETREL.SBR"
	-@erase "$(INTDIR)\GETRIF.OBJ"
	-@erase "$(INTDIR)\GETRIF.SBR"
	-@erase "$(INTDIR)\GETRIG.OBJ"
	-@erase "$(INTDIR)\GETRIG.SBR"
	-@erase "$(INTDIR)\GETRIL.OBJ"
	-@erase "$(INTDIR)\GETRIL.SBR"
	-@erase "$(INTDIR)\GETRIP.OBJ"
	-@erase "$(INTDIR)\GETRIP.SBR"
	-@erase "$(INTDIR)\GETTEXT.OBJ"
	-@erase "$(INTDIR)\GETTEXT.SBR"
	-@erase "$(INTDIR)\GETTEXTL.OBJ"
	-@erase "$(INTDIR)\GETTEXTL.SBR"
	-@erase "$(INTDIR)\GETTEXTN.OBJ"
	-@erase "$(INTDIR)\GETTEXTN.SBR"
	-@erase "$(INTDIR)\GIWINDOW.OBJ"
	-@erase "$(INTDIR)\GIWINDOW.SBR"
	-@erase "$(INTDIR)\HDRENTRY.OBJ"
	-@erase "$(INTDIR)\HDRENTRY.SBR"
	-@erase "$(INTDIR)\HTFUNC.OBJ"
	-@erase "$(INTDIR)\HTFUNC.SBR"
	-@erase "$(INTDIR)\HTMANR.OBJ"
	-@erase "$(INTDIR)\HTMANR.SBR"
	-@erase "$(INTDIR)\IDENT.OBJ"
	-@erase "$(INTDIR)\IDENT.SBR"
	-@erase "$(INTDIR)\IGLAGE.OBJ"
	-@erase "$(INTDIR)\IGLAGE.SBR"
	-@erase "$(INTDIR)\IGPTNL.OBJ"
	-@erase "$(INTDIR)\IGPTNL.SBR"
	-@erase "$(INTDIR)\ISALIKE.OBJ"
	-@erase "$(INTDIR)\ISALIKE.SBR"
	-@erase "$(INTDIR)\KOMPLEX.OBJ"
	-@erase "$(INTDIR)\KOMPLEX.SBR"
	-@erase "$(INTDIR)\KONS.OBJ"
	-@erase "$(INTDIR)\KONS.SBR"
	-@erase "$(INTDIR)\KONSOBJ.OBJ"
	-@erase "$(INTDIR)\KONSOBJ.SBR"
	-@erase "$(INTDIR)\KONSSATZ.OBJ"
	-@erase "$(INTDIR)\KONSSATZ.SBR"
	-@erase "$(INTDIR)\KONSUTIL.OBJ"
	-@erase "$(INTDIR)\KONSUTIL.SBR"
	-@erase "$(INTDIR)\LIBMAIN2.OBJ"
	-@erase "$(INTDIR)\LIBMAIN2.SBR"
	-@erase "$(INTDIR)\MDELKI.OBJ"
	-@erase "$(INTDIR)\MDELKI.SBR"
	-@erase "$(INTDIR)\MDELKM.OBJ"
	-@erase "$(INTDIR)\MDELKM.SBR"
	-@erase "$(INTDIR)\MDELKR.OBJ"
	-@erase "$(INTDIR)\MDELKR.SBR"
	-@erase "$(INTDIR)\MERKINFO.OBJ"
	-@erase "$(INTDIR)\MERKINFO.SBR"
	-@erase "$(INTDIR)\MERKMAL.OBJ"
	-@erase "$(INTDIR)\MERKMAL.SBR"
	-@erase "$(INTDIR)\MFIND.OBJ"
	-@erase "$(INTDIR)\MFIND.SBR"
	-@erase "$(INTDIR)\MGETKM.OBJ"
	-@erase "$(INTDIR)\MGETKM.SBR"
	-@erase "$(INTDIR)\MGETKR.OBJ"
	-@erase "$(INTDIR)\MGETKR.SBR"
	-@erase "$(INTDIR)\MGETKT.OBJ"
	-@erase "$(INTDIR)\MGETKT.SBR"
	-@erase "$(INTDIR)\MGETL.OBJ"
	-@erase "$(INTDIR)\MGETL.SBR"
	-@erase "$(INTDIR)\MGETTX.OBJ"
	-@erase "$(INTDIR)\MGETTX.SBR"
	-@erase "$(INTDIR)\MGETWM.OBJ"
	-@erase "$(INTDIR)\MGETWM.SBR"
	-@erase "$(INTDIR)\MODID.OBJ"
	-@erase "$(INTDIR)\MODID.SBR"
	-@erase "$(INTDIR)\MPUTKI.OBJ"
	-@erase "$(INTDIR)\MPUTKI.SBR"
	-@erase "$(INTDIR)\MPUTKM.OBJ"
	-@erase "$(INTDIR)\MPUTKM.SBR"
	-@erase "$(INTDIR)\MPUTKR.OBJ"
	-@erase "$(INTDIR)\MPUTKR.SBR"
	-@erase "$(INTDIR)\MPUTKT.OBJ"
	-@erase "$(INTDIR)\MPUTKT.SBR"
	-@erase "$(INTDIR)\MPUTTX.OBJ"
	-@erase "$(INTDIR)\MPUTTX.SBR"
	-@erase "$(INTDIR)\ObjGuid.obj"
	-@erase "$(INTDIR)\ObjGuid.sbr"
	-@erase "$(INTDIR)\OBJMTREE.OBJ"
	-@erase "$(INTDIR)\OBJMTREE.SBR"
	-@erase "$(INTDIR)\OLISTE.OBJ"
	-@erase "$(INTDIR)\OLISTE.SBR"
	-@erase "$(INTDIR)\OVLFOBJ.OBJ"
	-@erase "$(INTDIR)\OVLFOBJ.SBR"
	-@erase "$(INTDIR)\OVLLOBJ.OBJ"
	-@erase "$(INTDIR)\OVLLOBJ.SBR"
	-@erase "$(INTDIR)\OVLPOBJ.OBJ"
	-@erase "$(INTDIR)\OVLPOBJ.SBR"
	-@erase "$(INTDIR)\PALETTE.OBJ"
	-@erase "$(INTDIR)\PALETTE.SBR"
	-@erase "$(INTDIR)\PBD.OBJ"
	-@erase "$(INTDIR)\PBD.SBR"
	-@erase "$(INTDIR)\PBDIDS.OBJ"
	-@erase "$(INTDIR)\PBDIDS.SBR"
	-@erase "$(INTDIR)\PBDTEMP.OBJ"
	-@erase "$(INTDIR)\PBDTEMP.SBR"
	-@erase "$(INTDIR)\PROFDLL.OBJ"
	-@erase "$(INTDIR)\PROFDLL.SBR"
	-@erase "$(INTDIR)\PUINFL.OBJ"
	-@erase "$(INTDIR)\PUINFL.SBR"
	-@erase "$(INTDIR)\PUTFOBJ.OBJ"
	-@erase "$(INTDIR)\PUTFOBJ.SBR"
	-@erase "$(INTDIR)\PUTIDENT.OBJ"
	-@erase "$(INTDIR)\PUTIDENT.SBR"
	-@erase "$(INTDIR)\PUTKOBJ.OBJ"
	-@erase "$(INTDIR)\PUTKOBJ.SBR"
	-@erase "$(INTDIR)\PUTLINK.OBJ"
	-@erase "$(INTDIR)\PUTLINK.SBR"
	-@erase "$(INTDIR)\PUTLOBJ.OBJ"
	-@erase "$(INTDIR)\PUTLOBJ.SBR"
	-@erase "$(INTDIR)\PUTMIT.OBJ"
	-@erase "$(INTDIR)\PUTMIT.SBR"
	-@erase "$(INTDIR)\PUTPKT.OBJ"
	-@erase "$(INTDIR)\PUTPKT.SBR"
	-@erase "$(INTDIR)\PUTPOBJ.OBJ"
	-@erase "$(INTDIR)\PUTPOBJ.SBR"
	-@erase "$(INTDIR)\PUTREL.OBJ"
	-@erase "$(INTDIR)\PUTREL.SBR"
	-@erase "$(INTDIR)\PUTTEMPL.OBJ"
	-@erase "$(INTDIR)\PUTTEMPL.SBR"
	-@erase "$(INTDIR)\PUTTOBJ.OBJ"
	-@erase "$(INTDIR)\PUTTOBJ.SBR"
	-@erase "$(INTDIR)\PUTTXTC.OBJ"
	-@erase "$(INTDIR)\PUTTXTC.SBR"
	-@erase "$(INTDIR)\PUTTXTCN.OBJ"
	-@erase "$(INTDIR)\PUTTXTCN.SBR"
	-@erase "$(INTDIR)\QTFUNC.OBJ"
	-@erase "$(INTDIR)\QTFUNC.SBR"
	-@erase "$(INTDIR)\RECT.OBJ"
	-@erase "$(INTDIR)\RECT.SBR"
	-@erase "$(INTDIR)\REGISTRY.OBJ"
	-@erase "$(INTDIR)\REGISTRY.SBR"
	-@erase "$(INTDIR)\RELATIO.OBJ"
	-@erase "$(INTDIR)\RELATIO.SBR"
	-@erase "$(INTDIR)\RIGIN.OBJ"
	-@erase "$(INTDIR)\RIGIN.SBR"
	-@erase "$(INTDIR)\RIGINFO.OBJ"
	-@erase "$(INTDIR)\RIGINFO.SBR"
	-@erase "$(INTDIR)\RIGKP.OBJ"
	-@erase "$(INTDIR)\RIGKP.SBR"
	-@erase "$(INTDIR)\STINFL.OBJ"
	-@erase "$(INTDIR)\STINFL.SBR"
	-@erase "$(INTDIR)\Strings.obj"
	-@erase "$(INTDIR)\Strings.sbr"
	-@erase "$(INTDIR)\STRUTIL.OBJ"
	-@erase "$(INTDIR)\STRUTIL.SBR"
	-@erase "$(INTDIR)\TRIAS02P.OBJ"
	-@erase "$(INTDIR)\TRIAS02P.SBR"
	-@erase "$(INTDIR)\Trias322.res"
	-@erase "$(INTDIR)\trias322d.idb"
	-@erase "$(INTDIR)\trias322d.pch"
	-@erase "$(INTDIR)\trias322d.pdb"
	-@erase "$(INTDIR)\VISERROR.OBJ"
	-@erase "$(INTDIR)\VISERROR.SBR"
	-@erase "$(INTDIR)\VISINFO.OBJ"
	-@erase "$(INTDIR)\VISINFO.SBR"
	-@erase "$(OUTDIR)\trias32d.dll"
	-@erase "$(OUTDIR)\trias32d.exp"
	-@erase "$(OUTDIR)\trias32d.ilk"
	-@erase "$(OUTDIR)\trias32d.lib"
	-@erase "$(OUTDIR)\Trias422.bsc"
	-@erase "..\lib32\trias32d.lib"
	-@erase "c:\trias.mvc\trias200\trias32d.dll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

.\WinDebug\TRIAS322.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "DLL" /D "__CV__" /D "__TRIAS02DLL__" /D "OS_NO_ALLOCATORS" /D "OS_NO_STREAM_SUPPORT" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "OS_ALTERNATIVE_STRING_NAMES" /D "__ATL_USED__" /D "__ATL_11_USED__" /D "QI_EXCEPTION" /FR /Fp"Debug4/trias322d.pch" /Yu"trias02p.hxx" /Fd"Debug4/trias322d.pdb" /c
CPP_PROJ=/nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "DLL" /D\
 "__CV__" /D "__TRIAS02DLL__" /D "OS_NO_ALLOCATORS" /D "OS_NO_STREAM_SUPPORT" /D\
 "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D\
 "OS_ALTERNATIVE_STRING_NAMES" /D "__ATL_USED__" /D "__ATL_11_USED__" /D\
 "QI_EXCEPTION" /FR"$(INTDIR)/" /Fp"$(INTDIR)/trias322d.pch" /Yu"trias02p.hxx"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/trias322d.pdb" /c 
CPP_OBJS=.\Debug4/
CPP_SBRS=.\Debug4/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/Trias322.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Trias422.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\ATTRIBS.SBR" \
	"$(INTDIR)\COMMFIL.SBR" \
	"$(INTDIR)\CTF.SBR" \
	"$(INTDIR)\DATETIME.SBR" \
	"$(INTDIR)\DB.SBR" \
	"$(INTDIR)\dbasrt02.sbr" \
	"$(INTDIR)\DBGETGI.SBR" \
	"$(INTDIR)\DEL.SBR" \
	"$(INTDIR)\DELGI.SBR" \
	"$(INTDIR)\DELGIF.SBR" \
	"$(INTDIR)\DELGIL.SBR" \
	"$(INTDIR)\DELGIP.SBR" \
	"$(INTDIR)\DELID.SBR" \
	"$(INTDIR)\DELKAN.SBR" \
	"$(INTDIR)\DELKANF.SBR" \
	"$(INTDIR)\DELLINK.SBR" \
	"$(INTDIR)\DELMIN.SBR" \
	"$(INTDIR)\DELREL.SBR" \
	"$(INTDIR)\DELRELKO.SBR" \
	"$(INTDIR)\DLLBIND.SBR" \
	"$(INTDIR)\DRAWRECT.SBR" \
	"$(INTDIR)\EFONT.SBR" \
	"$(INTDIR)\EPEN.SBR" \
	"$(INTDIR)\EVALKOEF.SBR" \
	"$(INTDIR)\FINDREL.SBR" \
	"$(INTDIR)\FNDGI.SBR" \
	"$(INTDIR)\FNDKA.SBR" \
	"$(INTDIR)\FNDLI.SBR" \
	"$(INTDIR)\FNDMA.SBR" \
	"$(INTDIR)\FNDPU.SBR" \
	"$(INTDIR)\FNDTXT.SBR" \
	"$(INTDIR)\FNDTXTN.SBR" \
	"$(INTDIR)\FREETEXT.SBR" \
	"$(INTDIR)\GEO_OBJ.SBR" \
	"$(INTDIR)\GEO_OBJ1.SBR" \
	"$(INTDIR)\GEOTEXT.SBR" \
	"$(INTDIR)\GERADE.SBR" \
	"$(INTDIR)\GETAPU.SBR" \
	"$(INTDIR)\GETDBLM.SBR" \
	"$(INTDIR)\GETGI.SBR" \
	"$(INTDIR)\GETGIF.SBR" \
	"$(INTDIR)\GETGIL.SBR" \
	"$(INTDIR)\GETGIP.SBR" \
	"$(INTDIR)\GETKAN.SBR" \
	"$(INTDIR)\GETLONGM.SBR" \
	"$(INTDIR)\GETMERKL.SBR" \
	"$(INTDIR)\GETMI.SBR" \
	"$(INTDIR)\GETMIT.SBR" \
	"$(INTDIR)\GETRCODE.SBR" \
	"$(INTDIR)\GETREL.SBR" \
	"$(INTDIR)\GETRIF.SBR" \
	"$(INTDIR)\GETRIG.SBR" \
	"$(INTDIR)\GETRIL.SBR" \
	"$(INTDIR)\GETRIP.SBR" \
	"$(INTDIR)\GETTEXT.SBR" \
	"$(INTDIR)\GETTEXTL.SBR" \
	"$(INTDIR)\GETTEXTN.SBR" \
	"$(INTDIR)\GIWINDOW.SBR" \
	"$(INTDIR)\HDRENTRY.SBR" \
	"$(INTDIR)\HTFUNC.SBR" \
	"$(INTDIR)\HTMANR.SBR" \
	"$(INTDIR)\IDENT.SBR" \
	"$(INTDIR)\IGLAGE.SBR" \
	"$(INTDIR)\IGPTNL.SBR" \
	"$(INTDIR)\ISALIKE.SBR" \
	"$(INTDIR)\KOMPLEX.SBR" \
	"$(INTDIR)\KONS.SBR" \
	"$(INTDIR)\KONSOBJ.SBR" \
	"$(INTDIR)\KONSSATZ.SBR" \
	"$(INTDIR)\KONSUTIL.SBR" \
	"$(INTDIR)\LIBMAIN2.SBR" \
	"$(INTDIR)\MDELKI.SBR" \
	"$(INTDIR)\MDELKM.SBR" \
	"$(INTDIR)\MDELKR.SBR" \
	"$(INTDIR)\MERKINFO.SBR" \
	"$(INTDIR)\MERKMAL.SBR" \
	"$(INTDIR)\MFIND.SBR" \
	"$(INTDIR)\MGETKM.SBR" \
	"$(INTDIR)\MGETKR.SBR" \
	"$(INTDIR)\MGETKT.SBR" \
	"$(INTDIR)\MGETL.SBR" \
	"$(INTDIR)\MGETTX.SBR" \
	"$(INTDIR)\MGETWM.SBR" \
	"$(INTDIR)\MODID.SBR" \
	"$(INTDIR)\MPUTKI.SBR" \
	"$(INTDIR)\MPUTKM.SBR" \
	"$(INTDIR)\MPUTKR.SBR" \
	"$(INTDIR)\MPUTKT.SBR" \
	"$(INTDIR)\MPUTTX.SBR" \
	"$(INTDIR)\ObjGuid.sbr" \
	"$(INTDIR)\OBJMTREE.SBR" \
	"$(INTDIR)\OLISTE.SBR" \
	"$(INTDIR)\OVLFOBJ.SBR" \
	"$(INTDIR)\OVLLOBJ.SBR" \
	"$(INTDIR)\OVLPOBJ.SBR" \
	"$(INTDIR)\PALETTE.SBR" \
	"$(INTDIR)\PBD.SBR" \
	"$(INTDIR)\PBDIDS.SBR" \
	"$(INTDIR)\PBDTEMP.SBR" \
	"$(INTDIR)\PROFDLL.SBR" \
	"$(INTDIR)\PUINFL.SBR" \
	"$(INTDIR)\PUTFOBJ.SBR" \
	"$(INTDIR)\PUTIDENT.SBR" \
	"$(INTDIR)\PUTKOBJ.SBR" \
	"$(INTDIR)\PUTLINK.SBR" \
	"$(INTDIR)\PUTLOBJ.SBR" \
	"$(INTDIR)\PUTMIT.SBR" \
	"$(INTDIR)\PUTPKT.SBR" \
	"$(INTDIR)\PUTPOBJ.SBR" \
	"$(INTDIR)\PUTREL.SBR" \
	"$(INTDIR)\PUTTEMPL.SBR" \
	"$(INTDIR)\PUTTOBJ.SBR" \
	"$(INTDIR)\PUTTXTC.SBR" \
	"$(INTDIR)\PUTTXTCN.SBR" \
	"$(INTDIR)\QTFUNC.SBR" \
	"$(INTDIR)\RECT.SBR" \
	"$(INTDIR)\REGISTRY.SBR" \
	"$(INTDIR)\RELATIO.SBR" \
	"$(INTDIR)\RIGIN.SBR" \
	"$(INTDIR)\RIGINFO.SBR" \
	"$(INTDIR)\RIGKP.SBR" \
	"$(INTDIR)\STINFL.SBR" \
	"$(INTDIR)\Strings.sbr" \
	"$(INTDIR)\STRUTIL.SBR" \
	"$(INTDIR)\TRIAS02P.SBR" \
	"$(INTDIR)\VISERROR.SBR" \
	"$(INTDIR)\VISINFO.SBR"

"$(OUTDIR)\Trias422.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 ospace2d.lib trias31d.lib cont32d.lib tfrm32ld.lib tfrm32d.lib stdcppd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /pdb:"Debug4/trias322d.pdb" /debug /machine:I386 /stub:"obj32\rights.exe" /out:"Debug4/trias32d.dll" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /profile /pdb:none
LINK32_FLAGS=ospace2d.lib trias31d.lib cont32d.lib tfrm32ld.lib tfrm32d.lib\
 stdcppd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)/trias322d.pdb"\
 /debug /machine:I386 /def:".\obj32\TRIAS32D.DEF" /stub:"obj32\rights.exe"\
 /out:"$(OUTDIR)/trias32d.dll" /implib:"$(OUTDIR)/trias32d.lib"\
 /SUBSYSTEM:windows,4.0 
DEF_FILE= \
	".\obj32\TRIAS32D.DEF"
LINK32_OBJS= \
	"$(INTDIR)\ATTRIBS.OBJ" \
	"$(INTDIR)\COMMFIL.OBJ" \
	"$(INTDIR)\CTF.OBJ" \
	"$(INTDIR)\DATETIME.OBJ" \
	"$(INTDIR)\DB.OBJ" \
	"$(INTDIR)\dbasrt02.obj" \
	"$(INTDIR)\DBGETGI.OBJ" \
	"$(INTDIR)\DEL.OBJ" \
	"$(INTDIR)\DELGI.OBJ" \
	"$(INTDIR)\DELGIF.OBJ" \
	"$(INTDIR)\DELGIL.OBJ" \
	"$(INTDIR)\DELGIP.OBJ" \
	"$(INTDIR)\DELID.OBJ" \
	"$(INTDIR)\DELKAN.OBJ" \
	"$(INTDIR)\DELKANF.OBJ" \
	"$(INTDIR)\DELLINK.OBJ" \
	"$(INTDIR)\DELMIN.OBJ" \
	"$(INTDIR)\DELREL.OBJ" \
	"$(INTDIR)\DELRELKO.OBJ" \
	"$(INTDIR)\DLLBIND.OBJ" \
	"$(INTDIR)\DRAWRECT.OBJ" \
	"$(INTDIR)\EFONT.OBJ" \
	"$(INTDIR)\EPEN.OBJ" \
	"$(INTDIR)\EVALKOEF.OBJ" \
	"$(INTDIR)\FINDREL.OBJ" \
	"$(INTDIR)\FNDGI.OBJ" \
	"$(INTDIR)\FNDKA.OBJ" \
	"$(INTDIR)\FNDLI.OBJ" \
	"$(INTDIR)\FNDMA.OBJ" \
	"$(INTDIR)\FNDPU.OBJ" \
	"$(INTDIR)\FNDTXT.OBJ" \
	"$(INTDIR)\FNDTXTN.OBJ" \
	"$(INTDIR)\FREETEXT.OBJ" \
	"$(INTDIR)\GEO_OBJ.OBJ" \
	"$(INTDIR)\GEO_OBJ1.OBJ" \
	"$(INTDIR)\GEOTEXT.OBJ" \
	"$(INTDIR)\GERADE.OBJ" \
	"$(INTDIR)\GETAPU.OBJ" \
	"$(INTDIR)\GETDBLM.OBJ" \
	"$(INTDIR)\GETGI.OBJ" \
	"$(INTDIR)\GETGIF.OBJ" \
	"$(INTDIR)\GETGIL.OBJ" \
	"$(INTDIR)\GETGIP.OBJ" \
	"$(INTDIR)\GETKAN.OBJ" \
	"$(INTDIR)\GETLONGM.OBJ" \
	"$(INTDIR)\GETMERKL.OBJ" \
	"$(INTDIR)\GETMI.OBJ" \
	"$(INTDIR)\GETMIT.OBJ" \
	"$(INTDIR)\GETRCODE.OBJ" \
	"$(INTDIR)\GETREL.OBJ" \
	"$(INTDIR)\GETRIF.OBJ" \
	"$(INTDIR)\GETRIG.OBJ" \
	"$(INTDIR)\GETRIL.OBJ" \
	"$(INTDIR)\GETRIP.OBJ" \
	"$(INTDIR)\GETTEXT.OBJ" \
	"$(INTDIR)\GETTEXTL.OBJ" \
	"$(INTDIR)\GETTEXTN.OBJ" \
	"$(INTDIR)\GIWINDOW.OBJ" \
	"$(INTDIR)\HDRENTRY.OBJ" \
	"$(INTDIR)\HTFUNC.OBJ" \
	"$(INTDIR)\HTMANR.OBJ" \
	"$(INTDIR)\IDENT.OBJ" \
	"$(INTDIR)\IGLAGE.OBJ" \
	"$(INTDIR)\IGPTNL.OBJ" \
	"$(INTDIR)\ISALIKE.OBJ" \
	"$(INTDIR)\KOMPLEX.OBJ" \
	"$(INTDIR)\KONS.OBJ" \
	"$(INTDIR)\KONSOBJ.OBJ" \
	"$(INTDIR)\KONSSATZ.OBJ" \
	"$(INTDIR)\KONSUTIL.OBJ" \
	"$(INTDIR)\LIBMAIN2.OBJ" \
	"$(INTDIR)\MDELKI.OBJ" \
	"$(INTDIR)\MDELKM.OBJ" \
	"$(INTDIR)\MDELKR.OBJ" \
	"$(INTDIR)\MERKINFO.OBJ" \
	"$(INTDIR)\MERKMAL.OBJ" \
	"$(INTDIR)\MFIND.OBJ" \
	"$(INTDIR)\MGETKM.OBJ" \
	"$(INTDIR)\MGETKR.OBJ" \
	"$(INTDIR)\MGETKT.OBJ" \
	"$(INTDIR)\MGETL.OBJ" \
	"$(INTDIR)\MGETTX.OBJ" \
	"$(INTDIR)\MGETWM.OBJ" \
	"$(INTDIR)\MODID.OBJ" \
	"$(INTDIR)\MPUTKI.OBJ" \
	"$(INTDIR)\MPUTKM.OBJ" \
	"$(INTDIR)\MPUTKR.OBJ" \
	"$(INTDIR)\MPUTKT.OBJ" \
	"$(INTDIR)\MPUTTX.OBJ" \
	"$(INTDIR)\ObjGuid.obj" \
	"$(INTDIR)\OBJMTREE.OBJ" \
	"$(INTDIR)\OLISTE.OBJ" \
	"$(INTDIR)\OVLFOBJ.OBJ" \
	"$(INTDIR)\OVLLOBJ.OBJ" \
	"$(INTDIR)\OVLPOBJ.OBJ" \
	"$(INTDIR)\PALETTE.OBJ" \
	"$(INTDIR)\PBD.OBJ" \
	"$(INTDIR)\PBDIDS.OBJ" \
	"$(INTDIR)\PBDTEMP.OBJ" \
	"$(INTDIR)\PROFDLL.OBJ" \
	"$(INTDIR)\PUINFL.OBJ" \
	"$(INTDIR)\PUTFOBJ.OBJ" \
	"$(INTDIR)\PUTIDENT.OBJ" \
	"$(INTDIR)\PUTKOBJ.OBJ" \
	"$(INTDIR)\PUTLINK.OBJ" \
	"$(INTDIR)\PUTLOBJ.OBJ" \
	"$(INTDIR)\PUTMIT.OBJ" \
	"$(INTDIR)\PUTPKT.OBJ" \
	"$(INTDIR)\PUTPOBJ.OBJ" \
	"$(INTDIR)\PUTREL.OBJ" \
	"$(INTDIR)\PUTTEMPL.OBJ" \
	"$(INTDIR)\PUTTOBJ.OBJ" \
	"$(INTDIR)\PUTTXTC.OBJ" \
	"$(INTDIR)\PUTTXTCN.OBJ" \
	"$(INTDIR)\QTFUNC.OBJ" \
	"$(INTDIR)\RECT.OBJ" \
	"$(INTDIR)\REGISTRY.OBJ" \
	"$(INTDIR)\RELATIO.OBJ" \
	"$(INTDIR)\RIGIN.OBJ" \
	"$(INTDIR)\RIGINFO.OBJ" \
	"$(INTDIR)\RIGKP.OBJ" \
	"$(INTDIR)\STINFL.OBJ" \
	"$(INTDIR)\Strings.obj" \
	"$(INTDIR)\STRUTIL.OBJ" \
	"$(INTDIR)\TRIAS02P.OBJ" \
	"$(INTDIR)\Trias322.res" \
	"$(INTDIR)\VISERROR.OBJ" \
	"$(INTDIR)\VISINFO.OBJ"

"$(OUTDIR)\trias32d.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying Target to Destination ...
OutDir=.\Debug4
TargetPath=.\Debug4\trias32d.dll
TargetName=trias32d
InputPath=.\Debug4\trias32d.dll
SOURCE=$(InputPath)

BuildCmds= \
	rem copy "$(TargetPath)" c:\trias.mvc\trias200 \
	rem copy "$(OutDir)\$(TargetName).lib" e:\triasdev.mvc\lib32 \
	

"c:\trias.mvc\trias200\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"\triasdev.mvc\lib32\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Trias322"
# PROP BASE Intermediate_Dir "Trias322"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Pseudo"
# PROP Intermediate_Dir "Pseudo"
# PROP Target_Dir ""
OUTDIR=.\Pseudo
INTDIR=.\Pseudo
# Begin Custom Macros
TargetName=Trias322
# End Custom Macros

ALL : "$(OUTDIR)\Trias322.dll" "c:\trias.mvc\trias200.rel\Trias322.dll"\
 "..\lib32\Trias322.lib"

CLEAN : 
	-@erase "$(INTDIR)\ATTRIBS.OBJ"
	-@erase "$(INTDIR)\COMMFIL.OBJ"
	-@erase "$(INTDIR)\CTF.OBJ"
	-@erase "$(INTDIR)\DATETIME.OBJ"
	-@erase "$(INTDIR)\DB.OBJ"
	-@erase "$(INTDIR)\dbasrt02.obj"
	-@erase "$(INTDIR)\DBGETGI.OBJ"
	-@erase "$(INTDIR)\DEL.OBJ"
	-@erase "$(INTDIR)\DELGI.OBJ"
	-@erase "$(INTDIR)\DELGIF.OBJ"
	-@erase "$(INTDIR)\DELGIL.OBJ"
	-@erase "$(INTDIR)\DELGIP.OBJ"
	-@erase "$(INTDIR)\DELID.OBJ"
	-@erase "$(INTDIR)\DELKAN.OBJ"
	-@erase "$(INTDIR)\DELKANF.OBJ"
	-@erase "$(INTDIR)\DELLINK.OBJ"
	-@erase "$(INTDIR)\DELMIN.OBJ"
	-@erase "$(INTDIR)\DELREL.OBJ"
	-@erase "$(INTDIR)\DELRELKO.OBJ"
	-@erase "$(INTDIR)\DLLBIND.OBJ"
	-@erase "$(INTDIR)\DRAWRECT.OBJ"
	-@erase "$(INTDIR)\EFONT.OBJ"
	-@erase "$(INTDIR)\EPEN.OBJ"
	-@erase "$(INTDIR)\EVALKOEF.OBJ"
	-@erase "$(INTDIR)\FINDREL.OBJ"
	-@erase "$(INTDIR)\FNDGI.OBJ"
	-@erase "$(INTDIR)\FNDKA.OBJ"
	-@erase "$(INTDIR)\FNDLI.OBJ"
	-@erase "$(INTDIR)\FNDMA.OBJ"
	-@erase "$(INTDIR)\FNDPU.OBJ"
	-@erase "$(INTDIR)\FNDTXT.OBJ"
	-@erase "$(INTDIR)\FNDTXTN.OBJ"
	-@erase "$(INTDIR)\FREETEXT.OBJ"
	-@erase "$(INTDIR)\GEO_OBJ.OBJ"
	-@erase "$(INTDIR)\GEO_OBJ1.OBJ"
	-@erase "$(INTDIR)\GEOTEXT.OBJ"
	-@erase "$(INTDIR)\GERADE.OBJ"
	-@erase "$(INTDIR)\GETAPU.OBJ"
	-@erase "$(INTDIR)\GETDBLM.OBJ"
	-@erase "$(INTDIR)\GETGI.OBJ"
	-@erase "$(INTDIR)\GETGIF.OBJ"
	-@erase "$(INTDIR)\GETGIL.OBJ"
	-@erase "$(INTDIR)\GETGIP.OBJ"
	-@erase "$(INTDIR)\GETKAN.OBJ"
	-@erase "$(INTDIR)\GETLONGM.OBJ"
	-@erase "$(INTDIR)\GETMERKL.OBJ"
	-@erase "$(INTDIR)\GETMI.OBJ"
	-@erase "$(INTDIR)\GETMIT.OBJ"
	-@erase "$(INTDIR)\GETRCODE.OBJ"
	-@erase "$(INTDIR)\GETREL.OBJ"
	-@erase "$(INTDIR)\GETRIF.OBJ"
	-@erase "$(INTDIR)\GETRIG.OBJ"
	-@erase "$(INTDIR)\GETRIL.OBJ"
	-@erase "$(INTDIR)\GETRIP.OBJ"
	-@erase "$(INTDIR)\GETTEXT.OBJ"
	-@erase "$(INTDIR)\GETTEXTL.OBJ"
	-@erase "$(INTDIR)\GETTEXTN.OBJ"
	-@erase "$(INTDIR)\GIWINDOW.OBJ"
	-@erase "$(INTDIR)\HDRENTRY.OBJ"
	-@erase "$(INTDIR)\HTFUNC.OBJ"
	-@erase "$(INTDIR)\HTMANR.OBJ"
	-@erase "$(INTDIR)\IDENT.OBJ"
	-@erase "$(INTDIR)\IGLAGE.OBJ"
	-@erase "$(INTDIR)\IGPTNL.OBJ"
	-@erase "$(INTDIR)\ISALIKE.OBJ"
	-@erase "$(INTDIR)\KOMPLEX.OBJ"
	-@erase "$(INTDIR)\LIBMAIN2.OBJ"
	-@erase "$(INTDIR)\MDELKI.OBJ"
	-@erase "$(INTDIR)\MDELKM.OBJ"
	-@erase "$(INTDIR)\MDELKR.OBJ"
	-@erase "$(INTDIR)\MERKINFO.OBJ"
	-@erase "$(INTDIR)\MERKMAL.OBJ"
	-@erase "$(INTDIR)\MFIND.OBJ"
	-@erase "$(INTDIR)\MGETKM.OBJ"
	-@erase "$(INTDIR)\MGETKR.OBJ"
	-@erase "$(INTDIR)\MGETKT.OBJ"
	-@erase "$(INTDIR)\MGETL.OBJ"
	-@erase "$(INTDIR)\MGETTX.OBJ"
	-@erase "$(INTDIR)\MGETWM.OBJ"
	-@erase "$(INTDIR)\MODID.OBJ"
	-@erase "$(INTDIR)\MPUTKI.OBJ"
	-@erase "$(INTDIR)\MPUTKM.OBJ"
	-@erase "$(INTDIR)\MPUTKR.OBJ"
	-@erase "$(INTDIR)\MPUTKT.OBJ"
	-@erase "$(INTDIR)\MPUTTX.OBJ"
	-@erase "$(INTDIR)\ObjGuid.obj"
	-@erase "$(INTDIR)\OBJMTREE.OBJ"
	-@erase "$(INTDIR)\OLISTE.OBJ"
	-@erase "$(INTDIR)\OVLFOBJ.OBJ"
	-@erase "$(INTDIR)\OVLLOBJ.OBJ"
	-@erase "$(INTDIR)\OVLPOBJ.OBJ"
	-@erase "$(INTDIR)\PALETTE.OBJ"
	-@erase "$(INTDIR)\PBD.OBJ"
	-@erase "$(INTDIR)\PBDIDS.OBJ"
	-@erase "$(INTDIR)\PBDTEMP.OBJ"
	-@erase "$(INTDIR)\PROFDLL.OBJ"
	-@erase "$(INTDIR)\PUINFL.OBJ"
	-@erase "$(INTDIR)\PUTFOBJ.OBJ"
	-@erase "$(INTDIR)\PUTIDENT.OBJ"
	-@erase "$(INTDIR)\PUTKOBJ.OBJ"
	-@erase "$(INTDIR)\PUTLINK.OBJ"
	-@erase "$(INTDIR)\PUTLOBJ.OBJ"
	-@erase "$(INTDIR)\PUTMIT.OBJ"
	-@erase "$(INTDIR)\PUTPKT.OBJ"
	-@erase "$(INTDIR)\PUTPOBJ.OBJ"
	-@erase "$(INTDIR)\PUTREL.OBJ"
	-@erase "$(INTDIR)\PUTTEMPL.OBJ"
	-@erase "$(INTDIR)\PUTTOBJ.OBJ"
	-@erase "$(INTDIR)\PUTTXTC.OBJ"
	-@erase "$(INTDIR)\PUTTXTCN.OBJ"
	-@erase "$(INTDIR)\QTFUNC.OBJ"
	-@erase "$(INTDIR)\RECT.OBJ"
	-@erase "$(INTDIR)\REGISTRY.OBJ"
	-@erase "$(INTDIR)\RELATIO.OBJ"
	-@erase "$(INTDIR)\RIGIN.OBJ"
	-@erase "$(INTDIR)\RIGINFO.OBJ"
	-@erase "$(INTDIR)\RIGKP.OBJ"
	-@erase "$(INTDIR)\STINFL.OBJ"
	-@erase "$(INTDIR)\Strings.obj"
	-@erase "$(INTDIR)\STRUTIL.OBJ"
	-@erase "$(INTDIR)\TRIAS02P.OBJ"
	-@erase "$(INTDIR)\Trias322.res"
	-@erase "$(INTDIR)\Trias422.pch"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(INTDIR)\VISERROR.OBJ"
	-@erase "$(INTDIR)\VISINFO.OBJ"
	-@erase "$(OUTDIR)\Trias322.dll"
	-@erase "$(OUTDIR)\Trias322.exp"
	-@erase "$(OUTDIR)\Trias322.lib"
	-@erase "$(OUTDIR)\Trias322.pdb"
	-@erase "..\lib32\Trias322.lib"
	-@erase "c:\trias.mvc\trias200.rel\Trias322.dll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "DLL" /D "__CV__" /D "__TRIAS02DLL__" /D "OS_NO_ALLOCATORS" /D "OS_NO_STREAM_SUPPORT" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "OS_ALTERNATIVE_STRING_NAMES" /D "__ATL_USED__" /D "__ATL_11_USED__" /D "QI_EXCEPTION" /Yu"trias02p.hxx" /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "DLL" /D "__CV__" /D "__TRIAS02DLL__" /D "OS_NO_ALLOCATORS" /D "OS_NO_STREAM_SUPPORT" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "OS_ALTERNATIVE_STRING_NAMES" /D "__ATL_USED__" /D "__ATL_11_USED__" /D "QI_EXCEPTION" /Yu"trias02p.hxx" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W3 /WX /GX /Zi /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "STRICT" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "DLL" /D "__CV__" /D\
 "__TRIAS02DLL__" /D "OS_NO_ALLOCATORS" /D "OS_NO_STREAM_SUPPORT" /D "OS_WIN_95"\
 /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "OS_ALTERNATIVE_STRING_NAMES" /D\
 "__ATL_USED__" /D "__ATL_11_USED__" /D "QI_EXCEPTION"\
 /Fp"$(INTDIR)/Trias422.pch" /Yu"trias02p.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/"\
 /c 
CPP_OBJS=.\Pseudo/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/Trias322.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Trias422.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 ospace2r.lib trias321.lib cont32r.lib tfrmwrkl.lib tfrmwork.lib stdcppr.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /stub:"obj32\rights.exe" /out:"Release/Trias322.dll" /SUBSYSTEM:windows,4.0
# SUBTRACT BASE LINK32 /pdb:none /debug
# ADD LINK32 ospace2r.lib trias321.lib cont32r.lib tfrmwrkl.lib tfrmwork.lib stdcppr.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /stub:"obj32\rights.exe" /out:"Pseudo/Trias322.dll" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=ospace2r.lib trias321.lib cont32r.lib tfrmwrkl.lib tfrmwork.lib\
 stdcppr.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)/Trias322.pdb" /debug\
 /machine:I386 /def:".\obj32\TRIAS322.DEF" /stub:"obj32\rights.exe"\
 /out:"$(OUTDIR)/Trias322.dll" /implib:"$(OUTDIR)/Trias322.lib"\
 /SUBSYSTEM:windows,4.0 
DEF_FILE= \
	".\obj32\TRIAS322.DEF"
LINK32_OBJS= \
	"$(INTDIR)\ATTRIBS.OBJ" \
	"$(INTDIR)\COMMFIL.OBJ" \
	"$(INTDIR)\CTF.OBJ" \
	"$(INTDIR)\DATETIME.OBJ" \
	"$(INTDIR)\DB.OBJ" \
	"$(INTDIR)\dbasrt02.obj" \
	"$(INTDIR)\DBGETGI.OBJ" \
	"$(INTDIR)\DEL.OBJ" \
	"$(INTDIR)\DELGI.OBJ" \
	"$(INTDIR)\DELGIF.OBJ" \
	"$(INTDIR)\DELGIL.OBJ" \
	"$(INTDIR)\DELGIP.OBJ" \
	"$(INTDIR)\DELID.OBJ" \
	"$(INTDIR)\DELKAN.OBJ" \
	"$(INTDIR)\DELKANF.OBJ" \
	"$(INTDIR)\DELLINK.OBJ" \
	"$(INTDIR)\DELMIN.OBJ" \
	"$(INTDIR)\DELREL.OBJ" \
	"$(INTDIR)\DELRELKO.OBJ" \
	"$(INTDIR)\DLLBIND.OBJ" \
	"$(INTDIR)\DRAWRECT.OBJ" \
	"$(INTDIR)\EFONT.OBJ" \
	"$(INTDIR)\EPEN.OBJ" \
	"$(INTDIR)\EVALKOEF.OBJ" \
	"$(INTDIR)\FINDREL.OBJ" \
	"$(INTDIR)\FNDGI.OBJ" \
	"$(INTDIR)\FNDKA.OBJ" \
	"$(INTDIR)\FNDLI.OBJ" \
	"$(INTDIR)\FNDMA.OBJ" \
	"$(INTDIR)\FNDPU.OBJ" \
	"$(INTDIR)\FNDTXT.OBJ" \
	"$(INTDIR)\FNDTXTN.OBJ" \
	"$(INTDIR)\FREETEXT.OBJ" \
	"$(INTDIR)\GEO_OBJ.OBJ" \
	"$(INTDIR)\GEO_OBJ1.OBJ" \
	"$(INTDIR)\GEOTEXT.OBJ" \
	"$(INTDIR)\GERADE.OBJ" \
	"$(INTDIR)\GETAPU.OBJ" \
	"$(INTDIR)\GETDBLM.OBJ" \
	"$(INTDIR)\GETGI.OBJ" \
	"$(INTDIR)\GETGIF.OBJ" \
	"$(INTDIR)\GETGIL.OBJ" \
	"$(INTDIR)\GETGIP.OBJ" \
	"$(INTDIR)\GETKAN.OBJ" \
	"$(INTDIR)\GETLONGM.OBJ" \
	"$(INTDIR)\GETMERKL.OBJ" \
	"$(INTDIR)\GETMI.OBJ" \
	"$(INTDIR)\GETMIT.OBJ" \
	"$(INTDIR)\GETRCODE.OBJ" \
	"$(INTDIR)\GETREL.OBJ" \
	"$(INTDIR)\GETRIF.OBJ" \
	"$(INTDIR)\GETRIG.OBJ" \
	"$(INTDIR)\GETRIL.OBJ" \
	"$(INTDIR)\GETRIP.OBJ" \
	"$(INTDIR)\GETTEXT.OBJ" \
	"$(INTDIR)\GETTEXTL.OBJ" \
	"$(INTDIR)\GETTEXTN.OBJ" \
	"$(INTDIR)\GIWINDOW.OBJ" \
	"$(INTDIR)\HDRENTRY.OBJ" \
	"$(INTDIR)\HTFUNC.OBJ" \
	"$(INTDIR)\HTMANR.OBJ" \
	"$(INTDIR)\IDENT.OBJ" \
	"$(INTDIR)\IGLAGE.OBJ" \
	"$(INTDIR)\IGPTNL.OBJ" \
	"$(INTDIR)\ISALIKE.OBJ" \
	"$(INTDIR)\KOMPLEX.OBJ" \
	"$(INTDIR)\LIBMAIN2.OBJ" \
	"$(INTDIR)\MDELKI.OBJ" \
	"$(INTDIR)\MDELKM.OBJ" \
	"$(INTDIR)\MDELKR.OBJ" \
	"$(INTDIR)\MERKINFO.OBJ" \
	"$(INTDIR)\MERKMAL.OBJ" \
	"$(INTDIR)\MFIND.OBJ" \
	"$(INTDIR)\MGETKM.OBJ" \
	"$(INTDIR)\MGETKR.OBJ" \
	"$(INTDIR)\MGETKT.OBJ" \
	"$(INTDIR)\MGETL.OBJ" \
	"$(INTDIR)\MGETTX.OBJ" \
	"$(INTDIR)\MGETWM.OBJ" \
	"$(INTDIR)\MODID.OBJ" \
	"$(INTDIR)\MPUTKI.OBJ" \
	"$(INTDIR)\MPUTKM.OBJ" \
	"$(INTDIR)\MPUTKR.OBJ" \
	"$(INTDIR)\MPUTKT.OBJ" \
	"$(INTDIR)\MPUTTX.OBJ" \
	"$(INTDIR)\ObjGuid.obj" \
	"$(INTDIR)\OBJMTREE.OBJ" \
	"$(INTDIR)\OLISTE.OBJ" \
	"$(INTDIR)\OVLFOBJ.OBJ" \
	"$(INTDIR)\OVLLOBJ.OBJ" \
	"$(INTDIR)\OVLPOBJ.OBJ" \
	"$(INTDIR)\PALETTE.OBJ" \
	"$(INTDIR)\PBD.OBJ" \
	"$(INTDIR)\PBDIDS.OBJ" \
	"$(INTDIR)\PBDTEMP.OBJ" \
	"$(INTDIR)\PROFDLL.OBJ" \
	"$(INTDIR)\PUINFL.OBJ" \
	"$(INTDIR)\PUTFOBJ.OBJ" \
	"$(INTDIR)\PUTIDENT.OBJ" \
	"$(INTDIR)\PUTKOBJ.OBJ" \
	"$(INTDIR)\PUTLINK.OBJ" \
	"$(INTDIR)\PUTLOBJ.OBJ" \
	"$(INTDIR)\PUTMIT.OBJ" \
	"$(INTDIR)\PUTPKT.OBJ" \
	"$(INTDIR)\PUTPOBJ.OBJ" \
	"$(INTDIR)\PUTREL.OBJ" \
	"$(INTDIR)\PUTTEMPL.OBJ" \
	"$(INTDIR)\PUTTOBJ.OBJ" \
	"$(INTDIR)\PUTTXTC.OBJ" \
	"$(INTDIR)\PUTTXTCN.OBJ" \
	"$(INTDIR)\QTFUNC.OBJ" \
	"$(INTDIR)\RECT.OBJ" \
	"$(INTDIR)\REGISTRY.OBJ" \
	"$(INTDIR)\RELATIO.OBJ" \
	"$(INTDIR)\RIGIN.OBJ" \
	"$(INTDIR)\RIGINFO.OBJ" \
	"$(INTDIR)\RIGKP.OBJ" \
	"$(INTDIR)\STINFL.OBJ" \
	"$(INTDIR)\Strings.obj" \
	"$(INTDIR)\STRUTIL.OBJ" \
	"$(INTDIR)\TRIAS02P.OBJ" \
	"$(INTDIR)\Trias322.res" \
	"$(INTDIR)\VISERROR.OBJ" \
	"$(INTDIR)\VISINFO.OBJ"

"$(OUTDIR)\Trias322.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying Target to Destination ...
OutDir=.\Pseudo
TargetPath=.\Pseudo\Trias322.dll
TargetName=Trias322
InputPath=.\Pseudo\Trias322.dll
SOURCE=$(InputPath)

BuildCmds= \
	rem copy "$(TargetPath)" c:\trias.mvc\trias200.rel \
	rem copy "$(OutDir)\$(TargetName).lib" e:\triasdev.mvc\lib32 \
	

"c:\trias.mvc\trias200.rel\$(TargetName).dll" : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
   $(BuildCmds)

"\triasdev.mvc\lib32\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
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

# Name "Trias322 - Win32 Release"
# Name "Trias322 - Win32 Debug"
# Name "Trias322 - Win32 Pseudo Debug"

!IF  "$(CFG)" == "Trias322 - Win32 Release"

!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"

!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\DLLBIND.CXX
DEP_CPP_DLLBI=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\DLLBIND.OBJ" : $(SOURCE) $(DEP_CPP_DLLBI) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\DLLBIND.OBJ" : $(SOURCE) $(DEP_CPP_DLLBI) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\DLLBIND.SBR" : $(SOURCE) $(DEP_CPP_DLLBI) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\DLLBIND.OBJ" : $(SOURCE) $(DEP_CPP_DLLBI) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PROFDLL.CXX
DEP_CPP_PROFD=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Profile.hxx"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\PROFDLL.OBJ" : $(SOURCE) $(DEP_CPP_PROFD) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\PROFDLL.OBJ" : $(SOURCE) $(DEP_CPP_PROFD) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\PROFDLL.SBR" : $(SOURCE) $(DEP_CPP_PROFD) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\PROFDLL.OBJ" : $(SOURCE) $(DEP_CPP_PROFD) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\EVALKOEF.CXX
DEP_CPP_EVALK=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\EVALKOEF.OBJ" : $(SOURCE) $(DEP_CPP_EVALK) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\EVALKOEF.OBJ" : $(SOURCE) $(DEP_CPP_EVALK) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\EVALKOEF.SBR" : $(SOURCE) $(DEP_CPP_EVALK) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\EVALKOEF.OBJ" : $(SOURCE) $(DEP_CPP_EVALK) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DATETIME.CXX
DEP_CPP_DATET=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\DATETIME.OBJ" : $(SOURCE) $(DEP_CPP_DATET) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\DATETIME.OBJ" : $(SOURCE) $(DEP_CPP_DATET) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\DATETIME.SBR" : $(SOURCE) $(DEP_CPP_DATET) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\DATETIME.OBJ" : $(SOURCE) $(DEP_CPP_DATET) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\HDRENTRY.CXX
DEP_CPP_HDREN=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Hdrentry.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\HDRENTRY.OBJ" : $(SOURCE) $(DEP_CPP_HDREN) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\HDRENTRY.OBJ" : $(SOURCE) $(DEP_CPP_HDREN) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\HDRENTRY.SBR" : $(SOURCE) $(DEP_CPP_HDREN) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\HDRENTRY.OBJ" : $(SOURCE) $(DEP_CPP_HDREN) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\LIBMAIN2.CXX
DEP_CPP_LIBMA=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\Strings.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBADDR.HXX"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\Kons.hxx"\
	{$(INCLUDE)}"\KONSSATZ.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\registry.hxx"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRiASMode.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\LIBMAIN2.OBJ" : $(SOURCE) $(DEP_CPP_LIBMA) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\LIBMAIN2.OBJ" : $(SOURCE) $(DEP_CPP_LIBMA) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\LIBMAIN2.SBR" : $(SOURCE) $(DEP_CPP_LIBMA) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\LIBMAIN2.OBJ" : $(SOURCE) $(DEP_CPP_LIBMA) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRUTIL.CXX
DEP_CPP_STRUT=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\STRUTIL.OBJ" : $(SOURCE) $(DEP_CPP_STRUT) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\STRUTIL.OBJ" : $(SOURCE) $(DEP_CPP_STRUT) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\STRUTIL.SBR" : $(SOURCE) $(DEP_CPP_STRUT) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\STRUTIL.OBJ" : $(SOURCE) $(DEP_CPP_STRUT) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\COMMFIL.CXX
DEP_CPP_COMMF=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Impexp.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\COMMFIL.OBJ" : $(SOURCE) $(DEP_CPP_COMMF) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\COMMFIL.OBJ" : $(SOURCE) $(DEP_CPP_COMMF) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\COMMFIL.SBR" : $(SOURCE) $(DEP_CPP_COMMF) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\COMMFIL.OBJ" : $(SOURCE) $(DEP_CPP_COMMF) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CTF.CXX
DEP_CPP_CTF_C=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\TRIAS02.H"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Hdrentry.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\CTF.OBJ" : $(SOURCE) $(DEP_CPP_CTF_C) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\CTF.OBJ" : $(SOURCE) $(DEP_CPP_CTF_C) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\CTF.SBR" : $(SOURCE) $(DEP_CPP_CTF_C) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\CTF.OBJ" : $(SOURCE) $(DEP_CPP_CTF_C) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DRAWRECT.CXX

!IF  "$(CFG)" == "Trias322 - Win32 Release"

# SUBTRACT CPP /D "__CV__" /Yu

"$(INTDIR)\DRAWRECT.OBJ" : $(SOURCE) "$(INTDIR)"
   $(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "STRICT" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "DLL" /D "__TRIAS02DLL__" /D\
 "OS_NO_ALLOCATORS" /D "OS_NO_STREAM_SUPPORT" /D "OS_WIN_95" /D "OS_STL_ASSERT"\
 /D "OS_NO_WSTRING" /D "OS_ALTERNATIVE_STRING_NAMES" /D "__ATL_USED__" /D\
 "__ATL_11_USED__" /D "QI_EXCEPTION" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"

# SUBTRACT CPP /D "__CV__" /Yu

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "DLL" /D\
 "__TRIAS02DLL__" /D "OS_NO_ALLOCATORS" /D "OS_NO_STREAM_SUPPORT" /D "OS_WIN_95"\
 /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "OS_ALTERNATIVE_STRING_NAMES" /D\
 "__ATL_USED__" /D "__ATL_11_USED__" /D "QI_EXCEPTION" /FR"$(INTDIR)/"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/trias322d.pdb" /c $(SOURCE) \
	

"$(INTDIR)\DRAWRECT.OBJ" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\DRAWRECT.SBR" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"

# SUBTRACT BASE CPP /D "__CV__" /Yu
# SUBTRACT CPP /D "__CV__" /Yu

"$(INTDIR)\DRAWRECT.OBJ" : $(SOURCE) "$(INTDIR)"
   $(CPP) /nologo /MD /W3 /WX /GX /Zi /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "STRICT" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "DLL" /D "__TRIAS02DLL__"\
 /D "OS_NO_ALLOCATORS" /D "OS_NO_STREAM_SUPPORT" /D "OS_WIN_95" /D\
 "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "OS_ALTERNATIVE_STRING_NAMES" /D\
 "__ATL_USED__" /D "__ATL_11_USED__" /D "QI_EXCEPTION" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TRIAS02P.CXX
DEP_CPP_TRIAS=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"

# ADD CPP /Yc"trias02p.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "STRICT" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "DLL" /D "__CV__" /D\
 "__TRIAS02DLL__" /D "OS_NO_ALLOCATORS" /D "OS_NO_STREAM_SUPPORT" /D "OS_WIN_95"\
 /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "OS_ALTERNATIVE_STRING_NAMES" /D\
 "__ATL_USED__" /D "__ATL_11_USED__" /D "QI_EXCEPTION"\
 /Fp"$(INTDIR)/Trias422.pch" /Yc"trias02p.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\TRIAS02P.OBJ" : $(SOURCE) $(DEP_CPP_TRIAS) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Trias422.pch" : $(SOURCE) $(DEP_CPP_TRIAS) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"

# ADD CPP /Yc"trias02p.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "DLL" /D\
 "__CV__" /D "__TRIAS02DLL__" /D "OS_NO_ALLOCATORS" /D "OS_NO_STREAM_SUPPORT" /D\
 "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D\
 "OS_ALTERNATIVE_STRING_NAMES" /D "__ATL_USED__" /D "__ATL_11_USED__" /D\
 "QI_EXCEPTION" /FR"$(INTDIR)/" /Fp"$(INTDIR)/trias322d.pch" /Yc"trias02p.hxx"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/trias322d.pdb" /c $(SOURCE) \
	

"$(INTDIR)\TRIAS02P.OBJ" : $(SOURCE) $(DEP_CPP_TRIAS) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\TRIAS02P.SBR" : $(SOURCE) $(DEP_CPP_TRIAS) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\trias322d.pch" : $(SOURCE) $(DEP_CPP_TRIAS) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"

# ADD BASE CPP /Yc"trias02p.hxx"
# ADD CPP /Yc"trias02p.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /Zi /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "STRICT" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "DLL" /D "__CV__" /D\
 "__TRIAS02DLL__" /D "OS_NO_ALLOCATORS" /D "OS_NO_STREAM_SUPPORT" /D "OS_WIN_95"\
 /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "OS_ALTERNATIVE_STRING_NAMES" /D\
 "__ATL_USED__" /D "__ATL_11_USED__" /D "QI_EXCEPTION"\
 /Fp"$(INTDIR)/Trias422.pch" /Yc"trias02p.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/"\
 /c $(SOURCE) \
	

"$(INTDIR)\TRIAS02P.OBJ" : $(SOURCE) $(DEP_CPP_TRIAS) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Trias422.pch" : $(SOURCE) $(DEP_CPP_TRIAS) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\REGISTRY.CXX
DEP_CPP_REGIS=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\registry.hxx"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\REGISTRY.OBJ" : $(SOURCE) $(DEP_CPP_REGIS) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\REGISTRY.OBJ" : $(SOURCE) $(DEP_CPP_REGIS) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\REGISTRY.SBR" : $(SOURCE) $(DEP_CPP_REGIS) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\REGISTRY.OBJ" : $(SOURCE) $(DEP_CPP_REGIS) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DB.CXX
DEP_CPP_DB_CX=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\PBDIDS.HXX"\
	".\TRIAS02.H"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Hdrentry.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\PBD.HXX"\
	{$(INCLUDE)}"\PBDDB.H"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\DB.OBJ" : $(SOURCE) $(DEP_CPP_DB_CX) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\DB.OBJ" : $(SOURCE) $(DEP_CPP_DB_CX) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\DB.SBR" : $(SOURCE) $(DEP_CPP_DB_CX) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\DB.OBJ" : $(SOURCE) $(DEP_CPP_DB_CX) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\KONS.CXX
DEP_CPP_KONS_=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\PROTOCOL.HXX"\
	".\TRIAS02.H"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBADDR.HXX"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\Kons.hxx"\
	{$(INCLUDE)}"\KONSSATZ.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "DLL" /D\
 "__CV__" /D "__TRIAS02DLL__" /D "OS_NO_ALLOCATORS" /D "OS_NO_STREAM_SUPPORT" /D\
 "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D\
 "OS_ALTERNATIVE_STRING_NAMES" /D "__ATL_USED__" /D "__ATL_11_USED__" /D\
 "QI_EXCEPTION" /FR"$(INTDIR)/" /Fp"$(INTDIR)/trias322d.pch" /Yu"trias02p.hxx"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/trias322d.pdb" /c $(SOURCE) \
	

"$(INTDIR)\KONS.OBJ" : $(SOURCE) $(DEP_CPP_KONS_) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"
   $(BuildCmds)

"$(INTDIR)\KONS.SBR" : $(SOURCE) $(DEP_CPP_KONS_) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\KONSOBJ.CXX
DEP_CPP_KONSO=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\TRIAS02.H"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBADDR.HXX"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\Kons.hxx"\
	{$(INCLUDE)}"\KONSOBJ.HXX"\
	{$(INCLUDE)}"\KONSSATZ.HXX"\
	{$(INCLUDE)}"\KROUTINS.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OBJSTAT.HXX"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "DLL" /D\
 "__CV__" /D "__TRIAS02DLL__" /D "OS_NO_ALLOCATORS" /D "OS_NO_STREAM_SUPPORT" /D\
 "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D\
 "OS_ALTERNATIVE_STRING_NAMES" /D "__ATL_USED__" /D "__ATL_11_USED__" /D\
 "QI_EXCEPTION" /FR"$(INTDIR)/" /Fp"$(INTDIR)/trias322d.pch" /Yu"trias02p.hxx"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/trias322d.pdb" /c $(SOURCE) \
	

"$(INTDIR)\KONSOBJ.OBJ" : $(SOURCE) $(DEP_CPP_KONSO) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"
   $(BuildCmds)

"$(INTDIR)\KONSOBJ.SBR" : $(SOURCE) $(DEP_CPP_KONSO) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\KONSSATZ.CXX
DEP_CPP_KONSS=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\TRIAS02.H"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBADDR.HXX"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\Kons.hxx"\
	{$(INCLUDE)}"\KONSSATZ.HXX"\
	{$(INCLUDE)}"\KROUTINS.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\RISFILES.H"\
	{$(INCLUDE)}"\RISRECS.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "DLL" /D\
 "__CV__" /D "__TRIAS02DLL__" /D "OS_NO_ALLOCATORS" /D "OS_NO_STREAM_SUPPORT" /D\
 "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D\
 "OS_ALTERNATIVE_STRING_NAMES" /D "__ATL_USED__" /D "__ATL_11_USED__" /D\
 "QI_EXCEPTION" /FR"$(INTDIR)/" /Fp"$(INTDIR)/trias322d.pch" /Yu"trias02p.hxx"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/trias322d.pdb" /c $(SOURCE) \
	

"$(INTDIR)\KONSSATZ.OBJ" : $(SOURCE) $(DEP_CPP_KONSS) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"
   $(BuildCmds)

"$(INTDIR)\KONSSATZ.SBR" : $(SOURCE) $(DEP_CPP_KONSS) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\KONSUTIL.CXX
DEP_CPP_KONSU=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\TRIAS02.H"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBADDR.HXX"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\Kons.hxx"\
	{$(INCLUDE)}"\KONSSATZ.HXX"\
	{$(INCLUDE)}"\KROUTINS.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "DLL" /D\
 "__CV__" /D "__TRIAS02DLL__" /D "OS_NO_ALLOCATORS" /D "OS_NO_STREAM_SUPPORT" /D\
 "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D\
 "OS_ALTERNATIVE_STRING_NAMES" /D "__ATL_USED__" /D "__ATL_11_USED__" /D\
 "QI_EXCEPTION" /FR"$(INTDIR)/" /Fp"$(INTDIR)/trias322d.pch" /Yu"trias02p.hxx"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/trias322d.pdb" /c $(SOURCE) \
	

"$(INTDIR)\KONSUTIL.OBJ" : $(SOURCE) $(DEP_CPP_KONSU) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"
   $(BuildCmds)

"$(INTDIR)\KONSUTIL.SBR" : $(SOURCE) $(DEP_CPP_KONSU) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dbasrt02.cxx
DEP_CPP_DBASR=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRFKT.HXX"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OBJSTAT.HXX"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\dbasrt02.obj" : $(SOURCE) $(DEP_CPP_DBASR) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\dbasrt02.obj" : $(SOURCE) $(DEP_CPP_DBASR) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\dbasrt02.sbr" : $(SOURCE) $(DEP_CPP_DBASR) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\dbasrt02.obj" : $(SOURCE) $(DEP_CPP_DBASR) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GETAPU.CXX
DEP_CPP_GETAP=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\GETAPU.OBJ" : $(SOURCE) $(DEP_CPP_GETAP) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\GETAPU.OBJ" : $(SOURCE) $(DEP_CPP_GETAP) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\GETAPU.SBR" : $(SOURCE) $(DEP_CPP_GETAP) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\GETAPU.OBJ" : $(SOURCE) $(DEP_CPP_GETAP) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GETDBLM.CXX
DEP_CPP_GETDB=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\IDTDB.H"\
	{$(INCLUDE)}"\IDTDB001.H"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\GETDBLM.OBJ" : $(SOURCE) $(DEP_CPP_GETDB) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\GETDBLM.OBJ" : $(SOURCE) $(DEP_CPP_GETDB) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\GETDBLM.SBR" : $(SOURCE) $(DEP_CPP_GETDB) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\GETDBLM.OBJ" : $(SOURCE) $(DEP_CPP_GETDB) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GETGI.CXX
DEP_CPP_GETGI=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\GETGI.OBJ" : $(SOURCE) $(DEP_CPP_GETGI) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\GETGI.OBJ" : $(SOURCE) $(DEP_CPP_GETGI) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\GETGI.SBR" : $(SOURCE) $(DEP_CPP_GETGI) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\GETGI.OBJ" : $(SOURCE) $(DEP_CPP_GETGI) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GETGIF.CXX
DEP_CPP_GETGIF=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\GETGIF.OBJ" : $(SOURCE) $(DEP_CPP_GETGIF) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\GETGIF.OBJ" : $(SOURCE) $(DEP_CPP_GETGIF) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\GETGIF.SBR" : $(SOURCE) $(DEP_CPP_GETGIF) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\GETGIF.OBJ" : $(SOURCE) $(DEP_CPP_GETGIF) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GETGIL.CXX
DEP_CPP_GETGIL=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\GETGIL.OBJ" : $(SOURCE) $(DEP_CPP_GETGIL) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\GETGIL.OBJ" : $(SOURCE) $(DEP_CPP_GETGIL) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\GETGIL.SBR" : $(SOURCE) $(DEP_CPP_GETGIL) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\GETGIL.OBJ" : $(SOURCE) $(DEP_CPP_GETGIL) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GETGIP.CXX
DEP_CPP_GETGIP=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\GETGIP.OBJ" : $(SOURCE) $(DEP_CPP_GETGIP) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\GETGIP.OBJ" : $(SOURCE) $(DEP_CPP_GETGIP) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\GETGIP.SBR" : $(SOURCE) $(DEP_CPP_GETGIP) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\GETGIP.OBJ" : $(SOURCE) $(DEP_CPP_GETGIP) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GETKAN.CXX
DEP_CPP_GETKA=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\GETKAN.OBJ" : $(SOURCE) $(DEP_CPP_GETKA) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\GETKAN.OBJ" : $(SOURCE) $(DEP_CPP_GETKA) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\GETKAN.SBR" : $(SOURCE) $(DEP_CPP_GETKA) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\GETKAN.OBJ" : $(SOURCE) $(DEP_CPP_GETKA) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GETLONGM.CXX
DEP_CPP_GETLO=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\GETLONGM.OBJ" : $(SOURCE) $(DEP_CPP_GETLO) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\GETLONGM.OBJ" : $(SOURCE) $(DEP_CPP_GETLO) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\GETLONGM.SBR" : $(SOURCE) $(DEP_CPP_GETLO) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\GETLONGM.OBJ" : $(SOURCE) $(DEP_CPP_GETLO) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GETMERKL.CXX
DEP_CPP_GETME=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\GETMERKL.OBJ" : $(SOURCE) $(DEP_CPP_GETME) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\GETMERKL.OBJ" : $(SOURCE) $(DEP_CPP_GETME) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\GETMERKL.SBR" : $(SOURCE) $(DEP_CPP_GETME) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\GETMERKL.OBJ" : $(SOURCE) $(DEP_CPP_GETME) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GETMI.CXX
DEP_CPP_GETMI=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\MERKINFO.HXX"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\GETMI.OBJ" : $(SOURCE) $(DEP_CPP_GETMI) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\GETMI.OBJ" : $(SOURCE) $(DEP_CPP_GETMI) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\GETMI.SBR" : $(SOURCE) $(DEP_CPP_GETMI) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\GETMI.OBJ" : $(SOURCE) $(DEP_CPP_GETMI) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GETMIT.CXX
DEP_CPP_GETMIT=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\GETMIT.OBJ" : $(SOURCE) $(DEP_CPP_GETMIT) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\GETMIT.OBJ" : $(SOURCE) $(DEP_CPP_GETMIT) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\GETMIT.SBR" : $(SOURCE) $(DEP_CPP_GETMIT) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\GETMIT.OBJ" : $(SOURCE) $(DEP_CPP_GETMIT) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GETRCODE.CXX
DEP_CPP_GETRC=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\GETRCODE.HXX"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\GETRCODE.OBJ" : $(SOURCE) $(DEP_CPP_GETRC) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\GETRCODE.OBJ" : $(SOURCE) $(DEP_CPP_GETRC) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\GETRCODE.SBR" : $(SOURCE) $(DEP_CPP_GETRC) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\GETRCODE.OBJ" : $(SOURCE) $(DEP_CPP_GETRC) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GETREL.CXX
DEP_CPP_GETRE=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\GETRCODE.HXX"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\objfeld.hxx"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RELLISTE.HXX"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\GETREL.OBJ" : $(SOURCE) $(DEP_CPP_GETRE) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\GETREL.OBJ" : $(SOURCE) $(DEP_CPP_GETRE) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\GETREL.SBR" : $(SOURCE) $(DEP_CPP_GETRE) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\GETREL.OBJ" : $(SOURCE) $(DEP_CPP_GETRE) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GETRIF.CXX
DEP_CPP_GETRI=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\GETRIF.OBJ" : $(SOURCE) $(DEP_CPP_GETRI) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\GETRIF.OBJ" : $(SOURCE) $(DEP_CPP_GETRI) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\GETRIF.SBR" : $(SOURCE) $(DEP_CPP_GETRI) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\GETRIF.OBJ" : $(SOURCE) $(DEP_CPP_GETRI) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GETRIG.CXX
DEP_CPP_GETRIG=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\GETRIG.OBJ" : $(SOURCE) $(DEP_CPP_GETRIG) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\GETRIG.OBJ" : $(SOURCE) $(DEP_CPP_GETRIG) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\GETRIG.SBR" : $(SOURCE) $(DEP_CPP_GETRIG) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\GETRIG.OBJ" : $(SOURCE) $(DEP_CPP_GETRIG) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GETRIL.CXX
DEP_CPP_GETRIL=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\GETRIL.OBJ" : $(SOURCE) $(DEP_CPP_GETRIL) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\GETRIL.OBJ" : $(SOURCE) $(DEP_CPP_GETRIL) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\GETRIL.SBR" : $(SOURCE) $(DEP_CPP_GETRIL) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\GETRIL.OBJ" : $(SOURCE) $(DEP_CPP_GETRIL) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GETRIP.CXX
DEP_CPP_GETRIP=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\GETRIP.OBJ" : $(SOURCE) $(DEP_CPP_GETRIP) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\GETRIP.OBJ" : $(SOURCE) $(DEP_CPP_GETRIP) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\GETRIP.SBR" : $(SOURCE) $(DEP_CPP_GETRIP) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\GETRIP.OBJ" : $(SOURCE) $(DEP_CPP_GETRIP) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GETTEXT.CXX
DEP_CPP_GETTE=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\GETTEXT.OBJ" : $(SOURCE) $(DEP_CPP_GETTE) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\GETTEXT.OBJ" : $(SOURCE) $(DEP_CPP_GETTE) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\GETTEXT.SBR" : $(SOURCE) $(DEP_CPP_GETTE) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\GETTEXT.OBJ" : $(SOURCE) $(DEP_CPP_GETTE) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GETTEXTL.CXX
DEP_CPP_GETTEX=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\GETTEXTL.OBJ" : $(SOURCE) $(DEP_CPP_GETTEX) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\GETTEXTL.OBJ" : $(SOURCE) $(DEP_CPP_GETTEX) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\GETTEXTL.SBR" : $(SOURCE) $(DEP_CPP_GETTEX) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\GETTEXTL.OBJ" : $(SOURCE) $(DEP_CPP_GETTEX) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GETTEXTN.CXX
DEP_CPP_GETTEXT=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\GETTEXTN.OBJ" : $(SOURCE) $(DEP_CPP_GETTEXT) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\GETTEXTN.OBJ" : $(SOURCE) $(DEP_CPP_GETTEXT) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\GETTEXTN.SBR" : $(SOURCE) $(DEP_CPP_GETTEXT) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\GETTEXTN.OBJ" : $(SOURCE) $(DEP_CPP_GETTEXT) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DEL.CXX
DEP_CPP_DEL_C=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\DEL.OBJ" : $(SOURCE) $(DEP_CPP_DEL_C) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\DEL.OBJ" : $(SOURCE) $(DEP_CPP_DEL_C) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\DEL.SBR" : $(SOURCE) $(DEP_CPP_DEL_C) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\DEL.OBJ" : $(SOURCE) $(DEP_CPP_DEL_C) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DELGI.CXX
DEP_CPP_DELGI=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\DELGI.OBJ" : $(SOURCE) $(DEP_CPP_DELGI) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\DELGI.OBJ" : $(SOURCE) $(DEP_CPP_DELGI) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\DELGI.SBR" : $(SOURCE) $(DEP_CPP_DELGI) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\DELGI.OBJ" : $(SOURCE) $(DEP_CPP_DELGI) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DELGIF.CXX
DEP_CPP_DELGIF=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\DELGIF.OBJ" : $(SOURCE) $(DEP_CPP_DELGIF) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\DELGIF.OBJ" : $(SOURCE) $(DEP_CPP_DELGIF) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\DELGIF.SBR" : $(SOURCE) $(DEP_CPP_DELGIF) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\DELGIF.OBJ" : $(SOURCE) $(DEP_CPP_DELGIF) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DELGIL.CXX
DEP_CPP_DELGIL=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\DELGIL.OBJ" : $(SOURCE) $(DEP_CPP_DELGIL) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\DELGIL.OBJ" : $(SOURCE) $(DEP_CPP_DELGIL) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\DELGIL.SBR" : $(SOURCE) $(DEP_CPP_DELGIL) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\DELGIL.OBJ" : $(SOURCE) $(DEP_CPP_DELGIL) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DELGIP.CXX
DEP_CPP_DELGIP=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\DELGIP.OBJ" : $(SOURCE) $(DEP_CPP_DELGIP) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\DELGIP.OBJ" : $(SOURCE) $(DEP_CPP_DELGIP) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\DELGIP.SBR" : $(SOURCE) $(DEP_CPP_DELGIP) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\DELGIP.OBJ" : $(SOURCE) $(DEP_CPP_DELGIP) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DELID.CXX
DEP_CPP_DELID=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\DELID.OBJ" : $(SOURCE) $(DEP_CPP_DELID) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\DELID.OBJ" : $(SOURCE) $(DEP_CPP_DELID) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\DELID.SBR" : $(SOURCE) $(DEP_CPP_DELID) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\DELID.OBJ" : $(SOURCE) $(DEP_CPP_DELID) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DELKAN.CXX
DEP_CPP_DELKA=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\DELKAN.OBJ" : $(SOURCE) $(DEP_CPP_DELKA) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\DELKAN.OBJ" : $(SOURCE) $(DEP_CPP_DELKA) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\DELKAN.SBR" : $(SOURCE) $(DEP_CPP_DELKA) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\DELKAN.OBJ" : $(SOURCE) $(DEP_CPP_DELKA) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DELKANF.CXX
DEP_CPP_DELKAN=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\DELKANF.OBJ" : $(SOURCE) $(DEP_CPP_DELKAN) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\DELKANF.OBJ" : $(SOURCE) $(DEP_CPP_DELKAN) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\DELKANF.SBR" : $(SOURCE) $(DEP_CPP_DELKAN) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\DELKANF.OBJ" : $(SOURCE) $(DEP_CPP_DELKAN) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DELLINK.CXX
DEP_CPP_DELLI=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\DELLINK.OBJ" : $(SOURCE) $(DEP_CPP_DELLI) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\DELLINK.OBJ" : $(SOURCE) $(DEP_CPP_DELLI) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\DELLINK.SBR" : $(SOURCE) $(DEP_CPP_DELLI) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\DELLINK.OBJ" : $(SOURCE) $(DEP_CPP_DELLI) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DELMIN.CXX
DEP_CPP_DELMI=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\DELMIN.OBJ" : $(SOURCE) $(DEP_CPP_DELMI) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\DELMIN.OBJ" : $(SOURCE) $(DEP_CPP_DELMI) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\DELMIN.SBR" : $(SOURCE) $(DEP_CPP_DELMI) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\DELMIN.OBJ" : $(SOURCE) $(DEP_CPP_DELMI) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DELREL.CXX
DEP_CPP_DELRE=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\DELREL.OBJ" : $(SOURCE) $(DEP_CPP_DELRE) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\DELREL.OBJ" : $(SOURCE) $(DEP_CPP_DELRE) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\DELREL.SBR" : $(SOURCE) $(DEP_CPP_DELRE) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\DELREL.OBJ" : $(SOURCE) $(DEP_CPP_DELRE) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DELRELKO.CXX
DEP_CPP_DELREL=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\GETRCODE.HXX"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\objfeld.hxx"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RELLISTE.HXX"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\DELRELKO.OBJ" : $(SOURCE) $(DEP_CPP_DELREL) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\DELRELKO.OBJ" : $(SOURCE) $(DEP_CPP_DELREL) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\DELRELKO.SBR" : $(SOURCE) $(DEP_CPP_DELREL) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\DELRELKO.OBJ" : $(SOURCE) $(DEP_CPP_DELREL) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PUTFOBJ.CXX
DEP_CPP_PUTFO=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\PUTFOBJ.OBJ" : $(SOURCE) $(DEP_CPP_PUTFO) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\PUTFOBJ.OBJ" : $(SOURCE) $(DEP_CPP_PUTFO) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\PUTFOBJ.SBR" : $(SOURCE) $(DEP_CPP_PUTFO) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\PUTFOBJ.OBJ" : $(SOURCE) $(DEP_CPP_PUTFO) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PUTIDENT.CXX
DEP_CPP_PUTID=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\PUTIDENT.OBJ" : $(SOURCE) $(DEP_CPP_PUTID) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\PUTIDENT.OBJ" : $(SOURCE) $(DEP_CPP_PUTID) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\PUTIDENT.SBR" : $(SOURCE) $(DEP_CPP_PUTID) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\PUTIDENT.OBJ" : $(SOURCE) $(DEP_CPP_PUTID) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PUTKOBJ.CXX
DEP_CPP_PUTKO=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\PUTKOBJ.OBJ" : $(SOURCE) $(DEP_CPP_PUTKO) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\PUTKOBJ.OBJ" : $(SOURCE) $(DEP_CPP_PUTKO) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\PUTKOBJ.SBR" : $(SOURCE) $(DEP_CPP_PUTKO) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\PUTKOBJ.OBJ" : $(SOURCE) $(DEP_CPP_PUTKO) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PUTLINK.CXX
DEP_CPP_PUTLI=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\PUTLINK.OBJ" : $(SOURCE) $(DEP_CPP_PUTLI) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\PUTLINK.OBJ" : $(SOURCE) $(DEP_CPP_PUTLI) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\PUTLINK.SBR" : $(SOURCE) $(DEP_CPP_PUTLI) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\PUTLINK.OBJ" : $(SOURCE) $(DEP_CPP_PUTLI) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PUTLOBJ.CXX
DEP_CPP_PUTLO=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\PUTLOBJ.OBJ" : $(SOURCE) $(DEP_CPP_PUTLO) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\PUTLOBJ.OBJ" : $(SOURCE) $(DEP_CPP_PUTLO) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\PUTLOBJ.SBR" : $(SOURCE) $(DEP_CPP_PUTLO) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\PUTLOBJ.OBJ" : $(SOURCE) $(DEP_CPP_PUTLO) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PUTMIT.CXX
DEP_CPP_PUTMI=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\PUTMIT.OBJ" : $(SOURCE) $(DEP_CPP_PUTMI) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\PUTMIT.OBJ" : $(SOURCE) $(DEP_CPP_PUTMI) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\PUTMIT.SBR" : $(SOURCE) $(DEP_CPP_PUTMI) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\PUTMIT.OBJ" : $(SOURCE) $(DEP_CPP_PUTMI) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PUTPKT.CXX
DEP_CPP_PUTPK=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\PUTPKT.OBJ" : $(SOURCE) $(DEP_CPP_PUTPK) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\PUTPKT.OBJ" : $(SOURCE) $(DEP_CPP_PUTPK) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\PUTPKT.SBR" : $(SOURCE) $(DEP_CPP_PUTPK) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\PUTPKT.OBJ" : $(SOURCE) $(DEP_CPP_PUTPK) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PUTPOBJ.CXX
DEP_CPP_PUTPO=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\PUTPOBJ.OBJ" : $(SOURCE) $(DEP_CPP_PUTPO) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\PUTPOBJ.OBJ" : $(SOURCE) $(DEP_CPP_PUTPO) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\PUTPOBJ.SBR" : $(SOURCE) $(DEP_CPP_PUTPO) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\PUTPOBJ.OBJ" : $(SOURCE) $(DEP_CPP_PUTPO) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PUTREL.CXX
DEP_CPP_PUTRE=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\PUTREL.OBJ" : $(SOURCE) $(DEP_CPP_PUTRE) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\PUTREL.OBJ" : $(SOURCE) $(DEP_CPP_PUTRE) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\PUTREL.SBR" : $(SOURCE) $(DEP_CPP_PUTRE) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\PUTREL.OBJ" : $(SOURCE) $(DEP_CPP_PUTRE) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PUTTEMPL.CXX
DEP_CPP_PUTTE=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\PUTTEMPL.OBJ" : $(SOURCE) $(DEP_CPP_PUTTE) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\PUTTEMPL.OBJ" : $(SOURCE) $(DEP_CPP_PUTTE) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\PUTTEMPL.SBR" : $(SOURCE) $(DEP_CPP_PUTTE) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\PUTTEMPL.OBJ" : $(SOURCE) $(DEP_CPP_PUTTE) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PUTTOBJ.CXX
DEP_CPP_PUTTO=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\PUTTOBJ.OBJ" : $(SOURCE) $(DEP_CPP_PUTTO) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\PUTTOBJ.OBJ" : $(SOURCE) $(DEP_CPP_PUTTO) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\PUTTOBJ.SBR" : $(SOURCE) $(DEP_CPP_PUTTO) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\PUTTOBJ.OBJ" : $(SOURCE) $(DEP_CPP_PUTTO) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PUTTXTC.CXX
DEP_CPP_PUTTX=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\PUTTXTC.OBJ" : $(SOURCE) $(DEP_CPP_PUTTX) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\PUTTXTC.OBJ" : $(SOURCE) $(DEP_CPP_PUTTX) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\PUTTXTC.SBR" : $(SOURCE) $(DEP_CPP_PUTTX) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\PUTTXTC.OBJ" : $(SOURCE) $(DEP_CPP_PUTTX) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PUTTXTCN.CXX
DEP_CPP_PUTTXT=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\PUTTXTCN.OBJ" : $(SOURCE) $(DEP_CPP_PUTTXT) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\PUTTXTCN.OBJ" : $(SOURCE) $(DEP_CPP_PUTTXT) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\PUTTXTCN.SBR" : $(SOURCE) $(DEP_CPP_PUTTXT) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\PUTTXTCN.OBJ" : $(SOURCE) $(DEP_CPP_PUTTXT) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MDELKI.CXX
DEP_CPP_MDELK=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\IDTDB.H"\
	{$(INCLUDE)}"\IDTDB001.H"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\MDELKI.OBJ" : $(SOURCE) $(DEP_CPP_MDELK) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\MDELKI.OBJ" : $(SOURCE) $(DEP_CPP_MDELK) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\MDELKI.SBR" : $(SOURCE) $(DEP_CPP_MDELK) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\MDELKI.OBJ" : $(SOURCE) $(DEP_CPP_MDELK) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MDELKM.CXX
DEP_CPP_MDELKM=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\IDTDB.H"\
	{$(INCLUDE)}"\IDTDB001.H"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\MDELKM.OBJ" : $(SOURCE) $(DEP_CPP_MDELKM) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\MDELKM.OBJ" : $(SOURCE) $(DEP_CPP_MDELKM) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\MDELKM.SBR" : $(SOURCE) $(DEP_CPP_MDELKM) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\MDELKM.OBJ" : $(SOURCE) $(DEP_CPP_MDELKM) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MDELKR.CXX
DEP_CPP_MDELKR=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\IDTDB.H"\
	{$(INCLUDE)}"\IDTDB001.H"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\MDELKR.OBJ" : $(SOURCE) $(DEP_CPP_MDELKR) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\MDELKR.OBJ" : $(SOURCE) $(DEP_CPP_MDELKR) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\MDELKR.SBR" : $(SOURCE) $(DEP_CPP_MDELKR) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\MDELKR.OBJ" : $(SOURCE) $(DEP_CPP_MDELKR) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MFIND.CXX
DEP_CPP_MFIND=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\IDTDB.H"\
	{$(INCLUDE)}"\IDTDB001.H"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\MFIND.OBJ" : $(SOURCE) $(DEP_CPP_MFIND) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\MFIND.OBJ" : $(SOURCE) $(DEP_CPP_MFIND) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\MFIND.SBR" : $(SOURCE) $(DEP_CPP_MFIND) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\MFIND.OBJ" : $(SOURCE) $(DEP_CPP_MFIND) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MGETKM.CXX
DEP_CPP_MGETK=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\IDTDB.H"\
	{$(INCLUDE)}"\IDTDB001.H"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\MGETKM.OBJ" : $(SOURCE) $(DEP_CPP_MGETK) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\MGETKM.OBJ" : $(SOURCE) $(DEP_CPP_MGETK) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\MGETKM.SBR" : $(SOURCE) $(DEP_CPP_MGETK) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\MGETKM.OBJ" : $(SOURCE) $(DEP_CPP_MGETK) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MGETKR.CXX
DEP_CPP_MGETKR=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\IDTDB.H"\
	{$(INCLUDE)}"\IDTDB001.H"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\MGETKR.OBJ" : $(SOURCE) $(DEP_CPP_MGETKR) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\MGETKR.OBJ" : $(SOURCE) $(DEP_CPP_MGETKR) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\MGETKR.SBR" : $(SOURCE) $(DEP_CPP_MGETKR) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\MGETKR.OBJ" : $(SOURCE) $(DEP_CPP_MGETKR) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MGETKT.CXX
DEP_CPP_MGETKT=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\IDTDB.H"\
	{$(INCLUDE)}"\IDTDB001.H"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\MGETKT.OBJ" : $(SOURCE) $(DEP_CPP_MGETKT) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\MGETKT.OBJ" : $(SOURCE) $(DEP_CPP_MGETKT) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\MGETKT.SBR" : $(SOURCE) $(DEP_CPP_MGETKT) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\MGETKT.OBJ" : $(SOURCE) $(DEP_CPP_MGETKT) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MGETL.CXX
DEP_CPP_MGETL=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\IDTDB.H"\
	{$(INCLUDE)}"\IDTDB001.H"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\MGETL.OBJ" : $(SOURCE) $(DEP_CPP_MGETL) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\MGETL.OBJ" : $(SOURCE) $(DEP_CPP_MGETL) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\MGETL.SBR" : $(SOURCE) $(DEP_CPP_MGETL) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\MGETL.OBJ" : $(SOURCE) $(DEP_CPP_MGETL) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MGETTX.CXX
DEP_CPP_MGETT=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\IDTDB.H"\
	{$(INCLUDE)}"\IDTDB001.H"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\MGETTX.OBJ" : $(SOURCE) $(DEP_CPP_MGETT) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\MGETTX.OBJ" : $(SOURCE) $(DEP_CPP_MGETT) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\MGETTX.SBR" : $(SOURCE) $(DEP_CPP_MGETT) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\MGETTX.OBJ" : $(SOURCE) $(DEP_CPP_MGETT) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MGETWM.CXX
DEP_CPP_MGETW=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\IDTDB.H"\
	{$(INCLUDE)}"\IDTDB001.H"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\MGETWM.OBJ" : $(SOURCE) $(DEP_CPP_MGETW) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\MGETWM.OBJ" : $(SOURCE) $(DEP_CPP_MGETW) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\MGETWM.SBR" : $(SOURCE) $(DEP_CPP_MGETW) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\MGETWM.OBJ" : $(SOURCE) $(DEP_CPP_MGETW) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MPUTKI.CXX
DEP_CPP_MPUTK=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\IDTDB.H"\
	{$(INCLUDE)}"\IDTDB001.H"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\MPUTKI.OBJ" : $(SOURCE) $(DEP_CPP_MPUTK) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\MPUTKI.OBJ" : $(SOURCE) $(DEP_CPP_MPUTK) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\MPUTKI.SBR" : $(SOURCE) $(DEP_CPP_MPUTK) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\MPUTKI.OBJ" : $(SOURCE) $(DEP_CPP_MPUTK) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MPUTKM.CXX
DEP_CPP_MPUTKM=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\IDTDB.H"\
	{$(INCLUDE)}"\IDTDB001.H"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\MPUTKM.OBJ" : $(SOURCE) $(DEP_CPP_MPUTKM) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\MPUTKM.OBJ" : $(SOURCE) $(DEP_CPP_MPUTKM) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\MPUTKM.SBR" : $(SOURCE) $(DEP_CPP_MPUTKM) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\MPUTKM.OBJ" : $(SOURCE) $(DEP_CPP_MPUTKM) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MPUTKR.CXX
DEP_CPP_MPUTKR=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\IDTDB.H"\
	{$(INCLUDE)}"\IDTDB001.H"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\MPUTKR.OBJ" : $(SOURCE) $(DEP_CPP_MPUTKR) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\MPUTKR.OBJ" : $(SOURCE) $(DEP_CPP_MPUTKR) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\MPUTKR.SBR" : $(SOURCE) $(DEP_CPP_MPUTKR) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\MPUTKR.OBJ" : $(SOURCE) $(DEP_CPP_MPUTKR) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MPUTKT.CXX
DEP_CPP_MPUTKT=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\IDTDB.H"\
	{$(INCLUDE)}"\IDTDB001.H"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\MPUTKT.OBJ" : $(SOURCE) $(DEP_CPP_MPUTKT) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\MPUTKT.OBJ" : $(SOURCE) $(DEP_CPP_MPUTKT) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\MPUTKT.SBR" : $(SOURCE) $(DEP_CPP_MPUTKT) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\MPUTKT.OBJ" : $(SOURCE) $(DEP_CPP_MPUTKT) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MPUTTX.CXX
DEP_CPP_MPUTT=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\IDTDB.H"\
	{$(INCLUDE)}"\IDTDB001.H"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\MPUTTX.OBJ" : $(SOURCE) $(DEP_CPP_MPUTT) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\MPUTTX.OBJ" : $(SOURCE) $(DEP_CPP_MPUTT) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\MPUTTX.SBR" : $(SOURCE) $(DEP_CPP_MPUTT) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\MPUTTX.OBJ" : $(SOURCE) $(DEP_CPP_MPUTT) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PBD.CXX
DEP_CPP_PBD_C=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\PBDIDS.HXX"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MERKMAL.HXX"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\PBD.HXX"\
	{$(INCLUDE)}"\PBDDB.H"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\SWITCHKC.H"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\PBD.OBJ" : $(SOURCE) $(DEP_CPP_PBD_C) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\PBD.OBJ" : $(SOURCE) $(DEP_CPP_PBD_C) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\PBD.SBR" : $(SOURCE) $(DEP_CPP_PBD_C) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\PBD.OBJ" : $(SOURCE) $(DEP_CPP_PBD_C) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PBDIDS.CXX
DEP_CPP_PBDID=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\PBDIDS.HXX"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\PBD.HXX"\
	{$(INCLUDE)}"\PBDDB.H"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\PBDIDS.OBJ" : $(SOURCE) $(DEP_CPP_PBDID) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\PBDIDS.OBJ" : $(SOURCE) $(DEP_CPP_PBDID) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\PBDIDS.SBR" : $(SOURCE) $(DEP_CPP_PBDID) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\PBDIDS.OBJ" : $(SOURCE) $(DEP_CPP_PBDID) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PBDTEMP.CXX
DEP_CPP_PBDTE=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\PBD.HXX"\
	{$(INCLUDE)}"\PBDDB.H"\
	{$(INCLUDE)}"\PBDTEMP.HXX"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\PBDTEMP.OBJ" : $(SOURCE) $(DEP_CPP_PBDTE) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\PBDTEMP.OBJ" : $(SOURCE) $(DEP_CPP_PBDTE) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\PBDTEMP.SBR" : $(SOURCE) $(DEP_CPP_PBDTE) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\PBDTEMP.OBJ" : $(SOURCE) $(DEP_CPP_PBDTE) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FREETEXT.CXX
DEP_CPP_FREET=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\IDTDB.H"\
	{$(INCLUDE)}"\IDTDB001.H"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\FREETEXT.OBJ" : $(SOURCE) $(DEP_CPP_FREET) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\FREETEXT.OBJ" : $(SOURCE) $(DEP_CPP_FREET) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\FREETEXT.SBR" : $(SOURCE) $(DEP_CPP_FREET) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\FREETEXT.OBJ" : $(SOURCE) $(DEP_CPP_FREET) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FINDREL.CXX
DEP_CPP_FINDR=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\FINDREL.OBJ" : $(SOURCE) $(DEP_CPP_FINDR) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\FINDREL.OBJ" : $(SOURCE) $(DEP_CPP_FINDR) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\FINDREL.SBR" : $(SOURCE) $(DEP_CPP_FINDR) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\FINDREL.OBJ" : $(SOURCE) $(DEP_CPP_FINDR) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FNDGI.CXX
DEP_CPP_FNDGI=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\FNDGI.OBJ" : $(SOURCE) $(DEP_CPP_FNDGI) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\FNDGI.OBJ" : $(SOURCE) $(DEP_CPP_FNDGI) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\FNDGI.SBR" : $(SOURCE) $(DEP_CPP_FNDGI) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\FNDGI.OBJ" : $(SOURCE) $(DEP_CPP_FNDGI) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FNDKA.CXX
DEP_CPP_FNDKA=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\FNDKA.OBJ" : $(SOURCE) $(DEP_CPP_FNDKA) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\FNDKA.OBJ" : $(SOURCE) $(DEP_CPP_FNDKA) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\FNDKA.SBR" : $(SOURCE) $(DEP_CPP_FNDKA) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\FNDKA.OBJ" : $(SOURCE) $(DEP_CPP_FNDKA) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FNDLI.CXX
DEP_CPP_FNDLI=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\FNDLI.OBJ" : $(SOURCE) $(DEP_CPP_FNDLI) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\FNDLI.OBJ" : $(SOURCE) $(DEP_CPP_FNDLI) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\FNDLI.SBR" : $(SOURCE) $(DEP_CPP_FNDLI) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\FNDLI.OBJ" : $(SOURCE) $(DEP_CPP_FNDLI) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FNDMA.CXX
DEP_CPP_FNDMA=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\FNDMA.OBJ" : $(SOURCE) $(DEP_CPP_FNDMA) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\FNDMA.OBJ" : $(SOURCE) $(DEP_CPP_FNDMA) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\FNDMA.SBR" : $(SOURCE) $(DEP_CPP_FNDMA) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\FNDMA.OBJ" : $(SOURCE) $(DEP_CPP_FNDMA) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FNDPU.CXX
DEP_CPP_FNDPU=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\FNDPU.OBJ" : $(SOURCE) $(DEP_CPP_FNDPU) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\FNDPU.OBJ" : $(SOURCE) $(DEP_CPP_FNDPU) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\FNDPU.SBR" : $(SOURCE) $(DEP_CPP_FNDPU) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\FNDPU.OBJ" : $(SOURCE) $(DEP_CPP_FNDPU) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FNDTXT.CXX
DEP_CPP_FNDTX=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\FNDTXT.OBJ" : $(SOURCE) $(DEP_CPP_FNDTX) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\FNDTXT.OBJ" : $(SOURCE) $(DEP_CPP_FNDTX) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\FNDTXT.SBR" : $(SOURCE) $(DEP_CPP_FNDTX) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\FNDTXT.OBJ" : $(SOURCE) $(DEP_CPP_FNDTX) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FNDTXTN.CXX
DEP_CPP_FNDTXT=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\memory"\
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
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rawiter.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.h"\
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
	{$(INCLUDE)}"\ospace\utility\autoptr.h"\
	{$(INCLUDE)}"\ospace\utility\autoptr.org.h"\
	{$(INCLUDE)}"\ospace\utility\autores.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\FNDTXTN.OBJ" : $(SOURCE) $(DEP_CPP_FNDTXT) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\FNDTXTN.OBJ" : $(SOURCE) $(DEP_CPP_FNDTXT) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\FNDTXTN.SBR" : $(SOURCE) $(DEP_CPP_FNDTXT) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\FNDTXTN.OBJ" : $(SOURCE) $(DEP_CPP_FNDTXT) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\HTFUNC.CXX
DEP_CPP_HTFUN=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\HTFUNC.OBJ" : $(SOURCE) $(DEP_CPP_HTFUN) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\HTFUNC.OBJ" : $(SOURCE) $(DEP_CPP_HTFUN) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\HTFUNC.SBR" : $(SOURCE) $(DEP_CPP_HTFUN) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\HTFUNC.OBJ" : $(SOURCE) $(DEP_CPP_HTFUN) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\HTMANR.CXX
DEP_CPP_HTMAN=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\HTMANR.OBJ" : $(SOURCE) $(DEP_CPP_HTMAN) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\HTMANR.OBJ" : $(SOURCE) $(DEP_CPP_HTMAN) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\HTMANR.SBR" : $(SOURCE) $(DEP_CPP_HTMAN) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\HTMANR.OBJ" : $(SOURCE) $(DEP_CPP_HTMAN) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\IGLAGE.CXX
DEP_CPP_IGLAG=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\IGLAGE.OBJ" : $(SOURCE) $(DEP_CPP_IGLAG) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\IGLAGE.OBJ" : $(SOURCE) $(DEP_CPP_IGLAG) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\IGLAGE.SBR" : $(SOURCE) $(DEP_CPP_IGLAG) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\IGLAGE.OBJ" : $(SOURCE) $(DEP_CPP_IGLAG) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\IGPTNL.CXX
DEP_CPP_IGPTN=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\IGPTNL.OBJ" : $(SOURCE) $(DEP_CPP_IGPTN) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\IGPTNL.OBJ" : $(SOURCE) $(DEP_CPP_IGPTN) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\IGPTNL.SBR" : $(SOURCE) $(DEP_CPP_IGPTN) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\IGPTNL.OBJ" : $(SOURCE) $(DEP_CPP_IGPTN) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ISALIKE.CXX
DEP_CPP_ISALI=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\ISALIKE.OBJ" : $(SOURCE) $(DEP_CPP_ISALI) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\ISALIKE.OBJ" : $(SOURCE) $(DEP_CPP_ISALI) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\ISALIKE.SBR" : $(SOURCE) $(DEP_CPP_ISALI) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\ISALIKE.OBJ" : $(SOURCE) $(DEP_CPP_ISALI) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PUINFL.CXX
DEP_CPP_PUINF=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\PUINFL.OBJ" : $(SOURCE) $(DEP_CPP_PUINF) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\PUINFL.OBJ" : $(SOURCE) $(DEP_CPP_PUINF) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\PUINFL.SBR" : $(SOURCE) $(DEP_CPP_PUINF) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\PUINFL.OBJ" : $(SOURCE) $(DEP_CPP_PUINF) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\QTFUNC.CXX
DEP_CPP_QTFUN=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\QTFUNC.OBJ" : $(SOURCE) $(DEP_CPP_QTFUN) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\QTFUNC.OBJ" : $(SOURCE) $(DEP_CPP_QTFUN) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\QTFUNC.SBR" : $(SOURCE) $(DEP_CPP_QTFUN) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\QTFUNC.OBJ" : $(SOURCE) $(DEP_CPP_QTFUN) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\RIGIN.CXX
DEP_CPP_RIGIN=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\RIGIN.OBJ" : $(SOURCE) $(DEP_CPP_RIGIN) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\RIGIN.OBJ" : $(SOURCE) $(DEP_CPP_RIGIN) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\RIGIN.SBR" : $(SOURCE) $(DEP_CPP_RIGIN) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\RIGIN.OBJ" : $(SOURCE) $(DEP_CPP_RIGIN) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\RIGINFO.CXX
DEP_CPP_RIGINF=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\objfeld.hxx"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\PBD.HXX"\
	{$(INCLUDE)}"\PBDDB.H"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\RIGINFO.OBJ" : $(SOURCE) $(DEP_CPP_RIGINF) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\RIGINFO.OBJ" : $(SOURCE) $(DEP_CPP_RIGINF) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\RIGINFO.SBR" : $(SOURCE) $(DEP_CPP_RIGINF) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\RIGINFO.OBJ" : $(SOURCE) $(DEP_CPP_RIGINF) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\RIGKP.CXX
DEP_CPP_RIGKP=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\RIGKP.OBJ" : $(SOURCE) $(DEP_CPP_RIGKP) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\RIGKP.OBJ" : $(SOURCE) $(DEP_CPP_RIGKP) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\RIGKP.SBR" : $(SOURCE) $(DEP_CPP_RIGKP) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\RIGKP.OBJ" : $(SOURCE) $(DEP_CPP_RIGKP) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\STINFL.CXX
DEP_CPP_STINF=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\STINFL.OBJ" : $(SOURCE) $(DEP_CPP_STINF) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\STINFL.OBJ" : $(SOURCE) $(DEP_CPP_STINF) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\STINFL.SBR" : $(SOURCE) $(DEP_CPP_STINF) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\STINFL.OBJ" : $(SOURCE) $(DEP_CPP_STINF) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\OVLFOBJ.CXX
DEP_CPP_OVLFO=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\OVLFOBJ.OBJ" : $(SOURCE) $(DEP_CPP_OVLFO) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\OVLFOBJ.OBJ" : $(SOURCE) $(DEP_CPP_OVLFO) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\OVLFOBJ.SBR" : $(SOURCE) $(DEP_CPP_OVLFO) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\OVLFOBJ.OBJ" : $(SOURCE) $(DEP_CPP_OVLFO) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\OVLLOBJ.CXX
DEP_CPP_OVLLO=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\OVLLOBJ.OBJ" : $(SOURCE) $(DEP_CPP_OVLLO) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\OVLLOBJ.OBJ" : $(SOURCE) $(DEP_CPP_OVLLO) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\OVLLOBJ.SBR" : $(SOURCE) $(DEP_CPP_OVLLO) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\OVLLOBJ.OBJ" : $(SOURCE) $(DEP_CPP_OVLLO) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\OVLPOBJ.CXX
DEP_CPP_OVLPO=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\OVLPOBJ.OBJ" : $(SOURCE) $(DEP_CPP_OVLPO) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\OVLPOBJ.OBJ" : $(SOURCE) $(DEP_CPP_OVLPO) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\OVLPOBJ.SBR" : $(SOURCE) $(DEP_CPP_OVLPO) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\OVLPOBJ.OBJ" : $(SOURCE) $(DEP_CPP_OVLPO) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ATTRIBS.CXX
DEP_CPP_ATTRI=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBADDR.HXX"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\Kons.hxx"\
	{$(INCLUDE)}"\KONSOBJ.HXX"\
	{$(INCLUDE)}"\KONSSATZ.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\ATTRIBS.OBJ" : $(SOURCE) $(DEP_CPP_ATTRI) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\ATTRIBS.OBJ" : $(SOURCE) $(DEP_CPP_ATTRI) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\ATTRIBS.SBR" : $(SOURCE) $(DEP_CPP_ATTRI) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\ATTRIBS.OBJ" : $(SOURCE) $(DEP_CPP_ATTRI) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\VISERROR.CXX
DEP_CPP_VISER=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\VISERROR.HXX"\
	{$(INCLUDE)}"\VISERROR.INL"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\VISERROR.OBJ" : $(SOURCE) $(DEP_CPP_VISER) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\VISERROR.OBJ" : $(SOURCE) $(DEP_CPP_VISER) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\VISERROR.SBR" : $(SOURCE) $(DEP_CPP_VISER) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\VISERROR.OBJ" : $(SOURCE) $(DEP_CPP_VISER) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\VISINFO.CXX
DEP_CPP_VISIN=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\VISINFO.OBJ" : $(SOURCE) $(DEP_CPP_VISIN) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\VISINFO.OBJ" : $(SOURCE) $(DEP_CPP_VISIN) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\VISINFO.SBR" : $(SOURCE) $(DEP_CPP_VISIN) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\VISINFO.OBJ" : $(SOURCE) $(DEP_CPP_VISIN) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\IDENT.CXX

!IF  "$(CFG)" == "Trias322 - Win32 Release"

DEP_CPP_IDENT=\
	".\trias02p.hxx"\
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
	{$(INCLUDE)}"\EFONT.HXX"\
	{$(INCLUDE)}"\EPEN.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\Ident.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
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
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\PBD.HXX"\
	{$(INCLUDE)}"\PBDDB.H"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VISERROR.HXX"\
	{$(INCLUDE)}"\VISERROR.INL"\
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
	

"$(INTDIR)\IDENT.OBJ" : $(SOURCE) $(DEP_CPP_IDENT) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"

DEP_CPP_IDENT=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\EFONT.HXX"\
	{$(INCLUDE)}"\EPEN.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ident.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
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
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\PBD.HXX"\
	{$(INCLUDE)}"\PBDDB.H"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\VISERROR.HXX"\
	{$(INCLUDE)}"\VISERROR.INL"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

"$(INTDIR)\IDENT.OBJ" : $(SOURCE) $(DEP_CPP_IDENT) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\IDENT.SBR" : $(SOURCE) $(DEP_CPP_IDENT) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"

DEP_CPP_IDENT=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\EFONT.HXX"\
	{$(INCLUDE)}"\EPEN.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ident.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
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
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\PBD.HXX"\
	{$(INCLUDE)}"\PBDDB.H"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\VISERROR.HXX"\
	{$(INCLUDE)}"\VISERROR.INL"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

"$(INTDIR)\IDENT.OBJ" : $(SOURCE) $(DEP_CPP_IDENT) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PALETTE.CXX
DEP_CPP_PALET=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\PALETTE.HXX"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\PALETTE.OBJ" : $(SOURCE) $(DEP_CPP_PALET) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\PALETTE.OBJ" : $(SOURCE) $(DEP_CPP_PALET) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\PALETTE.SBR" : $(SOURCE) $(DEP_CPP_PALET) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\PALETTE.OBJ" : $(SOURCE) $(DEP_CPP_PALET) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\EFONT.CXX
DEP_CPP_EFONT=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\FONTSEL.H"\
	".\TRIAS02.H"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\EFONT.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Printer.hxx"\
	{$(INCLUDE)}"\prntpars.hxx"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TRIAS03M.HXX"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\EFONT.OBJ" : $(SOURCE) $(DEP_CPP_EFONT) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\EFONT.OBJ" : $(SOURCE) $(DEP_CPP_EFONT) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\EFONT.SBR" : $(SOURCE) $(DEP_CPP_EFONT) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\EFONT.OBJ" : $(SOURCE) $(DEP_CPP_EFONT) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\EPEN.CXX
DEP_CPP_EPEN_=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\EPEN.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\EPEN.OBJ" : $(SOURCE) $(DEP_CPP_EPEN_) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\EPEN.OBJ" : $(SOURCE) $(DEP_CPP_EPEN_) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\EPEN.SBR" : $(SOURCE) $(DEP_CPP_EPEN_) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\EPEN.OBJ" : $(SOURCE) $(DEP_CPP_EPEN_) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GEO_OBJ.CXX
DEP_CPP_GEO_O=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\GEO_OBJ.OBJ" : $(SOURCE) $(DEP_CPP_GEO_O) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\GEO_OBJ.OBJ" : $(SOURCE) $(DEP_CPP_GEO_O) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\GEO_OBJ.SBR" : $(SOURCE) $(DEP_CPP_GEO_O) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\GEO_OBJ.OBJ" : $(SOURCE) $(DEP_CPP_GEO_O) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GEO_OBJ1.CXX
DEP_CPP_GEO_OB=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\GERADE.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\GEO_OBJ1.OBJ" : $(SOURCE) $(DEP_CPP_GEO_OB) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\GEO_OBJ1.OBJ" : $(SOURCE) $(DEP_CPP_GEO_OB) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\GEO_OBJ1.SBR" : $(SOURCE) $(DEP_CPP_GEO_OB) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\GEO_OBJ1.OBJ" : $(SOURCE) $(DEP_CPP_GEO_OB) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GEOTEXT.CXX

!IF  "$(CFG)" == "Trias322 - Win32 Release"

DEP_CPP_GEOTE=\
	".\Strings.h"\
	".\TRIAS02.H"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\xtsnguid.h"\
	

"$(INTDIR)\GEOTEXT.OBJ" : $(SOURCE) $(DEP_CPP_GEOTE) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"

DEP_CPP_GEOTE=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\Strings.h"\
	".\TRIAS02.H"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

"$(INTDIR)\GEOTEXT.OBJ" : $(SOURCE) $(DEP_CPP_GEOTE) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\GEOTEXT.SBR" : $(SOURCE) $(DEP_CPP_GEOTE) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"

DEP_CPP_GEOTE=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\Strings.h"\
	".\TRIAS02.H"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

"$(INTDIR)\GEOTEXT.OBJ" : $(SOURCE) $(DEP_CPP_GEOTE) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\KOMPLEX.CXX
DEP_CPP_KOMPL=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\GETRCODE.HXX"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\objfeld.hxx"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\KOMPLEX.OBJ" : $(SOURCE) $(DEP_CPP_KOMPL) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\KOMPLEX.OBJ" : $(SOURCE) $(DEP_CPP_KOMPL) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\KOMPLEX.SBR" : $(SOURCE) $(DEP_CPP_KOMPL) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\KOMPLEX.OBJ" : $(SOURCE) $(DEP_CPP_KOMPL) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GERADE.CXX
DEP_CPP_GERAD=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\GERADE.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\GERADE.OBJ" : $(SOURCE) $(DEP_CPP_GERAD) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\GERADE.OBJ" : $(SOURCE) $(DEP_CPP_GERAD) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\GERADE.SBR" : $(SOURCE) $(DEP_CPP_GERAD) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\GERADE.OBJ" : $(SOURCE) $(DEP_CPP_GERAD) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\OBJMTREE.CXX
DEP_CPP_OBJMT=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OBJMTREE.HXX"\
	{$(INCLUDE)}"\OBJMTREE.INL"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\OBJMTREE.OBJ" : $(SOURCE) $(DEP_CPP_OBJMT) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\OBJMTREE.OBJ" : $(SOURCE) $(DEP_CPP_OBJMT) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\OBJMTREE.SBR" : $(SOURCE) $(DEP_CPP_OBJMT) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\OBJMTREE.OBJ" : $(SOURCE) $(DEP_CPP_OBJMT) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\OLISTE.CXX
DEP_CPP_OLIST=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ident.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\LISTOBJ.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\objfeld.hxx"\
	{$(INCLUDE)}"\Objliste.hxx"\
	{$(INCLUDE)}"\OBJMTREE.HXX"\
	{$(INCLUDE)}"\OBJMTREE.INL"\
	{$(INCLUDE)}"\OBJSTAT.HXX"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
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
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\Transfrm.hxx"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\XTENSND.H"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\OLISTE.OBJ" : $(SOURCE) $(DEP_CPP_OLIST) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\OLISTE.OBJ" : $(SOURCE) $(DEP_CPP_OLIST) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\OLISTE.SBR" : $(SOURCE) $(DEP_CPP_OLIST) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\OLISTE.OBJ" : $(SOURCE) $(DEP_CPP_OLIST) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\RECT.CXX
DEP_CPP_RECT_=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RECT.HXX"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\RECT.OBJ" : $(SOURCE) $(DEP_CPP_RECT_) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\RECT.OBJ" : $(SOURCE) $(DEP_CPP_RECT_) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\RECT.SBR" : $(SOURCE) $(DEP_CPP_RECT_) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\RECT.OBJ" : $(SOURCE) $(DEP_CPP_RECT_) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DBGETGI.CXX
DEP_CPP_DBGET=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBADDR.HXX"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Hdrentry.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\Kons.hxx"\
	{$(INCLUDE)}"\KONSOBJ.HXX"\
	{$(INCLUDE)}"\KONSSATZ.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\SWITCHKC.H"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\DBGETGI.OBJ" : $(SOURCE) $(DEP_CPP_DBGET) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\DBGETGI.OBJ" : $(SOURCE) $(DEP_CPP_DBGET) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\DBGETGI.SBR" : $(SOURCE) $(DEP_CPP_DBGET) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\DBGETGI.OBJ" : $(SOURCE) $(DEP_CPP_DBGET) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GIWINDOW.CXX
DEP_CPP_GIWIN=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\FUNCTIONAL"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ident.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ITERATOR"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\LISTOBJ.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\objfeld.hxx"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\string"\
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
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\SET"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XTREE"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\GIWINDOW.OBJ" : $(SOURCE) $(DEP_CPP_GIWIN) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\GIWINDOW.OBJ" : $(SOURCE) $(DEP_CPP_GIWIN) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\GIWINDOW.SBR" : $(SOURCE) $(DEP_CPP_GIWIN) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\GIWINDOW.OBJ" : $(SOURCE) $(DEP_CPP_GIWIN) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MERKINFO.CXX
DEP_CPP_MERKI=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\MERKINFO.HXX"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\MERKINFO.OBJ" : $(SOURCE) $(DEP_CPP_MERKI) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\MERKINFO.OBJ" : $(SOURCE) $(DEP_CPP_MERKI) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\MERKINFO.SBR" : $(SOURCE) $(DEP_CPP_MERKI) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\MERKINFO.OBJ" : $(SOURCE) $(DEP_CPP_MERKI) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MERKMAL.CXX
DEP_CPP_MERKM=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\MERKINFO.HXX"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MERKMAL.HXX"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\PBD.HXX"\
	{$(INCLUDE)}"\PBDDB.H"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\MERKMAL.OBJ" : $(SOURCE) $(DEP_CPP_MERKM) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\MERKMAL.OBJ" : $(SOURCE) $(DEP_CPP_MERKM) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\MERKMAL.SBR" : $(SOURCE) $(DEP_CPP_MERKM) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\MERKMAL.OBJ" : $(SOURCE) $(DEP_CPP_MERKM) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MODID.CXX
DEP_CPP_MODID=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\MODID.OBJ" : $(SOURCE) $(DEP_CPP_MODID) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\MODID.OBJ" : $(SOURCE) $(DEP_CPP_MODID) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\MODID.SBR" : $(SOURCE) $(DEP_CPP_MODID) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\MODID.OBJ" : $(SOURCE) $(DEP_CPP_MODID) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\RELATIO.CXX
DEP_CPP_RELAT=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\GETRCODE.HXX"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\objfeld.hxx"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RELLISTE.HXX"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\SWITCHKC.H"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\RELATIO.OBJ" : $(SOURCE) $(DEP_CPP_RELAT) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\RELATIO.OBJ" : $(SOURCE) $(DEP_CPP_RELAT) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\RELATIO.SBR" : $(SOURCE) $(DEP_CPP_RELAT) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\RELATIO.OBJ" : $(SOURCE) $(DEP_CPP_RELAT) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\obj32\Trias322.RC
DEP_RSC_TRIAS3=\
	".\obj32\FONTSEL.H"\
	".\obj32\RES\Deinstal.ico"\
	".\obj32\TRIAS322.RCV"\
	{$(INCLUDE)}"\RESSTRG.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\Trias322.res" : $(SOURCE) $(DEP_RSC_TRIAS3) "$(INTDIR)"
   $(RSC) /l 0x407 /fo"$(INTDIR)/Trias322.res" /i "obj32" /d "NDEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\Trias322.res" : $(SOURCE) $(DEP_RSC_TRIAS3) "$(INTDIR)"
   $(RSC) /l 0x407 /fo"$(INTDIR)/Trias322.res" /i "obj32" /d "_DEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\Trias322.res" : $(SOURCE) $(DEP_RSC_TRIAS3) "$(INTDIR)"
   $(RSC) /l 0x407 /fo"$(INTDIR)/Trias322.res" /i "obj32" /d "NDEBUG" $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\obj32\TRIAS32D.DEF

!IF  "$(CFG)" == "Trias322 - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"

!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\obj32\TRIAS322.DEF

!IF  "$(CFG)" == "Trias322 - Win32 Release"

# PROP Exclude_From_Build 0

!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"

# PROP BASE Exclude_From_Build 0
# PROP Exclude_From_Build 0

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ObjGuid.cpp
DEP_CPP_OBJGU=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\ObjGuid.obj" : $(SOURCE) $(DEP_CPP_OBJGU) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\ObjGuid.obj" : $(SOURCE) $(DEP_CPP_OBJGU) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\ObjGuid.sbr" : $(SOURCE) $(DEP_CPP_OBJGU) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\ObjGuid.obj" : $(SOURCE) $(DEP_CPP_OBJGU) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Strings.cpp
DEP_CPP_STRIN=\
	"..\Include.207\dbconfig.h"\
	"..\Include.207\errtypes.h"\
	"..\Include.207\routines.h"\
	".\Strings.h"\
	".\trias02p.hxx"\
	{$(INCLUDE)}"\Attribs.hxx"\
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
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CTF.HXX"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\Db.hxx"\
	{$(INCLUDE)}"\DBASRT02.H"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Dbtypes.h"\
	{$(INCLUDE)}"\defattr.h"\
	{$(INCLUDE)}"\DLLBIND.HXX"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\ERRDEF.H"\
	{$(INCLUDE)}"\ERRINST.HXX"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Fprotos.h"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Geo_obj.hxx"\
	{$(INCLUDE)}"\GEO_OBJ1.HXX"\
	{$(INCLUDE)}"\GEOTEXT.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\KOMPLEX.HXX"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\MPROTOS.H"\
	{$(INCLUDE)}"\NEW"\
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
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Risdb.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\visinfo.hxx"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	{$(INCLUDE)}"\ZFORC.H"\
	{$(INCLUDE)}"\ZIPEDB.H"\
	{$(INCLUDE)}"\ZPROTOS.H"\
	

!IF  "$(CFG)" == "Trias322 - Win32 Release"


"$(INTDIR)\Strings.obj" : $(SOURCE) $(DEP_CPP_STRIN) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"


"$(INTDIR)\Strings.obj" : $(SOURCE) $(DEP_CPP_STRIN) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"

"$(INTDIR)\Strings.sbr" : $(SOURCE) $(DEP_CPP_STRIN) "$(INTDIR)"\
 "$(INTDIR)\trias322d.pch"


!ELSEIF  "$(CFG)" == "Trias322 - Win32 Pseudo Debug"


"$(INTDIR)\Strings.obj" : $(SOURCE) $(DEP_CPP_STRIN) "$(INTDIR)"\
 "$(INTDIR)\Trias422.pch"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
