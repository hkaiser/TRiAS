# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=Trias321 - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Trias321 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Trias321 - Win32 Release" && "$(CFG)" !=\
 "Trias321 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Trias421.mak" CFG="Trias321 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Trias321 - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Trias321 - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "Trias321 - Win32 Debug"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "Trias321 - Win32 Release"

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
OutDir=.\Release
TargetName=Trias321
# End Custom Macros

ALL : "$(OUTDIR)\Trias321.dll" "c:\trias.mvc\trias200.rel\Trias321.dll"\
 "..\lib32\Release\Trias321.lib"

CLEAN : 
	-@erase "$(INTDIR)\ACTIVATE.OBJ"
	-@erase "$(INTDIR)\ASMBUF.OBJ"
	-@erase "$(INTDIR)\BAKKEY.OBJ"
	-@erase "$(INTDIR)\BITS.OBJ"
	-@erase "$(INTDIR)\COMBIN.OBJ"
	-@erase "$(INTDIR)\CRYPT.OBJ"
	-@erase "$(INTDIR)\CUBE.OBJ"
	-@erase "$(INTDIR)\DB_IO.OBJ"
	-@erase "$(INTDIR)\DBCLOSE.OBJ"
	-@erase "$(INTDIR)\DBCODB.OBJ"
	-@erase "$(INTDIR)\DBD.OBJ"
	-@erase "$(INTDIR)\DBINITC.OBJ"
	-@erase "$(INTDIR)\DBOPEN.OBJ"
	-@erase "$(INTDIR)\DELETE.OBJ"
	-@erase "$(INTDIR)\DELHD_F.OBJ"
	-@erase "$(INTDIR)\DIO_INIT.OBJ"
	-@erase "$(INTDIR)\eexterr.obj"
	-@erase "$(INTDIR)\EINVADDR.OBJ"
	-@erase "$(INTDIR)\enfnderr.obj"
	-@erase "$(INTDIR)\ENOMEM.OBJ"
	-@erase "$(INTDIR)\enospac.obj"
	-@erase "$(INTDIR)\ERRFKT.OBJ"
	-@erase "$(INTDIR)\EVISERR.OBJ"
	-@erase "$(INTDIR)\FDBCLOSE.OBJ"
	-@erase "$(INTDIR)\FDBOPEN.OBJ"
	-@erase "$(INTDIR)\FLEX.OBJ"
	-@erase "$(INTDIR)\GENBACK.OBJ"
	-@erase "$(INTDIR)\GETDWENT.OBJ"
	-@erase "$(INTDIR)\GETDWNAM.OBJ"
	-@erase "$(INTDIR)\GETDWUID.OBJ"
	-@erase "$(INTDIR)\GETHD_F.OBJ"
	-@erase "$(INTDIR)\GETHDLEN.OBJ"
	-@erase "$(INTDIR)\GETPATH.OBJ"
	-@erase "$(INTDIR)\HTCONT.OBJ"
	-@erase "$(INTDIR)\HTDEL.OBJ"
	-@erase "$(INTDIR)\HTINS.OBJ"
	-@erase "$(INTDIR)\HTPREP.OBJ"
	-@erase "$(INTDIR)\HTSEARCH.OBJ"
	-@erase "$(INTDIR)\HTSHRINK.OBJ"
	-@erase "$(INTDIR)\HTSPLIT.OBJ"
	-@erase "$(INTDIR)\HTWIND_F.OBJ"
	-@erase "$(INTDIR)\HTWINDOW.OBJ"
	-@erase "$(INTDIR)\INITTAB.OBJ"
	-@erase "$(INTDIR)\INSERT.OBJ"
	-@erase "$(INTDIR)\KEY_IO.OBJ"
	-@erase "$(INTDIR)\KEYCAT.OBJ"
	-@erase "$(INTDIR)\KEYCMP.OBJ"
	-@erase "$(INTDIR)\KEYDEL.OBJ"
	-@erase "$(INTDIR)\KEYFRST.OBJ"
	-@erase "$(INTDIR)\KEYINI.OBJ"
	-@erase "$(INTDIR)\KEYINS.OBJ"
	-@erase "$(INTDIR)\KEYLAST.OBJ"
	-@erase "$(INTDIR)\KEYLOC.OBJ"
	-@erase "$(INTDIR)\KEYNEXT.OBJ"
	-@erase "$(INTDIR)\KEYPREV.OBJ"
	-@erase "$(INTDIR)\KEYREAD.OBJ"
	-@erase "$(INTDIR)\KEYUTIL.OBJ"
	-@erase "$(INTDIR)\LADRC.OBJ"
	-@erase "$(INTDIR)\LIBMAIN1.OBJ"
	-@erase "$(INTDIR)\LISTEN.OBJ"
	-@erase "$(INTDIR)\LOCATE.OBJ"
	-@erase "$(INTDIR)\LOCFRST.OBJ"
	-@erase "$(INTDIR)\LOCLAST.OBJ"
	-@erase "$(INTDIR)\LOCSLT.OBJ"
	-@erase "$(INTDIR)\MYCRYPT.OBJ"
	-@erase "$(INTDIR)\NEWFILE.OBJ"
	-@erase "$(INTDIR)\NGMC.OBJ"
	-@erase "$(INTDIR)\NODEXP.OBJ"
	-@erase "$(INTDIR)\NODFIL.OBJ"
	-@erase "$(INTDIR)\NODSPL.OBJ"
	-@erase "$(INTDIR)\NULLCMP.OBJ"
	-@erase "$(INTDIR)\OVERFL.OBJ"
	-@erase "$(INTDIR)\PARENT.OBJ"
	-@erase "$(INTDIR)\PGZERO.OBJ"
	-@erase "$(INTDIR)\PUTHD_F.OBJ"
	-@erase "$(INTDIR)\PUTINL.OBJ"
	-@erase "$(INTDIR)\QTCONT.OBJ"
	-@erase "$(INTDIR)\QTDEL.OBJ"
	-@erase "$(INTDIR)\QTINS.OBJ"
	-@erase "$(INTDIR)\QTPREP.OBJ"
	-@erase "$(INTDIR)\QTSEARCH.OBJ"
	-@erase "$(INTDIR)\QTSHRINK.OBJ"
	-@erase "$(INTDIR)\QTSPLIT.OBJ"
	-@erase "$(INTDIR)\QTWIND_F.OBJ"
	-@erase "$(INTDIR)\QTWINDOW.OBJ"
	-@erase "$(INTDIR)\QUAD.OBJ"
	-@erase "$(INTDIR)\REINDEX.OBJ"
	-@erase "$(INTDIR)\RESOURCE.OBJ"
	-@erase "$(INTDIR)\ROOTSP.OBJ"
	-@erase "$(INTDIR)\SETERR.OBJ"
	-@erase "$(INTDIR)\SHRINK.OBJ"
	-@erase "$(INTDIR)\STATIST.OBJ"
	-@erase "$(INTDIR)\STRFCNS.OBJ"
	-@erase "$(INTDIR)\STRNCHR.OBJ"
	-@erase "$(INTDIR)\SWITCHKC.OBJ"
	-@erase "$(INTDIR)\TARGETFI.OBJ"
	-@erase "$(INTDIR)\TLOCSLT.OBJ"
	-@erase "$(INTDIR)\TPUTINL.OBJ"
	-@erase "$(INTDIR)\TRIAS01P.OBJ"
	-@erase "$(INTDIR)\Trias321.pch"
	-@erase "$(INTDIR)\Trias321.res"
	-@erase "$(INTDIR)\TZAPSLT.OBJ"
	-@erase "$(INTDIR)\VERSION.OBJ"
	-@erase "$(INTDIR)\ZACCESS.OBJ"
	-@erase "$(INTDIR)\ZACTIV.OBJ"
	-@erase "$(INTDIR)\ZAPSLT.OBJ"
	-@erase "$(INTDIR)\ZDISPOSE.OBJ"
	-@erase "$(INTDIR)\ZFILLNEW.OBJ"
	-@erase "$(INTDIR)\ZKEYFIND.OBJ"
	-@erase "$(INTDIR)\ZKEYFRST.OBJ"
	-@erase "$(INTDIR)\ZKEYLAST.OBJ"
	-@erase "$(INTDIR)\ZKEYNEXT.OBJ"
	-@erase "$(INTDIR)\ZKEYPREV.OBJ"
	-@erase "$(INTDIR)\ZKEYREAD.OBJ"
	-@erase "$(INTDIR)\ZREADREC.OBJ"
	-@erase "$(INTDIR)\ZRESTOR.OBJ"
	-@erase "$(INTDIR)\ZSETFILE.OBJ"
	-@erase "$(INTDIR)\ZSETPAGE.OBJ"
	-@erase "$(INTDIR)\ZTOUCH.OBJ"
	-@erase "$(INTDIR)\ZWRITREC.OBJ"
	-@erase "$(OUTDIR)\Trias321.dll"
	-@erase "$(OUTDIR)\Trias321.exp"
	-@erase "$(OUTDIR)\Trias321.lib"
	-@erase "..\lib32\Release\Trias321.lib"
	-@erase "c:\trias.mvc\trias200.rel\Trias321.dll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(OUTDIR)/TRIAS321.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "__CV__" /D "STRICT" /D "DLL" /D "MSWIND" /D "WIN32" /D "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D "__TRIAS01DLL__" /Fp"Release/Trias321.pch" /Yu"trias01p.hxx" /c
CPP_PROJ=/nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "__CV__" /D "STRICT" /D\
 "DLL" /D "MSWIND" /D "WIN32" /D "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D\
 "__TRIAS01DLL__" /Fp"$(INTDIR)/Trias321.pch" /Yu"trias01p.hxx" /Fo"$(INTDIR)/"\
 /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/Trias321.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Trias421.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 stdcppr.lib tfrmwork.lib cont32r.lib lz32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /stub:"obj32/rights.exe" /out:"Release/Trias321.dll" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none /debug
LINK32_FLAGS=stdcppr.lib tfrmwork.lib cont32r.lib lz32.lib kernel32.lib\
 user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib\
 ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll\
 /incremental:no /pdb:"$(OUTDIR)/Trias321.pdb" /machine:I386\
 /def:".\obj32\TRiAS321.def" /stub:"obj32/rights.exe"\
 /out:"$(OUTDIR)/Trias321.dll" /implib:"$(OUTDIR)/Trias321.lib"\
 /SUBSYSTEM:windows,4.0 
DEF_FILE= \
	".\obj32\TRiAS321.def"
LINK32_OBJS= \
	"$(INTDIR)\ACTIVATE.OBJ" \
	"$(INTDIR)\ASMBUF.OBJ" \
	"$(INTDIR)\BAKKEY.OBJ" \
	"$(INTDIR)\BITS.OBJ" \
	"$(INTDIR)\COMBIN.OBJ" \
	"$(INTDIR)\CRYPT.OBJ" \
	"$(INTDIR)\CUBE.OBJ" \
	"$(INTDIR)\DB_IO.OBJ" \
	"$(INTDIR)\DBCLOSE.OBJ" \
	"$(INTDIR)\DBCODB.OBJ" \
	"$(INTDIR)\DBD.OBJ" \
	"$(INTDIR)\DBINITC.OBJ" \
	"$(INTDIR)\DBOPEN.OBJ" \
	"$(INTDIR)\DELETE.OBJ" \
	"$(INTDIR)\DELHD_F.OBJ" \
	"$(INTDIR)\DIO_INIT.OBJ" \
	"$(INTDIR)\eexterr.obj" \
	"$(INTDIR)\EINVADDR.OBJ" \
	"$(INTDIR)\enfnderr.obj" \
	"$(INTDIR)\ENOMEM.OBJ" \
	"$(INTDIR)\enospac.obj" \
	"$(INTDIR)\ERRFKT.OBJ" \
	"$(INTDIR)\EVISERR.OBJ" \
	"$(INTDIR)\FDBCLOSE.OBJ" \
	"$(INTDIR)\FDBOPEN.OBJ" \
	"$(INTDIR)\FLEX.OBJ" \
	"$(INTDIR)\GENBACK.OBJ" \
	"$(INTDIR)\GETDWENT.OBJ" \
	"$(INTDIR)\GETDWNAM.OBJ" \
	"$(INTDIR)\GETDWUID.OBJ" \
	"$(INTDIR)\GETHD_F.OBJ" \
	"$(INTDIR)\GETHDLEN.OBJ" \
	"$(INTDIR)\GETPATH.OBJ" \
	"$(INTDIR)\HTCONT.OBJ" \
	"$(INTDIR)\HTDEL.OBJ" \
	"$(INTDIR)\HTINS.OBJ" \
	"$(INTDIR)\HTPREP.OBJ" \
	"$(INTDIR)\HTSEARCH.OBJ" \
	"$(INTDIR)\HTSHRINK.OBJ" \
	"$(INTDIR)\HTSPLIT.OBJ" \
	"$(INTDIR)\HTWIND_F.OBJ" \
	"$(INTDIR)\HTWINDOW.OBJ" \
	"$(INTDIR)\INITTAB.OBJ" \
	"$(INTDIR)\INSERT.OBJ" \
	"$(INTDIR)\KEY_IO.OBJ" \
	"$(INTDIR)\KEYCAT.OBJ" \
	"$(INTDIR)\KEYCMP.OBJ" \
	"$(INTDIR)\KEYDEL.OBJ" \
	"$(INTDIR)\KEYFRST.OBJ" \
	"$(INTDIR)\KEYINI.OBJ" \
	"$(INTDIR)\KEYINS.OBJ" \
	"$(INTDIR)\KEYLAST.OBJ" \
	"$(INTDIR)\KEYLOC.OBJ" \
	"$(INTDIR)\KEYNEXT.OBJ" \
	"$(INTDIR)\KEYPREV.OBJ" \
	"$(INTDIR)\KEYREAD.OBJ" \
	"$(INTDIR)\KEYUTIL.OBJ" \
	"$(INTDIR)\LADRC.OBJ" \
	"$(INTDIR)\LIBMAIN1.OBJ" \
	"$(INTDIR)\LISTEN.OBJ" \
	"$(INTDIR)\LOCATE.OBJ" \
	"$(INTDIR)\LOCFRST.OBJ" \
	"$(INTDIR)\LOCLAST.OBJ" \
	"$(INTDIR)\LOCSLT.OBJ" \
	"$(INTDIR)\MYCRYPT.OBJ" \
	"$(INTDIR)\NEWFILE.OBJ" \
	"$(INTDIR)\NGMC.OBJ" \
	"$(INTDIR)\NODEXP.OBJ" \
	"$(INTDIR)\NODFIL.OBJ" \
	"$(INTDIR)\NODSPL.OBJ" \
	"$(INTDIR)\NULLCMP.OBJ" \
	"$(INTDIR)\OVERFL.OBJ" \
	"$(INTDIR)\PARENT.OBJ" \
	"$(INTDIR)\PGZERO.OBJ" \
	"$(INTDIR)\PUTHD_F.OBJ" \
	"$(INTDIR)\PUTINL.OBJ" \
	"$(INTDIR)\QTCONT.OBJ" \
	"$(INTDIR)\QTDEL.OBJ" \
	"$(INTDIR)\QTINS.OBJ" \
	"$(INTDIR)\QTPREP.OBJ" \
	"$(INTDIR)\QTSEARCH.OBJ" \
	"$(INTDIR)\QTSHRINK.OBJ" \
	"$(INTDIR)\QTSPLIT.OBJ" \
	"$(INTDIR)\QTWIND_F.OBJ" \
	"$(INTDIR)\QTWINDOW.OBJ" \
	"$(INTDIR)\QUAD.OBJ" \
	"$(INTDIR)\REINDEX.OBJ" \
	"$(INTDIR)\RESOURCE.OBJ" \
	"$(INTDIR)\ROOTSP.OBJ" \
	"$(INTDIR)\SETERR.OBJ" \
	"$(INTDIR)\SHRINK.OBJ" \
	"$(INTDIR)\STATIST.OBJ" \
	"$(INTDIR)\STRFCNS.OBJ" \
	"$(INTDIR)\STRNCHR.OBJ" \
	"$(INTDIR)\SWITCHKC.OBJ" \
	"$(INTDIR)\TARGETFI.OBJ" \
	"$(INTDIR)\TLOCSLT.OBJ" \
	"$(INTDIR)\TPUTINL.OBJ" \
	"$(INTDIR)\TRIAS01P.OBJ" \
	"$(INTDIR)\Trias321.res" \
	"$(INTDIR)\TZAPSLT.OBJ" \
	"$(INTDIR)\VERSION.OBJ" \
	"$(INTDIR)\ZACCESS.OBJ" \
	"$(INTDIR)\ZACTIV.OBJ" \
	"$(INTDIR)\ZAPSLT.OBJ" \
	"$(INTDIR)\ZDISPOSE.OBJ" \
	"$(INTDIR)\ZFILLNEW.OBJ" \
	"$(INTDIR)\ZKEYFIND.OBJ" \
	"$(INTDIR)\ZKEYFRST.OBJ" \
	"$(INTDIR)\ZKEYLAST.OBJ" \
	"$(INTDIR)\ZKEYNEXT.OBJ" \
	"$(INTDIR)\ZKEYPREV.OBJ" \
	"$(INTDIR)\ZKEYREAD.OBJ" \
	"$(INTDIR)\ZREADREC.OBJ" \
	"$(INTDIR)\ZRESTOR.OBJ" \
	"$(INTDIR)\ZSETFILE.OBJ" \
	"$(INTDIR)\ZSETPAGE.OBJ" \
	"$(INTDIR)\ZTOUCH.OBJ" \
	"$(INTDIR)\ZWRITREC.OBJ"

"$(OUTDIR)\Trias321.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying Target to Destination ...
OutDir=.\Release
TargetPath=.\Release\Trias321.dll
TargetName=Trias321
InputPath=.\Release\Trias321.dll
SOURCE=$(InputPath)

BuildCmds= \
	rem copy $(TargetPath) c:\trias.mvc\trias200.rel \
	rem copy $(OutDir)\$(TargetName).lib e:\triasdev.mvc\lib32 \
	

"c:\trias.mvc\trias200.rel\$(TargetName).dll" : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
   $(BuildCmds)

"\triasdev.mvc\lib32\$(OutDir)\$(TargetName).lib" : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

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
OutDir=.\Debug4
TargetName=trias31d
# End Custom Macros

ALL : "$(OUTDIR)\trias31d.dll" "$(OUTDIR)\Trias421.bsc"\
 "c:\trias.mvc\trias200\trias31d.dll" "..\lib32\Debug4\trias31d.lib"

CLEAN : 
	-@erase "$(INTDIR)\ACTIVATE.OBJ"
	-@erase "$(INTDIR)\ACTIVATE.SBR"
	-@erase "$(INTDIR)\ASMBUF.OBJ"
	-@erase "$(INTDIR)\ASMBUF.SBR"
	-@erase "$(INTDIR)\BAKKEY.OBJ"
	-@erase "$(INTDIR)\BAKKEY.SBR"
	-@erase "$(INTDIR)\BITS.OBJ"
	-@erase "$(INTDIR)\BITS.SBR"
	-@erase "$(INTDIR)\COMBIN.OBJ"
	-@erase "$(INTDIR)\COMBIN.SBR"
	-@erase "$(INTDIR)\CRYPT.OBJ"
	-@erase "$(INTDIR)\CRYPT.SBR"
	-@erase "$(INTDIR)\CUBE.OBJ"
	-@erase "$(INTDIR)\CUBE.SBR"
	-@erase "$(INTDIR)\DB_IO.OBJ"
	-@erase "$(INTDIR)\DB_IO.SBR"
	-@erase "$(INTDIR)\DBCLOSE.OBJ"
	-@erase "$(INTDIR)\DBCLOSE.SBR"
	-@erase "$(INTDIR)\DBCODB.OBJ"
	-@erase "$(INTDIR)\DBCODB.SBR"
	-@erase "$(INTDIR)\DBD.OBJ"
	-@erase "$(INTDIR)\DBD.SBR"
	-@erase "$(INTDIR)\DBINITC.OBJ"
	-@erase "$(INTDIR)\DBINITC.SBR"
	-@erase "$(INTDIR)\DBOPEN.OBJ"
	-@erase "$(INTDIR)\DBOPEN.SBR"
	-@erase "$(INTDIR)\DELETE.OBJ"
	-@erase "$(INTDIR)\DELETE.SBR"
	-@erase "$(INTDIR)\DELHD_F.OBJ"
	-@erase "$(INTDIR)\DELHD_F.SBR"
	-@erase "$(INTDIR)\DIO_INIT.OBJ"
	-@erase "$(INTDIR)\DIO_INIT.SBR"
	-@erase "$(INTDIR)\eexterr.obj"
	-@erase "$(INTDIR)\eexterr.sbr"
	-@erase "$(INTDIR)\EINVADDR.OBJ"
	-@erase "$(INTDIR)\EINVADDR.SBR"
	-@erase "$(INTDIR)\enfnderr.obj"
	-@erase "$(INTDIR)\enfnderr.sbr"
	-@erase "$(INTDIR)\ENOMEM.OBJ"
	-@erase "$(INTDIR)\ENOMEM.SBR"
	-@erase "$(INTDIR)\enospac.obj"
	-@erase "$(INTDIR)\enospac.sbr"
	-@erase "$(INTDIR)\ERRFKT.OBJ"
	-@erase "$(INTDIR)\ERRFKT.SBR"
	-@erase "$(INTDIR)\EVISERR.OBJ"
	-@erase "$(INTDIR)\EVISERR.SBR"
	-@erase "$(INTDIR)\FDBCLOSE.OBJ"
	-@erase "$(INTDIR)\FDBCLOSE.SBR"
	-@erase "$(INTDIR)\FDBOPEN.OBJ"
	-@erase "$(INTDIR)\FDBOPEN.SBR"
	-@erase "$(INTDIR)\FLEX.OBJ"
	-@erase "$(INTDIR)\FLEX.SBR"
	-@erase "$(INTDIR)\GENBACK.OBJ"
	-@erase "$(INTDIR)\GENBACK.SBR"
	-@erase "$(INTDIR)\GETDWENT.OBJ"
	-@erase "$(INTDIR)\GETDWENT.SBR"
	-@erase "$(INTDIR)\GETDWNAM.OBJ"
	-@erase "$(INTDIR)\GETDWNAM.SBR"
	-@erase "$(INTDIR)\GETDWUID.OBJ"
	-@erase "$(INTDIR)\GETDWUID.SBR"
	-@erase "$(INTDIR)\GETHD_F.OBJ"
	-@erase "$(INTDIR)\GETHD_F.SBR"
	-@erase "$(INTDIR)\GETHDLEN.OBJ"
	-@erase "$(INTDIR)\GETHDLEN.SBR"
	-@erase "$(INTDIR)\GETPATH.OBJ"
	-@erase "$(INTDIR)\GETPATH.SBR"
	-@erase "$(INTDIR)\HTCONT.OBJ"
	-@erase "$(INTDIR)\HTCONT.SBR"
	-@erase "$(INTDIR)\HTDEL.OBJ"
	-@erase "$(INTDIR)\HTDEL.SBR"
	-@erase "$(INTDIR)\HTINS.OBJ"
	-@erase "$(INTDIR)\HTINS.SBR"
	-@erase "$(INTDIR)\HTPREP.OBJ"
	-@erase "$(INTDIR)\HTPREP.SBR"
	-@erase "$(INTDIR)\HTSEARCH.OBJ"
	-@erase "$(INTDIR)\HTSEARCH.SBR"
	-@erase "$(INTDIR)\HTSHRINK.OBJ"
	-@erase "$(INTDIR)\HTSHRINK.SBR"
	-@erase "$(INTDIR)\HTSPLIT.OBJ"
	-@erase "$(INTDIR)\HTSPLIT.SBR"
	-@erase "$(INTDIR)\HTWIND_F.OBJ"
	-@erase "$(INTDIR)\HTWIND_F.SBR"
	-@erase "$(INTDIR)\HTWINDOW.OBJ"
	-@erase "$(INTDIR)\HTWINDOW.SBR"
	-@erase "$(INTDIR)\INITTAB.OBJ"
	-@erase "$(INTDIR)\INITTAB.SBR"
	-@erase "$(INTDIR)\INSERT.OBJ"
	-@erase "$(INTDIR)\INSERT.SBR"
	-@erase "$(INTDIR)\KEY_IO.OBJ"
	-@erase "$(INTDIR)\KEY_IO.SBR"
	-@erase "$(INTDIR)\KEYCAT.OBJ"
	-@erase "$(INTDIR)\KEYCAT.SBR"
	-@erase "$(INTDIR)\KEYCMP.OBJ"
	-@erase "$(INTDIR)\KEYCMP.SBR"
	-@erase "$(INTDIR)\KEYDEL.OBJ"
	-@erase "$(INTDIR)\KEYDEL.SBR"
	-@erase "$(INTDIR)\KEYFRST.OBJ"
	-@erase "$(INTDIR)\KEYFRST.SBR"
	-@erase "$(INTDIR)\KEYINI.OBJ"
	-@erase "$(INTDIR)\KEYINI.SBR"
	-@erase "$(INTDIR)\KEYINS.OBJ"
	-@erase "$(INTDIR)\KEYINS.SBR"
	-@erase "$(INTDIR)\KEYLAST.OBJ"
	-@erase "$(INTDIR)\KEYLAST.SBR"
	-@erase "$(INTDIR)\KEYLOC.OBJ"
	-@erase "$(INTDIR)\KEYLOC.SBR"
	-@erase "$(INTDIR)\KEYNEXT.OBJ"
	-@erase "$(INTDIR)\KEYNEXT.SBR"
	-@erase "$(INTDIR)\KEYPREV.OBJ"
	-@erase "$(INTDIR)\KEYPREV.SBR"
	-@erase "$(INTDIR)\KEYREAD.OBJ"
	-@erase "$(INTDIR)\KEYREAD.SBR"
	-@erase "$(INTDIR)\KEYUTIL.OBJ"
	-@erase "$(INTDIR)\KEYUTIL.SBR"
	-@erase "$(INTDIR)\LADRC.OBJ"
	-@erase "$(INTDIR)\LADRC.SBR"
	-@erase "$(INTDIR)\LIBMAIN1.OBJ"
	-@erase "$(INTDIR)\LIBMAIN1.SBR"
	-@erase "$(INTDIR)\LISTEN.OBJ"
	-@erase "$(INTDIR)\LISTEN.SBR"
	-@erase "$(INTDIR)\LOCATE.OBJ"
	-@erase "$(INTDIR)\LOCATE.SBR"
	-@erase "$(INTDIR)\LOCFRST.OBJ"
	-@erase "$(INTDIR)\LOCFRST.SBR"
	-@erase "$(INTDIR)\LOCLAST.OBJ"
	-@erase "$(INTDIR)\LOCLAST.SBR"
	-@erase "$(INTDIR)\LOCSLT.OBJ"
	-@erase "$(INTDIR)\LOCSLT.SBR"
	-@erase "$(INTDIR)\MYCRYPT.OBJ"
	-@erase "$(INTDIR)\MYCRYPT.SBR"
	-@erase "$(INTDIR)\NEWFILE.OBJ"
	-@erase "$(INTDIR)\NEWFILE.SBR"
	-@erase "$(INTDIR)\NGMC.OBJ"
	-@erase "$(INTDIR)\NGMC.SBR"
	-@erase "$(INTDIR)\NODEXP.OBJ"
	-@erase "$(INTDIR)\NODEXP.SBR"
	-@erase "$(INTDIR)\NODFIL.OBJ"
	-@erase "$(INTDIR)\NODFIL.SBR"
	-@erase "$(INTDIR)\NODSPL.OBJ"
	-@erase "$(INTDIR)\NODSPL.SBR"
	-@erase "$(INTDIR)\NULLCMP.OBJ"
	-@erase "$(INTDIR)\NULLCMP.SBR"
	-@erase "$(INTDIR)\OVERFL.OBJ"
	-@erase "$(INTDIR)\OVERFL.SBR"
	-@erase "$(INTDIR)\PARENT.OBJ"
	-@erase "$(INTDIR)\PARENT.SBR"
	-@erase "$(INTDIR)\PGZERO.OBJ"
	-@erase "$(INTDIR)\PGZERO.SBR"
	-@erase "$(INTDIR)\PUTHD_F.OBJ"
	-@erase "$(INTDIR)\PUTHD_F.SBR"
	-@erase "$(INTDIR)\PUTINL.OBJ"
	-@erase "$(INTDIR)\PUTINL.SBR"
	-@erase "$(INTDIR)\QTCONT.OBJ"
	-@erase "$(INTDIR)\QTCONT.SBR"
	-@erase "$(INTDIR)\QTDEL.OBJ"
	-@erase "$(INTDIR)\QTDEL.SBR"
	-@erase "$(INTDIR)\QTINS.OBJ"
	-@erase "$(INTDIR)\QTINS.SBR"
	-@erase "$(INTDIR)\QTPREP.OBJ"
	-@erase "$(INTDIR)\QTPREP.SBR"
	-@erase "$(INTDIR)\QTSEARCH.OBJ"
	-@erase "$(INTDIR)\QTSEARCH.SBR"
	-@erase "$(INTDIR)\QTSHRINK.OBJ"
	-@erase "$(INTDIR)\QTSHRINK.SBR"
	-@erase "$(INTDIR)\QTSPLIT.OBJ"
	-@erase "$(INTDIR)\QTSPLIT.SBR"
	-@erase "$(INTDIR)\QTWIND_F.OBJ"
	-@erase "$(INTDIR)\QTWIND_F.SBR"
	-@erase "$(INTDIR)\QTWINDOW.OBJ"
	-@erase "$(INTDIR)\QTWINDOW.SBR"
	-@erase "$(INTDIR)\QUAD.OBJ"
	-@erase "$(INTDIR)\QUAD.SBR"
	-@erase "$(INTDIR)\REINDEX.OBJ"
	-@erase "$(INTDIR)\REINDEX.SBR"
	-@erase "$(INTDIR)\RESOURCE.OBJ"
	-@erase "$(INTDIR)\RESOURCE.SBR"
	-@erase "$(INTDIR)\ROOTSP.OBJ"
	-@erase "$(INTDIR)\ROOTSP.SBR"
	-@erase "$(INTDIR)\SETERR.OBJ"
	-@erase "$(INTDIR)\SETERR.SBR"
	-@erase "$(INTDIR)\SHRINK.OBJ"
	-@erase "$(INTDIR)\SHRINK.SBR"
	-@erase "$(INTDIR)\STATIST.OBJ"
	-@erase "$(INTDIR)\STATIST.SBR"
	-@erase "$(INTDIR)\STRFCNS.OBJ"
	-@erase "$(INTDIR)\STRFCNS.SBR"
	-@erase "$(INTDIR)\STRNCHR.OBJ"
	-@erase "$(INTDIR)\STRNCHR.SBR"
	-@erase "$(INTDIR)\SWITCHKC.OBJ"
	-@erase "$(INTDIR)\SWITCHKC.SBR"
	-@erase "$(INTDIR)\TARGETFI.OBJ"
	-@erase "$(INTDIR)\TARGETFI.SBR"
	-@erase "$(INTDIR)\TLOCSLT.OBJ"
	-@erase "$(INTDIR)\TLOCSLT.SBR"
	-@erase "$(INTDIR)\TPUTINL.OBJ"
	-@erase "$(INTDIR)\TPUTINL.SBR"
	-@erase "$(INTDIR)\TRIAS01P.OBJ"
	-@erase "$(INTDIR)\TRIAS01P.SBR"
	-@erase "$(INTDIR)\Trias321.res"
	-@erase "$(INTDIR)\trias321d.idb"
	-@erase "$(INTDIR)\trias321d.pch"
	-@erase "$(INTDIR)\trias321d.pdb"
	-@erase "$(INTDIR)\TZAPSLT.OBJ"
	-@erase "$(INTDIR)\TZAPSLT.SBR"
	-@erase "$(INTDIR)\VERSION.OBJ"
	-@erase "$(INTDIR)\VERSION.SBR"
	-@erase "$(INTDIR)\ZACCESS.OBJ"
	-@erase "$(INTDIR)\ZACCESS.SBR"
	-@erase "$(INTDIR)\ZACTIV.OBJ"
	-@erase "$(INTDIR)\ZACTIV.SBR"
	-@erase "$(INTDIR)\ZAPSLT.OBJ"
	-@erase "$(INTDIR)\ZAPSLT.SBR"
	-@erase "$(INTDIR)\ZDISPOSE.OBJ"
	-@erase "$(INTDIR)\ZDISPOSE.SBR"
	-@erase "$(INTDIR)\ZFILLNEW.OBJ"
	-@erase "$(INTDIR)\ZFILLNEW.SBR"
	-@erase "$(INTDIR)\ZKEYFIND.OBJ"
	-@erase "$(INTDIR)\ZKEYFIND.SBR"
	-@erase "$(INTDIR)\ZKEYFRST.OBJ"
	-@erase "$(INTDIR)\ZKEYFRST.SBR"
	-@erase "$(INTDIR)\ZKEYLAST.OBJ"
	-@erase "$(INTDIR)\ZKEYLAST.SBR"
	-@erase "$(INTDIR)\ZKEYNEXT.OBJ"
	-@erase "$(INTDIR)\ZKEYNEXT.SBR"
	-@erase "$(INTDIR)\ZKEYPREV.OBJ"
	-@erase "$(INTDIR)\ZKEYPREV.SBR"
	-@erase "$(INTDIR)\ZKEYREAD.OBJ"
	-@erase "$(INTDIR)\ZKEYREAD.SBR"
	-@erase "$(INTDIR)\ZREADREC.OBJ"
	-@erase "$(INTDIR)\ZREADREC.SBR"
	-@erase "$(INTDIR)\ZRESTOR.OBJ"
	-@erase "$(INTDIR)\ZRESTOR.SBR"
	-@erase "$(INTDIR)\ZSETFILE.OBJ"
	-@erase "$(INTDIR)\ZSETFILE.SBR"
	-@erase "$(INTDIR)\ZSETPAGE.OBJ"
	-@erase "$(INTDIR)\ZSETPAGE.SBR"
	-@erase "$(INTDIR)\ZTOUCH.OBJ"
	-@erase "$(INTDIR)\ZTOUCH.SBR"
	-@erase "$(INTDIR)\ZWRITREC.OBJ"
	-@erase "$(INTDIR)\ZWRITREC.SBR"
	-@erase "$(OUTDIR)\trias31d.dll"
	-@erase "$(OUTDIR)\trias31d.exp"
	-@erase "$(OUTDIR)\trias31d.lib"
	-@erase "$(OUTDIR)\Trias421.bsc"
	-@erase "..\lib32\Debug4\trias31d.lib"
	-@erase "c:\trias.mvc\trias200\trias31d.dll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(OUTDIR)/TRIAS321.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "__CV__" /D "STRICT" /D "DLL" /D "MSWIND" /D "WIN32" /D "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D "__TRIAS01DLL__" /FR /Fp"Debug4/trias321d.pch" /Yu"trias01p.hxx" /Fd"Debug4/trias321d.pdb" /c
CPP_PROJ=/nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "__CV__" /D\
 "STRICT" /D "DLL" /D "MSWIND" /D "WIN32" /D "_WINDOWS" /D "__XT" /D\
 "__DEXPROCS" /D "__TRIAS01DLL__" /FR"$(INTDIR)/" /Fp"$(INTDIR)/trias321d.pch"\
 /Yu"trias01p.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/trias321d.pdb" /c 
CPP_OBJS=.\Debug4/
CPP_SBRS=.\Debug4/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/Trias321.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Trias421.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\ACTIVATE.SBR" \
	"$(INTDIR)\ASMBUF.SBR" \
	"$(INTDIR)\BAKKEY.SBR" \
	"$(INTDIR)\BITS.SBR" \
	"$(INTDIR)\COMBIN.SBR" \
	"$(INTDIR)\CRYPT.SBR" \
	"$(INTDIR)\CUBE.SBR" \
	"$(INTDIR)\DB_IO.SBR" \
	"$(INTDIR)\DBCLOSE.SBR" \
	"$(INTDIR)\DBCODB.SBR" \
	"$(INTDIR)\DBD.SBR" \
	"$(INTDIR)\DBINITC.SBR" \
	"$(INTDIR)\DBOPEN.SBR" \
	"$(INTDIR)\DELETE.SBR" \
	"$(INTDIR)\DELHD_F.SBR" \
	"$(INTDIR)\DIO_INIT.SBR" \
	"$(INTDIR)\eexterr.sbr" \
	"$(INTDIR)\EINVADDR.SBR" \
	"$(INTDIR)\enfnderr.sbr" \
	"$(INTDIR)\ENOMEM.SBR" \
	"$(INTDIR)\enospac.sbr" \
	"$(INTDIR)\ERRFKT.SBR" \
	"$(INTDIR)\EVISERR.SBR" \
	"$(INTDIR)\FDBCLOSE.SBR" \
	"$(INTDIR)\FDBOPEN.SBR" \
	"$(INTDIR)\FLEX.SBR" \
	"$(INTDIR)\GENBACK.SBR" \
	"$(INTDIR)\GETDWENT.SBR" \
	"$(INTDIR)\GETDWNAM.SBR" \
	"$(INTDIR)\GETDWUID.SBR" \
	"$(INTDIR)\GETHD_F.SBR" \
	"$(INTDIR)\GETHDLEN.SBR" \
	"$(INTDIR)\GETPATH.SBR" \
	"$(INTDIR)\HTCONT.SBR" \
	"$(INTDIR)\HTDEL.SBR" \
	"$(INTDIR)\HTINS.SBR" \
	"$(INTDIR)\HTPREP.SBR" \
	"$(INTDIR)\HTSEARCH.SBR" \
	"$(INTDIR)\HTSHRINK.SBR" \
	"$(INTDIR)\HTSPLIT.SBR" \
	"$(INTDIR)\HTWIND_F.SBR" \
	"$(INTDIR)\HTWINDOW.SBR" \
	"$(INTDIR)\INITTAB.SBR" \
	"$(INTDIR)\INSERT.SBR" \
	"$(INTDIR)\KEY_IO.SBR" \
	"$(INTDIR)\KEYCAT.SBR" \
	"$(INTDIR)\KEYCMP.SBR" \
	"$(INTDIR)\KEYDEL.SBR" \
	"$(INTDIR)\KEYFRST.SBR" \
	"$(INTDIR)\KEYINI.SBR" \
	"$(INTDIR)\KEYINS.SBR" \
	"$(INTDIR)\KEYLAST.SBR" \
	"$(INTDIR)\KEYLOC.SBR" \
	"$(INTDIR)\KEYNEXT.SBR" \
	"$(INTDIR)\KEYPREV.SBR" \
	"$(INTDIR)\KEYREAD.SBR" \
	"$(INTDIR)\KEYUTIL.SBR" \
	"$(INTDIR)\LADRC.SBR" \
	"$(INTDIR)\LIBMAIN1.SBR" \
	"$(INTDIR)\LISTEN.SBR" \
	"$(INTDIR)\LOCATE.SBR" \
	"$(INTDIR)\LOCFRST.SBR" \
	"$(INTDIR)\LOCLAST.SBR" \
	"$(INTDIR)\LOCSLT.SBR" \
	"$(INTDIR)\MYCRYPT.SBR" \
	"$(INTDIR)\NEWFILE.SBR" \
	"$(INTDIR)\NGMC.SBR" \
	"$(INTDIR)\NODEXP.SBR" \
	"$(INTDIR)\NODFIL.SBR" \
	"$(INTDIR)\NODSPL.SBR" \
	"$(INTDIR)\NULLCMP.SBR" \
	"$(INTDIR)\OVERFL.SBR" \
	"$(INTDIR)\PARENT.SBR" \
	"$(INTDIR)\PGZERO.SBR" \
	"$(INTDIR)\PUTHD_F.SBR" \
	"$(INTDIR)\PUTINL.SBR" \
	"$(INTDIR)\QTCONT.SBR" \
	"$(INTDIR)\QTDEL.SBR" \
	"$(INTDIR)\QTINS.SBR" \
	"$(INTDIR)\QTPREP.SBR" \
	"$(INTDIR)\QTSEARCH.SBR" \
	"$(INTDIR)\QTSHRINK.SBR" \
	"$(INTDIR)\QTSPLIT.SBR" \
	"$(INTDIR)\QTWIND_F.SBR" \
	"$(INTDIR)\QTWINDOW.SBR" \
	"$(INTDIR)\QUAD.SBR" \
	"$(INTDIR)\REINDEX.SBR" \
	"$(INTDIR)\RESOURCE.SBR" \
	"$(INTDIR)\ROOTSP.SBR" \
	"$(INTDIR)\SETERR.SBR" \
	"$(INTDIR)\SHRINK.SBR" \
	"$(INTDIR)\STATIST.SBR" \
	"$(INTDIR)\STRFCNS.SBR" \
	"$(INTDIR)\STRNCHR.SBR" \
	"$(INTDIR)\SWITCHKC.SBR" \
	"$(INTDIR)\TARGETFI.SBR" \
	"$(INTDIR)\TLOCSLT.SBR" \
	"$(INTDIR)\TPUTINL.SBR" \
	"$(INTDIR)\TRIAS01P.SBR" \
	"$(INTDIR)\TZAPSLT.SBR" \
	"$(INTDIR)\VERSION.SBR" \
	"$(INTDIR)\ZACCESS.SBR" \
	"$(INTDIR)\ZACTIV.SBR" \
	"$(INTDIR)\ZAPSLT.SBR" \
	"$(INTDIR)\ZDISPOSE.SBR" \
	"$(INTDIR)\ZFILLNEW.SBR" \
	"$(INTDIR)\ZKEYFIND.SBR" \
	"$(INTDIR)\ZKEYFRST.SBR" \
	"$(INTDIR)\ZKEYLAST.SBR" \
	"$(INTDIR)\ZKEYNEXT.SBR" \
	"$(INTDIR)\ZKEYPREV.SBR" \
	"$(INTDIR)\ZKEYREAD.SBR" \
	"$(INTDIR)\ZREADREC.SBR" \
	"$(INTDIR)\ZRESTOR.SBR" \
	"$(INTDIR)\ZSETFILE.SBR" \
	"$(INTDIR)\ZSETPAGE.SBR" \
	"$(INTDIR)\ZTOUCH.SBR" \
	"$(INTDIR)\ZWRITREC.SBR"

"$(OUTDIR)\Trias421.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 stdcppd.lib tfrm32d.lib cont32d.lib lz32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /base:0x6b0000 /dll /profile /debug /machine:I386 /stub:"obj32/rights.exe" /out:"Debug4/trias31d.dll" /SUBSYSTEM:windows,4.0
LINK32_FLAGS=stdcppd.lib tfrm32d.lib cont32d.lib lz32.lib kernel32.lib\
 user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib\
 ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /base:0x6b0000\
 /dll /profile /debug /machine:I386 /def:".\obj32\TRiAS31d.def"\
 /stub:"obj32/rights.exe" /out:"$(OUTDIR)/trias31d.dll"\
 /implib:"$(OUTDIR)/trias31d.lib" /SUBSYSTEM:windows,4.0 
DEF_FILE= \
	".\obj32\TRiAS31d.def"
LINK32_OBJS= \
	"$(INTDIR)\ACTIVATE.OBJ" \
	"$(INTDIR)\ASMBUF.OBJ" \
	"$(INTDIR)\BAKKEY.OBJ" \
	"$(INTDIR)\BITS.OBJ" \
	"$(INTDIR)\COMBIN.OBJ" \
	"$(INTDIR)\CRYPT.OBJ" \
	"$(INTDIR)\CUBE.OBJ" \
	"$(INTDIR)\DB_IO.OBJ" \
	"$(INTDIR)\DBCLOSE.OBJ" \
	"$(INTDIR)\DBCODB.OBJ" \
	"$(INTDIR)\DBD.OBJ" \
	"$(INTDIR)\DBINITC.OBJ" \
	"$(INTDIR)\DBOPEN.OBJ" \
	"$(INTDIR)\DELETE.OBJ" \
	"$(INTDIR)\DELHD_F.OBJ" \
	"$(INTDIR)\DIO_INIT.OBJ" \
	"$(INTDIR)\eexterr.obj" \
	"$(INTDIR)\EINVADDR.OBJ" \
	"$(INTDIR)\enfnderr.obj" \
	"$(INTDIR)\ENOMEM.OBJ" \
	"$(INTDIR)\enospac.obj" \
	"$(INTDIR)\ERRFKT.OBJ" \
	"$(INTDIR)\EVISERR.OBJ" \
	"$(INTDIR)\FDBCLOSE.OBJ" \
	"$(INTDIR)\FDBOPEN.OBJ" \
	"$(INTDIR)\FLEX.OBJ" \
	"$(INTDIR)\GENBACK.OBJ" \
	"$(INTDIR)\GETDWENT.OBJ" \
	"$(INTDIR)\GETDWNAM.OBJ" \
	"$(INTDIR)\GETDWUID.OBJ" \
	"$(INTDIR)\GETHD_F.OBJ" \
	"$(INTDIR)\GETHDLEN.OBJ" \
	"$(INTDIR)\GETPATH.OBJ" \
	"$(INTDIR)\HTCONT.OBJ" \
	"$(INTDIR)\HTDEL.OBJ" \
	"$(INTDIR)\HTINS.OBJ" \
	"$(INTDIR)\HTPREP.OBJ" \
	"$(INTDIR)\HTSEARCH.OBJ" \
	"$(INTDIR)\HTSHRINK.OBJ" \
	"$(INTDIR)\HTSPLIT.OBJ" \
	"$(INTDIR)\HTWIND_F.OBJ" \
	"$(INTDIR)\HTWINDOW.OBJ" \
	"$(INTDIR)\INITTAB.OBJ" \
	"$(INTDIR)\INSERT.OBJ" \
	"$(INTDIR)\KEY_IO.OBJ" \
	"$(INTDIR)\KEYCAT.OBJ" \
	"$(INTDIR)\KEYCMP.OBJ" \
	"$(INTDIR)\KEYDEL.OBJ" \
	"$(INTDIR)\KEYFRST.OBJ" \
	"$(INTDIR)\KEYINI.OBJ" \
	"$(INTDIR)\KEYINS.OBJ" \
	"$(INTDIR)\KEYLAST.OBJ" \
	"$(INTDIR)\KEYLOC.OBJ" \
	"$(INTDIR)\KEYNEXT.OBJ" \
	"$(INTDIR)\KEYPREV.OBJ" \
	"$(INTDIR)\KEYREAD.OBJ" \
	"$(INTDIR)\KEYUTIL.OBJ" \
	"$(INTDIR)\LADRC.OBJ" \
	"$(INTDIR)\LIBMAIN1.OBJ" \
	"$(INTDIR)\LISTEN.OBJ" \
	"$(INTDIR)\LOCATE.OBJ" \
	"$(INTDIR)\LOCFRST.OBJ" \
	"$(INTDIR)\LOCLAST.OBJ" \
	"$(INTDIR)\LOCSLT.OBJ" \
	"$(INTDIR)\MYCRYPT.OBJ" \
	"$(INTDIR)\NEWFILE.OBJ" \
	"$(INTDIR)\NGMC.OBJ" \
	"$(INTDIR)\NODEXP.OBJ" \
	"$(INTDIR)\NODFIL.OBJ" \
	"$(INTDIR)\NODSPL.OBJ" \
	"$(INTDIR)\NULLCMP.OBJ" \
	"$(INTDIR)\OVERFL.OBJ" \
	"$(INTDIR)\PARENT.OBJ" \
	"$(INTDIR)\PGZERO.OBJ" \
	"$(INTDIR)\PUTHD_F.OBJ" \
	"$(INTDIR)\PUTINL.OBJ" \
	"$(INTDIR)\QTCONT.OBJ" \
	"$(INTDIR)\QTDEL.OBJ" \
	"$(INTDIR)\QTINS.OBJ" \
	"$(INTDIR)\QTPREP.OBJ" \
	"$(INTDIR)\QTSEARCH.OBJ" \
	"$(INTDIR)\QTSHRINK.OBJ" \
	"$(INTDIR)\QTSPLIT.OBJ" \
	"$(INTDIR)\QTWIND_F.OBJ" \
	"$(INTDIR)\QTWINDOW.OBJ" \
	"$(INTDIR)\QUAD.OBJ" \
	"$(INTDIR)\REINDEX.OBJ" \
	"$(INTDIR)\RESOURCE.OBJ" \
	"$(INTDIR)\ROOTSP.OBJ" \
	"$(INTDIR)\SETERR.OBJ" \
	"$(INTDIR)\SHRINK.OBJ" \
	"$(INTDIR)\STATIST.OBJ" \
	"$(INTDIR)\STRFCNS.OBJ" \
	"$(INTDIR)\STRNCHR.OBJ" \
	"$(INTDIR)\SWITCHKC.OBJ" \
	"$(INTDIR)\TARGETFI.OBJ" \
	"$(INTDIR)\TLOCSLT.OBJ" \
	"$(INTDIR)\TPUTINL.OBJ" \
	"$(INTDIR)\TRIAS01P.OBJ" \
	"$(INTDIR)\Trias321.res" \
	"$(INTDIR)\TZAPSLT.OBJ" \
	"$(INTDIR)\VERSION.OBJ" \
	"$(INTDIR)\ZACCESS.OBJ" \
	"$(INTDIR)\ZACTIV.OBJ" \
	"$(INTDIR)\ZAPSLT.OBJ" \
	"$(INTDIR)\ZDISPOSE.OBJ" \
	"$(INTDIR)\ZFILLNEW.OBJ" \
	"$(INTDIR)\ZKEYFIND.OBJ" \
	"$(INTDIR)\ZKEYFRST.OBJ" \
	"$(INTDIR)\ZKEYLAST.OBJ" \
	"$(INTDIR)\ZKEYNEXT.OBJ" \
	"$(INTDIR)\ZKEYPREV.OBJ" \
	"$(INTDIR)\ZKEYREAD.OBJ" \
	"$(INTDIR)\ZREADREC.OBJ" \
	"$(INTDIR)\ZRESTOR.OBJ" \
	"$(INTDIR)\ZSETFILE.OBJ" \
	"$(INTDIR)\ZSETPAGE.OBJ" \
	"$(INTDIR)\ZTOUCH.OBJ" \
	"$(INTDIR)\ZWRITREC.OBJ"

"$(OUTDIR)\trias31d.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying Target to Destination ...
OutDir=.\Debug4
TargetPath=.\Debug4\trias31d.dll
TargetName=trias31d
InputPath=.\Debug4\trias31d.dll
SOURCE=$(InputPath)

BuildCmds= \
	rem copy $(TargetPath) c:\trias.mvc\trias200 \
	rem copy $(OutDir)\$(TargetName).lib e:\triasdev.mvc\lib32 \
	

"c:\trias.mvc\trias200\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"\triasdev.mvc\lib32\$(OutDir)\$(TargetName).lib" : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
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

# Name "Trias321 - Win32 Release"
# Name "Trias321 - Win32 Debug"

!IF  "$(CFG)" == "Trias321 - Win32 Release"

!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\INITTAB.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_INITT=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\DBVERSIO.H"\
	{$(INCLUDE)}"\DWD.H"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\Strmhelp.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\INITTAB.OBJ" : $(SOURCE) $(DEP_CPP_INITT) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_INITT=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\DBVERSIO.H"\
	{$(INCLUDE)}"\DWD.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\Strmhelp.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\INITTAB.OBJ" : $(SOURCE) $(DEP_CPP_INITT) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\INITTAB.SBR" : $(SOURCE) $(DEP_CPP_INITT) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ASMBUF.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_ASMBU=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\ASMBUF.OBJ" : $(SOURCE) $(DEP_CPP_ASMBU) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_ASMBU=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\ASMBUF.OBJ" : $(SOURCE) $(DEP_CPP_ASMBU) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\ASMBUF.SBR" : $(SOURCE) $(DEP_CPP_ASMBU) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SWITCHKC.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_SWITC=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\SWITCHKC.H"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\SWITCHKC.OBJ" : $(SOURCE) $(DEP_CPP_SWITC) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_SWITC=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\SWITCHKC.H"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\SWITCHKC.OBJ" : $(SOURCE) $(DEP_CPP_SWITC) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\SWITCHKC.SBR" : $(SOURCE) $(DEP_CPP_SWITC) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ZSETFILE.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_ZSETF=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\ZSETFILE.OBJ" : $(SOURCE) $(DEP_CPP_ZSETF) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_ZSETF=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\ZSETFILE.OBJ" : $(SOURCE) $(DEP_CPP_ZSETF) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\ZSETFILE.SBR" : $(SOURCE) $(DEP_CPP_ZSETF) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\HTSHRINK.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_HTSHR=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\HTSHRINK.OBJ" : $(SOURCE) $(DEP_CPP_HTSHR) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_HTSHR=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\HTSHRINK.OBJ" : $(SOURCE) $(DEP_CPP_HTSHR) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\HTSHRINK.SBR" : $(SOURCE) $(DEP_CPP_HTSHR) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ZSETPAGE.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_ZSETP=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\ZSETPAGE.OBJ" : $(SOURCE) $(DEP_CPP_ZSETP) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_ZSETP=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\ZSETPAGE.OBJ" : $(SOURCE) $(DEP_CPP_ZSETP) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\ZSETPAGE.SBR" : $(SOURCE) $(DEP_CPP_ZSETP) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ZFILLNEW.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_ZFILL=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\ZFILLNEW.OBJ" : $(SOURCE) $(DEP_CPP_ZFILL) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_ZFILL=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\ZFILLNEW.OBJ" : $(SOURCE) $(DEP_CPP_ZFILL) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\ZFILLNEW.SBR" : $(SOURCE) $(DEP_CPP_ZFILL) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ZWRITREC.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_ZWRIT=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\ZWRITREC.OBJ" : $(SOURCE) $(DEP_CPP_ZWRIT) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_ZWRIT=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\ZWRITREC.OBJ" : $(SOURCE) $(DEP_CPP_ZWRIT) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\ZWRITREC.SBR" : $(SOURCE) $(DEP_CPP_ZWRIT) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\LOCATE.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_LOCAT=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\LOCATE.OBJ" : $(SOURCE) $(DEP_CPP_LOCAT) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_LOCAT=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\LOCATE.OBJ" : $(SOURCE) $(DEP_CPP_LOCAT) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\LOCATE.SBR" : $(SOURCE) $(DEP_CPP_LOCAT) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\KEYINS.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_KEYIN=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\KEYINS.OBJ" : $(SOURCE) $(DEP_CPP_KEYIN) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_KEYIN=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\KEYINS.OBJ" : $(SOURCE) $(DEP_CPP_KEYIN) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\KEYINS.SBR" : $(SOURCE) $(DEP_CPP_KEYIN) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\QTDEL.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_QTDEL=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\QTDEL.OBJ" : $(SOURCE) $(DEP_CPP_QTDEL) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_QTDEL=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\QTDEL.OBJ" : $(SOURCE) $(DEP_CPP_QTDEL) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\QTDEL.SBR" : $(SOURCE) $(DEP_CPP_QTDEL) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\QTINS.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_QTINS=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\QTINS.OBJ" : $(SOURCE) $(DEP_CPP_QTINS) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_QTINS=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\QTINS.OBJ" : $(SOURCE) $(DEP_CPP_QTINS) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\QTINS.SBR" : $(SOURCE) $(DEP_CPP_QTINS) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\LOCFRST.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_LOCFR=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\LOCFRST.OBJ" : $(SOURCE) $(DEP_CPP_LOCFR) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_LOCFR=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\LOCFRST.OBJ" : $(SOURCE) $(DEP_CPP_LOCFR) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\LOCFRST.SBR" : $(SOURCE) $(DEP_CPP_LOCFR) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FDBCLOSE.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_FDBCL=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\FDBCLOSE.OBJ" : $(SOURCE) $(DEP_CPP_FDBCL) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_FDBCL=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\FDBCLOSE.OBJ" : $(SOURCE) $(DEP_CPP_FDBCL) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\FDBCLOSE.SBR" : $(SOURCE) $(DEP_CPP_FDBCL) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TLOCSLT.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_TLOCS=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\TLOCSLT.OBJ" : $(SOURCE) $(DEP_CPP_TLOCS) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_TLOCS=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\TLOCSLT.OBJ" : $(SOURCE) $(DEP_CPP_TLOCS) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\TLOCSLT.SBR" : $(SOURCE) $(DEP_CPP_TLOCS) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ZTOUCH.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_ZTOUC=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\DBVERSIO.H"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\ZTOUCH.OBJ" : $(SOURCE) $(DEP_CPP_ZTOUC) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_ZTOUC=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\DBVERSIO.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\ZTOUCH.OBJ" : $(SOURCE) $(DEP_CPP_ZTOUC) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\ZTOUCH.SBR" : $(SOURCE) $(DEP_CPP_ZTOUC) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TPUTINL.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_TPUTI=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\TPUTINL.OBJ" : $(SOURCE) $(DEP_CPP_TPUTI) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_TPUTI=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\TPUTINL.OBJ" : $(SOURCE) $(DEP_CPP_TPUTI) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\TPUTINL.SBR" : $(SOURCE) $(DEP_CPP_TPUTI) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\COMBIN.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_COMBI=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\COMBIN.OBJ" : $(SOURCE) $(DEP_CPP_COMBI) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_COMBI=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\COMBIN.OBJ" : $(SOURCE) $(DEP_CPP_COMBI) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\COMBIN.SBR" : $(SOURCE) $(DEP_CPP_COMBI) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ZAPSLT.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_ZAPSL=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\ZAPSLT.OBJ" : $(SOURCE) $(DEP_CPP_ZAPSL) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_ZAPSL=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\ZAPSLT.OBJ" : $(SOURCE) $(DEP_CPP_ZAPSL) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\ZAPSLT.SBR" : $(SOURCE) $(DEP_CPP_ZAPSL) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\KEYCMP.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_KEYCM=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\KEYCMP.OBJ" : $(SOURCE) $(DEP_CPP_KEYCM) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_KEYCM=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\KEYCMP.OBJ" : $(SOURCE) $(DEP_CPP_KEYCM) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\KEYCMP.SBR" : $(SOURCE) $(DEP_CPP_KEYCM) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\KEYINI.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_KEYINI=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\KEYINI.OBJ" : $(SOURCE) $(DEP_CPP_KEYINI) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_KEYINI=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\KEYINI.OBJ" : $(SOURCE) $(DEP_CPP_KEYINI) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\KEYINI.SBR" : $(SOURCE) $(DEP_CPP_KEYINI) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\NGMC.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_NGMC_=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\NGMC.OBJ" : $(SOURCE) $(DEP_CPP_NGMC_) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_NGMC_=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\NGMC.OBJ" : $(SOURCE) $(DEP_CPP_NGMC_) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\NGMC.SBR" : $(SOURCE) $(DEP_CPP_NGMC_) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\KEYCAT.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_KEYCA=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\KEYCAT.OBJ" : $(SOURCE) $(DEP_CPP_KEYCA) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_KEYCA=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\KEYCAT.OBJ" : $(SOURCE) $(DEP_CPP_KEYCA) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\KEYCAT.SBR" : $(SOURCE) $(DEP_CPP_KEYCA) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DIO_INIT.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_DIO_I=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\DBVERSIO.H"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\DIO_INIT.OBJ" : $(SOURCE) $(DEP_CPP_DIO_I) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_DIO_I=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\DBVERSIO.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\DIO_INIT.OBJ" : $(SOURCE) $(DEP_CPP_DIO_I) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\DIO_INIT.SBR" : $(SOURCE) $(DEP_CPP_DIO_I) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MYCRYPT.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_MYCRY=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\MYCRYPT.OBJ" : $(SOURCE) $(DEP_CPP_MYCRY) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_MYCRY=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\MYCRYPT.OBJ" : $(SOURCE) $(DEP_CPP_MYCRY) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\MYCRYPT.SBR" : $(SOURCE) $(DEP_CPP_MYCRY) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ZDISPOSE.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_ZDISP=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\ZDISPOSE.OBJ" : $(SOURCE) $(DEP_CPP_ZDISP) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_ZDISP=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\ZDISPOSE.OBJ" : $(SOURCE) $(DEP_CPP_ZDISP) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\ZDISPOSE.SBR" : $(SOURCE) $(DEP_CPP_ZDISP) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SETERR.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_SETER=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ERRDB.H"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\SETERR.OBJ" : $(SOURCE) $(DEP_CPP_SETER) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_SETER=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ERRDB.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\SETERR.OBJ" : $(SOURCE) $(DEP_CPP_SETER) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\SETERR.SBR" : $(SOURCE) $(DEP_CPP_SETER) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\KEYLAST.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_KEYLA=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\KEYLAST.OBJ" : $(SOURCE) $(DEP_CPP_KEYLA) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_KEYLA=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\KEYLAST.OBJ" : $(SOURCE) $(DEP_CPP_KEYLA) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\KEYLAST.SBR" : $(SOURCE) $(DEP_CPP_KEYLA) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\HTWIND_F.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_HTWIN=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\HTWIND_F.OBJ" : $(SOURCE) $(DEP_CPP_HTWIN) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_HTWIN=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\HTWIND_F.OBJ" : $(SOURCE) $(DEP_CPP_HTWIN) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\HTWIND_F.SBR" : $(SOURCE) $(DEP_CPP_HTWIN) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GENBACK.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_GENBA=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\DBVERSIO.H"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\GENBACK.OBJ" : $(SOURCE) $(DEP_CPP_GENBA) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_GENBA=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\DBVERSIO.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\GENBACK.OBJ" : $(SOURCE) $(DEP_CPP_GENBA) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\GENBACK.SBR" : $(SOURCE) $(DEP_CPP_GENBA) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRNCHR.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_STRNC=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\STRNCHR.OBJ" : $(SOURCE) $(DEP_CPP_STRNC) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_STRNC=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\STRNCHR.OBJ" : $(SOURCE) $(DEP_CPP_STRNC) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\STRNCHR.SBR" : $(SOURCE) $(DEP_CPP_STRNC) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\HTCONT.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_HTCON=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\HTCONT.OBJ" : $(SOURCE) $(DEP_CPP_HTCON) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_HTCON=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\HTCONT.OBJ" : $(SOURCE) $(DEP_CPP_HTCON) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\HTCONT.SBR" : $(SOURCE) $(DEP_CPP_HTCON) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SHRINK.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_SHRIN=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\SHRINK.OBJ" : $(SOURCE) $(DEP_CPP_SHRIN) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_SHRIN=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\SHRINK.OBJ" : $(SOURCE) $(DEP_CPP_SHRIN) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\SHRINK.SBR" : $(SOURCE) $(DEP_CPP_SHRIN) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DBCLOSE.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_DBCLO=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\DBCLOSE.OBJ" : $(SOURCE) $(DEP_CPP_DBCLO) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_DBCLO=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\DBCLOSE.OBJ" : $(SOURCE) $(DEP_CPP_DBCLO) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\DBCLOSE.SBR" : $(SOURCE) $(DEP_CPP_DBCLO) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\QTSPLIT.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_QTSPL=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\QTSPLIT.OBJ" : $(SOURCE) $(DEP_CPP_QTSPL) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_QTSPL=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\QTSPLIT.OBJ" : $(SOURCE) $(DEP_CPP_QTSPL) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\QTSPLIT.SBR" : $(SOURCE) $(DEP_CPP_QTSPL) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\KEY_IO.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_KEY_I=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\KEY_IO.OBJ" : $(SOURCE) $(DEP_CPP_KEY_I) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_KEY_I=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\KEY_IO.OBJ" : $(SOURCE) $(DEP_CPP_KEY_I) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\KEY_IO.SBR" : $(SOURCE) $(DEP_CPP_KEY_I) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FDBOPEN.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_FDBOP=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\FDBOPEN.OBJ" : $(SOURCE) $(DEP_CPP_FDBOP) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_FDBOP=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\FDBOPEN.OBJ" : $(SOURCE) $(DEP_CPP_FDBOP) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\FDBOPEN.SBR" : $(SOURCE) $(DEP_CPP_FDBOP) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\NODFIL.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_NODFI=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\NODFIL.OBJ" : $(SOURCE) $(DEP_CPP_NODFI) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_NODFI=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\NODFIL.OBJ" : $(SOURCE) $(DEP_CPP_NODFI) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\NODFIL.SBR" : $(SOURCE) $(DEP_CPP_NODFI) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ZKEYREAD.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_ZKEYR=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\ZKEYREAD.OBJ" : $(SOURCE) $(DEP_CPP_ZKEYR) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_ZKEYR=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\ZKEYREAD.OBJ" : $(SOURCE) $(DEP_CPP_ZKEYR) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\ZKEYREAD.SBR" : $(SOURCE) $(DEP_CPP_ZKEYR) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ZACCESS.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_ZACCE=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\ZACCESS.OBJ" : $(SOURCE) $(DEP_CPP_ZACCE) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_ZACCE=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\ZACCESS.OBJ" : $(SOURCE) $(DEP_CPP_ZACCE) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\ZACCESS.SBR" : $(SOURCE) $(DEP_CPP_ZACCE) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\HTDEL.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_HTDEL=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\HTDEL.OBJ" : $(SOURCE) $(DEP_CPP_HTDEL) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_HTDEL=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\HTDEL.OBJ" : $(SOURCE) $(DEP_CPP_HTDEL) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\HTDEL.SBR" : $(SOURCE) $(DEP_CPP_HTDEL) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\HTINS.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_HTINS=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\HTINS.OBJ" : $(SOURCE) $(DEP_CPP_HTINS) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_HTINS=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\HTINS.OBJ" : $(SOURCE) $(DEP_CPP_HTINS) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\HTINS.SBR" : $(SOURCE) $(DEP_CPP_HTINS) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\QUAD.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_QUAD_=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\QUAD.OBJ" : $(SOURCE) $(DEP_CPP_QUAD_) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_QUAD_=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\QUAD.OBJ" : $(SOURCE) $(DEP_CPP_QUAD_) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\QUAD.SBR" : $(SOURCE) $(DEP_CPP_QUAD_) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\INSERT.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_INSER=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\INSERT.OBJ" : $(SOURCE) $(DEP_CPP_INSER) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_INSER=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\INSERT.OBJ" : $(SOURCE) $(DEP_CPP_INSER) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\INSERT.SBR" : $(SOURCE) $(DEP_CPP_INSER) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\QTWIND_F.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_QTWIN=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\QTWIND_F.OBJ" : $(SOURCE) $(DEP_CPP_QTWIN) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_QTWIN=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\QTWIND_F.OBJ" : $(SOURCE) $(DEP_CPP_QTWIN) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\QTWIND_F.SBR" : $(SOURCE) $(DEP_CPP_QTWIN) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\LOCSLT.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_LOCSL=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\LOCSLT.OBJ" : $(SOURCE) $(DEP_CPP_LOCSL) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_LOCSL=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\LOCSLT.OBJ" : $(SOURCE) $(DEP_CPP_LOCSL) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\LOCSLT.SBR" : $(SOURCE) $(DEP_CPP_LOCSL) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ZKEYFIND.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_ZKEYF=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\ZKEYFIND.OBJ" : $(SOURCE) $(DEP_CPP_ZKEYF) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_ZKEYF=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\ZKEYFIND.OBJ" : $(SOURCE) $(DEP_CPP_ZKEYF) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\ZKEYFIND.SBR" : $(SOURCE) $(DEP_CPP_ZKEYF) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PUTINL.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_PUTIN=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\PUTINL.OBJ" : $(SOURCE) $(DEP_CPP_PUTIN) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_PUTIN=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\PUTINL.OBJ" : $(SOURCE) $(DEP_CPP_PUTIN) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\PUTINL.SBR" : $(SOURCE) $(DEP_CPP_PUTIN) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CRYPT.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_CRYPT=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\CRYPT.OBJ" : $(SOURCE) $(DEP_CPP_CRYPT) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_CRYPT=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\CRYPT.OBJ" : $(SOURCE) $(DEP_CPP_CRYPT) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\CRYPT.SBR" : $(SOURCE) $(DEP_CPP_CRYPT) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ZKEYFRST.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_ZKEYFR=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\ZKEYFRST.OBJ" : $(SOURCE) $(DEP_CPP_ZKEYFR) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_ZKEYFR=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\ZKEYFRST.OBJ" : $(SOURCE) $(DEP_CPP_ZKEYFR) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\ZKEYFRST.SBR" : $(SOURCE) $(DEP_CPP_ZKEYFR) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\NODEXP.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_NODEX=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\NODEXP.OBJ" : $(SOURCE) $(DEP_CPP_NODEX) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_NODEX=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\NODEXP.OBJ" : $(SOURCE) $(DEP_CPP_NODEX) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\NODEXP.SBR" : $(SOURCE) $(DEP_CPP_NODEX) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\STATIST.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_STATI=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\STATIST.OBJ" : $(SOURCE) $(DEP_CPP_STATI) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_STATI=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\STATIST.OBJ" : $(SOURCE) $(DEP_CPP_STATI) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\STATIST.SBR" : $(SOURCE) $(DEP_CPP_STATI) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\LADRC.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_LADRC=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\LADRC.OBJ" : $(SOURCE) $(DEP_CPP_LADRC) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_LADRC=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\LADRC.OBJ" : $(SOURCE) $(DEP_CPP_LADRC) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\LADRC.SBR" : $(SOURCE) $(DEP_CPP_LADRC) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DELETE.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_DELET=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\DELETE.OBJ" : $(SOURCE) $(DEP_CPP_DELET) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_DELET=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\DELETE.OBJ" : $(SOURCE) $(DEP_CPP_DELET) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\DELETE.SBR" : $(SOURCE) $(DEP_CPP_DELET) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\LISTEN.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_LISTE=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\LISTEN.OBJ" : $(SOURCE) $(DEP_CPP_LISTE) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_LISTE=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\LISTEN.OBJ" : $(SOURCE) $(DEP_CPP_LISTE) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\LISTEN.SBR" : $(SOURCE) $(DEP_CPP_LISTE) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GETDWENT.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_GETDW=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\DWD.H"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	
# ADD CPP /D "COMPRESS_PWD"

"$(INTDIR)\GETDWENT.OBJ" : $(SOURCE) $(DEP_CPP_GETDW) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "__CV__" /D "STRICT" /D\
 "DLL" /D "MSWIND" /D "WIN32" /D "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D\
 "__TRIAS01DLL__" /D "COMPRESS_PWD" /Fp"$(INTDIR)/Trias321.pch"\
 /Yu"trias01p.hxx" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_GETDW=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\DWD.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	
# ADD CPP /D "COMPRESS_PWD"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "__CV__" /D\
 "STRICT" /D "DLL" /D "MSWIND" /D "WIN32" /D "_WINDOWS" /D "__XT" /D\
 "__DEXPROCS" /D "__TRIAS01DLL__" /D "COMPRESS_PWD" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/trias321d.pch" /Yu"trias01p.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/trias321d.pdb" /c $(SOURCE) \
	

"$(INTDIR)\GETDWENT.OBJ" : $(SOURCE) $(DEP_CPP_GETDW) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"
   $(BuildCmds)

"$(INTDIR)\GETDWENT.SBR" : $(SOURCE) $(DEP_CPP_GETDW) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\EVISERR.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_EVISE=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\VISERROR.HXX"\
	{$(INCLUDE)}"\VISERROR.INL"\
	

"$(INTDIR)\EVISERR.OBJ" : $(SOURCE) $(DEP_CPP_EVISE) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_EVISE=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\VISERROR.HXX"\
	{$(INCLUDE)}"\VISERROR.INL"\
	

"$(INTDIR)\EVISERR.OBJ" : $(SOURCE) $(DEP_CPP_EVISE) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\EVISERR.SBR" : $(SOURCE) $(DEP_CPP_EVISE) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\HTSPLIT.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_HTSPL=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\HTSPLIT.OBJ" : $(SOURCE) $(DEP_CPP_HTSPL) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_HTSPL=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\HTSPLIT.OBJ" : $(SOURCE) $(DEP_CPP_HTSPL) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\HTSPLIT.SBR" : $(SOURCE) $(DEP_CPP_HTSPL) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\HTPREP.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_HTPRE=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\HTPREP.OBJ" : $(SOURCE) $(DEP_CPP_HTPRE) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_HTPRE=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\HTPREP.OBJ" : $(SOURCE) $(DEP_CPP_HTPRE) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\HTPREP.SBR" : $(SOURCE) $(DEP_CPP_HTPRE) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\NULLCMP.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_NULLC=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	
# ADD CPP /D "NULLCMP"

"$(INTDIR)\NULLCMP.OBJ" : $(SOURCE) $(DEP_CPP_NULLC) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "__CV__" /D "STRICT" /D\
 "DLL" /D "MSWIND" /D "WIN32" /D "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D\
 "__TRIAS01DLL__" /D "NULLCMP" /Fp"$(INTDIR)/Trias321.pch" /Yu"trias01p.hxx"\
 /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_NULLC=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	
# ADD CPP /D "NULLCMP"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "__CV__" /D\
 "STRICT" /D "DLL" /D "MSWIND" /D "WIN32" /D "_WINDOWS" /D "__XT" /D\
 "__DEXPROCS" /D "__TRIAS01DLL__" /D "NULLCMP" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/trias321d.pch" /Yu"trias01p.hxx" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/trias321d.pdb" /c $(SOURCE) \
	

"$(INTDIR)\NULLCMP.OBJ" : $(SOURCE) $(DEP_CPP_NULLC) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"
   $(BuildCmds)

"$(INTDIR)\NULLCMP.SBR" : $(SOURCE) $(DEP_CPP_NULLC) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\HTWINDOW.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_HTWIND=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\HTWINDOW.OBJ" : $(SOURCE) $(DEP_CPP_HTWIND) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_HTWIND=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\HTWINDOW.OBJ" : $(SOURCE) $(DEP_CPP_HTWIND) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\HTWINDOW.SBR" : $(SOURCE) $(DEP_CPP_HTWIND) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\QTSHRINK.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_QTSHR=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\QTSHRINK.OBJ" : $(SOURCE) $(DEP_CPP_QTSHR) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_QTSHR=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\QTSHRINK.OBJ" : $(SOURCE) $(DEP_CPP_QTSHR) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\QTSHRINK.SBR" : $(SOURCE) $(DEP_CPP_QTSHR) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DB_IO.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_DB_IO=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\DB_IO.OBJ" : $(SOURCE) $(DEP_CPP_DB_IO) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_DB_IO=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\DB_IO.OBJ" : $(SOURCE) $(DEP_CPP_DB_IO) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\DB_IO.SBR" : $(SOURCE) $(DEP_CPP_DB_IO) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\HTSEARCH.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_HTSEA=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\HTSEARCH.OBJ" : $(SOURCE) $(DEP_CPP_HTSEA) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_HTSEA=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\HTSEARCH.OBJ" : $(SOURCE) $(DEP_CPP_HTSEA) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\HTSEARCH.SBR" : $(SOURCE) $(DEP_CPP_HTSEA) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\VERSION.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_VERSI=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\VERSION.OBJ" : $(SOURCE) $(DEP_CPP_VERSI) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_VERSI=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\VERSION.OBJ" : $(SOURCE) $(DEP_CPP_VERSI) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\VERSION.SBR" : $(SOURCE) $(DEP_CPP_VERSI) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\NODSPL.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_NODSP=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\NODSPL.OBJ" : $(SOURCE) $(DEP_CPP_NODSP) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_NODSP=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\NODSPL.OBJ" : $(SOURCE) $(DEP_CPP_NODSP) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\NODSPL.SBR" : $(SOURCE) $(DEP_CPP_NODSP) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\LOCLAST.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_LOCLA=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\LOCLAST.OBJ" : $(SOURCE) $(DEP_CPP_LOCLA) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_LOCLA=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\LOCLAST.OBJ" : $(SOURCE) $(DEP_CPP_LOCLA) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\LOCLAST.SBR" : $(SOURCE) $(DEP_CPP_LOCLA) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\NEWFILE.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_NEWFI=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\NEWFILE.OBJ" : $(SOURCE) $(DEP_CPP_NEWFI) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_NEWFI=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\NEWFILE.OBJ" : $(SOURCE) $(DEP_CPP_NEWFI) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\NEWFILE.SBR" : $(SOURCE) $(DEP_CPP_NEWFI) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ZKEYPREV.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_ZKEYP=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\ZKEYPREV.OBJ" : $(SOURCE) $(DEP_CPP_ZKEYP) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_ZKEYP=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\ZKEYPREV.OBJ" : $(SOURCE) $(DEP_CPP_ZKEYP) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\ZKEYPREV.SBR" : $(SOURCE) $(DEP_CPP_ZKEYP) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GETHD_F.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_GETHD=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\GETHD_F.OBJ" : $(SOURCE) $(DEP_CPP_GETHD) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_GETHD=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\GETHD_F.OBJ" : $(SOURCE) $(DEP_CPP_GETHD) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\GETHD_F.SBR" : $(SOURCE) $(DEP_CPP_GETHD) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FLEX.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_FLEX_=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\FLEX.H"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\FLEX.OBJ" : $(SOURCE) $(DEP_CPP_FLEX_) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_FLEX_=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\FLEX.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\FLEX.OBJ" : $(SOURCE) $(DEP_CPP_FLEX_) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\FLEX.SBR" : $(SOURCE) $(DEP_CPP_FLEX_) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PARENT.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_PAREN=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\PARENT.OBJ" : $(SOURCE) $(DEP_CPP_PAREN) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_PAREN=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\PARENT.OBJ" : $(SOURCE) $(DEP_CPP_PAREN) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\PARENT.SBR" : $(SOURCE) $(DEP_CPP_PAREN) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ZRESTOR.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_ZREST=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\DBVERSIO.H"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\ZRESTOR.OBJ" : $(SOURCE) $(DEP_CPP_ZREST) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_ZREST=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\DBVERSIO.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\ZRESTOR.OBJ" : $(SOURCE) $(DEP_CPP_ZREST) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\ZRESTOR.SBR" : $(SOURCE) $(DEP_CPP_ZREST) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GETPATH.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_GETPA=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\GETPATH.OBJ" : $(SOURCE) $(DEP_CPP_GETPA) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_GETPA=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\GETPATH.OBJ" : $(SOURCE) $(DEP_CPP_GETPA) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\GETPATH.SBR" : $(SOURCE) $(DEP_CPP_GETPA) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ENOMEM.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_ENOME=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\ENOMEM.OBJ" : $(SOURCE) $(DEP_CPP_ENOME) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_ENOME=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\ENOMEM.OBJ" : $(SOURCE) $(DEP_CPP_ENOME) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\ENOMEM.SBR" : $(SOURCE) $(DEP_CPP_ENOME) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TRIAS01P.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_TRIAS=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	
# ADD CPP /Yc"trias01p.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "__CV__" /D "STRICT" /D\
 "DLL" /D "MSWIND" /D "WIN32" /D "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D\
 "__TRIAS01DLL__" /Fp"$(INTDIR)/Trias321.pch" /Yc"trias01p.hxx" /Fo"$(INTDIR)/"\
 /c $(SOURCE) \
	

"$(INTDIR)\TRIAS01P.OBJ" : $(SOURCE) $(DEP_CPP_TRIAS) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Trias321.pch" : $(SOURCE) $(DEP_CPP_TRIAS) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_TRIAS=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\trias02m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	
# ADD CPP /Yc"trias01p.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "__CV__" /D\
 "STRICT" /D "DLL" /D "MSWIND" /D "WIN32" /D "_WINDOWS" /D "__XT" /D\
 "__DEXPROCS" /D "__TRIAS01DLL__" /FR"$(INTDIR)/" /Fp"$(INTDIR)/trias321d.pch"\
 /Yc"trias01p.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/trias321d.pdb" /c $(SOURCE) \
	

"$(INTDIR)\TRIAS01P.OBJ" : $(SOURCE) $(DEP_CPP_TRIAS) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\TRIAS01P.SBR" : $(SOURCE) $(DEP_CPP_TRIAS) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\trias321d.pch" : $(SOURCE) $(DEP_CPP_TRIAS) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\QTWINDOW.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_QTWIND=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\QTWINDOW.OBJ" : $(SOURCE) $(DEP_CPP_QTWIND) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_QTWIND=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\QTWINDOW.OBJ" : $(SOURCE) $(DEP_CPP_QTWIND) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\QTWINDOW.SBR" : $(SOURCE) $(DEP_CPP_QTWIND) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GETHDLEN.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_GETHDL=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\GETHDLEN.OBJ" : $(SOURCE) $(DEP_CPP_GETHDL) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_GETHDL=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\GETHDLEN.OBJ" : $(SOURCE) $(DEP_CPP_GETHDL) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\GETHDLEN.SBR" : $(SOURCE) $(DEP_CPP_GETHDL) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ROOTSP.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_ROOTS=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\ROOTSP.OBJ" : $(SOURCE) $(DEP_CPP_ROOTS) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_ROOTS=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\ROOTSP.OBJ" : $(SOURCE) $(DEP_CPP_ROOTS) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\ROOTSP.SBR" : $(SOURCE) $(DEP_CPP_ROOTS) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DBCODB.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_DBCOD=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\DBCODB.OBJ" : $(SOURCE) $(DEP_CPP_DBCOD) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_DBCOD=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\DBCODB.OBJ" : $(SOURCE) $(DEP_CPP_DBCOD) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\DBCODB.SBR" : $(SOURCE) $(DEP_CPP_DBCOD) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\QTSEARCH.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_QTSEA=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\QTSEARCH.OBJ" : $(SOURCE) $(DEP_CPP_QTSEA) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_QTSEA=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\QTSEARCH.OBJ" : $(SOURCE) $(DEP_CPP_QTSEA) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\QTSEARCH.SBR" : $(SOURCE) $(DEP_CPP_QTSEA) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PUTHD_F.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_PUTHD=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	
NODEP_CPP_PUTHD=\
	".\vmstypes.h"\
	

"$(INTDIR)\PUTHD_F.OBJ" : $(SOURCE) $(DEP_CPP_PUTHD) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_PUTHD=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	
NODEP_CPP_PUTHD=\
	".\vmstypes.h"\
	

"$(INTDIR)\PUTHD_F.OBJ" : $(SOURCE) $(DEP_CPP_PUTHD) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\PUTHD_F.SBR" : $(SOURCE) $(DEP_CPP_PUTHD) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\QTCONT.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_QTCON=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\QTCONT.OBJ" : $(SOURCE) $(DEP_CPP_QTCON) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_QTCON=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\QTCONT.OBJ" : $(SOURCE) $(DEP_CPP_QTCON) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\QTCONT.SBR" : $(SOURCE) $(DEP_CPP_QTCON) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DELHD_F.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_DELHD=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\DELHD_F.OBJ" : $(SOURCE) $(DEP_CPP_DELHD) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_DELHD=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\DELHD_F.OBJ" : $(SOURCE) $(DEP_CPP_DELHD) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\DELHD_F.SBR" : $(SOURCE) $(DEP_CPP_DELHD) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\KEYREAD.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_KEYRE=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\KEYREAD.OBJ" : $(SOURCE) $(DEP_CPP_KEYRE) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_KEYRE=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\KEYREAD.OBJ" : $(SOURCE) $(DEP_CPP_KEYRE) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\KEYREAD.SBR" : $(SOURCE) $(DEP_CPP_KEYRE) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\KEYDEL.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_KEYDE=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\KEYDEL.OBJ" : $(SOURCE) $(DEP_CPP_KEYDE) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_KEYDE=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\KEYDEL.OBJ" : $(SOURCE) $(DEP_CPP_KEYDE) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\KEYDEL.SBR" : $(SOURCE) $(DEP_CPP_KEYDE) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ZKEYNEXT.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_ZKEYN=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\ZKEYNEXT.OBJ" : $(SOURCE) $(DEP_CPP_ZKEYN) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_ZKEYN=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\ZKEYNEXT.OBJ" : $(SOURCE) $(DEP_CPP_ZKEYN) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\ZKEYNEXT.SBR" : $(SOURCE) $(DEP_CPP_ZKEYN) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\KEYNEXT.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_KEYNE=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\KEYNEXT.OBJ" : $(SOURCE) $(DEP_CPP_KEYNE) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_KEYNE=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\KEYNEXT.OBJ" : $(SOURCE) $(DEP_CPP_KEYNE) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\KEYNEXT.SBR" : $(SOURCE) $(DEP_CPP_KEYNE) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ACTIVATE.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_ACTIV=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\ACTIVATE.OBJ" : $(SOURCE) $(DEP_CPP_ACTIV) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_ACTIV=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\ACTIVATE.OBJ" : $(SOURCE) $(DEP_CPP_ACTIV) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\ACTIVATE.SBR" : $(SOURCE) $(DEP_CPP_ACTIV) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\REINDEX.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_REIND=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\REINDEX.OBJ" : $(SOURCE) $(DEP_CPP_REIND) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_REIND=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\REINDEX.OBJ" : $(SOURCE) $(DEP_CPP_REIND) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\REINDEX.SBR" : $(SOURCE) $(DEP_CPP_REIND) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\OVERFL.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_OVERF=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\OVERFL.OBJ" : $(SOURCE) $(DEP_CPP_OVERF) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_OVERF=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\OVERFL.OBJ" : $(SOURCE) $(DEP_CPP_OVERF) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\OVERFL.SBR" : $(SOURCE) $(DEP_CPP_OVERF) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\KEYUTIL.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_KEYUT=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\KEYUTIL.OBJ" : $(SOURCE) $(DEP_CPP_KEYUT) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_KEYUT=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\KEYUTIL.OBJ" : $(SOURCE) $(DEP_CPP_KEYUT) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\KEYUTIL.SBR" : $(SOURCE) $(DEP_CPP_KEYUT) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\KEYFRST.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_KEYFR=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\KEYFRST.OBJ" : $(SOURCE) $(DEP_CPP_KEYFR) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_KEYFR=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\KEYFRST.OBJ" : $(SOURCE) $(DEP_CPP_KEYFR) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\KEYFRST.SBR" : $(SOURCE) $(DEP_CPP_KEYFR) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\EINVADDR.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_EINVA=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\EINVADDR.OBJ" : $(SOURCE) $(DEP_CPP_EINVA) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_EINVA=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\EINVADDR.OBJ" : $(SOURCE) $(DEP_CPP_EINVA) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\EINVADDR.SBR" : $(SOURCE) $(DEP_CPP_EINVA) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ZACTIV.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_ZACTI=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\ZACTIV.OBJ" : $(SOURCE) $(DEP_CPP_ZACTI) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_ZACTI=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\ZACTIV.OBJ" : $(SOURCE) $(DEP_CPP_ZACTI) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\ZACTIV.SBR" : $(SOURCE) $(DEP_CPP_ZACTI) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GETDWNAM.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_GETDWN=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\DWD.H"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\GETDWNAM.OBJ" : $(SOURCE) $(DEP_CPP_GETDWN) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_GETDWN=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\DWD.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\GETDWNAM.OBJ" : $(SOURCE) $(DEP_CPP_GETDWN) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\GETDWNAM.SBR" : $(SOURCE) $(DEP_CPP_GETDWN) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ZREADREC.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_ZREAD=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\ZREADREC.OBJ" : $(SOURCE) $(DEP_CPP_ZREAD) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_ZREAD=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\ZREADREC.OBJ" : $(SOURCE) $(DEP_CPP_ZREAD) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\ZREADREC.SBR" : $(SOURCE) $(DEP_CPP_ZREAD) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\KEYLOC.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_KEYLO=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\KEYLOC.OBJ" : $(SOURCE) $(DEP_CPP_KEYLO) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_KEYLO=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\KEYLOC.OBJ" : $(SOURCE) $(DEP_CPP_KEYLO) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\KEYLOC.SBR" : $(SOURCE) $(DEP_CPP_KEYLO) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ZKEYLAST.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_ZKEYL=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\ZKEYLAST.OBJ" : $(SOURCE) $(DEP_CPP_ZKEYL) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_ZKEYL=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\ZKEYLAST.OBJ" : $(SOURCE) $(DEP_CPP_ZKEYL) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\ZKEYLAST.SBR" : $(SOURCE) $(DEP_CPP_ZKEYL) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DBOPEN.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_DBOPE=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	".\TRIAS01R.H"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\DBCONFIG.H"\
	{$(INCLUDE)}"\DBD.H"\
	{$(INCLUDE)}"\Dbd.hxx"\
	{$(INCLUDE)}"\DBDTEMPL.H"\
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\DWD.H"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\stghelp.hxx"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\DBOPEN.OBJ" : $(SOURCE) $(DEP_CPP_DBOPE) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_DBOPE=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	".\TRIAS01R.H"\
	{$(INCLUDE)}"\DBCONFIG.H"\
	{$(INCLUDE)}"\DBD.H"\
	{$(INCLUDE)}"\Dbd.hxx"\
	{$(INCLUDE)}"\DBDTEMPL.H"\
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\DWD.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\stghelp.hxx"\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\DBOPEN.OBJ" : $(SOURCE) $(DEP_CPP_DBOPE) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\DBOPEN.SBR" : $(SOURCE) $(DEP_CPP_DBOPE) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GETDWUID.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_GETDWU=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\DWD.H"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\GETDWUID.OBJ" : $(SOURCE) $(DEP_CPP_GETDWU) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_GETDWU=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\DWD.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\GETDWUID.OBJ" : $(SOURCE) $(DEP_CPP_GETDWU) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\GETDWUID.SBR" : $(SOURCE) $(DEP_CPP_GETDWU) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\LIBMAIN1.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_LIBMA=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\LIBMAIN1.OBJ" : $(SOURCE) $(DEP_CPP_LIBMA) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "__CV__" /D "STRICT" /D\
 "DLL" /D "MSWIND" /D "WIN32" /D "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D\
 "__TRIAS01DLL__" /Fp"$(INTDIR)/Trias321.pch" /Yu"trias01p.hxx" /Fo"$(INTDIR)/"\
 /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_LIBMA=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	
# ADD CPP /WX /Od

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "__CV__" /D\
 "STRICT" /D "DLL" /D "MSWIND" /D "WIN32" /D "_WINDOWS" /D "__XT" /D\
 "__DEXPROCS" /D "__TRIAS01DLL__" /FR"$(INTDIR)/" /Fp"$(INTDIR)/trias321d.pch"\
 /Yu"trias01p.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/trias321d.pdb" /c $(SOURCE) \
	

"$(INTDIR)\LIBMAIN1.OBJ" : $(SOURCE) $(DEP_CPP_LIBMA) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"
   $(BuildCmds)

"$(INTDIR)\LIBMAIN1.SBR" : $(SOURCE) $(DEP_CPP_LIBMA) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TZAPSLT.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_TZAPS=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\TZAPSLT.OBJ" : $(SOURCE) $(DEP_CPP_TZAPS) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_TZAPS=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\TZAPSLT.OBJ" : $(SOURCE) $(DEP_CPP_TZAPS) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\TZAPSLT.SBR" : $(SOURCE) $(DEP_CPP_TZAPS) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\QTPREP.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_QTPRE=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\QTPREP.OBJ" : $(SOURCE) $(DEP_CPP_QTPRE) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_QTPRE=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\QTPREP.OBJ" : $(SOURCE) $(DEP_CPP_QTPRE) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\QTPREP.SBR" : $(SOURCE) $(DEP_CPP_QTPRE) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ERRFKT.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_ERRFK=\
	".\ERRFKT.HXX"\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\ERRFKT.OBJ" : $(SOURCE) $(DEP_CPP_ERRFK) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_ERRFK=\
	".\ERRFKT.HXX"\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\ERRFKT.OBJ" : $(SOURCE) $(DEP_CPP_ERRFK) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\ERRFKT.SBR" : $(SOURCE) $(DEP_CPP_ERRFK) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DBINITC.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_DBINI=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\DBINITC.OBJ" : $(SOURCE) $(DEP_CPP_DBINI) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_DBINI=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\DBINITC.OBJ" : $(SOURCE) $(DEP_CPP_DBINI) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\DBINITC.SBR" : $(SOURCE) $(DEP_CPP_DBINI) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PGZERO.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_PGZER=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\DBVERSIO.H"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\PGZERO.OBJ" : $(SOURCE) $(DEP_CPP_PGZER) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_PGZER=\
	".\Syncdb.hxx"\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\DBVERSIO.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\PGZERO.OBJ" : $(SOURCE) $(DEP_CPP_PGZER) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\PGZERO.SBR" : $(SOURCE) $(DEP_CPP_PGZER) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\KEYPREV.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_KEYPR=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\KEYPREV.OBJ" : $(SOURCE) $(DEP_CPP_KEYPR) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_KEYPR=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\KEYPREV.OBJ" : $(SOURCE) $(DEP_CPP_KEYPR) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\KEYPREV.SBR" : $(SOURCE) $(DEP_CPP_KEYPR) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\BITS.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_BITS_=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\BITS.OBJ" : $(SOURCE) $(DEP_CPP_BITS_) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_BITS_=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\BITS.OBJ" : $(SOURCE) $(DEP_CPP_BITS_) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\BITS.SBR" : $(SOURCE) $(DEP_CPP_BITS_) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CUBE.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_CUBE_=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\CUBE.OBJ" : $(SOURCE) $(DEP_CPP_CUBE_) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_CUBE_=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\CUBE.OBJ" : $(SOURCE) $(DEP_CPP_CUBE_) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\CUBE.SBR" : $(SOURCE) $(DEP_CPP_CUBE_) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\BAKKEY.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_BAKKE=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\Bakkey.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\DBCONFIG.H"\
	{$(INCLUDE)}"\DBD.H"\
	{$(INCLUDE)}"\Dbd.hxx"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\STRFCNS.HXX"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\BAKKEY.OBJ" : $(SOURCE) $(DEP_CPP_BAKKE) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_BAKKE=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\Bakkey.hxx"\
	{$(INCLUDE)}"\DBCONFIG.H"\
	{$(INCLUDE)}"\DBD.H"\
	{$(INCLUDE)}"\Dbd.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\STRFCNS.HXX"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\BAKKEY.OBJ" : $(SOURCE) $(DEP_CPP_BAKKE) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\BAKKEY.SBR" : $(SOURCE) $(DEP_CPP_BAKKE) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DBD.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_DBD_C=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\Bakkey.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\DBCONFIG.H"\
	{$(INCLUDE)}"\DBD.H"\
	{$(INCLUDE)}"\Dbd.hxx"\
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STRFCNS.HXX"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TARGETFI.HXX"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\DBD.OBJ" : $(SOURCE) $(DEP_CPP_DBD_C) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_DBD_C=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\Bakkey.hxx"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\DBCONFIG.H"\
	{$(INCLUDE)}"\DBD.H"\
	{$(INCLUDE)}"\Dbd.hxx"\
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\RESSTRG.H"\
	{$(INCLUDE)}"\STRDUP.HXX"\
	{$(INCLUDE)}"\STRFCNS.HXX"\
	{$(INCLUDE)}"\TARGETFI.HXX"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\VERSIONS.H"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\DBD.OBJ" : $(SOURCE) $(DEP_CPP_DBD_C) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\DBD.SBR" : $(SOURCE) $(DEP_CPP_DBD_C) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRFCNS.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_STRFC=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRFCNS.HXX"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\STRFCNS.OBJ" : $(SOURCE) $(DEP_CPP_STRFC) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_STRFC=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\STRFCNS.HXX"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\STRFCNS.OBJ" : $(SOURCE) $(DEP_CPP_STRFC) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\STRFCNS.SBR" : $(SOURCE) $(DEP_CPP_STRFC) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TARGETFI.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_TARGE=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\DBCONFIG.H"\
	{$(INCLUDE)}"\DBD.H"\
	{$(INCLUDE)}"\Dbd.hxx"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TARGETFI.HXX"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\TARGETFI.OBJ" : $(SOURCE) $(DEP_CPP_TARGE) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_TARGE=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\DBCONFIG.H"\
	{$(INCLUDE)}"\DBD.H"\
	{$(INCLUDE)}"\Dbd.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TARGETFI.HXX"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\TARGETFI.OBJ" : $(SOURCE) $(DEP_CPP_TARGE) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\TARGETFI.SBR" : $(SOURCE) $(DEP_CPP_TARGE) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\RESOURCE.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_RESOU=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\DBDTEMPL.H"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\RESOURCE.OBJ" : $(SOURCE) $(DEP_CPP_RESOU) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_RESOU=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\DBDTEMPL.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\RESOURCE.OBJ" : $(SOURCE) $(DEP_CPP_RESOU) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\RESOURCE.SBR" : $(SOURCE) $(DEP_CPP_RESOU) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\eexterr.cxx

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_EEXTE=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\eexterr.obj" : $(SOURCE) $(DEP_CPP_EEXTE) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_EEXTE=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\eexterr.obj" : $(SOURCE) $(DEP_CPP_EEXTE) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\eexterr.sbr" : $(SOURCE) $(DEP_CPP_EEXTE) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\enfnderr.cxx

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_ENFND=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\enfnderr.obj" : $(SOURCE) $(DEP_CPP_ENFND) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_ENFND=\
	".\trias01p.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\enfnderr.obj" : $(SOURCE) $(DEP_CPP_ENFND) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\enfnderr.sbr" : $(SOURCE) $(DEP_CPP_ENFND) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\enospac.cxx

!IF  "$(CFG)" == "Trias321 - Win32 Release"

DEP_CPP_ENOSP=\
	".\trias01p.hxx"\
	".\TRIAS01R.H"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	

"$(INTDIR)\enospac.obj" : $(SOURCE) $(DEP_CPP_ENOSP) "$(INTDIR)"\
 "$(INTDIR)\Trias321.pch"


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

DEP_CPP_ENOSP=\
	".\trias01p.hxx"\
	".\TRIAS01R.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	

"$(INTDIR)\enospac.obj" : $(SOURCE) $(DEP_CPP_ENOSP) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"

"$(INTDIR)\enospac.sbr" : $(SOURCE) $(DEP_CPP_ENOSP) "$(INTDIR)"\
 "$(INTDIR)\trias321d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\obj32\Trias321.RC
DEP_RSC_TRIAS3=\
	".\obj32\trias321.rcv"\
	

!IF  "$(CFG)" == "Trias321 - Win32 Release"


"$(INTDIR)\Trias321.res" : $(SOURCE) $(DEP_RSC_TRIAS3) "$(INTDIR)"
   $(RSC) /l 0x407 /fo"$(INTDIR)/Trias321.res" /i "obj32" /d "NDEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"


"$(INTDIR)\Trias321.res" : $(SOURCE) $(DEP_RSC_TRIAS3) "$(INTDIR)"
   $(RSC) /l 0x407 /fo"$(INTDIR)/Trias321.res" /i "obj32" /d "_DEBUG" $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\obj32\TRiAS31d.def

!IF  "$(CFG)" == "Trias321 - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\obj32\TRiAS321.def

!IF  "$(CFG)" == "Trias321 - Win32 Release"

# PROP Exclude_From_Build 0

!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
