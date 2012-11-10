# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=Dbasedll - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Dbasedll - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Dbasedll - Win32 Release" && "$(CFG)" !=\
 "Dbasedll - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Dbasedll.mak" CFG="Dbasedll - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Dbasedll - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Dbasedll - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "Dbasedll - Win32 Debug"
MTL=mktyplib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "winrel"
# PROP Intermediate_Dir "winrel"
OUTDIR=.\winrel
INTDIR=.\winrel

ALL : "..\..\..\trias\trias\Dbasedll.dll"

CLEAN : 
	-@erase "$(INTDIR)\B4BLOCK.OBJ"
	-@erase "$(INTDIR)\BTTNCUR.OBJ"
	-@erase "$(INTDIR)\C4.OBJ"
	-@erase "$(INTDIR)\C4BCD.OBJ"
	-@erase "$(INTDIR)\C4CODE.OBJ"
	-@erase "$(INTDIR)\C4CODEOP.OBJ"
	-@erase "$(INTDIR)\CRCB.OBJ"
	-@erase "$(INTDIR)\D4APPEND.OBJ"
	-@erase "$(INTDIR)\D4CREATE.OBJ"
	-@erase "$(INTDIR)\D4DATA.OBJ"
	-@erase "$(INTDIR)\D4DATAFI.OBJ"
	-@erase "$(INTDIR)\D4DATAIN.OBJ"
	-@erase "$(INTDIR)\D4DATE.OBJ"
	-@erase "$(INTDIR)\D4FIELD.OBJ"
	-@erase "$(INTDIR)\D4GO.OBJ"
	-@erase "$(INTDIR)\D4LOCK.OBJ"
	-@erase "$(INTDIR)\D4PACK.OBJ"
	-@erase "$(INTDIR)\D4RECCNT.OBJ"
	-@erase "$(INTDIR)\D4SEEKDB.OBJ"
	-@erase "$(INTDIR)\D4WRITE.OBJ"
	-@erase "$(INTDIR)\D4XAPPBL.OBJ"
	-@erase "$(INTDIR)\D4XAPPEN.OBJ"
	-@erase "$(INTDIR)\D4XBOTTM.OBJ"
	-@erase "$(INTDIR)\D4XFLUSH.OBJ"
	-@erase "$(INTDIR)\D4XGO.OBJ"
	-@erase "$(INTDIR)\D4XGOEOF.OBJ"
	-@erase "$(INTDIR)\D4XLOCK.OBJ"
	-@erase "$(INTDIR)\D4XPOS.OBJ"
	-@erase "$(INTDIR)\D4XSEEK.OBJ"
	-@erase "$(INTDIR)\D4XSELCT.OBJ"
	-@erase "$(INTDIR)\D4XSKIP.OBJ"
	-@erase "$(INTDIR)\D4XTAG.OBJ"
	-@erase "$(INTDIR)\D4XTOP.OBJ"
	-@erase "$(INTDIR)\D4XWRITE.OBJ"
	-@erase "$(INTDIR)\D4ZAP.OBJ"
	-@erase "$(INTDIR)\Dbasedll.pch"
	-@erase "$(INTDIR)\DBASEDLL.res"
	-@erase "$(INTDIR)\DBASPROF.OBJ"
	-@erase "$(INTDIR)\DBFILTER.OBJ"
	-@erase "$(INTDIR)\DBLISTE.OBJ"
	-@erase "$(INTDIR)\DBTOOLS.OBJ"
	-@erase "$(INTDIR)\E4ERROR.OBJ"
	-@erase "$(INTDIR)\E4EXPR.OBJ"
	-@erase "$(INTDIR)\E4FUNCTI.OBJ"
	-@erase "$(INTDIR)\EXPREING.OBJ"
	-@erase "$(INTDIR)\F4FIELD.OBJ"
	-@erase "$(INTDIR)\F4FILE.OBJ"
	-@erase "$(INTDIR)\F4FILECR.OBJ"
	-@erase "$(INTDIR)\F4FILENM.OBJ"
	-@erase "$(INTDIR)\F4FILESE.OBJ"
	-@erase "$(INTDIR)\GB_API.OBJ"
	-@erase "$(INTDIR)\GB_INIT.OBJ"
	-@erase "$(INTDIR)\GB_PAINT.OBJ"
	-@erase "$(INTDIR)\GIZMO.OBJ"
	-@erase "$(INTDIR)\GIZMOBAR.OBJ"
	-@erase "$(INTDIR)\I4CHECK.OBJ"
	-@erase "$(INTDIR)\I4DUMP.OBJ"
	-@erase "$(INTDIR)\I4INDEX.OBJ"
	-@erase "$(INTDIR)\I4TAG.OBJ"
	-@erase "$(INTDIR)\L4LINK.OBJ"
	-@erase "$(INTDIR)\L4LINKAL.OBJ"
	-@erase "$(INTDIR)\L4LINKIT.OBJ"
	-@erase "$(INTDIR)\L4LINKSL.OBJ"
	-@erase "$(INTDIR)\L4LOCK_C.OBJ"
	-@erase "$(INTDIR)\LIBMAIN.OBJ"
	-@erase "$(INTDIR)\M4APPBL.OBJ"
	-@erase "$(INTDIR)\M4APPEND.OBJ"
	-@erase "$(INTDIR)\M4CHAIN.OBJ"
	-@erase "$(INTDIR)\M4CHECK.OBJ"
	-@erase "$(INTDIR)\M4COMPRS.OBJ"
	-@erase "$(INTDIR)\M4CREATE.OBJ"
	-@erase "$(INTDIR)\M4FIELD.OBJ"
	-@erase "$(INTDIR)\M4MEMO.OBJ"
	-@erase "$(INTDIR)\M4MEMORY.OBJ"
	-@erase "$(INTDIR)\M4PACK.OBJ"
	-@erase "$(INTDIR)\M4WRITE.OBJ"
	-@erase "$(INTDIR)\M4ZAP.OBJ"
	-@erase "$(INTDIR)\P4PARSE.OBJ"
	-@erase "$(INTDIR)\PHEADER.OBJ"
	-@erase "$(INTDIR)\R4REINDE.OBJ"
	-@erase "$(INTDIR)\RELATION.OBJ"
	-@erase "$(INTDIR)\S4ADD.OBJ"
	-@erase "$(INTDIR)\S4ENDPTR.OBJ"
	-@erase "$(INTDIR)\S4NULLEN.OBJ"
	-@erase "$(INTDIR)\S4QUICK.OBJ"
	-@erase "$(INTDIR)\S4REPLAC.OBJ"
	-@erase "$(INTDIR)\S4SEARCH.OBJ"
	-@erase "$(INTDIR)\S4SORT.OBJ"
	-@erase "$(INTDIR)\S4STR.OBJ"
	-@erase "$(INTDIR)\S4STRING.OBJ"
	-@erase "$(INTDIR)\S4STRLOW.OBJ"
	-@erase "$(INTDIR)\S4STRSET.OBJ"
	-@erase "$(INTDIR)\S4STRTRM.OBJ"
	-@erase "$(INTDIR)\S4SUBSTR.OBJ"
	-@erase "$(INTDIR)\S4UPPER.OBJ"
	-@erase "$(INTDIR)\U4UTIL.OBJ"
	-@erase "..\..\..\trias\trias\Dbasedll.dll"
	-@erase "..\..\lib.32\Dbasedll.exp"
	-@erase "..\..\lib.32\Dbasedll.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(OUTDIR)/DBASEDLL.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX" /Yc /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "__XT"\
 /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yc /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\winrel/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/DBASEDLL.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Dbasedll.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 tfrmwork.lib cont32r.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386 /stub:"d:\triasdev\dbasedll\mdx\rights.exe" /out:"d:\trias\trias\Dbasedll.dll" /implib:"d:/triasdev/lib.32/Dbasedll.lib"
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=tfrmwork.lib cont32r.lib kernel32.lib user32.lib gdi32.lib\
 winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib\
 uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll\
 /incremental:no /pdb:"$(OUTDIR)/Dbasedll.pdb" /machine:I386\
 /def:".\DBASEDLL.DEF" /stub:"d:\triasdev\dbasedll\mdx\rights.exe"\
 /out:"d:\trias\trias\Dbasedll.dll" /implib:"d:/triasdev/lib.32/Dbasedll.lib" 
DEF_FILE= \
	".\DBASEDLL.DEF"
LINK32_OBJS= \
	"$(INTDIR)\B4BLOCK.OBJ" \
	"$(INTDIR)\BTTNCUR.OBJ" \
	"$(INTDIR)\C4.OBJ" \
	"$(INTDIR)\C4BCD.OBJ" \
	"$(INTDIR)\C4CODE.OBJ" \
	"$(INTDIR)\C4CODEOP.OBJ" \
	"$(INTDIR)\CRCB.OBJ" \
	"$(INTDIR)\D4APPEND.OBJ" \
	"$(INTDIR)\D4CREATE.OBJ" \
	"$(INTDIR)\D4DATA.OBJ" \
	"$(INTDIR)\D4DATAFI.OBJ" \
	"$(INTDIR)\D4DATAIN.OBJ" \
	"$(INTDIR)\D4DATE.OBJ" \
	"$(INTDIR)\D4FIELD.OBJ" \
	"$(INTDIR)\D4GO.OBJ" \
	"$(INTDIR)\D4LOCK.OBJ" \
	"$(INTDIR)\D4PACK.OBJ" \
	"$(INTDIR)\D4RECCNT.OBJ" \
	"$(INTDIR)\D4SEEKDB.OBJ" \
	"$(INTDIR)\D4WRITE.OBJ" \
	"$(INTDIR)\D4XAPPBL.OBJ" \
	"$(INTDIR)\D4XAPPEN.OBJ" \
	"$(INTDIR)\D4XBOTTM.OBJ" \
	"$(INTDIR)\D4XFLUSH.OBJ" \
	"$(INTDIR)\D4XGO.OBJ" \
	"$(INTDIR)\D4XGOEOF.OBJ" \
	"$(INTDIR)\D4XLOCK.OBJ" \
	"$(INTDIR)\D4XPOS.OBJ" \
	"$(INTDIR)\D4XSEEK.OBJ" \
	"$(INTDIR)\D4XSELCT.OBJ" \
	"$(INTDIR)\D4XSKIP.OBJ" \
	"$(INTDIR)\D4XTAG.OBJ" \
	"$(INTDIR)\D4XTOP.OBJ" \
	"$(INTDIR)\D4XWRITE.OBJ" \
	"$(INTDIR)\D4ZAP.OBJ" \
	"$(INTDIR)\DBASEDLL.res" \
	"$(INTDIR)\DBASPROF.OBJ" \
	"$(INTDIR)\DBFILTER.OBJ" \
	"$(INTDIR)\DBLISTE.OBJ" \
	"$(INTDIR)\DBTOOLS.OBJ" \
	"$(INTDIR)\E4ERROR.OBJ" \
	"$(INTDIR)\E4EXPR.OBJ" \
	"$(INTDIR)\E4FUNCTI.OBJ" \
	"$(INTDIR)\EXPREING.OBJ" \
	"$(INTDIR)\F4FIELD.OBJ" \
	"$(INTDIR)\F4FILE.OBJ" \
	"$(INTDIR)\F4FILECR.OBJ" \
	"$(INTDIR)\F4FILENM.OBJ" \
	"$(INTDIR)\F4FILESE.OBJ" \
	"$(INTDIR)\GB_API.OBJ" \
	"$(INTDIR)\GB_INIT.OBJ" \
	"$(INTDIR)\GB_PAINT.OBJ" \
	"$(INTDIR)\GIZMO.OBJ" \
	"$(INTDIR)\GIZMOBAR.OBJ" \
	"$(INTDIR)\I4CHECK.OBJ" \
	"$(INTDIR)\I4DUMP.OBJ" \
	"$(INTDIR)\I4INDEX.OBJ" \
	"$(INTDIR)\I4TAG.OBJ" \
	"$(INTDIR)\L4LINK.OBJ" \
	"$(INTDIR)\L4LINKAL.OBJ" \
	"$(INTDIR)\L4LINKIT.OBJ" \
	"$(INTDIR)\L4LINKSL.OBJ" \
	"$(INTDIR)\L4LOCK_C.OBJ" \
	"$(INTDIR)\LIBMAIN.OBJ" \
	"$(INTDIR)\M4APPBL.OBJ" \
	"$(INTDIR)\M4APPEND.OBJ" \
	"$(INTDIR)\M4CHAIN.OBJ" \
	"$(INTDIR)\M4CHECK.OBJ" \
	"$(INTDIR)\M4COMPRS.OBJ" \
	"$(INTDIR)\M4CREATE.OBJ" \
	"$(INTDIR)\M4FIELD.OBJ" \
	"$(INTDIR)\M4MEMO.OBJ" \
	"$(INTDIR)\M4MEMORY.OBJ" \
	"$(INTDIR)\M4PACK.OBJ" \
	"$(INTDIR)\M4WRITE.OBJ" \
	"$(INTDIR)\M4ZAP.OBJ" \
	"$(INTDIR)\P4PARSE.OBJ" \
	"$(INTDIR)\PHEADER.OBJ" \
	"$(INTDIR)\R4REINDE.OBJ" \
	"$(INTDIR)\RELATION.OBJ" \
	"$(INTDIR)\S4ADD.OBJ" \
	"$(INTDIR)\S4ENDPTR.OBJ" \
	"$(INTDIR)\S4NULLEN.OBJ" \
	"$(INTDIR)\S4QUICK.OBJ" \
	"$(INTDIR)\S4REPLAC.OBJ" \
	"$(INTDIR)\S4SEARCH.OBJ" \
	"$(INTDIR)\S4SORT.OBJ" \
	"$(INTDIR)\S4STR.OBJ" \
	"$(INTDIR)\S4STRING.OBJ" \
	"$(INTDIR)\S4STRLOW.OBJ" \
	"$(INTDIR)\S4STRSET.OBJ" \
	"$(INTDIR)\S4STRTRM.OBJ" \
	"$(INTDIR)\S4SUBSTR.OBJ" \
	"$(INTDIR)\S4UPPER.OBJ" \
	"$(INTDIR)\U4UTIL.OBJ"

"..\..\..\trias\trias\Dbasedll.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "windebug"
# PROP Intermediate_Dir "windebug"
OUTDIR=.\windebug
INTDIR=.\windebug

ALL : "..\..\..\trias\trias200\dbase32d.dll"

CLEAN : 
	-@erase "$(INTDIR)\B4BLOCK.OBJ"
	-@erase "$(INTDIR)\BTTNCUR.OBJ"
	-@erase "$(INTDIR)\C4.OBJ"
	-@erase "$(INTDIR)\C4BCD.OBJ"
	-@erase "$(INTDIR)\C4CODE.OBJ"
	-@erase "$(INTDIR)\C4CODEOP.OBJ"
	-@erase "$(INTDIR)\CRCB.OBJ"
	-@erase "$(INTDIR)\D4APPEND.OBJ"
	-@erase "$(INTDIR)\D4CREATE.OBJ"
	-@erase "$(INTDIR)\D4DATA.OBJ"
	-@erase "$(INTDIR)\D4DATAFI.OBJ"
	-@erase "$(INTDIR)\D4DATAIN.OBJ"
	-@erase "$(INTDIR)\D4DATE.OBJ"
	-@erase "$(INTDIR)\D4FIELD.OBJ"
	-@erase "$(INTDIR)\D4GO.OBJ"
	-@erase "$(INTDIR)\D4LOCK.OBJ"
	-@erase "$(INTDIR)\D4PACK.OBJ"
	-@erase "$(INTDIR)\D4RECCNT.OBJ"
	-@erase "$(INTDIR)\D4SEEKDB.OBJ"
	-@erase "$(INTDIR)\D4WRITE.OBJ"
	-@erase "$(INTDIR)\D4XAPPBL.OBJ"
	-@erase "$(INTDIR)\D4XAPPEN.OBJ"
	-@erase "$(INTDIR)\D4XBOTTM.OBJ"
	-@erase "$(INTDIR)\D4XFLUSH.OBJ"
	-@erase "$(INTDIR)\D4XGO.OBJ"
	-@erase "$(INTDIR)\D4XGOEOF.OBJ"
	-@erase "$(INTDIR)\D4XLOCK.OBJ"
	-@erase "$(INTDIR)\D4XPOS.OBJ"
	-@erase "$(INTDIR)\D4XSEEK.OBJ"
	-@erase "$(INTDIR)\D4XSELCT.OBJ"
	-@erase "$(INTDIR)\D4XSKIP.OBJ"
	-@erase "$(INTDIR)\D4XTAG.OBJ"
	-@erase "$(INTDIR)\D4XTOP.OBJ"
	-@erase "$(INTDIR)\D4XWRITE.OBJ"
	-@erase "$(INTDIR)\D4ZAP.OBJ"
	-@erase "$(INTDIR)\Dbasedll.pch"
	-@erase "$(INTDIR)\DBASEDLL.res"
	-@erase "$(INTDIR)\DBASPROF.OBJ"
	-@erase "$(INTDIR)\DBFILTER.OBJ"
	-@erase "$(INTDIR)\DBLISTE.OBJ"
	-@erase "$(INTDIR)\DBTOOLS.OBJ"
	-@erase "$(INTDIR)\E4ERROR.OBJ"
	-@erase "$(INTDIR)\E4EXPR.OBJ"
	-@erase "$(INTDIR)\E4FUNCTI.OBJ"
	-@erase "$(INTDIR)\EXPREING.OBJ"
	-@erase "$(INTDIR)\F4FIELD.OBJ"
	-@erase "$(INTDIR)\F4FILE.OBJ"
	-@erase "$(INTDIR)\F4FILECR.OBJ"
	-@erase "$(INTDIR)\F4FILENM.OBJ"
	-@erase "$(INTDIR)\F4FILESE.OBJ"
	-@erase "$(INTDIR)\GB_API.OBJ"
	-@erase "$(INTDIR)\GB_INIT.OBJ"
	-@erase "$(INTDIR)\GB_PAINT.OBJ"
	-@erase "$(INTDIR)\GIZMO.OBJ"
	-@erase "$(INTDIR)\GIZMOBAR.OBJ"
	-@erase "$(INTDIR)\I4CHECK.OBJ"
	-@erase "$(INTDIR)\I4DUMP.OBJ"
	-@erase "$(INTDIR)\I4INDEX.OBJ"
	-@erase "$(INTDIR)\I4TAG.OBJ"
	-@erase "$(INTDIR)\L4LINK.OBJ"
	-@erase "$(INTDIR)\L4LINKAL.OBJ"
	-@erase "$(INTDIR)\L4LINKIT.OBJ"
	-@erase "$(INTDIR)\L4LINKSL.OBJ"
	-@erase "$(INTDIR)\L4LOCK_C.OBJ"
	-@erase "$(INTDIR)\LIBMAIN.OBJ"
	-@erase "$(INTDIR)\M4APPBL.OBJ"
	-@erase "$(INTDIR)\M4APPEND.OBJ"
	-@erase "$(INTDIR)\M4CHAIN.OBJ"
	-@erase "$(INTDIR)\M4CHECK.OBJ"
	-@erase "$(INTDIR)\M4COMPRS.OBJ"
	-@erase "$(INTDIR)\M4CREATE.OBJ"
	-@erase "$(INTDIR)\M4FIELD.OBJ"
	-@erase "$(INTDIR)\M4MEMO.OBJ"
	-@erase "$(INTDIR)\M4MEMORY.OBJ"
	-@erase "$(INTDIR)\M4PACK.OBJ"
	-@erase "$(INTDIR)\M4WRITE.OBJ"
	-@erase "$(INTDIR)\M4ZAP.OBJ"
	-@erase "$(INTDIR)\P4PARSE.OBJ"
	-@erase "$(INTDIR)\PHEADER.OBJ"
	-@erase "$(INTDIR)\R4REINDE.OBJ"
	-@erase "$(INTDIR)\RELATION.OBJ"
	-@erase "$(INTDIR)\S4ADD.OBJ"
	-@erase "$(INTDIR)\S4ENDPTR.OBJ"
	-@erase "$(INTDIR)\S4NULLEN.OBJ"
	-@erase "$(INTDIR)\S4QUICK.OBJ"
	-@erase "$(INTDIR)\S4REPLAC.OBJ"
	-@erase "$(INTDIR)\S4SEARCH.OBJ"
	-@erase "$(INTDIR)\S4SORT.OBJ"
	-@erase "$(INTDIR)\S4STR.OBJ"
	-@erase "$(INTDIR)\S4STRING.OBJ"
	-@erase "$(INTDIR)\S4STRLOW.OBJ"
	-@erase "$(INTDIR)\S4STRSET.OBJ"
	-@erase "$(INTDIR)\S4STRTRM.OBJ"
	-@erase "$(INTDIR)\S4SUBSTR.OBJ"
	-@erase "$(INTDIR)\S4UPPER.OBJ"
	-@erase "$(INTDIR)\U4UTIL.OBJ"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\dbase32d.pdb"
	-@erase "..\..\..\trias\trias200\dbase32d.dll"
	-@erase "..\..\lib.32\dbase32d.exp"
	-@erase "..\..\lib.32\dbase32d.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX" /Yu"d4all.h" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\windebug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/DBASEDLL.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Dbasedll.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 tfrm32d.lib cont32d.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib /nologo /dll /incremental:no /debug /machine:I386 /stub:"d:\triasdev\dbasedll\mdx\rights.exe" /out:"d:\trias\trias200\dbase32d.dll" /implib:"d:\triasdev\lib.32\dbase32d.lib" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=tfrm32d.lib cont32d.lib kernel32.lib user32.lib gdi32.lib\
 winspool.lib comdlg32.lib advapi32.lib shell32.lib /nologo /dll /incremental:no\
 /pdb:"$(OUTDIR)/dbase32d.pdb" /debug /machine:I386 /def:".\DBASEDLL.DEF"\
 /stub:"d:\triasdev\dbasedll\mdx\rights.exe"\
 /out:"d:\trias\trias200\dbase32d.dll" /implib:"d:\triasdev\lib.32\dbase32d.lib"\
 /SUBSYSTEM:windows,4.0 
DEF_FILE= \
	".\DBASEDLL.DEF"
LINK32_OBJS= \
	"$(INTDIR)\B4BLOCK.OBJ" \
	"$(INTDIR)\BTTNCUR.OBJ" \
	"$(INTDIR)\C4.OBJ" \
	"$(INTDIR)\C4BCD.OBJ" \
	"$(INTDIR)\C4CODE.OBJ" \
	"$(INTDIR)\C4CODEOP.OBJ" \
	"$(INTDIR)\CRCB.OBJ" \
	"$(INTDIR)\D4APPEND.OBJ" \
	"$(INTDIR)\D4CREATE.OBJ" \
	"$(INTDIR)\D4DATA.OBJ" \
	"$(INTDIR)\D4DATAFI.OBJ" \
	"$(INTDIR)\D4DATAIN.OBJ" \
	"$(INTDIR)\D4DATE.OBJ" \
	"$(INTDIR)\D4FIELD.OBJ" \
	"$(INTDIR)\D4GO.OBJ" \
	"$(INTDIR)\D4LOCK.OBJ" \
	"$(INTDIR)\D4PACK.OBJ" \
	"$(INTDIR)\D4RECCNT.OBJ" \
	"$(INTDIR)\D4SEEKDB.OBJ" \
	"$(INTDIR)\D4WRITE.OBJ" \
	"$(INTDIR)\D4XAPPBL.OBJ" \
	"$(INTDIR)\D4XAPPEN.OBJ" \
	"$(INTDIR)\D4XBOTTM.OBJ" \
	"$(INTDIR)\D4XFLUSH.OBJ" \
	"$(INTDIR)\D4XGO.OBJ" \
	"$(INTDIR)\D4XGOEOF.OBJ" \
	"$(INTDIR)\D4XLOCK.OBJ" \
	"$(INTDIR)\D4XPOS.OBJ" \
	"$(INTDIR)\D4XSEEK.OBJ" \
	"$(INTDIR)\D4XSELCT.OBJ" \
	"$(INTDIR)\D4XSKIP.OBJ" \
	"$(INTDIR)\D4XTAG.OBJ" \
	"$(INTDIR)\D4XTOP.OBJ" \
	"$(INTDIR)\D4XWRITE.OBJ" \
	"$(INTDIR)\D4ZAP.OBJ" \
	"$(INTDIR)\DBASEDLL.res" \
	"$(INTDIR)\DBASPROF.OBJ" \
	"$(INTDIR)\DBFILTER.OBJ" \
	"$(INTDIR)\DBLISTE.OBJ" \
	"$(INTDIR)\DBTOOLS.OBJ" \
	"$(INTDIR)\E4ERROR.OBJ" \
	"$(INTDIR)\E4EXPR.OBJ" \
	"$(INTDIR)\E4FUNCTI.OBJ" \
	"$(INTDIR)\EXPREING.OBJ" \
	"$(INTDIR)\F4FIELD.OBJ" \
	"$(INTDIR)\F4FILE.OBJ" \
	"$(INTDIR)\F4FILECR.OBJ" \
	"$(INTDIR)\F4FILENM.OBJ" \
	"$(INTDIR)\F4FILESE.OBJ" \
	"$(INTDIR)\GB_API.OBJ" \
	"$(INTDIR)\GB_INIT.OBJ" \
	"$(INTDIR)\GB_PAINT.OBJ" \
	"$(INTDIR)\GIZMO.OBJ" \
	"$(INTDIR)\GIZMOBAR.OBJ" \
	"$(INTDIR)\I4CHECK.OBJ" \
	"$(INTDIR)\I4DUMP.OBJ" \
	"$(INTDIR)\I4INDEX.OBJ" \
	"$(INTDIR)\I4TAG.OBJ" \
	"$(INTDIR)\L4LINK.OBJ" \
	"$(INTDIR)\L4LINKAL.OBJ" \
	"$(INTDIR)\L4LINKIT.OBJ" \
	"$(INTDIR)\L4LINKSL.OBJ" \
	"$(INTDIR)\L4LOCK_C.OBJ" \
	"$(INTDIR)\LIBMAIN.OBJ" \
	"$(INTDIR)\M4APPBL.OBJ" \
	"$(INTDIR)\M4APPEND.OBJ" \
	"$(INTDIR)\M4CHAIN.OBJ" \
	"$(INTDIR)\M4CHECK.OBJ" \
	"$(INTDIR)\M4COMPRS.OBJ" \
	"$(INTDIR)\M4CREATE.OBJ" \
	"$(INTDIR)\M4FIELD.OBJ" \
	"$(INTDIR)\M4MEMO.OBJ" \
	"$(INTDIR)\M4MEMORY.OBJ" \
	"$(INTDIR)\M4PACK.OBJ" \
	"$(INTDIR)\M4WRITE.OBJ" \
	"$(INTDIR)\M4ZAP.OBJ" \
	"$(INTDIR)\P4PARSE.OBJ" \
	"$(INTDIR)\PHEADER.OBJ" \
	"$(INTDIR)\R4REINDE.OBJ" \
	"$(INTDIR)\RELATION.OBJ" \
	"$(INTDIR)\S4ADD.OBJ" \
	"$(INTDIR)\S4ENDPTR.OBJ" \
	"$(INTDIR)\S4NULLEN.OBJ" \
	"$(INTDIR)\S4QUICK.OBJ" \
	"$(INTDIR)\S4REPLAC.OBJ" \
	"$(INTDIR)\S4SEARCH.OBJ" \
	"$(INTDIR)\S4SORT.OBJ" \
	"$(INTDIR)\S4STR.OBJ" \
	"$(INTDIR)\S4STRING.OBJ" \
	"$(INTDIR)\S4STRLOW.OBJ" \
	"$(INTDIR)\S4STRSET.OBJ" \
	"$(INTDIR)\S4STRTRM.OBJ" \
	"$(INTDIR)\S4SUBSTR.OBJ" \
	"$(INTDIR)\S4UPPER.OBJ" \
	"$(INTDIR)\U4UTIL.OBJ"

"..\..\..\trias\trias200\dbase32d.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Dbasedll - Win32 Release"
# Name "Dbasedll - Win32 Debug"

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\DBLISTE.CXX

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

DEP_CPP_DBLIS=\
	"..\..\INC_GLB.32\gc.h"\
	"..\..\inc_glb.32\syncthrd.hxx"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\Dbliste.hxx"\
	{$(INCLUDE)}"\Dbtools.hxx"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\Objfeld.hxx"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\U4util.h"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	
# ADD CPP /Yu"d4all.h"

"$(INTDIR)\DBLISTE.OBJ" : $(SOURCE) $(DEP_CPP_DBLIS) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"

DEP_CPP_DBLIS=\
	"..\..\INC_GLB.32\gc.h"\
	"..\..\inc_glb.32\syncthrd.hxx"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\Dbliste.hxx"\
	{$(INCLUDE)}"\Dbtools.hxx"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\Objfeld.hxx"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\U4util.h"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	

"$(INTDIR)\DBLISTE.OBJ" : $(SOURCE) $(DEP_CPP_DBLIS) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\D4XAPPEN.CXX
DEP_CPP_D4XAP=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\D4XAPPEN.OBJ" : $(SOURCE) $(DEP_CPP_D4XAP) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\D4XAPPEN.OBJ" : $(SOURCE) $(DEP_CPP_D4XAP) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\D4SEEKDB.CXX
DEP_CPP_D4SEE=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\D4SEEKDB.OBJ" : $(SOURCE) $(DEP_CPP_D4SEE) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\D4SEEKDB.OBJ" : $(SOURCE) $(DEP_CPP_D4SEE) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\C4CODEOP.CXX
DEP_CPP_C4COD=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\C4CODEOP.OBJ" : $(SOURCE) $(DEP_CPP_C4COD) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\C4CODEOP.OBJ" : $(SOURCE) $(DEP_CPP_C4COD) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\U4UTIL.CXX
DEP_CPP_U4UTI=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\U4UTIL.OBJ" : $(SOURCE) $(DEP_CPP_U4UTI) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\U4UTIL.OBJ" : $(SOURCE) $(DEP_CPP_U4UTI) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\S4SORT.CXX
DEP_CPP_S4SOR=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\S4SORT.OBJ" : $(SOURCE) $(DEP_CPP_S4SOR) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\S4SORT.OBJ" : $(SOURCE) $(DEP_CPP_S4SOR) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\F4FILECR.CXX
DEP_CPP_F4FIL=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\F4FILECR.OBJ" : $(SOURCE) $(DEP_CPP_F4FIL) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\F4FILECR.OBJ" : $(SOURCE) $(DEP_CPP_F4FIL) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\I4DUMP.CXX
DEP_CPP_I4DUM=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\I4DUMP.OBJ" : $(SOURCE) $(DEP_CPP_I4DUM) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\I4DUMP.OBJ" : $(SOURCE) $(DEP_CPP_I4DUM) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\D4XSELCT.CXX
DEP_CPP_D4XSE=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\D4XSELCT.OBJ" : $(SOURCE) $(DEP_CPP_D4XSE) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\D4XSELCT.OBJ" : $(SOURCE) $(DEP_CPP_D4XSE) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\D4XAPPBL.CXX
DEP_CPP_D4XAPP=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\D4XAPPBL.OBJ" : $(SOURCE) $(DEP_CPP_D4XAPP) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\D4XAPPBL.OBJ" : $(SOURCE) $(DEP_CPP_D4XAPP) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PHEADER.CXX
DEP_CPP_PHEAD=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yc"d4all.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "__XT"\
 /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yc"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\PHEADER.OBJ" : $(SOURCE) $(DEP_CPP_PHEAD) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Dbasedll.pch" : $(SOURCE) $(DEP_CPP_PHEAD) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"

# ADD CPP /Yc"d4all.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yc"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\PHEADER.OBJ" : $(SOURCE) $(DEP_CPP_PHEAD) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Dbasedll.pch" : $(SOURCE) $(DEP_CPP_PHEAD) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\D4PACK.CXX
DEP_CPP_D4PAC=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\D4PACK.OBJ" : $(SOURCE) $(DEP_CPP_D4PAC) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\D4PACK.OBJ" : $(SOURCE) $(DEP_CPP_D4PAC) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\C4.CXX
DEP_CPP_C4_CX=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\C4.OBJ" : $(SOURCE) $(DEP_CPP_C4_CX) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\C4.OBJ" : $(SOURCE) $(DEP_CPP_C4_CX) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\M4CHECK.CXX
DEP_CPP_M4CHE=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\M4CHECK.OBJ" : $(SOURCE) $(DEP_CPP_M4CHE) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\M4CHECK.OBJ" : $(SOURCE) $(DEP_CPP_M4CHE) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\D4XTOP.CXX
DEP_CPP_D4XTO=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\D4XTOP.OBJ" : $(SOURCE) $(DEP_CPP_D4XTO) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\D4XTOP.OBJ" : $(SOURCE) $(DEP_CPP_D4XTO) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\S4STRLOW.CXX
DEP_CPP_S4STR=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\S4STRLOW.OBJ" : $(SOURCE) $(DEP_CPP_S4STR) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\S4STRLOW.OBJ" : $(SOURCE) $(DEP_CPP_S4STR) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\D4DATE.CXX
DEP_CPP_D4DAT=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\D4DATE.OBJ" : $(SOURCE) $(DEP_CPP_D4DAT) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\D4DATE.OBJ" : $(SOURCE) $(DEP_CPP_D4DAT) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\D4DATAIN.CXX
DEP_CPP_D4DATA=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\D4DATAIN.OBJ" : $(SOURCE) $(DEP_CPP_D4DATA) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\D4DATAIN.OBJ" : $(SOURCE) $(DEP_CPP_D4DATA) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\D4DATA.CXX
DEP_CPP_D4DATA_=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\D4DATA.OBJ" : $(SOURCE) $(DEP_CPP_D4DATA_) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\D4DATA.OBJ" : $(SOURCE) $(DEP_CPP_D4DATA_) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\L4LINKSL.CXX
DEP_CPP_L4LIN=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\L4LINKSL.OBJ" : $(SOURCE) $(DEP_CPP_L4LIN) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\L4LINKSL.OBJ" : $(SOURCE) $(DEP_CPP_L4LIN) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\D4DATAFI.CXX
DEP_CPP_D4DATAF=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\D4DATAFI.OBJ" : $(SOURCE) $(DEP_CPP_D4DATAF) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\D4DATAFI.OBJ" : $(SOURCE) $(DEP_CPP_D4DATAF) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\M4CREATE.CXX
DEP_CPP_M4CRE=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\M4CREATE.OBJ" : $(SOURCE) $(DEP_CPP_M4CRE) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\M4CREATE.OBJ" : $(SOURCE) $(DEP_CPP_M4CRE) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\D4XFLUSH.CXX
DEP_CPP_D4XFL=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\D4XFLUSH.OBJ" : $(SOURCE) $(DEP_CPP_D4XFL) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\D4XFLUSH.OBJ" : $(SOURCE) $(DEP_CPP_D4XFL) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\S4REPLAC.CXX
DEP_CPP_S4REP=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\S4REPLAC.OBJ" : $(SOURCE) $(DEP_CPP_S4REP) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\S4REPLAC.OBJ" : $(SOURCE) $(DEP_CPP_S4REP) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\B4BLOCK.CXX
DEP_CPP_B4BLO=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\B4BLOCK.OBJ" : $(SOURCE) $(DEP_CPP_B4BLO) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\B4BLOCK.OBJ" : $(SOURCE) $(DEP_CPP_B4BLO) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\S4STRSET.CXX
DEP_CPP_S4STRS=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\S4STRSET.OBJ" : $(SOURCE) $(DEP_CPP_S4STRS) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\S4STRSET.OBJ" : $(SOURCE) $(DEP_CPP_S4STRS) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\R4REINDE.CXX
DEP_CPP_R4REI=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\R4REINDE.OBJ" : $(SOURCE) $(DEP_CPP_R4REI) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\R4REINDE.OBJ" : $(SOURCE) $(DEP_CPP_R4REI) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\L4LOCK_C.CXX
DEP_CPP_L4LOC=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\L4LOCK_C.OBJ" : $(SOURCE) $(DEP_CPP_L4LOC) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\L4LOCK_C.OBJ" : $(SOURCE) $(DEP_CPP_L4LOC) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DBFILTER.CXX

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

DEP_CPP_DBFIL=\
	"..\..\INC_GLB.32\gc.h"\
	"..\..\inc_glb.32\syncthrd.hxx"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\Dbliste.hxx"\
	{$(INCLUDE)}"\Dbtools.hxx"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\Objfeld.hxx"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\Relation.hxx"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\U4util.h"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	
# ADD CPP /Yu"d4all.h"

"$(INTDIR)\DBFILTER.OBJ" : $(SOURCE) $(DEP_CPP_DBFIL) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"

DEP_CPP_DBFIL=\
	"..\..\INC_GLB.32\gc.h"\
	"..\..\inc_glb.32\syncthrd.hxx"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\Dbliste.hxx"\
	{$(INCLUDE)}"\Dbtools.hxx"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\Objfeld.hxx"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\Relation.hxx"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\U4util.h"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	

"$(INTDIR)\DBFILTER.OBJ" : $(SOURCE) $(DEP_CPP_DBFIL) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\D4XSKIP.CXX
DEP_CPP_D4XSK=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\D4XSKIP.OBJ" : $(SOURCE) $(DEP_CPP_D4XSK) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\D4XSKIP.OBJ" : $(SOURCE) $(DEP_CPP_D4XSK) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\M4CHAIN.CXX
DEP_CPP_M4CHA=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\M4CHAIN.OBJ" : $(SOURCE) $(DEP_CPP_M4CHA) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\M4CHAIN.OBJ" : $(SOURCE) $(DEP_CPP_M4CHA) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\F4FILENM.CXX
DEP_CPP_F4FILE=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\F4FILENM.OBJ" : $(SOURCE) $(DEP_CPP_F4FILE) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\F4FILENM.OBJ" : $(SOURCE) $(DEP_CPP_F4FILE) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CRCB.CXX

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

DEP_CPP_CRCB_=\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\Crcb.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\Dbtools.hxx"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\U4util.h"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	
# ADD CPP /Yu"d4all.h"

"$(INTDIR)\CRCB.OBJ" : $(SOURCE) $(DEP_CPP_CRCB_) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"

DEP_CPP_CRCB_=\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\Crcb.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\Dbtools.hxx"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\U4util.h"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	

"$(INTDIR)\CRCB.OBJ" : $(SOURCE) $(DEP_CPP_CRCB_) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\D4XPOS.CXX
DEP_CPP_D4XPO=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\D4XPOS.OBJ" : $(SOURCE) $(DEP_CPP_D4XPO) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\D4XPOS.OBJ" : $(SOURCE) $(DEP_CPP_D4XPO) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\S4ENDPTR.CXX
DEP_CPP_S4END=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\S4ENDPTR.OBJ" : $(SOURCE) $(DEP_CPP_S4END) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\S4ENDPTR.OBJ" : $(SOURCE) $(DEP_CPP_S4END) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\S4ADD.CXX
DEP_CPP_S4ADD=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\S4ADD.OBJ" : $(SOURCE) $(DEP_CPP_S4ADD) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\S4ADD.OBJ" : $(SOURCE) $(DEP_CPP_S4ADD) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\M4WRITE.CXX
DEP_CPP_M4WRI=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\M4WRITE.OBJ" : $(SOURCE) $(DEP_CPP_M4WRI) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\M4WRITE.OBJ" : $(SOURCE) $(DEP_CPP_M4WRI) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\E4ERROR.CXX

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

DEP_CPP_E4ERR=\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	
# ADD CPP /Yu"d4all.h"

"$(INTDIR)\E4ERROR.OBJ" : $(SOURCE) $(DEP_CPP_E4ERR) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"

DEP_CPP_E4ERR=\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	

"$(INTDIR)\E4ERROR.OBJ" : $(SOURCE) $(DEP_CPP_E4ERR) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\M4FIELD.CXX
DEP_CPP_M4FIE=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\M4FIELD.OBJ" : $(SOURCE) $(DEP_CPP_M4FIE) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\M4FIELD.OBJ" : $(SOURCE) $(DEP_CPP_M4FIE) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\D4XLOCK.CXX
DEP_CPP_D4XLO=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\D4XLOCK.OBJ" : $(SOURCE) $(DEP_CPP_D4XLO) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\D4XLOCK.OBJ" : $(SOURCE) $(DEP_CPP_D4XLO) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\D4XBOTTM.CXX
DEP_CPP_D4XBO=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\D4XBOTTM.OBJ" : $(SOURCE) $(DEP_CPP_D4XBO) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\D4XBOTTM.OBJ" : $(SOURCE) $(DEP_CPP_D4XBO) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\RELATION.CXX

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

DEP_CPP_RELAT=\
	"..\..\INC_GLB.32\gc.h"\
	"..\..\inc_glb.32\syncthrd.hxx"\
	".\Relation.htp"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\Dbasekey.hxx"\
	{$(INCLUDE)}"\Dbliste.hxx"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\Objfeld.hxx"\
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\Relation.hxx"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\U4util.h"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	
# ADD CPP /Yu"d4all.h"

"$(INTDIR)\RELATION.OBJ" : $(SOURCE) $(DEP_CPP_RELAT) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"

DEP_CPP_RELAT=\
	"..\..\INC_GLB.32\gc.h"\
	"..\..\inc_glb.32\syncthrd.hxx"\
	".\Relation.htp"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\Dbasekey.hxx"\
	{$(INCLUDE)}"\Dbliste.hxx"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\Objfeld.hxx"\
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\Relation.hxx"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\U4util.h"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	

"$(INTDIR)\RELATION.OBJ" : $(SOURCE) $(DEP_CPP_RELAT) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\M4APPBL.CXX
DEP_CPP_M4APP=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\M4APPBL.OBJ" : $(SOURCE) $(DEP_CPP_M4APP) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\M4APPBL.OBJ" : $(SOURCE) $(DEP_CPP_M4APP) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\I4CHECK.CXX
DEP_CPP_I4CHE=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\I4CHECK.OBJ" : $(SOURCE) $(DEP_CPP_I4CHE) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\I4CHECK.OBJ" : $(SOURCE) $(DEP_CPP_I4CHE) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\M4COMPRS.CXX
DEP_CPP_M4COM=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\M4COMPRS.OBJ" : $(SOURCE) $(DEP_CPP_M4COM) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\M4COMPRS.OBJ" : $(SOURCE) $(DEP_CPP_M4COM) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\I4TAG.CXX
DEP_CPP_I4TAG=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\I4TAG.OBJ" : $(SOURCE) $(DEP_CPP_I4TAG) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\I4TAG.OBJ" : $(SOURCE) $(DEP_CPP_I4TAG) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\S4NULLEN.CXX
DEP_CPP_S4NUL=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\S4NULLEN.OBJ" : $(SOURCE) $(DEP_CPP_S4NUL) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\S4NULLEN.OBJ" : $(SOURCE) $(DEP_CPP_S4NUL) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\S4UPPER.CXX
DEP_CPP_S4UPP=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\S4UPPER.OBJ" : $(SOURCE) $(DEP_CPP_S4UPP) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\S4UPPER.OBJ" : $(SOURCE) $(DEP_CPP_S4UPP) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\M4PACK.CXX
DEP_CPP_M4PAC=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\M4PACK.OBJ" : $(SOURCE) $(DEP_CPP_M4PAC) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\M4PACK.OBJ" : $(SOURCE) $(DEP_CPP_M4PAC) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DBASEDLL.RC
DEP_RSC_DBASE=\
	".\DBASEDLL.RCV"\
	

"$(INTDIR)\DBASEDLL.res" : $(SOURCE) $(DEP_RSC_DBASE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\S4STR.CXX
DEP_CPP_S4STR_=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\S4STR.OBJ" : $(SOURCE) $(DEP_CPP_S4STR_) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\S4STR.OBJ" : $(SOURCE) $(DEP_CPP_S4STR_) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\L4LINKIT.CXX
DEP_CPP_L4LINK=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\L4LINKIT.OBJ" : $(SOURCE) $(DEP_CPP_L4LINK) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\L4LINKIT.OBJ" : $(SOURCE) $(DEP_CPP_L4LINK) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\D4WRITE.CXX
DEP_CPP_D4WRI=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\D4WRITE.OBJ" : $(SOURCE) $(DEP_CPP_D4WRI) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\D4WRITE.OBJ" : $(SOURCE) $(DEP_CPP_D4WRI) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\D4FIELD.CXX
DEP_CPP_D4FIE=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\D4FIELD.OBJ" : $(SOURCE) $(DEP_CPP_D4FIE) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\D4FIELD.OBJ" : $(SOURCE) $(DEP_CPP_D4FIE) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\D4APPEND.CXX
DEP_CPP_D4APP=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\D4APPEND.OBJ" : $(SOURCE) $(DEP_CPP_D4APP) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\D4APPEND.OBJ" : $(SOURCE) $(DEP_CPP_D4APP) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\E4FUNCTI.CXX
DEP_CPP_E4FUN=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\E4FUNCTI.OBJ" : $(SOURCE) $(DEP_CPP_E4FUN) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\E4FUNCTI.OBJ" : $(SOURCE) $(DEP_CPP_E4FUN) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\M4ZAP.CXX
DEP_CPP_M4ZAP=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\M4ZAP.OBJ" : $(SOURCE) $(DEP_CPP_M4ZAP) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\M4ZAP.OBJ" : $(SOURCE) $(DEP_CPP_M4ZAP) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\F4FILE.CXX
DEP_CPP_F4FILE_=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\F4FILE.OBJ" : $(SOURCE) $(DEP_CPP_F4FILE_) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\F4FILE.OBJ" : $(SOURCE) $(DEP_CPP_F4FILE_) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\C4BCD.CXX
DEP_CPP_C4BCD=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\C4BCD.OBJ" : $(SOURCE) $(DEP_CPP_C4BCD) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\C4BCD.OBJ" : $(SOURCE) $(DEP_CPP_C4BCD) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\S4STRTRM.CXX
DEP_CPP_S4STRT=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\S4STRTRM.OBJ" : $(SOURCE) $(DEP_CPP_S4STRT) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\S4STRTRM.OBJ" : $(SOURCE) $(DEP_CPP_S4STRT) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\S4STRING.CXX
DEP_CPP_S4STRI=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\S4STRING.OBJ" : $(SOURCE) $(DEP_CPP_S4STRI) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\S4STRING.OBJ" : $(SOURCE) $(DEP_CPP_S4STRI) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DBASEDLL.DEF

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\L4LINKAL.CXX
DEP_CPP_L4LINKA=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\L4LINKAL.OBJ" : $(SOURCE) $(DEP_CPP_L4LINKA) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\L4LINKAL.OBJ" : $(SOURCE) $(DEP_CPP_L4LINKA) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\D4XGO.CXX
DEP_CPP_D4XGO=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\D4XGO.OBJ" : $(SOURCE) $(DEP_CPP_D4XGO) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\D4XGO.OBJ" : $(SOURCE) $(DEP_CPP_D4XGO) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\I4INDEX.CXX
DEP_CPP_I4IND=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\I4INDEX.OBJ" : $(SOURCE) $(DEP_CPP_I4IND) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\I4INDEX.OBJ" : $(SOURCE) $(DEP_CPP_I4IND) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\D4CREATE.CXX
DEP_CPP_D4CRE=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\D4CREATE.OBJ" : $(SOURCE) $(DEP_CPP_D4CRE) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\D4CREATE.OBJ" : $(SOURCE) $(DEP_CPP_D4CRE) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\S4SEARCH.CXX
DEP_CPP_S4SEA=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\S4SEARCH.OBJ" : $(SOURCE) $(DEP_CPP_S4SEA) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\S4SEARCH.OBJ" : $(SOURCE) $(DEP_CPP_S4SEA) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\M4MEMO.CXX
DEP_CPP_M4MEM=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\M4MEMO.OBJ" : $(SOURCE) $(DEP_CPP_M4MEM) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\M4MEMO.OBJ" : $(SOURCE) $(DEP_CPP_M4MEM) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\F4FILESE.CXX
DEP_CPP_F4FILES=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\F4FILESE.OBJ" : $(SOURCE) $(DEP_CPP_F4FILES) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\F4FILESE.OBJ" : $(SOURCE) $(DEP_CPP_F4FILES) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\S4QUICK.CXX
DEP_CPP_S4QUI=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\S4QUICK.OBJ" : $(SOURCE) $(DEP_CPP_S4QUI) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\S4QUICK.OBJ" : $(SOURCE) $(DEP_CPP_S4QUI) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\M4APPEND.CXX
DEP_CPP_M4APPE=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\M4APPEND.OBJ" : $(SOURCE) $(DEP_CPP_M4APPE) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\M4APPEND.OBJ" : $(SOURCE) $(DEP_CPP_M4APPE) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\D4XGOEOF.CXX
DEP_CPP_D4XGOE=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\D4XGOEOF.OBJ" : $(SOURCE) $(DEP_CPP_D4XGOE) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\D4XGOEOF.OBJ" : $(SOURCE) $(DEP_CPP_D4XGOE) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\C4CODE.CXX
DEP_CPP_C4CODE=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\C4CODE.OBJ" : $(SOURCE) $(DEP_CPP_C4CODE) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\C4CODE.OBJ" : $(SOURCE) $(DEP_CPP_C4CODE) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\E4EXPR.CXX
DEP_CPP_E4EXP=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\E4EXPR.OBJ" : $(SOURCE) $(DEP_CPP_E4EXP) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\E4EXPR.OBJ" : $(SOURCE) $(DEP_CPP_E4EXP) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\D4XSEEK.CXX
DEP_CPP_D4XSEE=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\D4XSEEK.OBJ" : $(SOURCE) $(DEP_CPP_D4XSEE) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\D4XSEEK.OBJ" : $(SOURCE) $(DEP_CPP_D4XSEE) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\D4GO.CXX
DEP_CPP_D4GO_=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\D4GO.OBJ" : $(SOURCE) $(DEP_CPP_D4GO_) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\D4GO.OBJ" : $(SOURCE) $(DEP_CPP_D4GO_) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\D4LOCK.CXX
DEP_CPP_D4LOC=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\D4LOCK.OBJ" : $(SOURCE) $(DEP_CPP_D4LOC) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\D4LOCK.OBJ" : $(SOURCE) $(DEP_CPP_D4LOC) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\D4RECCNT.CXX
DEP_CPP_D4REC=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\D4RECCNT.OBJ" : $(SOURCE) $(DEP_CPP_D4REC) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\D4RECCNT.OBJ" : $(SOURCE) $(DEP_CPP_D4REC) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\F4FIELD.CXX
DEP_CPP_F4FIE=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\F4FIELD.OBJ" : $(SOURCE) $(DEP_CPP_F4FIE) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\F4FIELD.OBJ" : $(SOURCE) $(DEP_CPP_F4FIE) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\P4PARSE.CXX
DEP_CPP_P4PAR=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\P4PARSE.OBJ" : $(SOURCE) $(DEP_CPP_P4PAR) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\P4PARSE.OBJ" : $(SOURCE) $(DEP_CPP_P4PAR) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\M4MEMORY.CXX
DEP_CPP_M4MEMO=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\M4MEMORY.OBJ" : $(SOURCE) $(DEP_CPP_M4MEMO) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\M4MEMORY.OBJ" : $(SOURCE) $(DEP_CPP_M4MEMO) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\D4ZAP.CXX
DEP_CPP_D4ZAP=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\D4ZAP.OBJ" : $(SOURCE) $(DEP_CPP_D4ZAP) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\D4ZAP.OBJ" : $(SOURCE) $(DEP_CPP_D4ZAP) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\S4SUBSTR.CXX
DEP_CPP_S4SUB=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\S4SUBSTR.OBJ" : $(SOURCE) $(DEP_CPP_S4SUB) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\S4SUBSTR.OBJ" : $(SOURCE) $(DEP_CPP_S4SUB) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\LIBMAIN.CXX
DEP_CPP_LIBMA=\
	".\Bttncuri.h"\
	".\Gizmo.h"\
	".\Gizmoint.h"\
	".\Version.h"\
	".\Win1632.h"\
	{$(INCLUDE)}"\Bttncur.h"\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\Gizmobar.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\LIBMAIN.OBJ" : $(SOURCE) $(DEP_CPP_LIBMA) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\LIBMAIN.OBJ" : $(SOURCE) $(DEP_CPP_LIBMA) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\D4XTAG.CXX
DEP_CPP_D4XTA=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\D4XTAG.OBJ" : $(SOURCE) $(DEP_CPP_D4XTA) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\D4XTAG.OBJ" : $(SOURCE) $(DEP_CPP_D4XTA) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\L4LINK.CXX
DEP_CPP_L4LINK_=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\L4LINK.OBJ" : $(SOURCE) $(DEP_CPP_L4LINK_) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\L4LINK.OBJ" : $(SOURCE) $(DEP_CPP_L4LINK_) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\D4XWRITE.CXX
DEP_CPP_D4XWR=\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\D4XWRITE.OBJ" : $(SOURCE) $(DEP_CPP_D4XWR) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\D4XWRITE.OBJ" : $(SOURCE) $(DEP_CPP_D4XWR) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\EXPREING.CXX

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

DEP_CPP_EXPRE=\
	"..\..\INC_GLB.32\gc.h"\
	"..\..\inc_glb.32\syncthrd.hxx"\
	".\Dbasedll.hr"\
	".\Expreing.htp"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\Dbliste.hxx"\
	{$(INCLUDE)}"\Dbtools.hxx"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Errinstx.hxx"\
	{$(INCLUDE)}"\Expreing.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\U4util.h"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	
NODEP_CPP_EXPRE=\
	".\win16\dbasedll.h"\
	
# ADD CPP /Yu"d4all.h"

"$(INTDIR)\EXPREING.OBJ" : $(SOURCE) $(DEP_CPP_EXPRE) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"

DEP_CPP_EXPRE=\
	"..\..\INC_GLB.32\gc.h"\
	"..\..\inc_glb.32\syncthrd.hxx"\
	".\Dbasedll.hr"\
	".\Expreing.htp"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\Dbliste.hxx"\
	{$(INCLUDE)}"\Dbtools.hxx"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Errinstx.hxx"\
	{$(INCLUDE)}"\Expreing.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\U4util.h"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	
NODEP_CPP_EXPRE=\
	".\win16\dbasedll.h"\
	

"$(INTDIR)\EXPREING.OBJ" : $(SOURCE) $(DEP_CPP_EXPRE) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GB_PAINT.CXX
DEP_CPP_GB_PA=\
	".\Gizmo.h"\
	".\Gizmoint.h"\
	".\Win1632.h"\
	{$(INCLUDE)}"\Bttncur.h"\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\Gizmobar.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\GB_PAINT.OBJ" : $(SOURCE) $(DEP_CPP_GB_PA) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\GB_PAINT.OBJ" : $(SOURCE) $(DEP_CPP_GB_PA) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DBTOOLS.CXX

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

DEP_CPP_DBTOO=\
	".\Dbasedll.hr"\
	".\Dbtools.htp"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\Dbtools.hxx"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\U4util.h"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	
NODEP_CPP_DBTOO=\
	".\win16\dbasedll.h"\
	
# ADD CPP /Yu"d4all.h"

"$(INTDIR)\DBTOOLS.OBJ" : $(SOURCE) $(DEP_CPP_DBTOO) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"

DEP_CPP_DBTOO=\
	".\Dbasedll.hr"\
	".\Dbtools.htp"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\Dbtools.hxx"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\U4util.h"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	
NODEP_CPP_DBTOO=\
	".\win16\dbasedll.h"\
	

"$(INTDIR)\DBTOOLS.OBJ" : $(SOURCE) $(DEP_CPP_DBTOO) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GB_INIT.CXX
DEP_CPP_GB_IN=\
	".\Gizmo.h"\
	".\Gizmoint.h"\
	".\Win1632.h"\
	{$(INCLUDE)}"\Bttncur.h"\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\Gizmobar.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\GB_INIT.OBJ" : $(SOURCE) $(DEP_CPP_GB_IN) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\GB_INIT.OBJ" : $(SOURCE) $(DEP_CPP_GB_IN) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DBASPROF.CXX
DEP_CPP_DBASP=\
	".\Dbasedll.hr"\
	".\Dbasprof.htp"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\Dbaserel.hxx"\
	{$(INCLUDE)}"\Dbasprof.hxx"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\print.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\Strdup.hxx"\
	{$(INCLUDE)}"\trias01m.hxx"\
	{$(INCLUDE)}"\U4util.h"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	
NODEP_CPP_DBASP=\
	".\win16\dbasedll.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\DBASPROF.OBJ" : $(SOURCE) $(DEP_CPP_DBASP) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\DBASPROF.OBJ" : $(SOURCE) $(DEP_CPP_DBASP) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GB_API.CXX
DEP_CPP_GB_AP=\
	".\Gizmo.h"\
	".\Gizmoint.h"\
	".\Win1632.h"\
	{$(INCLUDE)}"\Bttncur.h"\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\Gizmobar.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\GB_API.OBJ" : $(SOURCE) $(DEP_CPP_GB_AP) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\GB_API.OBJ" : $(SOURCE) $(DEP_CPP_GB_AP) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\BTTNCUR.CXX
DEP_CPP_BTTNC=\
	".\Bttncuri.h"\
	{$(INCLUDE)}"\Bttncur.h"\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\BTTNCUR.OBJ" : $(SOURCE) $(DEP_CPP_BTTNC) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\BTTNCUR.OBJ" : $(SOURCE) $(DEP_CPP_BTTNC) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GIZMOBAR.CXX
DEP_CPP_GIZMO=\
	".\Gizmo.h"\
	".\Gizmoint.h"\
	".\Win1632.h"\
	{$(INCLUDE)}"\Bttncur.h"\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\Gizmobar.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\GIZMOBAR.OBJ" : $(SOURCE) $(DEP_CPP_GIZMO) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\GIZMOBAR.OBJ" : $(SOURCE) $(DEP_CPP_GIZMO) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GIZMO.CXX
DEP_CPP_GIZMO_=\
	".\Gizmo.h"\
	".\Gizmoint.h"\
	".\Win1632.h"\
	{$(INCLUDE)}"\Bttncur.h"\
	{$(INCLUDE)}"\C4.h"\
	{$(INCLUDE)}"\D4all.h"\
	{$(INCLUDE)}"\D4data.h"\
	{$(INCLUDE)}"\D4datafi.h"\
	{$(INCLUDE)}"\D4date.h"\
	{$(INCLUDE)}"\Dbasedlm.h"\
	{$(INCLUDE)}"\E4error.h"\
	{$(INCLUDE)}"\E4expr.h"\
	{$(INCLUDE)}"\E4parse.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\F4filese.h"\
	{$(INCLUDE)}"\Gizmobar.h"\
	{$(INCLUDE)}"\I4index.h"\
	{$(INCLUDE)}"\L4link.h"\
	{$(INCLUDE)}"\M4memo.h"\
	{$(INCLUDE)}"\M4memory.h"\
	{$(INCLUDE)}"\S4sort.h"\
	{$(INCLUDE)}"\U4util.h"\
	

!IF  "$(CFG)" == "Dbasedll - Win32 Release"

# ADD CPP /Yu"d4all.h"

"$(INTDIR)\GIZMO.OBJ" : $(SOURCE) $(DEP_CPP_GIZMO_) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MD /W3 /WX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Dbasedll - Win32 Debug"


"$(INTDIR)\GIZMO.OBJ" : $(SOURCE) $(DEP_CPP_GIZMO_) "$(INTDIR)"\
 "$(INTDIR)\Dbasedll.pch"
   $(CPP) /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DLL__" /D "MSWIND" /D "STRICT" /D "__CV__" /D "MDX"\
 /Fp"$(INTDIR)/Dbasedll.pch" /Yu"d4all.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE)


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
